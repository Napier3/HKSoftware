#include "stdafx.h"
#include"PpMqttIotEngine.h"
#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"

#include "../SmartTestInterface/AtsOutInterfaceMqttClient.h"
#include "../SttRegisterCode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern BOOL g_bShowTestWndTop;

//////////////////////////////////////////////////////////////////////////
//CPpMqttIotDevice

//MQTT�¼�����ӿڣ���CMqttMsgInterface�������
//class CMqttMsgProcessInterface
//�����յ���MQTT�������ƥ�䣬���ƥ��ɹ����򷵻�TRUE�����򷵻�FALSE
BOOL CPpMqttIotDevice::MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser)
{
	if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2] , MQTT_CMD_ID_IotState ) == 0)
	{
		//���ݶ�������˳��
		if (m_strID == oSttMqttTopicParser.m_pszSubTopic[1] || m_strID == oSttMqttTopicParser.m_pszSubTopic[0])
		{//  �����SN/DeviceSN/IotState/RunProcedure/EVENT/�¼�ID
			return TRUE;
		}
	}

	return FALSE;
}

//MQTT��Ϣ����
//�����SN/DeviceSN/IotState/RunProcedure/EVENT/�¼�ID
void CPpMqttIotDevice::MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser)
{
	CSttSysState oSysState;
	 //��ʱֻ����AtsCmd
	dvm_IncGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oSysState.SetXml_UTF8(oSttMqttTopicParser.m_pMqttPkgBuffer, oSttMqttTopicParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys, m_nSttCmdDataFormat);
	dvm_DecGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	On_SysState_IOT(&oSysState);
}

//MQTT���ⶩ�Ľӿں�����MQTT Client���ӳɹ��󣬱�����CMqttMsgProcessInterface
//������ص�����
/*
�����SN/DeviceSN/IotState/RunProcedure/EVENT/�¼�ID
*/
BOOL CPpMqttIotDevice::MqttSubscribeTopic()
{
	CString strTopic ;

	CString strBentchSN ;
	CString strDeviceSN; 
	strBentchSN = m_strBentchSN;
	strDeviceSN = m_strID;

	strTopic.Format(_T("%s/%s/IotState/#"), strBentchSN.GetString(), strDeviceSN.GetString());
	g_theAtsOutMqttClient->SubscribeTopic(strTopic, 0);

	strTopic.Format(_T("%s/IotState/#"), strDeviceSN.GetString());
	g_theAtsOutMqttClient->SubscribeTopic(strTopic, 0);

	strTopic.Format(_T("%s/RTDATA"), strDeviceSN.GetString());
	g_theAtsOutMqttClient->SubscribeTopic(strTopic, 0);

	return TRUE;
}

//MQTTȡ�����ⶩ�Ľӿں�����MQTT Client�Ͽ����Ӻ󣬱�����CMqttMsgProcessInterface
//Tȡ��������ص�����
BOOL CPpMqttIotDevice::MqttUnSubscribeTopic()
{
	CString strTopic ;
	CString strBentchSN ;
	CString strDeviceSN; 
	strBentchSN = m_strBentchSN;
	strDeviceSN = m_strID;

	strTopic.Format(_T("%s/%s/IotState/#"), strBentchSN.GetString(), strDeviceSN.GetString());
	g_theAtsOutMqttClient->UnSubscribeTopic(strTopic);

	strTopic.Format(_T("%s/IotState/#"), strDeviceSN.GetString());
	g_theAtsOutMqttClient->UnSubscribeTopic(strTopic);

	strTopic.Format(_T("%s/RTDATA"), strDeviceSN.GetString());
	g_theAtsOutMqttClient->UnSubscribeTopic(strTopic);

	return TRUE;
}

CPpMqttIotDevice::CPpMqttIotDevice()
{
	
}

CPpMqttIotDevice::~CPpMqttIotDevice()
{
	DisConnect();

	MqttRemoveFromClient();
}


void CPpMqttIotDevice::MqttAddToClient()
{
	CAtsOutInterfaceMqttClient::Create(m_strBentchSN);
	g_theAtsOutMqttClient->MqttAdd(this);
}

void CPpMqttIotDevice::MqttRemoveFromClient()
{
	g_theAtsOutMqttClient->MqttRemove(this);
	CAtsOutInterfaceMqttClient::Release();
}

void CPpMqttIotDevice::SetSttCmdDataFormat(long nSttCmdForat)
{
    m_nSttCmdDataFormat = nSttCmdForat;
}

BOOL CPpMqttIotDevice::ConnectSttServer()
{
	//���ӷ�����
	long nRet = g_theAtsOutMqttClient->Connect(m_strBentchSN);

	if (! nRet)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Connect IOT Protocol Server Failed!"));
		PostDeviceSysMessage(0, engineConnectDeviceFailed);

		return FALSE;
	}

	return TRUE;
}

void CPpMqttIotDevice::On_SysState_IOT(CSttSysState *pSysState)
{
	CPpSttIotDeviceBase::On_SysState_IOT(pSysState);
}

//  �����SN/DeviceSN/IotCmd/RunProcedure
long CPpMqttIotDevice::X_SendIotCmd(CSttIotCmd &oIotCmd)
{
	CSttMqttTopicCmbn oCmbn;
	oCmbn.ResetSubTopics();
	oCmbn.AddSubTopic(m_strBentchSN);
	oCmbn.AddSubTopic(m_strID);
	oCmbn.AddSubTopic(MQTT_CMD_ID_IotCmd);
	oCmbn.AddSubTopic(oIotCmd.m_strID);

	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oCmbn.m_nBufferLength = oIotCmd.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys
		, &oCmbn.m_pszBuffer, 0, m_nSttCmdDataFormat);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	g_theAtsOutMqttClient->PublicTopic(oCmbn);

	return 0;
}

BOOL CPpMqttIotDevice::IsConnectIotServerSucc()
{
	return g_theAtsOutMqttClient->IsConnectSuccessful();
}

long CPpMqttIotDevice::IsConnectSuccessful()
{
	return m_bIsSvrDeviceConnectSucc;
}

void CPpMqttIotDevice::DisConnect()
{
}

void CPpMqttIotDevice::DisConnectForClose(BOOL bDelete)
{
   
}

extern CString *g_strSmartTest_BenchSN;

void CPpMqttIotDevice::SetDeviceSN(const CString &strDeviceSN)
{
	CPpSttIotDeviceBase::SetDeviceSN(strDeviceSN);

	if (g_strSmartTest_BenchSN != NULL)
	{
		m_strBentchSN = *g_strSmartTest_BenchSN;
	}

	MqttAddToClient();
}

//////////////////////////////////////////////////////////////////////////
//CPpMqttIotEngine
CPpMqttIotEngine::CPpMqttIotEngine()
{
	
}

CPpMqttIotEngine::~CPpMqttIotEngine(void)
{
	
}


CPpSttIotDeviceBase* CPpMqttIotEngine::CreateNewDevice()
{
	return new CPpMqttIotDevice();
}
