#pragma once


#include "..\MemBuffer\CycleMemBuffer.h"
#include "ProtocolGlobalBaseDefine.h"
//////////////////////////////////////////////////////////////////////////
//缓冲区状态定义
//ECBS = ep cap buffer state

//还没有被解析
#define EBS_NOPARSED      0x00000000
 //全部解析完毕
#define EBS_BEPARSED      0x00000001 
//部分被解析
#define EBS_SOMEPARSED    0x00000002  
//解析错误
#define EBS_PARSEDERROR   0x00000004 

#define EBS_HASWRITE      0x00010000


class CEpCycleMemBuffer : public CCycleMemBuffer
{
public:
	CEpCycleMemBuffer();
	virtual ~CEpCycleMemBuffer();

	long  m_nCurrPos;
	DWORD m_dwState;

public:
	void OffsetCurrPos(long nLen);
// 	void SetCurrPos(long nPos);
// 	void SetCurrPos(PEPBUFFERPOS pBufferPos);
	void CombineBuffer(CEpCycleMemBuffer *pPrev);
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

public:
	virtual long GetLengthNeedParse()	{	return m_nDataLength - m_nCurrPos;	}
	virtual long GetUnparseBufferLength()	{	return m_nDataLength - m_nCurrPos;	}
	virtual void SetCurrPos(long nPos);
	virtual void SetCurrPos(PEPBUFFERPOS pBufferPos);
	virtual void GetBufferPos(PEPBUFFERPOS pBufferPos);
};


