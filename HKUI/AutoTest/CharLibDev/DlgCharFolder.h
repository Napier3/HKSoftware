#pragma once
#include "afxwin.h"

#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\XLanguage\XLanguageButton.h"
// CDlgCharFolder 对话框

class CDlgCharFolder : public CDialog
{
	DECLARE_DYNAMIC(CDlgCharFolder)

public:
	CDlgCharFolder(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCharFolder();
	CExBaseList *m_pParentFolder;
	CExBaseObject *m_pCurrEdit;

	void xlang_InitAndAdjust();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHARDOLDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	afx_msg void OnEnChangeEditName();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CXLanguageButton m_btnCancel;
	CXLanguageButton m_btnOK;
	CXLanguageTextWnd m_wndFolderName;
	CEdit m_edtFolderName;
};
