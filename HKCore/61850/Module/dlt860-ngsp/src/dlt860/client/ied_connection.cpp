/*
 *  ied_connection.c
 */

#include "stack_config.h"
#include <string>
#include "libdlt860_platform_includes.h"
#include "dlt860_client.h"
#include "gsp_mms_client_connection.h"
#include "gsp_ied_connection_private.h"
#include "conversions.h"
#include "libdlt860_common_api.h"
#include "asn_inc.h"

#define DEFAULT_CONNECTION_TIMEOUT 10000
#define DATA_SET_MAX_NAME_LENGTH 64 
#define OUTSTANDING_CALLS 12

using namespace std;  

namespace GSP {

// 控制对象
struct sGspControlObjectClient
{
    // 控制模式
    GspControlModel ctlModel;

    // 控制对象refs
    char* objectReference;

    // ied 链接信息
    GspIedConnection connection;

    // test 参数
    bool test;

    // 锁检查
    bool interlockCheck;

    // 同步检查
    bool synchroCheck;

    // 是否有时间激活模式
    bool hasTimeActivatedMode;

    // 错误描述
    GspLastApplError lastApplError;
    GspMmsError lastMmsError;

    // CommandTerminationHandler commandTerminationHandler;
    // void* commandTerminaionHandlerParameter;

    // 控制参数
    GspMmsValue* ctlVal;

    // 操作时间
    uint64_t opertime;

    // 控制数量
    uint8_t ctlNum;

    // Originator
    char* orIdent;
    int orCat;
};

// 数据集
struct sGspClientDataSet
{
    char* dataSetReference;
    GspMmsValue* dataSetValues;
};

// 文件条目
struct sGspFileDirectoryEntry {
    // 文件名字
    char* fileName;
    // 文件尺寸
    uint32_t fileSize;
    // 文件最后修改时间
    uint64_t lastModified;
    // 校验码
    unsigned long checkSum;
};
}

static void GspIedConnection_setState(GspIedConnection self, GspIedConnectionState newState);

GspIedClientError GspIedConnection_mapMmsErrorToIedError(GspMmsError mmsError)
{
    switch (mmsError) {

    // 没有错误
    case GSP_MMS_ERROR_NONE:
        return GSP_IED_ERROR_OK;

        // 实例不可用
    case GSP_MMS_ERROR_INSTANCE_NOT_AVAILABLE:
        return GSP_IED_ERROR_INSTANCE_NOT_AVAILABLE;

        // 实例在使用
    case GSP_MMS_ERROR_INSTANCE_IN_USE:
        return GSP_IED_ERROR_INSTANCE_IN_USE;

        // 访问违例
    case GSP_MMS_ERROR_ACCESS_VIOLATION:
        return GSP_IED_ERROR_ACCESS_VIOLATION;

        // 当前状态不允许访问
    case GSP_MMS_ERROR_ACCESS_NOT_ALLOWED_IN_CURRENT_STATE:
        return GSP_IED_ERROR_ACCESS_NOT_ALLOWED_IN_CURRENT_STATE;

        // 参数值不合适
    case GSP_MMS_PARAMETER_VALUE_INAPPROPRIATE:
        return GSP_IED_ERROR_PARAMETER_VALUE_INAPPROPRIATE;

        // 参数值不一致
    case GSP_MMS_PARAMETER_VALUE_INCONSISTENT:
        return GSP_IED_ERROR_PARAMETER_VALUE_INCONSISTENT;

        // 类不被支持
    case GSP_MMS_CLASS_NOT_SUPPORTED:
        return GSP_IED_ERROR_CLASS_NOT_SUPPORTED;

        // 实例被其它客户锁定
    case GSP_MMS_INSTANCE_LOCKED_BY_OTHER_CLIENT:
        return GSP_IED_ERROR_INSTANCE_LOCKED_BY_OTHER_CLIENT;

        // 控制必须被选择
    case GSP_MMS_CONTROL_MUST_BE_SELECTED:
        return GSP_IED_ERROR_CONTROL_MUST_BE_SELECTED;

        // 类型冲突
    case GSP_MMS_TYPE_CONFLICT:
        return GSP_IED_ERROR_TYPE_CONFLICT;

        // 由于通信约束失败
    case GSP_MMS_FAILED_DUE_TO_COMM_CONSTRAINT:
        return GSP_IED_ERROR_FAILED_DUE_TO_COMM_CONSTRAINT;

        // 由于服务器约束失败
    case GSP_MMS_FAILED_DUE_TO_SERVER_CONSTRAINT:
        return GSP_IED_ERROR_FAILED_DUE_TO_SERVER_CONSTRAINT;

        // 链接拒绝
    case GSP_MMS_ERROR_CONNECTION_REJECTED:
        return GSP_IED_ERROR_ERROR_CONNECTION_REJECTED;

        // 链接丢失
    case GSP_MMS_ERROR_CONNECTION_LOST:
        return GSP_IED_ERROR_ERROR_CONNECTION_LOST;

        // 服务超时
    case GSP_MMS_ERROR_SERVICE_TIMEOUT:
        return GSP_IED_ERROR_ERROR_SERVICE_TIMEOUT;

        // 应答解析错误
    case GSP_MMS_ERROR_PARSING_RESPONSE:
        return GSP_IED_ERROR_ERROR_PARSING_RESPONSE;

        // 硬件错误
    case GSP_MMS_ERROR_HARDWARE_FAULT:
        return GSP_IED_ERROR_ERROR_HARDWARE_FAULT;

        // 终止拒绝
    case GSP_MMS_ERROR_CONCLUDE_REJECTED:
        return GSP_IED_ERROR_ERROR_CONCLUDE_REJECTED;

        // 参数无效
    case GSP_MMS_ERROR_INVALID_ARGUMENTS:
        return GSP_IED_ERROR_ERROR_INVALID_ARGUMENTS;

        // 超出调用限制
    case GSP_MMS_ERROR_OUTSTANDING_CALL_LIMIT:
        return GSP_IED_ERROR_ERROR_OUTSTANDING_CALL_LIMIT;

    default:
        return GSP_IED_ERROR_UNKNOWN;
    }
}

GspIedClientError GspIedConnection_mapDataAccessErrorToIedError(GspMmsDataAccessError mmsError)
{
    switch (mmsError) {

    case GSP_DATA_ACCESS_ERROR_NO_RESPONSE:
        return GSP_IED_ERROR_TIMEOUT;

    case GSP_DATA_ACCESS_ERROR_SUCCESS:
        return GSP_IED_ERROR_OK;

    case GSP_DATA_ACCESS_ERROR_OBJECT_INVALIDATED:
        return GSP_IED_ERROR_OBJECT_INVALIDATED;

    case GSP_DATA_ACCESS_ERROR_HARDWARE_FAULT:
        return GSP_IED_ERROR_HARDWARE_FAULT;

    case GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE:
        return GSP_IED_ERROR_TEMPORARILY_UNAVAILABLE;

    case GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED:
        return GSP_IED_ERROR_ACCESS_DENIED;

    case GSP_DATA_ACCESS_ERROR_OBJECT_UNDEFINED:
        return GSP_IED_ERROR_OBJECT_UNDEFINED;

    case GSP_DATA_ACCESS_ERROR_INVALID_ADDRESS:
        return GSP_IED_ERROR_INVALID_ADDRESS;

    case GSP_DATA_ACCESS_ERROR_TYPE_UNSUPPORTED:
        return GSP_IED_ERROR_TYPE_UNSUPPORTED;

    case GSP_DATA_ACCESS_ERROR_TYPE_INCONSISTENT:
        return GSP_IED_ERROR_TYPE_INCONSISTENT;

    case GSP_DATA_ACCESS_ERROR_OBJECT_ATTRIBUTE_INCONSISTENT:
        return GSP_IED_ERROR_OBJECT_ATTRIBUTE_INCONSISTENT;

    case GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_UNSUPPORTED:
        return GSP_IED_ERROR_OBJECT_ACCESS_UNSUPPORTED;

    case GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT:
        return GSP_IED_ERROR_OBJECT_DOES_NOT_EXIST;

    case GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID:
        return GSP_IED_ERROR_OBJECT_VALUE_INVALID;

    default:
        return GSP_IED_ERROR_UNKNOWN;
    }
}

GspIedConnectionOutstandingCall GspIedConnection_allocateOutstandingCall(GspIedConnection self)
{
    GspSemaphore_wait(self->outstandingCallsLock);

    GspIedConnectionOutstandingCall call = nullptr;

    int i = 0;

    for (i = 0; i < OUTSTANDING_CALLS; i++) {
        if (self->outstandingCalls[i].used == false) {
            self->outstandingCalls[i].used = true;
            call = &(self->outstandingCalls[i]);
            break;
        }
    }

    GspSemaphore_post(self->outstandingCallsLock);

    return call;
}

void GspIedConnection_releaseOutstandingCall(GspIedConnection self, GspIedConnectionOutstandingCall call)
{
    GspSemaphore_wait(self->outstandingCallsLock);

    call->used = false;

    GspSemaphore_post(self->outstandingCallsLock);
}

GspIedConnectionOutstandingCall GspIedConnection_lookupOutstandingCall(GspIedConnection self, uint32_t invokeId)
{
    GspSemaphore_wait(self->outstandingCallsLock);

    GspIedConnectionOutstandingCall call = nullptr;

    int i = 0;

    for (i = 0; i < OUTSTANDING_CALLS; i++) {
        if ((self->outstandingCalls[i].used) && (self->outstandingCalls[i].invokeId == invokeId)) {
            call = &(self->outstandingCalls[i]);
            break;
        }
    }

    GspSemaphore_post(self->outstandingCallsLock);

    return call;
}

const char* GSP::Gsp_IedConnection_Associate(GspIedConnection self,
                                             GspIedClientError* error,
                                             const char* paramServerAccessPointReference){
    if (Gsp_IedConnection_GetState(self) == GSP_IED_STATE_CONNECTED) {
        // 设置ied 的链接状态
        GspIedConnection_setState(self, GSP_IED_STATE_CONNECTED);

        // mms 层链接中止
        GspMmsError mmsError;

        // 关联请求
        char* ret = GspMmsConnection_associationAsync(self->connection, &mmsError, paramServerAccessPointReference);

        // 错误代码映射
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);

        // 返回数据
        return ret;
    } else {
        *error = GSP_IED_ERROR_NOT_CONNECTED;
    }
    return nullptr;
}

void GSP::Gsp_IedConnection_FreeAssociateID(const char* paramAssociatedID){
    if(paramAssociatedID){
        GspMemory_free((void*)paramAssociatedID);
    }
}

void GSP::Gsp_IedConnection_Close(GspIedConnection self){
    if (Gsp_IedConnection_GetState(self) == GSP_IED_STATE_CONNECTED) {
        GspIedConnection_setState(self, GSP_IED_STATE_CLOSING);
        GspMmsConnection_close(self->connection);
    }
}

void GSP::Gsp_IedConnection_Abort(GspIedConnection self,
                                  GspIedClientError* error,
                                  GspAbortError reasonCode,
                                  const char* associationId){
    if (Gsp_IedConnection_GetState(self) == GSP_IED_STATE_CONNECTED) {
        // 设置ied 的链接状态
        GspIedConnection_setState(self, GSP_IED_STATE_CLOSING);

        // mms 层链接中止
        GspMmsError mmsError;
        GspMmsConnection_abort(self->connection, &mmsError, (uint8_t)reasonCode, (uint8_t *)associationId);

        // 错误代码映射
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    } else {
        *error = GSP_IED_ERROR_NOT_CONNECTED;
    }
}

static void GspHandleLastApplErrorMessage(GspIedConnection self, GspMmsValue* lastApplError)
{
    // 调试信息
    if (DEBUG_IED_CLIENT){
        Global_LogString("IED_CLIENT: received LastApplError\n");
    }

    if ((GspMmsValue_getType(lastApplError) != Data_PR_structure) || (GspMmsValue_getArraySize(lastApplError) != 5))
    {
        if (DEBUG_IED_CLIENT)
            Global_LogString("IED_CLIENT: LastApplError has wrong type!\n");

        return;
    }
}

