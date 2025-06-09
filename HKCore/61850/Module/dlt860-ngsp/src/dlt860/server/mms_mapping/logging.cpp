/*
 *  logging.c
 */

#include "libdlt860_platform_includes.h"
#include "stack_config.h"
#include "mms_mapping.h"
#include "logging.h"
#include "gsp_linked_list.h"
#include "gsp_hal_thread.h"

#include "simple_allocator.h"

#include "mms_mapping_internal.h"

#include "logging_api.h"

#if (CONFIG_DLT860_LOG_SERVICE == 1)

GspLogInstance*
GspLogInstance_create(GspLogicalNode* parentLN, const char* name)
{
    GspLogInstance* self = (GspLogInstance*) GLOBAL_MALLOC(sizeof(GspLogInstance));

    self->name = StringUtils_copyString(name);
    self->parentLN = parentLN;
    self->logStorage = NULL;
    self->locked = false;

    self->oldEntryId = 0;
    self->oldEntryTime = 0;
    self->newEntryId = 0;
    self->newEntryTime = 0;

    return self;
}

void
GspLogInstance_destroy(GspLogInstance* self)
{
    GLOBAL_FREEMEM(self->name);
    GLOBAL_FREEMEM(self);
}

void
GspLogInstance_logSingleData(GspLogInstance* self, const char* dataRef, GspMmsValue* value, uint8_t flag)
{
    GspLogStorage logStorage = self->logStorage;

    if (logStorage != NULL) {

        while (self->locked)
            GspThread_sleep(1);

        self->locked = true;

        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Log value - dataRef: %s flag: %i\n", dataRef, flag);

        uint64_t timestamp = GSP_Hal_getTimeInMs();

        uint64_t entryID = GspLogStorage_addEntry(logStorage, timestamp);

        uint8_t* data = nullptr;
        int dataSize = aper_encode_to_new_buffer(&asn_DEF_Data, nullptr, value, (void **)&data);

        GspLogStorage_addEntryData(logStorage, entryID, dataRef, data, dataSize, flag);

        self->locked = false;

        GLOBAL_FREEMEM(data);

        self->newEntryId = entryID;
        self->newEntryTime = timestamp;

    }
    else
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: no log storage available for logging!\n");
}

uint64_t
GspLogInstance_logEntryStart(GspLogInstance* self)
{
    GspLogStorage logStorage = self->logStorage;

    if (logStorage != NULL) {

        while (self->locked)
            GspThread_sleep(1);

        self->locked = true;

        uint64_t timestamp = GSP_Hal_getTimeInMs();

        uint64_t entryID = GspLogStorage_addEntry(logStorage, timestamp);

        return entryID;
    }
    else {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: no log storage available for logging!\n");

        return 0;
    }
}

void
GspLogInstance_logEntryData(GspLogInstance* self, uint64_t entryID, const char* dataRef, GspMmsValue* value, uint8_t flag)
{
    GspLogStorage logStorage = self->logStorage;

    if (logStorage != NULL) {

        uint8_t* data = nullptr;
        int dataSize = aper_encode_to_new_buffer(&asn_DEF_Data, nullptr, value, (void **)&data);
        
        GspLogStorage_addEntryData(logStorage, entryID, dataRef, data, dataSize, flag);

        self->locked = false;

        GLOBAL_FREEMEM(data);
    }
}

void
GspLogInstance_logEntryFinished(GspLogInstance* self, uint64_t entryID)
{
    self->locked = false;
}

void
GspLogInstance_setGspLogStorage(GspLogInstance* self, GspLogStorage logStorage)
{
    self->logStorage = logStorage;

    GspLogStorage_getOldestAndNewestEntries(logStorage, &(self->newEntryId), &(self->newEntryTime),
            &(self->oldEntryId), &(self->oldEntryTime));
}

