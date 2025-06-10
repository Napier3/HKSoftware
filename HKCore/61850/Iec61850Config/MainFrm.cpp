// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Iec61850Config.h"

#include "MainFrm.h"
#include "IecConfigFrame.h"
#include "SclFileFrame.h"

#include "..\Module\IecCfgTool\IecCfgTool.h"
#include "..\..\System\Module\XAtsSysSvrClient.h"
#include "..\..\Module\System\TickCount32.h"
#include "TestEngine.h"

#define WM_ICON_NOTIFY WM_USER+10


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_IECCFG_FILE_PANE, &CMainFrame::OnViewIeccfgFilePane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IECCFG_FILE_PANE, &CMainFrame::OnUpdateViewIeccfgFilePane)
	ON_COMMAND(ID_VIEW_IECCFG_DEVICE_PANE, &CMainFrame::OnViewIeccfgDevicePane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IECCFG_DEVICE_PANE, &CMainFrame::OnUpdateViewIeccfgDevicePane)
	ON_COMMAND(ID_VIEW_IECCFG_FILEDEVICE_PANE, &CMainFrame::OnViewIeccfgDeviceFilePane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IECCFG_FILEDEVICE_PANE, &CMainFrame::OnUpdateViewIeccfgDeviceFilePane)
	ON_COMMAND(ID_VIEW_MODEL_USE_HARM, &CMainFrame::OnViewModelUseHarm)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODEL_USE_HARM, &CMainFrame::OnUpdateViewModelUseHarm)
	ON_COMMAND(ID_VIEW_VERIFY_VOL_CUR, &CMainFrame::OnVerifyVolCurChannel)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VERIFY_VOL_CUR, &CMainFrame::OnUpdateVerifyVolCurChannel)

	ON_COMMAND(ID_VIEW_LINK_GOUT, &CMainFrame::OnViewLinkGout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LINK_GOUT, &CMainFrame::OnUpdateViewLinkGout)
	ON_COMMAND(ID_VIEW_AUTO_OPEN_LAST, &CMainFrame::OnViewAutoOpenLast)
	ON_UPDATE_COMMAND_UI(ID_VIEW_AUTO_OPEN_LAST, &CMainFrame::OnUpdateViewAutoOpenLast)
	ON_COMMAND(ID_VIEW_OUTPUT, &CMainFrame::OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, &CMainFrame::OnUpdateViewOutput)
	ON_COMMAND(ID_FILE_IMPORT, &CMainFrame::OnFileImport)
	ON_COMMAND(ID_FILE_IMPORT_AT02D, &CMainFrame::OnFileImportAT02D)//周宏军 20200616  增加AT02配置
	ON_MESSAGE(WM_ELECTRIC_TEST, &CMainFrame::OnElectricTestMsg)
	ON_MESSAGE(WM_XATSSYSCLIENT, &CMainFrame::OnXAtsSvrClientMessage)
	ON_MESSAGE(WM_TRAYICON_NOTIFY, OnTrayNotification)
	ON_COMMAND(ID_TRAYICON_EXITAPP, &CMainFrame::OnAppExit)
	ON_MESSAGE(WM_ON_SETTING_DISP_MODE, CMainFrame::OnSetDispMode)
END_MESSAGE_MAP()
// 	ON_COMMAND(ID_FILE_SAVE, &CMainFrame::OnFileSave)
// 	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CMainFrame::OnUpdateFileSave)
// 	ON_COMMAND(ID_FILE_SAVE_AS, &CMainFrame::OnFileSaveAs)
// 	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CMainFrame::OnUpdateFileSaveAs)

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);
}

CMainFrame::~CMainFrame()
{
}


BOOL CMainFrame::XCopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists)
{
// 	CString strSrcDocFile = ChangeFilePostfix(strSrcFile, g_strDocFilePostfix);
// 	CString strDestDocFile = ChangeFilePostfix(strDestFile, g_strDocFilePostfix);
// 
// 	::CopyFile(strSrcFile, strDestFile, FALSE);
// 	::CopyFile(strSrcDocFile, strDestDocFile, FALSE);

	return TRUE;
}


DWORD CMainFrame::XOpenXFile(CXFile *pFile)
{
 	CString strFile = pFile->GetTotalFileName();
	CIecCfgFile *pIecFile = CIecCfgTool::FindIecFile(strFile);
	
	if (pIecFile != NULL)
	{
		if (pIecFile->GetClassID() == IFTCLASSID_CIECCFGFILE)
		{
			//激活当前文档
			CFrameWnd *pFrameWnd = pIecFile->GetRefFrameWnd();
			ASSERT (pFrameWnd != NULL);
			ASSERT (pFrameWnd->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)) );
			CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrameWnd;
			pIecConfigFrame->ActivateFrame(1);
		}
		else
		{
			m_wndIecfgDevicePane.ShowPane(TRUE, FALSE, TRUE);
		}
	}
	else
	{
// 		if (IsFileExist(strFile))
// 		{
// 			OpenIecfgFile(strFile,TRUE);
// 		}
// 		else
		{
			OpenIecfgFile(strFile,FALSE);
		}
		
// 		pIecFile = theApp.OpenIecCfgFile(strFile);
// 		theApp.UpdateIecCfgFilesComboBox();
// 
// 		if (pIecFile->GetClassID() == IFTCLASSID_CIECCFGFILE_DEVICE)
// 		{
// 			CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecFile;
// 			m_wndIecfgDevicePane.ShowPane(TRUE, FALSE, TRUE);
// 			m_wndIecfgDevicePane.ShowIecfgDevice(pIecCfgFileDevice);;
// 		}
	}
// 
// 	CString strFile = pFile->GetTotalFileName();
// 
// 	if (ATS_IsTestTaskFile(strFile))
// 	{
// 		SetActiveGbTaskTree();
// 		CTestTask *pTestTask = theApp.GetTestTask();
// 
// 		if (pTestTask != NULL)
// 		{
// 			if (pTestTask->GetTaskFile() == strFile)
// 			{
// 				return 0;
// 			}
// 		}
// 
// 		OpenTaskFile(strFile);
// 	}
// 	else
// 	{
// 		theApp.OnCreateNewProjectFrame(strFile, TRUE);
// 	}

	if (pIecFile != NULL)
	{
		CIecCfgTool::AdjustIecCfgFile(pIecFile);
	}

	return 0;
}

