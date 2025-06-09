//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttLicenseGlobal.h

#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define STTCMDCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00310000)
#define STTCMDCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00310000)

#define STTCMDCLASSID_CSTTLICENSEMODULE       (STTCMDCLASSID_BASECLASS + 0X00000034)
#define STTCMDCLASSID_CSTTLICENSE       (STTCMDCLASSID_EXLISTCLASS + 0X00000035)
#define STTCMDCLASSID_CSTTLICENSEMNGR       (STTCMDCLASSID_EXLISTCLASS + 0X00000036)

class CLicenseXmlRWKeys : public CXmlRWKeys
{
protected:
	CLicenseXmlRWKeys();
	virtual ~CLicenseXmlRWKeys();
	static long g_nSTTLCSRef;

public:
	static CLicenseXmlRWKeys* g_pXmlKeys;
	static CLicenseXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSttLicenseMngrKey; //license-mngr
	BSTR m_strCSttLicenseKey; //license
	BSTR m_strCSttLicenseModuleKey; //module
	BSTR m_strKeyKey; //key
	BSTR m_strYearKey; //year
	BSTR m_strMonthKey; //month
	BSTR m_strDayKey; //day
	BSTR m_strDaysKey; //days
	BSTR m_strTimesKey; //times
	BSTR m_strTypeKey; //type

public:
	static BSTR CSttLicenseMngrKey()  {   return g_pXmlKeys->m_strCSttLicenseMngrKey;  }
	static BSTR CSttLicenseKey()  {   return g_pXmlKeys->m_strCSttLicenseKey;  }
	static BSTR CSttLicenseModuleKey()  {   return g_pXmlKeys->m_strCSttLicenseModuleKey;  }
	static BSTR KeyKey()  {   return g_pXmlKeys->m_strKeyKey;  }
	static BSTR YearKey()  {   return g_pXmlKeys->m_strYearKey;  }
	static BSTR MonthKey()  {   return g_pXmlKeys->m_strMonthKey;  }
	static BSTR DayKey()  {   return g_pXmlKeys->m_strDayKey;  }
	static BSTR DaysKey()  {   return g_pXmlKeys->m_strDaysKey;  }
	static BSTR TimesKey()  {   return g_pXmlKeys->m_strTimesKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
};



class CLicenseConstGlobal
{
private:
	CLicenseConstGlobal();
	virtual ~CLicenseConstGlobal();

public:
	static CLicenseConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CLicenseConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

typedef CLicenseXmlRWKeys CSttCmdDefineXmlRWKeys;
