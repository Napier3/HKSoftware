//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "XScdDrawGlobal.h"
#include "XScdDrawIedBase.h"

class CXScdDrawIedVTest : public CXScdDrawIedBase
{
public:
	CXScdDrawIedVTest();
	virtual ~CXScdDrawIedVTest();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_IED_VTEST;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

};

