#include "stdafx.h"
#include "SttHtmlReportVIewInterface.h"

//2022-9-23  lijunqing
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../XLangResource_Native.h"


//#define CurrRptFileData_in_HtmlRptCmd
//////////////////////////////////////////////////////////////////////////
//CSttHtmlRptCmd
static int g_nSttHtmlRptCmdIndex = 0;

CSttHtmlRptCmd::CSttHtmlRptCmd()
{
	m_pTestMacroUI = NULL;
	m_strGbDatas = NULL;
	m_bIsFinish = g_nSttHtmlRptCmdIndex;
	g_nSttHtmlRptCmdIndex++;   //20230216  lijunqing zhangyq
}

CSttHtmlRptCmd::~CSttHtmlRptCmd()
{
	if (m_strGbDatas != NULL)
	{
		delete m_strGbDatas;
	}
}

//////////////////////////////////////////////////////////////////////////
//CSttHtmlReportVIewInterface
CSttHtmlReportVIewInterface::CSttHtmlReportVIewInterface()
{
	m_pCurrHtmlRptCmd = NULL;
	m_bCanExecCmd = FALSE;
	m_nRptFillMode = STT_RPT_FILL_MODE_RPT_SYSTEM;
}

CSttHtmlReportVIewInterface::~CSttHtmlReportVIewInterface()
{

}

//20230217 zhangyq
void stt_rpt_html_file_open(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strParentItemsPath
				  , const CString &strItemsID, CString &strCurrRptFileData)
{//
	CString strFile = pTestMacroUI->m_strReportFile;

	if (strFile.GetLength() == 0)
	{//2022-9-23  lijunqing
		if (g_theHtmlRptGenFactory != NULL)
		{
			CSttXmacroHtmlRptGenBase *pHtmlRptGen = g_theHtmlRptGenFactory->CreateHtmlRptGen(pTestMacroUI->m_strID);

			if (pHtmlRptGen != NULL)
			{
				pHtmlRptGen->GenHtml();
				pHtmlRptGen->GetHtml(strCurrRptFileData);
			}
		}
	}
	else
	{
		if (! stt_ui_OpenHtmlFile(strFile, strCurrRptFileData))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Open Report File [%s] error...."), strFile.GetString());
			return;
		}
	}

	//替换
	CString strXid;

	if (strParentItemsPath.GetLength() > 0)
	{
		strXid = strParentItemsPath + "$";
	}

	strXid = strXid + strItemsID;
	strCurrRptFileData.Replace("$XID$", strXid);
}

CSttHtmlRptCmd* CSttHtmlReportVIewInterface::AddInsertCmd(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strParentItemsPath, const CString &strItemsID, const char *strGbDatas, BOOL bExec)
{
	CSttHtmlRptCmd *pNew = new CSttHtmlRptCmd();
	pNew->m_strHtmlRptCmd = SttHtmlRptCmd_Insert;
	pNew->m_pTestMacroUI = pTestMacroUI;
	pNew->m_strGbDatas = (char*)strGbDatas;
	pNew->m_strItemsID = strItemsID;
	pNew->m_strParentPath = strParentItemsPath;
	//20230217 zhangyq
	stt_rpt_html_file_open(pTestMacroUI, strParentItemsPath, strItemsID, pNew->m_strCurrRptFileData);

	AddTail(pNew);

	if (bExec)
	{
		ExecCmd();
	}

	return pNew;
}

CSttHtmlRptCmd* CSttHtmlReportVIewInterface::AddInsertHeadCmd(const CString &strParentItemsPath, const CString &strItemsID, BOOL bExec)
{
	CSttHtmlRptCmd *pNew = new CSttHtmlRptCmd();
	pNew->m_strHtmlRptCmd = SttHtmlRptCmd_Insert;
	pNew->m_strItemsID = strItemsID;
	pNew->m_strParentPath = strParentItemsPath;

	stt_ui_OpenHtmlHeadFile(STT_REPORT_HEAD_HTML_FILE, pNew->m_strCurrRptFileData);

	AddHead(pNew);

	if (bExec)
	{
		ExecCmd();
	}

	return pNew;
}

CSttHtmlRptCmd* CSttHtmlReportVIewInterface::AddUpdateCmd(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strParentItemsPath, const CString &strItemsID, const char *strGbDatas, BOOL bExec)
{
	CSttHtmlRptCmd *pNew = new CSttHtmlRptCmd();
	pNew->m_strHtmlRptCmd = SttHtmlRptCmd_Update;
	pNew->m_pTestMacroUI = pTestMacroUI;
	pNew->m_strGbDatas = (char*)strGbDatas;
	pNew->m_strItemsID = strItemsID;
	pNew->m_strParentPath = strParentItemsPath;
	//20230217 zhangyq
	stt_rpt_html_file_open(pTestMacroUI, strParentItemsPath, strItemsID, pNew->m_strCurrRptFileData);

	AddTail(pNew);

	if (bExec)
	{
		ExecCmd();
	}

	return pNew;
}

CSttHtmlRptCmd* CSttHtmlReportVIewInterface::AddFillRptTitleCmd(const CString &strItemsID, const char *strGbDatas, BOOL bExec)
{
	CSttHtmlRptCmd *pNew = new CSttHtmlRptCmd();
	pNew->m_strHtmlRptCmd = SttHtmlRptCmd_FillTitle;
	pNew->m_strGbDatas = (char*)strGbDatas;
	pNew->m_strItemsID = strItemsID;

	AddTail(pNew);

	if (bExec)
	{
		ExecCmd();
	}

	return pNew;
}

