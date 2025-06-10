#include "stdafx.h"
#include "SttSmartTestCom_Flow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSttSmartTestCom_Flow, CWnd)

CSttSmartTestCom_Flow::CSttSmartTestCom_Flow()
{

}

CSttSmartTestCom_Flow::~CSttSmartTestCom_Flow()
{

}

/*
<ats-cmd name="" id="CreateTest" testor="" >
    <paras name="" id="">
        <data id="test-id" value="" /> 【测试标识】
+测试定义：
        <data id="gbxml-file" value="*.ppxml" /> 【规约模板文件】
        <data name="EngineProgID" id="EngineProgID" value=""/>
        <data id="ppxml-file" value="*.ppxml" /> 【规约模板文件】
        <data id="dvm-file" value="*.xml" />  【点表文件】
        <data id="cmm-cfg-file" value="*.xml" />  【通信地址设置文件】
        <group id="omm-config" >  【通信地址设置】
            ...........................
        </group>
或者：
        <data id="TestDefine" value="" ><![CADATA[   创建测试的定义  ]]></data>
    </paras>
</ats -cmd>
*/

/*
<ats-cmd name="" id="CreateTest" testor="">
	<paras>
		<data name="测试模板" id="gbxml-file" value="SZNR-TTU.gbexe"/>
		<data name="测试模板" id="gbxml-file_s" value="……………"/>    //e-Report/Template
		【以下部分兼容老版本数据格式】
		<data name="" id="DeviceID" data-type="" value="SZNR-TTU"/>
		<data name="规则文件" id="ppxml-file" value="SZNR-TTU.ppxml"/>
		<data name="模型文件" id="dvm-file" value="SZNR-TTU.xml"/>
		<data name="报告记录文件" id="gbrpt-file" value="SZNR-TTU202012131427"/>
		<data name="被测装置引擎" id="EngineProgID" value="PpEngine"/>
		<group name="" id="comm-config" data-type="" value="">
			<data name="" id="tcp-client" data-type="" value="">
				<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
				<value name="" id="local-port" data-type="" value="20183"/>
				<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
				<value name="" id="remote-port" data-type="" value="2404"/>
			</data>
		</group>
		【以下部分为物联测试设备以及被测设备信息】
		<group id="devices">
			<group id="device">
				<data id="SN" value="123456789"/>
				<data id="EngineProgID" value="PpEngine"/>
				<data name="规则文件" id="ppxml-file" value="SZNR-TTU.ppxml"/>
				<data name="规则文件" id="ppxml-file_s" value="…… "/>  //e-Protocol/Template
				<data id="dvm-file" value="SZNR-TTU.xml"/>
				<data id="dvm-file_s" value="…… "/>   //e-Protocol/Library;[固定此路径，创建测试、编辑模板都从这个路径下]
				<data id="remote-ip" value="127.0.0.1"/>
				<data id="remote-port" value="9988"/>
			</group>
			……
		</group>
		<group id="test-apps">
			<group id="test-app">
				<data id="SN" value="123456789"/>
				<data id="EngineProgID" value="IotVm"/>
				<data id="dvm-file" value="MacroTest.xml"/>
				<data id="dvm-file_s" value="…… "/>   //测试仪不需要这个
				<data id="remote-ip" value="127.0.0.1"/>
				<data id="remote-port" value="9988"/>
			</group>
			……
		</group>
	</paras>
</ats-cmd>
*/
//如果没有传递测试模板参数，则表示打开已有测试记录，否则创建新的测试记录
long CSttSmartTestCom_Flow::Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	//先调用基类的创建测试，有问题再重载
	return CSttSmartTestCom::Ats_CreateTest(oAtsCmdDrv, pSttProtocol);
// 	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
// 
// 	CSttParas *pParas = pAtsCmd->GetSttParas();
// 	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
// 
// 	//pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, m_strBenchSN);
// 	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
// 
// 	if (pDevices != NULL)
// 	{
// 		m_pDevices = (CDataGroup *)pDevices->CloneEx(TRUE, TRUE);
// 
// 		if (m_strDeviceSN.IsEmpty() && m_pDevices != NULL)
// 		{
// 			CDataGroup *pFirstDevice = (CDataGroup *)m_pDevices->GetHead();
// 			pFirstDevice->GetDataValue(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
// 		}
// 	}
// 
// 	CSttSysState oSysState;
// 	CSttParas *pParasReturn = oSysState.GetSttParas();
// 	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
// 
// 	ReturnSysState_REPLY(pSttProtocol, pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
// 
// 	if (m_pXSmartTestClient == NULL)
// 	{
// 		InitSmartTestCom();
// 	}
// 
// 	if (m_pXSmartTestClient == NULL)
// 	{
// 		ReturnSysState_REPLY(pSttProtocol, pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
// 		return -1;
// 	}
// 
// 	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("正在创建测试，请稍后……"));
// 	
// 	//2021-8-4  lijunqing   
// 	m_pXSmartTestClient->AddEventSink(_T("SmartTestService.TestEventSink"), m_strDeviceSN);
// 
//     long nRet = m_pXSmartTestClient->CreateTest(pParas);
// 
// 	if (nRet != SMART_TEST_COM_EXEC_SUCC)
// 	{
// 		ReturnSysState_REPLY(pSttProtocol, pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
// 		return -1;
// 	}
// 	else
// 	{
// 		//创建成功，需要返回gbrpt-file
// // 		CString strGbrptFile;  //如何获取？
// // 		pParasReturn->AddNewData(XPARA_ID_GBRPTFILE, strGbrptFile);
// 		ReturnSysState_REPLY(pSttProtocol, pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
// 	}
// 
// 	return nRet;
}

long CSttSmartTestCom_Flow::Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	CString strDeviceSN;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_ConfigTest);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_FlowSetBench);
		return -1;
	}

	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pTestApps = (CDataGroup *)pParas->FindByID(XPARA_ID_test_apps);
	CString  strTestApps;

	if (pTestApps != NULL)
	{
		POS pos = pTestApps->GetHeadPosition();
		pTestApps->m_strDataType = XPARA_ID_test_apps;
		CDataGroup *pTestApp = NULL;

		while (pos != NULL)
		{
			pTestApp = (CDataGroup *)pTestApps->GetNext(pos);
			pTestApp->m_strDataType = XPARA_ID_test_app;
		}

		pTestApps->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strTestApps);
	}

	long nRet = m_pXSmartTestClient->ConfigTest(strDeviceSN, strTestApps);

	if ( nRet < 0)
	{
		pParasReturn->m_strTextParasID.Empty();
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_FlowSetBench);
		return -1;
	}
	else
	{

		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_FlowSetBench);
	}

	return 0;
}