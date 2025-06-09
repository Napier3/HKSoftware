#include "StdAfx.h"
#include "CmmChannel.h"
#include "DeviceCmmChannel.h"

#include "../DeviceModel/CmmConfigBase.h"
#include "../DeviceModel/CmmOnConnect.h"
#include "../PpEngineThreadBase.h"
#include "DeviceCmmChannel.h"

#ifndef _PSX_QT_LINUX_
#include "Iphlpapi.h"
#endif


void CCmmRcvSndTime::Log()
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%d:%d:%d.%d == (%d-%d)-(%d-%d)")
		, m_tm.wHour, m_tm.wMinute,m_tm.wSecond, m_tm.wMilliseconds
		, m_oCycleBufferPos.nBuf1BeginPos, m_oCycleBufferPos.nBuf1EndPos
		, m_oCycleBufferPos.nBuf2BeginPos, m_oCycleBufferPos.nBuf2EndPos);
}

CCmmRcvSndTime* CCmmRcvSndTimeMngr::FindTimeByPos(long nPos)
{
	POS pos = GetHeadPosition();
	CCmmRcvSndTime *pTime = NULL;
	CCmmRcvSndTime *pFind = NULL;

	while (pos != NULL)
	{
		pTime = (CCmmRcvSndTime*)GetNext(pos);

		if (pTime->IsInBufferPos(nPos))
		{
			pFind = pTime;
			break;
		}
// 		else
// 		{
// 			pTime->m_dwTickCount = 0;
// 		}
	}

	return pFind;
}

void CCmmRcvSndTimeMngr::DeletePrev(CCmmRcvSndTime *pTime)
{
// 	long nCount = GetCount();
// 
// 	if (nCount < 100)
// 	{
// 		return;
// 	}
// 
// 	long nIndex = nCount - 100;
// 	while (nIndex > 0)
// 	{
// 		DeleteHead();
// 	}

	CTickCount32 oTickCount32;

	CCmmRcvSndTime *p = (CCmmRcvSndTime*)GetHead();

	while (p != pTime)
	{
		//if (p->m_dwTickCount == 0)
		//超过30毫秒，删除
		if (oTickCount32.CalTickCountLong2(p->m_dwTickCount) > 30000)
		{
			DeleteHead();
		}
		else
		{
			break;
		}

		p = (CCmmRcvSndTime*)GetHead();
	}
}

//////////////////////////////////////////////////////////////////////////
//
CAutoCriticSection CCmmChannel::g_oCmmLogAutoCriticSection;

CCmmChannel::CCmmChannel(void)
{
	m_dwConnectState = CONNECT_STATE_NORMAL;
	m_nSendIndex = 0;
	m_nReceiveLen = 0;
	m_pCycleRcvBuffer = NULL;
	m_nParserBeginPos = 0;
	m_nSendSpyBeginPos = 0;						//缓冲区监视开始的位置
	m_nReceiveSpyBeginPos = 0;						//缓冲区监视开始的位置
	m_bResetRcvBufPos = FALSE;

	m_pXPkgFullRcvJdgInterface = NULL;
	m_pProtoPkgPrcss = NULL;
}

CCmmChannel::~CCmmChannel(void)
{
	RemoveAll();
	FreeBuffer();
}

void CCmmChannel::FreeBuffer()
{
	FreeReceiveBuffer();
	FreeSendBuffer();
}

void CCmmChannel::FreeReceiveBuffer()
{
	if (m_bAttachReceiveBuffer)
	{
		m_pCycleRcvBuffer = NULL;
		m_bAttachReceiveBuffer = FALSE;
	}
	else
	{
		delete m_pCycleRcvBuffer;
		m_pCycleRcvBuffer = NULL;
	}
}

void CCmmChannel::FreeSendBuffer()
{
	if (m_bAttachSendBuffer)
	{
		m_pSendBuffer = NULL;
		m_bAttachSendBuffer = FALSE;
	}
	else
	{
		delete m_pSendBuffer;
		m_pSendBuffer = NULL;
	}
}

