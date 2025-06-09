#include "StdAfx.h"
#include "GuideBookExportTool.h"
#include "../../../Module/DataMngr/ValuesParse.h"
#include "JobGuide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGuideBookExportTool::CGuideBookExportTool(void)
{
	CGuideBookExportConfig::Create();
// 	//guidebook
// 	m_nExportGlobalDatas = 1; //全局数据
// 	m_nExportJobGuide = 1; //作业指导
// 	m_nExportExtendRptDef = 0;  //扩展报告
// 
// 	//device
// 	m_nExportDeviceModule = 1; //设备模型
// 	m_nExportSysParas = 1;  //系统参数
// 
// 	//Item
// 	m_nExportRptMap = 1; //报告映射
// 	m_nExportReports = 1; //报告数据
// 
// 	//sysparaedit
// 	m_nExportSysParaEditValues = 0; //系统参数编辑项目的参数
// 
// 	//safety
// 	m_nExportSafetyDatas = 0; //数据定义
// 	m_nExportSafetyDllCall = 0;   //动态库调用
// 	m_nExportSafetyMsg = 0; //提示信息
// 
// 	//commoncmd
// 	m_nExportCmdPara = 0;  //命令参数
// 	m_nExportCmdDatas = 0; //命令定义的数据
// 	m_nExportCmdDsvScript = 0; //模型验证脚本
// 
// 	//macrotest
// 	m_nExportMacroTestParas = 0;  //电气量功能参数
}

CGuideBookExportTool::~CGuideBookExportTool(void)
{
	CGuideBookExportConfig::Release();
}

void CGuideBookExportTool::ExportGuideBook(CGuideBook *pGuideBook, const CString &strXmlFile)
{
	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	CXmlRWElementBase *pElement = pRWDoc->GetDocElement();

	ExportGuideBook(pGuideBook, *pRWDoc, *pElement);
	pRWDoc->SaveXml(strXmlFile);

	delete pRWDoc;
}

void CGuideBookExportTool::ExportGuideBook(CGuideBook *pGuideBook, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlGuideBook = NULL;
	pGuideBook->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlGuideBook);

	UINT nClassID = 0;
	POS pos = pGuideBook->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pGuideBook->GetNext(pos);
		nClassID = p->GetClassID();

		if (ExportItemChild(p, nClassID, oXMLDoc, *pXmlGuideBook))
		{
			continue;
		}

		switch (nClassID)
		{
		case GBCLASSID_DEVICE:
			Export((CDevice*)p, oXMLDoc, *pXmlGuideBook);
			break;

		case GBCLASSID_JOBGUIDE:
			if(CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportJobGuide)
			{
				Export((CJobGuide*)p, oXMLDoc, *pXmlGuideBook);
			}
			
			break;

		case DVMCLASSID_CDVMDATASET:
			if (p->m_strID == g_strGbGlobalDatasID)
			{
				if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportGlobalDatas)
				{
					p->XmlWrite(oXMLDoc, *pXmlGuideBook, CGbXMLKeys::g_pGbXMLKeys);
				}
			}
			else if (p->m_strID == DSID_EXTEND_RPT_TEMPLATE_DEF)
			{
				if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportExtendRptDef)
				{//m_pExtendRptTemplateDef
					p->XmlWrite(oXMLDoc, *pXmlGuideBook, CGbXMLKeys::g_pGbXMLKeys);
				}
			}
			break;

		default:
			break;
		}
	}
}

void CGuideBookExportTool::ExportTest(CGuideBook *pGuideBook)
{
	CDvmDataset oDataset;
	oDataset.m_strName = _T("ExportGuideBookTest");
	oDataset.m_strID = oDataset.m_strName;


	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	CXmlRWElementBase *pElement = pRWDoc->GetDocElement();

	CXmlRWElementBase *pXmlDataset = NULL;
	oDataset.XmlWriteEx(*pRWDoc, *pElement, CGbXMLKeys::g_pGbXMLKeys, pXmlDataset);
	ExportGuideBook(pGuideBook, *pRWDoc, *pXmlDataset);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("ExportGuideBookTest.xml");
	pRWDoc->SaveXml(strFile);

	delete pRWDoc;
}

void CGuideBookExportTool::ExportItems(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItems = NULL;
	pItems->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItems);

	UINT nClassID = 0;
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pItems->GetNext(pos);
		nClassID = p->GetClassID();

		if (ExportItemChild(p, nClassID, oXMLDoc, *pXmlItems))
		{
			continue;
		}

		if (ExportItemsChild(p, nClassID, oXMLDoc, *pXmlItems))
		{
			continue;
		}
	}
}

