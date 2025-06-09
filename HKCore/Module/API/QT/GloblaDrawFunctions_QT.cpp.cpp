#include "stdafx.h"
#include "..\GloblaDrawFunctions.h"
#include "..\StringApi.h"

void CmDrawText_CalRect(CDC *pDC, CRect &rc, const CString &strText, UINT uFormat)
{
    QRect textrect = pDC->fontMetrics().boundingRect(strText);
    rc.left = textrect.left();
    rc.top = textrect.top();
    rc.bottom = textrect.bottom();
    rc.right = textrect.right();
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

#ifdef OS_QT_LINUX
    LogFont.lfHeight=abs(lfHeight);
    LogFont.lfWidth=abs(lfWidth);

#else
    LogFont.lfHeight=lfHeight;
    LogFont.lfWidth=lfWidth;
#endif

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

#ifdef OS_QT_LINUX

    CString_to_char(lfFaceName, LogFont.lfFaceName);

#else //#ifdef OS_QT_LINUX

#ifdef UNICODE
    CString_to_wchar(lfFaceName, LogFont.lfFaceName);
#else
    CString_to_char(lfFaceName, LogFont.lfFaceName);
#endif

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

    for (i=0;i<iGap;i++)
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
    return CmDrawTextRect(hDC,lpStr,crColor,*cR,
                          crBK,lfFont,uBkMode,
                          uFormat,lShadow);
}

BOOL  CmDrawTextRect(CDC * hDC,const CString &lpStr,COLORREF crColor,CRect    cR,
                     COLORREF crBK,LOGFONT  lfFont,UINT uBkMode,
                     UINT uFormat,long lShadow)
{
    CFont CF;
    CF.CreateFontIndirect(&lfFont);
    CFont *c=hDC->SelectObject(&CF);
    hDC->SetBkColor(crBK);
    hDC->SetBkMode(uBkMode);

    CRect rcCal = cR;

    //2019-10-10 QT
    CmDrawText_CalRect(hDC, rcCal, lpStr, DT_LEFT);
/*#ifdef UNICODE
    hDC->DrawText(lpStr,wcslen(lpStr),rcCal, DT_CALCRECT );
#else
    hDC->DrawText(lpStr,strlen(lpStr),rcCal,DT_CALCRECT);
#endif*/

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

#ifndef OS_QT_LINUX
    #ifdef UNICODE
            hDC->DrawText(lpStr,wcslen(lpStr),cR1,uFormat);
    #else
            hDC->DrawText(lpStr,strlen(lpStr),cR1,uFormat);
    #endif
#else
        hDC->DrawText(lpStr, cR1, uFormat);
#endif
    }
    hDC->SelectObject(c);
    CF.DeleteObject();
    return(TRUE);
}

BOOL  CmGetDrawTextRect(CDC * hDC,const CString &lpStr,CRect    &cR,LOGFONT  lfFont,UINT uFormat)
{

    CFont CF;
    CF.CreateFontIndirect(&lfFont);
    CFont *c=hDC->SelectObject(&CF);
    CRect cR1=cR;

    if (uFormat&DT_VCENTER)
    {
        long lGap=abs(lfFont.lfHeight);
        long lHeight=cR1.Height();
        cR1.top+=(lHeight-lGap)/2;
        cR1.bottom-=(lHeight-lGap)/2;
    }

    //2019-10-10 QT
    CmDrawText_CalRect(hDC, cR1, lpStr, DT_LEFT);
    /*hDC->DrawText(lpStr,lstrlen(lpStr),cR1,
        uFormat|DT_CALCRECT);*/

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

    //�߿�
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

    //ѡ��
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


/*
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
*/
