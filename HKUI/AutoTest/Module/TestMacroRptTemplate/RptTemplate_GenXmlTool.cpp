#include "StdAfx.h"
#include "RptTemplate_GenXmlTool.h"
#include "..\..\..\SttStudio\Module\UI\Config\MacroTestUI\SttMacroTestUI_TestMacroUIDB.h"
#include "RptTemp_Png.h"

CRptTemplate_GenXmlTool::CRptTemplate_GenXmlTool(void)
{
	m_pRptTemp_GuideBook = NULL;
	m_pRptTemp_TestMacroUiRpt = NULL;
	m_pGuideBook = NULL;
	m_bCurrentItems_Ain = FALSE;
	m_pReportHeadParas = NULL;
	m_pRptHeadTemplate = NULL;

	CString strSysPath;
	strSysPath = _P_GetInstallPath();
	strSysPath += _T("STT/");
	InitGbGenSysPath(strSysPath); 
	InitRptTemplateCfg();
	m_pCurrUpdateItems = NULL;
}

CRptTemplate_GenXmlTool::~CRptTemplate_GenXmlTool(void)
{
	RemoveAll();

	if (m_pRptTemp_GuideBook != NULL)
	{
		delete m_pRptTemp_GuideBook;
		m_pRptTemp_GuideBook = NULL;
	}

	if (m_pRptTemp_TestMacroUiRpt != NULL)
	{
		delete m_pRptTemp_TestMacroUiRpt;
		m_pRptTemp_TestMacroUiRpt = NULL;
	}
}

void CRptTemplate_GenXmlTool::InitRptTemplateCfg()
{
	m_oRptTemplateCfg.OpenReportTemplateConfigFile();
}

