#include "cotp.h"
#include <stdio.h>
#include "mms_client_internal.h"

bool mmsClient_createGetRpcInterfaceDirectoryRequest(GspMmsConnection self,
                                                     GspByteBuffer* outMessage,
                                                     uint16_t invokeId,
                                                     const char* paramReferenceAfter){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装RPC接口目录帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetRpcInterfaceDirectory);

    // 请求数据参数
    GetRpcInterfaceDirectoryRequestPDU_t* requestPDU = (GetRpcInterfaceDirectoryRequestPDU_t*)GspMemory_calloc(1, sizeof(GetRpcInterfaceDirectoryRequestPDU_t));

    // 设置referenceAfter
    if(paramReferenceAfter){
        requestPDU->referenceAfter = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, paramReferenceAfter, strlen(paramReferenceAfter));
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetRpcInterfaceDirectoryRequestPDU,
                                                nullptr,
                                                requestPDU,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("GetRpcInterfaceDirectoryRequest encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDirectoryRequestPDU, requestPDU);
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
        printf("APER: 获取RPC接口目录请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetRpcInterfaceDirectoryRequestPDU, requestPDU);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDirectoryRequestPDU, requestPDU);
    return true;
}

bool mmsClient_parseGetRpcInterfaceDirectoryResponse(GspByteBuffer* message, GspLinkedList* outDataList){
    // 异常判断
    if(message == nullptr){
        printf("获取RPC接口回应帧数据处理失败\n");
        return false;
    }

    // 解析报文
    GetRpcInterfaceDirectoryResponsePDU_t* responsePDU = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetRpcInterfaceDirectoryResponsePDU,
                                               (void **)(&responsePDU),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetRpcInterfaceDirectoryResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDirectoryResponsePDU, responsePDU);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取RPC接口目录应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetRpcInterfaceDirectoryResponsePDU, responsePDU);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outDataList == nullptr){
        *outDataList = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outDataList, responsePDU);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetDataSetDirectoryResponsePDU, getDataSetDirectoryResponse);

    return *(responsePDU->moreFollows);
}

bool mmsClient_createGetRpcMethodDirectoryRequest(GspMmsConnection self,
                                                  GspByteBuffer* outMessage,
                                                  uint16_t invokeId,
                                                  const char* paramInterface,
                                                  const char* paramReferenceAfter){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装RPC方法目录帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetRpcMethodDirectory);

    // 请求数据参数
    GetRpcMethodDirectoryRequestPDU_t* requestPDU = (GetRpcMethodDirectoryRequestPDU_t*)GspMemory_calloc(1, sizeof(GetRpcMethodDirectoryRequestPDU_t));

    // 设置refs
    if(paramInterface){
#ifdef NOT_USE_IN_C11
		OCTET_STRING_t *pTmpString = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString, paramInterface, strlen(paramInterface));
		requestPDU->interfaceAPI = pTmpString;
#else
        requestPDU->interface = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString, paramInterface, strlen(paramInterface));
#endif

    }

    // 设置referenceAfter
    if(paramReferenceAfter){
        requestPDU->referenceAfter = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, paramReferenceAfter, strlen(paramReferenceAfter));
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetRpcMethodDirectoryRequestPDU,
                                                nullptr,
                                                requestPDU,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("GetRpcMethodDirectoryRequest encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDirectoryRequestPDU, requestPDU);
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
        printf("APER: 获取RPC方法目录请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetRpcMethodDirectoryRequestPDU, requestPDU);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDirectoryRequestPDU, requestPDU);
    return true;
}

bool mmsClient_parseGetRpcMethodDirectoryResponse(GspByteBuffer* message, GspLinkedList* outDataList){
    // 异常判断
    if(message == nullptr){
        printf("获取RPC方法目录回应帧数据处理失败\n");
        return false;
    }

    // 解析报文
    GetRpcMethodDirectoryResponsePDU_t* responsePDU = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetRpcMethodDirectoryResponsePDU,
                                               (void **)(&responsePDU),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetRpcMethodDirectoryResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDirectoryResponsePDU, responsePDU);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取RPC方法目录应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetRpcMethodDirectoryResponsePDU, responsePDU);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outDataList == nullptr){
        *outDataList = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outDataList, responsePDU);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDirectoryResponsePDU, responsePDU);

    return *(responsePDU->moreFollows);
}


