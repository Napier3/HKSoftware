#pragma once
#ifndef IECCFGGOOSEINDATAGRID_H
#define IECCFGGOOSEINDATAGRID_H

#include "..\UI\IEC61850Config\Grid\IecCfgGinDataGrid.h"
#include "..\..\..\Module\XLanguage\QT\XLanguageAPI_QT.h"
#include <QWidget>

#define IECCFGGINDATA_GRID_COLS		14

class CIecCfgGooseDataGrid : public CIecCfgGinDataGrid
{
	 Q_OBJECT
public:
	CIecCfgGooseDataGrid(QWidget* pparent = NULL);
	virtual ~CIecCfgGooseDataGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);//goosein控制块表格选择行改变，响应事件

signals:
	void sig_Update_ChDatas(CExBaseList *pCB_Data);

protected:
	QExBaseListCheckBoxDelegate *pCtrlBlockSelectDelegate;
	QExBaseListComBoxDelegBase *m_pFiberSelected_DelegBase;
	QExBaseListCheckBoxDelegate *m_pNdsComCheckDelegate;
};

#endif // IECCFGGINDATAGRID_H
