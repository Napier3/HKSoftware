#pragma once

#include "../../../Module/BaseClass/ExBaseObject.h"

class CPpDevConfigXMLKeys : public CXmlRWKeys
{
private:
	CPpDevConfigXMLKeys();
	virtual ~CPpDevConfigXMLKeys()	{	}

	static long g_nPpDevConfigXMLKeysRef;

public:
	static CPpDevConfigXMLKeys* g_pPpDevConfigXMLKeys;
	static CPpDevConfigXMLKeys* Create();
	static void Release();

public:
	BSTR m_strXSINoNamespaceSchemaLocationKey;
	BSTR m_strXmlnsKey;

	BSTR m_strPpDevConfigKey;
	BSTR m_strVersionKey;
	BSTR m_strDeviceModelsKey;
	BSTR m_strDevcieModelKey;
	BSTR m_strDebugDeviceFileKey;

	BSTR m_strFileKey;
};