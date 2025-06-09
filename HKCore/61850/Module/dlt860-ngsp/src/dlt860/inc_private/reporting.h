/*
 *  reporting.h
 */

#ifndef GSP_REPORTING_H_
#define GSP_REPORTING_H_

#include <deque>
#include <vector>
#include "ReportPDU.h"

using namespace std;

typedef struct sGspReportBufferEntry GspReportBufferEntry;

struct sGspReportBufferEntry {
    uint8_t entryId[8];
    uint64_t timeOfEntry;
    unsigned int flags:2; /* bit 0 (1 = isIntegrityReport), bit 1 (1 = isGiReport) */
    deque<ReportPDU__entry__entryData__Member*> data;
public:
    ~sGspReportBufferEntry() {
        auto tmpReport = (ReportPDU_t *)calloc(1, sizeof(ReportPDU_t));
        for(auto &item : data)
        {
            asn_sequence_add(&tmpReport->entry.entryData, item);
        }
        ASN_STRUCT_FREE(asn_DEF_ReportPDU, tmpReport);
    }
};

struct GspReportBuffer {
    bool isOverflow; /* true if overflow condition is active */
    int maxReportSize;
    deque<GspReportBufferEntry*> reportQueue;
    GspSemaphore lock; /* protect access to report buffer */
public:
    void clear();
    GspReportBufferEntry *first() {
        if(reportQueue.empty())
            return nullptr;
        auto entry = *reportQueue.begin();
        while(!entry)
        {
            reportQueue.pop_front();
            entry = *reportQueue.begin();
        }
        return entry;
    }

    GspReportBufferEntry *last() {
        if(reportQueue.empty())
            return nullptr;
        return reportQueue.back();
    }
    GspReportBuffer(int maxSize);
    ~GspReportBuffer();
};

struct GspReportControl{
    char* name;
    GspMmsDomain* domain;
    GspLogicalNode* parentLN;
    GspMmsValue* rcbValues;
    GspMmsValue* inclusionField;
    GspMmsValue* confRev;
    GspDataSet* dataSet;
    bool isDynamicDataSet;
    bool enabled;
    bool reserved;
    bool buffered; /* true if report is a buffered report */
    GspMmsValue** bufferedDataSetValues; /* used to buffer values during bufTm time */
    GspMmsValue** valueReferences; /* array to store value references for fast access */
    bool gi; /* flag to indicate that a GI report is triggered */
    uint16_t sqNum;
    uint32_t intgPd; /* integrity period in ms */
    uint32_t bufTm;
    uint64_t nextIntgReportTime; /* time when to send next integrity report */
    uint64_t reservationTimeout;
    GspMmsServerConnection clientConnection;
    uint64_t lastEntryId;
    int triggerOps;
    /* information for segmented reporting */
    bool segmented; /* indicates that a segmented report is in process */
    int startIndexForNextSegment; /* start data set index for the next report segment */
    GspMmsValue* subSeqVal; /* sub sequence value for segmented reporting */
    uint64_t segmentedReportTimestamp; /* time stamp used for all report segments */
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore createNotificationsMutex;  /* { covered by mutex } */
#endif
    uint8_t* inclusionFlags; /* { covered by mutex } */
    bool triggered;                      /* { covered by mutex } */
    uint64_t reportTime;                 /* { covered by mutex } */
    bool isBuffering; /* true if buffered RCB is buffering (datSet is set to a valid value) */
    bool isResync; /* true if buffered RCB is in resync state */
    int resvTms; /* -1 for preconfigured client, 0 - not reserved, > 0 reserved by client */
    GspReportBuffer* reportBuffer;
    GspMmsValue* timeOfEntry;
    GspIedServer server;
} ;

LIB860_INTERNAL GspReportControl* GspReportControl_create(bool buffered, GspLogicalNode* parentLN, int reportBufferSize, GspIedServer server);

LIB860_INTERNAL void GspReportControl_destroy(GspReportControl* self);

LIB860_INTERNAL void GspReportControl_valueUpdated(GspReportControl* self, int dataSetEntryIndex, int flag, bool modelLocked);

LIB860_INTERNAL GspMmsValue* GspReportControl_getRCBValue(GspReportControl* rc, const char *elementName);

LIB860_INTERNAL GspMmsVariableSpecification* GspReporting_createMmsBufferedRCBs(GspMmsMapping* self,
                                                                                GspMmsDomain* domain,
                                                                                GspLogicalNode* logicalNode,
                                                                                int reportsCount);

LIB860_INTERNAL GspMmsVariableSpecification* GspReporting_createMmsUnbufferedRCBs(GspMmsMapping* self,
                                                                                  GspMmsDomain* domain,
                                                                                  GspLogicalNode* logicalNode,
                                                                                  int reportsCount);

LIB860_INTERNAL GspMmsDataAccessError GspReporting_RCBWriteAccessHandler(GspMmsMapping* self,
                                                                         GspReportControl* rc,
                                                                         char* elementName,
                                                                         GspMmsValue* value,
                                                                         GspMmsServerConnection connection);

LIB860_INTERNAL void GspReportControl_readAccess(GspReportControl* rc, char* elementName);

LIB860_INTERNAL void GspReporting_activateBufferedReports(GspMmsMapping* self);

LIB860_INTERNAL void GspReporting_processReportEvents(GspMmsMapping* self, uint64_t currentTimeInMs);

LIB860_INTERNAL void GspReporting_processReportEventsAfterUnlock(GspMmsMapping* self);

LIB860_INTERNAL void GspReporting_sendReports(GspMmsMapping* self, GspMmsServerConnection connection);

LIB860_INTERNAL void GspReporting_deactivateReportsForConnection(GspMmsMapping* self, GspMmsServerConnection connection);

#endif /* GSP_REPORTING_H_ */
