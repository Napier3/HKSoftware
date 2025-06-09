// ../Module/Engine/CmmChannel/PpChnTestThread.cpp : 实现文件
//

#include "stdafx.h"
#include "PpChnTestThread.h"
#include "PpEngineBaseApp.h"
#include "../XLanguageResourcePp.h"

CString g_strChnTestCmd_Serial    = _T("port-test-serial");
CString g_strChnTestCmd_UdpClient = _T("port-test-udp-client");
CString g_strChnTestCmd_UdpServer = _T("port-test-udp-server");
CString g_strChnTestCmd_TcpClient = _T("port-test-tcp-client");
CString g_strChnTestCmd_TcpServer = _T("port-test-tcp-server");
CString g_strChnTestCmd_Exit      = _T("port-test-exit");

CString g_strChnTestPackageID     = _T("ChnTestPackage");


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CChnTestThreadWnd, CWnd)

CChnTestThreadWnd::CChnTestThreadWnd()
{

}

CChnTestThreadWnd::~CChnTestThreadWnd()
{
}


BEGIN_MESSAGE_MAP(CChnTestThreadWnd, CWnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()


BOOL CChnTestThreadWnd::CreateTestControlWnd()
{
	CreateEx(0, AfxRegisterWndClass(0), _T("_Test_Ctrl_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
	return TRUE;
}


void CChnTestThreadWnd::OnTimer(UINT_PTR nIDEvent)
{
	m_pPpChnTestThread->OnTimer(nIDEvent, 0);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CPpChnTestThread, CWinThread)

CPpChnTestThread::CPpChnTestThread()
{
	m_pDeviceCmmConfig = NULL;  //设备通讯配置对象
	m_pDeviceCmmChannel = NULL;    //关联的设备通讯对象
	m_pPkgSendMngr = NULL;  //报文帧发送管理对象

	m_pDeviceCmmChannel = new CDeviceCmmChannel();
	m_pPkgSendMngr      = new CPpPackageSendMngr();
//	m_pPpRecordMngr     = new  CPpRecordMngr();

	m_bHasPostWmquit = FALSE;

	m_nThreadExitState = PPEXIT_STATE_NONE;
	m_bDeleteEngineDataInExit = TRUE;
	m_bExitEngineThread = FALSE;
	m_pPoDeviceProcedureInterface = NULL;

	//记录所报文
	//m_pPpRecordMngr->RecordPackage(_T(""));
	m_bHasPostFinishMsg = FALSE;
	m_pUsingChannel = NULL;
	m_pChnTestThreadWnd = new CChnTestThreadWnd();
	m_pChnTestThreadWnd->m_pPpChnTestThread = this;
	m_pChnTestThreadWnd->CreateTestControlWnd();
}

CPpChnTestThread::~CPpChnTestThread()
{
	m_pChnTestThreadWnd->DestroyWindow();
	delete m_pChnTestThreadWnd;
}



// CPpChnTestThread
void CPpChnTestThread::PostConnectDeviceMsg()
{
	if (IsConnecting())
	{
		return;
	}

	if (IsConnectSuccessful())
	{
		return;
	}

	PostThreadMessage(WM_THREAD_CONNECT, NULL, NULL);
}

BOOL CPpChnTestThread::IsConnecting()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return FALSE;
	}

	return m_pDeviceCmmChannel->IsConnecting();
}

BOOL CPpChnTestThread::IsConnectSuccessful()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return FALSE;
	}

	return m_pDeviceCmmChannel->IsConnectSuccessful();
}

void CPpChnTestThread::OnDeviceConnectFinish(BOOL bSucc)
{
	//发送报文
}

void CPpChnTestThread::ChnTest(const CString &strChnTestID, CDeviceCmmConfig *pDeviceCmmConfig, long nMaxTimeLong)
{
	m_pDeviceCmmConfig = pDeviceCmmConfig;
	m_strChnTestID = strChnTestID;
	m_nMaxTestTimeLong = nMaxTimeLong;
	
	if (m_pDeviceCmmChannel->IsAllCmmChannelExit())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("    +++++++++++Begin Port Test: %s"), strChnTestID);
		ChnTest();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_LasterTestUnFinsh/*_T("    +++++++++++上次端口测试没结束: %s")*/, strChnTestID);
		m_pDeviceCmmChannel->DisConnectDevice();
		m_pChnTestThreadWnd->SetTestTimer(m_nChnTestTimerID, 200);
	}
}


