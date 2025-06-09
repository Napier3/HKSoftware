#include "IecCfgSmvFT3OutChsGrid.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../SoftKeyboard/SoftKeyBoard.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonData.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgSmvRate.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"

#include "../SttIecSMVFT3InitValueSetDialog.h"
#include "../../../SttSystemConfig/SttSystemConfig.h"



bool IsFT3OutValChNeededID( const CString& strID )
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

bool IsFT3OutCurrChNeededID( const CString& strID )
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


QFT3OutChMapComBoxDelegBase::QFT3OutChMapComBoxDelegBase( QObject *parent/*=NULL*/ )
: QIecCfgChsComBoxDelegBase(parent)
{

}

QFT3OutChMapComBoxDelegBase::~QFT3OutChMapComBoxDelegBase()
{

}

void QFT3OutChMapComBoxDelegBase::setEditorData( QWidget * editor, const QModelIndex &index ) const
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
			if(IsFT3OutValChNeededID(pDataTypeValue->m_strID))
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
			if(IsFT3OutCurrChNeededID(pDataTypeValue->m_strID))
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
		QIecCfgChsComBoxDelegBase::setEditorData(editor,index);
	}

}

void QFT3OutChMapComBoxDelegBase::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
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
	CString strChType = pCommonData->m_strChType;


	if (pVCellData->pExBaseList != NULL)
	{
		QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
		model->setData(index,comboBox->currentText(),Qt::EditRole);
		CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;
		QString strItem = index.model()->data(index,Qt::EditRole).toString();
		CDataTypeValue* pDataTypeValue = NULL;
		
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

CString Global_GetCodeValueMapString(CIecCfg6044CommonCh *pIecCfgFT3Ch)
{
	CString strText,strTmp;
	strText = "--";

	if (pIecCfgFT3Ch == NULL)
	{
		return strText;
	}

	if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)||
		(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other))
	{
		return strText;
	}

	if (pIecCfgFT3Ch->m_strAppChID.GetLength()<2)
	{
		return strText;
	}

	CIecCfgSmvRate *pIecCfgSmvRate = iecfg_GetSmvRate(pIecCfgFT3Ch,g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC);

	if (pIecCfgSmvRate == NULL)
	{
		return strText;
	}

	if (pIecCfgFT3Ch->m_strAppChID.Find("U") == 0)
	{
		if (g_oSttSystemConfig.GetFt3PrimCodeValue()) //chenling20240416
		{
			strText.Format("%ld/%.03fV",pIecCfgSmvRate->m_nCodeValue,pIecCfgSmvRate->m_fPrimValue * 1000);
		}
		else
		{
		strText.Format("%ld/%.03fkV",pIecCfgSmvRate->m_nCodeValue,pIecCfgSmvRate->m_fPrimValue);
		}
	} 
	else
	{
		if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)
		{
			strText.Format("%ld/%.03fA",pIecCfgSmvRate->m_nMeasCurrCodeValue,pIecCfgSmvRate->m_fPrimValue);
		} 
		else
		{
			strText.Format("%ld/%.03fA",pIecCfgSmvRate->m_nCodeValue,pIecCfgSmvRate->m_fPrimValue);
		}
	}

	return strText;
}

CIecCfgSmvFT3OutChsGrid::CIecCfgSmvFT3OutChsGrid(QWidget* pparent):CIecCfgChsGridBase(pparent)
{
}

CIecCfgSmvFT3OutChsGrid::~CIecCfgSmvFT3OutChsGrid()
{

}

