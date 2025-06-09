//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CommExprGlobal.cpp

#include "stdafx.h"
#include "CommExprGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CCommExprXmlRWKeys

CCommExprXmlRWKeys* CCommExprXmlRWKeys::g_pXmlKeys = NULL;
long CCommExprXmlRWKeys::g_nMngrRef = 0;


CCommExprXmlRWKeys::CCommExprXmlRWKeys()
{
	m_strCCommExprKey = L"expr";
	m_strValueKey = L"value";
	m_strOptrKey = L"optr";
}

CCommExprXmlRWKeys::~CCommExprXmlRWKeys()
{
}

CCommExprXmlRWKeys* CCommExprXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CCommExprXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CCommExprXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CCommExprConstGlobal

long CCommExprConstGlobal::g_nGlobalRef = 0;
CCommExprConstGlobal* CCommExprConstGlobal::g_pGlobal = NULL;


CCommExprConstGlobal::CCommExprConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CCommExprConstGlobal::~CCommExprConstGlobal()
{
}

CCommExprConstGlobal* CCommExprConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CCommExprConstGlobal();
	}

	return g_pGlobal;
}

void CCommExprConstGlobal::Release()
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
