#include "stdafx.h"
#include "UISftRsltWndMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/*
CUISftRsltWndInterface宽度计算：
	如果标题文本宽度大于150且小于300，作为2行文本，宽度为150+150+30=330
	如果小于150，作为一行
	大于300，标题文本取最大宽度150+150+30+5+150 = 485

调整算法
	1，计算所有row的第一列和第二列的最大宽度nMaxWidthCol1，nMaxWidthCol2
	2，将第一列根据nMaxWidthCol1进行调整，通过Edit控件对齐
	3，将第二列根据nMaxWidthCol2进行调整，通过Edit控件对齐
	4，根据是否有Infor控件进行第二次调整，col1向左对齐，col2向右对齐
*/

CUISftRsltWndMngr::CUISftRsltWndMngr()
{
}

CUISftRsltWndMngr::~CUISftRsltWndMngr()
{

}

void CUISftRsltWndMngr::CreateRsltEditWnd(CShortDatas* oReport,CWnd* pParentWnd,CRect rectWnd)
{
	if(oReport == NULL)
	{
		return;
	}
	
	long nCount = oReport->GetCount();
	if(nCount == 0)
	{
		return;
	}

	long nIndex = 0;
	CUISftRsltWndInterface* pRsltWnd = NULL;
	CShortData * oData = NULL;

	CRect rectRsltWnd = rectWnd;
	long nID = 20000;

	for(nIndex=0;nIndex<nCount;nIndex++)
	{
		oData = (CShortData*)oReport->GetAtIndex(nIndex);
		pRsltWnd = new CUISftRsltWndInterface;
		AddTail(pRsltWnd);
		pRsltWnd->CreateRsltEditWnd(oData,pParentWnd,nID);
	}
}

void CUISftRsltWndMngr::SetFont(CFont* pFont)
{
	POS pos = GetHeadPosition();
	CUISftRsltWndInterface *pRsltWnd = NULL;

	long nCount = GetCount();

	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		pRsltWnd->SetFont(pFont);
	}
}

long CUISftRsltWndMngr::GetHeight()
{
	long nHeight = 0;
	POS pos = GetHeadPosition();
	CUISftRsltWndInterface *pRsltWnd = NULL;

	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		nHeight += pRsltWnd->m_nHeight;
		nHeight += ResultWndGap;
	}

	nHeight += ResultWndGap;

	return nHeight;
}

BOOL CUISftRsltWndMngr::IsAllDataEntered()
{
	POS pos = GetHeadPosition();
	CUISftRsltWndInterface *pRsltWnd = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		
		CString strValue = pRsltWnd->m_oRsltData->m_strValue;
		if (strValue.GetLength() == 0)
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

void CUISftRsltWndMngr::CalSftRsltWndsSize()
{
	CUISftRsltWndInterface *pRsltWnd = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		pRsltWnd->CalResultWndSize();
	}
}

void CUISftRsltWndMngr::InitUISftRsltWndRows()
{
	m_oUISftRsltWndRows.DeleteAll();

	CUISftRsltWndInterface *pRsltWnd = NULL;
	POS pos = GetHeadPosition();
	CUISftRsltWndRow *pCurrRow = NULL;
	CUISftRsltWndRow *pRow = NULL;

	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		
		//if (pRsltWnd->m_nTitleWidth > CUISftRsltWndInterface::g_nResultTitleWidth * 2)
		if (pRsltWnd->IsSingle())
		{
			pRow = m_oUISftRsltWndRows.AddRow();
			pRow->SetSingle(pRsltWnd);
		}
		else
		{
			if (pCurrRow != NULL)
			{
				pCurrRow->SetRight(pRsltWnd);
				pCurrRow = NULL;
			}
			else
			{
				pCurrRow =  m_oUISftRsltWndRows.AddRow();
				pCurrRow->SetLeft(pRsltWnd); 
			}
		}
	}
}

