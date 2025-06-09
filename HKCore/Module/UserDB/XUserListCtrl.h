//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CXUserListCtrl

#pragma once

#include "..\..\Module\BaseClass\ExBaseListListCtrl.h"

#define XUSER_COL_INDEX      0
#define XUSER_COL_NAME       1
#define XUSER_COL_ID         2
#define XUSER_COL_CURRTOOL   3



class CXUserListCtrl : public CExBaseListListCtrl
{
public:
	CXUserListCtrl();
	virtual ~CXUserListCtrl();

	virtual void InitCollumns();
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);
	
//重载函数
public:


//私有成员变量
private:

//私有成员变量访问方法
public:
};

