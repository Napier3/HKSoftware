#include "SttIecChsEditWidget.h"
#include "SttIecSMVFT3InitValueSetDialog.h"
#include "SttIecSMVFT3InMapSetDialog.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSmvRates.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfg6044CommonCh.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../SttTestCntrFrameApi.h"
#include "../../Module/XLangResource_Native.h"
#include <QHeaderView>
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"

#include <QDesktopWidget>
#include <QApplication>

QSttIecChsEditWidget::QSttIecChsEditWidget(int nChsType,QWidget *parent)
: QWidget(parent)
{
	m_nChsType = nChsType;
	m_pMain_VLayout = NULL;
	m_pOK_CancelHLayout = NULL;
	m_pIecCfgChs = NULL;
	m_pIecCfgChsGrid = NULL;
	m_p_SetChsTest_PushButton = NULL;
	m_p_SelectAll_PushButton = NULL;
	m_p_UnSelectAll_PushButton = NULL;
	m_p_SelectProtCurr_PushButton = NULL;
	m_p_SelectMeasCurr_PushButton = NULL;
	m_p_SelectVol_PushButton = NULL;
	m_pCurrentMapComboBox = NULL;
	m_pVoltageMapComboBox = NULL;

	//2023/10/19 wjs 
	m_pDcCurrentMapComboBox = NULL;
	m_pDcVoltageMapComboBox = NULL;
	m_pAcCurrentMapComboBox = NULL;
	m_pAcVoltageMapComboBox = NULL;

	InitUI();

}

QSttIecChsEditWidget::~QSttIecChsEditWidget()
{
}

void QSttIecChsEditWidget::InitUI()
{
#ifndef _PSX_QT_LINUX_//zhouhj 20230608 在window下,采用默认大小显示
//	QRect rcScreen = QApplication::desktop()->availableGeometry();
//	resize(rcScreen.width(), rcScreen.height());
//	this->setFixedWidth(rcScreen.width());
//	this->setFixedHeight(rcScreen.height());
#else
    resize(stt_FrameTestCntrFrameWidth(),stt_FrameTestCntrFrameHeight());
    this->setFixedWidth(stt_FrameTestCntrFrameWidth());
    this->setFixedHeight(stt_FrameTestCntrFrameHeight());
#endif
// 	resize(650,500);
// 	this->setFixedWidth(650);
// 	this->setFixedHeight(500);

	//int a= IecConfigNavigationTreeIndex;

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_ChEdit");

	if (m_nChsType == STT_IEC_CHS_TYPE_SMV92)
	{
		m_pIecCfgChsGrid = new CIecCfgSmv92ChsGrid(this);
	}
	else if (m_nChsType == STT_IEC_CHS_TYPE_SMV92IN)
	{
		m_pIecCfgChsGrid = new CIecCfgSmv92InChsGrid(this);
	}
	else if (m_nChsType == STT_IEC_CHS_TYPE_GIN)
	{
		m_pIecCfgChsGrid = new CIecCfgGinChsGrid(this);
	}
	else if (m_nChsType == STT_IEC_CHS_TYPE_GOUT)
	{
		m_pIecCfgChsGrid = new CIecCfgGoutChannelsGrid(this);
	}
	else if (m_nChsType == STT_IEC_CHS_TYPE_SMV_FT3OUT)
	{
		m_pIecCfgChsGrid = new CIecCfgSmvFT3OutChsGrid(this);
	}
	else if (m_nChsType == STT_IEC_CHS_TYPE_SMV_FT3IN)
	{
		m_pIecCfgChsGrid = new CIecCfgSmvFT3InChsGrid(this);
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前通道类型(%d)识别出错."),m_nChsType);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_channelType.GetString(),m_nChsType);
		return;
	}

	//2022-10-22 sy 增加设置表格字体大小
	m_pIecCfgChsGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecCfgChsGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgChsGrid->InitGrid();

	m_pOK_CancelHLayout = new QHBoxLayout;

	if ((m_nChsType == STT_IEC_CHS_TYPE_SMV92)||(m_nChsType == STT_IEC_CHS_TYPE_SMV92IN))
	{
		InitUI_SMV92Map();
	}
	if ((m_nChsType == STT_IEC_CHS_TYPE_SMV_FT3OUT))
	{
		InitUI_SMVFT3Map();
	}
	if ((m_nChsType == STT_IEC_CHS_TYPE_SMV_FT3IN))
	{
		InitUI_SMVFT3InMap();
	}

	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);
	//main

	m_pOK_PushButton = new QPushButton(this);
	xlang_GetLangStrByFile(strTemp,"sOK");
	m_pOK_PushButton->setText(strTemp);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);

