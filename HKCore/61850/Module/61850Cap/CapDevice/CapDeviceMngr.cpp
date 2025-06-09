//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceMngr.cpp  CCapDeviceMngr


#include "stdafx.h"
#include "CapDeviceMngr.h"

#include "CapDevice91.h"
#include "CapDevice92.h"
#include "CapDeviceGoose.h"

CCapDeviceMngr::CCapDeviceMngr()
{
	//初始化属性


	//初始化成员变量

}

CCapDeviceMngr::~CCapDeviceMngr()
{
}

CCapDeviceBase* CCapDeviceMngr::FindCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT)
{
	CCapDeviceBase *p = NULL;
	CCapDeviceBase *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->Compare(pDstMac, pSrcMac, APPID, nCMT))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CCapDeviceBase* CCapDeviceMngr::AddCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT)
{
	CCapDeviceBase *pNew = NULL;

	switch (nCMT)
	{
	case PROTOCOL_61850_TYPE_91:
		pNew = new CCapDevice91();
		break;
	case PROTOCOL_61850_TYPE_92:
		pNew = new CCapDevice92();
		break;
	case PROTOCOL_61850_TYPE_GOOSE:
		pNew = new CCapDeviceGoose();
		break;
	case PROTOCOL_61850_TYPE_60448:
		//pNew = new CCapDevice91();
		break;
	default:
		break;
	}

	return pNew;
}



CCapDeviceBase* CCapDeviceMngr::FindCapDevice(PEPCAPBUFFERITEM pItemData)
{
	CCapDeviceBase *p = NULL;
	CCapDeviceBase *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)GetNext(pos);

		if (p->Compare(pItemData))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CCapDeviceBase* CCapDeviceMngr::AddCapDevice(PEPCAPBUFFERITEM pItemData)
{
	CCapDeviceBase *pNew = NULL;

	switch (pItemData->nProtocol)
	{
	case PROTOCOL_61850_TYPE_91:
		pNew = new CCapDevice91();
		pNew->Iinit(pItemData);
		AddTail(pNew);
		break;
	case PROTOCOL_61850_TYPE_92:
		pNew = new CCapDevice92();
		pNew->Iinit(pItemData);
		AddTail(pNew);
		break;
	case PROTOCOL_61850_TYPE_GOOSE:
		pNew = new CCapDeviceGoose();
		pNew->Iinit(pItemData);
		AddTail(pNew);
		break;
	case PROTOCOL_61850_TYPE_60448:
		//pNew = new CCapDevice91();
		break;
	default:
		break;
	}

	return pNew;
}


