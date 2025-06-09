// DynAxisSys.cpp : implementation file
//

#include "stdafx.h"
#include "DynAxisSys.h"
#include "../Api/GloblaDrawFunctions.h"
#include "../Api/StringApi.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////
///CDynAxis
void CDynAxis::LogicPointToDevicePoint(double x, double y, CPoint *pPoint, long nAxisIndex)
{
    if (m_pRuler != 0)
    {
        m_pRuler->LogicPointToDevicePoint(x, y, pPoint, nAxisIndex);
    }
    if (m_pRulerLog != 0)
    {
        m_pRulerLog->LogicPointToDevicePoint(x, y, pPoint, nAxisIndex);
    }

/*
    if (m_nAxisID == RULER_ID_X)
    {

    }
    else
    {

    }
*/
}

void CDynAxis::DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex)
{
    if (m_pRuler != 0)
    {
        m_pRuler->DevicePointToLogicPoint(point, x, y);
    }
    if (m_pRulerLog != 0)
    {
        m_pRulerLog->DevicePointToLogicPoint(point, x, y);
    }

/*
    if (m_nAxisID == RULER_ID_X)
    {

    }
    else
    {

    }
*/
}

void CDynAxis::LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex)
{

}

void CDynAxis::DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex)
{

}

void CDynAxis::GetAxisDrawArea(CRect &rcArea)
{
    rcArea = GetWorkArea();
}

void CDynAxis::GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{

}

void CDynAxis::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{

}

CRect CDynAxis::GetWorkArea()
{
    if (m_pRuler != 0)
    {
        return m_pRuler->GetWorkArea();
    }

    if (m_pRulerLog != 0)
    {
        return m_pRulerLog->GetWorkArea();
    }

    return CRect(0, 0, 100, 100);
}

void CDynAxis::SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax)
{
    if (m_nAxisID == RULER_ID_X)
    {
        if (m_pRuler != 0)
        {
            m_pRuler->SetAxisMinMax(dXMin, dXMin, dXMax, dXMax);
            m_pRuler->ResetAxis();
        }
        if (m_pRulerLog != 0)
        {
            m_pRulerLog->SetAxisMinMax(dXMin, dXMin, dXMax, dXMax);
            m_pRulerLog->ResetAxis();
        }
    }
    else
    {
        if (m_pRuler != 0)
        {
            m_pRuler->SetAxisMinMax(dYMin, dYMin, dYMax, dYMax);
            m_pRuler->ResetAxis();
        }
        if (m_pRulerLog != 0)
        {
            m_pRulerLog->SetAxisMinMax(dYMin, dYMin, dYMax, dYMax);
            m_pRulerLog->ResetAxis();
        }
    }
}

//lijunqing 2024-6-20
void CDynAxis::LogicPointToDevicePoint(double *pfBuff, CPoint *pPointBuf, long nDatasCount, long nAxisIndex)
{
	if (m_pRuler != 0)
	{
		m_pRuler->LogicPointToDevicePoint(pfBuff, pPointBuf, nDatasCount, nAxisIndex);
	}
	if (m_pRulerLog != 0)
	{
		m_pRulerLog->LogicPointToDevicePoint(pfBuff, pPointBuf, nDatasCount, nAxisIndex);
	}
}

CDynAxis::CDynAxis()
{
    m_pRulerLog = NULL;
    m_pRuler = NULL;

    m_fAxisMin = 0;
    m_fAxisMax = 10;
    m_nAxisID = RULER_ID_X;
    m_nAxisType = RULER_TYPE_DESCARTES;
}

CDynAxis::~CDynAxis()
{
	if (m_pRulerLog != NULL)
	{
		delete m_pRulerLog;
		m_pRulerLog = NULL;
	}

	if (m_pRuler != NULL)
	{
		delete m_pRuler;
		m_pRuler = NULL;
	}
}

void CDynAxis::SetAxisID_X()
{
    m_nAxisID = RULER_ID_X;
}

void CDynAxis::SetAxisID_Y()
{
    m_nAxisID = RULER_ID_Y;
}

void CDynAxis::SetAxisType_Ruler()
{
    if (m_nAxisType == RULER_TYPE_DESCARTES
            && m_pRuler != 0 )
    {
        return;
    }

    if (m_pRulerLog != NULL)
    {
        delete m_pRulerLog;
        m_pRulerLog = NULL;
    }

    m_pRuler = new CRulerAxis();
    m_nAxisType = RULER_TYPE_DESCARTES;

    if (m_nAxisID == RULER_ID_X)
    {
        m_pRuler->SetRulerTypeHorz();
        m_pRuler->SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);
    }
    else
    {
        m_pRuler->SetRulerTypeVert();
        m_pRuler->SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);//RULER_DIRECTION_LEFTUP);
    }

	m_pRuler->SetRulerBoderShow(0);
    m_pRuler->SetRulerBackColor(RGB(255, 255, 255));
}

