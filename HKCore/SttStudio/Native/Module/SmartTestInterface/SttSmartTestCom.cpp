#include "stdafx.h"
#include "SttSmartTestCom.h"
#include "../../../Module/BaseClass/StringSerializeBufferAscii.h"
#include "../SttCmd/GuideBook/SttItems.h"
#include "../../../IotAtsMngr/Module/SttMqttClientEngineConfig.h"
#include "../../../Module/XFileHttpClient/XFileHttpClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSttSmartTestCom, CWnd)

CSttSmartTestCom::CSttSmartTestCom()
{
	m_pXSmartTestClient = NULL;
	m_pDevices = NULL;
	m_WordApp = NULL;
	InitSmartTestCom();
}

CSttSmartTestCom::~CSttSmartTestCom()
{
	if (m_pDevices != NULL)
	{
		delete m_pDevices;
		m_pDevices = NULL;
	}

	if (m_WordApp != NULL)
	{
		m_WordApp.ReleaseDispatch();
		m_WordApp = NULL;
	}

	ExitSmartTestCom();
}

void CSttSmartTestCom::CreateWnd()
{
	CreateEx(0, AfxRegisterWndClass(0), _T("_Stt_SmartTest_Com_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
}

void CSttSmartTestCom::InitSmartTestCom()
{
	if (m_pXSmartTestClient == NULL)
	{
		m_pXSmartTestClient = new CXSmartTestClient();
		m_pXSmartTestClient->InitXSmartTestClient();
	}
}

void CSttSmartTestCom::ExitSmartTestCom()
{
	if (m_pXSmartTestClient != NULL)
	{
		m_pXSmartTestClient->ExitXSmartTestClient();
		delete m_pXSmartTestClient;
		m_pXSmartTestClient = NULL;
	}
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
		<data name="测试台标识" id="BenchSN" value="测试台SN/"/>
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
long CSttSmartTestCom::Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();

	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);

	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, m_strBenchSN);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	if (pDevices != NULL)
	{
		m_pDevices = (CDataGroup *)pDevices->CloneEx(TRUE, TRUE);

		if (m_strDeviceSN.IsEmpty() && m_pDevices != NULL)
		{
			CDataGroup *pFirstDevice = (CDataGroup *)m_pDevices->GetHead();
			pFirstDevice->GetDataValue(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
		}
	}

	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
	BOOL bRet = DownLoadAllFiles(pAtsCmd);

	if (!bRet)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface*)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -1;
	}

	//因为涉及到下载相关文件，将ACK的回复放到下载文件的地方：CAtsSvrMsgWnd::OnSttEngineCmdRcv(WPARAM wParam, LPARAM lParam)
	//ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest);

	if (m_pXSmartTestClient == NULL)
	{
		InitSmartTestCom();
	}

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -1;
	}

// 	CString strFile;
// 	strFile = _P_GetLibraryPath();
// 	strFile += _T("AtsCreateTestDefine.xml");
// 	pParas->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("正在创建测试，请稍后……"));
	
	//2021-8-4  lijunqing   
	//对于测试流模式，则m_strBenchSN应该为空，用m_strDeviceSN进行返回
	if (!m_strBenchSN.IsEmpty())
	{
		m_pXSmartTestClient->AddEventSink(_T("SmartTestService.TestEventSink"), m_strBenchSN);
	}
	else
	{
		m_pXSmartTestClient->AddEventSink(_T("SmartTestService.TestEventSink"), m_strDeviceSN);
	}	

	CSttGuideBook* pGuideBook = pParas->GetGuideBook();

	if (pGuideBook != NULL)
	{
		//若包含GuideBook的部分，先不处理
		pParas->Delete(pGuideBook);
		pParas->AttatchGuideBook(NULL);
	}

	CString strTestDefine;
	pParas->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strTestDefine);
    long nRet = m_pXSmartTestClient->CreateTest(strTestDefine);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
		return -1;
	}
	else
	{
		//创建成功，需要返回gbrpt-file
// 		CString strGbrptFile;  //如何获取？
// 		pParasReturn->AddNewData(XPARA_ID_GBRPTFILE, strGbrptFile);
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_CreateTest);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_StartTest);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_StartTest);
		return -1;
	}

    long nRet = m_pXSmartTestClient->BeginTest(m_strDeviceSN);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_StartTest);
	}
	else
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_StartTest);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_StopTest);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_StopTest);
		return -1;
	}

    long nRet = m_pXSmartTestClient->StopTest(m_strDeviceSN);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_StopTest);
	}
	else
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_StopTest);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CloseTest);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CloseTest);
		return -1;
	}

    long nRet = m_pXSmartTestClient->CloseTest(m_strDeviceSN);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CloseTest);
	}
	else
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_CloseTest);
	}

	//shaolei 20211022
	//延迟一秒钟后关闭SmartTest，否则SmartTest会在关闭测试过程中析构主框架，会导致崩溃
	CTickCount32 oTick;
	oTick.DoEvents(1000);

	//关闭自动测试
	ExitSmartTestCom();

	return nRet;
}
/*
<ats-cmd name="" id="TestItem" testor="" >
<paras name="" id="">	
<data id="ItemPath" value="" />  【项目的绝对路径】
<data id="ItemIndex" value="" />  【项目的编号】
</paras>
</ats -cmd>
*/
long CSttSmartTestCom::Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_TestItem);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_TestItem);
		return -1;
	}

	CString strItemPath;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);

    long nRet = m_pXSmartTestClient->TestPoint(m_strDeviceSN, strItemPath);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_TestItem);
	}
	else
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_TestItem);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_TestFrom);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_TestFrom);
		return -1;
	}

	CString strDeviceID, strItemPath;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);

	long nRet = m_pXSmartTestClient->TestBelow(m_strDeviceSN, strItemPath);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_TestFrom);
	}
	else
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_TestFrom);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_TestAllFailedItems);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_TestAllFailedItems);
		return -1;
	}

	CString strDeviceID;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);

	long nRet = m_pXSmartTestClient->TestAllInlegibleItems(m_strDeviceSN);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_TestAllFailedItems);
	}
	else
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_TestAllFailedItems);
	}

	return nRet;
}

