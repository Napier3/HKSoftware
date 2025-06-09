// GloblaDrawFunctions.cpp: implementation of the CGloblaDrawFunctions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GloblaDrawFunctions.h"

#ifdef _PSX_IDE_QT_
#include "QT/GloblaDrawFunctions_QT.cpp"
#else

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CmDrawText_CalRect(CDC *pDC, CRect &rc, const CString &strText, UINT uFormat)
{
	uFormat |= DT_CALCRECT;
	pDC->DrawText(strText, rc, uFormat);
}

LOGBRUSH InitLogBrush(int iStyle,int iWidth,COLORREF cr)
{
	LOGBRUSH lb;
	lb.lbColor=cr;
	lb.lbHatch=iWidth;
	lb.lbStyle=iStyle;
	return lb;
}
LOGPEN InitLogPen(int iStyle,int iWidth,COLORREF cr)
{
	LOGPEN lp;
	POINT p;
	p.x=iWidth;
	lp.lopnColor=cr;
	lp.lopnStyle=iStyle;
	lp.lopnWidth=p;
	return lp;
}

LOGFONT  InitLogFont ()
{
	return InitLogFont (-14,0,0,0,400,'\0','\0','\0','\1','\x1','\x2','\x1','1',_T("Tahoma"));
}
LOGFONT  InitLogFont (int   lfHeight, int   lfWidth, int   lfEscapement, int   lfOrientation,
								  int   lfWeight, BYTE  lfItalic, BYTE  lfUnderline, BYTE  lfStrikeOut,
								  BYTE  lfCharSet,BYTE  lfOutPrecision,BYTE  lfClipPrecision,BYTE  lfQuality,
								  BYTE  lfPitchAndFamily,const CString &lfFaceName)
{
	lfCharSet =DEFAULT_CHARSET;
	lfOutPrecision = 0;
	lfClipPrecision = 0;
	lfQuality = 0;
	lfPitchAndFamily = 0;
	LOGFONT LogFont;
	LogFont.lfHeight=lfHeight;
	LogFont.lfWidth=lfWidth;
	LogFont.lfEscapement=lfEscapement;
	LogFont.lfOrientation=lfOrientation;
	LogFont.lfWeight=lfWeight;
	LogFont.lfItalic=lfItalic;
	LogFont.lfUnderline=lfUnderline;
	LogFont.lfStrikeOut=lfStrikeOut;
	LogFont.lfCharSet=lfCharSet;
	LogFont.lfOutPrecision=lfOutPrecision;
	LogFont.lfClipPrecision=lfClipPrecision;
	LogFont.lfQuality=lfQuality;
	LogFont.lfPitchAndFamily=lfPitchAndFamily;

#ifdef UNICODE
	wcscpy(LogFont.lfFaceName,lfFaceName);
#else
	strcpy(LogFont.lfFaceName,lfFaceName);
#endif

	return(LogFont);
}



void DrawLine(CDC *cDC,int left,int top,int right,int bottom,CPen *cP,BOOL bDel)
{
	CPen *cOldB=cDC->SelectObject(cP);
	cDC->MoveTo(left,top);
	cDC->LineTo(right,bottom);
	cDC->SelectObject(cOldB);
	if(bDel)cP->DeleteObject();
}

void DrawShadowVertLine(CDC *cDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2)
{
//	cDC->Draw3dRect(iLeft-1,iTop,3,iLen,RGB(0,0,0),RGB(192,192,192));
	CPen cP(PS_SOLID,1,crColor1);
	CPen cP1(PS_SOLID,1,crColor2);
//	CPen cP2(PS_SOLID,1,RGB(192,192,192));
	DrawLine(cDC,iLeft,iTop,iLeft,iTop+iLen,&cP,TRUE);
	DrawLine(cDC,iLeft+1,iTop+2,iLeft+1,iTop+iLen,&cP1,TRUE);
//	DrawLine(cDC,iLeft+1,iTop,iLeft+1,iTop+iLen,&cP2);
}
void DrawShadowHorzLine(CDC *cDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2, long nDir)
{
//	cDC->Draw3dRect(iLeft-1,iTop,3,iLen,RGB(0,0,0),RGB(192,192,192));
	CPen cP(PS_SOLID,1,crColor1);//RGB(0,0,0));
	CPen cP1(PS_SOLID,1,crColor2);//RGB(230,230,230));
//	CPen cP2(PS_SOLID,1,RGB(192,192,192));
	DrawLine(cDC,iLeft,iTop,iLeft-iLen,iTop,&cP,TRUE);

	if (nDir == 0)
	{
		DrawLine(cDC,iLeft,iTop+1,iLeft-iLen+2,iTop+1,&cP1,TRUE);
	}
	else
	{
		DrawLine(cDC,iLeft,iTop+1,iLeft-iLen-2,iTop+1,&cP1,TRUE);
	}
//	DrawLine(cDC,iLeft+1,iTop,iLeft+1,iTop+iLen,&cP2);
}


