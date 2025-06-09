#include "TcpEdgeSocketMngr.h"

CTcpEdgeSocketMngr::CTcpEdgeSocketMngr()
{

}

CTcpEdgeSocketMngr::~CTcpEdgeSocketMngr()
{

}

bool CTcpEdgeSocketMngr::Connect(QString strLocalIP, QString strIP, long nMngrPort, long nDataPort)
{
	CTcpEdgeSocket* pSocket = new CTcpEdgeSocket;
	connect(pSocket, SIGNAL(sig_info(QString,long,QString)), this, SLOT(slot_info(QString,long,QString)));
	connect(pSocket, SIGNAL(sig_err(QString,long,QString)), this, SLOT(slot_err(QString,long,QString)));
	connect(pSocket, SIGNAL(sig_pkg(QString,long,QByteArray)), this, SLOT(slot_pkg(QString,long,QByteArray)));
	connect(pSocket, SIGNAL(sig_disconnect(QString,long)), this, SLOT(slot_disconnect(QString,long)));

	bool bRet = pSocket->InitSocket(strLocalIP, strIP, nMngrPort, nDataPort);
	if(bRet)
	{
		m_mapSockets[strIP] = pSocket;
		pSocket->start();
	}

	return bRet;
}

void CTcpEdgeSocketMngr::Disconnect(QString strIP)
{
	if (m_mapSockets[strIP] != NULL)
	{
		emit sig_disconnect(strIP, m_mapSockets[strIP]->GetDataPort());
		emit sig_disconnect(strIP, m_mapSockets[strIP]->GetMngrPort());
		delete m_mapSockets[strIP];
		m_mapSockets.remove(strIP);
	}
}

void CTcpEdgeSocketMngr::Send(QString strIP, long nPort, QByteArray bytes)
{
	if(m_mapSockets[strIP])
	{
		m_mapSockets[strIP]->Send(nPort, bytes);
	}
}

void CTcpEdgeSocketMngr::slot_info(QString strIP, long nPort, QString strInfo)
{

}

void CTcpEdgeSocketMngr::slot_err(QString strIP,long nPort, QString strErr)
{

}

void CTcpEdgeSocketMngr::slot_pkg(QString strIP,long nPort, QByteArray bytes)
{
	emit sig_recieve(strIP, nPort, bytes);
}

void CTcpEdgeSocketMngr::slot_disconnect(QString strIP,long nPort)
{
	emit sig_disconnect(strIP, nPort);
}