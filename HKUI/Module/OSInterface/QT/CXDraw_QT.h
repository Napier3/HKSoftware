#ifndef _CXDraw_qt_h__
#define _CXDraw_qt_h__

#ifdef _PSX_QT_LINUX_
#define HDC  void*
#endif

#include <qpoint.h>
#include <qrect.h>

#ifndef _USE_NO_GUI_
#include <qpainter.h>
#include <qpaintdevice.h>
#endif

#include <qsize.h>
//#include <qnamespace.h>
#include "XGlobalDefine_QT.h"

#include "CXDrawTypes_QT.h"
#include "CString_QT.h"

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

#ifndef _USE_NO_GUI_
inline COLORREF QColor_to_COLORREF(QColor &cr)
{
    int red = cr.red();
    int green = cr.green();
    int blue = cr.blue();
    return RGB(red, green, blue);
}

inline QColor COLORREF_to_QColor(const COLORREF &cr)//zhouhj 20210203 增加用于转换
{
	int r = cr & 0xFF;//zhouhj 20210203 两者之间需要转换
	int g = (cr >> 8) & 0xFF;
	int b = (cr >> 16) & 0xFF;
	return QColor(r,g,b);
}

inline void UINT_TxtFormat_to_QTextOption(UINT nFormat, QTextOption &oTxtOption)
{
    UINT n_DT_CENTER = nFormat & DT_CENTER;
    UINT n_DT_RIGHT = nFormat & DT_RIGHT;
    UINT n_DT_VCENTER = nFormat & DT_VCENTER;
    UINT n_DT_BOTTOM = nFormat & DT_BOTTOM;
    UINT n_DT_WORDBREAK = nFormat & DT_WORDBREAK;
/*
    UINT n_DT_SINGLELINE = nFormat & DT_SINGLELINE;
    UINT n_DT_EXPANDTABS = nFormat & DT_EXPANDTABS;
    UINT n_DT_TABSTOP = nFormat & DT_TABSTOP;
    UINT n_DT_NOCLIP = nFormat & DT_NOCLIP;
    UINT n_DT_EXTERNALLEADING = nFormat & DT_EXTERNALLEADING;
*/

    if (n_DT_VCENTER > 0 && n_DT_CENTER > 0)
    {
        oTxtOption.setAlignment(Qt::AlignCenter);
    }
    else
    {
        if (n_DT_VCENTER > 0 || n_DT_CENTER > 0)
        {
            if (n_DT_VCENTER > 0)
            {
                oTxtOption.setAlignment(Qt::AlignVCenter);
            }
            if (n_DT_CENTER > 0)
            {
                oTxtOption.setAlignment(Qt::AlignHCenter);
            }
        }
        else
        {
            if (n_DT_RIGHT > 0)
            {
                oTxtOption.setAlignment(Qt::AlignRight);
            }
            if (n_DT_BOTTOM > 0)
            {
                oTxtOption.setAlignment(Qt::AlignBottom);
            }
        }
    }

    if (n_DT_WORDBREAK > 0)
    {
        oTxtOption.setWrapMode(QTextOption::WordWrap);
    }
}
#endif

#ifndef _USE_NO_GUI_
class CFont : public QFont
#else
class CFont
#endif
{
public:
    CFont()
    {
    }
#ifndef _USE_NO_GUI_
    CFont(const QFont &font)
      : QFont(font)
    {

    }
#endif
    void CreateFontIndirect(LOGFONT  &lfFont)
    {
#ifndef _USE_NO_GUI_
        CString strName;
        strName = lfFont.lfFaceName;
        setFamily(strName);

		if (lfFont.lfWeight == 300)//zhouhj 20210202 对照Qt库中字体重新设置
        {
			setWeight(QFont::Light);
		}
		else if (lfFont.lfWeight == 500)
		{
			setWeight(QFont::DemiBold);
        }
		else if (lfFont.lfWeight == 600)
        {
            setWeight(QFont::Black);
        }
		else if (lfFont.lfWeight == 700)
		{
			setWeight(QFont::Bold);
		}
        else
        {
			setWeight(QFont::Normal);
        }

//         if (lfFont.lfWeight < 400)
//         {
//             setWeight(QFont::Normal);
//         }
//         else if (lfFont.lfWeight <= 600)
//         {
//             setWeight(QFont::Black);
//         }
//         else
//         {
//             setWeight(QFont::Bold);
//         }

        /*setPointSize*/setPixelSize(abs(lfFont.lfHeight));//zhouhj 20210201 需要保证为正数 ,setPixelSize字面意思是字体高度占用的像素px大小,setPointSize字面意思是字体高度占用的可物理测量的长度磅（point）pt大小，一般用于印刷领域。
//        setBold(lfFont.lfWidth > 0);//是否加粗是通过lfWeight来判断  zhouhj 20210202
        setItalic(lfFont.lfItalic);
        setUnderline(lfFont.lfUnderline);
        setOverline(lfFont.lfOutPrecision);
#endif
    }
    void CreateFontIndirect(LOGFONT *pLfFont)
    {
        CreateFontIndirect(*pLfFont);
    }
    void DeleteObject(){}
};

