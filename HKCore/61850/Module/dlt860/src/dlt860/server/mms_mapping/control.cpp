/*
 *  control.c
 */

#include "control.h"

#include "mms_mapping.h"
#include "dlt860_server.h"
#include "ied_server_private.h"

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)

#ifndef DEBUG_IED_SERVER
#define DEBUG_IED_SERVER 0
#endif

#define STATE_UNSELECTED 0
#define STATE_READY 1
#define STATE_WAIT_FOR_ACTIVATION_TIME 2
#define STATE_PERFORM_TEST 3
#define STATE_WAIT_FOR_EXECUTION 4
#define STATE_OPERATE 5

#define PENDING_EVENT_SELECTED 1
#define PENDING_EVENT_UNSELECTED 2
#define PENDING_EVENT_OP_RCVD_TRUE 4
#define PENDING_EVENT_OP_RCVD_FALSE 8
#define PENDING_EVENT_OP_OK_TRUE 16
#define PENDING_EVENT_OP_OK_FALSE 32

static GspMmsValue emptyString = {Data_PR_structure};

void
ControlObject_sendLastApplError(GspControlObject* self, GspMmsServerConnection connection, char* ctlVariable, int error,
        GspControlAddCause addCause, GspMmsValue* ctlNum, GspMmsValue* origin, bool handlerMode);

void
ControlObject_sendCommandTerminationPositive(GspControlObject* self);

void
ControlObject_sendCommandTerminationNegative(GspControlObject* self);

GspMmsValue*
Control_readAccessControlObject(GspMmsMapping* self, GspMmsDomain* domain, char* variableIdOrig,
        GspMmsServerConnection connection);

static void
unselectObject(GspControlObject* self);

static void
setState(GspControlObject* self, int newState)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->stateLock);
#endif

    self->state = newState;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->stateLock);
#endif
}

static int
getState(GspControlObject* self)
{
    int state;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->stateLock);
#endif

    state = self->state;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->stateLock);
#endif

    return state;
}

static void
setStSeld(GspControlObject* self, bool value)
{
    if (self->stSeld) {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->pendingEventsLock);
#endif

        if (value)
            self->pendingEvents |= PENDING_EVENT_SELECTED;
        else
            self->pendingEvents |= PENDING_EVENT_UNSELECTED;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->pendingEventsLock);
#endif
    }
}

static void
setOpRcvd(GspControlObject* self, bool value)
{
    if (self->opRcvd) {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->pendingEventsLock);
#endif

        if (value)
            self->pendingEvents |= PENDING_EVENT_OP_RCVD_TRUE;
        else
            self->pendingEvents |= PENDING_EVENT_OP_RCVD_FALSE;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->pendingEventsLock);
#endif
    }
}

static void
setOpOk(GspControlObject* self, bool value, uint64_t currentTimeInMs)
{
    if (self->opOk) {
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_wait(self->pendingEventsLock);
#endif

        if (value) {
            if (self->tOpOk) {
                GspMmsValue* timestamp = self->tOpOk->mmsValue;

                GspMmsValue_setUtcTimeMs(timestamp, currentTimeInMs);

                /* TODO update time quality */
            }


            self->pendingEvents |= PENDING_EVENT_OP_OK_TRUE;
        }
        else
            self->pendingEvents |= PENDING_EVENT_OP_OK_FALSE;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspSemaphore_post(self->pendingEventsLock);
#endif
    }
}

static void
updateSboTimeoutValue(GspControlObject* self)
{
    if (self->sboTimeout != nullptr) {
        uint32_t sboTimeoutVal = GspMmsValue_toInt32(self->sboTimeout);

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: set timeout for %s/%s.%s to %u\n", GspMmsDomain_getName(self->mmsDomain), self->lnName, self->name, sboTimeoutVal);

        self->selectTimeout = sboTimeoutVal;
    }
    else
        self->selectTimeout = CONFIG_CONTROL_DEFAULT_SBO_TIMEOUT;
}

static bool
isSboClassOperateOnce(GspControlObject* self)
{
    if (self->sboClass != nullptr) {
        if (GspMmsValue_toInt32(self->sboClass) == 1)
            return false;
        else
            return true;
    }
    else
        return true; /* default is operate-once ! */
}



static GspMmsValue*
getOperParameterOperTime(GspMmsValue* operParameters)
{
    if (GspMmsValue_getType(operParameters) == Data_PR_structure) {

        if (GspMmsValue_getArraySize(operParameters) == 7)
            return GspMmsValue_getElement(operParameters, 1);
    }

    return nullptr;
}

static bool
initiateControlTask(GspControlObject* self)
{
    GspClientConnection iedClientConnection =
            Gsp_private_IedServer_getClientConnectionByHandle(self->iedServer, self->mmsConnection);

    if (iedClientConnection == nullptr)
        return false;

    Gsp_private_ClientConnection_increaseTasksCount(iedClientConnection);

    return true;
}

static void
exitControlTask(GspControlObject* self)
{
    GspClientConnection iedClientConnection =
            Gsp_private_IedServer_getClientConnectionByHandle(self->iedServer, self->mmsConnection);

    if (iedClientConnection == nullptr)
        return;

    /* synchronize with connection management */
    Gsp_private_ClientConnection_decreaseTasksCount(iedClientConnection);
}

static void
abortControlOperation(GspControlObject* self)
{
    if ((self->ctlModel == 2) || (self->ctlModel == 4)) {

        if (isSboClassOperateOnce(self))
            unselectObject(self);
        else
            setState(self, STATE_READY);
    }
    else
        setState(self, STATE_READY);

    exitControlTask(self);
}

static GspControlHandlerResult
operateControl(GspControlObject* self, GspMmsValue* value, uint64_t currentTime, bool testCondition)
{
    self->selectTime = currentTime;

    self->errorValue = GSP_CONTROL_ERROR_NO_ERROR;
    self->addCauseValue = GSP_ADD_CAUSE_UNKNOWN;

    if (self->operateHandler != nullptr)
        return self->operateHandler((GspControlAction) self, self->operateHandlerParameter, value, testCondition);

    return GSP_CONTROL_RESULT_OK;
}

