#include "StdAfx.h"
#include "RptBkmkBatchAddTool.h"
#include "..\..\..\..\..\Module\XFileMngrBase\DlgXFileMngr.h"
#include "..\..\..\XLanguageResourceAts.h"


CRptBkmkBatchAddTool::CRptBkmkBatchAddTool(void)
{
	CRptBkmkBatchAddXmlRWKeys::Create();
	m_oRptBatchConfig.InitAfterRead();

	m_nRows = 0;
	m_nCols = 0;
	m_nSelectionRows = 0;
	m_nSelectionCols = 0;
}

CRptBkmkBatchAddTool::~CRptBkmkBatchAddTool(void)
{
	CRptBkmkBatchAddXmlRWKeys::Release();
}

BOOL CRptBkmkBatchAddTool::Init(CExBaseObject *pItem, CRptEditInterface* pRptEdit)
{
	if (!pRptEdit->rpt_GetRptBkmkBatchRowsCols( m_nSelectionRows, m_nSelectionCols))
	{
		return FALSE;
	}

	SetRowsCols(m_nSelectionRows, m_nSelectionCols);
	m_pItems = rpt_GetItems(pItem);
	InitItemMaps();

	CMacroTest *pMacroTest = GetMacroTest();

	if (pMacroTest != NULL)
	{
		m_nRepeatCount = pMacroTest->m_nRepeatTimes;
	}

	return FALSE;
}

void CRptBkmkBatchAddTool::GetBatchCellList(CExBaseList &oListBatchCell, CRptEditInterface* pRptEdit)
{
	if (m_oRptBatchConfig.IsRowDataColItemMode())
	{
		GetBatchCellList_ROWDATA_COLITEM(oListBatchCell, pRptEdit);
	}
	else if (m_oRptBatchConfig.IsRowItemColDataMode())
	{
		GetBatchCellList_ROWITEM_COLDATA(oListBatchCell, pRptEdit);
	}
	else if (m_oRptBatchConfig.IsRowRepeatColDataItemRowMode())
	{
		GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(oListBatchCell, pRptEdit);
	}
}

void CRptBkmkBatchAddTool::GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell, CRptEditInterface* pRptEdit)
{
	CRptBatchItemMaps *pItemMaps = m_oRptBatchConfig.GetRptBatchItemMaps();
	CRptBatchDataMaps *pDataMaps = m_oRptBatchConfig.GetRptBatchDataMaps();
	ASSERT(pItemMaps != NULL && pDataMaps != NULL);
	pRptEdit->GetBatchCellList_ROWITEM_COLDATA(oListBatchCell,pItemMaps,pDataMaps,m_nCols);
}

void CRptBkmkBatchAddTool::GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell, CRptEditInterface* pRptEdit)
{
	CRptBatchItemMaps *pItemMaps = m_oRptBatchConfig.GetRptBatchItemMaps();
	CRptBatchDataMaps *pDataMaps = m_oRptBatchConfig.GetRptBatchDataMaps();
	ASSERT(pItemMaps != NULL && pDataMaps != NULL);
	pRptEdit->GetBatchCellList_ROWDATA_COLITEM(oListBatchCell,pItemMaps, pDataMaps, m_nRows);
}

void CRptBkmkBatchAddTool::GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell, CRptEditInterface* pRptEdit)
{
	CRptBatchItemMaps *pItemMaps = m_oRptBatchConfig.GetRptBatchItemMaps();
	CRptBatchDataMaps *pDataMaps = m_oRptBatchConfig.GetRptBatchDataMaps();
	ASSERT(pItemMaps != NULL && pDataMaps != NULL);
	pRptEdit->GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(oListBatchCell,pItemMaps, pDataMaps, m_nRepeatCount, m_nCols);
}

