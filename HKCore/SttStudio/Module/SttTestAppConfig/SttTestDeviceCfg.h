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
	BOOL GetRemoteIP(CString &strRemoteIP);  //����˵�IP
	BOOL GetRemotePort(long &nPort);         //����˵Ķ˿�
	BOOL GetLocalIP(CString &strLocalIP);    //����IP��Loginָ����Ҫ

	void OpenTestDeviceConfig(const CString &strFile);
	void GetDefaultConfigFile(CString &strFile);
	void SaveTestDeviceConfig(const CString &strFile);

public:
	virtual void InitAfterRead();
};