/*
 *  gsp_ied_connection_private.h
 */

#ifndef GSP_IED_CONNECTION_PRIVATE_H_
#define GSP_IED_CONNECTION_PRIVATE_H_

// 调试开关
#ifndef DEBUG_IED_CLIENT
#define DEBUG_IED_CLIENT 1
#endif

#include "gsp_hal_thread.h"
#include "gsp_mms_value.h"
#include "gsp_mms_client_connection.h"

namespace GSP {

// 调用者的信息
typedef struct sGspIedConnectionOutstandingCall* GspIedConnectionOutstandingCall;
struct sGspIedConnectionOutstandingCall {
    bool used;
    uint32_t invokeId;
    void* callback;
    void* callbackParameter;
};

// 报告回调
typedef struct sGspReportCallInfo* GspReportCall;
struct sGspReportCallInfo {
    void* reportCallback;
    void* callbackParameter;
    char* reportRefs;
    char* rptId;
    
    sGspReportCallInfo(){
        reportCallback = nullptr;
        callbackParameter = nullptr;
        reportRefs = nullptr;
        rptId = nullptr;
    }

    sGspReportCallInfo(const sGspReportCallInfo& other){
        reportCallback = other.reportCallback;
        callbackParameter = other.callbackParameter;
        reportRefs = other.reportRefs;
        rptId = other.rptId;
    }

    sGspReportCallInfo& operator=(const sGspReportCallInfo& other){
        reportCallback = other.reportCallback;
        callbackParameter = other.callbackParameter;
        reportRefs = other.reportRefs;
        rptId = other.rptId;
        return *this;
    }

};

// 链接的结构定义
struct sGspIedConnection
{
    // mms 链接对象
    GspMmsConnection connection;

    // 当前链接状态
    GspIedConnectionState state;

    // 链接使能的报告列表
    GspLinkedList enabledReports;

    // 链接所对应设备的逻辑设备列表(暂未实现)
    GspLinkedList logicalDevices;

    // 客户端控制操作列表(暂未实现)
    GspLinkedList clientControls;

    // 最后的错误信息
    GspLastApplError lastApplError;

    // 链接状态信号量
    GspSemaphore stateMutex;

    // 报告处理的信号量
    GspSemaphore reportHandlerMutex;

    // 外部调用信号量
    GspSemaphore outstandingCallsLock;

    // 外部调用者信息
    GspIedConnectionOutstandingCall outstandingCalls;

    // 断链时回调
    GspIedConnectionClosedHandler connectionCloseHandler;
    void* connectionClosedParameter;

    // 链接状态改变时回调
    GspIedConnectionIedConnection_StateChangedHandler connectionStateChangedHandler;
    void* connectionStateChangedHandlerParameter;

    // 链接超时时间
    uint32_t connectionTimeout;
};

// 销毁 gspreportcallback
LIB860_INTERNAL void GspReportCall_Destory(GspReportCall self);

/**
 * @brief GspReportCall_lookup 查找注册的报告回调
 * @param self 链接信息
 * @param paramReportID 报告ID
 */ 
LIB860_INTERNAL GspReportCall GspReportCall_lookup(GspIedConnection self, const char* paramReportID);

}

#endif /* GSP_IED_CONNECTION_PRIVATE_H_ */