#ifdef _PSX_QT_LINUX_
	m_pOK_PushButton->setVisible(true);
#else
	m_pOK_PushButton->setVisible(false);
#endif

	m_pMain_VLayout = new QVBoxLayout(this);
	m_pMain_VLayout->addWidget(m_pIecCfgChsGrid);
	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout);
}

void QSttIecChsEditWidget::InitData(CIecCfgChsBase *pIecCfgChs)
{
	m_pIecCfgChs = pIecCfgChs;

	if ((m_nChsType == STT_IEC_CHS_TYPE_SMV92)||(m_nChsType == STT_IEC_CHS_TYPE_SMV92IN))
	{
		if (m_pIecCfgChs != NULL)
		{
		CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data *)m_pIecCfgChs->GetAncestor(CFGCLASSID_CIECCFG92DATA);

		if (pIecCfg92Data == NULL)
		{
			pIecCfg92Data = (CIecCfg92Data *)m_pIecCfgChs->GetAncestor(CFGCLASSID_CIECCFG92INPUTDATA);
		}

		ASSERT(pIecCfg92Data);

#ifdef _PSX_QT_LINUX_
		m_p_SetChsTest_PushButton->setFixedWidth(85);
#endif
		CString strTemp;
		if (pIecCfg92Data->IsAllChSetTest())
		{
			xlang_GetLangStrByFile(strTemp,"IEC_UnSetRepair");
			m_p_SetChsTest_PushButton->setText(strTemp);
		} 
		else
		{
			xlang_GetLangStrByFile(strTemp,"IEC_SetRepair");
			m_p_SetChsTest_PushButton->setText(strTemp);
		}
		}

		m_pIecCfgChsGrid->ShowDatas(m_pIecCfgChs);

		if (m_nChsType == STT_IEC_CHS_TYPE_SMV92)
		{
			m_p_SetChsTest_PushButton->setVisible(true);
			m_p_SelectAll_PushButton->setVisible(false);
			m_p_UnSelectAll_PushButton->setVisible(false);
			m_p_SelectProtCurr_PushButton->setVisible(false);
			m_p_SelectMeasCurr_PushButton->setVisible(false);
			m_p_SelectVol_PushButton->setVisible(false);
			connect(m_p_SetChsTest_PushButton, SIGNAL(clicked()), this, SLOT(slot_SetChsTestClicked()),Qt::UniqueConnection);
		} 
		else
		{
			m_p_SetChsTest_PushButton->setVisible(false);

			m_p_SelectAll_PushButton->setVisible(true);
			m_p_UnSelectAll_PushButton->setVisible(true);
			m_p_SelectProtCurr_PushButton->setVisible(true);
			m_p_SelectMeasCurr_PushButton->setVisible(true);
			m_p_SelectVol_PushButton->setVisible(true);
			connect(m_p_SelectAll_PushButton, SIGNAL(clicked()), this, SLOT(slot_SelectAllClicked()),Qt::UniqueConnection);
			connect(m_p_UnSelectAll_PushButton, SIGNAL(clicked()), this, SLOT(slot_UnSelectAllClicked()),Qt::UniqueConnection);
			connect(m_p_SelectProtCurr_PushButton, SIGNAL(clicked()), this, SLOT(slot_SelProtCurrClicked()),Qt::UniqueConnection);
			connect(m_p_SelectMeasCurr_PushButton, SIGNAL(clicked()), this, SLOT(slot_SelMeasCurrClicked()),Qt::UniqueConnection);
			connect(m_p_SelectVol_PushButton, SIGNAL(clicked()), this, SLOT(slot_SelVolClicked()));
		}

		connect(m_pCurrentMapComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CurrentMapChanged(int)),Qt::UniqueConnection);
		connect(m_pVoltageMapComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_VoltageMapChanged(int)),Qt::UniqueConnection);
	}
	else if ((m_nChsType == STT_IEC_CHS_TYPE_SMV_FT3OUT)||(m_nChsType == STT_IEC_CHS_TYPE_SMV_FT3IN))
	{
		g_oSttTestResourceMngr.m_oIecDatasMngr.UpdateFT3ChsTypeChanged(m_pIecCfgChs,g_oSystemParas.m_nIecFormat);//20230117 suyang 在添加的时候也需要更新FT3类型

		m_pIecCfgChsGrid->ShowDatas(m_pIecCfgChs);
		connect(m_pCurrentMapComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CurrentMapChanged(int)),Qt::UniqueConnection);
		connect(m_pVoltageMapComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_VoltageMapChanged(int)),Qt::UniqueConnection);
		//2023/10/19 wjs 添加FT3柔直模块下对combox的监视
		connect(m_pDcCurrentMapComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_DcCurrentMapChanged(int)),Qt::UniqueConnection);
		connect(m_pDcVoltageMapComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_DcVoltageMapChanged(int)),Qt::UniqueConnection);
		connect(m_pAcCurrentMapComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_AcCurrentMapChanged(int)),Qt::UniqueConnection);
		connect(m_pAcVoltageMapComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_AcVoltageMapChanged(int)),Qt::UniqueConnection);
	}
	else if ((m_nChsType == STT_IEC_CHS_TYPE_GIN)||(m_nChsType == STT_IEC_CHS_TYPE_GOUT))
	{
		m_pIecCfgChsGrid->ShowDatas(m_pIecCfgChs);
	}
	else
	{
		m_pIecCfgChsGrid->ShowDatas(m_pIecCfgChs);
	}
}