long CUISftRsltWndMngr::GetInforTextWndWidthHeight()
{
	m_nInforWndWidth = 0;
	m_nInforWndHeight = 0;

	CString strText;
	CDC *pDC = m_pInforWnd->GetDC();
	CRect rc(0, 0, 0, 0);
	CFont *pFont = m_pInforWnd->GetFont();
	CFont *pOldFont = NULL;
	
	rc.right = UI_GetSftInforWndMaxWidth();
	pOldFont = pDC->SelectObject(pFont);
	m_pInforWnd->GetWindowText(strText);
	pDC->DrawText(strText, rc, DT_CALCRECT | DT_WORDBREAK| DT_LEFT | DT_EXTERNALLEADING);
	m_nInforWndWidth = rc.Width();
	long nMaxWidth = UI_GetSftInforWndMaxWidth();
	m_nInforWndHeight = rc.Height();

	if (m_nInforWndHeight > 400)
	{
		m_nInforWndHeight = 400;
	}

	//最大宽度
	m_nInforWndWidth = nMaxWidth;

	pDC->DrawText(_T(" "), rc, DT_CALCRECT | DT_WORDBREAK| DT_LEFT | DT_EXTERNALLEADING); 
	long nSingleH = rc.Height();

	if (m_nInforWndWidth > 0)
	{
		if (m_nInforWndHeight > nSingleH)
		{
			m_nInforWndWidth = nMaxWidth;
		}

		m_nInforWndWidth += ::GetSystemMetrics(SM_CXBORDER);
		m_nInforWndHeight = m_nInforWndHeight + nSingleH;
	}
	else
	{
		m_nInforWndHeight = 0;
	}

	m_nInforWndHeight = m_nInforWndHeight + nSingleH;
	pDC->SelectObject(pOldFont);
	m_pInforWnd->ReleaseDC(pDC);

	return m_nInforWndWidth;
}

void CUISftRsltWndMngr::AdjustY_InforWnd(long &yPos)
{
	if (m_nInforWndWidth > 0)
	{
		CRect rc;
		rc.left = CUISftRsltWndInterface::g_nResultWndGap;
		rc.top = yPos;
		rc.right = rc.left + m_nInforWndWidth;
		rc.bottom = rc.top + m_nInforWndHeight;

		m_pInforWnd->MoveWindow(rc, TRUE);
		m_pInforWnd->ShowWindow(SW_SHOW);

		yPos += m_nInforWndHeight;
		yPos += CUISftRsltWndInterface::g_nResultWndGap;
	}
	else
	{
		m_pInforWnd->MoveWindow(CRect(0, 0, 0, 0), TRUE);
		m_pInforWnd->ShowWindow(SW_HIDE);
	}
}

void CUISftRsltWndMngr::AdjustOnlyOne(long xPos, long nWidth)
{
	if (m_oUISftRsltWndRows.GetCount() > 1)
	{
		return;
	}

	if (m_oUISftRsltWndRows.GetCount() == 0)
	{
		return;
	}

// 	if (m_nInforWndWidth > 0)
// 	{
// 		return;
// 	}

	CUISftRsltWndRow *p = NULL;
	p = (CUISftRsltWndRow *)m_oUISftRsltWndRows.GetHead();
	p->AdjustOne(xPos, nWidth);
//	m_nInforWndWidth = max(m_nInforWndWidth, nWidth);
}

void CUISftRsltWndMngr::AdjustY(long &yPos)
{
	yPos += CUISftRsltWndInterface::g_nResultWndGap;

	AdjustY_InforWnd(yPos);

	POS pos = m_oUISftRsltWndRows.GetHeadPosition();
	CUISftRsltWndRow *p = NULL;

	while (pos != NULL)
	{
		p = (CUISftRsltWndRow *)m_oUISftRsltWndRows.GetNext(pos);
		p->AdjustY(yPos);
	}
}

void CUISftRsltWndMngr::AdjustY_MainWnd(long &yPos)
{
	CRect rc;

	//OK按钮位置调整
	m_pButtonOK->GetWindowRect(rc);
	m_pParentWnd->ScreenToClient(rc);
	long nMaxWidth = m_nSftWndWidth;//UI_GetSftWndMaxWidth();
	long nWidthButtuon = rc.Width();
	long nHeightButtuon = rc.Height();
	long xGap = (nMaxWidth - nWidthButtuon ) / 2;
	rc.top = yPos;
	rc.left = xGap;
	rc.bottom = rc.top + nHeightButtuon;
	rc.right = rc.left + nWidthButtuon;
	m_pButtonOK->MoveWindow(rc);

	yPos += nHeightButtuon;
	yPos += CUISftRsltWndInterface::g_nResultColGapWidth;
	yPos += ::GetSystemMetrics(SM_CYBORDER) * 2;
	yPos += ::GetSystemMetrics(SM_CYCAPTION);

	CRect rcTemp;
	m_pParentWnd->GetWindowRect(&rcTemp);
	rcTemp.right = rcTemp.left + m_nSftWndWidth/*UI_GetSftWndMaxWidth()*/ + ::GetSystemMetrics(SM_CXBORDER) * 2;
	rcTemp.bottom = rcTemp.top + yPos;

	m_pParentWnd->MoveWindow(rcTemp);
	m_pParentWnd->CenterWindow(NULL);

	ShowWindow();
}

