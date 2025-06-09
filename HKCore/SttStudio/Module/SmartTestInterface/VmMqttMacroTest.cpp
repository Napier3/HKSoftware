#include "stdafx.h"
#include"VmMqttMacroTest.h"

#include "../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "MacroTestFactory.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"

#ifdef _PSX_QT_LINUX_
        #include "SttMacroTestMsgRcvInterface_Linux.h"
#else
        #include "SttMacroTestMsgRcvInterface_Win.h"
#endif
#include "../SttCmd/SttChMaps.h"
#include "../Engine/SttNativeTestEngine.h"
#include "AtsOutInterfaceMqttClient.h"

#define ADJUST_MACROID_ADJUSTONE   _T("AdjustOne")
#define ADJUST_MACROID_ADJUSTTHREE   _T("AdjustThree")
#define ADJUST_MACROID_ADJUSTSWITCH   _T("AdjustSwitch")
#define ADJUST_MACROID_ADJUSTONECOPY   _T("AdjustOneCopy")

#define HdResReqType_request  _T("request")
#define HdResReqType_release  _T("release")


CVmMqttMacroTest::CVmMqttMacroTest()
{
	CSttNativeTestEngineInterfaces::Create();

	m_bTestStarted = FALSE;
//2020-11-6  lijunqing
    m_oReportBuffer.SetBufferLength(256000);
    m_oReportBuffer.AllocBuffer(0);

 	m_pVmMqttMacroTestSpyDlg = NULL;
}


CVmMqttMacroTest::~CVmMqttMacroTest(void)
{
	MqttRemoveFromClient();

	if (m_pVmMqttMacroTestSpyDlg != NULL)
	{
		delete m_pVmMqttMacroTestSpyDlg;
		m_pVmMqttMacroTestSpyDlg = NULL;
	}

	CSttNativeTestEngineInterfaces::Release();
}

void CVmMqttMacroTest::MqttAddToClient()
{
	CAtsOutInterfaceMqttClient::Create(m_strBenchSN);
	g_theAtsOutMqttClient->MqttAdd(this);
}

void CVmMqttMacroTest::MqttRemoveFromClient()
{
	g_theAtsOutMqttClient->MqttRemove(this);
	CAtsOutInterfaceMqttClient::Release();
}

//MQTT事件处理接口，共CMqttMsgInterface对象调用
//class CMqttMsgProcessInterface

//根据收到的MQTT主题进行匹配，如果匹配成功，则返回TRUE，否则返回FALSE
//主题：测试仪SN/BenchSN/TestState/#
BOOL CVmMqttMacroTest::MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser)
{
	if ( m_strTestAppSN == oSttMqttTopicParser.m_pszSubTopic[0] )
	{
		return TRUE;
	}
	
	if ( m_strTestAppSN == oSttMqttTopicParser.m_pszSubTopic[1] )
	{
		return TRUE;
	}

	return FALSE;
}

//MQTT消息处理
//hd_res_req/ATS/TestState/StartTest/REPLY
//hd_res_req/ATS/TestState/EVENT/TestFinished
void CVmMqttMacroTest::MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser)
{
	CSttSysState oSysState;
	dvm_IncGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oSysState.SetXml_UTF8(oSttMqttTopicParser.m_pMqttPkgBuffer, oSttMqttTopicParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	dvm_DecGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	CSttMacro *pMacro = oSysState.GetSttMacro();
	
	if (oSttMqttTopicParser.m_nCount > 4)
	{//异常处理：不如不足五个，则忽略
	if (strcmp(oSttMqttTopicParser.m_pszSubTopic[4], SYS_STATE_EVENT_OnTestFinished) == 0)
	{
		OnTestFinished(pMacro->m_strID, pMacro->GetParas(), pMacro->GetResults());
	}
	else if (strcmp(oSttMqttTopicParser.m_pszSubTopic[4], SYS_STATE_EVENT_OnTestStarted) == 0)
	{
		OnTestStarted(m_strTestMacroID, oSysState.GetSttParas());
	}
	else if (strcmp(oSttMqttTopicParser.m_pszSubTopic[4], SYS_STATE_EVENT_OnTestStoped) == 0)
	{
		OnTestStoped(m_strTestMacroID, oSysState.GetSttParas());
	}
	else
	{

	}
	}
}

//MQTT主题订阅接口函数：MQTT Client连接成功后，遍历各CMqttMsgProcessInterface
//订阅相关的主题
//主题：测试仪SN/BenchSN/TestState/#
BOOL CVmMqttMacroTest::MqttSubscribeTopic()
{
	CString strTopic ;
	strTopic.Format(_T("%s/+/TestState/#"), m_strTestAppSN.GetString());
	g_theAtsOutMqttClient->SubscribeTopic(strTopic, 0);
	strTopic.Format(_T("%s/TestState/#"), m_strTestAppSN.GetString());
	g_theAtsOutMqttClient->SubscribeTopic(strTopic, 0);
	strTopic.Format(_T("+/%s/TestState/#"), m_strTestAppSN.GetString());
	g_theAtsOutMqttClient->SubscribeTopic(strTopic, 0);

	return TRUE;
}

//MQTT取消主题订阅接口函数：MQTT Client断开连接后，遍历各CMqttMsgProcessInterface
//T取消订阅相关的主题
BOOL CVmMqttMacroTest::MqttUnSubscribeTopic()
{
	CString strTopic ;
	strTopic.Format(_T("%s/+/TestState/#"), m_strTestAppSN.GetString());
	g_theAtsOutMqttClient->UnSubscribeTopic(strTopic);
	strTopic.Format(_T("%s/TestState/#"), m_strTestAppSN.GetString());
	g_theAtsOutMqttClient->UnSubscribeTopic(strTopic);
	strTopic.Format(_T("+/%s/TestState/#"), m_strTestAppSN.GetString());
	g_theAtsOutMqttClient->UnSubscribeTopic(strTopic);

	return TRUE;
}

void CVmMqttMacroTest::Release()
{
	
    CMacroTestInterface::Release();
}

void CVmMqttMacroTest::OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	PostTestWndMsg(MTMSG_CommError, 0);
}