void QSttIecChsEditWidget::SaveData()
{

}

void QSttIecChsEditWidget::slot_SetChsTestClicked()
{
	if ((m_nChsType != STT_IEC_CHS_TYPE_SMV92)/*&&(m_nChsType != STT_IEC_CHS_TYPE_SMV92IN)*/)
		return;

	CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data *)m_pIecCfgChs->GetAncestor(CFGCLASSID_CIECCFG92DATA);

// 	if (pIecCfg92Data == NULL)
// 	{
// 		pIecCfg92Data = (CIecCfg92Data *)m_pIecCfgChs->GetAncestor(CFGCLASSID_CIECCFG92INPUTDATA);
// 	}

	if (pIecCfg92Data == NULL)
	{
		return;
	}
#ifdef _PSX_QT_LINUX_
	m_p_SetChsTest_PushButton->setFixedWidth(85);
#endif	
	CString strTemp;
	if (pIecCfg92Data->IsAllChSetTest())
	{
//		pIecCfg92Data->SetChsQualityValue(0x00);
		pIecCfg92Data->SetTestState(0);
		xlang_GetLangStrByFile(strTemp,"IEC_SetRepair");
		m_p_SetChsTest_PushButton->setText(strTemp);
	} 
	else
	{
//		pIecCfg92Data->SetChsQualityValue(0x0800);
		pIecCfg92Data->SetTestState(1);
		xlang_GetLangStrByFile(strTemp,"IEC_UnSetRepair");
		m_p_SetChsTest_PushButton->setText(strTemp);
	}

	CIecCfgSmv92ChsGrid *pSmv92Grid = (CIecCfgSmv92ChsGrid*)m_pIecCfgChsGrid;
	pSmv92Grid->UpdateDatas_Quality();
//	m_pIecCfgChsGrid->ShowDatas(m_pIecCfgChs);
}

