#include "stdafx.h"
#include "TestControl.h"

#include "../GuideBook/Script/GbScript_GlobalDefine.h"
#include <math.h>
#include "../../Module/DataMngr/DvmDatasetSort.h"
#include "../GuideBook/GuideBookDefine.h"

#include "../XLanguageResourceAts.h"
#include "../GuideBook/GuideBookTool.h"
#include "../TCtrlCntrConfig.h"
#include "SmartTestBaseApp.h"

#include "TestControlWnd.h"
#include "../TCtrlCntrWorkSpace.h"
#include "TCtrlCntrBaseApp.h"
#include "../GuideBook\Script/GbScript_GlobalDefine.h"
#include "..\..\..\Module\KeyDb\XMatchToolBase.h"

#include "../XRecorderDlg.h"
#include "..\..\..\Module\EpotoInterface\EpotoInterface.h"
#include "..\..\..\Module\DataMngr\DatasetValid\DsvViewResultDialog.h"
#include "..\..\..\Module\DataMngr\DvmDatasetSort.h"

#include "../GuideBook/ReportMap/WordRptExport.h"
#include "../GuideBook/ReportMap/WPSRptExport.h"

#include "../SmartTestRpcEventApi.h"
#include "..\..\..\Module\API\MemClean.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestControl::CTestControl()
{
	m_pGbTreeCtrl = NULL;
	m_pInlegibleTestItemViewGrid = NULL;

#ifndef GUIDEBOOK_DEV_MODE
	m_pSysParaEditDlg = NULL;
	m_pSysParaViewDlg = NULL;
#endif

	//m_pCommCmdDlg = NULL;
	m_pUICommCmdViewDlg = NULL;
	m_bUICommCmdViewDlgRef = FALSE;
	m_pSafetyDlg = NULL;
}


long CTestControl::CreateReportFill(const CString &strRptProgID, BOOL bExportWord)
{
	return CTestControlBase::CreateReportFill(strRptProgID, bExportWord);
/*
	if (m_pReportFill != NULL)
	{
		return 0;
	}

	if (TCC_IsDebugWithoutReport())
	{	
		m_pReportFill = new CSystemRptFill();
	}
	else
	{
		if (strRptProgID.CompareNoCase(REPORTFILL_PROGID_WORD) == 0)
		{
			if (bExportWord)
			{
				g_theSmartTestBaseApp->CreateApp(CRptFillWordApp::New);
				m_pReportFill = new CWordRptFill();
			}
			else
			{
				g_theSmartTestBaseApp->CreateApp(CRptFillWordApp::New);
				m_pReportFill = new CWordRptFill();
			}
		}
		else if (!strRptProgID.CompareNoCase(REPORTFILL_PROGID_WPS))
		{
			g_theSmartTestBaseApp->CreateApp(CRptFillWPSApp::New);
			m_pReportFill = new CWPSRptFill();
		}
		else if (!strRptProgID.CompareNoCase(REPORTFILL_PROGID_SYSTEM))
		{		
			m_pReportFill = new CSystemRptFill();
			m_pReportFill->SetSysRptShowMaxCount(g_theSmartTestBaseApp->GetSysRptShowMaxCount());
		}
		else
		{	
			m_pReportFill = NULL;
		}
	}

	if (m_pReportFill != NULL)
	{
		m_pReportFill->SetGuideBook(m_pGuideBook);
		m_pReportFill->m_strName = m_strName;
		m_pReportFill->SetFillReport(g_theSmartTestBaseApp->IsFillReport());
	}

	return 0;
*/
}

CWordRptExportBase* CTestControl::CreateRptExport(const CString &strRptProgID)
{
	//shaolei 20220718
	return CTestControlBase::CreateRptExport(strRptProgID);
// 	CWordRptExportBase* pRptExport = NULL;
// 	
// 	if (strRptProgID == REPORTFILL_PROGID_WPS)
// 	{
// 		pRptExport = new CWPSRptExport;
// 	}
// 	else
// 	{
// 		pRptExport = new CWordRptExport;
// 	}
// 
// 	return pRptExport;
}

void CTestControl::FinishInptuData(CDataGroup *pDataGroup)
{
	if (m_pCurrTestItem == NULL)
	{
		return;
	}


	if (m_pCurrTestItem->GetClassID() == GBCLASSID_SAFETY)
	{
		CSafety *pSafety = (CSafety*)m_pCurrTestItem;
		SetVal_ShortDatas_by_DvmDatas(pDataGroup, pSafety->m_pDatas);

		if (m_pSafetyDlg != NULL)
		{
			m_pSafetyDlg->PostMessage(WM_FINISH_INPUTDATA, 0, 0);
		}
		else
		{
			FinishTestItemSafety(pSafety);
		}

		return;
	}

	if (m_pCurrTestItem->GetClassID() == GBCLASSID_SYSPARAEDIT)
	{
		CSysParaEdit *pSysParaEdit = (CSysParaEdit*)m_pCurrTestItem;
		CExBaseList *pList = pSysParaEdit->GetSysParaEditDataObjList();
		Gb_InitValueByDvmDatas(pDataGroup, pList);
		FinishTestItemSysParaEdit(pSysParaEdit);
		return;
	}

}

CTestControl::~CTestControl()
{
	DestroyAllTestItemUI();
	
}

//创建通讯规约引擎对象
void CTestControl::CreatePpEngineDevice(CProtocolEngineInterface *pEngine, CPpDeviceRef *pDevieceRef)
{
	CString strDeviceID ;
	strDeviceID = m_pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);

	//shaolei 20210831
	if (strDeviceID.IsEmpty())
	{
		if (pDevieceRef->m_strID.GetLength() > 0)
		{
			strDeviceID = pDevieceRef->m_strID;
		}
		else
		{
			strDeviceID = GetPathFileNameFromFilePathName(m_pGuideBook->m_strDeviceModelFile);
		}
	}
	
	CTestTask *pTestTask = g_theTCtrlCntrApp->GetMttTestTask();

	//2019-6-4  对于测试任务模式，保留上次的测试规约设备对象
	if (pTestTask != NULL)
	{
		pDevieceRef->m_oPpDevice = (CXProtocolDevice*)g_theTCtrlCntrApp->GetMttPpDevice();

		if (pDevieceRef->m_oPpDevice == NULL)
		{
			pDevieceRef->m_oPpDevice =  (CXProtocolDevice*)pEngine->CreateDevice(pDevieceRef->m_strPpTemplateFile, pDevieceRef->m_strDeviceModelFile, strDeviceID);
			g_theTCtrlCntrApp->SetMttPpDevice(pDevieceRef->m_oPpDevice);
		}
	}
	else
	{
		pDevieceRef->m_oPpDevice =  (CXProtocolDevice*)pEngine->CreateDevice(pDevieceRef->m_strPpTemplateFile, pDevieceRef->m_strDeviceModelFile, strDeviceID);
	}

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	if (pDevieceRef->m_strEngineMode.IsEmpty() || pDevieceRef->m_strEngineMode == STT_CMD_PARA_EngineMode_COM)
	{
		//COM接口，没有SetSttCmdDataFormat
	}
	else
	{
		if (pDevieceRef->m_oPpDevice != NULL)
		{
			pDevieceRef->m_oPpDevice->SetSttCmdDataFormat(g_theSmartTestBaseApp->GetXmlRwType());
		}
	}
#endif

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CreatePpEngineDevice:%s"), pDevieceRef->m_strID);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("      TemplateFile:%s"), pDevieceRef->m_strPpTemplateFile);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("      DvmFile:%s"), pDevieceRef->m_strDeviceModelFile);

	//设置录波文件路径
	SetPpEngineRecordFilePath(pDevieceRef->m_oPpDevice);
}

