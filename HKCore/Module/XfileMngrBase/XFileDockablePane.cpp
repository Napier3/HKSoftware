// XFileDockablePane.cpp : 实现文件
//

#include "stdafx.h"
#include "XFileDockablePane.h"

#include "XFilePasteDlg.h"
#include "XFileEditDlg.h"

#include "XFolderEditDlg.h"
#include "XFolderAddDlg.h"
#include "..\API\GloblaDrawFunctions.h"
#include "..\XLanguage\XLanguageMngr.h"

#ifdef _Use_YUN_Client_
	#include "YunFileApi\XYunFileApi.h"
#endif

// CXFileDockablePane

IMPLEMENT_DYNAMIC(CXFileDockablePane, CDockablePane)

CXFileDockablePane::CXFileDockablePane()
{
	m_pXFileMngr = NULL;
	m_pFilterTextMngr = NULL;
	m_nIDB_XFILEMNGR = 0;
	m_pXFileMsgRcvWnd = NULL;
	m_bFilterTextMngrCreate = FALSE;
	m_bDeleteAllFolder = TRUE;

	CFilterTextXmlRWKeys::Create();
}

CXFileDockablePane::~CXFileDockablePane()
{
	FreeFilterTextMngr();
	CFilterTextXmlRWKeys::Release();
}

void CXFileDockablePane::FreeFilterTextMngr()
{
	if (m_bFilterTextMngrCreate)
	{
		delete m_pFilterTextMngr;
		m_pFilterTextMngr = NULL;
	}

	m_bFilterTextMngrCreate = FALSE;
}

void CXFileDockablePane::CreateFilterTextMngr(const CString &strFile)
{
	FreeFilterTextMngr();
	m_bFilterTextMngrCreate = TRUE;

	m_pFilterTextMngr = new CFilterTextMngr();
	CString strFilterFile;

	if (strFile.GetAt(1) != ':')
	{
		strFilterFile = _P_GetConfigPath();
		strFilterFile += strFile;
	}
	else
	{
		strFilterFile = strFile;
	}

	m_pFilterTextMngr->OpenXmlFile(strFilterFile);
}

void CXFileDockablePane::ShowXFileTree(CXFileMngr* pXFileMngr)
{
	m_pXFileMngr = pXFileMngr;
	m_wndXFileTree.ShowXFileMngr(pXFileMngr);
	pXFileMngr->SetRefCtrrCtrl(&m_wndXFileTree);
}

void CXFileDockablePane::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	if (m_wndXFileTree.GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);
	int cyTlb = 0;
	
	if (m_nIDR_XFILEMNGR_TOOLBAR > 0)
	{
		cyTlb = m_wndXToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	}

	int cyButton = 20;
	int cxButton = 80;
	int cxCmb = 0;
	int nWidth = rectClient.Width()-8;

	if (cxButton > nWidth / 2)
	{
		cxButton = nWidth / 2;
		cxCmb = cxButton;
	}
	else
	{
		cxButton = 80;
		cxCmb = nWidth - cxButton;
	}

	long nTreeTop = rectClient.top + cyTlb + 1;
	long nTreeHeight =  rectClient.Height() - cyTlb - 2 - cyButton;
	long nTreeBottom = nTreeTop + nTreeHeight;

	if (m_nIDR_XFILEMNGR_TOOLBAR > 0)
	{
		m_wndXToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	}

	m_wndXFileTree.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, nTreeHeight-2, SWP_NOACTIVATE | SWP_NOZORDER);

	m_cmbFilterText.SetWindowPos(NULL, rectClient.left + 2, nTreeBottom, cxCmb, cyButton, SWP_NOACTIVATE | SWP_NOZORDER);
	m_btnFilter.SetWindowPos(NULL, rectClient.left + 4 + cxCmb, nTreeBottom, cxButton, cyButton, SWP_NOACTIVATE | SWP_NOZORDER);
	m_btnFilter.EnableWindow(TRUE);
}


