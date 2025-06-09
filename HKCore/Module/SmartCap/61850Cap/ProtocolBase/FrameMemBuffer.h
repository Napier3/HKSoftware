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
	EPCAPBUFFERITEM m_oCapBufferItem;  //ץ���ı���ͷ
	DWORD  m_dwReserved;    //������ zhouhj 2023.8.19

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
	long GetPkgChNum();//��ȡ��ǰ֡����ͨ������
	long GetAsduNum();//��ȡ������ASDU����
	long GetSmpCount();//��ȡ��ǰ�����еĲ���������ֵ

};


