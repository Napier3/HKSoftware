// ..\Module\Engine\CmmChannel\PpEngineThread.cpp : ʵ���ļ�
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
	m_pDeviceRef = NULL;         //�豸������ݹ������
	m_pTemplate = NULL;  //��Լģ�����
	m_pDeviceCmmConfigRef = NULL;  //�豸ͨѶ���ö���
	m_pDeviceCmmChannel = NULL;    //�������豸ͨѶ����
	m_pUsingChannel = NULL;
	m_pPkgSendMngr = NULL;  //����֡���͹������
	m_pDevcieModel = NULL;

	m_pDeviceCmmChannel = new CDeviceCmmChannel();
	m_pPkgSendMngr = new CPpPackageSendMngr();

	//Engine Thread��صĴ���
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

	//׼�������豸
	ASSERT (m_pDeviceCmmConfigRef != NULL);

	// �����豸֮ǰ���豸ͨѶ�������ݸ��Ƶ�ģ��ͨѶ����������

	if (m_pDeviceCmmConfigRef != NULL)
	{
		CopyDeviceCmmConfig(m_pTemplate->m_pCmmConfig, m_pDeviceCmmConfigRef);
	}

	m_pDeviceCmmChannel->m_pThread = this;

	return TRUE;
}

//�������нű������̳߳�ͻ�����ܵ��������̣߳�Ҫ�����߳���Ҫ�����߳�����ʱ�ӽ�����
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

	//ɾ����Ӧ��EngineData
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


// CPpEngineThread ��Ϣ�������

//��ӽ�����ɵ�֡������ʱ�б�
void CPpEngineThread::AddReceivePackageDetail(CPpPackageDetail *pPkg)
{

}

//ģ�� ����/ж��
void CPpEngineThread::LoadTemplate(const CString &strTemplageFile)
{

}

void CPpEngineThread::UnLoad()
{

}


