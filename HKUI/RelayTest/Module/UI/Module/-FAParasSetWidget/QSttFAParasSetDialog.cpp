#include "QSttFAParasSetDialog.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../UI/SttTestCntrFrameBase.h"
#include "../../../../Module/SttGlobalDef.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include <QComboBox>

QSttFAParasSetDialog::QSttFAParasSetDialog(QWidget *parent) : 
ui(new Ui::QSttFAParasSetDialog)
{
	ui->setupUi(this);
	m_pFaParaSet = new tmt_FaParasSet;
	InitUI();
	SetFAParasFont();
	InitConnections();
	InitItemOutput();
	InitItemSignal();
}

QSttFAParasSetDialog::~QSttFAParasSetDialog()
{

}

void QSttFAParasSetDialog::InitUI()
{
	QString styleSheet = "QLineEdit {"
		"    width: 85px;"
		"    max-width: 85px;"
		"    min-width: 85px;"
		"    height: 30px;"
		"}";

	ui->m_editRatedVol->setStyleSheet(styleSheet);
	ui->m_editResidualVol->setStyleSheet(styleSheet);
	ui->m_editRatedCur->setStyleSheet(styleSheet);
	ui->m_editFaultCur->setStyleSheet(styleSheet);
	ui->m_editFailureCur->setStyleSheet(styleSheet);
	ui->m_editErrorTime->setStyleSheet(styleSheet);
	ui->m_editxTime->setStyleSheet(styleSheet);
	ui->m_edityTime->setStyleSheet(styleSheet);
	ui->m_editzTime->setStyleSheet(styleSheet);
	ui->m_editxlTime->setStyleSheet(styleSheet);
	ui->m_editsTime->setStyleSheet(styleSheet);

	ui->m_editRatedVol->setText(QString::number(m_pFaParaSet->m_fRatedVoltage, 'f', 2) + "V"); 
	ui->m_editResidualVol->setText(QString::number(m_pFaParaSet->m_fResidualVoltage, 'f', 2) + "V");
	ui->m_editRatedCur->setText(QString::number(m_pFaParaSet->m_fRatedCurrent, 'f', 3) + "A");
	ui->m_editFaultCur->setText(QString::number(m_pFaParaSet->m_fFaultCurrent, 'f', 3) + "A");
	ui->m_editFailureCur->setText(QString::number(m_pFaParaSet->m_fFailureDuration, 'f', 3) + "s");
	ui->m_editErrorTime->setText(QString::number(m_pFaParaSet->m_fErrorAssessTime, 'f', 3) + "s");
	ui->m_editxTime->setText(QString::number(m_pFaParaSet->m_fxTime, 'f', 3) + "s");
	ui->m_edityTime->setText(QString::number(m_pFaParaSet->m_fyTime, 'f', 3) + "s");
	ui->m_editzTime->setText(QString::number(m_pFaParaSet->m_fzTime, 'f', 3) + "s");
	ui->m_editxlTime->setText(QString::number(m_pFaParaSet->m_fxlTime, 'f', 3) + "s");
	ui->m_editsTime->setText(QString::number(m_pFaParaSet->m_fsTime, 'f', 3) + "s");

	CString m_strVol[] = { _T("UAB"), _T("UCB") };
	for (int i = 0; i < 2; i++) 
	{  
		ui->m_cmbTermPowerVol->addItem(m_strVol[i]);  
		ui->m_cmbTermLoadVol->addItem(m_strVol[i]);  
	}
	ui->m_cmbTermPowerVol->setCurrentIndex(0);
	ui->m_cmbTermLoadVol->setCurrentIndex(1);

 	if (g_nBinCount > MAX_BINARYIN_COUNT)
 	{
 		g_nBinCount = MAX_BINARYIN_COUNT;
 	}

	QString strBinName;
	for (int i = 0; i < g_nBinCount; i++)
	{
		if (i == 0)
		{
			strBinName = g_sLangTxt_Manual_InA;
		}
		else if (i == 1)
		{
			strBinName = g_sLangTxt_Manual_InB;
		}
		else if (i == 2)
		{
			strBinName= g_sLangTxt_Manual_InC;
		}
		else if (i == 3)
		{
			strBinName = g_sLangTxt_Manual_InD;
		}
		else if (i == 4)
		{
			strBinName = g_sLangTxt_Manual_InE;
		}
		else if (i == 5)
		{
			strBinName = g_sLangTxt_Manual_InF;
		}
		else if (i == 6)
		{
			strBinName = g_sLangTxt_Manual_InG;
		}
		else
		{
			break;
		}

		ui->m_cmbTermCloseOutput->addItem(strBinName);
		if (i != 0) 
		{
			ui->m_cmbTermOpenOutput->addItem(strBinName);
		}
	}

	if (g_nBinCount > MAX_BINARYIN_COUNT)
	{
		g_nBinCount = MAX_BINARYIN_COUNT;
	}

	QString strBin0Name;
	for (int i = 0; i < g_nBinCount; i++)
	{
		if (i == 0)
		{
			strBin0Name = g_sLangTxt_Manual_Out1;
		}
		else if (i == 1)
		{
			strBin0Name = g_sLangTxt_Manual_Out2;
		}
		else if (i == 2)
		{
			strBin0Name = g_sLangTxt_Manual_Out3;
		}
		else if (i == 3)
		{
			strBin0Name = g_sLangTxt_Manual_Out4;
		}
		else if (i == 4)
		{
			strBin0Name = g_sLangTxt_Manual_Out5;
		}
		else if (i == 5)
		{
			strBin0Name = g_sLangTxt_Manual_Out6;
		}
		else if (i == 6)
		{
			strBin0Name = g_sLangTxt_Manual_Out7;
		}
		else
		{
			break;
		}
		ui->m_cmbTermCloseSignal->addItem(strBin0Name);
		if (i != 0) 
		{
			ui->m_cmbTermQuantileSignal->addItem(strBin0Name);
		}
	}
}

