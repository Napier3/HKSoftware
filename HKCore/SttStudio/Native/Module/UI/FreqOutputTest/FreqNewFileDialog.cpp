#include "FreqNewFileDialog.h"
#include "../SttTestCntrFrameBase.h"

QFreqNewFileDialog::QFreqNewFileDialog(tmt_FreqOutputParas *pFreqOutputParas, QWidget* parent): QDialog(parent)
{
	setWindowTitle(_T("新建文件"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(600, 400);
	setFixedSize(600,400);
	m_pFreqOutputParas = pFreqOutputParas;
	InitUI();
	InitConnect();
	InitData();
}

QFreqNewFileDialog::~QFreqNewFileDialog()
{

}

void QFreqNewFileDialog::InitUI()
{
	// 默认设置
	CString strText;
	m_pDefaultGroupBox = new QSttCheckableGroupBox(this);
	m_pDefaultGroupBox->setFont(*g_pSttGlobalFont);
	m_pDefaultGroupBox->setCheckable(true);
	strText = _T("默认设置");
	m_pDefaultGroupBox->setTitle(strText);
	QLabel *pRowLabel = new QLabel(this);
	pRowLabel->setFont(*g_pSttGlobalFont);
	strText = _T("行数");
	pRowLabel->setText(strText);
	m_pRowLineEdit = new QSttLineEdit(this);
	m_pRowLineEdit->setFont(*g_pSttGlobalFont);
	QLabel *pDurationLabel = new QLabel(this);
	pDurationLabel->setFont(*g_pSttGlobalFont);
	strText = _T("持续时长(ms)");
	pDurationLabel->setText(strText);
	m_pHoldTimeLineEdit = new QSttLineEdit(this);
	m_pHoldTimeLineEdit->setFont(*g_pSttGlobalFont);
	QLabel *pFreqLabel = new QLabel(this);
	pFreqLabel->setFont(*g_pSttGlobalFont);
	strText = _T("频率(Hz))");
	pFreqLabel->setText(strText);
	m_pFreqLineEdit = new QSttLineEdit(this);
	m_pFreqLineEdit->setFont(*g_pSttGlobalFont);
	QLabel *pCurrentLabel = new QLabel(this);
	pCurrentLabel->setFont(*g_pSttGlobalFont);
	strText = _T("直流电流(mA)");
	pCurrentLabel->setText(strText);
	m_pDcCurrentLineEdit = new QSttLineEdit(this);
	m_pDcCurrentLineEdit->setFont(*g_pSttGlobalFont);

	QGridLayout *pDefaultLayout = new QGridLayout;
	pDefaultLayout->addWidget(pRowLabel, 0, 0);
	pDefaultLayout->addWidget(m_pRowLineEdit, 0, 1);
	pDefaultLayout->addWidget(pDurationLabel, 0, 2);
	pDefaultLayout->addWidget(m_pHoldTimeLineEdit, 0, 3);
	pDefaultLayout->addWidget(pFreqLabel, 0, 4);
	pDefaultLayout->addWidget(m_pFreqLineEdit, 0, 5);
	pDefaultLayout->addWidget(pCurrentLabel, 1, 0);
	pDefaultLayout->addWidget(m_pDcCurrentLineEdit, 1, 1);
	m_pDefaultGroupBox->setLayout(pDefaultLayout);


	// 频率递变
	m_pFreqChangeGroupBox = new QSttCheckableGroupBox(this);
	m_pFreqChangeGroupBox->setCheckable(true);
	m_pFreqChangeGroupBox->setFont(*g_pSttGlobalFont);
	strText = _T("频率递变");
	m_pFreqChangeGroupBox->setTitle(strText);
	QLabel *pStartFreqLabel = new QLabel(this);
	pStartFreqLabel->setFont(*g_pSttGlobalFont);
	strText = _T("起值(Hz)");
	pStartFreqLabel->setText(strText);
	m_pStartFreqEdit = new QSttLineEdit(this);
	m_pStartFreqEdit->setFont(*g_pSttGlobalFont);
	QLabel *pEndFreqLabel = new QLabel(this);
	pEndFreqLabel->setFont(*g_pSttGlobalFont);
	strText = _T("终值(Hz)");
	pEndFreqLabel->setText(strText);
	m_pEndFreqEdit = new QSttLineEdit(this);
	m_pEndFreqEdit->setFont(*g_pSttGlobalFont);
	QLabel *pStepFreqLabel = new QLabel(this);
	pStepFreqLabel->setFont(*g_pSttGlobalFont);
	strText = _T("步长(mHz)");
	pStepFreqLabel->setText(strText);
	m_pStepFreqEdit = new QSttLineEdit(this);
	m_pStepFreqEdit->setFont(*g_pSttGlobalFont);
	QLabel *pChangeMethodLabel = new QLabel(this);
	pChangeMethodLabel->setFont(*g_pSttGlobalFont);
	strText = _T("变化方式:");
	pChangeMethodLabel->setText(strText);
	QStringList oRadioBtnList;
	oRadioBtnList << _T("始-终") << _T("始-终-始");
	m_ChangeFreqRadio[0] = new QRadioButton(oRadioBtnList[0], this);
	m_ChangeFreqRadio[0]->setFont(*g_pSttGlobalFont);
	m_ChangeFreqRadio[1] = new QRadioButton(oRadioBtnList[1], this);
	m_ChangeFreqRadio[1]->setFont(*g_pSttGlobalFont);

	QLabel *pDurationFreqLabel = new QLabel(this);
	pDurationFreqLabel->setFont(*g_pSttGlobalFont);
	strText = _T("持续时长(ms)");
	pDurationFreqLabel->setText(strText);
	m_pHoldTimeFreqLineEdit = new QSttLineEdit(this);
	m_pHoldTimeFreqLineEdit->setFont(*g_pSttGlobalFont);

	QGridLayout *pFreqChangeLayout = new QGridLayout;
	pFreqChangeLayout->addWidget(pStartFreqLabel, 0, 0);
	pFreqChangeLayout->addWidget(m_pStartFreqEdit, 0, 1);
	pFreqChangeLayout->addWidget(pEndFreqLabel, 0, 2);
	pFreqChangeLayout->addWidget(m_pEndFreqEdit, 0, 3);
	pFreqChangeLayout->addWidget(pStepFreqLabel, 0, 4);
	pFreqChangeLayout->addWidget(m_pStepFreqEdit, 0, 5);
	pFreqChangeLayout->addWidget(pChangeMethodLabel, 1, 0);
	pFreqChangeLayout->addWidget(m_ChangeFreqRadio[0], 1, 1);
	pFreqChangeLayout->addWidget(m_ChangeFreqRadio[1], 1, 2);
	pFreqChangeLayout->addWidget(pDurationFreqLabel, 1, 3);
	pFreqChangeLayout->addWidget(m_pHoldTimeFreqLineEdit, 1, 4);
	m_pFreqChangeGroupBox->setLayout(pFreqChangeLayout);


	// 直流电流递变
	m_pCurrentChangeGroupBox = new QSttCheckableGroupBox(this);
	m_pCurrentChangeGroupBox->setFont(*g_pSttGlobalFont);
	m_pCurrentChangeGroupBox->setCheckable(true);
	strText = _T("直流电流递变");
	m_pCurrentChangeGroupBox->setTitle(strText);
	QLabel *pStartCurrentLabel = new QLabel(this);
	pStartCurrentLabel->setFont(*g_pSttGlobalFont);
	strText = _T("起值(mA)");
	pStartCurrentLabel->setText(strText);
	m_pStartCurrentEdit = new QSttLineEdit(this);
	m_pStartCurrentEdit->setFont(*g_pSttGlobalFont);
	QLabel *pEndCurrentLabel = new QLabel(this);
	pEndCurrentLabel->setFont(*g_pSttGlobalFont);
	strText = _T("终值(mA)");
	pEndCurrentLabel->setText(strText);
	m_pEndCurrentEdit = new QSttLineEdit(this);
	m_pEndCurrentEdit->setFont(*g_pSttGlobalFont);
	QLabel *pStepCurrentLabel = new QLabel;
	pStepCurrentLabel->setFont(*g_pSttGlobalFont);
	strText = _T("步长(mA)");
	pStepCurrentLabel->setText(strText);
	m_pStepCurrentEdit = new QSttLineEdit(this);
	m_pStepCurrentEdit->setFont(*g_pSttGlobalFont);
	QLabel *pChangeMethodLabel1 = new QLabel(this);
	pChangeMethodLabel1->setFont(*g_pSttGlobalFont);
	strText = _T("变化方式:");
	pChangeMethodLabel1->setText(strText);
	m_ChangeCurrentRadio[0] = new QRadioButton(oRadioBtnList[0], this);
	m_ChangeCurrentRadio[0]->setFont(*g_pSttGlobalFont);
	m_ChangeCurrentRadio[1] = new QRadioButton(oRadioBtnList[1], this);
	m_ChangeCurrentRadio[1]->setFont(*g_pSttGlobalFont);
	QLabel *pDurationCurrentLabel = new QLabel;
	pDurationCurrentLabel->setFont(*g_pSttGlobalFont);
	strText = _T("持续时长(ms)");
	pDurationCurrentLabel->setText(strText);
	m_pHoldTimeCurrentLineEdit = new QSttLineEdit(this);
	m_pHoldTimeCurrentLineEdit->setFont(*g_pSttGlobalFont);

	QGridLayout *pCurrentChangeLayout = new QGridLayout;
	pCurrentChangeLayout->addWidget(pStartCurrentLabel, 0, 0);
	pCurrentChangeLayout->addWidget(m_pStartCurrentEdit, 0, 1);
	pCurrentChangeLayout->addWidget(pEndCurrentLabel, 0, 2);
	pCurrentChangeLayout->addWidget(m_pEndCurrentEdit, 0, 3);
	pCurrentChangeLayout->addWidget(pStepCurrentLabel, 0, 4);
	pCurrentChangeLayout->addWidget(m_pStepCurrentEdit, 0, 5);
	pCurrentChangeLayout->addWidget(pChangeMethodLabel1, 1, 0);
	pCurrentChangeLayout->addWidget(m_ChangeCurrentRadio[0], 1, 1);
	pCurrentChangeLayout->addWidget(m_ChangeCurrentRadio[1], 1, 2);
	pCurrentChangeLayout->addWidget(pDurationCurrentLabel, 1, 3);
	pCurrentChangeLayout->addWidget(m_pHoldTimeCurrentLineEdit, 1, 4);
	m_pCurrentChangeGroupBox->setLayout(pCurrentChangeLayout);

	QPushButton* pOKBtn = new QPushButton(this);
	strText = _T("确定");
	pOKBtn->setFont(*g_pSttGlobalFont);
	pOKBtn->setText(strText);
	QPushButton* pCancelBtn = new QPushButton(this);
	strText = _T("取消");
	pCancelBtn->setFont(*g_pSttGlobalFont);
	pCancelBtn->setText(strText);
	QHBoxLayout* pOkCancel_HBoxLayout = new QHBoxLayout;
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(pOKBtn);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(pCancelBtn);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);


	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pDefaultGroupBox);
	pMainLayout->addWidget(m_pFreqChangeGroupBox);
	pMainLayout->addWidget(m_pCurrentChangeGroupBox);
	pMainLayout->addLayout(pOkCancel_HBoxLayout);

	setLayout(pMainLayout);


	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QFreqNewFileDialog::InitConnect()
{
	connect(m_pDefaultGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	connect(m_pFreqChangeGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	connect(m_pCurrentChangeGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	
	connect(m_pRowLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_RowEditFinished()));
	connect(m_pHoldTimeLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pFreqLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pDcCurrentLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	
	connect(m_pStartFreqEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pEndFreqEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pStepFreqEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pHoldTimeFreqLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));

	connect(m_pStartCurrentEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pEndCurrentEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pStepCurrentEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pHoldTimeCurrentLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));


	for (int i = 0; i < 2; ++i)
	{
		connect(m_ChangeFreqRadio[i], SIGNAL(toggled(bool)), this, SLOT(slot_RadioChanged(bool)));
	}

	for (int i = 0; i < 2; ++i)
	{
		connect(m_ChangeCurrentRadio[i], SIGNAL(toggled(bool)), this, SLOT(slot_RadioChanged(bool)));
	}
}

void QFreqNewFileDialog::InitData()
{
	m_FreqOutputNewFile = &m_pFreqOutputParas->m_oFreqOutputNewFile;
	int nSetType = m_FreqOutputNewFile->m_nSetType;
	
	m_pDefaultGroupBox->setChecked(false);
	m_pFreqChangeGroupBox->setChecked(false);
	m_pCurrentChangeGroupBox->setChecked(false);

	switch (nSetType)
	{
	case 0:
		m_pDefaultGroupBox->setChecked(true);
		break;
	case 1:
		m_pFreqChangeGroupBox->setChecked(true);
		break;
	case 2:
		m_pCurrentChangeGroupBox->setChecked(true);
		break;
	}

	m_pRowLineEdit->setText(QString::number(m_FreqOutputNewFile->m_nRowCount,'f',0));
	m_pHoldTimeLineEdit->setText(QString::number(m_FreqOutputNewFile->m_fOutPutTime,'f',0));
	m_pFreqLineEdit->setText(QString::number(m_FreqOutputNewFile->m_fFrequency,'f',4));
	m_pDcCurrentLineEdit->setText(QString::number(m_FreqOutputNewFile->m_fDCCurrent,'f',4));

	m_pStartFreqEdit->setText(QString::number(m_FreqOutputNewFile->m_fStartFreq,'f',4));
	m_pEndFreqEdit->setText(QString::number(m_FreqOutputNewFile->m_fEndFreq,'f',4));
	m_pStepFreqEdit->setText(QString::number(m_FreqOutputNewFile->m_fStepFreq,'f',4));
	m_pHoldTimeFreqLineEdit->setText(QString::number(m_FreqOutputNewFile->m_fFreqOutPutTime,'f',0));
	if (m_FreqOutputNewFile->m_nFreqChangeMode == 0)
	{
		m_ChangeFreqRadio[0]->setChecked(true);
	}
	else
	{
		m_ChangeFreqRadio[1]->setChecked(true);
	}

	m_pStartCurrentEdit->setText(QString::number(m_FreqOutputNewFile->m_fStartCurrent,'f',4));
	m_pEndCurrentEdit->setText(QString::number(m_FreqOutputNewFile->m_fEndCurrent,'f',4));
	m_pStepCurrentEdit->setText(QString::number(m_FreqOutputNewFile->m_fStepCurrent,'f',4));
	m_pHoldTimeCurrentLineEdit->setText(QString::number(m_FreqOutputNewFile->m_fCurrentOutPutTime,'f',0));
	if (m_FreqOutputNewFile->m_nCurrentChangeMode == 0)
	{
		m_ChangeCurrentRadio[0]->setChecked(true);
	}
	else
	{
		m_ChangeCurrentRadio[1]->setChecked(true);
	}
}

void QFreqNewFileDialog::slot_btnOK_Clicked()
{
	if (m_pDefaultGroupBox->isChecked())
	{
		m_FreqOutputNewFile->m_nSetType = 0;
	}
	else if (m_pFreqChangeGroupBox->isChecked())
	{
		m_FreqOutputNewFile->m_nSetType = 1;
	}
	else
	{
		m_FreqOutputNewFile->m_nSetType = 2;
	}

	if (m_ChangeFreqRadio[0]->isChecked())
	{
		m_FreqOutputNewFile->m_nFreqChangeMode = 0;
	}
	else if (m_ChangeFreqRadio[1]->isChecked())
	{
		m_FreqOutputNewFile->m_nFreqChangeMode = 1;
	}

	if (m_ChangeCurrentRadio[0]->isChecked())
	{
		m_FreqOutputNewFile->m_nCurrentChangeMode = 0;
	}
	else if (m_ChangeCurrentRadio[1]->isChecked())
	{
		m_FreqOutputNewFile->m_nCurrentChangeMode = 1;
	}

	m_FreqOutputNewFile->m_nRowCount = m_pRowLineEdit->text().toInt();
	m_FreqOutputNewFile->m_fOutPutTime = m_pHoldTimeLineEdit->text().toFloat();
	m_FreqOutputNewFile->m_fFrequency = m_pFreqLineEdit->text().toFloat();
	m_FreqOutputNewFile->m_fDCCurrent = m_pDcCurrentLineEdit->text().toFloat();

	m_FreqOutputNewFile->m_fStartFreq = m_pStartFreqEdit->text().toFloat();
	m_FreqOutputNewFile->m_fEndFreq = m_pEndFreqEdit->text().toFloat();
	m_FreqOutputNewFile->m_fStepFreq = m_pStepFreqEdit->text().toFloat();
	m_FreqOutputNewFile->m_fFreqOutPutTime = m_pHoldTimeFreqLineEdit->text().toFloat();

	m_FreqOutputNewFile->m_fStartCurrent = m_pStartCurrentEdit->text().toFloat();
	m_FreqOutputNewFile->m_fEndCurrent = m_pEndCurrentEdit->text().toFloat();
	m_FreqOutputNewFile->m_fStepCurrent = m_pStepCurrentEdit->text().toFloat();
	m_FreqOutputNewFile->m_fCurrentOutPutTime = m_pHoldTimeCurrentLineEdit->text().toFloat();

	emit sig_UpdateTable();
	accept();
}

void QFreqNewFileDialog::slot_btnCancel_Clicked()
{
	close();
}

void QFreqNewFileDialog::slot_GroupBoxtoggled( bool bValue )
{
	QGroupBox* pGroupBox = qobject_cast<QGroupBox*>(sender());
	if (pGroupBox == NULL)
	{
		return;
	}
	m_pDefaultGroupBox->blockSignals(true);
	m_pFreqChangeGroupBox->blockSignals(true);
	m_pCurrentChangeGroupBox->blockSignals(true);

	if (pGroupBox == m_pDefaultGroupBox)
	{
		m_pDefaultGroupBox->setChecked(true);
		m_pFreqChangeGroupBox->setChecked(false);
		m_pCurrentChangeGroupBox->setChecked(false);
	}
	else if (pGroupBox == m_pFreqChangeGroupBox)
	{
		m_pDefaultGroupBox->setChecked(false);
		m_pFreqChangeGroupBox->setChecked(true);
		m_pCurrentChangeGroupBox->setChecked(false);
	}
	else
	{
		m_pDefaultGroupBox->setChecked(false);
		m_pFreqChangeGroupBox->setChecked(false);
		m_pCurrentChangeGroupBox->setChecked(true);
	}

	m_pDefaultGroupBox->blockSignals(false);
	m_pFreqChangeGroupBox->blockSignals(false);
	m_pCurrentChangeGroupBox->blockSignals(false);
}

void QFreqNewFileDialog::slot_RowEditFinished()
{
	int RowCount = m_pRowLineEdit->text().toInt();
	if (RowCount < 0)
	{
		RowCount = 0;
	}
	else if (RowCount > 1000)
	{
		RowCount = 1000;
	}

	m_pRowLineEdit->setText(QString::number(RowCount,'f',0));
}

void QFreqNewFileDialog::slot_LineEditFinished()
{
	QSttLineEdit* pLineEdit = qobject_cast<QSttLineEdit*>(sender());
	float fv = pLineEdit->text().toFloat();
	float fMax = 0,fMin = 0;
	long nUnit = 0;
	if (pLineEdit == m_pHoldTimeLineEdit || pLineEdit == m_pHoldTimeFreqLineEdit || pLineEdit == m_pHoldTimeCurrentLineEdit)
	{
		fMax = 3600;
		nUnit = 0;
	}
	else if (pLineEdit == m_pFreqLineEdit || pLineEdit == m_pEndFreqEdit ||  pLineEdit == m_pStepFreqEdit)
	{
		fMin = 44;
		fMax = 55;
		nUnit = 4;
		if (pLineEdit == m_pEndFreqEdit)
		{
			fMin = m_pStartFreqEdit->text().toFloat();
		}
	}
	else if (pLineEdit == m_pEndCurrentEdit || pLineEdit == m_pDcCurrentLineEdit || pLineEdit == m_pStepCurrentEdit)
	{
		fMax = 20;
		nUnit = 4;
		if (pLineEdit == m_pEndCurrentEdit)
		{
			fMin = m_pStartCurrentEdit->text().toFloat();
		}
	}
	else if (pLineEdit == m_pStartFreqEdit || pLineEdit == m_pStartCurrentEdit)
	{
		fMin = 44;
		nUnit = 4;
		if (pLineEdit == m_pStartFreqEdit)
		{
			fMax = m_pEndFreqEdit->text().toFloat();
		}
		else
		{
			fMax = m_pEndCurrentEdit->text().toFloat();
		}
	}
	fv = setLimit(fMin,fMax,fv);

	pLineEdit->setText(QString::number(fv,'f',nUnit));
}



void QFreqNewFileDialog::slot_RadioChanged( bool bValue )
{
	if (!bValue)
	{
		return;
	}

// 	QRadioButton* pRadioBtn = qobject_cast<QRadioButton*>(sender());
// 
// 	if (pRadioBtn == m_ChangeFreqRadio[0])
// 	{
// 		m_FreqOutputNewFile->m_nFreqChangeMode = 0;
// 	}
// 	else if (pRadioBtn == m_ChangeFreqRadio[1])
// 	{
// 		m_FreqOutputNewFile->m_nFreqChangeMode = 1;
// 	}
// 	else if (pRadioBtn == m_ChangeCurrentRadio[0])
// 	{
// 		m_FreqOutputNewFile->m_nCurrentChangeMode = 1;
// 	}
// 	else if (pRadioBtn == m_ChangeCurrentRadio[1])
// 	{
// 		m_FreqOutputNewFile->m_nCurrentChangeMode = 1;
// 	}
}

