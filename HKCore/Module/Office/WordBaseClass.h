// WordBaseClass.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_WORDBASECLASS_H__)
#define _WORDBASECLASS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "msword9.h"

class CWordDocBase
{
public:
	CWordDocBase(MSWord::_Application &oWordApp);
	CWordDocBase();
	virtual ~CWordDocBase();
	
public:
	virtual long New(const CString &strTemplateFile, const CString &strWordFile, BOOL bAdjust=FALSE);
	virtual long New(const CString &strWordFile, BOOL bAdjust=FALSE);
	virtual BOOL Open(const CString  &strWordFile, BOOL bAdjust=FALSE);
	virtual long Save();
	virtual long SaveAs(const CString  &strWordFile);
	virtual long Close(long nSave);

	//用于调整试验报告界面与主程序界面的布局
	virtual void SetParentWnd(CWnd* pParentWnd)		{		m_pParentWnd = pParentWnd;	}
	virtual CWnd* GetWordMainWnd()							{		return NULL;								}
	
protected:
	MSWord::_Application m_WordApp;
	MSWord::_Document m_oDoc;
	HWND m_hWordWnd;

	//WORD的父窗口
	CWnd* m_pParentWnd;
	HWND m_hParentWnd;

	BOOL AddNewReport(const CString &strRptTmplFile);
	BOOL CloseWordDocWindow();

public:
	void AdjustWordWindow();
	MSWord::_Document GetDoc()		{		return m_oDoc;		}
};

class CWordAppBase
{
public:
	CWordAppBase(MSWord::_Application &oWordApp);
	CWordAppBase();
	virtual ~CWordAppBase();

public:
	virtual MSWord::_Application GetWordApp(BOOL bVisible=FALSE);
	virtual BOOL CloseWordApplication();

	virtual CWordDocBase* CreateWordDocBase();

protected:
	MSWord::_Application m_WordApp;
	BOOL m_bIsAppRef;
};


#endif // !defined(_WORDBASECLASS_H__)
