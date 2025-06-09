#include "StdAfx.h"
#include "GuideBookStruDscTool.h"
#include "JobGuide.h"
#include "../../../Module/API/FileApi.h"
#include "../../../SttStudio/Module/SttCmd/GuideBook/SttContents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGuideBookStruDscTool::CGuideBookStruDscTool(void)
{
	//2021-8-5  lijunqing  只要使用这个工具，就是出于导出结构的状态
	g_bGbSaveGbStruDscFile = TRUE;
	m_bExportDsvScript = TRUE;
	m_bExportMacroUIParas = FALSE;
	m_bExportRsltExpr = FALSE;
	m_nExportRpt = EXPROT_RPT_NONE;
	m_bExportGlobalDatas = FALSE;
	m_bExportSysParas = FALSE;
	m_bExportCharacteristic = FALSE;
	m_bExportCmd = FALSE;
	m_bExportItemDatas = FALSE;
	m_bExportItemsTecs = FALSE;
}

CGuideBookStruDscTool::~CGuideBookStruDscTool(void)
{
	//2021-8-5  lijunqing  只要使用这个工具，就是出于导出结构的状态
	g_bGbSaveGbStruDscFile = FALSE;

}

//2021-8-5  lijunqing
void CGuideBookStruDscTool::ExportGuideBookStruDscToString(CGuideBook *pGuideBook, CString &strXml)
{
	m_pGuideBook = pGuideBook;
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	CXmlRWElementBase *pElement = pRWDoc->GetDocElement();

	ExportGuideBookStruDsc(pGuideBook, *pRWDoc, *pElement);

	pRWDoc->GetXml(strXml);
	delete pRWDoc;
}

void CGuideBookStruDscTool::ExportGuideBookStruDscToString_UTF8(CGuideBook *pGuideBook, char **ppszBuffer, long &nLen)
{
	m_pGuideBook = pGuideBook;
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	CXmlRWElementBase *pElement = pRWDoc->GetDocElement();

	ExportGuideBookStruDsc(pGuideBook, *pRWDoc, *pElement);

	nLen = pRWDoc->GetXml(ppszBuffer, 0);
	delete pRWDoc;
}

void CGuideBookStruDscTool::ExportGuideBookStruDsc(CGuideBook *pGuideBook, const CString &strXmlFile)
{
	m_pGuideBook = pGuideBook;
	CString strFile;
	strFile = ChangeFilePostfix(strXmlFile, g_strGbStruDscFileFilter);

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	CXmlRWElementBase *pElement = pRWDoc->GetDocElement();

	ExportGuideBookStruDsc(pGuideBook, *pRWDoc, *pElement);
	pRWDoc->SaveXml(strFile);

	delete pRWDoc;
}

void CGuideBookStruDscTool::ExportGuideBookStruDsc(CGuideBook *pGuideBook, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	m_pGuideBook = pGuideBook;
	CXmlRWElementBase *pXmlGuideBook = NULL;
	pGuideBook->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlGuideBook);

	UINT nClassID = 0;
	POS pos = pGuideBook->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pGuideBook->GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_DEVICE:
			ExportStruDsc((CDevice*)p, oXMLDoc, *pXmlGuideBook);
			break;

		case GBCLASSID_JOBGUIDE:
			ExportStruDsc((CJobGuide*)p, oXMLDoc, *pXmlGuideBook);
			break;

		case DVMCLASSID_CDVMDATASET:
			ExportStruDsc((CDvmDataset*)p, oXMLDoc, *pXmlGuideBook);
			break;
		case DTMCLASSID_CDATAGROUP:
			ExportStruDsc((CDataGroup*)p, oXMLDoc, *pXmlGuideBook);
			break;
		case GBCLASSID_TESTGLOBALDATASMNGR:
			ExportStruDsc((CTestGlobalDatasMngr*)p, oXMLDoc, *pXmlGuideBook);
			break;
		default:
			break;
		}
	}
}

void CGuideBookStruDscTool::ExportStruDscItemsChild(CExBaseList *pList, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	UINT nClassID = 0;
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (ExportStruDscItemsChild(p, nClassID, oXMLDoc, oParent))
		{
			continue;
		}
	}
}

