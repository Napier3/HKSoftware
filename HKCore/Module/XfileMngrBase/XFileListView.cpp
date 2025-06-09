// D:\WorkPM\Source\PMTest\GuideBookDev\UI\XFileListView.cpp : 实现文件
//

#include "stdafx.h"
#include "XFileListView.h"
#include "XFileDlgDefine.h"

#include "XFolderEditDlg.h"
#include "XFolderAddDlg.h"
#include "XFilePasteDlg.h"
#include "XFileEditDlg.h"
#include "..\XLanguage\XLanguageMngr.h"

#ifdef _Use_YUN_Client_
	#include "YunFileApi\XYunFileApi.h"
#endif

#define XFILE_LIST_COL_NAME             0
#define XFILE_LIST_COL_TYPE              1
#define XFILE_LIST_COL_SIZE               2
#define XFILE_LIST_COL_DATE              3
#define XFILE_LIST_COL_SIZE_YUN        4
#define XFILE_LIST_COL_DATE_YUN       5

#ifdef ATS_TEMPLREPORT_MNGR
	#define XFILE_LIST_COL_STATE		4
#endif 


// CXFileListView

IMPLEMENT_DYNAMIC(CXFileListView, CMFCListCtrl)

CXFileListView::CXFileListView()
{
	m_bFirstShow = TRUE;
	m_pXFolder = NULL;
	m_pFolderTree = NULL;
	m_pXFileMngr = NULL;
	m_bDeleteAllFolder = TRUE;
	m_nCurrSelIndex = 0;
	m_pFrameWnd = NULL;
}

CXFileListView::~CXFileListView()
{
}


BEGIN_MESSAGE_MAP(CXFileListView, CMFCListCtrl)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_GBDEV_DELETE_FILES,&CXFileListView::OnDelete)
	ON_COMMAND(ID_GBDEV_RENAME_FILES,&CXFileListView::OnRename)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, &CXFileListView::OnLvnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CXFileListView::OnLvnEndlabeledit)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_ADD, &CXFileListView::OnUpdateFolderAdd)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_ADD, &CXFileListView::OnFolderAdd)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_DELETE, &CXFileListView::OnUpdateFolderDelete)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_DELETE, &CXFileListView::OnFolderDelete)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EDIT, &CXFileListView::OnUpdateFolderEdit)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EDIT, &CXFileListView::OnFolderEdit)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_EXPORT, &CXFileListView::OnUpdateFolderExport)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_EXPORT,&CXFileListView:: OnFolderExport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_FOLDER_IMPORT, &CXFileListView::OnUpdateFolderImport)
	ON_COMMAND(XFID_XFILEMNGR_FOLDER_IMPORT, &CXFileListView::OnFolderImport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_COPY, &CXFileListView::OnUpdateFileCopy)
	ON_COMMAND(XFID_XFILEMNGRFILE_COPY, &CXFileListView::OnFileCopy)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_PASTE, &CXFileListView::OnUpdateFilePaste)
	ON_COMMAND(XFID_XFILEMNGRFILE_PASTE, &CXFileListView::OnFilePaste)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_DELETE, &CXFileListView::OnUpdateFileDelete)
	ON_COMMAND(XFID_XFILEMNGRFILE_DELETE, &CXFileListView::OnFileDelete)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EDIT, &CXFileListView::OnUpdateFileEdit)
	ON_COMMAND(XFID_XFILEMNGRFILE_EDIT, &CXFileListView::OnFileEdit)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_EXPORT, &CXFileListView::OnUpdateFileExport)
	ON_COMMAND(XFID_XFILEMNGRFILE_EXPORT, &CXFileListView::OnFileExport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_IMPORT, &CXFileListView::OnUpdateFileImport)
	ON_COMMAND(XFID_XFILEMNGRFILE_IMPORT, &CXFileListView::OnFileImport)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_DOWNLOAD, OnUpdateFileDownload)
	ON_COMMAND(XFID_XFILEMNGRFILE_DOWNLOAD, OnFileDownload)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGRFILE_UPLOAD, OnUpdateFileUpload)
	ON_COMMAND(XFID_XFILEMNGRFILE_UPLOAD, OnFileUpload)
	ON_NOTIFY_REFLECT(NM_CLICK, &CXFileListView::OnNMClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CXFileListView::OnNMDblclk)
	ON_COMMAND(XFID_XFILEMNGR_PUBLISH_ADD, &CXFileListView::OnPublishFileAdd)
	ON_UPDATE_COMMAND_UI(XFID_XFILEMNGR_PUBLISH_ADD, &CXFileListView::OnUpdatePublishFileAdd)
