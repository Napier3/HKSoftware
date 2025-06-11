#include "stdafx.h"
#include "BigComtradeTransPlay.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../Engine/SttClientTestEngine.h"

#ifdef _PSX_QT_LINUX_
  #include <pthread.h> //线程头文件
#include "../API/NetworkInterface.h"
#endif

CBigComtradeTransPlay *g_theBigComtradeTransPlay;

CBigComtradeTransPlay* CBigComtradeTransPlay::g_pBigComtradeTransPlay = NULL;
long CBigComtradeTransPlay::g_nBigComtradeTransPlay = 0;

void CBigComtradeTransPlay::Create()
{
	g_nBigComtradeTransPlay++;

	if (g_nBigComtradeTransPlay == 1)
	{
		g_pBigComtradeTransPlay = new CBigComtradeTransPlay();

		g_pBigComtradeTransPlay->m_bUseExternSttTestAppCfg = FALSE;
		g_pBigComtradeTransPlay->m_pSttTestAppCfg = new CSttTestAppCfg;
		g_pBigComtradeTransPlay->m_pSttTestAppCfg->SttOpen(_T(""));
		g_theBigComtradeTransPlay = g_pBigComtradeTransPlay;
	}
}

void CBigComtradeTransPlay::Create(CSttTestAppCfg *pSttTestAppCfg)
{
	g_nBigComtradeTransPlay++;

	if (g_nBigComtradeTransPlay == 1)
	{
		g_pBigComtradeTransPlay = new CBigComtradeTransPlay();

		if (pSttTestAppCfg != NULL)
		{
			g_pBigComtradeTransPlay->m_bUseExternSttTestAppCfg = TRUE;
			g_pBigComtradeTransPlay->m_pSttTestAppCfg = pSttTestAppCfg;
		}
		else
		{
			g_pBigComtradeTransPlay->m_bUseExternSttTestAppCfg = FALSE;
			g_pBigComtradeTransPlay->m_pSttTestAppCfg = new CSttTestAppCfg;
			g_pBigComtradeTransPlay->m_pSttTestAppCfg->SttOpen(_T(""));
		}
		
		g_theBigComtradeTransPlay = g_pBigComtradeTransPlay;
	}
}

void CBigComtradeTransPlay::Release()
{
	g_nBigComtradeTransPlay--;

	if (g_nBigComtradeTransPlay == 0)
	{
		delete g_pBigComtradeTransPlay;
		g_pBigComtradeTransPlay = NULL;
		g_theBigComtradeTransPlay = NULL;
	}
}

CBigComtradeTransPlay::CBigComtradeTransPlay()
{
	m_pSttTestAppCfg = NULL;
	m_bUseExternSttTestAppCfg = FALSE;
	m_bDrawSrcComtrade = FALSE;
	m_bExitThread = TRUE;
	m_pSttComtradeFileReadThread = NULL;
	m_pTestEngineClientData = NULL;
	m_bUseConnectServer = TRUE;

	//初始化AB缓存
	CComtradeBufMngr::Create(COMTRADE_LOOPBUF_SIZE,COMTRADE_ABBUF_SIZE);
	m_oComtradeSendSocket.m_pbAnalysisFinish = &m_oBigComtradeFileRead.m_bAnalysisFinish;
}

CBigComtradeTransPlay::~CBigComtradeTransPlay()
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

long CBigComtradeTransPlay::GetPlaySampleRate()
{
	return m_oBigComtradeFileRead.m_dInsertFreq;
}

void CBigComtradeTransPlay::WaitForThreadExit()
{
	CTickCount32 oTick;

	while(m_pSttComtradeFileReadThread != NULL)
	{
		oTick.DoEvents(5);
	}
}

CExBaseList *CBigComtradeTransPlay::GetAnalogs()
{
	return m_oBigComtradeFileRead.m_oSrcComtradeFile.GetAnalogs();
}

CExBaseList *CBigComtradeTransPlay::GetRates()
{
	return m_oBigComtradeFileRead.m_oSrcComtradeFile.GetRates();
}

CExBaseList * CBigComtradeTransPlay::GetBinarys()
{
	return m_oBigComtradeFileRead.m_oSrcComtradeFile.GetBinarys();
}

BOOL CBigComtradeTransPlay::ConnectServerState()
{
	return m_oComtradeClientSocket.ConnectServer();
}

