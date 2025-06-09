#include "FT3OutSetDialog.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../XLangResource_Native.h"


QFT3OutSetDialog::QFT3OutSetDialog(long dwValue,QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_dwValue=dwValue;
	InitUI();
}

QFT3OutSetDialog::~QFT3OutSetDialog()
{

}


void QFT3OutSetDialog::InitUI()
{
	resize(440,440);
	this->setFixedWidth(440);
	this->setFixedHeight(440);

	CString strTemp	=/*_T("FT3发布参数设置")*/g_sLangTxt_IEC_FT3PublishParameterSet; //lcq
	setWindowTitle(strTemp);

	CString strText;
	strText	= /*_T("确定")*/g_sLangTxt_OK; //lcq
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(strText);
	m_pOK_PushButton->setGeometry(QRect(90, 380, 111, 31));

	strText = /*_T("取消")*/g_sLangTxt_Cancel; //lcq
	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(strText);
	m_pCancel_PushButton->setGeometry(QRect(225, 380, 111, 31));

	horizontalLayout_Btn = new QHBoxLayout();
	horizontalLayout_Btn->addWidget(m_pOK_PushButton);
	horizontalLayout_Btn->addWidget(m_pCancel_PushButton);

	m_pLeftWidget = new QWidget(this);
	m_pLeftWidget->setGeometry(QRect(50, 10, 151, 371));

	verticalLayout_Left = new QVBoxLayout(m_pLeftWidget);

	verticalLayout_Left->setContentsMargins(0, 0, 0, 0);
	horizontalLayout_Bit0 = new QHBoxLayout();

	strText = _T("Bit[0]");
	m_pBit0_label = new QLabel(m_pLeftWidget);
	m_pBit0_label->setText(strText);

	horizontalLayout_Bit0->addWidget(m_pBit0_label);

	m_pBit0_comboBox = new QComboBox(m_pLeftWidget);
	m_pBit0_comboBox->addItem(CString("FALSE"));
	m_pBit0_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit0->addWidget(m_pBit0_comboBox);

	verticalLayout_Left->addLayout(horizontalLayout_Bit0);

	horizontalLayout_Bit1 = new QHBoxLayout();

	strText = _T("Bit[1]");
	m_pBit1_label = new QLabel(m_pLeftWidget);
	m_pBit1_label->setText(strText);

	horizontalLayout_Bit1->addWidget(m_pBit1_label);

	m_pBit1_comboBox = new QComboBox(m_pLeftWidget);
	m_pBit1_comboBox->addItem(CString("FALSE"));
	m_pBit1_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit1->addWidget(m_pBit1_comboBox);


	verticalLayout_Left->addLayout(horizontalLayout_Bit1);
	horizontalLayout_Bit2 = new QHBoxLayout();

	strText = _T("Bit[2]");
	m_pBit2_label = new QLabel(m_pLeftWidget);
	m_pBit2_label->setText(strText);
	horizontalLayout_Bit2->addWidget(m_pBit2_label);

	m_pBit2_comboBox = new QComboBox(m_pLeftWidget);
	m_pBit2_comboBox->addItem(CString("FALSE"));
	m_pBit2_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit2->addWidget(m_pBit2_comboBox);

	verticalLayout_Left->addLayout(horizontalLayout_Bit2);

	strText = _T("Bit[3]");
	horizontalLayout_Bit3 = new QHBoxLayout();
	m_pBit3_label = new QLabel(m_pLeftWidget);
	m_pBit3_label->setText(strText);

	horizontalLayout_Bit3->addWidget(m_pBit3_label);

	m_pBit3_comboBox = new QComboBox(m_pLeftWidget);
	m_pBit3_comboBox->addItem(CString("FALSE"));
	m_pBit3_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit3->addWidget(m_pBit3_comboBox);

	verticalLayout_Left->addLayout(horizontalLayout_Bit3);

	horizontalLayout_Bit4 = new QHBoxLayout();
	strText = _T("Bit[4]");
	m_pBit4_label = new QLabel(m_pLeftWidget);
	m_pBit4_label->setText(strText);

	horizontalLayout_Bit4->addWidget(m_pBit4_label);

	m_pBit4_comboBox = new QComboBox(m_pLeftWidget);
	m_pBit4_comboBox->addItem(CString("FALSE"));
	m_pBit4_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit4->addWidget(m_pBit4_comboBox);

	verticalLayout_Left->addLayout(horizontalLayout_Bit4);

	horizontalLayout_Bit5 = new QHBoxLayout();
	strText = _T("Bit[5]");
	m_pBit5_label = new QLabel(m_pLeftWidget);
	m_pBit5_label->setText(strText);
	horizontalLayout_Bit5->addWidget(m_pBit5_label);

	m_pBit5_comboBox = new QComboBox(m_pLeftWidget);
	m_pBit5_comboBox->addItem(CString("FALSE"));
	m_pBit5_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit5->addWidget(m_pBit5_comboBox);

	verticalLayout_Left->addLayout(horizontalLayout_Bit5);

	horizontalLayout_Bit6 = new QHBoxLayout();
	strText = _T("Bit[6]");
	m_pBit6_label = new QLabel(m_pLeftWidget);
	m_pBit6_label->setText(strText);
	horizontalLayout_Bit6->addWidget(m_pBit6_label);

	m_pBit6_comboBox = new QComboBox(m_pLeftWidget);
	m_pBit6_comboBox->addItem(CString("FALSE"));
	m_pBit6_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit6->addWidget(m_pBit6_comboBox);

	verticalLayout_Left->addLayout(horizontalLayout_Bit6);

	horizontalLayout_Bit7 = new QHBoxLayout();
	strText = _T("Bit[7]");
	m_pBit7_label = new QLabel(m_pLeftWidget);
	m_pBit7_label->setText(strText);
	horizontalLayout_Bit7->addWidget(m_pBit7_label);

	m_pBit7_comboBox = new QComboBox(m_pLeftWidget);
	m_pBit7_comboBox->addItem(CString("FALSE"));
	m_pBit7_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit7->addWidget(m_pBit7_comboBox);

	verticalLayout_Left->addLayout(horizontalLayout_Bit7);

	m_pRightWidget = new QWidget(this);
	m_pRightWidget->setGeometry(QRect(230, 10, 151, 371));
	verticalLayout_Right = new QVBoxLayout(m_pRightWidget);
	verticalLayout_Right->setContentsMargins(0, 0, 0, 0);
	horizontalLayout_Bit8 = new QHBoxLayout();
	strText = _T("Bit[8]");
	m_pBit8_label = new QLabel(m_pRightWidget);
	m_pBit8_label->setText(strText);
	horizontalLayout_Bit8->addWidget(m_pBit8_label);

	m_pBit8_comboBox = new QComboBox(m_pRightWidget);
	m_pBit8_comboBox->addItem(CString("FALSE"));
	m_pBit8_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit8->addWidget(m_pBit8_comboBox);

	verticalLayout_Right->addLayout(horizontalLayout_Bit8);

	horizontalLayout_Bit9 = new QHBoxLayout();
	strText = _T("Bit[9]");
	m_pBit9_label = new QLabel(m_pRightWidget);
	m_pBit9_label->setText(strText);
	horizontalLayout_Bit9->addWidget(m_pBit9_label);

	m_pBit9_comboBox = new QComboBox(m_pRightWidget);
	m_pBit9_comboBox->addItem(CString("FALSE"));
	m_pBit9_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit9->addWidget(m_pBit9_comboBox);

	verticalLayout_Right->addLayout(horizontalLayout_Bit9);

	horizontalLayout_Bit10 = new QHBoxLayout();
	strText = _T("Bit[10]");
	m_pBit10_label = new QLabel(m_pRightWidget);
	m_pBit10_label->setText(strText);
	horizontalLayout_Bit10->addWidget(m_pBit10_label);

	m_pBit10_comboBox = new QComboBox(m_pRightWidget);
	m_pBit10_comboBox->addItem(CString("FALSE"));
	m_pBit10_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit10->addWidget(m_pBit10_comboBox);

	verticalLayout_Right->addLayout(horizontalLayout_Bit10);

	horizontalLayout_Bit11 = new QHBoxLayout();
	strText = _T("Bit[11]");
	m_pBit11_label = new QLabel(m_pRightWidget);
	m_pBit11_label->setText(strText);
	horizontalLayout_Bit11->addWidget(m_pBit11_label);

	m_pBit11_comboBox = new QComboBox(m_pRightWidget);
	m_pBit11_comboBox->addItem(CString("FALSE"));
	m_pBit11_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit11->addWidget(m_pBit11_comboBox);

	verticalLayout_Right->addLayout(horizontalLayout_Bit11);

	horizontalLayout_Bit12 = new QHBoxLayout();
	strText = _T("Bit[12]");
	m_pBit12_label = new QLabel(m_pRightWidget);
	m_pBit12_label->setText(strText);
	horizontalLayout_Bit12->addWidget(m_pBit12_label);

	m_pBit12_comboBox = new QComboBox(m_pRightWidget);
	m_pBit12_comboBox->addItem(CString("FALSE"));
	m_pBit12_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit12->addWidget(m_pBit12_comboBox);

	verticalLayout_Right->addLayout(horizontalLayout_Bit12);

	horizontalLayout_Bit13 = new QHBoxLayout();

	strText = _T("Bit[13]");
	m_pBit13_label = new QLabel(m_pRightWidget);
	m_pBit13_label->setText(strText);
	horizontalLayout_Bit13->addWidget(m_pBit13_label);

	m_pBit13_comboBox = new QComboBox(m_pRightWidget);
	m_pBit13_comboBox->addItem(CString("FALSE"));
	m_pBit13_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit13->addWidget(m_pBit13_comboBox);

	verticalLayout_Right->addLayout(horizontalLayout_Bit13);

	horizontalLayout_Bit14 = new QHBoxLayout();
	strText = _T("Bit[14]");
	m_pBit14_label = new QLabel(m_pRightWidget);
	m_pBit14_label->setText(strText);
	horizontalLayout_Bit14->addWidget(m_pBit14_label);

	m_pBit14_comboBox = new QComboBox(m_pRightWidget);
	m_pBit14_comboBox->addItem(CString("FALSE"));
	m_pBit14_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit14->addWidget(m_pBit14_comboBox);

	verticalLayout_Right->addLayout(horizontalLayout_Bit14);

	horizontalLayout_Bit15 = new QHBoxLayout();
	strText = _T("Bit[15]");
	m_pBit15_label = new QLabel(m_pRightWidget);
	m_pBit15_label->setText(strText);
	horizontalLayout_Bit15->addWidget(m_pBit15_label);

	m_pBit15_comboBox = new QComboBox(m_pRightWidget);
	m_pBit15_comboBox->addItem(CString("FALSE"));
	m_pBit15_comboBox->addItem(CString("TRUE"));
	horizontalLayout_Bit15->addWidget(m_pBit15_comboBox);

	verticalLayout_Right->addLayout(horizontalLayout_Bit15);

	ShowData();
	SetInitValueFont();
	connect(m_pCancel_PushButton,SIGNAL(clicked()),this,SLOT(slot_CancelClicked()));
	connect(m_pOK_PushButton,SIGNAL(clicked()),this,SLOT(slot_OKClicked()));
}


