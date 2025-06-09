//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDeviceModelGlobal.cpp

#include "stdafx.h"
#include "EpCapDeviceModelGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CEpCapDeviceModelXmlRWKeys

CEpCapDeviceModelXmlRWKeys* CEpCapDeviceModelXmlRWKeys::g_pXmlKeys = NULL;
long CEpCapDeviceModelXmlRWKeys::g_nECDMRef = 0;


CEpCapDeviceModelXmlRWKeys::CEpCapDeviceModelXmlRWKeys()
{
	m_strCEpCapDeviceModelKey = L"device-model";
	m_strCEcdmProtocolAddrsKey = L"protocol-addrs";
	m_strCEcdmProtocolAddrKey = L"protocol-addr";
	m_strCEcdmDatasKey = L"epoto_datas";
	m_strCEcdmDataKey = L"data";
	m_strUnitKey = L"unit";
	m_strDataTypeKey = L"datatype";
	m_strMinKey = L"min";
	m_strMaxKey = L"max";
	m_strDeadKey = L"dead";
	m_strIndexKey = L"index";
	m_strProtocolKey = L"protocol";
	m_strYxAddrKey = L"yx-addr";
	m_strYcAddrKey = L"yc-addr";
	m_strYtAddrKey = L"yt-addr";
}

CEpCapDeviceModelXmlRWKeys::~CEpCapDeviceModelXmlRWKeys()
{
}

CEpCapDeviceModelXmlRWKeys* CEpCapDeviceModelXmlRWKeys::Create()
{
	g_nECDMRef++;

	if (g_nECDMRef == 1)
	{
		g_pXmlKeys = new CEpCapDeviceModelXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEpCapDeviceModelXmlRWKeys::Release()
{
	g_nECDMRef--;

	if (g_nECDMRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpCapDeviceModelConstGlobal

long CEpCapDeviceModelConstGlobal::g_nGlobalRef = 0;
CEpCapDeviceModelConstGlobal* CEpCapDeviceModelConstGlobal::g_pGlobal = NULL;


CEpCapDeviceModelConstGlobal::CEpCapDeviceModelConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CEpCapDeviceModelConstGlobal::~CEpCapDeviceModelConstGlobal()
{
}

CEpCapDeviceModelConstGlobal* CEpCapDeviceModelConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEpCapDeviceModelConstGlobal();
	}

	return g_pGlobal;
}

void CEpCapDeviceModelConstGlobal::Release()
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
