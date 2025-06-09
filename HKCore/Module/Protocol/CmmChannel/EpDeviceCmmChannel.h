#pragma once


#include "config\EpDeviceCmmConfig.h"
#include "EpCmmChannelCreateMngr.h"

/*
�豸ͨ������,ʵ��������ʵ���豸��ͨѶ
�Ӷ���ΪCEpCmm####Channel
������CEpProtocolBase
*/

class CEpDeviceCmmChannel :	public CExBaseList
{
public:
	CEpDeviceCmmChannel(void);
	~CEpDeviceCmmChannel(void);

	CWinThread *m_pThread;		//�����������߳�,�յ����ݺ󣬷�����Ϣ���߳̽��н���
	CEpDeviceCmmConfig *m_pDeviceConfig;
	BOOL m_bConnecting;

	CEpCmmRcvSndTimeMngr m_oCmmRcvSndTimeMngr;

public:
	virtual UINT GetClassID(){return EPCMMCLASSID_DEVICE_CMM_CHANNEL;};

public:
	//����ͨ�����ӵ���غ���
	BOOL ConnectDevice(CEpDeviceCmmConfig *pDeviceConfig);
	BOOL ConnectDevice();
	BOOL DisConnectDevice();

	BOOL OnReceive(CEpCmmChannel *pChannel, CEpCmmRcvSndTime *pCmmTime);
	BOOL ConnetAllClient(CEpCmmUdpServerChannel *pUdpServerChannel);
	BOOL IsConnectSuccessful();
	void OnCmmChannelConnectFinish();
	BOOL IsAllCmmChannelExit();
	BOOL IsConnecting()		{		return m_bConnecting;		}

	CEpCmmChannel* FindCmmChannel(const CString &strChannelID);
	CEpCmmChannel* FindCmmChannel(UINT nClassID);

private:
	void CreateCmmChannel();
	BOOL ConnetClient(CEpCmmUdpServerChannel *pUdpServerChannel, CEpCmmChannel *pClientChannel);

};
