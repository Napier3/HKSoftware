#include "IecCfgSmv92ChsGrid.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../SttIecQualitySetDialog.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../../Module/XLangResource_Native.h"
#include "../../../XLangResource_Native.h"

CIecCfgSmv92ChsGrid::CIecCfgSmv92ChsGrid(QWidget* pparent):CIecCfgChsGridBase(pparent)
{
}

CIecCfgSmv92ChsGrid::~CIecCfgSmv92ChsGrid()
{

}

void CIecCfgSmv92ChsGrid::InitGrid()
{
 	CIecCfgChsGridBase::InitGrid();
	m_pChQualityDelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(3,m_pChQualityDelegate);
	SetEditable(TRUE);

	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_Quality_doubleClicked(int,int)));

}

void CIecCfgSmv92ChsGrid::InitGridTitle()
{
	CString strChDescription,strChType,strChMaps,strQuality;
	xlang_GetLangStrByFile(strChDescription,"IEC_ChDescription");
	xlang_GetLangStrByFile(strChType,"IEC_ChType");
	xlang_GetLangStrByFile(strChMaps,"IEC_ChMaps");
	xlang_GetLangStrByFile(strQuality,"IEC_Quality");


	CString astrGridTitle[IECCFGSMV92CHS_GRID_COLS] = {strChDescription,strChType,strChMaps,strQuality,g_sLangTxt_IEC_DescExternal};
	int iGridWidth[IECCFGSMV92CHS_GRID_COLS]={300, 150,150,150,300};

	//20230725 suyang 适配分辨率 1024X768
#ifdef _PSX_QT_WINDOWS_

		iGridWidth[0] = 300;

#endif

	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMV92CHS_GRID_COLS);
}

void CIecCfgSmv92ChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFG92CH)
	{
		return;
	}

	CIecCfg92Ch *pIecCfg92Ch = (CIecCfg92Ch*)pData;

	long nCurrChIndex = pIecCfg92Ch->m_nIndex ;

    if (pIecCfg92Ch->m_strName.IsEmpty() || pIecCfg92Ch->m_strName.Find(_T("Ch")) >= 0)//cl20231027设置通道缺省项
	{
		pIecCfg92Ch->m_strName.Format(/*_T("通道%d")*/g_sLangTxt_Native_ChnN,nCurrChIndex+1);
	}

	Show_StaticString(pData,nRow,0,&pIecCfg92Ch->m_strName);
	Show_DataType_Val(pData, nRow, 1,iecfg_Smv92ChDataType, &pIecCfg92Ch->m_strChType,EndEditCell_Smv92ChSelChangged);
	UpdateData_ByDataType(pIecCfg92Ch,nRow);
// 	Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType, &pIecCfg92Ch->m_strAppChID);
 	Show_Hex(pData, nRow, 3, &pIecCfg92Ch->m_nQuality, 4,false);

	if (pIecCfg92Ch->m_strDescExternal.IsEmpty())
	{
		Show_StaticString(pData,nRow,4,_T("---"));
	}
	else
	{
		Show_StaticString(pData,nRow,4,&pIecCfg92Ch->m_strDescExternal);
	}

  	nRow++;
}

void CIecCfgSmv92ChsGrid::EndEditCell_Smv92ChSelChangged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfg92Ch *pIecCfgSmv92Ch = (CIecCfg92Ch*)pVCellData->pObj;
	((CIecCfgSmv92ChsGrid*)pGrid)->UpdateData_ByDataType(pIecCfgSmv92Ch,nRow);
}

void CIecCfgSmv92ChsGrid::UpdateData_ByDataType(CIecCfg92Ch *pIecCfgSmv92Ch,int nRow)
{
	if (pIecCfgSmv92Ch->m_strChType == iecfg_SmvChDataType_Val_Vol)
	{
		Show_DataType_Val(pIecCfgSmv92Ch, nRow, 2,iecfg_SmvAppChDataType_U, &pIecCfgSmv92Ch->m_strAppChID);
	} 
	else if (pIecCfgSmv92Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)
	{
		Show_DataType_Val(pIecCfgSmv92Ch, nRow, 2,iecfg_SmvAppChDataType_I, &pIecCfgSmv92Ch->m_strAppChID);
	} 
	else if (pIecCfgSmv92Ch->m_strChType == iecfg_SmvChDataType_Val_UTCTime)
	{
		Show_DataType_Val(pIecCfgSmv92Ch, nRow, 2,iecfg_SmvAppChDataType_T, &pIecCfgSmv92Ch->m_strAppChID);
	} 
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_SMV92map.GetString(),pIecCfgSmv92Ch->m_strChType.GetString());
	}
}

void CIecCfgSmv92ChsGrid::UpdateDatas_Quality()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	DisConnectAll_SigSlot();
	CIecCfg92Ch *pIecCfg92Ch = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行

	while (pos != NULL)
	{
		pIecCfg92Ch = (CIecCfg92Ch*)m_pDatas->GetNext(pos);
		Show_Hex(pIecCfg92Ch, nRowIndex, 3, &pIecCfg92Ch->m_nQuality, 4,false);
		nRowIndex++;
	}

	ConnectAll_SigSlot();
}

void CIecCfgSmv92ChsGrid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
{
	if (nCol != 0)
	{
		return;
	}
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	QString strValue = pItem->text();
	GetEngWidgetBoard_DigitData(strValue, parentWidget()->parentWidget());
	pItem->setText(strValue);

// 	WidgetKeyboard dlg(this);
// 	dlg.m_InputString = pItem->text();
// 	dlg.showToEdit();
// 	if (dlg.exec() == QDialog::Accepted)
// 	{
// 		pItem->setText(dlg.m_InputString);
// 	}
}

void CIecCfgSmv92ChsGrid::slot_Quality_doubleClicked( int nRow,int nCol )
{
	if (nCol !=3)
	{
		return;
	}

	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_
    if (IsScrollMoving())
	{
		return;
	}
#endif

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pItem->lParam;
	CIecCfg92Ch *pIecCfgSmv92Ch = (CIecCfg92Ch*)pVCellData->pObj;

	if (pIecCfgSmv92Ch == NULL)
	{
		return;
	}

	QSttIecQualitySetDialog oSttIecQualitySetDlg(pIecCfgSmv92Ch,this);
	oSttIecQualitySetDlg.setFont(parentWidget()->font());

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oSttIecQualitySetDlg);
	if (oSttIecQualitySetDlg.exec() ==  QDialog::Accepted)
	{
		UpdateDatas_Quality();
	}
	QSoftKeyBoard::ReAttachObj();
#else
	if (oSttIecQualitySetDlg.exec() ==  QDialog::Accepted)
	{
		UpdateDatas_Quality();
	}
#endif
}


