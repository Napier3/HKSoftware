//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbBaseList.h  CSmDbBaseList

#pragma once

#include "SmDbBaseObject.h"
#include "..\BaseClass\BaseList.h"

class CSmDbBaseList : public CBaseList
{
public:
	CSmDbBaseList();
	virtual ~CSmDbBaseList();


//重载函数
public:
	virtual long SmReadChildren(CShareMemClientEx &oSm);
	virtual long SmWriteChildren(CShareMemClientEx &oSm);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

