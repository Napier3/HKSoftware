#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"
#include "GetAllDataValuesErrorPDU.h"
#include "GetAllDataValuesRequestPDU.h"
#include "GetAllDataValuesResponsePDU.h"
#include "GetAllCBValuesErrorPDU.h"
#include "GetAllCBValuesRequestPDU.h"
#include "GetAllCBValuesResponsePDU.h"
#include "GetDataValuesErrorPDU.h"
#include "GetDataValuesRequestPDU.h"
#include "GetDataValuesResponsePDU.h"
#include "gsp_lib_memory.h"
#include "ACSIClass.h"
#include "gsp_mms_value.h"


bool mmsClient_createGetAllDataValuesRequest(GspMmsConnection self,
                                             GspByteBuffer* outMessage,
                                             uint16_t invokeId,
                                             const char* reference,
                                             const char* referenceAfter,
                                             GspFunctionalConstraint paramFC,
                                             GspRefType paramRefType){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装获取所有数据值帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetAllDataValues);

    // 封装请求数据包
    GetAllDataValuesRequestPDU_t *requestPkt = (GetAllDataValuesRequestPDU_t *)GspMemory_calloc(1, sizeof(GetAllDataValuesRequestPDU_t));
    memset(requestPkt, 0, sizeof(GetAllDataValuesRequestPDU_t));

    // fc
    if(paramFC != DLT860_FC_NONE && paramFC != DLT860_FC_ALL){
        char* fcStr = GspFunctionalConstraint_toString(paramFC);
        requestPkt->fc = OCTET_STRING_new_fromBuf(&asn_DEF_FunctionalConstraint, fcStr, static_cast<int>(strlen(fcStr)));
        delete [] fcStr;
    }

    // reference
    requestPkt->reference.present = static_cast<GetAllDataValuesRequestPDU__reference_PR>(paramRefType);
    if(reference){
        if(paramRefType == static_cast<GspRefType>(GetAllDataDefinitionRequestPDU__reference_PR_ldName)) {
            OCTET_STRING_fromBuf(&requestPkt->reference.choice.ldName, reference, static_cast<int>(strlen(reference)));
        } else {
            OCTET_STRING_fromBuf(&requestPkt->reference.choice.lnReference, reference, static_cast<int>(strlen(reference)));
        }
    } else {
        printf("创建获取所有数据定义请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_GetAllDataValuesRequestPDU, requestPkt);
        return false;
    }

    // 可选参数
    if(referenceAfter){
        requestPkt->referenceAfter = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, referenceAfter, static_cast<int>(strlen(referenceAfter)));
    }

    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetAllDataValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取所有数据定义请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_GetAllDataValuesRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取所有数据定义请求\n");
        xer_fprint(stdout, &asn_DEF_GetAllDataValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetAllDataValuesRequestPDU, requestPkt);

    return true;
}


bool mmsClient_parseGetAllDataValuesResponse (GspByteBuffer* message, GspLinkedList *outList){
    // 异常判断
    if(message == nullptr){
        printf("获取所有数据值回应帧数据处理失败\n");
        return false;
    }

    // 解析获取所有数据值应答
    GetAllDataValuesResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetAllDataValuesResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetAllDataValuesResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetAllDataValuesResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取所有数据值应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetAllDataValuesResponsePDU, responsePkg);
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
    // ASN_STRUCT_FREE(asn_DEF_GetAllDataValuesResponsePDU, responsePkg);
    return moreFlows;
}