BOOL CTestControl::CreatePpEngineDevice(CCommCmd *pCmd)
{
	if (m_oDeviceRefs.IsAllDeviceConnectSucc())
	{
		return TRUE;
	}

	//@@根据设备的ID【IP地址】，创建通讯设备对象
	//strDeviceID : 设备数据模型的ID【IP地址】
	CPpDeviceRef *pPpDeviceRef = NULL;
	pPpDeviceRef = m_oDeviceRefs.GetPpDeviceRefToConnect();
	ASSERT (pPpDeviceRef != NULL);

	//如果是多引擎，在此修改  李俊庆-20140918
	//shaolei  for debug  暂时写死  20210929
/*  //2023-8-22  lijunqing 不再使用m_pGuideBook->m_strPpEngineProgID，统一使用pPpDeviceRef->m_strPpEngineProgID
	//如果是打开测试记录文件，则进行初始化设置pPpDeviceRef
	CProtocolEngineInterface *pEngine = g_theSmartTestBaseApp->GetPpEngine(pPpDeviceRef->m_strEngineMode, m_pGuideBook->m_strPpEngineProgID);

	if (pEngine == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoPrtcCpnt/ *L"没有注册规约引擎组件"* /);
		return FALSE;
	}
*/


	//shaolei  for debug  暂时写死  20210929
	CProtocolEngineInterface *pEngine = g_theSmartTestBaseApp->GetPpEngine(pPpDeviceRef->m_strEngineMode, pPpDeviceRef->m_strPpEngineProgID);

	if (pEngine == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoPrtcCpnt/*L"没有注册规约引擎组件"*/);
		return FALSE;
	}

	try
	{
		if (pPpDeviceRef->m_oPpDevice == NULL)
		{
			//李俊庆  20140918
			CreatePpEngineDevice(pEngine, pPpDeviceRef);
		}
	}
	catch (...)
	{
		return FALSE;
	}

	//if (m_oPpDevice == NULL)
	if (pPpDeviceRef->m_oPpDevice == NULL)
	{
		g_theSmartTestBaseApp->ReleasePpEngine(pPpDeviceRef->m_strPpEngineProgID);//(m_pGuideBook->m_strPpEngineProgID);
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CreatPrtcFail/*L"创建规约通讯设备失败"*/);
	}
	else
	{
		try
		{
			pPpDeviceRef->m_oPpDevice->AttachSystemWndMsg((ULONG)m_pTCtrlWnd->m_hWnd, WM_ENGINE_SYSTEM_MSG);

			if (pCmd->IsUseConnect())
			{
				DeviceCmmConfig(pPpDeviceRef);
			}
			//Sleep (5000);
		}
		catch(...)
		{
			if (pPpDeviceRef != NULL)
			{
				if (pPpDeviceRef->m_oPpDevice != NULL)
				{
					pPpDeviceRef->m_oPpDevice = NULL;
					pPpDeviceRef->SetConnectState(FALSE);
				}
			}
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CTestControl::OpenWordReportFile(BOOL bExportWord, const CString &strDocFile)
{
	return CTestControlBase::OpenWordReportFile(bExportWord, strDocFile);
}

BOOL CTestControl::OpenWordReportFileOnly(CString &strWordFile)
{
	CTCtrlCntrConfig* pCtrlCntrConfig = g_theSmartTestBaseApp->GetCntrConfig();

	if (pCtrlCntrConfig->IsReportControlWPS())
	{
		CreateReportFill(REPORTFILL_PROGID_WPS, TRUE);
	}
	else
	{
		CreateReportFill(REPORTFILL_PROGID_WORD, TRUE);
	}
	
	m_pReportFill->SetParentWnd(NULL);
	
	//打开报告文件
	strWordFile = GetReportFilePath();

	CWordRptFill *pWordReportFill = (CWordRptFill*)m_pReportFill;
	ASSERT (pWordReportFill != NULL);
	pWordReportFill->SetGuideBook(m_pGuideBook);
	
	if (!pWordReportFill->OpenOnly(strWordFile))
	{
		return FALSE;
	}

	return TRUE;
}

void CTestControl::IsMacroTCtrlException()
{
	
	CTCtrlCntrConfig *pConfig = g_theSmartTestBaseApp->GetCntrConfig();

	if (pConfig == NULL)
	{
		return;
	}

	if (pConfig->m_nAutoTestCtrlException == 0)
	{
		return;
	}

	if (!IsNowTesting())
	{
		return;
	}

	if (m_pCurrTestItem->GetClassID() != GBCLASSID_MACROTEST)
	{
		return;
	}

	if (g_theTCtrlCntrApp->IsMacroTCtrlException())
	{
		try
		{
			delete m_pMacroTestInterface;
			m_pMacroTestInterface = NULL;
		}
		catch(...)
		{
		}

		//2017-10-29 m_strTestMacroFile==>m_strTestMacroFileID
		g_theSmartTestBaseApp->CreateMacroTestEngine(m_pGuideBook->m_strTestMacroFileID);
		m_pTCtrlWnd->m_pTestItemRef = m_pCurrTestItem;
		m_pTCtrlWnd->SetTimer(TIMER_TEST_FOR_OVERTIME, TIMER_TEST_FOR_OVERTIME_LONG*3, NULL);
	}
}

//隐藏全部测试相关的界面
void CTestControl::HideAllTestItemUI()
{
	try
	{
		if (m_pSafetyDlg != NULL)
		{
			m_pSafetyDlg->ShowWindow(SW_HIDE);
		}
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("HideAllTestItemUI::m_pSafetyDlg->ShowWindow(SW_HIDE):  Error......"));
	}
#ifndef GUIDEBOOK_DEV_MODE

	try
	{
		if (m_pSysParaEditDlg != NULL)
		{
			m_pSysParaEditDlg->ShowWindow(SW_HIDE);
		}
		if (m_pSysParaViewDlg != NULL)
		{
			m_pSysParaViewDlg->ShowWindow(SW_HIDE);
		}
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("HideAllTestItemUI::m_pSysParaViewDlg(m_pSysParaEditDlg)->ShowWindow(SW_HIDE):  Error......"));
	}
#endif

	try
	{
		if (m_pUICommCmdViewDlg != NULL && (!m_bUICommCmdViewDlgRef))
		{
			m_pUICommCmdViewDlg->ShowCommViewDlg(SW_HIDE);
		}
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("HideAllTestItemUI::m_pUICommCmdViewDlg->ShowWindow(SW_HIDE):  Error......"));
	}
}


void CTestControl::DestroyAllTestItemUI()
{
	if(m_pSafetyDlg != NULL)
	{
		m_pSafetyDlg->DestroyWindow();
		delete m_pSafetyDlg;
		m_pSafetyDlg = NULL;
	}

	if (!m_bUICommCmdViewDlgRef)
	{
		if(m_pUICommCmdViewDlg != NULL)
		{
			m_pUICommCmdViewDlg->DestroyWindow();
			delete m_pUICommCmdViewDlg;
		}
	}
	m_pUICommCmdViewDlg = NULL;

#ifndef GUIDEBOOK_DEV_MODE
	if(m_pSysParaEditDlg != NULL)
	{
		m_pSysParaEditDlg->DestroyWindow();
		delete m_pSysParaEditDlg;
		m_pSysParaEditDlg = NULL;
	}
	if(m_pSysParaViewDlg != NULL)
	{
		m_pSysParaViewDlg->DestroyWindow();
		delete m_pSysParaViewDlg;
		m_pSysParaViewDlg = NULL;
	}
#endif

}

//自动上传测试报告
void CTestControl::AutoSaveReportFileName(CWnd *pParentWnd, BOOL bJudgeState)
{
	if (bJudgeState)
	{
		if (!Gb_IsItemsTestFinished(m_pGuideBook))
		{
			return;
		}
	}

   
    CTCtrlCntrConfig *pConfig = g_theSmartTestBaseApp->GetCntrConfig();

	//路径的有效性
	if (pConfig->m_strAutoSaveReportPath.GetLength() < 3)
	{
		return;
	}

	if ( m_pGuideBook->m_strAotuSaveReportFileName.GetLength() < 3)
	{
		return;
	}

	//不创建路径，避免网络路径带来的问题
	//CreateAllDirectories(pConfig->m_strAutoSaveReportPath);

	CString strFile;
	CString strSrc = m_strGbBinaryFile;

	strFile = pConfig->m_strAutoSaveReportPath;

	if (strFile.Right(1) != _P_FOLDER_PATH_SEPARATOR_)
	{
		strFile += _P_FOLDER_PATH_SEPARATOR_;
	}

	CString strMsg = g_sLangTxt_ReportExpSucc/*_T("报告导出成功：\r\n")*/;
	strFile.AppendFormat(_T("%s.%s"), m_pGuideBook->m_strAotuSaveReportFileName, g_strGuideBookBinaryPostfix);

	strMsg.AppendFormat(_T("%s\r\n"), strFile);
	::X_CopyFile(strSrc, strFile, TRUE);
	strSrc  = ChangeFilePostfix(strSrc, g_strDocFilePostfix);
	strFile = ChangeFilePostfix(strFile, g_strDocFilePostfix);
	::X_CopyFile(strSrc, strFile, TRUE);
	strMsg.AppendFormat(_T("%s\r\n"), strFile);
	pParentWnd->MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_OK | MB_ICONINFORMATION);
}

