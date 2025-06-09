#include "StdAfx.h"
#include "TestItemViewGrid.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CTestItemViewGrid, CListCtrl)

#define TESTITEM_COL_INDEX  0
#define TESTITEM_COL_TYPE   1
#define TESTITEM_COL_STATE  2
#define TESTITEM_COL_NAME   3
#define TESTITEM_COL_REPORT 4

CTestItemViewGrid::CTestItemViewGrid(void)
{
	
}

CTestItemViewGrid::~CTestItemViewGrid(void)
{
	m_listInlegibleItem.RemoveAll();
}



BEGIN_MESSAGE_MAP(CTestItemViewGrid, CListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CTestItemViewGrid::OnNMDblclk)
END_MESSAGE_MAP()

void CTestItemViewGrid::CreateGrid(CWnd *pParent, CRect rcWnd, UINT nID, CWnd *pMainFrame)
{
	m_pMainFrame = pMainFrame;
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS;
	BOOL bTrue = Create(dwStyle, rcWnd, pParent, nID);

	ModifyStyle(LVS_SORTASCENDING | LVS_SORTDESCENDING, NULL);
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	InsertColumn(TESTITEM_COL_INDEX,g_sLangTxt_Index/*_T("编号")*/,LVCFMT_LEFT,60);
	InsertColumn(TESTITEM_COL_TYPE,g_sLangTxt_ItemType/*_T("项目类型")*/,LVCFMT_LEFT,100);
	InsertColumn(TESTITEM_COL_STATE,g_sLangTxt_Status/*_T("状态")*/,LVCFMT_LEFT,80);
	InsertColumn(TESTITEM_COL_NAME,g_sLangTxt_ItemPath/*_T("项目路径")*/,LVCFMT_LEFT,400);
	InsertColumn(TESTITEM_COL_REPORT,g_sLangTxt_ReportInf/*_T("报告信息")*/,LVCFMT_LEFT,400);
}

void CTestItemViewGrid::ShowItems(CExBaseList *pList)
{
	m_listInlegibleItem.RemoveAll();
	m_listInlegibleItem.Append(pList);
	DeleteAllItems();

	long nIndex = 0;
	POS pos = m_listInlegibleItem.GetHeadPosition();
	CExBaseObject *p = NULL;
	
	while (pos != NULL)
	{
		p = (CExBaseObject *)m_listInlegibleItem.GetNext(pos);
		ShowItem(p, nIndex);
		nIndex++;
	}
}

BOOL CTestItemViewGrid::AddItem(CExBaseObject *pItem)
{
	POS pos = m_listInlegibleItem.Find(pItem);

	if (pos != NULL)
	{
		return FALSE;
	}

	m_listInlegibleItem.AddTail(pItem);
	long nCount = m_listInlegibleItem.GetCount() - 1;
	ShowItem(pItem, nCount);

	return TRUE;
}

BOOL CTestItemViewGrid::RemoveItem(CExBaseObject *pItem)
{
	POS pos = m_listInlegibleItem.Find(pItem);

	if (pos == NULL)
	{
		return FALSE;
	}

	m_listInlegibleItem.RemoveAt(pos);
	long nIndex = 0;
	long nCount = GetItemCount();
	long nIndexFind = -1;
	CString strText;

	//删除Item
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if ((CExBaseObject*)GetItemData(nIndex) == pItem)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	if (nIndexFind == -1)
	{
		return FALSE;
	}

	DeleteItem(nIndexFind);

	//更新编号
	for (nIndex=nIndexFind; nIndex<nCount-1; nIndex++)
	{
		strText.Format(_T("%d"), nIndex+1);
		SetItemText(nIndex, 0, strText);
	}

	return TRUE;
}

void CTestItemViewGrid::ShowItem(CExBaseObject *pItem, long nIndex)
{
	CString strText;
	strText.Format(_T("%d"), nIndex+1);
	InsertItem(nIndex, strText);

	strText = pItem->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
	SetItemText(nIndex, TESTITEM_COL_NAME, strText);

	UINT nSate = ((CGbItemBase*)pItem)->GetStateEx();

	if (nSate == TEST_STATE_ELIGIBLEEX)
	{
		strText = g_sLangTxt_RetestQualified/*_T("重测合格")*/;
	}
	else
	{
		strText = g_sLangTxt_Unqualified/*_T("不合格")*/;
	}

	SetItemText(nIndex, TESTITEM_COL_STATE, strText);


	UINT nClassID = pItem->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_MACROTEST:
		UpdateItem((CMacroTest*)pItem, nIndex);
		break;

	case GBCLASSID_COMMCMD:
		UpdateItem((CCommCmd*)pItem, nIndex);
		break;

	case GBCLASSID_SAFETY:
		UpdateItem((CSafety*)pItem, nIndex);
		break;
	}

	SetItemData(nIndex, (DWORD)pItem);
}

void CTestItemViewGrid::UpdateItem(CMacroTest *pMacroTest, long nIndex)
{
	CString strText;

	SetItemText(nIndex, TESTITEM_COL_TYPE, g_sLangTxt_ElectrQuanPrjc/*_T("电气量项目")*/);
	CTestMacro* pTestMacro = Gb_GetMacroPtr(pMacroTest);

	if (pTestMacro == NULL)
	{
		return;
	}

	CShortDatas *pResults = pTestMacro->GetResults();
	CReport *pReport = pMacroTest->GetReport(-1);

	if (pReport == NULL)
	{
		return;
	}

	GetReportText(pReport, pResults, strText);
	SetItemText(nIndex, TESTITEM_COL_REPORT, strText);
}

void CTestItemViewGrid::UpdateItem(CCommCmd *pCommCmd, long nIndex)
{
	SetItemText(nIndex, TESTITEM_COL_TYPE, g_sLangTxt_ComictnComm/*_T("通讯命令")*/);
}

void CTestItemViewGrid::UpdateItem(CSafety *pSafety, long nIndex)
{
	CString strText;
	SetItemText(nIndex, TESTITEM_COL_TYPE, g_sLangTxt_ArtificialProject/*_T("人工项目")*/);
	CReport *pReport = pSafety->GetReport(-1);

	if (pReport == NULL)
	{
		return;
	}

	GetReportText(pReport, pSafety->GetDatas(), strText);
	SetItemText(nIndex, TESTITEM_COL_REPORT, strText);
}

void CTestItemViewGrid::GetReportText(CReport *pReport, CShortDatas *pDatas, CString &strText)
{
	if (pReport->m_pValues == NULL)
	{
		return;
	}

	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;
	CValue *pValue = NULL;
	strText.Empty();

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);
		pValue = (CValue*)pReport->m_pValues->FindByID(pData->m_strID);

		if (pValue != NULL)
		{
			strText.AppendFormat(_T("%s=%s; "), pData->m_strName, pValue->m_strValue);
		}
	}
}


void CTestItemViewGrid::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	CExBaseObject *pItem = NULL;

	if (pNMItemActivate->iItem >= 0)
	{
		pItem = (CExBaseObject *)GetItemData(pNMItemActivate->iItem);

		m_pMainFrame->PostMessage(WM_SELECT_TESTITEM, (WPARAM)pItem, (LPARAM)pItem);
	}

	*pResult = 0;
}