DWORD CMainFrame::OpenIecfgFile(const CString &strIecfgFile,BOOL bAutoGenerate)
{
	m_wndIecfgDevicePane.OnIecfgDeviceClose();//zhouhongjun  在打开新Iecfg文件前，关闭之前的

	CIecCfgFile *pIecFile = NULL;
	pIecFile = theApp.OpenIecCfgFileEx(strIecfgFile,bAutoGenerate);//按照路径名称去找对应的文件，如果之前的New则没复制文件到对应路径，返回值为NULL；如是open则有文件，返回文件的对象；
	theApp.UpdateIecCfgFilesComboBox();

	if (pIecFile == NULL)
	{
		return 0;
	}

	if (pIecFile->GetClassID() == IFTCLASSID_CIECCFGFILE_DEVICE)
	{
		CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecFile;
		m_wndIecfgDevicePane.ShowPane(TRUE, FALSE, TRUE);
		m_wndIecfgDevicePane.ShowIecfgDevice(pIecCfgFileDevice);

		if (theApp.IsRunAutomaition())//zhouhj 20210331 在自动测试情况下，自动打开第一个配置
		{
			theApp.CreateNewIecCfgFrame_FirstIecCfgDatasMngr(pIecCfgFileDevice);
		}
	}

	CIecCfgTool::AdjustIecCfgFile(pIecFile);

	return 1;
}

DWORD CMainFrame::XDeleteXFile(CXFile *pFile)
{
	CString strFile = pFile->GetTotalFileName();
	CIecCfgFile *pIecFile = CIecCfgTool::FindIecFile(strFile);

	if (pIecFile != NULL)
	{
		CString strMsg;
		strMsg.Format(CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigOpenNoDel/*_T("配置文件【%s】已经打开，不能删除！")*/, pFile->m_strName);
		MessageBox(strMsg, CXLanguageResourceIec_61850Cfg::g_sLangTxt_Message/*_T("提示")*/, MB_OK | MB_ICONWARNING);
		return XFILEMNGR_OPTR_FAILED;
	}
	else
	{

	}

	return XFILEMNGR_OPTR_SUCC;
}

DWORD CMainFrame::XDeleteXFolder(CXFolder *pFolder)
{
	BOOL bHas = CIecCfgTool::HasFileInFolder(pFolder);

	if (bHas)
	{
		CString strMsg;
		strMsg.Format(CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoDelContent/*_T("目录【%s】包含已经打开的文件，不能删除！")*/, pFolder->m_strName);
		MessageBox(strMsg,CXLanguageResourceIec_61850Cfg::g_sLangTxt_Message /*_T("提示")*/, MB_OK | MB_ICONWARNING);
		return XFILEMNGR_OPTR_FAILED;
	}

	return XFILEMNGR_OPTR_SUCC;
}

DWORD CMainFrame::XEditXFile(CXFile *pFile, const CString &strDestName)
{
// 	if (m_pTestControl != NULL)
// 	{
// 		CString strGbFile = m_pTestControl->GetGbBinaryFile();
// 		CString strXFile = pFile->m_strID;
// 		strGbFile.MakeLower();
// 		strXFile.MakeLower();
// 		strGbFile = GetPathFileNameFromFilePathName(strGbFile);
// 
// 		if (strGbFile == strXFile)
// 		{
// 			return XFILEMNGR_OPTR_FAILED;
// 		}
// 	}
// 
	CString strSrcFile = pFile->GetTotalFileName();
	CString strDestFile = pFile->GetRelativePath(TRUE);
	strDestFile = GetPathFromFilePathName(strDestFile);
	strDestFile += strDestName;
// 	CString strSrcDocFile = ChangeFilePostfix(strSrcFile, g_strDocFilePostfix);
// 	CString strDestDocFile = ChangeFilePostfix(strDestFile, g_strDocFilePostfix);
// 
// 	if (ATS_IsTestTaskFile(strSrcFile))
// 	{
// 		strDestFile = ChangeFilePostfix(strDestDocFile, g_strTestTaskFilePostfix);
// 	}
// 	else
// 	{
// 		strDestFile = ChangeFilePostfix(strDestDocFile, g_strGuideBookBinaryPostfix);
// 	}
// 
	::MoveFile(strSrcFile, strDestFile);
// 	::MoveFile(strSrcDocFile, strDestDocFile);
// 
	pFile->m_strName = GetPathFileNameFromFilePathName(strDestFile);
	pFile->m_strID = pFile->m_strName;

	return 0;
}

DWORD CMainFrame::XCanEditXFolder(CXFolder *pFolder)
{
	BOOL bHas = CIecCfgTool::HasFileInFolder(pFolder);

	if (bHas)
	{
		CString strMsg;
		strMsg.Format(CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoModifyContent/*_T("目录【%s】包含已经打开的文件，不能修改名称！")*/, pFolder->m_strName);
		MessageBox(strMsg, CXLanguageResourceIec_61850Cfg::g_sLangTxt_Message/*_T("提示")*/, MB_OK | MB_ICONWARNING);
		return XFILEMNGR_OPTR_FAILED;
	}

	return XFILEMNGR_OPTR_SUCC;
}

UINT CMainFrame::GetImgIndex(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();

	if (nClassID != CLASSID_XFILE)
	{
		return 0xFFFFFFFF;
	}

	//if (ATS_IsTestTaskFile(pObj->m_strName))
	{
		return 4;
	}
	//else
	{
		return 2;
	}
}

DWORD CMainFrame::XDownLoad(CExBaseObject *pXFileObj)
{
	return 0;
}

