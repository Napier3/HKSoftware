#ifndef STTFILETYPEMNGRGRID_H
#define STTFILETYPEMNGRGRID_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"

class CFileTypeMngrGrid : public QExBaseListGridBase
{
public:
	CFileTypeMngrGrid(QWidget* pParent= NULL);
	virtual ~CFileTypeMngrGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;

};

#endif // STTFILETYPEMNGRGRID_H
