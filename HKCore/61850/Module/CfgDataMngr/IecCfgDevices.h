//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

