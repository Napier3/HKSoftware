#include "IecCfgGoutChannelsGrid.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../../XLangResource_Native.h"


CIecCfgGoutChannelsGrid::CIecCfgGoutChannelsGrid(QWidget* pparent):CIecCfgChsGridBase(pparent)
{
}

CIecCfgGoutChannelsGrid::~CIecCfgGoutChannelsGrid()
{

}


void CIecCfgGoutChannelsGrid::InitGrid()
{
	CIecCfgChsGridBase::InitGrid();
	m_pValue_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(3,m_pValue_DelegBase);
	SetEditable(TRUE);
}

void CIecCfgGoutChannelsGrid::InitGridTitle()
{
	CString strChDescription,strChType,strChMaps,strInitValue;
	xlang_GetLangStrByFile(strChDescription,"IEC_ChDescription");
	xlang_GetLangStrByFile(strChType,"IEC_ChType");
	xlang_GetLangStrByFile(strChMaps,"IEC_ChMaps");
	xlang_GetLangStrByFile(strInitValue,"IEC_InitValue");

	CString astrGridTitle[IECCFGSMVGOUTCHANNELS_GRID_COLS] = {strChDescription,strChType,strChMaps,strInitValue,g_sLangTxt_IEC_DescExternal};
	int iGridWidth[IECCFGSMVGOUTCHANNELS_GRID_COLS]={300, 150,150,150,300};

	//20230725 suyang 适配分辨率 1024X768
#ifdef _PSX_QT_WINDOWS_

		iGridWidth[0] = 300;
#endif

	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMVGOUTCHANNELS_GRID_COLS);
}

void CIecCfgGoutChannelsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFGGOUTCH)
	{
		return;
	}

	CIecCfgGoutCh *pIecCfgGoutCh = (CIecCfgGoutCh*)pData;
	Show_StaticString(pData,nRow,0,&pIecCfgGoutCh->m_strName);
	Show_DataType_Val(pData, nRow, 1,iecfg_GooseChDataType, &pIecCfgGoutCh->m_strDataType,EndEditCell_GoutChSelChangged);
	UpdateData_ByDataType(pIecCfgGoutCh,nRow);

	if (pIecCfgGoutCh->m_strDescExternal.IsEmpty())
	{
		Show_StaticString(pData,nRow,4,_T("---"));
	} 
	else
	{
		Show_StaticString(pData,nRow,4,&pIecCfgGoutCh->m_strDescExternal);
	}

  	nRow++;
}

void CIecCfgGoutChannelsGrid::EndEditCell_GoutChSelChangged (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;

	if (nCol == 1)
	{
		pGoutCh->CheckDefautValue();
		((CIecCfgGoutChannelsGrid*)pGrid)->UpdateData_ByDataType(pGoutCh,nRow);
//		emit ((CIecCfgGoutChannelsGrid*)pGrid)->/*sig_Iec61850Cfg_Changed*/sig_GoutValue_Changed();
	}
	else if (nCol == 2)
	{
		((CIecCfgGoutChannelsGrid*)pGrid)->UpdateData_ByChMap(pGoutCh,nRow);
//		emit ((CIecCfgGoutChannelsGrid*)pGrid)->/*sig_Iec61850Cfg_Changed*/sig_GoutValue_Changed();
	}
	else if (nCol == 3)
	{
//		((CIecCfgGoutChannelsGrid*)pGrid)->UpdateData_Value(pGoutCh,nRow);
//		emit ((CIecCfgGoutChannelsGrid*)pGrid)->sig_GoutValue_Changed();
	}
}

