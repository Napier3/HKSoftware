// ..\Module\Engine\CmmChannel\EpEngineThread.cep : ʵ���ļ�
//

#include "stdafx.h"
#include "EpEngineThread.h"
#include "EpEngineBaseApp.h"

// CEpEngineThread

IMPLEMENT_DYNCREATE(CEpEngineThread, CWinThread)

CEpEngineThread::CEpEngineThread()
{
	m_pDevice = NULL;         //�豸������ݹ������
	m_pProtocol = NULL;  //��Լģ�����
	m_pDeviceCmmConfig = NULL;  //�豸ͨѶ���ö���
	m_pDeviceCmmChannel = NULL;    //�������豸ͨѶ����
	m_pUsingChannel = NULL;
	m_pPkgSendMngr = NULL;  //����֡���͹������
	m_pDevice = NULL;

	m_pDeviceCmmChannel = new CEpDeviceCmmChannel();
	m_pPkgSendMngr = new CEpFrameSendMngr();

	//Engine Thread��صĴ���
	m_pProcedureRunThread = NULL;
	m_bExitEngineThread = FALSE;
	m_bHasPostWmquit = FALSE;

	m_nThreadExitState = EPEXIT_STATE_NONE;
}

CEpEngineThread::~CEpEngineThread()
{

}

void CEpEngineThread::PostConnectDeviceMsg()
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

BOOL CEpEngineThread::IsConnecting()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return FALSE;
	}

	return m_pDeviceCmmChannel->IsConnecting();
}

BOOL CEpEngineThread::IsConnectSuccessful()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return FALSE;
	}

	return m_pDeviceCmmChannel->IsConnectSuccessful();
}

void CEpEngineThread::OnDeviceConnectFinish(BOOL bSucc)
{
	if (m_pEngineData != NULL)
	{
		m_pEngineData->OnDeviceConnectFinish(bSucc);
	}
}

BOOL CEpEngineThread::InitInstance()
{
	//m_oReceiveBuffer.SetBufferLength(1048576);  //1024*1024  1M

	//׼�������豸
	ASSERT (m_pDeviceCmmConfig != NULL);

	// �����豸֮ǰ���豸ͨѶ�������ݸ��Ƶ�ģ��ͨѶ����������

	if (m_pDeviceCmmConfig != NULL)
	{
		CopyDeviceCmmConfig(m_pProtocol->m_pCmmConfig, m_pDeviceCmmConfig);
	}

	m_pDeviceCmmChannel->m_pThread = this;

	return TRUE;
}

