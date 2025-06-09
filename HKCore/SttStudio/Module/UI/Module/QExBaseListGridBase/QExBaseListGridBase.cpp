#include "QExBaseListGridBase.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/API/MathApi.h"
#include <QHeaderView>
#include <QLineEdit>

BOOL CExBaseListGridOptrInterface::OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar)	{	return FALSE;	}
void CExBaseListGridOptrInterface::OnDataEditChanged(QTableWidget *pGridCtrl, int nRow, int nCol)				{	}
void CExBaseListGridOptrInterface::OnScrollGridFinished(){}

#ifndef _PSX_QT_LINUX_
QExBaseListGridBase::QExBaseListGridBase(QWidget* pparent):QTableWidget(pparent),m_pDatas(NULL)

#else
QExBaseListGridBase::QExBaseListGridBase(QWidget* pparent):QScrollTableWidget(pparent),m_pDatas(NULL)
#endif
{	
	//this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 50px; }"); //Goose界面滑块设置
	m_pCurrData = NULL;
	m_pDatas = NULL;
	m_bEditable = TRUE;
	m_bModified = FALSE;
	m_pDataViewOptrInterface = NULL;
	m_bHasConnectAll_SigSlot = FALSE;
	m_nAdjustBeginCol = -1;
	installEventFilter(this);
}

QExBaseListGridBase::~QExBaseListGridBase()
{
	FreeListVCellData();
}

void QExBaseListGridBase::SetItemBkColour(int nRow, int nCol, int r, int g, int b)
{
	SetItemBkColour(nRow, nCol, QColor(r, g, b));
}

void QExBaseListGridBase::SetItemFgColour(int nRow, int nCol, int r, int g, int b)
{
	SetItemFgColour(nRow, nCol, QColor(r, g, b));
}

void QExBaseListGridBase::SetItemEnable(int nRow, int nCol,BOOL bEnable)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	if (bEnable)
	{
		if (!(pItem->flags() & Qt::ItemIsEnabled))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEnabled));
		}
	} 
	else 
	{
		if((pItem->flags() & Qt::ItemIsEnabled))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEnabled));
		}
	}

}

void QExBaseListGridBase::SetItemEditable(int nRow, int nCol,BOOL bEditable)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	if (bEditable)
	{
		if (!(pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
		}
	} 
	else 
	{
		if((pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
		}
	}
}

void QExBaseListGridBase::SetDefaultRowHeight(int nRowHeight)
{
//	horizontalHeader()->setMinimumHeight(nRowHeight);
	verticalHeader()->setDefaultSectionSize(nRowHeight);
}

// void QExBaseListGridBase::AutoAdjColWidth()
// {
// 	horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents); 
// }

void QExBaseListGridBase::SetItemBkColour(int nRow, int nCol, QColor cr)
{
	QTableWidgetItem *pItem = item(nRow, nCol);

	if (pItem == NULL)
	{
		return;
	}

	pItem->setBackgroundColor(cr);
}

void QExBaseListGridBase::SetItemFgColour(int nRow, int nCol, QColor cr)
{
	QTableWidgetItem *pItem = item(nRow, nCol);

	if (pItem == NULL)
	{
		return;
	}

	pItem->setTextColor(cr);
}


void QExBaseListGridBase::Show_Index(CExBaseObject *pData, const int& nRow, const int& nCol)
{
	CString strText;
	strText.Format("%d", nRow);
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol, strText,bHasSetItem);
	pItem->nDataType = QT_GVET_NOEDIT;
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (!(pItem->flags()&Qt::ItemIsEnabled))
	{
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, (CString*)NULL, pData,NULL, NULL);
	pItem->lParam = (LPARAM)pVCellData;
	pVCellData->nVt = VCD_STRING;

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QExBaseListGridBase::Show_ItemString(const int& nRow, const int& nCol, CString *pString)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);
	pItem->setText(*pString);
	setItem(nRow,nCol,pItem);
}

void QExBaseListGridBase::Show_ItemString(const int& nRow, const int& nCol, const CString &strText)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);
	pItem->setText(strText);
	setItem(nRow,nCol,pItem);
}

void QExBaseListGridBase::Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString)
{
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,*pString,bHasSetItem);
	pItem->nDataType = QT_GVET_NOEDIT;
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags((Qt::ItemIsEnabled));

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, (CString*)NULL, pData,NULL, NULL);
	pItem->lParam = (LPARAM)pVCellData;
	pVCellData->nVt = VCD_STRING;

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QExBaseListGridBase::Update_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem != NULL)
	{
		pItem->setText(*pString);
		return;
	}

	pItem = new QGV_ITEM(*pString);
	pItem->setTextColor(Qt::black);
	pItem->nDataType = QT_GVET_NOEDIT;
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags((Qt::ItemIsEnabled));

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, (CString*)NULL, pData,NULL, NULL);
	pItem->lParam = (LPARAM)pVCellData;
	pVCellData->nVt = VCD_STRING;

	setItem(nRow,nCol,pItem);
}

void QExBaseListGridBase::Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strString)
{
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,strString,bHasSetItem);
	pItem->nDataType = QT_GVET_NOEDIT;
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
//	pItem->setFlags(Qt::NoItemFlags);
	pItem->setFlags((Qt::ItemIsEnabled));

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, (CString*)NULL, pData,NULL, NULL);
	pVCellData->nVt = VCD_STRING;
	pItem->lParam = (LPARAM)pVCellData;

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

