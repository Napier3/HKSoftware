//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ScriptFuncGlobal.cpp

#include "stdafx.h"
#include "ScriptFuncGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CScriptFuncXmlRWKeys

CScriptFuncXmlRWKeys* CScriptFuncXmlRWKeys::g_pXmlKeys = NULL;
long CScriptFuncXmlRWKeys::g_nSFNRef = 0;


CScriptFuncXmlRWKeys::CScriptFuncXmlRWKeys()
{
	m_strCScriptFuncsKey = L"funcs";
	m_strCScriptFuncKey = L"func";
	m_strCScriptFuncParaKey = L"para";
	m_strTypeKey = L"type";
	m_strReturnKey = L"return";
	m_strTextKey = L"text";
}

CScriptFuncXmlRWKeys::~CScriptFuncXmlRWKeys()
{
}

CScriptFuncXmlRWKeys* CScriptFuncXmlRWKeys::Create()
{
	g_nSFNRef++;

	if (g_nSFNRef == 1)
	{
		g_pXmlKeys = new CScriptFuncXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CScriptFuncXmlRWKeys::Release()
{
	g_nSFNRef--;

	if (g_nSFNRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CScriptFuncConstGlobal

long CScriptFuncConstGlobal::g_nGlobalRef = 0;
CScriptFuncConstGlobal* CScriptFuncConstGlobal::g_pGlobal = NULL;


CScriptFuncConstGlobal::CScriptFuncConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CScriptFuncConstGlobal::~CScriptFuncConstGlobal()
{
}

CScriptFuncConstGlobal* CScriptFuncConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CScriptFuncConstGlobal();
	}

	return g_pGlobal;
}

void CScriptFuncConstGlobal::Release()
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
