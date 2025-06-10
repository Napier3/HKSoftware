#include "SttTestAppBase.h"

#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"
#include "../UI/Config/Frame/SttFrameConfig.h"
#include "../UI/Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "../SttTestBase/SttMacroXmlKeys.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"
#include "../SttSystemConfig/SttSystemConfig.h"
#include "../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../../61850/Module/SCL/SclFileMngr/SclFileMngrGlobal.h"
#include "../UI/SttTestCntrCmdDefine.h"
#include "../../../61850/Module/XLanguageResourcePp_Mms.h"


#ifdef _PSX_QT_LINUX_
#include "../RecordTest/RingMemBufShm.h"
//#endif
#else
#include "../RecordTest/RingMemBufShmDebug.h"
#include "../RecordTest/QT/RingMemBufShmDebugWidget.h"

QRingMemBufShmDebugWidget *g_pRingMemBufShmDebugWidget = NULL;

#endif

#include "../RecordTest/QT/SttLocalRcdMemBufferMngrLinux.h"
#include "../../Module/SmartCap/SmartCapCtrl.h"
#include "../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../AutoTest/Module/Characteristic/CharacteristicGlobal.h"

#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdAi/GbWzdAiTool.h"
#include "../TestUI/Module/SttTestGridDefine/SttTestGridDefineGlobal.h"

CSttTestAppBase *g_pTheSttTestApp = NULL;
long g_nLogDebugInfor = 0;


//2022-4-7  lijunqing 不同的产品，使用的方式是不同的，例如：AT02D使用分配内存方式
//330使用共享内存方式，所以缓冲区在各工程的Main中创建，以保证通用性
CSttRcdBufferRcvMsg *g_pSttRcdSndRingBuf;

#define _use_g_theIotEngineApp_
//2022-11-12  lijunqing
#include "../SmartTestInterface/QT/PpSttIotEngineClientWidget.h"
#include "../UI/Controls/SafetyMsgCfg/SttSafetyMsgCfgGlobal.h"
#include "../../../61850/Module/61850ClientConfig/61850ClientCfgMngrGlobal.h"
#include "../../../AutoTest/Module/TestMacroRptTemplate/TestMacroRptTemplateGlobal.h"
extern CPpSttIotEngineClientApp *g_theIotEngineApp;


CSttTestAppBase::CSttTestAppBase()
{
   g_pTheSttTestApp = this;
   m_pTestCtrlCntr = NULL;
   m_pKeyDB = NULL;

   m_pDvmDevice = NULL;  //2023-2-21  lijunqing  被测装置的设备数据模型
}

CSttTestAppBase::~CSttTestAppBase()
{
	if (m_pKeyDB != NULL)
	{
		delete m_pKeyDB;
		m_pKeyDB = NULL;
	}

	if (m_pDvmDevice != NULL)
	{

	}
}

//#include <QtWebKit>

#ifndef _PSX_QT_LINUX_
#include "../../Module/XMinidmp/XMinidmp.h"
#endif

void CSttTestAppBase::InitSttTestApp(CXLanguageResourceBase *pLanguage)
{
	_P_InitSystemPath();
#ifndef _PSX_QT_LINUX_
	RunCrashHandler();
#endif
#ifdef _PSX_OS_CENTOS_
    StartSmartTest();
#endif
	CXLanguageXmlRWKeys::Create();
	CXLanguageMngr::Create(pLanguage, TRUE);

	CXLanguageMngr::xlang_AddXLanguageRerouce(new CXLanguageResourcePp_Mms(), TRUE);

#ifndef NOT_USE_XLANGUAGE
	((CSttAdjSysParaDataTypes*)g_pSttAdjSysParaDataTypes)->InitAdjSysParaDataTypes();
#endif

	CSttSystemConfigXmlRWKeys::Create();
	CMacroXmlKeys::Create();
	CDataMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CTestDataTypeMngrConstGlobal::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CCfgDataMngrConstGlobal::Create();
	CDeviceModelXmlKeys::Create();
	CSttMacroTestUI_TestMacroUIDB::Create();
	CSttCmdOverTimeTool::Create();
	CSclFileMngrXmlRWKeys::Create();

	CCharacteristicXmlRWKeys::Create();
	CKeyDbXmlRWKeys::Create();
	CTestMacroXmlRWKeys::Create();
	CSttSafetyMsgCfgXmlRWKeys::Create();
	C61850ClientCfgMngrXmlRWKeys::Create();
	CTestMacroRptTemplateXmlRWKeys::Create();

	CSttTestGridDefineXmlRWKeys::Create();
// 	QWebSettings::setMaximumPagesInCache(0);
// 	QWebSettings::setObjectCacheCapacities(0, 0, 0);
// 	QWebSettings::setOfflineStorageDefaultQuota(0);
// 	QWebSettings::setOfflineWebApplicationCacheQuota(0);

#ifdef _use_g_theIotEngineApp_
	//2022-11-12  lijunqing  通信客户端
	g_theIotEngineApp = new CPpSttIotEngineClientApp();
	g_theIotEngineApp->InitPpSttIotEngineClientApp();
	//Create_PpSttIotEngineDebugWidget();
#endif
}

