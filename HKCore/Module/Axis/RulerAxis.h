#if !defined(AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_)
#define AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RulerAxis.h : header file

#define RULERDRAW_ALL				0x000FFFFF
#define RULERDRAW_BODER				0x00000001	//��߱߿�
#define RULERDRAW_WORKAREA			0x00000002	//��߹�����
#define RULERDRAW_SCALETEXT			0x00000004	//��߱�ע
#define RULERDRAW_TENTHSCALE		0x00000008	//���1/10�̶Ȼ��ƿ���
#define RULERDRAW_HALFSCCALE		0x00000010	//���1/2�̶Ȼ��ƿ���

#include "AxisInterface.h"

#define RULER_DIRECTION_RIGHTDOWN    0
#define RULER_DIRECTION_LEFTUP       1

/////////////////////////////////////////////////////////////////////////////
// CRulerAxis command target

class CRulerAxis : public CAxisInterface
{
//2021-1-16  lijunqing
public:
	virtual void LogicPointToDevicePoint(double x, double y, CPoint *pPoint, long nAxisIndex=0);
	virtual void DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0);
	virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex);
	virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex);
	virtual void GetAxisDrawArea(CRect &rcArea);
	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
	virtual CRect GetWorkArea()	{	return m_rectRuler;	}
	virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);
#ifdef USE_AXIS_CONFIG
	virtual void SetAxisConfig(CDataGroup *pAxisConfig) ;
	virtual void GetAxisConfig(CDataGroup *pAxisConfig) ;
#endif
	void AttatchRefAxis(CRulerAxis *pAxis)	{	m_pRefAxis = pAxis;	}
protected:
	//���m_pRefAxisX��Ϊ�գ�������ΪY�᣻���m_pRefAxisY��Ϊ�գ�������ΪX��
	CRulerAxis *m_pRefAxis;

public:
	CRulerAxis(); 
	virtual ~CRulerAxis();
	static const long g_nRulerType_Horz;
	static const long g_nRulerType_Vert;

// Attributes
public:
	long	m_nRulerType;	////��ߵ����� 0��ˮƽ��ߣ�  1����ֱ���
	double	m_dVectorCoef;				//ʸ��ͼ�ı�������
	long	m_nDrawRulerTextType;	//��߿̶ȱ�ע������
	int		m_nBigSawMinWidth;		//��ߵĴ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
	int		m_nRulerHeight;
	long    m_nMaxRulerGapCount;
	double  m_dMaxZoomMultiple;
	long    m_nDrawStyle;
	
	int		m_nRulerDirection;		//��ߵķ���0����߱�ע����/�ң�	1����߱�ע����/��

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
	long     m_nFrameShadow;
	//HorzDef
	LOGFONT   m_lfRulerScaleFont, m_lfRulerTitleFont;
	COLORREF  m_crHorzSawText,m_crHorzTitleColor;
	CPen	  *m_pSmallSawPen;
	int       m_nHorBigSawLenLen,m_nHorHalfSawLen,m_nHorSmallSawLen;

// Operations
public:
	void InitIt();
	void ContinueInit();
	void SetScaleOffset(double dVal)	{	m_dScaleOffset = dVal;		}
	double GetScaleOffset()				{	return m_dScaleOffset;		}
	
	//##################################################3
	//�߼�������ʵ�������ת��
private:
	double    m_dScaleOffset;    //�̶ȱ�ʾ��ƫ��
	double	m_dOneHorGapValue;
	int		m_nCenterLogInDv;

protected:
	double m_dAxisScaleRate;  //����̶ȵı��������ʱ����е���
	CString m_strOldRulerName;
	void AdjustAxisName_Time();

public:
	void	InitHorzRulerAttr();
	void	GetAxisInterface(double& dCoef , int& nCenterLog) { dCoef = m_dOneHorGapValue;  nCenterLog = m_nCenterLogInDv;	}

private:
	double GetFloatCarryVal(double fVal);
	double MakeFloatGapValLegal(double fVal,double &lVal);//float fVal,int &lVal
	
	
public:	//++++++++++++++X �����ӿ�����
	double		m_dRulerHorOneGap;
	CString		m_strRulerName;
	void InitRulerDef();
	void ResetRulerDef();

	void SetRulerName(const CString &strName)
	{
		m_strRulerName = strName;
		m_strOldRulerName = strName;
		m_dAxisScaleRate = 1;
	}
	
	//##########################################################################
	//����ˮƽ��ߵ���������ֵ��Χ��س�Ա������
public:
	CRect	m_rectRuler;
	double	m_dHorMinValue;
	double	m_dHorMaxValue;
	double  m_dHorOldMinValue;
	double  m_dHorOldMaxValue;
	double	m_dHorCarryOneGap;
	int	m_nBOTTOMADD;
	
	void	ModifyRulerArea(CRect rectRuler);
	CRect	GetRulerArea();
	void	GetRulerMaxMinValue(double *dMinValue,double *dMaxValue);
	void	SetRulerMaxMinValue(double dMinValue,double dMaxValue);
	void	GetOldRulerMaxMinValue(double *dMinValue,double *dMaxValue);
	void	SetOldRulerMaxMinValue(double dMinValue,double dMaxValue);
	double	GetHorCarryOenGap();
	
	
	//////��ߵĻ��ơ�����
	CAxisScaleDataList       m_listRulerScale;
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

	//��������
	void SetBorder(long left,long top,long right,long bottom);
	void SetBorder(CRect rcBorder)    {    ModifyRulerArea(rcBorder);    }
	CRect GetBorder()                 {    return m_rectRuler;           }
