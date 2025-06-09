#include "IecCfgFT3OutGrid.h"
#include "FT3OutSetDialog.h"
#include <QLabel>
#include "../../../XLangResource_Native.h"
#include <QApplication>


bool IsIecCfgFT3OutValNeededID( const CString& strID )
{
	if(strID == _T("zero")||strID == _T("Ia1")||strID == _T("Ib1") || strID == _T("Ic1") ||
		strID == _T("Ia2")||strID == _T("Ib2") || strID == _T("Ic2") ||
		strID == _T("Ia3")||strID == _T("Ib3") || strID == _T("Ic3") ||
		strID == _T("Ia4")||strID == _T("Ib4") || strID == _T("Ic4"))
	{
		return true;
	}
	return false;
}

bool IsIecCfgFT3OutCurrNeededID( const CString& strID )
{
	if(strID == _T("zero")||strID == _T("Ua1")||strID == _T("Ub1") || strID == _T("Uc1") ||
		strID == _T("Ua2")||strID == _T("Ub2") || strID == _T("Uc2") ||
		strID == _T("Ua3")||strID == _T("Ub3") || strID == _T("Uc3") ||
		strID == _T("Ua4")||strID == _T("Ub4") || strID == _T("Uc4"))
	{
		return true;
	}
	return false;
}



QIecCfgFT3OutComBoxDelegBase::QIecCfgFT3OutComBoxDelegBase( QObject *parent/*=NULL*/ )
: QExBaseListComBoxDelegBase(parent)
{

}

QIecCfgFT3OutComBoxDelegBase::~QIecCfgFT3OutComBoxDelegBase()
{

}

void QIecCfgFT3OutComBoxDelegBase::setEditorData( QWidget * editor, const QModelIndex &index ) const
{
	QGV_ITEM* pCurItem = GetCurrItem(index);

	if (pCurItem == NULL || pCurItem->lParam == 0)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
	ASSERT(pVCellData->pExBaseList != NULL);

	CIecCfg6044CommonCh *pCommonData = (CIecCfg6044CommonCh *)pVCellData->pObj;
	CString strChType = pCommonData->m_strChType;

	if(strChType==iecfg_SmvChDataType_Val_CurrMeasure||strChType ==  iecfg_SmvChDataType_Val_Curr)
	{
		CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;

		if (!pDataType)
		{
			return;

		}		
		QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
		pComboBox->clear();
		CDataTypeValue* pDataTypeValue = NULL;
		POS pos = pDataType->GetHeadPosition();
		QString strItem = index.model()->data(index,Qt::EditRole).toString();

		int nCurrIndex = 0;

		while (pos)
		{
			pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);
			if(IsIecCfgFT3OutValNeededID(pDataTypeValue->m_strID))
			{
				pComboBox->addItem(pDataTypeValue->m_strName);
				if (pDataTypeValue->m_strName == strItem)
				{
					pComboBox->setCurrentIndex(nCurrIndex);
				}
				++nCurrIndex;
			}
		}
	}
	else if(strChType==iecfg_SmvChDataType_Val_Vol)
	{
		CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;

		if (!pDataType)
		{
			return;

		}		
		QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
		pComboBox->clear();
		CDataTypeValue* pDataTypeValue = NULL;
		POS pos = pDataType->GetHeadPosition();
		QString strItem = index.model()->data(index,Qt::EditRole).toString();

		int nCurrIndex = 0;

		while (pos)
		{
			pDataTypeValue = (CDataTypeValue*)pDataType->GetNext(pos);
			if(IsIecCfgFT3OutCurrNeededID(pDataTypeValue->m_strID))
			{
				pComboBox->addItem(pDataTypeValue->m_strName);
				if (pDataTypeValue->m_strName == strItem)
				{
					pComboBox->setCurrentIndex(nCurrIndex);
				}
				++nCurrIndex;
			}
		}
	}
	else
	{
		QExBaseListComBoxDelegBase::setEditorData(editor,index);
	}

}

