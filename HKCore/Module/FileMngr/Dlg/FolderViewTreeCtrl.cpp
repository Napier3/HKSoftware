// D:\WorkPM\Source\PMTest\GuideBookDev\UI\FolderViewTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "FolderViewTreeCtrl.h"
#include "FileViewListCtrl.h"
#include "DlgFileMngr.h"
#include "..\..\XLanguage\XLanguageResource.h"
// CFolderViewTreeCtrl

IMPLEMENT_DYNAMIC(CFolderViewTreeCtrl, CTreeCtrl)

CFolderViewTreeCtrl::CFolderViewTreeCtrl()
{
	m_pFileMngrBase = NULL;
}

CFolderViewTreeCtrl::~CFolderViewTreeCtrl()
{
}

void CFolderViewTreeCtrl::InitShowFolderViewTree()
{
	ASSERT(m_pFileMngrBase != NULL);
	DeleteAllItems();
	InsertItemToTreeCtrl(m_pFileMngrBase,NULL);
}

void CFolderViewTreeCtrl::InsertItemToTreeCtrl(CExBaseObject* pObj,HTREEITEM htiParent)
{
	ASSERT(m_pFileMngrBase != NULL);
	ASSERT(pObj != NULL);

	DWORD dwItemData = 0;
	HTREEITEM hTreeItem = NULL;

	if(IsFolder(pObj->GetClassID()))
	{
		hTreeItem = InsertItem(pObj->m_strName,0,0,htiParent);
		pObj->m_dwItemData = (DWORD)hTreeItem;
		SetItemData(hTreeItem,(DWORD)pObj);
		InsertItemChildrenToTreeCtrl(pObj,hTreeItem);
	}
}

void CFolderViewTreeCtrl::InsertItemChildrenToTreeCtrl(CExBaseObject* pObj,HTREEITEM htiParent)
{
	ASSERT(pObj != NULL);
	CExBaseObject* pObjChild = NULL;

	if( IsFolder(pObj->GetClassID()) )
	{
		CExBaseList* pList = (CExBaseList*)pObj;
		POS pos = pList->GetHeadPosition();

		while(pos != NULL)
		{
			pObjChild = (CExBaseObject*)pList->GetNext(pos);
			InsertItemToTreeCtrl(pObjChild,htiParent);
		}
	}
}

void CFolderViewTreeCtrl::SetRelatedListCtrl(CFileViewListCtrl* pFileList)
{
	ASSERT( pFileList != NULL);
	m_pFileList = pFileList;
}

BEGIN_MESSAGE_MAP(CFolderViewTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CFolderViewTreeCtrl::OnTvnSelchanged)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_GBDEV_NEW_FOLDER,&CFolderViewTreeCtrl::OnNewFolder)
	ON_COMMAND(ID_GBDEV_DELETE_FOLDER,&CFolderViewTreeCtrl::OnDeleteFolder)
	ON_COMMAND(ID_GBDEV_RENAME_FOLDER,&CFolderViewTreeCtrl::OnRenameFolder)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, &CFolderViewTreeCtrl::OnTvnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, &CFolderViewTreeCtrl::OnTvnEndlabeledit)
END_MESSAGE_MAP()


// CFolderViewTreeCtrl 消息处理程序
void CFolderViewTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	ASSERT(m_pFileList != NULL);

	if(GetSafeHwnd())
	{
		CFolderBase* pFolder = (CFolderBase*)GetItemData(GetSelectedItem());
		ASSERT(pFolder != NULL);
		if(pFolder != NULL && pFolder->CheckFileExist() )
		{
			//如果有改变 保存XML文件
			m_pFileMngrBase->SaveXMLFile();
			//theApp.RefreshAllFileMngrDialogs((CDlgFileMngr*)this->GetParent());
			//theApp.RefreshAllFileMngrViews(NULL);
			AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this->GetParent());
		}
	}
	GetParent()->SendMessage(WM_CHANGE_STATIC_PATH,0,0);
	m_pFileList->RefreshFileViewList();

	*pResult = 0;
}

void CFolderViewTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point, &uFlags);
	HTREEITEM hItemSelected = GetSelectedItem();

	if (hItem == NULL)
	{
		return;
	}
	else
	{
		SelectItem(hItem);
	}

	CTreeCtrl::OnRButtonDown(nFlags, point);

	ClientToScreen(&point);
	OnContextMenuEx(this, point);
}

void CFolderViewTreeCtrl::OnContextMenuEx(CWnd* pWnd, CPoint point)
{
	CMenu menu;		
	menu.CreatePopupMenu();
	// 添加菜单项
	menu.AppendMenu(MF_STRING,ID_GBDEV_NEW_FOLDER,CXLanguageResourceBase::g_sLangID_NewFolder/*_T("新建文件夹")*/);
	if((CFolderBase*)GetItemData(GetSelectedItem()) != m_pFileMngrBase)
	{
		menu.AppendMenu(MF_STRING,ID_GBDEV_RENAME_FOLDER,CXLanguageResourceBase::g_sLangTxt_ReName/*_T("重命名")*/);
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,ID_GBDEV_DELETE_FOLDER,CXLanguageResourceBase::g_sLangTxt_DeleteFloder/*_T("删除文件夹")*/);
	}

	//确定弹出式菜单的位置
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			
	//资源回收
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	
}

