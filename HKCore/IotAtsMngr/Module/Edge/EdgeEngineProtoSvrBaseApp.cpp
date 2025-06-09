#include "stdafx.h"
#include "EdgeEngineProtoSvrBaseApp.h"
#include "../SttMqttClientEngineConfig.h"

#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../SttStudio/Module/SttCmd/SttCmdDefineGlobal.h"
#include "../ProtocolBase/Factory/EngineToPxFactory.h"
#include "IotEngineToEdgeV4.h"
#include "IotEngineToEdgeV5.h"
#include "EdgeProtoDevice.h"
#include "EdgeCmd/EdgeAuth.h"
#include "EdgeEngineServerCfg.h"
#include "../../../Module/mosquitto-1.4.8/src/Mosquitto_Process.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CEdgeEngineProtoSvrBaseApp *g_pEdgeEngineProtoSvrBaseApp = NULL;

CEdgeEngineProtoSvrBaseApp::CEdgeEngineProtoSvrBaseApp()
{
	m_listDevice.m_strName = _T("���豸����");
	m_listDevice.m_strID = _T("EdgeDeviceMngr");
	m_bViewMode = FALSE;
	m_bLocalMode = FALSE;
	m_pEdgeServerView = 0;
	m_pMqttServerView = 0;
	m_nState = STATE_NONE;
}

CEdgeEngineProtoSvrBaseApp::~CEdgeEngineProtoSvrBaseApp()
{

}

static CIotEngineToPxBase* edge_CreateEngineToPx(CMqttEngineBase_Stt *pServer, CSttCmdBase *pCmd)
{
	CIotEngineProtocolServer *pIotEngineProtocolServer = (CIotEngineProtocolServer*)pServer;
	CString strDeviceID,strPpxml,strDvmFile,strCmmCfgFile;
	pCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);
	pCmd->GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpxml);//��Լ�ļ��ֶΣ�������ͬת��ģ��
	strPpxml.MakeUpper();
	pCmd->GetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);
	pCmd->GetParasDataValueByID(XPARA_ID_CommCfgFile, strCmmCfgFile);

	CIotEngineToPxBase* pIotEngineToPx = NULL;

	CEdgeProtoDevice *pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->FindDevice(strDeviceID);

	if (pDevice == NULL)
	{
		pDevice = new CEdgeProtoDevice();
		g_pEdgeEngineProtoSvrBaseApp->m_listDevice.AddTail(pDevice);
	}

	//ȡ�ö��ڱ��豸��˵��iotengine��SN�����Զ��ϱ�
	pDevice->m_strIotEngineSN = pCmd->m_strFromSN; 

	//2021-8-22  lijunqing  ��ʼ��װ�ù����Ĺ�Լ������Ѿ��������򲻴���
	pDevice->InitProtocol(strDeviceID, strDvmFile, strPpxml, _T(""), NULL);

	//2021-8-22  lijunqing  ������Լת�����󣬴����Ѿ������Ĺ�Լ����
	if (strPpxml == ENGINE_TO_PX_EDGEV4)
	{
		pIotEngineToPx = CIotEngineToEdgeV4::CreateEngineToPx(pDevice->m_pPxProtocol);
	}
	else if (strPpxml == ENGINE_TO_PX_EDGEV5)
	{
		pIotEngineToPx = CIotEngineToEdgeV5::CreateEngineToPx(pDevice->m_pPxProtocol);
	}

	if (pIotEngineToPx == NULL)
	{
		return NULL;
	}

	CDataGroup *pCfgGroup = NULL;
	CSttParas* pParas = pCmd->GetSttParas();
	pCfgGroup = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_CommConfig);
	pIotEngineToPx->ConfigMqttProtocol(strDeviceID,strDvmFile,strPpxml,strCmmCfgFile,pCfgGroup);
	pIotEngineToPx->SetIotEngineProtocolServer(pIotEngineProtocolServer);

	pIotEngineToPx->InitMqttProtocol(pServer->m_strIP,pServer->m_nPort);

	return pIotEngineToPx;
}

