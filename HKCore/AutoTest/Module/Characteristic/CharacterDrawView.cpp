//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewIedCfg.cpp  CXScdDrawViewIedCfg


#include "stdafx.h"
#include "CharacterDrawView.h"

#include "../../../Module/XDrawBase/XDrawMngrDescartes.h"
#include "../../../Module/XDrawBase/XDrawMngrLogarithm.h"

#ifndef _PSX_IDE_QT_
#ifndef _PSX_QT_LINUX_
#include "../../../Module/BaseClass/DIB.h"
#endif
#endif

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharacterDrawView::CCharacterDrawView()
{
	//初始化属性
	m_pCharacteristic = NULL;
	m_pCharacteristics       = NULL;

	//初始化成员变量
	m_pXDrawMngr_Axis = NULL;
	m_pCurrTestPoint = NULL;
	m_bCalCharTemp = FALSE;
	m_strAxis = AXIS_TYPE_ID_CARTES;
	m_ptMouseMoveBegin.x = -1;
	m_ptMouseMoveBegin.y = -1;
}

CCharacterDrawView::~CCharacterDrawView()
{
	if (m_pXDrawMngr_Axis != NULL)
	{
		delete m_pXDrawMngr_Axis;
		m_pXDrawMngr_Axis = NULL;
	}

	if (m_pCurrTestPoint != NULL)
	{
		delete m_pCurrTestPoint;
		m_pCurrTestPoint = NULL;
	}
}

void CCharacterDrawView::UpdateCurrTestPoint(double dX, double dY)
{
	m_bDrawCurrTestPoint = TRUE;

	if (m_pCurrTestPoint == NULL)
	{
		m_pCurrTestPoint = new CXDrawPoint();
		m_pCurrTestPoint->m_crForeColor = RGB(255, 0, 0);
		m_pCurrTestPoint->m_dwDrawStyle = 2; //+o	
	}

	m_pCurrTestPoint->m_fX = dX;
	m_pCurrTestPoint->m_fY = dY;
}

void CCharacterDrawView::FreeCurrTestPoint()
{
	m_bDrawCurrTestPoint = FALSE;
}

//创建绘图对象：整个特性曲线的绘图对象
DWORD CCharacterDrawView::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd, BOOL bViewTestLines, BOOL bCalCharTemp)
{
	m_bViewTestLines = bViewTestLines;
	m_bCalCharTemp  =bCalCharTemp;
	return XCreateElement(pData, pParentWnd);
}

//创建绘图对象：整个特性曲线的绘图对象
DWORD CCharacterDrawView::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->DeleteAll();
		//delete m_pXDrawMngr_Axis;
		//m_pXDrawMngr_Axis = NULL;
	}
	else
	{
	}

	if (pData == NULL)
	{
		return XCREATE_FAIL;
	}

	UINT nClassID = pData->GetClassID();
	
	//创建坐标系和绘图数据
	if  (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		m_pCharacteristic = (CCharacteristic*)pData;
		InitCharDrawView(m_pCharacteristic, pParentWnd);
	}
	else if (nClassID == CHARCLASSID_CCHARACTERISTICS)
	{
		m_pCharacteristics = (CCharacteristics*)pData;
		CCharacteristic *pCharTemp = NULL;
		POS pos = m_pCharacteristics->GetHeadPosition();
		
		while (pos != NULL)
		{
			pCharTemp = (CCharacteristic*)m_pCharacteristics->GetNext(pos);
			ASSERT (pCharTemp->GetClassID() == CHARCLASSID_CCHARACTERISTIC);
			InitCharDrawView(pCharTemp, pParentWnd);
		}
	}

	//2021-9-17  lijunqing  创建缺省的默认坐标系
	if (m_pXDrawMngr_Axis == NULL)
	{
		CreateXDrawMngr(m_strAxis);
	}

	//CalLayout
	CSize szView(0,0);
	szView = CalLayout(szView);

	//调整位置
    CPoint pt(0, 0);
    Layout(pt);

	return XCREATE_SUCC;
}

void CCharacterDrawView::CreateXDrawMngr(CCharacteristic *pCharTemp)
{
	CreateXDrawMngr(pCharTemp->m_strAxis);
}

void CCharacterDrawView::CreateXDrawMngr(const CString &strAxis)
{
	if (m_pXDrawMngr_Axis != NULL)
	{
		return;
	}

	if (strAxis == AXIS_TYPE_ID_CARTES)
	{
		m_pXDrawMngr_Axis = new CXDrawMngrDescartes();
	}
	else if (strAxis == AXIS_TYPE_ID_LOGARITHM)
	{
		m_pXDrawMngr_Axis = new CXDrawMngrLogarithm();
	}

	m_pXDrawMngr_Axis->m_strAxis = strAxis;
}

