#include "stdafx.h"
#include "IotEdgeServer_Mqtt.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"
#include "IotEdgeServer_MqttClient.h"
#include "EdgeEngineProtoSvrBaseApp.h"
#include "EdgeProtoDevice.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEdgeServer_Mqtt::CIotEdgeServer_Mqtt()
{

}

CIotEdgeServer_Mqtt::~CIotEdgeServer_Mqtt()
{
	
}

BOOL CIotEdgeServer_Mqtt::Init(const char *pszIP,long nPort)
{
	FreePxCmmInterface();

	CIotEdgeServer_MqttClient *pProtocolMqttClient = new CIotEdgeServer_MqttClient();
	BOOL bRet = pProtocolMqttClient->Connect(pszIP,nPort, "IotEdgeServer");

	if (bRet)
	{
		pProtocolMqttClient->SetMqttEngineRef(this);
		AttachPxCmmInterface(pProtocolMqttClient);
	}
	else
	{
		delete pProtocolMqttClient;
	}

	return bRet;
}

/************************
�������⣺������롢�����Ͽ�
/v1/{edgeId}/device/request
/v1/{edgeId}/device/data
**************************/
long CIotEdgeServer_Mqtt::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	switch(nCmdType)
	{
	case EDGE_CMD_TYPE_IDX_device:
		return Process_Edge_Device(strFromSN, pBuf, nLen,pszCmdID);
	default:
		break;
	}
// 	CSttIotCmd oIotCmd;
// 	BufToCmd(&oIotCmd,pBuf,nLen,MQTT_DATA_FORMAT_XML);
// 
// 	return Process_Cmd_Iot(oIotCmd);
	return 0;
}

long CIotEdgeServer_Mqtt::Process_Edge_Device(const CString &strFromSN, char *pBuf, long nLen,char *pszCmdID)
{
	//�����������
	// 	CEdgeCmd oIotCmd;
	// 	BufToCmd(&oIotCmd,pBuf,nLen,MQTT_DATA_FORMAT_XML);

	if (!strcmp(pszCmdID,EDGE_CMD_ID_request))
	{
		return Process_Edge_Device_Request(strFromSN, pBuf,nLen);
	}
	else if (!strcmp(pszCmdID,EDGE_CMD_ID_data))
	{
		return Process_Edge_Device_Data(strFromSN, pBuf,nLen);
	}

	return 0;
}