static void GspInformationReportCallBack(void* parameter, GspLinkedList& reportPDU )
{
    // 获取ied层链接信息
    GspIedConnection self = (GspIedConnection) parameter;

#ifdef NOT_USE_IN_C11
	deque<void *> d = *reportPDU;
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
#else
    for(auto &item : *reportPDU)
#endif
    {
        // 获取报告数据
#ifdef NOT_USE_IN_C11
		ReportPDU_t* reportData = (ReportPDU_t*)(*it);
#else
        ReportPDU_t* reportData = (ReportPDU_t*)item;
#endif

        // 获取报告ID
        char* rptID = (char*)GspMemory_calloc(reportData->rptID.size+1, sizeof(char));
        memcpy(rptID, reportData->rptID.buf, reportData->rptID.size);
        string reportIDStr(rptID);
        GspStringTrim(reportIDStr);
        GspMemory_free(rptID);

        // 兼容部分厂家
        replace_all_distinct(reportIDStr, "$BR$", ".");
        replace_all_distinct(reportIDStr, "$RP$", ".");

        // 调试信息
        if (DEBUG_IED_CLIENT){
            Global_LogString("IED_CLIENT: 接受到报告数据 %s\n", reportIDStr.data());
        }

        // 找到报告的注册回调
        GspReportCall lastCall = GspReportCall_lookup(self, reportIDStr.data());
        if(lastCall != nullptr){
            // 报告回调
            GspSemaphore_wait(self->reportHandlerMutex);
            GSPReportCallbackFunction callback = (GSPReportCallbackFunction)lastCall->reportCallback;
            callback(lastCall->callbackParameter, reportData);
            GspSemaphore_post(self->reportHandlerMutex);
        } else {
            Global_LogString("[%s]报告没有找到注册回调, 该报告还没有被客户端订阅过回调函数! \n", reportIDStr.data());
            // 释放异常内存
            Gsp_Report_Destory(reportData);
        }
    }

    // 内存释放
    GspLinkedList_destroyStatic(reportPDU);
}

GspClientDataSet GSP::Gsp_ClientDataSet_Create(const char* dataSetReference)
{
    GspClientDataSet self = (GspClientDataSet) GLOBAL_CALLOC(1, sizeof(struct sGspClientDataSet));
    self->dataSetReference = StringUtils_copyString(dataSetReference);
    StringUtils_replace(self->dataSetReference, '$', '.');
    self->dataSetValues = nullptr;
    return self;
}

void GSP::Gsp_ClientDataSet_Destroy(GspClientDataSet self)
{
    if (self->dataSetValues != nullptr)
        GspMmsValue_delete(self->dataSetValues);
    GLOBAL_FREEMEM(self->dataSetReference);
    GLOBAL_FREEMEM(self);
}

GspMmsValue* GSP::Gsp_ClientDataSet_GetValues(GspClientDataSet self)
{
    return self->dataSetValues;
}

char* GSP::Gsp_ClientDataSet_GetReference(GspClientDataSet self)
{
    return self->dataSetReference;
}

