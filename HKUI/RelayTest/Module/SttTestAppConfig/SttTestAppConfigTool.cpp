#include "stdafx.h"
#include "SttTestAppConfigTool.h"
#include "../../../Module/Socket/XPing.h"

#ifndef _PSX_IDE_QT_
#ifndef _Not_Use_CSttTestAppConfigDlg_
#include "Dialog\SttTestAppConfigDlg.h"
#endif
#endif

#ifdef _PSX_QT_LINUX_
#include "../API/NetworkInterface.h"
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//CSttTestAppConfigTool g_oSttTestAppConfigTool;

CSttTestAppConfigTool::CSttTestAppConfigTool()
{
	m_pSttTestMsgViewInterface = NULL;
	m_pClientEngine = NULL;
	m_strServerID = STT_SOFT_ID_TEST;
	m_strSoftID = STT_SOFT_ID_TEST;
	m_pSttTestAppCfg = NULL;
}

CSttTestAppConfigTool::~CSttTestAppConfigTool()
{
	//FreeClientEngine();
}

#ifndef _PSX_IDE_QT_
void CSttTestAppConfigTool::TestAppConfig(CSttTestEngineClientData **ppXClientEngine, CSttTestMsgViewInterface *pMsgView, CWnd *pParentWnd)
{
#ifndef _Not_Use_CSttTestAppConfigDlg_
	m_pSttTestMsgViewInterface = pMsgView;
	CSttTestAppConfigDlg oDlg;
	oDlg.m_pSttTestAppConfigTool = this;
	oDlg.m_pSttTestAppCfg = m_pSttTestAppCfg;

	if (oDlg.DoModal() == IDOK)
	{
		pParentWnd->KillTimer(1);

		if (*ppXClientEngine != NULL)
		{
			delete *ppXClientEngine;
		}

		GetSttTestEngineClientData(ppXClientEngine);
		pParentWnd->SetTimer(1,1000,NULL);
	}
#endif
}
#endif

CSttTestEngineClientData* CSttTestAppConfigTool::CreateTestEngine(CSttTestAppCfg *pSttTestAppCfg, CString &strErrorInfo)
{
	if (m_strServerID.GetLength() == 0)
	{
		m_strServerID = STT_SOFT_ID_TEST;
	}

	CSttTestEngineClientData *pClientEngine = NULL; 
	if (m_strServerID == STT_SOFT_ID_ATS)
	{
		pClientEngine = CreateAtsEngine(pSttTestAppCfg, m_strSoftID, strErrorInfo);
	}
	else
	{
		pClientEngine = CreateTestCtrlEngine(pSttTestAppCfg, m_strSoftID, strErrorInfo);
	}

	m_pClientEngine = NULL;
	return pClientEngine;
}

CSttTestEngineClientData* CSttTestAppConfigTool::CreateTestCtrlEngine(CSttTestAppCfg *pSttTestAppCfg, const CString &strSoftID, CString &strErrorInfo)
{
	BOOL bRet = FALSE;
	CString strTestAppIP;

	if (pSttTestAppCfg->IsLocal())
	{
#ifdef _PSX_OS_CENTOS_
		strTestAppIP = pSttTestAppCfg->GetTestAppIP(); //Centos下，是工控机，和Z7平台是分开的，无法直接通过获取主机IP的方式连接测试仪底层Server
#else
#ifdef _PSX_QT_LINUX_
		CString strMask;
		stt_net_get_deviceip(strTestAppIP, strMask);
#else
		strTestAppIP = pSttTestAppCfg->GetTestAppIP();
#endif
#endif
		bRet = Local_ConnectServer(pSttTestAppCfg, strTestAppIP, STT_PORT_TEST_SERVER, strSoftID);
	}
	else
	{
		strTestAppIP = pSttTestAppCfg->GetCloudIP();
		bRet = Remote_ConnectServer(pSttTestAppCfg, strTestAppIP, pSttTestAppCfg->GetCloudServerPort());
	}

	if (!bRet)
	{
#ifdef NOT_USE_XLANGUAGE
		strErrorInfo.Format(_T("连接服务器[%s][%d]失败"), strTestAppIP.GetString());
#else
		strErrorInfo.Format(g_sLangTxt_ConServerFail.GetString(), strTestAppIP.GetString());
#endif
		delete m_pClientEngine;
		m_pClientEngine = NULL;
	}

	return m_pClientEngine;
}

