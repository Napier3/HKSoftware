#pragma once
#include "WzdDlgBase.h"
#include "../StepCtrl/WzdDlgButton.h"
#include "../../../iSmartTestWzd/Resource.h"

class CWzdEntrySelDlg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzdEntrySelDlg)
private:
	CWzdDlgButton m_txtTitle;
	CWzdDlgButton m_btnNewTest;
	CWzdDlgButton m_btnOpen;
	CWzdDlgButton m_btnBluet;
	CWzdDlgButton m_btnSystem;
	CWzdDlgButton m_btnUpdate;
	CWzdDlgButton m_btnBk;

public:
	CWzdEntrySelDlg(CWnd* pParent = NULL);
	virtual ~CWzdEntrySelDlg();

	enum { IDD = IDD_WZDENTRYSELDLG_DIALOG };

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	virtual void OnInitialUpdate();
	virtual BOOL InitUI();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnNewtest();
	afx_msg void OnBnClickedBtnOpenRecord();
	afx_msg void OnBnClickedBtnOpenBluet();
};
