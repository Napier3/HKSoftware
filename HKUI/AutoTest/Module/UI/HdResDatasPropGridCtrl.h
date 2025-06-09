#pragma once
// #include <list>
#include "afxwin.h"

#include "..\GuideBook\GuideBookInterface.h"
#include "..\..\Module\Expression\ExprEdit.h"


#define WM_MACRO_PARA_VALUE_CHANGED (WM_USER + 6007)
#define WM_MACRO_PARA_SEL_CHANGED   (WM_USER + 6008)


class CHdResDatasPropGridProperty : public CMFCPropertyGridProperty
{
public:
	DECLARE_DYNAMIC(CHdResDatasPropGridProperty)

	CHdResDatasPropGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CHdResDatasPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	virtual ~CHdResDatasPropGridProperty(){}

	void SetIsValueList(BOOL b);

public:
	virtual BOOL OnEdit(LPPOINT lptClick);
	virtual void OnDrawValue(CDC* pDC, CRect rect);
	virtual void OnDrawDescription(CDC* pDC, CRect rect);
	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
	virtual void SetValue(const COleVariant& varValue);
	virtual void SetModifyFlagEx(BOOL bFlag);

	virtual void SetCombBoxType();
	virtual void SetButtonType();

	virtual void OnClickButton(CPoint point);

};


class CHdResDatasPropGridCtrl :	public CMFCPropertyGridCtrl
{
public:
	CHdResDatasPropGridCtrl();
	virtual ~CHdResDatasPropGridCtrl();

	virtual void OnPropertyChanged(CMFCPropertyGridProperty* pProp) const;
	virtual void OnChangeSelection(CMFCPropertyGridProperty* /*pNewSel*/, CMFCPropertyGridProperty* /*pOldSel*/);

	CDataTypes *m_pDataTypesRef;
	BOOL m_bAllowEditPara;
	CExprTextUnitList *m_oExprTextUnitList;

public:
	void SetHdResDatasPropGridCtrlDatas(CDataGroup  *pDataGroup);
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) const ;
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) ;

protected:
	void SetHdResDatasPropGridCtrlDatasRoot(CDataGroup  *pDataGroup);
	void SetHdResDatasPropGridCtrlDatas(CDataGroup  *pDataGroup, CHdResDatasPropGridProperty *pParent);
	BOOL IsDropList(CDvmData  *pData);
	BOOL IsButton(CDvmData  *pData);

protected:
	virtual BOOL ShowValData(CDvmData  *pData, CHdResDatasPropGridProperty *pParent);
	virtual BOOL IsValDataEnable(CDvmData  *pData)	{	return TRUE;	}

public:
	//表格操作
	CDvmData*  SetItemValue(const CString &strValue);
	CDvmData*  GetData(int nRow);
	CDvmData*  GetSelectData();
	BOOL IsCurrDataEnable();

	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);
	void ShowColumnTitle();
	void SetGridRows();

	void SetExprVariableFind(CExprVariableFind *pVariableFind)		{	m_oExprTextUnitList->SetExprVariableFind(pVariableFind);	}

	CString GetValueText(CDvmData  *pData, const CString &strValue);
	CExBaseObject* GettemHdResDatasPropGridCtrl()	{	return (CExBaseObject*)m_pItemHdResDatasPropGridCtrl;	}
	void SettemHdResDatasPropGridCtrl(CExBaseObject *p)	{	m_pItemHdResDatasPropGridCtrl = p;	}

protected:
	CDataGroup  *m_pDataGroup;
	CExBaseObject *m_pItemHdResDatasPropGridCtrl;
	void InitSetValueText(CString &strText, CDvmData  *pData);

	CBaseObject* GetDevice()		{		return m_pItemHdResDatasPropGridCtrl->GetAncestor(GBCLASSID_DEVICE);		}
	void GetEditTextValue(CString &strText, CString &strValue, CDvmData *pPara);

public:
	DECLARE_MESSAGE_MAP()
};
