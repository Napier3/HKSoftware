#include "GradientSettingDlg.h"
#include "ui_GradientSettingDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttTestSysGlobalPara.h"
#include "../Module/SttUIDefine.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
//#include "../SttTestCntrFrameBase.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttTabWidget.h"
#include "../../Module/XLangResource_Native.h"

QGradientSettingDlg::QGradientSettingDlg(tmt_GradientParasEx *pGradientParas, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::QGradientSettingDlg)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_nIsOK = 0;
	m_pGradientParas = pGradientParas;
	InitStyle();
	InitLanguage();
	InitPara();
	InitConnections();
	SetGradientSettingFont();

	ui->tabWidget->removeTab(0);
}

QGradientSettingDlg::~QGradientSettingDlg()
{
	delete ui;
}

void QGradientSettingDlg::SetGradientSettingFont()//设置字体
{
	//ui->m_labTimeBeforeChange->setFont(*g_pSttGlobalFont);
	//ui->m_editTimeBeforeChange->setFont(*g_pSttGlobalFont);
	//ui->m_labTimeBeforeFail->setFont(*g_pSttGlobalFont);
	//ui->m_editTimeBeforeFail->setFont(*g_pSttGlobalFont);
	//ui->m_labCurBeforeChange->setFont(*g_pSttGlobalFont);

	//ui->m_labPhase->setFont(*g_pSttGlobalFont);
	//ui->m_editPhase->setFont(*g_pSttGlobalFont);
	//ui->m_editCurBeforeChange->setFont(*g_pSttGlobalFont);
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

void QGradientSettingDlg::InitStyle()
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

void QGradientSettingDlg::on_m_btnOK_clicked()
{
	ExitHideKeyboardWidget();
	/*m_pGradientParas->m_fPrepareTime = ui->m_editTimeBeforeChange->text().toFloat();	//准备时间
	m_pGradientParas->m_fPreFaultTime = ui->m_editTimeBeforeFail->text().toFloat();	//故障前时间
	m_pGradientParas->m_fEDI = ui->m_editCurBeforeChange->text().toFloat();						//变化前电流I0
	m_pGradientParas->m_fEDUaIaAngle = ui->m_editPhase->text().toFloat();*///（参数传递，移走）

	if (ui->m_cbBinA->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[0].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[0].nSelect = 0;
	}

	if (ui->m_cbBinB->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[1].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[1].nSelect = 0;
	}

	if (ui->m_cbBinC->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[2].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[2].nSelect = 0;
	}

	if (ui->m_cbBinD->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[3].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[3].nSelect = 0;
	}

	if (ui->m_cbBinE->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[4].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[4].nSelect = 0;
	}

	if (ui->m_cbBinF->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[5].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[5].nSelect = 0;
	}

	if (ui->m_cbBinG->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[6].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[6].nSelect = 0;
	}

	if (ui->m_cbBinH->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[7].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[7].nSelect = 0;
	}

	if (ui->m_cbBinI->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[8].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[8].nSelect = 0;
	}

	if (ui->m_cbBinJ->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binIn[9].nSelect = 1;
	}
	else
	{
		m_pGradientParas->m_binIn[9].nSelect = 0;
	}

	if (ui->m_rbAnd->isChecked())
	{
		m_pGradientParas->m_nBinLogic = 1;
	}

	if (ui->m_rbOr->isChecked())
	{
		m_pGradientParas->m_nBinLogic = 0;
	}

	if (ui->m_cbBOut1->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][0].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][0].nState = 0;
	}

	if (ui->m_cbBOut2->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][1].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][1].nState = 0;
	}

	if (ui->m_cbBOut3->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][2].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][2].nState = 0;
	}

	if (ui->m_cbBOut4->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][3].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][3].nState = 0;
	}

	if (ui->m_cbBOut5->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][4].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][4].nState = 0;
	}

	if (ui->m_cbBOut6->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][5].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][5].nState = 0;
	}

	if (ui->m_cbBOut7->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][6].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][6].nState = 0;
	}

	if (ui->m_cbBOut8->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][7].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][7].nState = 0;
	}

	if (ui->m_cbBOut9->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][8].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][8].nState = 0;
	}

	if (ui->m_cbBOut10->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[0][9].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[0][9].nState = 0;
	}

	if (ui->m_cbBOut1_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][0].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][0].nState = 0;
	}

	if (ui->m_cbBOut2_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][1].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][1].nState = 0;
	}

	if (ui->m_cbBOut3_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][2].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][2].nState = 0;
	}

	if (ui->m_cbBOut4_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][3].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][3].nState = 0;
	}

	if (ui->m_cbBOut5_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][4].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][4].nState = 0;
	}

	if (ui->m_cbBOut6_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][5].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][5].nState = 0;
	}

	if (ui->m_cbBOut7_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][6].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][6].nState = 0;
	}

	if (ui->m_cbBOut8_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][7].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][7].nState = 0;
	}

	if (ui->m_cbBOut9_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][8].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][8].nState = 0;
	}

	if (ui->m_cbBOut10_E->checkState() == Qt::Checked)
	{
		m_pGradientParas->m_binOut[1][9].nState = 1;
	}
	else
	{
		m_pGradientParas->m_binOut[1][9].nState = 0;
	}

	close();
	m_nIsOK = 1;
}

