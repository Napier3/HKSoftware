// PowerDrawBaseClass.h: interface for the CPowerDrawBaseClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWBASECLASS_H__95DE7D16_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_)
#define AFX_POWERDRAWBASECLASS_H__95DE7D16_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define POWERADVANCE_PICK_RADIUS	2
#include "math.h"
#include "PDBaseObject.h"
#include "PDApi.h"

#define POWERADVANCE_UNIT_DRAW_MODE_NORMAL	0X001
#define POWERADVANCE_UNIT_DRAW_MODE_PICKED	0X002


class CPowerPointValue 
{
public:
	double dX,dY;
	CPowerPointValue();
	~CPowerPointValue();
};
class CPointValueObject : public CObject
{
public:
	double dX,dY;
	int	iIndex;
	CPointValueObject();
	~CPointValueObject();
};
class CAxisReference
{
public:
	CPoint	m_ptCenterLogInDv;	////�߼������ԭ�����豸�����ϵ�����ֵ
	double	m_fOneYGapValue;		///////Y��ʵ��������ʵ��ֵ�ı���
	double	m_fOneXGapValue;		///////X��ʵ��������ʵ��ֵ�ı���
	CAxisReference();
	~CAxisReference();
};

////////////////////����ֱ�ߺ�������������
/*
	ֱ�ߵ�����	
		iType=0			����ֱ��	y=k*x+b
		iType=1			k->��		x=b
*/
class CLineFunction : public CPDBaseObject
{
public:
	int		iType;		//ֱ�ߵ�����
	double	fCoefK;		//ֱ�ߵ�б�� k
	double	fSlantAngle;//ֱ�ߵ���б��
	double	fConstB;	//ֱ�ߵĳ��� b
	double	fbx,fby;	//ֱ�ߵ���ʼ��
	double	fex,fey;	//ֱ�ߵ���ֹ��
	void   InitIt();
	CLineFunction();
	~CLineFunction();
	void	SetCoefKByAngle(double fAngle,double fx,double fy);
};
class CPowerDrawBaseClass : public CPDBaseObject  
{
public:
	DECLARE_DYNCREATE(CPowerDrawBaseClass)

	CString strClassName;

//	CAxisReference axisReference;
public:
	unsigned long	m_ulColor;
	UINT		m_uiLineStyle;
	int			m_iLineWidth;

	unsigned long	m_ulPickColor;
	UINT		m_uiPickLineStyle;
	int			m_iPickLineWidth;
	void Init();

	int		m_iDrawModal;        ////0,normal  ; 1=>picked  ...
	////ѡ�еı�־
	int		m_iOldDrawModal;

public:
	CPowerDrawBaseClass();
	CPowerDrawBaseClass(CString strClass);
	CPowerDrawBaseClass(unsigned long color,UINT lineStyle,int iWidth);
	virtual ~CPowerDrawBaseClass();

	void    LogicPointToDevicePoint(CPoint *ptDevice,double fx,double fy,CAxisReference *axisReference);
	virtual BOOL InitOwnDataByString(CString strOwnData);
	virtual BOOL ContinueInitIt(CAxisReference *axisReference);
	virtual CPowerDrawBaseClass* DirectGetNewObject();
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString GetExportTextString(void);
	virtual CString  GetDisplayDataString(void);

	virtual BOOL PickIt(CPoint point);
	virtual void  BeforePrinting(double fMMValue);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

	/////////////��ȡֱ����ͼ�εĽ���
	//��ڲ�����ֱ�߷���	//���ز�����ֱ����ͼ�εĽ���ָ�롢����ĸ���
	virtual void GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);

	virtual void OnColorChanged(COLORREF color);	//����ͼԪ����ɫ�ı�
};

#endif // !defined(AFX_POWERDRAWBASECLASS_H__95DE7D16_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_)
