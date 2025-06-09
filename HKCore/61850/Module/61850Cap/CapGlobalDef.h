#pragma once

#include "..\..\..\Module\CriticalSection\SynCriticalSection.h"
#include "..\..\..\Module\BaseClass\ExBaseList.h"

#include "EthernetCapGlobalDef.h"
#include "ProtocolBase\ProtocolGlobalDef.h"

#define WM_CAP_WRITE_SMDB   (WM_USER+854)
#define WM_SHOW_CAP_INFOR   (WM_USER+101)

extern volatile __int64 g_nCaptureID;
volatile __int64 st_Cap_GenerateCaptureID();

#define STCAPPCLASSID_BASECLASS        (CLASSID_BASECLASS+0x04000000)
#define STCAPPCLASSID_LISTCLASS        (CLASSID_LISTCLASS+0x04000000)

#define STCAPCLASSID_BBINFOR           (STCAPPCLASSID_BASECLASS + 0X00000000)
#define STCAPCLASSID_BYTEBLOCK         (STCAPPCLASSID_LISTCLASS + 0X00000002)



//#pragma pack(1)

extern volatile __int64 g_nCaptureID;
volatile __int64 Ep_Cap_GenerateCaptureID();

typedef struct ep_ether_cap_time
{
	WORD year;
	WORD month;
	WORD day;
	WORD hour;
	WORD minute;
	WORD second;
	long usec;
}EP_ETHER_CAP_TIME;

void ep_cap_timeval_to_time(const struct timeval &ts, EP_ETHER_CAP_TIME &time);
void ep_time_to_cap_timeval(const EP_ETHER_CAP_TIME &time, struct timeval &ts);
void ep_curr_cap_timeval(struct timeval &ts);


extern DWORD g_nEpCapBufferWriteState;
// extern DWORD g_nEpCapBufferMngrFreeState;
extern DWORD g_nEpCapWriteCounter;

extern CAutoCriticSection g_oCapWriteCriticSection;


inline void Ep_SetCanWriteEpCapState()
{
	//CAutoSimpleLock oLock(g_oCapWriteCriticSection);
	g_nEpCapBufferWriteState = 1;
	//	CLogPrint::LogString(LOGLEVEL_TRACE, _T("Ep_SetCanWriteEpCapState"));
}


inline BOOL Ep_IsInWriteEpCapState()
{
	//CAutoSimpleLock oLock(g_oCapWriteCriticSection);

	return (g_nEpCapBufferWriteState == 2);
}

inline BOOL Ep_SetInWriteEpCapState()
{
	//CAutoSimpleLock oLock(g_oCapWriteCriticSection);
	g_nEpCapBufferWriteState = 2;
	return TRUE;
}

inline void Ep_FinishInWriteEpCapState()
{
	//CAutoSimpleLock oLock(g_oCapWriteCriticSection);
	g_nEpCapBufferWriteState = 3;
	//	CLogPrint::LogString(LOGLEVEL_TRACE, _T("Ep_FinishInWriteEpCapState"));
}

inline BOOL Ep_IsFinishInWriteEpCapState()
{
	//CAutoSimpleLock oLock(g_oCapWriteCriticSection);
	return (g_nEpCapBufferWriteState == 3 || g_nEpCapBufferWriteState == 0);
}


//////////////////////////////////////////////////////////////////////////

typedef struct ep_ip_address : public in_addr
{
}ep_ip_address;

typedef struct ep_ether_cap_ip
{
	ep_ip_address ip;
	u_short port;
}EP_ETHER_CAP_IP;

typedef struct ep_ether_cap_ip_group
{
	EP_ETHER_CAP_IP src;
	EP_ETHER_CAP_IP dst;
}EP_ETHER_CAP_IP_GROUP;

typedef struct ep61850Cap_addr
{
	BYTE  dstMac[6];
	BYTE  srcMac[6];
	UINT16 APPID;
}EP_61850_CAP_ADDR, *PEP_61850_CAP_ADDR;

