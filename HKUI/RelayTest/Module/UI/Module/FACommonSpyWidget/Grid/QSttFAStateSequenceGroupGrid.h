#ifndef  QSTTFASTATESEQUENCEGRID1
#define  QSTTFASTATESEQUENCEGRID1
#include <QWidget>
#include <QTableWidget>
#include "../../../SttTestCntrCmdDefine.h"

#include "../../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../../../Module/DataMngr/DataGroup.h"


#define  QSTTFASTATEGRIDCOL 6

class QSttFAStateSequenceGroupGrid:public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttFAStateSequenceGroupGrid(QWidget *parent = NULL);
	virtual ~QSttFAStateSequenceGroupGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	void ShowChildren(CDataGroup *pDataGroup, int& nRow, BOOL bInsertRow = TRUE);
	virtual void mousePressEvent(QMouseEvent *);

public slots:

	void slot_ItemClicked(QTableWidgetItem *item);
};


#endif