#include "IecCfgSmv92InChsGrid.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../SttIecQualitySetDialog.h"
#include "../../../XLangResource_Native.h"


CIecCfgSmv92InChsGrid::CIecCfgSmv92InChsGrid(QWidget* pparent):CIecCfgChsGridBase(pparent)
{

}

CIecCfgSmv92InChsGrid::~CIecCfgSmv92InChsGrid()
{

}

void CIecCfgSmv92InChsGrid::InitGrid()
{
	InitGridTitle();
	m_pChSelectDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pChSelectDelegate);

	m_pChType_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(2,m_pChType_DelegBase);
	m_pChMap_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(3,m_pChMap_DelegBase);
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif

	m_pChAccLevelDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(4,m_pChAccLevelDelegate);
	SetEditable(TRUE);
	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgSmv92InChsGrid::InitGridTitle()
{
	CString strChChoose,strChDescription,strChType,strChMaps,strAccuratyLevel;
	xlang_GetLangStrByFile(strChChoose,"sSelect");
	xlang_GetLangStrByFile(strChDescription,"IEC_ChDescription");
	xlang_GetLangStrByFile(strChType,"IEC_ChType");
	xlang_GetLangStrByFile(strChMaps,"IEC_ChMaps");
//	xlang_GetLangStrByFile(strQuality,"IEC_Quality");
//	strAccuratyLevel = tr("准确级");
	xlang_GetLangStrByFile(strAccuratyLevel,"IEC_AccuratyLevel");

	CString astrGridTitle[IECCFGSMV92INCHS_GRID_COLS] = {strChChoose,strChDescription,strChType,strChMaps,strAccuratyLevel};
	int iGridWidth[IECCFGSMV92INCHS_GRID_COLS]={80,420, 150,150,150};

	//20230725 suyang 适配分辨率 1024X768

#ifdef _PSX_QT_WINDOWS_

		iGridWidth[1] = 200;
#endif


	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMV92INCHS_GRID_COLS);
}

void CIecCfgSmv92InChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFG92CHIN)
	{
		return;
	}

	CIecCfg92ChIn *pIecCfg92Ch = (CIecCfg92ChIn*)pData;
	Show_Check(pData,nRow,0,&pIecCfg92Ch->m_nUseFlag);
	long nCurrChIndex = pIecCfg92Ch->m_nIndex ;
    if (pIecCfg92Ch->m_strName.IsEmpty() || pIecCfg92Ch->m_strName.Find(_T("Ch")) >= 0)//cl20231027设置通道缺省项
	{
		pIecCfg92Ch->m_strName.Format(/*_T("通道%d")*/g_sLangTxt_Native_ChnN,nCurrChIndex+1);
	}
	Show_StaticString(pData,nRow,1,&pIecCfg92Ch->m_strName);
	Show_DataType_Val(pData, nRow, 2,iecfg_Smv92ChDataType, &pIecCfg92Ch->m_strChType,EndEditCell_Smv92ChSelChangged);
	UpdateData_ByDataType(pIecCfg92Ch,nRow);
 //	Show_Hex(pData, nRow, 3, &pIecCfg92Ch->m_nQuality, 4,false);
  	nRow++;
}

void CIecCfgSmv92InChsGrid::EndEditCell_Smv92ChSelChangged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfg92ChIn *pIecCfgSmv92Ch = (CIecCfg92ChIn*)pVCellData->pObj;
	((CIecCfgSmv92InChsGrid*)pGrid)->UpdateData_ByDataType(pIecCfgSmv92Ch,nRow);
}

void CIecCfgSmv92InChsGrid::UpdateData_ByDataType(CIecCfg92ChIn *pIecCfgSmv92Ch,int nRow)
{
	if (pIecCfgSmv92Ch->m_strChType == iecfg_SmvChDataType_Val_Vol)
	{
		Show_DataType_Val(pIecCfgSmv92Ch, nRow, 3,iecfg_SmvAppChDataType_U, &pIecCfgSmv92Ch->m_strAppChID);
		Show_DataType_Val(pIecCfgSmv92Ch, nRow, 4,iecfg_SmvInAppChAccLevelDataType_U, &pIecCfgSmv92Ch->m_nAccuratyLevel);
	} 
	else if (pIecCfgSmv92Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)
	{
		Show_DataType_Val(pIecCfgSmv92Ch, nRow, 3,iecfg_SmvAppChDataType_I, &pIecCfgSmv92Ch->m_strAppChID);
		Show_DataType_Val(pIecCfgSmv92Ch, nRow, 4,iecfg_SmvInAppChAccLevelDataType_I, &pIecCfgSmv92Ch->m_nAccuratyLevel);
	} 
	else if (pIecCfgSmv92Ch->m_strChType == iecfg_SmvChDataType_Val_UTCTime)
	{
		Show_DataType_Val(pIecCfgSmv92Ch, nRow, 3,iecfg_SmvAppChDataType_T, &pIecCfgSmv92Ch->m_strAppChID);
		Show_StaticString(pIecCfgSmv92Ch, nRow, 4,"--");
	} 
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前SMV92通道映射出错(%s)."),pIecCfgSmv92Ch->m_strChType.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_SMV92map.GetString(),pIecCfgSmv92Ch->m_strChType.GetString()); //lcq
	}
}

void CIecCfgSmv92InChsGrid::UpdateDatas_Quality()
{
// 	if (m_pDatas == NULL)
// 	{
// 		return;
// 	}
// 
// 	DisConnectAll_SigSlot();
// 	CIecCfg92ChIn *pIecCfg92Ch = NULL;	
// 	POS pos = m_pDatas->GetHeadPosition();
// 	int nRowIndex = 0;//zhouhj Qt中不包括标题行
// 	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
// 
// 	while (pos != NULL)
// 	{
// 		pIecCfg92Ch = (CIecCfg92ChIn*)m_pDatas->GetNext(pos);
// 		Show_Hex(pIecCfg92Ch, nRowIndex, 3, &pIecCfg92Ch->m_nQuality, 4,false);
// 		nRowIndex++;
// 	}
// 
// 	ConnectAll_SigSlot();
}

void CIecCfgSmv92InChsGrid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
{
	if (nCol != 1/*0*/)
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
}