void QGradientSettingDlg::on_m_btnCancel_clicked()
{
	ExitHideKeyboardWidget();
	close();
	m_nIsOK = 2;
}

// void InitUI()
//{
//	initMaxPositiveEdit(ui->lne_XD);
//	initMaxPositiveEdit(ui->lne_JD);
//	initMaxPositiveEdit(ui->lne_coeff);
//}

void QGradientSettingDlg::InitLanguage()
{
    CString strText;
	/*xlang_GetLangStrByFile(strText, "Gradient_TimeBeforeChange");//？？？文本类型翻译转换？
	ui->m_labTimeBeforeChange->setText(strText + "(s):");
	xlang_GetLangStrByFile(strText, "Gradient_TimeBeforeFail");
	ui->m_labTimeBeforeFail->setText(strText + "(s):");
	xlang_GetLangStrByFile(strText, "Gradient_CurBeforeChange");
	ui->m_labCurBeforeChange->setText(strText + "(A):");*/

	xlang_GetLangStrByFile(strText, "Native_LogicAnd");
	ui->m_rbAnd->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_LogicOr");
	ui->m_rbOr->setText(strText);

	//xlang_SetLangStrToWidget(ui->m_tabManual, "Native_CommonPara", XLang_Ctrls_QTabWidget);
	//xlang_SetLangStrToWidget(ui->m_tabBIn, "Native_Bin", XLang_Ctrls_QTabWidget);
	//xlang_SetLangStrToWidget(ui->m_tabBOut, "Native_Bout", XLang_Ctrls_QTabWidget);
         
    ui->tabWidget->setTabText(NUM_ZERO,g_sLangTxt_Native_Bin);//开入量LCQ
    ui->tabWidget->setTabText(NUM_ONE,g_sLangTxt_Native_Bout);  //开出量LCQ

	xlang_SetLangStrToWidget(ui->m_gbNormal, "Gradient_Normal", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(ui->m_gbError, "Gradient_Failure", XLang_Ctrls_QGroupBox);
	ui->m_gbNormal->setTitle(g_sLangTxt_Gradient_Normal);
	ui->m_gbError->setTitle(g_sLangTxt_Gradient_Failure);
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

BOOL Global_BinaryInHasChecked(QCheckBox *pBinaryInCheck)
{
	if (!pBinaryInCheck->isEnabled())
	{
		return FALSE;
	}

	if (pBinaryInCheck->checkState() == Qt::Checked)
	{
		return TRUE;
	}

	return FALSE;
}

void QGradientSettingDlg::InitPara()
{
	/*initMaxPositiveEdit(ui->m_editTimeBeforeChange);
	initMaxPositiveEdit(ui->m_editTimeBeforeFail);
	initMaxPositiveEdit(ui->m_editCurBeforeChange);
	initMaxEdit_one(ui->m_editPhase);

	ui->m_editTimeBeforeChange->setText(QString::number(m_pGradientParas->m_fPrepareTime,'f',3));
	ui->m_editTimeBeforeFail->setText(QString::number(m_pGradientParas->m_fPreFaultTime,'f',3));
	m_pGradientParas->m_fEDU = g_oSystemParas.m_fVNom / G3;
	ui->m_editCurBeforeChange->setText(QString::number(m_pGradientParas->m_fEDI,'f',3));
	ui->m_editPhase->setText(QString::number(m_pGradientParas->m_fEDUaIaAngle,'f',1));
	m_pGradientParas->m_fEDFreq = g_oSystemParas.m_fFNom;*/

// 	ui->m_editTimeBeforeChange->setToolTip(QString("PrepareTime"));
// 	ui->m_editTimeBeforeFail->setToolTip(QString("PreFaultTime"));
// 	ui->m_editCurBeforeChange->setToolTip(QString("I0"));
// 	ui->m_editPhase->setToolTip(QString("Phi0"));

	GlobalSetQcheckState_BinaryIn(ui->m_cbBinA,m_pGradientParas->m_binIn,0);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinB,m_pGradientParas->m_binIn,1);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinC,m_pGradientParas->m_binIn,2);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinD,m_pGradientParas->m_binIn,3);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinE,m_pGradientParas->m_binIn,4);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinF,m_pGradientParas->m_binIn,5);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinG,m_pGradientParas->m_binIn,6);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinH,m_pGradientParas->m_binIn,7);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinI,m_pGradientParas->m_binIn,8);
	GlobalSetQcheckState_BinaryIn(ui->m_cbBinJ,m_pGradientParas->m_binIn,9);