static void
executeControlTask(GspControlObject* self, uint64_t currentTimeInMs)
{
    int state;

executeStateMachine:

    state = getState(self);

    switch (state) {

    case STATE_WAIT_FOR_ACTIVATION_TIME:
    case STATE_WAIT_FOR_EXECUTION:
    {
        GspControlHandlerResult dynamicCheckResult = GSP_CONTROL_RESULT_OK;
        bool isTimeActivatedControl = false;

        if (state == STATE_WAIT_FOR_ACTIVATION_TIME)
           isTimeActivatedControl = true;

        self->errorValue = GSP_CONTROL_ERROR_NO_ERROR;
        self->addCauseValue = GSP_ADD_CAUSE_BLOCKED_BY_SYNCHROCHECK;

        if (self->waitForExecutionHandler != nullptr) {
            dynamicCheckResult = self->waitForExecutionHandler((GspControlAction) self, self->waitForExecutionHandlerParameter, self->ctlVal,
                    self->testMode, self->synchroCheck);
        }

        if (dynamicCheckResult == GSP_CONTROL_RESULT_FAILED) {
            if ((self->errorValue != GSP_CONTROL_ERROR_NO_ERROR) || (self->addCauseValue != GSP_ADD_CAUSE_UNKNOWN)) {
                ControlObject_sendLastApplError(self, self->mmsConnection, std::string("Oper").data(),
                        self->errorValue, self->addCauseValue,
                        self->ctlNum, self->origin, false);
            }

            if (!isTimeActivatedControl) {
                // TODO:
//                MmsServerConnection_sendWriteResponse(self->mmsConnection, self->operateInvokeId,
//                        DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED, true);
            }

            abortControlOperation(self);
            exitControlTask(self);
        }
        else if (dynamicCheckResult == GSP_CONTROL_RESULT_OK) {
            if (isTimeActivatedControl) {
                ControlObject_sendCommandTerminationPositive(self);

                GspMmsValue* operTm = getOperParameterOperTime(self->oper);

                GspMmsValue_setUtcTime(operTm, 0);

            }
            else {
                // TODO:
//                MmsServerConnection_sendWriteResponse(self->mmsConnection, self->operateInvokeId,
//                        DATA_ACCESS_ERROR_SUCCESS, true);
            }

            setState(self, STATE_OPERATE);

            setOpOk(self, true, currentTimeInMs);

            goto executeStateMachine;
        }
    }
    break;

    case STATE_OPERATE:
    {
        uint64_t currentTime = GSP_Hal_getTimeInMs();

        GspControlHandlerResult result = operateControl(self, self->ctlVal, currentTime, self->testMode);

        if (result != GSP_CONTROL_RESULT_WAITING) {

            if (result == GSP_CONTROL_RESULT_OK) {

                if ((self->ctlModel == 4) || (self->ctlModel == 3)) {
                    ControlObject_sendCommandTerminationPositive(self);
                }
            }
            else {

                if ((self->ctlModel == 4) || (self->ctlModel == 3)) {
                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: operate failed!\n");

                    ControlObject_sendCommandTerminationNegative(self);
                }
            }

            abortControlOperation(self);
            exitControlTask(self);

            setOpOk(self, false, currentTimeInMs);
        }
    }
    break;

    }
}

GspControlObject*
GspControlObject_create(GspIedServer iedServer, GspMmsDomain* domain, char* lnName, char* name, GspMmsVariableSpecification* operSpec)
{
    GspControlObject* self = (GspControlObject*) GLOBAL_CALLOC(1, sizeof(GspControlObject));

    if (self == nullptr)
        return nullptr;

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: create control object for LD: %s, LN: %s, name: %s\n", domain->domainName, lnName, name);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    self->stateLock = GspSemaphore_create(1);
    self->pendingEventsLock = GspSemaphore_create(1);

    if ((self->stateLock == nullptr) || (self->pendingEventsLock == nullptr)) {
        GspControlObject_destroy(self);
        self = nullptr;
        return nullptr;
    }
#endif

    self->name = StringUtils_copyString(name);

    if (self->name == nullptr) {
        GspControlObject_destroy(self);
        self = nullptr;
        return self;
    }

    self->lnName = lnName;
    self->mmsDomain = domain;
    self->iedServer = iedServer;

    GspMmsVariableSpecification* ctlValSpec = GspMmsVariableSpecification_getChildSpecificationByName(operSpec, "ctlVal", nullptr);

    if (ctlValSpec) {
        self->ctlVal = GspMmsValue_newDefaultValue(ctlValSpec);
    }
    else {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: control object %s/%s.%s has no ctlVal element!\n", domain->domainName, lnName, name);
    }


    GspMmsVariableSpecification* originSpec = GspMmsVariableSpecification_getChildSpecificationByName(operSpec, "origin", nullptr);

    if (originSpec) {
        self->origin = GspMmsValue_newDefaultValue(originSpec);
    }
    else {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: control object %s/%s.%s has no origin element!\n", domain->domainName, lnName, name);
    }

    self->ctlNum = GspMmsValue_newUnsigned(8);
    return self;
}

void
GspControlObject_initialize(GspControlObject* self)
{
    GspMmsServer mmsServer = GspIedServer_getMmsServer(self->iedServer);

    if (emptyString.present != Data_PR_visible_string) {
        emptyString.present = Data_PR_visible_string;
        emptyString.choice.visible_string.size = 0;
        emptyString.choice.visible_string.buf = nullptr;
    }

    char strBuf[129];

    char* ctlModelName = StringUtils_createStringInBuffer(strBuf, 4, self->lnName, "$CF$", self->name, "$ctlModel");

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: initialize control for %s\n", ctlModelName);

    GspMmsValue* ctlModel = MmsServer_getValueFromCache(mmsServer,
            self->mmsDomain, ctlModelName);

    if (ctlModel == nullptr) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: No control model found for variable %s\n", ctlModelName);
    }

    char* sboClassName = StringUtils_createStringInBuffer(strBuf, 4, self->lnName, "$CF$", self->name, "$sboClass");

    self->sboClass = MmsServer_getValueFromCache(mmsServer, self->mmsDomain, sboClassName);

    char* ctlNumName = StringUtils_createStringInBuffer(strBuf, 4, self->lnName, "$ST$", self->name, "$ctlNum");

    self->ctlNumSt = MmsServer_getValueFromCache(mmsServer, self->mmsDomain, ctlNumName);

    char* originName = StringUtils_createStringInBuffer(strBuf, 4, self->lnName, "$ST$", self->name, "$origin");

    self->originSt = MmsServer_getValueFromCache(mmsServer, self->mmsDomain, originName);

    char* sboTimeoutName = StringUtils_createStringInBuffer(strBuf, 4, self->lnName, "$CF$", self->name, "$sboTimeout");

    self->sboTimeout = MmsServer_getValueFromCache(mmsServer,
         self->mmsDomain, sboTimeoutName);

    updateSboTimeoutValue(self);

    if (self->sbo) {
        char* controlObjectReference = StringUtils_createStringInBuffer(strBuf, 6, self->mmsDomain->domainName,
                "/", self->lnName, "$CO$", self->name, "$SBO");

        GspMmsValue_setVisibleString(self->sbo, controlObjectReference);
    }

    char* stSeldName = StringUtils_createStringInBuffer(strBuf, 6, self->mmsDomain->domainName, "/", self->lnName, ".", self->name, ".stSeld");

    GspIedModel *model = GspMmsMapping_getIedModelByDomainName(self->iedServer->mmsMapping, self->mmsDomain->domainName);
    self->stSeld = (GspDataAttribute*) GspIedModel_getModelNodeByObjectReference(model, stSeldName);

    if ((self->stSeld) && (self->stSeld->type != DLT860_BOOLEAN)) {
        self->stSeld = nullptr;

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER:  ERROR - stSeld of wrong type!\n");
    }

    char* opRcvdName = StringUtils_createStringInBuffer(strBuf, 6, self->mmsDomain->domainName, "/", self->lnName, ".", self->name, ".opRcvd");

    self->opRcvd = (GspDataAttribute*) GspIedModel_getModelNodeByObjectReference(model, opRcvdName);

    if ((self->opRcvd) && (self->opRcvd->type != DLT860_BOOLEAN)) {
        self->opRcvd = nullptr;

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER:  ERROR - opRcvd of wrong type!\n");
    }

    char* opOkName = StringUtils_createStringInBuffer(strBuf, 6, self->mmsDomain->domainName, "/", self->lnName, ".", self->name, ".opOk");

    self->opOk = (GspDataAttribute*) GspIedModel_getModelNodeByObjectReference(model, opOkName);

    if ((self->opOk) && (self->opOk->type != DLT860_BOOLEAN)) {
        self->opOk = nullptr;

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER:  ERROR - opOk of wrong type!\n");
    }

    char* tOpOkName = StringUtils_createStringInBuffer(strBuf, 6, self->mmsDomain->domainName, "/", self->lnName, ".", self->name, ".tOpOk");

    //self->tOpOk = (DataAttribute*) IedModel_getModelNodeByObjectReference(self->iedServer->model, tOpOkName);

    if ((self->tOpOk) && (self->tOpOk->type != DLT860_TIMESTAMP)) {
        self->tOpOk = nullptr;

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER:  ERROR - tOpOk of wrong type!\n");
    }

    self->error = GspMmsValue_newIntegerFromInt32(0);
    self->addCause = GspMmsValue_newIntegerFromInt32(0);

    if (ctlModel != nullptr) {
        int ctlModelVal = GspMmsValue_toInt32(ctlModel);

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER:  ctlModel: %i\n", ctlModelVal);

        if ((ctlModelVal < 0) || (ctlModelVal > 4)) {
            ctlModelVal = 1;
            if (DEBUG_IED_SERVER)
                printf("IED_SERVER:  invalid control model!\n");
        }

        self->ctlModel = ctlModelVal;

        if ((ctlModelVal == 2) || (ctlModelVal == 4)) /* SBO */
            setState(self, STATE_UNSELECTED);
        else
            setState(self, STATE_READY);
    }
}