void QIecCfgFT3OutComBoxDelegBase::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
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
	CIecCfg6044CommonCh *pCommonData = (CIecCfg6044CommonCh *)pVCellData->pObj;


	if (pVCellData->pExBaseList != NULL)
	{
		QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
		model->setData(index,comboBox->currentText(),Qt::EditRole);
		CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;
		QString strItem = index.model()->data(index,Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = NULL;
		CString strChType = pCommonData->m_strChType;

		if(strChType==iecfg_SmvChDataType_Val_CurrMeasure||strChType ==  iecfg_SmvChDataType_Val_Curr || strChType==iecfg_SmvChDataType_Val_Vol)
		{
			pDataTypeValue = (CDataTypeValue*)pDataType->FindByID(strItem);
		}
		else
		{
			pDataTypeValue = (CDataTypeValue*)pDataType->GetAtIndex(comboBox->currentIndex());
		}


		if (pDataTypeValue == NULL)
		{
			return;
		}

		ASSERT(pDataTypeValue);

		if (pVCellData->nVt == VCD_STRING)
		{
			*(pVCellData->pString) = pDataTypeValue->m_strID;
		}
		else if (pVCellData->nVt == VCD_LONG)
		{
			*(pVCellData->pnValue) = pDataTypeValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_DOUBLE)
		{
			*(pVCellData->pdValue) = pDataTypeValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_FLOAT)
		{
			*(pVCellData->pfValue) = pDataTypeValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_DWORD)
		{
			*(pVCellData->pdwValue) = pDataTypeValue->GetIndex();
		}

		//		*pVCellData->pString = pDataTypeValue->m_strID;
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

//////////////////////////////////////////////


IecCfgFT3OutGrid::IecCfgFT3OutGrid(QWidget* pParent) : QExBaseListGridBase(pParent)
{
	m_pChType_DelegBase = NULL;
	m_pMap_DelegBase =NULL;
	m_pBitLen_DelegBase = NULL;
	m_pSetting_DelegBase=NULL;
	installEventFilter(this);
}

IecCfgFT3OutGrid::~IecCfgFT3OutGrid()
{

}

void IecCfgFT3OutGrid::InitGrid()
{
	InitGridTitle();
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
	m_pChType_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(1,m_pChType_DelegBase);
	m_pMap_DelegBase = new QIecCfgFT3OutComBoxDelegBase(this);
	setItemDelegateForColumn(2,m_pMap_DelegBase);
	m_pBitLen_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(3,m_pBitLen_DelegBase);
	m_pSetting_DelegBase= new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(5,m_pSetting_DelegBase);

	SetEditable(TRUE);
	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(Slot_Setting_Clicked(int,int)));
}

void IecCfgFT3OutGrid::InitGridTitle()
{
	CString astrGridTitle[FT3CHS_GRID_COLS]={/*_T("描述")*/g_sLangTxt_State_Description,/*_T("通道类型")*/g_sLangTxt_IEC_ChType,/*_T("通道映射")*/g_sLangTxt_IEC_ChMaps,/*_T("字节长度")*/g_sLangTxt_IEC_ChByteLen,/*_T("值")*/g_sLangTxt_Goose_Value,/*_T("设置")*/g_sLangTxt_Gradient_Setting};//lcq
	int iGridWidth[FT3CHS_GRID_COLS]={150,150,150,150,100,200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, FT3CHS_GRID_COLS);
}

void IecCfgFT3OutGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	CIecCfg6044CommonCh *pIecCfg6044CommonCh=(CIecCfg6044CommonCh*)pData;
	Show_String(pData,nRow,0,&pIecCfg6044CommonCh->m_strName);

	if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		QExBaseListGridBase::Show_DataType_Val(pData,nRow,1,iecfg_SmvCommon6044DCChDataType,&pIecCfg6044CommonCh->m_strChType,
			EndEditCell_FT3ChSelChanged);//通道类型 
	}
	else
	{
		QExBaseListGridBase::Show_DataType_Val(pData,nRow,1,iecfg_SmvCommon6044ChDataType,&pIecCfg6044CommonCh->m_strChType,
			EndEditCell_FT3ChSelChanged);//通道类型 
	}
	UpdateData_ByDataType(pIecCfg6044CommonCh,nRow); 
	QExBaseListGridBase::Show_DataType_Val(pData,nRow,3,iecfg_SmvChByteLen,&pIecCfg6044CommonCh->m_nChLenth);//字节长度

	nRow++;
}


