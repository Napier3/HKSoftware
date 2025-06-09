//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestFlowEvx.cpp  CAtsSvrTestFlowEvx


#include "stdafx.h"
#include "AtsSvrTestFlowEvx.h"
#include "AtsSvrTestFlowsEvx.h"

#include "AtsSvrServiceEvx.h"
#include "../../../../SttStudio/Module/SmartTestInterface/SttSmartTestSvrFactory.h"


CAtsSvrTestFlowEvx::CAtsSvrTestFlowEvx()
{
	//初始化属性

	//初始化成员变量
	m_pCommConfig = NULL;
	m_pTestApps = NULL;

	m_nTestStateGunA = 0;
	m_nTestStateGunB = 0;
	m_pSmartTestSvr_GunB = NULL;
}

CAtsSvrTestFlowEvx::~CAtsSvrTestFlowEvx()
{
	
}

BOOL CAtsSvrTestFlowEvx::MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser, const CString &strDeviceSN)
{
	if (strDeviceSN == oSttMqttTopicParser.m_pszSubTopic[0])
	{
		return TRUE;
	}

	if (strDeviceSN == oSttMqttTopicParser.m_pszSubTopic[1])
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CAtsSvrTestFlowEvx::MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser)
{
	if (MqttMatch(oSttMqttTopicParser, m_strDeviceSN))
	{
		return TRUE;
	}

	if (MqttMatch(oSttMqttTopicParser, m_strDeviceSN+EVDX_GUN_SN_A))
	{
		return TRUE;
	}

	if (MqttMatch(oSttMqttTopicParser, m_strDeviceSN+EVDX_GUN_SN_B))
	{
		return TRUE;
	}

	if (MqttMatch(oSttMqttTopicParser, m_strDeviceSN+EVDX_GUN_SN_AB))
	{
		return TRUE;
	}

	if (MqttMatch(oSttMqttTopicParser, m_strBenchSN))
	{
		return TRUE;
	}

	return FALSE;
}

CBaseObject* CAtsSvrTestFlowEvx::Clone()
{
	CAtsSvrTestFlowEvx *p = new CAtsSvrTestFlowEvx();
	Copy(p);
	return p;
}

//////////////////////////////////////////////////////////////////////////
void CAtsSvrTestFlowEvx::InitGunXParas(CSttAtsCmd *pAtsCmd)
{
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_GunCount, m_nGunCount);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_GunARptFile, m_strGunARptFile);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_GunBRptFile, m_strGunBRptFile);

	InitGunRptFile();
}

void CAtsSvrTestFlowEvx::InitGunXParas(CDataGroup *pDevices)
{
	if (pDevices == NULL)
	{
		return;
	}

	CDataGroup *pDevice = (CDataGroup*)pDevices->FindByID(XPARA_ID_device);

	if (pDevice == NULL)
	{
		return;
	}

	stt_GetDataValueByID(pDevice, STT_CMD_PARA_GunCount, m_nGunCount);
	stt_GetDataValueByID(pDevice, STT_CMD_PARA_GunARptFile, m_strGunARptFile);
	stt_GetDataValueByID(pDevice, STT_CMD_PARA_GunBRptFile, m_strGunBRptFile);

	InitGunRptFile();
}

void CAtsSvrTestFlowEvx::InitGunRptFile()
{
	if (m_strGunARptFile.GetLength() > 1)
	{
		return;
	}

	if (m_nGunCount == 2)
	{
		m_strGunARptFile = m_strDeviceSN + _T("_A.gbrpt");
		m_strGunARptFile = m_strReportPath + m_strGunARptFile;
		m_strGunBRptFile = m_strDeviceSN + _T("_B.gbrpt");
		m_strGunBRptFile = m_strReportPath + m_strGunBRptFile;
	}
	else//if (m_nGunCount == 2)
	{
		m_strGunARptFile = m_strDeviceSN + _T(".gbrpt");
		m_strGunARptFile = m_strReportPath + m_strGunARptFile;
	}
}

