//CharacterDrawPng.h  CCharacterDrawPng

#pragma once

#include "../../../Module/XDrawBase/XDrawViewBase.h"
#include "Characteristics.h"

class CCharacterDrawPng : public CXDrawViewBase
{
public:
	CCharacterDrawPng();
	virtual ~CCharacterDrawPng();

//���غ���
public:
 	virtual UINT GetClassID() {    return CHARCLASSID_CCHARDRAWVIEW;   }

	BOOL SetViewTestLines(BOOL b=TRUE)	{	m_bViewTestLines = b;	}
	CXDrawPoint* GetCurTestPoint(){return m_pCurrTestPoint;}//zhouhj 20210824 ��ȡ��ǰ���Ե�
	CXDrawList* GetXDrawElementsForTemp(){return &m_oXDrawElementsForTemp;}//zhouhj 20210129 �ⲿ���Ե����ݣ���ʱ���ڴ˴�

	void SetAxis(const CString &strAxis=AXIS_TYPE_ID_CARTES)	{	m_strAxis = strAxis;	}
    CXDrawMngr* GetXDrawMngr_Axis() {   return m_pXDrawMngr_Axis; }
protected:
	CXDrawPoint            *m_pCurrTestPoint;//zhouhj 20210825 ��������ʹ��
	CXDrawMngr *m_pXDrawMngr_Axis;    //��ͼ��������ϵ

	//2021-9-17  lijunqing  Ĭ��ȱʡ������ϵ����û���������ߵ������ʹ��
	CString  m_strAxis;

//˽�г�Ա����
private:
	BOOL m_bViewTestLines;
	BOOL m_bCalCharTemp;  //2020-03-11  lijq
	CCharacteristic *m_pCharacteristic;
	CCharacteristics       *m_pCharacteristics;
	BOOL                   m_bDrawCurrTestPoint;

	//lijq 20200304 -- ���ڲ�����ʱ�Ե�ͼ�δ�����
	CXDrawList m_oXDrawElementsForTemp;

//˽�г�Ա�������ʷ���
public:
	void UpdateCurrTestPoint(double dX, double dY);
	void FreeCurrTestPoint();

	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd, BOOL bViewTestLines, BOOL bCalCharTemp);
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);

protected:
	virtual void InitCharDrawView(CCharacteristic *pCharTemp, CWnd *pParentWnd);
	
	void CreateXDrawMngr(CCharacteristic *pCharTemp);
	void CreateXDrawMngr(const CString &strAxis);

//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);

	//2021-9-7  lijunqing
	virtual void GetAxisInterface(CAxisInterface **ppAxisInterface);

public:
	virtual CSize Layout(CPoint &ptTopLeft);
	virtual CSize CalLayout(CSize &szDraw);

public:
	virtual BOOL HasDefChar();
	virtual BOOL HasDefChar(CCharacteristic *pCharTemplate);
	virtual void SetBorder(const CRect &rcBorder, CDC *pDC);

	virtual long DevicePointToLogicPoint (long ptx,long pty ,double *x,double *y);//zhouhj 20210130 ����������˫������㣬�ı�λ��ʱת��ʹ��
	void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);

	CRect GetBorder();


protected:
	void xdraw_TestSolvingEquation();

public:
	virtual void ZoomIn(double dCoef=2.0);
	virtual void ZoomOut(double dCoef=2.0);
	virtual void ZoomReset(double dCoef=2.0);
	virtual void MoveLeft(double dCoef=0.2);
	virtual void MoveRight(double dCoef=0.2);
	virtual void MoveUp(double dCoef=0.2);
	virtual void MoveDown(double dCoef=0.2);
	virtual void CalAxisMinMax(double &dXMin, double &dYMin, double &dXMax, double &dYMax);
 
	//2021-10-28  lijunqing   ����ƶ�ͼ��
	virtual void MouseMove_SetBegin(CPoint &ptBegin);
	virtual void MouseMove_MoveTo(CPoint &point);

protected:
	CPoint m_ptMouseMoveBegin;
};

BOOL char_view_WriteBitmapFile(CCharacteristic *pCharTemplate, long nWidth, long nHeight, const CString &strFile);