long CVmMqttMacroTest::SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID)
{
//     if (m_pTestMsgRcv != NULL)
//     {
//         m_pTestMsgRcv->SetWndMsg(hMainWnd, nMsgID);
//     }

    m_hMsgWnd = hMainWnd;
    m_nMsgID = nMsgID;

	return 0;
}

CString CVmMqttMacroTest::GetConfig()
{
	return _T("");
}

long CVmMqttMacroTest::SetConfig(CSttTestAppCfg *pSttTestAppCfg)
{
	//m_oSttTestClient.SetTestAppConfig(pSttTestAppCfg);

	return 0;
}

long CVmMqttMacroTest::SetConfig(const CString & bstrConfig)
{
	//m_oSttTestClient.SetTestAppConfig(bstrConfig);

	return 0;
}

BOOL CVmMqttMacroTest::IsAdjust(const CString &strMacroID)
{
	//2020-10-24  lijunqing
	//测试功能的类型判断
	if (m_pTestMacro->m_strType.CompareNoCase(_T("adjust")) == 0)
	{
		return TRUE;
	}

	if (strMacroID == ADJUST_MACROID_ADJUSTTHREE || strMacroID == ADJUST_MACROID_ADJUSTONE
	 	|| strMacroID == ADJUST_MACROID_ADJUSTSWITCH || strMacroID == STT_CMD_TYPE_ADJUST_WriteFile
		|| strMacroID == ADJUST_MACROID_ADJUSTONECOPY)
	{
		return TRUE;
	}

	return FALSE;
}


long CVmMqttMacroTest::Test(const CString & strMacroID, const CString & strParameter)
{
// 	if (m_pVmMqttMacroTestSpyDlg == NULL)
// 	{
// 		m_pVmMqttMacroTestSpyDlg = new CVmSttMacroTestSpyDlg();
// 
// #ifdef _PSX_IDE_QT_
// 
// #else
// 		m_pVmMqttMacroTestSpyDlg->SetUseModeless();
// 		m_pVmMqttMacroTestSpyDlg->DoModal();
// #endif
// 	}

    //m_strReport.Empty();
    //2020-11-6  lijunqing
    m_oReportBuffer.SeekToHead();
    m_oReportBuffer.StringEnd();

	if (strMacroID != m_pTestMacro->m_strID)
	{
		return -1;
	}

	//for debug
 	if (!ConnectDevice())
 	{
         CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.. MacroID = %s, strParameter = %s"), strMacroID.GetString(), strParameter.GetString());
 
         return -1;
 	}

	//CDataGroup oDataGroup;
	BOOL bRet_SetParameter = SetParameter(m_pTestMacro, strParameter);
	long nRet = STT_CMD_ExecStatus_NULL;

	//通道映射，需要特殊处理，从固定路径下获取对应的文件，形成参数
	if (m_pTestMacro->m_strID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		if (!SetParameter_ChMapsConfig(m_oFaultParas_Dvm, strParameter))
		{
			return -1;
		}

		nRet = Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
		return 0;
	}

    //IEC61850配置，特殊处理
    if(m_pTestMacro->m_strID == STT_CMD_TYPE_SYSTEM_IECConfig)
    {
		if(!SetParameter_IECConfig(m_oFaultParas_Dvm, strParameter))
		{
				return -1;
		}

        nRet = Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
        return 0;
    }

	//系统参数配置，特殊处理
	if(m_pTestMacro->m_strID == STT_CMD_TYPE_SYSTEM_SystemConfig)
	{
		if (!bRet_SetParameter)
		{
			if(!SetParameter_SystemConfig(m_oFaultParas_Dvm, strParameter))
			{
				return -1;
			}
		}
		
        nRet = Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
		return 0;
	}

	//校准命令特殊处理
	if (IsAdjust(strMacroID))
	{
		if (strMacroID == STT_CMD_TYPE_ADJUST_WriteFile)
		{
			//nRet = m_oSttTestClient.Adjust_WriteFile(TRUE);
		}
		else
		{
			nRet = Adjust_Adjust(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
		}
	}
	else if (strMacroID.Find(STT_CMD_TYPE_TEST_SysDefaultOutput) >= 0)
	{
		//系统默认输出命令，特殊处理：当收到Success后，直接发送结束消息
		nRet = Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, FALSE);  //同步方式

		if (Stt_Is_ExecStatus_Success(nRet))
		{
            PostTestWndMsg(MTMSG_TestFinished, 0);
		}
	}
	else
	{
		nRet = Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
	}

	return 0;
}

long CVmMqttMacroTest::Test(const CString & strMacroID, CDataGroup *pParas)
{
	m_pTestMacro = NULL;

// 	if (m_pVmMqttMacroTestSpyDlg == NULL)
// 	{
// 		m_pVmMqttMacroTestSpyDlg = new CVmSttMacroTestSpyDlg();
// 
// #ifdef _PSX_IDE_QT_
// 
// #else
// 		m_pVmMqttMacroTestSpyDlg->SetUseModeless();
// 		m_pVmMqttMacroTestSpyDlg->DoModal();
// #endif
// 	}

	m_oReportBuffer.SeekToHead();
	m_oReportBuffer.StringEnd();

	if (!ConnectDevice())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.. MacroID = %s"), strMacroID.GetString());
		return -1;
	}

	m_oFaultParas_Dvm.DeleteAll();
	m_oFaultParas_Dvm.AppendCloneEx(*pParas);
	Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);

	return 0;
}

CString CVmMqttMacroTest::GetReport()
{
	//此函数，暂时没有添加应答
	//long nRet = m_oClientTestEngine.Test_GetReport(strID);

	//shaolei 2021 07 29
    //所有的结果参数，均已经在m_oResults_Dvm中，此处不用再从TestMacro.xml文件中获取结果了
    //故注释，20220221
    //GetResultFromTestMacro();

    CString strReport;
    m_oReportBuffer.StringEnd();
    strReport = m_oReportBuffer.GetBuffer();
    return strReport;
}

