#pragma once
#include "afxwin.h"

#include "..\..\Module\BaseClass\ExBaseListComboBox.h"
#include "CharElementLineDlg.h"
#include "CharElementLinedDlg.h"
#include "CharElementLinerDlg.h"
#include "CharElementArcDlg.h"
#include "CharElementArcpDlg.h"
#include "CharElementMhoDlg.h"
#include "CharElementLensDlg.h"
#include "CharElementInvI2TDlg.h"
#include "CharElementInvIACDlg.h"
#include "CharElementInvIECDlg.h"
#include "CharElementInvIEEEDlg.h"
#include "CharElementInvOwnDefDlg.h"
#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\XLanguage\XLanguageButton.h"

// CDlgCharElement 对话框

class CDlgCharElement : public CDialog
{
	DECLARE_DYNAMIC(CDlgCharElement)

protected:
	void ShowElementDlg(const CString &strClassID);
	CCharElmentBaseDlg* CreateCharElementDlg(const CString &strClassID); 

	CCharElementMngrDlg m_oCharElementMngrDlg;
	CCharElmentBaseDlg *m_pElementDlgCurr;
	CRect m_rcCharElemDlg;

public:
	CDlgCharElement(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCharElement();
	CCharElement *m_pCharElementEdit;  //当前编辑的元素
	CCharElement *m_pCharElementSrcSel;  //当前选中的元素
	CCharElement *m_pPrevCharElement;  //当前选中的元素

	void xlang_InitAndAdjust();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHAR_ELEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExBaseListComboBox m_cmbElementType;
	CStatic m_wndFrmElement;
	afx_msg void OnCbnSelchangeCmbElementtype();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CString m_strErrLength;
	long m_nTestPoints;

	CXLanguageTextWnd m_wndEdgeElementType;
	CXLanguageTextWnd m_wndErrorBandLength;
	CXLanguageTextWnd m_wndEdgTestPoints;
	CXLanguageButton m_btnOK;
	CXLanguageButton m_btnCancel;
	CEdit m_edtErrorBandLength;
	CEdit m_edtEdgTestPoints;

};
