// D:\WorkPM\Source\PMTest\GuideBookDev\UI\XFileViewListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "XFileViewListCtrl.h"

// CXFileViewListCtrl

IMPLEMENT_DYNAMIC(CXFileViewListCtrl, CMFCListCtrl)

CXFileViewListCtrl::CXFileViewListCtrl()
{
	m_bFirstShow = TRUE;
	m_pFolderBase = NULL;
	m_pFolderTree = NULL;
	m_pFileMngrBase = NULL;
}

CXFileViewListCtrl::~CXFileViewListCtrl()
{
}


BEGIN_MESSAGE_MAP(CXFileViewListCtrl, CMFCListCtrl)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_GBDEV_DELETE_FILES,&CXFileViewListCtrl::OnDelete)
	ON_COMMAND(ID_GBDEV_RENAME_FILES,&CXFileViewListCtrl::OnRename)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, &CXFileViewListCtrl::OnLvnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CXFileViewListCtrl::OnLvnEndlabeledit)
END_MESSAGE_MAP()


// CXFileViewListCtrl 消息处理程序

int CXFileViewListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	return 0;
}

int CXFileViewListCtrl::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
{
	CString strItem1,strItem2;
	LVFINDINFO lvfi;
	lvfi.flags = LVFI_PARAM;
	lvfi.lParam = lParam1;
	strItem1 = this->GetItemText(this->FindItem(&lvfi,-1),iColumn);
	lvfi.lParam = lParam2;
	strItem2 = this->GetItemText(this->FindItem(&lvfi,-1),iColumn);

	// 排序 纯粹字符串比较
	return _tcsicmp(strItem1, strItem2);
}

void CXFileViewListCtrl::SetRelatedFolderTreeCtrl(CXFolderViewTreeCtrl* pFolderTree)
{
	m_pFolderTree = pFolderTree;
}

void CXFileViewListCtrl::RefreshFileViewList()
{
	ASSERT(m_pFolderTree != NULL);

	CXFolder* pSelFolder = (CXFolder*)m_pFolderTree->GetItemData(m_pFolderTree->GetSelectedItem());

	if(m_bFirstShow)
	{
		InsertColumn(0,_T("名称"),LVCFMT_LEFT,200);
		InsertColumn(1,_T("大小"),LVCFMT_LEFT,60);
		InsertColumn(2,_T("类型"),LVCFMT_LEFT,100);
		InsertColumn(3,_T("修改时间"),LVCFMT_LEFT,120);
	}
	m_bFirstShow = FALSE;
	DeleteAllItems();

	ASSERT(pSelFolder != NULL);
	POS pos = pSelFolder->GetHeadPosition();
	long nCount = pSelFolder->GetCount();
	CExBaseObject* pObj = NULL;

	while(pos!= NULL)
	{
		pObj = pSelFolder->GetNext(pos);
		InsertItemToListCtrl(pObj);
	}
}

void CXFileViewListCtrl::InsertItemToListCtrl(CExBaseObject* pObj)
{
	UINT nClassID = pObj->GetClassID();
	int nIndex;
	int nCount = GetItemCount();
	CString strSize,strModifyTime,strType;

	if(xfile_IsFolder(nClassID))
	{
		CXFolder* pFolder = (CXFolder*)pObj;
		nIndex = InsertItem(nCount,pFolder->m_strName,0);
		SetItemText(nCount,1,_T(""));														//大小
		SetItemText(nCount,2,_T("文件夹"));									//类型
		pFolder->GetFolderModifyTime(strModifyTime);
		SetItemText(nCount,3,strModifyTime);								//修改时间
		SetItemData(nIndex,(DWORD_PTR)pObj);
	}
	else if(xfile_IsFile(nClassID))
	{
		CXFile* pFile = (CXFile*)pObj;
		CString strPostfix;
		VERIFY(pFile->GetFilePostfix(strPostfix));
		strPostfix = strPostfix.Right(strPostfix.GetLength() - 1);

		if(strPostfix == m_strFilter)
		{
			VERIFY(pFile->GetFileSize(strSize));
			VERIFY(pFile->GetModifyTime(strModifyTime));
			//strType = pFile->GetFileType();
			nIndex = InsertItem(nCount,pObj->m_strName,2);
			SetItemText(nCount,1,strSize);														//大小
			SetItemText(nCount,2,strType);															//类型
			SetItemText(nCount,3,strModifyTime);										//修改时间
			SetItemData(nIndex,(DWORD_PTR)pObj);
		}
	}
}

void CXFileViewListCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	long nCount = GetSelectedCount();
	int nItem = -1;
	UINT uFlags = 0;
	nItem = HitTest(point, &uFlags);
	nCount = GetSelectedCount();

	CMFCListCtrl::OnRButtonDown(nFlags, point);

	if(nCount > 0)
	{
		ClientToScreen(&point);
		OnContextMenuEx(this, point);
	}
}

