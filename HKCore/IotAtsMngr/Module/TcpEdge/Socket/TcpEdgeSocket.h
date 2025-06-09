/**
 *@file
 *\brief ��ÿ���豸�Ľ��뵥�������̵߳��߳�ģ��
 *ÿ�������̶߳�Ӧ���豸������SOCKET�ͻ���CTcpEdgeSocketClient
 */

#ifndef _TCPEDGESOCKET_H_
#define _TCPEDGESOCKET_H_

#include "TcpEdgeSocketClient.h"
#include "../TcpEdgeGlobalDef.h"
#include "../../../../Module/MemBuffer/ExpandMemBuf.h"
#include <QThread>
#include <QReadWriteLock>
#include <QQueue>

struct tagBytes
{
	QString m_strIP;
	long m_nPort;
	QByteArray m_bytes;
};

class CTcpEdgeSocket : public QThread
{
	Q_OBJECT
private:
	QString m_strIP;
	long m_nMngrPort;
	long m_nDataPort;
	long m_bExit;		//�Ƿ��˳�
	bool m_bExited;		//�Ƿ��Ѿ��Ƴ�

	QReadWriteLock m_locker;
	QQueue<tagBytes> m_queueBytes;

	CTcpEdgeSocketClient* m_pMngrSocket;
	CTcpEdgeSocketClient* m_pDataSocket;

	//���ջ���
	long m_nMngrRecvIndex;
	CExpandMemBuf m_oMngrExpandRecvBuf;
	CExpandMemBuf m_oMngrPassageRecvBuf[256];
	long m_oMngrPassageRecvLen[256];

	long m_nDataRecvIndex;
	CExpandMemBuf m_oDataExpandRecvBuf;
	CExpandMemBuf m_oDataPassageRecvBuf[256];
	long m_oDataPassageRecvLen[256];

public:
	CTcpEdgeSocket();
	virtual ~CTcpEdgeSocket();

	/**
	 *@brief QThread����
	 */ 
	void run();
	/**
	 *@brief ��ʼ���豸����
	 *@param[in] strLocalIP ����ָ��IP
	 *@param[in] strIP �豸IP
	 *@param[in] nMngrPort ����ͨ���˿ں�
	 *@param[in] nDataPort ҵ��ͨ���˿ں�
	 *@return ����trueΪ�����ɹ�
	 */ 
	bool InitSocket(QString strLocalIP, QString strIP, long nMngrPort, long nDataPort);
	/**
	 *@brief �ر��豸����
	 */ 
	void Close();
	/**
	 *@brief ���ͱ���
	 *@param[in] nPort ���Ͷ˿�
	 *@param[in] bytes ��������
	 */ 
	void Send(long nPort, QByteArray bytes);
	/**
	 *@brief ��ȡ�豸�Ĺ���ͨ���˿�
	 *@return ���ض˿ں�
	 */ 
	long GetMngrPort() { return m_nMngrPort; }
	/**
	 *@brief ��ȡ�豸��ҵ��ͨ���˿�
	 *@return ���ض˿ں�
	 */ 
	long GetDataPort() { return m_nDataPort; }

protected:
	/**
	 *@brief д����
	 *@param[in] strIP �豸IP
	 *@param[in] nPort �˿ں�
	 *@param[in] bytes ����
	 */ 
	void WriteBytes(QString strIP, long nPort, QByteArray bytes);
	/**
	 *@brief ������
	 *@param[in] strIP �豸IP
	 *@param[in] nPort �˿ں�
	 *@return ���ر���
	 */ 
	QByteArray ReadBytes(QString& strIP, long& nPort);
	/**
	 *@brief ���չ���ͨ��������Ӧ
	 *@param[in] bytes ���յ��ı���
	 */ 
 	void OnMngrReceiveBuffer(QByteArray bytes);
	/**
	 *@brief ����������
	 *@return ����ture�����ɹ�
	 */ 
 	bool AnalysisMngrRecvBuf();
	/**
	 *@brief ���͹�����
	 *@param[in] strGatewayID �豸ID
	 *@param[in] pBuf ����
	 *@param[in] nLen ���ĳ���
	 *@return ����ture�������
	 */ 
 	bool ProcessRecvMngrPacket(QString strGatewayID, BYTE *pBuf, long nLen);
	/**
	 *@brief ����ҵ��ͨ��������Ӧ
	 *@param[in] bytes ���յ��ı���
	 */ 
	void OnDataReceiveBuffer(QByteArray bytes);
	/**
	 *@brief ����ҵ����
	 *@return ����ture�����ɹ�
	 */ 
	bool AnalysisDataRecvBuf();
	/**
	 *@brief ����ҵ����
	 *@param[in] strGatewayID �豸ID
	 *@param[in] pHead ����ͷ
	 *@param[in] nHeadLen ����ͷ����
	 *@param[in] pBuf ��������
	 *@param[in] nLen �������ݳ���
	 *@return ����ture�������
	 */ 
	bool ProcessRecvDataPacket(QString strGatewayID, BYTE *pHead, long nHeadLen, BYTE *pBuf, long nLen);
signals:
	//������ط���
	void sig_info(QString,long,QString);
	void sig_err(QString,long,QString);
	void sig_pkg(QString,long,QByteArray);
	void sig_disconnect(QString,long);

public slots:
	void OnMngrRead();
	void OnDataRead();
	void OnMngrDisconnect();
	void OnDataDisconnect();
};

#endif