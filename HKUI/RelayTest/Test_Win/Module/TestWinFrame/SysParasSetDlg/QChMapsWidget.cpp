#include "QChMapsWidget.h"
#include <QDebug>
#include <QSpacerItem>
#include <QFileDialog>
#include <QMessageBox>
#include "../../../../Module/Engine/SttPowerTestEngineBase.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../CommonMethod/commonMethod.h"
#include "../ReportView/XLangResource_PowerTestWin.h"


#pragma execution_character_set("utf-8")
QChMapsWidget::QChMapsWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pChMaps_GridLayout = NULL;
	m_pOutputSel_GroupBox = NULL;
	m_pOutputSel_HBoxLayout = NULL;
	m_pDigitalType_Label = NULL;
	m_pAnalogSel_CheckBox = NULL;
	m_pDigitalSel_CheckBox = NULL;
	m_pWeakSel_CheckBox = NULL;
	m_pDigitalType_Label =NULL;
	m_pDigitalType_Combobox = NULL;
	m_pChMapsGrid = NULL;
	m_pCurChMaps = NULL;
	m_pCurSysParas = NULL;
	m_pChMapsQuickWidget = NULL;
	m_pChMapsQuickSet_GroupBox = NULL;
}

QChMapsWidget::~QChMapsWidget()
{

}

void QChMapsWidget::initUI(STT_SystemParas *pSysParas,CSttChMaps *pChMaps)
{
	ReleaseUI();

	m_pCurSysParas = pSysParas;
	m_pCurChMaps = pChMaps;
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);

	m_pOutputSel_GroupBox = new QGroupBox(this);//第一行所有控件，放入该Group下
	m_pOutputSel_GroupBox->setTitle(/*tr("输出类型选择")*/g_sLangTxt_ChMaps_OutputSel);
	m_pOutputSel_HBoxLayout = new QHBoxLayout(m_pOutputSel_GroupBox);//在Group内部增加表格布局，表格布局中包含第一行全部控件

	m_pAnalogSel_CheckBox = new QCheckBox(m_pOutputSel_GroupBox);
	m_pAnalogSel_CheckBox->setText(/*tr("模拟")*/g_sLangTxt_ChMaps_Analog);
	m_pOutputSel_HBoxLayout->addWidget(m_pAnalogSel_CheckBox);

	m_pOutputSel_HBoxLayout->addSpacing(20);

	m_pDigitalSel_CheckBox = new QCheckBox(m_pOutputSel_GroupBox);
	m_pDigitalSel_CheckBox->setText(/*tr("数字")*/g_sLangTxt_ChMaps_Digital);
	m_pOutputSel_HBoxLayout->addWidget(m_pDigitalSel_CheckBox);

	m_pOutputSel_HBoxLayout->addSpacing(20);

	m_pWeakSel_CheckBox = new QCheckBox(m_pOutputSel_GroupBox);
	m_pWeakSel_CheckBox->setText(/*tr("弱信号")*/g_sLangTxt_ChMaps_Week);
	m_pOutputSel_HBoxLayout->addWidget(m_pWeakSel_CheckBox);

	m_pOutputSel_HBoxLayout->addStretch();

	m_pDigitalType_Label = new QLabel(m_pOutputSel_GroupBox);
	m_pDigitalType_Label->setText(/*tr("数字报文类型:")*/g_sLangTxt_ChMaps_DigitalType+":");
	m_pOutputSel_HBoxLayout->addWidget(m_pDigitalType_Label);

	m_pDigitalType_Combobox = new QComboBox(m_pOutputSel_GroupBox);
//	m_pDigitalType_Combobox->setObjectName(QString::fromUtf8("comboBoxIset"));
	sizePolicy.setHeightForWidth(m_pDigitalType_Combobox->sizePolicy().hasHeightForWidth());
	m_pDigitalType_Combobox->setSizePolicy(sizePolicy);
	m_pDigitalType_Combobox->insertItem(0,tr("IEC61850-9-2"));
	m_pDigitalType_Combobox->insertItem(1,tr("IEC60044-8(FT3)"));
	m_pDigitalType_Combobox->insertItem(2,/*tr("柔直(FT3)")*/g_sLangTxt_State_FThreeStraight);
