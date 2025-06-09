//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbItemsGenRuleDefMngrGlobal.cpp

#include "stdafx.h"
#include "GbItemsGenRuleDefMngrGlobal.h"
#include "../../../Module/Expression/XExprGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CGbItemsGenRuleDefMngrXmlRWKeys

CGbItemsGenRuleDefMngrXmlRWKeys* CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys = NULL;
long CGbItemsGenRuleDefMngrXmlRWKeys::g_nGbItemsGenMngrRef = 0;


CGbItemsGenRuleDefMngrXmlRWKeys::CGbItemsGenRuleDefMngrXmlRWKeys()
{
	m_strCItemsGenNodeKey = L"items-gen-node";
	m_strCItemsGenDefineKey = L"items-gen-define";
	m_strCItemsGenDataMapKey = L"data-map";
	m_strCItemsGenDatasetKey = L"dataset";
	m_strCItemsGenNameItemKey = L"name-item";
	m_strCItemsGenNameAddKey = L"name-add";
	m_strCItemsGenParaKey = L"para";
	m_strCItemsGenParaDefKey = L"paras-def";
	m_strCParasGenNodeKey = L"paras-gen-node";
	m_strCItemsGenEnableKey = L"enable";
	m_strCItemsGenDataKey = L"data";
	m_strCItemsGenInterfaceKey = L"interface";
	m_strCItemsGenParasMapKey = L"paras-map";
	m_strCItemsGenInstKey = L"items-gen-inst";
	m_strCItemsGenClassKey = L"items-gen-class";
	m_strCMacroItemsGenKey = L"macro-items-gen";
	m_strCMacroSelfDefGenKey = L"macro-selfdef-gen";
	m_strCGbItemsGenKey = L"gb-items-gen";
	m_strMacro_IdKey = L"macro-id";
	m_strNew_ItemsKey = L"new-items";
	m_strClassKey = L"class";
	m_strData_TypeKey = L"data-type";
	m_strValueKey = L"value";
	m_strModeKey = L"mode";
	m_strTypeKey = L"type";
	m_strFormatKey = L"format";
	m_strTextKey = L"text";
	m_strText_HeadKey = L"text-head";
	m_strText_TailKey = L"text-tail";
	m_strId_DataKey = L"id-data";
	m_strId_MapKey = L"id-map";
	m_strKeepExprKey = L"keepexpr";
	m_strName_HeadKey = L"name-head"; //name-head
	m_strName_TailKey = L"name-tail"; //id-tail
	m_strID_HeadKey = L"id-head"; //id-head
	m_strID_TailKey = L"id-tail"; //id-tail

	//character
	m_strCCharacteristicKey = L"characteristic";
	m_strCMacroCharItemLineDefKey = L"char-item-line";
	m_strCMacroCharItemsKey  = L"macro-char-items";
	m_strAxisModeKey = L"axis-mode";   //Axis mode:x-y; r-angle
	m_strParaIdXbKey = L"x-b";
	m_strParaIdYbKey = L"y-b";
	m_strParaIdXeKey = L"x-e";
	m_strParaIdYeKey = L"y-e";
	m_strParaIdXsetKey = L"x-set";
	m_strParaIdYsetKey = L"y-set";
	m_strParaIdXactKey = L"x-act";
	m_strParaIdYactKey = L"y-act";
	m_strParaIdFlagActKey = L"flag-act";

	m_strParaIdSearchXbKey = L"search-x-b";
	m_strParaIdSearchYbKey = L"search-y-b";
	m_strParaIdSearchActbKey = L"search-actb";
	m_strParaIdSearchXeKey = L"search-x-e";
	m_strParaIdSearchYeKey = L"search-y-e";
	m_strParaIdSearchActeKey = L"search-acte";
	m_strParaIdSearchXcKey = L"search-x-c";
	m_strParaIdSearchYcKey = L"search-y-c";

	m_strCItemRsltExprKey = L"rslt-expr";
	//m_strCItemValueRsltKey = L"value-rslt";
	m_strEngineProgIDKey = L"EngineProgID";
	m_strCItemsGenCommCmdKey = L"commcmd";
	m_strCItemsGenSafetyKey = L"safety";
	m_strCItemsGenSysParaEditKey = L"sysparaedit";
	m_strCmdIDKey = L"cmd-id";
	m_strRwOptrKey = L"rw-optr";
	m_strRptFillDsKey = L"rpt-fill-ds";
}

CGbItemsGenRuleDefMngrXmlRWKeys::~CGbItemsGenRuleDefMngrXmlRWKeys()
{
}

CGbItemsGenRuleDefMngrXmlRWKeys* CGbItemsGenRuleDefMngrXmlRWKeys::Create()
{
	CXExprXmlRWKeys::Create();
	g_nGbItemsGenMngrRef++;

	if (g_nGbItemsGenMngrRef == 1)
	{
		g_pXmlKeys = new CGbItemsGenRuleDefMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CGbItemsGenRuleDefMngrXmlRWKeys::Release()
{
	CXExprXmlRWKeys::Release();
	g_nGbItemsGenMngrRef--;

	if (g_nGbItemsGenMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CGbItemsGenRuleDefMngrConstGlobal

long CGbItemsGenRuleDefMngrConstGlobal::g_nGlobalRef = 0;
CGbItemsGenRuleDefMngrConstGlobal* CGbItemsGenRuleDefMngrConstGlobal::g_pGlobal = NULL;


CGbItemsGenRuleDefMngrConstGlobal::CGbItemsGenRuleDefMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CGbItemsGenRuleDefMngrConstGlobal::~CGbItemsGenRuleDefMngrConstGlobal()
{
}

CGbItemsGenRuleDefMngrConstGlobal* CGbItemsGenRuleDefMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CGbItemsGenRuleDefMngrConstGlobal();
	}

	return g_pGlobal;
}

void CGbItemsGenRuleDefMngrConstGlobal::Release()
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
