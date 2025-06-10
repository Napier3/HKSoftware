#include "SttImportDvmFile_EditGrid.h"
#include "..\..\..\..\Module\API\GlobalConfigApi.h"
#include "..\..\..\..\AutoTest\Module\GbItemsGen\GbSmartGenWzd\GbSmartGenWzd.h"
#include "../../XLangResource_Native.h"


extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QSttImportDvmFile_EditGrid_CheckBoxDelegate::QSttImportDvmFile_EditGrid_CheckBoxDelegate(QObject *parent)
: QExBaseListCheckBoxDelegate(parent)
{
	CString strEmptyPath;
	strEmptyPath =  _P_GetResourcePath();
	strEmptyPath += _T("Empty.png");
	m_oEmptyPixmap.load(strEmptyPath);
	m_oEmptyPixmap.scaled(20,20);
}

QSttImportDvmFile_EditGrid_CheckBoxDelegate::~QSttImportDvmFile_EditGrid_CheckBoxDelegate()
{

}

//��굥����Ԫ���ʱ���ػ��¼�����
void QSttImportDvmFile_EditGrid_CheckBoxDelegate::paint(QPainter * painter,
													 const QStyleOptionViewItem & option,
													 const QModelIndex & index) const
{
	CDvmData *pDvmData = NULL;
	QGV_ITEM* pCurItem = GetCurrItem(index);
	BOOL bTypeBool = FALSE;

	if ((pCurItem != NULL)&&(pCurItem->lParam != 0))
	{
		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
		pDvmData = (CDvmData *)pVCellData->pObj;
		CDvmValue *pFind = pDvmData->GetDataValue();   //���س�$t  $q֮��ĵ�һ��pDvmData�Ӷ���

		if (pFind == NULL)
		{
			if (pDvmData->m_strDataType == _T("BOOL"))
			{
				bTypeBool = TRUE;
			}
		}
		else if (pFind->m_strDataType == _T("BOOL"))
		{
			bTypeBool = TRUE;
		}
	}

	if (!bTypeBool)
	{
		return;
	}

	bool bChecked = index.model()->data(index, Qt::CheckStateRole).toBool();//����ͼƬ
	QRect rect = option.rect;
	QPoint pt = rect.center();

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

CSttImportDvmFile_EditGrid::CSttImportDvmFile_EditGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pValues = NULL;
	m_pDatasEdit = NULL;
	m_pDatasList = NULL;
}

CSttImportDvmFile_EditGrid::~CSttImportDvmFile_EditGrid()
{
	if (m_pValues != NULL)
	{
		m_pValues->RemoveAll();
		delete m_pValues;
		m_pValues = NULL;
	}

	if (m_pDatasEdit != NULL)
	{
		m_pDatasEdit->RemoveAll();
		delete m_pDatasEdit;
		m_pDatasEdit = NULL;
	}

	if (m_pDatasList != NULL)
	{
		m_pDatasList->RemoveAll();
		delete m_pDatasList;
		m_pDatasList = NULL;
	}
}

void CSttImportDvmFile_EditGrid::ClearCmdsValues()
{
	if (m_pValues == NULL)
	{
		return;
	}

	m_pValues->RemoveAll();
}

void CSttImportDvmFile_EditGrid::InitCmdsValues(CSttCommCmd *pCommCmd)
{
	if (m_pValues == NULL)
	{
		m_pValues = new CValues();
	}

	CSttCommCmdData* pCmd = pCommCmd->GetCommCmdData(FALSE);
	
	if (pCmd != NULL)
	{
		m_pValues->AppendEx(*pCmd, FALSE);
	}
}

void CSttImportDvmFile_EditGrid::AddDataToEditList(CDvmData *pData)
{
	if (m_pDatasEdit == NULL)
	{
		m_pDatasEdit = new CExBaseList();
	}

	POS pos = m_pDatasEdit->Find(pData);

	if (pos == NULL)
	{
		m_pDatasEdit->AddTail(pData);
	}
}

void CSttImportDvmFile_EditGrid::ClearEditList()
{
	if (m_pDatasEdit == NULL)
	{
		return;
	}

	m_pDatasEdit->RemoveAll();
}

void CSttImportDvmFile_EditGrid::InitDatasList(const CString &strDsKey)
{
	CExBaseList oListDatasets;  //���ݼ��б�
	CDvmDevice *pDevice = g_theGbSmartGenWzd->m_pDvmDevice;
	pDevice->GetDatasetList(strDsKey, oListDatasets);

	if (m_pDatasList == NULL)
	{
		m_pDatasList = new CExBaseList();
	}

	m_pDatasList->RemoveAll();
	POS pos = oListDatasets.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)oListDatasets.GetNext(pos);

		m_pDatasList->AppendEx(*pDataset, FALSE);
	}

	oListDatasets.RemoveAll();
}

