// DrawPara.h: interface for the CDrawPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWPARA_H__D57BB87E_FB2E_4953_B0A3_EA432828C9B4__INCLUDED_)
#define AFX_DRAWPARA_H__D57BB87E_FB2E_4953_B0A3_EA432828C9B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBase.h"
#include "../RecordTest/CalFunctions.h"

#define Para_FreqValue			0
#define Para_EffecValue			1
#define Para_EffecPhase			2
#define Para_FundValue			3
#define Para_HarmValue2			4  
#define Para_HarmValue3			5  
#define Para_HarmValue4			6 
#define Para_HarmValue5			7  
#define Para_HarmValue6			8  
#define Para_HarmValue7			9  
#define Para_HarmValue8			10  
#define Para_HarmValue9			11  
#define Para_HarmValue10		12 
#define Para_HarmValue11		13 
#define Para_HarmValue12		14 
#define Para_HarmValue13		15 
#define Para_HarmValue14		16 
#define Para_HarmValue15		17 
#define Para_HarmValue16		18 
#define Para_HarmValue17		19 
#define Para_HarmValue18		20 
#define Para_HarmValue19		21
#define Para_HarmValue20		22 
#define Para_HarmValue21		23 
#define Para_HarmValue22		24 
#define Para_HarmValue23		25 
#define Para_HarmValue24		26 
#define Para_HarmValue25		27 
#define Para_PeakValue			28
#define Para_VellayValue		29
#define Para_InstValue			30
#define Para_AverageValue		31
#define Para_Impedance			32 
#define Para_PositiveSequence	33
#define Para_NegativeSequence	34
#define Para_ZeroSequence		35 
#define Para_ActivePower		36 
#define Para_ReactivePower		37
#define Para_ApparentPower      38

class CDrawPara : public CDrawBase  
{
public:
	CDrawPara();
	virtual ~CDrawPara();

public:
	CString m_strUnit;
	UINT m_nParaID;
	double* m_pdValue;
	PRTATTRIBUTECALFUNCPARA m_pCalFuncPara;
	CALFUNC *m_pfCalFunc;
	CFont* m_pfPara;//参数的字体

public:
	virtual UINT GetParaID()	{	return m_nParaID;	}
	virtual void CalValue();
	virtual void Draw(CDC* pDC);
	virtual void GetDrawRectSize(long& cx,long& cy);
	virtual void Init(UINT nParaID,const CString& strUnit,PRTATTRIBUTECALFUNCPARA pCalFuncPara,CFont* pFont);
};

#endif // !defined(AFX_DRAWPARA_H__D57BB87E_FB2E_4953_B0A3_EA432828C9B4__INCLUDED_)
