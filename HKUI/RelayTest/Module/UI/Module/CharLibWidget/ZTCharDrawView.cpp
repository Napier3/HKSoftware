#include "ZTCharDrawView.h"
#include "../../../SttTestBase/SttComplexp.h"
#include "../../../../../Module/API/GloblaDrawFunctions.h"
#include "../../../../../Module/XDrawBase/XDrawMngrDescartes.h"
#include "../../../../../Module/XDrawBase/XDrawMngrLogarithm.h"
#include "../../../XLangResource_Native.h"

CZTCharDrawView::CZTCharDrawView(void)
{
	//初始化坐标系
	m_lfAxisInstruct_Font = InitLogFont ((long)(-15),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));
    m_strUnitAng = "°";
    m_strUnitMag = "Ω";
	m_bIsShowAng = false;
	m_strAngle = "";
	m_strFaultype = "";

	m_crAxisInstructPoint_FontColor = RGB( 0, 0, 0);
	m_crAxisInstructInit_PointColor = RGB( 255, 0, 255);
	m_crAxisInstructInit_LineColor = RGB( 0, 0, 255);
	m_dInstructLeftGap = 20;
	m_dInstructTopGap = 5;
	m_dInstructSpaceGap = 3;

	m_oAxisInstruct_Point.m_fX = 0;
	m_oAxisInstruct_Point.m_fY = 0;

	m_ImpSearch = false;//显示竖线正负误差
	m_pCurrTestPoint = new CXDrawPoint();
	m_pCurrTestPoint->m_crForeColor = m_crAxisInstructInit_PointColor;

    m_dMax_XAxis = 0;
    m_dMax_YAxis = 0;
    m_dMin_XAxis = 0;
    m_dMin_YAxis = 0;

    m_dReSetMax_X = -1;
    m_dReSetMax_Y = -1;
    m_dReSetMin_X = -1;
    m_dReSetMin_Y = -1;

	m_oMouseClick.m_strID.setNum(65535);

	if (m_pXDrawMngr_Axis == NULL)
	{
		CreateXDrawMngr(m_strAxis);
	}

	InitDrawLineColor(m_crAxisInstructInit_LineColor);
}

