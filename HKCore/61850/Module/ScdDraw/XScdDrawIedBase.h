//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "XScdDrawGlobal.h"
#include "XScdDrawLineBase.h"


class CXScdDrawIedBase : public CXDrawElements
{
public:
	CXScdDrawIedBase();
	virtual ~CXScdDrawIedBase();

//重载函数
public:
 	virtual void AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow);

public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

	virtual void GetAllLines(CXDrawElements &oScdLines);
	virtual void CreateCtrlLines();
	virtual void OnOnlyShowUsedChsChanged(CXScdDrawLines *pLines);
	virtual void RemoveErrorLines();

};

