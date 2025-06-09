//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GridCharElement.cpp  CGridGbtCommCmdEdit


#include "stdafx.h"
#include "GridGbtCommCmdEdit.h"
#include "..\UI\GbDvmComboBox.h"
#include "..\XLanguageResourceAts.h"
CGridGbtCommCmdEdit::CGridGbtCommCmdEdit()
{
	//初始化属性

	//初始化成员变量
}

CGridGbtCommCmdEdit::~CGridGbtCommCmdEdit()
{
	m_listDatasets.RemoveAll();
}


void CGridGbtCommCmdEdit::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(GBTCMDEDIT_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridGbtCommCmdEdit::InitGridTitle()
{
	CString astrTitle[GBTCMDEDIT_COLS] = {/*_T("编号")*/g_sLangTxt_Index,/*_T("名称")*/g_sLangTxt_Name,_T("ID"),/*_T("数据集")*/g_sLangTxt_DataSet};

	int iWidthGrid[GBTCMDEDIT_COLS]={40,100,100, 200};

	CExBaseListGrid::InitGridTitle(astrTitle, iWidthGrid, GBTCMDEDIT_COLS);
}


long CGridGbtCommCmdEdit::GetDatasCount()
{
	long nCount = m_pDatas->GetCount();
	POS pos = m_pDatas->GetHeadPosition();
	CGbtCommCmdItemEdit *pCmdEdit = NULL;

	while (pos != NULL)
	{
		pCmdEdit = (CGbtCommCmdItemEdit *)m_pDatas->GetNext(pos);
		nCount += pCmdEdit->GetCount();
	}

	return nCount;
}

void CGridGbtCommCmdEdit::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CGbtCommCmdItemEdit *pGbtCommCmdItemEdit = (CGbtCommCmdItemEdit*)pData;

	Show_Index(pGbtCommCmdItemEdit, nRow, GBTCMDEDIT_COL_INDEX);
	Show_StaticString(pGbtCommCmdItemEdit, nRow, GBTCMDEDIT_COL_NAME, &pGbtCommCmdItemEdit->m_strName);
	Show_StaticString(pGbtCommCmdItemEdit, nRow, GBTCMDEDIT_COL_ID, &pGbtCommCmdItemEdit->m_strID);
	Show_ComboBox(pGbtCommCmdItemEdit, nRow, GBTCMDEDIT_COL_DATASET, &pGbtCommCmdItemEdit->m_strDatasetPath, EndEditCell_CmbDataset);

	nRow++;

	POS pos = pGbtCommCmdItemEdit->GetHeadPosition();
	CGbtCommCmdItemEditExpand *pExpand = NULL;

	while (pos != NULL)
	{
		pExpand = (CGbtCommCmdItemEditExpand *)pGbtCommCmdItemEdit->GetNext(pos);
		Show_Index(pExpand, nRow, GBTCMDEDIT_COL_INDEX);
		Show_Check(pExpand, nRow, GBTCMDEDIT_COL_ID, &pExpand->m_bSelect);
		Show_ComboBox(pExpand, nRow, GBTCMDEDIT_COL_DATASET, &pExpand->m_strID, EndEditCell_CmbExpandDataset);
		nRow++;
	}
}

CString CGridGbtCommCmdEdit::GetMmsDsKey(CStringArray &astrMmsDsKey)
{
	CExBaseObject *pObj = GetCurrSelData(GBTCMDEDIT_COL_DATASET);
	CGbtCommCmdItemEdit *pCmdEdit = NULL;

	if (pObj->GetClassID() == GBTWZDCLASSID_COMMCMDEDIT)
	{
		pCmdEdit = (CGbtCommCmdItemEdit *)pObj;
	}
	else
	{
		pCmdEdit = (CGbtCommCmdItemEdit *)pObj->GetParent();
	}

	CCommCmd *pCommCmd = (CCommCmd*)pCmdEdit->m_pCommCmdRef;
	CGbCommCmdMms *pCmdMms = pCommCmd->GetGbCommCmd();

	CString strKey = Gb_GetDataSetKey(pCmdMms->m_strGbDataID);

	if (strKey == g_strDataSetIDKey[DSID_dsAll])
	{
		return _T("");
	}

	if (strKey == g_strDataSetIDKey[DSID_dsReport])
	{
		return _T("");
	}

	if (strKey == g_strDataSetIDKey[DSID_dsFile])
	{
		return _T("");
	}

	if (strKey == g_strDataSetIDKey[DSID_dsNone])
	{
		return _T("");
	}

	astrMmsDsKey.Add(strKey);

	return strKey;
}

