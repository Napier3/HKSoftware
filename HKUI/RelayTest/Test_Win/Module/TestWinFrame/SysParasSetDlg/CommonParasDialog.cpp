#include "CommonParasDialog.h"

CommonParasDialog::CommonParasDialog(tmt_ImpedanceParas *pImpedanceParas,QWidget *parent)
	: QDialog(parent)
{
	m_pImpedanceParas = pImpedanceParas;
	initUI();
	initData();
	connect(m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_ClickOk()));
	connect(m_BtnCancel,SIGNAL(clicked()),this,SLOT(slot_ClickCancel()));
}

CommonParasDialog::~CommonParasDialog()
{

}

void CommonParasDialog::initData()
{
	ASSERT(m_pImpedanceParas);

	m_editFaultTime->setText(QString::number(m_pImpedanceParas->m_fFaultTime, 'f', 3));
	m_editPreFaultTime->setText(QString::number(m_pImpedanceParas->m_fPreFaultTime, 'f', 3));
	m_CmbFaultTrigMode->SetIndex(&m_pImpedanceParas->m_nFaultTrigMode);
	m_editHour->setText(QString::number(m_pImpedanceParas->m_tGps.nHour, 'f', 0));
	m_editMinutes->setText(QString::number(m_pImpedanceParas->m_tGps.nMinutes, 'f', 0));
	m_editSeconds->setText(QString::number(m_pImpedanceParas->m_tGps.nSeconds, 'f', 0));
	m_CmbK0CalMode->SetIndex(&m_pImpedanceParas->m_nK0CalMode);
	m_editK0Amp->setText(QString::number(m_pImpedanceParas->m_fK0Amp, 'f', 3));
	m_editK0Angle->setText(QString::number(m_pImpedanceParas->m_fK0Angle, 'f', 3));
	m_editIfh->setText(QString::number(m_pImpedanceParas->m_fIfh, 'f', 3));
	m_editPowerAngle->setText(QString::number(m_pImpedanceParas->m_fPowerAngle, 'f', 3));
	m_editRecloseTime->setText(QString::number(m_pImpedanceParas->m_fRecloseTime, 'f', 3));
	m_editAfterAcceTime->setText(QString::number(m_pImpedanceParas->m_fAfterAcceTime, 'f', 3));
	m_CmbPTPoint->SetIndex((int*)(&m_pImpedanceParas->m_nPTPoint));
	m_CmbCTPoint->SetIndex(&m_pImpedanceParas->m_nCTPoint);
	m_CmbCBSimulation->SetIndex(&m_pImpedanceParas->m_bCBSimulation);
	m_editCBTripTime->setText(QString::number(m_pImpedanceParas->m_fCBTripTime, 'f', 3));
	m_editCBCloseTime->setText(QString::number(m_pImpedanceParas->m_fCBCloseTime, 'f', 3));
	m_CmbIPlusDC->SetIndex((int*)(&m_pImpedanceParas->m_bIPlusDC));
	m_CmbFaultIncMode->SetIndex(&m_pImpedanceParas->m_nFaultIncMode);
	m_editFaultAngle->setText(QString::number(m_pImpedanceParas->m_fFaultAngle, 'f', 3));
	m_editFaultAng_0->setText(QString::number(m_pImpedanceParas->m_fFaultAng_0, 'f', 3));
	m_CmbVzDefine->SetIndex(&m_pImpedanceParas->m_nVzDefine);
	m_editUxInput_Mag->setText(QString::number(m_pImpedanceParas->m_fUxInput_Mag, 'f', 3));
	m_editUxInput_Ang->setText(QString::number(m_pImpedanceParas->m_fUxInput_Ang, 'f', 3));
	m_editUxHigh->setText(QString::number(m_pImpedanceParas->m_fUxHigh, 'f', 3));
	m_editUxLow->setText(QString::number(m_pImpedanceParas->m_fUxLow, 'f', 3));

}

