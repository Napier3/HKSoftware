#include "stdafx.h"

#include "SttNativeRemoteClientSocket.h"
#include "../../../Engine/SttTestEngineBase.h"
#include "QHostAddress"

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
	disconnect(m_pSocket,SIGNAL(connected()),this,SLOT(Connected_Qt()));
	disconnect(m_pSocket,SIGNAL(disconnected()),this,SLOT(CloseSocket_Qt()));
	disconnect(m_pSocket,SIGNAL(readyRead()),this,SLOT(ReceiveBuffer_Qt()));
}

void CSttNativeRemoteClientSocket::Connected_Qt()
{
	g_pSttTestEngine->SetRefSocket(this);
	connect(m_pSocket,SIGNAL(disconnected()),this,SLOT(CloseSocket_Qt()));
	connect(m_pSocket,SIGNAL(readyRead()),this,SLOT(ReceiveBuffer_Qt()));
}

void CSttNativeRemoteClientSocket::CloseSocket_Qt()
{
	g_pSttTestEngine->CloseSocket(this);
}

void CSttNativeRemoteClientSocket::ReceiveBuffer_Qt()
{
	OnReceiveBuffer(0);
}

void CSttNativeRemoteClientSocket::OnError(QAbstractSocket::SocketError)
{//connect error
	CloseSocket();
}

BOOL CSttNativeRemoteClientSocket::ConnectServer(const CString &strIPServer,long nPort)
{//脱机软件中远程连接
	m_pSocket = new QTcpSocket;
	connect(m_pSocket,SIGNAL(connected()),this,SLOT(Connected_Qt()));
	connect(m_pSocket,SIGNAL(error(QAbstractSocket::SocketError))),this,SLOT(OnError(QAbstractSocket::SocketError));
	m_pSocket->connectToHost(QHostAddress(pszIP), nPort);

	m_strIPRemote = pszIP;
	m_nPortRemote = nPort;

	return TRUE;
}

void CSttNativeRemoteClientSocket::CloseSocket()
{
	m_pSocket->close();
}

long CSttNativeRemoteClientSocket::ReceiveBuffer(BYTE *pBuf, long nLen)
{
	return m_pSocket->read((char*)pBuf, nLen);
}

long CSttNativeRemoteClientSocket::SendBuffer(BYTE *pBuf, long nLen)
{
	stt_pkg_set_send_index(pBuf, m_nSendIndex++);
	return m_pSocket->write((const char*)pBuf,nLen);
}