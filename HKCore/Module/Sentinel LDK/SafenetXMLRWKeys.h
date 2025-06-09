#pragma once

#include "../BaseClass/ExBaseObject.h"


class CSafenetXMLRWKeys : public CXmlRWKeys
{
private:
	CSafenetXMLRWKeys();
	virtual ~ CSafenetXMLRWKeys()	{ }

public:
	static CSafenetXMLRWKeys* g_pSafenetRWKeys;
	static long g_nSafenetRWKeysRef;
	static CSafenetXMLRWKeys* Create();
	static void Release();

public:
	BSTR m_strSafenetKey;
	BSTR m_strServerPortKey;
	BSTR m_strServerIPKey;
	BSTR m_strUserIDKey;
	BSTR m_strUserPswKey;
	BSTR m_strUseServerKey;
	
	BSTR m_strSeverHostNameKey;
	BSTR m_strSeverMacKey;
	BSTR m_strLocalGatewayMacKey;
	BSTR m_strAccessTypeKey;

public:
	
};

