#pragma once

#include "afxwin.h"
#include "afxcmn.h"

#include "..\..\..\Module\DialogBase\DynDialogEx.h"
#include "DvmDatasetTreeCtrl.h"
// CViewSetsDialog �Ի���

#define IDC_TREE_DATASET_EX   0x12257
#define IDC_LIST_DATASET_EX   0x12258

class CViewSetsDialog : public CDynDialogEx
{
// 	DECLARE_DYNAMIC(CViewSetsDialog)

public:
	CViewSetsDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CViewSetsDialog();
	CExBaseObject *m_pDevice;
	
	void ShowDataset(CDataSet *pDataset);

	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CXMatchRefObjectSelDlg) 
public: 
	virtual int DoModal(); 
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_VIRTUAL 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDvmDatasetTreeCtrl m_treeDataset;
	CListCtrl m_listDataset;
	CButton m_btnOK;
	afx_msg void OnTvnSelchangedTreeDataset(NMHDR *pNMHDR, LRESULT *pResult);
};
