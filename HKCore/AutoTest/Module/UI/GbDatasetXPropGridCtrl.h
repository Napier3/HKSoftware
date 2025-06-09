#pragma once
// #include <list>
#include "afxwin.h"

#include "..\GuideBook\GuideBookInterface.h"
#include "..\..\Module\Expression\ExprEdit.h"

#include "../GuideBook/CommCmd.h"


#define WM_GBSET_VALUE_CHANGED (WM_USER + 6009)
#define WM_GBSET_SEL_CHANGED   (WM_USER + 6010)


class CGbDatasetXPropGridCtrlProperty : public CMFCPropertyGridProperty
{
public:
	DECLARE_DYNAMIC(CGbDatasetXPropGridCtrlProperty)

	CGbDatasetXPropGridCtrlProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CGbDatasetXPropGridCtrlProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	virtual ~CGbDatasetXPropGridCtrlProperty(){}

	void SetIsValueList(BOOL b);

public:
//	virtual BOOL OnEdit(LPPOINT lptClick);
// 	virtual void OnDrawValue(CDC* pDC, CRect rect);
// 	virtual void OnDrawDescription(CDC* pDC, CRect rect);
	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
	virtual void SetValue(const COleVariant& varValue);
	virtual void SetModifyFlagEx(BOOL bFlag);

	virtual void SetCombBoxType();
	virtual void SetButtonType();

// 	virtual void OnClickButton(CPoint point);

};


class CGbDatasetXPropGridCtrl :	public CMFCPropertyGridCtrl
{
public:
	CGbDatasetXPropGridCtrl();
	virtual ~CGbDatasetXPropGridCtrl();

	virtual void OnPropertyChanged(CMFCPropertyGridProperty* pProp) const;
	virtual void OnChangeSelection(CMFCPropertyGridProperty* /*pNewSel*/, CMFCPropertyGridProperty* /*pOldSel*/);

	CDataTypes *m_pDataTypesRef;
	BOOL m_bAllowEditPara;
	CExprTextUnitList *m_oExprTextUnitList;

public:
	virtual void DeleteAllData(BOOL b)		{	RemoveAll();	}

	void ShowDatas(CExBaseList *pDatas, BOOL bAllowEditPara);
	void ShowDatas(CDataSet  *pDataSet, CValues *pValues, BOOL bAllowEditPara);
	CExBaseObject* GetCurrSelData(long nIndex=0)	{	return GetSelectData();	}
	
	void AutoSizeColumns()	{}
	void GetCurrSelDatas(CExBaseList &oList, long nCol);
	void Filter(const CString &strFilter);

public:
	void ShowGbDataset(CDataSet  *pDataGroup, BOOL bAllowEditPara);
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) const ;
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) ;

protected:
	void SetGbDatasetRoot(CDataSet  *pDataGroup);
	void InsertGbDatasetGroup(CDataSetGroup  *pDataGroup, CGbDatasetXPropGridCtrlProperty *pParent);
	BOOL IsDropList(CDataObj  *pData);
	BOOL IsButton(CDataObj  *pData);

protected:
	virtual BOOL ShowValData(CDataObj  *pData, CGbDatasetXPropGridCtrlProperty *pParent);
	virtual BOOL IsValDataEnable(CDataObj  *pData)	{	return TRUE;	}

public:
	//表格操作
	CDataObj*  SetItemValue(const CString &strValue);
	CDataObj*  GetData(int nRow);
	CDataObj*  GetSelectData();
	BOOL IsCurrDataEnable();

	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);
	void ShowColumnTitle();
	void SetGridRows();

	CString GetValueText(CDataObj  *pData, const CString &strValue);

protected:
	CDataSet  *m_pDataSet;
	void InitSetValueText(CString &strText, CDataObj  *pData);
	void GetEditTextValue(CString &strText, CString &strValue, CDataObj *pPara);

public:
	DECLARE_MESSAGE_MAP()
};


class CGbDatasetXPropEditGridCtrl : public CGbDatasetXPropGridCtrl
{
public:
	CGbDatasetXPropEditGridCtrl();
	virtual ~CGbDatasetXPropEditGridCtrl();

	CCommCmd* m_pCommCmd;		//关联的数据对象

public:
	virtual void DeleteAllData(BOOL b)		{	m_oGbDatasetGroup.DeleteAll();	RemoveAll();	}
	void InsertGbDataObjValue(CDataObjValue  *pDataObjValue, CGbDatasetXPropGridCtrlProperty *pParent);
	virtual BOOL ShowValData(CDataObj  *pData, CGbDatasetXPropGridCtrlProperty *pParent);

	void ShowDatas(CExBaseList *pGbDataset, CExBaseList *pValues);
	void InsertData(CDataObj *pData, CValue *pValue);
	void InsertData(CDataObj *pData, CValues *pValues);
	void SetItemText(long nRow, long nCol, const CString &strText);
	void DeleteSelRows(BOOL bDeleteData=TRUE, int nStateForCol=0);
	long GetRowCount();
	void UpdateData(CExBaseObject *pData);
	void AutoSizeColumn(long nCol);

protected:
	CDataSetGroup m_oGbDatasetGroup;

	void InitGbDatasetGroup(CExBaseList *pGbDataset, CExBaseList *pValues);
	void InitGbDatasetGroup_Values(CExBaseList *pGbDataset, CExBaseList *pValues);
	void InitGbDatasetGroup_Dataset(CExBaseList *pGbDataset, CExBaseList *pValues);
	void InitGbDatasetGroup_List(CExBaseList *pGbDataset, CExBaseList *pValues);
	CDataObj* AddData(CDataObj *pData, CValue *pValue);
	CDataObj* AddData(CDataObj *pData, CValues *pValues);
	CDataObjValue* AddData(CDataObjValue *pDataValue, CValues *pValues);
	void InsertDataToCtrl(CDataObj *pData);

	void DeleteSelRows_Data(CDataObj *pData);
	void DeleteSelRows_DataGroup(CDataSetGroup *pDataGroup);

};