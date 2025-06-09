/**
 *@file
 *\brief �豸���汨�����߳�,�̳���QThread
 */

#ifndef _TCPEDGESAVEPKGTHREAD_H_
#define _TCPEDGESAVEPKGTHREAD_H_

#include <QThread>
#include <QVector>

class CTcpEdgeSavePkgThread : public QThread
{
public:
	/** ���ı�����ɱ�� **/
	void* m_pParam;
	/** ���ı����ļ�ȫ·�� **/
	QString m_strFullFileName;
	/** �ֶα������ϼ��� **/
	QVector<CString> m_vecBuffer;

public:
	CTcpEdgeSavePkgThread();
	virtual ~CTcpEdgeSavePkgThread();

	/**
	 *@brief ���߳�ִ�к�������,�����ļ�
	 */ 
	void run();
};

#endif