void IecCfgFT3OutGrid::UpdateData_ByDataType(CIecCfg6044CommonCh *pCommonCh,int nRow)
{
	if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_DCCur)//柔直电流
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_DCI, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);	

		//Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		Show_StaticString(pCommonCh,nRow,4,_T("--"));//20240224 suyang 只有在状态值 、其他情况下可以进行修改

		Show_StaticString(pCommonCh,nRow,5,_T(""));
	} 
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_DCVol)//柔直电压
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_DCU, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);
		
		//Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		Show_StaticString(pCommonCh,nRow,4,_T("--"));

		Show_StaticString(pCommonCh,nRow,5,_T(""));
	} 
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_NeutralU)
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_NeutralU, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);
		
		//Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		Show_StaticString(pCommonCh,nRow,4,_T("--"));

		Show_StaticString(pCommonCh,nRow,5,_T(""));
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_StateValue, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);
		Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);

		CString str= _T("...");
		Show_StaticString(pCommonCh,nRow,5,&str);
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_Other, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);
		//Show_StaticString(pCommonCh,nRow,4,_T("--"));
		Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		//Show_StaticString(pCommonCh,nRow,5,_T(""));

		if (pCommonCh->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			CString str= _T("...");
			Show_StaticString(pCommonCh,nRow,5,&str);
		}
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_6Vol)
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_6U, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);
		
		//Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		Show_StaticString(pCommonCh,nRow,4,_T("--"));

		Show_StaticString(pCommonCh,nRow,5,_T(""));
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_Vol)
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_U, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);
		
		//Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		Show_StaticString(pCommonCh,nRow,4,_T("--"));

		Show_StaticString(pCommonCh,nRow,5,_T(""));
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_6CurrProt)
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_6I, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);
		
		//Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		Show_StaticString(pCommonCh,nRow,4,_T("--"));

		Show_StaticString(pCommonCh,nRow,5,_T(""));
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_Curr || pCommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)//2024-5-30 wuxinyi 新增交流电流测量
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_I, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);
		
		//Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		Show_StaticString(pCommonCh,nRow,4,_T("--"));

		Show_StaticString(pCommonCh,nRow,5,_T(""));
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
	{
		QExBaseListGridBase::Show_DataType_Val(pCommonCh, nRow, 2,iecfg_SmvAppChDataType_6I, &pCommonCh->m_strAppChID,EndEditCell_FT3ChSelChanged);
		//Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		Show_StaticString(pCommonCh,nRow,4,_T("--"));

		Show_StaticString(pCommonCh,nRow,5,_T(""));
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前FT3通道映射出错(%s).")*/g_sLangTxt_Gradient_FT3CurChanErr.GetString(),pCommonCh->m_strChType.GetString());
	}
}

void IecCfgFT3OutGrid::UpdateData_ByChMap(CIecCfg6044CommonCh *pCommonCh,int nRow)
{

	if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_DCCur)
	{
		Show_StaticString(pCommonCh,nRow,4,_T("--"));//20240224 suyang 只有在状态值 、其他情况下可以进行修改
	} 
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_DCVol)
	{
		Show_StaticString(pCommonCh,nRow,4,_T("--"));
	} 
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_NeutralU)
 	{
 		Show_StaticString(pCommonCh,nRow,4,_T("--"));
 	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		if (pCommonCh->m_strAppChID==g_strAppChID_SmpCnt)
		{
			Show_StaticString(pCommonCh,nRow,4,_T("--"));
		}
		else
		{
			Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
		}
		
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_6Vol)
	{
		Show_StaticString(pCommonCh,nRow,4,_T("--"));
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_Vol)
	{
		Show_StaticString(pCommonCh,nRow,4,_T("--"));
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_6CurrProt)
	{
		Show_StaticString(pCommonCh,nRow,4,_T("--"));
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_Curr || pCommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)
	{
		Show_StaticString(pCommonCh,nRow,4,_T("--"));
	}
	else if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
	{
		Show_StaticString(pCommonCh,nRow,4,_T("--"));
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前FT3通道映射出错(%s).")*/g_sLangTxt_Gradient_FT3CurChanErr.GetString(),pCommonCh->m_strChType.GetString());
	}