//2023-6-20  lijunqing
CDataGroup* CVmMqttMacroTest::GetResults()
{
	return &m_oResults_Dvm;
}

long CVmMqttMacroTest::StopTest()
{
	return SendCmd_Test(_T(""), NULL, STT_CMD_TYPE_TEST_StopTest);
}

/*
<test-cmd name="" id=" CloseDevice " testor="TEST">
</test-cmd>
*/
long CVmMqttMacroTest::CloseDevice()
{
	return SendCmd_Test(_T(""), NULL,  STT_CMD_TYPE_TEST_CloseDevice);
}

CString CVmMqttMacroTest::GetSearchReport()
{
	CValues oValues;
	POS pos = m_oSearchRslts.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)m_oSearchRslts.GetNext(pos);
		oValues.AddValue(pData->m_strID, pData->m_strValue);
	}

	return oValues.GetDatasString();
}

long CVmMqttMacroTest::FinishTest(long nState)
{
	return 0;
}

long CVmMqttMacroTest::ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter)
{
	return 0;
}

unsigned long CVmMqttMacroTest::GetExternMsgRcvWnd()
{
	return 0;
}

unsigned long CVmMqttMacroTest::GetExternMsgID()
{
	return 0;
}

unsigned long CVmMqttMacroTest::StopDevice(void)
{
	return 0;
}

long CVmMqttMacroTest::UpdateParameter(const CString &strMacroID, CDataGroup *pParas)
{
    if(pParas == NULL)
    {
        return -1;
    }

    if (! g_theAtsOutMqttClient->IsConnectSuccessful())
    {
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.."), strMacroID.GetString());
        return -1;
    }

	m_oFaultParas_Dvm.InitDataValues(pParas, TRUE);  //把更新的参数，更新到故障啊参数中
	return Test_UpdateParameter(strMacroID, pParas);
}

/*
<test-cmd name="" id="TriggerTest" testor="TEST">
	<paras name="" id="">	
		<data id="TriggerID" value="1"/>  【触发的标识】
		……….
	</paras>
</test-cmd>
*/
long CVmMqttMacroTest::ManualTrigger()
{
    if (! g_theAtsOutMqttClient->IsConnectSuccessful())
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.."));
        return -1;
    }

	Test_SendTrigger();

	return 0;
}

BOOL CVmMqttMacroTest::SetParameter(CTestMacro *pTestMacro, const CString & strParameter)
{
    m_oFaultParas_Dvm.DeleteAll();
    m_oResults_Dvm.DeleteAll();
    pTestMacro->GetTestMacroParas_Fault_CloneEx(&m_oFaultParas_Dvm);
    pTestMacro->GetTestMacroParas_Result_CloneEx(&m_oResults_Dvm);

    long nLen = strParameter.GetLength();

    if(nLen > 6)
    {
        CString strLeft = strParameter.Left(6);

        if(strLeft == _T("<group"))
        {
            //如果TestMacroUiParas中有参数，则可以解析成一个CDataGroup
			//并且，该参数有可能只保存了非默认值
            CDataGroup oGroup;
            BSTR bstrText = strParameter.AllocSysString();
            CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
            BOOL bRet = oGroup.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
            CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

        #ifdef _PSX_IDE_QT_
            delete bstrText;
        #else
            SysFreeString(bstrText);
        #endif

            if(bRet)
            {
				/*  //非默认值，则不能直接删除后克隆
                m_oFaultParas_Dvm.DeleteAll();
                m_oFaultParas_Dvm.AppendCloneEx(oGroup, TRUE);
				*/
				m_oFaultParas_Dvm.InitDataValues(&oGroup, TRUE);
                return TRUE;
            }
        }
    }

    CString strLeft = strParameter.Left(1);

    if(strLeft == _T("<"))
    {
        return FALSE;
    }

	CEquationBuffer *pEquation = new CEquationBuffer;
	pEquation->InitBuffer(strParameter);
	//pTestMacro->InitParas_Dvm()
	//pTestMacro->GetTestMacroParas_Fault_CloneEx(&oDataGroup);

	m_oFaultParas_Dvm.Parser(pEquation);
	delete pEquation;
	return TRUE;
}

BOOL CVmMqttMacroTest::SetParameter_ChMapsConfig(CDataGroup &oDataGroup, const CString &strParameter)
{
	if (oDataGroup.GetCount() == 0 || strParameter.Left(1) == _T("<"))
	{
		return  SetParameter_ChMapsConfig_UIParas(oDataGroup, strParameter);
	}

	CDvmData *pChMapsConfigFile = (CDvmData *)oDataGroup.FindByID(STT_CMD_PARA_ChMapConfig_File);

	if (pChMapsConfigFile == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">> 通道映射配置，参数中找不到配置文件名..."));
        return  SetParameter_ChMapsConfig_UIParas(oDataGroup, strParameter);
	}

	//固定的路径
	CString strPath = _P_GetLibraryPath();
	strPath += _T("ChMapsConfig\\");

	pChMapsConfigFile->m_strValue.Replace(_T("\""), _T(""));
	CString strFile = strPath + pChMapsConfigFile->m_strValue;

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> 通道映射配置，映射文件【%s】不存在..."), strFile.GetString());
        return  SetParameter_ChMapsConfig_UIParas(oDataGroup, strParameter);
	}

	oDataGroup.DeleteAll();
    CSttChMaps *pMaps = new CSttChMaps;
    BOOL bOpen = pMaps->OpenChMapsFile(strFile);

	if (!bOpen)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> 通道映射配置，映射文件【%s】打开失败..."), strFile.GetString());
		return FALSE;
	}

    //CSttChMaps *pNew = (CSttChMaps *)oMaps.CloneEx(TRUE, TRUE);
    oDataGroup.AddNewChild(pMaps);

	return TRUE;
}

