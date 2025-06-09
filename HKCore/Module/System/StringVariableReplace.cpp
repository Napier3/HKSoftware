// StringVariableReplaceU.cpp: implementation of the CStringVariableReplace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringVariableReplace.h"
#include "..\API\StringApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringVariableReplace::CStringVariableReplace()
{
	m_pData = NULL;
	m_pDestBuffer = NULL;
	m_nDataLength = 0;
	m_nDestBufferLen = 0;
	m_bDataNew = TRUE;
	m_bBufAttach = FALSE;
}

CStringVariableReplace::CStringVariableReplace(CString &strBuffer, const CString &strSrc, const CString &strDest)
{
	m_bBufAttach = FALSE;
	Replace(strBuffer, strSrc, strDest);
}


CStringVariableReplace::~CStringVariableReplace()
{
	if (m_bBufAttach)
	{
		m_pData = NULL;
		m_pDestBuffer = NULL;
	}

	FreeSrc(TRUE);
	FreeDest(TRUE);
}


void CStringVariableReplace::InitBuffer(long nSrcBufLen, long nDestBufLen)
{
	FreeSrc(TRUE);
	FreeDest(TRUE);

	m_bDataNew = TRUE;
	m_pData = new char[nSrcBufLen];
	m_pDestBuffer = new char[nDestBufLen];

	m_pDestCurr = m_pDestBuffer;
	m_nDestBufferLen = nDestBufLen;
	m_pDestEnd = m_pDestBuffer + m_nDestBufferLen;
}

void CStringVariableReplace::FreeSrc(BOOL bDelete)
{
	m_nDataLength = 0;
	
	if (bDelete && m_bDataNew)
	{
		delete m_pData;
		m_pData = NULL;
	}
}

void CStringVariableReplace::FreeDest(BOOL bDelete)
{
	if (bDelete)
	{
		if (m_pDestBuffer != NULL)
		{
			delete []m_pDestBuffer;
			m_pDestBuffer = NULL;
		}

		m_nDestBufferLen = 0;
	}
	else
	{
		*m_pDestBuffer = 0;
	}
}

void CStringVariableReplace::Init(const CString &strBuffer)
{
	FreeSrc(TRUE);
	m_nDataLength = strBuffer.GetLength();
	m_pData = (char*)strBuffer.GetString();  //GetString
	InitDestBuffer(m_nDataLength / 4);
	m_bDataNew = FALSE;
}

void CStringVariableReplace::ExpandDestBuffer(long nLen)
{
	ASSERT( m_pDestBuffer != NULL);
	char *pTemp = m_pDestBuffer;
	long nLenNew = m_nDestBufferLen + max(nLen, m_nDestBufferLen / 2)+50;
	m_pDestBuffer = new char[nLenNew];
	ZeroMemory(m_pDestBuffer, nLenNew);
	memcpy(m_pDestBuffer, pTemp, m_nDestBufferLen);
	m_nDestBufferLen = nLenNew;

	m_pDestCurr = m_pDestBuffer + (m_pDestCurr - pTemp);
	m_pDestEnd = m_pDestBuffer + m_nDestBufferLen;

	delete pTemp;
}

void CStringVariableReplace::InitDestBuffer(long nAddLen)
{
	if (m_bBufAttach)
	{
		return;
	}

	if (m_pDestBuffer == NULL)
	{
		m_nDestBufferLen = nAddLen + m_nDataLength;
		m_pDestBuffer = new char[m_nDestBufferLen + 5];
		m_pDestCurr = m_pDestBuffer;
		m_pDestEnd = m_pDestCurr + m_nDestBufferLen;
	}
	else
	{
		if (m_nDataLength + nAddLen > m_nDestBufferLen)
		{
			FreeDest(TRUE);
			m_nDestBufferLen = nAddLen + m_nDataLength;
			m_pDestBuffer = new char[m_nDestBufferLen + 5];
			m_pDestCurr = m_pDestBuffer;
			m_pDestEnd = m_pDestCurr + m_nDestBufferLen;
		}
	}

	m_pDestCurr = m_pDestBuffer;
	m_pDestBuffer[0] = 0;
}

long CStringVariableReplace::Replace(CString &strBuffer, const CString &strSrc, const CString &strDest)
{
	ASSERT( !m_bBufAttach );

	if (strBuffer.GetLength() < strSrc.GetLength())
	{
		return 0;
	}

	Init(strBuffer);
	InitDestBuffer(0);

	long nReplaceCount = Replace(strSrc, strDest);

	if (nReplaceCount > 0)
	{
		strBuffer = m_pDestBuffer;
	}

	return nReplaceCount;
}


