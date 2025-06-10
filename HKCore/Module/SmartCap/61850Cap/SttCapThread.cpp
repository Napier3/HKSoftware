#include "stdafx.h"
#include "SttCapThread.h"

CSttCapThread::CSttCapThread(void)
{
	m_bUseParseThread = TRUE;
	m_nSttCapError = 0;
	m_pRecordTestCalThread = NULL;
	m_pAllDeviceRef = NULL;
	m_pSttRcdMemBufferMngr = NULL;
}

CSttCapThread::~CSttCapThread(void)
{

}

long CSttCapThread::OnReceive(BYTE *pRcvBuf, int iLen)
{
	
	return 0;
}

void CSttCapThread::OnSocketIdle(long nMs)
{
	
}

void CSttCapThread::OnClose(int nErrorCode)
{

}

void CSttCapThread::SetCapConfig(PETHER_CAP_CONFIG pConfig, DWORD dwMask)
{
	if( (CAPCFGMASK_USESRCMAC & dwMask) == CAPCFGMASK_USESRCMAC)
	{
		m_oEtherCapConfig.nUseSrcMac = pConfig->nUseSrcMac;
	}

	if( (CAPCFGMASK_SRCMAC & dwMask) == CAPCFGMASK_SRCMAC)
	{
		memcpy(m_oEtherCapConfig.byteSrcMac, pConfig->byteSrcMac, 6);
	}	

	if( (CAPCFGMASK_USEDESTMAC & dwMask) == CAPCFGMASK_USEDESTMAC)
	{
		m_oEtherCapConfig.nUseDestMac = pConfig->nUseDestMac;
	}

	if( (CAPCFGMASK_DESTMAC & dwMask) == CAPCFGMASK_DESTMAC)
	{
		memcpy(m_oEtherCapConfig.byteDestMac, pConfig->byteDestMac, 6);
	}

	if( (CAPCFGMASK_CAPSMV & dwMask) == CAPCFGMASK_CAPSMV)
	{
		m_oEtherCapConfig.nCapSmv = pConfig->nCapSmv;
	}

	if( (CAPCFGMASK_CAPGOOSE & dwMask) == CAPCFGMASK_CAPGOOSE)
	{
		m_oEtherCapConfig.nCapGoose = pConfig->nCapGoose;
	}

	if( (CAPCFGMASK_CARDINDEX & dwMask) == CAPCFGMASK_CARDINDEX)
	{
		m_oEtherCapConfig.nNetCardIndex = pConfig->nNetCardIndex;
	}
}

DWORD CSttCapThread::CreateCaptureThread()
{
	//m_pCaptureThread = AfxBeginThread(CaptureThread,this); 

	//m_pCaptureThread->m_bAutoDelete = TRUE; //移动到CXSttCap_61850::ConnectServer中

	if (m_bUseParseThread)
	{
#ifndef _PSX_IDE_QT_
		m_pParseThread = AfxBeginThread(ParseThread,this);
		m_pParseThread->m_bAutoDelete = TRUE;
#else
		m_pParseThread = new CWinThread(ParseThread,this);
		m_pParseThread->ResumeThread();
		m_pParseThread->m_bAutoDelete = FALSE;
#endif
	}

	return 0;
}

void CSttCapThread::ExitCapture()
{
#ifndef _PSX_IDE_QT_
#else
	if (m_pParseThread != NULL)
	{
		m_bExitCapture = TRUE; //
		
		while (m_pParseThread != NULL)
		{
			Sleep(10);
		}
	}
#endif
}

UINT CSttCapThread::CaptureThread(LPVOID pParam)
{
	CSttCapThread* pThis = (CSttCapThread*)pParam;

	//adhandle后不调用pcap_loop，而用下面的方法：
	while(TRUE)
	{
		if (pThis->m_bExitCapture)
		{
			break;
		}

		long res = 0;

		if(res <= 0)
		{
			Sleep(1);
			//continue;
		}
		else
		{

		}

	}

	pThis->m_pCaptureThread = NULL;

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("监视线程（%s）结束"), pThis->m_strName.GetString());

	return 0;
}

UINT ParseThread(LPVOID pParam)
{
	CSttCapThread *pThis = (CSttCapThread*)pParam;
	CTickCount32 oTick;
	CXCapPkgBufferMngrInterface *pSttRcdMemBufferMngr = pThis->m_pSttRcdMemBufferMngr;

	while (TRUE)
	{
		if (pThis->m_bExitCapture)
		{
			break;
		}

		if (! g_bSmartCap_RecordNow)
		{
			Sleep(5);
			continue;
		}

		g_bIsParsingPkg = TRUE;
		//2020-07-17  lijunqing 在此进行分帧，避免堵塞底层
		pSttRcdMemBufferMngr->TransCapPkg();

		if (pThis->MemBufferMngrParse() > 0)
		{
			//发送解析消息
            pThis->RecordTestCalValues();
		}
		else
		{
			Sleep(1);
		}

		//2020-06-27 更新链接状态
		if (oTick.GetTickCountLong(FALSE) >= 2000)
		{
			oTick.Enter();
			pThis->UpdateDeviceLinkState();
		}

		g_bIsParsingPkg = FALSE;
	}

	pThis->m_pParseThread = NULL;

	return 0;
}

void CSttCapThread::UpdateDeviceLinkState()
{
	if (m_pAllDeviceRef == NULL)
	{
		return;
	}

	m_pAllDeviceRef->UpdateDeviceLinkState();
}

extern BOOL g_bSmartCap_RecordNow; 
extern long g_nRecordTestCalState;

void CSttCapThread::RecordTestCalValues()
{
	if (m_pRecordTestCalThread == NULL)
	{
		return;
	}

	//zhouhj 2023.9.20 退出录波界面后,不再进行录波
	if (!g_bSmartCap_RecordNow)
	{
		return;
	}

	if (g_nRecordTestCalState)
	{
		return;
	}

	m_pRecordTestCalThread->PostThreadMessage(WM_BEGIN_CALVALUES/*WM_USER + 1018*/, 1, 1);
}