void CCharacterDrawView::InitCharDrawView(CCharacteristic *pCharTemp, CWnd *pParentWnd)
{
	if (m_bCalCharTemp)
	{
		pCharTemp->CalCharElement(NULL);
	}

	if (m_pXDrawMngr_Axis == NULL)
	{
		//创建坐标系
		CreateXDrawMngr(pCharTemp);
	}

	if (m_pXDrawMngr_Axis->m_strAxis.GetLength() == 0)
	{
		m_pXDrawMngr_Axis->m_strAxis = pCharTemp->m_strAxis;
	}
	else
	{
		if (m_pXDrawMngr_Axis->m_strAxis != pCharTemp->m_strAxis)
		{
#ifndef NOT_USE_XLANGUAGE
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_CoordinatesConflict.GetString()/*_T("特性曲线的坐标系“%s”与与图形管理模块的坐标系“%s”冲突")*/
#else
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("特性曲线的坐标系“%s”与与图形管理模块的坐标系“%s”冲突")
#endif
                , pCharTemp->m_strAxis.GetString(), m_pXDrawMngr_Axis->m_strAxis.GetString());
		}
	}

	m_pXDrawMngr_Axis->m_bXMin = pCharTemp->m_bXMin;
	m_pXDrawMngr_Axis->m_bXMax = pCharTemp->m_bXMax;
	m_pXDrawMngr_Axis->m_bYMin = pCharTemp->m_bYMin;
	m_pXDrawMngr_Axis->m_bYMax = pCharTemp->m_bYMax;

	if (pCharTemp->m_bXMin)
		m_pXDrawMngr_Axis->m_fXMin =pCharTemp->m_fXMin;

	if (pCharTemp->m_bYMin)
		m_pXDrawMngr_Axis->m_fYMin = pCharTemp->m_fYMin;

	if (pCharTemp->m_bXMax)
		m_pXDrawMngr_Axis->m_fXMax = pCharTemp->m_fXMax;

	if (pCharTemp->m_bYMax)
		m_pXDrawMngr_Axis->m_fYMax = pCharTemp->m_fYMax;

	//创建绘图数据
	CXDrawList *pDrawList = pCharTemp->InitCharDrawElement_ForDraw();
	CCharacterArea *pCharArea = pCharTemp->GetCharacterArea();
// 	CXDrawList *pDrawList = (CXDrawList*)pCharArea->DettachDrawListRef();
// 	
// 	if (pDrawList == NULL)
// 	{
// 		pDrawList = new CXDrawList();
// 		pCharArea->SetDrawListRef(pDrawList);
// 	}
// 
// 	m_pXDrawMngr_Axis->AddNewChild(pDrawList);
// 	pCharArea->InitCharDrawElement(pDrawList, FALSE);
	m_pXDrawMngr_Axis->AddNewChild(pDrawList);

	if (m_bViewTestLines)
	{
//		pCharTemp->InitCharDrawElement_ForCalOnly();//20230407 zhouhj
		pCharTemp->CalTestLines(NULL);
		pCharArea->InitCharDrawElementTestLines(pDrawList);
	}

	//xdraw_TestSolvingEquation();
}

void CCharacterDrawView::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->Draw(pDC);
	}

	CXDrawViewBase::Draw(pDC, fZoomRatio, ptOffset);

	DrawActiveElement(pDC, fZoomRatio, ptOffset);

	if (m_bDrawCurrTestPoint && m_pCurrTestPoint != NULL)
	{
		CAxisInterface *pAxisInterface = NULL;
		m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

		if (pAxisInterface != NULL)
		{
			m_pCurrTestPoint->LogicPointToDevicePoint(pAxisInterface);
			m_pCurrTestPoint->Draw(pDC, fZoomRatio, ptOffset);
		}

		m_oXDrawElementsForTemp.LogicPointToDevicePoint(pAxisInterface);//zhouhj 20210129 确保能够实时转换
	}

	//lijq 20200304 -- 用于测试临时性的图形处理功能
	m_oXDrawElementsForTemp.Draw(pDC, fZoomRatio, ptOffset);
}

//2021-9-7  lijunqing
void CCharacterDrawView::GetAxisInterface(CAxisInterface **ppAxisInterface)
{
	m_pXDrawMngr_Axis->GetAxisInterface(ppAxisInterface);
}

CSize CCharacterDrawView::Layout(CPoint &ptTopLeft)
{
	return CSize(m_nWidth, m_nHeight);
}

CSize CCharacterDrawView::CalLayout(CSize &szDraw)
{
	//计算总的Size
    CPoint pt(0, 0);
    szDraw = Layout(pt);

	return szDraw;
}

