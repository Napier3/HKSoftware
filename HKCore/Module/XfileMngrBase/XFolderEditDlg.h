#pragma once

#include "XFileDlgDefine.h"
#include "XFileMngr.h"
#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\Xlanguage\XLanguageButton.h"


// CXFolderEditDlg 对话框

class CXFolderEditDlg : public CDynDialogEx
{
	//DECLARE_DYNAMIC(CXFolderEditDlg)

public:
	CXFolderEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXFolderEditDlg();

	CXFolder *m_pSrcFolder;
	void EnableOkButton();

	void xlang_InitAndAdjust();
// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeEditDestName();
	CString m_strSrcFolderName;
	CString m_strDestFolderName;
	CString m_strInfor;

	CXLanguageButton m_btnOK;
	CXLanguageButton m_btnCancel;
	CEdit m_edtSrcFileName;
	CEdit m_edtDestFileName;
	CEdit m_edtInfor;
	CXLanguageTextWnd m_stcSrcFileName;
	CXLanguageTextWnd m_stcDstFileName;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();

};
