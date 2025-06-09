//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewIedCfg.h  CXScdDrawViewIedCfg

#pragma once

#include "XBinaryDrawBase.h"
#include "../../../Module/XDrawBase/XDrawViewBase.h"

class CXBinaryDrawView : public CXDrawViewBase
{
public:
	CXBinaryDrawView();
	virtual ~CXBinaryDrawView();

//重载函数
public:

//私有成员变量
protected:
	CXBinarysDrawBase *m_pBinarysDraw;
	BOOL m_bIsBinaryOut;
	BOOL m_bUseBinaryOutOptr;

//私有成员变量访问方法
public:

//绘图相关函数定义
public:
	void BinarysDraw(CDC *pDC);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag);

public:
	virtual CSize Layout(CPoint &ptTopLeft);
	virtual CSize CalLayout(CSize &szDraw);
};

