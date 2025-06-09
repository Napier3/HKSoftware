#ifndef QZKFEATUREADDDIG_H
#define QZKFEATUREADDDIG_H

#include <QDialog>
#include <QStyleFactory>
#include "ui_QCIFeatureAddDig.h"
#include "../../Module/TestWinFrame/testwinbase.h"

class QCIFeatureAddDig : public QDialog
{
	Q_OBJECT

public:
	QCIFeatureAddDig(QWidget *parent = 0);
	~QCIFeatureAddDig();

	void Init();
        void InitLanguage();
	void InitConnect();

	void RecursionShowObj(CExBaseList *pList,QTreeWidgetItem *pTreeItem);
	CCharacteristic* RecursionFindObj(CExBaseList *pList,CString strName);

signals:
	void sig_clickOK(CCharacteristic *pObj);

public slots:
	void slot_PbnOkClicked();

	void slot_PbnCancelClicked();
public:
	CCharacteristicLib m_oLib;
private:
	Ui::QCIFeatureAddDig ui;
};

#endif // QZKFEATUREADDDIG_H
