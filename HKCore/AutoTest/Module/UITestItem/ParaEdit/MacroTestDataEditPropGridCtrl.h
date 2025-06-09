#pragma once
#include <list>
#include "afxwin.h"

#include "..\..\GuideBook\GuideBookInterface.h"
// #include "..\..\Module\Expression\ExprEdit.h"


#define WM_MACRO_PARA_VALUE_CHANGED (WM_USER + 6007)
#define WM_MACRO_PARA_SEL_CHANGED   (WM_USER + 6008)


class CMacroTestDataEditPropGridProperty : public CMFCPropertyGridProperty
{
public:
	DECLARE_DYNAMIC(CMacroTestDataEditPropGridProperty)

	CMacroTestDataEditPropGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CMacroTestDataEditPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	virtual ~CMacroTestDataEditPropGridProperty(){}

	void SetIsValueList(BOOL b);

public:
	virtual BOOL OnEdit(LPPOINT lptClick);
	virtual void OnDrawValue(CDC* pDC, CRect rect);
	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
	virtual void SetValue(const COleVariant& varValue);
	virtual void SetModifyFlagEx(BOOL bFlag);

	virtual void SetCombBoxType();
};


class CMacroTestDataEditPropGridCtrl :	public CMFCPropertyGridCtrl
{
public:
	CMacroTestDataEditPropGridCtrl();
	virtual ~CMacroTestDataEditPropGridCtrl();

	virtual void OnPropertyChanged(CMFCPropertyGridProperty* pProp) const;
	virtual void OnChangeSelection(CMFCPropertyGridProperty* /*pNewSel*/, CMFCPropertyGridProperty* /*pOldSel*/);

public:
	void SetMacroTestDatas(CDataGroup  *pDataGroup, CShortDatas  *pDatas, CBaseObject *pMacroTest);
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) const ;
	void UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) ;

private:
	void SetMacroTestDatasRoot(CDataGroup  *pDataGroup);
	void SetMacroTestDatas(CDataGroup  *pDataGroup, CMacroTestDataEditPropGridProperty *pParent);
	void SetMacroTestDatas(CShortDatas  *pDatas, CMacroTestDataEditPropGridProperty *pParent);
	BOOL ShowValData(CShortData  *pData, CMacroTestDataEditPropGridProperty *pParent);
	BOOL IsDropList(CShortData  *pData);

public:
	//±í¸ñ²Ù×÷
	CShortData*  SetItemValue(const CString &strValue);
	CShortData*  GetData(int nRow);
	CShortData*  GetSelectData();

	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);
	void ShowColumnTitle();
	void SetGridRows();

// 	void SetExprVariableFind(CExprVariableFind *pVariableFind)		{	m_oExprTextUnitList->SetExprVariableFind(pVariableFind);	}

	CString GetValueText(CShortData  *pData, const CString &strValue);

public:
	CBaseObject *m_pItemMacroTest;

protected:
	CShortDatas  *m_pDatas;
	CDataGroup  *m_pDataGroup;
// 	CExprTextUnitList *m_oExprTextUnitList;
	void InitSetValueText(CString &strText, CShortData  *pData);

	CBaseObject* GetDevice()		{		return m_pItemMacroTest->GetAncestor(GBCLASSID_DEVICE);		}
	void GetEditTextValue(CString &strText, CString &strValue, CShortData *pPara);

public:
	DECLARE_MESSAGE_MAP()
};

CDataTypes* mtde_GetMacroTestDataTypes(CExBaseObject *pObj);
