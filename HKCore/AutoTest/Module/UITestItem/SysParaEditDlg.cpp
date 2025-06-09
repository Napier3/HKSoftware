// SysParaEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SysParaEditDlg.h"
#include "../TestControl/TestControlWnd.h"
#include "../../../Module/api/GloblaDrawFunctions.h"
// #include "..\GuideBook\SysParaEditGroupMngr.h"
#include "..\TestControl/TCtrlCntrBaseApp.h"
#include "..\XLanguageResourceAts.h"
// CSysParaEditDlg 对话框

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifndef _UITEST_USE_DIALOGEX
IMPLEMENT_DYNAMIC(CSysParaEditDlg, CDialog)
#endif

CSysParaEditDlg::CSysParaEditDlg(CWnd* pParent /*=NULL*/)
//: CDialog(CSysParaEditDlg::IDD, pParent)
{
	m_lfFont = InitLogFont();
#ifdef UNICODE
	lstrcpy(m_lfFont.lfFaceName,_T("Tahoma"));
#else
	strcpy(m_lfFont.lfFaceName, _T("Tahoma"));
#endif // UNICODE

	m_lfFont.lfHeight = 16;
	m_lfFont.lfWeight = 0;
	m_font.CreateFontIndirect(&m_lfFont);
	m_lfFont.lfHeight = 14;
	m_fontRsltCtrl.CreateFontIndirect(&m_lfFont);

	m_bSysPara = FALSE;

	m_pStesFileToolsFactory = CStesFileToolsFactory::Create();
	//m_pSysParaEditGroups = new CSysParaEditGroups();
}

CSysParaEditDlg::~CSysParaEditDlg()
{
	CStesFileToolsFactory::Release();
}

void CSysParaEditDlg::DoDataExchange(CDataExchange* pDX)
{
#ifdef _UITEST_USE_DIALOGEX
	CDynDialogEx::DoDataExchange(pDX);
#else
	CDialog::DoDataExchange(pDX);
#endif
}

#ifdef _UITEST_USE_DIALOGEX
BEGIN_MESSAGE_MAP(CSysParaEditDlg, CDynDialogEx)
#else
BEGIN_MESSAGE_MAP(CSysParaEditDlg, CDialog)
#endif
	ON_BN_CLICKED(IDC_SYSEDIT_BTN_OK, &CSysParaEditDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SYSEDIT_BTN_IMPORT, &CSysParaEditDlg::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_SYSEDIT_BTN_EXPORT, &CSysParaEditDlg::OnBnClickedBtnExport)
	ON_MESSAGE(WM_GRID_END_EDIT,  &CSysParaEditDlg::OnEndEdit)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_SYSEDIT_TAB_PARASEL_0, &CSysParaEditDlg::OnSelchangeTab1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSysParaEditDlg 消息处理程序

void CSysParaEditDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
	ShowWindow(SW_HIDE);

	//发送消息给TestControl，测试完成，填写报告
	if(m_pWndMsgRcv)
	{
		m_pWndMsgRcv->PostMessage(WM_SYSPARAEDIT_TEST_FINISHED, (WPARAM)m_pTestItemSysParaEdit, 1);
	}
}

void CSysParaEditDlg::OnBnClickedBtnImport()
{
// 	CSysParaEditGroups *pGroups = (CSysParaEditGroups*)m_pTestItemSysParaEdit->GetSysParaEditGroup();
// 	BOOL bTrue = FALSE;
// 
// 	if(m_strDatasetPathForEdit == g_strrSets || m_strDatasetPathForEdit == g_strrSoftswitchs || m_strDatasetPathForEdit == g_strrCtrlWords
// 		|| m_strDatasetPathForEdit == g_strwSets || m_strDatasetPathForEdit == g_strwSoftswitchs || m_strDatasetPathForEdit == g_strwCtrlWords)
// 	{
// 		ASSERT (m_pStesFileToolsFactory != NULL);
// 		CString strPath;
// 		strPath = _P_GetLibraryPath();
// 		bTrue =m_pStesFileToolsFactory->ImportFile(pGroups, this, strPath);
// 	}
// 	else
// 	{
// 
// 	}
// 
// 	if (bTrue)
// 	{
// 		ShowSysParaDatas();
// 	}
}

