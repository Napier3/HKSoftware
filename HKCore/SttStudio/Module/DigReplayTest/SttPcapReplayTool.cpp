#include "SttPcapReplayTool.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/WinPcap/Include/pcap.h"
#include "../Engine/SttClientTestEngine.h"

CSttPcapReplayTool *g_theSttPcapReplayTool = NULL;

CSttPcapReplayTool* CSttPcapReplayTool::g_pSttPcapReplayTool = NULL;
long CSttPcapReplayTool::g_nSttPcapReplayTool = 0;


void CSttPcapReplayTool::Create()
{
	g_nSttPcapReplayTool++;

	if (g_nSttPcapReplayTool == 1)
	{
		g_pSttPcapReplayTool = new CSttPcapReplayTool();

		g_pSttPcapReplayTool->m_bUseExternSttTestAppCfg = FALSE;
		g_pSttPcapReplayTool->m_pSttTestAppCfg = new CSttTestAppCfg;
		g_pSttPcapReplayTool->m_pSttTestAppCfg->SttOpen(_T(""));
		g_theSttPcapReplayTool = g_pSttPcapReplayTool;
	}
}

void CSttPcapReplayTool::Create(CSttTestAppCfg *pSttTestAppCfg)
{
	g_nSttPcapReplayTool++;

	if (g_nSttPcapReplayTool == 1)
	{
		g_pSttPcapReplayTool = new CSttPcapReplayTool();

		if (pSttTestAppCfg != NULL)
		{
			g_pSttPcapReplayTool->m_bUseExternSttTestAppCfg = TRUE;
			g_pSttPcapReplayTool->m_pSttTestAppCfg = pSttTestAppCfg;
		}
		else
		{
			g_pSttPcapReplayTool->m_bUseExternSttTestAppCfg = FALSE;
			g_pSttPcapReplayTool->m_pSttTestAppCfg = new CSttTestAppCfg;
			g_pSttPcapReplayTool->m_pSttTestAppCfg->SttOpen(_T(""));
		}

		g_theSttPcapReplayTool = g_pSttPcapReplayTool;
	}
}

void CSttPcapReplayTool::Release()
{
	g_nSttPcapReplayTool--;

	if (g_nSttPcapReplayTool == 0)
	{
		g_pSttPcapReplayTool->m_oSttPcapFileRead.FreeAll();
		delete g_pSttPcapReplayTool;
		g_pSttPcapReplayTool = NULL;
		g_theSttPcapReplayTool = NULL;
	}
}

CSttPcapReplayTool::CSttPcapReplayTool(void)
{
	m_pSttTestAppCfg = NULL;
	m_bUseExternSttTestAppCfg = FALSE;

	m_bExitThread = TRUE;
	m_pSttComtradeFileReadThread = NULL;
	m_pTestEngineClientData = NULL;
	//��ʼ��AB����
	CComtradeBufMngr::Create(COMTRADE_LOOPBUF_SIZE,COMTRADE_ABBUF_SIZE);
	m_oComtradeSendSocket.m_pbAnalysisFinish = &m_oSttPcapFileRead.m_bReadFiberDatasFinish;
}

CSttPcapReplayTool::~CSttPcapReplayTool(void)
{
	OnStopTest();
	//	FreeClientEngine();
	CComtradeBufMngr::Release();

	if ((m_pSttTestAppCfg != NULL)&&(!m_bUseExternSttTestAppCfg))
	{
		delete m_pSttTestAppCfg;
		m_pSttTestAppCfg = NULL;
	}
}

BOOL CSttPcapReplayTool::OnOpenPcapFile(const CString &strPcapFile)
{
	if (!IsFileExist(strPcapFile))
	{
		return FALSE;
	}

	//���³�ʼ��AB����
	CComtradeBufMngr::g_pComtradeBufMngr->ResetBuf();
	return m_oSttPcapFileRead.OpenPcapFile(strPcapFile);
}