void QSttFAParasSetDialog::SetData(tmt_FaParasSet *pFaParaSet)
{
	m_pFaParaSet = pFaParaSet;
	ui->m_editRatedVol->setText(QString::number(m_pFaParaSet->m_fRatedVoltage, 'f', 2) + "V"); 
	ui->m_editResidualVol->setText(QString::number(m_pFaParaSet->m_fResidualVoltage, 'f', 2) + "V");
	ui->m_editRatedCur->setText(QString::number(m_pFaParaSet->m_fRatedCurrent, 'f', 3) + "A");
	ui->m_editFaultCur->setText(QString::number(m_pFaParaSet->m_fFaultCurrent, 'f', 3) + "A");
	ui->m_editFailureCur->setText(QString::number(m_pFaParaSet->m_fFailureDuration, 'f', 3) + "s");
	ui->m_editErrorTime->setText(QString::number(m_pFaParaSet->m_fErrorAssessTime, 'f', 3) + "s");
	ui->m_editxTime->setText(QString::number(m_pFaParaSet->m_fxTime, 'f', 3) + "s");
	ui->m_edityTime->setText(QString::number(m_pFaParaSet->m_fyTime, 'f', 3) + "s");
	ui->m_editzTime->setText(QString::number(m_pFaParaSet->m_fzTime, 'f', 3) + "s");
	ui->m_editxlTime->setText(QString::number(m_pFaParaSet->m_fxlTime, 'f', 3) + "s");
	ui->m_editsTime->setText(QString::number(m_pFaParaSet->m_fsTime, 'f', 3) + "s");
}

