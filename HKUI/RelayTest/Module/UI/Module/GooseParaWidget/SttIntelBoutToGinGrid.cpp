#include "SttIntelBoutToGinGrid.h"
#include <QHeaderView>
#include "../SttUIDefine.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../CommonMethod/commonMethod.h"
#include <QApplication>

#define STTINTELBOUTTOGIN_GRID_COL_INDEX_DESC                    1
#define STTINTELBOUTTOGIN_GRID_COL_INDEX_DATATYPE                2
#define STTINTELBOUTTOGIN_GRID_COL_INDEX_VALUE                   3
#define STTINTELBOUTTOGIN_GRID_COL_INDEX_MAP                 4
#define STTINTELBOUTTOGIN_GRID_COL_INDEX_RESUIT                 5


CSttIntelBoutToGinGrid::CSttIntelBoutToGinGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pDataType_DelegBase = NULL;
	m_pMap_DelegBase = NULL;
	m_pValue_DelegBase = NULL;
}

CSttIntelBoutToGinGrid::~CSttIntelBoutToGinGrid()
{

}

void CSttIntelBoutToGinGrid::SetRunState(long nRunState)
{
	if (nRunState == STT_UI_RUN_STATE_Stoped)
	{
		m_bGooseFlag=nRunState;
		m_pDataType_DelegBase->SetEditable(TRUE);
		m_pMap_DelegBase->SetEditable(TRUE);
		m_pValue_DelegBase->SetEditable(TRUE);
		setEditTriggers(QAbstractItemView::DoubleClicked);
		SetEditable();
	}
	else if (nRunState == STT_UI_RUN_STATE_StateTested_NotEditable)
	{
		m_bGooseFlag=nRunState;
		m_pDataType_DelegBase->SetEditable(FALSE);
		m_pMap_DelegBase->SetEditable(FALSE);
		m_pValue_DelegBase->SetEditable(TRUE);
		setEditTriggers(QAbstractItemView::NoEditTriggers);
		SetEditable(FALSE);
	}
	else
	{
		m_pDataType_DelegBase->SetEditable(TRUE);
		m_pMap_DelegBase->SetEditable(TRUE);
		m_pValue_DelegBase->SetEditable(TRUE);
		setEditTriggers(QAbstractItemView::DoubleClicked);
		SetEditable(TRUE);
	}

	reset();
}

void CSttIntelBoutToGinGrid::InitGrid()
{
 	InitGridTitle();
	SetEditable(TRUE);
	m_pDataType_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(STTINTELBOUTTOGIN_GRID_COL_INDEX_DATATYPE,m_pDataType_DelegBase);
	m_pMap_DelegBase = new QIecCfgGinChsComBoxDelegate(this);
	setItemDelegateForColumn(STTINTELBOUTTOGIN_GRID_COL_INDEX_MAP,m_pMap_DelegBase);
	m_pValue_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(STTINTELBOUTTOGIN_GRID_COL_INDEX_VALUE,m_pValue_DelegBase);
	setAlternatingRowColors(true);
}

void CSttIntelBoutToGinGrid::InitGridTitle()
{
	CString astrGridTitle[STTINTELBOUTTOGINGRID_GRID_COLS] = {_T("序号"),_T("描述"),_T("数据类型"),_T("数值"),_T("开入关联"),_T("测试结果")};
	int  iColType[STTINTELBOUTTOGINGRID_GRID_COLS]={QT_GVET_NOEDIT,QT_GVET_NOEDIT, QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[STTINTELBOUTTOGINGRID_GRID_COLS]={40, 220, 90, 125, 100, 110};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTINTELBOUTTOGINGRID_GRID_COLS);
	QHeaderView* pHeadLeft = verticalHeader();
	pHeadLeft->setVisible(false);
}


void CSttIntelBoutToGinGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
	CString nindex ;
	nindex.Format("%d",nRow+1);
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pData;
	Show_StaticString(pData,nRow,0,&nindex); 
	Show_String(pData,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_DESC,&pGinCh->m_strName);
	Show_DataType_Val(pData, nRow, STTINTELBOUTTOGIN_GRID_COL_INDEX_DATATYPE,iecfg_GooseChDataType, &pGinCh->m_strDataType,EndEditCell_GinChSelChangged);
	UpdateData_ByDataType(pGinCh,nRow);
	nRow++;
}

CDataType* CSttIntelBoutToGinGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);
	return pDataType;
}

void CSttIntelBoutToGinGrid::EndEditCell_GinChSelChangged (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pVCellData->pObj;
	CDataTypeValue *pValue = NULL;
	if (nCol == STTINTELBOUTTOGIN_GRID_COL_INDEX_DATATYPE)//数据类型
	{
		pGinCh->CheckDefautValue();
		CDataType *pGooseChType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GooseChDataType);
		pValue = (CDataTypeValue *)pGooseChType->FindByID(pGinCh->m_strDataType);
		pGinCh->m_strDataTypeName = pValue->m_strName;

		((CSttIntelBoutToGinGrid*)pGrid)->UpdateData_ByDataType(pGinCh,nRow);	
		emit ((CSttIntelBoutToGinGrid*)pGrid)->/*sig_Iec61850Cfg_Changed*/sig_GoutValue_Changed();
	}
	else if (nCol == STTINTELBOUTTOGIN_GRID_COL_INDEX_MAP)//开入
	{
		pGinCh->m_strAppChID.Format(_T("%s;"),pGinCh->m_strAppChIDText.GetString());
		((CSttIntelBoutToGinGrid*)pGrid)->UpdateData_ByDataType(pGinCh,nRow);
		emit ((CSttIntelBoutToGinGrid*)pGrid)->/*sig_Iec61850Cfg_Changed*/sig_GoutValue_Changed();
	}

	else if (nCol == STTINTELBOUTTOGIN_GRID_COL_INDEX_VALUE)
	{
		//((CSttIntelBoutToGinGrid*)pGrid)->UpdateData_Value(pGinCh,nRow);
		emit ((CSttIntelBoutToGinGrid*)pGrid)->sig_GoutValue_Changed();
	}
	//((CSttIntelBoutToGinGrid*)pGrid)->setAlternatingRowColors(true);
}

void CSttIntelBoutToGinGrid::UpdateData_ByDataType(CIecCfgGinCh *pGinCh,int nRow)
{
	long nIndex = pGinCh->m_strAppChID.Find(_T(";"));//界面显示使用m_strAppChIDText,实际存储使用m_strAppChID,暂时只考虑一对一映射的模式,考虑昂立、豪迈都采用此方式

	if (nIndex>0)
	{
		pGinCh->m_strAppChIDText = pGinCh->m_strAppChID.left(nIndex);
	}
	else
	{
		pGinCh->m_strAppChIDText = pGinCh->m_strAppChID;
	}
	pGinCh->CheckDefautValue();
	if (pGinCh->m_strDataType == _T("BOOLEAN"))
	{
		Show_DataType_Val(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_single_def_value,&pGinCh->m_strDefaultValue,EndEditCell_GinChSelChangged); 
		Show_DataType_Val(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_MAP,iecfg_GinAppChDataType,&pGinCh->m_strAppChIDText,EndEditCell_GinChSelChangged); 
		Show_StaticString(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_RESUIT,_T("--")); 
	} 
	else if (pGinCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_double_def_value,&pGinCh->m_strDefaultValue,EndEditCell_GinChSelChangged); 
		Show_DataType_Val(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_MAP,iecfg_GinAppChDataType,&pGinCh->m_strAppChIDText,EndEditCell_GinChSelChangged); 
		Show_StaticString(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_RESUIT,_T("--")); 
	}  
	else
	{
		Show_String(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_VALUE,&pGinCh->m_strDefaultValue,EndEditCell_AppCh_GinDefaultValue); 
		Show_StaticString(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_MAP,_T("--")); 
		Show_StaticString(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_RESUIT,_T("--")); 
	}
	setAlternatingRowColors(true);
}

