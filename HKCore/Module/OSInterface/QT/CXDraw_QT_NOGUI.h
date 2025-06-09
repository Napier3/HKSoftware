#ifndef _CXDraw_QT_NOGUI_h_
#define _CXDraw_QT_NOGUI_h_

#include "XGlobalDefine_QT.h"

#include "CXDrawTypes_QT.h"

#ifdef _PSX_QT_LINUX_

typedef struct tagTEXTMETRIC
{
    LONG tmHeight;
    LONG tmAscent;
    LONG tmDescent;
    LONG tmInternalLeading;
    LONG tmExternalLeading;
    LONG tmAveCharWidth;
    LONG tmMaxCharWidth;
    LONG tmWeight;
    LONG tmOverhang;
    LONG tmDigitizedAspectX;
    LONG tmDigitizedAspectY;
    CHAR       tmFirstChar;
    CHAR       tmLastChar;
    CHAR       tmDefaultChar;
    CHAR       tmBreakChar;
    BYTE        tmItalic;
    BYTE        tmUnderlined;
    BYTE        tmStruckOut;
    BYTE        tmPitchAndFamily;
    BYTE        tmCharSet;
} TEXTMETRIC, *PTEXTMETRIC;

/*typedef struct tagPOINT
{
    LONG x;
    LONG y;
} 	POINT;
*/

//LOGFONT

typedef struct tagLOGFONTA_QT
{
    LONG lfHeight;
    LONG lfWidth;
    LONG lfEscapement;
    LONG lfOrientation;
    LONG lfWeight;
    BYTE lfItalic;
    BYTE lfUnderline;
    BYTE lfStrikeOut;
    BYTE lfCharSet;
    BYTE lfOutPrecision;
    BYTE lfClipPrecision;
    BYTE lfQuality;
    BYTE lfPitchAndFamily;
    char lfFaceName[ 32 ];
}LOGFONTA;

typedef tagLOGFONTA_QT LOGFONT;


//LOGBRUSH
typedef struct tagLOGBRUSH_QT
{
    UINT        lbStyle;
    COLORREF    lbColor;
    LONG        lbHatch;
} LOGBRUSH, *PLOGBRUSH;


//Logical Pe
typedef struct tagLOGPEN_QT
{
    UINT        lopnStyle;
    POINT       lopnWidth;
    COLORREF    lopnColor;
} LOGPEN, *PLOGPEN;

#endif

class CFont
{
public:
    CFont()
    {
    }

    void CreateFontIndirect(LOGFONT  &lfFont)
    {
 
    }
    void CreateFontIndirect(LOGFONT *pLfFont)
    {
   
    }
    void DeleteObject(){}
};

class CPen
{
public:
    CPen()
    {
    }
    CPen(int nPenStyle, int nWidth, COLORREF crColor)
    {
    }

    void CreatePen(int nPenStyle, int nWidth, COLORREF crColor)
    {

    }
    void CreatePenIndirect(LOGPEN &logPen)
    {
    }
    void CreatePenIndirect(LOGPEN *logPen)
    {
    }

    void DeleteObject()
    {

    }
};

class CBrush
{
public:
    CBrush()
    {

    }
    CBrush(COLORREF cr)
    {
    }

    void CreateSolidBrush(COLORREF crColor)
    {
    }

    void DeleteObject()
    {

    }
};

class CGdiObject
{
public:
    CGdiObject()
    {
    }


};

class CDC
{
public:
    CDC()
    {
    }

    CPen* SelectObject(CPen &pen)
    {
        return NULL;
    }
    CPen* SelectObject(CPen *pPen)
    {
         return NULL;
    }
    CBrush* SelectObject(CBrush &brush)
    {
        return NULL;
    }
    CBrush* SelectObject(CBrush *pBrush)
    {
        return NULL;
    }
    CFont* SelectObject(CFont &font)
    {
        return NULL;
    }
    CFont* SelectObject(CFont *pFont)
    {
        return NULL;
    }
    CGdiObject* SelectObject(CGdiObject *pObject)
    {
        return NULL;
    }

    CGdiObject* SelectStockObject(int nIndex)
    {
 			return NULL;
    }

    int SetBkMode(int nBkMode)
    {
    }

    void Ellipse(CRect &rect)
    {
    }
    void FillRect(CRect &rect, CBrush* pBrush)
    {
    }
    void FillRect(CRect *pRect, CBrush* pBrush)
    {
    }

    void MoveTo(CPoint &pt)
    {
    }
    void LineTo(CPoint &pt)
    {
    }
    void MoveTo(int x, int y)
    {
    }
    void LineTo(int x, int y)
    {
    }
     void Polyline(CPoint *pPoints, int nPoints)
    {
    }
   void Polygon(CPoint *pPoints, int nPoints)
    {
    }
    void Rectangle(int x1, int y1, int x2, int y2)
    {
    }
    void Rectangle(CRect &rect)
    {
    }
    void Rectangle(CRect *pRect)
    {
    }
    void Arc(const CRect &rcCircle,const CPoint &ptBegin, const CPoint &ptEnd)
    {
    }

    COLORREF SetBkColor(COLORREF crColor)
    {
        return 0;
    }
    COLORREF SetTextColor(COLORREF crColor)
    {
        return 0;
    }

    CSize GetTextExtent(CString &strText, long nCount=0)
    {
    	CSize sz;
    	return sz;
    }
    void DrawText(const CString& str, CRect &rect, UINT nFormat)
    {
    }
    void FillSolidRect(CRect &rc, COLORREF cr)
    {
    }
    void FillSolidRect(CRect *rc, COLORREF cr)
    {
    }

    int SetROP2(int nDrawMode)
    {
		return 0;
    }

    void SetPixel(int x, int y, COLORREF crColor)
    {
    }

    void SetPixel(POINT point, COLORREF crColor)
    {
    }

    BOOL GetTextMetrics(PTEXTMETRIC lpMetrics) const
    {
		return FALSE;
    }
};

class CBitmap
{
public:
    CBitmap(int width, int height, int nFormat=0)
    {

    }

    virtual ~CBitmap()
    {

    }

};

#endif   //_CXDraw_QT_NOGUI_h_
