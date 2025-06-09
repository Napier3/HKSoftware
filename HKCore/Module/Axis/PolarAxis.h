#if !defined(_POLARAXIS_H__)
#define _POLARAXIS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PolarAxis.h : header file
//
#include "AxisInterface.h"


#define		POLORAXIS_NAMEBUFFLEN	80
#define		POLORAXIS_AXISCOUNT		10

#define AXISTYPE_DESCARTES	0
#define AXISTYPE_POLOR		1
#define AXISTYPE_LOGARITHM	2

#define PI_180_RADIANTOANGLE	0.01745329	// 3.141592654/180
#define PI_180_ANGLETORADIAN	57.29577951	// 180/3.141592654


#define POLARAXISDRAW_ALL				0x000FFFFF
#define POLARAXISDRAW_WORKAREA			0x00000001	
#define POLARAXISDRAW_WORKAREAFRAME		0x00000002	
#define POLARAXISDRAW_AXISCENTER		0x00000004	
#define POLARAXISDRAW_AXISBODER			0x00000008	
#define POLARAXISDRAW_AXISTITLE			0x00000010	
#define POLARAXISDRAW_ANGLEUNIT_LINE	0x00000020	
#define POLARAXISDRAW_ANGLEUNIT_TEXT	0x00000040	
#define POLARAXISDRAW_CIRCLEUNIT		0x00000080	
#define POLARAXISDRAW_CIRCLEUNITTEXT	0x00001000	

//2022-5-14 lijunqing 
typedef struct _polar_vector_
{
public:
	char pszName[32];
	double dMag;
	double dAng;
	COLORREF crVector;//=RGB(0,0,0),
	int nLineWidth;//=1,
	unsigned int uiLineStyle;//=PS_SOLID,
	int nArrowLen;//=10,
	COLORREF crVectorTitle;//=RGB(0,0,0)
	
	void Init(char *p, long nWidth=3)
	{
		strcpy(pszName, p);

		if (pszName[1] == 'a')
		{
			crVector =RGB(255, 255, 0);
		}
		else if (pszName[1] == 'b')
		{
			crVector =RGB(0, 0, 255);
		}
		else if (pszName[1] == 'c')
		{
			crVector =RGB(255, 0, 0);
		}
		else
		{
			crVector =RGB(0, 0, 0);
		}

		nLineWidth = nWidth;
		uiLineStyle =PS_SOLID;
		nArrowLen=10;
		crVectorTitle=RGB(0,0,0);
	}

	void Init2(long nCh, long nWidth=3)
	{
		if (nCh == 0)
		{
			crVector =RGB(255, 255, 0);
		}
		else if (nCh == 1)
		{
			crVector =RGB(0, 0, 255);
		}
		else if (nCh == 2)
		{
			crVector =RGB(255, 0, 0);
		}
		else
		{
			crVector =RGB(0, 0, 0);
		}

		nLineWidth = nWidth;
		uiLineStyle =PS_SOLID;
		nArrowLen=10;
		crVectorTitle=RGB(0,0,0);
	}

}POLAR_VECTOR;

typedef struct _polar_vectors_
{
public:
	long nAxis;
	long nCount;
	long nEnable;
	POLAR_VECTOR *pArrVector;

	_polar_vectors_()
	{
		nAxis = 0;
		nCount = 0;
		nEnable = 1;
		pArrVector = NULL;
	}

	~_polar_vectors_()
	{
		Free();
	}

	void Free()
	{
		if (pArrVector != NULL)
		{
			free(pArrVector);
			pArrVector = NULL;
		}
	}

	void SetVectors(long n)
	{
		Free();

		if (n > 0)
		{
			pArrVector = (POLAR_VECTOR*)malloc(n * sizeof(POLAR_VECTOR));
			memset(pArrVector, 0, n * sizeof(POLAR_VECTOR));
		}

		nCount = n;
	}

	POLAR_VECTOR* GetAt(long nIndex)
	{
		if (nIndex < 0 || nIndex >= nCount)
		{
			return NULL;
		}

		return pArrVector + nIndex;
	}

	double get_max()
	{
		long k = 0;
		double dMax = 0;

		for (k=0; k<nCount; k++)
		{
			POLAR_VECTOR *p = pArrVector + k;
			dMax = dMax > p->dMag ? dMax : p->dMag;
		}

		return dMax;
	}

}POLAR_VECTORS;


