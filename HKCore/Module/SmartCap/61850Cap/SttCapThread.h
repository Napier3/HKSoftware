#pragma once


#include "EthernetCapGlobalDef.h"
#include "CapThreadBase.h"
#include "ProtocolBase/Stt/SttFrameMemBufferMngr.h"

#ifndef _PSX_IDE_QT_
#include "../../Socket/WinTcpSocketClient.h"
#endif

#include "CapDevice/CapDeviceMngr.h"
#include "ProtocolBase/Stt/SttRcdMemBufferMngr.h"

// extern long g_nEthernetCapError;

class CSttCapThread : public CCapThreadBase
{
public:
	CSttCapThread(void);
	virtual ~CSttCapThread(void);

	//2022-3-6 lijunqing �˴����ýӿڵķ�ʽ�����������ֻ�¼����ͨ�û�����
	//���磺AT02D�ǽ�AT02D�ı���ת��Ϊ���ֱ��ģ�330�ѻ�Ϊ�����ڴ�ģʽ����λ�����Ϊ¼��ͨ����������ֱ���
	//CSttRcdMemBufferMngr *m_pSttRcdMemBufferMngr;
	CXCapPkgBufferMngrInterface *m_pSttRcdMemBufferMngr;

	static CSttCapThread* CreateNewSttCapThread(CXCapPkgBufferMngrInterface *p)
	{
		CSttCapThread *pThread = new CSttCapThread();
		pThread->m_pSttRcdMemBufferMngr = p;
		return pThread;
	}

	void SetRecordTestCalThread(CWinThread *pThread)	{	m_pRecordTestCalThread = pThread;	}
	void SetCapDeviceAll(CCapDeviceMngr *p)	{	m_pAllDeviceRef = p;	}
public:
	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
	virtual void OnSocketIdle(long nMs);
	virtual void OnClose(int nErrorCode);

protected:
	long m_nSttCapError;
	ETHER_CAP_CONFIG m_oEtherCapConfig;
	CWinThread *m_pRecordTestCalThread;

public:
	virtual DWORD CreateCaptureThread();
	virtual void ExitCapture();
	void RecordTestCalValues();

public:
	CCapDeviceMngr *m_pAllDeviceRef;
	void UpdateDeviceLinkState();

public:
	void SetCapConfig(PETHER_CAP_CONFIG pConfig, DWORD dwMask=CAPCFGMASK_ALL);
	PETHER_CAP_CONFIG GetCapConfig()				{	return &m_oEtherCapConfig;		}
	void SetRestartWinCap()	{	m_nSttCapError = TRUE;	}
	BOOL IsRecordTestCalThreadCreated()	{	return m_pRecordTestCalThread != NULL;	}

public://protected
	static UINT CaptureThread(LPVOID pParam);	
};

static UINT ParseThread(LPVOID pParam);	
