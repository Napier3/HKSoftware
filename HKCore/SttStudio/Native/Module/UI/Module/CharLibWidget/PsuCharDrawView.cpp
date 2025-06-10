#include "PsuCharDrawView.h"
#include "../../../SttTestBase/SttComplexp.h"
#include "../../Module/API/GloblaDrawFunctions.h"
#include "../../Module/XDrawBase/XDrawMngrDescartes.h"
#include "../../Module/XDrawBase/XDrawMngrLogarithm.h"
#include "../../../XLangResource_Native.h"

CPsuCharDrawView::CPsuCharDrawView(void)
{
	//2021-9-15  lijunqing
	//m_pOtherDrawList = NULL;
//	m_pCurrTestPointLine = NULL;
	m_fZoomCoef = 1;

	//初始化坐标系
	m_lfAxisInstruct_Font = InitLogFont ((long)(-15/**m_fCoefficient*/),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));//zhouhj 20210218 m_fCoefficient暂时用1标识
// 	m_strInstruct1Text = _T("Z=19.917Ω");
// 	m_strInstruct2Text = _T("Phi=-175.662°");
	m_strUnitAng = _T("°");//20211027 sf
	m_strUnitMag = _T("Ω");
	m_bIsShowText = true;
	m_bIsShowAng = false;

	m_strInstructInit_Text = /*_T("+:初始")*/g_sLangTxt_Gradient_PInitial; //lcq
	m_strInstructSelect_Text = /*_T("+:选中")*/g_sLangTxt_Gradient_PSelected; //lcq
	m_strInstructEnd_Text = /*_T("+:试验结束")*/g_sLangTxt_Gradient_EndTrial; //lcq
	m_crAxisInstructPoint_FontColor = RGB( 0, 255, 0);
//	m_crAxisInstructX_FontColor = RGB( 0, 255, 0);
	m_crAxisInstructInit_FontColor = RGB( 255, 0, 0);
	m_crAxisInstructSelect_FontColor = RGB( 0, 255, 255);
	m_crAxisInstructEnd_FontColor = RGB( 255, 0, 255);
	m_dInstructLeftGap = 20;
	m_dInstructTopGap = 5;
	m_dInstructSpaceGap = 3;

	m_oAxisInstruct_Point.m_fX = 0;
	m_oAxisInstruct_Point.m_fY = 0;

	m_oLeftButtonLine.SetBeginPoint(0, 0);
	m_oLeftButtonLine.SetEndPoint(0, 0);
}

CPsuCharDrawView::~CPsuCharDrawView(void)
{
	m_pCurrTestPoint = NULL;
}

void CPsuCharDrawView::InitCharDrawView(CCharacteristic *pCharTemp, CWnd *pParentWnd)
{
	CCharacterDrawView::InitCharDrawView(pCharTemp,pParentWnd);
	//2021-9-15  lijunqing
	//m_pOtherDrawList = new CXDrawList;
	//m_pXDrawMngr_Axis->AddNewChild(m_pOtherDrawList);

	COLORREF oLinesColor = RGB(0,255,0);
	COLORREF oTestLineColor_sys = RGB(0,255,0);
	COLORREF oTestLineColor_User = RGB(255,0,255);
	InitDrawLineColor(oLinesColor,oTestLineColor_sys,oTestLineColor_User);
}

// void CPsuCharDrawView::SetTestPointLine(const double &dValueR,const double &dValueX)
// {
// // 	if (m_pCurrTestPointLine == NULL)
// // 	{
// // 		m_pCurrTestPointLine = new CXDrawLine();
// // 		m_pCurrTestPointLine->m_crForeColor = _CHARACTER_TEST_POINT_COLOR_TestLine;
// // 		m_oXDrawElementsForTemp.AddNewChild(m_pCurrTestPointLine);
// // 		m_pCurrTestPointLine->m_pXDrawDataRef = NULL;
// // 	}
// // 
// // 	m_pCurrTestPointLine->m_fXb = -dValueR*100;
// // 	m_pCurrTestPointLine->m_fYb = -dValueX*100;
// // 	m_pCurrTestPointLine->m_fXe = dValueR*100;
// // 	m_pCurrTestPointLine->m_fYe = dValueX*100;
// }

