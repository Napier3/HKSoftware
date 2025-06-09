#include "stdafx.h"
#include "IotVmEngineServerBaseApp.h"
#include "../SttMqttClientEngineConfig.h"

#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../SttStudio/Module/SttCmd/SttCmdDefineGlobal.h"
#include "../ProtocolBase/Factory/EngineToPxFactory.h"
#include "IotVmDevice.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotVmEngineServerBaseApp *g_pVmEngineProtoSvrBaseApp = NULL;

CIotVmEngineServerBaseApp::CIotVmEngineServerBaseApp()
{
	m_listDevice.m_strName = _T("测试仪管理");
	m_listDevice.m_strID = _T("TestAppDeviceMngr");
}

CIotVmEngineServerBaseApp::~CIotVmEngineServerBaseApp()
{

}

void CIotVmEngineServerBaseApp::InitProtoSvrBaseApp()
{
	CXProtoSrvrBaseApp::InitProtoSvrBaseApp();
	CSttCmdOverTimeTool::Create();

	//注册协议转换模块
	//2021-8-19  lijunqing
	//CEngineToPxFactory::RegisterEngineToPx(ENGINE_TO_PX_EDGEV4,edge_CreateEngineToPx);
	//CEngineToPxFactory::RegisterEngineToPx(ENGINE_TO_PX_EDGEV5,edge_CreateEngineToPx);

	CString strIP;
	long nPort = 0;
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);

	m_oIotVmServer_Mqtt.Init(strIP,nPort);
}

void CIotVmEngineServerBaseApp::ExitProtoSvrBaseApp()
{
	CXProtoSrvrBaseApp::ExitProtoSvrBaseApp();
	CSttCmdOverTimeTool::Release();
}

BOOL CIotVmEngineServerBaseApp::CheckDeviceInfo(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile)
{
	if (strDeviceID.IsEmpty() || strDvmFile.IsEmpty())
	{
		return FALSE;
	}

	strDvmFile = GetFileNameFromFilePath(strDvmFile);
	strDvmFile = g_strDvmFilePath + strDvmFile;
	return IsFileExist(strDvmFile);
}

CExBaseObject* CIotVmEngineServerBaseApp::FindDevice(const CString &strDeviceSN)
{
	//判断BaseApp中装置列表，是否存在，不存在返回失败
	return g_pVmEngineProtoSvrBaseApp->m_listDevice.FindByID(strDeviceSN);
}