void CTestControl::EmptyReportDatas(BOOL bUseCfgFlag)
{
	CTestControlBase::EmptyReportDatas(bUseCfgFlag);
}

void CTestControl::ChangeReportFileName(const CString &strFileName)
{
	CString strFile;
	CString strSrc = m_strGbBinaryFile;
	strFile = strFileName;
	strFile = ChangeFilePostfix(strFile, g_strGuideBookBinaryPostfix);
	strFile = GetPathFromFilePathName(m_strGbBinaryFile) + strFile;

	m_strGbBinaryFile = strFile;
	m_strGbBinaryFileName = GetPathFileNameFromFilePathName(m_strGbBinaryFile);

	::rename(strSrc, strFile);
	strSrc  = ChangeFilePostfix(strSrc, g_strDocFilePostfix);
	strFile = ChangeFilePostfix(strFile, g_strDocFilePostfix);

	if (m_pReportFill == NULL)
	{
		::rename(strSrc, strFile);
	}
	else 
	{
		if (m_pReportFill->GetReportFillClassID() == REPORTFILL_PROGID_WORD 
			|| m_pReportFill->GetReportFillClassID() == REPORTFILL_PROGID_WPS)
		{
			m_pReportFill->SaveAs(strFile);
			::DeleteFile(strSrc);
		}
		else
		{
			::rename(strSrc, strFile);
		}
	}

	CTestProject *pTestProject = (CTestProject*)GetTestProjectRef();

	if (pTestProject != NULL)
	{
		pTestProject->m_strID = m_strGbBinaryFileName;
		pTestProject->tsk_SetLocation(m_strGbBinaryFile);
	}

	m_pGuideBook->m_strGuideBookFile = m_strGbBinaryFile;
	InitGbBinaryFileName();

	if (m_pParentWnd != NULL)
	{
		if (m_pParentWnd->IsKindOf(RUNTIME_CLASS(CMDIChildWndEx)))
		{
			CMDIChildWndEx *pFrame = (CMDIChildWndEx*)m_pParentWnd;
			CDocument *pDoc = pFrame->GetActiveDocument();
			pDoc->SetTitle(m_strGbBinaryFileName);
		}
	}
}

void CTestControl::SetTestError(const CString &strTestError)
{
	CTestControlBase::SetTestError(strTestError);
	CFactoryBatchTestMngr::PostFacBatchTestMsg(FacBatchTestMsg_Attr_TestErr, (LPARAM)m_pGuideBook);
}

long CTestControl::TestItemSafety(CSafety* pItem)
{
	AddReport(pItem, -1, -1); //2017.0517

	if (m_pReportFill != NULL)
	{
		m_pReportFill->InitFillReport(pItem);
	}

	m_bSafetyScriptStopByRecord = FALSE;

	//执行初始化脚本
	CString strSyntax;
	pItem->RunInitScriptScript(strSyntax);

	//如果有语法错误，需要在界面显示
	if(m_pSafetyDlg == NULL)
	{
#ifdef _UITEST_USE_DIALOGEX
		m_pSafetyDlg = new CUISafetyTest(m_pParentWnd);
		m_pSafetyDlg->SetUseModeless();
		m_pSafetyDlg->DoModal();
#else
		m_pSafetyDlg = new CUISafetyTest;
		m_pSafetyDlg->Create(UI_GetSafetyDialogID(),m_pParentWnd);
#endif
	}
	else
	{
		//m_pSafetyDlg->ShowWindow(SW_SHOW);
	}

	//获取本项目的最后一次报告数据
	m_pSafetyDlg->InitTestItem(pItem, m_pTCtrlWnd);

	AdjustSafetyComCmdDlgPos();

// 	if ((m_pCurrSubTestItem == NULL) || (m_pCurrSubTestItem != pItem) )
// 	{
// 		TestFirstSubItems();
// 	}

	return 0;
}

long CTestControl::TestItemSysParaEdit(CSysParaEdit* pItem)
{
#ifndef GUIDEBOOK_DEV_MODE
	AddReport(pItem, -1, -1); //2017.05.17
   
    CTestTask *pTestTask = g_theTCtrlCntrApp->GetMttTestTask();
	
	if (pItem->m_strDatasetPath == g_strwSysPara)
	{
		if (pItem->m_nShow == 0)
		{
			long nDatasCount = 0;
			pItem->InitDataList(nDatasCount);
			return FinishTestItemSysParaEdit(pItem);
		}
	}

    if (g_theTCtrlCntrApp->IsTestMode_Report())
	{
		return TestItemSysParaEdit_Test(pItem);
	}

	if (pTestTask == NULL)
	{
		return TestItemSysParaEdit_Test(pItem);
	}
	
	//当前测试的报告不是任务中的项目
	CTestProject *pProject = pTestTask->FindByGbrptFile(m_strGbBinaryFile);

	if (pProject == NULL)
	{
		return TestItemSysParaEdit_Test(pItem);
	}

	//系统参数
	if (pItem->m_strDatasetPath != g_strwSysPara)
	{
		return TestItemSysParaEdit_Test(pItem);
	}
	else
	{
		if (pItem->m_nShow == 0)
		{
			long nDatasCount = 0;
			pItem->InitDataList(nDatasCount);
			return FinishTestItemSysParaEdit(pItem);
		}
	}

	//从TestTask参数获取系统参数
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CDataSet *pSysParas = pDevice->GetSysParas();
	CDvmDataset *pTaskSysParas = pTestTask->GetTaskSysParas(FALSE);

	//没有测试任务系统参数或者当前测试任务时第一个测试
	if (pTaskSysParas == NULL || pTestTask->FindProjectIndex(pProject) == 0)
	{
		long nDatasCount = 0;
		pItem->InitDataList(nDatasCount);
		return TestItemSysParaEdit_Test(pItem);
	}
	else
	{
		if (pProject->IsTestParaEditMode_UseOwn())
		{
			long nDatasCount = 0;
			pItem->InitDataList(nDatasCount);
			return FinishTestItemSysParaEdit(pItem);
		}
		else// if (pProject->IsTestParaEditMode_OnlyPopEdit())
		{
			pSysParas->InitValueByDvmDataset(pTaskSysParas, TRUE, dvm_dataset_find_mode_name_id());
			long nDatasCount = 0;
			pItem->InitDataList(nDatasCount);
			return FinishTestItemSysParaEdit(pItem);
		}
	}

#else

	return 0;

#endif
}

long CTestControl::TestItemSysParaEdit_Test(CSysParaEdit* pItem)
{
#ifndef GUIDEBOOK_DEV_MODE
	if(m_pSysParaEditDlg == NULL)
	{
#ifdef _UITEST_USE_DIALOGEX
		m_pSysParaEditDlg = new CSysParaEditDlg(m_pParentWnd);
		m_pSysParaEditDlg->SetUseModeless();
		m_pSysParaEditDlg->DoModal();
#else
		m_pSysParaEditDlg = new CSysParaEditDlg;
		m_pSysParaEditDlg->Create(UI_GetSysParaEditDialogID(),m_pParentWnd);
#endif
		m_pSysParaEditDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pSysParaEditDlg->ShowWindow(SW_SHOW);
	}

	//获取本项目的最后一次报告数据
	m_pSysParaEditDlg->InitTestItem(pItem, m_pTCtrlWnd);
#endif

	return 0;
}

long CTestControl::ViewSysPara(const CString &strSysParaID, CGbItemBase *pCurrSelItem)
{
#ifndef GUIDEBOOK_DEV_MODE
	if(m_pSysParaViewDlg == NULL)
	{
#ifdef _UITEST_USE_DIALOGEX
		m_pSysParaViewDlg = new CSysParaEditDlg(m_pParentWnd);
		m_pSysParaViewDlg->SetUseModeless();
		m_pSysParaViewDlg->DoModal();
#else
		m_pSysParaViewDlg = new CSysParaEditDlg;
		m_pSysParaViewDlg->Create(UI_GetSysParaEditDialogID(),m_pParentWnd);
#endif
		m_pSysParaViewDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pSysParaViewDlg->ShowWindow(SW_SHOW);
	}

	CDevice *pDevice = (CDevice*)pCurrSelItem->GetAncestor(GBCLASSID_DEVICE);
	//获取本项目的最后一次报告数据
	m_pSysParaViewDlg->InitTestItem(strSysParaID, m_pTCtrlWnd, pDevice);
#endif
	return 0;
}

