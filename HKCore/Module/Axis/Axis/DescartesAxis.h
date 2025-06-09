#if !defined(AFX_DESCARTESAXIS_H__8710398B_FF86_4B12_AE1B_6C53534255FD__INCLUDED_)
#define AFX_DESCARTESAXIS_H__8710398B_FF86_4B12_AE1B_6C53534255FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DescartesAxis.h : header file
//

#include "..\..\Module\BaseObject\BaseObject.h"
#include "..\..\Module\Interface\AxisInterface.h"

#define pi  3.141592653579798

/////////////////////////////////////////////////////////////////////////////
// CDescartesAxis command target

class CDescartesAxis : public CCmdTarget
{
	DECLARE_DYNCREATE(CDescartesAxis)

	CDescartesAxis();           // protected constructor used by dynamic creation

// Attributes
public:
	int		m_iMinOneGapWidth;		//X������Ĵ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
	int		m_iMinOneGapHeight;		//Y������Ĵ�̶ȱ�ע֮��ļ���ռ�(�߶�)��Сֵ
	long	m_lAxisType;			//����������� 0����ͨ�����᣻  1��ʱ��������
	BOOL	m_bAxisXYUnitLock;		//X��Y���������ʾ����������־
	double	m_dAxisWorkMarginRatio;	//���깤����ͬ���е�ͼ�εı߾�

	//����������̶���
	long	m_lXAxisMaxUnitCount;
	long	m_lYAxisMaxUnitCount;
	
	double	m_fOneXGapValue;	///////X��ʵ��������ʵ��ֵ�ı���
	double	m_fOneYGapValue;	///////Y��ʵ��������ʵ��ֵ�ı���

	//////////////////////////////////////////////////////////////////////////
	//��������������
	//////////////////////////////////////////////////////////////////////////

	//������ķ�Χ�����ֵ����Сֵ
	double     m_dXAxisMinVal,m_dXAxisMaxVal;	//����X��====>>��ʼ��λ�ã�������λ��
	double    m_dYAxisMinVal,m_dYAxisMaxVal;	//����Y��====>>��ʾ��������ֵ����Сֵ,
	
	CRect   m_rectBorder;	//����������
	CRect   m_rectWorkArea;	//�����Ṥ������

	CPoint	m_ptCenterLogInDv;	////�߼������ԭ�����豸�����ϵ�����ֵ
	double	m_dOneYGapValue;		///////Y��ʵ��������ʵ��ֵ�ı���
	double	m_dOneXGapValue;		///////X��ʵ��������ʵ��ֵ�ı���
	
	//������Ľ�λ������λ��λ1��2��5��10
	double	m_dXCarryOneGap;	//X���λ
	double	m_dYCarryOneGap;	//Y���λ
	float	m_fCoefficient;		//ͼ�μ���ķŴ�ϵ����������Ļ�ߴ������˴�Ŀ���
	
	//��������������
	
	CRect   m_rectXAxis,m_rectYAxis;	//X��,Y������
	int		m_iLeftGap,m_iRightGap,m_iTopGap,m_iBottomGap;	//

	//X��,Y��ԭʼ��ʾ��������ֵ����Сֵ,���ڻָ�ԭͼ��
	double     m_dXAxisOldMinVal,m_dXAxisOldMaxVal;	//����X��====>>��ʼ��λ�ã�������λ��
	double     m_dYAxisOldMinVal,m_dYAxisOldMaxVal;	//����Y��====>>��ʾ��������ֵ����Сֵ,

	//////////////////////////////////////////////
	long    m_lAxisDrawStyle;	//��ʾ����
	long    m_lXAxisTextDrawStyle;	//X���ע����ģʽ��0=��ע�ڿ̶��ұߣ�1=��ע�ڿ̶��·�����
	
	LOGFONT   m_lfAxisTitleFont;	////��������������
	COLORREF  m_crAxisTitleFont;	////����������������ɫ
	CString	  m_strAxisTitle;		////���������

	COLORREF m_crAxisBackColor;
	//��������ص�ɫ����
	COLORREF m_crWorkAreaBkColor;
	COLORREF m_crWorkAreaBorderLeftTopColor;
	COLORREF m_crWorkAreaBorderRightBottomColor;
	int		 m_iWorkAreaBorderShadow;	//�������߽���Ӱ
	LOGBRUSH m_cBkGroundBrush;
	COLORREF m_crFrameLeftTopColor;
	COLORREF m_crFrameRightBottomColor;
	int		 m_iFrameShadow;	//�������߽���Ӱ
	int      ColorR;
	int      ColorG;
	void     DrawXYAxisRect(CDC *pDC,float fZoomRatio,CPoint ptOffset);
	
	
	///////////////////////////////
	//Y�������������
	COLORREF m_crYUnitScaleColor;	//��λ�̶���ɫ
	COLORREF m_crYUnitScaleShadowColor;//��λ�̶���Ӱ��ɫ
	LOGFONT   m_lfYAxisScaleFont;	////��ֱ�̶ȵ�����
	LOGFONT   m_lfYAxisNameFont;		////Y�����Ƶ�����
	COLORREF  m_crYAxisScaleFontColor;
	COLORREF  m_crYAxisNameFontColor;//��ɫ
	long      m_lYAxisGridLineStyle;	//Y������ɫ
	COLORREF  m_crYAxisGridLineColor;
	LOGPEN	  m_logpenYAxisGridLine;
	COLORREF  m_crYAxisTenthScale;	//1/10�̶Ȼ�����ɫ
	LOGPEN	  m_logpenYAxisTenthScale;	//1/10�̶Ȼ���
	int       m_iYAxisAreaWidth;	//Y����������Ŀ��
	int       m_iYAxisUnitScaleLineLen;	//Y�����굥λ�̶ȳ���
	int       m_iYAxisHalfScaleLineLen;	//Y������1/2�̶ȳ���
	int       m_iYAxisTenthScaleLineLen;	//Y������1/10�̶ȳ���
	
	//X�������������
	COLORREF m_crXUnitScaleColor;	//��λ�̶���ɫ
	COLORREF m_crXUnitScaleShadowColor;//��λ�̶���Ӱ��ɫ
	LOGFONT   m_lfXAxisScaleFont;	////��ֱ�̶ȵ�����
	LOGFONT   m_lfXAxisNameFont;		////Y�����Ƶ�����
	COLORREF  m_crXAxisScaleFontColor;
	COLORREF  m_crXAxisNameFontColor;//��ɫ
	long      m_lXAxisGridLineStyle;
	COLORREF  m_crXAxisGridLineColor;
	LOGPEN	  m_logpenXAxisGridLine;
	COLORREF  m_crXAxisTenthScale;	//1/10�̶Ȼ�����ɫ
	LOGPEN	  m_logpenXAxisTenthScale;	//1/10�̶Ȼ���
	int       m_iXAxisAreaHeight;	//X����������ĸ߶�
	int       m_iXAxisUnitScaleLineLen;	//X�����굥λ�̶ȳ���
	int       m_iXAxisHalfScaleLineLen;	//X������1/2�̶ȳ���
	int       m_iXAxisTenthScaleLineLen;	//X������1/10�̶ȳ���

	////////	�������������������
	long  m_lAxisCenterLineWidth;
	long  m_lAxisCenterLineType;
	COLORREF m_crAxisCenterColor;

	double m_dMaxZoomMultiple;	//���Ŵ���

	//X���������
	double		m_dXAxisOneGap;	//X��ĵ�λ�̶ȵĸ߶�
	CString		m_strXAxisName;	//
	CBaseObjectList       m_listXAxisScale;
	//Y���������
	double		m_dYAxisOneGap;	//Y��ĵ�λ�̶ȵĸ߶�
	CString		m_strYAxisName;	//
	CBaseObjectList       m_listYAxisScale;
	
	
// Operations
public:
	void InitAxis();
	void ContinueInitAxis();
	
	//////////////////////////////////////////////////////////////////////////
	//���Ե�Set��Get��������
	
	int		GetXAxisMinSawGapWidth();
	void	SetXAxisMinSawGapWidth(int iXAxisMinSawGapWidth);
	int		GetYAxisMinSawGapHeight();
	void	SetYAxisMinSawGapHeight(int iYAxisMinSawGapHeight);
	long	GetXAxisType();
	void	SetXAxisType(long lType);
	void SetXAxisMaxUnitCount(long lVal);
	long GetXAxisMaxUnitCount( );
	void SetYAxisMaxUnitCount(long lVal);
	long GetYAxisMaxUnitCount( );
	
	///////Add in 2005/7/28//////////
	void SetBorder(CRect rectBorder);
	CRect GetBorder();
	void SetAxisXYUnitLock(BOOL bXYUnitLock);
	BOOL GetAxisXYUnitLock();
	CRect GetXAxisArea();
	CRect GetYAxisArea();
	
