//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptAnalysisGlobal.h

#pragma once

#include "ExBaseList.h"

#define RPTALSCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define RPTALSCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define RPTALSCLASSID_CRPTDATAALSDEF       (RPTALSCLASSID_BASECLASS + 0X00000000)
#define RPTALSCLASSID_CRPTDATAALSDEFS       (RPTALSCLASSID_EXLISTCLASS + 0X00000001)
#define RPTALSCLASSID_CRPTDATAALSDEFSMNGR       (RPTALSCLASSID_EXLISTCLASS + 0X00000002)

class CRptAnalysisXmlRWKeys : public CXmlRWKeys
{
protected:
	CRptAnalysisXmlRWKeys();
	virtual ~CRptAnalysisXmlRWKeys();
	static long g_nRPTALSRef;

public:
	static CRptAnalysisXmlRWKeys* g_pXmlKeys;
	static CRptAnalysisXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCRptDataAlsDefsMngrKey; //data-defs-mngr
	BSTR m_strCRptDataAlsDefsKey; //data-defs
	BSTR m_strCRptDataAlsDefKey; //data-def
	BSTR m_strItem_PathKey; //item-path
	BSTR m_strId_ValueKey; //id-value

public:
	static BSTR CRptDataAlsDefsMngrKey()  {   return g_pXmlKeys->m_strCRptDataAlsDefsMngrKey;  }
	static BSTR CRptDataAlsDefsKey()  {   return g_pXmlKeys->m_strCRptDataAlsDefsKey;  }
	static BSTR CRptDataAlsDefKey()  {   return g_pXmlKeys->m_strCRptDataAlsDefKey;  }
	static BSTR Item_PathKey()  {   return g_pXmlKeys->m_strItem_PathKey;  }
	static BSTR Id_ValueKey()  {   return g_pXmlKeys->m_strId_ValueKey;  }
};



class CRptAnalysisConstGlobal
{
private:
	CRptAnalysisConstGlobal();
	virtual ~CRptAnalysisConstGlobal();

public:
	static CRptAnalysisConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CRptAnalysisConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