void CEpEngineThread::ExitEngineThread()     
{
	if (m_bExitEngineThread)
	{
		return;
	}

	m_nThreadExitState = EPEXIT_STATE_NORMAL;
	//DisConnectDevice();
	PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
}
BOOL CEpEngineThread::IsThreadExitExtern()    
{
	if (!IsThreadExit())
	{
		return FALSE;
	}

	if (!m_bHasPostWmquit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpEngineThread::IsThreadExit()    
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

int CEpEngineThread::ExitInstance()
{
	m_listReceiveFrame.DeleteAll();
	m_listRunProcedure.DeleteAll();
	m_listProcedureToRun.DeleteAll();

	delete m_pDeviceCmmChannel;
	m_pDeviceCmmChannel = NULL;

	delete m_pPkgSendMngr;
	m_pPkgSendMngr = NULL;

	int nRet = CWinThread::ExitInstance();

	//ɾ����Ӧ��EngineData
	CEpEngineBaseApp *pApp = (CEpEngineBaseApp*)AfxGetApp();
	m_pEngineData->m_pEngineThread = NULL;
	pApp->DeleteEngineData(m_pEngineData);

	return nRet;
}

BEGIN_MESSAGE_MAP(CEpEngineThread, CWinThread)
	ON_THREAD_MESSAGE(WM_THREAD_RECEIVE, &CEpEngineThread::OnChannelReceive)
	ON_THREAD_MESSAGE(WM_THREAD_CONNECT, &CEpEngineThread::OnConnectDevice)
	ON_THREAD_MESSAGE(WM_THREAD_DISCONNECT, &CEpEngineThread::OnDisConnectDevice)
	ON_THREAD_MESSAGE(WM_EXIT_ENGINE_THREAD, &CEpEngineThread::OnExitEngineThread)
	ON_THREAD_MESSAGE(WM_DELETE_ALL_RECORD_FRAME, &CEpEngineThread::OnDeleteAllRecordFrame)
END_MESSAGE_MAP()


// CEpEngineThread ��Ϣ�������

//��ӽ�����ɵ�֡������ʱ�б�
void CEpEngineThread::AddReceiveFrameDetail(CEpFrameBase *pPkg)
{

}

//ģ�� ����/ж��
void CEpEngineThread::LoadTemplate(const CString &strTemplageFile)
{

}

void CEpEngineThread::UnLoad()
{

}


//�豸���ӡ��Ͽ�����
BOOL CEpEngineThread::ConnectDevice()
{
	ASSERT (m_pDeviceCmmChannel != NULL);
	ASSERT (m_pProtocol != NULL);

	if (m_pDeviceCmmChannel == NULL || m_pProtocol == NULL)
	{
		return FALSE;
	}

	// �����߳�
	m_pProcedureRunThread = AfxBeginThread(ProcedureRunThread,this);
	m_pProcedureRunThread->m_bAutoDelete = TRUE;
	m_pDeviceCmmChannel->ConnectDevice(m_pProtocol->m_pCmmConfig);

	return TRUE;
}

BOOL CEpEngineThread::CmmChannelConfig()
{
	return FALSE;
}

BOOL CEpEngineThread::DisConnectDevice()
{
	if (m_pDeviceCmmChannel == NULL)
	{
		return TRUE;
	}

	m_pDeviceCmmChannel->DisConnectDevice();
	m_bExitEngineThread = TRUE;

	return FALSE;
}

void EpDeleteUsedFrames(CExBaseList *pList, CEpEngineData *pEngineData)
{
	POS pos = pList->GetHeadPosition();
	POS posPrev = NULL;
	CEpFrameBase *pPkgDetail = NULL;
	POS posTail = pList->GetTailPosition();

	while (pos != posTail)
	{
		posPrev = pos;
		pPkgDetail = (CEpFrameBase*)pList->GetNext(pos);

		if (pPkgDetail->m_bUsed)
		{
			if (pPkgDetail->m_bRecord)
			{
				pList->RemoveAt(posPrev);
			}
			else
			{
				pList->RemoveAt(posPrev);
				delete pPkgDetail;
			}
		}
		else if ( pPkgDetail->IsTimeout())
		{
			if (pPkgDetail->m_bRecord)
			{
				pList->RemoveAt(posPrev);
			}
			else
			{
				pList->RemoveAt(posPrev);
				delete pPkgDetail;
			}
		}
	}
}

//���ݽ���,������m_pChannel�����յ����ݺ�,֪ͨEngineThread����
void CEpEngineThread::OnReceived(CEpCmmRcvSndTime *pCmmTime)
{
	if (m_pProtocol == NULL)
	{
		return ;
	}

// 	if (!m_pUsingChannel->HasBufferNeedParse())
// 	{
// 		return;
// 	}

	if (! m_pUsingChannel->DataIsEnoughForParse(m_pProtocol->m_nFrameMinLength))
	{
		return;
	}

	EPBUFFERPOS oBufPos;
	CreateParseBufferPos(oBufPos);
	CEpFrameDetail *pDetail = NULL;
	CEpFrameBase *pFrame = NULL;
	long nResult = 0;
	long nTempPos;

	while (TRUE)
	{
		//��ʼ����ǰ����������ĳ���
		m_nCurrPkgLen = 0;  
		nTempPos = m_pUsingChannel->m_nParserBeginPos;

		pDetail = new CEpFrameDetail();
		pDetail->SetChannel(m_pUsingChannel);
		pFrame = m_pProtocol->Parse(&oBufPos);

		//����֮��Ľ��������
		if (!Ep_IsParseError(nResult))
		{//�����ɹ�
			if (Ep_IsParseHasPakage(nResult))
			{//�������������ı��ģ��˴���Ŀ�����ڿ��Ǵ��ڣ�һ����û�н���ȫȫ���ı���
				//��ӵ����Ĺ������
				pDetail->SetBeginTime();
				pFrame->AppendToDetail(pDetail);
				pFrame->RemoveAll();
				m_listReceiveFrame.AddTail(pDetail);

				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("RCV PKG:%s"), pDetail->m_strName);
			
				if (m_pEngineData->m_pEpRecordMngr->IsFrameIDExist(pDetail->m_strID))
				{//��Լ¼������¼��Ҫ��¼�Ĺ�Լ֡
					if (!pDetail->m_bRecord)
					{
						m_pEngineData->m_pEpRecordMngr->AddFrame(pDetail);
						pDetail->m_bRecord = TRUE;
						CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("Record:%s {%d:%d:%d.%d}"), pDetail->m_strID
							, pDetail->m_tm.wHour,  pDetail->m_tm.wMinute, pDetail->m_tm.wSecond, pDetail->m_tm.wMilliseconds);
					}
				}

				m_pUsingChannel->OffsetParserBeginPos(oBufPos);
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
		else
		{
			Ep_OffsetEpBufferCurr(&oBufPos, 1);
			m_pUsingChannel->OffsetParserBeginPos(1);

			if (pDetail != NULL)
			{
				delete pDetail;
				pDetail = NULL;
			}
		}

		if (Ep_EpBufferLeave(&oBufPos) > m_pProtocol->m_nFrameMinLength)
		{//�����ǰ�Ļ��������󳤶��㹻,���������
			continue;
		}

		if (! m_pUsingChannel->DataIsEnoughForParse(m_pProtocol->m_nFrameMinLength))
		{//���û���㹻������,����
			break;
		}

		CreateParseBufferPos(oBufPos);
	}
}

//���ͽ��մ����߳�
UINT CEpEngineThread::PkgSendReceiveThread(LPVOID pParam)
{
	return 0;
}

//ִ�й���
void CEpEngineThread::RunProcedure(const CString &strProcedureID, CExBaseList *pInterface) 
{
	CEpProcedure *pProcedure = (CEpProcedure*)m_pProtocol->m_pEpProcedures->FindByID(strProcedureID);

	if (pProcedure == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("-----procedure \"%s\" not exist"), strProcedureID);
		return;
	}

	RunProcedure(pProcedure);
}

void CEpEngineThread::RunProcedure(UINT nClassID)
{
	CEpProcedure *pProcedure = (CEpProcedure*)m_pProtocol->m_pEpProcedures->FindByClassID(nClassID);

	if (pProcedure == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("-----procedure \"%08X\" not exist"), nClassID);
		return;
	}

	RunProcedure(pProcedure);
}

