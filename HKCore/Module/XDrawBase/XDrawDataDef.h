//XDrawData.h

#pragma once

#include "../API/MathApi.h"

#define XDRAW_DATA_POINT           1
#define XDRAW_DATA_LINE            2
#define XDRAW_DATA_ARC             3
#define XDRAW_DATA_CIRCLE          4
#define XDRAW_DATAS                5
#define XDRAW_DATA_POINTS          6
#define XDRAW_DATA_POINT_EX        7
#define XDRAW_DATA_LINE_EX         8


inline double xdraw_CalLengthPoints(double x1, double y1, double x2, double y2)
{
	return sqrt ( (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2) );
}

inline void xdraw_cal_min_max(double x, double y, double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{ 
    //在Ubuntu中，会报调用不明确，故修改
//	fMinY = min(y, fMinY);
//	fMaxY = max(y, fMaxY);
//	fMinX = min(x, fMinX);
//	fMaxX = max(x, fMaxX);

    fMinY = y<fMinY?y:fMinY;
    fMaxY = y>fMaxY?y:fMaxY;
    fMinX = x<fMinX?x:fMinX;
    fMaxX = x>fMaxX?x:fMaxX;
}

class CXDrawDataBase
{
public:
	CXDrawDataBase();
	virtual ~CXDrawDataBase();
	
public:
	virtual DWORD GetDrawDataType() = 0;
	virtual void Init() = 0;
	virtual void DataCopy(CXDrawDataBase *pDest) = 0;

	virtual void GetBeginPoint(double &x, double &y) = 0;
	virtual void GetEndPoint(double &x, double &y) = 0;
	virtual void GetBeginEndPoint(double &fxb, double &fyb, double &fxe, double &fye)
	{
		GetBeginPoint(fxb, fyb);
		GetBeginPoint(fxe, fye);
	}

	virtual void SetBeginPoint(double x, double y) = 0;
	virtual void SetEndPoint(double x, double y) = 0;
};

class CXDrawDatas : public CXDrawDataBase, public CTLinkList<CXDrawDataBase>
{
public:
	CXDrawDatas();
	virtual ~CXDrawDatas();

public:
	virtual DWORD GetDrawDataType()	{	return XDRAW_DATAS;	}
	virtual void Init() {};
	virtual void DataCopy(CXDrawDataBase *pDest);

	virtual void GetBeginPoint(double &x, double &y);
	virtual void GetEndPoint(double &x, double &y);
	virtual void SetBeginPoint(double x, double y);
	virtual void SetEndPoint(double x, double y);
	virtual void CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);
};

typedef struct struct_XDrawData_Point
{
	double m_fX,m_fY;
}XDRAWDATA_POINT, *PXDRAWDATA_POINT;

typedef struct struct_XDrawData_PointEx
{
	double *m_fX,*m_fY;
}XDRAWDATA_POINT_EX, *PXDRAWDATA_POINT_EX;

class CXDrawData_Point : public CXDrawDataBase, public XDRAWDATA_POINT
{
public:
	//double m_fX,m_fY;
	
	CXDrawData_Point();
	CXDrawData_Point(double x, double y)	{	m_fX = x;	m_fY = y;	}
	virtual ~CXDrawData_Point();
	
public:
	virtual DWORD GetDrawDataType()	{	return XDRAW_DATA_POINT;	}
	virtual void Init();
	virtual void DataCopy(CXDrawDataBase *pDest);
	virtual void GetBeginPoint(double &x, double &y);
	virtual void GetEndPoint(double &x, double &y);
	virtual void SetBeginPoint(double x, double y);
	virtual void SetEndPoint(double x, double y);
	virtual void CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)	{	xdraw_cal_min_max(m_fX, m_fY, fMinX, fMinY, fMaxX, fMaxY);	}

};

//2021-9-7  lijunqing
class CXDrawData_Point_Ex : public CXDrawDataBase, public XDRAWDATA_POINT_EX
{
public:
	CXDrawData_Point_Ex();
	CXDrawData_Point_Ex(double *x, double *y)	{	m_fX = x;	m_fY = y;	}
	virtual ~CXDrawData_Point_Ex();

public:
	virtual DWORD GetDrawDataType()	{	return XDRAW_DATA_POINT_EX;	}
	virtual void Init();
	virtual void DataCopy(CXDrawDataBase *pDest);
	virtual void GetBeginPoint(double &x, double &y);
	virtual void GetEndPoint(double &x, double &y);
	virtual void SetBeginPoint(double x, double y);
	virtual void SetEndPoint(double x, double y);
	virtual void CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)	{	xdraw_cal_min_max(*m_fX, *m_fY, fMinX, fMinY, fMaxX, fMaxY);	}

};
////////////////////定义直线函数方程数据类
/*
	直线的种类	
		iType=0			正常直线	y=k*x+b
		iType=1			k->∞		x=b
*/
#define CURVE_LINE_TYPE_BEELINE             0
#define CURVE_LINE_TYPE_LINE_SEGMENT   1
#define CURVE_LINE_TYPE_LINE_RAY           2

