#pragma once

/*
	π¶ƒ‹√Ë ˆ£∫
*/

#include "..\..\..\Module\MfcCtrlEx\IPAddressCtrlEx.h"
#include "UISftRsltWndInterface.h"

class CUISftRsltWndIpEdit : public CIPAddressCtrlEx
{
public:
	CUISftRsltWndIpEdit();
	virtual ~CUISftRsltWndIpEdit();

	void OnDataChanged();

public:
	CUISftRsltWndInterface* m_pResultWndInterface;

public:
	void InitResultDateTimeCtrl(CString &strValue);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnIpnFieldchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMThemeChanged(NMHDR *pNMHDR, LRESULT *pResult);
};