BOOL CRptBkmkBatchAddTool::OpenRptBatchConfigFile(CWnd *pParent)
{
	CXFileMngr oFileMngrBase;
	CString strPath;
	strPath = wzd_GetRptBatchFilePath();

	oFileMngrBase.SetRootPath(strPath);
	oFileMngrBase.m_strName.Format(_T("%s管理"), g_strRptBatchFileName);
	oFileMngrBase.m_strID = strPath;
	oFileMngrBase.SearchFiles(oFileMngrBase.m_strName, g_strRptBatchFilePostFix, strPath);

	CDlgXFileMngr dlg(0, g_strRptBatchFilePostFix, g_strRptBatchFileName, &oFileMngrBase, OPEN_FILE_MODE, pParent);

	if(dlg.DoModal() == IDOK)
	{
		m_strRptBatchFile = dlg.GetFileName();
		m_oRptBatchConfig.OpenXmlFile(m_strRptBatchFile, CRptBkmkBatchAddXmlRWKeys::CRptBatchConfigKey(), CRptBkmkBatchAddXmlRWKeys::g_pXmlKeys);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL CRptBkmkBatchAddTool::SaveRptBatchConfigFile(CWnd *pParent)
{
	CXFileMngr oFileMngrBase;
	CString strPath;
	strPath = wzd_GetRptBatchFilePath();

	oFileMngrBase.SetRootPath(strPath);
	oFileMngrBase.m_strName.Format(_T("%s管理"), g_strRptBatchFileName);
	oFileMngrBase.m_strID = strPath;
	oFileMngrBase.SearchFiles(g_strRptBatchFileName, g_strRptBatchFilePostFix, strPath);

	CDlgXFileMngr dlg(0, g_strRptBatchFilePostFix, g_strRptBatchFileName, &oFileMngrBase, SAVE_FILE_MODE, pParent);

	if(dlg.DoModal() == IDOK)
	{
		m_strRptBatchFile = dlg.GetFileName();
		m_oRptBatchConfig.SaveXmlFile(m_strRptBatchFile, CRptBkmkBatchAddXmlRWKeys::g_pXmlKeys);
		return TRUE;
	}

	return FALSE;
}


BOOL CRptBkmkBatchAddTool::SetMode(UINT nMode)
{
	if (m_oRptBatchConfig.GetMode() == nMode)
	{
		return FALSE;
	}

	m_oRptBatchConfig.SetMode(nMode);

	if (m_oRptBatchConfig.IsRowItemColDataMode())
	{
		m_nRows = m_nSelectionRows;
		m_nCols = m_nSelectionCols;
	}
	else if (m_oRptBatchConfig.IsRowDataColItemMode())
	{
		m_nRows = m_nSelectionRows;
		m_nCols = m_nSelectionCols;
	}
	else if (m_oRptBatchConfig.IsRowRepeatColDataItemRowMode())
	{
		m_nRows = m_nSelectionRows / m_nRepeatCount;
		m_nCols = m_nSelectionCols;
	}

	SetRowsCols(m_nRows, m_nCols);

	InitItemMaps();

	return TRUE;
}

CMacroTest* CRptBkmkBatchAddTool::GetMacroTest()
{
	CMacroTest *pMacroTest = NULL;
	CExBaseObject *p = NULL;
	POS pos = m_pItems->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CExBaseObject *)m_pItems->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_MACROTEST)
		{
			pMacroTest = (CMacroTest *)p;
			break;
		}
	}

	return pMacroTest;
}

void CRptBkmkBatchAddTool::GetAllMacroTest(CExBaseList *pList)	
{
	rpt_GetAllMacroTestItems(m_pItems, pList);	
}

void CRptBkmkBatchAddTool::SetRowsCols(long nRows, long nCols)
{
	CRptBatchDataMaps *pDataMaps = m_oRptBatchConfig.GetRptBatchDataMaps();
	CRptBatchItemMaps *pItemMaps = m_oRptBatchConfig.GetRptBatchItemMaps();

	m_nRows = nRows;
	m_nCols = nCols;
	pDataMaps->DeleteAll();
	pItemMaps->DeleteAll();

	if (m_oRptBatchConfig.IsRowDataColItemMode())
	{
		pDataMaps->AddChildren(RBACLASSID_CRPTBATCHDATAMAP, m_nRows);
		pItemMaps->AddChildren(RBACLASSID_CRPTBATCHITEMMAP, m_nCols);
	}
	else if (m_oRptBatchConfig.IsRowItemColDataMode())
	{
		pDataMaps->AddChildren(RBACLASSID_CRPTBATCHDATAMAP, m_nCols);
		pItemMaps->AddChildren(RBACLASSID_CRPTBATCHITEMMAP, m_nRows);
	}	
	else if (m_oRptBatchConfig.IsRowRepeatColDataItemRowMode())
	{
		pDataMaps->AddChildren(RBACLASSID_CRPTBATCHDATAMAP, m_nCols);
		pItemMaps->AddChildren(RBACLASSID_CRPTBATCHITEMMAP, m_nRows);
	}
}

void CRptBkmkBatchAddTool::InitItemMaps()
{
	CRptBatchItemMaps *pItemMaps = m_oRptBatchConfig.GetRptBatchItemMaps();
	
	CExBaseObject *pItem = NULL;
	POS pos = m_pItems->GetHeadPosition();
	long nIndex = 0;
	CRptBatchItemMap *pItemMap = NULL;

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)m_pItems->GetNext(pos);

		if (pItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			pItemMap = (CRptBatchItemMap *)pItemMaps->GetAtIndex(nIndex);

			if (pItemMap == NULL)
			{
				break;
			}

			pItemMap->m_strName = pItem->m_strName;
			pItemMap->m_strID = pItem->m_strID;
			pItemMap->m_nItemIndex = nIndex;
			pItemMap->m_nMapIndex = nIndex;
			pItemMap->m_pItemRef = pItem;
			nIndex++;
		}
	}
}

