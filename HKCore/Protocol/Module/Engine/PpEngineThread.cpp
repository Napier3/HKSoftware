// ..\Module\Engine\CmmChannel\PpEngineThread.cpp : 实现文件
//

#include "stdafx.h"
#include "PpEngineThread.h"
#include "PpEngineBaseApp.h"
#include "..\XLanguageResourcePp.h"

#ifndef _PP_DEV_MODE_
#include "..\ProcotolProject\PpCfgOptrsMngr.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPpEngineThread

IMPLEMENT_DYNCREATE(CPpEngineThread, CWinThread)

CPpEngineThread::CPpEngineThread()
{
	m_bInOnChannelReceive = FALSE;
	m_dwReConnectState = 0;
	m_pDeviceRef = NULL;         //设备点表数据管理对象
	m_pTemplate = NULL;  //规约模板对象
	m_pDeviceCmmConfigRef = NULL;  //设备通讯配置对象
	m_pDeviceCmmChannel = NULL;    //关联的设备通讯对象
	m_pUsingChannel = NULL;
	m_pPkgSendMngr = NULL;  //报文帧发送管理对象
	m_pDevcieModel = NULL;

	m_pDeviceCmmChannel = new CDeviceCmmChannel();
	m_pPkgSendMngr = new CPpPackageSendMngr();

	//Engine Thread相关的处理
	m_pProcedureRunThread = NULL;
	m_bExitEngineThread = FALSE;
	m_bHasPostWmquit = FALSE;

	m_nThreadExitState = PPEXIT_STATE_NONE;
	m_bDeleteEngineDataInExit = TRUE;

	m_bKillProcedure = FALSE;
	m_bViewProcedure = FALSE;

	m_nPkgRcvCounter = 0;
	m_bIsInThreadParse = FALSE;
}

CPpEngineThread::~CPpEngineThread()
{
	
}

void CPpEngineThread::PostConnectDeviceMsg()
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

BOOL CPpEngineThread::IsConnecting()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return FALSE;
	}

	return m_pDeviceCmmChannel->IsConnecting();
}

void CPpEngineThread::WaitDeviceConnectFinished()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return;
	}

	CTickCount32 oTick;
	long nIndex = 0;

	while (TRUE)
	{
		if (!IsConnecting() || nIndex > 200)
		{
			break;
		}

		oTick.DoEvents(50);
		nIndex++;
	}
}

BOOL CPpEngineThread::IsConnectSuccessful()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return FALSE;
	}

	return m_pDeviceCmmChannel->IsConnectSuccessful();
}

void CPpEngineThread::OnDeviceConnectFinish(BOOL bSucc)
{
	if (m_pEngineData != NULL)
	{
		m_pEngineData->OnDeviceConnectFinish(bSucc);
	}
}

void CPpEngineThread::OnCmmChannelClose(CCmmChannel *pChannel)
{
	if (pChannel != m_pUsingChannel)
	{
		return;
	}

	m_pUsingChannel = NULL;

	while (m_bIsInThreadParse)
	{
		Sleep(1);
	}
}

BOOL CPpEngineThread::InitInstance()
{
	//m_oReceiveBuffer.SetBufferLength(1048576);  //1024*1024  1M

	//准备连接设备
	ASSERT (m_pDeviceCmmConfigRef != NULL);

	// 连接设备之前将设备通讯配置数据复制到模板通讯配置数据中

	if (m_pDeviceCmmConfigRef != NULL)
	{
		CopyDeviceCmmConfig(m_pTemplate->m_pCmmConfig, m_pDeviceCmmConfigRef);
	}

	m_pDeviceCmmChannel->m_pThread = this;

	return TRUE;
}

//由于运行脚本与主线程冲突，不能单独结束线程，要结束线程需要在主线程设置时钟结束。
void CPpEngineThread::ExitEngineThread()     
{
	if (m_bExitEngineThread)
	{
		return;
	}

	if (PPEXIT_STATE_EXITPRUN != m_nThreadExitState)
	{
		m_nThreadExitState = PPEXIT_STATE_NORMAL;
	}

	//DisConnectDevice();
	PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
}

BOOL CPpEngineThread::IsThreadExitExtern()    
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

BOOL CPpEngineThread::IsThreadExit()    
{
	if (m_pProcedureRunThread != NULL)  
	{
		return FALSE;
	}

	if (!m_pDeviceCmmChannel->IsAllCmmChannelExit())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpEngineThread::IsRunProduceThreadExit()
{
	if (m_pProcedureRunThread != NULL)  
	{
		//Sleep(50);
		return FALSE;
	}

	return TRUE;
}

int CPpEngineThread::ExitInstance()
{
	m_listReceivePackage.DeleteAll();
	m_listRunProcedure.DeleteAll();
	m_listProcedureToRun.DeleteAll();

	delete m_pDeviceCmmChannel;
	m_pDeviceCmmChannel = NULL;

	delete m_pPkgSendMngr;
	m_pPkgSendMngr = NULL;

	int nRet = CWinThread::ExitInstance();

	//删除对应的EngineData
	CPpEngineBaseApp *pApp = (CPpEngineBaseApp*)AfxGetApp();
	m_pEngineData->m_pEngineThread = NULL;

	if (m_bDeleteEngineDataInExit)
	{
		//pApp->DeleteEngineData(m_pEngineData);
		m_pEngineData = NULL;
	}

	return nRet;
}

BEGIN_MESSAGE_MAP(CPpEngineThread, CWinThread)
	ON_THREAD_MESSAGE(WM_THREAD_RECEIVE, &CPpEngineThread::OnChannelReceive)
	ON_THREAD_MESSAGE(WM_THREAD_CONNECT, &CPpEngineThread::OnConnectDevice)
	ON_THREAD_MESSAGE(WM_THREAD_CONNECT_FINISHED, &CPpEngineThread::OnConnectDeviceFinished)
	ON_THREAD_MESSAGE(WM_THREAD_CONNECT_FAILED, &CPpEngineThread::OnConnectDeviceFailed)
	ON_THREAD_MESSAGE(WM_THREAD_DISCONNECT, &CPpEngineThread::OnDisConnectDevice)
	ON_THREAD_MESSAGE(WM_EXIT_ENGINE_THREAD, &CPpEngineThread::OnExitEngineThread)
	ON_THREAD_MESSAGE(WM_DELETE_ALL_RECORD_PACKAGE, &CPpEngineThread::OnDeleteAllRecordPackage)
END_MESSAGE_MAP()


// CPpEngineThread 消息处理程序

//添加解析完成的帧对象到临时列表
void CPpEngineThread::AddReceivePackageDetail(CPpPackageDetail *pPkg)
{

}

//模板 加载/卸载
void CPpEngineThread::LoadTemplate(const CString &strTemplageFile)
{

}

void CPpEngineThread::UnLoad()
{

}


//设备连接、断开管理
BOOL CPpEngineThread::ConnectDevice()
{
	m_bExitEngineThread = FALSE;
	ASSERT (m_pDeviceCmmChannel != NULL);
	ASSERT (m_pTemplate != NULL);

	if (m_pDeviceCmmChannel == NULL || m_pTemplate == NULL)
	{
		return FALSE;
	}

	{
		CAutoSimpleLock oLock(CCmmChannel::g_oCmmLogAutoCriticSection);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ConnectDevice：(%s)(%s)"), m_pEngineData->m_strPpTemplateFile, m_pEngineData->m_strPpDeviceFile);
	}
	// 启动线程

	if (m_pProcedureRunThread == NULL)
	{
		//处理断开连接后，重复的数据
		m_pDeviceCmmChannel->DeleteAll();

		m_pProcedureRunThread = AfxBeginThread(ProcedureRunThread,this);
		m_pProcedureRunThread->m_bAutoDelete = TRUE;
		CopyDeviceCmmConfig(m_pTemplate->m_pCmmConfig, m_pDeviceCmmConfigRef);  //??????????????????????
		m_pDeviceCmmChannel->m_dwCommMode = m_pTemplate->GetCommMode();
		m_pDeviceCmmChannel->m_pXPkgFullRcvJdgInterface = m_pTemplate->GetXPkgFullRcvJdgInterface();
		m_pDeviceCmmChannel->ConnectDevice(m_pTemplate->m_pCmmConfig);
		m_pUsingChannel = (CCmmChannel*)m_pDeviceCmmChannel->GetHead();
	}
	else
	{
		m_pDeviceCmmChannel->ConnectDevice(m_pTemplate->m_pCmmConfig, FALSE);
	}

	return TRUE;
}

BOOL CPpEngineThread::CmmChannelConfig()
{
	return FALSE;
}

BOOL CPpEngineThread::UnloadDevice()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return TRUE;
	}

	m_pDeviceCmmChannel->DisConnectDevice();
	m_bExitEngineThread = TRUE;

	return FALSE;
}