typedef struct ep_cap_addr
{
	union
	{
		EP_61850_CAP_ADDR addr_61850;
		EP_ETHER_CAP_IP_GROUP addr_tradition;//Traditional protocol
	};
}EP_CAP_ADDR, *PEP_CAP_ADDR;

typedef struct epCapBufferItem : public EP_CAP_ADDR
{
// 	BYTE  dstMac[6];
// 	BYTE  srcMac[6];
// 	UINT16 APPID;
	UINT16 nProtocol;
	double Time;
	long nChCount;
}EPCAPBUFFERITEM, *PEPCAPBUFFERITEM;


typedef struct epTime64
{
	union
	{
		volatile __int64 n64Time;
		BYTE tm[8];
	};
}EPTIME64, *PEPTIME64;

//2013-11-14
typedef struct epCapDbData
{
	EP_ETHER_CAP_IP_GROUP cap_addr; //ip���߶˿�
	EPTIME64 tm; //cap��ʱ��
	DWORD nProtocol;  //��Լ����
	DWORD nDataAddr;
	float fValue;
	//	volatile __int64 n64DeviceDataPos;  //�������ļ���λ��,���nDataType=0����Ч��λ��
}EPCAPDBDATA, *PEPCAPDBDATA;


typedef struct epCapDbBufferIndex
{
	volatile __int64 n64CapID;   //cap id
	//EP_ETHER_CAP_IP_GROUP cap_addr; //ip���߶˿�
	EP_CAP_ADDR cap_addr;
	DWORD nProtocol;  //��Լ����
	EPTIME64 tm; //cap��ʱ��
	// 	WORD nLength;  //cap�ĳ���
	WORD nFrameLen;  //���ĳ���
	//WORD nDeviceDataLen;  //�豸���ݳ���
	volatile __int64 n64CapFramePos; //cap�����ļ�λ��
	volatile __int64 n64CapDataPos; //cap�����ļ�λ��
	//EPDEVICEDATAHEAD oDataHead;  //����ͷ
	//	volatile __int64 n64DeviceDataPos;  //�������ļ���λ��,���nDataType=0����Ч��λ��
}EPCAPDBBUFFERINDEX, *PEPCAPDBBUFFERINDEX;



// typedef struct epCapDbBufferIndex0
// {
// 	EPTIME64 tm; //cap��ʱ��
// 	volatile __int64 n64CapDataIndexPos; //cap�����ļ�λ��
// }EPCAPDBBUFFERINDEX0, *PEPCAPDBBUFFERINDEX0;

typedef struct epCapDbBufferIndex0Ex
{
	EPTIME64 tm; //cap��ʱ��
	volatile __int64 n64CapFrameIndexPos; //cap�����ļ�λ��
	volatile __int64 n64DataPos; //��Լ�����ļ�λ��
}EPCAPDBBUFFERINDEX0EX, *PEPCAPDBBUFFERINDEX0EX;

//#define EP_CAP_DBINDEX0_COUNT   1440 //һ��Сʱһ��һ��������60��  24 * 60
// typedef struct epCapDbBufferIndex0Mngr
// {
// 	long nCurrIndex;  //��ǰ����Ч����
// 	long nIndexCount;  //��Ч�����ĸ���
// 	long nIndexMaxCount;  //�����������
// 	PEPCAPDBBUFFERINDEX0 pIndex0s; //�����б�
// }EPCAPDBBUFFERINDEX0MNGR, *PEPCAPDBBUFFERINDEX0MNGR;

typedef struct epCapDbBufferIndex0MngrEx
{
	long nCurrIndex;  //��ǰ����Ч����
	long nIndexCount;  //��Ч�����ĸ���
	long nIndexMaxCount;  //�����������
	PEPCAPDBBUFFERINDEX0EX pIndex0s; //�����б�
}EPCAPDBBUFFERINDEX0MNGREX, *PEPCAPDBBUFFERINDEX0MNGREX;

#define CAPDB_HEAD_STRING_SIZE 9
static const char g_strCapDbIndexHead[CAPDB_HEAD_STRING_SIZE] = "EPOTOCAP";

typedef struct epSmDbFilePos
{
	volatile __int64 n64MaxCapID;
	volatile __int64 n64DbIndexMax;       //������������
	volatile __int64 n64DbIndexCount;     //��������Ŀ
	volatile __int64 n64DbIndexCurrIndex;  //�����ĵ�ǰ���

	volatile __int64 n64DbIndexBeginPos;   //�������ݿ�ӳ����ʼλ��
	volatile __int64 n64DbIndexCurrPos;    //�������ݿ��ϴ�д���λ��
	DWORD dwDbIndexState;

	volatile __int64 n64CapFrmDvBeginPos;  //cap������ʼӰ��λ��
	volatile __int64 n64CapFrmDvCurrPos;   //cap�����ϴ�д��λ��

	volatile __int64 n64CapDataBeginPos;  //cap������ʼӰ��λ��
	volatile __int64 n64CapDataCurrPos;   //cap�����ϴ�д��λ��
	DWORD dwDbCapFrmDvState;

	EPTIME64 tmCurr;              //���һ�����ݵ�ʱ��
}EPSMDBFILEPOS, *PEPSMDBFILEPOS;

typedef struct epCapDbIndexHead
{
	BYTE strHead[CAPDB_HEAD_STRING_SIZE];
	DWORD dwVersion;
	DWORD dwState;
	EPSMDBFILEPOS oDbFilePos;
}EPCAPDBINDEXHEAD, *PEPCAPDBINDEXHEAD;

#define epCapDb_version_1   0x00010000
#define epCapDb_version_2   0x00020000

static DWORD g_dwCurrCapDbVersion  = epCapDb_version_2;
static DWORD g_dwCapDbVersionError  = 0;

inline BOOL IsCapDbVersionError()
{
	return (g_dwCapDbVersionError != 0);
}


//////////////////////////////////////////////////////////////////////////
//

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


inline void ep_cap_time_to_64timeex(EP_ETHER_CAP_TIME &time, EPTIME64EX &tm64)
{
	DWORD dwValue = time.usec;
	//wMicrosecond
	tm64.wMicrosecond = dwValue % 1000;

	//wMilliseconds
	dwValue -= tm64.wMicrosecond;
	dwValue /= 1000;
	tm64.wMilliseconds = dwValue % 1000;

	//second
	tm64.wSecond = time.second;
	tm64.wMinute = time.minute;
	tm64.wHour = time.hour;
	tm64.wDay = time.day;
	tm64.wMonth = time.month;
	tm64.wYear = time.year;
}

inline void ep_64timeex_to_cap_time(EPTIME64EX &tm64, EP_ETHER_CAP_TIME &time)
{
	time.usec = tm64.wMilliseconds * 1000 + tm64.wMicrosecond;
	time.second = tm64.wSecond;
	time.minute = tm64.wMinute;
	time.hour = tm64.wHour;
	time.day = tm64.wDay;
	time.month = tm64.wMonth;
	time.year = tm64.wYear;
}

inline void ep_cap_timeval_to_64timeex(const struct timeval &ts, EPTIME64EX &tm64)
{
	EP_ETHER_CAP_TIME tmCap;
	ep_cap_timeval_to_time(ts, tmCap);
	ep_cap_time_to_64timeex(tmCap, tm64);
}

inline void ep_cap_timeval_to_64time(const struct timeval &ts, EPTIME64 &tm64)
{
	EPTIME64EX tm64ex;
	ep_cap_timeval_to_64timeex(ts, tm64ex);
	Ep_TIME64EX_to_TIME64(tm64ex,tm64); 
}

inline void Ep_GetCurr64Time(EPTIME64 &tm)
{
	EPTIME64EX tmex;
	Ep_GetLocalTm_TIME64EX(tmex);
	Ep_TIME64EX_to_TIME64(tmex,tm); 
}


inline void Ep_ZeroEpBufferPos(PEPBUFFERPOS pBufPos)
{
	//	Ep_FreeDatas(pBufPos->oDatas);
	ZeroMemory(pBufPos, sizeof(EPBUFFERPOS));
}
