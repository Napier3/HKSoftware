#include "stdafx.h"
#include "SttPpEngineServer.h"

#include "SttPpServerSocket.h"
#include "../../SttTestAppConfig/SttTestAppCfg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttPpEngineServer* CSttPpEngineServer::g_pSttPpEngineServer = NULL;
long CSttPpEngineServer::g_nSttPpEngineServerRef = 0;

//监视服务端所有的命令报文
extern long g_nSttLogServerSpyAllCmd;

CSttPpEngineServer::CSttPpEngineServer()
{

}

CSttPpEngineServer::~CSttPpEngineServer()
{	

}

CSttPpEngineServer* CSttPpEngineServer::Create()
{
	CSttTestAppCfg oSttTestAppCfg; 
	oSttTestAppCfg.SttOpen(_T("SttPpEngineServerConfig.xml"));

	CString strIP = oSttTestAppCfg.GetLocalIP();
	CLogPrint::LogString(XLOGLEVEL_TRACE, strIP);

	CSttPpEngineServer *pRet = Create(const_cast<char*>(strIP.GetString()), 19821);

	return pRet;
}

CSttPpEngineServer* CSttPpEngineServer::Create(char *pszIP, int nPort)
{
	g_nSttPpEngineServerRef++;

	if (g_nSttPpEngineServerRef == 1)
	{
		g_pSttPpEngineServer = new CSttPpEngineServer();
		g_pSttPpEngineServer->InitSttServerEngine(pszIP, nPort);
	}

	return g_pSttPpEngineServer;
}

void CSttPpEngineServer::Release()
{
	g_nSttPpEngineServerRef--;

	if (g_nSttPpEngineServerRef == 0)
	{
		g_pSttPpEngineServer->ExitSttServerEngine();
		delete g_pSttPpEngineServer;
		g_pSttPpEngineServer = NULL;
	}
}

void CSttPpEngineServer::OnTimer()
{

}

void CSttPpEngineServer::InitSttServerEngine(const char *pszIP, int nPort,int nReplayPort)
{
    m_pServerSocket=new CSttPpServerSocket;
    m_pServerSocket->m_nMaxClientCount=5;
    
	if (m_pServerSocket->CreateServer(pszIP,nPort))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CreateServer [%s]  [%d] Success"), pszIP, nPort);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CreateServer [%s]  [%d] Failed"), pszIP, nPort);
	}

    m_pServerSocket->AttachCmdOverTimeMsgRcv(this);
    m_pServerSocket->SetTestEngine(this);
}

//2020-4-6  lijq
//如果没有这部分，Server的Accept线程无法退出
void CSttPpEngineServer::ExitSttServerEngine()
{
    if (m_pServerSocket != NULL)
    {
        m_pServerSocket->CloseSttServer();
        delete m_pServerSocket;
        m_pServerSocket = NULL;
    }
}
