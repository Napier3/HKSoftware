#pragma once
#include "CmmChannel.h"
#include "../DeviceModel/CmmTcpServerConfig.h"
#include "CmmNetServer.h"
#include "CmmTcpServerClientChannel.h"

class CCmmTcpServerChannel :	public CCmmChannel
{
public:
	CCmmTcpServerChannel(void);
	virtual ~CCmmTcpServerChannel(void);

	CCmmTcpServerConfig *m_pConfig;
	CCmmNetServer  *m_pNetServer;

	BOOL m_bPostConnectFinishMsgAfterAccept;
	char m_pszPpLogProtocol[10240]; 

public:
	virtual UINT GetClassID(){return CMMCLASSID_TCP_SERVER_CHANNEL;};

public:
	virtual BOOL Create(CExBaseObject *pConfig);
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect();
	virtual BOOL DisConnect();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsCmmChannelExit();
	virtual BOOL TerminateChannel();

	void OnConnectSucc();
//	BOOL IsClientTrue();
	BOOL AddClient(CCmmTcpServerClientChannel *pChannel);
	BOOL RemoveClient(CCmmTcpServerClientChannel *pChannel);

private:
	void SendToAll(CExBaseObject *pPkgSend);
	void SendTo(CExBaseObject *pPkgSend);

	CCmmTcpServerClientChannels m_oTcpServerClientChannels;
	CExBaseList m_listAllRemoveChannels;
};
