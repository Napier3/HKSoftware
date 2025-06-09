#include "StdAfx.h"
#include "SoftSwitchs.h"
#include "Set.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSoftSwitchs::CSoftSwitchs(void)
{
	m_strName =CXLanguageResourceAtsBase::g_sLangTxt_SoftStrap/* L"ÈíÑ¹°å"*/;
}

CSoftSwitchs::~CSoftSwitchs(void)
{
}

BSTR CSoftSwitchs::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strSoftSwitchsKey;     
}

CBaseObject* CSoftSwitchs::Clone()
{
	CSoftSwitchs* p = new CSoftSwitchs();
	Copy(p);

	return p;
}