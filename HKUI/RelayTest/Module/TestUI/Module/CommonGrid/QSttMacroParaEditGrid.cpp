#include "QSttMacroParaEditGrid.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include <QLabel>
#include <math.h>
//#include "../../../SttCmd/GuideBook/SttMacroTest.h"
#include "../../SttMultiMacroParasDefine.h"
#include "../../../UI/SttTestCntrFrameBase.h"

CSttMacroTestParaData *Global_FindAddMacroTestParaData(CSttMacroTest* pSttMacroTest,CTestMacro *pSingleMacro, const CString &strParaID)
{
	CSttMacroTestPara* pMacroPara = pSttMacroTest->GetSttMacroTestPara();

	if (pMacroPara == NULL)
	{
		if (pSingleMacro == NULL)
		{
			return NULL;
		}

		pMacroPara = pSttMacroTest->GetAddMacroTestPara(pSingleMacro->m_strID);
	}

	return Global_FindAddMacroTestParaData(pMacroPara,pSingleMacro,strParaID);
}

CSttMacroTestParaData *Global_FindAddMacroTestParaData(CSttMacroTestPara* pMacroPara,CTestMacro *pSingleMacro, const CString &strParaID)
{
	if (pMacroPara == NULL)
	{
		return NULL;
	}

	CSttMacroTestParaData *pSttMacroTestParaData = pMacroPara->FindMacroTestParaDataByID(strParaID);

	if (pSttMacroTestParaData != NULL)
	{
		return pSttMacroTestParaData;
	}

	if (pSingleMacro == NULL)
	{
		return NULL;
	}

	CShortData* pShortData = pSingleMacro->FindDataByID(strParaID);

	if (pShortData == NULL)
	{
		return NULL;
	}

	pSttMacroTestParaData = new CSttMacroTestParaData;
	CSttMacroTestParaDatas *pCSttMacroTestParaDatas = pMacroPara->GetSttMacroTestParaDatas(TRUE);
	pCSttMacroTestParaDatas->AddNewChild(pSttMacroTestParaData);
	pSttMacroTestParaData->m_strName = pShortData->m_strName;
	pSttMacroTestParaData->m_strID = pShortData->m_strID;
	pSttMacroTestParaData->m_strValue = pShortData->m_strValue;
	return pSttMacroTestParaData;
}

void Global_CreateAllParaDatas(CSttMacroTestParaDatas* pSttTestParaDatas, CTestMacro *pSingleMacro)
{
	if (pSingleMacro == NULL)
	{
		return;
	}

	CShortData *pShortData = NULL;
	CSttMacroTestParaData *pSttMacroTestParaData = NULL;
	CShortDatas *pShortDatas = pSingleMacro->GetSysParas();
	POS pos = pShortDatas->GetHeadPosition();

	while(pos)
	{
		pShortData = (CShortData *)pShortDatas->GetNext(pos);
		pSttMacroTestParaData = (CSttMacroTestParaData*)pSttTestParaDatas->FindByID(pShortData->m_strID);

		if (pSttMacroTestParaData == NULL)
		{
			pSttMacroTestParaData = new CSttMacroTestParaData;
			pSttMacroTestParaData->m_strID = pShortData->m_strID;
			pSttMacroTestParaData->m_strName = pShortData->m_strName;
			pSttMacroTestParaData->m_strValue = pShortData->m_strValue;
			pSttTestParaDatas->AddNewChild(pSttMacroTestParaData);
		}
	}

	pShortDatas = pSingleMacro->GetFaultParas();
	pos = pShortDatas->GetHeadPosition();

	while(pos)
	{
		pShortData = (CShortData *)pShortDatas->GetNext(pos);
		pSttMacroTestParaData = (CSttMacroTestParaData*)pSttTestParaDatas->FindByID(pShortData->m_strID);

		if (pSttMacroTestParaData == NULL)
		{
			pSttMacroTestParaData = new CSttMacroTestParaData;
			pSttMacroTestParaData->m_strID = pShortData->m_strID;
			pSttMacroTestParaData->m_strName = pShortData->m_strName;
			pSttMacroTestParaData->m_strValue = pShortData->m_strValue;
			pSttTestParaDatas->AddNewChild(pSttMacroTestParaData);
		}
	}
}

QSttMacroParaEditGrid::QSttMacroParaEditGrid(QWidget *parent)
	: QExBaseListGridBase(parent)
{
	m_pCurrGridInst = NULL;
	m_pParentWidget = parent;
	m_pMacroDataTypes = NULL;
	m_pSingleMacroRef = NULL;
	m_pCharacteristics_Items = NULL;
	m_nAdjustBeginCol = 0;
}

