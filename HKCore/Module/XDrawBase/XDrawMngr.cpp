//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawMngr.cpp  CXDrawMngr


#include "stdafx.h"
#include "XDrawMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CXDrawMngr::CXDrawMngr()
{
    //初始化属性
    m_fXMax = -999999;
    m_fYMax = -999999;
    m_fXMin = 999999;
    m_fYMin = 999999;

    m_bXMin = FALSE;
    m_bXMax = FALSE;
    m_bYMin = FALSE;
    m_bYMax = FALSE;

    m_rcBorder.left = 0;
    m_rcBorder.top = 0;
    m_rcBorder.right = 400;
    m_rcBorder.bottom = 300;

    //初始化成员变量
    SetBackColor(RGB(255, 255, 255));

    //////////////////////鼠标放大
    m_iMouseZoomNow=0;	//是否处于鼠标放大的状态
    m_iLBPushNum=0;		//鼠标按下的次数
    m_iMouseInCurveRegion=0;//鼠标点是否位于图形的区域之内
}

void CXDrawMngr::InitXDrawMngr()
{
    DeleteAll();

}

CXDrawMngr::~CXDrawMngr()
{
}

long CXDrawMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);
    CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strAxisKey, oNode, m_strAxis);
    xml_GetAttibuteValue(pXmlKeys->m_strXMaxKey, oNode, m_fXMax);
    xml_GetAttibuteValue(pXmlKeys->m_strYMaxKey, oNode, m_fYMax);
    xml_GetAttibuteValue(pXmlKeys->m_strXMinKey, oNode, m_fXMin);
    xml_GetAttibuteValue(pXmlKeys->m_strYMinKey, oNode, m_fYMin);
    return 0;
}

long CXDrawMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strAxisKey, oElement, m_strAxis);
    xml_SetAttributeValue(pXmlKeys->m_strXMaxKey, oElement, m_fXMax);
    xml_SetAttributeValue(pXmlKeys->m_strYMaxKey, oElement, m_fYMax);
    xml_SetAttributeValue(pXmlKeys->m_strXMinKey, oElement, m_fXMin);
    xml_SetAttributeValue(pXmlKeys->m_strYMinKey, oElement, m_fYMin);
    return 0;
}

long CXDrawMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
    if(oBinaryBuffer.IsCalSizeMode())
    {
        BinarySerializeCalLen(oBinaryBuffer, m_strAxis);
        BinarySerializeCalLen(oBinaryBuffer, m_fXMax);
        BinarySerializeCalLen(oBinaryBuffer, m_fYMax);
        BinarySerializeCalLen(oBinaryBuffer, m_fXMin);
        BinarySerializeCalLen(oBinaryBuffer, m_fYMin);
    }
    else if(oBinaryBuffer.IsReadMode())
    {
        BinarySerializeRead(oBinaryBuffer, m_strAxis);
        BinarySerializeRead(oBinaryBuffer, m_fXMax);
        BinarySerializeRead(oBinaryBuffer, m_fYMax);
        BinarySerializeRead(oBinaryBuffer, m_fXMin);
        BinarySerializeRead(oBinaryBuffer, m_fYMin);
    }
    else if(oBinaryBuffer.IsWriteMode())
    {
        BinarySerializeWrite(oBinaryBuffer, m_strAxis);
        BinarySerializeWrite(oBinaryBuffer, m_fXMax);
        BinarySerializeWrite(oBinaryBuffer, m_fYMax);
        BinarySerializeWrite(oBinaryBuffer, m_fXMin);
        BinarySerializeWrite(oBinaryBuffer, m_fYMin);
    }
    return 0;
}
//
// BOOL CXDrawMngr::IsEqualOwn(CBaseObject* pObj)
// {
// 	if(this == pObj)
// 	{
// 		return TRUE;
// 	}
//
// 	CXDrawMngr *p = (CXDrawMngr*)pObj;
//
// 	if(m_strAxis != p->m_strAxis)
// 	{
// 		return FALSE;
// 	}
//
// 	if(m_fXMax != p->m_fXMax)
// 	{
// 		return FALSE;
// 	}
//
// 	if(m_fYMax != p->m_fYMax)
// 	{
// 		return FALSE;
// 	}
//
// 	if(m_fXMin != p->m_fXMin)
// 	{
// 		return FALSE;
// 	}
//
// 	if(m_fYMin != p->m_fYMin)
// 	{
// 		return FALSE;
// 	}
//
// 	return TRUE;
// }
//
// BOOL CXDrawMngr::CopyOwn(CBaseObject* pDest)
// {
// 	if(this == pDest)
// 	{
// 		return TRUE;
// 	}
//
// 	CXDrawMngr *p = (CXDrawMngr*)pDest;
//
// 	p->m_strAxis = m_strAxis;
// 	p->m_fXMax = m_fXMax;
// 	p->m_fYMax = m_fYMax;
// 	p->m_fXMin = m_fXMin;
// 	p->m_fYMin = m_fYMin;
// 	return TRUE;
// }
//
// CBaseObject* CXDrawMngr::Clone()
// {
// 	CXDrawMngr *p = new CXDrawMngr();
// 	Copy(p);
// 	return p;
// }
//
// BOOL CXDrawMngr::CanPaste(UINT nClassID)
// {
// 	if (nClassID == DWCLASSID_CXDRAWLIST)
// 	{
// 		return TRUE;
// 	}
//
// 	return FALSE;
// }

