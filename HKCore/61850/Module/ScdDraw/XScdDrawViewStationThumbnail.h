//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewThumbnail.h  CXScdDrawViewThumbnail

#pragma once

#include "XScdDrawViewBase.h"
#include "XScdDrawIedThumbnail.h"

class CXScdDrawViewStationThumbnail : public CXScdDrawViewBase
{
public:
	CXScdDrawViewStationThumbnail();
	virtual ~CXScdDrawViewStationThumbnail();

	CXScdDrawLine_GooseBus *m_pLineGooseBus;
	CXScdDrawLine_SvBus    *m_pLineSvBus;
//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_THUMB;   }

//私有成员变量
private:
	CExBaseList m_listIedGroup;
	CXScdIedGroupThumb *m_pIedList_ProtMeas;//保护测控集合
	CXScdIedGroupThumb *m_pIedList_MergIntel;//智能终端合并单元集合
	CXScdIedGroupThumb *m_pIedList_ProtMeas2;//第二行保护测控IED

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	//virtual void Pick(const CPoint &point, CExBaseList &oList);

public:
	virtual CXDrawElement* XCreateChildElement(UINT nClassID);

	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);
	void InitXScdDrawViewThumbnail(CSclStation *pSclStation, CWnd *pParentWnd);
	virtual void CreateCtrlBusLines();

	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

	virtual void LayoutLines();
	virtual void InitLinesBeginElement();
	virtual void LayoutBusLines(CXScdDrawLine_Bus *pBus);

};

