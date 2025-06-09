#include "stdafx.h"
#include "GbItemBase.h"
#ifndef NOT_USE_GB_SCRIPT
#include "Script/GbScriptFunctions.h"
#endif 
#include "Items.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/Expression/EpExpression.h"
#include "../RecorderInterface.h"

#include "../XLanguageResourceAts.h"
#include "GuideBook.h"
#include "../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../../../Module/System/TickCount32.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const CString CGbItemBase::g_strItemFilePathKey    = _T("ITEM_FILE_PATH");
const CString CGbItemBase::g_strReportFilePathKey = _T("REPORT_FILE_PATH");
const CString CGbItemBase::g_strItemPathKey_gbrpt = _T("GBRPT");
const CString CGbItemBase::g_strItemPathKey_ItemIndex = _T("ITEM_INDEX");
const CString CGbItemBase::g_strItemPathKey_ItemName = _T("ITEM_NAME");
const CString CGbItemBase::g_strItemPathKey_ItemID = _T("ITEM_ID");

long g_nSmartTestMode = TEST_MODE_AUTOTEST;
//2023-9-11  李俊庆 拷贝时，只拷贝必要信息，用于给MES或者其他外部系统，去掉script、report-map等对象
long g_nGbCopyItemForMes = 0;

CGbItemBase::CGbItemBase()
{
	//m_dwReserved：用于记录和保存SystemReport的表格，清空
	m_dwReserved = 0;

	m_nIndex = 0;
	m_nTkID = 0xFFFF;
	m_nShow = 1;
	m_nEnable = 1;
	m_nExecType = 0;
	m_nBatchItem = 0;
	m_nSelect = 1;
	m_nState = TEST_STATE_NORMAL;
	m_nRsltJdg = 1;

	m_nExpandState = 0;

	 m_pInitScriptText = NULL;
	 m_pResultScriptText = NULL;
	 m_pNameScriptText = NULL;
	 m_pReports = NULL;
	 m_pReportsBack = NULL;
	 m_pRptMap = NULL;

	 m_pRptRef = NULL; //报告模板编辑的关联对象
	 m_nBreakLoopState = 0;
	 m_bIsSubItem = FALSE;

	 m_nMdvTestEach = 0;

	 //lijunqing 2022-9-24
	 m_pRsltExprRun = NULL;
}

CGbItemBase::~CGbItemBase()
{
#ifdef guidebook_report_dev_mode
	if (m_pReports != NULL)
	{
		delete m_pReports;
		m_pReports = NULL;
	}
#endif

	m_oSubGbItems.RemoveAll();
}

BOOL CGbItemBase::IsTestFinish()
{
	//如果没有选择，则认为是完成状态
	if (m_nSelect == 0)
	{
		return TRUE;
	}

	if (m_nEnable == 0 || m_nShow == 0)
	{
		return TRUE;
	}

	//测试合格、不合格、测试合格扩展，都认为是完成状态
	long nState = GetState();

	if ((nState == TEST_STATE_INLEGIBLE) || (nState == TEST_STATE_ELIGIBLEEX)
		|| (nState == TEST_STATE_ELIGIBLE))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CGbItemBase::SetTkID(long nTkID)
{ 
	m_nTkID = nTkID;
}

void CGbItemBase::SetSelect(long nSelect)
{ 
	m_nSelect = nSelect;
}

long CGbItemBase::GetState()
{
	//shaolei 2024-3-1 注释此处。会导致父节点的测试状态更新出错
// 	if (m_nSelect == 0)
// 	{//如果没有选中，默认为合格
// 		return TEST_STATE_ELIGIBLE;
// 	}

// 	if (m_nState < TEST_STATE_NORMAL || m_nState > TEST_STATE_INLEGIBLE)
// 	{
// 		m_nState = TEST_STATE_INLEGIBLE;
// 	}

	return (m_nState & 0x0F);
}

BOOL CGbItemBase::IsSkipState()
{
	return ((m_nState & 0xFF) >> 8) == TEST_STATE_SKIP;
}

long CGbItemBase::GetStateEx()
{
	POS pos = m_pReports->GetHeadPosition();
	long nCount = m_pReports->GetCount();

	if (nCount == 1)
	{
		return GetState();
	}

	long nRsltJdg1 = 0;
	long nRsltJdg0 = 0;
	CReport *pReport = NULL;
	
	while (pos != NULL)
	{
		pReport = (CReport*)m_pReports->GetNext(pos);

		if (pReport->GetResultJudge() == 1)
		{
			nRsltJdg1++;
		}
		else
		{
			nRsltJdg0++;
		}
	}

	if (nCount == nRsltJdg1)
	{
		return TEST_STATE_ELIGIBLE;
	}
	
	if (nCount == nRsltJdg0)
	{
		return TEST_STATE_INLEGIBLE;
	}

	return TEST_STATE_ELIGIBLEEX;
}

void CGbItemBase::SetState(long nState)
{
	if (g_nSmartTestMode == TEST_MODE_SINGLETEST)
	{
		//在单机测试模式下，直接赋值测试项目的状态，而不根据项目的报告去设置状态
		m_nState = nState;
		return;
	}

	if (nState == TEST_STATE_STOPED )
	{
		//ASSERT (m_pReports != NULL);
		if(m_pReports != NULL)
		{
			long nCount = m_pReports->GetCount();

			if (nCount > 0)
			{
				if (! InitStateByReport())
				{
					m_nState = nState;
				}
			}
			else
			{
				m_nState = nState;
			}
		}	
		else
		{
			m_nState = nState;
		}
	}
	else
	{
		if (nState == TEST_STATE_SKIP)
		{
			m_nState |= (TEST_STATE_SKIP << 8);
		}
		else
		{
			if ( ((nState >> 8) & 0xFF) == TEST_STATE_SKIP)
			{
				m_nState |= (TEST_STATE_SKIP << 8);
			}
			else
			{
				m_nState = nState;

				
			}
		}
	}

// 	if (nState == TEST_STATE_INLEGIBLE)
// 	{
// 		SetRsltJdg(0);
// 	}
// 
// 	if (nState == TEST_STATE_ELIGIBLE)
// 	{
// 		SetRsltJdg(1);
// 	}
}

void CGbItemBase::UpdateRsltJdgByState(long nState)
{
	if (m_pReports == NULL)
	{
		return;
	}

	long nRsltJdg = 0;

	if (nState == TEST_STATE_INLEGIBLE)
	{
		nRsltJdg = 0;
	}
	else if (nState == TEST_STATE_ELIGIBLE)
	{
		nRsltJdg = 1;
	}
	else
	{
		return;
	}

	m_nRsltJdg = nRsltJdg;

	CReport *pReport = GetReport(0);

	if (pReport == NULL)
	{
		pReport = AddReport(0,0);
	}

	//更新于结果判断相关的信息
	pReport->SetResultJudge(nRsltJdg);
}

BOOL CGbItemBase::IsEnableAndShow()
{
	if (m_pParent == NULL)
	{
		return TRUE;
	}

	if (GetClassID() == GBCLASSID_DEVICE)
	{
		return TRUE;
	}

	if ((m_nEnable == 0) || (m_nShow == 0))
	{
		return FALSE;
	}

	if  (! ((CGbItemBase*)m_pParent)->IsEnableAndShow() )
	{
		return FALSE;
	}

	return ((m_nEnable == 1) && (m_nShow == 1));
}

long CGbItemBase::GetSubGbItemsRsltJdg()
{
	POS pos = m_oSubGbItems.GetHeadPosition();
	CGbItemBase *pSub = NULL;
	long nRsltJdg = 1;

	while (pos != NULL)
	{
		pSub = (CGbItemBase *)m_oSubGbItems.GetNext(pos);

		if (pSub->m_nState == TEST_STATE_INLEGIBLE)
		{
			nRsltJdg = 0;
			break;
		}
	}

	return nRsltJdg;
}


//根据报告数据设置state
BOOL CGbItemBase::InitStateByReport()
{
	Gb_SetGbModifiedFlag(this, TRUE);
	ASSERT (m_pReports != NULL);
	
	if (m_pReports == NULL)
	{
		m_nState = TEST_STATE_INLEGIBLE;
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Item(%s) error"), m_strName.GetString());
		return TRUE;
	}

	long nCount = m_pReports->GetCount();

	if (nCount == 0)
	{
		m_nState = TEST_STATE_INLEGIBLE;
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Item(%s) error"), m_strName.GetString());
		return TRUE;
	}

	CReport *pReport = (CReport*)m_pReports->GetTail();
	ASSERT (pReport != NULL);

    CValue *pValue = pReport->FindReportData(g_strTestResultJudgeKey);

	if (pValue == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Item(%s) not define %s"),  m_strID.GetString(), g_strTestResultJudgeKey.GetString());
		//m_nState = TEST_STATE_INLEGIBLE;
		return FALSE;
	}
	else
	{
#ifdef _UNICODE
		long nRsltJdg = _wtol(pValue->m_strValue);
#else
        long nRsltJdg = atol(pValue->m_strValue.GetString());
#endif

		if(nRsltJdg < 0)
			return FALSE;

		if (nRsltJdg > 0)
		{
			if (GetSubGbItemsRsltJdg() == 0)
			{
				m_nState = TEST_STATE_INLEGIBLE;
			}
			else
			{
				m_nState = TEST_STATE_ELIGIBLE;
			}
		}
		else
		{
			m_nState = TEST_STATE_INLEGIBLE;
		}

		return TRUE;
	}
}

BOOL CGbItemBase::ValidResultScript()
{
	if (m_pResultScriptText == NULL)
	{
		return FALSE;
	}

	if (m_pResultScriptText->m_strScriptText.GetLength() < 5)
	{
		return FALSE;
	}

	return TRUE;
}

long CGbItemBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_nIndex);
		BinarySerializeCalLen(oBinaryBuffer,m_nTkID);
		BinarySerializeCalLen(oBinaryBuffer,m_nShow);
		BinarySerializeCalLen(oBinaryBuffer,m_nEnable);
		BinarySerializeCalLen(oBinaryBuffer,m_nExecType);
		BinarySerializeCalLen(oBinaryBuffer,m_nSelect);
		BinarySerializeCalLen(oBinaryBuffer,m_nState);
		BinarySerializeCalLen(oBinaryBuffer,m_nRsltJdg);
		BinarySerializeCalLen(oBinaryBuffer,m_nExpandState);
		BinarySerializeCalLen(oBinaryBuffer,m_nMdvTestEach);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_nIndex);
		BinarySerializeRead(oBinaryBuffer,m_nTkID);
		BinarySerializeRead(oBinaryBuffer,m_nShow);
		BinarySerializeRead(oBinaryBuffer,m_nEnable);
		BinarySerializeRead(oBinaryBuffer,m_nExecType);
		BinarySerializeRead(oBinaryBuffer,m_nSelect);
		BinarySerializeRead(oBinaryBuffer,m_nState);
		BinarySerializeRead(oBinaryBuffer,m_nRsltJdg);
		BinarySerializeRead(oBinaryBuffer,m_nExpandState);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_36)
		{
			BinarySerializeRead(oBinaryBuffer,m_nMdvTestEach);
		}
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_nIndex);
		BinarySerializeWrite(oBinaryBuffer,m_nTkID);
		BinarySerializeWrite(oBinaryBuffer,m_nShow);
		BinarySerializeWrite(oBinaryBuffer,m_nEnable);
		BinarySerializeWrite(oBinaryBuffer,m_nExecType);
		BinarySerializeWrite(oBinaryBuffer,m_nSelect);

		//2020-12-21 shaolei
#ifdef GUIDEBOOK_DEV_MODE
		m_nState = 0;
#endif
		BinarySerializeWrite(oBinaryBuffer,m_nState);
		BinarySerializeWrite(oBinaryBuffer,m_nRsltJdg);
		BinarySerializeWrite(oBinaryBuffer,m_nExpandState);
		BinarySerializeWrite(oBinaryBuffer,m_nMdvTestEach);
	}

	return 0;
}

long CGbItemBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTkIDKey,oNode,m_nTkID);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strShowKey,oNode,m_nShow);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strEnableKey,oNode,m_nEnable);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strExecTypeKey,oNode,m_nExecType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strBatchItemKey,oNode,m_nBatchItem);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMdvTestEachKey,oNode, m_nMdvTestEach);

	//2020-12-09  lijunqing
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strStateKey,oNode, m_nState);
    xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strSelectKey,oNode, m_nSelect);

	return 0;
}

long CGbItemBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);

	if (g_bGbExportXmlReportFile)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportItemAttrSimplify)
		{
			return 0;
		}
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTkIDKey,oElement,m_nTkID);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strSelectKey,oElement,m_nSelect);

	if (g_bGbSaveGbStruDscFile)
	{
		if (g_bGbSaveItemState_WhenSavedscxml)
		{
			xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strStateKey,oElement,m_nState);
		}
		
		return 0;
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strShowKey,oElement,m_nShow);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strEnableKey,oElement,m_nEnable);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strExecTypeKey,oElement,m_nExecType);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strBatchItemKey,oElement,m_nBatchItem);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strMdvTestEachKey,oElement,m_nMdvTestEach);
	
	//2020-12-21 shaolei
#ifdef GUIDEBOOK_DEV_MODE
	m_nState = 0;
#endif

	if (CGbXMLKeys::g_pGbXMLKeys->m_nSaveItemRpts <= 0)
	{
		//不保存报告时，将项目的状态，设置成TEST_STATE_NORMAL  shaolei 2023-9-14
		long nState = m_nState;
		m_nState = TEST_STATE_NORMAL;
		xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strStateKey,oElement,m_nState);
		m_nState = nState;
		return 0;
	}

	//2020-12-09  lijunqing
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strStateKey,oElement,m_nState);

	return 0;
}

BOOL CGbItemBase::InitSubIems()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	m_oSubGbItems.RemoveAll();

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_COMMCMD:
		case GBCLASSID_SAFETY:
			m_oSubGbItems.AddTail(p);
			((CGbItemBase*)p)->m_bIsSubItem = TRUE;
			break;

		default:
			break;
		}
	}

	return TRUE;
}

void CGbItemBase::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	m_oSubGbItems.RemoveAll();

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_SCRIPTTEXT_INIT:
			m_pInitScriptText = (CScriptTextInit*)p;
			break;
		case GBCLASSID_SCRIPTTEXT_NAME:
			m_pNameScriptText = (CScriptTextName*)p;
			break;
		case GBCLASSID_SCRIPTTEXT_RESULT:
			m_pResultScriptText = (CScriptTextResult*)p;
			break;
		case GBCLASSID_REPORTS:
			m_pReports = (CReports*)p;
			break;
		case GBCLASSID_REPORTSBACK:
			m_pReportsBack = (CReportsBack*)p;
			break;
		case RPTCLASSID_RPTREPORTMAP:
			m_pRptMap = (CReportMap*)p;
			break;