static void
ControlObject_handlePendingEvents(GspControlObject* self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->pendingEventsLock);
#endif

    if (self->pendingEvents > 0) {

        if (self->pendingEvents & PENDING_EVENT_SELECTED) {
            if (self->stSeld)
                GspIedServer_updateBooleanAttributeValue(self->iedServer, self->stSeld, true);

            self->pendingEvents &= ~(PENDING_EVENT_SELECTED);
        }

        if (self->pendingEvents & PENDING_EVENT_UNSELECTED) {
            if (self->stSeld)
                GspIedServer_updateBooleanAttributeValue(self->iedServer, self->stSeld, false);

            self->pendingEvents &= ~(PENDING_EVENT_UNSELECTED);
        }

        if (self->pendingEvents & PENDING_EVENT_OP_RCVD_TRUE) {
            if (self->opRcvd)
                GspIedServer_updateBooleanAttributeValue(self->iedServer, self->opRcvd, true);

            self->pendingEvents &= ~(PENDING_EVENT_OP_RCVD_TRUE);
        }

        if (self->pendingEvents & PENDING_EVENT_OP_RCVD_FALSE) {
            if (self->opRcvd)
                GspIedServer_updateBooleanAttributeValue(self->iedServer, self->opRcvd, false);

            self->pendingEvents &= ~(PENDING_EVENT_OP_RCVD_FALSE);
        }

        if (self->pendingEvents & PENDING_EVENT_OP_OK_TRUE) {
            if (self->opOk)
                GspIedServer_updateBooleanAttributeValue(self->iedServer, self->opOk, true);

            self->pendingEvents &= ~(PENDING_EVENT_OP_OK_TRUE);
        }

        if (self->pendingEvents & PENDING_EVENT_OP_OK_FALSE) {
            if (self->opOk)
                GspIedServer_updateBooleanAttributeValue(self->iedServer, self->opOk, false);

            self->pendingEvents &= ~(PENDING_EVENT_OP_OK_FALSE);
        }
    }

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->pendingEventsLock);
#endif
}

void
GspControlObject_destroy(GspControlObject* self)
{
    if (self->mmsValue)
        GspMmsValue_delete(self->mmsValue);

    if (self->error)
        GspMmsValue_delete(self->error);

    if (self->addCause)
        GspMmsValue_delete(self->addCause);

    if (self->ctlVal)
        GspMmsValue_delete(self->ctlVal);

    if (self->ctlNum)
        GspMmsValue_delete(self->ctlNum);

    if (self->origin)
        GspMmsValue_delete(self->origin);

    if (self->name)
        GLOBAL_FREEMEM(self->name);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    if (self->stateLock)
        GspSemaphore_destroy(self->stateLock);

    if (self->pendingEventsLock)
        GspSemaphore_destroy(self->pendingEventsLock);
#endif

    GLOBAL_FREEMEM(self);
}

char*
GspControlObject_getName(GspControlObject* self)
{
    return self->name;
}

char*
GspControlObject_getLNName(GspControlObject* self)
{
    return self->lnName;
}

GspMmsDomain*
GspControlObject_getDomain(GspControlObject* self)
{
    return self->mmsDomain;
}

void
GspControlObject_setMmsValue(GspControlObject* self, GspMmsValue* value)
{
    self->mmsValue = value;
}

void
GspControlObject_setTypeSpec(GspControlObject* self, GspMmsVariableSpecification* typeSpec)
{
    self->typeSpec = typeSpec;
}

GspMmsVariableSpecification*
GspControlObject_getTypeSpec(GspControlObject* self)
{
    return self->typeSpec;
}

GspMmsValue*
GspControlObject_getMmsValue(GspControlObject* self)
{
    return self->mmsValue;
}

static void
selectObject(GspControlObject* self, uint64_t selectTime, GspMmsServerConnection connection)
{
    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: control %s/%s.%s selected\n", GspMmsDomain_getName(self->mmsDomain), self->lnName, self->name);

    updateSboTimeoutValue(self);

    self->selectTime = selectTime;
    self->mmsConnection = connection;
    setStSeld(self, true);
    setState(self, STATE_READY);
}

static void
unselectObject(GspControlObject* self)
{
    setState(self, STATE_UNSELECTED);

    setStSeld(self, false);

    self->mmsConnection = nullptr;

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: control %s/%s.%s unselected\n", GspMmsDomain_getName(self->mmsDomain), self->lnName, self->name);
}

static void
checkSelectTimeout(GspControlObject* self, uint64_t currentTime)
{
    if ((self->ctlModel == 2) || (self->ctlModel == 4)) {

        if (getState(self) == STATE_READY) {
            if (self->selectTimeout > 0) {
                if (currentTime > (self->selectTime + self->selectTimeout)) {
                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: select-timeout (timeout-val = %i) for control %s/%s.%s\n",
                                self->selectTimeout, GspMmsDomain_getName(self->mmsDomain), self->lnName, self->name);

                    unselectObject(self);
                }
            }
        }
    }
}

bool
GspControlObject_unselect(GspControlObject* self, GspMmsServerConnection connection)
{
    if (self->mmsConnection == connection) {
        abortControlOperation(self);
        return true;
    }
    else
        return false;
}

