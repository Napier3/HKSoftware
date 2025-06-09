#include "StdAfx.h"
#include "BinaryIns.h"
#include "Binary.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBinaryIns::CBinaryIns(void)
{
	m_strName = CXLanguageResourceAtsBase::g_sLangTxt_InputValue/*L"¿ªÈëÁ¿"*/;
}

CBinaryIns::~CBinaryIns(void)
{
	//DeleteAll();
}

BSTR CBinaryIns::GetXmlElementKey()
{     
	return CGbXMLKeys::g_pGbXMLKeys->m_strBinaryInsKey;     
}

CBaseObject* CBinaryIns::Clone()
{
	CBinaryIns* p = new CBinaryIns();
	Copy(p);

	return p;
}