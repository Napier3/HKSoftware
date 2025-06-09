// MeterAxis.cpp : implementation file
//

#include "stdafx.h"
#include "MeterAxis.h"
#include <math.h>
#include "../API/GloblaDrawFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define METER_ROUND(x) (int)((x) + 0.5 - (double)((x) < 0))

/////////////////////////////////////////////////////////////////////////////
// CMeterAxis
CMeterAxis::CMeterAxis()
{
	m_bFrameGradient = FALSE;
	m_nTabNum = 3;
    m_fStartAngleDeg = 210;
    m_fEndAngleDeg = 330;
    m_nTicks = 10;
    m_nSubTicks = 5;
    m_dMaxValue = 100.0;
    m_dMinValue = 50.0;
    m_dCurrentValue = 00.0;
    m_nScaleDecimals = 0;
    m_nValueDecimals = 1;
    m_colorNeedle = RGB(255, 0, 0);
    m_strUnits = _T("");
    m_bColorTick = TRUE;

    // ��ɫ���
    m_colorTable[0] = RGB(177,255,99);
    m_colorTable[1] = RGB(0, 255,0);
    m_colorTable[2] = RGB(0,123,0);
    m_colorTable[3] = RGB(230,248, 38);
    m_colorTable[4] = RGB(253, 138, 29);
    m_colorTable[5] = RGB(255, 0, 0);

	// ��ȡϵͳ��ɫ;
	m_colorWindow    = RGB(0, 240, 240);//GetSysColor(COLOR_WINDOW);
	m_colorButton    = RGB(240, 240, 240);//GetSysColor(COLOR_BTNFACE);
	m_colorShadow    = RGB(192, 192, 192);//GetSysColor(COLOR_BTNSHADOW);
	m_colorHighlight = RGB(0, 0, 255);//GetSysColor(COLOR_BTNHIGHLIGHT);
	m_colorText        = RGB(0, 0, 0);//GetSysColor(COLOR_BTNTEXT);
	m_nScaleCount = 0;

	m_nFrameWidth = 2;            // �߿���
	m_nDrawTicks = 1;
	m_bDrawBackground = TRUE;
}

CMeterAxis::~CMeterAxis()
{
}


void CMeterAxis::DrawMeter(CDC *pDC)
{
	DrawMeterBack(pDC);
	DrawValue(pDC);
}

void CMeterAxis::DrawMeterBack(CDC *pDC)
{
	DrawMeterBackground(pDC);

	// ����ָ��
	DrawNeedle(pDC);

	DrawNode(pDC);
}

void CMeterAxis::SetBoder(const CRect &rc)
{
	m_rectCtrl  =rc;

	CalWorkArea();
	CalcMexterAxisDraw();
}

void CMeterAxis::SetBoder(long x, long y, long cx, long cy)
{
	SetBoder(CRect(x, y, cx, cy) );
}

