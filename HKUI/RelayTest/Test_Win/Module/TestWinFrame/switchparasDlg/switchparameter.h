#ifndef COMMONPARAMETER_H
#define COMMONPARAMETER_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include "..\..\Module\SttTest\Common\Impedance\tmt_impedance_test.h"
#include "..\..\Module\SttCmd\SttCmdDefineGlobal.h"
#include "../Module/CommonMethod/commonMethod.h"

class SwitchParameter : public QDialog
{
	Q_OBJECT

public:
	SwitchParameter(tmt_ImpedanceParas *pImpedanceParas, QWidget *parent = 0);
	~SwitchParameter();

public:
	void initUI();
	void setData();
	void closeEvent(QCloseEvent *event);
	void SetParameter();
	void InitParameter();
	void UpdateDataForDlg();


public slots:
	void slot_btnClicked();
	void  slot_btnOKClicked();
	void  slot_btnCancelClicked();
	void slot_cmb_CurrentChanged(int nIndex);
	void slot_fanZhuanTimeChanged();
	void slot_fanZhuanStoreTimeChanged();

private:private:
    QGridLayout * layout;
   // QGridLayout layout1;
	QGridLayout *mainLayout;
	QHBoxLayout  * pokLayout;

    QWidget *widget;
    int  n;
	int  row;

	QPushButton * pOKBtn ;
	QPushButton * pCancelBtn;
	QLineEdit * fanZhuanTime;
	QLineEdit * fanZhuanStoreTime;
	tmt_ImpedanceParas *m_pImpedanceParas;
	tmt_ImpedanceParas  m_ImpedanceParas;

	QList <QLabel *> listLabel;
	QList <QComboBox *> listComboBox;
};

#endif // COMMONPARAMETER_H
