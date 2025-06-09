#include "SttIecSysParasOtherSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/XLangResource_Native.h"

QSttIecSysParasOtherSetDialog::QSttIecSysParasOtherSetDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

//	m_pMain_HLayout = NULL;
//	m_pMain_ScrollArea = NULL;
//	m_pScrollArea_Widget = NULL;
	m_pMain_VLayout = NULL;
// 	m_pBCode1588GroupBox = NULL;
// 	m_pBCode1588HBoxLayout = NULL;
	m_pLCFibersGroupBox = NULL;
	m_pLCFibersHLayout = NULL;
	m_pSTFibersGroupBox = NULL;
	m_pSTFibersHLayout = NULL;
	m_pOK_CancelHLayout = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_pFiberParas = NULL;
	InitUI();
}

QSttIecSysParasOtherSetDialog::~QSttIecSysParasOtherSetDialog()
{
 
}

void QSttIecSysParasOtherSetDialog::InitUI()
{
	resize(250,315);
	this->setFixedWidth(250);
	this->setFixedHeight(315);
	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"State_Othersettings");
	setWindowTitle(strTemp);
//	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

//	m_pBCode1588GroupBox = new QGroupBox;
// 	m_oBCodeRadioGroup.pFirstRadio = new QRadioButton(tr("正逻辑"));
// 	m_oBCodeRadioGroup.pSecondRadio = new QRadioButton(tr("负逻辑"));
// 	m_oBCodeRadioGroup.pRadioGroupBox = new QGroupBox(tr("B码逻辑"));
// 	m_oBCodeRadioGroup.pVBoxLayout = new QVBoxLayout;
// 	m_oBCodeRadioGroup.pVBoxLayout->addWidget(m_oBCodeRadioGroup.pFirstRadio);
// 	m_oBCodeRadioGroup.pVBoxLayout->addWidget(m_oBCodeRadioGroup.pSecondRadio);
// 	//vBoxLayout1->addStretch();
// 	m_oBCodeRadioGroup.pRadioGroupBox->setLayout(m_oBCodeRadioGroup.pVBoxLayout);
// 
// 	m_oIEC1588RadioGroup.pFirstRadio = new QRadioButton(tr("对等延时"));
// 	m_oIEC1588RadioGroup.pSecondRadio = new QRadioButton(tr("延时请求-响应"));
// 	m_oIEC1588RadioGroup.pRadioGroupBox = new QGroupBox(tr("IEC1588同步机制"));
// 	m_oIEC1588RadioGroup.pVBoxLayout = new QVBoxLayout;
// 	m_oIEC1588RadioGroup.pVBoxLayout->addWidget(m_oIEC1588RadioGroup.pFirstRadio);
// 	m_oIEC1588RadioGroup.pVBoxLayout->addWidget(m_oIEC1588RadioGroup.pSecondRadio);
// 	m_oIEC1588RadioGroup.pRadioGroupBox->setLayout(m_oIEC1588RadioGroup.pVBoxLayout);
// 	
// 	m_pBCode1588HBoxLayout = new QHBoxLayout;
// 	m_pBCode1588HBoxLayout->addWidget(m_oBCodeRadioGroup.pRadioGroupBox);
// 	m_pBCode1588HBoxLayout->addWidget(m_oIEC1588RadioGroup.pRadioGroupBox);
// 	m_pBCode1588GroupBox->setLayout(m_pBCode1588HBoxLayout);

	m_pLCFibersGroupBox = new QGroupBox;
	m_pLCFibersHLayout = new QHBoxLayout;
	CString strGroupDesc,strFirstRadioDesc,strSecondRadioDesc;
	xlang_GetLangStrByFile(strFirstRadioDesc,"IEC_FMByte");
	xlang_GetLangStrByFile(strSecondRadioDesc,"IEC_GMByte");
