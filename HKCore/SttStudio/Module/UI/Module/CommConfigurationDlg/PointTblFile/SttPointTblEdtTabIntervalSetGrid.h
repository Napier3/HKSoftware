#ifndef SttCPointTblEdtTabIntervalSetGrid_H
#define SttCPointTblEdtTabIntervalSetGrid_H
#include <QApplication>
#include <QObject>
#include "../../QExBaseListGridBase/QExBaseListGridBase.h"

#define STTCPOINTTBLEDTTABINTERVALSETGRID_COLS		9


class SttCPointTblEdtTabIntervalSetGrid  : public QExBaseListGridBase
{
	Q_OBJECT

public:
	SttCPointTblEdtTabIntervalSetGrid (QWidget* pparent);
	virtual ~SttCPointTblEdtTabIntervalSetGrid ();
	void SetColumns(QStringList* strIdsList, QStringList* strNmsList);
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void SelectRow(int nRow);

	static void EndSttCommCfgEditCell_String(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndSttCommCfgEditCell_AddrValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;

	//QStringList *m_pColsList;
	QStringList m_oColIDsList;
	QStringList m_oColNamesList;


signals:
	void sig_ChangedIntervSetDevAddr();
	void sig_ChangedAdress(int nRow,int nCol,QString strValue);
	void sig_ApplyAll(bool bflag);//间隔参数是否同步

};

#endif // SttCPointTblEdtTabIntervalSetGrid 
