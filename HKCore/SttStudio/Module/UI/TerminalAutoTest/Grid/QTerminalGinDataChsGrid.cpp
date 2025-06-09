#include "QTerminalGinDataChsGrid.h"
#include "../SttMacroParaEditViewTerminalAutoTest.h"

QGinMapComBoxDelegBase::QGinMapComBoxDelegBase(QObject *parent): QIecCfgChsComBoxDelegBase(parent)
{

}

QGinMapComBoxDelegBase::~QGinMapComBoxDelegBase()
{

}

void QGinMapComBoxDelegBase::setEditorData(QWidget *editor, const QModelIndex &index) const
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
	CIecCfgGinDatas *pIecCfgGinDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGinMngr();
	//CIecCfgGinData* pIecCfgGinData = (CIecCfgGinData*)pIecCfgGinDatas->FindByClassID(CFGCLASSID_CIECCFGGINDATA);
	//CIecCfgGinChs *pGinData = (CIecCfgGinChs*)pIecCfgGinData->FindByClassID(CFGCLASSID_CIECCFGCHSGIN);

	CIecCfgGinData* pIecCfgGinData = NULL;
	POS pos = pIecCfgGinDatas->GetHeadPosition();
	CIecCfgGinChs *pGinData = NULL;

	CIecCfgGinCh *pIecCfgGinCh = NULL;
	CString strIndex;
	QVector<CString> oVector; 


	while(pos)
	{
		pIecCfgGinData = (CIecCfgGinData*)pIecCfgGinDatas->GetNext(pos);
		pGinData = (CIecCfgGinChs*)pIecCfgGinData->FindByClassID(CFGCLASSID_CIECCFGCHSGIN);

		POS pos1 = pGinData->GetHeadPosition();
		while(pos1)
		{
			pIecCfgGinCh = (CIecCfgGinCh *)pGinData->GetNext(pos1);

			if(pIecCfgGinCh != pGinCh && pIecCfgGinCh->m_strDevChID != _T("v0")&& pIecCfgGinCh->m_strDevChID != _T("v01"))
			{
				strIndex = pIecCfgGinCh->m_strDevChID;
				oVector.push_back(strIndex);
			}
		}
	}

	if (pDataType != NULL)
	{
		QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
		pComboBox->clear();
		QString strItem = index.model()->data(index,Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = NULL;
		POS pos = pDataType->GetHeadPosition();

		long nCurrIndex = 0,nCurrIndex2 = 0;

		while (pos)
		{
			pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);

			if (pDataTypeValue->m_strName == strItem)
			{
				nCurrIndex2 = nCurrIndex;
			}

 			bool b = oVector.contains(pDataTypeValue->m_strID);
 
  			if (b == false)
  			{
  				pComboBox->addItem(pDataTypeValue->m_strName);
  				nCurrIndex++;
  			}
		}

		if (nCurrIndex2 >= 0)
		{
			pComboBox->setCurrentIndex(nCurrIndex2);
		}	
	}
	else
	{
		QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
		lineEdit->setText(index.model()->data(index, Qt::EditRole).toString()); 
	}
}


void QGinMapComBoxDelegBase::setModelData(QWidget *editor, QAbstractItemModel *model, 
											   const QModelIndex &index) const
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
		CDataTypeValue* pDataTypeValue = (CDataTypeValue*)pDataType->FindByName(comboBox->currentText());
		ASSERT(pDataTypeValue);
		//CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pVCellData->pObj;

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


QTerminalGinDataChsGrid::QTerminalGinDataChsGrid(QWidget* pparent):CIecCfgChsGridBase(pparent)
{

}

QTerminalGinDataChsGrid::~QTerminalGinDataChsGrid()
{

}

void QTerminalGinDataChsGrid::InitGrid()
{
	InitGridTitle();
	m_pChType_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(1,m_pChType_DelegBase);
	m_pChMap_DelegBase = new /*QExBaseListComBoxDelegBase*/QGinMapComBoxDelegBase(this);
	setItemDelegateForColumn(2,m_pChMap_DelegBase);
	
	SetEditable(TRUE);
	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void QTerminalGinDataChsGrid::InitGridTitle()
{
	CString astrGridTitle[GINDATACHS_GRID_COLS];
	astrGridTitle[0]= _T("通道描述");  
	astrGridTitle[1]= _T("通道类型"); 
	astrGridTitle[2]= _T("开出映射"); 
	astrGridTitle[3]= _T("关联值"); 

	int iGridWidth[GINDATACHS_GRID_COLS]={300, 200,200,200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, GINDATACHS_GRID_COLS);
}

void QTerminalGinDataChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFGGINCH)
	{
		return;
	}

	CIecCfgGinCh *pIecCfgGinCh = (CIecCfgGinCh*)pData;
	Show_String(pData,nRow,0,&pIecCfgGinCh->m_strName);
	Show_DataType_Val(pData, nRow, 1,iecfg_GooseChDataType, &pIecCfgGinCh->m_strDataType,EndEditCell_GinChSelChangged);
	UpdateData_ByDataType(pIecCfgGinCh,nRow);
	nRow++;
}

