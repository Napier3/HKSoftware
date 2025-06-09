//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapConfigGlobal.cpp

#include "stdafx.h"
#include "EpCapConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CEpCapConfigXmlRWKeys

CEpCapConfigXmlRWKeys* CEpCapConfigXmlRWKeys::g_pXmlKeys = NULL;
long CEpCapConfigXmlRWKeys::g_nECRef = 0;


CEpCapConfigXmlRWKeys::CEpCapConfigXmlRWKeys()
{
	m_strCEpCapNetCardKey = L"net-card";
	m_strCEpCapSerialDeviceKey = L"device";
	m_strCEpCapSerialGroupKey = L"group";
	m_strCEpCapSerialConfigKey = L"serial-config";
	m_strCEpCapDirKey = L"dir";
	m_strCEpCapDirsKey = L"dirs";
	m_strCEpCapNetDeviceKey = L"device";
	m_strCEpCapNetGroupKey = L"group";
	m_strCEpCapNetConfigKey = L"net-config";
	m_strCEpCapConfigKey = L"ep-cap-config";
	m_strFileKey = L"file";
	m_strTcpKey = L"tcp";
	m_strUdpKey = L"udp";
	m_strIndexKey = L"index";
	m_strIPKey = L"ip";
	m_strProtocolKey = L"protocol";
	m_strValueKey = L"value";
	m_strIndex1Key = L"index1";
	m_strIndex2Key = L"index2";
	m_strComIDKey = L"com-id";
}

CEpCapConfigXmlRWKeys::~CEpCapConfigXmlRWKeys()
{
}

CEpCapConfigXmlRWKeys* CEpCapConfigXmlRWKeys::Create()
{
	g_nECRef++;

	if (g_nECRef == 1)
	{
		g_pXmlKeys = new CEpCapConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEpCapConfigXmlRWKeys::Release()
{
	g_nECRef--;

	if (g_nECRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpCapConfigConstGlobal

long CEpCapConfigConstGlobal::g_nGlobalRef = 0;
CEpCapConfigConstGlobal* CEpCapConfigConstGlobal::g_pGlobal = NULL;


CEpCapConfigConstGlobal::CEpCapConfigConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CEpCapConfigConstGlobal::~CEpCapConfigConstGlobal()
{
}

CEpCapConfigConstGlobal* CEpCapConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEpCapConfigConstGlobal();
	}

	return g_pGlobal;
}

void CEpCapConfigConstGlobal::Release()
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