void CDynAxis::SetAxisType_RulerLog()
{
    if (m_nAxisType == RULER_TYPE_LOG
            && m_pRulerLog != 0)
    {
        return;
    }

    if (m_pRuler != NULL)
    {
        delete m_pRuler;
        m_pRuler = NULL;
    }

    m_pRulerLog = new CRulerLogAxis();
    m_nAxisType = RULER_TYPE_LOG;

    if (m_nAxisID == RULER_ID_X)
    {
        m_pRulerLog->SetRulerTypeHorz();
        m_pRulerLog->SetRulerDirection(RULER_DIRECTION_RIGHTDOWN);
    }
    else
    {
        m_pRulerLog->SetRulerTypeVert();
        m_pRulerLog->SetRulerDirection(RULER_DIRECTION_LEFTUP);
    }

	//m_pRulerLog->SetRulerBoderShow(0);
    //m_pRulerLog->SetRulerBackColor(RGB(255, 255, 255));
}

void CDynAxis::SetAxisType(long nAxisType)
{
    if (nAxisType == RULER_TYPE_DESCARTES)
    {
       SetAxisType_Ruler();
       return;
    }

    if (nAxisType == RULER_TYPE_LOG)
    {
       SetAxisType_RulerLog();
       return;
    }

    SetAxisType_Ruler();
}

void CDynAxis::SetBorder(CRect &rcBorder)
{
    if(m_pRuler != 0)
    {
        m_pRuler->SetBorder(rcBorder);
    }

    if(m_pRulerLog != 0)
    {
        m_pRulerLog->SetBorder(rcBorder);
    }
}

void CDynAxis::DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset)
{
    if(m_pRuler != 0)
    {
        m_pRuler->DrawAxis(pDC, fZoomRatio, xOffset, yOffset);
    }

    if(m_pRulerLog != 0)
    {
        m_pRulerLog->DrawAxis(pDC, fZoomRatio, xOffset, yOffset);
    }
}

CAxisScaleDataList* CDynAxis::GetAxisScaleDataList()
{
	if(m_pRuler != 0)
	{
		return &m_pRuler->m_listRulerScale;
	}

	if(m_pRulerLog != 0)
	{
		return &m_pRulerLog->m_listRulerScale;
	}

	return 0;
}

void CDynAxis::SetAxisBKColor(COLORREF cr)
{
	if(m_pRuler != 0)
	{
		m_pRuler->SetRulerBackColor(cr);
	}

	if(m_pRulerLog != 0)
	{
		m_pRulerLog->SetAxisBackColor(cr);
	}
}

void CDynAxis::SetAxisSize(long nSize)
{
	if(m_pRuler != 0)
	{
		m_pRuler->SetRulerHeight(nSize);
	}

	if(m_pRulerLog != 0)
	{
		m_pRulerLog->SetRulerHeight(nSize);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
///CDynAxisSys
CDynAxisSys::CDynAxisSys()
{
	m_nDrawStyle = DYN_ALL;
	m_crAxisGrid = RGB(192,192,192);	
	m_crAxisCenter = RGB(0, 0, 0);
	m_crAxisBK = RGB(255, 255, 255);
	m_crViewBK = RGB(255, 255, 255);
	m_nAxisGridStyle = PS_DOT;

	m_nYAxisWidth = 35;
	m_nXAxisHeight = 25;

    m_oAxisX.SetAxisID_X();
    m_oAxisY.SetAxisID_Y();
}

CDynAxisSys::~CDynAxisSys()
{

}

void CDynAxisSys::LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint, long nAxisIndex)
{

}


void CDynAxisSys::LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex)
{
   
}

void CDynAxisSys::DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex)
{
    
}

//从实际坐标获取实际坐标所代表的值
void CDynAxisSys::DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex)
{
 
}

void CDynAxisSys::GetAxisDrawArea(CRect &rcArea)
{
 
}

void CDynAxisSys::GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
 
}

void CDynAxisSys::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{
 
}

CRect CDynAxisSys::GetWorkArea()
{
        return m_rcBoder;
}

void CDynAxisSys::SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax)
{
    m_oAxisX.SetAxisMinMax(dXMin, dXMin, dXMax, dXMax);
    m_oAxisY.SetAxisMinMax(dYMin, dYMin, dYMax, dYMax);
}



void CDynAxisSys::SetAxisType_X(const CString &strAxisType)
{
    long nAxis = axis_GetRulerAxisTypeByID(strAxisType);

    m_oAxisX.SetAxisType(nAxis);

	//添加属性设置的代码
	m_oAxisX.SetAxisSize(m_nXAxisHeight);
}

void CDynAxisSys::SetAxisType_Y(const CString &strAxisType)
{
    long nAxis = axis_GetRulerAxisTypeByID(strAxisType);

    m_oAxisY.SetAxisType(nAxis);

	//添加属性设置的代码
	m_oAxisY.SetAxisSize(m_nYAxisWidth);
}

