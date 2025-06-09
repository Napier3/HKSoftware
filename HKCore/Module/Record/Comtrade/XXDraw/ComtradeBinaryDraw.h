// ComtradeDigitalDraw.h: interface for the CComtradeDigitalDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined COMTRADEDIGITALDRAW_H_
#define COMTRADEDIGITALDRAW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ComtradeDrawBaseClass.h"

class CComtradeBinaryDraw : public CComtradeDrawBaseClass  
{
public:
	CComtradeBinaryDraw();
	CComtradeBinaryDraw(CString chType);
	virtual ~CComtradeBinaryDraw();

public:
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);
	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

// 	virtual void DrawIt(CComtradeDataBaseClass*pData,CPoint*pPoint,CAxisReference*axisRef,CDC*pDC);
// 	virtual void DrawIt(CDC*pDC,CComtradeDataBaseClass*pData,CMemBuffer_CPoint*pPointBuff,CAxisReference*axisRef,int iBeginIndex,int iEndIndex,int iMode=0);
// 	virtual void DrawCHTitle(CDC*pDC,CComtradeDataBaseClass*pData,int iMode=0,int iState=0,COLORREF crBack=RGB(192,192,192));
};

#endif // !defined(COMTRADEDIGITALDRAW_H_)