CZTCharDrawView::~CZTCharDrawView(void)
{
	if (m_pCurrTestPoint != NULL)
	{
		delete m_pCurrTestPoint;
		m_pCurrTestPoint = NULL;
	}
	m_oCharDrawList.DeleteAll();
	m_oCharPlusDrawList.DeleteAll();
	m_oCharMinusDrawList.DeleteAll();
	m_oTestPoints.DeleteAll();
}
void  CZTCharDrawView::ClearTestLines()
{
	m_oCharDrawList.DeleteAll();
	m_oCharPlusDrawList.DeleteAll();
	m_oCharMinusDrawList.DeleteAll();

}
CXDrawLine* CZTCharDrawView::AddOneTestLine(const CString &strIDPath,double dXMin,double dYMIn,double dXMax,double dYMax,double dPlus,double dMinus)
{//根据起始坐标、终止坐标、正负误差创建测试线段
	if (dYMIn < 0)
	{
		dYMIn = 0;
	}
	CXDrawLine *pLine = new CXDrawLine();
	pLine->SetBeginPoint(dXMin,dYMIn);
	pLine->SetEndPoint(dXMax,dYMax);
	pLine->m_strID = strIDPath;
	m_oCharDrawList.AddNewChild(pLine);
	
	if(m_ImpSearch&&dYMIn == dYMax)
	{//横线显示误差范围
	//20241010 luozibing 只存在一个相同strIDPath的节点
		CXDrawLine *pLinePlus = (CXDrawLine *)m_oCharPlusDrawList.FindByID(strIDPath);
		if (pLinePlus == NULL)
		{
			pLinePlus = new CXDrawLine();
			pLinePlus->m_nStyle = PS_DOT;
			pLinePlus->m_strID = strIDPath;
			m_oCharPlusDrawList.AddNewChild(pLinePlus);
		}
		pLinePlus->SetBeginPoint(dXMin,dYMIn+dPlus);
		pLinePlus->SetEndPoint(dXMax,dYMax+dPlus);
		

		double dYBeginMinus,dYEndMinus;
		dYBeginMinus = dYMIn-dMinus;
		dYEndMinus= dYMax-dMinus;
		if (dYBeginMinus<0);
		{
			dYBeginMinus = 0;
		}
		if (dYEndMinus <0)
		{
			dYEndMinus = 0;
		}
		CXDrawLine *pLineMinus = (CXDrawLine *)m_oCharMinusDrawList.FindByID(strIDPath);
		if (pLineMinus == NULL)
		{
			pLineMinus = new CXDrawLine();
			pLineMinus->m_nStyle = PS_DOT;
			pLineMinus->m_strID = strIDPath;
			m_oCharMinusDrawList.AddNewChild(pLineMinus);
		}
		pLineMinus->SetBeginPoint(dXMin,dYBeginMinus);
		pLineMinus->SetEndPoint(dXMax,dYEndMinus);
		
	}
	else if (!m_ImpSearch&& dXMin == dXMax)
	{//竖线显示误差范围
		CXDrawLine *pLinePlus = (CXDrawLine *)m_oCharPlusDrawList.FindByID(strIDPath);
		if (pLinePlus == NULL)
		{
			pLinePlus = new CXDrawLine();
			pLinePlus->m_nStyle = PS_DOT;
			pLinePlus->m_strID = strIDPath;
			m_oCharPlusDrawList.AddNewChild(pLinePlus);
		}
		pLinePlus->SetBeginPoint(dXMin+dPlus,dYMIn);
		pLinePlus->SetEndPoint(dXMax+dPlus,dYMax);

		CXDrawLine *pLineMinus = (CXDrawLine *)m_oCharMinusDrawList.FindByID(strIDPath);
		if (pLineMinus == NULL)
		{
			pLineMinus = new CXDrawLine();
			pLineMinus->m_nStyle = PS_DOT;
			pLineMinus->m_strID = strIDPath;
			m_oCharMinusDrawList.AddNewChild(pLineMinus);
		}
		pLineMinus->SetBeginPoint(dXMin-dMinus,dYMIn);
		pLineMinus->SetEndPoint(dXMax-dMinus,dYMax);
	}
	return pLine;
}
void CZTCharDrawView::InitDrawLineColor(const COLORREF &oColor)
{
 	ASSERT(m_pXDrawMngr_Axis);
 	m_pXDrawMngr_Axis->InitDrawLineColor(oColor);
}
void CZTCharDrawView::UI_OnMouseMove(UINT nFlags, CPoint point)
{
	SetAxisInstruct_Point(point);
}

void CZTCharDrawView::SetAxisInstruct_Point(const CPoint &point)
{
	ASSERT(m_pXDrawMngr_Axis);
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface != NULL)
	{
		pAxisInterface->DevicePointToLogicPoint(point,&m_oAxisInstruct_Point.m_fX,&m_oAxisInstruct_Point.m_fY);
	}
}

void CZTCharDrawView::GetAxisInterface(CAxisInterface **ppAxisInterface)
{
	ASSERT(m_pXDrawMngr_Axis);
	if(m_pXDrawMngr_Axis == NULL)
		return;
	m_pXDrawMngr_Axis->GetAxisInterface(ppAxisInterface);
}
void CZTCharDrawView::SetCurTestPoint(double dX,double dY,BOOL bWithin)
{
	if (m_pCurrTestPoint != NULL)
	{
		m_pCurrTestPoint->m_fY = dY;
		m_pCurrTestPoint->m_fX = dX;
	}
	if (bWithin)
	{
		m_pCurrTestPoint->m_dwDrawStyle = 1 ;//x
	}
	else
	{
		m_pCurrTestPoint->m_dwDrawStyle = 10;//8 o
	}
}

