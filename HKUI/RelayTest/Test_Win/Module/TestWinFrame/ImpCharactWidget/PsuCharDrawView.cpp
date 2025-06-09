#include "PsuCharDrawView.h"
#include "../../CommonMethod/Complexp.h"
#include "../../../../../Module/API/GloblaDrawFunctions.h"
#include "../../SttXTestMngrBaseApp.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

CPsuCharDrawView::CPsuCharDrawView(void)
{
	//2021-9-15  lijunqing
	//m_pOtherDrawList = NULL;
//	m_pCurrTestPointLine = NULL;
	m_fZoomCoef = 1;

	//初始化坐标系
	m_lfAxisInstruct_Font = InitLogFont ((long)(-11/**m_fCoefficient*/),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));//zhouhj 20210218 m_fCoefficient暂时用1标识
// 	m_strInstruct1Text = _T("Z=19.917Ω");
// 	m_strInstruct2Text = _T("Phi=-175.662°");
	m_strUnitAng = _T("°");//20211027 sf
	m_strUnitMag = _T("Ω");
	m_bIsShowText = true;

	m_strInstructInit_Text = /*_T("+:初始")*/g_sLangTxt_Gradient_PInitial;
	m_strInstructSelect_Text = /*_T("+:选中")*/g_sLangTxt_Gradient_PSelected;
	m_strInstructEnd_Text = /*_T("+:试验结束")*/g_sLangTxt_Gradient_EndTrial;
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

	m_nInstructionShowType = PsuChar_InstructionShowType_MagAng;
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

	COLORREF oColor = RGB(0,255,0);
	InitDrawLineColor(oColor);
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

void CPsuCharDrawView::AxisInstructTypeShow(long nShowType)
{
	 m_nInstructionShowType = nShowType ;
}

void CPsuCharDrawView::DrawAxisInstruction(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	 
	if (pAxisInterface == NULL)
		return;

	CString strInstruct1,strInstruct2;
	//cl 20230926 True坐标显示幅值相位，False根据实际情况
	if (m_nInstructionShowType == PsuChar_InstructionShowType_MagAng)
	{
		Complex oComplex(m_oAxisInstruct_Point.m_fX,m_oAxisInstruct_Point.m_fY);
		strInstruct1.Format(_T("%.3lf"),oComplex.norm());
		strInstruct2.Format(_T("%.3lf"),oComplex.arg());
	}
	else if(m_nInstructionShowType == PsuChar_InstructionShowType_XY)
	{
		strInstruct1.Format(_T("%.3lf"),m_oAxisInstruct_Point.m_fX);
		strInstruct2.Format(_T("%.3lf"),m_oAxisInstruct_Point.m_fY);
	}
	strInstruct1 += m_strUnitMag;
	strInstruct2 += m_strUnitAng;

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
	cp.CreatePen(PS_SOLID/*m_nStyle*/,1/*m_nWidth*/,_CHARACTER_TEST_POINT_COLOR_TestLine/*m_crForeColor*/);

	pOldPen=pDC->SelectObject(&cp);
	pDC->MoveTo(oPointBegin);
	pDC->LineTo(oPointEnd);
	pDC->SelectObject(pOldPen);
	cp.DeleteObject();	
}

void CPsuCharDrawView::CalAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{
	CCharacterDrawView::CalAxisMinMax(dXMin, dYMin, dXMax, dYMax);
//	CAutoSimpleLock oLock(g_theSttXTestMngrBaseApp->m_oCriticSectionCharDrawList);
	g_theSttXTestMngrBaseApp->m_oCharDrawList.GetLogicBorder(dXMin, dYMin, dXMax, dYMax);
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


void CPsuCharDrawView::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CCharacterDrawView::Draw(pDC,fZoomRatio,ptOffset);
	DrawAxisInstruction(pDC,fZoomRatio,ptOffset);
	DrawCurrTestPointLine(pDC,fZoomRatio,ptOffset);

//	CAutoSimpleLock oLock(g_theSttXTestMngrBaseApp->m_oCriticSectionCharDrawList);
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if(pAxisInterface)//cl20230922动作结果点
	{
		if(m_oTestPoints.GetCount())
		{
			POS pos = m_oTestPoints.GetHeadPosition();
			while (pos)
			{
				CXDrawPoint* pt = (CXDrawPoint*)m_oTestPoints.GetNext(pos);
				pt->LogicPointToDevicePoint(pAxisInterface);
				pt->Draw(pDC, fZoomRatio, ptOffset);
			}
		}
	}

	g_theSttXTestMngrBaseApp->m_oCharDrawList.LogicPointToDevicePoint(pAxisInterface);
	g_theSttXTestMngrBaseApp->m_oCharDrawList.Draw(pDC, fZoomRatio, ptOffset);
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


void CPsuCharDrawView::AddTestResultPoint(double dX, double dY,BOOL bAct)
{
	CXDrawPoint* pt = m_oTestPoints.AddPoint(dX, dY);

	if (bAct)
	{
		pt->m_crForeColor = RGB(255, 255, 0);
		pt->m_nPixel = 8;
	} 
	else
	{
		pt->m_crForeColor = RGB(255, 0, 0);
	}

	pt->m_dwDrawStyle = 1; 	
}

void CPsuCharDrawView::ClearTestPoints()
{
	m_oTestPoints.DeleteAll();
}