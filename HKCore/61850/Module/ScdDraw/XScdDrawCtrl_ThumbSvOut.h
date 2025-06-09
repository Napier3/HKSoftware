//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_ThumbSvOut.h  CXScdDrawCtrl_ThumbSvOut

#pragma once

#include "XScdDrawCtrl_ThumbBase.h"

class CXScdDrawCtrl_ThumbSvOut : public CXScdDrawCtrl_ThumbBase
{
public:
	CXScdDrawCtrl_ThumbSvOut();
	virtual ~CXScdDrawCtrl_ThumbSvOut();

	//重载函数
public:
	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_THUMB_SVOUT;   }
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void CreateCtrlBusLines();

	//私有成员变量
private:

	//私有成员变量访问方法
public:

	//绘图相关函数定义
public:

};