//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ExprMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define EXPCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define EXPCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define EXPCLASSID_CPPEXPR       (EXPCLASSID_BASECLASS + 0X00000000)
#define EXPCLASSID_CPPEXPRTYPE       (EXPCLASSID_EXLISTCLASS + 0X00000001)
#define EXPCLASSID_CPPEXPRRCVTYPES       (EXPCLASSID_EXLISTCLASS + 0X00000002)
#define EXPCLASSID_CPPEXPRSENDTYPES       (EXPCLASSID_EXLISTCLASS + 0X00000003)
#define EXPCLASSID_CPPEXPRTYPESMNGR       (EXPCLASSID_EXLISTCLASS + 0X00000004)


#define WM_SENDEXPRESSION				WM_USER + 1853
#define WM_ENABLEEXPRESSION				WM_USER + 1854

class CExprMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CExprMngrXmlRWKeys();
	virtual ~CExprMngrXmlRWKeys();
	static long g_nEXPRef;

public:
	static CExprMngrXmlRWKeys* g_pXmlKeys;
	static CExprMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCPpExprTypesMngrKey; //expr-mngr
	BSTR m_strCPpExprSendTypesKey; //expr-send
	BSTR m_strCPpExprRcvTypesKey; //expr-rcv
	BSTR m_strCPpExprTypeKey; //expr-type
	BSTR m_strCPpExprKey; //expr
	BSTR m_strValueKey;   //key

public:
	static BSTR CPpExprTypesMngrKey()  {   return g_pXmlKeys->m_strCPpExprTypesMngrKey;  }
	static BSTR CPpExprSendTypesKey()  {   return g_pXmlKeys->m_strCPpExprSendTypesKey;  }
	static BSTR CPpExprRcvTypesKey()  {   return g_pXmlKeys->m_strCPpExprRcvTypesKey;  }
	static BSTR CPpExprTypeKey()  {   return g_pXmlKeys->m_strCPpExprTypeKey;  }
	static BSTR CPpExprKey()  {   return g_pXmlKeys->m_strCPpExprKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
};



class CCExprMngrConstGlobal
{
private:
	CCExprMngrConstGlobal();
	virtual ~CCExprMngrConstGlobal();

public:
	static CCExprMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CCExprMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