#ifndef _USE_NO_GUI_
class CPen : public QPen
#else
class CPen
#endif
{
public:
    CPen()
    {
    }
#ifndef _USE_NO_GUI_
    CPen(const QPen &pen)
      : QPen(pen)
    {

    }
#endif

    CPen(int nPenStyle, int nWidth, COLORREF crColor)
    {
        CreatePen(nPenStyle, nWidth, crColor);
    }

    void CreatePen(int nPenStyle, int nWidth, COLORREF crColor)
    {
#ifndef _USE_NO_GUI_
        if (PS_SOLID == nPenStyle)
        {
            setStyle(Qt::SolidLine);
        }
        else if (PS_DASH == nPenStyle)
        {
            setStyle(Qt::DashLine);
        }
        else if (PS_DOT == nPenStyle)
        {
            setStyle(Qt::DotLine);
        }
        else if (PS_DASHDOT == nPenStyle)
        {
            setStyle(Qt::DashDotLine);
        }
        else if (PS_DASHDOTDOT == nPenStyle)
        {
            setStyle(Qt::DashDotDotLine);
        }
        else if (PS_NULL == nPenStyle)
        {
            setStyle(Qt::NoPen);
        }
        else
        {
            setStyle(Qt::SolidLine);
        }

        setWidth(nWidth);
// 		int r = crColor & 0xFF;
// 		int g = (crColor >> 8) & 0xFF;
// 		int b = (crColor >> 16) & 0xFF;
		QColor cr = COLORREF_to_QColor(crColor);
        setColor(cr);//zhouhj 20210201 之前缺少转换
#endif
    }
    void CreatePenIndirect(LOGPEN &logPen)
    {
        CreatePen(logPen.lopnStyle, logPen.lopnWidth.x, logPen.lopnColor);
    }
    void CreatePenIndirect(LOGPEN *logPen)
    {
        CreatePen(logPen->lopnStyle, logPen->lopnWidth.x, logPen->lopnColor);
    }

    void DeleteObject()
    {

    }
};