/*
<ats-cmd name="" id="CreateTest" testor="">
	<paras>
		<data name="测试模板" id="gbxml-file" value="SZNR-TTU.gbexe"/>
		<data name="测试模板" id="gbxml-file_s" value="……………"/> 
		<data name="报告模板" id="doc-file_s" value="……………"/> 
		<data name="" id="DeviceSN" data-type="" value="SZNR-TTU"/>
		<group id="devices">
			<group id="device">
				<data id="DeviceSN" value="123456789"/>
				<data id="Model" value="XXXX"/>     充电桩型号
				<data id="GunCount" value="1"/>     	枪的数量1或者2
				<data id="GunARptFile" value="XXXXXXX"/>   A枪测试报告
				<data id="GunBRptFile" value="XXXXXXX"/>   B枪测试报告  	
			</group>
		</group>
*/
long CAtsSvrTestFlowEvx::CreateSmartTestSvr(CSttAtsCmd *pAtsCmd)
{
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, m_strBenchSN);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_GunCount, m_nGunCount);

	InitGunXParas(pAtsCmd);
	InitGunXParas(m_pDevices);

	CSttAtsCmd *pAtsCmd_GunB = NULL;
	CSttAtsCmd *pAtsCmd_GunA = (CSttAtsCmd*)pAtsCmd->Clone();
	CSttParas *pParas = pAtsCmd_GunA->GetSttParas();
	pParas->DeleteByID(STT_CMD_PARA_GunCount);
	pParas->DeleteByID(STT_CMD_PARA_GunARptFile);
	pParas->DeleteByID(STT_CMD_PARA_GunBRptFile);

	CString strDeviceSN = m_strDeviceSN;

	if (m_nGunCount == 2)
	{
		strDeviceSN += EVDX_GUN_SN_A;
	}

	CString strGbXmlFile;
	m_oCreateTestParas.GetDataValue(XPARA_ID_GBXMLFILE, strGbXmlFile);
	pAtsCmd_GunA->AddNewParasData(STT_CMD_PARA_BenchSN, strDeviceSN);
	pAtsCmd_GunA->AddNewParasData(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pAtsCmd_GunA->AddNewParasData(XPARA_ID_GBXMLFILE, strGbXmlFile);
	
	if (m_pDevices != NULL)
	{
		pAtsCmd_GunA->AddNewParas(m_pDevices);
	}

	if (m_pTestApps != NULL)
	{
		pAtsCmd_GunA->AddNewParas(m_pTestApps);
	}

	//已经存在的报告数据，取消测试
	POS pos = m_oCreateTestParas.GetHeadPosition();
	CDvmData *pData = NULL;
	CDataGroup *pItemsSel = (CDataGroup*)pParas->AddNewGroup(STT_CMD_PARA_ItemsSel, STT_CMD_PARA_ItemsSel, STT_CMD_PARA_ItemsSel);
	CDataGroup *pItemSel = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)m_oCreateTestParas.GetNext(pos);

		if (pData->m_strDataType == XPARA_Val_Export_Para_RptFile)
		{
			pItemSel = pItemsSel->AddNewGroup(STT_CMD_PARA_ItemSel, STT_CMD_PARA_ItemSel, STT_CMD_PARA_ItemSel);
			pItemSel->AddNewData(STT_CMD_PARA_ItemPath, pData->m_strID);
			pItemSel->AddNewData(STT_CMD_PARA_Enable, _T("0"));
		}
	}
	
	if (m_nGunCount == 2)
	{
		pAtsCmd_GunB = (CSttAtsCmd *)pAtsCmd_GunA->Clone();
	}

	//GunA
	CXObjectRefDriver oDrvA(pAtsCmd_GunA);
	pAtsCmd_GunA->AddNewParasData(XPARA_ID_GBRPTFILE, m_strGunARptFile);

	if (m_pSmartTestSvr == NULL)
	{
		m_pSmartTestSvr = CSttSmartTestSvrFactory::CreateSttSmartTestSvr(SmartTestSvr_Mqtt, strDeviceSN);
	}
	
	m_pSmartTestSvr->m_strDeviceSN = strDeviceSN;
	m_pSmartTestSvr->m_strBenchSN = m_strBenchSN;
	m_pSmartTestSvr->Process_Cmd_Ats(oDrvA, this);

	//等待100ms再创建，避免出现SmartTest MQTT ClientID相同
	Sleep(100);

	//GunB
	if (pAtsCmd_GunB != NULL)
	{
		CXObjectRefDriver oDrvB(pAtsCmd_GunB);
		strDeviceSN = m_strDeviceSN + EVDX_GUN_SN_B;
		pAtsCmd_GunB->AddNewParasData(XPARA_ID_GBRPTFILE, m_strGunBRptFile);
		pAtsCmd_GunB->AddNewParasData(STT_CMD_PARA_BenchSN, strDeviceSN);
		pAtsCmd_GunB->AddNewParasData(STT_CMD_PARA_DeviceSN, strDeviceSN);

		if (m_pSmartTestSvr_GunB == NULL)
		{
			m_pSmartTestSvr_GunB = CSttSmartTestSvrFactory::CreateSttSmartTestSvr(SmartTestSvr_Mqtt, strDeviceSN);
		}

		m_pSmartTestSvr_GunB->m_strDeviceSN = strDeviceSN;
		m_pSmartTestSvr_GunB->m_strBenchSN = m_strBenchSN;
		m_pSmartTestSvr_GunB->Process_Cmd_Ats(oDrvB, this);
	}

	return 0;
}

