//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangItem.h  CXLangItem

#pragma once

#include "XLanguageMngr.h"

class CXLangToolBar : public CMFCToolBar
{
public:
	CXLangToolBar();

	virtual ~CXLangToolBar();

//重载函数
public:
	virtual void AdjustLocations();
	void UpdateTooltipsEx();


//私有成员变量
private:
	CString m_strToolTipTxt;

//私有成员变量访问方法
public:
};

