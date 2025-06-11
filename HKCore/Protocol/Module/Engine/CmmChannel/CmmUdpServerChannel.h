#pragma once
#include "CmmChannel.h"
#include "../DeviceModel/CmmUdpServerConfig.h"
#include "CmmNetServer.h"
#include "../../../../Module/Socket/WinUdpScoket.h"

class CCmmUdpServerChannel :	public CCmmChannel
{
public:
	CCmmUdpServerChannel(void);
	virtual ~CCmmUdpServerChannel(void);

	CCmmUdpServerConfig *m_pConfig;
	CCmmNetServer *m_pNetServer;
    struct sockaddr_in m_oSocketAddrIn;

public:
	virtual UINT GetClassID(){return CMMCLASSID_UDP_SERVER_CHANNEL;};


	virtual void OnChannelReceive(CCmmRcvSndTime *pCmmTime);
	//virtual void OnChannelReceive(CCycleMemBuffer *pReceiveBuffer, CCmmRcvSndTime *pCmmTime, PCYCLEMEMBUFFERPOS pBufPos);

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
	virtual BOOL ConnectOther();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsCmmChannelExit();
	virtual BOOL TerminateChannel();

	void OnServerAccept(struct sockaddr_in *pSckAddr);
};