void DrawRectBorder(CDC *pDC,CRect cR,COLORREF crColor)
{
	CPen pen(PS_SOLID,1,crColor);
	CPen *pOldPen = pDC->SelectObject(&pen);
	
	pDC->MoveTo(cR.left,cR.top);
	pDC->LineTo(cR.right,cR.top);
	pDC->LineTo(cR.right,cR.bottom);
	pDC->LineTo(cR.left,cR.bottom);
	pDC->LineTo(cR.left,cR.top);

	pen.DeleteObject();
	pDC->SelectObject(pOldPen);
}

void DrawRectBorder(CDC *pDC,long nLeft,long nTop,long nRight,long nBottom,COLORREF crColor)
{
	CPen pen(PS_SOLID,1,crColor);
	CPen *pOldPen = pDC->SelectObject(&pen);
	
	pDC->MoveTo(nLeft,nTop);
	pDC->LineTo(nRight,nTop);
	pDC->LineTo(nRight,nBottom);
	pDC->LineTo(nLeft,nBottom);
	pDC->LineTo(nLeft,nTop);
	
	pen.DeleteObject();
	pDC->SelectObject(pOldPen);	
}

void Draw3dRectByMe(CDC *cDC,CRect &cR,int iGap,COLORREF crLeftTop,COLORREF crRightBottom,COLORREF crBk)
{
	CPen cPen(PS_NULL,0,RGB(0,0,0));
	CBrush cBrush(crBk);
	CBrush *cOldB=cDC->SelectObject(&cBrush);
	CPen *cOldP=cDC->SelectObject(&cPen);
	cDC->Rectangle(&cR);
	cDC->SelectObject(cOldB);
	cDC->SelectObject(cOldP);
	cPen.DeleteObject();
	cBrush.DeleteObject();
	Draw3dRectBorder(cDC,cR,iGap,crLeftTop,crRightBottom);
}

void Draw3dRectBorder(CDC *cDC,CRect *cR,int iGap,COLORREF crLeftTop,COLORREF crRightBottom)
{
	Draw3dRectBorder(cDC, *cR, iGap, crLeftTop, crRightBottom);
}

void Draw3dRectBorder(CDC *cDC,CRect &cR,int iGap,COLORREF crLeftTop,COLORREF crRightBottom)
{
	CPen cP1(PS_SOLID,1,crLeftTop);
	CPen cP2(PS_SOLID,1,crRightBottom);
	int i=0;
	for (int i=0;i<iGap;i++)
	{
		DrawLine(cDC,cR.left+i,cR.top,cR.left+i,cR.bottom-i,&cP1,FALSE);
		DrawLine(cDC,cR.left+i,cR.bottom-i,cR.right,cR.bottom-i,&cP2,FALSE);
		DrawLine(cDC,cR.right-i,cR.bottom-i,cR.right-i,cR.top,&cP2,FALSE);
		DrawLine(cDC,cR.right-i,cR.top+i,cR.left,cR.top+i,&cP1,FALSE);
	}
	cP1.DeleteObject();
	cP2.DeleteObject();
}

long GetCharWidthByLogfont2(CDC *pDC,LOGFONT lf)
{
	long lfWidth = 0;
	
	CFont font;
	font.CreateFontIndirect(&lf);
	CFont *pOldFont=pDC->SelectObject(&font);
	
	CString str=_T("A");
	CSize size=pDC->GetTextExtent(str,str.GetLength());
	lfWidth = size.cx;
	
	pDC->SelectObject(pOldFont);
	font.DeleteObject();
	
	return lfWidth;
}