BOOL CPpEngineThread::DisConnectDevice()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return TRUE;
	}

	m_pDeviceCmmChannel->DisConnectDevice();
	m_bExitEngineThread = TRUE;

	return FALSE;
}

void PpDeleteUsedPackages(CExBaseList *pList, CPpEngineData *pEngineData)
{
	POS pos = pList->GetHeadPosition();
	POS posPrev = NULL;
	CPpPackageDetail *pPkgDetail = NULL;
	POS posTail = pList->GetTailPosition();

	while (pos != posTail)
	{
		posPrev = pos;
		pPkgDetail = (CPpPackageDetail*)pList->GetNext(pos);

		try
		{
			if (pPkgDetail->CanDelete())
			{
				pList->RemoveAt(posPrev);
				delete pPkgDetail;
			}
		}
		catch (...)
		{
			
		}
		
		
	}
}

//数据接受,关联的m_pChannel对象收到数据后,通知EngineThread对象
void CPpEngineThread::OnReceived(CCmmRcvSndTime *pCmmTime)
{
	if (m_pTemplate == NULL)
	{
		return ;
	}

#ifndef _use_CMemBufferList
	if (m_pUsingChannel->m_nParserBeginPos == m_pUsingChannel->m_pCycleRcvBuffer->GetDataFillBeginPosition())
	{
		return;
	}
#endif

	m_pEngineData->ResetRecvTick();

	//执行收到报文后的过程
	//2019-5-27   lijunqing
	//if (m_pEngineData->m_pTemplate->m_strOnRecvProcedure.GetLength() > 3)
	//{
	//	RunProcedure(m_pEngineData->m_pTemplate->m_strOnRecvProcedure, NULL, FALSE);
	//}

	//为了避免解析、制造使用XVM的冲突，将解析和制造都放到统一的线程中
	//Parse();
// 	CAutoSimpleLock oLock(m_oParsePkgCriticSection);
// 	m_nPkgRcvCounter++;
}

BOOL CPpEngineThread::EnterParse_FromPpRunThread()
{
//	CAutoSimpleLock oLock(m_oParsePkgCriticSection);
	BOOL bNeedRunProcedure = FALSE;//bNeedRunProcedure  2019-5-27
#ifdef _use_CMemBufferList
	Parse_Buff_List();
#else
	Parse(bNeedRunProcedure);
#endif
// 	if (m_nPkgRcvCounter > 0)
// 	{
// 		m_nPkgRcvCounter--;
// 	}

	if (bNeedRunProcedure)
	{//bNeedRunProcedure  2019-5-27
		RunProcedure(m_pEngineData->m_pTemplate->m_strOnRecvProcedure, NULL, FALSE);
	}

#ifndef _PP_DEV_MODE_
	CExBaseList* pList = m_pEngineData->GetListTrigerScriptRun();

	POS pos = pList->GetHeadPosition();
	CPpCfgOptr *pOptr = NULL;

	while (pos != NULL)
	{
		pOptr = (CPpCfgOptr *)pList->GetNext(pos);

		if (pOptr->CanRun())
		{
			m_pEngineData->RunScript(pOptr->m_pPpScript);
			pList->Remove(pOptr);
		}
	}


#endif

	return TRUE;
}

void CPpEngineThread::Parse(BOOL &bNeedRunProcedure)
{
	bNeedRunProcedure = FALSE;
	m_bIsInThreadParse = TRUE;

	if (m_pUsingChannel == NULL)
	{
		m_bIsInThreadParse = FALSE;
		return;
	}

	if (m_pUsingChannel->m_pCycleRcvBuffer == NULL)
	{
		m_bIsInThreadParse = FALSE;
		return;
	}

	PACKAGEBUFFERPOS oBufPos;
	CreateParseBufferPos(oBufPos);

	//没有报文
	if (oBufPos.nBuffer1EndPos <= 0 && oBufPos.nBuffer2EndPos <= 0)
	{
		m_bIsInThreadParse = FALSE;
		return;
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("--------------报文缓冲{%d}----------------"), oBufPos.nBuffer1EndPos);
	CPpPackageDetail *pDetail = NULL;
	long nResult = 0;
	long nTempPos;
	BOOL bResetReceiveBeginPos = FALSE;

	long nBufLength = PpGetLengthFromCurr(oBufPos) ;

	//待解析的报文长度超过128K，代表系统解析速度太慢了，跳过解析此部分
	if (nBufLength >= 131072) //128*1024
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("--------------报文缓冲%d>128K，忽略报文----------------"), nBufLength);
		m_pUsingChannel->OffsetParserBeginPos(nBufLength);
		m_bIsInThreadParse = FALSE;
		return;
	}

	if (oBufPos.nBuffer1BeginPos >= 917504)//896K
	{
		bResetReceiveBeginPos = TRUE;
	}

	if (nBufLength == 0)
	{
		m_bIsInThreadParse = FALSE;
		return;
	}

