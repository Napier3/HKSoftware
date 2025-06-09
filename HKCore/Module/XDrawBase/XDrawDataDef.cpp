//XDrawSolve.cpp 


#include "stdafx.h"
#include "XDrawDataDef.h"
#include "../BaseClass/ComplexNumber.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CXDrawDataBase
CXDrawDataBase::CXDrawDataBase()
{

}

CXDrawDataBase::~CXDrawDataBase()
{

}


//////////////////////////////////////////////////////////////////////////
//CXDrawDatas
CXDrawDatas::CXDrawDatas()
{

}

CXDrawDatas::~CXDrawDatas()
{

}

void CXDrawDatas::DataCopy(CXDrawDataBase *pDest){};

void CXDrawDatas::GetBeginPoint(double &x, double &y)
{
	CXDrawDataBase *p = (CXDrawDataBase*)GetHead();

	if (p != NULL)
	{
		p->GetBeginPoint(x, y);
	}
}

void CXDrawDatas::GetEndPoint(double &x, double &y)
{
	CXDrawDataBase *p = (CXDrawDataBase*)GetHead();

	if (p != NULL)
	{
		p->GetEndPoint(x, y);
	}
}

void CXDrawDatas::SetBeginPoint(double x, double y)
{
	CXDrawDataBase *p = (CXDrawDataBase*)GetHead();

	if (p != NULL)
	{
		p->SetBeginPoint(x, y);
	}
}

void CXDrawDatas::SetEndPoint(double x, double y)
{
	CXDrawDataBase *p = (CXDrawDataBase*)GetHead();

	if (p != NULL)
	{
		p->SetEndPoint(x, y);
	}
}

void CXDrawDatas::CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY){}

//////////////////////////////////////////////////////////////////////////
//CXDrawData_Point
CXDrawData_Point::CXDrawData_Point()
{
	m_fX = 0;
	m_fY = 0;
}

CXDrawData_Point::~CXDrawData_Point()
{

}

void CXDrawData_Point::Init()
{
	m_fX = m_fY = 0;
}

void CXDrawData_Point::DataCopy(CXDrawDataBase *pDest)
{
	ASSERT (pDest->GetDrawDataType() == XDRAW_DATA_POINT);

	if (this == pDest)
	{
		return;
	}

	CXDrawData_Point *p = (CXDrawData_Point*)pDest;
	p->m_fX = m_fX;
	p->m_fY = m_fY;
}

void CXDrawData_Point::GetBeginPoint(double &x, double &y){};
void CXDrawData_Point::GetEndPoint(double &x, double &y){};
void CXDrawData_Point::SetBeginPoint(double x, double y){};
void CXDrawData_Point::SetEndPoint(double x, double y){};

//////////////////////////////////////////////////////////////////////////
//CXDrawData_Point
CXDrawData_Point_Ex::CXDrawData_Point_Ex()
{
	m_fX = 0;
	m_fY = 0;
}

CXDrawData_Point_Ex::~CXDrawData_Point_Ex()
{

}

void CXDrawData_Point_Ex::Init()
{
	m_fX = m_fY = 0;
}

void CXDrawData_Point_Ex::DataCopy(CXDrawDataBase *pDest)
{
	ASSERT (pDest->GetDrawDataType() == XDRAW_DATA_POINT_EX);

	if (this == pDest)
	{
		return;
	}

	CXDrawData_Point_Ex *p = (CXDrawData_Point_Ex*)pDest;
	p->m_fX = m_fX;
	p->m_fY = m_fY;
}

void CXDrawData_Point_Ex::GetBeginPoint(double &x, double &y){};
void CXDrawData_Point_Ex::GetEndPoint(double &x, double &y){};
void CXDrawData_Point_Ex::SetBeginPoint(double x, double y){};
void CXDrawData_Point_Ex::SetEndPoint(double x, double y){};

//////////////////////////////////////////////////////////////////////////
//CXDrawData_Line
CXDrawData_Line::CXDrawData_Line()
{
	Init();
}

CXDrawData_Line::~CXDrawData_Line()
{
	
}


void CXDrawData_Line::Init()
{
	m_nType	= CURVE_LINE_TYPE_BEELINE;		//直线的种类
	m_fK	=1;		//直线的斜率 k
	m_fAngle  = 45;
	m_fB	= 0;		//直线的常数 b
	m_fXb =0;      m_fYb=0;	//直线的起始点
	m_fXe=0;       m_fYe=0;	//直线的终止点	
}

void CXDrawData_Line::DataCopy(CXDrawDataBase *pDest)
{
	ASSERT (pDest->GetDrawDataType() == XDRAW_DATA_LINE);

	if (this == pDest)
	{
		return;
	}

	CXDrawData_Line *p = (CXDrawData_Line*)pDest;
	p->m_nType = m_nType;
	p->m_fK = m_fK;
	p->m_fAngle = m_fAngle;
	p->m_fB = m_fB;
	p->m_fXb = m_fXb;
	p->m_fYb = m_fYb;
	p->m_fXe = m_fXe;
	p->m_fYe = m_fYe;
}

void CXDrawData_Line::GetBeginPoint(double &x, double &y)
{
	x = m_fXb;
	y = m_fYb;
}

void CXDrawData_Line::GetEndPoint(double &x, double &y)
{
	x = m_fXe;
	y = m_fYe;
}

void CXDrawData_Line::SetBeginPoint(double x, double y)
{
	m_fXb = x;
	m_fYb = y;
}

void CXDrawData_Line::SetEndPoint(double x, double y)
{
	m_fXe = x;
	m_fYe = y;
}

void CXDrawData_Line::InitLine(double fAngle,double fx,double fy)
{
	m_fXb=fx;
	m_fYb=fy;
	m_fAngle=fAngle;
	MakeAngleTo360(m_fAngle);
}

void CXDrawData_Line::InitLine(double fLengthUse)
{
	double fAngle = m_fAngle*_PI_D_180;
	m_fXe = m_fXb + fLengthUse * cos(fAngle);
	m_fYe = m_fYb + fLengthUse * sin(fAngle);
}

