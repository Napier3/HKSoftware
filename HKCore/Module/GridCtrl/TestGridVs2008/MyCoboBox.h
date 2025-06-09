#pragma once


// CMyCoboBox

class CMyCoboBox : public CComboBox
{
	DECLARE_DYNAMIC(CMyCoboBox)

public:
	CMyCoboBox();
	virtual ~CMyCoboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCbnKillfocus();
};


