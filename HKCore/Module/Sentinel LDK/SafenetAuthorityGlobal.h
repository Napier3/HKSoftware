//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SafenetAuthorityGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define SafenetAuthoritysID_Test            _T("Test")
#define SafenetAuthoritysID_TestApp       _T("TestApp")
#define SafenetAuthoritysID_hasp_info     _T("hasp_info")
#define SafenetAuthoritysID_TestMacros  _T("TestMacros")

class CSafenetAuthorityXmlRWKeys : public CXmlRWKeys
{
protected:
	CSafenetAuthorityXmlRWKeys();
	virtual ~CSafenetAuthorityXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSafenetAuthorityXmlRWKeys* g_pXmlKeys;
	static CSafenetAuthorityXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSafenetAuthoritysMngrKey; //safenet-authority-mngr
	BSTR m_strCSafenetAuthoritysKey; //safenet-authority
	BSTR m_strCSafenetAuthorityKey; //authority
	BSTR m_strAuthorityTypeKey; //type
	BSTR m_strEnableKey; //enable

public:
	static BSTR CSafenetAuthoritysMngrKey()  {   return g_pXmlKeys->m_strCSafenetAuthoritysMngrKey;  }
	static BSTR CSafenetAuthoritysKey()  {   return g_pXmlKeys->m_strCSafenetAuthoritysKey;  }
	static BSTR CSafenetAuthorityKey()  {   return g_pXmlKeys->m_strCSafenetAuthorityKey;  }
};