//不创建，开始测试的时候才创建
long CAtsSvrTestFlowEvx::Process_Cmd_Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv)
{
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);

	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, m_strGbxmlFile);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, m_strBenchSN);

	if (! pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_GunCount, m_nGunCount) )
	{//如果没有定义，则返回
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CreateTest not define [GunCount]"));
	}

	InitFlowReportPath();
	CSttParas *pParas = pAtsCmd->GetSttParas();
	InitTestDevices(pParas);
	InitCreateTestParas(pParas);
	InitGunXParas(pAtsCmd);
	InitGunXParas(m_pDevices);

	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);
	atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_CreateTest);

	return 0;
}


/*
<ats-cmd name="" id="StartTest" testor="ATS">
	<paras name="" id="">
		<data id=" DeviceSN " data-type="long" value="0" unit=""/>
		<data id="GunCount" value="1"/>     	枪的数量1或者2
		<data id="GunARptFile" value="XXXXXXX"/>   A枪测试报告
		<data id="GunBRptFile" value="XXXXXXX"/>   B枪测试报告  	
	</paras name>
</ats-cmd>
*/
long CAtsSvrTestFlowEvx::Process_Cmd_Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv)
{
	m_nTestStateGunA = 0;
	m_nTestStateGunB = 0;

	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_StartTest, STT_CMD_SYSSTATE_ATS);

	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	CSttAtsCmd *pNew = NULL;
	CString strDeviceSN = m_strDeviceSN;
	
	if (m_pSmartTestSvr == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Create And Start Test [%s]"), strDeviceSN.GetString());
		pNew = (CSttAtsCmd*)pAtsCmd->Clone();
		pNew->m_strID = STT_CMD_TYPE_ATS_CreateTest;
		CreateSmartTestSvr(pNew);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Start Test [%s]"), strDeviceSN.GetString());
		pNew = (CSttAtsCmd*)pAtsCmd->CloneEx();
		SendAtsCmdToAB(pAtsCmd,  STT_CMD_TYPE_ATS_StartTest);
	}

	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_StartTest, STT_CMD_SYSSTATE_ATS);
	strcpy(m_pszAtsSvrMsg, _T("开始测试...."));
	atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_StartTest);

	delete pNew;
	return 0;
}

long CAtsSvrTestFlowEvx::Process_Cmd_Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv)
{
	m_nTestStateGunA = 0;
	m_nTestStateGunB = 0;

	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_StopTest, STT_CMD_SYSSTATE_ATS);

	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	CSttAtsCmd *pNew = NULL;
	CString strDeviceSN = m_strDeviceSN;

	if (m_pSmartTestSvr == NULL)
	{
		ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_StopTest, STT_CMD_SYSSTATE_ATS);
		return 0;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Start Test [%s]"), strDeviceSN.GetString());
		pNew = (CSttAtsCmd*)pAtsCmd->CloneEx();
		SendAtsCmdToAB(pAtsCmd,  STT_CMD_TYPE_ATS_StopTest);
	}

	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_StopTest, STT_CMD_SYSSTATE_ATS);

	delete pNew;
	return 0;
}

long CAtsSvrTestFlowEvx::Process_Cmd_Ats_FlowSetBench(CXObjectRefDriver &oAtsCmdDrv)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, m_strBenchSN);

	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_FlowSetBench, STT_CMD_SYSSTATE_ATS);

	if (m_pSmartTestSvr != NULL)
	{
		m_pSmartTestSvr->m_strBenchSN = m_strBenchSN;
	}

	if (m_pSmartTestSvr_GunB != NULL)
	{
		m_pSmartTestSvr_GunB->m_strBenchSN = m_strBenchSN;
	}

	FlowSetBench_InitPara_Apps(oAtsCmdDrv);

	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_FlowSetBench, STT_CMD_SYSSTATE_ATS);

	strcpy(m_pszAtsSvrMsg, _T("设置工位"));
	atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_FlowSetBench);

	return 0;
}

