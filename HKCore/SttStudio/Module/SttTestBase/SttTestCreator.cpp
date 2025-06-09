#include "StdAfx.h"
#include "SttTestCreator.h"

#ifndef NOT_USE_XLANGUAGE
#include "../../../Module/XLanguage/XLanguageMngr.h"
#endif

CSttTestCreator::CSttTestCreator(const CString &strPxAppName, const CString &strName, const CString &strID, PFNCREATE* pFunCreate)
{
	m_strPxAppID = strPxAppName;
	m_strName = strName;
	m_strID = strID;
	m_pFunCreate = pFunCreate;
}

CSttTestCreator::~CSttTestCreator(void)
{

}

CSttTestBase* CSttTestCreator::Create(BOOL bBuildTrans)
{
	CSttTestBase *pTest = m_pFunCreate();
	pTest->m_strPxAppName = m_strPxAppID;
//	pTest->SetFilePostFix(m_strFilePostFix);
//	pTest->RegisterParas();

	if (!bBuildTrans)
	{
		return pTest;
	}

#ifndef NOT_USE_XLANGUAGE
    if (CXLanguageMngr::g_pXLanguageMngr == NULL)
	{
		return pTest;
	}

    //¶àÓïÑÔ×ª»¯
// 	CXLanguage oXLanguage;
	CExBaseList oListParas;
	oListParas.AddTail(pTest->GetFaultParas());
	oListParas.AddTail(pTest->GetFaultParasEx());
	oListParas.AddTail(pTest->GetSysParas());
	oListParas.AddTail(pTest->GetResults());
	oListParas.AddTail(pTest->GetResultsEx());
	oListParas.AddTail(pTest->GetSearchResults());
	oListParas.AddTail(pTest->GetBaseSpyParas());

	xlang_TranslateByResourceFileEx(&oListParas, _T("TestMacro.xml"));
	oListParas.RemoveAll();
#endif

	return pTest;
}
