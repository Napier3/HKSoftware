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
#include <QGroupBox>
#include <QVBoxLayout>

#include "..\..\Module\SttTest\Common\Impedance\tmt_impedance_test.h"
#include "..\..\Module\SttCmd\SttCmdDefineGlobal.h"
#include "..\..\..\..\..\SttStudio\Test_Win\Module\CommonMethod\commonMethod.h"
//#include "../Module/CommonMethod/commonMethod.h"
#include "..\Module\TestWinFrame\SysParasSetDlg\QFloatLineEdit.h"

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
	bool SetParameter();
	void InitParameter();
	void UpdateDataForDlg();
	void UpdateBinEnable();
	int    CheckParameter();
	void GetInput_OutputState();
	void SetModifyPara();
	void SetHideGroupBoxIn(); //dingxiaoya 20231120 隐藏开入操作

signals:
	void sig_CheckPara(int);

public:
	int  m_nIsOK;
	int  m_nInitFlag;
	tmt_ImpedanceParas *m_pImpedanceParasEx;//dingxiaoya 20231120 传递开出参数
	QFloatLineEdit* outPutKeepTime;
	QFloatLineEdit* outPutDelayTime;
public slots:
	void slot_btnClicked();
	void  slot_btnOKClicked();
	void  slot_btnCancelClicked();
	void slot_cmb_CurrentChanged(int nIndex);
	void slot_fanZhuanTimeChanged();
	void slot_fanZhuanStoreTimeChanged();

private:private:
    QGridLayout * layoutIn;
   // QGridLayout layout1;
	QGridLayout *mainLayout;
	QHBoxLayout  * pokLayout;

	QGridLayout * layoutOut;
	QVBoxLayout *m_pVBoxLayout;

    QWidget *widget;
    int  n;
	int  row;

	QPushButton * pOKBtn ;
	QPushButton * pCancelBtn;
	QFloatLineEdit * fanZhuanTime;
	QFloatLineEdit * fanZhuanStoreTime;
	tmt_ImpedanceParas *m_pImpedanceParas;
	tmt_ImpedanceParas  m_ImpedanceParas;

	QList <QLabel *> listLabel;
	QList <QComboBox *> listComboBox;
	QGroupBox *groupBoxIn;
	QGroupBox *groupBoxOut;
};

#endif // COMMONPARAMETER_H
