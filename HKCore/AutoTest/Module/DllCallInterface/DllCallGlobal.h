//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DllCallGlobal.h

#pragma once

#include "..\..\..\Module\DataMngr\DataMngrGlobal.h"

#define DLCLCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define DLCLCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define DLCLCLASSID_CDLLFUNCTION       (DLCLCLASSID_EXLISTCLASS + 0X00000000)
#define DLCLCLASSID_CDLLCALL       (DLCLCLASSID_EXLISTCLASS + 0X00000001)
#define DLCLCLASSID_CDLLCALLMNGR       (DLCLCLASSID_EXLISTCLASS + 0X00000002)
#define DLCLCLASSID_CFUNCPARAS       (DLCLCLASSID_EXLISTCLASS + 0X00000003)
#define DLCLCLASSID_CFUNCRESULTS       (DLCLCLASSID_EXLISTCLASS + 0X00000004)

class CDllCallXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CDllCallXmlRWKeys();
	virtual ~CDllCallXmlRWKeys();
	static long g_nDLCLRef;

public:
	static CDllCallXmlRWKeys* g_pXmlKeys;
	static CDllCallXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCFuncResultsKey; //results
	BSTR m_strCFuncParasKey; //paras
	BSTR m_strCDllCallDefMngrKey; //dll-calls
	BSTR m_strCDllCallDefKey; //dll-call
	BSTR m_strCDLLFunctionKey; //func
	BSTR m_strProgidKey; //progid

public:
	static BSTR CFuncResultsKey()  {   return g_pXmlKeys->m_strCFuncResultsKey;  }
	static BSTR CFuncParasKey()  {   return g_pXmlKeys->m_strCFuncParasKey;  }
	static BSTR CDllCallDefMngrKey()  {   return g_pXmlKeys->m_strCDllCallDefMngrKey;  }
	static BSTR CDllCallDefKey()  {   return g_pXmlKeys->m_strCDllCallDefKey;  }
	static BSTR CDLLFunctionKey()  {   return g_pXmlKeys->m_strCDLLFunctionKey;  }
	static BSTR ProgidKey()  {   return g_pXmlKeys->m_strProgidKey;  }
};



class CDllCallConstGlobal
{
private:
	CDllCallConstGlobal();
	virtual ~CDllCallConstGlobal();

public:
	static CDllCallConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CDllCallConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