void CAtsSvrTestFlowEvx::SendAtsCmdToAB(CSttAtsCmd *pAtsCmd, char *pszAtsCmd)
{
	if (m_nGunCount < 2)
	{//单枪，SmartTest直接处理
		return;
	}

	CSttMqttTopicCmbn oMqttCmbn;

	pAtsCmd->AddNewParasData(STT_CMD_PARA_DeviceSN, m_strDeviceSN + EVDX_GUN_SN_A);
	pAtsCmd->AddNewParasData(STT_CMD_PARA_BenchSN, m_strBenchSN);

	oMqttCmbn.AddSubTopic(m_strBenchSN);
	oMqttCmbn.AddSubTopic(m_strDeviceSN);
	oMqttCmbn.AddSubTopic("A");
	oMqttCmbn.AddSubTopic(MQTT_CMD_ID_AtsCmd);
	oMqttCmbn.AddSubTopic(pszAtsCmd);

	SendCmd(oMqttCmbn, pAtsCmd);

	oMqttCmbn.SetSubTopic(2, "B");
	pAtsCmd->AddNewParasData(STT_CMD_PARA_DeviceSN, m_strDeviceSN + EVDX_GUN_SN_B);
	SendCmd(oMqttCmbn, pAtsCmd);
}

long CAtsSvrTestFlowEvx::Process_Cmd_Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv)
{
	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_ACK, NULL, STT_CMD_TYPE_ATS_CloseTest, STT_CMD_SYSSTATE_ATS);
	ReturnSysState_REPLY(NULL, STT_CMD_ExecStatus_SUCCESS, NULL, STT_CMD_TYPE_ATS_CloseTest, STT_CMD_SYSSTATE_ATS);

	if (m_pSmartTestSvr != NULL)
	{
		delete  m_pSmartTestSvr;
		m_pSmartTestSvr = NULL;
	}

	if (m_pSmartTestSvr_GunB != NULL)
	{
		delete m_pSmartTestSvr_GunB;
		m_pSmartTestSvr_GunB = NULL;
	}

	if (m_nGunCount == 1)
	{
		return 0;
	}

	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	SendAtsCmdToAB(pAtsCmd, STT_CMD_TYPE_ATS_CloseTest);

	strcpy(m_pszAtsSvrMsg, _T("测试已经关闭"));
	atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_CloseTest);

	return 0;
}

long CAtsSvrTestFlowEvx::Process_Cmd_Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv)
{
	CAtsSvrTestFlow::Process_Cmd_Ats_SetItemsReport(oAtsCmdDrv);

	return 0;
}

/*
<ats-cmd name="" id="ExportReport" testor="ATS">
	<paras name="" id="">
		<data name="" id="BenchSN" data-type="" value="测试台SN/"/>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="CmbnDocs" data-type="" value="1"/>
	</paras>
</ats-cmd>
主题：充电桩SN/AtsCmd/ExportReport
CmbnDocs：组合汇总A、B枪报告。
*/
long CAtsSvrTestFlowEvx::Process_Cmd_Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	pAtsCmd->GetParasDataValueByID(_T("CmbnDocs"), m_nCmbnDocs);
	
	if (m_nGunCount == 1)
	{
		Ats_ExportReport(m_strGunARptFile, _T(""));
	}
	else
	{
		Ats_ExportReport(m_strGunARptFile, EVDX_GUN_SN_A);
	}

	return 0;
}

/*
<group name="GunA" id="GunA" data-type="Gun">
	<data name="" id="gbrpt-file" value="SZNR-TTU202012131427"/>
	<data name="" id="doc-file" value="SZNR-TTU202012131427.doc"/>
	<data name="" id="gbrpt-file_s" value="/../60193c6b41.gbrpt"/> 
	<data name=" id="doc-file_s" value="/../93c6b41.doc"/>
	<data name="" id="xml-file_s" value="/../93c6b41.xml"/>
</group>
*/
void CAtsSvrTestFlowEvx::Return_ExportFinish_AddFile(CDataGroup *pParent, const CString &strGbrptFile)
{
	CString strFileName;
	strFileName = GetFileNameFromFilePath(strGbrptFile);

	pParent->AddNewData(XPARA_ID_GBRPTFILE, strFileName);
	pParent->AddNewData(XPARA_ID_DOCRPTFILE, ChangeFilePostfix(strFileName, _T("doc")) );
	pParent->AddNewData(XPARA_ID_XMLRPTFILE, ChangeFilePostfix(strFileName, _T("xml")) );

	CString strUrlFile, strFile;
	strFile = strGbrptFile;

	return;
	if (atssvr_UploadFile(strFile, strUrlFile))
	{
		pParent->AddNewData(XPARA_ID_GBRPTFILE_S, strUrlFile);
	}

	strFile = ChangeFilePostfix(strGbrptFile, _T("doc"));
	if (atssvr_UploadFile(strFile, strUrlFile))
	{
		pParent->AddNewData(XPARA_ID_DOCRPTFILE_S, strUrlFile);
	}

	strFile = ChangeFilePostfix(strGbrptFile, _T("xml"));
	if (atssvr_UploadFile(strFile, strUrlFile))
	{
		pParent->AddNewData(XPARA_ID_XMLRPTFILE_S, strUrlFile);
	}
}

