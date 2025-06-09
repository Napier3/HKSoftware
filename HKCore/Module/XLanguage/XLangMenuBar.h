//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangItem.h  CXLangItem

#pragma once

#include "XLanguageMngr.h"

//////////////////////////////////////////////////////////////////////////
//CXLangMenuBar
class CXLangMenuBar : public CMFCMenuBar
{
public:
	CXLangMenuBar();

	virtual ~CXLangMenuBar();

//重载函数
public:
	virtual void CreateFromMenu(HMENU hMenu, BOOL bDefaultMenu = FALSE, BOOL bForceUpdate = FALSE);
	static long g_nMenuRootIndex;

//私有成员变量
private:
	void InitXLangByButton(CMFCToolBarMenuButton *pMenuButton);
	void InitXLangText(CMFCToolBarMenuButton *pButton);

//私有成员变量访问方法
public:
	void InitXLangButtons();
};

