#include "IecCfgGoutDataGrid.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutData.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"


CIecCfgGoutDataGrid::CIecCfgGoutDataGrid(QWidget* pparent):CIecCfgDataGridBase(pparent)
{
	m_pSrcMacAddrDelegate = NULL;
	m_pVlanIDDelegate = NULL;
	m_pTestCheckDelegate = NULL;
	m_pNdsComCheckDelegate = NULL;
	installEventFilter(this);
}

CIecCfgGoutDataGrid::~CIecCfgGoutDataGrid()
{

}

void CIecCfgGoutDataGrid::InitGrid()
{
 	CIecCfgDataGridBase::InitGrid();
	m_pDesMacAddrDelegate = new QIecNumberEditDelegate(QIecLineEdit::MAC_TEXT,this);
	setItemDelegateForColumn(6,m_pDesMacAddrDelegate);
	m_pSrcMacAddrDelegate = new QIecNumberEditDelegate(QIecLineEdit::MAC_TEXT,this);
	setItemDelegateForColumn(7,m_pSrcMacAddrDelegate);
	m_pAppIDDelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(1,m_pAppIDDelegate);

	m_pFiberSelected_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(3,m_pFiberSelected_DelegBase);

	m_pVlanIDDelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(10,m_pVlanIDDelegate);

	m_pVersionNODelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(11,m_pVersionNODelegate);

	m_pTestCheckDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(5,m_pTestCheckDelegate);

	m_pNdsComCheckDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(15,m_pNdsComCheckDelegate);

	SetEditable(TRUE);
//	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgGoutDataGrid::InitGridTitle()
{
	CString strChoose,strTarget,strSource,strIntrance,strDescribe,strChannelNumber,strVersion,strTest,strLifeTime;
	xlang_GetLangStrByFile(strChoose,"sSelect");
	xlang_GetLangStrByFile(strTarget,"IEC_Target");
	xlang_GetLangStrByFile(strSource,"IEC_Source");
	xlang_GetLangStrByFile(strIntrance,"IEC_Intrance");
	xlang_GetLangStrByFile(strDescribe,"State_Description");
	xlang_GetLangStrByFile(strChannelNumber,"IEC_ChannelNumber");
	xlang_GetLangStrByFile(strVersion,"IEC_Version");
	xlang_GetLangStrByFile(strTest,"IEC_Test");
	xlang_GetLangStrByFile(strLifeTime,"IEC_LifeTime");

	CString astrGridTitle[IECCFGGOUTDATA_GRID_COLS] = {strChoose,_T("APPID"),strDescribe,strIntrance,strChannelNumber,strTest,strTarget,strSource,strLifeTime,_T("VLAN_Priority"),_T("VLAN_ID")
	,strVersion,_T("GoCBRef"),_T("Dataset"),_T("GoID"),_T("NdsCom")};
	int iGridWidth[IECCFGGOUTDATA_GRID_COLS]={50, 100, 200, 120, 100, 105,220, 220, 180, 160,  100, 150, 260, 260,260,150};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGGOUTDATA_GRID_COLS);
}

BOOL CIecCfgGoutDataGrid::IsCfgData(CExBaseObject *pIecCfgDataBase)
{
	if (pIecCfgDataBase->GetClassID() != CFGCLASSID_CIECCFGGOUTDATA)
	{
		return FALSE;
	}

	return TRUE;
}

void CIecCfgGoutDataGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (!IsCfgData(pData))
	{
		return;
	}

	CString strTmp;
	CIecCfgGoutData *pIecCfgGoutData = (CIecCfgGoutData*)pData;
	Show_Check(pData,nRow,0,&pIecCfgGoutData->m_nUseFlag,EndEditCell_CheckChanged);
	Show_Hex(pData,nRow,1,&pIecCfgGoutData->m_dwAppID,2); 
	strTmp = pIecCfgGoutData->m_strIedRefDesc;

	if (!pIecCfgGoutData->m_strDataSetDesc.IsEmpty())
	{
		strTmp += _T("-");
		strTmp += pIecCfgGoutData->m_strDataSetDesc;
	}

	Show_StaticString(pData,nRow,2,&strTmp);
	Show_DataType_Val(pData,nRow,3,g_strAppPortDataType_Fiber,&pIecCfgGoutData->m_nFiberIndex,EndEditCell_DataType_Val); 
	Show_Long(pData,nRow,4,&pIecCfgGoutData->m_nChannelNum,TRUE,_T(""),EndEditCell_ChNum);
	Show_Check(pData,nRow,5,&pIecCfgGoutData->m_bTest);
	Show_String(pData,nRow,6,&pIecCfgGoutData->m_strDestAddress,EndEditCell_TextChangged); 
	Show_String(pData,nRow,7,&pIecCfgGoutData->m_strSrcAddress,EndEditCell_TextChangged); 
 	Show_Long(pData,nRow,8,&pIecCfgGoutData->m_nLiveTime);
	
	Show_Long(pData,nRow,9,&pIecCfgGoutData->m_dwVLandPriority);
	Show_Hex(pData,nRow,10,&pIecCfgGoutData->m_dwVLandID,2); 
	
	Show_Hex(pData,nRow,11,&pIecCfgGoutData->m_dwVersion,2); 

	Show_String(pData,nRow,12,&pIecCfgGoutData->m_strgocbRef,EndEditCell_TextChangged); 
	Show_String(pData,nRow,13,&pIecCfgGoutData->m_strDataSet,EndEditCell_TextChangged); 
	Show_String(pData,nRow,14,&pIecCfgGoutData->m_strGooseId,EndEditCell_TextChangged); 
	Show_Check(pData,nRow,15,&pIecCfgGoutData->m_bNdsCom);
	 
  	nRow++;
}

void CIecCfgGoutDataGrid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
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
	case 6:
	case 7:

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
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
	case 5:
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


