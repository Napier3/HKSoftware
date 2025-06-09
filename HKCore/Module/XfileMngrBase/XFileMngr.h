#pragma once

#include "XFolder.h"
#include "XFileTypes.h"

CXFile* FindFileBaseByName(const CString& strFileName,CXFolder* pFolder,CXFolder* &pFolderFind);

class CXFileMngr : public CXFolder
{
public:
	CXFileMngr();
	virtual ~CXFileMngr();

	virtual void InitYunRootFolder(CDataGroup *pDestGroup);

public:
	CString m_strRootPath;
	CString m_strYunRootPath;

private:
	CXFile *m_pSrcFile;
	CExBaseObject *m_pCurrSel;
	BOOL   m_bOnllySearchMainTypeFile;
	CTreeCtrl *m_pRefTreeCtrl;
	CDataGroup *m_pYunRootFolder;

public:
	void SetRootPath(const CString& strRootPath)	{		m_strRootPath = strRootPath;	m_strPath = strRootPath;		}
	CString GetRootPath()			{		return m_strRootPath;		}

public:
	virtual UINT GetClassID()		{		return CLASSID_XFILEMNGR;		}
	
	CExBaseObject* GetCurrSel()				{	return m_pCurrSel;	}
	void SetCurrSel(CExBaseObject *pSel)	{	m_pCurrSel = pSel;	}
	CXFile* GetCopySrcFile()			{	return m_pSrcFile;	}
	BOOL CopyFile();
	long SetLibraryPath(const CString &strPath, BOOL bTraveSubFolder=TRUE);
	long SetLibraryPath(const CString &strPath, BOOL bAddSubFiles, BOOL bAddSubFolders,BOOL bSearchSubFolders);//20220702 zhouhj 是否添加子文件、是否添加子文件夹、是否检索子文件夹
	long InitLibraryPath();
	void Research(BOOL bTraveSubFolder=TRUE, BOOL bAddFiles = TRUE); ////2022-3-23  lijunqing add bAddFiles
	void YunSearch();

	CXFile* GetCurrSelFile();
	CXFolder* GetCurrSelFolder();
	CXFolder* GetCurrFolder();

	long DeleteFile(CXFile *pFile);
	void SetOnllySearchMainTypeFile(BOOL  b)	{	m_bOnllySearchMainTypeFile = b;	}
	void SetRefCtrrCtrl(CTreeCtrl *pTreeCtrl)	{	m_pRefTreeCtrl = pTreeCtrl;		}
	CTreeCtrl* GetRefTreeCtrl()					{	return m_pRefTreeCtrl;			}
// #ifdef _PSX_QT_LINUX_
// 	void SetUseUtf8TextCodec(BOOL bUse){m_bUseUtf8TextCodec = bUse;}
// #endif

private:
	CExBaseList m_listFilePostFix;
	CXFileTypes m_oXFileTypes;
// #ifdef _PSX_QT_LINUX_
// 	BOOL m_bUseUtf8TextCodec;//20230513 zhouhj 在机器内,U盘存储空间内采用gbk编码,设备内部存储空间采用utf8编码,增加此标记
// #endif

public:
// 	void AddFileType(const CString &strName, const CString &strPostFix)
// 	{
// 		m_listFilePostFix.AddNew(strName, strPostFix);
// 	}

	CExBaseList* GEtFilePostfixList()	{	return &m_listFilePostFix;	}
	void InitByXFileTypes();
	CXFileTypes* GetXFileTypes()		{	return &m_oXFileTypes;		}
	void SetXFileTypes(CXFileTypes *pXFileTypes);
	void GetXFileDlgString(CString &strXFileFilter, CString &strXFilePostFix);
	BOOL ValidateFilePostfix(const CString &strFilePostfix);
	CXFileType* AddFileType(const CString &strName, const CString &strID, const CString &strExe, const CString &strRunMode)
	{	
		return m_oXFileTypes.AddFileType(strName, strID, strExe, strRunMode);	
	}
	
	void SearchFiles(const CString &strName, const CString &strPostfix, const CString &strPath, BOOL bTraveSubFolder=TRUE);

	void OpenXFleTypesConfig(const CString &strFile);

public:
	virtual BOOL XCopyFile(CXFile *pSrcFile, CXFolder *pFolder, BOOL bFailIfExists)
	{
		return m_oXFileTypes.XCopyFile(pSrcFile, pFolder, bFailIfExists);
	}
	virtual BOOL XImportFile(const CString &strFile, CXFolder *pFolder, BOOL bFailIfExists)
	{
		return m_oXFileTypes.XImportFile(strFile, pFolder, bFailIfExists);
	}

	virtual BOOL XCopyFile(CXFile *pSrcFile, const CString &strFolder, BOOL bFailIfExists)
	{
		return m_oXFileTypes.XCopyFile(pSrcFile, strFolder, bFailIfExists);
	}

	virtual BOOL XOpenXFile(CXFile *pFile)
	{
		return m_oXFileTypes.XOpenXFile(pFile);
	}

	virtual BOOL XDeleteXFile(CXFile *pFile)
	{
		BOOL b = m_oXFileTypes.XDeleteXFile(pFile);

		return b;
	}

	virtual BOOL XEditXFile(CXFile *pFile, const CString &strDestName)
	{
		return m_oXFileTypes.XEditXFile(pFile, strDestName);
	}

	CXFileType* FindFileType(CXFile *pSrcFile)				{	return m_oXFileTypes.FindFileType(pSrcFile);		}
	CXFileType* FindFileType(const CString &strFilePostfix)	{	return m_oXFileTypes.FindFileType(strFilePostfix);	};

};

//yyj
#ifndef _PSX_IDE_QT_ 
LRESULT xfile_OnInitXFileMngrMenu(CMenu *pMenu, CExBaseObject *pXFileObj);
#endif

void xfile_InsertChildrenToTreeCtrl(CXFileMngr *pFileMngr, CTreeCtrl *pTreeCtrl);
void xfile_InsertToTreeCtrl(CXFileMngr *pFileMngr, CTreeCtrl *pTreeCtrl);
CXFileMngr* xfile_GetXFileMngr(CExBaseObject *pXFileObj);
long xfile_GetAllFiles(CXFile *pXFile, CStringArray &astrFiles);
long xfile_GetAllFiles(CXFolder *pXFolder, CStringArray &astrFiles);
long xfile_TrimAllFiles(const CString &strRoot, CStringArray &astrFiles);

BOOL xfile_SplitPath(const CString &strPath, CStringArray &astrName);
BOOL xfile_QueryAllFiles(CXFolder *pFolder, CStringArray &astrFiles,BOOL bAddFolder = TRUE);
CXFolder* xfile_SelectFolder_RelPath(CXFileMngr *pFileMngr, const CString &strRelPath);
CXFile* xfile_SelectFile_RelPath(CXFileMngr *pFileMngr, const CString &strRelPath);
BOOL xfile_QueryAllFiles_And(CXFolder *pFolder, const CStringArray &astrKeys, CStringArray &astrFiles);
BOOL xfile_QueryAllFiles_Or(CXFolder *pFolder, const CStringArray &astrKeys, CStringArray &astrFiles);
long xfile_SelectAllFiles(CXFolder *pFolder, BOOL bHasSubFolder, CExBaseList &listFiles);
long xfile_SelectAllFiles(CXFolder *pFolder, const CString &strPostfix, CExBaseList &listFiles);
long xfile_SelectAllFilesCount(CXFolder *pFolder, const CString &strPostfix);
