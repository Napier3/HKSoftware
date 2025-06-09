#include "StdAfx.h"
#include "WordRptFillBase.h"
#include "../../TestControl/SmartTestBaseApp.h"

#ifndef _PSX_QT_LINUX_
#include "../../../../Module/Record/XRecordDrawComtradeDib.h"
#endif

CWordRptFillBase::CWordRptFillBase(void)
{
	m_hWordWnd = NULL;
	m_pCurrBkmk = NULL;
}

CWordRptFillBase::~CWordRptFillBase(void)
{
}

void CWordRptFillBase::AdjustDocWindow(CWnd* pWnd)
{
    CSmartTestBaseApp* pApp = g_theSmartTestBaseApp;
#ifndef _PSX_QT_LINUX_

	ASSERT(pApp->GetCntrConfig() != NULL);

	if (pWnd == NULL)
	{
		if (::IsWindow(m_hWordWnd))
		{
			pWnd = CWnd::FromHandle(m_hWordWnd);
		}
	}

	if (pWnd != NULL)
	{
		CRect rectWin;
		pWnd->GetWindowRect(rectWin);
		::SetParent(pWnd->GetSafeHwnd(),m_pParentWnd->GetSafeHwnd());

		if (/*TRUE*/pApp->GetCntrConfig()->m_nHideAllCmdbars == 1)
		{
			if (FALSE/*CanUnLockReport()*/)
			{
			}
			else
			{
				//注释掉下面一行，可以在word中输入
				pWnd->ModifyStyle(0,WS_CHILD);
			}

			pWnd->ModifyStyle(WS_BORDER | WS_DLGFRAME | WS_EX_WINDOWEDGE,0);
			pWnd->ModifyStyle(WS_SIZEBOX,0);
			pWnd->SetMenu(NULL);

			// need to adjust the client edge style as max/restore happens
			DWORD dwStyle = ::GetWindowLong(m_pParentWnd->GetSafeHwnd(), GWL_EXSTYLE);
			DWORD dwNewStyle = dwStyle;
			dwNewStyle |= WS_EX_CLIENTEDGE;

			if (dwStyle != dwNewStyle)
			{
				// SetWindowPos will not move invalid bits
				::RedrawWindow(m_pParentWnd->GetSafeHwnd(), NULL, NULL,
					RDW_INVALIDATE | RDW_ALLCHILDREN);

				// remove/add WS_EX_CLIENTEDGE to MDI client area
				::SetWindowLong(m_pParentWnd->GetSafeHwnd(), GWL_EXSTYLE, dwNewStyle);
				::SetWindowPos(m_pParentWnd->GetSafeHwnd(), NULL, 0, 0, 0, 0,
					SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE |
					SWP_NOZORDER | SWP_NOCOPYBITS);
				pWnd->ShowWindow(SW_SHOWMAXIMIZED);

				// return new client area
				::GetClientRect(m_pParentWnd->GetSafeHwnd(), &rectWin);
				pWnd->MoveWindow(rectWin);
				pWnd->SetFocus();
				m_hWordWnd = pWnd->m_hWnd;
			}

			::GetClientRect(m_pParentWnd->GetSafeHwnd(), &rectWin);
			pWnd->MoveWindow(rectWin);
			pWnd->SetFocus();
			pWnd->ShowWindow(SW_SHOWMAXIMIZED);			
		}
		else
		{
			pWnd->ModifyStyle(WS_SYSMENU,0);
			pWnd->ModifyStyle(WS_SIZEBOX,0);
			::GetClientRect(m_pParentWnd->GetSafeHwnd(), &rectWin);
			pWnd->MoveWindow(rectWin);
			pWnd->SetFocus();
		}

		m_hWordWnd = pWnd->m_hWnd;
	}
#endif
}

