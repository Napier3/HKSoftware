#include "stdafx.h"
#include "XDataGroupGridBase.h"

//////////////////////////////////////////////////////////////////////////
//CXDataGroupGridBase
CXDataGroupGridBase::CXDataGroupGridBase()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXDataGroupGridBase::~CXDataGroupGridBase()
{

}

void CXDataGroupGridBase::SetModifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	pData->SetModifiedFlag(bModified);
}


void CXDataGroupGridBase::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_idCurrentCell.col = -1;
	m_idCurrentCell.row = -1;
	ClearSelect();
	CTLinkList <_ExBaseCellData> listVCellData;
	BackListCellData(listVCellData);
	//m_listVCellData.DeleteAll();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(1);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 1;
	long nCalRows = GetDatasCount() + 1;//pDatas->GetCount() + 1;
	SetRowCount(nCalRows, bResetScrollBars);
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);

		if (m_dwChildClassID > 0)
		{//�ж϶����CLASSID
			if (pObj->GetClassID() != m_dwChildClassID)
			{
				continue;
			}
		}

		if (m_strChildDataTypeID.GetLength() > 0)
		{//�ж϶������������ m_strDataType
			nClassID = pObj->GetClassID();

			if (nClassID == DTMCLASSID_CDATAGROUP)
			{
				if (((CDataGroup*)pObj)->m_strDataType != m_strChildDataTypeID)
				{
					continue;
				}
			}

			else if (nClassID == DVMCLASSID_CDVMDATA)
			{
				if (((CDvmData*)pObj)->m_strDataType != m_strChildDataTypeID)
				{
					continue;
				}
			}
		}

		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}


//2020-11-23 addΪ���ͺű� �������ݿ�ʹ�ã�
void CXDataGroupGridBase::ShowDatasEx(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_idCurrentCell.col = -1;
	m_idCurrentCell.row = -1;
	ClearSelect();
	CTLinkList <_ExBaseCellData> listVCellData;
	BackListCellData(listVCellData);

	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(1);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 1;
	long nCalRows = GetDatasCount() + 1;
	SetRowCount(nCalRows, bResetScrollBars);
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);

		if (m_dwChildClassID > 0)
		{//�ж϶����CLASSID
			if (pObj->GetClassID() != m_dwChildClassID)
			{
				continue;
			}
		}

		if (m_strChildDataTypeID.GetLength() > 0)
		{//�ж϶������������ m_strDataType
			nClassID = pObj->GetClassID();

			if (nClassID == DTMCLASSID_CDATAGROUP)
			{
				if (((CDataGroup*)pObj)->m_strDataType != m_strChildDataTypeID)
				{
					continue;
				}
			}

			else if (nClassID == DVMCLASSID_CDVMDATA)
			{
				if (((CDvmData*)pObj)->m_strDataType != m_strChildDataTypeID)
				{
					continue;
				}
			}
		}

		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

//���������ԣ���ʾcell�ı�����ʱ��ʵ�ָ�������ʾ�ĸ�ʽ���⡿
void CXDataGroupGridBase::ShowAttr(CDvmData *pData, const CString &strAttrID, long nRow, long nCol)
{
	ShowAttrCol(pData, strAttrID, nRow, nCol);
}

//�����������͵����ԣ��ж�CDvmData�ġ�value�������Ƿ�����޸ġ����硰HdVersion����SoftVersion���ȾͲ��ܱ��޸ġ�
BOOL CXDataGroupGridBase::IsValueCanEdit(const CString &strDataType) 
{
	return TRUE;
}

//��ʼ������������
void CXDataGroupGridBase::InitGridColAttrs(CString *pStrColAttrs, long nCols)  
{
	m_astrColAttrs.RemoveAll();

	for (long nIndex = 0; nIndex<nCols; nIndex++)
	{
		m_astrColAttrs.Add(pStrColAttrs[nIndex]);
	}
}

