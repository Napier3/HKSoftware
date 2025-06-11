#pragma once
#include "CmmChannel.h"
#include "../DeviceModel/CmmTcpServerConfig.h"
#include "CmmNetServer.h"
#include "../../../../Module/Socket/WinTcpSocketClient.h"

class CCmmTcpServerClientChannel : public CCmmChannel, public CWinTcpSocketClient//public CThreadSocket
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
	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
	virtual void OnClose();
	virtual BOOL IsConnectSuccessful();
	virtual BOOL IsCmmChannelExit()	{	return FALSE;	};
	virtual BOOL TerminateChannel();
	//virtual BOOL IsConnectSuccessful();
	//virtual BOOL IsCmmChannelExit()	{	return FALSE;	};

	BOOL IsSame(CCmmTcpServerClientChannel *p)
	{
		return (m_hSocket == p->m_hSocket);
	}
};

typedef CTLinkList<CCmmTcpServerClientChannel> CCmmTcpServerClientChannels;