void CEpEngineThread::RunProcedure(CEpProcedure *pProcedure)
{
	CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
	m_listProcedureToRun.AddTail(pProcedure);
}

void CEpEngineThread::AddTempProcedureToRun()
{
	if (m_listProcedureToRun.GetCount() == 0)
	{
		return;
	}

	POS posTo = NULL;
	POS posToPrev = NULL;
	CEpProcedure *pTo = NULL;

	//����������ʱ������ӹ��̣����⴦��
	CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
	posTo = m_listProcedureToRun.GetHeadPosition();

	while (posTo != NULL)
	{//����������ʱ������ӹ���
		posToPrev = posTo;
		pTo =  (CEpProcedure*)m_listProcedureToRun.GetNext(posTo);

		if (FindRunningProcedure(pTo->m_strID) != NULL)
		{//�������ͬ�Ĺ��������У��򲻴���
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("����\"%s\"�Ѿ�����"), pTo->m_strID);
			pTo = NULL;
			continue;
		}

		//���������ȼ���ֱ����ӵ�ִ���б�ĩβ
		m_listRunProcedure.AddTail(pTo);
		pTo->CopyDataInterfaceToFrame();
	}//end of "����������ʱ������ӹ���"

	m_listProcedureToRun.RemoveAll();

	oLock.Free();
}

