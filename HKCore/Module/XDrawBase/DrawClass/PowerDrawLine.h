// PowerDrawLine.h: interface for the CPowerDrawLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERDRAWLINE_H__95DE7D17_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_)
#define AFX_POWERDRAWLINE_H__95DE7D17_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PowerDrawBaseClass.h"



class CPowerDrawLine : public CPowerDrawBaseClass  
{
public:
	DECLARE_DYNCREATE(CPowerDrawLine)
public:
	/////////��ͼ�ж�Ӧ�ĵ�����
	CPoint	m_pointBegin;
	CPoint	m_pointEnd;
	/////////��ͼ�ж�Ӧ�ĵ�����������ֵ
	CPowerPointValue	m_pvBegin;
	CPowerPointValue	m_pvEnd;
public:
	BOOL PickLine(CPoint curPoint);
	double GetLineAngle();
	CRect	GetMinRectBOX();
public:
	void Draw(CDC *pDC);

public:
	void Init();
	void InitPowerLine(CPoint pointBegin,CPoint pointEnd);
	CPowerDrawLine(CPoint pointBegin,CPoint pointEnd);
	CPowerDrawLine();
	void	SetPicked(BOOL bPicked=FALSE);
	virtual ~CPowerDrawLine();
	CPowerDrawLine(CString strClass);

	virtual BOOL InitOwnDataByString(CString strOwnData);
	virtual BOOL ContinueInitIt(CAxisReference *axisReference);
	virtual CPowerDrawBaseClass* DirectGetNewObject();
	virtual void DrawIt(CDC *pDC,BOOL bSel=FALSE,double fZoomRatio=1,CPoint ptOffset=CPoint(0,0));
	virtual CString GetExportTextString(void);
	virtual CString  GetDisplayDataString(void);
	virtual BOOL PickIt(CPoint point);
	virtual void GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);
	/////////////��ȡֱ����ͼ�εĽ���
	//��ڲ�����ֱ�߷���
	//���ز�����ֱ����ͼ�εĽ���ָ�롢����ĸ���
	BOOL IsPointTheJustPoint(CLineFunction*pLF,double fx,double fy);
	virtual void GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal=0.05);
	virtual void GetIntersectPV2(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect);
	virtual void OnColorChanged(COLORREF color);	//����ͼԪ����ɫ�ı�

	//////////////��������ߺ���
	double GetLineAngleVal();	//���ֱ�ߵ����		2001��11��11��
	double GetLineLength();		//���ֱ�ߵĳ���		2001��11��11��
	CString GetErrorLineString(CPointValueObject*ppvo1,CPointValueObject*ppvo2);
	CPowerDrawLine*GetErrorLine(double fErrorVal);	//��ô�ֱ�ߵ�ƫ��ֱ��
	CLineFunction*GetLineFunction();				//��ô�ֱ�ߵķ���
};

#endif // !defined(AFX_POWERDRAWLINE_H__95DE7D17_28DC_11D5_B09F_C8B1C1DA7A70__INCLUDED_)
