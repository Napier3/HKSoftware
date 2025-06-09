#pragma once

#include "QSettingItem.h"
#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"

class QSettingGridBase :	public QExBaseListGridBase
{
	Q_OBJECT
public:
	QSettingGridBase(QWidget* pparent);
	virtual ~QSettingGridBase(void);

public:
	virtual QGV_ITEM * NewGVItem(const CString &sText, QColor oTextColor = Qt::black);
	virtual void SetItemText(QGV_ITEM *pItem, const QString &strText);	//更新值	
	virtual void UpdateObjectText(const int& nRow, const int& nCol, CVariantDataAddress oVarAddress);

	virtual BOOL IsAttachSettingItem(QGV_ITEM *pCell);

	virtual void Update_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString);//20220605 zhouhj 更新表格中数据值,如果当前表格不存在,则创建,如果存在,则直接更新表格中内容,提高效率
	virtual void Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc = NULL);

	virtual void  Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bUnitConversion = TRUE);
	virtual void  Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, double *pfValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bUnitConversion = TRUE);
	virtual void  Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bUnitConversion = TRUE);
	virtual void  Show_Long(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnValue, BOOL bCanEdit = TRUE, const CString &strUnit = _T(""), GRID_CELL_EDIT_FUNC pFunc = NULL);
	virtual void  Show_Int(CExBaseObject *pData, const int& nRow, const int& nCol, int *pnValue, BOOL bCanEdit = TRUE, const CString &strUnit = _T(""), GRID_CELL_EDIT_FUNC pFunc = NULL);
	virtual void  Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, long *nCheck, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bEnable = TRUE);
	virtual void  Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bEnable = TRUE);

	//20241017 huanglinag 增加支持对象的表格
	virtual void UpdateObjectText_Object(const int& nRow, const int& nCol, CExBaseObject *pObject);
	virtual void Update_StaticString_Object(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString);//20220605 zhouhj 更新表格中数据值,如果当前表格不存在,则创建,如果存在,则直接更新表格中内容,提高效率
	virtual void Show_String_Object(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc = NULL);

	virtual void  Show_Float_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bUnitConversion = TRUE);
	virtual void  Show_Double_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, double *pfValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bUnitConversion = TRUE);
	virtual void  Show_Double_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bUnitConversion = TRUE);
	virtual void  Show_Long_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnValue, BOOL bCanEdit = TRUE, const CString &strUnit = _T(""), GRID_CELL_EDIT_FUNC pFunc = NULL);
	virtual void  Show_Int_Object(CExBaseObject *pData, const int& nRow, const int& nCol, int *pnValue, BOOL bCanEdit = TRUE, const CString &strUnit = _T(""), GRID_CELL_EDIT_FUNC pFunc = NULL);
	virtual void  Show_Check_Object(CExBaseObject *pData, const int& nRow, const int& nCol, long *nCheck, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bEnable = TRUE);
	virtual void  Show_Check_Object(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bEnable = TRUE);

};