//���̴����߳�:��ѭ�������ϱ���
UINT CEpEngineThread::ProcedureRunThread(LPVOID pParam)
{
	CEpEngineThread *pEngineThread = (CEpEngineThread*)pParam;
	ASSERT (pEngineThread != NULL);

	CExBaseList *pListRunProcedure = &pEngineThread->m_listRunProcedure;
	POS pos = NULL;
	POS posPrev = NULL;
	CEpProcedure *p = NULL;

	while (TRUE)
	{
		//����������ʱ������ӹ��̣����⴦��
		pEngineThread->AddTempProcedureToRun();
		pos = pListRunProcedure->GetHeadPosition();
		EpDeleteUsedFrames(&pEngineThread->m_listReceiveFrame, pEngineThread->m_pEngineData);

		while (pos != NULL)
		{//�������й���
			posPrev = pos;
			p = (CEpProcedure*)pListRunProcedure->GetNext(pos);
	
			p->Run();  //ִ�й�Լ����

			if (p->IsProcedureExit())
			{
				CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("----------����\"%s\"����----------"), p->m_strID);
				//���͹��̽�����Ϣ
				pEngineThread->m_pEngineData->OnProcedureEnd(p->m_strID);					

				//ִ�й��̽����ű�
				p->RunEndScript();

				//�������������������������ɾ��
				pListRunProcedure->RemoveAt(posPrev);
				posPrev = pos;
			}

			if (pEngineThread->m_bExitEngineThread)
			{//���洦�ڹر�״̬
				break;
			}
		}//end of "�������й���"

		pEngineThread->RecordSendFrame();

		if (pEngineThread->m_bExitEngineThread)
		{//���洦�ڹر�״̬
			break;
		}

		Sleep(50);
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
			Sleep(50);
			dwTimeLong += 50;
		}

		if (dwTimeLong > 5000)
		{
			break;
		}
	}

	pEngineThread->m_pPkgSendMngr->DeleteAll();
	pEngineThread->m_pProcedureRunThread = NULL;
	pEngineThread->m_nThreadExitState = EPEXIT_STATE_EXITPRUN; 

	return 0;
}

