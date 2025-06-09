#pragma once
#include "afxwin.h"

#include "..\XFileMngrBase\XFile.h"

#include "XFileDlgDefine.h"
#include "XFileMngr.h"
#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\Xlanguage\XLanguageButton.h"


// CXFilePastDlg �Ի���

class CXFilePasteDlg : public CDynDialogEx
{
	//DECLARE_DYNAMIC(CXFilePasteDlg)

public:
	CXFilePasteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXFilePasteDlg();

	CXFile *m_pSrcFile;
	CXFile *m_pDestFile;
	CXFolder *m_pDestFolder;

	void EnableOkButton();

	void xlang_InitAndAdjust();
// �Ի�������
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditDestName();
	afx_msg void OnBnClickedOverwrite();
	CString m_strSrcFileName;
	CString m_strDestFileName;
	CString m_strInfor;

	CXLanguageButton m_btnOK;
	CXLanguageButton m_btnCancel;
	CXLanguageButton m_btnOverWrite;
	CEdit m_edtSrcFileName;
	CEdit m_edtDestFileName;
	CEdit m_edtInfor;
	CXLanguageTextWnd m_stcSrcFileName;
	CXLanguageTextWnd m_stcDstFileName;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
