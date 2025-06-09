#pragma once
#include "epcmmchannel.h"
#include "config\EpCmmTcpClientConfig.h"
#include "..\..\Socket\ThreadSocket.h"

class CEpCmmTcpClientChannel :	public CEpCmmChannel, public CThreadSocket
{
public:
	CEpCmmTcpClientChannel(void);
	~CEpCmmTcpClientChannel(void);

	CEpCmmTcpClientConfig *m_pConfig;

public:
	virtual UINT GetClassID(){return EPCMMCLASSID_TCP_CLIENT_CHANNEL;};

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
	virtual long OnReceive();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsEpCmmChannelExit();
};
