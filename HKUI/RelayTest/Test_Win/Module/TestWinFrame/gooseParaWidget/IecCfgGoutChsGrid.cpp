#include "IecCfgGoutChsGrid.h"
#include <QCheckBox>
#include <QHeaderView>
#include "../../Define.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include <QApplication>


#define IECCFGGOUTCHS_GRID_COL_INDEX_DESC                    0
#define IECCFGGOUTCHS_GRID_COL_INDEX_DATATYPE                1
#define IECCFGGOUTCHS_GRID_COL_INDEX_MAP                     2
#define IECCFGGOUTCHS_GRID_COL_INDEX_VALUE                   3
#define IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE                 4

//////////////////////////////////////////////////////////////////////////

QIecCfgGoutChsCheckBoxDelegate::QIecCfgGoutChsCheckBoxDelegate(QObject *parent)
: QExBaseListCheckBoxDelegate(parent)
{
// 	CString strEmptyPath;
// #ifdef _PSX_QT_WINDOWS_
// 	strEmptyPath =  _P_GetResourcePath();
// 	strEmptyPath += _T("Empty.png");
// #else
// 	strEmptyPath = ":/ctrls/images/Empty.png";
// #endif
// 	m_oEmptyPixmap.load(strEmptyPath);
// 	m_oEmptyPixmap.scaled(20,20);
}

QIecCfgGoutChsCheckBoxDelegate::~QIecCfgGoutChsCheckBoxDelegate()
{

}

//鼠标单击单元格的时候，重绘事件触发
void QIecCfgGoutChsCheckBoxDelegate::paint(QPainter * painter,
										const QStyleOptionViewItem & option,
										const QModelIndex & index) const
{
	bool bChecked = index.model()->data(index, Qt::CheckStateRole).toBool();//绘制图片
	//按钮的风格选项  
	QStyleOptionButton *checkBoxOption = new QStyleOptionButton();  
// 	QRect rect = option.rect;
// 	QPoint pt = rect.center();

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if ((pCurItem != NULL)&&(pCurItem->lParam != 0))
	{
		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
		CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;

		if ((pGoutCh != NULL)&&((pGoutCh->m_strAppChID.Find("bout") == 0)||
			((pGoutCh->m_strDataType != _T("BOOLEAN"))&&(pGoutCh->m_strDataType != _T("Dbpos")))))
		{
 			//bChecked = false;
			return;
			
		}
	}

	checkBoxOption->state |= QStyle::State_Enabled;  
	//根据值判断是否选中  
	if(bChecked)  
	{  
		checkBoxOption->state |= QStyle::State_On;  
	}  
	else  
	{  
		checkBoxOption->state |= QStyle::State_Off;  
	}  
	//返回QCheckBox几何形状  
	checkBoxOption->rect = CheckBoxRect(option);  
	//绘制QCheckBox  
	QApplication::style()->drawControl(QStyle::CE_CheckBox,checkBoxOption,painter); 
}


//单击事件发生，值翻转
bool QIecCfgGoutChsCheckBoxDelegate::editorEvent(QEvent * event,
											  QAbstractItemModel * model,
											  const QStyleOptionViewItem &/* option*/,
											  const QModelIndex & index)
{
	if(event->type()==QEvent::MouseButtonPress)
	{
		QVariant varValue = model->data(index,Qt::CheckStateRole);

		bool bValue=varValue.toBool();

		if(varValue.isValid())//如果当前值有效,则将当前状态取反
		{
			bValue=bValue?false:true;
		}
		else//否则将当前值置为1,即置为选择状态
		{
			bValue=true;
		}

		model->setData(index,bValue,Qt::CheckStateRole);
		//		index.setData();

		QGV_ITEM* pCurItem = GetCurrItem(index);

		if (pCurItem == NULL)
		{
			return true;
		}

		pCurItem->dwValue = bValue;

		if (pCurItem->lParam == 0)
		{
			return true;
		}

		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
// 		ASSERT(pVCellData->pnValue);
// 
// 		if( *(pVCellData->pnValue) != bValue )
// 		{
// 			*(pVCellData->pnValue)  = bValue;
// 		}

		CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;

		if ((pGoutCh != NULL)&&((pGoutCh->m_strAppChID.Find("bout") == 0)||
			((pGoutCh->m_strDataType != _T("BOOLEAN"))&&(pGoutCh->m_strDataType != _T("Dbpos")))))
		{
			
			return true;

		}

		if (pCurItem->m_pEditFunc != NULL)
		{
			QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
			pCurItem->m_pEditFunc(index.row(),index.column(),pCurItem,pExBaseListGridBase);
			pExBaseListGridBase->OnDataSelChanged(index.row(),index.column());
		}

		return true;//I have handled the event
	}

	return false;


}
//////////////////////////////////////////////////////////////////////////

