#pragma once

#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../Module/BaseClass/ExBaseList.h"

#include "EthernetCapGlobalDef.h"
#include "ProtocolBase/ProtocolGlobalDef.h"

extern volatile __int64 g_nCaptureID;
volatile __int64 st_Cap_GenerateCaptureID();

#define STCAPPCLASSID_BASECLASS        (CLASSID_BASECLASS+0x04000000)
#define STCAPPCLASSID_LISTCLASS        (CLASSID_LISTCLASS+0x04000000)

#define STCAPCLASSID_BBINFOR           (STCAPPCLASSID_BASECLASS + 0X00000000)
#define STCAPCLASSID_BYTEBLOCK         (STCAPPCLASSID_LISTCLASS + 0X00000002)

#define Cap_Smv92Error_LoseSyn                                0//失步
#define Cap_Smv92Error_Loss                                   1//丢包
#define Cap_Smv92Error_Repeat                                 2//重复
#define Cap_Smv92Error_NumErr                                 3//采样序号错
#define Cap_Smv92Error_LengthParaErr                          4//长度参数错
#define Cap_Smv92Error_APDUCodeErr                            5
#define Cap_Smv92Error_ASDUCodeErr                            6
#define Cap_Smv92Error_TimeOut                                7
#define Cap_Smv92Error_Shake                                  8
#define Cap_Smv92Error_CommLoss                               9
#define Cap_Smv92Error_CommRecover                            10
#define Cap_Smv92Error_QualityErr                             11
#define Cap_Smv92Error_SVInvalid                              12
#define Cap_Smv92Error_TestStatus                             13
#define Cap_Smv92Error_DelayChanged                           14
#define Cap_Smv92Error_ASDUNumChanged                         15
#define Cap_Smv92Error_ADIncstc                               16
#define Cap_Smv92Error_IllegalData                            17



#define Cap_GsError_DummyBit                                           0
#define Cap_GsError_SQNumLoss                                          1
#define Cap_GsError_SQNumInitError                                     2
#define Cap_GsError_SQNumDisorder                                      3
#define Cap_GsError_SQNumRepeat                                        4
#define Cap_GsError_STNumLoss                                          5
#define Cap_GsError_DevRestart                                         6
#define Cap_GsError_STNumDisorder                                      7
#define Cap_GsError_APDUCodeErr                                        8
#define Cap_GsError_ASDUCodeErr                                        9
#define Cap_GsError_LengthParaErr                                     10
#define Cap_GsError_TimeOut                                           11
#define Cap_GsError_CommLoss                                          12
#define Cap_GsError_CommRecover                                       13
#define Cap_GsError_LivingTimeInvalid                                 14
#define Cap_GsError_ClockFault                                        15
#define Cap_GsError_ClockNotSyn                                       16
#define Cap_GsError_Illegal                                           17
// #define Cap_GsError_DummyBit                                          18
// #define Cap_GsError_DummyBit                                          19

//定义录波接受缓存，默认最大缓存为K，即K批量处理一次。
#define CAP_RCD_BUFFER_MAX_LEN   204800

//下面的用的解PCAP文件数据用的数据结构 马扬名ADD  20202-7-3 
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
typedef short _Int16;
typedef long _Int32;

#define Protocol61850_Pkg_Type_FT3                  3
#define Protocol61850_Pkg_Type_MUTIMEDATA           4//合并单元时间数据


// mym add 2020-7-14
inline int ConverStrToNum(CString strDealStr)
{
	return CString_To_long(strDealStr);
}