#ifdef _debug_spy
	CPpEngineBaseApp *pApp = (CPpEngineBaseApp*)AfxGetApp();
	CDebugData *pDebugData = NULL;
#endif

	long nErrorBeginPos = -1;
	long nErrorLength = 0;

	while (TRUE)
	{
		//初始化当前解析桢解析的长度
		m_nCurrPkgLen = 0;  
		nTempPos = m_pUsingChannel->m_nParserBeginPos;

#ifdef _debug_spy
		pDebugData = pApp->m_pDebugSpy->Create(0, 0, _T("Before Parse"));
#endif

		pDetail = new CPpPackageDetail(m_pUsingChannel);
		pDetail->SetParent(m_pEngineData);
		pDetail->m_pPkgBufPos = &oBufPos;
		nResult = m_pTemplate->Parse(oBufPos, pDetail);

#ifdef _debug_spy
		pDebugData->GetEndTime();
#endif

		//解析之后的结果有三种
		if (!IsPpParseError(nResult))
		{//解析成功
			if (IsPpParseHasPakage(nResult))
			{//解析包含完整的报文，此处的目的在于考虑串口，一次性没有接受全全部的报文
				//偏移报文的长度
				m_pUsingChannel->m_nParserBeginPos = oBufPos.nIndex;

				//添加到报文管理对象
				DWORD dwBegin = GetTickCount();

				pDetail->SetBeginTime();
				//???????????????????????????????????
				//20170309：去掉包问时间
				//InitPackageTime(pDetail, nTempPos); 
				m_listReceivePackage.AddTail(pDetail);

				if (g_bLogPackageInfor)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("解析帧：[%s][%s]    (%d-%d ; %d-%d  : nIndex=%d)"), pDetail->m_strName, pDetail->m_strID
						, oBufPos.nBuffer1BeginPos, oBufPos.nBuffer1EndPos, oBufPos.nBuffer2BeginPos, oBufPos.nBuffer2EndPos, oBufPos.nIndex);
				}

				//规约录波，记录需要记录的规约帧
				m_pEngineData->m_pPpRecordMngr->AddPackage(pDetail);
				//调用外部执行的过程脚本
				m_pEngineData->InitTrigerScriptRun(pDetail);

				//收到报文，执行过程，不管有没有解析完毕，结束解析，先执行过程
				//2019-5-27  lijq
				if (m_pEngineData->CanRunWPackageOnReceive())
				{
					bNeedRunProcedure = TRUE;
					break;
				}
			}
			else
			{//没有包含完整的报文：此处的目的在于考虑串口，一次性没有接受全全部的报文
				if (pDetail != NULL)
				{
					delete pDetail;
					pDetail = NULL;
				}

				break;
			}
		}
		else//解析不成功，则向下偏移，继续解析  //if (!IsPpParseError(nResult))
		{
#ifdef _use_CMemBufferList
			break;
#endif

			if (m_nCurrPkgLen > 0)//此行代码没有意义，系统暂时屏蔽了设置报文长度：20170622
			{//是一个完整的数据桢
				//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"Move Len(%d)", m_nCurrPkgLen);
				LogErrorParse(nErrorBeginPos, nErrorLength, &oBufPos);
				m_pUsingChannel->OffsetParserBeginPos(m_nCurrPkgLen);
				nErrorBeginPos = -1;
				nErrorLength = 0;
			}
			else
			{//没有完整的数据桢
				if (nErrorBeginPos == -1)
				{
					nErrorBeginPos = m_pUsingChannel->m_nParserBeginPos;
					nErrorLength = 1;
				}
				else
				{
					nErrorLength++;
				}

				m_pUsingChannel->OffsetParserBeginPos(1);
			}

			if (pDetail != NULL)
			{
				delete pDetail;
				pDetail = NULL;
			}
		}

		if (! m_pUsingChannel->DataIsEnoughForParse(m_pTemplate->m_nPackageMinLength))
		{
			break;
		}

		CreateParseBufferPos(oBufPos);

		//全部解析完毕，结束解析
		if (PpGetLengthFromCurr(oBufPos) == 0)
		{
			break;
		}
	}

	LogErrorParse(nErrorBeginPos, nErrorLength, &oBufPos);

	//解析执行完毕，再复位填充位置：目的，避免访问第二段数据，提高效率
	//if (oBufPos.nBuffer1BeginPos >= 917504)//896K
	if (bResetReceiveBeginPos)
	{
		m_pUsingChannel->ResetReceiveBeginPos();
	}

	m_bIsInThreadParse = FALSE;
}

#ifdef _use_CMemBufferList
void CPpEngineThread::Parse_Buff_List()
{
	PACKAGEBUFFERPOS oBufPos;
	CreateParseBufferPos(oBufPos);

	//没有报文
	if (oBufPos.nBuffer1EndPos <= 0)
	{
		return;
	}

	//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("--------------报文缓冲{%d}----------------"), oBufPos.nBuffer1EndPos);
	CPpPackageDetail *pDetail = NULL;
	long nResult = 0;

	pDetail = new CPpPackageDetail(m_pUsingChannel);
	pDetail->SetParent(m_pEngineData);
	pDetail->m_pPkgBufPos = &oBufPos;
	nResult = m_pTemplate->Parse(oBufPos, pDetail);

	//解析之后的结果有三种
	if (!IsPpParseError(nResult))
	{//解析成功
		if (IsPpParseHasPakage(nResult))
		{//解析包含完整的报文，此处的目的在于考虑串口，一次性没有接受全全部的报文
			//添加到报文管理对象
			DWORD dwBegin = GetTickCount();

			pDetail->SetBeginTime();
			//???????????????????????????????????
			//20170309：去掉包问时间
			//InitPackageTime(pDetail, nTempPos); 
			m_listReceivePackage.AddTail(pDetail);

			if (g_bLogPackageInfor)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("解析帧：[%s][%s]"), pDetail->m_strName, pDetail->m_strID);
			}

			//规约录波，记录需要记录的规约帧
			m_pEngineData->m_pPpRecordMngr->AddPackage(pDetail);
			//调用外部执行的过程脚本
			m_pEngineData->InitTrigerScriptRun(pDetail);
		}
		else
		{//没有包含完整的报文：此处的目的在于考虑串口，一次性没有接受全全部的报文
			if (pDetail != NULL)
			{
				delete pDetail;
				pDetail = NULL;
			}
		}
	}
	else//解析不成功，则向下偏移，继续解析  //if (!IsPpParseError(nResult))
	{
		LogErrorParse(0, oBufPos.nBuffer1EndPos, &oBufPos);
	
		if (pDetail != NULL)
		{
			delete pDetail;
			pDetail = NULL;
		}
	}
}

#endif