// 		case GBCLASSID_COMMCMD:
// 		case GBCLASSID_SAFETY:
// 			m_oSubGbItems.AddTail(p);
// 			((CGbItemBase*)p)->m_bIsSubItem = TRUE;
// 			break;

			//lijunqing 2022-9-24
		case GBCLASSID_ITEMRSLTEXPRRUN:
			m_pRsltExprRun = (CItemRsltExprRun*)p;

		default:
			break;
		}
	}

	if (m_pReports == NULL)
	{
		m_pReports = new CReports();
#ifndef guidebook_report_dev_mode
		AddNewChild(m_pReports);
#endif
	}
	else
	{
#ifdef guidebook_report_dev_mode
		Remove(m_pReports);
#endif
	}

	if (g_nGbCopyItemForMes == 1)
	{
		return;
	}

	if (m_pInitScriptText == NULL)
	{
		m_pInitScriptText = new CScriptTextInit();
		AddNewChild(m_pInitScriptText);
	}

	if (m_pNameScriptText == NULL)
	{
		m_pNameScriptText = new CScriptTextName();
		AddNewChild(m_pNameScriptText);
	}

	if (m_pResultScriptText == NULL)
	{
		m_pResultScriptText = new CScriptTextResult();
		AddNewChild(m_pResultScriptText);
	}

	if (m_pRptMap == NULL)
	{
		m_pRptMap = new CReportMap();
		AddNewChild(m_pRptMap);
	}
}

BOOL CGbItemBase::IsEqual(CBaseObject* pObj)
{
	return 0;
}

BOOL CGbItemBase::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if (this == pDest)
	{
		return TRUE;
	}
	
	CExBaseObject::CopyOwn(pDest);
	CGbItemBase *pItem = (CGbItemBase*)pDest;

	pItem->m_nIndex = m_nIndex;
	pItem->m_nTkID = m_nTkID;
	pItem->m_nShow = m_nShow;
	pItem->m_nEnable = m_nEnable;
	pItem->m_nExecType = m_nExecType;
	pItem->m_nSelect = m_nSelect;
	pItem->m_nState = m_nState;
	pItem->m_nRsltJdg = m_nRsltJdg;
	pItem->m_nExpandState = m_nExpandState;
	pItem->m_nMdvTestEach = m_nMdvTestEach;

	return TRUE;
}


BOOL CGbItemBase::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_MSG)
	{
		return TRUE;
	}

	return FALSE;
}


CExBaseObject* CGbItemBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CGbXMLKeys *pGbXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	if(strClassID == pGbXmlKeys->m_strScriptKey)
	{
		ASSERT (FALSE);
		return NULL;//new CScriptText();
	}
	else if(strClassID == pGbXmlKeys->m_strScriptInitKey)
	{
		m_pInitScriptText = new CScriptTextInit();
		return m_pInitScriptText;
	}
	else if(strClassID == pGbXmlKeys->m_strScriptResultKey)
	{
		m_pResultScriptText = new CScriptTextResult();
		return m_pResultScriptText;
	}
	else if(strClassID == pGbXmlKeys->m_strScriptNameKey)
	{
		m_pNameScriptText = new CScriptTextName();
		return m_pNameScriptText;
	}
	else if(strClassID == pGbXmlKeys->m_strReportsKey)
	{
		m_pReports = new CReports();
		return m_pReports;
	}
	else if(strClassID == pGbXmlKeys->m_strReportMapKey)
	{
		m_pRptMap = new CReportMap();
		return m_pRptMap;
	}
	else if(strClassID == pGbXmlKeys->m_strCItemRsltExprRunKey)
	{
		m_pRsltExprRun = new CItemRsltExprRun();
		return m_pRsltExprRun;
	}

	return NULL;
}

CExBaseObject* CGbItemBase::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_SCRIPTTEXT)
	{
		return new CScriptText();
	}
	else if (nClassID == GBCLASSID_SCRIPTTEXT_INIT)
	{
		return new CScriptTextInit();
	}
	else if (nClassID == GBCLASSID_SCRIPTTEXT_NAME)
	{
		return new CScriptTextName();
	}
	else if (nClassID == GBCLASSID_SCRIPTTEXT_RESULT)
	{
		return new CScriptTextResult();
	}
	else if(nClassID == GBCLASSID_REPORTS)
	{
		m_pReports = new CReports();
		return m_pReports;
	}
	else if(nClassID == RPTCLASSID_RPTREPORTMAP)
	{
		m_pRptMap = new CReportMap();
		return m_pRptMap;
	}
	else if(nClassID == GBCLASSID_REPORTSBACK)
	{
		m_pReportsBack = new CReportsBack();
		return m_pReportsBack;
	}
	else if(nClassID == GBCLASSID_ITEMRSLTEXPRRUN)
	{
		m_pRsltExprRun = new CItemRsltExprRun();
		return m_pRsltExprRun;
	}

	return NULL;
}

void CGbItemBase::SetRsltJdg(long nRsltJdg)
{
	m_nRsltJdg = nRsltJdg;

	if (m_pReports == NULL)
	{
		return;
	}

	//更新于结果判断相关的信息
	m_pReports->SetResultJudge(nRsltJdg);
	InitStateByReport();
	Gb_UpdateGbItemParentTestState(this);
}

void CGbItemBase::SetRsltJdg(CReport *pReport, long nRsltJdg)
{
	if (pReport == NULL)
	{
		return;
	}

	m_nRsltJdg = nRsltJdg;

	//更新于结果判断相关的信息
	pReport->SetResultJudge(nRsltJdg);

	InitStateByReport();
	Gb_UpdateGbItemParentTestState(this);
}

//公共接口

void CGbItemBase::CreateReports()
{
	if(m_pReports == NULL)
	{
		m_pReports = new CReports();
		m_pReports->SetParent(this);
		AddTail(m_pReports);
	}
}

void CGbItemBase::DeleteReport()
{
	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">>>>>>>>>>>>>>>>>>CGbItemBase::DeleteReport()---------------1---%s"), m_strID);
	if (m_pReports == NULL)
	{
		return;
	}

	POS pos = m_pReports->GetTailPosition();
	//ASSERT (pos != NULL);

	if (pos == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">>>>>>>>>>>>>>>>>>CGbItemBase::DeleteReport()---------------2---%s"), m_strID);
		return;
	}

	CReport *pReport = (CReport*)m_pReports->GetAt(pos);

	if (pReport->m_strEndTime.GetLength() > 0)
	{
		return;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">>>>>>>>>>>>>>>>>>CGbItemBase::DeleteReport()---------------3---%s"), m_strID);
	m_pReports->DeleteAt(pos);
}

BOOL CGbItemBase::HasReport()
{
	if (m_pReports == NULL)
	{
		return FALSE;
	}

	if (m_pReports->GetCount() == 0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbItemBase::HasReportEx()
{
	if (m_pReports == NULL)
	{
		return FALSE;
	}

	return m_pReports->HasReportEx();
}

CReport* CGbItemBase::AddReport(const CString &strName, const CString &strReportID)
{
	CreateReports();
	CReport* pReport = m_pReports->AddReport(strName, strReportID);	
	return pReport;
}

CReport* CGbItemBase::AddReport(long nRepeatTimes, long nTestIndex)
{
	CreateReports();

	CString strID, strName;
	GetCurrSystemtimeString(strName);

	if (nRepeatTimes > 0)
	{
		strID.Format(_T("Rpt%02d_%d_%d"), m_pReports->GetCount(), nRepeatTimes, nTestIndex);
	}
	else
	{
		strID.Format(_T("Rpt%02d"), m_pReports->GetCount());
	}

	return AddReport(strName, strID);
}

CReport* CGbItemBase::AddReport(CShortDatas  *pDatas)
{
	ASSERT (m_pReports != NULL);

	CReport* pReport = AddReport(-1, -1);
	SetReportValues(pDatas);

	return pReport;
}

CReport* CGbItemBase::AddReport(CValues* pValues)
{
	ASSERT (m_pReports != NULL);

	CReport* pReport = AddReport(-1, -1);
	SetReportValues(pValues);

	return pReport;
}

void CGbItemBase::DeleteReport(CReport *pReport)
{
	ASSERT(m_pReports != NULL);
	m_pReports->Delete(pReport);
}

BOOL CGbItemBase::SetReportValues(CValues* pValues)
{
	ASSERT (m_pReports != NULL);
	if(m_pReports == NULL)
		return FALSE;

	BOOL bTrue = m_pReports->SetReportValues(pValues);
	ASSERT (bTrue);

	return bTrue;
}

BOOL CGbItemBase::SetReportValues(CShortDatas  *pDatas)
{
	ASSERT (m_pReports != NULL);
	if(m_pReports == NULL)
		return FALSE;

	BOOL bTrue = m_pReports->SetReportValues(pDatas);
	ASSERT (bTrue);

	return bTrue;
}

BOOL CGbItemBase::RunResultScript(CString &strSyntax, BOOL bInitTrue, long nCurrTestTimes, long nRepeatTimes)
{
#ifndef guidebook_report_dev_mode
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook->IsTestError())
	{
		SetRsltJdg(1);
		return TRUE;
	}

	//缺省设置为合格
	if (bInitTrue)
	{
		SetRsltJdg(1);
	}

	//执行测试结果判断脚本
    strSyntax.Format(_T("Item(%s[%s]) ResultScript"), m_strName.GetString(), m_strID.GetString());

	if(m_pResultScriptText == NULL)
	{
		Gb_UpdateGbItemParentTestState(this);
		return FALSE;
	}

	long nErrors = 0;
#ifndef NOT_USE_GB_SCRIPT
	nErrors = Gb_RunScript(m_pResultScriptText, strSyntax, TRUE);
	if (nErrors > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ItemRstError.GetString()/*_T("项目【%s】结果脚本语法错误")*/, m_strName.GetString());
		m_nRsltJdg = 0;//如果脚本有语法错误，测试项目设置为不合格
		SetRsltJdg(0);
	}
#endif	

	AdjustReprtDatas();

	//2022-9-24  lijunqing
	if (m_pRsltExprRun != NULL)
	{
		if (m_pRsltExprRun->CanRun())
		{
			CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
			//函数传入this指针，是为了提高点效率，在表达式每个计算对象中
			//也可以获取当前项目的指针
			m_nRsltJdg = m_pRsltExprRun->RunRsltExprScript(this, pDevice, nCurrTestTimes, nRepeatTimes);
		}
	}

	m_pReports->SetResultJudge(m_nRsltJdg);

	if (m_nRsltJdg == 1)
	{
		m_nState = TEST_STATE_ELIGIBLE;
	}
	else
	{
		m_nState = TEST_STATE_INLEGIBLE;
	}

	Gb_UpdateGbItemParentTestState(this);

	//若存在需要插入项目树的项目，等待项目插入完成
	//Gb_WaitItemsInsertTree();

	return (nErrors == 0);
#else
	return 0;
#endif
}

BOOL CGbItemBase::RunInitScriptScript(CString &strSyntax)
{
#ifndef guidebook_report_dev_mode
	//执行测试结果判断脚本
	strSyntax.Format(_T("%d"), 10);
	long nErrors = 0;
#ifndef NOT_USE_GB_SCRIPT
	nErrors = Gb_RunScript(m_pInitScriptText, strSyntax);

	if (nErrors)
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"Item(%s[%s]) InitScript : %s", m_strName, m_strID, strSyntax);
	}
	else
	{

	}
#endif

	return (nErrors == 0);
#else
	return 0;
#endif

}

//shaolei  2023-4-15  仅执行结果判断表达式
BOOL CGbItemBase::RunRsltExpr_Only(long nCurrTestTimes, long nRepeatTimes)
{
	if (m_pRsltExprRun != NULL)
	{
		if (m_pRsltExprRun->CanRun())
		{
			CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
			//函数传入this指针，是为了提高点效率，在表达式每个计算对象中
			//也可以获取当前项目的指针
			m_nRsltJdg = m_pRsltExprRun->RunRsltExprScript(this, pDevice, nCurrTestTimes, nRepeatTimes);
		}
	}

	m_pReports->SetResultJudge(m_nRsltJdg);

	if (m_nRsltJdg == 1)
	{
		m_nState = TEST_STATE_ELIGIBLE;
	}
	else
	{
		m_nState = TEST_STATE_INLEGIBLE;
	}

	Gb_UpdateGbItemParentTestState(this);

	return 0;
}

void CGbItemBase::UpdateItemsReport()
{
	if (!Gb_IsItemsTestFinished(this))
	{
		return;
	}

	CreateReports();
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		pReport = AddReport(0, 0);
	}

	CValues *pValues = pReport->GetValues();
	ASSERT( pValues != NULL );

	if (pValues != NULL)
	{
		if ( (m_nState == TEST_STATE_ELIGIBLEEX)
			|| (m_nState == TEST_STATE_ELIGIBLE) )
		{
			Gb_AddResultJudgeKey(pValues, 1);
		}
		else
		{
			Gb_AddResultJudgeKey(pValues, 0);
		}
	}

}

CGbItemBase* CGbItemBase::GetFirstParentItems()
{
	CGbItemBase *pItems = (CGbItemBase*)GetAncestor(GBCLASSID_ITEMS);

	if (pItems != NULL)
	{
		return pItems;
	}

	pItems = (CGbItemBase*)GetAncestor(GBCLASSID_DEVICE);

	if (pItems != NULL)
	{
		return pItems;
	}

	pItems = (CGbItemBase*)GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pItems != NULL)
	{
		return pItems;
	}

	pItems = (CGbItemBase*)GetAncestor(GBCLASSID_JOBGUIDE);

	if (pItems != NULL)
	{
		return pItems;
	}

	return NULL;
}

CGbItemBase* CGbItemBase::FindItemByID(const CString &strID, UINT nClassID)
{
	CGbItemBase *pFind = NULL;

	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	UINT nItemClassID = 0;
	CItems *pItems = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nItemClassID = pObj->GetClassID();

		if (nItemClassID == GBCLASSID_ITEMS)
		{
			pFind = pItems->FindItemByID(strID, nClassID);

			if (pFind != NULL)
			{
				break;
			}
		}

		else if (nItemClassID == nClassID)
		{
			if (pObj->m_strID == strID)
			{
				pFind = (CGbItemBase *)pObj;
				break;
			}
		}
	}
	return pFind;
}