#ifndef _USE_NO_GUI_
class CBrush : public QBrush
#else
class CBrush
#endif
{
public:
    CBrush()
    {

    }
    CBrush(COLORREF cr)
    {
        CreateSolidBrush(cr);
    }
#ifndef _USE_NO_GUI_
    CBrush(const QBrush &brush)
      : QBrush(brush)
    {

    }
#endif
    void CreateSolidBrush(COLORREF crColor)
    {
        //#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
//         int r = crColor & 0xFF;
//         int g = (crColor >> 8) & 0xFF;
//         int b = (crColor >> 16) & 0xFF;
#ifndef _USE_NO_GUI_
        QColor cr = COLORREF_to_QColor(crColor);
        setColor(cr);
#endif
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

//2021-9-18  lijunqing
#ifndef _USE_NO_GUI_
class CRgn : public QRegion
#else
class CRgn
#endif
{
public:
	CRgn()
	{
	}

	~CRgn(){}

	BOOL CreateRectRgn(int x1, int y1, int x2, int y2)
	{
#ifndef _USE_NO_GUI_
        QRegion rgn(x1, y1, x2, y2);
		(QRegion &)(*this) = rgn;
#endif
        return TRUE;
	}

	void DeleteObject()
	{
	
	}
	void CreateRectRgnIndirect(const CRect &rc)
	{
		CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	}

};

#ifndef _USE_NO_GUI_
class CDC : public QPainter
#else
class CDC
#endif
{
public:
    CDC()
    {
        m_bHasListPoint = FALSE;
    }
#ifndef _USE_NO_GUI_
    CDC(QPaintDevice *pDevice)
        : QPainter(pDevice)
    {
        m_bHasListPoint = FALSE;
    }
#endif

    CPen* SelectObject(CPen &open)
    {
#ifndef _USE_NO_GUI_
        const QPen &old = pen();
        setPen((QPen&)open);

        return (CPen*)(&old);
#else
        return 0;
#endif
    }
    CPen* SelectObject(CPen *pPen)
    {
#ifndef _USE_NO_GUI_
        const QPen &old = pen();

        if (pPen != NULL)
        {
            setPen((QPen&)*pPen);
        }

        return (CPen*)(&old);
#else
        return 0;
#endif
    }
    CBrush* SelectObject(CBrush &oBrush)
    {
#ifndef _USE_NO_GUI_
        const QBrush &old = brush();
        setBrush((CBrush&)oBrush);
        return (CBrush*)(&old);
#else
        return 0;
#endif
    }
    CBrush* SelectObject(CBrush *pBrush)
    {
#ifndef _USE_NO_GUI_
        const QBrush &old = brush();
        if (pBrush != NULL)
        {
            setBrush((CBrush&)*pBrush);
        }

        return (CBrush*)(&old);
#else
        return 0;
#endif
    }
    CFont* SelectObject(CFont &oFont)
    {
#ifndef _USE_NO_GUI_
        const QFont &old = font();
        setFont((CFont&)oFont);
        return (CFont*)(&old);
#else
        return 0;
#endif
    }
    CFont* SelectObject(CFont *pFont)
    {
#ifndef _USE_NO_GUI_
        const QFont &old = font();

        if (pFont != NULL)
        {
            setFont((CFont&)*pFont);
        }

         return (CFont*)(&old);
#else
        return 0;
#endif
    }
    CGdiObject* SelectObject(CGdiObject *pObject)
    {
        if (pObject != NULL)
        {
            //setBrush((CBrush&)*pBrush);
        }

        return NULL;
    }

    CGdiObject* SelectStockObject(int nIndex)
    {
#ifndef _USE_NO_GUI_
        if (NULL_BRUSH == nIndex)
        {
            //QBrush brush(QT::NoBrush);
            setBrush(Qt::NoBrush);
        }
        else if (NULL_PEN == nIndex)
        {
            setPen(Qt::NoPen);
        }
        else
        {
            Q_ASSERT(false);
        }
#else
#endif

		return NULL;
    }

    int SetBkMode(int nBkMode)
    {
#ifndef _USE_NO_GUI_
        Qt::BGMode mode = backgroundMode();

        //void setBackgroundMode(Qt::BGMode mode);
        if (TRANSPARENT == nBkMode)
        {
            setBackgroundMode(Qt::TransparentMode);
        }
        else
        {
            setBackgroundMode(Qt::OpaqueMode);
        }

        if (mode == Qt::TransparentMode)
        {
            return TRANSPARENT;
        }
        else
        {
            return OPAQUE;
        }
#else
        return 0;
#endif
    }

    void Ellipse(CRect &rect)
    {
        //QPainter::drawEllipse(int x, int y, int w, int h)
#ifndef _USE_NO_GUI_
        drawEllipse(rect.left, rect.top, rect.Width(), rect.Height());
#endif
    }
    void FillRect(CRect &rect, CBrush* pBrush)
    {
#ifndef _USE_NO_GUI_
        SelectObject(pBrush);
        //drawRect(int x, int y, int w, int h)
        drawRect(rect.left, rect.top, rect.Width(), rect.Height());
#else
#endif
    }
    void FillRect(CRect *pRect, CBrush* pBrush)
    {
#ifndef _USE_NO_GUI_
        SelectObject(pBrush);
        //drawRect(int x, int y, int w, int h)
        drawRect(pRect->left, pRect->top, pRect->Width(), pRect->Height());
#else
#endif
    }

    void MoveTo(const CPoint &pt)
    {
        m_bHasListPoint = TRUE;
        m_ptLastPoint = pt;
    }
    void LineTo(const CPoint &pt)
    {
#ifndef _USE_NO_GUI_
        if (m_bHasListPoint)
        {//drawLine(int x1, int y1, int x2, int y2)
            drawLine(m_ptLastPoint.x, m_ptLastPoint.y, pt.x, pt.y);
        }
        else
        {
            drawLine(pt.x, pt.y, pt.x, pt.y);
            m_bHasListPoint = TRUE;
        }

        m_ptLastPoint = pt;
#else
#endif
    }

    void MoveTo(int x, int y)
    {
        m_bHasListPoint = TRUE;
        m_ptLastPoint.x = x;
        m_ptLastPoint.y = y;
    }
    void LineTo(int x, int y)
    {
#ifndef _USE_NO_GUI_
        if (m_bHasListPoint)
        {//drawLine(int x1, int y1, int x2, int y2)
            drawLine(m_ptLastPoint.x, m_ptLastPoint.y, x, y);
        }
        else
        {
            drawLine(x, y, x, y);
            m_bHasListPoint = TRUE;
        }

        m_ptLastPoint.x = x;
        m_ptLastPoint.y = y;
#else
#endif
    }
    void Polyline(CPoint *pPoints, int nPoints)
    {
		//2021-9-20  lijunqing
		//void drawPolyline(const QPoint *points, int pointCount);
#ifndef _USE_NO_GUI_
        drawPolyline((QPoint *)pPoints, nPoints);
#else
#endif
    }
    void Polygon(CPoint *pPoints, int nPoints)
    {
        //void drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill);
#ifndef _USE_NO_GUI_
        drawPolygon((QPoint *)pPoints, nPoints);
        return;

        QPolygon oPolygon(nPoints+1);
        int nIndex = 0;
        CPoint *pPointsEnd = pPoints + nPoints;
        CPoint *p = pPoints;

        while (p < pPointsEnd)
        {
            oPolygon.setPoint(nIndex, p->x, p->y);
            p++;
            nIndex++;
        }

        oPolygon.setPoint(nIndex, pPoints->x, pPoints->y);

        drawPolygon(oPolygon);
        //drawConvexPolygon(oPolygon);
#else
#endif
    }
    void Rectangle(int x1, int y1, int x2, int y2)
    {
#ifndef _USE_NO_GUI_
        //drawRect(int x, int y, int w, int h)
        CRect rect(x1,y1,x2,y2);
        QBrush oBrush = brush();
        QColor color = oBrush.color();
        fillRect(rect.Get_QRect(), color);

//        drawRect(x1, y1, x2, y2);
#else
#endif
    }
    void Rectangle(CRect &rect)
    {
        Rectangle(rect.left, rect.top, rect.right, rect.bottom);
    }
    void Rectangle(CRect *pRect)
    {
        Rectangle(pRect->left, pRect->top, pRect->right, pRect->bottom);
    }

    //画圆弧，未实现
    void Arc(const CRect &rcCircle,const CPoint &ptBegin, const CPoint &ptEnd);
    void Arc(const CRect *rcCircle,const CPoint &ptBegin, const CPoint &ptEnd);

    COLORREF SetBkColor(COLORREF crColor)
    {
#ifndef _USE_NO_GUI_
        CBrush brush;
        brush.CreateSolidBrush(crColor);

        QBrush oOldBrush = background();
        setBackground((QBrush&)brush);
        QColor oColor = oOldBrush.color();

        return QColor_to_COLORREF(oColor);
#else
        return 0;
#endif
    }
    COLORREF SetTextColor(COLORREF crColor)
    {
#ifndef _USE_NO_GUI_
        QPen oOldPen = pen();
        QColor oColor = COLORREF_to_QColor(crColor);

        setPen(oColor);
        oColor = oOldPen.color();

        return QColor_to_COLORREF(oColor);;
#else
        return 0;
#endif
    }

    CSize GetTextExtent(CString &strText, long nCount=0);
    void DrawText(const CString& str, CRect &rect, UINT nFormat)
    {
#ifndef _USE_NO_GUI_
        if ((nFormat & DT_CALCRECT) == DT_CALCRECT)
		{
			rect.left = 0;
			rect.top = 0;
			QFontMetrics fm = fontMetrics();
			rect.right = fm.width(str);
			rect.bottom = fm.height();
		}
		else
		{
			QTextOption oTxtOption;
			UINT_TxtFormat_to_QTextOption(nFormat, oTxtOption);
			drawText(rect.Get_QRect(), (QString&)str, oTxtOption);
		}
#else
#endif
    }
	void DrawText(const CString& str, CRect *pRect, UINT nFormat)
	{
		DrawText(str, *pRect, nFormat);
	}
   void FillSolidRect(CRect &rc, COLORREF cr)
    {
#ifndef _USE_NO_GUI_
       QColor color = COLORREF_to_QColor(cr);
       fillRect(rc.Get_QRect(), color);
#else
#endif
    }
    void FillSolidRect(CRect *rc, COLORREF cr)
    {
#ifndef _USE_NO_GUI_
        QColor color = COLORREF_to_QColor(cr);
        fillRect(rc->Get_QRect(), color);
#else
#endif
    }

    int SetROP2(int nDrawMode)
    {
		nDrawMode = 0;
		return 0;
    }

    void SetPixel(int x, int y, COLORREF crColor)
    {
#ifndef _USE_NO_GUI_
        crColor = 0;
        drawPoint(x, y);
#else
#endif
    }

    void SetPixel(POINT point, COLORREF crColor)
    {
        SetPixel(point.x, point.y, crColor);
    }

    BOOL GetTextMetrics(PTEXTMETRIC lpMetrics) const
    {
#ifndef _USE_NO_GUI_
        QFontMetrics fontMetric = fontMetrics();
        lpMetrics->tmHeight = fontMetric.height();
        lpMetrics->tmAscent = fontMetric.ascent();
        lpMetrics->tmDescent = fontMetric.descent();
        //lpMetrics->tmInternalLeading = fontMetric.;
        //lpMetrics->tmExternalLeading;
        lpMetrics->tmAveCharWidth = fontMetric.averageCharWidth();
        lpMetrics->tmMaxCharWidth = fontMetric.maxWidth();
        //lpMetrics->tmWeight = fontMetric.;
        lpMetrics->tmOverhang = fontMetric.overlinePos();
        //lpMetrics->tmDigitizedAspectX = fontMetric;
        //lpMetrics->tmDigitizedAspectY;
        //lpMetrics->tmFirstChar = fontMetric.;
        //lpMetrics->tmLastChar;
        //lpMetrics->tmDefaultChar;
        //lpMetrics->tmBreakChar;
        //lpMetrics->tmItalic = fontMetric.;
        //lpMetrics->tmUnderlined;
        //lpMetrics->tmStruckOut;
        //lpMetrics->tmPitchAndFamily;
        //lpMetrics->tmCharSet;
#else
#endif
        return FALSE;
    }

	BOOL Attach(HDC hDC)
	{
		hDC = 0;
		return TRUE;
	}
		// Attach/Detach affects only the Output DC
	HDC Detach()
	{
		return NULL;
	}

	int SelectClipRgn(CRgn* pRgn)
	{
#ifndef _USE_NO_GUI_
        if (pRgn == NULL)
		{
			QRegion rgn;
			setClipRegion(rgn, Qt::NoClip);
		}
		else
		{
			setClipRegion(*pRgn);
		}
#else
#endif

		return 0;
	}

	BOOL TextOut(int x, int y, const CString& str)
	{
#ifndef _USE_NO_GUI_
        drawText(x, y, str);
#else
#endif
		return TRUE;
	}

	COLORREF GetTextColor() const
	{
		return RGB(0, 0, 0);
	}


private:
    CPoint m_ptLastPoint;
    BOOL m_bHasListPoint;
};

#ifndef _USE_NO_GUI_
class CBitmap : public QImage
#else
class CBitmap
#endif
{
public:
#ifndef _USE_NO_GUI_
    CBitmap(int width, int height, Format format=QImage::Format_ARGB32)
        : QImage(width, height, format)
#else
    CBitmap(int width, int height, int format=0)
#endif
    {

    }

    virtual ~CBitmap()
    {

    }

};

#endif   //_CXDraw_qt_h__
