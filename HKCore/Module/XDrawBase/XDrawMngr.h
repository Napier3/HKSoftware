//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	void InitDrawLineColor(const COLORREF &oColor);//zhouhj 20210202 初始化链表中线条设置的颜色
//重载函数
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

//私有成员变量
private:

//私有成员变量访问方法
public:
// 	CXDrawList* FindByID(const CString &strID);
	CXDrawList* AddNew(const CString &strID);
	CXDrawList* AddNewByFile(const CString &strFile);

//////////////////////////////////////////////////////////////////////////
//绘图部分
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

//鼠标相关的操作入口
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point, CDC *pDC);
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point, CDC *pDC);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point, CDC *pDC);

	///////定义鼠标放大功能
protected:
	int		m_iMouseZoomNow;			//是否处于鼠标放大的状态
	float	m_fMaxZoomOut;
	int		m_iLBPushNum;				//鼠标按下的次数
	int		m_iMouseInCurveRegion;		//鼠标点是否位于图形的区域之内
	CPoint	m_pointOrigin,m_pointOld;	//纪录鼠标按下的第一点、当前所在的位置
	virtual BOOL OnMouseZoomMove(CPoint point, CDC *pDC);		//处理鼠标放大时的鼠标移动
	virtual void OnMouseZoomLBUp(CPoint point, CDC *pDC);		//处理鼠标放大时的鼠标左键弹起
	virtual BOOL OnMouseZoomLBDown(CPoint point, CDC *pDC);	//处理鼠标放大时的鼠标左键按下
	virtual void MouseMoveZoom();					//鼠标左键放大实现函数
	virtual CRect GetRectFromPoint(CPoint pt1,CPoint pt2);

	virtual void MoveDown(double dOffset=1.0);		//图形下下移动
	virtual void MoveLeft(double dOffset=1.0);		//图形向左移动
	virtual void MoveRight(double dOffset=1.0);	//图形向右移动
	virtual void MoveUp(double dOffset=1.0);		//图形向上移动
	virtual double GetXMoveOffset(double dMoveRate=0.2);
	virtual double GetYMoveOffset(double dMoveRate=0.2);
};

