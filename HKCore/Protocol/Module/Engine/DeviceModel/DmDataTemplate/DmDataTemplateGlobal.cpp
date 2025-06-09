//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DmDataTemplateGlobal.cpp

#include "stdafx.h"
#include "DmDataTemplateGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CDmDataTemplateXmlRWKeys

CDmDataTemplateXmlRWKeys* CDmDataTemplateXmlRWKeys::g_pXmlKeys = NULL;
long CDmDataTemplateXmlRWKeys::g_nDMDTRef = 0;


CDmDataTemplateXmlRWKeys::CDmDataTemplateXmlRWKeys()
{
	m_strCDmDataTemplateKey = L"dm-template";
	m_strCDmdtNodeDatasKey = L"node-datas";
	m_strCDmdtNodeDataKey = L"data";
	m_strIndexKey = L"index";
	m_strUnitKey = L"Unit";
}

CDmDataTemplateXmlRWKeys::~CDmDataTemplateXmlRWKeys()
{
}

CDmDataTemplateXmlRWKeys* CDmDataTemplateXmlRWKeys::Create()
{
	g_nDMDTRef++;

	if (g_nDMDTRef == 1)
	{
		g_pXmlKeys = new CDmDataTemplateXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CDmDataTemplateXmlRWKeys::Release()
{
	g_nDMDTRef--;

	if (g_nDMDTRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CDmDataTemplateConstGlobal

long CDmDataTemplateConstGlobal::g_nGlobalRef = 0;
CDmDataTemplateConstGlobal* CDmDataTemplateConstGlobal::g_pGlobal = NULL;


CDmDataTemplateConstGlobal::CDmDataTemplateConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CDmDataTemplateConstGlobal::~CDmDataTemplateConstGlobal()
{
}

CDmDataTemplateConstGlobal* CDmDataTemplateConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CDmDataTemplateConstGlobal();
	}

	return g_pGlobal;
}

void CDmDataTemplateConstGlobal::Release()
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
