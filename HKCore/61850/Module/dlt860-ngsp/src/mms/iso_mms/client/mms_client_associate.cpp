#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"
#include "AssociateRequestPDU.h"
#include "AssociateResponsePDU.h"
#include "AssociateNegotiateResponsePDU.h"
#include "AssociateNegotiateErrorPDU.h"
#include "AssociateNegotiateRequestPDU.h"
#include "AssociateNegotiateErrorPDU.h"
#include "AssociateNegotiateResponsePDU.h"
#include "AbortRequestPDU.h"
#include "ReleaseErrorPDU.h"
#include "ReleaseRequestPDU.h"
#include "ReleaseResponsePDU.h"

long g_nProtocolVersion = 0x201;


bool mmsClient_createAssociateNegotiateRequest(GspMmsConnection self,
                                               GspByteBuffer* outMessage,
                                               uint16_t invokeId,
                                               uint16_t paramApduSize,
                                               uint32_t paramAsduSize){
    // 异常判断
    if(outMessage == nullptr){
        Global_LogString("封装关联协商帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_AssociateNegotiate);

    // 请求数据参数
    AssociateNegotiateRequestPDU_t *associateNegotiateRequest = (AssociateNegotiateRequestPDU_t*)GspMemory_calloc(1, sizeof(AssociateNegotiateRequestPDU_t));
    memset(associateNegotiateRequest, 0, sizeof(AssociateNegotiateRequestPDU_t));
    associateNegotiateRequest->apduSize = paramApduSize;
    associateNegotiateRequest->asduSize = paramAsduSize;
    associateNegotiateRequest->protocolVersion = g_nProtocolVersion/*0x201*/;//zhouhj 20211111 由200改为201
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_AssociateNegotiateRequestPDU,
                                                nullptr,
                                                associateNegotiateRequest,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        Global_LogString("associate negotitate encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_AssociateNegotiateRequestPDU, associateNegotiateRequest);

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
        printf("APER: 关联协商请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_AssociateNegotiateRequestPDU, associateNegotiateRequest);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_AssociateNegotiateRequestPDU, associateNegotiateRequest);

    return true;
}

bool mmsClient_parseAssociateNegotiateResponse(GspByteBuffer* message, uint16_t* invokeId){
    // 异常判断
    if(message == nullptr){
        Global_LogString("关联协商回应帧数据处理失败\n");
        return false;
    }

    // 解析请求消息
    AssociateNegotiateResponsePDU_t *associateNegotiateResponse = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_AssociateNegotiateResponsePDU,
                                               (void **)&associateNegotiateResponse,
                                               message->buffer,
                                               (size_t)message->size);
    if(rval.code != RC_OK) {
        Global_LogString("associate decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_AssociateNegotiateResponsePDU, associateNegotiateResponse);
        return false;
    }

    // 设置协商后的参数值(TODO)

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 关联协商应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_AssociateNegotiateResponsePDU, associateNegotiateResponse);
        printf("apdu: %i\n", (uint16_t)associateNegotiateResponse->apduSize);
        printf("asdu: %i\n", (uint16_t)associateNegotiateResponse->asduSize);
        printf("protocolVersion: %i\n", (INT32U_t)associateNegotiateResponse->protocolVersion);
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_AssociateNegotiateResponsePDU, associateNegotiateResponse);
    return true;
}

bool mmsClient_createAssociateRequest(GspMmsConnection self,
                                      GspByteBuffer* outMessage,
                                      uint16_t invokeId,
                                      uint8_t* paramAccessPoint){
    // 异常判断
    if(outMessage == nullptr){
        Global_LogString("封装关联帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_Associate);

    // 封装关联请求数据包
    AssociateRequestPDU_t *associatePkt = (AssociateRequestPDU_t*)GspMemory_calloc(1, sizeof(AssociateRequestPDU_t));
    memset(associatePkt, 0, sizeof (AssociateRequestPDU_t));

    // TODO 证书

    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_AssociateRequestPDU,
                                                nullptr,
                                                associatePkt,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        Global_LogString("关联请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_AssociateRequestPDU, associatePkt);
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
        printf("APER: 关联请求帧请求信息\n");
        xer_fprint(stdout, &asn_DEF_AssociateRequestPDU, associatePkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_AssociateRequestPDU, associatePkt);
    return true;
}

bool mmsClient_parseAssociateResponse(GspByteBuffer* message, GspLinkedList *outData){
    // 异常判断
    if(message == nullptr){
        printf("关联回应帧数据处理失败\n");
        return false;
    }
    // 解析请求消息
    AssociateResponsePDU_t *associateResponse = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_AssociateResponsePDU,
                                               (void**)&associateResponse,
                                               message->buffer,
                                               (size_t)message->size);
    if(rval.code != RC_OK) {
        printf("关联回应帧解析错误!\n");
        ASN_STRUCT_FREE(asn_DEF_AssociateResponsePDU, associateResponse);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 关联应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_AssociateResponsePDU, associateResponse);
    }

    // 数据赋值
    if(!*outData){
        *outData = GspLinkedList_create();
    }
    GspLinkedList_add(*outData, associateResponse);

    // 释放内存(外部释放)
    // ASN_STRUCT_FREE(asn_DEF_AssociateResponsePDU, associateResponse);

    // 解析后的数据处理(TODO)
    return true;
}

bool mmsClient_createAbortRequest(GspMmsConnection self,
                                  GspByteBuffer* outMessage,
                                  uint16_t invokeId,
                                  uint8_t reasonCode,
                                  uint8_t* associationId){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装关联协商帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_Abort);

    // 请求数据参数
    AbortRequestPDU_t *abortRequest = (AbortRequestPDU_t *)GspMemory_calloc(1, sizeof(AbortRequestPDU_t));
    memset(abortRequest, 0, sizeof(AbortRequestPDU_t));
    abortRequest->reason = reasonCode;
    OCTET_STRING_fromString(&abortRequest->associationId, (char *)associationId);
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_AbortRequestPDU,
                                                nullptr,
                                                abortRequest,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);

    // 编码错误
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        Global_LogString("中止链接请求编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_AbortRequestPDU, abortRequest);

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
        printf("APER: 中止帧请求信息\n");
        xer_fprint(stdout, &asn_DEF_AbortRequestPDU, abortRequest);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_AbortRequestPDU, abortRequest);

    return true;
}

bool mmsClient_createConcludeRequest(GspMmsConnection self,
                                     GspByteBuffer* outMessage,
                                     uint16_t invokeId,
                                     uint8_t* associationId){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装关联协商帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_Release);

    // 请求数据封装
    ReleaseRequestPDU_t *releasePkg = (ReleaseRequestPDU_t*)GspMemory_calloc(1, sizeof(ReleaseRequestPDU_t));
    memset(releasePkg,0,sizeof (ReleaseRequestPDU_t));
    OCTET_STRING_fromString(&(releasePkg->associationId), (char *)associationId);
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_ReleaseRequestPDU,
                                                nullptr,
                                                releasePkg,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);

    // 编码错误
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        Global_LogString("释放链接请求编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_ReleaseRequestPDU, releasePkg);
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
        printf("APER: 释放关联信息\n");
        xer_fprint(stdout, &asn_DEF_ReleaseRequestPDU, releasePkg);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_ReleaseRequestPDU, releasePkg);
    return true;
}