BEGIN_MESSAGE_MAP(CXFileDockablePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_ADD, OnUpdateFolderAdd)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_ADD, OnFolderAdd)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_DELETE, OnUpdateFolderDelete)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_DELETE, OnFolderDelete)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EDIT, OnUpdateFolderEdit)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EDIT, OnFolderEdit)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EXPORT, OnUpdateFolderExport)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EXPORT, OnFolderExport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_IMPORT, OnUpdateFolderImport)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_IMPORT, OnFolderImport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_COPY, OnUpdateFileCopy)
	ON_COMMAND(XFID_XFILEMNGRFILE_COPY, OnFileCopy)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_PASTE, OnUpdateFilePaste)
	ON_COMMAND(XFID_XFILEMNGRFILE_PASTE, OnFilePaste)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_DELETE, OnUpdateFileDelete)
	ON_COMMAND(XFID_XFILEMNGRFILE_DELETE, OnFileDelete)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EDIT, OnUpdateFileEdit)
	ON_COMMAND(XFID_XFILEMNGRFILE_EDIT, OnFileEdit)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EXPORT, OnUpdateFileExport)
	ON_COMMAND(XFID_XFILEMNGRFILE_EXPORT, OnFileExport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_IMPORT, OnUpdateFileImport)
	ON_COMMAND(XFID_XFILEMNGRFILE_IMPORT, OnFileImport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_DOWNLOAD, OnUpdateFileDownload)
	ON_COMMAND(XFID_XFILEMNGRFILE_DOWNLOAD, OnFileDownload)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_UPLOAD, OnUpdateFileUpload)
	ON_COMMAND(XFID_XFILEMNGRFILE_UPLOAD, OnFileUpload)
	ON_COMMAND(XFID_STCFGFILE_VIEW_BTN_FILTER, OnFileFilter)
	ON_UPDATE_COMMAND_UI(XFID_STCFGFILE_VIEW_BTN_FILTER, OnUpdateFileFilter)
	ON_MESSAGE(WM_INIT_XFILEMNGR_MENU, OnInitXFileMngrMenu)
	ON_MESSAGE(WM_THREAD_XFILE_MNGR, OnXFileMngrSelChanged)
	ON_NOTIFY(NM_DBLCLK, XFID_STCFGFILE_VIEW_TREE, &CXFileDockablePane::OnNMDblclkTreeFile)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TVN_SELCHANGED, XFID_STCFGFILE_VIEW_TREE, OnTvnSelchangedXFile)
END_MESSAGE_MAP()



// CXFileDockablePane 消息处理程序
int CXFileDockablePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;

	if (!m_wndXFileTree.Create(dwViewStyle, rectDummy, this, XFID_STCFGFILE_VIEW_TREE))
	{
		TRACE0("未能创建XFile视图\n");
		return -1;      // 未能创建
	}
	
	CWnd *pFrameWnd = GetParent();
	//ASSERT(pFrameWnd != NULL && pFrameWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)));
	m_wndXFileTree.SetFrameWnd(pFrameWnd);

	// 加载视图图像:
	if (m_nIDB_XFILEMNGR != 0)
	{
		m_XFileImages.Create(m_nIDB_XFILEMNGR, 16, 0, RGB(255, 0, 0));
	}
	else
	{
		xfile_LoadFileMngrBmp(&m_XFileImages);
	}

	m_wndXFileTree.SetImageList(&m_XFileImages, TVSIL_NORMAL);

	if (m_nIDR_XFILEMNGR_TOOLBAR > 0)
	{
		m_wndXToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, m_nIDR_XFILEMNGR_TOOLBAR);
		m_wndXToolBar.LoadToolBar(m_nIDR_XFILEMNGR_TOOLBAR, 0, 0, TRUE /* 已锁定*/);
		m_wndXToolBar.SetPaneStyle(m_wndXToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
		m_wndXToolBar.SetPaneStyle(m_wndXToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
		m_wndXToolBar.SetOwner(this);
		m_wndXToolBar.SetRouteCommandsViaFrame(FALSE);
	}

	m_cmbFilterText.Create(WS_VISIBLE |WS_CHILD/*|WS_VISIBLE*/|CBS_DROPDOWN|CBS_AUTOHSCROLL|WS_VSCROLL|WS_TABSTOP , CRect(0, 0, 20, 300), this, XFID_STCFGFILE_VIEW_CMB_FILTER);
	m_btnFilter.Create(g_sLangTxt_Filter/*_T("过滤")*/,WS_VISIBLE | BS_PUSHBUTTON,CRect(0,0,50,30),this,XFID_STCFGFILE_VIEW_BTN_FILTER);
	m_btnFilter.EnableWindow(TRUE);

	m_cmbFilterText.SetAddEmptyString();
	m_cmbFilterText.InitFilterText(m_pFilterTextMngr);
	m_wndXFileTree.SetFrameWnd(this);

	m_cmbFilterText.SetFont(g_pGlobalFont);
	m_btnFilter.SetFont(g_pGlobalFont);

	AdjustLayout();

	return 0;
}

void CXFileDockablePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
	//st_PostAdjustCfgMsg();
}

void CXFileDockablePane::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndXFileTree.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CXFileDockablePane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndXFileTree.SetFocus();
}


void CXFileDockablePane::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{

}

void CXFileDockablePane::OnUpdateFolderAdd(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFolder != NULL || pFile != NULL);
}

void CXFileDockablePane::OnFolderAdd()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	CXFolderAddDlg dlg;
	dlg.m_pSrcFolder = pFolder;

	if (dlg.DoModal() == IDOK)
	{
		CXFolder *pNew = pFolder->AddFolder(dlg.m_strDestFolderName);
		m_wndXFileTree.Insert(pNew);
	}
}

void CXFileDockablePane::InsertFolderToTree(CXFolder *pXFolder)
{
	ASSERT (pXFolder != NULL);

	if (pXFolder == NULL)
	{
		return;
	}

	m_wndXFileTree.Insert(pXFolder);
}

void CXFileDockablePane::UpdateTree()
{
	m_wndXFileTree.Invalidate(TRUE);
}

void CXFileDockablePane::OnUpdateFolderDelete(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngr));
}

void CXFileDockablePane::OnFolderDelete()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	
	if (pFolder == NULL)
	{
		return ;
	}

	LRESULT nRet = m_pXFileMsgRcvWnd->XDeleteXFolder(pFolder);

	if (nRet == XFILEMNGR_OPTR_FAILED)
	{
		return;
	}

	if (!m_bDeleteAllFolder)
	{
		if (pFolder->GetCount() > 0)
		{
			CString strMsg;
			strMsg.Format(g_sLangTxt_FoldCoverFold/*_T("文件夹【%s】包含子文件夹或者文件\r\n请先删除子文件夹或者文件，然后再删除目录")*/, pFolder->m_strName);
			MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_OK | MB_ICONWARNING);
			return;
		}
	}

	CString strMsg;

	if (m_bDeleteAllFolder)
	{
		strMsg.Format(g_sLangTxt_DeleFold/*_T("删除文件夹将删除此文件夹及其下的全部文件及文件夹。\r\n确实要删除文件夹【%s】吗？")*/, pFolder->m_strName);
	}
	else
	{
		strMsg.Format( g_sLangTxt_SureDeleFold/*_T("确实要删除文件夹【%s】吗？")*/, pFolder->m_strName);
	}
	
	if (MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		return;
	}

	CXFolder *pParnt = (CXFolder*)pFolder->GetParent();

	HTREEITEM hNext = m_wndXFileTree.Delete(pFolder);

	if (m_bDeleteAllFolder)
	{
		pFolder->DeleteFolderEx();
	}
	else
	{
		pFolder->DeleteFolder();
	}

	pParnt->Delete(pFolder);
	m_wndXFileTree.SelectItem(hNext);
}

void CXFileDockablePane::OnUpdateFolderEdit(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngr));
}

void CXFileDockablePane::OnFolderEdit()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	if (pFolder == NULL)
	{
		return ;
	}

	CXFolderEditDlg dlg;
	dlg.m_pSrcFolder = pFolder;

	if (dlg.DoModal() == IDOK)
	{
		m_wndXFileTree.Update(pFolder);
	}

}

void CXFileDockablePane::OnUpdateFolderExport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngr));
}

void CXFileDockablePane::OnFolderExport()
{
	CXFolder *pSrcFolder = m_pXFileMngr->GetCurrSelFolder();

	if (pSrcFolder == NULL)
	{
		return;
	}

	TCHAR pszBuffer[MAX_PATH];
	bstr_t bstrText;
	bstrText = g_sLangTxt_ChoFoldExDir;

	if (!FGetDirectory(m_hWnd, pszBuffer, bstrText/*_T("选择配置文件夹导出目标目录")*/))
	{
		return;
	}

	//strDestParentPath：目标文件夹（父文件夹）
	//strDestPath：目标文件夹
	CString strDestParentPath = pszBuffer;
	CString strName;
	CString strDestPath = strDestParentPath + _P_FOLDER_PATH_SEPARATOR_ + pSrcFolder->m_strName;
	CString strMsg;

	if (IsFileExist(strDestPath))
	{
		strMsg.Format(g_sLangTxt_TargFolderExist/*_T("目标文件夹【%s】已经存在")*/, strDestPath);
		MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_OK | MB_ICONWARNING);
		return;
	}

	//pDestParentFolder=目标文件夹（父文件夹）
	CXFolder *pDestParentFolder = new CXFolder();
	pSrcFolder->CopyOwn(pDestParentFolder);
	pDestParentFolder->SetPath(strDestParentPath);

	CXFolder *pDestNew = (CXFolder*)pDestParentFolder->Paste(pSrcFolder);

	strMsg.Format(g_sLangTxt_ExpFileFin/*_T("导出目标文件夹【%s】完成")*/, strDestPath);
	MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_OK | MB_ICONINFORMATION);
	delete pDestParentFolder;
}