CXDrawPoint* CPsuCharDrawView::CreateNewTestPoint(const double &dR,const double &dX)
{
	//2021-9-15  lijunqing
// 	ASSERT(m_pOtherDrawList);
// 	if (m_pOtherDrawList == NULL)
// 	{
// 		return NULL;
// // 		m_pOtherDrawList = new CXDrawList;
// // 		m_pXDrawMngr_Axis->AddNewChild(m_pOtherDrawList);
// 	}

// 	CXDrawPoint *pXPoint = new CXDrawPoint();
// 	pXPoint->m_fX = dR;
// 	pXPoint->m_fY = dX;
// 	pXPoint->m_dwDrawStyle = 0;
// 	pXPoint->m_crForeColor = _CHARACTER_TEST_POINT_COLOR_Initial;
// 	m_pOtherDrawList->AddNewChild(pXPoint);
// 	pXPoint->m_pXDrawDataRef = NULL;
// 	return pXPoint;

	//2021-9-15  lijunqing
	return NULL;
}

void CPsuCharDrawView::DeleteTestPoint(CXDrawPoint *pTestPoint)
{
	//2021-9-15  lijunqing
// 	if (m_pOtherDrawList != NULL)
// 	{
// 		m_pOtherDrawList->Delete(pTestPoint);
// 	}
}

void CPsuCharDrawView::InitDrawLineColor(const COLORREF &oColor)
{
 	ASSERT(m_pXDrawMngr_Axis);
 	m_pXDrawMngr_Axis->InitDrawLineColor(oColor);
}

void CPsuCharDrawView::InitDrawLineColor(const COLORREF &oLinesColor,const COLORREF &oTestLineColor_sys,const COLORREF &oTestLineColor_User)
{
 	ASSERT(m_pXDrawMngr_Axis);

	POS pos_XDrawList = m_pXDrawMngr_Axis->GetHeadPosition();
	CXDrawList *pDrawList = NULL;
	CCharElementTestLine *pCharElementTestLine = NULL;

	while (pos_XDrawList != NULL)
	{
		pDrawList = (CXDrawList *)m_pXDrawMngr_Axis->GetNext(pos_XDrawList);

		POS pos = pDrawList->GetHeadPosition();
		CXDrawBase *pXDrawBase = NULL;

		while (pos != NULL)
		{
			pXDrawBase = (CXDrawBase*)pDrawList->GetNext(pos);

			//如果不初始化测试线,判断对应线条是否为测试线
			if ((pXDrawBase->m_pXDrawDataRef != NULL))
			{
				if (pXDrawBase->m_pXDrawDataRef->GetClassID() == CHARCLASSID_CCHARELEMENTTESTLINE)
				{
					pCharElementTestLine = (CCharElementTestLine*)pXDrawBase->m_pXDrawDataRef;

					if (pCharElementTestLine->m_strType == _T("user"))
					{
						pXDrawBase->m_crForeColor = oTestLineColor_User;
					} 
					else
					{
						pXDrawBase->m_crForeColor = oTestLineColor_sys;
					}

					continue;
				}
			}

			pXDrawBase->m_crForeColor = oLinesColor;
		}
	}
}

void CPsuCharDrawView::UI_OnMouseMove(UINT nFlags, CPoint point)
{
	SetAxisInstruct_Point(point);
}

void CPsuCharDrawView::UI_OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_pCurrTestPoint != NULL)
	{
		DevicePointToLogicPoint(point.x,point.y,&m_pCurrTestPoint->m_fX,&m_pCurrTestPoint->m_fY);	
//		SetTestPointLine(m_pCurrTestPoint->m_fX,m_pCurrTestPoint->m_fY);
	}
}

void CPsuCharDrawView::SetAxisInstruct_Point(const CPoint &point)
{
	ASSERT(m_pXDrawMngr_Axis);
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface != NULL)
	{
		pAxisInterface->DevicePointToLogicPoint(point,&m_oAxisInstruct_Point.m_fX,&m_oAxisInstruct_Point.m_fY);
	}
}

void CPsuCharDrawView::GetAxisInterface(CAxisInterface **ppAxisInterface)
{
	ASSERT(m_pXDrawMngr_Axis);
	m_pXDrawMngr_Axis->GetAxisInterface(ppAxisInterface);
}

// void CPsuCharDrawView::SetAxisInstruct(const CString &strAxisInstruct1, const CString &strAxisInstruct2)
// {
// 	m_strInstruct1Text = strAxisInstruct1;
// 	m_strInstruct2Text = strAxisInstruct2;
// }

void CPsuCharDrawView::UI_ZoomIn()
{
// 	m_pXDrawMngr_Axis->MouseMoveZoom();
// 	CAxisInterface *pAxisInterface = NULL;
// 	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
// 
// 	if (pAxisInterface != NULL)
// 	{
// 		m_fZoomCoef -= 0.1;
// 		pAxisInterface->ZoomIn(m_fZoomCoef);
// 	}
}

