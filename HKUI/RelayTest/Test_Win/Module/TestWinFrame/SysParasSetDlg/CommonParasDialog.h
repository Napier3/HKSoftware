#ifndef COMMONPARASDIALOG_H
#define COMMONPARASDIALOG_H

#include <QDialog> 
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "..\..\Module\SttTest\Common\Impedance\tmt_impedance_test.h"
#include "..\..\Module\SttCmd\SttCmdDefineGlobal.h"
#include "..\..\Module\TestWinFrame\SysParasSetDlg\QValueComboBox.h"
#include "..\..\Module\TestWinFrame\SysParasSetDlg\QFloatLineEdit.h"

class CommonParasDialog : public QDialog
{
	Q_OBJECT

public:
	CommonParasDialog(tmt_ImpedanceParas *pImpedanceParas,QWidget *parent);
	~CommonParasDialog();
	void initUI();
	void initData();
private:
	tmt_ImpedanceParas *m_pImpedanceParas;

signals:
	void sig_ClickOk();  //信号预留使用,供外部调用
private slots:
	void slot_ClickOk();
	void slot_ClickCancel();


public:
	QGridLayout *m_MainLayout;

	QFloatLineEdit *m_editFaultTime;                //故障时间裕度
	QFloatLineEdit *m_editPreFaultTime;                 //故障前时间
	QLabel *label_1;
	QLabel *label_2;

	QValueComboBox *m_CmbFaultTrigMode;        //故障触发方式
	QFloatLineEdit *m_editHour;                     //GPS触发时刻（时）
	QFloatLineEdit *m_editMinutes;                  //GPS触发时刻（分）
	QFloatLineEdit *m_editSeconds;                  //GPS触发时刻（秒）
	QLabel *label_3;
	QLabel *label_4;
	QLabel *label_5;
	QLabel *label_6;

	QValueComboBox *m_CmbK0CalMode;           //零序补偿系数表达方式
	QFloatLineEdit *m_editK0Amp;                   //零序补偿系数RE/RL
	QFloatLineEdit *m_editK0Angle;                 //零序补偿系数XE/XL
	QLabel *label_7;
	QLabel *label_8;
	QLabel *label_9;

	QFloatLineEdit *m_editIfh;                     //负荷电流
	QFloatLineEdit *m_editPowerAngle;              //负荷功角
	QLabel *label_10;
	QLabel *label_11;

	QFloatLineEdit *m_editRecloseTime;             //重合闸时间定值
	QFloatLineEdit *m_editAfterAcceTime;           //后加速时间定值
	QLabel *label_12;
	QLabel *label_13;

	QValueComboBox *m_CmbPTPoint;             //PT安装位置
	QValueComboBox *m_CmbCTPoint;             //CT正极性
	QValueComboBox *m_CmbCBSimulation;        //是否模拟断路器延时
	QFloatLineEdit *m_editCBTripTime;               //断路器跳闸延时
	QFloatLineEdit *m_editCBCloseTime;             //断路器合闸延时
	QLabel *label_14;
	QLabel *label_15;
	QLabel *label_16;
	QLabel *label_17;
	QLabel *label_18;

	QValueComboBox *m_CmbIPlusDC;             //是否叠加非周期分量
	QValueComboBox *m_CmbFaultIncMode;        //合闸角方式( 0-随机 1-定值)
	QFloatLineEdit *m_editFaultAngle;              //合闸角
	QFloatLineEdit *m_editFaultAng_0;              //合闸角的起始值
	QLabel *label_19;
	QLabel *label_20;
	QLabel *label_21;
	QLabel *label_22;

	QValueComboBox *m_CmbVzDefine;             //辅助电压Ux 输出方式
	QFloatLineEdit *m_editUxInput_Mag;           //同期电压幅值
	QFloatLineEdit *m_editUxInput_Ang;           //同期电压相位
	QFloatLineEdit *m_editUxHigh;           //有压测试值
	QFloatLineEdit *m_editUxLow;           //无压测试值
	
	QLabel *label_23;
	QLabel *label_24;
	QLabel *label_25;
	QLabel *label_26;
	QLabel *label_27;

	QPushButton *m_BtnOk;
	QPushButton *m_BtnCancel;


};

#endif // COMMONPARASDIALOG_H
