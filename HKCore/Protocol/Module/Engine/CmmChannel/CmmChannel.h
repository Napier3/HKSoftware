#pragma once

#include "CmmGlobalDefine.h"
#include "../../../../Module/CriticalSection/SynCriticalSection.h"
#include "../XPkgFullRcvJdgTool.h"
#include "../../../../Module/MemBuffer/MemBufferList.h"

#include "../ProtoPkgProcessInterface.h"

#include "../XPpPkgLogTool.h"

//2019-1-7:COM5003表计，谐波报文最大超过10K，所以将缓冲区大小放大到100K
#define CMM_RECEIVEBUFFER_LENGTH  102400   //接受缓冲区的大小，最大100K

#define CONNECT_STATE_NORMAL  0
#define CONNECT_STATE_SUCCESSFUL  1
#define CONNECT_STATE_FAILED 2

class CCmmReceiveInterface
{
public:
	virtual void OnReceive() = 0;
	virtual void OnException(long nException) = 0;

};

class CCmmRcvSndTime
{
public:
	CCmmRcvSndTime()
	{
		memset(&m_tm, 0, sizeof(SYSTEMTIME));
		m_bHasTimeInit = FALSE;
		m_dwTickCount = 0;
		memset(&m_oCycleBufferPos, 0, sizeof(CYCLEMEMBUFFERPOS));
	};
	virtual ~CCmmRcvSndTime(){}

	SYSTEMTIME m_tm;
	DWORD m_dwTickCount;
	CYCLEMEMBUFFERPOS m_oCycleBufferPos;

	void InitTime()
	{
		if (m_bHasTimeInit)
		{
			return;
		}

		::GetLocalTime(&m_tm);
		m_dwTickCount = ::GetTickCount();
		m_bHasTimeInit = TRUE;
	}

	void InitTime(SYSTEMTIME &tm)
	{
		if (m_bHasTimeInit)
		{
			return;
		}

		m_tm = tm;
		m_dwTickCount = ::GetTickCount();
		m_bHasTimeInit = TRUE;
	}

