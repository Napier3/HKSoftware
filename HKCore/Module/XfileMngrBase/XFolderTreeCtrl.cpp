// XFileTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XFolderTreeCtrl.h"
#include "XFileListView.h"
#include "XFilePasteDlg.h"
#include "XFileEditDlg.h"

#include "XFolderEditDlg.h"
#include "XFolderAddDlg.h"
#include "..\XLanguage\XLanguageMngr.h"

#ifdef _Use_YUN_Client_
	#include "YunFileApi\XYunFileApi.h"
#endif

// CXFolderTreeCtrl

/*
CImageList imglist;
CBitmap     bitmap;
imglist.Create(16, 16, ILC_MASK, 1, 1);
bitmap.LoadBitmap( IDB_COMPUTER );
imglist.Add(&bitmap, (COLORREF)0xFFFFFF);
bitmap.DeleteObject();
treectrl.SetImageList(&m_imgList, TVSIL_NORMAL);
*/

IMPLEMENT_DYNAMIC(CXFolderTreeCtrl, CTreeCtrl)

CXFolderTreeCtrl::CXFolderTreeCtrl()
{
	m_pXFileMngr = NULL;
	m_pFrameWnd = NULL;
	m_bSetExBaseItemData = TRUE;
	m_pXFileListView = NULL;
	m_bDeleteAllFolder = TRUE;
	m_pXFileMsgRcvWnd = NULL;
}

CXFolderTreeCtrl::~CXFolderTreeCtrl()
{
}

CExBaseObject* CXFolderTreeCtrl::GetSelObject()
{
	HTREEITEM hSel = GetSelectedItem();

	if (hSel == NULL)
	{
		return NULL;
	}

	CExBaseObject *pSel = (CExBaseObject*)GetItemData(hSel);
	return pSel;
}

CXFolder* CXFolderTreeCtrl::GetCurrSelFolder()
{
	CExBaseObject *pSel = GetSelObject();

	if (pSel == NULL)
	{
		return NULL;
	}

	CXFolder *pFolder = NULL;

	if (pSel->GetClassID() != CLASSID_XFILE)
	{
		pFolder = (CXFolder*)pSel;
	}

	return pFolder;
}


void CXFolderTreeCtrl::SelectNode(CExBaseObject* pObj)
{
	if (pObj == NULL)
	{
		return;
	}
	
	if (pObj->m_dwItemData != NULL)
	{
		this->SelectItem((HTREEITEM)pObj->m_dwItemData);
	}
}

void CXFolderTreeCtrl::ShowXFileMngr(CXFileMngr* pXFileMngr)
{
	m_pXFileMngr = pXFileMngr;
	DeleteAllItems();

	if(pXFileMngr == NULL)
	{
		return;
	}

	HTREEITEM hTreeItem = Insert(m_pXFileMngr, TVI_ROOT, NULL);

	if (m_bSetExBaseItemData)
	{
		hTreeItem = (HTREEITEM)pXFileMngr->m_dwItemData;
	}

	Expand(hTreeItem,TVE_EXPAND);
	SelectItem(hTreeItem);
	OnTvnSelchanged(hTreeItem);
}

UINT CXFolderTreeCtrl::GetImgIndex(CExBaseObject* pObj)
{
	return xfile_GetImageIndex(pObj);
}

HTREEITEM CXFolderTreeCtrl::Insert(CExBaseObject *pItem,HTREEITEM htiParent,HTREEITEM hAfter)
{
	HTREEITEM hTreeItem = NULL;

	if (pItem == NULL)
	{
		return NULL;
	}

	if (!CanInsert(pItem))
	{
		return NULL;
	}

	UINT nImg = GetImgIndex(pItem);

	hTreeItem = InsertItem(pItem->m_strName, nImg, nImg+1, htiParent,hAfter);

	if (m_bSetExBaseItemData)
	{
		pItem->m_dwItemData = (DWORD)hTreeItem;
	}

	SetItemData(hTreeItem, (DWORD)pItem);

	if (pItem->IsBaseList())
	{
		CExBaseList *pList = (CExBaseList*)pItem;
		POS pos = pList->GetHeadPosition();

		while (pos != NULL)
		{
			CExBaseObject *p = pList->GetNext(pos);
			Insert(p, hTreeItem, NULL);
		}
	}

	return hTreeItem;
}