//�豸���ӡ��Ͽ�����
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ConnectDevice��(%s)(%s)"), m_pEngineData->m_strPpTemplateFile, m_pEngineData->m_strPpDeviceFile);
	}
	// �����߳�

	if (m_pProcedureRunThread == NULL)
	{
		//����Ͽ����Ӻ��ظ�������
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

//���ݽ���,������m_pChannel�����յ����ݺ�,֪ͨEngineThread����
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

	//ִ���յ����ĺ�Ĺ���
	//2019-5-27   lijunqing
	//if (m_pEngineData->m_pTemplate->m_strOnRecvProcedure.GetLength() > 3)
	//{
	//	RunProcedure(m_pEngineData->m_pTemplate->m_strOnRecvProcedure, NULL, FALSE);
	//}

	//Ϊ�˱������������ʹ��XVM�ĳ�ͻ�������������춼�ŵ�ͳһ���߳���
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

	//û�б���
	if (oBufPos.nBuffer1EndPos <= 0 && oBufPos.nBuffer2EndPos <= 0)
	{
		m_bIsInThreadParse = FALSE;
		return;
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("--------------���Ļ���{%d}----------------"), oBufPos.nBuffer1EndPos);
	CPpPackageDetail *pDetail = NULL;
	long nResult = 0;
	long nTempPos;
	BOOL bResetReceiveBeginPos = FALSE;

	long nBufLength = PpGetLengthFromCurr(oBufPos) ;

	//�������ı��ĳ��ȳ���128K������ϵͳ�����ٶ�̫���ˣ����������˲���
	if (nBufLength >= 131072) //128*1024
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("--------------���Ļ���%d>128K�����Ա���----------------"), nBufLength);
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
		//��ʼ����ǰ����������ĳ���
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

		//����֮��Ľ��������
		if (!IsPpParseError(nResult))
		{//�����ɹ�
			if (IsPpParseHasPakage(nResult))
			{//�������������ı��ģ��˴���Ŀ�����ڿ��Ǵ��ڣ�һ����û�н���ȫȫ���ı���
				//ƫ�Ʊ��ĵĳ���
				m_pUsingChannel->m_nParserBeginPos = oBufPos.nIndex;

				//��ӵ����Ĺ������
				DWORD dwBegin = GetTickCount();

				pDetail->SetBeginTime();
				//???????????????????????????????????
				//20170309��ȥ������ʱ��
				//InitPackageTime(pDetail, nTempPos); 
				m_listReceivePackage.AddTail(pDetail);

				if (g_bLogPackageInfor)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("����֡��[%s][%s]    (%d-%d ; %d-%d  : nIndex=%d)"), pDetail->m_strName, pDetail->m_strID
						, oBufPos.nBuffer1BeginPos, oBufPos.nBuffer1EndPos, oBufPos.nBuffer2BeginPos, oBufPos.nBuffer2EndPos, oBufPos.nIndex);
				}

				//��Լ¼������¼��Ҫ��¼�Ĺ�Լ֡
				m_pEngineData->m_pPpRecordMngr->AddPackage(pDetail);
				//�����ⲿִ�еĹ��̽ű�
				m_pEngineData->InitTrigerScriptRun(pDetail);

				//�յ����ģ�ִ�й��̣�������û�н�����ϣ�������������ִ�й���
				//2019-5-27  lijq
				if (m_pEngineData->CanRunWPackageOnReceive())
				{
					bNeedRunProcedure = TRUE;
					break;
				}
			}
			else
			{//û�а��������ı��ģ��˴���Ŀ�����ڿ��Ǵ��ڣ�һ����û�н���ȫȫ���ı���
				if (pDetail != NULL)
				{
					delete pDetail;
					pDetail = NULL;
				}

				break;
			}
		}
		else//�������ɹ���������ƫ�ƣ���������  //if (!IsPpParseError(nResult))
		{
#ifdef _use_CMemBufferList
			break;
#endif

			if (m_nCurrPkgLen > 0)//���д���û�����壬ϵͳ��ʱ���������ñ��ĳ��ȣ�20170622
			{//��һ��������������
				//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"Move Len(%d)", m_nCurrPkgLen);
				LogErrorParse(nErrorBeginPos, nErrorLength, &oBufPos);
				m_pUsingChannel->OffsetParserBeginPos(m_nCurrPkgLen);
				nErrorBeginPos = -1;
				nErrorLength = 0;
			}
			else
			{//û��������������
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

		//ȫ��������ϣ���������
		if (PpGetLengthFromCurr(oBufPos) == 0)
		{
			break;
		}
	}

	LogErrorParse(nErrorBeginPos, nErrorLength, &oBufPos);

	//����ִ����ϣ��ٸ�λ���λ�ã�Ŀ�ģ�������ʵڶ������ݣ����Ч��
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

	//û�б���
	if (oBufPos.nBuffer1EndPos <= 0)
	{
		return;
	}

	//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("--------------���Ļ���{%d}----------------"), oBufPos.nBuffer1EndPos);
	CPpPackageDetail *pDetail = NULL;
	long nResult = 0;

	pDetail = new CPpPackageDetail(m_pUsingChannel);
	pDetail->SetParent(m_pEngineData);
	pDetail->m_pPkgBufPos = &oBufPos;
	nResult = m_pTemplate->Parse(oBufPos, pDetail);

	//����֮��Ľ��������
	if (!IsPpParseError(nResult))
	{//�����ɹ�
		if (IsPpParseHasPakage(nResult))
		{//�������������ı��ģ��˴���Ŀ�����ڿ��Ǵ��ڣ�һ����û�н���ȫȫ���ı���
			//��ӵ����Ĺ������
			DWORD dwBegin = GetTickCount();

			pDetail->SetBeginTime();
			//???????????????????????????????????
			//20170309��ȥ������ʱ��
			//InitPackageTime(pDetail, nTempPos); 
			m_listReceivePackage.AddTail(pDetail);

			if (g_bLogPackageInfor)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("����֡��[%s][%s]"), pDetail->m_strName, pDetail->m_strID);
			}

			//��Լ¼������¼��Ҫ��¼�Ĺ�Լ֡
			m_pEngineData->m_pPpRecordMngr->AddPackage(pDetail);
			//�����ⲿִ�еĹ��̽ű�
			m_pEngineData->InitTrigerScriptRun(pDetail);
		}
		else
		{//û�а��������ı��ģ��˴���Ŀ�����ڿ��Ǵ��ڣ�һ����û�н���ȫȫ���ı���
			if (pDetail != NULL)
			{
				delete pDetail;
				pDetail = NULL;
			}
		}
	}
	else//�������ɹ���������ƫ�ƣ���������  //if (!IsPpParseError(nResult))
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

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourcePpBase::g_sLangTxt_ErrorMessage/*_T("������:(Begin=%d      Len=%d)")*/	, nBeginPos	, nLength);

	CString strMsg;
	LogProtocol(m_pszPpLogProtocol, oBufPosError, strMsg);
	strMsg.Append(_T("\r\n\r\n"));
	CLogPrint::LogString(XLOGLEVEL_TRACE,strMsg);

}