void CRptTemplate_GenXmlTool::InitGbGenSysPath(const CString &strSysPath)
{
	CString strPath = strSysPath;

	if (strPath.GetLength() == 0)
	{
		strPath = _P_GetSystemPath();
	}

	m_strConfigPath = strPath;
	m_strConfigPath += g_pszKeyConfig;
	m_strConfigPath += _T("/");

	m_strDbPath = strPath;
	m_strDbPath += g_pszKeyDB;
	m_strDbPath += _T("/");

	m_strWorkSpacePath = strPath;
	m_strWorkSpacePath += g_pszKeyWorkspace;
	m_strWorkSpacePath += _T("/");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//以下是导出XML格式的报告数据文件的部分
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Dat(const CString &strXmlFile, CGuideBook *pGuideBook)
{
	if (pGuideBook == NULL)
	{
		return FALSE;
	}

	m_strXmlFile_Dat = strXmlFile;
	BOOL bRet = TRUE;

	if (m_pRptTemp_GuideBook == NULL)
	{
		m_pRptTemp_GuideBook = new CRptTemp_GuideBook();
	}

	m_pRptTemp_GuideBook->DeleteAll();

	//todo：待处理报告头，暂时不处理

	m_pGuideBook = pGuideBook;
	CDevice *pDevice = pGuideBook->GetDevice();
	bRet = GenRpt_Xml_Dat_Device(m_pRptTemp_GuideBook, pDevice);

	m_pRptTemp_GuideBook->SaveXmlFile(m_strXmlFile_Dat, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Dat_Device(CRptTemp_GuideBook *pRptTemp_GuideBook, CDevice *pDevice)
{
	if (pDevice == NULL || pRptTemp_GuideBook == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pItems = (CItems *)pObj;

		if (pItems->m_nSelect == 0)
		{
			continue;
		}

		if (! GenRpt_Xml_Dat_Items(pRptTemp_GuideBook, pItems))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Dat_Items(CExBaseList *pParent, CItems *pItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return FALSE;
	}

	if (pItems->IsTypeRootNode())
	{
		return GenRpt_Xml_Items_Dat_RootNode(pParent, pItems);
	}

	return GenRpt_Xml_Items_Dat_Normal(pParent, pItems);
}

//递归调用，只针对人工创建的CItems
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_Normal(CExBaseList *pParent, CItems *pItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return FALSE;
	}

	//对于人工创建的CItems节点，只需要导出子的CItems即可
	//因为就算人工创建的CItems节点，子对象包含CMacroTest，也不知道需要导出的报告数据有哪些
	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems);

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	POS pos = pItems->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pChildItems = (CItems *)pObj;

		if (pChildItems->m_nSelect == 0)
		{
			continue;
		}

		if (pChildItems->IsTypeRootNode())
		{
			if (! GenRpt_Xml_Items_Dat_RootNode(pRptTemp_Items, pChildItems))
			{
				bRet = FALSE;
			}
		}
		else
		{
			if (! GenRpt_Xml_Items_Dat_Normal(pRptTemp_Items, pChildItems))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_RootNode(CExBaseList *pParent, CItems *pItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return FALSE;
	}

	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems);

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	IsCurrentItemsAin(pItems->m_strStxmlFile);
	CSttMacroTestUI_TestMacroUIs *pUIs = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->GetTestMacroUIs();
	CSttMacroTestUI_TestMacroUI *pUI = (CSttMacroTestUI_TestMacroUI *)pUIs->FindByID(pItems->m_strStxmlFile);

	if (pUI == NULL)
	{
		return FALSE;
	}

	CRptTemp_TestMacroUiRptDef oRptDef;
	CString strFile;
	strFile = GetDBPath(); 
	strFile += STT_MACROTEST_UI_REALPATH_ATSGEN;
	strFile += _T("/");
	strFile += pUI->m_strrpt_Data_CfgFile;
	BOOL bRet = TRUE;

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件【%s】不存在"), strFile.GetString());
		return FALSE;
	}

	CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	bRet = oRptDef.OpenXmlFile(strFile, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);
	CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	if (!bRet)
	{
		return FALSE;
	}

	CString strItemPath;
	strItemPath = pItems->GetIDPathEx(GBCLASSID_DEVICE, FALSE);

	if (!GenRpt_Xml_Items_Dat_RootNode_UpdateItemsTec(&oRptDef, strItemPath))
	{
		//return FALSE;
	}

	bRet = GenRpt_Xml_Items_Dat_RootNode_Items(&oRptDef, pRptTemp_Items, pItems);

	return bRet;
}

/*
<group id="items-tecs" data-type="items-tecs">【技术要求编辑+数据小数位数配置】
<group id="item-path" data-type="items-tec">【一个group，代表一个项目的技术要求+报告数据保留小数位数，id填写为实际项目路径】
<data id="rpt_tec_data1" value=""/>【技术要求，id用固定前缀：“rpt_tec_”。技术要求可以有多个】
<data name="动作值小数点位数" data-type="int" id="rpt_precision_data1" value="1" min="0" max="4"/>【报告数据小数位数编辑，id用固定前缀：“rpt_precision_”。小数位数编辑可以有多个】
</group>
<group id="item-path" data-type="items-tec">
<data id="rpt_tec_data1" value=""/>
</group>
<group id="item-path" data-type="items-tec">
<data id="rpt_tec_data1" value=""/>
</group>
……
</group>
*/
//更新“技术要求” + “报告数据保留小数位数”数据接口
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_RootNode_UpdateItemsTec(CRptTemp_TestMacroUiRptDef *pRptDef, const CString &strItemPath)
{
	if (pRptDef == NULL)
	{
		return FALSE;
	}

	if (m_pGuideBook == NULL)
	{
		return FALSE;
	}

	CDataGroup *pSrc = m_pGuideBook->GetItemsTec();
	CDataGroup *pDest = pRptDef->GetItemsTec();

	if (pDest == NULL)
	{
		return TRUE;
	}

	if (pSrc == NULL)
	{
		return FALSE;
	}

	CDataGroup *pItemTec = (CDataGroup *)pSrc->FindByID(strItemPath);

	if (pItemTec == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到项目【%s】对应的技术要求 + 报告数据保留小数位数配置"), strItemPath.GetString());
		return FALSE;
	}

	pDest->InitDataValues(pItemTec, FALSE);

	return TRUE;
}

//rootnode下，可以只考虑items、macrotest和char-macro-items
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_RootNode_Items(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CItems *pItems)
{
	if (pRptItems == NULL || pRptDef == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	POS pos = pItems->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pItemsChild = (CItems *)pObj;

			if (pItemsChild->m_nSelect == 0)
			{
				continue;
			}

			if (pItemsChild->m_strID == STT_ITEMS_ID_BEFORETEST
				|| pItemsChild->m_strID == STT_ITEMS_ID_AFTERTEST)
			{
				continue;  //过滤掉测试前、测试后
			}

			CRptTemp_Items *pRptTemp_ItemsChild = GenRpt_Xml_NewItems(pRptItems, pItemsChild);

			if (pRptTemp_ItemsChild == NULL)
			{
				bRet = FALSE;
				continue;
			}

			if (! GenRpt_Xml_Items_Dat_RootNode_Items(pRptDef, pRptTemp_ItemsChild, pItemsChild))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == GBCLASSID_MACROTEST)
		{
			CMacroTest *pMacroTest = (CMacroTest *)pObj;

			if (pMacroTest->m_nSelect == 0)
			{
				continue;
			}

			if (! GenRpt_Xml_Items_Dat_RootNode_MacroTest(pRptDef, pRptItems, pMacroTest))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == GBCLASSID_MACROCHARITEMS)
		{
			CMacroCharItems *pMacroCharItems = (CMacroCharItems *)pObj;

			if (pMacroCharItems->m_nSelect == 0)
			{
				continue;
			}

			if (! GenRpt_Xml_Items_Dat_RootNode_MacroCharItems(pRptDef, pRptItems, pMacroCharItems))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

//电气量项目的父节点，有两种：CItems，CMacroCharItems。应该区分处理
//处理父项目是CItems的电气量
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_RootNode_MacroTest(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroTest *pMacroTest)
{
	CString strMacroID = pMacroTest->GetTestMacroID();
	CExBaseList oListParas;
	GetMacroTest_AllParas(&oListParas, pMacroTest);
	CRptTemp_MacroTest *pRptTemp_MacroTestDef = pRptDef->FindMacroTestByMacroID(strMacroID, &oListParas);

	if (pRptTemp_MacroTestDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，找不到macrotest节点【%s】"), strMacroID.GetString());
		//找不到，可能是不需要导出报告数据的电气量项目，所以返回TRUE
		return TRUE;
	}

	CRptTemp_ReportsDef* pRptTemp_ReportsDef = pRptTemp_MacroTestDef->GetRpeortsDef();

	if (pRptTemp_ReportsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，macrotest节点【%s】未定义reports-def"), strMacroID.GetString());
		return FALSE;
	}

	//此处待处理：报告数据不一定来自pMacroTest，有可能来自下面的通讯命令项目
	CRptTemp_MacroTest* pRptMacroTestNew = GenRpt_Xml_NewMacroTest(pRptItems, pMacroTest);
	CExBaseList oRptLists;

	if (pRptTemp_ReportsDef->m_strData_Path.GetLength() > 0)
	{
		CGbItemBaseList oDestList;
		//通过项目相对路径，查找项目
		pMacroTest->SelectItems(pRptTemp_ReportsDef->m_strData_Path, oDestList);
		long nCount = oDestList.GetCount();

		if (nCount != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("项目【%s】查找结果不唯一！找到【%d】个目标项目"), pRptTemp_ReportsDef->m_strData_Path.GetString(), nCount);
			oDestList.RemoveAll();
			return FALSE;
		}

		CGbItemBase *pDestItem = (CGbItemBase *)oDestList.GetHead();
		GetItemReports(&oRptLists, pDestItem);
		oDestList.RemoveAll();
	}
	else
	{
		GetItemReports(&oRptLists, pMacroTest);
	}

	//此处可能需要修改。预留的形参pMacroTest。暂时没有用到，若需要用到，此处可能得传具体的项目。如pDestItem
	BOOL bRet = GenRpt_Xml_MacroTest_Dat_Reports(pRptTemp_ReportsDef, &oRptLists, pRptMacroTestNew, pMacroTest);
	oRptLists.RemoveAll();
	return bRet;
}

//处理父项目是CMacroCharItems的电气量
//形参1：报告数据配置文件中定义的macro-char-items模板；
//形参2：实例化的macro-char-items节点
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_RootNode_MacroTest(CRptTemp_MacroCharItems *pMacroCharItemsDef, CRptTemp_MacroCharItems *pNewMacroCharItems, CMacroTest *pMacroTest)
{
	CRptTemp_MacroTest *pMacroTestDef = pMacroCharItemsDef->GetMacroTest();

	if (pMacroTestDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，macro-char-items节点【%s】，未配置macrotest子节点"), pMacroCharItemsDef->m_strMacro_Id.GetString());
		return FALSE;
	}

	CString strMacroID = pMacroTest->GetTestMacroID();

	if (strMacroID != pMacroTestDef->m_strMacro_Id)
	{
		//直接返回TRUE。过滤掉功能ID不匹配的电气量项目
		return TRUE;
	}

	CRptTemp_ReportsDef* pRptTemp_ReportsDef = pMacroTestDef->GetRpeortsDef();

	if (pRptTemp_ReportsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，macrotest节点【%s】未定义reports-def"), strMacroID.GetString());
		return FALSE;
	}

	CRptTemp_MacroTest* pRptMacroTestNew = GenRpt_Xml_NewMacroTest(pNewMacroCharItems, pMacroTest);
	CExBaseList oRptLists;
	GetItemReports(&oRptLists, pMacroTest);

	BOOL bRet = GenRpt_Xml_MacroTest_Dat_Reports(pRptTemp_ReportsDef, &oRptLists, pRptMacroTestNew, pMacroTest);
	oRptLists.RemoveAll();
	return bRet;
}

//macro-char-items节点，一般不会重复测试，不考虑重复测试次数。
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_RootNode_MacroCharItems(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroCharItems *pMacroCharItems)
{
	BOOL bRet = TRUE;
	CString strMacroID = pMacroCharItems->GetTestMacroID();
	CRptTemp_MacroCharItems *pRptTemp_MacroCharItemsDef = pRptDef->FindMacroCharItemsByMacroID(strMacroID);

	if (pRptTemp_MacroCharItemsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，找不到macro-char-items节点【%s】"), strMacroID.GetString());
		//对于特性曲线项目，必须要配置对应的节点
		return FALSE;
	}

	CRptTemp_MacroCharItems* pNewMacroCharItems = GenRpt_Xml_NewMacroCharItems(pRptItems, pMacroCharItems);

	if (pNewMacroCharItems == NULL)
	{
		return FALSE;
	}

	//先处理macro-char-items下的report-def节点
	CRptTemp_ReportDef *pReportDef = pRptTemp_MacroCharItemsDef->GetReportDef();
	CReport *pReport = pMacroCharItems->GetReport(-1);
	CString strItemPath;
	strItemPath = pMacroCharItems->GetIDPathEx(GBCLASSID_DEVICE, FALSE);

	if (pReportDef != NULL && pReport != NULL)
	{
		CRptTemp_Report *pNewReport = GenRpt_Xml_NewReport(pNewMacroCharItems, pReport);	

		if (! GenRpt_Xml_MacroCharItems_Dat_Report_Value(pReportDef, pNewReport, pReport, strItemPath))
		{
			bRet = FALSE;
		}
	}

	POS pos = pMacroCharItems->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pMacroCharItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_MACROTEST)
		{
			continue;
		}

		CMacroTest *pMacroTest = (CMacroTest *)pObj;

		if (pMacroTest->m_nSelect == 0)
		{
			continue;
		}

		if (! GenRpt_Xml_Items_Dat_RootNode_MacroTest(pRptTemp_MacroCharItemsDef, pNewMacroCharItems, pMacroTest))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_MacroCharItems_Dat_Report_Value(CRptTemp_ReportDef* pRptDef, CRptTemp_Report* pNewRpt, CReport* pReport, const CString &strItemPath)
{
	BOOL bRet = TRUE;
	POS pos = pRptDef->GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_ValueDef *pValueDef = (CRptTemp_ValueDef *)pRptDef->GetNext(pos);

		if (pValueDef->m_strID == RPT_TEMPLATE_VALUE_ID_PNG)
		{
			//特性图，特殊处理
			GenRpt_Xml_NewValue(pNewRpt, pValueDef, strItemPath);
			continue;
		}

		if (! GenRpt_Xml_NewValue(pNewRpt, pValueDef, pReport->m_pValues))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

//pRptMacroTestNew是需要实例化的macrotest节点
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_MacroTest_Dat_Reports(CRptTemp_ReportsDef* pRptDef, CExBaseList *pRptLists, CRptTemp_MacroTest* pRptMacroTestNew, CMacroTest *pMacroTest)
{
	if (pRptDef->GetCount() == 0)
	{
		return FALSE;
	}

	if (pRptLists->GetCount() == 0)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	CRptTemp_Reports *pRptTemp_Reports = pRptMacroTestNew->AddReprots();
	POS pos = pRptDef->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pRptDef->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_VALUEDEF)
		{
			//公共的报告数据，取最后一次报告中的
			CReport *pRpt = (CReport *)pRptLists->GetTail();

			if (! GenRpt_Xml_NewValue(pRptTemp_Reports, (CRptTemp_ValueDef *)pObj, pRpt))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTDEF)
		{
			//模板中，应该只有一个report-def。需要根据pRptLists的数量，实例化对应数量的report
			CRptTemp_ReportDef *pRptTemp_ReportDef = (CRptTemp_ReportDef *)pObj;

			if (! GenRpt_Xml_MacroTest_Dat_Report(pRptTemp_ReportDef, pRptTemp_Reports, pRptLists, pMacroTest))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_MacroTest_Dat_Report(CRptTemp_ReportDef* pRptDef, CExBaseList *pParent, CExBaseList* pRptLists, CMacroTest *pMacroTest)
{
	if (pRptLists->GetCount() == 0)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	long nIndex = 1;
	POS pos = pRptLists->GetHeadPosition();
	long nCalIndex = 0;
	long nRepeatTimes = pMacroTest->m_nRepeatTimes;

	while (pos != NULL)
	{
		CReport *pReport = (CReport *)pRptLists->GetNext(pos);
		CRptTemp_Report *pNewRpt = new CRptTemp_Report();
		pParent->AddNewChild(pNewRpt);

		if (nRepeatTimes > 1)
		{
			if (nIndex % nRepeatTimes == 1 && nIndex > nRepeatTimes)
			{
				nCalIndex++;
				pNewRpt->m_strName.Format(_T("计算报告%d"), nCalIndex);
				pNewRpt->m_strID.Format(_T("Cal_%2d"), nCalIndex);
				pNewRpt->m_nIndex = nCalIndex-1;
				nIndex++;

				if (! GenRpt_Xml_MacroTest_Dat_Report_Value(pRptDef, pNewRpt, pReport, pMacroTest))
				{
					bRet = FALSE;
				}

				continue;
			}
		}

		nIndex++;
		pNewRpt->m_strName.Format(_T("测次%d"), nIndex-nCalIndex-1);
		pNewRpt->m_strID.Format(_T("Rpt%2d"), nIndex-nCalIndex);
		pNewRpt->m_nIndex = nIndex-1-nCalIndex;

		if (! GenRpt_Xml_MacroTest_Dat_Report_Value(pRptDef, pNewRpt, pReport, pMacroTest))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

//考虑从结果判断脚本中获取结果参数，形参pMacroTest作保留用
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_MacroTest_Dat_Report_Value(CRptTemp_ReportDef* pRptDef, CRptTemp_Report* pNewRpt, CReport* pReport, CMacroTest *pMacroTest)
{
	BOOL bRet = TRUE;
	POS pos = pRptDef->GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_ValueDef *pValueDef = (CRptTemp_ValueDef *)pRptDef->GetNext(pos);

		if (! GenRpt_Xml_NewValue(pNewRpt, pValueDef, pReport))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//以下是导出XML格式的doc结构文件的部分
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc(const CString &strXmlFile, CGuideBook *pGuideBook)
{
	if (pGuideBook == NULL)
	{
		return FALSE;
	}

	m_strXmlFile_Doc = strXmlFile;
	BOOL bRet = TRUE;

	if (m_pRptTemp_TestMacroUiRpt == NULL)
	{
		m_pRptTemp_TestMacroUiRpt = new CRptTemp_TestMacroUiRpt();
	}

	m_pRptTemp_TestMacroUiRpt->DeleteAll();

	GenRpt_Xml_Doc_ProcessReportHead();

	CDevice *pDevice = pGuideBook->GetDevice();
	bRet = GenRpt_Xml_Doc_Device(m_pRptTemp_TestMacroUiRpt, pDevice);

	m_pRptTemp_TestMacroUiRpt->SaveXmlFile(m_strXmlFile_Doc, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);

	return bRet;
}

/*
<group name="报告头信息" id="TestGlobalDatas" data-type="TestGlobalDatas" value="1">
<group name="变电站信息" id="SubInformation" data-type="type" value="2">
<data name="变电站名称" id="SubName" data-type="string" value="北京博电" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="变电站地址" id="SubAddr" data-type="string" value="南京" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="回路名称" id="LoopName" data-type="string" value="1#线路" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="回路地址" id="LoopAddr" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="测试人员" id="Tester" data-type="string" value="测试员1" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
</group>
<group name="被测装置信息" id="DeviceInfor" data-type="type" value="2">
<data name="装置名称" id="DeviceName" data-type="string" value="线路保护装置" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="序列号" id="DeviceSN" data-type="string" value="SN123456789" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="装置型号" id="DeviceModel" data-type="string" value="PCS-931" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="定制单编号" id="SettingsNO" data-type="string" value="S123456" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="装置地址" id="DeviceAddr" data-type="string" value="302" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="附加信息" id="AdditionalInf" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="生产厂家" id="DeviceFactory" data-type="string" value="博电" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
</group>
<group name="额定值" id="NomSettings" data-type="type" value="0">
<data name="额定电压" id="Vnom" data-type="float" value="100" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="额定电流" id="Inom" data-type="float" value="1" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="额定频率" id="Fnom" data-type="float" value="50" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="开入防抖时间" id="SureTime" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
</group>
<group name="测试设备信息" id="TestAppInfor" data-type="type" value="0">
<data name="型号" id="AppModel" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="序列号" id="AppSN" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="电流最大值" id="Imax" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="电压最大值" id="Vmax" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="测试开始时间" id="TestStartTime" data-type="string" value="2022-3-19" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="测试终止时间" id="TestEndTime" data-type="string" value="2022-3-19" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
</group>
</group>
*/
void CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_ProcessReportHead()
{
	if (m_pRptTemp_TestMacroUiRpt == NULL || m_pReportHeadParas == NULL)
	{
		return;
	}

	//报告头，用固定的items节点，方便上位机统一处理
	CRptTemp_Items *pItems = new CRptTemp_Items();
	pItems->m_strID = _T("ReportHead");
	m_pRptTemp_TestMacroUiRpt->AddNewChild(pItems);

	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pItems);
	m_pRptHeadTemplate = pNewReportTemplate;
	POS pos = m_pReportHeadParas->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pGrp = (CDataGroup *)m_pReportHeadParas->GetNext(pos);

		if (pGrp->m_strValue == _T("0"))
		{
			continue;
		}

		CRptTemp_Text* pText = GenRpt_Xml_NewText(pNewReportTemplate);  //一个类别，对应一个文本
		pText->m_strText = pGrp->m_strName;
		pText->m_nBold = 1;

		GenRpt_Xml_Doc_ProcessReportHead_Grid(pGrp, pNewReportTemplate);  //一个类别的数据，生成一个表格
	}

	GenRpt_Xml_NewText(pNewReportTemplate);  //报告头结束后，插入一个空行
}

/*
<group name="测试设备信息" id="TestAppInfor" data-type="type" value="0">
<data name="型号" id="AppModel" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="序列号" id="AppSN" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="电流最大值" id="Imax" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="电压最大值" id="Vmax" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="测试开始时间" id="TestStartTime" data-type="string" value="2022-3-19" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
<data name="测试终止时间" id="TestEndTime" data-type="string" value="2022-3-19" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
</group>
1、一个组的数据，生成一个表格；
2、表格共4列，名称：值；名称：值。两个数据为一行；
*/
void CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_ProcessReportHead_Grid(CDataGroup *pGrp, CExBaseList *pParent)
{
	if (pGrp == NULL || pParent == NULL)
	{
		return;
	}

	CRptTemp_Grid* pNewGrid = new CRptTemp_Grid();
	pParent->AddNewChild(pNewGrid);
	pNewGrid->m_strData_Mode = RPT_TEMPLATE_DATAMODE_ROW_RPT;  //行模式
	pNewGrid->m_nShowBorders = 0;

	POS pos = pGrp->GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pGrp->GetNext(pos);
		nIndex++;
		CRptTemp_Row *pRow = NULL;

		if (nIndex%2 == 1) //两个数据一行：奇数，表示要另起一行
		{
			pRow = new CRptTemp_Row;
			pNewGrid->AddNewChild(pRow);
		}
		else
		{
			pRow = (CRptTemp_Row *)pNewGrid->GetTail();  //两个数据一行：偶数，表示不用新起一行
		}

		//cell在row中的顺序，代表单元格在这一行的顺序
		pRow->AddNewCell(pData->m_strName);
		pRow->AddNewCell(pData->m_strValue);
	}
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_Device(CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt, CDevice *pDevice)
{
	if (pDevice == NULL || pRptTemp_TestMacroUiRpt == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pItems = (CItems *)pObj;

		if (pItems->m_nSelect == 0)
		{
			continue;
		}

		if (! GenRpt_Xml_Doc_Items(pRptTemp_TestMacroUiRpt, pItems))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_Items(CExBaseList *pParent, CItems *pItems, BOOL bRecordItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return FALSE;
	}

	if (pItems->IsTypeRootNode())
	{
		return GenRpt_Xml_Items_Doc_RootNode(pParent, pItems, bRecordItems);
	}

	return GenRpt_Xml_Items_Doc_Normal(pParent, pItems, bRecordItems);
}

//递归调用，只针对人工创建的CItems
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_Normal(CExBaseList *pParent, CItems *pItems, BOOL bRecordItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return FALSE;
	}

	if (pItems->m_strID == STT_ITEMS_ID_BEFORETEST
		|| pItems->m_strID == STT_ITEMS_ID_AFTERTEST)
	{
		return TRUE;  //测试前、测试后。过滤掉
	}

	//对于人工创建的CItems节点，只需要导出子的CItems即可
	//因为就算人工创建的CItems节点，子对象包含CMacroTest，也不知道需要导出的报告数据有哪些
	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems);

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	if (bRecordItems)
	{
		//记录当前更新的节点，以便保存文件，供上位机动态刷新
		m_pCurrUpdateItems = pRptTemp_Items;
	}

	//普通CItems，也要建立索引。方便后续根据父节点更新
	pRptTemp_Items->m_pItems = pItems;
	AddTail(pRptTemp_Items);

	BOOL bRet = TRUE;
	POS pos = pItems->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pChildItems = (CItems *)pObj;

		if (pChildItems->m_nSelect == 0)
		{
			continue;
		}

		if (pChildItems->IsTypeRootNode())
		{
			if (! GenRpt_Xml_Items_Doc_RootNode(pRptTemp_Items, pChildItems))
			{
				bRet = FALSE;
			}
		}
		else
		{
			if (! GenRpt_Xml_Items_Doc_Normal(pRptTemp_Items, pChildItems))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode(CExBaseList *pParent, CItems *pItems, BOOL bRecordItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return FALSE;
	}

	if (pItems->m_strStxmlFile == _T("MUAccurAutoTest") || pItems->m_strStxmlFile == _T("MUAutoTest"))
	{
		//合并单元自动测试。表格相对固定，测试模型文件是变化的，采用配置的方式不好处理，此处统一代码特殊处理
		return GenRpt_Xml_Items_Doc_RootNode_MUAuto(pParent, pItems);
	}

	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems);

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	if (bRecordItems)
	{
		//记录当前更新的节点，以便保存文件，供上位机动态刷新
		m_pCurrUpdateItems = pRptTemp_Items;
	}

	pRptTemp_Items->m_pItems = pItems;
	AddTail(pRptTemp_Items);

	IsCurrentItemsAin(pItems->m_strStxmlFile);
	CSttMacroTestUI_TestMacroUIs *pUIs = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->GetTestMacroUIs();
	CSttMacroTestUI_TestMacroUI *pUI = (CSttMacroTestUI_TestMacroUI *)pUIs->FindByID(pItems->m_strStxmlFile);

	if (pUI == NULL)
	{
		return FALSE;
	}

	CRptTemp_TestMacroUiRptDef oRptDef;
	CString strFile;
	strFile = GetDBPath(); 
	strFile += STT_MACROTEST_UI_REALPATH_ATSGEN;
	strFile += _T("/");
	strFile += pUI->m_strrpt_Data_CfgFile;
	BOOL bRet = TRUE;

	CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	bRet = oRptDef.OpenXmlFile(strFile, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);
	CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	if (!bRet)
	{
		return FALSE;
	}

	CString strItemPath;
	strItemPath = pItems->GetIDPathEx(GBCLASSID_DEVICE, FALSE);

	if (! GenRpt_Xml_Items_Doc_RootNode_UpdateItemsTec(&oRptDef, strItemPath))
	{
		//return FALSE;
	}

	//最多定义一个report-template-def节点
	CRptTemp_ReportTemplateDef *pRptTemp_ReportTemplateDef = oRptDef.GetReportTemplateDef();

	if (pRptTemp_ReportTemplateDef != NULL)
	{
		//若oRptDef根节点定义了report-template-def。则说明：
		//1、是一个rootnode导出一个固化的报告。不是动态的
		//2、公共的部分，不随测试点而动态变化的，表格的行和列的数量同样是固定的

		//对于公共的参数，所有的项目都是一致的，直接取第一个电气量项目的参数
		CMacroTest *pMacroTest = pItems->GetFirstMacroTest(TRUE);
		//第一个电气量项目不为空时，导出公共参数部分
		if (pMacroTest != NULL)
		{
			if (! GenRpt_Xml_Doc_ReportTemplateDef_Head(&oRptDef, pRptTemp_Items, pItems))
			{
				bRet = FALSE;
			}
		}
	}

	bRet = GenRpt_Xml_Items_Doc_RootNode_Items(&oRptDef, pRptTemp_Items, pItems);

	return bRet;
}

//rootnode下，可以只考虑items、macrotest和char-macro-items
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_Items(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CItems *pItems)
{
	if (pRptItems == NULL || pRptDef == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	POS pos = pItems->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pItemsChild = (CItems *)pObj;

			if (pItemsChild->m_nSelect == 0)
			{
				continue;
			}

			if (pItemsChild->m_strID == STT_ITEMS_ID_BEFORETEST
				|| pItemsChild->m_strID == STT_ITEMS_ID_AFTERTEST)
			{
				continue;  //测试前、测试后。过滤掉
			}

			CRptTemp_Items *pRptTemp_ItemsChild = GenRpt_Xml_NewItems(pRptItems, pItemsChild);

			if (pRptTemp_ItemsChild == NULL)
			{
				bRet = FALSE;
				continue;
			}

			//普通CItems，也要建立索引。方便后续根据父节点更新
			pRptTemp_ItemsChild->m_pItems = pItemsChild;
			AddTail(pRptTemp_ItemsChild);

			if (! GenRpt_Xml_Items_Doc_RootNode_Items(pRptDef, pRptTemp_ItemsChild, pItemsChild))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == GBCLASSID_MACROTEST)
		{
			CMacroTest *pMacroTest = (CMacroTest *)pObj;

			if (pMacroTest->m_nSelect == 0)
			{
				continue;
			}

			if (! GenRpt_Xml_Items_Doc_RootNode_MacroTest(pRptDef, pRptItems, pMacroTest))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == GBCLASSID_MACROCHARITEMS)
		{
			CMacroCharItems *pMacroCharItems = (CMacroCharItems *)pObj;

			if (pMacroCharItems->m_nSelect == 0)
			{
				continue;
			}

			if (! GenRpt_Xml_Items_Doc_RootNode_MacroCharItems(pRptDef, pRptItems, pMacroCharItems))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

//items下的电气量项目。根据pRptDef中定义的macrotest的报告模式
//报告模式 = item，单独生成表格。
//items，则遍历形参pItems下所有的macrotest，统一生成表格
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MacroTest(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroTest *pMacroTest)
{
	CString strMacroID = pMacroTest->GetTestMacroID();
	CExBaseList oListParas;
	GetMacroTest_AllParas(&oListParas, pMacroTest);
	CRptTemp_MacroTest *pMacroTestDef = pRptDef->FindMacroTestByMacroID(strMacroID, &oListParas);

	if (pMacroTestDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，找不到macrotest节点【%s】"), strMacroID.GetString());
		return FALSE;
	}

	if (pMacroTestDef->m_strRpt_Mode == RPT_TEMPLATE_RPT_MODE_ITEM)
	{
		return GenRpt_Xml_Items_Doc_RootNode_MacroTest_RptMode_Item(pMacroTestDef, pRptItems, pMacroTest);
	}
	else if (pMacroTestDef->m_strRpt_Mode == RPT_TEMPLATE_RPT_MODE_ITEMS)
	{
		CItems *pItems = (CItems *)pMacroTest->GetParent();
		return GenRpt_Xml_Items_Doc_RootNode_MacroTest_RptMode_Items(pMacroTestDef, pRptItems, pItems);
	}

	return FALSE;
}

//曲线搜索项目。应当直接获取pRptDef定义的macro-char-items节点，找到定义的report-template-def。
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MacroCharItems(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroCharItems *pMacroCharItems)
{
	CRptTemp_MacroCharItems *pMacroCharItemsDef = pRptDef->FindMacroCharItemsByMacroID(pMacroCharItems->GetTestMacroID());

	if (pMacroCharItemsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，找不到macro-char-items节点【%s】"), pMacroCharItems->GetTestMacroID().GetString());
		//对于特性曲线项目，必须要配置对应的节点
		return FALSE;
	}

	CRptTemp_MacroCharItems* pNewMacroCharItems = GenRpt_Xml_NewMacroCharItems(pRptItems, pMacroCharItems);

	if (pNewMacroCharItems == NULL)
	{
		return FALSE;
	}

	CRptTemp_ReportTemplateDef *pReportTemplateDef = pMacroCharItemsDef->GetReportTemplateDef();

	if (pReportTemplateDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，macro-char-items下未定义report-template-def节点【%s】"), pMacroCharItemsDef->m_strMacro_Id.GetString());
		return FALSE;
	}

	if (pReportTemplateDef->GetCount() == 0)
	{
		//好多功能，都是直接配置在根节点，不是配置在macrotest下。
		return TRUE;
	}

	return GenRpt_Xml_Doc_ReportTemplateDef_MacroTestCharItems(pReportTemplateDef, pNewMacroCharItems, pMacroCharItems);
}

//更新“技术要求” + “报告数据保留小数位数”数据接口
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_UpdateItemsTec(CRptTemp_TestMacroUiRptDef *pRptDef, const CString &strItemPath)
{
	return GenRpt_Xml_Items_Dat_RootNode_UpdateItemsTec(pRptDef, strItemPath);
}

//报告导出模式：
//item：表示一个电气量项目，单独生成一个word表格。用于动作时间、动作值测试
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MacroTest_RptMode_Item(CRptTemp_MacroTest *pMacroTestDef, CRptTemp_Items *pRptItems, CMacroTest *pMacroTest)
{
	if (pRptItems == NULL || pMacroTestDef == NULL)
	{
		return FALSE;
	}

	if (pMacroTestDef->m_strMacro_Id != pMacroTest->GetTestMacroID())
	{
		//过滤掉测试功能ID不一致的电气量项目
		return TRUE;
	}

	CRptTemp_ReportTemplateDef *pReportTemplateDef = pMacroTestDef->GetReportTemplateDef();

	if (pReportTemplateDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，macrotest下未定义report-template-def节点【%s】"), pMacroTestDef->m_strMacro_Id.GetString());
		return FALSE;
	}

	if (pReportTemplateDef->GetCount() == 0)
	{
		//好多功能，都是直接配置在根节点，不是配置在macrotest下。
		return TRUE;
	}

	return GenRpt_Xml_Doc_ReportTemplateDef_MacroTest(pReportTemplateDef, pRptItems, pMacroTest);
}

//报告导出模式：
//items：表示最小的叶子CItems节点，下面所有的电气量项目，生成一个统一的表格
//report-template-def下定义的title-def和text-def。也是针对最小的叶子CItems节点。
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MacroTest_RptMode_Items(CRptTemp_MacroTest *pMacroTestDef, CRptTemp_Items *pRptItems, CItems *pItems)
{
	if (pRptItems == NULL || pMacroTestDef == NULL)
	{
		return FALSE;
	}

	//对于items模式，所有的电气量项目统一到一个表格，只需要生成一次
	if (pRptItems->IsHasGen())
	{
		return TRUE;
	}

	CRptTemp_ReportTemplateDef *pReportTemplateDef = pMacroTestDef->GetReportTemplateDef();

	if (pReportTemplateDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，macrotest下未定义report-template-def节点【%s】"), pMacroTestDef->m_strMacro_Id.GetString());
		return FALSE;
	}

	if (pReportTemplateDef->GetCount() == 0)
	{
		//好多功能，都是直接配置在根节点，不是配置在macrotest下。
		return TRUE;
	}

	pRptItems->SetHasGen(TRUE);
	return GenRpt_Xml_Doc_ReportTemplateDef_Items(pReportTemplateDef, pRptItems, pItems, pMacroTestDef->m_strMacro_Id);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_ReportTemplateDef_Head(CRptTemp_TestMacroUiRptDef *pRptDef, CExBaseList *pParent_RptTemp, CGbItemBase *pItemBase)
{
	//最多定义一个report-template-def节点
	CRptTemp_ReportTemplateDef *pRptTemp_ReportTemplateDef = pRptDef->GetReportTemplateDef();

	if (pRptTemp_ReportTemplateDef == NULL)
	{
		//可以不定义report-template-def节点
		return TRUE;
	}

	if (pRptTemp_ReportTemplateDef->GetCount() == 0)
	{
		return TRUE;
	}

	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pParent_RptTemp);
	BOOL bRet = TRUE;
	POS pos = pRptTemp_ReportTemplateDef->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pRptTemp_ReportTemplateDef->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_TITLEDEF)
		{
			CRptTemp_TitleDef *pTitleDef = (CRptTemp_TitleDef *)pObj;

			if (! GenRpt_Xml_Doc_TitleDef_Head(pTitleDef, pNewReportTemplate, pItemBase))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_TEXTDEF)
		{
			CRptTemp_TextDef *pTextDef = (CRptTemp_TextDef *)pObj;

			if ( !IsEnable_TextDef(pItemBase, pTextDef) )
			{
				continue;
			}

			if (! GenRpt_Xml_Doc_TextDef_Head(pTextDef, pNewReportTemplate, pItemBase))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_GRIDDEF)
		{
			CRptTemp_GridDef *pGridDef = (CRptTemp_GridDef *)pObj;

			if (! GenRpt_Xml_Doc_GridDef_Head(pGridDef, pNewReportTemplate, pItemBase))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_PNGDEF)
		{
			CRptTemp_PngDef *pPngDef = (CRptTemp_PngDef *)pObj;

			if (! GenRpt_Xml_Doc_PngDef_Head(pPngDef, pNewReportTemplate, pItemBase))
			{
				bRet = FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TitleDef_Head(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent, CGbItemBase *pItemBase)
{
	CItems *pRootNode = (CItems *)Gb_GetFirstParentItems(pItemBase, TRUE);
	BOOL bRet = TRUE;
	CString strText = pTitleDef->m_strText;
	CString strTemp, strText2;
	long nPos = strText.Find(_T("%s"));
	long nIndex = 0;

	while(nPos >= 0)
	{
		strTemp = strText.Left(nPos + 2);

		if (nIndex == 0)
		{
			CString strName = GetItemName(pRootNode, pTitleDef->m_nItem_Level);

			if (strName.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到对应等级【%d】的项目"), pTitleDef->m_nItem_Level);
				bRet = FALSE;
			}

			strTemp.Replace(_T("%s"), strName);
		}
		else if (nIndex == 1)
		{
			CString strName = GetItemName(pRootNode, pTitleDef->m_nItem_Level_2);

			if (strName.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到对应等级【%d】的项目"), pTitleDef->m_nItem_Level_2);
				bRet = FALSE;
			}

			strTemp.Replace(_T("%s"), strName);
		}
		else if (nIndex == 2)
		{
			CString strName = GetItemName(pRootNode, pTitleDef->m_nItem_Level_3);

			if (strName.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到对应等级【%d】的项目"), pTitleDef->m_nItem_Level_3);
				bRet = FALSE;
			}

			strTemp.Replace(_T("%s"), strName);
		}

		strText = strText.Mid(nPos + 2);
		strText2 += strTemp;
		nIndex++;
		nPos = strText.Find(_T("%s"));
	}

	strText2 += strText;
	strText2.AppendFormat(pItemBase->m_strName); //固定添加上项目自身的名称

	CRptTemp_Title* pNewTitle = GenRpt_Xml_NewTitle(pParent);
	pNewTitle->m_strText = strText2;
	pNewTitle->m_nLevel = pNewTitle->GetRelTitleLevel() + pTitleDef->m_nLevel;

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TextDef_Head(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent, CGbItemBase *pItemBase)
{
	BOOL bRet = TRUE;
	CString strText = pTextDef->m_strText;
	CString strText2, strTextFormat;
	strTextFormat = pTextDef->m_strText;

	CDataGroup *pItemsTec = pTextDef->GetItemsTec();
	bRet = GenRpt_Xml_Doc_TextDef_GetContext(strText, strText2, pItemBase, pItemsTec, pTextDef->m_strData1_Id, pTextDef->m_strData2_Id, pTextDef->m_strData3_Id
		, pTextDef->m_strData4_Id, pTextDef->m_strData5_Id, pTextDef->m_strData6_Id);

	CRptTemp_Text* pNewText = GenRpt_Xml_NewText(pParent);
	pNewText->m_strText = strText2;
	pNewText->m_fSize = pTextDef->m_fSize;
	pNewText->m_nBold = pTextDef->m_nBold;
	pNewText->m_strFont = pTextDef->m_strFont;
	pNewText->m_strTextFormat = strTextFormat;
	pNewText->m_strData1_Id = pTextDef->m_strData1_Id;
	pNewText->m_strData2_Id = pTextDef->m_strData2_Id;
	pNewText->m_strData3_Id = pTextDef->m_strData3_Id;
	pNewText->m_strData4_Id = pTextDef->m_strData4_Id;
	pNewText->m_strData5_Id = pTextDef->m_strData5_Id;
	pNewText->m_strData6_Id = pTextDef->m_strData6_Id;
	pNewText->m_pGbItemBase = pItemBase;
	pParent->AddTailToIndexList(pNewText);   //添加到索引链表，方便实时更新

	return bRet;
}

//获取text对象实例化后的文本。形参2是出参，形参1是入参
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TextDef_GetContext(CString &strText, CString &strTextContext, CGbItemBase *pItemBase, CDataGroup *pItemsTec
																, const CString &strData1_Id,  const CString &strData2_Id, const CString &strData3_Id
																, const CString &strData4_Id, const CString &strData5_Id, const CString &strData6_Id)
{
	CGbItemBase *pDestItem = pItemBase;

	if (pDestItem->GetClassID() == GBCLASSID_ITEMS)
	{
		//如果是分类，则取第一个电气量项目
		CItems *pItems = (CItems *)pDestItem;
		pDestItem = pItems->GetFirstMacroTest(TRUE);

		if (pDestItem == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到项目【%s】的电气量项目"), pItemBase->m_strName.GetString());
			pDestItem = pItemBase;
		}
	}

	BOOL bRet = TRUE;
	CString strTemp;
	long nPos = strText.Find(_T("%s"));
	long nIndex = 0;

	while(nPos >= 0)
	{
		strTemp = strText.Left(nPos + 2);

		if (nIndex == 0)
		{
			//先从数据接口查找，找不到再从报告数据查找
			CString strValue = GetItemsTec(pItemsTec, strData1_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData1_Id);
			}	

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到项目【%s】的报告数据【%s】"), pDestItem->m_strName.GetString(), strData1_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData1_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//如果找到数据类型定义，则直接采用数据类型取值的名称。仅限于电气量项目
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 1)
		{
			//先从数据接口查找，找不到再从报告数据查找
			CString strValue = GetItemsTec(pItemsTec, strData2_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData2_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到项目【%s】的报告数据【%s】"), pDestItem->m_strName.GetString(), strData2_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData2_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//如果找到数据类型定义，则直接采用数据类型取值的名称。仅限于电气量项目
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 2)
		{
			//先从数据接口查找，找不到再从报告数据查找
			CString strValue = GetItemsTec(pItemsTec, strData3_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData3_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到项目【%s】的报告数据【%s】"), pDestItem->m_strName.GetString(), strData3_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData3_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//如果找到数据类型定义，则直接采用数据类型取值的名称。仅限于电气量项目
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 3)
		{
			//先从数据接口查找，找不到再从报告数据查找
			CString strValue = GetItemsTec(pItemsTec, strData4_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData4_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到项目【%s】的报告数据【%s】"), pDestItem->m_strName.GetString(), strData4_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData4_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//如果找到数据类型定义，则直接采用数据类型取值的名称。仅限于电气量项目
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 4)
		{
			//先从数据接口查找，找不到再从报告数据查找
			CString strValue = GetItemsTec(pItemsTec, strData5_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData5_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到项目【%s】的报告数据【%s】"), pDestItem->m_strName.GetString(), strData5_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData5_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//如果找到数据类型定义，则直接采用数据类型取值的名称。仅限于电气量项目
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 5)
		{
			//先从数据接口查找，找不到再从报告数据查找
			CString strValue = GetItemsTec(pItemsTec, strData6_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData6_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到项目【%s】的报告数据【%s】"), pDestItem->m_strName.GetString(), strData6_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData6_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//如果找到数据类型定义，则直接采用数据类型取值的名称。仅限于电气量项目
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}

		strText = strText.Mid(nPos + 2);
		strTextContext += strTemp;
		nIndex++;
		nPos = strText.Find(_T("%s"));
	}

	strTextContext += strText;
	return bRet;
}

//目前只考虑行填写模式：即子对象只考虑head、row。grid不定义cols-def、rows-def
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_Head(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent, CGbItemBase *pItemBase)
{
	CExBaseList oListParas;
	BOOL bGetAllParas = FALSE;

	if (pGridDef->GetEnable() != NULL)
	{
		bGetAllParas = TRUE;
	}
	else if (pGridDef->IsRowHasEnableNode())
	{
		bGetAllParas = TRUE;
	}

	//提高效率，不为空，才处理使能
	if (bGetAllParas)
	{
		//表格使能，处理Items的部分
		ASSERT(pItemBase->GetClassID() == GBCLASSID_ITEMS);

		CItems *pRootNode = (CItems *)pItemBase;
		GetMacroTest_AllParas(&oListParas, pRootNode);

		if (! pGridDef->IsEnable(&oListParas))
		{
			return TRUE;
		}
	}

	if (! pGridDef->IsDataMode_Row())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("检测到表格定义为列填写模式，暂不处理……"));
		return FALSE;
	}

	BOOL bRet = TRUE;
	CRptTemp_Grid *pNewGrid = GenRpt_Xml_NewGrid(pParent, pGridDef); //同时处理了head
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	POS pos = pGridDef->GetHeadPosition();
	CRptTemp_TestMacroUiRptDef *pTestMacroUiDef = (CRptTemp_TestMacroUiRptDef *)pGridDef->GetAncestor(MNGRCLASSID_CRPTTEMP_TESTMACROUIRPTDEF);

	//循环只处理row
	while (pos != NULL)
	{
		pObj = pGridDef->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_ROW)
		{
			continue;
		}

		CRptTemp_Row *pRow = (CRptTemp_Row *)pObj;

		if (! pRow->IsEnable(&oListParas))
		{
			//row需判定是否使能
			continue;;
		}

		CRptTemp_Row *pNewRow = (CRptTemp_Row *)pRow->CloneEx(TRUE, TRUE);
		pNewRow->Delete(pNewRow->GetEnable()); //实例化后，删掉使能节点
		pNewGrid->AddNewChild(pNewRow);
		pParent->AddTailToIndexList(pNewRow);

		if (! GenRpt_Xml_Doc_GridDef_Head_FillRow(pNewRow, pItemBase, pTestMacroUiDef))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

//pItemBase一定是rootnode节点
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_Head_FillRow(CRptTemp_Row *pRow, CGbItemBase *pItemBase, CRptTemp_TestMacroUiRptDef *pRptTempUiDef)
{
	ASSERT(pItemBase->GetClassID() == GBCLASSID_ITEMS);

	if (pItemBase->GetClassID() != GBCLASSID_ITEMS)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("导出XML报告，检测到项目类型不对……"));
		return FALSE;
	}

	CItems *pItems = (CItems *)pItemBase;
	ASSERT(pItems->IsTypeRootNode());

	if (!pItems->IsTypeRootNode())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("导出XML报告，检测到项目非rootnode节点……"));
		return FALSE;
	}

	BOOL bRet = TRUE;
	POS pos = pRow->GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_Cell *pCell = (CRptTemp_Cell *)pRow->GetNext(pos);

		if (! GenRpt_Xml_Doc_GridDef_Head_FillCell(pCell, pItems, pRptTempUiDef))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_Head_FillCell(CRptTemp_Cell *pCell, CItems *pItems, CRptTemp_TestMacroUiRptDef *pRptTempUiDef)
{
	if (pCell->m_strType.IsEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Invalid Cell Type [is empty]"));
		return FALSE;
	}

	//固定文本或者是测试索引号，直接返回TRUE。实际上。此处不应该出现测试索引号
	if (pCell->m_strType == RPT_TEMPLATE_COL_DEF_TYPE_TEST_INDEX ||
		pCell->m_strType == RPT_TEMPLATE_COL_DEF_TYPE_TEXT)
	{
		return TRUE;
	}

	if (pCell->m_strType != RPT_TEMPLATE_COL_DEF_TYPE_DATA_ID)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Invalid Cell Type  [%s]"), pCell->m_strType.GetString());
		return FALSE;
	}

	//保留cell的data-id
	pCell->m_strDataID = pCell->m_strText;
	pCell->m_strText = _T("");

	CReport *pReport = NULL;
	CGbItemBase *pDestItem = pItems;
	CString strItemPath;

	if (pCell->m_strData_Path.IsEmpty())
	{
		//对于公共的参数，所有的项目都是一致的，直接取第一个电气量项目的参数
		CMacroTest *pMacroTest = pItems->GetFirstMacroTest(TRUE);

		if (pMacroTest != NULL)
		{
			pReport = pMacroTest->GetReport(-1);
			pDestItem = pMacroTest;
			strItemPath = Gb_GetItemPath(pMacroTest);
		}

		if (pReport == NULL)
		{
			pReport = pItems->GetReport(-1);
		}
	}
	else 
	{
		CGbItemBaseList oDestList;
		//通过项目相对路径，查找项目
		pItems->SelectItems(pCell->m_strData_Path, oDestList);
		long nCount = oDestList.GetCount();

		if (nCount != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("项目【%s】查找结果不唯一！找到【%d】个目标项目"), pCell->m_strData_Path.GetString(), nCount);
			oDestList.RemoveAll();
			return FALSE;
		}

		pDestItem = (CGbItemBase *)oDestList.GetHead();
		pReport = pDestItem->GetReport(-1);
		strItemPath = Gb_GetItemPath(pDestItem);
		oDestList.RemoveAll();
	}

	CRptTemp_Row *pRow = (CRptTemp_Row *)pCell->GetParent();
	pRow->m_strItemPath = strItemPath;
	pRow->m_pGbItemBase = pDestItem;
	pCell->UpdatePrecision(pRptTempUiDef);
	CString strRptValue;

	BOOL bRet = GenRpt_Xml_ProcessRptValue_GetValue(strRptValue, pCell->m_strDataID, pReport, pDestItem, pCell->m_strProcess, pCell->m_nPrecision);
	pCell->m_strText = strRptValue;
	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_Head_FillCell_ProcessVal(const CString& strSrcVal, CString &strVal, const CString &strProcess, long nPrecision)
{
	//表格填写时，与value-def处理一致
	return GenRpt_Xml_NewValue_ProcessVal(strSrcVal, strVal, strProcess, nPrecision);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_PngDef_Head(CRptTemp_PngDef *pPngDef, CRptTemp_ReportTemplate *pParent, CGbItemBase *pItemBase)
{
	if (pPngDef->m_nPngChar == 1)
	{
		//分类项目，则一定是曲线方程
		ASSERT(pItemBase->GetClassID() == GBCLASSID_ITEMS);

		if (pItemBase->GetClassID() != GBCLASSID_ITEMS)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, _T("检测到png-def的类型为曲线方程，但项目类型不为rootnode根节点，不支持导出……"));
			return FALSE;
		}

		CItems *pRootNode = (CItems *)pItemBase;
		CString strPngFile;
		GetPngFilePath_Char(pRootNode, strPngFile);

		if (strPngFile.IsEmpty())
		{
			return FALSE;
		}

		CRptTemp_Png *pNewPng = new CRptTemp_Png();
		pNewPng->m_strPngPath = strPngFile;
		pParent->AddNewChild(pNewPng);

		return TRUE;
	}
	else
	{
		if (pPngDef->m_bHasExport)
		{
			//对于row-items方式，图片是所有macrotest汇总导出一次，若已经导出过，则跳过
			return TRUE;
		}

		CString strItemPath;
		/*strItemPath = pItemBase->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
		CString strPngFile;
		GetPngFilePath(strItemPath, strPngFile);
		*/
		CItems *pItems = Gb_GetFirstParentItems(pItemBase, FALSE); //找到最近的父项目
		strItemPath = pItems->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
		CString strPngFile;

		if (! GetPngFilePath_FaultType(strItemPath, strPngFile, pPngDef->m_strMode))
		{
			//因为是最大化配置，文件不存在，直接返回TRUE。
			return TRUE;
		}

		pPngDef->m_bHasExport = TRUE;
		CRptTemp_Png *pNewPng = new CRptTemp_Png();
		pNewPng->m_strPngPath = strPngFile;
		pParent->AddNewChild(pNewPng);

		return TRUE;
	}

	return FALSE;
}

//以下四个，只处理macrotest节点定义的report-template-def。且rpt-mode=item
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_ReportTemplateDef_MacroTest(CRptTemp_ReportTemplateDef *pReportTemplateDef, CExBaseList *pParent_RptTemp, CMacroTest *pMacroTest)
{
	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pParent_RptTemp);
	BOOL bRet = TRUE;
	POS pos = pReportTemplateDef->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pReportTemplateDef->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_TITLEDEF)
		{
			CRptTemp_TitleDef *pTitleDef = (CRptTemp_TitleDef *)pObj;

			if (! GenRpt_Xml_Doc_TitleDef_MacroTest(pTitleDef, pNewReportTemplate, pMacroTest))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_TEXTDEF)
		{
			CRptTemp_TextDef *pTextDef = (CRptTemp_TextDef *)pObj;

			if (! GenRpt_Xml_Doc_TextDef_MacroTest(pTextDef, pNewReportTemplate, pMacroTest))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_GRIDDEF)
		{
			CRptTemp_GridDef *pGridDef = (CRptTemp_GridDef *)pObj;

			if (! GenRpt_Xml_Doc_GridDef_MacroTest(pGridDef, pNewReportTemplate, pMacroTest))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_PNGDEF)
		{
			CRptTemp_PngDef *pPngDef = (CRptTemp_PngDef *)pObj;

			if (! GenRpt_Xml_Doc_PngDef_Head(pPngDef, pNewReportTemplate, pMacroTest))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TitleDef_MacroTest(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroTest *pMacroTest)
{
	return GenRpt_Xml_Doc_TitleDef_Head(pTitleDef, pParent_RptTemp, pMacroTest);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TextDef_MacroTest(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroTest *pMacroTest)
{
	if (! IsEnable_TextDef(pMacroTest, pTextDef))
	{
		return TRUE;
	}

	return GenRpt_Xml_Doc_TextDef_Head(pTextDef, pParent_RptTemp, pMacroTest);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_MacroTest(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroTest *pMacroTest)
{
	CExBaseList *pListParas = new CExBaseList();
	//提高效率，不为空，才处理使能
	if (pGridDef->GetEnable() != NULL)
	{
		//表格使能，处理MacroTest的部分
		GetMacroTest_AllParas(pListParas, pMacroTest);

		if (! pGridDef->IsEnable(pListParas))
		{
			return TRUE;
		}
	}

	//目前暂时只考虑row-rpt模式。
	ASSERT(pGridDef->m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_RPT);
	CRptTemp_Grid *pNewGrid = GenRpt_Xml_NewGrid(pParent_RptTemp, pGridDef);
	BOOL bRet = GenRpt_Xml_GridDef_RowRpt(pNewGrid, pGridDef, pMacroTest, pListParas);
	delete pListParas;

	return bRet;
}

//以下四个，只处理macro-char-items节点定义的report-template-def
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_ReportTemplateDef_MacroTestCharItems(CRptTemp_ReportTemplateDef *pReportTemplateDef, CExBaseList *pParent_RptTemp, CMacroCharItems *pMacroCharItems)
{
	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pParent_RptTemp);
	BOOL bRet = TRUE;
	POS pos = pReportTemplateDef->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pReportTemplateDef->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_TITLEDEF)
		{
			CRptTemp_TitleDef *pTitleDef = (CRptTemp_TitleDef *)pObj;

			if (! GenRpt_Xml_Doc_TitleDef_MacroCharItems(pTitleDef, pNewReportTemplate, pMacroCharItems))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_TEXTDEF)
		{
			CRptTemp_TextDef *pTextDef = (CRptTemp_TextDef *)pObj;

			if (! GenRpt_Xml_Doc_TextDef_MacroCharItems(pTextDef, pNewReportTemplate, pMacroCharItems))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_GRIDDEF)
		{
			CRptTemp_GridDef *pGridDef = (CRptTemp_GridDef *)pObj;

			if (! GenRpt_Xml_Doc_GridDef_MacroCharItems(pGridDef, pNewReportTemplate, pMacroCharItems))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_PNGDEF)
		{
			CRptTemp_PngDef *pPngDef = (CRptTemp_PngDef *)pObj;

			if (! GenRpt_Xml_Doc_PngDef_MacroCharItems(pPngDef, pNewReportTemplate, pMacroCharItems))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TitleDef_MacroCharItems(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroCharItems *pMacroCharItems)
{
	return GenRpt_Xml_Doc_TitleDef_Head(pTitleDef, pParent_RptTemp, pMacroCharItems);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TextDef_MacroCharItems(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroCharItems *pMacroCharItems)
{
	if (! IsEnable_TextDef(pMacroCharItems, pTextDef))
	{
		return TRUE;
	}

	return GenRpt_Xml_Doc_TextDef_Head(pTextDef, pParent_RptTemp, pMacroCharItems);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_PngDef_MacroCharItems(CRptTemp_PngDef *pPngDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroCharItems *pMacroCharItems)
{
	CString strItemPath;
	strItemPath = pMacroCharItems->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
	CString strPngFile;
	GetPngFilePath(strItemPath, strPngFile);

	CRptTemp_Png *pNewPng = new CRptTemp_Png();
	pNewPng->m_strPngPath = strPngFile;
	pParent_RptTemp->AddNewChild(pNewPng);

	return TRUE;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_MacroCharItems(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroCharItems *pMacroCharItems)
{
	//提高效率，不为空，才处理使能
	if (pGridDef->GetEnable() != NULL)
	{
		//表格使能，处理MacroCharItems的部分
		CExBaseList oListParas;
		GetMacroCharItems_AllParas(&oListParas, pMacroCharItems);

		if (! pGridDef->IsEnable(&oListParas))
		{
			return TRUE;
		}
	}

	//目前暂时只考虑row-item模式。
	ASSERT(pGridDef->m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_ITEM);
	CRptTemp_Grid *pNewGrid = GenRpt_Xml_NewGrid(pParent_RptTemp, pGridDef);
	return GenRpt_Xml_GridDef_RowItem(pNewGrid, pGridDef, pMacroCharItems, pMacroCharItems->GetTestMacroID());
}

//以下四个，只处理macro节点定义的report-template-def。且rpt-mode=items
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_ReportTemplateDef_Items(CRptTemp_ReportTemplateDef *pReportTemplateDef, CExBaseList *pParent_RptTemp, CItems *pItems, const CString &strMacroID)
{
	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pParent_RptTemp);
	BOOL bRet = TRUE;
	POS pos = pReportTemplateDef->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pReportTemplateDef->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_TITLEDEF)
		{
			CRptTemp_TitleDef *pTitleDef = (CRptTemp_TitleDef *)pObj;

			if (! GenRpt_Xml_Doc_TitleDef_Items(pTitleDef, pNewReportTemplate, pItems))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_TEXTDEF)
		{
			CRptTemp_TextDef *pTextDef = (CRptTemp_TextDef *)pObj;

			if (! GenRpt_Xml_Doc_TextDef_Items(pTextDef, pNewReportTemplate, pItems))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_GRIDDEF)
		{
			CRptTemp_GridDef *pGridDef = (CRptTemp_GridDef *)pObj;

			if (! GenRpt_Xml_Doc_GridDef_Items(pGridDef, pNewReportTemplate, pItems, strMacroID))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_PNGDEF)
		{
			CRptTemp_PngDef *pPngDef = (CRptTemp_PngDef *)pObj;

			if (! GenRpt_Xml_Doc_PngDef_Head(pPngDef, pNewReportTemplate, pItems))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TitleDef_Items(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent_RptTemp, CItems *pItems)
{
	return GenRpt_Xml_Doc_TitleDef_Head(pTitleDef, pParent_RptTemp, pItems);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TextDef_Items(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent_RptTemp, CItems *pItems)
{
	if (! IsEnable_TextDef(pItems, pTextDef))
	{
		return TRUE;
	}

	return GenRpt_Xml_Doc_TextDef_Head(pTextDef, pParent_RptTemp, pItems);
}

//rpt-mode = row_item
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_Items(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent_RptTemp, CItems *pItems, const CString &strMacroID)
{
	//目前暂时只考虑row-item模式。
	ASSERT(pGridDef->m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_ITEM);
	CRptTemp_Grid *pNewGrid = GenRpt_Xml_NewGrid(pParent_RptTemp, pGridDef);
	return GenRpt_Xml_GridDef_RowItem(pNewGrid, pGridDef, pItems, strMacroID);
}

//row-item模式下，pItemBase为电气量项目的父节点（CItems、CMacroCharItems）
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_GridDef_RowItem(CRptTemp_Grid *pNewGrid, CRptTemp_GridDef *pGridDef, CGbItemBase *pItemBase, const CString &strMacroID)
{
	CRptTemp_ColsDef *pColsDef = (CRptTemp_ColsDef *)pGridDef->FindByClassID(MNGRCLASSID_CRPTTEMP_COLSDEF);
	ASSERT(pColsDef != NULL);

	if (pColsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，grid-def下未定义cols-def 【%s】"), pItemBase->m_strName.GetString());
		return FALSE;
	}

	long nIndex = 0;
	POS pos = pItemBase->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	BOOL bRet = TRUE;

	while (pos != NULL)
	{
		pObj = pItemBase->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_MACROTEST)
		{
			continue;
		}

		CMacroTest *pMacroTest = (CMacroTest *)pObj;

		if (pMacroTest->m_nSelect == 0)
		{
			continue;
		}

		if (pMacroTest->GetTestMacroID() != strMacroID)
		{
			//过滤掉测试功能ID 不一致的电气量项目
			continue;
		}

		nIndex++;
		CReport *pReport = pMacroTest->GetReport(-1);

		if (! GenRpt_Xml_GridDef_NewRow(pNewGrid, pColsDef, pReport, nIndex, pMacroTest))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

//row-rpt模式下。pGridDef中是定义了所有的row的
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_GridDef_RowRpt(CRptTemp_Grid *pNewGrid, CRptTemp_GridDef *pGridDef, CMacroTest *pMacroTest, CExBaseList *pListParas)
{
	CRptTemp_ColsDef *pColsDef = (CRptTemp_ColsDef *)pGridDef->FindByClassID(MNGRCLASSID_CRPTTEMP_COLSDEF);
	ASSERT(pColsDef != NULL);

	if (pColsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告数据配置文件中，grid-def下未定义cols-def 【%s】"), pMacroTest->m_strName.GetString());
		return FALSE;
	}

	CExBaseList oReportLists;
	GetItemReports(&oReportLists, pMacroTest);
	long nIndex = 0;
	CString strItemPath = Gb_GetItemPath(pMacroTest);
	CRptTemp_ReportTemplate *pParent_RptTemp = (CRptTemp_ReportTemplate *)pNewGrid->GetParent();

	POS pos = pGridDef->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	BOOL bRet = TRUE;

	while (pos != NULL)
	{
		pObj = pGridDef->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_ROW)
		{
			continue;
		}

		CRptTemp_Row *pRow = (CRptTemp_Row *)pObj;

		if ( !pRow->IsEnable(pListParas) )
		{
			//row需判定是否使能
			continue;
		}

		CRptTemp_Row *pNewRow = (CRptTemp_Row *)pRow->CloneEx(TRUE, TRUE);
		pNewRow->Delete(pNewRow->GetEnable()); //实例化后，删掉使能节点
		pNewRow->m_strItemPath = strItemPath;
		pNewRow->m_pGbItemBase = pMacroTest;
		pParent_RptTemp->AddTailToIndexList(pNewRow);

		pNewGrid->AddNewChild(pNewRow);
		CReport *pReport = (CReport *)oReportLists.GetAt(nIndex);

		if (! GenRpt_Xml_GridDef_FillRow(pNewRow, pColsDef, pReport, nIndex))
		{
			bRet = FALSE;
		}

		nIndex++;
	}

	oReportLists.RemoveAll();
	return bRet;
}

//nIndex从1开始
//row-item模式
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_GridDef_NewRow(CRptTemp_Grid *pNewGrid, CRptTemp_ColsDef *pColsDef, CReport *pReport, long nIndex, CGbItemBase *pItem)
{
	BOOL bRet = TRUE;
	CRptTemp_Row *pNewRow = new CRptTemp_Row;
	pNewGrid->AddNewChild(pNewRow);
	CGbItemBase *pItemBase = pItem;//(CGbItemBase *)pReport->GetParent()->GetParent();
	CString strItemPath = Gb_GetItemPath(pItem);
	pNewRow->m_pGbItemBase = pItem;
	pNewRow->m_strItemPath = strItemPath;
	CRptTemp_ReportTemplate *pParent_Template = (CRptTemp_ReportTemplate *)pNewGrid->GetParent();
	pParent_Template->AddTailToIndexList(pNewRow);
	POS pos = pColsDef->GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_ColDef *pColDef = (CRptTemp_ColDef *)pColsDef->GetNext(pos);

		CRptTemp_Cell *pNewCell = new CRptTemp_Cell;
		pNewRow->AddNewChild(pNewCell);

		if (pColDef->m_strType == RPT_TEMPLATE_COL_DEF_TYPE_TEST_INDEX)
		{
			pNewCell->m_strText.Format(_T("%d"), nIndex); //编号
		}
		else if (pColDef->m_strType == RPT_TEMPLATE_COL_DEF_TYPE_DATA_ID)
		{
			pColDef->UpdatePrecision();
			pNewCell->m_strPrecision = pColDef->m_strPrecision;
			pNewCell->m_nPrecision = pColDef->m_nPrecision;
			pNewCell->m_strProcess = pColDef->m_strProcess;
			pNewCell->m_strDataID = pColDef->m_strID;
			CString strRptValue;

			if (! GenRpt_Xml_ProcessRptValue_GetValue(strRptValue, pColDef->m_strID, pReport, pItemBase, pColDef->m_strProcess, pColDef->m_nPrecision))
			{
				bRet = FALSE;
			}

			pNewCell->m_strText = strRptValue;
		}
		else
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_GridDef_FillRow(CRptTemp_Row *pNewRow, CRptTemp_ColsDef *pColsDef, CReport *pReport, long nTestIndex)
{
	long nColIndex = 0;
	BOOL bRet = TRUE;

	if (pReport == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("测次【%d】的报告为空"), nTestIndex + 1);
		bRet = FALSE;
		//return FALSE;
	}

	POS pos = pColsDef->GetHeadPosition();
	CGbItemBase *pItemBase = NULL;

	if (pReport != NULL)
	{
		pItemBase = (CGbItemBase *)pReport->GetParent()->GetParent();
	}

	while (pos != NULL)
	{
		CRptTemp_ColDef *pColDef = (CRptTemp_ColDef *)pColsDef->GetNext(pos);
		CRptTemp_Cell *pCell = (CRptTemp_Cell *)pNewRow->GetAt(nColIndex);
		pCell->m_strText = _T("");

		if (pCell == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("测次【%d】的grid-def中，row缺少第【%d】列的cell定义"), nTestIndex + 1, nColIndex + 1);
			pCell = new CRptTemp_Cell();
			pNewRow->AddNewChild(pCell);
			bRet = FALSE;
		}

		if (pColDef->m_strType == RPT_TEMPLATE_COL_DEF_TYPE_TEST_INDEX)
		{
			//实际上，测次是预填的
			pCell->m_strText.Format(_T("%d"), nTestIndex+1); //测次
		}
		else if (pColDef->m_strType == RPT_TEMPLATE_COL_DEF_TYPE_DATA_ID)
		{
			pCell->m_strDataID = pColDef->m_strID;
			CString strRptValue;
			pColDef->UpdatePrecision();
			pCell->m_strPrecision = pColDef->m_strPrecision;
			pCell->m_nPrecision = pColDef->m_nPrecision;
			pCell->m_strProcess = pColDef->m_strProcess;

			if (! GenRpt_Xml_ProcessRptValue_GetValue(strRptValue, pColDef->m_strID, pReport, pItemBase, pColDef->m_strProcess, pColDef->m_nPrecision))
			{
				bRet = FALSE;
			}

			pCell->m_strText = strRptValue;
		}
		else
		{
			bRet = FALSE;
		}

		nColIndex++;
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_GridDef_FillRow_ProcessVal(const CString& strSrcVal, CString &strVal, const CString &strProcess, long nPrecision)
{
	//表格填写时，与value-def处理一致
	return GenRpt_Xml_NewValue_ProcessVal(strSrcVal, strVal, strProcess, nPrecision);
}

//合并单元自动测试，统一特殊处理
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto(CExBaseList *pParent, CItems *pItems)
{
	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems);  //name=合并单元自动测试【模板生成规则文件配置，需要作为标题或文本】

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	pRptTemp_Items->m_pItems = pItems;
	AddTail(pRptTemp_Items);

	if (pRptTemp_Items->m_nRpt_Title == 0)
	{
		//合并单元-自动测试没有作为标题，则手动添加一个text
		CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pRptTemp_Items); 
		CRptTemp_Text *pText = GenRpt_Xml_NewText(pNewReportTemplate);
		pText->m_strText = pRptTemp_Items->m_strName;
		pText->m_nBold = 1;
		//字体、字号未设置
	}

	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	BOOL bRet = TRUE;

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		if (pObj->m_strID == STT_ITEMS_ID_BEFORETEST)
		{
			//过滤掉测试前准备
			continue;
		}

		CItems *pChildItems = (CItems *)pObj;

		if (pChildItems->m_strID == _T("MUAccuracy"))
		{
			//精确度测试
			if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy(pRptTemp_Items, pChildItems))
			{
				bRet = FALSE;
			}
		}
		else if (pChildItems->m_strID == _T("MUZeroDrift"))
		{
			//零漂测试
			if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_ZeroDrift(pRptTemp_Items, pChildItems))
			{
				bRet = FALSE;
			}
		}
		else if (pChildItems->m_strID == _T("MUTimingAccur"))
		{
			//对时误差
			if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_TimingAccur(pRptTemp_Items, pChildItems))
			{
				bRet = FALSE;
			}
		}
		else if (pChildItems->m_strID == _T("MUPunctAccur"))
		{
			//守时误差
			if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_PunctAccur(pRptTemp_Items, pChildItems))
			{
				bRet = FALSE;
			}
		}
		else
		{
			//其他的暂不支持
			continue;
		}

	}

	return bRet;
}

//精确度测试
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy(CExBaseList *pParent, CItems *pItems)
{
	BOOL bRet = TRUE;
	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems); //name=精确度测试【模板生成规则文件配置，需要作为标题或文本】

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	pRptTemp_Items->m_pItems = pItems;
	AddTail(pRptTemp_Items);

	if (pRptTemp_Items->m_nRpt_Title == 0)
	{
		//精确度测试没有作为标题，则手动添加一个text
		CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pRptTemp_Items); 
		CRptTemp_Text *pText = GenRpt_Xml_NewText(pNewReportTemplate);
		pText->m_strText = pRptTemp_Items->m_strName;
		pText->m_nBold = 1;
		//字体、字号未设置
	}

	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	//精确度测试，分多个测试点，一个测试点对应一个CItems分类
	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pChildItems = (CItems *)pObj;

		if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item(pRptTemp_Items, pChildItems))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

//精确度测试-一个测试点
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item(CExBaseList *pParent, CItems *pItems)
{
	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems); //name=测试点名称【例如：2%测试项。模板生成规则文件配置，需要作为标题或文本】

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	pRptTemp_Items->m_pItems = pItems;
	AddTail(pRptTemp_Items);

	BOOL bRet = TRUE;
	//每个测试点下，都有唯一的电气量项目，其ID是随着测点变化的。例如：050，因此通过ClassID获取
	CMacroTest *pMacroTest = (CMacroTest *)pItems->FindByClassID(GBCLASSID_MACROTEST);

	if (pMacroTest == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】没找到电气量项目，无法生成报表xml数据"), pItems->m_strName.GetString());
		return FALSE;
	}

	//相关的测试数据，都是从通讯命令的报告获取：数据集获取
	CCommCmd *pCommCmd = (CCommCmd *)pMacroTest->FindByClassID(GBCLASSID_COMMCMD);//读结果，作为电气量项目的子项目，通过ClassID获取，避免ID不固定导致的错误

	if (pCommCmd == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】没找到读结果项目，无法生成报表xml数据"), pItems->m_strName.GetString());
		return FALSE;
	}

	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pRptTemp_Items); //一个测试点，一个ReportTemplate

	if (pRptTemp_Items->m_nRpt_Title == 0)
	{
		//测试点没有作为标题，则手动添加一个text
		CRptTemp_Text *pText = GenRpt_Xml_NewText(pNewReportTemplate);
		pText->m_strText = pRptTemp_Items->m_strName;
		pText->m_nBold = 1;
		//字体、字号未设置
	}

	//精度测试，每个测试点，都包括三个部分：比差测试、角差测试、复合误差测试
	if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Rat(pNewReportTemplate, pCommCmd, pItems->m_strName) )
	{
		bRet = FALSE;
	}

	if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Ang(pNewReportTemplate, pCommCmd, pItems->m_strName) )
	{
		bRet = FALSE;
	}

	if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Comp(pNewReportTemplate, pCommCmd, pItems->m_strName) )
	{
		bRet = FALSE;
	}

	return bRet;
}

