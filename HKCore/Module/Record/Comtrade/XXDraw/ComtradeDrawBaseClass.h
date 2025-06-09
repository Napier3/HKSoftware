// ComtradeDrawBaseClass.h: interface for the CComtradeDrawBaseClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined COMTRADEDRAWBASECLASS_H_
#define COMTRADEDRAWBASECLASS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\XDrawBase\XDrawElements.h"
#include "..\..\..\API\GloblaDrawFunctions.h"
#include "..\ComtradeDataBase.h"

#define ANALOG_DRAW_MIN_HEIGHT  160
#define BINARY_DRAW_HEIGHT          12

class CComtradeDrawBaseClass : public CXDrawElements  
{
public:
// 	CString	m_strDrawType;		//通道绘图的注册类
// 	LOGFONT	m_lfDrawFont;
// 
// 	CDC		*m_pMemDC;				//内存绘制指针
// 	CBitmap *m_pBitmap;				//新位图
// 	CBitmap *m_pOldBMP;				//原位图

protected:
	void Init();

public:
	CComtradeDrawBaseClass();
	CComtradeDrawBaseClass(CString strType);
	virtual ~CComtradeDrawBaseClass();

	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);
	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

	BOOL	GetTimeByCursorPos(int iXL,int iXR,float &fTime1,float &fTime2);
	BOOL	GetXPosByTimeVal(float fTime1,int &iXPos);
// 	virtual void DrawIt(CComtradeDataBaseClass*pData,CPoint*pPoint,CAxisReference*axisRef,CDC*pDC);
// 	virtual void DrawIt(CDC*pDC,CComtradeDataBaseClass*pData,CMemBuffer_CPoint*pPointBuff,CAxisReference*axisRef,int iBeginIndex,int iEndIndex,int iMode=0);
// 	virtual void DrawCHTitle(CDC*pDC,CComtradeDataBaseClass*pData,int iMode=0,int iState=0,COLORREF crBack=RGB(192,192,192));
};

#endif // !defined(COMTRADEDRAWBASECLASS_H_)