/*
<sys-state name="" id="ExportReport" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name=" " id="EventID" data-type="string" value="ExportFinish"/>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="BenchSN" value="测试台SN/"/>
		<data name="" id="gbrpt-file" value="SZNR-TTU202012131427"/>
		<data name="" id="doc-file" value="SZNR-TTU202012131427.doc"/>
		<data name="" id="gbrpt-file_s" value="/../60193c6b41.gbrpt"/> 
		<data name=" id="doc-file_s" value="/../93c6b41.doc"/>
		<data name="" id="xml-file_s" value="/../93c6b41.xml"/>
	</paras>
</sys-state>
*/
void CAtsSvrTestFlowEvx::Return_EVENT_ExportFinish_A()
{
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();

	Return_ExportFinish_AddFile(pParasReturn, m_strGunARptFile);

	Flow_Return_EVENT(oSysState, SYS_STATE_XEVENT_EVENTID_ExportFinish , STT_CMD_TYPE_ATS_ExportReport);
}

/*
<sys-state name="" id="ExportReport" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name=" " id="EventID" data-type="string" value="ExportFinish"/>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="BenchSN" value="测试台SN/"/>
		<data name="" id="doc-file" value="..2131427.doc"/>
		<data name="" id="doc-file_s" value="/../93c6b41.doc"/>
		<group name="GunA" id="GunA" data-type="Gun">
			<data name="" id="gbrpt-file" value="SZNR-TTU202012131427"/>
			<data name="" id="doc-file" value="SZNR-TTU202012131427.doc"/>
			<data name="" id="gbrpt-file_s" value="/../60193c6b41.gbrpt"/> 
			<data name="" id="doc-file_s" value="/../93c6b41.doc"/>
			<data name="" id="xml-file_s" value="/../93c6b41.xml"/>
		</group>
		<group name="GunB" id="GunB" data-type="Gun">
			<data name="" id="gbrpt-file" value="SZNR-TTU202012131427"/>
			<data name="" id="doc-file" value="SZNR-TTU202012131427.doc"/>
			<data name="" id="gbrpt-file_s" value="/../60193c6b41.gbrpt"/> 
			<data name="" id="doc-file_s" value="/../93c6b41.doc"/>
			<data name="" id="xml-file_s" value="/../93c6b41.xml"/>
		</group>
	</paras>
</sys-state>
*/
void CAtsSvrTestFlowEvx::Return_EVENT_ExportFinish_AB()
{
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();

	CDataGroup *pGun = pParasReturn->AddNewGroup(STT_CMD_PARA_GunA, STT_CMD_PARA_GunA, STT_CMD_PARA_Gun);
	Return_ExportFinish_AddFile(pGun, m_strGunARptFile);

	pGun = pParasReturn->AddNewGroup(STT_CMD_PARA_GunB, STT_CMD_PARA_GunB, STT_CMD_PARA_Gun);
	Return_ExportFinish_AddFile(pGun, m_strGunBRptFile);

	//汇总的报告
	CString strCmbRptFile = GetCmbnReportFile();
	pParasReturn->AddNewData(XPARA_ID_DOCRPTFILE, ChangeFilePostfix(strCmbRptFile, _T("doc")) );

	Flow_Return_EVENT(oSysState, SYS_STATE_XEVENT_EVENTID_ExportFinish , STT_CMD_TYPE_ATS_ExportReport);
}

