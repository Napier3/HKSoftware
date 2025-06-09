#pragma once

/*
	π¶ƒ‹√Ë ˆ£∫
*/

#include "UISftRsltWndInterface.h"

class CUISftRsltWndDateTimeCtrl : public CDateTimeCtrl
{
public:
	CUISftRsltWndDateTimeCtrl(const CString &strFormat);
	virtual ~CUISftRsltWndDateTimeCtrl();

public:
	CUISftRsltWndInterface* m_pResultWndInterface;
	CString m_strDateTimeFormat;  

public:
	void InitResultDateTimeCtrl(const CString &strFormat, CString &strValue);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult);
};