void CZTCharDrawView::DrawAxisInstruction(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	 
	if (pAxisInterface == NULL)
		return;

	Complex oComplex(m_oAxisInstruct_Point.m_fX,m_oAxisInstruct_Point.m_fY);
	CString strInstruct1,strInstruct2,strInstruct3;

	strInstruct1.Format(_T("%.3lf"),oComplex.real);
    strInstruct1 += m_strUnitMag.toLocal8Bit();//"Ω";
	strInstruct2.Format(_T("%.2lf"), m_strAngle.toDouble());
    strInstruct2 += m_strUnitAng.toLocal8Bit();//"°";
    strInstruct3 = g_sLangTxt_State_FaultType;
    strInstruct3 += m_strFaultype;

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

	rect.top = rectWorkArea.top + m_dInstructTopGap + 2*abs(lf.lfHeight) + 2*m_dInstructSpaceGap;
	rect.right = rect.left + lfWidth * strInstruct3.GetLength()*4;
	rect.bottom = rect.top + abs(lf.lfHeight);
	rect.OffsetRect(ptOffset);

	CmDrawTextRect(pDC,strInstruct3,m_crAxisInstructPoint_FontColor,
		&rect,RGB(0,0,0),lf,
		TRANSPARENT,DT_VCENTER|DT_LEFT,0);
}

void CZTCharDrawView::ClearSearchPoints(long nPtIndex)
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
void CZTCharDrawView::DrawActiveElement(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	CPoint ptPointLeftTop,ptlowerRight,ptlowerLeft;
	double dXMin, dXMax, dYMin, dYMax;
	pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);
	pAxisInterface->LogicPointToDevicePoint(dXMin,dYMax, &ptPointLeftTop);
	pAxisInterface->LogicPointToDevicePoint(dXMin,dYMin, &ptlowerRight);
	pAxisInterface->LogicPointToDevicePoint(dXMax,dYMin, &ptlowerLeft);

	pDC->MoveTo(ptlowerRight);
	pDC->LineTo(ptlowerLeft);

	CXDrawLine *pLine = (CXDrawLine*)m_oCharDrawList.FindByID(ZTVIEW_MINIMUM_VERTICAL_LINE);
	if(pLine != NULL)
	{
		pLine->m_fYe = dYMax;
	}
	pLine = (CXDrawLine*)m_oCharPlusDrawList.FindByID(ZTVIEW_MINIMUM_VERTICAL_LINE);
	if(pLine != NULL)
	{
		pLine->m_fYe = dYMax;
	}
	pLine = (CXDrawLine*)m_oCharMinusDrawList.FindByID(ZTVIEW_MINIMUM_VERTICAL_LINE);
	if(pLine != NULL)
	{
		pLine->m_fYe = dYMax;
	}

	pLine = (CXDrawLine*)m_oCharDrawList.FindByID(ZTVIEW_MAXIMUM_VERTICAL_LINE);
	if(pLine != NULL)
	{
		pLine->m_fYe = dYMax;
	}
	pLine = (CXDrawLine*)m_oCharPlusDrawList.FindByID(ZTVIEW_MAXIMUM_VERTICAL_LINE);
	if(pLine != NULL)
	{
		pLine->m_fYe = dYMax;
	}
	pLine = (CXDrawLine*)m_oCharMinusDrawList.FindByID(ZTVIEW_MAXIMUM_VERTICAL_LINE);
	if(pLine != NULL)
	{
		pLine->m_fYe = dYMax;
	}
	
	POS pos = m_oCharMinusDrawList.GetHeadPosition();
	while(pos != NULL)
	{
		CXDrawLine *pMinus = (CXDrawLine *)m_oCharMinusDrawList.GetNext(pos);
		CXDrawLine *pPlus = (CXDrawLine*)m_oCharPlusDrawList.FindByID(pMinus->m_strID);
		//显示实心矩形
		CRect rc;
		CPoint ptPointMin,ptPointMax;
		pAxisInterface->LogicPointToDevicePoint(pPlus->m_fXe,pPlus->m_fYe, &ptPointMax);
		pAxisInterface->LogicPointToDevicePoint(pMinus->m_fXb,pMinus->m_fYb, &ptPointMin);
		if (ptPointMin.x <ptPointLeftTop.x)
		{
			ptPointMin.x = ptPointLeftTop.x;
		}
		if (ptPointMax.x <ptPointLeftTop.x)
		{
			ptPointMax.x = ptPointLeftTop.x;
		}
		if (ptPointMax.y<ptPointLeftTop.y)
		{
			ptPointMax.y = ptPointLeftTop.y;
		}

		rc = CRect(ptPointMin.x, ptPointMin.y,ptPointMax.x,ptPointMax.y);
		pDC->FillSolidRect(rc,RGB( 255,255, 128));
	}
}
void CZTCharDrawView::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CCharacterDrawView::Draw(pDC,fZoomRatio,ptOffset);
	DrawAxisInstruction(pDC,fZoomRatio,ptOffset);
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	if(pAxisInterface == NULL)
	{
		return;
	}

	if(m_oTestPoints.GetCount())
	{
		POS pos = m_oTestPoints.GetHeadPosition();
		while (pos)
		{
			CXDrawPoint* pt = (CXDrawPoint*)m_oTestPoints.GetNext(pos);
			if (pt->m_strName == m_strFaultype)
			{
				pt->LogicPointToDevicePoint(pAxisInterface);//20240926 luozibing 测试点故障类型与选中故障类型相同
			pt->Draw(pDC, fZoomRatio, ptOffset);
		}
	}
	}
	m_oCharDrawList.LogicPointToDevicePoint(pAxisInterface);
	m_oCharDrawList.Draw(pDC, fZoomRatio, ptOffset);	

	m_oCharPlusDrawList.LogicPointToDevicePoint(pAxisInterface);
	m_oCharPlusDrawList.Draw(pDC, fZoomRatio, ptOffset);	

	m_oCharMinusDrawList.LogicPointToDevicePoint(pAxisInterface);
	m_oCharMinusDrawList.Draw(pDC, fZoomRatio, ptOffset);

	if (CString_To_long(m_oMouseClick.m_strID) != 65535)//20240926 luozibing 不为缺省值时显示鼠标左击坐标 
	{
	m_oMouseClick.LogicPointToDevicePoint(pAxisInterface);
	m_oMouseClick.Draw(pDC, fZoomRatio, ptOffset);
	}
	if (m_oTestPoints.GetCount() != 0)//20240926 luozibing 不存在测试点时，不显示选中测试点
	{
	m_pCurrTestPoint->LogicPointToDevicePoint(pAxisInterface);
	m_pCurrTestPoint->Draw(pDC, fZoomRatio, ptOffset);
	}
}