BOOL CVmMqttMacroTest::SetParameter_ChMapsConfig_UIParas(CDataGroup &oDataGroup, const CString &strParameter)
{
    BOOL bRet = FALSE;
    oDataGroup.DeleteAll();;

    if(strParameter.IsEmpty())
    {
        return bRet;
    }

    CSttChMaps *pMaps = new CSttChMaps;
    BSTR bstrText = strParameter.AllocSysString();
    bRet = pMaps->SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

#ifdef _PSX_IDE_QT_
    delete bstrText;
#else
    SysFreeString(bstrText);
#endif

    if(!bRet)
    {
        return FALSE;
    }

    //CSttChMaps *pNew = (CSttChMaps *)oMaps.CloneEx(TRUE, TRUE);
    oDataGroup.AddNewChild(pMaps);
    return TRUE;
}

 BOOL CVmMqttMacroTest::SetParameter_IECConfig(CDataGroup &oDataGroup, const CString &strParameter)
 {
	 if(strParameter.Left(1) == _T("<"))
	 {
		 return SetParameter_IECConfig_UIParas(oDataGroup, strParameter);
	 }

     BOOL bRet = FALSE;
    CDvmData *pIecCfg_File = (CDvmData *)oDataGroup.FindByID(STT_CMD_PARA_IecCfg_File);

    if (pIecCfg_File == NULL)
    {
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">>测试仪 IECCFG配置功能测试，参数中找不到配置文件名..."));
		return FALSE;
	}

	CString strPath;
// 		strPath = _P_GetLibraryPath();
// 		strPath += _T("IEC61850Config/");

	if (pIecCfg_File->m_strValue.Find(_T(".ixml")) < 0 && pIecCfg_File->m_strValue.Find(_T(".iecfg")) < 0)
	{
		strPath = pIecCfg_File->m_strValue + _T(".ixml");
	}
	else
	{
		strPath = pIecCfg_File->m_strValue;
	}
	
	//strPath += _T(".ixml");
	CIecCfgDatasMngr *pNewCfgDatasMngr = new CIecCfgDatasMngr;
	bRet = pNewCfgDatasMngr->OpenIecCfgFile(strPath);

	if (!bRet)
	{
		return FALSE;
	}

	oDataGroup.DeleteAll();
	oDataGroup.AddNewChild(pNewCfgDatasMngr);
	return TRUE;
 }

BOOL CVmMqttMacroTest::SetParameter_IECConfig_UIParas(CDataGroup &oDataGroup, const CString &strParameter)
{
	CIecCfgDatasMngr *pNewCfgDatasMngr = new CIecCfgDatasMngr;
	BSTR bstrText = strParameter.AllocSysString();
	BOOL bRet = pNewCfgDatasMngr->SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);
#endif

	if(!bRet)
	{
		return FALSE;
	}

	oDataGroup.DeleteAll();
	//CIecCfgDatasMngr *pNew = (CIecCfgDatasMngr *)oCfgDatasMngr.CloneEx(TRUE, TRUE);
	oDataGroup.AddNewChild(pNewCfgDatasMngr);

	return TRUE;
}

BOOL CVmMqttMacroTest::SetParameter_SystemConfig(CDataGroup &oDataGroup, const CString &strParameter)
{
	BOOL bRet = FALSE;
	CSttMacro oVmMqttMacro;
    oVmMqttMacro.SetCreateMacroChild(TRUE);
	BSTR bstrText = strParameter.AllocSysString();
    bRet = oVmMqttMacro.SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);
#endif

	if(!bRet)
	{
		return FALSE;
	}

	oDataGroup.DeleteAll();
	CSttParas *pParas = oVmMqttMacro.GetParas();
	oDataGroup.AppendCloneEx(*pParas, TRUE);

	return TRUE;
}


/*
<ats-cmd name="" id=" ConnectDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<group id="test-app">
			<data id="DeviceSN" value="123456789"/>
			<data id="EngineProgID" value="IotVm"/>
			<data id="dvm-file" value="MacroTest.xml"/>
			<data id="remote-ip" value="127.0.0.1"/>
			<data id="remote-port" value="9988"/>
		</group>
	</paras>
</ats-cmd>
*/
BOOL CVmMqttMacroTest::ConnectDevice()
{
	if (g_theAtsOutMqttClient->IsConnectSuccessful())
	{
		return TRUE;
	}
	
	g_theAtsOutMqttClient->Connect(m_strBenchSN);

    if (g_theAtsOutMqttClient->IsConnectSuccessful())
	{
        PostTestWndMsg(MTMSG_ConnectSuccess, 0);
		return TRUE;
	}
    else
    {
        PostTestWndMsg(MTMSG_ConnectFaild, 0);
		return FALSE;
    }
}

long CVmMqttMacroTest::System_Login()
{
	//return m_oSttTestClient.System_LoginEx();
	return 0;
}

long CVmMqttMacroTest::Adjust_ReadDeviceParameter(CStringArray &astrTypes, BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	if (!g_theAtsOutMqttClient->IsConnectSuccessful())
	{
		return 0;
	}

	return 0;
	//return m_oSttTestClient.Adjust_ReadDeviceParameter(astrTypes, bDoEvents, pRetData, bSendCmdAsync);
}

void CVmMqttMacroTest::PostTestWndMsg(WPARAM wParam, LPARAM lParam)
{
	if (!::IsWindow(((HWND)m_hMsgWnd)))
	{
		return;
	}

	::PostMessage((HWND)m_hMsgWnd, m_nMsgID, wParam, lParam);
}

long CVmMqttMacroTest::Test_StartTest(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	m_strTestMacroID = strMacroID;
	return SendCmd_Test(strMacroID, pParas, STT_CMD_TYPE_TEST_StartTest);
}

