//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangRibbonCtrls.cpp


#include "stdafx.h"
#include "XLangRibbonCtrls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CXLangRibbonButton::CXLangRibbonButton()
{
	
}

CXLangRibbonButton::~CXLangRibbonButton()
{

}

CXLangRibbonButton::CXLangRibbonButton(UINT nID, LPCTSTR lpszText, int nSmallImageIndex, int nLargeImageIndex, BOOL bAlwaysShowDescription)
	: CMFCRibbonButton(nID, lpszText, nSmallImageIndex, nLargeImageIndex, bAlwaysShowDescription)
{
	
}

CXLangRibbonButton::CXLangRibbonButton(UINT nID, LPCTSTR lpszText, HICON hIcon, BOOL bAlwaysShowDescription, HICON hIconSmall, BOOL bAutoDestroyIcon, BOOL bAlphaBlendIcon)
	: CMFCRibbonButton(nID, lpszText, hIcon, bAlwaysShowDescription, hIconSmall, bAutoDestroyIcon, bAlphaBlendIcon)
{
	
}


CXLangRibbonButton::CXLangRibbonButton(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText, int nSmallImageIndex, int nLargeImageIndex, BOOL bAlwaysShowDescription)
	: CMFCRibbonButton(nID, lpszText, nSmallImageIndex, nLargeImageIndex, bAlwaysShowDescription)
{
	m_strToolTipTxt = lpszTipText;
}

CXLangRibbonButton::CXLangRibbonButton(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText, HICON hIcon, BOOL bAlwaysShowDescription, HICON hIconSmall, BOOL bAutoDestroyIcon, BOOL bAlphaBlendIcon)
	: CMFCRibbonButton(nID, lpszText, hIcon, bAlwaysShowDescription, hIconSmall, bAutoDestroyIcon, bAlphaBlendIcon)
{
	m_strToolTipTxt = lpszTipText;
}

void CXLangRibbonButton::UpdateTooltipInfo()
{
	ASSERT_VALID(this);

	if (m_nID == 0 || m_nID == (UINT)-1)
	{
		return;
	}

	m_strToolTip.Empty();
	m_strDescription.Empty();

	if (m_strToolTipTxt.IsEmpty())
	{
		return;
	}

	AfxExtractSubString(m_strDescription, m_strToolTipTxt, 0);
	AfxExtractSubString(m_strToolTip, m_strToolTipTxt, 1, '\n');

	const CString strDummyAmpSeq = _T("\001\001");

	m_strToolTip.Replace(_T("&&"), strDummyAmpSeq);
	m_strToolTip.Remove(_T('&'));
	m_strToolTip.Replace(strDummyAmpSeq, _T("&"));
}



//CXLangRibbonCheckBox类//
CXLangRibbonCheckBox::CXLangRibbonCheckBox()
{

}

CXLangRibbonCheckBox::~CXLangRibbonCheckBox()
{

}

CXLangRibbonCheckBox::CXLangRibbonCheckBox(UINT nID, LPCTSTR lpszText)
:CMFCRibbonCheckBox( nID, lpszText)
{

}

CXLangRibbonCheckBox::CXLangRibbonCheckBox(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText)
:CMFCRibbonCheckBox( nID, lpszText)
{

	m_strToolTipTxt = lpszTipText;
}

void CXLangRibbonCheckBox::UpdateTooltipInfo()
{
	ASSERT_VALID(this);

	if (m_nID == 0 || m_nID == (UINT)-1)
	{
		return;
	}

	m_strToolTip.Empty();
	m_strDescription.Empty();

	if (m_strToolTipTxt.IsEmpty())
	{
		return;
	}

	AfxExtractSubString(m_strDescription, m_strToolTipTxt, 0);
	AfxExtractSubString(m_strToolTip, m_strToolTipTxt, 1, '\n');

	const CString strDummyAmpSeq = _T("\001\001");

	m_strToolTip.Replace(_T("&&"), strDummyAmpSeq);
	m_strToolTip.Remove(_T('&'));
	m_strToolTip.Replace(strDummyAmpSeq, _T("&"));
}
//CXLangRibbonCheckBox类//

//CXLangRibbonMainPanelButton类//
CXLangRibbonMainPanelButton::CXLangRibbonMainPanelButton()
{

}
CXLangRibbonMainPanelButton::~CXLangRibbonMainPanelButton()
{

}
CXLangRibbonMainPanelButton::CXLangRibbonMainPanelButton(UINT nID, LPCTSTR lpszText, int nSmallImageIndex)
:CMFCRibbonMainPanelButton( nID, lpszText, nSmallImageIndex)
{

}

CXLangRibbonMainPanelButton::CXLangRibbonMainPanelButton(UINT nID, LPCTSTR lpszText, HICON hIcon)
:CMFCRibbonMainPanelButton( nID, lpszText, hIcon)
{

}

CXLangRibbonMainPanelButton::CXLangRibbonMainPanelButton(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText, int nSmallImageIndex)
:CMFCRibbonMainPanelButton( nID, lpszText, nSmallImageIndex)
{
	m_strToolTipTxt = lpszTipText;
}

CXLangRibbonMainPanelButton::CXLangRibbonMainPanelButton(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText, HICON hIcon)
:CMFCRibbonMainPanelButton( nID, lpszText, hIcon)
{
	m_strToolTipTxt = lpszTipText;
}

void CXLangRibbonMainPanelButton::UpdateTooltipInfo()
{
	ASSERT_VALID(this);

	if (m_nID == 0 || m_nID == (UINT)-1)
	{
		return;
	}

	m_strToolTip.Empty();
	m_strDescription.Empty();

	if (m_strToolTipTxt.IsEmpty())
	{
		return;
	}

	AfxExtractSubString(m_strDescription, m_strToolTipTxt, 0);
	AfxExtractSubString(m_strToolTip, m_strToolTipTxt, 1, '\n');

	const CString strDummyAmpSeq = _T("\001\001");

	m_strToolTip.Replace(_T("&&"), strDummyAmpSeq);
	m_strToolTip.Remove(_T('&'));
	m_strToolTip.Replace(strDummyAmpSeq, _T("&"));
}