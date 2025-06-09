#include "SwingResultEvalDlg.h"
#include "ui_SwingResultEvalDlg.h"
#include "SwingTestCommon.h"

extern CFont *g_pSttGlobalFont;
extern void  Stt_Global_SettingParent(QWidget *parent);

QSwingResultEvalDlg::QSwingResultEvalDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSwingResultEvalDlg)
{
    if (parent->inherits(STT_SETTING_ORIGINAL_ClassID/*"CSttMacroParaEditViewOriginal"*/))
    {
        //设置记录Maps关系的地址
        g_pCurrTestMacroUI_DataMaps = &(((CSttMacroParaEditViewOriginal*)parent)->m_oDvmDataMaps);
    }
    Stt_Global_SettingParent(this);

    ui->setupUi(this);
	m_pCurTest = NULL;
    InitUI();

    connect(ui->m_tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(on_m_tableWidget_itemChanged(QTableWidgetItem *)));
}

QSwingResultEvalDlg::~QSwingResultEvalDlg()
{
	Stt_Global_SettingParent(NULL);	//20241018 huangliang
    delete ui;
}

void QSwingResultEvalDlg::InitUI()
{

    this->setFont(*g_pSttGlobalFont);
    this->setWindowTitle(/*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate);
    QStringList headers;
    headers << /*"名称"*/g_sLangTxt_Name << g_sLangTxt_SetValue/*"整定值"*/ <</*"误差类型"*/g_sLangTxt_StateEstimate_ErrorType <</* "相对误差(%)"*/g_sLangTxt_StateEstimate_RelError + "(%)" << /*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError << g_sLangTxt_Distance_AbsErrMinus;
    ui->m_tableWidget->setHorizontalHeaderLabels(headers);
	ui->m_btnOk->setText(g_sLangTxt_OK);
	ui->m_btnCancel->setText(g_sLangTxt_Cancel);

    ui->m_tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { height: 40; }");
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    ui->m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
	ui->m_tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    ui->m_tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background: skyblue;}"); // 设置表头背景色
    ui->m_tableWidget->setStyleSheet("selection-background-color: grey;selection-color: black");
    ui->m_tableWidget->verticalHeader()->setVisible(false);
    ui->m_tableWidget->setShowGrid(true);
    ui->m_tableWidget->setFixedHeight(82);

    QWidget *containerWidget_1 = new QWidget();
    QHBoxLayout *horizontalLayout_1 = new QHBoxLayout(containerWidget_1);
    horizontalLayout_1->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_1->setSpacing(0);
    m_pComboBox = new QComboBox(this);
    m_pComboBox->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
    m_pComboBox->addItem(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError);
    m_pComboBox->addItem(/*"绝对or相对"*/g_sLangTxt_CBOperate_AbsOrRelative);
    m_pComboBox->addItem(/*"绝对&相对"*/g_sLangTxt_CBOperate_AbsRelative);
    m_pComboBox->addItem(/*"组合误差"*/g_sLangTxt_CBOperate_CombError);
    m_pComboBox->addItem(/*"不评估"*/g_sLangTxt_Distance_ErrorNot);
    horizontalLayout_1->addWidget(m_pComboBox);
    m_pComboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->m_tableWidget->setCellWidget(0, 2, containerWidget_1);

    m_editSettingValue = new QTableWidgetItem();
    m_editSettingValue->setTextAlignment(Qt::AlignCenter);
    ui->m_tableWidget->setItem(0, 1, m_editSettingValue);

    m_editRelErr = new QSettingItem(ui->m_tableWidget);
    m_editRelErr->setTextAlignment(Qt::AlignCenter);
    ui->m_tableWidget->setItem(0, 3, m_editRelErr);

    m_editAbsErr = new QSettingItem(ui->m_tableWidget);
    m_editAbsErr->setTextAlignment(Qt::AlignCenter);
    ui->m_tableWidget->setItem(0, 4, m_editAbsErr);

    m_editAbsErrNeg = new QSettingItem(ui->m_tableWidget);
    m_editAbsErrNeg->setTextAlignment(Qt::AlignCenter);
    ui->m_tableWidget->setItem(0, 5, m_editAbsErrNeg); 

    ui->m_tableWidget->horizontalHeaderItem(0)->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->horizontalHeaderItem(1)->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->horizontalHeaderItem(2)->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->horizontalHeaderItem(3)->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->horizontalHeaderItem(4)->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->horizontalHeaderItem(5)->setFont(*g_pSttGlobalFont);

    return;
}

