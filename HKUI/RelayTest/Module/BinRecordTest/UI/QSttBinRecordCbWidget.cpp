#include "QSttBinRecordCbWidget.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../RecordTest/UI/SttIecSmvGrid_EffecValue.h"
#include "../../../../Module/SmartCap/XSttCap_61850.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "QSttBinRecordMainDlg.h"
#include "../../RecordTest/UI/SttIecSmvWaveMainWidget.h"
#include "../../RecordTest/UI/SttIecSmvWidget_Harm.h"
#include "../UI/SttBinRecord_RT.h"
#include "../../RecordTest/UI/SttIecSmvSequenceWidget.h"
#include "../../RecordTest/UI/SttIecSmvGrid_Power.h"
#include "../../RecordTest/UI/SttIecSmvVectorWidget.h"
#include "SttBinRecordDefine.h"
QSttBinRecordCbWidget *g_pSttBinRecordCbWidget = NULL;
QSttBinRecordCbWidget::QSttBinRecordCbWidget(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	g_pSttBinRecordCbWidget = this;
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_cmbCb = new QScrollComboBox;
	m_cmbCb->setObjectName("m_cmbCb");
	m_cmbCb->SetBoxSize(20, 30);
	connect(m_cmbCb, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CbCurrentIndexChanged(int)));
	ui.m_HLayOut_Btns->insertWidget(STT_BINRECORD_ID_NONE, m_cmbCb);

	m_cmbFunc = new QScrollComboBox;
	m_cmbFunc->setObjectName("m_cmbFunc");
	m_cmbFunc->SetBoxSize(20, 30);
	m_cmbFunc->setMaxVisibleItems(14);
	connect(m_cmbFunc, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_FuncCurrentIndexChanged(int)));
	ui.m_HLayOut_Btns->insertWidget(STT_BINRECORD_ID_NTHREE, m_cmbFunc);

	m_pCurrCapDevice = NULL;
	m_pSttIecRcdFuncInterface = NULL;

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SttBinRcdFuncs.xml");
	m_oBinRcdFucsDataType.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	m_cmbFunc->setCurrentIndex(STT_BINRECORD_ID_NZERO);
	UpDataShowPrimState();

	connect(ui.m_RBtn_ShowPrim, SIGNAL(clicked()), this, SLOT(slot_RBtn_ShowPrim()));
	connect(&m_oTimerBinRcdUpdate, SIGNAL(timeout()), this, SLOT(slot_Timer_BinRcdUpdate()));
	connect(ui.m_Btn_Back, SIGNAL(clicked()), this, SLOT(on_m_btnBack_clicked()));
}

QSttBinRecordCbWidget::~QSttBinRecordCbWidget()
{
	m_oTimerBinRcdUpdate.stop();
	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->Release();
		m_pSttIecRcdFuncInterface = NULL;
	}
	if (m_cmbFunc)
	{
		delete m_cmbFunc;
		m_cmbFunc = NULL;
	}
	if (m_cmbCb)
	{
		delete m_cmbCb;
		m_cmbCb = NULL;
	}
}

void QSttBinRecordCbWidget::InitFuncTypeComboBox()
{
	ex_InsertChildreComboBox(&m_oBinRcdFucsDataType, m_cmbFunc);
}

void QSttBinRecordCbWidget::OnCurrFuncChanged(long nIndex)
{
	if (nIndex < STT_BINRECORD_ID_NZERO)
	{
		nIndex = m_cmbFunc->currentIndex();
	}

	CDataTypeValue *pValue = (CDataTypeValue*)m_oBinRcdFucsDataType.GetAtIndex(nIndex);
	m_strIecRcdFuncID = pValue->m_strID;

	ExecIecFunc();
}

void QSttBinRecordCbWidget::ExecIecFunc(const CString &strIecfFunc)
{
	m_strIecRcdFuncID = strIecfFunc;
	ExecIecFunc();
}

void QSttBinRecordCbWidget::ExecIecFunc()
{
	CSttIecRcdFuncInterface *pForDelete = NULL;

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		if (m_pSttIecRcdFuncInterface->m_strIecRcdFuncID == m_strIecRcdFuncID)
		{
			m_pSttIecRcdFuncInterface->IecRcdFunc(m_pCurrCapDevice);
			return;
		}

		pForDelete = m_pSttIecRcdFuncInterface;
	}
	ExecIecFunc_Create();

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->m_strIecRcdFuncID = m_strIecRcdFuncID;
		ui.verticalLayout->insertWidget(STT_BINRECORD_ID_NZERO, m_pSttIecRcdFuncInterface->m_pIecRcdFuncWidget);

		m_pSttIecRcdFuncInterface->IecRcdFunc(m_pCurrCapDevice);
	}

	if (pForDelete != NULL)
	{
		pForDelete->Release();
	}
}

