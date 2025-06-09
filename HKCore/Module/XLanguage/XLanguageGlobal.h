//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define LGUGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X000A0000)
#define LGUGCLASSID_EXLISTCLASS     (CLASSID_EXLISTCLASS + 0X000A0000)

#define LGUGCLASSID_CLANGITEM       (LGUGCLASSID_BASECLASS + 0X00000000)
#define LGUGCLASSID_CLANGUAGE       (LGUGCLASSID_EXLISTCLASS + 0X00000001)
#define LGUGCLASSID_CLANGUAGEMNGR   (LGUGCLASSID_EXLISTCLASS + 0X00000002)

#define LGUGCLASSID_WNDBASE         (LGUGCLASSID_BASECLASS   + 0X00000011)
#define LGUGCLASSID_COL             (LGUGCLASSID_EXLISTCLASS + 0X00000012)
#define LGUGCLASSID_COLS            (LGUGCLASSID_EXLISTCLASS + 0X00000013)
#define LGUGCLASSID_FRAME           (LGUGCLASSID_EXLISTCLASS + 0X00000014)
#define LGUGCLASSID_MNGR            (LGUGCLASSID_EXLISTCLASS + 0X00000015)
#define CURRLANGUAGE_RUSSIAN         _T("Russian")
#define CURRLANGUAGE_ENGLISH         _T("English")

class CXLanguageXmlRWKeys : public CXmlRWKeys
{
protected:
	CXLanguageXmlRWKeys();
	virtual ~CXLanguageXmlRWKeys();
	static long g_nLGUGRef;

public:
	static CXLanguageXmlRWKeys* g_pXmlKeys;
	static CXLanguageXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCXLanguageMngrKey; //languages
	BSTR m_strCXLanguageKey; //language
	BSTR m_strCXLangItemKey; //item
	BSTR m_strTranslationKey; //translation
	BSTR m_strCurrLanguageKey; //curr-language
	BSTR m_strSrcTextKey; //translation
	BSTR m_strDebugStateKey; //debug

public:
	static BSTR CXLanguageMngrKey()  {   return g_pXmlKeys->m_strCXLanguageMngrKey;  }
	static BSTR CXLanguageKey()  {   return g_pXmlKeys->m_strCXLanguageKey;  }
	static BSTR CXLangItemKey()  {   return g_pXmlKeys->m_strCXLangItemKey;  }
	static BSTR TranslationKey()  {   return g_pXmlKeys->m_strTranslationKey;  }
	static BSTR CurrLanguageKey()  {   return g_pXmlKeys->m_strCurrLanguageKey;  }
	static BSTR SrcTextKey()  {   return g_pXmlKeys->m_strSrcTextKey;  }
	static BSTR DebugStateKey()  {   return g_pXmlKeys->m_strDebugStateKey;  }
};



class CXLanguageConstGlobal
{
private:
	CXLanguageConstGlobal();
	virtual ~CXLanguageConstGlobal();

public:
	static CXLanguageConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CXLanguageConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
