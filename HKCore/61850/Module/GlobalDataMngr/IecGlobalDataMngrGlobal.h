//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGlobalDataMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "../../../Module/DataMngr/DataTypes.h"

#define STGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define STGCLASSID_EXLISTCLASS       (CLASSID_LISTCLASS + 0X00010000)

#define STGCLASSID_CIecFilterTEXT       (STGCLASSID_BASECLASS + 0X00000000)
#define STGCLASSID_CIecFilterTEXTMNGR       (STGCLASSID_EXLISTCLASS + 0X00000001)
#define STGCLASSID_CDataTypeVALUE       (STGCLASSID_BASECLASS + 0X00000002)
#define STGCLASSID_CDataType       (STGCLASSID_EXLISTCLASS + 0X00000003)
#define STGCLASSID_CDataTypeMNGR       (STGCLASSID_EXLISTCLASS + 0X00000004)
#define STGCLASSID_CIecSmvCHDATATYPE       (STGCLASSID_EXLISTCLASS + 0X00000005)
#define STGCLASSID_CIecGooseCHDATATYPEMNGR       (STGCLASSID_EXLISTCLASS + 0X00000006)

class CIecGlobalDataMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CIecGlobalDataMngrXmlRWKeys();
	virtual ~CIecGlobalDataMngrXmlRWKeys();
	static long g_nSTGRef;

public:
	static CIecGlobalDataMngrXmlRWKeys* g_pXmlKeys;
	static CIecGlobalDataMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCIecGooseChDataTypeMngrKey; //gs-ch-data-type-mngr
	BSTR m_strCIecSmvChDataTypeKey; //smv-data-type
	BSTR m_strCDataTypeMngrKey; //data-type-mngr
	BSTR m_strCDataTypeKey; //data-type
	BSTR m_strCDataTypeValueKey; //dt-value
	BSTR m_strCIecFilterTextMngrKey; //txt-filter-mngr
	BSTR m_strCIecFilterTextKey; //txt-filter
	BSTR m_strIndexKey; //index

public:
	static BSTR CIecGooseChDataTypeMngrKey()  {   return g_pXmlKeys->m_strCIecGooseChDataTypeMngrKey;  }
	static BSTR CIecSmvChDataTypeKey()  {   return g_pXmlKeys->m_strCIecSmvChDataTypeKey;  }
	static BSTR CDataTypeMngrKey()  {   return g_pXmlKeys->m_strCDataTypeMngrKey;  }
	static BSTR CDataTypeKey()  {   return g_pXmlKeys->m_strCDataTypeKey;  }
	static BSTR CDataTypeValueKey()  {   return g_pXmlKeys->m_strCDataTypeValueKey;  }
	static BSTR CIecFilterTextMngrKey()  {   return g_pXmlKeys->m_strCIecFilterTextMngrKey;  }
	static BSTR CIecFilterTextKey()  {   return g_pXmlKeys->m_strCIecFilterTextKey;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
};


