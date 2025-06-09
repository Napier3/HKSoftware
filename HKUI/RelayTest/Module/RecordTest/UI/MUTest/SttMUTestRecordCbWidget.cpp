#include "SttMUTestRecordCbWidget.h"
#include "../../../SttTestCtrl/SttTestAppBase.h"
#include "../../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../UI/SttTestCntrFrameBase.h"
#include "../../../UI/SttTestCntrCmdDefine.h"
#include "../SttIecRecordMainWidget.h"
#include "../SttIecRecordDetectWidget.h"
#include "../SttIecSmvGrid_ChQualitySpy.h"
#include "../SttIecSmvGrid_EffecValue.h"
#include "../SttIecSmvWaveWidget.h"
#include "../SttIecSmvGrid_Power.h"
#include "../SttIecSmvGrid_Harm.h"
#include "../SttIecSmvGrid_PkgError.h"
#include "../SttIecSmvGrid_AD.h"
#include "../SttIecMUAccuracyWidget.h"
#include "../SttIecMUTimeWidget.h"
#include "../SttIecSmvGrid_MUErrorStatis.h"
#include "../SttIecGooseGrid_RT.h"
#include "../SttIecGooseGrid_TurnList.h"
#include "../SttIecGooseGrid_PkgError.h"
#include "../SttIecEmptyWidget.h"
#include "../SttIecSmvVectorWidget.h"
#include "../SttIecSmvSequenceWidget.h"
#include "../SttIecSmvMeterAxisWidget.h"
#include "../SttIecSmvGrid_ChAttr.h"
#include "../SttIecSmvGrid_PkgAnalyze.h"
#include "../SttIecGooseGrid_PkgAnalyze.h"
#include "../SttIecGooseTurnSpyWidget.h"
#include "../../../XLangResource_Native.h"
#include "../SttIecRecordWriteFileWidget.h"
#include "FirstCircleWave/SttMUTestFirstCwWidget.h"
#include "../FT3_Test/SttIecFT3Grid_RT.h"
#include "../FT3_Test/SttIecFT3OriginalMsgWidget.h"
#include "../SttIecSmvGrid_HarmAnalyze.h"



extern QSttIecRecordMainWidget *g_theSttIecRecordMainWidget;
extern QSttIecRecordDetectWidget *g_pSttIecRecordDetectWidget;

QSttMUTestRecordCbWidget::QSttMUTestRecordCbWidget(QFont font,long nPkgDetectType, QWidget *parent) :
    QDialog(parent)
{
	m_pSttIecSmvWaveWidget = NULL;
	m_pSttFirstCwWidget = NULL;
	m_pCurrCapDevice = NULL;
	m_pSttIecRcdFuncInterface = NULL;
	m_bMUTestMode = true;	
	
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SttIecRcdFuncs.xml");
	m_oIecRcdDataTypes.Open(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(&m_oIecRcdDataTypes, _T("SttIecRcdFuncs.xml"));
#endif

	if (nPkgDetectType == STT_IEC_DETECT_TYPE_60044)
	{
		if(g_pTheSttTestApp->GetCurrTestMacroUI() == STT_ORG_MACRO_MUAccurAutoTest)
		{
			m_pDataType_SttIecRcdMUFuncs = (CDataType*)m_oIecRcdDataTypes.FindByID(_T("SttIecRcdADMUAutoFuncs_Tab"));
		}
		else
		{
		m_pDataType_SttIecRcdMUFuncs = (CDataType*)m_oIecRcdDataTypes.FindByID(_T("SttIecRcdADMUFuncs_Tab"));
		}
//		g_oCapAnalysisConfig.m_nShowPrimaryValue = 0;
	}
	else
	{
		m_pDataType_SttIecRcdMUFuncs = (CDataType*)m_oIecRcdDataTypes.FindByID(_T("SttIecRcdMUFuncs_Tab"));
	}

	InitUI();
	g_pSttIecRecordCbWidget = this;
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	CString strTmp;
	strTmp = /*_T("接收通道")*/g_sLangTxt_Gradient_RecvChannnel; //lcq
	m_pSysSetBtn->setText(strTmp);
	xlang_SetLangStrToWidget(m_pPrevPageBtn, "Smv_PrevPage", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pNextPageBtn, "Smv_NextPage", XLang_Ctrls_QPushButton);


	connect(&m_oTimerIecRcdUpdate,   SIGNAL(timeout()),    this,   SLOT(slot_Timer_IecRcdUpdate()));
	OnCurrFuncChanged(-1);

	SetIecRecordCbFont();
	InitConnects();
}

QSttMUTestRecordCbWidget::~QSttMUTestRecordCbWidget()
{
	m_oTimerIecRcdUpdate.stop();
	disconnect(m_pSttRecordCBTabWidget,  SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));

	if (m_pSttIecSmvWaveWidget != NULL)
	{
		m_pSttRecordCBTabWidget->removeTab(m_pSttRecordCBTabWidget->indexOf(m_pSttIecSmvWaveWidget));
		m_pSttIecSmvWaveWidget->Release();
		m_pSttIecSmvWaveWidget = NULL;
	}
	if (m_pSttFirstCwWidget != NULL)
	{
		m_pSttRecordCBTabWidget->removeTab(m_pSttRecordCBTabWidget->indexOf(m_pSttFirstCwWidget));
		m_pSttFirstCwWidget->Release();
		m_pSttFirstCwWidget = NULL;
	}
}

