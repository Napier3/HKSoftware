#include "SwingImpChartDrawView.h"
#include "../../../../Module/API/GloblaDrawFunctions.h"
#include "../../../../Module/XDrawBase/XDrawMngrDescartes.h"
#include "../../../../Module/XDrawBase/XDrawMngrLogarithm.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../XLangResource_Native.h"
#include "../../../Module/SttTest/Common/tmt_system_config.h"
#include <math.h>
#include <qmath.h>
extern STT_SystemParas g_oSystemParas;

CSwingImpChartDrawView::CSwingImpChartDrawView(void)
{
	//2021-9-15  lijunqing
	m_fZoomCoef = 1;

	//初始化坐标系
	m_lfAxisInstruct_Font = InitLogFont ((long)(-15/**m_fCoefficient*/),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));//zhouhj 20210218 m_fCoefficient暂时用1标识
	m_strUnitAng = /*_T("°")*/g_sLangTxt_AxisUnitAng;//20211027 sf
	m_strUnitMag = /*_T("Ω")*/g_sLangTxt_AxisUnitOmega;

	m_crAxisInstructPoint_FontColor = RGB(0, 0, 0);
	m_dInstructLeftGap = 20;
	m_dInstructTopGap = 5;
	m_dInstructSpaceGap = 3;

	m_oAxisInstruct_Point.m_fX = 0;
	m_oAxisInstruct_Point.m_fY = 0;

	m_oZsLine.m_strTag = "Zs";
	m_oZsLine.SetBeginPoint(0, 0);
	m_oZsLine.SetEndPoint(0, 0);
	m_oZtLine.m_strTag = "Zt";
	m_oZtLine.SetBeginPoint(0, 0);
	m_oZtLine.SetEndPoint(0, 0);
	m_oImpTsLine.m_strTag = "Xd'";
	m_oImpTsLine.SetBeginPoint(0, 0);
	m_oImpTsLine.SetEndPoint(0, 0);
	m_oTestPoint.x = 0;
	m_oTestPoint.y = 0;

	m_oLineFontColor = RGB(0, 0, 255);
	m_oImpCirFontColor = RGB(0, 190, 255);	
	m_oTestPointColor = RGB(255, 0, 0);

	m_pCurTest = NULL;

}

CSwingImpChartDrawView::~CSwingImpChartDrawView(void)
{
	m_pCurrTestPoint = NULL;
}

void CSwingImpChartDrawView::UI_OnMouseMove(UINT nFlags, CPoint point)
{
	SetAxisInstruct_Point(point);
}

void CSwingImpChartDrawView::UI_OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_pCurrTestPoint != NULL)
	{
		DevicePointToLogicPoint(point.x,point.y,&m_pCurrTestPoint->m_fX,&m_pCurrTestPoint->m_fY);	
//		SetTestPointLine(m_pCurrTestPoint->m_fX,m_pCurrTestPoint->m_fY);
	}
}

void CSwingImpChartDrawView::SetCharacterDatas()
{

	m_oZs.SetParameter_ByAmpAng(m_pCurTest->m_oSwingParas.m_fImpSys, m_pCurTest->m_oSwingParas.m_fImpSysPh);
	m_oZt.SetParameter_ByAmpAng(m_pCurTest->m_oSwingParas.m_fImpTf, m_pCurTest->m_oSwingParas.m_fImpTfPh);
	m_oXd.SetParameter_ByAmpAng(m_pCurTest->m_oSwingParas.m_fImpTs, 90);
	m_oZtLine.SetBeginPoint(0, 0);
	m_oZtLine.SetEndPoint(m_oZt.real, m_oZt.imag);
	m_oZsLine.SetBeginPoint(m_oZt.real, m_oZt.imag);
	m_oZsLine.SetEndPoint(m_oZt.real + m_oZs.real, m_oZt.imag + m_oZs.imag);
	m_oImpTsLine.SetBeginPoint(0, 0);
	m_oImpTsLine.SetEndPoint(m_oXd.real, m_oXd.imag);

}

void CSwingImpChartDrawView::SetTestPoint(double dX, double dY)
{
	m_oTestPoint.x = dX;
	m_oTestPoint.y = dY;

	return;
}

void CSwingImpChartDrawView::SetAxisInstruct_Point(const CPoint &point)
{
	ASSERT(m_pXDrawMngr_Axis);
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface != NULL)
	{
		pAxisInterface->DevicePointToLogicPoint(point,&m_oAxisInstruct_Point.m_fX,&m_oAxisInstruct_Point.m_fY);
	}
}

void CSwingImpChartDrawView::GetAxisInterface(CAxisInterface **ppAxisInterface)
{
	ASSERT(m_pXDrawMngr_Axis);
	m_pXDrawMngr_Axis->GetAxisInterface(ppAxisInterface);
}