void QSttFAParasSetDialog::SetFAParasFont()
{
	ui->m_editRatedVol->setFont(*g_pSttGlobalFont);
	ui->m_editResidualVol->setFont(*g_pSttGlobalFont);
	ui->m_editRatedCur->setFont(*g_pSttGlobalFont);
	ui->m_editFaultCur->setFont(*g_pSttGlobalFont);
	ui->m_editFailureCur->setFont(*g_pSttGlobalFont);
	ui->m_editErrorTime->setFont(*g_pSttGlobalFont);
	ui->m_editxTime->setFont(*g_pSttGlobalFont);
	ui->m_edityTime->setFont(*g_pSttGlobalFont);
	ui->m_editzTime->setFont(*g_pSttGlobalFont);
	ui->m_editxlTime->setFont(*g_pSttGlobalFont);
	ui->m_editsTime->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermPowerVol->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermLoadVol->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermCloseOutput->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermOpenOutput->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermCloseSignal->setFont(*g_pSttGlobalFont);
	ui->m_cmbTermQuantileSignal->setFont(*g_pSttGlobalFont);
	ui->m_labRatedVol->setFont(*g_pSttGlobalFont);
	ui->m_labFailureCur->setFont(*g_pSttGlobalFont);
	ui->m_labFaultCur->setFont(*g_pSttGlobalFont);
	ui->m_labRatedCur->setFont(*g_pSttGlobalFont);
	ui->m_labErrorTime->setFont(*g_pSttGlobalFont);
	ui->m_labResidualVol->setFont(*g_pSttGlobalFont);
	ui->m_labTermLoadVol->setFont(*g_pSttGlobalFont);
	ui->m_labTermPowerVol->setFont(*g_pSttGlobalFont);
	ui->m_labTermCloseOutput->setFont(*g_pSttGlobalFont);
	ui->m_labTermOpenOutput->setFont(*g_pSttGlobalFont);
	ui->m_labTermCloseSignal->setFont(*g_pSttGlobalFont);
	ui->m_labTermQuantileSignal->setFont(*g_pSttGlobalFont);
	ui->m_labxTime->setFont(*g_pSttGlobalFont);
	ui->m_labyTime->setFont(*g_pSttGlobalFont);
	ui->m_labzTime->setFont(*g_pSttGlobalFont);
	ui->m_labxlTime->setFont(*g_pSttGlobalFont);
	ui->m_labsTime->setFont(*g_pSttGlobalFont);
}

void QSttFAParasSetDialog::InitConnections()
{
	//edit值
	connect(ui->m_editRatedVol, SIGNAL(editingFinished()), this, SLOT(slot_m_editRatedVol()));
	connect(ui->m_editResidualVol, SIGNAL(editingFinished()), this, SLOT(slot_m_editResidualVol()));
	connect(ui->m_editRatedCur, SIGNAL(editingFinished()), this, SLOT(slot_m_editRatedCur()));
	connect(ui->m_editFaultCur, SIGNAL(editingFinished()), this, SLOT(slot_m_editFaultCur()));
	connect(ui->m_editFailureCur, SIGNAL(editingFinished()), this, SLOT(slot_m_editFailureCur()));
	connect(ui->m_editErrorTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editErrorTime()));
	connect(ui->m_editxTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editxTime()));
	connect(ui->m_edityTime, SIGNAL(editingFinished()), this, SLOT(slot_m_edityTime()));
	connect(ui->m_editzTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editzTime()));
	connect(ui->m_editxlTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editxlTime()));
	connect(ui->m_editsTime, SIGNAL(editingFinished()), this, SLOT(slot_m_editsTime()));

	//UAB UCB
	connect(ui->m_cmbTermPowerVol, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermVolIndexChanged(int)));
	connect(ui->m_cmbTermLoadVol, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermVolIndexChanged(int)));

	//开入
	connect(ui->m_cmbTermCloseOutput, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermCloseOutputIndexChanged(int)));
	connect(ui->m_cmbTermOpenOutput, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermOpenOutputIndexChanged(int)));

	//开出
	connect(ui->m_cmbTermCloseSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermCloseSignalIndexChanged(int)));
	connect(ui->m_cmbTermQuantileSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TermQuantileSignalIndexChanged(int)));

}

void QSttFAParasSetDialog::slot_TermVolIndexChanged(int index)
{
	if (index >= 0)
	{
		QComboBox* senderComboBox = qobject_cast<QComboBox*>(sender()); // 获取发送信号的下拉框
		QComboBox* otherComboBox = NULL; // 另一个下拉框

		if (senderComboBox == ui->m_cmbTermPowerVol)
		{
			otherComboBox = ui->m_cmbTermLoadVol;
		}
		else if (senderComboBox == ui->m_cmbTermLoadVol)
		{
			otherComboBox = ui->m_cmbTermPowerVol;
		}

		if (otherComboBox != NULL)
		{
			if (otherComboBox->currentIndex() == index)
			{
				int otherIndex = (index + 1) % otherComboBox->count();
				otherComboBox->setCurrentIndex(otherIndex);
			}
		}

		int currentIndex = senderComboBox->currentIndex();
		if (senderComboBox == ui->m_cmbTermPowerVol)
		{
			m_pFaParaSet->m_nTermPowerVol = currentIndex; // 更新电源电压到结构体
		}
		else if (senderComboBox == ui->m_cmbTermLoadVol)
		{
			m_pFaParaSet->m_nTermLoadVol = currentIndex; // 更新负荷电压到结构体
		}
	}
}