CIecCfgGoutChsGrid::CIecCfgGoutChsGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pDataType_DelegBase = NULL;
	m_pMap_DelegBase = NULL;
	m_pValue_DelegBase = NULL;
}

CIecCfgGoutChsGrid::~CIecCfgGoutChsGrid()
{

}

void CIecCfgGoutChsGrid::SetRunState(long nRunState)
{
	if (nRunState == STT_UI_RUN_STATE_Stoped)
	{
		m_pDataType_DelegBase->SetEditable(TRUE);
		m_pMap_DelegBase->SetEditable(TRUE);
		m_pValue_DelegBase->SetEditable(TRUE);
		setEditTriggers(QAbstractItemView::DoubleClicked);
		SetEditable();
	}
	else if (nRunState == STT_UI_RUN_STATE_StateTested_NotEditable)
	{
		m_pDataType_DelegBase->SetEditable(FALSE);
		m_pMap_DelegBase->SetEditable(FALSE);
		m_pValue_DelegBase->SetEditable(FALSE);
		setEditTriggers(QAbstractItemView::NoEditTriggers);
		//SetEditable(FALSE);//202424 suyang 点表格中取反勾选框，数值不会改变，所以注销
	}
	else
	{
		m_pDataType_DelegBase->SetEditable(FALSE);
		m_pMap_DelegBase->SetEditable(FALSE);
		m_pValue_DelegBase->SetEditable(TRUE);
		setEditTriggers(QAbstractItemView::DoubleClicked);
		SetEditable(TRUE);
	}

	reset();//20220817 zhouhj 用于复归界面显示
}

void CIecCfgGoutChsGrid::InitGrid()
{
 	InitGridTitle();
	SetEditable(TRUE);
	m_pDataType_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(IECCFGGOUTCHS_GRID_COL_INDEX_DATATYPE,m_pDataType_DelegBase);
	m_pMap_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(IECCFGGOUTCHS_GRID_COL_INDEX_MAP,m_pMap_DelegBase);
	m_pValue_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,m_pValue_DelegBase);
 	m_pExBaseListCheckBoxDelegate = new QIecCfgGoutChsCheckBoxDelegate(this);
	setItemDelegateForColumn(IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,m_pExBaseListCheckBoxDelegate);
	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_GridCellClicked(int,int)));
}

void CIecCfgGoutChsGrid::InitGridTitle()
{
	CString astrGridTitle[IECCFGGOUTCHSGRID_GRID_COLS] = {/*_T("描述")*/g_sLangTxt_State_Description,/*_T("数据类型")*/g_sLangTxt_DataType,/*_T("映射")*/g_sLangTxt_Native_Maps,/*_T("数值")*/g_sLangTxt_Value,/*_T("取反")*/g_sLangTxt_Native_Reverse};
	int  iColType[IECCFGGOUTCHSGRID_GRID_COLS]={QT_GVET_NOEDIT, QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[IECCFGGOUTCHSGRID_GRID_COLS]={300, 150, 150, 150, 40};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGGOUTCHSGRID_GRID_COLS);
}

void CIecCfgGoutChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pData;
 	Show_String(pData,nRow,0,&pGoutCh->m_strName,EndEditCell_String); 
	Show_DataType_Val(pData,nRow,1,iecfg_GooseChDataType,&pGoutCh->m_strDataType,EndEditCell_GoutChSelChangged); 
	UpdateData_ByDataType(pGoutCh,nRow); 
  	nRow++;
}

CDataType* CIecCfgGoutChsGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CIecCfgGoutChsGrid::EndEditCell_GoutChSelChangged (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;

	if (nCol == IECCFGGOUTCHS_GRID_COL_INDEX_DATATYPE)
	{
		pGoutCh->CheckDefautValue();
		((CIecCfgGoutChsGrid*)pGrid)->UpdateData_ByDataType(pGoutCh,nRow);
		emit ((CIecCfgGoutChsGrid*)pGrid)->/*sig_Iec61850Cfg_Changed*/sig_GoutValue_Changed();
	}
	else if (nCol == IECCFGGOUTCHS_GRID_COL_INDEX_MAP)
	{
		((CIecCfgGoutChsGrid*)pGrid)->UpdateData_ByChMap(pGoutCh,nRow);
		emit ((CIecCfgGoutChsGrid*)pGrid)->/*sig_Iec61850Cfg_Changed*/sig_GoutValue_Changed();
	}
	else if (nCol == IECCFGGOUTCHS_GRID_COL_INDEX_VALUE)
	{
		((CIecCfgGoutChsGrid*)pGrid)->UpdateData_Value(pGoutCh,nRow);
		emit ((CIecCfgGoutChsGrid*)pGrid)->sig_GoutValue_Changed();
	}
}

