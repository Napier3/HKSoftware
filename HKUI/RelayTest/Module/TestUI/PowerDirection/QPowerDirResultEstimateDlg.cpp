#include "QPowerDirResultEstimateDlg.h"
#include "ui_QPowerDirResultEstimateDlg.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#pragma execution_character_set("utf-8")
extern CFont *g_pSttGlobalFont;

QPowerDirResultEstimateDlg::QPowerDirResultEstimateDlg(CDataGroup *pPara,QWidget *parent) :
    QDialog(parent), ui(new Ui::QPowerDirResultEstimateDlg)
{
    ui->setupUi(this);

	m_pCurrDataGroup = pPara;
    InitUI();
	InitLanguage();
	SetDatas(m_pCurrDataGroup);

	initConnections();

}

QPowerDirResultEstimateDlg::~QPowerDirResultEstimateDlg()
{
    delete ui;
}

void QPowerDirResultEstimateDlg::InitUI()
{

    this->setFont(*g_pSttGlobalFont);
    this->setWindowTitle(QString::fromUtf8(QString("结果评估").toStdString().c_str()));

	ui->tableWidget->setColumnWidth(0,138);
	ui->tableWidget->setColumnWidth(1,170);
	ui->tableWidget->setColumnWidth(2,135);
	ui->tableWidget->setColumnWidth(3,135);
	ui->tableWidget->setRowCount(3);
	ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); 
	ui->tableWidget->setStyleSheet("selection-background-color: grey;selection-color: black");
	ui->tableWidget->setRowHeight(0, 40);

	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->setShowGrid(true);
	ui->tableWidget->setFixedSize(580, 250);

    QTableWidgetItem *pAllowPressureItem = new QTableWidgetItem(g_sLangTxt_Gradient_MaxSenAngle);
    pAllowPressureItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
	pAllowPressureItem->setFont(*g_pSttGlobalFont);
    ui->tableWidget->setItem(0, 0, pAllowPressureItem);

	QTableWidgetItem *pAllowFreItem = new QTableWidgetItem(g_sLangTxt_Gradient_FirBoundAngle);
	pAllowFreItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
	pAllowFreItem->setFont(*g_pSttGlobalFont);
	ui->tableWidget->setItem(1, 0, pAllowFreItem);

	QTableWidgetItem *pLeadAngleItem = new QTableWidgetItem(g_sLangTxt_Gradient_SecBoundAngle);
	pLeadAngleItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
	pLeadAngleItem->setFont(*g_pSttGlobalFont);
	ui->tableWidget->setItem(2, 0, pLeadAngleItem);

	
	m_pMaxErrorTypeLabel = new QLabel(this);
	m_pMaxErrorTypeLabel->setText(g_sLangTxt_StateEstimate_AbsError);
	m_pMaxErrorTypeLabel->setDisabled(true);
	m_pMaxErrorTypeLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	ui->tableWidget->setCellWidget(0, 1, m_pMaxErrorTypeLabel);

	m_pErrorType1Label = new QLabel(this);
	m_pErrorType1Label->setText(g_sLangTxt_StateEstimate_AbsError);
	m_pErrorType1Label->setDisabled(true);
	m_pErrorType1Label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	ui->tableWidget->setCellWidget(1, 1, m_pErrorType1Label);

	m_pErrorType2Label = new QLabel(this);
	m_pErrorType2Label->setText(g_sLangTxt_StateEstimate_AbsError);
	m_pErrorType2Label->setDisabled(true);
	m_pErrorType2Label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	ui->tableWidget->setCellWidget(2, 1, m_pErrorType2Label);

    m_pRelativeErrorLabel1 = new QLabel(this);
	m_pRelativeErrorLabel1->setText("---");
	m_pRelativeErrorLabel1->setDisabled(true);
	m_pRelativeErrorLabel1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	ui->tableWidget->setCellWidget(0, 2, m_pRelativeErrorLabel1);

	m_pRelativeErrorLabel2 = new QLabel(this);
	m_pRelativeErrorLabel2->setText("---");
	m_pRelativeErrorLabel2->setDisabled(true);
	m_pRelativeErrorLabel2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	ui->tableWidget->setCellWidget(1, 2, m_pRelativeErrorLabel2);

	m_pRelativeErrorLabel3 = new QLabel(this);
	m_pRelativeErrorLabel3->setText("---");
	m_pRelativeErrorLabel3->setDisabled(true);
	m_pRelativeErrorLabel3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	ui->tableWidget->setCellWidget(2, 2, m_pRelativeErrorLabel3);

    m_pAbsoluteErrorEdit1 = new QLineEdit(this);
    m_pAbsoluteErrorEdit1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->tableWidget->setCellWidget(0, 3, m_pAbsoluteErrorEdit1);

	m_pAbsoluteErrorEdit2 = new QLineEdit(this);
	m_pAbsoluteErrorEdit2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	ui->tableWidget->setCellWidget(1, 3, m_pAbsoluteErrorEdit2);

	m_pAbsoluteErrorEdit3 = new QLineEdit(this);
	m_pAbsoluteErrorEdit3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	ui->tableWidget->setCellWidget(2, 3, m_pAbsoluteErrorEdit3);

    ui->tableWidget->horizontalHeaderItem(0)->setFont(*g_pSttGlobalFont);
    ui->tableWidget->horizontalHeaderItem(1)->setFont(*g_pSttGlobalFont);
    ui->tableWidget->horizontalHeaderItem(2)->setFont(*g_pSttGlobalFont);
    ui->tableWidget->horizontalHeaderItem(3)->setFont(*g_pSttGlobalFont);

    return;
}

