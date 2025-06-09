//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceSmvBase.h  CCapDeviceSmvBase

#pragma once

#include "CapDeviceBase.h"
#include "CapDeviceSmvCh.h"

class CCapDeviceSmvBase : public CCapDeviceBase
{
public:
	CCapDeviceSmvBase();
	virtual ~CCapDeviceSmvBase();


	long  m_nSampleRate;
	long  m_nAsduNum;

//重载函数
public:

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CCapDeviceChBase* CreateChannel()		{	return new CCapDeviceSmvCh();	}

};

