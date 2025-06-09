#include "stdafx.h"
#include "XEngineProtoSrvrBaseApp.h"
#include "../SttMqttClientEngineConfig.h"

#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../SttStudio/Module/SttCmd/SttCmdDefineGlobal.h"
#include "../ProtocolBase/Factory/EngineToPxFactory.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  


CXEngineProtoSrvrBaseApp *g_pEngineProtoSvrBaseApp = NULL;

CXEngineProtoSrvrBaseApp::CXEngineProtoSrvrBaseApp()
{
	g_pEngineProtoSvrBaseApp = this;
}

CXEngineProtoSrvrBaseApp::~CXEngineProtoSrvrBaseApp()
{

}

void CXEngineProtoSrvrBaseApp::InitProtoSvrBaseApp()
{
	CXProtoSrvrBaseApp::InitProtoSvrBaseApp();

	CString strIP;
	long nPort = 0;
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);

	//����Mqtt�ͻ���ģ���ʼ�������ӷ������Ͷ������⡿
	m_oIotEngineMqttServer.Init(strIP,nPort);
}

void CXEngineProtoSrvrBaseApp::ExitProtoSvrBaseApp()
{
	CXProtoSrvrBaseApp::ExitProtoSvrBaseApp();
}