void CEdgeEngineProtoSvrBaseApp::InitProtoSvrBaseApp()
{
	CXEngineProtoSrvrBaseApp::InitProtoSvrBaseApp();
	CEdgeCmdMngrXmlRWKeys::Create();
	//CEdgeEngineServerConfig::Create();

	//ע��Э��ת��ģ��
	//2021-8-19  lijunqing
// 	CEngineToPxFactory::RegisterEngineToPx(ENGINE_TO_PX_EDGEV4,CIotEngineToEdgeV4::CreateEngineToPx);
//	CEngineToPxFactory::RegisterEngineToPx(ENGINE_TO_PX_EDGEV5,CIotEngineToEdgeV5::CreateEngineToPx);
	CEngineToPxFactory::RegisterEngineToPx(ENGINE_TO_PX_EDGEV4,edge_CreateEngineToPx);
	CEngineToPxFactory::RegisterEngineToPx(ENGINE_TO_PX_EDGEV5,edge_CreateEngineToPx);

	CString strIP;
	long nPort = 0;
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);

	CString strMySqlIP, strMySqlPassword;
	long nMySqlPort;
	CSttMqttClientEngineConfig::GetMysqlServerIP(strMySqlIP);
	CSttMqttClientEngineConfig::GetMysqlServerPort(nMySqlPort);
	CSttMqttClientEngineConfig::GetMysqlServerPassword(strMySqlPassword);

	//yzj 2021-9-25 ���ڱ��豸��֤
	CDBServerInfoBase oDBServerInfo;
	oDBServerInfo.m_strDbName = _T("tyh");//���ݿ�����
	oDBServerInfo.m_strUserName = _T("root");
	oDBServerInfo.m_strPasswd = strMySqlPassword;
	oDBServerInfo.m_strHostIp = strMySqlIP;
	oDBServerInfo.m_iPort = nMySqlPort;
	oDBServerInfo.m_strEncoding = _T("utf8mb4");
	InitMySqlDB(oDBServerInfo);

	m_oIotEdgeMqttServer.Init(strIP,nPort);
}

void CEdgeEngineProtoSvrBaseApp::ExitProtoSvrBaseApp()
{
	m_oIotEdgeMqttServer.Disconnect();
	DisconnectDB();
	//CEdgeEngineServerConfig::Release();
	CEdgeCmdMngrXmlRWKeys::Release();
	CXEngineProtoSrvrBaseApp::ExitProtoSvrBaseApp();
}

BOOL CEdgeEngineProtoSvrBaseApp::CheckDeviceInfo(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile)
{
	if (strDeviceID.IsEmpty() || strDvmFile.IsEmpty())
	{
		return FALSE;
	}

	strDvmFile = GetFileNameFromFilePath(strDvmFile);
	strDvmFile = g_strDvmFilePath + strDvmFile;
	return IsFileExist(strDvmFile);
}

CExBaseObject* CEdgeEngineProtoSvrBaseApp::FindDevice(const CString &strDeviceSN)
{
	//�ж�BaseApp��װ���б��Ƿ���ڣ������ڷ���ʧ��
	return g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(strDeviceSN);
}

void CEdgeEngineProtoSvrBaseApp::CloseDevice(const CString& strDeviceSN)
{
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)m_listDevice.FindByID(strDeviceSN);
	pDevice->m_pPxProtocol = NULL;
	//pDevice->CloseDevice();
	//m_listDevice.DeleteByID(strDeviceSN);
}
void CEdgeEngineProtoSvrBaseApp::SetMsgWnd(const HWND hWnd)
{
	// ����һ��ȫ�ֵ�HWND����,ʹMqtt�����֪���ͻ���������Ҫ���ĸ����ڽ���ת��
	Mosquitto_SetMsgWnd(hWnd);
}

void CEdgeEngineProtoSvrBaseApp::UpdateCurrentView()
{

}