CReports* CGbItemBase::GetReports()
{
	if (m_pReports == NULL)
	{
		CreateReports();
	}

	return m_pReports;
}

CReport* CGbItemBase::GetCurrReport()
{
	if (m_pReports == NULL)
	{
		return NULL;
	}
	if (m_pReports->GetCount()>0)
	{
		CReport *pReport = (CReport*)m_pReports->GetTail();
		return pReport;
	}
	else
	{
		return NULL;
	}
}

CReport* CGbItemBase::GetReport(long nIndex)
{
	if (m_pReports == NULL)
	{
		return NULL;
	}

	long nCount = m_pReports->GetCount();

	if (nIndex == -1)
	{
		nIndex = nCount-1;
	}

	if (nCount > nIndex )
	{
		CReport *pReport = (CReport*)m_pReports->GetAtIndex(nIndex);
		return pReport;
	}
	else
	{
		return NULL;
	}
}

CReport* CGbItemBase::GetReport(const CString &strID)
{
	if (m_pReports == NULL)
	{
		return NULL;
	}

	return (CReport*)m_pReports->FindByID(strID);
}


CScriptText* CGbItemBase::GetInitScriptText()
{
	if (m_pInitScriptText == NULL)
	{
		m_pInitScriptText = new CScriptTextInit();
		m_pInitScriptText->SetParent(this);
		AddTail(m_pInitScriptText);
	}

	return m_pInitScriptText;
}

CScriptText* CGbItemBase::GetResultScriptText()
{
	if (m_pResultScriptText == NULL)
	{
		m_pResultScriptText = new CScriptTextResult();
		m_pResultScriptText->SetParent(this);
		AddTail(m_pResultScriptText);
	}
	return m_pResultScriptText;
}

CScriptText* CGbItemBase::GetNameScriptText()
{
	if (m_pNameScriptText == NULL)
	{
		m_pNameScriptText = new CScriptTextName();
		m_pNameScriptText->SetParent(this);
		AddTail(m_pNameScriptText);
	}

	return m_pNameScriptText;
}

CValue* CGbItemBase::FindRecordFile()
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		return NULL;
	}

	CValue *pFind = (CValue*)pReport->m_pValues->FindByID(g_strRecordResultKey) ;
	
	return pFind;
}

CItems* CGbItemBase::GetRsltExprScriptItems()
{
	CExBaseList *pParent = (CExBaseList*)GetParent();
	CItems *pItems = NULL;

	while (pParent != NULL)
	{
		if (pParent->GetClassID() != GBCLASSID_ITEMS)
		{
			break;
		}

		if (((CItems*)pParent)->HasItemsRsltExprScript())
		{
			pItems = (CItems *)pParent;
			break;
		}

		pParent = (CExBaseList*)pParent->GetParent();
	}

	return pItems;
}

long CGbItemBase::SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew)
{
	ASSERT (m_pReports != NULL);
	CReport *pReport = (CReport*)m_pReports->GetTail();
	CValue *pVal = NULL;
	ASSERT (pReport != NULL);
	BOOL bTrue = FALSE;

	pVal = pReport->FindReportData(strValueID);

	if (pVal != NULL)
	{
		bTrue = TRUE;
		pVal->m_strValue = strValue;
	}
	else
	{
		//显示：数据不存在
		bTrue = FALSE;
	}

	return bTrue;
}

long CGbItemBase::SetItemReportValue(const CString &strValueID,const CString &strValue)
{
	ASSERT (m_pReports != NULL);

	if (m_pReports == NULL)
	{
		return 0;
	}

	CReport *pReport = (CReport*)m_pReports->GetTail();
	CValue *pVal = NULL;
	ASSERT (pReport != NULL);
	BOOL bTrue = FALSE;

	if (pReport == NULL)
	{
		return bTrue;
	}

	return pReport->SetValue(strValueID, strValue);
// 	pVal = pReport->FindReportData(strValueID);
// 
// 	if (pVal != NULL)
// 	{
// 		bTrue = TRUE;
// 		pVal->m_strValue = strValue;
// 	}
// 	else
// 	{
// 		//显示：数据不存在
// 		bTrue = FALSE;
// 	}
// 
// 	return bTrue;
}

long CGbItemBase::SetItemReportValue(BSTR strValueID,BSTR strValue)
{
	CString strValueID1, strValue1;
	strValueID1 = strValueID;
	strValue1    = strValue;
	return SetItemReportValue(strValueID1, strValue1);
}

double CGbItemBase::GetItemParaValue(const char* pszValueID)
{
	CString strValueID(pszValueID);
	double dValue = 1;
	GetItemParaValue(strValueID, dValue);
	return dValue;
}

BOOL CGbItemBase::GetItemParaValue(const CString &strValueID, double &dValue)
{
	return 0;
}

double CGbItemBase::GetItemReportValue(const char* pszValueID)
{
	CString strValueID;
	strValueID = pszValueID;
	double dValue = 0;
	BOOL bTrue = FALSE;
	
	bTrue = GetItemReportValue(strValueID, dValue);

	return dValue;
}

BOOL CGbItemBase::GetItemReportValue(const CString & strValueID, double &dValue)
{
	ASSERT (m_pReports != NULL);
	CReport *pReport = (CReport*)m_pReports->GetTail();
	ASSERT (pReport != NULL);

	if (pReport == NULL)
	{
		return FALSE;
	}
	
	return pReport->GetReportValue(strValueID, dValue);
}

BOOL CGbItemBase::GetItemReportValue(const CString & strValueID, CString &strValue)
{
	ASSERT (m_pReports != NULL);
	CReport *pReport = (CReport*)m_pReports->GetTail();
	ASSERT (pReport != NULL);

	if (pReport == NULL)
	{
		return FALSE;
	}

	return pReport->GetReportValue(strValueID, strValue);
}


BOOL CGbItemBase::GetItemReportValue(const char* pszValueID, char *pszValue)
{
	ASSERT (m_pReports != NULL);
	CReport *pReport = (CReport*)m_pReports->GetTail();
	ASSERT (pReport != NULL);

	if (pReport == NULL)
	{
		return FALSE;
	}

	return pReport->GetReportValue(CString(pszValueID), pszValue);
}

BOOL CGbItemBase::GetItemReportValue(const char* pszValueID, char *pszValue, long nIndex)
{
	ASSERT (m_pReports != NULL);
	CReport *pReport = NULL;
	pReport = (CReport *)m_pReports->GetAtIndex(nIndex);
	
	if (pReport == NULL)
	{
		pReport = (CReport*)m_pReports->GetTail();
	}

	ASSERT (pReport != NULL);

	if (pReport == NULL)
	{
		return FALSE;
	}

	return pReport->GetReportValue(CString(pszValueID), pszValue);
}

BOOL CGbItemBase::GetItemReportValue(const CString &strValueID, long &nValue)
{
	ASSERT (m_pReports != NULL);
	CReport *pReport = (CReport*)m_pReports->GetTail();
	ASSERT (pReport != NULL);

	if (pReport == NULL)
	{
		return FALSE;
	}

	return pReport->GetReportValue(strValueID, nValue);
}

double CGbItemBase::GetItemReportExValue(long nIndex, const char* pszValueID)
{
	CString strValueID;
	strValueID = pszValueID;
	double dValue = 0;
	BOOL bTrue = FALSE;
	
	if (m_pReports == NULL)
	{
		return dValue;
	}

	if (m_pReports->GetCount() == 0)
	{
		return dValue;
	}

	CReport *pReport = (CReport*)m_pReports->GetTail();
	CString strValue;
	
	if (pReport->GetReportExValue(nIndex, strValueID, strValue))
	{
#ifdef _UNICODE
		dValue = _wtof(strValue);
#else
        dValue = atof(strValue.GetString());
#endif
	}

	return dValue;
}

BOOL CGbItemBase::GetItemReportExValue(const char* pszDataID, const char* pszValueID, CString &strValue)
{
	CString strValueID;
	CString strDataID;
	BOOL bTrue = FALSE;


	if (m_pReports == NULL)
	{
		return FALSE;
	}

	if (m_pReports->GetCount() == 0)
	{
		return FALSE;
	}

	strValueID = pszValueID;
	strDataID = pszDataID;

	CReport *pReport = (CReport*)m_pReports->GetTail();

	bTrue = pReport->GetReportExValue(strDataID, strValueID, strValue);
	
	return bTrue;
}

long CGbItemBase::GetItemReportExCount()
{
	if (m_pReports == NULL)
	{
		return 0;
	}

	if (m_pReports->GetCount() == 0)
	{
		return 0;
	}

	CReport *pReport = (CReport*)m_pReports->GetTail();
	
	//if (pReport->m_pRptDataEx == NULL)
	if (pReport->m_pRptDvmDataset)
	{
		return 0;
	}

	return pReport->m_pRptDvmDataset->GetCount();
}

long CGbItemBase::CalItemReportTimeGap(long nItem1Index, long nItem2Index, const char* pszValID)
{
	if (m_pReports == NULL)
	{
		return 0;
	}

	if (m_pReports->GetCount() == 0)
	{
		return 0;
	}

	CReport *pReport = (CReport*)m_pReports->GetTail();

	if (pReport->m_pRptDvmDataset == NULL)
	{
		return 0;
	}

	long nCount = pReport->m_pRptDvmDataset->GetCount();

	if (nCount <= nItem1Index || nCount <= nItem2Index )
	{
		return 0;
	}

	CDvmData* oData1 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem1Index);
	CDvmData* oData2 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem2Index);

	if (oData1 == NULL || oData2 == NULL)
	{
		return 0;
	}

	CString bstrID(pszValID);
	CTag* oTime1 = (CTag*)oData1->FindByID(bstrID);
	CTag* oTime2 = (CTag*)oData2->FindByID(bstrID);

	if (oTime1 == NULL || oTime2 == NULL)
	{
		return 0;
	}

	CString strTm1 = oTime1->m_strValue;
	CString strTm2 = oTime2->m_strValue;

	try
	{
#ifndef _PSX_QT_LINUX_
        COleDateTime tm1, tm2;
		tm1.ParseDateTime(strTm1);
		tm2.ParseDateTime(strTm2);
#endif
    }
	catch(...)
	{

	}

	return 0;
}

long CGbItemBase::LGetItemReportDataCount(const CString &strDataID, long nDataValue)
{
	if (m_pReports == NULL)
	{
		return 0;
	}

	long nDataCount = 0;
	CReport *pReport = NULL;
	POS pos = m_pReports->GetHeadPosition();
	CString bstrValue;

	while (pos != NULL)
	{
		pReport = (CReport*)GetNext(pos);

		if (pReport->m_pValues == NULL)
		{
			continue;
		}

		CValue *pValue = (CValue*)pReport->m_pValues->FindByID(strDataID);

		if (pValue != NULL)
		{
#ifdef _UNICODE
			if (_wtol(pValue->m_strValue) == nDataValue)
#else
            if (atol(pValue->m_strValue.GetString()) == nDataValue)
#endif
			{
				nDataCount++;
			}
		}
	}

	return nDataCount;
}

//状态的存储，为了提高存储速度，尽量只存储必要的状态数据
long CGbItemBase::SerializeState(CBinarySerialBuffer &oBinaryBuffer)
{
	SerializeOwn(oBinaryBuffer);
//// 	CExBaseObject::SerializeOwn(oBinaryBuffer);
//
//	if (oBinaryBuffer.IsCalSizeMode())
//	{
//		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
//// 		BinarySerializeCalLen(oBinaryBuffer, m_nTkID);
//// 		BinarySerializeCalLen(oBinaryBuffer, m_nShow);
//// 		BinarySerializeCalLen(oBinaryBuffer, m_nEnable);
//// 		BinarySerializeCalLen(oBinaryBuffer, m_nExecType);
////		BinarySerializeCalLen(oBinaryBuffer, m_nSelect);
//		BinarySerializeCalLen(oBinaryBuffer, m_nState);
//		BinarySerializeCalLen(oBinaryBuffer, m_nRsltJdg);
//// 		BinarySerializeCalLen(oBinaryBuffer, m_strRsltDsc);
//	}
//	else if (oBinaryBuffer.IsReadMode())
//	{	
//		BinarySerializeRead(oBinaryBuffer, m_nIndex);
////		BinarySerializeRead(oBinaryBuffer, m_nTkID);
//// 		BinarySerializeRead(oBinaryBuffer, m_nShow);
//// 		BinarySerializeRead(oBinaryBuffer, m_nEnable);
//// 		BinarySerializeRead(oBinaryBuffer, m_nExecType);
//// 		BinarySerializeRead(oBinaryBuffer, m_nSelect);
//		BinarySerializeRead(oBinaryBuffer, m_nState);
//		BinarySerializeRead(oBinaryBuffer, m_nRsltJdg);
//// 		BinarySerializeRead(oBinaryBuffer, m_strRsltDsc);
//	}
//	else if (oBinaryBuffer.IsWriteMode())
//	{
//		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
//// 		BinarySerializeWrite(oBinaryBuffer, m_nTkID);
//// 		BinarySerializeWrite(oBinaryBuffer, m_nShow);
//// 		BinarySerializeWrite(oBinaryBuffer, m_nEnable);
////		BinarySerializeWrite(oBinaryBuffer, m_nExecType);
////		BinarySerializeWrite(oBinaryBuffer, m_nSelect);
//		BinarySerializeWrite(oBinaryBuffer, m_nState);
//		BinarySerializeWrite(oBinaryBuffer, m_nRsltJdg);
////		BinarySerializeWrite(oBinaryBuffer, m_strRsltDsc);
	//	}

	return 0;
}

CGbItemBase* CGbItemBase::SelectItem(const CString &strPath)
{
	CGbItemBase *pSelectGbItem = NULL;
	CGbItemBaseList oListDest;

	SelectItems(strPath, oListDest);
	long nCount = oListDest.GetCount();

	if (nCount > 1 || nCount == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), strPath.GetString(), nCount);
	}
	else
	{
		pSelectGbItem = (CGbItemBase*)oListDest.GetHead();
	}

	oListDest.RemoveAll();

	return pSelectGbItem;
}

