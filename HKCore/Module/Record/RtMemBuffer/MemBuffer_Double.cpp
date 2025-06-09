// MemBuffer_Double.cpp: implementation of the CMemBuffer_Double class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemBuffer_Double.h"
#include "../../API/GlobalConfigApi.h"
#include "../../OSInterface/OSInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemBuffer_Double::CMemBuffer_Double()
{
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
	m_pBuffer			= NULL;
}

CMemBuffer_Double::~CMemBuffer_Double()
{
	FreeBuffer();
}

double* CMemBuffer_Double::GetBuffer()
{
	return m_pBuffer;
}

long CMemBuffer_Double::GetBufferLength()
{
	return m_nBufferLength;
}

long CMemBuffer_Double::GetDataFillBeginPosition()
{
	return m_nDataFillBeginPos;
}

long CMemBuffer_Double::GetDataLength()
{
	return m_nDataLength;
}

void CMemBuffer_Double::SetBufferLength(long lBufferLen)
{
	FreeBuffer();
	m_nBufferLength = lBufferLen;
	m_pBuffer = new double[lBufferLen+MEMBUFFER_LENGTH_EX];
	memset(m_pBuffer, 0, lBufferLen*sizeof(double));
}

void CMemBuffer_Double::AppendBuffer(double *pBuffer, long lLen)
{
	FreeBuffer();
	m_pBuffer = pBuffer;
	m_nBufferLength = lLen;
}

void CMemBuffer_Double::AppendBuffer(CMemBuffer_Double *pBuffer)
{
	FreeBuffer();
	m_pBuffer = pBuffer->GetBuffer();
}

long CMemBuffer_Double::CopyBuffer(double *pBuffer, long lLen, long lGap)
{
	long lPos1Begin = -1;
	long lPos1End = -1;
	long lPos2Begin = -1;
	long lPos2End = -1;

	long lLenCopy = CopyBuffer(lLen, lGap, FALSE, lPos1Begin, lPos1End, lPos2Begin, lPos2End);

	if (lPos1Begin >= 0)
	{
		CopyBufferByPos(pBuffer, lPos1Begin, lPos1End, lGap);
	}

	if (lPos2Begin >= 0)
	{
		CopyBufferByPos(pBuffer+lPos1End-lPos1Begin, lPos2Begin, lPos2End, lGap);
	}

	lLenCopy = CopyBuffer(lLen, lGap, TRUE, lPos1Begin, lPos1End, lPos2Begin, lPos2End);
	
	return lLenCopy;
}

//pBuffer：源缓冲区
//lCopyBeginPos：源缓冲开始拷贝的位置
long CMemBuffer_Double::CopyBuffer(CMemBuffer_Double *pBuffer, long &lCopyBeginPos, long lGap)
{
	{
		double *pTemp = pBuffer->GetBuffer();
		if (pTemp[pBuffer->GetBufferLength()-1] == 0x0087)
		{
			int i = 0;
		}
	}
	//确保源缓冲区的长度小于等于目标缓冲区的长度
	ASSERT(pBuffer->m_nBufferLength <= m_nBufferLength);
	if(pBuffer->m_nBufferLength > m_nBufferLength)
	{
		return -1;
	}
	
	//
	if (pBuffer->m_nDataLength == 0)
	{
		return -1;
	}
	
	long lOffset = 0;
	long lLen = 0;
	long lCopyLen = 0;
	long lCopyLenRet = 0;
	double *pTemp = NULL;

	//当前填充的位置大于开始拷贝的位置，只需要拷贝源数据的一个区域
	//即从lCopyBeginPos到pBuffer->m_nDataFillBeginPos位置
	if (pBuffer->m_nDataFillBeginPos > lCopyBeginPos)
	{
		pTemp = pBuffer->GetBuffer() + lCopyBeginPos;
		lLen = pBuffer->GetDataFillBeginPosition() - lCopyBeginPos;
		lCopyLenRet = CopyBuffer(pTemp, lLen, lGap);

		lOffset = lLen - lCopyLenRet;

//		if (lCopyLenRet == 0)
//		{
//			lCopyBeginPos = lCopyBeginPos + lCopyLenRet;//下一次拷贝的位置=当前位置+实际拷贝的长度
//		}
//		else if (lCopyBeginPos > 0)
//		{
//			lCopyBeginPos = lCopyBeginPos + lCopyLenRet - lOffset + lGap;
//		}
//		else //(lCopyBeginPos < 0)
//		{
//			lCopyBeginPos = lCopyBeginPos + lCopyLenRet - lOffset;
//		}
		
		lCopyBeginPos = lCopyBeginPos + lCopyLenRet;//下一次拷贝的位置=当前位置+实际拷贝的长度
	}
	else
	{
		//总的长度
		long nTotalLen = pBuffer->GetDataLength() - lCopyBeginPos + pBuffer->GetDataFillBeginPosition();

		//第一次拷贝，拷贝到缓冲区结束位置
		pTemp = pBuffer->GetBuffer() + lCopyBeginPos;
		lLen = pBuffer->GetDataLength() - lCopyBeginPos;
		lCopyLen = CopyBuffer(pTemp, lLen, lGap);
		lOffset = lLen - lCopyLen;  //间隔拷贝过程中到缓冲区末尾剩下的长度
		lCopyLenRet = lCopyLen;

		//第二次拷贝
		lLen = nTotalLen - lCopyLen;

		//第二次开始拷贝的起始位置
		if(lOffset > 0)
		{
			pTemp = pBuffer->GetBuffer() - lOffset + lGap;
		}
		else if (lOffset == 0)
		{
			pTemp = pBuffer->GetBuffer();
		}
		else //lOffset < 0
		{
			pTemp = pBuffer->GetBuffer() - lOffset;
		}

		//下一次拷贝的位置=第二次实际拷贝的长度
		lCopyLen = CopyBuffer(pTemp, lLen, lGap);
		lCopyBeginPos = lCopyLen - lOffset; 
		lCopyLenRet += lCopyLen;
	}

	return lCopyLenRet*lGap;
}