void QSttIecChsEditWidget::InitUI_SMV92Map()
{
	m_p_SetChsTest_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_p_SetChsTest_PushButton, "IEC_SetRepair", XLang_Ctrls_QPushButton);
	//m_p_SetChsTest_PushButton->setText(tr("置检修"));
	m_pCurrentMapComboBox = new QScrollComboBox;
	m_pVoltageMapComboBox = new QScrollComboBox;
	//CString strText;
	//strText = _T("全选");
	m_p_SelectAll_PushButton = new QPushButton(g_sLangTxt_SelAll,this);
	//strText = _T("全不选");
	m_p_UnSelectAll_PushButton = new QPushButton(g_sLangTxt_SelNone,this);
	//strText = _T("保护电流");
	m_p_SelectProtCurr_PushButton = new QPushButton(g_sLangTxt_IEC_Protectcurrent,this);
	//strText = _T("测量电流");
	m_p_SelectMeasCurr_PushButton = new QPushButton(g_sLangTxt_IEC_Measurcurrent,this);
	//strText = _T("电压");
	m_p_SelectVol_PushButton = new QPushButton(g_sLangTxt_Native_Voltage,this);


	m_pCurrentMapComboBox->addItem(_T("----"));
	m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC);
	m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC2);
	m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC3);
	m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC4);
	m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC5);
	m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC6);

	m_pVoltageMapComboBox->addItem(_T("----"));
	m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ);
	m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ2);
	m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ3);
	m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ4);
	m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ5);
	m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ6);

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_IMap");
	m_pIMap_Label = new QLabel(strTemp);
	m_pOK_CancelHLayout->addWidget(m_p_SetChsTest_PushButton);
	m_pOK_CancelHLayout->addWidget(m_pIMap_Label);
	m_pOK_CancelHLayout->addWidget(m_pCurrentMapComboBox);

	xlang_GetLangStrByFile(strTemp,"IEC_UMap");
	m_pUMap_Label = new QLabel(strTemp);
	m_pOK_CancelHLayout->addWidget(m_pUMap_Label);
	m_pOK_CancelHLayout->addWidget(m_pVoltageMapComboBox);
	m_pOK_CancelHLayout->addWidget(m_p_SelectAll_PushButton);
	m_pOK_CancelHLayout->addWidget(m_p_UnSelectAll_PushButton);
	m_pOK_CancelHLayout->addWidget(m_p_SelectProtCurr_PushButton);
	m_pOK_CancelHLayout->addWidget(m_p_SelectMeasCurr_PushButton);
	m_pOK_CancelHLayout->addWidget(m_p_SelectVol_PushButton);

	SetIec92ChsEditFont();
}
void QSttIecChsEditWidget::SetIec92ChsEditFont()
{
	m_p_SelectVol_PushButton->setFont(*g_pSttGlobalFont);
	m_p_SetChsTest_PushButton->setFont(*g_pSttGlobalFont);
	m_p_SelectAll_PushButton->setFont(*g_pSttGlobalFont);
	m_p_SelectMeasCurr_PushButton->setFont(*g_pSttGlobalFont);
	m_p_SelectProtCurr_PushButton->setFont(*g_pSttGlobalFont);
	m_p_UnSelectAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pIMap_Label->setFont(*g_pSttGlobalFont);
	m_pUMap_Label->setFont(*g_pSttGlobalFont);
	m_pVoltageMapComboBox->setFont(*g_pSttGlobalFont);
	m_pCurrentMapComboBox->setFont(*g_pSttGlobalFont);

}
void QSttIecChsEditWidget::InitUI_SMVFT3Map()/////////
{
	if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)//当前系统参数为柔直FT3
	{
		m_pDcVoltageMapComboBox = new QComboBox;
		m_pDcCurrentMapComboBox = new QComboBox;
		m_pAcVoltageMapComboBox = new QComboBox;
		m_pAcCurrentMapComboBox = new QComboBox;

		m_pDcVoltageMapComboBox->addItem(_T("----"));
		m_pDcVoltageMapComboBox->addItem(SMV_RATEID_STR_U1_123);
		m_pDcVoltageMapComboBox->addItem(SMV_RATEID_STR_U2_123);
// 		m_pDcVoltageMapComboBox->addItem(SMV_RATEID_STR_U3_123);
// 		m_pDcVoltageMapComboBox->addItem(SMV_RATEID_STR_U4_123);

		m_pDcCurrentMapComboBox->addItem(_T("----"));
		m_pDcCurrentMapComboBox->addItem(SMV_RATEID_STR_I1_123);
		m_pDcCurrentMapComboBox->addItem(SMV_RATEID_STR_I2_123);
		m_pDcCurrentMapComboBox->addItem(SMV_RATEID_STR_I3_123);
		m_pDcCurrentMapComboBox->addItem(SMV_RATEID_STR_I4_123);

		m_pAcVoltageMapComboBox->addItem(_T("----"));
		m_pAcVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ);
		m_pAcVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ2);
	
		m_pAcCurrentMapComboBox->addItem(_T("----"));
		m_pAcCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC);
		m_pAcCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC2);
		CString strTextTmp;
		strTextTmp = /* _T("?直流电压映射") */g_sLangTxt_Native_DCVmapping;
		m_pDcUMap_Label = new QLabel(strTextTmp);
		m_pOK_CancelHLayout->addWidget(m_pDcUMap_Label);
		m_pOK_CancelHLayout->addWidget(m_pDcVoltageMapComboBox);
	
		strTextTmp = /* _T("?直流电流映射") */g_sLangTxt_Native_DCImapping;
		m_pDcIMap_Label = new QLabel(strTextTmp);
		m_pOK_CancelHLayout->addWidget(m_pDcIMap_Label);
		m_pOK_CancelHLayout->addWidget(m_pDcCurrentMapComboBox);

		strTextTmp = /* _T("交流电压映射") */g_sLangTxt_Native_ACVmapping;
		m_pAcUMap_Label = new QLabel(strTextTmp);
		m_pOK_CancelHLayout->addWidget(m_pAcUMap_Label);
		m_pOK_CancelHLayout->addWidget(m_pAcVoltageMapComboBox);

		strTextTmp = /* _T("交流电流映射") */g_sLangTxt_Native_ACImapping;
		m_pAcIMap_Label = new QLabel(strTextTmp);
		m_pOK_CancelHLayout->addWidget(m_pAcIMap_Label);
		m_pOK_CancelHLayout->addWidget(m_pAcCurrentMapComboBox);

		m_p_SetInitValue_PushButton = new QPushButton(g_sLangTxt_IEC_SetInitValue,this);
		m_pOK_CancelHLayout->addWidget(m_p_SetInitValue_PushButton);
		connect(m_p_SetInitValue_PushButton, SIGNAL(clicked()), this, SLOT(slot_SetInitValueClicked()));
	
	}
	else
	{
		m_pCurrentMapComboBox = new QScrollComboBox;
		m_pVoltageMapComboBox = new QScrollComboBox;

		m_pCurrentMapComboBox->addItem(_T("----"));
		m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC);
		m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC2);
		m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC3);
		m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC4);
