//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpDeviceGlobal.cpp

#include "stdafx.h"
#include "EpDeviceGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CEpDeviceXmlRWKeys

CEpDeviceXmlRWKeys* CEpDeviceXmlRWKeys::g_pXmlKeys = NULL;
long CEpDeviceXmlRWKeys::g_nEPDRef = 0;


CEpDeviceXmlRWKeys::CEpDeviceXmlRWKeys()
{
	m_strCEpDeviceDataKey = L"data";
	m_strCEpDeviceNodeKey = L"node";
	m_strCEpDeviceKey = L"device";
	m_strUsedKey = L"use";
}

CEpDeviceXmlRWKeys::~CEpDeviceXmlRWKeys()
{
}

CEpDeviceXmlRWKeys* CEpDeviceXmlRWKeys::Create()
{
	g_nEPDRef++;

	if (g_nEPDRef == 1)
	{
		g_pXmlKeys = new CEpDeviceXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEpDeviceXmlRWKeys::Release()
{
	g_nEPDRef--;

	if (g_nEPDRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpDeviceConstGlobal

long CEpDeviceConstGlobal::g_nGlobalRef = 0;
CEpDeviceConstGlobal* CEpDeviceConstGlobal::g_pGlobal = NULL;


CEpDeviceConstGlobal::CEpDeviceConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CEpDeviceConstGlobal::~CEpDeviceConstGlobal()
{
}

CEpDeviceConstGlobal* CEpDeviceConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEpDeviceConstGlobal();
	}

	return g_pGlobal;
}

void CEpDeviceConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;
