// HarmHistogram.h: interface for the CHarmHistogram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARMHISTOGRAM_H__6C6F7360_FEC0_404C_BEDF_2FA6E458B942__INCLUDED_)
#define AFX_HARMHISTOGRAM_H__6C6F7360_FEC0_404C_BEDF_2FA6E458B942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\Module\Axis\RulerAxis.h"
#include "..\RecordTest\RecordTestClassDef.h"
#define HARM_ANALYSE_DRAW_BOTTOM_GAP    10
#define HARM_ANALYSE_DRAW_ONE_HARM_MIN_WIDTH    20
#define HARM_ANALYSE_DRAW_HARM_RECT_WIDTH    10
#define HARM_ANALYSE_DRAW_SCROLL_PAGE    6

class CHarmHistogram  
{
public:
	CHarmHistogram();
	virtual ~CHarmHistogram();

	long m_nHarmDrawBeginIndex;
	long m_nMaxHarmDrawOnce;
	CRect m_rcHarmDraw;
	
private:
	BOOL m_bAxisFixed;
	CRulerAxis m_oRulerAxis;
	CRect m_rcBorder;
	CRect m_rcAxis;
	CRect m_rcVariableName;
	CFont m_oHarmFont;
	CFont m_oHarmVariableNameFont;
	//PRTCHANNELATTRVALUE m_pCurrValue;//当前计算值

public:
	//////////////////////////////////////////////////////////////////////////
	//谐波绘图部分
	void CalMaxHarmValues();
	void SetBorder(const CRect &rc);
	void Draw(CDC *pDC);
	void SetAxisMaxValue(double dMax);
	void SetAxisFixed(BOOL bAxisFixed)		{	m_bAxisFixed = bAxisFixed;		}
	//void Set(PRTCHANNELATTRVALUE pValue)	{		m_pCurrValue = pValue;	}

private:
	void InitAxisSet();
	void InitAxis();
	void DrawHarm(CDC *pDC);
	void DrawHarm(CDC *pDC, long nIndex, long nBeginIndex, long xPos);
	long GetHarmDrawCount();

};

#endif // !defined(AFX_HARMHISTOGRAM_H__6C6F7360_FEC0_404C_BEDF_2FA6E458B942__INCLUDED_)
