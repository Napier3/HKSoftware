//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocCmpGlobal.cpp

#include "stdafx.h"
#include "DocCmpGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CDocCmpXmlRWKeys

CDocCmpXmlRWKeys* CDocCmpXmlRWKeys::g_pXmlKeys = NULL;
long CDocCmpXmlRWKeys::g_nDOCMPRef = 0;

long g_nDocTextUseCdata = 0;
long g_nLogDocCmpProgress = 1;

CDocCmpXmlRWKeys::CDocCmpXmlRWKeys()
{
	m_strCDocGroupKey = L"group";
	m_strCDocCmpKey = L"doc_cmp";
	m_strCDocFileKey = L"doc";
	m_strCDocTableKey = L"table";
	m_strCDocRowKey = L"row";
	m_strCDocCelKey = L"cel";
	m_strCDocTextKey = L"text";
	m_strCmp_IdKey = L"cmp_id";
	m_strTxtKey = L"txt";
	m_strStartKey = L"start";
	m_strEndKey = L"end";
	m_strErrorKey = L"error";
	m_strRowKey = L"row";
	m_strColKey = L"col";
	m_strWidthKey = L"width";
	m_strHeightKey = L"Height";
	m_strTxt_Cmp_IdKey = L"txt_cmp_id";
	m_strMap_IdKey = L"map-id";
	m_strCDocTextValKey = L"txt";

	m_nIsSaveCmpMode = 0;
}

CDocCmpXmlRWKeys::~CDocCmpXmlRWKeys()
{
}

CDocCmpXmlRWKeys* CDocCmpXmlRWKeys::Create()
{
	g_nDOCMPRef++;

	if (g_nDOCMPRef == 1)
	{
		g_pXmlKeys = new CDocCmpXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CDocCmpXmlRWKeys::Release()
{
	g_nDOCMPRef--;

	if (g_nDOCMPRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

BOOL CDocCmpXmlRWKeys::IsSaveCmpMode()
{
	return g_pXmlKeys->m_nIsSaveCmpMode;
}

void CDocCmpXmlRWKeys::SetSaveCmpMode(long nMode)
{
	g_pXmlKeys->m_nIsSaveCmpMode = nMode;
}

//////////////////////////////////////////////////////////////////////////
//CDocCmpConstGlobal

long CDocCmpConstGlobal::g_nGlobalRef = 0;
CDocCmpConstGlobal* CDocCmpConstGlobal::g_pGlobal = NULL;


CDocCmpConstGlobal::CDocCmpConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CDocCmpConstGlobal::~CDocCmpConstGlobal()
{
}

CDocCmpConstGlobal* CDocCmpConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CDocCmpConstGlobal();
	}

	return g_pGlobal;
}

void CDocCmpConstGlobal::Release()
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

long g_nDocCmpIndex = 0;

CString docmp_GenDocCmpID()
{
	CString strCmpID;
	strCmpID.Format(_T("cmp%d"), g_nDocCmpIndex);
	g_nDocCmpIndex++;
	return strCmpID;
}
