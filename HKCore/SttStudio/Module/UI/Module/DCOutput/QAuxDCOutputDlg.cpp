#include "QAuxDCOutputDlg.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include <QDirIterator>
#include "../../../SttSystemConfig/SttSystemConfig.h"
#include "../../../../Module/XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/ScrollCtrl/ScrollSlider.h"
extern QFont *g_pSttGlobalFont;

QAuxDCOutputDlg::QAuxDCOutputDlg(QWidget *parent)
	: QDialog(parent)
{
	//setWindowIcon (QPixmap( ":/images/Sys.png"));
	//setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	CString strTitle;
	//strTitle = _T("����ֱ������");
	xlang_GetLangStrByFile(strTitle,"State_AuxiliaryDCSettings"); //LCQ
	setWindowTitle(strTitle);
	m_pDC_Value_Slider = NULL;
	m_nOldSliderValue = 1;
}

QAuxDCOutputDlg::~QAuxDCOutputDlg()
{

}

void QAuxDCOutputDlg::initUI()
{
	CString strTitle;
	//ReleaseUI();//����ע��
	resize(240, 300);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(30);
	sizePolicy.setVerticalStretch(30);

	m_pAllVLayout = new QVBoxLayout(this);
	m_pDC_Value_Slider = new /*QSlider*/ScrollSlider(this);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pBegin_HBoxLayout = new QHBoxLayout(this);
	m_pAllVLayout->addLayout(m_pBegin_HBoxLayout);
	m_pBegin_HBoxLayout->addStretch();

	m_pScale_VBoxLayout = new QVBoxLayout(this);

	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	if(pCurDevice->m_strModel.Find(_T("PTU200L")) >= 0 || pCurDevice->m_strModel.Find(_T("PTU100A")) >= 0) 
	{
		QLabel *pScale48V_Label = new QLabel(this);
		pScale48V_Label->setFont(*g_pSttGlobalFont);
		pScale48V_Label->setText(tr("48V"));
		m_pScale_VBoxLayout->addWidget(pScale48V_Label);

		QLabel *pScale24V_Label = new QLabel(this);
		pScale24V_Label->setText(tr("24V"));
		pScale24V_Label->setFont(*g_pSttGlobalFont);
		m_pScale_VBoxLayout->addWidget(pScale24V_Label);
		m_pDC_Value_Slider->setMaximum(4);
	}
	else
	{
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

		m_pScale300V_Label->setFont(*g_pSttGlobalFont);
		m_pScale250V_Label->setFont(*g_pSttGlobalFont);
		m_pScale220V_Label->setFont(*g_pSttGlobalFont);
		m_pScale110V_Label->setFont(*g_pSttGlobalFont);

		m_pDC_Value_Slider->setMaximum(6);  // ���ֵ
	}


	/*m_pScale48V_Label = new QLabel(this);
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
	m_pScale_VBoxLayout->addWidget(m_pScale5V_Label);*/

	//strTitle = _T("����");
	xlang_GetLangStrByFile(strTitle,"State_Others");//LCQ
	m_pScaleOther_Label = new QLabel(this);
	m_pScaleOther_Label->setText(strTitle);
	m_pScale_VBoxLayout->addWidget(m_pScaleOther_Label);

	//strTitle = _T("�ر�");
	xlang_GetLangStrByFile(strTitle,"sClose");
	m_pScaleClosed_Label = new QLabel(this);
	m_pScaleClosed_Label->setText(strTitle);
	m_pScale_VBoxLayout->addWidget(m_pScaleClosed_Label);


	m_pBegin_HBoxLayout->addLayout(m_pScale_VBoxLayout);


	 m_pDC_Value_Slider->setOrientation(Qt::Vertical);  // ��ֱ����
	 m_pDC_Value_Slider->setMinimum(1);  // ��Сֵ
	 m_pDC_Value_Slider->setSingleStep(1);  // ����
	 m_pDC_Value_Slider->setTickInterval(1);
	m_pDC_Value_Slider->setMinimumSize(50, 100);
	m_pDC_Value_Slider->setTickPosition(ScrollSlider::TicksLeft);
	
	m_pBegin_HBoxLayout->addWidget(m_pDC_Value_Slider);
	m_pBegin_HBoxLayout->addStretch();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pAuxDC_GroupBox = new QGroupBox(this);
	m_pAllVLayout->addWidget(m_pAuxDC_GroupBox);
	m_pAuxDC_GroupBox->setTitle(tr(""));
	m_pAuxDC_Vol_HBoxLayout = new QHBoxLayout(m_pAuxDC_GroupBox);

	//strTitle = _T("��ѹֵ(V):");
	xlang_GetLangStrByFile(strTitle,"State_Voltagevalue");
	m_pAuxDC_Vol_Label = new QLabel(m_pAuxDC_GroupBox);
	m_pAuxDC_Vol_Label->setText(strTitle);
	m_pAuxDC_Vol_HBoxLayout->setSpacing(10);//�����м��
	m_pAuxDC_Vol_HBoxLayout->addWidget(m_pAuxDC_Vol_Label);

	m_pAuxDC_Vol_LineEdit = new QFloatLineEdit(m_pAuxDC_GroupBox);
	m_pAuxDC_Vol_HBoxLayout->addWidget(m_pAuxDC_Vol_LineEdit);

	if(pCurDevice->m_strModel.Find(_T("PTU200L")) >= 0 || pCurDevice->m_strModel.Find(_T("PTU100A")) >= 0) 
	{
		m_pAuxDC_Vol_LineEdit->InitCoverage_EditFinished(0,60,2);
	}
	else
	{
	m_pAuxDC_Vol_LineEdit->InitCoverage_EditFinished(110,300,2);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//strTitle = _T("ȷ��");
        xlang_GetLangStrByFile(strTitle,"sOK");//LCQ
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(strTitle);
	CString strImagesPath = _P_GetResourcePath();
#ifdef _PSX_QT_WINDOWS_
	m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));