void QSttFAParasSetDialog::slot_TermCloseOutputIndexChanged(int index) 
{
	if (index >= 0)
	{
		QComboBox* senderComboBox = qobject_cast<QComboBox*>(sender()); // 获取发送信号的下拉框
		QComboBox* otherComboBox = NULL; // 另一个下拉框

		if (senderComboBox == ui->m_cmbTermCloseOutput)
		{
			otherComboBox = ui->m_cmbTermOpenOutput;
		}
		if (otherComboBox != NULL)
		{
			otherComboBox->clear();
			InsertItemOutput(index,otherComboBox);
		}
		QString currentText = senderComboBox->currentText();
		m_pFaParaSet->m_strCloseOutput = currentText;
	}
}

void QSttFAParasSetDialog::slot_TermOpenOutputIndexChanged(int index) 
{
	if (index >= 0)
	{
		QComboBox* senderComboBox = qobject_cast<QComboBox*>(sender()); // 获取发送信号的下拉框
		QComboBox* otherComboBox = NULL; // 另一个下拉框

		if (senderComboBox == ui->m_cmbTermCloseOutput)
		{
			otherComboBox = ui->m_cmbTermOpenOutput;
		}
		if (otherComboBox != NULL)
		{
			otherComboBox->clear();
			InsertItemOutput(index,otherComboBox);
		}
		QString currentText = senderComboBox->currentText();
		m_pFaParaSet->m_strOpenOutput = currentText;
	}
}

void QSttFAParasSetDialog::slot_TermCloseSignalIndexChanged(int index)
{
 	if (index >= 0)
 	{
 		QComboBox* senderComboBox = qobject_cast<QComboBox*>(sender()); // 获取发送信号的下拉框
 		QComboBox* otherComboBox = NULL; // 另一个下拉框

 		if (senderComboBox == ui->m_cmbTermCloseSignal)
		{
 			otherComboBox = ui->m_cmbTermQuantileSignal;
		}
		if (otherComboBox != NULL)
		{
			otherComboBox->clear();
			InsertItemSignal(index,otherComboBox);
		}
		QString currentText = senderComboBox->currentText();
		m_pFaParaSet->m_strCloseSignal = currentText;
	}
}

void QSttFAParasSetDialog::slot_TermQuantileSignalIndexChanged(int index)
{
	if (index >= 0)
	{
		QComboBox* senderComboBox = qobject_cast<QComboBox*>(sender()); // 获取发送信号的下拉框
		QComboBox* otherComboBox = NULL; // 另一个下拉框

		if (senderComboBox == ui->m_cmbTermCloseSignal)
		{
			otherComboBox = ui->m_cmbTermQuantileSignal;
		}
		if (otherComboBox != NULL)
		{
			otherComboBox->clear();
			InsertItemSignal(index,otherComboBox);
		}
		QString currentText = senderComboBox->currentText();
		m_pFaParaSet->m_strQuantileSignal = currentText;
	}
}

void QSttFAParasSetDialog::InsertItemOutput(int index, QComboBox *pCombox) //向下拉框插入选项
{
	foreach(int i,m_pOutputItem.keys())
	{
		if(i != index)
		{
			pCombox->addItem(m_pOutputItem.value(i));
		}
	}
}

void QSttFAParasSetDialog::InitItemOutput()  //初始化 输入选项的名称
{
	QString strBinName;
	if (g_nBinCount > MAX_BINARYIN_COUNT)
	{
		g_nBinCount = MAX_BINARYIN_COUNT;
	}

	for (int i = 0; i < g_nBinCount; i++)
	{
		if (i == 0)
		{
			strBinName = g_sLangTxt_Manual_InA;
		}
		else if (i == 1)
		{
			strBinName = g_sLangTxt_Manual_InB;
		}
		else if (i == 2)
		{
			strBinName = g_sLangTxt_Manual_InC;
		}
		else if (i == 3)
		{
			strBinName = g_sLangTxt_Manual_InD;
		}
		else if (i == 4)
		{
			strBinName = g_sLangTxt_Manual_InE;
		}
		else if (i == 5)
		{
			strBinName = g_sLangTxt_Manual_InF;
		}
		else if (i == 6)
		{
			strBinName = g_sLangTxt_Manual_InG;
		}
		else
		{
			break;
		}
		m_pOutputItem[i] = strBinName;
	}
}