long CVmMqttMacroTest::Test_UpdateParameter(const CString &strMacroID, CDataGroup *pParas)
{
	return SendCmd_Test(strMacroID, pParas,  STT_CMD_TYPE_TEST_UpdateParameter);
}

long CVmMqttMacroTest::Test_SendTrigger()
{
	return SendCmd_Test(_T(""), NULL, STT_CMD_TYPE_TEST_TriggerTest);
}

void CVmMqttMacroTest::InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, const CString &strCmdType, const CString &strCmdID)
{
	oTopicCmbn.ResetSubTopics();
	oTopicCmbn.AddSubTopic(m_strBenchSN);
	oTopicCmbn.AddSubTopic(m_strTestAppSN);
	oTopicCmbn.AddSubTopic(strCmdType);
	oTopicCmbn.AddSubTopic(strCmdID);
}

//测试功能事件接口
void CVmMqttMacroTest::OnTestStarted(const CString &strMacroID, CDataGroup *pParas)
{
	//后续添加获取总的测试时长消息
	//m_pVmMqttMacroTestSpyDlg->ShowSpy(0);

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("OnTestStarted   ++  MacroID = %s"), strMacroID.GetString());
	m_bTestStarted = TRUE;

	//对于状态序列功能，进行特殊处理：根据状态数，删除多余的故障和结果参数
	CDvmData *pStateCount = (CDvmData *)m_oFaultParas_Dvm.FindByID(_T("StateCount"));

	if (pStateCount != NULL)
	{
		long nStateCount = CString_To_long(pStateCount->m_strValue);
		ResetParasByStateCount(nStateCount);
		ResetParas_RsltEvalute();
	}

	PostTestWndMsg(MTMSG_TestBegin, 0);
}

void CVmMqttMacroTest::OnTestStoped(const CString &strMacroID, CDataGroup *pParas)
{
	m_bTestStarted = FALSE;
}

void CVmMqttMacroTest::OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{
	//m_pVmMqttMacroTestSpyDlg->HideSpy();

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("OnTestFinished   ++  MacroID = %s"), strMacroID.GetString());

	if (strMacroID == HdResReqType_request || strMacroID == HdResReqType_release)
	{
		m_oResults_Dvm.DeleteAll();
		m_oResults_Dvm.AppendCloneEx(*pResults);
		AppendReport_ResultEx(&m_oResults_Dvm);
		PostTestWndMsg(MTMSG_TestFinished, 0);
		m_bTestStarted = FALSE;

		return;
	}

	m_oResults_Dvm.InitDataValues(pResults, TRUE);

	//对于状态序列功能，进行特殊处理：根据状态数，删除多余的故障和结果参数
	CDvmData *pStateCount = (CDvmData *)m_oFaultParas_Dvm.FindByID(_T("StateCount"));

	if (pStateCount != NULL)
    {
		long nStateCount = CString_To_long(pStateCount->m_strValue);
		ResetParasByStateCount(nStateCount);
		ResetParas_RsltEvalute();
    }

	AppendReport_ResultEx(&m_oResults_Dvm);

    //shaolei   新平台脱机软件，需要将结果返回给网页显示，将故障参数部分也作为结果传回
   AppendReport_ResultEx(&m_oFaultParas_Dvm);

	PostTestWndMsg(MTMSG_TestFinished, 0);
	m_bTestStarted = FALSE;
}

void CVmMqttMacroTest::OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{

}

/*
<sys-state name="" id="" ldName="0" LDdesc="1970-01-01 01:05:58" scl_gcb_confRev="" scl_gcb_APPID="EVENT" scl_gse_APPID="test-cmd">
	<paras name="" id="">
		<data name="ExecStatus" id="ExecStatus" data-type="string" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<group name="Event" id="Event" data-type="Event" value="">
			<data name="绝对时间" id="Time" data-type="time" value="993747952.809979558" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="相对时间" id="RealTime" data-type="double" value="19.809979558" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="Bin001" id="Bin001" data-type="long" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="Event" id="Event" data-type="Event" value="">
			<data name="绝对时间" id="Time" data-type="time" value="993747952.810141921" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="相对时间" id="RealTime" data-type="double" value="19.810141921" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="Bin001" id="Bin001" data-type="long" value="1" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="Event" id="Event" data-type="Event" value="">
			<data name="绝对时间" id="Time" data-type="time" value="993747952.810370088" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="相对时间" id="RealTime" data-type="double" value="19.810370088" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="Bin001" id="Bin001" data-type="long" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</paras>
</sys-state>
*/
//每一个sys-state$paras$group都会调用一次OnTestState
void CVmMqttMacroTest::OnTestState(const CString &strMacroID, CDataGroup *pParas)
{
	//EVENT事件，例如开入变位等信息，需要记录到报告中
	//shaolei 2020526
// 	POS pos = pParas->GetHeadPosition();
// 	CDvmData *pData = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pParas->GetNext(pos);
// 		m_oReportBuffer.AppendEquation(pData->m_strID.GetString(), pData->m_strValue.GetString());
// 	}

	//shaolei 20210627
	POS pos = pParas->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmData *pTime = (CDvmData *)pParas->FindByID(_T("Time"));
	CDvmData *pRealTime = (CDvmData *)pParas->FindByID(_T("RealTime"));

	//2021-10-13  lijunqing
	/*CTmResultParas *pResults = (CTmResultParas *)m_pTestMacro->GetResults();*/

	while (pos != NULL)
	{
		pData = (CDvmData *)pParas->GetNext(pos);

		if (pData->m_strID == _T("Time") || pData->m_strID == _T("RealTime"))
		{
			continue;
		}

		m_oReportBuffer.AppendEquation(pData->m_strID.GetString(), pData->m_strValue.GetString());
		m_oResults_Dvm.SetDataValue(pData->m_strID, pData->m_strValue, TRUE);//2021-10-13  lijunqing

		CString strID;

		if (pTime != NULL)
		{
            strID.Format(_T("%s$%s"), pData->m_strID.GetString(), pTime->m_strID.GetString());
			m_oReportBuffer.AppendEquation(strID.GetString(), pTime->m_strValue.GetString());
			m_oResults_Dvm.SetDataValue(strID, pTime->m_strValue, TRUE);//2021-10-13  lijunqing
		}

		if (pRealTime != NULL)
		{
            strID.Format(_T("%s$%s"), pData->m_strID.GetString(), pRealTime->m_strID.GetString());
			m_oReportBuffer.AppendEquation(strID.GetString(), pRealTime->m_strValue.GetString());
			m_oResults_Dvm.SetDataValue(strID, pRealTime->m_strValue, TRUE);//2021-10-13  lijunqing
		}
	}
}