BOOL CXFolderTreeCtrl::CanInsert(CExBaseObject* pObj)
{
	UINT nClassID = pObj->GetClassID();

	if (nClassID != CLASSID_XFILE)
	{
#ifndef exbase_not_use_m_dwReserved
		return (pObj->m_dwReserved > 0);
#else
		return 1;
#endif
	}
	else
	{
		return 0;
	}
}

HTREEITEM CXFolderTreeCtrl::GetLastFolderItem(HTREEITEM hParent)
{
	if (ItemHasChildren(hParent))
	{
		HTREEITEM hFolderItem = NULL;
		HTREEITEM hChildItem = GetChildItem(hParent);

		while (hChildItem != NULL)
		{
			CExBaseObject *p = (CExBaseObject *)GetItemData(hChildItem);

			if (p->GetClassID() == CLASSID_XFOLDER)
			{
				hFolderItem = hChildItem;
			}

			hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
		}

		return hFolderItem;
	}
	else
	{
		return NULL;
	}
}

BEGIN_MESSAGE_MAP(CXFolderTreeCtrl, CTreeCtrl)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CXFolderTreeCtrl::OnTvnSelchanged)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_ADD, &CXFolderTreeCtrl::OnUpdateFolderAdd)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_ADD, &CXFolderTreeCtrl::OnFolderAdd)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_DELETE, &CXFolderTreeCtrl::OnUpdateFolderDelete)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_DELETE, &CXFolderTreeCtrl::OnFolderDelete)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EDIT, &CXFolderTreeCtrl::OnUpdateFolderEdit)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EDIT, &CXFolderTreeCtrl::OnFolderEdit)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EXPORT, &CXFolderTreeCtrl::OnUpdateFolderExport)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EXPORT,&CXFolderTreeCtrl:: OnFolderExport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_IMPORT, &CXFolderTreeCtrl::OnUpdateFolderImport)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_IMPORT, &CXFolderTreeCtrl::OnFolderImport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_COPY, &CXFolderTreeCtrl::OnUpdateFileCopy)
	ON_COMMAND(XFID_XFILEMNGRFILE_COPY, &CXFolderTreeCtrl::OnFileCopy)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_PASTE, &CXFolderTreeCtrl::OnUpdateFilePaste)
	ON_COMMAND(XFID_XFILEMNGRFILE_PASTE, &CXFolderTreeCtrl::OnFilePaste)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_DELETE, &CXFolderTreeCtrl::OnUpdateFileDelete)
	ON_COMMAND(XFID_XFILEMNGRFILE_DELETE, &CXFolderTreeCtrl::OnFileDelete)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EDIT, &CXFolderTreeCtrl::OnUpdateFileEdit)
	ON_COMMAND(XFID_XFILEMNGRFILE_EDIT, &CXFolderTreeCtrl::OnFileEdit)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EXPORT, &CXFolderTreeCtrl::OnUpdateFileExport)
	ON_COMMAND(XFID_XFILEMNGRFILE_EXPORT, &CXFolderTreeCtrl::OnFileExport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_IMPORT, &CXFolderTreeCtrl::OnUpdateFileImport)
	ON_COMMAND(XFID_XFILEMNGRFILE_IMPORT, &CXFolderTreeCtrl::OnFileImport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_DOWNLOAD, &CXFolderTreeCtrl::OnUpdateFileDownload)
	ON_COMMAND(XFID_XFILEMNGRFILE_DOWNLOAD, &CXFolderTreeCtrl::OnFileDownload)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_UPLOAD, &CXFolderTreeCtrl::OnUpdateFileUpload)
	ON_COMMAND(XFID_XFILEMNGRFILE_UPLOAD, &CXFolderTreeCtrl::OnFileUpload)
END_MESSAGE_MAP()

// CXFolderTreeCtrl 消息处理程序

void CXFolderTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	UINT uFlags;
	HTREEITEM hItem = HitTest(point,&uFlags);
	Select(hItem, TVGN_CARET);
	
	CExBaseObject* pObj = NULL;
	if( (hItem != NULL) && (TVHT_ONITEM & uFlags) )
	{
		pObj = (CExBaseObject*)GetItemData(hItem);
	}

	//CTreeCtrl::OnRButtonDown(nFlags, point);

	if(pObj != NULL)
	{
		OnContextMenuTree(NULL,point,pObj);
	}
}

