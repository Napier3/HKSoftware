#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"
#include "GetFileDirectoryRequestPDU.h"
#include "GetFileDirectoryResponsePDU.h"
#include "GetFileDirectoryErrorPDU.h"
#include "GetFileErrorPDU.h"
#include "GetFileRequestPDU.h"
#include "GetFileResponsePDU.h"
#include "gsp_lib_memory.h"
#include "ACSIClass.h"
#include "gsp_mms_value.h"

#define UTCTIME_SIZE    8

bool mmsClient_parseGetDirecttoryResponse(GspByteBuffer* message, GspLinkedList* outServerDirectory){
    // 异常判断
    if(message == nullptr){
        printf("获取文件目录回应帧数据处理失败\n");
        return false;
    }

    // 解析获取文件目录数据
    GetFileDirectoryResponsePDU_t *responsePkg = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetFileDirectoryResponsePDU,
                                               (void **)(&responsePkg),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetFileDirectoryResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetFileDirectoryResponsePDU, responsePkg);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取读所有文件目录应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetFileDirectoryResponsePDU, responsePkg);
    }

    // 创建链表信息
    if(*outServerDirectory == nullptr){
        *outServerDirectory = GspLinkedList_create();
    }

    // 添加到列表里面
    GspLinkedList_add(*outServerDirectory, static_cast<void*>(responsePkg));

    // 是否有更多的数据
    bool moreFlows = *(responsePkg->moreFollows);

    // 外部释放资源
    // ASN_STRUCT_FREE(asn_DEF_GetFileDirectoryResponsePDU, responsePkg);

    return moreFlows;
}

bool mmsCLient_createGetDirectoryRequest(GspMmsConnection self,
                                         GspByteBuffer* outMessage,
                                         uint16_t invokeId,
                                         const char* pathName,
                                         const char* startTime,
                                         const char* endTime,
                                         const char* fileAfter)
{
    // 异常判断
    if(outMessage == nullptr){
        printf("获取文件目录请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetFileDirectory);

    // 封装请求数据包
    GetFileDirectoryRequestPDU_t *requestPkt = (GetFileDirectoryRequestPDU_t*)GspMemory_calloc(1, sizeof(GetFileDirectoryRequestPDU_t));
    memset(requestPkt, 0, sizeof(GetFileDirectoryRequestPDU_t));

    // 路径信息
    OCTET_STRING_fromBuf(&requestPkt->pathName, pathName, static_cast<int>(strlen(pathName)));

    // 开始时间
    if(startTime){
        requestPkt->startTime = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString255, startTime, UTCTIME_SIZE);
    }

    // 结束时间
    if(endTime){
        requestPkt->stopTime = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString255, endTime, UTCTIME_SIZE);
    }

    // 文件 after
    if(fileAfter){
        requestPkt->fileAfter = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString255, fileAfter, static_cast<int>(strlen(fileAfter)));
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetFileDirectoryRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取文件目录请求帧编码错误\n");

        // 释放内存
        ASN_STRUCT_FREE(asn_DEF_GetFileDirectoryRequestPDU, requestPkt);

        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取文件目录数据请求\n");
        xer_fprint(stdout, &asn_DEF_GetFileDirectoryRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 释放内存
    ASN_STRUCT_FREE(asn_DEF_GetFileDirectoryRequestPDU, requestPkt);

    return true;
}

bool mmsClient_createGetFileRequest(GspMmsConnection self,
                                    GspByteBuffer* outMessage,
                                    uint16_t invokeId,
                                    const char* fileName,
                                    INT32U_t startPostion){
    // 异常判断
    if(outMessage == nullptr){
        printf("获取文件请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetFile);

    // 封装请求数据包
    GetFileRequestPDU_t *requestPkt = (GetFileRequestPDU_t *)GspMemory_calloc(1, sizeof(GetFileRequestPDU_t));
    memset(requestPkt, 0, sizeof(GetFileRequestPDU_t));

    // 文件路径
    if(fileName){
        OCTET_STRING_fromBuf((OCTET_STRING_t*)&(requestPkt->filename), fileName, static_cast<int>(strlen(fileName)));
    }

    // 开始位置
    requestPkt->startPostion = startPostion;

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetFileRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建获取文件请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetFileRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 获取文件数据请求\n");
        xer_fprint(stdout, &asn_DEF_GetFileRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetFileRequestPDU, requestPkt);

    return true;
}

bool mmsCLient_parseGetFileResponse(GspByteBuffer* message, GspLinkedList* outFileDataPtr){
    // 异常判断
    if(message == nullptr){
        printf("获取文件内容回应帧数据处理失败\n");
        return false;
    }

    // 解析获取文件目录数据
    GetFileResponsePDU_t *responsePKG = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetFileResponsePDU,
                                               (void **)(&responsePKG),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetFileResponsePDU decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetFileResponsePDU, responsePKG);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取读文件内容应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetFileResponsePDU, responsePKG);
    }

    // 创建链表信息
    if(*outFileDataPtr == nullptr){
        *outFileDataPtr = GspLinkedList_create();
    }

    // 添加到列表里面
    GspLinkedList_add(*outFileDataPtr, static_cast<void*>(responsePKG));
    bool moreData =  !responsePKG->endOfFile;

    // 外部释放资源
    // ASN_STRUCT_FREE(asn_DEF_GetFileResponsePDU, responsePKG);

    return moreData;
}

bool mmsClient_createSetFileRequest(GspMmsConnection self,
                                    GspByteBuffer* outMessage,
                                    uint16_t invokeId,
                                    const char* fileName,
                                    uint32_t startPostion,
                                    const char* fileData,
                                    uint32_t fileDataSize,
                                    bool endFlag) {
    // 异常判断
    if(outMessage == nullptr) {
        printf("写文件请求帧数据处理失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_SetFile);

    // 封装请求数据包
    SetFileRequestPDU_t *requestPkt = (SetFileRequestPDU_t *)GspMemory_calloc(1, sizeof(SetFileRequestPDU_t));
    memset(requestPkt, 0, sizeof(SetFileRequestPDU_t));

    // 文件名字
    if(fileName) {
        OCTET_STRING_fromBuf((VisibleString255_t*)&(requestPkt->filename), fileName, static_cast<int>(strlen(fileName)));
    }

    // 开始位置
    requestPkt->startPostion = startPostion;

    // 文件数据
    if(fileData) {
        OCTET_STRING_fromBuf((OCTET_STRING_t*)&(requestPkt->fileData), fileData, static_cast<int>(fileDataSize));
    }

    // 是否结束
    requestPkt->endOfFile = endFlag;

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_SetFileRequestPDU,
                                                nullptr,
                                                requestPkt,
                                                outMessage->buffer + 2,
                                                static_cast<size_t>(outMessage->maxSize) - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("创建写文件目录请求帧编码错误\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_SetFileRequestPDU, requestPkt);
        return false;
    }

    outMessage->size += dVal.encoded / 8;
    if(dVal.encoded % 8 > 0) {
        outMessage->size += 1;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("****************************** 请求信息帧(开始) *******************************\n");
        printf("APER: 写文件数据请求\n");
        xer_fprint(stdout, &asn_DEF_SetFileRequestPDU, requestPkt);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_SetFileRequestPDU, requestPkt);

    return true;
}
