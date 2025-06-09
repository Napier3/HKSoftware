/*
 *  mms_client_connection.c
 */

#include "libdlt860_platform_includes.h"
#include "gsp_mms_client_connection.h"
#include "iso_client_connection.h"
#include "mms_client_internal.h"
#include "mms_common_internal.h"
#include "stack_config.h"
#include "byte_buffer.h"
#include "gsp_tls_config.h"
#include "GetFileResponsePDU.h"

// 链接默认超时时间
#define CONFIG_MMS_CONNECTION_DEFAULT_TIMEOUT 5000
// 链接超时时间
#define CONFIG_MMS_CONNECTION_DEFAULT_CONNECT_TIMEOUT 10000
// 同时调用的数量
#define OUTSTANDING_CALLS 10


using namespace GSP;

/**
 * @brief setConnectionState 链接状态改变
 * @param self 链接对象
 * @param newState 新的链接状态
 */
static void setConnectionState(GspMmsConnection self, GspMmsConnectionState newState)
{
    GspSemaphore_wait(self->associationStateLock);
    self->connectionState = newState;
    GspSemaphore_post(self->associationStateLock);
    if (self->stateChangedHandler)
        self->stateChangedHandler(self, self->stateChangedHandlerParameter, newState);
}

/**
 * @brief getConnectionState 获取当前的链接状态
 * @param self 链接对象
 * @return 链接状态
 */
static GspMmsConnectionState getConnectionState(GspMmsConnection self)
{
    GspMmsConnectionState state;
    GspSemaphore_wait(self->associationStateLock);
    state = self->connectionState;
    GspSemaphore_post(self->associationStateLock);
    return state;
}

/**
 * @brief handleUnconfirmedMmsPdu 报告处理回调
 */
static void handleUnconfirmedMmsPdu(GspMmsConnection self, GspByteBuffer* message)
{
    if(DEBUG_MMS_CLIENT){
        printf("接受到报告信息: 马上开始处理! \n");
    }

    // 报告解析
    GspLinkedList reportData = nullptr;
    bool ret = mmsClient_parseReportPDU(message, &reportData);
    if(!ret || reportData->empty()){
        Global_LogString("报告解析失败!\n");
        return;
    }

    // mms 回调信息
    uint64_t beginTime = GSP_Hal_getTimeInMs();
    self->reportHandler(self->reportHandlerParameter, reportData);
    uint64_t endTime = GSP_Hal_getTimeInMs();
    printf("ngsp 客户端处理报告花费时间: %lu \n", (endTime - beginTime));
}

static uint16_t getNextInvokeId(GspMmsConnection self)
{
    uint16_t nextInvokeId;
    GspSemaphore_wait(self->nextInvokeIdLock);
    if(self->nextInvokeId >= 65535) {
        self->nextInvokeId = 1;
    } else {
        self->nextInvokeId++;
    }
    nextInvokeId = self->nextInvokeId;
    GspSemaphore_post(self->nextInvokeIdLock);
    return nextInvokeId;
}

static GspMmsOutstandingCall checkForOutstandingCall(GspMmsConnection self, uint32_t invokeId)
{
    int i = 0;
    GspSemaphore_wait(self->outstandingCallsLock);
    for (i = 0; i < OUTSTANDING_CALLS; i++) {
        if (self->outstandingCalls[i].isUsed) {
            if (self->outstandingCalls[i].invokeId == invokeId) {
                GspSemaphore_post(self->outstandingCallsLock);
                return &(self->outstandingCalls[i]);
            }
        }
    }
    GspSemaphore_post(self->outstandingCallsLock);
    return nullptr;
}

static bool addToOutstandingCalls(GspMmsConnection self,
                                  uint32_t invokeId,
                                  GSP_MMS_SC type,
                                  void* userCallback,
                                  void* userParameter,
                                  GspMmsClientInternalParameter internalParameter)
{
    int i = 0;
    GspSemaphore_wait(self->outstandingCallsLock);
    for (i = 0; i < OUTSTANDING_CALLS; i++) {
        if (self->outstandingCalls[i].isUsed == false) {
            self->outstandingCalls[i].isUsed = true;
            self->outstandingCalls[i].invokeId = invokeId;
            self->outstandingCalls[i].timeout = GSP_Hal_getTimeInMs() + self->requestTimeout;
            self->outstandingCalls[i].type = type;
            self->outstandingCalls[i].userCallback = userCallback;
            self->outstandingCalls[i].userParameter = userParameter;
            self->outstandingCalls[i].internalParameter = internalParameter;
            GspSemaphore_post(self->outstandingCallsLock);
            return true;
        }
    }

    GspSemaphore_post(self->outstandingCallsLock);

    return false;
}

static void removeFromOutstandingCalls(GspMmsConnection self, uint32_t invokeId)
{
    int i = 0;
    GspSemaphore_wait(self->outstandingCallsLock);
    for (i = 0; i < OUTSTANDING_CALLS; i++) {
        if (self->outstandingCalls[i].isUsed) {
            if (self->outstandingCalls[i].invokeId == invokeId) {
                self->outstandingCalls[i].isUsed = false;
                break;
            }
        }
    }
    GspSemaphore_post(self->outstandingCallsLock);
}

static void sendMessage(GspMmsConnection self, GspByteBuffer* message)
{
#if (CONFIG_MMS_RAW_MESSAGE_LOGGING == 1)
    if (self->rawMmsMessageHandler != NULL) {
        MmsRawMessageHandler handler = (MmsRawMessageHandler) self->rawMmsMessageHandler;
        handler(self->rawMmsMessageHandlerParameter, message->buffer, message->size, false);
    }
#endif

    GspIsoClientConnection_sendMessage(self->isoClient, message);
}

static GspMmsError sendAsyncRequest(GspMmsConnection self,
                                    uint32_t invokeId,
                                    GspByteBuffer* message,
                                    GSP_MMS_SC type,
                                    void* userCallback,
                                    void* userParameter,
                                    GspMmsClientInternalParameter internalParameter)
{
    // 注册用户事件
    if (addToOutstandingCalls(self, invokeId, type, userCallback, userParameter, internalParameter) == false) {
        GspIsoClientConnection_releaseTransmitBuffer(self->isoClient);
        return GSP_MMS_ERROR_OUTSTANDING_CALL_LIMIT;
    }

    // 发送异步请求
    sendMessage(self, message);
    return GSP_MMS_ERROR_NONE;
}

/**
 * @brief handleGspClientMmsResponseWithPayload 处理客户端mms回应报文(含有数据负载的回应信息)
 * @param self 链接对象
 * @param message 原始数据信息(没有报文头)
 * @param paramInvokID 请求ID
 * @return 处理结果
 */
