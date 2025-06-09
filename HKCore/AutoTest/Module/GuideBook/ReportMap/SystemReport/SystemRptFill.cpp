#include "StdAfx.h"
#include "SystemRptFill.h"
#include "..\..\..\TestControl/TctrlCntrBaseApp.h"
#include "..\..\..\..\..\Module\API\GlobalApi.h"
#include "..\..\..\..\..\Module\API\GloblaDrawFunctions.h"
#include "..\..\..\TCtrlCntrDefine.h"
#include "..\..\..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL g_bSysReportFillShowAllDatas = TRUE;

#define _SYSRPTFILL_USE_COLS  1

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillItem
CSystemRptFillItem::CSystemRptFillItem()
{
	m_pWndTitle = NULL;
	m_pGridRpt = NULL;
	m_pGbItem = NULL;
}

CSystemRptFillItem::~CSystemRptFillItem()
{
	m_pGridRpt->FreeListVCellData();
	m_pGridRpt->DeleteAllItems(FALSE);
	m_pWndTitle->DestroyWindow();
	m_pGridRpt->DestroyWindow();
	delete m_pWndTitle;
	delete m_pGridRpt;
}

long CSystemRptFillItem::GetOffset()
{
	CRect rc1, rc2;
	m_pWndTitle->GetWindowRect(&rc1);
	m_pGridRpt->GetWindowRect(&rc2);

	return rc2.bottom - rc1.top + 5;
}

void CSystemRptFillItem::Offset(long nOffset, CWnd *pParentWnd)
{
	CRect rc1, rc2;
	m_pWndTitle->GetWindowRect(&rc1);
	m_pGridRpt->GetWindowRect(&rc2);

	pParentWnd->ScreenToClient(&rc1);
	pParentWnd->ScreenToClient(&rc2);

	rc1.OffsetRect(0, -nOffset);
	rc2.OffsetRect(0, -nOffset);

#ifdef _use_move_window
	m_pWndTitle->MoveWindow(rc1);
	m_pGridRpt->MoveWindow(rc2);
#else
	m_pWndTitle->SetWindowPos(NULL, rc1.left, rc1.top, rc1.Width(), rc1.Height(), SWP_SHOWWINDOW);
	m_pGridRpt->SetWindowPos(NULL, rc2.left, rc2.top, rc2.Width(), rc2.Height(), SWP_SHOWWINDOW);
#endif

}

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillItems
CSystemRptFillItems::CSystemRptFillItems()
{

}

CSystemRptFillItems::~CSystemRptFillItems()
{

}

void CSystemRptFillItems::AddSystemRptFillItem(CGbItemBase *pGbItem, CStatic *pWndTitle, CExBaseListGrid *pGridRpt)
{
	CSystemRptFillItem *pNew = new CSystemRptFillItem();
	pNew->m_pGridRpt = pGridRpt;
	pNew->m_pWndTitle = pWndTitle;
	pNew->m_pGbItem = pGbItem;
	AddTail(pNew);
}

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid
CSystemRptFillGridBase::CSystemRptFillGridBase()
{
	m_nAdjustBeginCol = 1;
	m_yCurrPos = 0;
}

CSystemRptFillGridBase::~CSystemRptFillGridBase()
{

}

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_ItemsRsltScript
#define SYSRPTGRID_ITEMSEXPR_COL_TESTINDEX  0
#define SYSRPTGRID_ITEMSEXPR_COL_DATAINDEX  1
#define SYSRPTGRID_ITEMSEXPR_COL_ITEMNAME   2
#define SYSRPTGRID_ITEMSEXPR_COL_STANDVAL    3
#define SYSRPTGRID_ITEMSEXPR_COL_DVMVAL       4
#define SYSRPTGRID_ITEMSEXPR_COL_ABSERRCAL  5
#define SYSRPTGRID_ITEMSEXPR_COL_RELERRCAL  6
#define SYSRPTGRID_ITEMSEXPR_COL_ABSERR       7
#define SYSRPTGRID_ITEMSEXPR_COL_RELERR       8
#define SYSRPTGRID_ITEMSEXPR_COL_RSLTJDG     9
#define SYSRPTGRID_ITEMSEXPR_COLS                  10

CSystemRptFillGrid_ItemsRsltScript::CSystemRptFillGrid_ItemsRsltScript()
{

}

CSystemRptFillGrid_ItemsRsltScript::~CSystemRptFillGrid_ItemsRsltScript()
{

}

void CSystemRptFillGrid_ItemsRsltScript::InitGrid()
{
	SetListMode(TRUE);
	//SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(SYSRPTGRID_ITEMSEXPR_COLS);
	SetFixedRowCount(0);
	SetFixedColumnCount(1);

	InitGridTitle();

	ResetScrollBars();
}

void CSystemRptFillGrid_ItemsRsltScript::InitGridTitle()
{
	CString cTempStr[SYSRPTGRID_ITEMSEXPR_COLS]={
		_T("测试次数")
		,_T("序号")
		,_T("测试项目")
		,_T("源输出量")
		,_T("装置测量量")
		,_T("绝对误差")
		,_T("相对误差")
		,_T("绝对误差限")
		,_T("相对误差限")
		,_T("结论")
	};
	int iWidth[SYSRPTGRID_ITEMSEXPR_COLS]={120, 60, 120, 200, 100, 100, 100, 100, 100, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, SYSRPTGRID_ITEMSEXPR_COLS);

	SetRowHeight(0, EXBASEGRID_ROWHEIGHT);
}


