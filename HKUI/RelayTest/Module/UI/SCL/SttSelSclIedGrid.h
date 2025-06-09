#ifndef STTSELSCLIEDGRID_H
#define STTSELSCLIEDGRID_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

#define STTSELSCLIED_GRID_COLS		5

class CSttSelSclIedGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	CSttSelSclIedGrid(QWidget *parent);
	virtual ~CSttSelSclIedGrid();
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateSelectState();
	static void EndEditCell_SclIedSel(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

private:
	QExBaseListCheckBoxDelegate *m_pSelectSclIedDelegate;
};

#endif // STTSELSCLIEDGRID_H
