#include "SmvAbnormalQualityset.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../Module/CommonMethod/commonMethod.h"
//#include "../../SttTestCntrFrameBase.h"

QSmvAbnormalQualitySet::QSmvAbnormalQualitySet(QList<int> &listQuality,QWidget *parent)
: QDialog(parent)
{
	ui = new Ui::SmvAbnormalQualitySet;
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	
	SetSmvAbnormalQualityFont();
	for (int i=0;i<listQuality.size();i++)
	{
		m_listQualityParas.append(listQuality.at(i));
	}
	
	initData();
        InitLanguage();

	connect(ui->pbn_OK,SIGNAL(clicked()),this,SLOT(slot_pbn_OKClicked()));
	connect(ui->pbn_Cancle,SIGNAL(clicked()),this,SLOT(slot_pbn_CancelClicked()));

	connect(ui->cmb_bit1,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit1StateChanged(int)));
	connect(ui->cmb_bit2,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit2StateChanged(int)));
	connect(ui->cmb_bit3,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit3StateChanged(int)));
	connect(ui->cmb_bit4,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit4StateChanged(int)));
	connect(ui->cmb_bit5,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit5StateChanged(int)));
	connect(ui->cmb_bit6,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit6StateChanged(int)));
	connect(ui->cmb_bit7,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit7StateChanged(int)));
	connect(ui->cmb_bit8,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit8StateChanged(int)));
	connect(ui->cmb_bit9,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit9StateChanged(int)));
	connect(ui->cmb_bit10,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit10StateChanged(int)));
	connect(ui->cmb_bit11,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit11StateChanged(int)));
	connect(ui->cmb_bit12,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_bit12StateChanged(int)));
	connect(ui->cmb_DispType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_DispTypeStateChanged(int)));
	connect(ui->lineEdit,SIGNAL(clicked()),this,SLOT(slot_lne_DispTypeKeyBoard()));
}

QSmvAbnormalQualitySet::~QSmvAbnormalQualitySet()
{
	delete ui;
}

void QSmvAbnormalQualitySet::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui->groupBox, g_sLangTxt_Gradient_Setting, XLang_Ctrls_QGroupBox);
    xlang_SetLangStrToWidget_Txt(ui->groupBox_2, g_sLangTxt_IEC_Details, XLang_Ctrls_QGroupBox);
    xlang_SetLangStrToWidget_Txt(ui->label, g_sLangTxt_Native_ValidBit, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_2, g_sLangTxt_Channel_Source, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_3, g_sLangTxt_Channel_Test, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_4, g_sLangTxt_IEC_Opb, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_5, g_sLangTxt_IEC_Overflow, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_6, g_sLangTxt_IEC_OutOfRange, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_7, g_sLangTxt_IEC_BadReference, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_8, g_sLangTxt_IEC_Oscillatory, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_9, g_sLangTxt_IEC_Failure, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_10, g_sLangTxt_IEC_OldData, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_11, g_sLangTxt_IEC_Inconsistent, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->label_12, g_sLangTxt_IEC_Inaccurate, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->checkBox, g_sLangTxt_Native_ModAllChan, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui->pbn_OK, g_sLangTxt_Native_Confm, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->pbn_Cancle, g_sLangTxt_Cancel, XLang_Ctrls_QPushButton);
}
void QSmvAbnormalQualitySet::initData()
{
	QString name = "cmb_bit";

	int iValue;
//	int iTemp = 0x03;
	iValue = m_listQualityParas[0];//iTemp&m_nQualityPara;

	ui->cmb_bit1->setCurrentIndex(iValue);
//	iTemp = 0x01;
//	iTemp = iTemp<<1;
	for (int i = 2; i <= 12; i++)
	{
//		iTemp = iTemp<<1;
//		iValue = iTemp&m_nQualityPara;
		iValue = m_listQualityParas[i-1];

		name = QString(tr("cmb_bit%1").arg(i));
		QComboBox *ckbox = NULL;
		if (i >= 10)
		{
			ckbox = ui->groupBox->findChild<QComboBox *>(name);
		}
		else
		{
			ckbox = ui->groupBox_2->findChild<QComboBox *>(name);
		}

		if (iValue == 0)
		{
			ckbox->setCurrentIndex(0);
		}
		else
		{
			ckbox->setCurrentIndex(1);
		}
	}

	ui->checkBox->setDisabled(true);
	ui->cmb_DispType->setCurrentIndex(2);

	slot_cmb_DispTypeStateChanged(2);
}