//精确度测试-一个测试点-比差测试
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Rat(CExBaseList *pParent, CCommCmd *pCommCmd, const CString &strItemsName)
{
	if (pCommCmd == NULL)
	{
		return FALSE;
	}

	CRptTemp_Text* pText = GenRpt_Xml_NewText(pParent);  //一个类别，对应一个文本
	pText->m_strText = _T("比差测试");
	pText->m_nBold = 1;

	//一个类别，对应一个表格
	CRptTemp_Grid* pNewGrid = new CRptTemp_Grid();
	pParent->AddNewChild(pNewGrid);
	pNewGrid->m_strData_Mode = RPT_TEMPLATE_DATAMODE_ROW_RPT;  //行模式

	CRptTemp_Row *pHead = new CRptTemp_Row;
	pNewGrid->AddNewChild(pHead);   //表格头，用行来实现。未测试，也有表格头
	//cell在row中的顺序，代表单元格在这一行的顺序
	pHead->AddNewCell(_T("编号"));
	pHead->AddNewCell(_T("通道名称"));
	pHead->AddNewCell(_T("输出幅值(V/A)"));
	pHead->AddNewCell(_T("最大值%"));
	pHead->AddNewCell(_T("最小值%"));
	pHead->AddNewCell(_T("平均值%"));
	pHead->AddNewCell(_T("结论"));

	CReport *pRpt = pCommCmd->GetReport(-1);

	if (pRpt == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元自动测试-比差测试，测试项【%s】读结果中，未找到测试报告"), strItemsName.GetString());
		return FALSE;
	}

	//处理每个通道的报告数据，0=比差测试
	return GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Datas(pNewGrid, pRpt, strItemsName, 0);
}

