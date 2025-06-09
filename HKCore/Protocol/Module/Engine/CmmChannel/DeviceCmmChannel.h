#pragma once

#include "CmmGlobalDefine.h"

#include "../DeviceModel/DeviceCmmConfig.h"
#include "CmmChannelCreateMngr.h"
#include "../../../../Module/System/TickCount32.h"
/*
设备通道对象,实现引擎与实际设备的通讯
子对象为CCmm####Channel
父对象：CPpTemplate
*/


class CDeviceCmmChannel :	public CExBaseList
{
public:
	CDeviceCmmChannel(void);
	virtual ~CDeviceCmmChannel(void);

	CWinThread *m_pThread;		//关联的引擎线程,收到数据后，发送消息给线程进行解析
	CDeviceCmmConfig *m_pDeviceConfig;
	BOOL m_bConnecting;
	DWORD m_dwCommMode;  //通讯模式；0=随意模式；1=问答模式
	CExBaseObject *m_pEngineDataRef; //关联的CPpEngineData

	CCmmRcvSndTimeMngr m_oCmmRcvSndTimeMngr;
	CXPkgFullRcvJdgInterface *m_pXPkgFullRcvJdgInterface;
	CProtoPkgProcessInterface *m_pProtoPkgPrcss;  //2023-01-27  lijunqing

public:
	void SetCommMode(const CString &strMode);
	virtual UINT GetClassID(){return CMMCLASSID_DEVICE_CMM_CHANNEL;};

public:
	//管理通道连接的相关函数
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
