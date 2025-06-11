#include "stdafx.h"
#include "SmartTestBaseApp.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "../../Module/API/GloblaDrawFunctions.h"
#include "../../Module/API/FileApi.h"

#include "../AutoTestXMLRWKeys.h"
#include "../../Module/API/SingleAppMutexApi.h"

#include "../XLanguageResourceAts.h"
#include "../GuideBook/GuideBookTool.h"
#include "../GuideBook/Script/GbScriptFunctions.h"

#include "../Module/SmartTestInterface/MacroTestFactory.h"
#include "../Module/SmartTestInterface/ProtocolEngineFactory.h"
#include "../../Module/API/GloblaDrawFunctions.h"
#include "../../Module/TestMacro/TestMacrosFileMngr.h"

#include "TestControlBase.h"

#ifndef _PSX_IDE_QT_
//2020-12-22  lijunqing  通信配置入口
#include "..\..\..\Protocol\Module\PpDeviceModelEditInterface\PpDeviceModelEditInterface.h"
#endif

#ifndef _PSX_IDE_QT_
#include "../RecorderPpEngine.h"
#endif

#include "../Module/UI/Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "../Module/Engine/SttNativeTestEngine.h"
#include "../Module/SttTestAppConfig/SttTestAppCfg.h"
#include "../Module/Engine/SttNativeTestEngine_Mqtt.h"
#include "../Module/SmartTestInterface/AtsOutInterfaceMqttClient.h"
#include "../Module/SttCmd/GuideBook/SttCmdGuideBookTransTool.h"
#include "../Module/SttAtsSvr/XSttSmartTestPAL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString g_strRcdFilePathRoot;
BOOL g_bCreateTestTimesDir = 0;

//2023-8-22 李俊庆  自动测试端，全局唯一的BenchSN
CString *g_strSmartTest_BenchSN = NULL;
CString *g_strMacroID = NULL;
//shaolei   2024-3-14  PowerTest7.0软件中，对于合并单元等测试，不能校验软件狗。采用配置相关的功能ID
CValues *g_pMacrosCfg = NULL;

//////////////////////////////////////////////////////////////////////////
//
CSmartTestBaseApp *g_theSmartTestBaseApp = NULL;
CRptFillAppBase *g_theRptFillApp = NULL;

CSmartTestBaseApp::CSmartTestBaseApp()
{
	g_theSmartTestBaseApp = this;
#ifndef _PSX_QT_LINUX_
	m_pKeyDB = NULL;
#endif
	m_pSystemConfig = new CTCtrlSystemConfig;

	CTCtrlCntrWorkSpace::Create();
	ASSERT(CTCtrlCntrWorkSpace::g_pWorkSpace != NULL);

	CAutoTestXMLRWKeys::Create();
	ASSERT(CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	m_pRptFillAppBase = NULL;

	m_hMacroTestLogWnd = NULL;
	m_hPpEngineLogWnd = NULL;

	m_nSvr_MQTT = 0;      //是否启动MQTT服务
	m_nSvr_STT = 0;      //是否启动MQTT服务
	m_nSmartTestServer = 0;  //自动测试智能服务
	//m_strAtsServiceSN = _T("AtsService");
	m_strBentchSN = _T("AtsPonovo");
	//m_strBentchSN = _T("test");   //TDM：暂时固定为test
	m_nSttCmdFormat = _PUGI_XML_TYPE_;
	m_nStartTestAfterCreate = 0;
    m_oRecorder = NULL;
}

CSmartTestBaseApp::~CSmartTestBaseApp()
{
	CTCtrlCntrWorkSpace::Release();
	CAutoTestXMLRWKeys::Release();

	if (m_pSystemConfig != NULL)
	{
		delete m_pSystemConfig;
		m_pSystemConfig = NULL;
	}

	if (m_pRptFillAppBase != NULL)
	{
		delete m_pRptFillAppBase;
		m_pRptFillAppBase = NULL;
	}

	if (g_pMacrosCfg != NULL)
	{
		delete g_pMacrosCfg;
		g_pMacrosCfg = NULL;
	}
}

void CSmartTestBaseApp::ReleaseMacroTestEngine()
{
	CMacroTestFactory::ReleaseMacroTestEngine();
}

void CSmartTestBaseApp::InitMacroTestEngineShowSpyWnd()
{
	CMacroTestFactory::InitMacroTestEngineShowSpyWnd();
}


void CSmartTestBaseApp::ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara)
{
	CMacroTestFactory::ExecuteMtCmd(strCmdID, strCmdPara);
}

