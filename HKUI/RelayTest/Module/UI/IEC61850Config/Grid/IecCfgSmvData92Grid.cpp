#include "IecCfgSmvData92Grid.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"

CIecCfgSmvData92Grid::CIecCfgSmvData92Grid(QWidget* pparent):CIecCfgDataGridBase(pparent)
{
	m_pSrcMacAddrDelegate = NULL;
	m_pDelayTimeDelegate = NULL;
	m_pVlanIDDelegate = NULL;
	m_pSynMode_DelegBase = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);
}

CIecCfgSmvData92Grid::~CIecCfgSmvData92Grid()
{

}

void CIecCfgSmvData92Grid::InitGrid()
{
	InitGridTitle();
	m_pCtrlBlockSelectDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pCtrlBlockSelectDelegate);
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif

	m_pAppIDDelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(1,m_pAppIDDelegate);	
#ifndef _PSX_QT_LINUX_
	m_pDelayTimeDelegate = new CIecSpinBoxDelegate(0,99999,this);
	setItemDelegateForColumn(4,m_pDelayTimeDelegate);
#endif
	m_pFiberSelected_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(3,m_pFiberSelected_DelegBase);
	m_pSynMode_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(6,m_pSynMode_DelegBase);
	m_pDesMacAddrDelegate = new QIecNumberEditDelegate(QIecLineEdit::MAC_TEXT,this);
	setItemDelegateForColumn(7,m_pDesMacAddrDelegate);
	m_pSrcMacAddrDelegate = new QIecNumberEditDelegate(QIecLineEdit::MAC_TEXT,this);
	setItemDelegateForColumn(8,m_pSrcMacAddrDelegate);

	m_pVlanIDDelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(10,m_pVlanIDDelegate);

	m_pVersionNODelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	setItemDelegateForColumn(11,m_pVersionNODelegate);
	
	SetEditable(TRUE);
	connect(this,SIGNAL(cellDoubleClicked/*cellClicked*//*itemDoubleClicked*/(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(sig_UpdateCheckState(CIecCfgDataBase*,int)),this,SLOT(slot_UpdateCheckState(CIecCfgDataBase*,int)));
}

void CIecCfgSmvData92Grid::InitGridTitle()
{
	CString strChoose,strTarget,strEntrance,strDescribe,strChannelNumber,strVersion,strSynchronously,strSource,strDelay;
	xlang_GetLangStrByFile(strChoose,"sSelect");
	xlang_GetLangStrByFile(strTarget,"IEC_Target");
	xlang_GetLangStrByFile(strSource,"IEC_Source");
	xlang_GetLangStrByFile(strDelay,"IEC_Delay");
	xlang_GetLangStrByFile(strEntrance,"IEC_Intrance");
	xlang_GetLangStrByFile(strDescribe,"State_Description");
	xlang_GetLangStrByFile(strChannelNumber,"IEC_ChannelNumber");
	xlang_GetLangStrByFile(strVersion,"IEC_Version");
	xlang_GetLangStrByFile(strSynchronously,"IEC_Synchronously");

	CString astrGridTitle[IECCFGSMVDATA92_GRID_COLS] = {strChoose,_T("APPID"),strDescribe,strEntrance,strDelay,strChannelNumber,strSynchronously,strTarget,strSource,_T("VLAN_Priority"),_T("VLAN_ID")
	,strVersion,_T("SVID"),_T("Dataset")};
	int iGridWidth[IECCFGSMVDATA92_GRID_COLS]={50, 80,220,130,130,80,160, 190, 190,  145, 100, 90,  260, 260};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMVDATA92_GRID_COLS);
}

BOOL CIecCfgSmvData92Grid::IsCfgData(CExBaseObject *pIecCfgDataBase)
{
	if (pIecCfgDataBase->GetClassID() != CFGCLASSID_CIECCFG92DATA)
	{
		return FALSE;
	}

	return TRUE;
}

void CIecCfgSmvData92Grid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
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

#ifdef _PSX_QT_LINUX_

	Show_Long(pData,nRow,4,&pIecCfg92Data->m_nDelay,TRUE,_T(""),EndEditCell_SampleDelay);
#else
	Show_Long(pData,nRow,4,&pIecCfg92Data->m_nDelay);
#endif

	
	Show_Long(pData,nRow,5,&pIecCfg92Data->m_nChannelNum,TRUE,_T(""),EndEditCell_ChNum);
	Show_DataType_Val(pData,nRow,6,g_strSynModeDataType_Fiber,&pIecCfg92Data->m_nSyn,EndEditCell_DataType_Val);
	Show_String(pData,nRow,7,&pIecCfg92Data->m_strDestAddress,EndEditCell_TextChangged); 
	Show_String(pData,nRow,8,&pIecCfg92Data->m_strSrcAddress,EndEditCell_TextChangged);

	Show_Long(pData,nRow,9,&pIecCfg92Data->m_nPriority);
	Show_Hex(pData,nRow,10,&pIecCfg92Data->m_dwVID,2);
	Show_Hex(pData,nRow,11,&pIecCfg92Data->m_dwVersion,2); 
	Show_String(pData,nRow,12,&pIecCfg92Data->m_strSVID,EndEditCell_TextChangged); 
	Show_String(pData,nRow,13,&pIecCfg92Data->m_strDataSet,EndEditCell_TextChangged); 

  	nRow++;
}

void CIecCfgSmvData92Grid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
{
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
	case 7:
	case 8:
	case 9:
	case 10:
	case 12:
	case 13:
		{
			QString strValue = pItem->text();
			GetEngWidgetBoard_DigitData(strValue, this);
			pItem->setText(strValue);

		}break;
	case 0:
	case 3:
	case 11:
		return;
	default:
		{
			QString strValue = pItem->text();
			GetWidgetBoard_DigitData(4, strValue,pItem, this);
		}break;
	}
}




