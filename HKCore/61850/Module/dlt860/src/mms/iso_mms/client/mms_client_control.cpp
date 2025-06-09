#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"
#include "SelectErrorPDU.h"
#include "SelectRequestPDU.h"
#include "SelectResponsePDU.h"
#include "dlt860_client.h"
#ifdef NOT_USE_IN_C11
#include <time.h>
//#include <afx.h>
#else
#include <chrono>
#endif

using namespace GSP;

bool mmsClient_createSelectRequest(GspMmsConnection self,
                                   GspByteBuffer* outMessage,
                                   uint16_t invokeId,
                                   const char* paramSelectRefs){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装选择数据失败\n");
        return false;
    }
    if(paramSelectRefs == nullptr){
        printf("封装选择时请求参数为空\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_Select);

    // 请求数据参数
    SelectRequestPDU_t *selectRequest = static_cast<SelectRequestPDU_t*>(GspMemory_calloc(1, sizeof(SelectRequestPDU_t)));
    memset(selectRequest, 0, sizeof(SelectRequestPDU_t));
    OCTET_STRING_fromBuf(&selectRequest->reference, paramSelectRefs, static_cast<int>(strlen(paramSelectRefs)));

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SelectRequestPDU,
                                                nullptr,
                                                selectRequest,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize - 2));
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("SelectRequestPDU_t encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_SelectRequestPDU, selectRequest);

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
        printf("APER: 选择请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_SelectRequestPDU, selectRequest);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_SelectRequestPDU, selectRequest);
    return true;
}

void mmsClient_parseSelectResponse(GspByteBuffer* message, GspLinkedList* outSelect){
    // 异常判断
    if(message == nullptr){
        printf("获取Select帧回应数据处理失败\n");
        return;
    }

    // 解析请求消息
    SelectResponsePDU_t *selectResponse = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_SelectResponsePDU,
                                               (void **)(&selectResponse),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("SelectResponsePDU_t decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_SelectResponsePDU, selectResponse);
        return;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: Select应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_SelectResponsePDU, selectResponse);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outSelect == nullptr){
        *outSelect = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outSelect, selectResponse);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_SelectResponsePDU, selectResponse);
    return;
}


bool mmsClient_createOpRequest(GspMmsConnection self,
                               GspByteBuffer* outMessage,
                               uint16_t invokeId,
                               const char* controlReference,
                               GspMmsValue* paramValue,
                               Originator__orCat paramOrCat,
                               const char* paramOrIdent,
                               bool syncCheck,
                               bool lockCheck,
                               bool test){
    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_Operate);

    // 请求数据参数
    OperateRequestPDU_t* operateRequest = static_cast<OperateRequestPDU_t*>(GspMemory_calloc(1, sizeof(OperateRequestPDU_t)));
    memset(operateRequest, 0, sizeof(OperateRequestPDU_t));

    // 控制对象refs
    OCTET_STRING_fromBuf(&operateRequest->reference, controlReference, static_cast<int>(strlen(controlReference)));

    // 控制值
    GspMmsValue_cloneFromOther(&operateRequest->ctlVal, paramValue);

    // origin
    operateRequest->origin.orCat = paramOrCat;
    OCTET_STRING_fromBuf(&operateRequest->origin.orIdent, paramOrIdent, static_cast<int>(strlen(paramOrIdent)));

    // 控制值数量(默认只控制一个)
    operateRequest->ctlNum = 1;

    // 时间
#ifdef NOT_USE_IN_C11
#ifdef _PSX_QT_LINUX_  zhouhj 20230101 linux
//    chrono::milliseconds ms = chrono::duration_cast< chrono::milliseconds >( chrono::system_clock::now().time_since_epoch());
   GspMmsValue* timeValue = GspMmsValue_newUtcTimeByMsTime(0);
#else
	time_t tmClock;
	SYSTEMTIME tmSys;   
	::GetLocalTime(&tmSys); 
	time(&tmClock); /*当前time_t类型UTC时间*/
	uint64_t nMsValue = tmClock*1000+tmSys.wMilliseconds;
	GspMmsValue* timeValue = GspMmsValue_newUtcTimeByMsTime(nMsValue);
#endif
#else
    chrono::milliseconds ms = chrono::duration_cast< chrono::milliseconds >( chrono::system_clock::now().time_since_epoch());
    GspMmsValue* timeValue = GspMmsValue_newUtcTimeByMsTime(ms.count());
#endif
    OCTET_STRING_fromBuf(&operateRequest->t, (char*)timeValue->choice.utc_time.buf, timeValue->choice.utc_time.size);

    // test(固定 false)
    operateRequest->test = test;

    // check
    GspMmsValue* check = GspMmsValue_newBitString(2);
    GspMmsValue_setBitStringBit(check, 0 , syncCheck);
    GspMmsValue_setBitStringBit(check, 1 , lockCheck);
    BitString_Update(operateRequest->check, &(check->choice.bit_string));


    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_OperateRequestPDU,
                                                nullptr,
                                                operateRequest,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize - 2));
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("OperateRequestPDU_t encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_OperateRequestPDU, operateRequest);

        return false;
    }

    // 内存释放
    GspMmsValue_delete(timeValue);
    GspMmsValue_delete(check);

    // 设置缓存尺寸
    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 选择请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_OperateRequestPDU, operateRequest);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_OperateRequestPDU, operateRequest);
    return true;
}