//2021-9-7  lijunqing 
class CXDrawData_LineBase : public CXDrawDataBase
{
public:
	CXDrawData_LineBase(){}
	virtual ~CXDrawData_LineBase()	{}

public:
	DWORD	m_nType;	//直线的种类
	double	m_fK;		//直线的斜率 k
	double	m_fB;	    //直线的常数 b
	
	double	m_fAngle;//直线的倾斜角，单位为角度（不是弧度）

	void Set_Beeline()	{	m_nType = CURVE_LINE_TYPE_BEELINE;	}
	void Set_LineSegment()	{	m_nType = CURVE_LINE_TYPE_LINE_SEGMENT;	}
	void Set_LineRay()	{	m_nType = CURVE_LINE_TYPE_LINE_RAY;	}

};

class CXDrawData_Line : public CXDrawData_LineBase
{
public:
	//直线的起始点
	double  m_fXb;
	double  m_fYb;

	//直线的终止点
	double  m_fXe;
	double  m_fYe;

	CXDrawData_Line();
	virtual ~CXDrawData_Line();
	

public:
	virtual DWORD GetDrawDataType()	{	return XDRAW_DATA_LINE;	}
	virtual void Init();
	virtual void DataCopy(CXDrawDataBase *pDest);

	virtual void GetBeginPoint(double &x, double &y);
	virtual void GetEndPoint(double &x, double &y);
	virtual void SetBeginPoint(double x, double y);
	virtual void SetEndPoint(double x, double y);

	virtual void CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)	
	{	
		xdraw_cal_min_max(m_fXb, m_fYb, fMinX, fMinY, fMaxX, fMaxY);	
		xdraw_cal_min_max(m_fXe, m_fYe, fMinX, fMinY, fMaxX, fMaxY);	
	}

public:
	void	InitLine(double fAngle,double fx,double fy);
	void	InitLine(double fLengthUse);
	BOOL IsLineVert()		{	return ( math_IsEqual(m_fAngle, 90) || math_IsEqual(m_fAngle, 270) );		}
	BOOL IsLineNormal()		{	return ! IsLineVert();		}

	BOOL IsPositiveDirPoint(double x, double y);
	BOOL IsPositiveDirPoint(CXDrawData_Point *point)	{	return IsPositiveDirPoint(point->m_fX, point->m_fY);	}
	void Init_K_B_by_XY();
	void Init_K_by_Angle();
};

//2021-9-7  lijunqing 
class CXDrawData_Line_Ex : public CXDrawData_LineBase
{
public:
	//直线的起始点
	double  *m_fXb;
	double  *m_fYb;

	//直线的终止点
	double  *m_fXe;
	double  *m_fYe;

	CXDrawData_Line_Ex();
	CXDrawData_Line_Ex(double *xb, double *yb, double *xe, double *ye)
	{
		m_fXb = xb;	m_fYb = yb;
		m_fXe = xe;	m_fYe = ye;
	}

	virtual ~CXDrawData_Line_Ex();
	
public:
	virtual DWORD GetDrawDataType()	{	return XDRAW_DATA_LINE;	}
	virtual void Init();
	virtual void DataCopy(CXDrawDataBase *pDest);

	virtual void GetBeginPoint(double &x, double &y);
	virtual void GetEndPoint(double &x, double &y);
	virtual void SetBeginPoint(double *x, double *y);
	virtual void SetEndPoint(double *x, double *y);

	virtual void CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)	
	{	
		xdraw_cal_min_max(*m_fXb, *m_fYb, fMinX, fMinY, fMaxX, fMaxY);	
		xdraw_cal_min_max(*m_fXe, *m_fYe, fMinX, fMinY, fMaxX, fMaxY);	
	}

public:
	void	InitLine(double fAngle,double fx,double fy);
	void	InitLine(double fLengthUse);
	BOOL IsLineVert()		{	return ( math_IsEqual(m_fAngle, 90) || math_IsEqual(m_fAngle, 270) );		}
	BOOL IsLineNormal()		{	return ! IsLineVert();		}

	BOOL IsPositiveDirPoint(double x, double y);
	BOOL IsPositiveDirPoint(CXDrawData_Point *point)	{	return IsPositiveDirPoint(point->m_fX, point->m_fY);	}
	void Init_K_B_by_XY();
	void Init_K_by_Angle();
};


class CXDrawData_Circle : public CXDrawDataBase
{
public:
	double  m_fXCenter;
	double  m_fYCenter;
	double  m_fXRadius;
	double  m_fYRadius;

