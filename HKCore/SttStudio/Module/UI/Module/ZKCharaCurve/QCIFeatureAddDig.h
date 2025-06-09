#ifndef QCIFEATUREADDDIG_H
#define QCIFEATUREADDDIG_H

#include <QDialog>
#include <QStyleFactory>
#include "ui_QCIFeatureAddDig.h"
#include "../../../../../Module/OSInterface/OSInterface.h"
#include "../../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include "../../../../../AutoTest/Module/Characteristic/CharacteristicLib.h"

class QCIFeatureAddDig : public QDialog
{
	Q_OBJECT

public:
	QCIFeatureAddDig(const CString &strCharLibPath,QWidget *parent = 0);
	~QCIFeatureAddDig();

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
	Ui::QCIFeatureAddDig ui;
};

#endif // QCIFEATUREADDDIG_H