CEpProcedure* CEpEngineThread::FindRunningProcedure(const CString &strProcedureID)
{
	POS pos = m_listRunProcedure.GetHeadPosition();
	CEpProcedure *p = NULL;
	CEpProcedure *pFind = NULL;

	while (pos != NULL)
	{
		p = (CEpProcedure*)m_listRunProcedure.GetNext(pos);

		if (p->m_strID == strProcedureID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CEpEngineThread::CreateParseBufferPos(EPBUFFERPOS &oBufPos)
{
	m_pUsingChannel->GetReceiveBufferPos(oBufPos);
//	EPBUFFERPOS oCycleBufPos;
//
// 	m_pUsingChannel->m_pCycleRcvBuffer->GetBufferPos(m_pUsingChannel->m_nParserBeginPos, -1, oCycleBufPos);
// 	oBufPos.nBuffer1BeginPos = oCycleBufPos.nBuf1BeginPos;
// 	oBufPos.nBuffer1EndPos = oCycleBufPos.nBuf1EndPos;
// 	oBufPos.nBuffer2BeginPos = oCycleBufPos.nBuf2BeginPos;
// 	oBufPos.nBuffer2EndPos = oCycleBufPos.nBuf2EndPos;
// 	oBufPos.pBuffer = oCycleBufPos.pBuffer;
// 	oBufPos.nIndex = oCycleBufPos.nBuf1BeginPos;
}

//��ȡͨѶͨ��
CEpCmmChannel* CEpEngineThread::GetCmmChannel(const CString &strCmmChannelID)
{
	CEpCmmChannel *pCmmChannel = NULL;
	pCmmChannel = (CEpCmmChannel*)m_pDeviceCmmChannel->FindByID(strCmmChannelID);
	return pCmmChannel;
}

CEpCmmChannel* CEpEngineThread::GetCmmChannel(CEpNode *pNode)
{
	CEpCmmChannel *pCmmChannel = NULL;

	if (pNode->m_strChannelID.GetLength() > 0)
	{
		pCmmChannel = GetCmmChannel(pNode->m_strChannelID);
	}

	if (pCmmChannel == NULL)
	{
		CEpProcedure *pProcedure = (CEpProcedure*)pNode->GetAncestor(EPCLASSID_PROCEDURE);

		pCmmChannel = GetCmmChannel(pProcedure->m_strChannelID);

		if (pCmmChannel != NULL)
		{
			return pCmmChannel;
		}


		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("�ڵ�\"%s\"�����ͨ��ͨ��\"%s\"������"), pProcedure->m_strID, pProcedure->m_strChannelID);

		pCmmChannel = GetCmmChannel(m_pProtocol->m_strDefaultChannel);

		if (pCmmChannel == NULL)
		{
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("ģ�嶨���ͨ��ͨ��\"%s\"������"), pNode->m_strChannelID);

			//ѡ���һ��
			pCmmChannel =  (CEpCmmChannel*)m_pDeviceCmmChannel->GetHead();

			if (pCmmChannel == NULL)
			{
				CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("ģ�嶨���ͨ��ͨ��������"));
			}
		}
	}

	return pCmmChannel;
}

CEpFrameBase* CEpEngineThread::AddFrameSend(CEpProcedure *pEpProcedureRun)
{
	ASSERT(m_pPkgSendMngr != NULL);
	CEpCmmChannel *pChannel = GetCmmChannel(pEpProcedureRun->GetCurrNode());
	CEpFrameBase *pPkgSend = m_pPkgSendMngr->AddNew(pEpProcedureRun, pChannel);
	pPkgSend->m_strChCmmMode = pEpProcedureRun->m_strChCmmMode;  //ͨѶģʽ

// 	long nCount = m_pPkgSendMngr->GetCount();
// 	CLogPrint::LogFormatString(g_pLogTracePrint, LOGLEVEL_TRACE, L"m_pPkgSendMngr(%d)", nCount);

	return pPkgSend;
}