QSttMacroParaEditGrid::~QSttMacroParaEditGrid()
{

}

void QSttMacroParaEditGrid::InitColDef(CSttGdGridInst *pCurrGridInst,CTestMacro *pSingleMacroRef,CDataTypes *pMacroDataTypes)
{
	m_pCurrGridInst = pCurrGridInst;
	m_pSingleMacroRef = pSingleMacroRef;
	m_pMacroDataTypes = pMacroDataTypes;
	InitGrid();

	if (m_pCurrGridInst == NULL)
	{
		return;
	}

	CSttGdInst_Cols* pSttGdInst_Cols = m_pCurrGridInst->GetInst_Cols();

	if (pSttGdInst_Cols == NULL)
	{
		return;
	}

	long nCol = 0;
	CSttGdInst_Col *pSttGdInst_Col = NULL;
	QItemDelegate *pQItemDelegate = NULL;
	POS pos = pSttGdInst_Cols->GetHeadPosition();

	while(pos)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos);
		setItemDelegateForColumn(nCol,NULL);
//		pQItemDelegate = (QItemDelegate*)itemDelegateForColumn(nCol);

		if (pSttGdInst_Col->m_strID == STT_MACRO_PARA_EDIT_GRID_ID_Select)
		{
			pQItemDelegate = new QExBaseListCheckBoxDelegate(this);
			setItemDelegateForColumn(nCol,pQItemDelegate);
		}
		else if ((pSttGdInst_Col->m_pSttGdColDef_Ref != NULL)&&(m_pMacroDataTypes != NULL))
		{
			if ((pSttGdInst_Col->m_pSttGdColDef_Ref->m_strDataType != "double")&&(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strDataType != "long"))
			{
				if (m_pMacroDataTypes->FindByID(pSttGdInst_Col->m_pSttGdColDef_Ref->m_strDataType) != NULL)
				{
					pQItemDelegate = new QExBaseListComBoxDelegBase(this);
					setItemDelegateForColumn(nCol,pQItemDelegate);
				}
			} 
			else
			{
			}
		}
		else
		{
		}

		nCol++;
	}
}

void QSttMacroParaEditGrid::InitGrid()
{
	InitGridTitle();
}

void QSttMacroParaEditGrid::InitGridTitle()
{
	if (m_pCurrGridInst == NULL)
	{
		return;
	}

	long nCount = m_pCurrGridInst->GetColCount();

	if (nCount<=0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前表格列数量(%ld)异常."),nCount);
		return;
	}

	CString *pastrColName = new CString[nCount];
	int *pnColWidth = new int[nCount];
	m_pCurrGridInst->GetGridColsTitleWidth(pastrColName,pnColWidth,nCount);
	QExBaseListGridBase::InitGridTitle(pastrColName, pnColWidth, nCount);
	delete[] pastrColName;
	delete[] pnColWidth;
}

void QSttMacroParaEditGrid::DisConnectAll_SigSlot()
{
	QExBaseListGridBase::DisConnectAll_SigSlot();

	if (m_pParentWidget != NULL)
	{
		disconnect(this,SIGNAL(sig_UpdateParaEditWidget(CSttMacroTest*)),m_pParentWidget,SLOT(slot_Grid_To_ParaEditWidget(CSttMacroTest*)));
	}
}

void QSttMacroParaEditGrid::ConnectAll_SigSlot()
{
	QExBaseListGridBase::ConnectAll_SigSlot();

	if (m_pParentWidget)
	{
		connect(this,SIGNAL(sig_UpdateParaEditWidget(CSttMacroTest*)),m_pParentWidget,SLOT(slot_Grid_To_ParaEditWidget(CSttMacroTest*)));
	}
}

void QSttMacroParaEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (m_pCurrGridInst == NULL)
	{
		return;
	}

	CSttGdInst_Cols *pSttGdInst_Cols = m_pCurrGridInst->GetInst_Cols();

	if (pSttGdInst_Cols == NULL)
	{
		return;
	}

	if (pData->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
	{
		return;
	}

	CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pData;
	CSttMacroTestPara* pMacroPara = pSttMacroTest->GetSttMacroTestPara();

	if (pMacroPara == NULL)
	{
		return;
	}

	CString strCtrlType;

	long nCol = 0;
	CSttGdInst_Col *pSttGdInst_Col = NULL;
	POS pos = pSttGdInst_Cols->GetHeadPosition();

	while(pos)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos);
		strCtrlType = "";

		if (pSttGdInst_Col->m_pSttGdColDef_Ref != NULL)
		{
			strCtrlType = pSttGdInst_Col->m_pSttGdColDef_Ref->m_strCtrlType;
		}

		if (pSttGdInst_Col->m_strID == STT_MACRO_PARA_EDIT_GRID_ID_Select)
		{
			Show_Check(pMacroPara, nRow, nCol, &pSttMacroTest->m_nSelect, EndEditCell_SelectStateCheck);
		}
		else if (pSttGdInst_Col->m_strID == STT_MACRO_PARA_EDIT_GRID_ID_State)
		{
			Show_StatePic(pMacroPara,nRow,nCol,&pSttMacroTest->m_nState);
		}
		else if ((pSttGdInst_Col->m_strID == STT_MACRO_PARA_EDIT_GRID_ID_TestRslt)||
			(strCtrlType == STT_TESTGRID_COL_CTRL_TYPE_ResultItem))
		{
			Show_TestResult(pSttMacroTest,nRow,nCol,pSttMacroTest->m_nState,pSttGdInst_Col);
		}		
		else
		{
			ShowDataGdUI(pMacroPara,pSttGdInst_Col->m_pSttGdColDef_Ref,nRow,nCol);
		}
		nCol++;
	}

	nRow++;
}

void  QSttMacroParaEditGrid::Show_StatePic(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnState, GRID_CELL_EDIT_FUNC pFunc)
{
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,_T(""),bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

// 	if((pItem->flags() & Qt::ItemIsEnabled))
// 	{
// 		pItem->setFlags((pItem->flags() & ~Qt::ItemIsEnabled));
// 	}

	if ((pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pnState, pData,NULL, NULL);
	pVCellData->nVt = VCD_LONG;
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_NOEDIT;

	pItem->m_pEditFunc = pFunc;
	pVCellData->pFunc = pFunc;

	QLabel *pCurrLabel = (QLabel*)cellWidget(nRow,nCol);

	if (pCurrLabel == NULL)
	{
		pCurrLabel = new QLabel;
		pCurrLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		setCellWidget(nRow,nCol,pCurrLabel);
	}

#ifdef _PSX_QT_WINDOWS_
	CString strPicPath = _P_GetResourcePath();

	if (*pnState == TEST_STATE_ELIGIBLE)
	{
		strPicPath += "correct.png";
		pCurrLabel->setPixmap(QPixmap(strPicPath));
	} 
	else if (*pnState == TEST_STATE_INLEGIBLE)
	{
		strPicPath += "error.png";
		pCurrLabel->setPixmap(QPixmap(strPicPath));
	}
	else
	{
		strPicPath += "circle_green.png";
		pCurrLabel->setPixmap(QPixmap(strPicPath));
	}

#else
	if (*pnState == TEST_STATE_ELIGIBLE)
	{
		pCurrLabel->setPixmap(QPixmap(":/ctrls/images/correct.png"));
	} 
	else if (*pnState == TEST_STATE_INLEGIBLE)
	{
		pCurrLabel->setPixmap(QPixmap(":/ctrls/images/correct.png"));
	}
// 	else if (*pnState == TEST_STATE_INLEGIBLE)
// 	{
// 		pCurrLabel->setPixmap(QPixmap(":/ctrls/images/correct.png"));
// 	}
// 	else
	{
		pCurrLabel->setPixmap(QPixmap(":/ctrls/images/circle_green.png"));
	}
#endif

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QSttMacroParaEditGrid::Show_TestResult(CSttMacroTest *pSttMacroTest, const int& nRow, const int& nCol, long nState, CSttGdInst_Col *pSttGdInst_Col)
{
	CString strText;

	if ((nState != TEST_STATE_ELIGIBLE)&&(nState != TEST_STATE_INLEGIBLE))
	{
		strText = "---";
	} 
	else
	{
        pSttGdInst_Col->m_pSttGdColDef_Ref->GetTestRsltString(pSttMacroTest->GetLastRptDvmValues(),m_pSingleMacroRef->GetResults(), strText);
	}

	CSttMacroTestPara* pMacroPara = pSttMacroTest->GetSttMacroTestPara();
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,strText,bHasSetItem);
	pItem->nDataType = QT_GVET_NOEDIT;
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags((Qt::ItemIsEnabled));
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, (CString*)NULL, pMacroPara,NULL, NULL);
	pItem->lParam = (LPARAM)pVCellData;
	pVCellData->nVt = VCD_STRING;

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void QSttMacroParaEditGrid::SetModifiedFlag(CExBaseObject *pData, BOOL bModified)	
{
	if (pData != NULL)
	{
		CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pData->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);

		if (pSttMacroTest != NULL)
		{
			pSttMacroTest->m_nModified = 1;//zhouhj 2024.9.2
			emit sig_UpdateParaEditWidget(pSttMacroTest);
		}
	}
	
	QExBaseListGridBase::SetModifiedFlag(pData,bModified);	
}

