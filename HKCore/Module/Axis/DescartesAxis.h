// DescartesAxis.h: interface for the CDescartesAxis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined DESCARTESAXIS_H_
#define DESCARTESAXIS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxisInterface.h"

//////////////////////////////////////////////////////////////////////////
//############################�ѿ�������ϵͳ##############################
//////////////////////////////////////////////////////////////////////////
#define DESCARTESAXISDRAW_ALL				0x00FFFFFF
#define DESCARTESAXISDRAW_WORKAREA			0x00000001	//
#define DESCARTESAXISDRAW_AXISCENTER		0x00000002	//
#define DESCARTESAXISDRAW_AXISBODER			0x00000004	//
#define DESCARTESAXISDRAW_AXISTITLE			0x00000008	//

#define DESCARTESAXISDRAW_XAXIS_ALL			0x00000FF0	//
#define DESCARTESAXISDRAW_XAXIS_LINE		0x00000010	//
#define DESCARTESAXISDRAW_XAXIS_SCALETEXT	0x00000020	//
#define DESCARTESAXISDRAW_XAXIS_TENTHSCALE	0x00000040	//
#define DESCARTESAXISDRAW_XAXIS_HALFSCCALE	0x00000080	//
#define DESCARTESAXISDRAW_XAXIS_NAME		0x00000100	//

#define DESCARTESAXISDRAW_YAXIS_ALL			0x000FF000	//
#define DESCARTESAXISDRAW_YAXIS_LINE		0x00001000	//
#define DESCARTESAXISDRAW_YAXIS_SCALETEXT	0x00002000	//
#define DESCARTESAXISDRAW_YAXIS_TENTHSCALE	0x00004000	//
#define DESCARTESAXISDRAW_YAXIS_HALFSCCALE	0x00008000	//
#define DESCARTESAXISDRAW_YAXIS_NAME		0x00100000	//



class CDescartesAxis : public CAxisInterface
{
public:
	CDescartesAxis();
	virtual ~CDescartesAxis();

private:
	long    m_nMinOneGapWidth;		//X������Ĵ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
	long    m_nMinOneGapHeight;		//Y������Ĵ�̶ȱ�ע֮��ļ���ռ�(�߶�)��Сֵ
	long	m_lAxisType;			//����������� 0����ͨ�����᣻  1��ʱ��������
	BOOL    m_bAxisXYUnitLock;		//X��Y���������ʾ����������־
	double  m_dAxisWorkMarginRatio;	//���깤����ͬ���е�ͼ�εı߾�

	//����������̶���
	long	m_lXAxisMaxUnitCount;
	long	m_lYAxisMaxUnitCount;
	

	//////////////////////////////////////////////////////////////////////////
	//��������������
	//////////////////////////////////////////////////////////////////////////

	//������ķ�Χ�����ֵ����Сֵ
	double    m_dXAxisMinVal, m_dXAxisMaxVal;	//����X��====>>��ʼ��λ�ã�������λ��
	double    m_dYAxisMinVal, m_dYAxisMaxVal;	//����Y��====>>��ʾ��������ֵ����Сֵ,
	double    m_dY2AxisMinVal, m_dY2AxisMaxVal;	//����Y��====>>��ʾ��������ֵ����Сֵ,
	
	CRect     m_rectBorder;	//����������
	CRect     m_rectWorkArea;	//�����Ṥ������

	CPoint	m_ptCenterLogInDv;	    ////�߼������ԭ�����豸�����ϵ�����ֵ
	double	m_dOneYGapValue;		///////Y��ʵ��������ʵ��ֵ�ı���
	double	m_dOneXGapValue;		///////X��ʵ��������ʵ��ֵ�ı���
	double	m_dOneY2GapValue;		///////Y��ʵ��������ʵ��ֵ�ı���
	
	//������Ľ�λ������λ��λ1��2��5��10
	double	m_dXCarryOneGap;	//X���λ
	double	m_dYCarryOneGap;	//Y���λ
	double	m_dY2CarryOneGap;	//Y���λ
	float	m_fCoefficient;		//ͼ�μ���ķŴ�ϵ����������Ļ�ߴ����ӡ�Ŀ���

	BOOL m_bLockXCarryOneGap;
	
	//��������������
	CRect   m_rectXAxis, m_rectYAxis, m_rectY2Axis;	//X��,Y������
	long	m_nLeftGap,m_nRightGap,m_nTopGap,m_nBottomGap;	//
	
	//X��,Y��ԭʼ��ʾ��������ֵ����Сֵ,���ڻָ�ԭͼ��
	double     m_dXAxisOldMinVal,m_dXAxisOldMaxVal;	//����X��====>>��ʼ��λ�ã�������λ��
	double     m_dYAxisOldMinVal,m_dYAxisOldMaxVal;	//����Y��====>>��ʾ��������ֵ����Сֵ,
	double     m_dY2AxisOldMinVal,m_dY2AxisOldMaxVal;	//����Y��====>>��ʾ��������ֵ����Сֵ,

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
	long		 m_nWorkAreaBorderShadow;	//�������߽���Ӱ
	LOGBRUSH m_cBkGroundBrush;
	COLORREF m_crFrameLeftTopColor;
	COLORREF m_crFrameRightBottomColor;
	long	m_nFrameShadow;	//�������߽���Ӱ
	void     DrawXYAxisRect(CDC *pDC,float fZoomRatio,CPoint ptOffset);
	
	
	///////////////////////////////
	//Y�������������
	COLORREF m_crYAxisWorkAreaBackColorFrom, m_crYAxisWorkAreaBackColorTo;    //Y������������ɫ
	COLORREF m_crYUnitScaleColor;	//��λ�̶���ɫ
	COLORREF m_crYUnitScaleShadowColor;//��λ�̶���Ӱ��ɫ
	LOGFONT   m_lfYAxisScaleFont;	////��ֱ�̶ȵ�����
	LOGFONT   m_lfYAxisNameFont;		////Y�����Ƶ�����
	COLORREF  m_crYAxisScaleFontColor;//Y��������������ɫ
	COLORREF  m_crYAxisNameFontColor;//��ɫ
	long      m_lYAxisGridLineStyle;	//Y������ɫ
	COLORREF  m_crYAxisGridLineColor;
	LOGPEN	  m_logpenYAxisGridLine;
	COLORREF  m_crYAxisTenthScale;	//1/10�̶Ȼ�����ɫ
	LOGPEN	  m_logpenYAxisTenthScale;	//1/10�̶Ȼ���
	long       m_nYAxisAreaWidth;	//Y����������Ŀ��
	long       m_nYAxisUnitScaleLineLen;	//Y�����굥λ�̶ȳ���
	long       m_nYAxisHalfScaleLineLen;	//Y������1/2�̶ȳ���
	long       m_nYAxisTenthScaleLineLen;	//Y������1/10�̶ȳ���
	
	//X�������������
	COLORREF m_crXAxisWorkAreaBackColorFrom, m_crXAxisWorkAreaBackColorTo;    //X������������ɫ
	COLORREF m_crXUnitScaleColor;	//��λ�̶���ɫ
	COLORREF m_crXUnitScaleShadowColor;//��λ�̶���Ӱ��ɫ
	LOGFONT   m_lfXAxisScaleFont;	////��ֱ�̶ȵ�����
	LOGFONT   m_lfXAxisNameFont;		////X�����Ƶ�����
	COLORREF  m_crXAxisScaleFontColor;
	COLORREF  m_crXAxisNameFontColor;//��ɫ
	long      m_lXAxisGridLineStyle;
	COLORREF  m_crXAxisGridLineColor;
	LOGPEN	  m_logpenXAxisGridLine;
	COLORREF  m_crXAxisTenthScale;	//1/10�̶Ȼ�����ɫ
	LOGPEN	  m_logpenXAxisTenthScale;	//1/10�̶Ȼ���
	long       m_nXAxisAreaHeight;	//X����������ĸ߶�
	long       m_nXAxisUnitScaleLineLen;	//X�����굥λ�̶ȳ���
	long       m_nXAxisHalfScaleLineLen;	//X������1/2�̶ȳ���
	long       m_nXAxisTenthScaleLineLen;	//X������1/10�̶ȳ���
	