// 		m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC5);//2024-5-30 wuxinyi 区分交流电流测量与保护之后限制4电压4电流
// 		m_pCurrentMapComboBox->addItem(SMV_RATEID_STR_IABC6);

		m_pVoltageMapComboBox->addItem(_T("----"));
		m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ);
		m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ2);
		m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ3);
		m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ4);
// 		m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ5);
// 		m_pVoltageMapComboBox->addItem(SMV_RATEID_STR_UABCZ6);

		m_pIMap_Label = new QLabel(g_sLangTxt_IEC_IMap);
		m_pOK_CancelHLayout->addWidget(m_pIMap_Label);
		m_pOK_CancelHLayout->addWidget(m_pCurrentMapComboBox);

		m_pUMap_Label = new QLabel(g_sLangTxt_IEC_UMap);
		m_pOK_CancelHLayout->addWidget(m_pUMap_Label);
		m_pOK_CancelHLayout->addWidget(m_pVoltageMapComboBox);

		m_p_SetInitValue_PushButton = new QPushButton(g_sLangTxt_IEC_SetInitValue,this);
		m_pOK_CancelHLayout->addWidget(m_p_SetInitValue_PushButton);
		connect(m_p_SetInitValue_PushButton, SIGNAL(clicked()), this, SLOT(slot_SetInitValueClicked()));
		SetIecFT3ChsEditFont();
	}

	if (m_pIecCfgChsGrid->GetCurrSelData() == NULL)
	{
		slot_SetInitValueEnabled(false);//20240418 suyang 初始化时没有选中数据，设置按钮灰化
	}

	connect(m_pIecCfgChsGrid, SIGNAL(sig_UpdateInitValueBtnEnabled(bool )), this, SLOT(slot_SetInitValueEnabled(bool)));
}