BOOL CXDrawData_Line::IsPositiveDirPoint(double x, double y)
{
	if (m_nType == CURVE_LINE_TYPE_BEELINE)
	{
		return TRUE;
	}

	BOOL bTrue=FALSE;

	if(m_fAngle == 0)//
	{
		if(x >= m_fXb)//正方向
		{
			bTrue=TRUE;
		}
	}
	else if(m_fAngle==180)
	{
		if(x < m_fXb)//正方向
		{
			bTrue=TRUE;
		}
	}
	else if(m_fAngle<180)
	{
		if(y > m_fYb)//正方向
		{
			bTrue=TRUE;
		}
	}
	else
	{
		if(y < m_fYb)//正方向
		{
			bTrue=TRUE;
		}
	}

	return bTrue;
}

void CXDrawData_Line::Init_K_B_by_XY()
{
	if (math_IsEqual(m_fXb,  m_fXe))
	{
		if (m_fYb <= m_fYe)
		{
			m_fAngle = 90;
		}
		else
		{
			m_fAngle = 270;
		}
	}
	else
	{
		m_fK = (m_fYe - m_fYb) / (m_fXe - m_fXb);
		m_fB = m_fYb - m_fK * m_fXb;
		m_fAngle = atan(m_fK);
		m_fAngle *= _180_D_PI;

		if (m_fXe < m_fXb)
		{
			m_fAngle += 180;
		}
	}
}

void CXDrawData_Line::Init_K_by_Angle()
{
	MakeAngleTo360(m_fAngle);

	if (math_IsEqual(m_fAngle, 90) || math_IsEqual(m_fAngle, 270))
	{
		m_fB = m_fXb;
		return;
	}

	double fAngle = m_fAngle*_PI_D_180;
	m_fK = tan(fAngle);
	m_fB = m_fYb - m_fK * m_fXb;
}


//////////////////////////////////////////////////////////////////////////
//CXDrawData_Line
CXDrawData_Line_Ex::CXDrawData_Line_Ex()
{
	Init();
}

CXDrawData_Line_Ex::~CXDrawData_Line_Ex()
{

}


void CXDrawData_Line_Ex::Init()
{
	m_nType	= CURVE_LINE_TYPE_BEELINE;		//直线的种类
	m_fK	=1;		//直线的斜率 k
	m_fAngle  = 45;
	m_fB	= 0;		//直线的常数 b
	m_fXb =0;      m_fYb=0;	//直线的起始点
	m_fXe=0;       m_fYe=0;	//直线的终止点	
}

void CXDrawData_Line_Ex::DataCopy(CXDrawDataBase *pDest)
{
	ASSERT (pDest->GetDrawDataType() == XDRAW_DATA_LINE);

	if (this == pDest)
	{
		return;
	}

	CXDrawData_Line_Ex *p = (CXDrawData_Line_Ex*)pDest;
	p->m_nType = m_nType;
	p->m_fK = m_fK;
	p->m_fAngle = m_fAngle;
	p->m_fB = m_fB;
	p->m_fXb = m_fXb;
	p->m_fYb = m_fYb;
	p->m_fXe = m_fXe;
	p->m_fYe = m_fYe;
}

void CXDrawData_Line_Ex::GetBeginPoint(double &x, double &y)
{
	x = *m_fXb;
	y = *m_fYb;
}

void CXDrawData_Line_Ex::GetEndPoint(double &x, double &y)
{
	x = *m_fXe;
	y = *m_fYe;
}

void CXDrawData_Line_Ex::SetBeginPoint(double *x, double *y)
{
	m_fXb = x;
	m_fYb = y;
}

void CXDrawData_Line_Ex::SetEndPoint(double *x, double *y)
{
	m_fXe = x;
	m_fYe = y;
}

void CXDrawData_Line_Ex::InitLine(double fAngle,double fx,double fy)
{
	ASSERT (FALSE);
// 	m_fXb=fx;
// 	m_fYb=fy;
// 	m_fAngle=fAngle;
// 	MakeAngleTo360(m_fAngle);
}

void CXDrawData_Line_Ex::InitLine(double fLengthUse)
{
	ASSERT (FALSE);
// 	double fAngle = m_fAngle*_PI_D_180;
// 	m_fXe = m_fXb + fLengthUse * cos(fAngle);
// 	m_fYe = m_fYb + fLengthUse * sin(fAngle);
}

BOOL CXDrawData_Line_Ex::IsPositiveDirPoint(double x, double y)
{
	if (m_nType == CURVE_LINE_TYPE_BEELINE)
	{
		return TRUE;
	}

	BOOL bTrue=FALSE;

	if(m_fAngle == 0)//
	{
		if(x >= *m_fXb)//正方向
		{
			bTrue=TRUE;
		}
	}
	else if(m_fAngle==180)
	{
		if(x < *m_fXb)//正方向
		{
			bTrue=TRUE;
		}
	}
	else if(m_fAngle<180)
	{
		if(y > *m_fYb)//正方向
		{
			bTrue=TRUE;
		}
	}
	else
	{
		if(y < *m_fYb)//正方向
		{
			bTrue=TRUE;
		}
	}

	return bTrue;
}

void CXDrawData_Line_Ex::Init_K_B_by_XY()
{
	if (math_IsEqual(*m_fXb,  *m_fXe))
	{
		if (*m_fYb <= *m_fYe)
		{
			m_fAngle = 90;
		}
		else
		{
			m_fAngle = 270;
		}
	}
	else
	{
		m_fK = (*m_fYe - *m_fYb) / (*m_fXe - *m_fXb);
		m_fB = *m_fYb - m_fK * *m_fXb;
		m_fAngle = atan(m_fK);
		m_fAngle *= _180_D_PI;

		if (*m_fXe < *m_fXb)
		{
			m_fAngle += 180;
		}
	}
}