CExBaseObject* CXDrawMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
    CExBaseObject *pNew  = NULL;
    CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;


    if (strClassID == pXmlKeys->m_strCXDrawListKey)
    {
        pNew = new CXDrawList();
    }

    return pNew;
}

CExBaseObject* CXDrawMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
    CExBaseObject *pNew  = NULL;


    if (nClassID == DWCLASSID_CXDRAWLIST)
    {
        pNew = new CXDrawList();
    }

    return pNew;
}
//
// CXDrawList* CXDrawMngr::FindByID(const CString &strID)
// {
// 	CXDrawList *p = NULL;
// 	CXDrawList *pFind = NULL;
// 	POS pos = GetHeadPosition();
//
// 	while (pos != NULL)
// 	{
// 		p = (CXDrawList*)GetNext(pos);
//
// 		if (p->m_strID == strID)
// 		{
// 			pFind = p;
// 			break;
// 		}
// 	}
//
// 	return pFind;
// }

CXDrawList* CXDrawMngr::AddNew(const CString &strID)
{
    CXDrawList *pFind = (CXDrawList*)FindByID(strID);

    if (pFind != NULL)
    {
        return NULL;
    }

    pFind = new CXDrawList();
    pFind->m_strID = strID;
    AddTail(pFind);
    pFind->SetParent(this);

    return pFind;
}

CXDrawList* CXDrawMngr::AddNewByFile(const CString &strFile)
{
    CXDrawList *pFind = new CXDrawList();
    pFind->OpenXmlFile(strFile, CXDrawXmlRWKeys::CXDrawListKey(), CXDrawXmlRWKeys::g_pXmlKeys);

    AddTail(pFind);
    pFind->SetParent(this);

    return pFind;
}

///////定义鼠标放大功能///////#############################################################################
void  CXDrawMngr::SetBorder(const CRect &rcBorder, CDC *pDC, BOOL bUseMngrAxisRange)
{
    m_rcBorder = rcBorder;

#ifndef XDrawMngr_NO_MemBufferDC
    m_oMembufferDC.Create(pDC, m_rcBorder);
#endif

    AdjustAxis(bUseMngrAxisRange);

    LogicPointToDevicePoint();
}

void  CXDrawMngr::Draw(CDC *pDC, long nLeft, long nTop, long nWidth, long nHeight)
{
#ifndef XDrawMngr_NO_MemBufferDC
    CDC *pMemDC = m_oMembufferDC.GetDC();
#else
	CDC *pMemDC = pDC;
#endif

    if (pMemDC == NULL)
    {
        return;
    }

    //背景色
#ifndef XDrawMngr_NO_MemBufferDC
    m_oMembufferDC.FillSolidRect(m_crBack);
#else
	pMemDC->FillSolidRect(m_rcBorder, m_crBack);
#endif

    //坐标系绘图
    DrawAxis(pMemDC);

    //绘制曲线图
    POS pos = GetHeadPosition();
    CXDrawList *pDrawList = NULL;

    while (pos != NULL)
    {
        pDrawList = (CXDrawList *)GetNext(pos);
        pDrawList->Draw(pMemDC, 1, CPoint(0, 0));
    }

#ifndef XDrawMngr_NO_MemBufferDC
    m_oMembufferDC.EndDC();
    m_oMembufferDC.BitBlt(nLeft, nTop, nWidth, nHeight,pDC, 0, 0, SRCCOPY);
#endif
}