void CMeterAxis::CalWorkArea()
{
	CRect rcMax;
	CPoint ptStart, ptEnd, ptCenter;
	double dLeftAngleRad, dRightAngleRad;
	CRect rc(0, 0, 100, 100);
	
	m_nRadiusFrame = min (rc.Width(), rc.Height());
	m_nRadiusFrame /= 2;

	ptCenter = rc.CenterPoint();

	CPoint pttemp;
	CString strtemp;
	double dRadPerDeg;
	double dTickAngleRad;
	double dTemp;
	int nTickAngle;
	double dtempangle;

	// ������ʼ����ֹ�ǻ���
	dRadPerDeg = 3.1415926525 /180.0;
	dLeftAngleRad = (m_fStartAngleDeg-180.0)*dRadPerDeg;
	dRightAngleRad = (m_fEndAngleDeg-360.0)*dRadPerDeg;

	// ����Բ����ʼ��ֹ�㼰����
	ptStart.x = ptCenter.x - (int)(m_nRadiusFrame*cos(dLeftAngleRad));
	ptStart.y = ptCenter.y + (int)(m_nRadiusFrame*sin(dLeftAngleRad));
	ptEnd.x = ptCenter.x  + (int)(m_nRadiusFrame*cos(-dRightAngleRad));
	ptEnd.y = ptCenter.y  + (int)(m_nRadiusFrame*sin(-dRightAngleRad));

	rcMax.top = 0;
	rcMax.bottom = ptCenter.y;
	rcMax.bottom = max(rcMax.bottom, ptStart.y);
	rcMax.bottom = max(rcMax.bottom, ptEnd.y);

	if (ptCenter.y < ptStart.y || ptCenter.y < ptEnd.y)
	{
		rcMax.left = min(ptStart.x, 0);
		rcMax.right = max(ptEnd.x, rc.right);
	}
	else
	{
		rcMax.left = max(ptStart.x, 0);
		rcMax.right = min(ptEnd.x, rc.right);
	}

	double dRate1 = rcMax.Width();
	dRate1 /= rcMax.Height();
	double dRate2 = m_rectCtrl.Width() ;
	dRate2 /= m_rectCtrl.Height();

	m_rectWorkArea = m_rectCtrl;
	double dOffset = 0;
	double dWidth=0, dHeight=0;
	long nWidth = 0, nHeight = 0;
	
	if (dRate1 > dRate2)
	{//����ľ��� �� ʵ�ʾ��θ��� ������
		nWidth = m_rectCtrl.Width();
		dHeight = nWidth / dRate1;
		dOffset = (m_rectCtrl.Height() - dHeight) / 2;
		long yOffset = dOffset;
		m_rectWorkArea.top += yOffset;
		m_rectWorkArea.bottom -= yOffset;
		double dRadiusFrame = m_rectWorkArea.Width();
		dRadiusFrame /= rcMax.Width();
		dRadiusFrame *= m_nRadiusFrame;
		m_nRadiusFrame = dRadiusFrame;
	}
	else
	{//����ľ��� �� ʵ�ʾ��θ��ߣ� ����߶�
		nHeight = m_rectCtrl.Height();
		dWidth = nHeight * dRate1;
		dOffset = (m_rectCtrl.Width() - dWidth) / 2;
		long xOffset = dOffset;
		m_rectWorkArea.left += xOffset;
		m_rectWorkArea.right -= xOffset;
		double dRadiusFrame = m_rectWorkArea.Height();
		dRadiusFrame /= rcMax.Height();
		dRadiusFrame *= m_nRadiusFrame;
		m_nRadiusFrame = dRadiusFrame;
	}

	long nDeflate = m_nFrameWidth * 2;;
	m_rectWorkArea.left += nDeflate;
	m_rectWorkArea.top += nDeflate;
	m_rectWorkArea.right -= nDeflate;
	m_rectWorkArea.bottom -= nDeflate+m_nFrameWidth;
	m_nRadiusFrame -= nDeflate;

	dWidth = m_rectWorkArea.Width();
	dWidth /= rcMax.Width();
	dHeight = m_rectWorkArea.Height();
	dHeight /= rcMax.Height();

	m_ptMeterAxisCenter.x = dWidth * ptCenter.x + m_rectWorkArea.left;
	m_ptMeterAxisCenter.y = dHeight * ptCenter.y  + m_rectWorkArea.top;
}

