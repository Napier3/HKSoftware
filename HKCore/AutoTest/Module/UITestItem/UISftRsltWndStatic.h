#pragma once

class CUISftRsltWndStatic : public CEdit //CStatic  2021-4-3  lijunqing
{
public:
	CUISftRsltWndStatic();
	virtual ~CUISftRsltWndStatic();

public:
	CFont *m_pFont;
public:
	long CalWndSize(long &nWidth,long &nHeight);
	long m_nWidth;
	long m_nHeight;

	//2021-4-3  lijunqing
	void CreateUIStatic(const CString &strText, CRect rcWnd, CWnd *pParent, UINT nID);
};