void CEpEngineThread::CopyDeviceCmmConfig(CEpDeviceCmmConfig *pDes, CEpDeviceCmmConfig* pSrc)
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
		case EPCLASSID_CMM_SERIAL_CONFIG:
			{// ����Ǵ�������
				pEx = FindByClassID(nClassID, pSrc);
				if (pEx)
				{
					pEx->CopyOwn(p);
				}
			}

			break;

		case EPCLASSID_NET_CONFIG:
			{// �������������
				CEpCmmNetConfig *pCmmNetConfigDes = (CEpCmmNetConfig*)p;
				CEpCmmNetConfig *pCmmNetConfigSrc = (CEpCmmNetConfig*)FindByClassID(nClassID, pSrc);
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

CExBaseObject* CEpEngineThread::FindByClassID(UINT nClassID, CExBaseList* pList)
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


void AFX_MSG_CALL CEpEngineThread::OnChannelReceive(WPARAM wParam, LPARAM lParam)
{
	CEpEngineBaseApp *pApp = (CEpEngineBaseApp*)AfxGetApp();
	EPBUFFERPOS oCycleBufPos;
	m_pUsingChannel = (CEpCmmChannel*)wParam;
	m_pUsingChannel->GetReceiveBufferPos(oCycleBufPos);
	CEpCmmRcvSndTime *pCmmTime = (CEpCmmRcvSndTime*)lParam; //���ܱ��ĵ�ʱ��

	if (pApp->GetProtocolSpy())
	{
		LogProtocol(m_pDevice, g_pLogPkgReceivePrint, oCycleBufPos);
	}
	else
	{
	}

	m_pDeviceCmmChannel->m_oCmmRcvSndTimeMngr.DeletePrev(pCmmTime);
	//��λ������ʼλ��
	m_pUsingChannel->ResetReceiveSpyBeginPos();
	OnReceived(pCmmTime);
}

void AFX_MSG_CALL CEpEngineThread::OnConnectDevice(WPARAM wParam, LPARAM lParam)
{
	ConnectDevice();
}

void AFX_MSG_CALL CEpEngineThread::OnDisConnectDevice(WPARAM wParam, LPARAM lParam)
{
	DisConnectDevice();
}

void AFX_MSG_CALL CEpEngineThread::OnExitEngineThread(WPARAM wParam, LPARAM lParam)
{
	if (m_nThreadExitState == EPEXIT_STATE_NORMAL)
	{
		m_bExitEngineThread = TRUE;
		PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
		return;
	}

	if (m_nThreadExitState == EPEXIT_STATE_EXITPRUN)
	{
		DisConnectDevice();
		PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
		m_nThreadExitState = EPEXIT_STATE_DISCONNECT;
		return;
	}

	if (IsThreadExit())
	{
		m_nThreadExitState = EPEXIT_STATE_EXIT;
		PostThreadMessage(WM_QUIT, 0, 0);
		m_bHasPostWmquit = TRUE;
	}
	else
	{
		PostThreadMessage(WM_EXIT_ENGINE_THREAD, 0, 0);
	}
}

void AFX_MSG_CALL CEpEngineThread::OnDeleteAllRecordFrame(WPARAM wParam, LPARAM lParam)
{
	//CLogPrint::LogFormatString(LOGLEVEL_TRACE, L"OnDeleteAllRecordFrame-delete:%d", ::GetTickCount());
	m_pEngineData->m_pEpRecordMngr->DeleteAll();
}

void CEpEngineThread::RecordSendFrame()
{
	CEpFrameBase *pSend = NULL;
	POS pos = m_pEngineData->m_pEpRecordMngr->GetHeadPosition();

	while (pos != NULL)
	{
		pSend = (CEpFrameBase*)m_pEngineData->m_pEpRecordMngr->GetNext(pos);

		if (pSend->HasSended())
		{
			if (m_pEngineData->m_pEpRecordMngr->IsFrameIDExist(pSend->m_strID))
			{
				m_pEngineData->m_pEpRecordMngr->AddTail(pSend);
			}		
		}
	}

	m_pPkgSendMngr->DeleteSendFrames();
}


//���ӱ���
void CEpEngineThread::LogProtocol(CExBaseObject *pDevice, LPVOID pPara, EPBUFFERPOS &oBufPos)
{
	if (oBufPos.dwBufferLen < 0)
	{
		return ;
	}

	CEpEngineBaseApp *pApp = (CEpEngineBaseApp*)AfxGetApp();

	if (pApp->IsExitEngineThread())
	{
		return;
	}

	if (! pApp->GetProtocolSpy())
	{
		return;
	}

	CEpDevice *pLogDevice = pApp->GetCurrSpyDevice();

	//���ӵ�ǰ�豸�Ĺ�Լ����
	if (pLogDevice != NULL)
	{
		if (pDevice != pLogDevice)
		{
			return;
		}
	}

	CString strMsg;
	long nIndex = 0;
	BYTE *pBuffer = oBufPos.pBuffer;
	BYTE *pEnd = oBufPos.pBuffer + oBufPos.dwBufferLen;

	while (pBuffer < pEnd)
	{
		strMsg.AppendFormat(_T("%02X "), *pBuffer);
		pBuffer++;
	}

	strMsg.Append(_T("\r\n"));
	CLogPrint::LogString(pPara, LOGLEVEL_TRACE, strMsg);
}

