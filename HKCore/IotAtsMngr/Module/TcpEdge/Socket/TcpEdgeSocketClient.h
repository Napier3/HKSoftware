/**
 *@file
 *\brief 对设备SOCKET客户端,所有的连接都是由客户端来执行的
 */

#ifndef _TCPEDGESOCKETCLIENT_H_
#define _TCPEDGESOCKETCLIENT_H_

#include <QTcpSocket>

class CTcpEdgeSocketClient : public QTcpSocket
{
	Q_OBJECT
private:
	QString m_strIP;
	long m_nPort;
	bool m_bConnected;
	QString m_strLastError;

	enum BindFlag {
		DefaultForPlatform = 0x0,
		ShareAddress = 0x1,
		DontShareAddress = 0x2,
		ReuseAddressHint = 0x4
	};

private:
	bool BindAndConnect(QString strLocalIP, QString strIP, long nPort);
	bool Connect(QString strIP, long nPort);

public:
	CTcpEdgeSocketClient();
	virtual ~CTcpEdgeSocketClient();

	bool Connect(QString strLocalIP, QString strIP, long nPort);
	bool IsConnected() { return m_bConnected; }
	void Disconnect();
	QString GetIP() { return m_strIP; }
	long GetPort() { return m_nPort; }
	bool Send(QByteArray bytes);
	QString GetLastError();
};

#endif