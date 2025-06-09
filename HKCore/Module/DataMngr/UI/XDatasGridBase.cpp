#include "stdafx.h"
#include "XDatasGridBase.h"

//////////////////////////////////////////////////////////////////////////
//CXDatasGridBase
CXDatasGridBase::CXDatasGridBase()
{
	//初始化属性

	//初始化成员变量
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
		{//判断对象的CLASSID
			if (pObj->GetClassID() != m_dwChildClassID)
			{
				continue;
			}
		}

		if (m_strChildDataTypeID.GetLength() > 0)
		{//判断对象的数据类型 m_strDataType
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


//2020-11-23 add为了型号表 操作数据库使用；
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
		{//判断对象的CLASSID
			if (pObj->GetClassID() != m_dwChildClassID)
			{
				continue;
			}
		}

		if (m_strChildDataTypeID.GetLength() > 0)
		{//判断对象的数据类型 m_strDataType
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

//【根据属性，显示cell文本。暂时不实现浮点数显示的格式问题】
void CXDatasGridBase::ShowAttr(CShortData *pData, const CString &strAttrID, long nRow, long nCol)
{
	ShowAttrCol(pData, strAttrID, nRow, nCol);
}

//根据数据类型的属性，判断CShortData的“value”属性是否可以修改。例如“HdVersion”“SoftVersion”等就不能被修改。
BOOL CXDatasGridBase::IsValueCanEdit(const CString &strDataType) 
{
	return TRUE;
}

//初始化属性列数组
void CXDatasGridBase::InitGridColAttrs(CString *pStrColAttrs, long nCols)  
{
	m_astrColAttrs.RemoveAll();

	for (long nIndex = 0; nIndex<nCols; nIndex++)
	{
		m_astrColAttrs.Add(pStrColAttrs[nIndex]);
	}
}

//////////////////////////////////////////////////////////////////////////
//显示属性、或者是子对象
void CXDatasGridBase::ShowAttrCol(CShortData *pData, const CString &strAttrID, long nRow, long nCol)  	//显示CShortData的属性
{
	CString strValue;
	strValue = pData->GetAttrValue(strAttrID);
	Show_StaticString(pData, nRow, nCol, strValue);
}


//////////////////////////////////////////////////////////////////////////
//遍历m_astrColAttrs
void CXDatasGridBase::ShowAttrCol(CShortData *pData, long nRow, long nCol)  	//显示CShortData的属性，
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