GspLinkedList GSP::Gsp_IedConnection_GetDataSetDirectory(GspIedConnection self,
                                                         GspIedClientError* error,
                                                         const char *datasetReference){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 结果准备
    GspLinkedList resultList = GspLinkedList_create();

    // 获取 DataSetDirectory
    GspLinkedList dataList = GspMmsConnection_getDataSetDirectory(self->connection, &mmsError, datasetReference);
    if(dataList){

#ifdef NOT_USE_IN_C11
		deque<void *> d = *dataList;
		for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
		{
			// 获取原始数据值
			GetDataSetDirectoryResponsePDU_t* innerItem = static_cast<GetDataSetDirectoryResponsePDU_t*>(*it);
#else
		for(auto &item: *dataList)
		{
            GetDataSetDirectoryResponsePDU_t *innerItem = (GetDataSetDirectoryResponsePDU_t *)item;
#endif

            int innerSize = innerItem->memberData.list.count;
            for (int innerIndex=0; innerIndex < innerSize; ++innerIndex) {
                // 值拷贝
                GetDataSetDirectoryResponsePDU__memberData__Member *tmpItem = innerItem->memberData.list.array[innerIndex];
                RefsFC tmpRetItem = (RefsFC)GspMemory_calloc(1, sizeof(sRefsFc));
                tmpRetItem->objRefs = (char*)GspMemory_calloc(1, tmpItem->reference.size+1);
                memcpy((void*)tmpRetItem->objRefs, tmpItem->reference.buf, tmpItem->reference.size);
                tmpRetItem->fc = (char*)GspMemory_calloc(1, tmpItem->fc.size+1);
                memcpy((void*)tmpRetItem->fc, tmpItem->fc.buf, tmpItem->fc.size);

                // 添加到结果列表
                GspLinkedList_add(resultList, tmpRetItem);
            }

            // 内存释放
            ASN_STRUCT_FREE(asn_DEF_GetDataSetDirectoryResponsePDU, innerItem);
        }

        // 内存释放
        GspLinkedList_destroyStatic(dataList);

    } else {
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return resultList;
}

void GSP::Gsp_GetDataSetDirectory_Destory(GspLinkedList self){
    if(self){
#ifdef NOT_USE_IN_C11
		deque<void *> d = *self;
		for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
		{
			// 获取原始数据值
			RefsFC tmpRetItem = static_cast<RefsFC>(*it);
#else
        for(auto& item: *self){
            RefsFC tmpRetItem = (RefsFC)item;
#endif
            if(tmpRetItem){
                if(tmpRetItem->fc)
                    GspMemory_free((void*)tmpRetItem->fc);
                if(tmpRetItem->objRefs)
                    GspMemory_free((void*)tmpRetItem->objRefs);
                GspMemory_free(tmpRetItem);
            }
        }
        GspLinkedList_destroyStatic(self);
    }
}

GspLinkedList GSP::Gsp_IedConnection_GetDataSetValues(GspIedConnection self,
                                                      GspIedClientError* error,
                                                      const char *datasetReference){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 获取 DataSetDirectory
    GspLinkedList dataList = GspMmsConnection_getDataSetValues(self->connection, &mmsError, datasetReference);
    if(!dataList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return dataList;
}

void GSP::Gsp_GetDataSetValues_Destory(GspLinkedList self){
    if(self){
#ifdef NOT_USE_IN_C11
		deque<void *> d = *self;
		for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
		{
			// 获取原始数据值
			GspMmsValue* item = static_cast<GspMmsValue*>(*it);
#else
		for(auto &pItemValue: *self){
			GspMmsValue* item = (GspMmsValue*)pItemValue;	
#endif
            if(item)
                GspMmsValue_delete((GspMmsValue*)item);
        }
        // 释放链表
        GspLinkedList_destroyStatic(self);
    }
}

void GSP::Gsp_RefsFCFree(RefsFC paramData){
    if(paramData){
        if(paramData->fc){
            GspMemory_free((void*)(paramData->fc));
        }

        if(paramData->objRefs){
            GspMemory_free((void*)paramData->objRefs);
        }

        GspMemory_free(paramData);
    }
}

static void GspIedConnection_setState(GspIedConnection self, GspIedConnectionState newState)
{
    GspSemaphore_wait(self->stateMutex);

    // 链接状态改变的回调
    if (self->state != newState) {
        if (self->connectionStateChangedHandler)
            self->connectionStateChangedHandler(self->connectionStateChangedHandlerParameter, self, newState);
    }

    // 设置链接状态
    self->state = newState;

    GspSemaphore_post(self->stateMutex);
}

static void GspMmsConnectionStateChangedCallBack(GspMmsConnection connection, void* parameter, GspMmsConnectionState newState)
{
    GspIedConnection self = (GspIedConnection) parameter;

    if (newState == GSP_MMS_CONNECTION_STATE_CONNECTED) {
        GspIedConnection_setState(self, GSP_IED_STATE_CONNECTED);
    }
    else if (newState == GSP_MMS_CONNECTION_STATE_CLOSED) {
        GspIedConnection_setState(self, GSP_IED_STATE_CLOSED);

        if (self->connectionCloseHandler != nullptr)
            self->connectionCloseHandler(self->connectionClosedParameter, self);

        if (DEBUG_IED_CLIENT)
            Global_LogString("IED_CLIENT: Connection closed!\n");
    }
    else if (newState == GSP_MMS_CONNECTION_STATE_CLOSING) {
        GspIedConnection_setState(self, GSP_IED_STATE_CLOSING);
    }
    else if (newState == GSP_MMS_CONNECTION_STATE_CONNECTING) {
        GspIedConnection_setState(self, GSP_IED_STATE_CONNECTING);
    }
}

static GspIedConnection GspCreateNewConnectionObject(GspTLSConfiguration tlsConfig, bool useThreads)
{
    GspIedConnection self = (GspIedConnection) GLOBAL_CALLOC(1, sizeof(struct sGspIedConnection));

    if (self) {
        self->enabledReports = GspLinkedList_create();
        self->logicalDevices = nullptr;
        self->clientControls = GspLinkedList_create();

        if (useThreads){
            self->connection = GspMmsConnection_createSecure(tlsConfig);
        } else {
            self->connection = GspMmsConnection_createNonThreaded(tlsConfig);
        }
        self->state = GSP_IED_STATE_CLOSED;
        self->stateMutex = GspSemaphore_create(1);
        self->reportHandlerMutex = GspSemaphore_create(1);
        self->outstandingCallsLock = GspSemaphore_create(1);
        self->outstandingCalls = (GspIedConnectionOutstandingCall) GLOBAL_CALLOC(OUTSTANDING_CALLS, sizeof(struct sGspIedConnectionOutstandingCall));
        self->connectionTimeout = DEFAULT_CONNECTION_TIMEOUT;
        GspMmsConnection_setInformationReportHandler(self->connection, GspInformationReportCallBack, self);
        GspMmsConnection_setConnectionStateChangedHandler(self->connection, GspMmsConnectionStateChangedCallBack, self);
    }

    return self;
}

GspIedConnection GSP::Gsp_IedConnection_Create()
{
    return GspCreateNewConnectionObject(nullptr, true);
}

bool GSP::Gsp_IedConnection_Tick(GspIedConnection self)
{
    return GspMmsConnection_tick(self->connection);
}

void GSP::Gsp_IedConnection_SetConnectTimeout(GspIedConnection self, uint32_t timeoutInMs)
{
    self->connectionTimeout = timeoutInMs;
}

void GSP::Gsp_IedConnection_SetRequestTimeout(GspIedConnection self, uint32_t timeoutInMs)
{
    if (self->connection) {
        GspMmsConnection_setRequestTimeout(self->connection, timeoutInMs);
    }
}

uint32_t GSP::Gsp_IedConnection_GetRequestTimeout(GspIedConnection self)
{
    if (self->connection) {
        return GspMmsConnection_getRequestTimeout(self->connection);
    } else {
        return 0;
    }
}

GspIedConnectionState GSP::Gsp_IedConnection_GetState(GspIedConnection self)
{
    GspIedConnectionState state;

    GspSemaphore_wait(self->stateMutex);
    state = self->state;
    GspSemaphore_post(self->stateMutex);

    return state;
}

void GSP::Gsp_IedConnection_InstallConnectionClosedHandler(GspIedConnection self, GspIedConnectionClosedHandler handler, void* parameter)
{
    self->connectionCloseHandler = handler;
    self->connectionClosedParameter = parameter;
}

bool GSP::Gsp_IedConnection_Connect(GspIedConnection self, GspIedClientError* error, const char* hostname, int tcpPort,const char* local_address)
{
    if (Gsp_IedConnection_GetState(self) != GSP_IED_STATE_CONNECTED) {

        // 设置超时时间
        GspMmsError mmsError;
        GspMmsConnection_setConnectTimeout(self->connection, self->connectionTimeout);

        // 建立 mms 链接
        if (GspMmsConnection_connect(self->connection, &mmsError, hostname, tcpPort,local_address)) {

            *error = GSP_IED_ERROR_OK;
            // 设置链接状态
            GspIedConnection_setState(self, GSP_IED_STATE_CONNECTED);
            return true;

        } else {
            // 设置链接状态
            GspIedConnection_setState(self, GSP_IED_STATE_CLOSED);
            *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
            return false;

        }

    } else {

        // 已经链接上了，不用重新链接
        *error = GSP_IED_ERROR_ALREADY_CONNECTED;
        return true;
    }
}

void GSP::Gsp_IedConnection_InstallStateChangedHandler(GspIedConnection self, GspIedConnectionIedConnection_StateChangedHandler handler, void* parameter)
{
    self->connectionStateChangedHandler = handler;
    self->connectionStateChangedHandlerParameter = parameter;
}

GspLinkedList GSP::Gsp_IedConnection_GetServerDirectory(GspIedConnection self, GspIedClientError* error){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 协议里面约定 获取serverDirectory 就是获取 逻辑设备
    GspLinkedList retList = GspMmsConnection_getServerDirectory(self->connection, &mmsError);
    if(retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    } else {
        *error = GSP_IED_ERROR_OK;
    }
    return retList;
}

GspLinkedList GSP::Gsp_IedConnection_GetLogicDeviceDirectory(GspIedConnection self, GspIedClientError* error, const char* paramLDName){

    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 协议里面约定 获取 getLogicDevices 就是获取 逻辑设备
    GspLinkedList retList = GspMmsConnection_getLogicDevices(self->connection, &mmsError, paramLDName);
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return retList;
}

GspLinkedList GSP::Gsp_IedConnection_GetLogicNodeDirectory(GspIedConnection self,
                                                           GspIedClientError* error,
                                                           GspACSICLASS paramType,
                                                           const char* reference){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // MMS 层获取数据
    GspLinkedList retList = GspMmsConnection_getLogicalNodeDirectory(self->connection, &mmsError, paramType, reference);
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return retList;
}

GspLinkedList GSP::Gsp_IedConnection_GetAllDataDefinition(GspIedConnection self,
                                                          GspIedClientError* error,
                                                          GspFunctionalConstraint fc,
                                                          const char* reference,
                                                          GspRefType paramRefType){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    //  MMS 层获取数据
    GspLinkedList retList = GspMmsConnection_getAllDataDefinition(self->connection, &mmsError, fc, reference, paramRefType);
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return retList;
}

void GSP::Gsp_FreeAllDataDefinition(void* paramAllDataDefinition){
    if(paramAllDataDefinition){
        ASN_STRUCT_FREE(asn_DEF_GetAllDataDefinitionResponsePDU, paramAllDataDefinition);
    }
}

GspLinkedList GSP::Gsp_IedConnection_GetAllDataValues(GspIedConnection self,
                                                      GspIedClientError* error,
                                                      GspFunctionalConstraint fc,
                                                      const char* reference,
                                                      GspRefType paramRefType){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    //  MMS 层获取数据
    GspLinkedList retList = GspMmsConnection_getAllDataValues(self->connection, &mmsError, fc, reference, paramRefType);

    // 结果数据
    GspLinkedList dataList = GspLinkedList_create();
    if(retList){
        // 数据转换映射
#ifdef NOT_USE_IN_C11
	deque<void *> d = *retList;
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++){
		//   for(int nIndex=0;nIndex<sizeof(*retList)/sizeof((*retList)[0]);nIndex++){
		// 获取原始数据
		GetAllDataValuesResponsePDU_t * dataItem = static_cast<GetAllDataValuesResponsePDU_t *>(*it);
#else
        for(auto &item : *retList){
            // 获取原始数据
            GetAllDataValuesResponsePDU_t * dataItem = static_cast<GetAllDataValuesResponsePDU_t *>(item);
#endif

            // 数据初步解析
            for(int index=0; index < dataItem->data.list.count; ++index){

                // 获取元素
                GetAllDataValuesResponsePDU__data__Member* innerDataItem = dataItem->data.list.array[index];
                GspClientDataSet dataSetItem = Gsp_ClientDataSet_Create((const char *)innerDataItem->reference.buf);
                dataSetItem->dataSetValues = GspMmsValue_clone((GspMmsValue*)&innerDataItem->value);
                GspLinkedList_add(dataList, dataSetItem);
            }

            // 原始数据内存释放
            ASN_STRUCT_FREE(asn_DEF_GetAllDataValuesResponsePDU, dataItem);
        }

        // 列表信息释放
        GspLinkedList_destroyStatic(retList);
    }

    // 错误信息
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return dataList;
}

GspLinkedList GSP::Gsp_IedConnection_GetDataValues(GspIedConnection self,
                                                   GspIedClientError* error,
                                                   GspLinkedList refsFcList){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    //  MMS 层获取数据
    GspLinkedList retList = GspMmsConnection_getDataValues(self->connection, &mmsError, refsFcList);
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return retList;
}

GspLinkedList GSP::Gsp_IedConnection_SetDataValues(GspIedConnection self,
                                                   GspIedClientError* error,
                                                   GspLinkedList dataRefsFcList){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    //  MMS层
    GspLinkedList retList = GspMmsConnection_setDataValues(self->connection, &mmsError, dataRefsFcList);
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return retList;
}

GspLinkedList GSP::Gsp_IedConnection_GetDataDefinition(GspIedConnection self,
                                                       GspIedClientError* error,
                                                       GspLinkedList refsFcList){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    //  MMS层
    GspLinkedList retList = GspMmsConnection_getDataDefinition(self->connection, &mmsError, refsFcList);
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return retList;
}

GspLinkedList GSP::Gsp_IedConnection_GetAllCBValues(GspIedConnection self,
                                                    GspIedClientError* error,
                                                    GspACSICLASS paramClassType,
                                                    const char* reference,
                                                    GspRefType paramRefType){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    //  MMS 层获取数据
    GspLinkedList retList = GspMmsConnection_getAllCBValues(self->connection, &mmsError, paramClassType, reference, paramRefType);

    // 数据转换(这里不再转换，结构略复杂，直接上传到用户层)

    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return retList;
}

void GSP::Gsp_FreeAllCBValue(void* paramAllCbValue){
    if(paramAllCbValue){
        ASN_STRUCT_FREE(asn_DEF_GetAllCBValuesResponsePDU, paramAllCbValue);
    }
}

void GSP::Gsp_IedConnection_Release(GspIedConnection self,
                                    GspIedClientError* error,
                                    const char* associationId)
{
    if (Gsp_IedConnection_GetState(self) == GSP_IED_STATE_CONNECTED) {
        GspMmsError mmsError;
        GspMmsConnection_conclude(self->connection, &mmsError, (uint8_t*)associationId);
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    } else {
        *error = GSP_IED_ERROR_NOT_CONNECTED;
    }
}

void Gsp_IedConnection_Close(GspIedConnection self)
{
    if (Gsp_IedConnection_GetState(self) == GSP_IED_STATE_CONNECTED) {
        GspIedConnection_setState(self, GSP_IED_STATE_CLOSING);
        GspMmsConnection_close(self->connection);
    }
}

void GSP::Gsp_IedConnection_Destroy(GspIedConnection self)
{
    // 关闭 mms 链接
    Gsp_IedConnection_Close(self);

    // 销毁并释放 mms 链接
    GspMmsConnection_destroy(self->connection);

    // 释放调用者的信息
    GLOBAL_FREEMEM(self->outstandingCalls);

    // 释放控制信息
    GspLinkedList_destroyStatic(self->clientControls);

    // 释放报告信息
    GspLinkedList_destroyStatic(self->enabledReports);

    // 释放信号量信息
    GspSemaphore_destroy(self->outstandingCallsLock);
    GspSemaphore_destroy(self->stateMutex);
    GspSemaphore_destroy(self->reportHandlerMutex);

    // 释放链接信息
    GLOBAL_FREEMEM(self);
}

const char* GSP::Gsp_FileDirEntry_GetFileName(GspFileDirectoryEntry self){
    return self->fileName;
}

uint32_t GSP::Gsp_FileDirEntry_GetFileSize(GspFileDirectoryEntry self)
{
    return self->fileSize;
}

uint64_t GSP::Gsp_FileDirEntry_GetLastModified(GspFileDirectoryEntry self)
{
    return self->lastModified;
}

uint64_t GSP::Gsp_FileDirEntry_GetCheckSum(GspFileDirectoryEntry self){
    return self->checkSum;
}

void GSP::Gsp_BitString_print(BIT_STRING_t* paramOther){
    BitString_Printf(paramOther);
}

void GSP::Gsp_FileDirEntry_Destroy(GspFileDirectoryEntry self)
{
    if(self->fileName){
        GLOBAL_FREEMEM(self->fileName);
    }
    if(self){
        GLOBAL_FREEMEM(self);
    }
}

static void GspMmsFileDirectoryCallBack(void* paramOldList, void* paramNewList)
{
    // 数据转换
    GspLinkedList fileNames = (GspLinkedList) paramOldList;
    GspLinkedList newItem = (GspLinkedList) paramNewList;

#ifdef NOT_USE_IN_C11
	deque<void *> d = *newItem;
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		// 获取原始数据值
		GetFileDirectoryResponsePDU_t* newFileList = static_cast<GetFileDirectoryResponsePDU_t*>(*it);
#else
    for(auto &item: *newItem)
    {
        // 获取原始数据值
        GetFileDirectoryResponsePDU_t* newFileList = static_cast<GetFileDirectoryResponsePDU_t*>(item);
#endif

        // 解析数据
        for(int index=0; index!=newFileList->fileEntry.list.count; ++index){
            GspFileDirectoryEntry newDirectoryEntry = (GspFileDirectoryEntry)GspMemory_calloc(1, sizeof(sGspFileDirectoryEntry));
            memset(newDirectoryEntry, 0, sizeof(sGspFileDirectoryEntry));
            FileEntry* fileItem = newFileList->fileEntry.list.array[index];
            newDirectoryEntry->fileSize = fileItem->fileSize;
            newDirectoryEntry->lastModified = convertUtcTimeToMs(fileItem->lastModified);
            newDirectoryEntry->fileName = StringUtils_copyString((char*)fileItem->fileName.buf);
            newDirectoryEntry->checkSum = fileItem->checkSum;
            GspLinkedList_add(fileNames, (void*) newDirectoryEntry);
        }

        // 原始数据内存释放
        ASN_STRUCT_FREE(asn_DEF_GetFileDirectoryResponsePDU, newFileList);
    }
}

GspLinkedList GSP::Gsp_IedConnection_GetFileDirectory(
        GspIedConnection self,
        GspIedClientError* error,
        const char* pathName,
        const char* startTime,
        const char* endTime,
        const char* fileAfter,
        bool &morefollow
        ){

    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 链表准备
    GspLinkedList fileNames = GspLinkedList_create();

    // 获取文件目录信息(mms层)
    morefollow = GspMmsConnection_getFileDirectory(self->connection, &mmsError, pathName, startTime, endTime, fileAfter, GspMmsFileDirectoryCallBack, fileNames);

    // 错误代码映射
    *error = GspIedConnection_mapMmsErrorToIedError(mmsError);

    // 设置返回值
    return fileNames;
}

struct sGspClientProvidedFileReadHandler {
    // 用户层面的 获取文件的回调函数
    GspClientGetFileHandler handler;
    // 回调函数参数
    void* handlerParameter;
    // 文件已经接收了多少字节数据
    uint32_t byteReceived;
};

static void GspMmsFileReadCallBack(void* parameter, uint8_t* buffer, uint32_t bytesReceived, bool endFlag)
{
    // 数据到来时，回调一下用户提供的回调函数
    struct sGspClientProvidedFileReadHandler* handler = (struct sGspClientProvidedFileReadHandler*) parameter;
    handler->handler(handler->handlerParameter, buffer, bytesReceived, !endFlag);
    handler->byteReceived += bytesReceived;
}

bool GSP::Gsp_IedConnection_GetFile(
        GspIedConnection self,
        GspIedClientError* error,
        const char* fileName,
        uint32_t *startPostion,
        GspClientGetFileHandler callback,
        void* handlerParameter
        ){

    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 请求参数准备
    sGspClientProvidedFileReadHandler requestParam;
    requestParam.handler = callback;
    requestParam.handlerParameter = handlerParameter;
    requestParam.byteReceived = 0;

    // 获取文件信息(mms层)
    bool moreFollows = GspMmsConnection_getFile(self->connection, &mmsError, fileName, *startPostion, GspMmsFileReadCallBack, &requestParam);
    *startPostion += (requestParam.byteReceived);

    // 打印调试
    printf("本次下载数据量:%d \n", requestParam.byteReceived);
    printf("是否还有后续数据:%d \n", moreFollows);

    // 设置返回值
    return moreFollows;
}

bool GSP::Gsp_IedConnection_setFile(
        GspIedConnection self,
        GspIedClientError* error,
        const char* fileName,
        uint32_t startPostion,
        const char* fileData,
        uint32_t fileDataSize,
        bool endOfFile
        ) {

    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    //  MMS 层设置数据
    bool retList = GspMmsConnection_setFile(self->connection,
                                            &mmsError,
                                            fileName,
                                            startPostion,
                                            fileData,
                                            fileDataSize,
                                            endOfFile);
    return retList;
}

BRCBControlBlk GSP::Gsp_IedConnection_GetBRCBValues(GspIedConnection self,
                                                    GspIedClientError* error,
                                                    const char* brcbReference){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 报告信息返回值
    BRCBControlBlk reportContrlInfo = (BRCBControlBlk)GspMemory_calloc(1, sizeof(sBRCBControlBlk));
    reportContrlInfo->brcbControlBlk = nullptr;
    reportContrlInfo->reportRefs = nullptr;

    //  MMS 层获取数据
    GspLinkedList retList = GspMmsConnection_getBRCBValues(self->connection, &mmsError, brcbReference);

    // 异常判断
    if(retList == nullptr){

        // 错误信息
        Global_LogString("获取缓存报告控制块失败: %s\n", brcbReference);
        *error = GSP_IED_ERROR_GET_VALUE;

        // 释放内存
        GspMemory_free(reportContrlInfo);
        return nullptr;
    }

    // 数据转换
    if(!retList->empty()){

        // 数据获取
        GetBRCBValuesResponsePDU_t *dataItemPtr = static_cast<GetBRCBValuesResponsePDU_t *>(retList->front());
        if(dataItemPtr->brcb.list.count > 0){
            GetBRCBValuesResponsePDU__brcb__Member* innerItem = dataItemPtr->brcb.list.array[0];
            if(innerItem->present == GetBRCBValuesResponsePDU__brcb__Member_PR_value){

                // 获取缓存报告控制块的值副本
                reportContrlInfo->brcbControlBlk = BRCB_convert(&(innerItem->choice.value));

                // report refs
                char* reportRefs = (char*)GspMemory_calloc(strlen(brcbReference) + 1, sizeof(char));
                memcpy(reportRefs, brcbReference, strlen(brcbReference));
                reportContrlInfo->reportRefs = reportRefs;

                // 释放内存
                ASN_STRUCT_FREE(asn_DEF_GetBRCBValuesResponsePDU, dataItemPtr);
                GspLinkedList_destroyStatic(retList);

                // 报告控制块指针
                return reportContrlInfo;
            } else {
                *error = GSP_IED_ERROR_GET_VALUE;
            }
        } else {
            // 读值错误
            *error = GSP_IED_ERROR_GET_VALUE;
        }

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetBRCBValuesResponsePDU, dataItemPtr);
    }

    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }

    // 内存释放
    GspMemory_free(reportContrlInfo);
    GspLinkedList_destroyStatic(retList);

    return nullptr;
}

bool GSP::Gsp_IedConnection_SetBRCBValues(GspIedConnection self,
                                          GspIedClientError* error,
                                          BRCBControlBlk brcbControlBlk){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    //  MMS 层设置数据
    GspLinkedList retList = GspMmsConnection_setBRCBValues(self->connection, &mmsError, brcbControlBlk);

    // 错误代码暂时不处理
    if(retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);

        for(int index=0; index != GspLinkedList_size(retList); ++index){
            SetBRCBValuesErrorPDU_t *item = static_cast<SetBRCBValuesErrorPDU_t *>(GspLinkedList_get(retList, index));
            ASN_STRUCT_FREE(asn_DEF_SetBRCBValuesErrorPDU, item);
        }
    }

    // 内存释放
    GspLinkedList_destroyStatic(retList);

    // 设备返回空数据时我们也认为是对的，因为有的厂家木有按照规范给返回数据而已
    return true;
}

char* GSP::Gsp_BRCBControlBlk_GetRptID(BRCBControlBlk brcbControlBlk){
    // 异常处理
    if(!brcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_GetRptID 失败, brcbControlBlk 报告控制块为空\n");
        return nullptr;
    }
    if(!brcbControlBlk->brcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_GetRptID 失败, brcbControlBlk->brcbControlBlk 报告控制块为空\n");
        return nullptr;
    }

    if(brcbControlBlk->brcbControlBlk->rptID){
        return (char*)brcbControlBlk->brcbControlBlk->rptID->buf;
    } else {
        return nullptr;
    }
}

void GSP::Gsp_BRCBControlBlk_CleanBuffer(BRCBControlBlk brcbControlBlk){
    // 异常处理
    if(!brcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_CleanBuffer 失败, brcbControlBlk 报告控制块为空\n");
        return;
    }

    // 兼容部分厂家的特殊操作
    GRCB_Clean_Without_Reference(brcbControlBlk->brcbControlBlk);

    // 内存分配
    if(!brcbControlBlk->brcbControlBlk){
        brcbControlBlk->brcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }

    // 总召数据
    brcbControlBlk->brcbControlBlk->purgeBuf = static_cast<BOOLEAN_t*>(GspMemory_calloc(1, sizeof(BOOLEAN_t)));
    *brcbControlBlk->brcbControlBlk->purgeBuf = 1;
}

void GSP::Gsp_BRCBControlBlk_EnableRpt(BRCBControlBlk paramBrcbControlBlk, bool rptFlag){
    // 异常处理
    if(!paramBrcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_EnableRpt 失败, paramBrcbControlBlk 报告控制块为空\n");
        return;
    }

    // 兼容部分厂家的特殊操作
    GRCB_Clean_Without_Reference(paramBrcbControlBlk->brcbControlBlk);

    // 内存分配
    if(!paramBrcbControlBlk->brcbControlBlk){
        paramBrcbControlBlk->brcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }

    // 启动报告
    paramBrcbControlBlk->brcbControlBlk->rptEna = static_cast<BOOLEAN_t*>(GspMemory_calloc(1, sizeof(BOOLEAN_t)));
    *paramBrcbControlBlk->brcbControlBlk->rptEna = rptFlag;
}

void GSP::Gsp_BRCBControlBlk_Destory(BRCBControlBlk paramBrcbControlBlk){

    if(!paramBrcbControlBlk){
        return;
    }

    // 释放refs
    if(paramBrcbControlBlk->reportRefs){
        GspMemory_free(paramBrcbControlBlk->reportRefs);
    }

    // 释放brcb
    GRCB_Clean(paramBrcbControlBlk->brcbControlBlk);

    // 释放外部结构
    GspMemory_free(paramBrcbControlBlk);

}

void GSP::Gsp_BRCBControlBlk_SetBufTime(BRCBControlBlk paramBrcbControlBlk, INT32U_t paramBufTime){
    // 异常处理
    if(!paramBrcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_SetBufTime 失败, paramBrcbControlBlk 报告控制块为空\n");
        return;
    }

    // 兼容部分厂家的特殊操作
    GRCB_Clean_Without_Reference(paramBrcbControlBlk->brcbControlBlk);

    // 内存分配
    if(!paramBrcbControlBlk->brcbControlBlk){
        paramBrcbControlBlk->brcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }

    paramBrcbControlBlk->brcbControlBlk->bufTm = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
    *paramBrcbControlBlk->brcbControlBlk->bufTm = paramBufTime;
}

void GSP::Gsp_BRCBControlBlk_GI(BRCBControlBlk paramBrcbControlBlk, bool paramGIFlag){
    // 异常处理
    if(!paramBrcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_GI 失败, paramBrcbControlBlk 报告控制块为空\n");
        return;
    }

    // 兼容部分厂家的特殊操作
    GRCB_Clean_Without_Reference(paramBrcbControlBlk->brcbControlBlk);

    // 内存分配
    if(!paramBrcbControlBlk->brcbControlBlk){
        paramBrcbControlBlk->brcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }

    // 总召数据
    paramBrcbControlBlk->brcbControlBlk->gi = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *paramBrcbControlBlk->brcbControlBlk->gi = paramGIFlag;
}

void GSP::Gsp_BRCBControlBlk_IntgPd(BRCBControlBlk paramBrcbControlBlk, INT32U_t paramIntgPd){
    // 异常处理
    if(!paramBrcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_IntgPd 失败, paramBrcbControlBlk 报告控制块为空\n");
        return;
    }

    // 兼容部分厂家的特殊操作
    GRCB_Clean_Without_Reference(paramBrcbControlBlk->brcbControlBlk);

    // 内存分配
    if(!paramBrcbControlBlk->brcbControlBlk){
        paramBrcbControlBlk->brcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }

    paramBrcbControlBlk->brcbControlBlk->intgPd = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
    *paramBrcbControlBlk->brcbControlBlk->intgPd = paramIntgPd;
}

void GSP::Gsp_BRCBControlBlk_SetOptFlds(BRCBControlBlk paramBrcbControlBlk,
                                        RCBOptFldType brcbControlOptType,
                                        bool paramValue,
                                        bool isMulity){
    // 异常处理
    if(!paramBrcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_SetOptFlds 失败, paramBrcbControlBlk 报告控制块为空\n");
        return;
    }

    if(!isMulity){
        GRCB_Clean_Without_Reference(paramBrcbControlBlk->brcbControlBlk);
    }

    // 内存分配
    if(!paramBrcbControlBlk->brcbControlBlk){
        paramBrcbControlBlk->brcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }
    if(!paramBrcbControlBlk->brcbControlBlk->optFlds){
        paramBrcbControlBlk->brcbControlBlk->optFlds = static_cast<RCBOptFlds_t*>(GspMemory_calloc(1, sizeof (RCBOptFlds_t)));
        paramBrcbControlBlk->brcbControlBlk->optFlds->bits_unused = 6;
        paramBrcbControlBlk->brcbControlBlk->optFlds->size = 2;
        paramBrcbControlBlk->brcbControlBlk->optFlds->buf = static_cast<uint8_t*>( GspMemory_calloc(2, sizeof(uint8_t)));
    }
    BitString_setBitValue(paramBrcbControlBlk->brcbControlBlk->optFlds, brcbControlOptType, paramValue);
}

void GSP::Gsp_BRCBControlBlk_SetReportRefs(BRCBControlBlk paramBrcbControlBlk,
                                           const char* paramValue){
    // 异常处理
    if(!paramBrcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_SetReportRefs 失败, paramBrcbControlBlk 报告控制块为空\n");
        return;
    }

    // 清空
    GRCB_Clean_Without_Reference((paramBrcbControlBlk)->brcbControlBlk);

    // 内存分配
    if(!(paramBrcbControlBlk)->reportRefs){
        (paramBrcbControlBlk)->reportRefs = static_cast<char*>(GspMemory_calloc(1, strlen(paramValue) + 1));
    }
    strncpy((paramBrcbControlBlk)->reportRefs, paramValue, strlen(paramValue));
}

void GSP::Gsp_BRCBControlBlk_SetRPTID(BRCBControlBlk paramBrcbControlBlk,
                                      const char* paramRptID){
    // 异常处理
    if(!paramBrcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_SetRPTID 失败, paramBrcbControlBlk 报告控制块为空\n");
        return;
    }

    // 清空
    GRCB_Clean_Without_Reference((paramBrcbControlBlk)->brcbControlBlk);

    // 内存分配 && 数值赋值
    paramBrcbControlBlk->brcbControlBlk->rptID = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString129, paramRptID, strlen(paramRptID));
}

void GSP::Gsp_URCBControlBlk_SetRPTID(URCBControlBlk paramUrcbControlBlk,
                                      const char* paramRptID){
    // 异常处理
    if(!paramUrcbControlBlk){
        Global_LogString("Gsp_URCBControlBlk_SetRPTID 失败, paramUrcbControlBlk 报告控制块为空\n");
        return;
    }

    // 清空
    GRCB_Clean_Without_Reference(paramUrcbControlBlk->urcbControlBlk);

    // 内存分配 && 数值赋值
    paramUrcbControlBlk->urcbControlBlk->rptID = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString129, paramRptID, strlen(paramRptID));
}

