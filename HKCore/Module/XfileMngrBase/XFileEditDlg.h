#pragma once

#include "XFileDlgDefine.h"
#include "XFileMngr.h"
#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\Xlanguage\XLanguageButton.h"

// CXFileEditDlg 对话框

class CXFileEditDlg : public CDynDialogEx
{
	//DECLARE_DYNAMIC(CXFileEditDlg)

public:
	CXFileEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXFileEditDlg();

	CXFile *m_pSrcFile;
	CXFileOptrMsgRcvWnd *m_pXFileMsgRcvWnd;

	void EnableOkButton();
	CString m_strFilePostfix;

public:
	//virtual int DoModal(); 

    void xlang_InitAndAdjust();

// 对话框数据
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditDestName();
	CString m_strSrcFileName;
	CString m_strDestFileName;
	CString m_strInfor;

	CButton m_btnOK;
	CButton m_btnCancel;
	CEdit m_edtSrcFileName;
	CEdit m_edtDestFileName;
	CEdit m_edtInfor;
	CXLanguageTextWnd m_stcSrcFileName;
	CXLanguageTextWnd m_stcDstFileName;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();

};
