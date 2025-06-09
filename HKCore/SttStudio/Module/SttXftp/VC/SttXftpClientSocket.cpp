// SttRemoteServerClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SttXftpClientSocket.h"
#include "../../../../Module/Socket/SocketGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CSttRemoteServerClientSocket

CSttXftpClientSocket::CSttXftpClientSocket()
{

}

CSttXftpClientSocket::~CSttXftpClientSocket()
{

}

BOOL CSttXftpClientSocket::ConnectServer(const CString &strIPServer,long nPort)
{//本地或远程测试端，连接成功后设置SttLocalTestEngine的RefSocket
	m_strIPRemote = strIPServer;
	m_nPortRemote = nPort;

//	SetReceiveBuffLen( STT_FILECMD_MAX_LEN );//yyj test

#ifndef _PSX_IDE_QT_
	InitSocket();
#endif

	Create(SOCK_STREAM);

	BOOL bRet = Connect(strIPServer.GetString(), nPort);

	if (bRet)
	{
		//InitSocketClient(20);
	}

	return bRet;
}

void CSttXftpClientSocket::OnReceive(int nErrorCode)
{
	OnReceiveBuffer(nErrorCode);
}

void CSttXftpClientSocket::OnClose(int nErrorCode)
{
	OnSocketClose(nErrorCode);
}

void CSttXftpClientSocket::CloseSocket()
{
	Close();
}

long CSttXftpClientSocket::ReceiveBuffer(BYTE *pBuf, long nLen)
{
	return 0;
}

long CSttXftpClientSocket::SendBuffer(BYTE *pBuf, long nLen)
{
	return Send((char*)pBuf, nLen);
}

long CSttXftpClientSocket::OnReceive(BYTE *pRcvBuf, int iLen)
{
	OnReceiveBuffer(pRcvBuf, iLen);
	return 0;
}

