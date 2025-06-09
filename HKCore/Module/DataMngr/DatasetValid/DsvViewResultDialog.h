#pragma once

#include "afxwin.h"
#include "afxcmn.h"

#include "..\..\DialogBase\DynDialogEx.h"
#include "DsvViewScriptTreeCtrl.h"
#include "DsvViewDatasetGrid.h"
// CDsvViewResultDialog 对话框

#define IDC_TREE_DSV_VIEW   0x12257
#define IDC_LIST_DSV_VIEW   0x12258

class CDsvViewResultDialog : public CDynDialogEx
{
// 	DECLARE_DYNAMIC(CDsvViewResultDialog)

public:
	CDsvViewResultDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDsvViewResultDialog();
	
	CDsvScript *m_pDsvScript;
	CDvmDataset *m_pDsvDataset;
	void ViewDsvScriptResult(CDsvScript *pDsvScript, CDvmDataset *pDsvDataset);
	void SetImageList(UINT nImageList)	{	m_nImageList = nImageList;	}

private:
	UINT m_nImageList;

	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CXMatchRefObjectSelDlg) 
public: 
	virtual int DoModal(); 
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_VIRTUAL 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDsvViewScriptTreeCtrl m_treeDataset;
	CDsvViewDatasetGrid    m_listDataset;
	CButton m_btnOK;
	afx_msg void OnTvnSelchangedTreeDataset(NMHDR *pNMHDR, LRESULT *pResult);
};
