#include "SttTestCtrlCntrBase.h"
#include "../UI/Interface/SttHtmlViewApi.h"
#include "../SttTestResourceMngr/TestResource/SttTestResource_4U3I.h"
#include "../SttTestResourceMngr/TestResource/SttTestResource_6U6I.h"
#include "../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../SttTestResourceMngr/TestResource/SttTestResource_Async.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"

#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdAi/GbWzdAiTool.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"

extern long g_nLogDebugInfor;

extern void Stt_Global_GetBinBoutMaxWidth();	//20241012 huangliang 获取开入开出映射后的最大宽度

long CSttTestCtrlCntrMsgInterface::OnUpdateSyncTime(CDataGroup *pSyncTime){	return 0; };
void CSttTestCtrlCntrMsgInterface::OnReport_ReadDevice(CDataGroup *pDeviceGroup){}
void CSttTestCtrlCntrMsgInterface::OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){};

CSttTestCtrlCntrBase::CSttTestCtrlCntrBase()
{
    m_pCurrTestItem = NULL;
	m_pTestCtrlCntrMsg = NULL;
	m_pCurrTestMacroUI = NULL;
	m_pSttTestResouce = NULL;
	
	OpenReportHead();//读取报告头文件，因为只需要调用一次，所以考虑放在构造函数中，后续再改 sf 20220218
}

CSttTestCtrlCntrBase::~CSttTestCtrlCntrBase()
{
	if (m_pSttTestResouce != NULL)
	{
		delete m_pSttTestResouce;
		m_pSttTestResouce = NULL;
	}
}

void CSttTestCtrlCntrBase::SetCurrTestItem(CExBaseObject *pCurrTestItem)
{
    if(pCurrTestItem != NULL)
    {
        m_pCurrTestItem = pCurrTestItem;
    }
}

CExBaseObject* CSttTestCtrlCntrBase::GetCurrTestItem()
{ 
	return m_pCurrTestItem;
}

CExBaseObject* CSttTestCtrlCntrBase::GetGuideBook()
{
	return NULL;
}

BOOL CSttTestCtrlCntrBase::StartTest(CDataGroup *pCurrentUIParas)
{
	return FALSE;
}

BOOL CSttTestCtrlCntrBase::StopTest()
{
	return FALSE;
}

long CSttTestCtrlCntrBase::SendManuTrigger()
{
	return 0;
}

void CSttTestCtrlCntrBase::GetAllItemsByID(const CString &strItemID, CExBaseList &oItemList)
{

}

//2022-3-29  lijunqing
long CSttTestCtrlCntrBase::TestItem(const CString &strItemPath)
{
	return 0;
}

long CSttTestCtrlCntrBase::TestFrom(const CString &strItemPath)
{
	return 0;
}

long CSttTestCtrlCntrBase::GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml,const CString &strParentPath)	{	return 0;	}

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
void CSttTestCtrlCntrBase::FillReport(CSttReports *pSttReports){}
#endif
void CSttTestCtrlCntrBase::GetEventInfo(CExBaseList& oInfoList){};
void CSttTestCtrlCntrBase::NewTest(CDataGroup *pDevice, CDataGroup *pTestApp, CDataGroup *pCommConfig){};

void CSttTestCtrlCntrBase::ConnectAtsServer()
{

}

