// XFileMngrFrame.cpp : 实现文件
//

#include "stdafx.h"
// #include "StationTestMain.h"
#include "XFileMngrFrame.h"

#include "XFileMngrFolderView.h"
#include "XFileMngrListView.h"

#include "XFileMngrDoc.h"
#include "DocFrameMngr.h"

// CXFileMngrFrame

IMPLEMENT_DYNCREATE(CXFileMngrFrame, CMDIChildWndEx)

CXFileMngrFrame::CXFileMngrFrame()
{
	m_pXFileMngrListView   = NULL;
	m_pXFileMngrFolderView = NULL;
	m_pXFileMngrDoc = NULL;
}

CXFileMngrFrame::~CXFileMngrFrame()
{
}


CXFileMngrFrame* UI_GetCXFileMngrFrame(CView *pView)
{
	CWnd *pParent = pView->GetParent();
	CXFileMngrFrame *Find = NULL;

	while (pParent != NULL)
	{
		if (pParent->IsKindOf(RUNTIME_CLASS(CXFileMngrFrame)) )
		{
			Find = (CXFileMngrFrame*)pParent;
			break;
		}

	}

	return Find;
}


BOOL CXFileMngrFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(&rect);

	m_wndSplitter.CreateStatic(this, //父窗口指针
		1, // 切分的行数
		2); // 切分的列数

	m_wndSplitter.CreateView(0,0, // 窗格的行、列序数
		RUNTIME_CLASS(CXFileMngrFolderView),//视图类
		CSize(rect.Width()/3,rect.Height()),//初始化大小
		pContext);//父窗口的创建参数

	//为第二个窗格产生视图
	m_wndSplitter.CreateView(0,1,
		RUNTIME_CLASS(CXFileMngrListView),
		CSize(rect.Width()*2/3,rect.Height()),
		pContext);

	m_pXFileMngrFolderView = (CXFileMngrFolderView*)m_wndSplitter.GetPane(0, 0);
	m_pXFileMngrListView   = (CXFileMngrListView*)m_wndSplitter.GetPane(0, 1);

	CXFolderTreeCtrl *pXFolderTreeCtrl = m_pXFileMngrFolderView->GetXFolderTreeCtrl();
	CXFileListView   *pXFileListView    = m_pXFileMngrListView->GetXFileListView();
	m_pXFileMngrFolderView->AttachXFileListView(pXFileListView, this);
	m_pXFileMngrListView->AttatchXFolderTreeCtrl(pXFolderTreeCtrl, this);

// 	m_pXFileMngrWnd = this;
// 	m_pXFileMsgRcvWndRef = (CXFileMngrDoc*)m_pXFileMngrDoc;
// 	m_pXFolderTreeRef    = m_pXFileMngrFolderView->GetXFolderTreeCtrl();
// 	m_pXFileListRef      = m_pXFileMngrListView->GetXFileListView();
// 	m_pXFileMngrWnd      = this;

	return TRUE;
}

BEGIN_MESSAGE_MAP(CXFileMngrFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_ADD, OnUpdateFolderAdd)
// 	ON_COMMAND(XFID_XFILEMNGR_FOLDER_ADD, OnFolderAdd)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_DELETE, OnUpdateFolderDelete)
// 	ON_COMMAND(XFID_XFILEMNGR_FOLDER_DELETE, OnFolderDelete)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EDIT, OnUpdateFolderEdit)
// 	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EDIT, OnFolderEdit)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EXPORT, OnUpdateFolderExport)
// 	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EXPORT, OnFolderExport)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_IMPORT, OnUpdateFolderImport)
// 	ON_COMMAND(XFID_XFILEMNGR_FOLDER_IMPORT, OnFolderImport)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_COPY, OnUpdateFileCopy)
// 	ON_COMMAND(XFID_XFILEMNGRFILE_COPY, OnFileCopy)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_PASTE, OnUpdateFilePaste)
// 	ON_COMMAND(XFID_XFILEMNGRFILE_PASTE, OnFilePaste)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_DELETE, OnUpdateFileDelete)
// 	ON_COMMAND(XFID_XFILEMNGRFILE_DELETE, OnFileDelete)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EDIT, OnUpdateFileEdit)
// 	ON_COMMAND(XFID_XFILEMNGRFILE_EDIT, OnFileEdit)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EXPORT, OnUpdateFileExport)
// 	ON_COMMAND(XFID_XFILEMNGRFILE_EXPORT, OnFileExport)
// 	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_IMPORT, OnUpdateFileImport)
// 	ON_COMMAND(XFID_XFILEMNGRFILE_IMPORT, OnFileImport)
// 	ON_MESSAGE(WM_INIT_XFILEMNGR_MENU, OnInitXFileMngrMenu)
END_MESSAGE_MAP()


