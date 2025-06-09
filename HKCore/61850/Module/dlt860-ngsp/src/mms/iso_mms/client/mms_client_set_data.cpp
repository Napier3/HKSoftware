#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"
#include "gsp_lib_memory.h"
#include "gsp_mms_value.h"


bool mmsCLient_createSetDataValuesRequest(GspMmsConnection self,
                                          GspByteBuffer* outMessage,
                                          uint16_t invokeId,
                                          GspLinkedList dataFcList)
{
    // 异常判断
    if(outMessage == nullptr){
        printf("写数据值请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_SetDataValues);

    // 封装请求数据包
    SetDataValuesRequestPDU_t *requestPkt = (SetDataValuesRequestPDU_t*)GspMemory_calloc(1, sizeof(SetDataValuesRequestPDU_t));
    memset(requestPkt, 0, sizeof(SetDataValuesRequestPDU_t));

    // 请求信息
    for(int index=0; index < GspLinkedList_size(dataFcList); ++index){

        // 申请内存
        SetDataValuesRequestPDU__data__Member *dataItem = (SetDataValuesRequestPDU__data__Member*)GspMemory_calloc(1, sizeof(SetDataValuesRequestPDU__data__Member));

        // 清空数据
        memset(dataItem, 0, sizeof(SetDataValuesRequestPDU__data__Member));

        // 获取参数
        RefsFcData dataRefsItem = static_cast<RefsFcData>(GspLinkedList_get(dataFcList, index));;

        // 填入请求 fc
        if(dataRefsItem->fc){
            dataItem->fc = OCTET_STRING_new_fromBuf(&asn_DEF_FunctionalConstraint, dataRefsItem->fc, static_cast<int>(strlen(dataRefsItem->fc)));
        } else {
            printf("warning: mmsCLient_createSetDataValuesRequest fc 此处不应该出现这种数据, 用户使用者出错, 请开发者自己检查一下 , 这里我做一下兼容默认值给空串\n");
        }

        // 填入请求 refs
        if(dataRefsItem->objRefs){
            OCTET_STRING_fromBuf(&(dataItem->reference), dataRefsItem->objRefs, static_cast<int>(strlen(dataRefsItem->objRefs)));
        } else {
            printf("warning: mmsCLient_createGetDataValuesRequest refs 此处不应该出现这种数据, 用户使用者出错, 请开发者自己检查一下 , 这里我做一下兼容默认值给空串\n");
        }

        // 填入数据值
        if(dataRefsItem->data){
            GspMmsValue_update(&dataItem->value, dataRefsItem->data);
        }

        // 入队列
        ASN_SEQUENCE_ADD(&requestPkt->data.list, dataItem);
    }
    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SetDataValuesRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建写数据请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_SetDataValuesRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 写数据请求\n");
        xer_fprint(stdout, &asn_DEF_SetDataValuesRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_SetDataValuesRequestPDU, requestPkt);

    return true;
}

bool mmsClient_parseSetDataValuesResponse (GspByteBuffer* message, GspLinkedList *outList){
    // 异常判断
    if(message == nullptr){
        printf("写数据值回应帧数据处理失败\n");
        return false;
    }

    // 解析获取所有数据值应答
    SetDataValuesResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_SetDataValuesResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));

    if(rval.code != RC_OK) {
        printf("mmsClient_parseSetDataValuesResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_SetDataValuesResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 写数据值应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_SetDataValuesResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outList == nullptr){
        *outList = GspLinkedList_create();
    }

    // 添加到列表
    GspLinkedList_add(*outList, responsePkg);

    // 释放内存 (使用者释放)
    //    ASN_STRUCT_FREE(asn_DEF_SetDataValuesResponsePDU, responsePkg);
    return true;
}
