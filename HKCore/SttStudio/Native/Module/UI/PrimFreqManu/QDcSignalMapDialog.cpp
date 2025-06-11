#include "QDcSignalMapDialog.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"

QDcSignalMapDialog::QDcSignalMapDialog(tmt_PrimFreqManualParas* pParas, QWidget* parent) : QDialog(parent)
{
	m_pExternalParas = pParas;
	m_pExternalParas->CopyOwn(&m_oInterParas);
	m_nParaSetSecondValue = 1;
	InitUI();
	InitData();
	InitConnect();

	
}

QDcSignalMapDialog::~QDcSignalMapDialog()
{

}

void QDcSignalMapDialog::InitUI()
{
	setWindowTitle(_T("对应关系"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	CString strText = _T("电网频率");
	m_pHzGrp = new QSttGroupBox(strText);

	strText = _T("发电机转速");
	m_pPulseGrp = new QSttGroupBox(strText);

	m_pMinHzEdt = new QSttLineEdit;
	m_pMaxHzEdt = new QSttLineEdit;
	m_pMinPulseEdt = new QSttLineEdit;
	m_pMaxPulseEdt = new QSttLineEdit;

	m_pMinHzEdt->setFont(*g_pSttGlobalFont);
	m_pMaxHzEdt->setFont(*g_pSttGlobalFont);
	m_pMinPulseEdt->setFont(*g_pSttGlobalFont);
	m_pMaxPulseEdt->setFont(*g_pSttGlobalFont);
	CString strUnit;

	for(int nIndex = 0; nIndex < 4; nIndex++)
	{
		if(nIndex < 2)
		{
			QLabel *pLable1 = new QLabel;
			m_pArryRangeMap[nIndex] = pLable1;
			m_pArryRangeMap[nIndex]->setText(_T("对应关系"));
			m_pArryRangeMap[nIndex]->setFont(*g_pSttGlobalFont);
		}
		QSttLineEdit *pLineEdit = new QSttLineEdit;
		m_pArryRangeEdit[nIndex] = pLineEdit;
		m_pArryRangeEdit[nIndex]->setFont(*g_pSttGlobalFont);
		int nOrder = nIndex % 2;
		CString str1 =  _T("4.0000");
		CString str2 =  _T("20.0000");

		(nOrder == 0) ? m_pArryRangeEdit[nIndex]->setText(str1): m_pArryRangeEdit[nIndex]->setText(str2);
		m_pArryRangeEdit[nIndex]->setEnabled(false);

		QLabel *pLable = new QLabel;
		m_pArryLbUnit[nIndex] = pLable;
		(nIndex < 2) ? strUnit = _T("(Hz)  -"):strUnit = _T("(N)  -");
		m_pArryLbUnit[nIndex]->setText(strUnit);
		m_pArryLbUnit[nIndex]->setFont(*g_pSttGlobalFont);
		pLable = new QLabel;
		m_pArryLbDcUnit[nIndex] = pLable;
		m_pArryLbDcUnit[nIndex]->setText(_T("(mA)"));
		m_pArryLbDcUnit[nIndex]->setFont(*g_pSttGlobalFont);
	}

	m_pVMainLayout = new QVBoxLayout(this);
	QHBoxLayout *m_phLayout[2];
	QGridLayout *m_pGridLayout[2];

	for(int nIndex = 0; nIndex < 2; nIndex++)
	{
		QHBoxLayout *pLayout = new QHBoxLayout;
		m_phLayout[nIndex] = pLayout;

		QGridLayout *pGLayout = new QGridLayout;
		m_pGridLayout[nIndex] = pGLayout;
	}

	//1
	m_pGridLayout[0]->addWidget(m_pMinHzEdt,0,0);
	m_pGridLayout[0]->addWidget(m_pArryLbUnit[0],0,1);
	m_pGridLayout[0]->addWidget(m_pArryRangeEdit[0],0,2);
	m_pGridLayout[0]->addWidget(m_pArryLbDcUnit[0],0,3);

	m_pGridLayout[0]->addWidget(m_pMaxHzEdt,1,0);
	m_pGridLayout[0]->addWidget(m_pArryLbUnit[1],1,1);
	m_pGridLayout[0]->addWidget(m_pArryRangeEdit[1],1,2);
	m_pGridLayout[0]->addWidget(m_pArryLbDcUnit[1],1,3);

	m_phLayout[0]->addWidget(m_pArryRangeMap[0],1);
	m_phLayout[0]->addLayout(m_pGridLayout[0],2);
	m_pHzGrp->setLayout(m_phLayout[0]);

	//2
	m_pGridLayout[1]->addWidget(m_pMinPulseEdt,0,0);
	m_pGridLayout[1]->addWidget(m_pArryLbUnit[2],0,1);
	m_pGridLayout[1]->addWidget(m_pArryRangeEdit[2],0,2);
	m_pGridLayout[1]->addWidget(m_pArryLbDcUnit[2],0,3);

	m_pGridLayout[1]->addWidget(m_pMaxPulseEdt,1,0);
	m_pGridLayout[1]->addWidget(m_pArryLbUnit[3],1,1);
	m_pGridLayout[1]->addWidget(m_pArryRangeEdit[3],1,2);
	m_pGridLayout[1]->addWidget(m_pArryLbDcUnit[3],1,3);

	m_phLayout[1]->addWidget(m_pArryRangeMap[1],1);
	m_phLayout[1]->addLayout(m_pGridLayout[1],2);
	m_pPulseGrp->setLayout(m_phLayout[1]);



	QHBoxLayout *pHLayout = new QHBoxLayout();
	pHLayout->addStretch();
	QPushButton* pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sOK");
	pBtn->setText(strText);
	pBtn->setFont(*g_pSttGlobalFont);

	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	pHLayout->addWidget(pBtn);
	pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sCancel");
	pBtn->setText(strText);
	pBtn->setFont(*g_pSttGlobalFont);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
	pHLayout->addWidget(pBtn);
	pHLayout->addStretch();

	m_pVMainLayout->addWidget(m_pHzGrp);
	m_pVMainLayout->addWidget(m_pPulseGrp);
	m_pVMainLayout->addLayout(pHLayout);

	setLayout(m_pVMainLayout);
	resize(600, 400);
}

void QDcSignalMapDialog::InitData()
{
	m_pMinHzEdt->setText(QString::number(m_oInterParas.m_fGridFrequencyMinHz,'f',4));
	m_pMaxHzEdt->setText(QString::number(m_oInterParas.m_fGridFrequencyMaxHz,'f',4));
	m_pMinPulseEdt->setText(QString::number(m_oInterParas.m_fGenSpeedMinRpm,'f',2));
	m_pMaxPulseEdt->setText(QString::number(m_oInterParas.m_fGenSpeedMaxRpm,'f',2));

}


void QDcSignalMapDialog::InitConnect()
{
	connect(m_pMinHzEdt, SIGNAL(editingFinished()), this, SLOT(slot_MinHzEdtFinished()));
	connect(m_pMaxHzEdt, SIGNAL(editingFinished()), this, SLOT(slot_MaxHzEdtFinished()));
	connect(m_pMinPulseEdt, SIGNAL(editingFinished()), this, SLOT(slot_MinPulseEdtFinished()));
	connect(m_pMaxPulseEdt, SIGNAL(editingFinished()), this, SLOT(slot_MaxPulseEdtFinished()));

}

void QDcSignalMapDialog::slot_btnOK_Clicked()
{
	m_oInterParas.CopyOwn(m_pExternalParas);
	accept();
}

void QDcSignalMapDialog::slot_btnCancel_Clicked()
{
	reject();
}

void QDcSignalMapDialog::slot_MinHzEdtFinished()
{
	float fv = m_pMinHzEdt->text().toFloat();
	if( fv < 45.0 || fv > 55.0f)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("电网频率支持45~55Hz,请重新输入！"));
	}
	fv = setLimit(45.0, 55.0f, fv);
	if(fv > m_oInterParas.m_fGridFrequencyMaxHz)
	{
		m_oInterParas.m_fGridFrequencyMaxHz = fv;
		m_pMaxHzEdt->setText(QString::number(fv,'f',4));
	}

	m_oInterParas.m_fGridFrequencyMinHz = fv;
	m_pMinHzEdt->setText(QString::number(fv,'f',4));

}