long CStringVariableReplace::Replace(char *pSrcBuf, char *pDestBuf, const CString &strSrc, const CString &strDest, BOOL bValidSeparator)
{
	m_bBufAttach = TRUE;
	m_pData = pSrcBuf;
	m_pDestBuffer = pDestBuf;
	m_pDestCurr = pDestBuf;
	long nLen = pDestBuf - pSrcBuf;
	nLen = abs(nLen);
	m_pDestEnd = pDestBuf + nLen;
	m_nDataLength = nLen;

	if (bValidSeparator)
	{
		return Replace(strSrc, strDest);
	}
	else
	{
		return Replace2(strSrc, strDest);
	}
}


long CStringVariableReplace::HasReplace(char *pSrcBuf, char *pDestBuf, const CString &strSrc, BOOL bValidSeparator)
{
	m_bBufAttach = TRUE;
	m_pData = pSrcBuf;
	m_pDestBuffer = pDestBuf;
	m_pDestCurr = pDestBuf;
	long nLen = pDestBuf - pSrcBuf;
	nLen = abs(nLen);
	m_pDestEnd = pDestBuf + nLen;
	m_nDataLength = nLen;

	if (bValidSeparator)
	{
		return HasReplace(strSrc);
	}
	else
	{
		return HasReplace2(strSrc);
	}
}

long CStringVariableReplace::Replace(const CString &strSrc, const CString &strDest)
{
	const char *pszSrc = strSrc.GetString();
	const char *pszDest = strDest.GetString();

	long nDestLen = strDest.GetLength();
	long nSrcLen = strSrc.GetLength();
	long nReplaceCount = 0;

	const char *pBegin = NULL;
	const char *pCurr = m_pData;
	char *pDest = NULL;
	const char *pEnd = pCurr + m_nDataLength;

	//处理字符串一开始就是要替换的字符串
	if (pCurr < pEnd)
	{
		//非有效字符  字符串结束
		if (*(pCurr + nSrcLen) == 0 )
		{
			if (strncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				AddToDestBuffer(pszDest, nDestLen);
				pCurr = pCurr + nSrcLen;
				nReplaceCount++;
			}
		}
		else if ( !IsVariableChar(*(pCurr + nSrcLen)))
		{
			if (strncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				AddToDestBuffer(pszDest, nDestLen);
				pCurr = pCurr + nSrcLen;
				nReplaceCount++;
			}
		}
	}

	pBegin = pCurr;

	while (pCurr < pEnd)
	{
		if (*pCurr == 0)
		{
			break;
		}

		//当前字符为分隔符号，字符串长度之外的也是分隔符
		if ((!IsVariableChar(*(pCurr))) && (!IsVariableChar(*(pCurr+nSrcLen+1)))  )
		{
			if (strncmp(pCurr+1, pszSrc, nSrcLen) == 0)
			{
				//拷贝其他字符串数据 
				if (pBegin != NULL)
				{
					AddToDestBuffer(pBegin, pCurr - pBegin+1);
				}

				//拷贝替换的目标字符串数据
				AddToDestBuffer(pszDest, nDestLen);
				pCurr = pCurr + nSrcLen+1;
				//AddToDestBuffer(*pCurr);
				//pCurr++;
				pBegin = pCurr;
				nReplaceCount++;
			}
			else
			{
				pCurr++;		
			}
		}
		else
		{
			pCurr++;
		}
	}
	
	if (nReplaceCount > 0)
	{
		if (pBegin != pCurr)
		{
			pEnd = m_pData + m_nDataLength;
			AddToDestBuffer(pBegin, pCurr - pBegin+1);
		}

		*m_pDestCurr = 0;
	}


	return nReplaceCount;
}


