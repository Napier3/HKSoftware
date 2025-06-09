/**
 *@file
 *\brief ���豸���ӽ��й���Ĺ���ģ��
 *�ڲ���¼���豸IP�����Ӧ��CTcpEdgeSocket�߳�
 */

#ifndef _TCPEDGESOCKETMNGR_H_
#define _TCPEDGESOCKETMNGR_H_

#include "TcpEdgeSocket.h"
#include <QMap>

class CTcpEdgeSocketMngr : public QObject
{
	Q_OBJECT
private:
	QMap<QString, CTcpEdgeSocket*> m_mapSockets; //��ƽ̨Ϊ�ͻ���,�����ӱ�Ե����Ϊ������

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