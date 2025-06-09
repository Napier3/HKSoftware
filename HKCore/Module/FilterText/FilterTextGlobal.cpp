//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterTextGlobal.cpp

#include "stdafx.h"
#include "FilterTextGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CFilterTextXmlRWKeys

CFilterTextXmlRWKeys* CFilterTextXmlRWKeys::g_pXmlKeys = NULL;
long CFilterTextXmlRWKeys::g_nFLTRef = 0;


CFilterTextXmlRWKeys::CFilterTextXmlRWKeys()
{
	m_strCFilterTextMngrKey = L"txt-filter-mngr";
	m_strCFilterTextKey = L"txt-filter";
}

CFilterTextXmlRWKeys::~CFilterTextXmlRWKeys()
{
}

CFilterTextXmlRWKeys* CFilterTextXmlRWKeys::Create()
{
	g_nFLTRef++;

	if (g_nFLTRef == 1)
	{
		g_pXmlKeys = new CFilterTextXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CFilterTextXmlRWKeys::Release()
{
	g_nFLTRef--;

	if (g_nFLTRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