// CXFileMngrFrame 消息处理程序

void CXFileMngrFrame::OnClose()
{
	CDocFrameMngr::CloseDocFrame(m_strDocID);

	CMDIChildWndEx::OnClose();
}


void CXFileMngrFrame::ShowXFileMngr(CXFileMngr *pXFileMngr)
{
// 	m_pXFileMngrRef = pXFileMngr;
	CXFolderTreeCtrl *pXFolderTreeCtrl = m_pXFileMngrFolderView->GetXFolderTreeCtrl();
	CXFileListView   *pXFileListView    = m_pXFileMngrListView->GetXFileListView();
	pXFolderTreeCtrl->SetXFileMsgRcvWnd((CXFileMngrDoc*)m_pXFileMngrDoc);

	m_pXFileMngrFolderView->ShowXFileMngr(pXFileMngr);
}

void CXFileMngrFrame::SetFramwWnd(CWnd *pFrameWnd)
{
	ASSERT (m_pXFileMngrListView != NULL);
	CXFileListView   *pXFileListView    = m_pXFileMngrListView->GetXFileListView();
	pXFileListView->SetFrameWnd(pFrameWnd);
}

void CXFileMngrFrame::ExecXFile(CXFile *pFile)
{
	// 	CXFileType *pXFileType = m_oXFileMngr.FindFileType(pFile);
	// 
	// 	if (pXFileType == NULL)
	// 	{
	// 		return;
	// 	}
	// 
	// 	if (pXFileType->m_strExe.GetLength() == 0)
	// 	{
	// 		return;
	// 	}
	// 
	// 	CString strExe = _P_GetFullPath(pXFileType->m_strExe);
	// 	CString strFile;
	// 	strFile.Format(_T("\"%s\""), pFile->GetTotalFileName());
	// 
	// 	ExecuteFile(strExe, strFile, pXFileType->m_strRunMode);
}


// 
// 
// void CXFileMngrFrame::OnUpdateFolderAdd(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderAdd(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFolderAdd()
// {
// 	xfile_OnFolderAdd();
// }
// 
// void CXFileMngrFrame::OnUpdateFolderDelete(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFolderDelete()
// {
// 	xfile_OnFolderDelete();
// }
// 
// void CXFileMngrFrame::OnUpdateFolderEdit(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFolderEdit()
// {
// 	xfile_OnFolderEdit();
// }
// 
// void CXFileMngrFrame::OnUpdateFolderExport(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFolderExport()
// {
// 	xfile_OnFolderExport();
// }
// 
// void CXFileMngrFrame::OnUpdateFolderImport(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFolderImport()
// {
// 	xfile_OnFolderImport();
// }
// 
// void CXFileMngrFrame::OnUpdateFileCopy(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFileCopy()
// {
// 	xfile_OnFileCopy();
// }
// 
// void CXFileMngrFrame::OnUpdateFilePaste(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFilePaste()
// {
// 	xfile_OnFilePaste();
// }
// 
// void CXFileMngrFrame::OnUpdateFileDelete(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFileDelete()
// {
// 	xfile_OnFileDelete();
// }
// 
// void CXFileMngrFrame::OnUpdateFileEdit(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFileEdit()
// {
// 	xfile_OnFileEdit();
// }
// 
// void CXFileMngrFrame::OnUpdateFileExport(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// void CXFileMngrFrame::OnFileExport()
// {
// 	xfile_OnFileExport();
// }
// 
// void CXFileMngrFrame::OnUpdateFileImport(CCmdUI* pCmdUI)
// {
// 	xfile_OnUpdateFolderDelete(pCmdUI);
// }
// 
// 
// void CXFileMngrFrame::OnFileImport()
// {
// 	xfile_OnFileImport();
// }
// // 
// // void CXFileMngrFrame::OnSaveAsFile(CXFolder *pCurrFolder, const CString &strFile)
// // {
// // 	xfile_OnSaveAsFile(pCurrFolder, strFile);
// // }
// 
// LRESULT CXFileMngrFrame::OnInitXFileMngrMenu(WPARAM wParam, LPARAM lParam)
// {
// 	return xfile_OnInitXFileMngrMenu(wParam, lParam);
// }