//2023-03-01 lijunqing 为了提高程序启动速度，和通信相关的，打开通信界面的时候在启动初始化
void CSttTestAppBase::IinitGbWzdAiTool()
{
	if (g_theGbWzdAiTool != NULL)
	{
		return;
	}

	InitKeyDB();

	//2023-2-23  lijunqing
	Create_GbWzdAiTool();  //可以考虑状态序列、谐波、手动等模块。不创建自动识别的部分
	g_theGbWzdAiTool->SetXKeyDB(m_pKeyDB);
	OpenPpSttCommConfigFile();

}

void CSttTestAppBase::ExitSttTestApp()
{
	if (m_pTestCtrlCntr != NULL)
	{
		delete m_pTestCtrlCntr;
		m_pTestCtrlCntr = NULL;
	}

	CSttTestGridDefineXmlRWKeys::Release();
	CTestMacroRptTemplateXmlRWKeys::Release();
	C61850ClientCfgMngrXmlRWKeys::Release();
	CSttSafetyMsgCfgXmlRWKeys::Release();
	CTestMacroXmlRWKeys::Release();
	CSclFileMngrXmlRWKeys::Release();
	CCfgDataMngrConstGlobal::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CTestDataTypeMngrConstGlobal::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CMacroXmlKeys::Release();
	CDeviceModelXmlKeys::Release();
	CSttMacroTestUI_TestMacroUIDB::Release();
	CSttSystemConfigXmlRWKeys::Release();

	CXLanguageMngr::Release();
	CXLanguageXmlRWKeys::Release();
	CSttCmdOverTimeTool::Release();
	CKeyDbXmlRWKeys::Release();
	CCharacteristicXmlRWKeys::Release();

#ifndef _PSX_QT_LINUX_
    ExitSmartTest();
	ExitIotProtoServer();
#endif

#ifdef _PSX_OS_CENTOS_
    ExitSmartTest();
#endif

	if (g_theSmartCapCtrl != NULL)
	{
		ExitSttIecRecord();
	}

	//2022-11-12  lijunqing  通信客户端
#ifdef _use_g_theIotEngineApp_
	//Release_PpSttIotEngineDebugWidget();

	if (g_theIotEngineApp)
	{
		g_theIotEngineApp->ExitPpSttIotEngineClientApp();
		delete g_theIotEngineApp;
		g_theIotEngineApp = NULL;
	}
#endif

	//2023-2-7  lijunqing
	Release_GbWzdAiTool();
}

void CSttTestAppBase::SetSttTestCtrlCntr(CSttTestCtrlCntrBase *pTestCtrlCntr)
{
	m_pTestCtrlCntr = pTestCtrlCntr;

	if (g_theGbWzdAiTool != NULL)
	{
		g_theGbWzdAiTool->SetSttGuideBook((CSttGuideBook*)pTestCtrlCntr->GetGuideBook());
	}
}

void CSttTestAppBase::SetCurrTestMacroUI(const CString &strID)
{
	m_pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(strID);
}

void CSttTestAppBase::SetCurrTestMacroUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	m_pTestMacroUI = pTestMacroUI;
}

CString CSttTestAppBase::GetCurrTestMacroUI()
{
	if (m_pTestMacroUI == NULL)
	{
		return "";
	}

	return m_pTestMacroUI->m_strID;
}

CString CSttTestAppBase::GetCurrUI_ID()
{
	if (m_pTestMacroUI == NULL)
	{
		return "";
	}

	return m_pTestMacroUI->m_strUI_ID;
}