void GSP::Gsp_BRCBControlBlk_SetTriggerConditions(BRCBControlBlk paramBrcbControlBlk,
                                                  RCBTriggerType brcbControlTriggerType,
                                                  bool paramValue,
                                                  bool isMulity){
    // 异常处理
    if(!paramBrcbControlBlk){
        Global_LogString("Gsp_BRCBControlBlk_SetTriggerConditions 失败, paramBrcbControlBlk 报告控制块为空\n");
        return;
    }

    if(!isMulity){
        GRCB_Clean_Without_Reference(paramBrcbControlBlk->brcbControlBlk);
    }

    // 内存分配
    if(!paramBrcbControlBlk->brcbControlBlk){
        paramBrcbControlBlk->brcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }
    if(!paramBrcbControlBlk->brcbControlBlk->trgOps){
        paramBrcbControlBlk->brcbControlBlk->trgOps = static_cast<TriggerConditions_t*>(GspMemory_calloc(1, sizeof (TriggerConditions_t)));
        paramBrcbControlBlk->brcbControlBlk->trgOps->bits_unused = 2;
        paramBrcbControlBlk->brcbControlBlk->trgOps->size = 1;
        paramBrcbControlBlk->brcbControlBlk->trgOps->buf = static_cast<uint8_t*>(GspMemory_calloc(1, sizeof(uint8_t)));
    }
    BitString_setBitValue(paramBrcbControlBlk->brcbControlBlk->trgOps, brcbControlTriggerType, paramValue);
}

void GSP::Gsp_BRCBControlBlk_SetEntryID(BRCBControlBlk brcbControlBlk,
                                        const char* paramEntryID,
                                        int idSize){
    // 异常处理
    if(!brcbControlBlk){
        Global_LogString("Gsp_IedConnection_SetEntryID 失败, paramBrcbControlBlk 报告控制块为空\n");
        return;
    }

    // 内存分配
    if(!brcbControlBlk->brcbControlBlk){
        brcbControlBlk->brcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }
    brcbControlBlk->brcbControlBlk->entryID = OCTET_STRING_new_fromBuf(&asn_DEF_EntryID, paramEntryID, idSize);
}