void CSmartTestBaseApp::CreateMacroTestEngine(const CString &strMacroFile)
{
	CMacroTestFactory::CreateMacroTestEngine(strMacroFile);
}

void CSmartTestBaseApp::InitPpEngineShowSpyWnd()
{
	CProtocolEngineFactory::InitPpEngineShowSpyWnd();
}

void CSmartTestBaseApp::StopProtocolParseForReadSoe(BOOL bStop)
{
	if (m_pCtrlCntrConfig->IsStopProtocolParseWhileReadSoe())
	{
		CProtocolEngineFactory::StopProtocolParseForReadSoe(bStop);
	}
}

BOOL CSmartTestBaseApp::Is_UsePowerTestTrans()
{
	return TRUE;	
}

/*
void CSmartTestBaseApp::CreateReportApp()
{
	if(m_pCtrlCntrConfig->IsReportControlWPS())
	{
		CreateApp(CRptFillWPSApp::New);
	}
	else
	{
		CreateApp(CRptFillWordApp::New);
	}
}
*/

void CSmartTestBaseApp::CreateApp(PFUNC_RPTFILLAPP_CREATE pCreateFunc)
{
	if (m_pRptFillAppBase != NULL)
	{
		return;
	}

	m_pRptFillAppBase = pCreateFunc();
	g_theRptFillApp = m_pRptFillAppBase;
}

/*
	初始化：在应用程序App的COM环境初始化之后调用
	过程：	初始化m_oSystemConfig
						初始化m_oTCtrlCntrConfig
						初始化m_oTestTasks
						初始化m_oTCtrlCntrWorkspace
*/
long CSmartTestBaseApp::InitSmartTestBaseApp()
{
    CGbXMLKeys::CreatetGbXMLkeys();
    CScriptTextMngrGlobalPool::Create();

    m_pCtrlCntrConfig = CTCtrlCntrConfig::Create();


    //测试功能数据接口
	TM_CreateTestMacros();
	CTestMacrosFileMngr::Create();

	m_pSystemConfig->Init();
	//m_pCtrlCntrConfig->Open();
	CTCtrlCntrWorkSpace::g_pWorkSpace->Open();

	//初始化数据类型   ?????????????????????????  有内存泄露  2021-8-5  lijunqing
	CGbDataTypeMngr::Create();

	//KeyDB  2013.4.15
#ifndef _PSX_QT_LINUX_
    CKeyDbXmlRWKeys::Create();
	m_pKeyDB = new CXKeyDB();
	m_pKeyDB->OpenKeyDbFile(_T(""), TRUE);
#endif

	//CCharacteristicXmlRWKeys::Create();
	//初始化测试任务文件管理对象
	CString strWorkSpacePath;
	strWorkSpacePath = GetWorkSpacePath();

	CReportTemplateConfigXmlRWKeys::Create();
	m_oReportTemplateConfig.OpenReportTemplateConfigFile();

	CGuideBookTool::Create();


	//初始化脚本
	//Gb_InitScrpitEngine();

	CMacroTestFactory::Create();
	CProtocolEngineFactory::Create();
    CGbParaTypeMngr::Create();
    CCfgDataMngrConstGlobal::Create();

	return 1;
}

void CSmartTestBaseApp::InitRecorder(CTestControlBase *pTestControl)
{
#ifndef _PSX_IDE_QT_
    if (!HasRecorder())
	{
		return;
	}

	if (m_oRecorder != NULL)
	{
		if (m_oRecorder->m_strRecordProgID == g_strRecorderPpEngineProgID)
		{
			CRecorderPpEngine *p = (CRecorderPpEngine*)m_oRecorder;
			p->m_pTestControl = pTestControl;
		}

		return;
	}

	if (m_pCtrlCntrConfig->m_strRecordProgID == g_strRecorderPpEngineProgID)
	{
		CRecorderPpEngine *pNew = new CRecorderPpEngine();
		pNew->CreateCrecorder(m_pCtrlCntrConfig->m_strRecordProgID);
		pNew->m_pTestControl = pTestControl;
		m_oRecorder = pNew;
	}

	if (m_oRecorder == NULL)
	{
		CreateNewRecorder();
	}

#endif
}

