#ifndef __String_Utf8_To_Gbk_h__
#define __String_Utf8_To_Gbk_h__

#ifdef __cplusplus
extern "C" {
#endif

int utf8_to_gbk(const unsigned char* pszBufIn, int nBufInLen, unsigned char* pszBufOut, int* pnBufOutLen);
int utf8_to_gbk_r(const unsigned char* pszBufIn, int nBufInLen, unsigned char** ppszBufOut, int* pnBufOutLen);
//2022-12-12  lijunqing C语言同名函数问题，所以将返回新建字符串的改为 utf8_to_gbk_r

#ifdef __cplusplus
}
#endif

#endif


