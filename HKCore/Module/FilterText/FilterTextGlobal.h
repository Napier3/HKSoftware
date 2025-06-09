//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterTextGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define FLTCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define FLTCLASSID_EXLICLASS       (CLASSID_LISTCLASS + 0X00010000)

#define FLTCLASSID_CFILTERTEXT       (FLTCLASSID_BASECLASS + 0X00000000)
#define FLTCLASSID_CFILTERTEXTMNGR       (FLTCLASSID_EXLICLASS + 0X00000001)

class CFilterTextXmlRWKeys : public CXmlRWKeys
{
protected:
	CFilterTextXmlRWKeys();
	virtual ~CFilterTextXmlRWKeys();
	static long g_nFLTRef;

public:
	static CFilterTextXmlRWKeys* g_pXmlKeys;
	static CFilterTextXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCFilterTextMngrKey; //txt-filter-mngr
	BSTR m_strCFilterTextKey; //txt-filter

public:
	static BSTR CFilterTextMngrKey()  {   return g_pXmlKeys->m_strCFilterTextMngrKey;  }
	static BSTR CFilterTextKey()  {   return g_pXmlKeys->m_strCFilterTextKey;  }
};