void CIecCfgSmvFT3OutChsGrid::InitGrid()
{
	InitGridTitle();
	m_pChType_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(1,m_pChType_DelegBase);
	m_pBitLen_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(2,m_pBitLen_DelegBase);
	m_pChMap_DelegBase = new QFT3OutChMapComBoxDelegBase(this);
	setItemDelegateForColumn(3,m_pChMap_DelegBase);
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
	//	AutoAdjColWidth();
	SetEditable(TRUE);
	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgSmvFT3OutChsGrid::InitGridTitle()
{
	//_T("通道描述"),_T("通道类型"),_T("字节长度"),_T("通道映射"),_T("码值对应关系"),_T("初始值")

	CString astrGridTitle[IECCFGSMVFT3OutCHS_GRID_COLS] = {g_sLangTxt_IEC_ChDescription,
		g_sLangTxt_IEC_ChType, g_sLangTxt_IEC_ChByteLen, g_sLangTxt_IEC_ChMaps,/*_T("码值对应关系")*/g_sLangTxt_Native_CodeValue_Corrspondence, g_sLangTxt_IEC_InitValue };
	int iGridWidth[IECCFGSMVFT3OutCHS_GRID_COLS]={250,150,150,150,200,150};
	
	//20230725 suyang 适配分辨率 1024X768
#ifdef _PSX_QT_WINDOWS_

		iGridWidth[0] = 150;
		iGridWidth[1] = 150;
		iGridWidth[2] = 150;

#endif

	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMVFT3OutCHS_GRID_COLS);
}

void CIecCfgSmvFT3OutChsGrid::UpdateChLength(CExBaseObject *pData, int& nRow, long nChLength, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFG6044COMMONCH)
	{
		return;
	}

	CIecCfg6044CommonCh *pIecCfgFT3Ch= (CIecCfg6044CommonCh*)pData;
	if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch,nRow,2,iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch,nRow,2,iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);
	}
	else
	{
		pIecCfgFT3Ch->m_nChLenth = nChLength;
		Show_Long(pIecCfgFT3Ch,nRow,2,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	}
	nRow ++;
}

void CIecCfgSmvFT3OutChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFG6044COMMONCH)
	{
		return;
	}

	CIecCfg6044CommonCh *pIecCfgFT3Ch= (CIecCfg6044CommonCh*)pData;

	CIecCfg6044CommonData *pIecCfg6044CommonData = (CIecCfg6044CommonData*)pIecCfgFT3Ch->GetAncestor(CFGCLASSID_CIECCFG6044COMMONDATA);
	BOOL bEnableAll = TRUE;

	if (pIecCfg6044CommonData != NULL)
	{
		if (!pIecCfg6044CommonData->m_strProtocolID.IsEmpty())
		{
			bEnableAll = FALSE;
		}
	}

	long nCurrChIndex = pIecCfgFT3Ch->m_nIndex ;

    if (pIecCfgFT3Ch->m_strName.IsEmpty() || pIecCfgFT3Ch->m_strName.Find(_T("Ch")) >= 0)//cl20231027设置通道缺省项
	{
		pIecCfgFT3Ch->m_strName.Format(/*_T("通道%d")*/g_sLangTxt_Native_ChnN.GetString(),nCurrChIndex+1);
	}

	Show_String(pData,nRow,0,&pIecCfgFT3Ch->m_strName);

	if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pData,nRow,1,iecfg_SmvCommon6044DCChDataType,&pIecCfgFT3Ch->m_strChType,EndEditCell_SmvFT3ChSelChangged);
	} 
	else
	{
		CIecCfgChsGridBase::Show_DataType_Val(pData,nRow,1,iecfg_SmvCommon6044ChDataType,&pIecCfgFT3Ch->m_strChType,EndEditCell_SmvFT3ChSelChangged);
	}

	UpdateData_ByDataType(pIecCfgFT3Ch,nRow);
//	Show_DataType_Val(pData,nRow,3,iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);

	SetItemEnable(nRow,0,bEnableAll);
	SetItemEnable(nRow,1,bEnableAll);
	SetItemEnable(nRow,2,bEnableAll);
	
	nRow++;
}

void CIecCfgSmvFT3OutChsGrid::EndEditCell_SmvFT3ChSelChangged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfg6044CommonCh *pIecCfgSmvFT3Ch = (CIecCfg6044CommonCh*)pVCellData->pObj;
	((CIecCfgSmvFT3OutChsGrid*)pGrid)->UpdateData_ByDataType(pIecCfgSmvFT3Ch,nRow);

	((CIecCfgSmvFT3OutChsGrid*)pGrid)->slot_SetInitValueBtn_Clicked(nRow,nCol);//20240122 suyang 更新下拉选项后更新初值设置按钮状态
}