void QSttMUTestRecordCbWidget::InitUI()
{
	m_pMainVLayout = new QVBoxLayout(this);
	m_pSttRecordCBTabWidget = new QTabWidget(this);
	m_pBottomBtnHLayout = new QHBoxLayout();
	m_pBottomBtnHLayout->setSpacing(6);
	m_pBottomBtnHLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
	m_pSysSetBtn = new QPushButton(this);
	m_pBottomBtnHLayout->addWidget(m_pSysSetBtn);

	CString strTmp;
	strTmp = /*"响应时间误差"*/g_sLangTxt_Gradient_ResTimeErr; //lcq
	m_pDelayValueError_Label = new QLabel(strTmp,this);
	m_pDelayValueError_Edit = new QLineEdit;
	strTmp = /*"报文响应时间"*/g_sLangTxt_Gradient_MessResTime; //lcq
	m_pRealDelayValue_Label = new QLabel(strTmp,this);
	m_pRealDelayValue_Edit = new QLineEdit;
	strTmp = /*"通道延时"*/g_sLangTxt_Gradient_ChaDelay; //lcq
	m_pDelayChValue_Label = new QLabel(strTmp,this);
	m_pDelayChValue_Edit = new QLineEdit;

	strTmp = _T("采样频率");
	m_pSampFreqLabel = new QLabel(this);
	m_pSampFreqLabel->setText(strTmp);
	m_pSampFreqEdit = new QLineEdit(this);

	strTmp = _T("输出速率");
	m_pOutputRateLabel = new QLabel(this);
	m_pOutputRateLabel->setText(strTmp);
	m_pOutputRateEdit = new QLineEdit(this);


	m_pDelayChValue_Edit->setReadOnly(true);
	m_pRealDelayValue_Edit->setReadOnly(true);
	m_pDelayValueError_Edit->setReadOnly(true);
	m_pSampFreqEdit->setReadOnly(true);
	m_pOutputRateEdit->setReadOnly(true);
	m_pDelayChValue_Edit->setText(_T("--"));
	m_pRealDelayValue_Edit->setText(_T("--"));
	m_pDelayValueError_Edit->setText(_T("--"));
	m_pSampFreqEdit->setText(_T("--"));
	m_pOutputRateEdit->setText(_T("--"));

// 	strTmp.Format(_T("%.03lf μs"),1.1f);
// 	m_pDelayValueError_Edit->setText(strTmp);

	m_pDelayChValue_Edit->setAlignment(Qt::AlignCenter);
	m_pRealDelayValue_Edit->setAlignment(Qt::AlignCenter);
	m_pDelayValueError_Edit->setAlignment(Qt::AlignCenter);
	m_pSampFreqEdit->setAlignment(Qt::AlignCenter);
	m_pOutputRateEdit->setAlignment(Qt::AlignCenter);

	m_pBottomBtnHLayout->addWidget(m_pDelayValueError_Label);
	m_pBottomBtnHLayout->addWidget(m_pDelayValueError_Edit);
	m_pBottomBtnHLayout->addWidget(m_pRealDelayValue_Label);
	m_pBottomBtnHLayout->addWidget(m_pRealDelayValue_Edit);
	m_pBottomBtnHLayout->addWidget(m_pDelayChValue_Label);
	m_pBottomBtnHLayout->addWidget(m_pDelayChValue_Edit);
	m_pBottomBtnHLayout->addWidget(m_pSampFreqLabel);
	m_pBottomBtnHLayout->addWidget(m_pSampFreqEdit);
	m_pBottomBtnHLayout->addWidget(m_pOutputRateLabel);
	m_pBottomBtnHLayout->addWidget(m_pOutputRateEdit);

	m_pBottomHSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	m_pBottomBtnHLayout->addItem(m_pBottomHSpacer1);
	m_pPrevPageBtn = new QPushButton(this);
	m_pBottomBtnHLayout->addWidget(m_pPrevPageBtn);
	m_pNextPageBtn = new QPushButton(this);
	m_pBottomBtnHLayout->addWidget(m_pNextPageBtn);
	m_pBottomHSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	m_pBottomBtnHLayout->addItem(m_pBottomHSpacer2);
	m_pMainVLayout->addWidget(m_pSttRecordCBTabWidget);
	m_pMainVLayout->addLayout(m_pBottomBtnHLayout);
	setLayout(m_pMainVLayout);

	if (m_pDataType_SttIecRcdMUFuncs)
	{
		CDataTypeValue* pDataTypeValue = NULL;
		QWidget *pCurrWidget = NULL;
		POS pos  = m_pDataType_SttIecRcdMUFuncs->GetHeadPosition();

		while(pos)
		{
			pDataTypeValue = (CDataTypeValue*)m_pDataType_SttIecRcdMUFuncs->GetNext(pos);
			pCurrWidget = NULL;

			//SMV   通道监视
			if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_ChQualitySpy)
			{
				CSttIecSmvGrid_ChQualitySpy *pGrid = new CSttIecSmvGrid_ChQualitySpy(this);
				pGrid->setFont(*g_pSttGlobalFont);
				pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->InitGrid();
				pGrid->m_bMUTestMode = TRUE;
				pCurrWidget = pGrid;
			}
			//SMV   通道属性
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_ChAttr)
			{
				CSttIecSmvGrid_ChAttr *pGrid = new CSttIecSmvGrid_ChAttr(this);
				pGrid->setFont(*g_pSttGlobalFont);
				pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->InitGrid();
				pGrid->m_bMUTestMode = TRUE;
				pCurrWidget = pGrid;
			}
			//SMV  有效值
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_EffecValue)
			{
				CSttIecSmvGrid_EffecValue *pGrid = new CSttIecSmvGrid_EffecValue(this);
				pGrid->setFont(*g_pSttGlobalFont);
				pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->InitGrid();
				pGrid->m_bMUTestMode = TRUE;
				pCurrWidget = pGrid;
			}
			//SMV   波形分析
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_Wave)
			{
				m_pSttIecSmvWaveWidget = new QSttIecSmvWaveWidget(this);
				m_pSttIecSmvWaveWidget->IecRcdFunc(NULL);
				m_pSttIecSmvWaveWidget->m_bMUTestMode = TRUE;
				pCurrWidget = m_pSttIecSmvWaveWidget;
			}
			//SMV   功率
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_Power)
			{
				CSttIecSmvGrid_Power *pGrid = new CSttIecSmvGrid_Power(this);
				pGrid->setFont(*g_pSttGlobalFont);
				pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->InitGrid();
				pGrid->m_bMUTestMode = TRUE;
				pCurrWidget = pGrid;
			}
			//SMV   谐波
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_Harm)
			{
				CSttIecSmvGrid_Harm *pGrid = new CSttIecSmvGrid_Harm(this);
				pGrid->setFont(*g_pSttGlobalFont);
				pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->InitGrid();
				pGrid->m_bMUTestMode = TRUE;
				pCurrWidget = pGrid;
			}
			//SMV   报文统计
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_PkgError)
			{
				QSttIecSmvPkgErrorWidget *pGrid = new QSttIecSmvPkgErrorWidget(this);
				pGrid->m_pGridPkgError->setFont(*g_pSttGlobalFont);
				pGrid->m_pGridPkgError->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->m_pGridPkgError->InitGrid();
				pGrid->m_bMUTestMode = TRUE;
				pCurrWidget = pGrid;
			}
			//SMV   双AD
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_AD)
			{
				CSttIecSmvGrid_AD *pGrid = new CSttIecSmvGrid_AD(this);
				pGrid->setFont(*g_pSttGlobalFont);
				pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->InitGrid();
				pGrid->m_bMUTestMode = TRUE;
				pCurrWidget = pGrid;
			}
			//SMV   MU精确度
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_MUAccuracy)
			{
				QSttIecMUAccuracyWidget *pMUAccuracyWidget = new QSttIecMUAccuracyWidget(this);
				pMUAccuracyWidget->ShowDelayTimeUI(false);
				pMUAccuracyWidget->m_bMUTestMode = TRUE;
				pCurrWidget = pMUAccuracyWidget;
			}
			//SMV   MU误差统计
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_MUErrorStatistics)
			{
				CSttIecSmvGrid_MUErrorStatis *pGrid = new CSttIecSmvGrid_MUErrorStatis(this);
				pGrid->setFont(*g_pSttGlobalFont);
				pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->InitGrid();
				pGrid->m_bMUTestMode = TRUE;
				pCurrWidget = pGrid;
			}
			//SMV   MU时间精度
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_MUTimingAccur)
			{
				QSttIecMUTimeWidget *pSttIecMUTimeWidget = new QSttIecMUTimeWidget(/*STTIEC_MUTIME_TYPE_TimeAccur,*/this);
				pSttIecMUTimeWidget->m_bMUTestMode = TRUE;
				pCurrWidget = pSttIecMUTimeWidget;
			}
			//SMV 矢量图
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_Vector)
			{
				QSttIecSmvVectorMainWidget *pSttIecSmvVectorMainWidget = new QSttIecSmvVectorMainWidget(this);
				pSttIecSmvVectorMainWidget->m_bMUTestMode = TRUE;
				pCurrWidget = pSttIecSmvVectorMainWidget;
			}
			//SMV 序分量
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_Sequence)
			{
				QSttIecSmvSequenceMainWidget *pSequence = new QSttIecSmvSequenceMainWidget(this);
				pSequence->m_bMUTestMode = TRUE;
				pCurrWidget = pSequence;
			}
			//SMV 极性分析
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_Polar)
			{
				QSttIecSmvMeterAxisWidget *pMeterAxis = new QSttIecSmvMeterAxisWidget(this);
				pMeterAxis->m_bMUTestMode = TRUE;
				pCurrWidget = pMeterAxis;
			}
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_PkgAnalyze)
			{
				CSttIecSmvGrid_PkgAnalyze *pPkgAnalyze = new CSttIecSmvGrid_PkgAnalyze(this);
				pPkgAnalyze->setFont(*g_pSttGlobalFont);
				pPkgAnalyze->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pPkgAnalyze->InitGrid();
				pPkgAnalyze->m_bMUTestMode = TRUE;
				pCurrWidget = pPkgAnalyze;
			}//首周波
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_MUFirstCycleTest)
			{
 				m_pSttFirstCwWidget = new QSttMUTestFirstCwWidget(this);
 				pCurrWidget = m_pSttFirstCwWidget;
			}
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_FT3_RT)
			{
//				g_oCapAnalysisConfig.FT3_RT();
				CSttIecFT3Grid_RT *pGrid = new CSttIecFT3Grid_RT(this);
				pGrid->setFont(*g_pSttGlobalFont);
				pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->InitGrid();
				pCurrWidget = pGrid;
			}
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_FT3_OriginalMsg)
			{
//				g_oCapAnalysisConfig.FT3_OriginalMsg();
				CSttIecFT3OriginalMsgWidget *pWidget = new CSttIecFT3OriginalMsgWidget(this);
				pCurrWidget = pWidget;
			}
			else if (pDataTypeValue->m_strID == IECRCD_FUNC_Smv_HarmAnalyze) //chenling 2024.5.29 谐波分析
			{
				CSttIecSmvGrid_HarmAnalyze *pGrid = new CSttIecSmvGrid_HarmAnalyze(this);
				pGrid->setFont(*g_pSttGlobalFont);
				pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
				pGrid->InitGrid();
				pGrid->m_bMUTestMode = TRUE;
				pCurrWidget = pGrid;
			}

			m_pSttRecordCBTabWidget->addTab(pCurrWidget,pDataTypeValue->m_strName);
		}
	}
	//2024-10-28 wuxy 标签显示不全
	m_pSttRecordCBTabWidget->setTabPosition(QTabWidget::North);
}