END_MESSAGE_MAP()


// CXFileListView 消息处理程序

int CXFileListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	return 0;
}

int CXFileListView::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
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

void CXFileListView::SetRelatedFolderTreeCtrl(CXFolderTreeCtrl* pFolderTree)
{
	m_pFolderTree = pFolderTree;
}

void CXFileListView::RefreshFileViewList()
{
	if (m_pFolderTree == NULL)
	{
		return;
	}

	ASSERT(m_pFolderTree != NULL);
	CXFolder* pSelFolder = m_pXFileMngr->GetCurrSelFolder();//(CXFolder*)m_pFolderTree->GetItemData(m_pFolderTree->GetSelectedItem());

	if (pSelFolder == NULL)
	{
		return;
	}

	if(m_bFirstShow)
	{
		InsertColumn(XFILE_LIST_COL_NAME,g_sLangTxt_Name/*_T("名称")*/,LVCFMT_LEFT,300);
		InsertColumn(XFILE_LIST_COL_SIZE,g_sLangTxt_Size/*_T("大小(KB)")*/,LVCFMT_LEFT,80);
		InsertColumn(XFILE_LIST_COL_TYPE,g_sLangTxt_Type/*_T("类型")*/,LVCFMT_LEFT,80);
		InsertColumn(XFILE_LIST_COL_DATE,g_sLangTxt_ModifiedTime/*_T("修改时间")*/,LVCFMT_LEFT,120);

#ifdef ATS_TEMPLREPORT_MNGR
		InsertColumn(XFILE_LIST_COL_STATE,_T("状态"),LVCFMT_LEFT,80);
#else
		if (m_bUseYun)
		{
			InsertColumn(XFILE_LIST_COL_SIZE_YUN,_T("大小(KB):云"),LVCFMT_LEFT,80);
			InsertColumn(XFILE_LIST_COL_DATE_YUN,_T("修改时间:云"),LVCFMT_LEFT,120);
		}
#endif
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

void CXFileListView::InsertItemToListCtrl(CExBaseObject* pObj)
{
	UINT nClassID = pObj->GetClassID();
	int nIndex;
	int nCount = GetItemCount();
	CString strSize,strModifyTime,strType;

#ifndef ATS_TEMPLREPORT_MNGR
	if(xfile_IsFolder(nClassID))
	{
		CXFolder* pFolder = (CXFolder*)pObj;

		if (pFolder->IsYunFolder())
		{
			nIndex = InsertItem(nCount,pFolder->m_strName,6);
		}
		else
		{
			nIndex = InsertItem(nCount,pFolder->m_strName,0);
		}
		SetItemText(nCount,XFILE_LIST_COL_SIZE,_T(""));
		SetItemText(nCount,XFILE_LIST_COL_TYPE,g_sLangTxt_Folder/*_T("文件夹")*/);
		pFolder->GetFolderModifyTime(strModifyTime);
		SetItemText(nCount,XFILE_LIST_COL_DATE,strModifyTime);
		SetItemData(nIndex,(DWORD_PTR)pObj);

		if (m_bUseYun)
		{
			if (pFolder->IsYunFolder())
			{
				SetItemText(nCount, XFILE_LIST_COL_SIZE_YUN, _T("*"));
				SetItemText(nCount, XFILE_LIST_COL_DATE_YUN, _T("*"));
			}
		}
	}
	else if(xfile_IsFile(nClassID))
#else	//ATS_TEMPLREPORT_MNGR
	if(xfile_IsFile(nClassID))
#endif	//ATS_TEMPLREPORT_MNGR
	{
		CXFile* pFile = (CXFile*)pObj;
		CString strPostfix;
		VERIFY(pFile->GetFilePostfix(strPostfix, FALSE));

		//if(strPostfix == m_strFilter)
		if (m_pXFileMngr->ValidateFilePostfix(strPostfix))
		{
			pFile->GetFileSize(strSize);
			pFile->GetModifyTime(strModifyTime);
			strType = pFile->GetFileType();

			if (pFile->IsYunFile())
			{
				nIndex = InsertItem(nCount,pObj->m_strName,8);
			}
			else
			{
				nIndex = InsertItem(nCount,pObj->m_strName,2);
			}

			SetItemText(nCount,XFILE_LIST_COL_SIZE,strSize);
			SetItemText(nCount,XFILE_LIST_COL_TYPE,strType);
			SetItemText(nCount,XFILE_LIST_COL_DATE,strModifyTime);
			SetItemData(nIndex,(DWORD_PTR)pObj);

			if (m_bUseYun)
			{
				if (pFile->IsYunFile())
				{
#ifdef ATS_TEMPLREPORT_MNGR
					SetItemText(nCount, XFILE_LIST_COL_STATE, _T("已上传"));
#else
					VERIFY(pFile->GetFileSize_Yun(strSize));
					VERIFY(pFile->GetModifyTime_Yun(strModifyTime));

					SetItemText(nCount, XFILE_LIST_COL_SIZE_YUN, strSize);
					SetItemText(nCount, XFILE_LIST_COL_DATE_YUN, strModifyTime);
#endif
				}
			}
		}
	}
}

void CXFileListView::UpdateItemToListCtrl(CExBaseObject* pObj, long nItem)
{
	UINT nClassID = pObj->GetClassID();
	CString strSize,strModifyTime,strType;

	if(xfile_IsFolder(nClassID))
	{
		CXFolder* pFolder = (CXFolder*)pObj;
		SetItemText(nItem,XFILE_LIST_COL_NAME,pFolder->m_strName);
		SetItemText(nItem,XFILE_LIST_COL_SIZE,_T(""));
		SetItemText(nItem,XFILE_LIST_COL_TYPE,g_sLangTxt_Folder/*_T("文件夹")*/);
		pFolder->GetFolderModifyTime(strModifyTime);
		SetItemText(nItem,XFILE_LIST_COL_DATE,strModifyTime);
		SetItemData(nItem,(DWORD_PTR)pObj);
	}
	else if(xfile_IsFile(nClassID))
	{
		CXFile* pFile = (CXFile*)pObj;
		CString strPostfix;
		VERIFY(pFile->GetFilePostfix(strPostfix, FALSE));

		if (m_pXFileMngr->ValidateFilePostfix(strPostfix))
		{
			VERIFY(pFile->GetFileSize(strSize));
			VERIFY(pFile->GetModifyTime(strModifyTime));
			strType = pFile->GetFileType();
			SetItemText(nItem,XFILE_LIST_COL_NAME,pObj->m_strName);
			SetItemText(nItem,XFILE_LIST_COL_SIZE,strSize);
			SetItemText(nItem,XFILE_LIST_COL_TYPE,strType);
			SetItemText(nItem,XFILE_LIST_COL_DATE,strModifyTime);
			SetItemData(nItem,(DWORD_PTR)pObj);

			if (m_bUseYun)
			{
				if (pFile->IsYunFile())
				{
					VERIFY(pFile->GetFileSize_Yun(strSize));
					VERIFY(pFile->GetModifyTime_Yun(strModifyTime));

					SetItemText(nItem, XFILE_LIST_COL_SIZE_YUN, strSize);
					SetItemText(nItem, XFILE_LIST_COL_DATE_YUN, strModifyTime);
				}
			}
		}
	}
}

void CXFileListView::OnRButtonDown(UINT nFlags, CPoint point)
{
	long nCount = GetSelectedCount();
	int nItem = -1;
	UINT uFlags = 0;
	nItem = HitTest(point, &uFlags);
	OnSelectXFileChanged(nItem);
	nCount = GetSelectedCount();

	CMFCListCtrl::OnRButtonDown(nFlags, point);

	//if(nCount > 0)
	{
		ClientToScreen(&point);
		OnContextMenuEx(this, point);
	}
}

void CXFileListView::OnContextMenuEx(CWnd* pWnd, CPoint point)
{
	CMenu menu;		
	menu.CreatePopupMenu();
	// 添加菜单项

	CXFile *pSelFile = m_pXFileMngr->GetCurrSelFile();
	CXFile *pCopySrcFile = m_pXFileMngr->GetCopySrcFile();

#ifdef ATS_TEMPLREPORT_MNGR
	if (pSelFile != NULL)	//Yun Server
	{
		if (pSelFile->IsYunFile())
		{
			menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DOWNLOAD,g_sLangTxt_DownLoad/*_T("下载")*/);
		}

		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_UPLOAD,g_sLangTxt_UpLoad/*_T("上传")*/);
	}
#else	//ATS_TEMPLREPORT_MNGR

#ifdef _ATS_VER_PUBLISH
	if (pSelFile != NULL)
	{
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_PUBLISH_ADD,g_sLangTxt_AddPubFile/*_T("添加")*/);
	}
