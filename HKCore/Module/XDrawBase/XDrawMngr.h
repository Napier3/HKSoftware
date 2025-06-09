//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDrawMngr.h  CXDrawMngr

#pragma once

#include "XDrawList.h"
#include "../BaseClass/MemBufferDC.H"
#include "../API/MathApi.h"

class CXDrawMngr : public CExBaseList
{
public:
	CXDrawMngr();
	virtual ~CXDrawMngr();

	CString  m_strAxis;
	double  m_fXMax;
	double  m_fYMax;
	double  m_fXMin;
	double  m_fYMin;

	BOOL  m_bXMin;
	BOOL  m_bXMax;
	BOOL  m_bYMin;
	BOOL  m_bYMax;

	void InitXDrawMngr();
	void InitDrawLineColor(const COLORREF &oColor);//zhouhj 20210202 ��ʼ���������������õ���ɫ
//���غ���
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual BOOL IsEqualOwn(CBaseObject* pObj);
// 	virtual BOOL CopyOwn(CBaseObject* pDest);
// 	virtual CBaseObject* Clone();
// 	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
// 	CXDrawList* FindByID(const CString &strID);
	CXDrawList* AddNew(const CString &strID);
	CXDrawList* AddNewByFile(const CString &strFile);

//////////////////////////////////////////////////////////////////////////
//��ͼ����
protected:
	UINT m_n_CURSOR_ZOOM;

	CRect m_rcBorder;

#ifndef XDrawMngr_NO_MemBufferDC
	CMemBufferDC m_oMembufferDC;
#endif
	CWnd *m_pRefWnd;
	COLORREF m_crBack;

public:
	virtual void Set_CURSOR_ZOOM(UINT nCURSOR_ZOOM)		{	m_n_CURSOR_ZOOM = nCURSOR_ZOOM;	}
	virtual void AttachRefWnd(CWnd *pWnd)				{	m_pRefWnd = pWnd;				}
	virtual void SetBackColor(COLORREF crBack)			{	m_crBack = crBack;				}

public:
	virtual void SetBorder(const CRect &rcBorder, CDC *pDC, BOOL bUseMngrAxisRange);
	virtual void Draw(CDC *pDC, long nLeft, long nTop, long nWidth, long nHeight);
	virtual void Draw(CDC *pDC);
	virtual CRect GetBorder()	{	return m_rcBorder;	}

public:
	virtual void InitAxis() = 0;
	virtual void AdjustAxis(BOOL bUseMngrAxisRange) = 0;
	virtual void ResetAxis() = 0;
	virtual void SetAxisRange(double &dXMin, double &dYMin, double &dXMax, double &dYMax) = 0;
	virtual void GetAxisInterface(CAxisInterface **ppAxisInterface) = 0;

	virtual void DevicePointToLogicPoint(const CPoint &point, double &dX, double &dY) = 0;
	virtual void DevicePointToLogicPoint(const CPoint &point, double *dX, double *dY) = 0;
	virtual void DrawAxis(CDC *pDC) = 0;

	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void LogicPointToDevicePoint();
	virtual void GetLogicBorder(double &dXMin, double &dYMin, double &dXMax, double &dYMax);

//�����صĲ������
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point, CDC *pDC);
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point, CDC *pDC);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point, CDC *pDC);

	///////�������Ŵ���
protected:
	int		m_iMouseZoomNow;			//�Ƿ������Ŵ��״̬
	float	m_fMaxZoomOut;
	int		m_iLBPushNum;				//��갴�µĴ���
	int		m_iMouseInCurveRegion;		//�����Ƿ�λ��ͼ�ε�����֮��
	CPoint	m_pointOrigin,m_pointOld;	//��¼��갴�µĵ�һ�㡢��ǰ���ڵ�λ��
	virtual BOOL OnMouseZoomMove(CPoint point, CDC *pDC);		//�������Ŵ�ʱ������ƶ�
	virtual void OnMouseZoomLBUp(CPoint point, CDC *pDC);		//�������Ŵ�ʱ������������
	virtual BOOL OnMouseZoomLBDown(CPoint point, CDC *pDC);	//�������Ŵ�ʱ������������
	virtual void MouseMoveZoom();					//�������Ŵ�ʵ�ֺ���
	virtual CRect GetRectFromPoint(CPoint pt1,CPoint pt2);

	virtual void MoveDown(double dOffset=1.0);		//ͼ�������ƶ�
	virtual void MoveLeft(double dOffset=1.0);		//ͼ�������ƶ�
	virtual void MoveRight(double dOffset=1.0);	//ͼ�������ƶ�
	virtual void MoveUp(double dOffset=1.0);		//ͼ�������ƶ�
	virtual double GetXMoveOffset(double dMoveRate=0.2);
	virtual double GetYMoveOffset(double dMoveRate=0.2);
};

