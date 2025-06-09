#include "SwingTestParasDlg.h"
#include "ui_SwingTestParasDlg.h"
#include "SwingTestCommon.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern CFont *g_pSttGlobalFont;

QSwingTestParasDlg::QSwingTestParasDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSwingTestParasDlg)
{
    ui->setupUi(this);
	m_pCurTest = NULL;
    InitUI();
	InitLanuage();
}

QSwingTestParasDlg::~QSwingTestParasDlg()
{
    delete ui;
}

void QSwingTestParasDlg::InitUI()
{
    this->setFont(*g_pSttGlobalFont);
    this->setWindowTitle(/*"通用参数"*/g_sLangTxt_Gradient_CommonParas);
    ui->tabWidget->setTabText(0, /*"通用参数"*/g_sLangTxt_Gradient_CommonParas);
    ui->tabWidget->setTabText(1, /*"开出量"*/g_sLangTxt_Native_Bout);
    ui->tabWidget->setCurrentIndex(0);
    ui->m_cbbCTPos->setCurrentIndex(1);

    ui->m_cbbCTPos->clear();
	ui->m_cbbCTPos->addItem(/*"指向母线"*/g_sLangTxt_CBOperate_CTPos1);
	ui->m_cbbCTPos->addItem(/*"指向线路"*/g_sLangTxt_CBOperate_TPos1);

}

void QSwingTestParasDlg::InitLanuage()
{
    xlang_SetLangStrToWidget(ui->m_labSwingTime, g_sLangID_Swing_Time, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labCTPos, g_sLangID_Swing_CTPos, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labSysZs, g_sLangID_Swing_Zs, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labSysZsPhi, g_sLangID_Swing_ZsPhi, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labTransZt, g_sLangID_Swing_Transformer, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labTransZtPhi, g_sLangID_Swing_Transformer_Phi, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labImpTs, g_sLangID_Swing_Dynamo, XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget(ui->m_btnOk, "sOK", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnCancel, "sCancel", XLang_Ctrls_QPushButton);

	xlang_SetLangStrToWidget(ui->m_cbBout1, "Manual_Out1", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(ui->m_cbBout2, "Manual_Out2", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(ui->m_cbBout3, "Manual_Out3", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(ui->m_cbBout4, "Manual_Out4", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(ui->m_cbBout5, "Manual_Out5", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(ui->m_cbBout6, "Manual_Out6", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(ui->m_cbBout7, "Manual_Out7", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(ui->m_cbBout8, "Manual_Out8", XLang_Ctrls_QCheckBox);
}
void QSwingTestParasDlg::UpdateParas()
{
    ui->m_editPreFaultTime->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fPreFaultTime),PREFAULTTIME_MAX, PREFAULTTIME_MIN, 3));
    ui->m_cbbCTPos->setCurrentIndex(m_pCurTest->m_oSwingParas.m_nCTPoint);
    ui->m_editImpSys->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fImpSys),IMPSYS_MAX, IMPSYS_MIN, 3));
    ui->m_editImpSysPh->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fImpSysPh),IMPSYSPH_MAX, IMPSYSPH_MIN, 3));
    ui->m_editImpTf->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fImpTf),IMPTF_MAX, IMPTF_MIN, 3));
    ui->m_editImpTfPh->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fImpTfPh),IMPTFPH_MAX, IMPTFPH_MIN, 3));
    ui->m_editImpTs->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fImpTs),IMPTS_MAX, IMPTS_MIN, 3));

    GlobalSetQcheckState_BinaryOut(ui->m_cbBout1, m_pCurTest->m_oSwingParas.m_binOut, 0);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout2, m_pCurTest->m_oSwingParas.m_binOut, 1);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout3, m_pCurTest->m_oSwingParas.m_binOut, 2);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout4, m_pCurTest->m_oSwingParas.m_binOut, 3);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout5, m_pCurTest->m_oSwingParas.m_binOut, 4);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout6, m_pCurTest->m_oSwingParas.m_binOut, 5);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout7, m_pCurTest->m_oSwingParas.m_binOut, 6);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout8, m_pCurTest->m_oSwingParas.m_binOut, 7);

