//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawIed.cpp  CXScdDrawIed


#include "stdafx.h"
#include "XScdDrawLine_Ctrl.h"

CXScdDrawLine_Ctrl::CXScdDrawLine_Ctrl()
{
	//��ʼ������

	//��ʼ����Ա����
	
}

CXScdDrawLine_Ctrl::~CXScdDrawLine_Ctrl()
{
	
}


void CXScdDrawLine_Ctrl::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawLineBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}