void CSystemRptFillGrid_ItemsRsltScript::UpdateDatas()
{
	CTLinkList <_ExBaseCellData> listVCellData;
	BackListCellData(listVCellData);
	ASSERT(m_pDatas != NULL);

	if (m_pDatas == NULL)
	{
		return;
	}

	CExBaseObject *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = m_nRows - m_pDatas->GetCount();

	while (pos != NULL)
	{
		pObj = m_pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	AdjustAllCols();
	ResetScrollBars();
	Invalidate(FALSE);
}


void CSystemRptFillGrid_ItemsRsltScript::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_pDatas = pDatas;

	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = m_nRows;
	int nRows = m_nRows;
	SetRowCount(pDatas->GetCount() + nRows);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);

	for (nRowIndex=nRows; nRowIndex<m_nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, EXBASEGRID_ROWHEIGHT);
	}

	AdjustAllCols(bResetScrollBars);

	if (bResetScrollBars)
	{
		ResetScrollBars();
	}

	Invalidate(FALSE);
}

void CSystemRptFillGrid_ItemsRsltScript::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CItemsRsltExpr *pItemsRsltExpr = (CItemsRsltExpr*)pData;
	CString strText;
	BOOL bUseRelErr = TRUE;

	if (math_IsEqual(pItemsRsltExpr->m_dRelError, 0))
	{
		bUseRelErr = FALSE;
	}

	strText.Format(_T("%d"), nRow);
	Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_DATAINDEX,     strText);
	Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_ITEMNAME,     &pItemsRsltExpr->m_strName);

	strText.Format(_T("%f"), pItemsRsltExpr->m_dStandValue);
	Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_STANDVAL,     strText);

	strText.Format(_T("%f"), pItemsRsltExpr->m_dDvmValue);
	Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_DVMVAL,     strText);

	strText.Format(_T("%f"), pItemsRsltExpr->m_dAbsErrorCal);
	Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_ABSERRCAL,     strText);
	strText.Format(_T("%f"), pItemsRsltExpr->m_dAbsError);
	Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_ABSERR,     strText);

	if (bUseRelErr)
	{
		strText.Format(_T("%f"), pItemsRsltExpr->m_dRelErrorCal);
		Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_RELERRCAL,     strText);
		strText.Format(_T("%f"), pItemsRsltExpr->m_dRelError);
		Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_RELERR,     strText);
	}
	else
	{
		strText = _T("---");
		Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_RELERRCAL,     strText);
		Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_RELERR,     strText);
	}

	if (pItemsRsltExpr->m_dwRsltJdg == 1)
	{
		Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_RSLTJDG,     g_sLangTxt_Qualified);
	}
	else
	{
		Show_StaticString(pItemsRsltExpr, nRow, SYSRPTGRID_ITEMSEXPR_COL_RSLTJDG,     g_sLangTxt_Unqualified);
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_MacroTest
// #define SYSRPTGRID_MACROTEST_COL_TESTINDEX  0
#define SYSRPTGRID_MACROTEST_COL_INDEX         0
#define SYSRPTGRID_MACROTEST_COL_PARANAME   1
#define SYSRPTGRID_MACROTEST_COL_PARAID        2
#define SYSRPTGRID_MACROTEST_COL_PARAVALUE  3

#define SYSRPTGRID_MACROTEST_COLS                 ( (SYSRPTGRID_MACROTEST_COL_PARAVALUE+1)*_SYSRPTFILL_USE_COLS)

CSystemRptFillGrid_MacroTest::CSystemRptFillGrid_MacroTest()
{
	m_pValues = NULL;
}

CSystemRptFillGrid_MacroTest::~CSystemRptFillGrid_MacroTest()
{
	
}

void CSystemRptFillGrid_MacroTest::InitGrid()
{
	SetListMode(TRUE);
	//SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(SYSRPTGRID_MACROTEST_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);

	InitGridTitle();

	ResetScrollBars();
}

void CSystemRptFillGrid_MacroTest::InitGridTitle()
{
	CString cTempStr[SYSRPTGRID_MACROTEST_COLS]={
		_T("序号")
		,_T("参数名称")
		,_T("参数ID")
		,_T("参数值")
	};
	int iWidth[SYSRPTGRID_MACROTEST_COLS]={60, 120, 200, 100};

	int nIndex = 0, nCol = 0;
	long nColAdd = 0;

	for (nIndex=1; nIndex<_SYSRPTFILL_USE_COLS; nIndex++)
	{
		nColAdd = (SYSRPTGRID_MACROTEST_COL_PARAVALUE+1) * nIndex;

		for (nCol=0; nCol <=SYSRPTGRID_MACROTEST_COL_PARAVALUE; nCol++)
		{
			cTempStr[nCol + nColAdd] = cTempStr[nCol];
			iWidth[nCol + nColAdd] = iWidth[nCol];
		}
	}

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, SYSRPTGRID_MACROTEST_COLS);

	SetRowHeight(0, EXBASEGRID_ROWHEIGHT);
}


void CSystemRptFillGrid_MacroTest::UpdateDatas()
{

}

