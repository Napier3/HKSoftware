#include "QAuxDCOutputDlg.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include <QDirIterator>
#include "../../../../Module/SttSystemConfig/SttSystemConfig.h"
#include "../../CommonMethod/commonMethod.h"
#include "../ReportView/XLangResource_PowerTestWin.h"
//#include "../testwinbase.h"

QAuxDCOutputDlg::QAuxDCOutputDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowIcon (QPixmap( ":/images/Sys.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(/*tr("辅助直流设置")*/g_sLangTxt_State_AuxiliaryDCSettings);
	m_pDC_Value_Slider = NULL;
	m_nOldSliderValue = 1;
}

QAuxDCOutputDlg::~QAuxDCOutputDlg()
{

}

void QAuxDCOutputDlg::initUI()
{
	ReleaseUI();
	resize(240, 300);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(30);
	sizePolicy.setVerticalStretch(30);

	m_pAllVLayout = new QVBoxLayout(this);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pBegin_HBoxLayout = new QHBoxLayout(this);
	m_pAllVLayout->addLayout(m_pBegin_HBoxLayout);
	m_pBegin_HBoxLayout->addStretch();

	m_pScale_VBoxLayout = new QVBoxLayout(this);

	m_pScale300V_Label = new QLabel(this);
	m_pScale300V_Label->setText(tr("300V"));
	m_pScale_VBoxLayout->addWidget(m_pScale300V_Label);

	m_pScale250V_Label = new QLabel(this);
	m_pScale250V_Label->setText(tr("250V"));
	m_pScale_VBoxLayout->addWidget(m_pScale250V_Label);

	m_pScale220V_Label = new QLabel(this);
	m_pScale220V_Label->setText(tr("220V"));
	m_pScale_VBoxLayout->addWidget(m_pScale220V_Label);

	m_pScale110V_Label = new QLabel(this);
	m_pScale110V_Label->setText(tr("110V"));
	m_pScale_VBoxLayout->addWidget(m_pScale110V_Label);

	m_pScale48V_Label = new QLabel(this);
	m_pScale48V_Label->setText(tr("48V"));
	m_pScale_VBoxLayout->addWidget(m_pScale48V_Label);

	m_pScale24V_Label = new QLabel(this);
	m_pScale24V_Label->setText(tr("24V"));
	m_pScale_VBoxLayout->addWidget(m_pScale24V_Label);

	m_pScale15V_Label = new QLabel(this);
	m_pScale15V_Label->setText(tr("15V"));
	m_pScale_VBoxLayout->addWidget(m_pScale15V_Label);

	m_pScale10V_Label = new QLabel(this);
	m_pScale10V_Label->setText(tr("10V"));
	m_pScale_VBoxLayout->addWidget(m_pScale10V_Label);

	m_pScale5V_Label = new QLabel(this);
	m_pScale5V_Label->setText(tr("5V"));
	m_pScale_VBoxLayout->addWidget(m_pScale5V_Label);

	m_pScaleOther_Label = new QLabel(this);
	m_pScaleOther_Label->setText(/*tr("其它")*/g_sLangTxt_State_Others);
	m_pScale_VBoxLayout->addWidget(m_pScaleOther_Label);

	m_pScaleClosed_Label = new QLabel(this);
	m_pScaleClosed_Label->setText(/*tr("关闭")*/g_sLangTxt_Close);
	m_pScale_VBoxLayout->addWidget(m_pScaleClosed_Label);


	m_pBegin_HBoxLayout->addLayout(m_pScale_VBoxLayout);


	m_pDC_Value_Slider = new QSlider(this);
	 m_pDC_Value_Slider->setOrientation(Qt::Vertical);  // 垂直方向

	 m_pDC_Value_Slider->setMinimum(1);  // 最小值
	 m_pDC_Value_Slider->setMaximum(11);  // 最大值
	 m_pDC_Value_Slider->setSingleStep(1);  // 步长
	 m_pDC_Value_Slider->setTickInterval(1);
	 m_pDC_Value_Slider->setTickPosition(QSlider::TicksLeft);

	m_pBegin_HBoxLayout->addWidget(m_pDC_Value_Slider);
	m_pBegin_HBoxLayout->addStretch();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pAuxDC_GroupBox = new QGroupBox(this);
	m_pAllVLayout->addWidget(m_pAuxDC_GroupBox);
	m_pAuxDC_GroupBox->setTitle(tr(""));
	m_pAuxDC_Vol_HBoxLayout = new QHBoxLayout(m_pAuxDC_GroupBox);


	m_pAuxDC_Vol_Label = new QLabel(m_pAuxDC_GroupBox);
	m_pAuxDC_Vol_Label->setText(/*tr("电压值(V):")*/g_sLangTxt_State_Voltagevalue);
	m_pAuxDC_Vol_HBoxLayout->setSpacing(10);//设置行间距
	m_pAuxDC_Vol_HBoxLayout->addWidget(m_pAuxDC_Vol_Label);

	m_pAuxDC_Vol_LineEdit = new QFloatLineEdit(m_pAuxDC_GroupBox);
	m_pAuxDC_Vol_LineEdit->InitCoverage(0,300);
	m_pAuxDC_Vol_HBoxLayout->addWidget(m_pAuxDC_Vol_LineEdit);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(/*tr("确定")*/g_sLangTxt_OK);
	m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));

	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(/*tr("取消")*/g_sLangTxt_Cancel);
	m_pCancel_PushButton->setIcon (QPixmap( "./images/Cancel.png"));

	m_pEnd_HBoxLayout = new QHBoxLayout(this);
	m_pEnd_HBoxLayout->addStretch();
	m_pEnd_HBoxLayout->addWidget(m_pOK_PushButton);
	m_pEnd_HBoxLayout->addSpacing(10);
	m_pEnd_HBoxLayout->addWidget(m_pCancel_PushButton);
	m_pEnd_HBoxLayout->addStretch();
	m_pEnd_HBoxLayout->setDirection(QBoxLayout::LeftToRight);
	m_pAllVLayout->addLayout(m_pEnd_HBoxLayout);
	InitDatas();
	this->setLayout(m_pAllVLayout);

	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pDC_Value_Slider, SIGNAL(valueChanged(int)), this, SLOT(slot_ScaleSetValue(int)));
}