void QFT3OutSetDialog::SetInitValueFont()
{
	m_pBit0_label->setFont(*g_pSttGlobalFont);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	m_pLeftWidget->setFont(*g_pSttGlobalFont);
	m_pBit0_label->setFont(*g_pSttGlobalFont);
	m_pBit0_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit1_label->setFont(*g_pSttGlobalFont);
	m_pBit1_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit2_label->setFont(*g_pSttGlobalFont);
	m_pBit2_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit3_label->setFont(*g_pSttGlobalFont);
	m_pBit3_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit4_label->setFont(*g_pSttGlobalFont);
	m_pBit4_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit5_label->setFont(*g_pSttGlobalFont);
	m_pBit5_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit6_label->setFont(*g_pSttGlobalFont);
	m_pBit6_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit7_label->setFont(*g_pSttGlobalFont);
	m_pBit7_comboBox->setFont(*g_pSttGlobalFont);
	m_pRightWidget->setFont(*g_pSttGlobalFont);
	m_pBit8_label->setFont(*g_pSttGlobalFont);
	m_pBit8_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit9_label->setFont(*g_pSttGlobalFont);
	m_pBit9_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit10_label->setFont(*g_pSttGlobalFont);
	m_pBit10_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit11_label->setFont(*g_pSttGlobalFont);
	m_pBit11_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit12_label->setFont(*g_pSttGlobalFont);
	m_pBit12_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit13_label->setFont(*g_pSttGlobalFont);
	m_pBit13_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit14_label->setFont(*g_pSttGlobalFont);
	m_pBit14_comboBox->setFont(*g_pSttGlobalFont);
	m_pBit15_label->setFont(*g_pSttGlobalFont);
	m_pBit15_comboBox->setFont(*g_pSttGlobalFont);
}


