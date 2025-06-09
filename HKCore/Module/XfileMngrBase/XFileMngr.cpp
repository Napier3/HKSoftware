#include "stdafx.h"
#include "XFileMngr.h"

#include "../XLanguage/XLanguageResource.h"
#include "../API/GlobalConfigApi.h"

#ifdef _Use_YUN_Client_
	#include "YunFileApi\XYunFileApi.h"
#endif

#ifdef _PSX_QT_LINUX_
#include <QTextCodec>
#endif

#include "../MemBuffer/BufferBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXFile* FindFileBaseByName(const CString& strFileName,CXFolder* pFolder,CXFolder* &pFolderFind)
{
	CExBaseObject* pObj = NULL;
	POS pos = pFolder->GetHeadPosition();

	while(pos != NULL)
	{
		pObj = pFolder->GetNext(pos);
		if( xfile_IsFile(pObj->GetClassID()) )
		{
			//如果是文件
			CXFile* pFile = (CXFile*)pObj;
			CString strFindFileName = pFile->GetTotalFileName();
			if(strFileName.CompareNoCase(strFindFileName) == 0)
			{
				pFolderFind = pFolder;
				return pFile;
			}
		}
		else if( xfile_IsFolder(pObj->GetClassID()) )
		{
			CXFile* pSubFile = NULL;
			pSubFile = FindFileBaseByName(strFileName,(CXFolder*)pObj,pFolderFind);
			if(pSubFile != NULL && pFolderFind != NULL)
			{
				return pSubFile;
			}
		}
	}

	return NULL;
}

CXFileMngr::CXFileMngr()
{
	m_pRefTreeCtrl = NULL;
#ifdef NOT_USE_XLANGUAGE
	m_strName =_T("配置文件管理");
#else
	m_strName = g_sLangTxt_ConfigFileManag/*_T("配置文件管理")*/;
#endif

// #ifdef _PSX_QT_LINUX_
// 	m_bUseUtf8TextCodec = TRUE;
// #endif

	m_strID = _T("_CXFileMngr_");
	m_pCurrSel = NULL;
	m_pSrcFile = NULL;
	SetOnllySearchMainTypeFile(TRUE);
	m_pYunRootFolder = NULL;
}

CXFileMngr::~CXFileMngr()
{
	if (m_pYunRootFolder != NULL)
	{
		delete m_pYunRootFolder;
		m_pYunRootFolder = NULL;
	}
}

void CXFileMngr::InitYunRootFolder(CDataGroup *pDestGroup)
{
	if (m_pYunRootFolder == NULL)
	{
		m_pYunRootFolder = new CDataGroup();
	}

	m_pYunRootFolder->DeleteAll();
	pDestGroup->CopyOwn(m_pYunRootFolder);
	m_pYunRootFolder->AppendCloneEx(*pDestGroup);
	DataGroupToXFolder(m_pYunRootFolder);
}

BOOL CXFileMngr::CopyFile()
{
	if (m_pCurrSel == NULL)
	{
		m_pSrcFile = NULL;
	}
	else
	{
		if (m_pCurrSel->GetClassID() == CLASSID_XFILE)
		{
			m_pSrcFile = (CXFile *)m_pCurrSel;
		}
		else
		{
			m_pSrcFile = NULL;
		}
	}

	return (m_pSrcFile != NULL);
}


long CXFileMngr::SetLibraryPath(const CString &strPath, BOOL bTraveSubFolder)
{
	return SetLibraryPath(strPath,TRUE,bTraveSubFolder,bTraveSubFolder);
// 	m_pCurrSel = NULL;
// 
// 	if (strPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
// 	{
// 		SetRootPath(strPath);
// 	}
// 	else
// 	{
// 		CString strTemp = strPath;
// 		strTemp += _P_FOLDER_PATH_SEPARATOR_;
// 		SetRootPath(strTemp);
// 	}
// 
// 	Search(&m_listFilePostFix, bTraveSubFolder);
// 
// 	YunSearch();
// 
// 	return 1;
}

