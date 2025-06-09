#pragma once
#include "afxwin.h"
#include "..\..\Module\DialogBase\DynDialogEx.h"
#include "..\GuideBook\GuideBook.h"

#define IDC_GBSELDLG_TREE_ITEMS    5410

class CXSelectItemsDlg : public CDynDialogEx
{
	DECLARE_DYNAMIC(CXSelectItemsDlg)

public:
	CXSelectItemsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXSelectItemsDlg();

	CGbItemBase *m_pTestItem;
	CExBaseObject *m_pCurrSelObj;

	virtual BOOL OnInitDialog();
	virtual void CreateControls();
	virtual int DoModal();
	virtual void OnOK();
	virtual void OnCancel();

	virtual void CreateOKCancel(long nTopPos);
	
	CTreeCtrl m_treeItemsAncester;
	CButton   m_btnOK;
	CButton   m_btnCancel;

	virtual void EnableButtons();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchangedTreeItems(NMHDR *pNMHDR, LRESULT *pResult);

};


