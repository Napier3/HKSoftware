#include "QLowFrepAddMultDlg.h"
#include <QLabel>
#include "../../UI/SoftKeyboard/SoftKeyBoard.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../OSInterface/QT/XMessageBox.h"

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang 

QLowFrepAddMultDlg::QLowFrepAddMultDlg(QWidget *parent /*= 0*/) : QDialog(parent),
ui(new Ui::QLowFrepAddMultDlg)
{
	Stt_Global_SettingParent(this);	//20240802 huangliang 
	ui->setupUi(this);
	//OpenXmlFile();
	InitUI();
    //InitFont();
	InitConnects();
}

QLowFrepAddMultDlg::~QLowFrepAddMultDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
	delete ui;
}

void QLowFrepAddMultDlg::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
    ui->m_CmbUSetMode->addItem(/*"相电压"*/g_sLangTxt_Native_VolSetTypeLN.remove("(Y)"));
    ui->m_CmbUSetMode->addItem(/*"线电压"*/g_sLangTxt_Native_VolSetTypeLL.remove("(D)"));

    ui->m_CmbUVariable->addItem(/*"低压"*/g_sLangTxt_LowFreq_LowVol);
    ui->m_CmbUVariable->addItem(/*"负序电压(U2)"*/g_sLangTxt_ActionTime_NegVol + "(U2)");
    ui->m_CmbUVariable->addItem(/*"零序电压(3U0)"*/g_sLangTxt_ActionTime_ZeroVol + "(3U0)");

	ui->m_EditBeginVal->setEnabled(false);
	ui->m_EditEndVal->setEnabled(false);
	ui->m_EditStep->setEnabled(false);
	ui->m_EditFreqEnd->setEnabled(false);
	ui->m_EditBeginVal1->setEnabled(false);
	ui->m_EditEndVal1->setEnabled(false);
	ui->m_EditStep1->setEnabled(false);
	ui->m_EditRampTo->setEnabled(false);
	ui->m_EditDvdt2Rate->setEnabled(false);
	ui->m_EditBeginVal2->setEnabled(false);
	ui->m_EditEndVal2->setEnabled(false);
	ui->m_EditStep2->setEnabled(false);
	ui->m_EditRampTo1->setEnabled(false);
	ui->m_EditDvdt3Rate->setEnabled(false);
	ui->m_labTips->setVisible(false);

	ui->m_LabTestItem->setText(/*测试项目*/g_sLangTxt_LowFreq_TestItem);
	ui->m_pLabSetValue->setText(/*整定值*/g_sLangTxt_State_SettingValue);
	ui->m_LabStart->setText(/*始值*/g_sLangTxt_State_BeginVal);
	ui->m_LabEnd->setText(/*终值*/g_sLangTxt_State_EndVal);
	ui->m_LabStep->setText(/*变化步长*/g_sLangTxt_Gradient_Step);
	ui->m_LabParas->setText(/*递变参数*/g_sLangTxt_LowFreq_GradientPara);
	ui->m_TripFreCheck->setText(/*频率动作值(Hz)*/g_sLangTxt_Gradient_FreAValue);
	ui->m_FActTimeCheck->setText(/*动作时间(s)*/g_sLangTxt_Native_ActionTime);
	ui->m_DvdtCloseCheck->setText(/*滑差闭锁值(Hz/s)*/g_sLangTxt_Native_sliptripValue + "(Hz/s)");
	ui->m_TripILockCheck->setText(/*低电流闭锁值(A)*/g_sLangTxt_LowFreq_ILock + "(A)");
	ui->m_TripULockCheck->setText(/*低电压闭锁值(V)*/g_sLangTxt_LowFreq_ULock + "(V)");
	ui->m_LabdvdtRate->setText(/*频率滑差倍数*/g_sLangTxt_LowFreq_dvdtRate);

	ui->m_LabFend1->setText(/*频率结束值(Hz)*/g_sLangTxt_LowFreq_FreqEnd);
	ui->m_Labdvdt1Rate->setText(/*频率滑差倍数*/g_sLangTxt_LowFreq_dvdtRate);
	ui->m_LabFreqEnd->setText(/*频率结束值(Hz)*/g_sLangTxt_LowFreq_FreqEnd);
	ui->m_LabRampTo->setText(/*频率结束值(Hz)*/g_sLangTxt_LowFreq_FreqEnd);
	ui->m_LabDvdt2Rate->setText(/*频率滑差倍数*/g_sLangTxt_LowFreq_dvdtRate);
	ui->m_LabRampTo1->setText(/*频率结束值(Hz)*/g_sLangTxt_LowFreq_FreqEnd);
	ui->m_LabDvdt3Rate->setText(/*频率滑差倍数*/g_sLangTxt_LowFreq_dvdtRate);

	ui->m_groupBox6->setTitle(/*时间参数*/g_sLangTxt_LowFreq_TimePara);
	ui->m_groupBox7->setTitle(/*电压闭锁参数*/g_sLangTxt_LowFreq_ULockPara);
	ui->m_LabHoldTime->setText(/*保持时间*/g_sLangTxt_Native_KeepTime + "(s):");
	ui->m_LabUSetMode->setText(/*闭锁电压选择*/g_sLangTxt_LowFreq_FreqFaultTrig);
	ui->m_LabUVariable->setText(/*电压变化量*/g_sLangTxt_Native_VoltChangeAmt);
	ui->m_BtnResultAssess->setText(/*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate);
	ui->m_BtnOk->setText(/*确定*/g_sLangTxt_OK);
	ui->m_BtnExit->setText(/*取消*/g_sLangTxt_Cancel);
	setWindowTitle(/*添加系列*/g_sLangTxt_Distance_AddMultTile);
	/*ui->m_EditFAct->setFixedWidth(110);
	ui->m_EditDvdtClose->setFixedWidth(110);
	ui->m_EditFActTime->setFixedWidth(110);

	ui->m_EditTripILock->setFixedWidth(110);
	ui->m_EditTripULock->setFixedWidth(110);

	ui->m_EditFstart->setFixedWidth(110);
	ui->m_EditBeginVal->setFixedWidth(110);
	ui->m_EditBeginVal1->setFixedWidth(110);
	ui->m_EditBeginVal2->setFixedWidth(110);
	ui->m_EditEndVal->setFixedWidth(110);
	ui->m_EditEndVal1->setFixedWidth(110);
	ui->m_EditEndVal2->setFixedWidth(110);
	ui->m_EditFstep->setFixedWidth(110);
	ui->m_EditStep->setFixedWidth(110);
	ui->m_EditStep1->setFixedWidth(110);
	ui->m_EditStep2->setFixedWidth(110);
	ui->m_EditdvdtRate->setFixedWidth(110);
	ui->m_EditFend1->setFixedWidth(110);
	ui->m_Editdvdt1Rate->setFixedWidth(110);
	ui->m_EditFreqEnd->setFixedWidth(110);
	ui->m_EditRampTo->setFixedWidth(110);
	ui->m_EditDvdt2Rate->setFixedWidth(110);
	ui->m_EditRampTo1->setFixedWidth(110);
	ui->m_EditDvdt3Rate->setFixedWidth(110);
	ui->m_EditHoldTime->setFixedWidth(110);*/

	resize(900, 300);
}