long CGbItemBase::SelectItems(const CString &strPath, CGbItemBaseList &oListDest)
{
    //2020-12-21 shaolei
    if (strPath.GetLength() == 0)
    {//路径为空 当前节点符合条件
        oListDest.AddTail(this);
        return 0;
    }

	UINT nClassID = GetClassID();
	BOOL bIsItems = (nClassID == GBCLASSID_ITEMS);
	CString strPathLeft, strPathRight;
	CGbItemBase* pTemp;

	//跳转至根节点 排除路径中的绝对路径
	int nSepPos = strPath.ReverseFind('/');

	if (nSepPos != -1)
	{
		pTemp = (CGbItemBase*)GetRoot();
		return pTemp == NULL ? -1 : pTemp->SelectItems(strPath.Mid(nSepPos+1), oListDest);
	}

	if (strPath[0] == '\\')
	{	//路径开始处的'\'符号为分隔符号 在此处跳过这些符号
		int i = 1;
		for (i = 1;strPath[i] == '\\'; i++);
		return SelectItems(strPath.Mid(i), oListDest);
	}

	nSepPos = strPath.Find('\\');		//寻找第一个'\'符号，将路径分为两部分 左部为要跳转至的节点 右部为传递给下一节点的参数

	if (nSepPos == -1)
	{
		strPathLeft = strPath;
		strPathRight = "";
	}
	else
	{
		strPathLeft = strPath.Left(nSepPos);
		strPathRight = strPath.Mid(nSepPos+1);
	}

	if (strPathLeft == ".")			//选择当前节点 继续查找
	{
		SelectItems(strPathRight, oListDest);
	} 
	else if (strPathLeft == "..")	//选中父节点 继续查找
	{
		pTemp = (CGbItemBase*)GetParent();//parent一定是CExBaseList对象
		pTemp == NULL ? -1 : pTemp->SelectItems(strPathRight, oListDest);
	}
	else if (strPathLeft == "?")	//匹配一级任意路径
	{
		if (bIsItems)	
		{//BaseObject 不存在子节点
			SelectChildrenItems(strPathRight, oListDest);
		}
	}
	else if (strPathLeft == "*")	//匹配任意级数的任意路径
	{
		SelectItems(strPathRight, oListDest);//将"*"匹配为空(零级)

		if ( bIsItems)	//BaseObject 不存在子节点
		{
			//SelectChildrenItems(strPathRight, oListDest);
			SelectChildrenItems(strPath, oListDest);
		}
	}
	else
	{
		SelectItemsLeft_Var(strPath, strPathLeft, strPathRight, oListDest);
	}

	return 0;
}

long CGbItemBase::SelectItemsLeft_Var(const CString &strPath, const CString &strPathLeft, const CString &strPathRight, CGbItemBaseList &oListDest)
{
	BOOL bIsBaseObject = IsBaseObject();

	if (bIsBaseObject)	//BaseObject 不存在子节点
	{
		if (strPathRight == "")
		{
			if (strPath == m_strID)
			{
				oListDest.AddTail(this);
			}
		}

		return 0;
	}
	else
	{
		CGbItemBase *pObj = NULL;

		if (strPathRight == "")
		{
// 			if (strPath == m_strID)
// 			{
// 				oListDest.AddTail(this);
// 			}

			pObj =(CGbItemBase*) ( ((CItems*)this)->FindByID(strPathLeft) );

			if (pObj != NULL)
			{
				oListDest.AddTail(pObj);
			}
		}
		else
		{
			pObj = (CGbItemBase*) ( ((CItems*)this)->FindByID(strPathLeft) );

			if (pObj == NULL)
			{
				return -1;
			}
			else
			{
				pObj->SelectItems(strPathRight, oListDest);
			}
		}
	}

	return 0;
}

BOOL CGbItemBase::SaveBinaryTempFile(const CString &strTempFilePath,const CString& strTempFileName)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("+++++for debug +++++ CGbItemBase::SaveBinaryTempFile   %s"), strTempFilePath.GetString());
	CreateAllDirectories(strTempFilePath);

	CBinarySerialBuffer oBuffer;
	Gb_InitGuideBookFileVersion(oBuffer);
	oBuffer.SetVersionFindByID(g_dwDataMngrVersionID);

	oBuffer.SetCalSizeMode();
	oBuffer.WriteVersion();
	Serialize(oBuffer);
	oBuffer.AllocBuffer(5);

	oBuffer.SetWriteMode();
	oBuffer.WriteVersion();
	Serialize(oBuffer);

	oBuffer.SaveToFile(strTempFileName);

	return TRUE;
}

BOOL CGbItemBase::OpenBinaryTempFile()
{
	if (HasReportEx())
	{
		return FALSE;
	}

	CString strTempFilePath = ats_GetBinaryTempFilePath(this);
	CString strTempFileName = ats_GetBinaryTempFile(strTempFilePath, this);
	return OpenBinaryTempFile(strTempFileName);
}

BOOL CGbItemBase::OpenBinaryTempFileReport(CBinarySerialBuffer &oBuffer)
{
	if (HasReportEx())
	{
		return FALSE;
	}

	CGbItemBase *pNew = CloneForTempFile();
	pNew->SetParent(GetParent());
	CString strTempFilePath = ats_GetBinaryTempFilePath(this);
	CString strTempFileName = ats_GetBinaryTempFile(strTempFilePath, this);

	if ( ! IsFileExist(strTempFilePath))
	{
		return FALSE;
	}

	BOOL bRet = pNew->OpenBinaryTempFile(strTempFileName, oBuffer);

	if (!bRet)
	{
		return bRet;
	}

	m_pReports->DeleteAll();
	m_pReports->AppendEx(*pNew->m_pReports);
	pNew->m_pReports->RemoveAll();
	delete pNew;

	return bRet;
}

BOOL CGbItemBase::OpenBinaryTempFile(const CString& strFileName)
{
	CBinarySerialBuffer oBuffer;
	return OpenBinaryTempFile(strFileName, oBuffer);
// 	DeleteAll();
// 
// 	CBinarySerialBuffer oBuffer;
// 	Gb_InitGuideBookFileVersion(oBuffer);
// 	oBuffer.ResetVersion();
// 
// 	if ( ! oBuffer.OpenFromFile(strFileName) )
// 	{
// 		return FALSE;
// 	}
// 
// 	oBuffer.SetReadMode();
// 	oBuffer.ReadVersion();
// 	oBuffer.SetVersionFindByID(g_dwDataMngrVersionID);
// 
// 	try
// 	{
// 		Serialize(oBuffer);
// 	}
// 	catch (...)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_FileRightError/*_T("文件【%s】版本错误！")*/, strFileName);
// 	}
// 
// 	return TRUE;
}

BOOL CGbItemBase::OpenBinaryTempFile(const CString& strFileName, 	CBinarySerialBuffer &oBuffer)
{
	DeleteAll();
	Gb_InitGuideBookFileVersion(oBuffer);
	oBuffer.ResetVersion();

	if ( ! oBuffer.OpenFromFile(strFileName, 5) )
	{
		return FALSE;
	}

	oBuffer.SetReadMode();
	oBuffer.ReadVersion();
	oBuffer.SetVersionFindByID(g_dwDataMngrVersionID);

	try
	{
		Serialize(oBuffer);
	}
	catch (...)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_FileRightError.GetString()/*_T("文件【%s】版本错误！")*/, strFileName.GetString());
	}

	return TRUE;
}

BOOL CGbItemBase::SaveXmlTempFile(const CString &strTempFilePath,const CString& strTempFileName)
{
	CreateAllDirectories(strTempFilePath);

	SaveXmlFile(strTempFileName, CGbXMLKeys::g_pGbXMLKeys);

	return TRUE;
}


BOOL CGbItemBase::OpenXmlTempFile(const CString& strFileName)
{
	DeleteAll();

	OpenXmlFile(strFileName, CGbXMLKeys::g_pGbXMLKeys);

	return TRUE;
}


CGbItemBase* CGbItemBase::CloneForTempFile(const CString& strTempFileName)
{
	CGbItemBase *pNew = CloneForTempFile();
	pNew->SetParent(m_pParent);
	CReports *pReports = NULL;
	
	if (!pNew->OpenBinaryTempFile(strTempFileName))
	{
		Copy(pNew);
		pReports = pNew->GetReports();
		pReports->DeleteAll();
	}
	else
	{
		pReports = pNew->GetReports();
	}

	CReport *pReport = GetReport(-1);
	pReports->AddTail(pReport);

	return pNew;
}

void CGbItemBase::FreeCloneForTempFile()
{
	CReports *pReports = GetReports();
	POS pos = pReports->GetTailPosition();
	pReports->RemoveAt(pos);
}

CGbItemBase* CGbItemBase::CloneForTempFile()
{
	return NULL;
}

CGbItemBase* CGbItemBase::OpenBinaryTempFileForRpt(const CString& strTempFileName)
{
	CGbItemBase *pNew = CloneForTempFile();

	if (pNew == NULL)
	{
		return NULL;
	}

	pNew->SetParent(GetParent());
	
	if (pNew->OpenBinaryTempFile(strTempFileName))
	{
		return pNew;
	}
	else
	{
		delete pNew;
		return NULL;
	}
}

 CGbItemBase* CGbItemBase::OpenBinaryTempFileForRpt(const CString& strTempFileName, 	CBinarySerialBuffer &oBuffer)
 {
	 try
	 {
		 CGbItemBase *pNew = NULL;
		 pNew = CloneForTempFile();

		 if (pNew == NULL)
		 {
			 return NULL;
		 }

		 pNew->InitAfterRead();

		 if (pNew->OpenBinaryTempFile(strTempFileName, oBuffer))
		 {
			 if (pNew->m_pRptMap != NULL)
			 {
				 if ((pNew->m_pRptMap->GetCount() == 0) && (m_pRptMap != NULL))
				 {
					 pNew->m_pRptMap->AppendClone(m_pRptMap);
				 }
			 }

			 pNew->SetParent(m_pParent);
			 return pNew;
		 }
		 else
		 {
			 delete pNew;
			 return NULL;
		 }
	 }
	 catch (...)
	 {
         CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error: open [%s] failed"), strTempFileName.GetString());
	 	return NULL;
	 }
 }

void CGbItemBase::ClearReportDatasByMap(const CString& strTempFilePath, const CString& strTempFileName, const CString &strXmlFile, BOOL bIsWriteTestTempFile)
{
	//避免多装置多组测试导致内存不足
	CReport *pReport = GetReport(-1);
	pReport->ClearReportDatasByMap(GetReportMap()
		, TRUE, 2);
}

void CGbItemBase::GetReportDatasByMap(CExBaseList *pListDatas)
{
    CReport *pReport = GetReport(-1);

    if(pReport == NULL)
        return;

    pReport->GetReportDatasByMap(GetReportMap(), pListDatas);
}

void CGbItemBase::ClearItemInDbState()
{
// 	if (m_pInitScriptText != NULL)
// 	{
// 		m_pInitScriptText->ClearItemInDbState();
// 	}
// 
// 	if (m_pResultScriptText != NULL)
// 	{
// 		m_pResultScriptText->ClearItemInDbState();
// 	}
// 
// 	if (m_pNameScriptText != NULL)
// 	{
// 		m_pNameScriptText->ClearItemInDbState();
// 	}

	if (m_pReports != NULL)
	{
		m_pReports->ClearItemInDbState();
	}
}

#ifdef GUIDEBOOK_DEV_MODE

void CGbItemBase::GenerateDevReports()
{
	
}

#endif


BOOL CGbItemBase::CopyChildren(CBaseObject* pDest)
{
	if (pDest->IsBaseObject() || IsBaseObject())
	{
		return FALSE;
	}

	CExBaseList *pList = (CExBaseList*)pDest;
	CExBaseObject *pObj = NULL;
	CExBaseObject *pNew = NULL;
	POS pos = GetHeadPosition();
	pList->DeleteAll();
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

#ifdef GUIDEBOOK_DEV_MODE
		if (nClassID == GBCLASSID_REPORTS || nClassID == GBCLASSID_REPORT)
		{
			continue;
		}
#endif

		if (g_nGbCopyItemForMes == 1)
		{
			if (nClassID == GBCLASSID_SCRIPTTEXT || nClassID == GBCLASSID_SCRIPTTEXT_INIT
				|| nClassID == GBCLASSID_SCRIPTTEXT_NAME || nClassID == GBCLASSID_SCRIPTTEXT_RESULT
				|| nClassID == RPTCLASSID_RPTREPORTMAP || nClassID == GBCLASSID_ITEMRSLTEXPRRUN
				|| nClassID == GBCLASSID_STANDARD || nClassID == GBCLASSID_DLLCALL
				|| nClassID == GBCLASSID_ITEMSRSLTEXPRSCRIPT)
			{
				continue;
			}
		}

		ASSERT(pObj != NULL);
		pNew = (CExBaseObject*)pObj->Clone();

		if (pNew != NULL)
		{
			pList->AddTail(pNew);
			pNew->SetParent(pList);
		}
	}

	return TRUE;
}


long CGbItemBase::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

#ifdef GUIDEBOOK_DEV_MODE
		if (nClassID == GBCLASSID_REPORTS)
		{
			continue;
		}
#endif

		if (g_bGbExportXmlReportFile)
		{
			if (Gb_IsItemNeedExportRpt(nClassID))
			{
				pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
			}
		}
		else
		{
// 			if (nClassID == GBCLASSID_REPORTS)
// 			{
// 				if (CGbXMLKeys::g_pGbXMLKeys->m_nSaveItemRpts <= 0)
// 				{
// 					continue;
// 				}
// 			}

			pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
		}
	}

	return 0;
}
// 
// long CGbItemBase::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
// {
// 	CExBaseObject *pObj = NULL;
// 	POS pos = GetHeadPosition();
// 	long nClassID = 0;
// 	long nCount = 0;
// 	long nIndex = 0;
// 
// 	if (oBinaryBuffer.IsCalSizeMode())
// 	{
// 		nCount = GetCount();
// 		oBinaryBuffer.AddBufferLength(sizeof(nCount));
// 		oBinaryBuffer.AddBufferLength(sizeof(nClassID) * nCount);
// 
// 		for (nIndex=0; nIndex<nCount; nIndex++)
// 		{
// 			pObj = GetNext(pos);
// 
// // 			if (pObj->GetClassID() == GBCLASSID_REPORTS)
// // 			{
// // 				continue;;
// // 			}
// 
// 			pObj->Serialize(oBinaryBuffer);
// 		}
// 	}
// 	else if (oBinaryBuffer.IsReadMode())
// 	{
// 		nCount = oBinaryBuffer.GetLong();
// 
// 		for (nIndex=0;nIndex<nCount;nIndex++)
// 		{
// 			nClassID = oBinaryBuffer.GetLong();
// 
// // 			if (nClassID == GBCLASSID_REPORTS)
// // 			{
// // 				continue;;
// // 			}
// 
// 			pObj = CreateNewChild(nClassID);
// 
// 			if (pObj != NULL)
// 			{
// 				pObj->SetParent(this);
// 				pObj->Serialize(oBinaryBuffer);
// 				AddNode(pObj);
// 			}
// 			else
// 			{
// 				ASSERT(pObj != NULL);
// 			}
// 		}
// 	}
// 	else if (oBinaryBuffer.IsWriteMode())
// 	{
// 		nCount = GetCount();
// 		oBinaryBuffer.PutLong(nCount);
// 
// 		while (pos)
// 		{
// 			pObj = GetNext(pos);
// 			nClassID = pObj->GetClassID();
// 
// // 			if (nClassID == GBCLASSID_REPORTS)
// // 			{
// // 				continue;;
// // 			}
// 
// 			oBinaryBuffer.PutLong(nClassID);
// 			pObj->Serialize(oBinaryBuffer);
// 		}
// 	}
// 
// 	return 0;
// }