void CXFolderTreeCtrl::OnContextMenuTree(CWnd* pWnd,CPoint point,CExBaseObject* pObj)
{
#ifdef ATS_TEMPLREPORT_MNGR
	return;
#endif

	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	CExBaseObject* pSel = (CExBaseObject*)GetSelObject();
	
	if(pSel != NULL)
	{
		InitContextMenuTree(menu, pSel);
		SetOwner(m_pFrameWnd);

		if (menu.GetMenuItemCount() > 0)
		{
			//CUIWndThread::Attach_Wnd_WM_COMMAND(this);
			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y, this);
			//资源回收
			//CUIWndThread::Attach_Wnd_WM_COMMAND(NULL);
			HMENU hmenu=menu.Detach();			
			menu.DestroyMenu();	
		}
	}	
}

void CXFolderTreeCtrl::InitContextMenuTree(CMenu &menu,CExBaseObject* pObj)
{
	if (m_pFrameWnd != NULL)
	{
		if (m_pFrameWnd->SendMessage(WM_INIT_XFILEMNGR_MENU, (WPARAM)(&menu), (LPARAM)pObj) > 0)
		{
			return;
		}
	}

	SetFocus();
	
	UINT nClassID = pObj->GetClassID();
	CXFile *pCopySrcFile = m_pXFileMngr->GetCopySrcFile();

	if (CLASSID_XFILE == nClassID)
	{
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_COPY,g_sLangTxt_CopyFile/*_T("拷贝文件")*/);
		
		if (pCopySrcFile != NULL)
		{
			menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
		}
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DELETE,g_sLangTxt_DeleteFile/*_T("删除文件")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EDIT,g_sLangTxt_FileRename/*_T("修改文件名称")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EXPORT,g_sLangTxt_ExportFile/*_T("导出文件")*/);
	}
	else if (nClassID == CLASSID_XFILEMNGR)
	{
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);
		menu.AppendMenu(MF_SEPARATOR);

		if (pCopySrcFile != NULL)
		{
			menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
		}

		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
	}
	else if (nClassID == CLASSID_XFOLDER)
	{
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_DELETE,g_sLangTxt_DeleteDirectory /*_T("删除目录")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EDIT,g_sLangTxt_DirectoryRename/*_T("修改目录名称")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EXPORT,g_sLangTxt_ExportDirectory/*_T("导出目录")*/);
		menu.AppendMenu(MF_SEPARATOR);

		if (pCopySrcFile != NULL)
		{
			menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
		}

		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
	}

#ifdef _Use_YUN_Client_
	if ((nClassID != CLASSID_XFILEMNGR) && Yun_IsLoginSucc())
#else
	if (nClassID != CLASSID_XFILEMNGR)
#endif
	{
		menu.AppendMenu(MF_SEPARATOR);

		if (xfile_IsYunFile(pObj))
		{
			menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DOWNLOAD,g_sLangTxt_DownLoad/*_T("下载")*/);
		}

		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_UPLOAD,g_sLangTxt_UpLoad/*_T("上传")*/);
	}
}


BOOL CXFolderTreeCtrl::Insert(CExBaseObject *pObj)
{
	if (!CanInsert(pObj))
	{
		return FALSE;
	}

	CExBaseObject *pParent = (CExBaseObject*)pObj->GetParent();

	HTREEITEM htiParent = (HTREEITEM)pParent->m_dwItemData;
	HTREEITEM hAfter = NULL;

	if (pObj->GetClassID() == CLASSID_XFOLDER)
	{
		hAfter = GetLastFolderItem(htiParent);
	}

	Insert(pObj, htiParent, hAfter);
	Expand(htiParent, TVE_EXPAND);
	SelectItem((HTREEITEM)pObj->m_dwItemData);

	return TRUE;
}

HTREEITEM CXFolderTreeCtrl::Delete(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return NULL;
	}

	if (pObj->m_dwItemData == NULL)
	{
		return NULL;
	}

	HTREEITEM hReturn = NULL;
	HTREEITEM hItem = (HTREEITEM)pObj->m_dwItemData;
	HTREEITEM hPrev = GetPrevSiblingItem(hItem);
	HTREEITEM hNext = GetNextSiblingItem(hItem);
	HTREEITEM hParent = GetParentItem(hItem);

	DeleteItem(hItem);

	HTREEITEM hNewItem = GetSelectedItem();

	if (hNext != NULL)
	{
		hReturn = hNext;
	}
	else if (hPrev != NULL)
	{
		hReturn = hPrev;
	}
	else if (hParent != NULL)
	{
		hReturn = hParent;
	}

	return hReturn;
}

