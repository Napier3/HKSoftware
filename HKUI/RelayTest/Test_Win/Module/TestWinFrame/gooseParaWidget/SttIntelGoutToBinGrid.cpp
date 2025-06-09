#include "SttIntelGoutToBinGrid.h"
#include <QCheckBox>
#include <QHeaderView>
#include "../../Define.h"
#include <QDesktopWidget>
#include <QApplication>
#include "../../SttXTestMngrBaseApp.h"


#define STTINTELGOUTTOBIN_GRID_COL_INDEX_DESC                    1
#define STTINTELGOUTTOBIN_GRID_COL_INDEX_DATATYPE                2
#define STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE                   3
#define STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE                 4
#define STTINTELGOUTTOBIN_GRID_COL_INDEX_RESUIT                 5
//////////////////////////////////////////////////////////////////////////

QSttIntelGoutToBinCheckBoxDelegate::QSttIntelGoutToBinCheckBoxDelegate(QObject *parent)
: QExBaseListCheckBoxDelegate(parent)
{
	InitStyleSheet();
}

QSttIntelGoutToBinCheckBoxDelegate::~QSttIntelGoutToBinCheckBoxDelegate()
{

}
void QSttIntelGoutToBinCheckBoxDelegate::InitStyleSheet()
{
	CString strEmptyPath,strSelectPath,strUnSelectPath;
	strSelectPath =  _P_GetResourcePath();
	strSelectPath += _T("checked.png");
	strUnSelectPath =  _P_GetResourcePath();
	strUnSelectPath += _T("unchecked.png");
	strEmptyPath =  _P_GetResourcePath();
	strEmptyPath += _T("Empty.png");
	m_oEmptyPixmap.load(strEmptyPath);
	m_oEmptyPixmap.scaled(20,20);
	m_oSelectedPixmap.load(strSelectPath);
	m_oSelectedPixmap.scaled(20,20);
	m_oUnselectedPixmap.load(strUnSelectPath);
	m_oUnselectedPixmap.scaled(20,20);
}
//鼠标单击单元格的时候，重绘事件触发
void QSttIntelGoutToBinCheckBoxDelegate::paint(QPainter * painter,
										   const QStyleOptionViewItem & option,
										   const QModelIndex & index) const
{
	
	bool bChecked = index.model()->data(index, Qt::CheckStateRole).toBool();//绘制图片
	QRect rect = option.rect;
	QPoint pt = rect.center();

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if ((pCurItem != NULL)&&(pCurItem->lParam != 0))
	{
		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
		CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;

		if ((pGoutCh != NULL)&&((pGoutCh->m_strAppChID.Find("bout") == 0)||
			((pGoutCh->m_strDataType != _T("BOOLEAN"))&&(pGoutCh->m_strDataType != _T("Dbpos")))))
		{
			//			QItemDelegate::paint(painter,option,index);
			pt -= QPoint(m_oEmptyPixmap.width()/2,m_oEmptyPixmap.height()/2);
			painter->drawPixmap(pt, m_oEmptyPixmap);
			return;
		}
	}

	if(bChecked)
	{
		pt -= QPoint(m_oSelectedPixmap.width()/2,m_oSelectedPixmap.height()/2);
		painter->drawPixmap(pt, m_oSelectedPixmap);
	}
	else
	{
		pt -= QPoint(m_oUnselectedPixmap.width()/2,m_oUnselectedPixmap.height()/2);
		painter->drawPixmap(pt, m_oUnselectedPixmap);
	}
  

}

//单击事件发生，值翻转
bool QSttIntelGoutToBinCheckBoxDelegate::editorEvent(QEvent * event,
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
////////////////////////////////////////////////////////////////////////////

CSttIntelGoutToBinGrid::CSttIntelGoutToBinGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pDataType_DelegBase = NULL;
	m_pValue_DelegBase = NULL;
	m_pCheckBoxDelegateBase = NULL;
}

CSttIntelGoutToBinGrid::~CSttIntelGoutToBinGrid()
{

}

