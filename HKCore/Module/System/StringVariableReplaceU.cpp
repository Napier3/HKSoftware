// StringVariableReplaceU.cpp: implementation of the CStringVariableReplaceU class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringVariableReplaceU.h"
#include "..\API\StringApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringVariableReplaceU::CStringVariableReplaceU()
{
	m_pData = NULL;
	m_pDestBuffer = NULL;
	m_nDataLength = 0;
	m_nDestBufferLen = 0;
	m_bDataNew = TRUE;
	m_bBufAttach = FALSE;
}

CStringVariableReplaceU::CStringVariableReplaceU(CString &strBuffer, const CString &strSrc, const CString &strDest)
{
	m_bBufAttach = FALSE;
	Replace(strBuffer, strSrc, strDest);
}


CStringVariableReplaceU::~CStringVariableReplaceU()
{
	if (m_bBufAttach)
	{
		m_pData = NULL;
		m_pDestBuffer = NULL;
	}

	FreeSrc(TRUE);
	FreeDest(TRUE);
}


void CStringVariableReplaceU::InitBuffer(long nSrcBufLen, long nDestBufLen)
{
	FreeSrc(TRUE);
	FreeDest(TRUE);

	m_bDataNew = TRUE;
	m_pData = new wchar_t[nSrcBufLen];
	m_pDestBuffer = new wchar_t[nDestBufLen];

	m_pDestCurr = m_pDestBuffer;
	m_nDestBufferLen = nDestBufLen;
	m_pDestEnd = m_pDestBuffer + m_nDestBufferLen;
}

void CStringVariableReplaceU::FreeSrc(BOOL bDelete)
{
	m_nDataLength = 0;
	
	if (bDelete && m_bDataNew)
	{
		delete m_pData;
		m_pData = NULL;
	}
}

void CStringVariableReplaceU::FreeDest(BOOL bDelete)
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

void CStringVariableReplaceU::Init(const CString &strBuffer)
{
	FreeSrc(TRUE);
	m_nDataLength = strBuffer.GetLength();
	m_pData = strBuffer.GetString();  //GetString
	InitDestBuffer(m_nDataLength / 4);
	m_bDataNew = FALSE;
}

void CStringVariableReplaceU::ExpandDestBuffer(long nLen)
{
	ASSERT( m_pDestBuffer != NULL);
	wchar_t *pTemp = m_pDestBuffer;
	long nLenNew = m_nDestBufferLen + max(nLen, m_nDestBufferLen / 2)+50;
	m_pDestBuffer = new wchar_t[nLenNew];
	ZeroMemory(m_pDestBuffer, nLenNew);
	memcpy(m_pDestBuffer, pTemp, m_nDestBufferLen);
	m_nDestBufferLen = nLenNew;

	m_pDestCurr = m_pDestBuffer + (m_pDestCurr - pTemp);
	m_pDestEnd = m_pDestBuffer + m_nDestBufferLen;

	delete pTemp;
}

void CStringVariableReplaceU::InitDestBuffer(long nAddLen)
{
	if (m_bBufAttach)
	{
		return;
	}

	if (m_pDestBuffer == NULL)
	{
		m_nDestBufferLen = nAddLen + m_nDataLength;
		m_pDestBuffer = new wchar_t[m_nDestBufferLen + 5];
		m_pDestCurr = m_pDestBuffer;
		m_pDestEnd = m_pDestCurr + m_nDestBufferLen;
	}
	else
	{
		if (m_nDataLength + nAddLen > m_nDestBufferLen)
		{
			FreeDest(TRUE);
			m_nDestBufferLen = nAddLen + m_nDataLength;
			m_pDestBuffer = new wchar_t[m_nDestBufferLen + 5];
			m_pDestCurr = m_pDestBuffer;
			m_pDestEnd = m_pDestCurr + m_nDestBufferLen;
		}
	}

	m_pDestCurr = m_pDestBuffer;
	m_pDestBuffer[0] = 0;
}

long CStringVariableReplaceU::Replace(CString &strBuffer, const CString &strSrc, const CString &strDest)
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


long CStringVariableReplaceU::Replace(wchar_t *pSrcBuf, wchar_t *pDestBuf, const CString &strSrc, const CString &strDest, BOOL bValidSeparator)
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


long CStringVariableReplaceU::HasReplace(wchar_t *pSrcBuf, wchar_t *pDestBuf, const CString &strSrc, BOOL bValidSeparator)
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

