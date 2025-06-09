#include <QMessageBox>
#include "SttIecSMV92InWidget.h"
#include <QDebug>
#include <fstream>
#include <QEvent>
#include <QKeyEvent>
#include "SttIecSMV92OtherSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"]
//#include "../../../../61850/Module/CfgDataMngr/IecCfgSmvInDatas.h"
//#include "../SttTestCntrFrameBase.h"

QSttIecSMV92InWidget::QSttIecSMV92InWidget(QFont oIecFont,QWidget *parent)
	: QSttIecConfigWidgetBase(parent)
{
	m_oIecFont = oIecFont;
	SetFont(m_oIecFont);
	InitUI();
	this->installEventFilter(this);
}

QSttIecSMV92InWidget::~QSttIecSMV92InWidget()
{
}

void QSttIecSMV92InWidget::InitUI()
{
 	QSttIecConfigWidgetBase::InitUI();
 	CreateToolbar();
	SetIecSMV92InFont();

	m_pIecCfgDataGridBase = new CIecCfgSmvData92InGrid(this);
	m_pIecCfgDataGridBase->horizontalHeader()->setFont(*g_pSttGlobalFont);//2022-10-22 sy 修改为*g_pSttGlobalFont
	m_pIecCfgDataGridBase->setFont(*g_pSttGlobalFont);
	m_pIecCfgDataGridBase->InitGrid();

 	m_pMainVLayout = new QVBoxLayout;
 	setLayout(m_pMainVLayout);
	m_pMainVLayout->addLayout(m_pSMV92FirstHLayout);
	m_pMainVLayout->addWidget(m_pIecCfgDataGridBase);
	m_pMainVLayout->addLayout(m_pCtrlBlocksSetHLayout);
}

void QSttIecSMV92InWidget::CreateToolbar()
{
	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_Details");

	m_pSMV92OtherSetButton = new QPushButton(strTemp);
	connect(m_pSMV92OtherSetButton, SIGNAL(clicked()), SLOT(slot_SMV92OtherSetClicked()));
	m_pSmpRateLineEdit = new QFloatLineEdit();
	m_pSmpRateLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	m_pSMV92FirstHLayout = new QHBoxLayout;
	m_pLabel = new QLabel(strTemp,this);
	xlang_SetLangStrToWidget(m_pLabel, "IEC_SamplingRate", XLang_Ctrls_QLabel);
// 	xlang_GetLangStrByFile(strTemp,"IEC_SamplingRate");
	m_pSMV92FirstHLayout->addWidget(m_pLabel);
	m_pSMV92FirstHLayout->addWidget(m_pSmpRateLineEdit);

	m_pSMV92FirstHLayout->addStretch();
	m_pSMV92FirstHLayout->addWidget(m_pSMV92OtherSetButton);

	connect(m_pSmpRateLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_SmpRateEdit_editingFinished()),Qt::UniqueConnection);

#ifdef _PSX_QT_LINUX_
	connect(m_pSmpRateLineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_SmpRateEditClicked()),Qt::UniqueConnection);

#endif
}

void QSttIecSMV92InWidget::SetIecSMV92InFont()
{
	m_pLabel->setFont(*g_pSttGlobalFont);
	m_pSmpRateLineEdit->setFont(*g_pSttGlobalFont);
	m_pSMV92OtherSetButton->setFont(*g_pSttGlobalFont);
}

void QSttIecSMV92InWidget::InitData(CIecCfgDatasBase* pIecCfgDatasBase)
{
	ASSERT(pIecCfgDatasBase);
	QSttIecConfigWidgetBase::InitData(pIecCfgDatasBase);
	CIecCfgDatasSmvIn* pIecCfgDatasSmvIn = (CIecCfgDatasSmvIn*)pIecCfgDatasBase;
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSmvIn->GetCommonData();
	m_pSmpRateLineEdit->InitCoverage(1,12800,0);
	m_pSmpRateLineEdit->SetValue(pSmvCommon->m_nSampleRate);
}

void QSttIecSMV92InWidget::SaveData()
{
	CIecCfgDatasSmvIn* pIecCfgDatasSmvIn = (CIecCfgDatasSmvIn*)m_pIecCfgDatasBase;
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSmvIn->GetCommonData();
	pSmvCommon->m_nSampleRate = m_pSmpRateLineEdit->GetValue_Long();
	pIecCfgDatasSmvIn->InitCfgDatasByCommon();
}

bool QSttIecSMV92InWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) 
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Down) 
		{	
		}
		else if (keyEvent->key() == Qt::Key_Up)
		{
		}
		else if (keyEvent->key() == Qt::Key_Escape)
		{
			return true;
		}

		return false;
	}else{
		return false;
	}
}

void QSttIecSMV92InWidget::slot_SMV92OtherSetClicked()
{
	CIecCfgDatasSmvIn* pIecCfgDatasSmvIn = (CIecCfgDatasSmvIn*)m_pIecCfgDatasBase;
	QSttIecSMV92OtherSetDialog oSmv92OtherSetDlg;
	oSmv92OtherSetDlg.setWindowModality(Qt::WindowModal);
	oSmv92OtherSetDlg.setFont(font());
	oSmv92OtherSetDlg.InitData(pIecCfgDatasSmvIn->GetIecCfgSmvRates());
	oSmv92OtherSetDlg.exec();
}

void QSttIecSMV92InWidget::slot_lne_SmpRateEditClicked()
{
	CString strValue;
	strValue = m_pSmpRateLineEdit->text();
	GetWidgetBoard_DigitData(4, strValue,m_pSmpRateLineEdit, this);
// 	m_pSmpRateLineEdit->setText(strValue);
}
void QSttIecSMV92InWidget::slot_lne_SmpRateEdit_editingFinished()
{
	CString strValue;
	strValue = m_pSmpRateLineEdit->text();
 	m_pSmpRateLineEdit->setText(strValue);
}
