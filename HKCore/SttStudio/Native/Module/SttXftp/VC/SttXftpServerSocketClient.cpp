// SttRemoteServerClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "SttXftpServerSocketClient.h"
#include "..\..\..\..\Module\Socket\SocketGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CSttRemoteServerClientSocket

CSttXftpServerSocketClient::CSttXftpServerSocketClient()
{

}

CSttXftpServerSocketClient::~CSttXftpServerSocketClient()
{

}

void CSttXftpServerSocketClient::OnReceive(int nErrorCode)
{
	OnReceiveBuffer(nErrorCode);
}

//�ж���Զ�̻��Ǳ��ض���
void CSttXftpServerSocketClient::OnClose(int nErrorCode)
{
	OnSocketClose(nErrorCode);
}

void CSttXftpServerSocketClient::CloseSocket()
{
	Close();
}

long CSttXftpServerSocketClient::ReceiveBuffer(BYTE *pBuf, long nLen)
{
	return 0;
}

long CSttXftpServerSocketClient::SendBuffer(BYTE *pBuf, long nLen)
{
	return Send((char*)pBuf, nLen);
}

long CSttXftpServerSocketClient::OnReceive(BYTE *pRcvBuf, int iLen)
{
	OnReceiveBuffer(pRcvBuf, iLen);
	return 0;
}

