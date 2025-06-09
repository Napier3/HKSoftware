#pragma once

#include "ExBaseListGridDef.h"

class CExBaseListXGridCtrlBase :	public CXGridCtrlBase
{
public:
	CExBaseListXGridCtrlBase();
	virtual ~CExBaseListXGridCtrlBase(void);

	CExBaseObject* GetCurrCellData();
	CExBaseObject* GetData(int nRow);
	CExBaseObject* GetCurrSelData(long nStateForCol=0);
	long GetCurrSelDatas(CExBaseList &listDatas, long nStateForCol=0);

	long GetDataRow(CExBaseObject *pData);
	CExBaseObject* GetDataRow(long nRow, long nCol=0);
	void GetAllSelectDatas(CExBaseList *pList, long nStateForCol=1);

	void ClearSelect();

	CExBaseObject* GetCurrData()							{	return m_pCurrData;			}
	CExBaseList* GetGridData()								{	return m_pDatas;			}
	CExBaseObject* GetFocusObject(int nRow,int Col);
	CExBaseObject* GetPreObject(int nRow,int nCol);

	virtual void AttachDataViewOptrInterface(CExBaseListGridOptrInterface *pInterface)	{	m_pDataViewOptrInterface = pInterface;	}

protected:
	CExBaseListGridOptrInterface *m_pDataViewOptrInterface;

	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	virtual CDataType* FindDataType(const CString &strDataType)		{	ASSERT (FALSE);	return NULL;	}
	
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
	virtual void FreeExBaseCell(long nRow, long nCol);

public:
	virtual void SetMidifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE)	{	}

public:
	virtual void InitGridTitle() = 0;
	virtual void InitGridTitle(const CString *pStrTitles, const int *pnWidth, int nCols);
	virtual void InitGrid() = 0;
	virtual BOOL UpdateData(CExBaseObject *pData);
	virtual BOOL UpdateDataIndex(long nRowBegin=1, long nIndexCol=0);

	//填充comboList cell
	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);

	//保存编辑
	virtual BOOL EndEditCell(int nRow, int nCol, DWORD dwItemData);

	//显示数据
	virtual void AttachDatas(CExBaseList *pDatas)	{	m_pDatas = pDatas;	}
	virtual void InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void UpdateDatas();
	virtual void AdjustAllCols();

	void FreeExBaseCellData(long nRow, long nCol);
	void FreeExBaseCellData(long nRow);

	virtual void MoveUp();
	virtual void MoveDown();
protected:
	CTLinkList <_ExBaseCellData> m_listVCellData;


	PEXBASECELLDATA CreateExBaseCellData(long *pnValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = _ExBaseCellData::CreateNew(pnValue, pObj, pExBaseList, pFunc);
		m_listVCellData.AddTail(p);
		return p;
	}

	PEXBASECELLDATA CreateExBaseCellData(DWORD *pnValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = _ExBaseCellData::CreateNew(pnValue, pObj, pExBaseList, pFunc);
		m_listVCellData.AddTail(p);
		return p;
	}

	PEXBASECELLDATA CreateExBaseCellData(double *pdValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = _ExBaseCellData::CreateNew(pdValue, pObj, pExBaseList, pFunc);
		m_listVCellData.AddTail(p);
		return p;
	}

	PEXBASECELLDATA CreateExBaseCellData(float *pfValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = _ExBaseCellData::CreateNew(pfValue, pObj, pExBaseList, pFunc);
		m_listVCellData.AddTail(p);
		return p;
	}

	PEXBASECELLDATA CreateExBaseCellData(CString *pStr, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = _ExBaseCellData::CreateNew(pStr, pObj, pExBaseList, pFunc);
		m_listVCellData.AddTail(p);
		return p;
	}
	PEXBASECELLDATA CreateExBaseCellData(CStringCmpBlocks *pStrCmpBlks, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = _ExBaseCellData::CreateNew(pStrCmpBlks, pObj, pExBaseList, pFunc);
		m_listVCellData.AddTail(p);
		return p;
	}

protected:
	void BackListCellData(CTLinkList <_ExBaseCellData> &listCellData)
	{
		POS pos = m_listVCellData.GetHeadPosition();
		_ExBaseCellData *p = NULL;

		while (pos != NULL)
		{
			p = m_listVCellData.GetNext(pos);
			listCellData.AddTail(p);
		}

		m_listVCellData.RemoveAll();
	}


protected:
	CExBaseObject *m_pCurrData;
	CExBaseList *m_pDatas;//表格所表示的Data对象
	static const CString m_strEmptyString;

	COLORREF m_crBkColor;
	COLORREF m_crTextColor;
	COLORREF m_crTitleTextBkColor;
	COLORREF m_crDataTextBkColor;
	long m_nAdjustBeginCol;

	CExBaseObject* GetVCellData(CGridCell *pCell);
	CExBaseObject* GetVCellData(const CCellID &oCellID);
	//显示功能
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE) = 0;

	virtual void Show_Index(CExBaseObject *pData, const int& nRow, const int& nCol, long nAddVal=0);
	virtual void Show_IndexSingle(CExBaseObject *pData, const int& nRow, const int& nCol);
	virtual void Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString);
	virtual void Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strString);
	virtual void Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void InitDataCellItem(GV_ITEM& Item, CExBaseObject *pObj);//设置文本颜色及文本背景
	virtual void InitDataCellItem(GV_ITEM& Item, CExBaseObject *pObj, const int& nRow, const int& nCol, BOOL bSetColor=TRUE);//设置文本颜色及文本背景
	
	virtual void Show_StringCmp(CExBaseObject *pData, const int& nRow, const int& nCol, CStringCmpBlocks *pStrCmpBlks);

	//编辑处理函数
	static void EndEditCell_String (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_String_NameAndID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_String_Name (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_String_ID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Datas(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	//数据类型
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strText, PEXBASECELLDATA pVCellData);

	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc=NULL);

	static void EndEditCell_DataType_Val(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual void  Show_DataType_Val_Long(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	static void EndEditCell_DataType_Val_Long(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual void  Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, float *pfValue, BOOL bCanEdit = TRUE, const CString &strUnit=_T(""), GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, double *pfValue, BOOL bCanEdit = TRUE, const CString &strUnit=_T(""), GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_Long(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnValue, BOOL bCanEdit = TRUE, const CString &strUnit=_T(""), GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DWORD(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pnValue, BOOL bCanEdit = TRUE, const CString &strUnit=_T(""), GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DWORD_Check(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pnValue,long nBits, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL);
	static void EndEditCell_Value(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual void  Show_Mac(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrMac, BOOL bSetColor=TRUE);
	static void EndEditCell_Mac (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual void  Show_Hex(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pdwValue, int iMaxLen, BOOL bCanEdit = TRUE, BOOL bSetColor=TRUE);
	static void EndEditCell_Hex (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual void  Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, long *nCheck, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bSetColor=TRUE);
	static void EndEditCell_Check (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