inline CString DecToBin(CString strDec)//10进制到2进制
{
	int nDec = ConverStrToNum(strDec);

	int nYushu, nShang;

	CString strBin = _T(""), strTemp;
	char buf[2];
	buf[0] = ' ';
	buf[1] = ' ';

	BOOL bContinue = TRUE;

	while ( bContinue )
	{
		nYushu = nDec%2;
		nShang = nDec/2;
		sprintf(buf,_T("%d"),nYushu);
		strTemp = strBin;
        strBin.Format(_T("%s%s"), buf, strTemp.GetString());
		nDec = nShang;
		if (nShang==0)
			bContinue=FALSE;
	}

	int nTemp = strBin.GetLength()%4;
	switch(nTemp)
	{
	case 1:
        strTemp.Format(_T("000%s"),strBin.GetString());
		strBin = strTemp;
		break;
	case 2:
        strTemp.Format(_T("00%s"),strBin.GetString());
		strBin = strTemp;
		break;
	case 3:
        strTemp.Format(_T("0%s"), strBin.GetString());
		strBin = strTemp;
		break;
	default:
		break;
	}
	return strBin;
}


inline CString HexToBin(CString strHexEx)//16-2
{
	CString strDec,strBin,strHex;
	strHex = strHexEx;
	DWORD dwHex = strtoul(strHex.GetString(), NULL, 16);
	strDec.Format(_T("%uld"),  dwHex);
	strBin = DecToBin(strDec);
	return strBin;
}
//PCAP文件头
struct _file_header
{
	_Int32 iMagic;
	_Int16 iMaVersion;
	_Int16 iMiVersion;
	_Int32 iTimezone;
	_Int32 iSigFlags;
	_Int32 iSnapLen;
	_Int32 iLinkType;
};

//数据包头
struct _pkthdr
{
	_Int32 iTimeSecond;
	_Int32 iTimeSS;
	_Int32 iPLength;
	_Int32 iLength;
};
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//

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

//zhouhj 保存pcap文件时的问题起始头部分 2023.9.6
extern BYTE g_bytePcapHead_us[24];
extern BYTE g_bytePcapHead_ns[24];

extern CAutoCriticSection g_oCapWriteCriticSection;


inline void Ep_SetCanWriteEpCapState()
{
	//CAutoSimpleLock oLock(g_oCapWriteCriticSection);
	g_nEpCapBufferWriteState = 1;
	//	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ep_SetCanWriteEpCapState"));
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
	//	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ep_FinishInWriteEpCapState"));
}

inline BOOL Ep_IsFinishInWriteEpCapState()
{
	//CAutoSimpleLock oLock(g_oCapWriteCriticSection);
	return (g_nEpCapBufferWriteState == 3 || g_nEpCapBufferWriteState == 0);
}


//////////////////////////////////////////////////////////////////////////

#ifdef _PSX_QT_LINUX_
typedef struct ep_ip_address
{
}ep_ip_address;
#else
typedef struct ep_ip_address : public in_addr
{
}ep_ip_address;
#endif

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
	BYTE  srcMac[6];
	BYTE  dstMac[6];
    unsigned short APPID;// zhouhj 2023.11.14 在FT3报文时,将AppID内容标记为光口
}EP_61850_CAP_ADDR, *PEP_61850_CAP_ADDR;

//2020-4-27  同 EP_61850_CAP_ADDR
// typedef struct epSttCap_addr
// {
// 	BYTE  srcMac[6];
// 	BYTE  dstMac[6];
// 	UINT16 APPID;
// 	UINT16 filber_smv_gs;
// }EP_STT_CAP_ADDR, *PEP_EP_STT_CAP_ADDR;


typedef struct ep_cap_addr
{
	union
	{
		EP_61850_CAP_ADDR addr_61850;
		EP_ETHER_CAP_IP_GROUP addr_tradition;//Traditional protocol
		//EP_STT_CAP_ADDR addr_stt; //2020-04-25  lijq  AT02D
		//2020-4-27  同 EP_61850_CAP_ADDR
	};
}EP_CAP_ADDR, *PEP_CAP_ADDR;

