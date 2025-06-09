// EpGlobalDefine.h
//////////////////////////////////////////////////////////////////////

#if !defined(_PROTOCOLGLOBALBASEDEFINE_H__)
#define _PROTOCOLGLOBALBASEDEFINE_H__

#include "..\BaseClass\ExBaseList.h"
class CEpCycleMemBuffer;
#include "..\EpProtocolCap\EpCapGlobalDef.h"

#define MAX_DATA_ONE_FRAME  1024
#define EPPROTOCOL_101  0
#define EPPROTOCOL_104  1
#define EPPROTOCOL_NONE 0xFF

#define EP_DEVICE_DATA_YX     0
#define EP_DEVICE_DATA_YC     1
#define EP_DEVICE_DATA_YT     2
#define EP_DEVICE_DATA_YK     3
#define EP_DEVICE_DATA_TSYN   4
#define EP_DEVICE_DATA_EMPTY  0xFFFF

#define EP_CAP_CHTYPE_UDP     0
#define EP_CAP_CHTYPE_TCP     1
#define EP_CAP_CHTYPE_SERIAL  2
#define EP_CAP_CHTYPE_IP      3
#define EP_CAP_CHTYPE_NET     4

//#pragma pack(1)

typedef struct epDeviceDataHead
{
	WORD nDeviceDataType;   //YC=0, YX=1; YT=2; YK=3
	WORD nDataCount;
}EPDEVICEDATAHEAD, *PEPDEVICEDATAHEAD;


typedef struct epTime64Ex
{
	WORD wYear;
	WORD wMonth;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
	WORD wMicrosecond;
}EPTIME64EX, *PEPTIME64EX;

class CEpY4Data
{
public:
	CEpY4Data()
	{
		m_nDataAddr = 0;
		m_fValue = 0;
		m_tm.n64Time = 0;
	}
	CEpY4Data(DWORD nDataAddr,float fValue,EPTIME64 tm)
	{
		m_nDataAddr = nDataAddr;
		m_fValue = fValue;
		m_tm = tm;
	}
	CEpY4Data(DWORD nDataAddr,float fValue)
	{
		m_nDataAddr = nDataAddr;
		m_fValue = fValue;
		m_tm.n64Time = 0;
	}

	virtual ~CEpY4Data()
	{

	}

	long WriteToBuffer(BYTE *pBuffer)
	{
		long nLen = 0;
		memcpy(pBuffer, &m_nDataAddr, sizeof(m_nDataAddr));
		pBuffer += sizeof(m_nDataAddr);
		nLen += sizeof(m_nDataAddr);

		memcpy(pBuffer, &m_fValue, sizeof(m_fValue));
		pBuffer += sizeof(m_fValue);
		nLen += sizeof(m_fValue);

		memcpy(pBuffer, &m_tm, sizeof(m_tm));
		pBuffer += sizeof(m_tm);
		nLen += sizeof(m_tm);

		return nLen;
	}

	long WriteToData(EPCAPDBDATA &oData)
	{
		oData.nDataAddr = m_nDataAddr;
		oData.fValue = m_fValue;
		//oData.tm = m_tm;
// 		long nLen = 0;
// 		memcpy(pBuffer, &m_nDataAddr, sizeof(m_nDataAddr));
// 		pBuffer += sizeof(m_nDataAddr);
// 		nLen += sizeof(m_nDataAddr);
// 
// 		memcpy(pBuffer, &m_fValue, sizeof(m_fValue));
// 		pBuffer += sizeof(m_fValue);
// 		nLen += sizeof(m_fValue);
// 
// 		memcpy(pBuffer, &m_tm, sizeof(m_tm));
// 		pBuffer += sizeof(m_tm);
// 		nLen += sizeof(m_tm);
		return 0;
	}

