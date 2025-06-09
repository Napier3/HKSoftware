/*
 *  iec61850_server.h
 */

#ifndef GSP_IED_SERVER_API_H_
#define GSP_IED_SERVER_API_H_

#include "gsp_mms_server.h"
#include "dlt860_dynamic_model.h"
#include "dlt860_model.h"
#include "dlt860_server_interface.h"

/**
 * \brief Configuration object to configure IEC 61850 stack features
 */
typedef struct sGspIedServerConfig* GspIedServerConfig;

struct sGspIedServerConfig
{
    /** size of the report buffer associated with a buffered report control block */
    int reportBufferSize;

    /** size of the report buffer associated with an unbuffered report control block */
    int reportBufferSizeURCBs;

    /** Base path (directory where the file service serves files */
    string fileServiceBasepath;

    /** when true (default) enable MMS file service */
    bool enableFileService;

    /** when true (default) enable dynamic data set services for MMS */
    bool enableDynamicDataSetService;

    /** the maximum number of allowed association specific data sets */
    int maxAssociationSpecificDataSets;

    /** the maximum number of allowed domain specific data sets */
    int maxDomainSpecificDataSets;

    /** maximum number of data set entries of dynamic data sets */
    int maxDataSetEntries;

    /** when true (default) enable log service */
    bool enableLogService;

    /** IEC 61850 edition (0 = edition 1, 1 = edition 2, 2 = edition 2.1, ...) */
    uint8_t edition;

    /** maximum number of MMS (TCP) connections */
    int maxMmsConnections;

    string logStoragePath;
};

LIB860_API GspIedServerConfig GspIedServerConfig_create();

LIB860_API void GspIedServerConfig_destroy(GspIedServerConfig config);

LIB860_API GspIedServer GspIedServer_create(GspIedModel* dataModel);

LIB860_API GspIedServer GspIedServer_createMulti(GspIedModel **dataModel, GspIedServerConfig config);

LIB860_API GspIedServer GspIedServer_createWithTlsSupport(GspIedModel* dataModel, GspTLSConfiguration tlsConfiguration);

LIB860_API GspIedServer GspIedServer_createWithConfig(GspIedModel* dataModel, GspTLSConfiguration tlsConfiguration, GspIedServerConfig serverConfiguration);

LIB860_API GspIedServer GspIedServer_createWithConfigMulti(GspIedModel** dataModel, GspTLSConfiguration tlsConfiguration, GspIedServerConfig serverConfiguration);

LIB860_API void GspIedServer_setLocalIpAddress(GspIedServer self, const char* localIpAddress);

LIB860_API void GspIedServer_setServerIdentity(GspIedServer self, const char* vendor, const char* model, const char* revision);

LIB860_API void GspIedServer_setFilestoreBasepath(GspIedServer self, const char* basepath);

LIB860_API void GspIedServer_start(GspIedServer self, int tcpPort);

LIB860_API void GspIedServer_startThreadless(GspIedServer self, int tcpPort);

LIB860_API int GspIedServer_waitReady(GspIedServer self, unsigned int timeoutMs);

LIB860_API void GspIedServer_processIncomingData(GspIedServer self);

LIB860_API void GspIedServer_performPeriodicTasks(GspIedServer self);

LIB860_API void GspIedServer_stopThreadless(GspIedServer self);

LIB860_API GspIedModel** GspIedServer_getDataModels(GspIedServer self);

LIB860_API int GspIedServer_getNumberOfOpenConnections(GspIedServer self);

LIB860_API GspMmsServer GspIedServer_getMmsServer(GspIedServer self);

LIB860_API void GspIedServer_enableGoosePublishing(GspIedServer self);

LIB860_API void GspIedServer_disableGoosePublishing(GspIedServer self);

LIB860_API void GspIedServer_setGooseInterfaceId(GspIedServer self, const char* interfaceId);

LIB860_API void GspIedServer_setGooseInterfaceIdEx(GspIedServer self, GspLogicalNode* ln, const char* gcbName, const char* interfaceId);

LIB860_API void GspIedServer_useGooseVlanTag(GspIedServer self, GspLogicalNode* ln, const char* gcbName, bool useVlanTag);

