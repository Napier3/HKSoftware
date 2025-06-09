// DrawPara.h: interface for the CDrawPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWPARA_H__D57BB87E_FB2E_4953_B0A3_EA432828C9B4__INCLUDED_)
#define AFX_DRAWPARA_H__D57BB87E_FB2E_4953_B0A3_EA432828C9B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBase.h"
#include "..\CalFunctions.h"


class CDrawPara : public CDrawBase  
{
public:
	CDrawPara();
	virtual ~CDrawPara();

public:
	CString m_strUnit;
	UINT m_nParaID;
	double m_fFrequency;
	double m_fValue;
	double m_fAngle;
	CFont* m_pfPara;//参数的字体

public:
	virtual UINT GetParaID()	{	return m_nParaID;	}
	virtual void CalValue();
	virtual void Draw(CDC* pDC);
	virtual void GetDrawRectSize(long& cx,long& cy);
	virtual void Init(UINT nParaID,const CString& strUnit,PRTATTRIBUTECALFUNCPARA pCalFuncPara,CFont* pFont);
};

#endif // !defined(AFX_DRAWPARA_H__D57BB87E_FB2E_4953_B0A3_EA432828C9B4__INCLUDED_)