//精确度测试-一个测试点-角差测试
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Ang(CExBaseList *pParent, CCommCmd *pCommCmd, const CString &strItemsName)
{
	if (pCommCmd == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	CRptTemp_Text* pText = GenRpt_Xml_NewText(pParent);  //一个类别，对应一个文本
	pText->m_strText = _T("角差测试");
	pText->m_nBold = 1;

	//一个类别，对应一个表格
	CRptTemp_Grid* pNewGrid = new CRptTemp_Grid();
	pParent->AddNewChild(pNewGrid);
	pNewGrid->m_strData_Mode = RPT_TEMPLATE_DATAMODE_ROW_RPT;  //行模式

	CRptTemp_Row *pHead = new CRptTemp_Row;
	pNewGrid->AddNewChild(pHead);   //表格头，用行来实现。未测试，也有表格头
	//cell在row中的顺序，代表单元格在这一行的顺序
	pHead->AddNewCell(_T("编号"));
	pHead->AddNewCell(_T("通道名称"));
	pHead->AddNewCell(_T("输出角度(°)"));
	pHead->AddNewCell(_T("最大值%"));
	pHead->AddNewCell(_T("最小值%"));
	pHead->AddNewCell(_T("平均值%"));
	pHead->AddNewCell(_T("结论"));

	CReport *pRpt = pCommCmd->GetReport(-1);

	if (pRpt == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元自动测试-角差测试，测试项【%s】读结果中，未找到测试报告"), strItemsName.GetString());
		return FALSE;
	}

	//处理每个通道的报告数据，1=角差测试
	return GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Datas(pNewGrid, pRpt, strItemsName, 1);
}

//精确度测试-一个测试点-复合误差测试
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Comp(CExBaseList *pParent, CCommCmd *pCommCmd, const CString &strItemsName)
{
	if (pCommCmd == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	CRptTemp_Text* pText = GenRpt_Xml_NewText(pParent);  //一个类别，对应一个文本
	pText->m_strText = _T("复合误差测试");
	pText->m_nBold = 1;

	//一个类别，对应一个表格
	CRptTemp_Grid* pNewGrid = new CRptTemp_Grid();
	pParent->AddNewChild(pNewGrid);
	pNewGrid->m_strData_Mode = RPT_TEMPLATE_DATAMODE_ROW_RPT;  //行模式

	CRptTemp_Row *pHead = new CRptTemp_Row;
	pNewGrid->AddNewChild(pHead);   //表格头，用行来实现。未测试，也有表格头
	//cell在row中的顺序，代表单元格在这一行的顺序
	pHead->AddNewCell(_T("编号"));
	pHead->AddNewCell(_T("通道名称"));
	pHead->AddNewCell(_T("输出幅值(V/A)"));
	pHead->AddNewCell(_T("输出角度(°)"));
	pHead->AddNewCell(_T("最大值%"));
	pHead->AddNewCell(_T("最小值%"));
	pHead->AddNewCell(_T("平均值%"));
	pHead->AddNewCell(_T("结论"));

	CReport *pRpt = pCommCmd->GetReport(-1);

	if (pRpt == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元自动测试-角差测试，测试项【%s】读结果中，未找到测试报告"), strItemsName.GetString());
		return FALSE;
	}

	//处理每个通道的报告数据，2=复合误差测试
	return GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Datas(pNewGrid, pRpt, strItemsName, 2);
}

//精确度测试-一个测试点，遍历并每个通道的报告数据。nType表示类型：0=比差；1=角差；2=复合误差
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Datas(CExBaseList *pParent, CReport *pRpt, const CString &strItemsName, long nType)
{
	if (pRpt == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	//遍历报告，数据集中一个数据，代表一行
	CDvmDataset *pRptDs = pRpt->m_pRptDvmDataset;
	POS pos = pRptDs->GetHeadPosition();
	CRptTemp_Row *pRow = NULL;
	long nIndex = 1;

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pRptDs->GetNext(pos);
		pRow = new CRptTemp_Row;
		pParent->AddNewChild(pRow);

		if (pData->m_strDataType == _T("UTCTime"))
		{
			GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_UTCTime(pRow, nIndex, pData);
		}
		else
		{
			//最后一个参数0，表示是比差
			if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Data(pRow, nIndex, pData, strItemsName, nType))
			{
				bRet = FALSE;
			}
		}

		nIndex++;
	}

	return bRet;
}

//合并单元精度测试-表格行填写：数据为时间通道
void CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_UTCTime(CRptTemp_Row *pRow, long nIndex, CDvmData *pData)
{
	if (pRow == NULL || pData == NULL)
	{
		return;
	}

	CString strIndex;
	strIndex.Format(_T("%d"), nIndex);
	//cell在row中的顺序，代表单元格在这一行的顺序
	pRow->AddNewCell(strIndex);
	pRow->AddNewCell(pData->m_strName);
	pRow->AddNewCell(_T("--"));
	pRow->AddNewCell(_T("--"));
	pRow->AddNewCell(_T("--"));
	pRow->AddNewCell(_T("--"));
	pRow->AddNewCell(_T("--"));
}

//合并单元精度测试-表格行填写：数据为电压电流通道。nType表示类型：0=比差；1=角差；2=复合误差
/*pData结构固定，如下：
<data name="5P保护电流A相1" id="SV1_I1_Ia1" data-type="Curr" value="" unit="A" min="" max="" format="" index="0" time="0" change="1" step="">
<value name="幅值" id="SV1_I1_Ia1$mag" data-type="FLOAT" value="0.00"/>
<value name="相位" id="SV1_I1_Ia1$ang" data-type="FLOAT" value="0.00"/>
<value name="频率" id="SV1_I1_Ia1$freq" data-type="FLOAT" value="50.00"/>
<value name="平均值" id="SV1_I1_Ia1$avg" data-type="FLOAT" value="0.00"/>
<value name="直流分量" id="SV1_I1_Ia1$DC" data-type="FLOAT" value="0.00"/>
<value name="基波" id="SV1_I1_Ia1$Base" data-type="FLOAT" value="0.00"/>
<value name="2次谐波" id="SV1_I1_Ia1$h2" data-type="FLOAT" value="0.00"/>
<value name="3次谐波" id="SV1_I1_Ia1$h3" data-type="FLOAT" value="0.00"/>
<value name="4次谐波" id="SV1_I1_Ia1$h4" data-type="FLOAT" value="0.00"/>
<value name="5次谐波" id="SV1_I1_Ia1$h5" data-type="FLOAT" value="0.00"/>
<value name="6次谐波" id="SV1_I1_Ia1$h6" data-type="FLOAT" value="0.00"/>
<value name="7次谐波" id="SV1_I1_Ia1$h7" data-type="FLOAT" value="0.00"/>
<value name="8次谐波" id="SV1_I1_Ia1$h8" data-type="FLOAT" value="0.00"/>
<value name="9次谐波" id="SV1_I1_Ia1$h9" data-type="FLOAT" value="0.00"/>
<value name="10次谐波" id="SV1_I1_Ia1$h10" data-type="FLOAT" value="0.00"/>
<value name="11次谐波" id="SV1_I1_Ia1$h11" data-type="FLOAT" value="0.00"/>
<value name="12次谐波" id="SV1_I1_Ia1$h12" data-type="FLOAT" value="0.00"/>
<value name="13次谐波" id="SV1_I1_Ia1$h13" data-type="FLOAT" value="0.00"/>
<value name="14次谐波" id="SV1_I1_Ia1$h14" data-type="FLOAT" value="0.00"/>
<value name="15次谐波" id="SV1_I1_Ia1$h15" data-type="FLOAT" value="0.00"/>
<value name="16次谐波" id="SV1_I1_Ia1$h16" data-type="FLOAT" value="0.00"/>
<value name="17次谐波" id="SV1_I1_Ia1$h17" data-type="FLOAT" value="0.00"/>
<value name="18次谐波" id="SV1_I1_Ia1$h18" data-type="FLOAT" value="0.00"/>
<value name="19次谐波" id="SV1_I1_Ia1$h19" data-type="FLOAT" value="0.00"/>
<value name="20次谐波" id="SV1_I1_Ia1$h20" data-type="FLOAT" value="0.00"/>
<value name="21次谐波" id="SV1_I1_Ia1$h21" data-type="FLOAT" value="0.00"/>
<value name="22次谐波" id="SV1_I1_Ia1$h22" data-type="FLOAT" value="0.00"/>
<value name="23次谐波" id="SV1_I1_Ia1$h23" data-type="FLOAT" value="0.00"/>
<value name="24次谐波" id="SV1_I1_Ia1$h24" data-type="FLOAT" value="0.00"/>
<value name="25次谐波" id="SV1_I1_Ia1$h25" data-type="FLOAT" value="0.00"/>
<value name="比差" id="SV1_I1_Ia1$RatError" data-type="FLOAT" value="0.00">
<value name="最大值" id="SV1_I1_Ia1$RatError$MaxValue" data-type="FLOAT" value=""/>
<value name="最小值" id="SV1_I1_Ia1$RatError$MinValue" data-type="FLOAT" value=""/>
<value name="平均值" id="SV1_I1_Ia1$RatError$AverageValue" data-type="FLOAT" value=""/>
<value name="测试次数" id="SV1_I1_Ia1$RatError$TestCount" data-type="long" value="0"/>
<value name="测试结果" id="SV1_I1_Ia1$RatError$Result" data-type="long" value="0"/>
<value name="误差范围" id="SV1_I1_Ia1$RatError$StdErrorValue" data-type="FLOAT" value="100"/>
<value name="测试结果描述" id="SV1_I1_Ia1$RatError$RltDesc" data-type="string" value="合格"/>
</value>
<value name="角差" id="SV1_I1_Ia1$AngError" data-type="FLOAT" value="0.00">
<value name="最大值" id="SV1_I1_Ia1$AngError$MaxValue" data-type="FLOAT" value=""/>
<value name="最小值" id="SV1_I1_Ia1$AngError$MinValue" data-type="FLOAT" value=""/>
<value name="平均值" id="SV1_I1_Ia1$AngError$AverageValue" data-type="FLOAT" value=""/>
<value name="测试次数" id="SV1_I1_Ia1$AngError$TestCount" data-type="long" value="0"/>
<value name="测试结果" id="SV1_I1_Ia1$AngError$Result" data-type="long" value="0"/>
<value name="误差范围" id="SV1_I1_Ia1$AngError$StdErrorValue" data-type="FLOAT" value="100"/>
<value name="测试结果描述" id="SV1_I1_Ia1$AngError$RltDesc" data-type="string" value="合格"/>
</value>
<value name="频差" id="SV1_I1_Ia1$FreqError" data-type="FLOAT" value="0.00"/>
<value name="检修状态值" id="SV1_I1_Ia1$TestValue" data-type="LONG" value="0"/>
<value name="复合误差" id="SV1_I1_Ia1$CompError" data-type="FLOAT" value="0.00">
<value name="最大值" id="SV1_I1_Ia1$CompError$MaxValue" data-type="FLOAT" value=""/>
<value name="最小值" id="SV1_I1_Ia1$CompError$MinValue" data-type="FLOAT" value=""/>
<value name="平均值" id="SV1_I1_Ia1$CompError$AverageValue" data-type="FLOAT" value=""/>
<value name="测试次数" id="SV1_I1_Ia1$CompError$TestCount" data-type="long" value="0"/>
<value name="测试结果" id="SV1_I1_Ia1$CompError$Result" data-type="long" value="0"/>
<value name="误差范围" id="SV1_I1_Ia1$CompError$StdErrorValue" data-type="FLOAT" value="100"/>
<value name="测试结果描述" id="SV1_I1_Ia1$CompError$RltDesc" data-type="string" value="合格"/>
</value>
</data>
*/
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Data(CRptTemp_Row *pRow, long nIndex, CDvmData *pData, const CString &strItemsName, long nType)
{
	if (pRow == NULL || pData == NULL)
	{
		return FALSE;
	}

	CString strID = pData->m_strID;
	CString strValueID;  
	BOOL bRet = TRUE;
	CString strIndex;
	strIndex.Format(_T("%d"), nIndex);
	//cell在row中的顺序，代表单元格在这一行的顺序
	pRow->AddNewCell(strIndex);  //编号
	pRow->AddNewCell(pData->m_strName);  //通道名称

	if (nType == 0)
	{
		//比差测试
		strID += _T("$RatError");
		CDvmValue *pRat = (CDvmValue *)pData->FindByID(strID);

		if (pRat == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】，通道【%s】没找到比差测试结果数据"), strItemsName.GetString(), pData->m_strName.GetString());
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			return FALSE;
		}

		pRow->AddNewCell(pData->m_strValue);   //输出幅值（V/A）

		//最大值、最小值、平均值、结论
		if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Data_Value(pRow, pRat, strItemsName, pData->m_strName, strID, _T("比差")))
		{
			bRet = FALSE;
		}
	}
	else if (nType == 1)
	{
		//角差测试
		strID += _T("$AngError");
		CDvmValue *pAng = (CDvmValue *)pData->FindByID(strID);

		if (pAng == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】，通道【%s】没找到角差测试结果数据"), strItemsName.GetString(), pData->m_strName.GetString());
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			return FALSE;
		}

		pRow->AddNewCell(pData->m_strFormat);   //输出角度（°）

		//最大值、最小值、平均值、结论
		if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Data_Value(pRow, pAng, strItemsName, pData->m_strName, strID, _T("角差")))
		{
			bRet = FALSE;
		}
	}
	else if (nType == 2)
	{
		//复合误差测试
		strID += _T("$CompError");
		CDvmValue *pComp = (CDvmValue *)pData->FindByID(strID);

		if (pComp == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】，通道【%s】没找到复合误差结果数据"), strItemsName.GetString(), pData->m_strName.GetString());
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			return FALSE;
		}

		pRow->AddNewCell(pData->m_strValue);   //输出幅值（V/A）
		pRow->AddNewCell(pData->m_strFormat);   //输出角度（°）

		//最大值、最小值、平均值、结论
		if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Data_Value(pRow, pComp, strItemsName, pData->m_strName, strID, _T("复合误差")))
		{
			bRet = FALSE;
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】，不支持的结果类型"), strItemsName.GetString());
		pRow->AddNewCell(_T("--")); 
		pRow->AddNewCell(_T("--")); 
		pRow->AddNewCell(_T("--")); 
		pRow->AddNewCell(_T("--")); 
		pRow->AddNewCell(_T("--")); 
		return FALSE;
	}

	return bRet;
}