void QAuxDCOutputDlg::ReleaseUI()
{
}

void QAuxDCOutputDlg::InitDatas()
{
	m_pAuxDC_Vol_LineEdit->SetValue(g_oSystemParas.m_fAuxDC_Vol);
	m_nOldSliderValue = SetValueToScaleUI(g_oSystemParas.m_fAuxDC_Vol);
}

int QAuxDCOutputDlg::SetValueToScaleUI(float fAuxDC_Vol)
{
	long nValue = fAuxDC_Vol;

	if ((fAuxDC_Vol-nValue)>0.5)
	{
		nValue++;
	}

	m_pAuxDC_Vol_LineEdit->setEnabled(false);

	if (nValue == 0)
	{
		m_pDC_Value_Slider->setValue(1);
	}
	else if (nValue == 5)
	{
		m_pDC_Value_Slider->setValue(3);
	}
	else if (nValue == 10)
	{
		m_pDC_Value_Slider->setValue(4);
	}
	else if (nValue == 15)
	{
		m_pDC_Value_Slider->setValue(5);
	}
	else if (nValue == 24)
	{
		m_pDC_Value_Slider->setValue(6);
	}
	else if (nValue == 48)
	{
		m_pDC_Value_Slider->setValue(7);
	}
	else if (nValue == 110)
	{
		m_pDC_Value_Slider->setValue(8);
	}
	else if (nValue == 220)
	{
		m_pDC_Value_Slider->setValue(9);
	}
	else if (nValue == 250)
	{
		m_pDC_Value_Slider->setValue(10);
	}
	else if (nValue == 300)
	{
		m_pDC_Value_Slider->setValue(11);
	}
	else
	{
		m_pDC_Value_Slider->setValue(2);
		m_pAuxDC_Vol_LineEdit->setEnabled(true);
	}

	return nValue;
}

void QAuxDCOutputDlg::SetUI_ToScaleValue(int nValue)
{
	if (nValue == 1)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(0.0);
	}
	else if (nValue == 3)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(5);
	}
	else if (nValue == 4)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(10);
	}
	else if (nValue == 5)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(15);
	}
	else if (nValue == 6)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(24);
	}
	else if (nValue == 7)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(48);
	}
	else if (nValue == 8)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(110);
	}
	else if (nValue == 9)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(220);
	}
	else if (nValue == 10)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(250);
	}
	else if (nValue == 11)
	{
		m_pAuxDC_Vol_LineEdit->SetValue(300);
	}
// 	else
// 	{
// 		m_pAuxDC_Vol_LineEdit->SetValue(10);
// 	}
}

void QAuxDCOutputDlg::slot_OKClicked()
{
	g_oSystemParas.m_fAuxDC_Vol = m_pAuxDC_Vol_LineEdit->GetValue();
	g_oSttTestResourceMngr.SaveSystemParasFile();
	close();

	//g_TestWinBase->UpdateAuxDcEnabled();

	emit sig_UpdateAuxDCOutput();
}

void QAuxDCOutputDlg::slot_CancelClicked()
{
	close();
}

void QAuxDCOutputDlg::slot_ScaleSetValue(int nValue)
{
	SetUI_ToScaleValue(nValue);

	if ((m_nOldSliderValue == 2)&&(nValue != 2))
	{
		m_pAuxDC_Vol_LineEdit->setEnabled(false);
	}
	else if ((m_nOldSliderValue != 2)&&(nValue == 2))
	{
		m_pAuxDC_Vol_LineEdit->setEnabled(true);
	}

	m_nOldSliderValue = nValue;
}