void GSP::Gsp_IedConnection_InstallReportCallBack(GspIedConnection self,
                                                  const char* paramReportRefs,
                                                  const char* paramReportID,
                                                  GSPReportCallbackFunction handler,
                                                  void* handlerParameter){

    // 异常判断
    if(!paramReportID || !paramReportID){
        return;
    }

    // 报告回调信息
    GspReportCall reportCall = (GspReportCall)GspMemory_calloc(1, sizeof(struct sGspReportCallInfo));
    reportCall->reportCallback = (void*)handler;
    reportCall->callbackParameter = handlerParameter;
    reportCall->reportRefs = (char*)GspMemory_calloc(strlen(paramReportRefs) + 1, sizeof(char));
    memcpy(reportCall->reportRefs, paramReportRefs, strlen(paramReportRefs));
    reportCall->rptId = (char*)GspMemory_calloc(strlen(paramReportID) + 1, sizeof(char));
    memcpy(reportCall->rptId, paramReportID, strlen(paramReportID));

    // 后安装的回调函数覆盖之前的函数
    string reportID(paramReportID);
    GspStringTrim(reportID);
    GspReportCall findReportCall = GspReportCall_lookup(self, reportID.data());
    if(findReportCall != nullptr){
        GspLinkedList_remove(self->enabledReports, findReportCall);
    }


    // 报告回调入映射表(同步操作)
    GspSemaphore_wait(self->reportHandlerMutex);
    GspLinkedList_add(self->enabledReports, reportCall);
    GspSemaphore_post(self->reportHandlerMutex);
}

void GSP::GspReportCall_Destory(GspReportCall self){
    GspMemory_free(self->reportRefs);
    GspMemory_free(self->rptId);
    GspMemory_free(self);
}

void GSP::Gsp_IedConnection_UnInstallReportCallBack(GspIedConnection self,
                                                    const char* paramReportID){

    // 异常判断
    if(!paramReportID){
        return;
    }

    // 找到对应的报告回调
    GspReportCall findReportCall = GspReportCall_lookup(self, paramReportID);
    if(findReportCall){
        GspSemaphore_wait(self->reportHandlerMutex);
        GspLinkedList_remove(self->enabledReports, findReportCall);
        GspReportCall_Destory(findReportCall);
        GspSemaphore_post(self->reportHandlerMutex);
    }
}

void GSP::Gsp_IedConnection_ReleaseAllReportCallBack(GspIedConnection self){
#ifdef NOT_USE_IN_C11
	deque<void *> d = *(self->enabledReports);
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++){
		GspReportCall findReportCall = (GspReportCall)(*it);
#else
    for(auto &item : *(self->enabledReports)){
        GspReportCall findReportCall = (GspReportCall) item;
#endif
        if(findReportCall){
            GspSemaphore_wait(self->reportHandlerMutex);
            GspLinkedList_remove(self->enabledReports, findReportCall);
            GspReportCall_Destory(findReportCall);
            GspSemaphore_post(self->reportHandlerMutex);
        }
    }
}

GspReportCall GSP::GspReportCall_lookup(GspIedConnection self, const char* paramReportID){

    if(self->enabledReports == nullptr){
        return nullptr;
    }

#ifdef NOT_USE_IN_C11
	deque<void *> d = *self->enabledReports;
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		GspReportCall report = (GspReportCall)(*it);
#else
    for(auto &item : *(self->enabledReports))
    {
        GspReportCall report = (GspReportCall) item;
#endif

        if (strcmp(report->rptId, paramReportID) == 0)
            return report;
    }

    return nullptr;
}

void GSP::Gsp_Report_Destory(void* report){
    if(report){
        ASN_STRUCT_FREE(asn_DEF_ReportPDU, report);
    }
}

const char* GSP::Gsp_ClientReport_getDataSetName(void* self){
    if(self){
        if(((ReportPDU_t*)self)->datSet){
            return (char*)(((ReportPDU_t*)self)->datSet->buf);
        }
    }
    return nullptr;
}

uint64_t GSP::Gsp_ClientReport_getReportTime(void* self){
    if(self){
        uint64_t timestamp = 0;
        if(((ReportPDU_t*)self)->entry.timeOfEntry){
            if(((ReportPDU_t*)self)->entry.timeOfEntry->buf){
                const uint8_t* binaryTimeBuf = ((ReportPDU_t*)self)->entry.timeOfEntry->buf;
                if (((ReportPDU_t*)self)->entry.timeOfEntry->size == 6) {
                    uint16_t daysDiff;
                    daysDiff = binaryTimeBuf[4] * 256;
                    daysDiff += binaryTimeBuf[5];
                    uint64_t mmsTime;
                    mmsTime = daysDiff * (86400000LL);
                    timestamp = mmsTime + (441763200000LL);
                }
                uint32_t msSinceMidnight = 0;
                msSinceMidnight = binaryTimeBuf[0] << 24;
                msSinceMidnight += binaryTimeBuf[1] << 16;
                msSinceMidnight += binaryTimeBuf[2] << 8;
                msSinceMidnight += binaryTimeBuf[3];
                timestamp += msSinceMidnight;
                return timestamp;
            }
        }
    }
    return 0;
}

void* GSP::Gsp_ClientReport_getDataSetValueList(void* self){
    if(self){
        return (void*)&(((ReportPDU_t*)self)->entry.entryData.list);
    }
    return nullptr;
}

uint32_t GSP::Gsp_ClientReport_getDataSetValuesSize(void* self){
    if(self){
        return ((GspReportList*)self)->count;
    }
    return 0;
}

GspMmsValue* GSP::Gsp_ClientReport_getDataSetValue(void* self, int paramIndex){
    if(self){
        if((paramIndex+1) > Gsp_ClientReport_getDataSetValuesSize(self)){
            return nullptr;
        }
        return &(((GspReportList*)self)->array[paramIndex]->value);
    }
    return nullptr;
}

const char* GSP::Gsp_ClientReport_getDataSetValueRefs(void* self, int paramIndex){
    if(self){
        if((paramIndex+1) > static_cast<int>(Gsp_ClientReport_getDataSetValuesSize(self))){
            return nullptr;
        }
        ObjectReference_t* refsPtr = ((GspReportList*)self)->array[paramIndex]->reference;
        if(refsPtr){
            return (char*)(refsPtr->buf);
        } else {
            return nullptr;
        }
    }
    return nullptr;
}

const char* GSP::Gsp_ClientReport_getDataSetValueFC(void* self, int paramIndex){
    if(self){
        if((paramIndex+1) > static_cast<int>(Gsp_ClientReport_getDataSetValuesSize(self))){
            return nullptr;
        }
        FunctionalConstraint_t	*fcPtr = ((GspReportList*)self)->array[paramIndex]->fc;
        if(fcPtr){
            return (char*)(fcPtr->buf);
        } else {
            return nullptr;
        }
    }
    return nullptr;
}

uint16_t GSP::Gsp_ClientReport_getDataSetValueID(void* self, int paramIndex){
    if(self){
        if((paramIndex+1) > (int)Gsp_ClientReport_getDataSetValuesSize(self)){
            return 0;
        }
        return static_cast<uint16_t>((((GspReportList*)self)->array[paramIndex]->id));
    }
    return 0;
}

const char* GSP::Gsp_ClientReport_getRptId(void* self){
    if(self){
        return (char*)(((ReportPDU_t*)self)->rptID.buf);
    }
    return nullptr;
}

EntryID_t *GSP::Gsp_ClientReport_getEntryId(void* self){
    if(self){
        return ((ReportPDU_t*)self)->entry.entryID;
    }
    return nullptr;
}

GspReportReasonCode GSP::Gsp_ClientReport_getReasonCode(void* self, int paramIndex){
    if(self){
        if((paramIndex+1) > (int)Gsp_ClientReport_getDataSetValuesSize(self)){
            return ReasonCode_reserved;
        }
        BIT_STRING_t* reasonCode = ((GspReportList*)self)->array[paramIndex]->reason;
        if(BitString_getBitValue(reasonCode, 0)){
            return ReasonCode_reserved;
        }
        if(BitString_getBitValue(reasonCode, 1)){
            return ReasonCode_data_change;
        }
        if(BitString_getBitValue(reasonCode, 2)){
            return ReasonCode_quality_change;
        }
        if(BitString_getBitValue(reasonCode, 3)){
            return ReasonCode_data_update;
        }
        if(BitString_getBitValue(reasonCode, 4)){
            return ReasonCode_integrity;
        }
        if(BitString_getBitValue(reasonCode, 5)){
            return ReasonCode_general_interrogation;
        }
        if(BitString_getBitValue(reasonCode, 6)){
            return ReasonCode_application_trigger;
        }
    }
    return ReasonCode_reserved;
}

const char* GSP::Gsp_ClientReport_getReasonCodeStr(void* self, int paramIndex){
    if(self){
        if((paramIndex+1) > (int)Gsp_ClientReport_getDataSetValuesSize(self)){
            return "ReasonCode_reserved";
        }
        BIT_STRING_t* reasonCode = ((GspReportList*)self)->array[paramIndex]->reason;
        if(BitString_getBitValue(reasonCode, 0)){
            return "ReasonCode_reserved";
        }
        if(BitString_getBitValue(reasonCode, 1)){
            return "ReasonCode_data_change";
        }
        if(BitString_getBitValue(reasonCode, 2)){
            return "ReasonCode_quality_change";
        }
        if(BitString_getBitValue(reasonCode, 3)){
            return "ReasonCode_data_update";
        }
        if(BitString_getBitValue(reasonCode, 4)){
            return "ReasonCode_integrity";
        }
        if(BitString_getBitValue(reasonCode, 5)){
            return "ReasonCode_general_interrogation";
        }
        if(BitString_getBitValue(reasonCode, 6)){
            return "ReasonCode_application_trigger";
        }
    }
    return "ReasonCode_reserved";
}

URCBControlBlk GSP::Gsp_IedConnection_GetURCBValues(GspIedConnection self,
                                                    GspIedClientError* error,
                                                    const char* urcbReference){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 报告信息返回值
    URCBControlBlk reportContrlInfo = (URCBControlBlk)GspMemory_calloc(1, sizeof(sURCBControlBlk));
    reportContrlInfo->urcbControlBlk = nullptr;
    reportContrlInfo->reportRefs = nullptr;

    //  MMS 层获取数据(同步接口)
    GspLinkedList retList = GspMmsConnection_getURCBValues(self->connection, &mmsError, urcbReference);

    // 异常判断
    if(retList == nullptr){
        // 设置错误值
        Global_LogString("获取非缓存报告控制块失败\n");
        *error = GSP_IED_ERROR_GET_VALUE;

        // 释放内存
        GspMemory_free(reportContrlInfo);
        return nullptr;
    }

    // 数据转换
    if(!retList->empty()){

        // 数据获取
        GetURCBValuesResponsePDU_t *dataItemPtr = static_cast<GetURCBValuesResponsePDU_t *>(retList->front());
        if(dataItemPtr->urcb.list.count > 0){
            GetURCBValuesResponsePDU__urcb__Member* innerItem = dataItemPtr->urcb.list.array[0];
            if(innerItem->present == GetURCBValuesResponsePDU__urcb__Member_PR_value){

                // 获取非缓存报告控制块的值副本
                reportContrlInfo->urcbControlBlk = URCB_convert(&innerItem->choice.value);

                // report refs
                char* reportRefs = (char*)GspMemory_calloc(strlen(urcbReference) + 1, sizeof(char));
                memcpy(reportRefs, urcbReference, strlen(urcbReference));
                (reportContrlInfo)->reportRefs = reportRefs;

                // 释放内存
                ASN_STRUCT_FREE(asn_DEF_GetURCBValuesResponsePDU, dataItemPtr);
                GspLinkedList_destroyStatic(retList);

                return reportContrlInfo;
            } else {
                *error = GSP_IED_ERROR_GET_VALUE;
            }
        } else {
            // 读值错误
            *error = GSP_IED_ERROR_GET_VALUE;
        }

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetURCBValuesResponsePDU, dataItemPtr);
    }

    if(retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    } else {
        *error = GSP_IED_ERROR_OK;
    }

    // 内存释放
    GspMemory_free(reportContrlInfo);
    GspLinkedList_destroyStatic(retList);

    return nullptr;
}

void GSP::Gsp_URCBControlBlk_EnableRpt(URCBControlBlk urcbControlBlk, bool rptFlag){

    // 异常处理
    if(!urcbControlBlk){
        Global_LogString("总召操作失败, 报告控制块为空\n");
        return;
    }

    // 兼容部分厂家的特殊操作
    GRCB_Clean_Without_Reference(urcbControlBlk->urcbControlBlk);

    // 启动报告
    urcbControlBlk->urcbControlBlk->rptEna = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *urcbControlBlk->urcbControlBlk->rptEna = rptFlag;
}