//获取项目关联的设备的CPU
CExBaseObject* CGbItemBase::GetCpu(const CString &strCpu)
{
#ifdef _UNICODE
	long nIndex = _wtol(strCpu);
#else
    long nIndex = atol(strCpu.GetString());
#endif

    if (IsStringNumber(strCpu.GetString()))
	{
#ifdef _UNICODE
		nIndex = _wtol(strCpu);
#else
        nIndex = atol(strCpu.GetString());
#endif

		return GetCpu(nIndex);
	}
	else
	{
		CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
		CCpus *pCpus = pDevice->m_pCpus;
		CExBaseObject *pFind = NULL;

		pFind = pCpus->FindByID(strCpu);

		if(pFind == NULL)
		{
			pFind = pCpus->FindByName(strCpu);
		}

		return pFind;
	}
}

long CGbItemBase::GetCpuIndex(const CString &strCpu)
{
	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);

	CCpus *pCpus = pDevice->m_pCpus;
	long nIndex = 0, nFindIndex=0;

	CCpu *pCpu = NULL;
	POS pos = pCpus->GetHeadPosition();

	while (pos != NULL)
	{
		pCpu = (CCpu*)pCpus->GetNext(pos);

		if (pCpu->m_strID == strCpu)
		{
			nFindIndex = nIndex;
			break;
		}

		nIndex++;
	}

	return nFindIndex;
}

CExBaseObject* CGbItemBase::GetCpu(long nCpuIndex)
{
	CBaseObject *p = GetAncestor(GBCLASSID_DEVICE);

	if (p == NULL)
	{
		return NULL;
	}

	CDevice *pDevice = (CDevice*)p;

	if (pDevice->m_pCpus != NULL)
	{
		long nCount = pDevice->m_pCpus->GetCount();

		if (nCount == 0)
		{
			return NULL;
		}

		else if (nCount == 1)
		{
			return pDevice->m_pCpus->GetAtIndex(0);
		}
		else
		{
			return pDevice->m_pCpus->GetAtIndex(nCpuIndex);
		}
	}
	else
	{
		return NULL;
	}
}

BOOL Gb_ISTestingSubtem(CGbItemBase *pItem)
{
	UINT nClassID = pItem->GetClassID();
	BOOL bTrue = FALSE;

	if (nClassID == GBCLASSID_COMMCMD)
	{
		CBaseObject *pParent = pItem->GetParent();
		UINT nParentClassID = pParent->GetClassID();

		if (nParentClassID == GBCLASSID_ITEMS || nParentClassID == GBCLASSID_JOBGUIDE
			|| nParentClassID == GBCLASSID_DEVICE)
		{
			bTrue = FALSE;
		}
		else
		{
			bTrue = TRUE;
		}
	}
	else 	if (nClassID == GBCLASSID_SAFETY)
	{
		CBaseObject *pParent = pItem->GetParent();
		UINT nParentClassID = pParent->GetClassID();

		if (nParentClassID == GBCLASSID_MACROTEST)
		{
			bTrue = TRUE;
		}
		else
		{
			bTrue = FALSE;
		}
	}

	return bTrue;
}

CReportMap* CGbItemBase::GetReportMap()
{
	if (m_pRptMap == NULL)
	{
		m_pRptMap = new CReportMap();
		AddNewChild(m_pRptMap);
	}

	return m_pRptMap;
}

CString CGbItemBase::GetPathName()
{
	CString strTemp, strRet;
	CBaseObject* pTemp;

	strRet = "";

	for (pTemp = this; pTemp != NULL; pTemp = pTemp->GetParent())
	{
		strTemp = strRet;
		strRet = ((CExBaseObject*)pTemp)->m_strName;
        strRet += _P_FOLDER_PATH_SEPARATOR_;
		strRet += strTemp;
	}

	strRet.TrimRight('\\');
	return strRet;
}

void CGbItemBase::ClearReport(BOOL bBack)
{
	if (bBack)
	{
		if (m_pReportsBack == NULL)
		{
			m_pReportsBack = new CReportsBack();
			AddNewChild(m_pReportsBack);
		}

		if (m_pReports != NULL)
		{
			m_pReportsBack->Append(m_pReports);
			m_pReports->RemoveAll();
		}
	}
	else
	{
		if (m_pReportsBack != NULL)
		{
			m_pReportsBack->DeleteAll();
		}

		if (m_pReports != NULL)
		{
			//m_pReports->DeleteAll();
			CReport *pInitReport = (CReport *)m_pReports->FindByID(_T("_Init_"));

			if (pInitReport != NULL)
			{
				m_pReports->Remove(pInitReport);
			}

			m_pReports->DeleteAll();

			if (pInitReport != NULL)
			{
				m_pReports->AddNewChild(pInitReport);
			}
		}
	}
}

double CGbItemBase::CalRptValMax(const CString &strValID, double &dMax)
{
	if (m_pReports == NULL)
	{
		return dMax;
	}

	POS pos = m_pReports->GetHeadPosition();
	CReport *pRpt = NULL;
	CValue *pFind = NULL;

	while (pos != NULL)
	{
		pRpt = (CReport *)m_pReports->GetNext(pos);
		pFind = (CValue *)pRpt->m_pValues->FindByID(strValID);

		if (pFind != NULL)
		{
			dMax = max(dMax, CString_To_double(pFind->m_strValue));
		}
	}

	return dMax;
}

double CGbItemBase::CalRptValMin(const CString &strValID, double &dMin)
{
	if (m_pReports == NULL)
	{
		return dMin;
	}

	POS pos = m_pReports->GetHeadPosition();
	CReport *pRpt = NULL;
	CValue *pFind = NULL;

	while (pos != NULL)
	{
		pRpt = (CReport *)m_pReports->GetNext(pos);
		pFind = (CValue *)pRpt->m_pValues->FindByID(strValID);

		if (pFind != NULL)
		{
			dMin = min(dMin, CString_To_double(pFind->m_strValue));
		}
	}

	return dMin;
}

long CGbItemBase::CalRptValSum(const CString &strValID, double &dValue, long &nCount)
{
	if (m_pReports == NULL)
	{
		return 0;
	}

	POS pos = m_pReports->GetHeadPosition();
	CReport *pRpt = NULL;
	CValue *pFind = NULL;

	while (pos != NULL)
	{
		pRpt = (CReport *)m_pReports->GetNext(pos);
		pFind = (CValue *)pRpt->m_pValues->FindByID(strValID);

		if (pFind != NULL)
		{
			dValue += CString_To_double(pFind->m_strValue);
			nCount++;
		}
	}

	return nCount;
}

CString CGbItemBase::GetItemStringPath()
{
	CString strPath;
	CExBaseObject *pParent = this;

	while (pParent != NULL)
	{
		strPath = _T("[") + pParent->m_strName + _T("]") + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent->GetClassID() == GBCLASSID_GUIDEBOOK)
		{
			break;
		}
	}

	return strPath;
}

void CGbItemBase::ReplaceSrciptText(CScriptText *pScript, UINT nScriptClassID, CGbItemBase *pSrcGbItem, BOOL bShowLog)
{
	switch (nScriptClassID)
	{
	case GBCLASSID_SCRIPTTEXT_INIT:
		pScript->CopyOwn(m_pInitScriptText);
		break;
	case GBCLASSID_SCRIPTTEXT_RESULT:
		pScript->CopyOwn(m_pResultScriptText);
		break;
	case GBCLASSID_SCRIPTTEXT_NAME:
		pScript->CopyOwn(m_pNameScriptText);
		break;
	}
}

BOOL CGbItemBase::Parse_Item_File_Path(const CString &strEpxr, CGbItemBase **ppSelectItem)
{
	CString strPath, strRight;

	if (!Gb_Parse_Item_File_Path(strEpxr, g_strItemFilePathKey, strPath, strRight))
	{
		return FALSE;
	}

// 	long nLen = g_strItemFilePathKey.GetLength();
// 
// 	if (strEpxr.Left(nLen) != )
// 	{
// 		return FALSE;
// 	}
// 
// 	CString strPath = strEpxr.Mid(nLen);
// 	strPath.Trim();
// 	TCHAR ch = strPath.GetAt(0);
// 
// 	if (ch == '[' || ch=='{')
// 	{
// 		strPath = strPath.Mid(1);
// 	}
// 
// 	nLen = strPath.GetLength();
// 	ch = strPath.GetAt(nLen-1);
// 
// 	if (ch == ']' || ch=='}')
// 	{
// 		strPath = strPath.Left(nLen-1);
// 	}

	*ppSelectItem = SelectItem(strPath);

	return TRUE;
}

//2020-02-03  lijq update items paras
/*

BOOL CGbItemBase::UpdateOwn(CBaseObject* pDest)
{
ASSERT(pDest != NULL);

if (this == pDest)
{
return TRUE;
}

CGbItemBase *pItem = (CGbItemBase*)pDest;

pItem->m_nTkID = m_nTkID;
pItem->m_nShow = m_nShow;
pItem->m_nEnable = m_nEnable;
pItem->m_nExecType = m_nExecType;
pItem->m_nMdvTestEach = m_nMdvTestEach;

m_pInitScriptText->Update(pItem->m_pInitScriptText);
m_pResultScriptText->Update(pItem->m_pResultScriptText);
m_pNameScriptText->Update(pItem->m_pNameScriptText);

return TRUE;
}

BOOL CGbItemBase::UpdateChildren(CBaseObject* pDest)
{
return CExBaseList::UpdateChildren(pDest);
}

*/
// BOOL CGbItemBase::Update(CBaseObject* pDest)
// {
// 	return TRUE;
// }

BOOL CGbItemBase::UpdateOwn(CBaseObject* pDest)
{
	CGbItemBase *pItem = (CGbItemBase*)pDest;

	CReports *pNewReports = GetReports();
	CReports *pOldReports = pItem->GetReports();
	pNewReports->AppendCloneEx(*pOldReports);

	m_nExpandState = pItem->m_nExpandState;
	m_nRsltJdg = pItem->m_nRsltJdg;
	m_nState = pItem->m_nState;
	m_nTkID = pItem->m_nTkID;
	m_nShow = pItem->m_nShow;
	m_nEnable = pItem->m_nEnable;
	m_nExecType = pItem->m_nExecType;
	m_nMdvTestEach = pItem->m_nMdvTestEach;
	m_nIndex = pItem->m_nIndex;

	return TRUE;
}


void CGbItemBase::UpdateItem(CItems *pDestItems, CGbItemBase *pNewItem)
{
	CGbItemBase *pItemFind = (CGbItemBase*)pDestItems->FindByID(pNewItem->m_strID);

	if (pItemFind == NULL)
	{
		pItemFind = (CGbItemBase*)pDestItems->FindByName(pNewItem->m_strName);
	}

	if (pItemFind == NULL)
	{
		return;
	}

	pNewItem->Update(pItemFind);
}

BOOL CGbItemBase::UpdateChildren(CBaseObject* pDest)
{
	CItems *pDestItems = (CItems*)pDest;

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (Gb_IsGbItemClassID(nClassID))
		{
			UpdateItem(pDestItems, (CGbItemBase*)p);
		}
		else
		{
		}
	}

	return TRUE;
}

void CGbItemBase::AfterUpdateItemIndex(long nOldIndex)
{
#ifndef _PSX_QT_LINUX_
    ASSERT (m_nIndex != nOldIndex);

	if (m_nIndex == nOldIndex || m_nIndex == 0)
	{
		return;
	}

#ifndef GUIDEBOOK_DEV_MODE
	CString strDestFilePath = Gb_GetItemTempFilePath(this);
	CString strSrcFilePath;
	strSrcFilePath.Format(_T("%d"), nOldIndex);
	strSrcFilePath = ChangeFileName(strDestFilePath, strSrcFilePath);

	if (!IsFileExist(strSrcFilePath))
	{
		return;
	}

	::rename(strSrcFilePath, strDestFilePath);

	strDestFilePath = ChangeFilePostfix(strDestFilePath, _T("xml"));
	strSrcFilePath = ChangeFilePostfix(strSrcFilePath, _T("xml"));
	::rename(strSrcFilePath, strDestFilePath);

#endif
#endif
}

BOOL CGbItemBase::GetTestTime(CString &strBeginTime, CString &strEndTime, BOOL bUseParent)
{
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		return FALSE;
	}

	strBeginTime = pReport->GetBeginTime();
	strEndTime = pReport->GetEndTime();

	if (!bUseParent)
	{
		return TRUE;
	}


	if (m_pParent == NULL)
	{
		return TRUE;
	}

	UINT nClassID = m_pParent->GetClassID();

	if ((nClassID != GBCLASSID_MACROTEST)
		&& (nClassID != GBCLASSID_SAFETY)
		&& (nClassID != GBCLASSID_SYSPARAEDIT) )
	{
		return TRUE;
	}

	CString strBeginTime2,strEndTime2;
	((CGbItemBase*)m_pParent)->GetTestTime(strBeginTime2, strEndTime2, FALSE);
	
	CGpsPcTime tm1, tm2;
	tm1.FromString(strBeginTime);
	tm2.FromString(strBeginTime2);

	if (tm1 > tm2)
	{
		strBeginTime = strBeginTime2;
	}

	tm1.FromString(strEndTime);
	tm2.FromString(strEndTime2);

	if (tm1 < tm2)
	{
		strEndTime = strEndTime2;
	}

	return TRUE;
}

CString CGbItemBase::GetActLogic_String()
{
	CString strActLogic;
	CExBaseObject *pParent = this;

	while (pParent != NULL)
	{
		UINT nClassID = pParent->GetClassID();

		if (nClassID == GBCLASSID_DEVICE)
		{
			break;
		}

		if(nClassID == GBCLASSID_ITEMS)
		{
			strActLogic = ((CItems *)pParent)->m_strActLogic;

			if(strActLogic.GetLength() > 0)
			{
				break;
			}
		}

		pParent = (CExBaseObject*)pParent->GetParent();
	}

	return strActLogic;
}

