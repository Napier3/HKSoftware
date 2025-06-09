#pragma once


#include "config\EpDeviceCmmConfig.h"
#include "EpCmmChannelCreateMngr.h"

/*
设备通道对象,实现引擎与实际设备的通讯
子对象为CEpCmm####Channel
父对象：CEpProtocolBase
*/

class CEpDeviceCmmChannel :	public CExBaseList
{
public:
	CEpDeviceCmmChannel(void);
	~CEpDeviceCmmChannel(void);

	CWinThread *m_pThread;		//关联的引擎线程,收到数据后，发送消息给线程进行解析
	CEpDeviceCmmConfig *m_pDeviceConfig;
	BOOL m_bConnecting;

	CEpCmmRcvSndTimeMngr m_oCmmRcvSndTimeMngr;

public:
	virtual UINT GetClassID(){return EPCMMCLASSID_DEVICE_CMM_CHANNEL;};

public:
	//管理通道连接的相关函数
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