void GSP::Gsp_URCBControlBlk_Destory(URCBControlBlk urcbControlBlk){

    if(!urcbControlBlk){
        return;
    }

    // 释放refs
    if(urcbControlBlk->reportRefs){
        GspMemory_free(urcbControlBlk->reportRefs);
    }

    // 释放urcb
    GRCB_Clean(urcbControlBlk->urcbControlBlk);

    // 释放外部结构
    GspMemory_free(urcbControlBlk);
}

void GSP::Gsp_URCBControlBlk_SetBufTime(URCBControlBlk paramUrcbControlBlk, INT32U_t paramBufTime){

    // 异常处理
    if(!paramUrcbControlBlk){
        Global_LogString("Gsp_URCBControlBlk_SetBufTime 失败, urcbControlBlk 报告控制块为空\n");
        return;
    }

    // 兼容部分厂家的特殊操作
    GRCB_Clean_Without_Reference(paramUrcbControlBlk->urcbControlBlk);

    // 内存分配
    if(!paramUrcbControlBlk->urcbControlBlk){
        paramUrcbControlBlk->urcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }

    // 设置缓存时间
    paramUrcbControlBlk->urcbControlBlk->bufTm = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
    *paramUrcbControlBlk->urcbControlBlk->bufTm = paramBufTime;
}

void GSP::Gsp_URCBControlBlk_GI(URCBControlBlk paramUrcbControlBlk, bool paramGIFlag){

    // 异常处理
    if(!paramUrcbControlBlk){
        Global_LogString("Gsp_URCBControlBlk_GI 失败, urcbControlBlk 报告控制块为空\n");
        return;
    }

    // 兼容部分厂家的特殊操作
    GRCB_Clean_Without_Reference(paramUrcbControlBlk->urcbControlBlk);

    // 内存分配
    if(!paramUrcbControlBlk->urcbControlBlk){
        paramUrcbControlBlk->urcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }

    // 总召数据
    paramUrcbControlBlk->urcbControlBlk->gi = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *paramUrcbControlBlk->urcbControlBlk->gi = paramGIFlag;
}

void GSP::Gsp_URCBControlBlk_IntgPd(URCBControlBlk paramUrcbControlBlk, INT32U_t paramIntgPd){
    // 异常处理
    if(!paramUrcbControlBlk){
        Global_LogString("Gsp_URCBControlBlk_IntgPd 失败, urcbControlBlk 报告控制块为空\n");
        return;
    }

    // 兼容部分厂家的特殊操作
    GRCB_Clean_Without_Reference(paramUrcbControlBlk->urcbControlBlk);

    // 内存分配
    if(!paramUrcbControlBlk->urcbControlBlk){
        paramUrcbControlBlk->urcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }

    paramUrcbControlBlk->urcbControlBlk->intgPd = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
    *paramUrcbControlBlk->urcbControlBlk->intgPd = paramIntgPd;
}

void GSP::Gsp_URCBControlBlk_SetOptFlds(URCBControlBlk paramUrcbControlBlk,
                                        RCBOptFldType urcbControlOptType,
                                        bool paramValue,
                                        bool isMulity){
    // 异常处理
    if(!paramUrcbControlBlk){
        Global_LogString("Gsp_URCBControlBlk_SetOptFlds 失败, urcbControlBlk 报告控制块为空\n");
        return;
    }

    if(!isMulity){
        GRCB_Clean_Without_Reference(paramUrcbControlBlk->urcbControlBlk);
    }

    // 内存分配
    if(!paramUrcbControlBlk->urcbControlBlk){
        paramUrcbControlBlk->urcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }
    if(!paramUrcbControlBlk->urcbControlBlk->optFlds){
        paramUrcbControlBlk->urcbControlBlk->optFlds = static_cast<RCBOptFlds_t*>(GspMemory_calloc(1, sizeof (RCBOptFlds_t)));
        paramUrcbControlBlk->urcbControlBlk->optFlds->bits_unused = 6;
        paramUrcbControlBlk->urcbControlBlk->optFlds->size = 2;
        paramUrcbControlBlk->urcbControlBlk->optFlds->buf = static_cast<uint8_t*>( GspMemory_calloc(2, sizeof(uint8_t)));
    }
    BitString_setBitValue(paramUrcbControlBlk->urcbControlBlk->optFlds, urcbControlOptType, paramValue);
}

void GSP::Gsp_URCBControlBlk_SetTriggerConditions(URCBControlBlk paramUrcbControlBlk,
                                                  RCBTriggerType urcbControlTriggerType,
                                                  bool paramValue,
                                                  bool isMulity){
    // 异常处理
    if(!paramUrcbControlBlk){
        Global_LogString("Gsp_URCBControlBlk_SetTriggerConditions 失败, urcbControlBlk 报告控制块为空\n");
        return;
    }

    if(!isMulity){
        GRCB_Clean_Without_Reference(paramUrcbControlBlk->urcbControlBlk);
    }

    // 内存分配
    if(!paramUrcbControlBlk->urcbControlBlk){
        paramUrcbControlBlk->urcbControlBlk = static_cast<GSPRCB>(GspMemory_calloc(1, sizeof(sGSPRCB)));
    }
    if(!paramUrcbControlBlk->urcbControlBlk->trgOps){
        paramUrcbControlBlk->urcbControlBlk->trgOps = static_cast<TriggerConditions_t*>(GspMemory_calloc(1, sizeof (TriggerConditions_t)));
        paramUrcbControlBlk->urcbControlBlk->trgOps->bits_unused = 2;
        paramUrcbControlBlk->urcbControlBlk->trgOps->size = 1;
        paramUrcbControlBlk->urcbControlBlk->trgOps->buf = static_cast<uint8_t*>(GspMemory_calloc(1, sizeof(uint8_t)));
    }
    BitString_setBitValue(paramUrcbControlBlk->urcbControlBlk->trgOps, urcbControlTriggerType, paramValue);
}

char* GSP::Gsp_URCBControlBlk_GetRptID(URCBControlBlk urcbControlBlk){
    // 异常处理
    if(!urcbControlBlk){
        Global_LogString("Gsp_URCBControlBlk_GetRptID 失败, urcbControlBlk 报告控制块为空\n");
        return nullptr;
    }
    if(!urcbControlBlk->urcbControlBlk){
        Global_LogString("Gsp_URCBControlBlk_GetRptID 失败, urcbControlBlk->urcbControlBlk 报告控制块为空\n");
        return nullptr;
    }

    return (char*)urcbControlBlk->urcbControlBlk->rptID->buf;
}

bool GSP::Gsp_IedConnection_SetURCBValues(GspIedConnection self,
                                          GspIedClientError* error,
                                          URCBControlBlk urcbControlBlk){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    //  MMS 层设置数据
    GspLinkedList retList = GspMmsConnection_setURCBValues(self->connection, &mmsError, urcbControlBlk);

    // 暂不处理错误代码
    if(retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);

        for(int index=0; index != GspLinkedList_size(retList); ++index){
            SetURCBValuesErrorPDU_t *item = (SetURCBValuesErrorPDU_t *)GspLinkedList_get(retList, index);
            ASN_STRUCT_FREE(asn_DEF_SetURCBValuesErrorPDU, item);
        }
    }

    // 内存释放
    GspLinkedList_destroyStatic(retList);

    return true;
}

void GSP::Gsp_URCBControlBlk_SetReportRefs(URCBControlBlk paramUrcbControlBlk,
                                           const char* paramValue){
    // 异常处理
    if(!paramUrcbControlBlk){
        Global_LogString("Gsp_URCBControlBlk_SetReportRefs 失败, paramUrcbControlBlk 报告控制块为空\n");
        return;
    }

    // 清空
    GRCB_Clean_Without_Reference((paramUrcbControlBlk)->urcbControlBlk);

    // 内存分配
    if(!(paramUrcbControlBlk)->reportRefs){
        (paramUrcbControlBlk)->reportRefs = static_cast<char*>(GspMemory_calloc(1, strlen(paramValue) + 1));
    }
    strncpy((paramUrcbControlBlk)->reportRefs, paramValue, strlen(paramValue));
}