/*
<search-results name="" id="">【从CDataGroup派生】
	<data name="搜索起点" id="SearchBegin" value="0.25" />
	<data name="当前值" id="CurrSearchVal" value="0.270000011" />
	<data name="搜索终点" id="SearchEnd" value="0.75" />
	<data name="搜索区间长度" id="SearchArea" value="0.5" />
	<data name="I1(Ie)" id="TripI1Ie" value="0.735000014" />
	<data name="I1A" id="TripI1A" value="0.735000014" />
	<data name="I2(Ie)" id="TripI2Ie" value="0.729984283" />
	<data name="I2A" id="TripI2A" value="0.729984283" />
</search-results>
*/
void CVmMqttMacroTest::OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults)
{
	m_oSearchRslts.DeleteAll();
	m_oSearchRslts.AppendCloneEx(*pSearchResults, TRUE);

	//记录搜索结果，发送消息给自动测试。自动测试收到消息后，会来获取结果
	PostTestWndMsg(MTMSG_SearchPointReport, 0);
}

void CVmMqttMacroTest::OnReport(CDataGroup *pParas)
{
	//这个函数不会被调用
// 	POS pos = pParas->GetHeadPosition();
// 	CDvmData *pData = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pParas->GetNext(pos);
// 		CString strReport;
// 		strReport.Format(_T("%s=%s;"), pData->m_strID, pData->m_strValue);
// 		m_strReport.AppendFormat(strReport);
// 	}
}

//#include "../../Native/Module/SttNativeTestMainApp.h"
//ret-type="REPORT" id-cmd="test-cmd"
/*
<sys-state name="" id="StartTest" mid="0" time="1970-01-01 00:00:00" mater-host="" ret-type="REPORT" id-cmd="test-cmd">
	<paras name="" id="">
		<data name="ExecStatus" id="ExecStatus" data-type="string" default-value="" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	</paras>
	<macro name="" id="" version="" type="" remark="">
		<results name="" id="">
			<group id="state0" data-type="State">
				<data id="TtripBin1" value="0" />
				<data id="TtripBin2" value="0" />
				……
				<data id="RampStepIndexBin8" value="-1" />
				<group id="ActRcd" data-type="ActRcd" />
			</group>
			<group id="state1" data-type="State">
				<data id="TtripBin1" value="0" />
				<data id="TtripBin2" value="0" />
				……
				<data id="RampStepIndexBin8" value="-1" />
				<group id="ActRcd" data-type="ActRcd" />
			</group>
			<group id="state2" data-type="State">
				<data id="TtripBin1" value="0" />
				<data id="TtripBin2" value="0" />
				……
				<data id="RampStepIndexBin8" value="-1" />
				<group id="ActRcd" data-type="ActRcd" />
			</group>
		</results>
	</macro>
</sys-state>
*/
void CVmMqttMacroTest::OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas)
{
	if (pParas->m_strID == STT_CMD_TYPE_ADJUST_ReadDeviceParameter)
	{
		stt_OnReport_ReadDeviceParameter(pParas);
// 		m_oReadDeviceParameter.DeleteAll();
// 		m_oReadDeviceParameter.AppendCloneEx2(*pParas);
		return;
	}

	if (m_pTestMacro != NULL)
	{
		//状态序列功能，重复测试时，每个REPORT都需要发送ats-cmd的REPORT事件；
		if (m_pTestMacro->m_strID != _T("StateTest"))
		{
			return;
		}
	}

	CDvmData *pRepeatTimes = (CDvmData *)m_oFaultParas_Dvm.FindByID(_T("_RepeatNumbers"));

	if (pRepeatTimes == NULL)
	{
		return;
	}

	long nRepeatTimes = CString_To_long(pRepeatTimes->m_strValue);

	if (nRepeatTimes <= 0)
	{
		return;
	}

	CSttSysState oSysState;
	CSttParas *pRtParas = oSysState.GetSttParas();
	oSysState.SetReporting();
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
	CSttReports *pSttReports = pRtParas->GetSttReports(TRUE);
	CSttReport *pRpt = new CSttReport;
	pSttReports->AddNewChild(pRpt);
	pRpt->InitValues(NULL);
	CDvmValues *pValues = pRpt->m_pValues;

	CSttSysState *pState = (CSttSysState *)pParas->GetParent();
	CSttMacro *pMacro = pState->GetSttMacro();
	CSttResults *pResults = pMacro->GetResults();
	CExBaseList oList;
	pResults->SelectAllDatas(oList);//这个链表中的参数暂时不带路径信息

	POS pos = oList.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)oList.GetNext(pos);
	 	CDvmValue *pNew = new CDvmValue();
	 	pNew->m_strID = pData->GetIDPathEx(pResults);
	 	pNew->m_strValue = pData->m_strValue;
		pValues->AddNewChild(pNew);
	}

	oList.RemoveAll();

	AppendReport_ResultEx(pValues, &m_oFaultParas_Dvm);

	oSysState.Set_Xml_Pkg_With_Name(TRUE);

	if (g_theNativeTestEngine != NULL)
	{
		g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

	oSysState.Set_Xml_Pkg_With_Name(FALSE);
}

