//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "XScdDrawGlobal.h"
#include "XScdDrawIedBase.h"

class CXScdDrawIedVTest : public CXScdDrawIedBase
{
public:
	CXScdDrawIedVTest();
	virtual ~CXScdDrawIedVTest();

//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_IED_VTEST;   }

//私有成员变量
private:

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

};