void CPpChnTestThread::ChnTest()
{
	ASSERT (m_pPpRecordMngr != NULL);
	m_pPpRecordMngr->RecordPackage(g_strChnTestPackageID);
	m_bHasPostFinishMsg = FALSE;
	m_nChnTestTimeCount = 0;

	//启动定时时钟
	m_nChnTestOverTimerID = 1039;
	m_pChnTestThreadWnd->SetTestTimer(m_nChnTestOverTimerID, 1000);

	m_pDeviceCmmChannel->m_pThread = this;
	m_pDeviceCmmChannel->ConnectDevice(m_pDeviceCmmConfig);
}

void CPpChnTestThread::OnTimer(UINT nIDEvent, LPARAM param)
{
	CLogPrint::LogString(XLOGLEVEL_ERROR, _T("CPpChnTestThread::OnTimer"));
	long n = 0;

	if (m_nChnTestTimerID == nIDEvent)
	{
		if (m_pDeviceCmmChannel->IsAllCmmChannelExit())
		{
			m_pChnTestThreadWnd->KillTestTimer(m_nChnTestTimerID);
			ChnTest();
		}

		return;
	}

	if (nIDEvent == m_nChnTestOverTimerID)
	{
		m_nChnTestTimeCount += 1;

		//发送完成消息
		if (m_nChnTestTimeCount >= m_nMaxTestTimeLong)
		{
			m_pChnTestThreadWnd->KillTestTimer(m_nChnTestOverTimerID);

			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CPpChnTestThread::Oerver Time"));

			if (!m_bHasPostFinishMsg)
			{
				m_bHasPostFinishMsg = TRUE;
				m_pPoDeviceProcedureInterface->OnProcedureEnd(m_strChnTestID, 3, 3);
			}
		}

		return;
	}
}

BOOL CPpChnTestThread::InitInstance()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CPpChnTestThread::InitInstance"));

	m_pDeviceCmmChannel->m_pThread = this;

	return TRUE;
}

//由于运行脚本与主线程冲突，不能单独结束线程，要结束线程需要在主线程设置时钟结束。
void CPpChnTestThread::ExitEngineThread()     
{
	m_nThreadExitState = PPEXIT_STATE_NORMAL;
	PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
}