long CSttSmartTestCom::Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_GetItemReport);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_GetItemReport);
		return -1;
	}

	//暂不实现
    return 0;
}

long CSttSmartTestCom::Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_GetReportFile);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_GetReportFile);
		return -1;
	}

	//暂不实现
    return 0;
}

long CSttSmartTestCom::Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_GetSystemState);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_GetSystemState);
		return -1;
	}

	//暂不实现
    return 0;
}

/*
<ats-cmd name="FinishInputData" id="" testor="" >
    <paras name="" id="">
        <data name="温度" id="Temperature" data-type="float" unit="" value="0" ……/>
        <data name="湿度" id="Humidity" data-type="float" unit="" value="0" ……/>
        <data name="气压" id="AirPressure" data-type="float" unit="" value="0" ……/>
    </paras>
</ats -cmd>
 */
 long CSttSmartTestCom::Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_FinishInputData);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_FinishInputData);
		return -1;
	}

    CSttParas *pAtsParas = pAtsCmd->GetSttParas();
	CString strDeviceID, strReport;

	pAtsParas->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceID);
	pAtsParas->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strReport);

	long nRet = m_pXSmartTestClient->FinishInputData(strDeviceID, strReport);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_FinishInputData);
	}
	else
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_FinishInputData);
	}

	return nRet;
 }

 /*   这个是老版本的报文格式
 <ats-cmd name="" id="SetItemState" testor="" >
     <paras name="" id="">
         <data id="ItemPath" value="" />  【项目的绝对路径】
         <data id="ItemIndex" value="" />  【项目的编号】
         <data id="Select" value="1" />
         <data id="Enable" value="1" />
         <data id="Show" value="1" />
     </paras>
 </ats -cmd>e
 */

 /*   这个是新版本的报文格式，一个报文可以设置多个测试项   20220606
 <ats-cmd name="" id=" SetItemState" testor="">
	 <paras>
		 <data name="" id="DeviceSN" data-type="" value="装置SN"/>
		 <group>
			 <data name="" id="ItemPath" data-type="" value="Device$ManulTest"/>
			 <data name="" id="Select" data-type="" value="1"/>
			 <data name="" id="Show" data-type="" value="1"/>
		 </group>
		 <group>
			 <data name="" id="ItemPath" data-type="" value="Device$AutoTest"/>
			 <data name="" id="Select" data-type="" value="1"/>
			 <data name="" id="Show" data-type="" value="1"/>
		 </group>
		 <group>
			 <data name="" id="ItemPath" data-type="" value="Device$AdditionalTest"/>
			 <data name="" id="Select" data-type="" value="1"/>
			 <data name="" id="Show" data-type="" value="1"/>
		 </group>
		 ……
	 </paras>
 </ats-cmd>
 */
 long CSttSmartTestCom::Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
