#if !defined(AFX_LOGARITHMAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_)
#define AFX_LOGARITHMAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogarithmAxis.h : header file
//
//#include "PowerAdvanceDrawPara.h"
//#include "PowerAdvanceRestoreData.h"
#include "..\..\Module\Interface\AxisInterface.h"
#include "..\..\Module\BaseObject\BaseObject.h"
#include "AxisScaleData.h"

#define LOGARITHM_XAXIS_LLINE			0x00000010
#define LOGARITHM_YAXIS_LLINE			0x00000020

#define POWERADVANCE_AREA				0x0001

#define POWERADVANCE_ALL				0x07fffffff
#define POWERADVANCE_XAXIS				0x0002
#define POWERADVANCE_XAXIS_LINE			0x00010000
#define POWERADVANCE_XAXIS_TEXT			0x00020000
#define POWERADVANCE_XAXIS_SAWTOOTH1	0x00040000
#define POWERADVANCE_XAXIS_SAWTOOTH2	0x00080000
#define POWERADVANCE_XAXIS_ALL			0x000F0002

#define POWERADVANCE_YAXIS				0x0004
#define POWERADVANCE_YAXIS_LINE			0x00100000
#define POWERADVANCE_YAXIS_TEXT			0x00200000
#define POWERADVANCE_YAXIS_SAWTOOTH1	0x00400000
#define POWERADVANCE_YAXIS_SAWTOOTH2	0x00800000
#define POWERADVANCE_YAXIS_ALL			0x00F00004

#define POWERADVANCE_AXISCENTER			0X00000100

#define POWERADVANCE_CIRCLE				0X00001000	//�Ƿ����Բ�̶�
#define POWERADVANCE_BIASlINE			0X00002000	//�Ƿ����б�߿̶�

#define POWERADVANE_PI		3.14159265

/////////////////////////////////////////////////////////////////////////////
// CLogarithmAxis command target

class CLogarithmAxis : public CCmdTarget
{
	DECLARE_DYNCREATE(CLogarithmAxis)

	CLogarithmAxis();           // protected constructor used by dynamic creation

public:
	COLORREF	m_crAxisGrid;				//���������		
	COLORREF	m_crAxisCenter;				//�������������ɫ
	COLORREF	m_crAxisBK;					//����ı���
	COLORREF	m_crZoneLine;				//��������ɫ
	COLORREF	m_crTestTitle;				//������Ŀ�ı�����ɫ
	COLORREF	m_crViewBK;					//��ͼ��ɫ
	long		m_lAxisGridLineType;		//���������ߵ�����
	CRect	m_rectAxis;			//����ϵ��λ��
	float	m_fAxisValue[4];		//��������ķ�Χ	0-3���ѿ������ꣻ4-7��������
	long    m_lAxisDrawStyle;
	long    m_lCurrTestItem;        //��ǰ������Ŀ

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
	CBaseObjectList       odYAxisDef;
	float					iYAxisOneGap;
	CString				cYAxisName;
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
	CBaseObjectList   odXAxisDef;
	float				iXAxisOneGap;
	CString				cXAxisName;
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
	
	void LogicPointToDevicePoint(float fx,float fy,CPoint *pPoint);	//���߼�����ת��Ϊʵ������
	void DevicePointToLogicPoint(CPoint point,double *fx,double *fy);//��ʵ�������ȡʵ�������������ֵ
	