void CXDrawData_Line_Ex::Init_K_by_Angle()
{
	MakeAngleTo360(m_fAngle);

	if (math_IsEqual(m_fAngle, 90) || math_IsEqual(m_fAngle, 270))
	{
		m_fB = *m_fXb;
		return;
	}

	double fAngle = m_fAngle*_PI_D_180;
	m_fK = tan(fAngle);
	m_fB = (*m_fYb) - m_fK * (*m_fXb);
}

//////////////////////////////////////////////////////////////////////////
//CXDrawData_Circle
CXDrawData_Circle::CXDrawData_Circle()
{
	Init();
}

CXDrawData_Circle::~CXDrawData_Circle()
{

}

void CXDrawData_Circle::Init()
{
	m_fXCenter = 0;
	m_fYCenter = 0;
	m_fXRadius = 1;
	m_fYRadius = 1;
}


void CXDrawData_Circle::DataCopy(CXDrawDataBase *pDest)
{
	ASSERT (pDest->GetDrawDataType() == XDRAW_DATA_CIRCLE);

	if (this == pDest)
	{
		return;
	}

	CXDrawData_Circle *p = (CXDrawData_Circle*)pDest;
	p->m_fXCenter = m_fXCenter;
	p->m_fYCenter = m_fYCenter;
	p->m_fXRadius = m_fXRadius;
	p->m_fYRadius = m_fYRadius;
}

void CXDrawData_Circle::GetBeginPoint(double &x, double &y)
{

}

void CXDrawData_Circle::GetEndPoint(double &x, double &y)
{

}

void CXDrawData_Circle::SetBeginPoint(double x, double y)
{
	
}

void CXDrawData_Circle::SetEndPoint(double x, double y)
{
	
}

double CXDrawData_Circle::GetPointAngle(double x, double y)
{
	double dAngle=0;

	double ft=0;
	int iFlag=1;
	ft = x- m_fXCenter;

	if(fabs(ft) > m_fXRadius)
	{
		if(x>=m_fXCenter)
		{
			ft = m_fXRadius;
		}
		else
		{
			ft = - m_fXRadius;
		}
	}
	else
	{
		ft=x- m_fXCenter;
	}

	dAngle=acos(ft / m_fXRadius);
	dAngle *= _180_D_PI;

	if(y < m_fYCenter)
	{
		dAngle = 360 - dAngle;
	}

	MakeAngleTo180(dAngle);

	return dAngle;
}

//////////////////////////////////////////////////////////////////////////
//CXDrawData_Arc
CXDrawData_Arc::CXDrawData_Arc()
{
	Init();
}

CXDrawData_Arc::~CXDrawData_Arc()
{

}

void CXDrawData_Arc::GetTangent(double x, double y, CXDrawData_Line &oLine)
{
	//圆弧在x、y点的切线
	CComplexNumber oC1(x, y);
	CComplexNumber oC2(m_fXCenter, m_fYCenter);
	oC1 -= oC2;

	if (IsCW())
	{
		oC1.Rotate(-90);
	}
	else
	{
		oC1.Rotate(90);
	}
	
	oLine.InitLine(oC1.GetAngle_0_360(), x, y);
}

void CXDrawData_Arc::Init()
{
	m_fAngleBegin = 0;
	m_fAngleEnd = 360;
}

void CXDrawData_Arc::DataCopy(CXDrawDataBase *pDest)
{
	ASSERT (pDest->GetDrawDataType() == XDRAW_DATA_ARC);

	if (this == pDest)
	{
		return;
	}

	CXDrawData_Arc *p = (CXDrawData_Arc*)pDest;
	p->m_fXCenter = m_fXCenter;
	p->m_fYCenter = m_fYCenter;
	p->m_fXRadius = m_fXRadius;
	p->m_fYRadius = m_fYRadius;
	p->m_fAngleBegin = m_fAngleBegin;
	p->m_fAngleEnd = m_fAngleEnd;
	p->m_nClockwise = m_nClockwise;
}

void CXDrawData_Arc::SetBeginPoint(double x, double y)
{
	m_fAngleBegin = GetPointAngle(x,y);
}

void CXDrawData_Arc::SetEndPoint(double x, double y)
{
	m_fAngleEnd = GetPointAngle(x,y);
}


BOOL CXDrawData_Arc::IsAngleInArc(double dAngle)
{
	BOOL b=FALSE;
	MakeAngleTo180(dAngle);

	//lijq 2020-3-15
	//解方程、然后计算角度，可能带来一定的角度误差，
	if (mathAngle360_IsEqual(dAngle, m_fAngleBegin, 0.002))
	{
		return TRUE;
	}

	if (mathAngle360_IsEqual(dAngle, m_fAngleEnd, 0.002))
	{
		return TRUE;
	}

	double fAngleBegin, fAngleEnd;

	if (IsCW())
	{
		fAngleEnd = m_fAngleBegin;
		fAngleBegin = m_fAngleEnd;
	}
	else
	{
		fAngleBegin = m_fAngleBegin;
		fAngleEnd = m_fAngleEnd;
	}

	MakeAngleTo180(fAngleBegin);
	MakeAngleTo180(fAngleEnd);
	//-180 ~ +180 区间
	if(fAngleBegin > fAngleEnd)
	{
		if(dAngle<=fAngleBegin && dAngle>=fAngleEnd)
			b=FALSE;
		else
			b=TRUE;
	}
	else
	{
		if(dAngle>=fAngleBegin && dAngle<=fAngleEnd)
		{
			b=TRUE;
		}
		else
		{
			b = FALSE;
		}
	}

	return b;
}

BOOL CXDrawData_Arc::IsPointOnArc(double x, double y)
{
	double dAngle=0;
	dAngle=GetPointAngle(x,y);

	return IsAngleInArc(dAngle);
}

void CXDrawData_Arc::GetBeginPoint(double &x, double &y)
{
	double dAngle = m_fAngleBegin * _PI_D_180;
	x = m_fXCenter + m_fXRadius * cos(dAngle);
	y = m_fYCenter + m_fXRadius * sin(dAngle);
}

void CXDrawData_Arc::GetEndPoint(double &x, double &y)
{
	double dAngle = m_fAngleEnd * _PI_D_180;
	x = m_fXCenter + m_fXRadius * cos(dAngle);
	y = m_fYCenter + m_fXRadius * sin(dAngle);
}