#else//_ATS_VER_PUBLISH
	menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
	menu.AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);

	if (pSelFile != NULL)
	{
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_COPY,g_sLangTxt_CopyFile/*_T("拷贝文件")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DELETE,g_sLangTxt_DeleteFile/*_T("删除文件")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EDIT,g_sLangTxt_FileRename/*_T("修改文件名称")*/);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EXPORT,g_sLangTxt_ExportFile/*_T("导出文件")*/);
	}

	if (pCopySrcFile != NULL)
	{
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
	}

	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
#endif////_ATS_VER_PUBLISH

#ifndef _ATS_VER_PUBLISH
	if (pSelFile != NULL)	//Yun Server
	{
		menu.AppendMenu(MF_SEPARATOR);

		if (pSelFile->IsYunFile())
		{
			menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DOWNLOAD,g_sLangTxt_DownLoad/*_T("下载")*/);
		}

		menu.AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_UPLOAD,g_sLangTxt_UpLoad/*_T("上传")*/);
	}
#endif

#endif	//ATS_TEMPLREPORT_MNGR

	//确定弹出式菜单的位置
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y, pWnd);			

	//资源回收
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	
}

void CXFileListView::OnDelete()
{
	long nCount = GetSelectedCount();

	if (nCount == 0)
	{
		m_pFolderTree->OnFolderDelete();
		return;
	}

	CString strInfo;
	strInfo.Format(g_sLangTxt_SureDeleItem/*_T("确定要删除这 %d 个项目吗?")*/, GetSelectedCount());
	
	if( MessageBox(strInfo,g_sLangTxt_SureDelete/*_T("删除确认")*/,MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		if( MessageBox(g_sLangTxt_SureAgain/*_T("删除后将无法恢复，请再次确认")*/,g_sLangTxt_SureDelete/*_T("删除确认")*/,MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
		{
			int nItem = -1;
		
			for (int i=0;i < nCount;i++)
			{
				nItem = -1;
				nItem = this->GetNextItem(nItem, LVNI_SELECTED);

				if (nItem == -1)
				{
					break;
				}

				ASSERT(nItem != -1);
				CExBaseObject* pObj = (CExBaseObject*)this->GetItemData(nItem);
				
				if(xfile_IsFile(pObj->GetClassID()))
				{
					CXFile* pFile = (CXFile*)pObj;
					
					if( !pFile->DeleteFile())
					{
						MessageBox(g_sLangTxt_DeleteFail /*_T("文件正在被使用，删除失败")*/,g_sLangTxt_FileDeleteFail/*_T("删除文件失败")*/,MB_OK);
						return ;
					}

					CXFolder* pParentFolder = (CXFolder*)pFile->GetParent();
					pParentFolder->Delete(pFile);
				}
				else if(xfile_IsFolder(pObj->GetClassID()))
				{
					CXFolder* pFolder = (CXFolder*)pObj;
					CXFolder* pParentFolder = (CXFolder*)pFolder->GetParent();
					ASSERT(pParentFolder != NULL);
					HTREEITEM hItemFolder = (HTREEITEM)pFolder->m_dwItemData;
					
					if( !pFolder->DeleteAllInFolder())
					{
						MessageBox(g_sLangTxt_DeleteFailFold/*_T("文件夹中包含正在被使用的文件，删除失败")*/,g_sLangTxt_FolderDeleteFail/*_T("删除文件夹失败")*/,MB_OK);
						return;
					}
					
					m_pFolderTree->DeleteItem(hItemFolder);
				}

				DeleteItem(nItem);
			}
			
			AfxGetApp()->PostThreadMessage(WM_THREAD_XFILE_MNGR,0,(LPARAM)this->GetParent());
			m_pXFileMngr->SetCurrSel(NULL);
		}
	}
}

void CXFileListView::OnRename()
{
	int nItem = -1;
	nItem = GetNextItem(nItem,LVNI_SELECTED);
	EditLabel(nItem);
}

//根据在listctrl中选择的文件夹查找treectrl中对应的HTREEITEM
HTREEITEM CXFileListView::FindTreeItem(int nItem)
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

void CXFileListView::OnLvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

	*pResult = 0;
}

void CXFileListView::OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	ASSERT(m_pXFileMngr != NULL);
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
				SetItemText(nItem, XFILE_LIST_COL_NAME,str);
				
				//m_pXFileMngr->SaveXMLFile();
				AfxGetApp()->PostThreadMessage(WM_THREAD_XFILE_MNGR,0,(LPARAM)this->GetParent());
			}
			else
			{
				MessageBox(g_sLangTxt_FoldAlrOpen/*_T("该文件夹中已被打开的文件")*/,g_sLangTxt_ModifiedFail/*_T("修改文件夹名称失败")*/,MB_OK);
			}
		}
		else if( xfile_IsFile(pObj->GetClassID()) )
		{
			CXFile* pFile = (CXFile*)pObj;
			if( pFile->RenameFile(str) )
			{
				SetItemText(nItem, XFILE_LIST_COL_NAME,str+m_strFilter);
				//m_pXFileMngr->SaveXMLFile();
				AfxGetApp()->PostThreadMessage(WM_THREAD_XFILE_MNGR,0,(LPARAM)this->GetParent());
			}
			else
			{
				MessageBox(g_sLangTxt_FileOpened /*_T("该文件已被打开")*/,g_sLangTxt_ModifiedFail/*_T("修改文件名称失败")*/,MB_OK);
			}
		}
	}

	*pResult = 0;
}


