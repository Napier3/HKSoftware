#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"


bool mmsClient_createSelectActiveSGRequest(GspMmsConnection self,
                                           GspByteBuffer* outMessage,
                                           uint16_t invokeId,
                                           const char* sgcbReference,
                                           uint8_t settingGroupNumber){
    // 异常判断
    if(outMessage == nullptr){
        printf("选择激活定值组请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_SelectActiveSG);

    // 封装请求数据包
    SelectActiveSGRequestPDU_t *requestPkt = (SelectActiveSGRequestPDU_t*)GspMemory_calloc(1, sizeof(SelectActiveSGRequestPDU_t));
    memset(requestPkt, 0, sizeof(requestPkt));

    // 参数设置 settingGroupNumber
    requestPkt->settingGroupNumber = settingGroupNumber;

    // 参数设置 settingGroupNumber
    if(sgcbReference){
        OCTET_STRING_fromBuf(&requestPkt->sgcbReference, sgcbReference, static_cast<int>(strlen(sgcbReference)));
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SelectActiveSGRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建选择激活定值组请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_SelectActiveSGRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 选择激活定值组数据请求\n");
        xer_fprint(stdout, &asn_DEF_SelectActiveSGRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_SelectActiveSGRequestPDU, requestPkt);

    return true;
}


bool mmsClient_parseSelectActiveSGResponse(GspByteBuffer* message,
                                            GspLinkedList* outData){
    // 异常判断
    if(message == nullptr){
        printf("解析选择激活定值组获取到了空数据包\n");
        return false;
    }

    // 解析选择激活定值组应答
    SelectActiveSGResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_SelectActiveSGResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("SelectActiveSGResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_SelectActiveSGResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析选择激活定值组应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_SelectActiveSGResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_SelectActiveSGResponsePDU, responsePkg);
    return true;
}


bool mmsClient_createSelectEditSGRequest(GspMmsConnection self,
                                         GspByteBuffer* outMessage,
                                         uint16_t invokeId,
                                         const char* sgcbReference,
                                         uint8_t settingGroupNumber){
    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_SelectEditSG);

    // 封装请求数据包
    SelectEditSGRequestPDU_t *requestPkt = (SelectEditSGRequestPDU_t *)GspMemory_calloc(1, sizeof(SelectEditSGRequestPDU_t));
    memset(requestPkt, 0, sizeof(SelectEditSGRequestPDU_t));

    // 参数设置 settingGroupNumber
    requestPkt->settingGroupNumber = settingGroupNumber;

    // 参数设置 sgcbReference
    if(sgcbReference){
        OCTET_STRING_fromBuf(&requestPkt->sgcbReference, sgcbReference, static_cast<int>(strlen(sgcbReference)));
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SelectEditSGRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建选择编辑定值组请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_SelectEditSGRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 选择编辑定值组数据请求\n");
        xer_fprint(stdout, &asn_DEF_SelectEditSGRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_SelectEditSGRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseSelectEditSGResponse(GspByteBuffer* message,
                                          GspLinkedList* outData){
    // 异常判断
    if(message == nullptr){
        printf("解析选择编辑定值组获取到了空数据包\n");
        return false;
    }

    // 解析选择编辑定值组应答
    SelectActiveSGResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_SelectEditSGResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("SelectEditSGResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_SelectEditSGResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析选择编辑定值组应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_SelectEditSGResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_SelectEditSGResponsePDU, responsePkg);
    return true;
}

bool mmsClient_createConfirmEditSGValuesRequest(GspMmsConnection self,
                                                GspByteBuffer* outMessage,
                                                uint16_t invokeId,
                                                const char* sgcbReference){
    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_ConfirmEditSGValues);

    // 封装请求数据包
    ConfirmEditSGValuesRequestPDU_t *requestPkt = (ConfirmEditSGValuesRequestPDU_t *)GspMemory_calloc(1, sizeof(ConfirmEditSGValuesRequestPDU_t));
    memset(requestPkt, 0, sizeof(ConfirmEditSGValuesRequestPDU_t));

    // 参数设置 sgcbReference
    if(sgcbReference){
        OCTET_STRING_fromBuf(&requestPkt->sgcbReference, sgcbReference, static_cast<int>(strlen(sgcbReference)));
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_ConfirmEditSGValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建确认编辑定值组值请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_ConfirmEditSGValuesRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 确认编辑定值组数据请求\n");
        xer_fprint(stdout, &asn_DEF_ConfirmEditSGValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_ConfirmEditSGValuesRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseConfirmEditSGValuesResponse(GspByteBuffer* message,
                                                 GspLinkedList* outData){
    // 异常判断
    if(message == nullptr){
        printf("解析确认编辑定值组获取到了空数据包\n");
        return false;
    }

    // 解析确认编辑定值组应答
    ConfirmEditSGValuesResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_ConfirmEditSGValuesResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("ConfirmEditSGValuesResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_ConfirmEditSGValuesResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析选择编辑定值组应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_ConfirmEditSGValuesResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_ConfirmEditSGValuesResponsePDU, responsePkg);
    return true;
}

bool mmsClient_createGetEditSGValueRequest(GspMmsConnection self,
                                           GspByteBuffer* outMessage,
                                           uint16_t invokeId,
                                           GspLinkedList sgRefs){
    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetEditSGValue);

    // 封装请求数据包
    GetEditSGValueRequestPDU_t *requestPkt = (GetEditSGValueRequestPDU_t *)GspMemory_calloc(1, sizeof (GetEditSGValueRequestPDU_t));
    memset(requestPkt, 0, sizeof(GetEditSGValueRequestPDU_t));

    // 参数设置 sgRefs
    if(sgRefs != nullptr){
        for(int index=0; index < GspLinkedList_size(sgRefs); ++index)
        {
            GetEditSGValueRequestPDU__data__Member *dataItem = (GetEditSGValueRequestPDU__data__Member *)GspMemory_calloc(1, sizeof(GetEditSGValueRequestPDU__data__Member));

            // 清空
            memset(dataItem, 0 , sizeof(GetEditSGValueRequestPDU__data__Member));

            // 请求参数
            RefsFC tmpItem = static_cast<RefsFC>(GspLinkedList_get(sgRefs, index));
            if(!tmpItem){
                printf("warning: 此处不应该出现这种数据, 用户使用者出错, 请开发者自己检查一下 \n");
                continue;
            }

            // fc
            if(!tmpItem->fc){
                printf("warning: mmsClient_createGetEditSGValueRequest fc 此处不应该出现这种数据, 用户使用者出错, 请开发者自己检查一下 , 这里我做一下兼容默认值给空串\n");
            } else {
                OCTET_STRING_fromBuf(&dataItem->fc, tmpItem->fc, static_cast<int>(strlen(tmpItem->fc)));
            }

            // refs
            if(!tmpItem->objRefs){
                printf("warning: mmsClient_createGetEditSGValueRequest refs 此处不应该出现这种数据, 用户使用者出错, 请开发者自己检查一下 , 这里我做一下兼容默认值给空串\n");
            } else {
                OCTET_STRING_fromBuf(&dataItem->reference, tmpItem->objRefs, static_cast<int>(strlen(tmpItem->objRefs)));
            }

            // 添加到队列里面
            ASN_SEQUENCE_ADD(&requestPkt->data.list, dataItem);
        }
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetEditSGValueRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取编辑定值组值请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_GetEditSGValueRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取定值组数据请求\n");
        xer_fprint(stdout, &asn_DEF_GetEditSGValueRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetEditSGValueRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseGetEditSGValueResponse(GspByteBuffer* message,
                                            GspLinkedList* outData){
    // 异常判断
    if(message == nullptr){
        printf("解析获取编辑定值组获取到了空数据包\n");
        return false;
    }

    // 解析获取编辑定值组应答
    GetEditSGValueResponsePDU_t* responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetEditSGValueResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetEditSGValueRequestPDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetEditSGValueResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析获取编辑定值组应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetEditSGValueResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetEditSGValueResponsePDU, responsePkg);
    return *responsePkg->moreFollows;
}

bool mmsClient_createGetSGCBValuesRequest(GspMmsConnection self,
                                          GspByteBuffer* outMessage,
                                          uint16_t invokeId,
                                          const char* sgcbReference){
    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetSGCBValues);

    // 封装请求数据包
    GetSGCBValuesRequestPDU_t* requestPkt = (GetSGCBValuesRequestPDU_t*)GspMemory_calloc(1, sizeof(GetSGCBValuesRequestPDU_t));
    memset(requestPkt, 0, sizeof(requestPkt));

    // 参数设置
    if(sgcbReference != nullptr){
        ObjectReference_t * referenceItem = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, sgcbReference, strlen(sgcbReference));
        ASN_SEQUENCE_ADD(&requestPkt->sgcbReference.list, referenceItem);
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetSGCBValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建读定值控制块值请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetSGCBValuesRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 读定值控制块值数据请求\n");
        xer_fprint(stdout, &asn_DEF_GetSGCBValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetSGCBValuesRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseGetSGCBValuesResponse(GspByteBuffer* message,
                                           GspLinkedList* outData){
    // 异常判断
    if(message == nullptr){
        printf("解析获取定值组控制块值获取到了空数据包\n");
        return false;
    }

    // 解析获取定值组控制块值应答
    GetSGCBValuesResponsePDU_t* responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetSGCBValuesResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetSGCBValuesResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetSGCBValuesResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析获取定值组控制块值应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetSGCBValuesResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetEditSGValueResponsePDU, responsePkg);
    return *responsePkg->moreFollows;
}

bool mmsClient_createSetEditSGValueRequest(GspMmsConnection self,
                                           GspByteBuffer* outMessage,
                                           uint16_t invokeId,
                                           GspLinkedList sgRefsData){
    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_SetEditSGValue);

    // 封装请求数据包
    SetEditSGValueRequestPDU_t *requestPkt = (SetEditSGValueRequestPDU_t *)GspMemory_calloc(1, sizeof(SetEditSGValueRequestPDU_t));
    memset(requestPkt, 0, sizeof(SetEditSGValueRequestPDU_t));

    // 参数设置
    if(sgRefsData != nullptr){
#ifdef NOT_USE_IN_C11
		deque<void *> d = *sgRefsData;

		for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
		{
			// 取出参数
			RefsData dataItem = (RefsData)(*it);
#else
        for(auto &item : *sgRefsData)
        {
            // 取出参数
            RefsData dataItem = (RefsData)item;
#endif

            // 设置参数
            SetEditSGValueRequestPDU__data__Member* tmpDataItem = (SetEditSGValueRequestPDU__data__Member*)GspMemory_calloc(1, sizeof(SetEditSGValueRequestPDU__data__Member));

            // refs
            memset(tmpDataItem, 0, sizeof(SetEditSGValueRequestPDU__data__Member));
            OCTET_STRING_fromBuf(&tmpDataItem->reference, dataItem->objRefs, -1);

            // data
            GspMmsValue_cloneFromOther(&tmpDataItem->value, dataItem->data);

            // 添加到列表
            ASN_SEQUENCE_ADD(&requestPkt->data, tmpDataItem);
        }
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SetEditSGValueRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        Global_LogString("创建写定值控制块值请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_SetEditSGValueRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 写定值数据请求\n");
        xer_fprint(stdout, &asn_DEF_SetEditSGValueRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_SetEditSGValueRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseSetEditSGValueResponse(GspByteBuffer* message,
                                            GspLinkedList* outData){
    // 异常判断
    if(message == nullptr){
        Global_LogString("解析写定值组控制块值获取到了空数据包\n");
        return false;
    }

    // 解析写定值组控制块值应答
    SetEditSGValueResponsePDU_t* responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_SetEditSGValueResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        Global_LogString("SetEditSGValueResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_SetEditSGValueResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 解析写定值组控制块值应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_SetEditSGValueResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outData == nullptr){
        *outData = GspLinkedList_create();
    }

    // 添加到输出列表中
    GspLinkedList_add(*outData, static_cast<void*>(responsePkg));

    // 释放内存(使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetEditSGValueResponsePDU, responsePkg);
    return true;
}
