#include "IecCfgGinDataGrid.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGinData.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"


CIecCfgGinDataGrid::CIecCfgGinDataGrid(QWidget* pparent):CIecCfgDataGridBase(pparent)
{
	m_pTestCheckDelegate = NULL;
	m_pNdsComCheckDelegate = NULL;
	m_pNotGocbCheckDelegate = NULL;
	installEventFilter(this);
}

CIecCfgGinDataGrid::~CIecCfgGinDataGrid()
{

}

void CIecCfgGinDataGrid::InitGrid()
{
 	CIecCfgDataGridBase::InitGrid();
	m_pAppIDDelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(1,m_pAppIDDelegate);
	m_pFiberSelected_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(3,m_pFiberSelected_DelegBase);

	m_pVersionNODelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(8,m_pVersionNODelegate);

	m_pTestCheckDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(6,m_pTestCheckDelegate);
	m_pNdsComCheckDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(12,m_pNdsComCheckDelegate);
	m_pNotGocbCheckDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(13,m_pNotGocbCheckDelegate);

	m_pDesMacAddrDelegate = new QIecNumberEditDelegate(QIecLineEdit::MAC_TEXT,this);
	setItemDelegateForColumn(5,m_pDesMacAddrDelegate);
	SetEditable(TRUE);

//	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgGinDataGrid::InitGridTitle()
{
	CString strChoose,strTarget,strEntrance,strDescribe,strChannelNumber,strVersion,strTest,strLifeTime,strUnParse;
	xlang_GetLangStrByFile(strChoose,"sSelect");
	xlang_GetLangStrByFile(strTarget,"IEC_Target");
	xlang_GetLangStrByFile(strEntrance,"IEC_Entrance");
	xlang_GetLangStrByFile(strDescribe,"State_Description");
	xlang_GetLangStrByFile(strChannelNumber,"IEC_ChannelNumber");
	xlang_GetLangStrByFile(strVersion,"IEC_Version");
	xlang_GetLangStrByFile(strTest,"IEC_Test");
	xlang_GetLangStrByFile(strLifeTime,"IEC_LifeTime");
	xlang_GetLangStrByFile(strUnParse,"IEC_ParseGoCB_GoID_Dataset");

	CString astrGridTitle[IECCFGGINDATA_GRID_COLS] = {strChoose,_T("APPID"),strDescribe,strEntrance,strChannelNumber,strTarget,strTest,strLifeTime,strVersion,
	_T("GoCBRef"),_T("DataSet"),_T("GoID"),_T("NdsCom"),strUnParse};
	int iGridWidth[IECCFGGINDATA_GRID_COLS]={50, 100, 200, 120, 100,200, 110, 170, 120, 260, 260, 200, 170, 310};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGGINDATA_GRID_COLS);
}

BOOL CIecCfgGinDataGrid::IsCfgData(CExBaseObject *pIecCfgDataBase)
{
	if (pIecCfgDataBase->GetClassID() != CFGCLASSID_CIECCFGGINDATA)
	{
		return FALSE;
	}

	return TRUE;
}

void CIecCfgGinDataGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (!IsCfgData(pData))
	{
		return;
	}

 	CIecCfgGinData *pIecCfgGinData = (CIecCfgGinData*)pData;
 	Show_Check(pData,nRow,0,&pIecCfgGinData->m_nUseFlag,EndEditCell_CheckChanged);
	Show_Hex(pData,nRow,1,&pIecCfgGinData->m_dwAppID,2); 
	Show_StaticString(pData,nRow,2,&pIecCfgGinData->m_strIedRefDesc);
	Show_DataType_Val(pData,nRow,3,g_strAppPortDataType_Fiber,&pIecCfgGinData->m_nFiberIndex,EndEditCell_DataType_Val); 
	Show_Long(pData,nRow,4,&pIecCfgGinData->m_nChannelNum,TRUE,_T(""),EndEditCell_ChNum);
 	Show_String(pData,nRow,5,&pIecCfgGinData->m_strDestAddress,EndEditCell_TextChangged); 
  	Show_DataType_Val(pData,nRow,6,g_strAppTestSetDataType,&pIecCfgGinData->m_bTest,EndEditCell_DataType_Val);
	Show_Long(pData,nRow,7,&pIecCfgGinData->m_nLiveTime); 
	Show_Hex(pData,nRow,8,&pIecCfgGinData->m_dwVersion,2); 
	Show_String(pData,nRow,9,&pIecCfgGinData->m_strgocbRef,EndEditCell_TextChangged); 
	Show_String(pData,nRow,10,&pIecCfgGinData->m_strDataSet,EndEditCell_TextChangged); 
	Show_String(pData,nRow,11,&pIecCfgGinData->m_strGooseId,EndEditCell_TextChangged);
	Show_Check(pData,nRow,12,&pIecCfgGinData->m_bNdsCom);
	Show_Check(pData,nRow,13,&pIecCfgGinData->m_nUseGooseID);

  	nRow++;
}

void CIecCfgGinDataGrid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
{
// 	QTableWidgetItem *pItem = this->item(nRow,nCol);
	QGV_ITEM *pItem = GetCell(nRow,nCol); 

	if (pItem == NULL)
	{
		return;
	}

	switch(nCol)
	{
	case 1:
	case 2:
	case 4:
	case 5:
	case 9:
	case 10:
	case 11:
		{
			QString strValue = pItem->text();
			GetEngWidgetBoard_DigitData(strValue, this);
			pItem->setText(strValue);

			/*
			WidgetKeyboard dlg(this);
			dlg.m_InputString = pItem->text();
			dlg.showToEdit();
			if (dlg.exec() == QDialog::Accepted)
			{
				pItem->setText(dlg.m_InputString);
			}
			*/
		}break;
	case 0:
	case 3:
	case 6:
	case 12:
	case 13:
		return;
	default:
		{
			QString strValue = pItem->text();
			GetWidgetBoard_DigitData(4, strValue,pItem, this);
// 			pItem->setText(strValue);

			/*
			WidgetKeyboardV_Digit dlg(4,this);
			dlg.m_strEditInfo = pItem->text();
			dlg.showToEdit();
			if (dlg.exec()==QDialog::Accepted)
			{
				pItem->setText(dlg.m_strEditInfo);
			}
			*/
		}break;
	}
}