void QLowFrepAddMultDlg::InitFont()
{
	ui->m_groupBox2->setFont(*g_pSttGlobalFont);
	ui->m_groupBox5->setFont(*g_pSttGlobalFont);
	ui->m_groupBox6->setFont(*g_pSttGlobalFont);
	ui->m_groupBox7->setFont(*g_pSttGlobalFont);
	ui->m_TripFreCheck->setFont(*g_pSttGlobalFont);
	ui->m_FActTimeCheck->setFont(*g_pSttGlobalFont);
	ui->m_DvdtCloseCheck->setFont(*g_pSttGlobalFont);
	ui->m_TripILockCheck->setFont(*g_pSttGlobalFont);
	ui->m_TripULockCheck->setFont(*g_pSttGlobalFont);

	ui->m_EditFAct->setFont(*g_pSttGlobalFont);
	ui->m_EditDvdtClose->setFont(*g_pSttGlobalFont);
	ui->m_EditFActTime->setFont(*g_pSttGlobalFont);

	ui->m_EditTripILock->setFont(*g_pSttGlobalFont);
	ui->m_EditTripULock->setFont(*g_pSttGlobalFont);

	ui->m_EditFstart->setFont(*g_pSttGlobalFont);
	ui->m_EditBeginVal->setFont(*g_pSttGlobalFont);
	ui->m_EditBeginVal1->setFont(*g_pSttGlobalFont);
	ui->m_EditBeginVal2->setFont(*g_pSttGlobalFont);
	ui->m_EditEndVal->setFont(*g_pSttGlobalFont);
	ui->m_EditEndVal1->setFont(*g_pSttGlobalFont);
	ui->m_EditEndVal2->setFont(*g_pSttGlobalFont);
	ui->m_EditFstep->setFont(*g_pSttGlobalFont);
	ui->m_EditStep->setFont(*g_pSttGlobalFont);
	ui->m_EditStep1->setFont(*g_pSttGlobalFont);
	ui->m_EditStep2->setFont(*g_pSttGlobalFont);
	ui->m_EditdvdtRate->setFont(*g_pSttGlobalFont);
	ui->m_EditFend1->setFont(*g_pSttGlobalFont);
	ui->m_Editdvdt1Rate->setFont(*g_pSttGlobalFont);
	ui->m_EditFreqEnd->setFont(*g_pSttGlobalFont);
	ui->m_EditRampTo->setFont(*g_pSttGlobalFont);
	ui->m_EditDvdt2Rate->setFont(*g_pSttGlobalFont);
	ui->m_EditRampTo1->setFont(*g_pSttGlobalFont);
	ui->m_EditDvdt3Rate->setFont(*g_pSttGlobalFont);
	ui->m_EditHoldTime->setFont(*g_pSttGlobalFont);
	ui->m_CmbUSetMode->setFont(*g_pSttGlobalFont);
	ui->m_CmbUVariable->setFont(*g_pSttGlobalFont);
	ui->m_BtnResultAssess->setFont(*g_pSttGlobalFont);
    //ui->m_BtnBinBout->setFont(*g_pSttGlobalFont);  //lijunqing build error[2024-7-12]
	ui->m_BtnExit->setFont(*g_pSttGlobalFont);

	ui->m_LabdvdtRate->setFont(*g_pSttGlobalFont);
	ui->m_LabFend1->setFont(*g_pSttGlobalFont);
	ui->m_Labdvdt1Rate->setFont(*g_pSttGlobalFont);
	ui->m_LabFreqEnd->setFont(*g_pSttGlobalFont);
	ui->m_LabRampTo->setFont(*g_pSttGlobalFont);
	ui->m_LabDvdt2Rate->setFont(*g_pSttGlobalFont);
	ui->m_LabRampTo1->setFont(*g_pSttGlobalFont);
	ui->m_LabDvdt3Rate->setFont(*g_pSttGlobalFont);
	ui->m_LabHoldTime->setFont(*g_pSttGlobalFont);
	ui->m_LabUSetMode->setFont(*g_pSttGlobalFont);
	ui->m_LabUVariable->setFont(*g_pSttGlobalFont);

	ui->m_LabTestItem->setFont(*g_pSttGlobalFont);
	ui->m_pLabSetValue->setFont(*g_pSttGlobalFont);
	ui->m_LabStart->setFont(*g_pSttGlobalFont);
	ui->m_LabEnd->setFont(*g_pSttGlobalFont);
	ui->m_LabStep->setFont(*g_pSttGlobalFont);
	ui->m_LabParas->setFont(*g_pSttGlobalFont);
	ui->m_EditFend->setFont(*g_pSttGlobalFont);
	ui->m_BtnOk->setFont(*g_pSttGlobalFont);
}