BOOL CSttPcapReplayTool::HasOpenPcapFile()
{
	if (m_oSttPcapFileRead.m_strPcapFilePath.IsEmpty())
	{
		return FALSE;
	}

	return IsFileExist(m_oSttPcapFileRead.m_strPcapFilePath);
}


void CSttPcapReplayTool::FreeClientEngine()
{
	if(m_pTestEngineClientData != NULL)
	{
		m_pTestEngineClientData->PrepareFreeClientEngine();
		delete m_pTestEngineClientData;
		m_pTestEngineClientData = NULL;
	}
}

BOOL CSttPcapReplayTool::CreateSttComtradeSocket()
{
	if (m_oComtradeSendSocket.IsSocketValid())//2023.6.26 zhouhj ���¼��ͨ��Socket��Ч,����Ҫ���´���
	{
		return TRUE;
	}

	FreeClientEngine();

	if (m_oComtradeSendSocket.m_hSocket != 0)
	{
		m_oComtradeSendSocket.Close();
		WaitForThreadExit();
	}

	if (!ComtradeControl_ConnServer(m_pSttTestAppCfg->GetTestAppIP()))
	{
		return FALSE;
	}

	BOOL bRet = m_oComtradeClientSocket.ConnectServer(m_pSttTestAppCfg->GetTestAppIP(), STT_PORT_COMTRADE_SERVER/*g_oSttTestAppCfg.GetTestServerPort()*/);

	if(!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���Ӳ����ǡ�%s,%d��ʧ��"),m_pSttTestAppCfg->GetTestAppIP().GetString(), STT_PORT_COMTRADE_SERVER);
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���Ӳ����ǡ�%s,%d���ɹ�"),m_pSttTestAppCfg->GetTestAppIP().GetString(), STT_PORT_COMTRADE_SERVER);

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_Login;
	oSysCmd.m_strTestor = STT_SOFT_ID_COMTRADE;

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("�������Ĺ��ϻط�ͨ��......"));
	long nRet = m_oComtradeClientSocket.SendCmd(&oSysCmd);

	m_oComtradeSendSocket.AttatchClientTestEngine(m_pTestEngineClientData);
	m_oComtradeSendSocket.AttatchSocketDatabase(&m_oComtradeClientSocket);
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("������ɣ�׼����ʼ����......"));
	return TRUE;
}

BOOL CSttPcapReplayTool::ComtradeControl_ConnServer(const CString &strIP)
{
	if (m_pTestEngineClientData == NULL)
	{
		CSttClientTestEngine *pNew = new CSttClientTestEngine();
		//		pNew->AttatchSttTestMsgViewInterface(this);
		m_pTestEngineClientData = pNew;
	}

	BOOL bRet = m_pTestEngineClientData->ConnectServer(strIP,STT_PORT_COMTRADE_SERVER);

	if(!bRet)
	{
		delete m_pTestEngineClientData;
		m_pTestEngineClientData = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Connect Server [%s] [%d]ʧ��"), strIP.GetString(),STT_PORT_COMTRADE_SERVER);
		return bRet;
	}

	//����LocalIP
#ifdef _PSX_QT_LINUX_
	CString strMask;
	stt_net_get_deviceip( m_pTestEngineClientData->m_pSttClientSocket->m_strIPLocal, strMask);
#else
	m_pTestEngineClientData->m_pSttClientSocket->m_strIPLocal = strIP;
#endif

#ifdef _PSX_QT_LINUX_
	m_pTestEngineClientData->m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_NATIVE);
#else
	m_pTestEngineClientData->m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_LOCAL);