long CCmmChannel::GetBufferPos(long nBeginPos, long nLen, CYCLEMEMBUFFERPOS &oBufPos)
{
	ZeroMemory(&oBufPos, sizeof(CYCLEMEMBUFFERPOS));

	if (nBeginPos < 0)
	{
		return m_pCycleRcvBuffer->GetBufferPos(m_nParserBeginPos, -1, oBufPos);
	}
	else
	{
		return m_pCycleRcvBuffer->GetBufferPos(nBeginPos, -1, oBufPos);
	}
}

#ifndef _use_CMemBufferList
void CCmmChannel::AttacthReceiveBuffer(CCycleMemBuffer *pBuffer)
{
	FreeReceiveBuffer();
	m_bAttachReceiveBuffer = TRUE;
	m_pCycleRcvBuffer = pBuffer;
}
#endif

void CCmmChannel::AttacthSendBuffer(CCycleMemBuffer *pBuffer)
{
	FreeSendBuffer();
	m_bAttachSendBuffer = TRUE;
	m_pSendBuffer = pBuffer;
}

void CCmmChannel::SetReceiveBufferLength(long nLen)
{
	FreeReceiveBuffer();
#ifdef _use_CMemBufferList
	m_pCycleRcvBuffer = new CMemBufferList();
#else
	m_pCycleRcvBuffer = new CCycleMemBuffer();
	m_pCycleRcvBuffer->SetBufferLength(nLen);
#endif
}

void CCmmChannel::SetSendBufferLength(long nLen)
{
	FreeSendBuffer();
	m_pSendBuffer = new CCycleMemBuffer();
	m_pSendBuffer->SetBufferLength(nLen);
}

CBaseObject* CCmmChannel::GetDeviceCmmChannel()
{
	CBaseObject *pFind = NULL;
	CBaseObject *pParent = GetParent();

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == CMMCLASSID_DEVICE_CMM_CHANNEL)
		{
			pFind = pParent;
			break;
		}

		pParent = pParent->GetParent();
	}

	return pFind;
}

void CMM_SetAllSendPkgState(CExBaseList *pList, BOOL bSend)
{
	POS pos = pList->GetHeadPosition();
	CPpPackageSend *p = NULL;

	while (pos != NULL)
	{
		p = (CPpPackageSend*)pList->GetNext(pos);
		p->SetSendState(TRUE);
	}

	pList->RemoveAll();
}

void CCmmChannel::OnChannelReceive(CCmmRcvSndTime *pCmmTime)
{
	CDeviceCmmChannel *pDeviceChannel = (CDeviceCmmChannel*)GetDeviceCmmChannel();
	ASSERT (pDeviceChannel != NULL);

	if (pDeviceChannel != NULL)
	{
		pDeviceChannel->OnReceive(this, pCmmTime);
	}
}

void CCmmChannel::ResetSendSpyBeginPos()
{
	if (m_pSendBuffer != NULL)
	{
		m_nSendSpyBeginPos = m_pSendBuffer->GetDataFillBeginPosition();
	}
}

void CCmmChannel::ResetReceiveSpyBeginPos()
{
#ifdef _use_CMemBufferList
#else
	if (m_pCycleRcvBuffer != NULL)
	{
		m_nReceiveSpyBeginPos = m_pCycleRcvBuffer->GetDataFillBeginPosition();
	}
#endif
}

void CCmmChannel::GetReceiveBufferPos(CYCLEMEMBUFFERPOS &oCycleBufPos)
{
	if (m_pCycleRcvBuffer == NULL)
	{
		memset(&oCycleBufPos, 0, sizeof(CYCLEMEMBUFFERPOS));
		oCycleBufPos.nBuf1BeginPos = -1;
	}
	else
	{
		m_pCycleRcvBuffer->GetBufferPos(m_nReceiveSpyBeginPos, -1, oCycleBufPos);
	}
}

