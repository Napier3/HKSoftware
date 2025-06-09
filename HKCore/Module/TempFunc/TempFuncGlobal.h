

//TempFuncGlobal.h     
//邵雷
#pragma once

#include "ExBaseList.h"
#include "..\KeyDb\XKeyDB.h"

#define KTFCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define KTFCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define KTFCLASSID_CXTEMPFUNC       (KTFCLASSID_EXLISTCLASS + 0X00000000)
#define KTFCLASSID_CXFUNCBASE       (KTFCLASSID_EXLISTCLASS + 0X00000001)
#define KTFCLASSID_CXKEYSBASE       (KTFCLASSID_EXLISTCLASS + 0X00000002)
#define KTFCLASSID_CXKEYBASE        (KTFCLASSID_EXLISTCLASS + 0X00000003)
#define KTFCLASSID_CXTEMPBASE       (KTFCLASSID_EXLISTCLASS + 0X00000004)
#define KTFCLASSID_CXSCENEBASE      (KTFCLASSID_EXLISTCLASS + 0X00000005)
#define KTFCLASSID_CXFOLDERBASE     (KTFCLASSID_EXLISTCLASS + 0X00000006)
//####################
//为Analyse相关的类，建立ID

class CTempFuncXmlRWFuncs : public CXmlRWKeys
{
protected:
	CTempFuncXmlRWFuncs();
	virtual ~CTempFuncXmlRWFuncs();
	static long g_nTempFuncRef;

public:
	static CTempFuncXmlRWFuncs* g_pXmlFuncs;
	static CTempFuncXmlRWFuncs* Create(CXKeyDB *pXKeyDB);
	static void Release();
	static CXKeyDB* GetXKeyDB();

public:
	BSTR m_strCXTempFuncsTempF;//Templates-Functions
	BSTR m_strCXTempFuncsFunc;//Function
	BSTR m_strCXTempFuncsKeys;//keys
	BSTR m_strCXTempFuncsKey;//key
	BSTR m_strCXTempFuncsTemp;//Template
	BSTR m_strCXTempFuncsScene;//Test-Scene
	BSTR m_strCXTempFuncsFolder;//Folder

	BSTR m_strCXTempFuncsArray;//array

	CXKeyDB *m_pXKeyDB;//模板管理模块使用到的关键字库

public:
	static BSTR CXTempFuncsTempF()  {   return g_pXmlFuncs->m_strCXTempFuncsTempF;  }
	static BSTR CXTempFuncsFunc()  {   return g_pXmlFuncs->m_strCXTempFuncsFunc;  }
	static BSTR CXTempFuncsKeys()  {   return g_pXmlFuncs->m_strCXTempFuncsKeys;  }
	static BSTR CXTempFuncsKey()  {   return g_pXmlFuncs->m_strCXTempFuncsKey;  }
	static BSTR CXTempFuncsTemp()  {   return g_pXmlFuncs->m_strCXTempFuncsTemp;  }
	static BSTR CXTempFuncsScene()   {   return g_pXmlFuncs->m_strCXTempFuncsScene;  }
	static BSTR CXTempFuncsFolder()  {   return g_pXmlFuncs->m_strCXTempFuncsFolder;  }

	static BSTR FuncKeyIsArrayKey()  {   return g_pXmlFuncs->m_strCXTempFuncsArray;  }

};