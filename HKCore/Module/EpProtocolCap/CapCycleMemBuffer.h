#pragma once


#include "..\Protocol\EpGlobalBaseDefine.h"
#include "..\ProtocolBase\EpCycleMemBuffer.h"
#include "EpEthernetCapGlobalDef.h"

//#pragma pack(1)

typedef struct epCapDbBufferIndex
{
	volatile __int64 n64CapID;   //cap id
	EP_ETHER_CAP_IP_GROUP ipGroup; //ip或者端口
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

class CCapCycleMemBuffer : public CEpCycleMemBuffer
{
public:
	CCapCycleMemBuffer();
	virtual ~CCapCycleMemBuffer();

	DWORD m_nProtocol;
	EPTIME64 m_ts;
	EP_ETHER_CAP_IP_GROUP m_ipGroup;
	volatile __int64 m_n64CapID;           //CAP ID
	volatile __int64 m_n64IndexPos;        //索引位置
	volatile __int64 m_n64DataPos;        //数据位置

	volatile __int64 m_n64FrmDvPos;   //报文原始\解析数据位置
	DWORD   m_dwFrameLen;
	DWORD   m_dwDeviceDataLen;

	CEpDeviceDatas *m_pDeviceDatas;
	long m_nParseDataPos;
	long m_nParseDataLength;

	const u_char *pkt_data_ref;


private:
	DWORD m_dwRecord;
#define RECORD_NEEDRECORD   0X01
#define RECORD_NORECORD     0X02
#define RECORD_HASRECORD    0X03

public:
	void Set_RECORD_NEEDRECORD()	{	m_dwRecord = RECORD_NEEDRECORD;	}
	void Set_RECORD_NORECORD()		{	m_dwRecord = RECORD_NORECORD;	}
	void Set_RECORD_HASRECORD()		{	m_dwRecord = RECORD_HASRECORD;	}

	BOOL Is_RECORD_NEEDRECORD()		{	return (m_dwRecord == RECORD_NEEDRECORD);	}
	BOOL Is_RECORD_NORECORD()		{	return (m_dwRecord == RECORD_NORECORD);		}
	BOOL Is_RECORD_HASRECORD()		{	return (m_dwRecord == RECORD_HASRECORD);	}

public:
// 	void GetCapDbBuffer(EPCAPDBBUFFER &oCapBuffer);
	void GetCapDbIndex(EPCAPDBBUFFERINDEX &oIndex);
	virtual void SetCurrPos(PEPBUFFERPOS pBufferPos);
//	virtual void GetBufferPos(PEPBUFFERPOS pBufferPos);
	COLORREF GetColor()	{	return GetEpCapIpGroupColor(m_ipGroup);	}
	void InitParsePos(const u_char *pkt_data, long nParseDataLen, EP_ETHER_CAP_IP_GROUP ipGroup, UINT nCapType);

public:
	virtual long GetLengthNeedParse();//	{	return m_nDataLength - m_nCurrPos;	}
	virtual long GetUnparseBufferLength();//	{	return m_nDataLength - m_nCurrPos;	}
	virtual void GetBufferPos(PEPBUFFERPOS pBufferPos);
	virtual void SetCurrPos(long nPos);

};


