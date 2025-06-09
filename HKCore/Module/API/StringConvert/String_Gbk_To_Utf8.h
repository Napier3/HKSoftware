#ifndef __String_Gbk_To_Utf8_h__
#define __String_Gbk_To_Utf8_h__

#ifdef __cplusplus
extern "C" {
#endif

int gbk_to_utf8(const unsigned char* pszBufIn, int nBufInLen, unsigned char* pszBufOut, int* pnBufOutLen);
int gbk_to_utf8_r(const unsigned char* pszBufIn, int nBufInLen, unsigned char** ppszBufOut, int* pnBufOutLen, int nOffset);
//2022-12-12  lijunqing C����ͬ���������⣬���Խ������½��ַ����ĸ�Ϊ gbk_to_utf8_r

#ifdef __cplusplus
}
#endif

#endif