//    ui->m_cbBout1->setChecked(m_pCurTest->m_oSwingParas.m_binOut[0].nState);
//    ui->m_cbBout2->setChecked(m_pCurTest->m_oSwingParas.m_binOut[1].nState);
//    ui->m_cbBout3->setChecked(m_pCurTest->m_oSwingParas.m_binOut[2].nState);
//    ui->m_cbBout4->setChecked(m_pCurTest->m_oSwingParas.m_binOut[3].nState);
//    ui->m_cbBout5->setChecked(m_pCurTest->m_oSwingParas.m_binOut[4].nState);
//    ui->m_cbBout6->setChecked(m_pCurTest->m_oSwingParas.m_binOut[5].nState);
//    ui->m_cbBout7->setChecked(m_pCurTest->m_oSwingParas.m_binOut[6].nState);
//    ui->m_cbBout8->setChecked(m_pCurTest->m_oSwingParas.m_binOut[7].nState);

	return;
}
void QSwingTestParasDlg::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL && m_pCurTest != NULL)
	{
		CSttDataGroupSerializeRead oRead(pParas);
		stt_xml_serialize(&(m_pCurTest->m_oSwingParas), &oRead);
	}

	UpdateParas();

	return;
}

void QSwingTestParasDlg::GetDatas(CDataGroup *pParas)
{
	pParas->SetDataValue("PreFaultTime",ui->m_editPreFaultTime->text().toDouble(), true);
    pParas->SetDataValue("CTPos", (long)ui->m_cbbCTPos->currentIndex(), true);
    pParas->SetDataValue("ImpSys", ui->m_editImpSys->text().toDouble(), true);
    pParas->SetDataValue("ImpSysPh", ui->m_editImpSysPh->text().toDouble(), true);
    pParas->SetDataValue("ImpTf", ui->m_editImpTf->text().toDouble(), true);
    pParas->SetDataValue("ImpTfPh", ui->m_editImpTfPh->text().toDouble(), true);
    pParas->SetDataValue("ImpTs", ui->m_editImpTs->text().toDouble(), true);
    pParas->SetDataValue("_Bout1", (long)ui->m_cbBout1->isChecked(), true);
    pParas->SetDataValue("_Bout2", (long)ui->m_cbBout2->isChecked(), true);
    pParas->SetDataValue("_Bout3", (long)ui->m_cbBout3->isChecked(), true);
    pParas->SetDataValue("_Bout4", (long)ui->m_cbBout4->isChecked(), true);
    pParas->SetDataValue("_Bout5", (long)ui->m_cbBout5->isChecked(), true);
    pParas->SetDataValue("_Bout6", (long)ui->m_cbBout6->isChecked(), true);
    pParas->SetDataValue("_Bout7", (long)ui->m_cbBout7->isChecked(), true);
    pParas->SetDataValue("_Bout8", (long)ui->m_cbBout8->isChecked(), true);

	return;
}

//确定按钮
void QSwingTestParasDlg::on_m_btnOk_clicked()
{
	GetDatas(m_pCurrDataGroup);
	SetDatas(m_pCurrDataGroup);
	emit sig_DataChanged();
	this->hide();
}

//取消按钮
void QSwingTestParasDlg::on_m_btnCancel_clicked()
{
	SetDatas(m_pCurrDataGroup);
	this->hide();
}

void QSwingTestParasDlg::on_m_editPreFaultTime_editingFinished()
{
	ui->m_editPreFaultTime->setText(SwingTestValueCheck(ui->m_editPreFaultTime->text(),PREFAULTTIME_MAX, PREFAULTTIME_MIN, 3));
	return;
}

void QSwingTestParasDlg::on_m_editImpSys_editingFinished()
{
	ui->m_editImpSys->setText(SwingTestValueCheck(ui->m_editImpSys->text(),IMPSYS_MAX, IMPSYS_MIN, 3));
	return;
}

void QSwingTestParasDlg::on_m_editImpSysPh_editingFinished()
{
	ui->m_editImpSysPh->setText(SwingTestValueCheck(ui->m_editImpSysPh->text(),IMPSYSPH_MAX, IMPSYSPH_MIN, 3));
	return;
}

void QSwingTestParasDlg::on_m_editImpTf_editingFinished()
{
	ui->m_editImpTf->setText(SwingTestValueCheck(ui->m_editImpTf->text(),IMPTF_MAX, IMPTF_MIN, 3));
	return;
}

void QSwingTestParasDlg::on_m_editImpTfPh_editingFinished()
{
	ui->m_editImpTfPh->setText(SwingTestValueCheck(ui->m_editImpTfPh->text(),IMPTFPH_MAX, IMPTFPH_MIN, 3));
	return;
}

void QSwingTestParasDlg::on_m_editImpTs_editingFinished()
{
	ui->m_editImpTs->setText(SwingTestValueCheck(ui->m_editImpTs->text(),IMPTS_MAX, IMPTS_MIN, 3));
	return;
}