/*   这段代码对应老版本的报文格式
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_SetItemState);

	 if (m_pXSmartTestClient == NULL)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_SetItemState);
		 return -1;
	 }

	 long nSelect, nEnable, nShow;
	 nShow = nSelect = nEnable = 1;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_Select, nSelect);
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_Show, nShow);
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_Enable, nEnable);

	 CString strItemPath;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);
	 long nState = TEST_STATE_ELIGIBLE;  //合格

    long nRet = m_pXSmartTestClient->SetItemStateEx(strItemPath, nSelect, nEnable, nShow, nState);

	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_SetItemState);
	}
	else
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_SetItemState);
	}
*/

	//对应新的报文格式，一个MQTT报文，可以设置多个测试项目的状态；
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_SetItemState);

	if (m_pXSmartTestClient == NULL)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_SetItemState);
		return -1;
	}

	long nSelect, nEnable, nShow;
	nShow = nSelect = nEnable = 1;
	CString strItemPath;
	CSttParas *pParas = pAtsCmd->GetSttParas();
	POS pos = pParas->GetHeadPosition();
	long nRet = SMART_TEST_COM_EXEC_SUCC;
	long nState = TEST_STATE_ELIGIBLE;  //合格

	while (pos != NULL)
	{
		CDataGroup *pGroup = (CDataGroup *)pParas->GetNext(pos);
		pGroup->GetDataValue(STT_CMD_PARA_Select, nSelect);
		pGroup->GetDataValue(STT_CMD_PARA_Show, nShow);
		pGroup->GetDataValue(STT_CMD_PARA_ItemPath, strItemPath);

		long nRetSingle = m_pXSmartTestClient->SetItemStateEx(strItemPath, nSelect, nEnable, nShow, nState);

		if (nRetSingle != SMART_TEST_COM_EXEC_SUCC)
		{
			nRet = nRetSingle;
		}
	}
	
	if (nRet != SMART_TEST_COM_EXEC_SUCC)
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_SetItemState);
	}
	else
	{
		ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_SetItemState);
	}

	return nRet;
 }

 long CSttSmartTestCom::Ats_InputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_InputData);

	return 0;
 }
 
 long CSttSmartTestCom::Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_ExportReport);

	 if (m_pXSmartTestClient == NULL)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_ExportReport);
		 return -1;
	 }

	 CString strDeviceID;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);

	 long nRet = m_pXSmartTestClient->ExportRpt(strDeviceID);

	 if (nRet != SMART_TEST_COM_EXEC_SUCC)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_ExportReport);
	 }
	 else
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_ExportReport);
	 }

	 return nRet;
 }
 
 long CSttSmartTestCom::Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_SetItemsReport);

	 if (m_pXSmartTestClient == NULL)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_SetItemsReport);
		 return -1;
	 }

	 CString strItemPath, strDeviceID;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);

	 CSttParas *pParas = pAtsCmd->GetSttParas();
	 CSttItems *pItems = (CSttItems *)pParas->FindByClassID(STTGBXMLCLASSID_CSTTITEMS);
	 CString  strReports;
	 
	 if (pItems != NULL)
	 {
	 pItems->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strReports);
	 }

	 long nRet = m_pXSmartTestClient->SetReports(strDeviceID, strItemPath, strReports);

	 if (nRet != SMART_TEST_COM_EXEC_SUCC)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_SetItemsReport);
	 }
	 else
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_SetItemsReport);
	 }

	 return nRet;
 }
 
 long CSttSmartTestCom::Ats_QueryItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_QueryItems);

	 if (m_pXSmartTestClient == NULL)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_QueryItems);
		 return -1;
	 }

	 CString strItemPath, strDeviceID;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);

	 pParasReturn->FreeTextParasBuf();
	  pParasReturn->m_nLenTextParas = m_pXSmartTestClient->QueryItems(strDeviceID, strItemPath, &pParasReturn->m_pszTextParas);

	 if ( pParasReturn->m_nLenTextParas == 0)
	 {
		 pParasReturn->m_strTextParasID.Empty();
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_QueryItems);
		 return -1;
	 }
	 else
	 {
		 //2021-8-9  lijunqing
// 		 BSTR bstrText = strItems.AllocSysString();
// 		 CSttItems *pItems = new CSttItems();
// 		 pItems->SetXml(bstrText,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
// 		 SysFreeString(bstrText);
// 		 pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
// 		 pParasReturn->AddNewData(STT_CMD_PARA_ItemPath, strItemPath);
// 
// 		 pParasReturn->AddNewChild(pItems);
		 //此处还需要添加data-types节点
		 pParasReturn->m_strTextParasID = _T("QueryItems");

		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_QueryItems);
	 }

	 return 0;
 }

 long CSttSmartTestCom::Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_ConfigTest);

	 if (m_pXSmartTestClient == NULL)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_ConfigTest);
		 return -1;
	 }

	 CString strDeviceID;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);

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

	 long nRet = m_pXSmartTestClient->ConfigTest(strDeviceID, strTestApps);

	 if ( nRet < 0)
	 {
		 pParasReturn->m_strTextParasID.Empty();
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_ConfigTest);
		 return -1;
	 }
	 else
	 {

		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_ConfigTest);
	 }

	 return 0;
 }

 long CSttSmartTestCom::Ats_QueryTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_QueryTestPara);

	 if (m_pXSmartTestClient == NULL)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_QueryTestPara);
		 return -1;
	 }

	 CString strDeviceSN, strTestParas;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	 long nRet = m_pXSmartTestClient->QueryTestParas(strDeviceSN, strTestParas);

	 if ( nRet < 0)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_QueryTestPara);
		 return -1;
	 }
	 else
	 {
		 BSTR bstrText = strTestParas.AllocSysString();
  		 CDvmDataset oDataset;
  		 oDataset.SetXml(bstrText,CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
  		 SysFreeString(bstrText);
  		 CDataGroup *pParas = new CDataGroup();
  		 pParas->m_strID.Format(_T("Paras"));
  		 pParasReturn->AddNewChild(pParas);
  		 pParas->AppendCloneEx(oDataset, TRUE);
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_QueryTestPara);

// 		 CSttSysState oSysStateEvent;
// 		 CSttParas *pParasEvent = oSysStateEvent.GetSttParas();
// 		 pParasEvent->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
// 
// 		 BSTR bstrText = strTestParas.AllocSysString();
// 		 CDvmDataset oDataset;
// 		 oDataset.SetXml(bstrText,CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
// 		 SysFreeString(bstrText);
// 		 CDataGroup *pParas = new CDataGroup();
// 		 pParas->m_strID.Format(_T("Paras"));
// 		 pParasEvent->AddNewChild(pParas);
// 		 pParas->AppendCloneEx(oDataset, TRUE);
// 		 ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysStateEvent, STT_CMD_TYPE_ATS_QueryTestParas);
	 }

	return 0;
 }

 long CSttSmartTestCom::Ats_SetTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();
	 CSttSysState oSysState;
	 CSttParas *pParasReturn = oSysState.GetSttParas();
	 pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);

	 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_SetTestPara);

	 if (m_pXSmartTestClient == NULL)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_SetTestPara);
		 return -1;
	 }

	 CString strDeviceSN, strTestParas;
	 pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	 CSttParas *pSttParas = pAtsCmd->GetSttParas();
	 CDataGroup *pParaGroup = (CDataGroup *)pSttParas->FindByID(_T("Paras"));
	 //转换为CDvmDataset，发送给自动测试。
	 CDvmDataset oDataset;
	 oDataset.AppendCloneEx(*pParaGroup, TRUE);
	 oDataset.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strTestParas);
	 long nRet = m_pXSmartTestClient->SetTestParas(strDeviceSN, strTestParas);

	 if ( nRet < 0)
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_SetTestPara);
		 return -1;
	 }
	 else
	 {
		 ReturnSysState_REPLY(pSttProtocol, (CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_SetTestPara);
	 }

	 return 0;
 }

 //解析外部系统上报的word报告和原始记录文件，并下载文件
 long CSttSmartTestCom::Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase)
 {
	 //关于数据ID，给英锐祺的定义和我们自己定义的不一致，一个是下划线，一个是中划线。先临时处理
	 CString strDocFile, strDocFile_s, strDocFileEx, strDocFileEx_s;
	 pSttCmdBase->GetParasDataValueByID(_T("doc_file"), strDocFile);
	 pSttCmdBase->GetParasDataValueByID(_T("doc_file_s"), strDocFile_s);
	 pSttCmdBase->GetParasDataValueByID(_T("doc_ex_file"), strDocFileEx);
	 pSttCmdBase->GetParasDataValueByID(_T("doc_ex_file_s"), strDocFileEx_s);

	 m_strDocFile.Empty();
	 m_strDocFileEx.Empty();
	 CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Process UploadReportFinish........"));
	 CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("----doc_file=[%s]"), strDocFile);
	 CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("----doc_file_s=[%s]"), strDocFile_s);
	 CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("----doc_ex_file=[%s]"), strDocFileEx);
	 CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("----doc_ex_file_s=[%s]"), strDocFileEx_s);

	 CString strHttpUrlHead,strUrl; 
	 CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	 CString strRootPath;
	 CString strFileDownLoad;
	 BOOL bRet1 = FALSE;
	 BOOL bRet2 = FALSE;
	 strRootPath = _P_GetInstallPath();
	 strRootPath += _T("e-Report\\WorkSpace\\");

	 if (strDocFile_s.GetLength() > 5)
	 {
		 //下载外部系统报告文件，并记录
		 strFileDownLoad = strRootPath + strDocFile;
		 m_strDocFile = strFileDownLoad;
		 strUrl = strHttpUrlHead + strDocFile_s;

		// 此处不考虑存在就不下载
		 //调试时，若文件存在，则不下载
	  	 if (IsFileExist(strFileDownLoad))
	  	 {
	  		 bRet1 = TRUE;
	  	 }
	  	 else
		 {
			 bRet1 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
		 }
	 }

	 if (strDocFileEx_s.GetLength() > 5)
	 {
		 //下载外部系统原始记录文件，并记录
		 strFileDownLoad = strRootPath + strDocFileEx;
		 m_strDocFileEx = strFileDownLoad;
		 strUrl = strHttpUrlHead + strDocFileEx_s;

		 //此处不考虑存在就不下载
		 //调试时，若文件存在，则不下载
	  	 if (IsFileExist(strFileDownLoad))
	  	 {
	  		 bRet1 = TRUE;
	  	 }
	  	 else
		 {
			 bRet2 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
		 }
	 }

	 return bRet1&&bRet2;
 }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long CSttSmartTestCom::OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState, long nSelect)
{
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	//pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
	pParasReturn->AddNewData(STT_CMD_PARA_ReportIndex, nReportIndex);
	CString strItemPath;
	strItemPath.Format(_T("%s$%s"), strDeviceID, strItemID);
	pParasReturn->AddNewData(STT_CMD_PARA_ItemPath, strItemPath);
	pParasReturn->AddNewData(STT_CMD_PARA_ItemIndex, nItemIndex);

	long nState = GB_GetTestStateByIDEx(strState);
	pParasReturn->AddNewData(STT_CMD_PARA_State, nState);

	ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_OnItemStateChanged);

	//2021-8-6  lijunqing 上送报告事件
	if (strState == TEST_STATE_DESC_ELIGIBLE || strState == TEST_STATE_DESC_INLEGIBLE
		|| strState == TEST_STATE_DESC_ELIGIBLEEX)
	{
		pParasReturn->FreeTextParasBuf();
		pParasReturn->m_nLenTextParas = m_pXSmartTestClient->GetReports(strDeviceID, strItemID, &pParasReturn->m_pszTextParas);
		pParasReturn->m_strTextParasID = SYS_STATE_RETTYPE_REPORT;
		ReturnSysState_REPORT(m_pSttProtocol, NULL, &oSysState);
	}

     return 0;
}

