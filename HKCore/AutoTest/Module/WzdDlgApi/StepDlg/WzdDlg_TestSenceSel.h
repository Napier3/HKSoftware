#pragma once
#include "WzdDlgBase.h"
#include "../StepCtrl/WzdDlgButton.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../StepCtrl/WzdDlgComboBox.h"
#include "../StepCtrl/WzdDlgEdit.h"

class CWzdDlg_TestSenceSel : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzdDlg_TestSenceSel)
private:
	CStatic m_txtUser;
	CWzdDlgComboBox m_cbbUser;
	CStatic m_txtCfg;
	CStatic m_txtLv;
	CWzdDlgComboBox m_cbbLv;
	CStatic m_txtType;
	CWzdDlgComboBox m_cbbType;
	CStatic m_txtFactory;
	CWzdDlgComboBox m_cbbFactory;
	CStatic m_txtComm;
	CWzdDlgComboBox m_cbbComm;
	CStatic m_txtTestType;
	CStatic m_txtSCD;
	CWzdDlgEdit m_editSCD;
	CWzdDlgNormalBtn m_btnSCD;
	CStatic m_txtFile;
	CButton m_cbFile;
	CWzdDlgEdit m_editFile;
	CWzdDlgNormalBtn m_btnFile;

	CWzdDlgComboBox m_cbbSubstationType;
	CWzdDlgComboBox m_cbbTestType;

private:
	CString m_strGbFile;
	CString m_strSelectPDF;

public:
	CWzdDlg_TestSenceSel(CWnd* pParent = NULL);
	virtual ~CWzdDlg_TestSenceSel();


	enum { IDD = IDD_SENCESEL_DIALOG };

private:
	void EnableSCD(BOOL bEnable = TRUE);
	void EnableFile(BOOL bEnable = TRUE);

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	virtual void OnInitialUpdate();
	virtual BOOL InitUI(CDataGroup* pDataGroup);
	BOOL IsIEDDevice();
	virtual BOOL DoNext();
	void SetGbFile(const CString& strFile);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedCbFile();
	afx_msg void OnBnClickedBtnScd();
	afx_msg void OnBnClickedBtnFile();
	afx_msg void OnCbnSelchangeCbbCfg();
	afx_msg void OnCbnSelchangeCbbComm();
	afx_msg void OnCbnSelChangeCbbFactory();
	afx_msg void OnCbnSelchangeCbbUser();
	afx_msg void OnCbnSelchangeCbbTesttype();
	afx_msg void OnCbnSelchangeCbbSitetype();
};

//当前页面未明晰及未实现部分
//
//变电站信息配置选择：“常规变电站”或者“智能变电站”，测试调用的是MMS客户端。
//变电站信息配置选择：“国产化常规变电站”或者“国产化智能变电站”，测试调用的是CMS客户端。