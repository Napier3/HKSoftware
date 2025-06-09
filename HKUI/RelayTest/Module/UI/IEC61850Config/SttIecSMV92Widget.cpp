#include <QMessageBox>
#include "SttIecSMV92Widget.h"
#include <QDebug>
#include <fstream>
#include <QEvent>
#include <QKeyEvent>
#include "SttIecSMV92OtherSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
//#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttIecSMV92Widget::QSttIecSMV92Widget(QFont oIecFont,QWidget *parent)
	: QSttIecConfigWidgetBase(parent)
{
	m_oIecFont = oIecFont;
	SetFont(m_oIecFont);
	InitUI();
	this->installEventFilter(this);
}

QSttIecSMV92Widget::~QSttIecSMV92Widget()
{
}

void QSttIecSMV92Widget::InitUI()
{
 	QSttIecConfigWidgetBase::InitUI();
 	CreateToolbar();
	SetIecSMV92Font();

	m_pIecCfgDataGridBase = new CIecCfgSmvData92Grid(this);
	m_pIecCfgDataGridBase->horizontalHeader()->setFont(*g_pSttGlobalFont);//2022-10-22 sy 修改为*g_pSttGlobalFont
	m_pIecCfgDataGridBase->setFont(*g_pSttGlobalFont);
	m_pIecCfgDataGridBase->InitGrid();

 	m_pMainVLayout = new QVBoxLayout;
 	setLayout(m_pMainVLayout);
	m_pMainVLayout->addLayout(m_pSMV92FirstHLayout);
	m_pMainVLayout->addWidget(m_pIecCfgDataGridBase);
	m_pMainVLayout->addLayout(m_pCtrlBlocksSetHLayout);
	
}

void QSttIecSMV92Widget::SetIecSMV92Font()
{
	m_pASDUComboBox->setFont(*g_pSttGlobalFont);
	m_pSmpRateLineEdit->setFont(*g_pSttGlobalFont);
	m_pDataSetCheckBox->setFont(*g_pSttGlobalFont);
	m_pRefrTmCheckBox->setFont(*g_pSttGlobalFont);
	m_pSecurityCheckBox->setFont(*g_pSttGlobalFont);
	m_pSmpRateCheckBox->setFont(*g_pSttGlobalFont);
	m_pSMV92OtherSetButton->setFont(*g_pSttGlobalFont);
	m_pLabel->setFont(*g_pSttGlobalFont);
	m_Asdu_Label->setFont(*g_pSttGlobalFont);
	m_pPacketTypeSelCombox->setFont(*g_pSttGlobalFont);
	m_pPacketType_Label->setFont(*g_pSttGlobalFont);
}

void QSttIecSMV92Widget::CreateToolbar()
{
	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_Details");

	m_pSMV92OtherSetButton = new QPushButton(strTemp);
	connect(m_pSMV92OtherSetButton, SIGNAL(clicked()), SLOT(slot_SMV92OtherSetClicked()));
	m_pSmpRateLineEdit = new QFloatLineEdit();
	m_pSmpRateLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	m_pSmpRateLineEdit->setFixedWidth(100);
	m_pASDUComboBox = new QScrollComboBox;
	m_pASDUComboBox->setFixedWidth(80);

	m_pPacketTypeSelCombox = new QScrollComboBox;
	m_pPacketTypeSelCombox->addItem("IEC 61850 9-2(Ed 1.0)");
	m_pPacketTypeSelCombox->addItem("IEC 61850 9-2(Ed 2.0)");
	//m_pPacketTypeSelCombox->addItem("IEC 61850 9-2(Ed 2.1)");

	for (int nIndex=1; nIndex<=STT_IEC_SMV92_ASDU_MAX_NUM; nIndex++)
	{
		m_pASDUComboBox->addItem(QString::number(nIndex));
	}

	m_pDataSetCheckBox = new QNumberCheckBox(tr("DataSet"));
	m_pSecurityCheckBox = new QNumberCheckBox(tr("Security"));
	m_pSmpRateCheckBox = new QNumberCheckBox(tr("SmpRate"));
	m_pRefrTmCheckBox = new QNumberCheckBox(tr("RefrTm"));

	m_pSMV92FirstHLayout = new QHBoxLayout;
	m_pLabel = new QLabel(strTemp,this);
	xlang_SetLangStrToWidget(m_pLabel, "IEC_SamplingRate", XLang_Ctrls_QLabel);
// 	xlang_GetLangStrByFile(strTemp,"IEC_SamplingRate");

    m_pPacketType_Label = new QLabel(g_sLangTxt_Gradient_MessageType);
	m_pSMV92FirstHLayout->addWidget(m_pPacketType_Label);
	m_pSMV92FirstHLayout->addWidget(m_pPacketTypeSelCombox);

	m_pSMV92FirstHLayout->addWidget(m_pLabel/*new QLabel(strTemp)*/);
	m_pSMV92FirstHLayout->addWidget(m_pSmpRateLineEdit);
	m_Asdu_Label = new QLabel(tr("ASDU"),this);
	m_pSMV92FirstHLayout->addWidget(m_Asdu_Label/*new QLabel(tr("ASDU"))*/);
	m_pSMV92FirstHLayout->addWidget(m_pASDUComboBox);

	m_pSMV92FirstHLayout->addWidget(m_pDataSetCheckBox);
	m_pSMV92FirstHLayout->addWidget(m_pSecurityCheckBox);
	m_pSMV92FirstHLayout->addWidget(m_pSmpRateCheckBox);
	m_pSMV92FirstHLayout->addWidget(m_pRefrTmCheckBox);
	m_pSMV92FirstHLayout->addStretch();
	m_pSMV92FirstHLayout->addWidget(m_pSMV92OtherSetButton);

	connect(m_pSmpRateLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_SmpRateEdit_editingFinished()),Qt::UniqueConnection);