void CSmartTestBaseApp::ReleaseRecorder()
{
	if (m_pCtrlCntrConfig == NULL)
	{
		return;
	}

	if (!HasRecorder())
	{
		return;
	}

	try
	{
		if (m_oRecorder != NULL)
		{
			m_oRecorder->Quit();
			delete m_oRecorder;
			m_oRecorder = NULL;
		}
	}
	catch (...)
	{
		TRACE("catch error-----");
	}

	m_oRecorder = NULL;
}

void CSmartTestBaseApp::SetRecorderProgID(const CString &strProgID)	
{	
	if (m_oRecorder != NULL)
	{
		if (m_oRecorder->m_strRecordProgID != strProgID)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Warning : Record [%s] is Running! Set Record ProgID [%s]")
                , m_oRecorder->m_strRecordProgID.GetString(), strProgID.GetString());
		}
	}

	return m_pCtrlCntrConfig->SetRecorderProgID(strProgID);	
}

CString CSmartTestBaseApp::GetWorkSpacePath()
{
	CString strWorkSpacePath;
	strWorkSpacePath = m_pCtrlCntrConfig->m_strWorkSpacePath;

	if (IsFileExist(strWorkSpacePath))
	{

	}
	else
	{
		strWorkSpacePath = g_strTCtrlCntrWorkspacePath;
	}

	return strWorkSpacePath;
}

/*
	释放测试环境：在应用程序的ExitInstance中调用
	一定要在ExitInstance中调用，否则应用程序会因释放环境顺序问题导致错误
*/
long CSmartTestBaseApp::ExitSmartTestBaseApp()
{
	StopSvr();
	if(m_pCtrlCntrConfig != NULL)
	{
		CTCtrlCntrConfig::Release();
		m_pCtrlCntrConfig = NULL;
	}

	if(m_pSystemConfig != NULL)
	{
		delete m_pSystemConfig;
		m_pSystemConfig = NULL;
	}

	CAutoTestXMLRWKeys::Release();
	CTCtrlCntrWorkSpace::Release();

	TM_ReleaseTestMacros();
	//ReleaseMacroTestEngine();   //use ReleaseConfig();  //2020-12-23  lijunqing

    //初始化数据类型
	CGbDataTypeMngr::Release();

#ifndef _PSX_QT_LINUX_
    ReleaseSingleAppMutex();
#endif

	//脚本
	//Gb_CloseScrpitEngine();
	//ReleasePpEngine();  //use ReleaseConfig();  //2020-12-23  lijunqing
	ReleaseConfig();  //2020-12-23  lijunqing

#ifndef _PSX_QT_LINUX_
    CKeyDbXmlRWKeys::Release();
#endif

	//CCharacteristicXmlRWKeys::Release();
	CReportTemplateConfigXmlRWKeys::Release();

	CGuideBookTool::Release();

	CTestMacrosFileMngr::Release();

	try
	{
		if (m_pRptFillAppBase != NULL)
		{
			m_pRptFillAppBase->CloseApplication();
		}
	}
	catch (...) 
	{
		TRACE("catch error-----");
	}

	if (m_oRecorder != NULL)
    {
		delete m_oRecorder;
		m_oRecorder = NULL;
	}

	CMacroTestFactory::Release();
	CProtocolEngineFactory::Release();
    CGbXMLKeys::Release();
    CScriptTextMngrGlobalPool::Release();
    CGbParaTypeMngr::Release();
     CCfgDataMngrConstGlobal::Release();

//2020-12-22  lijunqing  通信配置
#ifndef _PSX_IDE_QT_
	ReleasePpDeviceEditLib();
#endif

#ifndef _PSX_QT_LINUX_
	if (m_pKeyDB != NULL)
	{
		delete m_pKeyDB;
		m_pKeyDB = NULL;
	}
#endif

	return 0;
}

CProtocolEngineInterface* CSmartTestBaseApp::GetPpEngine(const CString &strEngineMode, const CString &strProgID)
{
	CProtocolEngineFactory::AttatchLogWnd(m_hPpEngineLogWnd);
	CProtocolEngineInterface *pPpEngine = CProtocolEngineFactory::GetProtocolEngine(strEngineMode, strProgID);

	return pPpEngine;
}

BOOL CSmartTestBaseApp::HasPpEngine()
{
	return CProtocolEngineFactory::HasPpEngine();
}

