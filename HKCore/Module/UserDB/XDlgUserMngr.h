#pragma once
#include "afxcmn.h"

#include "..\..\Module\BaseClass\ExBaseListListCtrl.h"
#include "afxwin.h"

class CXUserListCtrl : public CExBaseListListCtrl
{
public:
	CXUserListCtrl();
	virtual ~CXUserListCtrl();

public:
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);

};

// CXDlgUserMngr 对话框

class CXDlgUserMngr : public CDialog
{
	DECLARE_DYNAMIC(CXDlgUserMngr)

public:
	CXDlgUserMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXDlgUserMngr();
	CXUser *m_pCurrSelUser;
	long   m_nCurrSelUser;

	void EnableButtons();

// 对话框数据
	enum { IDD = IDD_DIALOG_USERMNGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnLvnItemchangedListUsermngr(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CXUserListCtrl m_listUserMngr;
	afx_msg void OnNMDblclkListUsermngr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListUsermngr(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_btnEdit;
	CButton m_btnDelete;
};