void QSttMUTestRecordCbWidget::InitConnects()
{
	connect(m_pSysSetBtn, SIGNAL(clicked()), this, SLOT(slot_SysSetBtnClicked()));
	connect(m_pPrevPageBtn, SIGNAL(clicked()), this, SLOT(slot_PrevPageBtnClicked()));
	connect(m_pNextPageBtn, SIGNAL(clicked()), this, SLOT(slot_NextPageBtnClicked()));
	connect(m_pSttRecordCBTabWidget,  SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
	connect(this, SIGNAL(sig_UpdateSVDatasetsPowerVector()), this, SLOT(slot_UpdateSVDatasetsPowerVector()));
}

void QSttMUTestRecordCbWidget::ShowDelayTimeUI(bool bShow,bool bIsADMUTest)
{
	m_pDelayChValue_Label->setVisible(bShow);
	m_pDelayChValue_Edit->setVisible(bShow);

	m_pSampFreqEdit->setVisible(bShow);
	m_pOutputRateEdit->setVisible(bShow);
	m_pSampFreqLabel->setVisible(bShow);
	m_pOutputRateLabel->setVisible(bShow);

	if (bIsADMUTest)
	{
		bShow = false;
	}

	m_pRealDelayValue_Label->setVisible(bShow);
	m_pRealDelayValue_Edit->setVisible(bShow);
	m_pDelayValueError_Label->setVisible(bShow);
	m_pDelayValueError_Edit->setVisible(bShow);
}

//////////////////////////////////////////////////////////////////////////
//CSttWndAssistInterface
//查找窗口，保留用 找到返回窗口,      否则返回NULL
CSttWndAssistInterface* QSttMUTestRecordCbWidget::ast_FindWnd(const CString &strWndID)
{

	return NULL;
}

//功能执行接口
bool QSttMUTestRecordCbWidget::ast_ExecCmd(const CString &strCmdID,const CString &strParas)
{

	return false;
}

bool QSttMUTestRecordCbWidget::ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID)
{

	return false;
}

