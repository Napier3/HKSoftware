// FrameBase.cpp: implementation of the CFrameBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FrameBase.h"
// #include "ProtocolBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrameBase::CFrameBase()
{ 
	memset(&m_tm,0,sizeof(SYSTEMTIME));
	m_nLength = 0;
	m_pBuffer = NULL;
	m_nChCount = 0;
	m_nMaxChCount = 0;
}

CFrameBase::~CFrameBase()
{
	if (m_pBuffer != NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}

}

void CFrameBase::CopyBuffer(BYTE *pRcvBuffer,long nLen)
{
	m_nLength = nLen;

	if (m_pBuffer != NULL)
	{
		delete m_pBuffer;
	}

	m_pBuffer = new CFrameMemBuffer();
	m_pBuffer->SetBufferLength(nLen);
	m_pBuffer->CopyBuffer(pRcvBuffer, nLen, 0);
}

void CFrameBase::FreeBuffer()
{
	if (m_pBuffer != NULL)
	{
		delete m_pBuffer;
	}

	m_nLength = 0;
	m_pBuffer = NULL;
}

void CFrameBase::GetFrameBufferPos(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->pBuffer      = m_pBuffer->GetBuffer();
	pBufferPos->nBufLength  = m_pBuffer->GetBufferLength();
	pBufferPos->nIndex       = 0;
	pBufferPos->nFrameCurr   = 0;
	pBufferPos->dwState      = 0;
}

BOOL CFrameBase::IsParseFrame()
{
	return TRUE;
}

BOOL CFrameBase::IsProduceFrame()
{
	return TRUE;
}

BOOL CFrameBase::IsEqual(CExBaseObject* pObj)
{
	CFrameBase *p = (CFrameBase*)pObj;

	return 0;
}

BOOL CFrameBase::Copy(CExBaseObject* pDesObj)
{
	CFrameBase *p = (CFrameBase*)pDesObj;

	return 0;
}

DWORD CFrameBase::Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)
{
	Ep_BeginParseFrame(pBufferPos);

	ParseOwn(pBufferPos, pDetailList);

	long nLen = 0;
	BYTE *pFrameBuffer = NULL;

	Ep_GetParseFrameBuffer(pBufferPos, &pFrameBuffer, &nLen);
	CopyBuffer(pFrameBuffer, nLen);

	return nLen;
}

DWORD CFrameBase::Parse(PEPBUFFERPOS pBufferPos)
{
	Ep_BeginParseFrame(pBufferPos);

	ParseOwn(pBufferPos);

	long nLen = 0;
	BYTE *pFrameBuffer = NULL;

	Ep_GetParseFrameBuffer(pBufferPos, &pFrameBuffer, &nLen);
	CopyBuffer(pFrameBuffer, nLen);

	return nLen;
}
BYTE CFrameBase::GetCheckSum(BYTE *byBuffer,int nLen)
{
	BYTE nCheckSum = 0;
	BYTE *pTemp = NULL;
	BYTE *pEnd = NULL;

	if ((byBuffer == NULL) || nLen <= 0)
	{
		return nCheckSum;
	}

	pTemp = byBuffer + 1;//从数据类型开始计算
	pEnd = byBuffer + nLen - 2;//2= 校验和+结束标识

	while (pTemp < pEnd)
	{
		nCheckSum += *pTemp;
		pTemp++;
	}

	return nCheckSum;
}

void CFrameBase::AppendToDetail(CExBaseList *pList)
{
	pList->Append(this);
}


CByteBlock* CFrameBase::AddNewByteBlock(CFrameDetail *pDetailList, const CString &strID, long nLen, long nIndex)
{
	CByteBlock *pNew = new CByteBlock();
	pNew->m_strID = strID;
	pNew->m_strName = strID;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	pDetailList->AddNewChild(pNew);
	return pNew;
}
// 
// CStByteBlockData* CFrameBase::AddNewDataByteBlock(const CString &strID, long nLen, long nIndSt)
// {
// 	CStByteBlockData *pNew = new CStByteBlockData();
// 	pNew->m_strID = strID;
// 	pNew->m_nIndSt = nIndSt;
// 	pNew->m_nLength = nLen;
// 	AddNewChild(pNew);
// 	return pNew;
// }


void CFrameBase::LogAndRecordProtocol()
{
	
}


int CFrameBase::SetChannelCount(int nCount)
{
	m_nChCount = 0;

	if(nCount>m_nMaxChCount)
	{
// 		if(m_pArrChannelData)
// 		{
// 			delete [] m_pArrChannelData;
// 			m_pArrChannelData = NULL;
// 		}
// 
// 		m_pArrChannelData = new CChannelData[nCount];
// 		if(m_pArrChannelData==NULL)
// 			return 0;
		m_nMaxChCount = nCount;
	}

	m_nChCount = nCount;
	return m_nChCount;
}
