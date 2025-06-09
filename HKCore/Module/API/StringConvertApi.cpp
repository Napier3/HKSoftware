#include "stdafx.h"
#include "StringConvertApi.h"

#include "StringApi.h"

#include "StringConvert/String_Gbk_To_Utf8.h"
#include "StringConvert/String_Utf8_To_Gbk.h"

int utf8_to_gbk(const CString &strUtf8,CString &strGbk)
{
	unsigned char* pStringGBK = NULL,*pStringUTF8 = NULL;
	pStringUTF8 = (unsigned char *)strUtf8.GetString();
	int nLenth = 0;
//	CString_to_char(strUtf8,(char**)&pStringUTF8);
	utf8_to_gbk_r((const unsigned char*)pStringUTF8,strlen((char*)pStringUTF8),&pStringGBK,&nLenth);
//	delete pStringUTF8;

	if (pStringGBK != NULL)
	{
		strGbk = (char*)pStringGBK;
		delete pStringGBK;
	}

	return nLenth;
}

int gbk_to_utf8(const CString &strGbk,CString &strUtf8)
{
	unsigned char* pStringGBK = NULL,*pStringUTF8 = NULL;
	pStringGBK = (unsigned char *)strGbk.GetString();
	int nLenth = 0;
//	CString_to_char(strGbk,(char**)&pStringGBK);
	utf8_to_gbk_r((const unsigned char*)pStringGBK,strlen((char*)pStringGBK),&pStringUTF8,&nLenth);
//	delete pStringGBK;

	if (pStringUTF8 != NULL)
	{
		strUtf8 = (char*)pStringUTF8;
		delete pStringUTF8;
	}

	return nLenth;
}

int Test_Convert()
{
// 	char pszSrcBuf[32];
// 	strcpy(pszSrcBuf, "≤‚ ‘1234");
// 	long nLen = strlen(pszSrcBuf);
// 	char pszSrcUtf8_w[64], pszSrcUtf8_l[64];
// 	char pszSrcGbk_w[64], pszSrcGbk_l[64];
// 	long nDestLen = 0;
// 	long nDestLen_w = 0;
// 	unsigned char *pszGbkL;
// 	unsigned char *pszUtf8L;
// 	int nUtf8L = 0, nGbkL = 0;
// 
//  	charGBK_to_charUtf8(pszSrcBuf, nLen, pszSrcUtf8_w, nDestLen);
// 	long nLenUtf8 = strlen(pszSrcUtf8_w);
// 
// 	charUtf8_to_charGBK(pszSrcUtf8_w, nLenUtf8, pszSrcGbk_w, nDestLen_w);
// 
// 	utf8_to_gbk_r((unsigned char*)pszSrcUtf8_w, nLenUtf8, &pszGbkL, &nGbkL);
// 	utf8_to_gbk_r((unsigned char*)pszSrcBuf, nLen, &pszUtf8L, &nUtf8L);
// 
// 	delete pszGbkL;
// 	delete pszUtf8L;

	return 0;
}
