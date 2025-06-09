#pragma once

/**************************************
CSttTestDeviceCfg:
**************************************/

#include "../../../Module/DataMngr/DataGroup.h"


#define TEST_DEVICE_CFG_LOCAL_IP			_T("local-ip")
#define TEST_DEVICE_CFG_REMOTE_IP			_T("remote-ip")
#define TEST_DEVICE_CFG_REMOTE_PORT		    _T("remote-port")

class CSttTestDeviceCfg : public CDataGroup
{
public:
	CSttTestDeviceCfg();
	virtual ~CSttTestDeviceCfg();

	CString m_strLocalIP;
	CString m_strRemoteIP;
	long m_nRemotePort;

public:
	BOOL GetRemoteIP(CString &strRemoteIP);  //服务端的IP
	BOOL GetRemotePort(long &nPort);         //服务端的端口
	BOOL GetLocalIP(CString &strLocalIP);    //本地IP。Login指令需要

	void OpenTestDeviceConfig(const CString &strFile);
	void GetDefaultConfigFile(CString &strFile);
	void SaveTestDeviceConfig(const CString &strFile);

public:
	virtual void InitAfterRead();
};