BOOL CXFolderTreeCtrl::Update(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	if (pObj->m_dwItemData == NULL)
	{
		return FALSE;
	}

	SetItemText((HTREEITEM)pObj->m_dwItemData, pObj->m_strName);

	return TRUE;
}

void CXFolderTreeCtrl::InitXFileMngrCurrSel()
{
	CExBaseObject *p = GetSelObject();
	m_pXFileMngr->SetCurrSel(p);
}

void CXFolderTreeCtrl::OnTvnSelchanged(HTREEITEM hItem)
{
	if (hItem != NULL)
	{
		CXFolder* pFolder = (CXFolder*)GetItemData(hItem);
		ASSERT(pFolder != NULL);
		m_pXFileMngr->SetCurrSel(pFolder);
		xfile_PostXFileObjSelChangeMsg(m_pFrameWnd, WM_THREAD_XFILE_MNGR, pFolder);
	}
	else
	{
		m_pXFileMngr->SetCurrSel(NULL);
		xfile_PostXFileObjSelChangeMsg(m_pFrameWnd, WM_THREAD_XFILE_MNGR, NULL);
	}

	if (m_pXFileListView != NULL)
	{
		m_pXFileListView->RefreshFileViewList();
	}
}

// CXFolderTreeCtrl 消息处理程序
void CXFolderTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

//	ASSERT(m_pXFileListView != NULL);

	HTREEITEM hItem = GetSelectedItem();

	OnTvnSelchanged(hItem);

	*pResult = 0;
}


// 
// void CXFolderTreeCtrl::OnNewFolder()
// {
// 	ASSERT(GetCount() != 0);
// 	HTREEITEM hParentItem = GetSelectedItem();
// 	CXFolder* pParentFolder = (CXFolder*)GetItemData(hParentItem);
// 	ASSERT(pParentFolder != NULL);
// 	CString strNewFolder = _T("新建文件夹");
// 
// 	//查找是否已经存在名为"新建文件夹 %d"的文件夹
// 	int nIndex = 1;
// 	while( pParentFolder->FindByLowerName(strNewFolder) != NULL)
// 	{
// 		strNewFolder.Format(_T("%s %d"),_T("新建文件夹"),nIndex++);
// 	}
// 
// 	CXFolder* pNewFolder = pParentFolder->AddFolder(strNewFolder);
// 
// 	if(pNewFolder != NULL) 
// 	{
// 		HTREEITEM hNew = InsertItem(strNewFolder,0,0,hParentItem);
// 		SetItemData(hNew,(DWORD_PTR)pNewFolder);
// 		pNewFolder->m_dwItemData = (DWORD)hNew;
// 		SelectItem(hNew);
// 		EnsureVisible(hNew);
// 		EditLabel(hNew);
// 		m_pXFileListView->RefreshFileViewList();
// 		//theApp.RefreshAllFileMngrDialogs((CDlgXFileMngr*)this->GetParent());
// 		//theApp.RefreshAllFileMngrViews(NULL);
// 		AfxGetApp()->PostThreadMessage(WM_THREAD_XFILE_MNGR,0,(LPARAM)this->GetParent());
// 	}
// }
// 
// void CXFolderTreeCtrl::OnDeleteFolder()
// {
// 	CString strInfo;
// 	CXFolder* pFolderBase = (CXFolder*)GetItemData(GetSelectedItem());
// 	CXFolder* pParent = (CXFolder*)pFolderBase->GetParent();
// 
// 	if(pParent != NULL)
// 	{
// 		strInfo.Format(_T("确定要删除文件夹 %s 及其子项目吗?"), pFolderBase->m_strName);
// 		if( MessageBox(strInfo,_T("删除确认"),MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
// 		{
// 			if( MessageBox(_T("删除后将无法恢复，请再次确认"),_T("删除确认"),MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
// 			{
// 				if( pFolderBase->DeleteAllInFolder())
// 				{
// 					DeleteItem(GetSelectedItem());
// 					m_pXFileListView->RefreshFileViewList();
// 					//theApp.RefreshAllFileMngrDialogs((CDlgXFileMngr*)this->GetParent());
// 					//theApp.RefreshAllFileMngrViews(NULL);
// 					AfxGetApp()->PostThreadMessage(WM_THREAD_XFILE_MNGR,0,(LPARAM)this->GetParent());
// 				}
// 				else
// 				{
// 					MessageBox(_T("文件夹中包含正在被使用的文件，删除失败"),_T("删除文件夹失败"),MB_OK);
// 				}
// 			}
// 		}
// 	}
// }
// 
// void CXFolderTreeCtrl::OnRenameFolder()
// {
// 	EditLabel(GetSelectedItem());
// }
// 
// void CXFolderTreeCtrl::OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
// 	ASSERT((sizeof(NMHDR*) == sizeof(WPARAM)) && (sizeof(LRESULT*) == sizeof(LPARAM)));
// 	*pResult = 0;
// }
// 
// void CXFolderTreeCtrl::OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
// 
// 	HTREEITEM hItem = pTVDispInfo->item.hItem;
// 	CString str = pTVDispInfo->item.pszText;
// 	str.TrimLeft();
// 	str.TrimRight();
// 
// 	if( !str.IsEmpty())
// 	{
// 		CXFolder* pFolder = (CXFolder*)GetItemData(hItem);
// 		ASSERT(pFolder != NULL);
// 		if( pFolder->RenameFolder(str) )
// 		{
// 			SetItemText(hItem,str);
// 			GetParent()->SendMessage(WM_CHANGE_STATIC_XPATH,0,0);
// 			AfxGetApp()->PostThreadMessage(WM_THREAD_XFILE_MNGR,0,(LPARAM)this->GetParent());
// 		}
// 		else
// 		{
// 			MessageBox(_T("该文件夹中已被打开的文件"),_T("修改文件夹名称失败"),MB_OK);
// 		}
// 	}
// 
// 	*pResult = 0;
// }
// 

