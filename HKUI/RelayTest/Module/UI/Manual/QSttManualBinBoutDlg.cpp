#include "QSttManualBinBoutDlg.h"
#include "ui_QSttManualBinBoutDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTestSysGlobalPara.h"
#include "../Module/SttUIDefine.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../SttTestCntrFrameAPI.h"
#include "../Controls/SttCheckBox.h"
#include"../../Module/XLangResource_Native.h"

QSttManualBinBoutDlg::QSttManualBinBoutDlg(tmt_BinaryIn *pBinaryIn,tmt_BinaryOut *pBinaryOut,
										   int *pnBinLogic,float *pfTrigDelay,BOOL *pbAuto, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttManualBinBoutDlg)
{
    ui->setupUi(this);
	m_pBinaryIn = pBinaryIn;
	m_pBinaryOut = pBinaryOut;
	m_pnBinLogic = pnBinLogic;
	m_pfTrigDelay = pfTrigDelay;
	m_pbAuto = pbAuto;
//	m_nIsOK = 0;

	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	

	//CString strText;
	//strText = _T("开关量设置");
	//xlang_GetLangStrByFile(g_sLangTxt_State_SwitchSet,"State_SwitchSet");//开关量设置（Dlg)-LCQ
	setWindowTitle(g_sLangTxt_Native_Switch);

	InitStyle();
	InitLanguage();
	InitPara();
	InitConnections();
	SetInBinaryOutSettingFont();
}

QSttManualBinBoutDlg::~QSttManualBinBoutDlg()
{
	delete ui;
}

void QSttManualBinBoutDlg::InitStyle()
{
	((QSttCheckBox*)ui->m_cbInA)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbInB)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbInC)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbInD)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbInE)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbInF)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbInG)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbInH)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbInI)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbInJ)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbOut5)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbOut6)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbOut7)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbOut8)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbOut9)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbOut10)->InitStyleSheet();
}

