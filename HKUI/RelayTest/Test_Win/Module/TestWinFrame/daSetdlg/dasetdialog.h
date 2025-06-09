#ifndef DASETDIALOG_H
#define DASETDIALOG_H

#include <QDialog>
#include "ui_dasetdialog.h"
#include "../../Module/SttTest/Common/tmt_system_config.h"
#include "qvalidator.h"

class DASetDialog : public QDialog
{
	Q_OBJECT

public:
	DASetDialog(QWidget *parent = 0);
	~DASetDialog();

	void initUI();
	void initConnections();
	void Initlanguage();
	void setData(STT_SystemParas* pSystemParas);

	QDoubleValidator* validatorVal;
	STT_SystemParas* m_pSystemParas;
//	int m_nFiber;
	int m_nIPowerMode;
	BOOL m_bChanged;

signals:
	void sig_DASetClicked(bool);

public slots:
	void slot_DASetClicked();
	void slot_changeISet(int nISet);
	void slot_lne_IChanged();
	void slot_CancelClicked();
//	void slot_1588FiberSet(int);
//	void slot_lne_LowSignalChanged();
	void slot_lne_StabTimeChanged();
	void slot_lne_VNomChanged();
	void slot_lne_INomChanged();
	void slot_lne_FNomChanged();
private:
	Ui::DialogDA ui;
};

#endif // DASETDIALOG_H
