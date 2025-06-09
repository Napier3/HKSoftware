//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmFileDBGlobal.cpp

#include "stdafx.h"
#include "SmFileDBGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CSmFileDBXmlRWKeys

CSmFileDBXmlRWKeys* CSmFileDBXmlRWKeys::g_pXmlKeys = NULL;
long CSmFileDBXmlRWKeys::g_nSMDBRef = 0;


CSmFileDBXmlRWKeys::CSmFileDBXmlRWKeys()
{
	m_strCSmDbFileKey = L"sm-file";
	m_strCSmDbDataExKey = L"sm-data-ex";
	m_strCSmDbTableKey = L"sm-table";
	m_strCSmDbDataKey = L"sm-data";
}

CSmFileDBXmlRWKeys::~CSmFileDBXmlRWKeys()
{
}

CSmFileDBXmlRWKeys* CSmFileDBXmlRWKeys::Create()
{
	g_nSMDBRef++;

	if (g_nSMDBRef == 1)
	{
		g_pXmlKeys = new CSmFileDBXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSmFileDBXmlRWKeys::Release()
{
	g_nSMDBRef--;

	if (g_nSMDBRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSmFileDBConstGlobal

long CSmFileDBConstGlobal::g_nGlobalRef = 0;
CSmFileDBConstGlobal* CSmFileDBConstGlobal::g_pGlobal = NULL;


CSmFileDBConstGlobal::CSmFileDBConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CSmFileDBConstGlobal::~CSmFileDBConstGlobal()
{
}

CSmFileDBConstGlobal* CSmFileDBConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSmFileDBConstGlobal();
	}

	return g_pGlobal;
}

void CSmFileDBConstGlobal::Release()
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