void CPsuCharDrawView::UI_ZoomOut()
{
// 	CAxisInterface *pAxisInterface = NULL;
// 	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
// 
// 	if (pAxisInterface != NULL)
// 	{
// 		m_fZoomCoef += 0.1;
// 		pAxisInterface->ZoomIn(m_fZoomCoef);
// 	}
}

void CPsuCharDrawView::SetCurTestPoint(CXDrawPoint *pCurrTestPoint,BOOL bUpdateInstruct)
{
	m_pCurrTestPoint = pCurrTestPoint;

	if (m_pCurrTestPoint == NULL)
	{
		return;
	}

	if (bUpdateInstruct)
	{
		m_oAxisInstruct_Point.m_fX = m_pCurrTestPoint->m_fX;
		m_oAxisInstruct_Point.m_fY = m_pCurrTestPoint->m_fY;
	}
}

void CPsuCharDrawView::DrawAxisInstruction(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	 
	if (pAxisInterface == NULL)
		return;

	Complex oComplex(m_oAxisInstruct_Point.m_fX,m_oAxisInstruct_Point.m_fY);
	CString strInstruct1,strInstruct2;

	if(m_strAxis == AXIS_TYPE_ID_POLAR)
	{
		strInstruct1.Format(_T("%.3lf"),oComplex.Mag);
		strInstruct1 += m_strUnitMag;
		strInstruct2.Format(_T("%.3lf"),oComplex.Ang);
		strInstruct2 += m_strUnitAng;
	}
	else if(m_strAxis == AXIS_TYPE_ID_LOGARITHM)
	{
		strInstruct1.Format(_T("%.3lf"),oComplex.real);
		strInstruct1 += m_strUnitMag;
		strInstruct2.Format(_T("%.3lf"),oComplex.imag);
		strInstruct2 += m_strUnitAng;
	}
	else
	{
		if(m_bIsShowAng)
		{
			strInstruct1.Format(_T("%.3lf"),oComplex.norm());
			strInstruct1 += m_strUnitMag;
			strInstruct2.Format(_T("%.3lf"),oComplex.arg());
			strInstruct2 += m_strUnitAng;	
		}
		else
		{
			strInstruct1.Format(_T("%.3lf"),oComplex.real);
			strInstruct1 += m_strUnitMag;
			strInstruct2.Format(_T("%.3lf"),oComplex.imag);
			strInstruct2 += m_strUnitAng;
		}
	}

	CRect rect,rectWorkArea;
	rectWorkArea = pAxisInterface->GetWorkArea();
	LOGFONT lf = m_lfAxisInstruct_Font;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lfWidth = GetCharWidthByLogfont2(pDC,lf);

	rect.left = rectWorkArea.left + m_dInstructLeftGap;
	rect.top = rectWorkArea.top + m_dInstructTopGap;
	rect.right = rect.left + lfWidth * strInstruct1.GetLength()*2;
	rect.bottom = rect.top + abs(lf.lfHeight);
	rect.OffsetRect(ptOffset);

	CmDrawTextRect(pDC,strInstruct1,m_crAxisInstructPoint_FontColor,
		&rect,RGB(0,0,0),lf,
		TRANSPARENT,DT_VCENTER|DT_LEFT,0);

	rect.top = rectWorkArea.top + m_dInstructTopGap + abs(lf.lfHeight) + m_dInstructSpaceGap;
	rect.right = rect.left + lfWidth * strInstruct2.GetLength()*2;
	rect.bottom = rect.top + abs(lf.lfHeight);
	rect.OffsetRect(ptOffset);

	CmDrawTextRect(pDC,strInstruct2,m_crAxisInstructPoint_FontColor,
		&rect,RGB(0,0,0),lf,
		TRANSPARENT,DT_VCENTER|DT_LEFT,0);

	if (m_bIsShowText)
	{
		rect.top = rectWorkArea.top + m_dInstructTopGap + 2*abs(lf.lfHeight) + 2*m_dInstructSpaceGap;
		rect.right = rect.left + lfWidth * m_strInstructInit_Text.GetLength()*2;
		rect.bottom = rect.top + abs(lf.lfHeight);
		rect.OffsetRect(ptOffset);

		CmDrawTextRect(pDC,m_strInstructInit_Text,m_crAxisInstructInit_FontColor,
			&rect,RGB(0,0,0),lf,
			TRANSPARENT,DT_VCENTER|DT_LEFT,0);

		rect.top = rectWorkArea.top + m_dInstructTopGap + 3*abs(lf.lfHeight) + 3*m_dInstructSpaceGap;
		rect.right = rect.left + lfWidth * m_strInstructSelect_Text.GetLength()*2;
		rect.bottom = rect.top + abs(lf.lfHeight);
		rect.OffsetRect(ptOffset);

		CmDrawTextRect(pDC,m_strInstructSelect_Text,m_crAxisInstructSelect_FontColor,
			&rect,RGB(0,0,0),lf,
			TRANSPARENT,DT_VCENTER|DT_LEFT,0);

		rect.top = rectWorkArea.top + m_dInstructTopGap + 4*abs(lf.lfHeight) + 4*m_dInstructSpaceGap;
		rect.right = rect.left + lfWidth * m_strInstructEnd_Text.GetLength()*2;
		rect.bottom = rect.top + abs(lf.lfHeight);
		rect.OffsetRect(ptOffset);

		CmDrawTextRect(pDC,m_strInstructEnd_Text,m_crAxisInstructEnd_FontColor,
			&rect,RGB(0,0,0),lf,
			TRANSPARENT,DT_VCENTER|DT_LEFT,0);
	}
	
}

