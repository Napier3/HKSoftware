#include "IecCfgSmvData92InGrid.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"

CIecCfgSmvData92InGrid::CIecCfgSmvData92InGrid(QWidget* pparent):CIecCfgDataGridBase(pparent)
{
	m_pDelayTimeDelegate = NULL;
	m_pVlanIDDelegate = NULL;
	m_pSynMode_DelegBase = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
}

CIecCfgSmvData92InGrid::~CIecCfgSmvData92InGrid()
{
}

void CIecCfgSmvData92InGrid::InitGrid()
{
	CIecCfgDataGridBase::InitGrid();
	m_pAppIDDelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(1,m_pAppIDDelegate);

	m_pFiberSelected_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(3,m_pFiberSelected_DelegBase);

	m_pDesMacAddrDelegate = new QIecNumberEditDelegate(QIecLineEdit::MAC_TEXT,this);
	setItemDelegateForColumn(5,m_pDesMacAddrDelegate);

	SetEditable(TRUE);
}

void CIecCfgSmvData92InGrid::InitGridTitle()
{
	CString strChoose,strTarget,strEntrance,strDescribe,strChannelNumber;
	xlang_GetLangStrByFile(strChoose,"sSelect");
	xlang_GetLangStrByFile(strTarget,"IEC_Target");
	xlang_GetLangStrByFile(strEntrance,"IEC_Entrance");
	xlang_GetLangStrByFile(strDescribe,"State_Description");
	xlang_GetLangStrByFile(strChannelNumber,"IEC_ChannelNumber");

	CString astrGridTitle[IECCFGSMVDATA92IN_GRID_COLS] = {strChoose,_T("APPID"),strDescribe,strEntrance,strChannelNumber,strTarget};
	int iGridWidth[IECCFGSMVDATA92IN_GRID_COLS]={60, 110, 200,150, 200, 200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMVDATA92IN_GRID_COLS);
}

BOOL CIecCfgSmvData92InGrid::IsCfgData(CExBaseObject *pIecCfgDataBase)
{
	if (pIecCfgDataBase->GetClassID() != CFGCLASSID_CIECCFG92INPUTDATA)
	{
		return FALSE;
	}

	return TRUE;
}

void CIecCfgSmvData92InGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (!IsCfgData(pData))
	{
		return;
	}

	CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data*)pData;
	Show_Check(pData,nRow,0,&pIecCfg92Data->m_nUseFlag,EndEditCell_CheckChanged);
	Show_Hex(pData,nRow,1,&pIecCfg92Data->m_dwAppID,2); 
	Show_StaticString(pData,nRow,2,&pIecCfg92Data->m_strIedRefDesc);
	Show_DataType_Val(pData,nRow,3,g_strAppPortDataType_Fiber,&pIecCfg92Data->m_nFiberIndex,EndEditCell_DataType_Val); 
	Show_Long(pData,nRow,4,&pIecCfg92Data->m_nChannelNum,TRUE,_T(""),EndEditCell_ChNum);
	Show_String(pData,nRow,5,&pIecCfg92Data->m_strDestAddress,EndEditCell_TextChangged); 
  	nRow++;
}

void CIecCfgSmvData92InGrid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
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
		{
			QString strValue = pItem->text();
			GetEngWidgetBoard_DigitData(strValue, this);
			pItem->setText(strValue);
		}break;
	case 0:
	case 3:
		return;
	default:
		{
			QString strValue = pItem->text();
			GetWidgetBoard_DigitData(4, strValue,pItem, this);
// 			pItem->setText(strValue);
		}break;
	}
}
