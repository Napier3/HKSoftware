#include "dasetdialog.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

DASetDialog::DASetDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_pSystemParas = NULL;
	m_bChanged = FALSE;
//	m_nFiber = 0;
	m_nIPowerMode = 0;

	initUI();
	initConnections();
	Initlanguage();
}

DASetDialog::~DASetDialog()
{

}

void DASetDialog::Initlanguage()
{
	xlang_SetLangStrToWidget_Txt(ui.groupBox_Modulle,g_sLangTxt_Native_tester_type,XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget_Txt(ui.checkBox_Analog,g_sLangTxt_AnalogValue,XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget_Txt(ui.checkBox_Digit,g_sLangTxt_Native_digital_signal,XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget_Txt(ui.checkBox_Week,g_sLangTxt_Native_smallsignal,XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget_Txt(ui.groupBox_Normal,g_sLangTxt_Report_RatedValue,XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget_Txt(ui.label_12,g_sLangTxt_Native_RatedVolt,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui.label_13,g_sLangTxt_Native_RatedCurr,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui.label_14,g_sLangTxt_Native_RatedFreq,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui.groupBox_Power,g_sLangTxt_Native_curmodule_set,XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget_Txt(ui.label_7,g_sLangTxt_Native_acrange_set,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui.label_9,g_sLangTxt_Native_acmaxportvol_set,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui.groupBox_Other,g_sLangTxt_State_Others,XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget_Txt(ui.label_15,g_sLangTxt_Native_debounce_time,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui.checkBox_BigCurr,g_sLangTxt_Native_highcurterml_Isoutput,XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget_Txt(ui.checkBox_6ITo3I,g_sLangTxt_Native_6Ito3I_output,XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget_Txt(ui.pushButtonSet,g_sLangTxt_Gradient_Setting,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui.pushButtonCancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);
}

void DASetDialog::initUI()
{
	validatorVal = new QDoubleValidator(0.3, 8.5, 3, this);
	ui.lineEditI->setValidator(validatorVal);

	ui.lineEditI->setDisabled(true);

	Qt::WindowFlags flags= this->windowFlags();
	setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);

	setWindowIcon(QIcon("./images/setCommon.png"));
}

void DASetDialog::initConnections()
{
	connect(ui.pushButtonSet, SIGNAL(clicked()), this, SLOT(slot_DASetClicked()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this , SLOT(slot_CancelClicked()));
	connect(ui.comboBoxIset,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeISet(int)));
	connect(ui.lineEditI, SIGNAL(editingFinished()), this, SLOT(slot_lne_IChanged()));
// 	connect(ui.combo_Fibers, SIGNAL(currentIndexChanged(int)),this,SLOT(slot_1588FiberSet(int)));
// 	connect(ui.lineEdit_LowSignal, SIGNAL(editingFinished()), this, SLOT(slot_lne_LowSignalChanged()));
	connect(ui.lineEdit_StabTime, SIGNAL(editingFinished()), this, SLOT(slot_lne_StabTimeChanged()));
	connect(ui.lineEdit_VNom, SIGNAL(editingFinished()), this, SLOT(slot_lne_VNomChanged()));
	connect(ui.lineEdit_INom, SIGNAL(editingFinished()), this, SLOT(slot_lne_INomChanged()));
	connect(ui.lineEdit_FNom, SIGNAL(editingFinished()), this, SLOT(slot_lne_FNomChanged()));
}

void DASetDialog::setData(STT_SystemParas* pSystemParas)
{
	ASSERT(pSystemParas != NULL);
	m_pSystemParas = pSystemParas;

// 	ui.comboBoxIset->setCurrentIndex(m_pSystemParas->m_oIPowerMode.m_nIPowerMode);
// 	if(m_pSystemParas->m_oIPowerMode.m_nIPowerMode == STT_CurrentMODULE_POWER_OTHER)
// 	{
// 		ui.lineEditI->setText( QString("%1").arg(m_pSystemParas->m_oIPowerMode.m_fVoltSet, 0, 'f', 2));
// 	}

// 	ui.combo_Fibers->setCurrentIndex(m_pSystemParas->m_n588InPort);
// 	ui.lineEdit_LowSignal->setText(QString::number(m_pSystemParas->m_nWSgnMode,10));
// 	ui.checkBox_BigCurr->setChecked(m_pSystemParas->m_bIout_ChansMergeOne);
// 	ui.checkBox_6ITo3I->setChecked(m_pSystemParas->m_bIout_ChansMergeThree);
	ui.checkBox_Analog->setChecked(m_pSystemParas->m_nHasAnalog);
	ui.checkBox_Digit->setChecked(m_pSystemParas->m_nHasDigital);
	ui.checkBox_Week->setChecked(m_pSystemParas->m_nHasWeek);
	ui.lineEdit_VNom->setText(QString("%1").arg(m_pSystemParas->m_fVNom, 0, 'f', 2));
	ui.lineEdit_INom->setText(QString("%1").arg(m_pSystemParas->m_fINom, 0, 'f', 2));
	ui.lineEdit_FNom->setText(QString("%1").arg(m_pSystemParas->m_fFNom, 0, 'f', 2));
	ui.lineEdit_StabTime->setText(QString("%1").arg(m_pSystemParas->m_fStabTime,0, 'f', 2));
}

void DASetDialog::slot_changeISet(int nISet)
{
	m_nIPowerMode = nISet;
// 	m_pSystemParas->m_oIPowerMode.m_nChMax = 12.5;
// 
// 	if (nISet == STT_CurrentMODULE_POWER_LOW || nISet == STT_CurrentMODULE_POWER_MIDDLE || nISet == STT_CurrentMODULE_POWER_HIGH)
// 	{
// 		ui.lineEditI->setDisabled(true);
// 
// 		ui.lineEditI->setText( QString("") );
// 		m_pSystemParas->m_oIPowerMode.m_fVoltSet = 0;
// 	}
// 	else if (nISet == STT_CurrentMODULE_POWER_OTHER)
// 	{
// 		ui.lineEditI->setDisabled(false);
// 	}
}

void DASetDialog::slot_lne_IChanged()
{
	double val =  ui.lineEditI->text().toDouble();
	if(val<0.3)
	{
		val = 0.3;
	}

	if (val>8.5)
	{
		val = 8.5;
	}

	ui.lineEditI->setText( QString("%1").arg(val, 0, 'f', 2) );
}

// void DASetDialog::slot_1588FiberSet(int nFiber)
// {
// 	m_nFiber = nFiber;
// }
// 
// void DASetDialog::slot_lne_LowSignalChanged()
// {
// 	int val = ui.lineEdit_LowSignal->text().toInt();
// 	ui.lineEdit_LowSignal->setText(QString::number(val,10));
// }

void DASetDialog::slot_lne_StabTimeChanged()
{
	QString str = ui.lineEdit_StabTime->text();
	double fv = str.toInt();
	if(fv < 0)
	{
		fv = 0;
	}

	ui.lineEdit_StabTime->setText( QString("%1").arg(fv, 0, 'f', 2) );
}

void DASetDialog::slot_lne_VNomChanged()
{
	QString str = ui.lineEdit_VNom->text();
	float fv = str.toFloat();
	if(fv < 0)
	{
		fv = 0;
	}

	ui.lineEdit_VNom->setText(QString::number(fv,'f',3));
}

void DASetDialog::slot_lne_INomChanged()
{
	QString str = ui.lineEdit_INom->text();
	float fv = str.toFloat();
	if(fv < 0)
	{
		fv = 0;
	}

	ui.lineEdit_INom->setText(QString::number(fv,'f',3));
}

void DASetDialog::slot_lne_FNomChanged()
{
	QString str = ui.lineEdit_FNom->text();
	float fv = str.toFloat();
	if(fv < 0)
	{
		fv = 0;
	}

	ui.lineEdit_FNom->setText(QString::number(fv,'f',2));
}

void DASetDialog::slot_DASetClicked()
{
	long nCheckState = ui.checkBox_Analog->isChecked();

	if (m_pSystemParas->m_nHasAnalog != nCheckState)
	{
		m_bChanged = TRUE;
		m_pSystemParas->m_nHasAnalog = nCheckState;
	}

	nCheckState = ui.checkBox_Digit->isChecked();

	if (m_pSystemParas->m_nHasDigital != nCheckState)
	{
		m_bChanged = TRUE;
		m_pSystemParas->m_nHasDigital = nCheckState;
	}

	nCheckState = ui.checkBox_Week->isChecked();

	if (m_pSystemParas->m_nHasWeek != nCheckState)
	{
		m_bChanged = TRUE;
		m_pSystemParas->m_nHasWeek = nCheckState;
	}

	if (m_pSystemParas->m_fVNom != ui.lineEdit_VNom->text().toFloat())
	{
		m_bChanged = TRUE;
		m_pSystemParas->m_fVNom = ui.lineEdit_VNom->text().toFloat();
	}

	if (m_pSystemParas->m_fINom != ui.lineEdit_INom->text().toFloat())
	{
		m_bChanged = TRUE;
		m_pSystemParas->m_fINom = ui.lineEdit_INom->text().toFloat();
	}
	
	if (m_pSystemParas->m_fFNom != ui.lineEdit_FNom->text().toFloat())
	{
		m_bChanged = TRUE;
		m_pSystemParas->m_fFNom = ui.lineEdit_FNom->text().toFloat();
	}
	
// 	if (m_pSystemParas->m_n588InPort != m_nFiber)
// 	{
// 		m_bChanged = TRUE;
// 		m_pSystemParas->m_n588InPort = m_nFiber;
// 	}

// 	if (m_pSystemParas->m_bIout_ChansMergeThree != ui.checkBox_6ITo3I->isChecked())
// 	{
// 		m_bChanged = TRUE;
// 		m_pSystemParas->m_bIout_ChansMergeThree = ui.checkBox_6ITo3I->isChecked();
// 	}
// 
// 	if (m_pSystemParas->m_bIout_ChansMergeOne != ui.checkBox_BigCurr->isChecked())
// 	{
// 		m_bChanged = TRUE;
// 		m_pSystemParas->m_bIout_ChansMergeOne = ui.checkBox_BigCurr->isChecked();
// 	}

// 	if (m_pSystemParas->m_oIPowerMode.m_nIPowerMode != m_nIPowerMode)
// 	{
// 		m_bChanged = TRUE;
// 		m_pSystemParas->m_oIPowerMode.m_nIPowerMode = m_nIPowerMode;
// 	}

// 	int nVal = ui.lineEdit_LowSignal->text().toInt();
// 	if(m_pSystemParas->m_nWSgnMode != nVal)
// 	{
// 		m_bChanged = TRUE;
// 		m_pSystemParas->m_nWSgnMode = nVal;
// 	}

// 	float fv =  ui.lineEditI->text().toFloat();
// 	if(m_pSystemParas->m_oIPowerMode.m_fVoltSet != fv)
// 	{
// 		m_bChanged = TRUE;
// 		m_pSystemParas->m_oIPowerMode.m_fVoltSet = fv;
// 	}

// 	fv = ui.lineEdit_StabTime->text().toFloat();
// 	if (m_pSystemParas->m_fStabTime != fv)
// 	{
// 		m_bChanged = TRUE;
// 		m_pSystemParas->m_fStabTime = fv;
//	}
	
//	emit sig_DASetClicked(m_bChanged);

	close();
}

void DASetDialog::slot_CancelClicked()
{
	close();
}