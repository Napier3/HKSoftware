#pragma once
#include "epcmmchannel.h"
#include "config\EpCmmUdpConfig.h"


class CEpCmmUdpClientChannel :	public CEpCmmChannel
{
public:
	CEpCmmUdpClientChannel(void);
	~CEpCmmUdpClientChannel(void);

	CEpCmmUdpConfig *m_pConfig;
	BOOL m_bNeedSend;

public:
	virtual UINT GetClassID(){return EPCMMCLASSID_UDP_CLIENT_CHANNEL;};

public:
	//UDP¿Í»§¶Ëº¯Êý
	static UINT UdpClientThread(LPVOID pParam);

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsEpCmmChannelExit();

private:
	typedef CTLinkList<EPBUFFERPOS> CCycleMemBufferPosMngr;
	CWinThread *m_pThread;
	BOOL m_bExitThread;

	void AddCycleMemBufferPos(EPBUFFERPOS &oBufPos);

};