/***************************
�ж��Ƿ����������������Ƿ���0
�����������룬��ӵ�BaseApp��listDevice��
***************************/
long CIotEdgeServer_Mqtt::Process_Edge_Device_Request(const CString &strFromSN, char *pBuf, long nLen)
{
	CEdgeCmd oEdgeCmd;
	BufToCmd(&oEdgeCmd, pBuf, nLen, EDGE_DATA_FORMAT_JSON);

	if(strFromSN == _T("edge_auth_id"))
	{
		CDataGroup oDataGroup;
		m_oEdgeAuthList.AddNewGroup(pBuf, pBuf, _T("STRUCT"));
	}
	else if(strFromSN.Find(_T("edge_auth_topic_")) == 0)
	{
		CDataGroup* pDataGroup = (CDataGroup*)m_oEdgeAuthList.FindByID(strFromSN.Mid(16));
		pDataGroup->AddNewData(EDGE_PROCEDURE_VAR_RequestAddr, pBuf);
	}
	else if(strFromSN.Find(_T("edge_auth_request_")) == 0)
	{
		CDataGroup* pDataGroup = (CDataGroup*)m_oEdgeAuthList.FindByID(strFromSN.Mid(18));
		pDataGroup->AddNewData(EDGE_PROCEDURE_VAR_RequestMessage, pBuf);
	}
	else if(strFromSN.Find(_T("edge_auth_response_")) == 0)
	{
		CDataGroup* pDataGroup = (CDataGroup*)m_oEdgeAuthList.FindByID(strFromSN.Mid(19));
		pDataGroup->AddNewData(EDGE_PROCEDURE_VAR_ResponseMessage, pBuf);
	}

	if(oEdgeCmd.m_strType == EDGE_CMD_INFO_Type_DEV_EVENT_LINKUP)
	{
		//�豸�б�Ӧ�ñ���һ������õ������豸��obj��
		//CString strDevSN = oEdgeCmd.GetEdgeParam()->GetEdgeDev()->m_strHardVersion;
		//5���Ĳ���devSN,ֻ�ܴ������ȡ
		CString strDevSN = strFromSN;
		//CString strDevName = oEdgeCmd.GetEdgeParam()->GetEdgeDev()->m_strDevName;
	
		CEdgeProtoDevice *pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(strDevSN);

		if (pDevice == NULL)
		{
			pDevice = new CEdgeProtoDevice();
			pDevice->m_strName = pDevice->m_strID = strDevSN;
			//pDevice->m_strName = strDevName;
			g_pEdgeEngineProtoSvrBaseApp->m_listDevice.AddTail(pDevice);
			AfxGetApp()->GetMainWnd()->PostMessage(WM_ON_STT_ENGINE_NEW_DEVICE, (WPARAM)pDevice, (LPARAM)pDevice);
		}

		//����linkup�ظ�����
		CEdgeCmd oCmd;
		CString strTime;
		GetCurrSystemtimeString(strTime);
		oCmd.SetProcedureID(EDGE_PROCEDURE_ID_DEV_EVENT_LINKUP);
		oCmd.m_strID = strDevSN;//���������ID
		oCmd.m_nMid = 10000;
		oCmd.m_strType = edge_GetCmdInfoType(EDGE_PROCEDURE_ID_DEV_EVENT_LINKUP);
		oCmd.m_strDeviceId = strDevSN;//�����ڲ���ID
		oCmd.m_strTimestamp = strTime;
		oCmd.m_nExpire = -1;
		oCmd.m_nCode = 200;
		CEdgeParam* pParam = new CEdgeParam;
		oCmd.SetEdgeParam(pParam);

		//linkup�Ļظ�������Ҫ��createdevice֮ǰ����,������Ҫд�뱨�����Ҫ��ǰ����
		//createdevice֮�����̽�����д�����ݼ���
		char* strJson = NULL;
		//�Զ�������GBK��
		long nLen = oCmd.GetXml(CEdgeCmdMngrXmlRWKeys::g_pXmlKeys, &strJson, 0, _JSON_TYPE_);
		CString strTopic = _T("");
		strTopic.Format(_T("/v1/%s/%s/%s"), oCmd.m_strID, 
			edge_GetCmdTypeID(oCmd.GetProcedureID()), edge_GetServerToEdgeCmdID(oCmd.GetProcedureID()));

		if(!pDevice->m_pLinkupReport->GetCount())
		{
			CString strLinkupTopicRecv, strLinkupDataSend;
			strLinkupTopicRecv.Format(_T("/v1/%s/device/request"), strFromSN);
			strLinkupDataSend = strJson;
			strLinkupDataSend = strLinkupDataSend.Mid(0, nLen);
			pDevice->m_pLinkupReport->AddNewData(EDGE_PROCEDURE_VAR_recvmsg_topic, strLinkupTopicRecv);
			pDevice->m_pLinkupReport->AddNewData(EDGE_PROCEDURE_VAR_recvmsg_message, pBuf);
			pDevice->m_pLinkupReport->AddNewData(EDGE_PROCEDURE_VAR_sendmsg_topic, strTopic);
			pDevice->m_pLinkupReport->AddNewData(EDGE_PROCEDURE_VAR_sendmsg_message, strLinkupDataSend);

			if(!pDevice->m_pReportFile)
			{
				CString strFilePath, strTime;
				SYSTEMTIME tm;
				GetSystemTime(&tm);
				strTime.Format(_T("%d%d%d%d%d%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
				strFilePath = _P_GetTemplatePath();
				strFilePath += strFromSN + strTime;
				pDevice->m_pReportFile = fopen(const_cast<char*>(strFilePath.GetString()), "w+");
			}
			fwrite(strLinkupTopicRecv, strLinkupTopicRecv.GetLength(), 1, pDevice->m_pReportFile);
			fwrite(pBuf, strlen(pBuf), 1, pDevice->m_pReportFile);
			fwrite(strTopic, strTopic.GetLength(), 1, pDevice->m_pReportFile);
			fwrite(strLinkupDataSend, strLinkupDataSend.GetLength(), 1, pDevice->m_pReportFile);
		}

		m_pPxCmmOptrInterface->Send(strJson, nLen, strTopic);
		delete strJson;
		return 1;
	}

	return 0;
}

/***************************
�ж��Ƿ��ǶϿ�����������Ƿ���0
����ǶϿ����룬ɾ��listDevice����ɾ��ָ����IotEngineProtocolServer
***************************/
long CIotEdgeServer_Mqtt::Process_Edge_Device_Data(const CString &strFromSN, char *pBuf, long nLen)
{
	CEdgeCmd oEdgeCmd;
	BufToCmd(&oEdgeCmd, pBuf, nLen, EDGE_DATA_FORMAT_JSON);

	if(oEdgeCmd.m_strType == EDGE_CMD_INFO_Type_DEV_EVENT_LINKDOWN)
	{
		CEdgeProtoDevice *pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(strFromSN);
		AfxGetApp()->GetMainWnd()->PostMessage(WM_ON_STT_ENGINE_DEL_DEVICE, (WPARAM)pDevice, (LPARAM)pDevice);
		return 1;
	}

	return 0;
}