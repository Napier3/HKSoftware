//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmFileDBGlobal.h

#pragma once

#include "..\ProtocolBase\ProtocolGlobalDef.h"
#include "..\CapGlobalDef.h"
#include "..\..\..\..\Module\MemBuffer\CycleMemBuffer.h"

// #include "..\..\BaseClass\ThreadProgressInterface.h"

#define EP_SEARCH_TYPE_YX     0
#define EP_SEARCH_TYPE_YC     1
#define EP_SEARCH_TYPE_YT     2
#define EP_SEARCH_TYPE_YK     4
#define EP_SEARCH_TYPE_YCYT   5
#define EP_SEARCH_TYPE_FRAME  0xFF

#define EPCAP_SEARCH_ADDR_DIR_TYPE_SERIAL  0
#define EPCAP_SEARCH_ADDR_DIR_TYPE_IP      1

#define WM_CAPQUERY_ITEM_CLICK  (WM_USER+2245)

#define WM_CAP_QUERY (WM_USER + 833)
#define WM_CAP_QUERYS (WM_USER + 834)



inline void ep_CapSearchAddr_UseSrc(BOOL bUse, DWORD &dwUse)
{
	//dwUse &= 0x0000FFFF;

	if (bUse) 
	{
		dwUse |= 0x00010000;
	}
	else
	{
		dwUse &= 0xFFFEFFFF;
	}
}

inline void ep_CapSearchAddr_UseDest(BOOL bUse, DWORD &dwUse)
{
//	dwUse &= 0xFFFF0000;

	if (bUse) 
	{
		dwUse |= 0x00000001;
	}
	else
	{
		dwUse &= 0xFFFFFFFE;
	}
}

inline BOOL ep_CapSearchAddr_UseSrc(DWORD dwUse)
{
	return ((dwUse & 0xFFFF0000) > 0);
}

inline BOOL ep_CapSearchAddr_UseDest(DWORD dwUse)
{
	return ((dwUse & 0x0000FFFF) > 0);
}


typedef struct epCapSearchAddrDir
{
	DWORD dwType;  //地址类型 Serial、IP
	DWORD dwUse;   //UseSrc+UseDest
	DWORD dwSrcAddr;
	DWORD dwDestAddr;
}EPCAPSEARCHADDRDIR, *PEPCAPSEARCHADDRDIR;

#define CAP_SEARCH_ADDR_DIR_MAX  20
#define CAP_SEARCH_DATA_MAX      20

typedef struct epCapSearchConfig
{
	DWORD dwMaxQuery;
	DWORD dwUseProtocol;
	DWORD dwProtocol;
	DWORD dwUseSearchType;
	DWORD dwSearchType;  //Frame/YC/YX/YK/YT
	DWORD dwSearchType2;  //Frame/YC/YX/YK/YT
	EPTIME64 tmBegin;
	EPTIME64 tmEnd;
	DWORD dwUseDir;
	DWORD dwAddrDirCount;
	EPCAPSEARCHADDRDIR oAddrDir[CAP_SEARCH_ADDR_DIR_MAX];
	DWORD dwDatasIndexCount;
	DWORD dwDatasIndex[CAP_SEARCH_DATA_MAX];
	DWORD dwFlag;
}EPCAPSEARCHCONFIG, *PEPCAPSEARCHCONFIG;  