#ifdef _PSX_QT_LINUX_
	connect(m_pSmpRateLineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_SmpRateEditClicked()),Qt::UniqueConnection);

#endif
}

void QSttIecSMV92Widget::InitData(CIecCfgDatasBase* pIecCfgDatasBase)
{
	ASSERT(pIecCfgDatasBase);
	QSttIecConfigWidgetBase::InitData(pIecCfgDatasBase);
	CIecCfgDatasSMV* pIecCfgDatasSMV = (CIecCfgDatasSMV*)pIecCfgDatasBase;
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();
	m_pSmpRateLineEdit->InitCoverage(1,12800,0);
	m_pSmpRateLineEdit->SetValue(pSmvCommon->m_nSampleRate);
	m_pASDUComboBox->setCurrentIndex(pSmvCommon->m_nAsduNum-1);

	CIecCfg92Data* pIecCfg92Data = (CIecCfg92Data*)pIecCfgDatasSMV->FindByClassID(CFGCLASSID_CIECCFG92DATA);

	if (pIecCfg92Data != NULL)
	{
		m_pDataSetCheckBox->SetValue(pIecCfg92Data->m_nUseDataSet);
		m_pSecurityCheckBox->SetValue(pIecCfg92Data->m_nUseEncrupt);
		m_pSmpRateCheckBox->SetValue(pIecCfg92Data->m_nUseSampRate);
		m_pRefrTmCheckBox->SetValue(pIecCfg92Data->m_nUseRefreshTime);
	}
	m_pPacketTypeSelCombox->setCurrentIndex(pIecCfgDatasSMV->m_nCfg92_Version);
}

void QSttIecSMV92Widget::SaveData()
{
	CIecCfgDatasSMV* pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatasBase;
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();
	pSmvCommon->m_nSampleRate = m_pSmpRateLineEdit->GetValue_Long();
	pSmvCommon->m_nAsduNum = m_pASDUComboBox->currentIndex() + 1;

	pIecCfgDatasSMV->m_nCfg92_Version = m_pPacketTypeSelCombox->currentIndex();

	int nSelDataset = m_pDataSetCheckBox->GetValue();
	int nSelSecurity = m_pSecurityCheckBox->GetValue();
	int nSelSmpRate = m_pSmpRateCheckBox->GetValue();
	int nSelRefrTm = m_pRefrTmCheckBox->GetValue();
	CExBaseObject *pCurObj = NULL;
	CIecCfg92Data *pIecCfg92Data = NULL;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgDatasSMV->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92DATA)
		{
			pIecCfg92Data = (CIecCfg92Data *)pCurObj;
			pIecCfg92Data->m_nUseDataSet = nSelDataset;
			pIecCfg92Data->m_nUseEncrupt = nSelSecurity;
			pIecCfg92Data->m_nUseSampRate = nSelSmpRate;
			pIecCfg92Data->m_nUseRefreshTime = nSelRefrTm;
			pIecCfg92Data->m_nSampleRate = pSmvCommon->m_nSampleRate;
		}
	}

//	pIecCfgDatasSMV->InitCfgDatasByCommon();
}

void QSttIecSMV92Widget::GetOptSelectState(int &nSelDataset,int &nSelSecurity,int &nSelSmpRate,int &nSelRefrTm)
{
	nSelDataset = m_pDataSetCheckBox->GetValue();
	nSelSecurity = m_pSecurityCheckBox->GetValue();
	nSelSmpRate = m_pSmpRateCheckBox->GetValue();
	nSelRefrTm = m_pRefrTmCheckBox->GetValue();
}


bool QSttIecSMV92Widget::eventFilter(QObject *obj, QEvent *event)
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

void QSttIecSMV92Widget::slot_SMV92OtherSetClicked()
{
	CIecCfgDatasSMV* pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatasBase;
	QSttIecSMV92OtherSetDialog oSmv92OtherSetDlg(this);
	oSmv92OtherSetDlg.setWindowModality(Qt::WindowModal);
	oSmv92OtherSetDlg.setFont(font());
	oSmv92OtherSetDlg.InitData(pIecCfgDatasSMV->GetIecCfgSmvRates());

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oSmv92OtherSetDlg);
	oSmv92OtherSetDlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	oSmv92OtherSetDlg.exec();
#endif
}

void QSttIecSMV92Widget::slot_lne_SmpRateEditClicked()
{
	CString strValue;
	strValue = m_pSmpRateLineEdit->text();// .Format("%.3f",m_pSmpRateLineEdit->GetValue());
	GetWidgetBoard_DigitData(4, strValue,m_pSmpRateLineEdit, this);
// 	m_pSmpRateLineEdit->setText(strValue);
}
void QSttIecSMV92Widget::slot_lne_SmpRateEdit_editingFinished()
{
	CString strValue;
	strValue = m_pSmpRateLineEdit->text();// .Format("%.3f",m_pSmpRateLineEdit->GetValue());
	m_pSmpRateLineEdit->setText(strValue);
}
