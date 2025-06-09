#ifndef ScanLanTesterGRID_H
#define ScanLanTesterGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListFloatEditDelegBase.h"
#include <QObject>

#define ScanLanTester_GRID_COLS		      3

class CScanLanTesterGrid : public QExBaseListGridBase
{
	Q_OBJECT//zhouhj 20210715 要使用信号、槽必须要加此
public:
	CScanLanTesterGrid(QWidget* pparent);
	virtual ~CScanLanTesterGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	//编辑处理函数
	static void EndEditCell_WeakRateSetString (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

private:

protected slots:
};

#endif // ScanLanTesterGRID_H
