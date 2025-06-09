//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XUser.cpp  CXUser


#include "stdafx.h"
#include "XBuf_Utf8_to_CharGBK.h"

CXBuf_Utf8_to_CharGBK::CXBuf_Utf8_to_CharGBK()
{
	m_pBuf_SrcUtf8 = NULL;
	m_nLen_SrcUtf8_Buf = 0;

	m_pBuf_DestCharGBK = NULL;
	m_nLen_DestCharGBK = 0;
	m_nUseLen_DestGBK = 0;
}

CXBuf_Utf8_to_CharGBK::~CXBuf_Utf8_to_CharGBK()
{
	if (m_pBuf_SrcUtf8 != NULL)
	{
		delete m_pBuf_SrcUtf8;
	}

	if (m_pBuf_DestCharGBK != NULL)
	{
		delete m_pBuf_DestCharGBK;
	}
}

wchar_t* CXBuf_Utf8_to_CharGBK::charUtf8_to_charGBK(char *pStrUtf8, long nLen)
{
	long nDestLen = CopyToSrcUtf8(pStrUtf8, nLen);
	nLen = MultiByteToWideChar(CP_UTF8, 0, m_pBuf_SrcUtf8, nDestLen, NULL, 0);

	if (nLen > m_nLen_DestCharGBK)
	{
		if (m_pBuf_DestCharGBK != NULL)
		{
			delete m_pBuf_DestCharGBK;
		}

		m_nLen_DestCharGBK = nLen + nLen * 0.2;//zhouhj 20211014 原来为0.1有可能出现不够用的情况改为0.2
		m_pBuf_DestCharGBK = new wchar_t[m_nLen_DestCharGBK];
	}

	memset(m_pBuf_DestCharGBK, 0, m_nLen_DestCharGBK * sizeof(wchar_t));
	m_nUseLen_DestGBK = 0;
	charUtf8_to_wcharGBK(m_pBuf_SrcUtf8, nDestLen, m_pBuf_DestCharGBK, m_nUseLen_DestGBK);
	m_pBuf_DestCharGBK[m_nUseLen_DestGBK] = 0;

	return m_pBuf_DestCharGBK;
}

long CXBuf_Utf8_to_CharGBK::CopyToSrcUtf8(char *pStrUtf8, long nLen)
{
	long nLenDest = nLen + nLen * 0.2;//zhouhj 20211014 原来为0.1有可能出现不够用的情况改为0.2
	
	if (nLenDest > m_nLen_SrcUtf8_Buf)
	{
		if (m_pBuf_SrcUtf8 != NULL)
		{
			delete m_pBuf_SrcUtf8;
		}

		m_nLen_SrcUtf8_Buf = nLenDest;
		m_pBuf_SrcUtf8 = new char[m_nLen_SrcUtf8_Buf];
	}

	char *pDest = m_pBuf_SrcUtf8;
	char *pSrc = pStrUtf8;
	char *pEnd = pStrUtf8 + nLen;
	long nStrLen = nLen;

	while (pSrc < pEnd)
	{
		if (*pSrc == 0x0a)
		{
			if (*(pSrc - 1) != 0x0d)
			{
				*pDest = 0x0d;
				pDest++;
				nStrLen++;
			}
		}

		*pDest = *pSrc;
		pSrc++;
		pDest++;
	}

	*pDest = 0;

	return nStrLen;
}