#else
    //m_pOK_PushButton->setIcon (QPixmap( ":/ctrls/images/Check.png"));
	m_pOK_PushButton->setIcon(QPixmap(strImagesPath + "images/Check.png"));

#endif
	//strTitle = _T("ȡ��");
	xlang_GetLangStrByFile(strTitle,"sCancel");//LCQ
	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(strTitle);
#ifdef _PSX_QT_WINDOWS_
	m_pCancel_PushButton->setIcon (QPixmap( "./images/Cancel.png"));
#else
	m_pCancel_PushButton->setIcon (QPixmap( ":/ctrls/images/Cancel.png"));
#endif
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

	setDCOutPutFont();
}

void QAuxDCOutputDlg::setDCOutPutFont()
{
	m_pAuxDC_Vol_Label->setFont(*g_pSttGlobalFont);
	m_pAuxDC_Vol_LineEdit->setFont(*g_pSttGlobalFont);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
// 	m_pScale300V_Label->setFont(*g_pSttGlobalFont);
// 	m_pScale250V_Label->setFont(*g_pSttGlobalFont);
// 	m_pScale220V_Label->setFont(*g_pSttGlobalFont);
// 	m_pScale110V_Label->setFont(*g_pSttGlobalFont);
	/*m_pScale48V_Label->setFont(*g_pSttGlobalFont);
	m_pScale24V_Label->setFont(*g_pSttGlobalFont);
	m_pScale15V_Label->setFont(*g_pSttGlobalFont);
	m_pScale10V_Label->setFont(*g_pSttGlobalFont);
	m_pScale5V_Label->setFont(*g_pSttGlobalFont);*/
	m_pScaleOther_Label->setFont(*g_pSttGlobalFont);
	m_pScaleClosed_Label->setFont(*g_pSttGlobalFont);
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

	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	if(pCurDevice->m_strModel.Find(_T("PTU200L")) >= 0 || pCurDevice->m_strModel.Find(_T("PTU100A")) >= 0) 
	{
		if (nValue == 0)
		{
			m_pDC_Value_Slider->setValue(1);
			return 1;
		}
		else if (nValue == 24)
		{
			m_pDC_Value_Slider->setValue(3);
			return 3;
		}
		else if (nValue == 48)
		{
			m_pDC_Value_Slider->setValue(4);
			return 4;
		}
		else
		{
			m_pDC_Value_Slider->setValue(2);
			m_pAuxDC_Vol_LineEdit->setEnabled(true);
			return 2;
		}
	}
	else
	{
	if (nValue == 0)
	{
		m_pDC_Value_Slider->setValue(1);
		return 1;
	}
	else if (nValue == 110)
	{
		m_pDC_Value_Slider->setValue(3);
		return 3;
	}
	else if (nValue == 220)
	{
		m_pDC_Value_Slider->setValue(4);
		return 4;
	}
	else if (nValue == 250)
	{
		m_pDC_Value_Slider->setValue(5);
		return 5;
	}
	else if (nValue == 300)
	{
		m_pDC_Value_Slider->setValue(6);
		return 6;
	}
	else
	{
		m_pDC_Value_Slider->setValue(2);
		m_pAuxDC_Vol_LineEdit->setEnabled(true);
		return 2;
	}
	}

}