DWORD CMainFrame::XUpload(CExBaseObject *pXFileObj)
{
	return 0;
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CXSplashWndBase::ShowSplashScreen(_T("StationTestMain.bmp"), this);

	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 其他可用样式...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
	mdiTabParams.m_bTabIcons = FALSE;    // 设置为 TRUE 将在 MDI 选项卡上启用文档图标
	mdiTabParams.m_bAutoColor = TRUE;    // 设置为 FALSE 将禁用 MDI 选项卡的自动着色
	mdiTabParams.m_bDocumentMenu = TRUE; // 在选项卡区域的右边缘启用文档菜单
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	InitNormalRibbon();
	InitAT02DRibbon();//周宏军  20200610 增加AT02D相关按钮

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	strTitlePane2 = _T("南京能云电力科技有限公司");
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);
	CMFCRibbonBaseElement *pElement = m_wndStatusBar.FindElement(ID_STATUSBAR_PANE1);
	CRect rc = pElement->GetRect();
	rc.right = 800;
	pElement->SetRect(rc);
	m_wndStatusBar.RecalcLayout();

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);

	m_wndXFilePane.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDeviceXFilePane.EnableDocking(CBRS_ALIGN_ANY);
	m_wndIecfgDevicePane.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndXFilePane, AFX_IDW_DOCKBAR_LEFT);
	ShowPane(&m_wndXFilePane, TRUE, FALSE, TRUE);
	m_wndXFilePane.ShowXFileTree(CIecCfgTool::GetIecCfgFileMngr());

	DockPane(&m_wndDeviceXFilePane, AFX_IDW_DOCKBAR_LEFT);
	ShowPane(&m_wndDeviceXFilePane, TRUE, FALSE, TRUE);
	m_wndDeviceXFilePane.ShowXFileTree(CIecCfgTool::GetIecCfgDeviceFileMngr());

	CDockablePane* pTabbedBar = NULL;
	m_wndIecfgDevicePane.AttachToTabWnd(&m_wndXFilePane, DM_SHOW, TRUE, &pTabbedBar);
	m_wndDeviceXFilePane.AttachToTabWnd(&m_wndXFilePane, DM_SHOW, TRUE, &pTabbedBar);

	ShowPane(&m_wndXFilePane, TRUE, FALSE, TRUE);
	ShowPane(&m_wndDeviceXFilePane, TRUE, FALSE, TRUE);
	ShowPane(&m_wndIecfgDevicePane, FALSE, FALSE, FALSE);
	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

	if (!m_TrayIcon.Enabled())
	{
		m_TrayIcon.Create(this, WM_ICON_NOTIFY, _T("测试仪IEC61850配置程序"),AfxGetApp()->LoadIcon(IDR_MAINFRAME), 0, TRUE); 
	}

	return 0;
}

void CMainFrame::ShowIecCfgFileTitleToStatusBar(const CString &strFile)
{
	CMFCRibbonBaseElement *pElement = m_wndStatusBar.FindElement(ID_STATUSBAR_PANE1);

	if (pElement != NULL)
	{
		CRect rc = pElement->GetRect();
		rc.right = 800;
		pElement->SetRect(rc);

		pElement->SetText(strFile);
		//m_wndStatusBar.SetRedraw(TRUE);
		//m_wndStatusBar.RecalcLayout();
		m_wndStatusBar.Invalidate(TRUE);
	}
}

void CMainFrame::ShowIecCfgFileTitleToStatusBar(CIecCfgFile *pIecfgFile)
{
	CExBaseObject *pAncestor = (CExBaseObject*)pIecfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);

	if (pAncestor == NULL)
	{
		ShowIecCfgFileTitleToStatusBar(pIecfgFile->m_strID);
	}
	else
	{
		CIecCfgFileDevice *pIecfgFileDevice = (CIecCfgFileDevice*)pAncestor;
		CString strTitle;
		strTitle.Format(_T("%s : %s"), pIecfgFileDevice->m_strID, pIecfgFile->m_pIecCfgDatasMngr->m_strID);
		ShowIecCfgFileTitleToStatusBar(strTitle);
	}
}