void CPpEngineThread::LogErrorParse(long nBeginPos, long nLength, PACKAGEBUFFERPOS *pBufPos)
{
	if (!g_bLogPackageInfor)
	{
		return;
	}

	if (nBeginPos == -1)
	{
		return;
	}

	CYCLEMEMBUFFERPOS oBufPosError;
	ZeroMemory(&oBufPosError, sizeof(CYCLEMEMBUFFERPOS));

	if (pBufPos == NULL)
	{
		CreateParseBufferPos(oBufPosError, nBeginPos, nLength);
	}
	else
	{
		oBufPosError.nBuf1BeginPos = pBufPos->nBuffer1BeginPos;
		oBufPosError.nBuf1EndPos = pBufPos->nBuffer1EndPos;
		oBufPosError.pBuffer = pBufPos->pBuffer;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourcePpBase::g_sLangTxt_ErrorMessage/*_T("错误报文:(Begin=%d      Len=%d)")*/	, nBeginPos	, nLength);

	CString strMsg;
	LogProtocol(m_pszPpLogProtocol, oBufPosError, strMsg);
	strMsg.Append(_T("\r\n\r\n"));
	CLogPrint::LogString(XLOGLEVEL_TRACE,strMsg);

}

void CPpEngineThread::InitPackageTime(CPpPackageDetail *pPkg, long nBeginPos)
{
#ifndef _use_CMemBufferList
	//////////////////////////////////////////////////////////////////////////
	//记录时间
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

		if (m_pEngineData->m_pPpRecordMngr->IsPackageIDExist(pPkg->m_strID))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>>>%s = %d:%d:%d.%d"), pPkg->m_strID
				, pPkg->m_tm.wHour, pPkg->m_tm.wMinute, pPkg->m_tm.wSecond, pPkg->m_tm.wMilliseconds);
		}
	}
	else
	{
		::GetLocalTime(&pPkg->m_tm);
		pPkg->m_dwTickCount = ::GetTickCount();
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L">>>>Error(%s) = %d:%d:%d.%d", pPkg->m_strID
// 			, pPkg->m_tm.wHour, pPkg->m_tm.wMinute, pPkg->m_tm.wSecond, pPkg->m_tm.wMilliseconds);
	}					
#endif
}

//发送接收处理线程
UINT CPpEngineThread::PkgSendReceiveThread(LPVOID pParam)
{
	return 0;
}


long CPpEngineThread::GetSendTickLong()
{
	return m_pEngineData->GetSendTickLong();
}

long CPpEngineThread::GetRecvTickLong()
{
	return m_pEngineData->GetRecvTickLong();
}

void CPpEngineThread::ResetSendTick()
{
	m_pEngineData->ResetSendTick();
}

void CPpEngineThread::ResetRecvTick()
{
	m_pEngineData->ResetRecvTick();
}

BOOL CPpEngineThread::IsProcedureExist(const CString &strProcedureID)
{
	POS pos = m_listRunProcedure.GetHeadPosition();
	CPpProcedureRun *p = NULL;
	BOOL bProcedureIsRun = FALSE;

	while (pos != NULL)
	{
		p = (CPpProcedureRun*)m_listRunProcedure.GetNext(pos);

		if (p->m_pProcedure->m_strID == strProcedureID)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("+++++++++RunPp:%s %s+++++++++"), p->m_pProcedure->m_strName, p->m_pProcedure->m_strID);
			bProcedureIsRun = TRUE;
		}
	}

	return bProcedureIsRun;
}

//执行过程
BOOL CPpEngineThread::RunProcedure(const CString &strProcedureID, CExBaseList *pInterface, BOOL bIsInit) 
{
	BOOL bRet = TRUE;

	if (pInterface != NULL)
	{
		CString strLog;
		CString strTemp = strProcedureID;

		POS pos = pInterface->GetHeadPosition();
		strLog.Format(_T("COM:RunProcedure(%s)"), strTemp);

		while (pos != NULL)
		{
			CBbVariable *pVariable = (CBbVariable*)pInterface->GetNext(pos);
			strTemp.Format(_T(" [%s=%s]"), pVariable->m_strID, pVariable->m_strValue);
			strLog += strTemp;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Device::RunProcedure: %s"), strLog);
	}

	CPpProcedure *pProcedure = (CPpProcedure*)m_pTemplate->m_pProcedures->FindByID(strProcedureID);

	if (pProcedure == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("-----procedure \"%s\" not exist"), strProcedureID);
		bRet = FALSE;
	}
	else
	{
		CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
		CPpProcedureRun *pRun = new CPpProcedureRun(pProcedure, pInterface, this, bIsInit);
		pRun->InitRunWPackageScpt();
		m_listProcedureToRun.AddTail(pRun);

		bRet = TRUE;
	}

	if (g_pTheEngineApp->m_bDebugMode)
	{
		return TRUE;
	}
	else
	{
		return bRet;
	}
}

void CPpEngineThread::KillProcedure(const CString &strProcedureID, CExBaseList *pInterface)
{
	m_strKillProcedure = strProcedureID;
	m_bKillProcedure = TRUE;
}

void CPpEngineThread::ViewProcedure()
{
	m_bViewProcedure = TRUE;;

}

void CPpEngineThread::AddTempProcedureToRun()
{
	if (m_listProcedureToRun.GetCount() == 0)
	{
		return;
	}

	POS posTo = NULL;
	POS posToPrev = NULL;
	CPpProcedureRun *pTo = NULL;

	//遍历过程临时链表，添加过程（互斥处理）
	CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
	posTo = m_listProcedureToRun.GetHeadPosition();

	while (posTo != NULL)
	{//遍历过程临时链表，添加过程
		posToPrev = posTo;
		pTo =  (CPpProcedureRun*)m_listProcedureToRun.GetNext(posTo);

		if (FindRunningProcedure(pTo->m_pProcedure->m_strID) != NULL)
		{//如果有相同的过程在运行，则不处理
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_ProcessRun/*L"过程\"%s\"已经运行"*/, pTo->m_pProcedure->m_strID);
			delete pTo;
			pTo = NULL;
			continue;
		}

		//不考虑优先级，直接添加到执行列表末尾
		m_listRunProcedure.AddTail(pTo);
		pTo->CopyDataInterfaceToPackage();
	}//end of "遍历过程临时链表，添加过程"

	m_listProcedureToRun.RemoveAll();

	oLock.Free();
}

void CPpEngineThread::LogAllProcedure()
{
	if (!m_bViewProcedure)
	{
		return;
	}

	POS pos = m_listRunProcedure.GetHeadPosition();
	CPpProcedureRun *p = NULL;

	while (pos != NULL)
	{
		p = (CPpProcedureRun*)m_listRunProcedure.GetNext(pos);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RunPp:%s %s"), p->m_pProcedure->m_strName, p->m_pProcedure->m_strID);
	}

#ifdef _use_CMemBufferList
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Buff:read_index=%d  write_index = %d")
		, m_pUsingChannel->m_pCycleRcvBuffer-> Get_read_index()
		, m_pUsingChannel->m_pCycleRcvBuffer-> Get_write_index()	);