void CPsuCharDrawView::DrawCurrTestPointLine(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if ((pAxisInterface == NULL)||(m_pCurrTestPoint == NULL))
	{
		return;
	}

	CPoint oPointBegin,oPointEnd;
	pAxisInterface->LogicPointToDevicePoint(-m_pCurrTestPoint->m_fX*100, -m_pCurrTestPoint->m_fY*100, &oPointBegin);
	pAxisInterface->LogicPointToDevicePoint(m_pCurrTestPoint->m_fX*100, m_pCurrTestPoint->m_fY*100, &oPointEnd);

	CPen cp,*pOldPen;
	cp.CreatePen(PS_SOLID/*m_nStyle*/,1/*m_nWidth*/, RGB(0, 255, 0));

	pOldPen=pDC->SelectObject(&cp);
	pDC->MoveTo(oPointBegin);
	pDC->LineTo(oPointEnd);
	pDC->SelectObject(pOldPen);
	cp.DeleteObject();	
}

void CPsuCharDrawView::CalAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
	CCharacterDrawView::CalAxisMinMax(dXMin, dYMin, dXMax, dYMax);
	m_oCharDrawList.GetLogicBorder(dXMin, dYMin, dXMax, dYMax);
	//没有测试线的时候，会出问题，临时处理 sf 20211028 
	if(dYMax == -1000000)
	{
		dYMax = 8;
		dYMin = -8;
	}
	if (dXMax == -1000000)
	{
		dXMax = 8;
		dXMin = -8;
	}
}

void CPsuCharDrawView::AddTestResultPoint(double dX, double dY,BOOL bAct)
{
// 	CAxisInterface *pAxisInterface = NULL;
// 	double dXMin = 0, dXMax = 0, dYMin = 0, dYMax = 0;
// 	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
// 
// 	if(pAxisInterface)
// 	{
// 		pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);
// 	}
// 
// 	if (dY<dYMin)
// 	{
// 		dY = dYMin; 
// 	}

	//yzj 2023.10.20 相同位置的点不应该重复添加
	for (int i = 0; i < m_oTestPoints.GetCount(); i++)
	{
		CXDrawPoint* pTemp = (CXDrawPoint*)m_oTestPoints.GetAt(i);
		if(pTemp->m_fX == dX && pTemp->m_fY == dY)
		{
			return;
		}
	}

	CXDrawPoint* pt = m_oTestPoints.AddPoint(dX, dY);

	if (bAct)
	{
		pt->m_crForeColor = RGB(255, 255, 0);
	} 
	else
	{
		pt->m_crForeColor = RGB(255, 0, 0);
	}

	pt->m_dwDrawStyle = 1; //x	
}

void CPsuCharDrawView::ClearSearchPoints(long nPtIndex)
{
	if(nPtIndex == -1)
	{
		m_oTestPoints.DeleteAll();
	}
	else
	{
		if(m_oTestPoints.GetCount() > nPtIndex)
		{
			m_oTestPoints.DeleteAt(nPtIndex);
		}
	}
}

long CPsuCharDrawView::GetSearchPointsCount()
{
	return m_oTestPoints.GetCount();
}