void CMainFrame::ShowIecfgFileDevice(CIecCfgFile *pIecfgFile)
{
	if (pIecfgFile == NULL)
	{
		m_wndIecfgDevicePane.ShowPane(FALSE, FALSE, FALSE);
	}
	else
	{
		CIecCfgFileDevice *pIecfgFileDevice = (CIecCfgFileDevice*)pIecfgFile;
		m_wndIecfgDevicePane.ShowPane(TRUE, FALSE, TRUE);
		m_wndIecfgDevicePane.ShowIecfgDevice(pIecfgFileDevice);
	}
}
void CMainFrame::ShowIecfgFileDevice(CIecCfgFileDevice *pIecfgFileDevice)
{
	if (pIecfgFileDevice == NULL)
	{
		m_wndIecfgDevicePane.ShowPane(FALSE, FALSE, FALSE);
	}
	else
	{
		m_wndIecfgDevicePane.ShowPane(TRUE, FALSE, TRUE);
		m_wndIecfgDevicePane.ShowIecfgDevice(pIecfgFileDevice);
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

void CMainFrame::InitNormalRibbon()
{
	// 加载面板图像:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_WRITESMALL);

	// 初始主按钮:
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(CXLanguageResourceIec_61850Cfg::g_sLangTxt_IEC61850Config/*_T("IEC61850测试仪配置")*/);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(_T("Iec61850Config"), IDB_WRITESMALL, IDB_WRITELARGE);

	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_NEW, CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConf/*_T("新建配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConfTip, 0, 0));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_SAVE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConf/*_T("保存配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConfTip, 1, 1));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_SAVE_AS, CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveAs/*_T("配置另存为")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAsTip, 2, 2));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_OPEN_SCL, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFile/*_T("打开SCD文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFileTip, 3, 3));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_OPEN_SCL_HIS, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFile/*_T("选择SCD文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFileTip, 4, 4));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_IMPORT, CXLanguageResourceIec_61850Cfg::g_sLangTxt_UseCfg/*_T("使用配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_UseCfgTip, 5, 5));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_CLOSE, CXLanguageResourceBase::g_sLangTxt_FileClose/*_T("关闭文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_CloseFileTip, 8, 8));

	pMainPanel->AddToBottom(new CXLangRibbonMainPanelButton(ID_APP_EXIT, /*strTemp*/CXLanguageResourceIec_61850Cfg::g_sLangTxt_AppExit,CXLanguageResourceIec_61850Cfg::g_sLangTxt_AppExitTip, 8));//2016.10.13

	// 为“剪贴板”面板添加“主”类别:
// 	bNameValid = strTemp.LoadString(IDS_RIBBON_HOME);
// 	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(_T("标准配置")/*CXLanguageResourceIec_61850Cfg::g_sLangTxt_Home*/, IDB_WRITESMALL, IDB_WRITELARGE);

	//文件
	CMFCRibbonPanel* pPanelFile = pCategoryHome->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFile/*_T("配置文件")*/, m_PanelImages.ExtractIcon(27));
	CXLangRibbonButton* pBtnFile = NULL;

	if (g_nEngineDispMode == _DISP_MODE_NORMAL)
	{
		pBtnFile = new CXLangRibbonButton(ID_FILE_NEW, CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConf/*_T("新配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConfTip, 0, 0);
		pPanelFile->Add(pBtnFile);

		pBtnFile = new CXLangRibbonButton(ID_FILE_IMPORT, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConf/*_T("导入配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConfTip, 11, 11);
		pPanelFile->Add(pBtnFile);
	}

	pBtnFile = new CXLangRibbonButton(ID_FILE_SAVE,CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConf/* _T("保存配置")*/,CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConfTip, 1, 1);
	pPanelFile->Add(pBtnFile);

	if (g_nEngineDispMode == _DISP_MODE_NORMAL)
	{
		pBtnFile = new CXLangRibbonButton(ID_FILE_SAVE_AS, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAs/*_T("配置另存为")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAsTip, 2, 2);
		pPanelFile->Add(pBtnFile);
	}


	//SCL
	pPanelFile = pCategoryHome->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_SCDFile/*_T("SCD文件")*/, m_PanelImages.ExtractIcon(27));

	pBtnFile = new CXLangRibbonButton(ID_FILE_OPEN_SCL, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFile/*_T("打开SCD文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFileTip, 3, 3);
	pPanelFile->Add(pBtnFile);
	pBtnFile = new CXLangRibbonButton(ID_FILE_OPEN_SCL_HIS, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFile/*_T("选择SCD文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFileTip, 4, 4);
	pPanelFile->Add(pBtnFile);
	pBtnFile = new CXLangRibbonButton(ID_FILE_NEW_DEVICE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewDeviceConfig/*_T("新设备配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewDeviceConfigTip, 15, 15);
	pPanelFile->Add(pBtnFile);

#if 0
	pPanelFile = pCategoryHome->AddPanel(_T("操作"), m_PanelImages.ExtractIcon(27));
	pBtnFile = new CMFCRibbonButton(ID_FILE_USE_IECCFGFILE, _T("使用配置"), 5, 5);
	pPanelFile->Add(pBtnFile);
	pBtnFile = new CMFCRibbonButton(ID_FILE_STATE_TOOL, _T("状态序列"), 12, 12);
	pPanelFile->Add(pBtnFile);
	pBtnFile = new CMFCRibbonButton(ID_FILE_STATE_STARTTEST, _T("开始测试"), 13, 13);
	pPanelFile->Add(pBtnFile);
	pBtnFile = new CMFCRibbonButton(ID_FILE_STATE_STOPTEST, _T("停止测试"), 14, 14);
	pPanelFile->Add(pBtnFile);
	pBtnFile = new CMFCRibbonButton(ID_FILE_RUN_61850CAP, _T("IEC抓包"), 6, 6);
	pPanelFile->Add(pBtnFile);
#endif

	// 创建和添加“视图”面板:

	CMFCRibbonPanel* pPanelView = pCategoryHome->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_View/*strTemp*/, m_PanelImages.ExtractIcon (7));
	CXLangRibbonCheckBox* pBtnCheck = NULL;
	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_IECCFG_FILEDEVICE_PANE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigFileBar/*_T("设备配置文件栏")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigFileBarTip);
	pPanelView->Add(pBtnCheck);

	if (g_nEngineDispMode == _DISP_MODE_NORMAL)
	{
		pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_IECCFG_FILE_PANE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFileBar/*_T("配置文件栏")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFileBarTip);
		pPanelView->Add(pBtnCheck);
	}

	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_IECCFG_DEVICE_PANE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigBar/*_T("设备配置栏")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigBarTip);
	pPanelView->Add(pBtnCheck);
	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_IECCFG_USEDIN, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OnlyReferencedChannel/*_T("只显示引用通道")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OnlyReferencedChannelTip);
	pPanelView->Add(pBtnCheck);
 	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_CH_PATH, _T("显示通道路径"), _T("显示通道路径"));
 	pPanelView->Add(pBtnCheck);
	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_OUTPUT, CXLanguageResourceBase::g_sLangTxt_OutputBar/*_T("输出栏")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OutputBarTip);
	pPanelView->Add(pBtnCheck);
	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_STATUS_BAR, CXLanguageResourceBase::g_sLangTxt_StatusBar/*_T("状态栏")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_StatusBarTip);
	pPanelView->Add(pBtnCheck);

	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_LINK_GOUT, _T("关联Gout虚端子"), _T("关联Gout虚端子"));
	pPanelView->Add(pBtnCheck);

	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_AUTO_OPEN_LAST, _T("自动打开上次配置"), _T("自动打开上次配置"));
	pPanelView->Add(pBtnCheck);

	pPanelFile = pCategoryHome->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_Other/*_T("其它")*/, m_PanelImages.ExtractIcon(27));
	pBtnFile = new CXLangRibbonButton(ID_APP_ABOUT, CXLanguageResourceBase::g_sLangTxt_HelpAbout/*_T("关于")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_AboutTip, 7, 7);
	pPanelFile->Add(pBtnFile);
	pBtnFile = new CXLangRibbonButton(ID_APP_EXIT, CXLanguageResourceIec_61850Cfg::g_sLangTxt_Quit/*_T("退出")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_QuitTip, 9, 9);
	pPanelFile->Add(pBtnFile);
}

void CMainFrame::InitPN466Ribbon()
{
	// 加载面板图像:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_WRITESMALL);

	// 初始主按钮:
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(CXLanguageResourceIec_61850Cfg::g_sLangTxt_IEC61850Config/*_T("IEC61850测试仪配置")*/);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(_T("Iec61850Config"), IDB_WRITESMALL, IDB_WRITELARGE);

	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_IMPORT, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConf/*_T("导入配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConfTip, 11, 11));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_SAVE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConf/*_T("保存配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConfTip, 1, 1));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_SAVE_AS, CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveAs/*_T("配置另存为")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAsTip, 2, 2));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_OPEN_SCL, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFile/*_T("打开SCD文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFileTip, 3, 3));
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_CLOSE, CXLanguageResourceBase::g_sLangTxt_FileClose/*_T("关闭文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_CloseFileTip, 8, 8));

	pMainPanel->AddToBottom(new CXLangRibbonMainPanelButton(ID_APP_EXIT, /*strTemp*/CXLanguageResourceIec_61850Cfg::g_sLangTxt_AppExit,CXLanguageResourceIec_61850Cfg::g_sLangTxt_AppExitTip, 8));//2016.10.13

	// 为“剪贴板”面板添加“主”类别:
	// 	bNameValid = strTemp.LoadString(IDS_RIBBON_HOME);
	// 	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(_T("标准配置")/*CXLanguageResourceIec_61850Cfg::g_sLangTxt_Home*/, IDB_WRITESMALL, IDB_WRITELARGE);

	//文件
	CMFCRibbonPanel* pPanelFile = NULL;
	CXLangRibbonButton* pBtnFile = NULL;
