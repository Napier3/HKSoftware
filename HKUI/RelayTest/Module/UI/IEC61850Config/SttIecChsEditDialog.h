#ifndef STTIECCHSEDITDIALOG_H
#define STTIECCHSEDITDIALOG_H

#include <QDialog>
#include <QApplication>
#include "SttIecChsEditWidget.h"

class QSttIecChsEditDialog : public QDialog
{
	Q_OBJECT

public:
	QSttIecChsEditDialog(int nChsType,QWidget *parent= NULL);
	~QSttIecChsEditDialog();
	void InitData(CIecCfgChsBase *pIecCfgChs);

private:
	void InitUI();
	int m_nChsType;
	QSttIecChsEditWidget *m_pIecChsEditWidget;

public slots:
	void slot_OKClicked();
};

#endif // STTIECCHSEDITDIALOG_H
