// ..\Module\Engine\CmmChannel\EpEngineThread.cep : 实现文件
//

#include "stdafx.h"
#include "EpEngineThread.h"
#include "EpEngineBaseApp.h"

// CEpEngineThread

IMPLEMENT_DYNCREATE(CEpEngineThread, CWinThread)

CEpEngineThread::CEpEngineThread()
{
	m_pDevice = NULL;         //设备点表数据管理对象
	m_pProtocol = NULL;  //规约模板对象
	m_pDeviceCmmConfig = NULL;  //设备通讯配置对象
	m_pDeviceCmmChannel = NULL;    //关联的设备通讯对象
	m_pUsingChannel = NULL;
	m_pPkgSendMngr = NULL;  //报文帧发送管理对象
	m_pDevice = NULL;

	m_pDeviceCmmChannel = new CEpDeviceCmmChannel();
	m_pPkgSendMngr = new CEpFrameSendMngr();

	//Engine Thread相关的处理
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

	//准备连接设备
	ASSERT (m_pDeviceCmmConfig != NULL);

	// 连接设备之前将设备通讯配置数据复制到模板通讯配置数据中

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

	//删除对应的EngineData
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


// CEpEngineThread 消息处理程序

//添加解析完成的帧对象到临时列表
void CEpEngineThread::AddReceiveFrameDetail(CEpFrameBase *pPkg)
{

}

//模板 加载/卸载
void CEpEngineThread::LoadTemplate(const CString &strTemplageFile)
{

}

void CEpEngineThread::UnLoad()
{

}


//设备连接、断开管理
BOOL CEpEngineThread::ConnectDevice()
{
	ASSERT (m_pDeviceCmmChannel != NULL);
	ASSERT (m_pProtocol != NULL);

	if (m_pDeviceCmmChannel == NULL || m_pProtocol == NULL)
	{
		return FALSE;
	}

	// 启动线程
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

//数据接受,关联的m_pChannel对象收到数据后,通知EngineThread对象
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
		//初始化当前解析桢解析的长度
		m_nCurrPkgLen = 0;  
		nTempPos = m_pUsingChannel->m_nParserBeginPos;

		pDetail = new CEpFrameDetail();
		pDetail->SetChannel(m_pUsingChannel);
		pFrame = m_pProtocol->Parse(&oBufPos);

		//解析之后的结果有三种
		if (!Ep_IsParseError(nResult))
		{//解析成功
			if (Ep_IsParseHasPakage(nResult))
			{//解析包含完整的报文，此处的目的在于考虑串口，一次性没有接受全全部的报文
				//添加到报文管理对象
				pDetail->SetBeginTime();
				pFrame->AppendToDetail(pDetail);
				pFrame->RemoveAll();
				m_listReceiveFrame.AddTail(pDetail);

				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("RCV PKG:%s"), pDetail->m_strName);
			
				if (m_pEngineData->m_pEpRecordMngr->IsFrameIDExist(pDetail->m_strID))
				{//规约录波，记录需要记录的规约帧
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
			{//没有包含完整的报文：此处的目的在于考虑串口，一次性没有接受全全部的报文
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
		{//如果当前的缓冲区对象长度足够,则继续解析
			continue;
		}

		if (! m_pUsingChannel->DataIsEnoughForParse(m_pProtocol->m_nFrameMinLength))
		{//如果没有足够的数据,结束
			break;
		}

		CreateParseBufferPos(oBufPos);
	}
}

//发送接收处理线程
UINT CEpEngineThread::PkgSendReceiveThread(LPVOID pParam)
{
	return 0;
}

//执行过程
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

	//遍历过程临时链表，添加过程（互斥处理）
	CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
	posTo = m_listProcedureToRun.GetHeadPosition();

	while (posTo != NULL)
	{//遍历过程临时链表，添加过程
		posToPrev = posTo;
		pTo =  (CEpProcedure*)m_listProcedureToRun.GetNext(posTo);

		if (FindRunningProcedure(pTo->m_strID) != NULL)
		{//如果有相同的过程在运行，则不处理
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("过程\"%s\"已经运行"), pTo->m_strID);
			pTo = NULL;
			continue;
		}

		//不考虑优先级，直接添加到执行列表末尾
		m_listRunProcedure.AddTail(pTo);
		pTo->CopyDataInterfaceToFrame();
	}//end of "遍历过程临时链表，添加过程"

	m_listProcedureToRun.RemoveAll();

	oLock.Free();
}

//过程处理线程:死循环，不断遍历
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
		//遍历过程临时链表，添加过程（互斥处理）
		pEngineThread->AddTempProcedureToRun();
		pos = pListRunProcedure->GetHeadPosition();
		EpDeleteUsedFrames(&pEngineThread->m_listReceiveFrame, pEngineThread->m_pEngineData);

		while (pos != NULL)
		{//遍历运行过程
			posPrev = pos;
			p = (CEpProcedure*)pListRunProcedure->GetNext(pos);
	
			p->Run();  //执行规约过程

			if (p->IsProcedureExit())
			{
				CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("----------过程\"%s\"结束----------"), p->m_strID);
				//发送过程结束消息
				pEngineThread->m_pEngineData->OnProcedureEnd(p->m_strID);					

				//执行过程结束脚本
				p->RunEndScript();

				//过程如果结束，从运行链表中删除
				pListRunProcedure->RemoveAt(posPrev);
				posPrev = pos;
			}

			if (pEngineThread->m_bExitEngineThread)
			{//引擎处于关闭状态
				break;
			}
		}//end of "遍历运行过程"

		pEngineThread->RecordSendFrame();

		if (pEngineThread->m_bExitEngineThread)
		{//引擎处于关闭状态
			break;
		}

		Sleep(50);
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

//获取通讯通道
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


		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("节点\"%s\"定义的通信通道\"%s\"不存在"), pProcedure->m_strID, pProcedure->m_strChannelID);

		pCmmChannel = GetCmmChannel(m_pProtocol->m_strDefaultChannel);

		if (pCmmChannel == NULL)
		{
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("模板定义的通信通道\"%s\"不存在"), pNode->m_strChannelID);

			//选择第一个
			pCmmChannel =  (CEpCmmChannel*)m_pDeviceCmmChannel->GetHead();

			if (pCmmChannel == NULL)
			{
				CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("模板定义的通信通道不存在"));
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
	pPkgSend->m_strChCmmMode = pEpProcedureRun->m_strChCmmMode;  //通讯模式

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
			{// 如果是串口数据
				pEx = FindByClassID(nClassID, pSrc);
				if (pEx)
				{
					pEx->CopyOwn(p);
				}
			}

			break;

		case EPCLASSID_NET_CONFIG:
			{// 如果是网口数据
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
	CEpCmmRcvSndTime *pCmmTime = (CEpCmmRcvSndTime*)lParam; //接受报文的时间

	if (pApp->GetProtocolSpy())
	{
		LogProtocol(m_pDevice, g_pLogPkgReceivePrint, oCycleBufPos);
	}
	else
	{
	}

	m_pDeviceCmmChannel->m_oCmmRcvSndTimeMngr.DeletePrev(pCmmTime);
	//复位监视起始位置
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


//监视报文
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

	//监视当前设备的规约报文
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