inline BOOL Ep_IsDatasIndexIn(EPCAPSEARCHCONFIG &oConfig, DWORD dwIndex)
{
	DWORD i = 0;

	for (i=0; i<oConfig.dwDatasIndexCount; i++)
	{
		if (dwIndex == oConfig.dwDatasIndex[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}

inline void Ep_AddDatasIndex(EPCAPSEARCHCONFIG &oConfig, DWORD dwIndex)
{
	if (oConfig.dwDatasIndexCount > CAP_SEARCH_DATA_MAX)
	{
		return;
	}

	oConfig.dwDatasIndex[oConfig.dwDatasIndexCount] = dwIndex;
	oConfig.dwDatasIndexCount++;
}


inline void Ep_AddAddrDir(EPCAPSEARCHCONFIG &oConfig, DWORD dwSrc)
{
	if (oConfig.dwAddrDirCount > CAP_SEARCH_ADDR_DIR_MAX)
	{
		return;
	}

	PEPCAPSEARCHADDRDIR pDir = &oConfig.oAddrDir[oConfig.dwAddrDirCount];

	ZeroMemory(pDir, sizeof(EPCAPSEARCHADDRDIR));
	ep_CapSearchAddr_UseSrc(TRUE, pDir->dwUse);
	pDir->dwSrcAddr = dwSrc;
	pDir->dwType = EPCAP_SEARCH_ADDR_DIR_TYPE_SERIAL;

	oConfig.dwAddrDirCount++;
}



inline void Ep_AddAddrDir(EPCAPSEARCHCONFIG &oConfig, DWORD dwSrc, DWORD dwDest)
{
	if (oConfig.dwAddrDirCount > CAP_SEARCH_ADDR_DIR_MAX)
	{
		return;
	}

	PEPCAPSEARCHADDRDIR pDir = &oConfig.oAddrDir[oConfig.dwAddrDirCount];

	ZeroMemory(pDir, sizeof(EPCAPSEARCHADDRDIR));
	ep_CapSearchAddr_UseSrc(dwSrc != 0xFFFFFFFF, pDir->dwUse);
	ep_CapSearchAddr_UseDest(dwDest != 0xFFFFFFFF, pDir->dwUse);
	
	pDir->dwSrcAddr = dwSrc;
	pDir->dwDestAddr = dwDest;
	pDir->dwType = EPCAP_SEARCH_ADDR_DIR_TYPE_IP;

	oConfig.dwAddrDirCount++;
}

inline void Ep_DeleteAddrDir(EPCAPSEARCHCONFIG &oConfig, DWORD nIndex)
{
	if (oConfig.dwAddrDirCount <= 0)
	{
		return;
	}

	if (nIndex >= oConfig.dwAddrDirCount)
	{
		return;
	}

	if (nIndex < 0)
	{
		return;
	}

	for (DWORD i=nIndex; i < oConfig.dwAddrDirCount-1; i++)
	{
		oConfig.oAddrDir[i] = oConfig.oAddrDir[i+1];
	}

	oConfig.dwAddrDirCount--;
}

typedef struct epQeuryRange
{
	long nBeginIndex;
	long nEndIndex;
}EPQUERYRANGE, *PEPQUERYRANGE;  


typedef struct epQeuryRanges
{
	EPQUERYRANGE range0;
	EPQUERYRANGE range1;
}EPQUERYRANGES, *PEPQUERYRANGES; 

class CEpQueryIndex0Range
{
public:
	CEpQueryIndex0Range()
	{
		m_pIndex0 = NULL;
		m_pIndex1 = NULL;
	}
	CEpQueryIndex0Range(PEPCAPDBBUFFERINDEX0EX pIndex0, PEPCAPDBBUFFERINDEX0EX pIndex1)
	{
		m_pIndex0 = (PEPCAPDBBUFFERINDEX0EX)malloc(sizeof(EPCAPDBBUFFERINDEX0EX));
		m_pIndex1 = (PEPCAPDBBUFFERINDEX0EX)malloc(sizeof(EPCAPDBBUFFERINDEX0EX));
		*m_pIndex0 = *pIndex0;
		*m_pIndex1 = *pIndex1;
	}

	virtual ~CEpQueryIndex0Range()
	{
		free(m_pIndex0);
		free(m_pIndex1);
		m_pIndex0 = NULL;
		m_pIndex1 = NULL;
	}

	PEPCAPDBBUFFERINDEX0EX m_pIndex0;
	PEPCAPDBBUFFERINDEX0EX m_pIndex1;
};


class CEpQueryIndex0Ranges : public CTLinkListEx<CEpQueryIndex0Range>
{
public:
	CEpQueryIndex0Ranges()
	{
		m_oIndex0Ranges.range0.nBeginIndex = -1;
		m_oIndex0Ranges.range0.nEndIndex = -1;
		m_oIndex0Ranges.range1.nBeginIndex = -1;
		m_oIndex0Ranges.range1.nEndIndex = -1;
	}

	virtual ~CEpQueryIndex0Ranges()
	{
		DeleteAll();
	}

	EPQUERYRANGES m_oIndex0Ranges;

	CEpQueryIndex0Range* AddIndex0Range(PEPCAPDBBUFFERINDEX0EX pIndex0, PEPCAPDBBUFFERINDEX0EX pIndex1)
	{
		CEpQueryIndex0Range *pNew = new CEpQueryIndex0Range(pIndex0, pIndex1);
		AddTail(pNew);
		return pNew;
	}
};

class CEpCapDbBufferIndex
{
public:
	CEpCapDbBufferIndex()
	{
	}
	CEpCapDbBufferIndex(PEPCAPDBBUFFERINDEX pIndex)
	{
		m_oEpCapBufferIndex = *pIndex;
	}
	virtual ~CEpCapDbBufferIndex()
	{

	}

	EPCAPDBBUFFERINDEX m_oEpCapBufferIndex;
	CCycleMemBuffer m_oBuffer;

	BYTE* GetBuffer()
	{
		return m_oBuffer.GetBuffer();
	}

	long GetBufferLength()
	{
		return m_oBuffer.GetDataLength();
	}

	void SetBuffer(BYTE *pBuffer, long nLen)
	{
		m_oBuffer.Init(pBuffer, nLen);
	}

public:
	BOOL operator ==(const CEpCapDbBufferIndex &val)
	{
		return (m_oEpCapBufferIndex.tm.n64Time == val.m_oEpCapBufferIndex.tm.n64Time);
	}

	BOOL operator >=(const CEpCapDbBufferIndex &val)
	{
		return (m_oEpCapBufferIndex.tm.n64Time >= val.m_oEpCapBufferIndex.tm.n64Time);
	}

	BOOL operator >(const CEpCapDbBufferIndex &val)
	{
		return (m_oEpCapBufferIndex.tm.n64Time > val.m_oEpCapBufferIndex.tm.n64Time);
	}

	BOOL operator <=(const CEpCapDbBufferIndex &val)
	{
		return (m_oEpCapBufferIndex.tm.n64Time <= val.m_oEpCapBufferIndex.tm.n64Time);
	}

	BOOL operator < (const CEpCapDbBufferIndex &val)
	{
		return (m_oEpCapBufferIndex.tm.n64Time < val.m_oEpCapBufferIndex.tm.n64Time);
	}
};

class CEpQueryEpCapDbBufferIndex : public CTLinkListEx<CEpCapDbBufferIndex>
{
public:
	CEpQueryEpCapDbBufferIndex()
	{

	}

	virtual ~CEpQueryEpCapDbBufferIndex()
	{

	}

	CEpCapDbBufferIndex* AddCapBufferIndex(PEPCAPDBBUFFERINDEX pIndex)
	{
		CEpCapDbBufferIndex *pNew = new CEpCapDbBufferIndex(pIndex);
		AddTail(pNew);
		return pNew;
	}

	void SortInc();

private:
	void QuickSort(DWORD *pdwBuffer, long nLeft, long nRight);

};

// CString Ep_GetCapDataText(CEpY4Data *pDeviceData, long nDataType);
// CString Ep_GetCapDataText(long nProtocol,CEpY4Data *pDeviceData, long nDataType);
// CExBaseObject* Ep_GetEdcmData(long nProtocol, long nDataType, long nItemIndex);