void QAuxDCOutputDlg::SetUI_ToScaleValue(int nValue)
{
	//chenling 2024.8.21PTU200Lֻ��������λ24V��48V
	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	if(pCurDevice->m_strModel.Find(_T("PTU200L")) >= 0 || pCurDevice->m_strModel.Find(_T("PTU100A")) >= 0) 
	{
		if (nValue == 1)
		{
			g_oSystemParas.m_fAuxDC_Vol = 0.0;
		}
		else if (nValue == 2)
		{
			g_oSystemParas.m_fAuxDC_Vol = m_pAuxDC_Vol_LineEdit->GetValue();
		}
		else if (nValue == 3)
		{
			g_oSystemParas.m_fAuxDC_Vol = 24;
		}
		else if (nValue == 4)
		{
			g_oSystemParas.m_fAuxDC_Vol = 48;
		}
	}
	else
	{
	if (nValue == 1)
	{
		g_oSystemParas.m_fAuxDC_Vol = 0.0;
	}
	else if (nValue == 2)
	{
		g_oSystemParas.m_fAuxDC_Vol = m_pAuxDC_Vol_LineEdit->GetValue();
	}
	else if (nValue == 3)
	{
		g_oSystemParas.m_fAuxDC_Vol = 110;
	}
	else if (nValue == 4)
	{
		g_oSystemParas.m_fAuxDC_Vol = 220;
	}
	else if (nValue == 5)
	{
		g_oSystemParas.m_fAuxDC_Vol = 250;
	}
	else if (nValue == 6)
	{
		g_oSystemParas.m_fAuxDC_Vol = 300;
	}
	}
}

void QAuxDCOutputDlg::slot_OKClicked()
{
	SetUI_ToScaleValue(m_nOldSliderValue);
	//g_oSystemParas.m_fAuxDC_Vol = m_pAuxDC_Vol_LineEdit->GetValue();
	g_oSttTestResourceMngr.SaveSystemParasFile();
	this->accept();
//	emit sig_UpdateAuxDCOutput();
}

void QAuxDCOutputDlg::slot_CancelClicked()
{
	close();
}

