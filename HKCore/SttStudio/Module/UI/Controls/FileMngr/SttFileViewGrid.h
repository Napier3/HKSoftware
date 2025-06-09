#ifndef STTFILEVIEWGRID_H
#define STTFILEVIEWGRID_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"

class CSttFileViewGrid : public QExBaseListGridBase
{
public:
	CSttFileViewGrid(QWidget* pParent= NULL);
	virtual ~CSttFileViewGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;
};

#endif // STTFILEVIEWGRID_H