void CSttImportDvmFile_EditGrid::InitDatasList(CStringArray &oDsKeyArray)
{
	CExBaseList oListDatasets;  //���ݼ��б�
	CDvmDevice *pDevice = g_theGbSmartGenWzd->m_pDvmDevice;
	pDevice->GetDatasetList(oDsKeyArray, oListDatasets);

	if (m_pDatasList == NULL)
	{
		m_pDatasList = new CExBaseList();
	}

	m_pDatasList->RemoveAll();
	POS pos = oListDatasets.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)oListDatasets.GetNext(pos);

		m_pDatasList->AppendEx(*pDataset, FALSE);
	}

	oListDatasets.RemoveAll();
}

void CSttImportDvmFile_EditGrid::ClearEmptyDatas()
{
	if (m_pDatasEdit == NULL)
	{
		return;
	}

	POS pos = m_pDatasEdit->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)m_pDatasEdit->GetNext(pos);

		if (pData->m_strValue.IsEmpty())
		{
			m_pDatasEdit->Remove(pData);
		}
	}
}

void CSttImportDvmFile_EditGrid::InitGrid()
{
	QExBaseListGridBase::InitGrid();
}

void CSttImportDvmFile_EditGrid::InitGridTitle()
{
//	CString astrGridTitle[8] = {"����", /*"��ʶ",*/ "��ֵ", "�޸�Ϊ", "��λ", "��Сֵ", "���ֵ", "����", ""};
	CString astrGridTitle[8] = {g_sLangTxt_Name, /*g_sLangTxt_Native_Identifier, */g_sLangTxt_Value, g_sLangTxt_Native_modifyto,
		g_sLangTxt_Unit, g_sLangTxt_MinValue, g_sLangTxt_MaxValue, g_sLangTxt_Step, ""};
	int iGridWidth[8]={200, 120, 120, 40, 100, 100, 100, 10};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 8);
}

void CSttImportDvmFile_EditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = (CDvmData *)pData;	
	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);   //����

	CDvmValue *pFind = pDvmData->GetDataValue();   //���س�$t  $q֮��ĵ�һ��pDvmData�Ӷ���

	if (pFind == NULL)
	{
		pDvmData->m_dwItemData = (unsigned long)pData;
		if (pDvmData->m_strDataType == "BOOL")
		{
			pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
			Show_Check(pDvmData, nRow, 1, (long*)(&pDvmData->m_dwReserved), NULL, FALSE);   //��ֵ
			ShowData_CmdValue_BOOL(pDvmData, nRow);   //�޸�Ϊ

			Show_StaticString(pDvmData, nRow, 5, &pDvmData->m_strMax);   //���ֵ
			Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMin);   //��Сֵ
		}
		else
		{
			//��բ����ֻ��ͨ��ID�жϡ���բ�������65535�������󳤶�2���ֽڡ�
			if (pDvmData->m_strID.Find("OUTMATR") > 0)
			{
				pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
				DWORD dwMax = CString_To_long(pDvmData->m_strMax);
				DWORD dwMin = CString_To_long(pDvmData->m_strMin);

				Show_Hex(pDvmData, nRow, 1, &pDvmData->m_dwReserved, 2, FALSE);   //��ֵ
				ShowData_CmdValue_Hex(pDvmData, nRow);   //�޸�Ϊ

				Show_Hex(pDvmData, nRow, 5, &dwMax, 2, FALSE);   //���ֵ
				Show_Hex(pDvmData, nRow, 4, &dwMin, 2, FALSE);   //��Сֵ
			}
			else
			{
				Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strValue);//��ֵ
				ShowData_CmdValue_String(pDvmData, nRow);  //�޸�Ϊ

				Show_StaticString(pDvmData, nRow, 5, &pDvmData->m_strMax);   //���ֵ
				Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMin);   //��Сֵ
			}
		}
	}
	else
	{
		pDvmData->m_dwItemData = (unsigned long)pFind;

		if (pFind->m_strDataType == "BOOL")
		{
			pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);

			Show_Check(pDvmData, nRow, 1, (long*)(&pDvmData->m_dwReserved), NULL, FALSE);//��ֵ
			ShowData_CmdValue_BOOL(pDvmData, nRow);   //�޸�Ϊ

			Show_StaticString(pDvmData, nRow, 5, &pDvmData->m_strMax);//���ֵ
			Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMin);//��Сֵ

			pDvmData->m_nChange = 1;
		}
		else if (pFind->m_strID.Find("OUTMATR") > 0)
		{
			//��բ����ֻ��ͨ��ID�жϡ���բ�������65535�������󳤶�2���ֽڡ�
			pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
			DWORD dwMax = CString_To_long(pDvmData->m_strMax);
			DWORD dwMin = CString_To_long(pDvmData->m_strMin);

			Show_Hex(pDvmData, nRow, 1, &pDvmData->m_dwReserved, 2, FALSE);//��ֵ
			ShowData_CmdValue_Hex(pDvmData, nRow);   //�޸�Ϊ

			Show_Hex(pDvmData, nRow, 5, &dwMax, 2, FALSE);//���ֵ
			Show_Hex(pDvmData, nRow, 4, &dwMin, 2, FALSE);//��Сֵ
		}
		else
		{
			Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strValue);//��ֵ
			ShowData_CmdValue_String(pDvmData, nRow);  //�޸�Ϊ

			Show_StaticString(pDvmData, nRow, 5, &pDvmData->m_strMax);//���ֵ
			Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strMin);//��Сֵ
		}
	}

	Show_StaticString(pDvmData, nRow, 3, &pDvmData->m_strUnit);   //��λ
	Show_StaticString(pDvmData, nRow, 6, &pDvmData->m_strStep);   //����

	nRow++;
}

