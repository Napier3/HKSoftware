#include "StdAfx.h"
#include "DsvViewDatasetGrid.h"
#include "../../XLanguage/XLanguageResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CDsvViewDatasetGrid::CDsvViewDatasetGrid()
{

}


CDsvViewDatasetGrid::~CDsvViewDatasetGrid(void)
{
	
}

void CDsvViewDatasetGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(4);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDsvViewDatasetGrid::InitGridTitle()
{
	CString cTempStr[4]={g_sLangTxt_SerNumber/*_T("ÐòºÅ")*/,g_sLangTxt_Name/*_T("Ãû³Æ")*/,_T("ID"),g_sLangTxt_Values/*_T("Öµ")*/};
	int iWidth[4]={60,200, 120, 60};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 4);
}	


void CDsvViewDatasetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	ASSERT (DVMCLASSID_CDVMDATA == nClassID);

	CDvmData *pDvmData = (CDvmData *)pData;

	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, &pDvmData->m_strName);
	Show_StaticString(pData, nRow, 2, &pDvmData->m_strID);
	Show_StaticString(pData, nRow, 3, &pDvmData->m_strValue);

#ifndef exbase_not_use_m_dwReserved
	if (pData->m_dwReserved == 0)
#else
	if (pData->m_dwItemData == 0)
#endif
	{
		SetItemFgColour(nRow, 1, RGB(255, 0, 0));
		SetItemFgColour(nRow, 2, RGB(255, 0, 0));
		SetItemFgColour(nRow, 3, RGB(255, 0, 0));
	}
#ifndef exbase_not_use_m_dwReserved
	else if (pData->m_dwReserved == 0x0FFFFFFF)
#else
	else if (pData->m_dwItemData == 0x0FFFFFFF)
#endif
	{
		SetItemFgColour(nRow, 1, RGB(128, 128, 0));
		SetItemFgColour(nRow, 2, RGB(128, 128, 0));
		SetItemFgColour(nRow, 3, RGB(128, 128, 0));
	}
	else
	{
		SetItemFgColour(nRow, 1, RGB(0, 0, 0));
		SetItemFgColour(nRow, 2, RGB(0, 0, 0));
		SetItemFgColour(nRow, 3, RGB(0, 0, 0));
	}

	nRow++;
}

void CDsvViewDatasetGrid::ViewDsvElement(CDsvElement *pDsvElement)
{
	long nRows = GetRowCount();
	long nRow = 0;

	for (nRow=1; nRow<nRows; nRow++)
	{
		SetItemBkColour(nRow, 1, RGB(255, 255, 255));
		SetItemBkColour(nRow, 2, RGB(255, 255, 255));
		SetItemBkColour(nRow, 3, RGB(255, 255, 255));
	}

	if (pDsvElement->m_listDsvMatch.GetCount() == 0)
	{
		Invalidate(FALSE);
		return;
	}

// 	CExBaseObject *p = pDsvElement->m_listDsvMatch.GetHead();
// 	long nBeginRow = m_pDatas->FindIndex(p) + 1;
// 	p = pDsvElement->m_listDsvMatch.GetTail();
// 	long nEndRow = m_pDatas->FindIndex(p) + 1;
// 
// 	for (nRow=nBeginRow; nRow<=nEndRow; nRow++)
// 	{
// 		SetItemBkColour(nRow, 1, RGB(153, 217, 234));
// 		SetItemBkColour(nRow, 2, RGB(153, 217, 234));
// 		SetItemBkColour(nRow, 3, RGB(153, 217, 234));
// 	}

	CExBaseObject *p = NULL;
	POS pos = pDsvElement->m_listDsvMatch.GetHeadPosition();

	while (pos != NULL)
	{
		p = pDsvElement->m_listDsvMatch.GetNext(pos);
		nRow = m_pDatas->FindIndex(p) + 1;

		SetItemBkColour(nRow, 1, RGB(153, 217, 234));
		SetItemBkColour(nRow, 2, RGB(153, 217, 234));
		SetItemBkColour(nRow, 3, RGB(153, 217, 234));
	}


	Invalidate(FALSE);
}