void CMeterAxis::CalcMexterAxisDraw()
{
	int nInnerRadius = m_nRadiusFrame*8/10;    // ��Բ���뾶
	m_nCenterRadius = m_nRadiusFrame/20;    // ����԰�뾶��С
	double dstepTickDeg = (360.0+m_fStartAngleDeg-m_fEndAngleDeg)/(m_nTicks*m_nSubTicks);    // �̶Ȳ����Ƕ�
	int nSubTickR = nInnerRadius+(m_nRadiusFrame-2*m_nFrameWidth-nInnerRadius)/2;
	double dDeg = (m_fStartAngleDeg+360.0-m_fEndAngleDeg)/(m_nTabNum*METER_PT_NUM);

	CPoint pttemp;
	CString strtemp;
	double dRadPerDeg;
	double dTickAngleRad;
	double dTemp;
	m_nScaleCount = 0;
	int nTickAngle;
	int nHeight;    // �����С
	double dtempangle;

	// ������ʼ����ֹ�ǻ���
	dRadPerDeg = 3.14159265/180.0;
	m_dLeftAngleRad = (m_fStartAngleDeg-180.0)*dRadPerDeg;
	m_dRightAngleRad = (m_fEndAngleDeg-360.0)*dRadPerDeg;

	// ����Բ����ʼ��ֹ�㼰����
	m_ptStart.x = m_ptMeterAxisCenter.x-(int)(m_nRadiusFrame*cos(m_dLeftAngleRad));
	m_ptStart.y = m_ptMeterAxisCenter.y+(int)(m_nRadiusFrame*sin(m_dLeftAngleRad));
	m_ptEnd.x = m_ptMeterAxisCenter.x+(int)(m_nRadiusFrame*cos(-m_dRightAngleRad));
	m_ptEnd.y = m_ptMeterAxisCenter.y+(int)(m_nRadiusFrame*sin(-m_dRightAngleRad));

	m_rectPanel.SetRect(m_ptMeterAxisCenter.x-m_nRadiusFrame, m_ptMeterAxisCenter.y-m_nRadiusFrame,
		m_ptMeterAxisCenter.x+m_nRadiusFrame, m_ptMeterAxisCenter.y+m_nRadiusFrame);

	double dAngle = 0;

	// ��ȡ���λ��
	for(int i=0; i<=METER_PT_NUM*m_nTabNum; i++)
	{
		dAngle = (m_fStartAngleDeg-i*dDeg)*dRadPerDeg;
		m_ptGroup1[i].x = m_ptMeterAxisCenter.x + (int)((m_nRadiusFrame-m_nFrameWidth)*cos(dAngle));
		m_ptGroup1[i].y = m_ptMeterAxisCenter.y - (int)((m_nRadiusFrame-m_nFrameWidth)*sin(dAngle));
		m_ptGroup2[i].x = m_ptMeterAxisCenter.x + (int)(m_nRadiusFrame*8*cos(dAngle) / 10);
		m_ptGroup2[i].y = m_ptMeterAxisCenter.y - (int)(m_nRadiusFrame*8*sin(dAngle) / 10);
	}

	// ������Ȧ
	m_ptInnerStart.x = m_ptMeterAxisCenter.x-(int)(nInnerRadius*cos(m_dLeftAngleRad));
	m_ptInnerStart.y = m_ptMeterAxisCenter.y+(int)(nInnerRadius*sin(m_dLeftAngleRad));
	m_ptInnerEnd.x = m_ptMeterAxisCenter.x+(int)(nInnerRadius*cos(-m_dRightAngleRad));
	m_ptInnerEnd.y = m_ptMeterAxisCenter.y+(int)(nInnerRadius*sin(-m_dRightAngleRad));
	m_rectInnerPanel.SetRect(m_ptMeterAxisCenter.x-nInnerRadius, m_ptMeterAxisCenter.y-nInnerRadius,
		m_ptMeterAxisCenter.x+nInnerRadius ,m_ptMeterAxisCenter.y+nInnerRadius);

	// ����̶ȵ�,���ⲻ����������ϴ����*100
	for(nTickAngle=m_fStartAngleDeg*100; nTickAngle>=(m_fEndAngleDeg-360)*100; nTickAngle-=(int)(dstepTickDeg*100))
	{
		// ת���ɻ���
		dTickAngleRad = (double)nTickAngle/100*dRadPerDeg;

		// ȷ����Ȧ����
		// ȷ��x����
		dTemp = m_ptMeterAxisCenter.x + (m_nRadiusFrame-2*m_nFrameWidth)*cos(dTickAngleRad);
		m_pointBoundary[m_nScaleCount].x = METER_ROUND(dTemp);
		// ȷ��y����
		dTemp = m_ptMeterAxisCenter.y - (m_nRadiusFrame-2*m_nFrameWidth)*sin(dTickAngleRad);
		m_pointBoundary[m_nScaleCount].y = METER_ROUND(dTemp);

		// ȷ���̶ȵ�(���̶Ⱥ��ӿ̶�)
		//���̶ȼ��ı���ע��
		if(m_nScaleCount%m_nSubTicks == 0)
		{
			dTemp = m_ptMeterAxisCenter.x + nInnerRadius*cos(dTickAngleRad);
			m_pointInner[m_nScaleCount].x = METER_ROUND(dTemp);
			dTemp = m_ptMeterAxisCenter.y - nInnerRadius*sin(dTickAngleRad);
			m_pointInner[m_nScaleCount].y = METER_ROUND(dTemp);
		}
		// �ӿ̶�
		else
		{
			dTemp = m_ptMeterAxisCenter.x + nSubTickR*cos(dTickAngleRad);
			m_pointInner[m_nScaleCount].x = METER_ROUND(dTemp);
			dTemp = m_ptMeterAxisCenter.y - nSubTickR*sin(dTickAngleRad);
			m_pointInner[m_nScaleCount].y = METER_ROUND(dTemp);
		}
		m_nScaleCount++ ;
	}

	// ���������
#ifndef _PSX_IDE_QT_
	m_rgnBoundary.DeleteObject() ;
	m_rgnBoundary.CreatePolygonRgn(m_pointBoundary, m_nScaleCount, ALTERNATE);
#endif

// 	m_rectValue.top = m_ptMeterAxisCenter.y + m_nRadiusFrame/5;
// 	m_rectValue.bottom = m_ptMeterAxisCenter.y + m_nRadiusFrame/2;
	m_rectValue.top = m_rectWorkArea.bottom - m_nRadiusFrame /2;
	m_rectValue.bottom = m_rectWorkArea.bottom;
	m_rectValue.left = m_ptMeterAxisCenter.x - m_nRadiusFrame/2;
	m_rectValue.right = m_ptMeterAxisCenter.x + m_nRadiusFrame/2;
}