void CIecCfgSmvFT3OutChsGrid::EndEditCell_SmvFT3ChMapSelChangged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfg6044CommonCh *pIecCfgFT3Ch = (CIecCfg6044CommonCh*)pVCellData->pObj;

	CString strText;
	strText = Global_GetCodeValueMapString(pIecCfgFT3Ch);
	((CIecCfgSmvFT3OutChsGrid*)pGrid)->Show_StaticString(pIecCfgFT3Ch,nRow,4,strText);

	((CIecCfgSmvFT3OutChsGrid*)pGrid)->UpdateChInitValue(pIecCfgFT3Ch,nRow);

	((CIecCfgSmvFT3OutChsGrid*)pGrid)->slot_SetInitValueBtn_Clicked(nRow,nCol);//20240122 suyang 更新下拉选项后更新初值设置按钮状态
}

void CIecCfgSmvFT3OutChsGrid::UpdateChInitValue(CIecCfg6044CommonCh *pIecCfgFT3Ch,int nRow)
{
	if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCCur)
	{
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCVol)
	{
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_NeutralU)
	{
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		//两个都是“其它”时,可以独立设置  zhouhj 2023.9.13
		if (pIecCfgFT3Ch->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		} 
		else
		{
			Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));
		}
	}
	else if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6Vol)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Vol))
	{
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));
	}
	else if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrProt)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure))
	{
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
	{
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前SMVFT3通道映射出错(%s)."),pIecCfgFT3Ch->m_strChType.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurSmvErr.GetString(),pIecCfgFT3Ch->m_strChType.GetString());
	}
	SetItemEditable(nRow,5,FALSE);

	
}