LIB860_API void GspIedServer_setAuthenticator(GspIedServer self, GspAcseAuthenticator authenticator, void* authenticatorParameter);

LIB860_API void GspIedServer_lockDataModel(GspIedServer self);

LIB860_API void GspIedServer_unlockDataModel(GspIedServer self);

LIB860_API GspMmsValue* GspIedServer_getAttributeValue(GspIedServer self, GspDataAttribute* dataAttribute);

LIB860_API bool GspIedServer_getBooleanAttributeValue(GspIedServer self, const GspDataAttribute* dataAttribute);

LIB860_API int32_t GspIedServer_getInt32AttributeValue(GspIedServer self, const GspDataAttribute* dataAttribute);

LIB860_API int64_t GspIedServer_getInt64AttributeValue(GspIedServer self, const GspDataAttribute* dataAttribute);

LIB860_API uint32_t GspIedServer_getUInt32AttributeValue(GspIedServer self, const GspDataAttribute* dataAttribute);

LIB860_API float GspIedServer_getFloatAttributeValue(GspIedServer self, const GspDataAttribute* dataAttribute);

LIB860_API uint64_t GspIedServer_getUTCTimeAttributeValue(GspIedServer self, const GspDataAttribute* dataAttribute);

LIB860_API uint32_t GspIedServer_getBitStringAttributeValue(GspIedServer self, const GspDataAttribute* dataAttribute);

LIB860_API const char* GspIedServer_getStringAttributeValue(GspIedServer self, const GspDataAttribute* dataAttribute);

LIB860_API GspMmsValue* GspIedServer_getFunctionalConstrainedData(GspIedServer self, GspDataObject* dataObject, GspFunctionalConstraint fc);

LIB860_API void GspIedServer_updateAttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, GspMmsValue* value);

LIB860_API void GspIedServer_updateFloatAttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, float value);

LIB860_API void GspIedServer_updateInt32AttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, int32_t value);

LIB860_API void GspIedServer_updateDbposValue(GspIedServer self, GspDataAttribute* dataAttribute, GspDbpos value);

LIB860_API void GspIedServer_updateInt64AttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, int64_t value);

LIB860_API void GspIedServer_updateUnsignedAttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, uint32_t value);

LIB860_API void GspIedServer_updateBitStringAttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, uint32_t value);

LIB860_API void GspIedServer_updateBooleanAttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, bool value);

LIB860_API void GspIedServer_updateBoolValue(GspIedServer self, const char *daRefer, bool value);

LIB860_API void GspIedServer_updateVisibleStringAttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, char *value);

LIB860_API void GspIedServer_updateUTCTimeAttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, uint64_t value);

LIB860_API void GspIedServer_updateTimestampAttributeValue(GspIedServer self, GspDataAttribute* dataAttribute, GspTimestamp* timestamp);

LIB860_API void GspIedServer_updateQuality(GspIedServer self, GspDataAttribute* dataAttribute, GspQuality quality);

LIB860_API void GspIedServer_setLogStorage(GspIedServer self, const char* logRef, GspLogStorage logStorage);

LIB860_API void GspIedServer_changeActiveSettingGroup(GspIedServer self, GspSettingGroupControlBlock* sgcb, uint8_t newActiveSg);

LIB860_API uint8_t GspIedServer_getActiveSettingGroup(GspIedServer self, GspSettingGroupControlBlock* sgcb);

LIB860_API void GspIedServer_setSgStorageFile(GspIedServer self, const char *file);
typedef enum {
    GSP_CONTROL_ACCEPTED = -1, /** check passed */
    GSP_CONTROL_HARDWARE_FAULT = 1, /** check failed due to hardware fault */
    GSP_CONTROL_TEMPORARILY_UNAVAILABLE = 2, /** control is already selected or operated */
    GSP_CONTROL_OBJECT_ACCESS_DENIED = 3, /** check failed due to access control reason - access denied for this client or state */
    GSP_CONTROL_OBJECT_UNDEFINED = 4, /** object not visible in this security context ??? */
    GSP_CONTROL_VALUE_INVALID = 11 /** ctlVal out of range */
} GspCheckHandlerResult;

