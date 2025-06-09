#include "mms_service_table.h"
#include "mms_server_func.h"
#include <memory>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "ied_server_private.h"

const int MAX_FUNC_INDEX = 156;

dataDumpCb g_dataDumpCb = nullptr;

void setDataDumpHandler(dataDumpCb func)
{
    g_dataDumpCb = func;
}

int xer_dump_to_string(const void *buffer, size_t size, void *application_specific_key)
{
    string *s = reinterpret_cast<string *>(application_specific_key);
    const char *strBuf = reinterpret_cast<const char *>(buffer);
    
    *s = *s + string(strBuf, size);
    return 0;
}

ServiceFuncInfo funcInfoTable [] = {
    {},         // 0
    { GspServerAssociate::handleAssociate, GSP_SC_Associate, &asn_DEF_AssociateRequestPDU, &asn_DEF_AssociateResponsePDU, &asn_DEF_AssociateErrorPDU }, // 1
    { GspServerAssociate::handleAbort, GSP_SC_Abort, &asn_DEF_AbortRequestPDU, nullptr, nullptr},   // 2
    { GspServerAssociate::handleRelease, GSP_SC_Release, &asn_DEF_ReleaseRequestPDU, &asn_DEF_ReleaseResponsePDU, &asn_DEF_ReleaseErrorPDU},  // 3
    {},         // 4
    {},         // 5
    {},         // 6
    {},         // 7
    {},         // 8,
    {},         // 9,
    {},         // 10,
    {},         // 11,
    {},         // 12,
    {},         // 13,
    {},         // 14,
    {},         // 15,
    {},         // 16,
    {},         // 17,
    {},         // 18,
    {},         // 19,
    {},         // 20,
    {},         // 21,
    {},         // 22,
    {},         // 23,
    {},         // 24,
    {},         // 25,
    {},         // 26,
    {},         // 27,
    {},         // 28,
    {},         // 29,
    {},         // 30,
    {},         // 31,
    {},         // 32,
    {},         // 33,
    {},         // 34,
    {},         // 35,
    {},         // 36,
    {},         // 37,
    {},         // 38,
    {},         // 39,
    {},         // 40,
    {},         // 41,
    {},         // 42,
    {},         // 43,
    {},         // 44,
    {},         // 45,
    {},         // 46,
    {},         // 47,
    { GspServerData::handleGetDataValues, GSP_SC_GetDataValues, &asn_DEF_GetDataValuesRequestPDU, &asn_DEF_GetDataValuesResponsePDU, &asn_DEF_GetDataValuesErrorPDU}, // 48
    { GspServerData::handleSetDataValues, GSP_SC_SetDataValues, &asn_DEF_SetDataValuesRequestPDU, &asn_DEF_SetDataValuesResponsePDU, &asn_DEF_SetDataValuesErrorPDU}, // 49
    { GspServerData::handleGetDataDirectory, GSP_SC_GetDataDirectory, &asn_DEF_GetDataDirectoryRequestPDU, &asn_DEF_GetDataDirectoryResponsePDU, &asn_DEF_GetDataDirectoryErrorPDU}, // 50
    { GspServerData::handleGetDataDefinition, GSP_SC_GetDataDefinition, &asn_DEF_GetDataDefinitionRequestPDU, &asn_DEF_GetDataDefinitionResponsePDU, &asn_DEF_GetDataDefinitionErrorPDU}, // 51
    {},         // 52,
    {},         // 53,
    { GspServerDataSet::handleCreateDataSet, GSP_SC_CreateDataSet, &asn_DEF_CreateDataSetRequestPDU, &asn_DEF_CreateDataSetResponsePDU, &asn_DEF_CreateDataSetErrorPDU}, // 54
    { GspServerDataSet::handleDeleteDataSet, GSP_SC_DeleteDataSet, &asn_DEF_DeleteDataSetRequestPDU, &asn_DEF_DeleteDataSetResponsePDU, &asn_DEF_DeleteDataSetErrorPDU}, // 55
    {},         // 56,
    { GspServerDataSet::handleGetDataSetDirectory, GSP_SC_GetDataSetDirectory, &asn_DEF_GetDataSetDirectoryRequestPDU, &asn_DEF_GetDataSetDirectoryResponsePDU, &asn_DEF_GetDataSetDirectoryErrorPDU}, // 57
    { GspServerDataSet::handleGetDataSetValues, GSP_SC_GetDataSetValues, &asn_DEF_GetDataSetValuesRequestPDU, &asn_DEF_GetDataSetValuesResponsePDU, &asn_DEF_GetDataSetValuesErrorPDU}, // 58
    { GspServerDataSet::handleSetDataSetValues, GSP_SC_SetDataSetValues, &asn_DEF_SetDataSetValuesRequestPDU, &asn_DEF_SetDataSetValuesResponsePDU, &asn_DEF_SetDataSetValuesErrorPDU}, // 59
    {},         // 60,
    {},         // 61,
    {},         // 62,
    {},         // 63,
    {},         // 64,
    {},         // 65,
    {},         // 66,
    {},         // 67,
    { GspServerControl::handleSelect, GSP_SC_Select, &asn_DEF_SelectRequestPDU, &asn_DEF_SelectResponsePDU, &asn_DEF_SelectErrorPDU}, // 68
    { GspServerControl::handleSelectWithValue, GSP_SC_SelectWithValue, &asn_DEF_SelectWithValueRequestPDU, &asn_DEF_SelectWithValueResponsePDU, &asn_DEF_SelectWithValueErrorPDU}, // 69
    { GspServerControl::handleCancel, GSP_SC_Cancel, &asn_DEF_CancelRequestPDU, &asn_DEF_CancelResponsePDU, &asn_DEF_CancelErrorPDU}, // 70
    { GspServerControl::handleOperate, GSP_SC_Operate, &asn_DEF_OperateRequestPDU, &asn_DEF_OperateResponsePDU, &asn_DEF_OperateErrorPDU}, // 71
    { GspServerControl::handleCommandTermination, GSP_SC_CommandTermination, &asn_DEF_CommandTerminationRequestPDU, nullptr, nullptr }, // 72
    { GspServerControl::handleTimeActivatedOperate, GSP_SC_TimeActivatedOperate, &asn_DEF_TimeActivatedOperateRequestPDU, &asn_DEF_TimeActivatedOperateResponsePDU, &asn_DEF_TimeActivatedOperateErrorPDU}, // 73
    { GspServerControl::handleTimeActivatedOperateTermination, GSP_SC_TimeActivatedOperateTermination, &asn_DEF_TimeActivatedOperateTerminationRequestPDU, nullptr, nullptr}, // 74
    {},         // 75,
    {},         // 76,
    {},         // 77,
    {},         // 78,
    {},         // 79,
    { GspServerObject::handleGetServerDirectory, GSP_SC_GetServerDirectory, &asn_DEF_GetServerDirectoryRequestPDU, &asn_DEF_GetServerDirectoryResponsePDU, &asn_DEF_GetServerDirectoryErrorPDU}, // 80
    { GspServerObject::handleGetLogicalDeviceDirectory, GSP_SC_GetLogicDeviceDirectory, &asn_DEF_GetLogicalDeviceDirectoryRequestPDU, &asn_DEF_GetLogicalDeviceDirectoryResponsePDU, &asn_DEF_GetLogicalDeviceDirectoryErrorPDU }, // 81
    { GspServerObject::handleGetLogicalNodeDirectory, GSP_SC_GetLogicNodeDirectory, &asn_DEF_GetLogicalNodeDirectoryRequestPDU, &asn_DEF_GetLogicalNodeDirectoryResponsePDU, &asn_DEF_GetLogicalNodeDirectoryErrorPDU }, // 82
    { GspServerObject::handleGetAllDataValues, GSP_SC_GetAllDataValues, &asn_DEF_GetAllDataValuesRequestPDU, &asn_DEF_GetAllDataValuesResponsePDU, &asn_DEF_GetAllDataValuesErrorPDU }, // 83
    { GspServerSettingGroup::handleSelectActiveSg, GSP_SC_SelectActiveSG, &asn_DEF_SelectActiveSGRequestPDU, &asn_DEF_SelectActiveSGResponsePDU, &asn_DEF_SelectActiveSGErrorPDU}, // 84
    { GspServerSettingGroup::handleSelectEditSg, GSP_SC_SelectEditSG, &asn_DEF_SelectEditSGRequestPDU, &asn_DEF_SelectEditSGResponsePDU, &asn_DEF_SelectEditSGErrorPDU}, // 85
    { GspServerSettingGroup::handleSetEditSgValue, GSP_SC_SetEditSGValue, &asn_DEF_SetEditSGValueRequestPDU, &asn_DEF_SetEditSGValueResponsePDU, &asn_DEF_SetEditSGValueErrorPDU}, // 86
    { GspServerSettingGroup::handleConfirmEditSgValues, GSP_SC_ConfirmEditSGValues, &asn_DEF_ConfirmEditSGValuesRequestPDU, &asn_DEF_ConfirmEditSGValuesResponsePDU, &asn_DEF_ConfirmEditSGValuesErrorPDU}, // 87
    { GspServerSettingGroup::handleGetEditSgValue, GSP_SC_GetEditSGValue, &asn_DEF_GetEditSGValueRequestPDU, &asn_DEF_GetEditSGValueResponsePDU, &asn_DEF_GetEditSGValueErrorPDU}, // 88
    { GspServerSettingGroup::handleGetSgcbValues, GSP_SC_GetSGCBValues, &asn_DEF_GetSGCBValuesRequestPDU, &asn_DEF_GetSGCBValuesResponsePDU, &asn_DEF_GetSGCBValuesErrorPDU}, // 89
    {},         // 90,
    { GspServerReport::handleGetBrcbValues, GSP_SC_GetBRCBValues, &asn_DEF_GetBRCBValuesRequestPDU, &asn_DEF_GetBRCBValuesResponsePDU, &asn_DEF_GetBRCBValuesErrorPDU}, // 91
    { GspServerReport::handleSetBrcbValues, GSP_SC_SetBRCBValues, &asn_DEF_SetBRCBValuesRequestPDU, &asn_DEF_NULL, &asn_DEF_SetBRCBValuesErrorPDU}, // 92
    { GspServerReport::handleGetUrcbValues, GSP_SC_GetURCBValues, &asn_DEF_GetURCBValuesRequestPDU, &asn_DEF_GetURCBValuesResponsePDU, &asn_DEF_GetURCBValuesErrorPDU}, // 93
    { GspServerReport::handleSetUrcbValues, GSP_SC_SetURCBValues, &asn_DEF_SetURCBValuesRequestPDU, &asn_DEF_NULL, &asn_DEF_SetURCBValuesErrorPDU}, // 94
    { GspServerLog::handleGetLcbValues, GSP_SC_GetLCBValues, &asn_DEF_GetLCBValuesRequestPDU, &asn_DEF_GetLCBValuesResponsePDU, &asn_DEF_GetLCBValuesErrorPDU}, // 95
    { GspServerLog::handleSetLcbValues, GSP_SC_SetLCBValues, &asn_DEF_SetLCBValuesRequestPDU, nullptr, &asn_DEF_SetLCBValuesErrorPDU}, // 96
    { GspServerLog::handleQueryLogByTime, GSP_SC_QueryLogByTime, &asn_DEF_QueryLogByTimeRequestPDU, &asn_DEF_QueryLogByTimeResponsePDU, &asn_DEF_QueryLogByTimeErrorPDU}, // 97
    { GspServerLog::handleQueryLogAfter, GSP_SC_QueryLogAfter, &asn_DEF_QueryLogAfterRequestPDU, &asn_DEF_QueryLogAfterResponsePDU, &asn_DEF_QueryLogAfterErrorPDU}, // 98
    { GspServerLog::handleGetLogStatusValues, GSP_SC_GetLogStatusValues, &asn_DEF_GetLogStatusValuesRequestPDU, &asn_DEF_GetLogStatusValues_ResponsePDU, &asn_DEF_GetLogStatusValuesErrorPDU },         // 99,
    {},         // 100,
    {},         // 101,
    { nullptr, GSP_SC_GetGoCBValues, &asn_DEF_GetGoCBValuesRequestPDU, &asn_DEF_GetGoCBValuesResponsePDU, &asn_DEF_GetGoCBValuesErrorPDU}, // 102
    { nullptr, GSP_SC_SetGoCBValues, &asn_DEF_SetGoCBValuesRequestPDU, nullptr, &asn_DEF_SetGoCBValuesErrorPDU}, // 103
    {},         // 104,
    { nullptr, GSP_SC_GetMSVCBValues, &asn_DEF_GetMSVCBValuesRequestPDU, &asn_DEF_GetMSVCBValuesResponsePDU, &asn_DEF_GetMSVCBValuesErrorPDU}, // 105
    { nullptr, GSP_SC_SetMSVCBValues, &asn_DEF_SetMSVCBValuesRequestPDU, nullptr, nullptr}, // 106
    {},         // 107,
    {},         // 108,
    {},         // 109,
    { GspServerRpc::handleGetRpcInterfaceDirectory, GSP_SC_GetRpcInterfaceDirectory, &asn_DEF_GetRpcInterfaceDirectoryRequestPDU, &asn_DEF_GetRpcInterfaceDirectoryResponsePDU, &asn_DEF_GetRpcInterfaceDirectoryErrorPDU}, // 110
    { GspServerRpc::handleGetRpcMethodDirectory, GSP_SC_GetRpcMethodDirectory, &asn_DEF_GetRpcMethodDirectoryRequestPDU, &asn_DEF_GetRpcMethodDirectoryResponsePDU, &asn_DEF_GetRpcMethodDirectoryErrorPDU}, // 111
    { GspServerRpc::handleGetRpcInterfaceDefinition, GSP_SC_GetRpcInterfaceDefinition, &asn_DEF_GetRpcInterfaceDefinitionRequestPDU, &asn_DEF_GetRpcInterfaceDefinitionResponsePDU, &asn_DEF_GetRpcInterfaceDefinitionErrorPDU}, // 112
    { GspServerRpc::handleGetRpcMethodDefinition, GSP_SC_GetRpcMethodDefinition, &asn_DEF_GetRpcMethodDefinitionRequestPDU, &asn_DEF_GetRpcMethodDefinitionResponsePDU, &asn_DEF_GetRpcMethodDefinitionErrorPDU}, // 113
    { GspServerRpc::handleRpcCall, GSP_SC_RpcCall, &asn_DEF_RpcCallRequestPDU, &asn_DEF_RpcCallResponsePDU, &asn_DEF_RpcCallErrorPDU}, // 114
    {},         // 115,
    {},         // 116,
    {},         // 117,
    {},         // 118,
    {},         // 119,
    {},         // 120,
    {},         // 121,
    {},         // 122,
    {},         // 123,
    {},         // 124,
    {},         // 125,
    {},         // 126,
    {},         // 127,
    { GspServerFile::handleGetFile, GSP_SC_GetFile, &asn_DEF_GetFileRequestPDU, &asn_DEF_GetFileResponsePDU, &asn_DEF_GetFileErrorPDU}, // 128
    { GspServerFile::handleSetFile, GSP_SC_SetFile, &asn_DEF_SetFileRequestPDU, &asn_DEF_SetFileResponsePDU, &asn_DEF_SetFileErrorPDU}, // 129
    { GspServerFile::handleDeleteFile, GSP_SC_DeleteFile, &asn_DEF_DeleteFileRequestPDU, &asn_DEF_DeleteFileResponsePDU, &asn_DEF_DeleteFileErrorPDU}, // 130
    { GspServerFile::handleGetFileAttributeValues, GSP_SC_GetFileAttributeValues, &asn_DEF_GetFileAttributeValuesRequestPDU, &asn_DEF_GetFileAttributeValuesResponsePDU, &asn_DEF_GetFileAttributeValuesErrorPDU}, // 131
    { GspServerFile::handleGetFileDirectory, GSP_SC_GetFileDirectory, &asn_DEF_GetFileDirectoryRequestPDU, &asn_DEF_GetFileDirectoryResponsePDU, &asn_DEF_GetFileDirectoryErrorPDU}, // 132
    {},         // 133,
    {},         // 134,
    {},         // 135,
    {},         // 136,
    {},         // 137,
    {},         // 138,
    {},         // 139,
    {},         // 140,
    {},         // 141,
    {},         // 142,
    {},         // 143,
    {},         // 144,
    {},         // 145,
    {},         // 146,
    {},         // 147,
    {},         // 148,
    {},         // 149,
    {},         // 150,
    {},         // 151,
    {},         // 152,
    { GspServerTest::handleTest, GSP_SC_Test, nullptr, nullptr, nullptr}, // 153
    { GspServerAssociate::handleAssociateNegotiate, GSP_SC_AssociateNegotiate, &asn_DEF_AssociateNegotiateRequestPDU, &asn_DEF_AssociateNegotiateResponsePDU, &asn_DEF_AssociateNegotiateErrorPDU}, // 154
    { GspServerObject::handleGetAllDataDefinition, GSP_SC_GetAllDataDefinition, &asn_DEF_GetAllDataDefinitionRequestPDU, &asn_DEF_GetAllDataDefinitionResponsePDU, &asn_DEF_GetAllDataDefinitionErrorPDU }, // 155
    { GspServerObject::handleGetAllCbValues, GSP_SC_GetAllCBValues, &asn_DEF_GetAllCBValuesRequestPDU, &asn_DEF_GetAllCBValuesResponsePDU, &asn_DEF_GetAllCBValuesErrorPDU }, // 156


};