void CMeterAxis::DrawMeterBackground(CDC *pDC)
{
    int nInnerRadius = m_nRadiusFrame*8/10;    // ��Բ���뾶

    double dstepTickDeg = (360.0+m_fStartAngleDeg-m_fEndAngleDeg)/(m_nTicks*m_nSubTicks);    // �̶Ȳ����Ƕ�

    int nSubTickR = nInnerRadius+(m_nRadiusFrame-2*m_nFrameWidth-nInnerRadius)/2;

    double dDeg = (m_fStartAngleDeg+360.0-m_fEndAngleDeg)/(m_nTabNum*METER_PT_NUM);

    CPen penDraw, *pPenOld;
    CFont *pFontOld;
    CBrush brushFill, *pBrushOld;
    CPoint ptRgn[METER_PT_NUM*2+2];
    CPoint pttemp;
    CString strtemp;
    double dRadPerDeg;
    double dTickAngleRad;
    double dTemp;
    int nTickAngle;
    int nHeight;    // �����С
    double dtempangle;

    // �ð�ťɫ���Ʊ���
	if (m_bDrawBackground)
	{
		brushFill.DeleteObject();
		brushFill.CreateSolidBrush(m_colorButton);
		pBrushOld = pDC->SelectObject(&brushFill);
		pDC->Rectangle(m_rectCtrl);
		pDC->SelectObject(pBrushOld);
	}

	CRect rectPanel = m_rectPanel;
	CPoint ptEnd = m_ptEnd;
	CPoint ptStart = m_ptStart;


    // ����Բ�̱߿�
	if (m_bFrameGradient)
	{
		// ��ʱʹ�õ���ɫ
		COLORREF colorCaption, cEdge, cMiddle;
		cMiddle = RGB(255, 255, 255);
		cEdge = RGB(96, 96, 255);

		for(int iOnBand=m_nFrameWidth; iOnBand>0; iOnBand--)
		{
			penDraw.DeleteObject();
			colorCaption = RGB((GetRValue(cEdge)-GetRValue(cMiddle))*((float)iOnBand)/m_nFrameWidth+GetRValue(cMiddle),
				(GetGValue(cEdge)-GetGValue(cMiddle))*((float)iOnBand)/m_nFrameWidth+GetGValue(cMiddle),
				(GetBValue(cEdge)-GetBValue(cMiddle))*((float)iOnBand)/m_nFrameWidth+GetBValue(cMiddle));
			penDraw.CreatePen(PS_SOLID, iOnBand*2, colorCaption);
			pPenOld = pDC->SelectObject(&penDraw);
			pDC->Arc(&rectPanel, ptEnd, ptStart);
			pDC->SelectObject(pPenOld);
		}
	}
	else
	{
		penDraw.DeleteObject();
		penDraw.CreatePen(PS_SOLID, m_nFrameWidth, RGB(0, 0, 0));
		pPenOld = pDC->SelectObject(&penDraw);
		pDC->Arc(&rectPanel, ptEnd, ptStart);
		pDC->SelectObject(pPenOld);
	}


    penDraw.DeleteObject();
    penDraw.CreatePen(PS_SOLID, 1, RGB(255,255,0));
    pPenOld = pDC->SelectObject(&penDraw);
   pDC->Arc(&m_rectInnerPanel, m_ptInnerEnd, m_ptInnerStart);
    pDC->SelectObject(pPenOld);

    if(m_bColorTick)
    {
        // ����ɫ�ʿ̶�
        for(int i=0; i<m_nTabNum; i++)
        {
            //ȷ������
            for(int j=0; j<=METER_PT_NUM; j++)
            {
                ptRgn[j] = m_ptGroup1[i*METER_PT_NUM+j];
                ptRgn[2*METER_PT_NUM+1-j] = m_ptGroup2[i*METER_PT_NUM+j];
            }

#ifdef _PSX_IDE_QT_
			QColor qcolor;
			qcolor = COLORREF_to_QColor(m_colorTable[i]);
			QBrush brush(qcolor);
			pDC->setBrush(brush);
#else
            brushFill.DeleteObject();
            brushFill.CreateSolidBrush(m_colorTable[i]);
			pBrushOld = pDC->SelectObject(&brushFill);
#endif
            penDraw.DeleteObject();
            penDraw.CreatePen(PS_SOLID, 1, m_colorTable[i]);
            pPenOld = pDC->SelectObject(&penDraw);

#ifdef _PSX_IDE_QT_
			pDC->drawPolygon(( QPoint*)ptRgn, 2*METER_PT_NUM+2);
#else
            pDC->Polygon(ptRgn, 2*METER_PT_NUM+2);
			pDC->SelectObject(pBrushOld);
#endif

            pDC->SelectObject(pPenOld);
        }

    }

	if (!m_nDrawTicks)
	{
		return;
	}

    // ���ƿ̶�
    penDraw.DeleteObject();
    penDraw.CreatePen(PS_SOLID, 1, RGB(0,0,0));
    pPenOld = pDC->SelectObject(&penDraw);
    for(int i=0; i<m_nScaleCount; i++)
    {
        pDC->MoveTo(m_pointBoundary[i]);
        pDC->LineTo(m_pointInner[i]);
    }
    pDC->SelectObject(pPenOld);

    // �̶ȱ��
    nHeight = m_nRadiusFrame/8;  //�����С
	LOGFONT oLogFont;
	oLogFont = InitLogFont ();
	oLogFont.lfHeight = nHeight;
	m_font.CreateFontIndirect(&oLogFont);

    pFontOld = pDC->SelectObject(&m_font);
    pDC->SetBkMode(TRANSPARENT);
	unsigned long uFormat = 0;
	CRect rcText(0, 0, 0, 0), rcSize(0, 0, 0, 0);
  
	for(int i=0; i<=m_nTicks; i++)
    {
        dtempangle = m_fStartAngleDeg-i*m_nSubTicks*dstepTickDeg;
        strtemp.Format("%.*lf", m_nScaleDecimals, (m_dMinValue+(m_dMaxValue-m_dMinValue)*i/m_nTicks));
		pDC->DrawText(strtemp, &rcSize, DT_CALCRECT);

        if(dtempangle>190)
        {
			uFormat = DT_BOTTOM|DT_LEFT;
            //pDC->SetTextAlign(TA_BOTTOM|TA_LEFT);
            //pDC->TextOut(m_pointInner[m_nSubTicks*i].x, m_pointInner[m_nSubTicks*i].y+nHeight/2, strtemp);
			rcText.left = m_pointInner[m_nSubTicks*i].x;
			rcText.top = m_pointInner[m_nSubTicks*i].y-nHeight/2;
        }

        else if(dtempangle>170)
        {
            //pDC->SetTextAlign(TA_BASELINE|TA_LEFT);
			uFormat = DT_VCENTER|DT_LEFT;
            //pDC->TextOut(m_pointInner[m_nSubTicks*i].x, m_pointInner[m_nSubTicks*i].y+nHeight/3, strtemp);
			rcText.left = m_pointInner[m_nSubTicks*i].x;
			rcText.top = m_pointInner[m_nSubTicks*i].y-nHeight/2;
       }
        else if(dtempangle>135)
        {
            //pDC->SetTextAlign(TA_BASELINE|TA_LEFT);
			uFormat = DT_VCENTER|DT_LEFT;
            //pDC->TextOut(m_pointInner[m_nSubTicks*i].x, m_pointInner[m_nSubTicks*i].y+nHeight/2, strtemp);
			rcText.left = m_pointInner[m_nSubTicks*i].x;
			rcText.top = m_pointInner[m_nSubTicks*i].y-nHeight/2;
       }
        else if(dtempangle>100)
        {
            //pDC->SetTextAlign(TA_TOP|TA_LEFT);
			uFormat = DT_TOP|DT_LEFT;
            //pDC->TextOut(m_pointInner[m_nSubTicks*i].x-nHeight/4, m_pointInner[m_nSubTicks*i].y-nHeight/8, strtemp);
			rcText.left = m_pointInner[m_nSubTicks*i].x-nHeight/4;
			rcText.top = m_pointInner[m_nSubTicks*i].y-nHeight/8;
        }

        else if(dtempangle>80)
        {
			uFormat = DT_TOP|DT_CENTER;
            //pDC->SetTextAlign(TA_TOP|TA_CENTER);
            //pDC->TextOut(m_pointInner[m_nSubTicks*i].x, m_pointInner[m_nSubTicks*i].y, strtemp);
			rcText.left = m_pointInner[m_nSubTicks*i].x - nHeight/2;
			rcText.top = m_pointInner[m_nSubTicks*i].y;
        }
        else if(dtempangle>45)
        {
            //pDC->SetTextAlign(TA_BOTTOM|TA_RIGHT);
			uFormat = DT_VCENTER|DT_RIGHT;
            //pDC->TextOut(m_pointInner[m_nSubTicks*i].x+nHeight/3, m_pointInner[m_nSubTicks*i].y+nHeight, strtemp);
			rcText.left = m_pointInner[m_nSubTicks*i].x-rcSize.Width();
			rcText.top = m_pointInner[m_nSubTicks*i].y;//-nHeight/2;
        }
        else if(dtempangle>10)
        {
            //pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);
			uFormat = DT_VCENTER|DT_RIGHT;
            //pDC->TextOut(m_pointInner[m_nSubTicks*i].x, m_pointInner[m_nSubTicks*i].y+nHeight/2, strtemp);
			rcText.left = m_pointInner[m_nSubTicks*i].x-rcSize.Width();
			rcText.top = m_pointInner[m_nSubTicks*i].y;//+nHeight/2;
        }
        else if(dtempangle>-10)
        {
            //pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);
			uFormat = DT_VCENTER|DT_RIGHT;
            //pDC->TextOut(m_pointInner[m_nSubTicks*i].x, m_pointInner[m_nSubTicks*i].y+nHeight/3, strtemp);
			rcText.left = m_pointInner[m_nSubTicks*i].x-rcSize.Width();
			rcText.top = m_pointInner[m_nSubTicks*i].y - nHeight/3;
        }
        else
        {
            //pDC->SetTextAlign(TA_RIGHT|TA_BOTTOM);
			uFormat = DT_BOTTOM|DT_RIGHT;
            //pDC->TextOut(m_pointInner[m_nSubTicks*i].x, m_pointInner[m_nSubTicks*i].y+nHeight/2, strtemp);
			rcText.left = m_pointInner[m_nSubTicks*i].x  -rcSize.Width();
			rcText.top = m_pointInner[m_nSubTicks*i].y - nHeight/2;
        }

		rcText.bottom = rcText.top + rcSize.Height();
		rcText.right = rcText.left + rcSize.Width();
		//pDC->Rectangle(rcText);
		CmDrawTextRect(pDC, strtemp, m_colorText, rcText, m_colorWindow, oLogFont, TRANSPARENT, uFormat, 0);
    }

    pDC->SelectObject(pFontOld);
}