bool CSttTestAppBase::IsTestMacro_CurrVolChAsItem()
{
	if (m_pTestMacroUI == NULL)
	{
		return false;
	}

	if(m_pTestMacroUI->m_strUI_ID == STT_ORG_MACRO_ManualTest
		|| m_pTestMacroUI->m_strUI_ID == STT_ORG_MACRO_HarmTest
		||m_pTestMacroUI->m_strUI_ID == STT_ORG_MACRO_StateTest
		||m_pTestMacroUI->m_strUI_ID == STT_ORG_MACRO_SmvAbnTest
		||m_pTestMacroUI->m_strUI_ID == STT_ORG_MACRO_GseAbnTest
		||m_pTestMacroUI->m_strUI_ID == STT_ORG_MACRO_ShortTimeOverTest)//zhouhj 2024.1.17
	{
		return true;
	}

	return false;
}

bool CSttTestAppBase::IsMuTest()
{
	if (m_pTestMacroUI == NULL)
	{
		return false;
	}

	return IsMuTest(m_pTestMacroUI->m_strID);
}

bool CSttTestAppBase::IsMuTest(const CString &strMacroID)
{
	if ((strMacroID == STT_ORG_MACRO_MUAccuracyTest)||
		(strMacroID == STT_ORG_MACRO_MUTimingAccurTest)||
		(strMacroID == STT_ORG_MACRO_MUPunctAccurTest)||
		(strMacroID == STT_ORG_MACRO_MUFirstCycleTest)||
		(strMacroID == STT_ORG_MACRO_MUAccurAutoTest) ||
		(strMacroID == STT_ORG_MACRO_MUAutoTest))
	{
		return true;
	}

	return false;
}

//zhouhj 2023.12.19 自动测试调用的时候,是否需要进行传参
bool CSttTestAppBase::SmartTestIsNeedArguments(const CString &strMacroID)
{
	if (IsMuTest(strMacroID))
	{
		return true;
	}
	else if (strMacroID == STT_ORG_MACRO_ShortTimeOverTest)
	{
		return true;
	}
	else if (strMacroID == STT_ORG_MACRO_SoeTest)
	{
		return true;
	}
	else if (strMacroID == STT_ORG_MACRO_LineDiffCurr6ITest)
	{
		return true;
	}
	else if (strMacroID == STT_ORG_MACRO_BusDiffCurr6ITest)
	{
		return true;
	}
	else if (strMacroID == STT_ORG_MACRO_ManualTest || 
		     strMacroID == STT_ORG_MACRO_StateTest || 
			 strMacroID == STT_ORG_MACRO_HarmTest ||
			 strMacroID == STT_ORG_MACRO_ReplayTest ||
		     strMacroID == STT_ORG_MACRO_AntiShakeTimeTest||
			 strMacroID == STT_ORG_MACRO_RemoteMeasTest||
			 strMacroID == STT_HTML_MACRO_ZeroTest ||
			 strMacroID == STT_CNTR_CMD_FAParasSetDialog ||
			 strMacroID ==STT_HTML_MACRO_OverCurrentTest ||
			 strMacroID == _T("TURecloseAccTest"))

	{
		return true;
	}
	
	
	return false;
}

#ifdef _PSX_QT_LINUX_
BOOL CSttTestAppBase::StartSmartTest()
{
    QProcess process;
    process.start("pgrep", QStringList() << "-x" << "SttTestMainCore");
    process.waitForFinished();
    if (process.exitCode() == 0)
    {
#ifdef _DEBUG
        return FALSE;
#endif
        ExitSmartTest();
    }
    char cCorePath[100];
    getcwd(cCorePath,sizeof(cCorePath));
    CString strCorePath(cCorePath);
    m_Process.start(strCorePath +_T("/SttTestMainCore"));

    return TRUE;
}

void CSttTestAppBase::ExitSmartTest()
{
    m_Process.terminate();
}

#endif

