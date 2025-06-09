//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbConfigGlobal.cpp

#include "stdafx.h"
#include "SmDbConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CSmDbConfigXmlRWKeys

CSmDbConfigXmlRWKeys* CSmDbConfigXmlRWKeys::g_pXmlKeys = NULL;
long CSmDbConfigXmlRWKeys::g_nMngrRef = 0;


CSmDbConfigXmlRWKeys::CSmDbConfigXmlRWKeys()
{
	m_strCEpCapDbFileAreaKey = L"db-area";
	m_strCSmDbFileCfgKey = L"sm-db-file";
	m_strCSmDbConfigKey = L"ep-cap-db-config";
	m_strSizeKey = L"size";
	m_strViewKey = L"view";
	m_strFileKey = L"file";
	m_strBeginPosKey = L"begin-pos";
}

CSmDbConfigXmlRWKeys::~CSmDbConfigXmlRWKeys()
{
}

CSmDbConfigXmlRWKeys* CSmDbConfigXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSmDbConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSmDbConfigXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSmDbConfigConstGlobal

long CSmDbConfigConstGlobal::g_nGlobalRef = 0;
CSmDbConfigConstGlobal* CSmDbConfigConstGlobal::g_pGlobal = NULL;


CSmDbConfigConstGlobal::CSmDbConfigConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CSmDbConfigConstGlobal::~CSmDbConfigConstGlobal()
{
}

CSmDbConfigConstGlobal* CSmDbConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSmDbConfigConstGlobal();
	}

	return g_pGlobal;
}

void CSmDbConfigConstGlobal::Release()
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