//	void ZoomIn(float fRate);
//	void ZoomOut(float fRate);
//	void Move(float fOffset);
	
	CAxisScaleData* GetFirstAxisData(POS &pos);
	CAxisScaleData* GetNextAxisData(POS &pos);
	

	void	DrawIt(CDC *pDC);
	
	void DrawOneRulerHorSawtooth(CDC *pDC,	CPoint cBegin,CPoint cEnd);
	void DrawOneRulerHorSawtoothShadow(CDC *pDC,CPoint cBegin,CPoint cEnd);
	void DrawLine(CDC *pDC,int left,int top,int right,int bottom,CPen *pPen);
	void DrawRulerShadowVertLine(CDC *pDC,int iLeft,int iTop,int iLen,COLORREF crColor1,COLORREF crColor2);
	void DrawRulerHor(CDC *pDC);
	void DrawRulerHorFrame(CDC*pDC);
	void DrawRulerHorLine(CDC *pDC,CAxisScaleData *pScaleData);
	void DrawRulerHorName(CDC*);
	void DrawRulerBack(CDC *pDC);

	//X������Ĵ�̶ȱ�ע֮��ļ���ռ�(���)��Сֵ
	long GetMinSawGapWidth(long *nValue);
	long SetMinSawGapWidth(long nValue);
	//��ߵ����� 0��ˮƽ��ߣ�  1����ֱ���
	long GetRulerType(long *nValue);
	long SetRulerType(long nValue);
	void SetRulerTypeHorz()
	{
		SetRulerType(g_nRulerType_Horz);
	}
	void SetRulerTypeVert()
	{
		SetRulerType(g_nRulerType_Vert);
	}
	//��ߵ����̶���
	long SetMaxUnitCount(long nValue);
	long GetMaxUnitCount(long *nValue);
	//����ϵͳ�Ļ�������,2005.08.12���
	long SetDrawStyle(long nValue);
	long GetDrawStyle(long *nValue);
	long SetDrawStyleBit(long nValue);
	long ClearDrawStyleBit(long nValue);
	
	//��߱�ע����ģʽ��0=��ע�ڿ̶��ұߣ�1=��ע�ڿ̶��·�����
	long SetScaleTextDrawStyle(long nValue);
	long GetScaleTextDrawStyle(long *nValue);
	//��������⼰�����塢��ɫ
	long SetRulerTitle(BSTR bstrValue);
	long GetRulerTitle(BSTR *pbstrValue);
	long SetRulerTitleFont(LOGFONT lfFont);
	LOGFONT GetRulerTitleFont();
	long SetRulerTitleFontColor(long nValue);
	long GetRulerTitleFontColor(long *nValue);
	
	//��߱���ɫ
	long SetRulerBackColor(long nValue);
	long GetRulerBackColor(long *nValue);
	//��߱߿����ɫ
	long SetFrameLeftTopColor(long nValue);
	long GetFrameLeftTopColor(long *nValue);
	long SetFrameRightBottomColor(long nValue);
	long GetFrameRightBottomColor(long *nValue);
	//��߱߿�߽���Ӱ
	long SetFrameShadow(long nValue);
	long GetFrameShadow(long *nValue);
	
	//��ߵ�λ�̶���ɫ
	long SetUnitScaleColor(long nValue);
	long GetUnitScaleColor(long *nValue);
	//��ߵ�λ�̶���Ӱ��ɫ
	long SetUnitScaleShadowColor(long nValue);
	long GetUnitScaleShadowColor(long *nValue);
	//��߿̶ȵ�����
	long SetRulerScaleFont(LOGFONT lfFont);
	LOGFONT GetRulerScaleFont();
	//��߿̶�������ɫ
	long SetRulerScaleFontColor(long nValue);
	long GetRulerScaleFontColor(long *nValue);
	//���1/10�̶Ȼ�����ɫ
	long SetRulerTenthScaleColor(long nValue);
	long GetRulerTenthScaleColor(long *nValue);
	//�����������Ŀ��/�߶�
	long SetRulerAreaWidth(long nValue);
	long GetRulerAreaWidth(long *nValue);
	//��ߵ�λ�̶ȳ���
	long SetRulerUnitScaleLineLen(long nValue);
	long GetRulerUnitScaleLineLen(long *nValue);
	//���1/2�̶ȳ���
	long SetRulerHalfScaleLineLen(long nValue);
	long GetRulerHalfScaleLineLen(long *nValue);
	long SetRulerHalfScaleShow(long nValue);
	//���1/10�̶ȳ���
	long SetRulerTenthScaleLineLen(long nValue);
	long GetRulerTenthScaleLineLen(long *nValue);
	long SetRulerTenthScaleShow(long nValue);
	//�߽�
	long SetRulerBoderShow(long nValue);
	//��ɫ
	long SetDrawBack(long nValue);
	
	//�߼��������豸����֮���ת��
	void LogicPointToDevicePoint(double dValue,long *nValue);
    void LogicPointToDevicePoint(double dValue,int *nValue);
    void DevicePointToLogicPoint(long nValue,double *dValue);
	
	//���귶Χ
	long SetMinMaxVal(double Min,double Max,long nReserved);
	long GetMinMaxVal(double *Min,double *Max,long nReserved);
	
	//���¼�������ϵͳ�Ŀ̶�
	long ResetAxis();
	
	//��ͼ
	void DrawAxis(CDC *pDC,float fZoomRatio,long xOffset,long yOffset)
	{
		DrawIt(pDC);
	}
	
	//�Ŵ���С
	void ZoomIn(float fRate);
	void ZoomOut(float fRate);
	void Move(float fOffset);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULERAXIS_H__B5B4081E_AF13_4BE4_AA54_869EDCF04B3F__INCLUDED_)
