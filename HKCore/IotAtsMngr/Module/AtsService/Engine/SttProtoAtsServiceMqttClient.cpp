#include "stdafx.h"
#include "SttProtoAtsServiceMqttClient.h"
#include "../../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../../Module/System/StringTokenizer.h"

CSttProtoAtsServiceMqttClient::CSttProtoAtsServiceMqttClient(const CString &strMqttTopic)
{
	m_strAtsMqttTopic = strMqttTopic;
}

CSttProtoAtsServiceMqttClient::CSttProtoAtsServiceMqttClient()
{
	m_strAtsMqttTopic = _T("#");
}

CSttProtoAtsServiceMqttClient::~CSttProtoAtsServiceMqttClient()
{

}

// BOOL CSttProtoAtsServiceMqttClient::Connect(const char *pszIP,long nPort)
// {
// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 
// // 	CString strClientID;
// // 	strClientID.Format(_T("AtsService_%u_%02d%02d%02d"),stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);
// 
// /*	Init(pszIP,nPort,strClientID);*/
// 
// 	return Connect(pszIP, nPort, _T("AtsService"));
// }

/************************
�˴�Ϊ����̨���ĵ����⣬������
ats/����̨SN/AtsCmd/CreateTest
ats/����̨SN/AtsCmd/StartTest
ats/����̨SN/AtsCmd/StopTest
ats/����̨SN/AtsCmd/CloseTest

ats/����̨SN/AtsState/EVENT/ItemStateChanged
ats/����̨SN/AtsState/EVENT/Report
ats/����̨SN/AtsState/EVENT/TestFinished
**************************/
BOOL CSttProtoAtsServiceMqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	CString strTopic;
	//atscmd ����ָ���
	strTopic.Format(_T("ats/%s/AtsCmd/%s"), m_strSN, m_strAtsMqttTopic);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	//ats EVENT�¼�����
	strTopic.Format(_T("ats/%s/AtsState/EVENT/%s"), m_strSN, m_strAtsMqttTopic);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	/************************************************************************
	//�����ⲿϵͳ�ϴ������������ʱû�м��ݷ�������ʱֱ��ע�͵�  shaolei  2023-5-25

	//shaolei 20210927
	//�����ⲿϵͳ�ϴ��������������
	//���Զ����Է������ö������̨ʱ��ÿ������̨�����ĸ����⣬�������
	if (m_strSN.Find(_T("Auto")) >= 0)
	{
		return TRUE;
	}

	strTopic.Format(_T("+/AtsState/EVENT/UploadReportFinished"));
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	**************************************************************************/
	
	return TRUE;
}

/*
����̨SN/AtsState/CreateTest/Reply
����̨SN/AtsState/EVENT/TestCreated
����̨SN/AtsState/EVENT/EngineEvent/�¼�ID���˲�����ʱ�����ǡ�
����̨SN/AtsCmd/InputData 
*/
CString CSttProtoAtsServiceMqttClient::GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;

	strTopic.Format(_T("%s/AtsState/%s/%s"),m_strSN,pszRetType, pszCmdID);

	return strTopic;
}

CString CSttProtoAtsServiceMqttClient::GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;

	if (strcmp(SYS_STATE_RETTYPE_REPLY, pszRetType) == 0)
	{
		//����̨SN/AtsState/FinishInputData/REPLY
		//������SN/TestState/StartTest/REPLY
		strTopic.Format(_T("ats/%s/%s/%s/%s"),m_strSN,pszCmdType,pszCmdID,pszRetType);
	}
	else if (strcmp(SYS_STATE_RETTYPE_EVENT, pszRetType) == 0)
	{
		//����̨SN/AtsState/EVENT/TestCreated
		//����̨SN/AtsState/EVENT/ItemStateChanged
		//������SN/TestState/EVENT/TestStarted
		strTopic.Format(_T("ats/%s/%s/%s/%s"),m_strSN,pszCmdType,pszRetType,pszCmdID);
	}
	else if (strcmp(SYS_STATE_RETTYPE_REPORT, pszRetType) == 0)
	{//������SN/TestState/REPORT
		strTopic.Format(_T("ats/%s/%s/%s"),m_strSN,pszCmdType,pszRetType);
	}
	else if (strcmp(SYS_STATE_RETTYPE_EXCEPTION, pszRetType) == 0)
	{//������SN/TestState/EXCEPTION
		strTopic.Format(_T("ats/%s/%s/%s"),m_strSN,pszCmdType,pszRetType);
	}

	return strTopic;
}
/************************
��Ϊ���Է����MqtClient�����ܵ�ָ�����
1��AtsCmd    
ats/����̨SN/AtsCmd/CreateTest
ats/����̨SN/AtsCmd/StartTest  �Զ�����SmartTest����
ats/����̨SN/AtsCmd/StopTest   �Զ�����SmartTest����
ats/����̨SN/AtsCmd/CloseTest

2��ATS EVENT�¼�
ats/����̨SN/AtsState/EVENT/ItemStateChanged
ats/����̨SN/AtsState/EVENT/Report
ats/����̨SN/AtsState/EVENT/TestFinished
	..............................................
3��InputDataָ���Ӧ��   ����̨SN/AtsState/InputData/Reply
**************************/
BOOL CSttProtoAtsServiceMqttClient::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() < 4)
	{//����յ���������С��4����ʾ����
		return FALSE;
	}

 	CString strCmdType, strSN_RcvCmd , strCmdID, strKey;
	strCmdType = oToken.GetToken(0);

	strSN_RcvCmd = oToken.GetToken(1);
	strFromSN = strSN_RcvCmd;

	if (oToken.GetStringsCount() == 4)
	{
		//AtsCmd��RTDATA
		CString strCmd;
		strCmd = oToken.GetToken(2);

		if (strCmd == _T("AtsCmd"))
		{
			strCmdID = oToken.GetToken(3);
		}
		else if (strCmd == _T("AtsState"))
		{
			strKey = oToken.GetToken(3);
			strCmdID = oToken.GetToken(2);  //AtsState
		}	
	}
	else if (oToken.GetStringsCount() == 5)
	{
		//EVENT
		strCmdID = oToken.GetToken(2);
		strKey = oToken.GetToken(3);
	}
	
	const char *pString = NULL;
	
	nCmdType = mqtt_cmd_to_stt_cmd_id(strCmdID);

	if (strKey == SYS_STATE_RETTYPE_REPLY)
	{
		strcpy(pszCmdID,oToken.GetToken(2));
		pString = oToken.GetToken(3);

		if (pString != NULL)
		{
			strcpy(pszRetType,pString);
		}
	}
	else if (strKey == SYS_STATE_RETTYPE_EVENT)
	{
		//����̨SN/AtsState/EVENT/ItemStateChanged
		//����̨SN/AtsState/EVENT/Report
		strcpy(pszRetType,oToken.GetToken(3));
		pString = oToken.GetToken(4);

		if (pString != NULL)
		{
			strcpy(pszCmdID,pString);
		}
	}
	else if (strKey == SYS_STATE_RETTYPE_RTDATA)
	{
		strcpy(pszRetType,oToken.GetToken(3));
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}
// void CSttProtoAtsServiceMqttClient::Init( const CString &strIP,long nPort,const CString &strClientID )
// {
// 	m_strIP = strIP;
//  	m_nPort = nPort;
//  	m_strClientID = strClientID;
// }



