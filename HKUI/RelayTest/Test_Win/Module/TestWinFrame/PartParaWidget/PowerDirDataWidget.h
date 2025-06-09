#ifndef POWERDIRDATAWIDGET_H
#define POWERDIRDATAWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "../testwinbase.h"
#include "../../../../Module/SttTest/Common/tmt_test_mngr.h"
#include "../../../../Module/SttTest/Common/Gradient/tmt_power_direction_test.h"
#include "../../Module/TestWinFrame/testwinbase.h"


class PowerDirDataWidget : public QWidget,public ParaSetWidgetInterface
{
	Q_OBJECT

public:
	PowerDirDataWidget(QWidget *parent);
	~PowerDirDataWidget();

	virtual void InitUI();
	virtual void setData(PTMT_PARAS_HEAD pCurr);
	virtual void InitData();

	virtual void stopInit();
	virtual void startInit();
signals:
	void sig_TestPhaseChanged();
	void sig_FaultPhaseChanged();
	void updateData();

protected slots:
	void slot_cmb_TestPhaseCurrentIndexChanged(int);
	void slot_cmb_FaultPhaseCurrentIndexChanged(int);

	void slot_SCVoltage_editingFinished();
	void slot_SCCurrent_editingFinished();

	void slot_Start_editingFinished();
	void slot_Stop_editingFinished();
	void slot_Step_editingFinished();
	void slot_StepTime_editingFinished();
public:
	tmt_PowerDirectionTest *m_PowerDirTest;
	tmt_PowerDirectionParasEx *m_PowerDirParas;
	tmt_PowerDirectionResults *m_PowerDirResults;
private:
	void SetFaultPhaseIndex(int nIndex);//nIndex为 测试相 值
	void GetFaultPhaseNumber(int nIndex);//nIndex为当前选中 故障相 的序号
private:

	QHBoxLayout *m_MainLayout;
	QGridLayout *m_leftLayout;
	QGridLayout *m_rightLayout;

	QSpacerItem *pSpacer1;
	QSpacerItem *pSpacer2;
	QSpacerItem *pSpacer3;

	QComboBox *m_CmbTestPhase;//测试相
	QLabel *label_TestPhase;
	QStringList strListTestPhase;

	QComboBox *m_CmbFaultPhase;//故障相
	QLabel *label_FaultPhase;
	QStringList strListFaultPhase;

	QLineEdit *m_LineSCVoltage;//故障电压
	QLabel *label_SCVoltage;

	QLineEdit *m_LineSCCurrent;//故障电流
	QLabel *label_SCCurrent;

	QLineEdit *m_LineStart;//变化始值
	QLabel *label_Start;

	QLineEdit *m_LineStop;//变化终值
	QLabel *label_Stop;

	QLineEdit *m_LineStep;//变化步长
	QLabel *label_Step;

	QLineEdit *m_LineStepTime;//故障时间
	QLabel *label_StepTime;

	QLineEdit *m_LineFreq;//频率
	QLabel *label_Freq;
	
};

#endif // POWERDIRDATAWIDGET_H
