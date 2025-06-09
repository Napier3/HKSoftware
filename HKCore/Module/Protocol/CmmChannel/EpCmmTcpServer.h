#pragma once

#include "EpCmmNetServer.h"
#include "..\..\Socket\ThreadSocket.h"

// CEpCmmTcpServer ����Ŀ��
//TCP�������˹������
//���ܿͻ��˵����ӣ�����CEpCmmTcpClientChannel
class CEpCmmTcpServer : public CThreadSocket, public CEpCmmNetServer
{
public:
	CEpCmmTcpServer();
	virtual ~CEpCmmTcpServer();

public:
	virtual UINT GetClassID(){return EPCMMCLASSID_TCPSERVER;};

public:
	virtual BOOL CreateServer(const CString &strIP, UINT nPort, const CString &strBoardcastIP, long nMulticastPort);
	virtual BOOL CreateServer();
	virtual BOOL CloseServer(CExBaseObject *pChannel);
	virtual BOOL IsServerClosed();

	virtual void OnAccept();

private:
	BOOL AddToServer(CExBaseObject *pTcpServerClientChannel);
};