long CAtsSvrTestFlowEvx::Process_Cmd_SysState_EVENT_ExportReport(CXObjectRefDriver &oAtsCmdDrv)
{
	delete m_pSmartTestSvr;
	m_pSmartTestSvr = NULL;

	if (m_nGunCount == 1)
	{//单枪，导出报告完成，自动测试已经发了ExportFinish
		Return_EVENT_ExportFinish_A();
		sprintf(m_pszAtsSvrMsg, _T("导出报告完成[%s]"), m_strGunARptFile.GetString());
		atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_ExportReport);
		return 0;
	}

	//导出A完成，接着导出B，然后进行报告合并
	CString strDeviceSN, strEventID;
	CSttSysState *pSysState = (CSttSysState*)oAtsCmdDrv.GetXObjectRef();
	pSysState->GetParasDataValueByID(STT_CMD_PARA_EventID, strEventID);

	if (strEventID != SYS_STATE_XEVENT_EVENTID_ExportFinish)
	{//不是导出报告完成事件，不进行处理
		return 0;
	}

	pSysState->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	strDeviceSN = strDeviceSN.Mid(m_strDeviceSN.GetLength());

	if (strDeviceSN == EVDX_GUN_SN_A)
	{
		Ats_ExportReport(m_strGunBRptFile, EVDX_GUN_SN_B);
	}
	else if (strDeviceSN == EVDX_GUN_SN_B)
	{
		Ats_CmbnReport();
	}
	else if (strDeviceSN == EVDX_GUN_SN_AB)
	{
		//合并报告完成，发送导出报告结束事件
		strcpy(m_pszAtsSvrMsg, _T("导出报告完成"));
		atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_ExportReport);
		Return_EVENT_ExportFinish_AB();
	}

	return 0;
}

long CAtsSvrTestFlowEvx::Process_Cmd_SysState_EVENT_TestStarted(CXObjectRefDriver &oAtsCmdDrv)
{
	if (m_nGunCount == 1)
	{//单枪，导出报告完成，自动测试已经发了ExportFinish
		sprintf(m_pszAtsSvrMsg, _T("测试完成[%s]"), m_strGunARptFile.GetString());
		atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_StartTest);
		return 0;
	}

	//导出A完成，接着导出B，然后进行报告合并
	CString strDeviceSN;
	CSttSysState *pSysState = (CSttSysState*)oAtsCmdDrv.GetXObjectRef();
	pSysState->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	strDeviceSN = strDeviceSN.Mid(m_strDeviceSN.GetLength());

	if (strDeviceSN == EVDX_GUN_SN_A)
	{
		m_nTestStateGunA = 1;
	}
	else if (strDeviceSN == EVDX_GUN_SN_B)
	{
		m_nTestStateGunB = 1;
	}

	if (strDeviceSN.GetLength() == 0)
	{//双枪模式下，发送综合测试开始指令，基本设备的SN
		return 0;
	}
	
	if (m_nTestStateGunA == 1 && m_nTestStateGunB == 1)
	{
		strcpy(m_pszAtsSvrMsg, "A枪、B枪都测试开始");
		atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_StartTest);

		CSttSysState oSysState;
		Flow_Return_EVENT(oSysState, SYS_STATE_EVENT_OnTestStarted , SYS_STATE_EVENT_OnTestStarted);
	}

	return 0;
}

long CAtsSvrTestFlowEvx::Process_Cmd_SysState_EVENT_TestStoped(CXObjectRefDriver &oAtsCmdDrv)
{
	if (m_nGunCount == 1)
	{//单枪，导出报告完成，自动测试已经发了ExportFinish
		sprintf(m_pszAtsSvrMsg, _T("测试停止[%s]"), m_strGunARptFile.GetString());
		atssvr_post_service_msg(this, SYS_STATE_EVENT_OnTestStoped);
		return 0;
	}

	//导出A完成，接着导出B，然后进行报告合并
	CString strDeviceSN;
	CSttSysState *pSysState = (CSttSysState*)oAtsCmdDrv.GetXObjectRef();
	pSysState->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	strDeviceSN = strDeviceSN.Mid(m_strDeviceSN.GetLength());

	if (strDeviceSN == EVDX_GUN_SN_A)
	{
		sprintf(m_pszAtsSvrMsg, _T("测试停止[%s]"), m_strGunARptFile.GetString());
		atssvr_post_service_msg(this, SYS_STATE_EVENT_OnTestStoped);
		m_nTestStateGunA = 1;
	}
	else if (strDeviceSN == EVDX_GUN_SN_B)
	{
		sprintf(m_pszAtsSvrMsg, _T("测试停止[%s]"), m_strGunBRptFile.GetString());
		atssvr_post_service_msg(this, SYS_STATE_EVENT_OnTestStoped);
		m_nTestStateGunB = 1;
	}

	if (strDeviceSN.GetLength() == 0)
	{//双枪模式下，发送综合指令，当前设备的SN
		return 0;
	}
	
	if (m_nTestStateGunA == 1 && m_nTestStateGunB == 1)
	{
		strcpy(m_pszAtsSvrMsg, "A枪、B枪都测试停止");
		atssvr_post_service_msg(this, SYS_STATE_EVENT_OnTestStoped);

		CSttSysState oSysState;
		Flow_Return_EVENT(oSysState, SYS_STATE_EVENT_OnTestStoped , SYS_STATE_EVENT_OnTestStoped);
	}

	return 0;
}

