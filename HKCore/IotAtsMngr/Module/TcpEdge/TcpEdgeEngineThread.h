/**
 *@file
 *\brief ���Ĺ�Լ���߳�,�̳���QThread
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
	/** ����ͨ���ϴ�����ʱ�� **/
	QTime m_timeMngrLastHealth;
	/** ҵ��ͨ���ϴ�����ʱ�� **/
	QTime m_timeDataLastHealth;
	/** ��Լ���� **/
	CTcpEdgeProtocol* m_pProtocol;

public:
	CTcpEdgeEngineThread();
	virtual ~CTcpEdgeEngineThread();
	/**
	 *@brief ���߳�ִ�к�������,���Ĵ���
	 */ 
	void run();

signals:
	/**
	 *@brief �߳��˳��ź�
	 */ 
	void sig_exit();
};

#endif