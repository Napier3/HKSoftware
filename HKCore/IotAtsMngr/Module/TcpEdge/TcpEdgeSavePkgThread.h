/**
 *@file
 *\brief 设备保存报文子线程,继承自QThread
 */

#ifndef _TCPEDGESAVEPKGTHREAD_H_
#define _TCPEDGESAVEPKGTHREAD_H_

#include <QThread>
#include <QVector>

class CTcpEdgeSavePkgThread : public QThread
{
public:
	/** 报文保存完成标记 **/
	void* m_pParam;
	/** 报文保存文件全路径 **/
	QString m_strFullFileName;
	/** 分段报文整合集合 **/
	QVector<CString> m_vecBuffer;

public:
	CTcpEdgeSavePkgThread();
	virtual ~CTcpEdgeSavePkgThread();

	/**
	 *@brief 多线程执行函数重载,保存文件
	 */ 
	void run();
};

#endif