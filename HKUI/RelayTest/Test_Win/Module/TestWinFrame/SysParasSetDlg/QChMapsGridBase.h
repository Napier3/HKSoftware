#ifndef QCHMAPSGRIDBASE_H
#define QCHMAPSGRIDBASE_H

#include <QTableWidget>
#include <QStandardItemModel>
#include "../../../Module/BaseClass/ExBaseList.h"

#include "QGridDefine.h"

typedef struct _ExBaseCellData
{
	LONG nVt;//关联的数据类型

	union
	{
		DWORD *pdwValue;
		long *pnValue;
		double *pdValue;
		float *pfValue;
		CString *pString;
// 		wchar_t *pWString;
// 		CStringCmpBlocks *pStrCmpBlks;
// 		SYSTEMTIME *ptmTime;
	};

	CExBaseObject *pObj;
	CExBaseList *pExBaseList;
	GRID_CELL_EDIT_FUNC *pFunc;

	static _ExBaseCellData* CreateNew(long *pnValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
//		exgrid_set_vcd_vt(pNew->nVt, VCD_LONG);
		pNew->pnValue = pnValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(DWORD *pdwValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
//		exgrid_set_vcd_vt(pNew->nVt, VCD_DWORD);
		pNew->pdwValue = pdwValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(double *pdValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
//		exgrid_set_vcd_vt(pNew->nVt, VCD_DOUBLE);
		pNew->pdValue = pdValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(float *pfValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
//		exgrid_set_vcd_vt(pNew->nVt, VCD_FLOAT);
		pNew->pfValue = pfValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(CString *pStr, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
//		exgrid_set_vcd_vt(pNew->nVt, VCD_STRING);
		pNew->pString = pStr;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}
}*PEXBASECELLDATA,EXBASECELLDATA;


class QChMapsGridBase : public QTableWidget
{
	Q_OBJECT

public:
	QChMapsGridBase(QWidget* pparent);
	virtual ~QChMapsGridBase();

	void SetEditable(BOOL bEditable = TRUE)       { m_bEditable = bEditable;          }
	BOOL IsEditable() const                       { return m_bEditable;               }

	BOOL SetRowCount(int nRows = 10, BOOL bResetScrollBars=TRUE);
	QGV_ITEM* GetCell(int nRow, int nCol) const;

	virtual long GetDatasCount();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void InitGridTitle(const CString *pStrTitles, const int *pnWidth, int nCols);
	virtual void AfterShowDatas(long nBeginRow, BOOL bResetScrollBars);

	virtual void Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString);
	virtual void Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);

	//编辑处理函数
	static void EndEditCell_String (int nRow, int nCol,QGV_ITEM *pCell, QChMapsGridBase *pGrid);

protected:
	virtual void ClearSelect();
	//显示功能
	virtual void InitGridTitle() = 0;
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE) = 0;

	void FreeExBaseCellData(long nRow, long nCol);
	void FreeListVCellData();//	{	m_listVCellData.DeleteAll();	}

protected:
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

	CExBaseObject *m_pCurrData;
	CExBaseList *m_pDatas;//表格所表示的Data对象

protected:
	CTLinkList <_ExBaseCellData> m_listVCellData;

private:
	BOOL m_bEditable;

protected slots:
	void slot_CellChanged(int nrow,int ncol);
	
};

#endif // QCHMAPSGRIDBASE_H