// 	pPanelFile = pCategoryHome->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFile/*_T("配置文件")*/, m_PanelImages.ExtractIcon(27));
// 
// 	pBtnFile = new CXLangRibbonButton(ID_FILE_IMPORT, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConf/*_T("导入配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConfTip, 11, 11);
// 	pPanelFile->Add(pBtnFile);
// 	pBtnFile = new CXLangRibbonButton(ID_FILE_SAVE,CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConf/* _T("保存配置")*/,CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConfTip, 1, 1);
// 	pPanelFile->Add(pBtnFile);
// 	pBtnFile = new CXLangRibbonButton(ID_FILE_SAVE_AS, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAs/*_T("配置另存为")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAsTip, 2, 2);
// 	pPanelFile->Add(pBtnFile);

	//SCL
	pPanelFile = pCategoryHome->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_SCDFile/*_T("SCD文件")*/, m_PanelImages.ExtractIcon(27));

	pBtnFile = new CXLangRibbonButton(ID_FILE_OPEN_SCL, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFile/*_T("打开SCD文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFileTip, 3, 3);
	pPanelFile->Add(pBtnFile);

	// 创建和添加“视图”面板:

	CMFCRibbonPanel* pPanelView = pCategoryHome->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_View/*strTemp*/, m_PanelImages.ExtractIcon (7));
	CXLangRibbonCheckBox* pBtnCheck = NULL;

	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_IECCFG_USEDIN, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OnlyReferencedChannel/*_T("只显示引用通道")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OnlyReferencedChannelTip);
	pPanelView->Add(pBtnCheck);
 	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_CH_PATH, _T("显示通道路径"), _T("显示通道路径"));
 	pPanelView->Add(pBtnCheck);
	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_OUTPUT, CXLanguageResourceBase::g_sLangTxt_OutputBar/*_T("输出栏")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OutputBarTip);
	pPanelView->Add(pBtnCheck);
// 	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_STATUS_BAR, CXLanguageResourceBase::g_sLangTxt_StatusBar/*_T("状态栏")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_StatusBarTip);
// 	pPanelView->Add(pBtnCheck);

	pPanelFile = pCategoryHome->AddPanel(_T("其它"), m_PanelImages.ExtractIcon(27));
// 	pBtnFile = new CXLangRibbonButton(ID_APP_ABOUT, CXLanguageResourceBase::g_sLangTxt_HelpAbout/*_T("关于")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_AboutTip, 7, 7);
// 	pPanelFile->Add(pBtnFile);
	pBtnFile = new CXLangRibbonButton(ID_SEND_CONFIG,_T("下发配置"),_T("下发参数配置文件."), 1, 1);
	pPanelFile->Add(pBtnFile);
	pBtnFile = new CXLangRibbonButton(ID_APP_EXIT, CXLanguageResourceIec_61850Cfg::g_sLangTxt_Quit/*_T("退出")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_QuitTip, 9, 9);
	pPanelFile->Add(pBtnFile);
	m_wndStatusBar.ModifyStyle(WS_VISIBLE, 0);
}

void CMainFrame::InitAT02DRibbon()//周宏军 20200616  增加AT02配置
{
	CMFCRibbonCategory* pCategoryAT02D = NULL;

	if (g_nEngineDispMode == _DISP_MODE_PNI302)
	{
		pCategoryAT02D = m_wndRibbonBar.AddCategory(_T("PNI302"), IDB_WRITESMALL, IDB_WRITELARGE);
	} 
	else
	{
		pCategoryAT02D = m_wndRibbonBar.AddCategory(_T("AT02D"), IDB_WRITESMALL, IDB_WRITELARGE);
	}

	//文件
	CMFCRibbonPanel *pPanelFile = pCategoryAT02D->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFile/*_T("配置文件")*/, m_PanelImages.ExtractIcon(27));
	CXLangRibbonButton* pBtnFile = NULL;

	if (g_nEngineDispMode != _DISP_MODE_PNI302)
	{
		pBtnFile = new CXLangRibbonButton(ID_FILE_NEW_AT02D, CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConf/*_T("新配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConfTip, 0, 0);
		pPanelFile->Add(pBtnFile);
		pBtnFile = new CXLangRibbonButton(ID_FILE_IMPORT_AT02D, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConf/*_T("导入配置")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConfTip, 11, 11);
		pPanelFile->Add(pBtnFile);
	}

	pBtnFile = new CXLangRibbonButton(ID_FILE_SAVE_AT02D,CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConf/* _T("保存配置")*/,CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConfTip, 1, 1);
	pPanelFile->Add(pBtnFile);

	if (g_nEngineDispMode != _DISP_MODE_PNI302)
	{
		pBtnFile = new CXLangRibbonButton(ID_FILE_SAVE_AS_AT02D, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAs/*_T("配置另存为")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAsTip, 2, 2);
		pPanelFile->Add(pBtnFile);

		pBtnFile = new CXLangRibbonButton(ID_EXPORT_DEVICE_MODEL,_T("导出模型"), _T("导出设备数据模型文件"), 5, 5);
		pPanelFile->Add(pBtnFile);
	}

	//SCL
	pPanelFile = pCategoryAT02D->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_SCDFile/*_T("SCD文件")*/, m_PanelImages.ExtractIcon(27));

	pBtnFile = new CXLangRibbonButton(ID_FILE_OPEN_SCL_AT02D, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFile/*_T("打开SCD文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFileTip, 3, 3);
	pPanelFile->Add(pBtnFile);
	pBtnFile = new CXLangRibbonButton(ID_FILE_OPEN_SCL_HIS_AT02D, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFile/*_T("选择SCD文件")*/, CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFileTip, 4, 4);
	pPanelFile->Add(pBtnFile);

	if (g_nEngineDispMode == _DISP_MODE_PNI302)
	{
		pBtnFile = new CXLangRibbonButton(ID_FILE_NEW_DEVICE_AT02D, _T("新设备配置"), CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewDeviceConfigTip, 15, 15);
		pPanelFile->Add(pBtnFile);
	}
	else
	{
		pBtnFile = new CXLangRibbonButton(ID_FILE_NEW_DEVICE_AT02D, _T("新AT02D配置"), CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewDeviceConfigTip, 15, 15);
		pPanelFile->Add(pBtnFile);
	}

	// 创建和添加“视图”面板:
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_RIBBON_VIEW);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelView = pCategoryAT02D->AddPanel(CXLanguageResourceIec_61850Cfg::g_sLangTxt_View/*strTemp*/, m_PanelImages.ExtractIcon (7));

	CXLangRibbonCheckBox* pBtnCheck = NULL;
	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_MODEL_USE_HARM, _T("模型包含谐波"), _T("模型包含谐波"));
	pPanelView->Add(pBtnCheck);
	pBtnCheck = new CXLangRibbonCheckBox(ID_VIEW_VERIFY_VOL_CUR, _T("校验电压电流通道"), _T("校验电压电流通道"));
	pPanelView->Add(pBtnCheck);
}

