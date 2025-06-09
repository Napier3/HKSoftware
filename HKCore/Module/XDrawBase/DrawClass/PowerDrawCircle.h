// PowerDrawCircle.h: interface for the CPowerDrawCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWCIRCLE_H__77921201_29A2_11D5_B09F_0050BA40BBF3__INCLUDED_)
#define AFX_POWERDRAWCIRCLE_H__77921201_29A2_11D5_B09F_0050BA40BBF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PowerDrawBaseClass.h"
#include "PowerDrawArc.h"

//#include "PowerDrawLine.h"

class CPowerDrawCircleValue
{
public:
	double	dOffset;
	double	dAngle;
	double	dDiameter;
	//CPowerPointValue	m_ppvCenter;
	double dA,dB;

public:
	BOOL IsThisATrueCircle();
	CPowerDrawCircleValue();
	~CPowerDrawCircleValue();
};

class CPowerDrawCircle : public CPowerDrawBaseClass  
{
public:
	DECLARE_DYNCREATE(CPowerDrawCircle)

public:
	CPoint	m_ptCenter;	///ʵ�ʵ�Բ������
	int     m_iRadiusX,m_iRadiusY;
	double	m_dRadius;

	CPowerDrawArc pArcL,pArcR;
	CPowerDrawCircleValue m_pdcv;

	void	Draw(CDC *pDC);
	void	Draw(CDC *pDC,CRect rectBox);
public:	/////Բ��ѡȡ
	BOOL	PickCircle(CPoint curPoint);
	CRect	GetMinRectBOX();
	void	SetPicked(BOOL bPicked=FALSE);

	////ѡ�еı�־

public:
//	void	OnLButtonDown(CDC *pDC,UINT nFlags, CPoint point);

public:
	BOOL InitCircleByOnePoint(double fx,double fy);
	CPowerDrawCircle();
	CPowerDrawCircle(CString strClass);
	virtual ~CPowerDrawCircle();

	void EndIt();
	void InitIt();
	virtual BOOL InitOwnDataByString(CString strOwnData);
	virtual BOOL ContinueInitIt(CAxisReference *axisReference);
	virtual CPowerDrawBaseClass* DirectGetNewObject();
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString GetExportTextString(void);
	virtual CString  GetDisplayDataString(void);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

	virtual BOOL PickIt(CPoint point);

	/////////////��ȡֱ����ͼ�εĽ���
	//��ڲ�����ֱ�߷���
	//���ز�����ֱ����ͼ�εĽ���ָ�롢����ĸ���
	double GetPVAngle(double fx,double fy);	//���Բ��һ��ĽǶ�
	virtual void GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	void GetCircleIntersetPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	void GetArcIntersetPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	BOOL IsPointTheJustPoint(CLineFunction*pLF,double fx,double fy);
	virtual void OnColorChanged(COLORREF color);	//����ͼԪ����ɫ�ı�

	//��������ߵ���ȡ����
	CString	GetErrorString(double fOffVal);
};

#endif // !defined(AFX_POWERDRAWCIRCLE_H__77921201_29A2_11D5_B09F_0050BA40BBF3__INCLUDED_)
