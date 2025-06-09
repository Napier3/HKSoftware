#pragma once
#include "epcmmchannel.h"
#include "config\EpCmmTcpServerConfig.h"
#include "EpCmmNetServer.h"
#include "EpCmmTcpServerClientChannel.h"
#include "..\..\Socket\ThreadSocket.h"

class CEpCmmTcpServerChannel :	public CEpCmmChannel//, public CThreadSocket
{
public:
	CEpCmmTcpServerChannel(void);
	~CEpCmmTcpServerChannel(void);

	CEpCmmTcpServerConfig *m_pConfig;
	CEpCmmNetServer  *m_pNetServer;

public:
	virtual UINT GetClassID(){return EPCMMCLASSID_TCP_SERVER_CHANNEL;};

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
// 	virtual long OnReceive();
//	virtual void OnClose();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsEpCmmChannelExit();

	void OnConnectSucc();
//	BOOL IsClientTrue();
	BOOL AddClient(CEpCmmTcpServerClientChannel *pChannel);

private:
	void SendToAll(CExBaseObject *pPkgSend);
	void SendTo(CExBaseObject *pPkgSend);

	CEpCmmTcpServerClientChannels m_oTcpServerClientChannels;
};
