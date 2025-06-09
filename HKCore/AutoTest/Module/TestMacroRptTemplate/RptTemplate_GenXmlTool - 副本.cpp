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

	CString strSysPath;
	strSysPath = _P_GetInstallPath();
	strSysPath += _T("STT/");
	InitGbGenSysPath(strSysPath); 
	InitRptTemplateCfg();
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
//�����ǵ���XML��ʽ�ı��������ļ��Ĳ���
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

	//todo����������ͷ����ʱ������

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

//�ݹ���ã�ֻ����˹�������CItems
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_Normal(CExBaseList *pParent, CItems *pItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return FALSE;
	}

	//�����˹�������CItems�ڵ㣬ֻ��Ҫ�����ӵ�CItems����
	//��Ϊ�����˹�������CItems�ڵ㣬�Ӷ������CMacroTest��Ҳ��֪����Ҫ�����ı�����������Щ
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ���%s��������"), strFile.GetString());
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
<group id="items-tecs" data-type="items-tecs">������Ҫ��༭+����С��λ�����á�
	<group id="item-path" data-type="items-tec">��һ��group������һ����Ŀ�ļ���Ҫ��+�������ݱ���С��λ����id��дΪʵ����Ŀ·����
		<data id="rpt_tec_data1" value=""/>������Ҫ��id�ù̶�ǰ׺����rpt_tec_��������Ҫ������ж����
		<data name="����ֵС����λ��" data-type="int" id="rpt_precision_data1" value="1" min="0" max="4"/>����������С��λ���༭��id�ù̶�ǰ׺����rpt_precision_����С��λ���༭�����ж����
	</group>
	<group id="item-path" data-type="items-tec">
		<data id="rpt_tec_data1" value=""/>
	</group>
	<group id="item-path" data-type="items-tec">
		<data id="rpt_tec_data1" value=""/>
	</group>
	����
</group>
*/
//���¡�����Ҫ�� + ���������ݱ���С��λ�������ݽӿ�
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ŀ��%s����Ӧ�ļ���Ҫ�� + �������ݱ���С��λ������"), strItemPath.GetString());
		return FALSE;
	}

	pDest->InitDataValues(pItemTec, FALSE);

	return TRUE;
}

//rootnode�£�����ֻ����items��macrotest��char-macro-items
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
				continue;  //���˵�����ǰ�����Ժ�
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

