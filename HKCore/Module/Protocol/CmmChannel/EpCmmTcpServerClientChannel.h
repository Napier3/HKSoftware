#pragma once
#include "epcmmchannel.h"
#include "config\EpCmmTcpServerConfig.h"
#include "EpCmmNetServer.h"
#include "..\..\Socket\ThreadSocket.h"

class CEpCmmTcpServerClientChannel : public CEpCmmChannel, public CThreadSocket
{
public:
	CEpCmmTcpServerClientChannel(void);
	~CEpCmmTcpServerClientChannel(void);

public:
	virtual UINT GetClassID(){return EPCMMCLASSID_TCP_SERVER_CLIENT_CHANNEL;};

public:
	virtual BOOL Create(CExBaseObject *pConfig)	{	return FALSE;	};
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect()	{	return FALSE;	}
	virtual BOOL DisConnect()	{	return FALSE;	}
	virtual long OnReceive();
	virtual void OnClose();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsEpCmmChannelExit()	{	return FALSE;	};

	BOOL IsSame(CEpCmmTcpServerClientChannel *p)
	{
		return (m_nIPAddr == p->m_nIPAddr);
	}
};

typedef CTLinkList<CEpCmmTcpServerClientChannel> CEpCmmTcpServerClientChannels;
