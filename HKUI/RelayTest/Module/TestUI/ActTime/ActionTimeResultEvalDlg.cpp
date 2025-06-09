#include "ActionTimeResultEvalDlg.h"
#include "ui_ActionTimeResultEvalDlg.h"
#include "ActionTimeCommon.h"

extern CFont *g_pSttGlobalFont;

QActionTimeResultEvalDlg::QActionTimeResultEvalDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QActionTimeResultEvalDlg)
{
    ui->setupUi(this);
    InitUI();

	connect(m_pLineEdit1,SIGNAL(editingFinished()),this,SLOT(on_m_pLineEdit1_editingFinished()));
	connect(m_pLineEdit2,SIGNAL(editingFinished()),this,SLOT(on_m_pLineEdit2_editingFinished()));
}

QActionTimeResultEvalDlg::~QActionTimeResultEvalDlg()
{
    delete ui;
}

void QActionTimeResultEvalDlg::InitUI()
{
	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();
	strPngPath = strPngPath + _T("images/ActionTimeTest.png");
#else
	strPngPath =  ":/ctrls/images/ActionTimeTest.png";
#endif
	this->setWindowIcon(QIcon(QPixmap(strPngPath)));
    this->setFont(*g_pSttGlobalFont);

	ui->m_tableWidget->setColumnWidth(0,120);
	ui->m_tableWidget->setColumnWidth(1,140);
	ui->m_tableWidget->setColumnWidth(2,120);
	ui->m_tableWidget->setRowCount(1);
	ui->m_tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { height: 40; }");
	ui->m_tableWidget->setRowHeight(0, 40);

	ui->m_tableWidget->verticalHeader()->setVisible(false);
	ui->m_tableWidget->setShowGrid(true);
	ui->m_tableWidget->setFixedSize(500, 80);

    QWidget *containerWidget_1 = new QWidget();
    QHBoxLayout *horizontalLayout_1 = new QHBoxLayout(containerWidget_1);
    horizontalLayout_1->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_1->setSpacing(0);
    m_pComboBox = new QComboBox(this);
	m_pComboBox->addItem(QString::fromUtf8(QString("绝对误差").toStdString().c_str()));
	m_pComboBox->addItem(QString::fromUtf8(QString("相对误差").toStdString().c_str()));
	m_pComboBox->addItem(QString::fromUtf8(QString("绝对or相对").toStdString().c_str()));
	m_pComboBox->addItem(QString::fromUtf8(QString("绝对&相对").toStdString().c_str()));
	m_pComboBox->addItem(QString::fromUtf8(QString("组合误差").toStdString().c_str()));
    horizontalLayout_1->addWidget(m_pComboBox);
    m_pComboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->m_tableWidget->setCellWidget(0, 1, containerWidget_1);

    QWidget *containerWidget_2 = new QWidget();
    QHBoxLayout *horizontalLayout_2 = new QHBoxLayout(containerWidget_2);
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_2->setSpacing(0);
    m_pLineEdit1 = new QLineEdit(this);
    horizontalLayout_2->addWidget(m_pLineEdit1);
    m_pLineEdit1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->m_tableWidget->setCellWidget(0, 2, containerWidget_2);

    QWidget *containerWidget_3 = new QWidget();
    QHBoxLayout *horizontalLayout_3 = new QHBoxLayout(containerWidget_3);
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_3->setSpacing(0);
    m_pLineEdit2 = new QLineEdit(this);
    horizontalLayout_3->addWidget(m_pLineEdit2);
    m_pLineEdit2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->m_tableWidget->setCellWidget(0, 3, containerWidget_3);

    ui->m_tableWidget->horizontalHeaderItem(0)->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->horizontalHeaderItem(1)->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->horizontalHeaderItem(2)->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->horizontalHeaderItem(3)->setFont(*g_pSttGlobalFont);

    return;
}

void QActionTimeResultEvalDlg::SetDatas(CDataGroup *pParas)
{
    int nTtripErrorLogic;
    double dTtripRelErr;
    double dTtripAbsErr;

	if (pParas != NULL)
	{
		pParas->GetDataValue("Ttrip_ErrorLogic",(long&)nTtripErrorLogic);
		pParas->GetDataValue("Ttrip_RelErr", dTtripRelErr);
		pParas->GetDataValue("Ttrip_AbsErr", dTtripAbsErr);
	}
    m_pComboBox->setCurrentIndex(nTtripErrorLogic);
    m_pLineEdit1->setText(QString::number(dTtripRelErr));
    m_pLineEdit2->setText(QString::number(dTtripAbsErr));

    return;
}

void QActionTimeResultEvalDlg::GetDatas(CDataGroup *pParas)
{
	pParas->SetDataValue("Ttrip_ErrorLogic",(long)m_pComboBox->currentIndex(), true);
	pParas->SetDataValue("Ttrip_RelErr", m_pLineEdit1->text().toDouble(), true);
	pParas->SetDataValue("Ttrip_AbsErr", m_pLineEdit2->text().toDouble(), true);

	return;
}

void QActionTimeResultEvalDlg::on_m_pLineEdit1_editingFinished()
{
	m_pLineEdit1->setText(ActTimeValueCheck(m_pLineEdit1->text(),TTRIPRELERR_MAX, TTRIPRELERR_MIN, 3));
	return;
}

void QActionTimeResultEvalDlg::on_m_pLineEdit2_editingFinished()
{
    m_pLineEdit2->setText(ActTimeValueCheck(m_pLineEdit2->text(),TTRIPABSERR_MAX, TTRIPABSERR_MIN, 3));
	return;
}

//
void QActionTimeResultEvalDlg::on_m_btnOk_clicked()
{
	GetDatas(m_pCurrDataGroup);
    this->hide();
}

//
void QActionTimeResultEvalDlg::on_m_btnCancel_clicked()
{
	SetDatas(m_pCurrDataGroup);
    this->hide();
}
