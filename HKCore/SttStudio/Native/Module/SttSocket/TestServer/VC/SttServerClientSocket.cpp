#include "stdafx.h"
#include "SttServerClientSocket.h"

CSttServerClientSocket::CSttServerClientSocket()
{

}

CSttServerClientSocket::~CSttServerClientSocket()
{
	
}

void CSttServerClientSocket::OnReceive(int nErrorCode)
{
	OnReceiveBuffer(nErrorCode);
}

//�ж���Զ�̻��Ǳ��ض���
void CSttServerClientSocket::OnClose(int nErrorCode)
{
	OnSocketClose(nErrorCode);
}

void CSttServerClientSocket::CloseSocket()
{
	Close();
}

long CSttServerClientSocket::ReceiveBuffer(BYTE *pBuf, long nLen)
{
	return 0;
}

long CSttServerClientSocket::SendBuffer(BYTE *pBuf, long nLen)
{
	return Send((char*)pBuf, nLen);
}

long CSttServerClientSocket::OnReceive(BYTE *pRcvBuf, int iLen)
{
	OnReceiveBuffer(pRcvBuf, iLen);
	return 0;
}