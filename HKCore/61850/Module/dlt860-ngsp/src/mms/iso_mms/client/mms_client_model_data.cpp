#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"
#include "GetServerDirectoryErrorPDU.h"
#include "GetServerDirectoryRequestPDU.h"
#include "GetServerDirectoryResponsePDU.h"
#include "GetLogicalDeviceDirectoryErrorPDU.h"
#include "GetLogicalDeviceDirectoryRequestPDU.h"
#include "GetLogicalDeviceDirectoryResponsePDU.h"
#include "GetLogicalNodeDirectoryErrorPDU.h"
#include "GetLogicalNodeDirectoryRequestPDU.h"
#include "GetLogicalNodeDirectoryResponsePDU.h"
#include "GetAllDataDefinitionErrorPDU.h"
#include "GetAllDataDefinitionRequestPDU.h"
#include "GetAllDataDefinitionResponsePDU.h"
#include "GetAllDataValuesErrorPDU.h"
#include "GetAllDataValuesRequestPDU.h"
#include "GetAllDataValuesResponsePDU.h"
#include "gsp_lib_memory.h"
#include "ACSIClass.h"


bool mmsClient_createGetServerDirectoryRequest(GspMmsConnection self,
                                               GspByteBuffer* outMessage,
                                               uint16_t invokeId,
                                               const char* referenceAfter){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装取消帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetServerDirectory);

    // 封装请求数据包
    GetServerDirectoryRequestPDU_t* requestPkt = static_cast<GetServerDirectoryRequestPDU_t*>(GspMemory_calloc(1, sizeof (GetServerDirectoryRequestPDU_t)));
    memset(requestPkt, 0, sizeof(GetServerDirectoryRequestPDU_t));
    requestPkt->objectClass = GetServerDirectoryRequestPDU__objectClass_logical_device;

    // 可选参数
    if(referenceAfter){
        requestPkt->referenceAfter = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, referenceAfter, strlen(referenceAfter));
    }

    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetServerDirectoryRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize - 2));
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取服务目录请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_GetServerDirectoryRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取服务目录请求\n");
        xer_fprint(stdout, &asn_DEF_GetServerDirectoryRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetServerDirectoryRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseGetServerDiecttoryResponse(GspByteBuffer* message, GspLinkedList* outServerDirectory){
    // 异常判断
    if(message == nullptr){
        printf("获取服务目录回应帧数据处理失败\n");
        return false;
    }

    // 解析获取服务目录应答
    GetServerDirectoryResponsePDU_t *getServerDirectoryResponse = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetServerDirectoryResponsePDU,
                                               reinterpret_cast<void **>(&getServerDirectoryResponse),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("associate decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetServerDirectoryResponsePDU, getServerDirectoryResponse);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取服务目录应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetServerDirectoryResponsePDU, getServerDirectoryResponse);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outServerDirectory == nullptr){
        *outServerDirectory = GspLinkedList_create();
    }
    int arrarySize = getServerDirectoryResponse->reference.list.count;
    for (int index=0; index < arrarySize; ++index) {
        ObjectReference_t tmpItem = *(getServerDirectoryResponse->reference.list.array[index]);
        uint8_t* itemStr = static_cast<uint8_t*>(GLOBAL_MALLOC(tmpItem.size+1));
        memset(itemStr, 0, tmpItem.size+1);
        memcpy(itemStr, tmpItem.buf, tmpItem.size);
        GspLinkedList_add(*outServerDirectory, itemStr);
    }

    // 是否有更多的数据
    bool moreFlows = *(getServerDirectoryResponse->moreFollows);

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetServerDirectoryResponsePDU, getServerDirectoryResponse);
    return moreFlows;
}


