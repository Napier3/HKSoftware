// SttRemoteServerClientSocket.cpp : 实现文件
//

#include "stdafx.h"

#include "SttRemoteServerClientSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CSttRemoteServerClientSocket

CSttRemoteServerClientSocket::CSttRemoteServerClientSocket()
{

}

CSttRemoteServerClientSocket::~CSttRemoteServerClientSocket()
{

}

void CSttRemoteServerClientSocket::OnReceive(int nErrorCode)
{
	OnReceiveBuffer(nErrorCode);

	CSocket::OnReceive(nErrorCode);
}

//判断是远程还是本地断链
void CSttRemoteServerClientSocket::OnClose(int nErrorCode)
{
	OnSocketClose(nErrorCode);

	CSocket::OnClose(nErrorCode);
}

long CSttRemoteServerClientSocket::ReceiveBuffer(char *pBuf, long nLen)
{
	return Receive(pBuf, nLen);
}

long CSttRemoteServerClientSocket::SendBuffer(char *pBuf, long nLen)
{
	return Send(pBuf, nLen);
}