typedef struct epCapBufferItem : public EP_CAP_ADDR
{
// 	BYTE  dstMac[6];
// 	BYTE  srcMac[6];
// 	UINT16 APPID;
    unsigned short nProtocol;
	__int64 Time;
//	int usec;//zhouhj 2023.7.23 增加报文时间戳中us记录  2023.8.9 zhouhj 删除,全部时间都记录在Time内
	long nChCount;
}EPCAPBUFFERITEM, *PEPCAPBUFFERITEM;

//yyj
#define STT_AT02_FIXED_HEAD			0x05640564
#define STT_AT02_FIXED_HEAD_LEN		4

//2020-04-23  lijq STT AT02
//#define SST_AT02_PKT_HEAD_USE_RESERVE

typedef struct _SttAt02_Pkt_head_
{
	DWORD hd_flag;
	long len;  //len*4=整个报文的长度
	UINT utc_s;
	UINT utc_ns;
	unsigned short filber_smv_gs;
	unsigned short appid;
	unsigned short packet_len;  //61850报文的长度
	unsigned short crc;
#ifdef SST_AT02_PKT_HEAD_USE_RESERVE
	unsigned short sv_smp_cnt;
	unsigned short reserive;
#else
	long nIndex;
#endif
}SST_AT02_PKT_HEAD, *PSST_AT02_PKT_HEAD;

//2022-6-19  lijunqing
// 很容易出现丢包的情况，为了排除是因为应用程序消耗资源比较大的情况，只做
// AT02D报文头分析。
#define STT_AT02_HDAD_STC_MAX  20
typedef struct _Stt_At02_Pkt_Head_Stc_
{
	unsigned short appid;
	unsigned short prev_sv_smp_cnt;
	long nSmpCntError;  //SampleCount Error 统计
	long nPkgCount;  //收到的报文总数
	long nMaxTimeDiff;//最大时间差单位微妙

	void init()
	{
		appid=0;
		prev_sv_smp_cnt = -1;
		nSmpCntError=0;
		nPkgCount = 0;
		nMaxTimeDiff = 0;
	}
}STT_AT02_PKT_HEAD_STC, *PSTT_AT02_PKT_HEAD_STC;

typedef struct _Stt_At02_Pkt_Head_Stc_Mngr_
{
	long nCount;
	STT_AT02_PKT_HEAD_STC oHeadStc[STT_AT02_HDAD_STC_MAX];

	void init()
	{
		nCount = 0;

		for (long k=0; k<STT_AT02_HDAD_STC_MAX; k++)
		{
			oHeadStc[k].init();
		}
	}
}STT_AT02_PKT_HEAD_STC_MNGR, *PSTT_AT02_PKT_HEAD_STC_MNGR;

//2020-04-27  61850 head
typedef struct _stt_61850_pkt_head
{
	BYTE  srcMac[6];
	BYTE  dstMac[6];
    unsigned short EtherType;
    unsigned short APPID;
    unsigned short Length;
}STT_61850_PKT_HEAD, *PSTT_61850_PKT_HEAD;

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
	EP_ETHER_CAP_IP_GROUP cap_addr; //ip或者端口
	EPTIME64 tm; //cap的时间
	DWORD nProtocol;  //规约类型
	DWORD nDataAddr;
	float fValue;
	//	volatile __int64 n64DeviceDataPos;  //数据在文件的位置,如果nDataType=0，无效的位置
}EPCAPDBDATA, *PEPCAPDBDATA;


typedef struct epCapDbBufferIndex
{
	volatile __int64 n64CapID;   //cap id
	//EP_ETHER_CAP_IP_GROUP cap_addr; //ip或者端口
	EP_CAP_ADDR cap_addr;
	DWORD nProtocol;  //规约类型
	EPTIME64 tm; //cap的时间
	// 	WORD nLength;  //cap的长度
	WORD nFrameLen;  //报文长度
	//WORD nDeviceDataLen;  //设备数据长度
	volatile __int64 n64CapFramePos; //cap报文文件位置
	volatile __int64 n64CapDataPos; //cap数据文件位置
	//EPDEVICEDATAHEAD oDataHead;  //数据头
	//	volatile __int64 n64DeviceDataPos;  //数据在文件的位置,如果nDataType=0，无效的位置
}EPCAPDBBUFFERINDEX, *PEPCAPDBBUFFERINDEX;



