#pragma once
#include "epcmmchannel.h"
#include "config\EpCmmUdpServerConfig.h"
#include "EpCmmNetServer.h"

class CEpCmmUdpServerChannel :	public CEpCmmChannel
{
public:
	CEpCmmUdpServerChannel(void);
	~CEpCmmUdpServerChannel(void);

	CEpCmmUdpServerConfig *m_pConfig;
	CEpCmmNetServer *m_pNetServer;
	struct sockaddr_in m_oSocketAddrIn;

public:
	virtual UINT GetClassID(){return EPCMMCLASSID_UDP_SERVER_CHANNEL;};


	virtual void OnChannelReceive(CEpCmmRcvSndTime *pEpCmmTime);

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
	virtual BOOL ConnectOther();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsEpCmmChannelExit();

	void OnServerAccept(struct sockaddr_in *pSckAddr);
};