BOOL  CmDrawTextRect(CDC * hDC,const CString &lpStr,COLORREF crColor,CRect    *cR,
					 COLORREF crBK,LOGFONT  lfFont,UINT uBkMode,
					 UINT uFormat,long lShadow)
{
	return CmDrawTextRect(hDC, lpStr, crColor, *cR, crBK, lfFont, uBkMode, uFormat, lShadow);
}

BOOL  CmDrawTextRect(CDC * hDC, const CString &lpStr,COLORREF crColor,CRect    cR,
					 COLORREF crBK,LOGFONT  lfFont,UINT uBkMode,
					 UINT uFormat,long lShadow)
{
	CFont CF;
	CF.CreateFontIndirect(&lfFont);
	CFont *c=hDC->SelectObject(&CF);
	hDC->SetBkColor(crBK);
	hDC->SetBkMode(uBkMode);

	CRect rcCal = cR;
#ifdef UNICODE
	hDC->DrawText(lpStr,wcslen(lpStr),rcCal, DT_CALCRECT );
#else
	hDC->DrawText(lpStr,strlen(lpStr),rcCal,DT_CALCRECT);
#endif

	long nLines = rcCal.Width() / cR.Width();

	if (rcCal.Width() > cR.Width() * nLines)
	{
		nLines++;
	}
	
	COLORREF Color;
	int i=0;
	for (i=0;i<3;i++)
	{
		CRect cR1=cR;

		if (i==0)
		{
			if (lShadow==0)
				continue;

			if (lShadow<0)
				Color=RGB(0,0,0);
			else 
				Color=RGB(255,255,255);

			CPoint point(abs(lShadow)*(-1),abs(lShadow)*(-1));
			cR1.OffsetRect(point);
		}
		else
		{
			if (i==1)
			{
				if (lShadow==0) 
					continue;

				if (lShadow>0)
					Color=RGB(0,0,0);
				else 
					Color=RGB(255,255,255);

				CPoint point(abs(lShadow),abs(lShadow));
				cR1.OffsetRect(point);
			}
			else 
				Color=crColor;
		}

		hDC->SetTextColor(Color);

		if (uFormat&DT_VCENTER)
		{
			long lGap = (abs(lfFont.lfHeight)+2) * nLines;
			long lHeight = cR1.Height();
			cR1.top += (lHeight-lGap)/2;
			cR1.bottom -= (lHeight-lGap)/2;
			cR1.bottom += 1;
		}

#ifdef UNICODE
		hDC->DrawText(lpStr,wcslen(lpStr),cR1,uFormat);
#else
		hDC->DrawText(lpStr,strlen(lpStr),cR1,uFormat);
#endif
	}
	hDC->SelectObject(c);
	CF.DeleteObject();
	return(TRUE);
}

BOOL  CmGetDrawTextRect(CDC * hDC,LPCTSTR lpStr,CRect    &cR,LOGFONT  lfFont,UINT uFormat)
{
	
	CFont CF;
	CF.CreateFontIndirect(&lfFont);
	CFont *c=hDC->SelectObject(&CF);
	CRect cR1=cR;
	if (uFormat&DT_VCENTER){
		long lGap=abs(lfFont.lfHeight);
		long lHeight=cR1.Height();
		cR1.top+=(lHeight-lGap)/2;
		cR1.bottom-=(lHeight-lGap)/2;
	}
	hDC->DrawText(lpStr,lstrlen(lpStr),cR1,
		uFormat|DT_CALCRECT);
	cR=cR1;
	hDC->SelectObject(c);
	CF.DeleteObject();
	return(TRUE);
}


void DrawExpandBoxRect(long xCenter,long yCenter,BOOL bExpand,CDC *pDC)
{
	COLORREF cr = RGB(128,128,128);
	CPen pen(PS_SOLID,1,cr);
	CPen *pOldPen = pDC->SelectObject(&pen);

	CRect rectBtn;
	GetExpandBoxRect(xCenter,yCenter,rectBtn);

	//pDC->Draw3dRect(rectBtn,cr,cr);
	pDC->MoveTo(rectBtn.left,rectBtn.top);
	pDC->LineTo(rectBtn.right,rectBtn.top);
	pDC->LineTo(rectBtn.right,rectBtn.bottom);
	pDC->LineTo(rectBtn.left,rectBtn.bottom);
	pDC->LineTo(rectBtn.left,rectBtn.top);
	if (bExpand)
	{
		pDC->MoveTo(xCenter-2,yCenter);
		pDC->LineTo(xCenter+3,yCenter);
	}
	else
	{
		pDC->MoveTo(xCenter-2,yCenter);
		pDC->LineTo(xCenter+3,yCenter);
		pDC->MoveTo(xCenter,yCenter-2);
		pDC->LineTo(xCenter,yCenter+3);
	}
	pDC->SelectObject(pOldPen);
	//pen.DeleteObject();
}