void CTestControl::ShowItemReportDsv(CExBaseObject *pGbItem, CReport *pReport)
{
	if ( pGbItem->GetClassID() == GBCLASSID_COMMCMD )
	{
		CCommCmd *pCommCmd = (CCommCmd*)pGbItem;
		CDvmDataset *pRptDataset = NULL;

		if (pCommCmd->RunDsvScript(&pRptDataset, pReport, FALSE))
		{
			CWnd *pParent = NULL;
			pParent = m_oTCtrlMsgRcv.m_pTCtrlMsgRcvWnd;
			CDsvViewResultDialog dlg(pParent);

			dlg.SetImageList(g_theTCtrlCntrApp->m_nDsvImage);
			dlg.m_pDsvDataset = pRptDataset;
			dlg.m_pDsvScript = pCommCmd->GetDsvScript();

			dlg.DoModal();

			return;
		}
	}
}

BOOL CTestControl::ExecuteTestItemCommCmd(CCommCmd* pItem)
{
	CCmd *pCmd = pItem->GetCmd();
	CReport *pReport = AddReport(pItem, pCmd->m_nRepeatTimes, m_nCommCmdTestTimes);//2017.05.17

	if ((m_pItemsRsltExprScript != NULL) && (m_nItemsRsltExprScriptTimeIgnore > 0) )
	{
		m_oItemsRsltExprScriptTimeTick.Enter();
	}
	
	//启动通讯命令前延时
	CString strSyntax;
	pItem->RunInitScriptScript(strSyntax);
	long nDelay = GetDelayBeforeCmd(pItem);

	if (nDelay > 0)
	{
		m_pTCtrlWnd->m_pTestItemRef = pItem;
		m_pTCtrlWnd->SetTestTimer(TIMER_DELAY_BEFORE_CMM_CMD, nDelay);
	}
	else
	{
		//如果不需要延时，则直接开始测试
		ExcuteCommCmdOnDelayBeforeFinish(pItem);
	}

	ExecuteTestItemCommCmd_ViewDlg(pItem);

	return TRUE;
}

BOOL CTestControl::ExecuteTestItemCommCmd_ViewDlg(CCommCmd* pItem)
{
	//创建对话框
	CreatemUICommCmdViewDlg(NULL);

	m_pUICommCmdViewDlg->InitTestItem(pItem, m_strGbBinaryFileName);

	if (m_pItemsRsltExprScript != NULL)
	{
		m_pUICommCmdViewDlg->InitTestItem(m_nItemsRsltExprScriptMaxRead
			, m_nItemsRsltExprScriptIndex+1
			, m_nItemsRsltExprScriptTimerLong);
	}
	else
	{
		m_pUICommCmdViewDlg->InitTestItem(-1, -1, -1);
	}

	long nDelay = GetDelayBeforeCmd(pItem);

	if (nDelay > 0)
	{
		m_pUICommCmdViewDlg->ShowCommMessage(g_sLangTxt_ComictnFront/*_T("通讯前延时")*/, TRUE);
		m_pUICommCmdViewDlg->m_nIDEvent = TIMER_DELAY_BEFORE_CMM_CMD;
	}
	else
	{
		m_pUICommCmdViewDlg->ShowCommMessage(g_sLangTxt_Communtioning/*_T("通讯中.......")*/, TRUE);
	}

	AdjustSafetyComCmdDlgPos();

	return TRUE;
}

//通讯命令测试
long CTestControl::CreatemUICommCmdViewDlg(LPVOID pUIViewDlg)
{
	CUICommCmdViewDlg *pUICommCmdViewDlg = (CUICommCmdViewDlg*)pUIViewDlg;

	if (pUICommCmdViewDlg == NULL)
	{
		if (m_bUICommCmdViewDlgRef)
		{
			if (m_pUICommCmdViewDlg != NULL)
			{
				return 0;
			}
		}

		if (m_pUICommCmdViewDlg == NULL)
		{
#ifdef _UITEST_USE_DIALOGEX
			m_pUICommCmdViewDlg = new CUICommCmdViewDlg(m_pParentWnd);
			m_pUICommCmdViewDlg->SetUseModeless();
			m_pUICommCmdViewDlg->DoModal();
#else
			m_pUICommCmdViewDlg = new CUICommCmdViewDlg();
			m_pUICommCmdViewDlg->Create(UI_GetCommCmdAttrDialogID(),m_pParentWnd);
#endif

		}

		m_pUICommCmdViewDlg->m_pTestCtrlWndRef = m_pTCtrlWnd;
	}
	else
	{
		if (!m_bUICommCmdViewDlgRef)
		{
			if (m_pUICommCmdViewDlg != NULL)
			{
				m_pUICommCmdViewDlg->DestroyWindow();
				delete m_pUICommCmdViewDlg;
				m_pUICommCmdViewDlg = NULL;
			}
		}

		m_pUICommCmdViewDlg = pUICommCmdViewDlg;
		m_bUICommCmdViewDlgRef = TRUE;
	}


	return 0;
}

void CTestControl::HideCommCmdAttrDlg()
{
	if(m_pUICommCmdViewDlg != NULL)
	{
		m_pUICommCmdViewDlg->ShowCommMessage(_T(""), FALSE);
		m_pUICommCmdViewDlg->ShowCommViewDlg(SW_HIDE);
	}
}


long CTestControl::UpdateStateAfterFinishTestItem(CGbItemBase* pItem, BOOL bNeedFireMsg)
{
	CTestControlBase::UpdateStateAfterFinishTestItem(pItem, bNeedFireMsg);

	if (m_pInlegibleTestItemViewGrid == NULL)
	{
		return 0;
	}

	if (pItem->GetState() == TEST_STATE_INLEGIBLE)
	{
		m_pInlegibleTestItemViewGrid->AddItem(pItem);
	}
	else
	{
		m_pInlegibleTestItemViewGrid->RemoveItem(pItem);
	}
	
	return 0;
}

void CTestControl::AddRecordReport(CGbItemBase* pItem)
{
	//不保存录波数据到报告中
	if (!g_theSmartTestBaseApp->GetAddRecorderReport())
	{
		return;
	}

	//使用录波组件
	if (g_theSmartTestBaseApp->GetAddRecorderReport_Recorder())
	{
		if (!g_theSmartTestBaseApp->HasRecorder())
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Has no recorder!"));
			return;
		}

		g_theSmartTestBaseApp->InitRecorder(this);
		CRecorderInterface* oRecorder = g_theSmartTestBaseApp->GetRecorder();

		if(!oRecorder->IsConnectSucc())
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Recorder connect failed!"));
			return;
		}
	}
	else
	{
		if (!g_theSmartTestBaseApp->HasPpEngine())
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Has no PpEngine, can not call record!"));
			return;
		}
	}

	CMacroTest *pMacroTest = (CMacroTest *)pItem;
	CString strRecordFile;
	strRecordFile.Format(_T("%d_%s"), m_pCurrTestItem->m_nIndex, m_pCurrTestItem->m_strName);
	strRecordFile = m_strGbBinaryFileName + _P_FOLDER_PATH_SEPARATOR_ + strRecordFile;
	
	if (pMacroTest->m_nTestTimes > 0)
	{
		strRecordFile.AppendFormat(_T("%d"), pMacroTest->m_nTestTimes+1);
	}

	CRecorderDlg dlg;
	dlg.m_pMacroTest = pMacroTest;
	dlg.m_strRecordFile = strRecordFile;

	if (dlg.DoModal() == IDCANCEL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_CallRecordFail /*_T("调用录波文件失败")*/);
		return;
	}

	pMacroTest->m_nTestTimes++;

	CReport *pReport = m_pCurrTestItem->GetReport(-1);
	CValues *pValues = pReport->m_pValues;
	CValue *pValue = (CValue*)pValues->FindByID(g_strRecordResultKey);

	if (pValue == NULL)
	{
		pValue = pValues->AddValue(g_strRecordResultKey, strRecordFile);
	}
	else
	{
		pValue->m_strValue = strRecordFile;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_ReadRecordFileS /*_T("读取录波文件：【%s】")*/, strRecordFile);
}

