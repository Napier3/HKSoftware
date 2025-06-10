#include "QSttCapFunSelectDlg.h"
#include "XGlobalDataTypes_QT.h"

QSttCapFunSelectDlg::QSttCapFunSelectDlg(QWidget *parent /*= 0*/, Qt::WFlags flags /*= 0*/, int nTestFunction)
{
	InitUI();
	if (nTestFunction == 1)
	{
		m_RadioBtnPkgStc->setChecked(true);
	}
	else if(nTestFunction == 0)
	{
		m_RadioBtnMUTest->setChecked(true);
	}
	
}

QSttCapFunSelectDlg::~QSttCapFunSelectDlg()
{

}

void QSttCapFunSelectDlg::InitUI()
{
	resize(300, 150);
	setWindowTitle(_T("功能选择"));
	verticalLayout_2 = new QVBoxLayout(this);
	m_pFunGroupBox = new QGroupBox(this);
	verticalLayout_3 = new QVBoxLayout(m_pFunGroupBox);
	m_pVFunsLayout = new QVBoxLayout();
	m_RadioBtnPkgStc = new QRadioButton(m_pFunGroupBox);

	m_pVFunsLayout->addWidget(m_RadioBtnPkgStc);
	m_RadioBtnPkgStc->setText(_T("报文统计"));

	m_RadioBtnMUTest = new QRadioButton(m_pFunGroupBox);

	m_pVFunsLayout->addWidget(m_RadioBtnMUTest);
	m_RadioBtnMUTest->setText(_T("MU精确度测试"));
	verticalLayout_3->addLayout(m_pVFunsLayout);
	verticalLayout_2->addWidget(m_pFunGroupBox);

	hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
	hboxLayout->setSpacing(6);
#endif
	hboxLayout->setContentsMargins(0, 0, 0, 0);
	spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

	hboxLayout->addItem(spacerItem);
	m_BtnOK = new QPushButton(this);
	m_BtnOK->setText(_T("确认"));
	hboxLayout->addWidget(m_BtnOK);
	m_BtnCancel = new QPushButton(this);
	m_BtnCancel->setText(_T("取消"));
	hboxLayout->addWidget(m_BtnCancel);


	verticalLayout_2->addLayout(hboxLayout);
	verticalLayout_2->setStretch(0, 3);
	verticalLayout_2->setStretch(1, 1);

	connect(m_BtnOK, SIGNAL(clicked()), this, SLOT(slot_m_BtnOK_Clicked()));
	connect(m_BtnCancel, SIGNAL(clicked()), this, SLOT(slot_m_BtnCancel_Clicked()));

} 

void QSttCapFunSelectDlg::slot_m_BtnOK_Clicked()
{
	bool bSvAnalysis = m_RadioBtnPkgStc->isChecked();
	emit sig_UpdateTestFun(bSvAnalysis);
	this->close();
}

void QSttCapFunSelectDlg::slot_m_BtnCancel_Clicked()
{
	this->close();
}