void QSttManualBinBoutDlg::InitLanguage()
{
	/*CString strText;
	xlang_GetLangStrByFile(strText, "Native_BinX");*/
	
	xlang_SetLangStrToWidget(ui->m_boxInSetting, "Native_Bin", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(ui->m_boxOutSetting, "Native_Bout", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget_Txt(ui->m_btnOK,g_sLangTxt_OK,XLang_Ctrls_QPushButton); //确定—LCQ
    xlang_SetLangStrToWidget_Txt(ui->m_btnCancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);//取消-LCQ
    xlang_SetLangStrToWidget_Txt(ui->m_rdOr,g_sLangTxt_Native_LogicOr,XLang_Ctrls_QRadioButton);//逻辑或—LCQ
	xlang_SetLangStrToWidget_Txt(ui->m_rdAnd,g_sLangTxt_Native_LogicAnd ,XLang_Ctrls_QRadioButton);//逻辑与—LCQ
	xlang_SetLangStrToWidget_Txt(ui->m_labDelayed,g_sLangTxt_Manual_Delayed,XLang_Ctrls_QLabel);//触发后延时—LCQ
}

void QSttManualBinBoutDlg::InitPara()
{
	GlobalSetQcheckState_BinaryIn(ui->m_cbInA,m_pBinaryIn,0);
	GlobalSetQcheckState_BinaryIn(ui->m_cbInB,m_pBinaryIn,1);
	GlobalSetQcheckState_BinaryIn(ui->m_cbInC,m_pBinaryIn,2);
	GlobalSetQcheckState_BinaryIn(ui->m_cbInD,m_pBinaryIn,3);
	GlobalSetQcheckState_BinaryIn(ui->m_cbInE,m_pBinaryIn,4);
	GlobalSetQcheckState_BinaryIn(ui->m_cbInF,m_pBinaryIn,5);
	GlobalSetQcheckState_BinaryIn(ui->m_cbInG,m_pBinaryIn,6);
	GlobalSetQcheckState_BinaryIn(ui->m_cbInH,m_pBinaryIn,7);
	GlobalSetQcheckState_BinaryIn(ui->m_cbInI,m_pBinaryIn,8);
	GlobalSetQcheckState_BinaryIn(ui->m_cbInJ,m_pBinaryIn,9);

	GlobalSetQcheckState_BinaryOut(ui->m_cbOut5,m_pBinaryOut,4);
	GlobalSetQcheckState_BinaryOut(ui->m_cbOut6,m_pBinaryOut,5);
	GlobalSetQcheckState_BinaryOut(ui->m_cbOut7,m_pBinaryOut,6);
	GlobalSetQcheckState_BinaryOut(ui->m_cbOut8,m_pBinaryOut,7);
	GlobalSetQcheckState_BinaryOut(ui->m_cbOut9,m_pBinaryOut,8);
	GlobalSetQcheckState_BinaryOut(ui->m_cbOut10,m_pBinaryOut,9);

	if(*m_pnBinLogic)
	{
		ui->m_rdAnd->setChecked(true);
	}
	else
	{
		ui->m_rdOr->setChecked(true);
	}

	ui->m_editDelayed->setText(QString::number(*m_pfTrigDelay,'f',2));

	if (*m_pbAuto == true)
	{
		ui->m_editDelayed->setEnabled(false);
	}
}

void QSttManualBinBoutDlg::InitConnections()
{
	connect(ui->m_cbInA, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbInB, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbInC, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbInD, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbInE, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbInF, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbInG, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbInH, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbInI, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbInJ, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));

}

void QSttManualBinBoutDlg::SetInBinaryOutSettingFont()
{
	ui->m_cbInA->setFont(*g_pSttGlobalFont);
	ui->m_cbInB->setFont(*g_pSttGlobalFont);
	ui->m_cbInC->setFont(*g_pSttGlobalFont);
	ui->m_cbInD->setFont(*g_pSttGlobalFont);
	ui->m_cbInE->setFont(*g_pSttGlobalFont);
	ui->m_cbInF->setFont(*g_pSttGlobalFont);
	ui->m_cbInG->setFont(*g_pSttGlobalFont);
	ui->m_cbInI->setFont(*g_pSttGlobalFont);
	ui->m_cbInH->setFont(*g_pSttGlobalFont);
	ui->m_cbInJ->setFont(*g_pSttGlobalFont);

	ui->m_rdAnd->setFont(*g_pSttGlobalFont);
	ui->m_rdOr->setFont(*g_pSttGlobalFont);

	ui->m_cbOut5->setFont(*g_pSttGlobalFont);	
	ui->m_cbOut6->setFont(*g_pSttGlobalFont);
	ui->m_cbOut7->setFont(*g_pSttGlobalFont);
	ui->m_cbOut8->setFont(*g_pSttGlobalFont);
	ui->m_cbOut9->setFont(*g_pSttGlobalFont);
	ui->m_cbOut10->setFont(*g_pSttGlobalFont);

	ui->m_labDelayed->setFont(*g_pSttGlobalFont);
	ui->m_editDelayed->setFont(*g_pSttGlobalFont);

	ui->m_btnOK->setFont(*g_pSttGlobalFont);
	ui->m_btnCancel->setFont(*g_pSttGlobalFont);

	ui->m_boxInSetting->setFont(*g_pSttGlobalFont);
	ui->m_boxOutSetting->setFont(*g_pSttGlobalFont);
}

void QSttManualBinBoutDlg::on_m_btnOK_clicked()
{
	ExitHideKeyboardWidget();
	if (ui->m_cbInA->checkState() == Qt::Checked)
	{
		m_pBinaryIn[0].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[0].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[0].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[0].nSelect = 0;
	}
	if (ui->m_cbInB->checkState() == Qt::Checked)
	{
		m_pBinaryIn[1].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[1].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[1].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[1].nSelect = 0;
	}
	if (ui->m_cbInC->checkState() == Qt::Checked)
	{
		m_pBinaryIn[2].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[2].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[2].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[2].nSelect = 0;
	}
	if (ui->m_cbInD->checkState() == Qt::Checked)
	{
		m_pBinaryIn[3].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[3].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[3].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[3].nSelect = 0;
	}
	if (ui->m_cbInE->checkState() == Qt::Checked)
	{
		m_pBinaryIn[4].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[4].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[4].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[4].nSelect = 0;
	}
	if (ui->m_cbInF->checkState() == Qt::Checked)
	{
		m_pBinaryIn[5].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[5].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[5].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[5].nSelect = 0;
	}
	if (ui->m_cbInG->checkState() == Qt::Checked)
	{
		m_pBinaryIn[6].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[6].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[6].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[6].nSelect = 0;
	}
	if (ui->m_cbInH->checkState() == Qt::Checked)
	{
		m_pBinaryIn[7].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[7].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[7].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[7].nSelect = 0;
	}
	if (ui->m_cbInI->checkState() == Qt::Checked)
	{
		m_pBinaryIn[8].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[8].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[8].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[8].nSelect = 0;
	}
	if (ui->m_cbInJ->checkState() == Qt::Checked)
	{
		m_pBinaryIn[9].nSelect = 1;
		stt_GetBinaryConfig()->m_binIn[9].nSelect = 1;
	}
	else
	{
		m_pBinaryIn[9].nSelect = 0;
		stt_GetBinaryConfig()->m_binIn[9].nSelect = 0;
	}
	if (ui->m_rdOr->isChecked())
	{
		*m_pnBinLogic = 0;
	}
	else
	{
		*m_pnBinLogic = 1;
	}
	if (ui->m_rdAnd->isChecked())
	{
		*m_pnBinLogic = 1;
	}
	else
	{
		*m_pnBinLogic = 0;
	}
	if (ui->m_cbOut5->checkState() == Qt::Checked)
	{
		m_pBinaryOut[4].nState = 1;
	}
	else
	{
		m_pBinaryOut[4].nState = 0;
	}
	if (ui->m_cbOut6->checkState() == Qt::Checked)
	{
		m_pBinaryOut[5].nState = 1;
	}
	else
	{
		m_pBinaryOut[5].nState = 0;
	}
	if (ui->m_cbOut7->checkState() == Qt::Checked)
	{
		m_pBinaryOut[6].nState = 1;
	}
	else
	{
		m_pBinaryOut[6].nState = 0;
	}
	if (ui->m_cbOut8->checkState() == Qt::Checked)
	{
		m_pBinaryOut[7].nState = 1;
	}
	else
	{
		m_pBinaryOut[7].nState = 0;
	}
	if (ui->m_cbOut9->checkState() == Qt::Checked)
	{
		m_pBinaryOut[8].nState = 1;
	}
	else
	{
		m_pBinaryOut[8].nState = 0;
	}
	if (ui->m_cbOut10->checkState() == Qt::Checked)
	{
		m_pBinaryOut[9].nState = 1;
	}
	else
	{
		m_pBinaryOut[9].nState = 0;
	}
	
//	m_nIsOK = 1;
	this->accept();
}

void QSttManualBinBoutDlg::on_m_btnCancel_clicked()
{
	ExitHideKeyboardWidget();
	close();
//	m_nIsOK = 2;
}

void QSttManualBinBoutDlg::slot_ck_BinaryInStateChanged(int idx)
{
	if (ui->m_cbInA->checkState() == Qt::Checked)
	{
		return;
	}
	if (ui->m_cbInB->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbInC->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbInD->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbInE->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbInF->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbInG->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbInH->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbInI->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbInJ->checkState() == Qt::Checked)
	{
		return;
	}
}

void QSttManualBinBoutDlg::on_m_editDelayChanged()
{
	if(ui->m_editDelayed->text().isEmpty())
	{
		ui->m_editDelayed->setText("0.00");
	}
	QString str = ui->m_editDelayed->text();
	GetWidgetBoard_DigitData(4,str,ui->m_editDelayed,this);
}

void QSttManualBinBoutDlg::slot_lne_delayedChanged()
{
	QString str = ui->m_editDelayed->text();
	if(str.right(1).contains("."))
	{
		str.append("00");
	}
	float fv = str.toFloat();
	fv=setLimit(0,999.999,fv);

	if (*m_pfTrigDelay != fv)
	{
		*m_pfTrigDelay = fv;
		//m_pSttMacroParaEditViewOriginal.m_bTmtParaChanged = TRUE;
	}
	ui->m_editDelayed->setText(QString::number(*m_pfTrigDelay,'f',2));
}

void QSttManualBinBoutDlg::on_m_editDelayed_editingFinished()
{
	if(ui->m_editDelayed->text().isEmpty())
	{
		ui->m_editDelayed->setText("0.00");
	}

	slot_lne_delayedChanged();
	
}

void QSttManualBinBoutDlg::DelayedSetVisible()
{
	ui->m_GroupDelayed->setVisible(false);
}


