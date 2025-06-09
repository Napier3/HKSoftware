#pragma once

#include "CmmNetServer.h"
#include "..\..\..\..\Module\Socket\ThreadSocket.h"
#include "CmmTcpServerClientChannel.h"

// CCmmTcpServer ����Ŀ��
//TCP�������˹������
//���ܿͻ��˵����ӣ�����CCmmTcpClientChannel
class CCmmTcpServer : public CThreadSocket
{
public:
	CCmmTcpServer();
	virtual ~CCmmTcpServer();

	CString m_strIP;
	unsigned short m_nPort;

public:
	virtual UINT GetClassID(){return CMMCLASSID_TCPSERVER;};

public:
	virtual BOOL CreateServer(const CString &strIP, UINT nPort, const CString &strBoardcastIP, long nMulticastPort);
	virtual BOOL CloseServer(CExBaseObject *pChannel);
	virtual BOOL IsServerClosed();

	virtual void OnAccept();
	virtual long OnReceive(SOCKET s);

private:
	BOOL AddToServer(CExBaseObject *pTcpServerClientChannel);
};


