#include "stdafx.h"
#include "TctrlCntrBaseApp.h"
#include	"../../Module/api/GlobalConfigApi.h"
#include "../../Module/api/GloblaDrawFunctions.h"
#include "../AutoTestXMLRWKeys.h"
#include "../../Module\API\SingleAppMutexApi.h"
#include "..\..\..\Module\EpotoInterface\EpotoInterface.h"
#include "..\..\..\Module\Encrypt\EncryptTool.h"
#include "..\..\..\61850\Module\MMS_STACK_CFG\MMS_STACK_CFG.h"

#include "../RecorderPpEngine.h"
#include "../RecorderInterfaceCOM.h"

#include "../XLanguageResourceAts.h"
#include "..\..\..\Protocol\Module\ProcotolProject\ClassProcotolProjectGlobal.h"
#include "..\..\..\Module\QRCode\QRCodeRead.h"
#include "../GuideBook\GuideBookTool.h"
#include "..\..\..\Module\Record\XRecordDrawComtradeDib.h"


#define _use_TerminateProgram

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//
CTCtrlCntrBaseApp *g_theTCtrlCntrApp = NULL;
//CRptFillAppBase *g_theRptFillApp = NULL;

CTCtrlCntrBaseApp::CTCtrlCntrBaseApp()
{
	srand(time(0));

	g_theTCtrlCntrApp = this;
	m_pWaveFileMngr = NULL;
	m_oRecorder = NULL;

	//m_pTestTasks = new CTestLibraryTasks;
#ifndef GUIDEBOOK_DEV_MODE
	m_pMttTestTask = NULL;
#endif

	m_pFontTestItem = NULL;
	
	m_pXTestMsgWnd = NULL;
	m_oRecorder = NULL;
	m_dwTestMode = TEST_MODE_REPORT;
	m_nDsvImage = 0;

#ifdef _use_ppengine_exception
	m_nPpMmsEngineCpuCounts = 0;
#endif
}

CTCtrlCntrBaseApp::~CTCtrlCntrBaseApp()
{
}

void CTCtrlCntrBaseApp::CreateReportApp()
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

BOOL CTCtrlCntrBaseApp::ats_IsRegisterTrue(BOOL bShowMsg, BOOL bFromTest)
{
#ifdef GUIDEBOOK_DEV_MODE
	return CSafenet_Login::hasp_has_catalog(FETUREID_AUTOTEST, bShowMsg);
#else
	ASSERT (m_pCtrlCntrConfig != NULL);

	if (bFromTest)
	{
		return TRUE;
	}

	if (Encrypt_IsUseRegisterFile())
	{
		return Encrypt_IsEncrypt();
	}
	else
	{
		return CSafenet_Login::hasp_has_catalog(FETUREID_AUTOTEST, bShowMsg);
	}
#endif
}

/*
	初始化：在应用程序App的COM环境初始化之后调用
	过程：	初始化m_oSystemConfig
						初始化m_oTCtrlCntrConfig
						初始化m_oTestTasks
						初始化m_oTCtrlCntrWorkspace
*/
long CTCtrlCntrBaseApp::InitSmartTestBaseApp()
{
	//初始化系统路径
	_P_InitSystemPath();

	if (! CSmartTestBaseApp::InitSmartTestBaseApp())
	{
		return 0;
	}

	CRcdComtradeFileMngr::Create();

	if (CTCtrlCntrConfig::Get_IsSingleApp())
	{
		if (!CreateSingleAppMutex(_T("AutoTest_TCtrlCntr_Inst_Lock")))
		{
			return FALSE;
		}
	}


	m_pTestFileMngr = new CXFileMngr();

	InitTCtrlCntrPath();

	InitTaskMngr();


//	m_WordCommandBarMngr.Init();
//
// 	m_pXTestMsgWnd = new CTestMsgWnd();
// 	m_pXTestMsgWnd->Create(CWnd::GetDesktopWindow());

#ifdef _use_MACROTEST_MEM_
	//与TCtrl交互的接口定义
	char pszPath[MAX_PATH];
	sprintf(pszPath, "%s%s", _P_GetBinPath(), MACROTEST_MEMFILENAME);
	m_pMemServer = new CShareMemServer(pszPath, MACROTEST_MAPNAME, MACROTEST_MAPSIZE);
#endif

	CString strPath;
	Gb_GetWavePath(strPath);

#ifdef GB_USE_XFILEMNGRBASE
	m_pWaveFileMngr = new CXFileMngr();
	m_pWaveFileMngr->SearchFiles(_T("wav"), _T("wav"),  strPath);
#else
	m_oWaveFileMngr.Traverse(strPath, _T("wav"),  FALSE);
#endif

	CString strWorkSpacePath;
	strWorkSpacePath = GetWorkSpacePath();

	//2021-8-5  lijunqing   ????????????????????????????有内存泄露
	ATS_InitSysReportFileMngr(m_pTestFileMngr, strWorkSpacePath);
	CreateAllEngine();

	//动态库调用初始化
	CSafetyDllCallMngr::Create();

#ifndef GUIDEBOOK_DEV_MODE
	CClassProcotolProjectXmlRWKeys::Create();
#endif

	//二维码
	CQRCodeRead::Create();

#ifndef GUIDEBOOK_DEV_MODE
	CDeviceModelXmlKeys::Create();
#endif

	//是否为工厂模式  2018-11-10
	if (CTCtrlCntrConfig::IsFacBatchTestMode())
	{
		CFactoryBatchTestMngr::Create();
	}

	return 1;
}