QGV_ITEM* QExBaseListGridBase::AddItem(int nRow, int nCol,const CString &strText,BOOL &bHasSetItem)
{
	bHasSetItem = FALSE;
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		pItem = new QGV_ITEM(strText);
		pItem->setTextColor(Qt::black);//zhouhj 20220323 创建后默认黑色,防止部分通道在不可编辑的情况下,颜色自动变为灰色,当前行选中时,不能显示当前内容
	}
	else
	{
		bHasSetItem = TRUE;
		pItem->setText(strText);
	}

	FreeExBaseCellData(pItem);

	//2022-3-20  lijunqing 后面还要调用，在此不调用，提高效率
	//setItem(nRow,nCol,pItem);
	return pItem;
}

void QExBaseListGridBase::Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
{
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,*pString,bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (!(pItem->flags()&Qt::ItemIsEditable))
	{
		pItem->setFlags((Qt::ItemIsEditable|Qt::ItemIsEnabled));
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pString, pData,NULL, pFunc);
	pVCellData->nVt = VCD_STRING;
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_EDITBOX;

	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		pItem->m_pEditFunc = EndEditCell_String;
		pVCellData->pFunc = EndEditCell_String;
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void  QExBaseListGridBase::Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnCheck, GRID_CELL_EDIT_FUNC pFunc, BOOL bEnable)
{
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,_T(""),bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
//	pItem->setsheet

//	unsigned int nValue1 = 0,nValue2 = (~Qt::ItemIsEditable),nValue3 = pItem->flags();

	if (bEnable)
	{
		if (!(pItem->flags() & Qt::ItemIsEnabled))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEnabled));
		}
	} 
	else 
	{
		if((pItem->flags() & Qt::ItemIsEnabled))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEnabled));
		}
	}

	if ((pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
	}

// 	if (((pItem->flags() & Qt::ItemIsEditable)))
// 	{
// //		nValue1 = (pItem->flags() & ~Qt::ItemIsEditable);
// 		pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
// 	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pnCheck, pData,NULL, NULL);
	pVCellData->nVt = VCD_LONG;
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_CHECKBOX;
	pItem->m_pEditFunc = NULL;

	if (*pnCheck)
	{
		pItem->setCheckState(Qt::Checked);
	} 
	else
	{
		pItem->setCheckState(Qt::Unchecked);
	}

	pItem->m_pEditFunc = pFunc;
	pVCellData->pFunc = pFunc;

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void  QExBaseListGridBase::Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc, BOOL bEnable)
{
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,_T(""),bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (bEnable)
	{
		if (!(pItem->flags() & Qt::ItemIsEnabled))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEnabled));
		}
	} 
	else 
	{
		if((pItem->flags() & Qt::ItemIsEnabled))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEnabled));
		}
	}

	if ((pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrCheck, pData,NULL, NULL);
	pVCellData->nVt = VCD_STRING;
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_CHECKBOX;
	pItem->m_pEditFunc = NULL;
	long nCheck = CString_To_long(*pstrCheck);

	if (nCheck)
	{
		pItem->setCheckState(Qt::Checked);
	} 
	else
	{
		pItem->setCheckState(Qt::Unchecked);
	}

	pItem->m_pEditFunc = pFunc;
	pVCellData->pFunc = pFunc;

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QExBaseListGridBase::Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	CString strFormat;
	strFormat.Format(_T("%%.%df"), nPrecision);
	CString strTmp;
	strTmp.Format(strFormat.GetString(), *pfValue);
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,strTmp,bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (bCanEdit)
	{
		if (!(pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
		}
	} 
	else
	{
		if ((pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
		}
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pfValue, pData,NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_EDITBOX;
	pVCellData->nVt = VCD_FLOAT;
	pItem->dwValue =( nPrecision << 16) + bUnitConversion;

	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		pItem->m_pEditFunc = EndEditCell_Value;
		pVCellData->pFunc = EndEditCell_Value;
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QExBaseListGridBase::Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, double *pfValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	CString strFormat;
	strFormat.Format(_T("%%.%df"), nPrecision);
	CString strTmp;
	strTmp.Format(strFormat.GetString(), *pfValue);
	BOOL bHasSetItem = FALSE;
    QGV_ITEM *pItem = AddItem(nRow,nCol,strTmp,bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (bCanEdit)
	{
		if (!(pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
		}
	} 
	else
	{
		if ((pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
		}
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pfValue, pData,NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_EDITBOX;
	pVCellData->nVt = VCD_DOUBLE;
	pItem->dwValue =( nPrecision << 16) + bUnitConversion;

	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		pItem->m_pEditFunc = EndEditCell_Value;
		pVCellData->pFunc = EndEditCell_Value;
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QExBaseListGridBase::Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	double dValue = CString_To_double(*pstrValue);
	CString strFormat;
	strFormat.Format(_T("%%.%df"), nPrecision);
	CString strTmp;
	strTmp.Format(strFormat.GetString(), dValue);
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,strTmp,bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (bCanEdit)
	{
		if (!(pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
		}
	} 
	else
	{
		if ((pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
		}
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrValue, pData,NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_EDITBOX;
	pVCellData->nVt = VCD_STRING;
	pItem->dwValue =( nPrecision << 16) + bUnitConversion;

	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		pItem->m_pEditFunc = EndEditCell_DoubleString;
		pVCellData->pFunc = EndEditCell_DoubleString;
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QExBaseListGridBase::Show_Long(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
{
	CString strTmp;
	strTmp.Format(_T("%ld"),*pnValue);
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,strTmp,bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
//	pItem->setFlags((Qt::ItemIsEditable|Qt::ItemIsEnabled));
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pnValue, pData,NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType =  bCanEdit ? QT_GVET_EDITBOX : QT_GVET_NOEDIT;
	pVCellData->nVt = VCD_LONG;

	if (bCanEdit)
	{
		if (!(pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
		}
	} 
	else
	{
		if ((pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
		}
	}


	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		pItem->m_pEditFunc = EndEditCell_Value;
		pVCellData->pFunc = EndEditCell_Value;
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QExBaseListGridBase::Show_Int(CExBaseObject *pData, const int& nRow, const int& nCol, int *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
{
	CString strTmp;
	strTmp.Format(_T("%d"),*pnValue);
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,strTmp,bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	//	pItem->setFlags((Qt::ItemIsEditable|Qt::ItemIsEnabled));
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pnValue, pData,NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType =  bCanEdit ? QT_GVET_EDITBOX : QT_GVET_NOEDIT;
	pVCellData->nVt = VCD_INT;

	if (bCanEdit)
	{
		if (!(pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
		}
	} 
	else
	{
		if ((pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
		}
	}


	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		pItem->m_pEditFunc = EndEditCell_Value;
		pVCellData->pFunc = EndEditCell_Value;
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QExBaseListGridBase::Show_Hex(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pdwValue, int iMaxLen,BOOL bCanEdit, BOOL bSetColor, GRID_CELL_EDIT_FUNC pFunc)
{
	CString strFormat,strTextValue;
	strFormat.Format(_T("0X%%0%dX"), iMaxLen*2);
	strTextValue.Format(strFormat.GetString(), (unsigned long)(*pdwValue));
	BOOL bHasSetItem = FALSE;
 	QGV_ITEM *pItem = AddItem(nRow,nCol,strTextValue,bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (bCanEdit)
	{
		if (!(pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
		}
	} 
	else
	{
		if ((pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
		}
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pdwValue, pData,NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_EDITBOX;
	pVCellData->nVt = VCD_DWORD;
	pItem->iMaxLen = iMaxLen;
 
	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		pItem->m_pEditFunc = EndEditCell_Hex;
		pVCellData->pFunc = EndEditCell_Hex;
	}
 
	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QExBaseListGridBase::EndEditCell_Hex (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CString strCurValue = pCell->text();

	DWORD dwCurValue = 0;

	if ((strCurValue.Find("0X")== -1)&&(strCurValue.Find("0x")== -1))
	{
		dwCurValue = strCurValue.toULong(0,10);
	}
	else
	{
		dwCurValue = strCurValue.toULong(0,16);
	}

	if (*pVCellData->pdwValue != dwCurValue)
	{
		*pVCellData->pdwValue = dwCurValue;
//		((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}
}

// void  QExBaseListGridBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strText, PEXBASECELLDATA pVCellData)
// {
// 	QGV_ITEM *pItem = AddItem(nRow,nCol,strText);
// 	FreeExBaseCellData(pItem);
// 	pItem->nDataType = QT_GVET_COMBOBOX;
// 	pItem->lParam = (LPARAM)pVCellData;
// 
// 	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
// 	pItem->setFlags((Qt::ItemIsEditable|Qt::ItemIsEnabled));
// 
// 	if (pVCellData->pFunc == NULL)
// 	{
// 		pVCellData->pFunc = EndEditCell_DataType_Val;
// 		pItem->m_pEditFunc = EndEditCell_DataType_Val;
// 	}
// 	else
// 	{
// 		pItem->m_pEditFunc = pVCellData->pFunc;
// 	}
//
// 	setItem(nRow,nCol,pItem);
// }


void  QExBaseListGridBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByID( *pstrValue );

		if (pValue == NULL)
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

void  QExBaseListGridBase::Show_DataType_Index(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrIndex, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataType *pDataType = FindDataType(strDataType);
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByIndex( *pstrIndex );

		if (pValue == NULL)
		{
			pValue = (CDataTypeValue*)pDataType->GetHead();

			if (pValue != NULL)
			{
				*pstrIndex = pValue->m_strIndex;
			}
		}
	}

	QGV_ITEM *pItem = NULL;
	BOOL bHasSetItem = FALSE;

	if (pValue == NULL)
	{
		CString strText;
		strText.Format(_T("%s"), pstrIndex->GetString());
		pItem = AddItem(nRow,nCol,strText,bHasSetItem);
	}
	else
	{
		pItem = AddItem(nRow,nCol,pValue->m_strName,bHasSetItem);
	}


	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrIndex, pData, NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_COMBOBOX;
	pItem->m_pEditFunc = pFunc;
	pVCellData->pExBaseList = pDataType;
	pVCellData->nVt = VCD_STRING;

	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (!(pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
	}

	if (pVCellData->pFunc == NULL)
	{
		pVCellData->pFunc = EndEditCell_DataType_Val;
		pItem->m_pEditFunc = EndEditCell_DataType_Val;
	}
	else
	{
		pItem->m_pEditFunc = pVCellData->pFunc;
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);//zhouhj20220323 此处缺省一个SetItem
	}
}

void  QExBaseListGridBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByIndex( *pnValue );

		if (pValue == NULL)
		{
			pValue = (CDataTypeValue*)pDataType->GetHead();

			if (pValue != NULL)
			{
				*pnValue = CString_To_long(pValue->m_strIndex);
			}
		}
	}

//	FreeExBaseCellData(nRow, nCol);

	QGV_ITEM *pItem = NULL;
	BOOL bHasSetItem = FALSE;

	if (pValue == NULL)
	{
		CString strText;
		strText.Format(_T("%d"), *pnValue);
		pItem = AddItem(nRow,nCol,strText,bHasSetItem);
	}
	else
	{
		pItem = AddItem(nRow,nCol,pValue->m_strName,bHasSetItem);
	}


	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pnValue, pData, NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_COMBOBOX;
	pItem->m_pEditFunc = pFunc;
	pVCellData->pExBaseList = pDataType;
	pVCellData->nVt = VCD_LONG;

	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (!(pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
	}

	if (pVCellData->pFunc == NULL)
	{
		pVCellData->pFunc = EndEditCell_DataType_Val;
		pItem->m_pEditFunc = EndEditCell_DataType_Val;
	}
	else
	{
		pItem->m_pEditFunc = pVCellData->pFunc;
	}

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);//zhouhj20220323 此处缺省一个SetItem
	}

// 	if (pValue == NULL)
// 	{
// 		CString strText;
// 		strText.Format(_T("%d"), *pnValue);
// 		Show_DataType_Val(pData, nRow, nCol, strText, pVCellData);
// 	}
// 	else
// 	{
// 		Show_DataType_Val(pData, nRow, nCol, pValue->m_strName, pVCellData);
// 	}

}

void  QExBaseListGridBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataType *pDataType = FindDataType(strDataType);
	Show_DataType_Val(pData, nRow, nCol, pDataType, pstrValue, pFunc);
}

void  QExBaseListGridBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataType *pDataType = FindDataType(strDataType);
	Show_DataType_Val(pData, nRow, nCol, pDataType, pnValue, pFunc);
}

void QExBaseListGridBase::EndEditCell_String (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (*pVCellData->pString != pCell->text())
	{
		*pVCellData->pString = pCell->text();
//		((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}
}


// void  QExBaseListGridBase::EndEditCell_Check (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
// {
// 	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
// 	ASSERT (pVCellData != NULL);
// 	ASSERT (pVCellData->pnValue != NULL);
// 	long nCheckValue = (pCell->checkState() != Qt::Unchecked);
// 
// 	if( *(pVCellData->pnValue) != nCheckValue )
// 	{
// 		*(pVCellData->pnValue) = nCheckValue;
// //		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
// 	}
// }

void QExBaseListGridBase::SetTableFont(const QFont &oFont)
{
	horizontalHeader()->setFont(oFont);
	setFont(oFont);
}

void QExBaseListGridBase::SelectRow(CExBaseObject *pCurrSelData)
{
	long nRowCount = rowCount();
	long nCurrSelRow = -1;

	for (int nIndex = 0;nIndex< nRowCount;nIndex++)
	{
		if (GetData(nIndex,0) == pCurrSelData)
		{
			nCurrSelRow = nIndex;
			break;
		}
	}

	SelectRow(nCurrSelRow+1);
}

QGV_ITEM* QExBaseListGridBase::GetCell(int nRow, int nCol) const
{
	if (nRow < 0 || nRow >= rowCount() || nCol < 0 || nCol >= columnCount()) return NULL;

	return (QGV_ITEM*)item(nRow,nCol);
}

void QExBaseListGridBase::FreeExBaseCellData(QGV_ITEM *pItem)
{
	if (pItem == NULL)
	{
		return;
	}

	if (pItem->lParam == 0)
	{
		return;
	}

	m_listVCellData.Delete((PEXBASECELLDATA)pItem->lParam);
	pItem->lParam = 0;
}

void QExBaseListGridBase::FreeExBaseCellData(long nRow, long nCol)
{
	QGV_ITEM *pCell = GetCell(nRow, nCol);

	if (pCell == NULL)
	{
		return;
	}

	if (pCell->lParam == 0)
	{
		return;
	}

	m_listVCellData.Delete((PEXBASECELLDATA)pCell->lParam);
	pCell->lParam = 0;
}

void QExBaseListGridBase::FreeListVCellData()
{	
	m_listVCellData.DeleteAll();	
	int nMaxRow = GetRowCount(), nMaxCol = GetColCount();
	QGV_ITEM *pItem = NULL; 

	for (int nRow = 0;nRow<nMaxRow;nRow++)
	{
		for (int nCol = 0;nCol<nMaxCol;nCol++)
		{
			pItem = GetCell(nRow,nCol);

			if (pItem != NULL)
			{
				pItem->lParam = 0;
			}
		}
	}
}

void QExBaseListGridBase::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
// 	m_idCurrentCell.col = -1;
// 	m_idCurrentCell.row = -1;
 	DisConnectAll_SigSlot();
//	FreeListVCellData();
// 	CTLinkList <_ExBaseCellData> listVCellData;
// 	BackListCellData(listVCellData);
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(0);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

// void QExBaseListGridBase::UpdateDatas()  //zhouhj 2023.12.27 重复定义了删除
// {
// 	if (m_pDatas == NULL)
// 	{
// 		return;
// 	}
// 
// 	DisConnectAll_SigSlot();
// 	CExBaseObject *pObj = NULL;	
// 	POS pos = m_pDatas->GetHeadPosition();
// 	int nRowIndex = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pObj = m_pDatas->GetNext(pos);
// 		ShowData(pObj, nRowIndex, FALSE);
// 	}
// 
// 	ConnectAll_SigSlot();
// }

void QExBaseListGridBase::InsertDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = rowCount();
	long nRows = nRowIndex + pDatas->GetCount();
	SetRowCount(nRows, bResetScrollBars);;

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

long QExBaseListGridBase::GetDatasCount()
{
	ASSERT (m_pDatas != NULL);

	if (m_pDatas == NULL)
	{
		return 0;
	}
	else
	{
		return m_pDatas->GetCount();
	}
}

BOOL QExBaseListGridBase::SetRowCount(int nRows, BOOL bResetScrollBars)
{
	setRowCount(nRows);
	return TRUE;
}

void QExBaseListGridBase::InitGridTitle(const CString *pStrTitles, const int *pnWidth, int nCols)
{
	QHeaderView* pHeadTop =horizontalHeader();
#ifndef _PSX_QT_LINUX_
	pHeadTop->setClickable(false);
	pHeadTop->setMovable(false);
#endif
	QHeaderView* pHeadLeft = verticalHeader();

	horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

// 	QFont font1 = horizontalHeader()->font();
// 	font1.setPointSize(14);
// 	horizontalHeader()->setFont(font1);

	QStringList headers;
	setColumnCount(nCols);

	for (int nIndex = 0;nIndex<nCols;nIndex++)
	{
		headers<<pStrTitles[nIndex];
		setColumnWidth(nIndex,pnWidth[nIndex]);
	}

	setHorizontalHeaderLabels(headers);
}

void QExBaseListGridBase::AfterShowDatas(long nBeginRow, BOOL bResetScrollBars)
{
//	AdjustAllCols();
	ConnectAll_SigSlot();

	if (m_bEditable)
	{
		setEditTriggers(QAbstractItemView::DoubleClicked);
//		connect(this,SIGNAL(cellClicked(int , int )),SLOT(slot_cellClicked(int , int )));
	}
	else
	{
		setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
// 	long nRowIndex = nBeginRow;
// 
// 	for (; nRowIndex<m_nRows; nRowIndex++)
// 	{
// 		SetRowHeight(nRowIndex, m_nRowHeight);
// 	}
// 
// 	AdjustAllCols(bResetScrollBars);
// 
// 	if (bResetScrollBars)
// 	{
// 		ResetScrollBars();
// 	}
// 
// 	Invalidate(FALSE);
}

QGV_ITEM* QExBaseListGridBase::GetCurrSelItem()
{
	QGV_ITEM *pItem = (QGV_ITEM*)this->currentItem();
	return pItem;
}

long QExBaseListGridBase::GetCurrSelDatas(CExBaseList &listDatas, long nStateForCol)
{
	listDatas.RemoveAll();
	QList<QTableWidgetItem*> items = selectedItems();

	for (int i=0; i<items.count(); i++)
	{
		QGV_ITEM *pItem = (QGV_ITEM *)items.at(i);

		if (pItem->isSelected())
		{
			PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pItem->lParam;

			if (pVCellData == NULL)
			{
				continue;
			}

			CExBaseObject *pSelData = pVCellData->pObj;
			listDatas.AddTail(pSelData);
		}
	}

	return listDatas.GetCount();
}

void QExBaseListGridBase::UpdateDatas()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	DisConnectAll_SigSlot();
	BOOL bResetScrollBars=TRUE;
	CExBaseObject *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = m_pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

BOOL QExBaseListGridBase::UpdateData(CExBaseObject *pData)
{
	int nRow = GetDataRow(pData, 1);

	if (nRow < 0)
	{
		return FALSE;
	}

	ShowData(pData, nRow, FALSE);
	return TRUE;
}

void QExBaseListGridBase::InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
//	SetRowCount(m_nRows + 1);
	DisConnectAll_SigSlot();
	int nRow = rowCount();
	insertRow(nRow);
	ShowData(pData, nRow, FALSE);
	ConnectAll_SigSlot();

// 	SetRowHeight(m_nRows-1, EXBASEGRID_ROWHEIGHT);
// 	AdjustAllCols();

// 	if (bInvalidate)
// 	{
// 		Invalidate(FALSE);
// 	}
}

long QExBaseListGridBase::DeleteDataRow(CExBaseObject *pData, BOOL bDeleteData)
{
	long nRow = GetDataRow(pData, 0/*1*/);//zhouhj 2023.12.11 从0开始,原方式如果只有一列数据获取有问题

	if (nRow < 0)
	{
		return -1;
	}

	if (bDeleteData)
	{
		CExBaseList *pParent = (CExBaseList*)pData->GetParent();

		if (pParent != NULL)
		{
			pParent->Delete(pData);
			SetModifiedFlag(pParent, TRUE);
		}
		else
		{
#ifndef NOT_USE_XLANGUAGE
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前表格数据链表无父对象,删除当前行数据失败,存在内存泄漏风险.")*/
				g_sLangTxt_Gradient_NoParObjRisk.GetString()); //lcq
#else
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前表格数据链表无父对象,删除当前行数据失败,存在内存泄漏风险.")); 
#endif
		}
	}

	DeleteRow(nRow);
// 	ResetScrollBars();
// 	Invalidate(FALSE);

	return nRow;
}

// void QExBaseListGridBase::AdjustAllCols(BOOL bResetScrollBars)
// {
// //	resizeRowsToContents();
// 	if (m_nAdjustBeginCol < 0)
// 	{
// 		return;
// 	}
// 
// 	long nCols = GetRowCount();
// 	long nCol = m_nAdjustBeginCol;
// 
// 	for (nCol=m_nAdjustBeginCol+1; nCol<=nCols; nCol++)
// 	{
// 		AutoSizeColumn(nCol, bResetScrollBars);
// 	}
// }

// BOOL QExBaseListGridBase::AutoSizeColumn(int nCol, BOOL bResetScrollBars)
// {
// 	long nCols = GetColCount();
// //	ASSERT(nCol >= 0 && nCol < nCols);
// 	if (nCol <= 0 || nCol > nCols) return FALSE;
// 
// 	int nWidth = 0,nCurrSize = 0;
// 	int nNumRows = GetRowCount();
// 	QFontMetrics fontMetrics = QFontMetrics(font());
// 	QGV_ITEM* pItem = NULL;
// 	QString strText;
// 
// 	for (int nRow = 0; nRow < nNumRows; nRow++)
// 	{
// 		pItem = GetCell(nRow,nCol);
// 		strText = pItem->text();
// 		nCurrSize = fontMetrics.width(strText);
// 
// 		if (nCurrSize > nWidth) 
// 			nWidth = nCurrSize;
// 	}
// 
// 	setColumnWidth(nCol,nWidth+10);
// 
// // 	if (bResetScrollBars)
// // 	{
// // 		ResetScrollBars();
// // 	}
// 
// 	return TRUE;
// }

long QExBaseListGridBase::GetDataRow(CExBaseObject *pData, long nCol)
{
	return GetDataRowEx(pData, 0, nCol);//zhouhj 20220402 row从0开始
}

LPARAM QExBaseListGridBase::GetItemData(int nRow, int nCol) const
{    
	QGV_ITEM* pCell = GetCell(nRow, nCol);
	if (!pCell) return (LPARAM) 0;

	return pCell->lParam;
}

int QExBaseListGridBase::GetRowCount() const
{
	return rowCount();
}

int QExBaseListGridBase::GetColCount() const
{
	return columnCount();
}

long QExBaseListGridBase::GetDataRowEx(CExBaseObject *pData, long nFromRow, long nCol)
{
	if (pData == NULL)
	{
		return -1;
	}

	long nIndex = -1;
 	long nRows = rowCount();
 	long nRow = nFromRow;

	for (; nRow<nRows; nRow++)
	{
		PEXBASECELLDATA pCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol);
		ASSERT (pCellData != NULL);

		if (pCellData != NULL)
		{
			if (pCellData->pObj == pData)
			{
				nIndex = nRow;
				break;
			}
		}
	}

	return nIndex;
}

BOOL QExBaseListGridBase::ChangeRowPosition(int nRow1, int nRow2)
{
	long nRowCount = rowCount();

	if ((nRow1 < 0 || nRow1 >= nRowCount) || (nRow2 < 0 || nRow2 >= nRowCount)) 
	{
		return FALSE;
	}

	DisConnectAll_SigSlot();
	CExBaseObject *p1 = GetData(nRow1,0);
	CExBaseObject *p2 = GetData(nRow2,0);
	ShowData(p1,nRow2,FALSE);
	ShowData(p2,nRow1,FALSE);
	ConnectAll_SigSlot();
	return TRUE;
}

void QExBaseListGridBase::MoveUp()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(1);

	long nRow = GetDataRow(pSel);//m_pDatas->FindIndex(pSel);

	if (nRow < 1)
	{
		return;
	}

	CExBaseObject *p1 = GetData(nRow-1,0);
	CExBaseObject *p2 = GetData(nRow,0);
	DisConnectAll_SigSlot();
	m_pDatas->ChangePosition(p1, p2);
 	ChangeRowPosition(nRow-1, nRow);
// 	UpdateDataIndex();
 	SelectRow(nRow-1);
	ConnectAll_SigSlot();
 	SetModifiedFlag(m_pDatas);
}

void QExBaseListGridBase::MoveDown()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(1);

	long nRow = GetDataRow(pSel);//m_pDatas->FindIndex(pSel);

	if (nRow >= GetRowCount() - 1)
	{
		return;
	}

	CExBaseObject *p1 = GetData(nRow+1,0);
	CExBaseObject *p2 = GetData(nRow,0);
	DisConnectAll_SigSlot();
	m_pDatas->ChangePosition(p1, p2);
 	ChangeRowPosition(nRow, nRow+1);
// 	UpdateDataIndex();
 	SelectRow(nRow+1);
	ConnectAll_SigSlot();
 	SetModifiedFlag(m_pDatas);

}

BOOL QExBaseListGridBase::DeleteRow(int nRow)
{
 	if ( nRow < 0 || nRow >= GetRowCount())
 		return FALSE;

	DisConnectAll_SigSlot();
	removeRow(nRow);
	ConnectAll_SigSlot();
// 
// 	CGridRow* pRow = m_RowData[nRow];
// 	if (!pRow) return FALSE;
// 
// 	ResetSelectedRange();
// 
// 	delete pRow;
// 	m_RowData.RemoveAt(nRow);
// 	UpdateRowsColsIndex();
// 
// 	m_nRows--;
// 	m_oColumns.SetRowCount(m_nRows);
// 	if (nRow < m_nFixedRows) m_nFixedRows--;
// 
// 	if (nRow == m_idCurrentCell.row)
// 		m_idCurrentCell.row = m_idCurrentCell.col = -1;
// 	else if (nRow < m_idCurrentCell.row)
// 		m_idCurrentCell.row--;
// 
// 	ResetScrollBars();

	return TRUE;
}


CExBaseObject* QExBaseListGridBase::GetCurrSelData(long nStateForCol)
{
	QGV_ITEM *pItem = GetCurrSelItem();

	if (pItem == NULL)
	{
		return NULL;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pItem->lParam;

	if (pVCellData == NULL)
	{
		return NULL;
	}

	CExBaseObject *pSelData = pVCellData->pObj;

	return pSelData;
}

CExBaseObject* QExBaseListGridBase::GetData(long nRow, long nCol)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol);

	if (pVCellData == NULL)
	{
		return NULL;
	}

	return pVCellData->pObj;
}

void QExBaseListGridBase::ClearSelect()
{
	m_bHasConnectAll_SigSlot = FALSE;
	disconnect(SIGNAL(cellChanged( int,int)),this,SLOT(slot_CellChanged( int , int )));
	disconnect(SIGNAL(currentCellChanged(int , int , int , int )),this,SLOT(slot_CurrentCellChanged(int , int , int , int )));
	disconnect(SIGNAL(cellDoubleClicked(int , int)), this, SLOT(slot_cellDoubleClicked(int , int)));

//	disconnect(SIGNAL(cellClicked(int , int )),this,SLOT(slot_cellClicked(int , int )));
}

void QExBaseListGridBase::DisConnectAll_SigSlot()
{
	m_bHasConnectAll_SigSlot = FALSE;
	disconnect(SIGNAL(cellChanged( int,int)),this,SLOT(slot_CellChanged( int , int )));
	disconnect(SIGNAL(currentCellChanged(int , int , int , int )),this,SLOT(slot_CurrentCellChanged(int , int , int , int )));
	disconnect(SIGNAL(sig_ScrollFinished()),this,SLOT(slot_ScrollGridFinished()));
	disconnect(SIGNAL(cellDoubleClicked(int , int)), this, SLOT(slot_cellDoubleClicked(int , int)));
}

void QExBaseListGridBase::ConnectAll_SigSlot()
{
	if (m_bHasConnectAll_SigSlot)
	{
		return;
	}

	m_bHasConnectAll_SigSlot = TRUE;
	connect(this,SIGNAL(cellChanged( int,int)),SLOT(slot_CellChanged( int , int )));
	connect(this,SIGNAL(currentCellChanged(int , int , int , int )),SLOT(slot_CurrentCellChanged(int , int , int , int )));
	connect(this,SIGNAL(sig_ScrollFinished()),SLOT(slot_ScrollGridFinished()));
	connect(this,SIGNAL(cellDoubleClicked(int , int)),SLOT(slot_cellDoubleClicked(int , int )));
}

void QExBaseListGridBase::slot_CellChanged(int nrow,int ncol)
{
	QGV_ITEM* pitem = (QGV_ITEM*)item(nrow,ncol);
	long nRows = GetRowCount();

	if(pitem == NULL)
	{
		return;
	}

	if ((pitem->m_pEditFunc != NULL)&&((pitem->nDataType == QT_GVET_EDITBOX)
		||((pitem->nDataType == QT_GVET_CHECKBOX)&&(itemDelegateForColumn(ncol) == NULL))))//zhouhj 20220325 CheckBox在代理中实现调用则不需在此处重新调用回调
	{
		pitem->m_pEditFunc(nrow,ncol,pitem,this);
	}

//	OnChanDataChanged(pitem);
}


// void QExBaseListGridBase::slot_cellClicked(int nrow,int ncol)
// {
// 	QGV_ITEM* pitem = (QGV_ITEM*)item(nrow,ncol);
// 
// 	if(pitem == NULL)
// 	{
// 		return;
// 	}
// 
// 	if ((pitem->m_pEditFunc != NULL)&&((pitem->nDataType == QT_GVET_CHECKBOX)))
// 	{
// 		pitem->m_pEditFunc(nrow,ncol,pitem,this);
// 	}
// 
// //	OnChanDataChanged(pitem);
// }

void QExBaseListGridBase::slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("currentRow=%d;currentColumn=%d;previousRow=%d;previousColumn=%d;"),currentRow,currentColumn,previousRow,previousColumn);

	if ((currentRow >= 0))
	{
		const QColor colorCurr = QColor(204,204,204);
		setRowColor(currentRow,colorCurr);
		OnDataSelChanged(currentRow,currentColumn);
	}

	if (previousRow >= 0)
	{
		const QColor colorOld = QColor(255,255,255);
		setRowColor(previousRow,colorOld);
	}
}

void QExBaseListGridBase::slot_cellDoubleClicked(int row, int column)
{
	if (row == -1 || column == -1)
	{
		return;
	}

	if (m_pDataViewOptrInterface != NULL)
	{
		m_pDataViewOptrInterface->OnEditCellLBDblClk(this, row, column, 0);
	}
}

void QExBaseListGridBase::setRowColor(int nRow, QColor color)
{
	if (nRow == -1)
	{
		return;
	}

	QGV_ITEM* pItemCurr = NULL;

	for (int nCol = 0; nCol<columnCount();nCol++)
	{
		pItemCurr = (QGV_ITEM*)item(nRow,nCol);

		if (pItemCurr != NULL)
		{
			pItemCurr->setBackgroundColor(color);
		}
	}
}

void QExBaseListGridBase::CreateGridMenu()
{
	connect(this, SIGNAL(customContextMenuRequested ( const QPoint & )), this, SLOT(slot_GridShowMenu(QPoint)));
}

void QExBaseListGridBase::focusOutEvent(QFocusEvent *event)
{
	DisableSystemMenu();
}

bool QExBaseListGridBase::eventFilter(QObject *obj, QEvent *event)
{
	DisableSystemMenu(obj, event);
	return QTableWidget::eventFilter(obj,event);
}

void QExBaseListGridBase::DisableSystemMenu()
{
	//禁用弹出edit的右键系统菜单
	installEventFilter(this);

	QList<QLineEdit*> oList = findChildren<QLineEdit*>();
	for (int i = 0; i < oList.size(); i++)
	{
		oList[i]->setContextMenuPolicy(Qt::NoContextMenu);
		oList[i]->installEventFilter(this);
	}
}

void QExBaseListGridBase::DisableSystemMenu(QObject *obj, QEvent *event)
{
	if(obj != this)
	{
		if(event->type() == QEvent::FocusOut)
		{
			this->setFocus();
		}
	}
}

void QExBaseListGridBase::slot_GridShowMenu(QPoint pos)
{
}

void QExBaseListGridBase::OnDataSelChanged(int nRow, int nCol)
{
	if (nRow == -1 || nCol == -1)
	{
		return;
	}

	if (m_pDataViewOptrInterface != NULL)
	{
		m_pDataViewOptrInterface->OnDataSelChanged(this, nRow, nCol);
	}
}

void QExBaseListGridBase::slot_ScrollGridFinished()
{
	if (m_pDataViewOptrInterface != NULL)
	{
		m_pDataViewOptrInterface->OnScrollGridFinished();
	}
}

void QExBaseListGridBase::EndEditCell_Value(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;

	if (pVCellData == NULL)
	{
		return;
	}

	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);
	CString strCurrText;

	if (pVCellData->nVt == VCD_DOUBLE)
	{
		strCurrText = pCell->text();
		double dValue =  math_GetValueFromString(strCurrText);
		CString strTmp;

		if (fabs(dValue-*(pVCellData->pdValue) ) > 0.00001)
		{
			*(pVCellData->pdValue) = dValue;
			long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;

			if (nPrecision > 0 )
			{
				CString strFormat;
				strFormat.Format(_T("%%.%ldlf"), nPrecision);
				strTmp.Format(strFormat.GetString(), *(pVCellData->pdValue));
				pCell->setText(strTmp);
			}
			else
			{
				math_GetStringFromValue(strTmp, *(pVCellData->pdValue), _T(""), pCell->dwValue);
				pCell->setText(strTmp);
			}

			((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		}

// 		double fValue = math_GetValueFromString(pCell->szText);
// 
// 		if (fabs(fValue-*(pVCellData->pfValue) ) > 0.00001)
// 		{
// 			*(pVCellData->pdValue) = math_GetValueFromString(pCell->szText);
// 			math_GetStringFromValue(pCell->szText, *(pVCellData->pdValue), _T(""), pCell->dwValue);
// 			pGrid->RedrawCell(nRow, nCol);
// 			((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
// 			((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
// 		}
	}
	else if (pVCellData->nVt == VCD_FLOAT)
	{
		strCurrText = pCell->text();
		float fValue =  math_GetValueFromString(strCurrText);
		CString strTmp;
//		float fValue = math_GetValueFromString(pCell->szText);

		if (fabs(fValue-*(pVCellData->pfValue) ) > 0.00001)
		{
			*(pVCellData->pfValue) = fValue;
			long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;

			if (nPrecision > 0 )
			{
				CString strFormat;
				strFormat.Format(_T("%%.%df"), nPrecision);
				strTmp.Format(strFormat.GetString(), *(pVCellData->pfValue));
				pCell->setText(strTmp);
			}
			else
			{
				math_GetStringFromValue(strTmp, *(pVCellData->pfValue), _T(""), pCell->dwValue);
				pCell->setText(strTmp);
			}

			((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
//			((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
		}
	}
	else if (pVCellData->nVt == VCD_LONG)
	{
		long nValue =  CString_To_long(pCell->text());

		if (nValue != *(pVCellData->pnValue))
		{
			*(pVCellData->pnValue) = nValue;
			((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
//			((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
		}
	}
	else if (pVCellData->nVt == VCD_INT)
	{
		int nValue =  CString_To_long(pCell->text());

		if (nValue != *(pVCellData->piValue))
		{
			*(pVCellData->piValue) = nValue;
			((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
			//			((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
		}
	}
	else if (pVCellData->nVt == VCD_DWORD)
	{
// 		if (*(pVCellData->pnValue) != pCell->dwValue)
// 		{
// 			*(pVCellData->pnValue) = pCell->dwValue;
// 			((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
// 			((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
// 		}
	}

	((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void QExBaseListGridBase::EndEditCell_DoubleString(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;

	if (pVCellData == NULL)
	{
		return;
	}

	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	CString strCurrText,strTmp;
	bool bOK = false;
	strCurrText = pCell->text();
	double dValue =  strCurrText.toDouble(&bOK);
	double dOldValue = pVCellData->pString->toDouble();

	if (!bOK)//转换失败,说明有非法字符,使用之前的内容
	{
		pCell->setText(*pVCellData->pString);
	}
	else if (fabs(dValue-dOldValue) > 0.00001)
	{
		long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;

		if (nPrecision > 0 )
		{
			CString strFormat;
			strFormat.Format(_T("%%.%ldlf"), nPrecision);
			pVCellData->pString->Format(strFormat.GetString(), dValue);
			pCell->setText(*pVCellData->pString);
		}
		else
		{
			*pVCellData->pString = pCell->text();
		}

		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	}
}

void QExBaseListGridBase::EndEditCell_DataType_Val (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	if (pVCellData->pExBaseList == NULL)
	{
#ifndef NOT_USE_XLANGUAGE
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("Row=%d  Col=%d  数据类型对象不存在")*/
			g_sLangTxt_DataTypeUnExist.GetString(), nRow, nCol);
#else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Row=%d  Col=%d  数据类型对象不存在"), nRow, nCol);
#endif
		return;
	}

	CDataType *pDataType = (CDataType*)pVCellData->pExBaseList;
	ASSERT (pDataType != NULL);
	CString strTmp = pCell->text();

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByName(strTmp);

	if (pValue == NULL)
	{
		//shaolei 2023-11-16 下拉框可编辑下，只处理字符串的部分
		if (pVCellData->nVt == VCD_STRING)
		{
			if (! strTmp.IsEmpty())
			{
				*(pVCellData->pString) = strTmp;
			}
		}
	}
	else
	{
		if (pVCellData->nVt == VCD_STRING)
		{
			*(pVCellData->pString) = pValue->m_strID;
		}
		else if (pVCellData->nVt == VCD_LONG)
		{
			*(pVCellData->pnValue) = pValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_DOUBLE)
		{
			*(pVCellData->pdValue) = pValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_FLOAT)
		{
			*(pVCellData->pfValue) = pValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_DWORD)
		{
			*(pVCellData->pdwValue) = pValue->GetIndex();
		}

		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
//		((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}

// 	if (((CExBaseListGrid*)pGrid)->m_nAdjustBeginCol >= 0)
// 	{
// 		pGrid->AutoSizeColumn(nCol);
// 		pGrid->ResetScrollBars();
// 		pGrid->InvalidateGrid(FALSE);
// 	}
}

//国际版移植
QGV_ITEM * QExBaseListGridBase::NewGVItem(const CString &sText, QColor oTextColor)
{
	QGV_ITEM *pGV_ITEM = new QGV_ITEM(sText);
	pGV_ITEM->setTextColor(oTextColor);
	return pGV_ITEM;
}

void QExBaseListGridBase::SetItemText(QGV_ITEM *pItem, const QString &strText)
{
	if(pItem == NULL)
		return ;

	pItem->setText(strText);
}


void Stt_Global_SettingSelect(QObject *parent, const CString &sFormat, const CString &sName)
{

}
