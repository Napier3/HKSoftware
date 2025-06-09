/**
 *@file
 *\brief 报文规约子线程,继承自QThread
 */

#ifndef _TCPEDGEENGINETHREAD_H_
#define _TCPEDGEENGINETHREAD_H_

#include <QTime>
#include <QThread>

class CTcpEdgeProtocol;
class CTcpEdgeEngineThread : public QThread
{
	Q_OBJECT
public:
	/** 管理通道上次心跳时间 **/
	QTime m_timeMngrLastHealth;
	/** 业务通道上次心跳时间 **/
	QTime m_timeDataLastHealth;
	/** 规约对象 **/
	CTcpEdgeProtocol* m_pProtocol;

public:
	CTcpEdgeEngineThread();
	virtual ~CTcpEdgeEngineThread();
	/**
	 *@brief 多线程执行函数重载,报文处理
	 */ 
	void run();

signals:
	/**
	 *@brief 线程退出信号
	 */ 
	void sig_exit();
};

#endif