void QAuxDCOutputDlg::slot_ScaleSetValue(int nValue)
{
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


#include "../../../../../Module/OSInterface/QT/XMessageBox.h"
QAuxDCOutputDlg_L336EXi::QAuxDCOutputDlg_L336EXi(QWidget *parent)
: QDialog(parent)
	{
	//setWindowIcon (QPixmap( ":/images/Sys.png"));
	//setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	CString strTitle;
	//strTitle = _T("����ֱ������");
	xlang_GetLangStrByFile(strTitle,"State_AuxiliaryDCSettings"); //LCQ
	setWindowTitle(strTitle);
	m_pDC_Value_Slider = NULL;
	m_nOldSliderValue = 1;
	}

QAuxDCOutputDlg_L336EXi::~QAuxDCOutputDlg_L336EXi()
	{

	}

void QAuxDCOutputDlg_L336EXi::initUI()
	{
	CString strTitle;
	ReleaseUI();
	resize(280, 300);
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

	m_pScale264V_Label = new QLabel(this);
	m_pScale264V_Label->setText(tr("264V"));
	m_pScale_VBoxLayout->addWidget(m_pScale264V_Label);

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

// 	m_pScale24V_Label = new QLabel(this);
// 	m_pScale24V_Label->setText(tr("24V"));
// 	m_pScale_VBoxLayout->addWidget(m_pScale24V_Label);//20241107 suyang ��������Ҫ��ע�� 48-264V
// 
// 	m_pScale15V_Label = new QLabel(this);
// 	m_pScale15V_Label->setText(tr("15V"));
// 	m_pScale_VBoxLayout->addWidget(m_pScale15V_Label);

	//strTitle = _T("����");
	xlang_GetLangStrByFile(strTitle,"State_Others");//LCQ
	m_pScaleOther_Label = new QLabel(this);
	m_pScaleOther_Label->setText(strTitle);
	m_pScale_VBoxLayout->addWidget(m_pScaleOther_Label);

	//strTitle = _T("�ر�");
	xlang_GetLangStrByFile(strTitle,"sClose");
	m_pScaleClosed_Label = new QLabel(this);
	m_pScaleClosed_Label->setText(strTitle);
	m_pScale_VBoxLayout->addWidget(m_pScaleClosed_Label);


	m_pBegin_HBoxLayout->addLayout(m_pScale_VBoxLayout);


	m_pDC_Value_Slider = new /*QSlider*/ScrollSlider(this);
	m_pDC_Value_Slider->setOrientation(Qt::Vertical);  // ��ֱ����

	m_pDC_Value_Slider->setMinimum(1);  // ��Сֵ
	m_pDC_Value_Slider->setMaximum(7);  // ���ֵ
	m_pDC_Value_Slider->setSingleStep(1);  // ����
	m_pDC_Value_Slider->setTickInterval(1);
	m_pDC_Value_Slider->setMinimumSize(50, 100);
	m_pDC_Value_Slider->setTickPosition(ScrollSlider::TicksLeft);

	m_pBegin_HBoxLayout->addWidget(m_pDC_Value_Slider);
	m_pBegin_HBoxLayout->addStretch();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pAuxDC_GroupBox = new QGroupBox(this);
	m_pAllVLayout->addWidget(m_pAuxDC_GroupBox);
	m_pAuxDC_GroupBox->setTitle(tr(""));
	m_pAuxDC_Vol_HBoxLayout = new QHBoxLayout(m_pAuxDC_GroupBox);

	//strTitle = _T("��ѹֵ(V):");
	xlang_GetLangStrByFile(strTitle,"State_Voltagevalue");
	m_pAuxDC_Vol_Label = new QLabel(m_pAuxDC_GroupBox);
	m_pAuxDC_Vol_Label->setText(strTitle);
	m_pAuxDC_Vol_HBoxLayout->setSpacing(10);//�����м��
	m_pAuxDC_Vol_HBoxLayout->addWidget(m_pAuxDC_Vol_Label);

	m_pAuxDC_Vol_LineEdit = new QFloatLineEdit(m_pAuxDC_GroupBox);
	m_pAuxDC_Vol_HBoxLayout->addWidget(m_pAuxDC_Vol_LineEdit);
//	m_pAuxDC_Vol_LineEdit->InitCoverage_EditFinished(/*12*/48,264,2);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//strTitle = _T("ȷ��");
	xlang_GetLangStrByFile(strTitle,"sOK");//LCQ
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(strTitle);
#ifdef _PSX_QT_WINDOWS_
	m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));
#else
	m_pOK_PushButton->setIcon (QPixmap( ":/ctrls/images/Check.png"));
#endif
	//strTitle = _T("ȡ��");
	xlang_GetLangStrByFile(strTitle,"sCancel");//LCQ
	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(strTitle);
#ifdef _PSX_QT_WINDOWS_
	m_pCancel_PushButton->setIcon (QPixmap( "./images/Cancel.png"));
#else
	m_pCancel_PushButton->setIcon (QPixmap( ":/ctrls/images/Cancel.png"));
#endif
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

	connect(m_pAuxDC_Vol_LineEdit, SIGNAL(editingFinished()), SLOT(slot_AuxDC_Vol_LineEdit()));

	setDCOutPutFont();
}

void QAuxDCOutputDlg_L336EXi::slot_AuxDC_Vol_LineEdit()
{
	QString str = m_pAuxDC_Vol_LineEdit->text();
	
	int nAuxDC_Vol = str.toInt();

	CString strMsgText;

	if (nAuxDC_Vol < 48)
	{
		strMsgText = /*"��Сֱ������Ϊ48V��ǿ������Ϊ48V"*/g_sLangTxt_State_MsgText48V.GetString();
		CXMessageBox::information(this,/* tr("��ʾ")*/g_sLangTxt_Message,strMsgText);
		m_pAuxDC_Vol_LineEdit->setText("48");
		m_nOldSliderValue = SetValueToScaleUI(48);
	}
	else if(nAuxDC_Vol > 264)
	{
		strMsgText = /*"���ֱ������Ϊ264V��ǿ������Ϊ264V"*/g_sLangTxt_State_MsgText264V.GetString();
		CXMessageBox::information(this,/* tr("��ʾ")*/g_sLangTxt_Message,strMsgText);
		m_pAuxDC_Vol_LineEdit->setText("264");
		m_nOldSliderValue = SetValueToScaleUI(264);
	}
	else
	{
		m_pAuxDC_Vol_LineEdit->setText(str);
		m_nOldSliderValue = SetValueToScaleUI(nAuxDC_Vol);
	}

	//SetUI_ToScaleValue(m_nOldSliderValue);
}