void CommonParasDialog::initUI()
{
	CTestDataTypeMngrConstGlobal::Create();

	m_MainLayout = new QGridLayout();
	
	label_1 = new QLabel();
	label_1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_1->setText(QObject::tr("故障时间裕度"));
	
	label_2 = new QLabel();
	label_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_2->setText(QObject::tr("故障前时间"));

	m_editFaultTime = new QFloatLineEdit(this);
	m_editFaultTime->InitCoverage(0,100);
	m_editFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editPreFaultTime = new QFloatLineEdit(this);
	m_editPreFaultTime->InitCoverage(0,100);
	m_editPreFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	label_3 = new QLabel();
	label_3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_3->setText(QObject::tr("故障触发方式"));
	label_4 = new QLabel();
	label_4->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_4->setText(QObject::tr("GPS触发时刻（时）"));
	label_5 = new QLabel();
	label_5->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_5->setText(QObject::tr("GPS触发时刻（分）"));
	label_6 = new QLabel();
	label_6->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_6->setText(QObject::tr("GPS触发时刻（秒）"));

	m_CmbFaultTrigMode = new QValueComboBox(this);
	m_CmbFaultTrigMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultTrigMode")));
	m_CmbFaultTrigMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editHour = new QFloatLineEdit(this);
	m_editHour->InitCoverage(0,100,0);
	m_editHour->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editMinutes = new QFloatLineEdit(this);
	m_editMinutes->InitCoverage(0,59,0);
	m_editMinutes->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editSeconds = new QFloatLineEdit(this);
	m_editSeconds->InitCoverage(0,59,0);
	m_editSeconds->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	label_7 = new QLabel();
	label_7->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_7->setText(QObject::tr("零序补偿系数表达方式"));
	label_8 = new QLabel();
	label_8->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_8->setText(QObject::tr("零序补偿系数RE/RL"));
	label_9 = new QLabel();
	label_9->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_9->setText(QObject::tr("零序补偿系数XE/XL"));

	m_CmbK0CalMode = new QValueComboBox(this);
	m_CmbK0CalMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("ZeroCalMode")));
	m_CmbK0CalMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editK0Amp = new QFloatLineEdit(this);
	m_editK0Amp->InitCoverage(0,100);
	m_editK0Amp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editK0Angle = new QFloatLineEdit(this);
	m_editK0Angle->InitCoverage(0,100);
	m_editK0Angle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	label_10 = new QLabel();
	label_10->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_10->setText(QObject::tr("负荷电流"));
	label_11 = new QLabel();
	label_11->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_11->setText(QObject::tr("负荷功角"));

	m_editIfh = new QFloatLineEdit(this);
	m_editIfh->InitCoverage(0,999);
	m_editIfh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editPowerAngle = new QFloatLineEdit(this);
	m_editPowerAngle->InitCoverage(0,180);
	m_editPowerAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	label_12 = new QLabel();
	label_12->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_12->setText(QObject::tr("重合闸时间定值"));
	label_13 = new QLabel();
	label_13->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_13->setText(QObject::tr("后加速时间定值"));

	m_editRecloseTime = new QFloatLineEdit(this);
	m_editRecloseTime->InitCoverage(0,999);
	m_editRecloseTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editAfterAcceTime = new QFloatLineEdit(this);
	m_editAfterAcceTime->InitCoverage(0,180);
	m_editAfterAcceTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	label_14 = new QLabel();
	label_14->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_14->setText(QObject::tr("PT安装位置"));
	label_15 = new QLabel();
	label_15->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_15->setText(QObject::tr("CT正极性"));
	label_16 = new QLabel();
	label_16->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_16->setText(QObject::tr("是否模拟断路器延时"));
	label_17 = new QLabel();
	label_17->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_17->setText(QObject::tr("断路器跳闸延时"));
	label_18 = new QLabel();
	label_18->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_18->setText(QObject::tr("断路器合闸延时"));

	m_CmbPTPoint = new QValueComboBox(this);
	m_CmbPTPoint->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("PTPosition")));
	m_CmbPTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_CmbCTPoint = new QValueComboBox(this);
	m_CmbCTPoint->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CTPos")));
	m_CmbCTPoint->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_CmbCBSimulation = new QValueComboBox(this);
	m_CmbCBSimulation->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("CBSimulation")));
	m_CmbCBSimulation->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editCBTripTime = new QFloatLineEdit(this);
	m_editCBTripTime->InitCoverage(0,999);
	m_editCBTripTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editCBCloseTime = new QFloatLineEdit(this);
	m_editCBCloseTime->InitCoverage(0,180);
	m_editCBCloseTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	label_19 = new QLabel();
	label_19->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_19->setText(QObject::tr("是否叠加非周期分量"));
	label_20 = new QLabel();
	label_20->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_20->setText(QObject::tr("合闸角方式"));
	label_21 = new QLabel();
	label_21->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_21->setText(QObject::tr("合闸角"));
	label_22 = new QLabel();
	label_22->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_22->setText(QObject::tr("合闸角的起始值"));
	
	m_CmbIPlusDC = new QValueComboBox(this);
	m_CmbIPlusDC->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultId")));
	m_CmbIPlusDC->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_CmbFaultIncMode = new QValueComboBox(this);
	m_CmbFaultIncMode->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("FaultAngMode")));
	m_CmbFaultIncMode->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	
	m_editFaultAngle = new QFloatLineEdit(this);
	m_editFaultAngle->InitCoverage(0,180,0);
	m_editFaultAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editFaultAng_0 = new QFloatLineEdit(this);
	m_editFaultAng_0->InitCoverage(0,100);
	m_editFaultAng_0->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


	label_23 = new QLabel();
	label_23->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_23->setText(QObject::tr("辅助电压Ux 输出方式"));
	label_24 = new QLabel();
	label_24->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_24->setText(QObject::tr("同期电压幅值"));
	label_25 = new QLabel();
	label_25->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_25->setText(QObject::tr("同期电压相位"));
	label_26 = new QLabel();
	label_26->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_26->setText(QObject::tr("有压测试值"));
	label_27 = new QLabel();
	label_27->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	label_27->setText(QObject::tr("无压测试值"));

	m_CmbVzDefine = new QValueComboBox(this);
	m_CmbVzDefine->SetValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(_T("UxMode")));
	m_CmbVzDefine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editUxInput_Mag = new QFloatLineEdit(this);
	m_editUxInput_Mag->InitCoverage(0,180,0);
	m_editUxInput_Mag->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editUxInput_Ang = new QFloatLineEdit(this);
	m_editUxInput_Ang->InitCoverage(0,100);
	m_editUxInput_Ang->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editUxHigh = new QFloatLineEdit(this);
	m_editUxHigh->InitCoverage(0,180,0);
	m_editUxHigh->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_editUxLow = new QFloatLineEdit(this);
	m_editUxLow->InitCoverage(0,100);
	m_editUxLow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_BtnOk = new QPushButton(this);
	m_BtnOk->setText(QObject::tr("确认"));
	m_BtnOk->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_BtnCancel = new QPushButton(this);
	m_BtnCancel->setText(QObject::tr("取消"));
	m_BtnCancel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	m_MainLayout->setSpacing(10);
	m_MainLayout->addWidget(label_1,0,0);
	m_MainLayout->addWidget(label_2,1,0);
	m_MainLayout->addWidget(label_3,2,0);
	m_MainLayout->addWidget(label_4,3,0);
	m_MainLayout->addWidget(label_5,4,0);
	m_MainLayout->addWidget(label_6,5,0);
	m_MainLayout->addWidget(label_7,6,0);
	m_MainLayout->addWidget(label_8,7,0);
	m_MainLayout->addWidget(label_9,8,0);
	m_MainLayout->addWidget(label_10,9,0);
	m_MainLayout->addWidget(label_11,10,0);
	m_MainLayout->addWidget(label_12,11,0);
	m_MainLayout->addWidget(label_13,12,0);
	m_MainLayout->addWidget(label_14,13,0);

	m_MainLayout->addWidget(m_editFaultTime,0,1);
	m_MainLayout->addWidget(m_editPreFaultTime,1,1);
	m_MainLayout->addWidget(m_CmbFaultTrigMode,2,1);
	m_MainLayout->addWidget(m_editHour,3,1);
	m_MainLayout->addWidget(m_editMinutes,4,1);
	m_MainLayout->addWidget(m_editSeconds,5,1);
	m_MainLayout->addWidget(m_CmbK0CalMode,6,1);
	m_MainLayout->addWidget(m_editK0Amp,7,1);
	m_MainLayout->addWidget(m_editK0Angle,8,1);
	m_MainLayout->addWidget(m_editIfh,9,1);
	m_MainLayout->addWidget(m_editPowerAngle,10,1);
	m_MainLayout->addWidget(m_editRecloseTime,11,1);
	m_MainLayout->addWidget(m_editAfterAcceTime,12,1);
	m_MainLayout->addWidget(m_CmbPTPoint,13,1);

	m_MainLayout->addWidget(label_15,0,2);
	m_MainLayout->addWidget(label_16,1,2);
	m_MainLayout->addWidget(label_17,2,2);
	m_MainLayout->addWidget(label_18,3,2);
	m_MainLayout->addWidget(label_19,4,2);
	m_MainLayout->addWidget(label_20,5,2);
	m_MainLayout->addWidget(label_21,6,2);
	m_MainLayout->addWidget(label_22,7,2);
	m_MainLayout->addWidget(label_23,8,2);
	m_MainLayout->addWidget(label_24,9,2);
	m_MainLayout->addWidget(label_25,10,2);
	m_MainLayout->addWidget(label_26,11,2);
	m_MainLayout->addWidget(label_27,12,2);
	m_MainLayout->addWidget(m_BtnOk,13,2);

	m_MainLayout->addWidget(m_CmbCTPoint,		0,3);
	m_MainLayout->addWidget(m_CmbCBSimulation,  1,3);
	m_MainLayout->addWidget(m_editCBTripTime,   2,3);
	m_MainLayout->addWidget(m_editCBCloseTime,  3,3);
	m_MainLayout->addWidget(m_CmbIPlusDC,		4,3);
	m_MainLayout->addWidget(m_CmbFaultIncMode,  5,3);
	m_MainLayout->addWidget(m_editFaultAngle,   6,3);
	m_MainLayout->addWidget(m_editFaultAng_0,   7,3);
	m_MainLayout->addWidget(m_CmbVzDefine,		8,3);
	m_MainLayout->addWidget(m_editUxInput_Mag,  9,3);
	m_MainLayout->addWidget(m_editUxInput_Ang,  10,3);
	m_MainLayout->addWidget(m_editUxHigh,		11,3);
	m_MainLayout->addWidget(m_editUxLow,	    12,3);
	m_MainLayout->addWidget(m_BtnCancel,		13,3);

	setLayout(m_MainLayout);
}

