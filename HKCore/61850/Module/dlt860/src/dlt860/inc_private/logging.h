/*
 *  logging.h
 */


#ifndef GSP_LIBIEC61850_SRC_IEC61850_INC_PRIVATE_LOGGING_H_
#define GSP_LIBIEC61850_SRC_IEC61850_INC_PRIVATE_LOGGING_H_

typedef struct {
    char* name;
    GspLogicalNode* parentLN;
    bool locked;
    GspLogStorage logStorage;
    uint64_t newEntryId;
    uint64_t newEntryTime;
    uint64_t oldEntryId;
    uint64_t oldEntryTime;
} GspLogInstance;

typedef struct {
    char* name;
    GspLogControlBlock* logControlBlock;
    GspMmsMapping* mmsMapping;
    GspDataSet* dataSet;
    char* dataSetRef;
    bool isDynamicDataSet;
    GspLogicalNode* logicalNode;
    GspMmsDomain* domain;
    GspMmsValue* mmsValue;
    GspMmsVariableSpecification* mmsType;
    GspMmsValue* oldEntr;
    GspMmsValue* oldEntrTm;
    GspMmsValue* newEntr;
    GspMmsValue* newEntrTm;
    GspLogInstance* logInstance;
    bool enabled;
    uint64_t nextIntegrityScan;
    int triggerOps;
    uint32_t intgPd;
} GspLogControl;


LIB860_INTERNAL GspLogInstance* GspLogInstance_create(GspLogicalNode* parentLN, const char* name);

LIB860_INTERNAL void GspLogInstance_setLogStorage(GspLogInstance* self, GspLogStorage logStorage);

LIB860_INTERNAL void GspLogInstance_logSingleData(GspLogInstance* self, const char* dataRef, GspMmsValue* value, uint8_t flag);

LIB860_INTERNAL uint64_t GspLogInstance_logEntryStart(GspLogInstance* self);

LIB860_INTERNAL void GspLogInstance_logEntryData(GspLogInstance* self, uint64_t entryID, const char* dataRef, GspMmsValue* value, uint8_t flag);

LIB860_INTERNAL void GspLogInstance_logEntryFinished(GspLogInstance* self, uint64_t entryID);

LIB860_INTERNAL void GspLogInstance_destroy(GspLogInstance* self);

LIB860_INTERNAL GspLogControl* LogControl_create(GspLogicalNode* parentLN, GspMmsMapping* mmsMapping);

LIB860_INTERNAL void GspLogControl_setLog(GspLogControl* self, GspLogInstance* logInstance);

LIB860_INTERNAL void GspLogControl_destroy(GspLogControl* self);

LIB860_INTERNAL void GspLogControl_setLogStorage(GspLogControl* self, GspLogStorage logStorage);

LIB860_INTERNAL GspMmsVariableSpecification* GspLogging_createLCBs(GspMmsMapping* self,
                                                                   GspMmsDomain* domain,
                                                                   GspLogicalNode* logicalNode,
                                                                   int lcbCount);

LIB860_INTERNAL void GspLogging_processIntegrityLogs(GspMmsMapping* self, uint64_t currentTimeInMs);

LIB860_INTERNAL GspMmsValue* Gsp_LOG_SVC_readAccessControlBlock(GspMmsMapping* self, GspMmsDomain* domain, char* variableIdOrig);

LIB860_INTERNAL GspMmsDataAccessError Gsp_LOG_SVC_writeAccessLogControlBlock(GspMmsMapping* self,
                                                                             GspMmsDomain* domain,
                                                                             char* variableIdOrig,
                                                                             GspMmsValue* value,
                                                                             GspMmsServerConnection connection);

LIB860_INTERNAL GspLogControl* lookupGspLogControl(GspMmsMapping* self, GspMmsDomain* domain, char* lnName, char* objectName);
LIB860_INTERNAL GspLogInstance* getGspLogInstanceByLogRef(GspMmsMapping* self, const char* logRef);
#endif