void QTerminalGinDataChsGrid::UpdateData_ByDataType(CIecCfgGinCh *pIecCfgGinCh,int nRow)
{
	//long nIndex = pIecCfgGinCh->m_strAppChID.Find(_T(";"));//界面显示使用m_strAppChIDText,实际存储使用m_strAppChID,暂时只考虑一对一映射的模式,考虑昂立、豪迈都采用此方式

	//if (nIndex>0)
	//{
	//	pIecCfgGinCh->m_strAppChIDText = pIecCfgGinCh->m_strAppChID.left(nIndex);
	//}
	//else
	//{
		pIecCfgGinCh->m_strAppChIDText = pIecCfgGinCh->m_strDevChID;
	//}

	if (pIecCfgGinCh->m_strDataType == _T("BOOLEAN"))
	{
		Show_DataType_Val(pIecCfgGinCh,nRow,2,g_strGsChDtID_goose_out_ch_single,&pIecCfgGinCh->m_strDevChID,EndEditCell_GinChSelChangged); 
	} 
	else if (pIecCfgGinCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pIecCfgGinCh,nRow,2,g_strGsChDtID_goose_out_ch_double,&pIecCfgGinCh->m_strDevChID,EndEditCell_GinChSelChangged); 
	} 
	else
	{
		pIecCfgGinCh->m_strAppChID = _T("");
		Show_StaticString(pIecCfgGinCh,nRow,2,_T("--")); 
	}
	
	UpdateData_ByChMap(pIecCfgGinCh,nRow);
}


void QTerminalGinDataChsGrid::EndEditCell_GinChSelChangged (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pVCellData->pObj;

	if (nCol == 1)
	{
		((QTerminalGinDataChsGrid*)pGrid)->UpdateData_ByDataType(pGinCh,nRow);
		CIecCfgGinDatas *pIecCfgGinDatas = (CIecCfgGinDatas*)pGinCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);

		if (pIecCfgGinDatas != NULL)
		{
			pIecCfgGinDatas->InitGinAppChMaps();
		}
	}
	else if (nCol == 2)
	{
		pGinCh->m_strAppChID.Format(_T("%s;"),pGinCh->m_strDevChID.GetString());
		((QTerminalGinDataChsGrid*)pGrid)->UpdateData_ByChMap(pGinCh,nRow);
	}
}

void QTerminalGinDataChsGrid::UpdateData_ByChMap(CIecCfgGinCh *pGinCh,int nRow)
{
	if (pGinCh->m_strDataType == _T("Timestamp") || pGinCh->m_strDataType == _T("Quality")
		||pGinCh->m_strDataType == _T("FLOAT32") || pGinCh->m_strDataType == _T("VisString64")
		||pGinCh->m_strDataType == _T("Struct") || pGinCh->m_strDataType == _T("INT32") ||  pGinCh->m_strDataType == _T("INT32U"))
	{
		Show_StaticString(pGinCh,nRow,3,_T("--"));
		return;
	}
	if (pGinCh->m_strDataType == _T("BOOLEAN") || pGinCh->m_strDataType == _T("Dbpos"))	
	{
		UpdateData_ByDevCh(pGinCh,nRow);
	}
}

void QTerminalGinDataChsGrid::UpdateData_ByDevCh(CIecCfgGinCh *pGinCh,int nRow)
{
	QMap<QString, QString> channelMap;
	channelMap.insert(_T("bout1"), _T("bin1;"));
	channelMap.insert(_T("bout2"), _T("bin2;"));
	channelMap.insert(_T("bout3"), _T("bin3;"));
	channelMap.insert(_T("bout4"), _T("bin4;"));
	channelMap.insert(_T("bout5"), _T("bin5;"));
	channelMap.insert(_T("bout6"), _T("bin6;"));
	channelMap.insert(_T("bout7"), _T("bin7;"));
	channelMap.insert(_T("bout8"), _T("bin8;"));

	QString devChID = pGinCh->m_strDevChID;
	if (channelMap.contains(devChID))
	{
		pGinCh->m_strAppChID = channelMap.value(devChID);
		QChar displayChar = QChar('A' + (devChID.right(1).toInt() - 1));
		QString showString = QString("开入%1").arg(displayChar);
		Show_StaticString(pGinCh, nRow, 3, showString);
	}
	else
	{
		if (pGinCh->m_strDataType == _T("BOOLEAN"))	
		{
			pGinCh->m_strAppChID = _T("v0");
		}
		else if (pGinCh->m_strDataType == _T("Dbpos"))
		{
			pGinCh->m_strAppChID = _T("v01");
		}
		Show_StaticString(pGinCh,nRow,3,_T("--"));
	}
}
