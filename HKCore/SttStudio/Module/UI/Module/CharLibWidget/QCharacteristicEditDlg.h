#ifndef QCHARACTERISTICEDITDLG_H
#define QCHARACTERISTICEDITDLG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"

class QCharacteristicEditDlg : public QDialog
{
	Q_OBJECT

public:
	QCharacteristicEditDlg(CCharacteristic *pCharacteristic,QWidget *parent);
	virtual ~QCharacteristicEditDlg();
	void InitUI();


protected:
	void InitDatas();
	void IntConnects();
	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pOkCancelHLayout;
	QPushButton *m_pOk_Button;
	QPushButton *m_pCancel_Button;

private:
	CCharacteristic *m_pSrcCharacteristic;
	CCharacteristic *m_pEditCharacteristic;

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	
};

#endif // QCHARACTERISTICEDITDLG_H