void CSystemRptFillGrid_MacroTest::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_pDatas = pDatas;
	CMacroTest *pMacroTest = (CMacroTest*)pDatas;
	CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
	CTestMacro *pTestMacro = 	Gb_GetMacroPtr(pMacroTest, pMacroTestPara->GetMacroID());

	m_pValues = pMacroTestPara->m_pValuesForCal;
	m_pFaultParas = pMacroTestPara->GetFaultParaDatas();
	CTmFaultParas *pFaultParas = (CTmFaultParas*)pTestMacro->GetFaultParas();
	CTmFaultParasEx *pFaultParasEx = pTestMacro->GetFaultParasEx();
	CShortDatas *pResults = pTestMacro->GetResults();
	CExBaseList listDatas;

	if (pFaultParasEx != NULL)
	{
		pFaultParasEx->SelectAllDatas(listDatas);
	}

	CExBaseObject *pObj = NULL;	
	POS pos = pFaultParas->GetHeadPosition();
	long nRows = pFaultParas->GetCount() + listDatas.GetCount() + pResults->GetCount();
	SetRowCount(nRows + 1);

	int nRowIndex = 1;

	//故障参数
	ShowDatas_FaultPara(pFaultParas, nRowIndex);

	//扩展故障参数
	ShowDatas_FaultParaEx(&listDatas, nRowIndex);

	//结果参数
	ShowDatas_Result(pResults, nRowIndex);

	listDatas.RemoveAll();
	SetRowCount(nRowIndex, bResetScrollBars);

	for (nRowIndex=nRows; nRowIndex<m_nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, EXBASEGRID_ROWHEIGHT);
	}

	AdjustAllCols(bResetScrollBars);

	if (bResetScrollBars)
	{
		ResetScrollBars();
	}
}

void CSystemRptFillGrid_MacroTest::ShowDatas_FaultPara(CExBaseList *pFaultParas, int &nRowIndex)
{
	CExBaseObject *pObj = NULL;	
	POS pos = pFaultParas->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pFaultParas->GetNext(pos);

		if (!g_bSysReportFillShowAllDatas)
		{
			if (m_pFaultParas->FindByID(pObj->m_strID) == NULL)
			{
				continue;
			}
		}

		ShowData(pObj, nRowIndex, FALSE);
	}
}

void CSystemRptFillGrid_MacroTest::ShowDatas_FaultParaEx(CExBaseList *pFaultParasEx, int &nRowIndex)
{
	CExBaseObject *pObj = NULL;	
	POS pos = pFaultParasEx->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pFaultParasEx->GetNext(pos);

		if (!g_bSysReportFillShowAllDatas)
		{
			if (m_pFaultParas->FindByID(pObj->m_strID) == NULL)
			{
				continue;
			}
		}

		ShowDataEx(pObj, nRowIndex, FALSE);
	}
}

void CSystemRptFillGrid_MacroTest::ShowDatas_Result(CExBaseList *pResults, int &nRowIndex)
{
	CExBaseObject *pObj = NULL;	
	POS pos = pResults->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pResults->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}
}

void CSystemRptFillGrid_MacroTest::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CShortData *pShortData = (CShortData*)pData;

	if (pShortData->m_nReserved < 0)
	{
		return;
	}

	CString strText;
	long nRowCal = (nRow - 1) / _SYSRPTFILL_USE_COLS;
	long nRowCalLeft = (nRow - 1) % _SYSRPTFILL_USE_COLS;
	long nColBegin = nRowCalLeft * (SYSRPTGRID_MACROTEST_COL_PARAVALUE + 1);
	nRowCal += 1;

	Show_IndexEx(pData, nRowCal, SYSRPTGRID_MACROTEST_COL_INDEX + nColBegin, nRow);
	Show_StaticString(pData, nRowCal, SYSRPTGRID_MACROTEST_COL_PARANAME+nColBegin,     &pShortData->m_strName);
	Show_StaticString(pData, nRowCal, SYSRPTGRID_MACROTEST_COL_PARAID+nColBegin,          &pShortData->m_strID);

	CValue *pValue = NULL;
	
	if (m_pValues != NULL)
	{
		pValue = (CValue*)m_pValues->FindByID(pShortData->m_strID);
	}

	if (pValue == NULL)
	{
		Show_StaticString(pData, nRowCal, SYSRPTGRID_MACROTEST_COL_PARAVALUE+nColBegin,    &pShortData->m_strValue);
	}
	else
	{
		Show_StaticString(pData, nRowCal, SYSRPTGRID_MACROTEST_COL_PARAVALUE+nColBegin,    &pValue->m_strValue);
	}

	nRow++;
}

void CSystemRptFillGrid_MacroTest::ShowDataEx(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CShortData *pShortData = (CShortData*)pData;
	CString strText, strIDPath;
	strIDPath = pShortData->GetIDPathEx(TMCLASSID_CTMFAULTPARASEX, FALSE);

	if (!g_bSysReportFillShowAllDatas)
	{
		if (m_pFaultParas->FindByID(strIDPath) == NULL)
		{
			return;
		}
	}

	Show_Index(pData, nRow, SYSRPTGRID_MACROTEST_COL_INDEX);

	strText = pShortData->GetNamePathEx(TMCLASSID_CTMFAULTPARASEX, FALSE);
	Show_StaticString(pData, nRow, SYSRPTGRID_MACROTEST_COL_PARANAME,     &strText);

	Show_StaticString(pData, nRow, SYSRPTGRID_MACROTEST_COL_PARAID,          &strIDPath);
	
	CValue *pValue = NULL;
	
	if (m_pValues != NULL)
	{
		pValue = (CValue*)m_pValues->FindByID(strIDPath);
	}

	if (pValue == NULL)
	{
		Show_StaticString(pData, nRow, SYSRPTGRID_MACROTEST_COL_PARAVALUE,    &pShortData->m_strValue);
	}
	else
	{
		Show_StaticString(pData, nRow, SYSRPTGRID_MACROTEST_COL_PARAVALUE,    &pValue->m_strValue);
	}

	nRow++;
}


