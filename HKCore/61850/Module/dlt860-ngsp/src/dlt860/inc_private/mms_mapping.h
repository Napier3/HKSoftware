/*
 *  mms_mapping.h
 */

#ifndef GSP_MMS_MAPPING_H_
#define GSP_MMS_MAPPING_H_

#include "dlt860_common_internal.h"
#include "libdlt860_define.h"
#include "mms_device_model.h"
#include "control.h"

#define GSP_REPORT_CONTROL_NONE 0U
#define GSP_REPORT_CONTROL_VALUE_CHANGED 1U
#define GSP_REPORT_CONTROL_QUALITY_CHANGED 2U
#define GSP_REPORT_CONTROL_VALUE_UPDATE 4U
#define GSP_REPORT_CONTROL_INTEGRITY 8U
#define GSP_REPORT_CONTROL_GENERAL_INTERROGATION 16U
#define GSP_REPORT_CONTROL_APPLICATION_TRIGGER 32U
#define GSP_REPORT_CONTROL_NOT_UPDATED 64U

typedef enum {
    LOG_CONTROL_NONE,
    LOG_CONTROL_VALUE_UPDATE,
    LOG_CONTROL_VALUE_CHANGED,
    LOG_CONTROL_QUALITY_CHANGED
} GspLogInclusionFlag;

typedef struct sGspMmsMapping GspMmsMapping;

typedef struct
{
    GspSettingGroupControlBlock* sgcb;
    GspMmsValue* sgcbMmsValues;
    GspMmsDomain* mmsDomain;

    GspActiveSettingGroupChangedHandler actSgChangedHandler;
    void* actSgChangedHandlerParameter;

    GspEditSettingGroupChangedHandler editSgChangedHandler;
    void* editSgChangedHandlerParameter;

    GspEditSettingGroupConfirmationHandler editSgConfirmedHandler;
    void* editSgConfirmedHandlerParameter;

    GspClientConnection editingClient;
    uint64_t reservationTimeout;
} GspSettingGroup;

LIB860_INTERNAL GspMmsMapping* GspMmsMapping_create(GspIedModel* model, GspIedServer iedServer);

LIB860_INTERNAL GspMmsMapping* GspMmsMapping_createMulti(GspIedModel **model, GspIedServer iedServer);

LIB860_INTERNAL GspMmsDevice* GspMmsMapping_getMmsDeviceModel(GspMmsMapping* mapping);
#if (CONFIG_DLT860_CONTROL_SERVICE == 1)
LIB860_INTERNAL void GspMmsMapping_initializeControlObjects(GspMmsMapping* self);
#endif

LIB860_INTERNAL void GspMmsMapping_configureSettingGroups(GspMmsMapping* self);

LIB860_INTERNAL void GspMmsMapping_checkForSettingGroupReservationTimeouts(GspMmsMapping* self, uint64_t currentTime);

LIB860_INTERNAL void GspMmsMapping_setSgChangedHandler(GspMmsMapping* self,
                                                       GspSettingGroupControlBlock* sgcb,
                                                       GspActiveSettingGroupChangedHandler handler,
                                                       void* parameter);

LIB860_INTERNAL void GspMmsMapping_setEditSgChangedHandler(GspMmsMapping* self,
                                                           GspSettingGroupControlBlock* sgcb,
                                                           GspEditSettingGroupChangedHandler handler,
                                                           void* parameter);

LIB860_INTERNAL void GspMmsMapping_setConfirmEditSgHandler(GspMmsMapping* self,
                                                           GspSettingGroupControlBlock* sgcb,
                                                           GspEditSettingGroupConfirmationHandler handler,
                                                           void* parameter);

LIB860_INTERNAL int GspchangeActiveSettingGroup(GspMmsMapping* self,
                                                GspSettingGroup* sg,
                                                uint8_t newActiveSg,
                                                GspClientConnection clientConn);

LIB860_INTERNAL int GspSelectEditSg(GspMmsMapping *self, GspClientConnection connection,
                                    GspSettingGroup *sg,
                                    uint8_t editSg);

LIB860_INTERNAL int GspSetEditSgs(GspMmsMapping *self, GspClientConnection connection, GspSettingGroup *sg);

LIB860_INTERNAL int GspConfirmEditSgs(GspMmsMapping *self, const string &refer, int editSg, const vector<string> &refers, const vector<string> &values);

LIB860_INTERNAL void GspMmsMapping_setMmsServer(GspMmsMapping* self, GspMmsServer server);

LIB860_INTERNAL void GspMmsMapping_installHandlers(GspMmsMapping* self);

LIB860_INTERNAL void GspMmsMapping_destroy(GspMmsMapping* mapping);