long CStringVariableReplace::Replace2(const CString &strSrc, const CString &strDest)
{
	const char *pszSrc = strSrc.GetString();
	const char *pszDest = strDest.GetString();

	long nDestLen = strDest.GetLength();
	long nSrcLen = strSrc.GetLength();
	long nReplaceCount = 0;

	const char *pBegin = NULL;
	const char *pCurr = m_pData;
	char *pDest = NULL;
	//m_nDataLength = strBuffer.GetLength();
	const char *pEnd = pCurr + m_nDataLength;

	//处理字符串一开始就是要替换的字符串
	if (pCurr < pEnd)
	{
		//非有效字符  字符串结束
		if (*(pCurr + nSrcLen) == 0 )
		{
			if (strncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				AddToDestBuffer(pszDest, nDestLen);
				pCurr = pCurr + nSrcLen;
				nReplaceCount++;
			}
		}
		else// if ( !IsVariableChar(*(pCurr + nSrcLen)))
		{
			if (strncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				AddToDestBuffer(pszDest, nDestLen);
				pCurr = pCurr + nSrcLen;
				nReplaceCount++;
			}
		}
	}

	pBegin = pCurr;

	while (pCurr < pEnd)
	{
		if (*pCurr == 0)
		{
			break;
		}

		if (strncmp(pCurr+1, pszSrc, nSrcLen) == 0)
		{
			//拷贝其他字符串数据 
			if (pBegin != NULL)
			{
				AddToDestBuffer(pBegin, pCurr - pBegin+1);
			}

			//拷贝替换的目标字符串数据
			AddToDestBuffer(pszDest, nDestLen);
			pCurr = pCurr + nSrcLen+1;
			//AddToDestBuffer(*pCurr);
			//pCurr++;
			pBegin = pCurr;
			nReplaceCount++;
		}
		else
		{
			pCurr++;		
		}
	}

	if (nReplaceCount > 0)
	{
		if (pBegin != pCurr)
		{
			pEnd = m_pData + m_nDataLength;
			AddToDestBuffer(pBegin, pCurr - pBegin+1);
		}

		*m_pDestCurr = 0;
	}

	return nReplaceCount;
}


long CStringVariableReplace::HasReplace(const CString &strSrc)
{
	const char *pszSrc = strSrc.GetString();
	long nSrcLen = strSrc.GetLength();
	long nReplaceCount = 0;

	const char *pBegin = NULL;
	const char *pCurr = m_pData;
	char *pDest = NULL;
	const char *pEnd = pCurr + m_nDataLength;

	//处理字符串一开始就是要替换的字符串
	if (pCurr < pEnd)
	{
		//非有效字符  字符串结束
		if (*(pCurr + nSrcLen) == 0 )
		{
			if (strncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				nReplaceCount++;
			}
		}
		else if ( !IsVariableChar(*(pCurr + nSrcLen)))
		{
			if (strncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				nReplaceCount++;
			}
		}
	}

	if (nReplaceCount > 0)
	{
		return nReplaceCount;
	}

	pBegin = pCurr;

	while (pCurr < pEnd)
	{
		if (*pCurr == 0)
		{
			break;
		}

		//当前字符为分隔符号，字符串长度之外的也是分隔符
		if ((!IsVariableChar(*(pCurr))) && (!IsVariableChar(*(pCurr+nSrcLen+1)))  )
		{
			if (strncmp(pCurr+1, pszSrc, nSrcLen) == 0)
			{
				nReplaceCount++;
				break;
			}
			else
			{
				pCurr++;		
			}
		}
		else
		{
			pCurr++;
		}
	}
	
	return nReplaceCount;
}


long CStringVariableReplace::HasReplace2(const CString &strSrc)
{
	const char *pszSrc = strSrc.GetString();
	long nSrcLen = strSrc.GetLength();
	long nReplaceCount = 0;

	const char *pBegin = NULL;
	const char *pCurr = m_pData;
	const char *pEnd = pCurr + m_nDataLength;

	//处理字符串一开始就是要替换的字符串
	if (pCurr < pEnd)
	{
		//非有效字符  字符串结束
		if (*(pCurr + nSrcLen) == 0 )
		{
			if (strncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				nReplaceCount++;
			}
		}
		else// if ( !IsVariableChar(*(pCurr + nSrcLen)))
		{
			if (strncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				nReplaceCount++;
			}
		}
	}

	if (nReplaceCount > 0)
	{
		return nReplaceCount;
	}

	pBegin = pCurr;

	while (pCurr < pEnd)
	{
		if (*pCurr == 0)
		{
			break;
		}

		if (strncmp(pCurr+1, pszSrc, nSrcLen) == 0)
		{
			nReplaceCount++;
			break;
		}
		else
		{
			pCurr++;		
		}
	}

	return nReplaceCount;
}

void CStringVariableReplace::GetString(CString &strBuffer)
{
	strBuffer = m_pDestBuffer;
}

void CStringVariableReplace::AddToDestBuffer(const char *pBuffer, long nLen)
{
	if (nLen == 0)
	{
		return;
	}

	if (m_bBufAttach)
	{
		strncpy(m_pDestCurr, pBuffer, nLen);
		m_pDestCurr += nLen;
	}
	else
	{
		if (m_pDestCurr + nLen > m_pDestEnd)
		{
			ExpandDestBuffer(nLen);
		}

		strncpy(m_pDestCurr, pBuffer, nLen);
		m_pDestCurr += nLen;
	}
	
}