#ifndef _PSX_QT_LINUX_
BOOL CSttTestAppBase::StartSmartTest(const CString& strMacroID)
{
	if (IsProgramExist(_T("SmartTestCore.exe")))
	{
#ifdef _DEBUG
		return FALSE;
#endif
		ExitSmartTest();
	}

	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Report/Bin/");
	strPath += _T("SmartTestCore.exe");

	//2022-3-27  lijunqing  直接启动，运行于后台
	CString strCmdLine = _T("MacroID:");

	if (SmartTestIsNeedArguments(strMacroID))
	{
		strCmdLine += strMacroID;
		strCmdLine += ";";
		QSttWgtCmdThread::startDetached_exe(strPath, strCmdLine);
	}
	else
	{
		QSttWgtCmdThread::startDetached_exe(strPath, _T(""));
	}

	return TRUE;

	//CTickCount32 oTick;
	//oTick.DoEvents(1000);
}

void CSttTestAppBase::ExitSmartTest()
{
	TerminateProgram(_T("SmartTestCore.exe"));
}

void CSttTestAppBase::StartIotProtoServer()
{
	if (IsProgramExist(_T("IotProtoServer.exe")))
	{
		ExitIotProtoServer();
	}

	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("IotEngineServer/Bin/");
	strPath += _T("IotProtoServer.exe");

	//直接启动，运行于后台
	QSttWgtCmdThread::startDetached_exe(strPath, _T(""));
}

void CSttTestAppBase::ExitIotProtoServer()
{
	TerminateProgram(_T("IotProtoServer.exe"));
}

#endif

void CSttTestAppBase::OnCmd_StartTest()
{

}

void CSttTestAppBase::OnCmd_StopTest()
{

}

//2022-4-11 lijunqing
void CSttTestAppBase::InitSttIecRecord(CSttTestAppCfg* pSttTestAppCfg)
{
	if (g_theSmartCapCtrl != NULL)
	{
		return;
	}

	CXSmartCapMngr::Create();

#ifdef _XSmartCap_use_SttRcdSocket_
	//使用动态分配的内存  2022-6-21  lijunqing
	CSttRcdMemBufferMngr *pSttRcdMemBufferMngr = new CSttRcdMemBufferMngr();
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->CreateSttCap_61850(pSttTestAppCfg, pSttRcdMemBufferMngr);
	pXSttCap_61850->m_bUseSttTestEngineClientData = FALSE;
	g_pSttRcdSndRingBuf = pXSttCap_61850;
#else

	//2022-4-7  lijunqing 创建共性内存Server
	CRingMemBuf *pRingMemBuf = NULL;
#ifdef _PSX_QT_LINUX_
	CRingMemBufShm *pRingMemBufShm = new CRingMemBufShm();
	pRingMemBufShm->ShmCreateClient();
	pRingMemBuf = pRingMemBufShm;
#else
	CRingMemBufShmDebug *pRingMemBufShm = new CRingMemBufShmDebug();
	pRingMemBufShm->ShmCreateServer();
	pRingMemBufShm->ShmCreateClient();
	pRingMemBuf = pRingMemBufShm;
#endif

	CSttLocalRcdMemBufferMngrLinux *pNewRcdMemBufferMngr = new CSttLocalRcdMemBufferMngrLinux();
	pNewRcdMemBufferMngr->SetRingMemBuf(pRingMemBuf);
    pNewRcdMemBufferMngr->ResetBuffer();
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->CreateSttCap_61850(pSttTestAppCfg, pNewRcdMemBufferMngr);
	pXSttCap_61850->m_bUseSttTestEngineClientData = FALSE;
	g_pSttRcdSndRingBuf = pRingMemBuf;

#endif

	//Windows模式下，增加调试功能
 #ifndef _PSX_QT_LINUX_
 #ifndef _XSmartCap_use_SttRcdSocket_//在socket模式下,暂不启动模拟探测
	g_pRingMemBufShmDebugWidget = new QRingMemBufShmDebugWidget();
    g_pRingMemBufShmDebugWidget->show();//true);
 #endif
 #endif

	CSmartCapCtrl::Create();
	g_theSmartCapCtrl->m_pXSttCap_61850 = pXSttCap_61850;
	g_theSmartCapCtrl->BeginSmartCapThread();
	pXSttCap_61850->m_pKeyDB = m_pKeyDB;

	//2022-9-25  lijunqing初始化 g_theHtmlRptGenFactory
	g_theHtmlRptGenFactory->m_pDvmDevice = pXSttCap_61850->m_pDvmDevice;

}

