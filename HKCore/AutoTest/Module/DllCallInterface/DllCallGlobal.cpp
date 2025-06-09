//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DllCallGlobal.cpp

#include "stdafx.h"
#include "DllCallGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CDllCallXmlRWKeys

CDllCallXmlRWKeys* CDllCallXmlRWKeys::g_pXmlKeys = NULL;
long CDllCallXmlRWKeys::g_nDLCLRef = 0;


CDllCallXmlRWKeys::CDllCallXmlRWKeys()
{
	m_strCFuncResultsKey = L"results";
	m_strCFuncParasKey = L"paras";
	m_strCDllCallDefMngrKey = L"dll-calls";
	m_strCDllCallDefKey = L"dll-call";
	m_strCDLLFunctionKey = L"func";
	m_strProgidKey = L"progid";
}

CDllCallXmlRWKeys::~CDllCallXmlRWKeys()
{
}

CDllCallXmlRWKeys* CDllCallXmlRWKeys::Create()
{
	g_nDLCLRef++;

	if (g_nDLCLRef == 1)
	{
		g_pXmlKeys = new CDllCallXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CDllCallXmlRWKeys::Release()
{
	g_nDLCLRef--;

	if (g_nDLCLRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CDllCallConstGlobal

long CDllCallConstGlobal::g_nGlobalRef = 0;
CDllCallConstGlobal* CDllCallConstGlobal::g_pGlobal = NULL;


CDllCallConstGlobal::CDllCallConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CDllCallConstGlobal::~CDllCallConstGlobal()
{
}

CDllCallConstGlobal* CDllCallConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CDllCallConstGlobal();
	}

	return g_pGlobal;
}

void CDllCallConstGlobal::Release()
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
