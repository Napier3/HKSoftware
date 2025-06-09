//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GlobalDataMngrGlobal.cpp

#include "stdafx.h"
#include "GlobalDataMngrGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CGlobalDataMngrXmlRWKeys

CGlobalDataMngrXmlRWKeys* CGlobalDataMngrXmlRWKeys::g_pXmlKeys = NULL;
long CGlobalDataMngrXmlRWKeys::g_nSTGRef = 0;


CGlobalDataMngrXmlRWKeys::CGlobalDataMngrXmlRWKeys()
{
	m_strCFilterTextMngrKey = L"txt-filter-mngr";
	m_strCFilterTextKey = L"txt-filter";
}

CGlobalDataMngrXmlRWKeys::~CGlobalDataMngrXmlRWKeys()
{
}

CGlobalDataMngrXmlRWKeys* CGlobalDataMngrXmlRWKeys::Create()
{
	g_nSTGRef++;

	if (g_nSTGRef == 1)
	{
		g_pXmlKeys = new CGlobalDataMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CGlobalDataMngrXmlRWKeys::Release()
{
	g_nSTGRef--;

	if (g_nSTGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