	BOOL IsInBufferPos(long nPos)
	{
		if (m_oCycleBufferPos.nBuf1BeginPos <= nPos && nPos < m_oCycleBufferPos.nBuf1EndPos )
		{
			return TRUE;
		}

		if (m_oCycleBufferPos.nBuf2BeginPos >= 0 && m_oCycleBufferPos.nBuf2EndPos >= 0)
		{
			if (m_oCycleBufferPos.nBuf2BeginPos <= nPos && nPos < m_oCycleBufferPos.nBuf2EndPos)
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	void Log();

	CCmmRcvSndTime* Clone()
	{
		CCmmRcvSndTime *pNew = new CCmmRcvSndTime();
		pNew->m_tm = m_tm;
		pNew->m_dwTickCount = m_dwTickCount;
		pNew->m_oCycleBufferPos = m_oCycleBufferPos;
		pNew->m_bHasTimeInit = m_bHasTimeInit;

		return pNew;
	}

private:
	BOOL m_bHasTimeInit;
};

class CCmmRcvSndTimeMngr : public CTLinkList<CCmmRcvSndTime>
{
public:
	CCmmRcvSndTimeMngr(){}
	virtual ~CCmmRcvSndTimeMngr(){}

	CCmmRcvSndTime* FindTimeByPos(long nPos);

	void DeletePrev(CCmmRcvSndTime *pTime);
};

/*
通讯通道对象
为保证通讯中不频繁发送数据，将发送的数据存放于一个链表中，定时发送
子对象为CPpPackageSend
*/

//#define _use_CMemBufferList

class CCmmChannel : public CExBaseList
{
public:
	CCmmChannel(void);
	virtual ~CCmmChannel(void);

	static CAutoCriticSection g_oCmmLogAutoCriticSection;

	DWORD m_dwConnectState;
	BYTE m_byteReceiveBuffer[CMM_RECEIVEBUFFER_LENGTH];
	long m_nReceiveLen;

	//缓冲区
	long m_nParserBeginPos;                   //缓冲区解析开始的位置
	long m_nSendSpyBeginPos;						//缓冲区监视开始的位置
	long m_nReceiveSpyBeginPos;						//缓冲区监视开始的位置

#ifdef _use_CMemBufferList
	CMemBufferList *m_pCycleRcvBuffer;
#else
	CCycleMemBuffer *m_pCycleRcvBuffer;
#endif

	CXPkgFullRcvJdgInterface *m_pXPkgFullRcvJdgInterface;
	CProtoPkgProcessInterface *m_pProtoPkgPrcss;  //2023-01-27  lijunqing

protected:
	BOOL m_bAttachReceiveBuffer;
	CCycleMemBuffer *m_pSendBuffer;
	BOOL m_bAttachSendBuffer;
	BOOL m_bResetRcvBufPos;
	
	CCmmReceiveInterface *m_pCmmRcvInterface;

	void FreeBuffer();
	void FreeReceiveBuffer();
	void FreeSendBuffer();

public:
	long GetBufferPos(long nBeginPos, long nLen, CYCLEMEMBUFFERPOS &oBufPos);
#ifndef _use_CMemBufferList
	void AttacthReceiveBuffer(CCycleMemBuffer *pBuffer);
#endif
	void AttacthSendBuffer(CCycleMemBuffer *pBuffer);

	void SetReceiveBufferLength(long nLen);
	void SetSendBufferLength(long nLen);

	void SetCmmReceiveInterface(CCmmReceiveInterface *pInterface)
	{
		m_pCmmRcvInterface = pInterface;
	}
	long GetSendIndex(){return m_nSendIndex;}
	virtual void OnChannelReceive(CCmmRcvSndTime *pCmmTime);
	void OnCmmChannelClose(CCmmChannel *pChannel);

#ifdef _use_CMemBufferList
	virtual void OnChannelReceive(CMemBufferList *pReceiveBuffer, CCmmRcvSndTime *pCmmTime, PCYCLEMEMBUFFERPOS pBufPos);
#else
	virtual void OnChannelReceive(CCycleMemBuffer *pReceiveBuffer, CCmmRcvSndTime *pCmmTime, PCYCLEMEMBUFFERPOS pBufPos);
#endif

	void OnException(long nException)
	{
		ASSERT (m_pCmmRcvInterface != NULL);

		if (m_pCmmRcvInterface != NULL)
		{
			m_pCmmRcvInterface->OnException(nException);
		}
	}

	void ResetSendSpyBeginPos();
	void ResetReceiveSpyBeginPos();
	void GetReceiveBufferPos(CYCLEMEMBUFFERPOS &oCycleBufPos);
	void GetSendBufferPos(CYCLEMEMBUFFERPOS &oCycleBufPos);
	void AppendRcvBuffer(BYTE *pReceiveBuffer, long nLen, CCmmRcvSndTime *pCmmTime);

public:
	virtual BOOL Create(CExBaseObject *pConfig) = 0;
	virtual BOOL Connect() = 0;
	virtual BOOL DisConnect() = 0;
	virtual BOOL TerminateChannel() = 0;
	virtual void Send(CExBaseObject *pPkgSend);
	void OffsetParserBeginPos(long nOffset);
	void ResetReceiveBeginPos();
	void ResetOffsetDataFillBeginPosition();
	BOOL DataIsEnoughForParse(long nMinLen);
	virtual BOOL IsConnectSuccessful() {    return (m_dwConnectState == CONNECT_STATE_SUCCESSFUL);    };
	void ResetState()		{	m_dwConnectState = CONNECT_STATE_NORMAL;	}
	BOOL HasConnected()	{	return (m_dwConnectState != CONNECT_STATE_NORMAL);		};
	virtual BOOL IsCmmChannelExit();

	//连接完成
	void OnConnectFinished();

	//连接失败
	void OnConnectFailed();

public: //protected:  //lijunqing 2024-12-16
	CAutoCriticSection m_oSendListCriticSection;   //发送链表互斥对象
	long m_nSendIndex;
	char m_pReceiveBuffer[CMM_RECEIVEBUFFER_LENGTH];

	CExBaseObject* GetPackageSend();
	void RemoveHead();
	CBaseObject* GetDeviceCmmChannel();
};

void CMM_OnChannelConnectSucc(CExBaseList *pCmmConfig, CWinThread *pThread);
void CMM_SetAllSendPkgState(CExBaseList *pList, BOOL bSend=TRUE);