void CSmartTestBaseApp::ReleasePpEngine(const CString &strProgID)
{
	CProtocolEngineFactory::ReleasePpEngine(strProgID);
}

void CSmartTestBaseApp::ReleasePpEngine()
{
	CProtocolEngineFactory::ReleasePpEngine();

#ifndef _PSX_IDE_QT_
	if (IsProgramExist(g_strPpMmsEngineExeName))
	{
		TerminateProgram(g_strPpMmsEngineExeName);
	}

	if (IsProgramExist(g_strPpEngineExeName))
	{
		TerminateProgram(g_strPpEngineExeName);
	}
#endif
}

CMacroTestInterface* CSmartTestBaseApp::GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps)
{
	CMacroTestFactory::AttatchLogWnd(m_hMacroTestLogWnd);
	return CMacroTestFactory::GetMacroTest(strType, strProgID, strMacroFile, pTestApps);
}

CString CSmartTestBaseApp::GetPpTemplateFilePath()
{
	CString strPath;
	strPath = _P_GetInstallPath();

// 	if (strPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
// 	{
// 		strPath = strPath.Left(strPath.GetLength()-1);
// 	}
// 
// 	long nPos = strPath.ReverseFind('\\');
// 	strPath = strPath.Left(nPos+1);
    strPath.AppendFormat(_T("%s\\"), m_pCtrlCntrConfig->m_strProtocolPath.GetString());
	
	return strPath;
}

//2020-12-22  lijunqing   for 简化版本
void CSmartTestBaseApp::ConfigTestApp(const CString &strProgID, const CString &strIP)
{
	if (m_strOldProgID_TestEngine != strProgID)
	{
		ReleaseMacroTestEngine();
		m_strOldProgID_TestEngine = strProgID;
	}

	CreateMacroTestEngine(strProgID);
	CMacroTestFactory::ConfigMacroTestEngine(strProgID, strIP);
}
/*
//2020-12-22  lijunqing  通信配置
#ifndef _PSX_QT_LINUX_

BOOL ppcfg_PpEngine(const CString &strProgID, const CString &strDvmFile)
{
	if (strProgID != g_strPpEngineProgID)
	{
		return FALSE;
	}

	if (g_hPpDeviceModelEditLib == NULL)
	{
		CString strPpBinPath = atssys_GetProtocolPath();
		strPpBinPath += _T("Bin\\");

		if (!LoadPpDeviceEditLib(strPpBinPath))
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Load Protocol Config DLL Failed!"));
			return TRUE;
		}
	}

	if (Pp_InstallLog != NULL)
	{
		Pp_InstallLog(CLogPrint::GetLog());
	}

	CString strCmmCfgFile = pp_GetDeviceCmmCfgFile(strDvmFile);
	char *pszFile = NULL;
	CString_to_char(strCmmCfgFile, &pszFile);
	LONG nRet = Pp_EditDeviceCmmConfigFile(pszFile, NULL, CRect (0, 0, 0, 0));
	delete pszFile;

	if (Pp_UnInstallLog != NULL)
	{
		Pp_UnInstallLog();
	}

	return TRUE;
}

#endif
*/

//2023-8-22
//此函数是创建的时候调用，目前默认为只支持COM
void CSmartTestBaseApp::ConfigTestDevice(const CString &strProgID, const CString &strDvmFile)
{
	//2020-12-22  lijunqing  通信配置
#ifndef _PSX_IDE_QT_

	if (m_strOldProgID_PpEngine != strProgID)
	{
		ReleasePpEngine();
		m_strOldProgID_PpEngine = strProgID;
	}

	if (ppcfg_PpEngine(strProgID, strDvmFile))
	{
		return ;
	}

	CProtocolEngineInterface *pEngine = GetPpEngine(_T(""), strProgID);

	if (pEngine == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Create Protocol Engine [%s] Failed!"), strProgID);
	}
	else
	{
		long nRet = pEngine->ConfigEngine(strDvmFile);

		if (nRet == 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("联机失败[%s]"), strProgID);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("联机成功[%s]"), strProgID);
		}
	}

#endif
	
}

void CSmartTestBaseApp::ReleaseConfig()
{
	//2020-12-23  lijunqing  通信配置
#ifndef _PSX_QT_LINUX_
	ReleasePpEngine();
	ReleaseMacroTestEngine();

	m_strOldProgID_PpEngine.Empty();
	m_strOldProgID_TestEngine.Empty();
#endif
}