void QSttIecChsEditWidget::slot_SetInitValueEnabled(bool isSetInitValue)
{

	m_p_SetInitValue_PushButton->setEnabled(isSetInitValue);
}



void QSttIecChsEditWidget::InitUI_SMVFT3InMap()/////////
{
	m_p_DIMap_PushButton = new QPushButton(g_sLangTxt_IEC_DIMap,this);
	m_pOK_CancelHLayout->addWidget(m_p_DIMap_PushButton);
	m_p_DIMap_PushButton->setFont(*g_pSttGlobalFont);
	
	//slot_BinMapEnabled();

	if (m_pIecCfgChsGrid->GetCurrSelData() == NULL)
	{
		slot_BinMapEnabled(false);
	}
	connect(m_pIecCfgChsGrid, SIGNAL(sig_UpdateBinMapEnabled(bool)), this, SLOT(slot_BinMapEnabled(bool)));

	connect(m_p_DIMap_PushButton, SIGNAL(clicked()), this, SLOT(slot_DIMapClicked()));
}

void QSttIecChsEditWidget::slot_BinMapEnabled(bool isBinMapEnabled)
{
	m_p_DIMap_PushButton->setEnabled( isBinMapEnabled);

}

void QSttIecChsEditWidget::SetIecFT3ChsEditFont()
{
	m_p_SetInitValue_PushButton->setFont(*g_pSttGlobalFont);
	m_pIMap_Label->setFont(*g_pSttGlobalFont);
	m_pUMap_Label->setFont(*g_pSttGlobalFont);
	m_pVoltageMapComboBox->setFont(*g_pSttGlobalFont);
	m_pCurrentMapComboBox->setFont(*g_pSttGlobalFont);
}

void QSttIecChsEditWidget::slot_CurrentMapChanged(int nIndex)
{
	SwitchChMap(nIndex,FALSE,TRUE,FALSE);
}

//2023/10/16 wjs 添加直流/交流 电压/电流的信号和槽函数

void QSttIecChsEditWidget::slot_VoltageMapChanged(int nIndex)
{
	SwitchChMap(nIndex,TRUE,FALSE,FALSE);
}

void QSttIecChsEditWidget::slot_DcVoltageMapChanged(int nIndex)
{
	SwitchChMap(nIndex,TRUE,FALSE,TRUE);

}
void QSttIecChsEditWidget::slot_DcCurrentMapChanged(int nIndex)
{
	SwitchChMap(nIndex,FALSE,TRUE,TRUE);
}

void QSttIecChsEditWidget::slot_AcVoltageMapChanged(int nIndex)
{
	SwitchChMap(nIndex,TRUE,FALSE,FALSE);
}

void QSttIecChsEditWidget::SwitchChMap(long nGroupIndex,BOOL bSetU, BOOL bSetI,BOOL bDC_FT3)
{
	if (nGroupIndex == 0)
	{
		return;
	}

	CIecCfgSmvDataBase *pIecCfgSmvDataBase = (CIecCfgSmvDataBase *)m_pIecCfgChs->GetAncestor(CFGCLASSID_CIECCFG92DATA);

	if (pIecCfgSmvDataBase == NULL)
	{
		pIecCfgSmvDataBase = (CIecCfgSmvDataBase *)m_pIecCfgChs->GetAncestor(CFGCLASSID_CIECCFG92INPUTDATA);
	}

	if (pIecCfgSmvDataBase == NULL)
	{
		pIecCfgSmvDataBase = (CIecCfgSmvDataBase *)m_pIecCfgChs->GetAncestor(CFGCLASSID_CIECCFG6044COMMONDATA);
	}

	if (pIecCfgSmvDataBase == NULL)
	{
		pIecCfgSmvDataBase = (CIecCfgSmvDataBase *)m_pIecCfgChs->GetAncestor(CFGCLASSID_CIECCFG6044COMMONINDATA);
	}

	if (pIecCfgSmvDataBase == NULL)
	{
		return;
	}

	pIecCfgSmvDataBase->SwitchChMap(nGroupIndex-1,bSetU,bSetI,bDC_FT3);
	m_pIecCfgChsGrid->ShowDatas(m_pIecCfgChs);
}