// 	m_pDigitalType_Combobox->insertItem(3,tr("采集器输出(国网)"));
// 	m_pDigitalType_Combobox->insertItem(4,tr("采集器输出(许继)"));
	m_pOutputSel_HBoxLayout->addWidget(m_pDigitalType_Combobox);

	m_pChMaps_GridLayout = new QGridLayout(this);//整个通道映射的布局控件
	m_pChMaps_GridLayout->addWidget(m_pOutputSel_GroupBox,0,0,1,1);

	long nType = g_oSttTestResourceMngr.m_pTestResouce->GetTestRsType();
	if ((nType == STT_TEST_RESOURCE_TYPE_4U3I) || (nType == STT_TEST_RESOURCE_TYPE_6U6I))
	{
		m_pChMapsQuickSet_GroupBox = new QGroupBox(this);
		m_pChMapsQuickSet_GroupBox->setTitle("通道映射快捷设置");
		m_pChMapsQuickSet_GroupBox->setMaximumHeight(300);
		QVBoxLayout *pVBoxLayout = new QVBoxLayout(m_pChMapsQuickSet_GroupBox);

		m_pChMapsQuickWidget = new QChMapsQuickWidget(pChMaps, m_pChMapsQuickSet_GroupBox);
		pVBoxLayout->addWidget(m_pChMapsQuickWidget);
		m_pChMaps_GridLayout->addWidget(m_pChMapsQuickSet_GroupBox,1,0,1,1);

		m_pChMapsGrid = new CChMapsGrid(pChMaps,this);
	m_pChMapsGrid->InitGrid();
	m_pChMaps_GridLayout->addWidget(m_pChMapsGrid,2,0,1,1);
		InitConnection();
	}
	else
	{
		m_pChMapsGrid = new CChMapsGrid(pChMaps,this);
		m_pChMapsGrid->InitGrid();
		m_pChMaps_GridLayout->addWidget(m_pChMapsGrid,1,0,1,1);
	}
 	

	m_pOutputSel_GroupBox->raise();
	InitDatas();
	m_pChMapsGrid->ShowDatas(pChMaps);

	connect(m_pDigitalType_Combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeDigitalType(int)));
}

void QChMapsWidget::InitConnection()
{
	connect(m_pChMapsGrid, SIGNAL(sig_AnalogUEndEditCellHasChanged(	CSttChMaps*)), m_pChMapsQuickWidget->m_pVoltAnalogQuickGrid, SLOT(slot_UpdateAnalogUComboxState(CSttChMaps*)));
	connect(m_pChMapsGrid, SIGNAL(sig_AnalogIEndEditCellHasChanged(CSttChMaps*)), m_pChMapsQuickWidget->m_pCurAnalogQuickGrid, SLOT(slot_UpdateAnalogIComboxState(CSttChMaps*)));
	connect(m_pChMapsQuickWidget->m_pVoltAnalogQuickGrid, SIGNAL(sig_ChMapStateIsChanged(long,int,int,int,int,bool)), m_pChMapsGrid, SLOT(slot_UpdateDefaultMaps(long,int,int,int,int,bool)));
	connect(m_pChMapsQuickWidget->m_pCurAnalogQuickGrid, SIGNAL(sig_ChMapStateIsChanged(long,int,int,int,int,bool)), m_pChMapsGrid, SLOT(slot_UpdateDefaultMaps(long,int,int,int,int,bool)));

	if (g_oSttTestResourceMngr.m_oWeak_Tags.GetCount() > 0)
	{
		connect(m_pChMapsGrid, SIGNAL(sig_WeakEndEditCellHasChanged(CSttChMaps*)), m_pChMapsQuickWidget->m_pCurWeakQuickGrid, SLOT(slot_UpdateWeakComboxState(CSttChMaps*)));
		connect(m_pChMapsQuickWidget->m_pCurWeakQuickGrid, SIGNAL(sig_WeakChMapStateIsChanged(long,int,int,int,int,bool)), m_pChMapsGrid, SLOT(slot_UpdateDefaultMaps(long,int,int,int,int,bool)));
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

void QChMapsWidget::slot_DefautMapsClicked()
{
	BOOL bHasDigital = FALSE,bHasWeek = FALSE;

	if (m_pDigitalSel_CheckBox->checkState() == Qt::Checked)
	{
		bHasDigital = TRUE;
	}

	if (m_pWeakSel_CheckBox->checkState() == Qt::Checked)
	{
		bHasWeek = TRUE;
	}

	if (!g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(m_pCurChMaps,m_pCurSysParas->m_nIecFormat,bHasDigital,bHasWeek))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("缺少硬件资源文件,无法创建缺省通道映射.")*/g_sLangTxt_Gradient_MissingDefaultMappings.GetString());
		return;
	}

	m_pChMapsGrid->ShowDatas(m_pCurChMaps);
	long nType = g_oSttTestResourceMngr.m_pTestResouce->GetTestRsType();
	if ((nType == STT_TEST_RESOURCE_TYPE_4U3I) || (nType == STT_TEST_RESOURCE_TYPE_6U6I))
	{
		m_pChMapsQuickWidget->m_pVoltAnalogQuickGrid->slot_UpdateAnalogUComboxState(m_pCurChMaps);
		m_pChMapsQuickWidget->m_pCurAnalogQuickGrid->slot_UpdateAnalogIComboxState(m_pCurChMaps);
		if (g_oSttTestResourceMngr.m_oWeak_Tags.GetCount() > 0)
		{
			m_pChMapsQuickWidget->m_pCurWeakQuickGrid->slot_UpdateWeakComboxState(m_pCurChMaps);
		}
	}
	
}