BOOL CPpChnTestThread::IsThreadExitExtern()    
{
	if (IsThreadExit())
	{
		return TRUE;
	}

	if (!m_bHasPostWmquit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpChnTestThread::IsThreadExit()    
{
	if (!m_pDeviceCmmChannel->IsAllCmmChannelExit())
	{
		return FALSE;
	}

	return TRUE;
}

int CPpChnTestThread::ExitInstance()
{
	m_listReceivePackage.DeleteAll();

	delete m_pDeviceCmmChannel;
	m_pDeviceCmmChannel = NULL;

	delete m_pPkgSendMngr;
	m_pPkgSendMngr = NULL;

	int nRet = CWinThread::ExitInstance();

	return nRet;
}

BEGIN_MESSAGE_MAP(CPpChnTestThread, CWinThread)
	ON_THREAD_MESSAGE(WM_THREAD_RECEIVE, &CPpChnTestThread::OnChannelReceive)
	ON_THREAD_MESSAGE(WM_EXIT_ENGINE_THREAD, &CPpChnTestThread::OnExitEngineThread)
	ON_THREAD_MESSAGE(WM_THREAD_CONNECT_FINISHED, &CPpChnTestThread::OnConnectDeviceFinished)
	ON_THREAD_MESSAGE(WM_DELETE_ALL_RECORD_PACKAGE, &CPpChnTestThread::OnDeleteAllRecordPackage)
END_MESSAGE_MAP()

//设备连接、断开管理
BOOL CPpChnTestThread::ConnectDevice()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CPpChnTestThread::ConnectDevice"));

	ASSERT (m_pDeviceCmmChannel != NULL);

	if (m_pDeviceCmmChannel == NULL)
	{
		return FALSE;
	}

	// 启动线程
	m_pDeviceCmmChannel->ConnectDevice(m_pDeviceCmmConfig);

	return TRUE;
}


void AFX_MSG_CALL CPpChnTestThread::OnConnectDeviceFinished(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CPpChnTestThread::OnConnectDeviceFinished"));
	//连接完成，发送报文

	CPpPackageSend *pSend = (CPpPackageSend*)m_pPkgSendMngr->GetHead();

	if (pSend == NULL)
	{
		m_pPoDeviceProcedureInterface->OnProcedureEnd(m_strChnTestID, 3, 3);
	}
	else
	{
		m_pUsingChannel = (CCmmChannel *)m_pDeviceCmmChannel->GetHead();
		m_pUsingChannel->Send(pSend);
	}
}

BOOL CPpChnTestThread::DisConnectDevice()
{
	ASSERT (m_pPpRecordMngr != NULL);
	m_pPpRecordMngr->UnRecordPackage(g_strChnTestPackageID);

	if (m_pDeviceCmmChannel == NULL)
	{
		return TRUE;
	}

	m_pChnTestThreadWnd->KillTestTimer(m_nChnTestOverTimerID);
	CTickCount32 oTickCount;
	m_pDeviceCmmChannel->DisConnectDevice();

	while (TRUE)
	{
		if (IsThreadExit())
		{
			break;
		}

		if (oTickCount.GetTickCountLong(FALSE) > 500)
		{
			break;
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ChannelTest/*_T("通道测试：关闭测试通道用时%d")*/, oTickCount.GetTickCountLong(FALSE));

	return TRUE;
}

//数据接受,关联的m_pChannel对象收到数据后,通知EngineThread对象
void CPpChnTestThread::OnReceived(CCmmRcvSndTime *pCmmTime)
{
// 	PACKAGEBUFFERPOS oBufPos;
// 	CreateParseBufferPos(oBufPos);
	CPpPackageDetail *pDetail = new CPpPackageDetail(m_pUsingChannel);
	long nResult = 0;
	long nTempPos;

	//初始化当前解析桢解析的长度
	nTempPos = m_pUsingChannel->m_nParserBeginPos;
	
	pDetail->m_strName = _T("接收报文");
	pDetail->m_strID  = g_strChnTestPackageID;

	//规约录波，记录需要记录的规约帧
	CDvmData *pData = m_pPpRecordMngr->AddPackage(pDetail);

#ifdef _DVM_VALUE_USE_CHAR_
	//ASSERT(FALSE);
	//PpLogProtocol(pCmmTime->m_oCycleBufferPos, pData->m_strValue);
#else
	//PpLogProtocol(pCmmTime->m_oCycleBufferPos, pData->m_strValue);
#endif
}

void CPpChnTestThread::LogErrorParse(long nBeginPos, long nLength)
{
	if (nBeginPos != -1)
	{
		CYCLEMEMBUFFERPOS oBufPosError;
		CreateParseBufferPos(oBufPosError, nBeginPos, nLength);

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ErrorMessage/*_T("错误报文:(Begin=%d      Len=%d)")*/	, nBeginPos	, nLength);
	
		CString strMsg;
		LogProtocol(oBufPosError, strMsg);
		strMsg.Append(_T("\r\n\r\n"));
		CLogPrint::LogString(XLOGLEVEL_TRACE,strMsg);
	}
}

void CPpChnTestThread::InitPackageTime(CPpPackageDetail *pPkg, long nBeginPos)
{
#ifndef _use_CMemBufferList
	long nTemp = nBeginPos + 1;
	if (nTemp > m_pUsingChannel->m_pCycleRcvBuffer->GetBufferLength())
	{
		nTemp = 0;
	}

	CCmmRcvSndTime *pTm = m_pDeviceCmmChannel->m_oCmmRcvSndTimeMngr.FindTimeByPos(nTemp);

	if (pTm != NULL)
	{
		pPkg->m_tm = pTm->m_tm;
		pPkg->m_dwTickCount = pTm->m_dwTickCount;

// 		if (m_pPpRecordMngr->IsPackageIDExist(pPkg->m_strID))
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L">>>>%s = %d:%d:%d.%d", pPkg->m_strID
// 				, pPkg->m_tm.wHour, pPkg->m_tm.wMinute, pPkg->m_tm.wSecond, pPkg->m_tm.wMilliseconds);
// 		}
	}
	else
	{
		::GetLocalTime(&pPkg->m_tm);
		pPkg->m_dwTickCount = ::GetTickCount();
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L">>>>Error(%s) = %d:%d:%d.%d", pPkg->m_strID
			, pPkg->m_tm.wHour, pPkg->m_tm.wMinute, pPkg->m_tm.wSecond, pPkg->m_tm.wMilliseconds);
	}					
#endif
}

