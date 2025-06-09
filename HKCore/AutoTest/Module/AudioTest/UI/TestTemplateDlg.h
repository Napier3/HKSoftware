#pragma once
#include "../../../AudioTest/resource.h"
#include "AudioDlgBase.h"
#include "ListCtrlEx.h"
// CTestTemplateDlg 对话框
class CTestTemplateDlg : /*public CDialog,*/public CAudioDlgBase
{
	DECLARE_DYNAMIC(CTestTemplateDlg)

public:
	CTestTemplateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestTemplateDlg();
	enum { IDD = IDD_DIALOG_TESTTEMPLATE };
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);

protected:

	DECLARE_MESSAGE_MAP()
public:
	void UpdateList(CString strID);

public:
	//CListCtrl m_ListCtrl_TestTemplate;
	CListCtrlEx m_ListCtrl_TestTemplate;

	CFont m_font;
	CStatic m_static;
	CString		m_strCurrentTempId;
};