void  CGridGbtCommCmdEdit::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)
{
	CComboBox *pCmbBox = (CComboBox*)cltWnd;
	CGbtCommCmdItemEditMngr *pMngr = (CGbtCommCmdItemEditMngr*)m_pDatas;
	CDevice *pDevice = pMngr->m_pGuideBookDest->GetDevice();
	CGbtCommCmdItemEdit *pCmdEdit = (CGbtCommCmdItemEdit*)GetCurrSelData(GBTCMDEDIT_COL_DATASET);
	
	//GbDvmCmb_ShowDvmTree(pDevice, pCmbBox, GetMmsDsKey());//->ShowDvmTree(pDevice);
	CStringArray astrMmsDsKey;
	GetMmsDsKey(astrMmsDsKey);
	GbDvmCmb_ShowDvmTree(pDevice, pCmbBox, astrMmsDsKey);

	long nCount = pCmbBox->GetCount();
	long nIndex = 0;
	long nIndexFind = -1;
	CExBaseObject *pObj = NULL;
	m_listDatasets.RemoveAll();

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pObj = (CExBaseObject*)pCmbBox->GetItemDataPtr(nIndex);
		m_listDatasets.AddTail(pObj);

		if (pObj->GetClassID() == GBCLASSID_DATASET)
		{
			CDataSet *pDataset = (CDataSet*)pObj;
			
			if (pCmdEdit->m_strDatasetPath == pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE))
			{
				nIndexFind = nIndex;
			}
		}
	}

//	pCmbBox->SetCurSel(nIndexFind);
}

void CGridGbtCommCmdEdit::EndEditCell_CmbDataset(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGridGbtCommCmdEdit *pCGridGbtCommCmdEdit = (CGridGbtCommCmdEdit*)pGrid;
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pString != NULL);
	CDataSet *pDataset = (CDataSet*)pCGridGbtCommCmdEdit->m_listDatasets.GetAtIndex(pCell->dwValue);
	CGbtCommCmdItemEdit *pCmdEdit = (CGbtCommCmdItemEdit*)pVellData->pObj;

	if (pDataset == NULL)
	{
	}
	else
	{
		if (pDataset->GetClassID() == GBCLASSID_DATASET)
		{
			pCmdEdit->m_strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
			CCommCmd *pCommCmd = (CCommCmd*)pCmdEdit->m_pCommCmdRef;
			pCommCmd->GetCmd()->m_strDatasetPath = pCmdEdit->m_strDatasetPath;
		}
	}

	pGrid->SetItemText(nRow, nCol, pCmdEdit->m_strDatasetPath);

	pGrid->AutoSizeColumn(nCol);
	pGrid->ResetScrollBars();
	pGrid->InvalidateGrid(FALSE);
	pCGridGbtCommCmdEdit->GetParent()->PostMessage(WM_COMMCMDEDIT_DATA_CHANGED, nRow,nCol);
}


void CGridGbtCommCmdEdit::EndEditCell_CmbExpandDataset(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGridGbtCommCmdEdit *pCGridGbtCommCmdEdit = (CGridGbtCommCmdEdit*)pGrid;
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pString != NULL);
	CDataSet *pDataset = (CDataSet*)pCGridGbtCommCmdEdit->m_listDatasets.GetAtIndex(pCell->dwValue);
	CGbtCommCmdItemEditExpand *pCmdEditExpand = (CGbtCommCmdItemEditExpand*)pVellData->pObj;

	if (pDataset == NULL)
	{
	}
	else
	{
		if (pDataset->GetClassID() == GBCLASSID_DATASET)
		{
			pCmdEditExpand->m_strID = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
		}
	}

	pGrid->SetItemText(nRow, nCol, pCmdEditExpand->m_strID);

	pGrid->AutoSizeColumn(nCol);
	pGrid->ResetScrollBars();
	pGrid->InvalidateGrid(FALSE);
	pCGridGbtCommCmdEdit->GetParent()->PostMessage(WM_COMMCMDEDIT_DATA_CHANGED, nRow,nCol);
}