void
GspControlObject_installListener(GspControlObject* self, GspControlHandler listener, void* parameter)
{
    self->operateHandler = listener;
    self->operateHandlerParameter = parameter;
}

void
GspControlObject_installCheckHandler(GspControlObject* self, GspControlPerformCheckHandler handler, void* parameter)
{
    self->checkHandler = handler;
    self->checkHandlerParameter = parameter;
}

void
GspControlObject_installWaitForExecutionHandler(GspControlObject* self, GspControlWaitForExecutionHandler handler,
        void* parameter)
{
    self->waitForExecutionHandler = handler;
    self->waitForExecutionHandlerParameter = parameter;
}

void
GspControlObject_updateControlModel(GspControlObject* self, GspControlModel value, GspDataObject* ctlObject)
{
    self->ctlModel = (uint32_t) value;

    if ((self->ctlModel == 2) || (self->ctlModel == 4)) /* SBO */
        setState(self, STATE_UNSELECTED);
    else
        setState(self, STATE_READY);

    GspDataAttribute* ctlModel = (GspDataAttribute*) GspModelNode_getChild((GspModelNode*) ctlObject, "ctlModel");

    if (ctlModel) {
        GspIedServer_updateInt32AttributeValue(self->iedServer, ctlModel, (int32_t) value);
    }
}

void
GspControl_processControlActions(GspMmsMapping* self, uint64_t currentTimeInMs)
{
    for(auto &item : *(self->controlObjects))
    {
        GspControlObject* controlObject = (GspControlObject*) item;

        if (controlObject->state == STATE_WAIT_FOR_ACTIVATION_TIME) {

            if (controlObject->operateTime <= currentTimeInMs) {

                /* enter state Perform Test */
                setOpRcvd(controlObject, true);

                if (DEBUG_IED_SERVER)
                    printf("IED_SERVER: time activated operate: perform test\n");

                controlObject->timeActivatedOperate = false;

                GspCheckHandlerResult checkResult = GSP_CONTROL_ACCEPTED;

                if (controlObject->checkHandler != nullptr) { /* perform operative tests */

                    controlObject->errorValue = GSP_CONTROL_ERROR_NO_ERROR;
                    controlObject->addCauseValue = GSP_ADD_CAUSE_BLOCKED_BY_INTERLOCKING;

                    checkResult = controlObject->checkHandler((GspControlAction) self,
                            controlObject->checkHandlerParameter, controlObject->ctlVal, controlObject->testMode,
                            controlObject->interlockCheck);
                }

                if (checkResult == GSP_CONTROL_ACCEPTED) {

                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: time activated operate: command accepted\n");

                    /* leave state Perform Test */
                    setOpRcvd(controlObject, false);

                    executeControlTask(controlObject, currentTimeInMs);
                }
                else {

                    ControlObject_sendLastApplError(controlObject, controlObject->mmsConnection, std::string("Oper").data(),
                            controlObject->errorValue, controlObject->addCauseValue,
                                controlObject->ctlNum, controlObject->origin, false);

                    /* leave state Perform Test */
                    setOpRcvd(controlObject, false);

                    abortControlOperation(controlObject);
                }
            }

        } /* if (controlObject->state == STATE_WAIT_FOR_ACTICATION_TIME) */
        else if (!((controlObject->state == STATE_UNSELECTED) || (controlObject->state == STATE_READY))) {
            executeControlTask(controlObject, currentTimeInMs);
        }
        else if (controlObject->state == STATE_READY) {
            checkSelectTimeout(controlObject, currentTimeInMs);
        }

        ControlObject_handlePendingEvents(controlObject);

    }
}

GspControlObject*
GspControl_lookupControlObject(GspMmsMapping* self, GspMmsDomain* domain, char* lnName, char* objectName)
{
    for(auto &item : *(self->controlObjects))
    {
        GspControlObject* controlObject = (GspControlObject*) item;

        if (GspControlObject_getDomain(controlObject) == domain) {
            if (strcmp(GspControlObject_getLNName(controlObject), lnName) == 0) {
                if (strcmp(GspControlObject_getName(controlObject), objectName) == 0) {
                    return controlObject;
                }
            }
        }

    }

    return nullptr;
}

static GspMmsValue*
getCtlVal(GspMmsValue* operParameters)
{
    if (GspMmsValue_getType(operParameters) == Data_PR_structure) {
        if (GspMmsValue_getArraySize(operParameters) > 5) {
            return GspMmsValue_getElement(operParameters, 0);
        }
    }

    return nullptr;
}

static GspMmsValue*
getOperParameterCtlNum(GspMmsValue* operParameters)
{
    if (GspMmsValue_getType(operParameters) == Data_PR_structure) {
        if (GspMmsValue_getArraySize(operParameters) == 7)
            return GspMmsValue_getElement(operParameters, 3);
        else if (GspMmsValue_getArraySize(operParameters) == 6)
            return GspMmsValue_getElement(operParameters, 2);
    }

    return nullptr;
}

static GspMmsValue*
getCancelParameterCtlNum(GspMmsValue* operParameters)
{
    if (GspMmsValue_getType(operParameters) == Data_PR_structure) {
        if (GspMmsValue_getArraySize(operParameters) == 6)
            return GspMmsValue_getElement(operParameters, 3);
        else if (GspMmsValue_getArraySize(operParameters) == 5)
            return GspMmsValue_getElement(operParameters, 2);
    }

    return nullptr;
}

static GspMmsValue*
getCancelParameterOrigin(GspMmsValue* operParameters)
{
    if (GspMmsValue_getType(operParameters) == Data_PR_structure) {
        if (GspMmsValue_getArraySize(operParameters) == 6)
            return GspMmsValue_getElement(operParameters, 2);
        else if (GspMmsValue_getArraySize(operParameters) == 5)
            return GspMmsValue_getElement(operParameters, 1);
    }

    return nullptr;
}

static GspMmsValue*
getOperParameterTest(GspMmsValue* operParameters)
{
    if (GspMmsValue_getType(operParameters) == Data_PR_structure)
    {
        if (GspMmsValue_getArraySize(operParameters) == 7)
            return GspMmsValue_getElement(operParameters, 5);
        else if (GspMmsValue_getArraySize(operParameters) == 6)
            return GspMmsValue_getElement(operParameters, 4);
    }

    return nullptr;
}

static GspMmsValue*
getOperParameterCheck(GspMmsValue* operParameters)
{
    if (GspMmsValue_getType(operParameters) == Data_PR_structure)
    {
        if (GspMmsValue_getArraySize(operParameters) == 7)
            return GspMmsValue_getElement(operParameters, 6);
        else if (GspMmsValue_getArraySize(operParameters) == 6)
            return GspMmsValue_getElement(operParameters, 5);
    }

    return nullptr;
}

static GspMmsValue*
getOperParameterOrigin(GspMmsValue* operParameters)
{
    if (GspMmsValue_getType(operParameters) == Data_PR_structure)
    {
        if (GspMmsValue_getArraySize(operParameters) == 7)
            return GspMmsValue_getElement(operParameters, 2);
        else if (GspMmsValue_getArraySize(operParameters) == 6)
            return GspMmsValue_getElement(operParameters, 1);
    }

    return nullptr;
}

