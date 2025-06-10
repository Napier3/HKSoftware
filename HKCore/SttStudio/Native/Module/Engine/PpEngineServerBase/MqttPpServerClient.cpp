#include "stdafx.h"
#include "MqttPpServerClient.h"
#include "../SttTestEngineBase.h"
#include "../../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineDeviceBase.h"
#include "../../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineServer.h"
#include "PpSvrInterfaceMqttClient.h"

CMqttPpServerClient::CMqttPpServerClient()
{
}

CMqttPpServerClient::~CMqttPpServerClient()
{

}



//MQTT事件处理接口，共CMqttMsgInterface对象调用
//class CMqttMsgProcessInterface
//根据收到的MQTT主题进行匹配，如果匹配成功，则返回TRUE，否则返回FALSE
BOOL CMqttPpServerClient::MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser)
{//主题：请求端SN/DeviceSN/IotCmd/RunProcedure
	if (m_strDeviceSN == oSttMqttTopicParser.m_pszSubTopic[1])
	{
		return TRUE;
	}

	return FALSE;
}

CSttIotCmd* CMqttPpServerClient::MqttTopicParser_To_IotCmd(CSttMqttTopicParser &oSttMqttTopicParser)
{
	CSttIotCmdDriver oDrvIotCmd;
	CIotPxCommChannelInterface *pIotPxCommChannelInterface = this;
	CSttIotCmd *pIotCmd = oDrvIotCmd.NewSttIotCmd(pIotPxCommChannelInterface);
	oDrvIotCmd.AddRef();

	//2022-10-22 lijunqing   初始化没命令数据的格式
	InitSttCmdDataFormat(oSttMqttTopicParser.m_pMqttPkgBuffer[0]);

	++CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	BOOL bRet = pIotCmd->SetXml_UTF8(oSttMqttTopicParser.m_pMqttPkgBuffer
		, oSttMqttTopicParser.m_nMqttPkgBufferLen
		, CSttCmdDefineXmlRWKeys::g_pXmlKeys
		, GetSttCmdDataFormat());
	--CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	return pIotCmd;
}

void CMqttPpServerClient::IOT_CreateDevice(CSttMqttTopicParser &oSttMqttTopicParser)
{
	m_strFromSN = oSttMqttTopicParser.m_pszSubTopic[0];
	CSttIotCmd *pIotCmd = MqttTopicParser_To_IotCmd(oSttMqttTopicParser);	

	CSttParas* pParas = pIotCmd->GetSttParas();
	pParas->GetDataValue(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	CIotPxEngineServer::POST_WM_IOT_CMD_MSG(this, pIotCmd);
}

void CMqttPpServerClient::IOT_CloseDevice(CSttMqttTopicParser &oSttMqttTopicParser)
{
	m_strFromSN = oSttMqttTopicParser.m_pszSubTopic[0];
	CSttIotCmd *pIotCmd = MqttTopicParser_To_IotCmd(oSttMqttTopicParser);	
	CIotPxEngineServer::POST_WM_IOT_CMD_MSG(this, pIotCmd);
}

//MQTT消息处理
//请求端SN/DeviceSN/IotCmd/RunProcedure
void CMqttPpServerClient::MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser)
{
	m_strFromSN = oSttMqttTopicParser.m_pszSubTopic[0];
	CSttIotCmd *pIotCmd = MqttTopicParser_To_IotCmd(oSttMqttTopicParser);	

	CIotPxEngineServer::POST_WM_IOT_CMD_MSG(this, pIotCmd);
}

//MQTT主题订阅接口函数：MQTT Client连接成功后，遍历各CMqttMsgProcessInterface
//订阅相关的主题
BOOL CMqttPpServerClient::MqttSubscribeTopic()
{
	//不需要订阅，在CPpSvrInterfaceMqttClient中订阅
	return TRUE;
}

//MQTT取消主题订阅接口函数：MQTT Client断开连接后，遍历各CMqttMsgProcessInterface
//T取消订阅相关的主题
BOOL CMqttPpServerClient::MqttUnSubscribeTopic()
{
	return TRUE;
}

long CMqttPpServerClient::PxSendBuffer(BYTE *pBuf, long nLen)
{
	return 0;
}

long CMqttPpServerClient::PxSendSysState(CSttSysState *pSysState)
{
	CSttMqttTopicCmbn oCmbn;
	oCmbn.ResetSubTopics();
	oCmbn.AddSubTopic(m_strFromSN);
	oCmbn.AddSubTopic(m_strDeviceSN);

	if (pSysState->m_strRetType == SYS_STATE_RETTYPE_REPLY)
	{//../ IotState/StopTest/REPLY
		oCmbn.AddSubTopic(MQTT_CMD_ID_IotState);
		oCmbn.AddSubTopic(pSysState->m_strID);
		oCmbn.AddSubTopic(pSysState->m_strRetType);
	}
	else if (pSysState->m_strRetType == SYS_STATE_RETTYPE_EVENT)
	{//../ IotState/EVENT/TestStoped
		oCmbn.AddSubTopic(MQTT_CMD_ID_IotState);
		oCmbn.AddSubTopic(pSysState->m_strRetType);
		oCmbn.AddSubTopic(pSysState->m_strID);
	}
	else  if (pSysState->m_strRetType == SYS_STATE_RETTYPE_RTDATA)
	{
		oCmbn.AddSubTopic(pSysState->m_strRetType);
	}
	else
	{
		oCmbn.AddSubTopic(pSysState->m_strID);
		oCmbn.AddSubTopic(pSysState->m_strRetType);
	}

	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oCmbn.m_nBufferLength = pSysState->GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys
		, &oCmbn.m_pszBuffer, 0, m_nSttCmdDataFormat);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	g_thePpSvrMqttClient->PublicTopic(oCmbn);

	return 0;
}


BOOL CMqttPpServerClient::ProcessRecvPacket(BYTE *pBuf,long nLen)
{
	return TRUE;
}


long CMqttPpServerClient::OnTestMsg(BYTE *pBuf, long nLen)
{
	return 0;
}

long CMqttPpServerClient::Process_Cmd_System(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	return 0;
}

long CMqttPpServerClient::Process_Cmd_IOT(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	return 0;
}

void CMqttPpServerClient::OnSocketClose(int nErrorCode, BOOL bDeleteSocket)
{
}
