//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//YunConfigGlobal.h

#pragma once

#include "../../BaseClass/ExBaseList.h"

#define YUNCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00040000)
#define YUNCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00040000)

#define YUNCLASSID_CYUNCONFIG       (YUNCLASSID_BASECLASS + 0X00000000)

class CYunConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CYunConfigXmlRWKeys();
	virtual ~CYunConfigXmlRWKeys();
	static long g_nYUNRef;

public:
	static CYunConfigXmlRWKeys* g_pXmlKeys;
	static CYunConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCYunConfigKey; //yun-config
	BSTR m_strProgIDKey; //progid

public:
	static BSTR CYunConfigKey()  {   return g_pXmlKeys->m_strCYunConfigKey;  }
	static BSTR ProgIDKey()  {   return g_pXmlKeys->m_strProgIDKey;  }
};

