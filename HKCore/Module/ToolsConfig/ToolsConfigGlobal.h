//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ToolsConfigGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define TCFCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define TCFCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define TCFCLASSID_CTOOLOBJECT       (TCFCLASSID_BASECLASS + 0X00000000)
#define TCFCLASSID_CTOOLSCONFIG       (TCFCLASSID_EXLISTCLASS + 0X00000001)

class CToolsConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CToolsConfigXmlRWKeys();
	virtual ~CToolsConfigXmlRWKeys();
	static long g_nTCFRef;

public:
	static CToolsConfigXmlRWKeys* g_pXmlKeys;
	static CToolsConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCToolsConfigKey; //tools-config
	BSTR m_strCToolObjectKey; //tool
	BSTR m_strTypeKey; //type
	BSTR m_strModeKey; //Mode
	BSTR m_strParaKey; //para
	BSTR m_strTitleKey; //title
	BSTR m_strServerNameKey; //title

	BSTR m_strUserServerKey;
	BSTR m_strUse_TASKTESTKey;
	BSTR m_strUse_SDVMPPKey;
	BSTR m_strUse_MDVMGRPKey;
	BSTR m_strUse_ReportPaneKey;
	BSTR m_strUseAppSelConfigKey;
	BSTR m_strName_TEST_PROJECT_EXKey;

public:
	static BSTR CToolsConfigKey()  {   return g_pXmlKeys->m_strCToolsConfigKey;  }
	static BSTR CToolObjectKey()  {   return g_pXmlKeys->m_strCToolObjectKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR ModeKey()  {   return g_pXmlKeys->m_strModeKey;  }
	static BSTR ParaKey()  {   return g_pXmlKeys->m_strParaKey;  }
	static BSTR TitleKey()  {   return g_pXmlKeys->m_strTitleKey;  }
	static BSTR ServerNameKey()  {   return g_pXmlKeys->m_strServerNameKey;  }
};



class CToolsConfigConstGlobal
{
private:
	CToolsConfigConstGlobal();
	virtual ~CToolsConfigConstGlobal();

public:
	static CToolsConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CToolsConfigConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
