#include "stdafx.h"
#include "CXDraw_QT.h"
#include "../../BaseClass/ComplexNumber.h"

void CDC::Arc(const CRect &rcCircle,const CPoint &ptBegin, const CPoint &ptEnd)
{
	Arc(&rcCircle, ptBegin, ptEnd);
}

void CDC::Arc(const CRect *rcCircle,const CPoint &ptBegin, const CPoint &ptEnd)
{
	CPoint ptCenter;
	ptCenter = rcCircle->CenterPoint();
	CComplexNumber c(ptCenter.x, -ptCenter.y);
	CComplexNumber b(ptBegin.x, -ptBegin.y);
	CComplexNumber e(ptEnd.x, -ptEnd.y);
	CComplexNumber r;
	double dAngle_b = 0.0f, dAngle_e = 0.0f,dOffSetAngle = 0.0f;
	r = b-c;
	dAngle_b = r.GetAngle_0_360();
	r = e-c;
	dAngle_e = r.GetAngle_0_360();
//	dOffSetAngle = dAngle_e - dAngle_b;
	dOffSetAngle = CComplexNumber::GetTheAngleRange_0_360(dAngle_e - dAngle_b);
	dAngle_b *= 16;
	dOffSetAngle *= 16;

	//drawArc(int x, int y, int w, int h, int a, int alen)
	drawArc(rcCircle->left, rcCircle->top, rcCircle->Width(), rcCircle->Height(), dAngle_b, dOffSetAngle/*dAngle_e - dAngle_b*/);
}

CSize CDC::GetTextExtent(CString &strText, long nCount)
{
    QRect textrect = fontMetrics().boundingRect(strText);
    CSize sz;

    sz.cx = textrect.width();
    sz.cy = textrect.height();

    return sz;
}