bool mmsClient_createGetLogicalDeviceDirectoryRequest(GspMmsConnection self,
                                                      GspByteBuffer* outMessage,
                                                      uint16_t invokeId,
                                                      const char* paramLDName,
                                                      const char* referenceAfter){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装取消帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetLogicDeviceDirectory);

    // 封装请求数据包
    GetLogicalDeviceDirectoryRequestPDU_t* requestPkt = static_cast<GetLogicalDeviceDirectoryRequestPDU_t*>(GspMemory_calloc(1, sizeof(GetLogicalDeviceDirectoryRequestPDU_t)));
    memset(requestPkt, 0, sizeof(GetLogicalDeviceDirectoryRequestPDU_t));

    // 可选参数 逻辑设备
    if(paramLDName){
        requestPkt->ldName = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectName, paramLDName, static_cast<int>(strlen(paramLDName)));
    }

    // 可选参数
    if(referenceAfter){
        requestPkt->referenceAfter = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, referenceAfter, static_cast<int>(strlen(referenceAfter)));
    }

    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetLogicalDeviceDirectoryRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize - 2));
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取逻辑设备请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetLogicalDeviceDirectoryRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取逻辑设备请求\n");
        xer_fprint(stdout, &asn_DEF_GetLogicalDeviceDirectoryRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetLogicalDeviceDirectoryRequestPDU, requestPkt);
    return true;
}

bool mmsClient_parseGetLogicalDeviceDirectoryResponse(GspByteBuffer* message, GspLinkedList *outList){
    // 异常判断
    if(message == nullptr){
        printf("获取逻辑设备回应帧数据处理失败\n");
        return false;
    }

    // 解析逻辑设备应答
    GetLogicalDeviceDirectoryResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetLogicalDeviceDirectoryResponsePDU,
                                               reinterpret_cast<void **>(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetLogicalDeviceDirectoryResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetLogicalDeviceDirectoryResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取逻辑设备应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetLogicalDeviceDirectoryResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outList == nullptr){
        *outList = GspLinkedList_create();
    }
    int arrarySize = responsePkg->lnReference.list.count;
    for (int index=0; index < arrarySize; ++index) {
        SubReference_t tmpItem = *(responsePkg->lnReference.list.array[index]);
        uint8_t* itemStr = static_cast<uint8_t*>(GLOBAL_MALLOC(tmpItem.size+1));
        memset(itemStr, 0, tmpItem.size+1);
        memcpy(itemStr, tmpItem.buf, tmpItem.size);
        GspLinkedList_add(*outList, itemStr);
    }

    // 是否有更多的数据
    bool moreFlows = *(responsePkg->moreFollows);

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetServerDirectoryResponsePDU, responsePkg);
    return moreFlows;
}


bool mmsClient_createGetLogicalNodeRequest(GspMmsConnection self,
                                           GspByteBuffer* outMessage,
                                           uint16_t invokeId,
                                           const char* reference,
                                           const char* referenceAfter,
                                           GspACSICLASS paramType) {
    // 异常判断
    if(outMessage == nullptr){
        printf("封装获取逻辑节点目录帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetLogicNodeDirectory);

    // 封装请求数据包
    GetLogicalNodeDirectoryRequestPDU_t *requestPkt = static_cast<GetLogicalNodeDirectoryRequestPDU_t*>(GspMemory_calloc(1, sizeof(GetLogicalNodeDirectoryRequestPDU_t)));
    memset(requestPkt, 0, sizeof(GetLogicalNodeDirectoryRequestPDU_t));

    // acsiClass
    requestPkt->acsiClass = paramType;

    // reference
    requestPkt->reference.present = GetLogicalNodeDirectoryRequestPDU__reference_PR_lnReference;
    if(reference){
        OCTET_STRING_fromBuf(&requestPkt->reference.choice.lnReference, reference, static_cast<int>(strlen(reference)));
    } else {
        printf("创建获取逻辑节点请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_GetLogicalNodeDirectoryRequestPDU, requestPkt);
        return false;
    }

    // 可选参数 逻辑设备
    if(referenceAfter){
        requestPkt->referenceAfter = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, referenceAfter, static_cast<int>(strlen(referenceAfter)));
    }

    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetLogicalNodeDirectoryRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize - 2));
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取逻辑节点请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_GetLogicalNodeDirectoryRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取逻辑节点请求\n");
        xer_fprint(stdout, &asn_DEF_GetLogicalNodeDirectoryRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetLogicalNodeDirectoryRequestPDU, requestPkt);

    return true;
}


