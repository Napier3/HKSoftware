//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_ThumbSvIn.h  CXScdDrawCtrl_ThumbSvIn

#pragma once

#include "XScdDrawCtrl_ThumbBase.h"

class CXScdDrawCtrl_ThumbSvIn : public CXScdDrawCtrl_ThumbBase
{
public:
	CXScdDrawCtrl_ThumbSvIn();
	virtual ~CXScdDrawCtrl_ThumbSvIn();

	//���غ���
public:
	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_THUMB_SVIN;   }
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

	virtual void CreateCtrlLines();
	virtual void CreateCtrlBusLines();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:

};
