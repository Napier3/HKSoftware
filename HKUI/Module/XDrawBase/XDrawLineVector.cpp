#include "XDrawLineVector.h"
#include "../API/GloblaDrawFunctions.h"
#include <math.h>
#include <qmath.h>

CXDrawLineVector::CXDrawLineVector(void)
{
	m_lfTextFont = InitLogFont((long)(-15),0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',_T("Tahoma"));//zhouhj 20210218 m_fCoefficient暂时用1标识
	m_crForeColor = RGB(255, 255, 255);
	m_oTagColor = RGB(0, 0, 0);
	m_strTag = "";
	m_dInstructLeftGap = 7;
	m_dInstructTopGap = 3;
	m_dInstructSpaceGap = 3;

}

CXDrawLineVector::~CXDrawLineVector(void)
{
}

#include <math.h>
void CXDrawLineVector::Draw(CAxisInterface *pAxis, CDC *pDC, COLORREF lineColor, double fZoomRatio,const CPoint &ptOffset)
{
	if(NULL == pAxis)
		return;

	m_crForeColor = lineColor;
	m_nWidth = 2;
	CXDrawLine::Draw(pDC, fZoomRatio, ptOffset);

	CPoint ptTemp;
	double d_BegX, d_BegY, d_EndX, d_EndY; /*坐标*/
	GetBeginPoint(d_BegX, d_BegY);
	GetEndPoint(d_EndX, d_EndY);
	pAxis->LogicPointToDevicePoint(d_EndX, d_EndY, &ptTemp);
	m_triPoints[0] = ptTemp;

	double d_BegPointX, d_BegPointY, d_EndPointX, d_EndPointY; /*像素点*/
	d_EndPointX = ptTemp.x;
	d_EndPointY = ptTemp.y;
	pAxis->LogicPointToDevicePoint(d_BegX, d_BegY, &ptTemp);
	d_BegPointX = ptTemp.x;
	d_BegPointY = ptTemp.y;
	
	double dMag = sqrt((d_EndPointY - d_BegPointY)*(d_EndPointY - d_BegPointY)+(d_EndPointX - d_BegPointX)*(d_EndPointX - d_BegPointX));
	double dAngle = asin((d_EndPointY - d_BegPointY)/dMag);
	double dPointX, dPointY;
	double dVectorAngle = 12 * (M_PI / 180.0);  //箭头夹角
	double dVectorWidth = 10;  //箭头长度 像素点
	
	dPointX = d_BegPointX + (dMag - dVectorWidth)*cos(dAngle) - dVectorWidth*tan(dVectorAngle)*sin(dAngle);
	dPointY = d_BegPointY + (dMag - dVectorWidth)*sin(dAngle) + dVectorWidth*tan(dVectorAngle)*cos(dAngle);
	m_triPoints[1].x = dPointX;
	m_triPoints[1].y = dPointY;
	dPointX = d_BegPointX + (dMag - dVectorWidth)*cos(dAngle) + dVectorWidth*tan(dVectorAngle)*sin(dAngle);
	dPointY = d_BegPointY + (dMag - dVectorWidth)*sin(dAngle) - dVectorWidth*tan(dVectorAngle)*cos(dAngle);
	m_triPoints[2].x = dPointX;
	m_triPoints[2].y = dPointY;

#ifdef _PSX_IDE_QT_
	QColor crBrush(lineColor & 0xff, (lineColor & 0xff00)>>8, (lineColor & 0xff0000)>>16);
	pDC->setBrush(crBrush);
#endif
	pDC->Polygon(m_triPoints, 3);
#ifdef _PSX_IDE_QT_
	pDC->setBrush(Qt::NoBrush);
#endif

	CRect rect,rectWorkArea;
	rectWorkArea = pAxis->GetWorkArea();
	LOGFONT lf = m_lfTextFont;
	lf.lfHeight = (long)(fZoomRatio * lf.lfHeight);
	long lfWidth = GetCharWidthByLogfont2(pDC,lf);

	rect.left = m_triPoints[0].x + m_dInstructLeftGap;
	rect.top = m_triPoints[0].y + m_dInstructTopGap;
	rect.right = rect.left + lfWidth * m_strTag.GetLength()*2;
	rect.bottom = rect.top + abs(lf.lfHeight);
	rect.OffsetRect(ptOffset);

	CmDrawTextRect(pDC, m_strTag, m_oTagColor,
		&rect,RGB(0,0,0),lf,
		TRANSPARENT,DT_VCENTER|DT_LEFT,0);

}
