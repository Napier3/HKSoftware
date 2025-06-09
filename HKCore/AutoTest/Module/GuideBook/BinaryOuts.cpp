#include "StdAfx.h"
#include "BinaryOuts.h"
#include "Binary.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBinaryOuts::CBinaryOuts(void)
{
	m_strName = CXLanguageResourceAtsBase::g_sLangTxt_OutputValue/*L"¿ª³öÁ¿"*/;
}

CBinaryOuts::~CBinaryOuts(void)
{
	//DeleteAll();
}

CBaseObject* CBinaryOuts::Clone()
{
	CBinaryOuts* p = new CBinaryOuts();
	Copy(p);

	return p;
}