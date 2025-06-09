//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CommExprGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CCOMMEXPR       (MngrCLASSID_EXLISTCLASS + 0X00000000)

class CCommExprXmlRWKeys : public CXmlRWKeys
{
protected:
	CCommExprXmlRWKeys();
	virtual ~CCommExprXmlRWKeys();
	static long g_nMngrRef;

public:
	static CCommExprXmlRWKeys* g_pXmlKeys;
	static CCommExprXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCCommExprKey; //expr
	BSTR m_strValueKey; //value
	BSTR m_strOptrKey; //optr

public:
	static BSTR CCommExprKey()  {   return g_pXmlKeys->m_strCCommExprKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR OptrKey()  {   return g_pXmlKeys->m_strOptrKey;  }
};



class CCommExprConstGlobal
{
private:
	CCommExprConstGlobal();
	virtual ~CCommExprConstGlobal();

public:
	static CCommExprConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CCommExprConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
