//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//KeyDbGlobal.cpp

#include "stdafx.h"
#include "KeyDbGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CKeyDbXmlRWKeys

CKeyDbXmlRWKeys* CKeyDbXmlRWKeys::g_pXmlKeys = NULL;
long CKeyDbXmlRWKeys::g_nKDBRef = 0;


CKeyDbXmlRWKeys::CKeyDbXmlRWKeys()
{
	m_strCXKeyMngrKey = L"keys";
	m_strCXKeyMapsKey = L"key-maps";

	m_strCXKeyDBKey = L"key-db";
	m_strCXKeyRefKey = L"key-ref";
	m_strCXKeyGroupBaseKey = L"key-group";
	m_strCXMultiKeyBaseKey = L"multi-key";
	m_strCXMatchKeyBaseKey = L"match-key";
	m_strCXKeyBaseKey = L"key";
	m_strImportanceKey = L"importance";
	m_strArrayIndexKey= L"array-index";
	m_strIsArrayKey = L"array";
	m_strMmsDvmFileKey = L"mms-dvm-file";
	m_strCXMatchConfigKey = L"match-config";
	m_strCXMatchDatasetRefsKey = L"dataset-refs";
	m_strCXMatchDatasetRefKey = L"dataset-ref";
	m_strCXMatchDatarefsKey = L"data-refs";
	m_strCXMatchDatarefKey = L"data-ref";
	m_strSrcPathKey = L"src-path";
	m_strDestPathKey = L"dest-path";
	m_strSrcDatasetPathKey = L"src-dataset-path";
	m_strMinRateKey = L"min-rate";
}

CKeyDbXmlRWKeys::~CKeyDbXmlRWKeys()
{
}

CKeyDbXmlRWKeys* CKeyDbXmlRWKeys::Create()
{
	g_nKDBRef++;

	if (g_nKDBRef == 1)
	{
		g_pXmlKeys = new CKeyDbXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CKeyDbXmlRWKeys::Release()
{
	g_nKDBRef--;

	if (g_nKDBRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CKeyDbConstGlobal

long CKeyDbConstGlobal::g_nGlobalRef = 0;
CKeyDbConstGlobal* CKeyDbConstGlobal::g_pGlobal = NULL;


CKeyDbConstGlobal::CKeyDbConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CKeyDbConstGlobal::~CKeyDbConstGlobal()
{
}

CKeyDbConstGlobal* CKeyDbConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CKeyDbConstGlobal();
	}

	return g_pGlobal;
}

void CKeyDbConstGlobal::Release()
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
