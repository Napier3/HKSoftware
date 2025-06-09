//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PdfParseGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define PDFPCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X0F000000)
#define PDFPCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X0F000000)

#define PDFPCLASSID_XML_STRING       (PDFPCLASSID_BASECLASS + 0X00000000)
#define PDFPCLASSID_ROW       (PDFPCLASSID_EXLISTCLASS + 0X00000001)
#define PDFPCLASSID_TABLE       (PDFPCLASSID_EXLISTCLASS + 0X00000002)
#define PDFPCLASSID_TABLES       (PDFPCLASSID_BASECLASS + 0X00000003)

class CPdfParseXmlRWKeys : public CXmlRWKeys
{
protected:
	CPdfParseXmlRWKeys();
	virtual ~CPdfParseXmlRWKeys();
	static long g_nPDFPRef;

public:
	static CPdfParseXmlRWKeys* g_pXmlKeys;
	static CPdfParseXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strRowKey; 
	BSTR m_strTableKey; 
	BSTR m_strTablesKey;
	BSTR m_strVposKey;
	BSTR m_strVpos2Key;
	BSTR m_strHposKey;
	BSTR m_strHpos2Key;
	BSTR m_strWidthKey;
	BSTR m_strHeightKey;
	BSTR m_strColKey;
	BSTR m_strColsKey;
	BSTR m_strStringDataKey;
	
public:
	static BSTR RowKey()    {     return g_pXmlKeys->m_strRowKey ;    } 
	static BSTR TableKey()    {     return g_pXmlKeys->m_strTableKey ;    } 
	static BSTR TablesKey()    {     return g_pXmlKeys->m_strTablesKey ;    }
	static BSTR VposKey()    {     return g_pXmlKeys->m_strVposKey ;    }
	static BSTR HposKey()    {     return g_pXmlKeys->m_strHposKey ;    }
	static BSTR WidthKey()    {     return g_pXmlKeys->m_strWidthKey ;    }
	static BSTR HeightKey()    {     return g_pXmlKeys->m_strHeightKey ;    }
	static BSTR ColKey()    {     return g_pXmlKeys->m_strColKey ;    }
	static BSTR ColsKey()    {     return g_pXmlKeys->m_strColsKey ;    }
	static BSTR StringDataKey()    {     return g_pXmlKeys->m_strStringDataKey ;    }
};