void CGbItemBase::GetItemsCount(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount)
{
	nEligibleCount = 0;
	nInlegibleCount = 0;
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if(!Gb_IsItemBaseClassID(nClassID))
		{
			continue;
		}

		CGbItemBase *pItem = (CGbItemBase *)pObj;

		if (!pItem->GetSelect())
		{
			continue;
		}

		if (nClassID != GBCLASSID_ITEMS)
		{
			nTotalCount++;

			if (pItem->GetState() == TEST_STATE_ELIGIBLE || pItem->GetState() == TEST_STATE_ELIGIBLEEX)
			{
				nEligibleCount++;
			}
			else if (pItem->GetState() == TEST_STATE_INLEGIBLE)
			{
				nInlegibleCount++;
			}
		}

		long nTotal = 0, nEligible = 0, nInlegible = 0;
		pItem->GetItemsCount(nTotal, nEligible, nInlegible);
		nTotalCount += nTotal;
		nEligibleCount += nEligible;
		nInlegibleCount += nInlegible;
	}
}

//shaolei 20220607
void CGbItemBase::SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect)
{
	if (bSetEnable)
	{
		SetEnable(nEnable);
	}

	if (bSetSelect)
	{
		SetSelect(nSelect);
	}

	if (bSetShow)
	{
		SetShow(nShow);
	}
}

//shaolei 20221020
CGbItemBase* CGbItemBase::GetPrevItem(CGbItemBase *pCurrItem)
{
	POS pos = Find(pCurrItem);
	GetPrev(pos);
	CGbItemBase *pFind = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetPrev(pos);
		nClassID = pObj->GetClassID();

		if (Gb_IsItemBaseClassID(nClassID))
		{
			pFind = (CGbItemBase *)pObj;
			break;
		}
	}

	return pFind;
}

CGbItemBase* CGbItemBase::GetNextItem(CGbItemBase *pCurrItem)
{
	POS pos = Find(pCurrItem);
	GetNext(pos);
	CGbItemBase *pFind = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (Gb_IsItemBaseClassID(nClassID))
		{
			pFind = (CGbItemBase *)pObj;
			break;
		}
	}

	return pFind;
}

CItemRsltExprRun* CGbItemBase::GetRsltExpr()
{
	if (m_pRsltExprRun != NULL)
	{
		return m_pRsltExprRun;
	}

	m_pRsltExprRun = new CItemRsltExprRun();
	AddNewChild(m_pRsltExprRun);
	return m_pRsltExprRun;
}

void CGbItemBase::GetRsltExpr(CString &strRsltExpr)
{
	if (m_pRsltExprRun == NULL)
	{
		return;
	}

	strRsltExpr = m_pRsltExprRun->GetXml(CGbXMLKeys::g_pXmlKeys);
}

CGbItemBase* CGbItemBase::FindItemByIDHas(const CString &strID)
{
	CGbItemBase *pItemFind = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			if (pObj->m_strID.Find(strID) >= 0)
			{
				pItemFind = (CGbItemBase *)pObj;
				break;
			}
		}

		if (Gb_IsGbItemClassID(nClassID))
		{
			if (pObj->m_strID.Find(strID) >= 0)
			{
				pItemFind = (CGbItemBase *)pObj;
				break;
			}
		}
	}

	return pItemFind;
}

CGbItemBase* CGbItemBase::FindItemByIDHas(const CString &strID, UINT nClassID)
{
	CGbItemBase *pItemFind = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (nClassID == pObj->GetClassID())
		{
			if (pObj->m_strID.Find(strID) >= 0)
			{
				pItemFind = (CGbItemBase *)pObj;
				break;
			}
		}
	}

	return pItemFind;
}

// bRecursion：是否递归删除子项目
void CGbItemBase::DeleteChildItem_Commcmd(BOOL bRecursion)
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_COMMCMD)
		{
			m_oSubGbItems.Remove(pObj);
			Delete(pObj);
		}
		else if (nClassID == GBCLASSID_ITEMS)
		{
			if (! bRecursion)
			{
				continue;
			}

			CItems* pItems = (CItems *)pObj;
			pItems->DeleteChildItem_Commcmd();
		}
		else if (nClassID == GBCLASSID_MACROTEST)
		{
			if (! bRecursion)
			{
				continue;
			}

			CMacroTest *pMacroTest = (CMacroTest *)pObj;
			pMacroTest->DeleteChildItem_Commcmd();
		}
		else if (nClassID == GBCLASSID_SAFETY)
		{
			if (! bRecursion)
			{
				continue;
			}

			CSafety *pSafety = (CSafety *)pObj;
			pSafety->DeleteChildItem_Commcmd();
		}
		else if (nClassID == GBCLASSID_SYSPARAEDIT)
		{
			if (! bRecursion)
			{
				continue;
			}

			CSysParaEdit *pSysParaEdit = (CSysParaEdit *)pObj;
			pSysParaEdit->DeleteChildItem_Commcmd();
		}
	}
}

BOOL CGbItemBase::IsHasChildItem(UINT nClassID)
{
	return (FindByClassID(GBCLASSID_COMMCMD) != NULL);
}

//bRecursion：是否递归调用
long CGbItemBase::GetChildItem(UINT nClassID, CExBaseList *pList, BOOL bRecursion)
{
	POS pos = GetHeadPosition();
	UINT nChildClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nChildClassID = pObj->GetClassID();

		if(bRecursion)
		{
			if (Gb_IsItemBaseClassID(nChildClassID))
			{
				CGbItemBase *pChild = (CGbItemBase *)pObj;
				pChild->GetChildItem(nClassID, pList, bRecursion);
			}
		}

		if (nChildClassID != nClassID)
		{
			continue;
		}

		pList->AddTail(pObj);
	}

	return pList->GetCount();
}

//shaolei  2024-4-18
//判断this是否是形参的祖先节点。是返回TRUE。用于判断是否是子项目
BOOL CGbItemBase::IsAncestorOf(CGbItemBase *pItem)
{
	if (pItem == NULL)
	{
		return FALSE;
	}

	CExBaseObject *pParent = pItem;
	BOOL bRet = FALSE;

	while (pParent != NULL)
	{
		if (pParent == this)
		{
			bRet = TRUE;
			break;
		}

		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL Gb_Parse_Item_File_Path(const CString &strEpxr, const CString &strPathKey, CString &strPath, CString &strAppend)
{
	long nLen = strPathKey.GetLength();

	if (strEpxr.Left(nLen) != strPathKey)
	{
		return FALSE;
	}

	strPath = strEpxr.Mid(nLen);
	strPath.Trim();

	if (strPath.GetLength() == 0)
	{
		return TRUE;
	}

	TCHAR ch = strPath.GetAt(0);

	if (ch == '[' || ch=='{')
	{
		strPath = strPath.Mid(1);
	}

	nLen = strPath.GetLength();

	if (nLen == 0)
	{
		return TRUE;
	}

	long nPos = 0;

	while (nPos < nLen)
	{
		ch = strPath.GetAt(nPos);

		if (ch == ']' || ch=='}')
		{
			break;
		}

		nPos++;
	}

	if (nPos < nLen)
	{
		strAppend = strPath.Mid(nPos+1);
	}

	strPath = strPath.Left(nPos);

	return TRUE;
}


CGbItemBase* Gb_GetParentItem(CBaseObject *pObj)
{
	UINT nClassID = 0;
	CBaseObject *pParent = NULL;
	CGbItemBase *pItem = NULL;

	if (pObj == NULL)
	{
		return NULL;
	}

	pParent = pObj->GetParent();

	while (pParent != NULL)
	{
		nClassID = pParent->GetClassID();

		//if (Gb_IsItemsBaseClassID())
		if (Gb_IsGbItemClassID(nClassID))
		{
			pItem = (CGbItemBase*)pParent;
			break;
		}
		else
		{
			pParent = pParent->GetParent();
		}
	}

	return pItem;
}


DWORD Gb_UpdateGbItemTestState(CExBaseList *pGbItem, DWORD *pdwTestState, long nCount)
{
	DWORD nState = TEST_STATE_NORMAL;

	if (pdwTestState[TEST_STATE_NORMAL] == nCount)
	{
		nState = TEST_STATE_NORMAL;
	}
	else if (pdwTestState[TEST_STATE_ELIGIBLE] == nCount)
	{
		nState = TEST_STATE_ELIGIBLE;
	}
	else if (pdwTestState[TEST_STATE_TESTING] > 0)
	{
		nState = TEST_STATE_TESTING;
	}
	else if (pdwTestState[TEST_STATE_STOPED] > 0)
	{
		nState = TEST_STATE_STOPED;
	}
	else if (pdwTestState[TEST_STATE_INLEGIBLE] > 0)
	{
		nState = TEST_STATE_INLEGIBLE;
	}
	else
	{
		nState = TEST_STATE_NORMAL;
	}

	((CGbItemBase*)pGbItem)->SetState(nState);
	((CGbItemBase*)pGbItem)->UpdateRsltJdgByState(nState);

	return nState;
}

DWORD Gb_UpdateGbItemTestStateByChildren(CExBaseList *pGbItems)
{
	UINT nClassID = 0;
	nClassID = pGbItems->GetClassID();
	CGbItemBase *pItem = (CGbItemBase*)pGbItems;

	if(Gb_IsItemBaseClassID(nClassID))
	{
		return ((CGbItemBase*)pGbItems)->GetState();
	}

	if (pItem->m_nSelect == 0)
	{
		return TEST_STATE_ELIGIBLE;
	}

	if (!Gb_IsItemsBaseClassID(nClassID))
	{
		return TEST_STATE_NORMAL;
	}

	CExBaseObject *pObj = NULL;
	DWORD narrTestState[TEST_STATE_COUNT];
	memset(narrTestState,0,sizeof(long)*TEST_STATE_COUNT);
	POS pos = pGbItems->GetHeadPosition();
	long nState = 0;
	long nCount = 0;

	while (pos != NULL)
	{
		pObj = (CExBaseObject*)pGbItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (Gb_IsItemsBaseClassID(nClassID))
		{
			CGbItemBase *pItem = (CGbItemBase*)pObj;

			if (pItem->m_nSelect > 0)
			{
				nState = Gb_UpdateGbItemTestStateByChildren((CExBaseList*)pObj);
				narrTestState[nState]++;
				nCount++;
			}
		}
		else if(Gb_IsItemBaseClassID(nClassID))
		{
			nState = ((CGbItemBase*)pObj)->GetState();
			narrTestState[nState]++;
			nCount++;
		}
	}

	nState = Gb_UpdateGbItemTestState(pGbItems, narrTestState, nCount);

	return nState;
}


DWORD Gb_UpdateGbItemParentTestState(CExBaseList *pGbItem)
{
	CExBaseList *pList = (CExBaseList*)pGbItem->GetParent();

	if (pList == NULL)
	{
		return TEST_STATE_NORMAL;
	}

	UINT nClassID = 0;
	nClassID = pList->GetClassID();

	if (!Gb_IsItemBaseClassID(nClassID))
	{
		return TEST_STATE_NORMAL;
	}

	CExBaseObject *pObj = NULL;
	DWORD narrTestState[TEST_STATE_COUNT];
	memset(narrTestState,0,sizeof(long)*TEST_STATE_COUNT);
	POS pos = pList->GetHeadPosition();
	long nState = 0;
	long nCount = 0;

	while (pos != NULL)
	{
		pObj = (CExBaseObject*)pList->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (Gb_IsItemBaseClassID(nClassID))
		{
			CGbItemBase *pItem = (CGbItemBase*)pObj;

			if (pItem->m_nSelect == 0)
			{
				//shaolei 2024-3-1 过滤掉没选择的项目。父项目的状态汇总，只根据已选择项目汇总
				continue;
			}

			nState = pItem->GetState();
			narrTestState[nState]++;
			nCount++;
		}
	}

	nState = Gb_UpdateGbItemTestState(pList, narrTestState, nCount);
	Gb_UpdateGbItemParentTestState(pList);
	
	return nState;
}

DWORD Gb_UpdateMacroTestItemTestStateByChildren(CGbItemBase *pMacroTestItem)
{
	long nPrevState = pMacroTestItem->GetState();

	if (nPrevState == TEST_STATE_INLEGIBLE)
	{
		return TEST_STATE_INLEGIBLE;
	}

	CExBaseObject *pObj = NULL;
	DWORD narrTestState[TEST_STATE_COUNT];
	memset(narrTestState,0,sizeof(long)*TEST_STATE_COUNT);
	POS pos = pMacroTestItem->GetHeadPosition();
	long nState = 0;
	long nCount = 0;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = (CExBaseObject*)pMacroTestItem->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (Gb_IsItemBaseClassID(nClassID))
		{
			CGbItemBase *pItem = (CGbItemBase*)pObj;
			nState = pItem->GetState();
			narrTestState[nState]++;
			nCount++;
		}
	}

	nState = Gb_UpdateGbItemTestState(pMacroTestItem, narrTestState, nCount);

	return nState;
}

CTestTypes* Gb_GetTestTypes(CExBaseObject *pObject)
{
	if (pObject == NULL)
	{
		return CTestTypeMngr::g_pTestTypes;
	}

	if (pObject->GetClassID() == GBCLASSID_GUIDEBOOK)
	{
		CGuideBook *p = (CGuideBook*)pObject;
		return &p->m_oTestTypes;
	}

	CGuideBook *pGuideBook = (CGuideBook*)pObject->GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook == NULL)
	{
		return CTestTypeMngr::g_pTestTypes;
	}
	else
	{
		return &pGuideBook->m_oTestTypes;
	}
}

CString Gb_GetWaveFilePath(const CString &strFile)
{
	if (strFile.GetLength() < 3)
	{
		return _T("");
	}

	CString strPath;
	Gb_GetWavePath(strPath);
	strPath += strFile;

	return strPath;
}

CString Gb_GetItemPathName(CExBaseObject *pObject, UINT nRootClassID)
{
	CString strPath;
	CExBaseObject *pParent = NULL;
	strPath = pObject->m_strName;

	pParent = (CExBaseObject*)pObject->GetParent();

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == nRootClassID)
		{
			break;
		}

		strPath = pParent->m_strName + _T("$") + strPath;

		pParent = (CExBaseObject*)pParent->GetParent();
	}

	return strPath;
}