void CCmmChannel::GetSendBufferPos(CYCLEMEMBUFFERPOS &oCycleBufPos)
{
	if (m_pCycleRcvBuffer == NULL)
	{
		memset(&oCycleBufPos, 0, sizeof(CYCLEMEMBUFFERPOS));
		oCycleBufPos.nBuf1BeginPos = -1;
	}
	else
	{
		m_pSendBuffer->GetBufferPos(m_nSendSpyBeginPos, -1, oCycleBufPos);
	}
}

long g_nCmmChRcvBufferIndex = 0;
void CCmmChannel::AppendRcvBuffer(BYTE *pReceiveBuffer, long nLen, CCmmRcvSndTime *pCmmTime)
{
	if (m_pProtoPkgPrcss != NULL)
	{
		m_pProtoPkgPrcss->PrcssAfterRcv(pReceiveBuffer, nLen);
	}

#ifdef _use_CMemBufferList
	m_pCycleRcvBuffer->add_pipe_msg(nLen, pReceiveBuffer, &pCmmTime->m_oCycleBufferPos);
#else
	if (m_bResetRcvBufPos)
	{
		m_bResetRcvBufPos = FALSE;
		m_pCycleRcvBuffer->ResetOffsetDataFillBeginPosition();
	}

	//2019-12-2  李俊庆
	//循环缓冲处理，如果没有有效数据，则复位缓冲区的位置
	long nLenFromCurrToFillBeginPos = m_pCycleRcvBuffer->GetLenFromCurrToFillBeginPos(m_nParserBeginPos);
	long nFillBeginPos = m_pCycleRcvBuffer->GetDataFillBeginPosition();

	if (nLenFromCurrToFillBeginPos == 0 && m_nParserBeginPos > 0)
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Reset Buffer before AppendRcvBuffer:  m_nParserBeginPos=%d  FillBeginPos=%d ")
// 			, m_nParserBeginPos, nFillBeginPos);
		m_nParserBeginPos = 0;
		nFillBeginPos = 0;
		m_pCycleRcvBuffer->ResetOffsetDataFillBeginPosition();
	}

	m_pCycleRcvBuffer->AppendBuffer(pReceiveBuffer, nLen);

	//记录本次时间收到的规约数据的位置
	m_pCycleRcvBuffer->GetBufferPos(nFillBeginPos, nLen, pCmmTime->m_oCycleBufferPos);
	CExBaseObject *pPpEngineData = (CExBaseObject *)GetAncestor(PPCLASSID_PPENGINEDATA);
	CXPpPkgLogTool::AddPpPkgLog2(pCmmTime->m_oCycleBufferPos, TRUE, pPpEngineData, g_nCmmChRcvBufferIndex);
	g_nCmmChRcvBufferIndex++;
#endif


// 	if (g_bLogPackageInfor)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"********append buffer [%d~%d][%d~%d]"
// 			, pCmmTime->m_oCycleBufferPos.nBuf1BeginPos, pCmmTime->m_oCycleBufferPos.nBuf1EndPos
// 			, pCmmTime->m_oCycleBufferPos.nBuf2BeginPos, pCmmTime->m_oCycleBufferPos.nBuf2EndPos);
// 	}
}

