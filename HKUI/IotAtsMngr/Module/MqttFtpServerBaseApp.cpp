#include "stdafx.h"
#include "MqttFtpServerBaseApp.h"
#include "../../SttStudio/Module/SttRegisterCode.h"
#include "SttMqttClientEngineConfig.h"
#include "../../Module/System/StringTokenizer.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  


CMqttFtpServerBaseApp::CMqttFtpServerBaseApp()
{

}

CMqttFtpServerBaseApp::~CMqttFtpServerBaseApp()
{

}

/*********************************
服务端订阅主题：
DstID/+[SrcID]/UploadCmd/UploadFileName
DstID/+[SrcID]/UploadCmd/UploadFileData
DstID/+[SrcID]/DownloadCmd/DownloadFileName
+[SrcID]/DstID/DownloadCmd/UploadFileName/Reply
+[SrcID]/DstID/DownloadCmd/UploadFileData/Reply
**********************************/
void CMqttFtpServerBaseApp::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{
	//根据主题
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	m_oMqttFileOptrMngr.CheckMqttFtpMsgRecv(oToken,pBuf,nLen);
}

void CMqttFtpServerBaseApp::OnMqttDisconnected(char *pszErr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:[ErrInfo=%s]"),pszErr);
}

BOOL CMqttFtpServerBaseApp::ConnectMqttServer()
{
	CString strIP,strClientID;
	long nPort = 0;
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);
	strClientID.Format(_T("MqttFtpServer_%d"),stt_GetMachineCode_U32());

	return CSttMqttClientTool::InitMqttClient(strIP,nPort,strClientID);
}

void CMqttFtpServerBaseApp::InitMqttFtpServerBaseApp()
{
	CDataMngrXmlRWKeys::Create();

	CString strFile = _P_GetConfigPath();
	strFile += _T("SttMqttClientEngineCfg.xml");
	CSttMqttClientEngineConfig::Create(strFile);

	CSttMqttClientTool::Create();
	CSttMqttClientTool::g_pSttMqttClientTool->AttachSttMqttMsgInterface(this);

	if (ConnectMqttServer())
	{
		long nQos = 0;
		CSttMqttClientEngineConfig::GetMqttDefualtQos(nQos);
		//订阅所有主题
		SubcribeMqttTopic(nQos);
	}
}

void CMqttFtpServerBaseApp::ExitMqttFtpServerBaseApp()
{
	CSttMqttClientTool::Release();
	CSttMqttClientEngineConfig::Release();

	CDataMngrXmlRWKeys::Release();
}

//启动后需要订阅的主题
BOOL CMqttFtpServerBaseApp::SubcribeMqttTopic(int nQos)
{
	m_oMqttFileOptrMngr.SubcribeFtpToic();

	return TRUE;
}