//��������Ŀ�ĸ��ڵ㣬�����֣�CItems��CMacroCharItems��Ӧ�����ִ���
//������Ŀ��CItems�ĵ�����
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_RootNode_MacroTest(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroTest *pMacroTest)
{
	CString strMacroID = pMacroTest->GetTestMacroID();
	CExBaseList oListParas;
	GetMacroTest_AllParas(&oListParas, pMacroTest);
	CRptTemp_MacroTest *pRptTemp_MacroTestDef = pRptDef->FindMacroTestByMacroID(strMacroID, &oListParas);

	if (pRptTemp_MacroTestDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У��Ҳ���macrotest�ڵ㡾%s��"), strMacroID.GetString());
		//�Ҳ����������ǲ���Ҫ�����������ݵĵ�������Ŀ�����Է���TRUE
		return TRUE;
	}

	CRptTemp_ReportsDef* pRptTemp_ReportsDef = pRptTemp_MacroTestDef->GetRpeortsDef();

	if (pRptTemp_ReportsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У�macrotest�ڵ㡾%s��δ����reports-def"), strMacroID.GetString());
		return FALSE;
	}

	//�˴��������������ݲ�һ������pMacroTest���п������������ͨѶ������Ŀ
	CRptTemp_MacroTest* pRptMacroTestNew = GenRpt_Xml_NewMacroTest(pRptItems, pMacroTest);
	CExBaseList oRptLists;

	if (pRptTemp_ReportsDef->m_strData_Path.GetLength() > 0)
	{
		CGbItemBaseList oDestList;
		//ͨ����Ŀ���·����������Ŀ
		pMacroTest->SelectItems(pRptTemp_ReportsDef->m_strData_Path, oDestList);
		long nCount = oDestList.GetCount();

		if (nCount != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("��Ŀ��%s�����ҽ����Ψһ���ҵ���%d����Ŀ����Ŀ"), pRptTemp_ReportsDef->m_strData_Path.GetString(), nCount);
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

	//�˴�������Ҫ�޸ġ�Ԥ�����β�pMacroTest����ʱû���õ�������Ҫ�õ����˴����ܵô��������Ŀ����pDestItem
	BOOL bRet = GenRpt_Xml_MacroTest_Dat_Reports(pRptTemp_ReportsDef, &oRptLists, pRptMacroTestNew, pMacroTest);
	oRptLists.RemoveAll();
	return bRet;
}

//������Ŀ��CMacroCharItems�ĵ�����
//�β�1���������������ļ��ж����macro-char-itemsģ�壻
//�β�2��ʵ������macro-char-items�ڵ�
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_RootNode_MacroTest(CRptTemp_MacroCharItems *pMacroCharItemsDef, CRptTemp_MacroCharItems *pNewMacroCharItems, CMacroTest *pMacroTest)
{
	CRptTemp_MacroTest *pMacroTestDef = pMacroCharItemsDef->GetMacroTest();

	if (pMacroTestDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У�macro-char-items�ڵ㡾%s����δ����macrotest�ӽڵ�"), pMacroCharItemsDef->m_strMacro_Id.GetString());
		return FALSE;
	}

	CString strMacroID = pMacroTest->GetTestMacroID();

	if (strMacroID != pMacroTestDef->m_strMacro_Id)
	{
		//ֱ�ӷ���TRUE�����˵�����ID��ƥ��ĵ�������Ŀ
		return TRUE;
	}

	CRptTemp_ReportsDef* pRptTemp_ReportsDef = pMacroTestDef->GetRpeortsDef();

	if (pRptTemp_ReportsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У�macrotest�ڵ㡾%s��δ����reports-def"), strMacroID.GetString());
		return FALSE;
	}

	CRptTemp_MacroTest* pRptMacroTestNew = GenRpt_Xml_NewMacroTest(pNewMacroCharItems, pMacroTest);
	CExBaseList oRptLists;
	GetItemReports(&oRptLists, pMacroTest);

	BOOL bRet = GenRpt_Xml_MacroTest_Dat_Reports(pRptTemp_ReportsDef, &oRptLists, pRptMacroTestNew, pMacroTest);
	oRptLists.RemoveAll();
	return bRet;
}

//macro-char-items�ڵ㣬һ�㲻���ظ����ԣ��������ظ����Դ�����
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Dat_RootNode_MacroCharItems(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroCharItems *pMacroCharItems)
{
	BOOL bRet = TRUE;
	CString strMacroID = pMacroCharItems->GetTestMacroID();
	CRptTemp_MacroCharItems *pRptTemp_MacroCharItemsDef = pRptDef->FindMacroCharItemsByMacroID(strMacroID);

	if (pRptTemp_MacroCharItemsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У��Ҳ���macro-char-items�ڵ㡾%s��"), strMacroID.GetString());
		//��������������Ŀ������Ҫ���ö�Ӧ�Ľڵ�
		return FALSE;
	}
	
	CRptTemp_MacroCharItems* pNewMacroCharItems = GenRpt_Xml_NewMacroCharItems(pRptItems, pMacroCharItems);

	if (pNewMacroCharItems == NULL)
	{
		return FALSE;
	}

	//�ȴ���macro-char-items�µ�report-def�ڵ�
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
			//����ͼ�����⴦��
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

//pRptMacroTestNew����Ҫʵ������macrotest�ڵ�
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
			//�����ı������ݣ�ȡ���һ�α����е�
			CReport *pRpt = (CReport *)pRptLists->GetTail();

			if (! GenRpt_Xml_NewValue(pRptTemp_Reports, (CRptTemp_ValueDef *)pObj, pRpt))
			{
				bRet = FALSE;
			}
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTDEF)
		{
			//ģ���У�Ӧ��ֻ��һ��report-def����Ҫ����pRptLists��������ʵ������Ӧ������report
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
				pNewRpt->m_strName.Format(_T("���㱨��%d"), nCalIndex);
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
		pNewRpt->m_strName.Format(_T("���%d"), nIndex-nCalIndex-1);
		pNewRpt->m_strID.Format(_T("Rpt%2d"), nIndex-nCalIndex);
		pNewRpt->m_nIndex = nIndex-1-nCalIndex;

		if (! GenRpt_Xml_MacroTest_Dat_Report_Value(pRptDef, pNewRpt, pReport, pMacroTest))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

//���Ǵӽ���жϽű��л�ȡ����������β�pMacroTest��������
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
//�����ǵ���XML��ʽ��doc�ṹ�ļ��Ĳ���
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
<group name="����ͷ��Ϣ" id="TestGlobalDatas" data-type="TestGlobalDatas" value="1">
	<group name="���վ��Ϣ" id="SubInformation" data-type="type" value="2">
		<data name="���վ����" id="SubName" data-type="string" value="��������" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="���վ��ַ" id="SubAddr" data-type="string" value="�Ͼ�" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="��·����" id="LoopName" data-type="string" value="1#��·" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="��·��ַ" id="LoopAddr" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="������Ա" id="Tester" data-type="string" value="����Ա1" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	</group>
	<group name="����װ����Ϣ" id="DeviceInfor" data-type="type" value="2">
		<data name="װ������" id="DeviceName" data-type="string" value="��·����װ��" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="���к�" id="DeviceSN" data-type="string" value="SN123456789" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="װ���ͺ�" id="DeviceModel" data-type="string" value="PCS-931" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="���Ƶ����" id="SettingsNO" data-type="string" value="S123456" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="װ�õ�ַ" id="DeviceAddr" data-type="string" value="302" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="������Ϣ" id="AdditionalInf" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="��������" id="DeviceFactory" data-type="string" value="����" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	</group>
	<group name="�ֵ" id="NomSettings" data-type="type" value="0">
		<data name="���ѹ" id="Vnom" data-type="float" value="100" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="�����" id="Inom" data-type="float" value="1" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="�Ƶ��" id="Fnom" data-type="float" value="50" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="�������ʱ��" id="SureTime" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	</group>
	<group name="�����豸��Ϣ" id="TestAppInfor" data-type="type" value="0">
		<data name="�ͺ�" id="AppModel" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="���к�" id="AppSN" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="�������ֵ" id="Imax" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="��ѹ���ֵ" id="Vmax" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="���Կ�ʼʱ��" id="TestStartTime" data-type="string" value="2022-3-19" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
		<data name="������ֹʱ��" id="TestEndTime" data-type="string" value="2022-3-19" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	</group>
</group>
*/
void CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_ProcessReportHead()
{
	if (m_pRptTemp_TestMacroUiRpt == NULL || m_pReportHeadParas == NULL)
	{
		return;
	}

	CRptTemp_ReportTemplate *pNewReportTemplate = GenRpt_Xml_NewReportTemplate(m_pRptTemp_TestMacroUiRpt);
	POS pos = m_pReportHeadParas->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pGrp = (CDataGroup *)m_pReportHeadParas->GetNext(pos);
		CRptTemp_Text* pText = GenRpt_Xml_NewText(pNewReportTemplate);  //һ����𣬶�Ӧһ���ı�
		pText->m_strText = pGrp->m_strName;
		pText->m_nBold = 1;

		GenRpt_Xml_Doc_ProcessReportHead_Grid(pGrp, pNewReportTemplate);  //һ���������ݣ�����һ�����
	}

	GenRpt_Xml_NewText(pNewReportTemplate);  //����ͷ�����󣬲���һ������
}

/*
<group name="�����豸��Ϣ" id="TestAppInfor" data-type="type" value="0">
	<data name="�ͺ�" id="AppModel" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="���к�" id="AppSN" data-type="string" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="�������ֵ" id="Imax" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="��ѹ���ֵ" id="Vmax" data-type="string" value="0.000000" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="���Կ�ʼʱ��" id="TestStartTime" data-type="string" value="2022-3-19" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<data name="������ֹʱ��" id="TestEndTime" data-type="string" value="2022-3-19" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
</group>
1��һ��������ݣ�����һ�����
2�����4�У����ƣ�ֵ�����ƣ�ֵ����������Ϊһ�У�
*/
void CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_ProcessReportHead_Grid(CDataGroup *pGrp, CExBaseList *pParent)
{
	if (pGrp == NULL || pParent == NULL)
	{
		return;
	}

	CRptTemp_Grid* pNewGrid = new CRptTemp_Grid();
	pParent->AddNewChild(pNewGrid);
	pNewGrid->m_strData_Mode = RPT_TEMPLATE_DATAMODE_ROW_RPT;  //��ģʽ
	pNewGrid->m_nShowBorders = 0;

	POS pos = pGrp->GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pGrp->GetNext(pos);
		nIndex++;
		CRptTemp_Row *pRow = NULL;

		if (nIndex%2 == 1) //��������һ�У���������ʾҪ����һ��
		{
			pRow = new CRptTemp_Row;
			pNewGrid->AddNewChild(pRow);
		}
		else
		{
			pRow = (CRptTemp_Row *)pNewGrid->GetTail();  //��������һ�У�ż������ʾ��������һ��
		}

		//cell��row�е�˳�򣬴���Ԫ������һ�е�˳��
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

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_Items(CExBaseList *pParent, CItems *pItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return FALSE;
	}

	if (pItems->IsTypeRootNode())
	{
		return GenRpt_Xml_Items_Doc_RootNode(pParent, pItems);
	}

	return GenRpt_Xml_Items_Doc_Normal(pParent, pItems);
}

//�ݹ���ã�ֻ����˹�������CItems
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_Normal(CExBaseList *pParent, CItems *pItems)
{
	if (pParent == NULL || pItems == NULL)
	{
		return FALSE;
	}

	if (pItems->m_strID == STT_ITEMS_ID_BEFORETEST
		|| pItems->m_strID == STT_ITEMS_ID_AFTERTEST)
	{
		return TRUE;  //����ǰ�����Ժ󡣹��˵�
	}

	//�����˹�������CItems�ڵ㣬ֻ��Ҫ�����ӵ�CItems����
	//��Ϊ�����˹�������CItems�ڵ㣬�Ӷ������CMacroTest��Ҳ��֪����Ҫ�����ı�����������Щ
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

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode(CExBaseList *pParent, CItems *pItems)
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

	//��ඨ��һ��report-template-def�ڵ�
	CRptTemp_ReportTemplateDef *pRptTemp_ReportTemplateDef = oRptDef.GetReportTemplateDef();

	if (pRptTemp_ReportTemplateDef != NULL)
	{
		//��oRptDef���ڵ㶨����report-template-def����˵����
		//1����һ��rootnode����һ���̻��ı��档���Ƕ�̬��
		//2�������Ĳ��֣�������Ե����̬�仯�ģ������к��е�����ͬ���ǹ̶���

		//���ڹ����Ĳ��������е���Ŀ����һ�µģ�ֱ��ȡ��һ����������Ŀ�Ĳ���
		CMacroTest *pMacroTest = pItems->GetFirstMacroTest();
		//��һ����������Ŀ��Ϊ��ʱ������������������
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

//rootnode�£�����ֻ����items��macrotest��char-macro-items
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
				continue;  //����ǰ�����Ժ󡣹��˵�
			}

			CRptTemp_Items *pRptTemp_ItemsChild = GenRpt_Xml_NewItems(pRptItems, pItemsChild);

			if (pRptTemp_ItemsChild == NULL)
			{
				bRet = FALSE;
				continue;
			}

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

//items�µĵ�������Ŀ������pRptDef�ж����macrotest�ı���ģʽ
//����ģʽ = item���������ɱ��
//items��������β�pItems�����е�macrotest��ͳһ���ɱ��
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MacroTest(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroTest *pMacroTest)
{
	CString strMacroID = pMacroTest->GetTestMacroID();
	CExBaseList oListParas;
	GetMacroTest_AllParas(&oListParas, pMacroTest);
	CRptTemp_MacroTest *pMacroTestDef = pRptDef->FindMacroTestByMacroID(strMacroID, &oListParas);

	if (pMacroTestDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У��Ҳ���macrotest�ڵ㡾%s��"), strMacroID.GetString());
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

//����������Ŀ��Ӧ��ֱ�ӻ�ȡpRptDef�����macro-char-items�ڵ㣬�ҵ������report-template-def��
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MacroCharItems(CRptTemp_TestMacroUiRptDef *pRptDef, CRptTemp_Items *pRptItems, CMacroCharItems *pMacroCharItems)
{
	CRptTemp_MacroCharItems *pMacroCharItemsDef = pRptDef->FindMacroCharItemsByMacroID(pMacroCharItems->GetTestMacroID());

	if (pMacroCharItemsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У��Ҳ���macro-char-items�ڵ㡾%s��"), pMacroCharItems->GetTestMacroID().GetString());
		//��������������Ŀ������Ҫ���ö�Ӧ�Ľڵ�
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У�macro-char-items��δ����report-template-def�ڵ㡾%s��"), pMacroCharItemsDef->m_strMacro_Id.GetString());
		return FALSE;
	}

	return GenRpt_Xml_Doc_ReportTemplateDef_MacroTestCharItems(pReportTemplateDef, pNewMacroCharItems, pMacroCharItems);
}

//���¡�����Ҫ�� + ���������ݱ���С��λ�������ݽӿ�
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_UpdateItemsTec(CRptTemp_TestMacroUiRptDef *pRptDef, const CString &strItemPath)
{
	return GenRpt_Xml_Items_Dat_RootNode_UpdateItemsTec(pRptDef, strItemPath);
}

//���浼��ģʽ��
//item����ʾһ����������Ŀ����������һ��word������ڶ���ʱ�䡢����ֵ����
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MacroTest_RptMode_Item(CRptTemp_MacroTest *pMacroTestDef, CRptTemp_Items *pRptItems, CMacroTest *pMacroTest)
{
	if (pRptItems == NULL || pMacroTestDef == NULL)
	{
		return FALSE;
	}

	if (pMacroTestDef->m_strMacro_Id != pMacroTest->GetTestMacroID())
	{
		//���˵����Թ���ID��һ�µĵ�������Ŀ
		return TRUE;
	}

	CRptTemp_ReportTemplateDef *pReportTemplateDef = pMacroTestDef->GetReportTemplateDef();

	if (pReportTemplateDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У�macrotest��δ����report-template-def�ڵ㡾%s��"), pMacroTestDef->m_strMacro_Id.GetString());
		return FALSE;
	}

	return GenRpt_Xml_Doc_ReportTemplateDef_MacroTest(pReportTemplateDef, pRptItems, pMacroTest);
}

//���浼��ģʽ��
//items����ʾ��С��Ҷ��CItems�ڵ㣬�������еĵ�������Ŀ������һ��ͳһ�ı��
//report-template-def�¶����title-def��text-def��Ҳ�������С��Ҷ��CItems�ڵ㡣
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Items_Doc_RootNode_MacroTest_RptMode_Items(CRptTemp_MacroTest *pMacroTestDef, CRptTemp_Items *pRptItems, CItems *pItems)
{
	if (pRptItems == NULL || pMacroTestDef == NULL)
	{
		return FALSE;
	}

	//����itemsģʽ�����еĵ�������Ŀͳһ��һ�����ֻ��Ҫ����һ��
	if (pRptItems->IsHasGen())
	{
		return TRUE;
	}

	CRptTemp_ReportTemplateDef *pReportTemplateDef = pMacroTestDef->GetReportTemplateDef();

	if (pReportTemplateDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У�macrotest��δ����report-template-def�ڵ㡾%s��"), pMacroTestDef->m_strMacro_Id.GetString());
		return FALSE;
	}

	pRptItems->SetHasGen(TRUE);
	return GenRpt_Xml_Doc_ReportTemplateDef_Items(pReportTemplateDef, pRptItems, pItems, pMacroTestDef->m_strMacro_Id);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_ReportTemplateDef_Head(CRptTemp_TestMacroUiRptDef *pRptDef, CExBaseList *pParent_RptTemp, CGbItemBase *pItemBase)
{
	//��ඨ��һ��report-template-def�ڵ�
	CRptTemp_ReportTemplateDef *pRptTemp_ReportTemplateDef = pRptDef->GetReportTemplateDef();

	if (pRptTemp_ReportTemplateDef == NULL)
	{
		//���Բ�����report-template-def�ڵ�
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
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ӧ�ȼ���%d������Ŀ"), pTitleDef->m_nItem_Level);
				bRet = FALSE;
			}

			strTemp.Replace(_T("%s"), strName);
		}
		else if (nIndex == 1)
		{
			CString strName = GetItemName(pRootNode, pTitleDef->m_nItem_Level_2);

			if (strName.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ӧ�ȼ���%d������Ŀ"), pTitleDef->m_nItem_Level_2);
				bRet = FALSE;
			}

			strTemp.Replace(_T("%s"), strName);
		}
		else if (nIndex == 2)
		{
			CString strName = GetItemName(pRootNode, pTitleDef->m_nItem_Level_3);

			if (strName.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ӧ�ȼ���%d������Ŀ"), pTitleDef->m_nItem_Level_3);
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
	strText2.AppendFormat(pItemBase->m_strName); //�̶��������Ŀ���������

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

	return bRet;
}

//��ȡtext����ʵ��������ı����β�2�ǳ��Σ��β�1�����
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TextDef_GetContext(CString &strText, CString &strTextContext, CGbItemBase *pItemBase, CDataGroup *pItemsTec
																, const CString &strData1_Id,  const CString &strData2_Id, const CString &strData3_Id
																, const CString &strData4_Id, const CString &strData5_Id, const CString &strData6_Id)
{
	CGbItemBase *pDestItem = pItemBase;

	if (pDestItem->GetClassID() == GBCLASSID_ITEMS)
	{
		//����Ƿ��࣬��ȡ��һ����������Ŀ
		CItems *pItems = (CItems *)pDestItem;
		pDestItem = pItems->GetFirstMacroTest();

		if (pDestItem == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ŀ��%s���ĵ�������Ŀ"), pItemBase->m_strName.GetString());
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
			//�ȴ����ݽӿڲ��ң��Ҳ����ٴӱ������ݲ���
			CString strValue = GetItemsTec(pItemsTec, strData1_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData1_Id);
			}	

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ŀ��%s���ı������ݡ�%s��"), pDestItem->m_strName.GetString(), strData1_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData1_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//����ҵ��������Ͷ��壬��ֱ�Ӳ�����������ȡֵ�����ơ������ڵ�������Ŀ
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 1)
		{
			//�ȴ����ݽӿڲ��ң��Ҳ����ٴӱ������ݲ���
			CString strValue = GetItemsTec(pItemsTec, strData2_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData2_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ŀ��%s���ı������ݡ�%s��"), pDestItem->m_strName.GetString(), strData2_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData2_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//����ҵ��������Ͷ��壬��ֱ�Ӳ�����������ȡֵ�����ơ������ڵ�������Ŀ
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 2)
		{
			//�ȴ����ݽӿڲ��ң��Ҳ����ٴӱ������ݲ���
			CString strValue = GetItemsTec(pItemsTec, strData3_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData3_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ŀ��%s���ı������ݡ�%s��"), pDestItem->m_strName.GetString(), strData3_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData3_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//����ҵ��������Ͷ��壬��ֱ�Ӳ�����������ȡֵ�����ơ������ڵ�������Ŀ
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 3)
		{
			//�ȴ����ݽӿڲ��ң��Ҳ����ٴӱ������ݲ���
			CString strValue = GetItemsTec(pItemsTec, strData4_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData4_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ŀ��%s���ı������ݡ�%s��"), pDestItem->m_strName.GetString(), strData4_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData4_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//����ҵ��������Ͷ��壬��ֱ�Ӳ�����������ȡֵ�����ơ������ڵ�������Ŀ
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 4)
		{
			//�ȴ����ݽӿڲ��ң��Ҳ����ٴӱ������ݲ���
			CString strValue = GetItemsTec(pItemsTec, strData5_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData5_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ŀ��%s���ı������ݡ�%s��"), pDestItem->m_strName.GetString(), strData5_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData5_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//����ҵ��������Ͷ��壬��ֱ�Ӳ�����������ȡֵ�����ơ������ڵ�������Ŀ
				strValue = pDataTypeValue->m_strName;
			}

			strTemp.Replace(_T("%s"), strValue);
		}
		else if (nIndex == 5)
		{
			//�ȴ����ݽӿڲ��ң��Ҳ����ٴӱ������ݲ���
			CString strValue = GetItemsTec(pItemsTec, strData6_Id);

			if (strValue.IsEmpty())
			{
				strValue = GetItemReportValue(pDestItem, strData6_Id);
			}

			if (strValue.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ���Ŀ��%s���ı������ݡ�%s��"), pDestItem->m_strName.GetString(), strData6_Id.GetString());
				bRet = FALSE;
			}

			CDataTypeValue *pDataTypeValue = GetDataTypeValue(strData6_Id, pDestItem, strValue);

			if (pDataTypeValue != NULL)
			{
				//����ҵ��������Ͷ��壬��ֱ�Ӳ�����������ȡֵ�����ơ������ڵ�������Ŀ
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

//Ŀǰֻ��������дģʽ�����Ӷ���ֻ����head��row��grid������cols-def��rows-def
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_Head(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent, CGbItemBase *pItemBase)
{
	//���Ч�ʣ���Ϊ�գ��Ŵ���ʹ��
	if (pGridDef->GetEnable() != NULL)
	{
		//���ʹ�ܣ�����Items�Ĳ���
		CExBaseList oListParas;
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
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("��⵽�����Ϊ����дģʽ���ݲ�������"));
		return FALSE;
	}

	BOOL bRet = TRUE;
	CRptTemp_Grid *pNewGrid = GenRpt_Xml_NewGrid(pParent, pGridDef); //ͬʱ������head
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	POS pos = pGridDef->GetHeadPosition();
	CRptTemp_TestMacroUiRptDef *pTestMacroUiDef = (CRptTemp_TestMacroUiRptDef *)pGridDef->GetAncestor(MNGRCLASSID_CRPTTEMP_TESTMACROUIRPTDEF);

	//ѭ��ֻ����row
	while (pos != NULL)
	{
		pObj = pGridDef->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_ROW)
		{
			continue;
		}

		CRptTemp_Row *pRow = (CRptTemp_Row *)pObj;
		CRptTemp_Row *pNewRow = (CRptTemp_Row *)pRow->CloneEx(TRUE, TRUE);
		pNewGrid->AddNewChild(pNewRow);

		if (! GenRpt_Xml_Doc_GridDef_Head_FillRow(pNewRow, pItemBase, pTestMacroUiDef))
		{
			bRet = FALSE;
		}
	}

	return bRet;
}

//pItemBaseһ����rootnode�ڵ�
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_Head_FillRow(CRptTemp_Row *pRow, CGbItemBase *pItemBase, CRptTemp_TestMacroUiRptDef *pRptTempUiDef)
{
	ASSERT(pItemBase->GetClassID() == GBCLASSID_ITEMS);

	if (pItemBase->GetClassID() != GBCLASSID_ITEMS)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("����XML���棬��⵽��Ŀ���Ͳ��ԡ���"));
		return FALSE;
	}

	CItems *pItems = (CItems *)pItemBase;
	ASSERT(pItems->IsTypeRootNode());

	if (!pItems->IsTypeRootNode())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("����XML���棬��⵽��Ŀ��rootnode�ڵ㡭��"));
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

	//�̶��ı������ǲ��������ţ�ֱ�ӷ���TRUE��ʵ���ϡ��˴���Ӧ�ó��ֲ���������
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

	//����cell��data-id
	pCell->m_strDataID = pCell->m_strText;
	pCell->m_strText = _T("");

	CReport *pReport = NULL;
	CGbItemBase *pDestItem = pItems;
	CString strItemPath;

	if (pCell->m_strData_Path.IsEmpty())
	{
		//���ڹ����Ĳ��������е���Ŀ����һ�µģ�ֱ��ȡ��һ����������Ŀ�Ĳ���
		CMacroTest *pMacroTest = pItems->GetFirstMacroTest();

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
		//ͨ����Ŀ���·����������Ŀ
		pItems->SelectItems(pCell->m_strData_Path, oDestList);
		long nCount = oDestList.GetCount();

		if (nCount != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("��Ŀ��%s�����ҽ����Ψһ���ҵ���%d����Ŀ����Ŀ"), pCell->m_strData_Path.GetString(), nCount);
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
	//�����дʱ����value-def����һ��
	return GenRpt_Xml_NewValue_ProcessVal(strSrcVal, strVal, strProcess, nPrecision);
}

//�����ĸ���ֻ����macrotest�ڵ㶨���report-template-def����rpt-mode=item
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
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TitleDef_MacroTest(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroTest *pMacroTest)
{
	return GenRpt_Xml_Doc_TitleDef_Head(pTitleDef, pParent_RptTemp, pMacroTest);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TextDef_MacroTest(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroTest *pMacroTest)
{
	//���Ч�ʣ�����enable�ڵ㣬���ж�ʹ��
	if (pTextDef->GetEnable() != NULL)
	{
		CExBaseList oListParas;
		GetMacroTest_AllParas(&oListParas, pMacroTest);

		//����ʹ�ܣ���ֱ������
		if (!pTextDef->IsEnable(&oListParas))
		{
			return TRUE;
		}
	}

	return GenRpt_Xml_Doc_TextDef_Head(pTextDef, pParent_RptTemp, pMacroTest);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_MacroTest(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent_RptTemp, CMacroTest *pMacroTest)
{
	//���Ч�ʣ���Ϊ�գ��Ŵ���ʹ��
	if (pGridDef->GetEnable() != NULL)
	{
		//���ʹ�ܣ�����MacroTest�Ĳ���
		CExBaseList oListParas;
		GetMacroTest_AllParas(&oListParas, pMacroTest);

		if (! pGridDef->IsEnable(&oListParas))
		{
			return TRUE;
		}
	}

	//Ŀǰ��ʱֻ����row-rptģʽ��
	ASSERT(pGridDef->m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_RPT);
	CRptTemp_Grid *pNewGrid = GenRpt_Xml_NewGrid(pParent_RptTemp, pGridDef);
	return GenRpt_Xml_GridDef_RowRpt(pNewGrid, pGridDef, pMacroTest);
}

//�����ĸ���ֻ����macro-char-items�ڵ㶨���report-template-def
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
	//���Ч�ʣ���Ϊ�գ��Ŵ���ʹ��
	if (pGridDef->GetEnable() != NULL)
	{
		//���ʹ�ܣ�����MacroCharItems�Ĳ���
		CExBaseList oListParas;
		GetMacroCharItems_AllParas(&oListParas, pMacroCharItems);

		if (! pGridDef->IsEnable(&oListParas))
		{
			return TRUE;
		}
	}

	//Ŀǰ��ʱֻ����row-itemģʽ��
	ASSERT(pGridDef->m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_ITEM);
	CRptTemp_Grid *pNewGrid = GenRpt_Xml_NewGrid(pParent_RptTemp, pGridDef);
	return GenRpt_Xml_GridDef_RowItem(pNewGrid, pGridDef, pMacroCharItems, pMacroCharItems->GetTestMacroID());
}

//�����ĸ���ֻ����macro�ڵ㶨���report-template-def����rpt-mode=items
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
	}

	return bRet;
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TitleDef_Items(CRptTemp_TitleDef *pTitleDef, CRptTemp_ReportTemplate *pParent_RptTemp, CItems *pItems)
{
	return GenRpt_Xml_Doc_TitleDef_Head(pTitleDef, pParent_RptTemp, pItems);
}

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_TextDef_Items(CRptTemp_TextDef *pTextDef, CRptTemp_ReportTemplate *pParent_RptTemp, CItems *pItems)
{
	return GenRpt_Xml_Doc_TextDef_Head(pTextDef, pParent_RptTemp, pItems);
}

//rpt-mode = row_item
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_Doc_GridDef_Items(CRptTemp_GridDef *pGridDef, CRptTemp_ReportTemplate *pParent_RptTemp, CItems *pItems, const CString &strMacroID)
{
	//Ŀǰ��ʱֻ����row-itemģʽ��
	ASSERT(pGridDef->m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_ITEM);
	CRptTemp_Grid *pNewGrid = GenRpt_Xml_NewGrid(pParent_RptTemp, pGridDef);
	return GenRpt_Xml_GridDef_RowItem(pNewGrid, pGridDef, pItems, strMacroID);
}

//row-itemģʽ�£�pItemBaseΪ��������Ŀ�ĸ��ڵ㣨CItems��CMacroCharItems��
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_GridDef_RowItem(CRptTemp_Grid *pNewGrid, CRptTemp_GridDef *pGridDef, CGbItemBase *pItemBase, const CString &strMacroID)
{
	CRptTemp_ColsDef *pColsDef = (CRptTemp_ColsDef *)pGridDef->FindByClassID(MNGRCLASSID_CRPTTEMP_COLSDEF);
	ASSERT(pColsDef != NULL);

	if (pColsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У�grid-def��δ����cols-def ��%s��"), pItemBase->m_strName.GetString());
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
			//���˵����Թ���ID ��һ�µĵ�������Ŀ
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

//row-rptģʽ�¡�pGridDef���Ƕ��������е�row��
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_GridDef_RowRpt(CRptTemp_Grid *pNewGrid, CRptTemp_GridDef *pGridDef, CMacroTest *pMacroTest)
{
	CRptTemp_ColsDef *pColsDef = (CRptTemp_ColsDef *)pGridDef->FindByClassID(MNGRCLASSID_CRPTTEMP_COLSDEF);
	ASSERT(pColsDef != NULL);

	if (pColsDef == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������������ļ��У�grid-def��δ����cols-def ��%s��"), pMacroTest->m_strName.GetString());
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
		CRptTemp_Row *pNewRow = (CRptTemp_Row *)pRow->CloneEx(TRUE, TRUE);
		pNewRow->m_strItemPath = strItemPath;
		pNewRow->m_pGbItemBase = pMacroTest;

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

//nIndex��1��ʼ
//row-itemģʽ
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
	POS pos = pColsDef->GetHeadPosition();

	while (pos != NULL)
	{
		CRptTemp_ColDef *pColDef = (CRptTemp_ColDef *)pColsDef->GetNext(pos);

		CRptTemp_Cell *pNewCell = new CRptTemp_Cell;
		pNewRow->AddNewChild(pNewCell);

		if (pColDef->m_strType == RPT_TEMPLATE_COL_DEF_TYPE_TEST_INDEX)
		{
			pNewCell->m_strText.Format(_T("%d"), nIndex); //���
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��Ρ�%d���ı���Ϊ��"), nTestIndex + 1);
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
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��Ρ�%d����grid-def�У�rowȱ�ٵڡ�%d���е�cell����"), nTestIndex + 1, nColIndex + 1);
			pCell = new CRptTemp_Cell();
			pNewRow->AddNewChild(pCell);
			bRet = FALSE;
		}

		if (pColDef->m_strType == RPT_TEMPLATE_COL_DEF_TYPE_TEST_INDEX)
		{
			//ʵ���ϣ������Ԥ���
			pCell->m_strText.Format(_T("%d"), nTestIndex+1); //���
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
	//�����дʱ����value-def����һ��
	return GenRpt_Xml_NewValue_ProcessVal(strSrcVal, strVal, strProcess, nPrecision);
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
		pNewValue->m_strVal = _T("δ�ҵ����ֵ");
		return FALSE;
	}

	if (pValueDef->m_strID != g_strTestResultDescriptKey)
	{
		CDataTypeValue *pDataTypeValue = GetDataTypeValue(pValueDef->m_strID, pItemBase, strRptValue);

		if (pDataTypeValue != NULL)
		{
			//����ҵ��������Ͷ��壬��ֱ�Ӳ�����������ȡֵ�����ƣ����ٴ�����Լ�������ڵ�������Ŀ
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
		pNewValue->m_strVal = _T("δ�ҵ����ֵ");
		return FALSE;
	}

	if (pValueDef->m_strID != g_strTestResultDescriptKey)
	{
		CDataTypeValue *pDataTypeValue = GetDataTypeValue(pValueDef->m_strID, pItemBase, strRptValue);

		if (pDataTypeValue != NULL)
		{
			//����ҵ��������Ͷ��壬��ֱ�Ӳ�����������ȡֵ�����ƣ����ٴ�����Լ�������ڵ�������Ŀ
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

	if (strSrcVal == _T("--") || strSrcVal == _T("δ����"))
	{
		return TRUE;
	}

	if (strProcess.IsEmpty() && nPrecision < 0)
	{
		//������Ҳ����Լ�����磺�������
		GenRpt_Xml_NewValue_ProcessVal_AdjustVal(strVal);
		return TRUE;
	}

	//Ŀǰ���ڱ������ݴ���ģ�ֻ�漰������ϵ����s��ms��Ҫ����1000��
	//��������Լ�ͱ������ϵ��ʱ���ȴ������ϵ��
	//���������������ı������ݴ�������Ҫ����strProcess���������⴦���Դ�ȷ���ȴ���strProcess�����ȴ�����Լ��
	if (! strProcess.IsEmpty())
	{
		CBkmkDataProcess *pProcess = FindDataProcessByID(strProcess);

		if (pProcess == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("δ�ҵ��������ݴ���Ķ��塾%s��"), strProcess.GetString());
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

//���������ݣ�m_pValues��m_pRptDvmDataset
BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessRptValue(CString &strRptValue, const CString &strDataID, CReport *pReport)
{
	if (pReport == NULL)
	{
		return FALSE;
	}

	//�����˴��������ݣ���������pReport->m_pRptDvmDataset;
	CValue *pFind = (CValue*)pReport->m_pValues->FindByID(strDataID);
	CDvmData *pRptData = (CDvmData *)pReport->m_pRptDvmDataset->FindByID(strDataID);

	if (pFind == NULL && pRptData == NULL)
	{
		if (m_bCurrentItems_Ain)
		{
			//ң�����ݷ���ӳ��
			CDataGroup *pAinDataMapCfg = m_pGuideBook->GetAinDataMapCfg();
			CDataGroup *pAinRatios = m_pGuideBook->GetAinRatios();

			if (pAinDataMapCfg == NULL)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("δ�ҵ�ң������ӳ�䣬����ʧ�ܣ�"));
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
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������Ҳ������������%s��"), strDataID);
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

				GenRpt_Xml_ProcessVal_AinRatios(pMap, pAinRatios, strRptValue);//����ң�����ݣ����ݱ�Ȼ���
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ң�����ӳ���У��Ҳ���ӳ�����ݡ�%s��"), strDataID);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������Ҳ������������%s��"), strDataID);
				return FALSE;
			}
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�������Ҳ������������%s��"), strDataID);
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

BOOL CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessRptValue_GetValue(CString &strRptValue, const CString &strDataID, CReport *pReport, CGbItemBase *pGbItem, const CString& strProcess, long nPrecision)
{
	BOOL bRet = TRUE;

	if (pReport == NULL)
	{
		return FALSE;
	}

	if (! GenRpt_Xml_ProcessRptValue(strRptValue, strDataID, pReport))
	{
		//strRptValue = _T("δ�ҵ��������ֵ");
		return FALSE;
	}

	CDataTypeValue *pDataTypeValue = NULL;

	if (strDataID != g_strTestResultDescriptKey)
	{
		pDataTypeValue = GetDataTypeValue(strDataID, pGbItem, strRptValue);

		if (pDataTypeValue != NULL)
		{
			//����ҵ��������Ͷ��壬��ֱ�Ӳ�����������ȡֵ�����ƣ����ٴ�����Լ�������ڵ�������Ŀ
			strRptValue = pDataTypeValue->m_strName;
		}
	}

	if (pDataTypeValue == NULL)
	{
		CString strDestValue;
		//ûȡ���������ͣ���ʾ��Ҫ������Լ
		if (! GenRpt_Xml_GridDef_FillRow_ProcessVal(strRptValue, strDestValue, strProcess, nPrecision))
		{
			bRet = FALSE;
		}

		strRptValue = strDestValue;
	}

	return bRet;
}

//����ң�����ݣ����ݲ���ֵ��ȣ����л���
/*
<group id="AinRatios" name="���������Ϣ">
	<data name="װ�ò���" id="DevMeas" value="1" data-type=""/>��װ�ò�����һ��ֵ�����Ƕ���ֵ��ȡֵ��1|2��
	<data name="PTһ�β�" id="PtPrimary" value="220" data-type=""/>��PTһ�β൥λΪkV��
	<data name="Pt���β�" id="PtSecondary" value="100" data-type=""/>��PT���β൥λΪV��
	<data name="Ctһ�β�" id="CtPrimary" value="" data-type=""/>
	<data name="Ct���β�" id="CtSecondary" value="" data-type=""/>��CTһ�Ρ����β൥λ��ΪA��
</group>
*/
//�β�strRptValue������ʱ���Ѿ��Ǵӱ����в��ҵ��ı�������ֵ���˴�������������¸�ֵ��strRptValue����
void CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessVal_AinRatios(CDvmData *pAinDataMap, CDataGroup *pAinRatios, CString &strRptValue)
{
	if (pAinRatios == NULL || pAinRatios == NULL)
	{
		return;
	}

	CDvmData *pDevMeas = (CDvmData *)pAinRatios->FindByID(ID_PARA_DevMeas);

	if (pDevMeas == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���װ�ò���������һ��ֵ���Ƕ���ֵ�����á���"));
		return;
	}

	if (pDevMeas->m_strValue == "2")
	{
		//����ֵ�����ø��ݱ�Ȼ���
		return;
	}

	//ң�����ӳ��ʱ�����ǹ̶�IDӳ��
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
		//ʣ��Ĺ������غ�Ƶ�ʣ����û���
		return;
	}
}

void CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessVal_AinRatios_I(CDataGroup *pAinRatios, CString &strRptValue)
{
	CDvmData *pCtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���CT���һ��ֵ����"));
		return;
	}

	CDvmData *pCtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���CT��ȶ���ֵ����"));
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
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���PT���һ��ֵ����"));
		return;
	}

	CDvmData *pPtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���PT��ȶ���ֵ����"));
		return;
	}

	double dPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dSecondary = CString_To_double(pPtSecondary->m_strValue);
	double dRatio = dPrimary * 1000 / dSecondary;  //PT����� kV / V��

	//װ�ò���һ��ֵʱ����ѹ��λΪkV
	double dRptVal = CString_To_double(strRptValue);
	dRptVal = dRptVal * 1000 / dRatio;
	strRptValue.Format(_T("%.6f"), dRptVal);
}

void CRptTemplate_GenXmlTool::GenRpt_Xml_ProcessVal_AinRatios_PQ(CDataGroup *pAinRatios, CString &strRptValue)
{
	CDvmData *pCtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���CT���һ��ֵ����"));
		return;
	}

	CDvmData *pCtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���CT��ȶ���ֵ����"));
		return;
	}

	CDvmData *pPtPrimary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���PT���һ��ֵ����"));
		return;
	}

	CDvmData *pPtSecondary = (CDvmData *)pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ģ��ȫ�������У��Ҳ���PT��ȶ���ֵ����"));
		return;
	}

	double dCtPrimary = CString_To_double(pCtPrimary->m_strValue);
	double dCtSecondary = CString_To_double(pCtSecondary->m_strValue);
	double dPtPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dPtSecondary = CString_To_double(pPtSecondary->m_strValue);
	//PT����� kV / V��
	double dRatio = (dCtPrimary / dCtSecondary) * (dPtPrimary * 1000 / dPtSecondary);  

	//װ�ò���һ��ֵʱ����ѹ��λΪkV�����ʵĵ�λ��MW��MVAr
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

	//����head
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

//������Ŀ�ȼ���������Եȼ��ĸ���Ŀ��CItems�ڵ㡣����������
CString CRptTemplate_GenXmlTool::GetItemName(CGbItemBase *pItemBase, long nItemLevel)
{
	//���������Ŀʱ��һ���ǻ���rootnode��CItems���ҵ�
	ASSERT(pItemBase->GetClassID() == GBCLASSID_ITEMS);

	if (pItemBase->GetClassID() != GBCLASSID_ITEMS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������Ŀ���Ƴ�����׼��Ŀ����CItems��%s��"), pItemBase->m_strName.GetString());
		return _T("");
	}

	CItems *pItems = (CItems *)pItemBase;
	ASSERT(pItems->IsTypeRootNode());

	if (! pItems->IsTypeRootNode())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������Ŀ���Ƴ�����׼��Ŀ����rootnode��%s��"), pItemBase->m_strName.GetString());
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

//���ݲ���ID����ȡ��Ŀ�ı���ֵ
CString CRptTemplate_GenXmlTool::GetItemReportValue(CGbItemBase *pItemBase, const CString &strDataID)
{
	UINT nClassID = pItemBase->GetClassID();

	//ֻ���ǵ�������Ŀ���迹������Ŀ
	//2023-11-6  ������CItems����������Ŀ�������ǴӸ��ڵ�ȡ
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

//�����ݽӿ��У����Ҷ�Ӧ�Ľӿ�����ֵ
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
		//˵��������������Դ�����Ӧ��������ֻȡ���һ��
		pRptLists->AddTail(pRpts->GetTail());
		return;
	}

	UINT nClassID = pItemBase->GetClassID();

	if (nClassID == GBCLASSID_MACROTEST)
	{
		//���ڵ�������Ŀ���˴���Ҫ�����������Ŀ������ظ�����
		CMacroTest *pMacroTest = (CMacroTest *)pItemBase;
		long nMacroTestRepeatTimes = pMacroTest->m_nRepeatTimes;

		if (nMacroTestRepeatTimes > 1)
		{
			nTestCount += nTestCount/nMacroTestRepeatTimes;  //���ڵ������Լ��ظ����ԵĲ��֣�Ӧ�����ϼ���ı�������
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
	strPngFile += _T("Img.png");  //����ͼ���Թ̶���������ʽ�����ڹ̶���·��
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

	//�ȴ���������
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

	//�����������Ŀ���ϲ���
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
			pFind->m_strValue = p->m_strExpression;  //�Ե�������Ŀ�Ĺ��ϲ���Ϊ׼
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

	//�ȴ���������
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

	//������������ϲ���
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
			pFind->m_strValue = p->m_strExpression;  //�Ե�������Ŀ�Ĺ��ϲ���Ϊ׼
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
		//�����ڵ�������Ŀ
		return NULL;
	}

	if (strIDPath == _T("RsltDsc"))
	{
		//�������������
		return NULL;
	}

	CString strMacroID;
	CMacroTest *pMacroTest = (CMacroTest *)pItemBase;
	strMacroID = pMacroTest->GetTestMacroID();

	return m_pGuideBook->GetDataTypeValue(strMacroID, strIDPath, strValue);
}