#ifdef _use_CMemBufferList
void CCmmChannel::OnChannelReceive(CMemBufferList *pReceiveBuffer, CCmmRcvSndTime *pCmmTime, PCYCLEMEMBUFFERPOS pBufPos)
{
	ASSERT (m_pCycleRcvBuffer != NULL);
	ASSERT (pReceiveBuffer != NULL);

	if (m_pCycleRcvBuffer == pReceiveBuffer)
	{

	}
	else
	{
		if (pBufPos == NULL)
		{
			BYTE *pBuffer = pCmmTime->m_oCycleBufferPos.pBuffer;//pReceiveBuffer->GetBuffer();
			long nLen = pCmmTime->m_oCycleBufferPos.nBuf1EndPos;//pReceiveBuffer->GetDataLength();
			AppendRcvBuffer(pBuffer, nLen, pCmmTime);
		}
	}

	CDeviceCmmChannel *pDeviceChannel = (CDeviceCmmChannel*)GetDeviceCmmChannel();
	ASSERT (pDeviceChannel != NULL);

	if (pDeviceChannel != NULL)
	{
		pDeviceChannel->OnReceive(this, pCmmTime);
	}
}
#else
void CCmmChannel::OnChannelReceive(CCycleMemBuffer *pReceiveBuffer, CCmmRcvSndTime *pCmmTime, PCYCLEMEMBUFFERPOS pBufPos)
{
	ASSERT (m_pCycleRcvBuffer != NULL);
	ASSERT (pReceiveBuffer != NULL);

	if (m_pCycleRcvBuffer == pReceiveBuffer)
	{

	}
	else
	{
		if (pBufPos == NULL)
		{
			BYTE *pBuffer = pReceiveBuffer->GetBuffer();
			long nLen = pReceiveBuffer->GetDataLength();
			AppendRcvBuffer(pBuffer, nLen, pCmmTime);
		}
	}

	CDeviceCmmChannel *pDeviceChannel = (CDeviceCmmChannel*)GetDeviceCmmChannel();
	ASSERT (pDeviceChannel != NULL);

	if (pDeviceChannel != NULL)
	{
		pDeviceChannel->OnReceive(this, pCmmTime);
	}
}
#endif


void CCmmChannel::OnCmmChannelClose(CCmmChannel *pChannel)
{
	CDeviceCmmChannel *pDeviceChannel = (CDeviceCmmChannel*)GetDeviceCmmChannel();
	pDeviceChannel->OnCmmChannelClose(pChannel);
}

void CCmmChannel::Send(CExBaseObject *pPkgSend)
{
	AddTail(pPkgSend);
}

void CCmmChannel::OffsetParserBeginPos(long nOffset)
{
	ASSERT (m_pCycleRcvBuffer != NULL);

#ifdef _use_CMemBufferList
#else
	m_nParserBeginPos += nOffset;
	long nBufferLen = m_pCycleRcvBuffer->GetBufferLength();

	if (m_nParserBeginPos >= nBufferLen)
	{
		m_nParserBeginPos -= nBufferLen;
	}
#endif

}

void CCmmChannel::ResetReceiveBeginPos()
{
	m_bResetRcvBufPos = TRUE;
}

void CCmmChannel::ResetOffsetDataFillBeginPosition()
{
#ifdef _use_CMemBufferList
#else
	if (m_bResetRcvBufPos)
	{
		m_bResetRcvBufPos = FALSE;
		m_pCycleRcvBuffer->ResetOffsetDataFillBeginPosition();
	}
#endif
}

//连接完成
void CCmmChannel::OnConnectFinished()
{
	CDeviceCmmChannel *pDeviceChannel = (CDeviceCmmChannel*)GetDeviceCmmChannel();
	ASSERT (pDeviceChannel != NULL);

	if (pDeviceChannel != NULL)
	{
		if (pDeviceChannel->IsConnectSuccessful())
		{
			CLogPrint::LogFormatString(g_pLogTracePrint, XLOGLEVEL_TRACE, _T("OnDeviceConnectFinish"));
		}
		else
		{
			CLogPrint::LogFormatString(g_pLogTracePrint, XLOGLEVEL_TRACE, _T("OnDeviceConnectFailed"));
		}

		pDeviceChannel->OnCmmChannelConnectFinish();
	}
}

