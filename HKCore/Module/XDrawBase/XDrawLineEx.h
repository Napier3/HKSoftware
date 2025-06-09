//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawLine.h  CXDrawLine_Ex

#pragma once

#include "XDrawGlobal.h"

#include "XDrawBase.h"


class CXDrawLine_Ex : public CXDrawBase, public CXDrawData_Line_Ex
{
public:
	CXDrawLine_Ex();
	CXDrawLine_Ex(double *xb, double *yb, double *xe, double *ye);
	virtual ~CXDrawLine_Ex();

//重载函数
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWLINE_EX;   }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual void SetBeginPoint(double *x, double *y)		{	CXDrawData_Line_Ex::SetBeginPoint(x, y);	};
	virtual void SetEndPoint(double *x, double *y)		{	CXDrawData_Line_Ex::SetEndPoint(x, y);	};
	virtual void SetBeginPoint(double x, double y)	{	ASSERT (FALSE);	}
	virtual void SetEndPoint(double x, double y)	{	ASSERT (FALSE);	}

//私有成员变量
private:
	/////////作图中对应的点坐标
	CPoint	m_pointBegin;
	CPoint	m_pointEnd;

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

};
