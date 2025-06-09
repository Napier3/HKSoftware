#if !defined(_MeterAxis_H__)
#define _MeterAxis_H__

#include "AxisInterface.h"

// MeterAxis.h : header file
//

#define METER_TABNUM 6
#define METER_PT_NUM 50
#define METER_BOUNDARY_POINTS 200

/////////////////////////////////////////////////////////////////////////////
// CMeterAxis
class CMeterAxis
{
// Construction
public:
    CMeterAxis();
	virtual ~CMeterAxis();

// Attributes
public:

// Operations
public:
	void DrawMeter(CDC *pDC);
	void DrawMeterBack(CDC *pDC);
	void DrawValue(CDC *pDC);

	void SetBoder(const CRect &rc);
	void SetBoder(long x, long y, long cx, long cy);
	void CalWorkArea();

// Implementation
public:
    void SetAngleRange(int nStartAngleDeg, int nEndAngleDeg);
	void SetSubTicks(int nSubTicks);
	void SetTicks(int nTicks);
	void SetUnits(CString &strUnits);
	void SetColorTick(BOOL bColorTick = FALSE);
	void SetValueDecimals(int nDecimals);
	void SetScaleDecimals(int nDecimals);
	void SetRange(double dMin, double dMax);
	void SetNeedleColor (COLORREF colorNeedle);
 
	void SetColorWindow(COLORREF cr)	{	m_colorWindow = cr;	}
	void SetColorTable(long nIndex, COLORREF cr)	{	m_colorTable[nIndex] = cr;	}
	void SetDrawTicks(BOOL b)	{	m_nDrawTicks = b;	}
	void SetDrawBackground(BOOL b)	{	m_bDrawBackground = b;	}
	void SetValue(double dVal)	{	m_dCurrentValue = dVal;	}
	double GetValue(){return m_dCurrentValue;}

protected:
	void DrawNode(CDC *pDC);
	void DrawMeterBackground(CDC *pDC);

	int m_nTabNum;
    BOOL m_bColorTick;
	BOOL m_bFrameGradient;
    COLORREF m_colorTable[6];
    CString m_strUnits;
    int m_nValueDecimals;
    void UpdateNeedle(double dValue);
    COLORREF m_colorNeedle;
    int m_nScaleDecimals;

    double m_dCurrentValue;
    double m_dMaxValue;
    double m_dMinValue;

    void DrawNeedle(CDC *pDC);
    double m_fStartAngleDeg;    // �Ǳ���Բ����ʼ�Ƕ�
    double m_fEndAngleDeg;        // �Ǳ���Բ����ֹ�Ƕ�
    int m_nTicks;            // �̶���
    BOOL m_nDrawTicks;            // �̶���
    int m_nSubTicks;        // �̶ֿ���
	BOOL m_bDrawBackground;

protected:
    double m_dLeftAngleRad;
    double m_dRightAngleRad;
    int m_nCenterRadius;

    CRect m_rectCtrl;            // �ؼ�����
	CRect m_rectWorkArea;   //��������
    CRect m_rectValue;            // ��ʾ��ֵ����

#ifndef _PSX_IDE_QT_
    CRgn m_rgnBoundary;
#endif

    CPoint m_ptMeterAxisCenter;        // �Ǳ�����
    CPoint m_pointBoundary[METER_BOUNDARY_POINTS]; // �߽�㣬���ڻ��ƿ̶�

    CFont m_font;            // ��ʾ��������

    COLORREF m_colorWindow;        // ����ɫ
    COLORREF m_colorHighlight;
    COLORREF m_colorShadow;
    COLORREF m_colorButton;
    COLORREF m_colorText;        // ��ʾ�ı���ɫ

    int m_nRadiusFrame;            // �Ǳ��̱߿�뾶
	CRect m_rectPanel,m_rectInnerPanel;
	CPoint m_pointInner[METER_BOUNDARY_POINTS], m_ptGroup1[METER_PT_NUM*METER_TABNUM+1], m_ptGroup2[METER_PT_NUM*METER_TABNUM+1];
	CPoint m_ptInnerStart, m_ptInnerEnd, m_ptStart, m_ptEnd;
	long  m_nScaleCount;
	int m_nFrameWidth;

protected:
	void CalcMexterAxisDraw();
};

#endif // !defined(_MeterAxis_H__)

