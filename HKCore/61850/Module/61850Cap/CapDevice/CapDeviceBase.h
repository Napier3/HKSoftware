//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceBase.h  CCapDeviceBase

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceChBase.h"
#include "..\ProtocolBase\ProtocolGlobalDef.h"
#include "..\..\..\..\Module\MemBuffer\CycleMemBuffer.h"
#include "..\CapGlobalDef.h"
// #include <vector>
// #include <map>
// 
// 
// typedef std::map< long, CCapDeviceChBase> CCapDeviceChMap;
// typedef std::map< long, CCapDeviceChBase>::iterator CCapDeviceChIter;

class CCapDeviceBase : public CExBaseList
{
public:
	CCapDeviceBase();
	virtual ~CCapDeviceBase();

	BYTE m_byteSrcMac[6];
	BYTE m_byteDestMac[6];
	DWORD m_dwAppID;
	UINT m_nType;
	
	CString m_strDestAddress;
	CString m_strSrcAddress;

	CCycleMemBuffer m_oBuffer;
	CExBaseObject *m_pFrame;

	__int64 m_n64CapDataIndex;
	BOOL m_bSelect;

	long m_nFillBeginPos;
	long m_nDatasCount;
	
// 	CCapDeviceChMap m_RecordChMap;
// 	CCapDeviceChMap m_RecordChMapRemove;
//重载函数
public:

//私有成员变量
private:
	virtual CCapDeviceChBase* CreateChannel() = 0;

//私有成员变量访问方法
public:
	virtual BOOL SetChannelNum(long nChannelNum);
	BOOL Compare(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT)
	{
		if (memcmp(m_byteDestMac, pDstMac, 6) != 0)
		{
			return FALSE;
		}

		if (memcmp(m_byteSrcMac, pSrcMac, 6) != 0)
		{
			return FALSE;
		}

		if (m_dwAppID != APPID)
		{
			return FALSE;
		}

		if (m_nType != nCMT)
		{
			return FALSE;
		}

		return TRUE;
	}
	BOOL Compare(PEPCAPBUFFERITEM pItemData)
	{
		if (memcmp(m_byteDestMac, pItemData->addr_61850.dstMac, 6) != 0)
		{
			return FALSE;
		}

		if (memcmp(m_byteSrcMac, pItemData->addr_61850.srcMac, 6) != 0)
		{
			return FALSE;
		}

		if (m_dwAppID != pItemData->addr_61850.APPID)
		{
			return FALSE;
		}

		if (m_nType != pItemData->nProtocol)
		{
			return FALSE;
		}

		return TRUE;
	}

	void Iinit(PEPCAPBUFFERITEM pItemData)
	{
		memcpy(m_byteDestMac, pItemData->addr_61850.dstMac, 6);
		memcpy(m_byteSrcMac, pItemData->addr_61850.srcMac, 6);
		m_dwAppID = pItemData->addr_61850.APPID;
		m_nType = pItemData->nProtocol;
		SetChannelNum(pItemData->nChCount);
	}

	void InitAddress();
	void ParseDeviceInfor();

	void InitDevice(PEPCAPPARSEDATAS pDatas);
	void AddCapDataBuffer(PEPCAPPARSEDATAS pDatas);
	void SetCapSelect(BOOL bSelect);

	void BeginCap();
};