//第三个参数的作用是TRUE修改索引地址，FALSE时获得地址
long CMemBuffer_Double::CopyBuffer(long lLen, long lGap, BOOL bOffsetBuffer, long &lPos1Begin, long &lPos1End, long &lPos2Begin, long &lPos2End)
{
	long lLenCopy = lLen / lGap;
	long nOffset = lLen - lLenCopy * lGap;

	if (nOffset > 0)
	{
		lLenCopy++;
	}

	long lEndPos = m_nDataFillBeginPos + lLenCopy; //目标缓冲区期望末位置
	long lLenCopy1 = 0, lLenCopy2 = 0;
	
	lPos1Begin = -1;
	lPos1End   = -1;
	lPos2Begin = -1;
	lPos2End   = -1;
	
	if (lEndPos < m_nBufferLength)
	{
		lPos1Begin = m_nDataFillBeginPos;
		lPos1End   = lEndPos;
		
		if (bOffsetBuffer)
		{
			m_nDataFillBeginPos = lEndPos;
		}
	}
	else 
	{
		//第一次拷贝,从m_nDataFillBeginPos到缓冲区末尾
		lLenCopy1 = m_nBufferLength - m_nDataFillBeginPos;
		lPos1Begin = m_nDataFillBeginPos;
		lPos1End   = m_nBufferLength;
		
		//第一次拷贝,从缓冲区开始到......
		lLenCopy2 = lLenCopy - lLenCopy1;
		lPos2Begin = 0;
		lPos2End   = lLenCopy2;
		
		if (bOffsetBuffer)
		{
			m_nDataFillBeginPos = lLenCopy2;
		}
		
	}
	
	if (bOffsetBuffer)
	{
		m_nDataLength += lLenCopy;
		
		if (m_nDataLength >= m_nBufferLength)
		{
			m_nDataLength = m_nBufferLength;
		}
	}
	
	return lLenCopy*lGap;
}

long CMemBuffer_Double::CopyBufferByPos(double *pBuffer, long lBeginPos, long lEndPos, long lGap)
{
	ASSERT (lBeginPos >= 0 && lEndPos >= 0 && lEndPos >= lBeginPos);
	if (!(lBeginPos >= 0 && lEndPos >= 0 && lEndPos >= lBeginPos))
	{
		return 0;
	}

	double *pDest = NULL;
	double *pDestEnd = NULL;
	double *pSrc = NULL;
	double *pSrcEnd = NULL;	

	pDest = m_pBuffer + lBeginPos;
	
	if (lGap == 1)
	{
		memcpy(pDest, pBuffer, (lEndPos - lBeginPos)*sizeof(double));
	}
	else
	{
		pDestEnd = m_pBuffer + lEndPos;
		pSrc = pBuffer;
		
		while (pDest < pDestEnd)
		{
			*pDest = *pSrc;
			pDest++;
			pSrc += lGap;
		}
	}

	return lGap * (lEndPos - lBeginPos);
}

