#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "asn_inc.h"
#include <string>

/**
 * @brief 编解码测试例子
 */

static unsigned int HexChar2Dec(char paramChar)
{
    if ('0' <= paramChar && paramChar <= '9') {
        return (paramChar - '0');
    } else if ('a' <= paramChar && paramChar <= 'f') {
        return (paramChar - 'a' + 10);
    } else if ('A' <= paramChar && paramChar <= 'F') {
        return (paramChar - 'A' + 10);
    } else {
        return -1;
    }
}

static unsigned int Str2Hex(const unsigned char *str)
{
    bool endFlag = (str[1] == '\0');
    unsigned int endValue = 0;
    if(endFlag){
        endValue = HexChar2Dec(str[0]);
    } else {
        endValue = HexChar2Dec(str[0])*16 + HexChar2Dec(str[1]);
    }
    return endValue;
}

int  StrHex2Hex(std::string paramIn, unsigned char *outData)
{
    unsigned char tmpHex[2] = {0};
    int len = paramIn.size() / 2;
    for (int index = 0; index < len; index++)
    {
        int idx = index * 2;
        tmpHex[0] = paramIn.data()[idx];
        tmpHex[1] = paramIn.data()[idx+1];
        outData[index] = (unsigned char)Str2Hex(tmpHex);
    }
    return len;
}



int main(int argc, char** argv) {
    // 报文数据
    string payload = "e200505f4c32323131444c44302f4c4c4e30535405e8abce030a";

    int payloadLen = payload.size();
    unsigned char *hexPayload = new unsigned char[payloadLen];
    memset(hexPayload, 0, payloadLen);
    int vaildPayloadLen = StrHex2Hex(payload, hexPayload);

    // 解码帧
    GetFileDirectoryResponsePDU_t *testPayload = nullptr;
    asn_dec_rval_t rval = aper_decode_complete(nullptr,
                                               &asn_DEF_GetAllDataDefinitionRequestPDU,
                                               (void **)&testPayload,
                                               hexPayload,
                                               vaildPayloadLen);
    if(rval.code != RC_OK) {
        printf("decode error!\n");
        ASN_STRUCT_FREE(asn_DEF_GetAllDataDefinitionRequestPDU, testPayload);
        return -1;
    }

    // 打印调试
    printf("解析正常 \n");
    xer_fprint(stdout, &asn_DEF_GetAllDataDefinitionRequestPDU, testPayload);

}


