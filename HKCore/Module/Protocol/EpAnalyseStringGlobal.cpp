//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpAnalyseStringGlobal.cpp

#include "stdafx.h"
#include "EpAnalyseStringGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CEpAnalyseStringXmlRWKeys

CEpAnalyseStringXmlRWKeys* CEpAnalyseStringXmlRWKeys::g_pXmlKeys = NULL;
long CEpAnalyseStringXmlRWKeys::g_nEPASRef = 0;


CEpAnalyseStringXmlRWKeys::CEpAnalyseStringXmlRWKeys()
{
	m_strCEpAnalyseStringValKey = L"ep-string-val";
	m_strCEpAnalyseMngrKey = L"ep-analyse-string";
	m_strCEpAnalyseStringKey = L"ep-string";
	m_strStringKey = L"string";
	m_strValueKey = L"value";
	m_strValue2Key = L"value2";
}

CEpAnalyseStringXmlRWKeys::~CEpAnalyseStringXmlRWKeys()
{
}

CEpAnalyseStringXmlRWKeys* CEpAnalyseStringXmlRWKeys::Create()
{
	g_nEPASRef++;

	if (g_nEPASRef == 1)
	{
		g_pXmlKeys = new CEpAnalyseStringXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEpAnalyseStringXmlRWKeys::Release()
{
	g_nEPASRef--;

	if (g_nEPASRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEpAnalyseStringConstGlobal

long CEpAnalyseStringConstGlobal::g_nGlobalRef = 0;
CEpAnalyseStringConstGlobal* CEpAnalyseStringConstGlobal::g_pGlobal = NULL;


CEpAnalyseStringConstGlobal::CEpAnalyseStringConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CEpAnalyseStringConstGlobal::~CEpAnalyseStringConstGlobal()
{
}

CEpAnalyseStringConstGlobal* CEpAnalyseStringConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEpAnalyseStringConstGlobal();
	}

	return g_pGlobal;
}

void CEpAnalyseStringConstGlobal::Release()
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