//////////////////////////////////////////////////////////////////////////

void CXFileListView::OnUpdateFolderAdd(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFolder != NULL || pFile != NULL);
}

void CXFileListView::OnFolderAdd()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	CXFolderAddDlg dlg;
	dlg.m_pSrcFolder = pFolder;

	if (dlg.DoModal() == IDOK)
	{
		CXFolder *pNew = pFolder->AddFolder(dlg.m_strDestFolderName);
		InsertItemToListCtrl(pNew);
		m_pFolderTree->Insert(pNew);
	}
}

void CXFileListView::OnUpdateFolderDelete(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngr));
}

void CXFileListView::OnFolderDelete()
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	if (pFolder == NULL)
	{
		return ;
	}

	if (!m_bDeleteAllFolder)
	{
		if (pFolder->GetCount() > 0)
		{
			CString strMsg;
			strMsg.Format(g_sLangTxt_FoldCoverFold /*_T("文件夹【%s】包含子文件夹或者文件\r\n请先删除子文件夹或者文件，然后再删除目录")*/, pFolder->m_strName);
			MessageBox(strMsg,g_sLangTxt_Message/* _T("提示")*/, MB_OK | MB_ICONWARNING);
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

	if (MessageBox(strMsg,g_sLangTxt_Message/* _T("提示")*/, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		return;
	}

	long nItem = -1;
	GetNextItem(nItem, LVNI_SELECTED);
	DeleteItem(nItem);

	CXFolder *pParnt = (CXFolder*)pFolder->GetParent();

	HTREEITEM hNext = m_pFolderTree->Delete(pFolder);

	if (m_bDeleteAllFolder)
	{
		pFolder->DeleteFolderEx();
	}
	else
	{
		pFolder->DeleteFolder();
	}

	pParnt->Delete(pFolder);
}

void CXFileListView::OnUpdateFolderEdit(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngr));
}

