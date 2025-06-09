#include "StdAfx.h"
#include "CtrlWords.h"
#include "Set.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCtrlWords::CCtrlWords(void)
{
	m_strName = CXLanguageResourceAtsBase::g_sLangTxt_ControlWord/*L"¿ØÖÆ×Ö"*/;
}

CCtrlWords::~CCtrlWords(void)
{
}

BSTR CCtrlWords::GetXmlElementKey()
 {   
	 return CGbXMLKeys::g_pGbXMLKeys->m_strCtrlWordsKey;     
}

CBaseObject* CCtrlWords::Clone()
{
	CCtrlWords* p = new CCtrlWords();
	Copy(p);

	return p;
}