void QFT3OutSetDialog::ShowData()
{
	long nFlag;
	for(int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		nFlag=(m_dwValue>>nIndex)%2;
		p_BitValue[nIndex]=nFlag;
	}

	for(int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		if(p_BitValue[nIndex]==1)
		{
			m_BitData[nIndex]="TRUE";
		}
		else
		{
			m_BitData[nIndex]="FALSE";
		}
	}

	m_pBit0_comboBox->setCurrentIndex(p_BitValue[0]);
	m_pBit1_comboBox->setCurrentIndex(p_BitValue[1]);
	m_pBit2_comboBox->setCurrentIndex(p_BitValue[2]);
	m_pBit3_comboBox->setCurrentIndex(p_BitValue[3]);
	m_pBit4_comboBox->setCurrentIndex(p_BitValue[4]);
	m_pBit5_comboBox->setCurrentIndex(p_BitValue[5]);
	m_pBit6_comboBox->setCurrentIndex(p_BitValue[6]);
	m_pBit7_comboBox->setCurrentIndex(p_BitValue[7]);
	m_pBit8_comboBox->setCurrentIndex(p_BitValue[8]);
	m_pBit9_comboBox->setCurrentIndex(p_BitValue[9]);
	m_pBit10_comboBox->setCurrentIndex(p_BitValue[10]);
	m_pBit11_comboBox->setCurrentIndex(p_BitValue[11]);
	m_pBit12_comboBox->setCurrentIndex(p_BitValue[12]);
	m_pBit13_comboBox->setCurrentIndex(p_BitValue[13]);
	m_pBit14_comboBox->setCurrentIndex(p_BitValue[14]);
	m_pBit15_comboBox->setCurrentIndex(p_BitValue[15]);
}

