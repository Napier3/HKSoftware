//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewIedVTest.h  CXScdDrawViewIedVTest

#pragma once

#include "XScdDrawViewBase.h"

class CXScdDrawViewVTest : public CXScdDrawViewBase
{
public:
	CXScdDrawViewVTest();
	virtual ~CXScdDrawViewVTest();

//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_VTEST;   }

//私有成员变量
private:

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);

};