void CSttTestCtrlCntrBase::OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	m_pCurrTestMacroUI = pTestMacroUI;

	if (pTestMacroUI == NULL)
	{
		return;
	}


	m_oTestMacroUI_Paras.DeleteAll();

	if (pTestMacroUI->IsUIWeb()||(!pTestMacroUI->m_strUI_ParaFile.IsEmpty()))//20220803 zhouhj 原生界面也采用此方式读取参数
	{
		if (g_nLogDebugInfor == 1)		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** begin OpenParasFile >>");
		stt_ui_OpenParasFile(pTestMacroUI->m_strUI_ParaFile, &m_oTestMacroUI_Paras);
		if (g_nLogDebugInfor == 1)		CLogPrint::LogString(XLOGLEVEL_TRACE, "***** end  OpenParasFile >>");

		//2023-2-7  lijunqing 根据装置模型智能生成模板参数
		if (g_theGbWzdAiTool != NULL)
		{
			CString strAiFile = stt_ui_GetParasAiFile(pTestMacroUI->m_strUI_ParaFile);
			g_theGbWzdAiTool->GbWzdAi(strAiFile, &m_oTestMacroUI_Paras);
			
			//调试模式下，查看智能匹配的结果
			//stt_ui_SaveParasFile("GbWzdAiTool_After_Ai.xml", &m_oTestMacroUI_Paras);
		}
	}
	
	if (g_nLogDebugInfor == 1)		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenHdRsFile >>");
	stt_OpenHdRsFile(pTestMacroUI->m_strHdRsFile);
	if (g_nLogDebugInfor == 1)		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end  OpenHdRsFile >>");


}

CString CSttTestCtrlCntrBase::GetCurrMacroUIParasFilePath()
{
	if (m_pCurrTestMacroUI == NULL)
	{
		return "";
	}

	CString strPath;
	strPath = _P_GetDBPath();
	strPath += "atsgen/";
	strPath += m_pCurrTestMacroUI->m_strUI_ParaFile;
	return strPath;
}

void CSttTestCtrlCntrBase::stt_OpenHdRsFile(const CString &strHdRsFile)
{
	if ((m_pSttTestResouce != NULL)&&(m_pSttTestResouce->GetChMapFileName() == strHdRsFile))//如果软件资源与当前的一致,则返回
	{
		return;
	}

	if (m_pSttTestResouce != NULL)
	{
		delete m_pSttTestResouce;
	}

	if (strHdRsFile == STT_TEST_RESOURCE_FILENAME_ASYNC)
	{
		m_pSttTestResouce = new CSttTestResource_Async;
	}
	else if (strHdRsFile == STT_TEST_RESOURCE_FILENAME_SYNC)
	{
		m_pSttTestResouce = new CSttTestResource_Sync;
	}
	else if (strHdRsFile == STT_TEST_RESOURCE_FILENAME_4U3I)
	{
		m_pSttTestResouce = new CSttTestResource_4U3I;
	}
	else if (strHdRsFile == STT_TEST_RESOURCE_FILENAME_6U6I)
	{
		m_pSttTestResouce = new CSttTestResource_6U6I;
	}
	else
		m_pSttTestResouce = new CSttTestResource_4U3I;

	g_oSttTestResourceMngr.m_pTestResouce = m_pSttTestResouce;
	g_oSttTestResourceMngr.CreateChMaps();
	g_oSttTestResourceMngr.InitLocalSysPara();
	g_oSttTestResourceMngr.ValidHardRsChMaps();
	g_oSttTestResourceMngr.CreateSoftRsCh();
	g_oSttTestResourceMngr.CreateRtDataMngr();
	g_oSttTestResourceMngr.m_oIecDatasMngr.UpdateFT3ChsType(g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nIecFormatMeas);//20240117 suyang 初始化时转换FT3通道类型
//	g_theTestCntrFrame->m_pSttTestResource = m_pSttTestResouce;

	//20241012 huangliang 读取配置信号后，获取开入开出映射后的最大宽度
	Stt_Global_GetBinBoutMaxWidth();
}



void CSttTestCtrlCntrBase::InitDefaultHdRs()
{
	stt_OpenHdRsFile(STT_TEST_RESOURCE_FILENAME_SYNC);
}

void CSttTestCtrlCntrBase::GetMacroUI_GbItems(CString &strMacroUI_Items)
{
	//获取m_pCurrEditMacroItems的概要信息
}

void CSttTestCtrlCntrBase::GetReportHeadFile(CString &strFile)
{
	strFile = stt_ui_GetParasFile("ReportHead_Paras.xml");
}

