#include "NGDSmartTestMainWidget.h"
#include "SttNGDSmartTestWin.h"
#include "QSttSelSclFileWidget.h"
#include "..\SmartCap\61850Cap\CapDevice\CapDeviceGoose.h"
extern SttNGDSmartTestWin *g_SttNGDSmartTestWin;

NGDSmartTestMainWidget::NGDSmartTestMainWidget(QWidget *parent)
{
	m_nPage = 1;
	ui.setupUi(this);
	connect(ui.m_BtnPreStep, SIGNAL(clicked()), this, SLOT(slot_On_m_Btn_PreStep_clicked()));
	connect(ui.m_BtnNextStep, SIGNAL(clicked()), this, SLOT(slot_On_m_Btn_NextStep_clicked()));
	connect(&m_oTimerForHeartBeat, SIGNAL(timeout()), this, SLOT(slot_TimerForHeartBeat()));
	m_oChooseSCDWidget.SetSCLStation(&m_oSclStation);
	m_oGooseInCfgWidget.SetSCLStation(&m_oSclStation);
	m_oGooseOutCfgWidget.SetSCLStation(&m_oSclStation);
	m_oChooseDeviceWidget.SetSCLStation(&m_oSclStation);
	ui.m_CentetLayout->addWidget(&m_oChooseSCDWidget);
	ui.m_CentetLayout->addWidget(&m_oIecDetectWidget);
	ui.m_CentetLayout->addWidget(&m_oGooseInCfgWidget);
	ui.m_CentetLayout->addWidget(&m_oGooseOutCfgWidget);
	ui.m_CentetLayout->addWidget(&m_oChooseDeviceWidget);

   	CDataGroup oSttIecCbGOOSE;
   	oSttIecCbGOOSE.AddNewData(XPARA_ID_APPID, _T("0X1004"));
   	oSttIecCbGOOSE.AddNewData(XPARA_ID_Type, XPARA_ID_TYPE_GOOSE);
   	oSttIecCbGOOSE.AddNewData(XPARA_ID_Port, long(1));
   	oSttIecCbGOOSE.AddNewData(XPARA_ID_ChCount, long(25));
     oSttIecCbGOOSE.AddNewData(IEC_PkgAnalyze_ID_GOOSEID, _T("gocb1"));
     oSttIecCbGOOSE.AddNewData(XPARA_ID_DestMac, _T("010CCD1004"));
   
   	CDataGroup oSttIecCbSMV;
   	oSttIecCbSMV.AddNewData(XPARA_ID_APPID, _T("0X4002"));
   	oSttIecCbSMV.AddNewData(XPARA_ID_Type, XPARA_ID_TYPE_SMV92);
   	oSttIecCbSMV.AddNewData(XPARA_ID_Port, long(2));
   	oSttIecCbSMV.AddNewData(XPARA_ID_ChCount, long(29));
    oSttIecCbSMV.AddNewData(IEC_PkgAnalyze_ID_SVID, _T("svcb1"));
    oSttIecCbSMV.AddNewData(XPARA_ID_DestMac, _T("010CCD4002"));
   	m_oX61850CapBase.m_oCapDeviceAll.AddCapDevice(&oSttIecCbGOOSE);
   	m_oX61850CapBase.m_oCapDeviceAll.AddCapDevice(&oSttIecCbSMV);
	InitUI();
}

NGDSmartTestMainWidget::~NGDSmartTestMainWidget()
{
	m_oX61850CapBase.m_oCapDeviceAll.RemoveAll();
}

