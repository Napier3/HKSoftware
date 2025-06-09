#pragma once

#include "ExBaseListGridDef.h"

class CExBaseListGrid :	public CGridCtrl, public CExBaseCtrlOptrInterface
{
public:
	virtual BOOL Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther=TRUE, BOOL bInvalidate=TRUE);
	virtual BOOL Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate=TRUE);

	virtual void Optr_UpdateDataIndex()	{	UpdateDataIndex();	};

public:
	CExBaseListGrid();
	virtual ~CExBaseListGrid(void);

	//xxy 20210603
	void SetRowsHeight(long nHeight){m_nRowHeight = nHeight;}

	virtual CString GetGridClassID()	{	return _T("ExBaseListGrid");	}

	CExBaseObject* GetCurrCellData();
	CExBaseObject* GetData(int nRow, long nCol=0);
	CExBaseObject* GetCurrSelData(long nStateForCol=0);
	long GetCurrSelRow(long nStateForCol=0);
	long GetCurrSelDatas(CExBaseList &listDatas, long nStateForCol=0);

	long GetDataRow(CExBaseObject *pData, long nCol=0);
	long GetDataRowEx(CExBaseObject *pData, long nFromRow, long nCol);
	CExBaseObject* GetDataRow(long nRow, long nCol=0);
	void GetAllSelectDatas(CExBaseList *pList, long nStateForCol=1);

	void ClearSelect();

	CExBaseObject* GetCurrData()							{	return m_pCurrData;			}
	CExBaseList* GetGridData()								{	return m_pDatas;			}
	CExBaseObject* GetFocusObject(int nRow,int Col);
	CExBaseObject* GetPreObject(int nRow,int nCol);

	virtual void AttachDataViewOptrInterface(CExBaseListGridOptrInterface *pInterface)	{	m_pDataViewOptrInterface = pInterface;	}
	virtual void DataViewOptr_DataChanged(int nRow, int nCol);
	virtual void DataViewOptr_DataChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);

protected:
	CExBaseListGridOptrInterface *m_pDataViewOptrInterface;

	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	virtual CDataType* FindDataType(const CString &strDataType)		{	ASSERT (FALSE);	return NULL;	}
	
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
	virtual void FreeExBaseCell(long nRow, long nCol);

public:
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);//	{ SetModified(bModified);	}
	virtual long GetAdjustBeginCol()	{	return m_nAdjustBeginCol;	}
	virtual void SetAdjustBeginCol(long nAdjustBeginCol=1)	{	m_nAdjustBeginCol = nAdjustBeginCol;	} //2020-10-22  lijunqing

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
	virtual long GetDatasCount();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void AfterShowDatas(long nBeginRow, BOOL bResetScrollBars);
	virtual void UpdateDatas();
	virtual void AdjustAllCols(BOOL bResetScrollBars=TRUE);

	void FreeExBaseCellData(long nRow, long nCol);
	void FreeExBaseCellData(long nRow);

	virtual void MoveUp();
	virtual void MoveDown();
	virtual void DeleteSelRows(BOOL bDeleteData=TRUE, int nStateForCol=0);
	virtual void DeleteSelRow(BOOL bDeleteData=TRUE);
	virtual long DeleteDataRow(CExBaseObject *pData, BOOL bDeleteData=TRUE);

	void FreeListVCellData()	{	m_listVCellData.DeleteAll();	}
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
	PEXBASECELLDATA CreateExBaseCellData(wchar_t *pStr, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
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
	PEXBASECELLDATA CreateExBaseCellData(SYSTEMTIME *ptmTime, UINT nTimeFormat, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = _ExBaseCellData::CreateNew(ptmTime, nTimeFormat, pObj, pExBaseList, pFunc);
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
	long m_nRowHeight;

	CExBaseObject* GetVCellData(CGridCell *pCell);
	CExBaseObject* GetVCellData(const CCellID &oCellID);
	//显示功能
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE) = 0;

	virtual void Show_Index(CExBaseObject *pData, const int& nRow, const int& nCol);
	virtual void Show_IndexEx(CExBaseObject *pData, const int& nRow, const int& nCol, long nIndex);
	virtual void Show_IndexSingle(CExBaseObject *pData, const int& nRow, const int& nCol);
	virtual void Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString);
	virtual void Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strString);
	virtual void Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void Show_Time(CExBaseObject *pData, const int& nRow, const int& nCol, SYSTEMTIME *ptmTime, UINT nTimeFormat=VCD_TIME_FORMAT_SHORT, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void Show_WString(CExBaseObject *pData, const int& nRow, const int& nCol, wchar_t *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void InitDataCellItem(GV_ITEM& Item, CExBaseObject *pObj);//设置文本颜色及文本背景
	virtual void InitDataCellItem(GV_ITEM& Item, CExBaseObject *pObj, const int& nRow, const int& nCol, BOOL bSetColor=TRUE);//设置文本颜色及文本背景
	
	virtual void Show_StringCmp(CExBaseObject *pData, const int& nRow, const int& nCol, CStringCmpBlocks *pStrCmpBlks);

	//编辑处理函数
	static void EndEditCell_String (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Time (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_WString (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_String_NameAndID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_String_Name (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_String_ID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Datas(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	//数据类型
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strText, PEXBASECELLDATA pVCellData);

	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc=NULL);

	static void EndEditCell_DataType_Val(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual void  Show_DataType_Val_Long(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	static void EndEditCell_DataType_Val_Long(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual void  Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bUnitConversion=TRUE);
	virtual void  Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, double *pfValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bUnitConversion=TRUE);
	virtual void  Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, float *pfValue, BOOL bCanEdit = TRUE, const CString &strUnit=_T(""), GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bUnitConversion=TRUE);
	virtual void  Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, double *pfValue, BOOL bCanEdit = TRUE, const CString &strUnit=_T(""), GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bUnitConversion=TRUE);
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

	virtual void  Show_ComboBox(CExBaseList *pData, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bSetColor=TRUE);
	virtual void  Show_ComboBox(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bSetColor=TRUE);
	virtual void  Show_ComboBox(CExBaseObject *pData, CExBaseList *pListSrc, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bSetColor=TRUE);
	static void EndEditCell_ComboBox(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

void exgrid_get_SYSTEMTIME_string(CString &strText, SYSTEMTIME &tm, UINT nFormat);