void CWordRptFillBase::AdjustReportWindowOnSize()
{
#ifndef _PSX_QT_LINUX_
    CWnd *pWnd = NULL;

	if (::IsWindow(m_hWordWnd))
	{
		pWnd = CWnd::FromHandle(m_hWordWnd);
	}

	if (pWnd != NULL)
	{
		CRect rectWin;
		::GetClientRect(m_pParentWnd->GetSafeHwnd(), &rectWin);
		//rectWin.left += 100;
		pWnd->MoveWindow(rectWin);
		pWnd->SetFocus();
		pWnd->BringWindowToTop();
		pWnd->UpdateWindow();
		pWnd->ShowWindow(SW_SHOW);
		pWnd->Invalidate(TRUE);
	}	
#endif
}

void CWordRptFillBase::CloseWord()
{
#ifndef _PSX_QT_LINUX_
    CSmartTestBaseApp* pApp = g_theSmartTestBaseApp;

	if( !IsValidApp() || !IsValidDoc())
	{
		return;
	}

	CloseWordDocWindow();
#endif
}

long CWordRptFillBase::HasReportNeedFill(const CGbItemBase* pItem)
{
	return 0;
}

long CWordRptFillBase::LocateReport(CGbItemBase* pItemBase)
{
#ifndef _PSX_QT_LINUX_
    CSmartTestBaseApp* pApp = g_theSmartTestBaseApp;

	CReportMap *pMap = pItemBase->m_pRptMap;
	ASSERT (pMap != NULL);

	POS pos = pMap->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pMap->GetNext(pos);
		nClassID = p->GetClassID();

		switch(nClassID)
		{
		case RPTCLASSID_RPTDATA:
			LocateReport((CRptData*)p);
			break;
		default:
			break;
		}
	}
#endif

	return 0;
}

long CWordRptFillBase::AdjustReport(CThreadProgressInterface *pProgress)
{
    CSmartTestBaseApp* pApp = g_theSmartTestBaseApp;

	if( !IsValidApp()  || !IsValidDoc())
	{
		return -1;
	}


	if (pProgress != NULL)
	{
		CTCtrlCntrConfig *pConfig = pApp->GetCntrConfig();
		CString strMsg;
        strMsg.Format(g_sLangTxt_NullReport/*_T("空白报告部分使用“%s”替换")*/, pConfig->m_strReplaceForEmptyCell.GetString());
		pProgress->SetMaxRange(2);
		pProgress->ShowMsg(strMsg);
	}

	AdjustReport_FillEmpty();

	if (pProgress != NULL)
	{
		pProgress->StepIt();
		pProgress->ShowMsg(g_sLangTxt_AdjustReport/*_T("调整报告区域")*/);
	}

	AdjustReport_Area();

	Save();

	return 0;
}

COLORREF CWordRptFillBase::TCC_GetItemReportColor(CGbItemBase *pItem)
{
	UINT nClassID = pItem->GetClassID();

    CTCtrlCntrConfig *pCtrlCntrCfg = g_theSmartTestBaseApp->GetCntrConfig();

	//避免有不合格的项目，导致项目分类相关填充的颜色问题
	if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_GUIDEBOOK)
	{
		return pCtrlCntrCfg->m_crNormal;
	}

	COLORREF color;
	int nItemState = pItem->GetState();

	if (nItemState == TEST_STATE_ELIGIBLE)
	{
		nItemState = pItem->GetStateEx();
	}

	switch(nItemState)
	{
	case TEST_STATE_NORMAL:
		color = pCtrlCntrCfg->m_crNormal;
		break;
	case TEST_STATE_INLEGIBLE:
		color = pCtrlCntrCfg->m_crInlegible;
		break;
	case TEST_STATE_ELIGIBLEEX:
		color = pCtrlCntrCfg->m_crEligibleEx;
		break;
	default:
		color = pCtrlCntrCfg->m_crNormal;
		break;
	}

	return color;
}