typedef struct _polar_vectors_mngr_
{
public:
	long nCount;
	POLAR_VECTORS *pArrVectors;

	_polar_vectors_mngr_()
	{
		nCount = 0;
		pArrVectors = NULL;
	}

	~_polar_vectors_mngr_()
	{
		Free();
	}

	void Free()
	{
		if (pArrVectors != NULL)
		{
			free(pArrVectors);
			pArrVectors = NULL;
		}
	}

	void SetVectors(long nVal)
	{
		Free();

		if (nVal > 0)
		{
			pArrVectors = (POLAR_VECTORS*)malloc(nVal * sizeof(POLAR_VECTORS));
			memset(pArrVectors, 0, nVal * sizeof(POLAR_VECTORS));
		}

		nCount = nVal;
	}
	void SetVectors(long nIndex, long nVal)
	{
		POLAR_VECTORS *p = GetAt(nIndex);

		if (p != NULL)
		{
			p->SetVectors(nVal);
		}
	}
	POLAR_VECTORS* GetAt(long n)
	{
		if (n < 0 || n >= nCount)
		{
			return NULL;
		}

		return pArrVectors + n;
	}

}POLAR_VECTORS_MNGR;

/////////////////////////////////////////////////////////////////////////////
// CPolarAxis command target

class CPolarAxis : public CAxisInterface
{
public:
	CPolarAxis();
	virtual ~CPolarAxis();

public://CAxisInterface
// 	virtual void LogicPointToDevicePoint(double x, double y, CPoint *pPoint, long nAxisIndex=0) = 0;
// 	virtual void DevicePointToLogicPoint(const CPoint &point ,double *x,double *y, long nAxisIndex=0) = 0;
//	virtual void GetAxisDrawArea(CRect &rcArea) = 0;
//	virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax) =  0;
	virtual void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);//zhouhj 20210130 ���������������������Ƶ�
	virtual CRect GetWorkArea();
//	virtual void SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax);

#ifdef USE_AXIS_CONFIG
	virtual void SetAxisConfig(CDataGroup *pAxisConfig);
	virtual void GetAxisConfig(CDataGroup *pAxisConfig);
#endif

