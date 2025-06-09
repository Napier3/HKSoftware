#pragma once
#include "WzdDlgBase.h"
#include "../../iSmartTestWzd/iSmartTestWzd.h"

class CWzdDlg_ConnectTip : public CDialog, CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzdDlg_ConnectTip)
private:
	CButton m_btnIcon;
	CStatic m_txtTitle;

public:
	CWzdDlg_ConnectTip(CWnd* pParent = NULL);
	virtual ~CWzdDlg_ConnectTip();

	enum { IDD = IDD_CONNECTTIP_DIALOG };

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
};