//合并单元精度测试-表格行填写：最大值、最小值、平均值、结论
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Accuracy_Item_Data_Value(CRptTemp_Row *pRow, CDvmValue *pDataValue, const CString &strItemsName, const CString &strDataName, const CString &strDataID, const CString &strTestType)
{
	BOOL bRet = TRUE;
	//最大值%
	CString strValueID = strDataID + _T("$MaxValue");
	CDvmValue *pValue = (CDvmValue *)pDataValue->FindByID(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】，通道【%s】%s测试结果中，未找到最大值"), strItemsName.GetString(), strDataName.GetString(), strTestType.GetString());
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pValue->m_strValue); 
	}

	//最小值%
	strValueID = strDataID + _T("$MinValue");
	pValue = (CDvmValue *)pDataValue->FindByID(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】，通道【%s】%s测试结果中，未找到最小值"), strItemsName.GetString(), strDataName.GetString(), strTestType.GetString());
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pValue->m_strValue); 
	}

	//平均值%
	strValueID = strDataID + _T("$AverageValue");
	pValue = (CDvmValue *)pDataValue->FindByID(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】，通道【%s】%s测试结果中，未找到平均值"), strItemsName.GetString(), strDataName.GetString(), strTestType.GetString());
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pValue->m_strValue); 
	}

	//结论
	strValueID = strDataID + _T("$RltDesc");
	pValue = (CDvmValue *)pDataValue->FindByID(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元精确度测试-测点【%s】，通道【%s】%s测试结果中，未找到结论"), strItemsName.GetString(), strDataName.GetString(), strTestType.GetString());
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pValue->m_strValue); 
	}

	return bRet;
}
//零漂测试
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_ZeroDrift(CExBaseList *pParent, CItems *pItems)
{
	BOOL bRet = TRUE;
	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems); //name=零漂测试【模板生成规则文件配置，需要作为标题或文本】

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	pRptTemp_Items->m_pItems = pItems;
	AddTail(pRptTemp_Items);

	if (pRptTemp_Items->m_nRpt_Title == 0)
	{
		//零漂测试没有作为标题，则手动添加一个text
		CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pRptTemp_Items); 
		CRptTemp_Text *pText = GenRpt_Xml_NewText(pNewReportTemplate);
		pText->m_strText = pRptTemp_Items->m_strName;
		pText->m_nBold = 1;
		//字体、字号未设置
	}

	//零漂测试分类，都有唯一的电气量项目，通过ClassID获取
	CMacroTest *pMacroTest = (CMacroTest *)pItems->FindByClassID(GBCLASSID_MACROTEST);

	if (pMacroTest == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元零漂测试，没找到电气量项目，无法生成报表xml数据"));
		return FALSE;
	}

	//相关的测试数据，都是从通讯命令的报告获取：数据集获取
	//零漂测试中，包含零漂、离散度测试
	CCommCmd *pZero = (CCommCmd *)pMacroTest->FindByID(_T("ReadRlts"));//读零漂，作为电气量项目的子项目，电气量项目下多个通讯命令，通过ID区分
	CCommCmd *pDiscrete = (CCommCmd *)pMacroTest->FindByID(_T("ReadDiscrete"));//读离散度，作为电气量项目的子项目，电气量项目下多个通讯命令，通过ID区分

	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pRptTemp_Items); //零漂测试，一个总的ReportTemplate

	if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_ZeroDrift_Zero(pNewReportTemplate, pZero) )
	{
		bRet = FALSE;
	}

	if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_ZeroDrift_Discrete(pNewReportTemplate, pDiscrete) )
	{
		bRet = FALSE;
	}

	return bRet;
}

//零漂测试 - 零漂
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_ZeroDrift_Zero(CExBaseList *pParent, CCommCmd *pCommCmd)
{
	if (pParent == NULL)
	{
		return FALSE;
	}

	if (pCommCmd == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-零漂测试，没找到读零漂结果的通讯命令"));
		return FALSE;
	}

	BOOL bRet = TRUE;
	CRptTemp_Text* pText = GenRpt_Xml_NewText(pParent);  //一个类别，对应一个文本
	pText->m_strText = _T("零漂");
	pText->m_nBold = 1;

	//一个类别，对应一个表格
	CRptTemp_Grid* pNewGrid = new CRptTemp_Grid();
	pParent->AddNewChild(pNewGrid);
	pNewGrid->m_strData_Mode = RPT_TEMPLATE_DATAMODE_ROW_RPT;  //行模式

	CRptTemp_Row *pHead = new CRptTemp_Row;
	pNewGrid->AddNewChild(pHead);   //表格头，用行来实现。未测试，也有表格头
	//cell在row中的顺序，代表单元格在这一行的顺序
	pHead->AddNewCell(_T("编号"));
	pHead->AddNewCell(_T("通道名称"));
	pHead->AddNewCell(_T("额定值(V/A)"));
	pHead->AddNewCell(_T("最大值%"));
	pHead->AddNewCell(_T("最小值%"));
	pHead->AddNewCell(_T("平均值%"));

	CReport *pRpt = pCommCmd->GetReport(-1);

	if (pRpt == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-零漂测试，未找到测试报告"));
		return FALSE;
	}

	//处理每个通道的报告数据
	return GenRpt_Xml_Items_Doc_RootNode_MUAuto_Zero_Datas(pNewGrid, pRpt);
}

//零漂测试 - 零漂，遍历并处理每个通道的报告数据
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Zero_Datas(CExBaseList *pParent, CReport *pRpt)
{
	if (pRpt == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	//遍历报告，数据集中一个数据，代表一行
	CDvmDataset *pRptDs = pRpt->m_pRptDvmDataset;
	POS pos = pRptDs->GetHeadPosition();
	CRptTemp_Row *pRow = NULL;
	long nIndex = 1;

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pRptDs->GetNext(pos);
		pRow = new CRptTemp_Row;
		pParent->AddNewChild(pRow);

		if (pData->m_strDataType == _T("UTCTime"))
		{
			CString strIndex;
			strIndex.Format(_T("%d"), nIndex);
			//cell在row中的顺序，代表单元格在这一行的顺序
			pRow->AddNewCell(strIndex);
			pRow->AddNewCell(pData->m_strName);
			pRow->AddNewCell(_T("--"));
			pRow->AddNewCell(_T("--"));
			pRow->AddNewCell(_T("--"));
			pRow->AddNewCell(_T("--"));
			pRow->AddNewCell(_T("--"));
		}
		else
		{
			if (! GenRpt_Xml_Items_Doc_RootNode_MUAuto_Zero_Data(pRow, nIndex, pData))
			{
				bRet = FALSE;
			}
		}

		nIndex++;
	}

	return bRet;
}

//合并单元零漂-表格行填写：数据为电压电流通道
//零漂的数据集，跟精度测试一致
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_Zero_Data(CRptTemp_Row *pRow, long nIndex, CDvmData *pData)
{
	if (pRow == NULL || pData == NULL)
	{
		return FALSE;
	}

	CString strID = pData->m_strID;
	CString strValueID;  
	BOOL bRet = TRUE;
	CString strIndex;
	strIndex.Format(_T("%d"), nIndex);
	//cell在row中的顺序，代表单元格在这一行的顺序
	pRow->AddNewCell(strIndex);  //编号
	pRow->AddNewCell(pData->m_strName);  //通道名称

	strID += _T("$RatError");  //零漂的数据ID，跟精度测试-比差测试一致。
	CDvmValue *pDataValue = (CDvmValue *)pData->FindByID(strID);

	if (pDataValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元零漂测试，通道【%s】没有测试结果数据"), pData->m_strName.GetString());
		pRow->AddNewCell(_T("--")); 
		pRow->AddNewCell(_T("--")); 
		pRow->AddNewCell(_T("--")); 
		pRow->AddNewCell(_T("--")); 
		pRow->AddNewCell(_T("--")); 
		return FALSE;
	}

	pRow->AddNewCell(pData->m_strValue);   //额定值（V/A）

	//最大值%
	strValueID = strID + _T("$MaxValue");
	CDvmValue *pValue = (CDvmValue *)pDataValue->FindByID(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元零漂测试，通道【%s】的测试结果数据中，未找到最大值"), pData->m_strName.GetString());
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pValue->m_strValue); 
	}

	//最小值%
	strValueID = strID + _T("$MinValue");
	pValue = (CDvmValue *)pDataValue->FindByID(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元零漂测试，通道【%s】的测试结果数据中，未找到最小值"), pData->m_strName.GetString());
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pValue->m_strValue); 
	}

	//平均值%
	strValueID = strID + _T("$AverageValue");
	pValue = (CDvmValue *)pDataValue->FindByID(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元零漂测试，通道【%s】的测试结果数据中，未找到平均值"), pData->m_strName.GetString());
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pValue->m_strValue); 
	}

	return bRet;
}