void  CXDrawMngr::Draw(CDC *pDC)
{
    Draw(pDC, m_rcBorder.left, m_rcBorder.top, m_rcBorder.Width(), m_rcBorder.Height());
}

void CXDrawMngr::LogicPointToDevicePoint(CAxisInterface *pAxis)
{
    POS pos = GetHeadPosition();
    CXDrawList *pDrawList = NULL;

    while (pos != NULL)
    {
        pDrawList = (CXDrawList *)GetNext(pos);
        pDrawList->LogicPointToDevicePoint(pAxis);
    }
}

void CXDrawMngr::LogicPointToDevicePoint()
{
    CAxisInterface *pAxisInterface = NULL;
    GetAxisInterface(&pAxisInterface);

    if (pAxisInterface != NULL)
    {
        LogicPointToDevicePoint(pAxisInterface);
    }
}


void  CXDrawMngr::GetLogicBorder(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
	//绘制曲线图
	POS pos = GetHeadPosition();
	CXDrawList *pDrawList = NULL;

	while (pos != NULL)
	{
		pDrawList = (CXDrawList *)GetNext(pos);
		pDrawList->GetLogicBorder(dXMin, dYMin, dXMax, dYMax);
	}
}


//////////////////////////////////////////////////////////////////////////
//
BOOL CXDrawMngr::OnLButtonDown(UINT nFlags, CPoint point, CDC *pDC)
{
    if (m_iMouseZoomNow)
    {
        OnMouseZoomLBDown(point, pDC);
        return TRUE;
    }

    return FALSE;
}

BOOL CXDrawMngr::OnLButtonUp(UINT nFlags, CPoint point, CDC *pDC)
{
    if (m_iMouseZoomNow)
    {
        OnMouseZoomLBUp(point, pDC);
        return TRUE;
    }

    return FALSE;
}

BOOL CXDrawMngr::OnMouseMove(UINT nFlags, CPoint point, CDC *pDC)
{
    if (m_iMouseZoomNow)
    {
        OnMouseZoomMove(point, pDC);
        return TRUE;
    }

    return FALSE;
}


///////定义鼠标放大功能///////#############################################################################
//处理鼠标放大时的鼠标移动
BOOL CXDrawMngr::OnMouseZoomMove(CPoint point, CDC *pDC)
{
#ifndef _PSX_IDE_QT_
    CRect	rectWorkArea=m_rcBorder;

    if(m_iLBPushNum==0)	//鼠标选择第一点
    {
        if(rectWorkArea.PtInRect(point))
        {
            m_iMouseInCurveRegion=1;
            ::SetCursor(AfxGetApp()->LoadCursor(m_n_CURSOR_ZOOM));
            return TRUE;
        }
        else
        {
            m_iMouseInCurveRegion=0;
            return FALSE;
        }
    }
    else	//鼠标移动，绘制放大的选择区域
    {
        ::SetCursor(AfxGetApp()->LoadCursor(m_n_CURSOR_ZOOM));
        CDC *pDC=m_pRefWnd->GetDC();
        CRect rect=GetRectFromPoint(m_pointOrigin,m_pointOld);
        long ll=pDC->SetROP2(R2_NOT);
        CGdiObject * pObj=pDC->SelectStockObject(NULL_BRUSH);
        pDC->Rectangle(rect);
        rect=GetRectFromPoint(m_pointOrigin,point);
        pDC->Rectangle(rect);
        m_pointOld=point;
        pDC->SelectObject(pObj);
        pDC->SetROP2(ll);
        m_pRefWnd->ReleaseDC(pDC);
    }
#endif

    return TRUE;
}
//处理鼠标放大时的鼠标左键弹起
void CXDrawMngr::OnMouseZoomLBUp(CPoint point, CDC *pDC)
{
#ifndef _PSX_IDE_QT_
    if(m_iMouseInCurveRegion==0)
        return;
    if(m_iLBPushNum>0)
    {
        m_iLBPushNum=0;
        CDC *pDC=m_pRefWnd->GetDC();
        CRect rect=GetRectFromPoint(m_pointOrigin,m_pointOld);
        long ll=pDC->SetROP2(R2_NOT);
        CGdiObject * pObj=pDC->SelectStockObject(NULL_BRUSH);
        pDC->Rectangle(rect);
        rect=GetRectFromPoint(m_pointOrigin,point);
        //pDC->Rectangle(rect);
        m_pointOld=point;
        pDC->SelectObject(pObj);
        pDC->SetROP2(ll);
        m_pRefWnd->ReleaseDC(pDC);
        ReleaseCapture();
        m_iMouseInCurveRegion=0;
        ::ClipCursor(NULL);
        MouseMoveZoom();
    }
#endif
}
//处理鼠标放大时的鼠标左键按下
BOOL CXDrawMngr::OnMouseZoomLBDown(CPoint point, CDC *pDC)
{
#ifndef _PSX_IDE_QT_
    if(m_iMouseInCurveRegion==0)
        return FALSE;
    CRect	rectWorkArea=m_rcBorder;
    m_pointOrigin=m_pointOld=point;
    m_iLBPushNum=1;
    m_pRefWnd->SetCapture();
    CRect	rect=rectWorkArea;
    m_pRefWnd->ClientToScreen(&rect);
    ::ClipCursor(&rect);
    ::SetCursor(AfxGetApp()->LoadCursor(m_n_CURSOR_ZOOM));
#endif
    return TRUE;
}
//鼠标左键放大实现函数
void CXDrawMngr::MouseMoveZoom()
{
    double fMinX,fMaxX,fMinY,fMaxY;
    double fx,fy;
    if(m_pointOrigin==m_pointOld)return;

    CRect rectZoom=GetRectFromPoint(m_pointOrigin,m_pointOld);
    DevicePointToLogicPoint(rectZoom.TopLeft(),&fx,&fy);
    fMinX=fx;fMaxY=fy;
    DevicePointToLogicPoint(rectZoom.BottomRight(),&fx,&fy);
    fMaxX=fx;fMinY=fy;

    SetAxisRange(fMinX, fMinY, fMaxX, fMaxY);
}

