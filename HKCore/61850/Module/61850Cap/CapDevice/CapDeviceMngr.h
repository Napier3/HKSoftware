//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceMngr.h  CCapDeviceMngr

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceBase.h"

class CCapDeviceMngr : public CExBaseList
{
public:
	CCapDeviceMngr();
	virtual ~CCapDeviceMngr();

//���غ���
public:

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CCapDeviceBase* FindCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	CCapDeviceBase* AddCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	
	CCapDeviceBase* FindCapDevice(PEPCAPBUFFERITEM pItemData);
	CCapDeviceBase* AddCapDevice(PEPCAPBUFFERITEM pItemData);
	
};