CSttTestEngineClientData* CSttTestAppConfigTool::CreateAtsEngine(CSttTestAppCfg *pSttTestAppCfg, const CString &strSoftID, CString &strErrorInfo)
{
	CString strIP;
	BOOL bRet = FALSE;

	if (pSttTestAppCfg->IsLocal())
	{
		strIP = pSttTestAppCfg->GetTestAppIP();
		bRet = Local_ConnectServer(pSttTestAppCfg, strIP, STT_PORT_NATIVE_SERVER, strSoftID);
	}
	else
	{
		strIP = pSttTestAppCfg->GetCloudIP();
		bRet = Remote_ConnectServer(pSttTestAppCfg, strIP, pSttTestAppCfg->GetCloudServerPort());
	}

	if (!bRet)
	{
#ifdef NOT_USE_XLANGUAGE
		strErrorInfo.Format(_T("连接服务器[%s][%d]失败"), strIP.GetString());
#else
		strErrorInfo.Format(g_sLangTxt_ConServerFail.GetString(), strIP.GetString());
#endif
		delete m_pClientEngine;
		m_pClientEngine = NULL;
	}

	return m_pClientEngine;
}


void CSttTestAppConfigTool::FreeClientEngine()
{
	if(m_pClientEngine != NULL)
	{
		m_pClientEngine->PrepareFreeClientEngine();

		delete m_pClientEngine;
		m_pClientEngine = NULL;
	}
}

void CSttTestAppConfigTool::GetSttTestEngineBase(CSttTestAppCfg *pSttTestAppCfg, CSttTestEngineBase** ppTestEngineBase)
{
	CSttTestEngineBase *p = GetSttTestEngineBase(pSttTestAppCfg);

	if (p == NULL)
	{
		*ppTestEngineBase = p;
	}
}

CSttTestEngineBase *CSttTestAppConfigTool::GetSttTestEngineBase(CSttTestAppCfg *pSttTestAppCfg)
{
	if (m_pClientEngine == NULL)
	{
		return NULL;
	}

	CSttTestEngineBase *pRet = NULL;
	CSttTestEngineClientData *pClientEngine = m_pClientEngine;

	if (pSttTestAppCfg->IsLocal())
	{
		pRet = (CSttTestEngineBase *)((CSttRemoteClientTestEngine *)pClientEngine);
	}
	else
	{
		pRet = (CSttTestEngineBase *)((CSttClientTestEngine *)pClientEngine);
	}

	m_pClientEngine = NULL;

	return pRet;
}

void CSttTestAppConfigTool::GetSttTestEngineClientData(CSttTestEngineClientData** ppTestEngineClientData)
{
	CSttTestEngineClientData *p = GetSttTestEngineClientData();

	if (p != NULL)
	{
		*ppTestEngineClientData = p;
	}
}

CSttTestEngineClientData* CSttTestAppConfigTool::GetSttTestEngineClientData()
{
	if (m_pClientEngine != NULL)
	{
		CSttTestEngineClientData *p = m_pClientEngine;
		m_pClientEngine = NULL;
		return p;
	}
	else
	{
		return NULL;
	}
}


BOOL CSttTestAppConfigTool::Local_ConnectServer()
{
	return TRUE;
}

BOOL CSttTestAppConfigTool::Remote_ConnectServer()
{
	return TRUE;
}

BOOL CSttTestAppConfigTool::Remote_DisconnectServer()
{
	if (m_pClientEngine == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_pClientEngine == NULL"));
		return FALSE;
	}

	m_pClientEngine->DisConnect();

	return TRUE;
}

