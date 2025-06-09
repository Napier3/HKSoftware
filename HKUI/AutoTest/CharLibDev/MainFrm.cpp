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
#include "CharLibDev.h"

#include "MainFrm.h"
#include "CharEditDlg.h"
#include "DlgImportCharFromRioFile.h"
#include "..\..\Module\XLanguage\XLangRibbonCtrls.h"

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
	ON_COMMAND(ID_CHAROPTR_NEWCHAR, &CMainFrame::OnCharoptrNewchar)
	ON_COMMAND(ID_CHAROPTR_SAVE, &CMainFrame::OnCharoptrSave)
	ON_UPDATE_COMMAND_UI(ID_CHAROPTR_SAVE, &CMainFrame::OnUpdateCharoptrSave)
	ON_COMMAND(ID_CHAROPTR_SAVEAS, &CMainFrame::OnCharoptrSaveas)
	ON_UPDATE_COMMAND_UI(ID_CHAROPTR_SAVEAS, &CMainFrame::OnUpdateCharoptrSaveas)
	ON_COMMAND(ID_CHAROPTR_DELETE, &CMainFrame::OnCharoptrDelete)
	ON_UPDATE_COMMAND_UI(ID_CHAROPTR_DELETE, &CMainFrame::OnUpdateCharoptrDelete)
	ON_COMMAND(ID_CHAROPTR_EXPORT, &CMainFrame::OnCharoptrExport)
	ON_UPDATE_COMMAND_UI(ID_CHAROPTR_EXPORT, &CMainFrame::OnUpdateCharoptrExport)
	ON_COMMAND(ID_VIEW_CHARPANE, &CMainFrame::OnViewCharpane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CHARPANE, &CMainFrame::OnUpdateViewCharpane)
	ON_COMMAND(ID_VIEW_OUTPUTWND, &CMainFrame::OnViewOutputwnd)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUTWND, &CMainFrame::OnUpdateViewOutputwnd)
	ON_WM_CLOSE()
	ON_COMMAND(ID_CHAROPTR_IMPORTFROMRIOFILE, &CMainFrame::OnCharoptrImportfromriofile)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
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
	InitializeRibbon();

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
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 加载菜单项图像(不在任何标准工具栏上):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	m_wndCharLibView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndCharLibView);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);


	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

	m_wndCharLibView.ShowCharLib();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

