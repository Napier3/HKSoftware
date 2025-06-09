//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "XScdDrawGlobal.h"

#define XSCD_ARROW_OPEN            0
#define XSCD_ARROW_SOLID           1
#define XSCD_ARROW_SOLID_FILLED    2
#define XSCD_ARROW_DIAMOND         3
#define XSCD_ARROW_DIAMOND_FILLED  4
#define XSCD_ARROW_CIRCLE          5
#define XSCD_ARROW_CIRCLE_FILLED   6


class CXScdDrawLineBase : public CXDrawElements
{
public:
	CXScdDrawLineBase();
	virtual ~CXScdDrawLineBase();

	long m_nShow;
public:
	virtual UINT GetClassID() {    return XSCDDRAW_LINE_BASE;   }

public:
	CExBaseObject *m_pBeginObj;
	CExBaseObject *m_pEndObj;
	CXDrawElement *m_pBeginElement;
	CXDrawElement *m_pEndElement;
	CPoint m_ptBegin;
	CPoint m_ptEnd;

public:
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	BOOL IsError();

//重载函数
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void InitLinePos();
	virtual void InitToBusLinePos();

	virtual void DrawLine(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);
	virtual void DrawArrow(CDC *pDC, const CPoint &p1,const CPoint &p2,double theta=30,int length=10, int nArrowType=XSCD_ARROW_SOLID_FILLED);
};

class CXScdDrawLine_ToBus : public CXScdDrawLineBase
{
public:
	CXScdDrawLine_ToBus();
	virtual ~CXScdDrawLine_ToBus();
public:
	virtual UINT GetClassID() {    return XSCDDRAW_LINE_TOBUS;   }

public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void InitLinePos();

};



class CXScdDrawLine_Vert : public CXScdDrawLineBase
{
public:
	CXScdDrawLine_Vert();
	virtual ~CXScdDrawLine_Vert();

public:
	
      CPoint m_ptMainIedTurn; //靠近被测IED的一个拐点坐标
	  

public:
		virtual UINT GetClassID() {    return XSCDDRAW_LINE_VERT;   }

public:
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual CBaseObject* Clone();

};


class CXScdDrawLine_Horz : public CXScdDrawLineBase
{
public:
	CXScdDrawLine_Horz();
	virtual ~CXScdDrawLine_Horz();

public:
	
      CPoint pt_MainIedTurn; //靠近被测IED的一个拐点坐标
	  

public:
		virtual UINT GetClassID() {    return XSCDDRAW_LINE_HORZ;   }

public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual CBaseObject* Clone();

};

class CXScdDrawLine_Bus  : public CXScdDrawLineBase
{
public:
	CXScdDrawLine_Bus();
	virtual ~CXScdDrawLine_Bus();

public:

public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void AddLine(CXScdDrawLineBase *pLine);
};


class CXScdDrawLine_GooseBus : public CXScdDrawLine_Bus
{
public:
	CXScdDrawLine_GooseBus();
	virtual ~CXScdDrawLine_GooseBus();
public:
		virtual UINT GetClassID() {    return XSCDDRAW_LINE_GOOSEBUS;   }
};


class CXScdDrawLine_SvBus : public CXScdDrawLine_Bus
{
public:
	CXScdDrawLine_SvBus();
	virtual ~CXScdDrawLine_SvBus();

public:
	virtual UINT GetClassID() {    return XSCDDRAW_LINE_SVBUS;   }
};

#define XSCDDRAW_PICK_RADIUS   4

CRect xscddraw_GetMinRectBox(const CPoint &ptBegin, const CPoint &ptEnd);
BOOL xscddraw_IsInMinRectBox(const CPoint &ptCurr, const CPoint &ptBegin, const CPoint &ptEnd);
double xscddraw_GetLineAngle(const CPoint &ptBegin, const CPoint &ptEnd);
BOOL xscddraw_PickLine(const CPoint &ptCurr, const CPoint &ptBegin, const CPoint &ptEnd);

//////////////////////////////////////////////////////////////////////////
//
class CXScdDrawLines : public CXDrawElements
{
public:
	CXScdDrawLines();
	virtual ~CXScdDrawLines();

public:
	virtual void Pick(const CPoint &point, CExBaseList &oList);

	CXScdDrawLineBase* FindByBeginObj(CExBaseObject *pObj);
	CXScdDrawLineBase* FindByEndObj(CExBaseObject *pObj);
	void RemoveErrorLines();
};