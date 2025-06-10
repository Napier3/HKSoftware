// SttRemoteServerClientSocket.cpp : 实现文件
//

#include "stdafx.h"

#include "SttCloudServerClientSocket.h"
#include "..\..\..\Module\Socket\SocketGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CSttRemoteServerClientSocket

CSttCloudServerClientSocket::CSttCloudServerClientSocket()
{

}

CSttCloudServerClientSocket::~CSttCloudServerClientSocket()
{

}

void CSttCloudServerClientSocket::OnReceive(int nErrorCode)
{
	OnReceiveBuffer(nErrorCode);
}

//判断是远程还是本地断链
void CSttCloudServerClientSocket::OnClose(int nErrorCode)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s Disonnect"), m_strIPRemote.GetString());
	OnSocketClose(nErrorCode);
}

void CSttCloudServerClientSocket::CloseSocket()
{
	Close();
}

long CSttCloudServerClientSocket::ReceiveBuffer(BYTE *pBuf, long nLen)
{
	return 0;
}

long CSttCloudServerClientSocket::SendBuffer(BYTE *pBuf, long nLen)
{
	return Send((char*)pBuf, nLen);
}

long CSttCloudServerClientSocket::OnReceive(BYTE *pRcvBuf, int iLen)
{
	OnReceiveBuffer(pRcvBuf, iLen);
	return 0;
}