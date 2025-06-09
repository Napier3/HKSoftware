//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroScriptMngrGlobal.h

#pragma once
#include "../DataMngr/ShortData.h"
#include "../TestMacro/TestMacro.h"

#include "../BaseClass/ExBaseList.h"

#define TMSCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00040000)
#define TMSCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00040000)

#define MCSCLASSID_CTMSCPTCMD       (TMSCLASSID_BASECLASS + 0X00000000)
#define MCSCLASSID_CTMSCPTVALUE       (TMSCLASSID_EXLISTCLASS + 0X00000001)
#define MCSCLASSID_CTMSCPTDATA       (TMSCLASSID_EXLISTCLASS + 0X00000002)
#define MCSCLASSID_CTESTMACROSCRIPT       (TMSCLASSID_EXLISTCLASS + 0X00000003)
#define MCSCLASSID_CTESTMACROSCRIPTMNGR       (TMSCLASSID_EXLISTCLASS + 0X00000004)
#define TMSCLASSID_CTMSCPTGROUPCMD       (TMSCLASSID_BASECLASS + 0X00000005)
#define TMSCLASSID_CGBUIMACROCONFIG       (TMSCLASSID_EXLISTCLASS + 0X00000006)
#define TMSCLASSID_CGBUIMACRO       (TMSCLASSID_BASECLASS + 0X00000007)

class CMacroScriptMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CMacroScriptMngrXmlRWKeys();
	virtual ~CMacroScriptMngrXmlRWKeys();
	static long g_nTMSRef;

public:
	static CMacroScriptMngrXmlRWKeys* g_pXmlKeys;
	static CMacroScriptMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCGbUIMacroKey; //macro
	BSTR m_strCGbUIMacroConfigKey; //gbui-macro-config
	BSTR m_strCTmScptGroupCmdKey; //gcmd
	BSTR m_strCTestMacroScriptMngrKey; //macro-scripts
	BSTR m_strCTestMacroScriptKey; //macro-script
	BSTR m_strCTmScptDataKey; //data
	BSTR m_strCTmScptValueKey; //value
	BSTR m_strCTmScptCmdKey; //cmd
	BSTR m_strDataIDKey; //data-id
	BSTR m_strAttrIDKey; //attr-id
	BSTR m_strValueKey; //Val
	BSTR m_strMacroIDKey; //macro-id
	BSTR m_strGroupIDKey; //group-id
	BSTR m_strDLLKey; //dll

public:
	static BSTR CGbUIMacroKey()  {   return g_pXmlKeys->m_strCGbUIMacroKey;  }
	static BSTR CGbUIMacroConfigKey()  {   return g_pXmlKeys->m_strCGbUIMacroConfigKey;  }
	static BSTR CTmScptGroupCmdKey()  {   return g_pXmlKeys->m_strCTmScptGroupCmdKey;  }
	static BSTR CTestMacroScriptMngrKey()  {   return g_pXmlKeys->m_strCTestMacroScriptMngrKey;  }
	static BSTR CTestMacroScriptKey()  {   return g_pXmlKeys->m_strCTestMacroScriptKey;  }
	static BSTR CTmScptDataKey()  {   return g_pXmlKeys->m_strCTmScptDataKey;  }
	static BSTR CTmScptValueKey()  {   return g_pXmlKeys->m_strCTmScptValueKey;  }
	static BSTR CTmScptCmdKey()  {   return g_pXmlKeys->m_strCTmScptCmdKey;  }
	static BSTR DataIDKey()  {   return g_pXmlKeys->m_strDataIDKey;  }
	static BSTR AttrIDKey()  {   return g_pXmlKeys->m_strAttrIDKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR MacroIDKey()  {   return g_pXmlKeys->m_strMacroIDKey;  }
	static BSTR GroupIDKey()  {   return g_pXmlKeys->m_strGroupIDKey;  }
	static BSTR DLLKey()  {   return g_pXmlKeys->m_strDLLKey;  }
};



class CMacroScriptMngrConstGlobal
{
private:
	CMacroScriptMngrConstGlobal();
	virtual ~CMacroScriptMngrConstGlobal();

public:
	static CMacroScriptMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CMacroScriptMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

BOOL TMS_IsDataEnable(CShortData *pData);
void TMS_SetDataEnable(CShortData *pData, BOOL bEnable=TRUE);

BOOL TMS_IsDataShow(CShortData *pData);
void TMS_SetDataShow(CShortData *pData, BOOL bShow=TRUE);
long TMS_SetDataAttr(CShortData *pData, const CString &strAttrID, const CString &strValue);
long TMS_SetDatasAttr(CExBaseList *pDatas, const CString &strAttrID, const CString &strValue);
long TMS_GetDatasByGroupID(CExBaseList *pDatas, const CString &strGroupID, CExBaseList *pList);
long TMS_GetDatasByGroupID(CTestMacro *pMacro, const CString &strGroupID, CExBaseList *pList);

long TMS_SetDataAttrByGroupID(CTestMacro *pMacro, const CString &strDataID, const CString &strAttrID, const CString &strValue);
long TMS_SetDatasAttrByGroupID(CTestMacro *pMacro, const CString &strGroupID, const CString &strAttrID, const CString &strValue);

void TMS_InitDatasAttr(CTestMacro *pMacro);
void TMS_InitDatasAttr(CExBaseList *pDatas);

BOOL TMS_RunScript(CTestMacro *pMacro, CShortData *pData);