void QPowerDirResultEstimateDlg::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(m_pRelativeErrorLabel1, g_sLangTxt_Native_Grid_Vol, XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(m_pRelativeErrorLabel2, g_sLangTxt_Native_Grid_Freq, XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(m_pRelativeErrorLabel3, g_sLangTxt_Native_GvolChangeStep, XLang_Ctrls_QLabel);
	
	m_pMaxErrorTypeLabel->setFont(*g_pSttGlobalFont);
	m_pErrorType1Label->setFont(*g_pSttGlobalFont);
	m_pErrorType2Label->setFont(*g_pSttGlobalFont);
	m_pAbsoluteErrorEdit1->setFont(*g_pSttGlobalFont);
	m_pAbsoluteErrorEdit2->setFont(*g_pSttGlobalFont);
	m_pAbsoluteErrorEdit3->setFont(*g_pSttGlobalFont);
}

void QPowerDirResultEstimateDlg::initConnections()
{
	connect(m_pAbsoluteErrorEdit1,SIGNAL(editingFinished()), this, SLOT(slot_lneAbsoluteErrorEdit1_TextChanged()));
	connect(m_pAbsoluteErrorEdit2,SIGNAL(editingFinished()), this, SLOT(slot_lneAbsoluteErrorEdit2_TextChanged()));
	connect(m_pAbsoluteErrorEdit3,SIGNAL(editingFinished()), this, SLOT(slot_lneAbsoluteErrorEdit3_TextChanged()));
}
void QPowerDirResultEstimateDlg::SetDatas(CDataGroup *pParas)
{
    double dMaxAngleAbsErr;//最大灵敏角绝对误差限
    double dAngleAbsErr;//边界角1绝对误差限
	double dAngleSAbsErr;//边界角2绝对误差限

	if (pParas != NULL)
	{
		pParas->GetDataValue("MaxAngle_AbsErr",dMaxAngleAbsErr);
		pParas->GetDataValue("AngleF_AbsErr", dAngleAbsErr);
		pParas->GetDataValue("AngleS_AbsErr", dAngleSAbsErr);
		
	}

	m_pAbsoluteErrorEdit1->setText(QString::number(dMaxAngleAbsErr));
	m_pAbsoluteErrorEdit2->setText(QString::number(dAngleAbsErr));
	m_pAbsoluteErrorEdit3->setText(QString::number(dAngleSAbsErr));

    return;
}

void QPowerDirResultEstimateDlg::GetDatas(CDataGroup *pParas)
{
	pParas->SetDataValue("MaxAngle_AbsErr", m_pAbsoluteErrorEdit1->text().toDouble(), true);
	pParas->SetDataValue("AngleF_AbsErr", m_pAbsoluteErrorEdit2->text().toDouble(), true);
	pParas->SetDataValue("AngleS_AbsErr", m_pAbsoluteErrorEdit3->text().toDouble(), true);
	
	return;
}

float QPowerDirResultEstimateDlg::on_lineEdit_TextChanged(QLineEdit *pLineEdit)
{
	if (pLineEdit->text().isEmpty())
	{
		pLineEdit->setText("0.000");
	}
	QString str = pLineEdit->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv = str.toFloat();
	fv = setLimit(0,200.000,fv);
	return fv;

}

void QPowerDirResultEstimateDlg::slot_lneAbsoluteErrorEdit1_TextChanged()
{
	float fv=on_lineEdit_TextChanged(m_pAbsoluteErrorEdit1);
	m_pAbsoluteErrorEdit1->setText(QString::number(fv,'f',3));
}

void QPowerDirResultEstimateDlg::slot_lneAbsoluteErrorEdit2_TextChanged()
{
	float fv=on_lineEdit_TextChanged(m_pAbsoluteErrorEdit2);
	m_pAbsoluteErrorEdit2->setText(QString::number(fv,'f',3));
}

void QPowerDirResultEstimateDlg::slot_lneAbsoluteErrorEdit3_TextChanged()
{
	float fv=on_lineEdit_TextChanged(m_pAbsoluteErrorEdit3);
	m_pAbsoluteErrorEdit3->setText(QString::number(fv,'f',3));
}

//确认
void QPowerDirResultEstimateDlg::on_pushButton_clicked()
{
	GetDatas(m_pCurrDataGroup);
    accept();
}

//取消
void QPowerDirResultEstimateDlg::on_pushButton_2_clicked()
{
	reject();
}
