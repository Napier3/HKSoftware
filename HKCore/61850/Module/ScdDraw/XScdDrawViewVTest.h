//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawViewIedVTest.h  CXScdDrawViewIedVTest

#pragma once

#include "XScdDrawViewBase.h"

class CXScdDrawViewVTest : public CXScdDrawViewBase
{
public:
	CXScdDrawViewVTest();
	virtual ~CXScdDrawViewVTest();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_VTEST;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);

};