COLORREF CWordRptFillBase::TCC_GetItemReportBackgroundColor(CGbItemBase *pItem)
{
	UINT nClassID = pItem->GetClassID();

    CTCtrlCntrConfig *pCtrlCntrCfg = g_theSmartTestBaseApp->GetCntrConfig();

	//避免有不合格的项目，导致项目分类相关填充的颜色问题
	if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_GUIDEBOOK)
	{
#ifdef _PSX_QT_LINUX_
        return RGB(255, 255, 255);  //2022-1-3  lijunqing  for LINUX
#else
        return MSWord::wdNoHighlight;
#endif
	}

	COLORREF color;
	int nItemState = pItem->GetState();

	if (nItemState == TEST_STATE_ELIGIBLE)
	{
		nItemState = pItem->GetStateEx();
	}

	switch(nItemState)
	{
	case TEST_STATE_NORMAL:
#ifdef _PSX_QT_LINUX_
        return RGB(255, 255, 255);  //2022-1-3  lijunqing  for LINUX
#else
        color = MSWord::wdNoHighlight;
#endif
		break;
	case TEST_STATE_INLEGIBLE:
		color = pCtrlCntrCfg->m_crBackgroundInlegible;
		break;
	case TEST_STATE_ELIGIBLEEX:
#ifdef _PSX_QT_LINUX_
        return RGB(255, 255, 255);  //2022-1-3  lijunqing  for LINUX
#else
        color = MSWord::wdNoHighlight;
#endif
		break;
	default:
#ifdef _PSX_QT_LINUX_
        return RGB(255, 255, 255);  //2022-1-3  lijunqing  for LINUX
#else
        color = MSWord::wdNoHighlight;
#endif
		break;
	}

	return color;
}

long CWordRptFillBase::TCC_GetItemReportBold(CGbItemBase *pItem)
{
	UINT nClassID = pItem->GetClassID();

    CTCtrlCntrConfig *pCtrlCntrCfg = g_theSmartTestBaseApp->GetCntrConfig();

	//避免有不合格的项目，导致项目分类相关填充的颜色问题
	if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_GUIDEBOOK)
	{
		return 0;
	}

	int nItemState = pItem->GetState();

	if (nItemState == TEST_STATE_ELIGIBLE)
	{
		nItemState = pItem->GetStateEx();
	}

	if(nItemState == TEST_STATE_INLEGIBLE || nItemState == TEST_STATE_ELIGIBLEEX)
	{
		return pCtrlCntrCfg->m_nInlegibleFontBold;
	}

	return 0;
}
BOOL CWordRptFillBase::TCC_GetReportDataColor(CRptData *pData, CReport *pReport, COLORREF &crData, COLORREF &crBackground, long &nInlegibleFontBold)
{
	CString strErrData;
	CString strLeft = pData->m_strID.Left(4);
	CString strID;

	if (strLeft == g_strAinExand_Abs || strLeft == g_strAinExand_Rel || strLeft == g_strAinExand_Rst)
	{
		strID = pData->m_strID.Mid(4);
	}
	else
	{
		strID = pData->m_strID;
	}

    strErrData.Format(_T("%s%s"), g_strDataResultJudgePrevKey.GetString(), strID.GetString());

	CValue *pErrValue = (CValue*)pReport->m_pValues->FindByID(strErrData);

	if (pErrValue == NULL)
	{
		return FALSE;
	}
	else
	{
		if (pErrValue->m_strValue == _T("0") )
		{
			crData = CTCtrlCntrConfig::GetColor_Eligible();
			nInlegibleFontBold = 0;
#ifdef _PSX_QT_LINUX_
         crBackground = RGB(255, 255, 255);  //2022-1-3  lijunqing  for LINUX
#else
            crBackground = MSWord::wdNoHighlight;
#endif
		}
		else
		{
			crData = CTCtrlCntrConfig::GetColor_Inlegible();
			nInlegibleFontBold = CTCtrlCntrConfig::Get_InlegibleFontBold();
			crBackground = CTCtrlCntrConfig::GetColor_Inlegible_Background();
		}

		return TRUE;
	}
}