void QSwingResultEvalDlg::UpdateParas()
{
    m_editSettingValue->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fActTimeSet),SETTINGVAL_MAX, SETTINGVAL_MIN, 3));
    m_pComboBox->setCurrentIndex(m_pCurTest->m_oSwingParas.m_nTtripErrorLogic);
    m_editRelErr->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fTtripRelErr),TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
    m_editAbsErr->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fTtripAbsErr),TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
    m_editAbsErrNeg->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fTtripAbsErr_Neg),TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));

    m_editRelErr->UpdateStructText(CVariantDataAddress(&m_pCurTest->m_oSwingParas.m_fTtripRelErr), 3);
    m_editAbsErr->UpdateStructText(CVariantDataAddress(&m_pCurTest->m_oSwingParas.m_fTtripAbsErr), 3);
    m_editAbsErrNeg->UpdateStructText(CVariantDataAddress(&m_pCurTest->m_oSwingParas.m_fTtripAbsErr_Neg), 3);

    return;
}

void QSwingResultEvalDlg::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL && m_pCurTest != NULL)
	{
		CSttDataGroupSerializeRead oRead(pParas);
		stt_xml_serialize(&(m_pCurTest->m_oSwingParas), &oRead);
	}

    UpdateParas();

    return;
}

void QSwingResultEvalDlg::GetDatas(CDataGroup *pParas)
{
    pParas->SetDataValue("TimeActSetting", m_editSettingValue->text().toDouble(), true);
	pParas->SetDataValue("Ttrip_ErrorLogic",(long)m_pComboBox->currentIndex(), true);
    pParas->SetDataValue("Ttrip_RelErr", m_editRelErr->text().toDouble(), true);
    pParas->SetDataValue("Ttrip_AbsErr", m_editAbsErr->text().toDouble(), true);
    pParas->SetDataValue("Ttrip_AbsErr_Neg", m_editAbsErrNeg->text().toDouble(), true);

	return;
}

void QSwingResultEvalDlg::on_m_tableWidget_itemChanged(QTableWidgetItem *item)
{
    int nRow = item->row();
    int nCol = item->column();

    if(nRow == 0 && nCol == 1)
    {
        /*整定值*/
        m_editSettingValue->setText(SwingTestValueCheck(m_editSettingValue->text(),SETTINGVAL_MAX, SETTINGVAL_MIN, 3));
    }
    else if(nRow == 0 && nCol == 3)
    {
        /*相对误差*/
        m_editRelErr->setText(SwingTestValueCheck(m_editRelErr->text(),TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
    }
    else if(nRow == 0 && nCol == 4)
    {
        /*绝对误差*/
        m_editAbsErr->setText(SwingTestValueCheck(m_editAbsErr->text(),TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
    }
    else if(nRow == 0 && nCol == 5)
    {
        /*绝对误差(-)*/
        m_editAbsErr->setText(SwingTestValueCheck(m_editAbsErr->text(),TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
    }

    return;
}

//确认
void QSwingResultEvalDlg::on_m_btnOk_clicked()
{
	GetDatas(m_pCurrDataGroup);
	SetDatas(m_pCurrDataGroup);
    this->hide();
}

//取消
void QSwingResultEvalDlg::on_m_btnCancel_clicked()
{
	SetDatas(m_pCurrDataGroup);
    this->hide();
}