CDataType* QSttMacroParaEditGrid::FindDataType(const CString &strDataType)
{
	if (m_pMacroDataTypes == NULL)
	{
		return NULL;
	}

	return (CDataType*)m_pMacroDataTypes->FindByID(strDataType);
}

CSttMacroTest* QSttMacroParaEditGrid::GetCurrSelSttMacroTest()
{
	CExBaseObject *pSelData = GetCurrSelData();

	if (pSelData == NULL)
	{
		int nRow = GetRowIndex((QGV_ITEM*)this->currentItem());

		if (nRow < 0)
		{
			return NULL;
		}

		pSelData = (CExBaseObject*)GetItemData(nRow,0);

		if (pSelData == NULL)
		{
			return NULL;
		}
	}

	if (pSelData->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		return (CSttMacroTest*)pSelData;
	}

	return (CSttMacroTest*)pSelData->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);
}

CExBaseObject* QSttMacroParaEditGrid::GetCurrSelData(long nStateForCol)
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

	if (pSelData == NULL)
	{
		return NULL;
	}

	return pSelData;
}

//void QSttMacroParaEditGrid::EndEditCell_DoubleString_ParaEdit(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
//{
//	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
//
//	if (pVCellData == NULL)
//	{
//		return;
//	}
//
//	ASSERT (pVCellData != NULL);
//	ASSERT (pVCellData->pString != NULL);
//
//	CString strCurrText,strTmp;
//	bool bOK = false;
//	strCurrText = pCell->text();
//	double dValue =  strCurrText.toDouble(&bOK);
//	double dOldValue = pVCellData->pString->toDouble();
//
//	if (!bOK)//转换失败,说明有非法字符,使用之前的内容
//	{
//		pCell->setText(*pVCellData->pString);
//	}
//	else if (fabs(dValue-dOldValue) > 0.00001)
//	{
//		long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;
//
//		if (nPrecision > 0 )
//		{
//			CString strFormat;
//			strFormat.Format(_T("%%.%ldlf"), nPrecision);
//			pVCellData->pString->Format(strFormat.GetString(), dValue);
//			pCell->setText(*pVCellData->pString);
//		}
//		else
//		{
//			*pVCellData->pString = pCell->text();
//		}
//
//		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
//	}
//}

void  QSttMacroParaEditGrid::Show_RateDouble(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, DWORD nReserved,BOOL bCanEdit)
{
	CSttGdColDef *pColDef = (CSttGdColDef*)nReserved;
	double dValue = CString_To_double(*pstrValue);
	dValue *= pColDef->m_fRate;
	CString strFormat;
	strFormat.Format(_T("%%.%df"), nPrecision);
	CString strTmp;
	strTmp.Format(strFormat.GetString(), dValue);
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow,nCol,strTmp,bHasSetItem);
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->nReserved = nReserved;

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

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrValue, pData,NULL, NULL);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_EDITBOX;
	pVCellData->nVt = VCD_STRING;
	pItem->dwValue =( nPrecision << 16);

	pItem->m_pEditFunc = EndEditCell_RateDoubleString;
	pVCellData->pFunc = EndEditCell_RateDoubleString;

	if (!bHasSetItem)
	{
		setItem(nRow,nCol,pItem);
	}
}

