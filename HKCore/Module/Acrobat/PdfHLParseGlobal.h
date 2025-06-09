//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PdfHLParseGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define PDF_CLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define PDF_CLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define PDF_CLASSID_CPDFDBINFO       (PDF_CLASSID_EXLISTCLASS + 0X00000000)
#define PDF_CLASSID_CPDFDBTABLE       (PDF_CLASSID_EXLISTCLASS + 0X00000001)
#define PDF_CLASSID_CPDFDBHEAD       (PDF_CLASSID_BASECLASS + 0X00000002)

class CPdfHLParseXmlRWKeys : public CXmlRWKeys
{
protected:
	CPdfHLParseXmlRWKeys();
	virtual ~CPdfHLParseXmlRWKeys();
	static long g_nPDF_Ref;

public:
	static CPdfHLParseXmlRWKeys* g_pXmlKeys;
	static CPdfHLParseXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCPdfDBHeadKey; //tableHead
	BSTR m_strCPdfDBTableKey; //tableBelong
	BSTR m_strCPdfDBInfoKey; //PdfInfo
	BSTR m_strNameHeadKey; //NameHead
	BSTR m_strDWHeadKey; //DWHead
	BSTR m_strValueHeadKey; //ValueHead
	BSTR m_strExistHeadKey; //ExistHead

public:
	static BSTR CPdfDBHeadKey()  {   return g_pXmlKeys->m_strCPdfDBHeadKey;  }
	static BSTR CPdfDBTableKey()  {   return g_pXmlKeys->m_strCPdfDBTableKey;  }
	static BSTR CPdfDBInfoKey()  {   return g_pXmlKeys->m_strCPdfDBInfoKey;  }
	static BSTR NameHeadKey()  {   return g_pXmlKeys->m_strNameHeadKey;  }
	static BSTR DWHeadKey()  {   return g_pXmlKeys->m_strDWHeadKey;  }
	static BSTR ValueHeadKey()  {   return g_pXmlKeys->m_strValueHeadKey;  }
	static BSTR ExistHeadKey()  {   return g_pXmlKeys->m_strExistHeadKey;  }
};



class CPdfHLParseConstGlobal
{
private:
	CPdfHLParseConstGlobal();
	virtual ~CPdfHLParseConstGlobal();

public:
	static CPdfHLParseConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CPdfHLParseConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