CRect CXDrawMngr::GetRectFromPoint(CPoint pt1,CPoint pt2)
{
    CRect rect;
    if(pt1.x>pt2.x)
    {
        rect.left=pt2.x;
        rect.right=pt1.x;
    }
    else
    {
        rect.left=pt1.x;
        rect.right=pt2.x;
    }
    if(pt1.y>pt2.y)
    {
        rect.top=pt2.y;
        rect.bottom=pt1.y;
    }
    else
    {
        rect.top=pt1.y;
        rect.bottom=pt2.y;
    }

    return rect;
}

//图形下下移动
void CXDrawMngr::MoveDown(double dOffset)
{
    double fMinX = m_fXMin,fMaxX = m_fXMax,fMinY = m_fYMin, fMaxY = m_fYMax;
    fMinY += dOffset;
    fMaxY += dOffset;

    SetAxisRange(fMinX, fMinY, fMaxX, fMaxY);
}
//图形向左移动
void CXDrawMngr::MoveLeft(double dOffset)
{
    double fMinX = m_fXMin,fMaxX = m_fXMax,fMinY = m_fYMin, fMaxY = m_fYMax;
    fMinX += dOffset;
    fMaxX += dOffset;

    SetAxisRange(fMinX, fMinY, fMaxX, fMaxY);
}
//图形向右移动
void CXDrawMngr::MoveRight(double dOffset)
{
    double fMinX = m_fXMin,fMaxX = m_fXMax,fMinY = m_fYMin, fMaxY = m_fYMax;
    fMinX -= dOffset;
    fMaxX -= dOffset;

    SetAxisRange(fMinX, fMinY, fMaxX, fMaxY);
}

//图形向上移动
void CXDrawMngr::MoveUp(double dOffset)
{
    double fMinX = m_fXMin,fMaxX = m_fXMax,fMinY = m_fYMin, fMaxY = m_fYMax;
    fMinY -= dOffset;
    fMaxY -= dOffset;

    SetAxisRange(fMinX, fMinY, fMaxX, fMaxY);
}

double CXDrawMngr::GetXMoveOffset(double dMoveRate)
{
    dMoveRate = fabs(dMoveRate);
    return dMoveRate * (m_fXMax - m_fXMin);
}

double CXDrawMngr::GetYMoveOffset(double dMoveRate)
{
    dMoveRate = fabs(dMoveRate);
    return dMoveRate * (m_fYMax - m_fYMin);
}

void CXDrawMngr::InitDrawLineColor(const COLORREF &oColor)
{
	POS pos = GetHeadPosition();
	CXDrawList *pDrawList = NULL;

	while (pos != NULL)
	{
		pDrawList = (CXDrawList *)GetNext(pos);
		pDrawList->InitDrawLineColor(oColor);
	}
}


