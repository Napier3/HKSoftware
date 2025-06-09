#include "StdAfx.h"
#include "StringCmpBlock.h"

CStringCmpBlock::CStringCmpBlock()
{
	m_nBeginPos=0;
	m_nLength=0;
	m_nCmpState=0;
	m_pStringRef = NULL;
}

CStringCmpBlock::~CStringCmpBlock()
{
}

void CStringCmpBlock::GetString(CString &strText)
{
	strText = m_pStringRef->Mid(m_nBeginPos, m_nLength);	
}

CString CStringCmpBlock::GetString()
{
	return m_pStringRef->Mid(m_nBeginPos, m_nLength);	
}

long CStringCmpBlock::Draw(CDC *pDC,  CRect rc, UINT nFormat , COLORREF crMatch, COLORREF crUnmatch)
{
#ifndef _USE_NO_GUI_
    COLORREF TextClr = (m_nCmpState==CMPSTATE_MATCH) ? crMatch :crUnmatch;
	CString strText = m_pStringRef->Mid(m_nBeginPos, m_nLength);
	CRect rcTemp(0,0,0,0);

	pDC->DrawText(strText,rcTemp,DT_CALCRECT);
	long width=rcTemp.Width();

	COLORREF crOld = pDC->GetTextColor();
	pDC->SetTextColor(TextClr);
#ifndef _PSX_QT_LINUX_
	DrawText(pDC->m_hDC, strText, -1, rc, DT_LEFT);

	pDC->SetTextColor(crOld);
#endif 
   
	return width;
#else
        return 0;
#endif
}
