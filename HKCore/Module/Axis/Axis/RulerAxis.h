#if !defined(AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_)
#define AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RulerAxis.h : header file
#include "..\..\Module\BaseObject\BaseObject.h"
#include "..\..\Module\Interface\AxisInterface.h"

#define RULERDRAW_ALL				0x000FFFFF
#define RULERDRAW_BODER				0x00000001	//��߱߿�
#define RULERDRAW_WORKAREA			0x00000002	//��߹�����
#define RULERDRAW_SCALETEXT			0x00000004	//��߱�ע
#define RULERDRAW_TENTHSCALE		0x00000008	//���1/10�̶Ȼ��ƿ���
#define RULERDRAW_HALFSCCALE		0x00000010	//���1/2�̶Ȼ��ƿ���


/////////////////////////////////////////////////////////////////////////////
// CRulerAxis command target

class CRulerAxis : public CCmdTarget
{
	DECLARE_DYNCREATE(CRulerAxis)

	CRulerAxis();           // protected constructor used by dynamic creation

// Attributes
public:
	long	m_nRulerType;	////��ߵ����� 0��ˮƽ��ߣ�  1����ֱ���
	double	m_dVectorCoef;				//ʸ��ͼ�ı�������
	long	m_lDrawRulerTextType;	//��߿̶ȱ�ע������
	int		m_iBigSawMinWidth;		//��ߵĴ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
	int		m_iRulerHeight;
	long    m_lMaxRulerGapCount;
	double  m_dMaxZoomMultiple;
	long    m_lDrawStyle;
	
	int		m_iRulerDirection;		//��ߵķ���0����߱�ע���£�	1����߱�ע����

	void	SetVectorCoef(double dCoef);////ʸ��ͼ�ı�������
	double	GetVectorCoef();
	void	SetRulerSawTextType(int iType);////��߿̶ȱ�ע������
	int		GetRulerSawTextType();
	void	SetBigSawMinWidth(int iSawWidth);//��ߵĴ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
	int		GetBigSawMinWidth();
	void	SetRulerDirection(int iRulerType);//��ߵķ���
	int		GetRulerDirection();
	void	SetRulerHeight(int iHeight);//�߶�
	int		GetRulerHeight();
	
	COLORREF m_crSmallSaw;
	COLORREF crShadowColor1,crShadowColor2;//��λ�̶���ɫ����λ�̶���Ӱ��ɫ
	COLORREF m_crFrameLeftTop,m_crFrameRightBottom;
	COLORREF m_crRulerBackColor;
	long     m_lFrameShadow;
	//HorzDef
	LOGFONT   lfHorzFont,lfHorzTitleFont;
	COLORREF  m_crHorzSawText,m_crHorzTitleColor;
	LOGPEN	  m_logpenSmallSaw;
	int       m_iHorBigSawLenLen,m_iHorHalfSawLen,m_iHorSmallSawLen;
// Operations
public:
	void InitIt();
	void ContinueInit();
	
	//##################################################3
	//�߼�������ʵ�������ת��
private:
	double	m_dOneHorGapValue;
	int		m_iCenterLogInDv;
public:
	void	InitHorzRulerAttr();
	void	LogicPointToDevicePoint(double fx,long *iX);	//���߼�����ת��Ϊʵ������
	void	DevicePointToLogicPoint(long iX,double *dX);//��ʵ�������ȡʵ�������������ֵ
	
private:
	double GetFloatCarryVal(double fVal);
	double MakeFloatGapValLegal(double fVal,double &lVal);//float fVal,int &lVal
	
	
public:	//++++++++++++++X �����ӿ�����
	double		m_dRulerHorOneGap;
	CString		m_strRulerName;
	void InitRulerDef();
	void ResetRulerDef();
	
	//##########################################################################
	//����ˮƽ��ߵ���������ֵ��Χ��س�Ա������
public:
	CRect	m_rectRuler;
	double	m_dHorMinValue;
	double	m_dHorMaxValue;
	double  m_dHorOldMinValue;
	double  m_dHorOldMaxValue;
	double	m_dHorCarryOneGap;
	int	m_iBOTTOMADD;
	