void CPpEngineThread::InitPackageTime(CPpPackageDetail *pPkg, long nBeginPos)
{
#ifndef _use_CMemBufferList
	//////////////////////////////////////////////////////////////////////////
	//��¼ʱ��
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

//���ͽ��մ����߳�
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

//ִ�й���
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

	//����������ʱ������ӹ��̣����⴦��
	CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
	posTo = m_listProcedureToRun.GetHeadPosition();

	while (posTo != NULL)
	{//����������ʱ������ӹ���
		posToPrev = posTo;
		pTo =  (CPpProcedureRun*)m_listProcedureToRun.GetNext(posTo);

		if (FindRunningProcedure(pTo->m_pProcedure->m_strID) != NULL)
		{//�������ͬ�Ĺ��������У��򲻴���
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_ProcessRun/*L"����\"%s\"�Ѿ�����"*/, pTo->m_pProcedure->m_strID);
			delete pTo;
			pTo = NULL;
			continue;
		}

		//���������ȼ���ֱ����ӵ�ִ���б�ĩβ
		m_listRunProcedure.AddTail(pTo);
		pTo->CopyDataInterfaceToPackage();
	}//end of "����������ʱ������ӹ���"

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
	{//�Ͽ���������
		m_dwReConnectState = 2;
		PostThreadMessage(WM_THREAD_CONNECT, NULL, NULL);
	}
	else if (m_dwReConnectState == 4)
	{
		Sleep(500);

		//10�����������
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

//���̴����߳�:��ѭ�������ϱ���
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
		{//���洦�ڹر�״̬
			break;
		}

		//��������������״̬
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

		//����������ʱ������ӹ��̣����⴦��
		pEngineThread->AddTempProcedureToRun();
		pos = pListRunProcedure->GetHeadPosition();
		PpDeleteUsedPackages(&pEngineThread->m_listReceivePackage, pEngineThread->m_pEngineData);

		//��ռ����
		while (pos != NULL)
		{
			if (pEngineThread->m_dwReConnectState != 0)
			{//����ʧ�ܣ���ִֹ�ж�ռ����
				break;
			}

			if (pEngineThread->m_bExitEngineThread)
			{//���洦�ڹر�״̬
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
		}//��ռ����

		if (pEngineThread->m_bExitEngineThread)
		{//���洦�ڹر�״̬
			break;
		}

		//���������ռ�߳�,����ִ�ж�ռ�߳�
		if (bHasExclusive)
		{
			continue;
		}

		//ִ�б��Ľ���
		pEngineThread->EnterParse_FromPpRunThread();

		pos = pListRunProcedure->GetHeadPosition();

		while (pos != NULL)
		{//�������й���
			posPrev = pos;
			p = (CPpProcedureRun*)pListRunProcedure->GetNext(pos);

			if (p->CanRun())
			{//�����Ƿ�������У������й������ȼ�����
				if (p->IsProcedureExit())
				{
					//�������̱���ץ��   2014-10-13  ���
					pEngineThread->OnProcedureExit(p);

					if (g_bLogEngineDebugInfor)
					{
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_ProcessClose/*L"----------����\"%s\"����----------"*/, p->m_pProcedure->m_strID);
					}
					
					//���͹��̽�����Ϣ
					if (!p->IsInitProcedure())
					{
						pEngineThread->m_pEngineData->OnProcedureEnd(p->m_pProcedure->m_strID, p->m_pProcedure->m_dwRunState, p->m_pProcedure->m_dwRunState);					
					}

					//ִ�й��̽����ű�
					p->m_pProcedure->RunEndScript();

					//�������������������������ɾ��
					pListRunProcedure->RemoveAt(posPrev);
					posPrev = pos;
					delete p;
				}
				else
				{
					p->Run();  //ִ�й�Լ����
				}
			}
			else
			{//�������ȼ�����������
				p->IncreasePriorityCounter();
			}

			if (pEngineThread->m_bExitEngineThread)
			{//���洦�ڹر�״̬
				break;
			}

			//Sleep(5);
		}//end of "�������й���"

		pEngineThread->RecordSendPackage();

		if (pEngineThread->m_bExitEngineThread)
		{//���洦�ڹر�״̬
			break;
		}

		pEngineThread->m_pEngineData->RunTrigerScript_Timer();
		Sleep(1);  //2018-7-8������S֡�����ִ�е��ٶȣ���Sleep(5)==>>Sleep(1)
	}

	//�ȴ�������ʹ�ò����˳�
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