void CMainFrame::IntRibbonByDispMode()
{
	long nCount = m_wndRibbonBar.GetCategoryCount();

	m_wndRibbonBar.RemoveAllCategories();

	if ((g_nEngineDispMode == _DISP_MODE_AT02D)||(g_nEngineDispMode == _DISP_MODE_PNI302))
	{
		InitAT02DRibbon();
	}
	else if (g_nEngineDispMode == _DISP_MODE_PN466)
	{
		InitPN466Ribbon();
	}
	else
	{
		InitNormalRibbon();
	}

	m_wndRibbonBar.RecalcLayout();
	m_wndRibbonBar.Invalidate(TRUE);
}

BOOL CMainFrame::CreateDockingWindows()
{
	if (!m_wndOutput.Create(CXLanguageResourceBase::g_sLangTxt_OutputBar, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);

	m_wndXFilePane.CreateFilterTextMngr(_T("IecCfgFilter.xml"));
	m_wndDeviceXFilePane.CreateFilterTextMngr(_T("IecCfgDeviceFilter.xml"));
	//m_wndXFilePane.SetIDB_XFILEMNGR(IDB_BITMAP_GUIDEBOOKFILE);

	m_wndXFilePane.SetXFileMsgRcvWnd(this);
	m_wndXFilePane.SetIDB_XFILEMNGR(IDB_IECCFGFILE);
	m_wndDeviceXFilePane.SetXFileMsgRcvWnd(this);
	m_wndDeviceXFilePane.SetIDB_XFILEMNGR(IDB_IECCFGFILE);

	// 创建文件视图
	if (!m_wndXFilePane.Create(CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFileManag /*_T("配置文件管理")*/, this, CRect(0, 0, 200, 200), TRUE, XID_XFILE_DOCPANE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“测试任务文件视图”窗口\n");
		return FALSE; // 未能创建
	}

	if (!m_wndDeviceXFilePane.Create(CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceCfgFileManag /*_T("设备配置文件管理")*/, this, CRect(0, 0, 200, 200), TRUE, XID_XFILE_DOCPANE+1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“测试任务文件视图”窗口\n");
		return FALSE; // 未能创建
	}

	if (!m_wndIecfgDevicePane.Create(CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceCfg /*_T("设备配置")*/, this, CRect(0, 0, 200, 200), TRUE, ID_IecfgDevice_DOCPANE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“设备IEC测试仪配置”窗口\n");
		return FALSE; // 未能创建
	}

	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

CXFolder* CMainFrame::GetCurrXFolder()
{
	CXFolder *pXFolder = NULL;
	CXFileMngr *pXFileMngr = CIecCfgTool::GetIecCfgFileMngr();

	pXFolder = pXFileMngr->GetCurrFolder();

	return pXFolder;
}

// 
// void CMainFrame::OnFileSave()
// {
// 	CFrameWnd *pFrame = GetActiveFrame();
// 	
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
// 	{
// 		return;
// 	}
// 
// // 	CXFileMngr *pFileMngr = CIecCfgTool::GetIecCfgFileMngr();
// // 	CXFolder *pFolder = pFileMngr->GetCurrFolder();
// 	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
// 	pIecConfigFrame->Save();
// }
// 
// void CMainFrame::OnUpdateFileSave(CCmdUI *pCmdUI)
// {
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (pFrame == NULL)
// 	{
// 		pCmdUI->Enable(FALSE);
// 		return;
// 	}
// 
// 	BOOL b = pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame));
// 	pCmdUI->Enable(b);
// }
// 
// void CMainFrame::OnFileSaveAs()
// {
// 	CFrameWnd *pFrame = GetActiveFrame();
// 
// 	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
// 	{
// 		return;
// 	}
// 
// 	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
// 	//pIecConfigFrame->SaveAs();
// }
// 
// void CMainFrame::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
// {
// 	OnUpdateFileSave(pCmdUI);
// }

void CMainFrame::OnClose()
{
	if (theApp.IsRunAutomaition())
	{
		ShowWindow(SW_HIDE);
		PostMsg_TestEngineFinish(_T(""));//退出程序
		return;
	}

	CString strFiles;
	BOOL bModified = CIecCfgTool::HasIecCfgFileModified(strFiles);

	//发送消息给外部程序
	CXAtsSysSvrClient::PostTestStateMsgTo(XMODULE_ID_StationTestMain, XMODULE_OPTR_IEC61850CONFIG, XMODULE_STATE_FINISH);

	if (bModified)
	{
		CString strMsg;
		strMsg.Format(_T("配置文件%s已修改,是否保存?"), strFiles);
		UINT nRet = MessageBox(strMsg,CXLanguageResourceIec_61850Cfg::g_sLangTxt_Message/* _T("提示")*/, MB_YESNO | MB_ICONQUESTION);

		if (nRet == IDCANCEL)
		{
			return;
		}
		else if (nRet == IDOK)
		{
		}
	}

	if (theApp.IsCfgInStationTest())
	{
		ShowWindow(SW_HIDE);
		return;
	}

	m_TrayIcon.HideIcon();
	__super::OnClose();
}

void CMainFrame::OnViewIeccfgFilePane()
{
	if (m_wndXFilePane.IsVisible())
	{
		m_wndXFilePane.ShowPane(FALSE, FALSE, FALSE);
	}
	else
	{
		m_wndXFilePane.ShowPane(TRUE, FALSE, TRUE);
	}
}

void CMainFrame::OnUpdateViewIeccfgFilePane(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndXFilePane.IsVisible());
}

void CMainFrame::OnViewIeccfgDevicePane()
{
	if (m_wndIecfgDevicePane.IsVisible())
	{
		m_wndIecfgDevicePane.ShowPane(FALSE, FALSE, FALSE);
	}
	else
	{
		m_wndIecfgDevicePane.ShowPane(TRUE, FALSE, TRUE);
	}
}

void CMainFrame::OnUpdateViewIeccfgDevicePane(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndIecfgDevicePane.IsVisible());
}

void CMainFrame::OnViewIeccfgDeviceFilePane()
{
	if (m_wndDeviceXFilePane.IsVisible())
	{
		m_wndDeviceXFilePane.ShowPane(FALSE, FALSE, FALSE);
	}
	else
	{
		m_wndDeviceXFilePane.ShowPane(TRUE, FALSE, TRUE);
	}
}

void CMainFrame::OnUpdateViewIeccfgDeviceFilePane(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndDeviceXFilePane.IsVisible());
}

void CMainFrame::OnViewModelUseHarm()
{
	if (CIecCfgTool::IsModelUseHarm())
	{
		CIecCfgTool::SetModelUseHarm(0);
	}
	else
	{
		CIecCfgTool::SetModelUseHarm(1);
	}
}

void CMainFrame::OnUpdateViewModelUseHarm(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CIecCfgTool::IsModelUseHarm());
}

void CMainFrame::OnVerifyVolCurChannel()
{
	if (CIecCfgTool::IsVerifyVolCurChannel())
	{
		CIecCfgTool::SetVerifyVolCurChannel(0);
	}
	else
	{
		CIecCfgTool::SetVerifyVolCurChannel(1);
	}
}

void CMainFrame::OnUpdateVerifyVolCurChannel(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CIecCfgTool::IsVerifyVolCurChannel());
}


