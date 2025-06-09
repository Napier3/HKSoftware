#pragma once

//×¢ÒâincludeÂ·¾¶
#include "GbCommCmdGlobalDefine.h"

class CCommCmdConfigXMLKeys : public CXmlRWKeys
{
private:
	CCommCmdConfigXMLKeys();
	virtual ~CCommCmdConfigXMLKeys()	{	}

	static long g_nConfigXMLKeysRef;

public:
	static CCommCmdConfigXMLKeys* g_pConfigXMLKeys;
	static CCommCmdConfigXMLKeys* CreateConfigXMLKeys();
	static void Release();

public:
	BSTR m_strCommCmdConfigKey;
	BSTR m_strCmdKey;
	BSTR m_strCmdExKey;
	BSTR m_strCmdParaKey;

	BSTR m_strPpProcedureIDKey;
	BSTR m_strPpDvNodeIDKey;
	BSTR m_strGbDataIDKey;
	BSTR m_strGbRwOptrKeyKey;
	BSTR m_strDatasetKey;
	BSTR m_strValueKey;
	BSTR m_strDataTypeKey;
	BSTR m_strUseConnectKey;
	BSTR m_strWzdEditModeKey;
};