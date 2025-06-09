#include "IecCfgChsGrid.h"

CIecCfgChsGrid::CIecCfgChsGrid(long nType, QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pIecCfgChs = NULL;
	m_nType = nType;
}

CIecCfgChsGrid::~CIecCfgChsGrid(void)
{
}

void CIecCfgChsGrid::InitGrid()
{
	InitGridTitle();
	m_pChType_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(1,m_pChType_DelegBase);
	if (m_nType == IECCFGGINCHSGRID)
	{
		m_pChMap_DelegBase = new QIecCfgGinChsComBoxDelegate(this);
		setItemDelegateForColumn(2,m_pChMap_DelegBase);
	}
	else if (m_nType == IECCFGGOUTCHSGRID)
	{
		m_pChOutType_DelegBase = new QIecCfgChsComBoxDelegBase(this);
		setItemDelegateForColumn(2,m_pChOutType_DelegBase);
	}
	
	SetEditable(TRUE);
}

void CIecCfgChsGrid::InitGridTitle()
{
	CString astrGridTitle[CIECCFGCHSGRID_COL] = {_T("通道描述"),_T("通道类型"),_T("开入(出)映射")};
	int iGridWidth[CIECCFGCHSGRID_COL]={400,300,300};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CIECCFGCHSGRID_COL);
}

void CIecCfgChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow/*=TRUE*/)
{
	long strId = pData->GetClassID();
	if (pData->GetClassID() == CFGCLASSID_CIECCFGGINCH)
	{
		CIecCfgGinCh *pIecCfgGinCh = (CIecCfgGinCh*)pData;
		Show_StaticString(pData,nRow,0,&pIecCfgGinCh->m_strName);
		Show_DataType_Val(pData, nRow, 1,iecfg_GooseChDataType, &pIecCfgGinCh->m_strDataType,EndEditCell_GinChSelChangged);
		UpdateGinData_ByDataType(pIecCfgGinCh, nRow);
	}
	else if (pData->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
	{
		CIecCfgGoutCh *pIecCfgGoutCh = (CIecCfgGoutCh*)pData;
		Show_StaticString(pData,nRow,0,&pIecCfgGoutCh->m_strName);
		Show_DataType_Val(pData, nRow, 1,iecfg_GooseChDataType, &pIecCfgGoutCh->m_strDataType,EndEditCell_GoutChSelChangged);
		UpdateGoutData_ByDataType(pIecCfgGoutCh, nRow);
	}
	else
	{
		return;
	}

	nRow++;
}

void CIecCfgChsGrid::InitData(CIecCfgChsBase *pIecCfgChs)
{
	m_pIecCfgChs = pIecCfgChs;
	this->ShowDatas(m_pIecCfgChs);
}

CDataType* CIecCfgChsGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CIecCfgChsGrid::UpdateGinData_ByDataType(CIecCfgGinCh *pIecCfgGinCh, int nRow)
{
	long nIndex = pIecCfgGinCh->m_strAppChID.Find(_T(";"));//界面显示使用m_strAppChIDText,实际存储使用m_strAppChID,暂时只考虑一对一映射的模式,考虑昂立、豪迈都采用此方式

	if (nIndex>0)
	{
		pIecCfgGinCh->m_strAppChIDText = pIecCfgGinCh->m_strAppChID.left(nIndex);
	}
	else
	{
		pIecCfgGinCh->m_strAppChIDText = pIecCfgGinCh->m_strAppChID;
	}

	if (pIecCfgGinCh->m_strDataType == _T("BOOLEAN"))
	{
		Show_DataType_Val(pIecCfgGinCh,nRow,2,iecfg_GinAppChDataType,&pIecCfgGinCh->m_strAppChIDText,EndEditCell_GinChSelChangged); 
	} 
	else if (pIecCfgGinCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pIecCfgGinCh,nRow,2,iecfg_GinAppChDataType,&pIecCfgGinCh->m_strAppChIDText,EndEditCell_GinChSelChangged); 
	} 
	else
	{
		pIecCfgGinCh->m_strAppChID = _T("");
		Show_StaticString(pIecCfgGinCh,nRow,2,_T("--")); 
	}

}