GspLogControl*
GspLogControl_create(GspLogicalNode* parentLN, GspMmsMapping* mmsMapping)
{
    GspLogControl* self = (GspLogControl*) GLOBAL_MALLOC(sizeof(GspLogControl));

    self->enabled = false;
    self->dataSet = NULL;
    self->isDynamicDataSet = false;
    self->triggerOps = 0;
    self->logicalNode = parentLN;
    self->mmsMapping = mmsMapping;
    self->dataSetRef = NULL;
    self->logInstance = NULL;
    self->intgPd = 0;
    self->nextIntegrityScan = 0;

    return self;
}

void
GspLogControl_destroy(GspLogControl* self)
{
    if (self != NULL) {

        GspMmsValue_delete(self->mmsValue);
        GLOBAL_FREEMEM(self->name);

        if (self->dataSetRef != NULL)
            GLOBAL_FREEMEM(self->dataSetRef);

        GLOBAL_FREEMEM(self);
    }
}

void
GspLogControl_setLog(GspLogControl* self, GspLogInstance* logInstance)
{
    self->logInstance = logInstance;
}

static void
prepareGspLogControl(GspLogControl* logControl)
{
    if (logControl->dataSetRef == NULL) {
        logControl->enabled = false;
        return;
    }

    GspDataSet* dataSet = GspIedModel_lookupDataSet(logControl->mmsMapping->model, logControl->dataSetRef);

    if (dataSet == NULL)
        return;
    else
        logControl->dataSet = dataSet;
}

static bool
enableLogging(GspLogControl* self)
{
    if ((self->dataSet != NULL) && (self->logInstance != NULL)) {
        self->enabled = true;

        if ((self->triggerOps & GSP_TRG_OPT_INTEGRITY) && (self->intgPd != 0))
            self->nextIntegrityScan = GSP_Hal_getTimeInMs();
        else
            self->nextIntegrityScan = 0;

        GspMmsValue* enabled = GspMmsValue_getSubElement(self->mmsValue, self->mmsType, std::string("LogEna").data());

        GspMmsValue_setBoolean(enabled, true);

        return true;
    }
    else
        return false;
}

static GspLogControlBlock*
getLCBForGspLogicalNodeWithIndex(GspMmsMapping* self, GspLogicalNode* logicalNode, int index)
{
    int lcbCount = 0;

    GspLogControlBlock* nextLcb = self->model->lcbs;

    while (nextLcb != NULL ) {
        if (nextLcb->parent == logicalNode) {

            if (lcbCount == index)
                return nextLcb;

            lcbCount++;

        }

        nextLcb = nextLcb->sibling;
    }

    return NULL ;
}

GspLogControl*
lookupGspLogControl(GspMmsMapping* self, GspMmsDomain* domain, char* lnName, char* objectName)
{
    for(auto &&element : *self->logControls)
    {
        auto *logControl = (GspLogControl*)element;
        if (logControl->domain == domain) {
            if (strcmp(logControl->logicalNode->name, lnName) == 0) {
                if (strcmp(logControl->logControlBlock->name, objectName) == 0) {
                    return logControl;
                }
            }
        }
    }

    return NULL;
}

GspLogInstance*
getGspLogInstanceByLogRef(GspMmsMapping* self, const char* logRef)
{
    char refStr[130];
    char ld_domianName[64];
    char* domainName;
    char* lnName;
    char* logName;

    strncpy(refStr, logRef, 129);

    domainName = refStr;

    lnName = strchr(refStr, '/');

    if (lnName == NULL)
        return NULL;

    if ((lnName - domainName) > 64)
        return NULL;

    lnName[0] = 0;
    lnName++;

    //logName = strchr(lnName, '$');
    logName = strchr(lnName, '.');

    if (logName == NULL)
        return NULL;

    logName[0] = 0;
    logName++;


    for(auto &&instance : *self->logInstances) {
        GspLogInstance* logInstance = (GspLogInstance*) instance;

        if (strcmp(logInstance->name, logName) == 0 || strcmp(logInstance->name, "GeneralLog") == 0) {

            if (strcmp(lnName, logInstance->parentLN->name) == 0) {
                GspLogicalDevice* ld = (GspLogicalDevice*) logInstance->parentLN->parent;
                snprintf(ld_domianName, 63, "%s%s", ld->iedName, ld->name);
                if (strcmp(ld_domianName, domainName) == 0)
                //if (strcmp(ld->name, domainName) == 0)
                    return logInstance;
            }
        }
    }
    return NULL;
}