void QLowFrepAddMultDlg::InitConnects()
{
	connect(ui->m_TripFreCheck, SIGNAL(clicked()), this, SLOT(slot_TripFreCheck()));
	connect(ui->m_FActTimeCheck, SIGNAL(clicked(bool)), this, SLOT(slot_FActTimeCheck(bool)));
	connect(ui->m_DvdtCloseCheck, SIGNAL(clicked(bool)), this, SLOT(slot_DvdtCloseCheck(bool)));
	connect(ui->m_TripILockCheck, SIGNAL(clicked(bool)), this, SLOT(slot_TripILockCheck(bool)));
	connect(ui->m_TripULockCheck, SIGNAL(clicked(bool)), this, SLOT(slot_TripULockCheck(bool)));

	
	connect(ui->m_EditFAct, SIGNAL(editingFinished()), this, SLOT(slot_EditFAct()));
	connect(ui->m_EditFstart, SIGNAL(editingFinished()), this, SLOT(slot_EditFstart()));
	connect(ui->m_EditFend, SIGNAL(editingFinished()), this, SLOT(slot_EditFend()));
	connect(ui->m_EditFstep, SIGNAL(editingFinished()), this, SLOT(slot_EditFstep()));
	connect(ui->m_EditdvdtRate, SIGNAL(editingFinished()), this, SLOT(slot_EditdvdtRate()));
	connect(ui->m_EditFActTime, SIGNAL(editingFinished()), this, SLOT(slot_EditFActTime()));
	connect(ui->m_EditFend1, SIGNAL(editingFinished()), this, SLOT(slot_EditFend1()));
	connect(ui->m_Editdvdt1Rate, SIGNAL(editingFinished()), this, SLOT(slot_Editdvdt1Rate()));
	connect(ui->m_EditDvdtClose, SIGNAL(editingFinished()), this, SLOT(slot_EditDvdtClose()));
	connect(ui->m_EditBeginVal, SIGNAL(editingFinished()), this, SLOT(slot_EditBeginVal()));
	connect(ui->m_EditEndVal, SIGNAL(editingFinished()), this, SLOT(slot_EditEndVal()));
	connect(ui->m_EditStep, SIGNAL(editingFinished()), this, SLOT(slot_EditStep()));
	connect(ui->m_EditFreqEnd, SIGNAL(editingFinished()), this, SLOT(slot_EditFreqEnd()));
	connect(ui->m_EditTripILock, SIGNAL(editingFinished()), this, SLOT(slot_EditTripILock()));
	connect(ui->m_EditBeginVal1, SIGNAL(editingFinished()), this, SLOT(slot_EditBeginVal1()));
	connect(ui->m_EditEndVal1, SIGNAL(editingFinished()), this, SLOT(slot_EditEndVal1()));
	connect(ui->m_EditStep1, SIGNAL(editingFinished()), this, SLOT(slot_EditStep1()));
	connect(ui->m_EditRampTo, SIGNAL(editingFinished()), this, SLOT(slot_EditRampTo()));
	connect(ui->m_EditDvdt2Rate, SIGNAL(editingFinished()), this, SLOT(slot_EditDvdt2Rate()));
	connect(ui->m_EditTripULock, SIGNAL(editingFinished()), this, SLOT(slot_EditTripULock()));
	connect(ui->m_EditBeginVal2, SIGNAL(editingFinished()), this, SLOT(slot_EditBeginVal2()));
	connect(ui->m_EditEndVal2, SIGNAL(editingFinished()), this, SLOT(slot_EditEndVal2()));
	connect(ui->m_EditStep2, SIGNAL(editingFinished()), this, SLOT(slot_EditStep2()));
	connect(ui->m_EditRampTo1, SIGNAL(editingFinished()), this, SLOT(slot_EditRampTo1()));
	connect(ui->m_EditDvdt3Rate, SIGNAL(editingFinished()), this, SLOT(slot_EditDvdt3Rate()));
	connect(ui->m_EditHoldTime, SIGNAL(editingFinished()), this, SLOT(slot_EditHoldTime()));

	connect(ui->m_CmbUSetMode, SIGNAL(editingFinished()), this, SLOT(slot_CmbUSetMode()));
	connect(ui->m_CmbUVariable, SIGNAL(editingFinished()), this, SLOT(slot_CmbUVariable()));

	connect(ui->m_BtnResultAssess, SIGNAL(clicked()), this, SLOT(slot_BtnResultAssess()));
    //connect(ui->m_BtnBinBout, SIGNAL(clicked()), this, SLOT(slot_BtnBinBout()));   //lijunqing build error[2024-7-12]
	connect(ui->m_BtnExit,SIGNAL(clicked()),this,SLOT(slot_Exit()));
	connect(ui->m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_Ok()));
}

