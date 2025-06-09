#include "stdafx.h"
#include "SttCloudSvrBaseApp.h"

#include "../../Module/Cloud/DB/RemoteCtrlMngrGlobal.h"
#include "../../Module/Cloud/DB/SttRemoteCtrlDbRWTool.h"
#include "../../Module/SttSocket/Cloud/SttCloudServerSocketBase.h"
#include "../../Module/SttCmd/SttCmdDefineGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttCloudSvrBaseApp *g_theSttCloudSvrApp = NULL;


CSttCloudSvrBaseApp::CSttCloudSvrBaseApp()
{
	g_theSttCloudSvrApp = this;
}

CSttCloudSvrBaseApp::~CSttCloudSvrBaseApp()
{

}

void CSttCloudSvrBaseApp::InitSttCloudSvrBaseApp()
{
	CCfgDataMngrXmlRWKeys::Create();
	CDataMngrXmlRWKeys::Create();
	CRemoteCtrlMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CSttCloudServerConfig::Create();

#ifdef _DBLIB_USE_SHAREMEM_	
	//数据库共享内存初始化
	InitSerializeSmBuffer();
#endif

	CDBServerInfoBase oServerInfo;
	oServerInfo.m_strHostIp = _T("127.0.0.1");
	oServerInfo.m_strDbName = _T("Stt_RemoteMngr");
	oServerInfo.m_strUserName = _T("root");
	oServerInfo.m_strPasswd = _T("123456");
	oServerInfo.m_iPort = CSttCloudServerConfig::GetMysqlPort();
	InitMySqlDB(oServerInfo);

	//清空实时表
	Stt_DeleteAllRealTimeDB(g_pTheMySqlApp,CRemoteCtrlMngrXmlRWKeys::g_pXmlKeys);

	m_oSttCloudServerSocket.CreateServer(CSttCloudServerConfig::GetSvrIP().GetString(),STT_PORT_CLOUD_SERVER);
}

void CSttCloudSvrBaseApp::ExitSttCloudSvrBaseApp()
{
	CRemoteCtrlMngrXmlRWKeys::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CSttCloudServerConfig::Release();
	CDataMngrXmlRWKeys::Release();
	CCfgDataMngrXmlRWKeys::Release();

#ifdef _DBLIB_USE_SHAREMEM_	
	ExitSerializeSmBuffer();
#endif

	//断开连接
	DisconnectDB();
}