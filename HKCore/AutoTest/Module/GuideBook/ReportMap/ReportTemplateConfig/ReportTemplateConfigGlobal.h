//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ReportTemplateConfigGlobal.h

#pragma once

#include "../../../../../Module/BaseClass/ExBaseList.h"

#define RPTCFGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define RPTCFGCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define RPTCFGCLASSID_CREPORTTEMPLATECONFIG       (RPTCFGCLASSID_EXLISTCLASS + 0X00000000)
#define RPTCFGCLASSID_CCOMMCMDSTRCUTATTR       (RPTCFGCLASSID_BASECLASS + 0X00000001)
#define RPTCFGCLASSID_CCOMMCMDSTRCUTATTRS       (RPTCFGCLASSID_EXLISTCLASS + 0X00000002)
#define RPTCFGCLASSID_CBKMKDATAPROCESS       (RPTCFGCLASSID_EXLISTCLASS + 0X00000003)
#define RPTCFGCLASSID_CBKMKDATAPROCESSMNGR       (RPTCFGCLASSID_EXLISTCLASS + 0X00000004)
#define RPTCFGCLASSID_CSYSRPTDATA       (RPTCFGCLASSID_BASECLASS + 0X00000005)
#define RPTCFGCLASSID_CSYSRPTDATAMNGR       (RPTCFGCLASSID_EXLISTCLASS + 0X00000006)
#define RPTCFGCLASSID_CMGRPCMBNDATAMNGR       (RPTCFGCLASSID_EXLISTCLASS + 0X00000007)

class CReportTemplateConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CReportTemplateConfigXmlRWKeys();
	virtual ~CReportTemplateConfigXmlRWKeys();
	static long g_nRPTCFGRef;

public:
	static CReportTemplateConfigXmlRWKeys* g_pXmlKeys;
	static CReportTemplateConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCMgrpCmbnDataMngrKey; //MgrpCmbn
	BSTR m_strCSysRptDataMngrKey; //sys-rpt-data-mngr
	BSTR m_strCSysRptDataKey; //rpt-data
	BSTR m_strCBkmkDataProcessMngrKey; //bkmk-data-process-mngr
	BSTR m_strCBkmkDataProcessKey; //process
	BSTR m_strCCommCmdStrcutAttrsKey; //comm-cmd-struct-attrs
	BSTR m_strCCommCmdStrcutAttrKey; //attr
	BSTR m_strCReportTemplateConfigKey; //report-template-config
	BSTR m_strOptrKey; //optr
	BSTR m_strValueKey; //value
	BSTR m_strTextTrueKey; //txt-true
	BSTR m_strTextFalseKey; //txt-false
	BSTR m_strTextAppendKey; //append-text

public:
	static BSTR CMgrpCmbnDataMngrKey()  {   return g_pXmlKeys->m_strCMgrpCmbnDataMngrKey;  }
	static BSTR CSysRptDataMngrKey()  {   return g_pXmlKeys->m_strCSysRptDataMngrKey;  }
	static BSTR CSysRptDataKey()  {   return g_pXmlKeys->m_strCSysRptDataKey;  }
	static BSTR CBkmkDataProcessMngrKey()  {   return g_pXmlKeys->m_strCBkmkDataProcessMngrKey;  }
	static BSTR CBkmkDataProcessKey()  {   return g_pXmlKeys->m_strCBkmkDataProcessKey;  }
	static BSTR CCommCmdStrcutAttrsKey()  {   return g_pXmlKeys->m_strCCommCmdStrcutAttrsKey;  }
	static BSTR CCommCmdStrcutAttrKey()  {   return g_pXmlKeys->m_strCCommCmdStrcutAttrKey;  }
	static BSTR CReportTemplateConfigKey()  {   return g_pXmlKeys->m_strCReportTemplateConfigKey;  }
	static BSTR OptrKey()  {   return g_pXmlKeys->m_strOptrKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR TextTrueKey()  {   return g_pXmlKeys->m_strTextTrueKey;  }
	static BSTR TextFalseKey()  {   return g_pXmlKeys->m_strTextFalseKey;  }
	static BSTR TextAppendKey()  {   return g_pXmlKeys->m_strTextAppendKey;  }
};



class CReportTemplateConfigConstGlobal
{
private:
	CReportTemplateConfigConstGlobal();
	virtual ~CReportTemplateConfigConstGlobal();

public:
	static CReportTemplateConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CReportTemplateConfigConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
