#pragma once


// CHexEdit

class CHexEdit : public CMFCMaskedEdit
{
	DECLARE_DYNAMIC(CHexEdit)

public:
	CHexEdit();
	virtual ~CHexEdit();
	void Init(long nLength);
	void InitEx(long nLength);
	void SetValue(DWORD dwValue);
	void GetValue(DWORD &dwValue);
	void SetValue(WORD wValue);
	void GetValue(WORD &wValue);
	void SetValue(BYTE byteValue);
	void GetValue(BYTE &byteValue);

	CString GetHexText()
	{
		CString strText;
		GetWindowText(strText);
		return strText;
	}
protected:
	long m_nLength;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