bool GSP::Gsp_IedConnection_SelectActiveSG(GspIedConnection self,
                                           GspIedClientError* error,
                                           const char* sgcbReference,
                                           INT8U_t settingGroupNumber){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms层接口调用
    bool ret = GspMmsConnection_selectActiveSG(self->connection, &mmsError, sgcbReference, (uint8_t)settingGroupNumber);

    // 错误代码映射
    if(!ret){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return ret;
}

bool GSP::Gsp_IedConnection_SelectEditSG(GspIedConnection self,
                                         GspIedClientError* error,
                                         const char* sgcbReference,
                                         INT8U_t settingGroupNumber){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms层接口调用
    bool ret = GspMmsConnection_selectEditSG(self->connection, &mmsError, sgcbReference, (uint8_t)settingGroupNumber);

    // 错误代码映射
    if(!ret){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return ret;
}

bool GSP::Gsp_IedConnection_SetEditSGValue(GspIedConnection self,
                                           GspIedClientError* error,
                                           GspLinkedList paramSgValueList){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms层接口调用
    bool ret = GspMmsConnection_setEditSGValues(self->connection, &mmsError, paramSgValueList);

    // 错误代码映射
    if(!ret){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return ret;
}

bool GSP::Gsp_IedConnection_ConfirmEditSGValues(GspIedConnection self,
                                                GspIedClientError* error,
                                                const char* sgcbReference){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms层接口调用
    bool ret = GspMmsConnection_confirmEditSGValues(self->connection, &mmsError, sgcbReference);

    // 错误代码映射
    if(!ret){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return ret;;
}

GspLinkedList GSP::Gsp_IedConnection_GetEditSGValue(GspIedConnection self,
                                                    GspIedClientError* error,
                                                    GspLinkedList paramSgRefsList){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms层接口调用
    GspLinkedList retList = GspMmsConnection_getEditSGValues(self->connection, &mmsError, paramSgRefsList);

    // 错误代码映射
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return retList;
}

GspLinkedList GSP::Gsp_IedConnection_GetSGCBValues(GspIedConnection self,
                                                   GspIedClientError* error,
                                                   const char* sgcbReference){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms层接口调用
    GspLinkedList retList = GspMmsConnection_getSGCBValues(self->connection, &mmsError, sgcbReference);

    // 错误代码映射
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return retList;
}

void GSP::Gsp_FreeSGCBValues(void* paramSgCbValue){
    if(paramSgCbValue){
        ASN_STRUCT_FREE(asn_DEF_GetSGCBValuesResponsePDU, paramSgCbValue);
    }
}

void GSP::Gsp_FreeEditSGValues(void* paramEditSgValues){
    if(paramEditSgValues){
        ASN_STRUCT_FREE(asn_DEF_GetEditSGValueResponsePDU, paramEditSgValues);
    }
}

bool GSP::Gsp_IedConnection_Select(GspControlObjectClient self, GspIedClientError* error){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms层接口调用
    bool retList = GspMmsConnection_select(self->connection->connection, &mmsError, self->objectReference);

    // 错误代码映射
    if(!retList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }

    return retList;
}

void GSP::Gsp_ControlObjectClientInit(GspControlObjectClient self,bool bTest,bool bSynCheck,bool bInterLockCheck,bool bHasTimeActive){

	if (self)
	{
		self->test = bTest;
		self->synchroCheck = bSynCheck;
		self->interlockCheck = bInterLockCheck;
		self->hasTimeActivatedMode = bHasTimeActive;
	}
}

bool GSP::Gsp_IedConnection_Operate(GspControlObjectClient self,
                                    GspIedClientError* error,
                                    GspMmsValue* ctlVal,
                                    uint64_t operTime){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 赋值
    self->ctlVal = ctlVal;

    // 参数整理 TODO 时间参数暂时不用

    // mms层接口调用
    GspLinkedList retList = GspMmsConnection_operate(self->connection->connection,
                                                     &mmsError,
                                                     self->objectReference,
                                                     ctlVal,
                                                     (e_Originator__orCat)self->orCat,
                                                     self->orIdent,
                                                     self->synchroCheck,
                                                     self->interlockCheck,
                                                     self->test);

    // 结果整定
    bool ret = false;
    if(!retList){
        // 错误代码映射
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    } else {
        // 结果整定
        if(GspLinkedList_size(retList) > 0){
            OperateResponsePDU_t* responsePDU = (OperateResponsePDU_t*)GspLinkedList_get(retList, 0);
            self->test = responsePDU->test;
            self->orCat = responsePDU->origin.orCat;
            self->orIdent = (char*)GspMemory_calloc(responsePDU->origin.orIdent.size + 1, sizeof(char));
            memcpy(self->orIdent, responsePDU->origin.orIdent.buf, responsePDU->origin.orIdent.size);
            self->ctlNum = responsePDU->ctlNum;

            // 控制操作正常
            ret = true;
        }
    }

    return ret;
}

bool GSP::Gsp_IedConnection_SelectWithValue(GspControlObjectClient self,
                                            GspIedClientError* error,
                                            GspMmsValue* ctlVal){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 赋值
    self->ctlVal = ctlVal;

    // mms层接口调用
    GspLinkedList retList = GspMmsConnection_selectWithValue(self->connection->connection,
                                                             &mmsError,
                                                             self->objectReference,
                                                             ctlVal,
                                                             (e_Originator__orCat)self->orCat,
                                                             self->orIdent,
                                                             self->synchroCheck,
                                                             self->interlockCheck,
                                                             self->test);

    // 结果整定
    bool ret = false;
    if(!retList){
        // 错误代码映射
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    } else {
        // 结果整定
        if(GspLinkedList_size(retList) > 0){
            SelectWithValueResponsePDU_t* responsePDU = (SelectWithValueResponsePDU_t*)GspLinkedList_get(retList, 0);
            self->test = responsePDU->test;
            self->orCat = responsePDU->origin.orCat;
            self->orIdent = (char*)GspMemory_calloc(responsePDU->origin.orIdent.size + 1, sizeof(char));
            memcpy(self->orIdent, responsePDU->origin.orIdent.buf, responsePDU->origin.orIdent.size);
            self->ctlNum = responsePDU->ctlNum;

            // 控制操作正常
            ret = true;
        }
    }

    return ret;
}

void GSP::Gsp_ControlObjectClient_Destroy(GspControlObjectClient self){
    if(self){

        // refs
        if(self->objectReference){
            GspMemory_free(self->objectReference);
        }

        // ctlVal
        if(self->ctlVal){
            GspMmsValue_delete(self->ctlVal);
        }

        // orIdent
        if(self->orIdent){
            GspMemory_free(self->orIdent);
        }

        GspMemory_free(self);
    }
}

GspControlObjectClient GSP::Gsp_ControlObjectClient_Create(const char* paramCtlReference,
                                                           GspIedConnection connection){
    // 控制对象
    GspControlObjectClient self = (GspControlObjectClient) GspMemory_calloc(1, sizeof(struct sGspControlObjectClient));

    // 拷贝对象
    if(paramCtlReference){
        self->objectReference = (char*)GspMemory_calloc(strlen(paramCtlReference) + 1, sizeof(char));
        memcpy(self->objectReference, paramCtlReference, strlen(paramCtlReference));
    }

    self->connection = connection;

    return  self;
}

bool GSP::Gsp_IedConnection_Cancel(GspControlObjectClient self){

    return true;
}

void GSP::Gsp_ControlObjectClient_SetControlModel(GspControlObjectClient self, GspControlModel ctlModel){
    if(self){
        self->ctlModel = ctlModel;
    }
}

void GSP::Gsp_ControlObjectClient_SetControlRefs(GspControlObjectClient self,
                                                 const char* paramControlRefs){
    if(self) {
        if(self->objectReference){
            GspMemory_free(self->objectReference);
        }
        self->objectReference = (char*)GspMemory_calloc(strlen(paramControlRefs)+1, sizeof(char));
        memcpy(self->objectReference, paramControlRefs, strlen(paramControlRefs));
    }
}

void GSP::Gsp_ControlObjectClient_SetTestMode(GspControlObjectClient self, bool value){
    if(self){
        self->test = value;
    }
}

void GSP::Gsp_ControlObjectClient_SetSyncCheck(GspControlObjectClient self, bool checkFlag){
    if(self){
        self->synchroCheck = checkFlag;
    }
}

void GSP::Gsp_ControlObjectClient_SetLockCheck(GspControlObjectClient self, bool checkFlag){
    if(self){
        self->interlockCheck = checkFlag;
    }
}

void GSP::Gsp_ControlObjectClient_SetMmsValue(GspControlObjectClient self,
                                              GspMmsValue* value){
    if(self){
        self->ctlVal = value;
    }
}

void GSP::Gsp_ControlObjectClient_SetOriginator(GspControlObjectClient self,
                                                Originator__orCat paramOrCat,
                                                const char* paramOrIdent){
    if(self){
        self->orCat = paramOrCat;
        if(paramOrIdent){
            self->orIdent = (char*)GspMemory_calloc(strlen(paramOrIdent)+1, sizeof (char));
            memcpy(self->orIdent, paramOrIdent, strlen(paramOrIdent));
        }
    }
}

bool GSP::Gsp_IedConnection_Test(GspIedConnection self, GspIedClientError* error){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms层接口调用
    bool ret = GspMmsConnection_test(self->connection, &mmsError, true);

    // 错误代码映射
    if(!ret){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }
    return ret;
}

GspLinkedList GSP::Gsp_IedConnection_GetRpcInterfaceDirectory(GspIedConnection self,
                                                              GspIedClientError* error){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 数据结果准备
    GspLinkedList retList = GspLinkedList_create();

    // mms 层接口调用
    GspLinkedList interfaceList = GspMmsConnection_getRpcInterfaceDirectory(self->connection, &mmsError, nullptr);

    // 数据处理
    if(interfaceList){
        int interfaceSize = GspLinkedList_size(interfaceList);
        if(interfaceSize > 0){

            // 获取数据
            GetRpcInterfaceDirectoryResponsePDU_t* response = (GetRpcInterfaceDirectoryResponsePDU_t*)GspLinkedList_get(interfaceList, 0);
            for(int index=0; index < response->reference.list.count; ++index){
                char* rpcInterFace = (char*)GspMemory_calloc(response->reference.list.array[index]->size + 1, 1);
                memcpy(rpcInterFace, response->reference.list.array[index]->buf, response->reference.list.array[index]->size);
                GspLinkedList_add(retList, rpcInterFace);
            }

            // moreflow
            bool moreData = *(response->moreFollows);

            // 释放内存
            ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDirectoryResponsePDU, response);
            GspLinkedList_destroyStatic(interfaceList);

            while (moreData) {
                // 获取最后一个元素
                char* lastElement = (char*)GspLinkedList_getLastElement(retList);

                // 获取下一页数据
                GspLinkedList tmpInterfaceList = GspMmsConnection_getRpcInterfaceDirectory(self->connection, &mmsError, lastElement);
                int tmpInterfaceSize = GspLinkedList_size(tmpInterfaceList);
                if(tmpInterfaceSize > 0){

                    // 获取数据
                    GetRpcInterfaceDirectoryResponsePDU_t* tmpResponse = (GetRpcInterfaceDirectoryResponsePDU_t*)GspLinkedList_get(tmpInterfaceList, 0);
                    for(int innerIndex=0; innerIndex < tmpResponse->reference.list.count; ++innerIndex){
                        char* rpcInterFace = (char*)GspMemory_calloc(tmpResponse->reference.list.array[innerIndex]->size + 1, 1);
                        memcpy(rpcInterFace, tmpResponse->reference.list.array[innerIndex]->buf, tmpResponse->reference.list.array[innerIndex]->size);
                        GspLinkedList_add(retList, rpcInterFace);
                    }

                    // moreflow
                    moreData = *(tmpResponse->moreFollows);

                    // 释放内存
                    ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDirectoryResponsePDU, tmpResponse);
                    GspLinkedList_destroyStatic(tmpInterfaceList);
                } else {
                    moreData = false;
                }
            }
        }
    }

    // 错误代码映射
    if(!interfaceList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }

    return retList;
}

void GSP::Gsp_IedConnection_FreeRpcInterfaceDirectory(GspLinkedList paramData){
    if(!paramData) return;

#ifdef NOT_USE_IN_C11
	deque<void *> d = *paramData;
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++){
		 char* rpcdItem  = (char*)(*it);
#else
    for(auto &methodItem: *paramData){
        // 获取接口信息
        char* rpcdItem = (char*)methodItem;
#endif

        // 释放条目
        GspMemory_free(rpcdItem);
    }

    GspLinkedList_destroyStatic(paramData);

}

GspLinkedList GSP::Gsp_IedConnection_GetRpcMethodDirectory(GspIedConnection self,
                                                           GspIedClientError* error,
                                                           const char* paramInterface){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 数据结果准备
    GspLinkedList retList = GspLinkedList_create();

    // mms 层接口调用
    GspLinkedList interfaceList = GspMmsConnection_getRpcMethodDirectory(self->connection, &mmsError, paramInterface, nullptr);

    // 数据处理
    if(interfaceList){
        int interfaceSize = GspLinkedList_size(interfaceList);
        if(interfaceSize > 0){

            // 获取数据
            GetRpcMethodDirectoryResponsePDU_t* response = (GetRpcMethodDirectoryResponsePDU_t*)GspLinkedList_get(interfaceList, 0);
            for(int index=0; index < response->reference.list.count; ++index){
                char* rpcInterFace = (char*)GspMemory_calloc(response->reference.list.array[index]->size + 1, 1);
                memcpy(rpcInterFace, response->reference.list.array[index]->buf, response->reference.list.array[index]->size);
                GspLinkedList_add(retList, rpcInterFace);
            }

            // moreflow
            bool moreData = *(response->moreFollows);

            // 释放内存
            ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDirectoryResponsePDU, response);
            GspLinkedList_destroyStatic(interfaceList);

            while (moreData) {
                // 获取最后一个元素
                char* lastElement = (char*)GspLinkedList_getLastElement(retList);

                // 获取下一页数据
                GspLinkedList tmpInterfaceList = GspMmsConnection_getRpcMethodDirectory(self->connection, &mmsError, paramInterface, lastElement);
                int tmpInterfaceSize = GspLinkedList_size(tmpInterfaceList);
                if(tmpInterfaceSize > 0){
                    // 获取数据
                    GetRpcMethodDirectoryResponsePDU_t* tmpResponse = (GetRpcMethodDirectoryResponsePDU_t*)GspLinkedList_get(tmpInterfaceList, 0);
                    for(int innerIndex=0; innerIndex < tmpResponse->reference.list.count; ++innerIndex){
                        char* rpcInterFace = (char*)GspMemory_calloc(tmpResponse->reference.list.array[innerIndex]->size + 1, 1);
                        memcpy(rpcInterFace, tmpResponse->reference.list.array[innerIndex]->buf, tmpResponse->reference.list.array[innerIndex]->size);
                        GspLinkedList_add(retList, rpcInterFace);
                    }

                    // moreflow
                    moreData = *(tmpResponse->moreFollows);

                    // 释放内存
                    ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDirectoryResponsePDU, tmpResponse);
                    GspLinkedList_destroyStatic(tmpInterfaceList);
                } else {
                    moreData = false;
                }
            }
        }
    }

    // 错误代码映射
    if(!interfaceList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }

    return retList;
}

void GSP::Gsp_IedConnection_FreeRpcMethodDirectory(GspLinkedList paramData){
    if(!paramData) return;

#ifdef NOT_USE_IN_C11
	deque<void *> d = *paramData;
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++){
		char* rpcdItem = (char*)(*it);
#else
    for(auto &methodItem: *paramData){
        // 获取接口信息
        char* rpcdItem = (char*)methodItem;
#endif

        // 释放条目
        GspMemory_free(rpcdItem);
    }

    GspLinkedList_destroyStatic(paramData);

}

GspLinkedList GSP::Gsp_IedConnection_GetRpcInterfaceDefinition(GspIedConnection self,
                                                               GspIedClientError* error,
                                                               const char* paramInterface){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 数据结果准备
    GspLinkedList retList = GspLinkedList_create();

    // mms 层接口调用
    GspLinkedList interfaceList = GspMmsConnection_getRpcInterfaceDefinition(self->connection, &mmsError, paramInterface, nullptr);

    // 数据处理
    if(interfaceList){
        int interfaceSize = GspLinkedList_size(interfaceList);
        if(interfaceSize > 0){

            // 获取数据
            GetRpcInterfaceDefinitionResponsePDU_t* response = (GetRpcInterfaceDefinitionResponsePDU_t*)GspLinkedList_get(interfaceList, 0);
            GspLinkedList_add(retList, response);

            // moreflow
            bool moreData = *(response->moreFollows);

            while (moreData) {
                // 获取最后一个元素
                GetRpcInterfaceDefinitionResponsePDU_t* lastPDU = (GetRpcInterfaceDefinitionResponsePDU_t*)GspLinkedList_getLastElement(retList);
                int pduSize = lastPDU->method.list.count;
                if(pduSize <= 0){
                    break;
                }
                const char* lastElement = (char*)lastPDU->method.list.array[0]->name.buf;

                // 获取下一页数据
                GspLinkedList tmpInterfaceList = GspMmsConnection_getRpcInterfaceDefinition(self->connection, &mmsError, paramInterface, lastElement);
                int tmpInterfaceSize = GspLinkedList_size(tmpInterfaceList);
                if(tmpInterfaceSize > 0){

                    // 获取数据
                    GetRpcInterfaceDefinitionResponsePDU_t* innerResponse = (GetRpcInterfaceDefinitionResponsePDU_t*)GspLinkedList_get(interfaceList, 0);
                    GspLinkedList_add(retList, innerResponse);

                    // moreflow
                    moreData = *(innerResponse->moreFollows);

                } else {
                    moreData = false;
                }
            }
        }
    }

    // 错误代码映射
    if(!interfaceList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }

    return retList;
}

