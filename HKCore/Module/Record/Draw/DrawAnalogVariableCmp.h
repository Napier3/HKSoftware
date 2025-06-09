// DrawAnalogVariableCmp.h: interface for the CDrawAnalogVariableCmp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DrawAnalogVariableCmp_H__)
#define _DrawAnalogVariableCmp_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawAnalogVariable.h"

class CDrawAnalogVariableCmp : public CDrawAnalogVariable  
{
public:
	CDrawAnalogVariableCmp();
	virtual ~CDrawAnalogVariableCmp();

public:
	CDrawAnalogVariable m_oCmpAnalogDraw;


public:
	virtual void SetShow(long nShow);

//	virtual void SetBorder(const CRect &rect, BOOL bSavePos);
	virtual void Draw_Cmp(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void LogicPointToDevicePoint_Cmp(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos) ;
	virtual UINT GetClassID()	{	return CMTRDCLASSID_CMPANALOGVARIABLE ;		}

};

#endif // !defined(_DrawAnalogVariableCmp_H__)
