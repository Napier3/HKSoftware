//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXMainConfigGlobal.cpp

#include "stdafx.h"
#include "SttXMainConfigGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

double g_dUIShowCoef = 1.0f; // 界面显示缩放比例
//////////////////////////////////////////////////////////////////////////
//CSttXMainConfigXmlRWKeys

CSttXMainConfigXmlRWKeys* CSttXMainConfigXmlRWKeys::g_pXmlKeys = NULL;
long CSttXMainConfigXmlRWKeys::g_nMngrRef = 0;


CSttXMainConfigXmlRWKeys::CSttXMainConfigXmlRWKeys()
{
	m_strCSttXuiDataBaseKey = L"";
	m_strCSttXuiDataTabsKey = L"tabs";
	m_strCSttXuiDataFileTypeKey = L"file-type";
	m_strCSttXuiDataFileTypesKey = L"file-types";
	m_strCSttXuiDataFileMngrGridKey = L"file-mngr-grid";
	m_strCSttXuiDataCmdKey = L"cmd";
	m_strCSttXuiDataButtonKey = L"button";
	m_strCSttXuiDataBtnsGroupKey = L"btns-group";
	m_strCSttXuiDataTestBtnsGroupKey = L"test-btns-group";
	m_strCSttXuiDataTextKey = L"text";
	m_strCSttXuiDataTabKey = L"tab";
	m_strCSttXuiDataFontKey = L"font";
	m_strCSttXuiDataGlobalKey = L"global";
	m_strCSttXuiDataMainConfigKey = L"main";
	m_strVersionKey = L"version";
	m_strTitleKey = L"title";
	m_strPicKey = L"pic";
	m_strCxKey = L"cx";
	m_strCyKey = L"cy";
	m_StrShowBatteryBtnKey = L"showBatteryBtn";
	m_strStartupDelayTimeKey = L"startup-delaytime";
	m_strCr_BackKey = L"cr-back";
	m_strCr_TextKey = L"cr-text";
	m_strSizeKey = L"size";
	m_strFontKey = L"font";
	m_strTextKey = L"text";
	m_strXKey = L"x";
	m_strYKey = L"y";
	m_strInsetKey = L"inset";
	m_strFromKey = L"from";
	m_strTypeKey = L"type";
	m_strData_SrcKey = L"data-src";
	m_strEmit_ModeKey = L"emit-mode";
	m_strRootKey = L"root";
	m_strArgvKey = L"argv";
}

CSttXMainConfigXmlRWKeys::~CSttXMainConfigXmlRWKeys()
{
}

CSttXMainConfigXmlRWKeys* CSttXMainConfigXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSttXMainConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttXMainConfigXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSttXMainConfigConstGlobal

long CSttXMainConfigConstGlobal::g_nGlobalRef = 0;
CSttXMainConfigConstGlobal* CSttXMainConfigConstGlobal::g_pGlobal = NULL;


CSttXMainConfigConstGlobal::CSttXMainConfigConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CSttXMainConfigConstGlobal::~CSttXMainConfigConstGlobal()
{
}

CSttXMainConfigConstGlobal* CSttXMainConfigConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSttXMainConfigConstGlobal();
	}

	return g_pGlobal;
}

void CSttXMainConfigConstGlobal::Release()
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
