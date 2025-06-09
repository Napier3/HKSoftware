#include "stdafx.h"
#include "SttMqttClientBase.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 


CSttMqttClientBase::CSttMqttClientBase()
:CMqttClientToPxEngine()
{

}

CSttMqttClientBase::~CSttMqttClientBase()
{

}


// BOOL CSttMqttClientBase::Connect(const char *pszIP,long nPort, const char *pszClientIDKey)
// {
// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 
// 	CString strClientID;
// 	strClientID.Format(_T("%s_%u_%02d%02d%03d"), pszClientIDKey
// 		,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);
// 
// 	Init(pszIP,nPort,strClientID);
// 	BOOL bRet = ConnectServer();
// 
// 	if (bRet)
// 	{
// 		//���ӳɹ���������������
// 		SubcribeMqttTopic(0);
// 	}
// 
// 	return bRet;
// }

long CSttMqttClientBase::Send(CExBaseObject *pCmdBase)
{
	if (!ConnectServer())
	{
		return -3;
	}

	if (Send_Stt(pCmdBase) >= 0)
	{
		return 1;
	}

	CSttCmdBase *pSttCmd = (CSttCmdBase *)pCmdBase;
	char *pszRetType = NULL;
	long nCmdType = pSttCmd->GetCmdType();
	char *pszCmdID = (char *)pSttCmd->m_strID.GetString();
	char *pszEventID = NULL;

	if (pSttCmd->GetClassID() == STTCMDCLASSID_CSTTSYSSTATE)
	{
		CSttSysState *pSysState = (CSttSysState *)pSttCmd;

		pszRetType = (char *)pSysState->m_strRetType.GetString();

		if (!strcmp(pszRetType,SYS_STATE_RETTYPE_EVENT))
		{//������¼�
			if ((!strcmp(pszCmdID,SYS_STATE_EVENT_OnEngineEvent))
				|| (!strcmp(pszCmdID,SYS_STATE_EVENT_OnTestAppEvent))
				|| (!strcmp(pszCmdID,STT_CMD_TYPE_IOT_RunProcedure)))
			{//����EngineEvent/TestAppEvent/RunProcedure
				CString strEventID;
				pSysState->GetParasDataValueByID(SYS_STATE_XEVENT_EVENTID,strEventID);

				pszEventID = (char *)strEventID.GetString();
			}
		}
	}

	char *pszBuf = NULL;
	long nLen = 0;
	nLen = pSttCmd->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszBuf,0);

	if (pszBuf == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("PublicCmd::pszBuf==NULL"));
		return -2;
	}

	long nRet = CMqttClientToPxEngine::Send(pSttCmd->m_strToSN, pszBuf,nLen,nCmdType,pszCmdID,pszRetType,pszEventID);
	delete pszBuf;
	return nRet;
}

long CSttMqttClientBase::Send_Stt(CExBaseObject *pCmdBase)
{
	CSttCmdBase *pSttCmd = (CSttCmdBase *)pCmdBase;
	pSttCmd->m_strFromSN = pSttCmd->m_strToSN;
	CString strTopic = GenerateTopic(pSttCmd);

	if (strTopic.GetLength() == 0)
	{
		return -1;
	}

	char *pszBuf = NULL;
	long nLen = 0;
	nLen = pSttCmd->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszBuf,0);
	long nRes = CMqttClientToPxEngine::Send(pszBuf, nLen, strTopic);
	delete pszBuf;
	return nRes;
}

//2021-7-19  lijunqing
CString CSttMqttClientBase::GenerateTopic(CSttCmdBase *pCmdBase)
{
	CString strTopic;
	UINT nClassID = pCmdBase->GetClassID();

	switch (nClassID)
	{
	case STTCMDCLASSID_CSTTATSCMD:
		strTopic = GenerateTopic((CSttAtsCmd*)pCmdBase);
		break;

	case STTCMDCLASSID_CSTTTESTCMD:
		strTopic = GenerateTopic((CSttTestCmd*)pCmdBase);
		break;

	case STTCMDCLASSID_CSTTSYSSTATE:
		strTopic = GenerateTopic((CSttSysState*)pCmdBase);
		break;

	case STTCMDCLASSID_CSTTIOTCMD:
		strTopic = GenerateTopic((CSttIotCmd*)pCmdBase);
		break;
	}

	//shaolei 2021 08 05
// 	CString strSN;
// 	strSN = m_oMqttClient.get
// 	if (strTopic.Find(mm_strSN))
// 	{
// 	}
	return strTopic;
}

CString CSttMqttClientBase::GenerateTopic(CSttAtsCmd *pAtsCmd)
{
	CString strTopic;

	strTopic.Format(_T("AtsCmd/%s"), pAtsCmd->m_strID);

	return strTopic;
}

CString CSttMqttClientBase::GenerateTopic(CSttTestCmd *pTestCmd)
{
	CString strTopic;

	strTopic.Format(_T("TestCmd/%s"), pTestCmd->m_strID);

	return strTopic;
}

