//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBkmkBatchAddGlobal.h

#pragma once

#include "../../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../../Module/BaseClass/ExBaseListListCtrl.h"
#define RBACLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define RBACLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define RBACLASSID_CRPTBATCHITEMMAP       (RBACLASSID_BASECLASS + 0X00000000)
#define RBACLASSID_CRPTBATCHITEMMAPS       (RBACLASSID_EXLISTCLASS + 0X00000001)
#define RBACLASSID_CRPTBATCHDATAMAP       (RBACLASSID_BASECLASS + 0X00000002)
#define RBACLASSID_CRPTBATCHDATAMAPS       (RBACLASSID_EXLISTCLASS + 0X00000003)
#define RBACLASSID_CRPTBATCHCONFIG       (RBACLASSID_EXLISTCLASS + 0X00000004)
#define RBACLASSID_CRPTBKMKBATCHCELL       (RBACLASSID_BASECLASS + 0X00000005)

class CRptBkmkBatchAddXmlRWKeys : public CXmlRWKeys
{
protected:
	CRptBkmkBatchAddXmlRWKeys();
	virtual ~CRptBkmkBatchAddXmlRWKeys();
	static long g_nRBARef;

public:
	static CRptBkmkBatchAddXmlRWKeys* g_pXmlKeys;
	static CRptBkmkBatchAddXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCRptBkmkBatchCellKey; //batch-cell
	BSTR m_strCRptBatchConfigKey; //rpt-batch-config
	BSTR m_strCRptBatchDataMapsKey; //data-maps
	BSTR m_strCRptBatchDataMapKey; //data-map
	BSTR m_strCRptBatchItemMapsKey; //item-maps
	BSTR m_strCRptBatchItemMapKey; //item-map
	BSTR m_strItemIndexKey; //item-index
	BSTR m_strMapIndexKey; //map-index
	BSTR m_strRepeatIndexKey; //repeat-index
	BSTR m_strDataAttrKey; //data-attr
	BSTR m_strPrecisionKey; //precision
	BSTR m_strModeKey; //mode

public:
	static BSTR CRptBkmkBatchCellKey()  {   return g_pXmlKeys->m_strCRptBkmkBatchCellKey;  }
	static BSTR CRptBatchConfigKey()  {   return g_pXmlKeys->m_strCRptBatchConfigKey;  }
	static BSTR CRptBatchDataMapsKey()  {   return g_pXmlKeys->m_strCRptBatchDataMapsKey;  }
	static BSTR CRptBatchDataMapKey()  {   return g_pXmlKeys->m_strCRptBatchDataMapKey;  }
	static BSTR CRptBatchItemMapsKey()  {   return g_pXmlKeys->m_strCRptBatchItemMapsKey;  }
	static BSTR CRptBatchItemMapKey()  {   return g_pXmlKeys->m_strCRptBatchItemMapKey;  }
	static BSTR ItemIndexKey()  {   return g_pXmlKeys->m_strItemIndexKey;  }
	static BSTR MapIndexKey()  {   return g_pXmlKeys->m_strMapIndexKey;  }
	static BSTR RepeatIndexKey()  {   return g_pXmlKeys->m_strRepeatIndexKey;  }
	static BSTR DataAttrKey()  {   return g_pXmlKeys->m_strDataAttrKey;  }
	static BSTR PrecisionKey()  {   return g_pXmlKeys->m_strPrecisionKey;  }
	static BSTR ModeKey()  {   return g_pXmlKeys->m_strModeKey;  }
};



class CRptBkmkBatchAddConstGlobal
{
private:
	CRptBkmkBatchAddConstGlobal();
	virtual ~CRptBkmkBatchAddConstGlobal();

public:
	static CRptBkmkBatchAddConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CRptBkmkBatchAddConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
