/**
 *@file
 *\brief 设备对象类
 */

#ifndef _TCPEDGEDEVICE_H_
#define _TCPEDGEDEVICE_H_

#include "TcpEdgeProtocol.h"
#include "TcpEdgeDeviceRecord.h"
#include "Word/TcpEdgeWordTool.h"

class CTcpEdgeDevice : public QObject, public CExBaseList
{
	Q_OBJECT
public:
	/** 设备名称 **/
	QString m_strDeviceName;
	/** 设备ID **/
	QString m_strDeviceID;
	/** 日志文件 **/
	QString m_strLogFile;
	/** 报告文件 **/
	QString m_strRptFile;
	/** 设备启动时间 **/
	QString m_strSetupTime;
	/** 文件接收路径 **/
	QString m_strRecvFilePath;
	/** 鉴权状态 **/
	long m_nHasAuth;
	/** 签名状态 **/
	bool m_bSign;
	/** 压缩状态 **/
	bool m_bZlib;
	/** 保存日志状态 **/
	bool m_bSavePkg;
	/** 保存报告状态 **/
	bool m_bSaveRpt;
	/** 鉴权R1接收 **/
	BYTE m_byteRecvR1[8];
	/** 鉴权R2发送 **/
	BYTE m_byteR2[8];
	/** 鉴权R2接收 **/
	BYTE m_byteRecvR2[8];
	/** 数据模型 **/
	CDvmDevice m_oDvmDevice;
	/** 规约模板指针 **/
	CTcpEdgeProtocol *m_pProtocol;
	/** 接收报文列表 **/
	CExBaseList m_listRcvPkg;
	/** 发送报文列表 **/
	CExBaseList m_listSendPkg;
	/** 测试过程中产生的数据记录 **/
	CTcpEdgeDeviceRecord m_oRecord;
	/** 测试报告生成接口 **/
	CTcpEdgeWordTool* m_pWordTool;

private:
	void InitProtocol(QString strDvmFile);

signals:
	/**
	 *@brief 心跳超时(设备ID)
	 */ 
	void sig_healthTimeout(QString);
	/**
	 *@brief 发送报文(设备ID, 端口, 流程ID, 数据)
	 */ 
	void sig_send(QString,long,QString,QByteArray);
	/**
	 *@brief 更新消息(IP, 消息, 消息类型)
	 */ 
	void sig_updatePkg(QString,QString,long);

public:
	CTcpEdgeDevice();
	virtual ~CTcpEdgeDevice();

	//创建与更新设备
	void CreateDevice(QString strIP, long nMngrPort, long nDataPort);
	void UpdateDevice(QString strName, QString strID);
	
	//接收SOCKET报文
	void OnRecieve(long nPort, QByteArray bytes);
	//Procedure报文下发
	void Send(long nPort, BYTE* pBuf, QString strPrcdrID, long nLen);
	//自定义报文下发
	void RunProcedure(QString strPkg, bool bIsMngrCh);
	//平台选定报文下发
	void RunProcedure(QString& strProcedureID, CDvmDataset *pDataset, long nPort = 0);

	CDvmDataset* FindDatasetByID(QString strID);

public slots:
	void slot_timeout();
	void slot_updatePkg(QString strIP, QString strLog, long nType);
};

#endif