void CXFileDockablePane::OnUpdateFolderImport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
//	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFolder != NULL);
}

void CXFileDockablePane::OnFolderImport()
{
	TCHAR pszBuffer[MAX_PATH];
	bstr_t bstrText;
	bstrText = g_sLangTxt_ChoImpFile;

	if (!FGetDirectory(m_hWnd, pszBuffer, bstrText/*_T("选择导入的配置文件夹")*/))
	{
		return;
	}

	CString strPath = pszBuffer;
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	CString strName;
	long nPos = strPath.ReverseFind('\\');

	if (nPos < 0)
	{
		return;
	}

	strName = strPath.Mid(nPos+1);

	if (pFolder->FindByID(strName) != NULL)
	{
		CString strMsg;
		strMsg.Format(g_sLangTxt_ExiSaNameFile/*_T("存在同名称的文件夹【%s】")*/, strName);
		MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	CXFolder *pNew = pFolder->AddPath(strPath);
	m_wndXFileTree.Insert(pNew);
}

void CXFileDockablePane::OnUpdateFileCopy(CCmdUI* pCmdUI)
{
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFileDockablePane::OnFileCopy()
{
	m_pXFileMngr->CopyFile();
}

void CXFileDockablePane::OnUpdateFilePaste(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	CXFile *pFile = m_pXFileMngr->GetCopySrcFile();

	pCmdUI->Enable(pFolder != NULL && pFile != NULL);
}

void CXFileDockablePane::OnFilePaste()
{
	CXFile *pFile = m_pXFileMngr->GetCopySrcFile();

	if (pFile == NULL)
	{
		return;
	}

	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	CXFile *pNewFile = NULL;

	if (pFolder->FindByID(pFile->m_strID) == NULL)
	{
		pNewFile = pFolder->AddFile(pFile);
	}
	else
	{
		CXFilePasteDlg dlg;
		dlg.m_pSrcFile = pFile;
		dlg.m_pDestFolder = pFolder;
		dlg.DoModal();

		pNewFile = dlg.m_pDestFile;
	}

	if (pNewFile == NULL)
	{
		return;
	}

	m_wndXFileTree.Insert(pNewFile);
	m_wndXFileTree.Select((HTREEITEM)pNewFile->m_dwItemData, TVGN_CARET);
}

void CXFileDockablePane::OnUpdateFileDelete(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFileDockablePane::OnFileDelete()
{
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();
	CString strFile = pFile->GetRelativePath(FALSE);
	CString strMsg;
	strMsg.Format(g_sLangTxt_SureDeleFile/*_T("你确实要删除文件【%s】吗？")*/, strFile);

	if (MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_OKCANCEL) != IDOK)
	{
		return;
	}

	if (m_pXFileMsgRcvWnd != NULL)
	{
		//LRESULT nRet = m_pXFileMsgRcvWnd->SendMessage(WM_XFILEMNGR_DELETE_XFILE, (WPARAM)pFile, (LPARAM)pFile);
		LRESULT nRet = m_pXFileMsgRcvWnd->XDeleteXFile(pFile);

		if (nRet == XFILEMNGR_OPTR_FAILED)
		{
			return;
		}
	}

	HTREEITEM hNextSel = m_wndXFileTree.Delete(pFile);
	m_pXFileMngr->DeleteFile(pFile);
	m_wndXFileTree.SelectItem(hNextSel);
}

//2017-2-17  lijunqing
void CXFileDockablePane::DeleteFile(CXFile *pXFile)
{
	HTREEITEM hItem = (HTREEITEM)pXFile->m_dwItemData;

	if (hItem != NULL)
	{
		m_wndXFileTree.DeleteItem(hItem);
	}

	m_pXFileMngr->DeleteFile(pXFile);
}

void CXFileDockablePane::SelectRoot()
{
	m_wndXFileTree.SelectNode(m_pXFileMngr);
}

void CXFileDockablePane::OnUpdateFileEdit(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFileDockablePane::OnFileEdit()
{
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	if (pFile == NULL)
	{
		return ;
	}

	CXFileEditDlg dlg;
	dlg.m_pSrcFile = pFile;
	dlg.m_pXFileMsgRcvWnd = m_pXFileMsgRcvWnd;

	if (dlg.DoModal() == IDOK)
	{
		m_wndXFileTree.Update(pFile);
	}

}

void CXFileDockablePane::OnUpdateFileExport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFileDockablePane::OnFileExport()
{
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();
	CString strPath = pFile->GetRelativePath(TRUE);
	CString strDestFile = pFile->m_strID;

	if (PopupSaveAsFileDialog(this, strDestFile, m_strXFileFilter, m_strXFilePostFix))
	{
// 		if (m_pXFileMsgRcvWnd != NULL)
// 		{
// 			LRESULT nRet = m_pXFileMsgRcvWnd->SendMessage(WM_XFILEMNGR_EXPORT_XFILE, (WPARAM)&strPath, (LPARAM)&strDestFile);
// 
// 			if (nRet == XFILEMNGR_OPTR_SUCC)
// 			{
// 				return;
// 			}
// 		}

		//::X_CopyFile(strPath, strDestFile, FALSE);
		XCopyFile(strPath, strDestFile, FALSE);
	}
}

void CXFileDockablePane::OnUpdateFileImport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL || pFolder != NULL);
}


void CXFileDockablePane::OnFileImport()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();

	if (pFolder == NULL)
	{
		return;
	}

	CString strSrcFile;
	CXFile *pFile = NULL;

	if (!PopupOpenFileDialog(this, strSrcFile, m_strXFileFilter, m_strXFilePostFix))
	{
		return;
	}
	
	if (pFolder->IsFileExist(strSrcFile))
	{
		CString strName = GetLastFolderNameFromPathName(strSrcFile);
		CString strMsg;
		strMsg.Format(g_sLangTxt_ExiSaNameFileCov/*_T("存在同名称的文件【%s】,覆盖吗？")*/, strName);
		
		if (MessageBox(strMsg, g_sLangTxt_FileCover/*_T("覆盖文件")*/, MB_OKCANCEL) == IDOK)
		{
			pFile = pFolder->OverWriteFile(strSrcFile);
		}
	}
	else
	{
		pFile = pFolder->AddFile(strSrcFile);
		if (pFile != NULL)
		{
			m_wndXFileTree.Insert(pFile);
		}
	}	
}

