#pragma once

#include "..\DvmDevice.h"
#include "..\..\GridBase\ExBaseListGrid.h"
#include "DsvScript.h"

#define  ANLYELEMENT_MODE_DATATYPE _T("any_element_mode")

class CDsvScriptEditInterface
{
public:
	virtual void SetEditDvData(CExBaseObject *pData) = 0;
	virtual DWORD GetDsvScriptEditID() = 0;
};

class CDsvScriptDlgInterface
{
public:
	virtual void SetCurrDsvScriptEditInterface(CDsvScriptEditInterface *pEditInterface) = 0;
	virtual void InitAttrDataType(CDataType *pDataType, CExBaseObject *pData) = 0;
	virtual void InitAttrVariableDataType(CDataType *pDataType) = 0;
};


#define DSV_ELEMENT_COL_INDEX   0
#define DSV_ELEMENT_COL_NAME    1
#define DSV_ELEMENT_COL_ID      2
#define DSV_ELEMENT_COL_MINOCC  3
#define DSV_ELEMENT_COL_MAXOCC  4

#define DSV_ELEMENT_COLS        5

class CDsvScriptAttrEditGrid;

class CDsvScriptEditGrid : public CExBaseListGrid, public CDsvScriptEditInterface
{
protected:
	static long g_nDsvScriptAttrRef;
	static CDataType *g_pDsvAnyElementDataType;

	void CreateDsvAnyElementDataType();
	void ReleaseDsvAnyElementDataType();

public:
	CDsvScriptEditGrid();
	virtual ~CDsvScriptEditGrid();

	CDsvScriptDlgInterface *m_pDsvScriptDlgInterface;

	virtual void SetEditDvData(CExBaseObject *pData);
	virtual DWORD GetDsvScriptEditID()	{	return 0;	}

	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pExDataList);
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);

	virtual void InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

protected:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	CDsvScriptAttrEditGrid *m_pAttrEditGrid;

public:
	void SetDsvScriptAttrEditGrid(CDsvScriptAttrEditGrid *pAttrEditGrid)	{	m_pAttrEditGrid = pAttrEditGrid;	}
};


//////////////////////////////////////////////////////////////////////////
#define DSV_ELEMENT_ATTR_COL_INDEX   0
#define DSV_ELEMENT_ATTR_COL_ID      1
#define DSV_ELEMENT_ATTR_COL_TYPE    2
#define DSV_ELEMENT_ATTR_COL_OPTR    3
#define DSV_ELEMENT_ATTR_COL_VALUE   4
#define DSV_ELEMENT_ATTR_COL_VALUE2  5
#define DSV_ELEMENT_ATTR_COL_VARIABLE  6

#define DSV_ELEMENT_ATTR_COLS        7


class CDsvScriptAttrEditGrid : public CExBaseListGrid, public CDsvScriptEditInterface
{
public:
	CDsvScriptAttrEditGrid();
	virtual ~CDsvScriptAttrEditGrid();

	CDsvScriptDlgInterface *m_pDsvScriptDlgInterface;

	virtual void SetEditDvData(CExBaseObject *pData);
	virtual DWORD GetDsvScriptEditID()	{	return 1;	}

	virtual void ShowDatas(CExBaseList *pExDataList);
	virtual void InitGrid();
	virtual void InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	void InitDsvAttrVariables();

protected:
	static long g_nDsvScriptAttrRef;
	static CDataType *g_pDsvAttrDataType;
	static CDataType *g_pDsvAttrOptr;
	static CDataType *g_pDsvAttrAttrs;
	static CDataType *g_pDsvAttrAttrsAll;
	static CDataType *g_pDsvAttrVariables;

	void InitDsvAttrAttrs();

protected:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void InitDsvAttrDataType();


protected:
	static void EndEditCell_AttrID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_AttrDataType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_AttrOptr (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Variable (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};


//////////////////////////////////////////////////////////////////////////
#define DSV_ELIMINATE_COL_INDEX   0
#define DSV_ELIMINATE_COL_NAME    1
#define DSV_ELIMINATE_COL_ID      2

#define DSV_ELIMINATE_COLS        3


class CDsvScriptEliminateEditGrid : public CExBaseListGrid, public CDsvScriptEditInterface
{
public:
	CDsvScriptEliminateEditGrid();
	virtual ~CDsvScriptEliminateEditGrid();

	CDsvScriptDlgInterface *m_pDsvScriptDlgInterface;

	virtual void InitGrid();
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);

	virtual void InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
protected:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void SetEditDvData(CExBaseObject *pData);
	virtual DWORD GetDsvScriptEditID() {	return 0;	}
};
