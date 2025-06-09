#pragma once

#include "..\BaseClass\ExBaseListComboBox.h"
#include "FilterTextMngr.h"
#define  WM_FILTERTEXT_END_EDIT  (WM_USER + 800)

class CFilterTextComboBox : public CExBaseListComboBox
{
public:
	CFilterTextComboBox();
	virtual ~CFilterTextComboBox();

public:
	void InitFilterText(CFilterTextMngr *pFilterTextMngr);
	void SaveFilterText();
	BOOL GetFilterText(CString &strFilterText);

private:
	CString m_strPrevFilterText;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelendok();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg UINT OnGetDlgCode();
};


