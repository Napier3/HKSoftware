#pragma once

#include "../../../iSmartTestWzd/Resource.h"
#include "../StepCtrl/UIDrawer.h"

// CWzd_FailItemAdviseDlg �Ի���

class CWzd_FailItemAdviseDlg : public CUIDialog
{
	DECLARE_DYNAMIC(CWzd_FailItemAdviseDlg)
private:
	CUIButton m_btnOK;
	CUIButton m_btnCancel;
	CStatic m_txtAdvise;

public:
	CWzd_FailItemAdviseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWzd_FailItemAdviseDlg();

// �Ի�������
	enum { IDD = IDD_FAIL_ITEM_ADVISE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	void InitFailItemAdvise(CString strAdvise = "");

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

private:
	CString m_strAdvise;
};