void  QSttMacroParaEditGrid::Show_Double_Zsetting(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue,
	DWORD nReserved, BOOL bCanEdit)
{
	CSttMacroTestParaData *pRateParaData = (CSttMacroTestParaData*)nReserved;
	double dValue = CString_To_double(*pstrValue);
	double dRateValue = CString_To_double(pRateParaData->m_strValue);
	dValue *= dRateValue;
	CString strFormat;
	strFormat.Format(_T("%%.%df"), nPrecision);
	CString strTmp;
	strTmp.Format(strFormat.GetString(), dValue);
	BOOL bHasSetItem = FALSE;
	QGV_ITEM *pItem = AddItem(nRow, nCol, strTmp, bHasSetItem/*, Qt::red*/);
	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pItem->nReserved = nReserved;
//	pItem->setTextColor(Qt::red);

	if (bCanEdit)
	{
		if (!(pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags() | Qt::ItemIsEditable));
		}
	}
	else
	{
		if ((pItem->flags() & Qt::ItemIsEditable))
		{
			pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
		}
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrValue, pData, NULL, NULL);
	pItem->lParam = (LPARAM)pVCellData;
	pItem->nDataType = QT_GVET_EDITBOX;
	pVCellData->nVt = VCD_STRING;
	pItem->dwValue = (nPrecision << 16);

	pItem->m_pEditFunc = EndEditCell_ZSettingDoubleString;
	pVCellData->pFunc = EndEditCell_ZSettingDoubleString;

	if (!bHasSetItem)
	{
		setItem(nRow, nCol, pItem);
	}
}

void QSttMacroParaEditGrid::EndEditCell_RateDoubleString(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;

	if (pVCellData == NULL)
	{
		return;
	}

	if (pCell->nReserved == 0)
	{
		return;
	}

	CSttGdColDef *pColDef = (CSttGdColDef*)pCell->nReserved;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	CString strCurrText,strTmp;
	bool bOK = false;
	strCurrText = pCell->text();
	//20240903 luozibing 直接获取text,会导致精度丢失，ZSeting出现误差
	CSttMacroTestParaData *pRateParaData = (CSttMacroTestParaData *)pGrid->GetData(nRow, nCol);
	strTmp.Format("%.1f", CString_To_double(pRateParaData->m_strValue) * 100);
	if (strCurrText == strTmp)
	{
		strCurrText.Format("%f", CString_To_double(pRateParaData->m_strValue) * 100);
	}
	double dValue =  strCurrText.toDouble(&bOK);
	double dOldValue = pVCellData->pString->toDouble();
	dValue /= pColDef->m_fRate;

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
			pVCellData->pString->Format("%f", dValue);//20240820 luozibing 保存到链表中的数据小数全保留,防止计算误差 
//			pVCellData->pString->Format(strFormat.GetString(), dValue);
			dValue *= pColDef->m_fRate;
			strCurrText.Format(strFormat.GetString(), dValue);
			pCell->setText(strCurrText);
		}
		else
		{
			*pVCellData->pString = pCell->text();
		}

		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	}
}

void QSttMacroParaEditGrid::EndEditCell_ZSettingDoubleString(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;

	if (pVCellData == NULL)
	{
		return;
	}

	if (pCell->nReserved == 0)
	{
		return;
	}

	CSttMacroTestParaData *pRateParaData = (CSttMacroTestParaData*)pCell->nReserved;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pString != NULL);

	CString strCurrText, strTmp;
	bool bOK = false;
	strCurrText = pCell->text();
	double dValue = strCurrText.toDouble(&bOK);
	double dSettingValue = pVCellData->pString->toDouble();
	double dOldValue = dSettingValue;
	dOldValue *= CString_To_double(pRateParaData->m_strValue);
	long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;

	if (nPrecision<=0)
	{
		nPrecision = 3;
	}

	CString strFormat;
	strFormat.Format(_T("%%.%ldlf"), nPrecision);

	if (!bOK)//转换失败,说明有非法字符,使用之前的内容
	{
		strCurrText.Format(strFormat.GetString(), dOldValue);
		pCell->setText(strCurrText);
	}
	else if (fabs(dValue - dOldValue) > 0.00001)
	{
		double dRate = dValue / dSettingValue;
		pRateParaData->m_strValue.Format("%f", dRate);//20240820 luozibing 保存到链表中的数据不处理小数位数
//		pRateParaData->m_strValue.Format(strFormat.GetString(), dRate);
		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	}
}

