#ifndef QAINDATAMAPGRID_H
#define QAINDATAMAPGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../../Module/DataMngr/DataGroup.h"

class QAinDataMapGrid: public QExBaseListGridBase
{
	Q_OBJECT

public:
	QAinDataMapGrid(QWidget* pParent);
	virtual ~QAinDataMapGrid();

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};

#endif //QAinDataMapGrid_H