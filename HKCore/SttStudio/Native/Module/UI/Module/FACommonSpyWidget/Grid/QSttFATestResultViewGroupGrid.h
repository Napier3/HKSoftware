#ifndef QSTTFASOEMESSAGEGROUPGRID_H
#define QSTTFASOEMESSAGEGROUPGRID_H
#include <QWidget>
#include <QTableWidget>
#include "../../QExBaseListGridBase/QExBaseListGridBase.h"

#define  QSTTFASOEGRIDCOL 3

class QSttFATestResultViewGroupGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:

	QSttFATestResultViewGroupGrid(QWidget *parent = NULL);
	virtual ~QSttFATestResultViewGroupGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
};

#endif