void QAuxDCOutputDlg_L336EXi::setDCOutPutFont()
	{
	m_pAuxDC_Vol_Label->setFont(*g_pSttGlobalFont);
	m_pAuxDC_Vol_LineEdit->setFont(*g_pSttGlobalFont);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	m_pScale264V_Label->setFont(*g_pSttGlobalFont);
	m_pScale250V_Label->setFont(*g_pSttGlobalFont);
	m_pScale220V_Label->setFont(*g_pSttGlobalFont);
	m_pScale110V_Label->setFont(*g_pSttGlobalFont);
	m_pScale48V_Label->setFont(*g_pSttGlobalFont);
// 	m_pScale24V_Label->setFont(*g_pSttGlobalFont);
// 	m_pScale15V_Label->setFont(*g_pSttGlobalFont);
	m_pScaleOther_Label->setFont(*g_pSttGlobalFont);
	m_pScaleClosed_Label->setFont(*g_pSttGlobalFont);
	}

void QAuxDCOutputDlg_L336EXi::ReleaseUI()
{
}

void QAuxDCOutputDlg_L336EXi::InitDatas()
{
	m_pAuxDC_Vol_LineEdit->SetValue(g_oSystemParas.m_fAuxDC_Vol);
	m_nOldSliderValue = SetValueToScaleUI(g_oSystemParas.m_fAuxDC_Vol);
}

int QAuxDCOutputDlg_L336EXi::SetValueToScaleUI(float fAuxDC_Vol)
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
		return 1;
	}
// 	else if (nValue == 15)
// 	{
// 		m_pDC_Value_Slider->setValue(3);
// 		return 3;
// 	}
// 	else if (nValue == 24)
// 	{
// 		m_pDC_Value_Slider->setValue(4);
// 		return 4;
// 	}
	else if (nValue == 48)
	{
		m_pDC_Value_Slider->setValue(3);
		return 3;
	}
	else if (nValue == 110)
	{
		m_pDC_Value_Slider->setValue(4);
		return 4;
	}
	else if (nValue == 220)
	{
		m_pDC_Value_Slider->setValue(5);
		return 5;
	}
	else if (nValue == 250)
	{
		m_pDC_Value_Slider->setValue(6);
		return 6;
	}
	else if (nValue == 264)
	{
		m_pDC_Value_Slider->setValue(7);
		return 7;
	}
	else
	{
		m_pDC_Value_Slider->setValue(2);
		m_pAuxDC_Vol_LineEdit->setEnabled(true);
		return 2;
	}
}

void QAuxDCOutputDlg_L336EXi::SetUI_ToScaleValue(int nValue)
{
	if (nValue == 1)
	{
		g_oSystemParas.m_fAuxDC_Vol = 0.0;
	}
	else if (nValue == 2)
	{
		g_oSystemParas.m_fAuxDC_Vol = m_pAuxDC_Vol_LineEdit->GetValue();
	}
// 	else if (nValue == 3)
// 	{
// 		g_oSystemParas.m_fAuxDC_Vol = 15;
// 	}
// 	else if (nValue == 4)
// 	{
// 		g_oSystemParas.m_fAuxDC_Vol = 24;
// 	}
	else if (nValue == 3)
	{
		g_oSystemParas.m_fAuxDC_Vol = 48;
	}
	else if (nValue == 4)
	{
		g_oSystemParas.m_fAuxDC_Vol = 110;
	}
	else if (nValue == 5)
	{
		g_oSystemParas.m_fAuxDC_Vol = 220;
	}
	else if (nValue == 6)
	{
		g_oSystemParas.m_fAuxDC_Vol = 250;
	}
	else if (nValue == 7)
	{
		g_oSystemParas.m_fAuxDC_Vol = 264;
	}
}
void QAuxDCOutputDlg_L336EXi::slot_OKClicked()
{
	SetUI_ToScaleValue(m_nOldSliderValue);
	//g_oSystemParas.m_fAuxDC_Vol = m_pAuxDC_Vol_LineEdit->GetValue();
	g_oSttTestResourceMngr.SaveSystemParasFile();
	this->accept();
//	emit sig_UpdateAuxDCOutput();
}

void QAuxDCOutputDlg_L336EXi::slot_CancelClicked()
{
	close();
}

void QAuxDCOutputDlg_L336EXi::slot_ScaleSetValue(int nValue)
{
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