	long ReadFromBuffer(BYTE *pBuffer)
	{
		ASSERT (pBuffer != NULL);

		if (pBuffer == NULL)
		{
			return 0;
		}

		long nLen = 0;
		//memcpy(pBuffer, &m_nDataAddr, sizeof(m_nDataAddr));
		//pBuffer += sizeof(m_nDataAddr);
		m_nDataAddr = *((DWORD*)pBuffer);
		nLen += sizeof(m_nDataAddr);
		pBuffer += sizeof(m_nDataAddr);;

		//memcpy(pBuffer, &m_fValue, sizeof(m_fValue));
		//pBuffer += sizeof(m_fValue);
		m_fValue = *((float*)pBuffer);
		nLen += sizeof(m_fValue);
		pBuffer += sizeof(m_fValue);;

		//memcpy(&m_tm, pBuffer, sizeof(m_tm));
		//pBuffer += sizeof(m_tm);
		m_tm.n64Time = *((volatile __int64*)pBuffer);
		nLen += sizeof(m_tm);

		return nLen;
	}

	long ReadFromData(EPCAPDBDATA &oData)
	{
		m_nDataAddr = oData.nDataAddr;
		m_fValue = oData.fValue;
		m_tm = oData.tm;
		return 0;
	}

public:
	DWORD m_nDataAddr;
	float m_fValue;
	EPTIME64 m_tm;

public:
	BOOL operator ==(const CEpY4Data &val)
	{
		return (m_tm.n64Time == val.m_tm.n64Time);
	}

	BOOL operator >=(const CEpY4Data &val)
	{
		return (m_tm.n64Time >= val.m_tm.n64Time);
	}

	BOOL operator >(const CEpY4Data &val)
	{
		return (m_tm.n64Time > val.m_tm.n64Time);
	}

	BOOL operator <=(const CEpY4Data &val)
	{
		return (m_tm.n64Time <= val.m_tm.n64Time);
	}

	BOOL operator < (const CEpY4Data &val)
	{
		return (m_tm.n64Time < val.m_tm.n64Time);
	}
};

// #define EPYCDATA EPY4DATA
// #define PEPYCDATA PEPY4DATA
// #define EPYXDATA EPY4DATA
// #define PEPYXDATA PEPY4DATA
// #define EPYTDATA EPY4DATA
// #define PEPYTDATA PEPY4DATA
// #define EPYKDATA EPY4DATA
// #define PEPYKDATA PEPY4DATA

class CEpDeviceDatas : public CTLinkList<CEpY4Data>
{
public:
	CEpDeviceDatas()
	{
		m_nItemIndex = 0;
//		nDataCount = 0;
		m_nDeviceDataType = EP_DEVICE_DATA_EMPTY;
	}

	virtual ~CEpDeviceDatas()
	{
		DeleteAll();
	}

	WORD m_nDeviceDataType; 
// 	WORD nDataCount;
	long m_nItemIndex;

	CStringArray m_astrName;
	CDWordArray m_adwIndex;
	
public:
	void AddName(const CString &strName, long nID);
	void RemoveName(long nIndex);
	CString GetName(long nID);

	CEpY4Data* AddY4Data(DWORD nDataAddr,float fValue,EPTIME64 tm)
	{
		CEpY4Data *pData = new CEpY4Data(nDataAddr, fValue, tm);
		AddTail(pData);
		return pData;
	}
	CEpY4Data* AddY4Data(DWORD nDataAddr,float fValue)
	{
		CEpY4Data *pData = new CEpY4Data(nDataAddr, fValue);
		AddTail(pData);
		return pData;
	}

	void SortDesc();
	void SortInc();

	void Append(CEpDeviceDatas *pDatas)
	{
		POS pos = pDatas->GetHeadPosition();
		CEpY4Data *p = NULL;

		while (pos != NULL)
		{
			AddTail(pDatas->GetNext(pos));
		}
	}

protected:
	void QuickSort(DWORD *pdwBuffer, long nLeft, long nRight);
};

class CEpDeviceDatasMngr : public CTLinkList<CEpDeviceDatas>
{
public:
	CEpDeviceDatasMngr()
	{

	}

	virtual ~CEpDeviceDatasMngr()
	{
		
	}

