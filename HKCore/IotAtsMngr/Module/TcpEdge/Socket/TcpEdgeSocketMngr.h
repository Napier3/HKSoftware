/**
 *@file
 *\brief 对设备连接进行管理的管理模块
 *内部记录了设备IP及其对应的CTcpEdgeSocket线程
 */

#ifndef _TCPEDGESOCKETMNGR_H_
#define _TCPEDGESOCKETMNGR_H_

#include "TcpEdgeSocket.h"
#include <QMap>

class CTcpEdgeSocketMngr : public QObject
{
	Q_OBJECT
private:
	QMap<QString, CTcpEdgeSocket*> m_mapSockets; //本平台为客户端,所连接边缘网关为服务器

public:
	CTcpEdgeSocketMngr();
	virtual ~CTcpEdgeSocketMngr();

public:
	bool Connect(QString strLocalIP, QString strIP, long nMngrPort, long nDataPort);
	void Disconnect(QString strIP);
	void Send(QString strIP, long nPort, QByteArray bytes);

signals:
	void sig_recieve(QString,long,QByteArray);
	void sig_disconnect(QString,long);

public slots:
	void slot_info(QString strIP, long nPort, QString strInfo);
	void slot_err(QString strIP,long nPort, QString strErr);
	void slot_pkg(QString strIP,long nPort, QByteArray bytes);
	void slot_disconnect(QString strIP,long nPort);
};

#endif