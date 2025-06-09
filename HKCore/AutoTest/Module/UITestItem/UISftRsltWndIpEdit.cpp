#include "stdafx.h"
#include "UISftRsltWndIpEdit.h"
#include "../GuideBook/GbDataTypeMngr.h"
#include <locale.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUISftRsltWndIpEdit::CUISftRsltWndIpEdit()
{
	m_pResultWndInterface = NULL;
}

CUISftRsltWndIpEdit::~CUISftRsltWndIpEdit()
{

}
BEGIN_MESSAGE_MAP(CUISftRsltWndIpEdit, CIPAddressCtrlEx)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_NOTIFY_REFLECT(IPN_FIELDCHANGED, &CUISftRsltWndIpEdit::OnIpnFieldchanged)
	ON_NOTIFY_REFLECT(NM_THEMECHANGED, &CUISftRsltWndIpEdit::OnNMThemeChanged)
END_MESSAGE_MAP()

void CUISftRsltWndIpEdit::OnDataChanged()
{
	CString strData;
	GetAddress(strData);

	if (m_pResultWndInterface != NULL)
	{
		m_pResultWndInterface->OnResultDataChanged(strData);
	}
}

void CUISftRsltWndIpEdit::OnKillFocus(CWnd* pNewWnd)
{
	CIPAddressCtrlEx::OnKillFocus(pNewWnd);

	OnDataChanged();
}

void CUISftRsltWndIpEdit::OnSetFocus(CWnd* pOldWnd)
{
	CIPAddressCtrlEx::OnSetFocus(pOldWnd);

	OnDataChanged();
}

void CUISftRsltWndIpEdit::OnIpnFieldchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	*pResult = 0;

	OnDataChanged();
}

void CUISftRsltWndIpEdit::OnNMThemeChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	OnDataChanged();
}