	void DrawIt(CDC *cDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawFrame(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));	
	void ModifyWorkArea(CRect* cRect,BOOL bInit,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	BOOL MakeWorkAreaLegal(CRect &cNewRect);
	void SetAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY);
	long GetAxisMinMaxVal(double *dMinX,double *dMinY,double *dMaxX,double *dMaxY);
	void SetBorder(CRect rectBorder);
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
	long    lDisplayType;//��ʾ����
	long    lDrawXAxisTextType;
	int		iMM;
public:
	int iLeftGap,iRightGap,iTopGap,iBottomGap;
	//WorkArea Bk
	COLORREF crBkGroundColor,crBkLeftTopColor,crBkRightBottomColor;
	LOGBRUSH cBkGroundBrush;
	int		 iShadow;
	///////////////////////////////
	//VertDef
	LOGFONT   lfVertFont,lfVertTitleFont;////��ֱ�̶ȼ�Y�����Ƶ�����
	COLORREF  crVertColor,crVertTitleColor;//��ɫ
	long      lVertLineStyle;
	COLORREF  crVert_WorkAreaLine_Color;
	LOGPEN	  crVert_WorkAreaLine_Pen,crVert_WorkAreaShortLine_Pen;;
	int       iVertAreaWidth;
	int       iVertGapLineLen1,iVertGapLineLen2,iVertGapLineLen3;
	
	COLORREF  m_crYTenthScaleColor;
	COLORREF  m_crYUnitScaleColor,m_crYUnitScaleShadowColor;
	//HorzDef
	LOGFONT   lfHorzFont,lfHorzTitleFont;
	COLORREF  crHorzColor,crHorzTitleColor;
	long      lHorzLineStyle;
	COLORREF  crHorz_WorkAreaLine_Color;
	LOGPEN	  crHorz_WorkAreaLine_Pen,crHorz_WorkAreaShortLine_Pen;
	int       iHorzAreaWidth;
	int       iHorzGapLineLen1,iHorzGapLineLen2,iHorzGapLineLen3;
	
	COLORREF  m_crXTenthScaleColor;
	COLORREF  m_crXUnitScaleColor,m_crXUnitScaleShadowColor;
	//Cursor Area Def
	LOGPEN    lCursorPen;
	LOGPEN	  lChoiceAreaPen;
	LOGBRUSH  lChoiceAreaBrush;
	
	///б�߿̶ȡ�Բ�̶ȵ����ݶ���
	COLORREF	crCircleScale,crBiaslineScale;
	long	lCircleLineType,lBiasLineType;
	LOGPEN		cr_CircleScale_Pen,cr_BiaslineScale_Pen;
	float		fCircleScaleOffset,fBiaslineScaleOffset;	//Բ�̶ȵİ뾶λ�ơ�б�߿̶ȵĽǶ�λ��
	
	////////	�������������������
	long  lAxisCenterLineWidth;
	long  lAxisCenterLineType;
	COLORREF crAxisCenter;
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
	CRect   cBorder;
	CRect   cWorkArea;//��������
	CRect   cX_Axis,cY_Axis;//X��,Y���ע����
	
	int     iDataMinVal,iDataMaxVal;//�������ֵ����Сֵ
	float     iDisplayMinVal,iDisplayMaxVal;//����Y��====>>��ʾ��������ֵ����Сֵ,
	float     iBeginPalace,iEndPalace;//����X��====>>��ʼ��λ�ã�������λ��
	int		iDirection;//����
	/////////////���涨���¼X��,Y��ԭʼ��ʾ��������ֵ����Сֵ,���ڻָ�ԭͼ��
	float     m_iOldBeginPalace,m_iOldEndPalace;//����X��====>>��ʼ��λ�ã�������λ��
	float     m_iOldDisplayMinVal,m_iOldDisplayMaxVal;//����Y��====>>��ʾ��������ֵ����Сֵ,
	//////////////////////////////////////////////
	int		iMinValueXAxis,iMaxValueXAxis;/////// X Axis max and min value.....
	long GetDataMaxVal();
	long GetDataMinVal();
	virtual const CLogarithmAxis & operator =(CLogarithmAxis &odTemp);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogarithmAxis)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLogarithmAxis();

	// Generated message map functions
	//{{AFX_MSG(CLogarithmAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLogarithmAxis)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CLogarithmAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
						 
	BEGIN_INTERFACE_PART(LogarithmAxisInterface,ILogarithmAxisInterface)
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
	END_INTERFACE_PART(LogarithmAxisInterface)

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

#endif // !defined(AFX_LOGARITHMAXIS_H__BD3F4631_2D7B_47BF_9E4C_984999405186__INCLUDED_)