void CMainFrame::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// 加载面板图像:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// 初始主按钮:
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(g_sLangTxt_File1);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_NEW);
	ASSERT(bNameValid);
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_NEW, g_sLangTxt_NewFileCreat/*strTemp*/,g_sLangTxt_NewFileCreatTip, 0, 0));
	bNameValid = strTemp.LoadString(IDS_RIBBON_OPEN);
	ASSERT(bNameValid);
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_OPEN, g_sLangTxt_Open0/*strTemp*/,g_sLangTxt_Open0Tip, 1, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_SAVE, g_sLangTxt_SaveS/*strTemp*/,g_sLangTxt_SaveSTip, 2, 2));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVEAS);
	ASSERT(bNameValid);
	pMainPanel->Add(new CXLangRibbonButton(ID_FILE_SAVE_AS,g_sLangTxt_SaveAsA /*strTemp*/,g_sLangTxt_SaveAsATip, 3, 3));

	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPrint = new CMFCRibbonButton(ID_FILE_PRINT, g_sLangTxt_Print1/*strTemp*/, 6, 6);
	pBtnPrint->SetKeys(_T("p"), _T("w"));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_LABEL);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonLabel(g_sLangTxt_RePrintDoc/*strTemp*/));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_QUICK);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_DIRECT, g_sLangTxt_PrintQuick/*strTemp*/, 7, 7, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_PREVIEW);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_PREVIEW, g_sLangTxt_PrintPre/*strTemp*/, 8, 8, TRUE));
	bNameValid = strTemp.LoadString(IDS_RIBBON_PRINT_SETUP);
	ASSERT(bNameValid);
	pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, g_sLangTxt_PrintSet/*strTemp*/, 11, 11, TRUE));
	pMainPanel->Add(pBtnPrint);
	pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CLOSE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, g_sLangTxt_FileClose1/*strTemp*/, 9, 9));

	bNameValid = strTemp.LoadString(IDS_RIBBON_RECENT_DOCS);
	ASSERT(bNameValid);
	pMainPanel->AddRecentFilesList(g_sLangTxt_CurrentUseDoc/*strTemp*/);

	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CXLangRibbonMainPanelButton(ID_APP_EXIT, g_sLangTxt_Exit1/*strTemp*/,g_sLangTxt_Exit1Tip, 15));

	CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(g_sLangTxt_CharCurveOprt/*_T("特性曲线操作")*/, IDB_WRITESMALL, IDB_WRITELARGE);

	CMFCRibbonPanel* pPane = pCategoryHome->AddPanel(g_sLangTxt_CurveOprt/*_T("曲线操作")*/, m_PanelImages.ExtractIcon(27));
	CMFCRibbonButton* pBtn = NULL;
	
	pBtn = new CXLangRibbonButton(ID_CHAROPTR_NEWCHAR, g_sLangTxt_NewCurve/*_T("新建曲线")*/,g_sLangTxt_NewCurveTip, 0, 0);
	pPane->Add(pBtn);
	pBtn = new CXLangRibbonButton(ID_CHAROPTR_IMPORTFROMRIOFILE, g_sLangTxt_ImportCurve, g_sLangTxt_ImportCurveTip, 8, 8);
	pPane->Add(pBtn);
	pBtn = new CXLangRibbonButton(ID_CHAROPTR_SAVE, g_sLangTxt_SaveCurve/*_T("保存曲线")*/,g_sLangTxt_SaveCurveTip, 1, 1);
	pPane->Add(pBtn);
	pBtn = new CXLangRibbonButton(ID_CHAROPTR_SAVEAS,  g_sLangTxt_SaveAsCurve/*_T("曲线另存为")*/,g_sLangTxt_SaveAsCurveTip, 2, 2);
	pPane->Add(pBtn);
	pBtn = new CXLangRibbonButton(ID_CHAROPTR_DELETE, g_sLangTxt_DeleteCurve/*_T("删除曲线")*/,g_sLangTxt_DeleteCurveTip, 3, 3);
	pPane->Add(pBtn);
	pBtn = new CXLangRibbonButton(ID_CHAROPTR_EXPORT, g_sLangTxt_ExportCurve/*_T("导出曲线")*/,g_sLangTxt_ExportCurveTip, 4, 4);
	pPane->Add(pBtn);
	pBtn = new CXLangRibbonButton(ID_CHAROPTR_EDIT,  g_sLangTxt_ModifyCurve/*_T("修改曲线")*/,g_sLangTxt_ModifyCurveTip, 7, 7);
	pPane->Add(pBtn);

	pPane = pCategoryHome->AddPanel(g_sLangTxt_View/*_T("视图")*/, m_PanelImages.ExtractIcon(27));
	pBtn = new CXLangRibbonCheckBox(ID_VIEW_CHARPANE, g_sLangTxt_CurveBar/*_T("曲线栏")*/,g_sLangTxt_CurveBarTip);
	pPane->Add(pBtn);
	pBtn = new CXLangRibbonCheckBox(ID_VIEW_OUTPUTWND, g_sLangTxt_OutputBar1/*_T("输出栏")*/,g_sLangTxt_OutputBar1Tip);
	pPane->Add(pBtn);

	pPane = pCategoryHome->AddPanel(g_sLangTxt_HelpAbout /*_T("关于")*/, m_PanelImages.ExtractIcon(27));
	pBtn = new CXLangRibbonButton(ID_APP_ABOUT,g_sLangTxt_About1 /* _T("关于")*/,g_sLangTxt_About1Tip, 5, 5);
	pPane->Add(pBtn);
	pBtn = new CXLangRibbonButton(ID_APP_EXIT, g_sLangTxt_Exit1/*_T("退出")*/,g_sLangTxt_Exit1Tip, 6, 6);
	pPane->Add(pBtn);

	// 将元素添加到选项卡右侧:
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(-1, g_sLangTxt_Style/*strTemp*/, -1, -1);

	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* 无默认命令*/, TRUE /* 右对齐*/);

	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
	ASSERT(bNameValid);
	pVisualStyleButton->SetToolTipText(g_sLangTxt_StyleTip1);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
	ASSERT(bNameValid);
	pVisualStyleButton->SetDescription(g_sLangTxt_StyleTip2/*strTemp*/);
	m_wndRibbonBar.AddToTabs(pVisualStyleButton);

	// 添加快速访问工具栏命令:
	CList<UINT, UINT> lstQATCmds;

	lstQATCmds.AddTail(ID_FILE_NEW);
	lstQATCmds.AddTail(ID_FILE_OPEN);
	lstQATCmds.AddTail(ID_FILE_SAVE);
	lstQATCmds.AddTail(ID_FILE_PRINT_DIRECT);

	m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);

	m_wndRibbonBar.AddToTabs(new CXLangRibbonButton(ID_APP_ABOUT, g_sLangTxt_About1/*_T("\na")*/,g_sLangTxt_About1Tip, m_PanelImages.ExtractIcon (0)));
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// 创建类视图
	CString strCharLibView;
	bNameValid = strCharLibView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndCharLibView.Create(g_sLangTxt_ClassView/*strCharLibView*/, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“类视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建输出窗口
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(g_sLangTxt_OutPut/*strOutputWnd*/, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hCharLibViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndCharLibView.SetIcon(hCharLibViewIcon, FALSE);

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

void CMainFrame::OnCharoptrNewchar()
{
	CCharEditDlg dlg;
	dlg.m_strTitle = g_sLangTxt_ModifyCharCurve/*_T("修改特性曲线")*/;
	CCharacteristic *pCharTemp = new CCharacteristic();
	CCharacterFolder *pCurrFolder = m_wndCharLibView.GetCurrSelFolder();
	dlg.m_pCurrFolder = (CCharacterFolder *)pCurrFolder;
	pCharTemp->InitAfterRead();
	dlg.m_pCharTemp = pCharTemp;

	if (dlg.DoModal() == IDOK)
	{
		pCharTemp->m_strName = dlg.m_strName;
		pCharTemp->m_strID   = dlg.m_strID;
		pCharTemp->m_strAxis = dlg.m_strAxis;
		pCharTemp->m_strTestLineMode = dlg.m_strTestLineMode;
		pCharTemp->m_strXMin = dlg.m_strXMin;
		pCharTemp->m_strXMax = dlg.m_strXMax;
		pCharTemp->m_strYMin = dlg.m_strYMin;
		pCharTemp->m_strYMax = dlg.m_strYMax;

		pCurrFolder->AddNewChild(pCharTemp);
		m_wndCharLibView.InsertCharTemp(pCharTemp);
		theApp.OpenCharTemplate(pCharTemp);
	}
	else
	{
		delete pCharTemp;
	}
}

void CMainFrame::OnCharoptrSave()
{
	theApp.m_oCharacteristicLib.SaveCharLibFile(_T(""));
	char_dev_SetModifiedFlag(&theApp.m_oCharacteristicLib, FALSE);
}

void CMainFrame::OnUpdateCharoptrSave(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnCharoptrSaveas()
{
	// TODO: 在此添加命令处理程序代码
}

void CMainFrame::OnUpdateCharoptrSaveas(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnCharoptrDelete()
{
	// TODO: 在此添加命令处理程序代码
}

void CMainFrame::OnUpdateCharoptrDelete(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnCharoptrExport()
{
	// TODO: 在此添加命令处理程序代码
}

void CMainFrame::OnUpdateCharoptrExport(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnViewCharpane()
{
	if (m_wndCharLibView.IsVisible())
	{
		m_wndCharLibView.ShowPane(FALSE, FALSE, FALSE);
	}
	else
	{
		m_wndCharLibView.ShowPane(TRUE, FALSE, TRUE);
	}
}

void CMainFrame::OnUpdateViewCharpane(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndCharLibView.IsVisible());
}

void CMainFrame::OnViewOutputwnd()
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

void CMainFrame::OnUpdateViewOutputwnd(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndOutput.IsVisible());
}

void CMainFrame::UpdateCharTemp(CCharacteristic *pCharTemp)
{
	m_wndCharLibView.UpdateCharTemp(pCharTemp);
}
void CMainFrame::OnClose()
{
	if (!char_dev_GetModifiedFlag(&theApp.m_oCharacteristicLib))
	{
		CMDIFrameWndEx::OnClose();
		return;
	}

	int nRet = MessageBox(g_sLangTxt_CharCurveSave/*_T("特性曲线库已经被修改，是否保存修改？")*/,g_sLangTxt_Message1/*_T("提示")*/,MB_YESNOCANCEL|MB_ICONQUESTION);

	switch(nRet)
	{
	case IDYES:
		theApp.m_oCharacteristicLib.SaveCharLibFile(_T(""));
		break;
	case IDNO:
		break;
	case IDCANCEL:
		return;
	}

	CMDIFrameWndEx::OnClose();
}

void CMainFrame::OnCharoptrImportfromriofile()
{
	CDlgImportCharFromRioFile dlgImport;

	if (dlgImport.DoModal() != IDOK)
	{
		return;
	}

	CCharEditDlg dlgEdit;
	dlgEdit.m_strTitle = g_sLangTxt_ModifyCharCurve/*_T("修改特性曲线")*/;
	CCharacteristic *pCharTemp = dlgImport.m_pCharacteristic;
	CCharacterFolder *pCurrFolder = m_wndCharLibView.GetCurrSelFolder();
	dlgEdit.m_pCurrFolder = (CCharacterFolder *)pCurrFolder;
	pCharTemp->InitAfterRead();
	dlgEdit.m_pCharTemp = pCharTemp;

	dlgEdit.DoModal();
	
	pCharTemp->m_strName = dlgEdit.m_strName;
	pCharTemp->m_strID   = dlgEdit.m_strID;
	pCharTemp->m_strAxis = dlgEdit.m_strAxis;
	pCharTemp->m_strTestLineMode = dlgEdit.m_strTestLineMode;
	pCharTemp->m_strXMin = dlgEdit.m_strXMin;
	pCharTemp->m_strXMax = dlgEdit.m_strXMax;
	pCharTemp->m_strYMin = dlgEdit.m_strYMin;
	pCharTemp->m_strYMax = dlgEdit.m_strYMax;

	pCurrFolder->AddNewChild(pCharTemp);
	m_wndCharLibView.InsertCharTemp(pCharTemp);
	theApp.OpenCharTemplate(pCharTemp);
}
