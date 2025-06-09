#include "stdafx.h"

#include "SttNativeRemoteClientSocket.h"
#include "../../../Engine/SttTestEngineBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttNativeRemoteClientSocket::CSttNativeRemoteClientSocket()
{

}

CSttNativeRemoteClientSocket::~CSttNativeRemoteClientSocket()
{

}

BOOL CSttNativeRemoteClientSocket::ConnectServer(const CString &strIPServer,long nPort)
{//脱机软件中远程连接
	char pszIPServer[64] = {0};
	CString_to_char(strIPServer,pszIPServer);

	m_strIPRemote = strIPServer;
	m_nPortRemote = nPort;

#ifndef _PSX_IDE_QT_
	InitSocket();
#endif

	SetReceiveBuffLen( STT_FILECMD_MAX_LEN );
	Create(SOCK_STREAM);

	BOOL bRet = Connect(pszIPServer, nPort);

	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("连接服务器[%s][%d]成功"), pszIPServer, nPort);
		InitSocketClient(20);
	}

	return bRet;
}

void CSttNativeRemoteClientSocket::OnReceive(int nErrorCode)
{
	OnReceiveBuffer(nErrorCode);
}

void CSttNativeRemoteClientSocket::OnClose(int nErrorCode)
{
	CSttNativeRemoteClientSocketBase::OnSocketClose(nErrorCode);
}

void CSttNativeRemoteClientSocket::CloseSocket()
{
	Close();
}

long CSttNativeRemoteClientSocket::ReceiveBuffer(BYTE *pBuf, long nLen)
{
	return 0;
}

long CSttNativeRemoteClientSocket::SendBuffer(BYTE *pBuf, long nLen)
{
	return Send((char*)pBuf, nLen);
}

long CSttNativeRemoteClientSocket::OnReceive(BYTE *pRcvBuf, int iLen)
{
	OnReceiveBuffer(pRcvBuf, iLen);
	return 0;
}