void CTestControl::AdjustSafetyComCmdDlgPos()
{
	if (m_pSafetyDlg == NULL)
	{
		return;
	}

	if (m_pUICommCmdViewDlg == NULL)
	{
		return;
	}

	if (!m_pSafetyDlg->IsWindowVisible())
	{
		return;
	}

	if (!m_pUICommCmdViewDlg->IsWindowVisible())
	{
		return;
	}

	CRect rcSafety, rcComCmd;
	m_pSafetyDlg->GetWindowRect(&rcSafety);
	m_pUICommCmdViewDlg->GetWindowRect(&rcComCmd);

	long nHeightSafety = rcSafety.Height();
	long nHeightCommCmd = rcComCmd.Height();
	long nHeightScreen = ::GetSystemMetrics(SM_CYSCREEN);
	
	long nOffSafety = (nHeightScreen - nHeightSafety - nHeightCommCmd) / 2 - rcSafety.top;
	rcSafety.OffsetRect(0, nOffSafety);

	long nOffComm = nHeightScreen - (nHeightScreen - nHeightSafety - nHeightCommCmd) / 2 - rcComCmd.bottom;
	rcComCmd.OffsetRect(0, nOffComm);

	m_pSafetyDlg->MoveWindow(rcSafety);
	m_pUICommCmdViewDlg->MoveWindow(rcComCmd);
}

void CTestControl::AttachItemViewGrid(void *pGrid, BOOL bUpdateGrid)
{
	m_pInlegibleTestItemViewGrid = (CTestItemViewGrid *)pGrid;

	if (bUpdateGrid)
	{
		CExBaseList oList;
		GetAllInlegibleTestItems(&oList, m_pGuideBook);
		m_pInlegibleTestItemViewGrid->ShowItems(&oList);
		oList.RemoveAll();
	}
}


long CTestControl::TestNextSubItem(CGbItemBase* pCurrSubItem)
{
	//m_dwReserved：用于记录和保存SystemReport的表格，清空
	ClearSysRptFill(m_pCurrSubTestItem);

	if (m_nStopTestByError == 1)
	{
		if (g_nLog_TestControl_Msg == 1)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("TestNextSubItem::m_nStopTestByError == 1"));
		}

		m_pCurrTestItem = NULL;
		m_pCurrSubTestItem = NULL;
		return 0;
	}

	ASSERT (m_pCurrSubTestItem != NULL);

	//是否作为实验中的提示信息出现
	long nClassID = m_pCurrTestItem->GetClassID();
	ASSERT (pCurrSubItem == m_pCurrSubTestItem);
	//ASSERT (nClassID == GBCLASSID_MACROTEST);
	BOOL bSubTestFinish = FALSE;

	//如果当前项目处于“m_nBreakLoopState == 1”状态，则结束跳出
	if (GBS_CanBreakLoop(m_pCurrTestItem))//if (m_pCurrTestItem->m_nBreakLoopState == 1)
	{
		bSubTestFinish = TRUE;
		m_pCurrSubTestItem = NULL;
	}
	else if (m_pItemContainer->GetGotoItem() != NULL)
	{
		bSubTestFinish = TRUE;
		m_pCurrSubTestItem = NULL;
	}
	else
	{
		GetNextTestSubItem();

		if (m_pCurrSubTestItem == NULL)
		{
			bSubTestFinish = TRUE;
		}
	}

	//if (GetNextTestSubItem() == NULL)
	BOOL bCallMacroStopTestError = FALSE;

	if (bSubTestFinish)
	{//没有子项目，完成当前测试项目的测试
		switch  (nClassID )
		{
		case GBCLASSID_MACROTEST:
			try
			{
				if (m_pMacroTestInterface != NULL)
				{
					//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("     -- call MacroTest.FinishTest"));
					if (!IsVirtualVm())
					{
						if (g_nLog_TestControl_Msg == 1)
						{
							CLogPrint::LogString(XLOGLEVEL_TRACE, _T("TestNextSubItem::Set_TIMER_TEST_CTRL_MACROFINISH"));
						}

						if (!m_bMacroTestFinished)
						{
							m_pTCtrlWnd->Set_TIMER_TEST_CTRL_MACROFINISH();
						}
					}
					else
					{
						if (g_nLog_TestControl_Msg == 1)
						{
							CLogPrint::LogString(XLOGLEVEL_TRACE, _T("TestNextSubItem::Virtual VM"));
						}
					}

					if (g_nLog_TestControl_Msg == 1)
					{
						CLogPrint::LogString(XLOGLEVEL_TRACE, _T("TestNextSubItem::FinishTest(1)"));
					}

					if (!m_bMacroTestFinished)
					{
						m_pMacroTestInterface->FinishTest(1);
					}
					else
					{
						FinishTestItem(m_pCurrTestItem);
					}
				}
			}
			catch (...)
			{
				bCallMacroStopTestError = TRUE;
			}

			if (bCallMacroStopTestError)
			{
				try
				{
					if (g_nLog_TestControl_Msg == 1)
					{
						CLogPrint::LogString(XLOGLEVEL_TRACE, _T("     -- call StopTest"));
					}

					m_pMacroTestInterface->StopTest();
					m_pTCtrlWnd->PostMessage(WM_ELECTRIC_TEST, MTMSG_TestFinished, MTMSG_TestFinished);
				}
				catch (...)
				{
					CLogPrint::LogString(XLOGLEVEL_TRACE, _T("call StopTest error-----"));
				}
			}
			break;
		case GBCLASSID_SYSPARAEDIT:
#ifndef GUIDEBOOK_DEV_MODE
			ASSERT (m_pSysParaEditDlg != NULL);

			if (m_pSysParaEditDlg != NULL)
			{
				m_pSysParaEditDlg->FinishTestCmmCmdItem();
				m_pSysParaEditDlg->UIFinishTestItem();
			}
#endif
			break;

		case GBCLASSID_SAFETY:
			ASSERT (m_pSafetyDlg != NULL);

			if (m_pSafetyDlg != NULL)
			{
				CSafety *pSafety = (CSafety *)m_pCurrTestItem;

				//如果提示信息不跟随通讯命令结束，自不进行此操作
				if (GBS_CanBreakLoop(pSafety))//if (pSafety->m_nBreakLoopState == 1)
				{
					m_pSafetyDlg->FinishTestCmmCmdItem();
					m_pSafetyDlg->UIFinishTestItem();
				}
			}
			break;

		default:
			FinishTestItem(m_pCurrTestItem);
			break;
		}
	}
	else
	{
		TestItem(m_pCurrSubTestItem);
	}

	return 0;
}

long CTestControl::FinishCurrTestItem(CDataGroup *pDataGroup)
{
	if (m_pCurrTestItem == NULL)
	{
		return 0;
	}


	if (m_pCurrTestItem->GetClassID() == GBCLASSID_SAFETY)
	{
		CSafety *pSafety = (CSafety*)m_pCurrTestItem;
		SetVal_ShortDatas_by_DvmDatas(pDataGroup, pSafety->m_pDatas);

 		if (m_pSafetyDlg != NULL)
 		{
 			m_pSafetyDlg->PostMessage(WM_FINISH_INPUTDATA, 0, 0);
 		}
 		else
		{
			FinishTestItemSafety(pSafety);
		}

		return 1;
	}

	if (m_pCurrTestItem->GetClassID() == GBCLASSID_SYSPARAEDIT)
	{
		CSysParaEdit *pSysParaEdit = (CSysParaEdit*)m_pCurrTestItem;
		CExBaseList *pList = pSysParaEdit->GetSysParaEditDataObjList();
		Gb_InitValueByDvmDatas(pDataGroup, pList);
		FinishTestItemSysParaEdit(pSysParaEdit);
		return 1;
	}

	return 0;
}

void CTestControl::AddSysParasToTask(CSysParaEdit* pItem)
{
#ifndef GUIDEBOOK_DEV_MODE
   
    CTestTask *pTestTask = g_theTCtrlCntrApp->GetMttTestTask();

	if (pTestTask == NULL)
	{
		return ;
	}

	//当前测试的报告不是任务中的项目
	CTestProject *pProject = pTestTask->FindByGbrptFile(m_strGbBinaryFile);

	if( pProject  == NULL)
	{
		return ;
	}

	//系统参数
	if (pItem->m_strDatasetPath != g_strwSysPara)
	{
		return ;
	}

	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CDataSet *pSysParas = pDevice->GetSysParas();
	CDvmDataset *pTaskSysParas = pTestTask->GetTaskSysParas(TRUE);

	if (pProject->IsTestParaEditMode_UseOwn())
	{
		//第一个项目，将参数添加到TestTask，否则不予处理
		if (0 == pTestTask->FindProjectIndex(pProject))
		{
			pSysParas->AddToDvmDataset(pTaskSysParas);
			pTestTask->Save();
		}
	}
	else
	{
		pSysParas->AddToDvmDataset(pTaskSysParas);
		pTestTask->Save();
	}
#endif
}

