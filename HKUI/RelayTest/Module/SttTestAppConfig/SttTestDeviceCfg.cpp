#include "stdafx.h"
#include "SttTestDeviceCfg.h"
#include"../../../Module/API/GlobalConfigApi.h"
#include"../../../Module/API/FileApi.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
char THIS_FILE[] = __FILE__; 
#endif  

CSttTestDeviceCfg::CSttTestDeviceCfg()
{
	m_nRemotePort = 19821;
	m_strRemoteIP = _T("127.0.0.1");
	m_strLocalIP  = _T("127.0.0.1");
}

CSttTestDeviceCfg::~CSttTestDeviceCfg()
{

}

BOOL CSttTestDeviceCfg::GetRemoteIP(CString &strRemoteIP)
{
	strRemoteIP = _T("192.168.2.10");
	return GetDataValue(TEST_DEVICE_CFG_REMOTE_IP,strRemoteIP);
}

BOOL CSttTestDeviceCfg::GetRemotePort(long &nPort)
{
	nPort = 19821;
	return GetDataValue(TEST_DEVICE_CFG_REMOTE_PORT,nPort);
}

BOOL CSttTestDeviceCfg::GetLocalIP(CString &strLocalIP)
{
	strLocalIP = _T("127.0.0.1");
	return GetDataValue(TEST_DEVICE_CFG_LOCAL_IP,strLocalIP);
}


void CSttTestDeviceCfg::GetDefaultConfigFile(CString &strFile)
{
	strFile = _P_GetConfigPath();
	strFile += _T("TestDeviceCfg.xml");
}

void CSttTestDeviceCfg::OpenTestDeviceConfig(const CString &strFile)
{
	CString strPath = strFile;
	
	if (strPath.GetLength() <= 5)
	{
		GetDefaultConfigFile(strPath);
	}
	else
	{
		if (!IsFileExist(strPath))
		{
			GetDefaultConfigFile(strPath);
		}
	}

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void CSttTestDeviceCfg::SaveTestDeviceConfig(const CString &strFile)
{
	CString strPath = strFile;

	if (strPath.GetLength() <= 5)
	{
		GetDefaultConfigFile(strPath);
	}
	else
	{
		if (!IsFileExist(strPath))
		{
			GetDefaultConfigFile(strPath);
		}
	}

	SetDataValue(TEST_DEVICE_CFG_LOCAL_IP,m_strLocalIP, TRUE);
	SetDataValue(TEST_DEVICE_CFG_REMOTE_PORT,m_nRemotePort, TRUE);
	SetDataValue(TEST_DEVICE_CFG_REMOTE_IP,m_strRemoteIP, TRUE);

	SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CSttTestDeviceCfg::InitAfterRead()
{
	GetRemotePort(m_nRemotePort);
	GetRemoteIP(m_strRemoteIP);
	GetLocalIP(m_strLocalIP);
}