void QSttIecChsEditWidget::slot_AcCurrentMapChanged(int nIndex)
{
	SwitchChMap(nIndex,FALSE,TRUE,FALSE);
}


void QSttIecChsEditWidget::slot_SelectAllClicked()
{
	if (m_pIecCfgChs == NULL)
	{
		return;
	}

	CIecCfg92Chs *pIecCfg92Chs = (CIecCfg92Chs*)m_pIecCfgChs;
	pIecCfg92Chs->SetSelState_SelectAll();
	m_pIecCfgChsGrid->UpdateSelectedState();
}

void QSttIecChsEditWidget::slot_UnSelectAllClicked()
{
	if (m_pIecCfgChs == NULL)
	{
		return;
	}

	CIecCfg92Chs *pIecCfg92Chs = (CIecCfg92Chs*)m_pIecCfgChs;
	pIecCfg92Chs->SetSelState_UnSelectAll();
	m_pIecCfgChsGrid->UpdateSelectedState();
}

void QSttIecChsEditWidget::slot_SelProtCurrClicked()
{
	if (m_pIecCfgChs == NULL)
	{
		return;
	}

	CIecCfg92Chs *pIecCfg92Chs = (CIecCfg92Chs*)m_pIecCfgChs;
	pIecCfg92Chs->SetSelState_SelProtCurrAll();
	m_pIecCfgChsGrid->UpdateSelectedState();
}

void QSttIecChsEditWidget::slot_SelMeasCurrClicked()
{
	if (m_pIecCfgChs == NULL)
	{
		return;
	}

	CIecCfg92Chs *pIecCfg92Chs = (CIecCfg92Chs*)m_pIecCfgChs;
	pIecCfg92Chs->SetSelState_SelMeasCurrAll();
	m_pIecCfgChsGrid->UpdateSelectedState();
}

void QSttIecChsEditWidget::slot_SelVolClicked()
{
	if (m_pIecCfgChs == NULL)
	{
		return;
	}

	CIecCfg92Chs *pIecCfg92Chs = (CIecCfg92Chs*)m_pIecCfgChs;
	pIecCfg92Chs->SetSelState_SelVolAll();
	m_pIecCfgChsGrid->UpdateSelectedState();
}

void QSttIecChsEditWidget::slot_SetInitValueClicked()
{
	if ((m_pIecCfgChs == NULL)||(m_pIecCfgChsGrid == NULL))
	{
		return;
	}
	
	CIecCfg6044CommonCh *pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)m_pIecCfgChsGrid->GetCurrSelData();

	if (pIecCfg6044CommonCh == NULL)
	{
		return;
	}

	QSttIecSMVFT3InitValueSetDialog oValueSetDlg(pIecCfg6044CommonCh->m_nValue,this);
	oValueSetDlg.exec();
	pIecCfg6044CommonCh->m_nValue = oValueSetDlg.m_dwValue;
	m_pIecCfgChsGrid->ShowDatas(m_pIecCfgChs);

}
void QSttIecChsEditWidget::slot_DIMapClicked()
{
	if ((m_pIecCfgChs == NULL)||(m_pIecCfgChsGrid == NULL))
	{
		return;
	}

	CIecCfg6044CommonCh *pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)m_pIecCfgChsGrid->GetCurrSelData();
	int nRow =m_pIecCfgChsGrid-> currentRow();


	if (pIecCfg6044CommonCh == NULL)
	{
		return;
	}

	QSttIecSMVFT3InMapSetDialog oDIMapDlg(pIecCfg6044CommonCh->m_strDevChID,this);
	oDIMapDlg.exec();
	pIecCfg6044CommonCh->m_strDevChID = oDIMapDlg.m_strMapString;
	//m_pIecCfgChsGrid->ShowDatas(m_pIecCfgChs);
	m_pIecCfgChsGrid->ShowCommonBinMap_StaticString(pIecCfg6044CommonCh,nRow);//20240308 suyang 设置完开入映射后显示到表格
}


void QSttIecChsEditWidget::slot_UpdateCB_ChDatas(CExBaseList *pCurrSelData)
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase *)pCurrSelData;

	if (pIecCfgData == NULL)
	{
		InitData(NULL);
	}
	else
	{
		InitData(pIecCfgData->m_pCfgChs);
	}
}