// typedef struct epCapDbBufferIndex0
// {
// 	EPTIME64 tm; //cap的时间
// 	volatile __int64 n64CapDataIndexPos; //cap数据文件位置
// }EPCAPDBBUFFERINDEX0, *PEPCAPDBBUFFERINDEX0;

typedef struct epCapDbBufferIndex0Ex
{
	EPTIME64 tm; //cap的时间
	volatile __int64 n64CapFrameIndexPos; //cap报文文件位置
	volatile __int64 n64DataPos; //规约数据文件位置
}EPCAPDBBUFFERINDEX0EX, *PEPCAPDBBUFFERINDEX0EX;

//#define EP_CAP_DBINDEX0_COUNT   1440 //一个小时一个一级索引，60天  24 * 60
// typedef struct epCapDbBufferIndex0Mngr
// {
// 	long nCurrIndex;  //当前的有效索引
// 	long nIndexCount;  //有效索引的个数
// 	long nIndexMaxCount;  //最大索引数量
// 	PEPCAPDBBUFFERINDEX0 pIndex0s; //索引列表
// }EPCAPDBBUFFERINDEX0MNGR, *PEPCAPDBBUFFERINDEX0MNGR;

typedef struct epCapDbBufferIndex0MngrEx
{
	long nCurrIndex;  //当前的有效索引
	long nIndexCount;  //有效索引的个数
	long nIndexMaxCount;  //最大索引数量
	PEPCAPDBBUFFERINDEX0EX pIndex0s; //索引列表
}EPCAPDBBUFFERINDEX0MNGREX, *PEPCAPDBBUFFERINDEX0MNGREX;

#define CAPDB_HEAD_STRING_SIZE 9
static const char g_strCapDbIndexHead[CAPDB_HEAD_STRING_SIZE] = "EPOTOCAP";

