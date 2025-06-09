//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

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

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;
