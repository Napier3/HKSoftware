#include "SttGrid_ExportRpt.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../AutoTest/Module/TestMacroRptTemplate/RptTemp_Data.h"
#include "SttTestCntrFrameWin.h"

//////////////////////////////////////////////////////////////////////////
QExBaseListComBoxDeleg_Edit::QExBaseListComBoxDeleg_Edit(QObject *parent)
: QExBaseListComBoxDelegBase(parent)
{
	m_bEditable= TRUE;
	m_bFirstClicked = TRUE;
}

QExBaseListComBoxDeleg_Edit::~QExBaseListComBoxDeleg_Edit()
{

}

QWidget *QExBaseListComBoxDeleg_Edit::createEditor(QWidget *parent, const QStyleOptionViewItem &, 
												  const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return NULL;
	}

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if (pCurItem == NULL)
	{
		return NULL;
	}

	if (pCurItem->lParam == 0)
	{
		return NULL;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
	CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;

	if (pDataType != NULL)
	{
		QScrollComboBox *pComboBox = new QScrollComboBox(parent);
#ifdef _PSX_QT_LINUX_//linux下需要特殊处理下
		pComboBox->SetIgnoreFirstHidePopup(true);
#endif
		pComboBox->setEditable(true);
		return pComboBox;
	} 
	else
	{
		return new QLineEdit(parent);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
CSttGrid_ExportRpt::CSttGrid_ExportRpt(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pUiParas = NULL;
	m_pGuideBook = NULL;
}

CSttGrid_ExportRpt::~CSttGrid_ExportRpt()
{
	
}

void CSttGrid_ExportRpt::InitGrid()
{
 	QExBaseListGridBase::InitGrid();

	m_pDataDecimal = new QExBaseListComBoxDeleg_Edit(this);
	setItemDelegateForColumn(1,m_pDataDecimal);
}

void CSttGrid_ExportRpt::InitGridTitle()
{
    CString astrGridTitle[3] = {"报告数据名称", "保留小数位数", /*  "备注" */ g_sLangTxt_State_Remark};
    int iGridWidth[4] = {300, 180, 240};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

void CSttGrid_ExportRpt::InitDataTypes()
{
	CDataType *pDataType = m_oDataTypes.AddNew2(_prefix_ID_Precision, _prefix_ID_Precision);
	CString strID;

	for (int nIndex=1; nIndex<5; nIndex++)
	{
		strID.Format(_T("%d"), nIndex);
		pDataType->AddNewValue(strID, strID, nIndex);
	}
}

CDataType* CSttGrid_ExportRpt::FindDataType(const CString &strDataType)
{
	return (CDataType *)m_oDataTypes.FindByID(strDataType);
}

void  CSttGrid_ExportRpt::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataType *pDataType = FindDataType(strDataType);

	if (pDataType == NULL)
	{
		return;
	}

	Show_DataType_Val(pData, nRow, nCol, pDataType, pstrValue, pFunc);
}

void  CSttGrid_ExportRpt::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByName( *pstrValue );

		if (pValue == NULL)
		{
			if (*pstrValue == "")
			{
				pValue = (CDataTypeValue*)pDataType->GetHead();
			}
			else
			{
				pValue = (CDataTypeValue*)pDataType->AddNewValue(*pstrValue, *pstrValue, pDataType->GetCount()+1);
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

//该表格显示数据集
void CSttGrid_ExportRpt::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (! IsEnable(pData))
	{
		return;
	}

	CDvmData *pDvmData = (CDvmData *)pData;

	if (IsDataItemsTec(pDvmData))
	{
		//只显示保留小数位数配置
		return;
	}

	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);
	CString strFormat = pDvmData->m_strFormat;

	if (strFormat.IsEmpty())
	{
		strFormat = _T("/");
	}
	
	Show_DataType_Val(pDvmData, nRow, 1, _prefix_ID_Precision, &pDvmData->m_strValue, EndEditCell_DataType_Val_Edit);
 	Show_StaticString(pDvmData, nRow, 2, &strFormat);

	nRow++;
}

void CSttGrid_ExportRpt::SetGuideBook(CSttGuideBook *pGuideBook)
{
	m_pGuideBook = pGuideBook;
}

void CSttGrid_ExportRpt::SetItems(CExBaseObject *pItems)
{
	if (m_pGuideBook == NULL)
	{
		return;
	}

	//形参是导出报告对话框临时new的对象，是不含界面参数信息的
	//需要根据项目路径，从GuideBook中查找真实的项目；
	CString strItemPath;
	stt_gb_get_itempath_id((CSttItemBase *)pItems, strItemPath);

	CSttItems *pItemsFind = (CSttItems *)stt_gb_find_itembase(m_pGuideBook, strItemPath);
	m_pUiParas = (CExBaseList *)((QSttTestCntrFrameWin *)g_theTestCntrFrame)->GetTestMacroUiParas(pItemsFind, FALSE);
}

BOOL CSttGrid_ExportRpt::IsEnable(CExBaseObject *pData)
{
	if (m_pUiParas == NULL)
	{
		return TRUE;
	}

	CRptTemp_Data *pRptData = (CRptTemp_Data *)pData;

	CExBaseList oListParas;
	GetAllParas(&oListParas);
	BOOL bRet = pRptData->IsEnable(&oListParas);
	oListParas.RemoveAll();
	return bRet;
}

void CSttGrid_ExportRpt::GetAllParas(CExBaseList *pList)
{
	if (m_pUiParas == NULL)
	{
		return;
	}

	CSttTestMacroUiParas *pUiParas = (CSttTestMacroUiParas *)m_pUiParas;
	CDataGroup oUiParas;
	BSTR bstrText = pUiParas->m_strParaText.AllocSysString();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = oUiParas.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);// 用完释放
#endif

	GetAllParasEx(pList, &oUiParas, &oUiParas);
}

void CSttGrid_ExportRpt::GetAllParasEx(CExBaseList *pParas, CDataGroup *pUIParas, CExBaseList *pRoot)
{
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	POS pos = pUIParas->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pUIParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;
			CDvmData *pNew = new CDvmData();
			pNew->m_strID = pData->GetIDPathEx(pRoot, FALSE);//pData->m_strID;
			pNew->m_strValue = pData->m_strValue;
			pParas->AddNewChild(pNew);
		}
		else if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pGrp = (CDataGroup *)pObj;
			GetAllParasEx(pParas, pGrp, pRoot);
		}
	}
}