//////////////////////////////////////////////////////////////////////////
//自动测试相关的服务  2023-8-15  lijunqing
void CSmartTestBaseApp::ProcessShellCmd(const CString &strCmdLine, CWnd *pMainWnd)
{
	if (strCmdLine.GetLength() > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("解析到命令行参数：【%s】"), strCmdLine.GetString());
	}
	
	CEquationBuffer oEquation;
	oEquation.SetSeparateChar(':');
	oEquation.SetSeparateEndChar(';');
	oEquation.InitBuffer(strCmdLine);
	long nCmdCount = 0;
	POS pos = oEquation.GetHeadPosition();
	CEquationKey *pKey = 0;
    CString strKeyName, strKeyValue;

	while (pos != NULL)
	{
		pKey = (CEquationKey *)oEquation.GetNext(pos);
        strKeyName = pKey->GetKeyName();
        strKeyValue = pKey->GetKeyValue();
        nCmdCount += ProcessShellCmd_Key(strKeyName, strKeyValue);
	}

	if (nCmdCount > 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CmdLine Error"));
	}

	if (m_pCtrlCntrConfig->m_nUseSttAtsSvr == 1)
	{
		m_nSmartTestServer = 1;
		m_nSvr_STT = 1;
#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
		m_nSvr_MQTT = 1;
#endif
	}

	OnShellCmd(pMainWnd);
}

long CSmartTestBaseApp::ProcessShellCmd_Key(CString &strID, CString &strValue)
{
	strID.MakeLower();

	if (strID == _T("open_gbrpt") || strID == _T("createtest") || strID == _T("retest") || strID == _T("exportreport") )
	{
		m_strCmdID = strID;
		m_strCmdFile = strValue;
		return 1;
	}
	else if (strID == _T("mqtt"))
	{
		m_nSvr_MQTT = CString_To_long(strValue);
	}
	else if (strID == _T("stt"))
	{
		m_nSvr_STT = CString_To_long(strValue);
	}
	else if (strID == _T("smarttestserver"))
	{
		m_nSmartTestServer = CString_To_long(strValue);
	}
	else if (strID == _T("benchsn"))
	{
		m_strBentchSN = strValue;
	}
	else if (strID == _T("devicesn"))
	{
		m_strDeviceSN = strValue;
	}
	else if (strID == _T("servicesn"))
	{
		m_strAtsServiceSN = strValue;
	}
	else if (strID == _T("starttestaftercreate"))
	{
		m_nStartTestAfterCreate = CString_To_long(strValue);
	}
	else if (strID == _T("cmdformat"))
	{
		m_nSttCmdFormat = text_GetFormatIndex(strValue);
	}
	else if (strID == _T("retgbdetail"))
	{
		long nRet = CString_To_long(strValue);

		if (nRet == 0)
		{
			CSttCmdGuideBookTransTool::g_bOnlyItemsTree = TRUE;
		}
		else
		{
			CSttCmdGuideBookTransTool::g_bOnlyItemsTree = FALSE;
		}
	}
	else if (strID == _T("macroid"))
	{
		m_strMacroID = strValue;
		g_strMacroID = &m_strMacroID;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CmdLineKey [%s][%s] error"), strID.GetString(), strValue.GetString());
	}

	return 0;
}

void CSmartTestBaseApp::OnShellCmd(CWnd *pMainWnd)
{
	if (m_strBentchSN.GetLength() > 0)
	{
	g_strSmartTest_BenchSN = &m_strBentchSN;
	}
	else
	{
		g_strSmartTest_BenchSN = &m_strDeviceSN;
	}

	StartSvr_CreateSttSmartTest();
	StartSvr_MQTT();
	StartSvr_STT();
	StartSvr_SmartTestServer();
	SetMainWnd(pMainWnd);

	//启动服务后，要先连接客户端。否则createtest、exportreport等指令执行结束后，无法返回应答
	if (m_nSvr_MQTT)
	{
		if (g_theAtsOutMqttClient != NULL)
		{
			g_theAtsOutMqttClient->Connect(m_strBentchSN);
			CSttNativeTestEngine_Mqtt *pMqtt = CSttNativeTestEngine_Mqtt::GetNativeTestEngine();
			pMqtt->InitMqttTopicCmbn(m_strAtsServiceSN, m_strBentchSN);
			pMqtt->SetXmlRwType(m_nSttCmdFormat);
			g_theAtsOutMqttClient->MqttAdd(pMqtt);
		}
	}

	if (m_strCmdID == _T("open_gbrpt") )
	{
		OnShellCmd_open_gbrpt();
	}
	else if (m_strCmdID == _T("createtest") )
	{
		OnShellCmd_CreateTest();
	}
	else if (m_strCmdID == _T("retest") )
	{
		OnShellCmd_ReTest();
	}
	else if (m_strCmdID == _T("exportreport") )
	{
		OnShellCmd_ExportReport();
	}
}

