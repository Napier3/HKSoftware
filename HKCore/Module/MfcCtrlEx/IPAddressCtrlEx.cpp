// IPAddressCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "IPAddressCtrlEx.h"


// CIPAddressCtrlEx

IMPLEMENT_DYNAMIC(CIPAddressCtrlEx, CIPAddressCtrl)

CIPAddressCtrlEx::CIPAddressCtrlEx()
{
	m_crText = RGB(0, 0, 0);
}

CIPAddressCtrlEx::~CIPAddressCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CIPAddressCtrlEx, CIPAddressCtrl)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CIPAddressCtrlEx 消息处理程序
void CIPAddressCtrlEx::SetAddress(const CString &strAddress)
{
	char pszIP[40];
	CString_to_char(strAddress, pszIP);

	if (strlen(pszIP) < 7)
	{
		strcpy(pszIP, "0.0.0.0");
	}
	
	ULONG saddr = inet_addr(pszIP);
	 in_addr addr;
	 addr.s_addr = saddr;
	SetAddress(addr);
}

void CIPAddressCtrlEx::SetAddress(const in_addr &addr)
{
	CIPAddressCtrl::SetAddress(addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4 );
}

void CIPAddressCtrlEx::GetAddress(CString &strAddress)
{
	in_addr addr;
	GetAddress(addr);
	strAddress.Format(_T("%d.%d.%d.%d"), addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4 );
}

void CIPAddressCtrlEx::GetAddress(in_addr &addr)
{
	CIPAddressCtrl::GetAddress(addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4 );
}

void CIPAddressCtrlEx::SetTextColor(COLORREF cr)
{
	m_crText = cr;
	Invalidate(TRUE);
}

HBRUSH CIPAddressCtrlEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CIPAddressCtrl::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetTextColor(m_crText);

	return hbr;
}
