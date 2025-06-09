#pragma once


#include "ProtocolGlobalDef.h"
#include "..\..\..\..\Module\WinPcap\Include\pcap.h"
#include "..\CapGlobalDef.h"

// #define FrameMemBuffer_use_pkthdr
#define FrameMemBuffer_use_FrameID

class CFrameMemBuffer : public CXMemBufferBse//CCycleMemBuffer
{
public:
	CFrameMemBuffer();
	virtual ~CFrameMemBuffer();

#ifdef FrameMemBuffer_use_FrameID
	__int64 m_n64FrameID;  //Frame ID
#endif

	__int64 m_n64FrmPos;   //报文原始\解析数据位置
	__int64 m_n64DataPos;
	DWORD m_dwState;

#ifdef FrameMemBuffer_use_pkthdr
	struct pcap_pkthdr m_oPcapHeader;
#endif

	EPCAPBUFFERITEM m_oCapBufferItem;

public:
	BOOL Ebs_NoParsed()		{	return (EBS_NOPARSED   == m_dwState);		}
	BOOL Ebs_SomeParsed()	{	return (EBS_SOMEPARSED == (m_dwState & EBS_SOMEPARSED) );		}
	BOOL Ebs_BeParsed()		{	return (EBS_BEPARSED   == (m_dwState & EBS_BEPARSED) );		}
	BOOL Ebs_IsParsedError()		{	return (EBS_PARSEDERROR   == (m_dwState & EBS_PARSEDERROR) );		}
	BOOL Ebs_BeWrited()		{	return (EBS_HASWRITE   == (m_dwState & EBS_HASWRITE) );		}

	void SetState(DWORD dwState)
	{
		m_dwState |= dwState;
	}

	BOOL CanFreeBuffer()
	{
		return ( Ebs_BeParsed() && Ebs_BeWrited() );
	}

	//内存释放
	virtual void FreeBuffer(BOOL bOnlyDeleteBuffer=FALSE);
	long GetWriteLength()
	{
		return sizeof(struct pcap_pkthdr) + m_nBufferLength;//m_nDataLength;
	}

public:
	virtual void GetCapDbIndex(EPCAPDBBUFFERINDEX &oIndex);

};


