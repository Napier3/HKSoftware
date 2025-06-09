#pragma once
#include "afxcmn.h"

#include "..\Module\Characteristic\CharLibTreeCtrl.h"
#include "afxwin.h"
#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\XLanguage\XLanguageButton.h"

// CCharEditDlg 对话框

class CCharEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CCharEditDlg)

public:
	CCharEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharEditDlg();

	CString m_strTitle;
	CCharacteristic *m_pCharTemp;
	CCharacterFolder *m_pCurrFolder;
	CString m_strAxis;
	CString m_strTestLineMode;

	CString  m_strXMin;
	CString  m_strXMax;
	CString  m_strYMin;
	CString  m_strYMax;

	void xlang_InitAndAdjust();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHAR };

protected:
	CImageList m_CharLibViewImages;
	void InitImageList();
	void EnableOKButton();
	void EnableMinMax();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strName;
	CString m_strID;
	int m_nAxis;
	afx_msg void OnBnClickedRadioDecartes();
	afx_msg void OnBnClickedRadioPolor();
	afx_msg void OnBnClickedRadioLog();
protected:
	virtual void OnOK();
public:
	CXLanguageButton m_btnOK;
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditId();
	int m_nSearchLineMode;
	CEdit m_edtXMin;
	CEdit m_edtXMax;
	CEdit m_edtYMin;
	CEdit m_edtYMax;

	CXLanguageTextWnd m_wndCharName;
	CXLanguageTextWnd m_wndCharMarking;
	CXLanguageTextWnd m_xFrameCharSystem;
	CXLanguageTextWnd m_xFrameSearchLineMode;
	CXLanguageButton m_btnDecSystem;
	CXLanguageButton m_btnPolarSystem;
	CXLanguageButton m_btnLogSystem;
	CXLanguageButton m_btnVertical;
	CXLanguageButton m_btnVerticalLine;
	CXLanguageButton m_btnHorizontalLine;
	CXLanguageButton m_btnCharCancel;
	CEdit m_edtCharName;
	CEdit m_edtCharMarking;
};