#endif

	m_bViewProcedure = FALSE;
}

void CPpEngineThread::KillProcedure()
{
	if (!m_bKillProcedure)
	{
		return;
	}

	POS pos = m_listRunProcedure.GetHeadPosition();
	POS posPrev = NULL;
	CPpProcedureRun *p = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CPpProcedureRun*)m_listRunProcedure.GetNext(pos);

		if (p->m_pProcedure->m_strID == m_strKillProcedure)
		{
			m_listRunProcedure.RemoveAt(posPrev);
			delete p;
			break;
		}
	}

	m_bKillProcedure = FALSE;
}

BOOL CPpEngineThread::ReConnectOnFailed()
{
	if (m_dwReConnectState == 0)
	{
		return FALSE;
	}

	if (m_dwReConnectState == 1)
	{//断开所有连接
		m_dwReConnectState = 2;
		PostThreadMessage(WM_THREAD_CONNECT, NULL, NULL);
	}
	else if (m_dwReConnectState == 4)
	{
		Sleep(500);

		//10秒后重新连接
		if (m_oReConnectTick.GetTickCountLong(FALSE) > 30000)
		{
			m_oReConnectTick.Enter();
			m_dwReConnectState = 2;
			PostThreadMessage(WM_THREAD_CONNECT, NULL, NULL);
		}
	}
	else
	{
		Sleep(500);

		if (m_oReConnectTick.GetTickCountLong(FALSE) > 5000)
		{
			PostThreadMessage(WM_THREAD_CONNECT, NULL, NULL);
		}
	}

	return TRUE;
}

void Pp_DebugParse(CCmmChannel *pUsingChannel)
{
	BYTE byteReceiveBuffer[255];
	BYTE *pTemp = byteReceiveBuffer;
	//10 80 01 00 81 16 10 C9 01 00 CA 16
	*pTemp = 0x10;		pTemp++;
	*pTemp = 0x80;		pTemp++;
	*pTemp = 0x01;		pTemp++;
	*pTemp = 0x00;		pTemp++;
	*pTemp = 0x81;		pTemp++;
	*pTemp = 0x16;		pTemp++;
	*pTemp = 0x10;		pTemp++;
	*pTemp = 0xC9;		pTemp++;
	*pTemp = 0x01;		pTemp++;
	*pTemp = 0x00;		pTemp++;
	*pTemp = 0xCA;		pTemp++;
	*pTemp = 0x16;		pTemp++;
	long dwDataLen = 12;

	pUsingChannel->m_pCycleRcvBuffer->AppendBuffer(byteReceiveBuffer, dwDataLen);
}

//过程处理线程:死循环，不断遍历
UINT CPpEngineThread::ProcedureRunThread(LPVOID pParam)
{
	CPpEngineThread *pEngineThread = (CPpEngineThread*)pParam;
	ASSERT (pEngineThread != NULL);

	CExBaseList *pListRunProcedure = &pEngineThread->m_listRunProcedure;
	POS pos = NULL;
	POS posPrev = NULL;
	CPpProcedureRun *p = NULL;
	BOOL bHasExclusive = FALSE;

	pEngineThread->m_pEngineData->InitTrigerScriptTimerRun();
	BOOL bTest_Pp_DebugParse = FALSE;

	while (TRUE)
	{
// 		if (bTest_Pp_DebugParse)
// 		{
// 			Pp_DebugParse(pEngineThread->m_pUsingChannel);
// 			pEngineThread->EnterParse_FromPpRunThread();
// 		}

		if (pEngineThread->m_bExitEngineThread)
		{//引擎处于关闭状态
			break;
		}

		//还处于重新连接状态
		if (pEngineThread->ReConnectOnFailed())
		{
			pListRunProcedure->DeleteAll();
			continue;
		}

		if (!pEngineThread->IsConnectSuccessful())
		{
			pListRunProcedure->DeleteAll();
			Sleep(50);
			continue;
		}

		bHasExclusive = FALSE;
		pEngineThread->LogAllProcedure();
		pEngineThread->KillProcedure();

		//遍历过程临时链表，添加过程（互斥处理）
		pEngineThread->AddTempProcedureToRun();
		pos = pListRunProcedure->GetHeadPosition();
		PpDeleteUsedPackages(&pEngineThread->m_listReceivePackage, pEngineThread->m_pEngineData);

		//独占过程
		while (pos != NULL)
		{
			if (pEngineThread->m_dwReConnectState != 0)
			{//连接失败，终止执行独占过程
				break;
			}

			if (pEngineThread->m_bExitEngineThread)
			{//引擎处于关闭状态
				break;
			}

			p = (CPpProcedureRun*)pListRunProcedure->GetNext(pos);

			if (p->IsExclusive())
			{
				pEngineThread->EnterParse_FromPpRunThread();

				if( ! p->IsProcedureExit() )
				{
					p->Run();
					bHasExclusive = TRUE;
					break;
				}
			}

			//Sleep(5);
		}//独占过程

		if (pEngineThread->m_bExitEngineThread)
		{//引擎处于关闭状态
			break;
		}

		//如果包含独占线程,继续执行独占线程
		if (bHasExclusive)
		{
			continue;
		}

		//执行报文解析
		pEngineThread->EnterParse_FromPpRunThread();

		pos = pListRunProcedure->GetHeadPosition();

		while (pos != NULL)
		{//遍历运行过程
			posPrev = pos;
			p = (CPpProcedureRun*)pListRunProcedure->GetNext(pos);

			if (p->CanRun())
			{//过程是否可以运行，即进行过程优先级处理
				if (p->IsProcedureExit())
				{
					//结束过程报文抓包   2014-10-13  李俊庆
					pEngineThread->OnProcedureExit(p);

					if (g_bLogEngineDebugInfor)
					{
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_ProcessClose/*L"----------过程\"%s\"结束----------"*/, p->m_pProcedure->m_strID);
					}
					
					//发送过程结束消息
					if (!p->IsInitProcedure())
					{
						pEngineThread->m_pEngineData->OnProcedureEnd(p->m_pProcedure->m_strID, p->m_pProcedure->m_dwRunState, p->m_pProcedure->m_dwRunState);					
					}

					//执行过程结束脚本
					p->m_pProcedure->RunEndScript();

					//过程如果结束，从运行链表中删除
					pListRunProcedure->RemoveAt(posPrev);
					posPrev = pos;
					delete p;
				}
				else
				{
					p->Run();  //执行规约过程
				}
			}
			else
			{//过程优先级计数器增加
				p->IncreasePriorityCounter();
			}

			if (pEngineThread->m_bExitEngineThread)
			{//引擎处于关闭状态
				break;
			}

			//Sleep(5);
		}//end of "遍历运行过程"

		pEngineThread->RecordSendPackage();

		if (pEngineThread->m_bExitEngineThread)
		{//引擎处于关闭状态
			break;
		}

		pEngineThread->m_pEngineData->RunTrigerScript_Timer();
		Sleep(1);  //2018-7-8：处理S帧，提高执行的速度，由Sleep(5)==>>Sleep(1)
	}

	//等待其他的使用部分退出
	DWORD dwTimeLong = 0;
	while (TRUE)
	{
		if (pEngineThread->m_pPkgSendMngr->HasAllSend())
		{
			break;
		}
		else
		{
			Sleep(5);
			dwTimeLong += 5;
		}

		if (dwTimeLong > 5000)
		{
			break;
		}
	}

	pEngineThread->m_pPkgSendMngr->DeleteAll();
	pEngineThread->m_listReceivePackage.DeleteAll();
	pEngineThread->m_listRunProcedure.DeleteAll(); 
	pEngineThread->m_listProcedureToRun.DeleteAll();

	pEngineThread->m_pProcedureRunThread = NULL;
	pEngineThread->m_pUsingChannel = NULL;
	pEngineThread->m_nThreadExitState = PPEXIT_STATE_EXITPRUN; 
	pEngineThread->m_bExitEngineThread = FALSE;
	pEngineThread->m_pEngineData->OnDeviceDisConnectFinish(0);

	return 0;
}

