#include "TcpEdgeSocketClient.h"
#include <QTime>

#ifdef Q_OS_LINUX
	#include <arpa/inet.h>
#else
	#include <WinSock.h>
	#pragma comment(lib, "ws2_32.lib")
#endif


CTcpEdgeSocketClient::CTcpEdgeSocketClient()
{
	m_nPort = 0;
	m_bConnected = false;
}

CTcpEdgeSocketClient::~CTcpEdgeSocketClient()
{

}

bool CTcpEdgeSocketClient::BindAndConnect(QString strLocalIP, QString strIP, long nPort)
{
 	int sockfd;
 	int result;
 	struct sockaddr_in localSockAddr;
 	struct sockaddr_in serverSockAddr;
 	memset(&localSockAddr, 0, sizeof(localSockAddr));
 	memset(&serverSockAddr, 0, sizeof(serverSockAddr));


	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	long nLocalPort = 1024 + qrand() % (65535 - 1024);

#ifndef Q_OS_LINUX
	WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(1, 1);
    long nErr = WSAStartup(wVersionRequested, &wsaData);
#endif

 	// create socket
 	sockfd = socket(AF_INET, SOCK_STREAM, 0);
 	if( sockfd == -1 ) 
 	{
 		qDebug() << WSAGetLastError();
		closesocket(sockfd);
 		return false;
 	}
 
 	// bind
 	localSockAddr.sin_family = AF_INET;
 	localSockAddr.sin_port = htons(nLocalPort);
 	localSockAddr.sin_addr.s_addr = inet_addr(strLocalIP.toLocal8Bit().data());
 
	long nCount = 65000;//重试65000次随机端口
 	while(bind(sockfd, (struct sockaddr *)&localSockAddr, sizeof(localSockAddr)) == -1)
 	{
		if(nCount == 0)
		{
			//随机了65000次端口后仍然绑定失败
			closesocket(sockfd);
			return false;
		}

 		qDebug() << WSAGetLastError();
		nLocalPort = 1024 + qrand() % (65535 - 1024);
		localSockAddr.sin_port = htons(nLocalPort);
		nCount--;
 	}
 
 	// connect
 	serverSockAddr.sin_family = AF_INET;
 	serverSockAddr.sin_port = htons(nPort);
	serverSockAddr.sin_addr.s_addr = inet_addr(strIP.toLocal8Bit().data());
	result = ::connect(sockfd, (struct sockaddr *)&serverSockAddr, sizeof(serverSockAddr));
 	if( result == -1 ) 
 	{
 		qDebug() << WSAGetLastError();
		closesocket(sockfd);
 		return false;
 	}
 
 	// set socket descriptor
 	if( !setSocketDescriptor(sockfd, QAbstractSocket::ConnectedState))
 	{
 		qDebug() << WSAGetLastError();
		closesocket(sockfd);
 		return false;
 	}

	return true;
}

bool CTcpEdgeSocketClient::Connect(QString strIP, long nPort)
{
	connectToHost(strIP, nPort);
	if(waitForConnected(5000))
	{
		m_bConnected = true;
		return true;
	}

	return false;
}

bool CTcpEdgeSocketClient::Connect(QString strLocalIP, QString strIP, long nPort)
{
	m_strIP = strIP;
	m_nPort = nPort;

	if (strLocalIP.length())
	{
		return BindAndConnect(strLocalIP, strIP, nPort);
	}

	return Connect(strIP, nPort);
}

void CTcpEdgeSocketClient::Disconnect()
{
	m_bConnected = false;
	abort();
}

bool CTcpEdgeSocketClient::Send(QByteArray bytes)
{
	if(write(bytes) == -1)
	{
		m_strLastError = errorString();
		return false;
	}

	if(waitForBytesWritten(5000))
	{
		m_strLastError = "发送数据超时!";
		return false;
	}

	return true;
}

QString CTcpEdgeSocketClient::GetLastError()
{
	return m_strLastError;
}