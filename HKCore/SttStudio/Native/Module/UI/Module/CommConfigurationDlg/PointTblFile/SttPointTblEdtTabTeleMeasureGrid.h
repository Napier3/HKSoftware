#ifndef SttCPointTblEdtTabTeleMeasureGrid_H
#define SttCPointTblEdtTabTeleMeasureGrid_H

#include "../../QExBaseListGridBase/QExBaseListGridBase.h"
#include <QApplication> 
#define STTCPOINTTBLEDTTABTELEMEASUREGRID_COLS		4
 
//遥测对应的间隔1点表
class SttCPointTblEdtTabTeleMeasureGrid  : public QExBaseListGridBase
{
		Q_OBJECT
public:
	SttCPointTblEdtTabTeleMeasureGrid (QWidget* pparent);
	virtual ~SttCPointTblEdtTabTeleMeasureGrid ();

	static void EndEditTeleMeasure_IndexValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void SelectRow(int nRow);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;

signals:
	void sig_ChangedTeleMeasureIndex();
};

#endif // SttCPointTblEdtTabTeleMeasureGrid 
