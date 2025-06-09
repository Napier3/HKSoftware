#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"
#include "gsp_lib_memory.h"
#include "ACSIClass.h"
#include "gsp_mms_value.h"
#include "GetBRCBValuesErrorPDU.h"
#include "GetBRCBValuesRequestPDU.h"
#include "GetBRCBValuesResponsePDU.h"
#include "SetBRCBValuesRequestPDU.h"
#include "SetBRCBValuesErrorPDU.h"
#include "ReportPDU.h"
#include "GetURCBValuesErrorPDU.h"
#include "GetURCBValuesRequestPDU.h"
#include "GetURCBValuesResponsePDU.h"
#include <string>

using namespace std;

bool mmsClient_createGetBRCBValuesRequest(GspMmsConnection self, 
                                          GspByteBuffer* outMessage,
                                          uint16_t invokeId,
                                          const char * brcbReference){

    // 异常判断
    if(outMessage == nullptr){
        Global_LogString("获取缓存报告控制块请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetBRCBValues);

    // 封装请求数据包
    GetBRCBValuesRequestPDU_t *requestPkt = (GetBRCBValuesRequestPDU_t *)GspMemory_calloc(1, sizeof(GetBRCBValuesRequestPDU_t));
    memset(requestPkt, 0, sizeof(GetBRCBValuesRequestPDU_t));

    // 缓存报告控制块refs
    ObjectReference_t * referenceItem = nullptr;
    if (brcbReference)
    {
        referenceItem = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, brcbReference, strlen(brcbReference));
        ASN_SEQUENCE_ADD(&requestPkt->reference.list, referenceItem);
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetBRCBValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        Global_LogString("创建获取缓存报告控制块值请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetBRCBValuesRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取缓存报告控制块值数据请求\n");
        xer_fprint(stdout, &asn_DEF_GetBRCBValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetBRCBValuesRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseGetBRCBValuesResponse(GspByteBuffer* message,
                                          GspLinkedList* outList){
    // 异常判断
    if(message == nullptr){
        Global_LogString("获取缓存报告控制块回应帧数据处理失败\n");
        return false;
    }

    // 解析获取缓存报告控制块值应答
    GetBRCBValuesResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetBRCBValuesResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        Global_LogString("GetBRCBValuesResponsePDU decode error!\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetBRCBValuesResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        Global_LogString("APER: 获取所有缓存报告控制块应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetBRCBValuesResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outList == nullptr){
        *outList = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outList, static_cast<void*>(responsePkg));

    // 是否有更多的数据
    bool moreFlows = *(responsePkg->moreFollows);

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetBRCBValuesResponsePDU, responsePkg);
    return moreFlows;
}

bool mmsClient_createSetBRCBValuesRequest(GspMmsConnection self, 
                                          GspByteBuffer* outMessage,
                                          uint16_t invokeId,
                                          BRCBControlBlk paramBrcbControlBlk){
    // 异常判断
    if(outMessage == nullptr){
        Global_LogString("设置缓存报告控制块请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_SetBRCBValues);

    // 封装请求数据包
    SetBRCBValuesRequestPDU_t *requestPkt = (SetBRCBValuesRequestPDU_t*)GspMemory_calloc(1, sizeof(SetBRCBValuesRequestPDU_t));
    memset(requestPkt, 0, sizeof(SetBRCBValuesRequestPDU_t));

    // 设置值
    if(paramBrcbControlBlk != nullptr ){
        SetBRCBValuesRequestPDU__brcb__Member *brcbControlBlkItem  = (SetBRCBValuesRequestPDU__brcb__Member *)GspMemory_calloc(1, sizeof(SetBRCBValuesRequestPDU__brcb__Member));

        // 获取用户设置的控制块参数
        GSPRCB brcbControlBlk = paramBrcbControlBlk->brcbControlBlk;

        // refs(最终就是想要拼接成 PE1001LD0/LLN0.brcbCommState02)形式
        string reportRef(paramBrcbControlBlk->reportRefs);

        // 兼容性处理(有的厂家就是不按照规范来 就是用 $ 我们只能做兼容)
        int splitPostion = reportRef.find_first_of("$");
        if(splitPostion != reportRef.npos){
            reportRef.replace(splitPostion, 1, ".");
        }
        OCTET_STRING_fromBuf(&brcbControlBlkItem->reference, reportRef.data(), reportRef.size());

        // rptID
        if(brcbControlBlk->rptID){
            brcbControlBlkItem->rptID = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString129, (const char*)brcbControlBlk->rptID->buf, brcbControlBlk->rptID->size);
        }

        // rptEna
        if(brcbControlBlk->rptEna){
            brcbControlBlkItem->rptEna = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
            *brcbControlBlkItem->rptEna = *brcbControlBlk->rptEna;
        }

        // datSet(这个接口暂时不用处理)
        // brcbControlBlkItem->datSet = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, (const char*)brcbControlBlk->datSet.buf, brcbControlBlk->datSet.size);

        // optFlds
        if(brcbControlBlk->optFlds){
            BitString_Update(brcbControlBlkItem->optFlds, brcbControlBlk->optFlds);
        }

        // bufTm
        if(brcbControlBlk->bufTm){
            brcbControlBlkItem->bufTm = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
            *brcbControlBlkItem->bufTm = *brcbControlBlk->bufTm;
        }

        // trgOps
        if(brcbControlBlk->trgOps){
            BitString_Update(brcbControlBlkItem->trgOps, brcbControlBlk->trgOps);
        }

        // intgPd
        if(brcbControlBlk->intgPd){
            brcbControlBlkItem->intgPd = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
            *brcbControlBlkItem->intgPd = *brcbControlBlk->intgPd;
        }

        // gi
        if(brcbControlBlk->gi){
            brcbControlBlkItem->gi = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
            *brcbControlBlkItem->gi = *brcbControlBlk->gi;
        }

        // purgeBuf
        if(brcbControlBlk->purgeBuf){
            brcbControlBlkItem->purgeBuf = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
            *brcbControlBlkItem->purgeBuf = *brcbControlBlk->purgeBuf;
        }

        // entryID
        if(brcbControlBlk->entryID){
            brcbControlBlkItem->entryID = (EntryID_t*)GspMemory_calloc(1, sizeof(EntryID_t));
            OCTET_STRING_fromBuf(brcbControlBlkItem->entryID, (const char*)brcbControlBlk->entryID->buf, brcbControlBlk->entryID->size);
        }

        ASN_SEQUENCE_ADD(&requestPkt->brcb.list, brcbControlBlkItem);
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SetBRCBValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        Global_LogString("设置获取缓存报告控制块值请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_SetBRCBValuesRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 设置缓存报告控制块值数据请求\n");
        xer_fprint(stdout, &asn_DEF_SetBRCBValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_SetBRCBValuesRequestPDU, requestPkt);
    return true;
}

bool mmsClient_parseSetBRCBErrorValues(GspByteBuffer* message,
                                       GspLinkedList* outData){
    // 异常判断
    if(message == nullptr){
        // printf("解析缓存报告控制块回应帧数据处理获取到了空数据包，按照协议认为设置成功\n");
        return true;
    }

    // 解析获取缓存报告控制块值应答
    SetBRCBValuesErrorPDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_SetBRCBValuesErrorPDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("SetBRCBValuesErrorPDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_SetBRCBValuesErrorPDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析设置缓存报告控制块应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_SetBRCBValuesErrorPDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetBRCBValuesResponsePDU, responsePkg);
    return true;
}

bool mmsClient_parseReportPDU(GspByteBuffer* message,
                              GspLinkedList* outData){
    // 异常判断
    if(message == nullptr){
        Global_LogString("解析报告失败, 传过来的数据为空\n");
        return false;
    }

    // 解析报告数据
    ReportPDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_ReportPDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        Global_LogString("parserReportPDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_ReportPDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析报告数据\n");
        xer_fprint(stdout, &asn_DEF_ReportPDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_ReportPDU, responsePkg);
    return true;
}

bool mmsClient_createGetURCBValuesRequest(GspMmsConnection self,
                                          GspByteBuffer* outMessage,
                                          uint16_t invokeId,
                                          const char* brcbReference){
    // 异常判断
    if(outMessage == nullptr){
        Global_LogString("获取非缓存报告控制块请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetURCBValues);

    // 封装请求数据包
    GetURCBValuesRequestPDU_t *requestPkt = (GetURCBValuesRequestPDU_t*)GspMemory_calloc(1, sizeof(GetURCBValuesRequestPDU_t));
    memset(requestPkt, 0, sizeof(GetURCBValuesRequestPDU_t));

    // 非缓存报告控制块refs
    ObjectReference_t * referenceItem = nullptr;
    if (brcbReference)
    {
        referenceItem = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, brcbReference, strlen(brcbReference));
        ASN_SEQUENCE_ADD(&(requestPkt->reference.list), referenceItem);
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetURCBValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        Global_LogString("创建获取非缓存报告控制块值请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetURCBValuesRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取非缓存报告控制块值数据请求\n");
        xer_fprint(stdout, &asn_DEF_GetURCBValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetURCBValuesRequestPDU, requestPkt);

    return true;
}

bool mmsCLient_parseGetURCBValuesResponse(GspByteBuffer* message,
                                          GspLinkedList* outList){
    // 异常判断
    if(message == nullptr){
        Global_LogString("获取非缓存报告控制块回应帧数据处理失败\n");
        return false;
    }

    // 解析获取缓存报告控制块值应答
    GetURCBValuesResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetURCBValuesResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        Global_LogString("asn_DEF_GetURCBValuesResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetURCBValuesResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        Global_LogString("APER: 获取所有非缓存报告控制块应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetURCBValuesResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outList == nullptr){
        *outList = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outList, static_cast<void*>(responsePkg));

    // 是否有更多的数据
    bool moreFlows = *(responsePkg->moreFollows);

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetURCBValuesResponsePDU, responsePkg);
    return moreFlows;
}

bool mmsClient_createSetURCBValuesRequest(GspMmsConnection self,
                                          GspByteBuffer* outMessage,
                                          uint16_t invokeId,
                                          URCBControlBlk paramUrcbControlBlk){
    // 异常判断
    if(outMessage == nullptr){
        Global_LogString("设置非缓存报告控制块请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_SetURCBValues);

    // 封装请求数据包
    SetURCBValuesRequestPDU_t *requestPkt = (SetURCBValuesRequestPDU_t*)GspMemory_calloc(1, sizeof(SetURCBValuesRequestPDU_t));
    memset(requestPkt, 0, sizeof(requestPkt));

    // 设置值
    SetURCBValuesRequestPDU__urcb__Member *urcbControlBlkItem = nullptr;
    if(paramUrcbControlBlk != nullptr ){
        urcbControlBlkItem = (SetURCBValuesRequestPDU__urcb__Member *)GspMemory_calloc(1, sizeof(SetURCBValuesRequestPDU__urcb__Member));

        // 获取用户设置的控制块参数
        GSPRCB urcbControlBlk = paramUrcbControlBlk->urcbControlBlk;

        // refs(最终就是想要拼接成 PE1001LD0/LLN0.urcbCommState02)形式
        string reportRef(paramUrcbControlBlk->reportRefs);

        // 兼容性处理(有的厂家就是不按照规范来 就是用 $ 我们只能做兼容, 且目前只替换遇到的第一个)
        int splitPostion = reportRef.find_first_of("$");
        if(splitPostion != reportRef.npos){
            reportRef.replace(splitPostion, 1, ".");
        }
        OCTET_STRING_fromBuf(&urcbControlBlkItem->reference, reportRef.data(), reportRef.size());

        // rptID
        if(urcbControlBlk->rptID){
            urcbControlBlkItem->rptID = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString129, (const char*)urcbControlBlk->rptID->buf, urcbControlBlk->rptID->size);
        }

        // rptEna
        if(urcbControlBlk->rptEna){
            urcbControlBlkItem->rptEna = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
            *urcbControlBlkItem->rptEna = *urcbControlBlk->rptEna;
        }

        // datSet(这个接口暂时不用处理)
        // brcbControlBlkItem->datSet = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, (const char*)brcbControlBlk->datSet.buf, brcbControlBlk->datSet.size);

        // optFlds
        if(urcbControlBlk->optFlds){
            BitString_Update(urcbControlBlkItem->optFlds, urcbControlBlk->optFlds);
        }

        // bufTm
        if(urcbControlBlk->bufTm){
            urcbControlBlkItem->bufTm = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
            *urcbControlBlkItem->bufTm = *urcbControlBlk->bufTm;
        }

        // trgOps
        if(urcbControlBlk->trgOps){
            BitString_Update(urcbControlBlkItem->trgOps, urcbControlBlk->trgOps);
        }

        // intgPd
        if(urcbControlBlk->intgPd){
            urcbControlBlkItem->intgPd = (INT32U_t*)GspMemory_calloc(1, sizeof(INT32U_t));
            *urcbControlBlkItem->intgPd = *urcbControlBlk->intgPd;
        }

        // gi
        if(urcbControlBlk->gi){
            urcbControlBlkItem->gi = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
            *urcbControlBlkItem->gi = *urcbControlBlk->gi;
        }

        // resv
        if(urcbControlBlk->resv){
            urcbControlBlkItem->resv = (BOOLEAN_t*)GspMemory_calloc(1, sizeof(BOOLEAN_t));
            *urcbControlBlkItem->resv = *urcbControlBlk->resv;
        }

        ASN_SEQUENCE_ADD(&requestPkt->urcb.list, urcbControlBlkItem);
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SetURCBValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        Global_LogString("设置获取非缓存报告控制块值请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_SetURCBValuesRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 设置非缓存报告控制块值数据请求\n");
        xer_fprint(stdout, &asn_DEF_SetURCBValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }


    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_SetURCBValuesRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseSetURCBValuesResponse(GspByteBuffer* message,
                                          GspLinkedList* outData){
    // 异常判断
    if(message == nullptr){
        // printf("解析非缓存报告控制块回应帧数据处理获取到了空数据包，按照协议认为设置成功\n");
        return true;
    }

    // 解析获取缓存报告控制块值应答
    SetURCBValuesErrorPDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_SetURCBValuesErrorPDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        Global_LogString("SetURCBValuesErrorPDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_SetURCBValuesErrorPDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析设置非缓存报告控制块应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_SetURCBValuesErrorPDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_SetURCBValuesErrorPDU, responsePkg);
    return true;
}