//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_CommCmd
// #define SYSRPTGRID_COMMCMD_COL_TESTINDEX  0
#define SYSRPTGRID_COMMCMD_COL_INDEX         0
#define SYSRPTGRID_COMMCMD_COL_PARANAME   1
#define SYSRPTGRID_COMMCMD_COL_PARAID        2
#define SYSRPTGRID_COMMCMD_COL_PARAVALUE  3
#define SYSRPTGRID_COMMCMD_COLS                  4

CSystemRptFillGrid_CommCmd::CSystemRptFillGrid_CommCmd()
{
	
}

CSystemRptFillGrid_CommCmd::~CSystemRptFillGrid_CommCmd()
{
	
}

void CSystemRptFillGrid_CommCmd::InitGrid()
{
	SetListMode(TRUE);
	//SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(SYSRPTGRID_COMMCMD_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);

	InitGridTitle();

	ResetScrollBars();
}

void CSystemRptFillGrid_CommCmd::InitGridTitle()
{
	CString cTempStr[SYSRPTGRID_COMMCMD_COLS]={
		_T("序号")
		,_T("参数名称")
		,_T("参数ID")
		,_T("参数值")
	};
	int iWidth[SYSRPTGRID_COMMCMD_COLS]={60, 120, 200, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, SYSRPTGRID_COMMCMD_COLS);

	SetRowHeight(0, EXBASEGRID_ROWHEIGHT);
}


void CSystemRptFillGrid_CommCmd::UpdateDatas()
{

}

void CSystemRptFillGrid_CommCmd::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	CCommCmd *pCommCmd = (CCommCmd*)pDatas;
	CReport *pReport = pCommCmd->GetReport(-1);
	m_pDatas = pReport->m_pValues;
	CExBaseList listDatas;
	listDatas.Append(pCommCmd->GetRptDataEx());//显示扩展报告数据
	CReportMap *pReportMap = pCommCmd->GetReportMap();
	pReportMap->SelectAllRptData(listDatas);	//显示报告标签定义的数据
	CExBaseList listShow;
	int nRowIndex = 1;

	//long nRows = listDatas.GetCount() + pReport->m_pRptDvmDataset->GetCount();
	if (listDatas.GetCount() > 0)
	{
		SetRowCount(listDatas.GetCount() + 1);
		POS pos = listDatas.GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = listDatas.GetNext(pos);

			if (listShow.FindByID(p->m_strID) != NULL)
			{
				continue;
			}

			ShowData(p, nRowIndex, FALSE);
			listShow.AddTail(p);
		}

		listDatas.RemoveAll();
		listShow.RemoveAll();
	}
	else
	{
		CDvmDataset *pRptDvmDataset = pReport->m_pRptDvmDataset;
		SetRowCount(pRptDvmDataset->GetCount() + 1);
		POS pos = pRptDvmDataset->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pRptDvmDataset->GetNext(pos);
			ShowData(p, nRowIndex, FALSE);
		}
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, TRUE);
}

void CSystemRptFillGrid_CommCmd::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CString strText;

	Show_Index(pData, nRow, SYSRPTGRID_COMMCMD_COL_INDEX);
	Show_StaticString(pData, nRow, SYSRPTGRID_COMMCMD_COL_PARANAME,     &pData->m_strName);
	Show_StaticString(pData, nRow, SYSRPTGRID_COMMCMD_COL_PARAID,          &pData->m_strID);

	if (pData->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		Show_StaticString(pData, nRow, SYSRPTGRID_COMMCMD_COL_PARAVALUE,          &((CDvmData*)pData)->m_strValue);
	}
	else
	{
		CValue *pValue =  (CValue*)m_pDatas->FindByID(pData->m_strID);

		if (pValue != NULL)
		{
			Show_StaticString(pData, nRow, SYSRPTGRID_COMMCMD_COL_PARAVALUE,          &pValue->m_strValue);
		}
		else
		{
			Show_StaticString(pData, nRow, SYSRPTGRID_COMMCMD_COL_PARAVALUE,          _T("----"));
		}
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_Safety
// #define SYSRPTGRID_SAFETY_COL_TESTINDEX  0
#define SYSRPTGRID_SAFETY_COL_INDEX         0
#define SYSRPTGRID_SAFETY_COL_PARANAME   1
#define SYSRPTGRID_SAFETY_COL_PARAID        2
#define SYSRPTGRID_SAFETY_COL_PARAVALUE  3
#define SYSRPTGRID_SAFETY_COLS                  4

CSystemRptFillGrid_Safety::CSystemRptFillGrid_Safety()
{
	
}

CSystemRptFillGrid_Safety::~CSystemRptFillGrid_Safety()
{
	
}

void CSystemRptFillGrid_Safety::InitGrid()
{
	SetListMode(TRUE);
	//SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(SYSRPTGRID_SAFETY_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);

	InitGridTitle();

	ResetScrollBars();
}

void CSystemRptFillGrid_Safety::InitGridTitle()
{
	CString cTempStr[SYSRPTGRID_SAFETY_COLS]={
		_T("序号")
		,_T("参数名称")
		,_T("参数ID")
		,_T("参数值")
	};
	int iWidth[SYSRPTGRID_SAFETY_COLS]={60, 120, 200, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, SYSRPTGRID_SAFETY_COLS);

	SetRowHeight(0, EXBASEGRID_ROWHEIGHT);
}


void CSystemRptFillGrid_Safety::UpdateDatas()
{

}

void CSystemRptFillGrid_Safety::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	CSafety *pSafety = (CSafety*)pDatas;
	CReport *pReport = pSafety->GetReport(-1);
	m_pDatas = pReport->m_pValues;
	CShortDatas *pSafetyDatas = pSafety->GetDatas();
	int nRowIndex = 1;

	SetRowCount(pSafetyDatas->GetCount() + 1);
	POS pos = pSafetyDatas->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pSafetyDatas->GetNext(pos);
		ShowData(p, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, TRUE);
}