long CTestControl::FinishTestItemCommCmd(CCommCmd* pItem)
{
	Gb_SetGbModifiedFlag(m_pGuideBook, TRUE);

	if (pItem == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CommunFalse2/*L"通讯过程中出现错误，Item==NULL"*/);
		return 0;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_NotCommunCmd/*L"通讯过程中出现错误，不是通讯命令"*/);
		return 0;
	}

	CCmd *pCmd = pItem->GetCmd();
	BOOL bFinish = FALSE;

	//处理通讯命令的后续项目，例如：投退压板，每次只能投退一个压板
	ContinueTestCommCmd(pItem, bFinish);

	//if (bFinish)
	{
		long nDelay = GetDelayAfterCmd(pItem);

		if (nDelay > 0)
		{
			m_pTCtrlWnd->m_pTestItemRef = pItem;
			m_pUICommCmdViewDlg->ShowCommMessage(g_sLangTxt_ComictnLater/*_T("通讯后延时")*/, TRUE);
			m_pUICommCmdViewDlg->m_nIDEvent = TIMER_DELAY_AFTER_CMM_CMD;
			m_pTCtrlWnd->SetTimer(TIMER_DELAY_AFTER_CMM_CMD, nDelay, NULL);
		}
		else
		{
			if (m_pItemsRsltExprScript == NULL)
			{
				m_pUICommCmdViewDlg->ShowCommMessage(_T(""), FALSE);
			}
			else
			{
				m_pUICommCmdViewDlg->ShowCommMessage(g_sLangTxt_Communtioning/*_T("通讯中.......")*/, FALSE);
			}

			//如果不需要延时，则直接处理结束
			ExcuteCommCmdOnDelayAfterFinish(pItem);
		}
	}

	return 0;
}

void CTestControl::RcdAnalyse(const CString &strTestFile)
{
	CRecorderInterface *pRecord = g_theSmartTestBaseApp->GetRecorder();

	if (pRecord == NULL)
	{
		return;
	}

	pRecord->RcdAnalyse(strTestFile);

	//获取结果数据
}

BOOL CTestControl::ProcessAfterCommCmdFinish(CCommCmd *pCommCmd)
{
	//如果没有测试完成
	if (m_pItemsRsltExprScript == NULL)
	{
		return TRUE;
	}

	//测试合格，返回
	if (pCommCmd->GetRsltJdg() == 1)
	{
		return TRUE;
	}

	if (m_nItemsRsltExprScriptIndex < m_nItemsRsltExprScriptMaxRead)
	{
		//添加多份报告数据，如果是读SOE项目，则不添加多次报告数据
		if (!pCommCmd->IsReadSoe())
		{
			CCmd *pCmd = pCommCmd->GetCmd();
			CReport *pReport = AddReport(pCommCmd, pCmd->m_nRepeatTimes, m_nCommCmdTestTimes);//2017.05.17
		}

		pCommCmd->SetState(TEST_STATE_TESTING);
		Gb_UpdateGbItemParentTestState(pCommCmd);
		m_pTCtrlWnd->SetTimer(TIMER_DELAY_CMM_CMD_ITEMSEXPR, m_nItemsRsltExprScriptTimerLong, NULL);
		m_pUICommCmdViewDlg->InitTestItem(m_nItemsRsltExprScriptMaxRead, m_nItemsRsltExprScriptIndex+1, m_nItemsRsltExprScriptTimerLong);
		m_pUICommCmdViewDlg->ShowCommMessage(_T("通讯中......."), TRUE);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


//执行过程
BOOL CTestControl::RunProcedure(const CString &bstrProcedureID, const CString & bstrDatasetPath
								, WPARAM wParam, LPARAM lParam, UINT nProcedureType, HWND hMsgRcvWnd)
{
	try
	{
		if (m_pUICommCmdViewDlg)
		{
			m_pUICommCmdViewDlg->ShowCommMessage(g_sLangTxt_Communtioning/*_T("通讯中.......")*/, TRUE);
		}
	}
	catch(...)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("m_pUICommCmdViewDlg->ShowCommMessage : Error......"));
	}

	return CTestControlBase::RunProcedure(bstrProcedureID, bstrDatasetPath, wParam, lParam, nProcedureType, hMsgRcvWnd);
}

long CTestControl::GBS_RcdSetPath(CGbItemBase *pItem, long nAppendItemPath, const CString &strRcdFilePathRoot, long nAppendTestTimeDir)
{
	CString strRcdFilePath;
	strRcdFilePath = GBS_RcdGetPath(pItem, nAppendItemPath, strRcdFilePathRoot, nAppendTestTimeDir);

	::CreateAllDirectories(strRcdFilePath);
	CProtocolDeviceInterface* oPpDevice = GetDevicePtr();
	oPpDevice->SetAttrByID(g_strPpEngineRecordFilePathKey, strRcdFilePath);

	CReport *pReport = pItem->GetReport(-1);
	CString strTemp;
	strTemp = _P_GetWorkspacePath();
	strTemp = strRcdFilePath.Mid(strTemp.GetLength());
	pReport->AddValue(g_strPpEngineRecordFilePathKey, strTemp);

	return 0;
}

CString CTestControl::GBS_RcdGetPath(CGbItemBase *pItem, long nAppendItemPath, const CString &strRcdFilePathRoot, long nAppendTestTimeDir)
{
	CString strRcdFilePath;
	long nPos = m_strGbBinaryFile.ReverseFind('.');
	strRcdFilePath = m_strGbBinaryFile.Left(nPos);
	strRcdFilePath += _P_FOLDER_PATH_SEPARATOR_;

	if (nAppendItemPath == 1)
	{
		strRcdFilePath.AppendFormat(_T("%s\\"), pItem->m_strName);
	}
	else if (nAppendItemPath == 2)
	{
		strRcdFilePath.AppendFormat(_T("%d\\"), pItem->m_nIndex);
	}
	else if (nAppendItemPath == 3)
	{
		strRcdFilePath.AppendFormat(_T("%d_%s\\"), pItem->m_nIndex, pItem->m_strName);
	}

	if (strRcdFilePathRoot.GetLength() > 0)
	{
		strRcdFilePath.AppendFormat(_T("%s\\"), strRcdFilePathRoot);
	}

	if (nAppendTestTimeDir)
	{
		if (pItem->GetClassID() == GBCLASSID_COMMCMD
			|| pItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			strRcdFilePath.AppendFormat(_T("%d\\"), pItem->GetReports()->GetCount());
		}
	}

	return strRcdFilePath;
}

long CTestControl::GBS_RecordCmd(const char *pszCmdID, const char *pszCmdPara)
{
   
	
    if (!g_theSmartTestBaseApp->HasRecorder())
	{
		return 0;
	}

	CRecorderDlg dlg;
	dlg.m_pMacroTest = NULL;
	dlg.m_strRecordFile.Empty();
	dlg.m_strCmdID   = pszCmdID;
	dlg.m_strCmdPara = pszCmdPara;

	if (dlg.DoModal() == IDCANCEL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_CallRecordFail2 /*_T("调用录波命令失败")*/);
		return 0;
	}

	return 1;
}

long CTestControl::GBS_RcdSetProgID(const char* pszRcdProgID)
{
   

	CString strProgID;
	strProgID = pszRcdProgID;
    g_theSmartTestBaseApp->SetRecorderProgID(strProgID);
	
	return 0;
}

long CTestControl::GBS_RcdExit()
{
   
    g_theSmartTestBaseApp->ReleaseRecorder();

	return 0;
}

long CTestControl::GBS_RcdConfig(const char* pszPara)
{
   

    if (!g_theSmartTestBaseApp->HasRecorder())
	{
		return 0;
	}

    g_theSmartTestBaseApp->InitRecorder(this);
	
	CRecorderDlg dlg;
	dlg.m_pMacroTest = NULL;
	dlg.m_strRecordFile.Empty();
	dlg.AddRecordOptr(RECORD_OPTR_CONFIG);

	if (dlg.DoModal() == IDCANCEL)
	{
		m_bSafetyScriptStopByRecord = TRUE;
		CLogPrint::LogString(XLOGLEVEL_TRACE,g_sLangTxt_CallCmdFail/* _T("调用命令失败")*/);
	}

	return 0;
}