static GspMmsValue*
getOperParameterTime(GspMmsValue* operParameters)
{
    GspMmsValue* timeParameter = nullptr;

    if (GspMmsValue_getType(operParameters) == Data_PR_structure)
    {
        if (GspMmsValue_getArraySize(operParameters) == 7)
            timeParameter = GspMmsValue_getElement(operParameters, 4);
        else if (GspMmsValue_getArraySize(operParameters) == 6)
            timeParameter = GspMmsValue_getElement(operParameters, 3);
    }

    if (timeParameter != nullptr)
        if ((GspMmsValue_getType(timeParameter) == Data_PR_utc_time) || (GspMmsValue_getType(timeParameter) == Data_PR_binary_time))
            return timeParameter;

    return nullptr;
}

void
ControlObject_sendCommandTerminationPositive(GspControlObject* self)
{
    char itemId[68]; /* 64 characters + space for FC + separator + string terminator */

    StringUtils_createStringInBuffer(itemId, 4, self->lnName, "$CO$", self->name, "$Oper");

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: send CommandTermination+: %s\n", itemId);

    GspMmsVariableAccessSpecification varSpec;

    varSpec.itemId = itemId;
    varSpec.domainId = GspMmsDomain_getName(self->mmsDomain);

    struct sGspLinkedList _varSpecList1;
    _varSpecList1.next = nullptr;
    struct sGspLinkedList _varSpecList;
    _varSpecList.data = nullptr;
    _varSpecList.next = &_varSpecList1;

    struct sGspLinkedList _values1;
    _values1.next = nullptr;
    struct sGspLinkedList _values;
    _values.data = nullptr;
    _values.next = &_values1;

    _varSpecList1.data = &varSpec;
    _values1.data = self->oper;

//    GspMmsServerConnection_sendInformationReportListOfVariables(self->mmsConnection, &_varSpecList, &_values, false);
}

void
ControlObject_sendCommandTerminationNegative(GspControlObject* self)
{
    /* create LastApplError */

    struct sGspLinkedList _varSpecList2;
    _varSpecList2.next = nullptr;
    struct sGspLinkedList _varSpecList1;
    _varSpecList1.next = &_varSpecList2;
    struct sGspLinkedList _varSpecList;
    _varSpecList.data = nullptr;
    _varSpecList.next = &_varSpecList1;

    struct sGspLinkedList _values2;
    _values2.next = nullptr;
    struct sGspLinkedList _values1;
    _values1.next = &_values2;
    struct sGspLinkedList _values;
    _values.data = nullptr;
    _values.next = &_values1;

    GspMmsValue lastApplErrorMemory;

    GspMmsValue* lastApplError = &lastApplErrorMemory;
    lastApplError->present = Data_PR_structure;
    char ctlObj[130];

    StringUtils_createStringInBuffer(ctlObj, 6, GspMmsDomain_getName(self->mmsDomain), "/",
            self->lnName, "$CO$", self->name, "$Oper");

    GspMmsValue ctlObjValueMemory;

    GspMmsValue* ctlObjValue = &ctlObjValueMemory;
    ctlObjValue->present = Data_PR_visible_string;
    ctlObjValue->choice.visible_string.buf = (uint8_t *)ctlObj;
    ctlObjValue->choice.visible_string.size = sizeof(ctlObj);

    GspMmsValue_setElement(lastApplError, 0, ctlObjValue);

    GspMmsValue_setInt32(self->error, self->errorValue);
    GspMmsValue_setInt32(self->addCause, self->addCauseValue);

    GspMmsValue_setElement(lastApplError, 1, self->error);
    GspMmsValue_setElement(lastApplError, 2, self->origin);
    GspMmsValue_setElement(lastApplError, 3, self->ctlNum);
    GspMmsValue_setElement(lastApplError, 4, self->addCause);

    GspMmsVariableAccessSpecification lastApplErrorVarSpec;

    lastApplErrorVarSpec.itemId = StringUtils_createStringFromBuffer((uint8_t*)"lastError", 10);
    lastApplErrorVarSpec.domainId = nullptr;

    /* create oper variable */

    char itemId[130];

    StringUtils_createStringInBuffer(itemId, 4, self->lnName, "$CO$", self->name, "$Oper");

    char* domainId = GspMmsDomain_getName(self->mmsDomain);

    GspMmsVariableAccessSpecification operVarSpec;

    operVarSpec.itemId = itemId;
    operVarSpec.domainId = domainId;

    /* create response */

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: send CommandTermination-: %s\n", itemId);

    _varSpecList1.data = &lastApplErrorVarSpec;
    _varSpecList2.data = &operVarSpec;

    _values1.data = lastApplError;
    _values2.data = self->oper;
} /* ControlObject_sendCommandTerminationNegative() */



void
ControlObject_sendLastApplError(GspControlObject* self, GspMmsServerConnection connection, char* ctlVariable, int error,
        GspControlAddCause addCause, GspMmsValue* ctlNum, GspMmsValue* origin, bool handlerMode)
{
    GspMmsValue lastApplErrorMemory;

    GspMmsValue* lastApplError = &lastApplErrorMemory;
    lastApplError->present = Data_PR_structure;
    char ctlObj[130];

    StringUtils_createStringInBuffer(ctlObj, 7, GspMmsDomain_getName(self->mmsDomain), "/",
            self->lnName, "$CO$", self->name, "$", ctlVariable);

    if (DEBUG_IED_SERVER) {
        printf("IED_SERVER: sendLastApplError:\n");
        printf("IED_SERVER:    control object: %s\n", ctlObj);
        printf("IED_SERVER:    ctlNum: %u\n", GspMmsValue_toUint32(ctlNum));
    }

    GspMmsValue ctlObjValueMemory;

    GspMmsValue* ctlObjValue = &ctlObjValueMemory;
    ctlObjValue->present = Data_PR_visible_string;
    ctlObjValue->choice.visible_string.buf = (uint8_t*)ctlObj;
    ctlObjValue->choice.visible_string.size = sizeof(ctlObj);

    GspMmsValue_setElement(lastApplError, 0, ctlObjValue);

    GspMmsValue_setInt32(self->error, error);
    GspMmsValue_setInt32(self->addCause, addCause);

    GspMmsValue_setElement(lastApplError, 1, self->error);
    GspMmsValue_setElement(lastApplError, 2, origin);
    GspMmsValue_setElement(lastApplError, 3, ctlNum);
    GspMmsValue_setElement(lastApplError, 4, self->addCause);

//    GspMmsServerConnection_sendInformationReportSingleVariableVMDSpecific(connection,
//            "LastApplError", lastApplError, handlerMode);
}

static void
updateControlParameters(GspControlObject* controlObject, GspMmsValue* ctlVal, GspMmsValue* ctlNum, GspMmsValue* origin, bool synchroCheck, bool interlockCheck)
{
    GspMmsValue_update(controlObject->ctlVal, ctlVal);
    GspMmsValue_update(controlObject->ctlNum, ctlNum);
    GspMmsValue_update(controlObject->origin, origin);
    controlObject->synchroCheck = synchroCheck;
    controlObject->interlockCheck = interlockCheck;

    if (controlObject->ctlNumSt)
        GspMmsValue_update(controlObject->ctlNumSt, ctlNum);

    if (controlObject->originSt)
        GspMmsValue_update(controlObject->originSt, origin);
}