bool mmsCLient_createGetAllCBValuesRequest(GspMmsConnection self,
                                           GspByteBuffer* outMessage,
                                           uint16_t invokeId,
                                           const char* reference,
                                           const char* referenceAfter,
                                           GspRefType paramRefType,
                                           GspACSICLASS paramType){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装读所有控制块值帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetAllCBValues);

    // 封装请求数据包
    GetAllCBValuesRequestPDU *requestPkt = (GetAllCBValuesRequestPDU*)GspMemory_calloc(1, sizeof(GetAllCBValuesRequestPDU));
    memset(requestPkt, 0, sizeof(GetAllCBValuesRequestPDU));

    // reference
    requestPkt->reference.present = static_cast<GetAllCBValuesRequestPDU__reference_PR>(paramRefType);
    if(reference){
        if(paramRefType == static_cast<GspRefType>(GetAllCBValuesRequestPDU__reference_PR_ldName)) {
            OCTET_STRING_fromBuf(&requestPkt->reference.choice.ldName, reference, static_cast<int>(strlen(reference)));
        } else {
            OCTET_STRING_fromBuf(&requestPkt->reference.choice.lnReference, reference, static_cast<int>(strlen(reference)));
        }
    } else {
        printf("创建读所有控制块值请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetAllCBValuesRequestPDU, requestPkt);
        return false;
    }

    // 可选参数
    if(referenceAfter){
        requestPkt->referenceAfter = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, referenceAfter, static_cast<int>(strlen(referenceAfter)));
    }

    // acsi
    requestPkt->acsiClass = paramType;

    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetAllCBValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建读所有控制块值请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetAllCBValuesRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 读所有控制块值请求\n");
        xer_fprint(stdout, &asn_DEF_GetAllCBValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetAllCBValuesRequestPDU, requestPkt);

    return true;
}


bool mmsClient_parseGetAllCBValuesResponse(GspByteBuffer* message, GspLinkedList *outList){
    // 异常判断
    if(message == nullptr){
        printf("获取读所有控制块值回应帧数据处理失败\n");
        return false;
    }

    // 解析读所有控制块值应答
    GetAllCBValuesResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetAllCBValuesResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetAllCBValuesResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetAllCBValuesResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取读所有控制块值应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetAllCBValuesResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outList == nullptr){
        *outList = GspLinkedList_create();
    }

    // 添加到列表里面
    GspLinkedList_add(*outList, static_cast<void*>(responsePkg));

    // 是否有更多的数据
    bool moreFlows = *(responsePkg->moreFollows);

    // 释放内存(外部释放内存)
    // ASN_STRUCT_FREE(asn_DEF_GetAllCBValuesResponsePDU, responsePkg);
    return moreFlows;
}