static void
updateLogStatusInLCB(GspLogControl* self)
{
    GspLogInstance* logInstance = self->logInstance;

    if (logInstance != NULL) {
        GspMmsValue_setBinaryTime(self->oldEntrTm, logInstance->oldEntryTime);
        GspMmsValue_setBinaryTime(self->newEntrTm, logInstance->newEntryTime);

        GspMmsValue_setOctetString(self->oldEntr, (uint8_t*) &(logInstance->oldEntryId), 8);
        GspMmsValue_setOctetString(self->newEntr, (uint8_t*) &(logInstance->newEntryId), 8);
    }
}


static void
freeDynamicDataSet(GspLogControl* self)
{
    if (self->isDynamicDataSet) {
        if (self->dataSet != NULL) {
            GspMmsMapping_freeDynamicallyCreatedDataSet(self->dataSet);
            self->isDynamicDataSet = false;
            self->dataSet = NULL;
        }
    }
}

GspMmsDataAccessError
Gsp_LOG_SVC_writeAccessLogControlBlock(GspMmsMapping* self, GspMmsDomain* domain, char* variableIdOrig,
        GspMmsValue* value, GspMmsServerConnection connection)
{
    bool updateValue = false;

    char variableId[130];

    strncpy(variableId, variableIdOrig, 129);

    char* separator = strchr(variableId, '$');

    *separator = 0;

    char* lnName = variableId;

    if (lnName == NULL)
        return GSP_DATA_ACCESS_ERROR_INVALID_ADDRESS;

    char* objectName = GspMmsMapping_getNextNameElement(separator + 1);

    if (objectName == NULL)
        return GSP_DATA_ACCESS_ERROR_INVALID_ADDRESS;

    char* varName = GspMmsMapping_getNextNameElement(objectName);

    if (varName != NULL)
        *(varName - 1) = 0;

    GspLogControl* logControl = lookupGspLogControl(self, domain, lnName, objectName);

    if (logControl == NULL) {
        return GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT;
    }

    if (strcmp(varName, "LogEna") == 0) {
        bool logEna = GspMmsValue_getBoolean(value);

        if (logEna == false) {
            logControl->enabled = false;
        }
        else {

            if (enableLogging(logControl)) {
                logControl->enabled = true;

                if (DEBUG_IED_SERVER)
                    printf("IED_SERVER: enabled log control %s\n", logControl->name);
            }
            else
                return GSP_DATA_ACCESS_ERROR_OBJECT_ATTRIBUTE_INCONSISTENT;
        }

       updateValue = true;
    }
    else if (strcmp(varName, "LogRef") == 0) {

        if (logControl->enabled == false) {
            /* check if logRef is valid or NULL */
            const char* logRef = GspMmsValue_toString(value);

            if (logRef == NULL) {

                logControl->logInstance = NULL;

                updateValue = true;
            }
            else {
               if (strcmp(logRef, "") == 0) {
                   logControl->logInstance = NULL;
                   updateValue = true;
               }
               else {

                   /* remove IED name from logRef */
                   char* iedName = self->mmsDevice->deviceName;

                   uint32_t iedNameLen = strlen(iedName);

                   if (iedNameLen < strlen(logRef)) {
                       if (memcmp(iedName, logRef, iedNameLen) == 0) {
                           logRef = logRef + iedNameLen;
                       }
                   }

                   GspLogInstance* logInstance = getGspLogInstanceByLogRef(self, logRef);

                   if (logInstance != NULL) {

                       logControl->logInstance = logInstance;
                       updateValue = true;
                   }
                   else
                       return GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;

               }
            }
        }
        else
            return GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
    }
    else if (strcmp(varName, "DatSet") == 0) {

        if (logControl->enabled == false) {
             /* check if datSet is valid or NULL/empty */
            const char* dataSetRef = GspMmsValue_toString(value);

            if (strlen(dataSetRef) == 0) {
                logControl->dataSet = NULL;
                updateValue = true;
            }
            else {
                GspDataSet* dataSet = GspIedModel_lookupDataSet(logControl->mmsMapping->model, dataSetRef);

                if (dataSet != NULL) {
                    freeDynamicDataSet(logControl);

                    logControl->dataSet = dataSet;
                    updateValue = true;

                }

#if (MMS_DYNAMIC_DATA_SETS == 1)

                if (dataSet == NULL) {

                    dataSet = GspMmsMapping_getDomainSpecificDataSet(self, dataSetRef);

                    if (dataSet == NULL) {

                        if (dataSetRef[0] == '/') { /* check for VMD specific data set */
                            GspMmsNamedVariableList mmsVariableList =
                                    GspMmsDevice_getNamedVariableListWithName(self->mmsDevice, dataSetRef + 1);

                            if (mmsVariableList != NULL)
                                dataSet = GspMmsMapping_createDataSetByNamedVariableList(self, mmsVariableList);
                        }
                    }

                    if (dataSet != NULL) {
                        freeDynamicDataSet(logControl);
                        logControl->dataSet = dataSet;
                        logControl->isDynamicDataSet = true;

                        updateValue = true;
                    }

                }

#endif /*(MMS_DYNAMIC_DATA_SETS == 1) */

                if (dataSet == NULL) {
                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER:   data set (%s) not found!\n", logControl->dataSetRef);
                    return GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID;
                }
            }


        }
        else
            return GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
    }
    else if (strcmp(varName, "IntgPd") == 0) {
        if (logControl->enabled == false) {
            logControl->intgPd = GspMmsValue_toUint32(value);
            updateValue = true;
        }
        else
            return GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
    }
    else if (strcmp(varName, "TrgOps") == 0) {
        if (logControl->enabled == false) {
            logControl->triggerOps = (GspMmsValue_getBitStringAsInteger(value) / 2);
            updateValue = true;
        }
        else
            return GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE;
    }

    if (updateValue) {
        GspMmsValue* element = GspMmsValue_getSubElement(logControl->mmsValue, logControl->mmsType, varName);

        GspMmsValue_update(element, value);

        return GSP_DATA_ACCESS_ERROR_SUCCESS;
    }

    return GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED;
}

