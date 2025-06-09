// D:\WorkPM\Source\PMTest\GuideBookDev\UI\FileViewListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileViewListCtrl.h"
#include "DlgFileMngr.h"
#include "..\..\XLanguage\XLanguageResource.h"
// CFileViewListCtrl

IMPLEMENT_DYNAMIC(CFileViewListCtrl, CMFCListCtrl)

CFileViewListCtrl::CFileViewListCtrl()
{
	m_bFirstShow = TRUE;
	m_pFolderBase = NULL;
	m_pFolderTree = NULL;
	m_pFileMngrBase = NULL;
}

CFileViewListCtrl::~CFileViewListCtrl()
{
}


BEGIN_MESSAGE_MAP(CFileViewListCtrl, CMFCListCtrl)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_GBDEV_DELETE_FILES,&CFileViewListCtrl::OnDelete)
	ON_COMMAND(ID_GBDEV_RENAME_FILES,&CFileViewListCtrl::OnRename)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, &CFileViewListCtrl::OnLvnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CFileViewListCtrl::OnLvnEndlabeledit)
END_MESSAGE_MAP()


// CFileViewListCtrl ��Ϣ�������

int CFileViewListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	
	return 0;
}

int CFileViewListCtrl::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
{
	CString strItem1,strItem2;
	LVFINDINFO lvfi;
	lvfi.flags = LVFI_PARAM;
	lvfi.lParam = lParam1;
	strItem1 = this->GetItemText(this->FindItem(&lvfi,-1),iColumn);
	lvfi.lParam = lParam2;
	strItem2 = this->GetItemText(this->FindItem(&lvfi,-1),iColumn);

	// ���� �����ַ����Ƚ�
	return _tcsicmp(strItem1, strItem2);
}

void CFileViewListCtrl::SetRelatedFolderTreeCtrl(CFolderViewTreeCtrl* pFolderTree)
{
	m_pFolderTree = pFolderTree;
}