void QLowFrepAddMultDlg::slot_TripFreCheck()
{
	bool state = ui->m_TripFreCheck->isChecked();

	ui->m_EditFstart->setEnabled(state);
	ui->m_EditFend->setEnabled(state);
	ui->m_EditFstep->setEnabled(state);
	ui->m_EditdvdtRate->setEnabled(state);

	ShowOneChecked(ui->m_TripFreCheck, state);
}

void QLowFrepAddMultDlg::slot_FActTimeCheck(bool state)
{
	ShowOneChecked(ui->m_FActTimeCheck, state);

	ui->m_EditFend1->setEnabled(state);
	ui->m_Editdvdt1Rate->setEnabled(state);
}

void QLowFrepAddMultDlg::slot_DvdtCloseCheck(bool state)
{
	ShowOneChecked(ui->m_DvdtCloseCheck, state);

	ui->m_EditBeginVal->setEnabled(state);
	ui->m_EditEndVal->setEnabled(state);
	ui->m_EditStep->setEnabled(state);
	ui->m_EditFreqEnd->setEnabled(state);
}

void QLowFrepAddMultDlg::slot_TripILockCheck(bool state)
{
	ShowOneChecked(ui->m_TripILockCheck, state);

	ui->m_EditBeginVal1->setEnabled(state);
	ui->m_EditEndVal1->setEnabled(state);
	ui->m_EditStep1->setEnabled(state);
	ui->m_EditRampTo->setEnabled(state);
	ui->m_EditDvdt2Rate->setEnabled(state);
}

