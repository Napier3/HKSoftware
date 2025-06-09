#ifndef IECCFGPRIMRATEGRID_H
#define IECCFGPRIMRATEGRID_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../Module/CommonCtrl_QT/QIecWidgetDelegate.h"

#define IECCFG_PRIMRATE_GRIDTYPE_PT            0
#define IECCFG_PRIMRATE_GRIDTYPE_CT            1

#define IECCFGPRIMRATE_GRID_COLS		3

class CIecCfgPrimRateGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	CIecCfgPrimRateGrid(long nGridType,QWidget *parent);
	virtual ~CIecCfgPrimRateGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual CDataType* FindDataType(const CString &strDataType);

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	static void EndEditCell_PrimrateDouble(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;
	double m_dMaxValue;
	double m_dMinValue;

private:
	long m_nGridType;

public slots:
	void slot_doubleClicked(int nRow,int nCol);	
};

#endif // IECCFGPRIMRATEGRID_H
