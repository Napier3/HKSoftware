//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_IED2DETAIL;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
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