void CSttIntelBoutToGinGrid::UpdateData_Inverse(QGV_ITEM *pCell,int nRow)
{
	if (pCell->lParam == 0)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pVCellData->pObj;

	if (pGinCh->m_strDataType == _T("BOOLEAN"))
	{
		if (pGinCh->m_strDefaultValue==_T("FALSE"))
		{
			pGinCh->m_strDefaultValue = _T("TRUE");
		}
		else
		{
			pGinCh->m_strDefaultValue = _T("FALSE");
		}

		Show_DataType_Val(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_single_def_value,&pGinCh->m_strDefaultValue,EndEditCell_GinChSelChangged); 
	} 
	else if (pGinCh->m_strDataType == _T("Dbpos"))
	{
		if (pGinCh->m_strDefaultValue == _T("[00]"))
		{
			pGinCh->m_strDefaultValue = _T("[11]");
		}
		else if (pGinCh->m_strDefaultValue == _T("[01]"))
		{
			pGinCh->m_strDefaultValue = _T("[10]");
		}
		else if (pGinCh->m_strDefaultValue == _T("[10]"))
		{
			pGinCh->m_strDefaultValue = _T("[01]");
		}
		else if (pGinCh->m_strDefaultValue == _T("[11]"))
		{
			pGinCh->m_strDefaultValue = _T("[00]");
		}

		Show_DataType_Val(pGinCh,nRow,STTINTELBOUTTOGIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_double_def_value,&pGinCh->m_strDefaultValue,EndEditCell_GinChSelChangged); 
	}
}

void CSttIntelBoutToGinGrid::UpdateState(int nCheckState)
{
	m_nCheckState=nCheckState;
}

void CSttIntelBoutToGinGrid::EndEditCell_AppCh_GinDefaultValue (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pVellData->pObj;
	ASSERT (pGinCh != NULL);
	CString strCellText = pCell->text();
	CString strOldDefaultValue = pGinCh->m_strDefaultValue;
	pGinCh->m_strDefaultValue = strCellText;
	pGinCh->CheckDefautValue();

	if (strCellText != pGinCh->m_strDefaultValue)
	{
		pCell->setText(pGinCh->m_strDefaultValue);
	}

	if (strOldDefaultValue != pGinCh->m_strDefaultValue)
	{
		emit ((CSttIntelBoutToGinGrid*)pGrid)->sig_GoutValue_Changed();
	}
}
void CSttIntelBoutToGinGrid::GridCellResultVlaues(float fResultTimeVlaue,char strCharacterIndex)
{
	if (m_pDatas == NULL)
	{
		return;
	}
	m_bBinFlag=FALSE;
	CString strResultVlaue,strResultVlaues;
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)m_pDatas;
	strResultVlaues.Format(_T("%.3fs"),fResultTimeVlaue);
	for (int i=0;i< m_pDatas->GetCount();i++)
	{
		QGV_ITEM *pCell = (QGV_ITEM *)item(i,STTINTELBOUTTOGIN_GRID_COL_INDEX_MAP);
		CString strId=pCell->text();
		strResultVlaue.Format(_T("开入%c"),strCharacterIndex);
		if (strcmp(strResultVlaue.GetString(),strId.GetString())==0&&m_nCheckState==Qt::Checked)
		{
			emit sig_GinRowIndex(i,fResultTimeVlaue);
			UpdateData_Inverse(pCell,i);
			Show_StaticString(pGinCh,i,STTINTELBOUTTOGIN_GRID_COL_INDEX_RESUIT,_T(strResultVlaues));	
			m_bBinFlag=TRUE;
		}
	}
	if (m_bBinFlag==FALSE&&m_nCheckState==Qt::Checked)
	{		
		CString strTmp;
		strTmp.AppendFormat(_T("开入%c不在该控制块中"),strCharacterIndex);
		CLogPrint::LogString(XLOGLEVEL_ERROR,strTmp); 
	}
}

void CSttIntelBoutToGinGrid::startInit()
{
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)m_pDatas;
	for (int i=0;i< m_pDatas->GetCount();i++)
	{
		Show_StaticString(pGinCh,i,STTINTELBOUTTOGIN_GRID_COL_INDEX_RESUIT,_T("--")); 
	}
}
bool CSttIntelBoutToGinGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type()==QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent*)event;
		mouseDoubleClickEvent((QMouseEvent*)pMouseEvent);
		return true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);
}

void CSttIntelBoutToGinGrid::mouseReleaseEvent(QMouseEvent *event)
{
#ifdef _PSX_QT_LINUX_
	if (!IsScrollMoving())
#endif
	{
		QMouseEvent *pEvent0 = new QMouseEvent(QEvent::MouseButtonDblClick, event->pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
		QApplication::postEvent(this, pEvent0);
	}

	QExBaseListGridBase::mouseReleaseEvent(event);
}
