#ifndef  QSTTFASTATESEQUENCEGRID1
#define  QSTTFASTATESEQUENCEGRID1
#include <QWidget>
#include <QTableWidget>
#include "../../../SttTestCntrCmdDefine.h"

#include "../../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../Module/DataMngr/DataGroup.h"


#define  QSTTFASTATEGRIDCOL 8

class QSttFAStateSequenceGroupGrid:public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttFAStateSequenceGroupGrid(QWidget *parent = NULL);
	virtual ~QSttFAStateSequenceGroupGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	void ShowChildren(CDataGroup *pDataGroup, int& nRow, BOOL bInsertRow = TRUE);
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *);
	static void EndEditCell_String (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	void StartInit();
	static double CalExpression(CString strExpression);
};

#endif