void QDcSignalMapDialog::slot_MaxHzEdtFinished()
{
	float fv = m_pMaxHzEdt->text().toFloat();
	if( fv < 45.0 || fv > 55.0f)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("电网频率支持45~55Hz,请重新输入！"));
	}
	fv = setLimit(45.0, 55.0f, fv);
	if(fv < m_oInterParas.m_fGridFrequencyMinHz)
	{
		m_pMaxHzEdt->setText(QString::number(m_oInterParas.m_fGridFrequencyMinHz,'f',4));
	}

	m_oInterParas.m_fGridFrequencyMaxHz = fv;
	m_pMaxHzEdt->setText(QString::number(fv,'f',4));

}

void QDcSignalMapDialog::slot_MinPulseEdtFinished()
{
	float fv = m_pMinPulseEdt->text().toFloat();
	if( fv < 100 || fv > 10000)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("发电机转速支持100~10000转,请重新输入！"));
	}
	fv = setLimit(100, 10000, fv);
	if(fv > m_oInterParas.m_fGenSpeedMaxRpm)
	{
		m_oInterParas.m_fGenSpeedMaxRpm = fv;
		m_pMaxPulseEdt->setText(QString::number(fv,'f',2));
	}

	m_oInterParas.m_fGenSpeedMinRpm = fv;
	m_pMinPulseEdt->setText(QString::number(fv,'f',2));

}

void QDcSignalMapDialog::slot_MaxPulseEdtFinished()
{
	float fv = m_pMaxPulseEdt->text().toFloat();
	if( fv < 100 || fv > 10000)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("发电机转速支持100~10000转,请重新输入！"));
	}
	fv = setLimit(100, 10000, fv);
	if(fv < m_oInterParas.m_fGenSpeedMinRpm)
	{
		m_pMaxPulseEdt->setText(QString::number(m_oInterParas.m_fGenSpeedMaxRpm,'f',2));
	}

	m_oInterParas.m_fGenSpeedMaxRpm = fv;
	m_pMaxPulseEdt->setText(QString::number(fv,'f',2));
}
