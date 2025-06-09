#include "ChMapsGrid.h"
#include "../../../../Module/SttCmd/SttChMap.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

#define CHMAPS_GRID_COL_INDEX_NAME                    0
//#define CHMAPS_GRID_COL_INDEX_ID                      1
#define CHMAPS_GRID_COL_INDEX_ANALOG                  1
#define CHMAPS_GRID_COL_INDEX_DIGITAL                 2
#define CHMAPS_GRID_COL_INDEX_WEAK                    3


CChMapsGrid::CChMapsGrid(CSttChMaps *pChMaps, QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_oSttChMaps = pChMaps;
}

CChMapsGrid::~CChMapsGrid()
{

}

void CChMapsGrid::InitGrid()
{
// 	SetListMode(TRUE);
// 	SetColumnCount(GROUPRIGHTS_TABLE_COLS);
// 	SetFixedRowCount(1);
// 	SetFixedColumnCount(1);
 	InitGridTitle();
	SetEditable(TRUE);
}

void CChMapsGrid::InitGridTitle()
{
	CString astrGridTitle[CHMAPS_GRID_COLS] = {/*_T("名称")*/g_sLangTxt_Name,/*_T("软件资源标识"),*//*_T("模拟量通道")*/g_sLangTxt_ChMaps_AnalogCh,/*_T("数字量通道")*/g_sLangTxt_ChMaps_DigitalCh,/*_T("弱信号通道")*/g_sLangTxt_ChMaps_WeekCh};
	int  iColType[CHMAPS_GRID_COLS]={QT_GVET_NOEDIT, /*QT_GVET_NOEDIT,*/QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[CHMAPS_GRID_COLS]={130,/* 100,*/ 130, 130, 130};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CHMAPS_GRID_COLS);
//	SetFont(g_pGlobalFont11);
}

void CChMapsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	CSttChMap *pChMap = (CSttChMap *)pData;
	Show_String(pData,nRow,0,&pChMap->m_strName,EndEditCell_String); 
//	Show_StaticString(pData,nRow,1,&pChMap->m_strID); 
	CString strAnalogString,strDigString,strWeakString;
	strAnalogString = pChMap->GetHdChsString(STT_MODULETYPE_ID_ANALOG);
	strDigString = pChMap->GetHdChsString(STT_MODULETYPE_ID_DIGITAL);
	strWeakString = pChMap->GetHdChsString(STT_MODULETYPE_ID_WEEK);

	Show_String(pData,nRow,1,&strAnalogString,EndEditCell_ChMapsString); 
	Show_String(pData,nRow,2,&strDigString,EndEditCell_ChMapsString); 
	Show_String(pData,nRow,3,&strWeakString,EndEditCell_ChMapsString); 
 	nRow++;
}

void CChMapsGrid::EndEditCell_ChMapsString (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CSttChMap *pChMap = (CSttChMap*)pVCellData->pObj;
	CString strText = pCell->text();
	CString strPrevText;
	QGV_ITEM* pPrevCell = (QGV_ITEM*)pGrid->item(nRow, nCol - 1);
	if (pPrevCell)
	{
		strPrevText = pPrevCell->text();
	}

	if (nCol == CHMAPS_GRID_COL_INDEX_ANALOG)
	{
		pChMap->InitHdChs_ByString(strText,STT_MODULETYPE_ID_ANALOG);
	}
	else if (nCol == CHMAPS_GRID_COL_INDEX_DIGITAL)
	{
		pChMap->InitHdChs_ByString(strText,STT_MODULETYPE_ID_DIGITAL);
	}
	else if (nCol == CHMAPS_GRID_COL_INDEX_WEAK)
	{
		pChMap->InitHdChs_ByString(strText,STT_MODULETYPE_ID_WEEK);
	}

	pCell->setText(strText);

	CChMapsGrid *chMapsGrid = dynamic_cast<CChMapsGrid*>(pGrid);
	if (chMapsGrid)
	{
		chMapsGrid->SendEditCellHasChanged(nRow, nCol, strPrevText);
	}
}