int callServiceFunc(int index, GspMmsServerConnection self, GspByteBuffer *request, GspByteBuffer *response)
{
    if(index > MAX_FUNC_INDEX || index < 0)
    {
        NLOG_WARN("接收到无效帧类型[{}]请求\n", index);
        return -1;
    }

    const ServiceFuncInfo &funcInfo = funcInfoTable[index];

    if(!funcInfo.func)
    {
        NLOG_WARN("帧类型[{}]请求没有对应的处理方法\n", index);
        return -1;
    }

    if(DEBUG_SERVER){
        NLOG_DEBUG("接受到帧类型[{}]请求, 开始处理\n", index);
    }

    void *requestData = nullptr;
    ServiceError_t error = ServiceError_no_error;
    try
    {
        if(!funcInfo.requestAsn)
        {
            // 对于test帧，直接返回
            IsoConnection_sendGspResp(self->isoConnection, response);
            return 0;
        }

        auto ret = aper_decode_complete(nullptr,
                                        funcInfo.requestAsn,
                                        &requestData,
                                        request->buffer,
                                        request->size
                                        );
        if(ret.code != RC_OK) {
            error = ServiceError_failed_due_to_communications_constraint;
            throw runtime_error("解码[" + to_string(funcInfo.index) + "]类型帧失败\n");
            return -1;
        }
        auto mapping = (GspMmsMapping*)self->server->connectionHandlerParameter;
        auto server = mapping->iedServer;
        auto clientConn = Gsp_private_IedServer_getClientConnectionByHandle(server, self);

        if(is_debug())
        {
            FILE *file = fopen("request_record.log", "a+");
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);

            std::ostringstream oss;
            oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S--------------------------------------------------------");
            auto str = oss.str();
            fprintf(file, "%s %s\n", GspClientConnection_getPeerAddress(clientConn), str.c_str());
            xer_fprint(file, funcInfo.requestAsn, requestData);
            fprintf(file, "----------------------------------------------------------------------------------\n\n");
            fclose(file);
        }


        void* responseData = nullptr;
        if (server->functionHook)
        {
            if(DEBUG_SERVER){
                NLOG_DEBUG("对于[{}]类型请求进行hook处理", index);
            }
            
            int iRet = server->functionHook(server, clientConn, requestData, index, server->functionHookParam, &responseData);
            if (responseData)
            {
                if(DEBUG_SERVER){
                    NLOG_DEBUG("[{}]类型hook回调返回数据，不再由服务端继续处理", index);
                }
            }

            if (iRet < 0)
            {
                if(DEBUG_SERVER){
                    NLOG_DEBUG("[{}]类型hook回调返回处理异常，发送回调异常报文，不再继续处理", index);
                }
                ASN_STRUCT_FREE(*funcInfo.requestAsn, requestData);
                int dVal = GspServer_encodeStructToBuffer(funcInfo.errorAsn, responseData, response);
                if (dVal < 0) {
                    throw runtime_error("编码[" + to_string(funcInfo.index) + "]类型帧失败, 错误代码[" + to_string(dVal) + "]\n");
                    assert(0);
                }
                IsoConnection_sendGspError(self->isoConnection, response);
                ASN_STRUCT_FREE(*funcInfo.errorAsn, responseData);
                return -1;
            }
        }

        if (!responseData)
        {
            responseData = funcInfo.func(self, requestData);
        }

        if(!responseData)
        {
            ASN_STRUCT_FREE(*funcInfo.requestAsn, requestData);
            return 0;
        }

        int dVal = GspServer_encodeStructToBuffer(funcInfo.responseAsn, responseData, response);

        if(dVal < 0) {
            error = ServiceError_failed_due_to_communications_constraint;
            throw runtime_error("编码[" + to_string(funcInfo.index) + "]类型帧失败, 错误代码[" + to_string(dVal) + "]\n");
            assert(0);
        }
        IsoConnection_sendGspResp(self->isoConnection, response);
        //xer_fprint(stdout, funcInfo.responseAsn, responseData);

        if(responseData != requestData)
        {
            ASN_STRUCT_FREE(*funcInfo.responseAsn, responseData);
        }
        ASN_STRUCT_FREE(*funcInfo.requestAsn, requestData);
        return 0;
    }
    catch (void *e)
    {
        ASN_STRUCT_FREE(*funcInfo.requestAsn, requestData);
        GspServer_encodeStructToBuffer(funcInfo.errorAsn, e, response);
        IsoConnection_sendGspError(self->isoConnection, response);
        return -1;
    }
    catch(long e)
    {
        ASN_STRUCT_FREE(*funcInfo.requestAsn, requestData);
        GspServer_encodeStructToBuffer(funcInfo.errorAsn, &e, response);
        IsoConnection_sendGspError(self->isoConnection, response);
        return -1;
    }
    catch(int e)
    {
        ASN_STRUCT_FREE(*funcInfo.requestAsn, requestData);
        GspServer_encodeStructToBuffer(funcInfo.errorAsn, &e, response);
        IsoConnection_sendGspError(self->isoConnection, response);
        return -1;
    }
    catch(const std::exception& e)
    {
        NLOG_WARN(e.what());
        ASN_STRUCT_FREE(*funcInfo.requestAsn, requestData);
        error = ServiceError_failed_due_to_server_constraint;
        GspServer_encodeStructToBuffer(funcInfo.errorAsn, &error, response);
        IsoConnection_sendGspError(self->isoConnection, response);
        return -1;
    }
    return -1;
}
