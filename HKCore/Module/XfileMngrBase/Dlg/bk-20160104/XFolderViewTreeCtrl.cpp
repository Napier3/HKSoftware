// D:\WorkPM\Source\PMTest\GuideBookDev\UI\XFolderViewTreeCtrl.cpp : ʵ���ļ�
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


// CXFolderViewTreeCtrl ��Ϣ�������
void CXFolderViewTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	ASSERT(m_pFileList != NULL);

	if(GetSafeHwnd())
	{
		CXFolder* pFolder = (CXFolder*)GetItemData(GetSelectedItem());
		ASSERT(pFolder != NULL);
		if(pFolder != NULL && pFolder->CheckFileExist() )
		{
			//����иı� ����XML�ļ�
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
	// ��Ӳ˵���
	menu.AppendMenu(MF_STRING,ID_GBDEV_NEW_FOLDER,_T("�½��ļ���"));
	if((CXFolder*)GetItemData(GetSelectedItem()) != m_pFileMngrBase)
	{
		menu.AppendMenu(MF_STRING,ID_GBDEV_RENAME_FOLDER,_T("������"));
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,ID_GBDEV_DELETE_FOLDER,_T("ɾ���ļ���"));
	}

	//ȷ������ʽ�˵���λ��
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			
	//��Դ����
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	
}

void CXFolderViewTreeCtrl::OnNewFolder()
{
	ASSERT(GetCount() != 0);
	HTREEITEM hParentItem = GetSelectedItem();
	CXFolder* pParentFolder = (CXFolder*)GetItemData(hParentItem);
	ASSERT(pParentFolder != NULL);
	CString strNewFolder = _T("�½��ļ���");
	
	//�����Ƿ��Ѿ�������Ϊ"�½��ļ��� %d"���ļ���
	int nIndex = 1;
	while( pParentFolder->FindByLowerName(strNewFolder) != NULL)
	{
		strNewFolder.Format(_T("%s %d"),_T("�½��ļ���"),nIndex++);
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
		strInfo.Format(_T("ȷ��Ҫɾ���ļ��� %s ��������Ŀ��?"), pFolderBase->m_strName);
		if( MessageBox(strInfo,_T("ɾ��ȷ��"),MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
		{
			if( MessageBox(_T("ɾ�����޷��ָ������ٴ�ȷ��"),_T("ɾ��ȷ��"),MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
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
					MessageBox(_T("�ļ����а������ڱ�ʹ�õ��ļ���ɾ��ʧ��"),_T("ɾ���ļ���ʧ��"),MB_OK);
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
			MessageBox(_T("���ļ������ѱ��򿪵��ļ�"),_T("�޸��ļ�������ʧ��"),MB_OK);
		}
	}
	
	*pResult = 0;
}

