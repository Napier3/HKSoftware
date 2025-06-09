/**
 *@file
 *\brief 对每个设备的接入单独创建线程的线程模块
 *每个连接线程对应该设备的两个SOCKET客户端CTcpEdgeSocketClient
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
	long m_bExit;		//是否退出
	bool m_bExited;		//是否已经推出

	QReadWriteLock m_locker;
	QQueue<tagBytes> m_queueBytes;

	CTcpEdgeSocketClient* m_pMngrSocket;
	CTcpEdgeSocketClient* m_pDataSocket;

	//接收缓存
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
	 *@brief QThread重载
	 */ 
	void run();
	/**
	 *@brief 初始化设备连接
	 *@param[in] strLocalIP 本地指定IP
	 *@param[in] strIP 设备IP
	 *@param[in] nMngrPort 管理通道端口号
	 *@param[in] nDataPort 业务通道端口号
	 *@return 返回true为创建成功
	 */ 
	bool InitSocket(QString strLocalIP, QString strIP, long nMngrPort, long nDataPort);
	/**
	 *@brief 关闭设备连接
	 */ 
	void Close();
	/**
	 *@brief 发送报文
	 *@param[in] nPort 发送端口
	 *@param[in] bytes 报文内容
	 */ 
	void Send(long nPort, QByteArray bytes);
	/**
	 *@brief 获取设备的管理通道端口
	 *@return 返回端口号
	 */ 
	long GetMngrPort() { return m_nMngrPort; }
	/**
	 *@brief 获取设备的业务通道端口
	 *@return 返回端口号
	 */ 
	long GetDataPort() { return m_nDataPort; }

protected:
	/**
	 *@brief 写报文
	 *@param[in] strIP 设备IP
	 *@param[in] nPort 端口号
	 *@param[in] bytes 报文
	 */ 
	void WriteBytes(QString strIP, long nPort, QByteArray bytes);
	/**
	 *@brief 读报文
	 *@param[in] strIP 设备IP
	 *@param[in] nPort 端口号
	 *@return 返回报文
	 */ 
	QByteArray ReadBytes(QString& strIP, long& nPort);
	/**
	 *@brief 接收管理通道报文响应
	 *@param[in] bytes 接收到的报文
	 */ 
 	void OnMngrReceiveBuffer(QByteArray bytes);
	/**
	 *@brief 分析管理报文
	 *@return 返回ture分析成功
	 */ 
 	bool AnalysisMngrRecvBuf();
	/**
	 *@brief 推送管理报文
	 *@param[in] strGatewayID 设备ID
	 *@param[in] pBuf 报文
	 *@param[in] nLen 报文长度
	 *@return 返回ture推送完成
	 */ 
 	bool ProcessRecvMngrPacket(QString strGatewayID, BYTE *pBuf, long nLen);
	/**
	 *@brief 接收业务通道报文响应
	 *@param[in] bytes 接收到的报文
	 */ 
	void OnDataReceiveBuffer(QByteArray bytes);
	/**
	 *@brief 分析业务报文
	 *@return 返回ture分析成功
	 */ 
	bool AnalysisDataRecvBuf();
	/**
	 *@brief 推送业务报文
	 *@param[in] strGatewayID 设备ID
	 *@param[in] pHead 报文头
	 *@param[in] nHeadLen 报文头长度
	 *@param[in] pBuf 报文内容
	 *@param[in] nLen 报文内容长度
	 *@return 返回ture推送完成
	 */ 
	bool ProcessRecvDataPacket(QString strGatewayID, BYTE *pHead, long nHeadLen, BYTE *pBuf, long nLen);
signals:
	//报文相关发送
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