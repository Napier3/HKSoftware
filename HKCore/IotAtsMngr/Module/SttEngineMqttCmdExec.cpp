#include "stdafx.h"
#include "SttEngineMqttCmdExec.h"
#include "SttMqttClientTool.h"
#include "SttMqttClientEngineConfig.h"
#include "SensorProtocol/SensorProtocalEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttEngineMqttCmdExec::CSttEngineMqttCmdExec(CSttSocketDataBase *pRefSocket)
{
	//��װ�ò��ԣ�װ��ID�������ļ��л�ȡ
	CSttMqttClientEngineConfig::GetMqttDeviceID(m_strID);
	m_pRefSocket = pRefSocket;

	m_bExitThread = FALSE;
	m_bSuspendThread = TRUE;
}

CSttEngineMqttCmdExec::~CSttEngineMqttCmdExec()
{
	m_bExitThread = TRUE;
	m_bSuspendThread = TRUE;

	CTickCount32 oTick;
	while(m_pThread != NULL)
	{
		oTick.DoEvents(5);
	}
}

long CSttEngineMqttCmdExec::ProcessRecvPacket(char *pBuf,long nLen,CMqttPpProcedure *pProcedure,CMqttPpPrase **ppPrase)
{
	SensorPkgInfo oSensorPkgInfo;
	long nRet = CSensorProtocalEngine::ProcessRecvPacket((BYTE *)pBuf,nLen,oSensorPkgInfo);
	if (nRet != PP_PRASE_SUCCESS)
	{//�����Ƿְ�δ���룬��У��ʧ��
		return nRet;
	}

	//����֡ͷ����ƥ������ڵ�
	*ppPrase = m_oMqttPpTemplate.FindPrase(oSensorPkgInfo.m_nPkgType,oSensorPkgInfo.m_nCtrlType,oSensorPkgInfo.m_nRequestSetFlag);
	if (*ppPrase == NULL)
	{//��ǰ�����ڽ����������Ҳ���
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ������ġ�%d,%d,%d���ڽ����������Ҳ���")
			,oSensorPkgInfo.m_nPkgType,oSensorPkgInfo.m_nCtrlType,oSensorPkgInfo.m_nRequestSetFlag);
		return PP_PRASE_ErrType_NOTFINDPRASE;
	}

	CMqttPpAck *pFindAck = pProcedure->FindAck((*ppPrase)->m_strID);
	if (pFindAck == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ�������ġ�%s�������ڴ�Ӧ��"),(*ppPrase)->m_strID);
		return PP_PRASE_ErrType_NOTACK;
	}

	int nParaCnt = 0,nFragInd = 0,nPkgType = 0;
	sensor_pkg_get_info((BYTE *)pBuf,nParaCnt,nFragInd,nPkgType);

	if (oSensorPkgInfo.m_pFragSDUBuf == NULL)
	{//���Ƿְ�
		if (IsPacketCtrlType(nPkgType))
		{//���Ʊ���
			sensor_pkt_get_paraDatas((BYTE *)(pBuf+SENSOR_PKG_INDEX_CTRLDATA),nParaCnt,oSensorPkgInfo,*ppPrase);
		}
		else
		{
			sensor_pkt_get_paraDatas((BYTE *)(pBuf+SENSOR_PKG_INDEX_DATA),nParaCnt,oSensorPkgInfo,*ppPrase);
		}
	}
	else
	{//�ְ�
		sensor_pkt_get_paraDatas(oSensorPkgInfo.m_pFragSDUBuf,nParaCnt,oSensorPkgInfo,*ppPrase);
	}

	//����Prase�ڵ�����
	return UpdatePraseValue(oSensorPkgInfo,*ppPrase);
}

long CSttEngineMqttCmdExec::UpdateSysState_MsgSendRecv(CSttSysState &oSysState)
{
	CString strCurMacroID = GetCurMacroID();
	CSttParas *pParas = oSysState.GetSttParas();
	CDataGroup *pPkgGroup = (CDataGroup *)pParas->FindByID(strCurMacroID);
	if (pPkgGroup == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("��ǰ�޽�������"));
		return PP_PRASE_ErrType_NOPKG;
	}

	CMqttPpProcedure *pProcedure = m_oMqttPpTemplate.FindProcedure(strCurMacroID);
	if (pProcedure == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ�����%s��δ�滮"),strCurMacroID);
		return PP_PRASE_ErrType_NOPROCEDURE;
	}
	
	POS pos = pPkgGroup->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmValue *pValue = NULL;
	long nRet = 0;

	while(pos != NULL)
	{
		pData = (CDvmData *)pPkgGroup->GetNext(pos);
		if (pData->m_strID != _T("Rcv"))
		{
			continue;
		}

		pValue = (CDvmValue *)pData->GetHead();
		if (pValue == NULL)
		{
			continue;
		}
		if (pValue->m_strValue.IsEmpty())
		{
			continue;
		}

		char *pBuf = NULL;
		long nLen = CString_to_char(pValue->m_strValue,&pBuf);

		CMqttPpPrase *pPrase = NULL;
		nRet = ProcessRecvPacket(pBuf,nLen,pProcedure,&pPrase);
		delete pBuf;

		if (nRet != PP_PRASE_SUCCESS)
		{
			if (nRet != PP_PRASE_ErrType_FRAG)
			{
				return nRet;
			}
		}
	}

	return nRet;
}

