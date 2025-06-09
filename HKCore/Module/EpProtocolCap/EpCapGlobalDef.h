#pragma once

#include "..\..\Module\CriticalSection\SynCriticalSection.h"

#define CAPTHREAD_ETHERNET  (CLASSID_BASECLASS + 0X00FF0001)
#define CAPTHREAD_SERIAL    (CLASSID_BASECLASS + 0X00FF0002)

#define WM_CAP_WRITE_SMDB   (WM_USER+854)
#define WM_SHOW_CAP_INFOR   (WM_USER+101)

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
	EP_ETHER_CAP_IP_GROUP ipGroup; //ip或者端口
	EPTIME64 tm; //cap的时间
	DWORD nProtocol;  //规约类型
	DWORD nDataAddr;
	float fValue;
	//	volatile __int64 n64DeviceDataPos;  //数据在文件的位置,如果nDataType=0，无效的位置
}EPCAPDBDATA, *PEPCAPDBDATA;