void mmsClient_parseOpResponse(GspByteBuffer* message, GspLinkedList* outSelect){
    // 异常判断
    if(message == nullptr){
        printf("获取Operate应答帧数据处理失败\n");
        return;
    }

    // 解析请求消息
    OperateResponsePDU_t *opResponse = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_OperateResponsePDU,
                                               (void **)(&opResponse),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("asn_DEF_OperateResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_OperateResponsePDU, opResponse);
        return;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: Operate应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_OperateResponsePDU, opResponse);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outSelect == nullptr){
        *outSelect = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outSelect, opResponse);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_OperateResponsePDU, selectResponse);
    return;
}

bool mmsClient_createSelectWithValueRequest(GspMmsConnection self,
                                            GspByteBuffer* outMessage,
                                            uint16_t invokeId,
                                            const char* paramSelectRefs,
                                            GspMmsValue* paramValue,
                                            int paramOrCat,
                                            const char* paramOrIdent,
                                            bool syncCheck,
                                            bool lockCheck,
                                            bool test){
    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_SelectWithValue);

    // 请求数据参数
    SelectWithValueRequestPDU_t* selectWithValueRequest = static_cast<SelectWithValueRequestPDU_t*>(GspMemory_calloc(1, sizeof(SelectWithValueRequestPDU_t)));
    memset(selectWithValueRequest, 0, sizeof(SelectWithValueRequestPDU_t));

    // reference
    OCTET_STRING_fromBuf(&selectWithValueRequest->reference, paramSelectRefs, static_cast<int>(strlen(paramSelectRefs)));

    // ctlVal
    GspMmsValue_cloneFromOther(&selectWithValueRequest->ctlVal, paramValue);

    // origin
    selectWithValueRequest->origin.orCat = paramOrCat;
    OCTET_STRING_fromBuf(&selectWithValueRequest->origin.orIdent, paramOrIdent, static_cast<int>(strlen(paramOrIdent)));

    // ctlNum
    selectWithValueRequest->ctlNum = 1;

    // t
#ifdef NOT_USE_IN_C11
#ifdef _PSX_QT_LINUX_  zhouhj 20230101 linux
    GspMmsValue* timeValue = GspMmsValue_newUtcTimeByMsTime(0);
#else
	time_t tmClock;
	SYSTEMTIME tmSys;   
	::GetLocalTime(&tmSys); 
	time(&tmClock); /*当前time_t类型UTC时间*/
	uint64_t nMsValue = tmClock*1000+tmSys.wMilliseconds;
	GspMmsValue* timeValue = GspMmsValue_newUtcTimeByMsTime(nMsValue);
#endif
#else
    chrono::milliseconds ms = chrono::duration_cast< chrono::milliseconds >( chrono::system_clock::now().time_since_epoch());
    GspMmsValue* timeValue = GspMmsValue_newUtcTimeByMsTime(ms.count());
#endif
    OCTET_STRING_fromBuf(&selectWithValueRequest->t, (char*)timeValue->choice.utc_time.buf, timeValue->choice.utc_time.size);

    // test
    selectWithValueRequest->test = test;

    // check
    GspMmsValue* check = GspMmsValue_newBitString(2);
    GspMmsValue_setBitStringBit(check, 0 , syncCheck);
    GspMmsValue_setBitStringBit(check, 1 , lockCheck);
    BitString_Update(selectWithValueRequest->check, &(check->choice.bit_string));

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SelectWithValueRequestPDU,
                                                nullptr,
                                                selectWithValueRequest,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize - 2));
    // 内存释放
    GspMmsValue_delete(timeValue);
    GspMmsValue_delete(check);

    // 编码结果判断
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("SelectWithValueRequestPDU_t encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_SelectWithValueRequestPDU, selectWithValueRequest);

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
        printf("APER: 选择请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_SelectWithValueRequestPDU, selectWithValueRequest);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_SelectWithValueRequestPDU, selectWithValueRequest);
    return true;
}

void mmsClient_parseSelectWithValueResponse(GspByteBuffer* message, GspLinkedList* outSelect){
    // 异常判断
    if(message == nullptr){
        printf("获取 SelectWithValue 应答帧数据处理失败\n");
        return;
    }

    // 解析请求消息
    SelectWithValueResponsePDU_t *swvResponse = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_SelectWithValueResponsePDU,
                                               (void **)(&swvResponse),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("SelectWithValueResponsePDU_t decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_SelectWithValueResponsePDU, swvResponse);
        return;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: SelectWithValueResponsePDU 应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_SelectWithValueResponsePDU, swvResponse);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outSelect == nullptr){
        *outSelect = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outSelect, swvResponse);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_SelectWithValueResponsePDU, selectResponse);
    return;
}