void CXDrawData_Arc::GetBeginEndPoint(double &fxb, double &fyb, double &fxe, double &fye)
{
	GetBeginPoint(fxb, fyb);
	GetBeginPoint(fxe, fye);
}

void CXDrawData_Arc::CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)	
{	
	double xb, yb, xe, ye;
	GetBeginPoint(xb, yb);
	GetEndPoint(xe, ye);

	xdraw_cal_min_max(xb, yb, fMinX, fMinY, fMaxX, fMaxY);	
	xdraw_cal_min_max(xe, ye, fMinX, fMinY, fMaxX, fMaxY);	

	if (IsAngleInArc(90))
	{
		xdraw_cal_min_max(m_fXCenter, m_fYCenter+m_fYRadius, fMinX, fMinY, fMaxX, fMaxY);	
	}

	if (IsAngleInArc(180))
	{
		xdraw_cal_min_max(m_fXCenter-m_fXRadius, m_fYCenter, fMinX, fMinY, fMaxX, fMaxY);	
	}

	if (IsAngleInArc(-90))
	{
		xdraw_cal_min_max(m_fXCenter, m_fYCenter-m_fYRadius, fMinX, fMinY, fMaxX, fMaxY);	
	}

	if (IsAngleInArc(0))
	{
		xdraw_cal_min_max(m_fXCenter+m_fXRadius, m_fYCenter, fMinX, fMinY, fMaxX, fMaxY);	
	}

	if (IsAngleInArc(-180))
	{
		xdraw_cal_min_max(m_fXCenter-m_fXRadius, m_fYCenter, fMinX, fMinY, fMaxX, fMaxY);	
	}
}

//////////////////////////////////////////////////////////////////////////
//CXDrawData_Points
CXDrawData_Points::CXDrawData_Points()
{
	m_pPoints = NULL;
	m_nPoints = 0;
	m_bIsAutoClose = FALSE;
	m_nPointsMax = 0;
}

CXDrawData_Points::~CXDrawData_Points()
{
	if (m_pPoints != NULL)
	{
		delete []m_pPoints;
	}
}

void CXDrawData_Points::FreePoints()
{
	if (m_pPoints != NULL)
	{
		delete []m_pPoints;
	}

	m_pPoints = NULL;
	m_nPoints = 0;
	m_bIsAutoClose = FALSE;
}

void CXDrawData_Points::InitPoints(long nPoints)
{
	FreePoints();

	m_pPoints = new XDRAWDATA_POINT[nPoints];
	memset(m_pPoints, 0, nPoints * sizeof(XDRAWDATA_POINT));

	m_nPointsMax = nPoints;
}

void CXDrawData_Points::Init()
{
	FreePoints();
}

void CXDrawData_Points::DataCopy(CXDrawDataBase *pDest)
{
	ASSERT (pDest->GetDrawDataType() == XDRAW_DATA_POINTS);

	if (this == pDest)
	{
		return;
	}

	CXDrawData_Points *pDestPoints = (CXDrawData_Points*)pDest;
	pDestPoints->FreePoints();
	pDestPoints->SetPointsMax(m_nPointsMax);
	pDestPoints->m_nPoints = m_nPoints;
	memcpy(pDestPoints->m_pPoints, m_pPoints, sizeof(XDRAWDATA_POINT) * m_nPointsMax);
}

void CXDrawData_Points::GetBeginPoint(double &x, double &y)
{
	if (m_pPoints == NULL || m_nPoints == 0)
	{
		return;
	}

	x = m_pPoints[0].m_fX;
	y = m_pPoints[0].m_fY;
}

void CXDrawData_Points::GetEndPoint(double &x, double &y)
{
	if (m_pPoints == NULL || m_nPoints == 0)
	{
		return;
	}

	x = m_pPoints[m_nPoints-1].m_fX;
	y = m_pPoints[m_nPoints-1].m_fY;
}

void CXDrawData_Points::SetBeginPoint(double x, double y)
{
	if (m_pPoints == NULL || m_nPoints == 0)
	{
		return;
	}

	m_pPoints[0].m_fX = x;
	m_pPoints[0].m_fY = y;
}

void CXDrawData_Points::SetEndPoint(double x, double y)
{
	if (m_pPoints == NULL || m_nPoints == 0)
	{
		return;
	}

	m_pPoints[m_nPoints].m_fX = x;
	m_pPoints[m_nPoints].m_fY = y;
}

void CXDrawData_Points::CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	if (m_pPoints == NULL || m_nPoints == 0)
	{
		return;
	}

	long nIndex = 0;

	for (nIndex=0; nIndex<m_nPoints; nIndex++)
	{
		xdraw_cal_min_max(m_pPoints[nIndex].m_fX, m_pPoints[nIndex].m_fY, fMinX, fMinY, fMaxX, fMaxY);
	}
}


void CXDrawData_Points::SetPointsMax(long nPointsMax)
{
	if (m_nPointsMax >= nPointsMax)
	{
		return;
	}

	if (m_pPoints == NULL)
	{
		m_pPoints = new XDRAWDATA_POINT[nPointsMax];
		memset(m_pPoints, 0, nPointsMax * sizeof(XDRAWDATA_POINT));
	}
	else
	{
		XDRAWDATA_POINT *pNewPoints = new XDRAWDATA_POINT[nPointsMax];
		memset(pNewPoints, 0, nPointsMax * sizeof(XDRAWDATA_POINT));
		memcpy(pNewPoints, m_pPoints, sizeof(XDRAWDATA_POINT) * m_nPointsMax);
		delete []m_pPoints;
		m_pPoints = pNewPoints;
	}

	m_nPointsMax = nPointsMax;
}

void CXDrawData_Points::ExpandPointsMax(long nPointsExpand)
{
	if (nPointsExpand <= 0)
	{
		return;
	}

	long nPointMax = m_nPointsMax + nPointsExpand;
	SetPointsMax(nPointMax);
}

