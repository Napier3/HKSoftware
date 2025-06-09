//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewIedThumbnail.h  CXScdDrawViewIedThumbnail

#pragma once

#include "XScdDrawViewBase.h"
#include "XScdDrawIedThumbnail.h"

class CXScdDrawViewIedThumbnail : public CXScdDrawViewBase
{
public:
	CXScdDrawViewIedThumbnail();
	virtual ~CXScdDrawViewIedThumbnail();

//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_THUMB;   }

//私有成员变量
private:
	CExBaseList m_listIedGroup;
	CXScdDrawIedThumbnail *m_pMainIedThumb;
	CXScdIedGroupThumb *m_pIedList_ProtMeas;//保护测控集合
	CXScdIedGroupThumb *m_pIedList_MergIntel;//智能终端合并单元集合

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);

public:
	virtual CXDrawElement* XCreateChildElement(UINT nClassID);

	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);

	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

	virtual void LayoutLines();
	//virtual void InitLinesBeginElement();

protected:
	void InitXScdDrawViewIedThumb(CXScdDrawIedThumbnail *pIedThumb, CWnd *pParentWnd);
	
	void InitXScdDrawViewIedThumb_GsIn(CXScdDrawCtrl_ThumbGsIn *pGsIn, CWnd *pParentWnd);
	void InitXScdDrawViewIedThumb_GsOut(CXScdDrawCtrl_ThumbGsOut *pGsOut, CWnd *pParentWnd);
	void InitXScdDrawViewIedThumb_SvIn(CXScdDrawCtrl_ThumbSvIn *pSvIn, CWnd *pParentWnd);
	void InitXScdDrawViewIedThumb_SvOut(CXScdDrawCtrl_ThumbSvOut *pSvOut, CWnd *pParentWnd);

	void InitXScdDrawViewIedThumb_In(CExBaseList *pCtrlIn, CExBaseList *pDestCtrl, CWnd *pParentWnd);
	void InitXScdDrawViewIedThumb_Out(CExBaseList *pCtrlOut, CExBaseList *pDestCtrl, CWnd *pParentWnd);

	CXScdDrawIedThumbnail* FindBySclIed(CSclIed *pIed);
};