void CUISftRsltWndMngr::AdjustAllWindows(CWnd* pParentWnd,CWnd* pInforWnd,CWnd* pButtonOK)
{
	m_pParentWnd = pParentWnd;
	m_pInforWnd = pInforWnd;
	m_pButtonOK = pButtonOK;
	long nW1 = 0;
	long nW2 = 0;
	long nW3 = 0;
	long nW4 = 0;

	//遍历各SftRsltWnd，计算窗体Width、Height
	CalSftRsltWndsSize();

	//将全部RsltWnd分列
	InitUISftRsltWndRows();

	//计算第1,2,single列最大宽度W1,W2,W3
	m_oUISftRsltWndRows.GetMaxWidth(nW1, nW2, nW3);

	//初始化infor窗口的宽度和高度
	GetInforTextWndWidthHeight();

	nW4 = m_nInforWndWidth;//UI_GetSftWndMaxWidth();
	nW4 = max(nW4, nW1 + nW2 + CUISftRsltWndInterface::g_nResultWndGap);
	nW4 = max(nW3, nW4);

	if (nW4 < 200)
	{
		nW4 = 200;
	}
// 	if (m_nInforWndWidth > 0)
// 	{
// 	}
// 	else
// 	{
// 	}

	//调整、对齐第一列（Gap,W1）
	m_oUISftRsltWndRows.AdjustCol1(CUISftRsltWndInterface::g_nResultWndGap, nW1);

	//调整、对齐第二列(W4-W2,W2)
	m_oUISftRsltWndRows.AdjustCol2(nW4 + CUISftRsltWndInterface::g_nResultWndGap * 2/*- nW2*/, nW2);

	//调整、对齐单列( W4-W3+Gap, W3)
	//m_oUISftRsltWndRows.AdjustColSingle(nW4 /*- nW3 + CUISftRsltWndInterface::g_nResultWndGap*/ , nW3);
	m_oUISftRsltWndRows.AdjustColSingle(nW4  + CUISftRsltWndInterface::g_nResultWndGap * 2 , nW3);

	//如果只有一个，则做特殊调整
	AdjustOnlyOne(CUISftRsltWndInterface::g_nResultWndGap, max(nW1, nW3) );

	m_nSftWndWidth = nW4 + CUISftRsltWndInterface::g_nResultWndGap * 2;
	m_nInforWndWidth =  nW4;

	//计算调整各Row在Y位置(W1+W2, bHasInfor)
	long yPos = 0;
	AdjustY(yPos);

	//主窗体位置调整AdjustMain(W4)
	AdjustY_MainWnd(yPos);

	return;
	CUISftRsltWndInterface *pRsltWnd = NULL;
	POS pos = GetHeadPosition();
	long nHeight = 0;
	long nWidthMax = 0;
	long nWidthMin = CUISftRsltWndInterface::g_nResultTitleWidth;

	//计算全部结果数据录入窗口的最大宽度、最小宽度、高度
	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		pRsltWnd->CalResultWndSize();
		nHeight += pRsltWnd->m_nHeight;
		nWidthMax = max(nWidthMax, pRsltWnd->m_nTitleWidth);
		nWidthMin = min(nWidthMin, pRsltWnd->m_nTitleWidth);
	}

	CRect rcTemp;
	pInforWnd->GetWindowRect(&rcTemp);
	m_pParentWnd->ScreenToClient(rcTemp);
	long nLines = ((CEdit*)pInforWnd)->GetLineCount();
	long nHeightInfor = rcTemp.bottom + CUISftRsltWndInterface::g_nResultWndGap*2;
	long nParentWidth = 0;
	long nBottom = 0;

	if (m_pInforWnd->GetWindowTextLength() == 0)
	{
		nHeightInfor = CUISftRsltWndInterface::g_nResultWndGap;
	}	

	BOOL bTwoCols = FALSE;

	if ( (nHeightInfor+nHeight > CUISftRsltWndInterface::g_nResultDlgMaxHeight)
		|| (nWidthMax < CUISftRsltWndInterface::g_nResultTitleWidth-20/*_GetOneResultWndWidth()*/))
	{
		if (GetCount() > 1)
		{
			bTwoCols = TRUE;
		}
	}