void CRptBkmkBatchAddToolYc::InitItemMaps()
{
	rpt_GetAllMacroTestItemsEx(m_pItems, &m_listItemsRef);
	InitItemMapsEx(&m_listItemsRef);
}

void CRptBkmkBatchAddToolYc::InitItemMapsEx(CExBaseList *pList)
{
	CRptBatchItemMaps *pItemMaps = m_oRptBatchConfig.GetRptBatchItemMaps();

	CExBaseObject *pItem = NULL;
	POS pos = pList->GetHeadPosition();
	long nIndex = 0;
	CRptBatchItemMap *pItemMap = NULL;

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)pList->GetNext(pos);

		//if (pItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			pItemMap = (CRptBatchItemMap *)pItemMaps->GetAtIndex(nIndex);

			if (pItemMap == NULL)
			{
				break;
			}

			pItemMap->m_strName = pItem->m_strName;
			pItemMap->m_strID = pItem->m_strID;
			pItemMap->m_nItemIndex = nIndex;
			pItemMap->m_nMapIndex = nIndex;
			pItemMap->m_pItemRef = pItem;
			nIndex++;
		}
	}
}
void CRptBkmkBatchAddTool::InitDataMaps()
{
	m_oRptBatchConfig.ClearMaps();
}

void CRptBkmkBatchAddTool::InitDataMaps(CExBaseObject *pData, const CString &strPrecision, const CString &strAttr, const CString &strDataProcess)
{
	CRptBatchDataMaps *pDataMaps = m_oRptBatchConfig.GetRptBatchDataMaps();
	POS pos = pDataMaps->GetHeadPosition();
	CRptBatchDataMap *pDataMap = NULL;
	long nIndex = 0;
	long nRepeatCount = 0;
	CRptBatchItemMaps *pItemMaps = m_oRptBatchConfig.GetRptBatchItemMaps();
	CMacroTest *pMacroTest = (CMacroTest*)pItemMaps->GetFirstMapItem();

	if (pMacroTest == NULL)
	{
		return;
	}

	nRepeatCount = pMacroTest->m_nRepeatTimes;

	if (nRepeatCount > 1)
	{
		nRepeatCount++;
	}
	else
	{
		return;
	}

	while (pos != NULL)
	{
		pDataMap = (CRptBatchDataMap*)pDataMaps->GetNext(pos);
		pDataMap->m_strName = pData->m_strName;
		pDataMap->m_strID = pData->m_strID;
		pDataMap->m_strPrecision = strPrecision;
		pDataMap->m_nRepeatIndex = nIndex;
		pDataMap->m_strDataAttr = strAttr;
		pDataMap->m_nMapIndex = nIndex;
		pDataMap->m_pDataRef = pData;
		pDataMap->m_strDataProcess = strDataProcess;
		nIndex++;

		if (nIndex >= nRepeatCount)
		{
			break;
		}
	}
}


CExBaseList* rpt_GetItems(CExBaseObject *pItem)
{
	UINT nClassID = pItem->GetClassID();
	CExBaseList *pItems = (CExBaseList*)pItem;

	if (Gb_IsGbItemClassID(nClassID) )
	{
		pItems = (CExBaseList *)pItem->GetParent();
	}

	return pItems;
}

void rpt_GetAllMacroTestItems(CExBaseList *pItems, CExBaseList *pListMacroTest)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pItem = NULL;

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)pItems->GetNext(pos);

		if (pItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			pListMacroTest->AddTail(pItem);
		}
	}
}

void rpt_GetAllMacroTestItemsEx(CExBaseList *pListSrc, CExBaseList *pListDst)
{
	POS pos = pListSrc->GetHeadPosition();
	CExBaseObject *pItem = NULL;

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)pListSrc->GetNext(pos);
		UINT nClassID = pItem->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			rpt_GetAllMacroTestItemsEx((CExBaseList*)pItem, pListDst);
			continue;
		}

		if (pItem->GetClassID() != GBCLASSID_MACROTEST)
		{
			continue;
		}

		CMacroTest *pMacroTest = (CMacroTest*)pItem;
		CExBaseList *pSubItems = pMacroTest->GetSubGbItems();

		if (pSubItems->GetCount() != 1)
		{
			continue;
		}

		CExBaseObject *pSubItem = (CExBaseObject *)pSubItems->GetHead();

		if (pSubItem->GetClassID() != GBCLASSID_COMMCMD)
		{
			continue;
		}

		CCommCmd *pCmd = (CCommCmd *)pSubItem;

		if (pCmd->m_strCommCmdID.Find(g_strDataSetIDKey[DSID_dsAin]) < 0)
		{
			continue;
		}

		pListDst->AddTail(pMacroTest);
	}
}

