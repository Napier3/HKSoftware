#include "stdafx.h"
#include "SttMacroParaEditInterface.h"


CSttMacroParaEditInterface::~CSttMacroParaEditInterface()
{
	m_oDvmDataMaps.DeleteAll();			//20240715 huangliang
}

void CSttMacroParaEditInterface::InitUI(const CString &strGridFile)
{

}

//测试功能更新参数
void CSttMacroParaEditInterface::UpdateEventMsg(CEventResult *pCurrEventResult)
{

}

void CSttMacroParaEditInterface::ShowReport(CDvmValues *pValues)
{

}

// 20220317 zhouhj
void CSttMacroParaEditInterface::UpdateTestResource(BOOL bCreateChMaps)
{

}

void CSttMacroParaEditInterface::Debug()
{

}

BOOL CSttMacroParaEditInterface::IsHtmlView()
{
    return false;
}

long CSttMacroParaEditInterface::GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml)
{
    return 0;
}

UINT CSttMacroParaEditInterface::GetMacroEditViewType()
{
    return MACRO_EDIT_VIEW_TYPE_BASE;
}

void CSttMacroParaEditInterface::InitSpyToolWidget()
{

}

//20230210 zhangyq
void CSttMacroParaEditInterface::ProcessGbAfterGenTemplate(CSttGuideBook *pSttGuideBook)
{

}

void CSttMacroParaEditInterface::ProcessRptAfterGenTemplate(QSttReportViewHtml *pSttReportViewHtml)
{

}

CString CSttMacroParaEditInterface::ProcessItemID(const CString & strItemID,long nLoopIndex)
{
    return "";
}

BOOL CSttMacroParaEditInterface::IsInternationalMode()
{
    return FALSE;
}

//20240715 huangliang
void CSttMacroParaEditInterface::RecordDvmDataMap(CDataMaps *pDvmDataMaps)
{

}