void CXFolderTreeCtrl::OnUpdateFolderAdd(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFolder != NULL || pFile != NULL);
}

void CXFolderTreeCtrl::OnFolderAdd()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	CXFolderAddDlg dlg;
	dlg.m_pSrcFolder = pFolder;

	if (dlg.DoModal() == IDOK)
	{
		CXFolder *pNew = pFolder->AddFolder(dlg.m_strDestFolderName);
		HTREEITEM hCurr = GetSelectedItem();
		Insert(pNew, hCurr);
		Expand(hCurr, TVE_EXPAND);
		SelectItem((HTREEITEM)pNew->m_dwItemData);
	}
}

void CXFolderTreeCtrl::OnUpdateFolderDelete(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngr));
}

void CXFolderTreeCtrl::OnFolderDelete()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	if (pFolder == NULL)
	{
		return ;
	}

	if (m_pXFileMsgRcvWnd != NULL)
	{
		LRESULT nRet = m_pXFileMsgRcvWnd->XDeleteXFolder(pFolder);

		if (nRet == XFILEMNGR_OPTR_FAILED)
		{
			return;
		}
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
		strMsg.Format(g_sLangTxt_SureDeleFold/*_T("确实要删除文件夹【%s】吗？")*/, pFolder->m_strName);
	}

	if (MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		return;
	}

	CXFolder *pParnt = (CXFolder*)pFolder->GetParent();

	HTREEITEM hNext = Delete(pFolder);

	if (m_bDeleteAllFolder)
	{
		pFolder->DeleteFolderEx();
	}
	else
	{
		pFolder->DeleteFolder();
	}

	pParnt->Delete(pFolder);
	m_pXFileMngr->SetCurrSel(NULL);
	SelectItem(hNext);
}

void CXFolderTreeCtrl::OnUpdateFolderEdit(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngr));
}

void CXFolderTreeCtrl::OnFolderEdit()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	if (pFolder == NULL)
	{
		return ;
	}

	if (m_pXFileMsgRcvWnd != NULL)
	{
		LRESULT nRet = m_pXFileMsgRcvWnd->XCanEditXFolder(pFolder);

		if (nRet == XFILEMNGR_OPTR_FAILED)
		{
			return;
		}
	}

	CXFolderEditDlg dlg;
	dlg.m_pSrcFolder = pFolder;

	if (dlg.DoModal() == IDOK)
	{
		Update(pFolder);
	}

}

void CXFolderTreeCtrl::OnUpdateFolderExport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngr));
}

