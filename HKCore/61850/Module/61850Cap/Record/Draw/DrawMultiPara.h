// DrawMultiPara.h: interface for the CDrawMultiPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWMULTIPARA_H__980E063A_165E_4731_B635_6D78A1A26C79__INCLUDED_)
#define AFX_DRAWMULTIPARA_H__980E063A_165E_4731_B635_6D78A1A26C79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawPara.h"

class CDrawMultiPara : public CDrawPara  //有2个参数的，如基波有幅值和相位
{
public:
	CDrawMultiPara();
	virtual ~CDrawMultiPara();

public:
	CString m_strUnit2;

public:		
	virtual void Draw(CDC* pDC);
	virtual void GetDrawRectSize(long& cx,long& cy);
	virtual void Init(UINT nParaID,const CString& strUnit,PRTATTRIBUTECALFUNCPARA pCalFuncPara,CFont* pFont);
};

#endif // !defined(AFX_DRAWMULTIPARA_H__980E063A_165E_4731_B635_6D78A1A26C79__INCLUDED_)
