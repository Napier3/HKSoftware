#include "SwingTestBinarySignalDlg.h"
#include "ui_SwingTestBinarySignalDlg.h"
#include "SwingTestCommon.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern QFont *g_pSttGlobalFont;

QSwingTestBinarySignalDlg::QSwingTestBinarySignalDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSwingTestBinarySignalDlg)
{
    ui->setupUi(this);
	m_pCurTest = NULL;
    InitUI();
	InitLanuage();
}

QSwingTestBinarySignalDlg::~QSwingTestBinarySignalDlg()
{
    delete ui;
}

void QSwingTestBinarySignalDlg::InitUI()
{
    CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
    strPngPath = _P_GetResourcePath();
    strPngPath = strPngPath + _T("images/Oscillation.png");
#else
    strPngPath =  ":/ctrls/images/Oscillation.png";
#endif
    this->setWindowTitle("g_sLangTxt_Native_Bout");
    this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setFont(*g_pSttGlobalFont);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

}

void QSwingTestBinarySignalDlg::InitLanuage()
{
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
void QSwingTestBinarySignalDlg::UpdateParas()
{
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout1, m_pCurTest->m_oSwingParas.m_binOut, 0);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout2, m_pCurTest->m_oSwingParas.m_binOut, 1);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout3, m_pCurTest->m_oSwingParas.m_binOut, 2);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout4, m_pCurTest->m_oSwingParas.m_binOut, 3);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout5, m_pCurTest->m_oSwingParas.m_binOut, 4);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout6, m_pCurTest->m_oSwingParas.m_binOut, 5);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout7, m_pCurTest->m_oSwingParas.m_binOut, 6);
    GlobalSetQcheckState_BinaryOut(ui->m_cbBout8, m_pCurTest->m_oSwingParas.m_binOut, 7);
}
void QSwingTestBinarySignalDlg::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL && m_pCurTest != NULL)
	{
		CSttDataGroupSerializeRead oRead(pParas);
		stt_xml_serialize(&(m_pCurTest->m_oSwingParas), &oRead);
	}

	UpdateParas();

}

void QSwingTestBinarySignalDlg::GetDatas(CDataGroup *pParas)
{
    pParas->SetDataValue("_Bout1", (long)ui->m_cbBout1->isChecked(), true);
    pParas->SetDataValue("_Bout2", (long)ui->m_cbBout2->isChecked(), true);
    pParas->SetDataValue("_Bout3", (long)ui->m_cbBout3->isChecked(), true);
    pParas->SetDataValue("_Bout4", (long)ui->m_cbBout4->isChecked(), true);
    pParas->SetDataValue("_Bout5", (long)ui->m_cbBout5->isChecked(), true);
    pParas->SetDataValue("_Bout6", (long)ui->m_cbBout6->isChecked(), true);
    pParas->SetDataValue("_Bout7", (long)ui->m_cbBout7->isChecked(), true);
    pParas->SetDataValue("_Bout8", (long)ui->m_cbBout8->isChecked(), true);

}

//确定按钮
void QSwingTestBinarySignalDlg::on_m_btnOk_clicked()
{
	GetDatas(m_pCurrDataGroup);
	SetDatas(m_pCurrDataGroup);
	emit sig_DataChanged();
	this->hide();
}

//取消按钮
void QSwingTestBinarySignalDlg::on_m_btnCancel_clicked()
{
	SetDatas(m_pCurrDataGroup);
	this->hide();
}