void CSysParaEditDlg::OnBnClickedBtnExport()
{
// 	CSysParaEditGroups *pGroups = (CSysParaEditGroups*)m_pTestItemSysParaEdit->GetSysParaEditGroup();
// 
// 	if(m_strDatasetPathForEdit == g_strrSets || m_strDatasetPathForEdit == g_strrSoftswitchs || m_strDatasetPathForEdit == g_strrCtrlWords
// 		|| m_strDatasetPathForEdit == g_strwSets || m_strDatasetPathForEdit == g_strwSoftswitchs || m_strDatasetPathForEdit == g_strwCtrlWords)
// 	{
// 		CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;
// 		ASSERT (m_pStesFileToolsFactory != NULL);
// 		CString strPath;
// 		strPath = _P_GetLibraryPath();
// 		m_pStesFileToolsFactory->ExportFile(pGroups, this, strPath, pApp->m_WordApp);
// 	}
// 	else
// 	{
// 
// 	}
}

void CSysParaEditDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

void CSysParaEditDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CSysParaEditDlg::OnClose()
{
	//停止测试
	ASSERT (m_pWndMsgRcv != NULL);

	if(m_pWndMsgRcv)
	{
		m_pWndMsgRcv->PostMessage(WM_SYSPARAEDIT_TEST_FINISHED, (WPARAM)m_pTestItemSysParaEdit, 0);
	}

	ShowWindow(SW_HIDE);
}

