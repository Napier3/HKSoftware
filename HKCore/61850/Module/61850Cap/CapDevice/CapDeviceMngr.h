//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceMngr.h  CCapDeviceMngr

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceBase.h"

class CCapDeviceMngr : public CExBaseList
{
public:
	CCapDeviceMngr();
	virtual ~CCapDeviceMngr();

//重载函数
public:

//私有成员变量
private:

//私有成员变量访问方法
public:
	CCapDeviceBase* FindCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	CCapDeviceBase* AddCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	
	CCapDeviceBase* FindCapDevice(PEPCAPBUFFERITEM pItemData);
	CCapDeviceBase* AddCapDevice(PEPCAPBUFFERITEM pItemData);
	
};

