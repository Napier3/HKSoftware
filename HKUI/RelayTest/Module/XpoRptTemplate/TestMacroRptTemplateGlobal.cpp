//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroRptTemplateGlobal.cpp

#include "stdafx.h"
#include "TestMacroRptTemplateGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CTestMacroRptTemplateXmlRWKeys

CTestMacroRptTemplateXmlRWKeys* CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys = NULL;
long CTestMacroRptTemplateXmlRWKeys::g_nMngrRef = 0;


CTestMacroRptTemplateXmlRWKeys::CTestMacroRptTemplateXmlRWKeys()
{
	m_strCRptTemp_ColKey = L"col";
	m_strCRptTemp_RowKey = L"row";
	m_strCRptTemp_CellKey = L"cell";
	m_strCRptTemp_HeadKey = L"head";
	m_strCRptTemp_RowDefKey = L"row-def";
	m_strCRptTemp_RowsDefKey = L"rows-def";
	m_strCRptTemp_ColDefKey = L"col-def";
	m_strCRptTemp_ColsDefKey = L"cols-def";
	m_strCRptTemp_GridDefKey = L"grid-def";
	m_strCRptTemp_TextDefKey = L"text-def";
	m_strCRptTemp_TitleDefKey = L"title-def";
	m_strCRptTemp_ReportsDefKey = L"reports-def";
	m_strCRptTemp_ValueDefKey = L"value-def";
	m_strCRptTemp_ReportDefKey = L"report-def";
	m_strCRptTemp_PngDefKey = L"png-def";
	m_strCRptTemp_TestMacroUiRptDefKey = L"test-macro-ui-rpt-def";
	m_strCRptTemp_ReportTemplateDefKey = L"report-template-def";
	m_strCRptTemp_MacroTestKey = L"macrotest";
	m_strCRptTemp_MacroCharItemsKey = L"macro-char-items";
	m_strCRptTemp_ItemsKey = L"items";
	m_strCRptTemp_GuideBookKey = L"guidebook";
	m_strRpt_TitleKey = L"rpt-title";
	m_strTitle_LevelKey = L"title-level";
	m_strMacro_IdKey = L"macro-id";
	m_strRpt_ModeKey = L"rpt-mode";
	m_strIndexKey = L"index";
	m_strValKey = L"val";
	m_strLevelKey = L"level";
	m_strTextKey = L"text";
	m_strItem_IdKey = L"item-id";
	m_strItem_LevelKey = L"item-level";
	m_strItem_Level_2Key = L"item-level-2";
	m_strItem_Level_3Key = L"item-level-3";
	m_strData_IdKey = L"data-id";
	m_strData1_IdKey = L"data1-id";
	m_strData2_IdKey = L"data2-id";
	m_strData3_IdKey = L"data3-id";
	m_strData4_IdKey = L"data4-id";
	m_strData5_IdKey = L"data5-id";
	m_strData6_IdKey = L"data6-id";
	m_strData_ModeKey = L"data-mode";
	m_strShow_BordersKey = L"show-borders";
	m_strTypeKey = L"type";
	m_strRow_SpanKey = L"row-span";
	m_strCol_SpanKey = L"col-span";
	m_strData_PathKey = L"data-path";
	m_strTextFormatKey = L"text-format";

	m_strCRptTemp_GridKey = L"grid";
	m_strCRptTemp_TextKey = L"text";
	m_strCRptTemp_TitleKey = L"title";
	m_strCRptTemp_ReportsKey = L"reports";
	m_strCRptTemp_ValueKey = L"value";
	m_strCRptTemp_ReportKey = L"report";
	m_strCRptTemp_TestMacroUiRptKey = L"test-macro-ui-rpt";
	m_strCRptTemp_ReportTemplateKey = L"report-template";
	m_strCRptTemp_EnableKey = L"enable";
	m_strCRptTemp_ParaOptrKey = L"para-optr";
	m_strCRptTemp_PngKey = L"png";
	m_strModeKey = L"mode";
	m_strOptrKey = L"optr";
	m_strPrecisionKey = L"precision";
	m_strProcessKey = L"process";
	m_strPngPathKey = L"png-path";

	m_strFontKey = L"font";
	m_strSizeKey = L"size";
	m_strBoldKey = L"bold";
	m_strItemPathKey = L"item-path";
}

CTestMacroRptTemplateXmlRWKeys::~CTestMacroRptTemplateXmlRWKeys()
{
}

CTestMacroRptTemplateXmlRWKeys* CTestMacroRptTemplateXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CTestMacroRptTemplateXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CTestMacroRptTemplateXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CTestMacroRptTemplateConstGlobal

long CTestMacroRptTemplateConstGlobal::g_nGlobalRef = 0;
CTestMacroRptTemplateConstGlobal* CTestMacroRptTemplateConstGlobal::g_pGlobal = NULL;


CTestMacroRptTemplateConstGlobal::CTestMacroRptTemplateConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CTestMacroRptTemplateConstGlobal::~CTestMacroRptTemplateConstGlobal()
{
}

CTestMacroRptTemplateConstGlobal* CTestMacroRptTemplateConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CTestMacroRptTemplateConstGlobal();
	}

	return g_pGlobal;
}

void CTestMacroRptTemplateConstGlobal::Release()
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
