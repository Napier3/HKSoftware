// GloblaDrawFunctions.h: interface for the CGloblaDrawFunctions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBLADRAWFUNCTIONS_H__188B0C96_EDD8_43C7_8362_A7F8EE0E9F08__INCLUDED_)
#define AFX_GLOBLADRAWFUNCTIONS_H__188B0C96_EDD8_43C7_8362_A7F8EE0E9F08__INCLUDED_

#include "../OSInterface/OSInterface.h"

//2019-10-10  ºÊ»›QT,add CmDrawText_CalRect
void CmDrawText_CalRect(CDC *pDC, CRect &rc, const CString &strText, UINT uFormat);

LOGBRUSH InitLogBrush(int iStyle,int iWidth,COLORREF cr);
LOGPEN InitLogPen(int iStyle,int iWidth,COLORREF cr);
LOGFONT  InitLogFont ();
LOGFONT  InitLogFont (int   lfHeight, int   lfWidth, int   lfEscapement, int   lfOrientation,
					  int   lfWeight, BYTE  lfItalic, BYTE  lfUnderline, BYTE  lfStrikeOut,
					  BYTE  lfCharSet,BYTE  lfOutPrecision,BYTE  lfClipPrecision,BYTE  lfQuality,
                                          BYTE  lfPitchAndFamily,const CString &lfFaceName);
void DrawShadowVertLine(CDC *cDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2);
void DrawShadowHorzLine(CDC *cDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2, long nDir=0);
void Draw3dRectByMe(CDC *cDC,CRect &cR,int iGap,COLORREF crLeftTop,COLORREF crRightBottom,COLORREF crBk);
void Draw3dRectBorder(CDC *cDC,CRect &cR,int iGap,COLORREF crLeftTop,COLORREF crRightBottom);
void Draw3dRectBorder(CDC *cDC,CRect *cR,int iGap,COLORREF crLeftTop,COLORREF crRightBottom);
void DrawRectBorder(CDC *pDC,CRect cR,COLORREF crColor);
void DrawRectBorder(CDC *pDC,long nLeft,long nTop,long nRight,long nBottom,COLORREF crColor);

BOOL  CmDrawTextRect(CDC * hDC,
                                         const CString &lpStr,
					 COLORREF crColor,
					 CRect    cR,
					 COLORREF crBK,
					 LOGFONT  lfFont,
					 UINT uBkMode,
					 UINT uFormat,long lShadow);
BOOL  CmDrawTextRect(CDC * hDC,
                                         const CString &lpStr,
                                         COLORREF crColor,
                                         CRect    *cR,
                                         COLORREF crBK,
                                         LOGFONT  lfFont,
                                         UINT uBkMode,
                                         UINT uFormat,long lShadow);

BOOL  CmGetDrawTextRect(CDC * hDC,
                                                const CString &lpStr,
						CRect    &cR,
						LOGFONT  lfFont,
						UINT uFormat);
long TwipToPixel(CDC *pDC,long lTwip, BOOL bHoriz=TRUE);
long PixelToTwip(CDC *pDC,long lPixel, BOOL bHoriz=TRUE);

long GetCharWidthByLogfont2(CDC *pDC,LOGFONT lf);

void DrawExpandBoxRect(long xCenter,long yCenter,BOOL bExpand,CDC *pDC);
void DrawCheckBoxRect(long xCenter,long yCenter,long nCheckState,CDC *pDC,BOOL bEnable=TRUE);

inline void GetExpandBoxSize(CSize &size)
{
	size.cx = 9;	
	size.cy = 9;
}

inline void GetCheckBoxSize(CSize &size)
{
	size.cx = 13;	
	size.cy = 13;
}
inline void GetExpandBoxRect(long xCenter,long yCenter,CRect &rectBox)
{
	rectBox = CRect(xCenter-4,yCenter-4,xCenter+4,yCenter+4);	
}

inline void GetCheckBoxRect(long xCenter,long yCenter,CRect &rectBox)
{
	rectBox = CRect(xCenter-6,yCenter-6,xCenter+6,yCenter+6);
}



#ifndef _PSX_IDE_QT_
typedef BOOL(WINAPI *PFNGRADIENTFILL)(HDC,PTRIVERTEX,ULONG,PVOID,ULONG,ULONG);
extern PFNGRADIENTFILL g_pfnFastGradientFill;
extern HMODULE g_hLibMsImg;

BOOL IsLowResolution(HDC hDC = 0);
COLORREF BlendColors(COLORREF crA, COLORREF crB, float fAmountA);
void GradientFill(CDC* pDC, LPRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);
void GradientFillFast(CDC* pDC, LPRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);
void GradientFillSlow(CDC* pDC, LPRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);

inline long LightenColor(COLORREF clr, double factor)
{
	return RGB(
		(long)(factor * 255 + (1.0 - factor) * GetRValue(clr)),
		(long)(factor * 255 + (1.0 - factor) * GetGValue(clr)),
		(long)(factor * 255 + (1.0 - factor) * GetBValue(clr))) ;
}

void DrawTransparentBitmap(CDC *pDC, UINT IDImage,CRect &rect, COLORREF rgbMask, BOOL bEnable = TRUE);
void DrawTransparentBitmap(CDC *pDC, CBitmap *pBmp,CRect &rect, COLORREF rgbMask, BOOL bEnable = TRUE);
#endif


extern CFont *g_pGlobalFont11;
extern CFont *g_pGlobalFont12;
extern CFont *g_pGlobalFont;
extern CFont *g_pGlobalFont14;
extern CFont *g_pGlobalFont15;
extern CFont *g_pGlobalFont16;
extern CFont *g_pGlobalFont18;
extern CFont *g_pGlobalFont20;
extern CFont *g_pGlobalFont24;

extern LOGFONT g_lfGlobalFont11;
extern LOGFONT g_lfGlobalFont12;
extern LOGFONT g_lfGlobalFont;
extern LOGFONT g_lfGlobalFont14;
extern LOGFONT g_lfGlobalFont15;
extern LOGFONT g_lfGlobalFont16;
extern LOGFONT g_lfGlobalFont18;
extern LOGFONT g_lfGlobalFont20;
extern LOGFONT g_lfGlobalFont24;

CFont* GetGlobalFontBySize(long nSize);
CFont* font_CreateNew(LOGFONT &lf, long lfHeight);



#endif // !defined(AFX_GLOBLADRAWFUNCTIONS_H__188B0C96_EDD8_43C7_8362_A7F8EE0E9F08__INCLUDED_)
