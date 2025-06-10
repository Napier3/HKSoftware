#ifndef QGOUTDATAGRID_H
#define QGOUTDATAGRID_H

#include "../../IEC61850Config/Grid/IecCfgDataGridBase.h"


#define GGOUTDATA_GRID_COLS		16

class QTerminalGoutDataGrid : public CIecCfgDataGridBase
{
	Q_OBJECT
public:
	QTerminalGoutDataGrid(QWidget* pparent);
	virtual ~QTerminalGoutDataGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	virtual BOOL IsCfgData(CExBaseObject *pIecCfgDataBase);
	static void EndEditCell_CheckChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

public slots:
	void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void slot_UpdateCheckState(CIecCfgDataBase *pIecCfgDataBase,int nRow);


signals:
	void sig_UpdateChansdata(CIecCfgChsBase *);
	void sig_UpdateCheckState(CIecCfgDataBase *pIecCfgDataBase,int nRow);

public:
	QIecNumberEditDelegate *m_pSrcMacAddrDelegate;
	QIecNumberEditDelegate *m_pVlanIDDelegate;
	QExBaseListCheckBoxDelegate *m_pTestCheckDelegate;
	QExBaseListCheckBoxDelegate *m_pNdsComCheckDelegate;
	long m_nFirstIndex;
};

#endif 