CPpProcedureRun* CPpEngineThread::FindRunningProcedure(const CString &strProcedureID)
{
	POS pos = m_listRunProcedure.GetHeadPosition();
	CPpProcedureRun *p = NULL;
	CPpProcedureRun *pFind = NULL;

	while (pos != NULL)
	{
		p = (CPpProcedureRun*)m_listRunProcedure.GetNext(pos);

		if (p->m_pProcedure->m_strID == strProcedureID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CPpEngineThread::CreateParseBufferPos(PACKAGEBUFFERPOS &oBufPos)
{
	CYCLEMEMBUFFERPOS oCycleBufPos;

	//m_pUsingChannel->GetBufferPos(-1, -1, oCycleBufPos);
	m_pUsingChannel->m_pCycleRcvBuffer->GetBufferPos(m_pUsingChannel->m_nParserBeginPos, -1, oCycleBufPos);
	oBufPos.nBuffer1BeginPos = oCycleBufPos.nBuf1BeginPos;
	oBufPos.nBuffer1EndPos = oCycleBufPos.nBuf1EndPos;
	oBufPos.nBuffer2BeginPos = oCycleBufPos.nBuf2BeginPos;
	oBufPos.nBuffer2EndPos = oCycleBufPos.nBuf2EndPos;
	oBufPos.pBuffer = oCycleBufPos.pBuffer;
	oBufPos.nIndex = oCycleBufPos.nBuf1BeginPos;
}

void CPpEngineThread::CreateParseBufferPos(PACKAGEBUFFERPOS &oBufPos, CCmmRcvSndTime *pCmmTime)
{
	CYCLEMEMBUFFERPOS oCycleBufPos = pCmmTime->m_oCycleBufferPos;

	//m_pUsingChannel->GetBufferPos(m_pUsingChannel->m_nParserBeginPos, -1, oCycleBufPos);
	oBufPos.nBuffer1BeginPos = oCycleBufPos.nBuf1BeginPos;
	oBufPos.nBuffer1EndPos = oCycleBufPos.nBuf1EndPos;
	oBufPos.nBuffer2BeginPos = oCycleBufPos.nBuf2BeginPos;
	oBufPos.nBuffer2EndPos = oCycleBufPos.nBuf2EndPos;
	oBufPos.pBuffer = oCycleBufPos.pBuffer;
	oBufPos.nIndex = oCycleBufPos.nBuf1BeginPos;
}

void CPpEngineThread::CreateParseBufferPos(CYCLEMEMBUFFERPOS &oBufPos,  long nBeginPos, long nLength)
{
// 	CYCLEMEMBUFFERPOS oCycleBufPos;

	m_pUsingChannel->GetBufferPos(nBeginPos, nLength, oBufPos);
// 	oBufPos.nBuffer1BeginPos = oCycleBufPos.nBuf1BeginPos;
// 	oBufPos.nBuffer1EndPos = oCycleBufPos.nBuf1EndPos;
// 	oBufPos.nBuffer2BeginPos = oCycleBufPos.nBuf2BeginPos;
// 	oBufPos.nBuffer2EndPos = oCycleBufPos.nBuf2EndPos;
// 	oBufPos.pBuffer = oCycleBufPos.pBuffer;
// 	oBufPos.nIndex = oCycleBufPos.nBuf1BeginPos;
}

//获取通讯通道
CCmmChannel* CPpEngineThread::GetCmmChannel(const CString &strCmmChannelID)
{
	CCmmChannel *pCmmChannel = NULL;
	pCmmChannel = (CCmmChannel*)m_pDeviceCmmChannel->FindByID(strCmmChannelID);
	return pCmmChannel;
}

CCmmChannel* CPpEngineThread::GetCmmChannel(CPpNode *pNode)
{
	CCmmChannel *pCmmChannel = NULL;

	if (pNode->m_strChannelID.GetLength() > 0)
	{
		pCmmChannel = GetCmmChannel(pNode->m_strChannelID);
	}

	if (pCmmChannel == NULL)
	{
		CPpProcedure *pProcedure = (CPpProcedure*)pNode->GetAncestor(PPCLASSID_PPPROCEDURE);

		pCmmChannel = GetCmmChannel(pProcedure->m_strChannelID);

		if (pCmmChannel != NULL)
		{
			return pCmmChannel;
		}


		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_CommunPathUnExist3/*L"节点\"%s\"定义的通信通道\"%s\"不存在"*/, pProcedure->m_strID, pProcedure->m_strChannelID);

		pCmmChannel = GetCmmChannel(m_pTemplate->m_strDefaultChannel);

		if (pCmmChannel == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_CommunPathUnExist2/*L"模板定义的通信通道\"%s\"不存在"*/, pNode->m_strChannelID);

			//选择第一个
			pCmmChannel =  (CCmmChannel*)m_pDeviceCmmChannel->GetHead();

			if (pCmmChannel == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_CommunPathUnExist/*L"模板定义的通信通道不存在"*/);
			}
		}
	}

	return pCmmChannel;
}

CPpPackageSend* CPpEngineThread::AddPackageSend(CPpProcedureRun *pPpProcedureRun)
{
	ASSERT(m_pPkgSendMngr != NULL);
	if (m_pTemplate == NULL)
	{
		return NULL;
	}

	CCmmChannel *pChannel = GetCmmChannel(pPpProcedureRun->GetCurrNode());
	CPpPackageSend *pPkgSend = m_pPkgSendMngr->AddNew(pPpProcedureRun, pChannel, m_pTemplate->m_nPackageMaxLength);
	pPkgSend->m_strChCmmMode = pPpProcedureRun->m_pProcedure->m_strChCmmMode;  //通讯模式

// 	long nCount = m_pPkgSendMngr->GetCount();
// 	CLogPrint::LogFormatString(g_pLogTracePrint, XLOGLEVEL_TRACE, L"m_pPkgSendMngr(%d)", nCount);

	return pPkgSend;
}