void CSmartTestBaseApp::SetMainWnd(CWnd *pWnd)
{
	if (g_theSttSmartTest/*CXSmartTestEntry::g_pXSttSmartTestEntry*/ == NULL)
	{
		return;
	}

	g_theSttSmartTest/*CXSmartTestEntry::g_pXSttSmartTestEntry*/->InitTestControlMainWnd(pWnd);
}

BOOL CSmartTestBaseApp::IsSmartTestRpc()
{
	if (m_strCmdID == _T("exportreport") )
	{
		return TRUE;
	}

	if (m_strCmdID == _T("createtest") )
	{
		return TRUE;
	}

	return FALSE;
}

void CSmartTestBaseApp::StopSvr()
{
	if (m_nSvr_MQTT > 0)
	{
		CSttNativeTestEngine_Mqtt::Release();
	}

	if (m_nSvr_STT > 0)
	{
		CSttNativeTestEngine::Release();
	}

	if (m_nSmartTestServer > 0)
	{
		if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_strSttAtsSvrScene == STT_ATS_SVR_SCENE_PAL)
		{
            //CXSmartTestPAL::Release();
		}
		else
		{
			CXSmartTestEntry::Release();
		}

		CSttMacroTestUI_TestMacroUIDB::Release();
	}
}

void CSmartTestBaseApp::StartSvr_CreateSttSmartTest()
{
	if (m_nSmartTestServer <= 0)
	{
		return;
	}

	if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_strSttAtsSvrScene == STT_ATS_SVR_SCENE_PAL)
	{
		//CXSmartTestPAL::Create();
	}
	else
	{
		CXSmartTestEntry::Create();
	}

	CSttMacroTestUI_TestMacroUIDB::Create();
}

void CSmartTestBaseApp::StartSvr_SmartTestServer()
{
	if (m_nSmartTestServer <= 0)
	{
		return;
	}

// 	if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_strSttAtsSvrScene == STT_ATS_SVR_SCENE_PAL)
// 	{
//         //CXSmartTestPAL::Create();
// 	}
// 	else
// 	{
// 		CXSmartTestEntry::Create();
// 	}
	
	if (g_theSttSmartTest == NULL)
	{
		return;
	}

	g_theSttSmartTest/*CXSmartTestEntry::g_pXSttSmartTestEntry*/->InitTestControl(true);
	g_theSttSmartTest/*CXSmartTestEntry::g_pXSttSmartTestEntry*/->InitTestControlMainWnd(NULL);
	g_theSttSmartTest/*CXSmartTestEntry::g_pXSttSmartTestEntry*/->SetStartTestAfterCreate(m_nStartTestAfterCreate);
}

void CSmartTestBaseApp::StartSvr_MQTT()
{
	if (m_nSvr_MQTT <= 0)
	{
		return;
	}

	CSttNativeTestEngine_Mqtt *pEngine = NULL;

	if (m_strBentchSN.GetLength() > 0)
	{
		pEngine = CSttNativeTestEngine_Mqtt::Create(m_strBentchSN, g_theSttSmartTest/*CXSmartTestEntry::g_pXSttSmartTestEntry*/);
	}
	else
	{
		pEngine = CSttNativeTestEngine_Mqtt::Create(m_strBentchSN, g_theSttSmartTest/*CXSmartTestEntry::g_pXSttSmartTestEntry*/);
	}
}

void CSmartTestBaseApp::StartSvr_STT()
{
	if (m_nSvr_STT <= 0)
	{
		return;
	}

	CSttNativeTestEngine::Create(_T("SmartTestServerConfig.xml"), g_theSttSmartTest/*CXSmartTestEntry::g_pXSttSmartTestEntry*/);
}