	void	ModifyRulerArea(CRect rectRuler);
	CRect	GetRulerArea();
	void	GetRulerMaxMinValue(double *dMinValue,double *dMaxValue);
	void	SetRulerMaxMinValue(double dMinValue,double dMaxValue);
	double	GetHorCarryOenGap();
	
	
	//////��ߵĻ��ơ�����
	CBaseObjectList       m_listRulerDef;
	void EndRulerDef();
	void ResetOneRulerHorDef(double lVal);
	
	CString GetTimeVal(float fTimeVal);
	CRect DrawRulerHorText(CDC *pDC,CAxisScaleData *pScaleData,BOOL b=FALSE,BOOL bDraw=TRUE);
	long GetBaseOneGapWidth();
	long GetMinOneGapWidth();
	long GetMaxRulerGapNum();
	long Get60CarryVal(int iVal);
	double GetRulerBeginVal(double lNowVal,double lGapVal);
	void DrawRulerHorSawtooth(CDC*,BYTE);
	void GetOneRulerHorWidth(double iGap,BYTE);
	void SetBorder(long left,long top,long right,long bottom);
	CRect GetBorder();
	void ZoomIn(float fRate);
	void ZoomOut(float fRate);
	void Move(float fOffset);
	
	POSITION m_posAxisData;

	CAxisScaleData* GetFirstAxisData();
	CAxisScaleData* GetNextAxisData();
	

	void	DrawIt(CDC *pDC);
	
	void DrawOneRulerHorSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd);
	void DrawOneRulerHorSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd);
	void DrawLine(CDC *pDC,int left,int top,int right,int bottom,CPen *cP,BOOL bDel);
	void DrawRulerShadowVertLine(CDC *pDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2);
	void DrawRulerHor(CDC *pDC);
	void DrawRulerHorFrame(CDC*pDC);
	void DrawRulerHorLine(CDC *pDC,CAxisScaleData *pScaleData);
	void DrawRulerHorName(CDC*);
	void DrawRulerBack(CDC *pDC);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulerAxis)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRulerAxis();

	// Generated message map functions
	//{{AFX_MSG(CRulerAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CRulerAxis)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CRulerAxis)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