	CEpDeviceDatas* FindByItemIndex(long nItemIndex)
	{
		CEpDeviceDatas *pDatas = NULL;
		CEpDeviceDatas *pFind = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pDatas = (CEpDeviceDatas *)GetNext(pos);

			if (pDatas->m_nItemIndex == nItemIndex)
			{
				pFind = pDatas;
				break;
			}
		}

		return pFind;
	}

	void AddDeviceData(CEpY4Data *pData,WORD nDeviceDataType, EPTIME64 &tm);
	void AddData(EPTIME64 &tm, DWORD nProtocol, DWORD nDataAddr, float fValue);

public:
	void AddDeviceDatas(BYTE *pBuffer, long nLength, EPTIME64 &tm);
	void AddDeviceDatas(CEpDeviceDatas *pDatas, EPTIME64 &tm);
	
};

// #define MAX_DEVICEDATAS_COUNT  10
// typedef struct epDeviceDatasMngr
// {
// 	long nCount;
// 	CEpDeviceDatas oDatas[MAX_DEVICEDATAS_COUNT];     //解析出来到的相关数据
// }EPDEVICEDATASMNGR, *PEPDEVICEDATASMNGR;

typedef struct epBufferPos
{
	BYTE *pBuffer;      //缓冲区地址
	DWORD dwBufferLen;  //缓冲区长度
	long nIndex;        //当前使用的缓冲区位置
	long nFrameCurr;    //当前帧使用的缓冲区索引位置
	DWORD dwState;      //状态，例如匹配的状态
	volatile __int64 n64ID;      //相关的ID，例如CaptureID
	DWORD nProtocol;      //规约类型
	CEpDeviceDatas* pDatas;     //解析出来到的相关数据
	INT nODDRLen;
	long nYxAddr;
	long nYcAddr;
	long nYtAddr;
	long nYkAddr;
	long bAddDetail;
}EPBUFFERPOS, *PEPBUFFERPOS;  


typedef struct epLongAndBytes
{
	union
	{
		DWORD dwValue;
		BYTE byteValue[4];
	};
}EPLONGANDBYTES;

#define POS_PROTOCOL_CAPTYPE   3
#define POS_PROTOCOL_PROTOTYPE 2
#define POS_PROTOCOL_FRAMETYPE 1
#define POS_PROTOCOL_FRAMEDIR  0

inline void Ep_SetProtocol_CapType(DWORD &nProtocol, WORD nCapType) //nType=UDP/TCP/---
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;
	v.byteValue[POS_PROTOCOL_CAPTYPE] = (BYTE)nCapType;
	nProtocol = v.dwValue;
}

inline void Ep_SetProtocol_ProtoType(DWORD &nProtocol, WORD nProtoType) //nType=101/104
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;
	v.byteValue[POS_PROTOCOL_PROTOTYPE] = (BYTE)nProtoType;
	nProtocol = v.dwValue;
}

inline void Ep_SetProtocol_ProtoType_Type(DWORD &nProtocol, WORD nType) //nType=101/104
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;

	DWORD nProtoType = v.byteValue[POS_PROTOCOL_PROTOTYPE];
	nProtoType = nProtoType & 0xF0;
	nProtoType = nProtoType | nType;

	v.byteValue[POS_PROTOCOL_PROTOTYPE] = (BYTE)nProtoType;
	nProtocol = v.dwValue;
}

inline void Ep_SetProtocol_ProtoType_Proto(DWORD &nProtocol, WORD nProto) //nType=101/104
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;

	DWORD nProtoType = v.byteValue[POS_PROTOCOL_PROTOTYPE];
	nProtoType = nProtoType & 0x0F;
	nProtoType = nProtoType | (nProto << 4);

	v.byteValue[POS_PROTOCOL_PROTOTYPE] = (BYTE)nProtoType;
	nProtocol = v.dwValue;
}