BOOL CBigComtradeTransPlay::CreateSttComtradeSocket()
{
	if (m_oComtradeSendSocket.IsSocketValid())//2023.6.26 zhouhj 如果录波通道Socket有效,则不需要重新创建
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
		m_bUseConnectServer = false;
		return FALSE;
	}

	BOOL bRet = m_oComtradeClientSocket.ConnectServer(m_pSttTestAppCfg->GetTestAppIP(), STT_PORT_COMTRADE_SERVER/*g_oSttTestAppCfg.GetTestServerPort()*/);

	if(!bRet)
	{
		m_bUseConnectServer = false;
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("连接测试仪【%s,%d】失败"),m_pSttTestAppCfg->GetTestAppIP().GetString(), STT_PORT_COMTRADE_SERVER);
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("连接测试仪【%s,%d】成功"),m_pSttTestAppCfg->GetTestAppIP().GetString(), STT_PORT_COMTRADE_SERVER);

	CSttSystemCmd oSysCmd;
	oSysCmd.m_strID = STT_CMD_TYPE_SYSTEM_Login;
	oSysCmd.m_strTestor = STT_SOFT_ID_COMTRADE;

	
	long nRet = m_oComtradeClientSocket.SendCmd(&oSysCmd);

	if (!nRet)
	{
		m_bUseConnectServer = false;
		return FALSE;
	}
	m_oComtradeSendSocket.AttatchClientTestEngine(m_pTestEngineClientData);
	m_oComtradeSendSocket.AttatchSocketDatabase(&m_oComtradeClientSocket);
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("连接完成，准备开始测试......"));
	return TRUE;
}

BOOL CBigComtradeTransPlay::UpdateChMapConfig()
{
	CString strPath = _P_GetConfigPath();
	strPath += _T("ComtradeReplayConfig.xml");
	
	BOOL bRet = m_oComtradePlayConfig.Open(strPath,m_oBigComtradeFileRead.m_dInsertFreq);
	return bRet;
}

BOOL CBigComtradeTransPlay::SaveComtradeReplayConfig(const CString &strFile)
{
	m_oComtradePlayConfig.m_strID = m_oBigComtradeFileRead.m_oSrcComtradeFile.m_strComtradeFile;
	return m_oComtradePlayConfig.Save(strFile,m_oBigComtradeFileRead.m_dInsertFreq);
}

BOOL CBigComtradeTransPlay::OnOpenComtradeFile(const CString &strComtradeFile,BOOL bInitDefault)
{
	if (!m_oBigComtradeFileRead.CheckComtradeFile(strComtradeFile))
	{//检查Comtrade文件是否正确
		return FALSE;
	}

	//重新初始化AB缓存
	CComtradeBufMngr::g_pComtradeBufMngr->ResetBuf();

	//根据配置参数、缓存大小计算缓存中能存的最大点数,分配回放用数据缓存
	m_oComtradePlayConfig.InitReplayBuf(FILE_READBUF_SIZE);

// 	if (bInitDefault&&m_oBigComtradeFileRead.GetAutoGenChABMap())
// 	{
// 		m_oComtradePlayConfig.InitDefault(FALSE);//只初始化模块参数及通道相关参数
// 	}
// 	else if(bInitDefault == TRUE)
// 	{
// 		m_oComtradePlayConfig.InitDefault(TRUE);
// 	}
	if (bInitDefault) 
	{
		m_oComtradePlayConfig.InitDefault(TRUE);
	} 
	else
	{
		bool bAutoGenChABMap = m_oBigComtradeFileRead.GetAutoGenChABMap();
		m_oComtradePlayConfig.InitDefault(!bAutoGenChABMap); // 如果自动生成映射，则传 FALSE，否则传 TRUE	
	}

	//初始化Comtrade 相关缓存
	m_oBigComtradeFileRead.AttachComtradePlayConfig(&m_oComtradePlayConfig);
	return m_oBigComtradeFileRead.OpenComtradeFile(strComtradeFile,FILE_READBUF_SIZE,bInitDefault);
}

//2021-9-19  lijunqing  是否有波形数据需要绘图
BOOL CBigComtradeTransPlay::HasComtradeDataNeedDraw()
{
	return m_oBigComtradeFileRead.m_oSrcComtradeFile.GetTotalPoints() > 0;
}