void CommonParasDialog::slot_ClickOk()
{
	m_pImpedanceParas->m_fFaultTime = m_editFaultTime->text().toFloat();
	m_pImpedanceParas->m_fPreFaultTime = m_editPreFaultTime->text().toFloat();
	/*m_CmbFaultTrigMode->SetIndex(&m_pImpedanceParas->m_nFaultTrigMode);*/
	m_pImpedanceParas->m_tGps.nHour = m_editHour->text().toFloat();
	m_pImpedanceParas->m_tGps.nMinutes = m_editMinutes->text().toFloat();
	m_pImpedanceParas->m_tGps.nSeconds = m_editSeconds->text().toFloat();
	/*m_CmbK0CalMode->SetIndex(&m_pImpedanceParas->m_nK0CalMode);*/
	m_pImpedanceParas->m_fK0Amp = m_editK0Amp->text().toFloat();
	m_pImpedanceParas->m_fK0Angle = m_editK0Angle->text().toFloat();
	m_pImpedanceParas->m_fIfh = m_editIfh->text().toFloat();
	m_pImpedanceParas->m_fPowerAngle = m_editPowerAngle->text().toFloat();
	m_pImpedanceParas->m_fRecloseTime = m_editRecloseTime->text().toFloat();
	m_pImpedanceParas->m_fAfterAcceTime = m_editAfterAcceTime->text().toFloat();
	/*m_CmbPTPoint->SetIndex((int*)(&m_pImpedanceParas->m_nPTPoint));
	m_CmbCTPoint->SetIndex(&m_pImpedanceParas->m_nCTPoint);
	m_CmbCBSimulation->SetIndex(&m_pImpedanceParas->m_bCBSimulation);*/
	m_pImpedanceParas->m_fCBTripTime = m_editCBTripTime->text().toFloat();
	m_pImpedanceParas->m_fCBCloseTime = m_editCBCloseTime->text().toFloat();
	/*m_CmbIPlusDC->SetIndex((int*)(&m_pImpedanceParas->m_bIPlusDC));
	m_CmbFaultIncMode->SetIndex(&m_pImpedanceParas->m_nFaultIncMode);*/
	m_pImpedanceParas->m_fFaultAngle = m_editFaultAngle->text().toFloat();
	m_pImpedanceParas->m_fFaultAng_0 = m_editFaultAng_0->text().toFloat();
	/*m_CmbVzDefine->SetIndex(&m_pImpedanceParas->m_nVzDefine);*/
	m_pImpedanceParas->m_fUxInput_Mag = m_editUxInput_Mag->text().toFloat();
	m_pImpedanceParas->m_fUxInput_Ang = m_editUxInput_Ang->text().toFloat();
	m_pImpedanceParas->m_fUxHigh = m_editUxHigh->text().toFloat();
	m_pImpedanceParas->m_fUxLow = m_editUxLow->text().toFloat();

	emit sig_ClickOk();
	close();
}
void CommonParasDialog::slot_ClickCancel()
{
	close();
}

