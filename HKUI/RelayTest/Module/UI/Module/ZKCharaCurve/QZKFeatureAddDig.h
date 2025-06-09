#ifndef QZKFEATUREADDDIG_H
#define QZKFEATUREADDDIG_H

#include <QDialog>
#include <QStyleFactory>
#include "ui_QZKFeatureAddDig.h"
#include "../../../../../Module/OSInterface/OSInterface.h"
#include "../../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include "../../../../../AutoTest/Module/Characteristic/CharacteristicLib.h"

class QZKFeatureAddDig : public QDialog
{
	Q_OBJECT

public:
	QZKFeatureAddDig(CString strLoadName,QWidget *parent = 0);
	~QZKFeatureAddDig();

	void Init();
	void InitConnect();
         void InitLanguage();
	void RecursionShowObj(CExBaseList *pList,QTreeWidgetItem *pTreeItem);
	CCharacteristic* RecursionFindObj(CExBaseList *pList,CString strName);

	CCharacteristic* GetSelectedChar();//获取当前选择的曲线
signals:
//	void sig_clickOK(CCharacteristic *pObj);

public slots:
	void slot_PbnOkClicked();

	void slot_PbnCancelClicked();
public:
	CCharacteristicLib m_oLib;
private:
	Ui::QZKFeatureAddDig ui;
};

#endif // QZKFEATUREADDDIG_H
