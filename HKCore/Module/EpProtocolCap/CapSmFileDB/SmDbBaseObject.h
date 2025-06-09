//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbBaseObject.h  CSmDbBaseObject

#pragma once

#include "SmFileDBGlobal.h"
#include "..\ShareMem\ShareMemServerEx.h"
#include "..\ShareMem\ShareMemClientEx.h"


class CSmDbBaseObject : public CBaseObject
{
public:
	CSmDbBaseObject();
	virtual ~CSmDbBaseObject();


//重载函数
public:
	virtual long SmRead(CShareMemClientEx &oSm)	{	SmReadOwn(oSm);	SmReadChildren(oSm);	InitAfterRead();	return 0;	}
	virtual long SmReadOwn(CShareMemClientEx &oSm)	{	return 0;	}
	virtual long SmReadChildren(CShareMemClientEx &oSm)	{	return 0;	}

	virtual long SmWrite(CShareMemClientEx &oSm)	{	SmWriteOwn(oSm);	SmWriteChildren(oSm);	return 0;	}
	virtual long SmWriteOwn(CShareMemClientEx &oSm)	{	return 0;	}
	virtual long SmWriteChildren(CShareMemClientEx &oSm)	{	return 0;	}

//私有成员变量
private:

//私有成员变量访问方法
public:
};