/************************************************************************/
/*
�Զ�����ģ������Ӧ��mqtt�ͻ���
*/

CSttProtoAtsService_Template_MqttClient::CSttProtoAtsService_Template_MqttClient(const CString &strMqttTopic)
{
	m_strAtsMqttTopic = strMqttTopic;
}

CSttProtoAtsService_Template_MqttClient::CSttProtoAtsService_Template_MqttClient()
{
	m_strAtsMqttTopic = _T("#");
}

CSttProtoAtsService_Template_MqttClient::~CSttProtoAtsService_Template_MqttClient()
{

}

/************************
�˴�Ϊ����ģ������ĵ����⣬������
ats/index_task/AtsCmd/ExportReport    ��������
ats/user_id/AtsCmd/UploadTemplate     ����ģ��
ats/user_id/AtsCmd/ImportTaskInfo     ����������Ϣ
ats/user_id/AtsCmd/ImportSampleInfo   ������Ʒ��Ϣ

ats/������SN|�豸SN/AtsState/RTDATA

//���������⣬�ɲ���ģ�������
dev/�豸SN/AtsState/EVENT/�¼�ID
test/������SN/AtsState/EVENT/�¼�ID
**************************/
BOOL CSttProtoAtsService_Template_MqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	CString strTopic;
	strTopic.Format(_T("ats/+/AtsCmd/%s"), m_strAtsMqttTopic);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	//������+�豸��ʵʱ���ݶ���
	strTopic.Format(_T("ats/+/AtsState/RTDATA"));
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	//�����ǵ��¼�����
	strTopic.Format(_T("test/+/AtsState/EVENT/+"));
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	//�豸���¼�����
	strTopic.Format(_T("dev/+/AtsState/EVENT/+"));
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	return TRUE;
}

CString CSttProtoAtsService_Template_MqttClient::GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;

	if (strcmp(SYS_STATE_RETTYPE_REPLY, pszRetType) == 0)
	{
		//user_id/AtsState/UploadTemplate/REPLY
		//user_id/TestState/ImportTaskInfo/REPLY
		strTopic.Format(_T("ats/%s/%s/%s/%s"),strToSN,pszCmdType,pszCmdID,pszRetType);
	}
	else if (strcmp(SYS_STATE_RETTYPE_EVENT, pszRetType) == 0)
	{
		//index_task/AtsState/EVENT/ExportReport
		strTopic.Format(_T("ats/%s/%s/%s/%s"),strToSN,pszCmdType,pszRetType,pszCmdID);
	}
	/*  ����ģ�����Ӧ������Ӧ�������¼�
	else if (strcmp(SYS_STATE_RETTYPE_REPORT, pszRetType) == 0)
	{//������SN/TestState/REPORT
		strTopic.Format(_T("%s/%s/%s"),strToSN,pszCmdType,pszRetType);
	}
	else if (strcmp(SYS_STATE_RETTYPE_EXCEPTION, pszRetType) == 0)
	{//������SN/TestState/EXCEPTION
		strTopic.Format(_T("%s/%s/%s"),strToSN,pszCmdType,pszRetType);
	}*/

	return strTopic;
}