void CXFileListView::OnFolderEdit()
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
		m_pFolderTree->Update(pFolder);
		UpdateItemToListCtrl(pFolder, m_nCurrSelIndex);
	}

}

void CXFileListView::OnUpdateFolderExport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();

	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngr));
}

void CXFileListView::OnFolderExport()
{
	m_pFolderTree->OnFolderExport();
}

void CXFileListView::OnUpdateFolderImport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	//	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFolder != NULL);
}

void CXFileListView::OnFolderImport()
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
		MessageBox(strMsg, g_sLangTxt_Message/* _T("提示")*/, MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	CXFolder *pNew = pFolder->AddPath(strPath);
	m_pFolderTree->Insert(pNew);
	InsertItemToListCtrl(pNew);
}

void CXFileListView::OnUpdateFileCopy(CCmdUI* pCmdUI)
{
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFileListView::OnFileCopy()
{
	m_pXFileMngr->CopyFile();
}

void CXFileListView::OnUpdateFilePaste(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrFolder();
	CXFile *pFile = m_pXFileMngr->GetCopySrcFile();

	pCmdUI->Enable(pFolder != NULL && pFile != NULL);
}

void CXFileListView::OnFilePaste()
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

	InsertItemToListCtrl(pNewFile);

	//Select((HTREEITEM)pNewFile->m_dwItemData, TVGN_CARET);
}

