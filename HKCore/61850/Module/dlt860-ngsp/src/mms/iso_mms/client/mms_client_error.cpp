#include "cotp.h"
#include <stdio.h>
#include "ServiceError.h"
#include "mms_client_internal.h"


uint16_t mmsClient_parseServerErrorResponse(GspByteBuffer* message, uint16_t *invokeId){
    // 异常判断
    if(message == nullptr){
        printf("错误代码解析失败\n");
        return 0;
    }

    // 编码解析
    ServiceError_t* errorCode = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_ServiceError,
                                               (void**)&errorCode,
                                               message->buffer,
                                               (size_t)message->size);
    if(rval.code != RC_OK) {
        printf("server error decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_ServiceError, errorCode);
        return 0;
    }

    // 打印测试
    if(DEBUG_APER){
        printf("APER: 错误代码信息\n");
        xer_fprint(stdout, &asn_DEF_ServiceError, errorCode);
    }

    // 错误代码
    uint16_t errorNo = static_cast<uint16_t>(*errorCode);

    // 内存释放
    ASN_STRUCT_FREE(asn_DEF_ServiceError, errorCode);

    return errorNo;
}
