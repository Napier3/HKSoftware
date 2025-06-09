#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"
#include "GetDataSetDirectoryErrorPDU.h"
#include "GetDataSetDirectoryRequestPDU.h"
#include "GetDataSetDirectoryResponsePDU.h"


bool mmsClient_createGetDataSetDirectoryRequest(GspMmsConnection self,
                                                GspByteBuffer* outMessage,
                                                uint16_t invokeId,
                                                const char* paramDataSetRefs){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装获取数据集目录数据失败\n");
        return false;
    }
    if(paramDataSetRefs == nullptr){
        printf("封装获取数据集目录时请求参数为空\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetDataSetDirectory);

    // 请求数据参数
    GetDataSetDirectoryRequestPDU_t *datasetDirectoryRequest = static_cast<GetDataSetDirectoryRequestPDU_t*>(GspMemory_calloc(1, sizeof(GetDataSetDirectoryRequestPDU_t)));
    memset(datasetDirectoryRequest, 0, sizeof(GetDataSetDirectoryRequestPDU_t));
    OCTET_STRING_fromBuf(&datasetDirectoryRequest->datasetReference, paramDataSetRefs, static_cast<int>(strlen(paramDataSetRefs)));

    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetDataSetDirectoryRequestPDU,
                                                nullptr,
                                                datasetDirectoryRequest,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize - 2));
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("GetDataSetDirectoryRequestPDU_t encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetDataSetDirectoryRequestPDU, datasetDirectoryRequest);

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
        printf("APER: 获取数据集目录请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetDataSetDirectoryRequestPDU, datasetDirectoryRequest);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetDataSetDirectoryRequestPDU, datasetDirectoryRequest);

    return true;
}

bool mmsClient_parseGetDataSetDirectoryResponse(GspByteBuffer* message, GspLinkedList* outDataSetDirectory){
    // 异常判断
    if(message == nullptr){
        printf("获取数据集目录回应帧数据处理失败\n");
        return false;
    }

    // 解析请求消息
    GetDataSetDirectoryResponsePDU_t *getDataSetDirectoryResponse = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetDataSetDirectoryResponsePDU,
                                               (void **)(&getDataSetDirectoryResponse),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetDataSetDirectoryResponsePDU_t decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetDataSetDirectoryResponsePDU, getDataSetDirectoryResponse);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取数据集目录应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetDataSetDirectoryResponsePDU, getDataSetDirectoryResponse);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outDataSetDirectory == nullptr){
        *outDataSetDirectory = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outDataSetDirectory, getDataSetDirectoryResponse);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetDataSetDirectoryResponsePDU, getDataSetDirectoryResponse);
    return *(getDataSetDirectoryResponse->moreFollows);
}

bool mmsClient_createGetDataSetValuesRequest(GspMmsConnection self,
                                             GspByteBuffer* outMessage,
                                             uint16_t invokeId,
                                             const char* paramDataSetRefs){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装获取数据集值数据失败\n");
        return false;
    }
    if(paramDataSetRefs == nullptr){
        printf("封装获取数据集值时请求参数为空\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetDataSetValues);

    // 请求数据参数
    GetDataSetValuesRequestPDU_t *datasetValuesRequest = static_cast<GetDataSetValuesRequestPDU_t*>(GspMemory_calloc(1, sizeof(GetDataSetValuesRequestPDU_t)));
    memset(datasetValuesRequest, 0, sizeof(GetDataSetValuesRequestPDU_t));
    OCTET_STRING_fromBuf(&datasetValuesRequest->datasetReference, paramDataSetRefs, static_cast<int>(strlen(paramDataSetRefs)));

    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetDataSetValuesRequestPDU,
                                                nullptr,
                                                datasetValuesRequest,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize - 2));
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("GetDataSetValuesRequestPDU_t encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetDataSetValuesRequestPDU, datasetValuesRequest);

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
        printf("APER: 获取数据集值请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetDataSetValuesRequestPDU, datasetValuesRequest);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetDataSetValuesRequestPDU, datasetValuesRequest);

    return true;
}

bool mmsClient_parseGetDataSetValuesResponse(GspByteBuffer* message,
                                             GspLinkedList* outDataSetValues){
    // 异常判断
    if(message == nullptr){
        printf("获取数据集值回应帧数据处理失败\n");
        return false;
    }

    // 解析请求消息
    GetDataSetValuesResponsePDU_t *getDataSetValuesResponse = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetDataSetValuesResponsePDU,
                                               (void **)(&getDataSetValuesResponse),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetDataSetValuesResponsePDU_t decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetDataSetValuesResponsePDU, getDataSetValuesResponse);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取数据集目录应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetDataSetValuesResponsePDU, getDataSetValuesResponse);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outDataSetValues == nullptr){
        *outDataSetValues = GspLinkedList_create();
    }

    int arrarySize = getDataSetValuesResponse->value.list.count;
    for (int index=0; index < arrarySize; ++index) {
        // 获取解析后的数据单元
        Data* tmpItem = getDataSetValuesResponse->value.list.array[index];

        // 拷贝一份数据
        Data* newItem = GspMmsValue_clone(tmpItem);

        // 添加到输出列表中
        GspLinkedList_add(*outDataSetValues, static_cast<void*>(newItem));
    }

    // 是否有更多的数据
    bool moreFlows = *(getDataSetValuesResponse->moreFollows);

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetDataSetValuesResponsePDU, getDataSetValuesResponse);
    return moreFlows;
}