void CIecCfgChsGrid::UpdateGoutData_ByDataType(CIecCfgGoutCh *pIecCfgGoutCh, int nRow)
{
	if (pIecCfgGoutCh->m_strAppChID.Find("bout") == 0)
	{
		if (pIecCfgGoutCh->m_strDataType == _T("BOOLEAN"))
		{
			Show_DataType_Val(pIecCfgGoutCh,nRow,2,g_strGsChDtID_goose_out_ch_single,&pIecCfgGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		} 
		else if (pIecCfgGoutCh->m_strDataType == _T("Dbpos"))
		{
			Show_DataType_Val(pIecCfgGoutCh,nRow,2,g_strGsChDtID_goose_out_ch_double,&pIecCfgGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
		} 
		else
		{
			Show_StaticString(pIecCfgGoutCh,nRow,2,_T("--"));  
		}

		return;
	}

	if (pIecCfgGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		Show_DataType_Val(pIecCfgGoutCh,nRow,2,g_strGsChDtID_goose_out_ch_single,&pIecCfgGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
	} 
	else if (pIecCfgGoutCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pIecCfgGoutCh,nRow,2,g_strGsChDtID_goose_out_ch_double,&pIecCfgGoutCh->m_strAppChID,EndEditCell_GoutChSelChangged); 
	} 
	else
	{
		Show_StaticString(pIecCfgGoutCh,nRow,2,_T("--")); 
		pIecCfgGoutCh->CheckDefautValue();
	}

}

void CIecCfgChsGrid::EndEditCell_GoutChSelChangged( int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid )
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;

	if (nCol == 1)
	{
		pGoutCh->CheckDefautValue();
		((CIecCfgChsGrid*)pGrid)->UpdateGoutData_ByDataType(pGoutCh,nRow);
	}
}

void CIecCfgChsGrid::EndEditCell_GinChSelChangged( int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid )
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pVCellData->pObj;

	if (nCol == 1)
	{
		((CIecCfgChsGrid*)pGrid)->UpdateGinData_ByDataType(pGinCh,nRow);
		CIecCfgGinDatas *pIecCfgGinDatas = (CIecCfgGinDatas*)pGinCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);

		if (pIecCfgGinDatas != NULL)
		{
			pIecCfgGinDatas->InitGinAppChMaps();
		}
	}
	else if (nCol == 2)
	{
		pGinCh->m_strAppChID.Format(_T("%s;"),pGinCh->m_strAppChIDText.GetString());
		((CIecCfgChsGrid*)pGrid)->UpdateGinData_ByDataType(pGinCh,nRow);
	}
}

void CIecCfgChsGrid::UpdateChDatas( CExBaseList *pCurrSelData )
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase *)pCurrSelData;

	if (pIecCfgData == NULL)
	{
		InitData(NULL);
	}
	else
	{
		InitData(pIecCfgData->m_pCfgChs);
	}

}

QIecCfgGinChsComBoxDelegate::QIecCfgGinChsComBoxDelegate( QObject *parent/*=NULL*/ ): QIecCfgChsComBoxDelegBase(parent)
{

}

QIecCfgGinChsComBoxDelegate::~QIecCfgGinChsComBoxDelegate()
{

}