void QSttFAParasSetDialog::InsertItemSignal(int index, QComboBox *pCombox) 
{
	foreach(int i,m_pSignalItem.keys())
	{
		if(i != index)
		{ 			
			pCombox->addItem(m_pSignalItem.value(i));
		}
	}
}

void QSttFAParasSetDialog::InitItemSignal()
{
	if (g_nBinCount > MAX_BINARYIN_COUNT)
	{
		g_nBinCount = MAX_BINARYIN_COUNT;
	}

	QString strBin0Name;
	for (int i = 0; i < g_nBinCount; i++)
	{
		if (i == 0)
		{
			strBin0Name = g_sLangTxt_Manual_Out1;
		}
		else if (i == 1)
		{
			strBin0Name = g_sLangTxt_Manual_Out2;
		}
		else if (i == 2)
		{
			strBin0Name = g_sLangTxt_Manual_Out3;
		}
		else if (i == 3)
		{
			strBin0Name = g_sLangTxt_Manual_Out4;
		}
		else if (i == 4)
		{
			strBin0Name = g_sLangTxt_Manual_Out5;
		}
		else if (i == 5)
		{
			strBin0Name = g_sLangTxt_Manual_Out6;
		}
		else if (i == 6)
		{
			strBin0Name = g_sLangTxt_Manual_Out7;
		}
		else
		{
			break;
		}
		m_pSignalItem[i] = strBin0Name;
	}
}

void QSttFAParasSetDialog::Update_Edit_Unit()
{
	QLineEdit* edit = qobject_cast<QLineEdit*>(sender());
	if (edit) 
	{
		QString unit;
		int decimals;
		double maxValue;
		if (edit == ui->m_editRatedVol || edit == ui->m_editResidualVol) 
		{
			unit = "V";
			decimals = 2;
			maxValue = 120.00;
		} 
		else if (edit == ui->m_editRatedCur || edit == ui->m_editFaultCur) 
		{
			unit = "A";
			decimals = 3;
			maxValue = 10.000;
		} 
		else 
		{
			unit = "s";
			decimals = 3;
			maxValue = 999.999;
		}
		QString value = edit->text();
		value.replace(unit, "");
		double numericValue = value.toDouble();

		 // 如果输入为负数，则改为0
		if (numericValue < 0)
		{
			numericValue = 0;
		}

		if (numericValue > maxValue && maxValue >= 0)
		{
			numericValue = maxValue; // 更新为限制后的最大值
		}
		edit->setText(QString::number(numericValue, 'f', decimals) + unit);

		// 更新结构体中的值
		if (edit == ui->m_editRatedVol)
		{
			m_pFaParaSet->m_fRatedVoltage = numericValue;
		}
		else if (edit == ui->m_editResidualVol)
		{
			m_pFaParaSet->m_fResidualVoltage = numericValue;
		}
		else if (edit == ui->m_editRatedCur)
		{
			m_pFaParaSet->m_fRatedCurrent = numericValue;
		}
		else if (edit == ui->m_editFaultCur)
		{
			m_pFaParaSet->m_fFaultCurrent = numericValue;
		}
		else if (edit == ui->m_editFailureCur)
		{
			m_pFaParaSet->m_fFailureDuration = numericValue;
		}
		else if (edit == ui->m_editErrorTime)
		{
			m_pFaParaSet->m_fErrorAssessTime = numericValue;
		}
		else if (edit == ui->m_editxTime)
		{
			m_pFaParaSet->m_fxTime = numericValue;
		}
		else if (edit == ui->m_edityTime)
		{
			m_pFaParaSet->m_fyTime = numericValue;
		}
		else if (edit == ui->m_editzTime)
		{
			m_pFaParaSet->m_fzTime = numericValue;
		}
		else if (edit == ui->m_editxlTime)
		{
			m_pFaParaSet->m_fxlTime = numericValue;
		}
		else if (edit == ui->m_editsTime)
		{
			m_pFaParaSet->m_fsTime = numericValue;
		}
		else
		{
			return;
		}
	}
}

