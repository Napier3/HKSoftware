#include "stdafx.h"
#include "XLangResource_SttNativeMain.h"

const CString CXLangResource_SttNativeMain::g_strXLangRs_Test = _T("Lang_SttNativeMain");

CXLangResource_SttNativeMain::CXLangResource_SttNativeMain()
{
    m_pXLangRsExe = &m_oXLangRs_Test;
    m_oXLangRs_Test.m_strID = g_strXLangRs_Test;
    m_oXLangRs_Test.m_strName = g_strXLangRs_Test;
}

CXLangResource_SttNativeMain::~CXLangResource_SttNativeMain()
{
    m_oXLangRs_Test.RemoveAll();
}


CXLangItem* CXLangResource_SttNativeMain::rs_AddString(const CString &strID, CString *pstrString)
{
    CXLangItem *p = CXLanguage::AddString(strID, pstrString);

    m_oXLangRs_Test.AddTail(p);

    return p;
}


void CXLangResource_SttNativeMain::InitLangRsByFile()
{
    CXLanguageResourceAtsBase::InitLangRsByFile();

    InitLangRsByFileEx(&m_oXLangRs_Test, g_strXLangRs_Test);
}


void CXLangResource_SttNativeMain::RegisterLanguageResource()
{
	CXLanguageResourceAtsBase::RegisterLanguageResource();
	rs_AddString(g_sLangID_Native_ChooseOpenFile, &g_sLangTxt_Native_ChooseOpenFile);
	
}CString CXLangResource_SttNativeMain::g_sLangID_Native_ChooseOpenFile = _T("Native_ChooseOpenFile");
CString CXLangResource_SttNativeMain::g_sLangTxt_Native_ChooseOpenFile = _T("选择需要打开的文件");