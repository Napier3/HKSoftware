//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "XScdDrawLineBase.h"



class CXScdDrawLine_Ctrl : public CXScdDrawLineBase
{
public:
	CXScdDrawLine_Ctrl();
	virtual ~CXScdDrawLine_Ctrl();

public:
	

//���غ���
public:
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual UINT GetClassID() {    return XSCDDRAW_LINE_CTRL;   }

};

