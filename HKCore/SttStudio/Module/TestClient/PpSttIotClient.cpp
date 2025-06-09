#include "stdafx.h"
#include "PpSttIotClient.h"
#include "../../Module/API/NetworkInterface.h"

CPpSttIotClient::CPpSttIotClient(void)
{
	CString strFile = _P_GetConfigPath();
	strFile += _T("PpSttIotClientConfig.xml");
	InitSttTestDeviceCfg(strFile);
}

CPpSttIotClient::~CPpSttIotClient(void)
{
}

long CPpSttIotClient::SendIotCmd(CSttIotCmd &oIotCmd)
{
	if (! IsConnectSuccess())
	{
		return STT_CMD_ExecStatus_FAILURE;
	}

	//return m_pXClientEngine->SendCmdSync(&oIotCmd,g_nTimeOut_Test,NULL,TRUE);
	//2023-5-19  Ljq Sl
	//ͨѶ����ִ�У���������첽�ģ��ʴ˴������첽����ͬ������ʱ��DoEvent()�Ῠ����
	return m_pXClientEngine->SendCmdAsync(&oIotCmd,g_nTimeOut_Test,NULL,TRUE);
}

/*��Ҫ���õ����ݰ�����
1��DeviceIP = �����IP��
2������˶˿ڣ�
3��local-ip = ����IP�����ڸ���¼�û���Ϣ��ֵ
*/
BOOL CPpSttIotClient::ConnectSttServer()
{
	if (IsConnectSuccess())
	{
		return TRUE;
	}

    CString strIP;
#ifdef _PSX_OS_CENTOS_
    stt_net_get_ip(&strIP);
#else
    strIP = m_oTestDeviceCfg.m_strRemoteIP;
#endif

	long nPort = m_oTestDeviceCfg.m_nRemotePort;

	CSttClientTestEngine *pNew = new CSttClientTestEngine();
	pNew->AttatchSttTestMsgViewInterface(this);
	m_pXClientEngine = pNew;

	BOOL bRet = m_pXClientEngine->ConnectServer(strIP,nPort);

	if(!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Connect Server [%s] failed"), strIP.GetString());
		return bRet;
	}

	//����LocalIP
	m_pXClientEngine->m_pSttClientSocket->m_strIPLocal = m_oTestDeviceCfg.m_strLocalIP;
	m_pXClientEngine->m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_LOCAL);

	m_pXClientEngine->m_pSttClientSocket->SetSocketType(STT_SOCKET_TYPE_LOCAL);
	m_pXClientEngine->m_oCurrUser.ID_Tester(g_nIDTester);
	m_pXClientEngine->m_oCurrUser.IP_User(m_pXClientEngine->m_pSttClientSocket->m_strIPLocal);
	m_pXClientEngine->m_oCurrUser.Name_User(m_pXClientEngine->m_pSttClientSocket->m_strIPLocal);
	m_pXClientEngine->m_oCurrUser.id_soft(STT_SOFT_ID_TEST);

	return bRet;
}

void CPpSttIotClient::InitSttTestDeviceCfg(const CString &strCfgFile)
{
	m_oTestDeviceCfg.OpenTestDeviceConfig(strCfgFile);
}

