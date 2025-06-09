// DrawParas.h: interface for the CDrawParas class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWPARAS_H__825624BE_0EC7_4E48_A2C0_89E3396CEE5A__INCLUDED_)
#define AFX_DRAWPARAS_H__825624BE_0EC7_4E48_A2C0_89E3396CEE5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawMultiPara.h"
#include "DrawBase.h"
#include "../RecordTest/CalFunctions.h"
#define Para_to_Cursor 5

class CDrawParas : public CXDrawElements
{
public:	
	CRect m_rcPara;
	CFont m_oParaFont;
	CString m_strUnit;
	CPoint m_ptBegin;
	long m_nParaPosToCursor;//0-Right 1-Left
	RTCHANNELATTRVALUE m_oParaValue;
	RTATTRIBUTECALFUNCPARA m_oCalPara;
	CRect m_rcClip;
public:
	virtual void Draw(CDC* pDC);
	void AddPara(UINT nID);
	void DeletePara(UINT nID);
	void DeleteAllPara();
	void CalParaRect(long nXPos, long nYCenter);
	CDrawPara* CreateNewPara(UINT nID);
	void SetUnit(const CString& strUnit) { m_strUnit = strUnit;	}
	void SetAdjustValue(double dZero,double dCoef);
	void SetClipRect(CRect rect);
	void SetParaRect(CRect rcPara);
	void SetParentWnd(CWnd* pParentWnd);

	//2022-9-1  lijunqing
	void CalValue();
public:
	CDrawParas();
	virtual ~CDrawParas();
};

#endif // !defined(AFX_DRAWPARAS_H__825624BE_0EC7_4E48_A2C0_89E3396CEE5A__INCLUDED_)