long CXFileMngr::SetLibraryPath(const CString &strPath, BOOL bAddSubFiles, BOOL bAddSubFolders,BOOL bSearchSubFolders)
{
#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
    InitLocalCodec_BeforeReadWrite(strPath,&pOldTextCodec);
#endif
	m_pCurrSel = NULL;

	if (strPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
	{
		SetRootPath(strPath);
	}
	else
	{
		CString strTemp = strPath;
		CString strLast = strPath.Right(1);

		if (strLast == "/" || strLast == "\\")
		{
		}
		else
		{
			strTemp += _P_FOLDER_PATH_SEPARATOR_;
		}
		
		SetRootPath(strTemp);
	}

	Search(&m_listFilePostFix, bAddSubFiles,bAddSubFolders,bSearchSubFolders);

	YunSearch();
#ifdef _PSX_QT_LINUX_
	ResetLocalCodec(pOldTextCodec);

#endif
	return 1;
}

//2022-3-23  lijunqing add bAddFiles
void CXFileMngr::Research(BOOL bTraveSubFolder, BOOL bAddFiles) 
{
	m_pCurrSel = NULL;
	DeleteAll();
	Search(&m_listFilePostFix, bTraveSubFolder, bAddFiles);

	YunSearch();
}

void CXFileMngr::YunSearch()
{
#ifdef _Use_YUN_Client_
	//从云端获取文件
	if (Yun_IsLoginSucc())
	{
// 		CXFileTypes *pXFileTypes = GetXFileTypes();
// 		CExBaseList listPostfix;
// 		pXFileTypes->GetAllFilePostfix(listPostfix);
// 
// 		Yun_Search(this, listPostfix, TRUE);
// 		listPostfix.RemoveAll();
		Yun_Search(this, m_listFilePostFix, TRUE);
	}

#endif
}

long CXFileMngr::InitLibraryPath()
{
	CString strLibrary;
	strLibrary = _P_GetLibraryPath();

	long nRet =  SetLibraryPath(strLibrary);
	Filter(_T(""), FILTERMODE_CLEAR);
	
	return nRet;
}

CXFile* CXFileMngr::GetCurrSelFile()
{
	if (m_pCurrSel == NULL)
	{
		return NULL;
	}

	if (m_pCurrSel->GetClassID() == CLASSID_XFILE)
	{
		return (CXFile*)m_pCurrSel;
	}
	else
	{
		return NULL;
	}
}

CXFolder* CXFileMngr::GetCurrSelFolder()
{
	if (m_pCurrSel == NULL)
	{
		return NULL;
	}

	if (m_pCurrSel->GetClassID() != CLASSID_XFILE)
	{
		return (CXFolder*)m_pCurrSel;
	}
	else
	{
		return NULL;
	}
}


CXFolder* CXFileMngr::GetCurrFolder()
{
	if (m_pCurrSel == NULL)
	{
		return NULL;
	}

	if (m_pCurrSel->GetClassID() != CLASSID_XFILE)
	{
		return (CXFolder*)m_pCurrSel;
	}
	else
	{
		return (CXFolder*)(m_pCurrSel->GetParent());
	}
}

long CXFileMngr::DeleteFile(CXFile *pFile)
{
	if (m_pCurrSel == pFile)
	{
		m_pCurrSel = NULL;
	}

	if (m_pSrcFile == pFile)
	{
		m_pSrcFile = NULL;
	}

	CXFolder *pFolder = (CXFolder*)pFile->GetParent();
	return pFolder->DeleteFile(pFile);
}

void CXFileMngr::InitByXFileTypes()
{
	m_listFilePostFix.DeleteAll();
	m_oXFileTypes.InitXFilePostfix(m_listFilePostFix, m_bOnllySearchMainTypeFile);
}

void CXFileMngr::SetXFileTypes(CXFileTypes *pXFileTypes)
{
	m_oXFileTypes.DeleteAll();
	m_oXFileTypes.AppendClone(pXFileTypes);
}

void CXFileMngr::GetXFileDlgString(CString &strXFileFilter, CString &strXFilePostFix)
{
	m_oXFileTypes.GetXFileDlgString(strXFileFilter, strXFilePostFix);
}

BOOL CXFileMngr::ValidateFilePostfix(const CString &strFilePostfix)
{
	return m_oXFileTypes.ValidateFilePostfix(strFilePostfix);
}


void CXFileMngr::SearchFiles(const CString &strName, const CString &strPostfix, const CString &strPath, BOOL bTraveSubFolder)
{
	CXFileType *pXFileType = AddFileType(strName, strPostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(strName, strPostfix);
	SetOnllySearchMainTypeFile(TRUE);
	InitByXFileTypes();
	SetLibraryPath(strPath,bTraveSubFolder);
}

void CXFileMngr::OpenXFleTypesConfig(const CString &strFile)
{
	m_oXFileTypes.DeleteAll();
	m_oXFileTypes.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	InitByXFileTypes();
}

//////////////////////////////////////////////////////////////////////////
//yyj
#ifndef _PSX_IDE_QT_
LRESULT xfile_OnInitXFileMngrMenu(CMenu *pMenu, CExBaseObject *pXFileObj)
{
	UINT nClassID = pXFileObj->GetClassID();


#ifdef NOT_USE_XLANGUAGE
	if (CLASSID_XFILE == nClassID)
	{
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,_T("添加目录"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,_T("导入目录"));
		pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_COPY,_T("拷贝文件"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,_T("粘贴文件"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DELETE,_T("删除文件"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EDIT,_T("修改文件名称"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,_T("导入文件"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EXPORT,_T("导出文件"));
	}
	else if (nClassID == CLASSID_XFILEMNGR)
	{
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,_T("添加目录"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,_T("导入目录"));
		pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,_T("粘贴文件"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,_T("导入文件"));
	}
	else if (nClassID == CLASSID_XFOLDER)
	{
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,_T("添加目录"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_DELETE,_T("删除目录"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EDIT,_T("修改目录名称"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,_T("导入目录"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EXPORT,_T("导出目录"));
		pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,_T("粘贴文件"));
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,_T("导入文件"));
	}
#else
	if (CLASSID_XFILE == nClassID)
	{
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);
		pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_COPY,g_sLangTxt_CopyFile/*_T("拷贝文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_DELETE,g_sLangTxt_DeleteFile/*_T("删除文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EDIT,g_sLangTxt_FileRename/*_T("修改文件名称")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_EXPORT,g_sLangTxt_ExportFile/*_T("导出文件")*/);
	}
	else if (nClassID == CLASSID_XFILEMNGR)
	{
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);
		pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
	}
	else if (nClassID == CLASSID_XFOLDER)
	{
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_ADD,g_sLangTxt_AddDirectory/*_T("添加目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_DELETE,g_sLangTxt_DeleteDirectory /*_T("删除目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EDIT,g_sLangTxt_DirectoryRename/*_T("修改目录名称")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_IMPORT,g_sLangTxt_ImportDirectory/*_T("导入目录")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGR_FOLDER_EXPORT,g_sLangTxt_ExportDirectory/*_T("导出目录")*/);
		pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_PASTE,g_sLangTxt_PasteFile/*_T("粘贴文件")*/);
		pMenu->AppendMenu(MF_STRING,XFID_XFILEMNGRFILE_IMPORT,g_sLangTxt_ImportFile/*_T("导入文件")*/);
	}
#endif


	return 0;
}
#endif

void xfile_InsertToTreeCtrl(CExBaseObject *pFileBase, CTreeCtrl *pTreeCtrl, HTREEITEM hParent);

void xfile_InsertToTreeCtrl(CExBaseList *pFileList, CTreeCtrl *pTreeCtrl, HTREEITEM hParent)
{
	POS pos = pFileList->GetHeadPosition();
	CExBaseObject *pFileBase = NULL;

	while (pos != NULL)
	{
		pFileBase = (CExBaseObject *)pFileList->GetNext(pos);
		xfile_InsertToTreeCtrl(pFileBase, pTreeCtrl, hParent);
	}
}

void xfile_InsertToTreeCtrl(CExBaseObject *pFileBase, CTreeCtrl *pTreeCtrl, HTREEITEM hParent)
{
	UINT nImage = xfile_GetImageIndex(pFileBase);

	HTREEITEM hItem = pTreeCtrl->InsertItem(pFileBase->m_strName, nImage, nImage +1, hParent);
	pFileBase->m_dwItemData = (DWORD)hItem;
	pTreeCtrl->SetItemData(hItem, (DWORD)pFileBase);

	if (xfile_IsFolder(pFileBase->GetClassID()))
	{
		xfile_InsertToTreeCtrl((CExBaseList*)pFileBase, pTreeCtrl, hItem);
	}	
}



void xfile_InsertChildrenToTreeCtrl(CXFileMngr *pFileMngr, CTreeCtrl *pTreeCtrl)
{
	xfile_InsertToTreeCtrl((CExBaseList*)pFileMngr, pTreeCtrl, TVI_ROOT);
}

void xfile_InsertToTreeCtrl(CXFileMngr *pFileMngr, CTreeCtrl *pTreeCtrl)
{
	xfile_InsertToTreeCtrl((CExBaseObject*)pFileMngr, pTreeCtrl, TVI_ROOT);
}


CXFileMngr* xfile_GetXFileMngr(CExBaseObject *pXFileObj)
{
	CBaseObject *pAncestor = NULL;
	CXFileMngr *pAncestorFind = NULL;

	pAncestor = pXFileObj;//m_pParent;

	while (pAncestor != NULL)
	{
		if (CLASSID_XFILEMNGR == (CLASSID_XFILEMNGR & pAncestor->GetClassID()) )
		{
			pAncestorFind = (CXFileMngr*)pAncestor;
			break;
		}

		pAncestor = pAncestor->GetParent();
	}

	return pAncestorFind;
}


long xfile_GetAllFiles(CXFile *pXFile, CStringArray &astrFiles)
{
	CXFileMngr *pXFileMngr = xfile_GetXFileMngr(pXFile);//(CXFileMngr*)pXFile->GetAncestor(CLASSID_XFILEMNGR);
	ASSERT (pXFileMngr != NULL);
	CXFileTypes *pXFileTypes = pXFileMngr->GetXFileTypes();
	CXFileType *pXFileType = pXFileTypes->FindFileType(pXFile);
	CString strFile;
	strFile = pXFile->GetTotalFileName();

	if (pXFileType == NULL)
	{
		astrFiles.Add(strFile);
		return 1;
	}

	POS pos =  pXFileType->GetHeadPosition();
	CXFileTypePostfix *p = NULL;

	while (pos != NULL)
	{
		p = (CXFileTypePostfix *)pXFileType->GetNext(pos);
		strFile = ChangeFilePostfix(strFile, p->m_strID);
		astrFiles.Add(strFile);
	}

	return astrFiles.GetCount();
}

long xfile_GetAllFiles(CXFolder *pXFolder, CStringArray &astrFiles)
{
	POS pos = pXFolder->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pXFolder->GetNext(pos);

		if (xfile_IsFolder(p->GetClassID()))
		{
			xfile_GetAllFiles((CXFolder*)p, astrFiles);
		}
		else
		{
			xfile_GetAllFiles((CXFile*)p, astrFiles);
		}
	}

	return astrFiles.GetCount();
}

long xfile_TrimAllFiles(const CString &strRoot, CStringArray &astrFiles)
{
	long nCount = astrFiles.GetCount();
	long nIndex = 0;
	long nLenRoot = strRoot.GetLength();
	CString strFile;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strFile = astrFiles.GetAt(nIndex);
		strFile = strFile.Mid(nLenRoot);
		astrFiles.Add(strFile);
	}

	return astrFiles.GetSize();
}