static bool
doesElementEquals(char* element, const char* name)
{
    int i = 0;

    while (name[i] != 0) {
        if (element[i] == 0)
            return false;

        if (element[i] != name[i])
            return false;

        i++;
    }

    if ((element[i] != 0) && (element[i] != '$'))
        return false;

    return true;
}

GspMmsValue*
Control_readAccessControlObject(GspMmsMapping* self, GspMmsDomain* domain, char* variableIdOrig,
        GspMmsServerConnection connection)
{
    GspMmsValue* value = nullptr;

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: readAccessControlObject: %s\n", variableIdOrig);

    char variableId[129];

    strncpy(variableId, variableIdOrig, 128);
    variableId[128] = 0;

    char* separator = strchr(variableId, '$');

    if (separator == nullptr)
        return nullptr;

    *separator = 0;

    char* lnName = variableId;

    if (lnName == nullptr)
        return nullptr;

    char* objectName = GspMmsMapping_getNextNameElement(separator + 1);

    if (objectName == nullptr)
        return nullptr;

    char* varName =  GspMmsMapping_getNextNameElement(objectName);

    if (varName != nullptr) {

        bool foundVar = false;

        char* nextVarName = varName;

        do {
            if (doesElementEquals(varName, "Oper") ||
                doesElementEquals(varName, "SBO") ||
                doesElementEquals(varName, "SBOw") ||
                doesElementEquals(varName, "Cancel"))
            {
                *(varName - 1) = 0;
                foundVar = true;
                break;
            }

            nextVarName  = GspMmsMapping_getNextNameElement(varName);

            if (nextVarName != nullptr)
                varName = nextVarName;

        } while (nextVarName != nullptr);

        if (foundVar == false)
            varName = nullptr;
    }

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: read_access control object: objectName: (%s) varName: (%s)\n", objectName, varName);

    GspControlObject* controlObject = GspControl_lookupControlObject(self, domain, lnName, objectName);

    if (controlObject != nullptr) {

        if (varName != nullptr) {
            if (strcmp(varName, "Oper") == 0)
                value = controlObject->oper;
            else if (strcmp(varName, "SBOw") == 0)
                value = controlObject->sbow;
            else if (strcmp(varName, "SBO") == 0) {
                if (controlObject->ctlModel == 2) {

                    uint64_t currentTime = GSP_Hal_getTimeInMs();

                    value = &emptyString;

                    checkSelectTimeout(controlObject, currentTime);

                    if (getState(controlObject) == STATE_UNSELECTED) {
                        GspCheckHandlerResult checkResult = GSP_CONTROL_ACCEPTED;

                        /* opRcvd must not be set here! */

                        controlObject->addCauseValue = GSP_ADD_CAUSE_UNKNOWN;
                        controlObject->mmsConnection = connection;

                        if (controlObject->checkHandler != nullptr) { /* perform operative tests */

                            controlObject->isSelect = 1;

                            checkResult = controlObject->checkHandler((GspControlAction) controlObject,
                                    controlObject->checkHandlerParameter, nullptr, false, false);

                            controlObject->isSelect = 0;
                        }

                        if (checkResult == GSP_CONTROL_ACCEPTED) {
                            selectObject(controlObject, currentTime, connection);
                            value = controlObject->sbo;
                        }
                    }

                }
                else {
                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: select not applicable for control model %i\n", controlObject->ctlModel);

                    value = controlObject->sbo;
                }
            }

            else if (strcmp(varName, "Cancel") == 0)
                value = controlObject->cancel;
            else {
                value = GspMmsValue_getSubElement(GspControlObject_getMmsValue(controlObject),
                        GspControlObject_getTypeSpec(controlObject), varName);
            }
        }
        else
            value = GspControlObject_getMmsValue(controlObject);
    }

    return value;
}

static bool
checkValidityOfOriginParameter(GspMmsValue* origin)
{
    //    if (MmsValue_getType(origin) != MMS_STRUCTURE)
    //        return false;

    //    if (MmsValue_getArraySize(origin) != 2)
    //        return false;

    //    MmsValue* orIdent = MmsValue_getElement(origin, 1);

    //    if (MmsValue_getType(orIdent) != MMS_OCTET_STRING)
    //        return false;

    //    if (MmsValue_getOctetStringSize(orIdent) > 64)
    //        return false;

    //    MmsValue* orCat = MmsValue_getElement(origin, 0);

    //    if (MmsValue_getType(orCat) != MMS_INTEGER)
    //        return false;

    //    int orCatIntValue = MmsValue_toInt32(orCat);

    //    if ((orCatIntValue < 0) || (orCatIntValue > 8))
    //        return false;

    return true;
}