void CPpEngineThread::CopyDeviceCmmConfig(CDeviceCmmConfig *pDes, CDeviceCmmConfig* pSrc)
{
	POS pos = pDes->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pEx = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDes->GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case DMCLASSID_CMM_SERIAL_CONFIG:
			{// 如果是串口数据
				pEx = FindByClassID(nClassID, pSrc);
				if (pEx)
				{
					pEx->CopyOwn(p);
					CCmmSerialConfig *pConfig = (CCmmSerialConfig*)p;
					//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("拷贝串口通讯参数(port=%d)"), pConfig->m_nPortNum);
				}
			}

			break;

		case DMCLASSID_NET_CONFIG:
			{// 如果是网口数据
				CCmmNetConfig *pCmmNetConfigDes = (CCmmNetConfig*)p;
				CCmmNetConfig *pCmmNetConfigSrc = (CCmmNetConfig*)FindByClassID(nClassID, pSrc);
				if (pCmmNetConfigSrc == NULL)
				{
					return;
				}
				POS posEx = pCmmNetConfigDes->GetHeadPosition();
				CExBaseObject *pObj = NULL;
				CExBaseObject *pObjEx = NULL;
				UINT nClassIDEx = 0;
				while (posEx != NULL)
				{
					pObj = pCmmNetConfigDes->GetNext(posEx);
					nClassIDEx = pObj->GetClassID();
					pObjEx = FindByClassID(nClassIDEx, pCmmNetConfigSrc);
					if (pObjEx)
					{
						pObjEx->CopyOwn(pObj);
					}
				}
			}

			break;

		}//end of "switch (nClassID)"
	}//end of "while (pos != NULL)"
}

CExBaseObject* CPpEngineThread::FindByClassID(UINT nClassID, CExBaseList* pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;	

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		if (nClassID == p->GetClassID())
		{
			return p;
		}
	}

	return NULL;
}

BOOL CPpEngineThread::GetDeviceAttribute(const CString &strAttrTag, CString &strAttrValue)
{
	if (m_pDeviceRef == NULL)
	{
		return FALSE;
	}

	return m_pDeviceRef->GetDeviceAttribute(strAttrTag, strAttrValue);
}

BOOL CPpEngineThread::SetDeviceAttribute(const CString &strAttrTag, const CString &strAttrValue)
{
	if (m_pDeviceRef == NULL)
	{
		return FALSE;
	}

	return m_pDeviceRef->SetDeviceAttribute(strAttrTag, strAttrValue);
}

void AFX_MSG_CALL CPpEngineThread::OnChannelReceive(WPARAM wParam, LPARAM lParam)
{
	if (m_pTemplate == NULL)
	{
		return;
	}

 	m_pUsingChannel = (CCmmChannel*)wParam;

// 	CYCLEMEMBUFFERPOS oCycleBufPos;
// 	m_pUsingChannel = (CCmmChannel*)wParam;
// 	m_pUsingChannel->GetReceiveBufferPos(oCycleBufPos);
//	CCmmRcvSndTime *pCmmTime = (CCmmRcvSndTime*)lParam; //接受报文的时间

// 	CString strTime;
// 	strTime.Format(_T("%02d:%02d:%02d.%03d  %d~%d  %d~%d"), pCmmTime->m_tm.wHour, pCmmTime->m_tm.wMinute, pCmmTime->m_tm.wSecond, pCmmTime->m_tm.wMilliseconds
// 		, pCmmTime->m_oCycleBufferPos.nBuf1BeginPos, pCmmTime->m_oCycleBufferPos.nBuf1EndPos
// 		, pCmmTime->m_oCycleBufferPos.nBuf2BeginPos, pCmmTime->m_oCycleBufferPos.nBuf2EndPos);
// 	CLogPrint::LogString(XLOGLEVEL_TRACE, strTime);

	if (m_bInOnChannelReceive)
	{
		return;
	}

	m_bInOnChannelReceive = TRUE;

// 	if (g_bLogPackageInfor)
// 	{
// 		PACKAGEBUFFERPOS oBufPos;
// 		CreateParseBufferPos(oBufPos);
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"++++OnChannelReceive{[%d~%d][%d~%d][%d]}"
// 			, oBufPos.nBuffer1BeginPos, oBufPos.nBuffer1EndPos
// 			, oBufPos.nBuffer2BeginPos, oBufPos.nBuffer2EndPos
// 			, oBufPos.nIndex);
// 	}

	CPpEngineBaseApp *pApp = (CPpEngineBaseApp*)AfxGetApp();

	//将打印报文功能移到通讯线程的OnReceive函数中，从而打印原始接收报文,目前暂时处理了TCPClient通讯方式，其它通讯方式后续有时间修改。
	//if (pApp->GetProtocolSpy())
	//{
	//	CString strTime;
	//	strTime.Format(_T("%02d:%02d:%02d.%03d"), pCmmTime->m_tm.wHour, pCmmTime->m_tm.wMinute, pCmmTime->m_tm.wSecond, pCmmTime->m_tm.wMilliseconds);
	//	LogProtocol(m_pDevice, g_pLogPkgReceivePrint, oCycleBufPos, TRUE, strTime);
	//	//LogProtocol(m_pDevice, g_pLogPkgReceivePrint, pCmmTime->m_oCycleBufferPos, TRUE);
	//}
	//else
	//{
	//}

	//m_pDeviceCmmChannel->m_oCmmRcvSndTimeMngr.DeletePrev(pCmmTime);
	//复位监视起始位置

	m_pUsingChannel->ResetReceiveSpyBeginPos();
	OnReceived(NULL);

	m_bInOnChannelReceive = FALSE;

// 	if (g_bLogPackageInfor)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, L"----OnChannelReceive{[%d~%d][%d~%d][%d]}");
// 	}
}

void AFX_MSG_CALL CPpEngineThread::OnConnectDevice(WPARAM wParam, LPARAM lParam)
{
	if (m_dwReConnectState == 0)
	{
		ConnectDevice();
		return;
	}

	m_oReConnectTick.Enter();
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("OnConnectDevice : StateIndex = %d"), m_dwReConnectState);

	if (m_dwReConnectState == 2)
	{//断开所有连接
		//DisConnectDevice();
		if (m_pDeviceCmmChannel != NULL)
		{
			m_pDeviceCmmChannel->DisConnectDevice();
		}

		m_dwReConnectState = 3;

		return ;
	}

	if (m_dwReConnectState == 3)
	{//判断所有连接是否已经断开，然后开始重新连接
		if (m_pDeviceCmmChannel->IsAllCmmChannelExit())
		{
			m_dwReConnectState = 4;
			//ConnectDevice();

			if (m_pDeviceCmmChannel != NULL)
			{
				m_pDeviceCmmChannel->ConnectDevice(FALSE);
			}
		}

		return ;
	}

	if (m_dwReConnectState == 4)
	{
		if (m_pDeviceCmmChannel->IsConnectSuccessful())
		{
			m_dwReConnectState = 0;
			return ;
		}
	}
}