//全部项目测试结束事件，注意与电气量项目结束事件的区别
long CSttSmartTestCom::OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex)
{
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pParasReturn->AddNewData(STT_CMD_PARA_ReportIndex, nReportIndex);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);

	ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_OnTestFinished);
     return 0;
}

long CSttSmartTestCom::OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex)
{
	//物联协议文档中缺少该事件的定义
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pParasReturn->AddNewData(STT_CMD_PARA_ReportIndex, nReportIndex);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);

	ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_OnTestStoped);
	return 0;
}

long CSttSmartTestCom::OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex)
{
	if (strEventID != SYS_STATE_XEVENT_EVENTID_ExportFinish)
	{
		return 0;
	}

	try
	{
		CSttSysState oSysState;
		CSttParas *pParasReturn = oSysState.GetSttParas();
		pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
		//pParasReturn->AddNewData(STT_CMD_PARA_ReportIndex, nReportIndex);
		pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
		pParasReturn->AddNewData(STT_CMD_PARA_EventID, strEventID);
		pParasReturn->AddNewData(STT_CMD_PARA_CurrDevice, nDeviceIndex+1);
		long nTotalDevices = 1;

		if (m_pDevices != NULL)
		{
			nTotalDevices = m_pDevices->GetCount();
		}

		pParasReturn->AddNewData(STT_CMD_PARA_TotalDevices, nTotalDevices);

		{
			//导出报告结束，需要获取所有报告文件，并上传
			//对于word格式的报告文件和原始记录文件，需要和外部系统的报告进行合并后，再上传
			CDataGroup *pFiles = GetReportFiles(strDeviceID);

			CString strUrl, strHttpUrlHead;
			CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
			strUrl = strHttpUrlHead + _T("/file/upload");
			std::string strLastRpt, strFileNameRpt, strUrlRpt;
			strLastRpt = "";

			//上传gbrpt报告文件
			CString strValue;
			pFiles->GetDataValue(XPARA_ID_GBRPTFILE, strValue);
			CString strFile_s, strFileName;

			CXFileHttpClient::UploadFile(strUrl, strValue);
			CXFileHttpClient::ParseURLReport(strLastRpt, strFileNameRpt, strUrlRpt);
			strFile_s = strFileNameRpt.c_str();
			strFileName = GetFileNameFromFilePath(strValue);

			pParasReturn->AddNewData(XPARA_ID_GBRPTFILE, strFileName);
			pParasReturn->AddNewData(XPARA_ID_GBRPTFILE_S, strFile_s);

			//上传xml报告文件
			pFiles->GetDataValue(XPARA_ID_XMLRPTFILE, strValue);

			CXFileHttpClient::UploadFile(strUrl, strValue);
			strLastRpt = "";
			CXFileHttpClient::ParseURLReport(strLastRpt, strFileNameRpt, strUrlRpt);
			strFile_s = strFileNameRpt.c_str();
			strFileName = GetFileNameFromFilePath(strValue);

			pParasReturn->AddNewData(XPARA_ID_XMLRPTFILE_S, strFile_s);
			pParasReturn->AddNewData(XPARA_ID_XMLRPTFILE, strFileName);

			//上传word报告文件，strValue带绝对路径
			pFiles->GetDataValue(XPARA_ID_DOCFILE, strValue);
			//拼接外部系统的测试报告，写入数据库oDeviceHisTest的为拼接后的总报告

			strValue = CombineWordFile(strValue, m_strDocFile);

			CXFileHttpClient::UploadFile(strUrl, strValue);
			strLastRpt = "";
			CXFileHttpClient::ParseURLReport(strLastRpt, strFileNameRpt, strUrlRpt);
			strFile_s = strFileNameRpt.c_str();
			strFileName = GetFileNameFromFilePath(strValue);

			pParasReturn->AddNewData(XPARA_ID_DOCRPTFILE_S, strFile_s);
			pParasReturn->AddNewData(XPARA_ID_DOCFILE, strFileName);

			//////////////////////////////////////////////////////////////////////////
			//上传扩展word报告文件，strValue带绝对路径
			pFiles->GetDataValue(XPARA_ID_DOCRPTFILE_EX, strValue);

			if (::IsFileExist(strValue))
			{

				CXFileHttpClient::UploadFile(strUrl, strValue);
				strLastRpt = "";
				CXFileHttpClient::ParseURLReport(strLastRpt, strFileNameRpt, strUrlRpt);
				strFile_s = strFileNameRpt.c_str();

				strFileName = GetFileNameFromFilePath(strValue);
				pParasReturn->AddNewData(XPARA_ID_DOCRPTFILE_EX_S, strFile_s);
				pParasReturn->AddNewData(XPARA_ID_DOCRPTFILE_EX, strFileName);

				//转成PDF文档，此处上传PDF文件，返回值即为PDF的绝对路径

				//此段为调试代码
// 				if (m_strDocFileEx.GetLength() > 5)
// 				{
// 					strValue = CombineWordFile(strValue, m_strDocFileEx, TRUE);
// 					CXFileHttpClient::UploadFile(strUrl, strValue);
// 					strLastRpt = "";
// 					CXFileHttpClient::ParseURLReport(strLastRpt, strFileNameRpt, strUrlRpt);
// 					strFile_s = strFileNameRpt.c_str();
// 					strFileName = GetFileNameFromFilePath(strValue);
// 					pParasReturn->AddNewData(XPARA_ID_PDFFILE_S, strFile_s);
// 					pParasReturn->AddNewData(XPARA_ID_PDFFILE, strFileName);
// 				}
			}
		}

		ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_ExportReport);

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ExportReport finish [%s]"), m_strBenchSN);
	}
	catch (...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ExportReport failed [%s]"), m_strBenchSN);
		
	}

	

    return 0;
}