void CPpChnTestThread::CreateParseBufferPos(PACKAGEBUFFERPOS &oBufPos)
{
	CYCLEMEMBUFFERPOS oCycleBufPos;

	m_pUsingChannel->GetBufferPos(-1, -1, oCycleBufPos);
	oBufPos.nBuffer1BeginPos = oCycleBufPos.nBuf1BeginPos;
	oBufPos.nBuffer1EndPos = oCycleBufPos.nBuf1EndPos;
	oBufPos.nBuffer2BeginPos = oCycleBufPos.nBuf2BeginPos;
	oBufPos.nBuffer2EndPos = oCycleBufPos.nBuf2EndPos;
	oBufPos.pBuffer = oCycleBufPos.pBuffer;
	oBufPos.nIndex = oCycleBufPos.nBuf1BeginPos;
}

void CPpChnTestThread::CreateParseBufferPos(CYCLEMEMBUFFERPOS &oBufPos,  long nBeginPos, long nLength)
{
	m_pUsingChannel->GetBufferPos(nBeginPos, nLength, oBufPos);
}

//获取通讯通道
CCmmChannel* CPpChnTestThread::GetCmmChannel(const CString &strCmmChannelID)
{
	CCmmChannel *pCmmChannel = NULL;
	pCmmChannel = (CCmmChannel*)m_pDeviceCmmChannel->FindByID(strCmmChannelID);
	return pCmmChannel;
}

CPpPackageSend* CPpChnTestThread::AddPackageSend()
{
	ASSERT(m_pPkgSendMngr != NULL);

	CPpPackageSend *pPkgSend = m_pPkgSendMngr->AddNew(NULL, m_pUsingChannel, 255);

	return pPkgSend;
}

void CPpChnTestThread::DeleteAllPackageSend()
{
	ASSERT(m_pPkgSendMngr != NULL);

	m_pPkgSendMngr->DeleteAll();
}

void AFX_MSG_CALL CPpChnTestThread::OnChannelReceive(WPARAM wParam, LPARAM lParam)
{
	CPpEngineBaseApp *pApp = g_pTheEngineApp;
	CYCLEMEMBUFFERPOS oCycleBufPos;
	m_pUsingChannel = (CCmmChannel*)wParam;
	m_pUsingChannel->GetReceiveBufferPos(oCycleBufPos);
	CCmmRcvSndTime *pCmmTime = (CCmmRcvSndTime*)lParam; //接受报文的时间

	//将打印报文功能移到通讯线程的OnReceive函数中，从而打印原始接收报文,目前暂时处理了TCPClient通讯方式，其它通讯方式后续有时间修改。
	//if (pApp->GetProtocolSpy())
	//{
	//	CString strTime;
	//	strTime.Format(_T("%02d:%02d:%02d.%03d"), pCmmTime->m_tm.wHour, pCmmTime->m_tm.wMinute, pCmmTime->m_tm.wSecond, pCmmTime->m_tm.wMilliseconds);
	//	LogProtocol(NULL, g_pLogPkgReceivePrint, oCycleBufPos, TRUE, strTime);
	//}
	//else
	//{
	//}

	m_pDeviceCmmChannel->m_oCmmRcvSndTimeMngr.DeletePrev(pCmmTime);
	
	//复位监视起始位置
	m_pUsingChannel->ResetReceiveSpyBeginPos();

	OnReceived(pCmmTime);

	//发送结束消息
	m_pChnTestThreadWnd->KillTestTimer(m_nChnTestOverTimerID);

	if (!m_bHasPostFinishMsg)
	{
		m_bHasPostFinishMsg = TRUE;
		m_pPoDeviceProcedureInterface->OnProcedureEnd(m_strChnTestID, 3, 3);
	}
}