long CSttEngineMqttCmdExec::UpdateSysState_MonitorPrase(CSttSysState &oSysState)
{
	CString strCurMacroID = GetCurMacroID();
	CSttParas *pParas = oSysState.GetSttParas();
	CDataGroup *pPkgGroup = (CDataGroup *)pParas->FindByID(strCurMacroID);
	if (pPkgGroup == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("��ǰ�޽�������"));
		return PP_PRASE_ErrType_NOPKG;
	}

	CMqttPpProcedure *pProcedure = m_oMqttPpTemplate.FindProcedure(strCurMacroID);
	if (pProcedure == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ�����%s��δ�滮"),strCurMacroID);
		return PP_PRASE_ErrType_NOPROCEDURE;
	}

	POS pos = pPkgGroup->GetHeadPosition();
	CDvmData *pData = (CDvmData *)pPkgGroup->GetTail();
	if (pData == NULL)
	{
		return PP_PRASE_ErrType_NOPKG;
	}
	if (pData->m_strID != _T("Rcv"))
	{
		return PP_PRASE_ErrType_NOPKG;
	}
	CDvmValue *pValue = (CDvmValue *)pData->GetHead();
	if (pValue == NULL)
	{
		return PP_PRASE_ErrType_NOPKG;
	}
	if (pValue->m_strValue.IsEmpty())
	{
		return PP_PRASE_ErrType_NOPKG;
	}

	long nRet = 0;
	char *pBuf = NULL;
	long nLen = CString_to_char(pValue->m_strValue,&pBuf);

	CMqttPpPrase *pPrase = NULL;
	nRet = ProcessRecvPacket(pBuf,nLen,pProcedure,&pPrase);
	delete pBuf;

	if (nRet != PP_PRASE_SUCCESS)
	{
		if (nRet != PP_PRASE_ErrType_FRAG)
		{
			return nRet;
		}
	}

	//���²����б�
	UpdateDatasByPrase(*pParas,pPrase);

	return nRet;
}

long CSttEngineMqttCmdExec::UpdateSysState_WarningPraseReply(CSttSysState &oSysState)
{
	return UpdateSysState_MonitorPrase(oSysState);
}

void CSttEngineMqttCmdExec::UpdateSysState(CSttSysState &oSysState)
{
	CString strCurMacroID = GetCurMacroID();
	CSttParas *pParas = oSysState.GetSttParas();
	long nRet = 0;
	
	if (strCurMacroID == STT_MACRO_ID_MSGRCVSEND)
	{
		nRet = UpdateSysState_MsgSendRecv(oSysState);
		//���½���ж�
		UpdateRsltJudge(nRet,pParas);
	}
	else if (strCurMacroID == STT_MACRO_ID_MONITORPRASE)
	{
		nRet = UpdateSysState_MonitorPrase(oSysState);
		//���½���ж�
		UpdateRsltJudge(nRet,pParas);
	}
	else if (strCurMacroID == STT_MACRO_ID_WARNINGPRASEREPLY)
	{
		nRet = UpdateSysState_WarningPraseReply(oSysState);
		//���½���ж�
		UpdateRsltJudge(nRet,pParas);
	}
}

BOOL CSttEngineMqttCmdExec::OnMqttMsgRecieve(CSttSysState &oSysState)
{
	if (m_bSuspendThread)
	{
		return FALSE;
	}
	if (oSysState.m_strID != m_oCurTestCmd.m_strID)
	{
		return FALSE;
	}

	if (oSysState.m_strID != STT_CMD_TYPE_TEST_StartTest)
	{//���ǿ�ʼ���������Ӧ��ֱ��ת���ظ�
		m_bSuspendThread = TRUE;
		return m_pRefSocket->SendSysState(&oSysState);
	}

	//����macro id��Щ���������жϸ���
	UpdateSysState(oSysState);

	//�����StartTest������Ӧ������TestFinish�¼�����
	CSttSysState oReportSysState;
	oReportSysState.UpdateSysStateHead(&m_oCurTestCmd);
	oReportSysState.m_strID = SYS_STATE_EVENT_OnTestFinished;
	oReportSysState.SetRetType(SYS_STATE_RETTYPE_EVENT);

	CSttMacro *pMacro = oReportSysState.GetSttMacro();
	pMacro->m_strID = GetCurMacroID();

	CSttResults *pResults = pMacro->GetResults();
	CSttParas *pParas = oSysState.GetSttParas();
	pResults->AttachParas(pParas);
	pParas->RemoveAll();

	m_bSuspendThread = TRUE;
	return m_pRefSocket->SendSysState(&oReportSysState);
}

