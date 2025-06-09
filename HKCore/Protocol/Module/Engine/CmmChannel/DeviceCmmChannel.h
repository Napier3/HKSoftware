#pragma once

#include "CmmGlobalDefine.h"

#include "../DeviceModel/DeviceCmmConfig.h"
#include "CmmChannelCreateMngr.h"
#include "../../../../Module/System/TickCount32.h"
/*
�豸ͨ������,ʵ��������ʵ���豸��ͨѶ
�Ӷ���ΪCCmm####Channel
������CPpTemplate
*/


class CDeviceCmmChannel :	public CExBaseList
{
public:
	CDeviceCmmChannel(void);
	virtual ~CDeviceCmmChannel(void);

	CWinThread *m_pThread;		//�����������߳�,�յ����ݺ󣬷�����Ϣ���߳̽��н���
	CDeviceCmmConfig *m_pDeviceConfig;
	BOOL m_bConnecting;
	DWORD m_dwCommMode;  //ͨѶģʽ��0=����ģʽ��1=�ʴ�ģʽ
	CExBaseObject *m_pEngineDataRef; //������CPpEngineData

	CCmmRcvSndTimeMngr m_oCmmRcvSndTimeMngr;
	CXPkgFullRcvJdgInterface *m_pXPkgFullRcvJdgInterface;
	CProtoPkgProcessInterface *m_pProtoPkgPrcss;  //2023-01-27  lijunqing

public:
	void SetCommMode(const CString &strMode);
	virtual UINT GetClassID(){return CMMCLASSID_DEVICE_CMM_CHANNEL;};

public:
	//����ͨ�����ӵ���غ���
	BOOL ConnectDevice(CDeviceCmmConfig *pDeviceConfig, BOOL bCreateChannel=TRUE);
	BOOL ConnectDevice(BOOL bCreateChannel=TRUE);
	BOOL DisConnectDevice();

	BOOL OnReceive(CCmmChannel *pChannel, CCmmRcvSndTime *pCmmTime);
	BOOL OnCmmChannelClose(CCmmChannel *pChannel);
        BOOL ConnetAllClient(CCmmUdpServerChannel *pUdpServerChannel);
        BOOL IsConnectSuccessful();
	void OnCmmChannelConnectFinish();
	void OnCmmChannelConnectFailed();
	BOOL IsAllCmmChannelExit();
	BOOL IsConnecting()		{		return m_bConnecting;		}
	DWORD GetTimeLong()		{		return m_oTickCount32.GetTickCountLong();	}

private:
	CTickCount32 m_oTickCount32;
	void CreateCmmChannel();
        BOOL ConnetClient(CCmmUdpServerChannel *pUdpServerChannel, CCmmChannel *pClientChannel);

};
