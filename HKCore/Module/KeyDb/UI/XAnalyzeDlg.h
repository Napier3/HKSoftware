#pragma once
#include "afxwin.h"
#include "XKeyDBUiGlobal.h"


// CBaseKeyDlg �Ի���

class CXAnalyzeDlg : public CDynDialogEx
{
	DECLARE_DYNAMIC(CXAnalyzeDlg)

public:
	CXAnalyzeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXAnalyzeDlg();
	// 
	// 	// �Ի�������
	// 	enum { IDD = IDD_KEYBASE_DIALOG };

	virtual BOOL OnInitDialog();
	void CreateControls();
	virtual int DoModal();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnSave;
	afx_msg void OnBnClickedBtnBasekeySave();
};