long CTestControl::GBS_RcdSelect(const char* pszPara)
{
   

    if (!g_theSmartTestBaseApp->HasRecorder())
	{
		return 0;
	}

    g_theSmartTestBaseApp->InitRecorder(this);

	CString strPara;
	strPara = pszPara;
	CDvmDataset oDatas;

    CRecorderInterface* oRecorder = g_theSmartTestBaseApp->GetRecorder();
	CString strXml = oRecorder->Select(strPara);
	BSTR bstrXml = strXml.AllocSysString();//oNode.GetXmlData();

	oDatas.SetXml(bstrXml,CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);

	::SysFreeString(bstrXml);
	CReport *pReport = m_pCurrTestItem->GetReport(-1);
	pReport->AddRptDvmDataset(oDatas);

	return 1;
}

long CTestControl::GBS_RcdValidate(const char* pszRsltID)
{
   

    if (!g_theSmartTestBaseApp->HasRecorder())
	{
		return 0;
	}

    g_theSmartTestBaseApp->InitRecorder(this);

	CString strPara;
	CDvmDataset oDatas;

    CRecorderInterface* oRecorder = g_theSmartTestBaseApp->GetRecorder();
	CString strXml = oRecorder->Validate(strPara);
	BSTR bstrXml = strXml.AllocSysString();//oNode.GetXmlData();
	oDatas.SetXml(bstrXml,CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);

	CReport *pReport = m_pCurrTestItem->GetReport(-1);
	pReport->AddRptDvmDataset(oDatas);
	::SysFreeString(bstrXml);

	CValue *pValue = pReport->FindReportData(CString(pszRsltID));
	pValue->m_strValue.Empty();

	if (pValue != NULL)
	{
		pValue->m_strValue.Empty();
		POS pos = oDatas.GetHeadPosition();
		CDvmData *pData = NULL;

		while (pos != NULL)
		{
			pData = (CDvmData *)oDatas.GetNext(pos);
			pValue->m_strValue.AppendFormat(_T("%s\r\n"), pData->m_strValue);
		}
	}

	return (pValue->m_strValue.GetLength() == 0);
}

long CTestControl::GBS_RcdCmpClear()
{
	g_theSmartTestBaseApp->InitRecorder(this);

	CRecorderInterface *pRecord = g_theSmartTestBaseApp->GetRecorder();

	if (pRecord == NULL)
	{
		return 0;
	}

	return pRecord->RcdCmpClear();
}

long CTestControl::GBS_RcdCmp(const char* pszStdFile, const char* pszTestFile)
{
	g_theSmartTestBaseApp->InitRecorder(this);
	CRecorderInterface *pRecord = g_theSmartTestBaseApp->GetRecorder();

	if (pRecord == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("GetRecorder error"));
		return 0;
	}

	CString strStdFile, strTestFile;
	CString strRcdFilePath;
	CGbItemBase *pRcdCmpItem = m_pCurrTestItem;
	CReport *pReport = NULL;
	
	if (0 == GBS_RcdCmp_GetFiles(pszStdFile, pszTestFile, strStdFile, strTestFile, &pRcdCmpItem))
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("GBS_RcdCmp_GetFiles error"));
		return 0;
	}

	if (!IsFileExist(strStdFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RcdCmp: std file not exist [%s]"), strStdFile);
		return 0;
	}

	if (!IsFileExist(strTestFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RcdCmp: std file not exist [%s]"), strTestFile);
		return 0;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RcdCmp [%s] [%s]"), strStdFile, strTestFile);
	RcdCmp(strStdFile, strTestFile);

	CString strResult;
	CDvmDataset oDatas;
	BSTR bstrXml = NULL;
	
	strResult = pRecord->GetResult();
	bstrXml = strResult.AllocSysString();
	oDatas.SetXml(bstrXml,CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
	::SysFreeString(bstrXml);
	//pReport->AddRptDvmDataset(oDatas);

	//复制报告数据
	pReport = pRcdCmpItem->GetReport(-1);
	pReport->AddReportDataset(&oDatas);//pReport->m_pRptDvmDataset);

	//取相对路径
	strRcdFilePath = GetPathFromFilePathName(m_strGbBinaryFile);
	long nPos = strRcdFilePath.GetLength();
	strStdFile = strStdFile.Mid(nPos);
	strTestFile = strTestFile.Mid(nPos);
	pReport->AddValue(g_strRecordCmpStdFile, strStdFile );
	pReport->AddValue(g_strRecordCmpTestFile, strTestFile );
// 	pReport->AddValue(g_strRecordCmpStdFile, GetPathFileNameFromFilePathName(strStdFile) );
// 	pReport->AddValue(g_strRecordCmpTestFile, GetPathFileNameFromFilePathName(strTestFile) );

	//处理录波对比图形的数据相对路径
	CValue *pValue = (CValue*)pReport->m_pValues->FindByID(_T("Cmp_bmp_file"));

	if (pValue != NULL)
	{
		strStdFile = GetPathFromFilePathName(strStdFile);
		pValue->m_strValue = strStdFile + pValue->m_strValue;
	}

	return 0;
}

CCommCmd* CTestControl::GBS_RcdCmp_GetCommCmd()
{
	if (m_pCurrSubTestItem != NULL)
	{
		if (m_pCurrSubTestItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			return (CCommCmd*)m_pCurrSubTestItem;
		}
	}

	if (m_pCurrTestItem != NULL)
	{
		if (m_pCurrTestItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			return (CCommCmd*)m_pCurrTestItem;
		}
	}

	return NULL;
}

CString CTestControl::GBS_RcdGetRcdDestPath(BOOL bIsFullPath)
{
	CString strRcdFilePath;

	if (bIsFullPath)
	{
		strRcdFilePath = GetPathFromFilePathName(m_strGbBinaryFile);
	}

	if (g_strRcdFilePathRoot.GetLength() > 0)
	{
		strRcdFilePath += g_strRcdFilePathRoot;
		ValidatePath(strRcdFilePath);
	}

	if (g_bCreateTestTimesDir != 0)
	{
		long nCount = m_pCurrTestItem->GetReports()->GetCount();
		strRcdFilePath.AppendFormat(_T("%d\\"), nCount);
	}

	return strRcdFilePath;
}

long CTestControl::GB_GetFullPath(CGbItemBase *pCurrItem, CString &strFile)
{
	CString strRetPath;
	BOOL bRet = _P_GetFullPathEx(strFile, strRetPath);

	if (bRet)
	{
		strFile = strRetPath;
	}

	if (Parse_Item_File_Path(pCurrItem, strFile, strFile))
	{
	}
	else if (Parse_Report_File_Path(pCurrItem, strFile, strFile))
	{
		
	}

	return strFile.GetLength();
}

long CTestControl::GBS_RcdCmp_GetFiles(const char* pszStdFile, const char* pszTestFile, CString &strStdFile, CString &strTestFile, CGbItemBase **ppRcdCmpItem)
{
	CString strRcdFilePath;
	CGbItemBase *pRcdCmpItem = m_pCurrTestItem;
	CReport *pReport = NULL;
	strRcdFilePath = GBS_RcdGetRcdDestPath(TRUE);//GetPathFromFilePathName(m_strGbBinaryFile);

	strStdFile = pszStdFile;
	strTestFile = pszTestFile;

	GB_GetFullPath(m_pCurrTestItem, strStdFile);
	GB_GetFullPath(m_pCurrTestItem, strTestFile);
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RcdCmp([%s],[%s]"), strStdFile, strTestFile);

	if (strTestFile.GetLength() <= 4)
	{
		CCommCmd *pCommCmd = GBS_RcdCmp_GetCommCmd();

		if (pCommCmd == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("RcdCmp命令没有对应的通讯命令"));
			return 0;
		}

		pReport = pCommCmd->GetReport(-1);

		if (pReport == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("RcdCmp命令没有报告数据"));
			return  0;
		}

		strTestFile = pReport->GetLastRcdFile();

		if (strTestFile.GetLength() < 4)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("扩展报告数据为空"));
			return  0;
		}

		pRcdCmpItem = pCommCmd;
	}

	if (strTestFile.GetAt(1) != ':')
	{
		strTestFile = strRcdFilePath + strTestFile;
	}

	if (strStdFile.GetLength() <= 4)
	{
		CString strStdSrcFile;
		strStdSrcFile = _P_GetXPath(g_strRecordComtradePath);
		strStdSrcFile += g_strRecordDefaultComtradeFile;

		strStdFile = strTestFile;
		long nPos = strStdFile.ReverseFind('.');
		
		if (nPos < 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("file error:%s"), strStdFile);
			return 0;
		}

		strStdFile = strStdFile.Left(nPos);
		strStdFile += _T("_std.cfg");

		GBS_RcdCmp_CopyStdFile(this, strStdSrcFile, strStdFile);
	}
	else
	{
		if (strStdFile.GetAt(1) != ':')
		{
			strStdFile = strRcdFilePath + strStdFile;
		}
	}

	*ppRcdCmpItem = pRcdCmpItem;

	return 1;
}