bool QSttMUTestRecordCbWidget::ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile)
{

	return false;
}

void QSttMUTestRecordCbWidget::UpdateFirstCirclePlot(long nChSetModifyType)
{
	if (m_pSttFirstCwWidget != NULL)
	{
		m_pSttFirstCwWidget->updatePlots(nChSetModifyType);
	}
}

//////////////////////////////////////////////////////////////////////////

void QSttMUTestRecordCbWidget::SetIecRecordCbFont()
{
	m_pSttRecordCBTabWidget->setFont(*g_pSttGlobalFont);
	m_pPrevPageBtn->setFont(*g_pSttGlobalFont);
	m_pNextPageBtn->setFont(*g_pSttGlobalFont);
	m_pSysSetBtn->setFont(*g_pSttGlobalFont);

	m_pDelayChValue_Label->setFont(*g_pSttGlobalFont);
	m_pDelayChValue_Edit->setFont(*g_pSttGlobalFont);
	m_pRealDelayValue_Label->setFont(*g_pSttGlobalFont);
	m_pRealDelayValue_Edit->setFont(*g_pSttGlobalFont);
	m_pDelayValueError_Label->setFont(*g_pSttGlobalFont);
	m_pDelayValueError_Edit->setFont(*g_pSttGlobalFont);

	m_pSampFreqEdit->setFont(*g_pSttGlobalFont);
	m_pOutputRateEdit->setFont(*g_pSttGlobalFont);
	m_pSampFreqLabel->setFont(*g_pSttGlobalFont);
	m_pOutputRateLabel->setFont(*g_pSttGlobalFont);


	//2024-6-1 wuxinyi 字体修改
#ifdef 	_PSX_QT_LINUX_
	QFont newFont= m_pSampFreqEdit->font();
    newFont.setPixelSize(12);
	// 设置新字体
	m_pDelayChValue_Edit->setFont(newFont);
	m_pRealDelayValue_Edit->setFont(newFont);
	m_pDelayValueError_Edit->setFont(newFont);
	m_pOutputRateEdit->setFont(newFont);
	m_pSampFreqEdit->setFont(newFont);

	// 还原控件的推荐大小
	m_pDelayChValue_Edit->setFixedHeight(30);
	m_pRealDelayValue_Edit->setFixedHeight(30);
	m_pDelayValueError_Edit->setFixedHeight(30);
	m_pOutputRateEdit->setFixedHeight(30);
	m_pSampFreqEdit->setFixedHeight(30);
#endif

}

void QSttMUTestRecordCbWidget::HideDelayErrUI()
{
	m_pRealDelayValue_Label->setVisible(FALSE);
	m_pRealDelayValue_Edit->setVisible(FALSE);
	m_pDelayValueError_Label->setVisible(FALSE);
	m_pDelayValueError_Edit->setVisible(FALSE);
}


