#ifndef SttCDevCommTeleMeasureGrid_H
#define SttCDevCommTeleMeasureGrid_H
#include <QApplication>
#include "../../QExBaseListGridBase/QExBaseListGridBase.h"

#define STTCDEVCOMMTELEMEASUREGRID_COLS		5

//遥测对应的 装置通讯表
class SttCDevCommTeleMeasureGrid : public QExBaseListGridBase
{
public:
	SttCDevCommTeleMeasureGrid (QWidget* pparent);
	virtual ~SttCDevCommTeleMeasureGrid ();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	static void EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	virtual void SelectRow(int nRow);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;
};

#endif // SttCDevCommTeleMeasureGrid
