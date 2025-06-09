#include "QChMapsWidget.h"
#include <QDebug>
#include <QSpacerItem>
#include <QFileDialog>
#include <QMessageBox>
#include "../../../../Module/Engine/SttPowerTestEngineBase.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../CommonMethod/commonMethod.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../ScrollCtrl/ScrollComboBox.h"
//#include "../../SttTestCntrFrameBase.h"
#include "../../Controls/SttCheckBox.h"
#include "../../../Module/XLangResource_Native.h"

#pragma execution_character_set("utf-8")
QChMapsWidget::QChMapsWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pChMaps_GridLayout = NULL;
//	m_pOutputSel_GroupBox = NULL;
	m_pOutputSel_HBoxLayout = NULL;
	m_pDigitalType_Label = NULL;
	m_pAnalogSel_CheckBox = NULL;
	m_pDigitalSel_CheckBox = NULL;
	m_pWeakSel_CheckBox = NULL;
	m_pDigitalType_Label =NULL;
	m_pDigitalType_Combobox = NULL;
// 	m_pImportChMaps_PButton = NULL;
// 	m_pExportChMaps_PButton =NULL;
	m_pChMapsGrid = NULL;
//	m_pChMapsSet_GroupBox = NULL;
// 	m_pChMapsSet_HBoxLayout = NULL;
// 	m_pDefautMaps_PButton = NULL;
	m_pCurChMaps = NULL;
	m_pCurSysParas = NULL;
//	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

QChMapsWidget::~QChMapsWidget()
{

}
void QChMapsWidget::setChMapsFont()
{
	m_pDigitalType_Combobox->setFont(*g_pSttGlobalFont);
	m_pChMapsGrid->setFont(*g_pSttGlobalFont);
	m_pChMapsGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);

}

void QChMapsWidget::initUI(STT_SystemParas *pSysParas,CSttChMaps *pChMaps)
{
	ReleaseUI();

	m_pCurSysParas = pSysParas;
	m_pCurChMaps = pChMaps;
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);

//	m_pOutputSel_GroupBox = new QGroupBox(this);//第一行所有控件，放入该Group下
//	xlang_SetLangStrToWidget(m_pOutputSel_GroupBox, "ChMaps_OutputSel", XLang_Ctrls_QGroupBox);
	m_pOutputSel_HBoxLayout = new QHBoxLayout;//在Group内部增加表格布局，表格布局中包含第一行全部控件

	m_pAnalogSel_CheckBox = new QSttCheckBox/*(m_pOutputSel_GroupBox)*/;
	xlang_SetLangStrToWidget(m_pAnalogSel_CheckBox, "ChMaps_Analog", XLang_Ctrls_QCheckBox);
	m_pOutputSel_HBoxLayout->addWidget(m_pAnalogSel_CheckBox);

	m_pOutputSel_HBoxLayout->addSpacing(20);

	m_pDigitalSel_CheckBox = new QSttCheckBox/*(m_pOutputSel_GroupBox)*/;
	xlang_SetLangStrToWidget(m_pDigitalSel_CheckBox, "ChMaps_Digital", XLang_Ctrls_QCheckBox);
	m_pOutputSel_HBoxLayout->addWidget(m_pDigitalSel_CheckBox);

	m_pOutputSel_HBoxLayout->addSpacing(20);

	m_pWeakSel_CheckBox = new QSttCheckBox/*(m_pOutputSel_GroupBox)*/;
	xlang_SetLangStrToWidget(m_pWeakSel_CheckBox, "ChMaps_Week", XLang_Ctrls_QCheckBox);
	m_pOutputSel_HBoxLayout->addWidget(m_pWeakSel_CheckBox);

	m_pOutputSel_HBoxLayout->addStretch();

	m_pDigitalType_Label = new QLabel/*(m_pOutputSel_GroupBox)*/;
	xlang_SetLangStrToWidget(m_pDigitalType_Label, "ChMaps_DigitalType", XLang_Ctrls_QLabel);
	m_pOutputSel_HBoxLayout->addWidget(m_pDigitalType_Label);

	m_pDigitalType_Combobox = new QScrollComboBox(this);
