#include "stdafx.h"
#include "XDatasGridBase.h"

//////////////////////////////////////////////////////////////////////////
//CXDatasGridBase
CXDatasGridBase::CXDatasGridBase()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXDatasGridBase::~CXDatasGridBase()
{

}

void CXDatasGridBase::SetModifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	pData->SetModifiedFlag(bModified);
}


void CXDatasGridBase::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
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

			if (nClassID == DTMCLASSID_CSHORTDATA)
			{
				if (((CShortData*)pObj)->m_strDataTypeID != m_strChildDataTypeID)
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
void CXDatasGridBase::ShowDatasEx(CExBaseList *pDatas, BOOL bResetScrollBars)
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

			if (nClassID == DTMCLASSID_CSHORTDATA)
			{
				if (((CShortData*)pObj)->m_strDataTypeID != m_strChildDataTypeID)
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
void CXDatasGridBase::ShowAttr(CShortData *pData, const CString &strAttrID, long nRow, long nCol)
{
	ShowAttrCol(pData, strAttrID, nRow, nCol);
}

//�����������͵����ԣ��ж�CShortData�ġ�value�������Ƿ�����޸ġ����硰HdVersion����SoftVersion���ȾͲ��ܱ��޸ġ�
BOOL CXDatasGridBase::IsValueCanEdit(const CString &strDataType) 
{
	return TRUE;
}

//��ʼ������������
void CXDatasGridBase::InitGridColAttrs(CString *pStrColAttrs, long nCols)  
{
	m_astrColAttrs.RemoveAll();

	for (long nIndex = 0; nIndex<nCols; nIndex++)
	{
		m_astrColAttrs.Add(pStrColAttrs[nIndex]);
	}
}

//////////////////////////////////////////////////////////////////////////
//��ʾ���ԡ��������Ӷ���
void CXDatasGridBase::ShowAttrCol(CShortData *pData, const CString &strAttrID, long nRow, long nCol)  	//��ʾCShortData������
{
	CString strValue;
	strValue = pData->GetAttrValue(strAttrID);
	Show_StaticString(pData, nRow, nCol, strValue);
}


//////////////////////////////////////////////////////////////////////////
//����m_astrColAttrs
void CXDatasGridBase::ShowAttrCol(CShortData *pData, long nRow, long nCol)  	//��ʾCShortData�����ԣ�
{
	CString strAttr;

	strAttr = m_astrColAttrs.GetAt(nCol);
	ShowAttrCol(pData, strAttr, nRow, nCol);
}

//////////////////////////////////////////////////////////////////////////
//CXDatasGrid_DataRow
CXDatasGrid_DataRow::CXDatasGrid_DataRow()
{
	m_dwChildClassID = DTMCLASSID_CSHORTDATA;
}

CXDatasGrid_DataRow::~CXDatasGrid_DataRow()
{

}

void CXDatasGrid_DataRow::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CShortData*pDvmData = (CShortData*)pData;

	Show_Index(pDvmData , nRow, 0);

	long nCol = 1;
	for (nCol=1; nCol < m_nCols; nCol++)
	{
		ShowAttrCol(pDvmData, nRow, nCol);
	}

	nRow++;
}