BOOL CCharacterDrawView::HasDefChar()
{
	if (m_pXDrawMngr_Axis == NULL)
	{
		return FALSE;
	}

	return (m_pXDrawMngr_Axis->GetCount() > 0);
}

BOOL CCharacterDrawView::HasDefChar(CCharacteristic *pCharTemplate)
{
	if (m_pXDrawMngr_Axis == NULL)
	{
		return FALSE;
	}

	if (m_pXDrawMngr_Axis->GetCount() == 0)
	{
		return FALSE;
	}

	return (m_pCharacteristic == pCharTemplate);
}

void CCharacterDrawView::SetBorder(const CRect &rcBorder, CDC *pDC)
{
	if (m_pXDrawMngr_Axis == NULL)
	{
		return;
	}

	ASSERT (m_pXDrawMngr_Axis != NULL);
	m_pXDrawMngr_Axis->SetBorder(rcBorder, pDC, TRUE);

	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	m_oXDrawElementsForTemp.LogicPointToDevicePoint(pAxisInterface);
}

CRect CCharacterDrawView::GetBorder()
{
	if (m_pXDrawMngr_Axis == NULL)
	{
		return CRect(0, 0, 0, 0);
	}

	return m_pXDrawMngr_Axis->GetBorder();
}

BOOL char_view_WriteBitmapFile(CCharacteristic *pCharTemplate, long nWidth, long nHeight, const CString &strFile)
{
#ifndef _PSX_IDE_QT_
#ifndef _PSX_QT_LINUX_
	CRect rcClient(0, 0, nWidth, nHeight);
	CDibDraw oDibDraw;
	oDibDraw.CreateDraw(rcClient.Width(), rcClient.Height());
	CCharacterDrawView *pBmpView = new CCharacterDrawView();
	
	HDC hDC = oDibDraw.GetDrawDC();
	CDC oDC;
	oDC.Attach(hDC);

	pBmpView->XCreateElement(pCharTemplate, NULL, TRUE, TRUE);
	pBmpView->SetBorder(rcClient, &oDC);
	pBmpView->Draw(&oDC, 1, CPoint(0, 0));
	oDC.Detach();

	oDibDraw.WriteToFile(strFile);

	delete pBmpView;
#endif
#endif

	return TRUE;
}



//////////////////////////////////////////////////////////////////////////
//
void CCharacterDrawView::xdraw_TestSolvingEquation()
{
	if (m_oXDrawElementsForTemp.GetCount() > 0)
	{
		return;
	}

	CXDrawCircle *pCircle1 = new CXDrawCircle();
	pCircle1->m_fXRadius = 1.5;
	pCircle1->m_fYRadius = 1.5;
	pCircle1->m_fXCenter = 2;
	pCircle1->m_fYCenter = 2;
	m_oXDrawElementsForTemp.AddNewChild(pCircle1);

	CXDrawCircle *pCircle2 = new CXDrawCircle();
	pCircle2->m_fXRadius = 1.0;
	pCircle2->m_fYRadius = 1.0;
	pCircle2->m_fXCenter = 0.5;
	pCircle2->m_fYCenter = 1.0;
	m_oXDrawElementsForTemp.AddNewChild(pCircle2);

	CXDrawLine *pLine = new CXDrawLine();
	pLine->m_fXb = -1;
	pLine->m_fYb = 1;
	pLine->m_fXe = 4;
	pLine->m_fYe = 3;
	pLine->Init_K_B_by_XY();
	m_oXDrawElementsForTemp.AddNewChild(pLine);

	CXDrawDatas listDatas;
	xdraw_SolveEquation(pCircle1, pCircle2, listDatas);
	xdraw_SolveEquation(pCircle1, pLine, listDatas);
	xdraw_SolveEquation(pCircle2, pLine, listDatas);

	POS pos = listDatas.GetHeadPosition();
	CXDrawData_Point *p = NULL;
	CXDrawPoint *pPoint = NULL;

	while (pos != NULL)
	{
		p = (CXDrawData_Point *)listDatas.GetNext(pos);
		pPoint = new CXDrawPoint();
		p->DataCopy(pPoint);
		pPoint->m_dwDrawStyle = 1;
		pPoint->m_crForeColor = RGB(255, 0, 0);
		m_oXDrawElementsForTemp.AddNewChild(pPoint);
	}
}

long CCharacterDrawView::DevicePointToLogicPoint (long ptx,long pty ,double *x,double *y)
{
	if (m_pXDrawMngr_Axis == NULL)
	{
		return 0;
	}

	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return 0;
	}

	CPoint oPoint;
	oPoint.SetPoint(ptx,pty);
	pAxisInterface->DevicePointToLogicPoint(oPoint,x,y);
	return 1;
}

