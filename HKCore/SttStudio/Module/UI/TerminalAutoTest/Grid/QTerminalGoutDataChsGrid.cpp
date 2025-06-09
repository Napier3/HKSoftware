#include "QTerminalGoutDataChsGrid.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../SttMacroParaEditViewTerminalAutoTest.h"

QGoutMapComBoxDelegBase::QGoutMapComBoxDelegBase(QObject *parent): QIecCfgChsComBoxDelegBase(parent)
{

}

QGoutMapComBoxDelegBase::~QGoutMapComBoxDelegBase()
{

}

void QGoutMapComBoxDelegBase::setEditorData(QWidget *editor, const QModelIndex &index) const
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
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;
	CIecCfgGoutDatas *pIecCfgGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
	//CIecCfgGoutData* pIecCfgGoutData = (CIecCfgGoutData*)pIecCfgGoutDatas->FindByClassID(CFGCLASSID_CIECCFGGOUTDATA);
	//CIecCfgGoutChs *pGoutData = (CIecCfgGoutChs*)pIecCfgGoutData->FindByClassID(CFGCLASSID_CIECCFGCHSGOUT);


	CIecCfgGoutData* pIecCfgGoutData = NULL;
	CIecCfgGoutChs *pGoutData = NULL;
	POS pos = pIecCfgGoutDatas->GetHeadPosition();
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;
	CString strIndex;
	QVector<CString> oVector; 

	while(pos)
	{
		pIecCfgGoutData = (CIecCfgGoutData*)pIecCfgGoutDatas->GetNext(pos);
		pGoutData = (CIecCfgGoutChs*)pIecCfgGoutData->FindByClassID(CFGCLASSID_CIECCFGCHSGOUT);

		POS pos1 = pGoutData->GetHeadPosition();
		while(pos1)
		{
			pIecCfgGoutCh = (CIecCfgGoutCh *)pGoutData->GetNext(pos1);

			if(pIecCfgGoutCh != pGoutCh && pIecCfgGoutCh->m_strDevChID != _T("none"))
			{
				strIndex = pIecCfgGoutCh->m_strDevChID;
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


void QGoutMapComBoxDelegBase::setModelData(QWidget *editor, QAbstractItemModel *model, 
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
		//CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;

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

QTerminalGoutDataChsGrid::QTerminalGoutDataChsGrid(QWidget* parent):CIecCfgChsGridBase(parent)
{
	
}

QTerminalGoutDataChsGrid::~QTerminalGoutDataChsGrid()
{

}

void QTerminalGoutDataChsGrid::InitGrid()
{
	InitGridTitle();
	m_pChType_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(1,m_pChType_DelegBase);
	m_pChMap_DelegBase = new /*QExBaseListComBoxDelegBase*/QGoutMapComBoxDelegBase(this);
	setItemDelegateForColumn(2,m_pChMap_DelegBase);

	SetEditable(TRUE);
}

void QTerminalGoutDataChsGrid::InitGridTitle()
{
	CString astrGridTitle[GOUTDATACHS_GRID_COLS];
	astrGridTitle[0]= _T("通道描述");  
	astrGridTitle[1]= _T("通道类型"); 
	astrGridTitle[2]= _T("开入映射"); 
	astrGridTitle[3]= _T("关联值"); 

	int iGridWidth[GOUTDATACHS_GRID_COLS]={300, 200,200,200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, GOUTDATACHS_GRID_COLS);
}

void QTerminalGoutDataChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFGGOUTCH)
	{
		return;
	}

	CIecCfgGoutCh *pIecCfgGoutCh = (CIecCfgGoutCh*)pData;
	Show_String(pData,nRow,0,&pIecCfgGoutCh->m_strName);
	Show_DataType_Val(pData, nRow, 1,iecfg_GooseChDataType, &pIecCfgGoutCh->m_strDataType,EndEditCell_GoutChSelChangged);
	UpdateData_ByDataType(pIecCfgGoutCh,nRow);


	nRow++;
}

void QTerminalGoutDataChsGrid::EndEditCell_GoutChSelChangged (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVCellData->pObj;

	if (nCol == 1)
	{
		((QTerminalGoutDataChsGrid*)pGrid)->UpdateData_ByDataType(pGoutCh,nRow);
	}
	else if (nCol == 2)
	{
		((QTerminalGoutDataChsGrid*)pGrid)->UpdateData_ByChMap(pGoutCh,nRow);
	}
	
}

void QTerminalGoutDataChsGrid::UpdateData_ByDataType(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		Show_DataType_Val(pGoutCh,nRow,2,iecfg_GinAppChDataType,&pGoutCh->m_strDevChID,EndEditCell_GoutChSelChangged); 
	} 
	else if (pGoutCh->m_strDataType == _T("Dbpos"))
	{
		Show_DataType_Val(pGoutCh,nRow,2,iecfg_GinAppChDataType,&pGoutCh->m_strDevChID,EndEditCell_GoutChSelChangged); 
	} 
	else
	{
		Show_StaticString(pGoutCh,nRow,2,_T("--")); 
	}

	UpdateData_ByChMap(pGoutCh,nRow);
}

void QTerminalGoutDataChsGrid::UpdateData_ByChMap(CIecCfgGoutCh *pGoutCh,int nRow)
{
	if (pGoutCh->m_strDataType == _T("Timestamp") || pGoutCh->m_strDataType == _T("Quality")
		||pGoutCh->m_strDataType == _T("FLOAT32") || pGoutCh->m_strDataType == _T("VisString64")
		||pGoutCh->m_strDataType == _T("Struct") || pGoutCh->m_strDataType == _T("INT32") ||  pGoutCh->m_strDataType == _T("INT32U"))
	{
		Show_StaticString(pGoutCh,nRow,3,_T("--"));
		return;
	}
	if (pGoutCh->m_strDataType == _T("BOOLEAN") || pGoutCh->m_strDataType == _T("Dbpos"))	
	{
		UpdateData_ByDevCh(pGoutCh,nRow);
	}
}

void QTerminalGoutDataChsGrid::UpdateData_ByDevCh(CIecCfgGoutCh *pGoutCh,int nRow)
{
	QMap<QString, QString> channelMap;
	channelMap.insert(_T("bin1"), _T("bout1"));
	channelMap.insert(_T("bin2"), _T("bout2"));
	channelMap.insert(_T("bin3"), _T("bout3"));
	channelMap.insert(_T("bin4"), _T("bout4"));
	channelMap.insert(_T("bin5"), _T("bout5"));
	channelMap.insert(_T("bin6"), _T("bout6"));
	channelMap.insert(_T("bin7"), _T("bout7"));
	channelMap.insert(_T("bin8"), _T("bout8"));

	CString strDevID,strDevValue,strAppID,strAppValue;
	QString devChID = pGoutCh->m_strDevChID;
	if (channelMap.contains(devChID))
	{
		pGoutCh->m_strAppChID = channelMap.value(devChID);
		QString showString = QString("开出%1").arg(devChID.right(1));
		Show_StaticString(pGoutCh, nRow, 3, showString);
	}
	else
	{
		if (pGoutCh->m_strDataType == _T("BOOLEAN"))	
		{
			pGoutCh->m_strAppChID = _T("v0");
		}
		else if (pGoutCh->m_strDataType == _T("Dbpos"))
		{
			pGoutCh->m_strAppChID = _T("v01");
		}
		Show_StaticString(pGoutCh,nRow,3,_T("--"));
	}
}