	//////////////////////////////////////////////////////////////////////////
	//X Axis 
	void SetXYAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY);
	void GetXYAxisMinMaxVal(double &dMinX,double &dMinY,double &dMaxX,double &dMaxY);
	void SetXAxisTextDrawStyle(long lXAxisTextDrawStyle = 1);
	long GetXAxisTextDrawStyle();
	void SetAxisTitleFont(LOGFONT lf);
	LOGFONT GetAxisTitleFont();
	void SetAxisTitleFontColor(COLORREF color);
	COLORREF GetAxisTitleFontColor();
	void SetAxisTitle(CString strAxisTitle);
	CString GetAxisTitle();
	CRect GetWorkArea();
	void SetAxisBackColor(COLORREF color);
	COLORREF GetAxisBackColor();
	void SetWorkAreaBkColor(COLORREF color);
	COLORREF GetWorkAreaBkColor();
	void SetWorkAreaBorderLeftTopColor(COLORREF color);
	COLORREF GetWorkAreaBorderLeftTopColor();
	void SetWorkAreaBorderRightBottomColor(COLORREF color);
	COLORREF GetWorkAreaBorderRightBottomColor();
	void SetWorkAreaBorderShadow(long lWorkAreaBorderShadow);
	long GetWorkAreaBorderShadow();
	void SetFrameLeftTopColor(COLORREF color);
	COLORREF GetFrameLeftTopColor();
	void SetFrameRightBottomColor(COLORREF color);
	COLORREF GetFrameRightBottomColor();
	void SetFrameShadow(long lWorkAreaBorderShadow);
	long GetFrameShadow();
	
	//////////////////////////////////////////////////////////////////////////
	//Y Axis
	void SetYUnitScaleColor(COLORREF color);
	COLORREF GetYUnitScaleColor();
	void SetYUnitScaleShadowColor(COLORREF color);
	COLORREF GetYUnitScaleShadowColor();
	void SetYAxisScaleFont(LOGFONT lf);
	LOGFONT GetYAxisScaleFont();
	void SetYAxisNameFont(LOGFONT lf);
	LOGFONT GetYAxisNameFont();
	void SetYAxisScaleFontColor(COLORREF color);
	COLORREF GetYAxisScaleFontColor();
	void SetYAxisNameFontColor(COLORREF color);
	COLORREF GetYAxisNameFontColor();
	void SetYAxisGridLineStyle(long l);
	long GetYAxisGridLineStyle();
	void SetYAxisGridLineColor(COLORREF color);
	COLORREF GetYAxisGridLineColor();
	void SetYAxisTenthScaleColor(COLORREF color);
	COLORREF GetYAxisTenthScaleColor();
	void SetYAxisAreaWidth(long l);
	long GetYAxisAreaWidth();
	void SetYAxisUnitScaleLineLen(long l);
	long GetYAxisUnitScaleLineLen();
	void SetYAxisHalfScaleLineLen(long l);
	long GetYAxisHalfScaleLineLen();
	void SetYAxisTenthScaleLineLen(long l);
	long GetYAxisTenthScaleLineLen();

	//X Axis
	void SetXUnitScaleColor(COLORREF color);
	COLORREF GetXUnitScaleColor();
	void SetXUnitScaleShadowColor(COLORREF color);
	COLORREF GetXUnitScaleShadowColor();
	void SetXAxisScaleFont(LOGFONT lf);
	LOGFONT GetXAxisScaleFont();
	void SetXAxisNameFont(LOGFONT lf);
	LOGFONT GetXAxisNameFont();
	void SetXAxisScaleFontColor(COLORREF color);
	COLORREF GetXAxisScaleFontColor();
	void SetXAxisNameFontColor(COLORREF color);
	COLORREF GetXAxisNameFontColor();
	void SetXAxisGridLineStyle(long l);
	long GetXAxisGridLineStyle();
	void SetXAxisGridLineColor(COLORREF color);
	COLORREF GetXAxisGridLineColor();
	void SetXAxisTenthScaleColor(COLORREF color);
	COLORREF GetXAxisTenthScaleColr();
	void SetXAxisAreaHeight(long l);
	long GetXAxisAreaHeight();
	void SetXAxisUnitScaleLineLen(long l);
	long GetXAxisUnitScaleLineLen();
	void SetXAxisHalfScaleLineLen(long l);
	long GetXAxisHalfScaleLineLen();
	void SetXAxisTenthScaleLineLen(long l);
	long GetXAxisTenthScaleLineLen();

	//�������������������
	void SetAxisCenterLineWidth(long l);
	long GetAxisCenterLineWidth();
	void SetAxisCenterLineType(long l);
	long GetAxisCenterLineType();
	void SetAxisCenterColor(COLORREF color);
	COLORREF GetAxisCenterColor();
	
	//����ת��
	void	LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint);	//���߼�����ת��Ϊʵ������
	void	DevicePointToLogicPoint(CPoint point,double *fx,double *fy);//��ʵ�������ȡʵ�������������ֵ

	//����������ݼ���
	double GetFloatCarryVal(double fVal);
	double MakeFloatGapValLegal(double fVal,double &lVal);//float fVal,int &lVal
	
	long GetCarryVal(int iVal);
	int MakeGapValLegal(float fVal,int &lVal);

	///////////////////////////////////////*********************************************
	///////////////////���涨�� Y ����ص����ݼ�����
	void SetYAxisName(CString strYAxisName);
	CString GetYAxisName();

	void	InitAxisAttr();
	void InitYAxisDef();
	void ResetYAxisDef();
	
	void EndYAxisDef();
	void ResetOneYAxisDef(double lVal);
	void DrawYAxis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisText(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	long GetBaseOneGapHeight();
	long GetMinOneGapHeight();
	void DrawYSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void GetOneYAxisHeight(double iGap,BYTE);		////////modify in 05-30;;
	void DrawOneYSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneYSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisName(CDC*,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawAxisTitle(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
	///////////////////////////////////////*********************************************
	///////////////////���涨�� X ����ص����ݼ�����
	//++++++++++++++X �����ӿ�����
	void InitXAxisDef();
	void ResetXAxisDef();
	void SetXAxisName(CString strXAxisName);
	CString GetXAxisName();

	void EndXAxisDef();
	void ResetOneXAxisDef(double lVal);
	void DrawXAxis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	CString GetTimeVal(float fTimeVal);
	CRect DrawXAxisText(CDC *pDC,CAxisScaleData *pScaleData,BOOL b=FALSE,BOOL bDraw=TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	long GetBaseOneGapWidth();
	long GetMinOneGapWidth();
	long Get60CarryVal(int iVal);
	double GetBeginVal(double lNowVal,double lGapVal); /////modify in 05-30;;
	double GetXBeginVal(double lNowVal,double lGapVal);
	void DrawXSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void GetOneXAxisWidth(double iGap,BYTE);
	void DrawOneXSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneXSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisName(CDC*,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));

	//����ϵͳ��������
	BOOL MakeWorkAreaLegal(CRect &cNewRect);
	CRect GetDrawWorkAreaRect(float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawArea(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawWorkAreaBorder(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));//,cR,iGap,crLeftTop,crRightBottom);
	void DrawAxisBack(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void AdjustAxisDef(CRect rectArea,BOOL bAdjust = TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	BOOL AdjustAxisDef(double fMinX,double fMinY,double fMaxX,double fMaxY,BOOL bAdjust = TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));

	//��ͼ����
	void	DrawIt(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void	DrawFrame(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void	DrawAxisCenter(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void ModifyWorkArea(CRect* cRect,BOOL bInit,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));


public:
	//////////////////////////////////////////////////////////////////////////
	//����Ŵ���С���ƶ��ӿ�
	void ZoomIn(float fZoomIn=2.0f);
	void ZoomIn(double dMinX,double dMaxX,double dMinY,double dMaxY);
	void ZoomIn(CRect rectZoomIn);
	void ZoomIn(long lLeft,long lTop,long lRight,long lBottom);
	void ZoomIn(CPoint ptLeftTop,CPoint ptRightBottom);
	void ZoomOut(float fZoomOut=2.0f);

	void Move(float fXOffset=1,float fYOffset=1);

public:
	//��������ϵ�Ļ�ͼλ��
	virtual long GetAxisMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax);
	//��ȡ����ϵ�Ļ�ͼλ��
	virtual long GetPosition(long *left, long *top, long *right, long *bottom);
	//��ȡ����ϵͳ�Ĺ�������������ϵͳ���귶Χ��ʾ����Ч����
	virtual long GetWorkArea(long *left, long *top, long *right, long *bottom);
	//���߼�����ת��Ϊ�豸����:ptx,ptyΪ�豸����
	virtual long LogicPointToDevicePoint(double x,double y,long *ptx,long *pty);
	//���豸����ת��Ϊ�߼�����:ptx,ptyΪ�豸����
	virtual long DevicePointToLogicPoint (long ptx,long pty ,double *x,double *y);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDescartesAxis)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDescartesAxis();

	// Generated message map functions
	//{{AFX_MSG(CDescartesAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CDescartesAxis)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDescartesAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(DescartesAxisInterface,IDescartesAxisInterface)
		//X������Ĵ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
		STDMETHOD_(long,GetXAxisMinSawGapWidth)(long *nValue);
		STDMETHOD_(long,SetXAxisMinSawGapWidth)(long nValue);
		//Y������Ĵ�̶ȱ�ע֮��ļ���ռ�(�߶�)��Сֵ
		STDMETHOD_(long,GetYAxisMinSawGapHeight)(long *nValue);
		STDMETHOD_(long,SetYAxisMinSawGapHeight)(long nValue);
		//����������� 0����ͨ�����᣻  1��ʱ��������
		STDMETHOD_(long,GetXAxisType)(long *nValue);
		STDMETHOD_(long,SetXAxisType)(long nValue);
		//����������̶���
		STDMETHOD_(long,SetXAxisMaxUnitCount)(long nValue);
		STDMETHOD_(long,GetXAxisMaxUnitCount)(long *nValue);
		STDMETHOD_(long,SetYAxisMaxUnitCount)(long nValue);
		STDMETHOD_(long,GetYAxisMaxUnitCount)(long *nValue);
		//X��Y���������ʾ����������־
		STDMETHOD_(long,SetAxisXYUnitLock)(long nValue);
		STDMETHOD_(long,GetAxisXYUnitLock)(long *nValue);
		//����ϵͳ�Ļ�������,2005.08.12���
		STDMETHOD_(long,SetAxisDrawStyle)(long nValue);
		STDMETHOD_(long,GetAxisDrawStyle)(long *nValue);
		STDMETHOD_(long,SetAxisDrawStyleBit)(long nValue);
		STDMETHOD_(long,ClearAxisDrawStyleBit)(long nValue);
		
		//X���ע����ģʽ��0=��ע�ڿ̶��ұߣ�1=��ע�ڿ̶��·�����
		STDMETHOD_(long,SetXAxisTextDrawStyle)(long nValue);
		STDMETHOD_(long,GetXAxisTextDrawStyle)(long *nValue);
		//��������⼰�����塢��ɫ
		STDMETHOD_(long,SetAxisTitle)(BSTR bstrValue);
		STDMETHOD_(long,GetAxisTitle)(BSTR *pbstrValue);
		STDMETHOD_(long,SetAxisTitleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetAxisTitleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		STDMETHOD_(long,SetAxisTitleFontColor)(long nValue);
		STDMETHOD_(long,GetAxisTitleFontColor)(long *nValue);
		
		//����ϵͳ�ı���ɫ
		STDMETHOD_(long,SetAxisBackColor)(long nValue);
		STDMETHOD_(long,GetAxisBackColor)(long *nValue);
		//����ϵͳ��������ɫ
		STDMETHOD_(long,SetWorkAreaBkColor)(long nValue);
		STDMETHOD_(long,GetWorkAreaBkColor)(long *nValue);
		STDMETHOD_(long,SetWorkAreaBorderLeftTopColor)(long nValue);
		STDMETHOD_(long,GetWorkAreaBorderLeftTopColor)(long *nValue);
		STDMETHOD_(long,SetWorkAreaBorderRightBottomColor)(long nValue);
		STDMETHOD_(long,GetWorkAreaBorderRightBottomColor)(long *nValue);
		//�������߽���Ӱ
		STDMETHOD_(long,SetWorkAreaBorderShadow)(long nValue);
		STDMETHOD_(long,GetWorkAreaBorderShadow)(long *nValue);
		//����ϵͳ�߿����ɫ
		STDMETHOD_(long,SetFrameLeftTopColor)(long nValue);
		STDMETHOD_(long,GetFrameLeftTopColor)(long *nValue);
		STDMETHOD_(long,SetFrameRightBottomColor)(long nValue);
		STDMETHOD_(long,GetFrameRightBottomColor)(long *nValue);
		//����ϵͳ�߿�߽���Ӱ
		STDMETHOD_(long,SetFrameShadow)(long nValue);
		STDMETHOD_(long,GetFrameShadow)(long *nValue);
		
		//Y Axis
		//��λ�̶���ɫ
		STDMETHOD_(long,SetYUnitScaleColor)(long nValue);
		STDMETHOD_(long,GetYUnitScaleColor)(long *nValue);
		//��λ�̶���Ӱ��ɫ
		STDMETHOD_(long,SetYUnitScaleShadowColor)(long nValue);
		STDMETHOD_(long,GetYUnitScaleShadowColor)(long *nValue);
		//��ֱ�̶ȵ�����
		STDMETHOD_(long,SetYAxisScaleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetYAxisScaleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		//Y�����ơ����塢������ɫ
		STDMETHOD_(long,SetYAxisName)(BSTR bstrName);
		STDMETHOD_(long,GetYAxisName)(BSTR *pbstrName);
		//Y�����Ƶ�����
		STDMETHOD_(long,SetYAxisNameFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetYAxisNameFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		//Y������������ɫ
		STDMETHOD_(long,SetYAxisNameFontColor)(long nValue);
		STDMETHOD_(long,GetYAxisNameFontColor)(long *nValue);
		//Y��̶�������ɫ
		STDMETHOD_(long,SetYAxisScaleFontColor)(long nValue);
		STDMETHOD_(long,GetYAxisScaleFontColor)(long *nValue);
		//Y���������͡���ɫ
		STDMETHOD_(long,SetYAxisGridLineStyle)(long nValue);
		STDMETHOD_(long,GetYAxisGridLineStyle)(long *nValue);
		STDMETHOD_(long,SetYAxisGridLineColor)(long nValue);
		STDMETHOD_(long,GetYAxisGridLineColor)(long *nValue);
		//1/10�̶Ȼ�����ɫ
		STDMETHOD_(long,SetYAxisTenthScaleColor)(long nValue);
		STDMETHOD_(long,GetYAxisTenthScaleColor)(long *nValue);
		//Y����������Ŀ��
		STDMETHOD_(long,SetYAxisAreaWidth)(long nValue);
		STDMETHOD_(long,GetYAxisAreaWidth)(long *nValue);
		//Y�����굥λ�̶ȳ���
		STDMETHOD_(long,SetYAxisUnitScaleLineLen)(long nValue);
		STDMETHOD_(long,GetYAxisUnitScaleLineLen)(long *nValue);
		//Y������1/2�̶ȳ���
		STDMETHOD_(long,SetYAxisHalfScaleLineLen)(long nValue);
		STDMETHOD_(long,GetYAxisHalfScaleLineLen)(long *nValue);
		////Y������1/10�̶ȳ���
		STDMETHOD_(long,SetYAxisTenthScaleLineLen)(long nValue);
		STDMETHOD_(long,GetYAxisTenthScaleLineLen)(long *nValue);

		//X Axis
		//��λ�̶���ɫ
		STDMETHOD_(long,SetXUnitScaleColor)(long nValue);
		STDMETHOD_(long,GetXUnitScaleColor)(long *nValue);
		//��λ�̶���Ӱ��ɫ
		STDMETHOD_(long,SetXUnitScaleShadowColor)(long nValue);
		STDMETHOD_(long,GetXUnitScaleShadowColor)(long *nValue);
		//��ֱ�̶ȵ�����
		STDMETHOD_(long,SetXAxisScaleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetXAxisScaleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		//X�����ơ����塢������ɫ
		STDMETHOD_(long,SetXAxisName)(BSTR bstrName);
		STDMETHOD_(long,GetXAxisName)(BSTR *pbstrName);
		//X�����Ƶ�����
		STDMETHOD_(long,SetXAxisNameFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
		STDMETHOD_(long,GetXAxisNameFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
		//X������������ɫ
		STDMETHOD_(long,SetXAxisNameFontColor)(long nValue);
		STDMETHOD_(long,GetXAxisNameFontColor)(long *nValue);
		//X��̶�������ɫ
		STDMETHOD_(long,SetXAxisScaleFontColor)(long nValue);
		STDMETHOD_(long,GetXAxisScaleFontColor)(long *nValue);
		//X���������͡���ɫ
		STDMETHOD_(long,SetXAxisGridLineStyle)(long nValue);
		STDMETHOD_(long,GetXAxisGridLineStyle)(long *nValue);
		STDMETHOD_(long,SetXAxisGridLineColor)(long nValue);
		STDMETHOD_(long,GetXAxisGridLineColor)(long *nValue);
		//1/10�̶Ȼ�����ɫ
		STDMETHOD_(long,SetXAxisTenthScaleColor)(long nValue);
		STDMETHOD_(long,GetXAxisTenthScaleColor)(long *nValue);
		//X����������Ŀ��
		STDMETHOD_(long,SetXAxisAreaHeight)(long nValue);
		STDMETHOD_(long,GetXAxisAreaHeight)(long *nValue);
		//X�����굥λ�̶ȳ���
		STDMETHOD_(long,SetXAxisUnitScaleLineLen)(long nValue);
		STDMETHOD_(long,GetXAxisUnitScaleLineLen)(long *nValue);
		//X������1/2�̶ȳ���
		STDMETHOD_(long,SetXAxisHalfScaleLineLen)(long nValue);
		STDMETHOD_(long,GetXAxisHalfScaleLineLen)(long *nValue);
		////X������1/10�̶ȳ���
		STDMETHOD_(long,SetXAxisTenthScaleLineLen)(long nValue);
		STDMETHOD_(long,GetXAxisTenthScaleLineLen)(long *nValue);
		
		//�������������������
		STDMETHOD_(long,SetAxisCenterLineWidth)(long nValue);
		STDMETHOD_(long,GetAxisCenterLineWidth)(long *nValue);
		STDMETHOD_(long,SetAxisCenterLineType)(long nValue);
		STDMETHOD_(long,GetAxisCenterLineType)(long *nValue);
		STDMETHOD_(long,SetAxisCenterColor)(long nValue);
		STDMETHOD_(long,GetAxisCenterColor)(long *nValue);
		
		//�߼��������豸����֮���ת��
		STDMETHOD_(long,LogicPointToDevicePoint)(double x,double y,long *ptx,long *pty);
		STDMETHOD_(long,DevicePointToLogicPoint)(long ptx,long pty ,double *x,double *y);
		
		//���귶Χ
		STDMETHOD_(long,SetMinMaxVal)(double xMin,double yMin,double xMax,double yMax,long nReserved);
		STDMETHOD_(long,GetMinMaxVal)(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved);
		
		//��������
		STDMETHOD_(long,SetBoder)(long left, long top, long right, long bottom);
		STDMETHOD_(long,GetBoder)(long *left, long *top, long *right, long *bottom);
		STDMETHOD_(long,GetWorkArea)(long *left, long *top, long *right, long *bottom);
		STDMETHOD_(long,GetXAxisArea)(long *left, long *top, long *right, long *bottom);
		STDMETHOD_(long,GetYAxisArea)(long *left, long *top, long *right, long *bottom);
		
		//���¼�������ϵͳ�Ŀ̶�
		STDMETHOD_(long,ResetAxis)();

		//��ͼ
		STDMETHOD_(long,DrawAxis)(long lDC,float fZoomRatio,long xOffset,long yOffset);

		//�Ŵ���С
		STDMETHOD_(long,ZoomIn1)(float fRate);
		STDMETHOD_(long,ZoomIn2)(double dMinX,double dMaxX,double dMinY,double dMaxY);
		STDMETHOD_(long,ZoomIn3)(long left,long top,long right,long bottom);
		STDMETHOD_(long,ZoomOut)(float fRate);
		STDMETHOD_(long,Move)(float fXOffset,float fYOffset);

	
	END_INTERFACE_PART(DescartesAxisInterface)

BEGIN_INTERFACE_PART(AxisBaseInterface,IAxisBaseInterface)
	//��������
	STDMETHOD_(long,GetBoder)(long *left, long *top, long *right, long *bottom);
	STDMETHOD_(long,GetWorkArea)(long *left, long *top, long *right, long *bottom);
	//�߼��������豸����֮���ת��
	STDMETHOD_(long,LogicPointToDevicePoint)(double x,double y,long *ptx,long *pty);
	STDMETHOD_(long,DevicePointToLogicPoint)(long ptx,long pty ,double *x,double *y);
	//���귶Χ
	STDMETHOD_(long,GetMinMaxVal)(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved);
	
END_INTERFACE_PART(AxisBaseInterface)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESCARTESAXIS_H__8710398B_FF86_4B12_AE1B_6C53534255FD__INCLUDED_)
