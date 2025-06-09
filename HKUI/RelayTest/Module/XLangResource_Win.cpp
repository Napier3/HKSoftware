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

	rs_AddString(g_sLangID_Win_IntelligentTestSystem, &g_sLangTxt_Win_IntelligentTestSystem);
	rs_AddString(g_sLangID_Win_VectorDiagram, &g_sLangTxt_Win_VectorDiagram);
	rs_AddString(g_sLangID_Win_StatusDiagram, &g_sLangTxt_Win_StatusDiagram);
	rs_AddString(g_sLangID_Win_PowerDiagram, &g_sLangTxt_Win_PowerDiagram);
	rs_AddString(g_sLangID_Win_WaveformDiagram, &g_sLangTxt_Win_WaveformDiagram);
	rs_AddString(g_sLangID_Win_InfoDiagram, &g_sLangTxt_Win_InfoDiagram);
	rs_AddString(g_sLangID_Win_ZTView, &g_sLangTxt_Win_ZTView);
	rs_AddString(g_sLangID_Win_LoadingTestInterface, &g_sLangTxt_Win_LoadingTestInterface);
	rs_AddString(g_sLangID_Win_SystemDiagram, &g_sLangTxt_Win_SystemDiagram);
	rs_AddString(g_sLangID_Win_WiringDiagram, &g_sLangTxt_Win_WiringDiagram);
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

	//2024-10-22 wuxinyi
	g_sLangID_Win_IntelligentTestSystem = _T("Win_IntelligentTestSystem");
	g_sLangTxt_Win_IntelligentTestSystem = _T("智能测试系统");
	g_sLangID_Win_VectorDiagram = _T("Win_VectorDiagram");
	g_sLangTxt_Win_VectorDiagram = _T("矢量图");
	g_sLangID_Win_StatusDiagram = _T("Win_StatusDiagram");
	g_sLangTxt_Win_StatusDiagram = _T("状态图");
	g_sLangID_Win_PowerDiagram = _T("Win_PowerDiagram");
	g_sLangTxt_Win_PowerDiagram = _T("功率图");
	g_sLangID_Win_WaveformDiagram = _T("Win_WaveformDiagram");
	g_sLangTxt_Win_WaveformDiagram = _T("波形图");
	g_sLangID_Win_InfoDiagram = _T("Win_InfoDiagram");
	g_sLangTxt_Win_InfoDiagram = _T("信息图");
	g_sLangID_Win_ZTView = _T("Win_ZTView");
	g_sLangTxt_Win_ZTView = _T("ZT视图");
	g_sLangID_Win_LoadingTestInterface = _T("Win_LoadingTestInterface");
	g_sLangTxt_Win_LoadingTestInterface = _T("正在加载测试功能界面,请稍后...");
	g_sLangID_Win_SystemDiagram = _T("Win_SystemDiagram");
	g_sLangTxt_Win_SystemDiagram = _T("系统图");
	g_sLangID_Win_WiringDiagram = _T("Win_WiringDiagram");
	g_sLangTxt_Win_WiringDiagram = _T("接线图");
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
CString g_sLangTxt_Win_CharEditTabTitle;//2024-10-22 wuxinyi
CString g_sLangID_Win_IntelligentTestSystem;
CString g_sLangTxt_Win_IntelligentTestSystem;

CString g_sLangID_Win_VectorDiagram;
CString g_sLangTxt_Win_VectorDiagram;

CString g_sLangID_Win_StatusDiagram;
CString g_sLangTxt_Win_StatusDiagram;

CString g_sLangID_Win_PowerDiagram;
CString g_sLangTxt_Win_PowerDiagram;

CString g_sLangID_Win_WaveformDiagram;
CString g_sLangTxt_Win_WaveformDiagram;

CString g_sLangID_Win_InfoDiagram;
CString g_sLangTxt_Win_InfoDiagram;

CString g_sLangID_Win_ZTView;
CString g_sLangTxt_Win_ZTView;

CString g_sLangID_Win_LoadingTestInterface;
CString g_sLangTxt_Win_LoadingTestInterface;

CString g_sLangID_Win_SystemDiagram;
CString g_sLangTxt_Win_SystemDiagram;

CString g_sLangID_Win_WiringDiagram;
CString g_sLangTxt_Win_WiringDiagram;