BOOL Gb_IsGuideBookTemplate(CExBaseObject *pObj)
{
	CGuideBook *pGuideBook = NULL;
	
	if (pObj->GetClassID() == GBCLASSID_GUIDEBOOK)
	{
		pGuideBook = (CGuideBook*)pObj;
	}
	else
	{
		pGuideBook = (CGuideBook*)pObj->GetAncestor(GBCLASSID_GUIDEBOOK);
	}

	ASSERT (pGuideBook != NULL);

	if (pGuideBook == NULL)
	{
		return FALSE;
	}
	else
	{
		return pGuideBook->IsGuideBookTemplateFile();
	}
}

BOOL Gb_IsDeviceChildNode(CExBaseObject *pObj)
{
	CDevice *pDevice = NULL;

	if (pObj->GetClassID() == GBCLASSID_DEVICE)
	{
		pDevice = (CDevice*)pObj;
	}
	else
	{
		pDevice = (CDevice*)pObj->GetAncestor(GBCLASSID_DEVICE);
	}

	if (pDevice == NULL)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


CString Gb_GetItemPathID(CExBaseObject *pObject, UINT nRootClassID)
{
	CString strIDPath;
	CExBaseObject *pParent = pObject;
	CString strTemp;

	while (pParent != NULL)
	{
		strTemp = pParent->m_strID + _T("$");
		strIDPath = strTemp + strIDPath;
		pParent = (CExBaseObject *)pParent->GetParent();

		if (pParent->GetClassID() == nRootClassID)
		{
			break;
		}
	}

	if (strIDPath.GetLength() > 0)
	{
		strIDPath = strIDPath.Left(strIDPath.GetLength() - 1);
	}

	return strIDPath;
}

CExBaseObject* Gb_GetItemByPathID(const CString &strIDPath, CExBaseList *pRoot)
{
	CExBaseObject *pObj = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = pRoot->GetHeadPosition();
	CString strTemp;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pRoot->GetNext(pos);

		if (strIDPath == pObj->m_strID)
		{
			pFind = pObj;
		}
		else
		{
			nClassID = pObj->GetClassID();

			if (nClassID == GBCLASSID_ITEMS || nClassID == GBCLASSID_DEVICE)
			{
				strTemp = pObj->m_strID + _T("$");

#ifdef _UNICODE
				if (_wcsnicmp(strTemp, strIDPath, strTemp.GetLength()) == 0)
				{
					strTemp = strIDPath.Mid(strTemp.GetLength());
					pFind = Gb_GetItemByPathID(strTemp, (CExBaseList*)pObj);
				}
#else
                if (strncmp(strTemp.GetString(), strIDPath.GetString(), strTemp.GetLength()) == 0)
				{
					strTemp = strIDPath.Mid(strTemp.GetLength());
					pFind = Gb_GetItemByPathID(strTemp, (CExBaseList*)pObj);
				}
#endif
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

BOOL Gb_IsItemsTestFinished(CExBaseList *pList)
{
	UINT nClassID = 0;
	nClassID = pList->GetClassID();
	BOOL bFinish = TRUE;

	if (nClassID == GBCLASSID_ITEMS)
	{
		CItems *pItems = (CItems*)pList;

		if (pItems->m_nEnable == 0 || pItems->m_nSelect == 0)
		{
			return TRUE;
		}
	}

	if(Gb_IsGbItemClassID(nClassID))
	{
		return ((CGbItemBase*)pList)->IsTestFinish();
	}

	if (Gb_IsItemsBaseClassID(nClassID))
	{
		POS pos = pList->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pList->GetNext(pos);
			bFinish = Gb_IsItemsTestFinished((CExBaseList*)p);

			if (!bFinish)
			{
				break;
			}
		}
	}

	return bFinish;
}

void Gb_SetItemsAllItemState(CExBaseList *pList, long nState)
{
	UINT nClassID = 0;
	nClassID = pList->GetClassID();

	if(Gb_IsGbItemClassID(nClassID))
	{
		CGbItemBase *pItem = (CGbItemBase*)pList;
		pItem->SetState(nState);
	}

	if (Gb_IsItemsBaseClassID(nClassID))
	{
		POS pos = pList->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pList->GetNext(pos);
			Gb_SetItemsAllItemState((CExBaseList*)p, nState);
		}
	}
}

//2021-10-14  lijunqing 移到DataObj
// inline BOOL Gb_CalParaExp_FindValue(CDevice *pDevice, CValues *pValues, const CString &strVarID, CString &strValue)
// {
// 	if (pValues != NULL)
// 	{
// 		if (pValues->GetValue(strVarID, strValue))
// 		{
// 			return TRUE;
// 		}
// 	}
// 
// 	return pDevice->GetVariableValue(strVarID, strValue, TRUE);
// }
// 
// BOOL Gb_CalParaExpression(const CString &strExpress, CExBaseList *pObjDevice, double &dValue, BOOL bLogError, CValues *pValues)
// {
// 	CEpExpression oEpExp;
// 
// 	if (strExpress.GetLength() == 0)
// 	{
// 		return FALSE;
// 	}
// 
// 	if (oEpExp.ChangeEpExpression(strExpress) == -1)
// 	{
//         CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionError.GetString()/*_T("表达式【%s】 错误")*/, strExpress.GetString());
// 		return FALSE;
// 	}
// 
// 	CDevice *pDevice = (CDevice*)pObjDevice;
// 	CString strValue;
// 	POS pos = oEpExp.GetHeadPosition();
// 	CEpExpVariable *pExpVar = NULL;
// 	BOOL bTrue = TRUE;
// 
// 	while (pos != NULL)
// 	{
// 		pExpVar = oEpExp.GetNext(pos);
// 
// 		if (Gb_CalParaExp_FindValue(pDevice, pValues, pExpVar->m_strVarID, strValue))
// 		{
// #ifdef _UNICODE
// 			pExpVar->m_dValue = _wtof(strValue);
// #else
//             pExpVar->m_dValue = atof(strValue.GetString());
// #endif
// 		}
// 		else
// 		{
// 			if (bLogError)
// 			{
//                 CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionVariable.GetString()/*_T("表达式变量【%s】 错误")*/, pExpVar->m_strVarID.GetString());
// 				bTrue = FALSE;
// 			}
// 		}
// 	}
// 
// 	oEpExp.Value(dValue);
// 
// 	return bTrue;
// }
// 
// BOOL Gb_CalParaExpressionEx(const CString &strExpress, CExBaseList *pObjDevice, double &dValue, BOOL bLogError, CString &strValue)
// {
// 	CEpExpression oEpExp;
// 
// 	if (oEpExp.ChangeEpExpression(strExpress) == -1)
// 	{
// 		strValue = strExpress;
//         CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionError.GetString()/*_T("表达式【%s】 错误")*/, strExpress.GetString());
// 		return FALSE;
// 	}
// 
// 	CDevice *pDevice = (CDevice*)pObjDevice;
// 	CString strTemp;
// 	POS pos = oEpExp.GetHeadPosition();
// 	CEpExpVariable *pExpVar = NULL;
// 	BOOL bTrue = TRUE;
// 
// 	while (pos != NULL)
// 	{
// 		pExpVar = oEpExp.GetNext(pos);
// 
// 		if (pDevice->GetVariableValue(pExpVar->m_strVarID, strTemp))
// 		{
// 			if (IsStringNumber(strTemp))
// 			{
// #ifdef _UNICODE
// 				pExpVar->m_dValue = _wtof(strTemp);
// #else
//                 pExpVar->m_dValue = atof(strTemp.GetString());
// #endif
// 			}
// 			else
// 			{
// 				//字符串类型，直接返回
// 				strValue = strTemp;
// 				bTrue = FALSE;
// 				break;
// 			}
// 		}
// 		else
// 		{
// 			if (bLogError)
// 			{
// 				strValue = strExpress;
//                 CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionVariable.GetString()/*_T("表达式变量【%s】 错误")*/, pExpVar->m_strVarID.GetString());
// 				bTrue = FALSE;
// 			}
// 		}
// 	}
// 
// 	if (bTrue)
// 	{
// 		oEpExp.Value(dValue);
// 	}
// 	else
// 	{
// 		dValue = 0;
// 	}
// 
// 	return bTrue;
// }

void Gb_AddToRptValues(CDvmValue *pData, CValues *pValues,  BOOL bUseReserved)
{
	if (bUseReserved)
	{
		if (pData->m_dwReserved == 0x0FFFFFFF)
		{
			return;
		}
	}

	pValues->AddValue(pData->m_strID, pData->m_strValue);

	if (pData->GetCount() == 0)
	{
		return;
	}

	POS pos = pData->GetHeadPosition();
	CDvmValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pData->GetNext(pos);
		Gb_AddToRptValues(pValue, pValues, bUseReserved);
	}
}

void Gb_AddToRptValues(CDvmValue *pData, CValues *pValues,  const CString &strAttrID)
{
	if (pData->m_strID.Right(strAttrID.GetLength()) == strAttrID)
	{
		pValues->AddValue(pData->m_strID, pData->m_strValue);
	}

	if (pData->GetCount() == 0)
	{
		return;
	}

	POS pos = pData->GetHeadPosition();
	CDvmValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pData->GetNext(pos);
		Gb_AddToRptValues(pValue, pValues, strAttrID);
	}
}

void Gb_AddToRptValues(CDvmDataset *pDataset, CValues *pValues,  BOOL bUseReserved)
{
	POS pos = pDataset->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pDataset->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			Gb_AddToRptValues((CDvmData*)p, pValues, bUseReserved);
		}
		else
		{
			Gb_AddToRptValues((CDvmDataset*)p, pValues, bUseReserved);
		}
	}
}

void Gb_AddToRptValues(CDvmData *pData, CValues *pValues,  BOOL bUseReserved)
{
	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		ASSERT (FALSE);
		return;
	}

	if (bUseReserved)
	{
		if (pData->m_dwReserved == 0x0FFFFFFF)
		{
			return;
		}
	}

	pValues->AddValue(pData->m_strID, pData->m_strValue);

	if (pData->GetCount() == 0)
	{
		return;
	}

	POS pos = pData->GetHeadPosition();
	CDvmValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pData->GetNext(pos);
		Gb_AddToRptValues(pValue, pValues, bUseReserved);
	}
}

void Gb_AddToRptValues(CDvmData *pData, CValues *pValues,  const CString &strAttrID)
{
	pValues->AddValue(pData->m_strID, pData->m_strValue);

	if (pData->GetCount() == 0)
	{
		return;
	}

	POS pos = pData->GetHeadPosition();
	CDvmValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pData->GetNext(pos);
		Gb_AddToRptValues(pValue, pValues, strAttrID);
	}
}


void Gb_AddToRptValues(CDataObjValue *pData, CValues *pValues,  BOOL bUseReserved)
{
	if (bUseReserved)
	{
		if (pData->m_dwReserved == 0x0FFFFFFF)
		{
			return;
		}
	}

	pValues->AddValue(pData->m_strID, pData->m_strValue);

	if (pData->GetCount() == 0)
	{
		return;
	}

	POS pos = pData->GetHeadPosition();
	CDataObjValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)pData->GetNext(pos);
		Gb_AddToRptValues(pValue, pValues, bUseReserved);
	}
}


void Gb_AddToRptValues(CDataSet *pDataset, CValues *pValues,  BOOL bUseReserved)
{
	POS pos = pDataset->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pDataset->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATAOBJ)
		{
			Gb_AddToRptValues((CDataObj*)p, pValues, bUseReserved);
		}
		else
		{
			Gb_AddToRptValues((CDataSet*)p, pValues, bUseReserved);
		}
	}
}

void Gb_AddToRptValues(CDataObj *pData, CValues *pValues,  BOOL bUseReserved)
{
	if (pData->GetClassID() != GBCLASSID_DATAOBJ)
	{
		ASSERT (FALSE);
		return;
	}

	if (bUseReserved)
	{
		if (pData->m_dwReserved == 0x0FFFFFFF)
		{
			return;
		}
	}

	pValues->AddValue(pData->m_strID, pData->m_strValue);

	if (pData->GetCount() == 0)
	{
		return;
	}

	POS pos = pData->GetHeadPosition();
	CDataObjValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)pData->GetNext(pos);
		Gb_AddToRptValues(pValue, pValues, bUseReserved);
	}
}

void Gb_AddToRptDataset(CDataSet *pDataset, CDvmDataset *pRptDataset,  BOOL bUseReserved)
{
	POS pos = pDataset->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pDataset->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATAOBJ)
		{
			Gb_AddToRptDataset((CDataObj*)p, pRptDataset, bUseReserved);
		}
		else
		{
			Gb_AddToRptDataset((CDataSet*)p, pRptDataset, bUseReserved);
		}
	}
}

void Gb_AddToRptDataset(CDataObj *pData, CDvmDataset *pRptDataset,  BOOL bUseReserved)
{
	if (pData->GetClassID() != GBCLASSID_DATAOBJ)
	{
		ASSERT (FALSE);
		return;
	}

	if (bUseReserved)
	{
		if (pData->m_dwReserved == 0x0FFFFFFF)
		{
			return;
		}
	}

	CDvmData *pNewData = pRptDataset->AddNewData(pData->m_strName, pData->m_strID, pData->m_strDataType, pData->m_strValue);
	//pNewData->m_strFormat = pData->m_strf

	if (pData->GetCount() == 0)
	{
		return;
	}

	POS pos = pData->GetHeadPosition();
	CDataObjValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)pData->GetNext(pos);
		Gb_AddToRptDataset(pValue, pNewData, bUseReserved);
	}
}

void Gb_AddToRptDataset(CDataObjValue *pData, CDvmData *pRptData,  BOOL bUseReserved)
{
	if (bUseReserved)
	{
		if (pData->m_dwReserved == 0x0FFFFFFF)
		{
			return;
		}
	}

	CDvmValue *pRptValue = pRptData->AddValue(pData->m_strName, pData->m_strID, pData->m_strDataTypeID, pData->m_strValue);

	if (pData->GetCount() == 0)
	{
		return;
	}

	POS pos = pData->GetHeadPosition();
	CDataObjValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)pData->GetNext(pos);
		Gb_AddToRptDataset(pValue, pRptValue, bUseReserved);
	}
}

void Gb_AddToRptDataset(CDataObjValue *pData, CDvmValue *pRptValue,  BOOL bUseReserved)
{
	if (bUseReserved)
	{
		if (pData->m_dwReserved == 0x0FFFFFFF)
		{
			return;
		}
	}

	CDvmValue *pRptValue_Child = pRptValue->AddValue(pData->m_strName, pData->m_strID, pData->m_strDataTypeID, pData->m_strValue);

	if (pData->GetCount() == 0)
	{
		return;
	}

	POS pos = pData->GetHeadPosition();
	CDataObjValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)pData->GetNext(pos);
		Gb_AddToRptDataset(pValue, pRptValue_Child, bUseReserved);
	}
}