// 	if (pCommonCh->m_strAppChID.Find(_T("U")) == 0 || pCommonCh->m_strAppChID.Find(_T("I")) == 0)
//  	{
//  		Show_StaticString(pCommonCh,nRow,4,_T("--"));
//  	}
// 	else
// 	{
// 		Show_Long(pCommonCh,nRow,4,&pCommonCh->m_nValue,TRUE,_T(""),EndEditCell_AppCh_FT3Value);
// 	}

// 	if (pCommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
// 	{
// 		if (pCommonCh->m_strAppChID==g_strAppChID_SmpCnt)
// 		{
// 			Show_StaticString(pCommonCh,nRow,4,_T("--"));
// 		}
// 	}
}


CDataType* IecCfgFT3OutGrid::FindDataType(const CString &strChType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strChType);

	return pDataType;
}

void IecCfgFT3OutGrid::EndEditCell_FT3ChSelChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfg6044CommonCh *pCommonCh = (CIecCfg6044CommonCh*)pVCellData->pObj;
	
	if (nCol=1)
	{
		((IecCfgFT3OutGrid*)pGrid)->UpdateData_ByDataType(pCommonCh,nRow);
		emit ((IecCfgFT3OutGrid*)pGrid)->sig_Ft3Value_Changed();
	}
	if (nCol=2)
	{
		((IecCfgFT3OutGrid*)pGrid)->UpdateData_ByChMap(pCommonCh,nRow);
		emit ((IecCfgFT3OutGrid*)pGrid)->sig_Ft3Value_Changed();
	}
}


void IecCfgFT3OutGrid::EndEditCell_AppCh_FT3Value(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfg6044CommonCh *pCommonCh = (CIecCfg6044CommonCh*)pVellData->pObj;
	ASSERT (pCommonCh != NULL);

	long nValue =  CString_To_long(pCell->text());

	if (nValue != *(pVellData->pnValue))
	{
		*(pVellData->pnValue) = nValue;
 		emit ((IecCfgFT3OutGrid*)pGrid)->sig_Ft3Value_Changed();
		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVellData->pObj);
	}
}

void IecCfgFT3OutGrid::Slot_Setting_Clicked(int nRow,int nCol)
{
	if (nCol !=5)
	{
		return;
	}
	QGV_ITEM *pItem = GetCell(nRow,nCol-1);

	if (pItem == NULL)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pItem->lParam;
	CIecCfg6044CommonCh *pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pVCellData->pObj;

	if (pIecCfg6044CommonCh == NULL)
	{
		return;
	}

	if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		CString str= _T("...");
		Show_StaticString(pIecCfg6044CommonCh,nRow,5,&str);

		QFT3OutSetDialog oFT3OutSetDialog(pIecCfg6044CommonCh->m_nValue,this);

		if (oFT3OutSetDialog.exec() ==  QDialog::Accepted)
		{
			pIecCfg6044CommonCh->m_nValue=oFT3OutSetDialog.m_dwValue;	
			UpdateDatas_Setting();
		    emit sig_Ft3Value_Changed();
		}
	}
	else if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		//两个都是“其它”时,可以独立设置 
		if (pIecCfg6044CommonCh->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			CString str= _T("...");
			Show_StaticString(pIecCfg6044CommonCh,nRow,5,&str);

			QFT3OutSetDialog oFT3OutSetDialog(pIecCfg6044CommonCh->m_nValue,this);

			if (oFT3OutSetDialog.exec() ==  QDialog::Accepted)
			{
				pIecCfg6044CommonCh->m_nValue=oFT3OutSetDialog.m_dwValue;	
				UpdateDatas_Setting();
				emit sig_Ft3Value_Changed();
			}

		} 

	}
}

