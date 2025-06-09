#pragma once
#include "cmmchannel.h"
#include "..\DeviceModel\CmmTcpServerConfig.h"
#include "CmmNetServer.h"
#include "..\..\..\..\Module\Socket\ThreadSocket.h"

class CCmmTcpServerClientChannel : public CCmmChannel, public CThreadSocket
{
public:
	CCmmTcpServerClientChannel(void);
	virtual ~CCmmTcpServerClientChannel(void);
	char m_pszPpLogProtocol[10240]; 

public:
	virtual UINT GetClassID(){return CMMCLASSID_TCP_SERVER_CLIENT_CHANNEL;};

public:
	virtual BOOL Create(CExBaseObject *pConfig)	{	return FALSE;	};
	virtual void Send(CExBaseObject *pPkgSend);
	virtual BOOL Connect()	{	return FALSE;	}
	virtual BOOL DisConnect()	{	return FALSE;	}
	virtual long OnReceive();
	virtual void OnClose();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsCmmChannelExit()	{	return FALSE;	};
	virtual BOOL TerminateChannel();
	//virtual BOOL IsConnectSuccessful();
	//virtual BOOL IsCmmChannelExit()	{	return FALSE;	};

	BOOL IsSame(CCmmTcpServerClientChannel *p)
	{
		return (m_nIPAddr == p->m_nIPAddr);
	}
};

typedef CTLinkList<CCmmTcpServerClientChannel> CCmmTcpServerClientChannels;
