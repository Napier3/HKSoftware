#include "stdafx.h"
#include "SttMqttEngineBase.h"

CSttMqttEngineBase::CSttMqttEngineBase()
{

}

CSttMqttEngineBase::~CSttMqttEngineBase()
{

}

void CSttMqttEngineBase::BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat)
{
	CSttCmdBase *pSttCmd = (CSttCmdBase *)pCmdBase;

	if (strFormat == MQTT_DATA_FORMAT_JSON)
	{
		pSttCmd->PraseCmdBuf(pBuf,nLen,NULL,MQTT_DATA_FORMAT_JSON);
	}
	else
	{//XML
		SetXmlBufferLen(nLen * 2);
		pSttCmd->PraseCmdBuf(pBuf,nLen,m_pszXmlBuffer,MQTT_DATA_FORMAT_XML);
	}
}

long CSttMqttEngineBase::ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttCmdData *pRetData)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pSttCmd);

	if (pRetData != NULL)
	{//���ؽ������
		oSysState.AppendParas(*pRetData);
	}

	oSysState.Set_ExecStatus(nCmdExecStatus);

	return m_pPxCmmOptrInterface->Send(&oSysState);
}

long CSttMqttEngineBase::ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,const CString &strDeviceID)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pSttCmd);

	if (!strDeviceID.IsEmpty())
	{
		oSysState.SetParasDataAttr(STT_CMD_PARA_DeviceSN, strDeviceID);
	}
	
	oSysState.Set_ExecStatus(nCmdExecStatus);

	return m_pPxCmmOptrInterface->Send(&oSysState);
}


//2021-7-22  lijunqing  ���ӷ���ϵͳ״̬�ĸ��ֺ�������
//ǰ����Ϊ���ݺ�����û���Ϣ���أ�����������������ֱ��������Ϊ�˼������д��벻Ҫ��������
//���º�����shaolei���������޸ģ����������βεȣ�  20210727
long CSttMqttEngineBase::ReturnSysState_REPLY(CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType)
{
	//2021-8-6  lijunqing  ??????????? ΪʲôҪ���´���һ��CSttSysState
	//CSttSysState oSysState;
	CSttSysState *pSysState = NULL;
	BOOL bNeedCreateNew = TRUE;

	if (pRetData != NULL)
	{
		if (pRetData->GetClassID() == STTCMDCLASSID_CSTTSYSSTATE)
		{
			pSysState = (CSttSysState *)pRetData;
			bNeedCreateNew = FALSE;
		}
	}

	if (bNeedCreateNew)
	{
		pSysState = new CSttSysState();
	}

	pSysState->m_strRetSttCmd = pszRetCmdType;//STT_CMD_SYSSTATE_ATS;
	pSysState->m_strID = pszEventID;

	if (pRetData != NULL && bNeedCreateNew)
	{//���ؽ������
		//2020-10-27  lijunqing
		pSysState->AppendParas(*pRetData);
		//pRetData->RemoveAll();
	}

	pSysState->Set_ExecStatus(nCmdExecStatus);

	if (m_pPxCmmOptrInterface == NULL && pCmmOptrInterface == NULL)
	{//2021-8-3  lijunqing ����ģʽ����ʾ��Ϣ
		CString strSysState;
		CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		pSysState->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strSysState);
		CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strSysState);

		if (bNeedCreateNew)
		{
			delete pSysState;
		}

		return 0;
	}

	//shaolei 20210801
	if (m_pPxCmmOptrInterface == NULL)
	{
		AttachPxCmmInterface(pCmmOptrInterface);
	}

	long nRet = m_pPxCmmOptrInterface->Send(pSysState);

	if (bNeedCreateNew)
	{
		delete pSysState;
	}

	return nRet;
}

long CSttMqttEngineBase::ReturnSysState_EVENT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType)
{
	//2021-8-6  lijunqing  ??????????? ΪʲôҪ���´���һ��CSttSysState
	//CSttSysState oSysState;
	CSttSysState *pSysState = NULL;
	BOOL bNeedCreateNew = TRUE;

	if (pRetData != NULL)
	{
		if (pRetData->GetClassID() == STTCMDCLASSID_CSTTSYSSTATE)
		{
			pSysState = (CSttSysState *)pRetData;
			bNeedCreateNew = FALSE;
		}
	}

	if (bNeedCreateNew)
	{
		pSysState = new CSttSysState();
	}

	pSysState->m_strRetSttCmd = pszRetCmdType;//STT_CMD_SYSSTATE_ATS;
	pSysState->m_strID = pszEventID;
	pSysState->SetEvent();

	if (pRetData != NULL && bNeedCreateNew)
	{//���ؽ������
		//2020-10-27  lijunqing
		pSysState->AppendParas(*pRetData);
		//pRetData->RemoveAll();
	}

	if (m_pPxCmmOptrInterface == NULL && pCmmOptrInterface == NULL)
	{//2021-8-5  lijunqing ����ģʽ����ʾ��Ϣ
		CString strSysState;
		CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		pSysState->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strSysState);
		CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strSysState);

		if (bNeedCreateNew)
		{
			delete pSysState;
		}

		return 0;
	}

	long nRet = m_pPxCmmOptrInterface->Send(pSysState);

	if (bNeedCreateNew)
	{
		delete pSysState;
	}

	return nRet;
}

//2021-8-6  lijunqing
long CSttMqttEngineBase::ReturnSysState_REPORT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszRetCmdType)
{
	CSttSysState *pSysState = (CSttSysState *)pRetData;
	pSysState->m_strRetSttCmd = pszRetCmdType; // STT_CMD_SYSSTATE_ATS;
	pSysState->m_strID = SYS_STATE_RETTYPE_REPORT;
	pSysState->SetReporting();

	if (m_pPxCmmOptrInterface == NULL && pCmmOptrInterface == NULL)
	{//2021-8-5  lijunqing ����ģʽ����ʾ��Ϣ
		CString strSysState;
		pSysState->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strSysState);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strSysState);
		return 0;
	}

	return m_pPxCmmOptrInterface->Send(pSysState);
}


long CSttMqttEngineBase::ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdBase *pSttCmd, long nCmdExecStatus, const CString &strDeviceID)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pSttCmd);

	oSysState.Set_ExecStatus(nCmdExecStatus);
	oSysState.SetParasDataAttr(STT_CMD_PARA_DeviceSN, strDeviceID);

	if (m_pPxCmmOptrInterface == NULL && pCmmOptrInterface == NULL)
	{//2021-8-5  lijunqing ����ģʽ����ʾ��Ϣ
		CString strSysState;
		oSysState.GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strSysState);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strSysState);
		return 0;
	}

	return m_pPxCmmOptrInterface->Send(&oSysState);
}

long CSttMqttEngineBase::ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, int nCmdType, char *pszCmdID, BOOL bIsSuccess)
{
	return 0;
}

long CSttMqttEngineBase::ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttSysState *pSysState, BOOL bSpyAllCmd)
{
	return 0;
}