// Attributes
public:
	long	m_lAxisType;
	double	m_fOneYGapValue;
	double	m_fOneXGapValue;
	CPoint	m_ptCenterLogInDv;
	
	//���弫����Ļ���������Ϣ
	long	m_lZoomCoefficient;
	CRect	m_rectBorder;			//�������������������
	CRect	m_rectWorkArea;			//������Ļ�ͼ����
	int		m_iHorzMarginGapLeft;		//�����ˮƽ�հ�����
	int		m_iHorzMarginGapRight;
	int		m_iVertMarginGapTop;		//����Ĵ�ֱ�հ�����
	int		m_iVertMarginGapBottom;
	LOGFONT	m_lfAxisCenter;			//�����������ע����
	LOGFONT	m_lfVectorName;			//ʸ�������ƻ�������
	
	LOGFONT   m_lfPolarAxisTitleFont;	////��������������
	COLORREF  m_crPolarAxisTitleFont;	////����������������ɫ
	CString	  m_strPolarAxisTitle;		////���������
	
	long    m_lAxisDrawStyle;	//��ʾ����
	CPoint	m_ptAxisCenter;			//������������
	
	//������ɫ��Ϣ
	COLORREF	m_crAxisBackColor;	//������ĵ�ɫ
	COLORREF	m_crAxisWorkAreaBk;	//��������ɫ
	COLORREF	m_crAxisCenter;		//������������ɫ
	COLORREF	m_crAxisFrame;		//����߿���ɫ
	COLORREF    m_crFrameLeftTopColor;
	COLORREF    m_crFrameRightBottomColor;
	int		 m_iFrameShadow;	//�������߽���Ӱ
	unsigned int	m_uiCenterLineType;
	int				m_iCenterLineWidth;
	
	//������Ʊ���  
	int		m_iAxisDrawType;		//�����������	�Ƕȿ̶ȡ���ֵ�̶ȡ�������
	
	//����Ƕȿ̶���صĺ��������Ʊ���,�Ƕȿ̶��ߵ����͡���ɫ���߿����塢������ɫ
	int		  m_iAngleUnit;			      //�Ƕȿ̶ȵ�λ30��15��10��5
	long      m_lAngleUnitLineStyle;      //����
	COLORREF  m_crAngleUnitLineColor;     //�̶�����ɫ
	long      m_lAngleUnitLineWidth;	  //���
	LOGFONT   m_lfAngleUnitFont;		  //����
	COLORREF  m_crAngleUnitFontColor;	  //������ɫ
	
	//�����ֵ�̶���صĺ���������Ʊ���
	long      m_lCircleUnitLineStyle;
	COLORREF  m_crCircleUnitLineColor;
	long    m_lCircleUnitLineWidth;
	int		m_iCircleGridCounts;	//��ֵ�̶�����ĸ���
	int		m_iCircleAxisCount;		//��ֵ�̶ȵ�������� 0~10 ��
	double	m_fCircleUnitValue[POLORAXIS_AXISCOUNT];	//�������ֵ�̶ȵ�����
	double	m_fCircleValOneGap[POLORAXIS_AXISCOUNT];	//��λ�߼������Ӧ��ʵ�ʷ�ֵ��С
	char	m_ppszCircleUnitName[POLORAXIS_AXISCOUNT][POLORAXIS_NAMEBUFFLEN];	//���������
// Operations
public:
	void	InitIt();
	void    AssertCircleGridCounts()
	{
		if (m_iCircleGridCounts<=0)
		{
			m_iCircleGridCounts = 1;
		}

		if (m_iCircleGridCounts > POLORAXIS_AXISCOUNT) 
		{
			m_iCircleGridCounts = POLORAXIS_AXISCOUNT;	
		}
	}
	
	void	SetZoomCoefficient(long lVal);
	long	GetZoomCoefficient();
	void	SetPolarAxisBorder(CRect rectBorder);
	CRect	GetPolarAxisBorder();
	CRect	GetPolarAxisWorkArea();
	CPoint	GetPolarAxisCenterPoint();
	void	SetMarginGap(int iHorzGapLeft=30,int iVertGapTop=10,int iHorzGapRight=30,int iVertGapBottom=10);
	long    GetMarginGap(int iHorzGapLeft,int iVertGapTop,int iHorzGapRight,int iVertGapBottom);
	void	ResetPolarAxis();
	void	ResetPolarAxis(int iCircleUnitIndex);
	long	GetXAxisType();
	void	SetXAxisType(long lType);
	
	void SetAxisBackColor(COLORREF color);
	COLORREF GetAxisBackColor();
	void SetWorkAreaBkColor(COLORREF color);
	COLORREF GetWorkAreaBkColor();
	void SetAxisCenterColor(COLORREF color);
	COLORREF GetAxisCenterColor();
	void SetAxisFrameColor(COLORREF color);
	COLORREF GetAxisFrameColor();
	void SetAngleUnitFontColor(COLORREF color);
	COLORREF GetAngleUnitFontColor();
	void SetAxisDrawType(long lVal);
	long GetAxisDrawType();
	void SetCenterLineType(long lVal);
	long GetCenterLineType();
	void SetCenterLineWidth(long lVal);
	long GetCenterLineWidth();
	void SetAngleUnitLineColor(COLORREF color);
	COLORREF GetAngleUnitLineColor();
	
	//����Ƕȿ̶���صĺ��������Ʊ���
	void	SetAngleUnit(int iAngleUnitIndex);	//0=5;1=10;2=15;3=30
	int		GetAngleUnit();
	
	//�����ֵ�̶���صĺ���������Ʊ���
	void	SetCircleGridCounts(int iCircleGridCounts);	//���÷�ֵ�̶�����ĸ���
	int		GetCircleGridCounts();	//��÷�ֵ�̶�����ĸ���
	
	void	SetCircleAxisCounts(int iCircleAxisCount);	//����������������
	int		GetCircleAxisCounts();	//���������������
	void	SetCircleUnitValue(int iUnitIndex,double fUnitVal);	//���õ�����ֵ����ķ�ֵ
	double	GetCircleUnitValue(int iUnitIndex);		//��õ�����ֵ����ķ�ֵ
	void	SetCircleUnitValue(double fUnitVal[POLORAXIS_AXISCOUNT]);	//���÷�ֵ����ķ�ֵ
	int 	GetCircleUnitValue(double fUnitVal[POLORAXIS_AXISCOUNT]);	//��÷�ֵ����ķ�ֵ�����ط�ֵ����ĸ���
	
	//#########################################################
	//���弫������ܵĶ���ӿں���
	void	DrawWorkArea(CDC *pDC);	//���Ʊ߿�
	void	DrawWorkAreaFrame(CDC *pDC);	//���Ʊ߿�
	void	DrawAxisBackGround(CDC *pDC);	//������ĵ�ɫ
	void	DrawAxisBoder(CDC *pDC);	//������ĵ�ɫ
	void    DrawAxisTitle(CDC *pDC,float fZoomRatio,CPoint ptOffset);
	
	void	DrawIt(CDC*pDC);		//�ܵĻ��ƽӿ�
	
	void	DrawTheVector(CDC*pDC,int iCircleUnitIndex,double fRadius,double fAngle,CString strVectorName,COLORREF crVector=RGB(0,0,0),int iLineWidth=1,unsigned int uiLineStyle=PS_SOLID,int iArrowLen=10,COLORREF crVectorTitle=RGB(0,0,0));//����һʸ��ͼ
	void	DrawTheVector(CDC*pDC,int iCircleUnitIndex,double fRadius1,double fAngle1,double fRadius2,double fAngle2,CString strVectorName,COLORREF crVector=RGB(0,0,0),int iLineWidth=1,unsigned int uiLineStyle=PS_SOLID,int iArrowLen=10,COLORREF crVectorTitle=RGB(0,0,0));//����һʸ��ͼ
	void	DrawTheVector(CDC*pDC,int iCircleUnitIndex,double fRadius1,double fAngle1,double fRadius2,double fAngle2,double *fRadiusL,double *fAngleL,CString strVectorName,COLORREF crVector=RGB(0,0,0),int iLineWidth=1,unsigned int uiLineStyle=PS_SOLID,int iArrowLen=10,COLORREF crVectorTitle=RGB(0,0,0));//����һʸ��ͼ

	//2022-5-14  lijunqing
	void   DrawTheVector(CDC *pDC, int iCircleUnitIndex, POLAR_VECTOR *pVector);
	void   DrawTheVector(CDC *pDC, POLAR_VECTORS *pVectors);
	void   DrawTheVector(CDC *pDC, POLAR_VECTORS_MNGR *pVectorsMngr);
	
	void	DrawCircle(CDC *pDC,int iCircleUnitIndex,double *pfRadius,long nCircles,COLORREF crCircle,long nLineStype=PS_SOLID,long lLineWidth=1);
	
	void	DrawAngleUnit(CDC*pDC);	//���ƽǶȿ̶�
	void	DrawCircleUnit(CDC*pDC);//���Ʒ�ֵ�̶�
	void	DrawAxisCenter(CDC*pDC);//����������
	
	virtual void	LogicPointToDevicePoint(double fRadius,double fAngle,CPoint *pPoint,long iCircleUnitIndex=0);	//���߼�����ת��Ϊʵ������
	virtual void	DevicePointToLogicPoint(const CPoint &point,double *fRadius,double *fAngle,long iCircleUnitIndex=0);//��ʵ�������ȡʵ�������������ֵ
    virtual void LogicPointToDevicePoint(double fVal, long *nVal, long nAxisIndex=0);
    virtual void DevicePointToLogicPoint(long nVal ,double *fVal, long nAxisIndex=0);
    virtual void GetAxisDrawArea(CRect &rcArea);
    virtual void GetAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);

	void ResetRuler();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	//##############################�ӿڶ���#####################################################