BOOL CGuideBookStruDscTool::ExportStruDscItemsChild(CExBaseObject *p, UINT nClassID, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	BOOL bRet = TRUE;

	switch (nClassID)
	{
	case GBCLASSID_MACROTEST:
		ExportStruDsc((CMacroTest*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_COMMCMD:
		ExportStruDsc((CCommCmd*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_SAFETY:
		ExportStruDsc((CSafety*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_SYSPARAEDIT:
		ExportStruDsc((CSysParaEdit*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_MACROCHARITEMS:
		ExportStruDsc((CMacroCharItems*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_ITEMS:
		ExportStruDsc((CItems*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_TESTMACROUIPARAS:
		ExportStruDsc((CTestMacroUiParas*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_TESTMACROCHARPARAS:
		ExportStruDsc((CTestMacroCharParas*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_ITEMRSLTEXPRRUN:
		ExportStruDsc((CItemRsltExprRun*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_REPORTS:
		ExportStruDsc((CReports*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_MACROPARA:
		ExportStruDsc((CMacroTestPara*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_DEVICE_SYSPARAS:
		ExportStruDsc((CSysParas*)p, oXMLDoc, oParent);
		break;

	case CHARCLASSID_CCHARACTERISTIC:
		ExportStruDsc((CCharacteristic*)p, oXMLDoc, oParent);
		break;

	case DVMCLASSID_CDSVSCRIPT:
		{
			if (m_pGuideBook->m_nGbDevSaveStruDescDsv != 0)
 			{
 				p->XmlWrite(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys);
 			}
		}
		break;

	case GBCLASSID_CMD:
		{
			if (m_bExportCmd)
			{
				p->XmlWrite(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys);
			}
		}
		break;

	default:
		bRet = FALSE;
		break;
	}
	
	return bRet;
}

void CGuideBookStruDscTool::ExportStruDsc(CDevice *pDevice, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlDevice = NULL;
	pDevice->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlDevice);

	ExportStruDscItemsChild(pDevice, oXMLDoc, *pXmlDevice);

// 	UINT nClassID = 0;
// 	POS pos = pDevice->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pDevice->GetNext(pos);
// 		nClassID = p->GetClassID();
// 
// 		if (ExportStruDscItemsChild(p, nClassID, oXMLDoc, *pXmlDevice))
// 		{
// 			continue;
// 		}
// 	}
}

void CGuideBookStruDscTool::ExportStruDsc(CTestGlobalDatasMngr *pDataMngr, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	//CXmlRWElementBase *pXmlDataMngr = NULL;
	//pDataMngr->XmlWrite(oXMLDoc, *pXmlDataMngr, CGbXMLKeys::g_pGbXMLKeys);
	pDataMngr->XmlWrite(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys);
}

void CGuideBookStruDscTool::ExportStruDsc(CJobGuide *pJobGuide, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlJobGuide = NULL;
	pJobGuide->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlJobGuide);

	ExportStruDscItemsChild(pJobGuide, oXMLDoc, *pXmlJobGuide);

// 	UINT nClassID = 0;
// 	POS pos = pJobGuide->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pJobGuide->GetNext(pos);
// 		nClassID = p->GetClassID();
// 
// 		if (ExportStruDscItemsChild(p, nClassID, oXMLDoc, *pXmlJobGuide))
// 		{
// 			continue;
// 		}
// 	}
}

//用于导出全局数据
void CGuideBookStruDscTool::ExportStruDsc(CDvmDataset*pDataset, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	if ( !m_bExportGlobalDatas)
	{
		return;
	}

	if (pDataset->m_strID != g_strGbGlobalDatasID)
	{
		return;
	}

	CXmlRWElementBase *pXmlDataset = NULL;
	pDataset->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlDataset);

	POS pos = pDataset->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pDataset->GetNext(pos);
		pObj->XmlWrite(oXMLDoc, *pXmlDataset, CGbXMLKeys::g_pGbXMLKeys);
	}
}

//用于导出技术要求 + 报告数据小数位数配置
void CGuideBookStruDscTool::ExportStruDsc(CDataGroup *pGrp, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	if ( !m_bExportItemsTecs)
	{
		return;
	}

	if (pGrp->m_strID == ID_ITEMS_TEC || pGrp->m_strID == ID_AIN_DATA_MAP_CFG)
	{
		CXmlRWElementBase *pXmlDataGroup = NULL;
		pGrp->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlDataGroup);

		POS pos = pGrp->GetHeadPosition();
		CExBaseObject *pObj = NULL;

		while (pos != NULL)
		{
			pObj = pGrp->GetNext(pos);
			pObj->XmlWrite(oXMLDoc, *pXmlDataGroup, CGbXMLKeys::g_pGbXMLKeys);
		}
	}
}

//用于导出系统参数
void CGuideBookStruDscTool::ExportStruDsc(CSysParas *pSysParas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	if ( !m_bExportSysParas)
	{
		return;
	}

	CXmlRWElementBase *pXmlSysParas = NULL;
	pSysParas->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlSysParas);

	POS pos = pSysParas->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pSysParas->GetNext(pos);
		pObj->XmlWrite(oXMLDoc, *pXmlSysParas, CGbXMLKeys::g_pGbXMLKeys);
	}
}

void CGuideBookStruDscTool::ExportStruDsc(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItems = NULL;
	pItems->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItems);

	ExportStruDscItemsChild(pItems, oXMLDoc, *pXmlItems);

// 	UINT nClassID = 0;
// 	POS pos = pItems->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pItems->GetNext(pos);
// 		nClassID = p->GetClassID();
// 
// 		if (ExportStruDscItemsChild(p, nClassID, oXMLDoc, *pXmlItems))
// 		{
// 			continue;
// 		}
// 	}
}


void CGuideBookStruDscTool::ExportStruDsc(CSysParaEdit *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItem = NULL;
	pItem->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);
	ProcessReportsBack_BF_Export(pItem);

	ExportStruDscItemsChild(pItem, oXMLDoc, *pXmlItem);

// 	UINT nClassID = 0;
// 	POS pos = pItem->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pItem->GetNext(pos);
// 		nClassID = p->GetClassID();
// 
// 		if (nClassID == GBCLASSID_REPORTS)
// 		{
// 			ExportStruDsc((CReports*)p, oXMLDoc, *pXmlItem);
// 		}
// 	}
}

void CGuideBookStruDscTool::ExportStruDsc(CSafety *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItem = NULL;
	pItem->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);
	ProcessReportsBack_BF_Export(pItem);

	ExportStruDscItemsChild(pItem, oXMLDoc, *pXmlItem);

	if (! m_bExportItemDatas)
	{
		return;
	}

 	UINT nClassID = 0;
 	POS pos = pItem->GetHeadPosition();
 	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pItem->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CSHORTDATAS)
		{
			CShortDatas *pDatas = (CShortDatas *)p;
			ExportStruDsc(pDatas, oXMLDoc, *pXmlItem);
		}
		else if (nClassID == GBCLASSID_MSG)
		{
			CMsg *pMsg = (CMsg *)p;
			CXmlRWElementBase *pXmlItemMsg = NULL;
			pMsg->XmlWriteEx(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys, pXmlItemMsg);
		}
	}
}

void CGuideBookStruDscTool::ExportStruDsc(CMacroTest *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItem = NULL;
	pItem->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);
	ProcessReportsBack_BF_Export(pItem);

	ExportStruDscItemsChild(pItem, oXMLDoc, *pXmlItem);

// 	UINT nClassID = 0;
// 	POS pos = pItem->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pItem->GetNext(pos);
// 		nClassID = p->GetClassID();
// 
// 		if (nClassID == GBCLASSID_COMMCMD)
// 		{
// 			ExportStruDsc((CCommCmd*)p, oXMLDoc, *pXmlItem);
// 			continue;
// 		}
// 
// 		if (nClassID == GBCLASSID_SAFETY)
// 		{
// 			ExportStruDsc((CSafety*)p, oXMLDoc, *pXmlItem);
// 			continue;
// 		}
// 
// 		if (nClassID == GBCLASSID_TESTMACROUIPARAS)
// 		{
// 			ExportStruDsc((CTestMacroUiParas*)p, oXMLDoc, *pXmlItem);
// 			continue;
// 		}
// 
// 		if (nClassID == GBCLASSID_MACROPARA)
// 		{
// 			ExportStruDsc((CMacroTestPara*)p, oXMLDoc, *pXmlItem);
// 		}
// 
// 		if (nClassID == GBCLASSID_ITEMRSLTEXPRRUN)
// 		{
// 			ExportStruDsc((CItemRsltExprRun*)p, oXMLDoc, *pXmlItem);
// 		}
// 
// 		if (nClassID == GBCLASSID_REPORTS)
// 		{
// 			ExportStruDsc((CReports*)p, oXMLDoc, *pXmlItem);
// 		}
// 	}
}

void CGuideBookStruDscTool::ExportStruDsc(CCommCmd *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItem = NULL;
	pItem->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);
	ProcessReportsBack_BF_Export(pItem);

	ExportStruDscItemsChild(pItem, oXMLDoc, *pXmlItem);

// 	UINT nClassID = 0;
// 	POS pos = pItem->GetHeadPosition();
// 	CExBaseObject *pObj = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pObj = pItem->GetNext(pos);
// 		nClassID = pObj->GetClassID();
// 
// 		if (nClassID == DVMCLASSID_CDSVSCRIPT)
// 		{
// 			if (m_pGuideBook->m_nGbDevSaveStruDescDsv != 0)
// 			{
// 				pObj->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
// 			}
// 
// 			continue;
// 		}
// 	}
}

void CGuideBookStruDscTool::ExportStruDsc(CMacroCharItems *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItem = NULL;
	pItem->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);

	UINT nClassID = 0;
	POS pos = pItem->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pItem->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_MACROTEST)
		{
			ExportStruDsc((CMacroTest*)p, oXMLDoc, *pXmlItem);
			continue;
		}

		if (nClassID == CHARCLASSID_CCHARACTERISTIC)
		{
			ExportStruDsc((CCharacteristic*)p, oXMLDoc, *pXmlItem);
			continue;
		}
	}
}

void CGuideBookStruDscTool::ExportStruDsc(CTestMacroUiParas *pUIParas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	if (!m_bExportMacroUIParas)
	{
		return;
	}

	CXmlRWElementBase *pXmlItem = NULL;
	pUIParas->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);
}

void CGuideBookStruDscTool::ExportStruDsc(CTestMacroCharParas *pCharParas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	if (!m_bExportCharacteristic)
	{
		return;
	}

	CXmlRWElementBase *pXmlItem = NULL;
	pCharParas->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);
}

void CGuideBookStruDscTool::ExportStruDsc(CMacroTestPara *pMacroTestPara, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItem = NULL;
	pMacroTestPara->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);
}

void CGuideBookStruDscTool::ExportStruDsc(CItemRsltExprRun *pRsltExprRun, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	if ( !m_bExportRsltExpr )
	{
		return;
	}

	CXmlRWElementBase *pXmlItem = NULL;
	pRsltExprRun->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);

	UINT nClassID = 0;
	POS pos = pRsltExprRun->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pRsltExprRun->GetNext(pos);
		pObj->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
	}
}

