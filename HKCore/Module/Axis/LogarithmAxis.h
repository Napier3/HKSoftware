#if !defined(AFX_LOGARITHMAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_)
#define AFX_LOGARITHMAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogarithmAxis.h : header file

#include "AxisInterface.h"

#define LOGARITHM_XAXIS_LLINE			0x00000010
#define LOGARITHM_YAXIS_LLINE			0x00000020

#define LOGARITHM_AREA				0x0001


#define LOGARITHM_ALL				0x07fffffff
#define LOGARITHM_XAXIS				0x0002
#define LOGARITHM_XAXIS_LINE			0x00010000
#define LOGARITHM_XAXIS_TEXT			0x00020000
#define LOGARITHM_XAXIS_SAWTOOTH1	0x00040000
#define LOGARITHM_XAXIS_SAWTOOTH2	0x00080000
#define LOGARITHM_XAXIS_ALL			0x000F0002

#define LOGARITHM_YAXIS				0x0004
#define LOGARITHM_YAXIS_LINE			0x00100000
#define LOGARITHM_YAXIS_TEXT			0x00200000
#define LOGARITHM_YAXIS_SAWTOOTH1	0x00400000
#define LOGARITHM_YAXIS_SAWTOOTH2	0x00800000
#define LOGARITHM_YAXIS_ALL			0x00F00004

#define LOGARITHM_AXISCENTER			0X00000100

#define LOGARITHM_CIRCLE				0X00001000	//�Ƿ����Բ�̶�
#define LOGARITHM_BIASlINE			0X00002000	//�Ƿ����б�߿̶�

#define POWERADVANE_PI		3.14159265

/////////////////////////////////////////////////////////////////////////////
// CLogarithmAxis command target

class CLogarithmAxis : public CAxisInterface
{
public:
	CLogarithmAxis();           // protected constructor used by dynamic creation
	virtual ~CLogarithmAxis();

// Operations
public:
	//����ת��
	virtual void	LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint, long nAxisIndex=0);	//���߼�����ת��Ϊʵ������
	virtual void	DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0);//��ʵ�������ȡʵ�������������ֵ
    virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex=0);
    virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex=0);
    virtual void GetAxisDrawArea(CRect &rcArea);
	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
	virtual void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);//zhouhj 20210130 ���������������������Ƶ�
	virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);

#ifdef USE_AXIS_CONFIG
	virtual void SetAxisConfig(CDataGroup *pAxisConfig);//zhouhj 20211026 ������������������
	virtual void GetAxisConfig(CDataGroup *pAxisConfig);
	void SetAxisConfig(CDvmData *pAxisData);
#endif

public:
	COLORREF	m_crAxisGrid;				//���������		
	COLORREF	m_crAxisCenter;				//�������������ɫ
	COLORREF	m_crAxisBK;					//����ı���
	COLORREF	m_crZoneLine;				//��������ɫ
	COLORREF	m_crTestTitle;				//������Ŀ�ı�����ɫ
	COLORREF	m_crViewBK;					//��ͼ��ɫ
	long		m_lAxisGridLineType;		//���������ߵ�����
	CRect	m_rectAxis;			//����ϵ��λ��
// 	float	m_fAxisValue[4];		//��������ķ�Χ	0-3���ѿ������ꣻ4-7��������
	long    m_lAxisDrawStyle;

	long m_lAxisType;			//�����������
	BOOL m_bAxisXYUnitLock;
	long m_lXAxisMaxUnitCount;
	long m_lYAxisMaxUnitCount;

	LOGFONT   m_lfAxisTitleFont;	////��������������
	COLORREF  m_crAxisTitleFont;	////����������������ɫ
	CString	  m_strAxisTitle;		////���������

	COLORREF m_crAxisBackColor;

	COLORREF m_crFrameLeftTopColor;
	COLORREF m_crFrameRightBottomColor;
	int		 m_iFrameShadow;	//�������߽���Ӱ

	double m_dMaxZoomMultiple;	//���Ŵ���
	double	m_dAxisWorkMarginRatio;	//���깤����ͬ���е�ͼ�εı߾�
	
	//////////���涨�� Y ����ص����ݼ�����
	CAxisScaleDataList       m_oYAxisDef;
	float					m_nYAxisOneGap;
	CString				m_strYAxisName;
	void InitYAxisDef();
	void EndYAxisDef();
	void ResetYAxisDef();
	void ResetOneYAxisDef(float lVal);
	void DrawYAxis(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisText(CDC *cDC,CAxisScaleData *odData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void SetYAxisTenthScaleColor(COLORREF color);
	COLORREF GetYAxisTenthScaleColor();
	void SetXAxisTenthScaleColor(COLORREF color);
	COLORREF GetXAxisTenthScaleColr();
	void GetOneYAxisHeight(float iGap,BYTE);		
	void DrawOneYSawtooth(CDC *cDC,	CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneYSawtoothShadow(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisName(CDC*cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawAxisTitle(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
	///////////////////////////////////////*********************************************
	///////////////////���涨�� X ����ص����ݼ�����
	CAxisScaleDataList   m_oXAxisDef;
	float				m_fXAxisOneGap;
	CString				m_strXAxisName;
	void InitXAxisDef();
	void EndXAxisDef();
	void ResetXAxisDef();
	void ResetOneXAxisDef(float lVal,BYTE);
	void DrawXAxis(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisLine(CDC *cDC,CAxisScaleData *odData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	CRect DrawXAxisText(CDC *cDC,CAxisScaleData *odData,BOOL b=FALSE,BOOL bDraw=TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	float GetBeginVal(float lNowVal,float lGapVal); /////modify in 05-30;;
	float GetXBeginVal(float lNowVal,float lGapVal);
	void DrawXSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void GetOneXAxisWidth(float iGap,BYTE);
	void DrawOneXSawtooth(CDC *cDC,	CPoint cBegin,CPoint cEnd,float fCarryVal=1.0,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneXSawtoothShadow(CDC *cDC,CPoint cBegin,CPoint cEnd,float fCarryVal=1.0,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisName(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
// 	void LogicPointToDevicePoint(float fx,float fy,CPoint *pPoint);	//���߼�����ת��Ϊʵ������
// 	void DevicePointToLogicPoint(CPoint point,double *fx,double *fy);//��ʵ�������ȡʵ�������������ֵ
	
	void DrawIt(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawFrame(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));	
	void ModifyWorkArea(CRect* pRect, BOOL bInit,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	BOOL MakeWorkAreaLegal(CRect &cNewRect);
	void SetAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY);
	long GetAxisMinMaxVal(double *dMinX,double *dMinY,double *dMaxX,double *dMaxY);
	void SetBorder(const CRect &rectBorder);
	void ResetAxis();
	void InitAxisAttr();
	//////
	CRect GetDrawWorkAreaRect();
	void DrawArea(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawAxisBack(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawWorkAreaBorder(CDC *pDC);//,cR,iGap,crLeftTop,crRightBottom);

	void ZoomIn(float fZoomIn=2.0f);
	void ZoomIn(double dMinX,double dMaxX,double dMinY,double dMaxY);
	void ZoomIn(long lLeft,long lTop,long lRight,long lBottom);	
	void ZoomOut(float fZoomOut=2.0f);	
	void Move(float fXOffset=1,float fYOffset=1);

//////////////////////////ADD at 0908//////////////////////////////
//////////////////////////DrawPara/////////////////////////////////
public:
	DWORD    m_dwDisplayType;//��ʾ����
	DWORD    m_dwDrawXAxisTextType;
	int		m_nZoomCoef;
	
public:
	int m_iLeftGap,m_iRightGap,m_iTopGap,m_iBottomGap;
	//WorkArea Bk
	COLORREF m_crBkGroundColor,m_crBkLeftTopColor,m_crBkRightBottomColor;
	LOGBRUSH m_cBkGroundBrush;
	int		 m_iShadow;
	///////////////////////////////
	//VertDef
	LOGFONT   m_lfVertFont,m_lfVertTitleFont;////��ֱ�̶ȼ�Y�����Ƶ�����
	COLORREF  m_crVertColor,m_crVertTitleColor;//��ɫ
	long      m_lVertLineStyle;
	COLORREF  m_crVert_WorkAreaLine_Color;
	LOGPEN	  m_penVert_WorkAreaLine,m_penVert_WorkAreaShortLine;;
	int       m_iVertAreaWidth;
	int       m_iVertGapLineLen1,m_iVertGapLineLen2,m_iVertGapLineLen3;
	
	COLORREF  m_crYTenthScaleColor;
	COLORREF  m_crYUnitScaleColor,m_crYUnitScaleShadowColor;
	//HorzDef
	LOGFONT   m_lfHorzFont,m_lfHorzTitleFont;
	COLORREF  m_crHorzColor,m_crHorzTitleColor;
	long      m_lHorzLineStyle;
	COLORREF  m_crHorz_WorkAreaLine_Color;
	LOGPEN	  m_penHorz_WorkAreaLine,m_penHorz_WorkAreaShortLine;
	int       m_iHorzAreaWidth;
	int       m_iHorzGapLineLen1,m_iHorzGapLineLen2,m_iHorzGapLineLen3;
	
	COLORREF  m_crXTenthScaleColor;
	COLORREF  m_crXUnitScaleColor,m_crXUnitScaleShadowColor;
	//Cursor Area Def
	LOGPEN    m_penCursor;
	LOGPEN	  m_penChoiceArea;
	LOGBRUSH  m_brushChoiceArea;
	
	///б�߿̶ȡ�Բ�̶ȵ����ݶ���
	COLORREF	m_crCircleScale,m_crBiaslineScale;
	long	m_lCircleLineType,m_lBiasLineType;
	LOGPEN		m_penCircleScale,m_penBiaslineScale;
	float		m_fCircleScaleOffset,m_fBiaslineScaleOffset;	//Բ�̶ȵİ뾶λ�ơ�б�߿̶ȵĽǶ�λ��
	
	////////	�������������������
	long  m_lAxisCenterLineWidth;
	long  m_lAxisCenterLineType;
	//	LOGPEN   logpenAxisCenter;
public:	
	void InitIt();
	void ContinueInit();

///////////////////////////////RestoreData///////////////////////////
public:
	int		m_iXMultipleCoeff,m_iYMultipleCoeff;		////ͼ�ηŴ�ı���		�߼�ֵ / �豸ֵ
	int		m_iXMaxMultipleCoeff,m_iYMaxMultipleCoeff;		////ͼ�ηŴ�ı���		�߼�ֵ / �豸ֵ
	int		m_iXMinMultipleCoeff,m_iYMinMultipleCoeff;		////ͼ�ηŴ�ı���		�߼�ֵ / �豸ֵ
	CPoint	m_ptCenterLogInDv;	////�߼������ԭ�����豸�����ϵ�����ֵ
	float	m_fOneYGapValue;		///////Y��ʵ��������ʵ��ֵ�ı���
	float	m_fOneXGapValue;		///////X��ʵ��������ʵ��ֵ�ı���
	
	float	m_fXCarryOneGap;
	float	m_fYCarryOneGap;
	
public:
	//	BYTE	bOnlyDisplayIntegeralArea;
	CRect   m_rcBorder;
	CRect   m_rcWorkArea;//��������
	CRect   m_rcX_Axis,m_rcY_Axis;//X��,Y���ע����
	
	int     m_iDataMinVal,m_iDataMaxVal;//�������ֵ����Сֵ
	float     m_iDisplayMinVal,m_iDisplayMaxVal;//����Y��====>>��ʾ��������ֵ����Сֵ,
	float     m_iBeginPalace,m_iEndPalace;//����X��====>>��ʼ��λ�ã�������λ��
	int		m_iDirection;//����
	/////////////���涨���¼X��,Y��ԭʼ��ʾ��������ֵ����Сֵ,���ڻָ�ԭͼ��
	float     m_iOldBeginPalace,m_iOldEndPalace;//����X��====>>��ʼ��λ�ã�������λ��
	float     m_iOldDisplayMinVal,m_iOldDisplayMaxVal;//����Y��====>>��ʾ��������ֵ����Сֵ,
	//////////////////////////////////////////////
	int		m_iMinValueXAxis,m_iMaxValueXAxis;/////// X Axis max and min value.....
	long GetDataMaxVal();
	long GetDataMinVal();
	virtual const CLogarithmAxis & operator =(CLogarithmAxis &odTemp);

// Operations
public:

// Implementation
public:
		//X������Ĵ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
		long GetXAxisMinSawGapWidth(long *nValue);
		long SetXAxisMinSawGapWidth(long nValue);
		//Y������Ĵ�̶ȱ�ע֮��ļ���ռ�(�߶�)��Сֵ
		long GetYAxisMinSawGapHeight(long *nValue);
		long SetYAxisMinSawGapHeight(long nValue);
		//����������� 0����ͨ�����᣻  1��ʱ��������
		long GetXAxisType(long *nValue);
		long SetXAxisType(long nValue);
		//����������̶���
		long SetXAxisMaxUnitCount(long nValue);
		long GetXAxisMaxUnitCount(long *nValue);
		long SetYAxisMaxUnitCount(long nValue);
		long GetYAxisMaxUnitCount(long *nValue);
		//X��Y���������ʾ����������־
		long SetAxisXYUnitLock(long nValue);
		long GetAxisXYUnitLock(long *nValue);
		//����ϵͳ�Ļ�������,2005.08.12���
		long SetAxisDrawStyle(long nValue);
		long GetAxisDrawStyle(long *nValue);
		long SetAxisDrawStyleBit(long nValue);
		long ClearAxisDrawStyleBit(long nValue);
		
		//X���ע����ģʽ��0=��ע�ڿ̶��ұߣ�1=��ע�ڿ̶��·�����
		long SetXAxisTextDrawStyle(long nValue);
		long GetXAxisTextDrawStyle(long *nValue);
		//��������⼰�����塢��ɫ
		long SetAxisTitle(const CString & bstrValue);
		long GetAxisTitle(CString *pbstrValue);
		long SetAxisTitleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName);
		long GetAxisTitleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName);
		long SetAxisTitleFontColor(long nValue);
		long GetAxisTitleFontColor(long *nValue);
		
		//����ϵͳ�ı���ɫ
		long SetAxisBackColor(long nValue);
		long GetAxisBackColor(long *nValue);
		//����ϵͳ��������ɫ
		long SetWorkAreaBkColor(long nValue);
		long GetWorkAreaBkColor(long *nValue);
		long SetWorkAreaBorderLeftTopColor(long nValue);
		long GetWorkAreaBorderLeftTopColor(long *nValue);
		long SetWorkAreaBorderRightBottomColor(long nValue);
		long GetWorkAreaBorderRightBottomColor(long *nValue);
		//�������߽���Ӱ
		long SetWorkAreaBorderShadow(long nValue);
		long GetWorkAreaBorderShadow(long *nValue);
		//����ϵͳ�߿����ɫ
		long SetFrameLeftTopColor(long nValue);
		long GetFrameLeftTopColor(long *nValue);
		long SetFrameRightBottomColor(long nValue);
		long GetFrameRightBottomColor(long *nValue);
		//����ϵͳ�߿�߽���Ӱ
		long SetFrameShadow(long nValue);
		long GetFrameShadow(long *nValue);
		
		//Y Axis
		//��λ�̶���ɫ
		long SetYUnitScaleColor(long nValue);
		long GetYUnitScaleColor(long *nValue);
		//��λ�̶���Ӱ��ɫ
		long SetYUnitScaleShadowColor(long nValue);
		long GetYUnitScaleShadowColor(long *nValue);
		//��ֱ�̶ȵ�����
		long SetYAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName);
		long GetYAxisScaleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName);
		//Y�����ơ����塢������ɫ
		long SetYAxisName(const CString & bstrName);
		long GetYAxisName(CString *pbstrName);
		//Y�����Ƶ�����
		long SetYAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName);
		long GetYAxisNameFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName);
		//Y������������ɫ
		long SetYAxisNameFontColor(long nValue);
		long GetYAxisNameFontColor(long *nValue);
		//Y��̶�������ɫ
		long SetYAxisScaleFontColor(long nValue);
		long GetYAxisScaleFontColor(long *nValue);
		//Y���������͡���ɫ
		long SetYAxisGridLineStyle(long nValue);
		long GetYAxisGridLineStyle(long *nValue);
		long SetYAxisGridLineColor(long nValue);
		long GetYAxisGridLineColor(long *nValue);
		//1/10�̶Ȼ�����ɫ
		long SetYAxisTenthScaleColor(long nValue);
		long GetYAxisTenthScaleColor(long *nValue);
		//Y����������Ŀ��
		long SetYAxisAreaWidth(long nValue);
		long GetYAxisAreaWidth(long *nValue);
		//Y�����굥λ�̶ȳ���
		long SetYAxisUnitScaleLineLen(long nValue);
		long GetYAxisUnitScaleLineLen(long *nValue);
		//Y������1/2�̶ȳ���
		long SetYAxisHalfScaleLineLen(long nValue);
		long GetYAxisHalfScaleLineLen(long *nValue);
		////Y������1/10�̶ȳ���
		long SetYAxisTenthScaleLineLen(long nValue);
		long GetYAxisTenthScaleLineLen(long *nValue);

		//X Axis
		//��λ�̶���ɫ
		long SetXUnitScaleColor(long nValue);
		long GetXUnitScaleColor(long *nValue);
		//��λ�̶���Ӱ��ɫ
		long SetXUnitScaleShadowColor(long nValue);
		long GetXUnitScaleShadowColor(long *nValue);
		//��ֱ�̶ȵ�����
		long SetXAxisScaleFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName);
		long GetXAxisScaleFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName);
		//X�����ơ����塢������ɫ
		long SetXAxisName(const CString & bstrName);
		long GetXAxisName(CString *pbstrName);
		//X�����Ƶ�����
		long SetXAxisNameFont(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,const CString & lfFaceName);
		long GetXAxisNameFont(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,CString *lfFaceName);
		//X������������ɫ
		long SetXAxisNameFontColor(long nValue);
		long GetXAxisNameFontColor(long *nValue);
		//X��̶�������ɫ
		long SetXAxisScaleFontColor(long nValue);
		long GetXAxisScaleFontColor(long *nValue);
		//X���������͡���ɫ
		long SetXAxisGridLineStyle(long nValue);
		long GetXAxisGridLineStyle(long *nValue);
		long SetXAxisGridLineColor(long nValue);
		long GetXAxisGridLineColor(long *nValue);
		//1/10�̶Ȼ�����ɫ
		long SetXAxisTenthScaleColor(long nValue);
		long GetXAxisTenthScaleColor(long *nValue);
		//X����������Ŀ��
		long SetXAxisAreaHeight(long nValue);
		long GetXAxisAreaHeight(long *nValue);
		//X�����굥λ�̶ȳ���
		long SetXAxisUnitScaleLineLen(long nValue);
		long GetXAxisUnitScaleLineLen(long *nValue);
		//X������1/2�̶ȳ���
		long SetXAxisHalfScaleLineLen(long nValue);
		long GetXAxisHalfScaleLineLen(long *nValue);
		////X������1/10�̶ȳ���
		long SetXAxisTenthScaleLineLen(long nValue);
		long GetXAxisTenthScaleLineLen(long *nValue);
		
		//�������������������
		long SetAxisCenterLineWidth(long nValue);
		long GetAxisCenterLineWidth(long *nValue);
		long SetAxisCenterLineType(long nValue);
		long GetAxisCenterLineType(long *nValue);
		long SetAxisCenterColor(long nValue);
		long GetAxisCenterColor(long *nValue);
		
		//�߼��������豸����֮���ת��
		long LogicPointToDevicePoint(double x,double y,long *ptx,long *pty);
		long DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y);
		
		//���귶Χ
		long SetMinMaxVal(double xMin,double yMin,double xMax,double yMax,long nReserved);
		long GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved);
		
		//��������
		long SetBoder(long left, long top, long right, long bottom);
		long GetBoder(long *left, long *top, long *right, long *bottom);
		long GetWorkArea(long *left, long *top, long *right, long *bottom);
		virtual CRect GetWorkArea();
		long GetXAxisArea(long *left, long *top, long *right, long *bottom);
		long GetYAxisArea(long *left, long *top, long *right, long *bottom);
		
		//��ͼ
		long DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset);

		//�Ŵ���С
		long ZoomIn1(float fRate);
		long ZoomIn2(double dMinX,double dMaxX,double dMinY,double dMaxY);
		long ZoomIn3(long left,long top,long right,long bottom);

		//��������
		//long GetBoder(long *left, long *top, long *right, long *bottom);
		//long GetWorkArea(long *left, long *top, long *right, long *bottom);
		//�߼��������豸����֮���ת��
		//long LogicPointToDevicePoint(double x,double y,long *ptx,long *pty);
		//long DevicePointToLogicPoint(long ptx,long pty ,double *x,double *y);
		//���귶Χ
		//long GetMinMaxVal(double *xMin,double *yMin,double *xMax,double *yMax,long nReserved);
};

#endif // !defined(AFX_LOGARITHMAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_)