BOOL xfile_SplitPath(const CString &strPath, CStringArray &astrName)
{
	astrName.RemoveAll();

	if (strPath.GetLength() == 0)
	{
		return FALSE;
	}

	CBufferBase oBuffer;
	oBuffer.InitBuffer(strPath);
	oBuffer.FormatBuffer('\\');
	oBuffer.FormatBuffer('/');

	CString strID;
	char *pTemp = oBuffer.GetString();

	while (oBuffer.IsPoiterInBuffer(pTemp))
	{
		strID = pTemp;
		astrName.Add(strID);
		pTemp = oBuffer.NextString();
	}

	return TRUE;
}

BOOL xfile_QueryAllFiles(CXFolder *pFolder, CStringArray &astrFiles,BOOL bAddFolder)
{
	CString strPath;
	POS pos = pFolder->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			if(bAddFolder)
			{
				strPath = ((CXFolder*)p)->GetRelativePath();
				strPath += _P_FOLDER_PATH_SEPARATOR_;
				astrFiles.Add(strPath);
			}
			
			xfile_QueryAllFiles((CXFolder*)p, astrFiles);
		}
		else
		{
			strPath = ((CXFile*)p)->GetRelativePath();
			astrFiles.Add(strPath);
		}
	}

	return TRUE;
}

