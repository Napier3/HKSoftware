#pragma once
#include "afxwin.h"
#include "XSelectItemsDlg.h"

#define IDC_GBSELDLG_COMBO_MODE   5411

class CXItemReplaceSelectDlg : public CXSelectItemsDlg
{
	DECLARE_DYNAMIC(CXItemReplaceSelectDlg)

public:
	CXItemReplaceSelectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXItemReplaceSelectDlg();

	virtual BOOL OnInitDialog();
	virtual void CreateControls();
	virtual int DoModal();
	virtual void OnOK();
	virtual void OnCancel();

	CComboBox m_cmbMode;
	long      m_nMode;

protected:

public:
	
};