// 	if ( (nHeightInfor+nHeight > CUISftRsltWndInterface::g_nResultDlgMaxHeight)
// 		|| (nWidthMax < CUISftRsltWndInterface::g_nResultTitleMaxWidth-20/*_GetOneResultWndWidth()*/))
	if (bTwoCols)
	{//分成两列
		long nColTotalHeight = nHeight / 2;
		nParentWidth = AdjustAllWindowsToTwoColumns(nColTotalHeight, nHeightInfor, nBottom);
	}
	else
	{//只有一列
		nParentWidth = AdjustAllWindowsOneColumn(nHeightInfor, nBottom);
	}

	if (nParentWidth == 0)
	{//没有结果变量
		nParentWidth = 440;
	}

	if (nParentWidth < UI_GetOneResultWndMaxWidth())
	{
		nParentWidth = UI_GetOneResultWndMaxWidth();
	}

	//InforWnd位置调整
	long xGap = nParentWidth - rcTemp.Width() - ::GetSystemMetrics(SM_CXBORDER)*2;
	rcTemp.right = nParentWidth - ::GetSystemMetrics(SM_CXBORDER)*2 - rcTemp.left - CUISftRsltWndInterface::g_nResultColGapWidth;
	pInforWnd->MoveWindow(rcTemp);

	//OK按钮位置调整
	pButtonOK->GetWindowRect(rcTemp);
	m_pParentWnd->ScreenToClient(rcTemp);
	long nWidthButtuon = rcTemp.Width();
	xGap = (nParentWidth - nWidthButtuon ) / 2 - ::GetSystemMetrics(SM_CXBORDER) - CUISftRsltWndInterface::g_nResultColGapWidth;
	rcTemp.OffsetRect(xGap - rcTemp.left, nBottom - rcTemp.top+10);
	nBottom += rcTemp.Height() + ::GetSystemMetrics(SM_CYCAPTION) + 16;
	pButtonOK->MoveWindow(rcTemp);

	m_pParentWnd->GetWindowRect(&rcTemp);
	rcTemp.right += nParentWidth - rcTemp.Width();
	rcTemp.bottom += nBottom - rcTemp.Height() + ::GetSystemMetrics(SM_CYBORDER) + CUISftRsltWndInterface::g_nResultColGapWidth;
	m_pParentWnd->MoveWindow(rcTemp);
	m_pParentWnd->CenterWindow(NULL);

	ShowWindow();
}

