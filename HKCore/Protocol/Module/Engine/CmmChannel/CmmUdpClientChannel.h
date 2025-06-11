#pragma once
#include "CmmChannel.h"
#include "../DeviceModel/CmmUdpClientConfig.h"
#include "../../../../Module/Socket/WinUdpScoket.h"


class CCmmUdpClientChannel :	public CCmmChannel, public CWinUdpSocket
{
public:
	CCmmUdpClientChannel(void);
	virtual ~CCmmUdpClientChannel(void);

	CCmmUdpClientConfig *m_pConfig;
	BOOL m_bNeedSend;
	char m_pszPpLogProtocol[10240]; 

public:
	virtual UINT GetClassID(){return CMMCLASSID_UDP_CLIENT_CHANNEL;};
	virtual void CreateThead();

public:

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
	virtual void OnChannelReceive(CCmmRcvSndTime *pCmmTime);
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsCmmChannelExit();
	virtual BOOL TerminateChannel();

public:
	bool IsExitThread()	{	return m_bExitThread;	}

private:
	typedef CTLinkList<CYCLEMEMBUFFERPOS> CCycleMemBufferPosMngr;
	//CCycleMemBufferPosMngr m_oCycleMemBufferPosMngr;
	//CWinThread *m_pThread;  //2024012016   lijunqing

	BOOL m_bExitThread;

	void AddCycleMemBufferPos(CYCLEMEMBUFFERPOS &oBufPos);

};


//UDP¿Í»§¶Ëº¯Êý
#ifdef _PSX_QT_LINUX_
void* cmm_UdpClientThread(LPVOID pParam);
#else
UINT cmm_UdpClientThread(LPVOID pParam);
#endif