void QSttMacroParaEditGrid::EndEditCell_SelectStateCheck(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;

	if (pVCellData == NULL)
	{
		return;
	}

	if (pVCellData->pObj == NULL)
	{
		return;
	}

//	CSttMacroTestParaData *pRateParaData = (CSttMacroTestParaData*)pVCellData->pObj;
	CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pVCellData->pObj->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);

	if (pSttMacroTest != NULL)
	{
		g_theTestCntrFrame->SendSetItemState(pSttMacroTest);
	}	
}
void QSttMacroParaEditGrid::EndEditCell_ZAngDoubleString(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	CString strCurrText = pCell->text();
	double dZAng = CString_To_double(strCurrText);
	if (dZAng>STT_MULTI_MACRO_ANGMAX || dZAng<STT_MULTI_MACRO_ANGMIN)
	{//20241014 luozibing 阻抗角超过取值范围，使用之前的内容
		PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
		double dOldZAng = CString_To_double(*pVCellData->pString);
		long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;
		if (nPrecision > 0)
		{
			CString strFormat;
			strFormat.Format(_T("%%.%ldlf"), nPrecision);
			pVCellData->pString->Format(strFormat.GetString(), dOldZAng);
			pCell->setText(*pVCellData->pString);
		}
	}
	QExBaseListGridBase::EndEditCell_DoubleString(nRow, nCol, pCell, pGrid);
}
void QSttMacroParaEditGrid::ShowDataGdUI(CSttMacroTestPara* pMacroPara,CSttGdColDef *pColDef,int nRow,int nCol)
{
	if (pColDef == NULL)
	{
		return;
	}

	//if (!pColDef->m_nEditable)
	//{
	//	Show_StaticString(pMacroPara,nRow,nCol,"");
	//	return;
	//}

	CString strParaID;
	strParaID = pColDef->GetParaID();

	if (strParaID.IsEmpty())
	{
		Show_StaticString(pMacroPara,nRow,nCol,"");
	} 
	else
	{
		CSttMacroTestParaData *pSttMacroTestParaData = Global_FindAddMacroTestParaData(pMacroPara,m_pSingleMacroRef,strParaID);

		if (pSttMacroTestParaData == NULL)
		{
			Show_StaticString(pSttMacroTestParaData,nRow,nCol,"");
			return;
		}

		if (!pColDef->m_nEditable)//mod wangtao 20240927 如果不可编辑且能找到绑定参数，则显示对应数值
		{
			if (pColDef->m_strDataType == "double")//add wangtao 20241018 如果是浮点数类型则保留三位小数
			{
				long nDec = 3;

				if (!pColDef->m_strDecimal.IsEmpty())
				{
					nDec = CString_To_long(pColDef->m_strDecimal);
				}
//				pSttMacroTestParaData->m_strValue = QString::number(pSttMacroTestParaData->m_strValue.toDouble(), 'f', 3);
				Show_Double(pSttMacroTestParaData, nRow, nCol, nDec, &pSttMacroTestParaData->m_strValue,FALSE);

			}
			else
			{
				Show_StaticString(pSttMacroTestParaData, nRow, nCol, &pSttMacroTestParaData->m_strValue);
			}

			return;
		}

		if (pColDef->IsImpedanceCustomItemCtrl())//是否为自定义控件
		{
			ShowData_ImpedanceCustomItem(pMacroPara, pSttMacroTestParaData, pColDef, nRow, nCol);
		}
		else if (pColDef->IsZSettingItemCtrl())//具有比率系数的Item,如百分比,实际值与显示值之间存在比率关系
		{
			long nDec = 3;

			if (!pColDef->m_strDecimal.IsEmpty())
			{
				nDec = CString_To_long(pColDef->m_strDecimal);
			}

			Show_Double_Zsetting(pSttMacroTestParaData, nRow, nCol, nDec, &pSttMacroTestParaData->m_strValue,
				(DWORD)Global_FindAddMacroTestParaData(pMacroPara, m_pSingleMacroRef, "Rate"));
		}
		else if (pColDef->IsRateItemCtrl())//具有比率系数的Item,如百分比,实际值与显示值之间存在比率关系
		{
			long nDec = 1;//20240820 luozibing 百分比显示一位小数

			if (!pColDef->m_strDecimal.IsEmpty())
			{
				nDec = CString_To_long(pColDef->m_strDecimal);
			}

			Show_RateDouble(pSttMacroTestParaData,nRow,nCol,nDec,&pSttMacroTestParaData->m_strValue,(DWORD)pColDef);
		} 
		else if (pColDef->IsCombBoxCtrl())//ComBox控件显示
		{
			Show_DataType_Index(pSttMacroTestParaData,nRow,nCol,pColDef->m_strDataType,&pSttMacroTestParaData->m_strValue);
		}
		else if (pColDef->m_strDataType == "double")//浮点类型数据显示
		{
			long nDec = 3;

			if (!pColDef->m_strDecimal.IsEmpty())
			{
				nDec = CString_To_long(pColDef->m_strDecimal);
			}

			if (pColDef->m_nSettingAttach)//判断该行是否进行了定值关联处理
			{
				Show_Double_SettingAttach(pSttMacroTestParaData,nRow,nCol,nDec,&pSttMacroTestParaData->m_strValue);
			} 
			else
			{
				if (pColDef->m_strID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG)
				{
					Show_Double(pSttMacroTestParaData, nRow, nCol, nDec, &pSttMacroTestParaData->m_strValue, TRUE, EndEditCell_ZAngDoubleString);
				}
				else
				{
					Show_Double(pSttMacroTestParaData, nRow, nCol, nDec, &pSttMacroTestParaData->m_strValue);
				}
				
			}
		} 
		else
		{
			Show_StaticString(pSttMacroTestParaData,nRow,nCol,"");
		}	
	}
}
void QSttMacroParaEditGrid::ShowData_ImpedanceCustomItem(CSttMacroTestPara* pMacroPara, CSttMacroTestParaData *pSttMacroTestParaData,
	CSttGdColDef *pColDef, int nRow, int nCol)
{//20240906 luozibing 新增判断单元格参数id，不同id显示函数不同
	CString strParaID;
	strParaID = pColDef->GetParaID();

	long nDec = 3;
	if (!pColDef->m_strDecimal.IsEmpty())
	{
		nDec = CString_To_long(pColDef->m_strDecimal);
	}

	CSttMacroTestParaData *pParaData_Zone = Global_FindAddMacroTestParaData(pMacroPara, m_pSingleMacroRef, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);

    if (strParaID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE || strParaID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ZONETYPE)
	{//20240906 luozibing 根据故障类型值查找曲线故障类型并显示对应的区段下拉框数据
		CSttMacroTestParaData *pParaData_Fault = Global_FindAddMacroTestParaData(pMacroPara, m_pSingleMacroRef, STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
		CString strFaultType, strDataTypeID;
		strDataTypeID = STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemZone;
		strDataTypeID += "_";
		strDataTypeID += Global_GetCharFaultTypeStringByFaultType(CString_To_long(pParaData_Fault->m_strValue));
		Show_DataType_Index(pSttMacroTestParaData, nRow, nCol, strDataTypeID,&pSttMacroTestParaData->m_strValue);
	}
    else if (strParaID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING || strParaID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_TSETTING)
	{
		if (CString_To_long(pParaData_Zone->m_strValue) == STT_MULTI_MACRO_ZONELine)//当前行区段为线路长度时，可以编辑
		{
			Show_Double(pSttMacroTestParaData, nRow, nCol, nDec, &pSttMacroTestParaData->m_strValue);
	}
		else
	{
			Show_StaticString(pSttMacroTestParaData, nRow, nCol, &pSttMacroTestParaData->m_strValue);
	}
		
	}
    else if (strParaID == STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC || strParaID == STT_MULTI_MACRO_DISTANCESEARCH_PARAS_ID_ERRORLOGIC)
	{
		if (CString_To_long(pParaData_Zone->m_strValue) == STT_MULTI_MACRO_ZONELine)//当前行区段为线路长度时，可以编辑
	{
			Show_DataType_Index(pSttMacroTestParaData, nRow, nCol, pColDef->m_strDataType, &pSttMacroTestParaData->m_strValue);
		}
		else
		{
			Show_StaticString(pSttMacroTestParaData, nRow, nCol, GetDataTypeValueName(pColDef->m_strDataType, pSttMacroTestParaData->m_strValue));
		}
	}
	else
	{
		Show_StaticString(pMacroPara, nRow, nCol, "");
	}
}
CString QSttMacroParaEditGrid::GetDataTypeValueName(CString strDataTypeID, CString strIndex)
{//20240911 luozibing 根据单元格DataType的Id和误差类型值显示对应DataTypeValue值
	CString strDataValue;
	CDataType *pDataType = FindDataType(strDataTypeID);
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		if (pDataType->GetCount() == 0)
		{
			return "";
		}
		pValue = (CDataTypeValue*)pDataType->FindByIndex(strIndex);

		if (pValue == NULL)
		{
			pValue = (CDataTypeValue*)pDataType->GetHead();
		}
		return pValue->m_strName;
	}
	return "";
	
}
//20240708 huangliang
void QSttMacroParaEditGrid::UpdateObjectText(const int& nRow, const int& nCol, CExBaseObject *pData)//CVariantDataAddress oVarAddress)
{
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	if (pItem == NULL)
		return;

	QSettingItem* pNewItem = dynamic_cast<QSettingItem*>(pItem);	
	//QSettingItem *pNewItem = (QSettingItem*)pItem;//20240809 huangliang 强转有问题
	if (pNewItem == NULL)
		return;
	//pNewItem->UpdateStructText(oVarAddress);
	pNewItem->UpdateObjectText(pData);		//20240923 huangliang 是使用对象，不是结构体
}
void QSttMacroParaEditGrid::Show_Double_SettingAttach(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit, 
	GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	//20240808 huangliang 先创建为SettingItem控件
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	if (pItem == NULL)
		{
		pItem = new QSettingItem(this);
		pItem->setTextColor(Qt::black);//zhouhj 20220323 创建后默认黑色,防止部分通道在不可编辑的情况下,颜色自动变为灰色,当前行选中时,不能显示当前内容
		setItem(nRow, nCol, pItem);		//20240809 huangliang 未添加数据
	}

	QExBaseListGridBase::Show_Double(pData, nRow, nCol, nPrecision, pstrValue, bCanEdit, pFunc, bUnitConversion);

	//20240808 huangliang
	UpdateObjectText(nRow, nCol, pData);// CVariantDataAddress(pstrValue));//20240923 huangliang 是使用对象，不是结构体
}

