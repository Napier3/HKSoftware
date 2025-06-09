#ifndef QGINDATAGRID_H
#define QGINDATAGRID_H


#include "../../IEC61850Config/Grid/IecCfgDataGridBase.h"

#define GINDATA_GRID_COLS		14

class QTerminalGinDataGrid : public CIecCfgDataGridBase
{
	Q_OBJECT
public:
	QTerminalGinDataGrid(QWidget* pparent);
	virtual ~QTerminalGinDataGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	virtual BOOL IsCfgData(CExBaseObject *pIecCfgDataBase);
	static void EndEditCell_CheckChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 20211029 处理勾选改变

public slots:
	void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void slot_UpdateCheckState(CIecCfgDataBase *pIecCfgDataBase,int nRow);

signals:
	void sig_UpdateChansdata(CIecCfgChsBase *);

public:
	QExBaseListComBoxDelegBase *m_pTestCheckDelegate;
	QExBaseListCheckBoxDelegate *m_pNdsComCheckDelegate;
	QExBaseListCheckBoxDelegate *m_pNotGocbCheckDelegate;
	long m_nFirstIndex;

};

#endif // IECCFGGINDATAGRID_H