void CMeterAxis::DrawNeedle(CDC *pDC)
{
    int nResult;
    double dRadPerDeg = 4.0*atan(1.0)/180.0;
    double dAngleDeg;
    double dAngleRad ;
    double dTemp ;
    CBrush brushFill, *pBrushOld ;
    CPen penDraw, *pPenOld ;
    CPoint pointNeedle[4] ;    // ָ�����ı������


    // ����ǶȲ��޶�ָ���ߵĽǶ�
    dAngleDeg = m_fStartAngleDeg-(360.0+m_fStartAngleDeg-m_fEndAngleDeg)
        *(m_dCurrentValue-m_dMinValue)/(m_dMaxValue-m_dMinValue);
    dAngleDeg = min(dAngleDeg, m_fStartAngleDeg);
    dAngleDeg = max(dAngleDeg, m_fEndAngleDeg-360.0);
    dAngleRad = dAngleDeg*dRadPerDeg;

    // ���������εױ�������
    pointNeedle[0].x = m_ptMeterAxisCenter.x - (int)(m_nCenterRadius*10*sin(dAngleRad)/8);
    pointNeedle[0].y = m_ptMeterAxisCenter.y - (int)(m_nCenterRadius*10*cos(dAngleRad)/8);
    pointNeedle[2].x = m_ptMeterAxisCenter.x + (int)(m_nCenterRadius*10*sin(dAngleRad)/8);
    pointNeedle[2].y = m_ptMeterAxisCenter.y + (int)(m_nCenterRadius*10*cos(dAngleRad)/8);

    // ����ָ�붥������
    dTemp = m_ptMeterAxisCenter.x + m_nRadiusFrame*cos(dAngleRad)*95/100;
    pointNeedle[1].x = METER_ROUND(dTemp);
    dTemp = m_ptMeterAxisCenter.y - m_nRadiusFrame*sin(dAngleRad)*95/100;
    pointNeedle[1].y = METER_ROUND(dTemp);
  
	brushFill.CreateSolidBrush(m_colorNeedle);
	penDraw.CreatePen(PS_SOLID, 3, m_colorNeedle);
	pPenOld = pDC->SelectObject(&penDraw) ;
	pBrushOld = pDC->SelectObject(&brushFill) ;

	// ����ָ��
	//pDC->Polygon(pointNeedle, 3);
	pDC->MoveTo(m_ptMeterAxisCenter);
	pDC->LineTo( pointNeedle[1]);

	pDC->SelectObject(pPenOld);
	pDC->SelectObject(pBrushOld);

	return;
/*	
	// ����ָ��β������
    dTemp = m_ptMeterAxisCenter.x - m_nRadiusFrame*cos(dAngleRad)/6;
    pointNeedle[3].x = METER_ROUND(dTemp);
    dTemp = m_ptMeterAxisCenter.y + m_nRadiusFrame*sin(dAngleRad)/6;
    pointNeedle[3].y = METER_ROUND(dTemp);

#ifndef _PSX_IDE_QT_
	pDC->SelectClipRgn(&m_rgnBoundary);
	m_rgnBoundary.DeleteObject() ;
#endif

    brushFill.CreateSolidBrush(m_colorNeedle);
    penDraw.CreatePen(PS_SOLID, 1, m_colorNeedle);

    pPenOld = pDC->SelectObject(&penDraw) ;
    pBrushOld = pDC->SelectObject(&brushFill) ;

    // ����ָ��
    pDC->Polygon(pointNeedle, 4);

    nResult = pDC->SelectClipRgn(NULL);

    pDC->SelectObject(pPenOld);
    pDC->SelectObject(pBrushOld);

    // ����д���
    if(dAngleDeg>90)
    {
        penDraw.DeleteObject();
        penDraw.CreatePen(PS_SOLID, 2, m_colorShadow);
        pPenOld = pDC->SelectObject(&penDraw);
        pDC->MoveTo(pointNeedle[1]);
        pDC->LineTo(pointNeedle[0]);
        pDC->LineTo(pointNeedle[3]);
        pDC->SelectObject(pPenOld);

        penDraw.DeleteObject();
        penDraw.CreatePen(PS_SOLID, 1, m_colorHighlight);
        pPenOld = pDC->SelectObject(&penDraw);
        pDC->MoveTo(pointNeedle[1]);
        pDC->LineTo(pointNeedle[2]);
        pDC->LineTo(pointNeedle[3]);
        pDC->SelectObject(pPenOld);
    }
    else
    {
        penDraw.DeleteObject();
        penDraw.CreatePen(PS_SOLID, 2, m_colorShadow);
        pPenOld = pDC->SelectObject(&penDraw);
        pDC->MoveTo(pointNeedle[1]);
        pDC->LineTo(pointNeedle[2]);
        pDC->LineTo(pointNeedle[3]);
        pDC->SelectObject(pPenOld);

        penDraw.DeleteObject();
        penDraw.CreatePen(PS_SOLID, 1, m_colorHighlight);
        pPenOld = pDC->SelectObject(&penDraw);
        pDC->MoveTo(pointNeedle[1]);
        pDC->LineTo(pointNeedle[0]);
        pDC->LineTo(pointNeedle[3]);
        pDC->SelectObject(pPenOld);
    }
	*/
}

