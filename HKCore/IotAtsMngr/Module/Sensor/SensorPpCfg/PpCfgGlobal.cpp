//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpCfgGlobal.cpp

#include "stdafx.h"
#include "PpCfgGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CPpCfgXmlRWKeys

CPpCfgXmlRWKeys* CPpCfgXmlRWKeys::g_pXmlKeys = NULL;
long CPpCfgXmlRWKeys::g_nPpCfgRef = 0;


CPpCfgXmlRWKeys::CPpCfgXmlRWKeys()
{
	m_strCSensorPpProduceKey = L"pp-produce";
	m_strCSensorPpPraseKey = L"pp-prase";
	m_strCSensorPpDeviceTypeKey = L"device-type";
	m_strCSensorPpConfigKey = L"sensor-pkg-protocol";
}

CPpCfgXmlRWKeys::~CPpCfgXmlRWKeys()
{
}

CPpCfgXmlRWKeys* CPpCfgXmlRWKeys::Create()
{
	g_nPpCfgRef++;

	if (g_nPpCfgRef == 1)
	{
		g_pXmlKeys = new CPpCfgXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CPpCfgXmlRWKeys::Release()
{
	g_nPpCfgRef--;

	if (g_nPpCfgRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CPpCfgConstGlobal

long CPpCfgConstGlobal::g_nGlobalRef = 0;
CPpCfgConstGlobal* CPpCfgConstGlobal::g_pGlobal = NULL;


CPpCfgConstGlobal::CPpCfgConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CPpCfgConstGlobal::~CPpCfgConstGlobal()
{
}

CPpCfgConstGlobal* CPpCfgConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CPpCfgConstGlobal();
	}

	return g_pGlobal;
}

void CPpCfgConstGlobal::Release()
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