typedef struct epSmDbFilePos
{
	volatile __int64 n64MaxCapID;
	volatile __int64 n64DbIndexMax;       //索引的最大个数
	volatile __int64 n64DbIndexCount;     //索引的数目
	volatile __int64 n64DbIndexCurrIndex;  //索引的当前编号

	volatile __int64 n64DbIndexBeginPos;   //索引数据库映射起始位置
	volatile __int64 n64DbIndexCurrPos;    //索引数据库上次写入的位置
	DWORD dwDbIndexState;

	volatile __int64 n64CapFrmDvBeginPos;  //cap报文起始影射位置
	volatile __int64 n64CapFrmDvCurrPos;   //cap报文上次写入位置

	volatile __int64 n64CapDataBeginPos;  //cap数据起始影射位置
	volatile __int64 n64CapDataCurrPos;   //cap数据上次写入位置
	DWORD dwDbCapFrmDvState;

	EPTIME64 tmCurr;              //最后一个数据的时间
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

//xujinqiang20200612add: 索引结构体，用于索引文件读写
typedef struct _Stt_Pkt_Index_
{
	EP_ETHER_CAP_TIME time;
	__int64 pos;
}SST_PKT_INDEX,*PSST_PKT_INDEX;

typedef struct _Stt_Pkt_Sm_Index_
{
	BYTE Version[8];
	__int64 n64SmWritePos;
	__int64 n64SmWriteLen;
	__int64 n64SmMaxLen;
	__int64 n64SmParsePos;
	__int64 n64IndexCount;
	SST_PKT_INDEX oIndex;
}SST_PKT_SM_INDEX,*PSST_PKT_SM_INDEX;

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
	strTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d %03d.%03d"), tm64Ex.wYear
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

inline double ep_tm_n64_t0_double(__int64 n64)
{
	double dTime = (double)(n64 & 0xFFFFFFFF);
	dTime /= 1000000000;
	dTime +=  n64 >> 32;
	return dTime;
}

inline double ep_tm_n64_sub(__int64 n64T1, __int64 n64T2)
{
	double dTime1 = ep_tm_n64_t0_double(n64T1);
	double dTime2 = ep_tm_n64_t0_double(n64T2);

	return dTime1 - dTime2;
}

inline void ep_cap_timeval_to_string_ns(__int64 n64Time, CString &strTime)
{
	//n64Time H32=s   L32=ns;
	struct timeval ts;
	EPTIME64EX tm;
	ts.tv_sec = n64Time >> 32;
	ts.tv_usec = n64Time & 0xFFFFFFFF;
	long ns = ts.tv_usec  % 1000;
	ts.tv_usec /= 1000;
	ep_cap_timeval_to_64timeex(ts, tm);
	Ep_EPTIME64Ex_To_String(tm, strTime);
	strTime.AppendFormat(_T(".%d"), ns);
}

inline void ep_cap_timeval_to_string_us(__int64 n64Time, CString &strTime)
{
	//n64Time H32=s   L32=ns;
	struct timeval ts;
	EPTIME64EX tm;
	ts.tv_sec = n64Time >> 32;
	ts.tv_usec = n64Time & 0xFFFFFFFF;
	ep_cap_timeval_to_64timeex(ts, tm);
	Ep_EPTIME64Ex_To_String(tm, strTime);
}

inline void ep_cap_timeval_to_string_ns(double dTime, CString &strTime)
{
	//n64Time H32=s   L32=ns;
	struct timeval ts;
	EPTIME64EX tm;
	ts.tv_sec = (long)dTime;
	dTime = (dTime - ts.tv_sec) * 1000000000;
	ts.tv_usec =   (long)dTime ;
	long ns = ts.tv_usec  % 1000;
	ts.tv_usec /= 1000;
	ep_cap_timeval_to_64timeex(ts, tm);
	Ep_EPTIME64Ex_To_String(tm, strTime);
	strTime.AppendFormat(_T(".%03d"), ns);
}

inline void ep_cap_timeval_to_string_us(double dTime, CString &strTime)
{
	//n64Time H32=s   L32=ns;
	struct timeval ts;
	EPTIME64EX tm;
	ts.tv_sec = (long)dTime;
	dTime = (dTime - ts.tv_sec) * 1000000;
	ts.tv_usec =   (long)dTime ;
	ep_cap_timeval_to_64timeex(ts, tm);
	Ep_EPTIME64Ex_To_String(tm, strTime);
}

void stt_GetVariablePhaseID(const CString &strName, CString &strPhaseID, CString &strUnit);
long GetTimeGap_EpcapBufferItem(EPCAPBUFFERITEM *pCurrItem,EPCAPBUFFERITEM *pPrevItem,BOOL bUSec = TRUE);//2023.7.23 获取两帧报文之间的时间差,参数3为单位是否为us,否则为ns
long GetTimeGap_EpcapBufferItem(__int64 u64_CurrTime,__int64 u64_PrevTime,BOOL bUSec = TRUE);//dingxy 20240827 函数类型变为long,防止负数转化为很大的值

bool stt_save_pcap_file(const CString &strSrcAt02dFile,const char *pszSavePcapFile);//将*.at02d文件转换为Pcap文件
bool stt_save_pcap_file_ft3(const CString &strSrcAt02dFile,const char *pszSavePcapFile);//将*.at02d文件转换为Pcap文件
long Global_GetPcapReadLenth(BYTE *pszBuffer,long nMaxLenth);
WORD Global_BufferGetWord(BYTE *pszBuffer);
DWORD Global_BufferGetDWORD(BYTE *pszBuffer);
__int64 Global_BufferGetINT64(BYTE *pszBuffer);

extern long g_nXSmartCapDebugMode;
extern long g_n_write_SyncDelt_Rcd_file_Mode;
extern CString g_strSttRcdFilePath;