void CSttIntelGoutToBinGrid::SetRunState(long nRunState)
{
	if (nRunState == STT_UI_RUN_STATE_Stoped)
	{
		m_pDataType_DelegBase->SetEditable(TRUE);
		m_pValue_DelegBase->SetEditable(TRUE);
		setEditTriggers(QAbstractItemView::DoubleClicked);
		SetEditable();
	}
	else if (nRunState == STT_UI_RUN_STATE_StateTested_NotEditable)
	{
		m_pDataType_DelegBase->SetEditable(FALSE);
		m_pValue_DelegBase->SetEditable(TRUE);
		setEditTriggers(QAbstractItemView::NoEditTriggers);
		SetEditable(TRUE);
	}
	else
	{
		m_pDataType_DelegBase->SetEditable(TRUE);
		m_pValue_DelegBase->SetEditable(TRUE);
		setEditTriggers(QAbstractItemView::DoubleClicked);
		SetEditable(TRUE);
	}

	reset();
}

void CSttIntelGoutToBinGrid::InitGrid()
{
	InitGridTitle();
	SetEditable(TRUE);
	m_pDataType_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(STTINTELGOUTTOBIN_GRID_COL_INDEX_DATATYPE,m_pDataType_DelegBase);
	m_pValue_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,m_pValue_DelegBase);
    m_pCheckBoxDelegateBase = new QSttIntelGoutToBinCheckBoxDelegate(this);
	setItemDelegateForColumn(STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE,m_pCheckBoxDelegateBase);
	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_GridCellClicked(int,int)));
	setAlternatingRowColors(true);
}

void CSttIntelGoutToBinGrid::InitGridTitle()
{
	CString astrGridTitle[STTINTELGOUTTOBINGRID_GRID_COLS] = {_T("序号"),_T("描述"),_T("数据类型"),_T("数值"),_T("取反"),_T("测试结果")};
	int  iColType[STTINTELGOUTTOBINGRID_GRID_COLS]={QT_GVET_NOEDIT,QT_GVET_NOEDIT, QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[STTINTELGOUTTOBINGRID_GRID_COLS]={40, 250, 100, 100, 40, 140};
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if (rect.height() == 1800)
	{
		iGridWidth[0]=70;
		iGridWidth[2]=110;
		iGridWidth[4]=90;
	}	
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTINTELGOUTTOBINGRID_GRID_COLS);
	QHeaderView* pHeadLeft = verticalHeader();
	pHeadLeft->setVisible(false);
}

void CSttIntelGoutToBinGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
	CString nindex; 
	nindex.Format("%d",nRow+1);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pData;
	Show_StaticString(pData,nRow,0,&nindex); 
 	Show_String(pData,nRow,1,&pGoutCh->m_strName,EndEditCell_String); 
	Show_DataType_Val(pData,nRow,2,iecfg_GooseChDataType,&pGoutCh->m_strDataType,EndEditCell_GoutChSelChangged); 
	UpdateData_ByDataType(pGoutCh,nRow); 
	setAlternatingRowColors(true);
	nRow++;
}

void CSttIntelGoutToBinGrid::UpdateDatas_Revert()
{
	if (m_pDatas == NULL)
	{
		return;
	}
	CIecCfgGoutCh *pGoutCh=NULL;
	POS pos=m_pDatas->GetHeadPosition();
	int nRow = 0;
	setGooseResultVlaues();
	while (pos != NULL)
	{
		pGoutCh = (CIecCfgGoutCh*)m_pDatas->GetNext(pos);
		UpdateDatas_ByRevert(pGoutCh,nRow); 
		nRow++;
	}
	setAlternatingRowColors(true);
}


CDataType* CSttIntelGoutToBinGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CSttIntelGoutToBinGrid::EndEditCell_GoutChSelChangged (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;
	CDataTypeValue *pValue = NULL;
	if (nCol == STTINTELGOUTTOBIN_GRID_COL_INDEX_DATATYPE)
	{
		pGoutCh->CheckDefautValue();
		CDataType *pGooseChType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GooseChDataType);
		pValue = (CDataTypeValue *)pGooseChType->FindByID(pGoutCh->m_strDataType);
		pGoutCh->m_strDataTypeName = pValue->m_strName;

		((CSttIntelGoutToBinGrid*)pGrid)->UpdateData_ByDataType(pGoutCh,nRow);
		emit ((CSttIntelGoutToBinGrid*)pGrid)->sig_GoutValue_Changed();
	}
	else if (nCol == STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE)
	{
		((CSttIntelGoutToBinGrid*)pGrid)->UpdateData_Value(pGoutCh,nRow);
		emit ((CSttIntelGoutToBinGrid*)pGrid)->sig_GoutValue_Changed();
	}
}

void CSttIntelGoutToBinGrid::UpdateData_ByDataType(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,_T("--")); 
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE,_T("--")); 
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_RESUIT,_T("--")); 
		return;
	}

	pGoutCh->CheckDefautValue();
	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{	
		Show_DataType_Val(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_single_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
		ShowCheck_BOOLEAN(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_RESUIT,_T("--")); 
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_double_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
		ShowCheck_BOOLEAN(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_RESUIT,_T("--")); 
	} 
	else
	{	
		Show_String(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,&pGoutCh->m_strDefaultValue,EndEditCell_AppCh_GoutDefaultValue); 
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE,_T(""));  
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_RESUIT,_T("--")); 
	}
}

void CSttIntelGoutToBinGrid::EndEditCell_AppCh_GoutDefaultValue (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
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
		emit ((CSttIntelGoutToBinGrid*)pGrid)->sig_GoutValue_Changed();
	}
}


void CSttIntelGoutToBinGrid::UpdateData_Value(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE,_T("")); 
		return;
	}

	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		ShowCheck_BOOLEAN(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		ShowCheck_Dbpos(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE,&pGoutCh->m_strDefaultValue);  
	} 
}

