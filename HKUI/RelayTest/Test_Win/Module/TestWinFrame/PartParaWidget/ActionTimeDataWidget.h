#ifndef ACTIONTIMEDATAWIDGET_H
#define ACTIONTIMEDATAWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "../testwinbase.h"
#include "../../../../Module/SttTest/Common/tmt_test_mngr.h"
#include "../../../../Module/SttTest/Common/ActionTime/tmt_action_time_test.h"
#include "../../Module/TestWinFrame/testwinbase.h"

class ActionTimeDataWidget : public QWidget,public ParaSetWidgetInterface
{
	Q_OBJECT

public:
	ActionTimeDataWidget(QWidget *parent,bool bRefValueType);//电流反时限传false 其他传true  sf 20211012
	~ActionTimeDataWidget();

	virtual void InitUI();
	virtual void setData(PTMT_PARAS_HEAD pCurr);
	virtual void InitData();

	virtual void stopInit();
	virtual void startInit();
	int SetFaultData(int nData);
	void UpdateActTime();
	BOOL isFloat(char* pszExpr);

signals:
	void sig_FaultTypeChange();
	void sig_FaultCurChange();
	void sig_SettingFaultTimeChanged();  //2023.7.18 zhangyq

protected slots:
	void slot_FaultVolTypeCurrentIndexChanged(int nIndex);
	void slot_FaultTypeCurrentIndexChanged(int nIndex);

	void slot_PreFaultVol_editingFinished();
	void slot_PreFaultCur_editingFinished();
	void slot_PreFaultAngle_editingFinished();
	void slot_FaultVol_editingFinished();
	void slot_FaultCur_editingFinished();
	void slot_FaultAngle_editingFinished();
	void slot_SettingFaultTime_editingFinished();

public:
	tmt_CurrInverseTimeTest *m_ActionTimeTest;
	tmt_ActionTimeParasEx *m_ActionTimeParas;
	tmt_ActionTimeResults  *m_ActionTimeResults;

	QHBoxLayout *m_MainLayout;

	bool m_bRefValueType;
	float m_fvalue;	//截取故障电流*之前的数
private:
	QGroupBox *groupBoxBefore;

	QLineEdit *m_LinePreFaultVol;//电压
	QLabel *label_PreFaultVol;

	QLineEdit *m_LinePreFaultCur;//电流
	QLabel *label_PreFaultCur;

	QLineEdit *m_LinePreFaultAngle;//相位差
	QLabel *label_PreFaultAngle;

	QLineEdit *m_LineFreq;//频率
	QLabel *label_Freq;

	QGroupBox *groupBoxAfter;

	QLineEdit *m_LineFaultVol;//短路电压
	QLabel *label_FaultVol;
	QComboBox *m_CmbFaultVolType;
	QStringList strListFaultVol;

	QLineEdit *m_LineFaultCur;//电流
	QLabel *label_FaultCur;

	QComboBox *m_CmbFaultType;//故障类型
	QLabel *label_FaultVolType;
	QStringList strListFaultVolType;

// 	QLabel *label_RefValueType; //基准值类型
// 	QComboBox *m_CmbRefValueType;
// 	QStringList strListRefValueType;

	QLineEdit *m_LineFaultAngle;//相位差
	QLabel *label_FaultAngle;

	QLineEdit *m_LineSettingFaultTime;//动作时间定值
	QLabel *label_SettingFaultTime;

	QSpacerItem *pSpacer1;
	QSpacerItem *pSpacer2;
	QSpacerItem *pSpacer3;
	
};

#endif // ACTIONTIMEDATAWIDGET_H