void CSystemRptFillGrid_Safety::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CShortData *pShortData = (CShortData*)pData;

	CString strText;

	Show_Index(pData, nRow, SYSRPTGRID_SAFETY_COL_INDEX);
	Show_StaticString(pData, nRow, SYSRPTGRID_SAFETY_COL_PARANAME,     &pShortData->m_strName);
	Show_StaticString(pData, nRow, SYSRPTGRID_SAFETY_COL_PARAID,          &pShortData->m_strID);

	CValue *pValue = (CValue *)m_pDatas->FindByID(pShortData->m_strID);

	if (pValue != NULL)
	{
		Show_StaticString(pData, nRow, SYSRPTGRID_SAFETY_COL_PARAVALUE,          &pValue->m_strValue);
	}
	else
	{
		Show_StaticString(pData, nRow, SYSRPTGRID_SAFETY_COL_PARAVALUE,          &pShortData->m_strValue);
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_SysParaEdit
// #define SYSRPTGRID_SYSPARAEDIT_COL_TESTINDEX  0
#define SYSRPTGRID_SYSPARAEDIT_COL_INDEX         0
#define SYSRPTGRID_SYSPARAEDIT_COL_PARANAME   1
#define SYSRPTGRID_SYSPARAEDIT_COL_PARAID        2
#define SYSRPTGRID_SYSPARAEDIT_COL_PARAVALUE  3
#define SYSRPTGRID_SYSPARAEDIT_COLS                  4

CSystemRptFillGrid_SysParaEdit::CSystemRptFillGrid_SysParaEdit()
{
	
}

CSystemRptFillGrid_SysParaEdit::~CSystemRptFillGrid_SysParaEdit()
{
	
}

void CSystemRptFillGrid_SysParaEdit::InitGrid()
{
	SetListMode(TRUE);
	//SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(SYSRPTGRID_SYSPARAEDIT_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);

	InitGridTitle();

	ResetScrollBars();
}

void CSystemRptFillGrid_SysParaEdit::InitGridTitle()
{
	CString cTempStr[SYSRPTGRID_SYSPARAEDIT_COLS]={
		_T("序号")
		,_T("参数名称")
		,_T("参数ID")
		,_T("参数值")
	};
	int iWidth[SYSRPTGRID_SYSPARAEDIT_COLS]={60, 120, 200, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, SYSRPTGRID_SYSPARAEDIT_COLS);

	SetRowHeight(0, EXBASEGRID_ROWHEIGHT);
}


void CSystemRptFillGrid_SysParaEdit::UpdateDatas()
{

}

void CSystemRptFillGrid_SysParaEdit::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	CSysParaEdit *pSysParaEdit = (CSysParaEdit*)pDatas;
	CReport *pReport = pSysParaEdit->GetReport(-1);
	m_pDatas = pReport->m_pValues;
	CDevice *pDevice = (CDevice*)pDatas->GetAncestor(GBCLASSID_DEVICE);
	CSysParas *pSysParas = pDevice->GetSysParas();
	int nRowIndex = 1;

	SetRowCount(pSysParas->GetCount() + 1);
	POS pos = pSysParas->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pSysParas->GetNext(pos);
		ShowData(p, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, TRUE);
}