long CVmMqttMacroTest::OnAts_Stop(CDataGroup *pParas)
{
	//shaolei 20210526  测试仪急停事件
	//暂时先发送通讯错误消息
	//char strIP[20] = {0};
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("测试仪【%s】急停！自动测试停止测试！"), strIP);
	PostTestWndMsg(MTMSG_CommError, 0);
	m_bTestStarted = FALSE;
	return 0;
}

void CVmMqttMacroTest::SetConfig_TestApp()
{
	if (m_pSttTestApp == NULL)
	{
		return;
	}

	SetConfig(m_pSttTestApp);
}

void CVmMqttMacroTest::GetParaIDPath(CString &strPath, CDvmData *pData)
{
	strPath.Empty();
	CExBaseObject *pParent = pData;
	CString strTemp;

	while (pParent != NULL)
	{
		if (pParent->m_strID.GetLength() == 0)
		{
			break;
		}

        strTemp.Format(_T("%s$"), pParent->m_strID.GetString());
		strPath = strTemp + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent == NULL)
		{
			break;
		}

		if (pParent->m_strID.IsEmpty())
		{
			break;
		}

// 		if (pParent->GetClassID() != STTCMDCLASSID_CSTTRESULTS)
// 		{
// 			break;
// 		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - 1;
		strPath = strPath.Left(nLen);
	}
}

//形参为测试仪底层返回的结果数据的group
void CVmMqttMacroTest::AppendReport_ResultEx(CDataGroup *pRsltGroup)
{
	CDvmData *pData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	POS pos = pRsltGroup->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pRsltGroup->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pGroup = (CDataGroup *)pObj;
			AppendReport_ResultEx(pGroup);
			continue;
		}

        if(nClassID  != DVMCLASSID_CDVMDATA)
            continue;

		pData = (CDvmData *)pObj;
		CString strID;
		GetParaIDPath(strID, pData);

		m_oReportBuffer.AppendEquation(strID.GetString(), pData->m_strValue.GetString());
	}
}

void CVmMqttMacroTest::AppendReport_ResultEx(CDvmValues *pValues, CDataGroup *pRsltGroup)
{
	CDvmData *pData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	POS pos = pRsltGroup->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pRsltGroup->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pGroup = (CDataGroup *)pObj;
			AppendReport_ResultEx(pValues, pGroup);
			continue;
		}

		if(nClassID  != DVMCLASSID_CDVMDATA)
			continue;

		pData = (CDvmData *)pObj;
		CString strID;
		GetParaIDPath(strID, pData);

		CDvmValue *pNew = new CDvmValue();
		pNew->m_strID = strID;
		pNew->m_strValue = pData->m_strValue;
		pValues->AddNewChild(pNew);
	}
}

void CVmMqttMacroTest::GetResultFromTestMacro()
{
	CTmResultParas *pResults = (CTmResultParas *)m_pTestMacro->GetResults();
	CTmResultParasEx *pResultsEx = m_pTestMacro->GetResultsEx();

	POS pos = pResults->GetHeadPosition();
	while (pos != NULL)
	{
		CShortData *pData = (CShortData*)pResults->GetNext(pos);
		m_oReportBuffer.AppendEquation(pData->m_strID.GetString(), pData->m_strValue.GetString());
	}

	//AppendReport_ResultEx(pResultsEx);
}

void CVmMqttMacroTest::ResetParasByStateCount(long nStateCount)
{
	ResetParasByStateCount(&m_oFaultParas_Dvm, nStateCount);
	//ResetParasByStateCount(&m_oResults_Dvm, nStateCount);
}

void CVmMqttMacroTest::ResetParasByStateCount(CDataGroup *pParas, long nStateCount)
{
	long nStateNum = -1;
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	POS pos = pParas->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		CDataGroup *pGrp = (CDataGroup *)pObj;
		long nPos = pGrp->m_strID.Find(_T("state"));

		if (nPos != 0)
		{
			continue;
		}

		CString strID = pGrp->m_strID.Mid(nPos + 5);
		//对于6.3的StateTest6U6I功能，状态序列的ID是从1开始：state1、state2...
		//所以此处注释掉“+ 1”。防止删掉最后一个状态的结果数据。
		//这样，对于ID是从0开始的状态序列：state0、state1。会多出一个状态的结果数据。
		nStateNum = CString_To_long(strID)/* + 1*/; 

		if (nStateNum > nStateCount)
		{
			m_oResults_Dvm.DeleteByID(pGrp->m_strID);   //结果参数删除对应的参数
			pParas->Delete(pGrp);
		}
	}
}

void CVmMqttMacroTest::ResetParas_RsltEvalute()
{
	CDataGroup *pRlstEvalueGrp = (CDataGroup *)m_oFaultParas_Dvm.FindByID(_T("rslt_evaluation"));
	CDataGroup *pRlstEvalueGrpRslt = (CDataGroup *)m_oResults_Dvm.FindByID(_T("rslt_evaluation"));

	if (pRlstEvalueGrp == NULL)
	{
		return;
	}

	CDataGroup *pRsltEvasluteChild = NULL;
	POS pos = pRlstEvalueGrp->GetHeadPosition();
	CDvmData *pUseError = NULL;

	while (pos != NULL)
	{
		pRsltEvasluteChild = (CDataGroup *)pRlstEvalueGrp->GetNext(pos);
		pUseError = (CDvmData *)pRsltEvasluteChild->FindByID(_T("UseError"));

		if (pUseError == NULL)
		{
			continue;
		}

		if (CString_To_long(pUseError->m_strValue) == 0)
		{
			if (pRlstEvalueGrpRslt != NULL)
			{
				pRlstEvalueGrpRslt->DeleteByID(pRsltEvasluteChild->m_strID);
			}

			pRlstEvalueGrp->Delete(pRsltEvasluteChild);
		}
	}
}

//校准命令：adj-cmd
long CVmMqttMacroTest::Adjust_Adjust(const CString &strMacroID, CDataGroup *pParas, BOOL bDoEvents
											 ,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	return SendCmd_Adjust(strMacroID, pParas, STT_CMD_TYPE_ADJUST_Adjust);
}