// 	strFirstRadioDesc = tr("百兆口");
// 	strSecondRadioDesc = tr("千兆口");

	for (int nIndex = 0;nIndex<STT_IEC_SYSPARAS_LC_FIBER_NUM;nIndex++)
	{
		xlang_GetLangStrByFile(strTemp,"IEC_LCFI");
		strGroupDesc = strTemp + CString(tr("%1")).arg(nIndex+1);
		m_oLCFiberRadioGroup[nIndex].pFirstRadio = new QRadioButton(strFirstRadioDesc);
		m_oLCFiberRadioGroup[nIndex].pSecondRadio = new QRadioButton(strSecondRadioDesc);
		m_oLCFiberRadioGroup[nIndex].pRadioGroupBox = new QGroupBox(strGroupDesc);
		m_oLCFiberRadioGroup[nIndex].pVBoxLayout = new QVBoxLayout;
		m_oLCFiberRadioGroup[nIndex].pVBoxLayout->addWidget(m_oLCFiberRadioGroup[nIndex].pFirstRadio);
		m_oLCFiberRadioGroup[nIndex].pVBoxLayout->addWidget(m_oLCFiberRadioGroup[nIndex].pSecondRadio);
		m_oLCFiberRadioGroup[nIndex].pRadioGroupBox->setLayout(m_oLCFiberRadioGroup[nIndex].pVBoxLayout);
		m_pLCFibersHLayout->addWidget(m_oLCFiberRadioGroup[nIndex].pRadioGroupBox);
		m_oLCFiberRadioGroup[nIndex].pFirstRadio->setChecked(true);
	}

	m_pLCFibersGroupBox->setLayout(m_pLCFibersHLayout);
	m_pSTFibersGroupBox = new QGroupBox;
	m_pSTFibersHLayout = new QHBoxLayout;

	xlang_GetLangStrByFile(strTemp,"IEC_STFI");
	for (int nIndex=0; nIndex<STT_IEC_SYSPARAS_ST_FIBER_NUM; nIndex++)
	{
		m_oSTFiberGroup[nIndex].pFirstRadio = new QRadioButton();
		xlang_SetLangStrToWidget(m_oSTFiberGroup[nIndex].pFirstRadio, "IEC_IRIGB", XLang_Ctrls_QRadioButton);

		//m_oSTFiberGroup[nIndex].pFirstRadio = new QRadioButton(tr("B码"));
		m_oSTFiberGroup[nIndex].pSecondRadio = new QRadioButton(tr("FT3"));
		m_oSTFiberGroup[nIndex].pRadioGroupBox = new QGroupBox(strTemp + CString(tr("%1:").arg(nIndex+1)));
		m_oSTFiberGroup[nIndex].pVBoxLayout = new QVBoxLayout;
		m_oSTFiberGroup[nIndex].pVBoxLayout->addWidget(m_oSTFiberGroup[nIndex].pFirstRadio);
		m_oSTFiberGroup[nIndex].pVBoxLayout->addWidget(m_oSTFiberGroup[nIndex].pSecondRadio);
		m_oSTFiberGroup[nIndex].pRadioGroupBox->setLayout(m_oSTFiberGroup[nIndex].pVBoxLayout);
		m_pSTFibersHLayout->addWidget(m_oSTFiberGroup[nIndex].pRadioGroupBox);
		m_oSTFiberGroup[nIndex].pFirstRadio->setChecked(true);
	}

	m_pSTFibersGroupBox->setLayout(m_pSTFibersHLayout);

	m_pOK_PushButton = new QPushButton(this);
// 	m_pOK_PushButton->setText(tr("确定"));
// 	m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));
	xlang_SetLangStrToWidget(m_pOK_PushButton, "sOK", XLang_Ctrls_QPushButton);

	m_pCancel_PushButton = new QPushButton(this);
// 	m_pCancel_PushButton->setText(tr("取消"));
// 	m_pCancel_PushButton->setIcon (QPixmap( "./images/Cancel.png"));
	xlang_SetLangStrToWidget(m_pCancel_PushButton, "sCancel", XLang_Ctrls_QPushButton);
	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);
	m_pOK_CancelHLayout->addSpacing(20);
	m_pOK_CancelHLayout->addWidget(m_pCancel_PushButton);
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);
	//main
	m_pMain_VLayout = new QVBoxLayout(this);
