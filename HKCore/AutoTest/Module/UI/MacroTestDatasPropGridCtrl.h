#pragma once
// #include <list>
#include "afxwin.h"

#include "..\GuideBook\GuideBookInterface.h"
#include "..\..\Module\Expression\ExprEdit.h"


#define WM_MACRO_PARA_VALUE_CHANGED (WM_USER + 6007)
#define WM_MACRO_PARA_SEL_CHANGED   (WM_USER + 6008)


class CMacroTestDatasPropGridProperty : public CMFCPropertyGridProperty
{
public:
	DECLARE_DYNAMIC(CMacroTestDatasPropGridProperty)

	CMacroTestDatasPropGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CMacroTestDatasPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	virtual ~CMacroTestDatasPropGridProperty(){}

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


class CMacroTestDatasPropGridCtrl :	public CMFCPropertyGridCtrl
{
public:
	CMacroTestDatasPropGridCtrl();
	virtual ~CMacroTestDatasPropGridCtrl();

	virtual void OnPropertyChanged(CMFCPropertyGridProperty* pProp) const;
	virtual void OnChangeSelection(CMFCPropertyGridProperty* /*pNewSel*/, CMFCPropertyGridProperty* /*pOldSel*/);

	CDataTypes *m_pDataTypesRef;
	BOOL m_bAllowEditPara;
	CExprTextUnitList *m_oExprTextUnitList;

public:
	void SetMacroTestDatas(CDataGroup  *pDataGroup, CShortDatas  *pDatas, CBaseObject *pMacroTest);
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) const ;
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) ;

protected:
	void SetMacroTestDatasRoot(CDataGroup  *pDataGroup);
	void SetMacroTestDatas(CDataGroup  *pDataGroup, CMacroTestDatasPropGridProperty *pParent);
	void SetMacroTestDatas(CShortDatas  *pDatas, CMacroTestDatasPropGridProperty *pParent);
	BOOL IsDropList(CShortData  *pData);
	BOOL IsButton(CShortData  *pData);

protected:
	virtual BOOL ShowValData(CShortData  *pData, CMacroTestDatasPropGridProperty *pParent);
	virtual BOOL IsValDataEnable(CShortData  *pData)	{	return TRUE;	}

public:
	//±í¸ñ²Ù×÷
	CShortData*  SetItemValue(const CString &strValue);
	CShortData*  GetData(int nRow);
	CShortData*  GetSelectData();
	BOOL IsCurrDataEnable();

	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);
	void ShowColumnTitle();
	void SetGridRows();

	void SetExprVariableFind(CExprVariableFind *pVariableFind)		{	m_oExprTextUnitList->SetExprVariableFind(pVariableFind);	}

	CString GetValueText(CShortData  *pData, const CString &strValue);
	CExBaseObject* GettemMacroTest()	{	return (CExBaseObject*)m_pItemMacroTest;	}

protected:
	CShortDatas  *m_pDatas;
	CDataGroup  *m_pDataGroup;
	CBaseObject *m_pItemMacroTest;
	void InitSetValueText(CString &strText, CShortData  *pData);

	CBaseObject* GetDevice()		{		return m_pItemMacroTest->GetAncestor(GBCLASSID_DEVICE);		}
	void GetEditTextValue(CString &strText, CString &strValue, CShortData *pPara);
	CMacroTestPara* GetMacroTestPara();
	CMacroTestPara* GetMacroTestPara() const;

public:
	DECLARE_MESSAGE_MAP()
};

class CMacroCharTestDataEnableState
{
public:
	virtual BOOL IsDataEnable(CShortData  *pData) = 0;
};

class CMacroChaTestrDatasPropGridCtrl : public CMacroTestDatasPropGridCtrl
{
public:
	CMacroChaTestrDatasPropGridCtrl();
	virtual ~CMacroChaTestrDatasPropGridCtrl();

	CMacroCharTestDataEnableState *m_pCMacroCharTestDataEnableState;

protected:
	virtual BOOL IsValDataEnable(CShortData  *pData);

};