	////////	�������������������
	long  m_lAxisCenterLineWidth;
	long  m_lAxisCenterLineType;
	COLORREF m_crAxisCenterColor;//��������ɫ

	double m_dMaxZoomMultiple;	//���Ŵ���

	//X���������
	double		m_dXAxisOneGap;	//X��ĵ�λ�̶ȵĸ߶�
	CString		m_strXAxisName;	//
	CAxisScaleDataList       m_listXAxisScale;
	//Y���������
	double		m_dYAxisOneGap;	//Y��ĵ�λ�̶ȵĸ߶�
	CString		m_strYAxisName;	//
	CAxisScaleDataList       m_listYAxisScale;


	BOOL      m_bUseY2Axis;
	CString		m_strY2AxisName;	//
	CAxisScaleDataList       m_listY2AxisScale;
	
	
// Operations
public:
	//����ת��
	virtual void	LogicPointToDevicePoint(double fx,double fy,CPoint *pPoint, long nAxisIndex=0);	//���߼�����ת��Ϊʵ������
	virtual void	DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0);//��ʵ�������ȡʵ�������������ֵ
    virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex);
    virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex);
    virtual void GetAxisDrawArea(CRect &rcArea);
	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
	virtual void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);//zhouhj 20210130 ���������������������Ƶ�
	virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);

#ifdef USE_AXIS_CONFIG
	virtual void SetAxisConfig(CDataGroup *pAxisConfig);//zhouhj 20211026 ������������������
	virtual void GetAxisConfig(CDataGroup *pAxisConfig);
	void SetAxisConfig(CDvmData *pAxisData);
#endif
	
