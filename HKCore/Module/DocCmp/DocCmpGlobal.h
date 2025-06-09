//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocCmpGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define DOCMPCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define DOCMPCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define DOCMPCLASSID_CDOCTEXT       (DOCMPCLASSID_BASECLASS + 0X00000000)
#define DOCMPCLASSID_CDOCCEL       (DOCMPCLASSID_EXLISTCLASS + 0X00000001)
#define DOCMPCLASSID_CDOCROW       (DOCMPCLASSID_EXLISTCLASS + 0X00000002)
#define DOCMPCLASSID_CDOCTABLE       (DOCMPCLASSID_EXLISTCLASS + 0X00000003)
#define DOCMPCLASSID_CDOCFILE       (DOCMPCLASSID_EXLISTCLASS + 0X00000004)
#define DOCMPCLASSID_CDOCCMP       (DOCMPCLASSID_EXLISTCLASS + 0X00000005)
#define DOCMPCLASSID_CDOCGROUP       (DOCMPCLASSID_EXLISTCLASS + 0X00000006)

class CDocCmpXmlRWKeys : public CXmlRWKeys
{
protected:
	CDocCmpXmlRWKeys();
	virtual ~CDocCmpXmlRWKeys();
	static long g_nDOCMPRef;

	long m_nIsSaveCmpMode;

public:
	static CDocCmpXmlRWKeys* g_pXmlKeys;
	static CDocCmpXmlRWKeys* Create();
	static void Release();

	static BOOL IsSaveCmpMode();
	static void SetSaveCmpMode(long nMode);

public:
	BSTR m_strCDocGroupKey; //group
	BSTR m_strCDocCmpKey; //doc_cmp
	BSTR m_strCDocFileKey; //doc
	BSTR m_strCDocTableKey; //table
	BSTR m_strCDocRowKey; //row
	BSTR m_strCDocCelKey; //cel
	BSTR m_strCDocTextKey; //text
	BSTR m_strCmp_IdKey; //cmp_id
	BSTR m_strTxtKey; //txt
	BSTR m_strStartKey; //start
	BSTR m_strEndKey; //end
	BSTR m_strErrorKey; //error
	BSTR m_strRowKey; //row
	BSTR m_strColKey; //col
	BSTR m_strWidthKey; //width
	BSTR m_strHeightKey; //Height
	BSTR m_strTxt_Cmp_IdKey; //txt_cmp_id
	BSTR m_strMap_IdKey; //map-id
	BSTR m_strCDocTextValKey; //txt

public:
	static BSTR CDocGroupKey()  {   return g_pXmlKeys->m_strCDocGroupKey;  }
	static BSTR CDocCmpKey()  {   return g_pXmlKeys->m_strCDocCmpKey;  }
	static BSTR CDocFileKey()  {   return g_pXmlKeys->m_strCDocFileKey;  }
	static BSTR CDocTableKey()  {   return g_pXmlKeys->m_strCDocTableKey;  }
	static BSTR CDocRowKey()  {   return g_pXmlKeys->m_strCDocRowKey;  }
	static BSTR CDocCelKey()  {   return g_pXmlKeys->m_strCDocCelKey;  }
	static BSTR CDocTextKey()  {   return g_pXmlKeys->m_strCDocTextKey;  }
	static BSTR Cmp_IdKey()  {   return g_pXmlKeys->m_strCmp_IdKey;  }
	static BSTR TxtKey()  {   return g_pXmlKeys->m_strTxtKey;  }
	static BSTR StartKey()  {   return g_pXmlKeys->m_strStartKey;  }
	static BSTR EndKey()  {   return g_pXmlKeys->m_strEndKey;  }
	static BSTR ErrorKey()  {   return g_pXmlKeys->m_strErrorKey;  }
	static BSTR RowKey()  {   return g_pXmlKeys->m_strRowKey;  }
	static BSTR ColKey()  {   return g_pXmlKeys->m_strColKey;  }
	static BSTR WidthKey()  {   return g_pXmlKeys->m_strWidthKey;  }
	static BSTR HeightKey()  {   return g_pXmlKeys->m_strHeightKey;  }
	static BSTR Txt_Cmp_IdKey()  {   return g_pXmlKeys->m_strTxt_Cmp_IdKey;  }
	static BSTR Map_IdKey()  {   return g_pXmlKeys->m_strMap_IdKey;  }
	static BSTR CDocTextValKey()  {   return g_pXmlKeys->m_strCDocTextValKey;  }
};



class CDocCmpConstGlobal
{
private:
	CDocCmpConstGlobal();
	virtual ~CDocCmpConstGlobal();

public:
	static CDocCmpConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CDocCmpConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

extern long g_nDocTextUseCdata;
extern long g_nLogDocCmpProgress;

CString docmp_GenDocCmpID();