void DrawCheckBoxRect(long xCenter,long yCenter,long nCheckState,CDC *pDC,BOOL bEnable)
{

	COLORREF crFrm = RGB(29,82,128);
	COLORREF crChk = RGB(34,161,34);

	if (!bEnable)
	{
		crFrm = RGB(128,128,128);
		crChk = RGB(192,192,192);
	}

	long xp1 = xCenter-3;
	long yp1 = yCenter-1;
	long xp2 = xCenter-1;
	long yp2 = yCenter+1;
	long xp3 = xCenter+4;
	long yp3 = yCenter-4;

	//±ß¿ò
	CRect rectBtn;
	GetCheckBoxRect(xCenter,yCenter,rectBtn);
	
	pDC->MoveTo(rectBtn.left,rectBtn.top);
	pDC->LineTo(rectBtn.right,rectBtn.top);
	pDC->LineTo(rectBtn.right,rectBtn.bottom);
	pDC->LineTo(rectBtn.left,rectBtn.bottom);
	pDC->LineTo(rectBtn.left,rectBtn.top);
	
	CBrush brush(RGB(255,255,255));
	rectBtn.DeflateRect(1,1,1,1);
	pDC->FillRect(rectBtn,&brush);
	brush.DeleteObject();
	
	//Ñ¡ÖÐ
	CPen pen(PS_SOLID,1,crChk);
	CPen *pOldPen = pDC->SelectObject(&pen);
	if (nCheckState == 1)
	{
		pDC->MoveTo(xp1,yp1);
		pDC->LineTo(xp2,yp2);
		pDC->LineTo(xp3,yp3);
		yp1++;		yp2++;		yp3++;
		pDC->MoveTo(xp1,yp1);
		pDC->LineTo(xp2,yp2);
		pDC->LineTo(xp3,yp3);
		yp1++;		yp2++;		yp3++;
		pDC->MoveTo(xp1,yp1);
		pDC->LineTo(xp2,yp2);
		pDC->LineTo(xp3,yp3);
	}
	else if (nCheckState == 2)
	{
		CRect rect(xCenter-3,yCenter-3,xCenter+4,yCenter+4);
		CBrush brush(crChk);
		pDC->FillRect(&rect,&brush);
		brush.DeleteObject();
	}

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}



BOOL IsLowResolution(HDC hDC)
{
	if (hDC)
	{
		int nColors = ::GetDeviceCaps(hDC, BITSPIXEL);			
		return (nColors > 0 && nColors <= 8);
		
	}
	hDC = ::GetDC(::GetDesktopWindow());
	if (hDC)
	{
		int nColors = ::GetDeviceCaps(hDC, BITSPIXEL);
		::ReleaseDC(::GetDesktopWindow(), hDC);
		
		return (nColors > 0 && nColors <= 8);
	}
	return FALSE;
}

PFNGRADIENTFILL g_pfnFastGradientFill = NULL;
HMODULE g_hLibMsImg = NULL;

COLORREF BlendColors(COLORREF crA, COLORREF crB, float fAmountA)
{
	BYTE btRed = (BYTE)min(255, (int)(GetRValue(crA) * fAmountA + GetRValue(crB) * (1.0f - fAmountA)));
	BYTE btGreen = (BYTE)min(255, (int)(GetGValue(crA) * fAmountA + GetGValue(crB) * (1.0f - fAmountA)));
	BYTE btBlue = (BYTE)min(255, (int)(GetBValue(crA) * fAmountA + GetBValue(crB) * (1.0f - fAmountA)));
	
	return RGB(btRed, btGreen, btBlue);
}

