#ifndef REPORTSETDIALOG_H
#define REPORTSETDIALOG_H

#include <QDialog>
#include "ui_reportsetdialog.h"
#include "reportSetParaDefine.h"

class ReportSetDialog : public QDialog
{
	Q_OBJECT

public:
	ReportSetDialog(reportSetPara para,QWidget *parent = 0);
	~ReportSetDialog();
public:
	void init();
	void updateParentItem(QTreeWidgetItem* item);

private slots:
	void treeItemChanged(QTreeWidgetItem* item,int column);
	void slot_pbn_OkClicked();
	void slot_pbn_CancleClicked();
signals:
	void sig_ReportSetParaOkClicked(reportSetPara &);

private:
	Ui::ReportSetDialog ui;
	QTreeWidgetItem* group1;
	QTreeWidgetItem* subItem11;
	QTreeWidgetItem* subItem12;
	QTreeWidgetItem* subItem13;
	QTreeWidgetItem* subItem14;
	QTreeWidgetItem* group2;
	QTreeWidgetItem* subItem21;
	QTreeWidgetItem* subItem22;
	QTreeWidgetItem* subItem23;
	QTreeWidgetItem* subItem24;
	QTreeWidgetItem* group3;
	QTreeWidgetItem* subItem31;
	QTreeWidgetItem* subItem32;
	reportSetPara m_reportsetpara;
};

#endif // REPORTSETDIALOG_H