void QChMapsWidget::slot_ImportChMapsClicked()
{
	CString strDBPath = _P_GetDBPath();

	CString strFilePath;
	CString strTmp;
	strTmp = g_oSttTestResourceMngr.m_pTestResouce->GetChMapsFilePostfix();
	CString strFilter;
	strFilter.Format(_T("project(*.%s)"),strTmp.GetString());

	strFilePath = QFileDialog::getOpenFileName(0, /*QObject::tr("选择通道映射文件")*/g_sLangTxt_Native_SelMapFile,
		strDBPath,
		strFilter);

	if (!strFilePath.IsEmpty())
	{
		m_pCurChMaps->OpenChMapsFile(strFilePath);
		m_pChMapsGrid->ShowDatas(m_pCurChMaps);
	}
}

void QChMapsWidget::slot_ExportChMapsClicked()
{
	CString strDBPath = _P_GetDBPath();
	CString strFilePath;

	QDir dir;
	if (!dir.exists(strDBPath))
	{
		if(!dir.mkpath(strDBPath))
		{
			QMessageBox::information(NULL, /*QObject::tr("提示")*/g_sLangTxt_Message, /*QObject::tr("创建通道映射缺省路径失败.")*/g_sLangTxt_Gradient_FailDefaultPath);
			return ;
		}
	}

	CString strTmp;
	strTmp = g_oSttTestResourceMngr.m_pTestResouce->GetChMapsFilePostfix();
	CString strFilter;
	strFilter.Format(_T("project(*.%s)"),strTmp.GetString());
	strFilePath = QFileDialog::getSaveFileName(0, /*QObject::tr("通道映射文件另存为")*/g_sLangTxt_Native_SaveMapFile,
		strDBPath,
		strFilter);

	if (!strFilePath.isEmpty())
	{
		if (!strFilePath.endsWith(strTmp.GetString()))
		{
			strFilePath.AppendFormat(_T(".%s"),strTmp.GetString());
		}

		CString strTmp;

		if (m_pCurChMaps->SaveChMapsFile(strFilePath))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,/*_T("导出通道映射文件[%s]成功.")*/g_sLangTxt_Native_ExpMapSucc.GetString(),strFilePath.GetString());
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,/*_T("导出通道映射文件[%s]失败.")*/g_sLangTxt_Native_ExpMapFail.GetString(),strFilePath.GetString());
		}
	}
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("缺少硬件资源文件,无法创建缺省通道映射.")*/g_sLangTxt_Gradient_MissingDefaultMappings.GetString());
		return;
	}

	g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(m_pCurChMaps,m_pCurSysParas->m_nIecFormat,TRUE);
	m_pChMapsGrid->ShowDatas(m_pCurChMaps);
}

void QChMapsWidget::ReleaseUI()
{
	if (m_pOutputSel_GroupBox != NULL)
	{
		delete m_pOutputSel_GroupBox;
		m_pOutputSel_GroupBox = NULL;
	}

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

	if (m_pChMapsGrid != NULL)
	{
		delete m_pChMapsGrid;
		m_pChMapsGrid = NULL;
	}

	if (m_pChMapsQuickWidget != NULL)
	{
		delete m_pChMapsQuickWidget;
		m_pChMapsQuickWidget = NULL;
	}

	if (m_pChMapsQuickSet_GroupBox != NULL)
	{
		delete m_pChMapsQuickSet_GroupBox;
		m_pChMapsQuickSet_GroupBox = NULL;
	}

	if (m_pChMaps_GridLayout != NULL)
	{
		delete m_pChMaps_GridLayout;
		m_pChMaps_GridLayout = NULL;
	}

}

