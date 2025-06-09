//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawLine.cpp  CXDrawLine_Ex


#include "stdafx.h"
#include "XDrawLineEx.h"
#include "../BaseClass/ComplexNumber.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXDrawLine_Ex::CXDrawLine_Ex()
{
	//初始化属性
	m_fXb = 0;
	m_fYb = 0;
	m_fXe = 0;
	m_fYe = 0;
	m_nStyle = 0;
	m_nWidth = 0;

	//初始化成员变量
}

CXDrawLine_Ex::CXDrawLine_Ex(double *xb, double *yb, double *xe, double *ye)
: CXDrawData_Line_Ex(xb, yb, xe, ye)
{

}

CXDrawLine_Ex::~CXDrawLine_Ex()
{
}

BOOL CXDrawLine_Ex::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXDrawBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXDrawLine_Ex *p = (CXDrawLine_Ex*)pObj;

	if(*m_fXb != *p->m_fXb)
	{
		return FALSE;
	}

	if(*m_fYb != *p->m_fYb)
	{
		return FALSE;
	}

	if(*m_fXe != *p->m_fXe)
	{
		return FALSE;
	}

	if(*m_fYe != *p->m_fYe)
	{
		return FALSE;
	}

	if(m_nStyle != p->m_nStyle)
	{
		return FALSE;
	}

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXDrawLine_Ex::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXDrawBase::CopyOwn(pDest);

	CXDrawLine_Ex *p = (CXDrawLine_Ex*)pDest;

	p->m_fXb = m_fXb;
	p->m_fYb = m_fYb;
	p->m_fXe = m_fXe;
	p->m_fYe = m_fYe;

	return TRUE;
}

CBaseObject* CXDrawLine_Ex::Clone()
{
	CXDrawLine_Ex *p = new CXDrawLine_Ex();
	Copy(p);
	return p;
}

void CXDrawLine_Ex::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
	pAxis->LogicPointToDevicePoint(*m_fXb, *m_fYb, &m_pointBegin);
	pAxis->LogicPointToDevicePoint(*m_fXe, *m_fYe, &m_pointEnd);
}


void CXDrawLine_Ex::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CPen cp,*pOldPen;

	switch(m_dwState)
	{
	case XDRAW_STATE_NORMAL:
		{
			cp.CreatePen(m_nStyle,m_nWidth,m_crForeColor);
			break;
		}
	case XDRAW_STATE_PICKED:
		{
			cp.CreatePen(m_nPickStyle,m_nPickWidth,m_crPickColor);
			break;
		}
	default:
		{
			cp.CreatePen(m_nStyle,m_nWidth,m_crForeColor);
			break;
		}
	}

	pOldPen=pDC->SelectObject(&cp);
	pDC->MoveTo(m_pointBegin);
	pDC->LineTo(m_pointEnd);
	pDC->SelectObject(pOldPen);
	cp.DeleteObject();		

}

void CXDrawLine_Ex::Pick(const CPoint &point, CExBaseList &oList)
{

}

void CXDrawLine_Ex::GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	CalMinMax(fMinX, fMinY, fMaxX, fMaxY);
}