void IecCfgFT3OutGrid::UpdateDatas_Setting()
{
	if (m_pDatas == NULL)
	{
		return;
	}
	DisConnectAll_SigSlot();
	CIecCfg6044CommonCh *pIecCfg6044CommonCh=NULL;
	POS pos=m_pDatas->GetHeadPosition();
	int nRowIndex = 0;
	long nCalRows = GetDatasCount();

	while (pos != NULL)
	{
		pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)m_pDatas->GetNext(pos);
		UpdateData_ByChMap(pIecCfg6044CommonCh,nRowIndex); 
		nRowIndex++;
	}
	ConnectAll_SigSlot();
}

void IecCfgFT3OutGrid::SetRunState(long nRunState)
{
	if (nRunState == STT_UI_RUN_STATE_Stoped)
	{
		m_pChType_DelegBase->SetEditable(TRUE);
		m_pMap_DelegBase->SetEditable(TRUE);
		m_pBitLen_DelegBase->SetEditable(TRUE);
		m_pSetting_DelegBase->SetEditable(FALSE);
		setEditTriggers(QAbstractItemView::DoubleClicked);
		SetEditable();
	}
	else if (nRunState == STT_UI_RUN_STATE_StateTested_NotEditable)
	{
		m_pChType_DelegBase->SetEditable(FALSE);
		m_pMap_DelegBase->SetEditable(FALSE);
		m_pBitLen_DelegBase->SetEditable(FALSE);
		m_pSetting_DelegBase->SetEditable(FALSE);
		setEditTriggers(QAbstractItemView::NoEditTriggers);
		SetEditable(FALSE);
	}
	else
	{
		m_pChType_DelegBase->SetEditable(FALSE);
		m_pMap_DelegBase->SetEditable(FALSE);
		m_pBitLen_DelegBase->SetEditable(FALSE);
		m_pSetting_DelegBase->SetEditable(FALSE);
		setEditTriggers(QAbstractItemView::DoubleClicked);
		SetEditable(TRUE);
	}
	reset();
}


bool IecCfgFT3OutGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type()==QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent*)event;
		mouseDoubleClickEvent((QMouseEvent*)pMouseEvent);
		return true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);
}

void IecCfgFT3OutGrid::mouseReleaseEvent(QMouseEvent *event)
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

void IecCfgFT3OutGrid::Show_DataType_Val( CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc )
{
// 	QExBaseListGridBase::Show_DataType_Val(pData,nRow,nCol,pDataType,pstrValue,pFunc);
	CIecCfg6044CommonCh *p6044CommonCh = (CIecCfg6044CommonCh *)pData;
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByID( *pstrValue );

		if (pValue == NULL || (((p6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)
			||(p6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Curr)) && !IsIecCfgFT3OutValNeededID(p6044CommonCh->m_strAppChID))||
			((p6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Vol)&&!IsIecCfgFT3OutCurrNeededID(p6044CommonCh->m_strAppChID)))
		{
			pValue = (CDataTypeValue*)pDataType->GetHead();

			if (pValue != NULL)
			{
				*pstrValue = pValue->m_strID;
			}
		}
	}

	QGV_ITEM *pItem = NULL;
	BOOL bHasSetItem = FALSE;

	if (pValue == NULL)
	{
		pItem = AddItem(nRow,nCol,*pstrValue,bHasSetItem);
	}
	else
	{
		pItem = AddItem(nRow,nCol,pValue->m_strName,bHasSetItem);
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrValue, pData, NULL, pFunc);
	pVCellData->pExBaseList = pDataType;
	pVCellData->nVt = VCD_STRING;
	pItem->m_pEditFunc = pFunc;

	pItem->nDataType = QT_GVET_COMBOBOX;
	pItem->lParam = (LPARAM)pVCellData;

	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (!(pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