bool mmsCLient_createGetDataValuesRequest(GspMmsConnection self,
                                          GspByteBuffer* outMessage,
                                          uint16_t invokeId,
                                          GspLinkedList refsFcList)
{
    // 异常判断
    if(outMessage == nullptr){
        printf("获取数据值请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetDataValues);

    // 封装请求数据包
    GetDataValuesRequestPDU_t *requestPkt = (GetDataValuesRequestPDU_t*)GspMemory_calloc(1, sizeof(GetDataValuesRequestPDU_t));
    memset(requestPkt, 0, sizeof(GetDataValuesRequestPDU_t));

    // 请求信息
    for(int index=0; index < GspLinkedList_size(refsFcList); ++index){

        // 申请内存
        GetDataValuesRequestPDU__data__Member *dataItem = (GetDataValuesRequestPDU__data__Member*)GspMemory_calloc(1, sizeof(GetDataValuesRequestPDU__data__Member));

        // 清空数据
        memset(dataItem, 0, sizeof (GetDataValuesRequestPDU__data__Member));

        // 获取参数
        RefsFC refsItem = static_cast<RefsFC>(GspLinkedList_get(refsFcList, index));;

        // 填入请求 fc
        if(refsItem->fc){
            dataItem->fc = OCTET_STRING_new_fromBuf(&asn_DEF_FunctionalConstraint, refsItem->fc, static_cast<int>(strlen(refsItem->fc)));
        } else {
            printf("warning: mmsCLient_createGetDataValuesRequest fc 此处不应该出现这种数据, 用户使用者出错, 请开发者自己检查一下 , 这里我做一下兼容默认值给空串\n");
        }

        // 填入请求 refs
        if(refsItem->objRefs){
            OCTET_STRING_fromBuf(&(dataItem->reference), refsItem->objRefs, static_cast<int>(strlen(refsItem->objRefs)));
        } else {
            printf("warning: mmsCLient_createGetDataValuesRequest refs 此处不应该出现这种数据, 用户使用者出错, 请开发者自己检查一下 , 这里我做一下兼容默认值给空串\n");
        }

        // 入队列
        ASN_SEQUENCE_ADD(&requestPkt->data.list, dataItem);
    }
    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetDataValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取数据请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetDataValuesRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取数据请求\n");
        xer_fprint(stdout, &asn_DEF_GetDataValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetDataValuesRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseGetDataValuesResponse (GspByteBuffer* message, GspLinkedList *outList){
    // 异常判断
    if(message == nullptr){
        printf("获取数据值回应帧数据处理失败\n");
        return false;
    }

    // 解析获取所有数据值应答
    GetDataValuesResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetDataValuesResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));

    if(rval.code != RC_OK) {
        printf("mmsClient_parserGetDataValuesResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetDataValuesResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取数据值应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetDataValuesResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outList == nullptr){
        *outList = GspLinkedList_create();
    }
    int arrarySize = responsePkg->value.list.count;
    for (int index=0; index < arrarySize; ++index) {
        // 获取解析后的数据单元
        Data* tmpItem = responsePkg->value.list.array[index];

        // 拷贝一份数据
        Data* newItem = GspMmsValue_clone(tmpItem);

        // 添加到输出列表中
        GspLinkedList_add(*outList, static_cast<void*>(newItem));
    }

    // 是否有更多的数据
    bool moreFlows = *(responsePkg->moreFollows);

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetDataValuesResponsePDU, responsePkg);
    return moreFlows;
}

bool mmsCLient_createGetDataDefinitionRequest(GspMmsConnection self,
                                              GspByteBuffer* outMessage,
                                              uint16_t invokeId,
                                              GspLinkedList refsFcList){
    // 异常判断
    if(outMessage == nullptr){
        printf("获取数据定义请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetDataDefinition);

    // 封装请求数据包
    GetDataDefinitionRequestPDU_t *requestPkt = (GetDataDefinitionRequestPDU_t*)GspMemory_calloc(1, sizeof(GetDataDefinitionRequestPDU_t));
    memset(requestPkt, 0, sizeof(GetDataDefinitionRequestPDU_t));

    // 请求信息
    for(int index=0; index < GspLinkedList_size(refsFcList); ++index){

        // 申请内存
        GetDataDefinitionRequestPDU__data__Member *dataItem = (GetDataDefinitionRequestPDU__data__Member*)GspMemory_calloc(1, sizeof(GetDataDefinitionRequestPDU__data__Member));

        // 清空数据
        memset(dataItem, 0, sizeof(GetDataDefinitionRequestPDU__data__Member));

        // 获取参数
        RefsFC refsItem = static_cast<RefsFC>(GspLinkedList_get(refsFcList, index));;

        // 填入请求 fc
        if(refsItem->fc){
            dataItem->fc = OCTET_STRING_new_fromBuf(&asn_DEF_FunctionalConstraint, refsItem->fc, static_cast<int>(strlen(refsItem->fc)));
        } else {
            printf("warning: mmsCLient_createGetDataDefinitionRequest fc 此处不应该出现这种数据, 用户使用者出错, 请开发者自己检查一下 , 这里我做一下兼容默认值给空串\n");
        }

        // 填入请求 refs
        if(refsItem->objRefs){
            OCTET_STRING_fromBuf(&(dataItem->reference), refsItem->objRefs, static_cast<int>(strlen(refsItem->objRefs)));
        } else {
            printf("warning: mmsCLient_createGetDataDefinitionRequest refs 此处不应该出现这种数据, 用户使用者出错, 请开发者自己检查一下 , 这里我做一下兼容默认值给空串\n");
        }

        // 入队列
        ASN_SEQUENCE_ADD(&requestPkt->data.list, dataItem);
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetDataDefinitionRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取数据定义请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetDataDefinitionRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取数据定义请求\n");
        xer_fprint(stdout, &asn_DEF_GetDataDefinitionRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetDataDefinitionRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseGetDataDefinitionResponse(GspByteBuffer* message,
                                              GspLinkedList *outList){
    // 异常判断
    if(message == nullptr){
        Global_LogString("获取数据定义回应帧数据处理失败\n");
        return false;
    }

    // 解析获取所有数据值应答
    GetDataDefinitionResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetDataDefinitionResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));

    if(rval.code != RC_OK) {
        Global_LogString("mmsClient_parseGetDataDefinitionResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetDataDefinitionResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取数据值应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetDataDefinitionResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outList == nullptr){
        *outList = GspLinkedList_create();
    }

    // 是否有更多的数据
    bool moreFlows = *(responsePkg->moreFollows);

    // 释放内存(使用者释放内存)
    // ASN_STRUCT_FREE(asn_DEF_GetDataDefinitionResponsePDU, responsePkg);
    return moreFlows;
}