void QSttMUTestRecordCbWidget::slot_currentChangedTabWidget(int nCurrIndex)
{
	OnCurrFuncChanged(nCurrIndex);
}

void QSttMUTestRecordCbWidget::OnCurrFuncChanged(long nIndex)
{
	if (nIndex < 0)
	{
		nIndex = m_pSttRecordCBTabWidget->currentIndex();

		if (nIndex<0)
		{
			nIndex = 0;
		}
	}

	//2024-10-21 wuxinyi 修改m_pDataType_SttIecRcdMUFuncs为空中断问题
	if (m_pDataType_SttIecRcdMUFuncs == NULL)
	{
		return;
	}

	CDataTypeValue *pValue = (CDataTypeValue*)m_pDataType_SttIecRcdMUFuncs->GetAtIndex(nIndex);
	m_strIecRcdFuncID = pValue->m_strID;
	ExecIecFunc();
}

void QSttMUTestRecordCbWidget::UpdateSVDatasetsPowerVector()
{
	emit sig_UpdateSVDatasetsPowerVector();
}

void QSttMUTestRecordCbWidget::slot_SysSetBtnClicked()
{
	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->Config();
	}

//调试使用,在Socket方式下,存储压缩报文
// 
// 	if (CSttRcdSocketBase::IsWriteAt02dRcdFileWrite())
// 	{
// 		CSttRcdSocketBase::CloseAt02dRcdFileWrite();
// 	} 
// 	else
// 	{
// 		CString strFile;
// 		SYSTEMTIME tmSys;
// 		GetLocalTime(&tmSys);
// 		strFile = _P_GetLibraryPath();
// 		strFile.AppendFormat(_T("Test%d_%d_%d_%d_%d.at02dz"), tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
// 		CSttRcdSocketBase::CreateAt02dRcdFileWrite(strFile);
// 	}
}

void QSttMUTestRecordCbWidget::BtnBack()
{
// 	if (m_pSVDelayData != NULL)
// 	{
// 		disconnect(this, SIGNAL(sig_UpdateMUTimeAccurRlt(CDvmData*)), g_theTestCntrFrame, SLOT(slot_UpdateMUTimeAccurRlt(CDvmData*)));
// 		m_pSVDelayData = NULL;
// 	}

// 	if (m_pSttFirstCwWidget != NULL)
// 	{
// 		m_pSttFirstCwWidget->updatePlots();
// 	}

	if (m_pSttIecSmvWaveWidget != NULL)
	{
		m_pSttIecSmvWaveWidget->m_pCapDevice = NULL;
	}

	g_bSmartCap_RecordNow = FALSE;  //2022-5-3  lijunqing stop record

	Ats_IecRecord_Stop();
	m_oTimerIecRcdUpdate.stop();

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
#ifdef _XSmartCap_use_SttRcdSocket_
	g_theXSmartCapMngr->StopCap();
	pXSttCap_61850->DisConnectServer();
#endif

// 	CString strFile;
// 	strFile = _P_GetLibraryPath();
// 	//	CreateAllDirectories(strFile)
// 	strFile += _T("SttIecRecordDetectDvm002.xml");
// 	pXSttCap_61850->m_pDvmDevice->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	g_theSttIecRecordMainWidget->ShowIecDetectWindow();

	if ( m_pSttIecRcdFuncInterface != NULL )
	{
		m_pSttIecRcdFuncInterface->IecRcdFunc(NULL);
	}
}

// void QSttMUTestRecordCbWidget::Connect_UpdateMUTimeAccurRlt(BOOL bCoonect)
// {
// 	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
// 
// 	if ((m_pSVDelayData != NULL)&&(pXSttCap_61850!= NULL))
// 	{
// 		if (bCoonect)
// 		{
// 			connect(this, SIGNAL(sig_UpdateMUTimeAccurRlt(CDvmData*)), g_theTestCntrFrame, SLOT(slot_UpdateMUTimeAccurRlt(CDvmData*)));
// 		}
// 	}
// }

void QSttMUTestRecordCbWidget::Update_IecRcdTimer()
{
	float fNewTime = STT_IEC_RECORD_TIMER_DEFAULT_VALUE;

	if (g_nUseCustomMUTestRpt)
	{
		fNewTime = g_fMUTestTimeEach;
	}

	if (fabs(fNewTime-m_fIecRcdTimer)>0.001)
	{
		m_fIecRcdTimer = fNewTime;
		m_oTimerIecRcdUpdate.stop();
		m_oTimerIecRcdUpdate.start(m_fIecRcdTimer*1000);
	}
}

void QSttMUTestRecordCbWidget::SetCapDevice(CCapDeviceBase *pCapDevice)
{
	if (m_pCurrCapDevice != NULL)
	{
		if (pCapDevice->IsSameType(m_pCurrCapDevice->m_nType)
			&& pCapDevice->m_dwAppID == m_pCurrCapDevice->m_dwAppID)
		{
			return;
		}
	}

	if (pCapDevice != NULL)
	{
		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			HideDelayErrUI();
		}
	}

	//表示为设置CapDevice状态，此时如果因为功能列表框更新带来的变化，不做处理
	m_bInSetCapDevice = TRUE;
	m_pCurrCapDevice = pCapDevice; 
	OnCurrFuncChanged(-1);
	m_bInSetCapDevice = FALSE;
}

void QSttMUTestRecordCbWidget::SetSelectedCbs(CExBaseList *pSelectedCbs)
{
	m_pSelectedCbs = pSelectedCbs;

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CCapDeviceBase *pCapDevice = NULL;

	if (pXSttCap_61850 != NULL)
	{
		pCapDevice = pXSttCap_61850->GetMUTestCapDevice();
	}

	SetCapDevice(pCapDevice);
}

