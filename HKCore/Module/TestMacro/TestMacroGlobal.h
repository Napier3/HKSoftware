//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"
#include "../DataMngr/ShortDatas.h"

#define TMCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00020000)
#define TMCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00020000)

#define TMCLASSID_CTESTMACRO       (TMCLASSID_EXLISTCLASS + 0X00000000)
#define TMCLASSID_CTESTMACROS       (TMCLASSID_EXLISTCLASS + 0X00000001)
#define TMCLASSID_CTMFAULTPARAS       (TMCLASSID_EXLISTCLASS + 0X00000002)
#define TMCLASSID_CTMSYSPARAS       (TMCLASSID_EXLISTCLASS + 0X00000003)
#define TMCLASSID_CTMRESULTPARAS       (TMCLASSID_EXLISTCLASS + 0X00000004)
#define TMCLASSID_CTESTMACROSFILE       (TMCLASSID_EXLISTCLASS + 0X00000005)
#define TMCLASSID_CTESTMACROSFILEMNGR       (TMCLASSID_EXLISTCLASS + 0X00000006)
#define TMCLASSID_CTMFAULTPARASEX       (TMCLASSID_EXLISTCLASS + 0X00000007)
#define TMCLASSID_CTESTMACROCONFIGS       (TMCLASSID_EXLISTCLASS + 0X00000008)
#define TMCLASSID_CTESTMACROCONFIG       (TMCLASSID_BASECLASS + 0X00000009)
#define TMCLASSID_CTMRESULTPARASEX       (TMCLASSID_EXLISTCLASS + 0X0000000A)
#define TMCLASSID_CTMSEARCHRESULTPARAS       (TMCLASSID_EXLISTCLASS + 0X0000000B)
#define TMCLASSID_CTESTMACROSINCLUDE       (TMCLASSID_EXLISTCLASS + 0X0000000C)

class CTestMacroXmlRWKeys : public CDataMngrXmlRWKeys
{
public:
	CTestMacroXmlRWKeys();
	virtual ~CTestMacroXmlRWKeys();
	static long g_nTMRef;

public:
	static CTestMacroXmlRWKeys* g_pXmlKeys;
	static CTestMacroXmlRWKeys* Create();
	static void Release();
	static CTestMacroXmlRWKeys* CreateNew()
	{
		return new CTestMacroXmlRWKeys();
	}

public:
	BSTR m_strCTestMacrosIncludeKey; //macros-include  2021-8-14  lijunqing  充电桩自动测试，多仪器功能文件的扩充
	BSTR m_strCTestMacroConfigKey; //macro-test-config
	BSTR m_strCTestMacroConfigsKey; //test-macro-configs
	BSTR m_strCTestMacrosFileMngrKey; //macro-file-mngr
	BSTR m_strCTestMacrosFileKey; //macro-file
	BSTR m_strCTmResultParasKey; //results
	BSTR m_strCTmSearchResultParasKey; //search-results
	BSTR m_strCTmResultParasExKey; //results-ex
	BSTR m_strCTmSysParasKey; //sys-paras
	BSTR m_strCTmFaultParasKey; //fault-paras
	BSTR m_strCTmFaultParasExKey; //fault-paras-ex
	BSTR m_strCTestMacrosKey; //macros
	BSTR m_strCTestMacroKey; //macro
	BSTR m_strVersionKey; //version
	BSTR m_strTypeKey; //type
	BSTR m_strRemarkKey; //remark
	BSTR m_strProgIDKey; //prog-id
	BSTR m_strFileKey; //file
	BSTR m_strCmmFileKey; //cmm-file
	BSTR m_strTestTypeFileKey; //test-type-file
	BSTR m_strDataTypeFileKey; //data-type-file
	BSTR m_strDvmFileKey; //dvm-file
	BSTR m_strActiveMacroTestKey; //active-macro-test
	BSTR m_strRecordProgIDKey; //recrod-progid
	BSTR m_strIecConfigFileKey; //iec-config-file
	BSTR m_strExpandConfigFileKey; 
	BSTR m_strDllCallFileKey; 
	BSTR m_strOldIDKey; 

public:
	static BSTR CTestMacrosIncludeKey()  {   return g_pXmlKeys->m_strCTestMacrosIncludeKey;  }
	static BSTR CTestMacroConfigKey()  {   return g_pXmlKeys->m_strCTestMacroConfigKey;  }
	static BSTR CTestMacroConfigsKey()  {   return g_pXmlKeys->m_strCTestMacroConfigsKey;  }
	static BSTR CTmFaultParasExKey()  {   return g_pXmlKeys->m_strCTmFaultParasExKey;  }
	static BSTR CTestMacrosFileMngrKey()  {   return g_pXmlKeys->m_strCTestMacrosFileMngrKey;  }
	static BSTR CTestMacrosFileKey()  {   return g_pXmlKeys->m_strCTestMacrosFileKey;  }
	static BSTR CTmResultParasKey()  {   return g_pXmlKeys->m_strCTmResultParasKey;  }
	static BSTR CTmSearchResultParasKey()  {   return g_pXmlKeys->m_strCTmSearchResultParasKey;  }
	static BSTR CTmResultParasExKey()  {   return g_pXmlKeys->m_strCTmResultParasExKey;  }
	static BSTR CTmSysParasKey()  {   return g_pXmlKeys->m_strCTmSysParasKey;  }
	static BSTR CTmFaultParasKey()  {   return g_pXmlKeys->m_strCTmFaultParasKey;  }
	static BSTR CTestMacrosKey()  {   return g_pXmlKeys->m_strCTestMacrosKey;  }
	static BSTR CTestMacroKey()  {   return g_pXmlKeys->m_strCTestMacroKey;  }
	static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR RemarkKey()  {   return g_pXmlKeys->m_strRemarkKey;  }
	static BSTR ProgIDKey()  {   return g_pXmlKeys->m_strProgIDKey;  }
	static BSTR FileKey()  {   return g_pXmlKeys->m_strFileKey;  }
	static BSTR CmmFileKey()  {   return g_pXmlKeys->m_strCmmFileKey;  }
	static BSTR TestTypeFileKey()  {   return g_pXmlKeys->m_strTestTypeFileKey;  }
	static BSTR DataTypeFileKey()  {   return g_pXmlKeys->m_strDataTypeFileKey;  }
	static BSTR DvmFileKey()  {   return g_pXmlKeys->m_strDvmFileKey;  }
	static BSTR ActiveMacroTestKey()  {   return g_pXmlKeys->m_strActiveMacroTestKey;  }
	static BSTR IecConfigFileKey()  {   return g_pXmlKeys->m_strIecConfigFileKey;  }
	static BSTR ExpandConfigFileKey()  {   return g_pXmlKeys->m_strExpandConfigFileKey;  }
	static BSTR OldIDKey()  {   return g_pXmlKeys->m_strOldIDKey;  }
};



class CTestMacroConstGlobal
{
private:
	CTestMacroConstGlobal();
	virtual ~CTestMacroConstGlobal();

public:
	static CTestMacroConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CTestMacroConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

CString tm_GetParaDataPath(CExBaseObject *pData);
static const CString g_strDefaultMacroType = _T("relay");