BOOL CSttEngineMqttCmdExec::IsCmdTimeOut()
{
	DWORD dwCurTime = GetTickCount();

	return (dwCurTime - m_dwStartTime >= m_nTimeOut);
}

void CSttEngineMqttCmdExec::ReplyCmdTimeOut()
{
	m_bSuspendThread = TRUE;

	if (m_oCurTestCmd.m_strID != STT_CMD_TYPE_TEST_StartTest)
	{//���ǿ�ʼ���������Ӧ��ֱ��ת���ظ�
		ReturnSysState(STT_CMD_ExecStatus_TIMEOUT);
		return;
	}

	//�����StartTest������Ӧ������TestFinish�¼�����
	CSttSysState oReportSysState;
	oReportSysState.UpdateSysStateHead(&m_oCurTestCmd);
	oReportSysState.m_strID = SYS_STATE_EVENT_OnTestFinished;
	oReportSysState.SetRetType(SYS_STATE_RETTYPE_EVENT);

	CSttMacro *pMacro = oReportSysState.GetSttMacro();
	pMacro->m_strID = GetCurMacroID();

	CSttResults *pResults = pMacro->GetResults();
	pResults->SetDataAttr(STT_SYS_STATE_ID_ExecStatus, STT_CMD_ExecStatus_TIMEOUT);

	m_pRefSocket->SendSysState(&oReportSysState);
}

long CSttEngineMqttCmdExec::Process_Cmd_Test(CSttTestCmd &oTestCmd)
{
	if (!m_bSuspendThread)
	{
		ReturnSysState(STT_CMD_ExecStatus_FAILURE,NULL,NULL,&oTestCmd);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ���%s:%s��δ������"),m_oCurTestCmd.m_strID,GetCurMacroID());
		return 0;
	}
	
	oTestCmd.Copy(&m_oCurTestCmd);

	ReturnSysState(STT_CMD_ExecStatus_ACK);

	long nRet = 0;

	if (oTestCmd.m_strID == STT_CMD_TYPE_TEST_SetParameter)
	{
		nRet = Process_Cmd_Test_SetParameter(oTestCmd);
	}
	else if (oTestCmd.m_strID == STT_CMD_TYPE_TEST_StartTest)
	{
		nRet = Process_Cmd_Test_StartTest(oTestCmd);
	}
	else if (oTestCmd.m_strID == STT_CMD_TYPE_TEST_StopTest)
	{
		nRet = Process_Cmd_Test_StopTest(oTestCmd);
	}
	else
	{//������������

	}

	return nRet;
}

CString CSttEngineMqttCmdExec::GetCurMacroID()
{
	CSttMacro *pMacro = m_oCurTestCmd.GetSttMacro();

	return pMacro->m_strID;
}

BOOL CSttEngineMqttCmdExec::PublicTestCmd(CSttTestCmd &oTestCmd)
{
	CSttMacro *pMacro = oTestCmd.GetSttMacro();
	CSttParas *pParas = pMacro->GetParas();

	//��Ե�װ�ò��ԣ����DeviceSN
	pParas->AddNewData(_T("Device"),m_strID);

	//���ÿ��װ��ƴMQTT���ķ���
	char *pBuf = NULL;
	long nLen = oTestCmd.GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys,&pBuf);

	BOOL bRet = CSttMqttClientTool::PublicTopic(MQTT_TOPIC_TestCmd, pBuf,nLen);
	delete pBuf;

	if (!bRet)
	{
		ReturnSysState(STT_CMD_ExecStatus_FAILURE);
	}
	
	return bRet;
}