void QSmvAbnormalQualitySet::SetSmvAbnormalQualityFont()
{
	
	ui->label->setFont(*g_pSttGlobalFont);
	ui->cmb_bit1->setFont(*g_pSttGlobalFont);
	ui->label_2->setFont(*g_pSttGlobalFont);
	ui->cmb_bit10->setFont(*g_pSttGlobalFont);
	ui->label_3->setFont(*g_pSttGlobalFont);
	ui->cmb_bit11->setFont(*g_pSttGlobalFont);
	ui->label_4->setFont(*g_pSttGlobalFont);
	ui->cmb_bit12->setFont(*g_pSttGlobalFont);
	ui->label_5->setFont(*g_pSttGlobalFont);
	ui->cmb_bit2->setFont(*g_pSttGlobalFont);
	ui->label_6->setFont(*g_pSttGlobalFont);
	ui->cmb_bit3->setFont(*g_pSttGlobalFont);
	ui->label_7->setFont(*g_pSttGlobalFont);
	ui->cmb_bit4->setFont(*g_pSttGlobalFont);
	ui->label_8->setFont(*g_pSttGlobalFont);
	ui->cmb_bit5->setFont(*g_pSttGlobalFont);
	ui->label_9->setFont(*g_pSttGlobalFont);
	ui->cmb_bit6->setFont(*g_pSttGlobalFont);
	ui->label_10->setFont(*g_pSttGlobalFont);
	ui->label_11->setFont(*g_pSttGlobalFont);
	ui->cmb_bit7->setFont(*g_pSttGlobalFont);
	ui->cmb_bit8->setFont(*g_pSttGlobalFont);
	ui->cmb_bit9->setFont(*g_pSttGlobalFont);
	ui->label_12->setFont(*g_pSttGlobalFont);
	ui->cmb_DispType->setFont(*g_pSttGlobalFont);
	ui->lineEdit->setFont(*g_pSttGlobalFont);
	ui->pbn_OK->setFont(*g_pSttGlobalFont);
	ui->pbn_Cancle->setFont(*g_pSttGlobalFont);

	ui->groupBox->setFont(*g_pSttGlobalFont);
	ui->groupBox_2->setFont(*g_pSttGlobalFont);

}


int QSmvAbnormalQualitySet::GetValue()
{
	QString name = "cmb_bit";
	int iValue = ui->cmb_bit1->currentIndex();
	for (int i = 2;i<=12;i++)
	{
		name = QString(tr("cmb_bit%1").arg(i));
		QComboBox *ckbox = NULL;
		if (i >= 10)
		{
			ckbox = ui->groupBox->findChild<QComboBox *>(name);
		}
		else
		{
			ckbox = ui->groupBox_2->findChild<QComboBox *>(name);
		}
		int index = ckbox->currentIndex();
		index = index<<(i);
		iValue += index;
	}
	return iValue;
}

void QSmvAbnormalQualitySet::GetValues()
{
	QString name = "cmb_bit";
	m_listQualityParas[0] = ui->cmb_bit1->currentIndex();
	for (int i = 2;i<=12;i++)
	{
		name = QString(tr("cmb_bit%1").arg(i));
		QComboBox *ckbox = NULL;
		if (i >= 10)
		{
			ckbox = ui->groupBox->findChild<QComboBox *>(name);
		}
		else
		{
			ckbox = ui->groupBox_2->findChild<QComboBox *>(name);
		}
		m_listQualityParas[i-1] = ckbox->currentIndex();
	}
}

void QSmvAbnormalQualitySet::slot_pbn_OKClicked()
{
//	int nQualityPara = GetValue();
//	emit sig_QualityPara(nQualityPara);

	GetValues();
	emit sig_QualityPara(m_listQualityParas);

	close();
}

void QSmvAbnormalQualitySet::slot_pbn_CancelClicked()
{
	close();
}

void QSmvAbnormalQualitySet::slot_cmb_bit1StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit2StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit3StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit4StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit5StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit6StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit7StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit8StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit9StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit10StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit11StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_bit12StateChanged(int index)
{
	slot_cmb_DispTypeStateChanged(ui->cmb_DispType->currentIndex());
}

void QSmvAbnormalQualitySet::slot_cmb_DispTypeStateChanged(int index)
{
	QString str;
	if (index == 0)
	{
		int iValue = GetValue();
		str = QString("%1").arg(iValue,16,2,QChar('0'));
	}
	else if (index == 1)
	{
		int iValue = GetValue();
		str = QString::number(iValue);
	}
	else
	{
		int iValue = GetValue();
		str = QString("%1").arg(iValue,4,16,QChar('0'));
	}
	ui->lineEdit->setText(str.toUpper());
}

//void QSmvAbnormalQualitySet::slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor)
//{
//	QString str;
//	GetEngWidgetBoard_DigitData(str, this);
//	pEditLine->setText(str);
//	pEditLine->SetEditFinished();
//}

void QSmvAbnormalQualitySet::slot_lne_DispTypeKeyBoard()
{
	QString str = ui->lineEdit->text();
	GetEngWidgetBoard_DigitData(str,parentWidget());
	ui->lineEdit->setText(str);
	ui->lineEdit->SetEditFinished();

}