void CPsuCharDrawView::CalLinesPoints(long nIndex, CXDrawDatas* pDatas, CString strType)
{
	CXDrawList* pList = (CXDrawList*)m_pXDrawMngr_Axis->GetAt(nIndex);
	CXDrawBase* pObj = NULL;
	UINT nClassID = 0;
	CCharElementLined* pBase = NULL;
	CXDrawPolyline *pXDrawPolyline = NULL;
	CCharElementInverse *pCharElementInverse = NULL;
	CXDrawData_Point *pXDrawData_Point = NULL;

	POS pos = pList->GetHeadPosition();
	while (pos)
	{
		pObj = (CXDrawBase*)pList->GetNext(pos);
		nClassID = pObj->GetClassID();

		if((nClassID == DWCLASSID_CXDRAWLINE)&&(pObj->m_pXDrawDataRef != NULL))
		{
			if(pObj->m_pXDrawDataRef->GetClassID() == CHARCLASSID_CCHARELEMENTTESTLINE)
			{
				//测试线与特性曲线的类名相似,但父类完全不同,同时也不需要判断相交
				continue;
			}

			m_oLeftButtonLine.Init_K_B_by_XY();
			pBase = (CCharElementLined*)pObj->m_pXDrawDataRef;
			pBase->Init_K_B_by_XY();
			if(strType == CHAR_TESTLINE_MODE_ID_VERT)
			{
				if(pBase->m_fXb > m_oLeftButtonLine.m_fXb || pBase->m_fXe < m_oLeftButtonLine.m_fXe)
				{
					//排除不在相交区域内的线段
					continue;
				}			
			}
			else
			{
				if(pBase->m_fYb > m_oLeftButtonLine.m_fYb || pBase->m_fYe < m_oLeftButtonLine.m_fYe)
				{
					//排除不在相交区域内的线段
					continue;
				}	
			}
			xdraw_SolveEquation(pBase, &m_oLeftButtonLine, *pDatas);
		}
		else if(nClassID == DWCLASSID_CXDRAWARC)
		{
		}
		else if (nClassID == DWCLASSID_CXDRAWCIRCLE)
		{
		}
		else if (nClassID == DWCLASSID_CXDRAWPOLYLINE)//反时限特性曲线
		{
			m_oLeftButtonLine.Init_K_B_by_XY();
			pXDrawPolyline = (CXDrawPolyline*)pObj;

			if (pXDrawPolyline->m_pXDrawDataRef == NULL)
			{
				continue;
			}

			pCharElementInverse = (CCharElementInverse*)pXDrawPolyline->m_pXDrawDataRef;
			double dYValue = pCharElementInverse->CalInverse(m_oAxisInstruct_Point.m_fX);

			if (dYValue>0)//反时限对应Y轴为时间,必定为正值
			{
				pXDrawData_Point = new CXDrawData_Point(m_oAxisInstruct_Point.m_fX, dYValue);
				pDatas->AddTail(pXDrawData_Point);
			}
		}	
	}
}

void CPsuCharDrawView::CalVertHorzLine(long nIndex, CString strType)
{
	CAxisInterface *pAxisInterface = NULL;
	double dXMin = 0, dXMax = 0, dYMin = 0, dYMax = 0;
	BOOL bLogarithm = FALSE;

	if (m_pXDrawMngr_Axis->m_strAxis == AXIS_TYPE_ID_LOGARITHM)
	{
		bLogarithm = TRUE;
	}

	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if(pAxisInterface)
	{
		pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

		if (bLogarithm)
		{
			dYMin = pow(10,dYMin);
			dYMax = pow(10,dYMax);
			dXMin = pow(10,dXMin);
			dXMax = pow(10,dXMax);
		}
	}
	if(strType == CHAR_TESTLINE_MODE_ID_VERT)
	{
		m_oLeftButtonLine.SetBeginPoint(m_oAxisInstruct_Point.m_fX, dYMin);
		m_oLeftButtonLine.SetEndPoint(m_oAxisInstruct_Point.m_fX, dYMax);
	}
	else
	{
		m_oLeftButtonLine.SetBeginPoint(dXMin, m_oAxisInstruct_Point.m_fY);
		m_oLeftButtonLine.SetEndPoint(dXMax, m_oAxisInstruct_Point.m_fY);
	}
	
	m_oLeftButtonLine.SetColor(m_crAxisInstructInit_FontColor);
	m_oLeftButtonLine.LogicPointToDevicePoint(pAxisInterface);
	m_oLeftButtonLine.DeleteChildren();

	CXDrawDatas oDatas;
	CalLinesPoints(nIndex, &oDatas, strType);
	POS pos = oDatas.GetHeadPosition();
	while (pos)
	{
		CXDrawData_Point* ptEqua = (CXDrawData_Point*)oDatas.GetNext(pos);
		CXDrawPoint* pt = new CXDrawPoint();
		pt->m_fX = ptEqua->m_fX;
		pt->m_fY = ptEqua->m_fY;
		m_oLeftButtonLine.AddNewChild(pt);
	}
}