BOOL Gb_IsDsvTextWithValue(CExBaseObject *pObj)
{
	CDevice *pDevice = (CDevice*)pObj->GetAncestor(GBCLASSID_DEVICE);

	if (pDevice == NULL)
	{
		return FALSE;
	}
	else
	{
		return (pDevice->m_nDsvTextWithValue == 1);
	}
}

BOOL Gb_IsDsvTextWithUtcTime(CExBaseObject *pObj)
{
	CDevice *pDevice = (CDevice*)pObj->GetAncestor(GBCLASSID_DEVICE);

	if (pDevice == NULL)
	{
		return FALSE;
	}
	else
	{
		return (pDevice->m_nDsvTextWithUtcTime == 1);
	}
}

UINT Gb_GetImgIndex(CExBaseObject* pGbNode)
{
	UINT nClassID = pGbNode->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_GUIDEBOOK:
		nClassID = 0;
		break;
	case GBCLASSID_JOBGUIDE:
		nClassID = 1;
		break;
	case GBCLASSID_DEVICE:
		nClassID = 2;
		break;
	case GBCLASSID_ITEMS:
		nClassID = 3;
		break;
	case GBCLASSID_CPU:
		nClassID = 4;
		break;
	case GBCLASSID_MACROTEST:
		nClassID = 5;
		break;
	case GBCLASSID_MACROCHARITEMS:
		nClassID = 10;
		break;
	case CHARCLASSID_CCHARACTERISTICS:
		nClassID = 11;
		break;
	case GBCLASSID_SAFETY:
		nClassID = 6;
		break;
	case GBCLASSID_COMMCMD:
		nClassID = 7;
		break;
	case GBCLASSID_DEVICE_SYSPARAS:
		nClassID = 8;
		break;
	case GBCLASSID_SYSPARAEDIT:
		nClassID = 8;
		break;
	case GBCLASSID_HDRESREQUEST:
		nClassID = 12;
		break;
	default:
		nClassID = 9;
		break;
	}

	return nClassID;
}

CTestMacrosFile* Gb_GetTestMacroFile(CExBaseObject *pItem)
{
	CTestMacrosFile *pFind = NULL;
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestMacrosFileMngr *pTestMacroFileMngr = CTestMacrosFileMngr::g_pTestMacrosFileMngr;

	pFind = pTestMacroFileMngr->FindByFile(pGuideBook->m_strTestMacroFileID, pGuideBook->m_strCommCmdConfigFile);
	
	return pFind;
}

CString Gb_GetDllCallFile(CExBaseObject *pItem)
{
	CTestMacrosFile *pMacroFile = Gb_GetTestMacroFile(pItem);

	if (pMacroFile == NULL)
	{
		return _T("");
	}
	else
	{
		return pMacroFile->DllCallFile(TRUE);
	}
}


//2019-12-31  lijunqing
long Gb_GetDvmIndexFromPath(const CString &strDataPath)
{
	if (strDataPath.GetLength() == 0)
	{
		return -1;
	}

	TCHAR ch = strDataPath.GetAt(0);

	if ( ! ('0' <= ch && ch <= '9') )
	{
		return -1;
	}

	long nPos = strDataPath.Find('$');

	if (nPos < 0)
	{
		return -1;
	}

	CString strDvIndex = strDataPath.Left(nPos);

	if (IsStringNumber(strDvIndex))
	{
		return CString_To_long(strDvIndex);
	}
	else
	{
		return -1;
	}
}

CExBaseObject* Gb_FindVariableByID(CExBaseObject *pGbObj, const CString &strID)
{
	ASSERT (pGbObj != NULL);
	CDevice *pDevice = (CDevice*)pGbObj->GetAncestor(GBCLASSID_DEVICE);
	ASSERT (pDevice != NULL);

	CExBaseObject *pFind = NULL;

	if (Gb_IsGuideBookTemplate(pDevice))
	{
#ifndef _PSX_QT_LINUX_
        pFind = pDevice->m_pGbtDataInterfaces->m_pGbtDatas->FindByID(strID);
#endif
    }
	else
	{
		pFind = pDevice->SelectDataObj(strID);
	}

	return pFind;
}

long Gb_GetDvmIndexByObj(CExBaseObject *pGbObj)
{
	CExBaseObject *pCpus = (CExBaseObject*)pGbObj->GetAncestor(GBCLASSID_CPUS);
	ASSERT (pCpus != NULL);

	if (pCpus == NULL)
	{
		return -1;
	}

	CExBaseList *pDevices = (CExBaseList*)pCpus->GetParent();
	long nDvmIndex = -1;
	
	POS pos = pDevices->GetHeadPosition();
	CExBaseObject* p = NULL;

	while(pos)
	{
		p = pDevices->GetNext(pos);

		if (GBCLASSID_CPUS == p->GetClassID())
		{
			nDvmIndex++;

			if (p == pCpus)
			{
				break;
			}
		}
	}

	return nDvmIndex;
}


CString Gb_GetItemTempFilePath(CGbItemBase* pItem)
{
	CString strTempFilePath = ats_GetBinaryTempFilePath(pItem);
	CString strTempFileName = ats_GetBinaryTempFile(strTempFilePath, pItem);
	return strTempFileName;
}

//2021-2-23  lijunqing  
CString ats_GetBinaryTempFilePath(CGbItemBase* pItem)
{
	CTestControlBaseInterface *pTestControl = tctrl_GetTestControl(pItem);
	CString strTempFilePath;

	if (pTestControl != NULL)
	{
		strTempFilePath = pTestControl->GetItemTempPath();
	}

	return strTempFilePath;
}

//2021-2-23  lijunqing : 
CTestControlBaseInterface* tctrl_GetTestControl(CExBaseObject *pItem)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControlBaseInterface *pTestControl = (CTestControlBaseInterface*)pGuideBook->GetParent();

	return pTestControl;
}

CString Gb_GetSummaryRslt(CGbItemBase *pItem)
{
	CString strRet = _T("合格");
	long nState = pItem->GetState();

	if (nState == TEST_STATE_INLEGIBLE)
	{
		strRet = _T("不合格");
		return strRet;
	}

	POS pos = pItem->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pItem->GetNext(pos);

		if (Gb_IsGbItemClassID(pObj->GetClassID()) || pObj->GetClassID() == GBCLASSID_ITEMS)
		{
			CGbItemBase *pGbItem = (CGbItemBase *)pObj;
			strRet = Gb_GetSummaryRslt(pGbItem);

			if (strRet == _T("不合格"))
			{
				return strRet;
			}
		}
	}

	return strRet;
}
CItems* Gb_GetFirstParentItems(CBaseObject *pObj, BOOL bType)
{
	UINT nClassID = 0;
	CBaseObject *pParent = NULL;
	CItems *pItem = NULL;

	if (pObj == NULL)
	{
		return NULL;
	}

	pParent = pObj;

	while (pParent != NULL)
	{
		nClassID = pParent->GetClassID();

		if (nClassID == GBCLASSID_DEVICE)
		{
			break;
		}

		if (GBCLASSID_ITEMS == nClassID)
		{
			pItem = (CItems*)pParent;

			if (bType)
			{
				if (!pItem->IsTypeRootNode())
				{
					pParent = pParent->GetParent();
					pItem = NULL;
					continue;
				}
			}

			break;
		}
		else
		{
			pParent = pParent->GetParent();
		}
	}

	return pItem;
}

//形参为当前的RootType节点
CItems* Gb_GetNextRootTypeItems(CExBaseObject *pCurrItems)
{
	UINT nClassID = 0;
	CExBaseList *pParent = (CExBaseList *)pCurrItems->GetParent();
	CItems *pFind = NULL;
	CExBaseObject *pObj = NULL;

	if (pCurrItems == NULL)
	{
		return NULL;
	}

	//先查找当前RootType节点的后续兄弟节点。
	POS pos = pParent->Find(pCurrItems);
	pParent->GetNext(pos);

	while (pos != NULL)
	{
		pObj = pParent->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pItems = (CItems *)pObj;

		if (pItems->IsTypeRootNode())
		{
			return pItems;
		}

		pFind = pItems->FindFirstRootTypeItem();

		if (pFind != NULL)
		{
			return pFind;
		}
	}

	if (pParent->GetClassID() == GBCLASSID_DEVICE)
	{
		return NULL;
	}

	//如果没找到，再往父节点查找
	pParent = (CExBaseList *)pParent->GetParent();

	while (pParent != NULL)
	{
		nClassID = pParent->GetClassID();

		if (nClassID == GBCLASSID_DEVICE)
		{
			break;
		}

		if (GBCLASSID_ITEMS == nClassID)
		{
			pFind = Gb_GetNextRootTypeItems(pParent);

			if (pFind != NULL)
			{
				break;
			}
			else
			{
				pParent = (CExBaseList *)pParent->GetParent();
			}
		}
		else
		{
			pParent = (CExBaseList *)pParent->GetParent();
		}
	}

	return pFind;
}

void Gb_GetAllItemsByID(CGbItemBase *pItem, const CString &strID, CExBaseList &oItemList, UINT nItemClassID)
{
    if(pItem == NULL)
        return;

	POS pos = pItem->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pItem->GetNext(pos);
		nClassID = p->GetClassID();

		if ( nClassID == nItemClassID )
		{
			if (p->m_strID == strID)
			{
				oItemList.AddTail(p);
			}	
		}

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pItems = (CItems *)p;
			Gb_GetAllItemsByID(pItems, strID, oItemList, nItemClassID);
		}
	}
}

long Gb_GetChildItemsCount(CGbItemBase *pItem)
{
	long nCount = 0;

	POS pos = pItem->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pItem->GetNext(pos);
		nClassID = p->GetClassID();

		if ( nClassID == GBCLASSID_SAFETY || nClassID == GBCLASSID_MACROTEST
			|| nClassID == GBCLASSID_COMMCMD || nClassID == GBCLASSID_SYSPARAEDIT
			|| nClassID == GBCLASSID_MACROCHARITEMS || nClassID == GBCLASSID_ITEMS)
		{
			nCount++;	
		}
	}

	return nCount;
}

long Gb_GetItem_IDHas(const CString &strIDHas, CGbItemBase *pParentItem, CExBaseList *pDestList)
{
	POS pos = pParentItem->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pParentItem->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pItems = (CItems *)pObj;
			Gb_GetItem_IDHas(strIDHas, pItems, pDestList);
		}

		if ( !Gb_IsGbItemClassID(nClassID))
		{
			continue;
		}

		CGbItemBase *pGbItem = (CGbItemBase *)pObj;
		
		if (pGbItem->m_strID.Find(strIDHas) >= 0)
		{
			pDestList->AddTail(pGbItem);
		}
	}

	return pDestList->GetCount();
}

//处理SV接收压板一致性测试
//形参1：SV压板数据集；形参2：父项目列表；形参3：过滤的项目类型
void Gb_GenSvMatchItems(CExBaseList *pDataSet, CExBaseList *pItems, UINT nClassID)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	//遍历项目列表
	while (pos != NULL)
	{
		pObj = (CExBaseObject *)pItems->GetNext(pos);

		//过滤掉不对应的测试项目
		if (pObj->GetClassID() != nClassID)
		{
			continue;
		}

		//目前只考虑电气量项目
		if (nClassID == GBCLASSID_MACROTEST)
		{
			CMacroTest *pMacroTest = (CMacroTest *)pObj;
			pMacroTest->GenSvMatchItems(pDataSet);
		}
	}
}

void Gb_AtsInitReport_Name(CReport *pReport)
{
	if (pReport == NULL)
	{
		return;
	}

	if (pReport->m_pValues == NULL)
	{
		return;
	}

	if (pReport->m_pValues->GetCount() == 0)
	{
		return;
	}

	CReports *pReports = (CReports *)pReport->GetParent();
	CGbItemBase *pItem = (CGbItemBase *)pReports->GetParent();

	if (pItem->GetClassID() != GBCLASSID_MACROTEST)
	{
		//暂时只考虑电气量项目
		return;
	}

	CMacroTest *pMacroTest = (CMacroTest *)pItem;
	CGuideBook *pGuideBook = (CGuideBook *)pMacroTest->GetAncestor(GBCLASSID_GUIDEBOOK);
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();

	if (pMacroTestPara == NULL)
	{
		return;
	}

	CString strMacroID = pMacroTestPara->GetMacroID();

	if (pGuideBook->m_pTestMacros == NULL)
	{
		return;
	}

	CTestMacro *pTestMacro = (CTestMacro *)pGuideBook->m_pTestMacros->FindByID(strMacroID);

	if (pTestMacro == NULL)
	{
		return;
	}

	POS pos = pReport->m_pValues->GetHeadPosition();

	while (pos != NULL)
	{
		CValue *pValue = (CValue *)pReport->m_pValues->GetNext(pos);

		if (pValue->m_strID == g_strTestResultJudgeKey)
		{
			pValue->m_strName = g_strTestResultJudgeNameKey;
			continue;
		}

		if (pValue->m_strID == g_strTestResultDescriptKey)
		{
			pValue->m_strName = g_strTestResultDescriptNameKey;
			continue;
		}

		if (pValue->m_strID == g_strTestResultTimeKey)
		{
			pValue->m_strName = g_strTestResultTimeNameKey;
			continue;
		}

		CShortData *pData = pTestMacro->FindDataByID(pValue->m_strID);

		if (pData != NULL)
		{
			if (pData->m_strName.IsEmpty())
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TestMacro.xml中，参数【%s】未配置name属性！"), pData->m_strID.GetString());
			}
			else
			{
				pValue->m_strName = pTestMacro->GetParaNamePath(pData);//pData->m_strName;
			}
		}
		else
		{
			//找不到，考虑从结果判断表达式中查找。
			CXExprNode *pNode = (CXExprNode *)pItem->GetRsltExpr();

			//结果判断里面，只有名称
			if (pNode != NULL)
			{
				Gb_AtsInitReport_Name(pValue, pNode);
			}
		}
	}
}

void Gb_AtsInitReport_Name(CValue *pValue, CXExprNode *pNode)
{
	if (pNode == NULL || pValue == NULL)
	{
		return;
	}

	CString strName;
	pNode->GetValueName(pValue->m_strID, strName);

	if ( !strName.IsEmpty())
	{
		pValue->m_strName = strName;
	}
}
