// EpFrameRecord.h: interface for the CEpFrameRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPFRAMERECORD_H__)
#define _EPFRAMERECORD_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CapCycleMemBufferMngr.h"
#include "..\Protocol\ProtocolBase\EpFrameBase.h"

#define FRAME_RECORD_BUFFER_LEN   20
#define FRAME_RECORD_LIMIT   10000

//#define FRAMERECORD_USE_DWORD 

class CEpFrameRecord : public CExBaseObject
{
public:
	CEpFrameRecord();
	virtual ~CEpFrameRecord();
	
	DWORD m_nProtocol;  //101,104
	EPTIME64 m_tm; //cap的时间
	EP_ETHER_CAP_IP_GROUP m_ipGroup; //ip或者端口
	volatile __int64 m_n64CapID;   //cap id
//	EPDEVICEDATAHEAD m_oDataHead;  //数据头
	WORD m_nDeviceDataType;
	WORD m_nDataCount;

	CCycleMemBuffer m_oBuffer;
	//CCycleMemBuffer *m_pFrmBuffer;
// 	BYTE m_pFrmBuffer[FRAME_RECORD_BUFFER_LEN+2];
// 	long m_nFrmBuffer;

public:
	void SetBuffer(CCycleMemBuffer *pBuffer);
	void SetBuffer(BYTE *pBuffer, long nLength);
	CCycleMemBuffer* GetRecordBuffer()	{	return &m_oBuffer;	}
};

class CEpFrameRecordMngr : public CExBaseList
{
public:
	CEpFrameRecordMngr();
	virtual ~CEpFrameRecordMngr();

public:
	long GetCount()	{	return m_nCount;	}
	long GetLimit()	{	return m_nLimit;	}
	void SetLimit(long nLimit);
	CEpFrameRecord* AddRecord(long &nCurrIndex);
	CEpFrameRecord* GetRecord(long nIndex);
	
private:
#ifdef FRAMERECORD_USE_DWORD
	DWORD *m_pRecordMngr;
#endif

	long m_nLimit;
	long m_nCount;
	long m_nCurrIndex;

	void CreateRecord(long nBeginIndex);
};

#endif // !defined(_EPFRAMERECORD_H__)
