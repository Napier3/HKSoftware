// EpFrameBase.cpp: implementation of the CEpFrameBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpFrameBase.h"
#include "EpProtocolBase.h"
#include "..\CmmChannel\EpCmmChannel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpFrameBase::CEpFrameBase()
{ 
	memset(&m_tm,0,sizeof(SYSTEMTIME));
	m_dwTickCount = 0;
	m_nLength = 0;
	m_pFrameGroup = NULL;
	m_pBuffer = NULL;
	m_dwState = EPFRAME_STATE_CHECK_TRUE;
	m_dwNetCmmMode = ID_NET_CMM_MODE_TOPOINT;
	m_bLock = FALSE;

	m_pEpProcedure = NULL;
	m_pChannel = NULL;
	m_nTimeoutLong = 20000;
}

CEpFrameBase::~CEpFrameBase()
{
	if (m_pBuffer != NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}

}

void CEpFrameBase::CopyBuffer(BYTE *pRcvBuffer,long nLen)
{
	m_nLength = nLen;

	if (m_pBuffer != NULL)
	{
		delete m_pBuffer;
	}

	m_pBuffer = new CCycleMemBuffer();
	m_pBuffer->SetBufferLength(nLen);
	m_pBuffer->CopyBuffer(pRcvBuffer, nLen, 0);
}

void CEpFrameBase::FreeBuffer()
{
	if (m_pBuffer != NULL)
	{
		delete m_pBuffer;
	}

	m_nLength = 0;
	m_pBuffer = NULL;
}

void CEpFrameBase::GetFrameBufferPos(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->pBuffer      = m_pBuffer->GetBuffer();
	pBufferPos->dwBufferLen  = m_pBuffer->GetBufferLength();
	pBufferPos->nIndex       = 0;
	pBufferPos->nFrameCurr   = 0;
	pBufferPos->dwState      = 0;
}

BOOL CEpFrameBase::IsParseFrame()
{
	return TRUE;
}

BOOL CEpFrameBase::IsProduceFrame()
{
	return TRUE;
}

long CEpFrameBase::IsEqual(CExBaseObject* pObj)
{
	CEpFrameBase *p = (CEpFrameBase*)pObj;

	return 0;
}

long CEpFrameBase::Copy(CExBaseObject* pDesObj)
{
	CEpFrameBase *p = (CEpFrameBase*)pDesObj;

	return 0;
}

DWORD CEpFrameBase::Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)
{
	Ep_BeginParseFrame(pBufferPos);

	ParseOwn(pBufferPos, pDetailList);

	long nLen = 0;
	BYTE *pFrameBuffer = NULL;

	Ep_GetParseFrameBuffer(pBufferPos, &pFrameBuffer, &nLen);
	CopyBuffer(pFrameBuffer, nLen);

	return nLen;
}

BYTE CEpFrameBase::GetCheckSum(BYTE *byBuffer,int nLen)
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

void CEpFrameBase::Send()
{
	if (m_pChannel != NULL)
	{
		CEpCmmChannel *pChannel = (CEpCmmChannel*)m_pChannel;
		pChannel->Send(this);
	}
	else
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("帧\"%s\"没有指定发送通道"), m_strID);
	}
}

BOOL CEpFrameBase::IsTimeout()
{
	return (long(GetTickCount()-m_nBeginTime)>m_nTimeoutLong);

}

void CEpFrameBase::SetBeginTime()
{
	m_nBeginTime = GetTickCount();
}

void CEpFrameBase::SetChannel(CEpCmmChannel *pChannel)
{
	m_pChannel = pChannel;
}

void CEpFrameBase::AppendToDetail(CExBaseList *pList)
{
	pList->Append(this);
}

void CEpFrameBase::InitFrameNum()
{
	CEpCmmChannel *pCmmChannel = (CEpCmmChannel*)m_pChannel;
	m_nPkgNum = pCmmChannel->GetSendIndex();
}

void CEpFrameBase::InitSend(CExBaseObject *pEpProcedure, CEpCmmChannel *pChannel)
{
	m_pEpProcedure = pEpProcedure;
	m_pChannel = pChannel;
	m_dwState = EPFRAME_STATE_NONE;
	m_bLock = FALSE;
}

CEpByteBlock* CEpFrameBase::AddNewByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex)
{
	CEpByteBlock *pNew = new CEpByteBlock();
	pNew->m_strID = strID;
	pNew->m_strName = strID;
	pNew->m_nIndex = nIndex;
	pNew->m_nLength = nLen;
	pDetailList->AddNewChild(pNew);
	return pNew;
}
// 
// CEpByteBlockData* CEpFrameBase::AddNewDataByteBlock(const CString &strID, long nLen, long nIndex)
// {
// 	CEpByteBlockData *pNew = new CEpByteBlockData();
// 	pNew->m_strID = strID;
// 	pNew->m_nIndex = nIndex;
// 	pNew->m_nLength = nLen;
// 	AddNewChild(pNew);
// 	return pNew;
// }

void CEpFrameBase::InitTime()
{
	::GetLocalTime(&m_tm);
	m_dwTickCount = ::GetTickCount();

}

void CEpFrameBase::LogAndRecordProtocol()
{
	
}

CEpFrameBase* Ep_FindFrameByID(DWORD dwClassID, CExBaseObject *pCurr)
{
	CEpProtocolBase *pProtocol = (CEpProtocolBase*)pCurr->GetAncestor(EPCLASSID_PROTOCOL);
	ASSERT(pProtocol != NULL);

	return pProtocol->FindFrameByID(dwClassID);
}



//////////////////////////////////////////////////////////////////////////
//
CEpFrameDetail::CEpFrameDetail()
{

}

CEpFrameDetail::~CEpFrameDetail()
{

}

void CEpFrameDetail::InitDetail(CEpFrameBase *pFrame)
{
	pFrame->AppendToDetail(this);
	pFrame->RemoveAll();
	
	m_dwFrameClassID = pFrame->GetClassID();

	m_tm = pFrame->m_tm;//规约报文发送或者接受的时间
	m_dwTickCount = pFrame->m_dwTickCount;
	m_nBeginTime = pFrame->m_nBeginTime;
	m_nTimeoutLong = pFrame->m_nTimeoutLong;
	m_nLength = pFrame->m_nTimeoutLong;
	m_pBuffer = pFrame->m_pBuffer;
	m_dwNetCmmMode = pFrame->m_dwNetCmmMode;
	m_bLock = pFrame->m_bLock;
	m_bUsed = pFrame->m_bUsed;
	m_pChannel = pFrame->m_pChannel;
	m_pEpProcedure = pFrame->m_pEpProcedure;
	m_nPkgNum = pFrame->m_nPkgNum;
	m_pEngineThread = pFrame->m_pEngineThread;
//	m_dwRecord = pFrame->m_dwRecord;

	m_strID = pFrame->m_strID;
	m_strName = pFrame->m_strName;
}

void CEpFrameDetail::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	CExBaseObject::InsertTreeCtrl(pTreeCtrl, htiParent, (DWORD)m_pBuffer->GetBuffer());
}