long CSttEngineMqttCmdExec::Process_Cmd_Test_SetParameter(CSttTestCmd &oTestCmd)
{
	//���MacroID=SetDeviceID,������װ��ID�͹�Լģ��
	CString strCurMacroID = GetCurMacroID();
	if (strCurMacroID == _T("SetDeviceID"))
	{
		CSttMacro *pMacro = oTestCmd.GetSttMacro();
		CSttParas *pParas = pMacro->GetParas();
		CString strDeviceID,strPpTemplate;

		pParas->GetDataValue(_T("Device"),strDeviceID);
		pParas->GetDataValue(_T("PpTemplate"),strPpTemplate);
		BOOL bRet = m_oMqttPpTemplate.OpenXmlFile(strPpTemplate,CMqttPpCfgXmlRWKeys::g_pXmlKeys);
		if (bRet)
		{
			m_strID = strDeviceID;
			return ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		}
		else
		{
			return ReturnSysState(STT_CMD_ExecStatus_FAILURE);
		}
	}

	if (!PublicTestCmd(oTestCmd))
	{
		return 0;
	}

	//������ʱ��
	m_dwStartTime = GetTickCount();
	m_nTimeOut = 5000;
	m_bSuspendThread = FALSE;

	return 1;
}

long CSttEngineMqttCmdExec::Process_Cmd_Test_StartTest(CSttTestCmd &oTestCmd)
{
	if (!PublicTestCmd(oTestCmd))
	{
		return 0;
	}

	ReturnSysState(STT_CMD_ExecStatus_SUCCESS);

	//������ʱ��
	m_dwStartTime = GetTickCount();
	m_nTimeOut = UpdateTimerOut(GetCurMacroID());
	m_bSuspendThread = FALSE;

	return 1;
}

long CSttEngineMqttCmdExec::Process_Cmd_Test_StopTest(CSttTestCmd &oTestCmd)
{
	if (!PublicTestCmd(oTestCmd))
	{
		return 0;
	}

	//������ʱ��
	m_dwStartTime = GetTickCount();
	m_nTimeOut = 5000;
	m_bSuspendThread = FALSE;

	return 1;
}

long CSttEngineMqttCmdExec::ReturnSysState(long nCmdExecStatus,CSttCmdData *pRetData,CSttSocketDataBase *pSocket,CSttTestCmd *pTestCmd)
{
	if ((m_pRefSocket == NULL) && (pSocket == NULL))
	{
		return 0;
	}

	CSttSysState oSysState;
	if (pTestCmd == NULL)
	{
		pTestCmd = &m_oCurTestCmd;
	}
	oSysState.UpdateSysStateHead(pTestCmd);

	if (pRetData != NULL)
	{//���ؽ������
		oSysState.AppendParas(*pRetData);
	}

	oSysState.Set_ExecStatus(nCmdExecStatus);

	if (pSocket != NULL)
	{
		return pSocket->SendSysState(&oSysState);
	}
	else
	{
		return m_pRefSocket->SendSysState(&oSysState);
	}
}

void *CSttEngineMqttCmdExec::TestCmdExecThread(LPVOID lParam)
{
	CSttEngineMqttCmdExec *pCmdExec = (CSttEngineMqttCmdExec *)lParam;

	while(TRUE)
	{
		if (pCmdExec->m_bExitThread)
		{
			break;
		}

		if (pCmdExec->m_bSuspendThread)
		{
			Sleep(100);
			continue;
		}

		if (pCmdExec->IsCmdTimeOut())
		{
			pCmdExec->ReplyCmdTimeOut();
			continue;
		}

		Sleep(20);
	}

	pCmdExec->m_pThread = NULL;
	return (void *)0;
}

/////////////////////////////////////

void UpdateRsltJudge(long nRslt,CSttParas *pParas)
{
	CString strRes = _T("�ϸ�");
	switch (nRslt)
	{
	case PP_PRASE_ErrType_FRAG:
		strRes = _T("��Ƭ������");
		break;
	case PP_PRASE_ErrType_CRCERR:
		strRes = _T("CRCУ�����");
		break;
	case PP_PRASE_ErrType_NOTFINDPRASE:
		strRes = _T("δ�ҵ���������");
		break;
	case PP_PRASE_ErrType_NOTACK:
		strRes = _T("�����ڴ�Ӧ��");
		break;
	case PP_PRASE_ErrType_PARANOTMATCH:
		strRes = _T("������ƥ��");
		break;
	case PP_PRASE_ErrType_PARALENERR:
		strRes = _T("�����������ȷǷ�");
		break;
	case PP_PRASE_ErrType_NOPKG:
		strRes = _T("�޹��̱���");
		break;
	case PP_PRASE_ErrType_NOPROCEDURE:
		strRes = _T("û�����ý�������");
		break;
	default:
		strRes = _T("�ϸ�");
		break;
	}

	pParas->SetDataAttr(STT_PARA_ID_RSLTJUDGE, nRslt);
	pParas->SetDataAttr(STT_PARA_ID_RSLTDSC, strRes);
}