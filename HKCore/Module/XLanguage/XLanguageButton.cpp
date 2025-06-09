// XLanguageButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XLanguageButton.h"


// CXLanguageButton

IMPLEMENT_DYNAMIC(CXLanguageButton, CButton)

CXLanguageButton::CXLanguageButton()
{

}

CXLanguageButton::~CXLanguageButton()
{
}


BEGIN_MESSAGE_MAP(CXLanguageButton, CButton)
END_MESSAGE_MAP()



// CXLanguageButton 消息处理程序
BOOL CXLanguageButton::SetLanguageID(const CString &strLanguageID)
{
	m_pWndRef = this;
	return InitByLanguageID(strLanguageID, this);
}

void CXLanguageButton::CalXLangWndAdj(CRect &rcOrigin, long &nCalWidth)
{
	m_pWndRef = this;
	xlang_CalXLangWndAdj(this, rcOrigin, nCalWidth);
	
	UINT nStyle = GetStyle();

	if ( (nStyle & BS_CHECKBOX)==BS_CHECKBOX 
		|| (nStyle & BS_AUTOCHECKBOX) == BS_AUTOCHECKBOX
		|| (nStyle & BS_RADIOBUTTON) == BS_RADIOBUTTON
		|| (nStyle & BS_AUTORADIOBUTTON) == BS_AUTORADIOBUTTON
		)
	{
		nCalWidth += 18;
	}
	else
	{
		nCalWidth += GetSystemMetrics(SM_CXBORDER) * 2;
		nCalWidth += 6;
	}
}