void CXFileDockablePane::OnUpdateFileDownload(CCmdUI* pCmdUI)
{

}

void CXFileDockablePane::OnFileDownload()
{
	CExBaseObject *pXObj = m_pXFileMngr->GetCurrSel();

	if (pXObj == NULL)
	{
		return;
	}

#ifdef _Use_YUN_Client_
	if (Yun_IsLoginSucc())
	{
		Yun_DownLoad(pXObj, TRUE);
	}
#endif
}

void CXFileDockablePane::OnUpdateFileUpload(CCmdUI* pCmdUI)
{

}

void CXFileDockablePane::OnFileUpload()
{
	CExBaseObject *pXObj = m_pXFileMngr->GetCurrSel();

	if (pXObj == NULL)
	{
		return;
	}

#ifdef _Use_YUN_Client_
	if (Yun_IsLoginSucc())
	{
		Yun_UpLoad(pXObj, TRUE);
	}
#endif
}

void CXFileDockablePane::OnSaveAsFile(CXFolder *pCurrFolder, const CString &strFile)
{
	CString strTemp = strFile;
	strTemp.MakeLower();
	CXFile *pFile = pCurrFolder->SelectFileInCurrFolder(strTemp);

	if (pFile == NULL)
	{
		pFile = pCurrFolder->AddFile2(strFile);
		if (pFile != NULL)
		{
			m_wndXFileTree.Insert(pFile);
		}
	}
	
}

CXFolder* CXFileDockablePane::OnSaveAsFolder(CXFolder *pCurrFolder, const CString &strFolder)
{
	CString strTemp = strFolder;
	strTemp.MakeLower();
	CXFolder *pFolder = pCurrFolder->SelectFolderInCurrFolder(strTemp);

	if (pFolder == NULL)
	{
		pFolder = pCurrFolder->AddFolder(strFolder, FALSE);

		if (pFolder != NULL)
		{
			m_wndXFileTree.Insert(pFolder);
		}
	}
	else
	{
		if (pFolder->m_dwItemData == 0)
		{
			m_wndXFileTree.Insert(pFolder);
		}
	}

	return pFolder;
}

