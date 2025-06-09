#ifndef QZKFEATUREADDDIG_H
#define QZKFEATUREADDDIG_H

#include <QDialog>
#include <QStyleFactory>
#include "ui_QZKFeatureAddDig.h"
#include "../../Module/TestWinFrame/testwinbase.h"

class QZKFeatureAddDig : public QDialog
{
	Q_OBJECT

public:
	QZKFeatureAddDig(CString strLoadName,QWidget *parent = 0);
	~QZKFeatureAddDig();

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
	Ui::QZKFeatureAddDig ui;
};

#endif // QZKFEATUREADDDIG_H
