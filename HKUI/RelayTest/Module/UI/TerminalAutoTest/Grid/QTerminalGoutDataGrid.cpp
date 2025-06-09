#include "QTerminalGoutDataGrid.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutData.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDatasBase.h"

QTerminalGoutDataGrid::QTerminalGoutDataGrid(QWidget* pparent):CIecCfgDataGridBase(pparent)
{
	m_pSrcMacAddrDelegate = NULL;
	m_pVlanIDDelegate = NULL;
	m_pTestCheckDelegate = NULL;
	m_pNdsComCheckDelegate = NULL;
	m_nFirstIndex = 0;
	installEventFilter(this);
	connect(this,SIGNAL(currentCellChanged(int , int , int , int )),SLOT(slot_CurrentCellChanged(int , int , int , int )));
	connect(this,SIGNAL(sig_UpdateCheckState(CIecCfgDataBase*,int)),this,SLOT(slot_UpdateCheckState(CIecCfgDataBase*,int)));
}

QTerminalGoutDataGrid::~QTerminalGoutDataGrid()
{

}

void QTerminalGoutDataGrid::InitGrid()
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
}

void QTerminalGoutDataGrid::InitGridTitle()
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

	CString astrGridTitle[GGOUTDATA_GRID_COLS] = {strChoose,_T("APPID"),strDescribe,strIntrance,strChannelNumber,strTest,strTarget,strSource,strLifeTime,_T("VLAN_Priority"),_T("VLAN_ID")
	,strVersion,_T("GoCBRef"),_T("Dataset"),_T("GoID"),_T("NdsCom")};
	int iGridWidth[GGOUTDATA_GRID_COLS]={50, 100, 200, 100, 100, 105,220, 220, 160, 160,  100, 150, 260, 260,260,150};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, GGOUTDATA_GRID_COLS);
}

BOOL QTerminalGoutDataGrid::IsCfgData(CExBaseObject *pIecCfgDataBase)
{
	if (pIecCfgDataBase->GetClassID() != CFGCLASSID_CIECCFGGOUTDATA)
	{
		return FALSE;
	}

	return TRUE;
}

void QTerminalGoutDataGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (!IsCfgData(pData))
	{
		return;
	}

	CString strTmp;
	CIecCfgGoutData *pIecCfgGoutData = (CIecCfgGoutData*)pData;

	if (pIecCfgGoutData->m_nUseFlag == 1 )
	{
		m_nFirstIndex ++;
	}

	if (m_nFirstIndex > 1)
	{
		pIecCfgGoutData->m_nUseFlag = 0;
	}
	
	
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
	Show_String(pData,nRow,6,&pIecCfgGoutData->m_strDestAddress,EndEditCell_String); 
	Show_String(pData,nRow,7,&pIecCfgGoutData->m_strSrcAddress,EndEditCell_String); 
 	Show_Long(pData,nRow,8,&pIecCfgGoutData->m_nLiveTime);
	
	Show_Long(pData,nRow,9,&pIecCfgGoutData->m_dwVLandPriority);
	Show_Hex(pData,nRow,10,&pIecCfgGoutData->m_dwVLandID,2); 
	
	Show_Hex(pData,nRow,11,&pIecCfgGoutData->m_dwVersion,2); 

	Show_String(pData,nRow,12,&pIecCfgGoutData->m_strgocbRef,EndEditCell_String); 
	Show_String(pData,nRow,13,&pIecCfgGoutData->m_strDataSet,EndEditCell_String); 
	Show_String(pData,nRow,14,&pIecCfgGoutData->m_strGooseId,EndEditCell_String); 
	Show_Check(pData,nRow,15,&pIecCfgGoutData->m_bNdsCom);
	 
  	nRow++;
}

void QTerminalGoutDataGrid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
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



void QTerminalGoutDataGrid::slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if ((currentRow >= 0))
	{
		OnDataSelChanged(currentRow,currentColumn);
	}

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase *)GetCurrSelData();

	if (pIecCfgData == NULL)
	{
		return;
	}

	emit sig_UpdateChansdata(pIecCfgData->m_pCfgChs);
}


void QTerminalGoutDataGrid::EndEditCell_CheckChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	QTerminalGoutDataGrid *pOwnGrid = (QTerminalGoutDataGrid*)pGrid;

	if ((pVCellData->pObj != NULL))
	{
		CIecCfgDataBase *pIecCfgDataBase = (CIecCfgDataBase*)pVCellData->pObj;
		CIecCfgDatasBase *pIecCfgDatasBase = (CIecCfgDatasBase*)pIecCfgDataBase->GetParent();

// 		if ((pIecCfgDatasBase != NULL)&&(pIecCfgDataBase->m_nUseFlag))
// 		{
// 			long nUseCount = pIecCfgDatasBase->GetUseDatasCount(pIecCfgDataBase->GetClassID());
// 			long nMaxCfgDataCount = 1;
// 
// 
// 			if (nUseCount>nMaxCfgDataCount)
// 			{
// 				pIecCfgDataBase->m_nUseFlag = 0;
// 				CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("当前选择的控制块数量(%ld),大于最大设置控制块数量(%ld)."),nUseCount,nMaxCfgDataCount);
// 				emit pOwnGrid->sig_UpdateCheckState(pIecCfgDataBase,nRow);
// 			}
// 		}

		CIecCfgDataBase *pDataBase = NULL;
		POS pos = pIecCfgDatasBase->GetHeadPosition();
		long nIndex = 0;
		while(pos)
		{
			pDataBase = (CIecCfgDataBase *)pIecCfgDatasBase->GetNext(pos);
			if (pDataBase != pIecCfgDataBase)
			{
				pDataBase->m_nUseFlag = 0;
				emit pOwnGrid->sig_UpdateCheckState(pDataBase,nIndex);
			}
			else
			{
				pIecCfgDataBase->m_nUseFlag = 1;
				emit pOwnGrid->sig_UpdateCheckState(pIecCfgDataBase,nRow);
			}

			nIndex ++ ;
		}
	}
}

void QTerminalGoutDataGrid::slot_UpdateCheckState(CIecCfgDataBase *pIecCfgDataBase,int nRow)
{
	Show_Check(pIecCfgDataBase,nRow,0,&pIecCfgDataBase->m_nUseFlag,EndEditCell_CheckChanged);
}