long CAtsSvrTestFlowEvx::Process_Cmd_SysState_EVENT_TestFinished(CXObjectRefDriver &oAtsCmdDrv)
{
	if (m_nGunCount == 1)
	{//单枪，导出报告完成，自动测试已经发了ExportFinish
		sprintf(m_pszAtsSvrMsg, _T("测试完成[%s]"), m_strGunARptFile.GetString());
		atssvr_post_service_msg(this, SYS_STATE_EVENT_OnTestFinished);
		return 0;
	}

	//导出A完成，接着导出B，然后进行报告合并
	CString strDeviceSN;
	CSttSysState *pSysState = (CSttSysState*)oAtsCmdDrv.GetXObjectRef();
	pSysState->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	strDeviceSN = strDeviceSN.Mid(m_strDeviceSN.GetLength());

	if (strDeviceSN == EVDX_GUN_SN_A)
	{
		sprintf(m_pszAtsSvrMsg, _T("测试完成[%s]"), m_strGunARptFile.GetString());
		atssvr_post_service_msg(this, SYS_STATE_EVENT_OnTestFinished);
		m_nTestStateGunA = 1;
	}
	else if (strDeviceSN == EVDX_GUN_SN_B)
	{
		sprintf(m_pszAtsSvrMsg, _T("测试完成[%s]"), m_strGunBRptFile.GetString());
		atssvr_post_service_msg(this, SYS_STATE_EVENT_OnTestFinished);
		m_nTestStateGunB = 1;
	}

	if (strDeviceSN.GetLength() == 0)
	{//双枪模式下，发送综合测试开始指令，基本设备的SN
		return 0;
	}

	if (m_nTestStateGunA == 1 && m_nTestStateGunB == 1)
	{
		strcpy(m_pszAtsSvrMsg, "A枪、B枪都测试完成");
		atssvr_post_service_msg(this, SYS_STATE_EVENT_OnTestFinished);

		CSttSysState oSysState;
		Flow_Return_EVENT(oSysState, SYS_STATE_EVENT_OnTestFinished , SYS_STATE_EVENT_OnTestFinished);
	}

	return 0;
}

/*
<ats-cmd name="" id="ExportReport" testor="ATS">
	<paras name="" id="">
		<data name="" id="ExportMode" data-type="ExportMode" value="single"/>
		<data name="" id="BenchSN" data-type="" value="测试台SN/"/>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="测试模板" id="gbxml-file_s" value="……………"/> 
		<data name="gbrpt-file" id="gbrpt-file" data-type="" value="1"/>
		<group name="rpt-files" id="rpt-files" data-type="rpt-files" >
			<group name="rpt-file" id="rpt-file" data-type="rpt-file" >
				<data id="ItemPath" data-type="string" value=""/>
				<data id="file" data-type="rpt-file" value="XXXXX.xml"/>
			</group>
			。。。。。。。。。。。。。。
		</group>
		<group name="globaldatas" id="globaldatas" data-type="rpt-files" >
			<data id="" data-type="string" value=""/>
			。。。。。。。。。。。。。。
		</group>
	</paras>
</ats-cmd>
如果定义了gbrpt-file，则将rpt-files合并到gbrpt-file，并导出
如果没定义gbrpt-file，则打开模板创建gbrpt-file，将rpt-files合并到gbrpt-file，并导出
Globaldatas：全局数据，采用绝对路径的方式，填入到报告对应的标签位置。
*/
void CAtsSvrTestFlowEvx::Ats_ExportReport(const CString &strGbRptFile, const CString &strGunID)
{
	CString strDeviceSN;
	strDeviceSN = m_strDeviceSN;

	if (strGunID.GetLength() > 0)
	{
		strDeviceSN += strGunID;
	}

	CSttAtsCmd *pAtsCmd = new CSttAtsCmd();
	pAtsCmd->m_strID = STT_CMD_TYPE_ATS_ExportReport;
	CSttParas *pSttParas = pAtsCmd->GetSttParas();
	pSttParas->AddNewData(XPARA_ID_Export_Mode, XPARA_Val_Export_Mode_single);
	pSttParas->AddNewData(STT_CMD_PARA_BenchSN, strDeviceSN);
	pSttParas->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pSttParas->AddNewData(XPARA_ID_GBXMLFILE, m_strGbxmlFile);
	pSttParas->AddNewData(XPARA_ID_GBRPTFILE, strGbRptFile);
	CDataGroup *pRptFiles = pSttParas->AddNewGroup(XPARA_Val_Export_Para_RptFiles, XPARA_Val_Export_Para_RptFiles, XPARA_Val_Export_Para_RptFiles);
	CDataGroup *pRptFile = NULL;

	POS pos = m_oCreateTestParas.GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)m_oCreateTestParas.GetNext(pos);

		if (pData->m_strDataType == XPARA_Val_Export_Para_RptFile)
		{
			pRptFile = pRptFiles->AddNewGroup(XPARA_Val_Export_Para_RptFile, XPARA_Val_Export_Para_RptFile, XPARA_Val_Export_Para_RptFile);
			pRptFile->AddNewData(STT_CMD_PARA_ItemPath, pData->m_strID);
			pRptFile->AddNewData(XPARA_Val_Export_Para_RptFile, pData->m_strValue);
		}
	}

	CXObjectRefDriver oDrvA(pAtsCmd);
	m_pSmartTestSvr = CSttSmartTestSvrFactory::CreateSttSmartTestSvr(SmartTestSvr_Mqtt, strDeviceSN);
	m_pSmartTestSvr->Process_Cmd_Ats(oDrvA, this);

	sprintf(m_pszAtsSvrMsg, _T("导出报告[%s]"), strGbRptFile.GetString());
	atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_ExportReport);

}