void CChMapsGrid::SendEditCellHasChanged(int nRow, int nCol, CString strText)
{
	if (nCol == CHMAPS_GRID_ANALOG)
	{
		if (strText.contains("U"))
		{
			emit sig_AnalogUEndEditCellHasChanged(m_oSttChMaps);
		}
		else if (strText.contains("I"))
		{
			emit sig_AnalogIEndEditCellHasChanged(m_oSttChMaps);
		}
	}
	else if (nCol == CHMAPS_GRID_WEEK)
	{
		emit sig_WeakEndEditCellHasChanged(m_oSttChMaps);

	}
}

void CChMapsGrid::slot_UpdateDefaultMaps(long nType, int nMoudleTag, int nGroupIndex, int nChBeginIndex,int nselect, bool bIsAppend)
{
	CSttChMap *pSttChMap = NULL;
	CString strSoftRsID, strText;
	nGroupIndex = (nGroupIndex - 1) * 3 + 1;

	if ((nType == AnalogMoudle_U) || (nType == AnalogMoudle_I))
	{
		for (int nIndex = nChBeginIndex; nIndex < 3 + nChBeginIndex; nIndex++)//三个一组
		{
			strSoftRsID.Format(_T("%c%ld"),(nType == AnalogMoudle_U ? 'U' : 'I'), nIndex);
			pSttChMap = m_oSttChMaps->GetChMap(strSoftRsID);
			if (pSttChMap == NULL)
			{
				break;
			}
			CString strAnalogString;
			strAnalogString = pSttChMap->GetHdChsString(STT_MODULETYPE_ID_ANALOG);
			if (nselect == 0)
			{
				strText.Format(_T("%c%d_%d;"), (nType == AnalogMoudle_U ? 'U' : 'I'), nMoudleTag, nGroupIndex);
				if (bIsAppend)//同一列中有其他的映射状态则追加映射通道
				{
					strAnalogString += strText;
				}
				else//反之则只放入当前的映射通道
				{
					strAnalogString = strText;
				}
				pSttChMap->InitHdChs_ByString(strAnalogString,STT_MODULETYPE_ID_ANALOG);
			}
			else if (nselect == 1)
			{
				if (bIsAppend)
				{
					strText.Format(_T("%c%d_%d;"), (nType == AnalogMoudle_U ? 'U' : 'I'), nMoudleTag, nGroupIndex);
					strAnalogString.Replace(strText, _T(""));
					pSttChMap->InitHdChs_ByString(strAnalogString,STT_MODULETYPE_ID_ANALOG);
				}
				else
				{
					strText = _T("");
					pSttChMap->InitHdChs_ByString(strText,STT_MODULETYPE_ID_ANALOG);
				}

			}
			nGroupIndex++;
		}

	}
	else if ((nType == WeakMoudle_U) || (nType == WeakMoudle_I))
	{
		for (int nIndex = nChBeginIndex; nIndex < 3 + nChBeginIndex; nIndex++)
		{
			strSoftRsID.Format(_T("%c%ld"),(nType == WeakMoudle_U ? 'U' : 'I'), nIndex);
			pSttChMap = m_oSttChMaps->GetChMap(strSoftRsID);
			if (pSttChMap == NULL)
			{
				break;
			}
			CString strWeakString;
			strWeakString = pSttChMap->GetHdChsString(STT_MODULETYPE_ID_WEEK);
			if (nselect == 0)
			{
				strText.Format(_T("Uw%d_%d;"), nMoudleTag, nGroupIndex);
				if (bIsAppend)//同一列中有其他的映射状态则追加映射通道
				{
					strWeakString += strText;
				}
				else//反之则只放入当前的映射通道
				{
					strWeakString = strText;
				}
				pSttChMap->InitHdChs_ByString(strWeakString,STT_MODULETYPE_ID_WEEK);
			}
			else if (nselect == 1)
			{
				if (bIsAppend)
				{
					strText.Format(_T("Uw%d_%d;"), nMoudleTag, nGroupIndex);
					strWeakString.Replace(strText, _T(""));
					pSttChMap->InitHdChs_ByString(strWeakString,STT_MODULETYPE_ID_WEEK);
				}
				else
				{
					strText = _T("");
					pSttChMap->InitHdChs_ByString(strText,STT_MODULETYPE_ID_WEEK);
				}

			}

			nGroupIndex++;
		}
	}
	
	ShowDatas(m_oSttChMaps);
}