#include "SequenceGradientSettingDlg.h"
#include "ui_SequenceGradientSettingDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTestSysGlobalPara.h"
#include "../Module/SttUIDefine.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
//#include "../SttTestCntrFrameBase.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"
#include "../../Module/XLangResource_Native.h"

QSequenceGradientSettingDlg::QSequenceGradientSettingDlg(tmt_GradientParasEx *pSequenceGradient, QWidget *parent):
QDialog(parent), ui(new Ui::QSequenceGradientSettingDlg)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_nIsOK = 0;
	m_pSequenceGradientParas = pSequenceGradient;
	InitStyle();
	InitLanguage();
	InitPara();
	InitConnections();
	SetSequenceGradientSettingFont();
	ui->tabWidget->removeTab(0);
	
}

QSequenceGradientSettingDlg::~QSequenceGradientSettingDlg()
{
	delete ui;
}

void QSequenceGradientSettingDlg::InitLanguage()
{
	CString strText;
	xlang_GetLangStrByFile(strText, "Native_LogicAnd");
	ui->m_rbAnd->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_LogicOr");
	ui->m_rbOr->setText(strText);
	ui->tabWidget->setTabText(NUM_ZERO,g_sLangTxt_Native_Bin);//开入量LCQ
	ui->tabWidget->setTabText(NUM_ONE,g_sLangTxt_Native_Bout);  //开出量LCQ

	xlang_SetLangStrToWidget(ui->m_gbNormal, "Gradient_Normal", XLang_Ctrls_QGroupBox);//正常态
	xlang_SetLangStrToWidget(ui->m_gbError, "Gradient_Failure", XLang_Ctrls_QGroupBox);//故障态

	xlang_SetLangStrToWidget(ui->m_btnOK, "sOK", XLang_Ctrls_QPushButton);//确认和取消按钮的功能
	xlang_SetLangStrToWidget(ui->m_btnCancel, "sCancel", XLang_Ctrls_QPushButton);
	xlang_GetLangStrByFile(strText, "Native_BinX");
	ui->m_cbBinA->setText(strText + "A");
	ui->m_cbBinB->setText(strText + "B");
	ui->m_cbBinC->setText(strText + "C");
	ui->m_cbBinD->setText(strText + "D");
	ui->m_cbBinE->setText(strText + "E");
	ui->m_cbBinF->setText(strText + "F");
	ui->m_cbBinG->setText(strText + "G");
	ui->m_cbBinH->setText(strText + "H");
	ui->m_cbBinI->setText(strText + "I");
	ui->m_cbBinJ->setText(strText + "J");

	xlang_GetLangStrByFile(strText, "Native_BoutX");
	ui->m_cbBOut1->setText(strText + "1");
	ui->m_cbBOut2->setText(strText + "2");
	ui->m_cbBOut3->setText(strText + "3");
	ui->m_cbBOut4->setText(strText + "4");
	ui->m_cbBOut5->setText(strText + "5");
	ui->m_cbBOut6->setText(strText + "6");
	ui->m_cbBOut7->setText(strText + "7");
	ui->m_cbBOut8->setText(strText + "8");
	ui->m_cbBOut9->setText(strText + "9");
	ui->m_cbBOut10->setText(strText + "10");

	ui->m_cbBOut1_E->setText(strText + "1");
	ui->m_cbBOut2_E->setText(strText + "2");
	ui->m_cbBOut3_E->setText(strText + "3");
	ui->m_cbBOut4_E->setText(strText + "4");
	ui->m_cbBOut5_E->setText(strText + "5");
	ui->m_cbBOut6_E->setText(strText + "6");
	ui->m_cbBOut7_E->setText(strText + "7");
	ui->m_cbBOut8_E->setText(strText + "8");
	ui->m_cbBOut9_E->setText(strText + "9");
	ui->m_cbBOut10_E->setText(strText + "10");

}