void CMeterAxis::UpdateNeedle(double dValue)
{
    m_dCurrentValue = dValue;
    //Invalidate();
}

void CMeterAxis::SetNeedleColor(COLORREF colorNeedle)
{
    m_colorNeedle = colorNeedle ;
}


void CMeterAxis::SetRange(double dMin, double dMax)
{
    m_dMaxValue = dMax ;
    m_dMinValue = dMin ;
}


void CMeterAxis::SetScaleDecimals(int nDecimals)
{
    m_nScaleDecimals = nDecimals ;
}

void CMeterAxis::SetUnits(CString &strUnits)
{
    m_strUnits = strUnits ;
}

void CMeterAxis::SetValueDecimals(int nDecimals)
{
    m_nValueDecimals = nDecimals ;
}





void CMeterAxis::DrawNode(CDC *pDC)
{
    CPen penDraw, *pPenOld;
    COLORREF cEdge, cMiddle, cNode;
    cMiddle = RGB(255, 255, 255);
    cEdge = RGB(0, 0, 0);
	CRect rc;
	CPoint ptBegin, ptEnd;

    for(int i=m_nCenterRadius*3/4; i>=0; i--)
    {
        cNode = RGB((GetRValue(cEdge)-GetRValue(cMiddle))*((float)i)*4/(3*m_nCenterRadius)+GetRValue(cMiddle),
            (GetGValue(cEdge)-GetGValue(cMiddle))*((float)i)*4/(3*m_nCenterRadius)+GetGValue(cMiddle),
            (GetBValue(cEdge)-GetBValue(cMiddle))*((float)i)*4/(3*m_nCenterRadius)+GetBValue(cMiddle));

        penDraw.DeleteObject();
        penDraw.CreatePen(PS_SOLID, 1, cNode);
        pPenOld = pDC->SelectObject(&penDraw);
		rc.left = m_ptMeterAxisCenter.x-i;
		rc.top = m_ptMeterAxisCenter.y-i;
		rc.right = m_ptMeterAxisCenter.x+i;
		rc.bottom = m_ptMeterAxisCenter.y+i;
		ptBegin.x = m_ptMeterAxisCenter.x-i;
		ptBegin.y = m_ptMeterAxisCenter.y;
		ptEnd.x = m_ptMeterAxisCenter.x-i;
		ptEnd.y = m_ptMeterAxisCenter.y;

		pDC->Arc(&rc, ptBegin, ptEnd);
       // pDC->Arc(m_ptMeterAxisCenter.x-i, m_ptMeterAxisCenter.y-i,m_ptMeterAxisCenter.x+i,m_ptMeterAxisCenter.y+i,
         //   m_ptMeterAxisCenter.x-i,m_ptMeterAxisCenter.y,m_ptMeterAxisCenter.x-i,m_ptMeterAxisCenter.y);

        pDC->SelectObject(pPenOld);
    }
}