void CSmartTestBaseApp::OnShellCmd_open_gbrpt()
{

}

void CSmartTestBaseApp::OnShellCmd_CreateTest()
{

}

void CSmartTestBaseApp::OnShellCmd_ReTest()
{


}

void CSmartTestBaseApp::OnShellCmd_ExportReport()
{

}

void CSmartTestBaseApp::SetXmlRwType(long nType)
{
	if (m_nSvr_MQTT)
	{
		CSttNativeTestEngine_Mqtt *pEngine = CSttNativeTestEngine_Mqtt::GetNativeTestEngine();
		pEngine->SetXmlRwType(nType);
	}

	if (m_nSvr_STT)
	{
		//没找到对应的m_mXmlRWType。暂不处理
	}
}

CString CSmartTestBaseApp::GetCmdFilePath(long nMode)
{
	CString strPath;  //带路径的

	if (m_strCmdFile.Find('\\') >= 0 || m_strCmdFile.Find('/') >= 0)
	{//为文件路径，兼容windows和linux
		strPath = m_strCmdFile;
	}
	else
	{
		strPath = _P_GetDBPath();
		strPath += m_strCmdFile;
	}

	return strPath;
}

CSttAtsCmd* CSmartTestBaseApp::OpenCmdFile()
{
	CString strPath;  //带路径的
	strPath = GetCmdFilePath(0);

	CSttAtsCmd *pAtsCmd = new CSttAtsCmd();
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	pAtsCmd->OpenXmlFile(strPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	return pAtsCmd;
}

long CSmartTestBaseApp::GetXmlRwType()
{
	if (m_nSvr_MQTT)
	{
		CSttNativeTestEngine_Mqtt *pEngine = CSttNativeTestEngine_Mqtt::GetNativeTestEngine();
		return pEngine->GetXmlRwType();
	}

	if (m_nSvr_STT)
	{
		//没找到对应的m_mXmlRWType。暂时默认_PUGI_XML_TYPE_
		return _PUGI_XML_TYPE_;
	}

	return _PUGI_XML_TYPE_;
}

//////////////////////////////////////////////////////////////////////////
COLORREF TCC_GetItemStateColor(CGbItemBase *pItem, BOOL bEnable)
{
	CSmartTestBaseApp* pApp = g_theSmartTestBaseApp;
	COLORREF color;
	int nItemState = pItem->GetState();
	CTCtrlCntrConfig *pCtrlCntrCfg = pApp->GetCntrConfig();

	if (!bEnable)
	{
		return pCtrlCntrCfg->m_crProhibit;
	}

	switch(nItemState)
	{
	case TEST_STATE_NORMAL:
		color = pCtrlCntrCfg->m_crNormal;
		break;
	case TEST_STATE_TESTING:
		color = pCtrlCntrCfg->m_crTesting;
		break;
	case TEST_STATE_ELIGIBLE:
		color = pCtrlCntrCfg->m_crEligible;
		break;
	case TEST_STATE_STOPED:
		color = pCtrlCntrCfg->m_crStopped;
		break;
	case TEST_STATE_INLEGIBLE:
		color = pCtrlCntrCfg->m_crInlegible;
		break;
	case TEST_STATE_SKIP:
		color = pCtrlCntrCfg->m_crInlegible;
		break;
		//	case g_nNotStandard:
		//		color = pCtrlCntrCfg->m_crNotStandard;
		//		break;
	default:
		color = RGB(0,0,0);
		break;
	}

	//取消选择的项目、项目Enable==0
	if (pItem->m_nSelect == 0 || pItem->m_nEnable == 0)
	{
		color = pCtrlCntrCfg->m_crProhibit;
	}

	return color;
}


void Init_ShowTestWndTop(BOOL bMinimize)
{
	if ( CTCtrlCntrConfig::g_pTCtrlCntrConfig->Is_TestWndMode_HideWhenMinize())
	{
		if (bMinimize)
		{
			g_bShowTestWndTop = FALSE;
		}
		else
		{
			g_bShowTestWndTop = TRUE;
		}
	}
	else
	{
		g_bShowTestWndTop = TRUE;
	}

	g_theSmartTestBaseApp->InitMacroTestEngineShowSpyWnd();
	g_theSmartTestBaseApp->InitPpEngineShowSpyWnd();
}