void CMainFrame::OnViewLinkGout()
{
	if (CIecCfgTool::LinkGout())
	{
		CIecCfgTool::SetLinkGout(0);
	}
	else
	{
		CIecCfgTool::SetLinkGout(1);
	}
}

void CMainFrame::OnUpdateViewLinkGout(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CIecCfgTool::LinkGout());
}

void CMainFrame::OnViewAutoOpenLast()
{
	if (CIecCfgTool::IsAutoOpenLast())
	{
		CIecCfgTool::SetAutoOpenLast(0);
	}
	else
	{
		CIecCfgTool::SetAutoOpenLast(1);
	}
}

void CMainFrame::OnUpdateViewAutoOpenLast(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CIecCfgTool::IsAutoOpenLast());
}

void CMainFrame::OnViewOutput()
{
	if (m_wndOutput.IsVisible())
	{
		m_wndOutput.ShowPane(FALSE, FALSE, FALSE);
	}
	else
	{
		m_wndOutput.ShowPane(TRUE, FALSE, TRUE);
	}
}

void CMainFrame::OnUpdateViewOutput(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndOutput.IsVisible());
}

void CMainFrame::OnFileImport()
{
	CString strFilter,strFile;

	if (g_nEngineDispMode == _DISP_MODE_PN466)
	{
		strFilter = _T("IEC61850配置文件(*.ixml)|*.ixml||");
//		strFilter = _T("IEC61850配置文件(*.ixml)|*.ixml||");

		if (! PopupOpenFileDialog(this, strFile, strFilter, _T("ixml")) )
		{
			return;
		}
	} 
	else
	{
		strFilter = _T("IEC61850配置文件(*.iecfg;*.ixml)|*.iecfg;*.ixml|装置配置(*.iecfg)|*.iecfg|单个配置(*.ixml)|*.ixml||");

		if (! PopupOpenFileDialog(this, strFile, strFilter, _T("")) )
		{
			return;
		}
	}

	if (g_nEngineDispMode == _DISP_MODE_PN466)
	{
		if (IsFileExist(g_szEngineIecfgPath))//zhouhj20210911先删除之前的文件,再将文件拷贝到新的位置
		{
			CIecCfgFile *pIecCfgFile = CIecCfgTool::OpenIecFile(g_szEngineIecfgPath);

			if (pIecCfgFile != NULL)
			{
				CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pIecCfgFile->GetRefFrameWnd();
				CIecCfgTool::CloseIecFile(pIecCfgFile,TRUE);
				ASSERT(pIecConfigFrame);
				X_CopyFile(strFile,g_szEngineIecfgPath);
				CIecCfgFile *pIecCfgFile = CIecCfgTool::OpenIecFile(g_szEngineIecfgPath);
				pIecCfgFile->SetRefFrameWnd(pIecConfigFrame);
				pIecConfigFrame->m_pDocument->UpdateAllViews(NULL, (LPARAM)pIecCfgFile, NULL);
// 
// 				if (pIecConfigFrame != NULL)
// 				{
// 					pIecConfigFrame->SetCloseFrameByDelete(TRUE);
// 					pIecConfigFrame->PostMessage(WM_CLOSE, 0, 0);
// 				}
// 
// 				CTickCount32 oTickCount;
// 				oTickCount.DoEvents(500);//zhouhj 20210911 确保之前的窗口已经关闭
			}
		}

// 		X_CopyFile(strFile,g_szEngineIecfgPath);
// 		OpenIecfgFile(g_szEngineIecfgPath,FALSE);
		return;
	}

	CIecCfgFile *pIecCfgFile = NULL;
	pIecCfgFile = theApp.OpenIecCfgFileEx(strFile,FALSE);

	if (pIecCfgFile->GetClassID() == IFTCLASSID_CIECCFGFILE_DEVICE)
	{
		CIecCfgFileDevice *pIecfileDevice = (CIecCfgFileDevice *)pIecCfgFile;
		theApp.UpdateIecCfgFilesComboBox();

		m_wndIecfgDevicePane.ShowPane(TRUE, FALSE, TRUE);
		m_wndIecfgDevicePane.ShowIecfgDevice(pIecfileDevice);
		CIecCfgTool::AdjustIecCfgFile(pIecCfgFile);
	}
}

