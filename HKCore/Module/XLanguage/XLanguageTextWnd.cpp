// XLanguageTextWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XLanguageTextWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CXLanguageTextWnd

IMPLEMENT_DYNAMIC(CXLanguageTextWnd, CStatic)

CXLanguageTextWnd::CXLanguageTextWnd()
{

}

CXLanguageTextWnd::~CXLanguageTextWnd()
{
}


BEGIN_MESSAGE_MAP(CXLanguageTextWnd, CStatic)
END_MESSAGE_MAP()



// CXLanguageTextWnd ��Ϣ�������
BOOL CXLanguageTextWnd::SetLanguageID(const CString &strLanguageID)
{
	m_pWndRef = this;

	return InitByLanguageID(strLanguageID, this);
}


void CXLanguageTextWnd::CalXLangWndAdj(CRect &rcOrigin, long &nCalWidth)
{
	m_pWndRef = this;

	xlang_CalXLangWndAdj(this, rcOrigin, nCalWidth);

	UINT nStyle = GetStyle();

	if ( (nStyle & BS_GROUPBOX)==BS_GROUPBOX)
	{
		nCalWidth += 18;
	}
	else
	{
	}
}