inline void Ep_SetProtocol_FrameType(DWORD &nProtocol, WORD nFrameType) //nFrameType
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;
	v.byteValue[POS_PROTOCOL_FRAMETYPE] = (BYTE)nFrameType;
	nProtocol = v.dwValue;
}
inline void Ep_SetProtocol_FrameDir(DWORD &nProtocol, WORD nFrameDir) 
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;
	v.byteValue[POS_PROTOCOL_FRAMEDIR] = (BYTE)nFrameDir;
	nProtocol = v.dwValue;
}

inline DWORD Ep_GetProtocol_CapType(DWORD &nProtocol)
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;
	return v.byteValue[POS_PROTOCOL_CAPTYPE];
}


inline DWORD Ep_GetProtocol_ProtoType(DWORD &nProtocol) 
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;
	return v.byteValue[POS_PROTOCOL_PROTOTYPE];
}

inline DWORD Ep_GetProtocol_ProtoType_Type(DWORD &nProtocol) //nType=101/104
{
	DWORD nType = Ep_GetProtocol_ProtoType(nProtocol);
	nType = nType & 0x0F;
	return nType;
}

inline DWORD Ep_GetProtocol_ProtoType_Proto(DWORD &nProtocol) //nType=101/104
{
	DWORD nType = Ep_GetProtocol_ProtoType(nProtocol);
	nType = nType >> 4;
	nType = nType & 0x0F;
	return nType;
}

inline DWORD Ep_GetProtocol_FrameType(DWORD &nProtocol) 
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;
	return v.byteValue[POS_PROTOCOL_FRAMETYPE];
}

inline DWORD Ep_GetProtocol_FrameDir(DWORD &nProtocol) 
{
	EPLONGANDBYTES v;
	v.dwValue = nProtocol;
	return v.byteValue[POS_PROTOCOL_FRAMEDIR];
}

inline void Ep_BackBufferPos(EPBUFFERPOS &oSrc, EPBUFFERPOS &oDest)
{
	oDest.pBuffer = oSrc.pBuffer;
	oDest.dwBufferLen = oSrc.dwBufferLen;
	oDest.nIndex = oSrc.nIndex;
	oDest.nFrameCurr = oSrc.nFrameCurr;
	//oDest.dwState = oSrc.dwState;
	oDest.n64ID = oSrc.n64ID;
	oDest.nProtocol = oSrc.nProtocol;
}

inline void Ep_InitEpBufferPos(EPBUFFERPOS &oBufferPos)
{
	memset(&oBufferPos, 0, sizeof(EPBUFFERPOS));
}

inline void Ep_InitEpBufferPos(PEPBUFFERPOS pBufferPos)
{
	memset(pBufferPos, 0, sizeof(EPBUFFERPOS));
}

//获得缓冲区剩下的长度
inline long Ep_EpBufferLeave(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->dwBufferLen - pBufferPos->nIndex;
}

//获得缓冲区当前的位置
inline BYTE* Ep_GetEpBufferCurr(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->pBuffer + pBufferPos->nIndex;
}

//获得帧开始的缓冲区
inline BYTE* Ep_GetEpFrameBufferBegin(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->pBuffer + pBufferPos->nIndex - pBufferPos->nFrameCurr;
}

//获得帧的当前位置
inline long Ep_GetEpFramePos(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->nFrameCurr;
}

//偏移缓冲区位置,继续下一个帧的操作
inline long Ep_OffsetEpBufferCurr(PEPBUFFERPOS pBufferPos, long nOffset)
{
	pBufferPos->nIndex += nOffset;
	pBufferPos->nFrameCurr += nOffset;
	return pBufferPos->nIndex;
}

//开始解析,置位帧操作缓冲区起始的位置
inline void Ep_BeginParseFrame(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->nFrameCurr = 0;
}

inline long Ep_GetParseFrameBuffer(PEPBUFFERPOS pBufferPos, BYTE **ppBuffer, long *pnLen)
{
	*pnLen = pBufferPos->nFrameCurr;
	*ppBuffer = pBufferPos->pBuffer + pBufferPos->nIndex - pBufferPos->nFrameCurr;
	return *pnLen;
}