CXFolder* xfile_SelectFolder_RelPath(CXFileMngr *pFileMngr, const CString &strRelPath)
{
	CStringArray astrID;
	xfile_SplitPath(strRelPath, astrID);

	return pFileMngr->SelectFolder(astrID, 0);
}

CXFile* xfile_SelectFile_RelPath(CXFileMngr *pFileMngr, const CString &strRelPath)
{
	CStringArray astrID;
	xfile_SplitPath(strRelPath, astrID);

	return pFileMngr->SelectFile(astrID);
}

BOOL xfile_filepath_has_key(const CString &strFilePath, const CStringArray &astrKeys)
{
	CString strTemp = strFilePath;
	strTemp.MakeLower();

	long nCount = astrKeys.GetCount();
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (strTemp.Find(astrKeys.GetAt(nIndex)) >= 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL xfile_filepath_has_keys(const CString &strFilePath, const CStringArray &astrKeys)
{
	CString strTemp = strFilePath;
	strTemp.MakeLower();

	long nCount = astrKeys.GetCount();
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (strTemp.Find(astrKeys.GetAt(nIndex)) < 0)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL xfile_QueryAllFiles_And(CXFolder *pFolder, const CStringArray &astrKeys, CStringArray &astrFiles)
{
	CString strPath;
	POS pos = pFolder->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			strPath = ((CXFolder*)p)->GetRelativePath();
			strPath += _P_FOLDER_PATH_SEPARATOR_;

			if (xfile_filepath_has_keys(strPath, astrKeys))
			{
				astrFiles.Add(strPath);
			}

			xfile_QueryAllFiles_And((CXFolder*)p, astrKeys, astrFiles);
		}
		else
		{
			strPath = ((CXFile*)p)->GetRelativePath();

			if (xfile_filepath_has_keys(strPath, astrKeys))
			{
				astrFiles.Add(strPath);
			}
		}
	}

	return TRUE;
}


BOOL xfile_QueryAllFiles_Or(CXFolder *pFolder, const CStringArray &astrKeys, CStringArray &astrFiles)
{
	CString strPath;
	POS pos = pFolder->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			strPath = ((CXFolder*)p)->GetRelativePath();
			strPath += _P_FOLDER_PATH_SEPARATOR_;

			if (xfile_filepath_has_key(strPath, astrKeys))
			{
				astrFiles.Add(strPath);
			}

			xfile_QueryAllFiles_Or((CXFolder*)p, astrKeys, astrFiles);
		}
		else
		{
			strPath = ((CXFile*)p)->GetRelativePath();

			if (xfile_filepath_has_key(strPath, astrKeys))
			{
				astrFiles.Add(strPath);
			}
		}
	}

	return TRUE;
}

