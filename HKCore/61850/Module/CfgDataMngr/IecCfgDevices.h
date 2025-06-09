//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDevices.h  CIecCfgDevices

#pragma once
#include "IecCfgDevice.h"

class CIecCfgDevices : public CExBaseList
{
public:
	CIecCfgDevices(){}
	~CIecCfgDevices(){}

	void AddIecCfgDevice(const CString& strIecCfgFile);
	void RemoveIecCfgDevice(CIecCfgDevice* pCfgDevice);

	CIecCfgDataBase* FindIecCfgData(PEPCAPBUFFERITEM pItemData);
	CIecCfgDataBase* FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID,UINT nCMT,UINT nChCount);
};