long CSttSmartTestCom::OnTestAppEvent(const CString& strDeviceID, const CString& strEvent)
{
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
	pParasReturn->AddNewData(STT_CMD_PARA_EventID, strEvent);

	ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_OnTestAppEvent);
     return 0;
}

long CSttSmartTestCom::OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent)
{
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
	pParasReturn->AddNewData(STT_CMD_PARA_EventID, strEvent);

	ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_OnEngineEvent);
     return 0;
}

//多个被测设备同时测试时，每个设备返回一次TestCreated事件
long CSttSmartTestCom::OnTestCreated(const CString& strDeviceID)
{
	if (m_pXSmartTestClient == NULL)
	{
		return -1;
	}

	//2021-7-25  lijunqing  因为返回的文本可能比较大，通过返回CString的方式会多出一次构造析构
	//效率相对比较低，所以改为传址返回
	//CString strGuideBook;
	//m_pXSmartTestClient->GetGuideBook(strDeviceID, strGuideBook);

	//2021-8-4  lijunqing 此对象只是临时对象，不用作为全局变量
	//CSttGuideBook *pGuideBook = new CSttGuideBook();

// 	BSTR bstrText = strGuideBook.AllocSysString();
// 	pGuideBook->SetXml(bstrText,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
// 	SysFreeString(bstrText);

	//回复OnTestCreated事件
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
	long nTotalTimeLong = 0;
	pParasReturn->AddNewData(STT_CMD_PARA_TestTotalTimeLong, nTotalTimeLong);

	long nTotalItemsCount = 0;
	m_pXSmartTestClient->GetTotalItemsCount(strDeviceID, nTotalItemsCount);
	pParasReturn->AddNewData(STT_CMD_PARA_TotalItems, nTotalItemsCount);
	//pParasReturn->AddNewChild(pGuideBook);
	pParasReturn->m_strTextParasID = _T("GuideBook");
	
	pParasReturn->FreeTextParasBuf();
	pParasReturn->m_nLenTextParas = m_pXSmartTestClient->GetGuideBook(strDeviceID, &pParasReturn->m_pszTextParas);

	ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_OnTestCreated);

     return 0;
}

long CSttSmartTestCom::OnOpenGbrptFileFailed(const CString& strDeviceID)
{
	//物联协议文档中缺少该事件的定义
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);

	ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_OnOpenGbrptFileFailed);
	return 0;
}

/*
<sys-state name="" id="TestProcess" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="BenchSN" data-type="" value="测试台SN/"/>
		<data id="TotalItems" data-type="long" value="100" unit=""/>
		<data id="CurrItem" data-type="long" value="30" unit=""/>
		<data id="TotalTime" data-type="long" value="6000" unit="s"/>
		<data id="RemainTime" data-type="long" value="3000" unit="s"/>
		<data name="" id="DeviceState" data-type="" value="合格|不合格"/>
	</paras>
</sys-state>
*/
long CSttSmartTestCom::OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState)
{
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
	pParasReturn->AddNewData(STT_CMD_PARA_TotalItems, nTotalItems);
	pParasReturn->AddNewData(STT_CMD_PARA_CurrItem, nCurrItem);
	pParasReturn->AddNewData(STT_CMD_PARA_TotalTime, nTotalTime);
	pParasReturn->AddNewData(STT_CMD_PARA_RemainTime, nRemainTime);
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceState, strDeviceState);

	ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_OnTestProcess);

	return 0;
}