/*
	释放测试环境：在应用程序的ExitInstance中调用
	一定要在ExitInstance中调用，否则应用程序会因释放环境顺序问题导致错误
*/
long CTCtrlCntrBaseApp::ExitSmartTestBaseApp()
{

	//是否为工厂模式  2018-11-10
	if (CTCtrlCntrConfig::IsFacBatchTestMode())
	{
		CFactoryBatchTestMngr::Release();
	}

	ReleaseRecorder();

	if(m_pFontTestItem != NULL)
	{
		delete m_pFontTestItem;
		m_pFontTestItem = NULL;
	}



#ifdef _use_MACROTEST_MEM_
	if (m_pMemServer != NULL)
	{
		delete m_pMemServer;
		m_pMemServer = NULL;
	}
#endif

#ifndef GUIDEBOOK_DEV_MODE
	CloseTestTask();
#endif

	if (m_pWaveFileMngr != NULL)
	{
		delete m_pWaveFileMngr;
		m_pWaveFileMngr = NULL;
	}

	if (m_pTestFileMngr != NULL)
	{
		delete m_pTestFileMngr;
		m_pTestFileMngr = NULL;
	}

	CSafetyDllCallMngr::Release();	//动态库调用

#ifndef GUIDEBOOK_DEV_MODE
	CClassProcotolProjectXmlRWKeys::Release();
#endif

	//二维码
	CQRCodeRead::Release();

#ifndef GUIDEBOOK_DEV_MODE
	CDeviceModelXmlKeys::Release();
#endif

	CRcdComtradeFileMngr::Release();

	CSmartTestBaseApp::ExitSmartTestBaseApp();

	return 0;
}

void CTCtrlCntrBaseApp::CreateNewRecorder()
{
	CRecorderCOM *pNew = new CRecorderCOM();
	pNew->CreateCrecorder(m_pCtrlCntrConfig->m_strRecordProgID);
	m_oRecorder = pNew;
}

/*
	从文件读入任务管理
	因为任务管理的数据可能比较多，不提倡一开始就读入全部的任务
	在需要的时候再读入
*/
void CTCtrlCntrBaseApp::InitTaskMngr()
{
	//用于测试
	//m_pTestTasks->Open();
}

void CTCtrlCntrBaseApp::SaveTaskMngr()
{
	//m_pTestTasks->Save();
}

void CTCtrlCntrBaseApp::CreateGbTreeImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	m_GbTreeImageList.DeleteImageList();
	m_GbTreeImageList.Create (nBitmapID, cx, nGrow, crMask);

	LOGFONT lf = InitLogFont();
	lf.lfHeight = 14;
	lf.lfWeight = 400;

#ifdef UNICODE
	lstrcpy(lf.lfFaceName,L"宋体");
#else
	strcpy(lf.lfFaceName,"宋体");	
#endif // UNICODE
	
	if (m_pFontTestItem == NULL)
	{
		m_pFontTestItem =  new CFont;
		m_pFontTestItem->CreateFontIndirect(&lf);	
	}
}

