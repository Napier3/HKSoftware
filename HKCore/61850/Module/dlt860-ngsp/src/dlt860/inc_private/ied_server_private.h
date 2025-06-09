/*
 *  ied_server_private.h
 */


#ifndef GSP_IED_SERVER_PRIVATE_H_
#define GSP_IED_SERVER_PRIVATE_H_

#define ALLOW_WRITE_ACCESS_DC 1
#define ALLOW_WRITE_ACCESS_CF 2
#define ALLOW_WRITE_ACCESS_SP 4
#define ALLOW_WRITE_ACCESS_SV 8
#define ALLOW_WRITE_ACCESS_SE 16

#include "sgstorage.h"
#include <mutex>
#include <unordered_map>
#include <string>
#include "dlt860_server_interface.h"

using namespace std;

struct sGspIedServer
{
    GspIedModel** modelss;
    GspMmsDevice* mmsDevice;
    GspMmsServer mmsServer;
    char* localIpAddress;
    GspMmsMapping* mmsMapping;
    GspLinkedList clientConnections;
    uint8_t writeAccessPolicies;

#if (CONFIG_DLT860_REPORT_SERVICE == 1)
    int reportBufferSizeBRCBs;
    int reportBufferSizeURCBs;
#endif

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore dataModelLock;
    GspSemaphore clientConnectionsLock;
    GspIedServerConfig serverConfig;
#endif

#if (CONFIG_MMS_SERVER_CONFIG_SERVICES_AT_RUNTIME == 1)
    bool logServiceEnabled;
#endif

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspThread serverThread;
#endif

#if (CONFIG_IEC61850_SUPPORT_SERVER_IDENTITY == 1)
    char* vendorName;
    char* modelName;
    char* revision;
#endif

    uint8_t edition;
    bool running;
    ServerFunctionHook functionHook;
    void* functionHookParam;
    unordered_map<string, GspModelNode*> referNodeCache;
    unordered_map<string, GspDataSet*> dataSetCache;
    GspLinkedList cacheValueList;
    mutex &getlock() { return valueLock; }
private:
    mutex valueLock;
};

LIB860_INTERNAL GspClientConnection Gsp_private_IedServer_getClientConnectionByHandle(GspIedServer self, void* serverConnectionHandle);

LIB860_INTERNAL GspClientConnection Gsp_private_ClientConnection_create(void* serverConnectionHandle);

LIB860_INTERNAL void Gsp_private_ClientConnection_destroy(GspClientConnection self);

LIB860_INTERNAL int Gsp_private_ClientConnection_getTasksCount(GspClientConnection self);

LIB860_INTERNAL void Gsp_private_ClientConnection_increaseTasksCount(GspClientConnection self);

LIB860_INTERNAL void Gsp_private_ClientConnection_decreaseTasksCount(GspClientConnection self);

LIB860_INTERNAL void* Gsp_private_ClientConnection_getServerConnectionHandle(GspClientConnection self);

LIB860_INTERNAL void Gsp_private_IedServer_addNewClientConnection(GspIedServer self, GspClientConnection newClientConnection);

LIB860_INTERNAL void Gsp_private_IedServer_removeClientConnection(GspIedServer self, GspClientConnection clientConnection);

LIB860_INTERNAL GspDataSet *Gsp_private_IedServer_getDataSet(GspIedServer self, const char *dataSetRefer);
#endif /* GSP_IED_SERVER_PRIVATE_H_ */