BOOL CGuideBookExportTool::ExportItemChild(CExBaseObject *p, UINT nClassID, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	if (nClassID == RPTCLASSID_RPTREPORTMAP)
	{
		CReportMap *pRptMap = (CReportMap *)p;

		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportRptMap)
		{
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportRptmapNotSaveNull)
			{
				if(pRptMap->GetCount() == 0)
				{
					return TRUE;
				}
			}

			pRptMap->XmlWrite(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys);
		}

		return TRUE;
	}

	if (nClassID == GBCLASSID_REPORTS)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportReports)
		{
			p->XmlWrite(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys);
		}

		return TRUE;
	}

	if (nClassID == GBCLASSID_SCRIPTTEXT_INIT)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportScriptInit)
		{
			p->XmlWrite(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys);
		}
		
		return TRUE;
	}

	if (nClassID == GBCLASSID_SCRIPTTEXT_NAME)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportScriptName)
		{
			p->XmlWrite(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys);
		}

		return TRUE;
	}

	if (nClassID == GBCLASSID_SCRIPTTEXT_RESULT)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportScriptRslt)
		{
			p->XmlWrite(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys);
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CGuideBookExportTool::ExportItemsChild(CExBaseObject *p, UINT nClassID, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	BOOL bRet = TRUE;

	switch (nClassID)
	{
	case GBCLASSID_MACROTEST:
		Export((CMacroTest*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_COMMCMD:
		Export((CCommCmd*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_SAFETY:
		Export((CSafety*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_SYSPARAEDIT:
		Export((CSysParaEdit*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_MACROCHARITEMS:
		Export((CMacroCharItems*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_ITEMS:
		Export((CItems*)p, oXMLDoc, oParent);
		break;

	case GBCLASSID_ITEMSRSLTEXPR:
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportScriptExprScript)
		{
			p->XmlWrite(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys);
		}
		break;

	default:
		bRet = FALSE;
		break;
	}
	
	return bRet;
}

void CGuideBookExportTool::Export(CDevice *pDevice, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlDevice = NULL;
	pDevice->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlDevice);

	UINT nClassID = 0;
	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pDevice->GetNext(pos);
		nClassID = p->GetClassID();

		if (ExportItemChild(p, nClassID, oXMLDoc, *pXmlDevice))
		{
			continue;
		}

		if (ExportItemsChild(p, nClassID, oXMLDoc, *pXmlDevice))
		{
			continue;
		}

		switch (nClassID)
		{
		case GBCLASSID_CPUS:
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportDeviceModule)
			{
				p->XmlWrite(oXMLDoc, *pXmlDevice, CGbXMLKeys::g_pGbXMLKeys);
			}
			break;

		case GBCLASSID_DEVICE_SYSPARAS:
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportSysParas)
			{
				p->XmlWrite(oXMLDoc, *pXmlDevice, CGbXMLKeys::g_pGbXMLKeys);
			}
			break;

		default:
			break;
		}
	}
}

void CGuideBookExportTool::Export(CJobGuide *pJobGuide, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlJobGuide = NULL;
	pJobGuide->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlJobGuide);

	UINT nClassID = 0;
	POS pos = pJobGuide->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pJobGuide->GetNext(pos);
		nClassID = p->GetClassID();

		if (ExportItemChild(p, nClassID, oXMLDoc, *pXmlJobGuide))
		{
			continue;
		}

		if (ExportItemsChild(p, nClassID, oXMLDoc, *pXmlJobGuide))
		{
			continue;
		}
	}
}
void CGuideBookExportTool::Export(CItems *pItems, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{
	CXmlRWElementBase *pXmlItems = NULL;
	pItems->XmlWriteEx(oXMLDoc, oParent, CGbXMLKeys::g_pGbXMLKeys, pXmlItems);

	UINT nClassID = 0;
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pItems->GetNext(pos);
		nClassID = p->GetClassID();

		if (ExportItemChild(p, nClassID, oXMLDoc, *pXmlItems))
		{
			continue;
		}

		if (ExportItemsChild(p, nClassID, oXMLDoc, *pXmlItems))
		{
			continue;
		}
	}

}


void CGuideBookExportTool::Export(CSysParaEdit *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
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

		if (ExportItemChild(p, nClassID, oXMLDoc, *pXmlItem))
		{
			continue;
		}

		if (nClassID == DTMCLASSID_CVALUES)
		{
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportSysParaEditValues)
			{
				p->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
			}
		}
	}
}

void CGuideBookExportTool::Export(CSafety *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
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

		if (ExportItemChild(p, nClassID, oXMLDoc, *pXmlItem))
		{
			continue;
		}

		if (nClassID == GBCLASSID_MSG)
		{
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportSafetyMsg)
			{
				p->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
			}
			continue;
		}

		if (nClassID == DTMCLASSID_CSHORTDATAS)
		{
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportSafetyDatas)
			{
				p->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
			}
			continue;
		}

		if (nClassID == GBCLASSID_DLLCALL)
		{
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportSafetyDllCall)
			{
				p->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
			}
			continue;
		}
	}
}

void CGuideBookExportTool::Export(CMacroTest *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
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

		if (ExportItemChild(p, nClassID, oXMLDoc, *pXmlItem))
		{
			continue;
		}

		if (nClassID == GBCLASSID_COMMCMD)
		{
			Export((CCommCmd*)p, oXMLDoc, *pXmlItem);
			continue;
		}

		if (nClassID == GBCLASSID_SAFETY)
		{
			Export((CSafety*)p, oXMLDoc, *pXmlItem);
			continue;
		}

		if (nClassID == GBCLASSID_MACROPARA)
		{
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportMacroTestParas)
			{
				p->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
			}
			continue;
		}
	}
}

void CGuideBookExportTool::Export(CCommCmd *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
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

		if (ExportItemChild(p, nClassID, oXMLDoc, *pXmlItem))
		{
			continue;
		}

		if (nClassID == GBCLASSID_CMD)
		{
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportCmdPara)
			{
				p->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
			}
			continue;
		}

		if (nClassID == DTMCLASSID_CSHORTDATAS)
		{
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportCmdDatas)
			{
				p->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
			}
			continue;
		}

		if (nClassID == DVMCLASSID_CDSVSCRIPT)
		{
			if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportCmdDsvScript)
			{
				p->XmlWrite(oXMLDoc, *pXmlItem, CGbXMLKeys::g_pGbXMLKeys);
			}
			continue;
		}
	}
}

void CGuideBookExportTool::Export(CMacroCharItems *pItem, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
{

}

// void CGuideBookExportTool::Export(CReportMap *pRptMap, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
// {
// 
// }
// 
// void CGuideBookExportTool::Export(CReports *pReorts, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent)
// {
// 
// }
