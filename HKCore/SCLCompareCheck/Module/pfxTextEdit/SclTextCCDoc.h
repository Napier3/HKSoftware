#pragma once
#include "pfx\pfxeditctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSclTextCCDoc ÎÄµµ
class CSclTextCCDoc : public CPfxEditDoc
{
	DECLARE_DYNCREATE(CSclTextCCDoc)

public:
	CPfxEditTypeInfo * m_pPfxEditTypeInfo;//zhow
	BOOL m_bDircClose;

protected:
	CSclTextCCDoc();
	virtual        ~CSclTextCCDoc();

public:
        BOOL           GetSaveAsFileName(CString& fileName,
                               BOOL bReplace,
                               LONG& nFileConverter,
                               LONG& nLineBreakType);
        

protected:
	virtual BOOL   SaveModified(); // return true if ok to continue
        virtual void   SetModifiedFlag(BOOL bModified);
        virtual BOOL   DoSave(LPCTSTR pszPathName, BOOL bReplace = true);
        virtual LONG   OnEvent(UINT nCode, LPARAM lParam);
        virtual BOOL   OnInitDocument(LPCTSTR pszPathName);
		virtual BOOL   OnOpenDocument(LPCTSTR pszPathName);

protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
//	virtual BOOL OnNewDocument();
};
