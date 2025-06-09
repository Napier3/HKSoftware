#include "stdafx.h"

#include "SttRemoteClientSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttRemoteClientSocket::CSttRemoteClientSocket()
{

}

CSttRemoteClientSocket::~CSttRemoteClientSocket()
{

}

BOOL CSttRemoteClientSocket::ConnectServer(const CString &strIPServer,long nPort)
{
	m_strIPRemote = strIPServer;
	m_nPortRemote = nPort;
	return Connect(strIPServer,nPort);
}

void CSttRemoteClientSocket::OnReceive(int nErrorCode)
{
	OnReceiveBuffer(nErrorCode);

	CSocket::OnReceive(nErrorCode);
}

long CSttRemoteClientSocket::ReceiveBuffer(BYTE *pBuf, long nLen)
{
	return Receive(pBuf, nLen);
}

long CSttRemoteClientSocket::SendBuffer(BYTE *pBuf, long nLen)
{
	return Send(pBuf, nLen);
}