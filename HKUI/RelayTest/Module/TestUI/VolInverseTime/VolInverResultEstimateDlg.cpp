#include "VolInverResultEstimateDlg.h"
#include "ui_VolInverResultEstimateDlg.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"

extern CFont *g_pSttGlobalFont;

QVolInverResultEstimateDlg::QVolInverResultEstimateDlg(CDataGroup *pPara,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QVolInverResultEstimateDlg)
{
    ui->setupUi(this);

	m_pCurrDataGroup = pPara;
    InitUI();
	SetDatas(m_pCurrDataGroup);

	connect(m_pLineEdit1,SIGNAL(editingFinished()), this, SLOT(on_lineEdit1_TextChanged()));
	connect(m_pLineEdit2,SIGNAL(editingFinished()), this, SLOT(on_lineEdit2_TextChanged()));

}

QVolInverResultEstimateDlg::~QVolInverResultEstimateDlg()
{
    delete ui;
}

void QVolInverResultEstimateDlg::InitUI()
{

    this->setFont(*g_pSttGlobalFont);
    this->setWindowTitle(QString::fromUtf8(QString("结果评估").toStdString().c_str()));

	ui->tableWidget->setColumnWidth(0,138);
	ui->tableWidget->setColumnWidth(1,160);
	ui->tableWidget->setColumnWidth(2,140);
	ui->tableWidget->setColumnWidth(3,140);
	ui->tableWidget->setRowCount(1);
	ui->tableWidget->setRowHeight(0, 40);
	ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); 
	ui->tableWidget->setStyleSheet("selection-background-color: grey;selection-color: black");
	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->setShowGrid(true);
	ui->tableWidget->setFixedSize(580, 80);


    QTableWidgetItem *pItem = new QTableWidgetItem(QString::fromUtf8(QString("动作时间(s)").toStdString().c_str()));
    pItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(0, 0, pItem);

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
    ui->tableWidget->setCellWidget(0, 1, containerWidget_1);

    QWidget *containerWidget_2 = new QWidget();
    QHBoxLayout *horizontalLayout_2 = new QHBoxLayout(containerWidget_2);
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_2->setSpacing(0);
    m_pLineEdit1 = new QLineEdit(this);
    horizontalLayout_2->addWidget(m_pLineEdit1);
    m_pLineEdit1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->tableWidget->setCellWidget(0, 2, containerWidget_2);

    QWidget *containerWidget_3 = new QWidget();
    QHBoxLayout *horizontalLayout_3 = new QHBoxLayout(containerWidget_3);
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_3->setSpacing(0);
    m_pLineEdit2 = new QLineEdit(this);
    horizontalLayout_3->addWidget(m_pLineEdit2);
    m_pLineEdit2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->tableWidget->setCellWidget(0, 3, containerWidget_3);

    ui->tableWidget->horizontalHeaderItem(0)->setFont(*g_pSttGlobalFont);
    ui->tableWidget->horizontalHeaderItem(1)->setFont(*g_pSttGlobalFont);
    ui->tableWidget->horizontalHeaderItem(2)->setFont(*g_pSttGlobalFont);
    ui->tableWidget->horizontalHeaderItem(3)->setFont(*g_pSttGlobalFont);

    return;
}

void QVolInverResultEstimateDlg::SetDatas(CDataGroup *pParas)
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

void QVolInverResultEstimateDlg::GetDatas(CDataGroup *pParas)
{
	if(pParas == NULL)
		return;

	pParas->SetDataValue("Ttrip_ErrorLogic",(long)m_pComboBox->currentIndex(), true);
	pParas->SetDataValue("Ttrip_RelErr", m_pLineEdit1->text().toDouble(), true);
	pParas->SetDataValue("Ttrip_AbsErr", m_pLineEdit2->text().toDouble(), true);

	return;
}

void QVolInverResultEstimateDlg::on_lineEdit1_TextChanged()
{
	if (m_pLineEdit1->text().isEmpty())
	{
		m_pLineEdit1->setText("0.000");
	}
	QString str = m_pLineEdit1->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv = str.toFloat();
	fv = setLimit(0,100.000,fv);
	m_pLineEdit1->setText(QString::number(fv,'f',3));
}

void QVolInverResultEstimateDlg::on_lineEdit2_TextChanged()
{
	if (m_pLineEdit2->text().isEmpty())
	{
		m_pLineEdit2->setText("0.000");
	}
	QString str = m_pLineEdit2->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv = str.toFloat();
	fv = setLimit(0,200.000,fv);
	m_pLineEdit2->setText(QString::number(fv,'f',3));
}

//确认
void QVolInverResultEstimateDlg::on_pushButton_clicked()
{
	GetDatas(m_pCurrDataGroup);
    accept();
}

//取消
void QVolInverResultEstimateDlg::on_pushButton_2_clicked()
{
	reject();
}
