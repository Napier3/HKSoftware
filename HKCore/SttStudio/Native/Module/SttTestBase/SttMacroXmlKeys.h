#pragma once
#include "../../../Module/BaseClass/ExBaseList.h"

class CMacroXmlKeys : public CXmlRWKeys
{
private:
	CMacroXmlKeys(void);
	virtual ~CMacroXmlKeys(void);

public:
	static CMacroXmlKeys *g_pMacroXmlKeys;
	static CMacroXmlKeys *Create();
	static void Release();
	static long g_nRef;

public:
	//for CSttParaObject
	BSTR m_strParaKey;
	BSTR m_strParaUnitKey;
	BSTR m_strParaDataTypeKey;
	BSTR m_strParaValueKey;
	BSTR m_strParaDefValueKey;
	BSTR m_strRemarkKey;
	BSTR m_strParaGroupKey;
	BSTR m_strCreateGroupKey;
	BSTR m_strParasKey;
	BSTR m_strParasFormatKey;//dingxy 20240519

	//for CSttTestBase
	BSTR m_strTestMacrosKey;
	BSTR m_strProgIDKey;
	BSTR m_strTestMacroKey;
	BSTR m_strPxAppTypeKey;
	BSTR m_strFaultParasKey;
	BSTR m_strFaultParasExKey;
	BSTR m_strSysParasKey;
	BSTR m_strResultsKey;
	BSTR m_strSearchResultsKey;//zhouhj 20210925 增加用于搜索类返回结果
	BSTR m_strUiDllFileKey;
	BSTR m_strResultExKey;

public:
	//for CSttParaObject
	static BSTR ParaKey()		{	return g_pMacroXmlKeys->m_strParaKey ;	}
	static BSTR ParaUnitKey()		{	return g_pMacroXmlKeys->m_strParaUnitKey ;	}
	static BSTR ParaDataTypeKey()		{	return g_pMacroXmlKeys->m_strParaDataTypeKey ;	}
	static BSTR ParaValueKey()		{	return g_pMacroXmlKeys->m_strParaValueKey ;	}
	static BSTR ParaDefValueKey()		{	return g_pMacroXmlKeys->m_strParaDefValueKey ;	}
	static BSTR RemarkKey()		{	return g_pMacroXmlKeys->m_strRemarkKey ;	}
	static BSTR ParaGroupKey()		{	return g_pMacroXmlKeys->m_strParaGroupKey ;	}
	static BSTR CreateGroupKey()		{	return g_pMacroXmlKeys->m_strCreateGroupKey ;	}
	static BSTR ParaFormatKey()     {   return g_pMacroXmlKeys->m_strParasFormatKey; }

	//for CSttTestBase
	static BSTR TestMacrosKey()		{	return g_pMacroXmlKeys->m_strTestMacrosKey ;	}
	static BSTR ProgIDKey()		{	return g_pMacroXmlKeys->m_strProgIDKey ;	}
	static BSTR TestMacroKey()		{	return g_pMacroXmlKeys->m_strTestMacroKey ;	}
	static BSTR PxAppTypeKey()		{	return g_pMacroXmlKeys->m_strPxAppTypeKey ;	}
	static BSTR FaultParasKey()		{	return g_pMacroXmlKeys->m_strFaultParasKey ;	}
	static BSTR FaultParasExKey()		{	return g_pMacroXmlKeys->m_strFaultParasExKey ;	}
	static BSTR SysParasKey()		{	return g_pMacroXmlKeys->m_strSysParasKey ;	}
	static BSTR ResultsKey()		{	return g_pMacroXmlKeys->m_strResultsKey ;	}
	static BSTR SearchResultsKey()		{	return g_pMacroXmlKeys->m_strSearchResultsKey ;	}//zhouhj 20210925 增加用于搜索类返回结果
	static BSTR UiDllFileKey()		{	return g_pMacroXmlKeys->m_strUiDllFileKey ;	}
	static BSTR ResultExKey()		{	return g_pMacroXmlKeys->m_strResultExKey ;	}
	static BSTR ParasKey()		{	return g_pMacroXmlKeys->m_strParasKey ;	}
};
