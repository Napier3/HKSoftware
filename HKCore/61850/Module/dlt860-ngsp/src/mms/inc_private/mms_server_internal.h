/*
 *  mms_server_internal.h
 */

#ifndef GSP_MMS_SERVER_INTERNAL_H_
#define GSP_MMS_SERVER_INTERNAL_H_

#include "libdlt860_platform_includes.h"

#include <string>
#include <vector>
#include <deque>
#include "gsp_mms_common.h"
#include "mms_server_connection.h"
#include "mms_device_model.h"
#include "mms_common_internal.h"
#include "stack_config.h"
#include "mms_server_libinternal.h"
#include "asn_inc.h"
#include "byte_buffer.h"
#include "string_utilities.h"
#include "map.h"
#include "gsp_hal_thread.h"
#include "stringmap.h"
#include "mms_value_cache.h"

using namespace std;
class CacheMap : public unordered_map<GspMmsDomain *, ValueHashMap *>
{
public:
    CacheMap()
    {
    }
};

#ifndef DEBUG_MMS_SERVER
#define DEBUG_MMS_SERVER 0
#endif

#ifndef MMS_STATUS_SERVICE
#define MMS_STATUS_SERVICE 1
#endif

#ifndef MMS_IDENTIFY_SERVICE
#define MMS_IDENTIFY_SERVICE 1
#endif

#ifndef MMS_FILE_SERVICE
#define MMS_FILE_SERVICE 1
#endif

#ifndef CONFIG_MMS_SERVER_MAX_GET_FILE_TASKS
#define CONFIG_MMS_SERVER_MAX_GET_FILE_TASKS 5
#endif




struct sGspMmsServer {
    GspIsoServer isoServer;
    GspMmsDevice* device;

    MmsReadVariableHandler readHandler;
    void* readHandlerParameter;

    MmsReadAccessHandler readAccessHandler;
    void* readAccessHandlerParameter;

    MmsWriteVariableHandler writeHandler;
    void* writeHandlerParameter;

    MmsConnectionHandler connectionHandler;
    void* connectionHandlerParameter;

    GspMmsNamedVariableListChangedHandler variableListChangedHandler; /* TODO this is only required if dynamic data sets are supported! */
    void* variableListChangedHandlerParameter;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore openConnectionsLock;
#endif

    Map openConnections;
    CacheMap *valueCaches;
    
    bool isLocked;

    GspByteBuffer* transmitBuffer; /* global buffer for encoding reports, delayed responses... */
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore transmitBufferMutex;
#endif

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore modelMutex;
#endif

#if (MMS_STATUS_SERVICE == 1)
    int vmdLogicalStatus;
    int vmdPhysicalStatus;
    GSP_MmsStatusRequestListener statusRequestListener;
    void* statusRequestListenerParameter;
#endif /* MMS_STATUS_SERVICE == 1 */

#if (MMS_IDENTIFY_SERVICE == 1)
    char* vendorName;
    char* modelName;
    char* revision;
#endif /* MMS_IDENTIFY_SERVICE == 1 */

#if (MMS_OBTAIN_FILE_SERVICE == 1)
    GspMmsObtainFileHandler obtainFileHandler;
    void* obtainFileHandlerParameter;

    GspMmsGetFileCompleteHandler getFileCompleteHandler;
    void* getFileCompleteHandlerParameter;

#endif

#if (MMS_FILE_SERVICE == 1)
    GspMmsFileAccessHandler fileAccessHandler;
    void* fileAccessHandlerParameter;
#endif

#if (CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME == 1)
    char* filestoreBasepath;
#endif

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
    int maxConnections;
    bool fileServiceEnabled;
    bool dynamicVariableListServiceEnabled;
    int maxDataSetEntries;
    bool journalServiceEnabled;
    int maxAssociationSpecificDataSets;
    int maxDomainSpecificDataSets;
#endif /* (CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME == 1) */
    char* logStoragePath;
};

struct sGspMmsServerConnection {
    int maxServOutstandingCalling;
    int maxServOutstandingCalled;
    int dataStructureNestingLevel;
    uint32_t maxPduSize; /* local detail */
    GspIsoConnection isoConnection;
    GspMmsServer server;

    uint16_t apduSize;
    uint32_t asduSize;

#if (MMS_OBTAIN_FILE_SERVICE == 1)
    uint32_t lastRequestInvokeId; /* only used by obtainFile service */
#endif

#if (MMS_DYNAMIC_DATA_SETS == 1)
    GspLinkedList /*<MmsNamedVariableList>*/namedVariableLists; /* aa-specific named variable lists */
#endif

};



LIB860_INTERNAL GspByteBuffer* MmsServer_reserveTransmitBuffer(GspMmsServer self);

LIB860_INTERNAL void MmsServer_releaseTransmitBuffer(GspMmsServer self);

LIB860_INTERNAL void MmsServer_callConnectionHandler(GspMmsServer self, GspMmsServerConnection connection);

LIB860_INTERNAL GspMmsNamedVariableList mmsServer_getNamedVariableListWithName(GspLinkedList namedVariableLists, const char* variableListName);

LIB860_INTERNAL void toDotReference(string &reference);

LIB860_INTERNAL void toDollarReference(string &reference);

LIB860_INTERNAL void splitFcFromReference(const string &reference, string &fc, string &referWithoutFc);

LIB860_INTERNAL void splitFcFromReferenceDot(const string &reference, string &fc, string &referWithoutFc);

LIB860_INTERNAL void splitStr(vector<string> &output, const string &input, char delim);

LIB860_INTERNAL void splitStr(deque<string> &output, const string &input, char delim);

LIB860_INTERNAL void addFcToReference(string &reference, const string &fc, char delim);

LIB860_INTERNAL int GspServer_handleSetDataValues(GspMmsServerConnection self,
                                                  GspByteBuffer *request,
                                                  GspByteBuffer *response);

// LIB860_INTERNAL int GspServer_handleGetDataSetDirectory(GspMmsServerConnection self,
//                                                         GspByteBuffer *request,
//                                                         GspByteBuffer *response);

// LIB860_INTERNAL int GspServer_handleGetDataSetValues(GspMmsServerConnection self,
//                                                      GspByteBuffer *request,
//                                                      GspByteBuffer *response);

LIB860_INTERNAL int GspServer_encodeStructToBuffer(void *str, void *data, GspByteBuffer *response);

LIB860_INTERNAL void *createCbResponse(GspMmsServer self, ACSIClass_t acsi, const string &refer, const string &referAfter);

#endif /* MMS_SERVER_INTERNAL_H_ */
