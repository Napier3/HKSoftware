//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GlobalDataMngrGlobal.h

#pragma once

#include "..\..\..\Module\BaseClass\ExBaseList.h"

#define TFLTCLASSID_BASECLASS         (CLASSID_BASECLASS + 0X00010000)
#define TFLTCLASSID_EXLISTCLASS       (CLASSID_LISTCLASS + 0X00010000)

#define TFLTCLASSID_CFILTERTEXT       (TFLTCLASSID_BASECLASS + 0X00000000)
#define TFLTCLASSID_CFILTERTEXTMNGR       (TFLTCLASSID_EXLISTCLASS + 0X00000001)


class CGlobalDataMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CGlobalDataMngrXmlRWKeys();
	virtual ~CGlobalDataMngrXmlRWKeys();
	static long g_nSTGRef;

public:
	static CGlobalDataMngrXmlRWKeys* g_pXmlKeys;
	static CGlobalDataMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCFilterTextMngrKey; //txt-filter-mngr
	BSTR m_strCFilterTextKey; //txt-filter

public:
	static BSTR CFilterTextMngrKey()  {   return g_pXmlKeys->m_strCFilterTextMngrKey;  }
	static BSTR CFilterTextKey()  {   return g_pXmlKeys->m_strCFilterTextKey;  }
};