CExBaseList* CWordRptFillBase::FillReportParentItem(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible)
{
	CGbItemBase *pGbItem = GetParentGbItem(pReport);

	if (pGbItem == NULL)
	{
		return NULL;
	}

	m_crReport = TCC_GetItemReportColor(pGbItem);
	m_crReportBackground = TCC_GetItemReportBackgroundColor(pGbItem);
	m_nInlegibleFontBold = TCC_GetItemReportBold(pGbItem);
	long nRet = 0;
	CExBaseList *pRptDataList = NULL;

	if (nRepeatIndex < 1)
	{
		nRet = CWordRptFillBase::FillReport(pReport, pGbItem->m_pRptMap);
		pRptDataList = pGbItem->m_pRptMap;
	}
	else
	{
		nRet = CWordRptFillBase::FillReport(pReport, pGbItem->m_pRptMap->FindRptMapRepeat(nRepeatIndex));
		pRptDataList = pGbItem->m_pRptMap->FindRptMapRepeat(nRepeatIndex);
	}

	//对于不合格项目，能够在文档的末尾添加不合格项目的引用链接
	if (nInsertDataLinkWhenEligible != 1)
	{
		return NULL;
	}

	if (pGbItem->GetState() != TEST_STATE_INLEGIBLE)
	{
		return NULL;
	}

	return pRptDataList;
}

//设置报告数据，填写报告
long CWordRptFillBase::FillReport(CReport* pReport, CExBaseList *pRptDataList)
{
	if (pRptDataList == NULL)
	{
		return 0;
	}

	POS pos = pRptDataList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	//遍历每一个CRptData对象，查找相关的数据，填写报告
	while (pos != NULL)
	{
		p = pRptDataList->GetNext(pos);
		nClassID = p->GetClassID();

		switch(nClassID)
		{
		case RPTCLASSID_RPTDATA:
			FillReport((CRptData*)p, pReport);
			break;
		default:
			break;
		}
	}

	FillReport_Dataset(pReport, pRptDataList);

	return 0;
}

long CWordRptFillBase::FillReport_Dataset(CReport* pReport, CExBaseList *pRptDataList)
{
	//处理数据集的填写
	if (pReport->m_pRptDvmDataset == NULL)
	{
		return 0;
	}

	CDvmDataset *pDataset = pReport->m_pRptDvmDataset;
	CRptData *pDsRptData = (CRptData*)pRptDataList->FindByID(pReport->m_pRptDvmDataset->m_strID);

	if (pDsRptData == NULL)
	{
		return 0;
	}

	long nIndex = 0;
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CString strValue;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);
		POS posBkmk = pDsRptData->GetHeadPosition();
		CRptBkmk *pBkmk = NULL;

		while (posBkmk != NULL)
		{
			pBkmk = (CRptBkmk *)pDsRptData->GetNext(posBkmk);

			if (pData->GetValueByID(pBkmk->m_strDataAttrID, strValue))
			{
				if (pBkmk->IsFillMode_Row())
				{
					FillReport_Row(strValue, pBkmk, nIndex, FALSE);
				}
				else
				{
					FillReport_Col(strValue, pBkmk, nIndex, FALSE);
				}
			}
		}

		nIndex++;
	}

	return 0;
}

long CWordRptFillBase::FillReport(CReport* pReport, CRptMapRepeat *pRepeat)
{
	return FillReport(pReport, (CExBaseList*)pRepeat);
}

long CWordRptFillBase::FillReport(CReport* pReport, CReportMap *pMap)
{
	return FillReport(pReport, (CExBaseList*)pMap);
}

long CWordRptFillBase::AdjustReport_FillEmpty()
{
    CSmartTestBaseApp* pApp = g_theSmartTestBaseApp;
	CTCtrlCntrConfig *pConfig = pApp->GetCntrConfig();

	AdjustReport_FillEmpty(pConfig->m_strReplaceForEmptyCell, (CExBaseList*)m_pGuideBook);

	return 0;
}

long CWordRptFillBase::AdjustReport_FillEmpty(const CString &strReplace, CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();

	if (nClassID != RPTCLASSID_RPTBKMK)
	{
		return 0;
	}

	CRptBkmk *pBkmk = (CRptBkmk*)pObj;
	AdjustReport_FillEmpty(strReplace, pBkmk);

	return 0;
}

long CWordRptFillBase::AdjustReport_FillEmpty(const CString &strReplace, CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject*)pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == RPTCLASSID_RPTAREA)
		{
			continue;
		}

		if (nClassID == RPTCLASSID_RPTDATA)
		{
			AdjustReport_FillEmpty(strReplace, (CRptData*)p);
			continue;
		}

		if (p->IsBaseList())
		{
			AdjustReport_FillEmpty(strReplace, (CExBaseList*)p);
		}
		else
		{
			AdjustReport_FillEmpty(strReplace, p);
		}
	}

	return 0;
}