bool mmsClient_createGetRpcInterfaceDefinitionRequest(GspMmsConnection self,
                                                      GspByteBuffer* outMessage,
                                                      uint16_t invokeId,
                                                      const char* paramInterface,
                                                      const char* paramRefsAfter){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装获取RPC接口定义帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetRpcInterfaceDefinition);

    // 请求数据参数
    GetRpcInterfaceDefinitionRequestPDU_t* requestPDU = (GetRpcInterfaceDefinitionRequestPDU_t*)GspMemory_calloc(1, sizeof(GetRpcInterfaceDefinitionRequestPDU_t));

    // 设置refs
    if(paramInterface){
#ifdef NOT_USE_IN_C11
		OCTET_STRING_fromBuf(&requestPDU->interfaceAPI, paramInterface, strlen(paramInterface));
#else
        OCTET_STRING_fromBuf(&requestPDU->interface, paramInterface, strlen(paramInterface));
#endif
    }

    // refs after
    if(paramRefsAfter){
        requestPDU->referenceAfter = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString, paramRefsAfter, strlen(paramRefsAfter));
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetRpcInterfaceDefinitionRequestPDU,
                                                nullptr,
                                                requestPDU,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("GetRpcInterfaceDefinitionRequest encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDefinitionRequestPDU, requestPDU);
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
        printf("APER: 获取RPC方法目录请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetRpcInterfaceDefinitionRequestPDU, requestPDU);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDefinitionRequestPDU, requestPDU);
    return true;
}

bool mmsClient_parseGetRpcInterfaceDefinitionResponse(GspByteBuffer* message, GspLinkedList* outDataList){
    // 异常判断
    if(message == nullptr){
        printf("获取RPC接口定义回应帧数据处理失败\n");
        return false;
    }

    // 解析报文
    GetRpcInterfaceDefinitionResponsePDU_t* responsePDU = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetRpcInterfaceDefinitionResponsePDU,
                                               (void **)(&responsePDU),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetRpcInterfaceDefinitionResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDefinitionResponsePDU, responsePDU);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取RPC接口定义应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetRpcInterfaceDefinitionResponsePDU, responsePDU);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outDataList == nullptr){
        *outDataList = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outDataList, responsePDU);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetRpcInterfaceDefinitionResponsePDU, responsePDU);

    return *(responsePDU->moreFollows);
}


bool mmsClient_createGetRpcMethodDefinitionRequest(GspMmsConnection self,
                                                   GspByteBuffer* outMessage,
                                                   uint16_t invokeId,
                                                   GspLinkedList paramRefList){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装获取RPC方法定义帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_GetRpcMethodDefinition);

    // 请求数据参数
    GetRpcMethodDefinitionRequestPDU_t* requestPDU = (GetRpcMethodDefinitionRequestPDU_t*)GspMemory_calloc(1, sizeof(GetRpcMethodDefinitionRequestPDU_t));

    // 设置refs