void AFX_MSG_CALL CPpEngineThread::OnConnectDeviceFinished(WPARAM wParam, LPARAM lParam)
{
	m_dwReConnectState = 0;

	m_pEngineData->ResetRecvTick();   //发送报文计时
	m_pEngineData->ResetSendTick();   //发送报文计时

	if (m_pEngineData != NULL)
	{
		m_pEngineData->OnDeviceConnectFinish(lParam);
	}
}


void AFX_MSG_CALL CPpEngineThread::OnConnectDeviceFailed(WPARAM wParam, LPARAM lParam)
{
	if (m_dwReConnectState == 0)
	{
		m_oReConnectTick.Enter();
		m_dwReConnectState = 1;
		return;
	}
}

void AFX_MSG_CALL CPpEngineThread::OnDisConnectDevice(WPARAM wParam, LPARAM lParam)
{
	UnloadDevice();
}

void AFX_MSG_CALL CPpEngineThread::OnExitEngineThread(WPARAM wParam, LPARAM lParam)
{
	CTickCount32 oTick;

	if (m_nThreadExitState == PPEXIT_STATE_NORMAL)
	{
		//oTick.DoEvents(50);
		m_bExitEngineThread = TRUE;
		PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
		return;
	}

	if (m_nThreadExitState == PPEXIT_STATE_EXITPRUN)
	{
		UnloadDevice();
		//oTick.DoEvents(50);
		PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
		m_nThreadExitState = PPEXIT_STATE_DISCONNECT;
		return;
	}

	if (IsThreadExit())
	{
		m_nThreadExitState = PPEXIT_STATE_EXIT;
		PostThreadMessage(WM_QUIT, 0, 0);
		m_bHasPostWmquit = TRUE;
		AfxGetMainWnd()->PostMessage(WM_DISCONNECT_SUCCESS, (WPARAM)m_pEngineData, (LPARAM)m_pEngineData);
	}
	else
	{
		//oTick.DoEvents(50);
		PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
	}
}

void AFX_MSG_CALL CPpEngineThread::OnDeleteAllRecordPackage(WPARAM wParam, LPARAM lParam)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"OnDeleteAllRecordPackage-delete:%d", ::GetTickCount());
	m_pEngineData->m_pPpRecordMngr->OnDeleteAllRecordPackage();
}

void CPpEngineThread::RecordSendPackage()
{
	CPpPackageSend *pSend = NULL;
	POS pos = m_pEngineData->m_pPpRecordMngr->GetHeadPosition();

	while (pos != NULL)
	{
		pSend = (CPpPackageSend*)m_pEngineData->m_pPpRecordMngr->GetNext(pos);

		if (pSend->HasSended())
		{
			if (pSend->m_pPackageDetail != NULL)
			{
				if (m_pEngineData->m_pPpRecordMngr->IsPackageIDExist(pSend->m_pPackageDetail->m_strID))
				{
					m_pEngineData->m_pPpRecordMngr->AddTail(pSend->m_pPackageDetail);
					pSend->m_pPackageDetail = NULL;
				}		
			}
		}
	}

	m_pPkgSendMngr->DeleteSendPackages();
}


//监视报文
void CPpEngineThread::LogProtocol(char *pszPpLogProtocol, CYCLEMEMBUFFERPOS &oBufPos, CString &strMsg)
{
	PpLogProtocol(pszPpLogProtocol, oBufPos, strMsg);
	return;
// 	long nIndex = 0;
// 	BYTE *pBuffer = oBufPos.pBuffer + oBufPos.nBuf1BeginPos;
// 	BYTE *pEnd = oBufPos.pBuffer + oBufPos.nBuf1EndPos;
// 
// 	while (pBuffer < pEnd)
// 	{
// 		strMsg.AppendFormat(L"%02X ", *pBuffer);
// 		pBuffer++;
// 	}
// 
// 	if (oBufPos.nBuf2EndPos >= 0)
// 	{
// 		pBuffer = oBufPos.pBuffer + oBufPos.nBuf2BeginPos;
// 		pEnd = oBufPos.pBuffer + oBufPos.nBuf2EndPos;
// 
// 		while (pBuffer < pEnd)
// 		{
// 			strMsg.AppendFormat(L"%02X ", *pBuffer);
// 			pBuffer++;
// 		}
// 	}
}

void CPpEngineThread::LogProtocol(CExBaseObject *pDevice, LPVOID pPara, CYCLEMEMBUFFERPOS &oBufPos, BOOL bRecv, const CString &strTime)
{
	if (oBufPos.nBuf1BeginPos < 0 || oBufPos.nBuf1EndPos <= oBufPos.nBuf1BeginPos)
	{
		return ;
	}

	CPpEngineBaseApp *pApp = (CPpEngineBaseApp*)AfxGetApp();

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
// 
// 	CString strMsg;
// 
// 	if (bRecv)
// 	{
// 		strMsg = CXLanguageResourcePpBase::g_sLangTxt_Receive/*_T("接收 ")*/;
// 	}
// 	else
// 	{
// 		strMsg = CXLanguageResourcePpBase::g_sLangTxt_Send/*_T("发送 ")*/;
// 	}
// 
// 	if (strTime.GetLength() > 0)
// 	{
// 		strMsg = strTime + strMsg;
// 	}
// 
// 	LogProtocol(m_pszPpLogProtocol, oBufPos, strMsg);
// 	strMsg.Append(_T("\r\n"));
// 
// 	CLogPrint::LogString(pPara, XLOGLEVEL_TRACE, strMsg);
}

void CPpEngineThread::ExitRunProduceThread()
{
	m_pTemplate = NULL;//设置为NULL，接收到数据时不予理睬。

	CPpProcedureRun *p = NULL;
	POS pos = m_listRunProcedure.GetHeadPosition();
	while (pos != NULL)
	{
		p = (CPpProcedureRun *)m_listRunProcedure.GetNext(pos);
		if (p != NULL)
		{
			p->ExitProcedure();
		}
	}

	m_bExitEngineThread = TRUE;

}

void CPpEngineThread::OnProcedureExit(CPpProcedureRun *pPpProcedureRun)
{
	m_pEngineData->m_pPpRecordMngr->OnProcedureExit(pPpProcedureRun->m_pProcedure->m_strID);
}

void CPpEngineThread::OnProcedureStart(CPpProcedureRun *pPpProcedureRun)
{
	m_pEngineData->m_pPpRecordMngr->OnProcedureStart(pPpProcedureRun->m_pProcedure->m_strID);
}