void CSystemRptFillGrid_SysParaEdit::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDataObj *pDataObj = (CDataObj*)pData;

	CString strText;

	Show_Index(pData, nRow, SYSRPTGRID_SYSPARAEDIT_COL_INDEX);
	Show_StaticString(pData, nRow, SYSRPTGRID_SYSPARAEDIT_COL_PARANAME,     &pDataObj->m_strName);
	Show_StaticString(pData, nRow, SYSRPTGRID_SYSPARAEDIT_COL_PARAID,          &pDataObj->m_strID);

	CValue *pValue = (CValue *)m_pDatas->FindByID(pDataObj->m_strID);

	if (pValue != NULL)
	{
		Show_StaticString(pData, nRow, SYSRPTGRID_SYSPARAEDIT_COL_PARAVALUE,          &pValue->m_strValue);
	}
	else
	{
		Show_StaticString(pData, nRow, SYSRPTGRID_SYSPARAEDIT_COL_PARAVALUE,          &pDataObj->m_strValue);
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CSystemRptFill
CSystemRptFill::CSystemRptFill(void)
{
	m_pLastReport = NULL;
	m_pLastGrid = NULL;
	m_pLastRptFillObject = NULL;
	m_pLastRptFillObjectSub = NULL;
	m_nCtrlID = 1;
	m_nViewHeight = 0;
	m_nLastItemsScriptTestIndex = 0;
	m_nSysRptShowMaxCount = 0;
	m_nViewWidth = 0;
	m_nViewHeight = 0;
}

CSystemRptFill::~CSystemRptFill(void)
{
	
}

//////////////////////////////////////////////////////////////////////////
//
//重载父类成员虚函数
//
//////////////////////////////////////////////////////////////////////////
void CSystemRptFill::CreateSystemApp()
{
	
}

CString CSystemRptFill::GetReportFillClassID()
{
	return REPORTFILL_PROGID_SYSTEM;
}

long CSystemRptFill::New(CString strReportMapFile, CString strReportTemplFile, CString strReportFile, BOOL bFirst)
{
	return TRUE;
}

long CSystemRptFill::Open(const CString  &strReportFile, BOOL bFirst)
{
	CItemContainer *pItemContainer = (CItemContainer*)m_pGuideBook->GetItemContainer();
	ASSERT (pItemContainer != NULL);

	if (pItemContainer == NULL)
	{
		return 0;
	}

	CExBaseList *pListItems = pItemContainer->GetGuideBookAllItems();
	POS pos = pListItems->GetHeadPosition();
	CGbItemBase *pItem = NULL;
	CReport *pReport = NULL;

	while (pos != NULL)
	{
		pItem = (CGbItemBase *)pListItems->GetNext(pos);
		pReport = pItem->GetReport(-1);

		if (pReport != NULL)
		{
			InitFillReport(pReport);
		}

		if (m_listSysRptFillItems.GetCount() <= m_nSysRptShowMaxCount)
		{
			break;
		}
	}

	AdjustReportWindowOnSize();

	return 0;
}

long CSystemRptFill::Save()
{
	return TRUE;
}

long CSystemRptFill::SaveAs(CString  strRptFile)
{
	return TRUE;
}

long CSystemRptFill::Close(long nSave)
{
	return TRUE;
}

void CSystemRptFill::SetSysRptShowMaxCount(long nSysRptShowMaxCount)	
{	
	m_nSysRptShowMaxCount = nSysRptShowMaxCount;	
}

void CSystemRptFill::AdjustReportWindowOnSize()
{
	
}

//是否包含需要填写的报告数据的位置
long CSystemRptFill::HasReportNeedFill(const CGbItemBase* pItem)
{
	return 0;
}

long CSystemRptFill::FillReport(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible)
{
	if (!m_bFillReport)
	{
		return 0;
	}

	CExBaseObject *pTestControl = (CExBaseObject*)pReport->GetAncestor(GBCLASSID_TESTCONTROL);
	ASSERT (pTestControl != NULL);
	ASSERT (m_strName == pTestControl->m_strName);

	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
	CGbItemBase *pGbItem = GetParentGbItem(pReport);

	if (pGbItem == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pGbItem->GetClassID();
	CItemsRsltExprScript *pItemsRsltExprScript = NULL;

	switch (nClassID)
	{
	case GBCLASSID_COMMCMD:
		{
			CCommCmd *pCommCmd = (CCommCmd *)pGbItem;
			pItemsRsltExprScript = GetItemsRsltExprScript(pCommCmd);

			if (pItemsRsltExprScript == NULL)
			{
				ShowReport(pCommCmd, pReport);
			}
			else
			{
				ShowReport(pItemsRsltExprScript, pReport, (CGbItemBase*)pCommCmd->GetParent());
			}
		}
		break;

	case GBCLASSID_MACROTEST:
		{
			CMacroTest *pMacroTest = (CMacroTest*)pGbItem;
			pItemsRsltExprScript = GetItemsRsltExprScript(pMacroTest);

			if (pItemsRsltExprScript == NULL)
			{
				ShowReport(pMacroTest, pReport);
			}
			else
			{
				//ShowReport(pItemsRsltExprScript, pReport, pMacroTest);
			}
		}
		break;

	case GBCLASSID_SYSPARAEDIT:
		{
			CSysParaEdit *pSysParaEdit = (CSysParaEdit *)pGbItem;
			ShowReport(pSysParaEdit, pReport);
		}
		break;

	case GBCLASSID_SAFETY:
		{
			CSafety *pSafety = (CSafety *)pGbItem;
			ShowReport(pSafety, pReport);
		}
		break;
	}

	return 0;
}

//在报告中定位
long CSystemRptFill::LocateReport(CGbItemBase* pItemBase)
{
	return 0;
}

long CSystemRptFill::AdjustReport(CThreadProgressInterface *pProgress)
{
	return 0;
}

long CSystemRptFill::AdjustReport_FillEmpty()
{
	return 0;
}

BOOL CSystemRptFill::ActiveWindow(const CString &strTitle)
{
	BOOL bTrue = FALSE;
	
	return bTrue;
}

BOOL CSystemRptFill::AddNewReport(const CString &strRptTmplFile)
{
	BOOL bTrue = TRUE;
	
	return bTrue;
}

void CSystemRptFill::PrintReport()
{
}

void CSystemRptFill::ExportPdf()
{
}
void CSystemRptFill::ZoomReport(long nPercentage)
{
}

long CSystemRptFill::GetZoomReport()
{
	long nPercentage = 100;
	return nPercentage;
}

void CSystemRptFill::EmptyReportText()
{
}

BOOL CSystemRptFill::CloseSystemDocWindow()
{
	return TRUE;
}

void CSystemRptFill::AdjustSystemWindow()
{
}

void CSystemRptFill::AdjustSystemReportFills()
{
	if (m_listSysRptFillItems.GetCount() <= m_nSysRptShowMaxCount)
	{
		return;
	}

	CSystemRptFillItem *pRptFillItem = (CSystemRptFillItem*)m_listSysRptFillItems.GetHead();
	pRptFillItem->m_pGbItem->m_dwReserved = 0;
	long nOffset = pRptFillItem->GetOffset();
	m_listSysRptFillItems.Delete(pRptFillItem);
	
	POS pos = m_listSysRptFillItems.GetHeadPosition();

	while (pos != NULL)
	{
		pRptFillItem = (CSystemRptFillItem *)m_listSysRptFillItems.GetNext(pos);
		pRptFillItem->Offset(nOffset, m_pParentWnd);
	}

	m_nViewHeight -= nOffset;
}

CItemsRsltExprScript* CSystemRptFill::GetItemsRsltExprScript(CGbItemBase* pItem)
{
	UINT nClassID = pItem->GetClassID();
	CCommCmd *pCommCmd = NULL;

	if (nClassID != GBCLASSID_COMMCMD && nClassID != GBCLASSID_MACROTEST)
	{
		return NULL;
	}

	if (nClassID == GBCLASSID_COMMCMD)
	{
		pCommCmd = (CCommCmd*)pItem;
		return  pCommCmd->GetItemsRsltExprScript();
	}

	CMacroTest *pMacroTest = (CMacroTest*)pItem;

	CExBaseList *pList = pMacroTest->GetSubGbItems();
	ASSERT (pList != NULL);

	if (pList->GetCount() != 1)
	{
		return NULL;
	}

	CGbItemBase *pSubItem = (CGbItemBase*)pList->GetHead();

	if (pSubItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		return NULL;
	}

	pCommCmd = (CCommCmd*)pSubItem;
	return  pCommCmd->GetItemsRsltExprScript();
}

void CSystemRptFill::ShowReport(CCommCmd *pCommCmd, CReport *pReport)
{
	CSystemRptFillGridBase *pRptFillGrid = (CSystemRptFillGridBase*)pCommCmd->m_dwReserved;

	if (pRptFillGrid == NULL)
	{
		CreateReportShow(pCommCmd, new CSystemRptFillGrid_CommCmd(), pCommCmd);
	}
	else
	{
		pRptFillGrid->ShowDatas(pCommCmd);
		UpdateGrid(pCommCmd, pRptFillGrid);
	}
}

void CSystemRptFill::ShowReport(CMacroTest *pMacroTest, CReport *pReport)
{
	CSystemRptFillGridBase *pRptFillGrid = (CSystemRptFillGridBase*)pMacroTest->m_dwReserved;

	CMacroTestPara *pTestPara = pMacroTest->GetMacroTestPara();
	CValues *pValues = pTestPara->m_pValuesForCal;
	CTestMacro *pTestMacro = 	Gb_GetMacroPtr(pMacroTest, pTestPara->GetMacroID());

	if (pTestMacro == NULL)
	{
		return;
	}

	if (pRptFillGrid == NULL)
	{
		m_pLastRptFillObject = pMacroTest;
		CreateReportShow(pMacroTest, new CSystemRptFillGrid_MacroTest(), pMacroTest);
	}
	else
	{
		pRptFillGrid->ShowDatas(pMacroTest);
		UpdateGrid(pMacroTest, pRptFillGrid);
	}

}

void CSystemRptFill::ShowReport(CSafety *pSafety, CReport *pReport)
{
	CSystemRptFillGridBase *pRptFillGrid = (CSystemRptFillGridBase*)pSafety->m_dwReserved;

	if (pRptFillGrid == NULL)
	{
		CreateReportShow(pSafety, new CSystemRptFillGrid_Safety(), pSafety);
	}
	else
	{
		pRptFillGrid->ShowDatas(pSafety);
		UpdateGrid(pSafety, pRptFillGrid);
	}
}

void CSystemRptFill::ShowReport(CSysParaEdit *pSysParaEdit, CReport *pReport)
{
	CSystemRptFillGridBase *pRptFillGrid = (CSystemRptFillGridBase*)pSysParaEdit->m_dwReserved;

	if (pRptFillGrid == NULL)
	{
		CreateReportShow(pSysParaEdit, new CSystemRptFillGrid_SysParaEdit(), pSysParaEdit);
	}
	else
	{
		pRptFillGrid->ShowDatas(pSysParaEdit);
		UpdateGrid(pSysParaEdit, pRptFillGrid);
	}
}
#define SYSREPORT_GRID_VERT_ADD   10
#define SYSREPORT_GRID_HORZ_ADD   40

void CSystemRptFill::ShowReport(CItemsRsltExprScript *pItemsRsltExprScript, CReport *pReport, CGbItemBase *pGbItem)
{
	if (m_pLastRptFillObject == pGbItem)
	{
		ASSERT (m_pLastGrid != NULL);

		if (m_pLastGrid == NULL)
		{
			return;
		}

		if (m_nLastItemsScriptTestIndex == pItemsRsltExprScript->m_dwReserved)
		{//更新表格数据
			m_pLastGrid->UpdateDatas();
		}
		else
		{//显示表格
			m_pLastGrid->ShowDatas(pItemsRsltExprScript);
			UpdateGrid(pGbItem);
		}
	}
	else
	{
		m_nLastItemsScriptTestIndex = 0;
		CreateReportShow(pGbItem, new CSystemRptFillGrid_ItemsRsltScript(), pItemsRsltExprScript);
	}

	m_nLastItemsScriptTestIndex = pItemsRsltExprScript->m_dwReserved;
	m_pLastRptFillObject = pGbItem;
}

void CSystemRptFill::CreateReportShow(CGbItemBase *pGbItem, CSystemRptFillGridBase *pReportGrid, CExBaseList *pDatas)
{
	CString strText;
	CStatic *pWndTitle = new CStatic();
	CRect rcWnd;
	strText = pGbItem->GetNamePathEx(GBCLASSID_DEVICE, FALSE, _T(" / "));
	//strText = pGbItem->GetNamePathEx(GBCLASSID_TESTCONTROL, TRUE, _T(" / "));
	CPoint ptScroll;
	long nPos = m_pParentWnd->GetScrollPos(SB_VERT);

	m_yCurrRptCtrlPos = m_nViewHeight;// + 5;// - nPos;

	rcWnd.left = 5;
	rcWnd.top = m_yCurrRptCtrlPos + 5 - nPos;
	rcWnd.bottom = rcWnd.top + 16;	
	rcWnd.right = GetWidth();
	pWndTitle->CreateEx(0, _T("STATIC"), strText, WS_VISIBLE | WS_CHILD | SS_LEFT, rcWnd, m_pParentWnd, m_nCtrlID++);
	pWndTitle->SetFont(g_pGlobalFont12);

	rcWnd.top = rcWnd.bottom + 2;
	rcWnd.bottom = rcWnd.top + 40;
	pReportGrid->Create(rcWnd, m_pParentWnd, m_nCtrlID++);
	pReportGrid->InitGrid();
	pReportGrid->ShowDatas(pDatas);
	long nHeightAdd = pReportGrid->GetVirtualHeight() + SYSREPORT_GRID_VERT_ADD;
	long nAddWidth = 0;

	if (nHeightAdd < 50)
	{
		if (pGbItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			CCommCmd *pCmd = (CCommCmd*)pGbItem;
			nAddWidth = 200;
			
			if (pCmd->IsCmdRptDataset())
			{
				nHeightAdd += 80;
			}
		}
	}

	rcWnd.bottom = rcWnd.top + nHeightAdd;
	rcWnd.right = rcWnd.left + pReportGrid->GetVirtualWidth() + SYSREPORT_GRID_HORZ_ADD+nAddWidth;

#ifdef _use_move_window
	pReportGrid->MoveWindow(rcWnd);
#else
	pReportGrid->SetWindowPos(NULL, rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height(), SWP_SHOWWINDOW);
#endif

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%d, %d, %d, %d"), rcWnd.top, rcWnd.bottom, rcWnd.left, rcWnd.right);

	m_listSysRptFillItems.AddSystemRptFillItem(pGbItem, pWndTitle, pReportGrid);
	//m_yCurrRptWndPos = max(m_yCurrRptWndPos, rcWnd.bottom);

	//if (rcWnd.bottom > m_yCurrRptWndPos)
	//{
	//	m_yCurrRptWndPos = rcWnd.bottom;
	//}

	pReportGrid->m_yCurrPos = m_nViewHeight;
	m_nViewHeight += nHeightAdd + 18 + 5 + 2;  //18=16+12
	AdjustSystemReportFills();

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("------------------------------%s   %d"), pGbItem->m_strName, m_yCurrRptWndPos);
	m_pLastGrid = pReportGrid;
	m_pParentWnd->PostMessage(WM_ADJUSTVIEWSIZE, (DWORD)this, (DWORD)this);
	pGbItem->m_dwReserved = (DWORD)pReportGrid;
}

void CSystemRptFill::UpdateGrid(CGbItemBase *pGbItem)
{
	UpdateGrid(pGbItem, m_pLastGrid);
// 	CRect rcWnd;
// 	m_pLastGrid->GetWindowRect(&rcWnd);
// 	m_pParentWnd->ScreenToClient(&rcWnd);
// 	rcWnd.bottom = rcWnd.top + m_pLastGrid->GetVirtualHeight() + SYSREPORT_GRID_VERT_ADD;
// 	rcWnd.right = rcWnd.left + m_pLastGrid->GetVirtualWidth() + SYSREPORT_GRID_HORZ_ADD;
// 	m_pLastGrid->MoveWindow(rcWnd);
// 	m_yCurrRptWndPos = rcWnd.bottom;
// 
// 	m_pParentWnd->PostMessage(WM_ADJUSTVIEWSIZE, rcWnd.Width(), m_yCurrRptWndPos);
}

void CSystemRptFill::UpdateGrid(CGbItemBase *pGbItem, CSystemRptFillGridBase *pRptFillGrid)
{
	CRect rcWnd;
	pRptFillGrid->GetWindowRect(&rcWnd);
	m_pParentWnd->ScreenToClient(&rcWnd);
// 	rcWnd.bottom = rcWnd.top + pRptFillGrid->GetVirtualHeight() + SYSREPORT_GRID_VERT_ADD;
// 	rcWnd.right = rcWnd.left + pRptFillGrid->GetVirtualWidth() + SYSREPORT_GRID_HORZ_ADD;
// 	pRptFillGrid->MoveWindow(rcWnd);
	//m_yCurrRptWndPos = max(m_yCurrRptWndPos, rcWnd.bottom);
	
// 	if (rcWnd.bottom > m_yCurrRptWndPos)
// 	{
// 		m_yCurrRptWndPos = rcWnd.bottom;
// 	}
// 
// 	if (rcWnd.right > m_nViewWidth)
// 	{
// 		m_nViewWidth = rcWnd.right;
// 	}

	m_yCurrRptCtrlPos = pRptFillGrid->m_yCurrPos;
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("------------------------------%s   %d"), pGbItem->m_strName, m_yCurrRptWndPos);
	m_pParentWnd->PostMessage(WM_ADJUSTVIEWSIZE, (DWORD)this, 0);
}

long CSystemRptFill::GetWidth()
{
	if (m_nViewWidth >= SYSTEMREPORT_VIEW_MIN_WIDTH)
	{
		return m_nViewWidth;
	}
	else
	{
		return SYSTEMREPORT_VIEW_MIN_WIDTH;
	}
}

long CSystemRptFill::GetHeight()
{
	return m_nViewHeight;
}

long CSystemRptFill::GetCurrPos()
{
	return m_yCurrRptCtrlPos;
}