// D:\WorkPM\Source\PMTest\GuideBookDev\UI\FolderViewTreeCtrl.cpp : ʵ���ļ�
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


// CFolderViewTreeCtrl ��Ϣ�������
void CFolderViewTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	ASSERT(m_pFileList != NULL);

	if(GetSafeHwnd())
	{
		CFolderBase* pFolder = (CFolderBase*)GetItemData(GetSelectedItem());
		ASSERT(pFolder != NULL);
		if(pFolder != NULL && pFolder->CheckFileExist() )
		{
			//����иı� ����XML�ļ�
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
	// ��Ӳ˵���
	menu.AppendMenu(MF_STRING,ID_GBDEV_NEW_FOLDER,CXLanguageResourceBase::g_sLangID_NewFolder/*_T("�½��ļ���")*/);
	if((CFolderBase*)GetItemData(GetSelectedItem()) != m_pFileMngrBase)
	{
		menu.AppendMenu(MF_STRING,ID_GBDEV_RENAME_FOLDER,CXLanguageResourceBase::g_sLangTxt_ReName/*_T("������")*/);
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,ID_GBDEV_DELETE_FOLDER,CXLanguageResourceBase::g_sLangTxt_DeleteFloder/*_T("ɾ���ļ���")*/);
	}

	//ȷ������ʽ�˵���λ��
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			
	//��Դ����
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	
}

void CFolderViewTreeCtrl::OnNewFolder()
{
	ASSERT(GetCount() != 0);
	HTREEITEM hParentItem = GetSelectedItem();
	CFolderBase* pParentFolder = (CFolderBase*)GetItemData(hParentItem);
	ASSERT(pParentFolder != NULL);
	CString strNewFolder = CXLanguageResourceBase::g_sLangID_NewFolder/*_T("�½��ļ���")*/;
	
	//�����Ƿ��Ѿ�������Ϊ"�½��ļ��� %d"���ļ���
	int nIndex = 1;
	while( pParentFolder->FindByLowerName(strNewFolder) != NULL)
	{
		strNewFolder.Format(_T("%s %d"),CXLanguageResourceBase::g_sLangID_NewFolder/*_T("�½��ļ���")*/,nIndex++);
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
		strInfo.Format(CXLanguageResourceBase::g_sLangTxt_SureDelFoldItem/*_T("ȷ��Ҫɾ���ļ��� %s ��������Ŀ��?")*/, pFolderBase->m_strName);
		if( MessageBox(strInfo,CXLanguageResourceBase::g_sLangTxt_SureDelete/*_T("ɾ��ȷ��")*/,MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
		{
			if( MessageBox(CXLanguageResourceBase::g_sLangTxt_SureAgain/*_T("ɾ�����޷��ָ������ٴ�ȷ��")*/,CXLanguageResourceBase::g_sLangTxt_SureDelete/*_T("ɾ��ȷ��")*/,MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
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
					MessageBox(CXLanguageResourceBase::g_sLangTxt_DeleteFailFold/*_T("�ļ����а������ڱ�ʹ�õ��ļ���ɾ��ʧ��")*/,CXLanguageResourceBase::g_sLangTxt_FolderDeleteFail/*_T("ɾ���ļ���ʧ��")*/,MB_OK);
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
			MessageBox(CXLanguageResourceBase::g_sLangTxt_FoldAlrOpen/*_T("���ļ������ѱ��򿪵��ļ�")*/,CXLanguageResourceBase::g_sLangTxt_ModifiedFail/*_T("�޸��ļ�������ʧ��")*/,MB_OK);
		}
	}
	
	*pResult = 0;
}