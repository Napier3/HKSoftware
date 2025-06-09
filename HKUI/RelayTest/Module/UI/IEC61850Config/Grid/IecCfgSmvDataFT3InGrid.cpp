#include "IecCfgSmvDataFT3InGrid.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg6044Data.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonInData.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"

CIecCfgSmvDataFT3InGrid::CIecCfgSmvDataFT3InGrid(QWidget* pparent):CIecCfgDataGridBase(pparent)
{
	m_pDelayTimeDelegate = NULL;
	m_pSynMode_DelegBase = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
}

CIecCfgSmvDataFT3InGrid::~CIecCfgSmvDataFT3InGrid()
{

}

void CIecCfgSmvDataFT3InGrid::InitGrid()
{
	InitGridTitle();
	m_pCtrlBlockSelectDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pCtrlBlockSelectDelegate);
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
#ifndef _PSX_QT_LINUX_
	m_pDelayTimeDelegate = new CIecSpinBoxDelegate(0,99999,this);
	setItemDelegateForColumn(5,m_pDelayTimeDelegate);
#endif
	m_pFiberSelected_DelegBase = new QFiberSelectedComBoxDelegBase(this);
	setItemDelegateForColumn(1,m_pFiberSelected_DelegBase);
	m_pByteNum_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(3,m_pByteNum_DelegBase);
	m_pSynMode_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(4,m_pSynMode_DelegBase);
	SetEditable(TRUE);
	connect(this,SIGNAL(cellDoubleClicked/*cellClicked*//*itemDoubleClicked*/(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);

}

void CIecCfgSmvDataFT3InGrid::InitGridTitle()
{
	//"State_SelectChannel","IEC_FIChoose","IEC_ChannelNumber","IEC_SmpByteNum","IEC_SmpCntType","IEC_RatedDelay"
	CString astrGridTitle[IECCFGSMVDATAFT3_GRID_COLS] = {g_sLangTxt_Select,g_sLangTxt_IEC_FIChoose,g_sLangTxt_IEC_ChannelNumber,g_sLangTxt_IEC_SmpByteNum,g_sLangTxt_IEC_SmpCntType,g_sLangTxt_IEC_RatedDelay};
	int iGridWidth[IECCFGSMVDATAFT3_GRID_COLS]={50, 140, 120, 120, 300, 125};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMVDATAFT3_GRID_COLS);
}

BOOL CIecCfgSmvDataFT3InGrid::IsCfgData(CExBaseObject *pIecCfgDataBase)
{
	if (pIecCfgDataBase->GetClassID() != CFGCLASSID_CIECCFG6044COMMONINDATA)
	{
		return FALSE;
	}
	return TRUE;
}

void CIecCfgSmvDataFT3InGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (!IsCfgData(pData))
	{
		return;
	}
	CIecCfg6044CommonInData *pIecCfgFT3Data = (CIecCfg6044CommonInData*)pData;
	Show_Check(pData,nRow,0,&pIecCfgFT3Data->m_nUseFlag,EndEditCell_CheckChanged);

// 	long nFiberCount = CCfgDataMngrConstGlobal::GetAppPortFT3InNum_ST();
// 	if (nRow < nFiberCount)
// 	{
		Show_DataType_Val(pData,nRow,1,g_strAppPortDataType_Ft3In,&pIecCfgFT3Data->m_nFiberIndex,EndEditCell_DataType_Val);
// 	}
// 	else
// 	{
// 		Show_StaticString(pData,nRow,1,_T(""));
// 		QMessageBox::information(this, tr("提示"),tr("光口已全部占用，当前无可选择的光口！"));
// 	}

	Show_Long(pData,nRow,2,&pIecCfgFT3Data->m_nChannelNum,TRUE,_T(""),EndEditCell_ChNum);
	Show_DataType_Val(pData,nRow,3,g_strAppPortDataType_SmpByteNum,&pIecCfgFT3Data->m_nSmpDataLen,EndEditCell_ChLenthChangged);
	Show_DataType_Val(pData,nRow,4,g_strAppPortDataType_SmpCntType,&pIecCfgFT3Data->m_nSmpCntType);
	Show_Long(pData,nRow,5,&pIecCfgFT3Data->m_nDelayTime);
	nRow++;
}

void CIecCfgSmvDataFT3InGrid::OnDataSelChanged(int nRow, int nCol)
{
	CIecCfgDataGridBase::OnDataSelChanged(nRow,nCol);

	CIecCfg6044CommonInData *pIecCfgFT3Data = (CIecCfg6044CommonInData*)GetData(nRow,nCol);

	if (pIecCfgFT3Data == NULL)
	{
		return;
	}

	BOOL bEnable = TRUE;

	if (!pIecCfgFT3Data->m_strProtocolID.IsEmpty())
	{
		bEnable = FALSE;
	} 

	SetItemEnable(nRow,2,bEnable);
	SetItemEnable(nRow,3,bEnable);
// 	SetItemEnable(nRow,4,bEnable);
// 	SetItemEnable(nRow,5,bEnable);
}

void CIecCfgSmvDataFT3InGrid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	switch(nCol)
	{
	case 2:
	case 3:
	case 5:
		{
			QString strValue = pItem->text();
			GetEngWidgetBoard_DigitData(strValue, this);
			pItem->setText(strValue);

		}break;
	case 0:
	case 1:
	case 4:
		return;
	default:
		{
			QString strValue = pItem->text();
			GetWidgetBoard_DigitData(4, strValue,pItem, this);
		}break;
	}
}


