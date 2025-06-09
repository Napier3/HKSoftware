// XMatchDatasetSelDlg.h: interface for the CXMatchDatasetSelDlg class. 
// 
////////////////////////////////////////////////////////////////////// 

#if !defined(_XMatchDatasetSelDlg_H__) 
#define _XMatchDatasetSelDlg_H__ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 

#include "..\DialogBase\DynDialogEx.h" 
#include "KeyDbGlobal.h"

class CXMatchDatasetSelDlg : public CDynDialogEx   
{ 
public: 
	CXMatchDatasetSelDlg(CXMatchRefObjectSelEdit *pEdit, CWnd* pParent = NULL); 
	virtual ~CXMatchDatasetSelDlg(); 

	CTreeCtrl m_treeDataset; 
	CXMatchRefObjectSelEdit *m_pEdit;
	CExBaseList m_oListDataset;

	void ResetDatasetList();
	void AddDataset(CExBaseObject *pDataset, BOOL bAddToTree=TRUE);
	void ShowDatasetTree();
	CExBaseObject* GetSelectDataObject();
	void SelectData(CExBaseObject *pData);

protected:
	void InsertDataset(CExBaseList *pDataset, HTREEITEM hParent);
	HTREEITEM FindDataItem(CExBaseObject *pData, HTREEITEM hParent);

	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CXMatchDatasetSelDlg) 
public: 
	virtual int DoModal(); 
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_VIRTUAL 

	// Implementation 
protected: 

	// Generated message map functions 
	//{{AFX_MSG(CXMatchDatasetSelDlg) 
	virtual BOOL OnInitDialog(); 
	afx_msg void OnNMDblclkTreeDataset(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 

class CXMatchDataObjEditDlg : public CDynDialogEx   
{ 
public: 
	CXMatchDataObjEditDlg(CWnd* pParent = NULL); 
	virtual ~CXMatchDataObjEditDlg(); 

	CEdit m_editValue;
	CButton m_btnOK;
	CButton m_btnCancel;

	CString m_strValue;
	CString m_strDataName;

protected:
	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CXMatchDatasetSelDlg) 
public: 
	virtual int DoModal(); 
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_VIRTUAL 

	// Implementation 
protected: 

	// Generated message map functions 
	//{{AFX_MSG(CXMatchDatasetSelDlg) 
	virtual BOOL OnInitDialog(); 
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 

#endif // !defined(_XMatchDatasetSelDlg_H__) 