void CSttImportDvmFile_EditGrid::ShowData_CmdValue_String(CDvmData *pData, int& nRow)
{
	CValue *pValue = (CValue *)m_pValues->FindByID(pData->m_strID);

	if (pValue != NULL)
	{
		Show_String(pData, nRow, 2, &pValue->m_strValue, EndEditCell_CmdDataValue);   //�޸�Ϊ
	}
	else
	{
		//�˴�Ϊ����ʾ���ַ�����ʹ������ʱ����strValue���ڻص��У��Ͳ���ʹ��pString
		CString strValue;
		Show_String(pData, nRow, 2, &strValue, EndEditCell_CmdDataValue);
	}
}

void CSttImportDvmFile_EditGrid::ShowData_CmdValue_BOOL(CDvmData *pData, int& nRow)
{
	CValue *pValue = (CValue *)m_pValues->FindByID(pData->m_strID);

	if (pValue != NULL)
	{
		pValue->m_dwReserved = CString_To_long(pValue->m_strValue);
		Show_Check(pData, nRow, 2, (long*)(&pValue->m_dwReserved), EndEditCell_CmdDataValue_BOOL); //�޸�Ϊ
	}
	else
	{
		DWORD dwValue = CString_To_long(pData->m_strValue);
		Show_Check(pData, nRow, 2, (long*)(&dwValue), EndEditCell_CmdDataValue_BOOL);   //�޸�Ϊ
	}
}

void CSttImportDvmFile_EditGrid::ShowData_CmdValue_Hex(CDvmData *pData, int& nRow)
{
	CValue *pValue = (CValue *)m_pValues->FindByID(pData->m_strID);

	if (pValue != NULL)
	{
		pValue->m_dwReserved = CString_To_long(pValue->m_strValue);
		Show_Hex(pData, nRow, 2, &pValue->m_dwReserved, 2, TRUE, TRUE, EndEditCell_CmdDataValue_Hex); //�޸�Ϊ
	}
	else
	{
		DWORD dwValue = CString_To_long(pData->m_strValue);
		Show_Hex(pData, nRow, 2, &dwValue, 2, TRUE, TRUE, EndEditCell_CmdDataValue_Hex); //�޸�Ϊ
	}
}

void CSttImportDvmFile_EditGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	DisConnectAll_SigSlot();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(0);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt�в�����������
	long nCalRows = GetDatasCount();//zhouhj Qt�в�����������
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

void CSttImportDvmFile_EditGrid::EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CString strCurValue = pCell->text();

	//if (*pVCellData->pString != strCurValue)
	{
		CDvmData *pData = (CDvmData *)pVCellData->pObj;

		if (strCurValue.GetLength() > 0)
		{
			//��ֹģ���б��޸�Ϊһ�����ַ���
			pData->m_strValue = strCurValue;
		}
		
		//pVCellData->pString = &pData->m_strValue;

		((CSttImportDvmFile_EditGrid *)pGrid)->AddDataToEditList(pData);
	}
}

void CSttImportDvmFile_EditGrid::ShowDatas()
{
	ShowDatas(m_pDatasList);
}
/*
enum CheckState {
   Unchecked,
   PartiallyChecked,
   Checked
};
*/
void CSttImportDvmFile_EditGrid::EndEditCell_CmdDataValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (*pVCellData->pnValue != pCell->checkState())
	{
		CDvmData *pData = (CDvmData *)pVCellData->pObj;

		if (pCell->checkState() == Qt::Unchecked)
		{
			*pVCellData->pnValue = 0;
			pData->m_strValue = _T("0");
		}
		else
		{
			*pVCellData->pnValue = 1;
			pData->m_strValue = _T("1");
		}

		((CSttImportDvmFile_EditGrid *)pGrid)->AddDataToEditList(pData);
	}
}

void CSttImportDvmFile_EditGrid::EndEditCell_CmdDataValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
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
		CDvmData *pData = (CDvmData *)pVCellData->pObj;
		*pVCellData->pdwValue = dwCurValue;

		pData->m_strValue.Format(_T("%d"), dwCurValue);

		((CSttImportDvmFile_EditGrid *)pGrid)->AddDataToEditList(pData);
	}
}