//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.cpp  CXScdDrawIed


#include "stdafx.h"
#include "XScdDrawLine_Ctrl.h"

CXScdDrawLine_Ctrl::CXScdDrawLine_Ctrl()
{
	//初始化属性

	//初始化成员变量
	
}

CXScdDrawLine_Ctrl::~CXScdDrawLine_Ctrl()
{
	
}


void CXScdDrawLine_Ctrl::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawLineBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}