void QSttMUTestRecordCbWidget::Ats_IecRecord(BOOL bIsFromIecfgFile)
{
	m_oTimerIecRcdUpdate.stop();
	RecordCapDevice();

    CDataGroup oMacroParas;
    g_theXSmartCapMngr->GetSttCapParas(&oMacroParas, g_pSttIecRecordDetectWidget->m_bViewSmv
		, g_pSttIecRecordDetectWidget->m_bViewGoose,g_pSttIecRecordDetectWidget->m_bViewFT3);
    oMacroParas.AddNewData(_T("Enable"), (long)1);
    oMacroParas.AddNewData(_T("Mode"), (long)1);

	if (CXCapPkgBufferMngrInterface::Is_XSmartCapDebugHead())
	{//如果是调试报文头的模式，则下发参数“DebugHead”
		oMacroParas.AddNewData(_T("DebugHead"), (long)1);  //调试报文头
	}

	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
    pNative->Ats_IecRecord(&oMacroParas);

	//for debug====  400 修改刷新频率
    m_oTimerIecRcdUpdate.start(m_fIecRcdTimer*1000);
}

void QSttMUTestRecordCbWidget::Ats_IecRecord_Stop()
{
    CDataGroup oMacroParas;
    oMacroParas.AddNewData(_T("Enable"), (long)0);
    CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
    pNative->Ats_IecRecord(&oMacroParas);
}

void QSttMUTestRecordCbWidget::InitIecRecordCb(const CString &strIecFunc)
{
	m_strIecRcdFuncID = strIecFunc;
	m_pCurrCapDevice = NULL;
}

void QSttMUTestRecordCbWidget::UpdateCapDevice(CCapDeviceBase *pCapDevice)
{//更新装置：如果当前装置是需要更新的装置，则更新
	//2022-6-11  lijunqing 此函数设计的初期是因为探测的时候没有返回通道数
	//所以要动态增加到RecordDevice中，新版本返回了通道数，此函数仅仅不做处理

	//20022-6-11 lijunqing 后续是否考虑由于通道数不匹配的问题更新界面，在做修改
	//????????????????????????????????????????
}

void QSttMUTestRecordCbWidget::RecordCapDevice(CCapDeviceBase *pCapDevice)
{
	if (m_pCurrCapDevice != NULL)
	{
		if (m_pCurrCapDevice != pCapDevice)
		{
			//停止录波m_pCurrCapDevice
		}
	}

	m_pCurrCapDevice = pCapDevice;
	g_theXSmartCapMngr->RecordDevice(pCapDevice);
	
	//DvmDevice初始化：如果没有关联的设备，创建设备数据模型dsSv
	g_theXSmartCapMngr->InitDvmDevice(pCapDevice);
	g_theXSmartCapMngr->IecAnalysis_AddDatasets();

	g_theXSmartCapMngr->m_pX61850Cap->BeginRecord();
	g_theXSmartCapMngr->m_pX61850Cap->Init_SV_Channels();
	g_theXSmartCapMngr->m_pX61850Cap->Init_GS_Channels();

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->IecRcdFunc(pCapDevice);
	}
}

void QSttMUTestRecordCbWidget::RecordCapDevice()
{
	g_theXSmartCapMngr->m_pX61850Cap->RecordDevices();

	//关联DvmDevice和RecordTest
	g_theXSmartCapMngr->m_pX61850Cap->BeginRecord();
	g_theXSmartCapMngr->m_pX61850Cap->Init_SV_Channels();
	g_theXSmartCapMngr->m_pX61850Cap->Init_GS_Channels();

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->IecRcdFunc(m_pCurrCapDevice);
	}
}

void QSttMUTestRecordCbWidget::ExecIecFunc(const CString &strIecfFunc)
{
	m_strIecRcdFuncID = strIecfFunc;
	ExecIecFunc();
}