void CXFileDockablePane::SetXFileMsgRcvWnd(CXFileOptrMsgRcvWnd *pWnd)
{
	m_pXFileMsgRcvWnd = pWnd;
	m_wndXFileTree.SetXFileMsgRcvWnd(pWnd);
}

void CXFileDockablePane::OnTvnSelchangedXFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	CExBaseObject *pSel = NULL;

	if (pNMTreeView->itemNew.hItem != NULL)
	{
		pSel = (CExBaseObject*)m_wndXFileTree.GetItemData(pNMTreeView->itemNew.hItem);
	}

	m_pXFileMngr->SetCurrSel(pSel);
	
	*pResult = 0;
}


void CXFileDockablePane::OnFileFilter()
{
	CString strFilterText;
	
	if (!m_cmbFilterText.GetFilterText(strFilterText))
	{
		return;
	}

	if (strFilterText.GetLength() == 0)
	{
		m_pXFileMngr->Filter(strFilterText, FILTERMODE_CLEAR);
	}
	else
	{
		m_pXFileMngr->Filter(strFilterText, FILTERMODE_HAS);
	}

	m_wndXFileTree.ShowXFileMngr(m_pXFileMngr);
}

void CXFileDockablePane::OnUpdateFileFilter(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

 LRESULT CXFileDockablePane::OnInitXFileMngrMenu(WPARAM wParam, LPARAM lParam)
 {
	CMenu *pMenu = (CMenu*)wParam;
	CExBaseObject* pObj = (CExBaseObject*)lParam;

	UINT nClassID = pObj->GetClassID();

	if (CLASSID_XFILE == nClassID)
	{
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);
		pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_COPY,g_sLangTxt_CopyFile/*_T("拷贝文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DELETE,g_sLangTxt_DeleteFile/*_T("删除文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EDIT,g_sLangTxt_FileRename/*_T("修改文件名称")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EXPORT,g_sLangTxt_ExportFile/*_T("导出文件")*/);
	}
	else if (nClassID == CLASSID_XFILEMNGR)
	{
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);
		pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
	}
	else if (nClassID == CLASSID_XFOLDER)
	{
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_DELETE,g_sLangTxt_DeleteDirectory /*_T("删除目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EDIT,g_sLangTxt_DirectoryRename/*_T("修改目录名称")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EXPORT,g_sLangTxt_ExportDirectory/*_T("导出目录")*/);
		pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
	}

#ifdef _Use_YUN_Client_
	if ((nClassID != CLASSID_XFILEMNGR) && Yun_IsLoginSucc())
#else
	if (nClassID != CLASSID_XFILEMNGR)
#endif
	{
		pMenu->AppendMenu(MF_SEPARATOR);

		if (xfile_IsYunFile(pObj))
		{
			pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DOWNLOAD,g_sLangTxt_DownLoad/*_T("下载")*/);
		}
		
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_UPLOAD,g_sLangTxt_UpLoad/*_T("上传")*/);
	}

	 return 0;
 }

 LRESULT CXFileDockablePane::OnXFileMngrSelChanged(WPARAM wParam, LPARAM lParam)
 {
	 CExBaseObject *pSel = (CExBaseObject*)wParam;

	 m_pXFileMngr->SetCurrSel(pSel);

	 return 0;
 }


 void CXFileDockablePane::OnNMDblclkTreeFile(NMHDR *pNMHDR, LRESULT *pResult)
 {
	 *pResult = 0;
	 CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	 if (pFile == NULL)
	 {
		 return;
	 }

	 if (m_pXFileMsgRcvWnd != NULL)
	 {
		 //m_pXFileMsgRcvWnd->PostMessage(WM_XFILEMNGR_OPEN_XFILE, (WPARAM)pFile, (LPARAM)pFile);
		 m_pXFileMsgRcvWnd->XOpenXFile(pFile);
	 }
 }

 void CXFileDockablePane::OnClose()
 {
	 // TODO: 在此添加消息处理程序代码和/或调用默认值

	 CDockablePane::OnClose();
 }

 void CXFileDockablePane::OnShowWindow(BOOL bShow, UINT nStatus)
 {
	 CDockablePane::OnShowWindow(bShow, nStatus);

	 //st_PostAdjustCfgMsg();
 }
