#pragma once

#include "XKeyDBUiGlobal.h"



class CXMultiKeyDlg : public CXKeyEditDlgBase
{
	DECLARE_DYNAMIC(CXMultiKeyDlg)

public:
	CXMultiKeyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXMultiKeyDlg();

	int m_nCurrSelIndex;
	CExBaseObject *m_pKey;
	CExBaseObject *m_pMultiKeyBase;

	//操作
	void ShowMultiKeyList();

	virtual BOOL OnInitDialog();
	void CreateControls();

	virtual int DoModal();
	virtual void OnCancel(){};
	virtual void OnOK(){};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnSave;
	CButton m_btnInsert;
	CButton m_btnDelete;
	CButton m_btnCancle;

	CListCtrl m_listMultiKey;

	CEdit m_editName;
	CEdit m_editID;
	CEdit m_editKeyBase;

	CString m_strName;
	CString m_strID;
	CString m_strKeyBase;

	CStatic m_NameStatic;
	CStatic m_IDStatic;
	CStatic m_BaseKeyStatic;

	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnInsert();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnCancle();

	afx_msg void OnDestroy();
	afx_msg void OnNMClickListMultikey(NMHDR *pNMHDR, LRESULT *pResult);
};