#ifdef NOT_USE_IN_C11
	deque<void *> d = *paramRefList;
	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++){
		char* refItemStr = (char*)(*it);
#else
    for(auto &refItem: *paramRefList){
        char* refItemStr = (char*)refItem;
#endif
        VisibleString_t* tmpItem = OCTET_STRING_new_fromBuf(&asn_DEF_VisibleString, refItemStr, strlen(refItemStr));
        ASN_SEQUENCE_ADD(&(requestPDU->reference.list), tmpItem);
    }

    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_GetRpcMethodDefinitionRequestPDU,
                                                nullptr,
                                                requestPDU,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("GetRpcMethodDefinitionRequest encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDefinitionRequestPDU, requestPDU);
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
        printf("APER: 获取RPC方法定义请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetRpcMethodDefinitionRequestPDU, requestPDU);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDefinitionRequestPDU, requestPDU);
    return true;
}


bool mmsClient_parseGetRpcMethodDefinitionResponse(GspByteBuffer* message, GspLinkedList* outDataList){
    // 异常判断
    if(message == nullptr){
        printf("获取RPC方法定义回应帧数据处理失败\n");
        return false;
    }

    // 解析报文
    GetRpcMethodDefinitionResponsePDU_t* responsePDU = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetRpcMethodDefinitionResponsePDU,
                                               (void **)(&responsePDU),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("GetRpcMethodDefinitionResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDefinitionResponsePDU, responsePDU);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 获取RPC方法定义应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_GetRpcMethodDefinitionResponsePDU, responsePDU);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outDataList == nullptr){
        *outDataList = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outDataList, responsePDU);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_GetRpcMethodDefinitionResponsePDU, responsePDU);

    return *(responsePDU->moreFollows);
}

bool mmsClient_createRpcCallRequest(GspMmsConnection self,
                                    GspByteBuffer* outMessage,
                                    uint16_t invokeId,
                                    const char * paramFuncation,
                                    GspMmsValue* paramData,
                                    const char* paramCallID){
    // 异常判断
    if(outMessage == nullptr){
        printf("封装RPCCall帧数据失败\n");
        return false;
    }

    // invokeid 内存赋值
    memcpy(outMessage->buffer, &invokeId, sizeof(invokeId));
    outMessage->size += sizeof(invokeId);

    // 设置请求头部信息
    GspIsoClientConnection_setCc(self->isoClient, 0, 0, 0, 0x01);
    GspIsoClientConnection_setResponseSc(self->isoClient, GSP_MMS_SC_RpcCall);

    // 请求数据参数
    RpcCallRequestPDU_t* requestPDU = (RpcCallRequestPDU_t*)GspMemory_calloc(1, sizeof(RpcCallRequestPDU_t));

    // 方法名字
    if(paramFuncation){
        OCTET_STRING_fromBuf(&requestPDU->method, paramFuncation, strlen(paramFuncation));
    }

    // 设置参数
    if(paramCallID){
        requestPDU->req.present = RpcCallRequestPDU__req_PR_callID;
        OCTET_STRING_fromBuf(&(requestPDU->req.choice.callID), paramCallID, strlen(paramCallID));
    } else {
        requestPDU->req.present = RpcCallRequestPDU__req_PR_reqData;
        GspMmsValue_update(&(requestPDU->req.choice.reqData), paramData);
    }


    // 编码
    asn_enc_rval_t dVal = aper_encode_to_buffer(&asn_DEF_RpcCallRequestPDU,
                                                nullptr,
                                                requestPDU,
                                                outMessage->buffer + 2,
                                                (size_t)outMessage->maxSize - 2);
    if(dVal.encoded <= 0) {
        // TODO: 编码错误
        printf("RpcCallRequest encode error\n");

        // 内存释放
        ASN_STRUCT_FREE(asn_DEF_RpcCallRequestPDU, requestPDU);
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
        printf("APER: RPCCall 请求帧信息\n");
        xer_fprint(stdout, &asn_DEF_RpcCallRequestPDU, requestPDU);
        printf("****************************** 请求信息帧(结束) *******************************\n");
    }

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_RpcCallRequestPDU, requestPDU);
    return true;
}

bool mmsClient_parseRpcCallResponse(GspByteBuffer* message, GspLinkedList* outDataList){
    // 异常判断
    if(message == nullptr){
        printf("RPCCall 回应帧数据处理失败\n");
        return false;
    }

    // 解析报文
    RpcCallResponsePDU_t* responsePDU = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_RpcCallResponsePDU,
                                               (void **)(&responsePDU),
                                               message->buffer,
                                               static_cast<size_t>(message->size));
    if(rval.code != RC_OK) {
        printf("RpcCallResponse decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_RpcCallResponsePDU, responsePDU);
        return false;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: RPCCall 应答帧信息\n");
        xer_fprint(stdout, &asn_DEF_RpcCallResponsePDU, responsePDU);
    }

    // 如果链表信息为空，则创建链表信息
    if(*outDataList == nullptr){
        *outDataList = GspLinkedList_create();
    }

    // 赋值
    GspLinkedList_add(*outDataList, responsePDU);

    // 内存释放 (使用者释放)
    // ASN_STRUCT_FREE(asn_DEF_RpcCallResponsePDU, responsePDU);

    return true;
}
