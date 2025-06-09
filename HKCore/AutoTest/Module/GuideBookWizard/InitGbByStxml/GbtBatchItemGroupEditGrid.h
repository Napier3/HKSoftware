#pragma once
#include "..\..\..\..\Module\GridCtrl\GridCtrl.h"
#include "..\GbInsertStxmlFileTool.h"

#define WM_BATCHITEM_GRID_CELL_SEL_CHANGED  (WM_USER+6752)

#define BATCHITEMEDIT_GRID_COLS   4
#define BATCHITEMEDIT_GRID_ID_INEX 0
#define BATCHITEMEDIT_GRID_ID_DATAINTERFACE  1
#define BATCHITEMEDIT_GRID_ID_DATASCRIPT     2
#define BATCHITEMEDIT_GRID_ID_DATAREF        3

class CGbtBatchItemGroupEditGrid :	public CGridCtrl
{
public:
	CGbtBatchItemGroupEditGrid(void);
	~CGbtBatchItemGroupEditGrid(void);

public:
	virtual void ShowBatchItemGroups(CGbInsertStxmlFileTool *pTool);
	virtual void InsertBatchItemGroup(CGbtBatchItemGroup *pGroup, long nColIndex=-1);

	virtual void InitExGrid();
	virtual void InitGridTitle();
	virtual void DeleteGroup(long nGroupIndex);
	virtual CGbtBatchItemGroup* GetSelBatchItemGroup();

	virtual CGbtBatchItemRef* GetSelBatchItemRef();
	virtual CGbtBatchItemRefValue* GetSelBatchItemRefValue();
	virtual void ResetGroupEditGrid();
public:

protected:
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	virtual BOOL OnCellRButtonUp(const CCellID &idCell);
	COLORREF GetCGbtBatchItemRefValueColor(CGbtBatchItemRefValue *pValue);

protected:
	CGbInsertStxmlFileTool *m_pTool;
	CGbtBatchItemGroups *m_pGbtBatchItemGroups;
	CDevice *m_pDevice;

	virtual void ShowBatchItemGroupsFixRows();
	virtual void ShowBatchItemGroup(CGbtBatchItemGroup *pGroup, long nGroupColIndex, BOOL bIsTitle);
	virtual void ShowBatchItemRefTitle(CGbtBatchItemRef *pItemRef, long &nRowIndex);
	virtual void ShowBatchItemRef(CGbtBatchItemRef *pItemRef, long nGroupColIndex, long &nRowIndex);
	virtual void DeleteBatchItemGroup(long nGroupColIndex);


protected:
	virtual void Show_StaticString(const int& nRow, const int& nCol, const CString &strText, LPARAM lParam=0);
	void Show_BatchItemGroupName(int nRow, int nCol,CGbtBatchItemGroup *pGroup);
	void Show_BatchItemGroupID(int nRow, int nCol,CGbtBatchItemGroup *pGroup);
	void Show_BatchItemValue(int nRow, int nCol,CGbtBatchItemRefValue *pValue);


	static void EndEdit_BatchItemGroupName(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEdit_BatchItemGroupID(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEdit_BatchItemValue(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};


//////////////////////////////////////////////////////////////////////////

class CGbtBatchGbtDataGroupEditGrid :	public CGbtBatchItemGroupEditGrid
{
public:
	CGbtBatchGbtDataGroupEditGrid(void);
	virtual ~CGbtBatchGbtDataGroupEditGrid(void);

public:
	virtual void InsertBatchItemGroup(CGbtBatchItemGroup *pGroup, long nColIndex=-1);
	virtual void InitExGrid();
	virtual void InitGridTitle();
	virtual void DeleteGroup(long nGroupIndex);
	virtual CGbtBatchItemGroup* GetSelBatchItemGroup();
	virtual CGbtBatchItemRef* GetSelBatchItemRef()				{	return NULL;	}
	virtual CGbtBatchItemRefValue* GetSelBatchItemRefValue()	{	return NULL;	}
	virtual void ResetGroupEditGrid();

public:
	virtual CGbtBatchGbtDataRef* GetSelBatchGbtDataRef();
	virtual CGbtBatchGbtDataGroup* GetSelBatchGbtDataGroup();

protected:
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	virtual BOOL OnCellRButtonUp(const CCellID &idCell);

protected:
	virtual void ShowBatchItemGroupsFixRows();
	virtual void ShowBatchItemGroup(CGbtBatchItemGroup *pGroup, long nGroupColIndex, BOOL bIsTitle);
	virtual void ShowBatchGbtDataRefTitle(CGbtBatchGbtDataRef *pItemRef, long &nRowIndex);
	virtual void ShowBatchGbtDataRef(CGbtBatchGbtDataRef *pItemRef, long nGroupColIndex, long &nRowIndex);
	//virtual void DeleteBatchGbtDataGroup(long nGroupColIndex);


protected:
// 	virtual void Show_StaticString(const int& nRow, const int& nCol, const CString &strText, LPARAM lParam=0);
// 	virtual void Show_BatchGbtDataGroupName(int nRow, int nCol,CGbtBatchGbtDataGroup *pGroup);
// 	virtual void Show_BatchGbtDataGroupID(int nRow, int nCol,CGbtBatchGbtDataGroup *pGroup);
//	virtual void Show_BatchGbtDataValue(int nRow, int nCol,CGbtBatchGbtDataRef *pValue);


	static void EndEdit_BatchGbtDataValue(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};