void AFX_MSG_CALL CPpChnTestThread::OnExitEngineThread(WPARAM wParam, LPARAM lParam)
{
	if (m_nThreadExitState == PPEXIT_STATE_NORMAL)
	{
		m_nThreadExitState = PPEXIT_STATE_EXITPRUN;
		m_bExitEngineThread = TRUE;
		PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
		return;
	}

	if (m_nThreadExitState == PPEXIT_STATE_EXITPRUN)
	{
		DisConnectDevice();
		PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
		m_nThreadExitState = PPEXIT_STATE_DISCONNECT;
		return;
	}

	if (IsThreadExit())
	{
		m_nThreadExitState = PPEXIT_STATE_EXIT;
		PostThreadMessage(WM_QUIT, 0, 0);
		m_bHasPostWmquit = TRUE;
	}
	else
	{
		PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
	}
}

void AFX_MSG_CALL CPpChnTestThread::OnDeleteAllRecordPackage(WPARAM wParam, LPARAM lParam)
{
	m_pPpRecordMngr->OnDeleteAllRecordPackage();
}

void CPpChnTestThread::RecordSendPackage()
{
	return;
}

//监视报文
void CPpChnTestThread::LogProtocol(CYCLEMEMBUFFERPOS &oBufPos, CString &strMsg)
{
	long nIndex = 0;
	BYTE *pBuffer = oBufPos.pBuffer + oBufPos.nBuf1BeginPos;
	BYTE *pEnd = oBufPos.pBuffer + oBufPos.nBuf1EndPos;

	while (pBuffer < pEnd)
	{
		strMsg.AppendFormat(_T("%02X "), *pBuffer);
		pBuffer++;
	}

	if (oBufPos.nBuf2EndPos >= 0)
	{
		pBuffer = oBufPos.pBuffer + oBufPos.nBuf2BeginPos;
		pEnd = oBufPos.pBuffer + oBufPos.nBuf2EndPos;

		while (pBuffer < pEnd)
		{
			strMsg.AppendFormat(_T("%02X "), *pBuffer);
			pBuffer++;
		}
	}
}

void CPpChnTestThread::LogProtocol(CExBaseObject *pDevice, LPVOID pPara, CYCLEMEMBUFFERPOS &oBufPos, BOOL bRecv, const CString &strTime)
{
	if (oBufPos.nBuf1BeginPos < 0 || oBufPos.nBuf1EndPos <= oBufPos.nBuf1BeginPos)
	{
		return ;
	}

	CPpEngineBaseApp *pApp = g_pTheEngineApp;

	if (pApp->IsExitEngineThread())
	{
		return;
	}

	if (! pApp->GetProtocolSpy())
	{
		return;
	}

	CDvmDevice *pLogDevice = pApp->GetCurrSpyDevice();

	//监视当前设备的规约报文
	if (pLogDevice != NULL)
	{
		if (pDevice != pLogDevice)
		{
			return;
		}
	}

	//2020-03-26
	CXPpPkgLogTool::AddPpPkgLog(oBufPos, bRecv);
	return;
/*
	CString strMsg;

	if (bRecv)
	{
		strMsg = _T("<< ");
	}
	else
	{
		strMsg = _T(">> ");
	}

	if (strTime.GetLength() > 0)
	{
		strMsg = strTime + strMsg;
	}

	LogProtocol(oBufPos, strMsg);

	strMsg.Append(_T("\r\n"));

	CLogPrint::LogString(pPara, XLOGLEVEL_TRACE, strMsg);
*/
}