//零漂测试 - 离散度
/*
<dataset name="dsSVErr" id="dsSVErr" data-type="" write-mode="0" index="0" addr="0">
<data name="SV1" id="SV1" data-type="int" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step="">
<value name="报文总帧数" id="SV1$PkgTotalNum" data-type="int" value=""/>
<value name="最大离散度误差(us)" id="SV1$MaxTimeDiscrete" data-type="double" value="">
<value name="最大值" id="SV1$MaxTimeDiscrete$MaxValue" data-type="double" value=""/>
<value name="测试结果" id="SV1$MaxTimeDiscrete$Result" data-type="long" value="0"/>
<value name="测试结果描述" id="SV1$MaxTimeDiscrete$RltDesc" data-type="string" value="合格"/>
</value>
<value name="失步" id="SV1$LoseSyn" data-type="int" value=""/>
<value name="丢包" id="SV1$Loss" data-type="int" value=""/>
<value name="重复" id="SV1$Repeat" data-type="int" value=""/>
<value name="采样序号错" id="SV1$NumErr" data-type="int" value=""/>
<value name="长度参数错" id="SV1$LengthParaErr" data-type="int" value=""/>
<value name="APDU编码错" id="SV1$APDUCodeErr" data-type="int" value=""/>
<value name="ASDU编码错" id="SV1$ASDUCodeErr" data-type="int" value=""/>
<value name="超时" id="SV1$TimeOut" data-type="int" value=""/>
<value name="抖动" id="SV1$Shake" data-type="int" value=""/>
<value name="通信中断" id="SV1$CommLoss" data-type="int" value=""/>
<value name="通信恢复" id="SV1$CommRecover" data-type="int" value=""/>
<value name="品质异常" id="SV1$QualityErr" data-type="int" value=""/>
<value name="采样无效" id="SV1$SVInvalid" data-type="int" value=""/>
<value name="检修状态" id="SV1$TestStatus" data-type="int" value=""/>
<value name="通道延时改变" id="SV1$DelayChanged" data-type="int" value=""/>
<value name="ASDU数目改变" id="SV1$ASDUNumChanged" data-type="int" value=""/>
<value name="双A/D采样不一致" id="SV1$ADIncstc" data-type="int" value=""/>
<value name="非法SMV的异常报文" id="SV1$IllegalData" data-type="int" value=""/>
</data>
</dataset>
*/
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_ZeroDrift_Discrete(CExBaseList *pParent, CCommCmd *pCommCmd)
{
	if (pParent == NULL)
	{
		return FALSE;
	}

	if (pCommCmd == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-零漂测试，没找到读离散度结果的通讯命令"));
		return FALSE;
	}

	BOOL bRet = TRUE;
	CRptTemp_Text* pText = GenRpt_Xml_NewText(pParent);  //一个类别，对应一个文本
	pText->m_strText = _T("离散度测试");
	pText->m_nBold = 1;

	//一个类别，对应一个表格
	CRptTemp_Grid* pNewGrid = new CRptTemp_Grid();
	pParent->AddNewChild(pNewGrid);
	pNewGrid->m_strData_Mode = RPT_TEMPLATE_DATAMODE_ROW_RPT;  //行模式

	CRptTemp_Row *pHead = new CRptTemp_Row;
	pNewGrid->AddNewChild(pHead);   //表格头，用行来实现。未测试，也有表格头
	//cell在row中的顺序，代表单元格在这一行的顺序
	pHead->AddNewCell(_T("编号"));
	pHead->AddNewCell(_T("最大离散度(μs)"));
	pHead->AddNewCell(_T("结论"));

	CReport *pRpt = pCommCmd->GetReport(-1);

	if (pRpt == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-离散度测试，未找到测试报告"));
		return FALSE;
	}

	//处理每个通道的报告数据
	return GenRpt_Xml_Items_Doc_RootNode_MUAuto_ZeroDrift_Discrete_Datas(pNewGrid, pRpt);
}

//零漂测试 - 离散度，遍历并处理每个通道的报告数据
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_ZeroDrift_Discrete_Datas(CExBaseList *pParent, CReport *pRpt)
{
	if (pRpt == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	//遍历报告，数据集中一个数据，代表一行
	CDvmDataset *pRptDs = pRpt->m_pRptDvmDataset;
	POS pos = pRptDs->GetHeadPosition();
	CRptTemp_Row *pRow = NULL;
	long nIndex = 1;

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pRptDs->GetNext(pos);
		pRow = new CRptTemp_Row;
		pParent->AddNewChild(pRow);

		CString strID = pData->m_strID;
		CString strValueID;  
		BOOL bRet = TRUE;
		CString strIndex;
		strIndex.Format(_T("%d"), nIndex);
		//cell在row中的顺序，代表单元格在这一行的顺序
		pRow->AddNewCell(strIndex);  //编号

		strID += _T("$MaxTimeDiscrete");  
		CDvmValue *pDataValue = (CDvmValue *)pData->FindByID(strID);  //最大离散度

		if (pDataValue == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元零散度测试，通道【%s】没有结果数据"), pData->m_strName.GetString());
			pRow->AddNewCell(_T("--")); 
			pRow->AddNewCell(_T("--")); 
			bRet = FALSE;
			nIndex++;
			continue;
		}

		//最大离散度(μs)
		strValueID = strID + _T("$MaxValue");
		CDvmValue *pValue = (CDvmValue *)pDataValue->FindByID(strValueID);

		if (pValue == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元零散度测试，通道【%s】结果数据中，未找到最大离散度"), pData->m_strName.GetString());
			pRow->AddNewCell(_T("--")); 
			bRet = FALSE;
		}
		else
		{
			pRow->AddNewCell(pValue->m_strValue); 
		}

		//结论
		strValueID = strID + _T("$RltDesc");
		pValue = (CDvmValue *)pDataValue->FindByID(strValueID);

		if (pValue == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("合并单元零散度测试，通道【%s】结果数据中，未找到结论"), pData->m_strName.GetString());
			pRow->AddNewCell(_T("--")); 
			bRet = FALSE;
		}
		else
		{
			pRow->AddNewCell(pValue->m_strValue); 
		}

		nIndex++;
	}

	return bRet;
}

//对时误差
/*
<dataset name="dsMUTimeRlt" id="dsMUTimeRlt" data-type="" write-mode="0" index="0" addr="0">
<data name="已测试时长" id="HasUsingTime" data-type="long" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="最大误差时间" id="MaxErrTime" data-type="float" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="最小误差时间" id="MinErrTime" data-type="float" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="当前误差" id="CurrErrTime" data-type="float" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="平均误差时间" id="AverageErrTime" data-type="float" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="时间精度测试结果" id="MUTimeResult" data-type="long" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
</dataset>
*/
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_TimingAccur(CExBaseList *pParent, CItems *pItems)
{
	BOOL bRet = TRUE;
	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems); //name=对时误差测试【模板生成规则文件配置，需要作为标题或文本】

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	pRptTemp_Items->m_pItems = pItems;
	AddTail(pRptTemp_Items);

	if (pRptTemp_Items->m_nRpt_Title == 0)
	{
		//对时误差测试没有作为标题，则手动添加一个text
		CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pRptTemp_Items); 
		CRptTemp_Text *pText = GenRpt_Xml_NewText(pNewReportTemplate);
		pText->m_strText = pRptTemp_Items->m_strName;
		pText->m_nBold = 1;
		//字体、字号未设置
	}

	//对时误差测试分类，都有唯一的电气量项目，通过ClassID获取
	CMacroTest *pMacroTest = (CMacroTest *)pItems->FindByClassID(GBCLASSID_MACROTEST);

	if (pMacroTest == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元对时误差测试，没找到电气量项目，无法生成报表xml数据"));
		return FALSE;
	}

	//相关的测试数据，都是从通讯命令的报告获取：数据集获取
	CCommCmd *pCommCmd = (CCommCmd *)pMacroTest->FindByClassID(GBCLASSID_COMMCMD);//读结果，作为电气量项目的子项目，为避免ID变化，通过ClassID获取
	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pRptTemp_Items); //对时误差测试，一个总的ReportTemplate

	CRptTemp_Grid* pNewGrid = new CRptTemp_Grid();
	pNewReportTemplate->AddNewChild(pNewGrid);
	pNewGrid->m_strData_Mode = RPT_TEMPLATE_DATAMODE_ROW_RPT;  //行模式

	CRptTemp_Row *pHead = new CRptTemp_Row;
	pNewGrid->AddNewChild(pHead);   //表格头，用行来实现。未测试，也有表格头
	//cell在row中的顺序，代表单元格在这一行的顺序
	pHead->AddNewCell(_T("编号"));
	pHead->AddNewCell(_T("对时时长(s)"));
	pHead->AddNewCell(_T("最大误差(μs)"));
	pHead->AddNewCell(_T("最小误差(μs)"));
	pHead->AddNewCell(_T("平均误差(μs)"));
	pHead->AddNewCell(_T("结论"));

	if (pCommCmd == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-对时误差测试，没找到读结果的通讯命令"));
		return FALSE;
	}

	CReport *pMacroTestRpt = pMacroTest->GetReport(-1);
	CString strOutPutTime;
	strOutPutTime = _T("--");

	if (pMacroTestRpt == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-对时误差测试，未找到测试报告"));
		bRet = FALSE;
	}
	else
	{
		CValue *pValue = (CValue *)pMacroTestRpt->m_pValues->FindByID(_T("OutputTime"));

		if (pValue == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-对时误差测试，报告中未找到对时时长"));
			bRet = FALSE;
		}
		else
		{
			strOutPutTime = pValue->m_strValue;
		}
	}

	CReport *pRpt = pCommCmd->GetReport(-1);

	if (pRpt == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-对时误差测试，未找到测试报告"));
		return FALSE;
	}

	CDvmDataset* pRptDs = pRpt->m_pRptDvmDataset;
	CRptTemp_Row *pRow = new CRptTemp_Row;
	pNewGrid->AddNewChild(pRow);

	//cell在row中的顺序，代表单元格在这一行的顺序
	pRow->AddNewCell(_T("1"));  //编号
	pRow->AddNewCell(strOutPutTime);  //对时时长

	//最大误差(μs)
	CDvmData *pData = (CDvmData *)pRptDs->FindByID(_T("MaxErrTime"));

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-对时误差测试，结果数据中，未找到最大误差"));
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pData->m_strValue); 
	}

	//最小误差(μs)
	pData = (CDvmData *)pRptDs->FindByID(_T("MinErrTime"));

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-对时误差测试，结果数据中，未找到最小误差"));
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pData->m_strValue); 
	}

	//平均误差(μs)
	pData = (CDvmData *)pRptDs->FindByID(_T("AverageErrTime"));

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-对时误差测试，结果数据中，未找到平均误差"));
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pData->m_strValue); 
	}

	//结论
	pData = (CDvmData *)pRptDs->FindByID(_T("RsltDsc"));

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-对时误差测试，结果数据中，未找到结论"));
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pData->m_strValue); 
	}

	return bRet;
}

//守时误差
/*
<dataset name="dsMUTimeRlt" id="dsMUTimeRlt" data-type="" write-mode="0" index="0" addr="0">
<data name="已测试时长" id="HasUsingTime" data-type="long" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="最大误差时间" id="MaxErrTime" data-type="float" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="最小误差时间" id="MinErrTime" data-type="float" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="当前误差" id="CurrErrTime" data-type="float" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="平均误差时间" id="AverageErrTime" data-type="float" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
<data name="时间精度测试结果" id="MUTimeResult" data-type="long" default-value="" value="0" unit="" min="" max="" format="" index="0" time="0" change="1" step=""/>
</dataset>
*/
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MUAuto_PunctAccur(CExBaseList *pParent, CItems *pItems)
{
	BOOL bRet = TRUE;
	CRptTemp_Items *pRptTemp_Items = GenRpt_Xml_NewItems(pParent, pItems); //name=守时误差测试【模板生成规则文件配置，需要作为标题或文本】

	if (pRptTemp_Items == NULL)
	{
		return FALSE;
	}

	pRptTemp_Items->m_pItems = pItems;
	AddTail(pRptTemp_Items);

	if (pRptTemp_Items->m_nRpt_Title == 0)
	{
		//守时误差测试没有作为标题，则手动添加一个text
		CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pRptTemp_Items); 
		CRptTemp_Text *pText = GenRpt_Xml_NewText(pNewReportTemplate);
		pText->m_strText = pRptTemp_Items->m_strName;
		pText->m_nBold = 1;
		//字体、字号未设置
	}

	//对时误差测试分类，都有唯一的电气量项目，通过ClassID获取
	CMacroTest *pMacroTest = (CMacroTest *)pItems->FindByClassID(GBCLASSID_MACROTEST);

	if (pMacroTest == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元守时误差测试，没找到电气量项目，无法生成报表xml数据"));
		return FALSE;
	}

	//相关的测试数据，都是从通讯命令的报告获取：数据集获取
	CCommCmd *pCommCmd = (CCommCmd *)pMacroTest->FindByClassID(GBCLASSID_COMMCMD);//读结果，作为电气量项目的子项目，为避免ID变化，通过ClassID获取
	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(pRptTemp_Items); //守时误差测试，一个总的ReportTemplate

	CRptTemp_Grid* pNewGrid = new CRptTemp_Grid();
	pNewReportTemplate->AddNewChild(pNewGrid);
	pNewGrid->m_strData_Mode = RPT_TEMPLATE_DATAMODE_ROW_RPT;  //行模式

	CRptTemp_Row *pHead = new CRptTemp_Row;
	pNewGrid->AddNewChild(pHead);   //表格头，用行来实现。未测试，也有表格头
	//cell在row中的顺序，代表单元格在这一行的顺序
	pHead->AddNewCell(_T("编号"));
	pHead->AddNewCell(_T("守时时长(s)"));
	pHead->AddNewCell(_T("最大误差(μs)"));
	pHead->AddNewCell(_T("最小误差(μs)"));
	pHead->AddNewCell(_T("平均误差(μs)"));
	pHead->AddNewCell(_T("结论"));

	if (pCommCmd == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-守时误差测试，没找到读结果的通讯命令"));
		return FALSE;
	}

	CReport *pMacroTestRpt = pMacroTest->GetReport(-1);
	CString strOutPutTime;
	strOutPutTime = _T("--");

	if (pMacroTestRpt == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-守时误差测试，未找到测试报告"));
		bRet = FALSE;
	}
	else
	{
		CValue *pValue = (CValue *)pMacroTestRpt->m_pValues->FindByID(_T("OutputTime"));

		if (pValue == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-守时误差测试，报告中未找到守时时长"));
			bRet = FALSE;
		}
		else
		{
			strOutPutTime = pValue->m_strValue;
		}
	}

	CReport *pRpt = pCommCmd->GetReport(-1);

	if (pRpt == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-守时误差测试，未找到测试报告"));
		return FALSE;
	}

	CDvmDataset* pRptDs = pRpt->m_pRptDvmDataset;
	CRptTemp_Row *pRow = new CRptTemp_Row;
	pNewGrid->AddNewChild(pRow);

	//cell在row中的顺序，代表单元格在这一行的顺序
	pRow->AddNewCell(_T("1"));  //编号
	pRow->AddNewCell(strOutPutTime);  //守时时长

	//最大误差(μs)
	CDvmData *pData = (CDvmData *)pRptDs->FindByID(_T("MaxErrTime"));

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-守时误差测试，结果数据中，未找到最大误差"));
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pData->m_strValue); 
	}

	//最小误差(μs)
	pData = (CDvmData *)pRptDs->FindByID(_T("MinErrTime"));

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-守时误差测试，结果数据中，未找到最小误差"));
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pData->m_strValue); 
	}

	//平均误差(μs)
	pData = (CDvmData *)pRptDs->FindByID(_T("AverageErrTime"));

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-守时误差测试，结果数据中，未找到平均误差"));
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pData->m_strValue); 
	}

	//结论
	pData = (CDvmData *)pRptDs->FindByID(_T("RsltDsc"));

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("合并单元自动测试-守时误差测试，结果数据中，未找到结论"));
		pRow->AddNewCell(_T("--")); 
		bRet = FALSE;
	}
	else
	{
		pRow->AddNewCell(pData->m_strValue); 
	}

	return bRet;
}

CRptTemp_Items* CRptTemplate_GenXmlTool::GenRpt_Xml_NewItems(CExBaseList *pParent, CItems *pItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return NULL;
	}

	CRptTemp_Items *pNewItems = new CRptTemp_Items();
	pNewItems->m_strName = pItems->m_strName;
	pNewItems->m_strID = pItems->m_strID;
	pNewItems->m_nRpt_Title = pItems->m_nRptTitle;
	pNewItems->m_ntitle_level = pItems->m_nTitleLevel;
	pParent->AddNewChild(pNewItems);

	return pNewItems;
}

CRptTemp_MacroTest* CRptTemplate_GenXmlTool::GenRpt_Xml_NewMacroTest(CExBaseList *pParent, CMacroTest *pMacroTest)
{
	if (pParent == NULL || pMacroTest == NULL)
	{
		return NULL;
	}

	CRptTemp_MacroTest *pNewMacroTest = new CRptTemp_MacroTest();
	pNewMacroTest->m_strName = pMacroTest->m_strName;
	pNewMacroTest->m_strID = pMacroTest->m_strID;
	pParent->AddNewChild(pNewMacroTest);

	return pNewMacroTest;
}

CRptTemp_MacroCharItems* CRptTemplate_GenXmlTool::GenRpt_Xml_NewMacroCharItems(CExBaseList *pParent, CMacroCharItems *pMacroCharItems)
{
	if (pParent == NULL || pMacroCharItems == NULL)
	{
		return NULL;
	}

	CRptTemp_MacroCharItems *pNewMacroCharItems = new CRptTemp_MacroCharItems();
	pNewMacroCharItems->m_strName = pMacroCharItems->m_strName;
	pNewMacroCharItems->m_strID = pMacroCharItems->m_strID;
	pNewMacroCharItems->m_strMacro_Id = pMacroCharItems->GetTestMacroID();
	pParent->AddNewChild(pNewMacroCharItems);

	return pNewMacroCharItems;
}