long QSttMacroParaEditGrid::GetDataRowEx(CExBaseObject *pData, long nFromRow, long nCol)
{
	if (pData == NULL)
	{
		return -1;
	}

	CSttMacroTest *pSttMacroTest = NULL;

	if (pData->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
	{
		pSttMacroTest = (CSttMacroTest*)pData->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);

		if (pSttMacroTest == NULL)
		{
			return -1;
		}
	}
	else
	{
		pSttMacroTest = (CSttMacroTest *)pData;
	}

	CSttMacroTestPara* pMacroParas = pSttMacroTest->GetSttMacroTestPara();

	if (pMacroParas == NULL)
	{
		return -1;
	}

	long nIndex = -1;
	long nRows = rowCount();
	long nRow = nFromRow;
	nCol = 0;

	for (; nRow<nRows; nRow++)
	{
		PEXBASECELLDATA pCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol);
		ASSERT (pCellData != NULL);

		if (pCellData != NULL)
		{
			if (pCellData->pObj == pMacroParas)
			{
				nIndex = nRow;
				break;
			}
		}
	}

	return nIndex;
}

void QSttMacroParaEditGrid::SelectRow(int nRow)
{
	QExBaseListGridBase::SelectRow(nRow);
}

void QSttMacroParaEditGrid::SelectRow(CExBaseObject *pCurrSelData)
{
	long nRowCount = rowCount();
	long nCurrSelRow = -1;
	CExBaseObject *pCurrObj = NULL;

	if (pCurrSelData != NULL)
	{
		for (int nIndex = 0; nIndex< nRowCount; nIndex++)
		{
			pCurrObj = GetData(nIndex, 0);

			if (pCurrObj == NULL)
			{
				continue;
			}

			if (pCurrObj == pCurrSelData)
			{
				nCurrSelRow = nIndex;
				break;
			}

			if (pCurrObj->GetAncestor(pCurrSelData->GetClassID()) == pCurrSelData)
			{
				nCurrSelRow = nIndex;
				break;
			}
		}
	}

	SelectRow(nCurrSelRow + 1);
}

