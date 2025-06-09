//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDatasGeneratorGlobal.cpp

#include "stdafx.h"
#include "EpCapDatasGeneratorGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CEpCapDatasGeneratorXmlRWKeys

CEpCapDatasGeneratorXmlRWKeys* CEpCapDatasGeneratorXmlRWKeys::g_pXmlKeys = NULL;
long CEpCapDatasGeneratorXmlRWKeys::g_nECGRef = 0;


CEpCapDatasGeneratorXmlRWKeys::CEpCapDatasGeneratorXmlRWKeys()
{
	m_strCEpCapGenBaseKey = L"";
	m_strCEpCapGenMngrKey = L"gen-mngr";
	m_strCEpCapGenSerialKey = L"gen-serial";
	m_strCEpCapGenUdpKey = L"gen-udp";
	m_strCEpCapGenDatasKey = L"cap-datas";
	m_strCEpCapGenDataKey = L"cap-data";
	m_strCapIDKey = L"cap-id";
	m_strCapTimeKey = L"cap-tm";
	m_strCapMsKey = L"cap-ms";
	m_strAddrSrcKey = L"addr-src";
	m_strAddrDstKey = L"addr-dst";
	m_strTypeKey = L"type";
	m_strDataKey = L"data";
	m_strLocalIPKey = L"local-ip";
	m_strLocalPortKey = L"local-port";
	m_strRemotePortKey = L"remote-port";
	m_strRemoteIPKey = L"remote-ip";
	m_strBaudRateKey = L"baud-rate";
	m_strDataBitKey = L"data-bit";
	m_strStopBitKey = L"stop-bit";
	m_strParityKey = L"parity";
	m_strPortKey = L"port";
	m_strFileKey = L"gen-file";
}

CEpCapDatasGeneratorXmlRWKeys::~CEpCapDatasGeneratorXmlRWKeys()
{
}

CEpCapDatasGeneratorXmlRWKeys* CEpCapDatasGeneratorXmlRWKeys::Create()
{
	g_nECGRef++;

	if (g_nECGRef == 1)
	{
		g_pXmlKeys = new CEpCapDatasGeneratorXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEpCapDatasGeneratorXmlRWKeys::Release()
{
	g_nECGRef--;

	if (g_nECGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpCapDatasGeneratorConstGlobal

long CEpCapDatasGeneratorConstGlobal::g_nGlobalRef = 0;
CEpCapDatasGeneratorConstGlobal* CEpCapDatasGeneratorConstGlobal::g_pGlobal = NULL;


CEpCapDatasGeneratorConstGlobal::CEpCapDatasGeneratorConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CEpCapDatasGeneratorConstGlobal::~CEpCapDatasGeneratorConstGlobal()
{
}

CEpCapDatasGeneratorConstGlobal* CEpCapDatasGeneratorConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEpCapDatasGeneratorConstGlobal();
	}

	return g_pGlobal;
}

void CEpCapDatasGeneratorConstGlobal::Release()
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
