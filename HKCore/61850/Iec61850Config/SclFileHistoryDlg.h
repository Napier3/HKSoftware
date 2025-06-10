#pragma once
#include "afxwin.h"


#include "..\..\Module\XLanguage\XLanguageButton.h" //2016.10.14

// CSclFileHistoryDlg �Ի���

class CSclFileHistoryDlg : public CDialog
{
	DECLARE_DYNAMIC(CSclFileHistoryDlg)

public:
	CSclFileHistoryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSclFileHistoryDlg();
	CString m_strSclFile;

	void xlang_InitAndAdjust();//2016.10.14

// �Ի�������
	enum { IDD = IDD_DLG_SCL_FILE_HIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void EnableOKButton();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_listSclFileHis;
	CXLanguageButton m_btnOK;    //003   20161014
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnLbnSelchangeListSclHis();
	afx_msg void OnLbnDblclkListSclHis();
	afx_msg void OnBnClickedButtonDelete();
	CXLanguageButton m_btnDelete;    //002   20161014
	CXLanguageButton m_btnIecBrowse;  //001   20161014
	CXLanguageButton m_btnIecCancel;   //004   20161014
};