//20240926 huangliang 
BOOL QSttMacroParaEditGrid::IsAttachSettingItem(QGV_ITEM *pCell)
{
	QSettingItem* pItem = dynamic_cast<QSettingItem*>(pCell);
	if (pItem == NULL)
		return FALSE;

	if (pItem->inherits(STT_SETTING_ITEM_ClassID/*"QGV_HLITEM"*/))
	{
		if (((QSettingItem*)pItem)->IsSetting())
		{
			return TRUE;
		}
	}
	return FALSE;
}

//void QSttMacroParaEditGrid::SelectSttMacroTest(CSttMacroTest *pCurrSelData)
//{//20240913 luozibing 根据选择测试项，设置表格选中行
//	long nRowCount = rowCount();
//	long nCurrSelRow = -1;
//
//	for (int nIndex = 0; nIndex < nRowCount; nIndex++)
//	{
//		CExBaseObject *pCurrObj = (CExBaseObject *)GetData(nIndex, 0);
//		if (pCurrObj == NULL)
//		{
//			continue;;
//		}
//
//		CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pCurrObj->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);
//		if (pSttMacroTest == pCurrSelData)
//		{
//			nCurrSelRow = nIndex;
//			break;
//		}
//	}
//	SelectRow(nCurrSelRow+1);
//}