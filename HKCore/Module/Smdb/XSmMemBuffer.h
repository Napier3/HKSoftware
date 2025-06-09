#pragma once

#include "../MemBuffer/XMemBufferBse.h"

//��û�б�����
#define EBS_NOPARSED      0x00000000
//ȫ���������
#define EBS_BEPARSED      0x00000001 
//���ֱ�����
#define EBS_SOMEPARSED    0x00000002  
//��������
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

	__int64 m_n64Pos;         //����ԭʼ\��������λ��\��������
	DWORD m_dwState;
	__int64 m_n64TimeSnamp;
	int m_nFiberAndPkgType;//zhouhj 2023.11.14 ��ǹ�ںż���������,ʵ�ʵײ㷵�ر��ĵ�2�ֽ����ݳ�������(��ҪFT3ʹ�ù�ڱ��)
//�����ڱ���̽��ʱ,��ǹ��

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

	//�ڴ��ͷ�
	//virtual void FreeBuffer(BOOL bOnlyDeleteBuffer=FALSE);
	virtual long GetWriteLength()	{		return m_nBufferLength;	}
	virtual BYTE* GetBufferHead()	{	return NULL;	}
	virtual long GetBufferHeadLength()	{	return 0;	}

public:
	//virtual void GetCapDbIndex(EPCAPDBBUFFERINDEX &oIndex);

};


