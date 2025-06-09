#include "stdafx.h"

#include "SttPpServerSocket.h"
#include "SttPpServerClientSocket.h"

CSttPpServerSocket::CSttPpServerSocket()
{
	
}

CSttPpServerSocket::~CSttPpServerSocket()
{
	
}

CWinTcpSocketClient* CSttPpServerSocket::CreateNewSocketClient()
{
	return new CSttPpServerClientSocket();
}
