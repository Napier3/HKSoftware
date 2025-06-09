#pragma once

#include "XFileDlgDefine.h"
#include "XFileMngr.h"
#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\Xlanguage\XLanguageButton.h"




// CXFolderAddDlg �Ի���

class CXFolderAddDlg : public CDynDialogEx
{
	//DECLARE_DYNAMIC(CXFolderAddDlg)

public:
	CXFolderAddDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXFolderAddDlg();
	
	CXFolder *m_pSrcFolder;
	void EnableOkButton();

	void xlang_InitAndAdjust();

// �Ի�������

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeEditDestName();
	CString m_strDestFolderName;
	CString m_strInfor;

	CXLanguageButton m_btnOK;
	CXLanguageButton m_btnCancel;
	CEdit m_edtDestFileName;
	CEdit m_edtInfor;
	CXLanguageTextWnd m_stcDstFileName;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