long CSttSmartTestCom::OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex)
{
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pParasReturn->AddNewData(STT_CMD_PARA_ReportIndex, nReportIndex);
	pParasReturn->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);

	ReturnSysState_EVENT(m_pSttProtocol, NULL, &oSysState, SYS_STATE_EVENT_OnTestStarted);
	return 0;
}

long CSttSmartTestCom::ReturnSysState_REPLY(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID)
{
	if (pSttProtocol == NULL)
	{
		return 0;
	}

	return pSttProtocol->ReturnSysState_REPLY(pCmmOptrInterface, nCmdExecStatus, pRetData, pszEventID, STT_CMD_SYSSTATE_ATS);
}

long CSttSmartTestCom::ReturnSysState_EVENT(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID)
{
	if (pSttProtocol == NULL)
	{
		return 0;
	}

	return pSttProtocol->ReturnSysState_EVENT(pCmmOptrInterface, pRetData, pszEventID, STT_CMD_SYSSTATE_ATS);
}

//2021-8-6  lijunqing
long CSttSmartTestCom::ReturnSysState_REPORT(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData)
{
	if (pSttProtocol == NULL)
	{
		return 0;
	}

	return pSttProtocol->ReturnSysState_REPORT(pCmmOptrInterface, pRetData, STT_CMD_SYSSTATE_ATS);
}


CDataGroup* CSttSmartTestCom::GetReportFiles(const CString &strDeviceID)
{
	CString strFiles;
	m_pXSmartTestClient->GetReportFiles(strDeviceID, strFiles);
	CDataGroup *pFiles = new CDataGroup();
	BSTR bstrText = strFiles.AllocSysString();
	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	pFiles->SetXml(bstrText,CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	SysFreeString(bstrText);

	return pFiles;
}

MSWord::_Application CSttSmartTestCom::GetWordApp(BOOL bShow)
{
	if (m_WordApp != NULL)
	{
		return m_WordApp;
	}

	try
	{
		if (!m_WordApp.CreateDispatch(_T("Word.Application")))
		{
			AfxMessageBox(_T("没有安装Word"));
			return NULL;
		}

		m_WordApp.SetVisible(bShow);  //This shows the application.
	}
	catch (...)
	{
		TRACE("catch error-----");
	}

	return m_WordApp;
}

BOOL CSttSmartTestCom::wordOptr_ActiveWindow(MSWord::_Application	&oWordApp, const CString &strTitle)
{
	BOOL bTrue = FALSE;

	try
	{
		MSWord::Windows oWindows = oWordApp.GetWindows();
		COleVariant oIndex;

		long nIndex = 1;
		long nCount = oWindows.GetCount();

		for (nIndex=1; nIndex<=nCount; nIndex++)
		{
			oIndex = nIndex;
			MSWord::Window oWindow = oWindows.Item(&oIndex);
			CString strCaption = oWindow.GetCaption();

			if (strCaption.Find(strTitle) >= 0)
			{
				oWindow.Activate();
				bTrue = TRUE;
				break;
			}
		}
	}
	catch (...)
	{

	}

	return bTrue;
}

void CSttSmartTestCom::word_close_doc(MSWord::_Document &oDoc, MSWord::_Document &oDoc2)
{
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (oDoc != NULL)
		{
			oDoc.Close(covFalse,covOptional,covOptional);
		}
	}
	catch (...)
	{

	}
	try
	{
		if (oDoc2 != NULL)
		{
			oDoc2.Close(covFalse,covOptional,covOptional);
		}
	}
	catch (...)
	{

	}

	m_WordApp.Quit(covFalse, covOptional, covOptional);
	m_WordApp = NULL;

	oDoc = NULL;
	oDoc2 = NULL;
}

BOOL CSttSmartTestCom::word_insert_doc_bkmk(MSWord::_Document &oDoc, MSWord::_Document &oDoc2, const CString &strFile1, const CString &strFile2)
{
	COleVariant vDocFile(strFile1);	
	COleVariant vDocFile2(strFile2);	
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)MSWord::wdStory);
	COleVariant vUnit2((long)MSWord::wdCharacter);
	COleVariant vCount((long)1);
	COleVariant varstrNull(_T(""));

	//协议一致性报告插入的书签
	static CString bkmk_POS_IOT_REPORT_FILE_INSERT_AT = _T("POS_IOT_REPORT_FILE_INSERT_AT");

	try
	{
		COleVariant vIndex(bkmk_POS_IOT_REPORT_FILE_INSERT_AT);
		MSWord::Bookmarks oBkmks = oDoc.GetBookmarks();

		if (!oBkmks.Exists(bkmk_POS_IOT_REPORT_FILE_INSERT_AT))
		{
			return FALSE;
		}

		MSWord::Bookmark  oBkmk = oBkmks.Item(vIndex);

		oDoc2.Activate();
		oDoc2.Select();
		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		wordSelection.WholeStory();
		wordSelection.Copy();
		
		oBkmk.Select();
		wordSelection =m_WordApp.GetSelection();
		wordSelection.Paste();	

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("插入报告成功: file1= [%s] file2= [%s]"), strFile1, strFile2);
		return TRUE;
	}
	catch (...)
	{
		word_close_doc(oDoc, oDoc2);
		return FALSE;
	}
}

