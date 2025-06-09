#pragma once

#include "../../BaseClass/ExBaseObject.h"


class CXFcenterXMLRWKeys : public CXmlRWKeys
{
private:
	CXFcenterXMLRWKeys();
	virtual ~ CXFcenterXMLRWKeys()	{ }

public:
	static CXFcenterXMLRWKeys* g_pXFcenterRWKeys;
	static long g_nXFcenterRWKeysRef;
	static CXFcenterXMLRWKeys* Create();
	static void Release();

public:
	BSTR m_strXFcenterKey;
	BSTR m_strServerPortKey;
	BSTR m_strServerIPKey;
	BSTR m_strUserIDKey;
	BSTR m_strUserPswKey;
	BSTR m_strUseServerKey;

	BSTR m_strFileReportsKey;
	BSTR m_strFileTemplateKey;
	BSTR m_strFileProtocolKey;

	BSTR m_strSeverHostNameKey;
	BSTR m_strSeverMacKey;
	BSTR m_strLocalGatewayMacKey;
	BSTR m_strAccessTypeKey;
public:
	
};

