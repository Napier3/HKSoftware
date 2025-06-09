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
此处为测试台订阅的主题，包括：
ats/测试台SN/AtsCmd/CreateTest
ats/测试台SN/AtsCmd/StartTest
ats/测试台SN/AtsCmd/StopTest
ats/测试台SN/AtsCmd/CloseTest

ats/测试台SN/AtsState/EVENT/ItemStateChanged
ats/测试台SN/AtsState/EVENT/Report
ats/测试台SN/AtsState/EVENT/TestFinished
**************************/
BOOL CSttProtoAtsServiceMqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	CString strTopic;
	//atscmd 控制指令订阅
	strTopic.Format(_T("ats/%s/AtsCmd/%s"), m_strSN, m_strAtsMqttTopic);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	//ats EVENT事件订阅
	strTopic.Format(_T("ats/%s/AtsState/EVENT/%s"), m_strSN, m_strAtsMqttTopic);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	/************************************************************************
	//对于外部系统上传报告结束，暂时没有兼容方案，临时直接注释掉  shaolei  2023-5-25

	//shaolei 20210927
	//订阅外部系统上传报告结束的主题
	//当自动测试服务配置多个测试台时，每个测试台都订阅该主题，会出问题
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
测试台SN/AtsState/CreateTest/Reply
测试台SN/AtsState/EVENT/TestCreated
测试台SN/AtsState/EVENT/EngineEvent/事件ID【此部分暂时不考虑】
测试台SN/AtsCmd/InputData 
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
		//测试台SN/AtsState/FinishInputData/REPLY
		//测试仪SN/TestState/StartTest/REPLY
		strTopic.Format(_T("ats/%s/%s/%s/%s"),m_strSN,pszCmdType,pszCmdID,pszRetType);
	}
	else if (strcmp(SYS_STATE_RETTYPE_EVENT, pszRetType) == 0)
	{
		//测试台SN/AtsState/EVENT/TestCreated
		//测试台SN/AtsState/EVENT/ItemStateChanged
		//测试仪SN/TestState/EVENT/TestStarted
		strTopic.Format(_T("ats/%s/%s/%s/%s"),m_strSN,pszCmdType,pszRetType,pszCmdID);
	}
	else if (strcmp(SYS_STATE_RETTYPE_REPORT, pszRetType) == 0)
	{//测试仪SN/TestState/REPORT
		strTopic.Format(_T("ats/%s/%s/%s"),m_strSN,pszCmdType,pszRetType);
	}
	else if (strcmp(SYS_STATE_RETTYPE_EXCEPTION, pszRetType) == 0)
	{//测试仪SN/TestState/EXCEPTION
		strTopic.Format(_T("ats/%s/%s/%s"),m_strSN,pszCmdType,pszRetType);
	}

	return strTopic;
}
/************************
作为测试服务的MqtClient，接受的指令包括
1、AtsCmd    
ats/测试台SN/AtsCmd/CreateTest
ats/测试台SN/AtsCmd/StartTest  自动测试SmartTest订阅
ats/测试台SN/AtsCmd/StopTest   自动测试SmartTest订阅
ats/测试台SN/AtsCmd/CloseTest

2、ATS EVENT事件
ats/测试台SN/AtsState/EVENT/ItemStateChanged
ats/测试台SN/AtsState/EVENT/Report
ats/测试台SN/AtsState/EVENT/TestFinished
	..............................................
3、InputData指令的应答   测试台SN/AtsState/InputData/Reply
**************************/
BOOL CSttProtoAtsServiceMqttClient::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() < 4)
	{//如果收到的主题数小于4，表示错误
		return FALSE;
	}

 	CString strCmdType, strSN_RcvCmd , strCmdID, strKey;
	strCmdType = oToken.GetToken(0);

	strSN_RcvCmd = oToken.GetToken(1);
	strFromSN = strSN_RcvCmd;

	if (oToken.GetStringsCount() == 4)
	{
		//AtsCmd和RTDATA
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
		//测试台SN/AtsState/EVENT/ItemStateChanged
		//测试台SN/AtsState/EVENT/Report
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
自动测试模板服务对应的mqtt客户端
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
此处为测试模板服务订阅的主题，包括：
ats/index_task/AtsCmd/ExportReport    导出报告
ats/user_id/AtsCmd/UploadTemplate     新增模板
ats/user_id/AtsCmd/ImportTaskInfo     导入任务信息
ats/user_id/AtsCmd/ImportSampleInfo   导入样品信息

ats/测试仪SN|设备SN/AtsState/RTDATA

//这两个主题，由测试模板服务订阅
dev/设备SN/AtsState/EVENT/事件ID
test/测试仪SN/AtsState/EVENT/事件ID
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

	//测试仪+设备的实时数据订阅
	strTopic.Format(_T("ats/+/AtsState/RTDATA"));
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	//测试仪的事件订阅
	strTopic.Format(_T("test/+/AtsState/EVENT/+"));
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	//设备的事件订阅
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
	/*  测试模板服务，应当不会应答以下事件
	else if (strcmp(SYS_STATE_RETTYPE_REPORT, pszRetType) == 0)
	{//测试仪SN/TestState/REPORT
		strTopic.Format(_T("%s/%s/%s"),strToSN,pszCmdType,pszRetType);
	}
	else if (strcmp(SYS_STATE_RETTYPE_EXCEPTION, pszRetType) == 0)
	{//测试仪SN/TestState/EXCEPTION
		strTopic.Format(_T("%s/%s/%s"),strToSN,pszCmdType,pszRetType);
	}*/

	return strTopic;
}