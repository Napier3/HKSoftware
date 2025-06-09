//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawViewIedThumbnail.h  CXScdDrawViewIedThumbnail

#pragma once

#include "XScdDrawViewBase.h"
#include "XScdDrawIedThumbnail.h"

class CXScdDrawViewIedThumbnail : public CXScdDrawViewBase
{
public:
	CXScdDrawViewIedThumbnail();
	virtual ~CXScdDrawViewIedThumbnail();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_THUMB;   }

//˽�г�Ա����
private:
	CExBaseList m_listIedGroup;
	CXScdDrawIedThumbnail *m_pMainIedThumb;
	CXScdIedGroupThumb *m_pIedList_ProtMeas;//������ؼ���
	CXScdIedGroupThumb *m_pIedList_MergIntel;//�����ն˺ϲ���Ԫ����

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
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

