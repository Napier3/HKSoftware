//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroMapMngrGlobal.h

#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define MPCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MPCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MPCLASSID_CMACROMAPS       (MPCLASSID_EXLISTCLASS + 0X00000000)
#define MPCLASSID_CMACROMAP       (MPCLASSID_EXLISTCLASS + 0X00000001)
#define MPCLASSID_CPARAMAP       (MPCLASSID_EXLISTCLASS + 0X00000002)
#define MPCLASSID_CVALUEMAP       (MPCLASSID_BASECLASS + 0X00000003)
#define MPCLASSID_CPARAMAPEXPR       (MPCLASSID_EXLISTCLASS + 0X00000004)
#define MPCLASSID_CPARAMAPCAL       (MPCLASSID_BASECLASS + 0X00000005)

class CMacroMapMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CMacroMapMngrXmlRWKeys();
	virtual ~CMacroMapMngrXmlRWKeys();
	static long g_nMPRef;

public:
	static CMacroMapMngrXmlRWKeys* g_pXmlKeys;
	static CMacroMapMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCParaMapCalKey; //para-map-cal
	BSTR m_strCParaMapExprKey; //para-map-expr
	BSTR m_strCValueMapKey; //value-map
	BSTR m_strCParaMapKey; //para-map
	BSTR m_strCMacroMapKey; //macro-map
	BSTR m_strCMacroMapsKey; //macro-maps
	//BSTR m_strMapKey; //map
	BSTR m_strMapNameKey; //mapname
	BSTR m_strMapIDKey; //mapid
	BSTR m_strUseKey; //use
	BSTR m_strCalScriptKey; //cal-scpt
	BSTR m_strExprKey; //expr

public:
	static BSTR CParaMapCalKey()  {   return g_pXmlKeys->m_strCParaMapCalKey;  }
	static BSTR CParaMapExprKey()  {   return g_pXmlKeys->m_strCParaMapExprKey;  }
	static BSTR CValueMapKey()  {   return g_pXmlKeys->m_strCValueMapKey;  }
	static BSTR CParaMapKey()  {   return g_pXmlKeys->m_strCParaMapKey;  }
	static BSTR CMacroMapKey()  {   return g_pXmlKeys->m_strCMacroMapKey;  }
	static BSTR CMacroMapsKey()  {   return g_pXmlKeys->m_strCMacroMapsKey;  }
	//static BSTR MapKey()  {   return g_pXmlKeys->m_strMapKey;  }
	static BSTR MapNameKey()  {   return g_pXmlKeys->m_strMapNameKey;  }
	static BSTR MapIDKey()  {   return g_pXmlKeys->m_strMapIDKey;  }
	static BSTR UseKey()  {   return g_pXmlKeys->m_strUseKey;  }
	static BSTR ExprKey()  {   return g_pXmlKeys->m_strExprKey;  }
};



class CMacroMapMngrConstGlobal
{
private:
	CMacroMapMngrConstGlobal();
	virtual ~CMacroMapMngrConstGlobal();

public:
	static CMacroMapMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CMacroMapMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
