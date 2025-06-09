//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestFlowsEvx.cpp  CAtsSvrTestFlowsEvx


#include "stdafx.h"
#include "AtsSvrTestFlowsEvx.h"

CAtsSvrTestFlowsEvx::CAtsSvrTestFlowsEvx()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrTestFlowsEvx::~CAtsSvrTestFlowsEvx()
{
}

CBaseObject* CAtsSvrTestFlowsEvx::Clone()
{
	CAtsSvrTestFlowsEvx *p = new CAtsSvrTestFlowsEvx();
	Copy(p);
	return p;
}


CExBaseObject* CAtsSvrTestFlowsEvx::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrTestFlowKey)
	{
		pNew = new CAtsSvrTestFlowEvx();
	}

	return pNew;
}

CExBaseObject* CAtsSvrTestFlowsEvx::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRTESTFLOW)
	{
		pNew = new CAtsSvrTestFlowEvx();
	}

	return pNew;
}

long CAtsSvrTestFlowsEvx::Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	CString strDeviceSN, strBenchSN;
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();

	//判断是否为CreateTest命令，如果是：
	//获取DevieSN，根据DeviceSN创建TestFlow，然后调用TestFlow的Process_Cmd_Ats
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, strBenchSN);
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);

	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);

	if (pDevices != NULL)
	{
		if (strDeviceSN.IsEmpty() && pDevices != NULL)
		{
			CDataGroup *pFirstDevice = (CDataGroup *)pDevices->GetHead();
			pFirstDevice->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);
		}
	}

	if (strDeviceSN.GetLength() <= 2)
	{
		pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);
		pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);

		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("AtsSvrTestFlowsEvx::Process_Cmd_Ats AtsCmd Error "));
		return -1;
	}

	CAtsSvrTestFlowEvx *pFlow = (CAtsSvrTestFlowEvx*)FindByID(strDeviceSN);

	if (pFlow == NULL)
	{
		if (pAtsCmd->m_strID != STT_CMD_TYPE_ATS_CreateTest)
		{//只有创建测试指令CreateTest才new flow
			pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface()
				, STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);
			pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface()
				, STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);

			return 0;
		}

		pFlow = new CAtsSvrTestFlowEvx();
		pFlow->m_strID = strDeviceSN;
		pFlow->m_strOutSysID = pAtsCmd->m_strFromSN;
		pFlow->m_strDeviceSN = strDeviceSN;
		pFlow->m_strBenchSN = strBenchSN;
		AddNewChild(pFlow);
		g_theSttOutMqttClient->MqttAdd(pFlow);
		pFlow->Process_Cmd_Ats(oAtsCmdDrv);
	}
	else
	{//已经存在，执行失败
		if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_CreateTest)
		{
			pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);
			pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);
		}
		else
		{
			//除了CreateTest之外的指令，例如：STT_CMD_TYPE_ATS_FlowSetBench，需要作处理
			pFlow->Process_Cmd_Ats(oAtsCmdDrv);
		}
	}

	return 0;
}