//	m_pDigitalType_Combobox->setObjectName(QString::fromUtf8("comboBoxIset"));
	sizePolicy.setHeightForWidth(m_pDigitalType_Combobox->sizePolicy().hasHeightForWidth());
	m_pDigitalType_Combobox->setSizePolicy(sizePolicy);
	m_pDigitalType_Combobox->insertItem(0,tr("IEC61850-9-2"));
	m_pDigitalType_Combobox->insertItem(1,tr("IEC60044-8(FT3)"));

	if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
	{
		//m_pDigitalType_Combobox->insertItem(2,tr("柔直(FT3)"));
        m_pDigitalType_Combobox->insertItem(2,g_sLangTxt_State_FThreeStraight); //柔直(FT3) lcq 3.14
	}
	else
	{
		m_pDigitalType_Combobox->insertItem(2,tr("VSC-HVDC(FT3)"));
	}
// 	m_pDigitalType_Combobox->insertItem(3,tr("采集器输出(国网)"));
// 	m_pDigitalType_Combobox->insertItem(4,tr("采集器输出(许继)"));
	m_pOutputSel_HBoxLayout->addWidget(m_pDigitalType_Combobox);

// 	m_pChMapsSet_GroupBox = new QGroupBox(this);
// 	xlang_SetLangStrToWidget(m_pChMapsSet_GroupBox, "ChMaps_Title", XLang_Ctrls_QGroupBox);
// 	m_pChMapsSet_HBoxLayout = new QHBoxLayout(m_pChMapsSet_GroupBox);

	m_pChMaps_GridLayout = new QGridLayout(this);//整个通道映射的布局控件
	m_pChMaps_GridLayout->addLayout(m_pOutputSel_HBoxLayout,0,0,1,1);

//	m_pChMaps_GridLayout->addWidget(m_pChMapsSet_GroupBox,1,0,1,1);

	m_pChMapsGrid = new CChMapsGrid(this);
	m_pChMapsGrid->InitGrid();
	m_pChMaps_GridLayout->addWidget(m_pChMapsGrid,1,0,1,1);

//	m_pOutputSel_GroupBox->raise();
	InitDatas();
	m_pChMapsGrid->ShowDatas(pChMaps);
	
	connect(m_pDigitalType_Combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeDigitalType(int)));

	setChMapsFont();
}

//将系统参数部分的控件，设置为disable状态
void QChMapsWidget::DisableCtrls_SysCfg()  
{
	if (m_pAnalogSel_CheckBox != NULL)
	{
		m_pAnalogSel_CheckBox->setDisabled(true);
	}

	if (m_pDigitalSel_CheckBox != NULL)
	{
		m_pDigitalSel_CheckBox->setDisabled(true);
	}

	if (m_pWeakSel_CheckBox != NULL)
	{
		m_pWeakSel_CheckBox->setDisabled(true);
	}

	if (m_pDigitalType_Combobox != NULL)
	{
		m_pDigitalType_Combobox->setDisabled(true);
	}
}

void QChMapsWidget::InitDatas()
{
	ASSERT(m_pCurSysParas);

	if (m_pCurSysParas->m_nHasAnalog)
	{
		m_pAnalogSel_CheckBox->setCheckState(Qt::Checked);
	} 
	else
	{
		m_pAnalogSel_CheckBox->setCheckState(Qt::Unchecked);
	}

	if (m_pCurSysParas->m_nHasDigital)
	{
		m_pDigitalSel_CheckBox->setCheckState(Qt::Checked);
	} 
	else
	{
		m_pDigitalSel_CheckBox->setCheckState(Qt::Unchecked);
	}

	if (m_pCurSysParas->m_nHasWeek)
	{
		m_pWeakSel_CheckBox->setCheckState(Qt::Checked);
	} 
	else
	{
		m_pWeakSel_CheckBox->setCheckState(Qt::Unchecked);
	}

	if (g_oLocalSysPara.m_nSupportAnalogOutput == 0)
	{
		m_pAnalogSel_CheckBox->setDisabled(true);
	}

	if (g_oLocalSysPara.m_nSupportDigitalOutput == 0)
	{
		m_pDigitalSel_CheckBox->setDisabled(true);
		m_pDigitalType_Combobox->setDisabled(true);
	}

	if (g_oLocalSysPara.m_nSupportWeakOutput == 0)
	{
		m_pWeakSel_CheckBox->setDisabled(true);
	}

	m_pDigitalType_Combobox->setCurrentIndex(m_pCurSysParas->m_nIecFormat);
}