//	m_pScrollAreaWidget_GridLayout->setHorizontalSpacing(100);
//	m_pScrollAreaWidget_GridLayout->addWidget(m_pBCode1588GroupBox, 0, 0, 1, 2);
 	m_pMain_VLayout->addWidget(m_pLCFibersGroupBox/*, 0, 0, 1, 2*/);
 	m_pMain_VLayout->addWidget(m_pSTFibersGroupBox/*, 1, 0, 1, 2*/);
	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout/*,2, 0, 1, 2*/);

// 	m_pMain_ScrollArea = new QScrollArea(this);
// 	m_pScrollArea_Widget = new QWidget(m_pMain_ScrollArea);
//	m_pScrollArea_Widget->setLayout(m_pScrollAreaWidget_GridLayout);

// 	m_pMain_ScrollArea->setWidget(m_pScrollArea_Widget);
// 	m_pMain_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

// 	m_pMain_HLayout = new QHBoxLayout(this);
// 	m_pMain_HLayout->addWidget(m_pMain_ScrollArea);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QSttIecSysParasOtherSetDialog::InitData(CIecCfgFiberParas *pFiberParas)
{
	m_pFiberParas = pFiberParas;

	CString strID;
	CIecCfgFiberPara *pFiberPara = NULL;

	for (int nIndex = 0;nIndex<STT_IEC_SYSPARAS_LC_FIBER_NUM;nIndex++)
	{
		strID.Format(_T("LC%d"),nIndex+1);
		pFiberPara = (CIecCfgFiberPara*)m_pFiberParas->FindByID(strID);

		if (pFiberPara == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_parameterport.GetString(),strID.GetString());
		}
		else
		{
			m_oLCFiberRadioGroup[nIndex].pSecondRadio->setChecked(pFiberPara->m_ntype);
		}
	}

	for (int nIndex = 0;nIndex<STT_IEC_SYSPARAS_ST_FIBER_NUM;nIndex++)
	{
		strID.Format(_T("ST%d"),nIndex+1);
		pFiberPara = (CIecCfgFiberPara*)m_pFiberParas->FindByID(strID);

		if (pFiberPara == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_parameterport.GetString(),strID.GetString());
		}
		else
		{
			m_oSTFiberGroup[nIndex].pSecondRadio->setChecked(pFiberPara->m_ntype);
		}
	}
}

void QSttIecSysParasOtherSetDialog::SaveData()
{
	CString strID;
	CIecCfgFiberPara *pFiberPara = NULL;

	for (int nIndex = 0;nIndex<STT_IEC_SYSPARAS_LC_FIBER_NUM;nIndex++)
	{
		strID.Format(_T("LC%d"),nIndex+1);
		pFiberPara = (CIecCfgFiberPara*)m_pFiberParas->FindByID(strID);

		if (pFiberPara == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_parameterport.GetString(),strID.GetString());
		}
		else
		{
			pFiberPara->m_ntype = m_oLCFiberRadioGroup[nIndex].pSecondRadio->isChecked();
		}
	}

	for (int nIndex = 0;nIndex<STT_IEC_SYSPARAS_ST_FIBER_NUM;nIndex++)
	{
		strID.Format(_T("ST%d"),nIndex+1);
		pFiberPara = (CIecCfgFiberPara*)m_pFiberParas->FindByID(strID);

		if (pFiberPara == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_parameterport.GetString(),strID.GetString());
		}
		else
		{
			pFiberPara->m_ntype = m_oSTFiberGroup[nIndex].pSecondRadio->isChecked();
		}
	}
}

void QSttIecSysParasOtherSetDialog::slot_OKClicked()
{
	SaveData();
	close();
}

void QSttIecSysParasOtherSetDialog::slot_CancelClicked()
{
	close();
}


