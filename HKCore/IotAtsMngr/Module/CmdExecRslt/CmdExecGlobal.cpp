//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CmdExecGlobal.cpp

#include "stdafx.h"
#include "CmdExecGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CCmdExecXmlRWKeys

CCmdExecXmlRWKeys* CCmdExecXmlRWKeys::g_pXmlKeys = NULL;
long CCmdExecXmlRWKeys::g_nMngrRef = 0;


CCmdExecXmlRWKeys::CCmdExecXmlRWKeys()
{
	m_strCExecResultKey = L"rslt";
	m_strCCmdExecRsltKey = L"cmd-exec-rslt";
}

CCmdExecXmlRWKeys::~CCmdExecXmlRWKeys()
{
}

CCmdExecXmlRWKeys* CCmdExecXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CCmdExecXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CCmdExecXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CCmdExecConstGlobal

long CCmdExecConstGlobal::g_nGlobalRef = 0;
CCmdExecConstGlobal* CCmdExecConstGlobal::g_pGlobal = NULL;


CCmdExecConstGlobal::CCmdExecConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CCmdExecConstGlobal::~CCmdExecConstGlobal()
{
}

CCmdExecConstGlobal* CCmdExecConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CCmdExecConstGlobal();
	}

	return g_pGlobal;
}

void CCmdExecConstGlobal::Release()
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