long CWordRptFillBase::AdjustReport_FillEmpty(const CString &strReplace, CRptData *pData)
{
	//有报告数据填充   无法通过CRptData的属性去判断有报告填充的书签填写的值是否为空，因此在CRptBkmk增加m_strValue属性，用于记录填写的书签的值
	if (pData->m_nDataFill > 0)  //填过一次报告，但填的空，m_nDataFill也是1 
	{
		return 0;
	}

	POS pos = pData->GetHeadPosition();
	CRptBkmk *pBkmk = NULL;

	while (pos != NULL)
	{
		pBkmk = (CRptBkmk*)pData->GetNext(pos);
		AdjustReport_FillEmpty(strReplace, pBkmk);
	}

	return 1;
}

long CWordRptFillBase::AdjustReport_FillEmpty(const CString &strReplace, CRptBkmk *pBkmk)
{
	UINT nClassID = pBkmk->GetClassID();
	ASSERT (nClassID == RPTCLASSID_RPTBKMK);

	if (nClassID != RPTCLASSID_RPTBKMK)
	{
		return 0;
	}

	//是系统处理
	if (IsSysBkmkDataProcess(pBkmk->m_strProcess))
	{
		AdjustReport_SysBkmkDataProcess(pBkmk);
		return 0;
	}

	FillReport(strReplace, pBkmk, FALSE);

	return 0;
}

long CWordRptFillBase::AdjustReport_Area()
{
	AdjustReport_Area((CExBaseList*)m_pGuideBook);

	return 0;
}

long CWordRptFillBase::AdjustReport_Area(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if ( Gb_IsGbItemClassID(nClassID))
		{
			AdjustReport_DelArea((CGbItemBase*)p);
		}
		else if (Gb_IsItemsBaseClassID(nClassID))
		{
			AdjustReport_Area((CItems*)p);
		}
	}

	return 0;
}

long CWordRptFillBase::AdjustReport_Area(CItems *pItems)
{
	AdjustReport_Area( (CExBaseList*)pItems);

	//调整本项目的区域
	AdjustReport_DelArea( (CGbItemBase*)pItems);

	return 0;
}

long  CWordRptFillBase::AdjustReport_DelArea(CGbItemBase *pItem)
{
	if (pItem->IsEnableAndShow())
	{
		if (pItem->m_nSelect > 0)
		{
			return 0;
		}
	}

	AdjustReport_DelArea(pItem->m_pRptMap->m_pArea);

	return 0;
}

long CWordRptFillBase::AdjustReport_SysBkmkDataProcess(CRptBkmk *pBkmk)
{
	if (pBkmk->m_strProcess == SYS_BKMK_DATA_PROCESS_v_null_del_row)
	{
		AdjustReport_DelRow(pBkmk);
		return 0;
	}

	if (pBkmk->m_strProcess == SYS_BKMK_DATA_PROCESS_v_null_del_col)
	{
		AdjustReport_DelCol(pBkmk);
		return 0;
	}

	return -1;
}

