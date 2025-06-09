#pragma once


// CIPAddressCtrlEx

class CIPAddressCtrlEx : public CIPAddressCtrl
{
	DECLARE_DYNAMIC(CIPAddressCtrlEx)

public:
	CIPAddressCtrlEx();
	virtual ~CIPAddressCtrlEx();

	void SetAddress(const CString &strAddress);
	void SetAddress(const in_addr &addr);
	
	void GetAddress(CString &strAddress);
	void GetAddress(in_addr &addr);

	void SetTextColor(COLORREF cr);
protected:
	COLORREF m_crText;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