void QLowFrepAddMultDlg::slot_TripULockCheck(bool state)
{
	ShowOneChecked(ui->m_TripULockCheck, state);

	ui->m_EditBeginVal2->setEnabled(state);
	ui->m_EditEndVal2->setEnabled(state);
	ui->m_EditStep2->setEnabled(state);
	ui->m_EditRampTo1->setEnabled(state);
	ui->m_EditDvdt3Rate->setEnabled(state);
}


void QLowFrepAddMultDlg::ShowOneChecked(QCheckBox* pCurrentCheckBox, bool state) 
{
	if (!state &&
		!ui->m_TripFreCheck->isChecked()&&
		!ui->m_FActTimeCheck->isChecked()&&
		!ui->m_DvdtCloseCheck->isChecked()&&
		!ui->m_TripILockCheck->isChecked()&&
		!ui->m_TripULockCheck->isChecked())
	{
			ui->m_TripFreCheck->setChecked(true);
			ui->m_EditFstart->setEnabled(true);
			ui->m_EditFend->setEnabled(true);
			ui->m_EditFstep->setEnabled(true);
			ui->m_EditdvdtRate->setEnabled(true);
			SetApplyTips(/*_T("请至少勾选一个测试项！")*/g_sLangTxt_MaintainatLeastOneItem);
	}
}

