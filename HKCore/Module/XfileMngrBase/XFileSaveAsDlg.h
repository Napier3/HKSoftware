#pragma once
#include "afxwin.h"

#include "XFileDlgDefine.h"
#include "XFolderTreeCtrl.h"
#include "XFileMngr.h"
#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\Xlanguage\XLanguageButton.h"

// CXFileSaveAsDlg 对话框

class CXFileSaveAsDlg : public CDynDialogEx
{
	//DECLARE_DYNAMIC(CXFileSaveAsDlg)

public:
	CXFileSaveAsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXFileSaveAsDlg();
	CString GetXFilePath();
	CString GetXFile();
	CString m_strXFilePath;
	CXFolder *m_pCurrSelFolder;
	CXFileMngr *m_pXFileMngr;
	CString m_strXFilePostFix;
	CString m_strXFileFilter;

    void xlang_InitAndAdjust();
// 对话框数据

protected:
	CXFolder* GetSelFolder()	{		return (CXFolder*)m_treeFolder.GetSelObject();	}
	void EnableOkButton();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CXFolderTreeCtrl m_treeFolder;
	CString m_strXFile;
	afx_msg void OnEnChangeEditFilename();
	afx_msg void OnTvnSelchangedTreeFolder(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CXLanguageButton m_btnOK;
	CXLanguageButton m_btnCancel;
	CXLanguageTextWnd m_stcTitleSelFolder;
	CXLanguageTextWnd m_stcTitleFileName;
	CEdit   m_edtFileName;

protected:
	virtual void OnOK();
public:
	afx_msg void OnNMDblclkTreeFolder(NMHDR *pNMHDR, LRESULT *pResult);
};