void CSttIntelGoutToBinGrid::UpdateData_Inverse(QGV_ITEM *pCell,int nRow)
{
	if (pCell->lParam == 0)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;
	CString strCellText = pCell->text();
	if (strCellText==NULL)
	{
		pCell->setFlags(Qt::NoItemFlags);
	}
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
		Show_DataType_Val(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_single_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
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
		Show_DataType_Val(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_double_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
	}
}

void CSttIntelGoutToBinGrid::UpdateData_ByInverse(QGV_ITEM *pCell,int nRow)
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

	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{
		return;
	}
	pGoutCh->CheckDefautValue();
	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		if (nCheckState== Qt::Checked)
		{
			nCheckState = Qt::Unchecked;
			pGoutCh->m_strDefaultValue=_T("FALSE");
		}
		pCell->setCheckState((Qt::CheckState)nCheckState);
		Show_DataType_Val(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_single_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		if (nCheckState== Qt::Checked)
		{			
			nCheckState = Qt::Unchecked;
			pGoutCh->m_strDefaultValue = _T("[01]");			
		}
		pCell->setCheckState((Qt::CheckState)nCheckState);
		Show_DataType_Val(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,g_strGsChDtID_goose_out_ch_double_def_value,&pGoutCh->m_strDefaultValue,EndEditCell_GoutChSelChangged); 
	}
	else
	{
		nCheckState = Qt::Unchecked;
		pCell->setCheckState((Qt::CheckState)nCheckState);
	}
}
void CSttIntelGoutToBinGrid::UpdateDatas_ByRevert(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strAppChID.Find("bout") == 0)
	{
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,_T("--")/*&pGoutCh->m_strDefaultValue*/); 
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE,_T("--")); 
		Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_RESUIT,_T("--")); 
		return;
	}
	if (pGoutCh->m_strDataType == g_strGooseChType_Float)
	{
		pGoutCh->m_strDefaultValue = _T("0.0");
	}
	if (pGoutCh->m_strDataType == g_strGooseChType_Quality)
	{
		pGoutCh->m_strDefaultValue = _T("0X0000");
	}		
	if(pGoutCh->m_strDataType == g_strGooseChType_Time)
	{
		pGoutCh->m_strDefaultValue = _T("");
	}		
	if(pGoutCh->m_strDataType == g_strGooseChType_Time)
	{
		pGoutCh->m_strDefaultValue = _T("");
	}	
	if(pGoutCh->m_strDataType == g_strGooseChType_String)
	{
		pGoutCh->m_strAppChID = _T("0000000000000");
	}
	if(pGoutCh->m_strDataType == g_strGooseChType_Integer||pGoutCh->m_strDataType == g_strGooseChType_UInteger)
	{
		pGoutCh->m_strAppChID = _T("0");
	}
	Show_String(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_VALUE,&pGoutCh->m_strDefaultValue,EndEditCell_AppCh_GoutDefaultValue); 
	QGV_ITEM *pCell = GetCell(nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE);//取反复归为默认状态单点0,双点01
	UpdateData_ByInverse(pCell,nRow);
	Show_StaticString(pGoutCh,nRow,STTINTELGOUTTOBIN_GRID_COL_INDEX_RESUIT,_T("--")); 

}
void CSttIntelGoutToBinGrid::ShowCheck_BOOLEAN(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
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

void CSttIntelGoutToBinGrid::ShowCheck_Dbpos(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
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

BOOL CSttIntelGoutToBinGrid::IsCheckedState_ChValue(const CString &strChValue)
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

void CSttIntelGoutToBinGrid::slot_GridCellClicked(int row, int column)
{	
	if ((column == STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE)&&(IsEditable()))
	{
		QGV_ITEM *pCell = GetCell(row,column);
		UpdateData_Inverse(pCell,row);
		if (g_theSttXTestMngrBaseApp->m_bGooseFlag==true)
		{
			m_nRowIndex=row;//取最后一个的行数
			emit sig_GoutRowIndex(m_nRowIndex);
			emit sig_GoutValue_Changed();
			
		}
	}
}

void CSttIntelGoutToBinGrid::EnableInverseCol(BOOL bEnable)
{
	int nRows = GetDatasCount();
	for (int i=0;i<nRows;i++)
	{
		QTableWidgetItem* pitem = item(i,STTINTELGOUTTOBIN_GRID_COL_INDEX_INVERSE);
		if (pitem)
		{
			if (bEnable)
			{
				pitem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);				
			}
		}	
	}
}

void CSttIntelGoutToBinGrid::GridCellResultVlaues(float fResultTimeVlaue,char strCharacterIndex)//计时结束测试结果显示
{
	CString strResultVlaue=_T("");
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)m_pDatas;
	strResultVlaue.Format(_T("%c=%.3fs,"),strCharacterIndex,fResultTimeVlaue);

	//20240103 gongyiping 在同行的测试结果上有多个开入量的显示
	int nCharacterindex = m_strResultVlaues.Find(strCharacterIndex);//查找字符的下标
	int nPeriodindex = m_strResultVlaues.Find(",",nCharacterindex);//从查找到相同字符的下标查找“，”
	if (nPeriodindex >= 0)
	{
		CString strPreVlaue = m_strResultVlaues.Left(nCharacterindex);
		CString strEndVlaue = m_strResultVlaues.Mid(nPeriodindex+1);
		m_strResultVlaues=strPreVlaue+strEndVlaue;
	}
	m_strResultVlaues=m_strResultVlaues+strResultVlaue;
	for (int i=0;i< m_pDatas->GetCount();i++)
	{
		Show_StaticString(pGoutCh,m_nRowIndex,STTINTELGOUTTOBIN_GRID_COL_INDEX_RESUIT,_T(m_strResultVlaues));	
	}
}
void CSttIntelGoutToBinGrid::setGooseResultVlaues()//计时结束ResultVlaues初始化
{
	m_strResultVlaues=_T("");
}

void CSttIntelGoutToBinGrid::startInit()
{
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)m_pDatas;
	for (int i=0;i< m_pDatas->GetCount();i++)
	{
		Show_StaticString(pGoutCh,i,STTINTELGOUTTOBIN_GRID_COL_INDEX_RESUIT,_T("--")); 
	}

}