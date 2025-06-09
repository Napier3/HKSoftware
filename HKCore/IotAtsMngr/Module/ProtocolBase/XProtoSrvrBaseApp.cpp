#include "stdafx.h"
#include "XProtoSrvrBaseApp.h"
#include "../SttMqttClientEngineConfig.h"

#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../SttStudio/Module/SttCmd/SttCmdDefineGlobal.h"
#include "../ProtocolBase/Factory/EngineToPxFactory.h"
#include "../../../SttStudio/Module/SttTestBase/SttMacroXmlKeys.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  


CString g_strDvmFilePath = _T("");
CString g_strPpxmlFilePath = _T("");

CXProtoSrvrBaseApp *g_pProtoSvrBaseApp = NULL;

CXProtoSrvrBaseApp::CXProtoSrvrBaseApp()
{
	g_pProtoSvrBaseApp = this;
}

CXProtoSrvrBaseApp::~CXProtoSrvrBaseApp()
{

}

void CXProtoSrvrBaseApp::InitProtoSvrBaseApp()
{
	_P_InitSystemPath();
	CDataMngrXmlRWKeys::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CCfgDataMngrConstGlobal::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CEngineToPxFactory::Create();
	CSttCmdOverTimeTool::Create();
	CMacroXmlKeys::Create();

	//配置文件初始化
// 	CString strFile = _P_GetConfigPath();
// 	strFile += _T("SttMqttClientEngineCfg.xml");
	CString strFile;  //此处不赋值，则会调用默认的配置文件SttMqttClientEngineCfg.xml
	CSttMqttClientEngineConfig::Create(strFile);

	//规约引擎服务模型文件和规约模板文件管理路径
	InitGlobalFilePath();
}

void CXProtoSrvrBaseApp::ExitProtoSvrBaseApp()
{
	CMacroXmlKeys::Release();
	CEngineToPxFactory::Release();
	CSttMqttClientEngineConfig::Release();
	CSttCmdOverTimeTool::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CCfgDataMngrConstGlobal::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();

}

/*********************************
第一步：检查文件是否存在，若存在，则返回TRUE，若不存在，执行第二步
第二步：查询装置表，及规约引擎表，下载文件
***********************************/
BOOL CXProtoSrvrBaseApp::CheckDeviceInfo(const CString &strDeviceID
										,CString &strDvmFile,CString &strPpxmlFile)
{
	if (strDeviceID.IsEmpty() || strDvmFile.IsEmpty() || strPpxmlFile.IsEmpty())
	{
		return FALSE;
	}

	ASSERT(FALSE);

	return TRUE;
}

CExBaseObject* CXProtoSrvrBaseApp::FindDevice(const CString &strDeviceSN)
{
	CPxProtoDeviceBase *pFind = (CPxProtoDeviceBase*)m_listDevice.FindByID(strDeviceSN);
	return pFind;
}

CPxProtoDeviceBase* CXProtoSrvrBaseApp::AddDevice(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile)
{
	ASSERT (FALSE);

	return NULL;
}

void CXProtoSrvrBaseApp::InitGlobalFilePath()
{
	CString strRootPath = _P_GetInstallPath();
	
	g_strDvmFilePath = strRootPath + _T("e-Protocol\\Library\\");
	g_strPpxmlFilePath = strRootPath + _T("e-Protocol\\Template\\");
}