// 槽函数 - m_editRatedVol
void QSttFAParasSetDialog::slot_m_editRatedVol()
{
	float newValue0 = ui->m_editRatedVol->text().toFloat();
	if (m_pFaParaSet->m_fRatedVoltage != newValue0)
	{
		m_pFaParaSet->m_fRatedVoltage = newValue0;
	}
	Update_Edit_Unit();
}

// 槽函数 - m_editResidualVol
void QSttFAParasSetDialog::slot_m_editResidualVol()
{

	 float newValue1 = ui->m_editResidualVol->text().toFloat();
	 if (m_pFaParaSet->m_fResidualVoltage != newValue1)
	 {
		 m_pFaParaSet->m_fResidualVoltage = newValue1;
	 }
	 Update_Edit_Unit();
}

// 槽函数 - m_editRatedCur
void QSttFAParasSetDialog::slot_m_editRatedCur()
{

	float newValue2 = ui->m_editRatedCur->text().toFloat();
	if (m_pFaParaSet->m_fRatedCurrent != newValue2)
	{
		m_pFaParaSet->m_fRatedCurrent = newValue2;
	}
	Update_Edit_Unit();
}

// 槽函数 - m_editFaultCur
void QSttFAParasSetDialog::slot_m_editFaultCur()
{

	float newValue3 = ui->m_editFaultCur->text().toFloat();
	if (m_pFaParaSet->m_fFaultCurrent != newValue3)
	{
		m_pFaParaSet->m_fFaultCurrent = newValue3;
	}
	Update_Edit_Unit();
}

// 槽函数 - m_editFailureCur
void QSttFAParasSetDialog::slot_m_editFailureCur()
{

	float newValue4 = ui->m_editFailureCur->text().toFloat();
	if (m_pFaParaSet->m_fFailureDuration != newValue4)
	{
		m_pFaParaSet->m_fFailureDuration = newValue4;
	}
	Update_Edit_Unit();
}

// 槽函数 - m_editErrorTime
void QSttFAParasSetDialog::slot_m_editErrorTime()
{

	float newValue5 = ui->m_editErrorTime->text().toFloat();
	if (m_pFaParaSet->m_fErrorAssessTime != newValue5)
	{
		m_pFaParaSet->m_fErrorAssessTime = newValue5;
	}
	Update_Edit_Unit();
}

// 槽函数 - m_fxTime
void QSttFAParasSetDialog::slot_m_editxTime()
{

	float newValue6 = ui->m_editxTime->text().toFloat();
	if (m_pFaParaSet->m_fxTime != newValue6)
	{
		m_pFaParaSet->m_fxTime = newValue6;
	}
	Update_Edit_Unit();
}

// 槽函数 - m_fyTime
void QSttFAParasSetDialog::slot_m_edityTime()
{

	float newValue7 = ui->m_edityTime->text().toFloat();
	if (m_pFaParaSet->m_fyTime != newValue7)
	{
		m_pFaParaSet->m_fyTime = newValue7;
	}
	Update_Edit_Unit();
}

// 槽函数 - m_editzTime
void QSttFAParasSetDialog::slot_m_editzTime()
{

	float newValue8 = ui->m_editzTime->text().toFloat();
	if (m_pFaParaSet->m_fzTime != newValue8)
	{
		m_pFaParaSet->m_fzTime = newValue8;
	}
	Update_Edit_Unit();
}

// 槽函数 - m_editxlTime
void QSttFAParasSetDialog::slot_m_editxlTime()
{

	float newValue9 = ui->m_editxlTime->text().toFloat();
	if (m_pFaParaSet->m_fxlTime != newValue9)
	{
		m_pFaParaSet->m_fxlTime = newValue9;
	}
	Update_Edit_Unit();
}

// 槽函数 - m_editsTime
void QSttFAParasSetDialog::slot_m_editsTime()
{

	float newValue10 = ui->m_editsTime->text().toFloat();
	if (m_pFaParaSet->m_fsTime != newValue10)
	{
		m_pFaParaSet->m_fsTime = newValue10;
	}
	Update_Edit_Unit();
}