void QSttMUTestRecordCbWidget::ExecIecFunc_SetCapAnalysisConfig()
{
	CString strSysSetString;
	strSysSetString = /*_T("接收通道")*/g_sLangTxt_Gradient_RecvChannnel; //lcq
	QWidget *pCurrWidget = m_pSttRecordCBTabWidget->currentWidget();
	g_nRecordTestCalState = 0;
	//SMV   通道监视
	if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_ChQualitySpy)
	{
		g_oCapAnalysisConfig.Smv_ChQualitySpy();
		CSttIecSmvGrid_ChQualitySpy *pGrid = (CSttIecSmvGrid_ChQualitySpy*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV   通道属性
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_ChAttr)
	{
		g_oCapAnalysisConfig.Smv_EffecValue();
		CSttIecSmvGrid_ChAttr *pGrid = (CSttIecSmvGrid_ChAttr*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV  有效值
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_EffecValue)
	{
		g_oCapAnalysisConfig.Smv_EffecValue();
		CSttIecSmvGrid_EffecValue *pGrid = (CSttIecSmvGrid_EffecValue*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV   波形分析
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Wave)
	{
		g_oCapAnalysisConfig.Smv_Wave();
		QSttIecSmvWaveWidget *pChildWidget = (QSttIecSmvWaveWidget*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV   功率
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Power)
	{
		g_oCapAnalysisConfig.Smv_Power();
		CSttIecSmvGrid_Power *pChildWidget = (CSttIecSmvGrid_Power*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV   谐波
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Harm)
	{
		g_oCapAnalysisConfig.Smv_Harm();
		CSttIecSmvGrid_Harm *pChildWidget = (CSttIecSmvGrid_Harm*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV   报文统计
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_PkgError)
	{
		strSysSetString = tr("清空");
		xlang_GetLangStrByFile(strSysSetString,"Native_Clear");
		g_oCapAnalysisConfig.Smv_PkgError();
		g_nRecordTestCalState = 1;
		QSttIecSmvPkgErrorWidget *pChildWidget = (QSttIecSmvPkgErrorWidget*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV   双AD
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_AD)
	{
		g_oCapAnalysisConfig.Smv_AD();
		CSttIecSmvGrid_AD *pChildWidget = (CSttIecSmvGrid_AD*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV   MU精确度
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUAccuracy)
	{
		g_oCapAnalysisConfig.Smv_MUAccuracy();
		QSttIecMUAccuracyWidget *pChildWidget = (QSttIecMUAccuracyWidget*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV   MU误差统计
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUErrorStatistics)
	{
		xlang_GetLangStrByFile(strSysSetString,"Native_Clear");
		g_oCapAnalysisConfig.Smv_MUErrorStatistics();
		CSttIecSmvGrid_MUErrorStatis *pChildWidget = (CSttIecSmvGrid_MUErrorStatis*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV   MU时间精度
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUTimingAccur)
	{
		xlang_GetLangStrByFile(strSysSetString,"Native_Clear");
		g_oCapAnalysisConfig.Smv_MUErrorStatistics();
		QSttIecMUTimeWidget *pChildWidget = (QSttIecMUTimeWidget*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV 矢量图
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Vector)
	{
		g_oCapAnalysisConfig.Smv_Vector();
		QSttIecSmvVectorMainWidget *pChildWidget = (QSttIecSmvVectorMainWidget*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV 序分量
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Sequence)
	{
		g_oCapAnalysisConfig.Smv_Vector();
		QSttIecSmvSequenceMainWidget *pChildWidget = (QSttIecSmvSequenceMainWidget*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	//SMV 极性分析
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Polar)
	{
		g_oCapAnalysisConfig.Smv_Vector();
		QSttIecSmvMeterAxisWidget *pChildWidget = (QSttIecSmvMeterAxisWidget*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_PkgAnalyze)
	{
		g_oCapAnalysisConfig.Smv_PkgAnalyze();
		CSttIecSmvGrid_PkgAnalyze *pChildWidget = (CSttIecSmvGrid_PkgAnalyze*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUFirstCycleTest)//首周波
	{
		QSttMUTestFirstCwWidget *pChildWidget = (QSttMUTestFirstCwWidget*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pChildWidget;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_FT3_RT)
	{
		g_oCapAnalysisConfig.FT3_RT();
		CSttIecFT3Grid_RT *pGrid = (CSttIecFT3Grid_RT*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pGrid;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_FT3_OriginalMsg)
	{
		g_oCapAnalysisConfig.FT3_OriginalMsg();
		CSttIecFT3OriginalMsgWidget *pWidget = (CSttIecFT3OriginalMsgWidget*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pWidget;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_HarmAnalyze)//chenling 2024.5.29 谐波分析
	{
		g_oCapAnalysisConfig.Smv_Harm();
		CSttIecSmvGrid_HarmAnalyze *pGrid =(CSttIecSmvGrid_HarmAnalyze*)pCurrWidget;
		m_pSttIecRcdFuncInterface = pGrid;
	}

	g_oCapAnalysisConfig.m_bMU_Test = true;
	g_oCapAnalysisConfig.m_bAnalysisData_PhaseDelt = true;
	g_oCapAnalysisConfig.m_bAnalysisData_Complex = true;
	m_pSysSetBtn->setText(strSysSetString);
}

void QSttMUTestRecordCbWidget::ExecIecFunc()
{
	CDataTypeValue *pDataTypeValue = (CDataTypeValue*)m_pDataType_SttIecRcdMUFuncs->FindByID(m_strIecRcdFuncID);

	if (pDataTypeValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("合并单元测试功能ID()在配置文件中未查找到.")*/g_sLangTxt_Gradient_MergeUint.GetString(),m_strIecRcdFuncID.GetString());
	}
	else
	{
		long nCurrIndex = m_pDataType_SttIecRcdMUFuncs->FindIndex(pDataTypeValue);

		if (nCurrIndex != m_pSttRecordCBTabWidget->currentIndex())
		{
			disconnect(m_pSttRecordCBTabWidget,  SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
			m_pSttRecordCBTabWidget->setCurrentIndex(nCurrIndex);
			connect(m_pSttRecordCBTabWidget,  SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
		}
	}

	ExecIecFunc_SetCapAnalysisConfig();
	if(g_pTheSttTestApp->GetCurrTestMacroUI() == STT_ORG_MACRO_MUAccurAutoTest)
	{
		ShowDelayTimeUI(m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUAccuracy,m_pDataType_SttIecRcdMUFuncs->m_strID == "SttIecRcdADMUAutoFuncs_Tab");
	}
	else
	{
	ShowDelayTimeUI(m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUAccuracy,m_pDataType_SttIecRcdMUFuncs->m_strID == "SttIecRcdADMUFuncs_Tab");
	}

	if (m_pSttIecRcdFuncInterface)
	{
		if (m_pSttIecRcdFuncInterface->NeedNextAndPrev())
		{
			m_pNextPageBtn->show();
			m_pPrevPageBtn->show();
		}
		else
		{
			m_pNextPageBtn->hide();
			m_pPrevPageBtn->hide();
		}

		if (m_pSttIecRcdFuncInterface->NeedConfig())
		{
			m_pSysSetBtn->show();
		}
		else
		{
			m_pSysSetBtn->hide();
		}

		if (m_pSttIecRcdFuncInterface->m_pIecRcdFuncWidget == m_pSttIecSmvWaveWidget)
		{
			if (m_pSttIecRcdFuncInterface->m_pCapDevice != m_pCurrCapDevice)
			{
				m_pSttIecSmvWaveWidget->ReleaseUI();
			}
			else
			{
				m_pSttIecSmvWaveWidget->m_bInitTimeAxis = TRUE;
			}
		} 

		m_pSttIecRcdFuncInterface->IecRcdFunc(m_pCurrCapDevice);
		
	} 
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前选择测试功能异常(%s),导致m_pSttIecRcdFuncInterface==NULL."*/g_sLangTxt_Gradient_NAbnormalRes.GetString()
			,m_strIecRcdFuncID.GetString());
	}
}

void QSttMUTestRecordCbWidget::slot_Timer_IecRcdUpdate()
{
	if ((m_pSttIecRcdFuncInterface == NULL)||(g_theXSmartCapMngr == NULL)
		/*||(!g_bSmartCap_RecordNow)*/ || m_bStopTimerUpdate)//zhouhj 2024.4.10 退出录波后,定时器不再刷新
	{
		return;
	}

	CAutoSimpleLock oLock(m_oFuncCriticSection);

	m_pSttIecRcdFuncInterface->IecRcdFuncUpdate(m_pCurrCapDevice);
	IecRcdFuncUpdate_MUDelayTimes(m_pCurrCapDevice);

	if (m_bMUTestMode && (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Wave))//合并单元测试,波形图界面,也更新计算
	{
		CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
		pXSttCap_61850->UpdateDvmDeviceDatas();
	}

	if ((m_pSVDelayData != NULL)&&(g_oCapAnalysisConfig.m_bMU_Test))
	{
		CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
		pXSttCap_61850->CalMuTimeTestRlt_NoPPS();
//		emit sig_UpdateMUTimeAccurRlt(m_pSVDelayData);
	}
}

void QSttMUTestRecordCbWidget::IecRcdFuncUpdate_MUDelayTimes(CCapDeviceBase *pCapDevice)
{
	if (m_pSVDelayData != NULL)
	{
		CString strID,strTmp;
		strID = m_pSVDelayData->m_strID + STT_MUTEST_DL_ChDelay/*Format("%s$ChDelay",.GetString())*/;
		CDvmValue *pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);
		double dDelayError = 0.0f,dChDelay = 0.0f,dCurrDelay = 0.0f;

		if (pCurrValue != NULL)
		{
			dChDelay = CString_To_double(pCurrValue->m_strValue);
			strTmp.Format(_T("%.03lf "),dChDelay);
			CString strUnit = _T("μs");
			strTmp += strUnit;
			m_pDelayChValue_Edit->setText(strTmp);
		}

		strID = m_pSVDelayData->m_strID + STT_MUTEST_DL_RealDelay /*.Format("%s$RealDelay",m_pSVDelayData->m_strID.GetString())*/;
		pCurrValue = (CDvmValue*)m_pSVDelayData->FindByID(strID);

		if (pCurrValue != NULL)
		{
			dCurrDelay = CString_To_double(pCurrValue->m_strValue);
			strTmp.Format(_T("%.03lf "),dCurrDelay);
			CString strUnit = _T("μs");
			strTmp += strUnit;
			m_pRealDelayValue_Edit->setText(strTmp);
		}

		dDelayError = dCurrDelay - dChDelay;
		strTmp.Format(_T("%.03lf "),dDelayError);
		CString strUnit = _T("μs");
		strTmp += strUnit;//2024-09-24 zhouyangyong 修改单位乱码
		m_pDelayValueError_Edit->setText(strTmp);
	}

	//刷新采样频率/输出速率
	UpdateSampFreOutputRateData(pCapDevice);
}

void QSttMUTestRecordCbWidget::slot_PrevPageBtnClicked()
{
	CAutoSimpleLock oLock(m_oFuncCriticSection);
	m_pSttIecRcdFuncInterface->PrevPage();
}

void QSttMUTestRecordCbWidget::slot_NextPageBtnClicked()
{
	CAutoSimpleLock oLock(m_oFuncCriticSection);
	m_pSttIecRcdFuncInterface->NextPage();
}

void QSttMUTestRecordCbWidget::slot_UpdateSVDatasetsPowerVector()
{
	m_oTimerIecRcdUpdate.stop();
	g_theXSmartCapMngr->m_pX61850Cap->IecAnalysis_UpdateSvDatasetsPowerVector();
	m_oTimerIecRcdUpdate.start(m_fIecRcdTimer*1000/*500*/);
}

void QSttMUTestRecordCbWidget::UpdateSampFreOutputRateData( CCapDeviceBase *pCapDevice )
{
	if (pCapDevice == NULL)
	{
		return;
	}
	CString strTextTmp;
	//采样频率
	CCapDevice6044 *pDevice6044 = (CCapDevice6044*)pCapDevice;
	strTextTmp.Format(_T("%ld Hz"),pDevice6044->m_nSmpRate);
	m_pSampFreqEdit->setText(strTextTmp);

	//输出速率
	strTextTmp.Format(_T("%.01lf Mbps"),pDevice6044->m_dBaudRate);
	m_pOutputRateEdit->setText(strTextTmp);
}