BOOL CWordRptFillBase::IsRptDataSingleMode(CRptData *pData, CReport *pReport, CShortData **ppTag)
{
	CGbItemBase* pItem = (CGbItemBase*)pReport->GetParent()->GetParent();

	ASSERT (pItem != NULL);

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		return TRUE;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	*ppTag = pCommCmd->FindRptDataEx(pData->m_strID);

	if (*ppTag == NULL)
	{
		return TRUE;
	}

	if ((*ppTag)->m_strDataTypeID == g_bstrCommCmdDataExModeID[COMMCMD_DATAEX_MODE_COL] 
		|| (*ppTag)->m_strDataTypeID == g_bstrCommCmdDataExModeID[COMMCMD_DATAEX_MODE_ROW] )
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void CWordRptFillBase::FillReport(CRptData *pData, CReport *pReport)
{
	CShortData * pTag = NULL;

	//2021-10-16  lijunqing
	//在此处理特殊情况，例如TestAppDef、Testers等全局数据集，这些部分从书签开始位置往表格下方自动填写
	CGuideBook *pGuideBook = (CGuideBook*)pData->GetAncestor(GBCLASSID_GUIDEBOOK);
	CDvmDataset *pDataset = pGuideBook->FindGlobalDataset(pData->m_strID);

	//行模式填写，需要独立的报告表格，故此处先注释  shaolei 20211018
	//for debug
// 	if (pDataset != NULL)
// 	{
// 		FillReportDatasetRowMode(pData, pDataset);
// 		return;
// 	}

	//pData->m_nDataFill++; 

	//通讯命令中定义的扩展数据为Cell模式，以及其他项目的报告数据
	//此部分将来需要修改
	if (IsRptDataSingleMode(pData, pReport, &pTag))
	{
		pData->m_nDataFill += FillReportSingle(pData, pReport);
	}
	else
	{
		pData->m_nDataFill += FillReportGroup(pData, pReport, pTag);
	}
}

long CWordRptFillBase::FillReportGroup(CRptData *pData, CReport *pReport, CShortData * oTag)
{
	if (oTag->m_strDataTypeID == g_bstrCommCmdDataExModeID[COMMCMD_DATAEX_MODE_COL] )
	{
		FillReportGroupColMode(pData, pReport, oTag);
	}
	else if (oTag->m_strDataTypeID == g_bstrCommCmdDataExModeID[COMMCMD_DATAEX_MODE_ROW] )
	{
		FillReportGroupRowMode(pData, pReport, oTag);
	}

	return 1;
}

long CWordRptFillBase::Gb_RptFill_GetReportGroupDataCount(CCommCmd *pCommCmd, CReport *pReport)
{
	long nCount = 0;

	if (pReport->m_pRptDvmDataset != NULL)
	{
		nCount = pReport->m_pRptDvmDataset->GetCount();
	}

	return nCount;
}

void CWordRptFillBase::FillReportGroupRowMode(CRptData *pData, CReport *pReport, CShortData * oTagDataDef)
{

}

long CWordRptFillBase::FillReportSingle(CRptData *pData, CReport *pReport)
{
	long nDataFill = 0;
	CString strValue;// = GetReportString(pData, pReport);
	POS pos = pData->GetHeadPosition();
	CRptBkmk *pBkmk = NULL;

	//二维码文件
	if (pData->m_strID == CSafety::g_strQRCodeFileID)
	{
		CSafety *pSafety = (CSafety*)pReport->GetAncestor(GBCLASSID_SAFETY);
		strValue = _P_GetBinPath();

		if (pSafety == NULL)
		{
			return nDataFill;
		}

		strValue += pSafety->GetQRCodeFile();

		if (::IsFileExist(strValue))
		{
			while (pos != NULL)
			{
				pBkmk = (CRptBkmk*)pData->GetNext(pos);
				FillReportFile(strValue, pBkmk);
				nDataFill++;
				//pBkmk->m_strValue = strValue; //shaolei 19.07.25
			}
		}
	}
	else if (pData->m_strID == CMacroCharItems::g_strKeyCharGraph)
	{//特性曲线图
		CMacroCharItems *pMacroCharItems = (CMacroCharItems*)pReport->GetAncestor(GBCLASSID_MACROCHARITEMS);

		if (pMacroCharItems->IsAllMacroTestFinished())
		{
			//改进：特性曲线图在报告同级路径下，
			CString strFile = char_test_GetCharGraphFile();

			if (::IsFileExist(strFile))
			{
				while (pos != NULL)
				{
					pBkmk = (CRptBkmk*)pData->GetNext(pos);
					FillReportFile(strFile, pBkmk);
					nDataFill++;
					//pBkmk->m_strValue = strFile; //shaolei 19.07.25
				}
			}
		}		
	}
	else if (IsDataABitmapFile(pData, pReport, strValue))
	{//波形图以及其他图形文件
		while (pos != NULL)
		{
			pBkmk = (CRptBkmk*)pData->GetNext(pos);
			FillReportFile(strValue, pBkmk);
			nDataFill++;
			//pBkmk->m_strValue = strValue; //shaolei 19.07.25
		}
	}
	else if (IsDataAComtradeFile(pData, pReport, strValue))
	{//COMTRADE文件
		FillReportComtrdeFile(pData, pReport, strValue);
		nDataFill++;
	}
	else
	{
		CExBaseList *pReports = (CExBaseList*)pReport->GetParent();
		long nRptIndex = pReports->FindIndex(pReport);
		CMacroCharItems *pMacroCharItems = (CMacroCharItems*)pReport->GetAncestor(GBCLASSID_MACROCHARITEMS);

		if (pMacroCharItems != NULL)
		{
			nRptIndex = pMacroCharItems->GetMacroTestIndex((CMacroTest*)pReport->GetAncestor(GBCLASSID_MACROTEST));
		}

		//获得数据对象的合格状态
		COLORREF crData, crBack, crBackground, crBkBackground;

		long nFondBold = 0, nFondBoldBack;
		BOOL bTrue = TCC_GetReportDataColor(pData, pReport, crData, crBackground, nFondBold);

		if (bTrue)
		{
			crBack = m_crReport;
			nFondBoldBack = m_nInlegibleFontBold;
			crBkBackground = m_crReportBackground;

			m_crReport = crData;
			m_nInlegibleFontBold = nFondBold;
			m_crReportBackground = crBackground;
		}

		//遍历每个CRptData的标签，获取标签数据填写报告
		while (pos != NULL)
		{
			pBkmk = (CRptBkmk*)pData->GetNext(pos);
			strValue = GetReportString(pData, pBkmk, pReport);
			FillReport(strValue, pBkmk, nRptIndex, TRUE);

			if (IsSysBkmkDataProcess(pBkmk->m_strProcess))
			{
				if (strValue.GetLength() > 0)
				{
					nDataFill++;
				}
			}
			else
			{
				nDataFill++;
			}
			//pBkmk->m_strValue = strValue; //shaolei 19.07.25
		}

		if (bTrue)
		{
			m_crReport = crBack;
			m_nInlegibleFontBold = nFondBoldBack;  //2021-2-26  lijunqing
			m_crReportBackground = crBkBackground;
		}
	}
	return nDataFill;
}

BOOL CWordRptFillBase::GetReportDataFilePath(CRptData *pData, CValue *pValue, CString &strFile)
{
	strFile = pValue->m_strValue;

	if (::IsFileExist(strFile))
	{
		return TRUE;
	}

	strFile = Gb_GetReportFilePath(pData, FALSE);

	TCHAR ch = pValue->m_strValue.GetAt(0);

	if (ch == '\\' || ch == '/')
	{
		strFile += pValue->m_strValue.Mid(1);
	}
	else
	{
		strFile += pValue->m_strValue;
	}

	if (::IsFileExist(strFile))
	{
		return TRUE;
	}

	strFile = Gb_GetReportFilePath(pData, TRUE);
	strFile += pValue->m_strValue;

	if (::IsFileExist(strFile))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CWordRptFillBase::IsDataABitmapFile(CRptData *pData, CReport *pReport, CString &strFile)
{
	CString strID;
	strID = pData->m_strID;
	strID.MakeLower();

	CReports *pReports = (CReports *)pReport->GetParent();
	CGbItemBase *pItem = (CGbItemBase *)pReports->GetParent();

	if (strID.Find(_T("file")) < 0)
	{
		return FALSE;
	}

	CValue *pValue = (CValue*)pReport->FindReportData(pData->m_strID);

	if (pValue == NULL)
	{
		return FALSE;
	}

	CString strPistfix = ParseFilePostfix(pValue->m_strValue);
	strPistfix.MakeLower();

	if (strPistfix == _T("bmp") || strPistfix == _T("jpg") || strPistfix == _T("png"))
	{
		return GetReportDataFilePath(pData, pValue, strFile);
// 		strFile = Gb_GetReportFilePath(pData, FALSE);
// 		strFile += pValue->m_strValue;
// 
// 		if (::IsFileExist(strFile))
// 		{
// 			return TRUE;
// 		}
	}

	return FALSE;
}

BOOL CWordRptFillBase::IsDataAComtradeFile(CRptData *pData, CReport *pReport, CString &strFile)
{
	CString strID;
	strID = pData->m_strID;
	strID.MakeLower();

	if (strID.Find(_T("file")) < 0)
	{
		return FALSE;
	}

	CValue *pValue = (CValue*)pReport->FindReportData(pData->m_strID);

	if (pValue== NULL)
	{
		return FALSE;
	}

	CString strPistfix = ParseFilePostfix(pValue->m_strValue);
	strPistfix.MakeLower();

	if (strPistfix != _T("cfg") && strPistfix != _T("dat"))
	{
		return FALSE;
	}

	return GetReportDataFilePath(pData, pValue, strFile);
}

void CWordRptFillBase::FillReport(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor)
{
    CSmartTestBaseApp* pApp = g_theSmartTestBaseApp;

	if( !IsValidApp() || !IsValidDoc())
	{
		return;
	}

	if (pBkmk->IsFillMode_Cell())
	{
		m_pCurrBkmk = pBkmk;
		FillReport_Cell(strValue, pBkmk, nRptIndex, bSetColor);
		m_pCurrBkmk = NULL;
		return;
	}

	if (pBkmk->IsFillMode_Col())
	{
		m_pCurrBkmk = pBkmk;
		FillReport_Col(strValue, pBkmk, nRptIndex, bSetColor);
		m_pCurrBkmk = NULL;
		return;
	}

	if (pBkmk->IsFillMode_Row())
	{
		m_pCurrBkmk = pBkmk;
		FillReport_Row(strValue, pBkmk, nRptIndex, bSetColor);
		m_pCurrBkmk = NULL;
		return;
	}

	m_pCurrBkmk = pBkmk;
	FillReport_Cell(strValue, pBkmk, nRptIndex, bSetColor);
	m_pCurrBkmk = NULL;
}

long CWordRptFillBase::LocateReport(CRptData *pData)
{
	POS pos = pData->GetHeadPosition();
	CRptBkmk *pRptBkmk;

	while(pos != NULL)
	{
		pRptBkmk = (CRptBkmk*)pData->GetAt(pos);

		if (LocateReport(pRptBkmk) > 0)
		{
			break;
		}

		pData->GetNext(pos);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
void CWordRptFillBase::FillReportComtrdeFile(CRptData *pData, CReport *pReport, const CString &strFile)
{
#ifndef _PSX_QT_LINUX_
    POS pos = pData->GetHeadPosition();
	CRptBkmk *pBkmk = NULL;
	BOOL bNeedDraw = FALSE;

	while (pos != NULL)
	{
		pBkmk = (CRptBkmk*)pData->GetNext(pos);
		
		if (pBkmk->m_strDataAttrID == g_strDataAttrID_Value)
		{
			bNeedDraw = TRUE;
			break;
		}
	}

	CXRecordDrawComtradeDib oXRecordDrawComtradeDib;
	CRcdComtradeFile *pComtradeFile = NULL;
	long nWidth = 800, nHeight = 600;
	CString strValue;

	if (bNeedDraw)
	{
		pReport->FindReportData(XRECORD_DRAW_PARA_WIDTH, nWidth);
		pReport->FindReportData(XRECORD_DRAW_PARA_HEIGHT, nHeight);
		pComtradeFile = CRcdComtradeFileMngr::OpenComtradeFile(strFile);
		oXRecordDrawComtradeDib.InitByComtrade(pComtradeFile, nWidth, nHeight, FALSE);
		oXRecordDrawComtradeDib.ComtradeDib(m_pParentWnd);
	}

	pos = pData->GetHeadPosition();

	while (pos != NULL)
	{
		pBkmk = (CRptBkmk*)pData->GetNext(pos);
		m_pCurrBkmk = pBkmk;

		if (pBkmk->m_strDataAttrID == g_strDataAttrID_Value)
		{
			FillReportClipboard(pBkmk);
		}
		else
		{
			strValue = GetReportString(pData, pBkmk, pReport);
			FillReport(strValue, pBkmk, 0, TRUE);
		}
	}
#endif

	m_pCurrBkmk = NULL;
}
