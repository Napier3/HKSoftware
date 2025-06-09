#include "stdafx.h"
#include "IotVmServer_Mqtt.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"
#include "IotVmServer_MqttClient.h"
#include "IotVmEngineServerBaseApp.h"
#include "IotVmDevice.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotVmServer_Mqtt::CIotVmServer_Mqtt()
{
	m_pXCommSvrWnd = NULL;
	m_pVmConfig = NULL;
}

CIotVmServer_Mqtt::~CIotVmServer_Mqtt()
{
	if (m_pXCommSvrWnd != NULL)
	{
		m_pXCommSvrWnd->KillTimer(WM_TIMER_ID_HEARTBEAT_TESTAPP);
		delete m_pXCommSvrWnd;
		m_pXCommSvrWnd = NULL;
	}

	if (m_pVmConfig != NULL)
	{
		delete m_pVmConfig;
		m_pVmConfig = NULL;
	}
}

void CIotVmServer_Mqtt::BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat)
{
	CSttTestCmd *pVmCmd = (CSttTestCmd *)pCmdBase;

	if (strFormat == MQTT_DATA_FORMAT_JSON)
	{
		pVmCmd->PraseCmdBuf(pBuf,nLen,NULL,MQTT_DATA_FORMAT_JSON);
	}
	else
	{
		//XML
		SetXmlBufferLen(nLen * 2);
		pVmCmd->PraseCmdBuf(pBuf,nLen,m_pszXmlBuffer,MQTT_DATA_FORMAT_XML);
	}
}

//mqtt连接断链事件
void CIotVmServer_Mqtt::OnClose(char *pszErr)
{
	FreePxCmmInterface();
	DeleteAll();
}


BOOL CIotVmServer_Mqtt::Init(const char *pszIP,long nPort)
{
	if (m_pXCommSvrWnd == NULL)
	{//创建消息窗口
		m_pXCommSvrWnd = new CXCommSvrWnd;
		m_pXCommSvrWnd->CreateXCommSvrWnd(this);
	}

	FreePxCmmInterface();
	OpenVmConfigFile();

	CIotVmServer_MqttClient *pProtocolMqttClient = new CIotVmServer_MqttClient();
	pProtocolMqttClient->m_pVmConfig = m_pVmConfig;
	BOOL bRet = pProtocolMqttClient->Connect(pszIP,nPort, "IotVmServer");

	if (bRet)
	{
		pProtocolMqttClient->SetMqttEngineRef(this);
		AttachPxCmmInterface(pProtocolMqttClient);

		m_pXCommSvrWnd->SetTimer(WM_TIMER_ID_HEARTBEAT_TESTAPP, 60000, NULL);
	}
	else
	{
		delete pProtocolMqttClient;
	}

	return bRet;
}

/************************
主题：测试服务端SN/TestCmd/CreateDevice
**************************/
long CIotVmServer_Mqtt::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	CXObjectRefDriver oDriver(CSttTestCmd::New);
	CSttTestCmd *pTestCmd = (CSttTestCmd*)oDriver.New();
	pTestCmd->SetSttCmmOptrInterface(pCmmOptrInterface);

	pTestCmd->m_strFromSN = strFromSN;
	BufToCmd(pTestCmd, pBuf, nLen, MQTT_DATA_FORMAT_XML);

	if(pTestCmd->m_strID == STT_CMD_TYPE_IOT_CreateDevice)
	{
		oDriver.AddRef();
		m_pXCommSvrWnd->PostMessage(XCOMM_WND_MSG,0,(LPARAM)pTestCmd);	
	}
	else if (pTestCmd->m_strID == STT_CMD_TYPE_IOT_CloseDevice)
	{
		CIotVmProtoToXImp *pIotVmProtocolXImp = (CIotVmProtoToXImp *)FindByID(strFromSN);

		if (pIotVmProtocolXImp != NULL)
		{
			m_pXCommSvrWnd->PostMessage(XCOMM_WND_MSG,1,(LPARAM)pIotVmProtocolXImp);
		}		
	}

	return 0;
}

