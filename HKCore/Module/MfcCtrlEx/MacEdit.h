#pragma once


// CMacEdit

class CMacEdit : public CMFCMaskedEdit
{
	DECLARE_DYNAMIC(CMacEdit)

public:
	CMacEdit();
	virtual ~CMacEdit();
	void Init();
	void GetMacAddr(CString &strMac);
	CString GetMacText();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