inline void Ep_GetCycleMemBuffer(CEpCycleMemBuffer *pBuffer, PEPBUFFERPOS pBufPos);
// {
// 	Ep_InitEpBufferPos(pBufPos);
// 	pBufPos->dwBufferLen = pBuffer->GetDataLength();
// 	pBufPos->pBuffer = pBuffer->GetBuffer();
// 	pBufPos->nIndex = pBuffer->m_nCurrPos;
// }

typedef struct epParseMonitor
{
	EPBUFFERPOS buf_pos;
	CExBaseObject *pObj;
	long nMonitorState;
}EPPARSEMONITOR, *PEPPARSEMONITOR;

inline void Ep_SetParseMonitorState(PEPPARSEMONITOR pMonitor)
{
	pMonitor->nMonitorState = 1;
}

inline void Ep_InitParseMonitor(PEPPARSEMONITOR pMonitor, EPBUFFERPOS &buf_pos, CExBaseObject *pObj)
{
	pMonitor->buf_pos = buf_pos;
	pMonitor->pObj = pObj;
	pMonitor->nMonitorState = 0;
}

inline void Ep_InitParseMonitor(PEPPARSEMONITOR pMonitor, EPBUFFERPOS *pBufPos, CExBaseObject *pObj)
{
	Ep_InitParseMonitor(pMonitor, *pBufPos, pObj);
}

// inline PEPPARSEMONITOR Ep_CreateParseMonitor(EPBUFFERPOS &buf_pos, CExBaseObject *pObj)
// {
// 	PEPPARSEMONITOR pNew = (PEPPARSEMONITOR)malloc(sizeof(EPPARSEMONITOR));
// 	pNew->buf_pos = buf_pos;
// 	pNew->pObj = pObj;
// 	pNew->nMonitorState = 0;
// 	return pNew;
// }
// 
// inline PEPPARSEMONITOR Ep_CreateParseMonitor(EPBUFFERPOS *pBufPos, CExBaseObject *pObj)
// {
// 	PEPPARSEMONITOR pNew = (PEPPARSEMONITOR)malloc(sizeof(EPPARSEMONITOR));
// 	pNew->buf_pos = *pBufPos;
// 	pNew->pObj = pObj;
// 	pNew->nMonitorState = 0;
// 	return pNew;
// }

typedef struct epParseMonitorBuffer
{
	PEPPARSEMONITOR pMonitors; //
	long nCurrIndex;  //当前的索引
	long nCount;       //总的数量
}EPPARSEMONITORBUFFER, *PEPPARSEMONITORBUFFER;

// inline void Ep_InitParseMonitorBuffer(PEPPARSEMONITORBUFFER pMonitorBuffer)
// {
// 	pMonitorBuffer->nCount = 0;
// 	pMonitorBuffer->nCurrIndex = 0;
// 	pMonitorBuffer->pMonitors = NULL;
// }
// 
// inline void Ep_InitParseMonitorBuffer(EPPARSEMONITORBUFFER &oMonitorBuffer)
// {
// 	Ep_InitParseMonitorBuffer(&oMonitorBuffer);
// }
// 
// inline void Ep_FreeParseMonitorBuffer(PEPPARSEMONITORBUFFER pMonitorBuffer)
// {
// 	if (pMonitorBuffer == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (pMonitorBuffer->pMonitors != NULL)
// 	{
// 		free(pMonitorBuffer->pMonitors);
// 		pMonitorBuffer->pMonitors = NULL;
// 	}
// }
// 
// inline BOOL Ep_InitParseMonitorBuffer(PEPPARSEMONITORBUFFER pMonitorBuffer, long nCount)
// {
// 	ASSERT (pMonitorBuffer != NULL);
// 	Ep_FreeParseMonitorBuffer(pMonitorBuffer);
// 
// 	if (nCount > 0)
// 	{
// 		pMonitorBuffer->pMonitors =  (PEPPARSEMONITOR)malloc(nCount*sizeof(EPPARSEMONITOR));
// 	}
// 
// 	return (pMonitorBuffer->pMonitors != NULL);
// }