LIB860_INTERNAL void GspMmsMapping_startEventWorkerThread(GspMmsMapping* self);

LIB860_INTERNAL void GspMmsMapping_stopEventWorkerThread(GspMmsMapping* self);

LIB860_INTERNAL GspDataSet* GspMmsMapping_createDataSetByNamedVariableList(GspMmsMapping* self, GspMmsNamedVariableList variableList);

LIB860_INTERNAL void GspMmsMapping_triggerReportObservers(GspMmsMapping* self, GspMmsValue* value, int flag);

LIB860_INTERNAL void GspReportControl_triggerReportObservers(GspReportControl* rc, int flag, bool modelLocked, int index);

LIB860_INTERNAL void GspMmsMapping_triggerLogging(GspMmsMapping* self, GspMmsValue* value, GspLogInclusionFlag flag);

//LIB860_INTERNAL void GspMmsMapping_triggerGooseObservers(GspMmsMapping* self, GspMmsValue* value);

//LIB860_INTERNAL void GspMmsMapping_enableGoosePublishing(GspMmsMapping* self);

//LIB860_INTERNAL void GspMmsMapping_disableGoosePublishing(GspMmsMapping* self);

//LIB860_INTERNAL void GspMmsMapping_useGooseVlanTag(GspMmsMapping* self, GspLogicalNode* ln, const char* gcbName, bool useVlanTag);

//LIB860_INTERNAL void GspMmsMapping_setGooseInterfaceId(GspMmsMapping* self,  GspLogicalNode* ln, const char* gcbName, const char* interfaceId);

// LIB860_INTERNAL void GspMmsMapping_addControlObject(GspMmsMapping* self, GspControlObject* controlObject);

LIB860_INTERNAL char* GspMmsMapping_getNextNameElement(char* name);

LIB860_INTERNAL void GspMmsMapping_createPhyComAddrStructure(GspMmsVariableSpecification* namedVariable);

// LIB860_INTERNAL GspControlObject* GspMmsMapping_getControlObject(GspMmsMapping* self, GspMmsDomain* domain, char* lnName, char* coName);

LIB860_INTERNAL GspMmsNamedVariableList GspMmsMapping_getDomainSpecificVariableList(GspMmsMapping* self, const char* variableListReference);

LIB860_INTERNAL GspDataSet* GspMmsMapping_getDomainSpecificDataSet(GspMmsMapping* self, const char* dataSetName);

LIB860_INTERNAL void GspMmsMapping_freeDynamicallyCreatedDataSet(GspDataSet* dataSet);

LIB860_INTERNAL void GspMmsMapping_setConnectionIndicationHandler(GspMmsMapping* self, GspIedConnectionIndicationHandler handler, void* parameter);

LIB860_INTERNAL void GspMmsMapping_setGspLogStorage(GspMmsMapping* self, const char* logRef, GspLogStorage logStorage);

LIB860_INTERNAL void GspMmsMapping_installWriteAccessHandler(GspMmsMapping* self, GspDataAttribute* dataAttribute, GspWriteAccessHandler handler, void* parameter);

LIB860_INTERNAL void GspMmsMapping_installReadAccessHandler(GspMmsMapping* self, GspReadAccessHandler handler, void* paramter);

// LIB860_INTERNAL GspMmsDataAccessError GspControl_writeAccessControlObject(GspMmsMapping* self,
//                                                                           GspMmsDomain* domain,
//                                                                           char* variableIdOrig,
//                                                                           GspMmsValue* value,
//                                                                           GspMmsServerConnection connection);

// LIB860_INTERNAL GspControlObject* GspControl_lookupControlObject(GspMmsMapping* self, GspMmsDomain* domain, char* lnName, char* objectName);

// LIB860_INTERNAL void GspControl_processControlActions(GspMmsMapping* self, uint64_t currentTimeInMs);

LIB860_INTERNAL GspIedModel* GspMmsMapping_getIedModelByDomainName(GspMmsMapping* self, const string &domainName);

LIB860_INTERNAL GspLogicalDevice* GspMmsMapping_getLdByDomainName(GspMmsMapping *self, const string &domainName);

LIB860_INTERNAL GspSettingGroup* GspgetSettingGroupByMmsDomain(GspMmsMapping* self, GspMmsDomain* domain);

LIB860_INTERNAL void GspMmsMapping_setSgStorageFile(GspMmsMapping *self, const string &filePath);

LIB860_INTERNAL Data_t *mmsMapping_getDataByReference(GspMmsMapping *self, const string &reference, const string &fc);

#endif /* GSP_MMS_MAPPING_H_ */
