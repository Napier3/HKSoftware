#include "QSettingGridBase.h"

QSettingGridBase::QSettingGridBase(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

QSettingGridBase::~QSettingGridBase(void)
{
}

QGV_ITEM * QSettingGridBase::NewGVItem(const CString &sText, QColor oTextColor)
{
	QGV_ITEM *pItem = new QSettingItem(this);
	pItem->setTextColor(oTextColor);
	pItem->setText(sText);
	return pItem;
}

void QSettingGridBase::SetItemText(QGV_ITEM *pItem, const QString &strText)
{
	if(pItem == NULL)
		return ;

	if (IsAttachSettingItem(pItem))
	{
		((QSettingItem*)pItem)->RefushData();
		return;
	}

	QExBaseListGridBase::SetItemText(pItem, strText);
}

void QSettingGridBase::UpdateObjectText(const int& nRow, const int& nCol, CVariantDataAddress oVarAddress)
{
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	if (pItem == NULL)
		return;
	QSettingItem* pNewItem = dynamic_cast<QSettingItem*>(pItem);	
	//QSettingItem *pNewItem = (QSettingItem*)pItem;//20240809 huangliang 强转有问题
	if(pNewItem == NULL)
		return ;
	pNewItem->UpdateStructText(oVarAddress);
}

BOOL QSettingGridBase::IsAttachSettingItem(QGV_ITEM *pCell)
{
	QSettingItem* pItem = dynamic_cast<QSettingItem*>(pCell);
	//QSettingItem *pItem = (QSettingItem*)pCell;//20240809 huangliang 强转有问题
	if(pItem == NULL)
		return FALSE;

	if (pItem->inherits(STT_SETTING_ITEM_ClassID/*"QGV_HLITEM"*/))
	{
		if(((QSettingItem*)pItem)->IsSetting())
		{
			return TRUE;
		}		
	}
	return FALSE;
}
void QSettingGridBase::Update_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString)
{
	QGV_ITEM *pItem = GetCell(nRow, nCol);

	if (pItem != NULL)
	{
		//pItem->setText(*pString);
		SetItemText(pItem, *pString);	//20240708 huangliang
		return;
	}

	QExBaseListGridBase::Update_StaticString(pData, nRow, nCol, pString);

	//20240708 huangliang
	UpdateObjectText(nRow, nCol, CVariantDataAddress(pString));
}

void QSettingGridBase::Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
{
	QExBaseListGridBase::Show_String(pData, nRow, nCol, pString, pFunc);

	//20240708 huangliang
	UpdateObjectText(nRow, nCol, CVariantDataAddress(pString));
}

void  QSettingGridBase::Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnCheck, GRID_CELL_EDIT_FUNC pFunc, BOOL bEnable)
{
	QExBaseListGridBase::Show_Check(pData, nRow, nCol, pnCheck, pFunc, bEnable);

	//20240708 huangliang
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	UpdateObjectText(nRow, nCol, CVariantDataAddress(pnCheck));
}

void  QSettingGridBase::Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc, BOOL bEnable)
{
	QExBaseListGridBase::Show_Check(pData, nRow, nCol, pstrCheck, pFunc, bEnable);

	//20240708 huangliang
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	UpdateObjectText(nRow, nCol, CVariantDataAddress(pstrCheck));
}

void QSettingGridBase::Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	QExBaseListGridBase::Show_Float(pData, nRow, nCol, nPrecision, pfValue, bCanEdit, pFunc, bUnitConversion);

	//20240708 huangliang
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	UpdateObjectText(nRow, nCol, CVariantDataAddress(pfValue));
}

void QSettingGridBase::Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, double *pfValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	QExBaseListGridBase::Show_Double(pData, nRow, nCol, nPrecision, pfValue, bCanEdit, pFunc, bUnitConversion);

	//20240708 huangliang
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	UpdateObjectText(nRow, nCol, CVariantDataAddress(pfValue));
}

void QSettingGridBase::Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	QExBaseListGridBase::Show_Double(pData, nRow, nCol, nPrecision, pstrValue, bCanEdit, pFunc, bUnitConversion);

	//20240708 huangliang
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	UpdateObjectText(nRow, nCol, CVariantDataAddress(pstrValue));
}