BOOL CSttTestAppConfigTool::Local_ConnectServer(CSttTestAppCfg *pSttTestAppCfg, const CString &strIP,long nPort
												,const CString &strIdSoft, CTestEventBaseInterface *pTestEventRcv)
{
	if (! pSttTestAppCfg->IsLocal())
	{
		FreeClientEngine();
	}

	pSttTestAppCfg->SetLocalApp();

	if (m_pClientEngine == NULL)
	{
		CSttClientTestEngine *pNew = new CSttClientTestEngine();
		pNew->AttatchSttTestMsgViewInterface(m_pSttTestMsgViewInterface);
		m_pClientEngine = pNew;

		if (pTestEventRcv != NULL)
		{
			m_pClientEngine->SetTestEventInterface(pTestEventRcv);
		}
	}

	BOOL bRet = m_pClientEngine->ConnectServer(strIP,nPort);

	if(!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Connect Server [%s] 失败"), strIP.GetString());
		return bRet;
	}

	//设置LocalIP
#ifdef _PSX_OS_CENTOS_
	m_pClientEngine->m_pSttClientSocket->SttXmdChAddr(pSttTestAppCfg->GetLocalIP()); //Centos下，是工控机，和Z7平台是分开的，无法直接通过获取主机IP的方式连接测试仪底层Server
#else
#ifdef _PSX_QT_LINUX_
    CString strMask;
    CString strChIP = m_pClientEngine->m_pSttClientSocket->SttXmdChAddr();
    stt_net_get_deviceip( strChIP, strMask);
#else
	m_pClientEngine->m_pSttClientSocket->SttXmdChAddr(pSttTestAppCfg->GetLocalIP());
#endif
#endif

#ifdef _PSX_QT_LINUX_
	m_pClientEngine->m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_NATIVE);
#else
	m_pClientEngine->m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_LOCAL);
#endif

	m_pClientEngine->m_pSttClientSocket->SetSocketType(STT_SOCKET_TYPE_LOCAL);

#ifdef STT_TEST_CMD_USE_RandomNum
	//ID_Tester改为随机数 2024-6-4
#ifdef _USE_IN_IED_QT5
	// 获取当前时间的时间戳（毫秒级）
	qint64 currentTimeMillis = QDateTime::currentMSecsSinceEpoch();

	// 使用时间戳作为随机数生成器的种子
	srand((unsigned int)currentTimeMillis);
#else
	srand((unsigned int)time(NULL));
#endif
	unsigned int nIDTester = rand();
	m_pClientEngine->m_oCurrUser.ID_Tester(nIDTester/*g_nIDTester*/);
#else
	m_pClientEngine->m_oCurrUser.ID_Tester(g_nIDTester);
#endif

	m_pClientEngine->m_oCurrUser.IP_User(m_pClientEngine->m_pSttClientSocket->SttXmdChAddr());
	m_pClientEngine->m_oCurrUser.Name_User(m_pClientEngine->m_pSttClientSocket->SttXmdChAddr());
	m_pClientEngine->m_oCurrUser.id_soft(strIdSoft);
#ifndef _PSX_QT_LINUX_
	m_pClientEngine->m_oCurrUser.SetLogInTime();//zhouhj 2024.5.13 传递登录时间
#endif

	if (g_nSttXcmdCh_Type != SttXcmdChType_AxAtsLib)
	{
		CSttCmdData oRetData;
		long nExecStatus = m_pClientEngine->System_Login(TRUE, &oRetData);

		if (nExecStatus != STT_CMD_ExecStatus_SUCCESS)
		{
			bRet = FALSE;
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Login失败"));
		}
	}

	return bRet;
}