/*
<ats-cmd name="" id="ExportReport" testor="ATS">
	<paras name="" id="">
		<data name="" id="ExportMode" data-type="ExportMode" value="docs"/>
		<data name="" id="BenchSN" data-type="" value="测试台SN/"/>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="doc-file" data-type="" value="######.Doc"/>
		<group name="gbrpts" id="gbrpts" data-type="gbrpts" >
			<data id="gbrpt" data-type="gbrpt" value="XXXXX.gbrpt"/>
			。。。。。。。。。。。。。。
			<data id="gbrpt" data-type="gbrpt" value="XXXXX.gbrpt"/>
		</group>
		<group name="docs" id="docs" data-type="docs" >
			<data id="doc" data-type="doc" value="XXXXX.doc"/>
			。。。。。。。。。。。。。。
			<data id="doc" data-type="doc" value="XXXXX.doc"/>
		</group>
	</paras>
</ats-cmd>
doc-file：多个word文档合并的目标文档
Docs：待合并的多个word文档
*/
CString CAtsSvrTestFlowEvx::GetCmbnReportFile()
{
	CString strCmbnDocFile;
	strCmbnDocFile = m_strDeviceSN + _T(".doc");
	strCmbnDocFile = GetPathFromFilePathName(m_strGunARptFile) + strCmbnDocFile;
	return strCmbnDocFile;
}

void CAtsSvrTestFlowEvx::Ats_CmbnReport()
{
	CString strDeviceSN, strCmbnDocFile;
	strDeviceSN = m_strDeviceSN + EVDX_GUN_SN_AB;

	CSttAtsCmd *pAtsCmd = new CSttAtsCmd();
	CSttParas *pSttParas = pAtsCmd->GetSttParas();
	
	pAtsCmd->m_strID = STT_CMD_TYPE_ATS_ExportReport;
	pSttParas->AddNewData(XPARA_ID_Export_Mode, XPARA_Val_Export_Mode_docs);
	pSttParas->AddNewData(STT_CMD_PARA_BenchSN, strDeviceSN);
	pSttParas->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);
	
	strCmbnDocFile = GetCmbnReportFile();
	pSttParas->AddNewData(XPARA_ID_DOCRPTFILE, strCmbnDocFile);

	CDataGroup *pDocFiles = pSttParas->AddNewGroup(XPARA_Val_Export_Mode_docs, XPARA_Val_Export_Mode_docs, XPARA_Val_Export_Mode_docs);
	pDocFiles->AddNewData(XPARA_Val_Export_Para_doc, ChangeFilePostfix(m_strGunARptFile, _T("doc")));
	pDocFiles->AddNewData(XPARA_Val_Export_Para_doc, ChangeFilePostfix(m_strGunBRptFile, _T("doc")));

	CXObjectRefDriver oDrvA(pAtsCmd);
	m_pSmartTestSvr = CSttSmartTestSvrFactory::CreateSttSmartTestSvr(SmartTestSvr_Mqtt, strDeviceSN);
	m_pSmartTestSvr->Process_Cmd_Ats(oDrvA, this);

	sprintf(m_pszAtsSvrMsg, _T("合并报告[%s]"), strCmbnDocFile.GetString());
	atssvr_post_service_msg(this, STT_CMD_TYPE_ATS_ExportReport);
}

