//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawViewIedCfg.h  CXScdDrawViewIedCfg

#pragma once

#include "XBinaryDrawBase.h"
#include "../../../Module/XDrawBase/XDrawViewBase.h"

class CXBinaryDrawView : public CXDrawViewBase
{
public:
	CXBinaryDrawView();
	virtual ~CXBinaryDrawView();

//���غ���
public:

//˽�г�Ա����
protected:
	CXBinarysDrawBase *m_pBinarysDraw;
	BOOL m_bIsBinaryOut;
	BOOL m_bUseBinaryOutOptr;

//˽�г�Ա�������ʷ���
public:

//��ͼ��غ�������
public:
	void BinarysDraw(CDC *pDC);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag);

public:
	virtual CSize Layout(CPoint &ptTopLeft);
	virtual CSize CalLayout(CSize &szDraw);
};