// 	ui->m_cbBinA->setChecked(m_pGradientParas->m_binIn[0].nSelect);
// 	ui->m_cbBinB->setChecked(m_pGradientParas->m_binIn[1].nSelect);
// 	ui->m_cbBinC->setChecked(m_pGradientParas->m_binIn[2].nSelect);
// 	ui->m_cbBinD->setChecked(m_pGradientParas->m_binIn[3].nSelect);
// 	ui->m_cbBinE->setChecked(m_pGradientParas->m_binIn[4].nSelect);
// 	ui->m_cbBinF->setChecked(m_pGradientParas->m_binIn[5].nSelect);
// 	ui->m_cbBinG->setChecked(m_pGradientParas->m_binIn[6].nSelect);
// 	ui->m_cbBinH->setChecked(m_pGradientParas->m_binIn[7].nSelect);
// 
// 	if(g_nBinCount != 8)
// 	{
// 		ui->m_cbBinI->setChecked(m_pGradientParas->m_binIn[8].nSelect);
// 		ui->m_cbBinJ->setChecked(m_pGradientParas->m_binIn[9].nSelect);
// 	}
// 	else
// 	{
// 		ui->m_cbBinI->setChecked(false);
// 		ui->m_cbBinJ->setChecked(false);
// 		ui->m_cbBinI->setEnabled(false);
// 		ui->m_cbBinJ->setEnabled(false);
// 	}
	
	//常态开出量设置
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut1,m_pGradientParas->m_binOut[0],0);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut2,m_pGradientParas->m_binOut[0],1);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut3,m_pGradientParas->m_binOut[0],2);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut4,m_pGradientParas->m_binOut[0],3);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut5,m_pGradientParas->m_binOut[0],4);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut6,m_pGradientParas->m_binOut[0],5);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut7,m_pGradientParas->m_binOut[0],6);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut8,m_pGradientParas->m_binOut[0],7);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut9,m_pGradientParas->m_binOut[0],8);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut10,m_pGradientParas->m_binOut[0],9);
// 	ui->m_cbBOut1->setChecked(m_pGradientParas->m_binOut[0][0].nState);
// 	ui->m_cbBOut2->setChecked(m_pGradientParas->m_binOut[0][1].nState);
// 	ui->m_cbBOut3->setChecked(m_pGradientParas->m_binOut[0][2].nState);
// 	ui->m_cbBOut4->setChecked(m_pGradientParas->m_binOut[0][3].nState);
// 	ui->m_cbBOut5->setChecked(m_pGradientParas->m_binOut[0][4].nState);
// 	ui->m_cbBOut6->setChecked(m_pGradientParas->m_binOut[0][5].nState);
// 	ui->m_cbBOut7->setChecked(m_pGradientParas->m_binOut[0][6].nState);
// 	ui->m_cbBOut8->setChecked(m_pGradientParas->m_binOut[0][7].nState);
// 	if(g_nBoutCount == 10)
// 	{
// 		ui->m_cbBOut9->setChecked(m_pGradientParas->m_binOut[0][8].nState);
// 		ui->m_cbBOut10->setChecked(m_pGradientParas->m_binOut[0][9].nState);
// 	}
// 	else
// 	{
// 		ui->m_cbBOut9->setChecked(false);
// 		ui->m_cbBOut10->setChecked(false);
// 		ui->m_cbBOut9->setEnabled(false);
// 		ui->m_cbBOut10->setEnabled(false);
// 	}

	//故障态开出量设置
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut1_E,m_pGradientParas->m_binOut[1],0);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut2_E,m_pGradientParas->m_binOut[1],1);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut3_E,m_pGradientParas->m_binOut[1],2);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut4_E,m_pGradientParas->m_binOut[1],3);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut5_E,m_pGradientParas->m_binOut[1],4);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut6_E,m_pGradientParas->m_binOut[1],5);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut7_E,m_pGradientParas->m_binOut[1],6);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut8_E,m_pGradientParas->m_binOut[1],7);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut9_E,m_pGradientParas->m_binOut[1],8);
	GlobalSetQcheckState_BinaryOut(ui->m_cbBOut10_E,m_pGradientParas->m_binOut[1],9);

