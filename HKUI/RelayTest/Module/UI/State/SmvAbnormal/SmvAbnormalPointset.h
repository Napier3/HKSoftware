#ifndef ABNORMALPOINTSET_H
#define ABNORMALPOINTSET_H

#include <QDialog>
#include "ui_SmvAbnormalPointset.h"

#include <qtablewidget.h>
#include <QStringList>

class QSmvAbnormalPointSet : public QDialog
{
	Q_OBJECT

public:
	QSmvAbnormalPointSet(int flag,QList<bool> &validpoint,QWidget *parent = 0);
	~QSmvAbnormalPointSet();

signals:
	void sig_validPoint(QList<bool> &pointlist);

protected slots:
	void slot_pbn_AllSelsectClicked();
	void slot_pbn_SelectInvertClicked();
	void slot_pbn_OkClicked();
	void slot_pbn_CancleClicked();

private:
	Ui::SmvAbnormalPointSet ui;
	void init();
	void initConnect();
     void InitLanguage();
	void initData();

	int headerFlag;
	QList<bool> abnomalPointEnabled;
};

#endif // ABNORMALPOINTSET_H