void CSttTestAppBase::ExitSttIecRecord()
{
	//delete g_pSttRcdSndRingBuf;  在pXSttCap_61850中删除
	g_pSttRcdSndRingBuf = NULL;
	CXSmartCapMngr::Release();
	CSmartCapCtrl::Release();

 #ifdef _PSX_QT_LINUX_
 
 #else
	delete g_pRingMemBufShmDebugWidget;
	g_pRingMemBufShmDebugWidget = NULL;
#endif
}

void CSttTestAppBase::InitKeyDB()
{
	if (m_pKeyDB != NULL)
	{
		return;
	}

	m_pKeyDB = new CXKeyDB();
	m_pKeyDB->OpenKeyDbFile(_T("RelayTestKeyDb.xml"), TRUE);
}


//2023-2-21  lijunqing  被测装置的设备数据模型
void CSttTestAppBase::CreateNewDvmDevice()
{
	FreeDvmDevice();
	m_pDvmDevice = new CDvmDevice();
}

void CSttTestAppBase::CreateNewDvmDevice(const CString &strFile)
{
	CreateNewDvmDevice();
	OpenDvmDevice(strFile);
}

void CSttTestAppBase::OpenDvmDevice(const CString &strFile)
{
	if (strFile.GetLength() < 5)
	{
		return;
	}

	if (m_pDvmDevice == NULL)
	{
		return;
	}

	CString strPath;


    if ((strFile.Find("/")>=0) || (strFile.Find(_T("\\")) > 0))
	{
		strPath = strFile;
	}
	else
	{
// 		strPath = _P_GetLibraryPath();
// 		strPath += strFile;
		//默认的模型文件路径。
		strPath = _P_GetInstallPath();//zhouhj 2023.12.6 参考window软件模型文件在e-Protocol\\文件夹下
#ifdef _PSX_QT_LINUX_
		strPath += _T("e-Protocol/Library/");
#else
		strPath += _T("e-Protocol\\Library\\");
#endif
		strPath += strFile;

// 		if (!IsFileExist(strPath))
// 		{
// 			strPath = strFile;
// 		}
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,"(%s)(%s).",strPath.GetString(),strFile.GetString());

	m_pDvmDevice->OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (g_theGbWzdAiTool != NULL)
	{
		g_theGbWzdAiTool->SetDvmDevice(m_pDvmDevice);
		g_theGbWzdAiTool->DvmFilterByExtendKeys();
	}
}

void CSttTestAppBase::FreeDvmDevice()
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}

	if (IsDeviceNewCreate())
	{
		delete m_pDvmDevice;
	}

	m_pDvmDevice = NULL;
}

void CSttTestAppBase::AttachDvmDevice(CDvmDevice *pDevice)
{
	FreeDvmDevice();
	m_pDvmDevice = pDevice;
	m_pDvmDevice->m_dwReserved = 0;  //表示为外部关联的设备数据模型

	if (g_theGbWzdAiTool != NULL)
	{
		g_theGbWzdAiTool->SetDvmDevice(m_pDvmDevice);
		g_theGbWzdAiTool->DvmFilterByExtendKeys();
	}
}

BOOL CSttTestAppBase::IsDeviceNewCreate()
{
	if (m_pDvmDevice == NULL)
	{
		return FALSE;
	}

	return (m_pDvmDevice->m_dwReserved == 0x0FFFFFFF);
}

void CSttTestAppBase::OpenPpSttCommConfigFile()
{
	CString strFile,strDvmFilePath;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");

	if (! m_oCommConfig.OpenCommConfigFile(strFile) )
	{
		return;
	}

	m_oCommConfig.UpdateFilePath_UseAbs();//zhouhj 使用绝对路径
	strDvmFilePath = m_oCommConfig.Get_DvmFile();

	if (strDvmFilePath.GetLength() <= 5)
	{
		return;
	}

// 	strFile = _P_GetLibraryPath();
// 	strFile = strFile + m_oCommConfig.Get_DvmFile();

	if (!IsFileExist(strDvmFilePath))
	{
		strFile = _P_GetInstallPath();//zhouhj 2023.12.6 参考window软件模型文件在e-Protocol\\文件夹下
		strFile += _T("e-Protocol\\Library\\");
		strFile += strDvmFilePath;
		strDvmFilePath = strFile;
	} 

	

	if (! ::IsFileExist(strDvmFilePath))
	{
		return;
	}

	CreateNewDvmDevice(strDvmFilePath);
}

