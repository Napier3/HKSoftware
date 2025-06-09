#ifndef _Stt_Aux_IP_SetGrid_H_
#define _Stt_Aux_IP_SetGrid_H_

#include <QTableWidget>
#include <QAction>
#include <QHeaderView>

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"


class QSttAuxIPSetGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttAuxIPSetGrid(QWidget *parent = 0);
	~QSttAuxIPSetGrid();
	
	void InitGrid();
	void InitGridTitle();
	void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);


public:
	bool m_bRunning;
	
};

#endif 
