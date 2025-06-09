//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangItem.h  CXLangItem

#pragma once

#include "XLanguageMngr.h"

class CXLangMenu : public CMenu
{
public:
	CXLangMenu();

	virtual ~CXLangMenu();

//重载函数
public:
	BOOL LoadMenu(UINT nIDResource);


//私有成员变量
private:
	void InitMenuXLang(CMenu *pMenu, long &nNewXLangStrCount);

//私有成员变量访问方法
public:
};