void CIecCfgGoutChsGrid::UpdateData_ByDataType(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{
		if (pGoutCh->m_strDataType == _T("BOOLEAN"))
		{
			Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_MAP,g_strGsChDtID_goose_out_ch_single,&pGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		} 
		else if (pGoutCh->m_strDataType == _T("Dbpos"))
		{
			Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_MAP,g_strGsChDtID_goose_out_ch_double,&pGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		} 
		else
		{
			Show_StaticString(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_MAP,_T("--"));  
		}

		Show_StaticString(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,_T("--")/*&pGoutCh->m_strDefaultValue*/); 
		Show_StaticString(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,_T("--")); 
		return;
	}

	pGoutCh->CheckDefautValue();

	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_MAP,g_strGsChDtID_goose_out_ch_single,&pGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_single_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
		ShowCheck_BOOLEAN(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_MAP,g_strGsChDtID_goose_out_ch_double,&pGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_double_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
		ShowCheck_Dbpos(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
	} 
	else
	{
		Show_StaticString(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_MAP,_T("--")); 
		Show_String(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,&pGoutCh->m_strDefaultValue,EndEditCell_AppCh_GoutDefaultValue); 
		Show_StaticString(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,_T(""));  
		SetItemEnable(nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,TRUE);

	}
}

void CIecCfgGoutChsGrid::UpdateData_ByChMap(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{

		Show_StaticString(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,_T("--")/*&pGoutCh->m_strDefaultValue*/); 
		Show_StaticString(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,_T("--")); 
		return;
	}

	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_single_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
		ShowCheck_BOOLEAN(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_double_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
		ShowCheck_Dbpos(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
	} 
	else
	{
		Show_String(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,&pGoutCh->m_strDefaultValue,EndEditCell_AppCh_GoutDefaultValue); 
		Show_StaticString(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,_T(""));  
	}
}

void CIecCfgGoutChsGrid::EndEditCell_AppCh_GoutDefaultValue (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
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

	if (strOldDefaultValue != pGoutCh->m_strDefaultValue)
	{
		emit ((CIecCfgGoutChsGrid*)pGrid)->sig_GoutValue_Changed();
	}
}


void CIecCfgGoutChsGrid::UpdateData_Value(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{
		Show_StaticString(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,_T("")); 
		return;
	}

	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		ShowCheck_BOOLEAN(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		ShowCheck_Dbpos(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
	} 
}

void CIecCfgGoutChsGrid::UpdateData_AllValues(long nCheckState)
{
	if (m_pDatas == NULL)
	{
		return;
	}

	long nDataCount = m_pDatas->GetCount();
	QGV_ITEM *pCell = NULL;

	for (int nIndex = 0;nIndex<nDataCount;nIndex++)
	{
		pCell = GetCell(nIndex,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE);
		UpdateData_Inverse(pCell,nIndex);
	}
}

void CIecCfgGoutChsGrid::UpdateData_Inverse(QGV_ITEM *pCell,int nRow)
{
	if (pCell->lParam == 0)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;
	long nCheckState = Qt::Checked;

	if (IsCheckedState_ChValue(pGoutCh->m_strDefaultValue))
	{
		nCheckState = Qt::Unchecked;
	}

	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{
		return;
	}

	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		if (nCheckState== Qt::Checked)
		{
			pGoutCh->m_strDefaultValue = _T("TRUE");
		}
		else
		{
			pGoutCh->m_strDefaultValue = _T("FALSE");
		}

		pCell->setCheckState((Qt::CheckState)nCheckState);
		Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_single_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		if (nCheckState== Qt::Checked)
		{
			if (pGoutCh->m_strDefaultValue == _T("[00]"))
			{
				pGoutCh->m_strDefaultValue = _T("[11]");
			}
			else if (pGoutCh->m_strDefaultValue == _T("[01]"))
			{
				pGoutCh->m_strDefaultValue = _T("[10]");
			}
		}
		else
		{
			if (pGoutCh->m_strDefaultValue == _T("[10]"))
			{
				pGoutCh->m_strDefaultValue = _T("[01]");
			}
			else if (pGoutCh->m_strDefaultValue == _T("[11]"))
			{
				pGoutCh->m_strDefaultValue = _T("[00]");
			}
		}

		pCell->setCheckState((Qt::CheckState)nCheckState);
		Show_DataType_Val(pGoutCh,nRow,IECCFGGOUTCHS_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_double_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
	}
}

void CIecCfgGoutChsGrid::ShowCheck_BOOLEAN(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
{
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,_T(""),bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pString, pData,NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_CHECKBOX;
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pData;
	pItem->m_pEditFunc = NULL;

	if (pGoutCh->m_strDefaultValue == _T("TRUE"))
	{
		pItem->setCheckState(Qt::Checked);
	} 
	else
	{
		pItem->setCheckState(Qt::Unchecked);
	}

	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void CIecCfgGoutChsGrid::ShowCheck_Dbpos(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
{
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,_T(""),bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pString, pData,NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_CHECKBOX;
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pData;
	pItem->m_pEditFunc = NULL;

	if ((pGoutCh->m_strDefaultValue == _T("[10]"))||(pGoutCh->m_strDefaultValue == _T("[11]")))
	{
		pItem->setCheckState(Qt::Checked);
	} 
	else
	{
		pItem->setCheckState(Qt::Unchecked);
	}

	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}

	if (!bHasSetItem)
	{
	setItem(nRow,nCol,pItem);
	}
}

BOOL CIecCfgGoutChsGrid::IsCheckedState_ChValue(const CString &strChValue)
{
	if (strChValue == _T("TRUE"))
	{
		return TRUE;
	}

	if ((strChValue == _T("[10]"))||(strChValue == _T("[11]")))
	{
		return TRUE;
	}

	return FALSE;
}

void CIecCfgGoutChsGrid::slot_GridCellClicked(int row, int column)
{
	if ((column == IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE)&&(IsEditable()))
	{
		QGV_ITEM *pCell = GetCell(row,column);
		UpdateData_Inverse(pCell,row);
		emit sig_GoutValue_Changed();
	}
}

void CIecCfgGoutChsGrid::EnableInverseCol(BOOL bEnable)
{
	int nRows = GetDatasCount();
	for (int i=0;i<nRows;i++)
	{
		QTableWidgetItem* pitem = item(i,IECCFGGOUTCHS_GRID_COL_INDEX_INVERSE);
		if (pitem)
		{
			if (bEnable)
			{
				pitem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
			}
			else
			{
				pitem->setFlags(Qt::NoItemFlags);
			}
		}
	}
}