void CXFileViewListCtrl::OnContextMenuEx(CWnd* pWnd, CPoint point)
{
	CMenu menu;		
	menu.CreatePopupMenu();
	// 添加菜单项
	
	if(GetSelectedCount() > 0)
	{
		if( GetSelectedCount() == 1)
			{
				menu.AppendMenu(MF_STRING,ID_GBDEV_RENAME_FILES,_T("重命名"));
				menu.AppendMenu(MF_SEPARATOR);
		}
		menu.AppendMenu(MF_STRING,ID_GBDEV_DELETE_FILES,_T("删除"));
	}
	
	//确定弹出式菜单的位置
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			
	//资源回收
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	
}

void CXFileViewListCtrl::OnDelete()
{
	CString strInfo;
	strInfo.Format(_T("确定要删除这 %d 个项目吗?"), GetSelectedCount());
	if( MessageBox(strInfo,_T("删除确认"),MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		if( MessageBox(_T("删除后将无法恢复，请再次确认"),_T("删除确认"),MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
		{
			long nCount = GetSelectedCount();
			int nItem = -1;
			for (int i=0;i < nCount;i++)
			{
				nItem = this->GetNextItem(nItem, LVNI_SELECTED);
				ASSERT(nItem != -1);
				CExBaseObject* pObj = (CExBaseObject*)this->GetItemData(nItem);
				if(xfile_IsFile(pObj->GetClassID()))
				{
					CXFile* pFile = (CXFile*)pObj;
					if( !pFile->DeleteFile())
					{
						MessageBox(_T("文件正在被使用，删除失败"),_T("删除文件失败"),MB_OK);
						return ;
					}
				}
				else if(xfile_IsFolder(pObj->GetClassID()))
				{
					CXFolder* pFolder = (CXFolder*)pObj;
					CXFolder* pParentFolder = (CXFolder*)pFolder->GetParent();
					ASSERT(pParentFolder != NULL);
					if( !pFolder->DeleteAllInFolder())
					{
						MessageBox(_T("文件夹中包含正在被使用的文件，删除失败"),_T("删除文件夹失败"),MB_OK);
						return;
					}
					m_pFolderTree->DeleteItem(FindTreeItem(nItem));
				}
			}
			
			ASSERT(m_pFileMngrBase != NULL);
			//m_pFileMngrBase->SaveXMLFile();
			this->RefreshFileViewList();
			//theApp.RefreshAllFileMngrDialogs((CXDlgFileMngr*)this->GetParent());
			//theApp.RefreshAllFileMngrViews(NULL);

			AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_XFILEMNGR,0,(LPARAM)this->GetParent());
		}
	}
}

void CXFileViewListCtrl::OnRename()
{
	int nItem = -1;
	nItem = GetNextItem(nItem,LVNI_SELECTED);
	EditLabel(nItem);
}

//根据在listctrl中选择的文件夹查找treectrl中对应的HTREEITEM
HTREEITEM CXFileViewListCtrl::FindTreeItem(int nItem)
{
	ASSERT(nItem != -1);
	CXFolder* pFolder = (CXFolder*)GetItemData(nItem);
	HTREEITEM hParentItem = m_pFolderTree->GetSelectedItem();
	
	HTREEITEM hFind = NULL;
	HTREEITEM hTemp = m_pFolderTree->GetNextItem(hParentItem,TVGN_CHILD);

	while(m_pFolderTree->GetItemData(hTemp) != (DWORD_PTR)pFolder)
	{
		hTemp = m_pFolderTree->GetNextItem(hTemp,TVGN_NEXT);
	}
	
	hFind = hTemp;
	ASSERT(hFind != NULL);

	return hFind;
}

void CXFileViewListCtrl::OnLvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

	*pResult = 0;
}

void CXFileViewListCtrl::OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	ASSERT(m_pFileMngrBase != NULL);
	int nItem =pDispInfo->item.iItem;
	ASSERT(nItem != -1);

	CString str = pDispInfo->item.pszText;
	str.TrimLeft();
	str.TrimRight();

	if( !str.IsEmpty() )
	{
		CExBaseObject* pObj = (CExBaseObject*)GetItemData(nItem);
		ASSERT(pObj != NULL);
		
		if( xfile_IsFolder(pObj->GetClassID()) )
		{
			CXFolder* pFolder = (CXFolder*)pObj;
			if( pFolder->RenameFolder(str) )
			{
				m_pFolderTree->SetItemText(FindTreeItem(nItem),str);
				SetItemText(nItem,0,str);
				
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
		else if( xfile_IsFile(pObj->GetClassID()) )
		{
			CXFile* pFile = (CXFile*)pObj;
			if( pFile->RenameFile(str) )
			{
				SetItemText(nItem,0,str+m_strFilter);
				//m_pFileMngrBase->SaveXMLFile();
				//theApp.RefreshAllFileMngrDialogs((CXDlgFileMngr*)this->GetParent());
				//theApp.RefreshAllFileMngrViews(NULL);
				AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_XFILEMNGR,0,(LPARAM)this->GetParent());
			}
			else
			{
				MessageBox(_T("该文件已被打开"),_T("修改文件名称失败"),MB_OK);
			}
		}
	}

	*pResult = 0;
}