void GradientFill(CDC* pDC, LPRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz)
{
	if (!lpRect)
		return;
	
	if (::IsRectEmpty(lpRect))
		return;
	
	if (IsLowResolution(pDC->GetSafeHdc()))
	{
		pDC->FillSolidRect(lpRect, crFrom);
	} 
	else if (crFrom == crTo)
	{
		pDC->FillSolidRect(lpRect, crFrom);
	} 
	else if (g_pfnFastGradientFill)
	{
		GradientFillFast(pDC, lpRect, crFrom, crTo, bHorz);
	}
	else
	{
		GradientFillSlow(pDC, lpRect, crFrom, crTo, bHorz);
	}
}

void GradientFillSlow(CDC* pDC, LPRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz)
{
	int nWidth = max(1, lpRect->right - lpRect->left);
	int nHeight = max(1, lpRect->bottom - lpRect->top);
	
	CRect rc;
	pDC->GetClipBox(&rc);
	if (rc.IsRectEmpty()) rc = *lpRect;
	else rc.IntersectRect(rc, lpRect);
	
	if (bHorz)
	{
		for (int nX = rc.left; nX < rc.right; nX++)
			pDC->FillSolidRect(nX, rc.top, 1, rc.Height(), BlendColors(crFrom, crTo, (float)(1.0 - ((nX - lpRect->left) / (float)nWidth))));
	}
	else
	{
		for (int nY = rc.top; nY < rc.bottom; nY++)
			pDC->FillSolidRect(rc.left, nY, rc.Width(), 1, BlendColors(crFrom, crTo, (float)(1.0 - ((nY - lpRect->top)) / (float)nHeight)));
	}
}


void GradientFillFast(CDC* pDC, LPRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz)
{
	TRIVERTEX vert[2];
	vert[0].x      = lpRect->left;
	vert[0].y      = lpRect->top;
	vert[0].Red    = (COLOR16)(GetRValue(crFrom) << 8);
	vert[0].Green  = (COLOR16)(GetGValue(crFrom) << 8);
	vert[0].Blue   = (COLOR16)(GetBValue(crFrom) << 8);
	vert[0].Alpha  = 0x0000;
	
	vert[1].x      = lpRect->right;
	vert[1].y      = lpRect->bottom; 
	vert[1].Red    = (COLOR16)(GetRValue(crTo) << 8);
	vert[1].Green  = (COLOR16)(GetGValue(crTo) << 8);
	vert[1].Blue   = (COLOR16)(GetBValue(crTo) << 8);
	vert[1].Alpha  = 0x0000;
	
	GRADIENT_RECT gRect = { 0, 1 };
	
	g_pfnFastGradientFill(*pDC, vert, 2, &gRect, 1, bHorz ? GRADIENT_FILL_RECT_H : GRADIENT_FILL_RECT_V);
}


void DrawTransparentBitmap(CDC *pDC, UINT IDImage,CRect &rect, COLORREF rgbMask, BOOL bEnable)
{
	CBitmap Image;
	Image.LoadBitmap(IDImage);
	DrawTransparentBitmap(pDC, &Image, rect, rgbMask,bEnable);
}

void DrawTransparentBitmap(CDC *pDC, CBitmap *pBmp, CRect &rect, COLORREF rgbMask, BOOL bEnable)
{
	CDC ImageDC,MaskDC;
	CBitmap *pOldImage;
	CBitmap maskBitmap,*pOldMaskDCBitmap ;

	ImageDC.CreateCompatibleDC(pDC);
	pOldImage=ImageDC.SelectObject(pBmp);
	MaskDC.CreateCompatibleDC(pDC);
	maskBitmap.CreateBitmap( rect.Width(), rect.Height(), 1, 1, NULL );
	pOldMaskDCBitmap = MaskDC.SelectObject( &maskBitmap );
	ImageDC.SetBkColor(rgbMask);
	MaskDC.BitBlt( 0, 0, rect.Width(), rect.Height(), &ImageDC, 0, 0, SRCCOPY );
	
	ImageDC.SetBkColor(RGB(0,0,0));
	ImageDC.SetTextColor(RGB(255,255,255));
	ImageDC.BitBlt(0, 0, rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND);
	pDC->BitBlt(rect.left,rect.top,rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND);
	pDC->BitBlt(rect.left,rect.top,rect.Width(), rect.Height(), &ImageDC, 0, 0,SRCPAINT);
	MaskDC.SelectObject(pOldMaskDCBitmap);
	ImageDC.SelectObject(pOldImage);
}

