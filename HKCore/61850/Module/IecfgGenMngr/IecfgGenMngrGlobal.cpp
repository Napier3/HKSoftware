//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecfgGenMngrGlobal.cpp

#include "stdafx.h"
#include "IecfgGenMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CIecfgGenMngrXmlRWKeys

CIecfgGenMngrXmlRWKeys* CIecfgGenMngrXmlRWKeys::g_pXmlKeys = NULL;
long CIecfgGenMngrXmlRWKeys::g_nGenrateRef = 0;


CIecfgGenMngrXmlRWKeys::CIecfgGenMngrXmlRWKeys()
{
	m_strCIecGenRule_CtrlChKey = L"ch";
	m_strCIecGenCfgDataMngrRule_BaseKey = L"";
	m_strCIecGenCfgChildKeyKey = L"child-key";
	m_strCIecGenCfgKeyKey = L"key";
	m_strCIecGenCfgKeysKey = L"keys";
	m_strCIecGenRule_CtrlBlockKey = L"ctrl-block";
	m_strCIecGenCfgDataMngrRule_GoutKey = L"gout-rule";
	m_strCIecGenCfgDataMngrRule_GinKey = L"gin-rule";
	m_strCIecGenCfgDataMngrRule_SMVKey = L"smv-rule";
	m_strCIecGenCfgDataMngrRuleKey = L"cfg-data-mngr-rule";
	m_strCIecDeviceRuleKey = L"cfg-device-rule";
	m_strCIecGenRuleMngrKey = L"iecfg-gen-mngr";
	m_strNet_DescKey = L"net-desc";
	m_strIecfgKey = L"iecfg";
	m_strGin_Ch_File_NameKey = L"gin-ch-file-name";
	m_strFiber_IndexKey = L"fiber-index";
	m_strMatch_RatioKey = L"match-ratio";
	m_strLogicKey = L"logic";
	m_strApp_ChKey = L"app-ch";
	m_strCh_TypeKey = L"ch-type";
	m_strPhsIDKey = L"phs";
}

CIecfgGenMngrXmlRWKeys::~CIecfgGenMngrXmlRWKeys()
{
}

CIecfgGenMngrXmlRWKeys* CIecfgGenMngrXmlRWKeys::Create()
{
	g_nGenrateRef++;

	if (g_nGenrateRef == 1)
	{
		g_pXmlKeys = new CIecfgGenMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CIecfgGenMngrXmlRWKeys::Release()
{
	g_nGenrateRef--;

	if (g_nGenrateRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CIecfgGenMngrConstGlobal

long CIecfgGenMngrConstGlobal::g_nGlobalRef = 0;
CIecfgGenMngrConstGlobal* CIecfgGenMngrConstGlobal::g_pGlobal = NULL;


CIecfgGenMngrConstGlobal::CIecfgGenMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CIecfgGenMngrConstGlobal::~CIecfgGenMngrConstGlobal()
{
}

CIecfgGenMngrConstGlobal* CIecfgGenMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CIecfgGenMngrConstGlobal();
	}

	return g_pGlobal;
}

void CIecfgGenMngrConstGlobal::Release()
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