long CUISftRsltWndMngr::AdjustAllWindowsToTwoColumns(long nColTotalHeight,long nYBegin,long &nBottom)
{
	long nParentWindth = 0;
	CUISftRsltWndInterface *pRsltWnd = NULL;
	POS pos = GetHeadPosition();
	POS posColumn2 = NULL;
	long nHeight = 0;
	long nWidthMax = 0;
	long nWidthMin = CUISftRsltWndInterface::g_nResultTitleWidth;
	CRect rc;

	//////////////////////////////////////////////////////////////////////////
	//第一列//////////////////////////////////////////////////////////////////
	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetAt(pos);
		nHeight += pRsltWnd->m_nHeight;
		nWidthMax = max(nWidthMax, pRsltWnd->m_nTitleWidth);
		GetNext(pos);

		if (nHeight >= nColTotalHeight)
		{
			posColumn2 = pos;
			break;
		}
	}

	//如果所有标题的最大宽度小于最大列宽度，则计算位移
	long nXOffset = min(nWidthMax, CUISftRsltWndInterface::g_nResultTitleWidth) 
		- CUISftRsltWndInterface::g_nResultTitleWidth + CUISftRsltWndInterface::g_nResultColGapWidth;
	nParentWindth = min(nWidthMax, CUISftRsltWndInterface::g_nResultTitleWidth);
	nParentWindth += CUISftRsltWndInterface::g_nResultEditWidth;
	nParentWindth += CUISftRsltWndInterface::g_nResultUnitWidth;
	nParentWindth += CUISftRsltWndInterface::g_nResultWndGap*2;
	nParentWindth += CUISftRsltWndInterface::g_nResultColGapWidth;

	if (nXOffset > -2)//如果偏差小于两个像素
	{
		nXOffset = 0;
	}

	long nYOffset = nYBegin;

	pos = GetHeadPosition();
	while (TRUE)
	{
		if (pos == NULL)
		{
			break;
		}
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		pRsltWnd->AdjustResultWndPosition(nXOffset, nYOffset, nWidthMax);
		nYOffset += pRsltWnd->m_nHeight + CUISftRsltWndInterface::g_nResultWndGap;

		if (pos == posColumn2)
		{
			break;
		}
	}

	nBottom = nYOffset;
	//////////////////////////////////////////////////////////////////////////
	//第二列//////////////////////////////////////////////////////////////////
	pos = posColumn2;
	nWidthMax = 0;

	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		nWidthMax = max(nWidthMax, pRsltWnd->m_nTitleWidth);
	}

	//如果所有标题的最大宽度小于最大列宽度，则计算位移
	nYOffset = nYBegin;
	pos = posColumn2;
	nXOffset = nParentWindth + nWidthMax - CUISftRsltWndInterface::g_nResultTitleWidth;
	nParentWindth += min(nWidthMax, CUISftRsltWndInterface::g_nResultTitleWidth);
	nParentWindth += CUISftRsltWndInterface::g_nResultEditWidth;
	nParentWindth += CUISftRsltWndInterface::g_nResultUnitWidth;
	nParentWindth += CUISftRsltWndInterface::g_nResultWndGap*2;
	nParentWindth += CUISftRsltWndInterface::g_nResultColGapWidth;

	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		pRsltWnd->AdjustResultWndPosition(nXOffset, nYOffset, nWidthMax);
		nYOffset += pRsltWnd->m_nHeight + CUISftRsltWndInterface::g_nResultWndGap;
	}

	nBottom = max(nYOffset, nBottom);
	return nParentWindth;
}

long CUISftRsltWndMngr::AdjustAllWindowsOneColumn(long nYBegin,long &nBottom)
{
	long nParentWindth = 0;
	CUISftRsltWndInterface *pRsltWnd = NULL;
	POS pos = GetHeadPosition();
	long nHeight = 0;
	long nWidthMax = 0;
	long nWidthMin = CUISftRsltWndInterface::g_nResultTitleWidth;
	CRect rc;

	//////////////////////////////////////////////////////////////////////////
	//第一列//////////////////////////////////////////////////////////////////
	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		nHeight += pRsltWnd->m_nHeight;
		nWidthMax = max(nWidthMax, pRsltWnd->m_nTitleWidth);
	}


	//如果所有标题的最大宽度小于最大列宽度，则计算位移
	long nXOffset = min(nWidthMax, CUISftRsltWndInterface::g_nResultTitleWidth) 
		- CUISftRsltWndInterface::g_nResultTitleWidth + CUISftRsltWndInterface::g_nResultColGapWidth;
	long nYOffset = nYBegin;
	pos = GetHeadPosition();
	nParentWindth += min(nWidthMax, CUISftRsltWndInterface::g_nResultTitleWidth);
	nParentWindth += CUISftRsltWndInterface::g_nResultEditWidth;
	nParentWindth += CUISftRsltWndInterface::g_nResultUnitWidth;
	nParentWindth += CUISftRsltWndInterface::g_nResultWndGap*2;
	nParentWindth += CUISftRsltWndInterface::g_nResultColGapWidth;

	if (nXOffset > -2)//如果偏差小于两个像素
	{
		nXOffset = 0;
	}

	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		pRsltWnd->AdjustResultWndPosition(nXOffset, nYOffset, nWidthMax);
		nYOffset += pRsltWnd->m_nHeight + CUISftRsltWndInterface::g_nResultWndGap;
	}

	nBottom = nYOffset;

	return nParentWindth;
}

void CUISftRsltWndMngr::ShowWindow()
{
	//m_pParentWnd->ShowWindow(SW_SHOW);
	m_pButtonOK->ShowWindow(SW_SHOW);
	if (m_pInforWnd->GetWindowTextLength() > 0)
	{
		m_pInforWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pInforWnd->ShowWindow(SW_HIDE);
	}

	POS pos = GetHeadPosition();
	CUISftRsltWndInterface *pRsltWnd = NULL;

	while (pos != NULL)
	{
		pRsltWnd = (CUISftRsltWndInterface*)GetNext(pos);
		pRsltWnd->ShowWindow();
	}
}