BOOL CSttTestAppConfigTool::ConnectServer(CSttTestAppCfg *pSttTestAppCfg, const CString &strIP,long nPort)
{
	if (! pSttTestAppCfg->IsLocal())
	{
		FreeClientEngine();
	}

	pSttTestAppCfg->SetLocalApp();

	if (m_pClientEngine == NULL)
	{
		CSttClientTestEngine *pNew = new CSttClientTestEngine();
		pNew->AttatchSttTestMsgViewInterface(m_pSttTestMsgViewInterface);
		m_pClientEngine = pNew;
	}

	BOOL bRet = m_pClientEngine->ConnectServer(strIP,nPort);

	return bRet;
}

BOOL CSttTestAppConfigTool::Remote_ConnectServer(CSttTestAppCfg *pSttTestAppCfg, const CString &strIP,long nPort)
{
	if (pSttTestAppCfg->IsLocal())
	{
		FreeClientEngine();
	}

	pSttTestAppCfg->SetRemoteApp();

	if (m_pClientEngine == NULL)
	{
		CSttRemoteClientTestEngine *pNew = new CSttRemoteClientTestEngine();
		pNew->AttatchSttTestMsgViewInterface(m_pSttTestMsgViewInterface);
		m_pClientEngine = pNew;
	}

	BOOL bRet = m_pClientEngine->ConnectServer(strIP,nPort);

	return bRet;
}

BOOL CSttTestAppConfigTool::Remote_BindAndLogin(CSttTestAppCfg *pSttTestAppCfg, CSttTestRemoteRegister *pRegister,CSttTestClientUser *pUser)
{
	ASSERT(m_pClientEngine != NULL);
	ASSERT(pRegister != NULL);
	ASSERT(pUser != NULL);

	if (pSttTestAppCfg->IsLocal())
	{
		return FALSE;
	}

	long nExecStatus = m_pClientEngine->Remote_Bind(pRegister);
	if (nExecStatus != STT_CMD_ExecStatus_SUCCESS)
	{
		return FALSE;
	}

	m_pClientEngine->m_oCurrUser.DeleteAll();
	m_pClientEngine->m_oCurrUser.AppendEx(*pUser);
	pUser->RemoveAll();

	//设置LocalIP
	m_pClientEngine->m_pSttClientSocket->SttXmdChAddr(pSttTestAppCfg->GetLocalIP());

	m_pClientEngine->m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_REMOTE);
	m_pClientEngine->m_pSttClientSocket->SetSocketType(STT_SOCKET_TYPE_REMOTE);
	m_pClientEngine->m_oCurrUser.ID_Tester(g_nIDTester);
	m_pClientEngine->m_oCurrUser.IP_User(m_pClientEngine->m_pSttClientSocket->SttXmdChAddr());

	CSttCmdData oRetData;
	nExecStatus = m_pClientEngine->System_Login(TRUE, &oRetData);
	if (nExecStatus != STT_CMD_ExecStatus_SUCCESS)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttTestAppConfigTool::IsTestAppExist(CSttTestAppCfg *pSttTestAppCfg, CString &strErrorInfo)
{
#ifdef _PSX_QT_LINUX_
	return TRUE;
#else
	char* pszIP = NULL;
	CString strTestAppIP = pSttTestAppCfg->GetTestAppIP();
	CString_to_char(strTestAppIP,&pszIP);

	BOOL bConnect = xping(pszIP);
	delete pszIP;

	if (!bConnect)
	{
		strErrorInfo.Format(_T("测试仪：%s 网络连接不通！"),strTestAppIP.GetString());
		CLogPrint::LogString(XLOGLEVEL_DEBUG, strErrorInfo);
	}

	return bConnect;
#endif
}

BOOL CSttTestAppConfigTool::IsCloudServerExist(CSttTestAppCfg *pSttTestAppCfg)
{
	char* pszIP = NULL;
	CString strCloudIP = pSttTestAppCfg->GetCloudIP();
	CString_to_char(strCloudIP,&pszIP);

	BOOL bConnect = xping(pszIP);
	delete pszIP;

	if (!bConnect)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("云服务器：%s 网络连接不通！"),strCloudIP.GetString());
	}

	return bConnect;
}