#ifdef _use_ppengine_exception
BOOL CTCtrlCntrBaseApp::IsPpMmsEngineException()
{
	int nCpuUsage = m_oSysExeCpuUsage.get_cpu_usage();

	if (nCpuUsage > 50)
	{
		m_nPpMmsEngineCpuCounts++;
	}

	if (m_nPpMmsEngineCpuCounts > 3)
	{
		m_nPpMmsEngineCpuCounts = 0;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
#endif

void CTCtrlCntrBaseApp::CreatePpEngine()
{
	//关闭进程
#ifdef _use_TerminateProgram
	TerminateProgram(g_strPpEngineExeName);
	TerminateProgram(g_strPpMmsEngineExeName);
#endif
}

void CTCtrlCntrBaseApp::CreateAllEngine()
{
	CreatePpEngine();
}

BOOL CTCtrlCntrBaseApp::IsMacroTCtrlException()
{
	return FALSE;

#ifdef _use_MACROTEST_MEM_

	if (m_pMemServer == NULL)
	{
		return FALSE;
	}

	static LONG EXCEPTION_COUNT = 10;
	DWORD *pdwBuffer = (DWORD*)m_pMemServer->GetBuffer();
	*pdwBuffer = *pdwBuffer + 1;
	*(pdwBuffer + 1) = *(pdwBuffer + 1) + 1;
	*(pdwBuffer + 2) = *(pdwBuffer + 2) + 1;

	if (*pdwBuffer > EXCEPTION_COUNT ||  *(pdwBuffer + 1) > EXCEPTION_COUNT || *(pdwBuffer + 2) > EXCEPTION_COUNT)
	{
		memset(pdwBuffer, 0, 3 * sizeof(DWORD));
		return TRUE;
	}
	else
	{
		return FALSE;
	}
#endif
}


void CTCtrlCntrBaseApp::ExecutePpEngineCmd(CTestControlBase *pTestControl, const CString &strCmdID, const CString &strCmdPara)
{
	if (pTestControl == NULL)
	{
		return;
	}

	UINT nTestControlMode = pTestControl->GetTestControlMode();

	switch (nTestControlMode)
	{
	case TESTCONTROLMODE_NORMAL:
		ExecutePpEngineCmd_NORMAL(pTestControl, strCmdID, strCmdPara);
		break;

	case TESTCONTROLMODE_MGBRPT:
		ExecutePpEngineCmd_MGBRPT(pTestControl, strCmdID, strCmdPara);
		break;

	case TESTCONTROLMODE_MDGBRPT:
		ExecutePpEngineCmd_MDGBRPT(pTestControl, strCmdID, strCmdPara);
		break;

	default:
		break;
	}
}

void CTCtrlCntrBaseApp::ExecutePpEngineCmd_NORMAL(CTestControlBase *pTestControl, const CString &strCmdID, const CString &strCmdPara)
{
	m_strPpEngineCmdID = strCmdID;
	m_strPpEngineCmdPara = strCmdPara;
	pTestControl->Out_RunProcedure(strCmdID, _T(""), 0, 0, ProcedureType_EngineCmd);
}

void CTCtrlCntrBaseApp::ExecutePpEngineCmd_MGBRPT(CTestControlBase *pTestControl, const CString &strCmdID, const CString &strCmdPara)
{
	m_strPpEngineCmdID = strCmdID;
	m_strPpEngineCmdPara = strCmdPara;
	pTestControl->Out_RunProcedure(strCmdID, _T(""), 0, 0, ProcedureType_EngineCmd);
}

void CTCtrlCntrBaseApp::ExecutePpEngineCmd_MDGBRPT(CTestControlBase *pTestControl, const CString &strCmdID, const CString &strCmdPara)
{
	m_strPpEngineCmdID = strCmdID;
	m_strPpEngineCmdPara = strCmdPara;
	pTestControl->Out_RunProcedure(strCmdID, _T(""), 0, 0, ProcedureType_EngineCmd);
}


void CTCtrlCntrBaseApp::FireTestItemErrorMsg(CGbItemBase *pItem, long nStopByError)
{
	if (pItem->GetState() == TEST_STATE_INLEGIBLE)
	{
		if (m_pXTestMsgWnd != NULL && CTCtrlCntrConfig::GetShowTestMsgWnd())
		{
			m_pXTestMsgWnd->PostMessage(WM_GBITEM_TEST_STATE, (WPARAM)pItem, (WPARAM)nStopByError);
		}
	}

	PostThreadMessage(WM_GBITEM_TEST_STATE, (WPARAM)pItem, (WPARAM)nStopByError);
}

void CTCtrlCntrBaseApp::FireTestFinishMessage(BOOL bMttTaskFinish)
{
	if (m_pXTestMsgWnd != NULL  && CTCtrlCntrConfig::GetShowTestMsgWnd())
	{
#ifndef GUIDEBOOK_DEV_MODE
		if (m_pMttTestTask == NULL)
		{
			m_pXTestMsgWnd->PostMessage(WM_GBITEM_TEST_STATE, 0, 0);
		}
		else
		{
			if (bMttTaskFinish)
			{
				m_pXTestMsgWnd->PostMessage(WM_GBITEM_TEST_STATE, 0, 0);
			}
		}
#else
		m_pXTestMsgWnd->PostMessage(WM_GBITEM_TEST_STATE, 0, 0);
#endif
	}

	PostThreadMessage(WM_GBITEM_TEST_STATE, 0, 0);
}

#ifndef GUIDEBOOK_DEV_MODE
CTestTask* CTCtrlCntrBaseApp::CreateNewTask(CTestTask *pTestTask)
{
	CloseTestTask();
	m_pMttTestTask = (CTestTask*)pTestTask->Clone();

	return m_pMttTestTask;
}

void CTCtrlCntrBaseApp::OpenTaskFile(const CString &strTaskFile)
{
	CloseTestTask();

	m_pMttTestTask = new CTestTask();
	m_pMttTestTask->OpenTaskFile(strTaskFile);
}

void CTCtrlCntrBaseApp::SaveTaskFile()
{
	ASSERT (m_pMttTestTask != NULL);
}

void CTCtrlCntrBaseApp::ReleaseMttDevice()
{
	try
	{
		m_oMttPpDevice = NULL;
	}
	catch (...)
	{
	}

}

void CTCtrlCntrBaseApp::CloseTestTask()
{
	if (m_pMttTestTask == NULL)
	{
		return;
	}

	ReleaseMttDevice();
	m_pMttTestTask->Save(TRUE);
	delete m_pMttTestTask;
	m_pMttTestTask = NULL;
}
#endif

#ifndef GUIDEBOOK_DEV_MODE

void CTCtrlCntrBaseApp::WritePpMmsEngineConfig(CTestTask *pTestTask)
{
	//释放MMS规约引擎程序
	ReleasePpEngine(g_strPpEngineProgIDMms);
	pTestTask->WritePpMmsEngineConfig();
// 	CTestProject *pProject = NULL;
// 	CMMS_STACK_CFG oMMS_STACK_CFG;
// 	oMMS_STACK_CFG.Open_MMS_STACK_CFG_Outer();
// 	CStkCfg_RemoteAddressList *pRemoteAddressList = oMMS_STACK_CFG.GetRemoteAddressList();
// 	long nIndex = 0;
// 	pRemoteAddressList->SetCount(m_pTestTask->GetCount());
// 	CStkCfg_RemoteAddress *pAddress = NULL;
// 	POS pos = pTestTask->GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pProject = (CTestProject *)pTestTask->GetNext(pos);
// 		pAddress = (CStkCfg_RemoteAddress *)pRemoteAddressList->GetAtIndex(nIndex);
// 		pAddress->SetIP(pProject->m_strLocalID);
// 		pAddress->m_strModel = pProject->m_strName;
// 		nIndex++;
// 	}
// 
// 	oMMS_STACK_CFG.Save_MMS_STACK_CFG_Outer();
// 	oMMS_STACK_CFG.WriteIpToVMDFile();
}

#endif

void CTCtrlCntrBaseApp::WritePpMmsEngineConfig()
{
#ifndef GUIDEBOOK_DEV_MODE
	WritePpMmsEngineConfig(m_pMttTestTask);
#endif
}

BOOL TCC_IsDebugWithoutReport()
{
	ASSERT (g_theTCtrlCntrApp != NULL);
	return g_theTCtrlCntrApp->IsDebugWithoutReport();
}

