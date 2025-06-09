#pragma once
#include "afxwin.h"
#include "..\..\Module\DialogBase\DynDialogEx.h"
#include "GbItemBase.h"

// CBaseKeyDlg �Ի���

class CXScriptEditDlg : public CDynDialogEx
{
	DECLARE_DYNAMIC(CXScriptEditDlg)

public:
	CXScriptEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXScriptEditDlg();

	CGbItemBase *m_pGbItemBase;

	virtual BOOL OnInitDialog();
	void CreateControls();
	virtual int DoModal();
	virtual void OnOK();
	virtual void OnCancel();

	CEdit m_editScript;
	CButton   m_btnOK;
	CButton   m_btnCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


