#ifndef SttCCommCfgPkgMonitorLeftGrid_H
#define SttCCommCfgPkgMonitorLeftGrid_H

#include "../../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../SttCmd/SttParas.h"

#define STTCCOMMCFGPKGMONITORLEFTGRID_COLS		3 

class SttCCommCfgPkgMonitorLeftGrid : public QExBaseListGridBase
{
public:
	SttCCommCfgPkgMonitorLeftGrid (QWidget* pparent);
	virtual ~SttCCommCfgPkgMonitorLeftGrid ();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void SelectRow(int nRow);
	//void ShowData(QString strTimer,QString strDir,QString strData,int nRow,BOOL bInsertRow=TRUE);
	void ShowData(CSttParas *pData, int nRow);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;
};

#endif // SttCCommCfgPkgMonitorLeftGrid_H 