bool mmsClient_parseLogicalNodeResponse (GspByteBuffer* message, GspLinkedList *outList){
    // 异常判断
    if(message == nullptr){
        printf("获取逻辑节点回应帧数据处理失败\n");
        return false;
    }

    // 解析逻辑设备应答
    GetLogicalNodeDirectoryResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetLogicalNodeDirectoryResponsePDU,
                                               reinterpret_cast<void **>(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetLogicalNodeDirectoryResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetLogicalNodeDirectoryResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取逻辑节点应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetLogicalNodeDirectoryResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outList == nullptr){
        *outList = GspLinkedList_create();
    }
    int arrarySize = responsePkg->reference.list.count;
    for (int index=0; index < arrarySize; ++index) {
        SubReference_t tmpItem = *(responsePkg->reference.list.array[index]);
        uint8_t* itemStr = static_cast<uint8_t*>(GLOBAL_MALLOC(tmpItem.size+1));
        memset(itemStr, 0, tmpItem.size+1);
        memcpy(itemStr, tmpItem.buf, tmpItem.size);
        GspLinkedList_add(*outList, itemStr);
    }

    // 是否有更多的数据
    bool moreFlows = *(responsePkg->moreFollows);

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetLogicalNodeDirectoryResponsePDU, responsePkg);
    return moreFlows;
}

bool mmsClient_createGetAllDataDefinitionRequest(GspMmsConnection self,
                                                 GspByteBuffer* outMessage,
                                                 uint16_t invokeId,
                                                 const char* reference,
                                                 const char* referenceAfter,
                                                 GspFunctionalConstraint paramFC,
                                                 GspRefType paramRefType){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装获取所有数据定义帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetAllDataDefinition);

    // 封装请求数据包
    GetAllDataDefinitionRequestPDU_t *requestPkt = static_cast<GetAllDataDefinitionRequestPDU_t *>(GspMemory_calloc(1, sizeof(GetAllDataDefinitionRequestPDU_t)));
    memset(requestPkt, 0, sizeof(GetAllDataDefinitionRequestPDU_t));

    // fc
    if(paramFC != DLT860_FC_NONE && paramFC != DLT860_FC_ALL){
        char* fcStr = GspFunctionalConstraint_toString(paramFC);
        requestPkt->fc = OCTET_STRING_new_fromBuf(&asn_DEF_FunctionalConstraint, fcStr, static_cast<int>(strlen(fcStr)));
        delete [] fcStr;
    }

    // reference
    requestPkt->reference.present = static_cast<GetAllDataDefinitionRequestPDU__reference_PR>(paramRefType);
    if(reference){
        if(static_cast<GetAllDataDefinitionRequestPDU__reference_PR>(paramRefType) == GetAllDataDefinitionRequestPDU__reference_PR_ldName) {
            OCTET_STRING_fromBuf(&requestPkt->reference.choice.ldName, reference, static_cast<int>(strlen(reference)));
        } else {
            OCTET_STRING_fromBuf(&requestPkt->reference.choice.lnReference, reference, static_cast<int>(strlen(reference)));
        }
    } else {
        printf("创建获取所有数据定义请求帧编码错误\n");
        return false;
    }

    // 可选参数 逻辑设备
    if(referenceAfter){
        requestPkt->referenceAfter = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, referenceAfter, static_cast<int>(strlen(referenceAfter)));
    }

    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetAllDataDefinitionRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize - 2));
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取所有数据定义请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetAllDataDefinitionRequestPDU, requestPkt);

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
        xer_fprint(stdout, &asn_DEF_GetAllDataDefinitionRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetAllDataDefinitionRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseGetAllDataDefinitionResponse (GspByteBuffer* message, GspLinkedList *outList){
    // 异常判断
    if(message == nullptr){
        printf("获取所有数据定义回应帧数据处理失败\n");
        return false;
    }

    // 解析逻辑设备应答
    GetAllDataDefinitionResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetAllDataDefinitionResponsePDU,
                                               reinterpret_cast<void **>(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetAllDataDefinitionResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetAllDataDefinitionResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取所有数据定义应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetAllDataDefinitionResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outList == nullptr){
        *outList = GspLinkedList_create();
    }
    GspLinkedList_add(*outList, responsePkg);

    // 是否有更多的数据
    bool moreFlows = *(responsePkg->moreFollows);

    // 释放内存(外部释放)
    //    ASN_STRUCT_FREE(asn_DEF_GetAllDataDefinitionResponsePDU, responsePkg);
    return moreFlows;
}
