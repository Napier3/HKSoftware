#include "StdAfx.h"
#include "YCTamplateXMLKeys.h"

long CYCTamplateXMLKeys::g_nYCTamplateKeysRef = 0;
CYCTamplateXMLKeys* CYCTamplateXMLKeys::g_pYCTamplateKeys = NULL;

CYCTamplateXMLKeys::CYCTamplateXMLKeys(void)
{
	m_strKeyYCTemplate = L"yc-template";
	m_strKeyUnit = L"unit";
	m_strKeyData = L"data";
	m_strKeyModel = L"model";
}

CYCTamplateXMLKeys::~CYCTamplateXMLKeys(void)
{
}

CYCTamplateXMLKeys* CYCTamplateXMLKeys::CreatetYCTamplateXMLkeys()
{
	g_nYCTamplateKeysRef++;

	if (g_nYCTamplateKeysRef == 1)
	{
		g_pYCTamplateKeys = new CYCTamplateXMLKeys();
		ASSERT(g_pYCTamplateKeys != NULL);
	}

	return g_pYCTamplateKeys;
}

void CYCTamplateXMLKeys::Release()
{
	g_nYCTamplateKeysRef--;

	if (g_nYCTamplateKeysRef == 0)
	{
		delete g_pYCTamplateKeys;
		g_pYCTamplateKeys = NULL;
	}
}