void CCharacterDrawView::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle)
{
	if (m_pXDrawMngr_Axis == NULL)
	{
		return;
	}

	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}


	pAxisInterface->SetAxisName(strXAxisName,strYAxisName,strAxisTitle);
}

void CCharacterDrawView::ZoomIn(double dCoef)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}

	double dXMin, dXMax, dYMin, dYMax;
	pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	double dXGap = (dXMax - dXMin) / 4;
	double dYGap = (dYMax - dYMin) / 4;

	dXMin += dXGap;
	dXMax -= dXGap;
	dYMin += dYGap;
	dYMax -= dYGap;

	pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
	}
}

void CCharacterDrawView::ZoomOut(double dCoef)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}

	double dXMin, dXMax, dYMin, dYMax;
	pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	double dXGap = (dXMax - dXMin) / 2;
	double dYGap = (dYMax - dYMin) / 2;

	dXMin -= dXGap;
	dXMax += dXGap;
	dYMin -= dYGap;
	dYMax += dYGap;

	pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
	}
}

void CCharacterDrawView::CalAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->GetLogicBorder(dXMin, dYMin, dXMax, dYMax);
	}
}

void CCharacterDrawView::ZoomReset(double dCoef)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}

// 	double dXMin = 1000000, dXMax=-1000000, dYMin=1000000, dYMax=-1000000;
// 	CalAxisMinMax(dXMin, dYMin, dXMax, dYMax);
// 
// 	double dXGap = (dXMax - dXMin) * 0.1;
// 	double dYGap = (dYMax - dYMin) * 0.1;
// 
// 	dXMin -= dXGap;
// 	dXMax += dXGap;
// 	dYMin -= dYGap;
// 	dYMax += dYGap;
// 
//     pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);
// 
// 	if (m_pXDrawMngr_Axis != NULL)
// 	{
// 		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
// 	}

	//cl20231012 CalAxisMinMax()数值有问题，有现成的复归接口函数调用
	m_pXDrawMngr_Axis->AdjustAxis(TRUE);
}

void CCharacterDrawView::MoveLeft(double dCoef)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}

	double dXMin, dXMax, dYMin, dYMax;
	pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	double dXGap = (dXMax - dXMin) * dCoef;
	double dYGap = (dYMax - dYMin) * dCoef;

	dXMin += dXGap;
	dXMax += dXGap;
// 	dYMin -= dYGap;
// 	dYMax += dYGap;

	pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
	}
}

void CCharacterDrawView::MoveRight(double dCoef)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}

	double dXMin, dXMax, dYMin, dYMax;
	pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	double dXGap = (dXMax - dXMin) * dCoef;
	double dYGap = (dYMax - dYMin) * dCoef;

	dXMin -= dXGap;
	dXMax -= dXGap;
	// 	dYMin -= dYGap;
	// 	dYMax += dYGap;

	pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
	}
}

void CCharacterDrawView::MoveUp(double dCoef)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}

	double dXMin, dXMax, dYMin, dYMax;
	pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	double dXGap = (dXMax - dXMin) * dCoef;
	double dYGap = (dYMax - dYMin) * dCoef;

// 	dXMin += dXGap;
// 	dXMax -= dXGap;
	dYMin -= dYGap;
	dYMax -= dYGap;

	pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
	}
}

void CCharacterDrawView::MoveDown(double dCoef)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}

	double dXMin, dXMax, dYMin, dYMax;
	pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	double dXGap = (dXMax - dXMin) * dCoef;
	double dYGap = (dYMax - dYMin) * dCoef;

	// 	dXMin += dXGap;
	// 	dXMax -= dXGap;
	dYMin += dYGap;
	dYMax += dYGap;

	pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
	}
}

//2021-10-28  lijunqing   鼠标移动图形
void CCharacterDrawView::MouseMove_SetBegin(CPoint &ptBegin)
{
	m_ptMouseMoveBegin = ptBegin;
}

void CCharacterDrawView::MouseMove_MoveTo(CPoint &point)
{
	if (m_ptMouseMoveBegin.x - point.x == 0 && m_ptMouseMoveBegin.y - point.y == 0)
	{
		return;
	}

	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}

	double dXMin, dXMax, dYMin, dYMax;
	double xb, yb, xe, ye;
	pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);
	
	pAxisInterface->DevicePointToLogicPoint(m_ptMouseMoveBegin, &xb, &yb);
	pAxisInterface->DevicePointToLogicPoint(point, &xe, &ye);

	double dXMove = xe - xb;
	double dYMove = ye - yb;

	dXMin -= dXMove;
	dXMax -= dXMove;
	dYMin -= dYMove; 
	dYMax -= dYMove;

	pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
	}

	m_ptMouseMoveBegin = point;
}

