//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBkmkBatchAddGlobal.cpp

#include "stdafx.h"
#include "RptBkmkBatchAddGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CRptBkmkBatchAddXmlRWKeys

CRptBkmkBatchAddXmlRWKeys* CRptBkmkBatchAddXmlRWKeys::g_pXmlKeys = NULL;
long CRptBkmkBatchAddXmlRWKeys::g_nRBARef = 0;


CRptBkmkBatchAddXmlRWKeys::CRptBkmkBatchAddXmlRWKeys()
{
	m_strCRptBkmkBatchCellKey = L"batch-cell";
	m_strCRptBatchConfigKey = L"rpt-batch-config";
	m_strCRptBatchDataMapsKey = L"data-maps";
	m_strCRptBatchDataMapKey = L"data-map";
	m_strCRptBatchItemMapsKey = L"item-maps";
	m_strCRptBatchItemMapKey = L"item-map";
	m_strItemIndexKey = L"item-index";
	m_strMapIndexKey = L"map-index";
	m_strRepeatIndexKey = L"repeat-index";
	m_strDataAttrKey = L"data-attr";
	m_strPrecisionKey = L"precision";
	m_strModeKey = L"mode";
}

CRptBkmkBatchAddXmlRWKeys::~CRptBkmkBatchAddXmlRWKeys()
{
}

CRptBkmkBatchAddXmlRWKeys* CRptBkmkBatchAddXmlRWKeys::Create()
{
	g_nRBARef++;

	if (g_nRBARef == 1)
	{
		g_pXmlKeys = new CRptBkmkBatchAddXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CRptBkmkBatchAddXmlRWKeys::Release()
{
	g_nRBARef--;

	if (g_nRBARef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CRptBkmkBatchAddConstGlobal

long CRptBkmkBatchAddConstGlobal::g_nGlobalRef = 0;
CRptBkmkBatchAddConstGlobal* CRptBkmkBatchAddConstGlobal::g_pGlobal = NULL;


CRptBkmkBatchAddConstGlobal::CRptBkmkBatchAddConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CRptBkmkBatchAddConstGlobal::~CRptBkmkBatchAddConstGlobal()
{
}

CRptBkmkBatchAddConstGlobal* CRptBkmkBatchAddConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CRptBkmkBatchAddConstGlobal();
	}

	return g_pGlobal;
}

void CRptBkmkBatchAddConstGlobal::Release()
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
