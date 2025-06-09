//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StringMatchMapGlobal.cpp

#include "stdafx.h"
#include "StringMatchMapGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CStringMatchMapXmlRWKeys

CStringMatchMapXmlRWKeys* CStringMatchMapXmlRWKeys::g_pXmlKeys = NULL;
long CStringMatchMapXmlRWKeys::g_nSMMRef = 0;


CStringMatchMapXmlRWKeys::CStringMatchMapXmlRWKeys()
{
	m_strCSmmRefGroupKeysKey = L"ref-group-keys";
	m_strCSmmGroupKeysKey = L"group-keys";
	m_strCSmmMacthToolKey = L"";
	m_strCSmmRefGroupKeyKey = L"ref-group-key";
	m_strCSmmRefKeyKey = L"ref-key";
	m_strCSmmKeyMngrKey = L"key-mngr";
	m_strCSmmMultiKeyKey = L"multi-key";
	m_strCSmmGroupKeyKey = L"group-key";
	m_strCSmmKeyKey = L"key";
	m_strIndexKey = L"index";
	m_strTypeKey = L"type";
}

CStringMatchMapXmlRWKeys::~CStringMatchMapXmlRWKeys()
{
}

CStringMatchMapXmlRWKeys* CStringMatchMapXmlRWKeys::Create()
{
	g_nSMMRef++;

	if (g_nSMMRef == 1)
	{
		g_pXmlKeys = new CStringMatchMapXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CStringMatchMapXmlRWKeys::Release()
{
	g_nSMMRef--;

	if (g_nSMMRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CStringMatchMapConstGlobal

long CStringMatchMapConstGlobal::g_nGlobalRef = 0;
CStringMatchMapConstGlobal* CStringMatchMapConstGlobal::g_pGlobal = NULL;


CStringMatchMapConstGlobal::CStringMatchMapConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CStringMatchMapConstGlobal::~CStringMatchMapConstGlobal()
{
}

CStringMatchMapConstGlobal* CStringMatchMapConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CStringMatchMapConstGlobal();
	}

	return g_pGlobal;
}

void CStringMatchMapConstGlobal::Release()
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