BOOL CSttSmartTestCom::word_insert_doc_tail(MSWord::_Document &oDoc, MSWord::_Document &oDoc2, const CString &strFile1, const CString &strFile2)
{
	COleVariant vDocFile(strFile1);	
	COleVariant vDocFile2(strFile2);	
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)MSWord::wdStory);
	COleVariant vUnit2((long)MSWord::wdCharacter);
	COleVariant vCount((long)1);
	COleVariant varstrNull(_T(""));

	try
	{
		CString strTitle;
		strTitle = GetFileTitleFromFilePath(strFile2);

		if (!wordOptr_ActiveWindow(m_WordApp, strTitle))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("插入%s失败"), strFile2);
			word_close_doc(oDoc, oDoc2);
			return FALSE;
		}

		MSWord::Selection wordSelection = m_WordApp.GetSelection();
		wordSelection.WholeStory();
		wordSelection.Copy();
		strTitle = GetFileTitleFromFilePath(strFile1);

		if (!wordOptr_ActiveWindow(m_WordApp, strTitle))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("插入%s失败"), strFile1);
			word_close_doc(oDoc, oDoc2);
			return FALSE;
		}	

		wordSelection =m_WordApp.GetSelection();
		wordSelection.EndKey(&vUnit, &covOptional);
		wordSelection.Paste();	
		wordSelection.Delete(&vUnit2, &vCount);

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并报告成功: file1= [%s] file2= [%s]"), strFile1, strFile2);
		return TRUE;
	}
	catch (...)
	{
		word_close_doc(oDoc, oDoc2);
		return FALSE;
	}
}

//形参均为全路径。将文件2拼接到文件1的后面，并返回新文档的绝对路径；
CString CSttSmartTestCom::CombineWordFile(const CString &strFile1, const CString &strFile2, BOOL bToPdf)
{
	if (strFile1.IsEmpty() || strFile2.IsEmpty())
	{
		return strFile1;
	}

	GetWordApp(FALSE);
	MSWord::Documents docs = m_WordApp.GetDocuments();

	COleVariant vDocFile(strFile1);	
	COleVariant vDocFile2(strFile2);	
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vUnit((long)MSWord::wdStory);
	COleVariant vUnit2((long)MSWord::wdCharacter);
	COleVariant vCount((long)1);
	COleVariant varstrNull(_T(""));
	MSWord::_Document oDoc, oDoc2;

	try
	{
		//打开报告文件
		oDoc = docs.Open(&vDocFile,covOptional,covFalse,covTrue,covOptional,covOptional,
			covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
	}
	catch (...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Open [%s] failed"), strFile1);
		word_close_doc(oDoc, oDoc2);
		return strFile1;
	}

	try
	{
		//打开原始记录报告文件
		oDoc2 = docs.Open(&vDocFile2,covOptional,covFalse,covTrue,covOptional,covOptional,
			covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
	}
	catch (...)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Open [%s] failed"), strFile2);
		word_close_doc(oDoc, oDoc2);
		return strFile1;
	}

	if (oDoc == NULL || oDoc2 == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error: file1= [%s] file2= [%s] failed"), strFile1, strFile2);

		word_close_doc(oDoc, oDoc2);
		return strFile1;
	}

	try
	{
		if (!word_insert_doc_bkmk(oDoc, oDoc2, strFile1, strFile2))
		{
			if (!word_insert_doc_tail(oDoc, oDoc2, strFile1, strFile2))
			{
				return strFile1;
			}
		}
	}
	catch (...)
	{
		word_close_doc(oDoc, oDoc2);
		return strFile1;
	}

	CComVariant FileFormat1(0);

	try
	{
		oDoc.Save();
// 		oDoc.SaveAs(&FileName1,
// 			&FileFormat1,
// 			&covFalse,
// 			varstrNull,
// 			&covTrue,		
// 			varstrNull,
// 			&covFalse,
// 			&covFalse,
// 			&covFalse,
// 			&covFalse,
// 			&covFalse
// 			/*&vOpt,&vOpt,&vOpt,&vOpt,&vOpt*/);
	}
	catch (...)
	{

	}

	//转PDF，需要返回PDF的文件名
	CString strPdfFile;
	if (bToPdf)
	{
		strPdfFile = ChangeFilePostfix(strFile1,_T("pdf"));
		CComVariant FileName(strPdfFile);
		CComVariant FileFormat(17);//pdf格式

		try
		{
			oDoc.SaveAs(&FileName,
				&FileFormat,
				&covFalse,
				varstrNull,
				&covTrue,		
				varstrNull,
				&covFalse,
				&covFalse,
				&covFalse,
				&covFalse,
				&covFalse
				/*&vOpt,&vOpt,&vOpt,&vOpt,&vOpt*/);

			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出PDF成功: pdf file= [%s]failed"), FileName);

		}
		catch (...)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出PDF失败: pdf file= [%s]failed"), FileName);
			strPdfFile = _T("");	
		}
	}

	word_close_doc(oDoc, oDoc2);

	if (bToPdf)
	{
		return strPdfFile;
	}

	return strFile1;
}

// BOOL CSttSmartTestCom::UploadAllRptFiles(CDataGroup* pFiles)
// {
// 	POS pos = pFiles->GetHeadPosition();
// 	CString strFileName;
// 	CDvmData *pFile = NULL;
// 	CString strUrl, strHttpUrlHead;
// 	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
// 	strUrl = strHttpUrlHead + _T("//file//upload");
// 	BOOL bRetrun = TRUE;
// 
// 	while (pos != NULL)
// 	{
// 		pFile = (CDvmData *)pFiles->GetNext(pos);
// 
// 		if (!CXFileHttpClient::UploadFile(strUrl, pFile->m_strValue))
// 		{
// 			bRetrun = FALSE;
// 		}
// 
// // 		CXFileHttpClient::GetLastReport()
// 	}
// 
// 	return bRetrun;
// }

//D:/Program Files/EPOTO/e-Report/Workspace/1111.doc
//http://192.168.1.253:8080/file/upload


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
<ats-cmd name="" id="CreateTest" testor="">
	<paras>
		<data name="测试台标识" id="TestID" value="测试台SN/"/>
		<data name="测试模板" id="gbxml-file" value="SZNR-TTU.gbexe"/>
		<data name="测试模板" id="gbxml-file_s" value="……………"/>    //e-Report/Template
		<data name="报告模板" id="doc-file_s" value="……………"/>    //e-Report/Template
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
/*
#define XPARA_ID_GBXMLFILE_S  _T("gbxml-file_s")
#define XPARA_ID_DVMFILE_S    _T("dvm-file_s")
#define XPARA_ID_PPXMLFILE_S   _T("ppxml-file_s")
#define XPARA_ID_DOCRPTFILE_S  _T("doc-file_s")
*/