void CXDrawData_Points::AddPoint(double x, double y)
{
	if (m_nPoints >= m_nPointsMax)
	{
		return;
	}

	m_pPoints[m_nPoints].m_fX = x;
	m_pPoints[m_nPoints].m_fY = y;
	m_nPoints++;
}

void CXDrawData_Points::AddPointEx(double x, double y)
{
	if (m_nPoints >= m_nPointsMax)
	{
		ExpandPointsMax(1);
	}

	AddPoint(x, y);
}

//////////////////////////////////////////////////////////////////////////
//
long xdraw_SolveEquation(CXDrawDataBase *pDrawData1, CXDrawDataBase *pDrawData2, CXDrawDatas &listIntersect)
{
	ASSERT ( pDrawData1 != NULL && pDrawData2 != NULL );

	if (pDrawData1 == NULL || pDrawData2 == NULL)
	{
		return 0;
	}

	UINT nType1 = pDrawData1->GetDrawDataType();
	UINT nType2 = pDrawData2->GetDrawDataType();

	switch (nType1)
	{
	case XDRAW_DATA_LINE:
		switch (nType2)
		{
		case XDRAW_DATA_LINE:
			xdraw_SolveEquation((CXDrawData_Line*)pDrawData1, (CXDrawData_Line*)pDrawData2, listIntersect);
			break;
		case XDRAW_DATA_ARC:
			xdraw_SolveEquation((CXDrawData_Line*)pDrawData1, (CXDrawData_Arc*)pDrawData2, listIntersect);
			break;
		case XDRAW_DATA_CIRCLE:
			xdraw_SolveEquation((CXDrawData_Line*)pDrawData1, (CXDrawData_Circle*)pDrawData2, listIntersect);
			break;
		default:
			break;
		}

		break;

	case XDRAW_DATA_ARC:
		switch (nType2)
		{
		case XDRAW_DATA_LINE:
			xdraw_SolveEquation((CXDrawData_Arc*)pDrawData1, (CXDrawData_Line*)pDrawData2, listIntersect, TRUE);
			break;
		case XDRAW_DATA_ARC:
			xdraw_SolveEquation((CXDrawData_Arc*)pDrawData1, (CXDrawData_Arc*)pDrawData2, listIntersect);
			break;
		case XDRAW_DATA_CIRCLE:
			xdraw_SolveEquation((CXDrawData_Arc*)pDrawData1, (CXDrawData_Circle*)pDrawData2, listIntersect);
			break;
		default:
			break;
		}

		break;

	case XDRAW_DATA_CIRCLE:
		switch (nType2)
		{
		case XDRAW_DATA_LINE:
			xdraw_SolveEquation((CXDrawData_Circle*)pDrawData1, (CXDrawData_Line*)pDrawData2, listIntersect);
			break;
		case XDRAW_DATA_ARC:
			xdraw_SolveEquation((CXDrawData_Circle*)pDrawData1, (CXDrawData_Arc*)pDrawData2, listIntersect);
			break;
		case XDRAW_DATA_CIRCLE:
			xdraw_SolveEquation((CXDrawData_Circle*)pDrawData1, (CXDrawData_Circle*)pDrawData2, listIntersect);
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	if (listIntersect.GetCount() == 0)
	{
		if (nType1 == XDRAW_DATA_LINE && nType2 == XDRAW_DATA_ARC)
		{
			CXDrawData_Point *ppv = new CXDrawData_Point();
			pDrawData2->GetBeginPoint(ppv->m_fX, ppv->m_fY);
			listIntersect.AddTail(ppv);
			return 0;
		}

		if (nType2 == XDRAW_DATA_LINE && nType1 == XDRAW_DATA_ARC)
		{
			CXDrawData_Point *ppv = new CXDrawData_Point();
			pDrawData2->GetEndPoint(ppv->m_fX, ppv->m_fY);
			listIntersect.AddTail(ppv);
			return 0;
		}
	}

	return 0;
}

long xdraw_SolveEquation(CXDrawData_Circle *pCircle, CXDrawData_Line *pLine, CXDrawDatas &listIntersect)
{
	int iIntersetNum=0;
	double fX0,fY0;	//圆心坐标
	fX0=pCircle->m_fXCenter;	fY0=pCircle->m_fYCenter;//////////////获取圆心的坐标
	CXDrawData_Point *ppvo = NULL;
	double fintx=0,finty=0;
	double fintx1=0,finty1=0;
	double fCoef_A,fCoef_B,fCoef_C;//二次方程的系数

	//直线为垂直X轴的直线
	if(pLine->IsLineVert()) //★★★★★★如果垂直线
	{
		if(fX0>pLine->m_fB+pCircle->m_fXRadius || fX0<pLine->m_fB-pCircle->m_fXRadius )//如果	x0-R > b 或者 b > x0+R	没有交点
		{
			/*ppvo=NULL;iIntersetNum=0;*/
		}
		else//x0-R <= b <=x0+R	
		{
			if(fX0==pLine->m_fB+pCircle->m_fXRadius || fX0==pLine->m_fB-pCircle->m_fXRadius)//如果(x0-R==b) || (b==x0+R)	一个交点
			{	//一个交点
				fintx=pLine->m_fB; //x=b		y=y0
				finty=fY0;

				iIntersetNum=1;
				ppvo=new CXDrawData_Point(fintx, finty);
				listIntersect.AddTail(ppvo);
			}
			else
			{//有两个交点
				double fhypot=pCircle->m_fXRadius*pCircle->m_fXRadius-(pLine->m_fB-fX0)*(pLine->m_fB-fX0);
				fhypot=(double)pow(fhypot,0.5);
				iIntersetNum=2;

				fintx=pLine->m_fB;
				finty=fY0+fhypot;
				ppvo=new CXDrawData_Point(fintx, finty);
				listIntersect.AddTail(ppvo);

				finty=fY0-fhypot;
				ppvo=new CXDrawData_Point(fintx, finty);
				listIntersect.AddTail(ppvo);
			}
		}

		return iIntersetNum;
	}

	fCoef_A=1+pLine->m_fK*pLine->m_fK; //A=1+k*k	
	fCoef_B=pLine->m_fK*pLine->m_fB - pLine->m_fK*fY0 - fX0; //B=2*k*b-2*k*y0-2*x0
	fCoef_B=fCoef_B*2;
	fCoef_C=fX0*fX0 + (pLine->m_fB-fY0)*(pLine->m_fB-fY0)-pCircle->m_fXRadius*pCircle->m_fXRadius;//C=x0*x0+(b-y0)*(b-y0)-R*R
	double fDELTA=fCoef_B*fCoef_B-4*fCoef_A*fCoef_C;//B*B-4*A*C

	if(fDELTA<0)//无交点
	{
		ppvo=NULL;iIntersetNum=0;
	}
	else if(fDELTA==0)//一个交点
	{
		fintx=-fCoef_B*0.5f / fCoef_A;//x=-B / (2*A)
		finty=pLine->m_fK*fintx+pLine->m_fB;

		ppvo=new CXDrawData_Point(fintx, finty);
		iIntersetNum=1;
		listIntersect.AddTail(ppvo);
	}
	else//两个交点
	{//x=(-B±sqrt(B*B-4*A*C)) / (2*A)	y=k*x+b
		fDELTA=(double)pow(fDELTA,0.5);
		fintx=(-fCoef_B+fDELTA)*0.5f/fCoef_A;
		finty=pLine->m_fK*fintx+pLine->m_fB;
		fintx1=(-fCoef_B-fDELTA)*0.5f/fCoef_A;
		finty1=pLine->m_fK*fintx1+pLine->m_fB;
		iIntersetNum=2;

		ppvo=new CXDrawData_Point(fintx, finty);
		listIntersect.AddTail(ppvo);

		ppvo=new CXDrawData_Point(fintx1, finty1);
		listIntersect.AddTail(ppvo);
	}

	return iIntersetNum;
}

long xdraw_SolveEquation(CXDrawData_Line *pLine, CXDrawData_Circle *pCircle, CXDrawDatas &listIntersect)
{
	return xdraw_SolveEquation(pCircle, pLine, listIntersect);
}

long xdraw_SolveEquation(CXDrawData_Arc *pArc, CXDrawData_Line *pLine, CXDrawDatas &listIntersect)
{
	return xdraw_SolveEquation((CXDrawData_Circle*)pArc, pLine, listIntersect);
}

long xdraw_SolveEquation(CXDrawData_Arc *pArc, CXDrawData_Line *pLine, CXDrawDatas &listIntersect, BOOL bIner)
{
	if (bIner)
	{
		CXDrawDatas listTemp;
		xdraw_SolveEquation(pArc, pLine, listTemp);//解方程,获取圆弧与直线的交点

		POS pos = listTemp.GetHeadPosition();
		POS posPrev = NULL;
		CXDrawData_Point *p = NULL;

		while (pos != NULL)
		{
			posPrev = pos;
			p = (CXDrawData_Point *)listTemp.GetNext(pos);

			if (pLine->IsPositiveDirPoint(p) && pArc->IsPointOnArc(p))
			{
				listIntersect.AddTail(p);
				listTemp.RemoveAt(posPrev);
			}
		}
	}
	else
	{
		xdraw_SolveEquation(pArc, pLine, listIntersect);
	}

	return listIntersect.GetCount();
}

long xdraw_SolveEquation(CXDrawData_Line *pLine, CXDrawData_Arc *pArc, CXDrawDatas &listIntersect)
{
	return xdraw_SolveEquation(pArc, pLine, listIntersect, TRUE);
}


// 
// void xdraw_SolveEquation(CXDrawData_Arc *pArc, CXDrawData_Line *pLine, CXDrawDatas &listIntersect,BOOL bIner,int iEndOrBegin)
// {
// 	CXDrawDatas listTemp;
// 	long nCount = xdraw_SolveEquation(pArc, pLine, listTemp, bIner);
// 
// 	if (nCount == 0)
// 	{
// 		if (iEndOrBegin == 1)
// 		{
// 
// 		}
// 	}
// }
//
// void GetIntersectPV3(CXDrawData_Arc *pArc, CXDrawData_Line *pLine, CXDrawDatas &listIntersect,BOOL bIner,int iEndOrBegin)
// {
// 	int iIntersetNum=0;
// 	double fX0,fY0;	//圆心坐标
// 	fX0=pArc->m_fXCenter;	fY0=pArc->m_fYCenter;//////////////获取圆心的坐标
// 	////////////////////////////////////////////////////////////////////////////
// 	//		解方程
// 	CXDrawData_Point *ppvo = NULL;
// 	double fintx=0,finty=0;
// 	double fintx1=0,finty1=0;
// 
// 	double fCoef_A,fCoef_B,fCoef_C;//二次方程的系数
// 
// 	//直线为垂直X轴的直线
// 	if(pLine->IsLineVert()) //★★★★★★如果垂直线
// 	{
// 		if(fX0>pLine->m_fB+pArc->m_fXRadius || fX0<pLine->m_fB-pArc->m_fXRadius )//如果	x0-R > b 或者 b > x0+R	没有交点
// 		{
// 			/*ppvo=NULL;iIntersetNum=0;*/
// 		}
// 		else//x0-R <= b <=x0+R	
// 		{
// 			if(fX0==pLine->m_fB+pArc->m_fXRadius || fX0==pLine->m_fB-pArc->m_fXRadius)//如果(x0-R==b) || (b==x0+R)	一个交点
// 			{	//一个交点
// 				fintx=pLine->m_fB; //x=b		y=y0
// 				finty=fY0;
// 
// 				if(pLine->IsPositiveDirPoint(fintx,finty))//正方向
// 				{
// 					if (bIner)
// 					{
// 						if(pArc->IsPointOnArc(fintx,finty))
// 						{
// 							iIntersetNum=1;
// 							ppvo=new CXDrawData_Point(fintx, finty);
// 							listIntersect.AddTail(ppvo);
// 						}
// 					}
// 					else
// 					{
// 						iIntersetNum=1;
// 						ppvo=new CXDrawData_Point(fintx, finty);
// 						listIntersect.AddTail(ppvo);
// 					}
// 				}
// 				else
// 				{//反方向
// 					/*ppvo=NULL;iIntersetNum=0;*/
// 				}
// 			}
// 			else
// 			{//有两个交点
// 				double fx=pArc->m_fXRadius*pArc->m_fXRadius-(pLine->m_fB-fX0)*(pLine->m_fB-fX0);
// 				fx=(double)pow(fx,0.5);
// 				double fy=pLine->m_fB-fX0; 
// 				double fhypot=fx;
// 				fintx=pLine->m_fB;
// 				finty=fY0+fhypot;
// 				iIntersetNum=2;
// 				
// 				if(pLine->IsPositiveDirPoint(fintx,finty))//正方向
// 				{
// 					finty=fY0+fhypot;
// 					ppvo=new CXDrawData_Point(fintx, finty);
// 					listIntersect.AddTail(ppvo);
// 				}
// 
// 				finty=fY0-fhypot;
// 				finty=fY0+fhypot;
// 				ppvo=new CXDrawData_Point(fintx, finty);
// 				listIntersect.AddTail(ppvo);
// 			}
// 		}
// 		return ;
// 	}
// 
// 	fCoef_A=1+pLine->m_fK*pLine->m_fK; //A=1+k*k	
// 	fCoef_B=pLine->m_fK*pLine->m_fB - pLine->m_fK*fY0 - fX0; //B=2*k*b-2*k*y0-2*x0
// 	fCoef_B=fCoef_B*2;
// 	fCoef_C=fX0*fX0 + (pLine->m_fB-fY0)*(pLine->m_fB-fY0)-pArc->m_fXRadius*pArc->m_fXRadius;//C=x0*x0+(b-y0)*(b-y0)-R*R
// 	double fDELTA=fCoef_B*fCoef_B-4*fCoef_A*fCoef_C;//B*B-4*A*C
// 	
// 	if(fDELTA<0)//无交点
// 	{
// 		ppvo=NULL;iIntersetNum=0;
// 	}
// 	else if(fDELTA==0)//一个交点
// 	{
// 		fintx=-fCoef_B*0.5f / fCoef_A;//x=-B / (2*A)
// 		finty=pLine->m_fK*fintx+pLine->m_fB;
// 		if(pLine->IsPositiveDirPoint(fintx,finty))//正方向
// 		{
// 			if(bIner)
// 			{
// 				if(pArc->IsPointOnArc(fintx,finty))
// 				{
// 					ppvo=new CXDrawData_Point(fintx, finty);
// 					iIntersetNum=1;
// 					listIntersect.AddTail(ppvo);
// 				}
// 			}
// 			else
// 			{
// 				ppvo=new CXDrawData_Point(fintx, finty);
// 				iIntersetNum=1;
// 				listIntersect.AddTail(ppvo);
// 			}
// 		}
// 		else{ppvo=NULL;iIntersetNum=0;}////反方向
// 	}
// 	else//两个交点
// 	{//x=(-B±sqrt(B*B-4*A*C)) / (2*A)	y=k*x+b
// 		fDELTA=(double)pow(fDELTA,0.5);
// 		fintx=(-fCoef_B+fDELTA)*0.5f/fCoef_A;
// 		finty=pLine->m_fK*fintx+pLine->m_fB;
// 		fintx1=(-fCoef_B-fDELTA)*0.5f/fCoef_A;
// 		finty1=pLine->m_fK*fintx1+pLine->m_fB;
// 		iIntersetNum=2;
// 		
// 		if(iIntersetNum==0)
// 		{
// 			ppvo=NULL;
// 		}
// 		else
// 		{
// 			if(bIner)
// 			{
// 				if(pArc->IsPointOnArc(fintx,finty))
// 				{
// 					ppvo=new CXDrawData_Point(fintx, finty);
// 					listIntersect.AddTail(ppvo);
// 				}
// 				if(pArc->IsPointOnArc(fintx1,finty1))
// 				{
// 					ppvo=new CXDrawData_Point(fintx1, finty1);
// 					listIntersect.AddTail(ppvo);
// 				}
// 			}
// 			else
// 			{
// 				ppvo=new CXDrawData_Point;
// 				double fx=0,fy=0;
// 			
// 				if(iEndOrBegin==1)	//begin point
// 				{
// 					pArc->GetBeginPoint(fx, fy);
// 				}
// 				else
// 				{
// 					pArc->GetEndPoint(fx, fy);
// 				}
// 				double fLen1=hypot(fintx-fx,finty-fy);
// 				double fLen2=hypot(fintx1-fx,finty1-fy);
// 				
// 				if(fLen1<fLen2)
// 				{
// 					ppvo->m_fX=fintx;ppvo->m_fY=finty;
// 				}
// 				else
// 				{
// 					ppvo->m_fX=fintx1;ppvo->m_fY=finty1;
// 				}
// 			
// 				listIntersect.AddTail(ppvo);
// 			}
// 		}
// 	}
// }

long xdraw_SolveEquation(CXDrawData_Line *pLine1, CXDrawData_Line*pLine2,CXDrawDatas &listIntersect)
{
	double fx,fy;
	int nNum = 0;

	/////直线段数据(x1,y1)、(x2,y2)
	CXDrawData_Point *ppv = NULL;

	if( math_IsEqual(pLine1->m_fK, pLine2->m_fK)
		&& math_IsEqual(pLine1->m_fAngle, pLine2->m_fAngle) ) //平行线，两个直线没有交点
	{
		return nNum;
	}	

	if(pLine1->IsLineVert())	//当前直线为垂直线
	{
		//前面已经处理了平行线，所以直线2不可能为垂线
		fx=pLine1->m_fXb;
		fy=pLine2->m_fK*fx+pLine2->m_fB;
		nNum=1;
	}
	else if(pLine2->IsLineVert())	//前直线为垂直线
	{
		fx=pLine2->m_fXb;
		fy=pLine1->m_fK*fx+pLine1->m_fB;
		nNum=1;
	}
	else
	{
		fx=(pLine1->m_fB-pLine2->m_fB)/(pLine2->m_fK-pLine1->m_fK);
		fy=pLine1->m_fK*fx + pLine1->m_fB;
		nNum=1;
// 		if(pLine2->IsPositiveDirPoint(fx,fy))
// 		{
// 			nNum=1;
// 		}
	}

	if(nNum)
	{
		ppv=new CXDrawData_Point;
		ppv->m_fX = fx;	
		ppv->m_fY = fy;			
		listIntersect.AddTail(ppv);
	}
	
	return nNum;
}

#define xsec_sqr(val) ((val) * (val))
#define xse_c_equal(c1, c2) (math_IsEqual((c1.m_fXCenter), (c2.m_fXCenter)) && math_IsEqual((c1.m_fYCenter), (c2.m_fYCenter)) && math_IsEqual((c1.m_fXRadius), (c2.m_fXRadius)))
#define xse_y_equal(c1, c2) math_IsEqual((c1.m_fYCenter), (c2.m_fYCenter))
#define xse_x_equal(c1, c2) math_IsEqual((c1.m_fXCenter), (c2.m_fXCenter))

long xdraw_SolveEquation(CXDrawData_Circle &c1,CXDrawData_Circle &c2, CXDrawDatas &listIntersect)
{
	long nCpunt = 0;
	double B2_4AC, A, B, C, K, S, x1, y1, x2, y2, x, y;

	if (xse_c_equal(c1, c2))
		return 0;

	if (xse_y_equal(c1, c2))
	{
		x = (xsec_sqr((c1.m_fXCenter)) + xsec_sqr((c1.m_fYCenter)) + xsec_sqr((c2.m_fXRadius)) - xsec_sqr((c2.m_fXCenter)) - xsec_sqr((c2.m_fYCenter)) - xsec_sqr((c1.m_fXRadius))) / (2 * (c1.m_fXCenter) - 2 * (c2.m_fXCenter));
		A = 1;
		B = (-2) *  (c1.m_fYCenter);
		C = xsec_sqr(x) + xsec_sqr((c1.m_fXCenter)) + xsec_sqr((c1.m_fYCenter)) - xsec_sqr((c1.m_fXRadius)) - 2 * (c1.m_fXCenter)*x;
		B2_4AC = xsec_sqr(B) - 4 * A*C;

		if (B2_4AC < 0)
		{
			return 0;
		}
		else
		{
			x1 = x2 = x;
			y1 = ((-B) + sqrt(B2_4AC)) / (2 * A);
			y2 = ((-B) - sqrt(B2_4AC)) / (2 * A);
		}
	}
	else
	{
		if (xse_x_equal(c1, c2))
		{
			y = (xsec_sqr((c1.m_fXCenter)) + xsec_sqr((c1.m_fYCenter)) + xsec_sqr((c2.m_fXRadius)) - xsec_sqr((c2.m_fXCenter)) - xsec_sqr((c2.m_fYCenter)) - xsec_sqr((c1.m_fXRadius))) / (2 * (c1.m_fYCenter) - 2 * (c2.m_fYCenter));
			A = 1;
			B = (-2) * (c1.m_fXCenter);
			C = xsec_sqr((c1.m_fXCenter)) + xsec_sqr((c1.m_fYCenter)) + xsec_sqr(y) - xsec_sqr((c1.m_fXRadius)) - 2 * y* (c1.m_fYCenter);
			B2_4AC = xsec_sqr(B) - 4 * A*C;

			if (B2_4AC < 0)
				return -1;
			else
			{
				y1 = y2 = y;
				x1 = ((-B) + sqrt(B2_4AC)) / (2 * A);
				x2 = ((-B) - sqrt(B2_4AC)) / (2 * A);
			}
		}
		else
		{
			K = (2 * (c2.m_fXCenter) - 2 * (c1.m_fXCenter)) / (2 * (c1.m_fYCenter) - 2 * (c2.m_fYCenter));
			S = (xsec_sqr((c1.m_fXCenter)) + xsec_sqr((c1.m_fYCenter)) + xsec_sqr((c2.m_fXRadius)) - xsec_sqr((c2.m_fXCenter)) - xsec_sqr((c2.m_fYCenter)) - xsec_sqr((c1.m_fXRadius))) / (2 * (c1.m_fYCenter) - 2 * (c2.m_fYCenter));

			//解二次方程
			A = (1 + xsec_sqr(K));
			B = 2 * K * S - 2 * (c1.m_fXCenter) - 2 * (c1.m_fYCenter)*K;
			C = xsec_sqr(S) + xsec_sqr((c1.m_fXCenter)) + xsec_sqr((c1.m_fYCenter)) - xsec_sqr((c1.m_fXRadius)) - 2 * (c1.m_fYCenter)*S;
			B2_4AC = xsec_sqr(B) - 4 * A*C;

			if (B2_4AC < 0)
			{
				return 0;
			}
			else
			{
				x1 = ((-B) + sqrt(B2_4AC)) / (2 * A);
				x2 = ((-B) - sqrt(B2_4AC)) / (2 * A);
				y1 = K * x1 + S;
				y2 = K * x2 + S;
			}
		}
	}

	CXDrawData_Point *ppv = NULL;

	if (math_IsEqual(x1, x2) && math_IsEqual(y1, y2))
	{//一个点
		ppv = new CXDrawData_Point(x1, y1);
		listIntersect.AddTail(ppv);
		return 1;
	}
	else
	{
		ppv = new CXDrawData_Point(x1, y1);
		listIntersect.AddTail(ppv);

		ppv = new CXDrawData_Point(x2, y2);
		listIntersect.AddTail(ppv);
		return 2;
	}
}

long xdraw_SolveEquation(CXDrawData_Circle *pCircle1,CXDrawData_Circle *pCircle2, CXDrawDatas &listIntersect)
{
	return xdraw_SolveEquation(*pCircle1, *pCircle2, listIntersect);
}