void QSettingGridBase::Show_Long(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
{
	QExBaseListGridBase::Show_Long(pData, nRow, nCol, pnValue, bCanEdit, strUnit, pFunc);

	//20240708 huangliang
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	UpdateObjectText(nRow, nCol, CVariantDataAddress(pnValue));
}

void QSettingGridBase::Show_Int(CExBaseObject *pData, const int& nRow, const int& nCol, int *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
{
	QExBaseListGridBase::Show_Int(pData, nRow, nCol, pnValue, bCanEdit, strUnit, pFunc);

	//20240708 huangliang
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	UpdateObjectText(nRow, nCol, CVariantDataAddress(pnValue));
}

//20241017 huanglinag 增加支持对象的表格
void QSettingGridBase::UpdateObjectText_Object(const int& nRow, const int& nCol, CExBaseObject *pObject)
{
	QGV_ITEM *pItem = GetCell(nRow, nCol);
	if (pItem == NULL)
		return;
	QSettingItem* pNewItem = dynamic_cast<QSettingItem*>(pItem);
	if (pNewItem == NULL)
		return;
	pNewItem->UpdateObjectText(pObject);
}

void QSettingGridBase::Update_StaticString_Object(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString)
{
	QGV_ITEM *pItem = GetCell(nRow, nCol);

	if (pItem != NULL)
	{
		//pItem->setText(*pString);
		SetItemText(pItem, *pString);	//20240708 huangliang
		return;
	}

	QExBaseListGridBase::Update_StaticString(pData, nRow, nCol, pString);

	//20240708 huangliang
	UpdateObjectText_Object(nRow, nCol, pData);
}

void QSettingGridBase::Show_String_Object(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
{
	QExBaseListGridBase::Show_String(pData, nRow, nCol, pString, pFunc);

	//20240708 huangliang
	UpdateObjectText_Object(nRow, nCol, pData);
}

void  QSettingGridBase::Show_Check_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnCheck, GRID_CELL_EDIT_FUNC pFunc, BOOL bEnable)
{
	QExBaseListGridBase::Show_Check(pData, nRow, nCol, pnCheck, pFunc, bEnable);

	//20240708 huangliang
	UpdateObjectText_Object(nRow, nCol, pData);
}

void  QSettingGridBase::Show_Check_Object(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc, BOOL bEnable)
{
	QExBaseListGridBase::Show_Check(pData, nRow, nCol, pstrCheck, pFunc, bEnable);

	//20240708 huangliang
	UpdateObjectText_Object(nRow, nCol, pData);
}

void QSettingGridBase::Show_Float_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	QExBaseListGridBase::Show_Float(pData, nRow, nCol, nPrecision, pfValue, bCanEdit, pFunc, bUnitConversion);

	//20240708 huangliang
	UpdateObjectText_Object(nRow, nCol, pData);
}

void QSettingGridBase::Show_Double_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, double *pfValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	QExBaseListGridBase::Show_Double(pData, nRow, nCol, nPrecision, pfValue, bCanEdit, pFunc, bUnitConversion);

	//20240708 huangliang
	UpdateObjectText_Object(nRow, nCol, pData);
}

void QSettingGridBase::Show_Double_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	QExBaseListGridBase::Show_Double(pData, nRow, nCol, nPrecision, pstrValue, bCanEdit, pFunc, bUnitConversion);

	//20240708 huangliang
	UpdateObjectText_Object(nRow, nCol, pData);
}

void QSettingGridBase::Show_Long_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
{
	QExBaseListGridBase::Show_Long(pData, nRow, nCol, pnValue, bCanEdit, strUnit, pFunc);

	//20240708 huangliang
	UpdateObjectText_Object(nRow, nCol, pData);
}

void QSettingGridBase::Show_Int_Object(CExBaseObject *pData, const int& nRow, const int& nCol, int *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
{
	QExBaseListGridBase::Show_Int(pData, nRow, nCol, pnValue, bCanEdit, strUnit, pFunc);

	//20240708 huangliang
	UpdateObjectText_Object(nRow, nCol, pData);
}