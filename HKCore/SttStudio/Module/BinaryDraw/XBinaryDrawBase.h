//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawIed.h  CXDrawIed

#pragma once

#include "XBinaryDrawGlobal.h"
//#include "..\XGlobalApi.h"

#define  XBINARY_DRAW_WIDTH   42
#define  XBINARY_DRAW_HEIGHT  26
#define  XBINARY_DRAW_HEIGHT_FONT  16
#define  XBINARY_DRAW_GAP_HOR   3
#define  XBINARY_DRAW_GAP_VER    3

#define  XBINARY_DRAW_WIDTH_S   32
#define  XBINARY_DRAW_HEIGHT_S  20
#define  XBINARY_DRAW_HEIGHT_FONT_S  12
#define  XBINARY_DRAW_GAP_HOR_S   2
#define  XBINARY_DRAW_GAP_VER_S    2


#define BIANRY_DRAW_MODE_CARD_NXID    0
#define BIANRY_DRAW_MODE_CARD_ALLID   1


#define   X_BINARY_DRAW_SIZE_LARGE   1
#define   X_BINARY_DRAW_SIZE_SMALL   0

extern long g_nXBinaryDrawSize;
extern long g_nBinaryDrawMode;
extern LOGFONT g_fontXBinaryDraw;

#define BINARY_CLOSE_COLOR   RGB(255, 0, 0)
#define BINARY_OPEN_COLOR    RGB(0,250,154)

//////////////////////////////////////////////////////////////////////////
//CXBinaryDrawBase
class CXBinaryDrawBase : public CXDrawElement
{
public:
	CXBinaryDrawBase();
	virtual ~CXBinaryDrawBase();

	long    m_nBinaryIndex;   //开关量编号

//构建函数
public:
	virtual UINT GetClassID()                             {      return XBINARYDRAW_BINARY;                 }

	virtual long GetBinaryBitVal();
//重载函数
public:
 	virtual void AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow);

public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag);
	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

};

class CXBinaryOutDraw : public CXBinaryDrawBase
{
public:
	CXBinaryOutDraw();
	virtual ~CXBinaryOutDraw();

public:
	virtual UINT GetClassID()                             {      return XBINARYDRAW_BINARYOUT;                 }

public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag);
	virtual BOOL UI_OnLButtonDown(UINT nFlags, CPoint point);

};

//////////////////////////////////////////////////////////////////////////
//CXBinarysDrawBase
class CXBinarysDrawBase : public CXDrawElements
{
public:
	CXBinarysDrawBase();
	virtual ~CXBinarysDrawBase();

	BYTE *m_pBinaryBufRef;
	long    m_nBinaryCount;   //开关量数目

//构建函数
public:
	virtual UINT GetClassID()                             {      return XBINARYDRAW_BINARYS;                 }

//重载函数
public:
	virtual void AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow);
	
public:
	//virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag);
	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

};


inline long vm_binary_get_width()
{
	if (X_BINARY_DRAW_SIZE_LARGE == g_nXBinaryDrawSize)
	{
		return XBINARY_DRAW_WIDTH + XBINARY_DRAW_GAP_HOR * 2;
	}
	else
	{
		return XBINARY_DRAW_WIDTH_S + XBINARY_DRAW_GAP_HOR_S * 2;
	}
}

inline long vm_binary_get_height()
{
	if (X_BINARY_DRAW_SIZE_LARGE == g_nXBinaryDrawSize)
	{
		return XBINARY_DRAW_HEIGHT + XBINARY_DRAW_GAP_VER * 2;
	}
	else
	{
		return XBINARY_DRAW_HEIGHT_S + XBINARY_DRAW_GAP_VER_S * 2;
	}
}

void vm_draw_init_binary_font();
void vm_draw_get_binary_rect(const CPoint &ptTopLeft, CRect &rc);
void vm_draw_get_binary_name(CString &strName, long nBinaryIndex);