CString CSttMqttClientBase::GenerateTopic(CSttSysState *pSysState)
{
	CString strTopic, strEventID, strCmdType;
	//CSttSysState ˵����REPLY��EVENT����ʱ��Ҫ��FromSN��ֵ��ToSN
	pSysState->m_strToSN = pSysState->m_strFromSN;

	//shaolei 20210805
	if (pSysState->m_strRetType == SYS_STATE_RETTYPE_REPLY)
	{
		//����̨SN/AtsState/FinishInputData/REPLY
		//������SN/TestState/StartTest/REPLY
		strEventID = SYS_STATE_RETTYPE_REPLY;
	}
	else if (pSysState->m_strRetType == SYS_STATE_RETTYPE_EVENT)
	{
		//����̨SN/AtsState/EVENT/TestCreated
		//����̨SN/AtsState/EVENT/ItemStateChanged
		//������SN/TestState/EVENT/TestStarted
		strEventID = SYS_STATE_RETTYPE_EVENT;
	}
	else if (pSysState->m_strRetType == SYS_STATE_RETTYPE_REPORT)
	{//������SN/TestState/REPORT
		strEventID = SYS_STATE_RETTYPE_REPORT;
	}
	else if (pSysState->m_strRetType == SYS_STATE_RETTYPE_EXCEPTION)
	{//������SN/TestState/EXCEPTION
		strEventID = SYS_STATE_RETTYPE_EXCEPTION;
	}

	if (pSysState->m_strRetSttCmd == STT_CMD_SYSSTATE_ATS)
	{
		//����̨SN/AtsState/CreateTest/REPLY
		strCmdType = _T("AtsState");
	}
	else if (pSysState->m_strRetSttCmd == STT_CMD_SYSSTATE_TEST)
	{//������SN/TestState/UpdateParameter/REPLY
		strCmdType = _T("TestState");
	}
	else if (pSysState->m_strRetSttCmd == STT_CMD_SYSSTATE_IOT)
	{//�����SN/IotState/CloseDevice/REPLY
		strCmdType = _T("IotState");
	}

	char* pszCmdType, *pszCmdID, *pszRetType, *pszEventID;
	CString_to_char(strCmdType, &pszCmdType);
	CString_to_char(pSysState->m_strID, &pszCmdID);
	CString_to_char(pSysState->m_strRetType, &pszRetType);
	CString_to_char(strEventID, &pszEventID);
	strTopic = GenerateTopic(pSysState->m_strToSN, pszCmdType, pszCmdID, pszRetType, pszEventID);
	delete pszEventID;
	delete pszCmdID;
	delete pszCmdType;
	delete pszRetType;
/*
	if (pSysState->m_strRetSttCmd == STT_CMD_SYSSTATE_ATS)
	{
		//����̨SN/AtsState/CreateTest/REPLY
		strTopic = _T("AtsState/");
	}
	else if (pSysState->m_strRetSttCmd == STT_CMD_SYSSTATE_TEST)
	{//������SN/TestState/UpdateParameter/REPLY
		strTopic = _T("TestState/");
	}
	else
	{
		//��Ϊû��ϵͳ���ǣ��˴����ؿգ�����лС�µĴ�����д���
		return strTopic;
	}

	if (pSysState->m_strRetType == SYS_STATE_RETTYPE_REPLY)
	{
		//����̨SN/AtsState/FinishInputData/REPLY
		//������SN/TestState/StartTest/REPLY
		strTopic.AppendFormat(_T("%s/"), pSysState->m_strID);
		strTopic += SYS_STATE_RETTYPE_REPLY;
	}
	else if (pSysState->m_strRetType == SYS_STATE_RETTYPE_EVENT)
	{
		//����̨SN/AtsState/EVENT/TestCreated
		//����̨SN/AtsState/EVENT/ItemStateChanged
		//������SN/TestState/EVENT/TestStarted
		strTopic += SYS_STATE_RETTYPE_EVENT;
		strTopic.AppendFormat(_T("/%s"), pSysState->m_strID);
	}
	else if (pSysState->m_strRetType == SYS_STATE_RETTYPE_REPORT)
	{//������SN/TestState/REPORT
		strTopic += SYS_STATE_RETTYPE_REPORT;
	}
	else if (pSysState->m_strRetType == SYS_STATE_RETTYPE_EXCEPTION)
	{//������SN/TestState/EXCEPTION
		strTopic += SYS_STATE_RETTYPE_EXCEPTION;
	}

	else
	{
		strTopic.AppendFormat(_T("%s/%s"), pSysState->m_strID, pSysState->m_strRetType);
	}

	//����������ʱ������
	//����̨SN/AtsState/EVENT/TestAppEvent/�¼�ID
	//����̨SN/AtsState/EVENT/EngineEvent/�¼�ID
*/
	return strTopic;
}

//�����SN/��Լ����߷���ID/IotCmd/CreateDevice
CString CSttMqttClientBase::GenerateTopic(CSttIotCmd *pIotCmd)
{
	CString strTopic;

	strTopic.Format(_T("IotCmd/%s"), pIotCmd->m_strID);

	return strTopic;
}

CString CSttMqttClientBase::GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	return _T("");
}