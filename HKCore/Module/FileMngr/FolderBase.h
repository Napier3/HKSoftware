#pragma once

#include "FileBase.h"
#include "../BaseClass/ExBaseList.h"
#include "../api/FileApi.h"

#define FIND_MODE_ALL    0
#define FIND_MODE_FOLDER 1
#define FIND_MODE_FILE   2

class CFileMngrBase;

class CFolderBase : public CExBaseList
{
public:
	CFolderBase();
	virtual ~CFolderBase();

// Ù–‘
protected:
	CString m_strPath;
	
public:
	virtual UINT GetClassID()										{		return CLASSID_FOLDER_BASE;		}
	virtual BSTR GetXmlElementKey()					{		return g_strFolderKey;							}
	
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	BOOL CheckFileExist();
	BOOL IsFolderExist();

	virtual CString GetFolderPath();
	virtual CString GetPath()		{	return GetFolderPath();		}

	virtual CFileBase* AddFile(CExBaseObject* pNode,const CString& strFileName,/*const CString& strFileType,*/BOOL bOverWrite);
	//virtual CFileBase* AddFile(CGuideBook* pGuideBook,const CString& strFileName,const CString& strFileType,BOOL bOverWrite);
	virtual CFolderBase* AddFolder(const CString &strFolderName, BOOL bCreateFolder=TRUE);
	
	BOOL GetFolderModifyTime(CString& strModifyTime);
	CExBaseObject* FindByLowerName(CString strFolderName);

	virtual BOOL DeleteAllInFolder();
	virtual BOOL RenameFolder(const CString &strNewName);

	BOOL CheckFileOpen();
	BOOL CheckFileOpenChildren(CFolderBase* pFolder);

	CFileBase* SelectFile(const CString &strFile, BOOL bUseFullPath=FALSE);
	CFileBase* SelectFileInCurrFolder(const CString &strFile, BOOL bUseFullPath=FALSE);
	CFileBase* SelectFileInSubFolder(const CString &strFile, BOOL bUseFullPath=FALSE);

	CFolderBase* SelectFolder(const CString &strFolder, BOOL bUseFullPath=FALSE);
	CFolderBase* SelectFolderInCurrFolder(const CString &strFolder, BOOL bUseFullPath=FALSE);
	CFolderBase* SelectFolderInSubFolder(const CString &strFolder, BOOL bUseFullPath=FALSE);
};