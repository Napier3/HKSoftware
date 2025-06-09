#include "SttServerClientSocket.h"
#include "QDebug"

CSttServerClientSocket::CSttServerClientSocket()
{

}

CSttServerClientSocket::~CSttServerClientSocket()
{
	disconnect(m_pSocket,SIGNAL(disconnected()),this,SLOT(OnSocketClose_Qt()));
	disconnect(m_pSocket,SIGNAL(readyRead()),this,SLOT(ReceiveBuffer_Qt()));
}

void CSttServerClientSocket::OnSocketClose_Qt()
{
	OnSocketClose(0);
}

void CSttServerClientSocket::SetSocket(QTcpSocket* pSocket)
{
	m_pSocket = pSocket;
	connect(m_pSocket,SIGNAL(disconnected()),this,SLOT(OnSocketClose_Qt()));
	connect(m_pSocket,SIGNAL(readyRead()),this,SLOT(ReceiveBuffer_Qt()));
}

void CSttServerClientSocket::ReceiveBuffer_Qt()
{
	OnReceiveBuffer(0);
}

long CSttServerClientSocket::ReceiveBuffer(BYTE *pBuf,long nLen)
{
	/*
	QByteArray array=m_pSocket->readAll();
	int nRcvLen=array.size();

#ifdef DEBUG_MODE
	QString temp;
	for(int i=0;i<nRcvLen;i++)
	{
		temp+=QString("%1").arg(array.at(i),2,16,QChar('0'));
	}
	qDebug()<<temp;
#endif

	if(nRcvLen==0)
		return 0;

	memcpy(pBuf,array.data(),nRcvLen);
	return nRcvLen;
*/

	//2019-12-30   lijunqing
	long nRcvLen = m_pSocket->read((char*)pBuf, nLen);

	return nRcvLen;
}

long CSttServerClientSocket::SendBuffer(BYTE *pBuf,long nLen)
{
    stt_pkg_set_send_index(pBuf, m_nSendIndex++);
	int nRet=m_pSocket->write((const char*)pBuf,nLen);
	return nRet;
}

void CSttServerClientSocket::CloseSocket()
{
	m_pSocket->close();
}