long xfile_SelectAllFiles(CXFolder *pFolder, BOOL bHasSubFolder, CExBaseList &listFiles)
{
	POS pos = pFolder->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			if (bHasSubFolder)
			{
				xfile_SelectAllFiles((CXFolder*)p, bHasSubFolder, listFiles);
			}
		}
		else
		{
			listFiles.AddTail(p);
		}
	}

	return listFiles.GetCount();
}

long xfile_SelectAllFiles(CXFolder *pFolder, const CString &strPostfix, CExBaseList &listFiles)
{
	POS pos = pFolder->GetHeadPosition();
	CExBaseObject *p = NULL;
	CString strTemp;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			xfile_SelectAllFiles((CXFolder*)p, strPostfix, listFiles);
		}
		else
		{
			strTemp = ParseFilePostfix(p->m_strID);
			strTemp.MakeLower();

			if (strTemp == strPostfix)
			{
				listFiles.AddTail(p);
			}
		}
	}

	return listFiles.GetCount();
}

long xfile_SelectAllFilesCount(CXFolder *pFolder, const CString &strPostfix)
{
	POS pos = pFolder->GetHeadPosition();
	CExBaseObject *p = NULL;
	CString strTemp;
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			continue;	
		}

		if (strPostfix.IsEmpty())
		{
			nCount++;
		}
		else
		{
			strTemp = ParseFilePostfix(p->m_strID);

			if (strPostfix.CompareNoCase(strTemp) == 0)
			{
				nCount++;
			}
		}
	}

	return nCount;
}