#endif

	m_pTestEngineClientData->m_pSttClientSocket->SetSocketType(STT_SOCKET_TYPE_LOCAL);
	m_pTestEngineClientData->m_oCurrUser.ID_Tester(g_nIDTester);
	m_pTestEngineClientData->m_oCurrUser.IP_User(m_pTestEngineClientData->m_pSttClientSocket->m_strIPLocal);
	m_pTestEngineClientData->m_oCurrUser.Name_User(m_pTestEngineClientData->m_pSttClientSocket->m_strIPLocal);
	m_pTestEngineClientData->m_oCurrUser.id_soft(STT_SOFT_ID_COMTRADECONTRL);

	CSttCmdData oRetData;
	long nExecStatus = m_pTestEngineClientData->System_Login(TRUE, &oRetData);

	if (nExecStatus != STT_CMD_ExecStatus_SUCCESS)
	{
		bRet = FALSE;
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Loginʧ��"));
	}

	if(bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "����������¼��ͨ���ɹ�");
		m_pTestEngineClientData->SetTestEventInterface(this);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "���Ӳ�����¼��ͨ��ʧ�ܣ�����������·�Ƿ���ͨ��IP��ַ���˿������Ƿ���ȷ��Ȼ�����������Ӱ�ť��������");
	}

	return bRet;
}

void CSttPcapReplayTool::WaitForThreadExit()
{
	CTickCount32 oTick;

	while(m_pSttComtradeFileReadThread != NULL)
	{
		oTick.DoEvents(5);
	}
}

void CSttPcapReplayTool::OnStartTest()
{//��ʼ���ԣ����������߳�
	OnStopTest();
	m_oSttPcapFileRead.GenerateFibersDatas();

	if (!m_oSttPcapFileRead.HasPcapSendDatas())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ������Pcap�ط�����Ϊ��,���������ûطŲ���."));
		return;
	}

	m_oSttPcapFileRead.CalOutputTime();

#ifdef _PSX_QT_LINUX_
	pthread_create((pthread_t*)&m_pSttComtradeFileReadThread,NULL,SttComtradeFileReadThread,(LPVOID)this );
#else
	m_pSttComtradeFileReadThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttComtradeFileReadThread,(LPVOID)this,0,NULL);
#endif
}

void CSttPcapReplayTool::OnStopTest()
{
	m_bExitThread = TRUE;
	WaitForThreadExit();
}

long CSttPcapReplayTool::Event_OnProcessComtradeRequstData(long nIndex)
{
	return OnProcessComtradeRequstData(nIndex);
}

long CSttPcapReplayTool::Event_OnProcessComtradeSendDataStartAck(long nIndex)
{
	return OnProcessComtradeSendDataStartAck(nIndex);
}


//�յ�������������
long CSttPcapReplayTool::OnProcessComtradeRequstData(long nIndex)
{
	m_oComtradeSendSocket.SetCurrSendDataIndex(nIndex);

	return 1;
}

long CSttPcapReplayTool::OnProcessComtradeSendDataStartAck(long nIndex)
{
	m_oComtradeSendSocket.SetSendDataStartAck();

	return 1;
}

//��ʼ����ʱ���������ļ��߳�
#ifdef _PSX_QT_LINUX_
void* CSttPcapReplayTool::SttComtradeFileReadThread(LPVOID pParam)
#else
UINT CSttPcapReplayTool::SttComtradeFileReadThread(LPVOID pParam)
#endif
{
	CSttPcapReplayTool *pReplay = (CSttPcapReplayTool*)pParam;
	pReplay->m_bExitThread = FALSE;

 	while(!pReplay->m_oSttPcapFileRead.m_bReadFiberDatasFinish)
 	{
 		if (pReplay->m_bExitThread)
 		{
 			break;
 		}
 
 		//��ѯ�ջ���
 		int nIndex = CComtradeBufMngr::g_pComtradeBufMngr->GetABBufIndexCanWrite();
 
 		if (nIndex <= 0)
 		{
 			Sleep(1);
 			continue;
 		}
 
 		pReplay->m_oSttPcapFileRead.GenerateABBuf(nIndex);
 	}

	pReplay->m_bExitThread = TRUE;
	pReplay->m_pSttComtradeFileReadThread = NULL;
#ifndef _PSX_QT_LINUX_
	return 1;
#endif
}