BEGIN_INTERFACE_PART(RulerAxisInterface,IRulerAxisInterface)
	//X������Ĵ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
	STDMETHOD_(long,GetMinSawGapWidth)(long *nValue);
	STDMETHOD_(long,SetMinSawGapWidth)(long nValue);
	//��ߵ����� 0��ˮƽ��ߣ�  1����ֱ���
	STDMETHOD_(long,GetRulerType)(long *nValue);
	STDMETHOD_(long,SetRulerType)(long nValue);
	//��ߵ����̶���
	STDMETHOD_(long,SetMaxUnitCount)(long nValue);
	STDMETHOD_(long,GetMaxUnitCount)(long *nValue);
	//����ϵͳ�Ļ�������,2005.08.12���
	STDMETHOD_(long,SetDrawStyle)(long nValue);
	STDMETHOD_(long,GetDrawStyle)(long *nValue);
	STDMETHOD_(long,SetDrawStyleBit)(long nValue);
	STDMETHOD_(long,ClearDrawStyleBit)(long nValue);
	
	//��߱�ע����ģʽ��0=��ע�ڿ̶��ұߣ�1=��ע�ڿ̶��·�����
	STDMETHOD_(long,SetScaleTextDrawStyle)(long nValue);
	STDMETHOD_(long,GetScaleTextDrawStyle)(long *nValue);
	//��������⼰�����塢��ɫ
	STDMETHOD_(long,SetRulerTitle)(BSTR bstrValue);
	STDMETHOD_(long,GetRulerTitle)(BSTR *pbstrValue);
	STDMETHOD_(long,SetRulerTitleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	STDMETHOD_(long,GetRulerTitleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	STDMETHOD_(long,SetRulerTitleFontColor)(long nValue);
	STDMETHOD_(long,GetRulerTitleFontColor)(long *nValue);
	
	//��߱���ɫ
	STDMETHOD_(long,SetRulerBackColor)(long nValue);
	STDMETHOD_(long,GetRulerBackColor)(long *nValue);
	//��߱߿����ɫ
	STDMETHOD_(long,SetFrameLeftTopColor)(long nValue);
	STDMETHOD_(long,GetFrameLeftTopColor)(long *nValue);
	STDMETHOD_(long,SetFrameRightBottomColor)(long nValue);
	STDMETHOD_(long,GetFrameRightBottomColor)(long *nValue);
	//��߱߿�߽���Ӱ
	STDMETHOD_(long,SetFrameShadow)(long nValue);
	STDMETHOD_(long,GetFrameShadow)(long *nValue);
	
	//��ߵ�λ�̶���ɫ
	STDMETHOD_(long,SetUnitScaleColor)(long nValue);
	STDMETHOD_(long,GetUnitScaleColor)(long *nValue);
	//��ߵ�λ�̶���Ӱ��ɫ
	STDMETHOD_(long,SetUnitScaleShadowColor)(long nValue);
	STDMETHOD_(long,GetUnitScaleShadowColor)(long *nValue);
	//��߿̶ȵ�����
	STDMETHOD_(long,SetRulerScaleFont)(long lfHeight,long lfWidth,long lfEscapement,long lfOrientation,long lfWeight,long lfItalic,long lfUnderline,long lfStrikeOut,long lfCharSet,long lfOutPrecision,long lfClipPrecision,long lfQuality,long lfPitchAndFamily,BSTR lfFaceName);
	STDMETHOD_(long,GetRulerScaleFont)(long *lfHeight,long *lfWidth,long *lfEscapement,long *lfOrientation,long *lfWeight,long *lfItalic,long *lfUnderline,long *lfStrikeOut,long *lfCharSet,long *lfOutPrecision,long *lfClipPrecision,long *lfQuality,long *lfPitchAndFamily,BSTR *lfFaceName);
	//��߿̶�������ɫ
	STDMETHOD_(long,SetRulerScaleFontColor)(long nValue);
	STDMETHOD_(long,GetRulerScaleFontColor)(long *nValue);
	//���1/10�̶Ȼ�����ɫ
	STDMETHOD_(long,SetRulerTenthScaleColor)(long nValue);
	STDMETHOD_(long,GetRulerTenthScaleColor)(long *nValue);
	//�����������Ŀ��/�߶�
	STDMETHOD_(long,SetRulerAreaWidth)(long nValue);
	STDMETHOD_(long,GetRulerAreaWidth)(long *nValue);
	//��ߵ�λ�̶ȳ���
	STDMETHOD_(long,SetRulerUnitScaleLineLen)(long nValue);
	STDMETHOD_(long,GetRulerUnitScaleLineLen)(long *nValue);
	//���1/2�̶ȳ���
	STDMETHOD_(long,SetRulerHalfScaleLineLen)(long nValue);
	STDMETHOD_(long,GetRulerHalfScaleLineLen)(long *nValue);
	//���1/10�̶ȳ���
	STDMETHOD_(long,SetRulerTenthScaleLineLen)(long nValue);
	STDMETHOD_(long,GetRulerTenthScaleLineLen)(long *nValue);
	
	//�߼��������豸����֮���ת��
	STDMETHOD_(long,LogicPointToDevicePoint)(double dValue,long *nValue);
	STDMETHOD_(long,DevicePointToLogicPoint)(long nValue,double *dValue);
	
	//���귶Χ
	STDMETHOD_(long,SetMinMaxVal)(double Min,double Max,long nReserved);
	STDMETHOD_(long,GetMinMaxVal)(double *Min,double *Max,long nReserved);
	
	//��������
	STDMETHOD_(long,SetBoder)(long left, long top, long right, long bottom);
	STDMETHOD_(long,GetBoder)(long *left, long *top, long *right, long *bottom);
	
	//���¼�������ϵͳ�Ŀ̶�
	STDMETHOD_(long,ResetAxis)();
	
	//��ͼ
	STDMETHOD_(long,DrawAxis)(long lDC,float fZoomRatio,long xOffset,long yOffset);
	
	//�Ŵ���С
	STDMETHOD_(long,ZoomIn)(float fRate);
	STDMETHOD_(long,ZoomOut)(float fRate);
	STDMETHOD_(long,Move)(float fOffset);
	
END_INTERFACE_PART(RulerAxisInterface)

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

#endif // !defined(AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_)
