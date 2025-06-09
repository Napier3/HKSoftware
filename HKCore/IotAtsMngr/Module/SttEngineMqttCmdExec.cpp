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
	//当装置测试，装置ID从配置文件中获取
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
	{//可能是分包未收齐，或校验失败
		return nRet;
	}

	//根据帧头查找匹配解析节点
	*ppPrase = m_oMqttPpTemplate.FindPrase(oSensorPkgInfo.m_nPkgType,oSensorPkgInfo.m_nCtrlType,oSensorPkgInfo.m_nRequestSetFlag);
	if (*ppPrase == NULL)
	{//当前报文在解析规则中找不到
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前结果报文【%d,%d,%d】在解析规则中找不到")
			,oSensorPkgInfo.m_nPkgType,oSensorPkgInfo.m_nCtrlType,oSensorPkgInfo.m_nRequestSetFlag);
		return PP_PRASE_ErrType_NOTFINDPRASE;
	}

	CMqttPpAck *pFindAck = pProcedure->FindAck((*ppPrase)->m_strID);
	if (pFindAck == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前交互报文【%s】不是期待应答。"),(*ppPrase)->m_strID);
		return PP_PRASE_ErrType_NOTACK;
	}

	int nParaCnt = 0,nFragInd = 0,nPkgType = 0;
	sensor_pkg_get_info((BYTE *)pBuf,nParaCnt,nFragInd,nPkgType);

	if (oSensorPkgInfo.m_pFragSDUBuf == NULL)
	{//不是分包
		if (IsPacketCtrlType(nPkgType))
		{//控制报文
			sensor_pkt_get_paraDatas((BYTE *)(pBuf+SENSOR_PKG_INDEX_CTRLDATA),nParaCnt,oSensorPkgInfo,*ppPrase);
		}
		else
		{
			sensor_pkt_get_paraDatas((BYTE *)(pBuf+SENSOR_PKG_INDEX_DATA),nParaCnt,oSensorPkgInfo,*ppPrase);
		}
	}
	else
	{//分包
		sensor_pkt_get_paraDatas(oSensorPkgInfo.m_pFragSDUBuf,nParaCnt,oSensorPkgInfo,*ppPrase);
	}

	//更新Prase节点数据
	return UpdatePraseValue(oSensorPkgInfo,*ppPrase);
}

long CSttEngineMqttCmdExec::UpdateSysState_MsgSendRecv(CSttSysState &oSysState)
{
	CString strCurMacroID = GetCurMacroID();
	CSttParas *pParas = oSysState.GetSttParas();
	CDataGroup *pPkgGroup = (CDataGroup *)pParas->FindByID(strCurMacroID);
	if (pPkgGroup == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("当前无交互过程"));
		return PP_PRASE_ErrType_NOPKG;
	}

	CMqttPpProcedure *pProcedure = m_oMqttPpTemplate.FindProcedure(strCurMacroID);
	if (pProcedure == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前测试项【%s】未规划"),strCurMacroID);
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
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("当前无交互过程"));
		return PP_PRASE_ErrType_NOPKG;
	}

	CMqttPpProcedure *pProcedure = m_oMqttPpTemplate.FindProcedure(strCurMacroID);
	if (pProcedure == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前测试项【%s】未规划"),strCurMacroID);
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

	//更新参数列表
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
		//更新结果判断
		UpdateRsltJudge(nRet,pParas);
	}
	else if (strCurMacroID == STT_MACRO_ID_MONITORPRASE)
	{
		nRet = UpdateSysState_MonitorPrase(oSysState);
		//更新结果判断
		UpdateRsltJudge(nRet,pParas);
	}
	else if (strCurMacroID == STT_MACRO_ID_WARNINGPRASEREPLY)
	{
		nRet = UpdateSysState_WarningPraseReply(oSysState);
		//更新结果判断
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
	{//不是开始测试命令的应答，直接转发回复
		m_bSuspendThread = TRUE;
		return m_pRefSocket->SendSysState(&oSysState);
	}

	//根据macro id有些测试项结果判断更新
	UpdateSysState(oSysState);

	//如果是StartTest命令结果应答，生成TestFinish事件返回
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
	{//不是开始测试命令的应答，直接转发回复
		ReturnSysState(STT_CMD_ExecStatus_TIMEOUT);
		return;
	}

	//如果是StartTest命令结果应答，生成TestFinish事件返回
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前命令【%s:%s】未结束。"),m_oCurTestCmd.m_strID,GetCurMacroID());
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
	{//其他测试命令

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

	//针对单装置测试，添加DeviceSN
	pParas->AddNewData(_T("Device"),m_strID);

	//针对每个装置拼MQTT报文发送
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
	//如果MacroID=SetDeviceID,则设置装置ID和规约模板
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

	//启动定时器
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

	//启动定时器
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

	//启动定时器
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
	{//返回结果数据
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
	CString strRes = _T("合格");
	switch (nRslt)
	{
	case PP_PRASE_ErrType_FRAG:
		strRes = _T("分片不完整");
		break;
	case PP_PRASE_ErrType_CRCERR:
		strRes = _T("CRC校验错误");
		break;
	case PP_PRASE_ErrType_NOTFINDPRASE:
		strRes = _T("未找到解析规则");
		break;
	case PP_PRASE_ErrType_NOTACK:
		strRes = _T("不是期待应答");
		break;
	case PP_PRASE_ErrType_PARANOTMATCH:
		strRes = _T("参数不匹配");
		break;
	case PP_PRASE_ErrType_PARALENERR:
		strRes = _T("参数解析长度非法");
		break;
	case PP_PRASE_ErrType_NOPKG:
		strRes = _T("无过程报文");
		break;
	case PP_PRASE_ErrType_NOPROCEDURE:
		strRes = _T("没有配置交互过程");
		break;
	default:
		strRes = _T("合格");
		break;
	}

	pParas->SetDataAttr(STT_PARA_ID_RSLTJUDGE, nRslt);
	pParas->SetDataAttr(STT_PARA_ID_RSLTDSC, strRes);
}