//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_THUMB;   }

//˽�г�Ա����
private:
	CExBaseList m_listIedGroup;
	CXScdIedGroupThumb *m_pIedList_ProtMeas;//������ؼ���
	CXScdIedGroupThumb *m_pIedList_MergIntel;//�����ն˺ϲ���Ԫ����
	CXScdIedGroupThumb *m_pIedList_ProtMeas2;//�ڶ��б������IED

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
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

