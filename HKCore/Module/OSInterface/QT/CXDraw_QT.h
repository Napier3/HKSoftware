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

inline COLORREF QColor_to_COLORREF(QColor &cr)
{
    int red = cr.red();
    int green = cr.green();
    int blue = cr.blue();
    return RGB(red, green, blue);
}

inline QColor COLORREF_to_QColor(const COLORREF &cr)//zhouhj 20210203 ��������ת��
{
	int r = cr & 0xFF;//zhouhj 20210203 ����֮����Ҫת��
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

class CFont : public QFont
{
public:
    CFont()
    {
    }
    CFont(const QFont &font)
      : QFont(font)
    {

    }
    void CreateFontIndirect(LOGFONT  &lfFont)
    {
        CString strName;
        strName = lfFont.lfFaceName;
        setFamily(strName);

		if (lfFont.lfWeight == 300)//zhouhj 20210202 ����Qt����������������
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

        /*setPointSize*/setPixelSize(abs(lfFont.lfHeight));//zhouhj 20210201 ��Ҫ��֤Ϊ���� ,setPixelSize������˼������߶�ռ�õ�����px��С,setPointSize������˼������߶�ռ�õĿ���������ĳ��Ȱ���point��pt��С��һ������ӡˢ����
//        setBold(lfFont.lfWidth > 0);//�Ƿ�Ӵ���ͨ��lfWeight���ж�  zhouhj 20210202
        setItalic(lfFont.lfItalic);
        setUnderline(lfFont.lfUnderline);
        setOverline(lfFont.lfOutPrecision);
    }
    void CreateFontIndirect(LOGFONT *pLfFont)
    {
        CreateFontIndirect(*pLfFont);
    }
    void DeleteObject(){}
};

class CPen : public QPen
{
public:
    CPen()
    {
    }
    CPen(const QPen &pen)
      : QPen(pen)
    {

    }
    CPen(int nPenStyle, int nWidth, COLORREF crColor)
    {
        CreatePen(nPenStyle, nWidth, crColor);
    }

    void CreatePen(int nPenStyle, int nWidth, COLORREF crColor)
    {
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
        setColor(cr);//zhouhj 20210201 ֮ǰȱ��ת��
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

class CBrush : public QBrush
{
public:
    CBrush()
    {

    }
    CBrush(COLORREF cr)
    {
        CreateSolidBrush(cr);
    }
    CBrush(const QBrush &brush)
      : QBrush(brush)
    {

    }
    void CreateSolidBrush(COLORREF crColor)
    {
        //#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
//         int r = crColor & 0xFF;
//         int g = (crColor >> 8) & 0xFF;
//         int b = (crColor >> 16) & 0xFF;
        QColor cr = COLORREF_to_QColor(crColor);
        setColor(cr);
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
class CRgn : public QRegion
{
public:
	CRgn()
	{
	}

	~CRgn(){}

	BOOL CreateRectRgn(int x1, int y1, int x2, int y2)
	{
		QRegion rgn(x1, y1, x2, y2);
		(QRegion &)(*this) = rgn;
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

class CDC : public QPainter
{
public:
    CDC()
    {
        m_bHasListPoint = FALSE;
    }
    CDC(QPaintDevice *pDevice)
        : QPainter(pDevice)
    {
        m_bHasListPoint = FALSE;
    }

    CPen* SelectObject(CPen &open)
    {
        const QPen &old = pen();
        setPen((QPen&)open);

        return (CPen*)(&old);
    }
    CPen* SelectObject(CPen *pPen)
    {
        const QPen &old = pen();

        if (pPen != NULL)
        {
            setPen((QPen&)*pPen);
        }

        return (CPen*)(&old);
    }
    CBrush* SelectObject(CBrush &oBrush)
    {
        const QBrush &old = brush();
        setBrush((CBrush&)oBrush);
        return (CBrush*)(&old);
    }
    CBrush* SelectObject(CBrush *pBrush)
    {
        const QBrush &old = brush();
        if (pBrush != NULL)
        {
            setBrush((CBrush&)*pBrush);
        }

        return (CBrush*)(&old);
    }
    CFont* SelectObject(CFont &oFont)
    {
        const QFont &old = font();
        setFont((CFont&)oFont);
        return (CFont*)(&old);
    }
    CFont* SelectObject(CFont *pFont)
    {
        const QFont &old = font();

        if (pFont != NULL)
        {
            setFont((CFont&)*pFont);
        }

         return (CFont*)(&old);
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

		return NULL;
    }

    int SetBkMode(int nBkMode)
    {
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
    }

    void Ellipse(CRect &rect)
    {
        //QPainter::drawEllipse(int x, int y, int w, int h)
        drawEllipse(rect.left, rect.top, rect.Width(), rect.Height());
    }
    void FillRect(CRect &rect, CBrush* pBrush)
    {
        SelectObject(pBrush);
        //drawRect(int x, int y, int w, int h)
        drawRect(rect.left, rect.top, rect.Width(), rect.Height());
    }
    void FillRect(CRect *pRect, CBrush* pBrush)
    {
        SelectObject(pBrush);
        //drawRect(int x, int y, int w, int h)
        drawRect(pRect->left, pRect->top, pRect->Width(), pRect->Height());
    }

    void MoveTo(const CPoint &pt)
    {
        m_bHasListPoint = TRUE;
        m_ptLastPoint = pt;
    }
    void LineTo(const CPoint &pt)
    {
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
    }

    void MoveTo(int x, int y)
    {
        m_bHasListPoint = TRUE;
        m_ptLastPoint.x = x;
        m_ptLastPoint.y = y;
    }
    void LineTo(int x, int y)
    {
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
    }
    void Polyline(CPoint *pPoints, int nPoints)
    {
		//2021-9-20  lijunqing
		//void drawPolyline(const QPoint *points, int pointCount);
		  drawPolyline((QPoint *)pPoints, nPoints);
    }
    void Polygon(CPoint *pPoints, int nPoints)
    {
        //void drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill);
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
    }
    void Rectangle(int x1, int y1, int x2, int y2)
    {
        //drawRect(int x, int y, int w, int h)
 		CRect rect(x1,y1,x2,y2);
		QBrush oBrush = brush();
 		QColor color = oBrush.color();
 		fillRect(rect.Get_QRect(), color);

//        drawRect(x1, y1, x2, y2);
    }
    void Rectangle(CRect &rect)
    {
        Rectangle(rect.left, rect.top, rect.right, rect.bottom);
    }
    void Rectangle(CRect *pRect)
    {
        Rectangle(pRect->left, pRect->top, pRect->right, pRect->bottom);
    }
    void Arc(const CRect &rcCircle,const CPoint &ptBegin, const CPoint &ptEnd);
	void Arc(const CRect *rcCircle,const CPoint &ptBegin, const CPoint &ptEnd);

    COLORREF SetBkColor(COLORREF crColor)
    {
        CBrush brush;
        brush.CreateSolidBrush(crColor);

        QBrush oOldBrush = background();
        setBackground((QBrush&)brush);
        QColor oColor = oOldBrush.color();

        return QColor_to_COLORREF(oColor);
    }
    COLORREF SetTextColor(COLORREF crColor)
    {
        QPen oOldPen = pen();
// 		int r = crColor & 0xFF;//zhouhj 20210203 ����֮����Ҫת��
// 		int g = (crColor >> 8) & 0xFF;
// 		int b = (crColor >> 16) & 0xFF;
		QColor oColor = COLORREF_to_QColor(crColor);
 //       QColor oColor(crColor);

        setPen(oColor);
        oColor = oOldPen.color();

        return QColor_to_COLORREF(oColor);;
    }

    CSize GetTextExtent(CString &strText, long nCount=0);
    void DrawText(const CString& str, CRect &rect, UINT nFormat)
    {
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
    }
	void DrawText(const CString& str, CRect *pRect, UINT nFormat)
	{
		DrawText(str, *pRect, nFormat);
	}
   void FillSolidRect(CRect &rc, COLORREF cr)
    {
        QColor color = COLORREF_to_QColor(cr);
        fillRect(rc.Get_QRect(), color);
    }
    void FillSolidRect(CRect *rc, COLORREF cr)
    {
        QColor color = COLORREF_to_QColor(cr);
        fillRect(rc->Get_QRect(), color);
    }

    int SetROP2(int nDrawMode)
    {
		nDrawMode = 0;
		return 0;
    }

    void SetPixel(int x, int y, COLORREF crColor)
    {
        crColor = 0;
        drawPoint(x, y);
    }

    void SetPixel(POINT point, COLORREF crColor)
    {
        SetPixel(point.x, point.y, crColor);
    }

    BOOL GetTextMetrics(PTEXTMETRIC lpMetrics) const
    {
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
		if (pRgn == NULL)
		{
			QRegion rgn;
			setClipRegion(rgn, Qt::NoClip);
		}
		else
		{
			setClipRegion(*pRgn);
		}

		return 0;
	}

	BOOL TextOut(int x, int y, const CString& str)
	{
		drawText(x, y, str);
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

class CBitmap : public QImage
{
public:
    CBitmap(int width, int height, Format format=QImage::Format_ARGB32)
        : QImage(width, height, format)
    {

    }

    virtual ~CBitmap()
    {

    }

};

#endif   //_CXDraw_qt_h__