void CXFileListView::OnUpdateFileDelete(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFileListView::OnFileDelete()
{
	OnDelete();
}

void CXFileListView::OnUpdateFileEdit(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFileListView::OnFileEdit()
{
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	if (pFile == NULL)
	{
		return ;
	}

	CXFileEditDlg dlg;
	dlg.m_pSrcFile = pFile;
	//dlg.m_pXFileMsgRcvWnd = m_pXFileMsgRcvWnd;

	if (dlg.DoModal() == IDOK)
	{
		UpdateItemToListCtrl(pFile, m_nCurrSelIndex);
	}

}

void CXFileListView::OnUpdateFileExport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL);
}

void CXFileListView::OnFileExport()
{
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();
// 	CString strPath = pFile->GetRelativePath(TRUE);
// 	CString strDestFile = pFile->m_strID;
// 
// 	CString strXFileFilter, strXFilePostFix;
// 	m_pXFileMngr->GetXFileDlgString(strXFileFilter, strXFilePostFix);

	TCHAR pszBuffer[MAX_PATH];
	bstr_t bstrText;
	bstrText = g_sLangTxt_ChoImpFile;

	if (!FGetDirectory(m_hWnd, pszBuffer, bstrText/*_T("选择导入的配置文件夹")*/))
	{
		return;
	}

	CString strPath;
	strPath = pszBuffer;
	m_pXFileMngr->XCopyFile(pFile, strPath, FALSE);

// 	if (PopupSaveAsFileDialog(this, strDestFile, strXFileFilter, strXFilePostFix))
// 	{
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
		//XCopyFile(strPath, strDestFile, FALSE);
// 	}
}

void CXFileListView::OnUpdateFileImport(CCmdUI* pCmdUI)
{
	CXFolder *pFolder = m_pXFileMngr->GetCurrSelFolder();
	CXFile *pFile = m_pXFileMngr->GetCurrSelFile();

	pCmdUI->Enable(pFile != NULL || pFolder != NULL);
}