//��ȡͨѶͨ��
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


		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_CommunPathUnExist3/*L"�ڵ�\"%s\"�����ͨ��ͨ��\"%s\"������"*/, pProcedure->m_strID, pProcedure->m_strChannelID);

		pCmmChannel = GetCmmChannel(m_pTemplate->m_strDefaultChannel);

		if (pCmmChannel == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_CommunPathUnExist2/*L"ģ�嶨���ͨ��ͨ��\"%s\"������"*/, pNode->m_strChannelID);

			//ѡ���һ��
			pCmmChannel =  (CCmmChannel*)m_pDeviceCmmChannel->GetHead();

			if (pCmmChannel == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourcePpBase::g_sLangTxt_CommunPathUnExist/*L"ģ�嶨���ͨ��ͨ��������"*/);
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
	pPkgSend->m_strChCmmMode = pPpProcedureRun->m_pProcedure->m_strChCmmMode;  //ͨѶģʽ

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
			{// ����Ǵ�������
				pEx = FindByClassID(nClassID, pSrc);
				if (pEx)
				{
					pEx->CopyOwn(p);
					CCmmSerialConfig *pConfig = (CCmmSerialConfig*)p;
					//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��������ͨѶ����(port=%d)"), pConfig->m_nPortNum);
				}
			}

			break;

		case DMCLASSID_NET_CONFIG:
			{// �������������
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
//	CCmmRcvSndTime *pCmmTime = (CCmmRcvSndTime*)lParam; //���ܱ��ĵ�ʱ��

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

	//����ӡ���Ĺ����Ƶ�ͨѶ�̵߳�OnReceive�����У��Ӷ���ӡԭʼ���ձ���,Ŀǰ��ʱ������TCPClientͨѶ��ʽ������ͨѶ��ʽ������ʱ���޸ġ�
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
	//��λ������ʼλ��

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
	{//�Ͽ���������
		//DisConnectDevice();
		if (m_pDeviceCmmChannel != NULL)
		{
			m_pDeviceCmmChannel->DisConnectDevice();
		}

		m_dwReConnectState = 3;

		return ;
	}

	if (m_dwReConnectState == 3)
	{//�ж����������Ƿ��Ѿ��Ͽ���Ȼ��ʼ��������
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

	m_pEngineData->ResetRecvTick();   //���ͱ��ļ�ʱ
	m_pEngineData->ResetSendTick();   //���ͱ��ļ�ʱ

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


//���ӱ���
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

	//���ӵ�ǰ�豸�Ĺ�Լ����
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
// 		strMsg = CXLanguageResourcePpBase::g_sLangTxt_Receive/*_T("���� ")*/;
// 	}
// 	else
// 	{
// 		strMsg = CXLanguageResourcePpBase::g_sLangTxt_Send/*_T("���� ")*/;
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
	m_pTemplate = NULL;//����ΪNULL�����յ�����ʱ������ǡ�

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