GspMmsDataAccessError
GspControl_writeAccessControlObject(GspMmsMapping* self, GspMmsDomain* domain, char* variableIdOrig,
        GspMmsValue* value, GspMmsServerConnection connection)
{
    GspMmsDataAccessError indication = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;

    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: writeAccessControlObject: %s\n", variableIdOrig);

    char variableId[65];

    strncpy(variableId, variableIdOrig, 64);
    variableId[64] = 0;

    char* separator = strchr(variableId, '$');

    if (separator == nullptr)
        return indication;

    *separator = 0;

    char* lnName = variableId;

    if (lnName == nullptr)
        return indication;

    char* objectName = GspMmsMapping_getNextNameElement(separator + 1);

    if (objectName == nullptr)
        return indication;

    char* varName =  GspMmsMapping_getNextNameElement(objectName);

    if (varName != nullptr) {

        bool foundVar = false;

        char* nextVarName = varName;

        do {
            if (doesElementEquals(varName, "Oper") ||
                doesElementEquals(varName, "SBO") ||
                doesElementEquals(varName, "SBOw") ||
                doesElementEquals(varName, "Cancel"))
            {
                *(varName - 1) = 0;
                foundVar = true;
                break;
            }

            nextVarName  = GspMmsMapping_getNextNameElement(varName);

            if (nextVarName != nullptr)
                varName = nextVarName;

        } while (nextVarName != nullptr);

        if (foundVar == false)
            varName = nullptr;
    }


    if (DEBUG_IED_SERVER)
        printf("IED_SERVER: write access control: objectName: (%s) varName: (%s)\n", objectName, varName);


    if (varName == nullptr) {
        indication = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
        return indication;
    }

    GspControlObject* controlObject = GspControl_lookupControlObject(self, domain, lnName, objectName);

    if (controlObject == nullptr) {
        indication = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
        return indication;
    }

    if (controlObject->ctlModel == GSP_CONTROL_MODEL_STATUS_ONLY) {
        indication = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_UNSUPPORTED;
        return indication;
    }

    if (strcmp(varName, "SBOw") == 0) { /* select with value */

        if (controlObject->ctlModel == 4) {

            GspMmsValue* ctlVal = getCtlVal(value);

            if (ctlVal != nullptr) {

                GspMmsValue* ctlNum = getOperParameterCtlNum(value);
                GspMmsValue* origin = getOperParameterOrigin(value);
                GspMmsValue* check = getOperParameterCheck(value);
                GspMmsValue* test = getOperParameterTest(value);

                if (checkValidityOfOriginParameter(origin) == false) {
                    indication = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;

                    ControlObject_sendLastApplError(controlObject, connection, std::string("SBOw").data(), GSP_CONTROL_ERROR_NO_ERROR,
                            GSP_ADD_CAUSE_SELECT_FAILED, ctlNum, origin, true);

                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: SBOw - invalid origin value\n");

                    return indication;
                }

                uint64_t currentTime = GSP_Hal_getTimeInMs();

                checkSelectTimeout(controlObject, currentTime);

                int state = getState(controlObject);

                if (state != STATE_UNSELECTED) {
                    indication = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;

                    ControlObject_sendLastApplError(controlObject, connection, std::string("SBOw").data(), GSP_CONTROL_ERROR_NO_ERROR,
                            GSP_ADD_CAUSE_OBJECT_ALREADY_SELECTED, ctlNum, origin, true);

                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: SBOw - select failed!\n");
                }
                else {

                    GspCheckHandlerResult checkResult = GSP_CONTROL_ACCEPTED;

                    /* opRcvd must not be set here! */

                    bool interlockCheck = GspMmsValue_getBitStringBit(check, 1);
                    bool synchroCheck = GspMmsValue_getBitStringBit(check, 0);
                    bool testCondition = GspMmsValue_getBoolean(test);

                    controlObject->addCauseValue = GSP_ADD_CAUSE_SELECT_FAILED;

                    updateControlParameters(controlObject, ctlVal, ctlNum, origin, synchroCheck, interlockCheck);

                    if (controlObject->checkHandler != nullptr) { /* perform operative tests */

                        controlObject->isSelect = 1;

                        controlObject->mmsConnection = connection;

                        checkResult = controlObject->checkHandler((GspControlAction) controlObject,
                                controlObject->checkHandlerParameter, ctlVal, testCondition, interlockCheck);

                        controlObject->isSelect = 0;
                    }

                    if (checkResult == GSP_CONTROL_ACCEPTED) {
                        selectObject(controlObject, currentTime, connection);

                        indication = GSP_DATA_ACCESS_ERROR_SUCCESS;

                        if (DEBUG_IED_SERVER)
                            printf("IED_SERVER: SBOw - selected successful\n");
                    }
                    else {
                        indication = (GspMmsDataAccessError) checkResult;

                        ControlObject_sendLastApplError(controlObject, connection, std::string("SBOw").data(), controlObject->errorValue,
                                controlObject->addCauseValue, ctlNum, origin, true);

                        controlObject->mmsConnection = nullptr;

                        if (DEBUG_IED_SERVER)
                            printf("IED_SERVER: SBOw - select rejected by application!\n");
                    }
                }
            }
            else {
                indication = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
            }
        }
        else {
            indication = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
            return indication;
        }
    }
    else if (strcmp(varName, "Oper") == 0) {
        GspMmsValue* ctlVal = getCtlVal(value);
        GspMmsValue* test = getOperParameterTest(value);
        GspMmsValue* ctlNum = getOperParameterCtlNum(value);
        GspMmsValue* origin = getOperParameterOrigin(value);
        GspMmsValue* check = getOperParameterCheck(value);
        GspMmsValue* timeParameter = getOperParameterTime(value);

        if ((ctlVal == nullptr) || (test == nullptr) || (ctlNum == nullptr) || (origin == nullptr) || (check == nullptr)
                || (timeParameter == nullptr)) {
            indication = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
            return indication;
        }

        if (checkValidityOfOriginParameter(origin) == false) {
            indication = GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;

            if ((controlObject->ctlModel == 2) || (controlObject->ctlModel == 4)) {
                ControlObject_sendLastApplError(controlObject, connection, std::string("Oper").data(),
                        GSP_CONTROL_ERROR_NO_ERROR, GSP_ADD_CAUSE_INCONSISTENT_PARAMETERS,
                            ctlNum, origin, true);

                unselectObject(controlObject);
            }

            return indication;
        }

        uint64_t currentTime = GSP_Hal_getTimeInMs();

        checkSelectTimeout(controlObject, currentTime);

        int state = getState(controlObject);

        if (state == STATE_WAIT_FOR_ACTIVATION_TIME) {
            indication = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;

            ControlObject_sendLastApplError(controlObject, connection, std::string("Oper").data(),
                    GSP_CONTROL_ERROR_NO_ERROR, GSP_ADD_CAUSE_COMMAND_ALREADY_IN_EXECUTION,
                        ctlNum, origin, true);

            return indication;
        }
        else if (state == STATE_READY) {

            bool interlockCheck = GspMmsValue_getBitStringBit(check, 1);
            bool synchroCheck = GspMmsValue_getBitStringBit(check, 0);

            bool testCondition = GspMmsValue_getBoolean(test);

            controlObject->testMode = testCondition;

            if ((controlObject->ctlModel == 2) || (controlObject->ctlModel == 4)) {
                if (controlObject->mmsConnection != connection) {
                    indication = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: Oper - operate from wrong client connection!\n");

                    ControlObject_sendLastApplError(controlObject, connection, std::string("Oper").data(), GSP_CONTROL_ERROR_NO_ERROR,
                            GSP_ADD_CAUSE_LOCKED_BY_OTHER_CLIENT, ctlNum, origin, true);

                    return indication;
                }

                if (controlObject->ctlModel == 4) { /* select-before-operate with enhanced security */
                    if ((GspMmsValue_equals(ctlVal, controlObject->ctlVal) &&
                         GspMmsValue_equals(origin, controlObject->origin) &&
                         GspMmsValue_equals(ctlNum, controlObject->ctlNum) &&
                         (controlObject->interlockCheck == interlockCheck) &&
                         (controlObject->synchroCheck == synchroCheck)
                         ) == false)
                    {

                        indication = GSP_DATA_ACCESS_ERROR_TYPE_INCONSISTENT;
                        ControlObject_sendLastApplError(controlObject, connection, std::string("Oper").data(),
                                GSP_CONTROL_ERROR_NO_ERROR, GSP_ADD_CAUSE_INCONSISTENT_PARAMETERS,
                                    ctlNum, origin, true);

                        unselectObject(controlObject);

                        return indication;
                    }
                }
            }

            updateControlParameters(controlObject, ctlVal, ctlNum, origin, synchroCheck, interlockCheck);

            GspMmsValue* operTm = getOperParameterOperTime(value);

            if (operTm != nullptr) {
                controlObject->operateTime = GspMmsValue_getUtcTimeInMs(operTm);

                if (controlObject->operateTime != 0) {
                    controlObject->timeActivatedOperate = true;
                    controlObject->synchroCheck = synchroCheck;
                    controlObject->interlockCheck = interlockCheck;
                    controlObject->mmsConnection = connection;

                    GspCheckHandlerResult checkResult = GSP_CONTROL_ACCEPTED;
                    if (controlObject->checkHandler != nullptr) { /* perform operative tests */

                        checkResult = controlObject->checkHandler((GspControlAction) controlObject,
                            controlObject->checkHandlerParameter, ctlVal, testCondition, interlockCheck);

                    }

                    if (checkResult == GSP_CONTROL_ACCEPTED) {
                        initiateControlTask(controlObject);

                        setState(controlObject, STATE_WAIT_FOR_ACTIVATION_TIME);

                        if (DEBUG_IED_SERVER)
                            printf("IED_SERVER: Oper - activate time activated control\n");

                        indication = GSP_DATA_ACCESS_ERROR_SUCCESS;
                    }
                    else {
                        indication = (GspMmsDataAccessError) checkResult;
                    }
                }
            }
            else{
                controlObject->operateTime = 0;
            }

            GspMmsValue_update(controlObject->oper, value);

            if (controlObject->timeActivatedOperate == false) {

                GspCheckHandlerResult checkResult = GSP_CONTROL_ACCEPTED;

                /* enter state Perform Test */
                setOpRcvd(controlObject, true);

                controlObject->addCauseValue = GSP_ADD_CAUSE_UNKNOWN;
                controlObject->mmsConnection = connection;

                if (controlObject->checkHandler != nullptr) { /* perform operative tests */

                    checkResult = controlObject->checkHandler((GspControlAction) controlObject,
                            controlObject->checkHandlerParameter, ctlVal, testCondition, interlockCheck);
                }

                if (checkResult == GSP_CONTROL_ACCEPTED) {
                    indication = GSP_DATA_ACCESS_ERROR_NO_RESPONSE;

                    controlObject->mmsConnection = connection;

                    controlObject->operateInvokeId = GspMmsServerConnection_getLastInvokeId(connection);

                    setState(controlObject, STATE_WAIT_FOR_EXECUTION);

                    /* leave state Perform Test */
                    setOpRcvd(controlObject, false);

                    initiateControlTask(controlObject);
                }
                else {
                    indication = (GspMmsDataAccessError) checkResult;

                    /* leave state Perform Test */
                    setOpRcvd(controlObject, false);

                    abortControlOperation(controlObject);

                    if ((controlObject->ctlModel == 2) || (controlObject->ctlModel == 4))
                        unselectObject(controlObject);
                }
            }

        }
        else if (state == STATE_UNSELECTED) {
            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Oper failed - control not selected!\n");

            indication = GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
            ControlObject_sendLastApplError(controlObject, connection, std::string("Oper").data(),
                    GSP_CONTROL_ERROR_NO_ERROR, GSP_ADD_CAUSE_OBJECT_NOT_SELECTED,
                        ctlNum, origin, true);

            return indication;
        }
        else if ((state == STATE_OPERATE) || (state == STATE_WAIT_FOR_EXECUTION)) {
            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Oper failed - control already being executed!\n");

            indication = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;

            ControlObject_sendLastApplError(controlObject, connection, std::string("Oper").data(),
                    GSP_CONTROL_ERROR_NO_ERROR, GSP_ADD_CAUSE_COMMAND_ALREADY_IN_EXECUTION,
                    ctlNum, origin, true);

            return indication;
        }
    }
    else if (strcmp(varName, "Cancel") == 0) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: control received cancel!\n");

        int state = getState(controlObject);

        GspMmsValue* ctlNum = getCancelParameterCtlNum(value);
        GspMmsValue* origin = getCancelParameterOrigin(value);

        if ((ctlNum == nullptr) || (origin == nullptr)) {
            indication = GSP_DATA_ACCESS_ERROR_TYPE_INCONSISTENT;
            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Invalid cancel message!\n");
            return indication;
        }

        if ((controlObject->ctlModel == 2) || (controlObject->ctlModel == 4)) {
            if (state != STATE_UNSELECTED) {
                if (controlObject->mmsConnection == connection) {
                    indication = GSP_DATA_ACCESS_ERROR_SUCCESS;
                    unselectObject(controlObject);
                    return indication;
                }
                else {
                    indication = GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
                    ControlObject_sendLastApplError(controlObject, connection, std::string("Cancel").data(),
                            GSP_CONTROL_ERROR_NO_ERROR, GSP_ADD_CAUSE_LOCKED_BY_OTHER_CLIENT,
                                ctlNum, origin, true);
                }
            }
            else {
                indication = GSP_DATA_ACCESS_ERROR_SUCCESS;
            }
        }

        if (controlObject->timeActivatedOperate) {
            controlObject->timeActivatedOperate = false;
            abortControlOperation(controlObject);

            indication = GSP_DATA_ACCESS_ERROR_SUCCESS;

            return indication;
        }
    }
    return indication;
}