void CMeterAxis::SetColorTick(BOOL bColorTick)
{
    m_bColorTick = bColorTick;
}

void CMeterAxis::DrawValue(CDC *pDC)
{
    int nHeight;
    CPoint pttemp;
    CString strtemp;
    CFont *pFontOld;

    //  ��ֵ��ʾ
    nHeight = m_nRadiusFrame/8;
    pttemp = m_rectValue.CenterPoint();
    strtemp.Format("%.*lf", m_nValueDecimals, m_dCurrentValue);
    m_font.DeleteObject() ;

	LOGFONT oLogFont;
	oLogFont = InitLogFont ();
	oLogFont.lfHeight = nHeight;
	m_font.CreateFontIndirect(&oLogFont);

    pFontOld = pDC->SelectObject(&m_font);
    pDC->SetBkColor(m_colorButton);

	CRect rcText(0, 0, 0, 0), rcSize(0, 0, 0, 0);

	if (m_strUnits.GetLength() > 0)
	{
		pDC->DrawText(m_strUnits, &rcSize, DT_CALCRECT);
		rcText.left = pttemp.x;
		rcText.top = pttemp.y;
		rcText.bottom = rcText.top + rcSize.Height();
		rcText.right = rcText.left + rcSize.Width();
		CmDrawTextRect(pDC, strtemp, m_colorText, rcText, m_colorWindow, oLogFont, TRANSPARENT, DT_VCENTER | DT_CENTER, 0);
	}
    //pDC->SetTextAlign(TA_TOP|TA_CENTER);

	pDC->DrawText(strtemp, &rcSize, DT_CALCRECT);
	rcText.left = pttemp.x;
	rcText.top = pttemp.y+nHeight;
	rcText.bottom = rcText.top + rcSize.Height();
	rcText.right = rcText.left + rcSize.Width();
	CmDrawTextRect(pDC, strtemp, m_colorText, rcText, m_colorWindow, oLogFont, TRANSPARENT, DT_VCENTER | DT_CENTER, 0);

	//pDC->TextOut(pttemp.x, pttemp.y, m_strUnits);
   // pDC->TextOut(pttemp.x, pttemp.y+nHeight, strtemp);

    // �ָ�����ͱ���ɫ
    pDC->SelectObject(pFontOld);
    pDC->SetBkColor(m_colorWindow);
}

void CMeterAxis::SetTicks(int nTicks)
{
    m_nTicks = nTicks;
}

void CMeterAxis::SetSubTicks(int nSubTicks)
{
    m_nSubTicks = nSubTicks;
}

void CMeterAxis::SetAngleRange(int nStartAngleDeg, int nEndAngleDeg)
{
    m_fStartAngleDeg = nStartAngleDeg;
    m_fEndAngleDeg = nEndAngleDeg;
}