GspMmsValue*
LIBIEC61850_LOG_SVC_readAccessControlBlock(GspMmsMapping* self, GspMmsDomain* domain, char* variableIdOrig)
{
    GspMmsValue* value = NULL;

    char variableId[130];

    strncpy(variableId, variableIdOrig, 129);

    char* separator = strchr(variableId, '$');

    *separator = 0;

    char* lnName = variableId;

    if (lnName == NULL)
        return NULL;

    char* objectName = GspMmsMapping_getNextNameElement(separator + 1);

    if (objectName == NULL)
        return NULL;

    char* varName = GspMmsMapping_getNextNameElement(objectName);

    if (varName != NULL)
        *(varName - 1) = 0;

    GspLogControl* logControl = lookupGspLogControl(self, domain, lnName, objectName);

    if (logControl != NULL) {

        updateLogStatusInLCB(logControl);

        if (varName != NULL) {
            value = GspMmsValue_getSubElement(logControl->mmsValue, logControl->mmsType, varName);
        }
        else {
            value = logControl->mmsValue;
        }
    }

    return value;
}


static char*
createDataSetReferenceForDefaultDataSet(GspLogControlBlock* lcb, GspLogControl* logControl)
{
    char* dataSetReference;

    char* domainName = logControl->domain->domainName;
    char* lnName = lcb->parent->name;

    dataSetReference = StringUtils_createString(5, domainName, "/", lnName, "$", lcb->dataSetName);

    return dataSetReference;
}

