// D:\WorkPM\Source\PMTest\GuideBookDev\UI\XFolderViewTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XFolderViewTreeCtrl.h"
#include "XFileViewListCtrl.h"

// CXFolderViewTreeCtrl

IMPLEMENT_DYNAMIC(CXFolderViewTreeCtrl, CTreeCtrl)

CXFolderViewTreeCtrl::CXFolderViewTreeCtrl()
{
	m_pFileMngrBase = NULL;
}

CXFolderViewTreeCtrl::~CXFolderViewTreeCtrl()
{
}

void CXFolderViewTreeCtrl::InitShowFolderViewTree()
{
	ASSERT(m_pFileMngrBase != NULL);
	DeleteAllItems();
	InsertItemToTreeCtrl(m_pFileMngrBase,NULL);
}

void CXFolderViewTreeCtrl::InsertItemToTreeCtrl(CExBaseObject* pObj,HTREEITEM htiParent)
{
	ASSERT(m_pFileMngrBase != NULL);
	ASSERT(pObj != NULL);

	DWORD dwItemData = 0;
	HTREEITEM hTreeItem = NULL;

	if(xfile_IsFolder(pObj->GetClassID()))
	{
		hTreeItem = InsertItem(pObj->m_strName,0,0,htiParent);
		pObj->m_dwItemData = (DWORD)hTreeItem;
		SetItemData(hTreeItem,(DWORD)pObj);
		InsertItemChildrenToTreeCtrl(pObj,hTreeItem);
	}
}

void CXFolderViewTreeCtrl::InsertItemChildrenToTreeCtrl(CExBaseObject* pObj,HTREEITEM htiParent)
{
	ASSERT(pObj != NULL);
	CExBaseObject* pObjChild = NULL;

	if( xfile_IsFolder(pObj->GetClassID()) )
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

void CXFolderViewTreeCtrl::SetRelatedListCtrl(CXFileViewListCtrl* pFileList)
{
	ASSERT( pFileList != NULL);
	m_pFileList = pFileList;
}

BEGIN_MESSAGE_MAP(CXFolderViewTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CXFolderViewTreeCtrl::OnTvnSelchanged)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_GBDEV_NEW_FOLDER,&CXFolderViewTreeCtrl::OnNewFolder)
	ON_COMMAND(ID_GBDEV_DELETE_FOLDER,&CXFolderViewTreeCtrl::OnDeleteFolder)
	ON_COMMAND(ID_GBDEV_RENAME_FOLDER,&CXFolderViewTreeCtrl::OnRenameFolder)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, &CXFolderViewTreeCtrl::OnTvnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, &CXFolderViewTreeCtrl::OnTvnEndlabeledit)
END_MESSAGE_MAP()


// CXFolderViewTreeCtrl 消息处理程序
void CXFolderViewTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	ASSERT(m_pFileList != NULL);

	if(GetSafeHwnd())
	{
		CXFolder* pFolder = (CXFolder*)GetItemData(GetSelectedItem());
		ASSERT(pFolder != NULL);
		if(pFolder != NULL && pFolder->CheckFileExist() )
		{
			//如果有改变 保存XML文件
			//m_pFileMngrBase->SaveXMLFile();
			//theApp.RefreshAllFileMngrDialogs((CXDlgFileMngr*)this->GetParent());
			//theApp.RefreshAllFileMngrViews(NULL);
			AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_XFILEMNGR,0,(LPARAM)this->GetParent());
		}
	}
	GetParent()->SendMessage(WM_CHANGE_STATIC_PATH,0,0);
	m_pFileList->RefreshFileViewList();

	*pResult = 0;
}

void CXFolderViewTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
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

void CXFolderViewTreeCtrl::OnContextMenuEx(CWnd* pWnd, CPoint point)
{
	CMenu menu;		
	menu.CreatePopupMenu();
	// 添加菜单项
	menu.AppendMenu(MF_STRING,ID_GBDEV_NEW_FOLDER,_T("新建文件夹"));
	if((CXFolder*)GetItemData(GetSelectedItem()) != m_pFileMngrBase)
	{
		menu.AppendMenu(MF_STRING,ID_GBDEV_RENAME_FOLDER,_T("重命名"));
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,ID_GBDEV_DELETE_FOLDER,_T("删除文件夹"));
	}

	//确定弹出式菜单的位置
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			
	//资源回收
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	
}