void CFileViewListCtrl::RefreshFileViewList()
{
	ASSERT(m_pFolderTree != NULL);

	CFolderBase* pSelFolder = (CFolderBase*)m_pFolderTree->GetItemData(m_pFolderTree->GetSelectedItem());

	if(m_bFirstShow)
	{
		InsertColumn(0,CXLanguageResourceBase::g_sLangID_Name/*_T("����")*/,LVCFMT_LEFT,200);
		InsertColumn(1,CXLanguageResourceBase::g_sLangID_Size2/*_T("��С")*/,LVCFMT_LEFT,60);
		InsertColumn(2,CXLanguageResourceBase::g_sLangID_Type/*_T("����")*/,LVCFMT_LEFT,100);
		InsertColumn(3,CXLanguageResourceBase::g_sLangTxt_ModifiedTime/*_T("�޸�ʱ��")*/,LVCFMT_LEFT,120);
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

void CFileViewListCtrl::InsertItemToListCtrl(CExBaseObject* pObj)
{
	UINT nClassID = pObj->GetClassID();
	int nIndex;
	int nCount = GetItemCount();
	CString strSize,strModifyTime,strType;

	if(IsFolder(nClassID))
	{
		CFolderBase* pFolder = (CFolderBase*)pObj;
		nIndex = InsertItem(nCount,pFolder->m_strName,0);
		SetItemText(nCount,1,_T(""));														//��С
		SetItemText(nCount,2,CXLanguageResourceBase::g_sLangTxt_Folder/*_T("�ļ���")*/);									//����
		pFolder->GetFolderModifyTime(strModifyTime);
		SetItemText(nCount,3,strModifyTime);								//�޸�ʱ��
		SetItemData(nIndex,(DWORD_PTR)pObj);
	}
	else if(IsFile(nClassID))
	{
		CFileBase* pFile = (CFileBase*)pObj;
		CString strPostfix;
		VERIFY(pFile->GetFilePostfix(strPostfix));
		strPostfix = strPostfix.Right(strPostfix.GetLength() - 1);

		if(strPostfix == m_strFilter)
		{
			VERIFY(pFile->GetFileSize(strSize));
			VERIFY(pFile->GetModifyTime(strModifyTime));
			//strType = pFile->GetFileType();
			nIndex = InsertItem(nCount,pObj->m_strName,2);
			SetItemText(nCount,1,strSize);														//��С
			SetItemText(nCount,2,strType);															//����
			SetItemText(nCount,3,strModifyTime);										//�޸�ʱ��
			SetItemData(nIndex,(DWORD_PTR)pObj);
		}
	}
}

void CFileViewListCtrl::OnRButtonDown(UINT nFlags, CPoint point)
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

void CFileViewListCtrl::OnContextMenuEx(CWnd* pWnd, CPoint point)
{
	CMenu menu;		
	menu.CreatePopupMenu();
	// ��Ӳ˵���
	
	if(GetSelectedCount() > 0)
	{
		if( GetSelectedCount() == 1)
			{
				menu.AppendMenu(MF_STRING,ID_GBDEV_RENAME_FILES,CXLanguageResourceBase::g_sLangTxt_ReName/*_T("������")*/);
				menu.AppendMenu(MF_SEPARATOR);
		}
		menu.AppendMenu(MF_STRING,ID_GBDEV_DELETE_FILES,CXLanguageResourceBase::g_sLangTxt_Delete/*_T("ɾ��")*/);
	}
	
	//ȷ������ʽ�˵���λ��
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			
	//��Դ����
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	
}

void CFileViewListCtrl::OnDelete()
{
	CString strInfo;
	strInfo.Format(CXLanguageResourceBase::g_sLangTxt_SureDeleItem/*_T("ȷ��Ҫɾ���� %d ����Ŀ��?")*/, GetSelectedCount());
	if( MessageBox(strInfo,CXLanguageResourceBase::g_sLangTxt_SureDelete/*_T("ɾ��ȷ��")*/,MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		if( MessageBox(CXLanguageResourceBase::g_sLangTxt_SureAgain/*_T("ɾ�����޷��ָ������ٴ�ȷ��")*/,CXLanguageResourceBase::g_sLangTxt_SureDelete/*_T("ɾ��ȷ��")*/,MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
		{
			long nCount = GetSelectedCount();
			int nItem = -1;
			for (int i=0;i < nCount;i++)
			{
				nItem = this->GetNextItem(nItem, LVNI_SELECTED);
				ASSERT(nItem != -1);
				CExBaseObject* pObj = (CExBaseObject*)this->GetItemData(nItem);
				if(IsFile(pObj->GetClassID()))
				{
					CFileBase* pFile = (CFileBase*)pObj;
					if( !pFile->DeleteFile())
					{
						MessageBox(CXLanguageResourceBase::g_sLangTxt_DeleteFail/*_T("�ļ����ڱ�ʹ�ã�ɾ��ʧ��")*/,CXLanguageResourceBase::g_sLangTxt_FileDeleteFail/*_T("ɾ���ļ�ʧ��")*/,MB_OK);
						return ;
					}
				}
				else if(IsFolder(pObj->GetClassID()))
				{
					CFolderBase* pFolder = (CFolderBase*)pObj;
					CFolderBase* pParentFolder = (CFolderBase*)pFolder->GetParent();
					ASSERT(pParentFolder != NULL);
					if( !pFolder->DeleteAllInFolder())
					{
						MessageBox(CXLanguageResourceBase::g_sLangTxt_DeleteFailFold/*_T("�ļ����а������ڱ�ʹ�õ��ļ���ɾ��ʧ��")*/,CXLanguageResourceBase::g_sLangTxt_FolderDeleteFail/*_T("ɾ���ļ���ʧ��")*/,MB_OK);
						return;
					}
					m_pFolderTree->DeleteItem(FindTreeItem(nItem));
				}
			}
			
			ASSERT(m_pFileMngrBase != NULL);
			m_pFileMngrBase->SaveXMLFile();
			this->RefreshFileViewList();
			//theApp.RefreshAllFileMngrDialogs((CDlgFileMngr*)this->GetParent());
			//theApp.RefreshAllFileMngrViews(NULL);

			AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this->GetParent());
		}
	}
}

void CFileViewListCtrl::OnRename()
{
	int nItem = -1;
	nItem = GetNextItem(nItem,LVNI_SELECTED);
	EditLabel(nItem);
}

//������listctrl��ѡ����ļ��в���treectrl�ж�Ӧ��HTREEITEM
HTREEITEM CFileViewListCtrl::FindTreeItem(int nItem)
{
	ASSERT(nItem != -1);
	CFolderBase* pFolder = (CFolderBase*)GetItemData(nItem);
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

void CFileViewListCtrl::OnLvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

	*pResult = 0;
}

void CFileViewListCtrl::OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
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
		
		if( IsFolder(pObj->GetClassID()) )
		{
			CFolderBase* pFolder = (CFolderBase*)pObj;
			if( pFolder->RenameFolder(str) )
			{
				m_pFolderTree->SetItemText(FindTreeItem(nItem),str);
				SetItemText(nItem,0,str);
				
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
		else if( IsFile(pObj->GetClassID()) )
		{
			CFileBase* pFile = (CFileBase*)pObj;
			if( pFile->RenameFile(str) )
			{
				SetItemText(nItem,0,str+m_strFilter);
				m_pFileMngrBase->SaveXMLFile();
				//theApp.RefreshAllFileMngrDialogs((CDlgFileMngr*)this->GetParent());
				//theApp.RefreshAllFileMngrViews(NULL);
				AfxGetApp()->PostThreadMessage(WM_THREAD_DLG_FILE_MNGR,0,(LPARAM)this->GetParent());
			}
			else
			{
				MessageBox(CXLanguageResourceBase::g_sLangTxt_FileOpened/*_T("���ļ��ѱ���")*/,CXLanguageResourceBase::g_sLangTxt_ModiftyFileNameFail/*_T("�޸��ļ�����ʧ��")*/,MB_OK);
			}
		}
	}

	*pResult = 0;
}
