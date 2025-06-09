#pragma once

// CXFileMngrDoc 文档
#include "..\..\Module\XfileMngrBase\XFileMngr.h"

class CXFileMngrDoc : public CDocument, public CXFileOptrMsgRcvWnd
{
	DECLARE_DYNCREATE(CXFileMngrDoc)

public:
	virtual BOOL XCopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists);
	virtual DWORD XOpenXFile(CXFile *pFile);
	virtual DWORD XDeleteXFile(CXFile *pFile);
	virtual DWORD XDeleteXFolder(CXFolder *pFolder);
	virtual DWORD XEditXFile(CXFile *pFile, const CString &strDestName);
	virtual DWORD XCanEditXFolder(CXFolder *pFolder);
	virtual UINT GetImgIndex(CExBaseObject *pObj);
	virtual DWORD XDownLoad(CExBaseObject *pXFileObj);
	virtual DWORD XUpload(CExBaseObject *pXFileObj);

public:
	CXFileMngrDoc();
	virtual ~CXFileMngrDoc();
	CXFileMngr *m_pXFileMngr;

#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // 为文档 I/O 重写
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
