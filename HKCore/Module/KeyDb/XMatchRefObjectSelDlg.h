// XMatchRefObjectSelDlg.h: interface for the CXMatchRefObjectSelDlg class. 
// 
////////////////////////////////////////////////////////////////////// 

#if !defined(_XMatchRefObjectSelDlg_H__) 
#define _XMatchRefObjectSelDlg_H__ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 

#include "..\DialogBase\DynDialogEx.h" 

#include "KeyDbGlobal.h"

class CXMatchRefObjectSelDlg : public CDynDialogEx   
{ 
public: 
	CXMatchRefObjectSelDlg(CXMatchRefObjectSelEdit *pEdit, CWnd* pParent = NULL); 
	virtual ~CXMatchRefObjectSelDlg(); 

	CListBox m_lstBox; 
	CXMatchRefObjectSelEdit *m_pEdit;
	void ShowExBaseList(CExBaseList *pListDatas, BOOL bAddEmpty=FALSE, BOOL bShowID=FALSE);

	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CXMatchRefObjectSelDlg) 
public: 
	virtual int DoModal(); 
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_VIRTUAL 

	// Implementation 
protected: 

	// Generated message map functions 
	//{{AFX_MSG(CXMatchRefObjectSelDlg) 
	virtual BOOL OnInitDialog(); 
	afx_msg void OnDblclkList(); 
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 

#endif // !defined(_XMatchRefObjectSelDlg_H__) 