void CSttGrid_ExportRpt::EndEditCell_DataType_Val_Edit (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	if (pVCellData->pExBaseList == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("Row=%d  Col=%d  数据类型对象不存在")*/g_sLangTxt_DataTypeUnExist.GetString(), nRow, nCol);
		return;
	}

	CDataType *pDataType = (CDataType*)pVCellData->pExBaseList;
	ASSERT (pDataType != NULL);
	CString strTmp = pCell->text();

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByName(strTmp);

	if (pValue == NULL)
	{
		pValue = (CDataTypeValue*)pDataType->AddNewValue(strTmp, strTmp, pDataType->GetCount()+1);

		if (pVCellData->nVt == VCD_STRING)
		{
			*(pVCellData->pString) = strTmp;
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
}

BOOL IsDataItemsTec(CDvmData *pData)
{
	if (pData->m_strID.Find(_prefix_ID_Tec) >= 0)
	{
		//技术要求
		return TRUE;
	}
	else if (pData->m_strID.Find(_prefix_ID_Precision) >= 0)
	{
		//报告数据保留小数位数
		return FALSE;
	}
	else if (pData->m_strDataType == "string")
	{
		//数据类型为string，认为是技术要求
		return TRUE;
	}
	else if (pData->m_strDataType == "int")
	{
		//数据类型为int，认为是报告数据保留小数位数
		return FALSE;
	}
	else 
	{
		//默认为技术要求
		return TRUE;
	}
}