long NGDSmartTestMainWidget::OnRtData(CSttParas *pParas)
{
	CExBaseObject *pChildObj = NULL;
	POS pos = pParas->GetHeadPosition();
	CDataGroup *pRtDataGroup = NULL;

	while(pos)
	{
		pChildObj = pParas->GetNext(pos);

		if (pChildObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pRtDataGroup = (CDataGroup *)pChildObj;

		if (pRtDataGroup->m_strID == XPARA_ID_IEC_CB)
		{
			On_IecDetect(pRtDataGroup);
			m_oIecDetectWidget.m_pGridIecCb->ShowDatas(&m_oX61850CapBase.m_oCapDeviceAll);
		}
	}

	return 1;
}

void NGDSmartTestMainWidget::InitUI()
{
	m_oChooseSCDWidget.InitCombo();
}

void NGDSmartTestMainWidget::UpdateView()
{
	if (m_strPage[m_nPage] == Process_MainWidget)
	{
		g_SttNGDSmartTestWin->show();
		this->close();
	}
	if (m_strPage[m_nPage] == Process_LoadSCD)
	{
		ui.m_BtnNextStep->setEnabled(m_bLoadSCDFile);
		ui.m_ExTitleLabel->setText(_T("步骤一：导入SCD"));
		m_oIecDetectWidget.hide();
		m_oGooseInCfgWidget.hide();
		m_oChooseDeviceWidget.hide();
		m_oGooseOutCfgWidget.hide();

		m_oChooseSCDWidget.show();
		ui.m_BtnNextStep->setText(_T("下一步"));
	}
	else if (m_strPage[m_nPage] == Process_MUDetect)
	{
		SendIecDetect(TRUE);
		ui.m_ExTitleLabel->setText(_T("步骤二：合并单元探测"));
		m_oGooseInCfgWidget.hide();
		m_oChooseDeviceWidget.hide();
		m_oChooseSCDWidget.hide();
		m_oGooseOutCfgWidget.hide();

		m_oIecDetectWidget.show();
		m_oIecDetectWidget.m_pGridIecCb->m_bViewSmv = TRUE;
		m_oIecDetectWidget.m_pGridIecCb->m_bViewGoose = FALSE;
		m_oIecDetectWidget.m_pGridIecCb->ShowDatas(&m_oX61850CapBase.m_oCapDeviceAll);
		ui.m_BtnNextStep->setText(_T("下一步"));
	}
	else if (m_strPage[m_nPage] == Process_GooseDetect)
	{
		ui.m_ExTitleLabel->setText(_T("步骤三：智能终端探测"));
		m_oGooseInCfgWidget.hide();
		m_oChooseDeviceWidget.hide();
		m_oChooseSCDWidget.hide();
		m_oGooseOutCfgWidget.hide();

		m_oIecDetectWidget.show();
		m_oIecDetectWidget.m_pGridIecCb->m_bViewGoose = TRUE;
		m_oIecDetectWidget.m_pGridIecCb->m_bViewSmv = FALSE;
		m_oIecDetectWidget.m_pGridIecCb->ShowDatas(&m_oX61850CapBase.m_oCapDeviceAll);
 		ui.m_BtnNextStep->setText(_T("下一步"));
	}
	else if (m_strPage[m_nPage] == Process_GooseInCfg)
	{
		ui.m_ExTitleLabel->setText(_T("步骤四：智能终端GOOSE订阅配置"));
		m_oChooseDeviceWidget.hide();
		m_oChooseSCDWidget.hide();
		m_oIecDetectWidget.hide();
		m_oGooseOutCfgWidget.hide();

		m_oGooseInCfgWidget.show();
		ui.m_BtnNextStep->setText(_T("下一步"));
	}
	else if (m_strPage[m_nPage] == Process_GooseOutCfg)
	{
		ui.m_ExTitleLabel->setText(_T("步骤五：智能终端GOOSE发布配置"));
		m_oChooseDeviceWidget.hide();
		m_oChooseSCDWidget.hide();
		m_oIecDetectWidget.hide();
		m_oGooseInCfgWidget.hide();
		
		m_oGooseOutCfgWidget.show();
		if (m_nTestMode == TestMode_CollectExecuteUnit)
		{
			ui.m_BtnNextStep->setText(_T("创建测试"));
		}
		else
		{
			ui.m_BtnNextStep->setText(_T("下一步"));
		}
	}
	else if (m_strPage[m_nPage] == Process_ChooseDev)
	{
		if (m_nTestMode == TestMode_Protector)
		{
			ui.m_ExTitleLabel->setText(_T("步骤二：保护装置选择"));
		}
		else
		{
			ui.m_ExTitleLabel->setText(_T("步骤六：保护装置选择"));
		}
		m_oChooseSCDWidget.hide();
		m_oIecDetectWidget.hide();
		m_oGooseInCfgWidget.hide();
		m_oGooseOutCfgWidget.hide();

		m_oChooseDeviceWidget.show();
		m_oChooseDeviceWidget.UpdateIEDGrids();
		ui.m_BtnNextStep->setText(_T("创建测试"));
	}
}
CString NGDSmartTestMainWidget::GetSmartTestModFile()
{
	CString strSmartTestModFile = _T("");
	m_oChooseSCDWidget.GetModFileName();
	strSmartTestModFile += m_oChooseSCDWidget.m_strModFileName;
	return strSmartTestModFile;
}

void NGDSmartTestMainWidget::slot_On_m_Btn_PreStep_clicked()
{
	if (m_nPage > 0)
	{
		m_nPage--;
	}
	UpdateView();
}

void NGDSmartTestMainWidget::slot_On_m_Btn_NextStep_clicked()
{
	CString strBtnText = ui.m_BtnNextStep->text();
	if (strBtnText == _T("创建测试"))
	{
		CreatAutoTest();//创建自动测试
		m_strSmartTestModFile = _P_GetTemplatePath();
		m_strSmartTestModFile += GetSmartTestModFile();
		m_strSmartTestModFile += _T(".gbxml");
		m_pSelectIed = m_oChooseDeviceWidget.m_pIecDevicesGrid->GetSelectIED();
		ReplaceIEDForSmartTest(m_pSelectIed);
		ExportDvmModFile();
		ExportIecCfgFile();
		OpenGbRptFile(m_strGbRptFile);
		return;
	}
	else if (m_strPage[m_nPage] == Process_GooseDetect)
	{
		if (m_SelectCbsChanged == TRUE)
		{
			UpdateRecordDevices();
			InitIecCfgs();
			InitGooseInOutData();
			m_oGooseInCfgWidget.initData(m_pIecCfgGinDatas);
			m_oGooseOutCfgWidget.initData(m_pIecCfgGoutDatas);
		}
	}
	if (m_nTestMode == TestMode_EntireyInterval && m_nPage < 6)
	{
		m_nPage++;
	}
	else if (m_nTestMode == TestMode_CollectExecuteUnit && m_nPage < 5)
	{
		m_nPage++;
	}
	else if (m_nTestMode == TestMode_Protector && m_nPage < 3)
	{
		m_nPage++;
	}
	UpdateView();
}

void NGDSmartTestMainWidget::slot_TimerForHeartBeat()
{
	if (m_pXClientEngine != NULL)
	{
		m_pXClientEngine->OnSendHeartbeatTimer_NotCheakAuthority();
	}
}
