#ifndef GSP_MMS_SERVER_FUNC_H
#define GSP_MMS_SERVER_FUNC_H

#include "gsp_mms_server.h"
#include <string>
#include <set>
#include "dlt860_server_interface.h"
#include <chrono>
#include <unordered_map>
#include <filesystem>

using namespace std;
template <typename T>
T *createAsnResponse()
{
    auto obj = (T*)calloc(1, sizeof(T));
    return obj;
}

class GspServerAssociate
{
public:
    static void *handleAssociateNegotiate(GspMmsServerConnection self, void *request);
    static void *handleAssociate(GspMmsServerConnection self, void *request);
    static void *handleRelease(GspMmsServerConnection self, void *request);
    static void *handleAbort(GspMmsServerConnection self, void *request);
};

class GspServerObject
{
public:
    static void *handleGetServerDirectory(GspMmsServerConnection self, void *request);
    static void *handleGetLogicalDeviceDirectory(GspMmsServerConnection self, void *request);
    static void *handleGetLogicalNodeDirectory(GspMmsServerConnection self, void *request);
    static void *handleGetAllDataValues(GspMmsServerConnection self, void *request);
    static void *handleGetAllCbValues(GspMmsServerConnection self, void *request);
    static void* handleGetAllDataDefinition(GspMmsServerConnection self, void* request);
    static void setIgnoreIedNames(const set<string> &iedNames) { _ignoreIedNames = iedNames; }
private:
    static set<string> _ignoreIedNames;
};

template <typename TP>
time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
    return system_clock::to_time_t(sctp);
}

class GspServerFile
{
public:
    static void *handleGetFileDirectory(GspMmsServerConnection self, void *request);
    static void *handleGetFileAttributeValues(GspMmsServerConnection self, void *request);
    static void *handleDeleteFile(GspMmsServerConnection self, void *request);
    static void *handleGetFile(GspMmsServerConnection self, void *request);
    static void *handleSetFile(GspMmsServerConnection self, void *request);
    static bool getFileInfo(const filesystem::path& filename, uint32_t* fileSize, uint64_t* lastModificationTimestamp);
    static uint32_t getFileCrc32(const string &fileName);
};

class GspServerTest
{
public:
    static void *handleTest(GspMmsServerConnection self, void *request);
};

class GspServerData
{
public:
    static void *handleGetDataValues(GspMmsServerConnection self, void *request);
    static void *handleSetDataValues(GspMmsServerConnection self, void *request);
    static void *handleGetDataDirectory(GspMmsServerConnection self, void *request);
    static void *handleGetDataDefinition(GspMmsServerConnection self, void *request);
private:
    static void fillDataDefine(GspModelNode* modelNode, GetDataDefinitionResponsePDU_t* resp, const string& parentRef, const string& fc, const string& referAfter);
};

class GspServerDataSet
{
public:
    static void *handleGetDataSetValues(GspMmsServerConnection self, void *request);
    static void *handleSetDataSetValues(GspMmsServerConnection self, void *request);
    static void *handleGetDataSetDirectory(GspMmsServerConnection self, void *request);
    static void *handleCreateDataSet(GspMmsServerConnection self, void *request);
    static void *handleDeleteDataSet(GspMmsServerConnection self, void *request);
};

class GspServerSettingGroup
{
public:
    static void *handleSelectActiveSg(GspMmsServerConnection self, void *request);
    static void *handleSelectActiveSgImp(GspMmsServerConnection self, const string &refer, int sgNumber);
    static void *handleSelectEditSg(GspMmsServerConnection self, void *request);
    static void *handleSetEditSgValue(GspMmsServerConnection self, void *request);
    static void *handleConfirmEditSgValues(GspMmsServerConnection self, void *request);
    static void *handleGetEditSgValue(GspMmsServerConnection self, void *request);
    static void *handleGetSgcbValues(GspMmsServerConnection self, void *request);
};

class GspServerReport
{
public:
    static void *handleGetBrcbValues(GspMmsServerConnection self, void *request);
    static void *handleSetBrcbValues(GspMmsServerConnection self, void *request);
    static void *handleGetUrcbValues(GspMmsServerConnection self, void *request);
    static void *handleSetUrcbValues(GspMmsServerConnection self, void *request);
};

class GspServerRpc
{
public:
    static void *handleGetRpcInterfaceDirectory(GspMmsServerConnection self, void* request);
    static void* handleGetRpcMethodDirectory(GspMmsServerConnection self, void* request);
    static void* handleGetRpcInterfaceDefinition(GspMmsServerConnection self, void* request);
    static void* handleGetRpcMethodDefinition(GspMmsServerConnection self, void* request);
    static void* handleRpcCall(GspMmsServerConnection self, void* request);
    static void addRpcCall(const string &interface, const string &method, RpcInfo *rpcInfo);
    static void delRpcCall(const string &interface, const string &method);
private:
    static map<string, map<string, RpcInfo*> > interfaceMethodMap;
};

class GspServerControl
{
public:
    static void *handleSelect(GspMmsServerConnection self, void *request);
    static void *handleSelectWithValue(GspMmsServerConnection self, void *request);
    static void *handleCancel(GspMmsServerConnection self, void *request);
    static void *handleOperate(GspMmsServerConnection self, void *request);
    static void *handleCommandTermination(GspMmsServerConnection self, void *request);
    static void *handleTimeActivatedOperate(GspMmsServerConnection self, void *request);
    static void *handleTimeActivatedOperateTermination(GspMmsServerConnection self, void *request);

};

class GspServerLog
{
public:
    static void *handleGetLcbValues(GspMmsServerConnection self, void *request);
    static void *handleSetLcbValues(GspMmsServerConnection self, void *request);
    static void *handleQueryLogByTime(GspMmsServerConnection self, void *request);
    static void *handleQueryLogAfter(GspMmsServerConnection self, void *request);
    static void *handleGetLogStatusValues(GspMmsServerConnection self, void *request);
};

#endif