void CIotVmServer_Mqtt::OnXTimer(UINT nIDEvent)
{
	if (nIDEvent == WM_TIMER_ID_HEARTBEAT_TESTAPP)
	{
		SendHeartBeat();
	}
}
//XCOMM_WND_MSG
//创建IotVmProtocolServer模块消息处理逻辑
void CIotVmServer_Mqtt::OnXCommMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1)
	{//发消息删除IotEngineProtocolServer模块

		//延时5S，保证CloseDevice命令、终止上送实时数据等、处理完成
		CTickCount32 oTick;
		oTick.DoEvents(5000);

		CIotVmProtoToXImp *pIotVmProtocolXImp = (CIotVmProtoToXImp *)lParam;
		pIotVmProtocolXImp->Disconnect();
		//pIotVmProtocolXImp->OnClose(NULL);
		pIotVmProtocolXImp->FreePxCmmInterface();
		Delete(pIotVmProtocolXImp);

		return;
	}

	CXObjectRefDriver oDriver((CSttTestCmd*)lParam);
	CSttTestCmd *pTestCmd = (CSttTestCmd*)oDriver.GetXObjectRef();

	//发消息创建IotEngineProtocolServer模块

	if (pTestCmd == NULL)
	{
		return;
	}

	CString strDeviceID;
	pTestCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);

	long nExecStatus = STT_CMD_ExecStatus_SUCCESS;

	//创建IotEngineProtocolServer模块
	if (!CreateIotVmProtoToXImp(*pTestCmd))
	{
		//调试用  注释此处
		nExecStatus = STT_CMD_ExecStatus_FAILURE;
	}

	//返回Reply应答
	CSttSysState oSysState;
	CSttParas *pParas = oSysState.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	ReturnSysState_REPLY((CSttCmmOptrInterface *)pTestCmd->GetSttCmmOptrInterface(), nExecStatus, &oSysState, STT_CMD_TYPE_ATS_CreateDevice, STT_CMD_SYSSTATE_TEST);

	//ReturnSysState(pTestCmd,nExecStatus,strDeviceID);
}

void CIotVmServer_Mqtt::OnClseDevice(CIotVmProtoToXImp *pIotVmProtocolXImp)
{
	if (m_pXCommSvrWnd != NULL)
	{
		m_pXCommSvrWnd->PostMessage(XCOMM_WND_MSG,1,(LPARAM)pIotVmProtocolXImp);
	}
}

BOOL CIotVmServer_Mqtt::OpenVmConfigFile()
{
	if (m_pVmConfig != NULL)
	{
		delete m_pVmConfig; 
		m_pVmConfig = NULL;
	}

	CString strFilePath;
	strFilePath = _P_GetConfigPath();
	strFilePath += FILE_VM_CONFIG;

	if (!IsFileExist(strFilePath))
	{
		return FALSE;
	}

	m_pVmConfig = new CDataGroup();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = m_pVmConfig->OpenXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	return bRet;
}

BOOL CIotVmServer_Mqtt::CreateIotVmProtoToXImp(CSttTestCmd &oTestCmd)
{
	//创建IotVmProtocolServer接口
	CString strDeviceSN;
	oTestCmd.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

	CIotVmProtoToXImp *pFind = (CIotVmProtoToXImp *)FindByID(strDeviceSN);

	if (pFind != NULL)
	{
		//若该装置对应的IotEngineProtocolServer已经创建，
		//则需要取消之前订阅的主题，订阅新的主题，因为请求端SN已改变
		//pFind->ReSubcribeMqttTopic();
		return TRUE;
	}

	//若该装置对应的IotEngineProtocolServer模块不存在，则创建并初始化

	pFind = new CIotVmProtoToXImp(this);
	pFind->m_strID = strDeviceSN;

	//初始化IotEngineProtocolServer接口Mqtt客户端模块
	BOOL bRet = pFind->Init(m_strIP,m_nPort);

	if(bRet)
	{
		//创建协议转换模块和协议服务模块
		if (pFind->CreateProtocol(oTestCmd))
		{
			//将IotEngineProtocolServer模块添加到子对象链表中
			AddNewChild(pFind);
		}
		else
		{
			delete pFind;
			bRet = FALSE;
		}	
	}
	else
	{
		delete pFind;
	}

	return bRet;
}

void CIotVmServer_Mqtt::SendHeartBeat()
{
	if (GetPxCmmOptrInterface() == NULL)
	{
		return;
	}

	CIotVmProtoToXImp *pDevice = NULL;
	POS pos = GetHeadPosition();

	CDataGroup oGroup;
	CString strXML;
	CString strTopic;

	while (pos != NULL)
	{
		pDevice = (CIotVmProtoToXImp *)GetNext(pos);
		oGroup.AddNewData(STT_CMD_PARA_DeviceSN, pDevice->m_strID);
		oGroup.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXML);
		strTopic.Format(_T("%s/HeartBeat"), pDevice->m_strID);
		GetPxCmmOptrInterface()->Send(const_cast<char*>(strXML.GetString()), 
			strXML.GetLength(), strTopic);
		oGroup.DeleteAll();
	}
}