void CSttTestCtrlCntrBase::OpenReportHead()
{
	CString strPath;
	GetReportHeadFile(strPath);

	dvm_IncGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	m_oTestReportHead.OpenXmlFile(strPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(&m_oTestReportHead,_T("ReportHead_Paras.xml"));
#endif

	dvm_DecGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CSttTestCtrlCntrBase::SaveReportHead()
{
	CString strPath;
	GetReportHeadFile(strPath);
	m_oTestReportHead.SaveXmlFile(strPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

//模板生成相关的接口
//单个功能的模板生成
long CSttTestCtrlCntrBase::Ats_GenerateTemplate()
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_CreateTemplate()
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_UpdateReportHead()
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_UpdateCharacteristic(CExBaseList *pParent)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID
											 , CDataGroup *pCommCmd, const CString &strDvmFile, const CString strTestClass, long nRepeatTimes
											 , long nRptTitle, long nTitleLevel, long nSynMode)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_SetItemPara(const CString &strItemPath, const CString& strMacroID)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_SetItemPara_RsltExpr(const CString &strItemPath, const CString& strRlstExpr)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_AddMacro(const CString &strParentItemPath, const CString &strItemName, const CString &strItemID, const CString &strMacroID, const CString &strItemParas)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_UpdateItem(const CString &strItemPath)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_UpdateItem(const CString &strItemPath, const CString &strItemParas, const CString &strItemType)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_QueryItem(const CString &strItemPath)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_SetParameter(const CString &strMacroID, CDataGroup *pParas)
{
	return 0;
}

//2022-3-29  lijunqing
long CSttTestCtrlCntrBase::Ats_NewItems(CExBaseList *pParent, CExBaseObject *pItems)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_EditItems(CExBaseList *pParent, CExBaseObject *pItems, const CString &strItemsID)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_DeleteItems(CExBaseList *pParent, CExBaseObject *pItems)
{
	return 0;
}

//2022-10-20  shaolei
long CSttTestCtrlCntrBase::Ats_MoveUpItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_MoveDownItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes)
{
	return 0;
}

//2023-2-1  shaolei
long CSttTestCtrlCntrBase::Ats_ItemPaste(CExBaseList *pParent, const CString& strSrcItemPath)
{
	return 0;
}

//2023-8-11 shaolei //添加测试前、后通讯组合
long CSttTestCtrlCntrBase::Ats_CmdAddGrp(CExBaseList *pParent, long nAftUseReset, long nAddCommCmd)
{
	return 0;
}

//2023-8-14 shaolei  //导入模型文件(模型映射)
long CSttTestCtrlCntrBase::Ats_ImportDvmFile(const CString &strDvmFile, long nIsDvmMap)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_ImportDvmFile(CDvmDevice *pDvmDevice, long nIsDvmMap)
{
	return 0;
}

//2023-8-28 shaolei  //遥测参数映射
long CSttTestCtrlCntrBase::Ats_AinDataMap(CDataGroup *pMapParas, CDataGroup *pAinDevRatios)
{
	return 0;
}

//2023-8-29 shaolei  //配置装置
long CSttTestCtrlCntrBase::Ats_ConfigDevice(CDataGroup *pCommCfg)
{
	return 0;
}

//2022-08-31 shaolei
long CSttTestCtrlCntrBase::Ats_GenrateItems_CmdWzd(CExBaseList *pParent, CDataGroup *pCommCmd, const CString &strMacroName, const CString &strTestClass, long nSynMode)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_GenrateItems_CmdAdd(const CString &strParentItemPath, CDataGroup *pCommCmd, CSttContents *pContents)
{
	return 0;
}

//2024.6.28 zhouhj添加单个电气量测试项目
long CSttTestCtrlCntrBase::Ats_AddOneMacroItem(CDataGroup *pMacroParas,const CString &strItemName,const CString &strItemID,const CString &strItemsPath,
	long nAddPos, const CString &strMacroID, const CString &strTestMacroUI_ID)
{
	return 0;
}
// 
// long CSttTestCtrlCntrBase::Ats_UpdateOneMacroItem(CDataGroup *pMacroParas,long nSelect,const CString &strItemsPath,const CString &strMacroID)
// {
// 	return 0;
// }

long CSttTestCtrlCntrBase::Ats_UpdateOneMacroItem(CSttMacroTest *pSttMacroTest)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_DeleteOneItem(const CString &strItemID,const CString &strParentItemsPath)
{
	return 0;
}

long CSttTestCtrlCntrBase::Ats_GenerateItems_AddSafety(CDataGroup *pParas, CExBaseList *pListDatas, CExBaseList *pMsgs)
{
	return 0;
}
//模板、报告数据等相关的接口  2022-3-14  lijunqing
CString CSttTestCtrlCntrBase::SaveTestFile(const CString &strRealPath, const CString &strTemplateFileName)
{
	return "";
}
CString CSttTestCtrlCntrBase::SaveSysTemplateFile(const CString &strTemplateFileName)
{
	return "";
}
CString CSttTestCtrlCntrBase::SaveTemplateFile(const CString &strTemplateFileName)
{
	return "";
}

BOOL CSttTestCtrlCntrBase::SaveTemplate(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas, long nSynMode)
{
	return FALSE;
}

BOOL CSttTestCtrlCntrBase::SaveTest(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas, long nSynMode)
{
	return FALSE;
}

BOOL CSttTestCtrlCntrBase::ExportWordRpt(const CString &strPath, const CString &strFileName, CDataGroup *pParas)
{
	return FALSE;
}

BOOL CSttTestCtrlCntrBase::OpenTemplate(const CString &strFileWithPath, const CString &strDvmFile)
{
	return FALSE;
}

BOOL CSttTestCtrlCntrBase::OpenTest(const CString &strFileWithPath, const CString &strDvmFile)
{
	return FALSE;
}

//清除报告数据，形参是预留的参数，可以不传递参数
BOOL CSttTestCtrlCntrBase::ClearReportsRslts(CDataGroup *pParas)
{
	return FALSE;
}

//2022-4-14 lijunqing
void CSttTestCtrlCntrBase::Ats_IecDetect(long bEnable)
{
	
}

void CSttTestCtrlCntrBase::Ats_IecRecord(CDataGroup *pIecRecordParas)
{
	
}


void CSttTestCtrlCntrBase::Ats_BinRecord(CDataGroup *pBinRecordParas)
{

}

void CSttTestCtrlCntrBase::Ats_BinConfig(CDataGroup *pBinConfigParas)
{

}

//2022-3-11 lijunqing
void CSttTestCtrlCntrBase::OpenMacroTestUI_ParaFile(long nFileIndex)
{
	if (m_pCurrTestMacroUI == NULL)
	{
		return;
	}

	CString strFile = m_pCurrTestMacroUI->m_strUI_ParaFile;

	if (nFileIndex > 0)
	{
		strFile = GetFileTitleFromFilePath(strFile);
		strFile.AppendFormat("%d", nFileIndex);
		strFile += ".xml";
	}

	stt_ui_OpenParasFile(strFile, &m_oTestMacroUI_Paras);
}

void CSttTestCtrlCntrBase::SaveMacroTestUI_ParaFile(const CString &strTitleAdd)
{
	if (m_pCurrTestMacroUI == NULL)
	{
		return;
	}

	CString strFile = m_pCurrTestMacroUI->m_strUI_ParaFile;

	if (strTitleAdd.GetLength() > 0)
	{
		strFile = GetFileTitleFromFilePath(strFile);
		strFile += strTitleAdd;
		strFile += ".xml";
	}

	stt_ui_SaveParasFile(strFile, &m_oTestMacroUI_Paras);
}

void CSttTestCtrlCntrBase::SaveCurrTestMacroUITemplateFile()
{
	if (m_pCurrTestMacroUI == NULL)
	{
		return;
	}

	CString strFile = SaveSysTemplateFile(m_pCurrTestMacroUI->m_strID);
}

long CSttTestCtrlCntrBase::GetGbItemCount()
{
	ASSERT(FALSE);

	return 0;
}

//是否已有测试任务，以是否创建测试（创建CSttDevice）为判断依据
BOOL CSttTestCtrlCntrBase::IsHasTestTask()
{
	ASSERT(FALSE);

	return FALSE;
}
