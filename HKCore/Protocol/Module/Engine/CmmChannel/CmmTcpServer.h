#pragma once

#include "CmmNetServer.h"
//#include "../../../../Module/Socket/ThreadSocket.h"
#include "CmmTcpServerClientChannel.h"
#include "../../../../Module/Socket/WinTcpSocket.h"
#include "../../../../Module/Socket/WinTcpSocketServer.h"

// CCmmTcpServer ����Ŀ��
//TCP�������˹������
//���ܿͻ��˵����ӣ�����CCmmTcpClientChannel
//lijunqing 2024012016 CThreadSocket >> CWinTcpSocket
class CCmmTcpServer : public CCmmNetServer, public CWinTcpSocketServer//public CThreadSocket,
{
public:
	CCmmTcpServer();
	virtual ~CCmmTcpServer();

public:
	virtual UINT GetClassID(){return CMMCLASSID_TCPSERVER;};

public:
	virtual BOOL CreateServer(const CString &strIP, UINT nPort, const CString &strBoardcastIP, long nMulticastPort);
	virtual BOOL CreateServer();
	virtual BOOL CloseServer(CExBaseObject *pChannel);
	virtual BOOL IsServerClosed();

	virtual CWinTcpSocketClient* CreateNewSocketClient();
	virtual void OnAccept(CWinTcpSocketClient *pSocket);

private:
	BOOL AddToServer(CExBaseObject *pTcpServerClientChannel);
};


