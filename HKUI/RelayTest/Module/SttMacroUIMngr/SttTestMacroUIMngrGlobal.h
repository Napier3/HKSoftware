//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestMacroUIMngrGlobal.h

#pragma once

#include "ExBaseList.h"

#define UIMngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define UIMngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define UIMNGRCLASSID_STTMACROUIMNGR       (UIMngrCLASSID_EXLISTCLASS + 0X00000000)
#define UIMNGRCLASSID_UIGROUP       (UIMngrCLASSID_EXLISTCLASS + 0X00000001)
#define UIMNGRCLASSID_MACROUI       (UIMngrCLASSID_BASECLASS + 0X00000002)

class CSttTestMacroUIMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CSttTestMacroUIMngrXmlRWKeys();
	virtual ~CSttTestMacroUIMngrXmlRWKeys();
	static long g_nUIMngrRef;

public:
	static CSttTestMacroUIMngrXmlRWKeys* g_pXmlKeys;
	static CSttTestMacroUIMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strMacroUIKey; //macro-ui
	BSTR m_strUIGroupKey; //ui-group
	BSTR m_strSttMacroUIMngrKey; //stt-macro-ui-mngr
	BSTR m_strTypeKey; //type
	BSTR m_strUi_TypeKey; //ui-type
	BSTR m_strFileKey; //file
	BSTR m_strTemplate_GenKey; //template-gen

public:
	static BSTR MacroUIKey()  {   return g_pXmlKeys->m_strMacroUIKey;  }
	static BSTR UIGroupKey()  {   return g_pXmlKeys->m_strUIGroupKey;  }
	static BSTR SttMacroUIMngrKey()  {   return g_pXmlKeys->m_strSttMacroUIMngrKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR Ui_TypeKey()  {   return g_pXmlKeys->m_strUi_TypeKey;  }
	static BSTR FileKey()  {   return g_pXmlKeys->m_strFileKey;  }
	static BSTR Template_GenKey()  {   return g_pXmlKeys->m_strTemplate_GenKey;  }
};



class CSttTestMacroUIMngrConstGlobal
{
private:
	CSttTestMacroUIMngrConstGlobal();
	virtual ~CSttTestMacroUIMngrConstGlobal();

public:
	static CSttTestMacroUIMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSttTestMacroUIMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