void QChMapsWidget::SaveDatas()
{
	if (m_pAnalogSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pCurSysParas->m_nHasAnalog = 1;
	}
	else
	{
		m_pCurSysParas->m_nHasAnalog = 0;
	}

	if (m_pDigitalSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pCurSysParas->m_nHasDigital = 1;
	}
	else
	{
		m_pCurSysParas->m_nHasDigital = 0;
	}

	if (m_pWeakSel_CheckBox->checkState() == Qt::Checked)
	{
		m_pCurSysParas->m_nHasWeek = 1;
	}
	else
	{
		m_pCurSysParas->m_nHasWeek = 0;
	}

	m_pCurSysParas->m_nIecFormat = m_pDigitalType_Combobox->currentIndex();
}

void QChMapsWidget::slot_changeDigitalType(int nIndex)
{
	m_pCurSysParas->m_nIecFormat = nIndex;

	if (m_pDigitalSel_CheckBox->checkState() != Qt::Checked)
	{
		return;
	}

	if (!g_oSttTestResourceMngr.HasLoadDevice())
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("缺少硬件资源文件,无法创建缺省通道映射."))
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_MissingDefaultMappings.GetString()); //缺少硬件资源文件,无法创建缺省通道映射 lcq 3.14 
		return;
	}

	g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(m_pCurChMaps,m_pCurSysParas->m_nIecFormat,TRUE);
	m_pChMapsGrid->ShowDatas(m_pCurChMaps);
}

void QChMapsWidget::ReleaseUI()
{
// 	if (m_pOutputSel_GroupBox != NULL)
// 	{
// 		delete m_pOutputSel_GroupBox;
// 		m_pOutputSel_GroupBox = NULL;
// 	}

	if (m_pOutputSel_HBoxLayout != NULL)
	{
		delete m_pOutputSel_HBoxLayout;
		m_pOutputSel_HBoxLayout = NULL;
	}

	if (m_pDigitalType_Label != NULL)
	{
		delete m_pDigitalType_Label;
		m_pDigitalType_Label = NULL;
	}

	if (m_pAnalogSel_CheckBox != NULL)
	{
		delete m_pAnalogSel_CheckBox;
		m_pAnalogSel_CheckBox = NULL;
	}

	if (m_pDigitalSel_CheckBox != NULL)
	{
		delete m_pDigitalSel_CheckBox;
		m_pDigitalSel_CheckBox = NULL;
	}

	if (m_pWeakSel_CheckBox != NULL)
	{
		delete m_pWeakSel_CheckBox;
		m_pWeakSel_CheckBox = NULL;
	}

	if (m_pDigitalType_Label != NULL)
	{
		delete m_pDigitalType_Label;
		m_pDigitalType_Label = NULL;
	}

	if (m_pDigitalType_Combobox != NULL)
	{
		delete m_pDigitalType_Combobox;
		m_pDigitalType_Combobox = NULL;
	}

// 	if (m_pImportChMaps_PButton != NULL)
// 	{
// 		delete m_pImportChMaps_PButton;
// 		m_pImportChMaps_PButton = NULL;
// 	}
// 
// 	if (m_pExportChMaps_PButton != NULL)
// 	{
// 		delete m_pExportChMaps_PButton;
// 		m_pExportChMaps_PButton = NULL;
// 	}

	if (m_pChMapsGrid != NULL)
	{
		delete m_pChMapsGrid;
		m_pChMapsGrid = NULL;
	}

	if (m_pChMaps_GridLayout != NULL)
	{
		delete m_pChMaps_GridLayout;
		m_pChMaps_GridLayout = NULL;
	}
}

