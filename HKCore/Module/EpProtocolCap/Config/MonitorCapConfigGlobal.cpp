//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MonitorCapConfigGlobal.cpp

#include "stdafx.h"
#include "MonitorCapConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CMonitorCapConfigXmlRWKeys

CMonitorCapConfigXmlRWKeys* CMonitorCapConfigXmlRWKeys::g_pXmlKeys = NULL;
long CMonitorCapConfigXmlRWKeys::g_nEMCRef = 0;


CMonitorCapConfigXmlRWKeys::CMonitorCapConfigXmlRWKeys()
{
	m_strCEmcDeviceModelFileKey = L"dvm-file";
	m_strCEmcDeviceModelFilesKey = L"dvm-files";
	m_strCEmcQueryProtocolsKey = L"protocols";
	m_strCEmcQueryProtocolKey = L"protocol";
	m_strCEmcQueryAddrDirKey = L"dir";
	m_strCEmcQueryAddrMapKey = L"addr-map";
	m_strCEmcNetDeviceKey = L"net-device";
	m_strCEmcNetDevicesKey = L"net-devices";
	m_strCEmcNetConfigKey = L"net";
	m_strCEmcNetsConfigKey = L"nets";
	m_strCEmcSerialConfigKey = L"serial";
	m_strCEmcSerialsConfigKey = L"serials";
	m_strCMonitorCapConfigKey = L"ep-cap-config";
	m_strProtocolKey = L"protocol";
	m_strPortKey = L"port";
	m_strBaudRateKey = L"baud-rate";
	m_strByteSizeKey = L"byte-size";
	m_strStopBitsKey = L"stop-bits";
	m_strParityKey = L"parity";
	m_strProtocolKey = L"protocol";
	m_strUDPKey = L"UDP";
	m_strTCPKey = L"TCP";
	m_strOtherKey = L"Other";
	m_strSrcKey = L"src";
	m_strDestKey = L"dest";
	m_strDirKey = L"dir";
	m_strUseGeneratorKey = L"use-generator";
	m_strDvmFileKey = L"dvm-file";
	m_strCEpCapYcAnalysisMngrKey = L"analysis-mngr";
	m_strCEpCapYcAnalysisKey = L"yc-analysis";
	m_strCEpCapYcAnalysisItemKey = L"item";
	m_strItemIndexKey = L"item-index";
	m_strProtocolKey = L"protocol";
	m_strColorKey = L"color";
	m_strDrawTypeKey = L"draw-type";
	m_strFileKey = L"file";
}

CMonitorCapConfigXmlRWKeys::~CMonitorCapConfigXmlRWKeys()
{
}

CMonitorCapConfigXmlRWKeys* CMonitorCapConfigXmlRWKeys::Create()
{
	g_nEMCRef++;

	if (g_nEMCRef == 1)
	{
		g_pXmlKeys = new CMonitorCapConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CMonitorCapConfigXmlRWKeys::Release()
{
	g_nEMCRef--;

	if (g_nEMCRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CMonitorCapConfigConstGlobal

long CMonitorCapConfigConstGlobal::g_nGlobalRef = 0;
CMonitorCapConfigConstGlobal* CMonitorCapConfigConstGlobal::g_pGlobal = NULL;


CMonitorCapConfigConstGlobal::CMonitorCapConfigConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CMonitorCapConfigConstGlobal::~CMonitorCapConfigConstGlobal()
{
}

CMonitorCapConfigConstGlobal* CMonitorCapConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CMonitorCapConfigConstGlobal();
	}

	return g_pGlobal;
}

void CMonitorCapConfigConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;
