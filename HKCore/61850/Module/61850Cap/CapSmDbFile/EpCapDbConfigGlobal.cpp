//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapDbConfigGlobal.cpp

#include "stdafx.h"
#include "EpCapDbConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CEpCapDbConfigXmlRWKeys

CEpCapDbConfigXmlRWKeys* CEpCapDbConfigXmlRWKeys::g_pXmlKeys = NULL;
long CEpCapDbConfigXmlRWKeys::g_nMngrRef = 0;


CEpCapDbConfigXmlRWKeys::CEpCapDbConfigXmlRWKeys()
{
	m_strCEpCapDbFileAreaKey = L"db-area";
	m_strCEpCapDbFileCfgKey = L"sm-db-file";
	m_strCEpCapDbConfigKey = L"ep-cap-db-config";
	m_strSizeKey = L"size";
	m_strViewKey = L"view";
	m_strFileKey = L"file";
	m_strBeginPosKey = L"begin-pos";
}

CEpCapDbConfigXmlRWKeys::~CEpCapDbConfigXmlRWKeys()
{
}

CEpCapDbConfigXmlRWKeys* CEpCapDbConfigXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CEpCapDbConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEpCapDbConfigXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpCapDbConfigConstGlobal

long CEpCapDbConfigConstGlobal::g_nGlobalRef = 0;
CEpCapDbConfigConstGlobal* CEpCapDbConfigConstGlobal::g_pGlobal = NULL;


CEpCapDbConfigConstGlobal::CEpCapDbConfigConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CEpCapDbConfigConstGlobal::~CEpCapDbConfigConstGlobal()
{
}

CEpCapDbConfigConstGlobal* CEpCapDbConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEpCapDbConfigConstGlobal();
	}

	return g_pGlobal;
}

void CEpCapDbConfigConstGlobal::Release()
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