void CXFileListView::OnFileImport()
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
		strMsg.Format(g_sLangTxt_ExiSaNameFileCov /*_T("存在同名称的文件【%s】,覆盖吗？")*/, strName);

		if (MessageBox(strMsg, g_sLangTxt_FileCover/*_T("覆盖文件")*/, MB_OKCANCEL) == IDOK)
		{
			//pFile = pFolder->OverWriteFile(strSrcFile);
			m_pXFileMngr->XImportFile(strSrcFile, pFolder, FALSE);
			UpdateItemToListCtrl(pFile, m_nCurrSelIndex);
		}
	}
	else
	{
		m_pXFileMngr->XImportFile(strSrcFile, pFolder, FALSE);
		CString strName = GetLastFolderNameFromPathName(strSrcFile);
		pFile = pFolder->AddFile2(strName);

		if (pFile != NULL)
		{
			InsertItemToListCtrl(pFile);
		}
	}	
}


void CXFileListView::OnUpdateFileDownload(CCmdUI* pCmdUI)
{

}

void CXFileListView::OnFileDownload()
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
#else
	m_pFrameWnd->PostMessage(WM_USER+1010,(WPARAM)pXObj,(LPARAM)pXObj);
#endif
}

void CXFileListView::OnUpdateFileUpload(CCmdUI* pCmdUI)
{

}

void CXFileListView::OnFileUpload()
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
#else
	m_pFrameWnd->PostMessage(WM_USER+1011,(WPARAM)pXObj,(LPARAM)pXObj);
#endif
}

void CXFileListView::OnSelectXFileChanged(long nItemIndex)
{
	m_nCurrSelIndex = nItemIndex;
	CExBaseObject *pSel = NULL;

	if (m_nCurrSelIndex >= 0)
	{
		pSel = (CExBaseObject*)GetItemData(m_nCurrSelIndex);
		m_pXFileMngr->SetCurrSel(pSel);
		xfile_PostXFileObjSelChangeMsg(m_pFrameWnd, WM_THREAD_XFILE_MNGR, pSel);
	}
	else
	{
		m_pXFileMngr->SetCurrSel(NULL);
	}
}

void CXFileListView::OnPublishFileAdd()
{
	CExBaseObject *pXObj = m_pXFileMngr->GetCurrSel();

	if (pXObj == NULL)
	{
		return;
	}

#ifdef _ATS_VER_PUBLISH
	m_pFrameWnd->PostMessage(WM_USER+2011,(WPARAM)pXObj,(LPARAM)pXObj);
#endif
}

void CXFileListView::OnUpdatePublishFileAdd(CCmdUI* pCmdUI)
{

}

void CXFileListView::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	OnSelectXFileChanged(pNMItemActivate->iItem);
// 	m_nCurrSelIndex = pNMItemActivate->iItem;
// 	CExBaseObject *pSel = NULL;
// 
// 	if (m_nCurrSelIndex >= 0)
// 	{
// 		pSel = (CExBaseObject*)GetItemData(m_nCurrSelIndex);
// 		m_pXFileMngr->SetCurrSel(pSel);
// 		xfile_PostXFileObjSelChangeMsg(m_pFrameWnd, WM_THREAD_XFILE_MNGR, pSel);
// 	}

	*pResult = 0;
}

void CXFileListView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	long nCount = GetSelectedCount();

	if(nCount == 1)
	{
		int nItem = -1;
		nItem = GetNextItem(nItem,LVNI_SELECTED);
		ASSERT(nItem != -1);
		CExBaseObject* pObj = (CExBaseObject*)GetItemData(nItem);

		if( xfile_IsFolder(pObj->GetClassID()) )
		{
			ASSERT (m_pFolderTree != NULL);
			m_pFolderTree->SelectItem((HTREEITEM)pObj->m_dwItemData);
		}

		if( xfile_IsFile(pObj->GetClassID()) )
		{
			CXFile *pFile = (CXFile *)pObj;
			xfile_PostXFileObjSelChangeMsg(m_pFrameWnd, WM_XFILEMNGR_OPEN_XFILE, pFile);
		}
	}

	*pResult = 0;
}