void CXFolderViewTreeCtrl::OnNewFolder()
{
	ASSERT(GetCount() != 0);
	HTREEITEM hParentItem = GetSelectedItem();
	CXFolder* pParentFolder = (CXFolder*)GetItemData(hParentItem);
	ASSERT(pParentFolder != NULL);
	CString strNewFolder = _T("新建文件夹");
	
	//查找是否已经存在名为"新建文件夹 %d"的文件夹
	int nIndex = 1;
	while( pParentFolder->FindByLowerName(strNewFolder) != NULL)
	{
		strNewFolder.Format(_T("%s %d"),_T("新建文件夹"),nIndex++);
	}

	CXFolder* pNewFolder = pParentFolder->AddFolder(strNewFolder);
	if(pNewFolder != NULL) 
	{
		HTREEITEM hNew = InsertItem(strNewFolder,0,0,hParentItem);
		SetItemData(hNew,(DWORD_PTR)pNewFolder);
		pNewFolder->m_dwItemData = (DWORD)hNew;
		SelectItem(hNew);
		EnsureVisible(hNew);
		EditLabel(hNew);
		m_pFileList->RefreshFileViewList();
		//m_pFileMngrBase->SaveXMLFile();
		//theApp.RefreshAllFileMngrDialogs((CXDlgFileMngr*)this->GetParent());
		//theApp.RefreshAllFileMngrViews(NULL);
		AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_XFILEMNGR,0,(LPARAM)this->GetParent());
	}
}

void CXFolderViewTreeCtrl::OnDeleteFolder()
{
	CString strInfo;
	CXFolder* pFolderBase = (CXFolder*)GetItemData(GetSelectedItem());
	CXFolder* pParent = (CXFolder*)pFolderBase->GetParent();
	
	if(pParent != NULL)
	{
		strInfo.Format(_T("确定要删除文件夹 %s 及其子项目吗?"), pFolderBase->m_strName);
		if( MessageBox(strInfo,_T("删除确认"),MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
		{
			if( MessageBox(_T("删除后将无法恢复，请再次确认"),_T("删除确认"),MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
			{
				if( pFolderBase->DeleteAllInFolder())
				{
					DeleteItem(GetSelectedItem());
					//m_pFileMngrBase->SaveXMLFile();
					//m_pFileList->RefreshFileViewList();
					//theApp.RefreshAllFileMngrDialogs((CXDlgFileMngr*)this->GetParent());
					//theApp.RefreshAllFileMngrViews(NULL);
					AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_XFILEMNGR,0,(LPARAM)this->GetParent());
				}
				else
				{
					MessageBox(_T("文件夹中包含正在被使用的文件，删除失败"),_T("删除文件夹失败"),MB_OK);
				}
			}
		}
	}
}

void CXFolderViewTreeCtrl::OnRenameFolder()
{
	EditLabel(GetSelectedItem());
}

void CXFolderViewTreeCtrl::OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	ASSERT((sizeof(NMHDR*) == sizeof(WPARAM)) && (sizeof(LRESULT*) == sizeof(LPARAM)));
	*pResult = 0;
}

void CXFolderViewTreeCtrl::OnTvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	
	HTREEITEM hItem = pTVDispInfo->item.hItem;
	CString str = pTVDispInfo->item.pszText;
	str.TrimLeft();
	str.TrimRight();
	
	if( !str.IsEmpty())
	{
		CXFolder* pFolder = (CXFolder*)GetItemData(hItem);
		ASSERT(pFolder != NULL);
		if( pFolder->RenameFolder(str) )
		{
			SetItemText(hItem,str);
			GetParent()->SendMessage(WM_CHANGE_STATIC_PATH,0,0);
			//m_pFileMngrBase->SaveXMLFile();
			//theApp.RefreshAllFileMngrDialogs((CXDlgFileMngr*)this->GetParent());
			//theApp.RefreshAllFileMngrViews(NULL);
			AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_XFILEMNGR,0,(LPARAM)this->GetParent());
		}
		else
		{
			MessageBox(_T("该文件夹中已被打开的文件"),_T("修改文件夹名称失败"),MB_OK);
		}
	}
	
	*pResult = 0;
}