long CTestControl::GBS_RcdAnalyse_GetFile(const char* pszRcdFile, CString &strRcdFile, CGbItemBase **ppRcdCmpItem)
{
	CString strRcdFilePath;
	CGbItemBase *pRcdCmpItem = m_pCurrTestItem;
	CReport *pReport = NULL;
	strRcdFilePath = GBS_RcdGetRcdDestPath(TRUE);//GetPathFromFilePathName(m_strGbBinaryFile);

	strRcdFile = pszRcdFile;

	if (strRcdFile.GetLength() <= 4)
	{
		CCommCmd *pCommCmd = GBS_RcdCmp_GetCommCmd();

		if (pCommCmd == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("RcdCmp命令没有对应的通讯命令"));
			return 0;
		}

		pReport = pCommCmd->GetReport(-1);

		if (pReport == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("RcdCmp命令没有报告数据"));
			return  0;
		}

		strRcdFile = pReport->GetLastRcdFile();

		if (strRcdFile.GetLength() < 4)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("扩展报告数据为空"));
			return  0;
		}

		pRcdCmpItem = pCommCmd;
	}

	strRcdFile = strRcdFilePath + strRcdFile;
	*ppRcdCmpItem = pRcdCmpItem;

	return 1;
}

long CTestControl::GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile)
{
	strStdSrcFile = ChangeFilePostfix(strStdSrcFile, _T("cfg"));
	strStdDestFile = ChangeFilePostfix(strStdDestFile, _T("cfg"));

	if (!::X_CopyFile(strStdSrcFile, strStdDestFile, FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("failed copy:%s==>>%s"), strStdSrcFile, strStdDestFile);
	}

	strStdSrcFile = ChangeFilePostfix(strStdSrcFile, _T("dat"));
	strStdDestFile = ChangeFilePostfix(strStdDestFile, _T("dat"));

	if (!::X_CopyFile(strStdSrcFile, strStdDestFile, FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("failed copy:%s==>>%s"), strStdSrcFile, strStdDestFile);
	}

	return 0;
}

long CTestControl::GBS_RcdCopyFile(const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir)
{
	CString strSrcFile, strDestFile;
	CString strRcdFilePath;

	//////////////////////////////////////////////////////////////////////////
	strRcdFilePath = GetPathFromFilePathName(m_strGbBinaryFile);

	//创建路径
	if (nCreateTestTimesDir == 1)
	{
		long nCount = m_pCurrTestItem->GetReports()->GetCount();
		strRcdFilePath.AppendFormat(_T("%d\\"), nCount);
	}

	strSrcFile = pszSrcFile;
	strDestFile = pszDestFile;
	
	CString strStdSrcFilePath;
	strStdSrcFilePath = _P_GetXPath(g_strRecordComtradePath);

	//	如果文件为空，表示MR1200的录波文件“e-Report\Comtrade\CurrentRecord.cfg/dat”
	if (strSrcFile.GetLength() <= 4)
	{
		strSrcFile = g_strRecordDefaultComtradeFile;
	}

	if (strDestFile.GetLength() == 0)
	{
		strDestFile = strSrcFile;
	}
	else
	{
		long nPos = strDestFile.ReverseFind('.');

		if (nPos < 0)//	如果为相对路径信息，则表示将源文件拷贝到测试报告指定的路径下
		{
			ValidatePath(strDestFile);
			strDestFile += GetPathFileNameFromFilePathName(strSrcFile);
		}
	}

	strDestFile = strRcdFilePath + strDestFile;
	strSrcFile = strStdSrcFilePath + strSrcFile;

	strRcdFilePath = GetPathFromFilePathName(strDestFile);
	CreateAllDirectories(strRcdFilePath);

	GBS_RcdCmp_CopyStdFile(this, strSrcFile, strDestFile);

	return 0;
}


long CTestControl::GBS_RcdAnalyse(const char* pszRcdFile)
{
	g_theSmartTestBaseApp->InitRecorder(this);
	CRecorderInterface *pRecord = g_theSmartTestBaseApp->GetRecorder();

	if (pRecord == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("GetRecorder error"));
		return 0;
	}

	CString strTestFile;
	CString strRcdFilePath;
	CGbItemBase *pRcdCmpItem = m_pCurrTestItem;
	CReport *pReport = NULL;

	if (0 == GBS_RcdAnalyse_GetFile(pszRcdFile, strTestFile, &pRcdCmpItem))
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("GBS_RcdAnalyse_GetFile error"));
		return 0;
	}

	if (!IsFileExist(strTestFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RcdAnalyse: record file not exist [%s]"), strTestFile);
		return 0;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RcdAnalyse [%s]"), strTestFile);
	RcdAnalyse(strTestFile);

	CString strResult;
	CDvmDataset oDatas;
	BSTR bstrXml = NULL;

	strResult = pRecord->GetResult();
	bstrXml = strResult.AllocSysString();
	oDatas.SetXml(bstrXml,CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
	::SysFreeString(bstrXml);
	//pReport->AddRptDvmDataset(oDatas);

	//复制报告数据
	pReport = pRcdCmpItem->GetReport(-1);
	pReport->AddReportDataset(&oDatas);//pReport->m_pRptDvmDataset);

	//取相对路径
	strRcdFilePath = GetPathFromFilePathName(m_strGbBinaryFile);
	long nPos = strRcdFilePath.GetLength();
	strTestFile = strTestFile.Mid(nPos);
	pReport->AddValue(g_strRecordCmpTestFile, strTestFile );

	//处理录波对比图形的数据相对路径
	CValue *pValue = (CValue*)pReport->m_pValues->FindByID(_T("Analyse_bmp_file"));

	if (pValue != NULL)
	{
		strTestFile = GetPathFromFilePathName(strTestFile);
		pValue->m_strValue = strTestFile + pValue->m_strValue;
	}

	return 0;
}

void CTestControl::Gbs_SetTmTriggerSecond(long nSecond, long nOptr)
{
	if (m_pUICommCmdViewDlg == NULL || m_pTCtrlWnd == NULL)
	{
		return;
	}

	m_pTCtrlWnd->Gbs_SetTmTriggerSecond(nSecond, nOptr);
}

void CTestControl::Gbs_SetTmTriggerCountMinute(long nMinute)
{
	if (m_pUICommCmdViewDlg == NULL || m_pTCtrlWnd == NULL)
	{
		return;
	}

	m_pTCtrlWnd->Gbs_SetTmTriggerCounter_Minute(nMinute);
}

void CTestControl::Gbs_EnterTmTrigger()
{
	if (m_pUICommCmdViewDlg == NULL || m_pTCtrlWnd == NULL)
	{
		return;
	}

	m_pTCtrlWnd->Gbs_EnterTmTrigger();
	m_pUICommCmdViewDlg->Gbs_EnterTimeTrigger();
}

void CTestControl::Gbs_StartTimerTigger()
{
	if (m_pUICommCmdViewDlg == NULL || m_pTCtrlWnd == NULL)
	{
		return;
	}

	m_pTCtrlWnd->Gbs_StartTmTrigger();
}

void CTestControl::Gbs_StopTimerTrigger()
{
	if (m_pUICommCmdViewDlg == NULL || m_pTCtrlWnd == NULL)
	{
		return;
	}

	m_pTCtrlWnd->Gbs_StopTmTrigger();
}

//2020-12-21  lijunqing
void CTestControl::ConfigVmEngine()
{
	if (m_pMacroTestInterface != NULL)
	{
		m_pMacroTestInterface->SetConfig(_T(""));
	}
	else
	{
		
	}
}

void CTestControl::ConfigPpEngine()
{
	
}