void CFolderViewTreeCtrl::OnNewFolder()
{
	ASSERT(GetCount() != 0);
	HTREEITEM hParentItem = GetSelectedItem();
	CFolderBase* pParentFolder = (CFolderBase*)GetItemData(hParentItem);
	ASSERT(pParentFolder != NULL);
	CString strNewFolder = CXLanguageResourceBase::g_sLangID_NewFolder/*_T("新建文件夹")*/;
	
	//查找是否已经存在名为"新建文件夹 %d"的文件夹
	int nIndex = 1;
	while( pParentFolder->FindByLowerName(strNewFolder) != NULL)
	{
		strNewFolder.Format(_T("%s %d"),CXLanguageResourceBase::g_sLangID_NewFolder/*_T("新建文件夹")*/,nIndex++);
	}

	CFolderBase* pNewFolder = pParentFolder->AddFolder(strNewFolder);
	if(pNewFolder != NULL) 
	{
		HTREEITEM hNew = InsertItem(strNewFolder,0,0,hParentItem);
		SetItemData(hNew,(DWORD_PTR)pNewFolder);
		pNewFolder->m_dwItemData = (DWORD)hNew;
		SelectItem(hNew);
		EnsureVisible(hNew);
		EditLabel(hNew);
		m_pFileList->RefreshFileViewList();
		m_pFileMngrBase->SaveXMLFile();
		//theApp.RefreshAllFileMngrDialogs((CDlgFileMngr*)this->GetParent());
		//theApp.RefreshAllFileMngrViews(NULL);
		AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this->GetParent());
	}
}

void CFolderViewTreeCtrl::OnDeleteFolder()
{
	CString strInfo;
	CFolderBase* pFolderBase = (CFolderBase*)GetItemData(GetSelectedItem());
	CFolderBase* pParent = (CFolderBase*)pFolderBase->GetParent();
	
	if(pParent != NULL)
	{
		strInfo.Format(CXLanguageResourceBase::g_sLangTxt_SureDelFoldItem/*_T("确定要删除文件夹 %s 及其子项目吗?")*/, pFolderBase->m_strName);
		if( MessageBox(strInfo,CXLanguageResourceBase::g_sLangTxt_SureDelete/*_T("删除确认")*/,MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
		{
			if( MessageBox(CXLanguageResourceBase::g_sLangTxt_SureAgain/*_T("删除后将无法恢复，请再次确认")*/,CXLanguageResourceBase::g_sLangTxt_SureDelete/*_T("删除确认")*/,MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
			{
				if( pFolderBase->DeleteAllInFolder())
				{
					DeleteItem(GetSelectedItem());
					m_pFileMngrBase->SaveXMLFile();
					m_pFileList->RefreshFileViewList();
					//theApp.RefreshAllFileMngrDialogs((CDlgFileMngr*)this->GetParent());
					//theApp.RefreshAllFileMngrViews(NULL);
					AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this->GetParent());
				}
				else
				{
					MessageBox(CXLanguageResourceBase::g_sLangTxt_DeleteFailFold/*_T("文件夹中包含正在被使用的文件，删除失败")*/,CXLanguageResourceBase::g_sLangTxt_FolderDeleteFail/*_T("删除文件夹失败")*/,MB_OK);
				}
			}
		}
	}
}

void CFolderViewTreeCtrl::OnRenameFolder()
{
	EditLabel(GetSelectedItem());
}

void CFolderViewTreeCtrl::OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	ASSERT((sizeof(NMHDR*) == sizeof(WPARAM)) && (sizeof(LRESULT*) == sizeof(LPARAM)));
	*pResult = 0;
}

void CFolderViewTreeCtrl::OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	
	HTREEITEM hItem = pTVDispInfo->item.hItem;
	CString str = pTVDispInfo->item.pszText;
	str.TrimLeft();
	str.TrimRight();
	
	if( !str.IsEmpty())
	{
		CFolderBase* pFolder = (CFolderBase*)GetItemData(hItem);
		ASSERT(pFolder != NULL);
		if( pFolder->RenameFolder(str) )
		{
			SetItemText(hItem,str);
			GetParent()->SendMessage(WM_CHANGE_STATIC_PATH,0,0);
			m_pFileMngrBase->SaveXMLFile();
			//theApp.RefreshAllFileMngrDialogs((CDlgFileMngr*)this->GetParent());
			//theApp.RefreshAllFileMngrViews(NULL);
			AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this->GetParent());
		}
		else
		{
			MessageBox(CXLanguageResourceBase::g_sLangTxt_FoldAlrOpen/*_T("该文件夹中已被打开的文件")*/,CXLanguageResourceBase::g_sLangTxt_ModifiedFail/*_T("修改文件夹名称失败")*/,MB_OK);
		}
	}
	
	*pResult = 0;
}