void QIecCfgGinChsComBoxDelegate::setEditorData( QWidget * editor, const QModelIndex &index ) const
{
	if (!m_bEditable)
	{
		return;
	}

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if (pCurItem == NULL)
	{
		return;
	}

	if (pCurItem->lParam == 0)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
	ASSERT(pVCellData->pExBaseList != NULL);
	CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pVCellData->pObj;

	if (pDataType != NULL)
	{
		QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
		pComboBox->clear();
		int nCurIndex = -1,nIndex = 0;
		QString strItem = index.model()->data(index,Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = NULL;
		CIecCfgGinDatas *pIecCfgGinDatas = (CIecCfgGinDatas*)pGinCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);
		CIecCfgGinAppChMaps* pIecCfgGinAppChMaps = pIecCfgGinDatas->GetIecCfgGinAppChMaps();
		CIecCfgGinAppChMap* pIecCfgGinAppChMap = NULL;
		POS pos = pDataType->GetHeadPosition();

		while (pos)
		{
			pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);
			pIecCfgGinAppChMap = (CIecCfgGinAppChMap*)pIecCfgGinAppChMaps->FindByID(pDataTypeValue->m_strID);

			if ((pIecCfgGinAppChMap!= NULL)&&(pIecCfgGinAppChMap->m_pIecCfgGinCh != NULL)&&(pDataTypeValue->m_strName != strItem))
			{
				continue;
			}

			if (pDataTypeValue->m_strName == strItem)
			{
				nCurIndex = nIndex;
			}

			pComboBox->addItem(pDataTypeValue->m_strName);
			nIndex++;
		}

		if (nCurIndex>=0)
		{
			pComboBox->setCurrentIndex(nCurIndex);
			pComboBox->showPopup();
		}
	}
	else
	{
		QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
		lineEdit->setText(index.model()->data(index, Qt::EditRole).toString()); 
	}
}

void QIecCfgGinChsComBoxDelegate::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	if (!m_bEditable)
	{
		return;
	}

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if (pCurItem == NULL)
	{
		return;
	}

	if (pCurItem->lParam == 0)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;

	if (pVCellData->pExBaseList != NULL)
	{
		QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
		model->setData(index,comboBox->currentText(),Qt::EditRole);
		CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;
		QString strItem = index.model()->data(index,Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = (CDataTypeValue*)pDataType->FindByName(comboBox->currentText());//   ->GetAtIndex(comboBox->currentIndex());
		ASSERT(pDataTypeValue);
		CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pVCellData->pObj;

		CIecCfgGinDatas *pIecCfgGinDatas = (CIecCfgGinDatas*)pGinCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);

		if (pIecCfgGinDatas != NULL)
		{
			CIecCfgGinAppChMaps* pIecCfgGinAppChMaps = pIecCfgGinDatas->GetIecCfgGinAppChMaps();
			CIecCfgGinAppChMap *pIecCfgGinAppChMapNew = (CIecCfgGinAppChMap*)pIecCfgGinAppChMaps->FindByID(pDataTypeValue->m_strID);
			CIecCfgGinAppChMap *pIecCfgGinAppChMapOld = (CIecCfgGinAppChMap*)pIecCfgGinAppChMaps->FindByID(pGinCh->m_strAppChIDText);

			if (pIecCfgGinAppChMapNew != NULL)
			{
				if (pIecCfgGinAppChMapNew->m_pIecCfgGinCh != NULL)
				{
					if (pIecCfgGinAppChMapNew != pIecCfgGinAppChMapOld)
					{
					}

					if (pCurItem->m_pEditFunc != NULL)
					{
						QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
						pCurItem->m_pEditFunc(index.row(),index.column(),pCurItem,pExBaseListGridBase);
					}

					return;	 					
				}
				else
				{
					pIecCfgGinAppChMapNew->m_pIecCfgGinCh = pGinCh;
				}
			}

			if (pIecCfgGinAppChMapOld != NULL)
			{
				pIecCfgGinAppChMapOld->m_pIecCfgGinCh = NULL;
			}
		}

		*(pVCellData->pString) = pDataTypeValue->m_strID;
	}
	else
	{
		QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(editor);
		QString text = pLineEdit->text();  
		model->setData(index, text, Qt::EditRole);
		*pVCellData->pString = text;
	}

	if (pCurItem->m_pEditFunc != NULL)
	{
		QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
		pCurItem->m_pEditFunc(index.row(),index.column(),pCurItem,pExBaseListGridBase);
	}
}