void GSP::Gsp_IedConnection_FreeRpcInterfaceDefinition(GspLinkedList paramData){

    if(!paramData) return;

#ifdef NOT_USE_IN_C11
	deque<void *> d = *paramData;
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++){
		GetRpcInterfaceDefinitionResponsePDU_t* rpcdItem = (GetRpcInterfaceDefinitionResponsePDU_t*)(*it);
#else
    for(auto &interfaceDefinationItem: *paramData){
        // 获取接口定义信息
        GetRpcInterfaceDefinitionResponsePDU_t* rpcdItem = (GetRpcInterfaceDefinitionResponsePDU_t*)interfaceDefinationItem;
#endif

        // 释放条目
        ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDefinitionResponsePDU, rpcdItem);
    }

    GspLinkedList_destroyStatic(paramData);
}

GspLinkedList GSP::Gsp_IedConnection_GetRpcMethodDefinition(GspIedConnection self,
                                                            GspIedClientError* error,
                                                            GspLinkedList paramMethodList){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms 层接口调用
    GspLinkedList methodList = GspMmsConnection_getRpcMethodDefinition(self->connection, &mmsError, paramMethodList);

    // 错误代码映射
    if(!methodList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }

    return methodList;
}

void GSP::Gsp_IedConnection_FreeRpcMethodDefinition(GspLinkedList paramData){

    if(!paramData) return;

#ifdef NOT_USE_IN_C11
	deque<void *> d = *paramData;
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++){
		GetRpcMethodDefinitionResponsePDU_t* rpcdItem = (GetRpcMethodDefinitionResponsePDU_t*)(*it);
#else
    for(auto &interfaceDefinationItem: *paramData){
        // 获取接口定义信息
        GetRpcMethodDefinitionResponsePDU_t* rpcdItem = (GetRpcMethodDefinitionResponsePDU_t*)interfaceDefinationItem;
#endif

        // 释放条目
        ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDefinitionResponsePDU, rpcdItem);
    }

    GspLinkedList_destroyStatic(paramData);
}

void* GSP::Gsp_IedConnection_RPCCall(GspIedConnection self,
                                     GspIedClientError* error,
                                     const char* paramFuncation,
                                     GspMmsValue* paramData,
                                     const char* paramCallID){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms 层接口调用
    GspLinkedList methodList = GspMmsConnection_RpcCall(self->connection, &mmsError, paramFuncation, paramData, paramCallID);

    // 错误代码映射
    if(!methodList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }

    return methodList;
}

GspMmsValue* GSP::Gsp_RPCCallResPonse_getData(void* paramResponse){
    if(paramResponse){
        // 获取地一个数据
        RpcCallResponsePDU_t* resPDU = static_cast<RpcCallResponsePDU_t*>(static_cast<GspLinkedList>(paramResponse)->front());
        return &resPDU->rspData;
    }
    return nullptr;
}

const char* GSP::Gsp_RPCCallResPonse_getNextCallID(void* paramResponse){
    if(paramResponse){
        RpcCallResponsePDU_t* resPDU = static_cast<RpcCallResponsePDU_t*>(static_cast<GspLinkedList>(paramResponse)->front());
        return (char*)resPDU->nextCallID->buf;
    }
    return nullptr;
}

void GSP::Gsp_IedConnection_FreeRPCCallPDU(void* paramResponsePDU){
    if(paramResponsePDU){
        RpcCallResponsePDU_t* resPDU = static_cast<RpcCallResponsePDU_t*>(static_cast<GspLinkedList>(paramResponsePDU)->front());
        ASN_STRUCT_FREE(asn_DEF_RpcCallResponsePDU, resPDU);
    }
}

void* GSP::Gsp_IedConnection_GetLCBValues(GspIedConnection self,
                                          GspIedClientError* error,
                                          const char* paramLCBRefs){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms 层接口调用
    GspLinkedList paramList = GspLinkedList_create();
    GspLinkedList_add(paramList, (void*)paramLCBRefs);
    GspLinkedList lcbList = GspMmsConnection_getLCBValues(self->connection, &mmsError, paramList);
    GspLinkedList_destroyStatic(paramList);

    // 错误代码映射
    if(!lcbList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
        return nullptr;
    }

    // 数据值
    int retCount = GspLinkedList_size(lcbList);
    if(retCount > 0){
        void* retValue = GspLinkedList_get(lcbList, 0);
        return retValue;
    }

    return nullptr;
}

bool GSP::Gsp_LCBlock_hasError(void* paramLCBInfo){

    // 异常信息判断
    if(!paramLCBInfo) {
        return true;
    }

    // 数据转换
    GetLCBValuesResponsePDU_t* responsePDU = static_cast<GetLCBValuesResponsePDU_t*>(paramLCBInfo);

    // 在 api 层我们约束了仅能单个控制块的设置
    if(responsePDU->lcb.list.size <= 0){
        return true;
    }
    GetLCBValuesResponsePDU__lcb__Member* lcbItem = responsePDU->lcb.list.array[0];

    // 返回是否含有错误信息
    return lcbItem->present == GetLCBValuesResponsePDU__lcb__Member_PR_error;
}

const char* GSP::Gsp_LCBlock_getLogRef(void* paramLCBInfo){
    // 异常信息判断
    if(!paramLCBInfo) {
        return nullptr;
    }

    // 数据转换
    GetLCBValuesResponsePDU_t* responsePDU = static_cast<GetLCBValuesResponsePDU_t*>(paramLCBInfo);

    // 在 api 层我们约束了仅能单个控制块的设置
    if(responsePDU->lcb.list.size <= 0){
        return nullptr;
    }
    GetLCBValuesResponsePDU__lcb__Member* lcbItem = responsePDU->lcb.list.array[0];

    // 数据获取
    if(lcbItem){
        return (char*)lcbItem->choice.value.logRef.buf;
    }

    return nullptr;
}

bool GSP::Gsp_LCBlock_setLogRef(void* paramLCBInfo, const char* paramLogRef){
    // 异常信息判断
    if(!paramLCBInfo) {
        return false;
    }

    // 数据转换
    GetLCBValuesResponsePDU_t* responsePDU = static_cast<GetLCBValuesResponsePDU_t*>(paramLCBInfo);

    // 在 api 层我们约束了仅能单个控制块的设置
    if(responsePDU->lcb.list.size <= 0){
        return false;
    }
    GetLCBValuesResponsePDU__lcb__Member* lcbItem = responsePDU->lcb.list.array[0];

    // 数据获取
    if(lcbItem){
        OCTET_STRING_fromBuf(&(lcbItem->choice.value.logRef), paramLogRef, strlen(paramLogRef));
    }

    return false;
}

GspIedClientError GSP::Gsp_LCBlock_getErrorCode(void* paramLCBInfo){
    // 异常信息判断
    if(!paramLCBInfo){
        return GSP_IED_ERROR_UNKNOWN;
    }

    // 数据转换
    GetLCBValuesResponsePDU_t* responsePDU = static_cast<GetLCBValuesResponsePDU_t*>(paramLCBInfo);

    // 在 api 层我们约束了仅能单个控制块的设置
    if(responsePDU->lcb.list.size <= 0){
        return GSP_IED_ERROR_UNKNOWN;
    }
    GetLCBValuesResponsePDU__lcb__Member* lcbItem = responsePDU->lcb.list.array[0];

    // 错误代码映射
    if(lcbItem->present == GetLCBValuesResponsePDU__lcb__Member_PR_error){
        return (GspIedClientError)lcbItem->choice.error;
    }

    return GSP_IED_ERROR_OK;
}

bool GSP::Gsp_LCBlock_getLogEna(void* paramLCBInfo) {

    // 异常信息判断
    if(!paramLCBInfo){
        return false;
    }

    // 数据转换
    GetLCBValuesResponsePDU_t* responsePDU = static_cast<GetLCBValuesResponsePDU_t*>(paramLCBInfo);

    // 在 api 层我们约束了仅能单个控制块的设置
    if(responsePDU->lcb.list.size <= 0){
        return false;
    }
    GetLCBValuesResponsePDU__lcb__Member* lcbItem = responsePDU->lcb.list.array[0];

    // 获取数值
    if(lcbItem) {
        return lcbItem->choice.value.logEna;
    }

    return false;
}

bool GSP::Gsp_LCBlock_setLogEna(void* paramLCBInfo, bool paramEna){
    // 异常转换
    if(!paramLCBInfo){
        return false;
    }

    // 数据转换
    GetLCBValuesResponsePDU_t* responsePDU = static_cast<GetLCBValuesResponsePDU_t*>(paramLCBInfo);

    // 在 api 我们约束仅能但个控制块设置
    if(responsePDU->lcb.list.size <= 0){
        return false;
    }
    GetLCBValuesResponsePDU__lcb__Member* lcbItem = responsePDU->lcb.list.array[0];

    // 数据值创建
    if(lcbItem){
        lcbItem->choice.value.logEna = paramEna;
    }
    return true;
}

const char* GSP::Gsp_LCBlock_getDatset(void* paramLCBInfo){

    // 异常信息判断
    if(!paramLCBInfo){
        return nullptr;
    }

    // 数据转换
    GetLCBValuesResponsePDU_t* responsePDU = static_cast<GetLCBValuesResponsePDU_t*>(paramLCBInfo);

    // 在 api 层我们约束了仅能单个控制块的设置
    if(responsePDU->lcb.list.size <= 0){
        return nullptr;
    }
    GetLCBValuesResponsePDU__lcb__Member* lcbItem = responsePDU->lcb.list.array[0];

    // 获取数值
    return (char*)lcbItem->choice.value.datSet.buf;
}

int GSP::Gsp_LCBlock_getIntgPd(void* paramLCBInfo) {
    // 异常信息判断
    if(!paramLCBInfo){
        return -1;
    }

    // 数据转换
    GetLCBValuesResponsePDU_t* responsePDU = static_cast<GetLCBValuesResponsePDU_t*>(paramLCBInfo);

    // 在 api 层我们约束了仅能单个控制块的设置
    if(responsePDU->lcb.list.size <= 0){
        return -1;
    }
    GetLCBValuesResponsePDU__lcb__Member* lcbItem = responsePDU->lcb.list.array[0];

    // 获取数值
    return lcbItem->choice.value.intgPd;
}

void GSP::Gsp_LCBlock_free(void* paramLCBInfo){
    // 异常信息判断
    if(!paramLCBInfo){
        return;
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetLCBValuesRequestPDU, paramLCBInfo);
}

bool GSP::Gsp_IedConnection_SetLCBValues(GspIedConnection self,
                                         GspIedClientError* error,
                                         void* paramLCBRefs){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // 参数转换
    GetLCBValuesResponsePDU_t* responsePDU = static_cast<GetLCBValuesResponsePDU_t*>(paramLCBRefs);
    SetLCBValuesRequestPDU__lcb__Member* requestItem = (SetLCBValuesRequestPDU__lcb__Member*)GspMemory_calloc(1, sizeof(SetLCBValuesRequestPDU__lcb__Member));
    GetLCBValuesResponsePDU__lcb__Member* lcbItem = responsePDU->lcb.list.array[0];
    OCTET_STRING_fromBuf(&requestItem->reference, (char*)lcbItem->choice.value.logRef.buf, lcbItem->choice.value.logRef.size);
    requestItem->logEna = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
    *(requestItem->logEna) = lcbItem->choice.value.logEna;

    // mms 层接口调用
    GspLinkedList paramList = GspLinkedList_create();
    GspLinkedList_add(paramList, requestItem);
    GspLinkedList lcbList = GspMmsConnection_setLCBValues(self->connection, &mmsError, paramList);
    GspLinkedList_destroyStatic(paramList);

    // 错误代码映射
    if(!lcbList){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
        return false;
    }

    return true;
}

GspLinkedList GSP::Gsp_IedConnection_QueryLogByTime(GspIedConnection self,
                                                    GspIedClientError* error,
                                                    const char* paramLogRefs,
                                                    const char* startTime,
                                                    const char* stopTime,
                                                    const char* afterEntryID){
    // 错误代码
    GspMmsError mmsError = GSP_MMS_ERROR_NONE;
    if (error) {
        *error = GSP_IED_ERROR_OK;
    }

    // mms 层接口调用
    GspLinkedList loginfo = GspMmsConnection_queryLogByTime(self->connection, &mmsError, paramLogRefs, startTime, stopTime, afterEntryID);

    // 错误代码映射
    if(!loginfo){
        *error = GspIedConnection_mapMmsErrorToIedError(mmsError);
    }

    return loginfo;
}