void CGuideBookStruDscTool::ExportStruDsc(CReports *pReports, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	if ( ! m_nExportRpt )
	{
		return;
	}

	CXmlRWElementBase *pXmlItem = NULL;
	pReports->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);

	POS pos = pReports->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pReports->GetNext(pos);

		if (m_nExportRpt == EXPROT_RPT_INIT)
		{
			if (pObj->m_strID != _T("_Init_")/*STT_REPORT_ID_INIT*/)
			{
				continue;
			}
		}

		pObj->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
	}
}

void CGuideBookStruDscTool::ExportStruDsc(CCharacteristic *pCharacteristic, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	if ( !m_bExportCharacteristic)
	{
		return;
	}
	
	CXmlRWElementBase *pXmlItem = NULL;
	pCharacteristic->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);

// 	CSttContents *pContents = new CSttContents();
// 	pContents->m_strID = _T("characteristic");//STT_CMD_PARA_Characteristic;
// 	pCharacteristic->GetXml(CCharacteristicXmlRWKeys::g_pXmlKeys, pContents->m_strText);
// 	pContents->XmlWriteEx(oXMLDoc, oParent, CSttCmdDefineXmlRWKeys::g_pXmlKeys, pXmlItem);
}

void CGuideBookStruDscTool::ExportStruDsc(CShortDatas *pDatas, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItem = NULL;
	pDatas->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItem);

	POS pos = pDatas->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		pObj->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
	}
}

//处理备份的报告，将备份的报告放到m_pReports指针，统一导出
void CGuideBookStruDscTool::ProcessReportsBack_BF_Export(CGbItemBase *pGbItemBase)
{
	if (m_nExportRpt != EXPROT_RPT_ALL)
	{
		return;
	}

	CReports *pReportBack = pGbItemBase->GetReportsBack();

	if (pReportBack != NULL)
	{
		//说明项目重复测试
		CReports *pReports = pGbItemBase->GetReports();
		CReports oReport;
		oReport.Append(pReports);
		pReports->RemoveAll();

		//把备份的报告，放到前面
		pReports->Append(pReportBack);
		pReportBack->RemoveAll();

		pReports->Append(&oReport);
		oReport.RemoveAll();
	}
}