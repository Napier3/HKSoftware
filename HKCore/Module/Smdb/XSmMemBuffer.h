#pragma once

#include "../MemBuffer/XMemBufferBse.h"

//还没有被解析
#define EBS_NOPARSED      0x00000000
//全部解析完毕
#define EBS_BEPARSED      0x00000001 
//部分被解析
#define EBS_SOMEPARSED    0x00000002  
//解析错误
#define EBS_PARSEDERROR   0x00000004 

#define EBS_HASWRITE      0x00010000

#define WM_CAP_WRITE_SMDB   (WM_USER+854)
#define WM_SHOW_CAP_INFOR   (WM_USER+101)


#define EP_TIME_EX_TYPE_DOUBLE 0
#define EP_TIME_EX_TYPE_N64 1
#define EP_TIME_EX_TYPE_STTUTC 2

typedef struct _stt_time_64_
{
	unsigned int nType; //0 = double; 1= n64; 2=stt utc(s+ns)
	union
	{
		double dTime;
                __int64 n64Time;
#ifdef _QT_IN_LINUX_
                struct
#else
                struct stt_utc_tm
 #endif

		{
			unsigned int utc_ns;
			unsigned int utc_s;
                }stt_utc;
	};
}STT_TIME_64;


class CXSmMemBuffer : public CXMemBufferBse//CCycleMemBuffer
{
public:
	CXSmMemBuffer();
	virtual ~CXSmMemBuffer();

	__int64 m_n64Pos;         //报文原始\解析数据位置\缓存数据
	DWORD m_dwState;
	__int64 m_n64TimeSnamp;
	int m_nFiberAndPkgType;//zhouhj 2023.11.14 标记光口号及报文类型,实际底层返回报文的2字节数据长度内容(主要FT3使用光口标记)
//仅用于报文探测时,标记光口

public:
	void SetState(DWORD dwState)	{		m_dwState |= dwState;		}
	BOOL Ebs_NoParsed()			{	return (EBS_NOPARSED   == m_dwState);		}
	BOOL Ebs_SomeParsed()		{	return (EBS_SOMEPARSED == (m_dwState & EBS_SOMEPARSED) );		}
	BOOL Ebs_BeParsed()			{	return (EBS_BEPARSED   == (m_dwState & EBS_BEPARSED) );		}
	BOOL Ebs_IsParsedError()		{	return (EBS_PARSEDERROR   == (m_dwState & EBS_PARSEDERROR) );		}
	BOOL Ebs_BeWrited()			{	return (EBS_HASWRITE   == (m_dwState & EBS_HASWRITE) );		}

	void Ebs_SetParsed()				{	SetState (EBS_BEPARSED);		}
	void Ebs_SetWrited()				{	SetState (EBS_HASWRITE);		}
	BOOL CanFreeBuffer()			{		return ( Ebs_BeParsed() && Ebs_BeWrited() );	}

	//内存释放
	//virtual void FreeBuffer(BOOL bOnlyDeleteBuffer=FALSE);
	virtual long GetWriteLength()	{		return m_nBufferLength;	}
	virtual BYTE* GetBufferHead()	{	return NULL;	}
	virtual long GetBufferHeadLength()	{	return 0;	}

public:
	//virtual void GetCapDbIndex(EPCAPDBBUFFERINDEX &oIndex);

};


