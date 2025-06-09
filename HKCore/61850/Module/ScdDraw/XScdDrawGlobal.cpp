//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecXScdDrawGlobal.cpp

#include "stdafx.h"
#include "XScdDrawGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CXScdDrawXmlRWKeys

CXScdDrawXmlRWKeys* CXScdDrawXmlRWKeys::g_pXmlKeys = NULL;
long CXScdDrawXmlRWKeys::g_nCFGRef = 0;

CXScdDrawXmlRWKeys::CXScdDrawXmlRWKeys()
{
	

}

CXScdDrawXmlRWKeys::~CXScdDrawXmlRWKeys()
{
}

CXScdDrawXmlRWKeys* CXScdDrawXmlRWKeys::Create()
{
	g_nCFGRef++;

	if (g_nCFGRef == 1)
	{
		g_pXmlKeys = new CXScdDrawXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CXScdDrawXmlRWKeys::Release()
{
	g_nCFGRef--;

	if (g_nCFGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CXScdDrawConstGlobal

long CXScdDrawConstGlobal::g_nGlobalRef = 0;
CXScdDrawConstGlobal* CXScdDrawConstGlobal::g_pGlobal = NULL;

long CXScdDrawConstGlobal::m_nOnlyShowUsedSvOutChs = 0;
long CXScdDrawConstGlobal::m_nOnlyShowUsedGsOutChs = 0;

CXScdDrawConstGlobal::CXScdDrawConstGlobal()
{

	//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()
	InitGlobal();
}

CXScdDrawConstGlobal::~CXScdDrawConstGlobal()
{
}

CXScdDrawConstGlobal* CXScdDrawConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CXScdDrawConstGlobal();
	}

	return g_pGlobal;
}

void CXScdDrawConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

BOOL CXScdDrawConstGlobal::OnlyShowUsedSvOutChs()
{
	if (g_nGlobalRef == NULL)
	{
		return FALSE;
	}

	return (g_pGlobal->m_nOnlyShowUsedSvOutChs == 1);
}

BOOL CXScdDrawConstGlobal::OnlyShowUsedGsOutChs()
{
	if (g_nGlobalRef == NULL)
	{
		return FALSE;
	}

	return (g_pGlobal->m_nOnlyShowUsedGsOutChs == 1);
}


void CXScdDrawConstGlobal::SetOnlyShowUsedSvOutChs(long nShow)
{
	if (g_nGlobalRef == NULL)
	{
		return ;
	}

	g_pGlobal->m_nOnlyShowUsedSvOutChs = nShow;
}

void CXScdDrawConstGlobal::SetOnlyShowUsedGsOutChs(long nShow)
{
	if (g_nGlobalRef == NULL)
	{
		return ;
	}

	g_pGlobal->m_nOnlyShowUsedGsOutChs = nShow;
}

void CXScdDrawConstGlobal::InitGlobal()
{

}
//����ȫ�ֳ�����������ʼ��������

//����ȫ�ֳ���������
