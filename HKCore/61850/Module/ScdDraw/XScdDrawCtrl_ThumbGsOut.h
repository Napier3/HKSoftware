//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_ThumbGsOut.h  CXScdDrawCtrl_ThumbGsOut

#pragma once

#include "XScdDrawCtrl_ThumbBase.h"

class CXScdDrawCtrl_ThumbGsOut : public CXScdDrawCtrl_ThumbBase
{
public:
	CXScdDrawCtrl_ThumbGsOut();
	virtual ~CXScdDrawCtrl_ThumbGsOut();

	//重载函数
public:
	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_THUMB_GSOUT;   }
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void CreateCtrlBusLines();

	//私有成员变量
private:

	//私有成员变量访问方法
public:

	//绘图相关函数定义
public:

};

