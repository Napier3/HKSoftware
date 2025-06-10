#ifndef SttCPointTblEdtTabTeleParaCommGrid_H
#define SttCPointTblEdtTabTeleParaCommGrid_H
#include <QApplication> 
#include "../../QExBaseListGridBase/QExBaseListGridBase.h"

#define STTCPOINTTBLEDTTABTELEPARACOMMGRID_COLS		3

//其他参数对应的间隔1点表
class SttCPointTblEdtTabTeleParaCommGrid  : public QExBaseListGridBase
{
		Q_OBJECT
public:
	SttCPointTblEdtTabTeleParaCommGrid (QWidget* pparent);
	virtual ~SttCPointTblEdtTabTeleParaCommGrid ();

	static void EndSttCommCfgEditCell_IndexValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void SelectRow(int nRow);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;

signals:
	void sig_ChangedParaComIndex();

};

#endif // SttCPointTblEdtTabTeleParaCommGrid 
