//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestCtrrlMacroTestUIMngrGlobal.cpp

#include "stdafx.h"
#include "SttTestCtrrlMacroTestUIMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSttTestCtrrlMacroTestUIMngrXmlRWKeys

CSttTestCtrrlMacroTestUIMngrXmlRWKeys* CSttTestCtrrlMacroTestUIMngrXmlRWKeys::g_pXmlKeys = NULL;
long CSttTestCtrrlMacroTestUIMngrXmlRWKeys::g_nMACROTESTUIMngrRef = 0;


CSttTestCtrrlMacroTestUIMngrXmlRWKeys::CSttTestCtrrlMacroTestUIMngrXmlRWKeys()
{
	m_strCSttMacroTestUI_GroupKey = L"group";
	m_strCSttMacroTestUI_TestMacroUIRefKey = L"test-macro-ui-ref";
	m_strCSttMacroTestUI_TestMacroUIMngrKey = L"test-macro-ui-mngr";
	m_strCSttMacroTestUI_TestMacroUIKey = L"test-macro-ui";
	m_strCSttMacroTestUI_TestMacroUIsKey = L"test-macro-uis";
	m_strCSttMacroTestUI_TestMacroUIDBKey = L"test-macro-ui-db";
	m_strMacro_FileKey = L"macro-file";
	m_strMacro_IdKey = L"macro-id";
	m_strGen_FileKey = L"gen-file";
	m_strGirdFileKey = L"grid-file";
	m_strUi_FileKey = L"ui-file";
	m_strUi_Para_FileKey = L"ui-para-file";
	m_strReport_FileKey = L"report-file";
	m_strHd_Rs_FileKey = L"hd-rs-file";
	m_strCharLib_FileKey = L"charlib-file";
	m_strUi_IdKey = L"ui-id";

	//shaolei 2023-6-20
	m_strRptDataCfgFileKey = L"rpt-data-cfg-file";
	m_strRepeatTimesKey = L"repeat-times";
}

CSttTestCtrrlMacroTestUIMngrXmlRWKeys::~CSttTestCtrrlMacroTestUIMngrXmlRWKeys()
{
}

CSttTestCtrrlMacroTestUIMngrXmlRWKeys* CSttTestCtrrlMacroTestUIMngrXmlRWKeys::Create()
{
	g_nMACROTESTUIMngrRef++;

	if (g_nMACROTESTUIMngrRef == 1)
	{
		g_pXmlKeys = new CSttTestCtrrlMacroTestUIMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttTestCtrrlMacroTestUIMngrXmlRWKeys::Release()
{
	g_nMACROTESTUIMngrRef--;

	if (g_nMACROTESTUIMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSttTestCtrrlMacroTestUIMngrConstGlobal

long CSttTestCtrrlMacroTestUIMngrConstGlobal::g_nGlobalRef = 0;
CSttTestCtrrlMacroTestUIMngrConstGlobal* CSttTestCtrrlMacroTestUIMngrConstGlobal::g_pGlobal = NULL;


CSttTestCtrrlMacroTestUIMngrConstGlobal::CSttTestCtrrlMacroTestUIMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CSttTestCtrrlMacroTestUIMngrConstGlobal::~CSttTestCtrrlMacroTestUIMngrConstGlobal()
{
}

CSttTestCtrrlMacroTestUIMngrConstGlobal* CSttTestCtrrlMacroTestUIMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSttTestCtrrlMacroTestUIMngrConstGlobal();
	}

	return g_pGlobal;
}

void CSttTestCtrrlMacroTestUIMngrConstGlobal::Release()
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
