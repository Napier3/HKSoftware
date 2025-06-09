//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PowerTestSetMapsGlobal.cpp

#include "stdafx.h"
#include "PowerTestSetMapsGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CPowerTestSetMapsXmlRWKeys

CPowerTestSetMapsXmlRWKeys* CPowerTestSetMapsXmlRWKeys::g_pXmlKeys = NULL;
long CPowerTestSetMapsXmlRWKeys::g_nSetMapMngrRef = 0;


CPowerTestSetMapsXmlRWKeys::CPowerTestSetMapsXmlRWKeys()
{
	m_strCSetMapKey = L"set-map";
	m_strCParaMapKey = L"para-map";
	m_strCPowerTestSetMapsKey = L"powertest-set-maps";
	m_strMapKey = L"map";
}

CPowerTestSetMapsXmlRWKeys::~CPowerTestSetMapsXmlRWKeys()
{
}

CPowerTestSetMapsXmlRWKeys* CPowerTestSetMapsXmlRWKeys::Create()
{
	g_nSetMapMngrRef++;

	if (g_nSetMapMngrRef == 1)
	{
		g_pXmlKeys = new CPowerTestSetMapsXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CPowerTestSetMapsXmlRWKeys::Release()
{
	g_nSetMapMngrRef--;

	if (g_nSetMapMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CPowerTestSetMapsConstGlobal

long CPowerTestSetMapsConstGlobal::g_nGlobalRef = 0;
CPowerTestSetMapsConstGlobal* CPowerTestSetMapsConstGlobal::g_pGlobal = NULL;


CPowerTestSetMapsConstGlobal::CPowerTestSetMapsConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CPowerTestSetMapsConstGlobal::~CPowerTestSetMapsConstGlobal()
{
}

CPowerTestSetMapsConstGlobal* CPowerTestSetMapsConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CPowerTestSetMapsConstGlobal();
	}

	return g_pGlobal;
}

void CPowerTestSetMapsConstGlobal::Release()
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