void CSwingImpChartDrawView::DrawAxisInstruction(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	 
	if (pAxisInterface == NULL)
		return;

	Complex oComplex(m_oAxisInstruct_Point.m_fX,m_oAxisInstruct_Point.m_fY);
	CString strInstruct1,strInstruct2;

	strInstruct1.Format(_T("R=%.3lf"),oComplex.real);
	strInstruct1 += m_strUnitMag;
	strInstruct2.Format(_T("X=%.3lf"),oComplex.imag);
	strInstruct2 += m_strUnitMag;

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
	
}

void CSwingImpChartDrawView::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CCharacterDrawView::Draw(pDC,fZoomRatio,ptOffset);

	DrawAxisInstruction(pDC,fZoomRatio,ptOffset);

	BOOL bLogarithm = FALSE;

	if (m_pXDrawMngr_Axis->m_strAxis == AXIS_TYPE_ID_LOGARITHM)
	{
		bLogarithm = TRUE;
	}

	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	if(NULL == pAxisInterface)
		return;

	/*75°阻抗角的直线*/
	double dXmin;
	double dYmin;
	double dXmax;
	double dYmax;
	pAxisInterface->GetAxisMinMax(dXmin, dYmin, dXmax, dYmax);
	if(dXmin * tan(75*(M_PI / 180.0)) < dYmin)
	{
		m_oZLine.SetBeginPoint(dYmin / tan(75*(M_PI / 180.0)),dYmin);
	}	
	else
	{
		m_oZLine.SetBeginPoint(dXmin,dXmin * tan(75*(M_PI / 180.0)));
	}
	if(dXmax * tan(75*(M_PI / 180.0)) > dYmax)
	{
		m_oZLine.SetEndPoint(dYmax / tan(75*(M_PI / 180.0)),dYmax);
	}	
	else
	{
		m_oZLine.SetEndPoint(dXmax,dXmax * tan(75*(M_PI / 180.0)));
	}	
	m_oZLine.LogicPointToDevicePoint(pAxisInterface);
	m_oZLine.m_crForeColor = RGB(177, 177, 177);
	m_oZLine.Draw(pDC, fZoomRatio, ptOffset);

	/*振荡阻抗*/
	DrawSwingImpCharacter(pDC, fZoomRatio, ptOffset);

}

void CSwingImpChartDrawView::DrawSwingImpCharacter(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{

	CAxisInterface *pAxisInterface = NULL;
	m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	if(NULL == pAxisInterface)
		return;

	m_oZtLine.LogicPointToDevicePoint(pAxisInterface);
	m_oZsLine.LogicPointToDevicePoint(pAxisInterface);
	m_oImpTsLine.LogicPointToDevicePoint(pAxisInterface);
	m_oZtLine.Draw(pAxisInterface, pDC, m_oLineFontColor, fZoomRatio, ptOffset);
	m_oZsLine.Draw(pAxisInterface, pDC, m_oLineFontColor, fZoomRatio, ptOffset);
	m_oImpTsLine.Draw(pAxisInterface, pDC, m_oLineFontColor, fZoomRatio, ptOffset);

	long nPixel = 2;
	double dwDrawStyle = 0;
	Complex oComplex1;
	Complex o_Vs, o_Z;
	CPoint oTempPoint;
	o_Vs = oComplex1.polar(g_oSystemParas.m_fVNom, 0.0);
	for(int i = 0; i < 130; i++)
	{
		float fAngleGap = i * 360.0 / 128.0;
		o_Z = ((oComplex1.polar(g_oSystemParas.m_fVNom*m_pCurTest->m_oSwingParas.m_fRate, fAngleGap)-o_Vs)/(m_oZs+m_oXd+m_oZt)*(m_oZs+m_oZt)+o_Vs)/((oComplex1.polar(g_oSystemParas.m_fVNom * m_pCurTest->m_oSwingParas.m_fRate, fAngleGap)-o_Vs)/(m_oZs+m_oXd+m_oZt));
		pAxisInterface->LogicPointToDevicePoint(o_Z.real, o_Z.imag, &oTempPoint);
		xdraw_DrawPoint(pDC, oTempPoint, dwDrawStyle, m_oImpCirFontColor, nPixel, fZoomRatio, ptOffset);
	}

	nPixel = 4;
	pAxisInterface->LogicPointToDevicePoint(m_oTestPoint.x, m_oTestPoint.y, &oTempPoint);
	xdraw_DrawPoint(pDC, oTempPoint, dwDrawStyle, m_oTestPointColor, nPixel, fZoomRatio, ptOffset);

	return;
}

//设置显示的单位 非阻抗类调用 20211027 sf
void CSwingImpChartDrawView::SetXYUnitShow(CString strUnitMag,CString strUnitAng)
{
	m_strUnitMag = strUnitMag;
	m_strUnitAng = strUnitAng;
}