void QSttBinRecordCbWidget::ExecIecFunc_Create()
{
	//有效值
	if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_EffecValue)
	{
		g_oCapAnalysisConfig.Smv_EffecValue();
		CSttBinRecord_RT *pGrid = new CSttBinRecord_RT(this);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Wave)
	{
		g_oCapAnalysisConfig.Smv_Wave();
		QSttIecSmvWaveMainWidget*pWave = new QSttIecSmvWaveMainWidget(this);
		m_pSttIecRcdFuncInterface = pWave;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Harm)
	{
		g_oCapAnalysisConfig.Smv_Harm();
		CSttIecSmvWidget_Harm *pSttIecSmvWidget_Harm = new CSttIecSmvWidget_Harm(this);
		pSttIecSmvWidget_Harm->HarmFunc_Create(IECRCD_FUNC_Smv_Harm_ValidValue);
		m_pSttIecRcdFuncInterface = pSttIecSmvWidget_Harm->m_pSttIecRcdFuncInterface;
		m_pSttIecSmvWidget_Harm = pSttIecSmvWidget_Harm;
//		m_cmbHarmDisplay->setCurrentIndex(0);
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Power)
	{
		g_oCapAnalysisConfig.Smv_Power();
		CSttIecSmvGrid_Power *pGrid = new CSttIecSmvGrid_Power(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Vector)
	{
		g_oCapAnalysisConfig.Smv_Vector();
		QSttIecSmvVectorMainWidget *pSequence = new QSttIecSmvVectorMainWidget(this);
		m_pSttIecRcdFuncInterface = pSequence;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Sequence)
	{
		g_oCapAnalysisConfig.Smv_Vector();
		QSttIecSmvSequenceMainWidget *pSequence = new QSttIecSmvSequenceMainWidget(this);
		m_pSttIecRcdFuncInterface = pSequence;
	}

}

void QSttBinRecordCbWidget::SetCapDevice(CCapDeviceBase *pCapDevice)
{
	m_pCurrCapDevice = pCapDevice;
	InitFuncTypeComboBox();
}

void QSttBinRecordCbWidget::SetCapDeviceAll(CCapDeviceMngr *pCapDeviceAll)
{
	m_pCapDeviceAll = pCapDeviceAll;
	ex_InsertChildreComboBox(m_pCapDeviceAll, m_cmbCb);
	m_cmbCb->setCurrentIndex(STT_BINRECORD_ID_NZERO);
}

void QSttBinRecordCbWidget::RecordCapDevice(CCapDeviceBase *pCapDevice)
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

	//关联DvmDevice和RecordTest
	//CCapDeviceChRecordMngr::InitRecordTest()
	g_theXSmartCapMngr->m_pX61850Cap->BeginRecord();
	g_theXSmartCapMngr->m_pX61850Cap->Init_SV_Channels();
	g_theXSmartCapMngr->m_pX61850Cap->Init_GS_Channels();

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->IecRcdFunc(pCapDevice);
	}
}

void QSttBinRecordCbWidget::RecordCapDevice()
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

void QSttBinRecordCbWidget::BtnBack()
{
	g_bSmartCap_RecordNow = FALSE;
	m_oTimerBinRcdUpdate.stop();
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	g_theXSmartCapMngr->StopCap();
	pXSttCap_61850->ClearPara();
	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->Release();
		m_pSttIecRcdFuncInterface = NULL;
	}
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("SttBinRecordDvm001.xml");
	pXSttCap_61850->m_pDvmDevice->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttBinRecordCbWidget::UpDataShowPrimState()
{
	if (g_oCapAnalysisConfig.m_nShowPrimaryValue == STT_BINRECORD_ID_NZERO)
	{
		ui.m_RBtn_ShowPrim->setChecked(true);
	}
	else
	{
		ui.m_RBtn_ShowPrim->setChecked(false);
	}
	
}

void QSttBinRecordCbWidget::slot_CbCurrentIndexChanged(int index)
{
	if (index < STT_BINRECORD_ID_NZERO)
	{
		return;
	}

	if (m_cmbCb->IsScrolling())
	{
		return;
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDeviceAll->GetAtIndex(index);
	SetCapDevice(pCapDevice);
}

void QSttBinRecordCbWidget::slot_FuncCurrentIndexChanged(int index)
{
	if (index < STT_BINRECORD_ID_NZERO)
	{
		return;
	}

	if (m_cmbFunc->IsScrolling())
	{
		return;
	}

// 	if (m_bInSetCapDevice)
// 	{//当处于当前设备更新的时候，更新了Func，不做处理，在SetCapDevice函数中处理
// 		return;
// 	}

	OnCurrFuncChanged(index);
}

void QSttBinRecordCbWidget::slot_CbHarmDisplayIndexChanged(int index)
{
	if (index < STT_BINRECORD_ID_NZERO)
	{
		return;
	}

	if (m_cmbHarmDisplay->IsScrolling())
	{
		return;
	}

	m_pSttIecSmvWidget_Harm->HarmFunc_Create(index);
	m_pSttIecRcdFuncInterface = m_pSttIecSmvWidget_Harm->m_pSttIecRcdFuncInterface;
	ui.verticalLayout->insertWidget(STT_BINRECORD_ID_NZERO, m_pSttIecRcdFuncInterface->m_pIecRcdFuncWidget);
	m_pSttIecRcdFuncInterface->IecRcdFunc(m_pCurrCapDevice);
}

void QSttBinRecordCbWidget::on_m_btnBack_clicked()
{
	BtnBack();
	g_theSttBinRecordMainWidget->ShowBinConfigWindow();
}

void QSttBinRecordCbWidget::slot_Timer_BinRcdUpdate()
{
	if ((m_pSttIecRcdFuncInterface == NULL) || (g_theXSmartCapMngr == NULL) )//退出录波后,定时器不再刷新
	{
		return;
	}

	CAutoSimpleLock oLock(m_oFuncCriticSection);

	m_pSttIecRcdFuncInterface->IecRcdFuncUpdate(m_pCurrCapDevice);
}

void QSttBinRecordCbWidget::slot_RBtn_ShowPrim()
{
	long nState = ui.m_RBtn_ShowPrim->isChecked();
	if (nState)
	{
		g_oCapAnalysisConfig.m_nShowPrimaryValue = STT_BINRECORD_ID_NZERO;
	}
	else
	{
		g_oCapAnalysisConfig.m_nShowPrimaryValue = STT_BINRECORD_ID_NONE;
	}
}