inline PEPPARSEMONITOR Ep_AddParseMonitorBuffer(PEPPARSEMONITORBUFFER pMonitorBuffer,EPBUFFERPOS &buf_pos, CExBaseObject *pObj, long &nCurrIndex)
{
	ASSERT (pMonitorBuffer != NULL);
	ASSERT(pMonitorBuffer->pMonitors != NULL);

	PEPPARSEMONITOR pCurr = &(pMonitorBuffer->pMonitors[pMonitorBuffer->nCurrIndex]);
	Ep_InitParseMonitor(pCurr, buf_pos, pObj);
	nCurrIndex = pMonitorBuffer->nCurrIndex;
	pMonitorBuffer->nCurrIndex++;

	if (pMonitorBuffer->nCurrIndex >= pMonitorBuffer->nCount)
	{
		pMonitorBuffer->nCurrIndex = 0;
	}

	return pCurr;
}

inline PEPPARSEMONITOR Ep_AddParseMonitorBuffer(PEPPARSEMONITORBUFFER pMonitorBuffer, PEPBUFFERPOS pBufPos, CExBaseObject *pObj, long &nCurrIndex)
{
	return Ep_AddParseMonitorBuffer(pMonitorBuffer, *pBufPos, pObj, nCurrIndex);
}

inline PEPPARSEMONITOR Ep_AddParseMonitorBuffer(EPPARSEMONITORBUFFER &oMonitorBuffer, PEPBUFFERPOS pBufPos, CExBaseObject *pObj, long &nCurrIndex)
{
	return Ep_AddParseMonitorBuffer(&oMonitorBuffer, *pBufPos, pObj, nCurrIndex);
}

inline PEPPARSEMONITOR Ep_AddParseMonitorBuffer(EPPARSEMONITORBUFFER &oMonitorBuffer,EPBUFFERPOS &buf_pos, CExBaseObject *pObj, long &nCurrIndex)
{
	return Ep_AddParseMonitorBuffer(&oMonitorBuffer, buf_pos, pObj, nCurrIndex);
}

inline PEPPARSEMONITOR Ep_GetCurrParseMonitor(PEPPARSEMONITORBUFFER pMonitorBuffer)
{
	ASSERT (pMonitorBuffer != NULL);
	ASSERT(pMonitorBuffer->pMonitors != NULL);

	return &(pMonitorBuffer->pMonitors[pMonitorBuffer->nCurrIndex]);
}

inline PEPPARSEMONITOR Ep_GetCurrParseMonitor(EPPARSEMONITORBUFFER &oMonitorBuffer)
{
	ASSERT(oMonitorBuffer.pMonitors != NULL);

	return &(oMonitorBuffer.pMonitors[oMonitorBuffer.nCurrIndex]);
}

inline PEPPARSEMONITOR Ep_GetParseMonitor(EPPARSEMONITORBUFFER &oMonitorBuffer, long nIndex)
{
	ASSERT(oMonitorBuffer.pMonitors != NULL);

	if (nIndex < 0 || nIndex >= oMonitorBuffer.nCount)
	{
		return NULL;
	}

	return &(oMonitorBuffer.pMonitors[nIndex]);
}

inline PEPPARSEMONITOR Ep_GetParseMonitor(PEPPARSEMONITORBUFFER pMonitorBuffer, long nIndex)
{
	ASSERT(pMonitorBuffer != NULL);

	return Ep_GetParseMonitor(*pMonitorBuffer, nIndex);
}

inline void Ep_FreeDatas(CEpDeviceDatas* pDatas)
{
	//ZeroMemory(pDatas, sizeof(CEpDeviceDatas));
	pDatas->m_nDeviceDataType = EP_DEVICE_DATA_EMPTY;
//	pDatas->nDataCount = 0;
	pDatas->DeleteAll();
}

