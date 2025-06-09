#pragma once


#include "ProtocolGlobalDef.h"

#ifndef _PSX_IDE_QT_
#include "../../../../Module/WinPcap/Include/pcap.h"
#endif

#include "../CapGlobalDef.h"

#include "../../../../Module/SmDb/XSmMemBuffer.h"
// #define FrameMemBuffer_use_pkthdr
#define FrameMemBuffer_use_FrameID

class CFrameMemBuffer : public CXSmMemBuffer
{
public:
	CFrameMemBuffer();
	virtual ~CFrameMemBuffer();

	__int64 m_n64FrameID;  //Frame ID
	__int64 m_n64DataPos;
	EPCAPBUFFERITEM m_oCapBufferItem;  //抓包的报文头
	DWORD  m_dwReserved;    //保留用 zhouhj 2023.8.19

public:
	virtual long GetWriteLength()
	{
#ifndef _PSX_IDE_QT_
		return sizeof(struct pcap_pkthdr) + m_nBufferLength;//m_nDataLength;
#else
		return m_nBufferLength;
#endif

	}

public:
	virtual void GetCapDbIndex(EPCAPDBBUFFERINDEX &oIndex);
	virtual BYTE* GetBufferHead()	{	return (BYTE*)(&m_oCapBufferItem);	}
	virtual long GetBufferHeadLength()	{	return sizeof(EPCAPBUFFERITEM);	}
	long GetPkgChNum();//获取当前帧报文通道数量
	long GetAsduNum();//获取报文中ASDU数量
	long GetSmpCount();//获取当前报文中的采样计数器值

};


