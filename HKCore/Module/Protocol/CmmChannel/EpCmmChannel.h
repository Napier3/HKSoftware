#pragma once

#include "..\EpGlobalDefine.h"
#include "..\ProtocolBase\EpFrameBase.h"
#include "..\..\CriticalSection\SynCriticalSection.h"
#include "..\..\ProtocolBase\EpCycleMemBufferMngr.h"

#define CMM_RECEIVEBUFFER_LENGTH  10240   //���ܻ������Ĵ�С�����10K

#define CONNECT_STATE_NORMAL  0
#define CONNECT_STATE_SUCCESSFUL  1
#define CONNECT_STATE_FAILED 2

class CEpCmmReceiveInterface
{
public:
	virtual void OnReceive() = 0;
	virtual void OnException(long nException) = 0;

};

class CEpCmmRcvSndTime
{
public:
	CEpCmmRcvSndTime()
	{
		memset(&m_tm, 0, sizeof(SYSTEMTIME));
		m_bHasTimeInit = FALSE;
		m_dwTickCount = 0;
		m_pBuffer = NULL;
	};
	~CEpCmmRcvSndTime(){}

	SYSTEMTIME m_tm;
	DWORD m_dwTickCount;
	CEpCycleMemBuffer *m_pBuffer;

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
		if (0 <= nPos && nPos < m_pBuffer->GetDataLength() )
		{
			return TRUE;
		}

		return FALSE;
	}

	void Log();

private:
	BOOL m_bHasTimeInit;
};

class CEpCmmRcvSndTimeMngr : public CTLinkList<CEpCmmRcvSndTime>
{
public:
	CEpCmmRcvSndTimeMngr(){}
	~CEpCmmRcvSndTimeMngr(){}

	CEpCmmRcvSndTime* FindTimeByPos(long nPos);

	void DeletePrev(CEpCmmRcvSndTime *pTime);
};

/*
ͨѶͨ������
Ϊ��֤ͨѶ�в�Ƶ���������ݣ������͵����ݴ����һ�������У���ʱ����
�Ӷ���ΪCEpFrameBase
*/
class CEpCmmChannel : public CExBaseList
{
public:
	CEpCmmChannel(void);
	~CEpCmmChannel(void);

	DWORD m_dwConnectState;
	BYTE m_byteReceiveBuffer[CMM_RECEIVEBUFFER_LENGTH];
	long m_nReceiveLen;

	//������
	long m_nParserBeginPos;                   //������������ʼ��λ��
	long m_nSendSpyBeginPos;						//���������ӿ�ʼ��λ��
	long m_nReceiveSpyBeginPos;						//���������ӿ�ʼ��λ��
	CEpCycleMemBufferMngr m_oCycleRcvBuffer;

protected:
	BOOL m_bAttachReceiveBuffer;
	CCycleMemBuffer *m_pSendBuffer;
	BOOL m_bAttachSendBuffer;
	
	CEpCmmReceiveInterface *m_pEpCmmRcvInterface;

	void FreeBuffer();
	void FreeReceiveBuffer();
	void FreeSendBuffer();

public:
	void AttacthReceiveBuffer(CCycleMemBuffer *pBuffer);
	void AttacthSendBuffer(CCycleMemBuffer *pBuffer);

	//void SetReceiveBufferLength(long nLen);
	void SetSendBufferLength(long nLen);

	void SetEpCmmReceiveInterface(CEpCmmReceiveInterface *pInterface)
	{
		m_pEpCmmRcvInterface = pInterface;
	}
	long GetSendIndex(){return m_nSendIndex;}
	virtual void OnChannelReceive(CEpCmmRcvSndTime *pEpCmmTime);

	void OnException(long nException)
	{
		ASSERT (m_pEpCmmRcvInterface != NULL);

		if (m_pEpCmmRcvInterface != NULL)
		{
			m_pEpCmmRcvInterface->OnException(nException);
		}
	}

	void ResetSendSpyBeginPos();
	void ResetReceiveSpyBeginPos();
	void GetReceiveBufferPos(EPBUFFERPOS &oCycleBufPos);
	void AppendRcvBuffer(BYTE *pReceiveBuffer, long nLen, CEpCmmRcvSndTime *pEpCmmTime);
	BOOL HasBufferNeedParse()	{		return m_oCycleRcvBuffer.HasBufferNeedParse();		}
	void SetReceiveBufferLength(long nBufferLen)	{	m_oCycleRcvBuffer.SetMaxBufferLength(nBufferLen);	}
	CEpCmmChannel* FindCmmChannel(const CString &strChannelID)
	{
		if (m_strID == strChannelID)
		{
			return this;
		}
		else
		{
			return NULL;
		}
	}
	CEpCmmChannel* FindCmmChannel(UINT nClassID)
	{
		if (GetClassID() == nClassID)
		{
			return this;
		}
		else
		{
			return NULL;
		}
	}

public:
	virtual BOOL Create(CExBaseObject *pConfig) = 0;
	virtual BOOL Connect() = 0;
	virtual BOOL DisConnect() = 0;
	virtual void Send(CExBaseObject *pPkgSend);
	void OffsetParserBeginPos(EPBUFFERPOS &oCycleBufPos);
	void OffsetParserBeginPos(long nLen);
	BOOL DataIsEnoughForParse(long nMinLen);
	virtual BOOL IsConnectSuccessful() {    return (m_dwConnectState == CONNECT_STATE_SUCCESSFUL);    };
	void ResetState()		{	m_dwConnectState = CONNECT_STATE_NORMAL;	}
	BOOL HasConnected()	{	return (m_dwConnectState != CONNECT_STATE_NORMAL);		};
	virtual BOOL IsEpCmmChannelExit();

	//�������
	void OnConnectFinished();

protected:
	CAutoCriticSection m_oSendListCriticSection;   //�������������
	long m_nSendIndex;
	char m_pReceiveBuffer[CMM_RECEIVEBUFFER_LENGTH];

	CExBaseObject* GetFrameSend();
	void RemoveHead();
	CBaseObject* GetEpDeviceCmmChannel();
};

void CMM_OnChannelConnectSucc(CExBaseList *pEpCmmConfig, CWinThread *pThread);
void CMM_SetAllSendPkgState(CExBaseList *pList, BOOL bSend=TRUE);

