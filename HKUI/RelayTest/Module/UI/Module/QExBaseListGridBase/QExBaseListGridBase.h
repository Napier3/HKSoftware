#ifndef QCHMAPSGRIDBASE_H
#define QCHMAPSGRIDBASE_H

#include <QTableWidget>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QFont>
#include "../../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../../Module/DataMngr/DataType.h"

#include "QGridDefine.h"
#include "../ScrollCtrl/ScrollTableWidget.h"

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
		int *piValue;
	};

	CExBaseObject *pObj;
	CExBaseList *pExBaseList;
	GRID_CELL_EDIT_FUNC *pFunc;

	static _ExBaseCellData* CreateNew(long *pnValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
        _ExBaseCellData* pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		pNew->pnValue = pnValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(int *piValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		_ExBaseCellData* pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		pNew->piValue = piValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(DWORD *pdwValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
        _ExBaseCellData* pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		pNew->pdwValue = pdwValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(double *pdValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
        _ExBaseCellData* pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		pNew->pdValue = pdValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(float *pfValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
        _ExBaseCellData* pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		pNew->pfValue = pfValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(CString *pStr, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
        _ExBaseCellData* pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		pNew->pString = pStr;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}
}*PEXBASECELLDATA,EXBASECELLDATA;

class CExBaseListGridOptrInterface
{
public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol) = 0;
	virtual BOOL OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar);
	virtual void OnDataEditChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	virtual void OnScrollGridFinished();

};

#ifndef _PSX_QT_LINUX_
class QExBaseListGridBase : public QTableWidget
#else
class QExBaseListGridBase : public QScrollTableWidget
#endif
{
	Q_OBJECT//zhouhj 20210715 要使用信号、槽必须要加此

public:
	QExBaseListGridBase(QWidget* pparent);
	virtual ~QExBaseListGridBase();
	virtual void InitGrid()
	{
		InitGridTitle();
	}

	void SetEditable(BOOL bEditable = TRUE)       { m_bEditable = bEditable;          }
	BOOL IsEditable() const                       { return m_bEditable;               }
	void SetModified(BOOL bModified = TRUE)       { m_bModified = bModified;          }

        virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE)
        {
#ifdef _PSX_IDE_QT_
        (void)pData;
#endif
            SetModified(bModified);
        }
	virtual long GetAdjustBeginCol()	{	return m_nAdjustBeginCol;	}
	virtual void SetAdjustBeginCol(long nAdjustBeginCol=1)	{	m_nAdjustBeginCol = nAdjustBeginCol;	}

	void SetItemBkColour(int nRow, int nCol, int , int g, int b);
	void SetItemFgColour(int nRow, int nCol, int , int g, int b);
	void SetItemBkColour(int nRow, int nCol, QColor cr);
	void SetItemFgColour(int nRow, int nCol, QColor cr);
	void SetItemEnable(int nRow, int nCol,BOOL bEnable);//设置当前单元格的使能状态
	void SetItemEditable(int nRow, int nCol,BOOL bEditable);//设置当前单元格的可编辑

	void SetDefaultRowHeight(int nRowHeight);//设置所有列的默认行高
	BOOL AutoSizeColumn(int nCol, BOOL bResetScrollBars=TRUE);

	virtual void SelectRow(int nRow)  //默认从1开始
	{  
		if (nRow<=0)
		{
			return;
		}

		selectRow(nRow-1);  
	};

	virtual void SelectRow(CExBaseObject *pCurrSelData);
	void SetTableFont(const QFont &oFont);//设置整个表的字体(包括表头)
	CExBaseList* GetDatas(){return m_pDatas;}
	BOOL SetRowCount(int nRows = 10, BOOL bResetScrollBars=TRUE);
	QGV_ITEM* GetCell(int nRow, int nCol) const;
	int GetRowIndex(QGV_ITEM *pItem);

	QGV_ITEM* AddItem(int nRow, int nCol, const CString &strText, BOOL &bHasSetItem, QColor oTextColor = Qt::black);

	virtual CExBaseObject* GetCurrSelData(long nStateForCol=0);
	CExBaseObject* GetData(long nRow, long nCol);
	QGV_ITEM* GetCurrSelItem();
	long GetCurrSelDatas(CExBaseList &listDatas, long nStateForCol=0);

	virtual BOOL UpdateData(CExBaseObject *pData);
	virtual void InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual long DeleteDataRow(CExBaseObject *pData, BOOL bDeleteData=TRUE);
	CString GetHeaderTextFromCol(int nCol);
	virtual void AdjustAllCols(BOOL bResetScrollBars = TRUE);

	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
	virtual void AttachDataViewOptrInterface(CExBaseListGridOptrInterface *pInterface)	{	m_pDataViewOptrInterface = pInterface;	}

	virtual long GetDatasCount();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void UpdateDatas();
	virtual void InsertDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void InitGridTitle(const CString *pStrTitles, const int *pnWidth, int nCols);
	virtual void AfterShowDatas(long nBeginRow, BOOL bResetScrollBars);

	virtual void Show_Index(CExBaseObject *pData, const int& nRow, const int& nCol);

	virtual void Show_ItemString(const int& nRow, const int& nCol, CString *pString);
	virtual void Show_ItemString(const int& nRow, const int& nCol, const CString &strText);

	virtual void Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString);
	virtual void Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strString);
	virtual void Update_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString);//20220605 zhouhj 更新表格中数据值,如果当前表格不存在,则创建,如果存在,则直接更新表格中内容,提高效率
	virtual void Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);
	//数据类型