void QSequenceGradientSettingDlg::InitPara()
{
	//开入量
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinA,m_pSequenceGradientParas->m_binIn,0);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinB,m_pSequenceGradientParas->m_binIn,1);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinC,m_pSequenceGradientParas->m_binIn,2);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinD,m_pSequenceGradientParas->m_binIn,3);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinE,m_pSequenceGradientParas->m_binIn,4);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinF,m_pSequenceGradientParas->m_binIn,5);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinG,m_pSequenceGradientParas->m_binIn,6);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinH,m_pSequenceGradientParas->m_binIn,7);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinI,m_pSequenceGradientParas->m_binIn,8);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinJ,m_pSequenceGradientParas->m_binIn,9);
	//常态开出量
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut1,m_pSequenceGradientParas->m_binOut[0],0);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut2,m_pSequenceGradientParas->m_binOut[0],1);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut3,m_pSequenceGradientParas->m_binOut[0],2);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut4,m_pSequenceGradientParas->m_binOut[0],3);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut5,m_pSequenceGradientParas->m_binOut[0],4);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut6,m_pSequenceGradientParas->m_binOut[0],5);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut7,m_pSequenceGradientParas->m_binOut[0],6);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut8,m_pSequenceGradientParas->m_binOut[0],7);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut9,m_pSequenceGradientParas->m_binOut[0],8);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut10,m_pSequenceGradientParas->m_binOut[0],9);
	//故障态开出量设置
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut1_E,m_pSequenceGradientParas->m_binOut[1],0);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut2_E,m_pSequenceGradientParas->m_binOut[1],1);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut3_E,m_pSequenceGradientParas->m_binOut[1],2);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut4_E,m_pSequenceGradientParas->m_binOut[1],3);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut5_E,m_pSequenceGradientParas->m_binOut[1],4);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut6_E,m_pSequenceGradientParas->m_binOut[1],5);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut7_E,m_pSequenceGradientParas->m_binOut[1],6);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut8_E,m_pSequenceGradientParas->m_binOut[1],7);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut9_E,m_pSequenceGradientParas->m_binOut[1],8);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut10_E,m_pSequenceGradientParas->m_binOut[1],9);

	if (m_pSequenceGradientParas->m_nBinLogic)
	{
		ui->m_rbAnd->setChecked(true);
	}
	else
	{
		ui->m_rbOr->setChecked(true);
	}
}

void QSequenceGradientSettingDlg::InitConnections()
{
	connect(ui->m_cbBinA, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbBinB, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbBinC, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbBinD, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbBinE, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbBinF, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbBinG, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbBinH, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbBinI, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));
	connect(ui->m_cbBinJ, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_BinaryInStateChanged(int)));

}

void QSequenceGradientSettingDlg::SetSequenceGradientSettingFont()
{
	ui->m_cbBinA->setFont(*g_pSttGlobalFont);
	ui->m_cbBinB->setFont(*g_pSttGlobalFont);
	ui->m_cbBinC->setFont(*g_pSttGlobalFont);
	ui->m_cbBinD->setFont(*g_pSttGlobalFont);
	ui->m_cbBinE->setFont(*g_pSttGlobalFont);
	ui->m_cbBinF->setFont(*g_pSttGlobalFont);
	ui->m_cbBinG->setFont(*g_pSttGlobalFont);
	ui->m_cbBinI->setFont(*g_pSttGlobalFont);
	ui->m_cbBinH->setFont(*g_pSttGlobalFont);
	ui->m_cbBinJ->setFont(*g_pSttGlobalFont);

	ui->m_rbAnd->setFont(*g_pSttGlobalFont);
	ui->m_rbOr->setFont(*g_pSttGlobalFont);
	ui->m_tabBOut->setFont(*g_pSttGlobalFont);
	ui->m_gbNormal->setFont(*g_pSttGlobalFont);

	ui->m_cbBOut1->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut2->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut3->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut4->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut5->setFont(*g_pSttGlobalFont);	
	ui->m_cbBOut6->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut7->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut8->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut9->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut10->setFont(*g_pSttGlobalFont);
	ui->m_gbError->setFont(*g_pSttGlobalFont);

	ui->m_cbBOut1_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut2_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut3_E->setFont(*g_pSttGlobalFont);	
	ui->m_cbBOut4_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut5_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut6_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut7_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut8_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut9_E->setFont(*g_pSttGlobalFont);
	ui->m_cbBOut10_E->setFont(*g_pSttGlobalFont);

	ui->m_btnOK->setFont(*g_pSttGlobalFont);	
	ui->m_btnCancel->setFont(*g_pSttGlobalFont);

	ui->tabWidget->setFont(*g_pSttGlobalFont);
}

void QSequenceGradientSettingDlg::InitStyle()
{
	((QSttTabWidget*)ui->tabWidget)->InitStyleSheet();

	((QSttCheckBox*)ui->m_cbBinA)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinB)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinC)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinD)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinE)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinF)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinG)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinH)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinI)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBinJ)->InitStyleSheet();

	((QSttCheckBox*)ui->m_cbBOut1)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut2)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut3)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut4)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut5)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut6)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut7)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut8)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut9)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut10)->InitStyleSheet();

	((QSttCheckBox*)ui->m_cbBOut1_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut2_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut3_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut4_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut5_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut6_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut7_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut8_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut9_E)->InitStyleSheet();
	((QSttCheckBox*)ui->m_cbBOut10_E)->InitStyleSheet();
}