BOOL CSttSmartTestCom::DownLoadAllFiles(CSttAtsCmd *pAtsCmd)
{
	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	CString strFile, strFile_s, strRootPath;
	CSttParas *pParas = (CSttParas *)pAtsCmd->GetSttParas();
	CString strFileDownLoad;
	BOOL bRet1 = TRUE;
	BOOL bRet2 = TRUE;
	strRootPath = _P_GetInstallPath();
	strRootPath += _T("e-Report\\Template\\");

	//下载测试模板文件
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE_S, strFile_s);
	
	if (strFile_s.IsEmpty())
	{
		//测试模板文件是必须项，若不存在，直接返回下载失败
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("测试模板文件【%s】为空，下载失败！"), strFile);
		bRet1 = FALSE;
	}
	else
	{
		strFileDownLoad = strRootPath + strFile;
		strUrl = strHttpUrlHead + strFile_s;

		if (IsFileExist(strFileDownLoad))
		{
			bRet1 = TRUE;
		}
		else
		{
		bRet1 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
	}
	}

	//下载报告模板文件
	strFile_s.Empty();
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DOCRPTFILE_S, strFile_s);
	strFile = ChangeFilePostfix(strFile, _T("doc"));

	if (strFile_s.IsEmpty())
	{
		//报告模板文件是必须项，若不存在，直接返回下载失败
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("报告模板文件【%s】为空，下载失败！"), strFile);
		bRet2 = FALSE;
	}
	else
	{
		strFileDownLoad = strRootPath + strFile;
		strUrl = strHttpUrlHead + strFile_s;

		if (IsFileExist(strFileDownLoad))
		{
			bRet2 = TRUE;
		}
		else
		{
		bRet2 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
		}
	}	

	//下载扩展报告模板文件
	strFile_s.Empty();
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DOCRPTFILE_EX_S, strFile_s);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DOCRPTFILE_EX, strFile);
	BOOL bRet3 = TRUE;

	if (!strFile_s.IsEmpty())
	{
		strFileDownLoad = strRootPath + strFile;
		strUrl = strHttpUrlHead + strFile_s;

		if (!IsFileExist(strFileDownLoad))
		{
			bRet3 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
		}
	}	

	//下载测试仪配置文件（固定后缀为iecfg），根目录为e-Report\Template，非必须项
	BOOL bRet4 = TRUE;
	strFile_s.Empty();
	pAtsCmd->GetParasDataValueByID(XPARA_ID_IECFGFILE, strFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_IECFGFILE_S, strFile_s);
	
	if (!strFile_s.IsEmpty())
	{
		strFileDownLoad = strRootPath + strFile;
		strUrl = strHttpUrlHead + strFile_s;

		if (IsFileExist(strFileDownLoad))
		{
			bRet4 = TRUE;
		}
		else
		{
			bRet4 = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
	}
	}

	//下载被测装置相关的文件
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
	BOOL bRet5 = TRUE;

	if (pDevices != NULL)
	{
		bRet5 = DownLoadFiles_Devices(pDevices);
	}

// 	CDataGroup *pApps = (CDataGroup *)pParas->FindByID(XPARA_ID_test_apps);
// 	BOOL bRet4 = TRUE;
// 
// 	if (pApps != NULL)
// 	{
// 		bRet4 = DownLoadFiles_TestApps(pApps);
// 	}

	return bRet3&&bRet2&&bRet1&&bRet4&&bRet5;
}

BOOL CSttSmartTestCom::DownLoadFiles_Devices(CDataGroup *pDevices)
{
	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);
	CString strFile, strFile_s, strRootPath;
	CString strFileDownLoad;

	POS pos = pDevices->GetHeadPosition();
	CString strDvmRoot, strPpRoot;
	strRootPath = _P_GetInstallPath();
	strDvmRoot = strRootPath + _T("e-Protocol\\Library\\");
	strPpRoot = strRootPath + _T("e-Protocol\\Template\\");
	BOOL bReturn = TRUE;

	while (pos != NULL)
	{
		CDataGroup *pDevice = (CDataGroup *)pDevices->GetNext(pos);

		//下载模型文件
		strFile_s.Empty();
		pDevice->GetDataValue(XPARA_ID_DVMFILE_S, strFile_s);
		pDevice->GetDataValue(XPARA_ID_DVMFILE, strFile);
		BOOL bRet = TRUE;

		if (strFile_s.IsEmpty())
		{
			//模型文件是必须项，若不存在，直接返回下载失败
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("被测设备模型文件【%s】为空，下载失败！"), strFile);
			//充电桩自动测试，可以不用模型，故此处修改为非必须，下载失败不返回失败
			//2021 12 28 shaolei
			//bRet = FALSE;
		}
		else
		{	
			strFileDownLoad = strDvmRoot + strFile;
			strUrl = strHttpUrlHead + strFile_s;

			if (IsFileExist(strFileDownLoad))
			{
				bRet = TRUE;
			}
			else
			{
				bRet = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
			}
		}

		if (!bRet)
		{
			bReturn = FALSE;
		}

		//下载规约模板文件
		strFile_s.Empty();
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE_S, strFile_s);
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE, strFile);

		if (!strFile_s.IsEmpty())
		{
			//规约模板文件不是必须项，若不存在，则跳过下载
			strFileDownLoad = strPpRoot + strFile;
			strUrl = strHttpUrlHead + strFile_s;

			if (IsFileExist(strFileDownLoad))
			{
				bRet = TRUE;
			}
			else
			{
				bRet = CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
			}

			if (!bRet)
			{
				bReturn = FALSE;
			}
		}
	}

	return bReturn;
}

BOOL CSttSmartTestCom::DownLoadFiles_TestApps(CDataGroup *pTestApps)
{
	BOOL bReturn = TRUE;
	return bReturn;
}