	CXDrawData_Circle();
	virtual ~CXDrawData_Circle();

public:
	virtual DWORD GetDrawDataType()	{	return XDRAW_DATA_CIRCLE;	}
	virtual void Init();
	virtual void DataCopy(CXDrawDataBase *pDest);

	virtual void GetBeginPoint(double &x, double &y);
	virtual void GetEndPoint(double &x, double &y);
	virtual void SetBeginPoint(double x, double y);
	virtual void SetEndPoint(double x, double y);
	virtual void CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)	
	{	
		xdraw_cal_min_max(m_fXCenter+m_fXRadius, m_fYCenter + m_fYRadius, fMinX, fMinY, fMaxX, fMaxY);	
		xdraw_cal_min_max(m_fXCenter-m_fXRadius, m_fYCenter - m_fYRadius, fMinX, fMinY, fMaxX, fMaxY);	
	}

public:
	double GetPointAngle(double x, double y);
	double GetLenToCenter(double x, double y)	{	return xdraw_CalLengthPoints(x, y, m_fXCenter, m_fYCenter);	}
};

#define ARC_CLOCKWISE_CW     0
#define ARC_CLOCKWISE_CCW   1

class CXDrawData_Arc : public CXDrawData_Circle
{
public:
	double  m_fAngleBegin;  //单位为角度（不是弧度）
	double  m_fAngleEnd;
	UINT m_nClockwise;  //

	CXDrawData_Arc();
	virtual ~CXDrawData_Arc();

	void GetTangent(double x, double y, CXDrawData_Line &oLine);
	BOOL IsCW()		{	return (ARC_CLOCKWISE_CW == m_nClockwise);	}
	BOOL IsCCW()	{	return (ARC_CLOCKWISE_CCW == m_nClockwise);	}

public:
	virtual DWORD GetDrawDataType()	{	return XDRAW_DATA_ARC;	}
	virtual void Init();
	virtual void DataCopy(CXDrawDataBase *pDest);
	virtual void SetBeginPoint(double x, double y);
	virtual void SetEndPoint(double x, double y);

public:
	BOOL IsAngleInArc(double dAngle);
	BOOL IsPointOnArc(double x, double y);
	BOOL IsPointOnArc(CXDrawData_Point *point)	{	return IsPointOnArc(point->m_fX, point->m_fY);	}
	virtual void GetBeginPoint(double &x, double &y);
	virtual void GetEndPoint(double &x, double &y);
	virtual void GetBeginEndPoint(double &fxb, double &fyb, double &fxe, double &fye);
	virtual void CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)	;
};

class CXDrawData_Points : public CXDrawDataBase
{
public:
	long m_nPoints;  //当前使用的点数
	long m_nPointsMax; //当前缓冲区最大的点数
	PXDRAWDATA_POINT m_pPoints;
	bool m_bIsAutoClose;

	CXDrawData_Points();
	virtual ~CXDrawData_Points();

private:
	void FreePoints();

public:
	virtual DWORD GetDrawDataType()	{	return XDRAW_DATA_POINTS;	}
	virtual void Init();
	virtual void DataCopy(CXDrawDataBase *pDest);
	virtual void GetBeginPoint(double &x, double &y);
	virtual void GetEndPoint(double &x, double &y);
	virtual void SetBeginPoint(double x, double y);
	virtual void SetEndPoint(double x, double y);
	virtual void CalMinMax(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

	void SetPointsMax(long nPointsMax);
	void ExpandPointsMax(long nPointsExpand);
	BOOL HasPoints()	{	return m_nPoints < m_nPointsMax;	}
	void AddPoint(double x, double y);
	void AddPointEx(double x, double y);

	void InitPoints(long nPoints);
};

long xdraw_SolveEquation(CXDrawDataBase *pDrawData1, CXDrawDataBase *pDrawData2, CXDrawDatas &listIntersect);

long xdraw_SolveEquation(CXDrawData_Circle *pCircle, CXDrawData_Line *pLine, CXDrawDatas &listIntersect);
long xdraw_SolveEquation(CXDrawData_Line *pLine, CXDrawData_Circle *pCircle, CXDrawDatas &listIntersect);

long xdraw_SolveEquation(CXDrawData_Arc *pArc, CXDrawData_Line *pLine, CXDrawDatas &listIntersect);
long xdraw_SolveEquation(CXDrawData_Line *pLine, CXDrawData_Arc *pArc, CXDrawDatas &listIntersect);
long xdraw_SolveEquation(CXDrawData_Arc *pArc, CXDrawData_Line *pLine, CXDrawDatas &listIntersect, BOOL bIner);

long xdraw_SolveEquation(CXDrawData_Line *pLine1, CXDrawData_Line*pLine2,CXDrawDatas &listIntersect);

long xdraw_SolveEquation(CXDrawData_Circle *pCircle1,CXDrawData_Circle *pCircle2, CXDrawDatas &listIntersect);