long CStringVariableReplaceU::Replace(const CString &strSrc, const CString &strDest)
{
	const wchar_t *pszSrc = strSrc.GetString();
	const wchar_t *pszDest = strDest.GetString();

	long nDestLen = strDest.GetLength();
	long nSrcLen = strSrc.GetLength();
	long nReplaceCount = 0;

	const wchar_t *pBegin = NULL;
	const wchar_t *pCurr = m_pData;
	wchar_t *pDest = NULL;
	const wchar_t *pEnd = pCurr + m_nDataLength;

	//处理字符串一开始就是要替换的字符串
	if (pCurr < pEnd)
	{
		//非有效字符  字符串结束
		if (*(pCurr + nSrcLen) == 0 )
		{
			if (wcsncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				AddToDestBuffer(pszDest, nDestLen);
				pCurr = pCurr + nSrcLen;
				nReplaceCount++;
			}
		}
		else if ( !IsVariableChar(*(pCurr + nSrcLen)))
		{
			if (wcsncmp(pCurr, pszSrc, nSrcLen) == 0)
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
			if (wcsncmp(pCurr+1, pszSrc, nSrcLen) == 0)
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


long CStringVariableReplaceU::Replace2(const CString &strSrc, const CString &strDest)
{
	const wchar_t *pszSrc = strSrc.GetString();
	const wchar_t *pszDest = strDest.GetString();

	long nDestLen = strDest.GetLength();
	long nSrcLen = strSrc.GetLength();
	long nReplaceCount = 0;

	const wchar_t *pBegin = NULL;
	const wchar_t *pCurr = m_pData;
	wchar_t *pDest = NULL;
	//m_nDataLength = strBuffer.GetLength();
	const wchar_t *pEnd = pCurr + m_nDataLength;

	//处理字符串一开始就是要替换的字符串
	if (pCurr < pEnd)
	{
		//非有效字符  字符串结束
		if (*(pCurr + nSrcLen) == 0 )
		{
			if (wcsncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				AddToDestBuffer(pszDest, nDestLen);
				pCurr = pCurr + nSrcLen;
				nReplaceCount++;
			}
		}
		else// if ( !IsVariableChar(*(pCurr + nSrcLen)))
		{
			if (wcsncmp(pCurr, pszSrc, nSrcLen) == 0)
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

		if (wcsncmp(pCurr+1, pszSrc, nSrcLen) == 0)
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


long CStringVariableReplaceU::HasReplace(const CString &strSrc)
{
	const wchar_t *pszSrc = strSrc.GetString();
	long nSrcLen = strSrc.GetLength();
	long nReplaceCount = 0;

	const wchar_t *pBegin = NULL;
	const wchar_t *pCurr = m_pData;
	wchar_t *pDest = NULL;
	const wchar_t *pEnd = pCurr + m_nDataLength;

	//处理字符串一开始就是要替换的字符串
	if (pCurr < pEnd)
	{
		//非有效字符  字符串结束
		if (*(pCurr + nSrcLen) == 0 )
		{
			if (wcsncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				nReplaceCount++;
			}
		}
		else if ( !IsVariableChar(*(pCurr + nSrcLen)))
		{
			if (wcsncmp(pCurr, pszSrc, nSrcLen) == 0)
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
			if (wcsncmp(pCurr+1, pszSrc, nSrcLen) == 0)
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


long CStringVariableReplaceU::HasReplace2(const CString &strSrc)
{
	const wchar_t *pszSrc = strSrc.GetString();
	long nSrcLen = strSrc.GetLength();
	long nReplaceCount = 0;

	const wchar_t *pBegin = NULL;
	const wchar_t *pCurr = m_pData;
	const wchar_t *pEnd = pCurr + m_nDataLength;

	//处理字符串一开始就是要替换的字符串
	if (pCurr < pEnd)
	{
		//非有效字符  字符串结束
		if (*(pCurr + nSrcLen) == 0 )
		{
			if (wcsncmp(pCurr, pszSrc, nSrcLen) == 0)
			{
				nReplaceCount++;
			}
		}
		else// if ( !IsVariableChar(*(pCurr + nSrcLen)))
		{
			if (wcsncmp(pCurr, pszSrc, nSrcLen) == 0)
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

		if (wcsncmp(pCurr+1, pszSrc, nSrcLen) == 0)
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

void CStringVariableReplaceU::GetString(CString &strBuffer)
{
	strBuffer = m_pDestBuffer;
}

void CStringVariableReplaceU::AddToDestBuffer(const wchar_t *pBuffer, long nLen)
{
	if (nLen == 0)
	{
		return;
	}

	if (m_bBufAttach)
	{
		wcsncpy(m_pDestCurr, pBuffer, nLen);
		m_pDestCurr += nLen;
	}
	else
	{
		if (m_pDestCurr + nLen > m_pDestEnd)
		{
			ExpandDestBuffer(nLen);
		}

		wcsncpy(m_pDestCurr, pBuffer, nLen);
		m_pDestCurr += nLen;
	}
	
}