void CIecCfgSmvFT3OutChsGrid::UpdateData_ByDataType(CIecCfg6044CommonCh *pIecCfgFT3Ch,int nRow)
{
	CIecCfg6044CommonData *pIecCfg6044CommonData = (CIecCfg6044CommonData*)pIecCfgFT3Ch->GetAncestor(CFGCLASSID_CIECCFG6044COMMONDATA);

	if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCCur)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_DCI, &pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));

		if (pIecCfg6044CommonData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonData->m_nSmpDataLen;
		}		
		
		Show_Long(pIecCfgFT3Ch,nRow,2,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCVol)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_DCU, &pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));

		if (pIecCfg6044CommonData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonData->m_nSmpDataLen;
		}		
		
		Show_Long(pIecCfgFT3Ch,nRow,2,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_NeutralU)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_NeutralU, &pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));

		if (pIecCfg6044CommonData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonData->m_nSmpDataLen;
		}		
		
		Show_Long(pIecCfgFT3Ch,nRow,2,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_StateValue, &pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);
		Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch,nRow,2,iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_Other, &pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);

		//两个都是“其它”时,可以独立设置  zhouhj 2023.9.13
		if (pIecCfgFT3Ch->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		} 
		else
		{
			Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));
		}

		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch,nRow,2,iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6Vol)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_6U, &pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));

		if (pIecCfg6044CommonData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonData->m_nSmpDataLen;
		}		
		
		Show_Long(pIecCfgFT3Ch,nRow,2,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Vol)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_U, &pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);

		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));

		if (pIecCfg6044CommonData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonData->m_nSmpDataLen;
		}		
		
		Show_Long(pIecCfgFT3Ch,nRow,2,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrProt)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_6I, &pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));

		if (pIecCfg6044CommonData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonData->m_nSmpDataLen;
		}		
		
		Show_Long(pIecCfgFT3Ch,nRow,2,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	}
	else if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure))
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_I, &pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));
		if (pIecCfg6044CommonData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonData->m_nSmpDataLen;
		}		
		
		Show_Long(pIecCfgFT3Ch,nRow,2,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
	{
		CIecCfgChsGridBase::Show_DataType_Val(pIecCfgFT3Ch, nRow, 3,iecfg_SmvAppChDataType_6I,&pIecCfgFT3Ch->m_strAppChID,
			EndEditCell_SmvFT3ChMapSelChangged);
		//Show_Long(pIecCfgFT3Ch,nRow,5,&pIecCfgFT3Ch->m_nValue);
		Show_StaticString(pIecCfgFT3Ch,nRow,5,_T("--"));

		if (pIecCfg6044CommonData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonData->m_nSmpDataLen;
		}		
		
		Show_Long(pIecCfgFT3Ch,nRow,2,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前SMVFT3通道映射出错(%s)."),pIecCfgFT3Ch->m_strChType.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurSmvErr.GetString(),pIecCfgFT3Ch->m_strChType.GetString());
	}

	CString strText;
	strText = Global_GetCodeValueMapString(pIecCfgFT3Ch);
	Show_StaticString(pIecCfgFT3Ch,nRow,4,strText);
}

void CIecCfgSmvFT3OutChsGrid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
{
	slot_SetInitValueBtn_Clicked(nRow,nCol);

	if (nCol == 5)
	{
		SetInitValue(nRow,nCol);
		return;
	}

	if (nCol != 0)
	{
		return;
	}
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	QString strValue = pItem->text();
	GetEngWidgetBoard_DigitData(strValue, parentWidget()->parentWidget());
	pItem->setText(strValue);

	// 	WidgetKeyboard dlg(this);
	// 	dlg.m_InputString = pItem->text();
	// 	dlg.showToEdit();
	// 	if (dlg.exec() == QDialog::Accepted)
	// 	{
	// 		pItem->setText(dlg.m_InputString);
	// 	}
}

// void CIecCfgSmvFT3OutChsGrid::OnDataSelChanged(int nRow, int nCol)
// {
// 	CIecCfgDataGridBase::OnDataSelChanged(nRow,nCol);
// 
// 	CIecCfg6044CommonInData *pIecCfgFT3Data = (CIecCfg6044CommonInData*)GetData(nRow,nCol);
// 
// 	if (pIecCfgFT3Data == NULL)
// 	{
// 		return;
// 	}
// 
// 	BOOL bEnable = TRUE;
// 
// 	if (!pIecCfgFT3Data->m_strProtocolID.IsEmpty())
// 	{
// 		bEnable = FALSE;
// 	} 
// 
// 	SetItemEnable(nRow,2,bEnable);
// 	SetItemEnable(nRow,3,bEnable);
// 	SetItemEnable(nRow,4,bEnable);
// 	SetItemEnable(nRow,5,bEnable);
// }


void CIecCfgSmvFT3OutChsGrid::SetInitValue(int nRow,int nCol)
{
	if (nCol != 5)
	{
		return;
	}
	QGV_ITEM *pItem = GetCell(nRow,nCol);

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
	QSttIecSMVFT3InitValueSetDialog oValueSetDlg(pIecCfg6044CommonCh->m_nValue,this);
	oValueSetDlg.exec();
	pIecCfg6044CommonCh->m_nValue = oValueSetDlg.m_dwValue;

		UpdateChInitValue(pIecCfg6044CommonCh,nRow);
		
	}
	else if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
	{

		//两个都是“其它”时,可以弹出  suyang 2024.01.20
		if (pIecCfg6044CommonCh->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			QSttIecSMVFT3InitValueSetDialog oValueSetDlg(pIecCfg6044CommonCh->m_nValue,this);
			oValueSetDlg.exec();
			pIecCfg6044CommonCh->m_nValue = oValueSetDlg.m_dwValue;

	UpdateChInitValue(pIecCfg6044CommonCh,nRow);
			
		} 

	}


}

void CIecCfgSmvFT3OutChsGrid::slot_SetInitValueBtn_Clicked( int nRow,int nCol )
{
	bool bSetInitValue = FALSE;

	QGV_ITEM *pItem = GetCell(nRow,nCol);

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
		bSetInitValue = TRUE;

	}
	else if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
	{

		//两个都是“其它”时,可以弹出  suyang 2024.01.20
		if (pIecCfg6044CommonCh->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			bSetInitValue = TRUE;

		} 

	}


	emit sig_UpdateInitValueBtnEnabled(bSetInitValue);
}

void CIecCfgSmvFT3OutChsGrid::Show_DataType_Val( CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc )
{
	CIecCfg6044CommonCh *p6044CommonCh = (CIecCfg6044CommonCh *)pData;
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByID( *pstrValue );

		if (pValue == NULL || (((p6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)
			||(p6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Curr)) && !IsFT3OutValChNeededID(p6044CommonCh->m_strAppChID))||
			((p6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Vol)&&!IsFT3OutCurrChNeededID(p6044CommonCh->m_strAppChID)))
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