static GspMmsValue*
createTrgOps(GspLogControlBlock* logControlBlock) {
    GspMmsValue* trgOps = GspMmsValue_newBitString(-6);

    uint8_t triggerOps = logControlBlock->trgOps;

    if (triggerOps & GSP_TRG_OPT_DATA_CHANGED)
        GspMmsValue_setBitStringBit(trgOps, 1, true);
    if (triggerOps & GSP_TRG_OPT_QUALITY_CHANGED)
        GspMmsValue_setBitStringBit(trgOps, 2, true);
    if (triggerOps & GSP_TRG_OPT_DATA_UPDATE)
        GspMmsValue_setBitStringBit(trgOps, 3, true);
    if (triggerOps & GSP_TRG_OPT_INTEGRITY)
        GspMmsValue_setBitStringBit(trgOps, 4, true);

    return trgOps;
}

static void
GspLogControl_updateLogEna(GspLogControl* self)
{
    GspMmsValue_setBoolean(GspMmsValue_getElement(self->mmsValue, 0), self->enabled);
}

static GspMmsVariableSpecification*
createGspLogControlBlock(GspMmsMapping* self, GspLogControlBlock* logControlBlock,
        GspLogControl* logControl)
{
    GspMmsVariableSpecification* lcb = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    lcb->name = StringUtils_copyString(logControlBlock->name);
    lcb->type = GSP_MMS_STRUCTURE;

    GspMmsValue* mmsValue = GspMmsValue_createEmptyStructure(9);

    int structSize = 9;

    // mmsValue->value.structure.components = (GspMmsValue**) GLOBAL_CALLOC(structSize, sizeof(GspMmsValue*));

    lcb->typeSpec.structure.elementCount = structSize;

    lcb->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(structSize,
            sizeof(GspMmsVariableSpecification*));

    /* LogEna */
    GspMmsVariableSpecification* namedVariable =
            (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));

    namedVariable->name = StringUtils_copyString("LogEna");
    namedVariable->type = GSP_MMS_BOOLEAN;

    lcb->typeSpec.structure.elements[0] = namedVariable;
    mmsValue->choice.structure.list.array[0] = GspMmsValue_newBoolean(logControlBlock->logEna);

    /* LogRef */
    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("LogRef");
    namedVariable->typeSpec.visibleString = -129;
    namedVariable->type = GSP_MMS_VISIBLE_STRING;
    lcb->typeSpec.structure.elements[1] = namedVariable;

    if (logControlBlock->logRef != NULL) {
        char logRef[130];

        int maxLogRefLength = 129 - strlen(self->model->name);

        strcpy(logRef, self->model->name);
        strncat(logRef, logControlBlock->logRef, maxLogRefLength);

        mmsValue->choice.structure.list.array[1] = GspMmsValue_newVisibleString(logRef);
    }
    else {
        char* logRef = StringUtils_createString(4, logControl->domain->domainName, "/", logControlBlock->parent->name,
                ".GeneralLog");

        mmsValue->choice.structure.list.array[1] = GspMmsValue_newVisibleString(logRef);

        GLOBAL_FREEMEM(logRef);
    }

    /* DatSet */
    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("DatSet");
    namedVariable->typeSpec.visibleString = -129;
    namedVariable->type = GSP_MMS_VISIBLE_STRING;
    lcb->typeSpec.structure.elements[2] = namedVariable;

    if (logControlBlock->dataSetName != NULL) {
        char* dataSetReference = createDataSetReferenceForDefaultDataSet(logControlBlock, logControl);

        logControl->dataSetRef = dataSetReference;
        mmsValue->choice.structure.list.array[2] = GspMmsValue_newVisibleString(dataSetReference);
    }
    else
        mmsValue->choice.structure.list.array[2] = GspMmsValue_newVisibleString("");

    /* OldEntrTm */
    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("OldEntrTm");
    namedVariable->type = GSP_MMS_BINARY_TIME;
    namedVariable->typeSpec.binaryTime = 6;
    lcb->typeSpec.structure.elements[3] = namedVariable;

    mmsValue->choice.structure.list.array[3] = GspMmsValue_newBinaryTime(false);

    logControl->oldEntrTm = mmsValue->choice.structure.list.array[3];

    /* NewEntrTm */
    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("NewEntrTm");
    namedVariable->type = GSP_MMS_BINARY_TIME;
    namedVariable->typeSpec.binaryTime = 6;
    lcb->typeSpec.structure.elements[4] = namedVariable;

    mmsValue->choice.structure.list.array[4] = GspMmsValue_newBinaryTime(false);

    logControl->newEntrTm = mmsValue->choice.structure.list.array[4];

    /* OldEntr */
    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("OldEntr");
    namedVariable->type = GSP_MMS_OCTET_STRING;
    namedVariable->typeSpec.octetString = 8;

    lcb->typeSpec.structure.elements[5] = namedVariable;

    mmsValue->choice.structure.list.array[5] = GspMmsValue_newOctetString(8, 8);

    logControl->oldEntr = mmsValue->choice.structure.list.array[5];

    /* NewEntr */
    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("NewEntr");
    namedVariable->type = GSP_MMS_OCTET_STRING;
    namedVariable->typeSpec.octetString = 8;

    lcb->typeSpec.structure.elements[6] = namedVariable;

    mmsValue->choice.structure.list.array[6] = GspMmsValue_newOctetString(8, 8);

    logControl->newEntr = mmsValue->choice.structure.list.array[6];

    /* TrgOps */
    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("TrgOps");
    namedVariable->type = GSP_MMS_BIT_STRING;
    namedVariable->typeSpec.bitString = -6;
    lcb->typeSpec.structure.elements[7] = namedVariable;
    mmsValue->choice.structure.list.array[7] = createTrgOps(logControlBlock);

    /* IntgPd */
    namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1, sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("IntgPd");
    namedVariable->type = GSP_MMS_UINT32;
    lcb->typeSpec.structure.elements[8] = namedVariable;
    mmsValue->choice.structure.list.array[8] =
            GspMmsValue_newUnsignedFromUint32(logControlBlock->intPeriod);

    logControl->intgPd = logControlBlock->intPeriod;

    logControl->mmsType = lcb;
    logControl->mmsValue = mmsValue;
    logControl->logControlBlock = logControlBlock;
    logControl->triggerOps = logControlBlock->trgOps;

    logControl->enabled = logControlBlock->logEna;

    prepareGspLogControl(logControl);

    return lcb;
}

