#include "SttCommCmdWzd_DsReadWidget.h"
#include "ui_SttCommCmdWzd_DsReadWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttGlobalDef.h"
#include "../SttTestCntrFrameBase.h"
#include "SettingZoneComboBox.h"
#include "SttCmdWzdDataAddWidget.h"
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"


#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

void QSttCommCmdWzd_DsReadWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{

}

QSttCommCmdWzd_DsReadWidget::QSttCommCmdWzd_DsReadWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttCommCmdWzd_DsReadWidget)
{
    ui->setupUi(this);
	xlang_SetLangStrToWidget_Txt(ui->m_txtSetZone,g_sLangTxt_FixedValueRegion,XLang_Ctrls_QLabel);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_pReadGrid = new CSttCmdWzdGrid_Read(this);
	m_pReadGrid->InitGrid();
	m_pReadGrid->AttachDataViewOptrInterface(this);
	ui->verticalLayout->insertWidget(1, m_pReadGrid);

	UI_SetFont(font);
	SettingZoneComboBox_Init(ui->m_cmbSetZone);

	connect(ui->m_cmbSetZone, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cmbSettingZone_currentIndexChanged(int)));
	connect(this,SIGNAL(sig_EnableSettingZone()), this, SLOT(slot_EnableSettingZone()));
}

QSttCommCmdWzd_DsReadWidget::~QSttCommCmdWzd_DsReadWidget()
{
    delete ui;
}

void QSttCommCmdWzd_DsReadWidget::UI_SetFont(QFont font)
{
 	ui->m_txtSetZone->setFont(font);
	ui->m_cmbSetZone->setFont(font);
}

void QSttCommCmdWzd_DsReadWidget::ShowDatas(CExBaseList *pList)
{
	if (m_pReadGrid == NULL)
	{
		return;
	}

	m_pCurrStep = (CSttCmdWzd_Step *)pList;
	m_pReadGrid->ShowDatas(m_pCurrStep);

	if (m_pCurrStep->m_nZoneIndex != -1)
	{
		ui->m_cmbSetZone->setCurrentIndex(m_pCurrStep->m_nZoneIndex);
	}
	else
	{
		ui->m_cmbSetZone->setCurrentIndex(0);
	}

	//此处需要改成信号槽的方式，因为是从TCP接收子线程调用过来的
	//EnableSettingZone();
	emit sig_EnableSettingZone();
}

void QSttCommCmdWzd_DsReadWidget::EnableSettingZone()
{
	if (m_pCurrStep == NULL)
	{
		return;
	}

	if (m_pCurrStep->m_strID == _T("ReadSetting"))
	{
		ui->m_cmbSetZone->setDisabled(false);
		int index = ui->m_cmbSetZone->currentIndex();
		m_pCurrStep->m_nZoneIndex = index;
	}
	else
	{
		ui->m_cmbSetZone->setDisabled(true);
	}
}

void QSttCommCmdWzd_DsReadWidget::on_m_cmbSettingZone_currentIndexChanged(int index)
{
	if (index < 0)
	{
		index = ui->m_cmbSetZone->currentIndex();
	}

	if (m_pCurrStep != NULL)
	{
		m_pCurrStep->m_nZoneIndex = index;
	}
}

void QSttCommCmdWzd_DsReadWidget::slot_EnableSettingZone()
{
	EnableSettingZone();
}
