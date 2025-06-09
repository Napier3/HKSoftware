#include "QDataTypeComboBox.h"

QDataTypeComboBox::QDataTypeComboBox(QWidget *parent)
: CExBaseListComboBox(parent)
{
}

QDataTypeComboBox::~QDataTypeComboBox()
{

}

void QDataTypeComboBox::ShowDataType(CDataType *pDataType)
{
	ShowBaseList(pDataType);
}

CString QDataTypeComboBox::GetSelectIndex()
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

long QDataTypeComboBox::GetSelectIndex2()
{
	return CString_To_long(GetSelectIndex());
}

BOOL QDataTypeComboBox::SetSelByIndex(const CString &strIndex)
{
	ASSERT (m_pList != NULL);

	if (m_pList == NULL)
	{
		setCurrentIndex(-1);
		return NULL;
	}

	CDataType *pDataType = (CDataType*)m_pList;
	CExBaseObject *pFind = pDataType->FindByIndex(strIndex);

	pFind = SetCurrSelObj(pFind);

	return (pFind != NULL);
}

BOOL QDataTypeComboBox::SetSelByIndex(long nIndex)
{
	CString strIndex;
	strIndex.Format(_T("%d"), nIndex);

	return SetSelByIndex(strIndex);
}

CExBaseObject* QDataTypeComboBox::GetSelectObject()
{
	CString strText;
	strText = currentText();

	if ((m_pList == NULL)||(strText.IsEmpty()))
	{
		return NULL;
	}

	return (CExBaseObject*)m_pList->FindByName(strText);
}

// long QDataTypeComboBox::AddObj(CExBaseObject *pObj)
// {
// 	if (!CanAdd(pObj))
// 	{
// 		return -1;
// 	}
// 
// 	long nIndex = count();
// 
// 	if (m_bAddName)
// 	{
// 		addItem(pObj->m_strName,QVariant::fromValue((void*)pObj));
// 	}
// 	else
// 	{
// 		addItem(pObj->m_strID,QVariant::fromValue((void*)pObj));
// 	}
// 
// 	SetItemData(nIndex, (DWORD)pObj);
// 
// 	return nIndex;
// }
