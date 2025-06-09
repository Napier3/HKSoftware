//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDevice_101Global.cpp

#include "stdafx.h"
#include "EpDevice_101Global.h"

//////////////////////////////////////////////////////////////////////////
//CEpDevice_101XmlRWKeys

CEpDevice_101XmlRWKeys* CEpDevice_101XmlRWKeys::g_pXmlKeys = NULL;
long CEpDevice_101XmlRWKeys::g_nEPDRef = 0;


CEpDevice_101XmlRWKeys::CEpDevice_101XmlRWKeys()
{
	m_strCEpDeviceNode101YxKey = L"yx-node";
	m_strCEpDeviceNode101YtKey = L"yt-node";
	m_strCEpDeviceNode101YkKey = L"yk-node";
	m_strCEpDeviceNode101YcKey = L"yc-node";
	m_strCEpDeviceData101YxKey = L"yx";
	m_strCEpDeviceData101YtKey = L"yt";
	m_strCEpDeviceData101YkKey = L"yk";
	m_strCEpDeviceData101YcKey = L"yc";
	m_strCEpDevice101Key = L"device";
	m_strValueKey = L"value";
	m_strMaxKey = L"max";
	m_strMinKey = L"min";
	m_strUnitKey = L"unit";
}

CEpDevice_101XmlRWKeys::~CEpDevice_101XmlRWKeys()
{
}

CEpDevice_101XmlRWKeys* CEpDevice_101XmlRWKeys::Create()
{
	g_nEPDRef++;

	if (g_nEPDRef == 1)
	{
		g_pXmlKeys = new CEpDevice_101XmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEpDevice_101XmlRWKeys::Release()
{
	g_nEPDRef--;

	if (g_nEPDRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpDevice_101ConstGlobal

long CEpDevice_101ConstGlobal::g_nGlobalRef = 0;
CEpDevice_101ConstGlobal* CEpDevice_101ConstGlobal::g_pGlobal = NULL;


CEpDevice_101ConstGlobal::CEpDevice_101ConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CEpDevice_101ConstGlobal::~CEpDevice_101ConstGlobal()
{
}

CEpDevice_101ConstGlobal* CEpDevice_101ConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEpDevice_101ConstGlobal();
	}

	return g_pGlobal;
}

void CEpDevice_101ConstGlobal::Release()
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
