#ifndef IECCFGSMVRATEGRID_H
#define IECCFGSMVRATEGRID_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"


#define IECCFGSMVRATE_GRID_COLS		2

class CIecCfgSmvRateGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	CIecCfgSmvRateGrid(QWidget* pparent);
	virtual ~CIecCfgSmvRateGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

public:
	//编辑处理函数
	BOOL m_bRunning;
	static void EndEditCell_RateValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);


protected:

public slots:
 	void slot_doubleClicked(int nRow,int nCol);
};

#endif // IECCFGSMVRATEGRID_H