void CMemBuffer_Double::FreeBuffer()
{
	if (m_pBuffer!= NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
}

void CMemBuffer_Double::Init()
{
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
}

void CMemBuffer_Double::WriteLogTxt()
{
	if ((m_pBuffer == NULL)||(m_nDataLength<=0))
	{
		return;
	}

	CString strText;
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	strText = _P_GetLibraryPath();
	strText.AppendFormat(_T("MemBuffDouble-%04d.%02d.%02d_%02d-%02d-%02d-%03d.txt"),
		tm.wYear,tm.wMonth,tm.wDay, tm.wHour, tm.wMinute, tm.wSecond ,tm.wMilliseconds);
	CFile oFile;
	long nIndex = 0;

	if (oFile.Open(strText, CFile::modeCreate | CFile::modeWrite))
	{
		for (nIndex=0; nIndex<m_nDataLength; nIndex++)
		{
			strText.Format(_T("%lf\r\n"),m_pBuffer[nIndex]); 
			oFile.Write(strText.GetString(), strText.GetLength());
		}

		oFile.Close();
	}
}

/*
#ifdef _use_global_log_
void CMemBuffer_Double::LOG_ShowBuffer(BOOL bShowTitle)
{
	long nIndex = 0;
	CString strTemp;
	CString strData;

	if (bShowTitle)
	{
		strTemp.Format("BufferLen=%d  DataLen=%d  DataFill=%d", m_nBufferLength, m_nDataLength, m_nDataFillBeginPos);
		LOG_WriteLawString(strTemp);
	}

	for (nIndex=0; nIndex<m_nBufferLength; nIndex++)
	{
		strTemp.Format("%04d ", m_pBuffer[nIndex]);
		strData += strTemp;
	}

	LOG_WriteLawString(strData);
}

#endif*/



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CComplexMemBuffer_Double::CComplexMemBuffer_Double()
{
//	m_pScript = NULL;
	m_nSrcMemBufferCount = 0;
	long nIndex = 0;

	for (nIndex=0; nIndex<COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT; nIndex++)
	{
		m_pSrcBuffer[nIndex] = NULL;
	}

	//m_pScript = new CRtMemBufScript();
}

CComplexMemBuffer_Double::~CComplexMemBuffer_Double()
{
/*
	if (m_pScript != NULL)
	{
		delete m_pScript;
		m_pScript = NULL;
	}
*/
}

BOOL CComplexMemBuffer_Double::ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)
{
	short nVal = 0;
	long nIndex = 0;

/*
	for (nIndex=nPos1Begin; nIndex<nPos1End; nIndex++)
	{
		m_pScript->m_nIndex = nIndex;
		m_pScript->RunExpression();
		//m_pBuffer[nIndex] = nVal;
	}

	for (nIndex=nPos2Begin; nIndex<nPos2End; nIndex++)
	{
		m_pScript->m_nIndex = nIndex;
		m_pScript->RunExpression();
		//m_pBuffer[nIndex] = nVal;
	}
*/
	
	return TRUE;
}

/*

#ifdef _debug_complex_channel
void CComplexMemBuffer_Double::CreateScript()
{
	CRtScriptBase::PEXPNODE pNode = NULL;
	CRtScriptBase::PEXPNODE pLeft = NULL;
	CRtScriptBase::PEXPNODE pRight = NULL;

	//root
	pNode = m_pScript->NewExpNode();
	m_pScript->m_pExpRoot = pNode;
	pNode->nOptrID = RTSCRIPT_OPTRID_ADD;
	pNode->m_nIsRefValue = TRUE;
	pNode->pValue = m_pBuffer;

	pLeft = m_pScript->NewExpNode();
	pLeft->m_nIsRefValue = TRUE;
	pLeft->pValue = m_pSrcBuffer[0]->GetBuffer();
	pLeft->nOptrID = RTSCRIPT_OPTRID_REFVALUE;

	pRight = m_pScript->NewExpNode();
	pRight->m_nIsRefValue = TRUE;
	pRight->pValue = m_pSrcBuffer[1]->GetBuffer();
	pRight->nOptrID = RTSCRIPT_OPTRID_REFVALUE;

	pNode->pLeft = pLeft;
	pNode->pRight = pRight;
}

#endif
*/