//////////////////////////////////////////////////////////////////////////
//EPTIME64
//YEAR=D63-D52  MONTH=D51-D48 DAY=D47-D43  HOUR=D42-D38  MINUTE=D37-D32  SECOND-MS-US=D31-D0
void Ep_TIME64_to_TIME64EX(EPTIME64 &tmSrc, EPTIME64EX &tmDest);
void Ep_TIME64EX_to_TIME64(EPTIME64EX &tmSrc, EPTIME64 &tmDest);
void Ep_GetLocalTm_TIME64EX(EPTIME64EX &tmDest);
void Ep_TIME64EX_to_SYSTEMTIME(EPTIME64EX &tmSrc, SYSTEMTIME &tmDest);
void Ep_SYSTEMTIME_to_TIME64EX(SYSTEMTIME &tmSrc, EPTIME64EX &tmDest);

inline void Ep_EPTIME64Ex_To_String(EPTIME64EX &tm64Ex, CString &strTime)
{
	strTime.Format(_T("%d-%2d-%2d %2d:%2d:%2d %3d.%3d"), tm64Ex.wYear
		, tm64Ex.wMonth, tm64Ex.wDay, tm64Ex.wHour, tm64Ex.wMinute
		, tm64Ex.wSecond, tm64Ex.wMilliseconds, tm64Ex.wMicrosecond);
}

inline void Ep_EPTIME64_To_String(EPTIME64 &tm64, CString &strTime)
{
	EPTIME64EX tm64Ex;
	Ep_TIME64_to_TIME64EX(tm64, tm64Ex);
	Ep_EPTIME64Ex_To_String(tm64Ex, strTime);
}


inline BOOL Ep_IsTimeIn(EPTIME64 &tmb, EPTIME64 &tme, EPTIME64 &tm)
{
	return (tmb.n64Time <= tm.n64Time && tm.n64Time <= tme.n64Time);
}

inline BOOL Ep_IsTimeAreaIn(EPTIME64 &tm1b, EPTIME64 &tm1e, EPTIME64 &tm2b, EPTIME64 &tm2e)
{
	if (Ep_IsTimeIn(tm1b, tm1e, tm2b))
	{
		return TRUE;
	}

	if (Ep_IsTimeIn(tm1b, tm1e, tm2e))
	{
		return TRUE;
	}

	if (Ep_IsTimeIn(tm2b, tm2e, tm1b))
	{
		return TRUE;
	}

	if (Ep_IsTimeIn(tm2b, tm2e, tm1e))
	{
		return TRUE;
	}

	return FALSE;
}

inline SYSTEMTIME Ep_64TimeSystemTime(EPTIME64 &tm)
{	
	SYSTEMTIME tmSys;
	EPTIME64EX tm64Ex;
	Ep_TIME64_to_TIME64EX(tm, tm64Ex);
	Ep_TIME64EX_to_SYSTEMTIME(tm64Ex, tmSys);
	return tmSys;
}

inline void Ep_64TimeSystemTime(EPTIME64 &tm, SYSTEMTIME &tmSys)
{	
	EPTIME64EX tm64Ex;
	Ep_TIME64_to_TIME64EX(tm, tm64Ex);
	Ep_TIME64EX_to_SYSTEMTIME(tm64Ex, tmSys);
}

inline void Ep_SystemTime_to_64Time(SYSTEMTIME &tmSrc, EPTIME64 &tmDest)
{	
	EPTIME64EX tm64Ex;
	Ep_SYSTEMTIME_to_TIME64EX(tmSrc, tm64Ex);
	Ep_TIME64EX_to_TIME64(tm64Ex, tmDest);
}

inline void Ep_ZeroEpBufferPos(PEPBUFFERPOS pBufPos)
{
//	Ep_FreeDatas(pBufPos->oDatas);
	ZeroMemory(pBufPos, sizeof(EPBUFFERPOS));
}



#endif // !defined(_PROTOCOLGLOBALBASEDEFINE_H__)