void CCmmChannel::OnConnectFailed()
{
	CDeviceCmmChannel *pDeviceChannel = (CDeviceCmmChannel*)GetDeviceCmmChannel();
	ASSERT (pDeviceChannel != NULL);

	if (pDeviceChannel != NULL)
	{
		pDeviceChannel->OnCmmChannelConnectFailed();
	}
}

BOOL CCmmChannel::IsCmmChannelExit()
{
	return FALSE;
}

BOOL CCmmChannel::DataIsEnoughForParse(long nMinLen)
{
	ASSERT (nMinLen >= 1);

	CYCLEMEMBUFFERPOS oBufPos;
	m_pCycleRcvBuffer->GetBufferPos(m_nParserBeginPos, -1, oBufPos);

	long nCurrLen = 0;
	if (oBufPos.nBuf1BeginPos == -1 && oBufPos.nBuf1EndPos == 0)
	{
		nCurrLen = 0;
	}
	else
	{
		nCurrLen = oBufPos.nBuf1EndPos - oBufPos.nBuf1BeginPos;
	}

	if (oBufPos.nBuf2EndPos >= 0 && oBufPos.nBuf2BeginPos >= 0)
	{
		nCurrLen += oBufPos.nBuf2EndPos - oBufPos.nBuf2BeginPos;
	}	

	return (nCurrLen >= nMinLen);
}

CExBaseObject* CCmmChannel::GetPackageSend()
{
	CAutoSimpleLock oLock(m_oSendListCriticSection);

	CPpPackageSend* pPkgSend = (CPpPackageSend*)GetHead();

	if (pPkgSend != NULL)
	{
		pPkgSend->m_pPackageDetail->InitPackageTime();
		pPkgSend->m_pPackageDetail->SetBeginTime();
	}

	oLock.Free();
	return pPkgSend;
}


void CCmmChannel::RemoveHead()
{
	if (GetCount() == 0)
	{
		return;
	}

	CAutoSimpleLock oLock(m_oSendListCriticSection);
	long nIndex = 0;
	RemoveAt(nIndex);
	oLock.Free();
}

void CMM_OnChannelConnectSucc(CExBaseList *pCmmConfig, CWinThread *pThread)
{
	POS pos = pCmmConfig->GetHeadPosition();
	CCmmOnConnect *pObj = NULL;
	CPpEngineThreadBase *pEngineThread = (CPpEngineThreadBase*)pThread;

	while (pos != NULL)
	{
		pObj = (CCmmOnConnect*)pCmmConfig->GetNext(pos);
		if (pObj != NULL && pObj->GetClassID() == DMCLASSID_CMM_ONCONNECT)
		{
            CLogPrint::LogFormatString(g_pLogTracePrint, XLOGLEVEL_TRACE, _T("RunProcedure(%s)"), pObj->m_strText.GetString());

			pEngineThread->RunProcedure(pObj->m_strText, NULL, TRUE);
		}
	}
}
/*
BOOL GetSubNetMask(BYTE &b1, BYTE &b2, BYTE &b3, BYTE &b4)//获取子网掩码
{
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;

	pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );
	unsigned long ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into the ulOutBufLen variable
	//GetAdaptersInfo 可以获得本地计算机的网络信息，从而获得该计算机的子网掩码。
	//该函数在头文件 Iphlpapi.h.（需安装 Platform  SDK）中声明，库文件 Iphlpapi.lib。
	if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS) 
	{
		//GlobalFree (pAdapterInfo);
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
	}

	PIP_ADAPTER_INFO pAdapterInfoOld = pAdapterInfo;

	//获得本地计算机的网络信息函数 
	if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
	{
		pAdapter = pAdapterInfo;

		while (pAdapter) 
		{			
			sscanf(pAdapter->IpAddressList.IpMask.String, "%c.%c.%c.%c", &b1, &b2, &b3, &b4);
			pAdapter = pAdapter->Next;
			//break;
		}
	}
	else
	{
		return FALSE;
	}

	free(pAdapterInfoOld);

	return TRUE;
}
*/