// 	ui->m_cbBOut1_E->setChecked(m_pGradientParas->m_binOut[1][0].nState);
// 	ui->m_cbBOut2_E->setChecked(m_pGradientParas->m_binOut[1][1].nState);
// 	ui->m_cbBOut3_E->setChecked(m_pGradientParas->m_binOut[1][2].nState);
// 	ui->m_cbBOut4_E->setChecked(m_pGradientParas->m_binOut[1][3].nState);
// 	ui->m_cbBOut5_E->setChecked(m_pGradientParas->m_binOut[1][4].nState);
// 	ui->m_cbBOut6_E->setChecked(m_pGradientParas->m_binOut[1][5].nState);
// 	ui->m_cbBOut7_E->setChecked(m_pGradientParas->m_binOut[1][6].nState);
// 	ui->m_cbBOut8_E->setChecked(m_pGradientParas->m_binOut[1][7].nState);
// 	if(g_nBoutCount == 10)
// 	{
// 		ui->m_cbBOut9_E->setChecked(m_pGradientParas->m_binOut[1][8].nState);
// 		ui->m_cbBOut10_E->setChecked(m_pGradientParas->m_binOut[1][9].nState);
// 	}
// 	else
// 	{
// 		ui->m_cbBOut9_E->setChecked(false);
// 		ui->m_cbBOut10_E->setChecked(false);
// 		ui->m_cbBOut9_E->setEnabled(false);
// 		ui->m_cbBOut10_E->setEnabled(false);
// 	}

	if(m_pGradientParas->m_nBinLogic)
	{
		ui->m_rbAnd->setChecked(true);
	}
	else
	{
		ui->m_rbOr->setChecked(true);
	}
}