void CXFolderTreeCtrl::OnFolderExport()
{
	CXFolder *pSrcFolder = m_pXFileMngr->GetCurrSelFolder();

	if (pSrcFolder == NULL)
	{
		return;
	}

	TCHAR pszBuffer[MAX_PATH];
	bstr_t bstrText;
	bstrText = g_sLangTxt_ChoFoldExDir;

	if (!FGetDirectory(m_hWnd, pszBuffer,bstrText/* _T("选择配置文件夹导出目标目录")*/))
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

void CXFolderTreeCtrl::OnUpdateFolderImport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	//	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFolder != NULL);
}

void CXFolderTreeCtrl::OnFolderImport()
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
	Insert(pNew);
}

void CXFolderTreeCtrl::OnUpdateFileCopy(CCmdUI* pCmdUI)
{
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFolderTreeCtrl::OnFileCopy()
{
	m_pXFileMngr->CopyFile();
}

void CXFolderTreeCtrl::OnUpdateFilePaste(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	CXFile *pFile = m_pXFileMngr->GetCopySrcFile();

	pCmdUI->Enable(pFolder != NULL && pFile != NULL);
}

void CXFolderTreeCtrl::OnFilePaste()
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

	Insert(pNewFile);
	Select((HTREEITEM)pNewFile->m_dwItemData, TVGN_CARET);
}

void CXFolderTreeCtrl::OnUpdateFileDelete(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFolderTreeCtrl::OnFileDelete()
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

	HTREEITEM hNextSel = Delete(pFile);
	m_pXFileMngr->DeleteFile(pFile);
	m_pXFileMngr->SetCurrSel(NULL);
	SelectItem(hNextSel);
}

void CXFolderTreeCtrl::OnUpdateFileEdit(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFolderTreeCtrl::OnFileEdit()
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
		Update(pFile);
	}

}

void CXFolderTreeCtrl::OnUpdateFileExport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFolderTreeCtrl::OnFileExport()
{
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();
	CString strPath = pFile->GetRelativePath(TRUE);
	CString strDestFile = pFile->m_strID;

	CString strXFileFilter, strXFilePostFix;
	m_pXFileMngr->GetXFileDlgString(strXFileFilter, strXFilePostFix);

	if (PopupSaveAsFileDialog(this, strDestFile, strXFileFilter, strXFilePostFix))
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

void CXFolderTreeCtrl::OnUpdateFileImport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL || pFolder != NULL);
}


void CXFolderTreeCtrl::OnFileImport()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();

	if (pFolder == NULL)
	{
		return;
	}

	CString strSrcFile;
	CXFile *pFile = NULL;

	CString strXFileFilter, strXFilePostFix;
	m_pXFileMngr->GetXFileDlgString(strXFileFilter, strXFilePostFix);

	if (!PopupOpenFileDialog(this, strSrcFile, strXFileFilter, strXFilePostFix))
	{
		return;
	}


	if (pFolder->IsFileExist(strSrcFile))
	{
		CString strName = GetLastFolderNameFromPathName(strSrcFile);
		CString strMsg;
		strMsg.Format(g_sLangTxt_ExiSaNameFileCov/*_T("存在同名称的文件【%s】,覆盖吗？")*/, strName);

		if (MessageBox(strMsg, g_sLangTxt_FileCover/* _T("覆盖文件")*/, MB_OKCANCEL) == IDOK)
		{
			pFile = pFolder->OverWriteFile(strSrcFile);
		}
	}
	else
	{
		pFile = pFolder->AddFile(strSrcFile);
		if (pFile != NULL)
		{
			Insert(pFile);
		}
	}	
}


void CXFolderTreeCtrl::OnUpdateFileDownload(CCmdUI* pCmdUI)
{

}

void CXFolderTreeCtrl::OnFileDownload()
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

void CXFolderTreeCtrl::OnUpdateFileUpload(CCmdUI* pCmdUI)
{

}

void CXFolderTreeCtrl::OnFileUpload()
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


// 
// void CXFolderTreeCtrl::OnSaveAsFile(CXFolder *pCurrFolder, const CString &strFile)
// {
// 	CString strTemp = strFile;
// 	strTemp.MakeLower();
// 	CXFile *pFile = pCurrFolder->SelectFileInCurrFolder(strTemp);
// 
// 	if (pFile == NULL)
// 	{
// 		pFile = pCurrFolder->AddFile2(strFile);
// 		if (pFile != NULL)
// 		{
// 			Insert(pFile);
// 		}
// 	}
// }
// 

BOOL CXFolderTreeCtrl::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CTreeCtrl::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