void CPsuCharDrawView::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CCharacterDrawView::Draw(pDC,fZoomRatio,ptOffset);

	DrawAxisInstruction(pDC,fZoomRatio,ptOffset);

	BOOL bLogarithm = FALSE;

	if (m_pXDrawMngr_Axis->m_strAxis == AXIS_TYPE_ID_LOGARITHM)
	{
		bLogarithm = TRUE;
	}

	//DrawCurrTestPointLine(pDC,fZoomRatio,ptOffset);

	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	if(pAxisInterface)
	{
		if(m_oTestPoints.GetCount())
		{
			//画过程中点
			POS pos = m_oTestPoints.GetHeadPosition();
			while (pos)
			{
				CXDrawPoint* pt = (CXDrawPoint*)m_oTestPoints.GetNext(pos);
				pt->LogicPointToDevicePoint(pAxisInterface);
				pt->Draw(pDC, fZoomRatio, ptOffset);
			}
		}
	}

	//画鼠标竖线以及相交点
	m_oLeftButtonLine.Draw(pDC, fZoomRatio, ptOffset);
	CRect rc;
	POS posPt = m_oLeftButtonLine.GetHeadPosition();

	while(posPt)
	{
		CPoint ptPoint;
		CXDrawPoint* pt = (CXDrawPoint*)m_oLeftButtonLine.GetNext(posPt);
		pAxisInterface->LogicPointToDevicePoint(pt->m_fX, pt->m_fY, &ptPoint);
		CString strPt;
		strPt.Format("(%.3f, %.3f)", pt->m_fX, pt->m_fY);

		if (bLogarithm)
		{
			rc = CRect(ptPoint.x, ptPoint.y  - 36, ptPoint.x + strPt.GetLength() * 16, ptPoint.y);
		} 
		else
		{
			rc = CRect(ptPoint.x, ptPoint.y, ptPoint.x + strPt.GetLength() * 16, ptPoint.y + 36);
		}
		
		CmDrawTextRect(pDC, strPt, m_crAxisInstructInit_FontColor,
			&rc, RGB(0,255,0), m_lfAxisInstruct_Font,
			TRANSPARENT,DT_VCENTER|DT_LEFT,0);
	}

	m_oCharDrawList.LogicPointToDevicePoint(pAxisInterface);
	m_oCharDrawList.Draw(pDC, fZoomRatio, ptOffset);
}

//设置显示的单位 非阻抗类调用 20211027 sf
void CPsuCharDrawView::SetXYUnitShow(CString strUnitMag,CString strUnitAng)
{
	m_strUnitMag = strUnitMag;
	m_strUnitAng = strUnitAng;
}

//设置是否需要显示测试点标识 20211027 sf
void CPsuCharDrawView::SetIsShowText( bool bIsShowText )
{
	m_bIsShowText = bIsShowText;
}

void CPsuCharDrawView::SetIsShowAng(bool bIsShowAng)
{
	m_bIsShowAng = bIsShowAng;
}

void CPsuCharDrawView::UpdateAxisType(const CString& strAxis,BOOL bLockXY)
{
	if(m_pXDrawMngr_Axis)
	{
		delete m_pXDrawMngr_Axis;
		m_pXDrawMngr_Axis = NULL;
	}

	CreateXDrawMngr(strAxis);
	if(m_pXDrawMngr_Axis->GetClassID() == DWCLASSID_CXDRAWMNGRDESCARTES)
	{
		((CXDrawMngrDescartes*)m_pXDrawMngr_Axis)->SetAxisXYUnitLock(bLockXY);
	}
	else if (m_pXDrawMngr_Axis->GetClassID() == DWCLASSID_CXDRAWMNGRLOGARITHM)
	{
		((CXDrawMngrLogarithm*)m_pXDrawMngr_Axis)->SetAxisXYUnitLock(bLockXY);
	}
}

CXDrawLine* CPsuCharDrawView::GetLeftButtonLine()
{
	return &m_oLeftButtonLine;
}