void CIecCfgGoutChannelsGrid::UpdateData_ByDataType(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{
		if (pGoutCh->m_strDataType == _T("BOOLEAN"))
		{
			Show_DataType_Val(pGoutCh,nRow,2,g_strGsChDtID_goose_out_ch_single,&pGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		} 
		else if (pGoutCh->m_strDataType == _T("Dbpos"))
		{
			Show_DataType_Val(pGoutCh,nRow,2,g_strGsChDtID_goose_out_ch_double,&pGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		} 
		else
		{
			Show_StaticString(pGoutCh,nRow,2,_T("--"));  
		}

		Show_StaticString(pGoutCh,nRow,3,_T("--")/*&pGoutCh->m_strDefaultValue*/); 
		return;
	}

	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		Show_DataType_Val(pGoutCh,nRow,2,g_strGsChDtID_goose_out_ch_single,&pGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		Show_DataType_Val(pGoutCh,nRow,3,g_strGsChDtID_goose_out_ch_single_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pGoutCh,nRow,2,g_strGsChDtID_goose_out_ch_double,&pGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		Show_DataType_Val(pGoutCh,nRow,3,g_strGsChDtID_goose_out_ch_double_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
	} 
	else
	{
		Show_StaticString(pGoutCh,nRow,2,_T("--")); 
		pGoutCh->CheckDefautValue();
		Show_String(pGoutCh,nRow,3,&pGoutCh->m_strDefaultValue,EndEditCell_AppCh_GoutDefaultValue); 
	}
}


void CIecCfgGoutChannelsGrid::UpdateData_ByChMap(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{

		Show_StaticString(pGoutCh,nRow,3,_T("--")/*&pGoutCh->m_strDefaultValue*/); 
		return;
	}

	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		Show_DataType_Val(pGoutCh,nRow,3,g_strGsChDtID_goose_out_ch_single_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pGoutCh,nRow,3,g_strGsChDtID_goose_out_ch_double_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
	} 
	else
	{
		Show_String(pGoutCh,nRow,3,&pGoutCh->m_strDefaultValue,EndEditCell_AppCh_GoutDefaultValue); 
	}
}

void CIecCfgGoutChannelsGrid::EndEditCell_AppCh_GoutDefaultValue (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVellData->pObj;
	ASSERT (pGoutCh != NULL);
	CString strCellText = pCell->text();
	CString strOldDefaultValue = pGoutCh->m_strDefaultValue;
	pGoutCh->m_strDefaultValue = strCellText;
	pGoutCh->CheckDefautValue();

	if (strCellText != pGoutCh->m_strDefaultValue)
	{
		pCell->setText(pGoutCh->m_strDefaultValue);
	}

// 	if (strOldDefaultValue != pGoutCh->m_strDefaultValue)
// 	{
// 		emit ((CIecCfgGoutChsGrid*)pGrid)->sig_GoutValue_Changed();
// 	}
}

void CIecCfgGoutChannelsGrid::GridDoubleClicked_ShowKeyBoard(int nRow,int nCol)
{
	if ((nCol != 0)&&(nCol != 3))
	{
		return;
	}
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	QString strValue = pItem->text();

	if (nCol == 0)
	{
		GetEngWidgetBoard_DigitData(strValue, parentWidget()->parentWidget());
		pItem->setText(strValue);
	}
	else
	{
		PEXBASECELLDATA pVellData = (_ExBaseCellData*)pItem->lParam;
		ASSERT (pVellData != NULL);
		CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVellData->pObj;
		ASSERT (pGoutCh != NULL);

		if (pGoutCh->m_strAppChID.Find("bout") != -1)
		{
			return;
		}

		if (pGoutCh->m_strDataType == _T("Quality"))
		{
			GetEngWidgetBoard_DigitData(strValue, parentWidget()->parentWidget());
			pItem->setText(strValue);
		} 
		else if ((pGoutCh->m_strDataType == _T("BOOLEAN"))||(pGoutCh->m_strDataType == _T("Dbpos")))
		{
		}
		else
		{
			GetWidgetBoard_DigitData(4,strValue,pItem, parentWidget()->parentWidget());
// 			pItem->setText(strValue);
		}
	}
	

}