CRptTemp_Report* CRptTemplate_GenXmlTool::GenRpt_Xml_NewReport(CExBaseList *pParent, CReport *pReport)
{
	if (pParent == NULL || pReport == NULL)
	{
		return NULL;
	}

	CRptTemp_Report *pNewReport = new CRptTemp_Report();
	pNewReport->m_strName = pReport->m_strName;
	pNewReport->m_strID = pReport->m_strID;
	pParent->AddNewChild(pNewReport);

	return pNewReport;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_NewValue(CExBaseList *pParent, CRptTemp_ValueDef* pValueDef, const CString &strItemPath)
{
	CString strPngFile;
	CRptTemp_Value *pNewValue = new CRptTemp_Value();
	pNewValue->m_strName = pValueDef->m_strName;
	pNewValue->m_strID = pValueDef->m_strID;
	GetPngFilePath(strItemPath, strPngFile);
	pNewValue->m_strVal = strPngFile;
	pParent->AddNewChild(pNewValue);

	return TRUE;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_NewValue(CExBaseList *pParent, CRptTemp_ValueDef* pValueDef, CValues *pValues)
{
	if (pValues == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	CValue* pValue = (CValue *)pValues->FindByID(pValueDef->m_strID);

	CRptTemp_Value *pNewValue = new CRptTemp_Value();
	pNewValue->m_strName = pValueDef->m_strName;
	pNewValue->m_strID = pValueDef->m_strID;
	pParent->AddNewChild(pNewValue);
	CString strRptValue;
	CReport *pReport = (CReport *)pValues->GetParent();
	CGbItemBase *pItemBase = (CGbItemBase *)pReport->GetParent()->GetParent();

	if (! GenRpt_Xml_ProcessRptValue(strRptValue, pValueDef->m_strID, pReport))
	{
		pNewValue->m_strVal = _T("未找到结果值");
		return FALSE;
	}

	if (pValueDef->m_strID != g_strTestResultDescriptKey)
	{
		CDataTypeValue *pDataTypeValue = GetDataTypeValue(pValueDef->m_strID, pItemBase, strRptValue);

		if (pDataTypeValue != NULL)
		{
			//如果找到数据类型定义，则直接采用数据类型取值的名称，不再处理修约。仅限于电气量项目
			pNewValue->m_strVal = pDataTypeValue->m_strName;
			return TRUE;
		}
	}

	pValueDef->UpdatePrecision();
	bRet = GenRpt_Xml_NewValue_ProcessVal(strRptValue, pNewValue->m_strVal, pValueDef->m_strProcess, pValueDef->m_nPrecision);
	//pNewValue->m_strVal = strRptValue;

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_NewValue(CExBaseList *pParent, CRptTemp_ValueDef* pValueDef, CReport *pReport)
{
	if (pReport == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	CRptTemp_Value *pNewValue = new CRptTemp_Value();
	pNewValue->m_strName = pValueDef->m_strName;
	pNewValue->m_strID = pValueDef->m_strID;
	pParent->AddNewChild(pNewValue);
	CString strRptValue;
	CGbItemBase *pItemBase = (CGbItemBase *)pReport->GetParent()->GetParent();

	if (! GenRpt_Xml_ProcessRptValue(strRptValue, pValueDef->m_strID, pReport))
	{
		pNewValue->m_strVal = _T("未找到结果值");
		return FALSE;
	}

	if (pValueDef->m_strID != g_strTestResultDescriptKey)
	{
		CDataTypeValue *pDataTypeValue = GetDataTypeValue(pValueDef->m_strID, pItemBase, strRptValue);

		if (pDataTypeValue != NULL)
		{
			//如果找到数据类型定义，则直接采用数据类型取值的名称，不再处理修约。仅限于电气量项目
			pNewValue->m_strVal = pDataTypeValue->m_strName;
			return TRUE;
		}
	}

	pValueDef->UpdatePrecision();
	bRet = GenRpt_Xml_NewValue_ProcessVal(strRptValue, pNewValue->m_strVal, pValueDef->m_strProcess, pValueDef->m_nPrecision);
	//pNewValue->m_strVal = strRptValue;

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_NewValue_ProcessVal(const CString& strSrcVal, CString &strVal, const CString &strProcess, long nPrecision)
{
	BOOL bRet = TRUE;
	CString strAdd;
	double dVal = CString_To_double(strSrcVal);
	strVal = strSrcVal;

	if (strSrcVal == _T("--") || strSrcVal == _T("未动作"))
	{
		return TRUE;
	}

	if (strProcess.IsEmpty() && nPrecision < 0)
	{
		//不处理也不修约，比如：结果描述
		GenRpt_Xml_NewValue_ProcessVal_AdjustVal(strVal);
		return TRUE;
	}

	//目前对于报告数据处理的，只涉及到比例系数（s到ms，要乘以1000）
	//所以在修约和报告比例系数时，先处理比例系数
	//后面若扩充其它的报告数据处理，则需要根据strProcess，进行特殊处理。以此确定先处理strProcess还是先处理修约。
	if (! strProcess.IsEmpty())
	{
		CBkmkDataProcess *pProcess = FindDataProcessByID(strProcess);

		if (pProcess == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("未找到报告数据处理的定义【%s】"), strProcess.GetString());
			bRet = FALSE;
		}
		else
		{
			bRet = pProcess->ProcessData(strVal, strAdd, -1);
			dVal = CString_To_double(strVal);
		}
	}

	if (nPrecision >= 0)
	{
		// 		long nCoef = 1;
		// 		double dCoef = 1.0;
		// 		long nCount = nPrecision;
		// 		
		// 		while (nCount > 0)
		// 		{
		// 			nCoef *= 10;
		// 			dCoef *= 10;
		// 			nCount--;
		// 		}
		// 
		// 		//dVal = math_ValueRevised(dVal, nPrecision);
		// 		dVal = ((int)(dVal*nCoef+0.5))/dCoef; 
		CString strFormat;
		strFormat.Format(_T("%%.%df"), nPrecision);
		strVal.Format(strFormat, dVal);
	}
	else
	{
		strVal.Format(_T("%f"), dVal);
	}

	if (! strAdd.IsEmpty())
	{
		strVal = strVal + strAdd;
	}

	GenRpt_Xml_NewValue_ProcessVal_AdjustVal(strVal);
	return bRet;
}

void CRptTemplate_GenXmlTool::GenRpt_Xml_NewValue_ProcessVal_AdjustVal(CString &strVal)
{
	if (strVal == _T("-0.0000000"))
	{
		strVal = _T("0.0000000");
	}

	if (strVal == _T("-0.000000"))
	{
		strVal = _T("0.000000");
	}

	if (strVal == _T("-0.00000"))
	{
		strVal = _T("0.00000");
	}

	if (strVal == _T("-0.0000"))
	{
		strVal = _T("0.0000");
	}

	if (strVal == _T("-0.000"))
	{
		strVal = _T("0.000");
	}

	if (strVal == _T("-0.00"))
	{
		strVal = _T("0.00");
	}

	if (strVal == _T("-0.0"))
	{
		strVal = _T("0.0");
	}

	if (strVal == _T("-0"))
	{
		strVal = _T("0");
	}
}

//处理报告数据：m_pValues，m_pRptDvmDataset
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessRptValue(CString &strRptValue, const CString &strDataID, CReport *pReport)
{
	if (pReport == NULL)
	{
		return FALSE;
	}

	//处理：此处报告数据，可能来自pReport->m_pRptDvmDataset;
	CValue *pFind = (CValue*)pReport->m_pValues->FindByID(strDataID);
	CDvmData *pRptData = (CDvmData *)pReport->m_pRptDvmDataset->FindByID(strDataID);

	if (pFind == NULL && pRptData == NULL)
	{
		if (m_bCurrentItems_Ain)
		{
			//遥测数据反向映射
			CDataGroup *pAinDataMapCfg = m_pGuideBook->GetAinDataMapCfg();
			CDataGroup *pAinRatios = m_pGuideBook->GetAinRatios();

			if (pAinDataMapCfg == NULL)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("未找到遥测数据映射，导出失败！"));
				return FALSE;
			}

			CDvmData *pMap = (CDvmData *)pAinDataMapCfg->FindByID(strDataID);

			if (pMap != NULL)
			{
				pFind = (CValue*)pReport->m_pValues->FindByID(pMap->m_strValue);

				if (pFind == NULL)
				{
					pRptData = (CDvmData *)pReport->m_pRptDvmDataset->FindByID(pMap->m_strValue);

					if (pRptData == NULL)
					{
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告中找不到结果参数【%s】"), strDataID);
						return FALSE;
					}
					else
					{
						strRptValue = pRptData->m_strValue;

					}
				}
				else
				{
					strRptValue = pFind->m_strValue;
				}

				GenRpt_Xml_ProcessVal_AinRatios(pMap, pAinRatios, strRptValue);//处理遥测数据，根据变比换算
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("遥测参数映射中，找不到映射数据【%s】"), strDataID);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告中找不到结果参数【%s】"), strDataID);
				return FALSE;
			}
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告中找不到结果参数【%s】"), strDataID);
			return FALSE;
		}
	}
	else if(pFind != NULL)
	{
		strRptValue = pFind->m_strValue;
	}
	else if (pRptData != NULL)
	{
		strRptValue = pRptData->m_strValue;
	}

	return TRUE;
}

//获取报告值，状态序列部分参数特殊处理
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessRptValue_StateTest(CString &strRptValue, const CString &strDataID)
{
	if (strDataID.Find(_T("TtripBegin_State")) >= 0
		|| strDataID.Find(_T("TtripEnd_State")) >= 0 )
	{
		//计时起点、终点：状态
		//state_0、……、state_19   BinTrig=开入量触发
		if (strRptValue == _T("BinTrig"))
		{
			strRptValue = _T("开入量触发");
		}
		else
		{
			long nPos = strRptValue.Find(_T("_"));
			strRptValue = strRptValue.Mid(nPos + 1);
			long nState = CString_To_long(strRptValue);
			strRptValue.Format(_T("状态%d"), nState+1);//索引号从0开始。
		}

		return TRUE;
	}
	else if (strDataID.Find(_T("TtripBegin_Bin")) >= 0
		|| strDataID.Find(_T("TtripEnd_Bin")) >= 0 )
	{
		//计时起点、终点：开入选择
		//ActBin_4$0=开入E 1->0 【第一个数字，索引号，从0开始。后面的数字，表示开入变位的状态。0=1->0,1=0->1】
		if (strRptValue.IsEmpty())
		{
			strRptValue = _T("--");
		}
		else
		{
			CString strLeft,strRight;
			long nPos = strRptValue.Find(_T("$"));
			strLeft = strRptValue.Left(nPos);
			strRight = strRptValue.Mid(nPos+1);

			nPos = strLeft.Find(_T("_"));
			strLeft = strLeft.Mid(nPos + 1);
			long nIndex = CString_To_long(strLeft);
			char ch = 'A' + nIndex;
			strRptValue = "开入";
			strRptValue += ch;
			
			if (strRight == _T("0"))
			{
				strRptValue += _T(" 1->0");
			}
			else
			{
				strRptValue += _T(" 0->1");
			}
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessRptValue_GetValue(CString &strRptValue, const CString &strDataID, CReport *pReport, CGbItemBase *pGbItem, const CString& strProcess, long nPrecision)
{
	BOOL bRet = TRUE;

	if (pReport == NULL)
	{
		return FALSE;
	}

	if (! GenRpt_Xml_ProcessRptValue(strRptValue, strDataID, pReport))
	{
		//strRptValue = _T("未找到结果参数值");
		return FALSE;
	}

	if ( GenRpt_Xml_ProcessRptValue_StateTest(strRptValue, strDataID) )
	{
		//根据strDataID，若判定状态序列项目特殊ID，则特殊处理
		return TRUE;
	}

	CDataTypeValue *pDataTypeValue = NULL;

	if (strDataID != g_strTestResultDescriptKey)
	{
		pDataTypeValue = GetDataTypeValue(strDataID, pGbItem, strRptValue);

		if (pDataTypeValue != NULL)
		{
			//如果找到数据类型定义，则直接采用数据类型取值的名称，不再处理修约。仅限于电气量项目
			strRptValue = pDataTypeValue->m_strName;
		}
	}

	if (pDataTypeValue == NULL)
	{
		CString strDestValue;
		//没取到数据类型，表示需要处理修约
		if (! GenRpt_Xml_GridDef_FillRow_ProcessVal(strRptValue, strDestValue, strProcess, nPrecision))
		{
			bRet = FALSE;
		}

		strRptValue = strDestValue;
	}

	return bRet;
}

//处理遥测数据，根据采样值变比，进行换算
/*
<group id="AinRatios" name="采样变比信息">
<data name="装置采样" id="DevMeas" value="1" data-type=""/>【装置采样是一次值、还是二次值。取值：1|2】
<data name="PT一次侧" id="PtPrimary" value="220" data-type=""/>【PT一次侧单位为kV】
<data name="Pt二次侧" id="PtSecondary" value="100" data-type=""/>【PT二次侧单位为V】
<data name="Ct一次侧" id="CtPrimary" value="" data-type=""/>
<data name="Ct二次侧" id="CtSecondary" value="" data-type=""/>【CT一次、二次侧单位均为A】
</group>
*/
//形参strRptValue。传入时，已经是从报告中查找到的报告数据值，此处经过换算后，重新赋值给strRptValue返回
void CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessVal_AinRatios(CDvmData *pAinDataMap, CDataGroup *pAinRatios, CString &strRptValue)
{
	if (pAinRatios == NULL || pAinRatios == NULL)
	{
		return;
	}

	CDvmData *pDevMeas = (CDvmData *)pAinRatios->FindByID(ID_PARA_DevMeas);

	if (pDevMeas == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到装置采样数据是一次值还是二次值的配置……"));
		return;
	}

	if (pDevMeas->m_strValue == "2")
	{
		//二次值，不用根据变比换算
		return;
	}

	//遥测参数映射时，都是固定ID映射
	if (pAinDataMap->m_strID == _T("MIa")
		|| pAinDataMap->m_strID == _T("MIb")
		|| pAinDataMap->m_strID == _T("MIc"))
	{
		return GenRpt_Xml_ProcessVal_AinRatios_I(pAinRatios, strRptValue);
	}
	else if (pAinDataMap->m_strID == _T("MUa")
		|| pAinDataMap->m_strID == _T("MUb")
		|| pAinDataMap->m_strID == _T("MUc"))
	{
		return GenRpt_Xml_ProcessVal_AinRatios_U(pAinRatios, strRptValue);
	}
	else if (pAinDataMap->m_strID == _T("P")
		|| pAinDataMap->m_strID == _T("Q"))
	{
		return GenRpt_Xml_ProcessVal_AinRatios_PQ(pAinRatios, strRptValue);
	}
	else
	{
		//剩余的功率因素和频率，不用换算
		return;
	}
}

void CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessVal_AinRatios_I(CDataGroup *pAinRatios, CString &strRptValue)
{
	CDvmData *pCtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比一次值……"));
		return;
	}

	CDvmData *pCtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比二次值……"));
		return;
	}

	double dPrimary = CString_To_double(pCtPrimary->m_strValue);
	double dSecondary = CString_To_double(pCtSecondary->m_strValue);
	double dRatio = dPrimary / dSecondary;

	double dRptVal = CString_To_double(strRptValue);
	dRptVal = dRptVal / dRatio;
	strRptValue.Format(_T("%.6f"), dRptVal);
}

void CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessVal_AinRatios_U(CDataGroup *pAinRatios, CString &strRptValue)
{
	CDvmData *pPtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比一次值……"));
		return;
	}

	CDvmData *pPtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比二次值……"));
		return;
	}

	double dPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dSecondary = CString_To_double(pPtSecondary->m_strValue);
	double dRatio = dPrimary * 1000 / dSecondary;  //PT变比是 kV / V。

	//装置采样一次值时，电压单位为kV
	double dRptVal = CString_To_double(strRptValue);
	dRptVal = dRptVal * 1000 / dRatio;
	strRptValue.Format(_T("%.6f"), dRptVal);
}

void CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessVal_AinRatios_PQ(CDataGroup *pAinRatios, CString &strRptValue)
{
	CDvmData *pCtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比一次值……"));
		return;
	}

	CDvmData *pCtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比二次值……"));
		return;
	}

	CDvmData *pPtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比一次值……"));
		return;
	}

	CDvmData *pPtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比二次值……"));
		return;
	}

	double dCtPrimary = CString_To_double(pCtPrimary->m_strValue);
	double dCtSecondary = CString_To_double(pCtSecondary->m_strValue);
	double dPtPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dPtSecondary = CString_To_double(pPtSecondary->m_strValue);
	//PT变比是 kV / V。
	double dRatio = (dCtPrimary / dCtSecondary) * (dPtPrimary * 1000 / dPtSecondary);  

	//装置采样一次值时，电压单位为kV。功率的单位是MW，MVAr
	double dRptVal = CString_To_double(strRptValue);
	dRptVal = dRptVal * 1000000 / dRatio;
	strRptValue.Format(_T("%.6f"), dRptVal);
}

CRptTemp_ReportTemplate* CRptTemplate_GenXmlTool::GenRpt_Xml_NewReportTemplate(CExBaseList *pParent)
{
	CRptTemp_ReportTemplate* pNew = new CRptTemp_ReportTemplate();
	pParent->AddNewChild(pNew);
	return pNew;
}

CRptTemp_Title* CRptTemplate_GenXmlTool::GenRpt_Xml_NewTitle(CExBaseList *pParent)
{
	CRptTemp_Title* pNew = new CRptTemp_Title();
	pParent->AddNewChild(pNew);
	return pNew;
}

CRptTemp_Text* CRptTemplate_GenXmlTool::GenRpt_Xml_NewText(CExBaseList *pParent)
{
	CRptTemp_Text* pNew = new CRptTemp_Text();
	pParent->AddNewChild(pNew);
	return pNew;
}

CRptTemp_Grid* CRptTemplate_GenXmlTool::GenRpt_Xml_NewGrid(CExBaseList *pParent, CRptTemp_GridDef *pGridDef)
{
	CRptTemp_Grid* pNew = new CRptTemp_Grid();
	pParent->AddNewChild(pNew);
	pNew->m_strData_Mode = pGridDef->m_strData_Mode;
	pNew->m_nShowBorders = pGridDef->m_nShowBorders;

	//处理head
	POS pos = pGridDef->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pGridDef->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_HEAD)
		{
			continue;
		}

		CRptTemp_Head *pHead = (CRptTemp_Head *)pObj;
		CRptTemp_Head *pNewHead = (CRptTemp_Head *)pHead->CloneEx(TRUE, TRUE);
		pNew->AddNewChild(pNewHead);
	}

	return pNew;
}

//根据项目等级，查找相对等级的父项目：CItems节点。并返回名称
CString CRptTemplate_GenXmlTool::GetItemName(CGbItemBase *pItemBase, long nItemLevel)
{
	//查找相对项目时，一定是基于rootnode的CItems查找的
	ASSERT(pItemBase->GetClassID() == GBCLASSID_ITEMS);

	if (pItemBase->GetClassID() != GBCLASSID_ITEMS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("查找项目名称出错，基准项目不是CItems【%s】"), pItemBase->m_strName.GetString());
		return _T("");
	}

	CItems *pItems = (CItems *)pItemBase;
	ASSERT(pItems->IsTypeRootNode());

	if (! pItems->IsTypeRootNode())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("查找项目名称出错，基准项目不是rootnode【%s】"), pItemBase->m_strName.GetString());
		return _T("");
	}

	CExBaseObject *pParentItem = pItemBase;
	UINT nClassID = 0;
	CString strTextFind;

	while (nItemLevel > 0)
	{
		pParentItem = (CExBaseObject *)pParentItem->GetParent();
		nClassID = pParentItem->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			break;
		}

		nItemLevel--;

		if (nItemLevel == 0)
		{
			strTextFind = pParentItem->m_strName;
		}
	}

	return strTextFind;
}

//根据参数ID，获取项目的报告值
CString CRptTemplate_GenXmlTool::GetItemReportValue(CGbItemBase *pItemBase, const CString &strDataID)
{
	UINT nClassID = pItemBase->GetClassID();

	//只考虑电气量项目和阻抗搜索项目
	//2023-11-6  增加了CItems。过励磁项目，结论是从父节点取
	if ((nClassID != GBCLASSID_MACROTEST)
		&& (nClassID != GBCLASSID_MACROCHARITEMS)
		&& (nClassID != GBCLASSID_ITEMS))
	{
		return _T("");
	}

	CReport *pReport = pItemBase->GetReport(-1);

	if (pReport == NULL)
	{
		return _T("");
	}

	CString strRptValue;
	GenRpt_Xml_ProcessRptValue(strRptValue, strDataID, pReport);
	return strRptValue;
}

//从数据接口中，查找对应的接口数据值
CString CRptTemplate_GenXmlTool::GetItemsTec(CRptTemp_TextDef *pTextDef, const CString &strDataID)
{
	CDataGroup *pItemsTec = pTextDef->GetItemsTec();

	if (pItemsTec == NULL)
	{
		return _T("");
	}

	return GetItemsTec(pItemsTec, strDataID);
}

CString CRptTemplate_GenXmlTool::GetItemsTec(CDataGroup *pItemsTec, const CString &strDataID)
{
	if (pItemsTec == NULL)
	{
		return _T("");
	}

	CDvmData *pData = (CDvmData *)pItemsTec->FindByID(strDataID);

	if (pData == NULL)
	{
		return _T("");
	}

	return pData->m_strValue;
}

void CRptTemplate_GenXmlTool::GetItemReports(CExBaseList *pRptLists, CGbItemBase *pItemBase)
{
	pRptLists->RemoveAll();

	if (pItemBase == NULL)
	{
		return;
	}

	long nTestCount = pItemBase->GetItemTestCount();
	CReports *pRpts = pItemBase->GetReports();

	if (pRpts->GetCount() == 0 )
	{
		return;
	}

	if (pRpts->GetCount() < nTestCount)
	{
		//说明报告数量与测试次数对应不起来，只取最后一次
		pRptLists->AddTail(pRpts->GetTail());
		return;
	}

	UINT nClassID = pItemBase->GetClassID();

	if (nClassID == GBCLASSID_MACROTEST)
	{
		//对于电气量项目，此处还要处理电气量项目本身的重复次数
		CMacroTest *pMacroTest = (CMacroTest *)pItemBase;
		long nMacroTestRepeatTimes = pMacroTest->m_nRepeatTimes;

		if (nMacroTestRepeatTimes > 1)
		{
			nTestCount += nTestCount/nMacroTestRepeatTimes;  //对于电气量自己重复测试的部分，应当加上计算的报告数量
		}
	}

	POS pos = pRpts->GetTailPosition();

	while(nTestCount > 0 &&  pos != NULL)
	{
		CReport *pRpt = (CReport *)pRpts->GetPrev(pos);
		pRptLists->AddTail(pRpt);
		pRptLists->BringToHead(pRpt);
		nTestCount--;
	}
}

void CRptTemplate_GenXmlTool::GetPngFilePath(const CString &strItemPath, CString &strPngFile)
{
	strPngFile = _P_GetInstallPath();
	strPngFile += _T("Stt\\Workspace\\Img\\");
	strPngFile += strItemPath;
	strPngFile += _T("Img.png");  //特性图，以固定的命名方式，存在固定的路径
}	

//按照故障类型，返回图片名称，返回值判定图片是否存在
BOOL CRptTemplate_GenXmlTool::GetPngFilePath_FaultType(const CString &strItemPath, CString &strPngFile, const CString &strMode)
{
	 //特性图，以固定的命名方式，存在固定的路径
	strPngFile = _P_GetInstallPath();
	strPngFile += _T("Stt\\Workspace\\Img\\");
	strPngFile += strItemPath;
	strPngFile += _T("$");  
	strPngFile += strMode;
	strPngFile += _T(".png");

	return IsFileExist(strPngFile);
}