//////////////////////////////////////////////////////////////////////////
//��ʾ���ԡ��������Ӷ���
void CXDataGroupGridBase::ShowAttrCol(CDvmData *pData, const CString &strAttrID, long nRow, long nCol)  	//��ʾCDvmData������
{
	CString strValue;
	strValue = pData->GetAttrValue(strAttrID);

	if (strAttrID == g_strDataAttrID_Value)
	{
		CDataType *pDataType = FindDataType(pData->m_strDataType);

		if (pDataType != NULL)
		{
			Show_DataType_Val(pData, nRow, nCol, pDataType, &pData->m_strValue);
		}
		else
		{
			Show_String(pData, nRow, nCol, &pData->m_strValue);
		}
	}
	else
	{
		Show_StaticString(pData, nRow, nCol, strValue);
	}
}

void CXDataGroupGridBase::ShowAttrCol(CDataGroup *pDataGroup, const CString &strDataID, long nRow, long nCol)  	//��ʾDvmData�Ӷ���
{
	CExBaseObject *pFind = pDataGroup->FindByID(strDataID);

	if (pFind == NULL)
	{
		return;
	}

	if (pFind->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return;
	}

	CDvmData *pData = (CDvmData*)pFind;
	CDataType *pDataType = FindDataType(pData->m_strDataType);

	if (pDataType != NULL)
	{
		Show_DataType_Val(pData, nRow, nCol, pDataType, &pData->m_strValue);
	}
	else
	{
		Show_String(pData, nRow, nCol, &pData->m_strValue);
	}
}

//////////////////////////////////////////////////////////////////////////
//����m_astrColAttrs
void CXDataGroupGridBase::ShowAttrCol(CDvmData *pData, long nRow, long nCol)  	//��ʾCDvmData�����ԣ�
{
	CString strAttr;

	strAttr = m_astrColAttrs.GetAt(nCol);
	ShowAttrCol(pData, strAttr, nRow, nCol);
}

void CXDataGroupGridBase::ShowAttrCol(CDataGroup *pDataGroup, long nRow, long nCol)  	//��ʾDvmData�Ӷ���
{
	CString strAttr;

	strAttr = m_astrColAttrs.GetAt(nCol);
	ShowAttrCol(pDataGroup, strAttr, nRow, nCol);
}


//////////////////////////////////////////////////////////////////////////
//CXDvmGrid_DataRow
CXDvmGrid_GroupRow::CXDvmGrid_GroupRow()
{
	m_dwChildClassID = DTMCLASSID_CDATAGROUP;
}

CXDvmGrid_GroupRow::~CXDvmGrid_GroupRow()
{

}


void CXDvmGrid_GroupRow::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CXDvmGrid_GroupRow::InitGridTitle()
{
	CString astrTitle[3] = {_T("���"),_T("ģ������")};
	CString astrAttrs[3] = {_T(""),_T("Name"), _T("ID")};
	int nWidth[5]={40,120,120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 3);
	InitGridColAttrs(astrAttrs, 3);
}

void CXDvmGrid_GroupRow::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	Show_Index(pData , nRow, 0);
	Show_StaticString(pData , nRow, 1, pData->m_strName);
	Show_StaticString(pData , nRow, 2, pData->m_strID);

	nRow++;
}


//////////////////////////////////////////////////////////////////////////
//CXDvmGrid_DataRow
CXDvmGrid_DataRow::CXDvmGrid_DataRow()
{
	m_dwChildClassID = DVMCLASSID_CDVMDATA;
}

CXDvmGrid_DataRow::~CXDvmGrid_DataRow()
{

}

void CXDvmGrid_DataRow::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData*pDvmData = (CDvmData*)pData;

	Show_Index(pDvmData , nRow, 0);

	long nCol = 1;
	for (nCol=1; nCol < m_nCols; nCol++)
	{
		ShowAttrCol(pDvmData, nRow, nCol);
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CXDvmGrid_GroupRowDataCol
CXDvmGrid_GroupRowDataCol::CXDvmGrid_GroupRowDataCol()
{
	m_dwChildClassID = DTMCLASSID_CDATAGROUP;
}

CXDvmGrid_GroupRowDataCol::~CXDvmGrid_GroupRowDataCol()
{

}

void CXDvmGrid_GroupRowDataCol::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDataGroup*pDataGroup = (CDataGroup*)pData;

	Show_Index(pDataGroup , nRow, 0);

	for (long nCol=1; nCol<m_nCols; nCol++)
	{
		ShowAttrCol(pDataGroup , nRow, nCol);
	}

	nRow++;
}

