#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"

#define  BINARYTIME_SIZE    6

bool mmsClient_createGetLCBValuesRequest(GspMmsConnection self,
                                         GspByteBuffer* outMessage,
                                         uint16_t invokeId,
                                         GspLinkedList paramRefsList){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装获取日志控制块帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetLCBValues);

    // 请求数据参数
    GetLCBValuesRequestPDU_t* requestPDU = (GetLCBValuesRequestPDU_t*)GspMemory_calloc(1, sizeof(GetLCBValuesRequestPDU_t));

    // 设置 refs
    for(int index=0; index < GspLinkedList_size(paramRefsList); ++index){
        char* refs = (char*)GspLinkedList_get(paramRefsList, index);
#ifdef NOT_USE_IN_C11
        OCTET_STRING_t* pString = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, refs, strlen(refs));
        ASN_SEQUENCE_ADD(&requestPDU->reference.list, pString);
#else
        auto str = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, refs, strlen(refs));
        ASN_SEQUENCE_ADD(&requestPDU->reference.list, str);
#endif
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetLCBValuesRequestPDU,
                                                nullptr,
                                                requestPDU,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("GetLCBValuesRequestRequest encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetLCBValuesRequestPDU, requestPDU);
        return false;
    }

    // 设置缓存尺寸
    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取日志控制块请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetLCBValuesRequestPDU, requestPDU);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetLCBValuesRequestPDU, requestPDU);
    return true;
}

bool mmsClient_parseGetLCBValuesResponse(GspByteBuffer* message, GspLinkedList* outDataList){

    // 异常判断
    if(message == nullptr){
        printf("获取日志控制块回应帧数据处理失败\n");
        return false;
    }

    // 解析报文
    GetLCBValuesResponsePDU_t* responsePDU = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetLCBValuesResponsePDU,
                                               (void **)(&responsePDU),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetLCBValuesResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetLCBValuesResponsePDU, responsePDU);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取日志控制快应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetLCBValuesResponsePDU, responsePDU);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outDataList == nullptr){
        *outDataList = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outDataList, responsePDU);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetLCBValuesResponsePDU, GetLCBValuesResponse);

    return *(responsePDU->moreFollows);
}

bool mmsClient_createSetLCBValuesRequest(GspMmsConnection self,
                                         GspByteBuffer* outMessage,
                                         uint16_t invokeId,
                                         GspLinkedList paramLCBList){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装设置日志控制块帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_SetLCBValues);

    // 请求数据参数
    SetLCBValuesRequestPDU_t* requestPDU = (SetLCBValuesRequestPDU_t*)GspMemory_calloc(1, sizeof(SetLCBValuesRequestPDU_t));

    // 设置 lcb
    for(int index=0; index < GspLinkedList_size(paramLCBList); ++index){
        SetLCBValuesRequestPDU__lcb__Member* lcbItem = (SetLCBValuesRequestPDU__lcb__Member*)GspLinkedList_get(paramLCBList, index);
        ASN_SEQUENCE_ADD(&requestPDU->lcb.list, lcbItem);
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SetLCBValuesRequestPDU,
                                                nullptr,
                                                requestPDU,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("SetLCBValuesRequestRequest encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_SetLCBValuesRequestPDU, requestPDU);
        return false;
    }

    // 设置缓存尺寸
    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 设置日志控制块请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_SetLCBValuesRequestPDU, requestPDU);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_SetLCBValuesRequestPDU, requestPDU);
    return true;
}

bool mmsClient_parseSetLCBErrorValues(GspByteBuffer* message,
                                      GspLinkedList* outData) {
    // 异常判断
    if(message == nullptr){
        // printf("解析日志控制块回应帧数据处理获取到了空数据包，按照协议认为设置成功\n");
        return true;
    }

    // 解析获取缓存报告控制块值应答
    SetLCBValuesErrorPDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_SetLCBValuesErrorPDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("SetLCBValuesErrorPDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_SetLCBValuesErrorPDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析设置日志报告控制块应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_SetLCBValuesErrorPDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_SetLCBValuesErrorPDU, responsePkg);
    return true;
}

bool mmsClient_createQueryLogByTimeRequest(GspMmsConnection self,
                                           GspByteBuffer* outMessage,
                                           uint16_t invokeId,
                                           const char* logRefs,
                                           const char* startTime,
                                           const char* endTime,
                                           const char* entryAfter){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装查询日志信息帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_QueryLogByTime);

    // 请求数据参数
    QueryLogByTimeRequestPDU_t* requestPDU = (QueryLogByTimeRequestPDU_t*)GspMemory_calloc(1, sizeof(QueryLogByTimeRequestPDU_t));

    // log refs
    if(logRefs){
        OCTET_STRING_fromBuf(&requestPDU->logReference, logRefs, strlen(logRefs));
    }

    // 设置开始时间
    if(startTime){
        requestPDU->startTime = OCTET_STRING_new_fromBuf(&asn_DEF_EntryTime, startTime, BINARYTIME_SIZE);
    }

    // 设置结束时间
    if(endTime){
        requestPDU->stopTime = OCTET_STRING_new_fromBuf(&asn_DEF_EntryTime, endTime, BINARYTIME_SIZE);
    }

    // entry after
    if(entryAfter){
        requestPDU->entryAfter = OCTET_STRING_new_fromBuf(&asn_DEF_EntryID, entryAfter, strlen(entryAfter));
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_QueryLogByTimeRequestPDU,
                                                nullptr,
                                                requestPDU,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("QueryLogByTimeRequest encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_QueryLogByTimeRequestPDU, requestPDU);
        return false;
    }

    // 设置缓存尺寸
    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 查询日志信息请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_QueryLogByTimeRequestPDU, requestPDU);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_QueryLogByTimeRequestPDU, requestPDU);
    return true;
}

bool mmsClient_parseQueryLogByTimeValues(GspByteBuffer* message,
                                         GspLinkedList* outDataList) {
    // 异常判断
    if(message == nullptr){
        printf("查询日志回应帧数据处理失败\n");
        return false;
    }

    // 解析报文
    QueryLogByTimeResponsePDU_t* responsePDU = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_QueryLogByTimeResponsePDU,
                                               (void **)(&responsePDU),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("QueryLogByTimeResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_QueryLogByTimeResponsePDU, responsePDU);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 查询日志信息应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_QueryLogByTimeResponsePDU, responsePDU);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outDataList == nullptr){
        *outDataList = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outDataList, responsePDU);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_QueryLogByTimeResponsePDU, GetLCBValuesResponse);

    return *(responsePDU->moreFollows);
}
