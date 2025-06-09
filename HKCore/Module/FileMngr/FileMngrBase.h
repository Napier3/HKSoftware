#pragma once

#include "FolderBase.h"

CFileBase* FindFileBaseByName(const CString& strFileName,CFolderBase* pFolder,CFolderBase* &pFolderFind);

class CFileMngrBase : public CFolderBase
{
public:
	CFileMngrBase();
	virtual ~CFileMngrBase();

public:
	CString m_strRootPath;
	CString m_strMngrFileName;

public:
	BSTR m_strFileKey;
	BSTR m_strFolderKey;

	virtual UINT GetClassID()		{		return CLASSID_FOLDER_BASE;		}
	
	void SetRootPath(const CString& strRootPath)				{		m_strRootPath = strRootPath;		}
	CString GetRootPath()																	{		return m_strRootPath;		}

	virtual BOOL SaveXMLFile();
	virtual BOOL OpenXMLFile();
	virtual void Traverse(const CString& strPath,const CString& strFilePostFix/*,const CString& strFileType*/, BOOL bTraveSubFolder=TRUE);
};

void file_InsertChildrenToTreeCtrl(CFileMngrBase *pFileMngr, CTreeCtrl *pTreeCtrl);
void file_InsertToTreeCtrl(CFileMngrBase *pFileMngr, CTreeCtrl *pTreeCtrl);
