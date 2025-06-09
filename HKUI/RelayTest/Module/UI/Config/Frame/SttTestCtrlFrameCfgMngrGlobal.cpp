//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestCtrlFrameCfgMngrGlobal.cpp

#include "stdafx.h"
#include "SttTestCtrlFrameCfgMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSttTestCtrlFrameCfgMngrXmlRWKeys

CSttTestCtrlFrameCfgMngrXmlRWKeys* CSttTestCtrlFrameCfgMngrXmlRWKeys::g_pXmlKeys = NULL;
long CSttTestCtrlFrameCfgMngrXmlRWKeys::g_nMngrRef = 0;


CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttTestCtrlFrameCfgMngrXmlRWKeys()
{
	m_strCSttFrame_StatusBarKey = L"status-bar";
	m_strCSttFrame_ResultBarKey = L"result-bar";
	m_strCSttFrame_RightPanesKey = L"right-panes";
	m_strCSttFrame_ReportViewKey = L"report-view";
	m_strCSttFrame_MacroParaViewKey = L"macro-para-view";
	m_strCSttFrame_SizeKey = L"size";
	m_strCSttFrame_GbTreeKey = L"gb-tree";
	m_strCSttFrame_DataKey = L"data";
	m_strCSttFrame_ButtonKey = L"button";
	m_strCSttFrame_PanalKey = L"panal";
	m_strCSttFrame_ToolBarKey = L"tool-bar";
	m_strCSttFrame_ItemKey = L"item";
	m_strCSttFrame_MenuKey = L"menu";
	m_strCSttFrame_MenusKey = L"menus";
	m_strCSttFrame_FontKey = L"font";
	m_strCSttFrameConfigKey = L"frame-config";
	m_strWidthKey = L"width";
	m_strHeightKey = L"height";
	m_strBoldKey = L"bold";
	m_strUseKey = L"use";
	m_strIcon_PosKey = L"icon-pos";
	m_strTypeKey = L"type";
	m_strIconKey = L"icon";
	m_strEnableStateKey = L"enable-state";
	m_strLogDebugInforKey = L"log-debug-infor";
	m_strFrameBtnGapKey = L"frame-btn-gap";
	m_strSelMacroShow=L"sel-macro-show";

	m_strCSttFrame_GlobalDataKey = L"global-data";
	m_strCSttFrame_GlobalDatasKey = L"global-datas";
	m_strData_TypeKey = L"data-type";
	m_strValueKey = L"value";
	
	m_strMacro_UseKey = L"macro-use";
}

CSttTestCtrlFrameCfgMngrXmlRWKeys::~CSttTestCtrlFrameCfgMngrXmlRWKeys()
{
}

CSttTestCtrlFrameCfgMngrXmlRWKeys* CSttTestCtrlFrameCfgMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSttTestCtrlFrameCfgMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttTestCtrlFrameCfgMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSttTestCtrlFrameCfgMngrConstGlobal

long CSttTestCtrlFrameCfgMngrConstGlobal::g_nGlobalRef = 0;
CSttTestCtrlFrameCfgMngrConstGlobal* CSttTestCtrlFrameCfgMngrConstGlobal::g_pGlobal = NULL;


CSttTestCtrlFrameCfgMngrConstGlobal::CSttTestCtrlFrameCfgMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CSttTestCtrlFrameCfgMngrConstGlobal::~CSttTestCtrlFrameCfgMngrConstGlobal()
{
}

CSttTestCtrlFrameCfgMngrConstGlobal* CSttTestCtrlFrameCfgMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSttTestCtrlFrameCfgMngrConstGlobal();
	}

	return g_pGlobal;
}

void CSttTestCtrlFrameCfgMngrConstGlobal::Release()
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