void QFT3OutSetDialog::SaveData()
{
	m_BitData[0] = m_pBit0_comboBox->currentText();
	m_BitData[1] = m_pBit1_comboBox->currentText();
	m_BitData[2] = m_pBit2_comboBox->currentText();
	m_BitData[3] = m_pBit3_comboBox->currentText();
	m_BitData[4] = m_pBit4_comboBox->currentText();
	m_BitData[5] = m_pBit5_comboBox->currentText();
	m_BitData[6] = m_pBit6_comboBox->currentText();
	m_BitData[7] = m_pBit7_comboBox->currentText();
	m_BitData[8] = m_pBit8_comboBox->currentText();
	m_BitData[9] = m_pBit9_comboBox->currentText();
	m_BitData[10] = m_pBit10_comboBox->currentText();
	m_BitData[11] = m_pBit11_comboBox->currentText();
	m_BitData[12] = m_pBit12_comboBox->currentText();
	m_BitData[13] = m_pBit13_comboBox->currentText();
	m_BitData[14] = m_pBit14_comboBox->currentText();
	m_BitData[15] = m_pBit15_comboBox->currentText();

	m_dwValue = 0;

	for(int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		if(m_BitData[nIndex]=="TRUE")
		{
			p_BitValue[nIndex] = 1;
		}
		else
		{
			p_BitValue[nIndex] = 0;
		}

	}
	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		m_dwValue += p_BitValue[nIndex]<<nIndex;
	}
}

void QFT3OutSetDialog::slot_CancelClicked()
{
	close();
}

void QFT3OutSetDialog::slot_OKClicked()
{
	SaveData();
	this->accept();
}