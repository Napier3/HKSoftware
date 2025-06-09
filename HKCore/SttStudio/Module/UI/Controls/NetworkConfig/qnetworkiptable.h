#ifndef _qnetworkip_table_H
#define _qnetworkip_table_H

#include <QTableWidget>
#include <QAction>
#include <QHeaderView>

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"


class QNetworkIpTable : public QExBaseListGridBase
{
	Q_OBJECT

public:
	QNetworkIpTable(QWidget *parent = 0);
	~QNetworkIpTable();
	
	void InitGrid();
	void InitGridTitle();
	void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);


public:
	bool m_bRunning;
	
};

#endif // _qnetworkip_table_H