void handleGspClientMmsResponseWithPayload(GspMmsConnection self,
                                           GspByteBuffer* response,
                                           GspMmsOutstandingCall outstandingCall,
                                           GspMmsError err)
{
    // 默认参数（没有后续数据）
    bool moreFollows = false;
    
    // 接口的区别处理
    switch(outstandingCall->type){
    case GSP_MMS_SC_GetServerDirectory:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetServerDiecttoryResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetLogicDeviceDirectory:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetLogicalDeviceDirectoryResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetLogicNodeDirectory:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseLogicalNodeResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetAllDataDefinition:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetAllDataDefinitionResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetAllDataValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetAllDataValuesResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetAllCBValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetAllCBValuesResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetDataValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetDataValuesResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_SetDataValues:
    {
        // 获取用户端回调
        GspMmsSetDataValuesHandler handler = (GspMmsSetDataValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);

        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseSetDataValuesResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList);
            }
        }
    } break;
    case GSP_MMS_SC_GetDataDefinition:
    {
        // 获取用户端回调
        GspMmsGetDataDefinitionHandler handler = (GspMmsGetDataDefinitionHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {

            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);

        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetDataDefinitionResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetFileDirectory:
    {
        // 获取用户端回调(getFileDirHandler)
        GspMmsConnectionFileDirectoryHandler handler = (GspMmsConnectionFileDirectoryHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息(新获取的文件列表)
            GspLinkedList newFileDir = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetDirecttoryResponse(response, &newFileDir);

            // 处理回调
            if (newFileDir == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err,  nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, newFileDir, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetFile:
    {
        // 获取用户端回调(FileReadHandler)
        GspMmsConnectionFileReadHandler handler = (GspMmsConnectionFileReadHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {
            // 解析回应
            GspLinkedList fileDataPtr = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);
            moreFollows = mmsCLient_parseGetFileResponse(response, &fileDataPtr);

            // 处理回调
            if (fileDataPtr == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err,  nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, fileDataPtr, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetBRCBValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList nameList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetBRCBValuesResponse(response, &nameList);

            // 处理回调
            if (nameList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nameList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_Test:
    {
        printf("收到服务端发来的心跳帧 Test \n");
        // TODO 这里要回复一下服务端一帧心跳信息
    } break;
    case GSP_MMS_SC_SetBRCBValues:
    {
        // 获取用户端回调
        GspSetRCBValuesHandler handler = (GspSetRCBValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseSetBRCBErrorValues(response, &responseValue);

            // 处理回调
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
        }
    } break;
    case GSP_MMS_SC_GetURCBValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList urcbValueList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsCLient_parseGetURCBValuesResponse(response, &urcbValueList);

            // 处理回调
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, urcbValueList, moreFollows);
        }
    } break;
    case GSP_MMS_SC_SetURCBValues:
    {
        // 获取用户端回调
        GspSetRCBValuesHandler handler = (GspSetRCBValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseSetURCBValuesResponse(response, &responseValue);

            // 处理回调
            if (responseValue == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
            }
        }
    } break;
    case GSP_MMS_SC_SelectActiveSG:
    {
        // 获取mms层的用户回调
        GspMmsSelectSGHandler handler = (GspMmsSelectSGHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseSelectActiveSGResponse(response, &responseValue);

            // 处理回调
            if (responseValue == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
            }
        }
    } break;
    case GSP_MMS_SC_SelectEditSG:
    {
        // 获取mms层的用户回调
        GspMmsSGCBValuesHandler handler = (GspMmsSGCBValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseSelectEditSGResponse(response, &responseValue);

            // 处理回调
            if (responseValue == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
            }
        }
    } break;
    case GSP_MMS_SC_GetSGCBValues:
    {
        // 获取mms层的用户回调
        GspMmsSGCBValuesHandler handler = (GspMmsSGCBValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetSGCBValuesResponse(response, &responseValue);

            // 处理回调
            if (responseValue == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
            }
        }
    } break;
    case GSP_MMS_SC_GetEditSGValue:
    {
        // 获取mms层的用户回调
        GspMmsGetEditSGValuesHandler handler = (GspMmsGetEditSGValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetEditSGValueResponse(response, &responseValue);

            // 处理回调
            if (responseValue == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
            }
        }
    } break;
    case GSP_MMS_SC_SetEditSGValue:
    {
        // 获取mms层的用户回调
        GspMmsSetEditSGValuesHandler handler = (GspMmsSetEditSGValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应(对应回调中解析)
            mmsClient_parseSetEditSGValueResponse(response, &responseValue);

            // 处理回调
            if (responseValue == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
            }
        }
    } break;
    case GSP_MMS_SC_ConfirmEditSGValues:
    {
        // 获取mms层的用户回调
        GspMmsConfirmEditSGValuesHandler handler = (GspMmsConfirmEditSGValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应(对应回调中解析)
            mmsClient_parseConfirmEditSGValuesResponse(response, &responseValue);

            // 处理回调
            if (responseValue == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
            }
        }
    } break;
    case GSP_MMS_SC_GetDataSetDirectory:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetDataSetDirectoryResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_GetDataSetValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr, false);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseGetDataSetValuesResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr, false);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList, moreFollows);
            }
        }
    } break;
    case GSP_MMS_SC_Associate:{
        // 获取用户端回调
        GspMmsAssocaiationHandler handler = (GspMmsAssocaiationHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            moreFollows = mmsClient_parseAssociateResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_Select:{
        // 获取用户端回调
        GspMmsSelectHandler handler = (GspMmsSelectHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseSelectResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_Operate:{
        // 获取用户端回调
        GspMmsOperateHandler handler = (GspMmsOperateHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseOpResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_SelectWithValue:{
        // 获取用户端回调
        GspMmsSelectWithValueHandler handler = (GspMmsSelectWithValueHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseSelectWithValueResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_Release:{
        // 获取用户端回调
        GspMmsConcludeAbortHandler handler = (GspMmsConcludeAbortHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->userParameter, err, false);
        } else {
            handler(outstandingCall->userParameter, err, true);
        }
    } break;
    case GSP_MMS_SC_GetRpcInterfaceDirectory:{
        // 获取用户端回调
        GspMmsGetRpcInterfaceDirectoryHandler handler = (GspMmsGetRpcInterfaceDirectoryHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseGetRpcInterfaceDirectoryResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_GetRpcMethodDirectory:{
        // 获取用户端回调
        GspMmsGetRpcMethodDirectoryHandler handler = (GspMmsGetRpcMethodDirectoryHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseGetRpcMethodDirectoryResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_GetRpcInterfaceDefinition:{
        // 获取用户端回调
        GspMmsGetRpcInterfaceDefinitionHandler handler = (GspMmsGetRpcInterfaceDefinitionHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseGetRpcInterfaceDefinitionResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_GetRpcMethodDefinition:{
        // 获取用户端回调
        GspMmsGetRpcMethodDefinitionHandler handler = (GspMmsGetRpcMethodDefinitionHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseGetRpcMethodDefinitionResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_RpcCall:{
        // 获取用户端回调
        GspMmsRpcCallHandler handler = (GspMmsRpcCallHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseRpcCallResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_GetLCBValues:{
        // 获取用户端回调
        GspMmsGetLCBValuesHandler handler = (GspMmsGetLCBValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseGetLCBValuesResponse(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_SetLCBValues:{
        // 获取用户端回调
        GspMmsSetLCBValuesHandler handler = (GspMmsSetLCBValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseSetLCBErrorValues(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    case GSP_MMS_SC_QueryLogByTime:{
        // 获取用户端回调
        GspMmsQueryLogByTimeHandler handler = (GspMmsQueryLogByTimeHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList dataRetList = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseQueryLogByTimeValues(response, &dataRetList);

            // 处理回调
            if (dataRetList == nullptr) {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, GSP_MMS_ERROR_PARSING_RESPONSE, nullptr);
            } else {
                handler(outstandingCall->invokeId, outstandingCall->userParameter, err, dataRetList);
            }
        }
    } break;
    default:
    {
        if(DEBUG_MMS_CLIENT){
            Global_LogString("MMS_CLIENT : 该接口没有实现 \n");
        }
    } break;
    }

    // 移除异步回调
    if (err != GSP_MMS_ERROR_SERVICE_TIMEOUT){
        removeFromOutstandingCalls(self, outstandingCall->invokeId);
    }
}

static inline bool handleGspClientConnectError(GspMmsConnection self,
                                               GspByteBuffer* message,
                                               uint16_t paramInvokID,
                                               uint8_t sc){

    // 错误代码解析
    uint16_t errorCode = (uint16_t)mmsClient_parseServerErrorResponse(message, &paramInvokID);
    if(DEBUG_MMS_CLIENT){
        printf("链接时发生错误: %d \n", errorCode);
    }

    // 错误代码处理
    switch(sc){
    case GSP_MMS_SC_AssociateNegotiate:
    case GSP_MMS_SC_Associate:{
        // 设置链接状态(链接失败)
        setConnectionState(self, GSP_MMS_CONNECTION_STATE_CLOSED);
    } break;
    }
    return true;
}

/**
 * @brief handleGspClientMmsError 处理服务端发过来的错误信息(服务端返回的错误信息)
 * @param self 链接对象
 * @param message 原始数据信息(没有报文头)
 * @param paramInvokID 请求ID
 * @return 处理结果
 */
static inline bool handleGspClientWorkFlowMmsError(GspMmsConnection self,
                                                   GspByteBuffer* message,
                                                   uint16_t paramInvokID,
                                                   GspMmsOutstandingCall outstandingCall,
                                                   uint8_t sc) {
    // 错误判断
    if(!self){
        if(DEBUG_MMS_CLIENT){
            Global_LogString("MMS_CLIENT : 处理服务端错误回应时出现错误 \n");
        }
        return false;
    }

    // 错误代码解析
    uint16_t errorCode = (uint16_t)mmsClient_parseServerErrorResponse(message, &paramInvokID);

    // 错误代码处理
    switch(sc){
    case GSP_MMS_SC_SelectEditSG:
    {
        // 获取mms层的用户回调
        GspMmsSelectSGHandler handler = (GspMmsSelectSGHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_ConfirmEditSGValues:
    {
        // 获取mms层的用户回调
        GspMmsConfirmEditSGValuesHandler handler = (GspMmsConfirmEditSGValuesHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_SetEditSGValue:{
        // 获取mms层的用户回调
        GspMmsSetEditSGValuesHandler handler = (GspMmsSetEditSGValuesHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_GetSGCBValues:
    {
        // 获取mms层的用户回调
        GspMmsSGCBValuesHandler handler = (GspMmsSGCBValuesHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_GetEditSGValue:{
        // 获取mms层的用户回调
        GspMmsGetEditSGValuesHandler handler = (GspMmsGetEditSGValuesHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_SelectActiveSG:
    {
        // 获取mms层的用户回调
        GspMmsSelectSGHandler handler = (GspMmsSelectSGHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_SetURCBValues:
    {
        // 获取用户端回调
        GspSetRCBValuesHandler handler = (GspSetRCBValuesHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_SetBRCBValues:
    {
        // 获取用户端回调
        GspSetRCBValuesHandler handler = (GspSetRCBValuesHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_GetURCBValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetFileDirectory:
    {
        // 获取用户端回调(getFileDirHandler)
        GspMmsConnectionFileDirectoryHandler handler = (GspMmsConnectionFileDirectoryHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetFile:
    {
        // 获取用户端回调(FileReadHandler)
        GspMmsConnectionFileReadHandler handler = (GspMmsConnectionFileReadHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_SetFile:
    {
        // 获取用户端回调(FileReadHandler)
        GspMmsConnectionSetFileHandler handler = (GspMmsConnectionSetFileHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_GetBRCBValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetServerDirectory:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetLogicDeviceDirectory:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetLogicNodeDirectory:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetAllDataDefinition:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetAllDataValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetAllCBValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetDataValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_SetDataValues:
    {
        // 获取用户端回调
        GspMmsSetDataValuesHandler handler = (GspMmsSetDataValuesHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_GetDataDefinition:
    {
        // 获取用户端回调
        GspMmsGetDataDefinitionHandler handler = (GspMmsGetDataDefinitionHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetDataSetValues:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_GetDataSetDirectory:
    {
        // 获取用户端回调
        GspMmsGetModelOrDataHandler handler = (GspMmsGetModelOrDataHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr, false);
    } break;
    case GSP_MMS_SC_Select:
    {
        // 获取用户端回调
        GspMmsSelectHandler handler = (GspMmsSelectHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_Operate:
    {
        // 获取用户端回调
        GspMmsOperateHandler handler = (GspMmsOperateHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_SelectWithValue:
    {
        // 获取用户端回调
        GspMmsSelectWithValueHandler handler = (GspMmsSelectWithValueHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_Release:
    {
        // 获取用户端回调
        GspMmsConcludeAbortHandler handler = (GspMmsConcludeAbortHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), false);
    } break;
    case GSP_MMS_SC_GetRpcInterfaceDirectory:
    {
        // 获取用户端回调
        GspMmsGetRpcInterfaceDirectoryHandler handler = (GspMmsGetRpcInterfaceDirectoryHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_GetRpcMethodDirectory:
    {
        // 获取用户端回调
        GspMmsGetRpcMethodDirectoryHandler handler = (GspMmsGetRpcMethodDirectoryHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_GetRpcInterfaceDefinition:
    {
        // 获取用户端回调
        GspMmsGetRpcInterfaceDefinitionHandler handler = (GspMmsGetRpcInterfaceDefinitionHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_GetRpcMethodDefinition:
    {
        // 获取用户端回调
        GspMmsGetRpcMethodDefinitionHandler handler = (GspMmsGetRpcMethodDefinitionHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_RpcCall:
    {
        // 获取用户端回调
        GspMmsRpcCallHandler handler = (GspMmsRpcCallHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_GetLCBValues:
    {
        // 获取用户端回调
        GspMmsGetLCBValuesHandler handler = (GspMmsGetLCBValuesHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_SetLCBValues:
    {
        // 获取用户端回调
        GspMmsSetLCBValuesHandler handler = (GspMmsSetLCBValuesHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    case GSP_MMS_SC_QueryLogByTime:
    {
        // 获取用户端回调
        GspMmsQueryLogByTimeHandler handler = (GspMmsQueryLogByTimeHandler) outstandingCall->userCallback;

        // 错误处理回调
        handler(outstandingCall->invokeId, outstandingCall->userParameter, static_cast<GspMmsError>(errorCode), nullptr);
    } break;
    default:
    {
        return false;
    }
    }

    return true;
}

/**
 * @brief handleGspClientMmsAuthResponse 处理服务端发过来的回应消息(认证类的回应信息)
 * @param self 链接对象
 * @param message 原始数据信息(没有报文头和reqID)
 * @param paramInvokID 请求ID
 * @return 处理结果
 */
static inline bool handleGspClientMmsAuthResponse(GspMmsConnection self,
                                                  GspByteBuffer* message,
                                                  uint16_t paramInvokID,
                                                  uint8_t sc) {
    // 错误判断
    if(!self){
        if(DEBUG_MMS_CLIENT){
            Global_LogString("MMS_CLIENT : 处理服务端回应时出现错误 \n");
        }
        return false;
    }

    // 对应服务的处理
    switch (sc) {
    case GSP_MMS_SC_AssociateNegotiate:
        // 关联协商应答帧解析
        mmsClient_parseAssociateNegotiateResponse(message, &paramInvokID);
        // 设置链接状态(链接成功)
        setConnectionState(self, GSP_MMS_CONNECTION_STATE_CONNECTED);
        break;
    }
    return true;
}

/**
 * @brief handleGspClientMmsResponseWithNoPayload 处理客户端mms回应报文(不含有数据负载的回应信息)
 * @param self 链接对象
 * @param message 原始数据信息(没有报文头)
 * @param paramInvokID 请求ID
 * @return 处理结果
 */
static inline void handleGspClientMmsResponseWithNoPayload(GspMmsConnection self,
                                                           GspByteBuffer* response,
                                                           GspMmsOutstandingCall outstandingCall,
                                                           GspMmsError err){
    switch(outstandingCall->type) {
    case GSP_MMS_SC_SetBRCBValues:
    {
        // 获取用户端回调
        GspSetRCBValuesHandler handler = (GspSetRCBValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            bool moreFollows = mmsClient_parseSetBRCBErrorValues(response, &responseValue);

            // 处理回调
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
        }
    } break;
    case GSP_MMS_SC_SetURCBValues:
    {
        // 获取用户端回调
        GspSetRCBValuesHandler handler = (GspSetRCBValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            bool moreFollows = mmsClient_parseSetURCBValuesResponse(response, &responseValue);

            // 处理回调
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
        }
    } break;
    case GSP_MMS_SC_SelectActiveSG:
    {
        // 获取mms层的用户回调
        GspMmsSelectSGHandler handler = (GspMmsSelectSGHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseSelectActiveSGResponse(response, &responseValue);

            // 处理回调
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
        }
    } break;
    case GSP_MMS_SC_SelectEditSG:
    {
        // 获取mms层的用户回调
        GspMmsSelectSGHandler handler = (GspMmsSelectSGHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应
            mmsClient_parseSelectEditSGResponse(response, &responseValue);

            // 处理回调
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
        }
    } break;
    case GSP_MMS_SC_SetEditSGValue:
    {
        // 获取mms层的用户回调
        GspMmsSetEditSGValuesHandler handler = (GspMmsSetEditSGValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应(对应回调中解析)
            mmsClient_parseSetEditSGValueResponse(response, &responseValue);

            // 处理回调
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
        }
    } break;
    case GSP_MMS_SC_ConfirmEditSGValues:{
        // 获取mms层的用户回调
        GspMmsConfirmEditSGValuesHandler handler = (GspMmsConfirmEditSGValuesHandler) outstandingCall->userCallback;

        // 处理异常时
        if (err != GSP_MMS_ERROR_NONE) {
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
        } else {

            // 参数信息
            GspLinkedList responseValue = static_cast<GspLinkedList>(outstandingCall->internalParameter.ptr);

            // 解析回应(对应回调中解析)
            mmsClient_parseConfirmEditSGValuesResponse(response, &responseValue);

            // 处理回调
            handler(outstandingCall->invokeId, outstandingCall->userParameter, err, responseValue);
        }
    } break;
    case GSP_MMS_SC_SetFile:
    {
        // 获取用户端回调(SetFileHandler)
        GspMmsConnectionSetFileHandler handler = (GspMmsConnectionSetFileHandler) outstandingCall->userCallback;

        // 处理回调（这里不用解析，正常帧就是木有报文数据）
        handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);
    } break;
    case GSP_MMS_SC_SetDataValues:
    {
        // 获取用户端回调
        GspMmsSetDataValuesHandler handler = (GspMmsSetDataValuesHandler) outstandingCall->userCallback;

        // 处理回调（这里不用解析，这里做错误兼容）
        handler(outstandingCall->invokeId, outstandingCall->userParameter, err, nullptr);

    } break;
    default:
    {
        if(DEBUG_MMS_CLIENT){
            Global_LogString("MMS_CLIENT : 该接口没有实现 \n");
        }
        break;
    }
    }

    // 移除异步回调
    if (err != GSP_MMS_ERROR_SERVICE_TIMEOUT){
        removeFromOutstandingCalls(self, outstandingCall->invokeId);
    }
}

/**
 * @brief handleGspClientMmsRequest 处理服务端发过来的请求消息(服务端发出的请求信息)
 * @param self 链接对象
 * @param message 原始数据信息(没有报文头)
 * @param paramInvokID 请求ID
 * @param errorFlag 错误标记
 * @return
 */
static inline bool handleGspClientMmsRequest(GspMmsConnection self,
                                             GspByteBuffer* message,
                                             uint16_t paramInvokID,
                                             uint8_t sc,
                                             int errorFlag) {
    // 错误兼容
    if(!message){
        return false;
    }

    // 是否有错误代码
    if(errorFlag){

        // 报文调试
        if (DEBUG_MMS_CLIENT){
            Global_LogString("MMS_CLIENT: 服务端发送含有错误代码的请求帧\n");
        }

        return false;
    }

    // 是否有数据负载
    if(GspByteBuffer_getSize(message) < 1){

        // 报文调试
        if (DEBUG_MMS_CLIENT){
            Global_LogString("MMS_CLIENT: 服务端发送不含数据负载的请求帧\n");
        }

        // 心跳
        if(paramInvokID <= 0){
            printf("收到服务端请求的心跳帧 Test \n");
            GspMmsError errorInfo;
            if(GspMmsConnection_test(self, &errorInfo, false)){
                printf("回应服务端请求心跳成功\n");
            } else {
                Global_LogString("回应服务端请求心跳失败\n");
            }

        } else {
            // 报文调试
            if (DEBUG_MMS_CLIENT){
                Global_LogString("MMS_CLIENT: 服务端发送不含数据负载的请求帧, 这里不应该出现这种，放弃处理\n");
            }

            return false;
        }

    } else {

        // 报文调试
        if (DEBUG_MMS_CLIENT){
            Global_LogString("MMS_CLIENT: 服务端发送含有数据负载的请求帧, 这里不应该出现这种，放弃处理\n");
        }

        return false;
    }

    // 错误兼容
    return true;
}

/**
 * @brief handleGspClientMmsResponse 处理服务端发过来的应答消息(服务端返回的应答信息)
 * @param self 链接对象
 * @param message 原始数据信息(没有报文头)
 * @param paramInvokID 请求ID
  * @param errorFlag 错误标记
 * @return
 */
static inline bool handleGspClientMmsResponse(GspMmsConnection self,
                                              GspByteBuffer* message,
                                              uint16_t paramInvokID,
                                              uint8_t sc,
                                              int errorFlag) {
    // 错误兼容
    if(!message){
        return false;
    }

    // 处理认证关联类回应消息(特殊处理)
    if(sc == GSP_MMS_SC_AssociateNegotiate){
        return handleGspClientMmsAuthResponse(self, message, paramInvokID, sc);
    }

    // 是否有错误代码
    if(errorFlag){

        // 报文调试
        if (DEBUG_MMS_CLIENT){
            Global_LogString("MMS_CLIENT: 服务端返回含有错误代码的数据帧\n");
        }

        // 错误类报文处理
        if(sc == GSP_MMS_SC_AssociateNegotiate || sc == GSP_MMS_SC_Associate){
            return handleGspClientConnectError(self, message, paramInvokID, sc);
        } else {
            GspMmsOutstandingCall call = checkForOutstandingCall(self, paramInvokID);
            if (call) {
                if (call->type != GSP_MMS_SC_NONE) {
                    call->isUsed = false;
                    return handleGspClientWorkFlowMmsError(self, message, paramInvokID, call, sc);
                } else {
					Global_LogString("mmsIsoCallback: Service code type does not exist.");
                    return false;
                }
            } else {
				Global_LogString("MMS_CLIENT: When processing a message response with an error code, the corresponding client callback was not found.");
                return false;
            }
        }
    }

    // 是否有数据负载
    if(GspByteBuffer_getSize(message) >= 1) {
        GspMmsOutstandingCall call = checkForOutstandingCall(self, paramInvokID);
        if (call) {
            GspMmsError err = GSP_MMS_ERROR_NONE;
            if (call->type != GSP_MMS_SC_NONE) {
                handleGspClientMmsResponseWithPayload(self, message, call, err);
                return true;
            } else {
                Global_LogString("mmsIsoCallback 服务码类型不存在!\n");
            }
        } else {
            Global_LogString("!!!!!!! 处理报文回应时，没有找到对应的客户端回调 !!!!!!! \n");
            return false;
        }
    } else {
        // 心跳
        if(paramInvokID <= 0){

            printf("收到服务端回应的心跳帧 Test \n");

        } else {

            GspMmsOutstandingCall call = checkForOutstandingCall(self, paramInvokID);
            if (call) {
                GspMmsError err = GSP_MMS_ERROR_NONE;
                if (call->type != GSP_MMS_SC_NONE) {
                    handleGspClientMmsResponseWithNoPayload(self, nullptr, call, err);
                    return true;
                } else {
                    Global_LogString("mmsIsoCallback 处理无数据负载时发现: 服务码类型不存在!\n");
                    return false;
                }
            } else {
                Global_LogString("处理无数据负载时: 没有找到对应的客户端回调\n");
                return false;
            }
        }
    }

    // 错误兼容
    return true;
}

/**
 * @brief mmsIsoCallback mms 回调处理函数
 * @param indication 回调函数索引
 * @param parameter 回调函数参数
 * @param payload 负载数据
 */
static void mmsIsoCallback(GspIsoIndication indication, void* parameter, GspByteBuffer* payload, uint16_t invokID)
{
    // mms 链接信息
    GspMmsConnection self = static_cast<GspMmsConnection>(parameter);

    // 调试信息
    if (DEBUG_MMS_CLIENT){
        if (indication != GSP_ISO_IND_TICK)
            printf("MMS_CLIENT: mmsIsoCallback called with indication %i\n", indication);
    }

    // 定时器回调工作流程
    if (indication == GSP_ISO_IND_TICK) {

        // 获取当前毫秒
        uint64_t currentTime = GSP_Hal_getTimeInMs();
        int i = 0;

        // 检查调用者的请求若是超时了则回复超时信息
        GspSemaphore_wait(self->outstandingCallsLock);
        for (i = 0; i < OUTSTANDING_CALLS; i++) {
            if (self->outstandingCalls[i].isUsed) {
                if (currentTime > self->outstandingCalls[i].timeout) {
                    if (self->outstandingCalls[i].type != GSP_MMS_SC_NONE)
                        handleGspClientMmsResponseWithPayload(self, nullptr, &(self->outstandingCalls[i]), GSP_MMS_ERROR_SERVICE_TIMEOUT);
                    self->outstandingCalls[i].isUsed = false;
                    break;
                }
            }
        }
        GspSemaphore_post(self->outstandingCallsLock);

        // 链接超时时的回调函数
        if (self->concludeHandler != nullptr) {
            if (currentTime > self->concludeTimeout) {
                self->concludeHandler(self->concludeHandlerParameter, GSP_MMS_ERROR_SERVICE_TIMEOUT, false);
                self->concludeHandler = nullptr;
            }
        }
        return;
    }

    // 链接关闭时的回调工作流程
    if (indication == GSP_ISO_IND_CLOSED) {
        if (DEBUG_MMS_CLIENT){
            printf("MMS_CLIENT: mmsIsoCallback: Connection lost or closed by client!\n");
        }

        setConnectionState(self, GSP_MMS_CONNECTION_STATE_CLOSED);
        if (self->connectionLostHandler != nullptr){
            self->connectionLostHandler(self, self->connectionLostHandlerParameter);
        }
        return;
    }

    // 链接关联失败的回调工作流程
    if (indication == GSP_ISO_IND_ASSOCIATION_FAILED) {
        if (DEBUG_MMS_CLIENT)
            printf("MMS_CLIENT: mmsIsoCallback: association failed!\n");
        setConnectionState(self, GSP_MMS_CONNECTION_STATE_CLOSING);
        return;
    }

    // 获取报文头部信息
    GspIsoClientConnection isoClientConnectionPtr = self->isoClient;
    uint8_t sc = GspIsoClientConnection_getGspRequestSc(isoClientConnectionPtr);
    int resp = GspIsoClientConnection_getGspResp(isoClientConnectionPtr);
    int error = GspIsoClientConnection_getGspError(isoClientConnectionPtr);
	self->m_bResponseError = error;//zhouhj 20220101 增加用于记录返回错误
// 	char zfTmpString[256];
// 	sprintf(zfTmpString,"ResponseHeader,ScID(%d),RespID(%d),ErrorID(%d).",sc,resp ,error);
// 	Global_LogString(zfTmpString);

    // 报文调试
    if(DEBUG_MMS_CLIENT){
        printf("****************************** 应答信息头部信息(开始) ************************** \n");
        printf("*  MMS_CLIENT: 报文头：服务码: %i  \n", sc);
        printf("*  MMS_CLIENT: 报文头：回应标记位: %i  \n", resp);
        printf("*  MMS_CLIENT: 报文头：错误标记位: %i  \n", error);
        printf("****************************** 应答信息头部信息(结束) ************************** \n");
        printf("消息ID: %d \n", invokID);
    }

    // 报告类的数据处理
    if(sc == GSP_MMS_SC_Report){
        handleUnconfirmedMmsPdu(self, payload);
        return;
    }

    // 服务端的数据处理(请求\回应)
    if(resp){
        // 处理应答消息
        bool ret = handleGspClientMmsResponse(self, payload, invokID, sc, error);

        // 调试信息
        if(DEBUG_MMS_CLIENT){
            printf("MMS_CLIENT: 处理服务端应答消息, 处理结果 -> %d \n", ret);
        }
    } else {
        // 处理请求信息
        bool ret = handleGspClientMmsRequest(self, payload, invokID, sc, error);

        // 调试信息
        if(DEBUG_MMS_CLIENT){
            printf("MMS_CLIENT: 处理服务端请求消息, 处理结果 -> %d \n", ret);
        }
    }

    // 是否记录原始数据(CONFIG_MMS_RAW_MESSAGE_LOGGING == 1)
#if (CONFIG_MMS_RAW_MESSAGE_LOGGING == 1)
    if (self->rawMmsMessageHandler != nullptr) {
        MmsRawMessageHandler handler = (MmsRawMessageHandler) self->rawMmsMessageHandler;
        handler(self->rawMmsMessageHandlerParameter, buf, payload->size, true);
    }
#endif
}

// mms 链接处理线程的回调函数
#if (CONFIG_MMS_THREADLESS_STACK == 0)
static void* connectionHandlingThread(void* parameter)
{
    // 线程参数
    GspMmsConnection self = (GspMmsConnection) parameter;

    // 线程任务
    while (self->connectionThreadRunning) {
        if (GspMmsConnection_tick(self))
            GspThread_sleep(1);
    }
    return nullptr;
}
#endif

static GspMmsConnection MmsConnection_createInternal(GspTLSConfiguration tlsConfig, bool createThread)
{
#if (CONFIG_MMS_THREADLESS_STACK == 1)
    if (createThread)
        return nullptr;
#endif

    GspMmsConnection self = (GspMmsConnection) GLOBAL_CALLOC(1, sizeof(struct sGspMmsConnection));

    if (self) {

        self->parameters.dataStructureNestingLevel = -1;
        self->parameters.maxServOutstandingCalled = -1;
        self->parameters.maxServOutstandingCalling = -1;
        self->parameters.maxAPDUSize = -1;

        self->parameters.maxAPDUSize = CONFIG_MMS_MAXIMUM_APDU_SIZE;
        self->parameters.maxASDUSize = CONFIG_MMS_MAXIMUM_ASDU_SIZE;

        self->requestTimeout = CONFIG_MMS_CONNECTION_DEFAULT_TIMEOUT;

        self->nextInvokeIdLock = GspSemaphore_create(1);
        self->outstandingCallsLock = GspSemaphore_create(1);
        self->associationStateLock = GspSemaphore_create(1);
        self->connectionState = GSP_MMS_CONNECTION_STATE_CLOSED;

        self->concludeHandler = nullptr;
        self->concludeHandlerParameter = nullptr;
        self->concludeTimeout = 0;

        self->outstandingCalls = (GspMmsOutstandingCall) GLOBAL_CALLOC(OUTSTANDING_CALLS, sizeof(struct sGspMmsOutstandingCall));

        self->isoParameters = GspIsoConnectionParameters_create();
        self->nextInvokeId = 1;

        self->associationId = (unsigned char*)"default";

        /* Load default values for connection parameters */
        GspTSelector tSelector = { 2, { 0, 1 } };
        GspSSelector sSelector = { 2, { 0, 1 } };
        GspPSelector pSelector = { 4, { 0, 0, 0, 1 } };

        GspIsoConnectionParameters_setLocalAddresses(self->isoParameters, pSelector, sSelector, tSelector);
        GspIsoConnectionParameters_setLocalApTitle(self->isoParameters, "1.1.1.999", 12);
        GspIsoConnectionParameters_setRemoteAddresses(self->isoParameters, pSelector, sSelector, tSelector);
        GspIsoConnectionParameters_setRemoteApTitle(self->isoParameters, "1.1.1.999.1", 12);

        self->connectTimeout = CONFIG_MMS_CONNECTION_DEFAULT_CONNECT_TIMEOUT;
        self->isoClient = GspIsoClientConnection_create(self->isoParameters, (GspIsoIndicationCallback) mmsIsoCallback, (void*) self);

#if (CONFIG_MMS_THREADLESS_STACK == 0)
        self->createThread = createThread;
        self->connectionHandlingThread = nullptr;
        self->connectionThreadRunning = false;
#endif
    }

    return self;
}

GspMmsConnection GspMmsConnection_create()
{
    return MmsConnection_createInternal(nullptr, true);
}

GspMmsConnection GspMmsConnection_createSecure(GspTLSConfiguration tlsConfig)
{
    return MmsConnection_createInternal(tlsConfig, true);
}

GspMmsConnection GspMmsConnection_createNonThreaded(GspTLSConfiguration tlsConfig)
{
    return MmsConnection_createInternal(tlsConfig, false);
}

void GspMmsConnection_destroy(GspMmsConnection self)
{
    // 判断是否释放线程信息
#if (CONFIG_MMS_THREADLESS_STACK == 0)
    if (self->createThread) {
        if (self->connectionHandlingThread) {
            if (self->connectionThreadRunning) {
                self->connectionThreadRunning = false;
                GspThread_destroy(self->connectionHandlingThread);
                self->connectionHandlingThread = nullptr;
            }
        }
    }
#endif

    // 释放iso链接信息
    if (self->isoClient != nullptr)
        GspIsoClientConnection_destroy(self->isoClient);

    // 释放iso链接参数信息
    if (self->isoParameters != nullptr)
        GspIsoConnectionParameters_destroy(self->isoParameters);

    // 释放信号量信息
    GspSemaphore_destroy(self->nextInvokeIdLock);
    GspSemaphore_destroy(self->outstandingCallsLock);
    GspSemaphore_destroy(self->associationStateLock);

    // 释放接口调用信息
    GLOBAL_FREEMEM(self->outstandingCalls);

    // 释放文件服务相关信息
#if (MMS_OBTAIN_FILE_SERVICE == 1)
#if (CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME == 1)
    if (self->filestoreBasepath != nullptr)
        GLOBAL_FREEMEM(self->filestoreBasepath);
#endif
#endif

    GLOBAL_FREEMEM(self);
}

void GspMmsConnection_setFilestoreBasepath(GspMmsConnection self, const char* basepath)
{
#if (MMS_OBTAIN_FILE_SERVICE == 1)
#if (CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME == 1)
    if (self->filestoreBasepath != nullptr) {
        GLOBAL_FREEMEM(self->filestoreBasepath);
        self->filestoreBasepath = nullptr;
    }

    if (basepath != nullptr)
        self->filestoreBasepath = StringUtils_copyString(basepath);
#endif
#endif
}

char* MmsConnection_getFilestoreBasepath(GspMmsConnection self)
{
#if (MMS_OBTAIN_FILE_SERVICE == 1)
#if (CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME == 1)
    if (self->filestoreBasepath != nullptr)
        return self->filestoreBasepath;
    else
        return StringUtils_createStringFromBuffer((uint8_t*)CONFIG_VIRTUAL_FILESTORE_BASEPATH, strlen(CONFIG_VIRTUAL_FILESTORE_BASEPATH));
#else
    return CONFIG_VIRTUAL_FILESTORE_BASEPATH;
#endif

#else
    return CONFIG_VIRTUAL_FILESTORE_BASEPATH;
#endif
}

void GspMmsConnection_setRawMessageHandler(GspMmsConnection self, GspMmsRawMessageHandler handler, void* parameter)
{
#if (CONFIG_MMS_RAW_MESSAGE_LOGGING == 1)
    self->rawMmsMessageHandler = (void*) handler;
    self->rawMmsMessageHandlerParameter = parameter;
#endif
}

void GspMmsConnection_setConnectionLostHandler(GspMmsConnection self, GspMmsConnectionLostHandler handler, void* handlerParameter)
{
    self->connectionLostHandler = handler;
    self->connectionLostHandlerParameter = handlerParameter;
}

void GspMmsConnection_setConnectionStateChangedHandler(GspMmsConnection self, GspMmsConnectionStateChangedHandler handler, void* parameter)
{
    self->stateChangedHandler = handler;
    self->stateChangedHandlerParameter = parameter;
}

void GspMmsConnection_setRequestTimeout(GspMmsConnection self, uint32_t timeoutInMs)
{
    self->requestTimeout = timeoutInMs;
}

uint32_t GspMmsConnection_getRequestTimeout(GspMmsConnection self)
{
    return self->requestTimeout;
}

void GspMmsConnection_setConnectTimeout(GspMmsConnection self, uint32_t timeoutInMs)
{
    self->connectTimeout = timeoutInMs;
}

void MmsConnection_setLocalDetail(GspMmsConnection self, int32_t localDetail)
{
    self->parameters.maxAPDUSize = localDetail;
}

int32_t MmsConnection_getLocalDetail(GspMmsConnection self)
{
    return self->parameters.maxAPDUSize;
}

GspIsoConnectionParameters GspMmsConnection_getIsoConnectionParameters(GspMmsConnection self)
{
    return self->isoParameters;
}

GspMmsConnectionParameters GspMmsConnection_getMmsConnectionParameters(GspMmsConnection self)
{
    return self->parameters;
}

/**
 * @brief The connectParameters struct 链接相关的参数
 */
struct connectParameters
{
    // 信号量
    GspSemaphore sem;
    // 链接状态
    GspMmsConnectionState state;
    // 链接状态改变时的回调函数
    GspMmsConnectionStateChangedHandler originalHandler;
    // 链接状态改变时回调函数的参数
    void* originalParameter;
};

/**
 * @brief internalConnectionStateChangedHandler 内部默认的链接状态改变的回调函数
 * @param connection 链接对象
 * @param parameter 回调参数
 * @param newState 新的链接状态
 */
static void internalConnectionStateChangedHandler (GspMmsConnection connection, void* parameter, GspMmsConnectionState newState)
{
    struct connectParameters* conParams = (struct connectParameters*) parameter;

    if ((newState == GSP_MMS_CONNECTION_STATE_CLOSED) || (newState == GSP_MMS_CONNECTION_STATE_CONNECTED))
    {
        conParams->state = newState;
        GspSemaphore_post(conParams->sem);
    } else {
        if (conParams->originalHandler){
            conParams->originalHandler(connection, conParams->originalParameter, newState);
        }
    }
}

bool GspMmsConnection_connect(GspMmsConnection self, GspMmsError* mmsError, const char* serverName, int serverPort,const char* local_address)
{
    // 链接结果
    bool success = false;

    // 链接参数
    struct connectParameters conParams;

    // 设置链接参数
    conParams.sem = GspSemaphore_create(1);
    conParams.state = GSP_MMS_CONNECTION_STATE_CONNECTING;
    conParams.originalHandler = self->stateChangedHandler;
    conParams.originalParameter = self->stateChangedHandlerParameter;
    GspSemaphore_wait(conParams.sem);

    // 设置状态改变时的回调函数(临时使用默认的)
    self->stateChangedHandler = internalConnectionStateChangedHandler;
    self->stateChangedHandlerParameter = &conParams;

    // 链接到服务端(异步)
    GspMmsError err;
    GspMmsConnection_connectAsync(self, &err, serverName, serverPort,local_address);
    if (err == GSP_MMS_ERROR_NONE) {

        // 等待对方回应
        GspSemaphore_wait(conParams.sem);

        // 结果处理
        if (conParams.state == GSP_MMS_CONNECTION_STATE_CONNECTED) {
            *mmsError = GSP_MMS_ERROR_NONE;
            success = true;
        } else {
            *mmsError = GSP_MMS_ERROR_CONNECTION_REJECTED;
        }

        // 内部回调
        if (conParams.originalHandler) {
            conParams.originalHandler(self, conParams.originalParameter, conParams.state);
        }

    } else {
        *mmsError = err;
    }

    // 释放资源
    GspSemaphore_destroy(conParams.sem);

    // 设置状态改变时的回调函数(改回用户指定的)
    self->stateChangedHandler = conParams.originalHandler;
    self->stateChangedHandlerParameter = conParams.originalParameter;

    return success;
}

void GspMmsConnection_connectAsync(GspMmsConnection self, GspMmsError* mmsError, const char* serverName, int serverPort,const char* local_address)
{
    // 服务端口
    if (serverPort == -1) {
#if (CONFIG_MMS_SUPPORT_TLS == 1)
        if (self->isoParameters->tlsConfiguration)
            serverPort = 9102;
        else
            serverPort = 8102;
#else
        serverPort = 8102;
#endif
    }

    // 是否创建线程
#if (CONFIG_MMS_THREADLESS_STACK == 0)
    if (self->createThread) {
        if (self->connectionHandlingThread == nullptr) {

            self->connectionHandlingThread = GspThread_create(connectionHandlingThread, self, false);
            self->connectionThreadRunning = true;
            GspThread_start(self->connectionHandlingThread);
        }
    }
#endif

    // 设置客户端链接参数
    GspIsoConnectionParameters_setTcpParameters(self->isoParameters, serverName, serverPort);

    // 设置最大的 apdu size
    if (self->parameters.maxAPDUSize == -1)
        self->parameters.maxAPDUSize = CONFIG_MMS_MAXIMUM_APDU_SIZE;

    // 设置最大的 asdu size
    if (self->parameters.maxASDUSize == -1)
        self->parameters.maxASDUSize = CONFIG_MMS_MAXIMUM_ASDU_SIZE;

    // 获取一个发送缓冲区
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);

    // 构造关联请求帧数据
    mmsClient_createAssociateNegotiateRequest(self, payload, 1 , (uint16_t)self->parameters.maxAPDUSize, (uint16_t)self->parameters.maxASDUSize);

    // 建立 TCP 链接
    if (GspIsoClientConnection_associateAsync(self->isoClient, self->connectTimeout, self->requestTimeout,local_address)) {

        // 修改链接状态
        setConnectionState(self, GSP_MMS_CONNECTION_STATE_CONNECTING);
        *mmsError = GSP_MMS_ERROR_NONE;

    } else {
        *mmsError = GSP_MMS_ERROR_OTHER;
    }
}

bool GspMmsConnection_tick(GspMmsConnection self)
{
    return GspIsoClientConnection_handleConnection(self->isoClient);
}

/**
 * @brief MmsConnection_close mms 链接关闭
 * @param self
 */
void GspMmsConnection_close(GspMmsConnection self)
{
    self->connectionLostHandler = nullptr;
    if (getConnectionState(self) == GSP_MMS_CONNECTION_STATE_CONNECTED)
        GspIsoClientConnection_close(self->isoClient);
}

/**
 * @brief MmsConnection_abort 链接终止
 * @param self 链接对象
 * @param mmsError 错误信息
 */
void GspMmsConnection_abort(GspMmsConnection self, GspMmsError* mmsError, uint8_t reasonCode, uint8_t* associationId)
{
    *mmsError = GSP_MMS_ERROR_NONE;
    self->connectionLostHandler = nullptr;

    if (getConnectionState(self) == GSP_MMS_CONNECTION_STATE_CONNECTED) {

        // 获取一个发送缓冲区
        GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);

        // 获取invokid
        uint16_t invokeId = getNextInvokeId(self);

        // 构造链接中止的报文
        mmsClient_createAbortRequest(self, payload, invokeId, reasonCode, associationId);

        // iso 层链接中止且发送数据
        GspIsoClientConnection_abortAsync(self->isoClient);
        GspIsoClientConnection_close(self->isoClient);

        *mmsError = GSP_MMS_ERROR_NONE;
    } else {
        *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
    }
}

struct concludeParameters
{
    GspSemaphore waitForResponse;
    GspMmsError err;
    bool success;
};

static void concludeHandler(void* parameter, GspMmsError mmsError, bool success)
{
    struct concludeParameters* parameters = (struct concludeParameters*) parameter;
    parameters->err = mmsError;
    parameters->success = success;
    GspSemaphore_post(parameters->waitForResponse);
}

void GspMmsConnection_conclude(GspMmsConnection self, GspMmsError* mmsError, uint8_t* associationId)
{
    GspMmsError err = GSP_MMS_ERROR_NONE;
    GspMmsConnection_concludeAsync(self, &err,associationId);
    if (mmsError){
        *mmsError = err;
    }
}

void GspMmsConnection_concludeAsync(GspMmsConnection self,
                                    GspMmsError* mmsError,
                                    uint8_t* associationId)
{
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return;
    }

    *mmsError = GSP_MMS_ERROR_NONE;

    // 获取内存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);

    // 获取invokid
    uint16_t invokeId = getNextInvokeId(self);

    // 创建取消请求包
    mmsClient_createConcludeRequest(self, payload, invokeId, associationId);

    // 请求参数
    struct concludeParameters reqParameter;
    reqParameter.waitForResponse = GspSemaphore_create(1);;
    reqParameter.success = false;
    reqParameter.err = GSP_MMS_ERROR_NONE;
    self->concludeTimeout = GSP_Hal_getTimeInMs() + self->requestTimeout;
    GspSemaphore_wait(reqParameter.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;

    // 发送请求数据
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_Release, (void*)concludeHandler, &reqParameter, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(reqParameter.waitForResponse);
        *mmsError = reqParameter.err;
    }
    GspSemaphore_destroy(reqParameter.waitForResponse);

}

// 关联请求信息
struct GetAssociationParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void AssociationHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct GetAssociationParameters* parameters = (struct GetAssociationParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

char* GspMmsConnection_associationAsync(GspMmsConnection self,
                                        GspMmsError* mmsError,
                                        const char* paramServerAccessPointReference){
    // 错误代码
    *mmsError = GSP_MMS_ERROR_NONE;

    // 获取内存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);

    // 获取invokid
    uint16_t invokeId = getNextInvokeId(self);

    // 创建关联请求
    if(mmsClient_createAssociateRequest(self, payload, invokeId, (uint8_t*)paramServerAccessPointReference)){
        if(DEBUG_MMS_CLIENT){
            printf("创建获取关联请求帧成功 \n");
        }
    } else {
        if(DEBUG_MMS_CLIENT){
            Global_LogString("创建获取关联请求帧失败 \n");
        }
    }

    // 初始化请求参数
    GetAssociationParameters requestParam;
    memset(&requestParam, 0, sizeof(GetAssociationParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;

    // 发送请求数据
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_Associate, (void*)AssociationHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        GspLinkedList retList = requestParam.dataRetList;
        if(retList){
            if(GspLinkedList_size(retList)>0){
                AssociateResponsePDU* responsePDU = (AssociateResponsePDU*)GspLinkedList_get(retList, 0);
                printf("关联ID: %s\n", responsePDU->associationId.buf);
                printf("关联错误代码: %ld\n", responsePDU->serviceError);
                char* associateID = (char*)GspMemory_calloc(responsePDU->associationId.size+1, sizeof (char));
                memcpy(associateID, responsePDU->associationId.buf, responsePDU->associationId.size);
                ASN_STRUCT_FREE(asn_DEF_AssociateResponsePDU, responsePDU);
                GspLinkedList_destroyStatic(retList);
                return associateID;
            }
        }
    }
    return nullptr;
}

void GspMmsConnection_setInformationReportHandler(GspMmsConnection self, GspMmsInformationReportHandler handler, void* parameter)
{
    self->reportHandler = handler;
    self->reportHandlerParameter = parameter;
}


/************************************************* 获取数据类信息接口 **************************************************/

/**
 * @brief mmsClient_getDataAndModelTaskRequestAsync 获取名字列表异步请求
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param domainId 域名ID
 * @param objectClass 服务码
 * @param continueAfter 开始的名字参数(获取其后续的数据)
 * @param handler 数据处理的回调指针
 * @param parameter 回调函数的参数
 * @param nameList 返回的数据列表
 * @param paramObjType 调用数据类型
 * @param paramFC 功能约束
 * @return 消息ID
 */
static uint32_t mmsClient_getDataAndModelTaskRequestAsync(
        GspMmsConnection self,
        GspMmsError* mmsError,
        const char* refs,
        GSP_MMS_SC serverCode,
        const char* continueAfter,
        GspMmsGetModelOrDataHandler handler,
        void* parameter,
        GspLinkedList retDataList,
        GspACSICLASS paramObjType,
        GspFunctionalConstraint paramFC,
        GspRefType paramRefType)
{
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return invokeId;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    if (serverCode == GSP_MMS_SC_GetServerDirectory) {
        if(mmsClient_createGetServerDirectoryRequest(self, payload, invokeId, continueAfter)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建获取服务器目录的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建获取服务器目录的数据帧失败！\n");
            return invokeId;
        }
    } else if(serverCode == GSP_MMS_SC_GetLogicDeviceDirectory){
        if(mmsClient_createGetLogicalDeviceDirectoryRequest(self, payload, invokeId, refs,continueAfter)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建获取逻辑设设备的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建获取逻辑设设备的数据帧失败！\n");
            return invokeId;
        }
    } else if(serverCode == GSP_MMS_SC_GetLogicNodeDirectory) {
        if(mmsClient_createGetLogicalNodeRequest(self, payload, invokeId, refs,continueAfter, paramObjType)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建获取逻辑节点的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建获取逻辑节点的数据帧失败！\n");
            return invokeId;
        }
    } else if(serverCode == GSP_MMS_SC_GetAllDataDefinition) {
        if(mmsClient_createGetAllDataDefinitionRequest(self, payload, invokeId, refs,continueAfter, paramFC, paramRefType)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建获取数据定义的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建获取所有数据定义的数据帧失败！\n");
            return invokeId;
        }
    } else if(serverCode == GSP_MMS_SC_GetAllDataValues){
        if(mmsClient_createGetAllDataValuesRequest(self, payload, invokeId, refs, continueAfter, paramFC, paramRefType)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建获取数据值的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建获取所有数据值的数据帧失败！\n");
            return invokeId;
        }
    } else if(serverCode == GSP_MMS_SC_GetAllCBValues){
        if(mmsCLient_createGetAllCBValuesRequest(self, payload, invokeId, refs, continueAfter, paramRefType, paramObjType)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建读所有控制块值的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建读所有控制块值的数据帧失败！\n");
            return invokeId;
        }
    } else if(serverCode == GSP_MMS_SC_GetBRCBValues){
        if(mmsClient_createGetBRCBValuesRequest(self, payload, invokeId, refs)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建获取缓存报告控制块值的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建获取缓存报告控制块值的数据帧失败！\n");
            return invokeId;
        }
    } else if(serverCode == GSP_MMS_SC_GetURCBValues){
        if(mmsClient_createGetURCBValuesRequest(self, payload, invokeId, refs)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建获取非缓存报告控制块值的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建获取非缓存报告控制块值的数据帧失败！\n");
            return invokeId;
        }
    } else if(serverCode == GSP_MMS_SC_GetDataSetDirectory){
        if(mmsClient_createGetDataSetDirectoryRequest(self, payload, invokeId, refs)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建获取数据集目录值的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建获取数据集目录值的数据帧失败！\n");
        }
    } else if(serverCode == GSP_MMS_SC_GetDataSetValues){
        if(mmsClient_createGetDataSetValuesRequest(self, payload, invokeId, refs)){
            if(DEBUG_MMS_CLIENT)
                printf("MMS_CLIENT：创建获取数据集值的数据帧正确！\n");
        } else {
            if(DEBUG_MMS_CLIENT)
                Global_LogString("MMS_CLIENT：创建获取数据集值的数据帧失败！\n");
        }
    }

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = retDataList;
    GspMmsError err = sendAsyncRequest(self, invokeId, payload, serverCode, (void*)handler, parameter, intParam);

    // 错误代码
    if (mmsError)
        *mmsError = err;

    return invokeId;
}

struct getDataOrModelParameters
{
    // 信号量
    GspSemaphore sem;
    // 错误信息
    GspMmsError err;
    // 模型列表
    GspLinkedList dataList;
    // 是否有后续数据
    bool moreFollows;
};

/**
 * @brief getModelOrDataWorkflowHandler 获取模型名字列表的工作流默认回调函数
 * (用于使阻塞的函数获取到数据结果并继续执行)
 * @param invokeId 消息ID
 * @param parameter 参数信息
 * @param mmsError 错误信息
 * @param nameList 数据列表结果
 * @param moreFollows 是否有更多的数据
 */
static void getModelOrDataWorkflowHandler(uint32_t invokeId, 
                                          void* parameter,
                                          GspMmsError mmsError,
                                          GspLinkedList nameList,
                                          bool moreFollows)
{
    struct getDataOrModelParameters* parameters = (struct getDataOrModelParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataList = nameList;
    parameters->moreFollows = moreFollows;
    GspSemaphore_post(parameters->sem);
}

/**
 * @brief mmsClient_getNameList 获取模型列表, 当有后续帧时，以此获取直至帧尾
 * @param self 链接对象
 * @param mmsError 链接错误信息
 * @param domainId 逻辑设备名字
 * @param objectClass 服务码
 * @param paramObjType 对象类型
 * @param paramFC 功能约束
 * @return 模型或者数据列表
 */
static GspLinkedList mmsClient_getDataWorkflow(GspMmsConnection self,
                                               GspMmsError *mmsError,
                                               const char* refs,
                                               GSP_MMS_SC objectClass,
                                               GspACSICLASS paramObjType,
                                               GspFunctionalConstraint paramFC,
                                               GspRefType paramRefType)
{
    // 异步请求参数
    GspLinkedList list = nullptr;
    bool moreFollows = false;
    struct getDataOrModelParameters parameter;
    GspMmsError err = GSP_MMS_ERROR_NONE;
    parameter.sem = GspSemaphore_create(1);;
    parameter.moreFollows = false;
    parameter.dataList = nullptr;
    GspSemaphore_wait(parameter.sem);

    // 异步的获取数据
    mmsClient_getDataAndModelTaskRequestAsync(self,
                                              &err,
                                              refs,
                                              objectClass,
                                              nullptr,
                                              getModelOrDataWorkflowHandler,
                                              &parameter,
                                              nullptr,
                                              paramObjType,
                                              paramFC,
                                              paramRefType);

    // 同步的等待结果
    if (err == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(parameter.sem);
        err = parameter.err;
        list = parameter.dataList;
        moreFollows = parameter.moreFollows;
    }
    GspSemaphore_destroy(parameter.sem);

    // 获取后续的所有数据
    while (moreFollows) {
        parameter.sem = GspSemaphore_create(1);
        char* continueAfter = nullptr;
        if (list) {
            void* elem_item = GspLinkedList_getLastElement(list);
            switch (objectClass)
            {
            case GSP_MMS_SC_GetAllDataDefinition:
            {
                GetAllDataDefinitionResponsePDU_t* elem_ret = static_cast<GetAllDataDefinitionResponsePDU_t*>(elem_item);
                GetAllDataDefinitionResponsePDU__data__Member* data_item = elem_ret->data.list.array[elem_ret->data.list.count - 1];
                continueAfter = (char*)(data_item->reference.buf);
            } break;
            case GSP_MMS_SC_GetAllDataValues:
            {
                GetAllDataValuesResponsePDU_t* elem_ret = static_cast<GetAllDataValuesResponsePDU_t*>(elem_item);
                GetAllDataValuesResponsePDU__data__Member* data_item = elem_ret->data.list.array[elem_ret->data.list.count - 1];
                continueAfter = (char*)(data_item->reference.buf);
            } break;
            case GSP_MMS_SC_GetAllCBValues:
            {
                GetAllCBValuesResponsePDU_t* elem_ret = static_cast<GetAllCBValuesResponsePDU_t*>(elem_item);
                GetAllCBValuesResponsePDU__cbValue__Member* data_item = elem_ret->cbValue.list.array[elem_ret->cbValue.list.count - 1];
                continueAfter = (char*)(data_item->reference.buf);
            } break;
            case GSP_MMS_SC_GetDataSetDirectory:
            {
                GetDataSetDirectoryResponsePDU_t* elem_ret = static_cast<GetDataSetDirectoryResponsePDU_t*>(elem_item);
                GetDataSetDirectoryResponsePDU__memberData__Member* data_item = elem_ret->memberData.list.array[elem_ret->memberData.list.count - 1];
                continueAfter = (char*)(data_item->reference.buf);
            } break;
            case GSP_MMS_SC_GetBRCBValues:
            {
                GetBRCBValuesResponsePDU_t* elem_ret = static_cast<GetBRCBValuesResponsePDU_t*>(elem_item);
                GetBRCBValuesResponsePDU__brcb__Member* data_item = elem_ret->brcb.list.array[elem_ret->brcb.list.count - 1];
                if(data_item->present == GetBRCBValuesResponsePDU__brcb__Member_PR_value)
                {
                    continueAfter = (char*)(data_item->choice.value.rptID.buf);
                } else {
                    return list;
                }
            } break;
            default:
                continueAfter = static_cast<char*>(elem_item);
                break;
            }
        }
        GspSemaphore_wait(parameter.sem);
        mmsClient_getDataAndModelTaskRequestAsync(self,
                                                  &err,
                                                  refs,
                                                  objectClass,
                                                  continueAfter,
                                                  getModelOrDataWorkflowHandler,
                                                  &parameter,
                                                  list,
                                                  paramObjType,
                                                  paramFC,
                                                  paramRefType);
        if (err == GSP_MMS_ERROR_NONE) {
            GspSemaphore_wait(parameter.sem);
            err = parameter.err;
            list = parameter.dataList;
            moreFollows = parameter.moreFollows;
        }
        GspSemaphore_destroy(parameter.sem);
    }

    if (mmsError)
        *mmsError = err;

    if (err != GSP_MMS_ERROR_NONE) {
        if (list) {
            GspLinkedList_destroy(list);
            list = nullptr;
        }
    }

    return list;
}

GspLinkedList GspMmsConnection_getServerDirectory(GspMmsConnection self,
                                                  GspMmsError* mmsError)
{
    return mmsClient_getDataWorkflow(self, mmsError, nullptr, GSP_MMS_SC_GetServerDirectory, GSP_ACSIClass_reserved, DLT860_FC_NONE, NOTHING);
}

GspLinkedList GspMmsConnection_getLogicDevices(GspMmsConnection self,
                                               GspMmsError* mmsError,
                                               const char* paramLDName){
    return mmsClient_getDataWorkflow(self, mmsError, paramLDName, GSP_MMS_SC_GetLogicDeviceDirectory, GSP_ACSIClass_reserved, DLT860_FC_NONE, LDNAME);
}

GspLinkedList GspMmsConnection_getLogicalNodeDirectory(GspMmsConnection self,
                                                       GspMmsError* mmsError,
                                                       GspACSICLASS paramClass,
                                                       const char* reference){
    return mmsClient_getDataWorkflow(self, mmsError, reference, GSP_MMS_SC_GetLogicNodeDirectory, paramClass, DLT860_FC_NONE, LNREFERENCE);
}

GspLinkedList GspMmsConnection_getAllDataDefinition(GspMmsConnection self,
                                                    GspMmsError* mmsError,
                                                    GspFunctionalConstraint paramFc,
                                                    const char* reference,
                                                    GspRefType paramRefType){
    return mmsClient_getDataWorkflow(self, mmsError, reference, GSP_MMS_SC_GetAllDataDefinition, GSP_ACSIClass_reserved, paramFc, paramRefType);
}

GspLinkedList GspMmsConnection_getAllDataValues(GspMmsConnection self,
                                                GspMmsError* mmsError,
                                                GspFunctionalConstraint paramFc,
                                                const char* reference,
                                                GspRefType paramRefType){
    return mmsClient_getDataWorkflow(self, mmsError, reference, GSP_MMS_SC_GetAllDataValues, GSP_ACSIClass_reserved, paramFc, paramRefType);
}


GspLinkedList GspMmsConnection_getAllCBValues(GspMmsConnection self,
                                              GspMmsError* mmsError,
                                              GspACSICLASS paramClass,
                                              const char* reference,
                                              GspRefType paramRefType){
    return mmsClient_getDataWorkflow(self, mmsError, reference, GSP_MMS_SC_GetAllCBValues, paramClass, DLT860_FC_NONE, paramRefType);
}

/************************************************* 读取一个或多个数据信息 ******************************************/

// 获取值请求信息
struct GetDataValuesParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void GetDataValuesHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct GetDataValuesParameters* parameters = (struct GetDataValuesParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_getDataValues(GspMmsConnection self,
                                             GspMmsError* mmsError,
                                             GspLinkedList refsFcList){
    // 消息ID
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsCLient_createGetDataValuesRequest(self, payload, invokeId, refsFcList)){
        if(DEBUG_MMS_CLIENT){
            printf("创建获取数据值请求帧成功 \n");
        }
    } else {
        if(DEBUG_MMS_CLIENT){
            Global_LogString("创建获取数据值请求帧失败 \n");
        }
    }

    // 初始化请求参数
    GetDataValuesParameters requestParam;
    memset(&requestParam, 0 , sizeof(GetDataValuesParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetDataValues, (void*)GetDataValuesHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // TODO 这里可能需要处理 moreflow

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

// 写值请求信息
struct SetDataValuesParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void SetDataValuesHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct GetDataValuesParameters* parameters = (struct GetDataValuesParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_setDataValues(GspMmsConnection self,
                                             GspMmsError* mmsError,
                                             GspLinkedList dataRefsFcList){
    // 消息ID
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsCLient_createSetDataValuesRequest(self, payload, invokeId, dataRefsFcList)){
        if(DEBUG_MMS_CLIENT){
            printf("创建写数据值请求帧成功 \n");
        }
    } else {
        if(DEBUG_MMS_CLIENT){
            Global_LogString("创建写数据值请求帧失败 \n");
        }
    }

    // 初始化请求参数
    SetDataValuesParameters requestParam;
    memset(&requestParam, 0 , sizeof(SetDataValuesParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_SetDataValues, (void*)SetDataValuesHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

// 获取数据定义请求信息
struct GetDataDefinitionParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void GetDataDefinitionHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct GetDataDefinitionParameters* parameters = (struct GetDataDefinitionParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_getDataDefinition(GspMmsConnection self,
                                                 GspMmsError* mmsError,
                                                 GspLinkedList refsFcList){
    // 消息ID
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsCLient_createGetDataDefinitionRequest(self, payload, invokeId, refsFcList)){
        if(DEBUG_MMS_CLIENT){
            printf("创建获取数据定义请求帧成功 \n");
        }
    } else {
        if(DEBUG_MMS_CLIENT){
            Global_LogString("创建获取数据定义请求帧失败 \n");
        }
    }

    // 初始化请求参数
    GetDataDefinitionParameters requestParam;
    memset(&requestParam, 0 , sizeof(GetDataDefinitionParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetDataDefinition, (void*)GetDataDefinitionHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE){
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

/************************************************* 获取数据集目录信息 ***********************************************/

GspLinkedList GspMmsConnection_getDataSetDirectory(GspMmsConnection self,
                                                   GspMmsError* mmsError,
                                                   const char* paramReference){
    return mmsClient_getDataWorkflow(self, mmsError, paramReference, GSP_MMS_SC_GetDataSetDirectory, GSP_ACSIClass_reserved, DLT860_FC_NONE, NOTHING);
}

GspLinkedList GspMmsConnection_getDataSetValues(GspMmsConnection self,
                                                GspMmsError* mmsError,
                                                const char* paramReference){
    return mmsClient_getDataWorkflow(self, mmsError, paramReference, GSP_MMS_SC_GetDataSetValues, GSP_ACSIClass_reserved, DLT860_FC_NONE, NOTHING);
}

/************************************************* 获取文件目录信息 ***********************************************/

struct getFileDirParameters
{
    // 等待应答的信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 是否有后续数据
    bool moreFollows;
    // 文件处理回调(用户层面)
    GspMmsFileDirectoryHandler handler;
    // 处理参数
    void* handlerParameter;
};

static void getFileDirHandler(uint32_t invokeId,
                              void* parameter,
                              GspMmsError mmsError,
                              void* paramNewFileList,
                              bool moreFollows)
{
    // 获取参数
    struct getFileDirParameters* parameters = (struct getFileDirParameters*) parameter;
    parameters->err = mmsError;
    parameters->moreFollows = moreFollows;

    // 调用用户层回调
    if ((mmsError != GSP_MMS_ERROR_NONE) || (paramNewFileList == nullptr)) {
        parameters->err = GSP_MMS_ERROR_OTHER;
        Global_LogString("MMS : 获取文件目录回调中，发现有一些错误 或者 文件夹为空\n");
    } else {
        parameters->handler(parameters->handlerParameter, paramNewFileList);
    }

    // 内存释放
    GspLinkedList_destroyStatic((GspLinkedList)paramNewFileList);

    // 解锁等待互斥
    GspSemaphore_post(parameters->waitForResponse);
}

bool GspMmsConnection_getFileDirectory(
        GspMmsConnection self,
        GspMmsError* mmsError,
        const char* pathName,
        const char* startTime,
        const char* endTime,
        const char* fileAfter,
        GspMmsFileDirectoryHandler fileDirResHandler,
        void* paramHandlerParam){

    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return false;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 根据服务码创建不同的请求数据帧
    if(mmsCLient_createGetDirectoryRequest(self, payload, invokeId, pathName, startTime, endTime, fileAfter)){
        if(DEBUG_MMS_CLIENT){
            printf("创建获取文件列表请求帧成功:%s \n", pathName);
        }
    } else {
        if(DEBUG_MMS_CLIENT){
            Global_LogString("创建获取文件列表请求帧失败:%s \n", pathName);
        }
    }

    // 初始化请求参数
    bool moreFollows = false;
    struct getFileDirParameters parameter;
    parameter.handler = fileDirResHandler;
    parameter.handlerParameter = paramHandlerParam;

    // 初始化信号量
    parameter.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(parameter.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetFileDirectory, (void*)getFileDirHandler, &parameter, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(parameter.waitForResponse);
        *mmsError = parameter.err;
        moreFollows = parameter.moreFollows;
    }
    GspSemaphore_destroy(parameter.waitForResponse);

    // 结果返回
    return moreFollows;
}

/************************************************* 获取文件信息 *****************************************************/
struct FileReadParameters
{
    GspSemaphore waitForResponse;
    GspMmsError err;
    GspMmsFileReadHandler handler;
    void* handlerParameter;
    bool moreFollows;
};

void FileReadHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList buffer, bool moreFollows){
    // 获取参数
    FileReadParameters *params = (FileReadParameters*) parameter;
    params->err = mmsError;
    params->moreFollows = moreFollows;

    // 异常过滤
    if(!buffer){
        GspSemaphore_post(params->waitForResponse);
        return;
    }

    if ((mmsError != GSP_MMS_ERROR_NONE) || (buffer->empty())) {

        // 打印信息
        if(DEBUG_MMS_CLIENT)
            Global_LogString("MMS : 获取下载文件中，发现有一些错误\n");
    } else {
        // 获取数据
        GetFileResponsePDU_t* fileDataRes = (GetFileResponsePDU_t*) buffer->front();

        // 回调处理
        params->handler(params->handlerParameter, fileDataRes->fileData.buf, fileDataRes->fileData.size, moreFollows);

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_GetFileResponsePDU, fileDataRes);
    }

    // 内存释放
    GspLinkedList_destroyStatic(buffer);

    // 解锁等待互斥
    GspSemaphore_post(params->waitForResponse);
}

bool GspMmsConnection_getFile(GspMmsConnection self,
                              GspMmsError* mmsError,
                              const char* fileName,
                              uint32_t startPostion,
                              GspMmsFileReadHandler handler,
                              void* paramHandlerParam){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError)
            *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return false;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 根据服务码创建不同的请求数据帧
    if(mmsClient_createGetFileRequest(self, payload, invokeId, fileName, startPostion)){
        printf("创建获取文件请求帧成功 \n");
    } else {
        Global_LogString("创建获取文件请求帧失败 \n");
    }

    // 下载文件请求参数
    bool moreFollows = false;
    FileReadParameters requestParam;
    requestParam.handler = handler;
    requestParam.handlerParameter = paramHandlerParam;

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetFile, (void*)FileReadHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
        moreFollows = requestParam.moreFollows;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果返回
    return moreFollows;;
}

struct SetFileParameters
{
    GspSemaphore waitForResponse;
    GspMmsError err;
    GspLinkedList dataRetList;
};

void setFileHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList buffer){

    // 获取请求参数
    SetFileParameters *responseParam = (SetFileParameters *)parameter;
    responseParam->err = mmsError;
    responseParam->dataRetList = buffer;

    // 错误信息判断
    if(mmsError != GSP_MMS_ERROR_NONE){
        Global_LogString("setFileHandler 错误代码: %d \n", mmsError);
    }

    // 解锁等待互斥
    GspSemaphore_post(responseParam->waitForResponse);
}

bool GspMmsConnection_setFile(GspMmsConnection self,
                              GspMmsError* mmsError,
                              const char* fileName,
                              uint32_t startPostion,
                              const char* fileData,
                              uint32_t fileDataSize,
                              bool endFlag) {
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError)
            *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return false;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 根据服务码创建不同的请求数据帧
    if(mmsClient_createSetFileRequest(self, payload, invokeId, fileName, startPostion, fileData, fileDataSize, endFlag)){
        printf("创建写文件请求帧成功 \n");
    } else {
        Global_LogString("创建写文件请求帧失败 \n");
    }

    // 上传文件请求参数
    bool result = false;
    SetFileParameters requestParam;
    requestParam.waitForResponse = GspSemaphore_create(1);;
    requestParam.dataRetList = nullptr;
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_SetFile, (void*)setFileHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
        result = true;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果返回
    return result;;
}

/************************************************* 缓存报告类信息 *****************************************************/

struct SetReportControlBlkParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

GspLinkedList GspMmsConnection_getBRCBValues(GspMmsConnection self,
                                             GspMmsError* mmsError,
                                             const char* brcbReference){
    return mmsClient_getDataWorkflow(self, mmsError, brcbReference, GSP_MMS_SC_GetBRCBValues, GSP_ACSIClass_reserved, DLT860_FC_NONE, NOTHING);
}

void setRCBValuesHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList buffer){
    
    // 获取请求参数
    SetReportControlBlkParameters *responseParam = (SetReportControlBlkParameters *)parameter;
    responseParam->err = mmsError;
    responseParam->dataRetList = buffer;

    // 错误信息判断
    if(mmsError != GSP_MMS_ERROR_NONE){
        Global_LogString("setBRCBValuesHandler 错误代码: %d \n", mmsError);
    }

    // 解锁等待互斥
    GspSemaphore_post(responseParam->waitForResponse);
}

GspLinkedList GspMmsConnection_setBRCBValues(GspMmsConnection self,
                                             GspMmsError* mmsError,
                                             BRCBControlBlk brcbControlBlk){
    // 准备参数
    GspLinkedList retList = nullptr;

    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return retList;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 发起异步设置请求
    if(mmsClient_createSetBRCBValuesRequest(self, payload, invokeId, brcbControlBlk)){
        if(DEBUG_MMS_CLIENT)
            printf("创建设置缓存报告控制块值请求帧成功 \n");
    } else {
        if(DEBUG_MMS_CLIENT)
            Global_LogString("创建设置缓存报告控制块值请求帧失败 \n");
    }

    // 请求参数准备
    SetReportControlBlkParameters requestParams;
    requestParams.waitForResponse = GspSemaphore_create(1);;
    requestParams.dataRetList = nullptr;
    GspSemaphore_wait(requestParams.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_SetBRCBValues, (void*)setRCBValuesHandler, &requestParams, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParams.waitForResponse);
        *mmsError = requestParams.err;
        retList = requestParams.dataRetList;
    }
    GspSemaphore_destroy(requestParams.waitForResponse);

    return retList;
}

/************************************************* 非缓存报告类信息 *****************************************************/

GspLinkedList GspMmsConnection_getURCBValues(GspMmsConnection self,
                                             GspMmsError* mmsError,
                                             const char* brcbReference){
    return mmsClient_getDataWorkflow(self,
                                     mmsError,
                                     brcbReference,
                                     GSP_MMS_SC_GetURCBValues,
                                     GSP_ACSIClass_reserved,
                                     DLT860_FC_NONE,
                                     NOTHING);
}

GspLinkedList GspMmsConnection_setURCBValues(GspMmsConnection self,
                                             GspMmsError* mmsError,
                                             URCBControlBlk urcbControlBlk){
    // 准备参数
    GspLinkedList retList = nullptr;

    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return retList;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 发起异步设置请求
    if(mmsClient_createSetURCBValuesRequest(self, payload, invokeId, urcbControlBlk)){
        if(DEBUG_MMS_CLIENT)
            printf("创建设置非缓存报告控制块值请求帧成功 \n");
    } else {
        if(DEBUG_MMS_CLIENT)
            Global_LogString("创建设置非缓存报告控制块值请求帧失败 \n");
    }

    // 请求参数准备
    SetReportControlBlkParameters requestParams;
    requestParams.waitForResponse = GspSemaphore_create(1);;
    requestParams.dataRetList = nullptr;
    GspSemaphore_wait(requestParams.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_SetURCBValues, (void*)setRCBValuesHandler, &requestParams, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParams.waitForResponse);
        *mmsError = requestParams.err;
        retList = requestParams.dataRetList;
    }
    GspSemaphore_destroy(requestParams.waitForResponse);

    return retList;
}


/************************************************* 定值类类信息 ********************************************************/

// 选择定值组请求信息
struct SelectSGParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void SelectActiveSGHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){

    // TODO 默认都是切区成功

    // 获取传入的参数
    SelectSGParameters *params = (SelectSGParameters*) parameter;

    // 错误代码赋值
    params->err = mmsError;

    // 解锁等待互斥
    GspSemaphore_post(params->waitForResponse);
}

bool GspMmsConnection_selectActiveSG(GspMmsConnection self,
                                     GspMmsError* mmsError,
                                     const char* sgcbReference,
                                     uint8_t settingGroupNumber){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return false;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createSelectActiveSGRequest(self, payload, invokeId, sgcbReference, settingGroupNumber)){
        printf("创建激活定值组请求帧成功 \n");
    } else {
        Global_LogString("创建激活定值组请求帧失败 \n");
    }

    // 初始化请求参数
    SelectSGParameters requestParam;
    memset(&requestParam, 0 , sizeof(SelectSGParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_SelectActiveSG, (void*)SelectActiveSGHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return true;
    }
    return false;
}

bool GspMmsConnection_selectEditSG(GspMmsConnection self,
                                   GspMmsError* mmsError,
                                   const char* sgcbReference,
                                   uint8_t settingGroupNumber){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return false;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createSelectEditSGRequest(self, payload, invokeId, sgcbReference, settingGroupNumber)){
        printf("创建切换编辑定值组请求帧成功: %s \n", sgcbReference);
    } else {
        Global_LogString("创建切换编辑定值组请求帧失败：%s \n", sgcbReference);
    }

    // 初始化请求参数
    SelectSGParameters requestParam;
    memset(&requestParam, 0 , sizeof(SelectSGParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_SelectEditSG, (void*)SelectActiveSGHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return true;
    }
    return false;
}

// 获取定值组值请求信息
struct GetSGParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void GetSGCBValuesHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct GetSGParameters* parameters = (struct GetSGParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_getSGCBValues(GspMmsConnection self,
                                             GspMmsError* mmsError,
                                             const char* sgcbReference){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createGetSGCBValuesRequest(self, payload, invokeId, sgcbReference)){
        printf("创建获取定值组请求帧成功 \n");
    } else {
        Global_LogString("创建获取定值组请求帧失败 \n");
    }

    // 初始化请求参数
    GetSGParameters requestParam;
    memset(&requestParam, 0 , sizeof(GetSGParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetSGCBValues, (void*)GetSGCBValuesHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

// 获取定值组值请求信息
struct GetEditSGValuesParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void GetEditSGValuesHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct GetEditSGValuesParameters* parameters = (struct GetEditSGValuesParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_getEditSGValues(GspMmsConnection self,
                                               GspMmsError* mmsError,
                                               GspLinkedList paramList){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createGetEditSGValueRequest(self, payload, invokeId, paramList)){
        printf("创建获取定值组请求帧成功 \n");
    } else {
        Global_LogString("创建获取定值组请求帧失败 \n");
    }

    // 初始化请求参数
    GetEditSGValuesParameters requestParam;
    memset(&requestParam, 0 , sizeof(GetEditSGValuesParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetEditSGValue, (void*)GetEditSGValuesHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // TODO 这里可能需要处理 moreflow

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

// 修改定值组值请求信息
struct SetEditSGValuesParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void SetEditSGValuesHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct SetEditSGValuesParameters* parameters = (struct SetEditSGValuesParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

bool GspMmsConnection_setEditSGValues(GspMmsConnection self,
                                      GspMmsError* mmsError,
                                      GspLinkedList paramList){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return false;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createSetEditSGValueRequest(self, payload, invokeId, paramList)){
        printf("创建写定值组请求帧成功 \n");
    } else {
        Global_LogString("创建写定值组请求帧失败 \n");
    }

    // 初始化请求参数
    SetEditSGValuesParameters requestParam;
    memset(&requestParam, 0 , sizeof(SetEditSGValuesParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_SetEditSGValue, (void*)SetEditSGValuesHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) 
	{
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }

    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE)
	{
        if(!requestParam.dataRetList)
		{
			if (self->m_bResponseError)//zhouhj20220110 在收到返回错误报文头时返回false
			{
				return false;
			}

            return true;
        } 
		else 
		{
            // 只要有一个定值写失败了，就认为是失败了
            bool ret = true;
#ifdef NOT_USE_IN_C11
			deque<void *> d = *requestParam.dataRetList;

			for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
			{
				SetEditSGValueResponsePDU_t* retItem = (SetEditSGValueResponsePDU_t*) (*it);
#else
            for(auto &item : *(requestParam.dataRetList))
            {
                SetEditSGValueResponsePDU_t* retItem = (SetEditSGValueResponsePDU_t*) item;
#endif
                for (int index=0; index != retItem->result.list.count; ++index) 
				{
                    ServiceError_t* errorCode = retItem->result.list.array[index];
                    if(*errorCode != 0)
					{
                        ret = false;
                    }
                }

                // 内存释放
                ASN_STRUCT_FREE(asn_DEF_SetEditSGValueResponsePDU, retItem);
            }

			if (self->m_bResponseError)//zhouhj20220110 在收到返回错误报文头时返回false
			{
				ret = false;
			}

            // 内存释放
            GspLinkedList_destroyStatic(requestParam.dataRetList);
            return ret;
        }
    }

    // 内存释放
    GspLinkedList_destroyStatic(requestParam.dataRetList);
    return false;
}

// 确认定值组修改的请求信息
struct ConfirmSGValueParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void ConfirmEditSGValuesHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){

    // TODO 默认都是切区成功

    // 获取传入的参数
    ConfirmSGValueParameters *params = (ConfirmSGValueParameters*) parameter;

    // 错误代码赋值
    params->err = mmsError;

    // 解锁等待互斥
    GspSemaphore_post(params->waitForResponse);
}


bool GspMmsConnection_confirmEditSGValues(GspMmsConnection self,
                                          GspMmsError* mmsError,
                                          const char* sgcbReference){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return false;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createConfirmEditSGValuesRequest(self, payload, invokeId, sgcbReference)){
        printf("创建确认编辑定值组值请求帧成功 \n");
    } else {
        Global_LogString("创建确认编辑定值组值请求帧失败 \n");
    }

    // 初始化请求参数
    ConfirmSGValueParameters requestParam;
    memset(&requestParam, 0 , sizeof(ConfirmSGValueParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_ConfirmEditSGValues, (void*)ConfirmEditSGValuesHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return true;
    }
    return false;
}

// test 请求信息
struct TestParameters
{
    // 错误信息
    GspMmsError err;
};

void testHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError){
    // TODO 测试帧暂不做处理
}

bool GspMmsConnection_test(GspMmsConnection self, GspMmsError* mmsError, bool reqFlag){
    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return false;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);

    if(reqFlag){
        // 创建请求数据帧
        mmsClient_createTestRequest(self);
    } else {
        // 创建应答数据帧
        mmsClient_createTestResponse(self);
    }

    // 获取invokid
    uint16_t invokeId = getNextInvokeId(self);

    // 初始化请求参数
    TestParameters requestParam;
    memset(&requestParam, 0 , sizeof(TestParameters));

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_Test, (void*)testHandler, &requestParam, intParam);

    // 异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        *mmsError = requestParam.err;
    }

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return true;
    }
    return false;
}

// select 请求信息
struct SelectParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void SelectHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct SelectParameters* parameters = (struct SelectParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

bool GspMmsConnection_select(GspMmsConnection self,
                             GspMmsError* mmsError,
                             const char* controlReference){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return false;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createSelectRequest(self, payload, invokeId, controlReference)){
        printf("创建控制选择请求帧成功:%s \n", controlReference);
    } else {
        Global_LogString("创建控制选择请求帧失败:%s \n", controlReference);
    }

    // 初始化请求参数
    SelectParameters requestParam;
    memset(&requestParam, 0 , sizeof(SelectParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_Select, (void*)SelectHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return true;
    }
    return false;
}

// Operate 请求信息
struct OperateParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void OperateHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct OperateParameters* parameters = (struct OperateParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_operate(GspMmsConnection self,
                                       GspMmsError* mmsError,
                                       const char* controlReference,
                                       GspMmsValue* paramValue,
                                       Originator__orCat paramOrCat,
                                       const char* paramOrIdent,
                                       bool syncCheck,
                                       bool lockCheck,
                                       bool test){
    // invokid 初始化
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createOpRequest(self, payload, invokeId, controlReference, paramValue, paramOrCat, paramOrIdent, syncCheck, lockCheck, test)){
        printf("创建控制操作请求帧成功 \n");
    } else {
        Global_LogString("创建控制操作请求帧失败 \n");
    }

    // 初始化请求参数
    OperateParameters requestParam;
    memset(&requestParam, 0 , sizeof(OperateParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_Operate, (void*)OperateHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

// SelectWithValue 请求信息
struct SelectWithValueParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void SelectWithValueHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct SelectWithValueParameters* parameters = (struct SelectWithValueParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_selectWithValue(GspMmsConnection self,
                                               GspMmsError* mmsError,
                                               const char* controlReference,
                                               GspMmsValue* paramValue,
                                               Originator__orCat paramOrCat,
                                               const char* paramOrIdent,
                                               bool syncCheck,
                                               bool lockCheck,
                                               bool test){
    // invokid 初始化
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createSelectWithValueRequest(self, payload, invokeId, controlReference, paramValue, paramOrCat, paramOrIdent, syncCheck, lockCheck, test)){
        printf("创建带值选择操作请求帧成功:%s \n", controlReference);
    } else {
        Global_LogString("创建带值选择操作请求帧失败:%s \n", controlReference);
        GspIsoClientConnection_releaseTransmitBuffer(self->isoClient);
        return nullptr;
    }

    // 初始化请求参数
    SelectWithValueParameters requestParam;
    memset(&requestParam, 0 , sizeof(SelectWithValueParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_SelectWithValue, (void*)SelectWithValueHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}


struct RpcInterfaceDirectoryParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void GetRpcInterfaceDirectoryHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct RpcInterfaceDirectoryParameters* parameters = (struct RpcInterfaceDirectoryParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_getRpcInterfaceDirectory(GspMmsConnection self,
                                                        GspMmsError* mmsError,
                                                        const char* paramRefsAfter){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createGetRpcInterfaceDirectoryRequest(self, payload, invokeId, paramRefsAfter)){
        printf("创建获取RPC接口请求帧成功 \n");
    } else {
        Global_LogString("创建获取RPC接口请求帧失败 \n");
    }

    // 初始化请求参数
    RpcInterfaceDirectoryParameters requestParam;
    memset(&requestParam, 0 , sizeof(RpcInterfaceDirectoryParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetRpcInterfaceDirectory, (void*)GetRpcInterfaceDirectoryHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

struct RpcMethodDirectoryParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void GetRpcMethodDirectoryHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct RpcMethodDirectoryParameters* parameters = (struct RpcMethodDirectoryParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_getRpcMethodDirectory(GspMmsConnection self,
                                                     GspMmsError* mmsError,
                                                     const char* paramInterface,
                                                     const char* paramRefsAfter){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createGetRpcMethodDirectoryRequest(self, payload, invokeId, paramInterface, paramRefsAfter)){
        printf("创建获取RPC方法请求帧成功 \n");
    } else {
        Global_LogString("创建获取RPC方法请求帧失败 \n");
    }

    // 初始化请求参数
    RpcMethodDirectoryParameters requestParam;
    memset(&requestParam, 0 , sizeof(RpcMethodDirectoryParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetRpcMethodDirectory, (void*)GetRpcMethodDirectoryHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

struct RPCInterfaceDefinitionParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void GetRpcInterfaceDefinitionHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct RPCInterfaceDefinitionParameters* parameters = (struct RPCInterfaceDefinitionParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_getRpcInterfaceDefinition(GspMmsConnection self,
                                                         GspMmsError* mmsError,
                                                         const char* paramInterfaceRef,
                                                         const char* paramRefsAfter){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createGetRpcInterfaceDefinitionRequest(self, payload, invokeId, paramInterfaceRef, paramRefsAfter)){
        printf("创建获取RPC接口定义请求帧成功 \n");
    } else {
        Global_LogString("创建获取RPC接口定义请求帧失败 \n");
    }

    // 初始化请求参数
    RPCInterfaceDefinitionParameters requestParam;
    memset(&requestParam, 0 , sizeof(RPCInterfaceDefinitionParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetRpcInterfaceDefinition, (void*)GetRpcInterfaceDefinitionHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

struct RPCMethodDefinitionParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void GetRpcMethodDefinitionHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct RPCMethodDefinitionParameters* parameters = (struct RPCMethodDefinitionParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_getRpcMethodDefinition(GspMmsConnection self,
                                                      GspMmsError* mmsError,
                                                      GspLinkedList paramMethodRefList){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createGetRpcMethodDefinitionRequest(self, payload, invokeId, paramMethodRefList)){
        printf("创建获取RPC方法定义请求帧成功 \n");
    } else {
        Global_LogString("创建获取RPC方法定义请求帧失败 \n");
    }

    // 初始化请求参数
    RPCMethodDefinitionParameters requestParam;
    memset(&requestParam, 0 , sizeof(RPCMethodDefinitionParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetRpcMethodDefinition, (void*)GetRpcMethodDefinitionHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

struct RPCCallParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void RPCCallHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct RPCCallParameters* parameters = (struct RPCCallParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_RpcCall(GspMmsConnection self,
                                       GspMmsError* mmsError,
                                       const char* paramFuncation,
                                       GspMmsValue* paramData,
                                       const char* paramCallID){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createRpcCallRequest(self, payload, invokeId, paramFuncation, paramData, paramCallID)){
        printf("创建获取RpcCall方法定义请求帧成功 \n");
    } else {
        Global_LogString("创建获取RpcCall方法定义请求帧失败 \n");
    }

    // 初始化请求参数
    RPCCallParameters requestParam;
    memset(&requestParam, 0 , sizeof(RPCCallParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_RpcCall, (void*)RPCCallHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

struct GetLCBParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void GetLCBValuesHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct GetLCBParameters* parameters = (struct GetLCBParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}


GspLinkedList GspMmsConnection_getLCBValues(GspMmsConnection self,
                                            GspMmsError* mmsError,
                                            GspLinkedList paramLCBRefsList){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createGetLCBValuesRequest(self, payload, invokeId, paramLCBRefsList)){
        printf("创建获取 LCBValues 请求帧成功 \n");
    } else {
        Global_LogString("创建获取 LCBValues 请求帧失败 \n");
    }

    // 初始化请求参数
    GetLCBParameters requestParam;
    memset(&requestParam, 0 , sizeof(GetLCBParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_GetLCBValues, (void*)GetLCBValuesHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

struct SetLCBParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void SetLCBValuesHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct GetLCBParameters* parameters = (struct GetLCBParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_setLCBValues(GspMmsConnection self,
                                            GspMmsError* mmsError,
                                            GspLinkedList paramLCBRefsList){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (mmsError) *mmsError = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createSetLCBValuesRequest(self, payload, invokeId, paramLCBRefsList)){
        printf("创建获取 SetLCBValues 请求帧成功 \n");
    } else {
        Global_LogString("创建获取 SetLCBValues 请求帧失败 \n");
    }

    // 初始化请求参数
    SetLCBParameters requestParam;
    memset(&requestParam, 0 , sizeof(SetLCBParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *mmsError = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_SetLCBValues, (void*)SetLCBValuesHandler, &requestParam, intParam);

    // 等待异步结果
    if (*mmsError == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *mmsError = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*mmsError == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}

struct QueryLogByTimeParameters
{
    // 信号量
    GspSemaphore waitForResponse;
    // 错误信息
    GspMmsError err;
    // 结果信息
    GspLinkedList dataRetList;
};

void QueryLogByTimeHandler(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList){
    struct GetLCBParameters* parameters = (struct GetLCBParameters*) parameter;
    parameters->err = mmsError;
    parameters->dataRetList = retList;
    GspSemaphore_post(parameters->waitForResponse);
}

GspLinkedList GspMmsConnection_queryLogByTime(GspMmsConnection self,
                                              GspMmsError* error,
                                              const char* paramLogRefs,
                                              const char* startTime,
                                              const char* stopTime,
                                              const char* afterEntryID){
    // invokid init
    uint16_t invokeId = 0;

    // 链接状态判断
    if (getConnectionState(self) != GSP_MMS_CONNECTION_STATE_CONNECTED) {
        if (error) *error = GSP_MMS_ERROR_CONNECTION_LOST;
        return nullptr;
    }

    // 获取请求数据缓存
    GspByteBuffer* payload = GspIsoClientConnection_allocateTransmitBuffer(self->isoClient);
    invokeId = getNextInvokeId(self);

    // 创建请求数据帧
    if(mmsClient_createQueryLogByTimeRequest(self, payload, invokeId, paramLogRefs, startTime, stopTime, afterEntryID)){
        printf("创建获取 queryLogByTime 请求帧成功 \n");
    } else {
        Global_LogString("创建获取 queryLogByTime 请求帧失败 \n");
        return nullptr;
    }

    // 初始化请求参数
    QueryLogByTimeParameters requestParam;
    memset(&requestParam, 0 , sizeof(QueryLogByTimeParameters));

    // 初始化信号量
    requestParam.waitForResponse = GspSemaphore_create(1);
    GspSemaphore_wait(requestParam.waitForResponse);

    // 发送异步信息
    GspMmsClientInternalParameter intParam;
    intParam.ptr = nullptr;
    *error = sendAsyncRequest(self, invokeId, payload, GSP_MMS_SC_QueryLogByTime, (void*)QueryLogByTimeHandler, &requestParam, intParam);

    // 等待异步结果
    if (*error == GSP_MMS_ERROR_NONE) {
        GspSemaphore_wait(requestParam.waitForResponse);
        *error = requestParam.err;
    }
    GspSemaphore_destroy(requestParam.waitForResponse);

    // 结果解析
    if(*error == GSP_MMS_ERROR_NONE){
        return requestParam.dataRetList;
    }
    return nullptr;
}
