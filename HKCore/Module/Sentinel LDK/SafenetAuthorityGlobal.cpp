//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SafenetAuthorityGlobal.cpp

#include "stdafx.h"
#include "SafenetAuthorityGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CSafenetAuthorityXmlRWKeys

CSafenetAuthorityXmlRWKeys* CSafenetAuthorityXmlRWKeys::g_pXmlKeys = NULL;
long CSafenetAuthorityXmlRWKeys::g_nMngrRef = 0;


CSafenetAuthorityXmlRWKeys::CSafenetAuthorityXmlRWKeys()
{
	m_strCSafenetAuthoritysMngrKey = L"authoritys-mngr";
	m_strCSafenetAuthoritysKey = L"authoritys";
	m_strCSafenetAuthorityKey = L"authority";
	m_strAuthorityTypeKey = L"type";
	m_strEnableKey = L"enable";
}

CSafenetAuthorityXmlRWKeys::~CSafenetAuthorityXmlRWKeys()
{
}

CSafenetAuthorityXmlRWKeys* CSafenetAuthorityXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSafenetAuthorityXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSafenetAuthorityXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}