//2021-9-20  lijunqing
CRcdComtradeFile* CBigComtradeTransPlay::GetSrcComtradeFile()
{
	return &m_oBigComtradeFileRead.m_oSrcComtradeFile;
}
CRcdComtradeFile* CBigComtradeTransPlay::GetPlayComtradeFile()
{
	return &m_oBigComtradeFileRead.m_oSrcComtradeFile;
}

void CBigComtradeTransPlay::GenerateComtradeChDatas(BOOL bSeekToBegin)
{
	m_oBigComtradeFileRead.GenerateComtradeChDatas(bSeekToBegin);
}

void CBigComtradeTransPlay::OnStartTest()
{//开始测试，创建解析线程
	OnStopTest();

// #ifdef _Stt_Cmtrd_Save_File_
// 
// 	CString strFile = g_strFtpRootFile + _T("sttComtrade_local.txt");
// 	OpenCmtrdSaveFile(strFile);
// 
// #endif

	CTickCount32 oTick;
	//开始重新填充Loop，A,B
	m_oBigComtradeFileRead.BeginGenerateComtradeBuf(FALSE);

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("BeginGenerateComtradeBuf 耗时[%dms]"),oTick.GetTickCountLong());
	
#ifdef _PSX_QT_LINUX_
    pthread_create((pthread_t*)&m_pSttComtradeFileReadThread,NULL,SttComtradeFileReadThread,(LPVOID)this );
#else
    m_pSttComtradeFileReadThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttComtradeFileReadThread,(LPVOID)this,0,NULL);
#endif
}

void CBigComtradeTransPlay::OnStopTest()
{
	m_bExitThread = TRUE;
	WaitForThreadExit();
//	FreeClientEngine();
}

//收到请求数据命令
long CBigComtradeTransPlay::OnProcessComtradeRequstData(long nIndex)
{
	m_oComtradeSendSocket.SetCurrSendDataIndex(nIndex);

	return 1;
}

long CBigComtradeTransPlay::OnProcessComtradeSendDataStartAck(long nIndex)
{
	m_oComtradeSendSocket.SetSendDataStartAck();

	return 1;
}

//开始测试时创建解析文件线程
#ifdef _PSX_QT_LINUX_
void* CBigComtradeTransPlay::SttComtradeFileReadThread(LPVOID pParam)
#else
UINT CBigComtradeTransPlay::SttComtradeFileReadThread(LPVOID pParam)
#endif
{
	CBigComtradeTransPlay *pReplay = (CBigComtradeTransPlay*)pParam;
	pReplay->m_bExitThread = FALSE;

	while(!pReplay->m_oBigComtradeFileRead.IsAnalysisFinish())
	{
		if (pReplay->m_bExitThread)
		{
			break;
		}

		//查询空缓存
		int nIndex = CComtradeBufMngr::g_pComtradeBufMngr->GetABBufIndexCanWrite();

		if (nIndex <= 0)
		{
			Sleep(1);
			continue;
		}

		pReplay->m_oBigComtradeFileRead.GenerateABBuf(nIndex);
	}

	pReplay->m_bExitThread = TRUE;
	pReplay->m_pSttComtradeFileReadThread = NULL;
#ifndef _PSX_QT_LINUX_
	return 1;
#endif
}

BOOL CBigComtradeTransPlay::ComtradeControl_ConnServer(const CString &strIP)
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Connect Server [%s] [%d] failed"), strIP.GetString(),STT_PORT_COMTRADE_SERVER);
		return bRet;
	}

	//设置LocalIP
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Login失败"));
	}

	if(bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "测试仪连接录波通道成功");
		m_pTestEngineClientData->SetTestEventInterface(this);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "连接测试仪录波通道失败，请检查网络链路是否连通，IP地址及端口配置是否正确；然后点击网络连接按钮重新连接");
	}

	return bRet;
}

void CBigComtradeTransPlay::FreeClientEngine()
{
	if(m_pTestEngineClientData != NULL)
	{
//		m_pTestEngineClientData->DisConnect();
		m_pTestEngineClientData->PrepareFreeClientEngine();

		delete m_pTestEngineClientData;
		m_pTestEngineClientData = NULL;
	}
}

long CBigComtradeTransPlay::Event_OnProcessComtradeRequstData(long nIndex)
{
	return OnProcessComtradeRequstData(nIndex);
}

long CBigComtradeTransPlay::Event_OnProcessComtradeSendDataStartAck(long nIndex)
{
	return OnProcessComtradeSendDataStartAck(nIndex);
}