void CSttHtmlReportVIewInterface::ExcuteNextCmd()
{
	if (m_pCurrHtmlRptCmd != NULL)
	{
		return;
	}

	if (GetCount() == 0)
	{
		return;
	}

	if (m_pCurrHtmlRptCmd == NULL)
	{
		m_pCurrHtmlRptCmd = GetHead();
	}

	if (m_pCurrHtmlRptCmd != NULL)
	{
		ExecCmd(m_pCurrHtmlRptCmd);
	}
}

void CSttHtmlReportVIewInterface::ExecCmd()
{
	if (GetCount() == 0)
	{
		return;
	}

	if (m_pCurrHtmlRptCmd != NULL)
	{
		return;
	}

	if (!m_bCanExecCmd)
	{
		return;
	}

	m_pCurrHtmlRptCmd = GetHead();
	ExecCmd(m_pCurrHtmlRptCmd);	
}

void CSttHtmlReportVIewInterface::ExecCmd(CSttHtmlRptCmd *pSttHtmlRptCmd)
{
	//20230217 zhangyq
	BOOL bCanExecNext = TRUE;

	if (pSttHtmlRptCmd->m_strHtmlRptCmd == SttHtmlRptCmd_Insert)
	{
		//bCanExecNext = FALSE;
		AddMacroTestReport(pSttHtmlRptCmd->m_strParentPath, pSttHtmlRptCmd->m_strItemsID, pSttHtmlRptCmd->m_pTestMacroUI, pSttHtmlRptCmd->m_strGbDatas, pSttHtmlRptCmd->m_strCurrRptFileData);
	}
	else if (pSttHtmlRptCmd->m_strHtmlRptCmd == SttHtmlRptCmd_Update/*SttHtmlRptCmd_Insert*/)//zhouhj 20220407
	{
		UpdateMacroTestReport(pSttHtmlRptCmd->m_strParentPath, pSttHtmlRptCmd->m_strItemsID, pSttHtmlRptCmd->m_strGbDatas, pSttHtmlRptCmd->m_strCurrRptFileData);
	}
	else if (pSttHtmlRptCmd->m_strHtmlRptCmd == SttHtmlRptCmd_FillTitle)//zhouhj 2023.7.27
	{
		FillReportTitle(pSttHtmlRptCmd->m_strItemsID, pSttHtmlRptCmd->m_strGbDatas);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("未知的网页报告执行命令(%s).")*/g_sLangTxt_Gradient_UnknownCommand.GetString(),pSttHtmlRptCmd->m_strHtmlRptCmd.GetString());
	}

	Remove(m_pCurrHtmlRptCmd);
	m_pCurrHtmlRptCmd = NULL;

	if (bCanExecNext)
	{
	ExcuteNextCmd();
	}
}

//2022-10-3  lijunqing报告填写模式
void CSttHtmlReportVIewInterface::SetRptFillModeByID(const CString &strRptFillModeID)
{
	if (strRptFillModeID == ID_STT_RPT_FILL_MODE_RPT_DATA_PATH)
	{
		m_nRptFillMode = STT_RPT_FILL_MODE_RPT_DATA_PATH;
	}
	else if (strRptFillModeID == ID_STT_RPT_FILL_MODE_RPT_MAP_DATAS)
	{
		m_nRptFillMode = STT_RPT_FILL_MODE_RPT_MAP_DATAS;
	}
	else if (strRptFillModeID == STT_RPT_FILL_MODE_RPT_SYSTEM)
	{
		m_nRptFillMode = STT_RPT_FILL_MODE_RPT_SYSTEM;
	}
	else
	{
		m_nRptFillMode = STT_RPT_FILL_MODE_RPT_SYSTEM;
	}
}

void CSttHtmlReportVIewInterface::InitReport(const CString &strReportFile)
{
	DeleteRptHtml("","");//zhouhj 2023.9.27 当传入的路径为空时,清空当前全部网页内容
	OpenReportFile(strReportFile);
}

extern long g_nLogDebugInfor;

//20230217 zhangyq 删掉打开报告部分，直接调用到AddInsertCmd和AddUpdateCmd
void CSttHtmlReportVIewInterface::AddMacroTestReport(const CString &strParentPath, const CString &strItemsID, CSttMacroTestUI_TestMacroUI *pTestMacroUI, const char *strGbDatas, const CString &strRptFileData)
{
	m_pTestMacroUI = pTestMacroUI;

	DeleteRptHtml(strParentPath, strItemsID);
	InsertRptHtml(strParentPath, strItemsID, strGbDatas, strRptFileData);
}

void CSttHtmlReportVIewInterface::DeleteMacroTestReport(const CString &strParentPath, const CString &strItemsID)
{
	DeleteRptHtml(strParentPath, strItemsID);
}

//20230217 zhangyq
void CSttHtmlReportVIewInterface::UpdateMacroTestReport(const CString &strParentPath, const CString &strItemsID, const CString &strGbDatas, const CString &strRptFileData)
{
	UpdateRptHtml(strParentPath,strItemsID,strGbDatas.GetString(), strRptFileData);
}


void CSttHtmlReportVIewInterface::FillReport(const CString &strParentPath, const CString &strItemID, CDvmValues *pValues)
{
	
}

void CSttHtmlReportVIewInterface::FillReport(const CString &strParentPath, const CString &strItemID, CDvmDataset *pDataset)
{

}


#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
void CSttHtmlReportVIewInterface::FillReport(const CString &strParentPath, const CString &strItemID, CSttReports *pSttReports)
{

}

#endif

#ifdef STT_MACRO_TEST_UI_USE_GUIDEBOOK
void CSttHtmlReportVIewInterface::FillReport(const CString &strParentPath, const CString &strItemID, CReports *pReports)
{

}
#endif
