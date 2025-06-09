#pragma once
#include "../../../../Module/BaseClass/ExBaseObject.h"

class CYCTamplateXMLKeys: public CXmlRWKeys
{
private:
	CYCTamplateXMLKeys(void);
	virtual ~CYCTamplateXMLKeys(void);

public:
	static long g_nYCTamplateKeysRef;
	static CYCTamplateXMLKeys* g_pYCTamplateKeys;
	static CYCTamplateXMLKeys* CreatetYCTamplateXMLkeys();
	static void Release();
public:
	BSTR m_strKeyYCTemplate;
	BSTR m_strKeyUnit;
	BSTR m_strKeyData;
	BSTR m_strKeyModel;
};