void CRptTemplate_GenXmlTool::GetPngFilePath_Char(CItems *pItems, CString &strPngFile)
{
	CTestMacroCharParas *pCharParas = pItems->GetTestMacroCharParas();
	CCharacteristics oChars;
	oChars.SetXml(pCharParas->m_strParaText, CCharacteristicXmlRWKeys::g_pXmlKeys);
	CCharacteristic *pChar = (CCharacteristic *)oChars.FindByClassID(CHARCLASSID_CCHARACTERISTIC);

	if (pChar == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("项目【%s】没找到特性曲线信息--1，报告中无法生成曲线方程"), pItems->m_strName.GetString());
		return;
	}

	CCharacterArea *pArea = (CCharacterArea *)pChar->FindByClassID(CHARCLASSID_CCHARACTERAREA);

	if (pArea == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("项目【%s】没找到特性曲线信息--2，报告中无法生成曲线方程"), pItems->m_strName.GetString());
		return;
	}

	//走到此处的一定是反时限
	CCharElementInverse *pElement = (CCharElementInverse *)pArea->GetHead();  //有且仅有一个曲线

	if (pElement == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("项目【%s】没找到特性曲线信息--3，报告中无法生成曲线方程"), pItems->m_strName.GetString());
		return;
	}

	strPngFile = _P_GetInstallPath();
	strPngFile += _T("Stt/Resource/");
	strPngFile += "images/";

	CString strCostomText;

	if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEEE)
	{
		strPngFile += "IEEE";
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIAC)
	{
		strPngFile += "IAC";
	}
	else if(pElement->GetClassID() == CHARCLASSID_CCHARELEMENTI2T)
	{
		strPngFile += "I2T";
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIEC)
	{
		strPngFile += "IEC";
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTRXIDG)
	{
		strPngFile += "RXIDG";
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTRICURVE)
	{
		strPngFile += "RICURVE";
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTLABIECCURVE)
	{
		strPngFile += "LABIECCURVE";
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIT)
	{
		strPngFile += "IT";
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTI2TEx)
	{
		strPngFile += "I2TEx";
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTUIVP)
	{
		strPngFile += "UIVP";
	}
	else if (pElement->GetClassID() == CHARCLASSID_CCHARELEMENTIUF)
	{
		strPngFile += "IUF";
	}

	strPngFile += "_1.bmp";
}

void CRptTemplate_GenXmlTool::GetMacroTest_AllParas(CExBaseList *pParas, CItems *pRootNode)
{
	if (pRootNode == NULL)
	{
		return;
	}

	if (!pRootNode->IsTypeRootNode())
	{
		return;
	}

	CTestMacroUiParas *pUiParas = pRootNode->GetTestMacroUiParas();

	if (pUiParas == NULL)
	{
		CMacroTest *pMacroTest = (CMacroTest *)pRootNode->FindByID(pRootNode->m_strStxmlFile);

		if (pMacroTest != NULL)
		{
			return GetMacroTest_AllParas(pParas, pMacroTest);
		}
	}
	else
	{
		CDataGroup oUiParas;
		BSTR bstrText = pUiParas->m_strParaText.AllocSysString();
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		BOOL bRet = oUiParas.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		SysFreeString(bstrText);

		GetMacroTest_AllParas_UIParas(pParas, &oUiParas, &oUiParas);
	}
}

void CRptTemplate_GenXmlTool::GetMacroTest_AllParas(CExBaseList *pParas, CMacroTest *pMacroTest)
{
	if (pMacroTest == NULL)
	{
		return;
	}

	pParas->DeleteAll();

	//先处理界面参数
	CTestMacroUiParas *pUiParas = pMacroTest->GetTestMacroUiParas();

	if (pUiParas == NULL)
	{
		CItems *pItems = Gb_GetFirstParentItems(pMacroTest, TRUE);

		if (pItems != NULL)
		{
			pUiParas = pItems->GetTestMacroUiParas();
		}
	}

	if (pUiParas != NULL)
	{
		CDataGroup oUiParas;
		BSTR bstrText = pUiParas->m_strParaText.AllocSysString();
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		BOOL bRet = oUiParas.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		SysFreeString(bstrText);

		GetMacroTest_AllParas_UIParas(pParas, &oUiParas, &oUiParas);
	}

	//后处理电气量项目故障参数
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CMacroTestParaDatas *pFaultParas = pMacroTestPara->GetFaultParaDatas();

	POS pos = pFaultParas->GetHeadPosition();

	while (pos != NULL)
	{
		CMacroTestParaData *p = (CMacroTestParaData *)pFaultParas->GetNext(pos);
		CDvmData *pFind = (CDvmData *)pParas->FindByID(p->m_strID);

		if (pFind == NULL)
		{
			CDvmData *pData = new CDvmData();
			pData->m_strValue = p->m_strExpression;
			pData->m_strID = p->m_strID;
			pParas->AddNewChild(pData);
		}
		else
		{
			pFind->m_strValue = p->m_strExpression;  //以电气量项目的故障参数为准
		}
	}
}

void CRptTemplate_GenXmlTool::GetMacroCharItems_AllParas(CExBaseList *pParas, CMacroCharItems *pMacroCharItems)
{
	if (pMacroCharItems == NULL)
	{
		return;
	}

	pParas->DeleteAll();

	//先处理界面参数
	CTestMacroUiParas *pUiParas = NULL;
	CItems *pItems = Gb_GetFirstParentItems(pMacroCharItems, TRUE);

	if (pItems != NULL)
	{
		pUiParas = pItems->GetTestMacroUiParas();
	}

	if (pUiParas != NULL)
	{
		CDataGroup oUiParas;
		BSTR bstrText = pUiParas->m_strParaText.AllocSysString();
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		BOOL bRet = oUiParas.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		SysFreeString(bstrText);

		GetMacroTest_AllParas_UIParas(pParas, &oUiParas, &oUiParas);
	}

	//后处理电气量故障参数
	CMacroTestPara *pMacroTestPara = pMacroCharItems->GetMacroTestPara();
	CMacroTestParaDatas *pFaultParas = pMacroTestPara->GetFaultParaDatas();

	POS pos = pFaultParas->GetHeadPosition();

	while (pos != NULL)
	{
		CMacroTestParaData *p = (CMacroTestParaData *)pFaultParas->GetNext(pos);
		CDvmData *pFind = (CDvmData *)pParas->FindByID(p->m_strID);

		if (pFind == NULL)
		{
			CDvmData *pData = new CDvmData();
			pData->m_strValue = p->m_strExpression;
			pData->m_strID = p->m_strID;
			pParas->AddNewChild(pData);
		}
		else
		{
			pFind->m_strValue = p->m_strExpression;  //以电气量项目的故障参数为准
		}
	}
}

void CRptTemplate_GenXmlTool::GetMacroTest_AllParas_UIParas(CExBaseList *pParas, CDataGroup *pUIParas, CExBaseList *pRoot)
{
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	POS pos = pUIParas->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pUIParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;
			CDvmData *pNew = new CDvmData();
			pNew->m_strID = pData->GetIDPathEx(pRoot, FALSE);//pData->m_strID;
			pNew->m_strValue = pData->m_strValue;
			pParas->AddNewChild(pNew);
		}
		else if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pGrp = (CDataGroup *)pObj;
			GetMacroTest_AllParas_UIParas(pParas, pGrp, pRoot);
		}
	}
}

BOOL CRptTemplate_GenXmlTool::IsEnable_TextDef(CGbItemBase *pItemBase, CRptTemp_TextDef *pTextDef)
{
	//提高效率，存在enable节点，才判断使能
	if (pTextDef->GetEnable() == NULL)
	{
		//默认使能
		return TRUE;
	}

	UINT nClassID = pItemBase->GetClassID();
	CExBaseList oListParas;

	if (nClassID == GBCLASSID_ITEMS)
	{
		CItems *pItems = (CItems *)pItemBase;
		GetMacroTest_AllParas(&oListParas, pItems);
	}
	else if (nClassID == GBCLASSID_MACROTEST)
	{
		CMacroTest *pMacroTest = (CMacroTest *)pItemBase;
		GetMacroTest_AllParas(&oListParas, pMacroTest);
	}
	else if (nClassID == GBCLASSID_MACROCHARITEMS)
	{
		CMacroCharItems *pMacroCharItems = (CMacroCharItems *)pItemBase;
		GetMacroCharItems_AllParas(&oListParas, pMacroCharItems);
	}

	return pTextDef->IsEnable(&oListParas);
}

CBkmkDataProcess* CRptTemplate_GenXmlTool::FindDataProcessByID(const CString &strID)
{
	CBkmkDataProcessMngr* pProcessMngr = m_oRptTemplateCfg.GetBkmkDataProcessMngr();

	if (pProcessMngr == NULL)
	{
		return NULL;
	}

	return (CBkmkDataProcess *)pProcessMngr->FindByID(strID);
}

BOOL CRptTemplate_GenXmlTool::IsCurrentItemsAin(const CString &strItemsID)
{
	if (strItemsID == _T("AccuracyTest")
		|| strItemsID == _T("PowerAccuracyTest")
		|| strItemsID == _T("FreqPFTest")
		|| strItemsID == _T("FreqCurrTest")
		|| strItemsID == _T("SupplyVolHeatTest")
		|| strItemsID == _T("HarmChangeTest")
		|| strItemsID == _T("PFOverTest")
		|| strItemsID == _T("PowerVolCurrTest"))
	{
		m_bCurrentItems_Ain = TRUE;
	}
	else
	{
		m_bCurrentItems_Ain = FALSE;
	}

	return m_bCurrentItems_Ain;
}

CDataTypeValue* CRptTemplate_GenXmlTool::GetDataTypeValue(const CString &strIDPath, CGbItemBase *pItemBase, const CString &strValue)
{
	if (pItemBase == NULL)
	{
		return NULL;
	}

	if (pItemBase->GetClassID() != GBCLASSID_MACROTEST)
	{
		//仅限于电气量项目
		return NULL;
	}

	if (strIDPath == _T("RsltDsc"))
	{
		//结果描述不处理
		return NULL;
	}

	CString strMacroID;
	CMacroTest *pMacroTest = (CMacroTest *)pItemBase;
	strMacroID = pMacroTest->GetTestMacroID();

	return m_pGuideBook->GetDataTypeValue(strMacroID, strIDPath, strValue);
}

void CRptTemplate_GenXmlTool::Init(CGuideBook *pGudieBook, BOOL bGenDoc)
{
	//导出实时docxml用，暂时不用考虑dat文件
	RemoveAll();

	if (m_pRptTemp_TestMacroUiRpt == NULL)
	{
		m_pRptTemp_TestMacroUiRpt = new CRptTemp_TestMacroUiRpt();
	}

	if (pGudieBook != NULL)
	{
		m_pGuideBook = pGudieBook;
	}

	m_pRptTemp_TestMacroUiRpt->DeleteAll();
	m_pCurrUpdateItems = NULL;
	GenRpt_Xml_Doc_ProcessReportHead();

	CString strDocXmlFile;
	strDocXmlFile = GetWorkSpacePath();
	strDocXmlFile += _T("RealTime.docxml");
	m_strXmlFile_Doc = strDocXmlFile;

	if (bGenDoc)
	{
		CDevice *pDevice = pGudieBook->GetDevice();
		GenRpt_Xml_Doc_Device(m_pRptTemp_TestMacroUiRpt, pDevice);
	}
}

BOOL CRptTemplate_GenXmlTool::SaveDocXmlFile()
{
	if (m_pRptTemp_TestMacroUiRpt == NULL)
	{
		return FALSE;
	}

	return m_pRptTemp_TestMacroUiRpt->SaveXmlFile(m_strXmlFile_Doc, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);
}

//每次实时刷新报告视图，均只保存当前需要整体刷新的Items的部分，以减小文件大小
BOOL CRptTemplate_GenXmlTool::SaveDocXmlFile(CRptTemp_Items *pRptItems)
{
	if (pRptItems != NULL)
	{
		return pRptItems->SaveXmlFile(m_strXmlFile_Doc, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);
	}

	if (m_pCurrUpdateItems != NULL)
	{
		return m_pCurrUpdateItems->SaveXmlFile(m_strXmlFile_Doc, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);
	}

	return m_pRptTemp_TestMacroUiRpt->SaveXmlFile(m_strXmlFile_Doc, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);
}

//仅保存报告头，采用临时CRptTemp_Items保存，方便上位机统一处理
//用于新建测试、报告头单独刷新时
BOOL CRptTemplate_GenXmlTool::SaveDocXmlFile_RptHead()
{
	ASSERT(m_pReportHeadParas != NULL);
	ASSERT(m_pRptHeadTemplate != NULL);

	CRptTemp_Items *pItems = new CRptTemp_Items();
	pItems->m_strID = _T("ReportHead");
	pItems->AddTail(m_pRptHeadTemplate);
	BOOL bRet = pItems->SaveXmlFile(m_strXmlFile_Doc, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);

	pItems->Remove(m_pRptHeadTemplate);
	delete pItems;
	pItems = NULL;
	return bRet;
}

CRptTemp_Items* CRptTemplate_GenXmlTool::FindItemsByGbItem(CExBaseObject *pGbItem)
{
	CRptTemp_Items *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_Items *pItems = (CRptTemp_Items *)GetNext(pos);

		if (pItems->m_pItems == pGbItem)
		{
			pFind = pItems;
			break;
		}
	}

	return pFind;
}

//形参为新生成的rootnode：CItems
BOOL CRptTemplate_GenXmlTool::GenerateTemplate_Items(CExBaseObject *pItems)
{
	if (pItems == NULL)
	{
		return FALSE;
	}

	CRptTemp_Items *pRptItems = FindItemsByGbItem(pItems);

	if (pRptItems == NULL)
	{
		//表示第一次添加
		CExBaseObject *pParent = (CExBaseObject *)pItems->GetParent();
		UINT nClassID = pParent->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			//父节点是CItems
			CItems *pParentItems = (CItems *)pParent;
			CRptTemp_Items *pParentRptItems = FindItemsByGbItem(pParentItems);  //普通CItems，也要建立索引
			ASSERT(pParentRptItems != NULL);

			if (pParentRptItems == NULL)
			{
				return FALSE;
			}

			//找到父节点，则pItems对应的CRptTemp_Items对象，添加到pParentRptItems，作为其子对象
			return GenRpt_Xml_Doc_Items(pParentRptItems, (CItems *)pItems, TRUE);

		}
		else if (nClassID == GBCLASSID_DEVICE)
		{
			//父节点是CDevice。则pItems对应的CRptTemp_Items对象，直接添加到docxml的根节点
			return GenRpt_Xml_Doc_Items(m_pRptTemp_TestMacroUiRpt, (CItems *)pItems, TRUE);
		}
	}
	else
	{
		//表示是参数更新或追加，整体删除重新生成
		RemoveItemsByAncestor(pRptItems);  //避免重复释放，先移除有祖先关系的。同时也会移除自身
		CExBaseList *pParent = (CExBaseList *)pRptItems->GetParent();
		pParent->Delete(pRptItems);  //为简化算法，删除后整个重新刷新
		return GenRpt_Xml_Doc_Items(pParent, (CItems *)pItems, TRUE);
	}

	return FALSE;
}

//形参为新生成的CItems
BOOL CRptTemplate_GenXmlTool::GenerateItems_Items(CExBaseObject *pItems)
{
	if (pItems == NULL)
	{
		return FALSE;
	}

	//对于GenerateItems指令，可能是new-items，追加添加系列。
	//因此，可能已经完成了初始化
	if (m_pRptTemp_TestMacroUiRpt == NULL)
	{
		Init(m_pGuideBook);
	}

	return GenerateTemplate_Items(pItems);
}

void CRptTemplate_GenXmlTool::RemoveItemsByAncestor(CRptTemp_Items *pAncestorItems)
{
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_Items *pItems = (CRptTemp_Items *)GetNext(pos);

		if (pAncestorItems->IsAncestorOf(pItems))
		{
			Remove(pItems);
		}
	}
}

void CRptTemplate_GenXmlTool::RemoveItemsByDelete(CGbItemBase *pItemDelete)
{
	POS pos = GetHeadPosition();
	CExBaseList oListRemove;  //需要删除的链表

	while (pos != NULL)
	{
		CRptTemp_Items *pItems = (CRptTemp_Items *)GetNext(pos);

		if (pItems->m_pItems == pItemDelete
			|| pItemDelete->IsAncestorOf((CGbItemBase *)pItems->m_pItems))
		{
			Remove(pItems);
			oListRemove.AddTail(pItems);  //先添加的，可能是后添加的父节点，要后删
		}
	}

	//倒序删除所有需要删除的节点，避免内存泄漏和重复释放
	pos = oListRemove.GetTailPosition();

	while (pos != NULL)
	{
		CRptTemp_Items *pRptItems = (CRptTemp_Items *)oListRemove.GetPrev(pos);
		CExBaseList *pParent = (CExBaseList *)pRptItems->GetParent();
		pParent->Delete(pRptItems);
	}

	oListRemove.RemoveAll();
}

BOOL CRptTemplate_GenXmlTool::UpdateItem_Report(CGbItemBase *pItem)
{
	if (pItem == NULL)
	{
		return FALSE;
	}

	CItems *pRootNode = Gb_GetFirstParentItems(pItem, TRUE);

	if (pRootNode == NULL)
	{
		return FALSE;
	}

	CRptTemp_Items *pRptItems = FindItemsByGbItem(pRootNode);
	ASSERT(pRptItems != NULL);

	m_pCurrUpdateItems = pRptItems;
	//todo：更新pRptItems下索引中有绑定关系的docxml对象；
	POS pos = pRptItems->m_oList.GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	BOOL bRet = TRUE;

	while (pos != NULL)
	{
		pObj = pRptItems->m_oList.GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_TEXT)
		{
			CRptTemp_Text* pText = (CRptTemp_Text*)pObj;

			if (pText->m_pGbItemBase != pItem)
			{
				//没有绑定关系，不处理
				continue;
			}

			if (! UpdateItem_Report(pItem, pText))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_ROW)
		{
			CRptTemp_Row* pRow = (CRptTemp_Row*)pObj;

			if (pRow->m_pGbItemBase != pItem)
			{
				//没有绑定关系，不处理
				continue;
			}

			if (! UpdateItem_Report(pItem, pRow))
			{
				bRet = FALSE;
			}
		}
		else
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::UpdateItem_Report(CGbItemBase *pItem, CRptTemp_Row *pRow)
{
	CReport *pReport = pItem->GetReport(-1);

	if (pReport == NULL)
	{
		return FALSE;
	}

	BOOL bRet = TRUE;
	POS pos = pRow->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pRow->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_CELL)
		{
			continue;
		}

		CRptTemp_Cell *pCell = (CRptTemp_Cell *)pObj;
		CString strRptValue;

		if (! GenRpt_Xml_ProcessRptValue_GetValue(strRptValue, pCell->m_strDataID, pReport, pItem, pCell->m_strProcess, pCell->m_nPrecision))
		{
			bRet = FALSE;
		}

		pCell->m_strText = strRptValue;
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::UpdateItem_Report(CGbItemBase *pItem, CRptTemp_Text *pText)
{
	BOOL bRet = TRUE;
	CString strText = pText->m_strTextFormat;
	CString strTextContext;
	//形参4。为技术要求。实例化后的docxml中没有该信息，暂时传值NULL
	bRet = GenRpt_Xml_Doc_TextDef_GetContext(strText, strTextContext, pItem, NULL, pText->m_strData1_Id, pText->m_strData2_Id, pText->m_strData3_Id
		, pText->m_strData4_Id, pText->m_strData5_Id, pText->m_strData6_Id);

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::UpdateReportHeadParas(CDataGroup *pReportHeadParas)
{
	SetReportHeadParas(pReportHeadParas);

	if (m_pRptTemp_TestMacroUiRpt == NULL)
	{
		Init(m_pGuideBook);
	}

	CRptTemp_ReportTemplate *pReportHead = (CRptTemp_ReportTemplate *)m_pRptTemp_TestMacroUiRpt->FindByClassID(MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE);

	if (pReportHead != NULL)
	{
		m_pRptTemp_TestMacroUiRpt->Delete(pReportHead);
	}

	GenRpt_Xml_Doc_ProcessReportHead();

	return TRUE;
}