CFont *g_pGlobalFont11 = NULL;
CFont *g_pGlobalFont12 = NULL;
CFont *g_pGlobalFont = NULL;
CFont *g_pGlobalFont14 = NULL;
CFont *g_pGlobalFont15 = NULL;
CFont *g_pGlobalFont16 = NULL;
CFont *g_pGlobalFont18 = NULL;
CFont *g_pGlobalFont20 = NULL;
CFont *g_pGlobalFont24 = NULL;



class _CInitGlobalFont_
{
public:
	static void _New_Font(LOGFONT &lf, long lfHeight, CFont **ppFont)
	{
		lf.lfHeight = lfHeight;
		*ppFont = new CFont();
		(*ppFont)->CreateFontIndirect(&lf);
	}

	_CInitGlobalFont_()
	{
		LOGFONT lf;
		lf = InitLogFont();
		lf.lfHeight = -13;
		lf.lfWeight = 400;

		g_lfGlobalFont11 = lf;
		g_lfGlobalFont12 = lf;
		g_lfGlobalFont = lf;
		g_lfGlobalFont14 = lf;
		g_lfGlobalFont15 = lf;
		g_lfGlobalFont16 = lf;
		g_lfGlobalFont18 = lf;
		g_lfGlobalFont20 = lf;
		g_lfGlobalFont24 = lf;
		
		_New_Font(g_lfGlobalFont11, -11, &g_pGlobalFont11);
		_New_Font(g_lfGlobalFont12, -12, &g_pGlobalFont12);
		_New_Font(g_lfGlobalFont, -13, &g_pGlobalFont);
		_New_Font(g_lfGlobalFont14, -14, &g_pGlobalFont14);
		_New_Font(g_lfGlobalFont15, -15, &g_pGlobalFont15);
		_New_Font(g_lfGlobalFont16, -16, &g_pGlobalFont16);
		_New_Font(g_lfGlobalFont18, -18, &g_pGlobalFont18);
		_New_Font(g_lfGlobalFont20, -20, &g_pGlobalFont20);
		_New_Font(g_lfGlobalFont24, -24, &g_pGlobalFont24);
	}
	virtual ~_CInitGlobalFont_()
	{
		delete g_pGlobalFont11;		g_pGlobalFont11 = NULL;
		delete g_pGlobalFont12;		g_pGlobalFont12 = NULL;
		delete g_pGlobalFont;		g_pGlobalFont = NULL;
		delete g_pGlobalFont14;		g_pGlobalFont14 = NULL;
		delete g_pGlobalFont15;		g_pGlobalFont15 = NULL;
		delete g_pGlobalFont16;		g_pGlobalFont16 = NULL;
		delete g_pGlobalFont18;		g_pGlobalFont18 = NULL;
		delete g_pGlobalFont20;		g_pGlobalFont20 = NULL;
		delete g_pGlobalFont24;		g_pGlobalFont24 = NULL;
	}
}g_oInitGlobalFont;

CFont* font_CreateNew(LOGFONT &lf, long lfHeight)
{
	CFont *pNew = NULL;
	g_oInitGlobalFont._New_Font(lf, lfHeight, &pNew);
	return pNew;
}

CFont* GetGlobalFontBySize(long nSize)
{
	if (nSize < 0)
	{
		nSize = -nSize;
	}

	if (nSize < 11)
	{
		return g_pGlobalFont;
	}
	else if (nSize == 11)
	{
		return g_pGlobalFont11;
	}
	else if (nSize == 12)
	{
		return g_pGlobalFont12;
	}
	else if (nSize <= 14)
	{
		return g_pGlobalFont14;
	}
	else if (nSize == 15)
	{
		return g_pGlobalFont15;
	}
	else if (nSize == 16)
	{
		return g_pGlobalFont16;
	}
	else if (nSize <= 18)
	{
		return g_pGlobalFont18;
	}
	else if (nSize <= 20)
	{
		return g_pGlobalFont20;
	}
	else
	{
		return g_pGlobalFont14;
	}
}

#endif

LOGFONT g_lfGlobalFont11;
LOGFONT g_lfGlobalFont12;
LOGFONT g_lfGlobalFont;
LOGFONT g_lfGlobalFont14;
LOGFONT g_lfGlobalFont15;
LOGFONT g_lfGlobalFont16;
LOGFONT g_lfGlobalFont18;
LOGFONT g_lfGlobalFont20;
LOGFONT g_lfGlobalFont24;
