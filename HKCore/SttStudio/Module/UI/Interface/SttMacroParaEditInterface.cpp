#include "stdafx.h"
#include "SttMacroParaEditInterface.h"


CSttMacroParaEditInterface::~CSttMacroParaEditInterface()
{
	m_oDvmDataMaps.DeleteAll();			//20240715 huangliang
}

void CSttMacroParaEditInterface::InitUI(const CString &strGridFile)
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
	if(pDvmDataMaps == NULL)
		return ;
	m_oDvmDataMaps.DeleteAll();
	m_oDvmDataMaps.m_strID = STT_SETTING_DVMDATA_MAP_ID;

	CDvmData *pObject = NULL;
	POS pos = pDvmDataMaps->GetHeadPosition();
	while(pos)
	{
		pObject = (CDvmData *)pDvmDataMaps->GetNext(pos);
		if(pObject != NULL)
		{
			CDvmData *pNewDvm = (CDvmData *)pObject->Clone();
			m_oDvmDataMaps.AddTail(pNewDvm);
		}
	}
}