//	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strText, PEXBASECELLDATA pVCellData);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Index(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrIndex, GRID_CELL_EDIT_FUNC pFunc=NULL);//20230215 传递的是m_strIndex

	virtual void  Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bUnitConversion=TRUE);
	virtual void  Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, double *pfValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bUnitConversion=TRUE);
	virtual void  Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bUnitConversion=TRUE);
	virtual void  Show_Long(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnValue, BOOL bCanEdit = TRUE, const CString &strUnit=_T(""), GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_Int(CExBaseObject *pData, const int& nRow, const int& nCol, int *pnValue, BOOL bCanEdit = TRUE, const CString &strUnit=_T(""), GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, long *nCheck, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bEnable=TRUE);
	virtual void  Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bEnable=TRUE);
//	static void EndEditCell_Check (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	virtual void  Show_Hex(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pdwValue, int iMaxLen, BOOL bCanEdit = TRUE, BOOL bSetColor=TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL);
	static void EndEditCell_Hex (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	//编辑处理函数
	static void EndEditCell_String(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_DoubleString(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_Value(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_DataType_Val(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	//20240708 huangliang
	virtual QGV_ITEM * NewGVItem(const CString &sText, QColor oTextColor = Qt::black);// { return new QGV_ITEM(sText); }
	virtual void SetItemText(QGV_ITEM *pItem, const QString &strText);	//更新值	
        virtual BOOL IsAttachSettingItem(QGV_ITEM *pCell)
        {
#ifdef _PSX_IDE_QT_
        (void)pCell;
#endif
            return FALSE;
        }//当前单元格是否关联了定值

protected:
	BOOL m_bHasConnectAll_SigSlot;
	long m_nAdjustBeginCol;
	virtual void ClearSelect();
	virtual void DisConnectAll_SigSlot();
	virtual void ConnectAll_SigSlot();

	long GetDataRow(CExBaseObject *pData, long nCol=0);
	virtual long GetDataRowEx(CExBaseObject *pData, long nFromRow, long nCol);
	virtual BOOL ChangeRowPosition(int nRow1, int nRow2);

	virtual void MoveUp();
	virtual void MoveDown();

	BOOL DeleteRow(int nRow);
	LPARAM GetItemData(int nRow, int nCol) const;
	int GetRowCount() const;
	int GetColCount() const;
	//显示功能
	virtual void InitGridTitle() = 0;
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE) = 0;

	void FreeExBaseCellData(QGV_ITEM *pItem);
	void FreeExBaseCellData(long nRow, long nCol);
	void FreeListVCellData();//	{	m_listVCellData.DeleteAll();	}
        virtual CDataType* FindDataType(const CString &strDataType)
        {
#ifdef _PSX_IDE_QT_
        (void)strDataType;
#endif
            ASSERT (FALSE);
            return NULL;
        }
	virtual void CreateGridMenu();//创建表格选中后显示菜单

	virtual void focusOutEvent(QFocusEvent *event);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	virtual void DisableSystemMenu(); //禁用系统菜单,需要挂载在Grid的focusOutEvent事件中
	virtual void DisableSystemMenu(QObject *obj, QEvent *event); //禁用系统菜单,需要挂载在Grid的eventFilter中
protected:
	PEXBASECELLDATA CreateExBaseCellData(unsigned long lParam, long *pnValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = (PEXBASECELLDATA)lParam;
		
		if (p == NULL)
		{
			p = _ExBaseCellData::CreateNew(pnValue, pObj, pExBaseList, pFunc);
			m_listVCellData.AddTail(p);
		}
		else
		{
			p->pnValue = pnValue;
			p->pObj = pObj;
			p->pExBaseList = pExBaseList;
			p->pFunc = pFunc;
		}

		return p;
	}

	PEXBASECELLDATA CreateExBaseCellData(unsigned long lParam, int *pnValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = (PEXBASECELLDATA)lParam;

		if (p == NULL)
		{
			p = _ExBaseCellData::CreateNew(pnValue, pObj, pExBaseList, pFunc);
			m_listVCellData.AddTail(p);
		}
		else
		{
			p->piValue = pnValue;
			p->pObj = pObj;
			p->pExBaseList = pExBaseList;
			p->pFunc = pFunc;
		}

		return p;
	}

	PEXBASECELLDATA CreateExBaseCellData(unsigned long lParam, DWORD *pnValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = (PEXBASECELLDATA)lParam;

		if (p == NULL)
	{
			p = _ExBaseCellData::CreateNew(pnValue, pObj, pExBaseList, pFunc);
			m_listVCellData.AddTail(p);
		}
		else
		{
			p->pdwValue = pnValue;
			p->pObj = pObj;
			p->pExBaseList = pExBaseList;
			p->pFunc = pFunc;
		}

		return p;
	}

	PEXBASECELLDATA CreateExBaseCellData(unsigned long lParam, double *pdValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = (PEXBASECELLDATA)lParam;

		if (p == NULL)
	{
			p = _ExBaseCellData::CreateNew(pdValue, pObj, pExBaseList, pFunc);
			m_listVCellData.AddTail(p);
		}
		else
		{
			p->pdValue = pdValue;
			p->pObj = pObj;
			p->pExBaseList = pExBaseList;
			p->pFunc = pFunc;
		}

		return p;
	}

	PEXBASECELLDATA CreateExBaseCellData(unsigned long lParam, float *pfValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = (PEXBASECELLDATA)lParam;

		if (p == NULL)
	{
			p = _ExBaseCellData::CreateNew(pfValue, pObj, pExBaseList, pFunc);
			m_listVCellData.AddTail(p);
		}
		else
		{
			p->pfValue = pfValue;
			p->pObj = pObj;
			p->pExBaseList = pExBaseList;
			p->pFunc = pFunc;
		}

		return p;
	}

	PEXBASECELLDATA CreateExBaseCellData(unsigned long lParam, CString *pStr, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA p = (PEXBASECELLDATA)lParam;

		if (p == NULL)
		{
			p = _ExBaseCellData::CreateNew(pStr, pObj, pExBaseList, pFunc);
			m_listVCellData.AddTail(p);
		}
		else
		{
			p->pString = pStr;
			p->pObj = pObj;
			p->pExBaseList = pExBaseList;
			p->pFunc = pFunc;
		}

		return p;
	}

	CExBaseObject *m_pCurrData;
	CExBaseList *m_pDatas;//表格所表示的Data对象

protected:
	void setRowColor(int nRow, QColor color);

	CExBaseListGridOptrInterface *m_pDataViewOptrInterface;
	CTLinkList <_ExBaseCellData> m_listVCellData;

private:
	BOOL m_bEditable;
	BOOL m_bModified;

protected slots:
	void slot_CellChanged(int nrow,int ncol);
//	void slot_cellClicked(int nrow,int ncol);
	virtual void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	virtual void slot_GridShowMenu(QPoint pos);//用于显示菜单
	virtual void slot_ScrollGridFinished();
	virtual void slot_cellDoubleClicked(int row, int column);
};

#endif // QCHMAPSGRIDBASE_H
