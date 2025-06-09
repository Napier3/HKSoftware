//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGlobalDataMngrGlobal.cpp

#include "stdafx.h"
#include "IecGlobalDataMngrGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CIecGlobalDataMngrXmlRWKeys

CIecGlobalDataMngrXmlRWKeys* CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys = NULL;
long CIecGlobalDataMngrXmlRWKeys::g_nSTGRef = 0;


CIecGlobalDataMngrXmlRWKeys::CIecGlobalDataMngrXmlRWKeys()
{
	m_strCIecGooseChDataTypeMngrKey = L"gs-ch-data-type-mngr";
	m_strCIecSmvChDataTypeKey = L"smv-data-type";
	m_strCDataTypeMngrKey = L"data-type-mngr";
	m_strCDataTypeKey = L"data-type";
	m_strCDataTypeValueKey = L"value";
	m_strCIecFilterTextMngrKey = L"txt-filter-mngr";
	m_strCIecFilterTextKey = L"txt-filter";
	m_strIndexKey = L"index";
}

CIecGlobalDataMngrXmlRWKeys::~CIecGlobalDataMngrXmlRWKeys()
{
}

CIecGlobalDataMngrXmlRWKeys* CIecGlobalDataMngrXmlRWKeys::Create()
{
	g_nSTGRef++;

	if (g_nSTGRef == 1)
	{
		g_pXmlKeys = new CIecGlobalDataMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CIecGlobalDataMngrXmlRWKeys::Release()
{
	g_nSTGRef--;

	if (g_nSTGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

