// XFileDockablePane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XFileDlgDefine.h"

#include "XFilePasteDlg.h"
#include "XFileEditDlg.h"

#include "XFolderEditDlg.h"
#include "XFolderAddDlg.h"
#include "..\API\GloblaDrawFunctions.h"

#include "XFolderTreeCtrl.h"
#include "XFileListView.h"
// 
// CXFileMngrOptrInterface::CXFileMngrOptrInterface()
// {
// 	m_pXFileMngrWnd = NULL;
// }
// 
// CXFileMngrOptrInterface::~CXFileMngrOptrInterface()
// {
// 
// }
// 
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFolderAdd(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 
// 	pCmdUI->Enable(pFolder != NULL || pFile != NULL);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFolderAdd()
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrFolder();
// 	CXFolderAddDlg dlg;
// 	dlg.m_pSrcFolder = pFolder;
// 
// 	if (dlg.DoModal() == IDOK)
// 	{
// 		CXFolder *pNew = pFolder->AddFolder(dlg.m_strDestFolderName);
// 		m_pXFolderTreeRef->Insert(pNew);
// 	}
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFolderDelete(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 
// 	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngrRef));
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFolderDelete()
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 	
// 	if (pFolder == NULL)
// 	{
// 		return ;
// 	}
// 
// 	LRESULT nRet = m_pXFileMsgRcvWndRef->XDeleteXFolder(pFolder);
// 
// 	if (nRet == XFILEMNGR_OPTR_FAILED)
// 	{
// 		return;
// 	}
// 
// 	if (!m_bDeleteAllFolder)
// 	{
// 		if (pFolder->GetCount() > 0)
// 		{
// 			CString strMsg;
// 			strMsg.Format(_T("�ļ��С�%s���������ļ��л����ļ�\r\n����ɾ�����ļ��л����ļ���Ȼ����ɾ��Ŀ¼"), pFolder->m_strName);
// 			ASSERT(m_pXFileMngrWnd != NULL);
// 			m_pXFileMngrWnd->MessageBox(strMsg, _T("��ʾ"), MB_OK | MB_ICONWARNING);
// 			return;
// 		}
// 	}
// 
// 	CString strMsg;
// 
// 	if (m_bDeleteAllFolder)
// 	{
// 		strMsg.Format(_T("ɾ���ļ��н�ɾ�����ļ��м����µ�ȫ���ļ����ļ��С�\r\nȷʵҪɾ���ļ��С�%s����"), pFolder->m_strName);
// 	}
// 	else
// 	{
// 		strMsg.Format(_T("ȷʵҪɾ���ļ��С�%s����"), pFolder->m_strName);
// 	}
// 	
// 	if (m_pXFileMngrWnd->MessageBox(strMsg, _T("��ʾ"), MB_YESNO | MB_ICONQUESTION) == IDNO)
// 	{
// 		return;
// 	}
// 
// 	CXFolder *pParnt = (CXFolder*)pFolder->GetParent();
// 
// 	HTREEITEM hNext = m_pXFolderTreeRef->Delete(pFolder);
// 
// 	if (m_bDeleteAllFolder)
// 	{
// 		pFolder->DeleteFolderEx();
// 	}
// 	else
// 	{
// 		pFolder->DeleteFolder();
// 	}
// 
// 	pParnt->Delete(pFolder);
// 	m_pXFolderTreeRef->SelectItem(hNext);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFolderEdit(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 
// 	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngrRef));
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFolderEdit()
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 
// 	if (pFolder == NULL)
// 	{
// 		return ;
// 	}
// 
// 	CXFolderEditDlg dlg;
// 	dlg.m_pSrcFolder = pFolder;
// 
// 	if (dlg.DoModal() == IDOK)
// 	{
// 		m_pXFolderTreeRef->Update(pFolder);
// 	}
// 
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFolderExport(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 
// 	pCmdUI->Enable(pFolder != NULL && pFolder != (m_pXFileMngrRef));
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFolderExport()
// {
// 	CXFolder *pSrcFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 
// 	if (pSrcFolder == NULL)
// 	{
// 		return;
// 	}
// 
// 	TCHAR pszBuffer[MAX_PATH];
// 
// 	if (!FGetDirectory(m_pXFileMngrWnd->m_hWnd, pszBuffer, _T("ѡ�������ļ��е���Ŀ��Ŀ¼")))
// 	{
// 		return;
// 	}
// 
// 	//strDestParentPath��Ŀ���ļ��У����ļ��У�
// 	//strDestPath��Ŀ���ļ���
// 	CString strDestParentPath = pszBuffer;
// 	CString strName;
// 	CString strDestPath = strDestParentPath + _P_FOLDER_PATH_SEPARATOR_ + pSrcFolder->m_strName;
// 	CString strMsg;
// 
// 	if (IsFileExist(strDestPath))
// 	{
// 		strMsg.Format(_T("Ŀ���ļ��С�%s���Ѿ�����"), strDestPath);
// 		m_pXFileMngrWnd->MessageBox(strMsg, _T("��ʾ"), MB_OK | MB_ICONWARNING);
// 		return;
// 	}
// 
// 	//pDestParentFolder=Ŀ���ļ��У����ļ��У�
// 	CXFolder *pDestParentFolder = new CXFolder();
// 	pSrcFolder->CopyOwn(pDestParentFolder);
// 	pDestParentFolder->SetPath(strDestParentPath);
// 
// 	CXFolder *pDestNew = (CXFolder*)pDestParentFolder->Paste(pSrcFolder);
// 
// 	strMsg.Format(_T("����Ŀ���ļ��С�%s�����"), strDestPath);
// 	m_pXFileMngrWnd->MessageBox(strMsg, _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
// 	delete pDestParentFolder;
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFolderImport(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrFolder();
// //	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 
// 	pCmdUI->Enable(pFolder != NULL);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFolderImport()
// {
// 	TCHAR pszBuffer[MAX_PATH];
// 
// 	if (!FGetDirectory(m_pXFileMngrWnd->m_hWnd, pszBuffer, _T("ѡ����������ļ���")))
// 	{
// 		return;
// 	}
// 
// 	CString strPath = pszBuffer;
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrFolder();
// 	CString strName;
// 	long nPos = strPath.ReverseFind('\\');
// 
// 	if (nPos < 0)
// 	{
// 		return;
// 	}
// 
// 	strName = strPath.Mid(nPos+1);
// 
// 	if (pFolder->FindByID(strName) != NULL)
// 	{
// 		CString strMsg;
// 		strMsg.Format(_T("����ͬ���Ƶ��ļ��С�%s��"), strName);
// 		m_pXFileMngrWnd->MessageBox(strMsg, _T("��ʾ"), MB_OK | MB_ICONEXCLAMATION);
// 		return;
// 	}
// 
// 	CXFolder *pNew = pFolder->AddPath(strPath);
// 	m_pXFolderTreeRef->Insert(pNew);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFileCopy(CCmdUI* pCmdUI)
// {
// 	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 
// 	pCmdUI->Enable(pFile != NULL);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFileCopy()
// {
// 	m_pXFileMngrRef->CopyFile();
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFilePaste(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrFolder();
// 	CXFile *pFile = m_pXFileMngrRef->GetCopySrcFile();
// 
// 	pCmdUI->Enable(pFolder != NULL && pFile != NULL);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFilePaste()
// {
// 	CXFile *pFile = m_pXFileMngrRef->GetCopySrcFile();
// 
// 	if (pFile == NULL)
// 	{
// 		return;
// 	}
// 
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrFolder();
// 	CXFile *pNewFile = NULL;
// 
// 	if (pFolder->FindByID(pFile->m_strID) == NULL)
// 	{
// 		pNewFile = pFolder->AddFile(pFile);
// 	}
// 	else
// 	{
// 		CXFilePasteDlg dlg;
// 		dlg.m_pSrcFile = pFile;
// 		dlg.m_pDestFolder = pFolder;
// 		dlg.DoModal();
// 
// 		pNewFile = dlg.m_pDestFile;
// 	}
// 
// 	if (pNewFile == NULL)
// 	{
// 		return;
// 	}
// 
// 	m_pXFolderTreeRef->Insert(pNewFile);
// 	m_pXFolderTreeRef->Select((HTREEITEM)pNewFile->m_dwItemData, TVGN_CARET);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFileDelete(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 
// 	pCmdUI->Enable(pFile != NULL);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFileDelete()
// {
// 	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 	CString strFile = pFile->GetRelativePath(FALSE);
// 	CString strMsg;
// 	strMsg.Format(_T("��ȷʵҪɾ���ļ���%s����"), strFile);
// 
// 	if (m_pXFileMngrWnd->MessageBox(strMsg, _T("��ʾ"), MB_OKCANCEL) != IDOK)
// 	{
// 		return;
// 	}
// 
// 	if (m_pXFileMsgRcvWndRef != NULL)
// 	{
// 		//LRESULT nRet = m_pXFileMsgRcvWndRef->SendMessage(WM_XFILEMNGR_DELETE_XFILE, (WPARAM)pFile, (LPARAM)pFile);
// 		LRESULT nRet = m_pXFileMsgRcvWndRef->XDeleteXFile(pFile);
// 
// 		if (nRet == XFILEMNGR_OPTR_FAILED)
// 		{
// 			return;
// 		}
// 	}
// 
// 	HTREEITEM hNextSel = m_pXFolderTreeRef->Delete(pFile);
// 	m_pXFileMngrRef->DeleteFile(pFile);
// 	m_pXFolderTreeRef->SelectItem(hNextSel);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFileEdit(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 
// 	pCmdUI->Enable(pFile != NULL);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFileEdit()
// {
// 	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 
// 	if (pFile == NULL)
// 	{
// 		return ;
// 	}
// 
// 	CXFileEditDlg dlg;
// 	dlg.m_pSrcFile = pFile;
// 	dlg.m_pXFileMsgRcvWnd = m_pXFileMsgRcvWndRef;
// 
// 	if (dlg.DoModal() == IDOK)
// 	{
// 		m_pXFolderTreeRef->Update(pFile);
// 	}
// 
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFileExport(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 
// 	pCmdUI->Enable(pFile != NULL);
// }
// 
// void CXFileMngrOptrInterface::xfile_OnFileExport()
// {
// 	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 	CString strPath = pFile->GetRelativePath(TRUE);
// 	CString strDestFile = pFile->m_strID;
// 
// 	if (PopupSaveAsFileDialog(m_pXFileMngrWnd, strDestFile, m_strXFileFilter, m_strXFilePostFix))
// 	{
// // 		if (m_pXFileMsgRcvWndRef != NULL)
// // 		{
// // 			LRESULT nRet = m_pXFileMsgRcvWndRef->SendMessage(WM_XFILEMNGR_EXPORT_XFILE, (WPARAM)&strPath, (LPARAM)&strDestFile);
// // 
// // 			if (nRet == XFILEMNGR_OPTR_SUCC)
// // 			{
// // 				return;
// // 			}
// // 		}
// 
// 		//::X_CopyFile(strPath, strDestFile, FALSE);
// 		XCopyFile(strPath, strDestFile, FALSE);
// 	}
// }
// 
// void CXFileMngrOptrInterface::xfile_OnUpdateFileImport(CCmdUI* pCmdUI)
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrSelFolder();
// 	CXFile *pFile = m_pXFileMngrRef->GetCurrSelFile();
// 
// 	pCmdUI->Enable(pFile != NULL || pFolder != NULL);
// }
// 
// 
// void CXFileMngrOptrInterface::xfile_OnFileImport()
// {
// 	CXFolder *pFolder = m_pXFileMngrRef->GetCurrFolder();
// 
// 	if (pFolder == NULL)
// 	{
// 		return;
// 	}
// 
// 	CString strSrcFile;
// 	CXFile *pFile = NULL;
// 
// 	if (!PopupOpenFileDialog(m_pXFileMngrWnd, strSrcFile, m_strXFileFilter, m_strXFilePostFix))
// 	{
// 		return;
// 	}
// 	
// 	if (pFolder->IsFileExist(strSrcFile))
// 	{
// 		CString strName = GetLastFolderNameFromPathName(strSrcFile);
// 		CString strMsg;
// 		strMsg.Format(_T("����ͬ���Ƶ��ļ���%s��,������"), strName);
// 		
// 		if (m_pXFileMngrWnd->MessageBox(strMsg, _T("�����ļ�"), MB_OKCANCEL) == IDOK)
// 		{
// 			pFile = pFolder->OverWriteFile(strSrcFile);
// 		}
// 	}
// 	else
// 	{
// 		pFile = pFolder->AddFile(strSrcFile);
// 		if (pFile != NULL)
// 		{
// 			m_pXFolderTreeRef->Insert(pFile);
// 		}
// 	}	
// }
// 
// void CXFileMngrOptrInterface::xfile_OnSaveAsFile(CXFolder *pCurrFolder, const CString &strFile)
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
// 			m_pXFolderTreeRef->Insert(pFile);
// 		}
// 	}
// }
// 
//  LRESULT CXFileMngrOptrInterface::xfile_OnInitXFileMngrMenu(WPARAM wParam, LPARAM lParam)
//  {
// 	CMenu *pMenu = (CMenu*)wParam;
// 	CExBaseObject* pObj = (CExBaseObject*)lParam;
// 
// 	UINT nClassID = pObj->GetClassID();
// 
// 	if (CLASSID_XFILE == nClassID)
// 	{
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,_T("���Ŀ¼"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,_T("����Ŀ¼"));
// 		pMenu->AppendMenu(MF_SEPARATOR);
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_COPY,_T("�����ļ�"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,_T("ճ���ļ�"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DELETE,_T("ɾ���ļ�"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EDIT,_T("�޸��ļ�����"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,_T("�����ļ�"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EXPORT,_T("�����ļ�"));
// 	}
// 	else if (nClassID == CLASSID_XFILEMNGR)
// 	{
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,_T("���Ŀ¼"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,_T("����Ŀ¼"));
// 		pMenu->AppendMenu(MF_SEPARATOR);
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,_T("ճ���ļ�"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,_T("�����ļ�"));
// 	}
// 	else if (nClassID == CLASSID_XFOLDER)
// 	{
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,_T("���Ŀ¼"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_DELETE,_T("ɾ��Ŀ¼"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EDIT,_T("�޸�Ŀ¼����"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,_T("����Ŀ¼"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EXPORT,_T("����Ŀ¼"));
// 		pMenu->AppendMenu(MF_SEPARATOR);
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,_T("ճ���ļ�"));
// 		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,_T("�����ļ�"));
// 	}
// 
// 	 return 0;
//  }


