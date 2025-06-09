//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecFiberConfig.h  CIecFiberConfig

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

class CIecFiberCh : public CExBaseObject
{
public:
	CIecFiberCh();
	virtual ~CIecFiberCh();
	
	long m_nIndex;
	long m_nState;   //状态，被开出使用、开入使用
	long m_nUseCount;   //使用计数器
};

class CIecFiberConfig : public CExBaseList
{
public:
	CIecFiberConfig();
	virtual ~CIecFiberConfig();


//重载函数
public:
	void InitFiberConfig(long nFiberCount);
	void InitFt3Config(long nFiberCount);
	void InitFiberConfig(long nAppType, long nAppVersion);
	
	
//私有成员变量
private:

//私有成员变量访问方法
public:
};

 
