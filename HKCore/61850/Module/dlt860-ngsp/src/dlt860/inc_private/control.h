/*
 *  control.h
 */

#ifndef GSP_CONTROL_H_
#define GSP_CONTROL_H_

#include "dlt860_model.h"
#include "dlt860_server.h"
#include "mms_server_connection.h"
#include "mms_server_libinternal.h"
#include "mms_device_model.h"
#include "mms_mapping_internal.h"
#include "gsp_mms_client_connection.h"
#include "libdlt860_platform_includes.h"
#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
typedef struct sGspControlObject GspControlObject;

struct sGspControlObject
{
    GspMmsDomain* mmsDomain;
    GspIedServer iedServer;
    char* lnName;
    char* name;
    unsigned state:4;
    unsigned ctlModel:4;
    unsigned pendingEvents:8;
    unsigned testMode:1;
    unsigned interlockCheck:1;
    unsigned synchroCheck:1;
    unsigned timeActivatedOperate:1;
    unsigned operateOnce:1;
    unsigned isSelect:1;
    GspControlAddCause addCauseValue:6;
    unsigned errorValue:2;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore stateLock;
    GspSemaphore pendingEventsLock;
#endif

    GspMmsValue* mmsValue;
    GspMmsVariableSpecification* typeSpec;
    GspMmsValue* oper;
    GspMmsValue* sbo;
    GspMmsValue* sbow;
    GspMmsValue* cancel;
    GspMmsValue* ctlVal;
    GspMmsValue* ctlNum;
    GspMmsValue* origin;
    GspMmsValue* timestamp;
    GspMmsValue* ctlNumSt;
    GspMmsValue* originSt;

    /* for automatic update of stSeld attribute */
    GspDataAttribute* stSeld;

    /* for automatic update of opRcvd attribute */
    GspDataAttribute* opRcvd;

    /* for automatic update of opOk attribute */
    GspDataAttribute* opOk;

    /* for automatic update of tOpOk attribute */
    GspDataAttribute* tOpOk;

    /* for LastAppIError */
    GspMmsValue* error;
    GspMmsValue* addCause;

    uint64_t selectTime;
    uint32_t selectTimeout;
    GspMmsValue* sboClass;
    GspMmsValue* sboTimeout;

    uint64_t operateTime;

    GspMmsServerConnection mmsConnection;

    uint32_t operateInvokeId;

    GspControlHandler operateHandler;
    void* operateHandlerParameter;

    GspControlPerformCheckHandler checkHandler;
    void* checkHandlerParameter;

    GspControlWaitForExecutionHandler waitForExecutionHandler;
    void* waitForExecutionHandlerParameter;

    GspDataObject* dataObject;
};

// LIB860_INTERNAL GspControlObject* GspControlObject_create(GspIedServer iedServer, GspMmsDomain* domain, char* lnName, char* name, GspMmsVariableSpecification* operSpec);

// LIB860_INTERNAL void GspControlObject_initialize(GspControlObject* self);

// LIB860_INTERNAL void GspControlObject_destroy(GspControlObject* self);

// LIB860_INTERNAL void GspControlObject_setMmsValue(GspControlObject* self, GspMmsValue* value);

// LIB860_INTERNAL GspMmsValue* GspControlObject_getMmsValue(GspControlObject* self);

// LIB860_INTERNAL void GspControlObject_setTypeSpec(GspControlObject* self, GspMmsVariableSpecification* typeSpec);

// LIB860_INTERNAL GspMmsVariableSpecification* GspControlObject_getTypeSpec(GspControlObject* self);

// LIB860_INTERNAL char* GspControlObject_getName(GspControlObject* self);

// LIB860_INTERNAL char* GspControlObject_getLNName(GspControlObject* self);

// LIB860_INTERNAL GspMmsDomain* GspControlObject_getDomain(GspControlObject* self);

// LIB860_INTERNAL bool GspControlObject_select(GspControlObject* self, GspMmsServerConnection connection);

// LIB860_INTERNAL bool GspControlObject_unselect(GspControlObject* self, GspMmsServerConnection connection);

// LIB860_INTERNAL void GspControlObject_installListener(GspControlObject* self, GspControlHandler listener, void* parameter);

// LIB860_INTERNAL void GspControlObject_installCheckHandler(GspControlObject* self, GspControlPerformCheckHandler handler, void* parameter);

// LIB860_INTERNAL void GspControlObject_installWaitForExecutionHandler(GspControlObject* self, GspControlWaitForExecutionHandler handler, void* parameter);

// LIB860_INTERNAL void GspControlObject_updateControlModel(GspControlObject* self, GspControlModel value, GspDataObject* ctlObject);
#endif

#endif /* GSP_CONTROL_H_ */