long CVmMqttMacroTest::SendCmd_Adjust(const CString &strMacroID, CDataGroup *pParas, const CString &strCmdID)
{
	CSttAdjustCmd oAdjustCmd;
	CSttMqttTopicCmbn oTopicCmbn;

	oAdjustCmd.m_strID = _T("Adjust");;
	oAdjustCmd.SetParameter(strMacroID, pParas);

	InitTopicCmbn(oTopicCmbn, oAdjustCmd.m_strID, strCmdID);
	stt_mqtt_GetParasBuffer(&oAdjustCmd, oTopicCmbn);

	return g_theAtsOutMqttClient->PublicTopic(oTopicCmbn);
}

long CVmMqttMacroTest::SendCmd_Test(const CString &strMacroID, CDataGroup *pParas, const CString &strCmdID)
{
	CSttTestCmd oTestCmd;
	CSttMqttTopicCmbn oTopicCmbn;

	oTestCmd.m_strID = MQTT_CMD_ID_TestCmd;
	oTestCmd.SetParameter(strMacroID, pParas);

	InitTopicCmbn(oTopicCmbn, oTestCmd.m_strID, strCmdID);
	stt_mqtt_GetParasBuffer(&oTestCmd, oTopicCmbn);

	return g_theAtsOutMqttClient->PublicTopic(oTopicCmbn);
}


//////////////////////////////////////////////////////////////////////////
//
CVmMqttMacroTestCreator::CVmMqttMacroTestCreator()
{

}

CVmMqttMacroTestCreator::~CVmMqttMacroTestCreator()
{

}

CMacroTestEngineInterface* CVmMqttMacroTestCreator::CreateMacroTestEngine(const CString &strMacroFile)
{

	return NULL;
}

CMacroTestEngineInterface* CVmMqttMacroTestCreator::GetMacroTestEngine(const CString &strType, const CString &strProgID, const CString &strMacroFile)
{

	return NULL;
}

CMacroTestInterface* CVmMqttMacroTestCreator::GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps)
{
	CString strID;


	if (strType == _T("hd_res"))
	{
		strID = strType;
	}
	else
	{
		strID = strProgID;
	}

	CDataGroup *pTestApp = pTestApps->FindByDataType(strType);
	CString strBenchSN, strTestAppSN, strEngineMode, strEngineProgID2;

	if (pTestApp == NULL)
	{
		pTestApp = (CDataGroup *)pTestApps->FindByID(XPARA_ID_test_app);

		if (pTestApp == NULL)
		{
			pTestApp = pTestApps->FindByDataType(XPARA_ID_test_app);
		}
	}

	if (pTestApp != NULL)
	{//2023-8-23  lijunqing ID的特殊处理
		pTestApp->GetDataValue(STT_CMD_PARA_BenchSN, strBenchSN);
		pTestApp->GetDataValue(STT_CMD_PARA_DeviceSN, strTestAppSN);
		pTestApp->GetDataValue(STT_CMD_PARA_EngineMode, strEngineMode);
		pTestApp->GetDataValue(STT_CMD_PARA_EngineProgID, strEngineProgID2);
	}

	if (strBenchSN.GetLength() == 0)
	{
		if (g_strSmartTest_BenchSN != NULL)
		{
			strBenchSN = *g_strSmartTest_BenchSN;
		}
	}

	if (strTestAppSN.GetLength() > 0)
	{//2023-8-23  lijunqing ID的特殊处理
		strID = strTestAppSN;
	}

	if (strID.GetLength() == 0)
	{//2023-8-23  lijunqing ID的特殊处理
		strID = strEngineMode + strEngineProgID2 + strProgID;
	}

	CVmMqttMacroTest *pVmMqttMacroTest = (CVmMqttMacroTest*)SttFindByID(strID);

	if (pVmMqttMacroTest == NULL)
	{
		pVmMqttMacroTest = new CVmMqttMacroTest();
		BOOL bFirstCreate = FALSE;
		AddNewChild(pVmMqttMacroTest);
		pVmMqttMacroTest->m_strID = strID;
		pVmMqttMacroTest->m_strBenchSN = strBenchSN;
		pVmMqttMacroTest->m_strTestAppSN = strTestAppSN;

		pVmMqttMacroTest->MqttAddToClient();
	}

	return pVmMqttMacroTest;
}

void CVmMqttMacroTestCreator::InitMacroTestEngineShowSpyWnd()
{

}

void CVmMqttMacroTestCreator::ReleaseMacroTestEngine()
{
	POS pos = GetHeadPosition();
	CVmMqttMacroTest *pVmMqttMacroTest = NULL;

	while (pos != NULL)
	{
		pVmMqttMacroTest = (CVmMqttMacroTest *)GetNext(pos);
		pVmMqttMacroTest->CloseDevice();
	}

	DeleteAll();
}

void CVmMqttMacroTestCreator::ReleaseMacroTestEngine(const CString &strProgID)
{
	CVmMqttMacroTest *pMacroTest = (CVmMqttMacroTest*)SttFindByID(strProgID);

	if (pMacroTest != NULL)
	{
		pMacroTest->CloseDevice();
		Delete(pMacroTest);
	}
}

void CVmMqttMacroTestCreator::ShowSpyWnd()
{

}

void CVmMqttMacroTestCreator::ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara)
{

}

long CVmMqttMacroTestCreator::ConfigEngine(const CString &strMacroFile, const CString &strIP)
{
	return 0;
}

long CVmMqttMacroTestCreator::AttatchLogWnd(unsigned long hWnd)
{
// 	POS pos = GetHeadPosition();
// 	CVmMqttMacroTest *pVmMqttMacroTest = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pVmMqttMacroTest = (CVmMqttMacroTest *)GetNext(pos);
// 		pVmMqttMacroTest->AttatchLogWnd(hWnd);
// 	}

	m_hLogWnd = hWnd;

	return 0;
}
