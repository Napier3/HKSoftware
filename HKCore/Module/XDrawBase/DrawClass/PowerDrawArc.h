// PowerDrawArc.h: interface for the CPowerDrawArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWARC_H__781122E0_2C5C_11D5_B0A0_0050BA40BBF3__INCLUDED_)
#define AFX_POWERDRAWARC_H__781122E0_2C5C_11D5_B0A0_0050BA40BBF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PowerDrawBaseClass.h"

class CPowerDrawArc : public CPowerDrawBaseClass  
{
public:
	DECLARE_DYNCREATE(CPowerDrawArc)

public:
	CPoint pt1,pt2,pt3;       ///pt2  Բ�����м��

	CPowerPointValue	m_ppv1,m_ppv2,m_ppv3;

	CPowerPointValue m_ppvBegin,m_ppvEnd;

	double	fCenterX,fCenterY;
	double	fRadius;

	double	fBeginAngle,fEndAngle;

	int  m_iRadiusX,m_iRadiusY;
	CPoint m_ptCenter;
	CPoint m_ptBegin,m_ptEnd;

	////////Բ����ʰȡ
	CRect	GetBox();
	BOOL	PickArc(CPoint point);
	double	GetPickPointAngle(CPoint pt);
	void	SetPicked(BOOL bPicked=FALSE);
public:
	BOOL	SetArcPoints(CPoint p1,CPoint p2,CPoint p3);
	BOOL	SetArcValues(CPowerPointValue	ppv1,CPowerPointValue	ppv2,CPowerPointValue	ppv3);
	void	Draw(CDC *pDC,int m_DrawMode,int m_DrawMode1,unsigned long ululBKColor);
public:
	CPowerDrawArc();
	CPowerDrawArc(CString strClass);
	virtual ~CPowerDrawArc();

	virtual BOOL InitOwnDataByString(CString strOwnData);
	virtual BOOL ContinueInitIt(CAxisReference *axisReference);
	virtual CPowerDrawBaseClass* DirectGetNewObject();
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString GetExportTextString(void);
	virtual CString  GetDisplayDataString(void);
	virtual BOOL PickIt(CPoint point);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);
	int GetQuadrant(double fx,double fy);

	double GetTheAngle(double f1,double f2,double fr);
	double GetIntPVAngle(double fx,double fy);
	/////////////��ȡֱ����ͼ�εĽ���
	//��ڲ�����ֱ�߷���
	//���ز�����ֱ����ͼ�εĽ���ָ�롢����ĸ���
	virtual void GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	BOOL IsPointTheJustPoint(CLineFunction*pLF,double fx,double fy);
	BOOL IsIntersectPTOnArc(double fx,double fy);
	virtual void OnColorChanged(COLORREF color);	//����ͼԪ����ɫ�ı�

	//���������㺯��
	CPowerDrawArc*GetErrorArc(double fErrorVal);		//���ƫ�ƺ���������
	CString GetErrorArcString(CPointValueObject*ppvo1,CPointValueObject*ppvo2,BOOL bIner=FALSE);
	virtual void GetIntersectPV2(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,BOOL bIner=FALSE,int iEndOrBegin=0);
};

#endif // !defined(AFX_POWERDRAWARC_H__781122E0_2C5C_11D5_B0A0_0050BA40BBF3__INCLUDED_)
