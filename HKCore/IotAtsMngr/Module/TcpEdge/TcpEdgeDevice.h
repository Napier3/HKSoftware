/**
 *@file
 *\brief �豸������
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
	/** �豸���� **/
	QString m_strDeviceName;
	/** �豸ID **/
	QString m_strDeviceID;
	/** ��־�ļ� **/
	QString m_strLogFile;
	/** �����ļ� **/
	QString m_strRptFile;
	/** �豸����ʱ�� **/
	QString m_strSetupTime;
	/** �ļ�����·�� **/
	QString m_strRecvFilePath;
	/** ��Ȩ״̬ **/
	long m_nHasAuth;
	/** ǩ��״̬ **/
	bool m_bSign;
	/** ѹ��״̬ **/
	bool m_bZlib;
	/** ������־״̬ **/
	bool m_bSavePkg;
	/** ���汨��״̬ **/
	bool m_bSaveRpt;
	/** ��ȨR1���� **/
	BYTE m_byteRecvR1[8];
	/** ��ȨR2���� **/
	BYTE m_byteR2[8];
	/** ��ȨR2���� **/
	BYTE m_byteRecvR2[8];
	/** ����ģ�� **/
	CDvmDevice m_oDvmDevice;
	/** ��Լģ��ָ�� **/
	CTcpEdgeProtocol *m_pProtocol;
	/** ���ձ����б� **/
	CExBaseList m_listRcvPkg;
	/** ���ͱ����б� **/
	CExBaseList m_listSendPkg;
	/** ���Թ����в��������ݼ�¼ **/
	CTcpEdgeDeviceRecord m_oRecord;
	/** ���Ա������ɽӿ� **/
	CTcpEdgeWordTool* m_pWordTool;

private:
	void InitProtocol(QString strDvmFile);

signals:
	/**
	 *@brief ������ʱ(�豸ID)
	 */ 
	void sig_healthTimeout(QString);
	/**
	 *@brief ���ͱ���(�豸ID, �˿�, ����ID, ����)
	 */ 
	void sig_send(QString,long,QString,QByteArray);
	/**
	 *@brief ������Ϣ(IP, ��Ϣ, ��Ϣ����)
	 */ 
	void sig_updatePkg(QString,QString,long);

public:
	CTcpEdgeDevice();
	virtual ~CTcpEdgeDevice();

	//����������豸
	void CreateDevice(QString strIP, long nMngrPort, long nDataPort);
	void UpdateDevice(QString strName, QString strID);
	
	//����SOCKET����
	void OnRecieve(long nPort, QByteArray bytes);
	//Procedure�����·�
	void Send(long nPort, BYTE* pBuf, QString strPrcdrID, long nLen);
	//�Զ��屨���·�
	void RunProcedure(QString strPkg, bool bIsMngrCh);
	//ƽ̨ѡ�������·�
	void RunProcedure(QString& strProcedureID, CDvmDataset *pDataset, long nPort = 0);

	CDvmDataset* FindDatasetByID(QString strID);

public slots:
	void slot_timeout();
	void slot_updatePkg(QString strIP, QString strLog, long nType);
};

#endif