//设置显示的单位
void CZTCharDrawView::SetXYUnitShow(CString strUnitMag,CString strUnitAng)
{
	m_strUnitMag = strUnitMag;
	m_strUnitAng = strUnitAng;
}
void CZTCharDrawView::UI_ZoomIn()
{

}
void CZTCharDrawView::UI_ZoomOut()
{

}
void CZTCharDrawView::ZoomIn(double dCoef)
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
	
	if (dYMin < 0)
	{
		dYMin = 0;
	}

    m_dMin_XAxis = dXMin;
    m_dMin_YAxis = dYMin;
    m_dMax_XAxis = dXMax;
    m_dMax_YAxis = dYMax;
	pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
	}
}

void CZTCharDrawView::ZoomOut(double dCoef)
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
	
	if (dYMin < 0)
	{
		dYMin = 0;
    }
    m_dMin_XAxis = dXMin;
    m_dMin_YAxis = dYMin;
    m_dMax_XAxis = dXMax;
    m_dMax_YAxis = dYMax;
	pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

	if (m_pXDrawMngr_Axis != NULL)
	{
		m_pXDrawMngr_Axis->LogicPointToDevicePoint();
	}
}
void CZTCharDrawView::ZoomReset(double dCoef)
{
	//CCharacterDrawView::ZoomReset(dCoef);
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface == NULL)
	{
		return;
	}
    if(m_dReSetMax_X != -1)
    {
        pAxisInterface->SetAxisMinMax(m_dReSetMin_X, m_dReSetMin_Y, m_dReSetMax_X, m_dReSetMax_Y);
    }
}
void CZTCharDrawView::ZoomAxisReset(double dMaxY)
{
    //CCharacterDrawView::ZoomReset(dCoef);
    CAxisInterface *pAxisInterface = NULL;
    m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

    if (pAxisInterface == NULL)
    {
        return;
    }

    double dXMin, dXMax, dYMin, dYMax;
    pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);
    if (dYMin < 0)
    {
        dYMin = 0;
        m_dMin_YAxis = dYMin;
        if(m_dMin_XAxis != 0&& m_dMax_XAxis != 0)
        {
            pAxisInterface->SetAxisMinMax(m_dMin_XAxis, m_dMin_YAxis, m_dMax_XAxis, m_dMax_YAxis);
        }
        else
        {
            pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);
        }
    }
    m_dReSetMax_X = dXMax;
    m_dReSetMax_Y = dYMax;
    m_dReSetMin_X = dXMin;
    m_dReSetMin_Y = dYMin;
    if (dMaxY*2 > dYMin)
    {
        dYMax = dMaxY*2;
        dMaxY = 0;
        m_dMax_YAxis = dYMax;

        m_dReSetMax_X = dXMax;
        m_dReSetMax_Y = dYMax;
        m_dReSetMin_X = dXMin;
        m_dReSetMin_Y = dYMin;
        if(m_dMin_XAxis != 0&& m_dMax_XAxis != 0)
        {
            pAxisInterface->SetAxisMinMax(m_dMin_XAxis, m_dMin_YAxis, m_dMax_XAxis, m_dMax_YAxis);
        }
        else
        {
            pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);
        }
    }
}
void CZTCharDrawView::ZoomAxisPointInCenter(double dX,double dY)
{
    //CCharacterDrawView::ZoomReset(dCoef);
    CAxisInterface *pAxisInterface = NULL;
    m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

    if (pAxisInterface == NULL)
    {
        return;
    }

    double dXMin, dXMax, dYMin, dYMax;
    pAxisInterface->GetAxisMinMax(dXMin, dYMin, dXMax, dYMax);

    double dDiff_X,dDiff_Y;
    dDiff_X = dXMax - dXMin;
    dXMin = dX-dDiff_X/2;
    dXMax = dX+dDiff_X/2;
    m_dMin_XAxis = dXMin;
    m_dMax_XAxis = dXMax;

    dDiff_Y = dYMax - dYMin;
	dYMin = dY - dDiff_Y / 2;
    dYMax = dY + dDiff_Y/2;
    m_dMin_YAxis = dYMin;
    m_dMax_YAxis = dYMax;
    if(m_dMin_XAxis != 0&& m_dMax_XAxis != 0)
    {
        pAxisInterface->SetAxisMinMax(m_dMin_XAxis, m_dMin_YAxis, m_dMax_XAxis, m_dMax_YAxis);
    }
    else
    {
        pAxisInterface->SetAxisMinMax(dXMin, dYMin, dXMax, dYMax);
    }
}
void CZTCharDrawView::LeftButtonDown()
{
	CXDrawLine *pLine = CheckCurrentTestPoint();
	m_oMouseClick.m_strID.setNum(m_oAxisInstruct_Point.m_fX);
	//判断坐标对应x轴对应坐标有无测试线
	if (pLine != NULL)
	{
		m_oMouseClick.m_fX = m_oAxisInstruct_Point.m_fX;
		m_oMouseClick.m_fY = pLine->m_fYb;
		m_oMouseClick.m_dwDrawStyle = 1;
	}
	else
	{
		m_oMouseClick.m_fX = m_oAxisInstruct_Point.m_fX;
		m_oMouseClick.m_fY = m_oAxisInstruct_Point.m_fY;
		m_oMouseClick.m_dwDrawStyle = 10;

	}
}
CXDrawLine * CZTCharDrawView::CheckCurrentTestPoint()
{
	POS pos = m_oCharDrawList.GetHeadPosition();
	while(pos != NULL)
	{
		CXDrawLine *pLine = (CXDrawLine*)m_oCharDrawList.GetNext(pos);
		if (pLine->m_fXe > 0)
		{
			if(m_oAxisInstruct_Point.m_fX - pLine->m_fXb > -PRECISION \
				&& m_oAxisInstruct_Point.m_fX - pLine->m_fXe < PRECISION)
			{
				return pLine;
			}
		} 
		else
		{
			if(m_oAxisInstruct_Point.m_fX - pLine->m_fXb < 0 \
				&& m_oAxisInstruct_Point.m_fX - pLine->m_fXe > 0)
			{
				return pLine;
			}
		}
		
	}
	return NULL;
}
void CZTCharDrawView::SetAngleAndFaultype(const CString &strAngle, const CString &strFaultype)
{
	m_strAngle = strAngle;
	m_strFaultype = strFaultype;
}
CXDrawPoint* CZTCharDrawView::AddOneTestPoint(const double &dR, const double &dX)
{
	//20240709 luozibing 新增测试点
	CXDrawPoint *pPoint = new CXDrawPoint();
	pPoint->m_fX = dR;
	pPoint->m_fY = dX;
	//pPoint->m_strID = strIDPath;
	m_oTestPoints.AddNewChild(pPoint);

	pPoint->m_crForeColor = m_crAxisInstructInit_PointColor;//初始测试点文字颜色
	pPoint->m_dwDrawStyle = 8;//o
	return pPoint;
}
CXDrawPoint* CZTCharDrawView::AddOneTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY)
{
	CXDrawPoint *pPoint = (CXDrawPoint *)m_oTestPoints.FindByID(strIDPath);
	if (pPoint != NULL)
	{
		return NULL;
	}
	pPoint = new CXDrawPoint();
	pPoint->m_strName = strFaultType;
	pPoint->m_strID = strIDPath;
	pPoint->m_fX = dX;
	pPoint->m_fY = dY;
	m_oTestPoints.AddNewChild(pPoint);
	return pPoint;
}
void CZTCharDrawView::DeleteTestPoint(const CString &strIDPath)
{
	//20240808 luozibing 删除测试点
	CXDrawPoint *pPoint = (CXDrawPoint *)m_oTestPoints.FindByID(strIDPath);
	if (pPoint != NULL)
	{
		FreeCurrTestPoint();
		m_oTestPoints.Delete(pPoint);
	}
}
bool CZTCharDrawView::UpdateTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY, BOOL bSelPonit)
{
	COLORREF  FontColor;
	DWORD dwDrawStyle;
	CXDrawPoint* pOldCurPoint;
	if (m_oMouseClick.m_dwDrawStyle == 10)
	{//20240926 luozibing当前左击坐标未在测试线上更新测试点时不显示
		m_oMouseClick.m_strID.setNum(65535);
	}
	
	CXDrawPoint *pPoint = (CXDrawPoint *)m_oTestPoints.FindByID(strIDPath);
	if (pPoint == NULL)
	{
		return false;
	}
	if (pPoint->m_fX != dX || pPoint->m_fY != dY)//测试项坐标改变
	{
		pPoint->m_fX = dX;
		pPoint->m_fY = dY;
	}
	pPoint->m_strName = strFaultType;
	if (bSelPonit)
	{//选择时设置当前点为选择状态,设置其他测试点为初始状态
		pPoint->m_crForeColor = m_crAxisInstructInit_PointColor;
		pPoint->m_dwDrawStyle = 8;
		POS pos = m_oTestPoints.GetHeadPosition();
		while (pos)
		{
			pOldCurPoint = (CXDrawPoint*)m_oTestPoints.GetNext(pos);
			if (pOldCurPoint != pPoint&&pOldCurPoint != NULL)
			{
				pOldCurPoint->m_crForeColor = m_crAxisInstructPoint_FontColor;//初始
			}
		}
		SetCurTestPoint(pPoint->m_fX, pPoint->m_fY,false);
		ZoomAxisPointInCenter(pPoint->m_fX, pPoint->m_fY);//当前选中测试项居中显示
	}
	else
	{//设置当前点为初始状态
		pPoint->m_crForeColor = m_crAxisInstructPoint_FontColor;
		pPoint->m_dwDrawStyle = 2;
	}
	return true;
}