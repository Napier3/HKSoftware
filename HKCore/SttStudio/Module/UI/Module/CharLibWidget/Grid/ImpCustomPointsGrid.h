#ifndef QIMPCUSTOMPOINTSGRID_H
#define QIMPCUSTOMPOINTSGRID_H

#include <QObject>
#include "../../QExBaseListGridBase/QExBaseListGridBase.h"

#define IMPCUSTOMPOINTS_GRID_COLS	  	5

class QImpCustomPointsGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	QImpCustomPointsGrid(QWidget *parent);
	virtual ~QImpCustomPointsGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:

signals:

public slots:
};

#endif // QIMPCUSTOMPOINTSGRID_H
