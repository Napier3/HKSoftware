#pragma once

#include "DvmDevice.h"
#include "..\GridBase\ExBaseListGrid.h"


#define DVM_DATA_COL_INDEX       0
#define DVM_DATA_COL_NAME        1
#define DVM_DATA_COL_ID          2
#define DVM_DATA_COL_DATATYPE    3
#define DVM_DATA_COL_DATATYPEID  4
#define DVM_DATA_COL_ITEMINDEX   5
#define DVM_DATA_COL_MIN         6
#define DVM_DATA_COL_MAX         7
#define DVM_DATA_COL_UNIT        8
#define DVM_DATA_COL_STEP        9
#define DVM_DATA_COL_VALUE        10
#define DVM_DATA_COL_CHANGE      11

#define DVM_DATA_COLS            12
#define DVM_DATANODES_COLS       4

class CDvmValueEditGrid;

#define ID_DATA_OPTR_COPY      5120
#define ID_DATA_OPTR_DELETE    5121
#define ID_DATA_OPTR_ADD       5122
#define ID_DATA_OPTR_MOVEUP    5123
#define ID_DATA_OPTR_MOVEDOWN  5124

//CDvmDataNodesEditGrid
class CDvmDataNodesEditGrid : public CExBaseListGrid
{
public:
	CDvmDataNodesEditGrid();
	virtual ~CDvmDataNodesEditGrid();

	virtual void InitGrid();
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);

protected:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

protected:
	static void EndEditCell_Name (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_ID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
};

//CDvmDataEditGrid
class CDvmDataEditGrid : public CExBaseListGrid
{
public:
	CDvmDataEditGrid();
	virtual ~CDvmDataEditGrid();

	//CDvmData *m_pCopyDvmData;
	CExBaseList m_listCopyDatas;


	virtual void InitGrid();
	virtual void InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	virtual BOOL OnCellRButtonUpEx(UINT nFlags, CPoint point);
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
	void SetDvmValueEditGrid(CDvmValueEditGrid *pGrid)	{	m_pAttrEditGrid = pGrid;	}

protected:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	CDvmValueEditGrid *m_pAttrEditGrid;

protected:
	static void EndEditCell_Name (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_ID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_DataType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Min (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Max (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Step (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Unit (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

public:
	void OnDataOptrDelete();
	void OnDataOptrCopy();
	void OnDataOptrAdd();
	void OnDataOptrAdd(CDvmData *pData);
	void OnDataOptrMoveUp();
	void OnDataOptrMoveDown();
};


//////////////////////////////////////////////////////////////////////////
#define DVM_DATA_VALUE_COL_INDEX       0
#define DVM_DATA_VALUE_COL_ID          1
#define DVM_DATA_VALUE_COL_DATATYPE    2

#define DVM_DATA_VALUE_COLS            3

class CDvmValueEditGrid : public CExBaseListGrid
{
public:
	CDvmValueEditGrid();
	virtual ~CDvmValueEditGrid();

	virtual void ShowDatas(CExBaseList *pExDataList);
	virtual void InitGrid();
	virtual void InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);

protected:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void InitDsvAttrDataType();


protected:
	static void EndEditCell_ID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_DataType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};