void QSequenceGradientSettingDlg::on_m_btnOK_clicked()
{
	ExitHideKeyboardWidget();
	if (ui->m_cbBinA->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[0].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[0].nSelect = 0;
	}

	if (ui->m_cbBinB->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[1].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[1].nSelect = 0;
	}

	if (ui->m_cbBinC->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[2].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[2].nSelect = 0;
	}

	if (ui->m_cbBinD->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[3].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[3].nSelect = 0;
	}

	if (ui->m_cbBinE->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[4].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[4].nSelect = 0;
	}

	if (ui->m_cbBinF->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[5].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[5].nSelect = 0;
	}

	if (ui->m_cbBinG->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[6].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[6].nSelect = 0;
	}

	if (ui->m_cbBinH->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[7].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[7].nSelect = 0;
	}

	if (ui->m_cbBinI->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[8].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[8].nSelect = 0;
	}

	if (ui->m_cbBinJ->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binIn[9].nSelect = 1;
	}
	else
	{
		m_pSequenceGradientParas->m_binIn[9].nSelect = 0;
	}

	if (ui->m_rbAnd->isChecked())
	{
		m_pSequenceGradientParas->m_nBinLogic = 1;
	}

	if (ui->m_rbOr->isChecked())
	{
		m_pSequenceGradientParas->m_nBinLogic = 0;
	}

	if (ui->m_cbBOut1->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][0].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][0].nState = 0;
	}

	if (ui->m_cbBOut2->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][1].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][1].nState = 0;
	}

	if (ui->m_cbBOut3->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][2].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][2].nState = 0;
	}

	if (ui->m_cbBOut4->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][3].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][3].nState = 0;
	}

	if (ui->m_cbBOut5->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][4].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][4].nState = 0;
	}

	if (ui->m_cbBOut6->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][5].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][5].nState = 0;
	}

	if (ui->m_cbBOut7->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][6].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][6].nState = 0;
	}

	if (ui->m_cbBOut8->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][7].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][7].nState = 0;
	}

	if (ui->m_cbBOut9->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][8].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][8].nState = 0;
	}

	if (ui->m_cbBOut10->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[0][9].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[0][9].nState = 0;
	}

	if (ui->m_cbBOut1_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][0].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][0].nState = 0;
	}

	if (ui->m_cbBOut2_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][1].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][1].nState = 0;
	}

	if (ui->m_cbBOut3_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][2].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][2].nState = 0;
	}

	if (ui->m_cbBOut4_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][3].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][3].nState = 0;
	}

	if (ui->m_cbBOut5_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][4].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][4].nState = 0;
	}

	if (ui->m_cbBOut6_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][5].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][5].nState = 0;
	}

	if (ui->m_cbBOut7_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][6].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][6].nState = 0;
	}

	if (ui->m_cbBOut8_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][7].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][7].nState = 0;
	}

	if (ui->m_cbBOut9_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][8].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][8].nState = 0;
	}

	if (ui->m_cbBOut10_E->checkState() == Qt::Checked)
	{
		m_pSequenceGradientParas->m_binOut[1][9].nState = 1;
	} 
	else
	{
		m_pSequenceGradientParas->m_binOut[1][9].nState = 0;
	}

	close();
	m_nIsOK = 1;
}
void QSequenceGradientSettingDlg::on_m_btnCancel_clicked()
{
	ExitHideKeyboardWidget();
	close();
	m_nIsOK = 2;
}

void QSequenceGradientSettingDlg::slot_ck_BinaryInStateChanged(int )
{
	if (ui->m_cbBinA->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbBinB->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbBinC->checkState() == Qt::Checked)
	{
		return;
	}

	if (ui->m_cbBinD->checkState() ==  Qt::Checked)
	{
		return;
	}

	if (ui->m_cbBinE->checkState() ==  Qt::Checked)
	{
		return;
	}

	if (ui->m_cbBinF->checkState() ==  Qt::Checked)
	{
		return;
	}

	if (ui->m_cbBinG->checkState() ==  Qt::Checked)
	{
		return;
	}

	if (ui->m_cbBinH->checkState() ==  Qt::Checked)
	{
		return;
	}

	if (ui->m_cbBinI->checkState() ==  Qt::Checked)
	{
		return;
	}

	if (ui->m_cbBinJ->checkState() ==  Qt::Checked)
	{
		return;
	}

	ui->m_cbBinA->setCheckState(Qt::Checked);
}