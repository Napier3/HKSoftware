#include "stdafx.h"
#include "XLangResource_Win.h"

const CString CXLangResource_Win::g_strXLangRs_Test = _T("Lang_WinTest");

CXLangResource_Win::CXLangResource_Win()
{
    m_pXLangRsExe = &m_oXLangRs_Test;
    m_oXLangRs_Test.m_strID = g_strXLangRs_Test;
    m_oXLangRs_Test.m_strName = g_strXLangRs_Test;
}

CXLangResource_Win::~CXLangResource_Win()
{
    m_oXLangRs_Test.RemoveAll();
}


CXLangItem* CXLangResource_Win::rs_AddString(const CString &strID, CString *pstrString)
{
    CXLangItem *p = CXLanguage::AddString(strID, pstrString);

    m_oXLangRs_Test.AddTail(p);

    return p;
}


void CXLangResource_Win::InitLangRsByFile()
{
    CXLangResource_Native::InitLangRsByFile();

    InitLangRsByFileEx(&m_oXLangRs_Test, g_strXLangRs_Test);
}


void CXLangResource_Win::RegisterLanguageResource()
{
    CXLangResource_Native::RegisterLanguageResource();
	rs_AddString(g_sLangID_Win_SysConfig, &g_sLangTxt_Win_SysConfig);
	rs_AddString(g_sLangID_Win_Iec61850Config, &g_sLangTxt_Win_Iec61850Config);
	rs_AddString(g_sLangID_Win_PpxmlPath, &g_sLangTxt_Win_PpxmlPath);
	rs_AddString(g_sLangID_Win_PpxmlFilter, &g_sLangTxt_Win_PpxmlFilter);
	rs_AddString(g_sLangID_Win_CharTabTitle, &g_sLangTxt_Win_CharTabTitle);
	rs_AddString(g_sLangID_Win_CharEditTabTitle, &g_sLangTxt_Win_CharEditTabTitle);
}

void CXLangResource_Win::InitLangTxt()
{
	CXLangResource_Native::InitLangTxt();
	g_sLangID_Win_SysConfig = _T("Win_SysConfig");
	g_sLangTxt_Win_SysConfig = _T("系统参数配置");
	g_sLangID_Win_Iec61850Config = _T("Win_Iec61850Config");
	g_sLangTxt_Win_Iec61850Config = _T("IEC61850配置");
	g_sLangID_Win_PpxmlPath = _T("Win_PpxmlPath");
	g_sLangTxt_Win_PpxmlPath = _T("规约模板路径");
	g_sLangID_Win_PpxmlFilter = _T("Win_PpxmlFilter");
	g_sLangTxt_Win_PpxmlFilter = _T("规约模板文件 (*.ppxml)");
	g_sLangID_Win_CharTabTitle = _T("Win_CharTabTitle");
	g_sLangTxt_Win_CharTabTitle = _T("特性曲线图");
	g_sLangID_Win_CharEditTabTitle = _T("Win_CharEditTabTitle");
	g_sLangTxt_Win_CharEditTabTitle = _T("特性曲线编辑");
}

CString g_sLangID_Win_SysConfig;
CString g_sLangTxt_Win_SysConfig;
CString g_sLangID_Win_Iec61850Config;
CString g_sLangTxt_Win_Iec61850Config;
CString g_sLangID_Win_PpxmlPath;
CString g_sLangTxt_Win_PpxmlPath;
CString g_sLangID_Win_PpxmlFilter;
CString g_sLangTxt_Win_PpxmlFilter;
CString g_sLangID_Win_CharTabTitle;
CString g_sLangTxt_Win_CharTabTitle;
CString g_sLangID_Win_CharEditTabTitle;
CString g_sLangTxt_Win_CharEditTabTitle;