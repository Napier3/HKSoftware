//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpPrjGlobal.cpp

#include "stdafx.h"
#include "PpPrjGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CPpPrjXmlRWKeys

CPpPrjXmlRWKeys* CPpPrjXmlRWKeys::g_pXmlKeys = NULL;
long CPpPrjXmlRWKeys::g_nMngrRef = 0;


CPpPrjXmlRWKeys::CPpPrjXmlRWKeys()
{
	m_strCPpPrjDeviceKey = L"device";
	m_strCPpPrjDevicesKey = L"devices";
	m_strTemplate_FileKey = L"template-file";
	m_strDdvm_FileKey = L"ddvm-file";
}

CPpPrjXmlRWKeys::~CPpPrjXmlRWKeys()
{
}

CPpPrjXmlRWKeys* CPpPrjXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CPpPrjXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CPpPrjXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CPpPrjConstGlobal

long CPpPrjConstGlobal::g_nGlobalRef = 0;
CPpPrjConstGlobal* CPpPrjConstGlobal::g_pGlobal = NULL;


CPpPrjConstGlobal::CPpPrjConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CPpPrjConstGlobal::~CPpPrjConstGlobal()
{
}

CPpPrjConstGlobal* CPpPrjConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CPpPrjConstGlobal();
	}

	return g_pGlobal;
}

void CPpPrjConstGlobal::Release()
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