CRptBkmkBatchAddToolYc::CRptBkmkBatchAddToolYc()
{

}

CRptBkmkBatchAddToolYc::~CRptBkmkBatchAddToolYc()
{
	m_listItemsRef.RemoveAll();
};

void CRptBkmkBatchAddToolYc::GetAllMacroTest(CExBaseList *pListDst)
{
	pListDst->AppendEx(m_listItemsRef, FALSE);
	//GetAllMacroTest(pListDst, m_pItems);
}

 void CRptBkmkBatchAddToolYc::GetAllCommCmd(CExBaseList *pList)
 {
	POS pos = m_listItemsRef.GetHeadPosition();
	CMacroTest *pMacroTest = NULL;

	while (pos != NULL)
	{
		pMacroTest = (CMacroTest *)m_listItemsRef.GetNext(pos);
		CExBaseList *pSubItems = pMacroTest->GetSubGbItems();
		CExBaseObject *pSubItem = (CExBaseObject *)pSubItems->GetHead();
		pList->AddTail(pSubItem);
	}
 }


CMacroTest* CRptBkmkBatchAddToolYc::GetMacroTest()
{
	CMacroTest *pMacroTest = NULL;
	CExBaseObject *p = NULL;
	POS pos = m_listItemsRef.GetHeadPosition();

	if (pos != NULL)
	{
		pMacroTest = (CMacroTest *)m_pItems->GetNext(pos);
	}

	return pMacroTest;
}

CCommCmd* CRptBkmkBatchAddToolYc::GetCommCmd()
{
	CMacroTest *pMacroTest = GetMacroTest();
	ASSERT (pMacroTest != NULL);

	if (pMacroTest == NULL)
	{
		return NULL;
	}

	CExBaseList *pSubItems = pMacroTest->GetSubGbItems();

	if (pSubItems->GetCount() != 1)
	{
		return NULL;
	}

	CExBaseObject *pSubItem = (CExBaseObject *)pSubItems->GetHead();

	if (pSubItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		return NULL;
	}

	CCommCmd *pCCommCmd = (CCommCmd *)pSubItem;

	if (pCCommCmd->m_strCommCmdID.Find(g_strDataSetIDKey[DSID_dsAin]) < 0)
	{
		return NULL;
	}

	return pCCommCmd;
}


void CRptBkmkBatchAddToolYc::InitDataMaps(CExBaseObject *pData, const CString &strPrecision, const CString &strAttr, const CString &strDataProcess)
{
	CRptBatchDataMaps *pDataMaps = m_oRptBatchConfig.GetRptBatchDataMaps();
	POS pos = pDataMaps->GetHeadPosition();
	CRptBatchDataMap *pDataMap = NULL;
	long nIndex = 0;
	long nRepeatCount = 0;
	CRptBatchItemMaps *pItemMaps = m_oRptBatchConfig.GetRptBatchItemMaps();
	CExBaseObject *pMapItem = pItemMaps->GetFirstMapItem();

	if (pMapItem == NULL)
	{
		return;
	}

	if (pMapItem->GetClassID() == GBCLASSID_MACROTEST)
	{
		CMacroTest *pMacroTest = (CMacroTest*)pMapItem;
		nRepeatCount = pMacroTest->m_nRepeatTimes;
	}
	else if (pMapItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		CCommCmd *pCommCmd = (CCommCmd*)pMapItem;
		CCmd *pCmd = pCommCmd->GetCmd();
		nRepeatCount = pCmd->m_nRepeatTimes;
	}

	if (nRepeatCount > 1)
	{
		nRepeatCount++;
	}
	else
	{
		return;
	}

	while (pos != NULL)
	{
		pDataMap = (CRptBatchDataMap*)pDataMaps->GetNext(pos);
		pDataMap->m_strName = pData->m_strName;
		pDataMap->m_strID = pData->m_strID;
		pDataMap->m_strPrecision = strPrecision;
		pDataMap->m_nRepeatIndex = nIndex;
		pDataMap->m_strDataAttr = strAttr;
		pDataMap->m_nMapIndex = nIndex;
		pDataMap->m_pDataRef = pData;
		pDataMap->m_strDataProcess = strDataProcess;
		nIndex++;

		if (nIndex >= nRepeatCount)
		{
			break;
		}
	}
}