void CMainFrame::OnFileImportAT02D()
{
	OnFileImport();
}

LRESULT CMainFrame::OnElectricTestMsg(WPARAM wParam, LPARAM lParam)
{
	//CLogPrint::LogString(XLOGLEVEL_TRACE, L"TestControlWnd::OnElectricTestMsg");
	return theApp.OnElectricTestMsg(wParam,lParam);
}

LRESULT CMainFrame::OnSetDispMode(WPARAM wParam, LPARAM lParam)
{
	IntRibbonByDispMode();

	if (g_nEngineDispMode == _DISP_MODE_PN466)
	{
		m_wndXFilePane.ShowPane(FALSE, FALSE, FALSE);
		m_wndIecfgDevicePane.ShowPane(FALSE, FALSE, FALSE);
		m_wndDeviceXFilePane.ShowPane(FALSE, FALSE, FALSE);
	}

	return 0;
}

LRESULT CMainFrame::OnXAtsSvrClientMessage(WPARAM wParam, LPARAM lParam)
{
	AtsSysSvr::CSysMsg oSysMsg;
	CXAtsSysSvrClient::GetSysMsg(lParam, oSysMsg);

	if (oSysMsg == NULL)
	{
		return 0;
	}

	CString strMsgID;
	strMsgID = oSysMsg.GetMsgID();
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("AutoTest OnXAtsSvrClientMessage:  MsgID=%s"), strMsgID);

	//配置文件已经存在
	ASSERT (strMsgID == XPARA_ID_IecfgFile);

	CString strIecFile, strTscdFile, strOptr;
	strIecFile = oSysMsg.FindParaByID(XPARA_ID_IecfgFile);
	strTscdFile = oSysMsg.FindParaByID(XPARA_ID_TscdFile);
	strOptr = oSysMsg.FindParaByID(XPARA_ID_Optr);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("*******************%s"), strTscdFile);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("*******************%s"), strIecFile);

	CString strIedID = ParseFileName(strIecFile);//根据.iecfg文件的路径，复制传递出对应文件名，即对应的IED名称；
	theApp.CreateNewSclFrame(strTscdFile, strIedID);//打开.tscd文件，并指定到对应strIedID的装置；
	BOOL bAutoGenerate = IsFileExist(strIecFile);
	
	if (OpenIecfgFile(strIecFile,bAutoGenerate) == 0)//在打开配置文件函数中实现智能配置；如果是新建的话，早早返回0值进入if语句中；
	{
		if (strOptr == XPARA_ID_OptrVal_New)
		{
//			theApp.CreateNewSclFrame(strTscdFile, strIedID);//打开.tscd文件，并指定到对应strIedID的装置；  
			CIecCfgFile *pIecCfgFile = CIecCfgTool::NewIecCfgFile(g_strDeviceIecCfgFilePostfix);//新建一个空的配置设备对象；
			CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecCfgFile;
			theApp.OnFileNewDevice(pIecCfgFileDevice);
			pIecCfgFile->SaveAs(strIecFile);//将新建的设备存储到对应的路径下；

			m_wndIecfgDevicePane.ShowPane(TRUE, FALSE, TRUE);
			m_wndIecfgDevicePane.ShowIecfgDevice(pIecCfgFileDevice);
			CIecCfgTool::AdjustIecCfgFile(pIecCfgFile);
			
		}
	}
	else
	{
// 		CIecCfgFile *pIecCfgFileOld = CIecCfgTool::FindIecFile(strIecFile);//之前已经将读取的文件存入静态变量中，根据路径名查找到对应的设备配置文件；
// 		CIecCfgTool::CloseIecFile(pIecCfgFileOld , TRUE);
// 
// 		CIecCfgFile *pIecCfgFile = CIecCfgTool::OpenIecFile(strIecFile);
// 
// 		m_wndIecfgDevicePane.ShowPane(TRUE, FALSE, TRUE);
// 		m_wndIecfgDevicePane.ShowIecfgDevice((CIecCfgFileDevice*)pIecCfgFile);
// 
// 		if (pIecCfgFile != NULL)
// 		{
// 			CIecCfgTool::AdjustIecCfgFile(pIecCfgFile);
// 		}
	}

	theApp.UpdateIecCfgFilesComboBox();
	CXAtsSysSvrClient::DeleteSysMsg(lParam);

	//发送消息给外部程序
	CXAtsSysSvrClient::PostTestStateMsgTo(XMODULE_ID_StationTestMain, XMODULE_OPTR_IEC61850CONFIG, XMODULE_STATE_TESTING);

	ShowWindow(SW_SHOW);
	BringWindowToTop();

	return 0;
}


LRESULT CMainFrame::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(lParam) == WM_LBUTTONDBLCLK)
	{
		if (IsWindowVisible())
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			ShowWindow(SW_SHOW);
			BringWindowToTop();
		}

		return TRUE;
	}

	if (LOWORD(lParam) == WM_RBUTTONUP)
	{
		CMenu menu;		
		menu.CreatePopupMenu();

		menu.AppendMenu(MF_STRING, ID_TRAYICON_EXITAPP, _T("退出")); 

		CPoint point;
		GetCursorPos(&point);

		menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);			

		//资源回收
		HMENU hmenu=menu.Detach();			
		menu.DestroyMenu();	

		return TRUE;
	}

	return TRUE;
}

void CMainFrame::OnAppExit()
{
	m_TrayIcon.HideIcon();
	__super::OnClose();
}
