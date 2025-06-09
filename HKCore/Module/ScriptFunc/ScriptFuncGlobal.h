//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ScriptFuncGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define SFNCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define SFNCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define SFNCLASSID_CSCRIPTFUNCPARA       (SFNCLASSID_BASECLASS + 0X00000000)
#define SFNCLASSID_CSCRIPTFUNC       (SFNCLASSID_EXLISTCLASS + 0X00000001)
#define SFNCLASSID_CSCRIPTFUNCS       (SFNCLASSID_EXLISTCLASS + 0X00000002)

class CScriptFuncXmlRWKeys : public CXmlRWKeys
{
protected:
	CScriptFuncXmlRWKeys();
	virtual ~CScriptFuncXmlRWKeys();
	static long g_nSFNRef;

public:
	static CScriptFuncXmlRWKeys* g_pXmlKeys;
	static CScriptFuncXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCScriptFuncsKey; //funcs
	BSTR m_strCScriptFuncKey; //func
	BSTR m_strCScriptFuncParaKey; //para
	BSTR m_strTypeKey; //type
	BSTR m_strReturnKey; //return
	BSTR m_strTextKey; //text

public:
	static BSTR CScriptFuncsKey()  {   return g_pXmlKeys->m_strCScriptFuncsKey;  }
	static BSTR CScriptFuncKey()  {   return g_pXmlKeys->m_strCScriptFuncKey;  }
	static BSTR CScriptFuncParaKey()  {   return g_pXmlKeys->m_strCScriptFuncParaKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR ReturnKey()  {   return g_pXmlKeys->m_strReturnKey;  }
	static BSTR TextKey()  {   return g_pXmlKeys->m_strTextKey;  }
};



class CScriptFuncConstGlobal
{
private:
	CScriptFuncConstGlobal();
	virtual ~CScriptFuncConstGlobal();

public:
	static CScriptFuncConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CScriptFuncConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
