#include "SttGrid_ExportRpt_Tec.h"
#include "../../../XLangResource_Native.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
CSttGrid_ExportRpt_Tec::CSttGrid_ExportRpt_Tec(QWidget* pparent):CSttGrid_ExportRpt(pparent)
{
}

CSttGrid_ExportRpt_Tec::~CSttGrid_ExportRpt_Tec()
{
	
}

//ÿ��ˢ����ʾ�������³�ʼ��
void CSttGrid_ExportRpt_Tec::InitDataTypes(CDataTypes *pDataTypes)
{
	m_oDataTypes.DeleteAll();
	m_oDataTypes.m_strID = pDataTypes->m_strID;
	m_oDataTypes.AppendCloneEx2(*pDataTypes);
}

CDataTypes* CSttGrid_ExportRpt_Tec::InitDataTypes(CDataGroup *pItemTec)
{
	m_oDataTypes.DeleteAll();
	POS pos = pItemTec->GetHeadPosition();
	CString strID;

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pItemTec->GetNext(pos);

		if (! IsDataItemsTec(pData))
		{
			//���˵�����С��λ���༭�����ã�ֻ��������Ҫ��༭������
			continue;
		}

		strID = pData->m_strID + _postfix_ID_TimesTerm;   //�̶���׺������Ƿ����������
		CDvmValue *pValue = (CDvmValue *)pData->FindByID(strID);
		InitDataTypes(pValue);

		strID = pData->m_strID + _postfix_ID_ErrRange;   //�̶���׺��ʱ��/����ֵ��Χ
		pValue = (CDvmValue *)pData->FindByID(strID);
		InitDataTypes(pValue);
	}

	m_oDataTypes.m_strID = pItemTec->m_strID;
	return &m_oDataTypes;
}

void CSttGrid_ExportRpt_Tec::InitDataTypes(CDvmValue *pValue)
{
	if (pValue == NULL)
	{
		return;
	}

	CDataType *pDataType = m_oDataTypes.AddNew2(pValue->m_strID, pValue->m_strID);
	long nIndex = 1;
	POS pos = pValue->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmValue *pChildValue = (CDvmValue *)pValue->GetNext(pos);
		pDataType->AddNewValue(pChildValue->m_strValue, pChildValue->m_strID, nIndex);
		nIndex++;
	}

	//ĩβ��һ���հ�ѡ��
	CString strID;
	strID.Format(_T("datatype_%d"), nIndex);
	pDataType->AddNewValue(_T(""), strID, nIndex);
}

void CSttGrid_ExportRpt_Tec::InitGrid()
{
 	QExBaseListGridBase::InitGrid();

	m_pDataTimesTerm = new QExBaseListComBoxDeleg_Edit(this);
	setItemDelegateForColumn(1,m_pDataTimesTerm);
	m_pDataErrorRange = new QExBaseListComBoxDeleg_Edit(this);
	setItemDelegateForColumn(2,m_pDataErrorRange);
}

void CSttGrid_ExportRpt_Tec::InitGridTitle()
{
    CString astrGridTitle[4] = {"����Ҫ������", "����Ƿ����������", "ʱ��/����ֵ��Χ", /*  "��ע" */ g_sLangTxt_State_Remark};
    int iGridWidth[4] = {150, 200, 200, 120};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 4);
}

CDataType* CSttGrid_ExportRpt_Tec::FindDataType(const CString &strDataType)
{
	return (CDataType *)m_oDataTypes.FindByID(strDataType);
}

void  CSttGrid_ExportRpt_Tec::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataType *pDataType = FindDataType(strDataType);
	Show_DataType_Val(pData, nRow, nCol, pDataType, pstrValue, pFunc);
}

void  CSttGrid_ExportRpt_Tec::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CSttGrid_ExportRpt::Show_DataType_Val(pData, nRow, nCol, pDataType, pstrValue, pFunc);
}

//�ñ����ʾ����Ҫ��༭
void CSttGrid_ExportRpt_Tec::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (! IsEnable(pData))
	{
		return;
	}

	CDvmData *pDvmData = (CDvmData *)pData;

	if (! IsDataItemsTec(pDvmData))
	{
		return;
	}

	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);
	CString strFormat = pDvmData->m_strFormat;

	if (strFormat.IsEmpty())
	{
		strFormat = _T("/");
	}
	
	CString strID = pData->m_strID + _postfix_ID_TimesTerm;   //�̶���׺������Ƿ����������
	CDvmValue *pValue = (CDvmValue *)pDvmData->FindByID(strID);

	if (pValue != NULL)
	{
		Show_DataType_Val(pDvmData, nRow, 1, strID, &pValue->m_strValue, EndEditCell_DataType_Val_Edit);
	}
	else
	{
		CString strValue;
		Show_StaticString(pDvmData, nRow, 1, &strValue);
	}
	
	strID = pData->m_strID + _postfix_ID_ErrRange;   //�̶���׺��ʱ��/����ֵ��Χ
	pValue = (CDvmValue *)pDvmData->FindByID(strID);

	if (pValue != NULL)
	{
		Show_DataType_Val(pDvmData, nRow, 2, strID, &pValue->m_strValue, EndEditCell_DataType_Val_Edit);
	}
	else
	{
		Show_String(pDvmData, nRow, 2, &pDvmData->m_strValue);
	}

 	Show_StaticString(pDvmData, nRow, 3, &strFormat);

	nRow++;
}

void CSttGrid_ExportRpt_Tec::EndEditCell_DataType_Val_Edit (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	if (pVCellData->pExBaseList == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("Row=%d  Col=%d  �������Ͷ��󲻴���")*/g_sLangTxt_DataTypeUnExist.GetString(), nRow, nCol);
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
			*(pVCellData->pString) = pValue->m_strName;
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