void QLowFrepAddMultDlg::slot_EditFAct()
{
	if (ui->m_EditFAct->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditFAct)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditFAct->text().toFloat();
	fv = setLimit(0,1000.000,fv);
	ui->m_EditFAct->setText(QString::number(fv, 'f', 3));

	float fFstart = fv - 0.1 * abs(fv - g_oSystemParas.m_fFNom);
	ui->m_EditFstart->setText(QString::number(fFstart, 'f', 3));

	float fFend = fv + 0.1 * abs(fv - g_oSystemParas.m_fFNom);
	ui->m_EditFend->setText(QString::number(fFend, 'f', 3));

}
void QLowFrepAddMultDlg::slot_EditFstart()
{
	
	if (ui->m_EditFstart->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditFstart)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditFstart->text().toFloat();
	fv = setLimit(0,2000.000,fv);
	ui->m_EditFstart->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditFend()
{
	
	if (ui->m_EditFend->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditFend)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditFend->text().toFloat();
	fv = setLimit(0,2000.000,fv);
	ui->m_EditFend->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditFstep()
{
	
	if (ui->m_EditFstep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditFstep)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditFstep->text().toFloat();
	fv = setLimit(0,100.000,fv);
	ui->m_EditFstep->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditdvdtRate()
{
	float fv = ui->m_EditdvdtRate->text().toFloat();
	fv = setLimit(0,22.00,fv);
	ui->m_EditdvdtRate->setText(QString::number(fv, 'f', 2));
}
void QLowFrepAddMultDlg::slot_EditFActTime()
{
	
	if (ui->m_EditFActTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditFActTime)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditFActTime->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_EditFActTime->setText(QString::number(fv, 'f', 3));

	float fHoldTime = fv * 1.2;
	ui->m_EditHoldTime->setText(QString::number(fHoldTime, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditFend1()
{
	float fv = ui->m_EditFend1->text().toFloat();
	fv = setLimit(0,1000.000,fv);
	ui->m_EditFend1->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_Editdvdt1Rate()
{
	float fv = ui->m_Editdvdt1Rate->text().toFloat();
	fv = setLimit(0,22.00,fv);
	ui->m_Editdvdt1Rate->setText(QString::number(fv, 'f', 2));
}
void QLowFrepAddMultDlg::slot_EditDvdtClose()
{
	
	if (ui->m_EditDvdtClose->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditDvdtClose)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditDvdtClose->text().toFloat();
	fv = setLimit(0,1000.000,fv);
	ui->m_EditDvdtClose->setText(QString::number(fv, 'f', 3));

	float fBeginVal = fv * 1.1;
	ui->m_EditBeginVal->setText(QString::number(fBeginVal, 'f', 3));

	float fEndVal = fv * 0.8;
	ui->m_EditEndVal->setText(QString::number(fEndVal, 'f', 3));

	float fStep = fv * 0.1;
	ui->m_EditStep->setText(QString::number(fStep, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditBeginVal()
{
	
	if (ui->m_EditBeginVal->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditBeginVal)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditBeginVal->text().toFloat();
	fv = setLimit(0,2000.000,fv);
	ui->m_EditBeginVal->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditEndVal()
{
	
	if (ui->m_EditEndVal->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditEndVal)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditEndVal->text().toFloat();
	fv = setLimit(0,800.000,fv);
	ui->m_EditEndVal->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditStep()
{
	
	if (ui->m_EditStep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditStep)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditStep->text().toFloat();
	fv = setLimit(0,100.000,fv);
	ui->m_EditStep->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditFreqEnd()
{
	float fv = ui->m_EditFreqEnd->text().toFloat();
	fv = setLimit(0,1000.000,fv);
	ui->m_EditFreqEnd->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditTripILock()
{
	
	if (ui->m_EditTripILock->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditTripILock)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditTripILock->text().toFloat();
	fv = setLimit(0,20.000,fv);
	ui->m_EditTripILock->setText(QString::number(fv, 'f', 3));

	float fBeginVal1 = fv * 0.8;
	ui->m_EditBeginVal1->setText(QString::number(fBeginVal1, 'f', 3));

	float fEndVal1 = fv * 1.2;
	ui->m_EditEndVal1->setText(QString::number(fEndVal1, 'f', 3));

	float fStep1 = fv * 0.1;
	ui->m_EditStep1->setText(QString::number(fStep1, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditBeginVal1()
{
	
	if (ui->m_EditBeginVal1->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditBeginVal1)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditBeginVal1->text().toFloat();
	fv = setLimit(0, 50.000, fv);
	ui->m_EditBeginVal1->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditEndVal1()
{
	
	if (ui->m_EditEndVal1->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditEndVal1)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditEndVal1->text().toFloat();
	fv = setLimit(0,40.000,fv);
	ui->m_EditEndVal1->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditStep1()
{
	
	if (ui->m_EditStep1->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditStep1)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditStep1->text().toFloat();
	fv = setLimit(0,100.000,fv);
	ui->m_EditStep1->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditRampTo()
{
	float fv = ui->m_EditRampTo->text().toFloat();
	fv = setLimit(0,1000.000,fv);
	ui->m_EditRampTo->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditDvdt2Rate()
{
	float fv = ui->m_EditDvdt2Rate->text().toFloat();
	fv = setLimit(0,22.00,fv);
	ui->m_EditDvdt2Rate->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditTripULock()
{
	
	if (ui->m_EditTripULock->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditTripULock)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditTripULock->text().toFloat();
	fv = setLimit(0,130.000,fv);
	ui->m_EditTripULock->setText(QString::number(fv, 'f', 3));

	float fBeginVal2 = fv * 1.2;
	ui->m_EditBeginVal2->setText(QString::number(fBeginVal2, 'f', 3));

	float fEndVal2 = fv * 0.8;
	ui->m_EditEndVal2->setText(QString::number(fEndVal2, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditBeginVal2()
{
	
	if (ui->m_EditBeginVal2->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditBeginVal2)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditBeginVal2->text().toFloat();
	fv = setLimit(0,300.000,fv);
	ui->m_EditBeginVal2->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditEndVal2()
{
	
	if (ui->m_EditEndVal2->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditEndVal2)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditEndVal2->text().toFloat();
	fv = setLimit(0,300.000,fv);
	ui->m_EditEndVal2->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditStep2()
{
	
	if (ui->m_EditStep2->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_EditStep2)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_EditStep2->text().toFloat();
	fv = setLimit(0,300.000,fv);
	ui->m_EditStep2->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditRampTo1()
{
	float fv = ui->m_EditRampTo1->text().toFloat();
	fv = setLimit(0,1000.000,fv);
	ui->m_EditRampTo1->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_EditDvdt3Rate()
{
	float fv = ui->m_EditDvdt3Rate->text().toFloat();
	fv = setLimit(0,22.00,fv);
	ui->m_EditDvdt3Rate->setText(QString::number(fv, 'f', 2));
}

void QLowFrepAddMultDlg::slot_EditHoldTime()
{
	float fv = ui->m_EditHoldTime->text().toFloat();
	fv = setLimit(0,999.999,fv);
	ui->m_EditHoldTime->setText(QString::number(fv, 'f', 3));
}
void QLowFrepAddMultDlg::slot_CmbUSetMode()
{

}
void QLowFrepAddMultDlg::slot_CmbUVariable()
{

}
void QLowFrepAddMultDlg::slot_BtnResultAssess()
{
	QLowFrepResultAssessDlg dlg(&m_oLowFrepDataGroup,this);
    dlg.setWindowTitle(g_sLangTxt_StateEstimate_ResultEstimate);
	dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

/*  //lijunqing build error[2024-7-12]
void QLowFrepAddMultDlg::slot_BtnBinBout()
{
    QLowFrepBinBoutDlg dlg(&m_oLowFrepDataGroup,this);
    dlg.setWindowTitle("开关量");
    dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
    QSoftKeyBoard::AttachObj(&dlg);
    dlg.exec();
    QSoftKeyBoard::ReAttachObj();
#else
    dlg.exec();
#endif

}
*/

void QLowFrepAddMultDlg::OpenXmlFile()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/LowFreqI_Paras.xml");

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oLowFrepDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void QLowFrepAddMultDlg::InitDatas()
{
	CDvmData *pData = NULL;
	long nValue;
	float fValue;

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripFre_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_TripFreCheck->setChecked(nValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("FActTime_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_FActTimeCheck->setChecked(nValue);
	}


	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("DvdtClose_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_DvdtCloseCheck->setChecked(nValue);
	}


	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripILock_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_TripILockCheck->setChecked(nValue);
	}


	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripULock_Check");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_TripULockCheck->setChecked(nValue);
	}


	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("FAct");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditFAct->setText(QString::number(fValue, 'f', 3));
		ui->m_EditFAct->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Fstart");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditFstart->setText(QString::number(fValue, 'f', 3));
		ui->m_EditFstart->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Fend");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditFend->setText(QString::number(fValue, 'f', 3));
		ui->m_EditFend->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Fstep");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditFstep->setText(QString::number(fValue, 'f', 3));
		ui->m_EditFstep->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("dvdtRate");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditdvdtRate->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("FActTime");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditFActTime->setText(QString::number(fValue, 'f', 3));
		ui->m_EditFActTime->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Fend1");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditFend1->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("dvdt1Rate");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_Editdvdt1Rate->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("DvdtClose");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditDvdtClose->setText(QString::number(fValue, 'f', 3));
		ui->m_EditDvdtClose->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("BeginVal");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditBeginVal->setText(QString::number(fValue, 'f', 3));
		ui->m_EditBeginVal->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("EndVal");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditEndVal->setText(QString::number(fValue, 'f', 3));
		ui->m_EditEndVal->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Step");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditStep->setText(QString::number(fValue, 'f', 3));
		ui->m_EditStep->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("FreqEnd");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditFreqEnd->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripILock");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditTripILock->setText(QString::number(fValue, 'f', 3));
		ui->m_EditTripILock->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("BeginVal1");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditBeginVal1->setText(QString::number(fValue, 'f', 3));
		ui->m_EditBeginVal1->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("EndVal1");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditEndVal1->setText(QString::number(fValue, 'f', 3));
		ui->m_EditEndVal1->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Step1");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditStep1->setText(QString::number(fValue, 'f', 3));
		ui->m_EditStep1->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("RampTo");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditRampTo->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("dvdt2Rate");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditDvdt2Rate->setText(QString::number(fValue, 'f', 2));
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripULock");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditTripULock->setText(QString::number(fValue, 'f', 3));
		ui->m_EditTripULock->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("BeginVal2");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditBeginVal2->setText(QString::number(fValue, 'f', 3));
		ui->m_EditBeginVal2->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("EndVal2");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditEndVal2->setText(QString::number(fValue, 'f', 3));
		ui->m_EditEndVal2->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Step2");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		//ui->m_EditStep2->setText(QString::number(fValue, 'f', 3));
		ui->m_EditStep2->UpdateObjectText(pData, pData->m_strValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("RampTo1");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditRampTo1->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("dvdt3Rate");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditDvdt3Rate->setText(QString::number(fValue, 'f', 2));
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("HoldTime");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		ui->m_EditHoldTime->setText(QString::number(fValue, 'f', 3));
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("USetMode");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_CmbUSetMode->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("UVariable");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		ui->m_CmbUVariable->setCurrentIndex(nValue);
	}
}

void QLowFrepAddMultDlg::slot_Ok()
{
	CDvmData *pData;
    long nTripFre = ui->m_TripFreCheck->isChecked();
	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripFre_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nTripFre);
		ui->m_TripFreCheck->setChecked(nTripFre);
	}

	long nFActTime = ui->m_FActTimeCheck->isChecked();
	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("FActTime_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nFActTime);
		ui->m_FActTimeCheck->setChecked(nFActTime);
	}

	long nDvdtClose = ui->m_DvdtCloseCheck->isChecked();
	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("DvdtClose_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nDvdtClose);
		ui->m_DvdtCloseCheck->setChecked(nDvdtClose);
	}

	long nTripILock = ui->m_TripILockCheck->isChecked();
	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripILock_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nTripILock);
		ui->m_TripILockCheck->setChecked(nTripILock);
	}

	long nTripULock = ui->m_TripULockCheck->isChecked();
	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripULock_Check");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nTripULock);
		ui->m_TripULockCheck->setChecked(nTripULock);
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("FAct");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditFAct->GetText();//20240723 huangliang GetText()替换text();
	}
	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Fstart");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditFstart->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Fend");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditFend->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Fstep");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditFstep->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("dvdtRate");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditdvdtRate->text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("FActTime");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditFActTime->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Fend1");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditFend1->text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("dvdt1Rate");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_Editdvdt1Rate->text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("DvdtClose");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditDvdtClose->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("BeginVal");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditBeginVal->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("EndVal");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditEndVal->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Step");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditStep->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("FreqEnd");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditFreqEnd->text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripILock");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditTripILock->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("BeginVal1");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditBeginVal1->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("EndVal1");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditEndVal1->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Step1");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditStep1->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("RampTo");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditRampTo->text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("dvdt2Rate");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditDvdt2Rate->text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("TripULock");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditTripULock->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("BeginVal2");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditBeginVal2->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("EndVal2");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditEndVal2->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("Step2");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditStep2->GetText();//20240723 huangliang GetText()替换text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("RampTo1");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditRampTo1->text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("dvdt3Rate");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditDvdt3Rate->text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("HoldTime");
	if (pData != NULL)
	{
		pData->m_strValue = ui->m_EditHoldTime->text();
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("USetMode");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(ui->m_CmbUSetMode->currentIndex());
	}

	pData = (CDvmData *)m_oLowFrepDataGroup.FindByID("UVariable");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(ui->m_CmbUVariable->currentIndex());
	}

	accept();
}

void QLowFrepAddMultDlg::slot_Exit()
{
	this->close();
}
void QLowFrepAddMultDlg::SetApplyTips(CString strTips)
{
	ui->m_labTips->setText(strTips);
	ui->m_labTips->setVisible(true);
	m_nTipsTime = startTimer(TIPS_DISPLAY_TIME);
}
void QLowFrepAddMultDlg::timerEvent(QTimerEvent* ev)
{
	if (ev->timerId() == m_nTipsTime){
		ui->m_labTips->setVisible(false);
	}
}
void QLowFrepAddMultDlg::GetBinarysParas(CExBaseList *pParas)
{
	if (pParas == NULL)
		return;

	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_A, "A");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_B, "B");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_C, "C");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_D, "R");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_E, "E");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_F, "F");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_G,"G");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_H,"H");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID_AndOr,"_AndOr");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B01,"_B01");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B02,"_B02");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B03,"_B03");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B04,"_B04");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B05,"_B05");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B06,"_B06");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B07,"_B07");
	CheckForBinarys(pParas, STT_MULTI_MACRO_LOWFREQ_PARAS_ID__B08,"_B08");
}
void QLowFrepAddMultDlg::CheckForBinarys(CExBaseList *pParas, CString strMapID, CString strID)
{
	//检查开关量对应数据是否存在，存在则更新数据，不存在则添加
	if (pParas == NULL)
		return;
	CDvmData *pDvmData;
	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strMapID);
	if (pData != NULL)
	{
		pDvmData = (CDvmData *)m_oLowFrepDataGroup.FindByID(strID);
		if (pDvmData != NULL)
		{
			pDvmData->m_strValue = pData->m_strValue;
		}
	}
}