void CDynAxisSys::SetAxisType_X_Descartes()
{
    SetAxisType_X(RULER_TYPE_ID_DESCARTES);
}

void CDynAxisSys::SetAxisType_Y_Descartes()
{
    SetAxisType_Y(RULER_TYPE_ID_DESCARTES);
}

void CDynAxisSys::SetAxisType_X_Log()
{
    SetAxisType_X(RULER_TYPE_ID_LOG);
}

void CDynAxisSys::SetAxisType_Y_Log()
{
    SetAxisType_Y(RULER_TYPE_ID_LOG);
}


void CDynAxisSys::SetBorder(CRect &rcBorder)
{
    m_rcBoder = rcBorder;
    ValidateBoder();

    CRect rc = m_rcBoder;
    rc.top = rc.bottom - m_nXAxisHeight;
	rc.left += m_nYAxisWidth;
    m_oAxisX.SetBorder(rc);

    rc = m_rcBoder;
    rc.right = rc.left + m_nYAxisWidth;
	rc.bottom -= m_nXAxisHeight;
    m_oAxisY.SetBorder(rc);

	m_rcWorkArea = m_rcBoder;
	m_rcWorkArea.left += m_nYAxisWidth;
	m_rcWorkArea.bottom -= m_nXAxisHeight;
}

void CDynAxisSys::DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset)
{
	if (m_nDrawStyle && DYN_BACK)
	{
		DrawRulerBack(pDC);
	}

    m_oAxisX.DrawAxis(pDC, fZoomRatio, xOffset, yOffset);
	m_oAxisY.DrawAxis(pDC, fZoomRatio, xOffset, yOffset);

	DrawXAxisLine(pDC, fZoomRatio, xOffset, yOffset);
	DrawYAxisLine(pDC, fZoomRatio, xOffset, yOffset);
}

void CDynAxisSys::ValidateBoder()
{
    if (m_rcBoder.Width() < 100)
    {
        m_rcBoder.right = m_rcBoder.left + 100;
    }

    if (m_rcBoder.Height() < 100)
    {
        m_rcBoder.bottom = m_rcBoder.top + 100;
    }
}

void CDynAxisSys::DrawXAxisLine(CDC *pDC,float fZoomRatio,long xOffset,long yOffset)
{
	CAxisScaleDataList* pAxisScales = m_oAxisX.GetAxisScaleDataList();

    if (pAxisScales == NULL)
    {
        return;
    }

	POS pos = pAxisScales->GetHeadPosition();
	CAxisScaleData *pScale = NULL;
	CPoint pt;
	CPoint ptOffset(xOffset, yOffset);

	while (pos != NULL)
	{
		pScale = (CAxisScaleData *)pAxisScales->GetNext(pos);

		if ((pScale->m_ptAxisScale.x < m_rcWorkArea.left) || (pScale->m_ptAxisScale.x > m_rcWorkArea.right))
		{
			continue;
		}


		pt.x = pScale->m_ptAxisScale.x;
		pt.y = m_rcWorkArea.top;
		pt.Offset(ptOffset);
		pDC->MoveTo(pt);

		pt.x = pScale->m_ptAxisScale.x;
		pt.y = m_rcWorkArea.bottom;
		pt.Offset(ptOffset);
		pDC->LineTo(pt);
	}
}

void CDynAxisSys::DrawYAxisLine(CDC *pDC,float fZoomRatio,long xOffset,long yOffset)
{
	CAxisScaleDataList* pAxisScales = m_oAxisY.GetAxisScaleDataList();

    if (pAxisScales == NULL)
    {
        return;
    }

    POS pos = pAxisScales->GetHeadPosition();
	CAxisScaleData *pScale = NULL;
	CPoint pt;
	CPoint ptOffset(xOffset, yOffset);

	while (pos != NULL)
	{
		pScale = (CAxisScaleData *)pAxisScales->GetNext(pos);

		if ((pScale->m_ptAxisScale.y < m_rcWorkArea.top) || (pScale->m_ptAxisScale.y > m_rcWorkArea.bottom))
		{
			continue;
		}


		pt.x = m_rcWorkArea.left;
		pt.y = pScale->m_ptAxisScale.y;
		pt.Offset(ptOffset);
		pDC->MoveTo(pt);

		pt.x = m_rcWorkArea.right;
		pt.y = pScale->m_ptAxisScale.y;
		pt.Offset(ptOffset);
		pDC->LineTo(pt);
	}

}


void CDynAxisSys::DrawRulerBack(CDC *pDC)
{
	//绘制背景
	CBrush brush;
	brush.CreateSolidBrush(m_crViewBK);
	pDC->FillRect(m_rcBoder,&brush);
	brush.DeleteObject();
}