public:
	//��ȡ����ϵ�Ļ�ͼλ��
	long GetPosition(long *left, long *top, long *right, long *bottom);
//	//��ȡ����ϵͳ�Ĺ�������������ϵͳ���귶Χ��ʾ����Ч����
//	long GetWorkArea(long *left, long *top, long *right, long *bottom);
//	//���߼�����ת��Ϊ�豸����:ptx,ptyΪ�豸����
//	long LogicPointToDevicePoint(double x,double y,long *ptx,long *pty);
//	//���豸����ת��Ϊ�߼�����:ptx,ptyΪ�豸����
//	long DevicePointToLogicPoint (long ptx,long pty ,double *x,double *y);

	//����ϵͳ�Ļ�������,2005.08.12���
	long SetAxisDrawStyle(long nValue)		{		m_lAxisDrawStyle = nValue;	return m_lAxisDrawStyle;	}
	long GetAxisDrawStyle(long *nValue)		{		return m_lAxisDrawStyle;			}
	long SetAxisDrawStyleBit(long nValue);
	long ClearAxisDrawStyleBit(long nValue);
	
	//��������⼰�����塢��ɫ
    long SetAxisTitle(const CString &bstrValue)  {   m_strPolarAxisTitle = bstrValue;  return 0;   }
	CString GetAxisTitle()                       {   return m_strPolarAxisTitle;     }
	long SetAxisTitleFont(LOGFONT lfFont);
	LOGFONT GetAxisTitleFont();
	long SetAxisTitleFontColor(long nValue);
	long GetAxisTitleFontColor(long *nValue);
	
	//����ϵͳ�ı���ɫ
	long SetAxisBackColor(long nValue);
	long GetAxisBackColor(long *nValue);
	//����ϵͳ��������ɫ
	long SetWorkAreaBkColor(long nValue);
	long GetWorkAreaBkColor(long *nValue);
	//����ϵͳ�߿����ɫ
	long SetFrameLeftTopColor(long nValue);
	long GetFrameLeftTopColor(long *nValue);
	long SetFrameRightBottomColor(long nValue);
	long GetFrameRightBottomColor(long *nValue);
	//����ϵͳ�߿�߽���Ӱ
	long SetFrameShadow(long nValue);
	long GetFrameShadow(long *nValue);
	
	//�Ƕȿ̶��ߵ����͡���ɫ���߿����塢������ɫ
	void SetAngleUnitLineStyle(long nValue);
	long GetAngleUnitLineStyle();
	long SetAngleUnitLineColor(long nValue);
	long GetAngleUnitLineColor(long *nValue);
	long SetAngleUnitLineWidth(long nValue);
	long GetAngleUnitLineWidth(long *nValue);
	long SetAngleUnitFont(LOGFONT lfFont);
	LOGFONT GetAngleUnitFont();
	long SetAngleUnitFontColor(long nValue);
	long GetAngleUnitFontColor(long *nValue);
	
	//Բ(��ֵ)�̶��ߵ����͡���ɫ���߿�
	long SetCircleUnitLineStyle(long nValue);
	long GetCircleUnitLineStyle(long *nValue);
	long SetCircleUnitLineColor(long nValue);
	long GetCircleUnitLineColor(long *nValue);
	long SetCircleUnitLineWidth(long nValue);
	long GetCircleUnitLineWidth(long *nValue);
	
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
	long SetAngleUnitID(long nValue)         {    SetAngleUnit(nValue);  return 0;  };
	long GetAngleUnitID(long *nValue);
	long SetCircleAxisCounts(long nValue);
	long GetCircleAxisCounts(long *nValue);
	long SetCircleUnitValue(double dValue,long nCircleAxisID);
	long GetCircleUnitValue(double *dValue,long nCircleAxisID);
	
	//��������
    inline long SetBorder(long left, long top, long right, long bottom)
	{
		SetPolarAxisBorder(CRect(left, top, right, bottom));
		return 0;
	}
    inline long SetBorder(CRect rcBoder)
	{
		SetPolarAxisBorder(rcBoder);
		return 0;
	}
    long GetBorder(long *left, long *top, long *right, long *bottom);
	long GetWorkArea(long *left, long *top, long *right, long *bottom);
	long SetMarginGap(long nLeftGap, long nTopGap, long nRightGap, long nBottomGap);
	long GetMarginGap(long *nLeftGap, long *nTopGap, long *nRightGap, long *nBottomGap);
	
	//���¼�������ϵͳ�Ŀ̶�
	long ResetAxis()       {        ResetPolarAxis();    return 0;   }
	
	//��ͼ
	void DrawAxis(CDC *pDC)
	{
		DrawIt(pDC);
	}
	long DrawVector(CDC *pDC,long nUnitIndex,double fRadius,double fAngle,const CString &strVectorName,long crVector,long nLineWidth,long nLineStyle,long nArrowLen,long crVectorTitle,float fZoomRatio,long xOffset,long yOffset)
	{
		DrawTheVector(pDC,nUnitIndex, fRadius, fAngle,strVectorName,crVector,nLineWidth,nLineStyle,nArrowLen,crVectorTitle);
		return 0;
	}
	long DrawVectorEx(CDC *pDC,long nUnitIndex,double dRadius1,double dAngle1,double dRadius2,double dAngle2,const CString &strVectorName,long crVector,long nLineWidth,long nLineStyle,long nArrowLen,long crVectorTitle,float fZoomRatio,long xOffset,long yOffset)
	{
		DrawTheVector(pDC, nUnitIndex, dRadius1, dAngle1, dRadius2, dAngle2,strVectorName
			,crVector,nLineWidth,nLineStyle,nArrowLen,crVectorTitle);
		return 0;
	}
	long DrawVectorEx2(CDC *pDC,long nUnitIndex,double dRadius1,double dAngle1,double dRadius2,double dAngle2,double *dRadiusL,double *dAngleL,const CString &strVectorName,long crVector,long nLineWidth,long nLineStyle,long nArrowLen,long crVectorTitle,float fZoomRatio,long xOffset,long yOffset)
	{
		DrawTheVector(pDC, nUnitIndex, dRadius1, dAngle1, dRadius2, dAngle2, dRadiusL, dAngleL
			,strVectorName, crVector, nLineWidth, nLineStyle, nArrowLen, crVectorTitle);
		return 0;
	}
	void GetTheVector(double fRadius1,double fAngle1,double fRadius2,double fAngle2,double *fRadiusL,double *fAngleL);
	long DrawCircle(CDC *pDC,long nUnitIndex,double dRadius,long crCircle,long nLineStype,long nLineWidth,float fZoomRatio,long xOffset,long yOffset)
	{
		CPoint pt(xOffset,yOffset);
		DrawCircle(pDC, nUnitIndex, &dRadius, m_iCircleAxisCount, crCircle, nLineStype, nLineWidth);
	}
	
	//�Ŵ���С
	void ZoomIn(float fRate);
	void ZoomOut(float fRate);
};

#endif // !defined(_POLARAXIS_H__)
