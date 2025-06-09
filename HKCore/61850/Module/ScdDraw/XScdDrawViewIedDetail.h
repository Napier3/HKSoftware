//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewIed2Detail.h  CXScdDrawViewIed2Detail

#pragma once

#include "XScdDrawViewBase.h"
#include "XScdDrawIedSclDetail.h"
#include "XScdDrawLine_Ctrls.h"

class CXScdDrawViewIedDetail : public CXScdDrawViewBase
{
public:
	CXScdDrawViewIedDetail();
	virtual ~CXScdDrawViewIedDetail();

//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_IED2DETAIL;   }

//私有成员变量
private:

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);

public:
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);
	virtual CXDrawElement* XCreateChildElement(UINT nClassID);

	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

	virtual void LayoutLines();
	virtual void InitLinesBeginElement();
	virtual void OnOnlyShowUsedChsChanged();

protected:
	void InitXScdDrawViewIedDetail(CXScdDrawLine_Ctrls *pLineCtrls, CWnd *pParentWnd);
// 	void InitXScdDrawViewIedThumb(CXScdDrawIedSclDetail *pIedThumb, CWnd *pParentWnd);
// 	
// 	void InitXScdDrawViewIedThumb_GsIn(CXScdDrawCtrl_ThumbGsIn *pGsIn, CWnd *pParentWnd);
// 	void InitXScdDrawViewIedThumb_GsOut(CXScdDrawCtrl_ThumbGsOut *pGsOut, CWnd *pParentWnd);
// 	void InitXScdDrawViewIedThumb_SvIn(CXScdDrawCtrl_ThumbSvIn *pSvIn, CWnd *pParentWnd);
// 	void InitXScdDrawViewIedThumb_SvOut(CXScdDrawCtrl_ThumbSvOut *pSvOut, CWnd *pParentWnd);
// 
// 	void InitXScdDrawViewIedThumb_In(CExBaseList *pCtrlIn, CExBaseList *pDestCtrl, CWnd *pParentWnd);
// 	void InitXScdDrawViewIedThumb_Out(CExBaseList *pCtrlOut, CExBaseList *pDestCtrl, CWnd *pParentWnd);
// 
// 	CXScdDrawIedSclDetail* FindBySclIed(CSclIed *pIed);
};