GspMmsVariableSpecification*
GspLogging_createLCBs(GspMmsMapping* self, GspMmsDomain* domain, GspLogicalNode* logicalNode,
        int lcbCount)
{
    GspMmsVariableSpecification* namedVariable = (GspMmsVariableSpecification*) GLOBAL_CALLOC(1,
            sizeof(GspMmsVariableSpecification));
    namedVariable->name = StringUtils_copyString("LG");
    namedVariable->type = GSP_MMS_STRUCTURE;

    namedVariable->typeSpec.structure.elementCount = lcbCount;
    namedVariable->typeSpec.structure.elements = (GspMmsVariableSpecification**) GLOBAL_CALLOC(lcbCount,
            sizeof(GspMmsVariableSpecification*));

    int currentLcb = 0;

    while (currentLcb < lcbCount) {

        GspLogControl* logControl = GspLogControl_create(logicalNode, self);

        GspLogControlBlock* logControlBlock = getLCBForGspLogicalNodeWithIndex(self, logicalNode, currentLcb);

        logControl->name = StringUtils_createString(3, logicalNode->name, "$LG$", logControlBlock->name);
        logControl->domain = domain;

        namedVariable->typeSpec.structure.elements[currentLcb] =
                createGspLogControlBlock(self, logControlBlock, logControl);

        if (logControlBlock->logRef != NULL)
            logControl->logInstance = getGspLogInstanceByLogRef(self, logControlBlock->logRef);

        if (logControl->enabled)
            enableLogging(logControl);

        GspLogControl_updateLogEna(logControl);

        GspLinkedList_add(self->logControls, logControl);

        currentLcb++;
    }

    return namedVariable;
}

