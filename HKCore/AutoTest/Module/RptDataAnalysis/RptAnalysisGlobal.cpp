//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptAnalysisGlobal.cpp

#include "stdafx.h"
#include "RptAnalysisGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CRptAnalysisXmlRWKeys

CRptAnalysisXmlRWKeys* CRptAnalysisXmlRWKeys::g_pXmlKeys = NULL;
long CRptAnalysisXmlRWKeys::g_nRPTALSRef = 0;


CRptAnalysisXmlRWKeys::CRptAnalysisXmlRWKeys()
{
	m_strCRptDataAlsDefsMngrKey = L"data-defs-mngr";
	m_strCRptDataAlsDefsKey = L"data-defs";
	m_strCRptDataAlsDefKey = L"data-def";
	m_strItem_PathKey = L"item-path";
	m_strId_ValueKey = L"id-value";
}

CRptAnalysisXmlRWKeys::~CRptAnalysisXmlRWKeys()
{
}

CRptAnalysisXmlRWKeys* CRptAnalysisXmlRWKeys::Create()
{
	g_nRPTALSRef++;

	if (g_nRPTALSRef == 1)
	{
		g_pXmlKeys = new CRptAnalysisXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CRptAnalysisXmlRWKeys::Release()
{
	g_nRPTALSRef--;

	if (g_nRPTALSRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CRptAnalysisConstGlobal

long CRptAnalysisConstGlobal::g_nGlobalRef = 0;
CRptAnalysisConstGlobal* CRptAnalysisConstGlobal::g_pGlobal = NULL;


CRptAnalysisConstGlobal::CRptAnalysisConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CRptAnalysisConstGlobal::~CRptAnalysisConstGlobal()
{
}

CRptAnalysisConstGlobal* CRptAnalysisConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CRptAnalysisConstGlobal();
	}

	return g_pGlobal;
}

void CRptAnalysisConstGlobal::Release()
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