private:
	void InitAxis();
	void ContinueInitAxis();
	
	CRect GetXAxisArea();
	CRect GetYAxisArea();
	CRect GetY2AxisArea();
	
	//////////////////////////////////////////////////////////////////////////
	//X Axis 
	COLORREF GetXAxisTenthScaleColr();


	//����������ݼ���
	double GetFloatCarryVal(double fVal);
	double MakeFloatGapValLegal(double fVal,double &lVal);//float fVal,long &lVal

	long GetCarryVal(long iVal);
	long MakeGapValLegal(float fVal,long &lVal);

	///////////////////////////////////////*********************************************
	///////////////////���涨�� Y ����ص����ݼ�����
	void	InitAxisAttr();
	void InitYAxisDef();
	void ResetYAxisDef();
	void ResetY2AxisDef();
	
	void EndYAxisDef();
	void ResetOneYAxisDef(double lVal);
	void ResetOneY2AxisDef(double lVal);
	void DrawYAxis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawY2Axis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisText(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawY2AxisText(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	long GetBaseOneGapHeight();
	long GetMinOneGapHeight();
	void DrawYSawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawY2Sawtooth(CDC*,BYTE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void GetOneYAxisHeight(double iGap,BYTE);		////////modify in 05-30;;
	void DrawOneYSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneY2Sawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneYSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawOneY2SawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawYAxisName(CDC*,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawY2AxisName(CDC*,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawAxisTitle(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	
	///////////////////////////////////////*********************************************
	///////////////////���涨�� X ����ص����ݼ�����
	//++++++++++++++X �����ӿ�����
	void InitXAxisDef();
	void ResetXAxisDef();

	void EndXAxisDef();
	void ResetOneXAxisDef(double lVal);
	void DrawXAxis(CDC *pDC,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	void DrawXAxisLine(CDC *pDC,CAxisScaleData *pScaleData,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	CString GetTimeVal(float fTimeVal);
	CRect DrawXAxisText(CDC *pDC,CAxisScaleData *pScaleData,BOOL b=FALSE,BOOL bDraw=TRUE,float fZoomRatio=1.0f,CPoint ptOffset=CPoint(0,0));
	long GetBaseOneGapWidth();
	long GetMinOneGapWidth();
	long Get60CarryVal(long iVal);
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


	//#############################################################################################//
	//################################�ӿڶ���#####################################################//
	//#############################################################################################//
public:
	void   SetUseY2Axis(BOOL bUseY2Axis)     {      m_bUseY2Axis = bUseY2Axis;  }
	BOOL   GetUseY2Axis()                    {      return m_bUseY2Axis;        }
	void   SetLeftGap(long nGap)             {      m_nLeftGap = nGap;          }
	void   SetTopGap(long nGap)              {      m_nTopGap = nGap;           }
	void   SetRightGap(long nGap)            {      m_nRightGap = nGap;         }
	void   SetBottomGap(long nGap)           {      m_nBottomGap = nGap;        }

	//////////////////////////////////////////////////////////////////////////
	//����Ŵ���С���ƶ��ӿ�
	virtual void ZoomIn(float fZoomIn=2.0f);
	void ZoomIn(double dMinX,double dMaxX,double dMinY,double dMaxY);
	void ZoomIn(CRect rectZoomIn);
	void ZoomIn(long lLeft,long lTop,long lRight,long lBottom);
	void ZoomIn(CPoint ptLeftTop,CPoint ptRightBottom);
	virtual void ZoomOut(float fZoomOut=2.0f);

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
	virtual void GetAxisInterface(long &nXCenterLog,long &nYCenterLog,double &dXCoef,double &dYCoef);
	
	//����ϵ�Ļ�ͼλ��
	void SetMinMaxVal(double xMin,double yMin,double xMax,double yMax,long nReserved)
	{
		SetXYAxisMinMaxVal(xMin, yMin, xMax, yMax);
	}
	
	//////////////////////////////////////////////////////////////////////////
	//����ϵ
public:
	//���귶Χ
	void SetXYAxisMinMaxVal(double dMinX,double dMinY,double dMaxX,double dMaxY, double dMinY2=0,double dMaxY2=10);
	void GetXYAxisMinMaxVal(double &dMinX,double &dMinY,double &dMaxX,double &dMaxY, double &dMinY2,double &dMaxY2);
	
	//����ϵ����
	void SetAxisTitle(CString strAxisTitle);
	CString GetAxisTitle();
	
	//����ϵ������
	virtual CRect GetWorkArea();
	
	//��������
	void SetBorder(CRect rectBorder);
	CRect GetBorder();

	void SetXAxisWorkAreaBackColor(COLORREF crAxisWorkAreaBackColorFrom, COLORREF crAxisWorkAreaBackColorTo)
	{
		m_crXAxisWorkAreaBackColorFrom = crAxisWorkAreaBackColorFrom;
		m_crXAxisWorkAreaBackColorTo = crAxisWorkAreaBackColorTo;
	}
	void SetYAxisWorkAreaBackColor(COLORREF crAxisWorkAreaBackColorFrom, COLORREF crAxisWorkAreaBackColorTo)
	{
		m_crYAxisWorkAreaBackColorFrom = crAxisWorkAreaBackColorFrom;
		m_crYAxisWorkAreaBackColorTo = crAxisWorkAreaBackColorTo;
	}
	void GetXAxisWorkAreaBackColor(COLORREF &crAxisWorkAreaBackColorFrom, COLORREF &crAxisWorkAreaBackColorTo)
	{
		crAxisWorkAreaBackColorFrom = m_crXAxisWorkAreaBackColorFrom;
		crAxisWorkAreaBackColorTo   = m_crXAxisWorkAreaBackColorTo;
	}
	void GetYAxisWorkAreaBackColor(COLORREF &crAxisWorkAreaBackColorFrom, COLORREF &crAxisWorkAreaBackColorTo)
	{
		crAxisWorkAreaBackColorFrom = m_crYAxisWorkAreaBackColorFrom;
		crAxisWorkAreaBackColorTo   = m_crYAxisWorkAreaBackColorTo;
	}
	//////////////////////////////////////////////////////////////////////////
	//X������
public:
	void SetXAxisName(CString strXAxisName);
	CString GetXAxisName();

	//X������Ĵ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
	long GetXAxisMinSawGapWidth();
	void SetXAxisMinSawGapWidth(long nValue);

	//Y������Ĵ�̶ȱ�ע֮��ļ���ռ�(�߶�)��Сֵ
	long GetYAxisMinSawGapHeight();
	void SetYAxisMinSawGapHeight(long nValue);

	//����������� 0����ͨ�����᣻  1��ʱ��������
	long GetXAxisType();
	void SetXAxisType(long nValue);

	//����������̶���
	void SetXAxisMaxUnitCount(long nValue);
	long GetXAxisMaxUnitCount();
	void SetYAxisMaxUnitCount(long nValue);
	long GetYAxisMaxUnitCount();
	void LockXCarryOneGap(BOOL bLock, double dXCarryOneGap);

	//X��Y���������ʾ����������־
	void SetAxisXYUnitLock(long nValue);
	long GetAxisXYUnitLock();

	//����ϵͳ�Ļ�������,2005.08.12���
	void SetAxisDrawStyle(long nValue)      {        m_lAxisDrawStyle = nValue;    };
	void SetAxisDrawStyleEx(DWORD dwValue)      {        m_lAxisDrawStyle |= dwValue;    };
	void ClearAxisDrawStyleEx(DWORD dwValue)      {        m_lAxisDrawStyle &= (~dwValue);    };
	long GetAxisDrawStyle()                 {        return m_lAxisDrawStyle;      } ;
	void SetAxisDrawStyleBit(long nValue);
	long ClearAxisDrawStyleBit(long nValue);
	
	//X���ע����ģʽ��0=��ע�ڿ̶��ұߣ�1=��ע�ڿ̶��·�����
	void SetXAxisTextDrawStyle(long nValue = 1);
	long GetXAxisTextDrawStyle();

	//��������⼰�����塢��ɫ
    //void SetAxisTitle(BSTR bstrValue);
    //long GetAxisTitle(BSTR *pbstrValue);
	void SetAxisTitleFont(LOGFONT lfFont);//long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetAxisTitleFont();//long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	void SetAxisTitleFontColor(COLORREF nValue);
	COLORREF GetAxisTitleFontColor();
	
	//����ϵͳ�ı���ɫ
	void SetAxisBackColor(COLORREF nValue);
	COLORREF GetAxisBackColor();

	//����ϵͳ��������ɫ
	void SetWorkAreaBkColor(COLORREF nValue);
	COLORREF GetWorkAreaBkColor();
	void SetWorkAreaBorderLeftTopColor(COLORREF nValue);
	COLORREF GetWorkAreaBorderLeftTopColor();
	void SetWorkAreaBorderRightBottomColor(COLORREF nValue);
	COLORREF GetWorkAreaBorderRightBottomColor();

	//�������߽���Ӱ
	void SetWorkAreaBorderShadow(long nValue);
	long GetWorkAreaBorderShadow();

	//����ϵͳ�߿����ɫ
	void SetFrameLeftTopColor(COLORREF nValue);
	COLORREF GetFrameLeftTopColor();
	void SetFrameRightBottomColor(COLORREF nValue);
	COLORREF GetFrameRightBottomColor();

	//����ϵͳ�߿�߽���Ӱ
	void SetFrameShadow(long nValue);
	long GetFrameShadow();
	
	//////////////////////////////////////////////////////////////////////////
	//Y Axis
public:
	//������
	void SetYAxisName(CString strYAxisName);
	CString GetYAxisName();
	void SetY2AxisName(CString strYAxisName);
	CString GetY2AxisName();

	//��λ�̶���ɫ
	void SetYUnitScaleColor(COLORREF nValue);
	COLORREF GetYUnitScaleColor();
	//��λ�̶���Ӱ��ɫ
	void SetYUnitScaleShadowColor(COLORREF nValue);
	COLORREF GetYUnitScaleShadowColor();
	//��ֱ�̶ȵ�����
	void SetYAxisScaleFont(LOGFONT lf);  //long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetYAxisScaleFont();  //long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//Y�����ơ����塢������ɫ
    //void SetYAxisName(BSTR bstrName);
    //long GetYAxisName(BSTR *pbstrName);
	//Y�����Ƶ�����
	void SetYAxisNameFont(LOGFONT lfFont);//(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetYAxisNameFont();//long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//Y������������ɫ
	void SetYAxisNameFontColor(COLORREF nValue);
	COLORREF GetYAxisNameFontColor();
	//Y��̶�������ɫ
	void SetYAxisScaleFontColor(COLORREF nValue);
	COLORREF GetYAxisScaleFontColor();
	//Y���������͡���ɫ
	void SetYAxisGridLineStyle(long nValue);
	long GetYAxisGridLineStyle();
	void SetYAxisGridLineColor(COLORREF nValue);
	COLORREF GetYAxisGridLineColor();
	//1/10�̶Ȼ�����ɫ
	void SetYAxisTenthScaleColor(COLORREF nValue);
	COLORREF GetYAxisTenthScaleColor();
	//Y����������Ŀ��
	void SetYAxisAreaWidth(long nValue);
	long GetYAxisAreaWidth();
	//Y�����굥λ�̶ȳ���
	void SetYAxisUnitScaleLineLen(long nValue);
	long GetYAxisUnitScaleLineLen();
	//Y������1/2�̶ȳ���
	void SetYAxisHalfScaleLineLen(long nValue);
	long GetYAxisHalfScaleLineLen();
	////Y������1/10�̶ȳ���
	void SetYAxisTenthScaleLineLen(long nValue);
	long GetYAxisTenthScaleLineLen();
	
	//X Axis
	//��λ�̶���ɫ
	void SetXUnitScaleColor(COLORREF nValue);
	COLORREF GetXUnitScaleColor();
	//��λ�̶���Ӱ��ɫ
	void SetXUnitScaleShadowColor(COLORREF nValue);
	COLORREF GetXUnitScaleShadowColor();
	//��ֱ�̶ȵ�����
	void SetXAxisScaleFont(LOGFONT lfFont);//(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetXAxisScaleFont();//long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//X�����ơ����塢������ɫ
    //void SetXAxisName(BSTR bstrName);
    //long GetXAxisName(BSTR *pbstrName);
	//X�����Ƶ�����
	void SetXAxisNameFont(LOGFONT lfFont);//(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	LOGFONT GetXAxisNameFont();//long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//X������������ɫ
	void SetXAxisNameFontColor(COLORREF nValue);
	COLORREF GetXAxisNameFontColor();
	//X��̶�������ɫ
	void SetXAxisScaleFontColor(COLORREF nValue);
	COLORREF GetXAxisScaleFontColor();
	//X���������͡���ɫ
	void SetXAxisGridLineStyle(long nValue);
	long GetXAxisGridLineStyle();
	void SetXAxisGridLineColor(COLORREF nValue);
	COLORREF GetXAxisGridLineColor();
	//1/10�̶Ȼ�����ɫ
	void SetXAxisTenthScaleColor(COLORREF nValue);
	COLORREF GetXAxisTenthScaleColor();
	//X����������Ŀ��
	void SetXAxisAreaHeight(long nValue);
	long GetXAxisAreaHeight();
	//X�����굥λ�̶ȳ���
	void SetXAxisUnitScaleLineLen(long nValue);
	long GetXAxisUnitScaleLineLen();
	//X������1/2�̶ȳ���
	void SetXAxisHalfScaleLineLen(long nValue);
	long GetXAxisHalfScaleLineLen();
	////X������1/10�̶ȳ���
	void SetXAxisTenthScaleLineLen(long nValue);
	long GetXAxisTenthScaleLineLen();
	
	//�������������������
	void SetAxisCenterLineWidth(long nValue);
	long GetAxisCenterLineWidth();
	void SetAxisCenterLineType(long nValue);
	long GetAxisCenterLineType();
	void SetAxisCenterColor(COLORREF nValue);
	COLORREF GetAxisCenterColor();
	
	//���¼�������ϵͳ�Ŀ̶�
	long ResetAxis();
	
	//��ͼ
	long DrawAxis(CDC *pDC, float fZoomRatio,long xOffset,long yOffset)
	{
		CPoint pt;
		pt = CPoint(xOffset,yOffset);
		DrawIt(pDC,fZoomRatio,pt);	
		return 0;
	}
	long DrawAxis(CDC *pDC,float fZoomRatio, CPoint &ptOffset)
	{
		DrawIt(pDC,fZoomRatio,ptOffset);	
		return 0;
	}
	
};


#endif // !defined(DESCARTESAXIS_H_