BOOL CSysParaEditDlg::OnInitDialog()
{
#ifdef _UITEST_USE_DIALOGEX
	CDynDialogEx::OnInitDialog();
#else
	CDialog::OnInitDialog();
#endif
	// TODO:  在此添加额外的初始化
	InitMacroRect();

	MoveWindow(&m_rectWin);
	CenterWindow();

	DWORD dwStyle = BS_PUSHBUTTON;
	m_btnNext.Create(g_sLangTxt_NextStep,dwStyle,m_rectBtnNext,this,IDC_SYSEDIT_BTN_OK);
	m_btnNext.SetFont(&m_font);
	m_btnNext.MoveWindow(&m_rectBtnNext);
	m_btnNext.ShowWindow(SW_SHOW);

	m_btnImport.Create(g_sLangTxt_Import/*g_strUI_BtnCaptionImport*/,dwStyle,m_rectImport,this,IDC_SYSEDIT_BTN_IMPORT);
	m_btnImport.SetFont(&m_font);
	m_btnImport.MoveWindow(&m_rectImport);
	m_btnImport.ShowWindow(SW_HIDE);

	m_btnExport.Create(g_sLangTxt_Export/*g_strUI_BtnCaptionExport*/,dwStyle,m_rectExport,this,IDC_SYSEDIT_BTN_EXPORT);
	m_btnExport.SetFont(&m_font);
	m_btnExport.MoveWindow(&m_rectExport);
	m_btnExport.ShowWindow(SW_HIDE);

// 	m_tabParaEditSel.Create(dwStyle,rectTab,this,IDC_SYSEDIT_TAB_PARASEL_0);
// 	m_tabParaEditSel.SetFont(&m_font);
// 	m_tabParaEditSel.MoveWindow(&rectTab);
// 	m_tabParaEditSel.ShowWindow(SW_SHOW);
// 
	m_gridSysPara.Create(m_rectGrid,this,IDC_SYSEDIT_RELAYSETGRID);
	m_gridSysPara.SetFont(&m_font);
	m_gridSysPara.MoveWindow(&m_rectGrid);
	m_gridSysPara.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSysParaEditDlg::InitTestItem(const CString &strSysParaID, CTestControlWnd *pWndMsgRcv, CDevice *pDevice)
{
	m_pWndMsgRcv = pWndMsgRcv;

	SetWindowText(g_sLangTxt_ViewPara/*_T("查看参数")*/);
	m_pTestItemSysParaEdit = NULL;

	m_pCurDevice = pDevice;
	ASSERT(m_pCurDevice != NULL);

//	m_tabParaEditSel.DeleteAllItems();
	m_strDatasetPathForEdit = strSysParaID;
	m_gridSysPara.InitGrid(TRUE);

	InitTableItems();

	m_btnNext.SetWindowText(g_sLangTxt_Finish);//g_strTestBtnOK_Finish);

	ShowWindow(SW_SHOW);
}

void CSysParaEditDlg::InitTestItem(CSysParaEdit* pTestItemSysParaEdit, CTestControlWnd *pWndMsgRcv)
{
	m_pWndMsgRcv = pWndMsgRcv;
	ASSERT (pTestItemSysParaEdit != NULL);

	if (pTestItemSysParaEdit == NULL)
	{
		return;
	}

	SetWindowText(pTestItemSysParaEdit->GetName());
	m_pTestItemSysParaEdit = pTestItemSysParaEdit;

	m_pCurDevice = (CDevice*)pTestItemSysParaEdit->GetAncestor(GBCLASSID_DEVICE);
	ASSERT(m_pCurDevice != NULL);

//	m_tabParaEditSel.DeleteAllItems();
	m_strDatasetPathForEdit = pTestItemSysParaEdit->GetDatasetPath();
	m_gridSysPara.InitGrid(TRUE);

	InitListData();
	ShowSysParaDatas();
	//InitTableItems();

	if (m_pWndMsgRcv->m_pTestControl->HasNextItemNeedTest())
	{
		m_btnNext.SetWindowText(g_sLangTxt_NextStep);//g_strTestBtnOK_Next);
	}
	else
	{
		m_btnNext.SetWindowText(g_sLangTxt_Finish);//g_strTestBtnOK_Finish);
	}

// 	if (m_pTestItemSysParaEdit->GetCommCmds()->GetCount() > 0)
// 	{
// 		m_btnNext.EnableWindow(FALSE);
// 	}

	ShowWindow(SW_SHOW);
}

void CSysParaEditDlg::InitTableItems()
{
// 	CSysParaEditGroups *pGroups = (CSysParaEditGroups*)m_pTestItemSysParaEdit->GetSysParaEditGroup();
// 	CSysParaEditGroup *pGroup = NULL;
// 
// 	POS pos = pGroups->GetHeadPosition();
// 	long nIndex = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pGroup = (CSysParaEditGroup *)pGroups->GetNext(pos);
// 		m_tabParaEditSel.InsertItem(nIndex, pGroup->m_strName, nIndex);
// 		nIndex++;
// 	}
// 
// 	m_tabParaEditSel.SetCurSel(0);
	ShowSysParaDatas();
}

void CSysParaEditDlg::ShowSysParaDatas()
{
	m_gridSysPara.InitVariables_Dataset(m_pTestItemSysParaEdit->GetSysParaEditDataObjList(), m_pTestItemSysParaEdit->GetParas());
}

void CSysParaEditDlg::FinishTestCmmCmdItem()
{
	m_gridSysPara.UpdateVariables();
}

void CSysParaEditDlg::UIFinishTestItem()
{
	FinishTestCmmCmdItem();
	m_btnNext.EnableWindow(TRUE);
}

LRESULT CSysParaEditDlg::OnEndEdit(WPARAM wParam, LPARAM lParam)
{
	long nCol,nRow;
	nCol = lParam & 0x0FFFF;
	nRow = (lParam>>16) & 0x0FFFF;
	m_gridSysPara.OnEndEdit(nRow, nCol);


	return 0;
}

void CSysParaEditDlg::InitListData()
{
	long nMode = 0;
	m_pTestItemSysParaEdit->InitDataList(nMode);
}

void CSysParaEditDlg::ChangeCurGroup(long nIndex)
{

}

//初始化RECT
void CSysParaEditDlg::InitMacroRect()
{
	m_rectWin.top = SYSEDIT_WIN_TOP;
	m_rectWin.bottom = SYSEDIT_WIN_BOTTOM;
	m_rectWin.left = SYSEDIT_WIN_LEFT;
	m_rectWin.right= SYSEDIT_WIN_RIGHT;

	m_rectTab.top = SYSEDIT_Tab_TOP;
	m_rectTab.bottom = SYSEDIT_Tab_BOTTOM;
	m_rectTab.left = SYSEDIT_Tab_LEFT;
	m_rectTab.right= SYSEDIT_Tab_RIGHT;

	m_rectGrid.top = SYSEDIT_Grid_TOP;
	m_rectGrid.bottom = SYSEDIT_Grid_BOTTOM;
	m_rectGrid.left = SYSEDIT_Grid_LEFT;
	m_rectGrid.right= SYSEDIT_Grid_RIGHT;
	m_rectGrid = m_rectTab;

	m_rectBtnNext.top = SYSEDIT_BTN_NEXT_TOP;
	m_rectBtnNext.bottom = SYSEDIT_BTN_NEXT_BOTTOM;
	m_rectBtnNext.left = SYSEDIT_BTN_NEXT_LEFT;
	m_rectBtnNext.right= SYSEDIT_BTN_NEXT_RIGHT;

	m_rectImport.top = SYSEDIT_BTN_IMPORT_TOP;
	m_rectImport.bottom = SYSEDIT_BTN_IMPORT_BOTTOM;
	m_rectImport.left = SYSEDIT_BTN_IMPORT_LEFT;
	m_rectImport.right= SYSEDIT_BTN_IMPORT_RIGHT;

	m_rectExport.top = SYSEDIT_BTN_EXPORT_TOP;
	m_rectExport.bottom = SYSEDIT_BTN_EXPORT_BOTTOM;
	m_rectExport.left = SYSEDIT_BTN_EXPORT_LEFT;
	m_rectExport.right= SYSEDIT_BTN_EXPORT_RIGHT;
}