/*void QGradientSettingDlg::on_m_editTimeBeforeChangeChanged()//响应的槽函数实现部分（新界面需要，移走）
{
	if (ui->m_editTimeBeforeChange->text().isEmpty())
	{
		ui->m_editTimeBeforeChange->setText("0");
	}

	QString str = ui->m_editTimeBeforeChange->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}
	else if (fv>999.999)
	{
		fv = 999.999;
	}

	ui->m_editTimeBeforeChange->setText(QString::number(fv,'f',3));
}

void QGradientSettingDlg::on_m_editTimeBeforeFailChanged()
{
	if (ui->m_editTimeBeforeFail->text().isEmpty())
	{
		ui->m_editTimeBeforeFail->setText("0");
	}

	QString str = ui->m_editTimeBeforeFail->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}
	else if (fv>999.999)
	{
		fv = 999.999;
	}

	ui->m_editTimeBeforeFail->setText(QString::number(fv,'f',3));
}

void QGradientSettingDlg::on_m_editCurBeforeChangeChanged()
{
	if (ui->m_editCurBeforeChange->text().isEmpty())
	{
		ui->m_editCurBeforeChange->setText("0");
	}

	QString str = ui->m_editCurBeforeChange->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}
	else if (fv>g_oLocalSysPara.m_fAC_CurMax)
	{
		fv = g_oLocalSysPara.m_fAC_CurMax;
	}

	ui->m_editCurBeforeChange->setText(QString::number(fv,'f',3));
}

void QGradientSettingDlg::on_m_editPhaseChanged()
{
	if (ui->m_editPhase->text().isEmpty())
	{
		ui->m_editPhase->setText("0");
	}

	QString str = ui->m_editPhase->text();
	if (str.right(1).contains("."))
	{
		str.append(000);
	}

	float fv = str.toFloat();
	if (fv<0)
	{
		fv = 0;
	}
	else if (fv>360)
	{
		fv = fv-(int)(fv/360)*360;
	}

	ui->m_editPhase->setText(QString::number(fv,'f',1));
}

void QGradientSettingDlg::slot_edit_changed(QSttLineEdit* pEditLine, long nType)
{
	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();

	switch(nType)
	{
	case 0: GetWidgetBoard_DigitData(4,str,pEditLine, parentWidget()); break;
	case 1: GetWidgetBoard_DigitData(1,str,pEditLine,parentWidget()); break;
	case 2: GetWidgetBoard_DigitData(2,str,pEditLine,parentWidget()); break;
	default:
		break;
	}

	if (str.right(1).contains("."))
	{
		str.append("000");
	}

// 	pEditLine->setText(str);
// 	pEditLine->SetEditFinished();
}*/

void QGradientSettingDlg::InitConnections()
{
	//connect(ui->m_editTimeBeforeChange,SIGNAL(editingFinished()),this,SLOT(on_m_editTimeBeforeChangeChanged()));
	//connect(ui->m_editTimeBeforeFail,SIGNAL(editingFinished()),this,SLOT(on_m_editTimeBeforeFailChanged()));
	//connect(ui->m_editCurBeforeChange,SIGNAL(editingFinished()),this,SLOT(on_m_editCurBeforeChangeChanged()));
	//connect(ui->m_editPhase,SIGNAL(editingFinished()),this,SLOT(on_m_editPhaseChanged()));//Zhouyy2023/01/07 响应部分（新界面需要，移走）
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

void QGradientSettingDlg::slot_ck_BinaryInStateChanged(int )
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

	if (Global_BinaryInHasChecked(ui->m_cbBinD))
	{
		return;
	}

	if (Global_BinaryInHasChecked(ui->m_cbBinE))
	{
		return;
	}

	if (Global_BinaryInHasChecked(ui->m_cbBinF))
	{
		return;
	}

	if (Global_BinaryInHasChecked(ui->m_cbBinG))
	{
		return;
	}

	if (Global_BinaryInHasChecked(ui->m_cbBinH))
	{
		return;
	}

	if (Global_BinaryInHasChecked(ui->m_cbBinI))
	{
		return;
	}

	if (Global_BinaryInHasChecked(ui->m_cbBinJ))
	{
		return;
	}

	ui->m_cbBinA->setCheckState(Qt::Checked);
}

/*void QGradientSettingDlg::on_m_editTimeBeforeChange_clicked()//Zhouyy2023/01/07鼠标响应部分(移走）
{
	slot_edit_changed(ui->m_editTimeBeforeChange, 0);
}

void QGradientSettingDlg::on_m_editTimeBeforeFail_clicked()
{
	slot_edit_changed(ui->m_editTimeBeforeFail, 0);
}

void QGradientSettingDlg::on_m_editCurBeforeChange_clicked()
{
	slot_edit_changed(ui->m_editCurBeforeChange, 0);
}

void QGradientSettingDlg::on_m_editPhase_clicked()
{
	slot_edit_changed(ui->m_editPhase, 0);
}*/
