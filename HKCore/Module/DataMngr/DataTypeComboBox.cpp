// DataTypeComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "DataTypeComboBox.h"


// CDataTypeComboBox

IMPLEMENT_DYNAMIC(CDataTypeComboBox, CComboBox)

CDataTypeComboBox::CDataTypeComboBox()
{
	m_pList = NULL;
}

CDataTypeComboBox::~CDataTypeComboBox()
{
}

void CDataTypeComboBox::ShowDataType(CDataType *pDataType)
{
	ShowBaseList(pDataType);
}

CString CDataTypeComboBox::GetSelectIndex()
{
	CDataTypeValue *pValue = (CDataTypeValue*)GetSelectObject();

	if (pValue == NULL)
	{
		return _T("");
	}
	else
	{
		return pValue->m_strIndex;
	}
}

long CDataTypeComboBox::GetSelectIndex2()
{
	return CString_To_long(GetSelectIndex());
}

BOOL CDataTypeComboBox::SetSelByIndex(const CString &strIndex)
{
	ASSERT (m_pList != NULL);

	if (m_pList == NULL)
	{
		SetCurSel(-1);
		return NULL;
	}

	CDataType *pDataType = (CDataType*)m_pList;
	CExBaseObject *pFind = pDataType->FindByIndex(strIndex);

	pFind = SetCurrSelObj(pFind);

	return (pFind != NULL);
}

BOOL CDataTypeComboBox::SetSelByIndex(long nIndex)
{
	CString strIndex;
	strIndex.Format(_T("%d"), nIndex);

	return SetSelByIndex(strIndex);
}

BEGIN_MESSAGE_MAP(CDataTypeComboBox, CComboBox)
END_MESSAGE_MAP()



// CDataTypeComboBox 消息处理程序