void
GspControlAction_setError(GspControlAction self, GspControlLastApplError error)
{
    GspControlObject* controlObject = (GspControlObject*) self;

    controlObject->errorValue = error;
}

void
GspControlAction_setAddCause(GspControlAction self, GspControlAddCause addCause)
{
    GspControlObject* controlObject = (GspControlObject*) self;

    controlObject->addCauseValue = addCause;
}

int
GspControlAction_getOrCat(GspControlAction self)
{
    GspControlObject* controlObject = (GspControlObject*) self;

    if (controlObject->origin) {
        GspMmsValue* orCat = GspMmsValue_getElement(controlObject->origin, 0);

        if (orCat) {
            return GspMmsValue_toInt32(orCat);
        }
    }

    return 0;
}

uint8_t*
GspControlAction_getOrIdent(GspControlAction self, int* orIdentSize)
{
    GspControlObject* controlObject = (GspControlObject*) self;

    if (controlObject->origin) {
        GspMmsValue* orIdent = GspMmsValue_getElement(controlObject->origin, 1);

        if (orIdent) {
            if (GspMmsValue_getType(orIdent) == Data_PR_octet_string) {
                *orIdentSize  = GspMmsValue_getOctetStringSize(orIdent);
                return GspMmsValue_getOctetStringBuffer(orIdent);
            }
        }
    }

    return nullptr;
}

int
GspControlAction_getCtlNum(GspControlAction self)
{
    GspControlObject* controlObject = (GspControlObject*) self;

    if (controlObject->ctlNum) {
        return GspMmsValue_toInt32(controlObject->ctlNum);
    }

    return -1;
}

bool
GspControlAction_isSelect(GspControlAction self)
{
    GspControlObject* controlObject = (GspControlObject*) self;

    if (controlObject->isSelect)
        return true;
    else
        return false;
}

GspClientConnection
GspControlAction_getClientConnection(GspControlAction self)
{
    GspControlObject* controlObject = (GspControlObject*) self;

    return Gsp_private_IedServer_getClientConnectionByHandle(controlObject->iedServer, controlObject->mmsConnection);
}

GspDataObject*
GspControlAction_getControlObject(GspControlAction self)
{
    GspControlObject* controlObject = (GspControlObject*) self;

    return controlObject->dataObject;
}

uint64_t
GspControlAction_getControlTime(GspControlAction self)
{
    GspControlObject* controlObject = (GspControlObject*) self;

    return controlObject->operateTime;
}

#endif /* (CONFIG_DLT860_CONTROL_SERVICE == 1) */

