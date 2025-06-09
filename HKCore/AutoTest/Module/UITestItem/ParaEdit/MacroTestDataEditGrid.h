#pragma once
#include "..\..\module\gridctrl\gridctrl.h"
#include "..\Module\GuideBook\GuideBookDefine.h"

class CMacroTestDataEditGrid :	public CGridCtrl
{
public:
	CMacroTestDataEditGrid();
	~CMacroTestDataEditGrid();

	void SetMacroTestDatas(CShortDatas* oDatas, CBaseObject *pMacroTest);
	CGridCell* GetSelectedCell();

	//±í¸ñ²Ù×÷
	CShortData * SetItemValue(const CString &strValue);
	CShortData * GetData(int nRow);
	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);
	void ShowColumnTitle();
	void SetGridRows();
	void ShowValData(CShortData * oData, int nRowIndex);
	virtual BOOL EndEditCell(int nRow, int nCol, DWORD dwItemData=0);

protected:
	COLORREF m_crTextColor;
	COLORREF m_crBkColor;
	CShortDatas* m_oDatas;
	CBaseObject *m_pItemMacroTest;

	CBaseObject* GetDevice()		{		return m_pItemMacroTest->GetAncestor(GBCLASSID_DEVICE);		}
	BOOL EndEditCell_Set(CGridCell *pCell, CString &strValue);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
};