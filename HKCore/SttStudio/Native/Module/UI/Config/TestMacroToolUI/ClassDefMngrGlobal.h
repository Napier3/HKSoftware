//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ClassDefMngrGlobal.h

#pragma once

#include "../../../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CTESTMACROTOOLBAR       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CTESTMACROGROUP       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CTESTMACROREF       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CCOMMCMDREF       (MngrCLASSID_EXLISTCLASS + 0X00000003)

class CClassDefMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CClassDefMngrXmlRWKeys();
	virtual ~CClassDefMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static CClassDefMngrXmlRWKeys* g_pXmlKeys;
	static CClassDefMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCCommcmdRefKey; //CommcmdRef
	BSTR m_strCTestMacroRefKey; //TestMacroRef
	BSTR m_strCTestMacroGroupKey; //TestMacroGroup
	BSTR m_strCTestMacroToolBarKey; //TestMacroToolBar
	BSTR m_strPicKey; //pic
	BSTR m_strFormatKey; //format
	BSTR m_strValueKey; //value

public:
	static BSTR CCommcmdRefKey()  {   return g_pXmlKeys->m_strCCommcmdRefKey;  }
	static BSTR CTestMacroRefKey()  {   return g_pXmlKeys->m_strCTestMacroRefKey;  }
	static BSTR CTestMacroGroupKey()  {   return g_pXmlKeys->m_strCTestMacroGroupKey;  }
	static BSTR CTestMacroToolBarKey()  {   return g_pXmlKeys->m_strCTestMacroToolBarKey;  }
	static BSTR PicKey()  {   return g_pXmlKeys->m_strPicKey;  }
	static BSTR FormatKey()  {   return g_pXmlKeys->m_strFormatKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
};



class CClassDefMngrConstGlobal
{
private:
	CClassDefMngrConstGlobal();
	virtual ~CClassDefMngrConstGlobal();

public:
	static CClassDefMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CClassDefMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