static void
GspLogControl_logAllDatasetEntries(GspLogControl* self, const char* iedName)
{
    if (self->dataSet == NULL)
        return;

    if (self->logInstance != NULL) {

        char dataRef[130];

        GspLogInstance* log = self->logInstance;

        uint64_t entryID = GspLogInstance_logEntryStart(log);

        GspDataSetEntry* dataSetEntry = self->dataSet->fcdas;

        while (dataSetEntry != NULL) {

            sprintf(dataRef, "%s%s/%s", iedName, dataSetEntry->logicalDeviceName, dataSetEntry->variableName);

            GspLogInstance_logEntryData(log, entryID, dataRef, dataSetEntry->value, GSP_TRG_OPT_INTEGRITY * 2);

            dataSetEntry = dataSetEntry->sibling;
        }

        GspLogInstance_logEntryFinished(log, entryID);

    }
}

void
GspLogging_processIntegrityLogs(GspMmsMapping* self, uint64_t currentTimeInMs)
{
    for(auto &&logControlElem : *self->logControls) {

        GspLogControl* logControl = (GspLogControl*) logControlElem;

        if (logControl->enabled) {

            if (logControl->nextIntegrityScan != 0) {

                if (currentTimeInMs >= logControl->nextIntegrityScan) {

                    if (DEBUG_IED_SERVER)
                        printf("IED_SERVER: INTEGRITY SCAN for log %s\n", logControl->name);

                    GspLogControl_logAllDatasetEntries(logControl, self->mmsDevice->deviceName);

                    logControl->nextIntegrityScan += logControl->intgPd;
                }
            }
        }
    }
}

void
GspMmsMapping_setGspLogStorage(GspMmsMapping* self, const char* logRef, GspLogStorage logStorage)
{
    GspLogInstance* logInstance = getGspLogInstanceByLogRef(self, logRef);

    if (logInstance != NULL) {
        GspLogInstance_setGspLogStorage(logInstance, logStorage);

        char domainName[65];

        GspMmsMapping_getMmsDomainFromObjectReference(logRef, domainName);

        char domainNameWithIEDName[65];

        strcpy(domainNameWithIEDName, self->model->name);
        strcat(domainNameWithIEDName, domainName);

        GspMmsDomain* mmsDomain = GspMmsDevice_getDomain(self->mmsDevice, domainNameWithIEDName);

        if (mmsDomain == NULL) {
            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: GspMmsMapping_setGspLogStorage: domain %s not found!\n", domainNameWithIEDName);

            return;
        }

        GspMmsJournal mmsJournal = NULL;

        const char* logName = strchr(logRef, '/');

        if (logName != NULL) {
            logName += 1;
            mmsJournal = GspMmsDomain_getJournal(mmsDomain, logName);
        }

        if (mmsJournal != NULL)
            mmsJournal->logStorage = logStorage;
        else
            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Failed to retrieve MMS journal for log!\n");
    }

    if (DEBUG_IED_SERVER)
        if (logInstance == NULL)
            printf("IED_SERVER: GspMmsMapping_setGspLogStorage no matching log for %s found!\n", logRef);
}


GspMmsValue* Gsp_LOG_SVC_readAccessControlBlock(GspMmsMapping* self, GspMmsDomain* domain, char* variableIdOrig)
{
    return nullptr;
}


#endif /* (CONFIG_DLT860_LOG_SERVICE == 1) */