typedef enum {
    GSP_CONTROL_RESULT_FAILED = 0, /** check or operation failed */
    GSP_CONTROL_RESULT_OK = 1,     /** check or operation was successful */
    GSP_CONTROL_RESULT_WAITING = 2 /** check or operation is in progress */
} GspControlHandlerResult;

typedef void* GspControlAction;

#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
LIB860_API void GspControlAction_setError(GspControlAction self, GspControlLastApplError error);

LIB860_API void GspControlAction_setAddCause(GspControlAction self, GspControlAddCause addCause);

LIB860_API int GspControlAction_getOrCat(GspControlAction self);

LIB860_API uint8_t* GspControlAction_getOrIdent(GspControlAction self, int* orIdentSize);

LIB860_API int GspControlAction_getCtlNum(GspControlAction self);

LIB860_API bool GspControlAction_isSelect(GspControlAction self);

LIB860_API GspClientConnection GspControlAction_getClientConnection(GspControlAction self);

LIB860_API GspDataObject* GspControlAction_getControlObject(GspControlAction self);

LIB860_API uint64_t GspControlAction_getControlTime(GspControlAction self);

typedef GspCheckHandlerResult (*GspControlPerformCheckHandler) (GspControlAction action,
                                                                void* parameter,
                                                                GspMmsValue* ctlVal,
                                                                bool test,
                                                                bool interlockCheck);

typedef GspControlHandlerResult (*GspControlWaitForExecutionHandler) (GspControlAction action,
                                                                      void* parameter,
                                                                      GspMmsValue* ctlVal,
                                                                      bool test,
                                                                      bool synchroCheck);

typedef GspControlHandlerResult (*GspControlHandler) (GspControlAction action,
                                                      void* parameter,
                                                      GspMmsValue* ctlVal,
                                                      bool test);

LIB860_API void GspIedServer_setControlHandler(GspIedServer self, GspDataObject* node, GspControlHandler handler, void* parameter);

LIB860_API void GspIedServer_setPerformCheckHandler(GspIedServer self, GspDataObject* node, GspControlPerformCheckHandler handler, void* parameter);

LIB860_API void GspIedServer_setWaitForExecutionHandler(GspIedServer self, GspDataObject* node, GspControlWaitForExecutionHandler handler, void* parameter);

LIB860_API void GspIedServer_updateCtlModel(GspIedServer self, GspDataObject* ctlObject, GspControlModel value);
#endif

/** Control block has been enabled by client */
#define GSP_DLT860_SVCB_EVENT_ENABLE 1

/** Control block has been disabled by client */
#define GSP_DLT860_SVCB_EVENT_DISABLE 0

typedef void (*GspSVCBEventHandler) (GspSVControlBlock* svcb, int event, void* parameter);

//LIB860_API void GspIedServer_setSVCBHandler(GspIedServer self, GspSVControlBlock* svcb, GspSVCBEventHandler handler, void* parameter);

typedef GspMmsDataAccessError (*GspWriteAccessHandler) (GspDataAttribute* dataAttribute, GspMmsValue* value, GspClientConnection connection, void* parameter);

LIB860_API void GspIedServer_handleWriteAccess(GspIedServer self,
                                               GspDataAttribute* dataAttribute,
                                               GspWriteAccessHandler handler,
                                               void* parameter);

typedef enum {
    ACCESS_POLICY_ALLOW,
    ACCESS_POLICY_DENY
} GspAccessPolicy;

LIB860_API void GspIedServer_setWriteAccessPolicy(GspIedServer self, GspFunctionalConstraint fc, GspAccessPolicy policy);

typedef GspMmsDataAccessError (*GspReadAccessHandler) (GspLogicalDevice* ld,
                                                    GspLogicalNode* ln,
                                                    GspDataObject* dataObject,
                                                    GspFunctionalConstraint fc,
                                                    GspClientConnection connection,
                                                    void* parameter);

LIB860_API void GspIedServer_setReadAccessHandler(GspIedServer self, GspReadAccessHandler handler, void* parameter);

GspMmsValue *GspIedServer_getValueByStr(GspIedServer server, const char *refer, const char *fc, const char *value);

#endif /* GSP_IED_SERVER_API_H_ */
