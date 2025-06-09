#include "stdafx.h"
#include "testwinbase.h"
#include "../DockPane/logwidget.h"
#include "../DockPane/statusinfo.h"
#include "../IniFile/IniFile.h"
#include "../../../Module/LiveUpdate/SttLiveUpdateShell.h"
#include "../../Module/SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../Module/TestWinFrame/SysParasSetDlg/QSysParasSetDialog.h"
#include "../Module/TestWinFrame/OffLineDlg/QOffLineDlg.h"
#include "../../../Module/SttDevice/Module/PowerCtrl/SttPowerCtrlCom.h"
#include "../Module/TestWinFrame/ReportView/SttReportHeadSetDlg.h"

#include "../../../Module/XLanguage/XLanguageMngr.h"

#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

#include "OffLineDlg/QOffLineDlg.h"
#include "IEC61850Config/SttIecConfigDialogWin.h"

#ifndef NOT_USE_SetSetting
#include "SettingValueDlg/SettingValueDialog.h"
#endif

#include "SysParasSetDlg/QModuleSetDlg.h"
#include "SysParasSetDlg/QAuxDCOutputDlg.h"
#include "SysParasSetDlg/QChMapsDlg.h"
#include "SysParasSetDlg/QPasswordDlg.h"

#include "./RsltWidget/RsltExprMngr.h"
#include "QScanLanTesterDlg/QScanLanTesterDlg.h"
#include "QDeviceInforDlg/QDeviceInforDlg.h"
#include "../../../../61850/Module/SCL/SclFileMngr/SclFileMngrGlobal.h"
#include "../../../../61850/Module/SCL/SclFileMngr/XSclFileMngr.h"

#include "../../../Module/SttTest/Common/tmt_adjust_sys_para_trans.h"
#include <set>
#ifdef STT_USE_IecCap_

#include "../RecordTest/SttRcdBufferRcvMsg.h"
#include "../RecordTest/RingMemBuf.h"
#include "../RecordTest/RingMemBufShmDebug.h"
#include "../RecordTest/QT/SttLocalRcdMemBufferMngrLinux.h"
#include "../../../../Module/SmartCap/XSttCap_61850.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../RecordTest/QT/RingMemBufShmDebugWidget.h"
#include "../../../Module/HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../../../Module/SmartCap/SmartCapCtrl.h"

#endif


#include <QTextCodec>
#include <QRect>
#include <QDesktopWidget>
#include <QSharedMemory>
#include <QProcess>

TestWinBase* g_TestWinBase = NULL;
bool g_bTestAppConnect = FALSE;

#ifdef STT_USE_IecCap_

CSttRcdBufferRcvMsg *g_pSttRcdSndRingBuf; //20230627 suyang
QRingMemBufShmDebugWidget *g_pRingMemBufShmDebugWidget = NULL;
extern CSttXHtmlRptGenFactoryBase *g_theHtmlRptGenFactory;

#endif

double g_dUIShowCoef = 1.0f; // 界面显示缩放比例

//#define STT_UPDATE_TESTMACRO_SM_ID		_T("TestMacroSM")	//TestMacroSM共享内存ID

TestWinBase::TestWinBase(QWidget *parent, Qt::WFlags flags,int nMode):QMainWindow(parent, flags)
	,m_oTestMacroSM(STT_UPDATE_TESTMACRO_SM_ID)
{
	//layout
	m_centralWidget = NULL;
	m_gridLayout = NULL;
	m_gridLayout2 = NULL;
	m_tabWidget = NULL;
	m_testParaView = NULL;

	m_pSttXTestMngrHtmlRpt = NULL;
	//	QWidget *m_reportTab;

	m_pParaTab;
	m_ReportTextEdit = NULL;

	m_menuBar = NULL;
	m_mainToolBar = NULL;
	m_statusBar = NULL;

	m_headerToolBar = NULL;
	m_setToolBar = NULL;
	m_reportToolBar = NULL;
	m_viewToolBar = NULL;
	m_updateToolBar = NULL;

	m_headerMenu = NULL;
	m_setMenu = NULL;
	m_reportMenu = NULL;
	m_viewMenu = NULL;
	m_verMenu = NULL;

	m_LabGps = NULL;
	m_LabIconGps = NULL;
	m_LabVer = NULL;
	m_LabLinkTxt = NULL;
	m_LabVersion = NULL;
	m_LabLinkIcon = NULL;

	//QAction
	m_startAct = NULL;
	m_manuTrigerAct = NULL;
	m_stopAct = NULL;
	m_openAct = NULL;
	m_saveAct = NULL;
	m_saveAsAct = NULL;
	m_IECAct = NULL;
	m_IECCapAct = NULL;
	m_customSetAct = NULL;
	m_setSysAct = NULL;
	m_soeTestAct = NULL;
	m_setCommonAct = NULL;
	m_setSettingAct = NULL;	
	m_setSwitchAct = NULL;	
	m_setCustomAct = NULL;
	m_Connect = NULL;	
	m_pChRsMaps_Action = NULL;	//通道资源映射 zhouhj 20211016
	m_pAuxDC_Action = NULL;	//辅助直流设置 zhouhj 20211016
	m_pModulesGearSwitch_Action = NULL;	//辅助直流设置 zhouhj 20211016
// 	m_pLuminousPower_Action = NULL; //2023-11-22 suyang 重复删除
	m_OffLineSel_Action = NULL;


	m_reportSetAct = NULL;	//报告设置
	m_reportViewAct = NULL;	//报告浏览

	m_reportOpenAct = NULL;	
	m_reportSaveAct = NULL;
	m_viewTestAct = NULL;
	m_viewReportAct = NULL;
	m_viewDockSwitchAct = NULL;
	m_viewDockStaInfoAct = NULL;
	m_VersionInforAct = NULL;//zhouhj 20211021 版本信息
	m_updateLocalAct = NULL;
	m_updateTestAppAct = NULL;

	//m_DockSwitch = NULL; 重复
	//m_DockStaInfo = NULL;
	m_TextEditStaInfo = NULL;

	m_pStartBtn = NULL;
	m_pManuTrigerBtn = NULL;
	m_pStopBtn = NULL;
	m_pSetSysBtn = NULL;//"系统参数"按钮
	m_pOffLineSelBtn = NULL;//"脱机选择"按钮
	m_pSetCommonBtn = NULL;
	m_pSetSwitchBtn = NULL;
	m_pSetSettingBtn = NULL;
	m_pSetCustomBtn = NULL;
	m_pDASetBtn = NULL;
	m_pIECBtn = NULL;

	m_pConnectBtn = NULL;
	m_pChRsMapsBtn = NULL;//zhouhj 20211016 通道映射
	m_pReportSetBtn = NULL;	//报告设置
	m_pReportViewBtn = NULL;	//报告浏览
	m_pSoeTestBtn = NULL;

	m_pViewTestBtn = NULL;
	m_pViewReportBtn = NULL;
	//2022.5.20


	g_TestWinBase = this;
//	m_bIECParasChanged = true;
	m_bSystemParasChanged = true;
	m_bChMapsChanged = TRUE;
	m_bAuxDCOutputStarted = false;
	m_bCustomACOutputStarted = false;
	m_DockSwitch = NULL;
	m_DockStaInfo = NULL;
	m_startAct = NULL;
// 	m_manuTrigerAct = NULL;
	m_stopAct = NULL;
	m_openAct = NULL;
	m_saveAct = NULL;
	m_saveAsAct = NULL;
	m_setSysAct = NULL;
	m_setCommonAct = NULL;
	m_setSettingAct = NULL;
	m_setSwitchAct = NULL;
	m_Connect = NULL;
	m_pChRsMaps_Action = NULL;
	m_pAuxDC_Action = NULL;
	m_pModulesGearSwitch_Action = NULL;
	m_pLuminousPower_Action = NULL;
// 	m_IECAct = NULL;
	m_setCustomAct = NULL;
	m_soeTestAct = NULL;
// 	m_reportSetAct = NULL;重复
// 	m_reportViewAct = NULL;
// 	m_reportOpenAct = NULL;
// 	m_reportSaveAct = NULL;
// 	m_viewDockSwitchAct = NULL;
// 	m_viewDockStaInfoAct = NULL;
// 	m_updateLocalAct = NULL;	
// 	m_VersionInforAct = NULL;
// 	m_updateTestAppAct = NULL;
	m_pAnaParaSet = NULL;
	m_pDigParaSet = NULL;
	m_pLowSParaSet = NULL;
	m_pSyncParaSet = NULL;
	m_pGooseParaWidget = NULL;
	m_pExSwitchInputSetWidget = NULL;
	m_pExSwitchOutputSetWidget = NULL;
	m_TestTable = NULL;
	m_pSttTestResource = NULL;
/*	m_pIECBtn = NULL;*/
	m_nCurrTestIndex = -1;
	m_nMode = nMode;
	m_pCurrOpTest = NULL;
	m_pOffLineSelBtn = NULL;
	m_pSoeTestBtn = NULL;
	m_pSetCustomBtn = NULL;
	m_pChRsMapsBtn = NULL;
	m_reportToolBar = NULL; 
	m_pReportSetBtn = NULL;
	m_pReportViewBtn = NULL;
	m_infoWidget = NULL;
	m_pTimeResponseWidget = NULL;
	m_pWaveWidget = NULL;
	m_pSttXTestMngrHtmlRpt = NULL;
	m_pFT3Widget=NULL;

	//suyang 20230628
	m_pIECCapBtn = NULL;  
	m_bIsUsingIecCap = FALSE;

	m_pAuxDCBtn = NULL;

#ifdef STT_USE_IecCap_
	m_pKeyDB = NULL;
#endif
	m_bReportData = TRUE;

	
	//2022.5.19 caoxc
	m_TestTable = NULL;
	m_bLoadFinished = false;

	m_strLogInfo[0] = "ReadDeviceParameter" ;
	m_strLogInfo[1] = "OnReport";
	m_strLogInfo[2] = "UpdateParameter";
	m_strLogInfo[3] = "Process_Cmd_Test";
	m_strLogInfo[4] = "StartTest";
	m_strLogInfo[5] = "SetParameter";
	m_strLogInfo[6] = "CheckBeforeProcessCmdTest";
	m_strLogInfo[7] = "CSttHarmTest";
	m_bInitConneced = FALSE;

	QDesktopWidget *pDeskTop = QApplication::desktop();
	QRect rcScreen = pDeskTop->screenGeometry();
	m_nScreenWidth = rcScreen.width();
	m_nScreenHeight = rcScreen.height();

	CLogPrint::Create(this);
	g_nTimeOut_Test = 10000;//zhouhj 2023.12.1 修改缺省超时时间,防止命令发送后,没有权限,软件需要等很久才能结束
	//zhouhj 2023.12.11 从3s改为10s防止下发IEC配置文件比较大,出现超时

	InitXmlKeys();
	CXLanguageXmlRWKeys::Create();
	CXLanguageMngr::Create(new CXLangResource_PowerTestWin(), TRUE);

#ifndef NOT_USE_XLANGUAGE
 	((CSttAdjSysParaDataTypes*)g_pSttAdjSysParaDataTypes)->InitAdjSysParaDataTypes();
#endif

	CSclFileMngrXmlRWKeys::Create();
	CCharacteristicXmlRWKeys::Create();
	g_oSttTestAppCfg.SttOpen(g_oSttTestAppCfg.GetSttCfgFile());
	g_oSttTestResourceMngr.LoadDefaultIec61850Config();//放入QGooseParaWidget::initGooseTable()中加载
	g_oSttSystemConfig.OpenSystemConfig();

	if (!g_oXSclFileMngr.m_bHasOpenCfgFile)
	{
		g_oXSclFileMngr.OpenSclFileMngrCfg();
		CString strCurrTscdFilePath;
		strCurrTscdFilePath = g_oXSclFileMngr.GetCurrSelTscdFilePah();
		m_oSclStation.OpenSclStationFile(strCurrTscdFilePath);
	}

	initData();
	InitDefaultSystemParas();//在initData已去除初始化参数,故单独调用初始化函数
	connect(&m_oTimer,SIGNAL(timeout()),this,SLOT(slot_Timer()));
//	connect(this,SIGNAL(sig_UpdateEventMsg()),this,SLOT(slot_UpdateEventMsg()));//zhouhj 2024.4.11 目前采用定时器调用的方式此处 未用到
	connect(this,SIGNAL(sig_OnUpdateGpsTime(long , long ,long ,QString)),this,SLOT(slot_OnUpdateGpsTime(long , long ,long ,QString)),Qt::QueuedConnection);
	connect(this,SIGNAL(sig_OnUpdateGpsTime(CDataGroup *)),this,SLOT(slot_OnUpdateRtSyncTime(CDataGroup*)),Qt::QueuedConnection);//不同线程,槽函数需要使用队列模式在主线程执行

	connect(this,SIGNAL(sig_updataVectorData()), this, SLOT(slot_updateVectorData()));


	//2021-5-30  lijunqing
	m_oTmtTestMngr.init();
	LogPrintSoftWareVersionMsg();

	OpenReportHead();//打开报告头


	HDC hd = GetDC(NULL);
	double dDotPix1 = GetDeviceCaps(hd, LOGPIXELSX);
	g_dUIShowCoef = dDotPix1 / 96;

	InitIECChannelsData();
}

void TestWinBase::LogPrintTypeMsg()
{
	CString strMsg;
	strMsg = _T("当前输出类型为: ");

	if (g_oSystemParas.m_nHasAnalog == 1)
	{
		strMsg += "  模拟量";
	}
	
	if (g_oSystemParas.m_nHasDigital == 1)
	{
		strMsg += _T(" 数字量");
	}
	
	if (g_oSystemParas.m_nHasWeek == 1)
	{
		strMsg += "  小信号";
	}

	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 0) &&(g_oSystemParas.m_nHasWeek == 0))
	{
		strMsg = _T(" ");
	}


	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,strMsg.GetString());
	
// 	//20240415 suyang 北京要求 初始化时电流为1档
// 	if(g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[0].m_nIPowerMode != 0)
// 	{
// 		g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[0].m_nIPowerMode = 0;
// 	}


}

void TestWinBase::LogPrintSoftWareVersionMsg()
{
// 	QDate buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " " ), "MMM dd yyyy");
// 	QString srtr = QString( __DATE__ );
// 
// 	if (srtr.mid(4,1)==" ")
// 	{
// 		buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " " ), "MMM d yyyy");
// 	}
// 	else
// 	{
// 		buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " " ), "MMM dd yyyy");
// 	}
// 
// 	CString strVer = tr("Version:6.4_") + buildDate.toString("yyyyMMdd");
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前程序版本(%s)."),strVer.GetString());
}

TestWinBase::~TestWinBase()
{
	if (m_bViewTestStarted)
	{
		slot_stop();
	}

/*
	g_oSttTestAppCfg.SttOpen(g_oSttTestAppCfg.GetOldCfgFile());

	FreeXClientEngine();
	ReleaseXmlKeys();

	if (m_pSttTestResource != NULL)
	{
		delete m_pSttTestResource;
		m_pSttTestResource = NULL;
	}
*/
	CXLanguageMngr::Release();
	CXLanguageXmlRWKeys::Release();

	CSclFileMngrXmlRWKeys::Release();
	CCharacteristicXmlRWKeys::Release();
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();

#ifdef STT_USE_IecCap_

	if (m_pKeyDB != NULL)
	{
		delete m_pKeyDB;
		m_pKeyDB = NULL;
	}

	if (g_theSmartCapCtrl != NULL)
	{
		ExitSttIecRecord();
	}

#endif

}

void TestWinBase::initUI()
{
	createLayout();	
	createDockStaInfo();	
	createActions();	
	createToolBar();
	createMenus();
	createStatusBar();	

	m_pTimeResponseWidget = m_testParaView->getMonitor()->GetTimeResponseWidget();
	m_vectorWidget = m_testParaView->getMonitor()->GetVectorWidget();
    //chenling
	m_powerdiagramWidget=m_testParaView->getMonitor()->GetPowerDiagramWidget();
// 	m_powerWidget = m_testParaView->getMonitor()->GetPowerWidget();
	m_seqWidget = m_testParaView->getMonitor()->GetSeqWidget();
	m_lineVoltWidget = m_testParaView->getMonitor()->GetLineVoltWidget();
	m_infoWidget = m_testParaView->getMonitor()->GetInfoWidget();
	initConnect();	
	setTitleIcon();

	if (SeparateShowTestView())
	{
		MonitorTab* pMonitorTab = m_testParaView->getMonitor();
		QMainPara* pQMainPara = m_testParaView->getMainPara();
		CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

		if (pSttDevConfig->m_nDoubleClickEdit == 0)
		{
			pMonitorTab->setVisible(false);
			pQMainPara->setVisible(true);
		}
	}

	showMaximized();
	setFocusPolicy(Qt::StrongFocus);
	setWindowState(Qt::WindowMaximized);
}

void TestWinBase::initConnect()
{
//	connect(&m_oCommTestAppCfgDlg, SIGNAL(sig_CommCfgOK(QString &,long)), this, SLOT(slot_CommCfgOK(QString &,long)));
	connect(&m_oDcSetDlg, SIGNAL(sig_ACStartClicked()), this, SLOT(slot_CustomACOutputStart()));
	connect(&m_oDcSetDlg, SIGNAL(sig_ACEndClicked()), this, SLOT(slot_CustomACOutputEnd()));

	connect(&m_oDASetDlg, SIGNAL(sig_DASetClicked(bool)), this, SLOT(slot_DASetStart(bool)));

	connect(&m_oSoeDlg, SIGNAL(sig_SoeStartClicked()), this, SLOT(slot_SoeStart()));
	connect(&m_oSoeDlg, SIGNAL(sig_SoeStopClicked()), this, SLOT(slot_SoeStop()));
	connect(&m_oSoeDlg, SIGNAL(sig_SoeParasSave()), this, SLOT(slot_SoeParasSave()));
	connect(this, SIGNAL(sig_UpdateTestResource()), this, SLOT(slot_UpdateTestResource()));

	connect(this, SIGNAL(sig_LogString(CString)), this, SLOT(slot_LogString(CString)));

	//2022.5.19 caoxc
	if(m_pSttXTestMngrHtmlRpt)
	{
		QSttReportViewHtml* pReportView= (QSttReportViewHtml*)m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
		connect(pReportView,SIGNAL(msg_HtmlLoadFinish(bool)),this,SLOT(slot_loadFinished(bool)));
	}
}

void TestWinBase::initData()
{
	initCommonParas();
}

void TestWinBase::initCommonParas()
{
	if (!OpenSysOutputParaFile())
	{
		InitDefualtSysOutputPara();
		stt_xml_serialize_write_SysOutput();//zhouhj 20210629 如果稳态输出模板文件不存在,则初始化并保存缺省文件
	}

	if (!OpenSoeParasFile())
	{
		initDefaultSoeParaFile();
	}	
}

// BOOL Global_SetModuleMaxMinValue_AC_Vol(CDataGroup *pModuleAttrs,float *pfMaxMax,float *pfMaxMin,long nModulePower)
// {
// 	if (nModulePower == STT_MODULE_VOLT_V130_130)
// 	{
// 		*pfMaxMax = max(*pfMaxMax,130);
// 		*pfMaxMin = min(*pfMaxMin,130);
// 		return TRUE;
// 	}
// 	else if (nModulePower == STT_MODULE_VOLT_V248_248)
// 	{
// 		*pfMaxMax = max(*pfMaxMax,248);
// 		*pfMaxMin = min(*pfMaxMin,248);
// 		return TRUE;
// 	}
// 	else if (nModulePower == STT_MODULE_VOLT_V270_270)
// 	{
// 		*pfMaxMax = max(*pfMaxMax,270);
// 		*pfMaxMin = min(*pfMaxMin,270);
// 		return TRUE;
// 	}
// 	else if (nModulePower == STT_MODULE_VOLT_V300_300)
// 	{
// 		*pfMaxMax = max(*pfMaxMax,300);
// 		*pfMaxMin = min(*pfMaxMin,300);
// 		return TRUE;
// 	}
// 	else if (nModulePower == STT_MODULE_VOLT_V300_440)
// 	{
// 		*pfMaxMax = max(*pfMaxMax,440);
// 		*pfMaxMin = min(*pfMaxMin,440);
// 		return TRUE;
// 	}
// 
// 	CDvmData* pDataMax = (CDvmData*)pModuleAttrs->FindByID(_T("ChMax"));
// 
// 	if (pDataMax == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	float dTmp = CString_To_double(pDataMax->m_strValue);
// 	*pfMaxMax = max(*pfMaxMax,dTmp);
// 	*pfMaxMin = min(*pfMaxMin,dTmp);
// 	return TRUE;
// }

/*
BOOL Global_SetModuleMaxMinValue(CDataGroup *pModule,float *pfAC_MaxMax,float *pfAC_MaxMin,float *pfDC_MaxMax,float *pfDC_MaxMin,BOOL bVol)
{
	CDataGroup *pModuleAttrs = (CDataGroup*)pModule->FindByID(_T("ModuleAttrs"));

	if (pModuleAttrs == NULL)
	{
		return FALSE;
	}

	CDataGroup *pHdGears = (CDataGroup*)pModuleAttrs->FindByID(_T("HdGears"));

	if (pHdGears == NULL)
	{
		return FALSE;
	}

	CExBaseList *pCurObj = NULL;
	double dCurGearValue = 0.0f,dTmpValue = 0.0f,dCurChMaxDC = 10.0f;

	if (!pModuleAttrs->GetDataValue(_T("ChDcMax"),dCurChMaxDC))
	{
		if (bVol)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前电压模块,缺少\"通道出直流最大值\"(ChDcMax)数据."));
		} 
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前电流模块,缺少\"通道出直流最大值\"(ChDcMax)数据."));
		}
	}
	
	*pfDC_MaxMax = max(*pfDC_MaxMax,dCurChMaxDC);
	*pfDC_MaxMin = min(*pfDC_MaxMin,dCurChMaxDC);
	POS pos = pHdGears->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDataGroup *pGearGroup = NULL;

	while(pos)
	{
		pCurObj = (CExBaseList*)pHdGears->GetNext(pos);

		if (pCurObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pGearGroup = (CDataGroup *)pCurObj;

		if ((pGearGroup->m_strDataType != _T("HdGear")))
		{
			continue;
		}

		pDvmData = (CDvmData*)pCurObj->FindByID(_T("GearValue"));

		if (pDvmData == NULL)
		{
			continue;
		}

		dTmpValue = CString_To_double(pDvmData->m_strValue);
		dCurGearValue = max(dCurGearValue,dTmpValue);
	}

	if (abs(dCurGearValue)<=EPSINON)
	{
		return FALSE;
	}

	*pfAC_MaxMax = max(*pfAC_MaxMax,dCurGearValue);
	*pfAC_MaxMin = min(*pfAC_MaxMin,dCurGearValue);

// 	if (bVol)//如果是电压模块,其最大直流输出为交流的1.4倍,如果是电流模块,其最大输出为直流的一半
// 	{
// 		dCurGearValue *= 1.4f;//zhouhj 20210828 通道出直流数据仍然从模块属性中取
// 	} 
// 	else
// 	{
// 		dCurGearValue /= 2.0f;
// 	}
// 	
// 	*pfDC_MaxMax = max(*pfDC_MaxMax,dCurGearValue);
// 	*pfDC_MaxMin = min(*pfDC_MaxMin,dCurGearValue);
	return TRUE;

}
*/

// BOOL Global_SetModuleMaxMinValue_DC_Vol(CDataGroup *pModuleAttrs,float *pfMaxMax,float *pfMaxMin,long nModulePower)
// {
// 	CDvmData* pDataMax = (CDvmData*)pModuleAttrs->FindByID(_T("ChDcMax"));
// 
// 	if (pDataMax == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	float dTmp = CString_To_double(pDataMax->m_strValue);
// 	*pfMaxMax = max(*pfMaxMax,dTmp);
// 	*pfMaxMin = min(*pfMaxMin,dTmp);
// 	return TRUE;
// }
/*

BOOL Global_GetBinBoutExNum(CDataGroup *pModuleAttrs,int &nBinExNum,int &nBoutExNum)
{
	CString strTmp;
	CDvmData* pData = NULL;

	for (int nIndex = 0;nIndex<4;nIndex++)
	{
		strTmp.Format(_T("SwitchIn_%d"),nIndex);

		pData = (CDvmData*)pModuleAttrs->FindByID(strTmp);

		if (pData != NULL)
		{
			if (CString_To_long(pData->m_strValue) == 0)
			{
				nBinExNum += 16;
			} 
			else
			{
				nBoutExNum += 16;
			}
		}
	}

	return TRUE;
}
*/

// BOOL Global_SetModuleMaxMinValue_AC_Cur(CDataGroup *pModuleAttrs,float *pfMaxMax,float *pfMaxMin,long nModulePower)
// {
// 	if (nModulePower == STT_MODULE_CURRENT_C12_5)
// 	{
// 		*pfMaxMax = max(*pfMaxMax,12.5);
// 		*pfMaxMin = min(*pfMaxMin,12.5);
// 		return TRUE;
// 	}
//  	else if ((nModulePower == STT_MODULE_CURRENT_C20))//zhouhj 20210718  宏定义已被删除
//  	{
//  		*pfMaxMax = max(*pfMaxMax,20);
//  		*pfMaxMin = min(*pfMaxMin,20);
//  		return TRUE;
//  	}
// 	else if (nModulePower == STT_MODULE_CURRENT_C32)
// 	{
// 		*pfMaxMax = max(*pfMaxMax,32);
// 		*pfMaxMin = min(*pfMaxMin,32);
// 		return TRUE;
// 	}
// 
// 	CDvmData* pDataMax = (CDvmData*)pModuleAttrs->FindByID(_T("ChMax"));
// 
// 	if (pDataMax == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	float dTmp = CString_To_double(pDataMax->m_strValue);
// 	*pfMaxMax = max(*pfMaxMax,dTmp);
// 	*pfMaxMin = min(*pfMaxMin,dTmp);
// 	return TRUE;
// }
// 
// BOOL Global_SetModuleMaxMinValue_DC_Cur(CDataGroup *pModuleAttrs,float *pfMaxMax,float *pfMaxMin,long nModulePower)
// {
// 	CDvmData* pDataMax = (CDvmData*)pModuleAttrs->FindByID(_T("ChDcMax"));
// 
// 	if (pDataMax == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	float dTmp = CString_To_double(pDataMax->m_strValue);
// 	*pfMaxMax = max(*pfMaxMax,dTmp);
// 	*pfMaxMin = min(*pfMaxMin,dTmp);
// 	return TRUE;
// }
/*

long Global_GetModulePowerValue(CDataGroup *pModuleAttrs)
{
	CDvmData* pData = (CDvmData*)pModuleAttrs->FindByID(_T("ModulePower"));

	if (pData == NULL)
	{
		return -1;
	}

	return CString_To_long(pData->m_strValue);
}

long Global_GetModulePos(CDataGroup *pModuleAttrs)
{
	CDvmData* pData = (CDvmData*)pModuleAttrs->FindByID(_T("ModulePos"));

	if (pData == NULL)
	{
		return -1;
	}

	return CString_To_long(pData->m_strValue);
}

long Global_GetModuleType(CDataGroup *pModuleAttrs)
{
	CDvmData* pData = (CDvmData*)pModuleAttrs->FindByID(STT_ADJ_ID_ModuleType);

	if (pData == NULL)
	{
		return -1;
	}

	CDataType *pFind = (CDataType*)g_pSttAdjSysParaDataTypes->FindByID(STT_ADJ_ID_ModuleType);

	if (pFind == NULL)
	{
		return -1;
	}

	CDataTypeValue *pValue = (CDataTypeValue*)pFind->FindByID(pData->m_strValue);

	if (pValue == NULL)
	{
		return -1;
	}

	return CString_To_long(pValue->m_strIndex);
}*/

/*
void TestWinBase::initLocalSysPara()
{
	if (!g_oSttTestResourceMngr.HasLoadDevice())
	{
		return;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//从资源中取得开入数、开出数
	CDataGroup* pBoutGroup = g_oSttTestResourceMngr.m_oCurrDevice.GetBoutTrunOnValueDef();

	if (pBoutGroup)
	{
		g_nBoutCount = pBoutGroup->GetCount();
		if (g_nBoutCount == 0)
		{
			g_nBoutCount = BINOUT_NUM;	//8个
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	g_oLocalSysPara.InitMaxMinVolCurValue();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CExBaseList oCurModuleListRef;
	long nAnalogModuleNum = 0,nDigitalModuleNum = 0,nWeakModuleNum = 0,nExBinBoutModuleNum = 0;
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_VOLT);//获取全部电压模块
//	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_VOLT_CURRENT);//获取全部电压模块
	nAnalogModuleNum = oCurModuleListRef.GetCount();
	CDataGroup *pModule = NULL;
	CDataGroup *pModuleAttrs = NULL;
	CDvmData *pData = NULL;
//	long nModulePower = -1;
	double dTmp = 0;
	POS pos = oCurModuleListRef.GetHeadPosition();

	while (pos != NULL)//在该循环中设置电压模块最大值,最小值
	{
		pModule = (CDataGroup *)oCurModuleListRef.GetNext(pos);
		Global_SetModuleMaxMinValue(pModule,&g_oLocalSysPara.m_fAC_VolMax,&g_oLocalSysPara.m_fAC_VolMin,&g_oLocalSysPara.m_fDC_VolMax,&g_oLocalSysPara.m_fDC_VolMin,TRUE);
// 		pModuleAttrs = (CDataGroup*)pModule->FindByID(_T("ModuleAttrs"));
// 
// 		if (pModuleAttrs == NULL)
// 		{
// 			continue;
// 		}
// 
// 		nModulePower = Global_GetModulePowerValue(pModuleAttrs);
// 		Global_SetModuleMaxMinValue_AC_Vol(pModuleAttrs,&g_oLocalSysPara.m_fAC_VolMax,&g_oLocalSysPara.m_fAC_VolMin,nModulePower);
// 		Global_SetModuleMaxMinValue_DC_Vol(pModuleAttrs,&g_oLocalSysPara.m_fDC_VolMax,&g_oLocalSysPara.m_fDC_VolMin,nModulePower);
	}

	if (g_oLocalSysPara.m_fAC_VolMax <= 0){
		g_oLocalSysPara.m_fAC_VolMax = 130;
	}

	if(g_oLocalSysPara.m_fDC_VolMax <= 0){
		g_oLocalSysPara.m_fDC_VolMax = 100;
	}

	oCurModuleListRef.RemoveAll();
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_CURRENT);
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_VOLT_CURRENT);
	tmt_GearSetCurModules *pGearSetCurModules = &g_oSystemParas.m_oGearSetCurModules;
	pGearSetCurModules->m_nCurModuleNum = oCurModuleListRef.GetCount();//设置电流模块总数量
	nAnalogModuleNum += pGearSetCurModules->m_nCurModuleNum;

	tmt_CurModuleGear *pCurGear = NULL;
	long nCurModuleIndex = -1;
	pos = oCurModuleListRef.GetHeadPosition();
	
	while (pos != NULL)//在该循环中设置电流模块最大值,最小值,电流模块功率档位等
	{
		pModule = (CDataGroup *)oCurModuleListRef.GetNext(pos);
		pModuleAttrs = (CDataGroup*)pModule->FindByID(_T("ModuleAttrs"));
		nCurModuleIndex++;
		pCurGear = &pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex];

		if (pModuleAttrs == NULL)
		{
			pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex].m_nModulePos = -1;
			pCurGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_SUPPORT;
			pCurGear->m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_NULL;
			continue;
		}

		pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex].m_nModulePos = Global_GetModulePos(pModuleAttrs);
		pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex].m_nModuleType = Global_GetModuleType(pModuleAttrs);

		if (pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex].m_nModuleType != STT_MODULE_TYPE_VOLT_CURRENT)
		{
			Global_SetModuleMaxMinValue(pModule,&g_oLocalSysPara.m_fAC_CurMax,&g_oLocalSysPara.m_fAC_CurMin,&g_oLocalSysPara.m_fDC_CurMax,&g_oLocalSysPara.m_fDC_CurMin,FALSE);
		}

// 		nModulePower = Global_GetModulePowerValue(pModuleAttrs);
// 		Global_SetModuleMaxMinValue_AC_Cur(pModuleAttrs,&g_oLocalSysPara.m_fAC_CurMax,&g_oLocalSysPara.m_fAC_CurMin,nModulePower);
// 		Global_SetModuleMaxMinValue_DC_Cur(pModuleAttrs,&g_oLocalSysPara.m_fDC_CurMax,&g_oLocalSysPara.m_fDC_CurMin,nModulePower);

		pData = (CDvmData*)pModuleAttrs->FindByID(_T("ThreeChansMode"));

		if (pData != NULL)
		{
			if ((pCurGear->m_nMergeCurTerminal != STT_LARGE_CURRENT_MERGE_NOT_MERGE)&&(pCurGear->m_nMergeCurTerminal != STT_LARGE_CURRENT_MERGE_THREE_CH))
			{
				pCurGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_MERGE;
			}

			pCurGear->m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_NULL;
			continue;
		}

		pData = (CDvmData*)pModuleAttrs->FindByID(_T("OneChanMode"));

		if (pData == NULL)
		{
			pCurGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_SUPPORT;
			pCurGear->m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_NULL;
			continue;
		}

		if ((pCurGear->m_nMergeCurTerminal != STT_LARGE_CURRENT_MERGE_NOT_MERGE)&&(pCurGear->m_nMergeCurTerminal != STT_LARGE_CURRENT_MERGE_ONE_CH))
		{
			pCurGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_MERGE;
		}

		if (pCurGear->m_nLargeCurOutTerm == STT_LARGE_CUR_OUT_NULL)//如果当前选择的为空,则需要对其进行初始化
		{
			pCurGear->m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_TERM_A;
		}
	}

	oCurModuleListRef.RemoveAll();

	if (g_oLocalSysPara.m_fAC_CurMax <= 0){
		g_oLocalSysPara.m_fAC_CurMax = 20;
	}

	if(g_oLocalSysPara.m_fDC_CurMax <= 0){
		g_oLocalSysPara.m_fDC_CurMax = 20;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_0G8M);
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_2G6M);
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_4G4M);
	nDigitalModuleNum = oCurModuleListRef.GetCount();
	oCurModuleListRef.RemoveAll();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_WEEK_EX);
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_WEEK_MAIN);
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_WEEK_EX_48);
	nWeakModuleNum = oCurModuleListRef.GetCount();
	oCurModuleListRef.RemoveAll();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	g_oSttTestResourceMngr.m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_SWITCH);
	nExBinBoutModuleNum = oCurModuleListRef.GetCount();

	pos = oCurModuleListRef.GetHeadPosition();
	g_oLocalSysPara.m_nCHBinInExNum = 0;
	g_oLocalSysPara.m_nCHBinOutExNum = 0;

	while (pos != NULL)
	{
		pModule = (CDataGroup *)oCurModuleListRef.GetNext(pos);
		pModuleAttrs = (CDataGroup*)pModule->FindByID(_T("ModuleAttrs"));

		if (pModuleAttrs == NULL)
		{
			continue;
		}

		Global_GetBinBoutExNum(pModuleAttrs,g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum);
	}

	oCurModuleListRef.RemoveAll();
	g_oLocalSysPara.m_nSupportAnalogOutput = 1;
	g_oLocalSysPara.m_nSupportDigitalOutput = 1;
	g_oLocalSysPara.m_nSupportWeakOutput = 1;

	if (nAnalogModuleNum == 0)
	{
		g_oSystemParas.m_nHasAnalog = 0;
		g_oLocalSysPara.m_nSupportAnalogOutput = 0;
	}

	if (nDigitalModuleNum == 0)
	{
		g_oSystemParas.m_nHasDigital = 0;
		g_oLocalSysPara.m_nSupportDigitalOutput = 0;
	}

	if (nWeakModuleNum == 0)
	{
		g_oSystemParas.m_nHasWeek = 0;
		g_oLocalSysPara.m_nSupportWeakOutput = 0;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("最大交流电压输出值(%fV),最大交流电流输出值(%fA)."),g_oLocalSysPara.m_fAC_VolMax,g_oLocalSysPara.m_fAC_CurMax);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("最大直流电压输出值(%fV),最大直流电流输出值(%fA)."),g_oLocalSysPara.m_fDC_VolMax,g_oLocalSysPara.m_fDC_CurMax);
}
*/
void TestWinBase::setTitleIcon()
{
	CString strName;
	strName = g_oSttSystemConfig.m_strCompanyName;

	if (strName.IsEmpty())
	{
		strName = _T("Ponovo");
	}

	strName += _T(" 通用试验");
	setWindowTitle(strName/*tr("Ponovo通用试验")*/);
	setWindowIcon(QPixmap("./images/ManualTest.png"));
}

void TestWinBase::createLayout(/*int nMode*/)
{
	resize(848, 497);
	m_centralWidget = new QWidget();
	m_centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
	m_gridLayout = new QGridLayout(m_centralWidget);
	m_gridLayout->setSpacing(6);
	m_gridLayout->setContentsMargins(11, 11, 11, 11);
	m_gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

	m_tabWidget = new QTabWidget(m_centralWidget);
	m_tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
	m_tabWidget->setTabPosition(QTabWidget::South);
	m_tabWidget->findChildren<QTabBar*>().at(0)->hide();//隐藏tab的标签头 sf 20210926

	m_testParaView = new TestParaView(m_tabWidget/*,nMode*/);
	m_testParaView->setObjectName(QString::fromUtf8("para_tab"));
	m_tabWidget->addTab(m_testParaView, QString());
  
	if(m_pSttXTestMngrHtmlRpt)
	{
		QSttReportViewHtml* pReportView= (QSttReportViewHtml*)m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
		m_tabWidget->addTab(pReportView, QString());
	}
/*
	m_reportTab = new QWidget();
	m_reportTab->setObjectName(QString::fromUtf8("report_tab"));

	m_gridLayout2 = new QGridLayout(m_reportTab);
	m_gridLayout2->setSpacing(0);
	m_gridLayout2->setContentsMargins(0, 0, 0, 0);
	m_gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
	m_ReportTextEdit = new QTextEdit(m_reportTab);
	m_ReportTextEdit->setObjectName(QString::fromUtf8("m_ReportTextEdit"));
	m_gridLayout2->addWidget(m_ReportTextEdit, 0, 0, 1, 1);
	m_tabWidget->addTab(m_reportTab, QString());
*/
	m_tabWidget->setTabText(m_tabWidget->indexOf(m_testParaView),tr("试验视图"));

	if(m_pSttXTestMngrHtmlRpt)
	{
		QSttReportViewHtml* pReportView= (QSttReportViewHtml*)m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
		m_tabWidget->setTabText(m_tabWidget->indexOf(pReportView),tr("报告视图"));
	}
	
	m_gridLayout->addWidget(m_tabWidget, 0, 0, 1, 1);
	setCentralWidget(m_centralWidget);

	m_menuBar = new QMenuBar();
	m_menuBar->setObjectName(QString::fromUtf8("menuBar"));
	m_menuBar->setGeometry(QRect(0, 0, 848, 23));
	setMenuBar(m_menuBar);
	m_mainToolBar = new QToolBar();
	m_mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
	addToolBar(Qt::TopToolBarArea, m_mainToolBar);
	m_statusBar = new QStatusBar();
	m_statusBar->setObjectName(QString::fromUtf8("statusBar"));
	setStatusBar(m_statusBar);

	m_tabWidget->setCurrentIndex(0);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QCustomDockWidget::QCustomDockWidget(const QString &title, QWidget *parent)
: QDockWidget(title, parent)
{


}
QCustomDockWidget::~QCustomDockWidget()
{

}

void QCustomDockWidget::closeEvent(QCloseEvent *event)
{
	// 检查当前位置是否为初始位置
	if (geometry().bottomLeft() != m_initialPosition) {
		// 不是初始位置，将位置还原到初始位置
		//move(initialPosition);
		emit sig_updateQDockWidget();

		event->ignore(); // 阻止默认的关闭行为
	} 
	// 	else 
	// 	{
	// 		event->accept(); // 接受关闭事件
	// 	}
}

// 这个是保存和还原QDockWidget 代码，记录一下，以防需要用时找不到

// public:
// 
// 	void SaveDockPosition(QDockWidget *dockWidget);//20240108 suyang 保存DockWidget当前状态
// 	void RestoreDockPosition(QDockWidget *dockWidget);//20240108 suyang 还原DockWidget之前状态
// 	bool hasDraggedDock;
// 	QDockWidget *initialDockState;

// void  TestWinBase::RestoreDockPosition(QDockWidget *dockWidget)
// {
// 	QSettings settings("MyApp", "MyMainWindow");
// 	QVariant dockState = settings.value("dockState_" + dockWidget->objectName());
// 	if (dockState.isValid()) 
// 	{
// 		QByteArray sd  = dockState.toByteArray();
// 		restoreState(dockState.toByteArray());
// 	}
// }
// 
// void TestWinBase::SaveDockPosition(QDockWidget *dockWidget)
// {
// 	QSettings settings("MyApp", "MyMainWindow");
// 	settings.setValue("dockState_" + dockWidget->objectName(), saveState());
// }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestWinBase::slot_DockClosed()
{
	QString strTextEdit = m_TextEditStaInfo->toHtml();
	// 	RestoreDockPosition(m_DockStaInfo);
	delete m_DockStaInfo;
	m_DockStaInfo = NULL;
	createDockStaInfo();
	tabifyDockWidget(m_DockSwitch,m_DockStaInfo);
	m_TextEditStaInfo->setText(strTextEdit);

}

void TestWinBase::createDockStaInfo()
{
	if (m_DockStaInfo)
	{
		QList<QLayout*> layoutF = m_DockStaInfo->findChildren<QLayout*>();
		foreach (QLayout* lay, layoutF) 
		{   
			delete lay; 
			lay = NULL;
		}

		QList<QTextEdit*> btnF = m_DockStaInfo->findChildren<QTextEdit*>();
		foreach (QTextEdit* btn, btnF) 
		{   
			delete btn;  
			btn = NULL;
		}

		delete m_DockStaInfo;
		m_DockStaInfo = NULL;
	}

	//状态历史记录
	m_DockStaInfo =new QCustomDockWidget(tr("状态历史记录"),this);  
	m_DockStaInfo->setFeatures(QDockWidget::NoDockWidgetFeatures);  
	m_DockStaInfo->m_initialPosition = geometry().bottomLeft();


	m_DockStaInfo->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
	m_TextEditStaInfo=new QTextEdit(); 
	QFont ft;
	ft.setPointSize(9);
	m_TextEditStaInfo->setFont(ft);
	m_DockStaInfo->setWidget(m_TextEditStaInfo);  

// 	SaveDockPosition(m_DockStaInfo);

	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();  // 20240417  xueyangfan   增加状态历史记录拖出来的时候可以调整大小
	if (pSttDevConfig->m_nDoubleClickEdit == 0)
	{
		m_DockSwitch->setFixedHeight(93);
		m_DockStaInfo->setFixedHeight(93);
	}

	addDockWidget(Qt::BottomDockWidgetArea, m_DockStaInfo);//mym 2021-8-21 add 
	
	connect(m_DockStaInfo, SIGNAL(sig_updateQDockWidget()), this,SLOT(slot_DockClosed()));
}

void TestWinBase::createDockSwitch()
{
	if (m_DockSwitch)
	{
		QList<QLayout*> layoutF = m_DockSwitch->findChildren<QLayout*>();
		foreach (QLayout* lay, layoutF) 
		{   
			delete lay; 
			lay = NULL;
		}

		QList<QToolButton*> btnF = m_DockSwitch->findChildren<QToolButton*>();
		foreach (QToolButton* btn, btnF) 
		{   
			delete btn;  
			btn = NULL;
		}

		delete m_DockSwitch;
		m_DockSwitch = NULL;
	}

	m_oBinInToolBtnList.clear();
	m_oBinOutToolBtnList.clear();
	m_IInfoList.clear();

	//状态灯显示
	m_DockSwitch = new QCustomDockWidget(tr("状态灯显示"),this);  
	m_DockSwitch->setFeatures(QDockWidget::DockWidgetClosable);  
	m_DockSwitch->setAllowedAreas(Qt::BottomDockWidgetArea);  
	QWidget *w1 = new QWidget();
	QToolButton *pToolBtn = NULL;

	m_V = new QToolButton;
	m_OH = new QToolButton;
	m_Run = new QToolButton;
	m_DCurrent = new QToolButton;

	//从资源中取得模拟的开入数
	for(int i=0; i<g_nBinCount/*g_nBinCount*/; i++)
	{
		pToolBtn = new QToolButton;
		m_oBinInToolBtnList.append(pToolBtn);
	}

	//电流通道数固定为1
//	for (int i=0;i<g_oLocalSysPara.m_nCHINum;i++)
	{
		pToolBtn = new QToolButton;
		m_IInfoList.append(pToolBtn);
	}

	//从资源中取得模拟的开出数
	for(int i=0; i<g_nBoutCount/*g_nBoutCount*/; i++)
	{
		pToolBtn = new QToolButton;
		m_oBinOutToolBtnList.append(pToolBtn);
	}

	UpdateToolButtons();

	QHBoxLayout *layout = new QHBoxLayout;
	layout->setSpacing(0);
	layout->addWidget(m_Run);
	layout->addWidget(m_DCurrent);

	layout->addSpacing(5);
	for(int i=0; i<m_oBinInToolBtnList.size(); i++)
	{
		layout->addWidget(m_oBinInToolBtnList.at(i));
	}

	layout->addSpacing(5);
	for (int i=0;i<m_IInfoList.size();i++)
	{
		layout->addWidget(m_IInfoList.at(i));
	}
	layout->addWidget(m_V);
	layout->addWidget(m_OH);
	layout->addSpacing(5);

	for(int i=0; i<m_oBinOutToolBtnList.size(); i++)
	{
		layout->addWidget(m_oBinOutToolBtnList.at(i));
	}

	QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	layout->addItem(horizontalSpacer);
	layout->setContentsMargins(0,0,0,0);
	w1->setLayout(layout);
	m_DockSwitch->setWidget(w1);  

	addDockWidget(Qt::BottomDockWidgetArea,m_DockSwitch);
	//addDockWidget(Qt::BottomDockWidgetArea,m_DockStaInfo);// mym 2021-8-21 注销
	tabifyDockWidget(m_DockSwitch,m_DockStaInfo);
// 
 	/*m_DockStaInfo*/m_DockSwitch->show();		//20210926 sf 打开页面显示状态灯
 	/*m_DockStaInfo*/m_DockSwitch->raise();
}

void TestWinBase::AddInitRecord(QString strInfo)
{
	AddRecord(QColor("black"),strInfo);
}

void TestWinBase::AddRecord(QColor color, QString description )
{
	if (m_TextEditStaInfo == NULL)
		return;

 	m_TextEditStaInfo->setTextColor(color);

 	QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
 	time += "      ";
 	time += description;
 
 	m_TextEditStaInfo->append(time);

  	QTextCursor cursor = m_TextEditStaInfo->textCursor();     
  	cursor.movePosition(QTextCursor::End);     
  	m_TextEditStaInfo->setTextCursor(cursor);
}

void TestWinBase::InitXLanguage()
{
	_P_InitSystemPath();

// 	CSttSystemConfigXmlRWKeys::Create();
// 	CMacroXmlKeys::Create();
// 	CDataMngrXmlRWKeys::Create();
// 	CSttCmdDefineXmlRWKeys::Create();
// 	CCfgDataMngrXmlRWKeys::Create();
// 
// 	CCfgDataMngrConstGlobal::Create();
// 	CFilterTextXmlRWKeys::Create();
// 	CSttCmdOverTimeTool::Create();
// 	CDeviceModelXmlKeys::Create();

	CXLanguageXmlRWKeys::Create();
	CXLanguageMngr::Create(new CXLangResource_PowerTestWin(), TRUE);
}

void TestWinBase::ReleaseXLanguage()
{
//	ReleaseXmlKeys();
	CXLanguageMngr::Release();
	CXLanguageXmlRWKeys::Release();
}

void TestWinBase::UpdateToolButtons()
{
#ifdef STT_USE_Resource_Img_
	if (m_bViewTestStarted)
	{
		initToolbutton(m_Run,"Run",QString(":/images/SwitchIcon/run.png"));
	}
	else
	{
		initToolbutton(m_Run,"Run",QString(":/images/SwitchIcon/shutoff.png"));
	}

	if (m_oCurrEventResult.m_nUdc != 0)
	{
		initToolbutton(m_DCurrent,"Udc",QString(":/images/SwitchIcon/run.png"));
	}
	else
	{
		initToolbutton(m_DCurrent,"Udc",QString(":/images/SwitchIcon/shutoff.png"));
	}

// 	//开入（最多10个）
// 	char strName[MAX_BINARYIN_COUNT] = "ABCDEFGHIJKLMNOP";		
// 	for(int i=0; i<m_oBinInToolBtnList.size(); i++)
// 	{
// 		if (m_oBinaryConfig.m_binIn[i].nSelect)
// 		{
// 			if (m_oCurrEventResult.m_BinIn[i] != 0)
// 			{
// 				initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString(":/images/SwitchIcon/switch_close.png"));
// 			}
// 			else
// 			{
// 				initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString(":/images/SwitchIcon/switch_open.png"));
// 			}
// 		}
// 		else
// 		{
// 			initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString(":/images/SwitchIcon/switch_null.png"));
// 		}	
// 	}

	//开出
	for(int i=0; i<m_oBinOutToolBtnList.size(); i++)
	{
		if (m_oCurrEventResult.m_BinOut[i] != 0 && m_bViewTestStarted)
		{
			initToolbutton(m_oBinOutToolBtnList.at(i),QString::number(i+1,10),QString(":/images/SwitchIcon/switch_close.png"));
		}
		else
		{
			initToolbutton(m_oBinOutToolBtnList.at(i),QString::number(i+1,10),QString(":/images/SwitchIcon/switch_open.png"));
		}
	}



#else
	if (m_bViewTestStarted)
	{
		initToolbutton(m_Run,"Run",QString("./images/SwichIcon/run.png"));
	}
	else
	{
		initToolbutton(m_Run,"Run",QString("./images/SwichIcon/shutoff.png"));
	}

	if (m_oCurrEventResult.m_nUdc != 0)
	{
		initToolbutton(m_DCurrent,"Udc",QString("./images/SwichIcon/run.png"));
	}
	else
	{
		initToolbutton(m_DCurrent,"Udc",QString("./images/SwichIcon/shutoff.png"));
	}

	//开入（最多10个）
// 	char strName[MAX_BINARYIN_COUNT] = "ABCDEFGHIJKLMNOP";		
// 	for(int i=0; i<m_oBinInToolBtnList.size(); i++)
// 	{
// 		if (m_oBinaryConfig.m_binIn[i].nSelect)
// 		{
// 			if (m_oCurrEventResult.m_BinIn[i] != 0)
// 			{
// 				initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString("./images/SwichIcon/switch_close.png"));
// 			}
// 			else
// 			{
// 				initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString("./images/SwichIcon/switch_open.png"));
// 			}
// 		}
// 		else
// 		{
// 			initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString("./images/SwichIcon/switch_null.png"));
// 		}	
// 	}

	//开出
	for(int i=0; i<m_oBinOutToolBtnList.size(); i++)
	{
		if (m_oCurrEventResult.m_BinOut[i] != 0 && m_bViewTestStarted)
		{
			initToolbutton(m_oBinOutToolBtnList.at(i),QString::number(i+1,10),QString("./images/SwichIcon/switch_close.png"));
		}
		else
		{
			initToolbutton(m_oBinOutToolBtnList.at(i),QString::number(i+1,10),QString("./images/SwichIcon/switch_open.png"));
		}
	}

//	CSttTestEngineClientData *pClientEngine = g_oSttTestAppConfigTool.m_pClientEngine;



#endif

	signalIBreak_UOverLoad_OverHeat();
	signalBinInToolBtn();
	//电流开路
// 	QStringList oList;
// 	GetAnalogUIStringList(oList,Moudle_I);
// 	long nNum = min(oList.size(),m_IInfoList.size()) ; 
// 	bool bIBreak = false;
// 
// 	for (int j=0;j<MAX_CURRENT_COUNT;j++)
// 	{
// 		if (m_oCurrEventResult.m_IBreak[j] != 0)
// 		{
// 			bIBreak = true;
// 			break;
// 		}
// 	}

//	for(int i=0; i<nNum; i++)
// 	{
// 		if (bIBreak)
// 		{
// 			initToolbutton(m_IInfoList.at(i),/*oList.at(i)*/"I",QString("./images/SwichIcon/circle_yellow.png"));
// 		}
// 		else
// 		{
// 			initToolbutton(m_IInfoList.at(i),/*oList.at(i)*/"I",QString("./images/SwichIcon/circle_red.png"));
// 		}
// 	}
// 
// 	if (m_oCurrEventResult.m_nUShort != 0)
// 	{
// 		initToolbutton(m_V,"U",QString("./images/SwichIcon/circle_yellow.png"));
// 	}
// 	else
// 	{
// 		initToolbutton(m_V,"U",QString("./images/SwichIcon/circle_red.png"));
// 	}
// 
// 	if (m_oCurrEventResult.m_nOverHeat != 0)
// 	{
// 		initToolbutton(m_OH,"OH",QString("./images/SwichIcon/circle_yellow.png"));
// 	}
// 	else
// 	{
// 		initToolbutton(m_OH,"OH",QString("./images/SwichIcon/circle_red.png"));
// 	}
}

void TestWinBase::createActions()
{
	CreateActions(TRUE,TRUE,TRUE);
	
}

void TestWinBase::CreateActions(BOOL bHasCommonParas,BOOL bHasSetting,BOOL bHasReport,BOOL bHasSwitchs)
{
	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

#ifdef STT_USE_Resource_Img_
	m_startAct = new QAction(QIcon(":/images/start.png"), tr("开始测试"),this);
	m_manuTrigerAct = new QAction(QIcon(":/images/manuTriger.png"), tr("手动触发"),this);
	m_stopAct = new QAction(QIcon(":/images/stop.png"), tr("停止测试"),this);

#else

	m_startAct = new QAction(QIcon("./images/start.png"), tr("开始测试"),this);
	m_manuTrigerAct = new QAction(QIcon("./images/manuTriger.png"), tr("手动触发"),this);
	m_stopAct = new QAction(QIcon("./images/stop.png"), tr("停止测试"),this);

#endif

	m_startAct->setStatusTip(tr("开始测试(F2)"));
	connect(m_startAct, SIGNAL(triggered()), this, SLOT(slot_start()));

	m_manuTrigerAct->setStatusTip(tr("手动触发"));
	connect(m_manuTrigerAct, SIGNAL(triggered()), this, SLOT(slot_manuTriger()));
	m_manuTrigerAct->setDisabled(true);

	m_stopAct->setStatusTip(tr("停止测试(Esc)"));
	connect(m_stopAct, SIGNAL(triggered()), this, SLOT(slot_stop()));

	//文件
#ifdef STT_USE_Resource_Img_
	m_openAct = new QAction(QIcon(":/images/open.png"), tr("打开模板文件"),this);
	m_saveAct = new QAction(QIcon(":/images/save.png"), tr("保存模板文件"),this);
	m_saveAsAct = new QAction(QIcon(":/images/saveAs.png"), tr("模板另存为"),this);
#else

	m_openAct = new QAction(QIcon("./images/open.png"), tr("打开模板文件"),this);
	m_saveAct = new QAction(QIcon("./images/save.png"), tr("保存模板文件"),this);
	m_saveAsAct = new QAction(QIcon("./images/saveAs.png"), tr("模板另存为"),this);
#endif

	m_openAct->setShortcuts(QKeySequence::Open);
	m_openAct->setStatusTip(tr("打开模板文件"));
	connect(m_openAct, SIGNAL(triggered()), this, SLOT(slot_openTestParas()));

	m_saveAct->setShortcuts(QKeySequence::Save);
	m_saveAct->setStatusTip(tr("保存模板文件"));
	connect(m_saveAct, SIGNAL(triggered()), this, SLOT(slot_saveTestParas()));

	m_saveAsAct->setShortcuts(QKeySequence::SaveAs);
	m_saveAsAct->setStatusTip(tr("模板另存为"));
	connect(m_saveAsAct, SIGNAL(triggered()), this, SLOT(slot_saveAsTestParas()));

	//设置
#ifdef STT_USE_Resource_Img_
	m_setSysAct = new QAction(QIcon(":/images/Sys.png"), tr("系统参数"),this);

	if (bHasCommonParas)
	{
		m_setCommonAct = new QAction(QIcon(":/images/setCommon.png"), tr("通用参数"),this);
	}

	if (bHasSetting)
	{
		m_setSettingAct = new QAction(QIcon(":/images/setSetting.png"), tr("整定值"),this);
	}

	if (bHasSwitchs)
	{
		m_setSwitchAct = new QAction(QIcon(":/images/setSwitch.png"), tr("开关量"),this);
	}
	m_Connect = new QAction(QIcon(":/images/Netset.png"), tr("网络连接"),this);
	m_pChRsMaps_Action = new QAction(QIcon(":/images/Sys.png"), tr("通道映射"),this);
	m_pAuxDC_Action = new QAction(QIcon(":/images/Sys.png"), tr("直流设置"),this);
	m_pModulesGearSwitch_Action = new QAction(QIcon(":/images/Sys.png"), tr("输出功率"),this);
	m_pLuminousPower_Action=new QAction(QIcon(":/images/Sys.png"), tr("光功率"),this);
	m_IECAct = new QAction(QIcon(":/images/IEC.png"), tr("IEC"),this);
	m_OffLineSel_Action = new QAction(QIcon(":/images/Sys.png"), tr("脱机选择"),this);

	if (pSttDevConfig->m_nSelSteadyOutput)
	{
		m_setCustomAct = new QAction(QIcon(":/images/Dc.png"), tr("稳态输出"),this);
	}

	if (pSttDevConfig->m_nSelSOE_Test)
	{
		m_soeTestAct = new QAction(QIcon(":/images/Library.png"), tr("SOE测试"),this);
	}
#else

	m_setSysAct = new QAction(QIcon("./images/Sys.png"), tr("系统参数"),this);

	if (bHasCommonParas)
	{
		m_setCommonAct = new QAction(QIcon("./images/setCommon.png"), tr("通用参数"),this);
	}

	if (bHasSetting)
	{
		m_setSettingAct = new QAction(QIcon("./images/setSetting.png"), tr("整定值"),this);
	}

	if (bHasSwitchs)
	{
		m_setSwitchAct = new QAction(QIcon("./images/setSwitch.png"), tr("开关量"),this);
	}
	m_Connect = new QAction(QIcon("./images/Netset.png"), tr("网络连接"),this);
	m_pChRsMaps_Action = new QAction(QIcon("./images/Sys.png"), tr("通道映射"),this);
	m_pAuxDC_Action = new QAction(QIcon("./images/Sys.png"), tr("直流设置"),this);
	m_pModulesGearSwitch_Action = new QAction(QIcon("./images/Sys.png"), tr("输出功率"),this);
	m_pLuminousPower_Action=new QAction(QIcon("./images/Sys.png"), tr("光功率"),this);
	m_IECAct = new QAction(QIcon("./images/IEC.png"), tr("IEC"),this);
	m_OffLineSel_Action = new QAction(QIcon("./images/Sys.png"), tr("脱机选择"),this);

	if (pSttDevConfig->m_nSelSteadyOutput)
	{
		m_setCustomAct = new QAction(QIcon("./images/Dc.png"), tr("稳态输出"),this);
	}

	if (pSttDevConfig->m_nSelSOE_Test)
	{
		m_soeTestAct = new QAction(QIcon("./images/Library.png"), tr("SOE测试"),this);
	}
#endif

	m_setSysAct->setStatusTip(tr("型号参数配置"));
	connect(m_setSysAct, SIGNAL(triggered()), this, SLOT(slot_setSys()));

	if (bHasCommonParas)
	{
		m_setCommonAct->setStatusTip(tr("通用参数设置对话框"));
		connect(m_setCommonAct, SIGNAL(triggered()), this, SLOT(slot_setCommon()));
	}

	if (bHasSetting)
	{
		m_setSettingAct->setStatusTip(tr("整定值参数设置对话框"));
		m_setSettingAct->setDisabled(false);
		connect(m_setSettingAct, SIGNAL(triggered()), this, SLOT(slot_setSetting()));
	}

	if (bHasSwitchs)
	{
		m_setSwitchAct->setStatusTip(tr("开关量设置对话框"));
		connect(m_setSwitchAct, SIGNAL(triggered()), this, SLOT(slot_setSwitch()));
	}
	

	m_Connect->setStatusTip(tr("网络连接对话框"));
	connect(m_Connect, SIGNAL(triggered()), this, SLOT(slot_connect()));

	m_pChRsMaps_Action->setStatusTip(tr("通道资源映射对话框"));
	connect(m_pChRsMaps_Action, SIGNAL(triggered()), this, SLOT(slot_ChRsMaps_Dlg()));

	m_pAuxDC_Action->setStatusTip(tr("辅助直流设置对话框"));
	connect(m_pAuxDC_Action, SIGNAL(triggered()), this, SLOT(slot_AuxDC_Dlg()));

	m_pModulesGearSwitch_Action->setStatusTip(tr("输出功率设置对话框"));
	connect(m_pModulesGearSwitch_Action, SIGNAL(triggered()), this, SLOT(slot_ModulesGearSwitch_Dlg()));

	m_pLuminousPower_Action->setStatusTip(tr("光功率"));
	connect(m_pLuminousPower_Action, SIGNAL(triggered()), this, SLOT(slot_LuminousPower_Dlg()));

	m_IECAct->setStatusTip(tr("IEC报文设置"));
	connect(m_IECAct, SIGNAL(triggered()), this, SLOT(slot_IEC()));

	m_OffLineSel_Action->setStatusTip(tr("脱机选择测试仪型号、SN"));
	connect(m_OffLineSel_Action, SIGNAL(triggered()), this, SLOT(slot_OffLineSel()));


	if (pSttDevConfig->m_nSelSteadyOutput)
	{
		m_setCustomAct->setStatusTip(tr("交直流稳态输出"));
		connect(m_setCustomAct, SIGNAL(triggered()), this, SLOT(slot_setCustom()));
	}

	if (pSttDevConfig->m_nSelSOE_Test)
	{
		m_soeTestAct->setStatusTip(tr("SOE测试"));
		connect(m_soeTestAct, SIGNAL(triggered()), this, SLOT(slot_soeTest()));
	}

	//报告
	//2022.5.18 caoxc
	//if (bHasReport)
	{
#ifdef STT_USE_Resource_Img_
		m_reportSetAct = new QAction(QIcon(":/images/reportSet.png"), tr("报告设置"),this);
		m_reportSaveAct = new QAction(QIcon(":/images/reportExport.png"), tr("导出报告"),this);
#else
		m_reportSetAct = new QAction(QIcon("./images/reportSet.png"), tr("报告设置"),this);
		m_reportSaveAct = new QAction(QIcon("./images/reportExport.png"), tr("导出报告"),this);
		
#endif
		m_reportSetAct->setStatusTip(tr("报告参数设置"));
		connect(m_reportSetAct, SIGNAL(triggered()), this, SLOT(slot_reportSet()));

		/*	
		m_reportViewAct = new QAction(QIcon("./images/OpenFile.png"), tr("报告浏览"),this);
		m_reportViewAct->setStatusTip(tr("报告浏览"));
		connect(m_reportViewAct, SIGNAL(triggered()), this, SLOT(slot_viewReport()));
		m_reportOpenAct = new QAction(QIcon("./images/OpenFile.png"), tr("打开报告"),this);
		m_reportOpenAct->setStatusTip(tr("打开报告"));
		connect(m_reportOpenAct, SIGNAL(triggered()), this, SLOT(slot_reportOpen()));
		*/
	
		m_reportSaveAct->setStatusTip(tr("导出报告"));
		connect(m_reportSaveAct, SIGNAL(triggered()), this, SLOT(slot_reportSave()));
	}

	//视图
#ifdef STT_USE_Resource_Img_

	m_viewTestAct = new QAction(QIcon(":/images/Power.png"), tr("&试验视图"),this);
	m_viewReportAct = new QAction(QIcon(":/images/reportView.png"), tr("&报告视图"),this);
	m_viewDockSwitchAct = new QAction(QIcon(":/images/switchView.png"), tr("&状态灯视图"),this);
	m_viewDockStaInfoAct = new QAction(QIcon(":/images/History.png"), tr("&状态历史视图"),this);
	m_VersionInforAct = new QAction(QIcon(":/images/LocalUpdate.png"), tr("&版本信息"),this);	
	m_updateLocalAct = new QAction(QIcon(":/images/LocalUpdate.png"), tr("&更新软件"),this);	
	m_updateTestAppAct = new QAction(QIcon(":/images/TestAppUpdate.png"), tr("&更新底层"),this);
#else


	m_viewTestAct = new QAction(QIcon("./images/Power.png"), tr("&试验视图"),this);
	m_viewReportAct = new QAction(QIcon("./images/reportView.png"), tr("&报告视图"),this);
	m_viewDockSwitchAct = new QAction(QIcon("./images/switchView.png"), tr("&状态灯视图"),this);
	m_viewDockStaInfoAct = new QAction(QIcon("./images/History.png"), tr("&状态历史视图"),this);
	m_VersionInforAct = new QAction(QIcon("./images/LocalUpdate.png"), tr("&版本信息"),this);	
	m_updateLocalAct = new QAction(QIcon("./images/LocalUpdate.png"), tr("&更新软件"),this);	
	m_updateTestAppAct = new QAction(QIcon("./images/TestAppUpdate.png"), tr("&更新底层"),this);
#endif


	m_viewTestAct->setStatusTip(tr("显示试验视图"));
	connect(m_viewTestAct, SIGNAL(triggered()), this, SLOT(slot_viewTest()));

	m_viewReportAct->setStatusTip(tr("显示报告视图"));
	connect(m_viewReportAct, SIGNAL(triggered()), this, SLOT(slot_viewReport()));

	m_viewDockSwitchAct->setStatusTip(tr("显示状态灯视图"));
	m_viewDockSwitchAct->setCheckable(true);
	m_viewDockSwitchAct->setChecked(false);
	connect(m_viewDockSwitchAct, SIGNAL(triggered()), this, SLOT(slot_viewDockSwichEx()));

	m_viewDockStaInfoAct->setStatusTip(tr("显示状态历史视图"));
	m_viewDockStaInfoAct->setCheckable(true);
	m_viewDockStaInfoAct->setChecked(true);
	connect(m_viewDockStaInfoAct, SIGNAL(triggered()), this, SLOT(slot_viewDockStaInfoEx()));

	//版本更新
	m_VersionInforAct->setStatusTip(tr("当前测试仪版本信息"));
	connect(m_VersionInforAct, SIGNAL(triggered()), this, SLOT(slot_versionInformation()));

	m_updateLocalAct->setStatusTip(tr("更新上位机软件"));
	connect(m_updateLocalAct, SIGNAL(triggered()), this, SLOT(slot_localUpdate()));

	m_updateTestAppAct->setStatusTip(tr("更新测试仪底层程序"));
	connect(m_updateTestAppAct, SIGNAL(triggered()), this, SLOT(slot_testAppUpdate()));

	this->setFocusPolicy(Qt::StrongFocus);
}

void TestWinBase::CreateAction_IecCap()
	{
#ifdef STT_USE_Resource_Img_
		m_IECCapAct = new QAction(QIcon(":/images/IEC.png"), tr("报文探测"),this);
#else
		m_IECCapAct = new QAction(QIcon("./images/IEC.png"), tr("报文探测"),this);
#endif
		m_IECCapAct->setStatusTip(tr("报文探测"));
		connect(m_IECCapAct, SIGNAL(triggered()), this, SLOT(slot_IECCap()));

	}


void TestWinBase::createMenus()
{
	CreateMenus(TRUE,TRUE,TRUE);
}

void TestWinBase::CreateMenus(BOOL bHasCommonParas,BOOL bHasSetting,BOOL bHasReport,BOOL bHasSwitchs)
{
	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	m_headerMenu = menuBar()->addMenu(tr("文件"));
	m_headerMenu->addSeparator();
	m_headerMenu->addAction(m_openAct);
	m_headerMenu->addAction(m_saveAct);
	m_headerMenu->addAction(m_saveAsAct);
	m_headerMenu->addSeparator();

	m_setMenu = menuBar()->addMenu(tr("设置"));
	m_setMenu->addAction(m_setSysAct);

	if (bHasCommonParas)
	{
		m_setMenu->addAction(m_setCommonAct);
	}

	if (bHasSetting)
	{
		m_setMenu->addAction(m_setSettingAct);
	}

	if (bHasSwitchs)
	{
		m_setMenu->addAction(m_setSwitchAct);
	}
	
	if (pSttDevConfig->m_nSelSteadyOutput)
		m_setMenu->addAction(m_setCustomAct);

	if (pSttDevConfig->m_nSelSOE_Test)
		m_setMenu->addAction(m_soeTestAct);


	if (m_IECCapAct != NULL)
	{
		m_setMenu->addAction(m_IECCapAct);
	}

	m_setMenu->addAction(m_IECAct);
	m_setMenu->addAction(m_Connect);
	m_setMenu->addAction(m_pChRsMaps_Action);
	m_setMenu->addAction(m_pAuxDC_Action);
	m_setMenu->addAction(m_pModulesGearSwitch_Action);
	m_setMenu->addAction(m_pLuminousPower_Action);
	m_setMenu->addAction(m_OffLineSel_Action);
	
//	if (bHasReport)
//	{
//		m_setMenu->addAction(m_reportSetAct);
////		m_reportMenu->addAction(m_reportOpenAct);
////		m_reportMenu->addAction(m_reportSaveAct);
//	}

	// 2022.5.17 caoxc
	m_reportMenu = menuBar()->addMenu(tr("报告"));
	m_reportMenu->addAction(m_reportSetAct);
//		m_reportMenu->addAction(m_reportOpenAct);
	m_reportMenu->addAction(m_reportSaveAct);
	//m_viewMenu->addAction(m_viewDockSwitchAct);
	//m_viewMenu->addAction(m_viewDockStaInfoAct);

	m_viewMenu = menuBar()->addMenu(tr("视图"));
	m_viewMenu->addSeparator();
	m_viewMenu->addAction(m_viewDockSwitchAct);
	m_viewMenu->addAction(m_viewDockStaInfoAct);

	m_verMenu = menuBar()->addMenu(tr("版本"));
	m_verMenu->addAction(m_VersionInforAct);
	m_verMenu->addAction(m_updateLocalAct);
	m_verMenu->addAction(m_updateTestAppAct);
}

void TestWinBase::createToolBar()
{
	CreateToolBar(TRUE,TRUE,TRUE,TRUE);
}

void TestWinBase::CreateToolBar(BOOL bHasManualTrigger,BOOL bHasCommonParas,BOOL bHasSetting,BOOL bHasReport,BOOL bHasSwitchs,BOOL bIecCap,BOOL bAuxDC,BOOL bHasChRsMaps)
{
	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	m_headerToolBar = addToolBar(tr("开始"));

#ifdef STT_USE_Resource_Img_

	m_pStartBtn = addToolButton(QString(tr("开始测试")),QString(":/images/start.png"),QString(tr("开始测试(F2)")));

	if (bHasManualTrigger)
	{
		m_pManuTrigerBtn = addToolButton(QString(tr("手动触发")),QString(":/images/manuTriger.png"),QString(tr("手动触发")));
	}
	m_pStopBtn = addToolButton(QString(tr("停止测试")),QString(":/images/stop.png"),QString(tr("停止测试(Esc)")));


#else
	m_pStartBtn = addToolButton(QString(tr("开始测试")),QString("./images/start.png"),QString(tr("开始测试(F2)")));

	if (bHasManualTrigger)
	{
		m_pManuTrigerBtn = addToolButton(QString(tr("手动触发")),QString("./images/manuTriger.png"),QString(tr("手动触发")));
	}
	m_pStopBtn = addToolButton(QString(tr("停止测试")),QString("./images/stop.png"),QString(tr("停止测试(Esc)")));


#endif

	
	m_headerToolBar->addWidget(m_pStartBtn);
	connect(m_pStartBtn, SIGNAL(clicked()), this, SLOT(slot_start()));

	if (bHasManualTrigger)
	{
		m_headerToolBar->addWidget(m_pManuTrigerBtn);
		connect(m_pManuTrigerBtn, SIGNAL(clicked()), this, SLOT(slot_manuTriger()));
	}

	
	m_headerToolBar->addWidget(m_pStopBtn);
	connect(m_pStopBtn, SIGNAL(clicked()), this, SLOT(slot_stop()));
	m_pStopBtn->setDisabled(true);

	m_headerToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	//设置
	m_setToolBar = addToolBar(tr("设置"));

#ifdef STT_USE_Resource_Img_
	m_pSetSysBtn = addToolButton(QString(tr("系统参数")),QString(":/images/Sys.png"),QString(tr("系统参数配置对话框")));

	if (pSttDevConfig->m_nSelOffLine)
	{
		m_pOffLineSelBtn = addToolButton(QString(tr("脱机选择")),QString(":/images/Sys.png"),QString(tr("脱机选择测试仪型号、SN")));
	}
	if (bHasCommonParas)
	{
		m_pSetCommonBtn = addToolButton(QString(tr("通用参数")),QString(":/images/setCommon.png"),QString(tr("通用参数设置对话框")));

	}

	if (bHasSetting)
	{
		m_pSetSettingBtn = addToolButton(QString(tr("整定值")),QString(":/images/setSetting.png"),QString(tr("整定值参数设置对话框")));
	}

	if (bHasSwitchs)
	{
		m_pSetSwitchBtn = addToolButton(QString(tr("开关量")),QString(":/images/setSwitch.png"),QString(tr("开关量设置对话框")));
	}

	m_pIECBtn = addToolButton(QString(tr("IEC")),QString(":/images/IEC.png"),QString(tr("IEC")));

	if (bIecCap)
	{
		m_pIECCapBtn = addToolButton(QString(tr("报文探测")),QString(":/images/IEC.png"),QString(tr("报文探测")));
	}

	if(bAuxDC)
	{
		m_pAuxDCBtn = addToolButton(QString(tr("直流设置")),QString(":/images/Sys.png"),QString(tr("辅助直流设置对话框")));
	}

	if (pSttDevConfig->m_nSelSteadyOutput)
	{
		m_pSetCustomBtn = addToolButton(QString(tr("稳态输出")),QString(":/images/Dc.png"),QString(tr("交直流稳态输出")));
	}

	if (pSttDevConfig->m_nSelSOE_Test)
	{
		m_pSoeTestBtn = addToolButton(QString(tr("SOE测试")),QString(":/images/Library.png"),QString(tr("SOE测试")));
	}

	m_pConnectBtn = addToolButton(QString(tr("网络连接")),QString(":/images/Netset.png"),QString(tr("网络连接对话框")));
	if(bHasChRsMaps)
	{
		m_pChRsMapsBtn = addToolButton(QString(tr("通道映射")),QString(":/images/Sys.png"),QString(tr("通道资源映射对话框")));	
	}

	if (bHasReport)
	{
		m_pReportSetBtn = addToolButton(QString(tr("报告设置")),QString(":/images/reportSet.png"),QString(tr("报告设置")));	
	}
#else

	m_pSetSysBtn = addToolButton(QString(tr("系统参数")),QString("./images/Sys.png"),QString(tr("系统参数配置对话框")));

	if (pSttDevConfig->m_nSelOffLine)
	{
		m_pOffLineSelBtn = addToolButton(QString(tr("脱机选择")),QString("./images/Sys.png"),QString(tr("脱机选择测试仪型号、SN")));
	}
	if (bHasCommonParas)
	{
		m_pSetCommonBtn = addToolButton(QString(tr("通用参数")),QString("./images/setCommon.png"),QString(tr("通用参数设置对话框")));

	}

	if (bHasSetting)
	{
		m_pSetSettingBtn = addToolButton(QString(tr("整定值")),QString("./images/setSetting.png"),QString(tr("整定值参数设置对话框")));
	}

	if (bHasSwitchs)
	{
		m_pSetSwitchBtn = addToolButton(QString(tr("开关量")),QString("./images/setSwitch.png"),QString(tr("开关量设置对话框")));
	}
	
	m_pIECBtn = addToolButton(QString(tr("IEC")),QString("./images/IEC.png"),QString(tr("IEC")));

	if (bIecCap)
	{
		m_pIECCapBtn = addToolButton(QString(tr("报文探测")),QString("./images/IEC.png"),QString(tr("报文探测")));
	}

	if(bAuxDC)
	{
		m_pAuxDCBtn = addToolButton(QString(tr("直流设置")),QString("./images/Sys.png"),QString(tr("辅助直流设置对话框")));
	}

	if (pSttDevConfig->m_nSelSteadyOutput)
	{
		m_pSetCustomBtn = addToolButton(QString(tr("稳态输出")),QString("./images/Dc.png"),QString(tr("交直流稳态输出")));
	}

	if (pSttDevConfig->m_nSelSOE_Test)
	{
		m_pSoeTestBtn = addToolButton(QString(tr("SOE测试")),QString("./images/Library.png"),QString(tr("SOE测试")));
	}

	m_pConnectBtn = addToolButton(QString(tr("网络连接")),QString("./images/Netset.png"),QString(tr("网络连接对话框")));
	if(bHasChRsMaps)
	{
		m_pChRsMapsBtn = addToolButton(QString(tr("通道映射")),QString("./images/Sys.png"),QString(tr("通道资源映射对话框")));	
	}

	if (bHasReport)
	{
		m_pReportSetBtn = addToolButton(QString(tr("报告设置")),QString("./images/reportSet.png"),QString(tr("报告设置")));	
	}

#endif

	m_setToolBar->addWidget(m_pSetSysBtn);
	connect(m_pSetSysBtn, SIGNAL(clicked()), this, SLOT(slot_setSys()));

	if (pSttDevConfig->m_nSelOffLine)
	{
		m_setToolBar->addWidget(m_pOffLineSelBtn);
		connect(m_pOffLineSelBtn, SIGNAL(clicked()), this, SLOT(slot_OffLineSel()));
	}

	if (bHasCommonParas)
	{
		m_setToolBar->addWidget(m_pSetCommonBtn);
		connect(m_pSetCommonBtn, SIGNAL(clicked()), this, SLOT(slot_setCommon()));
	}

	if (bHasSetting)
	{
		m_setToolBar->addWidget(m_pSetSettingBtn);
		connect(m_pSetSettingBtn, SIGNAL(clicked()), this, SLOT(slot_setSetting()));
	}

	if (bHasSwitchs)
	{
		m_setToolBar->addWidget(m_pSetSwitchBtn);
		connect(m_pSetSwitchBtn, SIGNAL(clicked()), this, SLOT(slot_setSwitch()));
	}
	
	
	m_setToolBar->addWidget(m_pIECBtn);
	connect(m_pIECBtn, SIGNAL(clicked()), this, SLOT(slot_IEC()));

	if (bIecCap)
	{
		m_setToolBar->addWidget(m_pIECCapBtn);
		connect(m_pIECCapBtn, SIGNAL(clicked()), this, SLOT(slot_IECCap()));
	}
	
	if(bAuxDC)
	{
		m_setToolBar->addWidget(m_pAuxDCBtn);
		connect(m_pAuxDCBtn, SIGNAL(clicked()), this, SLOT(slot_AuxDC_Dlg()));
	}


	if (pSttDevConfig->m_nSelSteadyOutput)
	{
		m_setToolBar->addWidget(m_pSetCustomBtn);
		connect(m_pSetCustomBtn, SIGNAL(clicked()), this, SLOT(slot_setCustom()));
	}

	if (pSttDevConfig->m_nSelSOE_Test)
	{
		m_setToolBar->addWidget(m_pSoeTestBtn);
		connect(m_pSoeTestBtn, SIGNAL(clicked()), this, SLOT(slot_soeTest()));
	}

	m_setToolBar->addWidget(m_pConnectBtn);
	connect(m_pConnectBtn, SIGNAL(clicked()), this, SLOT(slot_connect()));

	if(bHasChRsMaps)
	{
	m_setToolBar->addWidget(m_pChRsMapsBtn);
	connect(m_pChRsMapsBtn, SIGNAL(clicked()), this, SLOT(slot_ChRsMaps_Dlg()));
	}

	if (bHasReport)
	{
		m_setToolBar->addWidget(m_pReportSetBtn);
		connect(m_pReportSetBtn, SIGNAL(clicked()), this, SLOT(slot_reportSet()));
	}

	m_setToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	
	//视图
	m_viewToolBar = addToolBar(tr("视图"));
#ifdef STT_USE_Resource_Img_
	m_pViewTestBtn = addToolButton(QString(tr("试验视图")),QString(":/images/Power.png"),QString(tr("显示试验视图")));
	m_pViewReportBtn = addToolButton(QString(tr("报告视图")),QString(":/images/reportView.png"),QString(tr("显示报告视图")));

#else
	m_pViewTestBtn = addToolButton(QString(tr("试验视图")),QString("./images/Power.png"),QString(tr("显示试验视图")));
	m_pViewReportBtn = addToolButton(QString(tr("报告视图")),QString("./images/reportView.png"),QString(tr("显示报告视图")));

#endif

	m_viewToolBar->addWidget(m_pViewTestBtn);
	m_pViewTestBtn->setStyleSheet("QToolButton { ""background-color:rgb(240,255,255);" "}");

	connect(m_pViewTestBtn, SIGNAL(clicked()), this, SLOT(slot_viewTest()));

	m_viewToolBar->addWidget(m_pViewReportBtn);
	connect(m_pViewReportBtn, SIGNAL(clicked()), this, SLOT(slot_viewReport()));

	m_viewToolBar->addSeparator();

// 	m_pDockSwitchBtn = addToolButton(QString(tr("状态灯视图")),QString("./images/switchView.png"),QString(tr("显示状态灯视图")));
// 	m_viewToolBar->addWidget(m_pDockSwitchBtn);
// 	m_pDockSwitchBtn->setCheckable(true);
// 	m_pDockSwitchBtn->setChecked(/*false*/true);	//sf 20210926 打开显示状态灯
// 	connect(m_pDockSwitchBtn, SIGNAL(clicked()), this, SLOT(slot_viewDockSwich()));

// 	m_pDockStaInfoBtn = addToolButton(QString(tr("状态历史视图")),QString("./images/History.png"),QString(tr("显示状态历史视图")));
// 	m_viewToolBar->addWidget(m_pDockStaInfoBtn);
// 	m_pDockStaInfoBtn->setCheckable(true);
// 	m_pDockStaInfoBtn->setChecked(/*true*/false);	//sf 20210926 打开显示状态灯
// 	connect(m_pDockStaInfoBtn, SIGNAL(clicked()), this, SLOT(slot_viewDockStaInfo()));

	m_viewToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void TestWinBase::createStatusBar()
{
	m_LabIconGps = new QLabel;
#ifdef STT_USE_Resource_Img_
	m_LabIconGps->setPixmap(QPixmap(":/images/gps2.png"));
#else

	m_LabIconGps->setPixmap(QPixmap("./images/gps2.png"));
#endif
	QFontMetrics fontMetrics = QFontMetrics(font());
	int nLabelWidth = fontMetrics.width(tr("1970年1月1日 00:00:00")) + 20;

	m_LabVersion = new QLabel;

	CString strExeDateTime,strTmp;
	strTmp = __DATE__;
	strExeDateTime = _T("Version:6.4_");
	strExeDateTime += Global_GetSoftwareGeneVersion(strTmp);
// 	strExeDateTime += " ";
// 	strExeDateTime += __TIME__;
//	strExeDateTime += ") ";

	m_LabVersion->setText(strExeDateTime);

	m_LabLinkTxt = new QLabel;
	m_LabLinkTxt->setStyleSheet(" QLabel{ color: black }");
	QString strLink = tr("连接状态：");
	nLabelWidth = fontMetrics.width(strLink) + 5;
	m_LabLinkTxt->setFixedWidth(nLabelWidth);
	m_LabLinkTxt->setText(strLink);

	m_LabLinkIcon = new QLabel;
#ifdef STT_USE_Resource_Img_
	m_LabLinkIcon->setPixmap(QPixmap(":/images/circle_black.png"));
#else
	m_LabLinkIcon->setPixmap(QPixmap("./images/circle_black.png"));
#endif
// 	QDate buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " " ), "MMM dd yyyy");
// 	QString srtr = QString( __DATE__ );
// 	if (srtr.mid(4,1)==" ")
// 	{
// 		buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " " ), "MMM d yyyy");
// 	}
// 	else
// 	{
// 		buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " " ), "MMM dd yyyy");
// 	}

	m_LabVer = new QLabel;
	m_LabVer->setStyleSheet(" QLabel{ color: red }");
	QString strVer = tr("未对时")/* + buildDate.toString("yyyyMMdd")*/;
	nLabelWidth = fontMetrics.width(strVer) + 5;
	m_LabVer->setFixedWidth(nLabelWidth);
	m_LabVer->setText(strVer);
	m_LabVer->setToolTip(tr("对时"));

	statusBar()->addPermanentWidget(m_LabVersion);
	statusBar()->addPermanentWidget(m_LabLinkTxt);
	statusBar()->addPermanentWidget(m_LabLinkIcon);
	statusBar()->addPermanentWidget(m_LabVer);
	statusBar()->addPermanentWidget(m_LabIconGps);
	statusBar()->showMessage(tr("Ready"));
}

// void TestWinBase::OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend)
// {
// 	emit sig_OnUpdateGpsTime(nSyn,nSecond,nNSecend);
// }

void TestWinBase::slot_OnUpdateRtSyncTime(CDataGroup *pRtSycTime)
{
	long nSecond = 0,nNSecend = 0,nTimeZone = 0,nSyn = 0;
	CString strTime;
	strTime = _T("");
	stt_GetDataValueByID(pRtSycTime, _T("Sync"), nSyn);
	stt_GetDataValueByID(pRtSycTime, _T("Utc_s"), nSecond);
	stt_GetDataValueByID(pRtSycTime, _T("Utc_ns"), nNSecend);
	stt_GetDataValueByID(pRtSycTime, _T("TimeZone"), nTimeZone);//zhouhj 20230613 补偿时区差
	stt_GetDataValueByID(pRtSycTime, _T("CurDate"), strTime);
	slot_OnUpdateGpsTime(nSyn,nSecond + nTimeZone,nNSecend,strTime);//增加时区补偿,zhouhj 20230616

	if(m_bViewTestStarted && m_pTimeResponseWidget)
	{
		double dLocalTime = nSecond + nTimeZone*60*60 + nNSecend * 0.000000001;
		m_pTimeResponseWidget->UpdateLocalTime(dLocalTime);
	}

	//chenling 20230412	
	POS pos=pRtSycTime->GetHeadPosition();
	CDataGroup *pFiberMsgGroup=NULL;
	CExBaseObject *pCurrObj = NULL;
	g_oSttTestResourceMngr.m_oFiberMsgGroup.DeleteAll();

	while (pos)
	{
		pCurrObj = pRtSycTime->GetNext(pos);

		if (pCurrObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pFiberMsgGroup = (CDataGroup *)pCurrObj;
		if (pFiberMsgGroup->m_strDataType=="LightPower")
		{		
			pRtSycTime->Remove(pCurrObj);
			POS pos2 = pFiberMsgGroup->GetHeadPosition();
			CExBaseObject * pData = NULL;

			while(pos2)
			{
				pData = (CExBaseObject *)pFiberMsgGroup->GetNext(pos2);	
				g_oSttTestResourceMngr.m_oFiberMsgGroup.AddNewChild(pData);
			}

		}
	}

	delete pRtSycTime;
}

void TestWinBase::slot_OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend, QString strTime)
{
	if (nSyn != g_oLocalSysPara.m_nHasSyn)
	{
 		g_oLocalSysPara.m_nHasSyn = nSyn;
 
 		if (g_oLocalSysPara.m_nHasSyn == 0)
 		{
 			QFontMetrics fontMetrics = QFontMetrics(font());
 			m_LabVer->setStyleSheet(" QLabel{ color: red }");
 			QString strVer = tr("未对时");
 			int nLabelWidth = fontMetrics.width(strVer) + 5;
 			m_LabVer->setFixedWidth(nLabelWidth);
 			m_LabVer->setText(strVer);
#ifdef STT_USE_Resource_Img_
			m_LabIconGps->setPixmap(QPixmap(":/images/gps2.png"));

#else
 			m_LabIconGps->setPixmap(QPixmap("./images/gps2.png"));
#endif
 		} 
 		else
		{
			QFontMetrics fontMetrics = QFontMetrics(font());
			int nLabelWidth = fontMetrics.width(tr("1970年1月1日 00:00:00.000")) + 5;
			m_LabVer->setStyleSheet(" QLabel{ color: blue }");

			if (strTime.isEmpty())
			{
				m_LabVer->setText(QDateTime::fromTime_t(nSecond).toString("yyyy-MM-dd hh:mm:ss:")+QString("%1").arg((int)(nNSecend/1000000)));
			} 
			else
			{
				nLabelWidth = fontMetrics.width(tr("1970年1月1日 00:00:00")) + 5;
				m_LabVer->setText(strTime);
			}

			m_LabVer->setFixedWidth(nLabelWidth);
#ifdef STT_USE_Resource_Img_
			m_LabIconGps->setPixmap(QPixmap(":/images/gps.png"));
#else
			m_LabIconGps->setPixmap(QPixmap("./images/gps.png"));
#endif
			m_LabIconGps->show();
		}
	}
	else if (nSyn > 0 )
	{
		if (strTime.isEmpty())
		{
			m_LabVer->setText(QDateTime::fromTime_t(nSecond).toString("yyyy-MM-dd hh:mm:ss:")+QString("%1").arg((int)(nNSecend/1000000)));
		} 
		else
		{
			m_LabVer->setText(strTime);
		}
	}
}

void TestWinBase::setActionEnabled(ACTION_TYPE act,bool bEnable)
{	
//	bEnable = !bEnable;

	switch(act)
	{
	case ACTION_OPENTESTPARA:
		if(m_openAct){
			m_openAct->setEnabled(bEnable);
		}
		break;
	case ACTION_SAVETESTPARA:
		if(m_saveAct){
			m_saveAct->setEnabled(bEnable);
		}
		break;
	case ACTION_SAVEASTESTPARA:
		if(m_saveAsAct){
			m_saveAsAct->setEnabled(bEnable);
		}
		break;
	case ACTION_START:
		if(m_startAct && m_pStartBtn){
//			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ACTION_START(%d)"),bEnable);
			m_startAct->setEnabled(bEnable);
			m_pStartBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_MANUTRIGER:
		if(m_manuTrigerAct && m_pManuTrigerBtn){
			m_manuTrigerAct->setEnabled(bEnable);
			m_pManuTrigerBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_STOP:
		if(m_stopAct && m_pStopBtn){
			m_stopAct->setEnabled(bEnable);
			m_pStopBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_SYSTEMPARA:
		if(m_setSysAct && m_pSetSysBtn){
			m_setSysAct->setEnabled(bEnable);
			m_pSetSysBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_OFFLINE:
		if(/*m_setSysAct && */m_pOffLineSelBtn){
			//m_setSysAct->setEnabled(bEnable);
			m_pOffLineSelBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_COMMONPARA:
		if(m_setCommonAct && m_pSetCommonBtn)
		{
			m_setCommonAct->setEnabled(bEnable);
			m_pSetCommonBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_SETTING:
		if(m_setSettingAct && m_pSetSettingBtn)
		{
			m_setSettingAct->setEnabled(bEnable);
			m_pSetSettingBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_SETSWITCH:
		if(m_setSwitchAct && m_pSetSwitchBtn){
			m_setSwitchAct->setEnabled(bEnable);
			m_pSetSwitchBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_IEC:
		if(m_IECAct && m_pIECBtn){
			m_IECAct->setEnabled(bEnable);
			m_pIECBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_IECCap:
		if(m_IECCapAct && m_pIECCapBtn){
			m_IECCapAct->setEnabled(bEnable);
			m_pIECCapBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_AUXOUTPUT:
		if(m_setCustomAct && m_pSetCustomBtn){
			m_setCustomAct->setEnabled(bEnable);
			m_pSetCustomBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_SOETEST:
		if(m_soeTestAct && m_pSoeTestBtn){
			m_soeTestAct->setEnabled(bEnable);
			m_pSoeTestBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_NETSET:
		if(m_Connect && m_pConnectBtn){
			m_Connect->setEnabled(bEnable);
			m_pConnectBtn->setEnabled(bEnable);
		}
		break;

	case ACTION_CHRSMAPS:
		if (m_pChRsMaps_Action)
		{
			m_pChRsMaps_Action->setEnabled(bEnable);
		}

		if (m_pChRsMapsBtn)
		{
			m_pChRsMapsBtn->setEnabled(bEnable);
		}

		break;

	case ACTION_AUXDC:
		if (m_pAuxDC_Action)  //zhouhj 20220217 直流输出设置,不受当前测试仪是否在运行中限制
		{
			m_pAuxDC_Action->setEnabled(bEnable);
			if (m_pAuxDCBtn != NULL)
			{
				m_pAuxDCBtn->setEnabled(bEnable);//20240202chenling 运行时直流输出设置灰掉
			}
		}
		break;

	case ACTION_MODULESGEAERSWITCH:
		if (m_pModulesGearSwitch_Action)
		{
			m_pModulesGearSwitch_Action->setEnabled(bEnable);
		}

		break;

	case ACTION_SETREPORT:
		if (m_reportSetAct)
		{
			m_reportSetAct->setEnabled(bEnable);//20240222 suyang  m_pReportSetBtn没有new  所以分开写
		}

		if(m_pReportSetBtn)
		{
			
			m_pReportSetBtn->setEnabled(bEnable);
		}
		break;

	case ACTION_OPENREPORT:
		if (m_reportOpenAct){
			m_reportOpenAct->setEnabled(bEnable);
		}
		break;

	case ACTION_SAVEREPORT:
		if (m_reportSaveAct){
			m_reportSaveAct->setEnabled(bEnable);
		}
		break;

	case ACTION_VIEWSWITCH:
		if(m_viewDockSwitchAct/* && m_pDockSwitchBtn*/){
			m_viewDockSwitchAct->setEnabled(bEnable);
//			m_pDockSwitchBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_VIEWSTATINF:
		if(m_viewDockStaInfoAct/* && m_pDockStaInfoBtn*/){
			m_viewDockStaInfoAct->setEnabled(bEnable);
	//		m_pDockStaInfoBtn->setEnabled(bEnable);
		}
		break;
/*
	case ACTION_VIEWTEST:
		if(m_viewTestAct && m_pViewTestBtn){
			m_viewTestAct->setEnabled(bEnable);
			m_pViewTestBtn->setEnabled(bEnable);
		}
		break;
	case ACTION_VIEWREPORT:
		if(m_viewReportAct && m_pViewReportBtn){
			m_viewReportAct->setEnabled(bEnable);
			m_pViewReportBtn->setEnabled(bEnable);
		}
		break;
*/
	case ACTION_VERSIONINFOR:
		if(m_VersionInforAct){
			m_VersionInforAct->setEnabled(bEnable);
		}
		break;
	case ACTION_UPDATELOCAL:
		if(m_updateLocalAct){
			m_updateLocalAct->setEnabled(bEnable);
		}
		break;
	case ACTION_UPDATETESTAPP:
		if(m_updateTestAppAct){
			m_updateTestAppAct->setEnabled(bEnable);
		}
		break;
	}
}

void TestWinBase::setMonitorEnabled(MONITOR_TYPE mnt,bool bEnable)
{
	QTabWidget* pTab = m_testParaView->getMonitor()->GetTabWidget();
	int index = -1;

	switch(mnt)
	{
	case MONITOR_PLOT:

		if (m_pTimeResponseWidget != NULL)
		{
			index = pTab->indexOf(m_pTimeResponseWidget);
		}
		break;
	case MONITOR_VECTOR:
		index = pTab->indexOf(m_vectorWidget);
		break;
	case MONITOR_POWER:
		//index = pTab->indexOf(m_powerWidget);		
		index = pTab->indexOf(m_powerdiagramWidget);		
		break;
	case MONITOR_SEQUENCE:
		index = pTab->indexOf(m_seqWidget);
		break;
	case MONITOR_LINEVOLT:
		index = pTab->indexOf(m_lineVoltWidget);
		break;
	case MONITOR_INFO:
		index = pTab->indexOf(m_infoWidget);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("m_infoWidget%d"),index);
		break;
	case MONITOR_WAVE:

		if (m_pWaveWidget!= NULL)
		{
			index = pTab->indexOf(m_pWaveWidget);
		}
		break;
	}

	if (index == -1)
	{
		return;
	}

//	pTab->setTabEnabled(index,bEnable);

	if (bEnable)//zhouhj 20211022 增加判断
	{
		pTab->setCurrentIndex(index);
	} 
	else
	{
		pTab->removeTab(index);
	}
}

void TestWinBase::setTestParasEnabled(PARAS_TYPE para,bool bEnable)
{
	QTabWidget* pTab = m_testParaView->getMainPara()->m_tabWidget;
	int index = 0;

	switch (para)
	{
	case PARAS_TEST:
		index = pTab->indexOf(m_testParaView->getMainPara()->getTemplateWidget());
		break;
	case PARAS_GOOSE:
		index = pTab->indexOf(m_pGooseParaWidget);
		break;
	case PARAS_EXINPUTSET:
		index = pTab->indexOf(m_pExSwitchInputSetWidget);
		break;
	case PARAS_EXOUTPUTSET:
		index = pTab->indexOf(m_pExSwitchOutputSetWidget);
		break; 
	}

	pTab->setTabEnabled(index,bEnable);
}

QToolButton* TestWinBase::addToolButton(QString strToolText,QString strPixmap,QString strToolTip)
{
	QToolButton* pToolBtn = new QToolButton;
// 	pToolBtn->setFixedSize(90,55);
	if(g_dUIShowCoef > 1.5)
	{
		pToolBtn->setFixedSize(65*g_dUIShowCoef,65);
	}
	else
	{
		pToolBtn->setFixedSize(90,55);
	}
	

	QLabel *buttonImage = new QLabel();
	buttonImage->setPixmap(QPixmap(strPixmap));
	buttonImage->setAlignment(Qt::AlignCenter);
	buttonImage->setContentsMargins(0,3,0,0);
	QLabel *buttonTxt = new QLabel();
	buttonTxt->setText(strToolText);
	buttonTxt->setContentsMargins(0,2,0,2);
	buttonTxt->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
	QVBoxLayout *topLayout = new QVBoxLayout();
	topLayout->addWidget(buttonImage);
	QVBoxLayout *bottomLayout = new QVBoxLayout();
	bottomLayout->addWidget(buttonTxt);
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->setMargin(0);
	mainLayout->setSpacing(5);
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bottomLayout);
	pToolBtn->setLayout(mainLayout);
	pToolBtn->setToolTip(strToolTip);

	return pToolBtn;
}

void TestWinBase::GenerateTestCmdFromIEC(CSttParas &oSttParas)
{
	//zhouhj 2024.3.22 生成paras时不需要判断,在判断是否下发时处理
//	if (m_pGooseParaWidget)
	{
		CSttXTestMngrBaseApp::GenerateTestCmdFromIEC(oSttParas);
	}
}

/*
void TestWinBase::GenerateTestCmdFromDefaultOutput(CSttTestCmd &oSttTestCmd)
{
	oSttTestCmd.m_strID = STT_CMD_TYPE_TEST_StartTest;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->m_strID = MACROID_SttSystemDefaultOutput;

	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase* pMacroParas = oSttXmlSerializeTool.GetMacroParas();

	//序列化参数
	stt_xml_serialize(&g_oDefaultOutputPara, pMacroParas);

	//根据pDoc生成对象
	oSttTestCmd.DeleteAll();
	oSttXmlSerializeTool.SttXmlSerializeRead(&oSttTestCmd);
}
*/

void TestWinBase::InitTestResource()
{
/*	if (m_pSttTestResource == NULL)
	{
		CreateTestResource();
		ASSERT(m_pSttTestResource);
		g_oSttTestResourceMngr.m_pTestResouce = m_pSttTestResource;
	}

	g_oSttTestResourceMngr.CreateChMaps();//打开本地通道映射文件
	initLocalSysPara();//在创建通道映射文件后,再初始化系统参数,如果当前缺省选择的输出模式有问题,如果选择了数字输出,但测试仪不支持数字输出,需要在初始化系统参数时,将对应设置取消
	g_oSttTestResourceMngr.ValidHardRsChMaps();//验证通道映射文件中硬件信息是否在Device中存在，删除不存在的硬件信息，如果不存在，则根据Device信息，创建缺省
	g_oSttTestResourceMngr.CreateSoftRsCh();
	g_oSttTestResourceMngr.CreateRtDataMngr();
*/

	CSttXTestMngrBaseApp::InitTestResource();
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pEventToProgress = m_pTimeResponseWidget;
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pEventToVector = m_vectorWidget;

	//2021-6-1  yangyijun
// 	g_oSttTestResourceMngr.m_oRtDataMngr.m_pEventToPower = m_powerWidget;		
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pEventToLineVolt = m_lineVoltWidget;
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pEventToSequence = m_seqWidget;	
}

/*
CString TestWinBase::getSystemParasFilePath()
{
	CString strFilePath = _P_GetConfigPath();
	strFilePath += FILE_SYSTEMPARA;

	return strFilePath;
}

CString TestWinBase::getSoeParasFilePath()
{
	CString strFilePath = _P_GetConfigPath();
	strFilePath += FILE_SOETESTPARA;

	return strFilePath;
}

long TestWinBase::OpenSoeParasFile(const CString& strSoeFile)
{
	long nRet = 0;
	CString strFile;

	if (strSoeFile.IsEmpty() || !IsFileExist(strSoeFile) || ParseFilePostfix(strSoeFile) != Postfix_SoeTest)
	{
		strFile = getSoeParasFilePath();
	}
	else
	{
		strFile = strSoeFile;
	}

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Soe测试参数文件【%s】不存在"),strFile.GetString());
		return FALSE;
	}

	CSttTestCmd oSttCmd;
	CSttMacro *pSttMacro = oSttCmd.GetSttMacro(TRUE,TRUE);

	CSttXmlSerializeTool oSttXmlSerializeTool;
	if (oSttXmlSerializeTool.CreateXmlSerializeRead(pSttMacro, strFile) == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析Soe测试参数文件失败【%s】"),strFile.GetString());
		return FALSE;
	}

	pSttMacro->SetCreateMacroChild(TRUE);
	oSttXmlSerializeTool.SttXmlSerializeRead(pSttMacro);

	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetParas();
	stt_xml_serialize(&m_oSoeParas, pMacroParas);

	return TRUE;
}

BOOL TestWinBase::SaveSoeParasFile(const CString& strSoeFile)
{
	CString strFile;

	CSttTestCmd oSttCmd;
	GenerateTestCmdFromSoeParas(oSttCmd);

	CSttMacro *pMacro = oSttCmd.GetSttMacro();
	CSttParas *pParas = pMacro->GetParas();
	ASSERT(pParas != NULL);

	if (strSoeFile.IsEmpty() || ParseFilePostfix(strSoeFile) != Postfix_SoeTest)
	{
		strFile = getSoeParasFilePath();
	}
	else
	{
		strFile = strSoeFile;
	}

	return pMacro->SaveXmlFile(strFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void TestWinBase::GenerateTestCmdFromSoeParas(CSttTestCmd &oSttTestCmd)
{
	oSttTestCmd.m_strID = STT_CMD_TYPE_TEST_StartTest;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttMacro *pMacro = oSttTestCmd.GetSttMacro(TRUE,TRUE);
	pMacro->m_strID = MACROID_SOETEST;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);
	CSttXmlSerializeBase* pMacroParas = oSttXmlSerializeTool.GetParas();

	//序列化参数
	stt_xml_serialize(&m_oSoeParas, pMacroParas);

	//根据pDoc生成对象
	oSttTestCmd.GetSttMacro()->DeleteAll();
	oSttTestCmd.GetSttMacro()->SetCreateMacroChild(true);
	oSttXmlSerializeTool.SttXmlSerializeRead(oSttTestCmd.GetSttMacro());
}

// mym 评估 2012-07-21 系统参数数据 dataset；
void TestWinBase::GetSystemParaDataGroup()
{
	g_pTmt_SystemParaRef->DeleteAll();

	CSttDataGroupSerializeRegister oRegister(g_pTmt_SystemParaRef);
	stt_xml_serialize_ErrorValues(&g_oSystemParas, &oRegister);
}

void TestWinBase::OnTestInitialize(CEventResult *pEventInfo,CDataGroup *pParas)
{
	ASSERT(pParas != NULL);

	CDataGroup *pEventBinGroup = (CDataGroup*)pParas->FindByID(SYS_STATE_XEVENT_EVENTID_BIN);
	CDataGroup *pEventBoutGroup = (CDataGroup*)pParas->FindByID(SYS_STATE_XEVENT_EVENTID_BOUT);

	int i=0;
	char strName[10];
	if (pEventBinGroup)
	{
		for (i=1; i<=MAX_BINARYIN_COUNT; i++)
		{
			sprintf(strName,"Bin%03d",i);
			stt_GetDataValueByID(pEventBinGroup, strName, pEventInfo->m_BinIn[i-1]);
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BinEx%03d",i);
			stt_GetDataValueByID(pEventBinGroup, strName, pEventInfo->m_BinInEx[i-1]);
		}
	}

	if (pEventBoutGroup)
	{
		for (i=1; i<=MAX_BINARYOUT_COUNT; i++)
		{
			sprintf(strName,"Bout%03d",i);
			stt_GetDataValueByID(pEventBoutGroup, strName, pEventInfo->m_BinOut[i-1]);
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BoutEx%03d",i);
			stt_GetDataValueByID(pEventBoutGroup, strName, pEventInfo->m_BinOutEx[i-1]);
		}
	}
}
*/

void TestWinBase::EndBinStateOnStarting()
{
/*	//初始化开入
	for (int i=0;i<g_nBinCount;i++)
		m_oCurrEventResult.m_BinIn[i] = 0;

	//初始化扩展开出
	for (int i=0;i<g_oLocalSysPara.m_nCHBinInExNum;i++)
		m_oCurrEventResult.m_BinInEx[i] = 0;

	//初始化开出
	for (int i=0;i<g_nBoutCount;i++)
		m_oCurrEventResult.m_BinOut[i] = 0;

	//初始化扩展开出
	for (int i=0;i<g_oLocalSysPara.m_nCHBinOutExNum;i++)
		m_oCurrEventResult.m_BinOutEx[i] = 0;
*/
	CSttXTestMngrBaseApp::EndBinStateOnStarting();
	UpdateToolButtons();
}
//////////////////////////////////////////////////////////////////////////
//
/*
BOOL TestWinBase::HasNextNeedTest()
{
	return GetNextItemNeedTest() >= 0 ;
}

long TestWinBase::GetNextItemNeedTest()
{
	if (m_oTmtTestMngr.m_nCount == 0)
	{
		return -1;
	}

	long nCurrIndex = 0;
	nCurrIndex  = m_nCurrTestIndex + 1;

	for (; nCurrIndex < m_oTmtTestMngr.m_nCount; nCurrIndex++)
	{
		if (m_oTmtTestMngr.m_pParasBuffer[nCurrIndex]->m_nSelected != 0)
		{
			break;
		}
	}

	if (nCurrIndex < m_oTmtTestMngr.m_nCount)
	{
		return nCurrIndex;
	}
	else
	{
		return -1;
	}
}

BOOL TestWinBase::TestCurrTestPoint()
{
	SendStartCmd();

	return TRUE;
}

void TestWinBase::GenerateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel)
{
	InitTestCmdFromParas(oSttTestCmd, STT_CMD_TYPE_TEST_StartTest, bSel);
}

void TestWinBase::UpdateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel)
{
	InitTestCmdFromParas(oSttTestCmd, STT_CMD_TYPE_TEST_UpdateParameter, bSel);
}

void TestWinBase::InitTestCmdFromParas(CSttTestCmd &oSttTestCmd, const CString &strCmdID, bool bSel)
{
	PTMT_PARAS_HEAD p = Test_GetAt(m_nCurrTestIndex);
	oSttTestCmd.m_strID = strCmdID;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttMacro *pMacro = oSttTestCmd.GetSttMacro(FALSE,FALSE);
	pMacro->m_strID = p->m_pszMacroID;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase* pMacroSerializeBase = oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);

	//序列化参数
	ASSERT(m_pSttTestResource);
	SerializeTestParas(pMacroSerializeBase, p,m_pSttTestResource->GetVolRsNum(),m_pSttTestResource->GetVCurRsNum(),
		g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum,g_oSystemParas.m_nHasDigital);

	pMacro->SetCreateMacroChild(true);
	oSttXmlSerializeTool.SttXmlSerializeRead(pMacro);
}

void TestWinBase::ClearTestMngr()
{
//	m_nCurrTestIndex = 0;

	long nIndex = 0;
	PTMT_PARAS_HEAD p = NULL;

	for (nIndex=0; nIndex<m_oTmtTestMngr.m_nCount; nIndex++)
	{
		p = Test_GetAt(nIndex);
		p->m_nTestState = 0;

		ClearResult(p);
	}
}

void TestWinBase::ClearResult(PTMT_PARAS_HEAD pHead)
{

}

PTMT_PARAS_HEAD TestWinBase::CreateTestParas(PTMT_PARAS_HEAD pCurr)
{
	return CreateTestParas(pCurr->m_pszMacroID);
}

void TestWinBase::Test_Add(PTMT_PARAS_HEAD pParas)
{
	stt_test_mngr_add(&m_oTmtTestMngr, pParas);
}

PTMT_PARAS_HEAD TestWinBase::Test_GetAt(long nIndex)
{
	return stt_test_mngr_get_at(&m_oTmtTestMngr, nIndex);
}

void TestWinBase::Test_InsertAt(PTMT_PARAS_HEAD pParas, long nIndex)
{
	stt_test_mngr_insert_at(&m_oTmtTestMngr, pParas, nIndex);
}

void TestWinBase::Test_SetAt(PTMT_PARAS_HEAD pParas, long nIndex)
{
	stt_test_mngr_set_at(&m_oTmtTestMngr, pParas, nIndex);
}

void TestWinBase::Test_DeleteAt(long nIndex)
{
	stt_test_mngr_delete_at(&m_oTmtTestMngr, nIndex);
}
*/
void TestWinBase::UpdateEventMsg(CEventResult *pEventInfo)
{
	if (!m_bStarted)
	{
		return;
	}
	pEventInfo->Copy(&m_oCurrEventResult);

	if (m_oCurrEventResult.m_strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		SysStateEvent_OnTestStart();
	}

	if (m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnSwichInChanged 
		|| m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnSwichOutChanged)
	{
		SysStateReport_OnSwithChanged();
	}

	if(m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnSwichInChanged 
		|| m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnSwichOutChanged
		|| m_oCurrEventResult.m_strEventID == SYS_STATE_EVENT_OnTestStarted
		|| m_oCurrEventResult.m_strEventID == SYS_STATE_RETTYPE_UPDATE)
	{
		if(m_pTimeResponseWidget)
		{
			for (int i = 0; i < g_nBinCount; i++)
			{
				m_pTimeResponseWidget->AddBinPoint(i, pEventInfo->m_fTime, pEventInfo->m_BinIn[i]);
			}

			for (int i = 0; i < g_nBoutCount; i++)
			{
				m_pTimeResponseWidget->AddBoutPoint(i, pEventInfo->m_fTime, pEventInfo->m_BinOut[i]);
			}
		}
	}

	if (isStateMode())
	{
		m_infoWidget->InsertSwitchInfoTable(&m_oCurrEventResult,true);
	}
	else
	{
		m_infoWidget->InsertSwitchInfoTable(&m_oCurrEventResult);
	}

	if(m_oCurrEventResult.m_strEventID == SYS_STATE_REPORT_OnStateChanged)
	{
		SysStateReport_OnStateChanged();
	}

	if (m_oCurrEventResult.m_strEventID == SYS_STATE_EVENT_OnTestStoped)
	{
		SysStateEvent_OnTestStoped();
	}

	if (m_oCurrEventResult.m_strEventID == SYS_STATE_EVENT_OnTestFinished)
	{
		SysStateEvent_OnTestFinished();
	}

	//更新指示灯
	UpdateToolButtons();
}

void TestWinBase::SysStateEvent_OnTestStart()
{
	
}

void TestWinBase::SysStateReport_OnSwithChanged()
{
//	m_pTimeResponseWidget->OnRtSwitchChanged(m_oCurrEventResult.m_fActTime);
}

void TestWinBase::SysStateReport_OnStateChanged()
{
	if (m_oCurrEventResult.m_nCurrStateIndex>=0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("State %d"),m_oCurrEventResult.m_nCurrStateIndex+1);
	}
}

void TestWinBase::SysStateEvent_OnTestStoped()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("SysStateEvent_OnTestStoped"));
	m_nCurrTestIndex = -1;
//	OnViewTestStop();
	m_oCurrEventResult.init(false);
	memset(m_oCurrEventResult.m_BinOut,0,sizeof(long)*MAX_BINARYOUT_COUNT);
	memset(m_oCurrEventResult.m_BinOutEx,0,sizeof(long)*MAX_ExBINARY_COUNT);
	emit sig_ViewTestStop();//zhouhj 20211023  改为发消息的方式否则 Started命令收到后,可能会与此信号处理的顺序反掉
}

CString OpenSaveTemplateFileDlg(QWidget *parent,const CString &strTitle,const QStringList &strFilterList,
								const CString &strFolderPath,BOOL bIsOpen)
{
// 	QStringList strFiltPostFixs;
// 	CString strModelPostfix;
// 	strModelPostfix.Format(_T("project(*.%s)"), STT_UPDATE_TEST_XML_POSTFIX/*.GetString()*/);
// 	strFiltPostFixs << strModelPostfix <<strFilter;//统一模板文件

	CString strText;
	QFileDialog dlg(parent, strTitle);
	dlg.setFileMode(QFileDialog::AnyFile);
// 	dlg.setNameFilter(strFilter);
	dlg.setNameFilters(strFilterList);//2023-12-20 wuxinyi 定义文件筛选

	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	dlg.setDirectory(strFolderPath);
	strText = _T("文件路径");
	dlg.setLabelText(QFileDialog::LookIn, strText);
	strText = _T("文件名");
	dlg.setLabelText(QFileDialog::FileName, strText);
	strText = _T("文件类型");
	dlg.setLabelText(QFileDialog::FileType, strText);

	if(bIsOpen)
	{
		dlg.setAcceptMode(QFileDialog::AcceptOpen);
		strText = _T("打开");
		dlg.setLabelText(QFileDialog::Accept, strText);
	}
	else
	{
		dlg.setAcceptMode(QFileDialog::AcceptSave);
		strText = _T("保存");
		dlg.setLabelText(QFileDialog::Accept, strText);	
	}

	strText = _T("取消");
	dlg.setLabelText(QFileDialog::Reject, strText);

	CString strFileName,strSelectFilter;
	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFileName = fileNames.at(0);
		strSelectFilter = dlg.selectedFilter();
		CString strTmp;
		long nIndex = strSelectFilter.Find("*.");

		if (nIndex>=0)
		{
			strTmp = strSelectFilter.Mid(nIndex+1);
			strTmp.Replace(_T(")"),_T(""));

			if (strFileName.Find(strTmp) == -1)
			{
				strFileName += strTmp;
			}
		}

	}

	return strFileName;
}

void TestWinBase::SysStateEvent_OnTestFinished()
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("SysStateEvent_OnTestFinished"));

	if (HasNextNeedTest())
	{
		m_nCurrTestIndex = GetNextItemNeedTest();
		TestCurrTestPoint();
	}
	else
	{
		SysStateEvent_OnTestStoped();
	}
}

/*
CString TestWinBase::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _P_GetMoudleFileName();
	strFile += _T(".");
	strFile += m_oTmtTestMngr.m_pszParaFilePostfix;

	return strFile;
}
*/
//基类增加m_strParaFileTitle变量，=过流试验模板文件
//基类增加m_strParaFilePostfix变量，=project(*.octxml)
void TestWinBase::slot_openTestParas()
{
	//20230308 zhangyq 打开配置文件
	//CString strCfgPath = _P_GetConfigPath();

//	CLogPrint::LogString(XLOGLEVEL_ERROR,_T("000"));

	if (g_oSttSystemConfig.GetCount() == 0)
	{
//		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("111"));
		g_oSttSystemConfig.OpenSystemConfig();
//		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("222"));
	}

	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();
//	CLogPrint::LogString(XLOGLEVEL_ERROR,_T("333"));

	QString fileName;
	fileName.clear();

	//mym add 2021-10-12 
/*统一用main的编码
	QTextCodec *codec = QTextCodec::codecForName("system");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
*/
	CString strFolderPath;
	strFolderPath = _T("");

	if (!pSttDevConfig->m_strLastFolderPath.IsEmpty())
	{
		strFolderPath = GetPathFromFilePathName(pSttDevConfig->m_strLastFolderPath);
	}
	else
	{
		strFolderPath = _P_GetTemplatePath();
	}

	QStringList strFiltPostFixs;
	CString strModelPostfix;
	strModelPostfix.Format(_T("project(*.%s)"), STT_UPDATE_TEST_XML_POSTFIX/*.GetString()*/);
	strFiltPostFixs << strModelPostfix <<m_strParaFilePostfix;//统一模板文件

	fileName = OpenSaveTemplateFileDlg(this,m_strParaFileTitle,strFiltPostFixs,strFolderPath,TRUE);

//	fileName = QFileDialog::getOpenFileName(this, m_strParaFileTitle.GetString(),_T("")/*strFolderPath*/,m_strParaFilePostfix.GetString());
//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("开始打开模板文件后(%s)."),strFolderPath.GetString());

	if (!fileName.isEmpty())
	{			
		CString strIECFilePath = ChangeFilePostfix(fileName, "ixml");

		if((g_oLocalSysPara.m_nSupportDigitalOutput == 1)&&(IsFileExist(strIECFilePath)))//不支持数字量
		{
			CString strMsg = _T("是否加载模板中的IEC配置？");
			int nRet = QMessageBox::question(this, /*tr("提示")*/g_sLangTxt_Message,strMsg,/*tr("是")*/g_sLangTxt_State_Yes,/*tr("否")*/g_sLangTxt_State_No);
			if(nRet == 0)
	{
				g_oSttTestResourceMngr.m_oIecDatasMngr.OpenIecCfgFile(strIECFilePath);
			}
		}

		CString strFilePath(fileName);
		OpenTestTestMngrFile(strFilePath);

		//20230308  zhangyq 记录文件路径，保存配置
		m_strFilePath = strFilePath;
		pSttDevConfig->m_strLastFolderPath = strFilePath;
		g_oSttSystemConfig.SaveSystemConfig();
//		pSttDevConfig->SaveXmlFile(strDefautPath,CSttSystemConfigXmlRWKeys::g_pXmlKeys);

		//更新IEC配置参数之后更新界面
// 		if (m_pGooseParaWidget)
// 		{
// 			long nParasSetSel = g_oSttTestResourceMngr.m_oIecDatasMngr.GetParasSetSel();
// 
// 			UpdateGoutTab(TRUE);//zhouhj 手动模块参数无意义,对于状态序列及多个测试项目的更新全部克隆链表
// 			UpdateFT3Tab(TRUE);
// 			UpdateIECChannelsData();
// 
// 			g_oSttTestResourceMngr.ValidIecParasSetSel();
// 			long nNewParasSetSel = g_oSttTestResourceMngr.m_oIecDatasMngr.GetParasSetSel();
// 
// 			if ((nParasSetSel != nNewParasSetSel)&&(nNewParasSetSel))//如果参数设置改变为二次值输出了,需要重新更新界面,设置各通道的电压电流设置最大值
// 			{
// 				OnUpdateTestResource(FALSE);
// 			}
// 		}

		InitUI_OpenParas();

		//2022.5.20 caoxc
		if(m_bLoadFinished)
		{
			slot_ClearAllResult();
		}
	}
}

//基类增加m_strDefaultParaFile变量，保存默认参数文件路径
void TestWinBase::slot_saveTestParas()
{
	CString strTmp;

	//20230303 zhangyq
	QDir dir;
	if (dir.exists(m_strFilePath))
	{
		if (SaveTestMngrFile(m_strFilePath))
		{
			QMessageBox::information(NULL, QObject::tr("提示"), QObject::tr("文件保存成功！"));//chenling 20230526
			strTmp = QString(tr("文件[%1]保存成功.")).arg(m_strFilePath);		
		}
		else
		{
			QMessageBox::information(NULL, QObject::tr("提示"), QObject::tr("文件保存失败！"));
			strTmp = QString(tr("文件[%1]保存失败.")).arg(m_strFilePath);
		}
	}
	else
	{
		if (SaveTestMngrFile(m_strDefaultParaFile))
		{
			QMessageBox::information(NULL, QObject::tr("提示"), QObject::tr("文件保存成功！"));//chenling 20230526
			strTmp = QString(tr("默认参数文件[%1]保存成功.")).arg(m_strDefaultParaFile);		
		}
		else
		{
			QMessageBox::information(NULL, QObject::tr("提示"), QObject::tr("文件保存失败！"));
			strTmp = QString(tr("默认参数文件[%1]保存失败.")).arg(m_strDefaultParaFile);
		}
	}


	CLogPrint::LogString(XLOGLEVEL_TRACE,strTmp);

	m_bTmtParaChanged = FALSE;
}

void TestWinBase::slot_saveAsTestParas()
{

	CString strPostfix = _T("");//2023-12-29 wuxinyi 统一修改保存模板后缀名
	//20230308 zhangyq
	//CString strCfgPath = _P_GetTemplatePath();

	if (g_oSttSystemConfig.GetCount() == 0)
	{
		g_oSttSystemConfig.OpenSystemConfig();
	}

	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	QString fileName;
	fileName.clear();

// 	QDir dir;
// 	if (!dir.exists(/*strCfgPath*/pSttDevConfig->m_strLastFolderPath))
// 	{
// 		if(!dir.mkpath(/*strCfgPath*/pSttDevConfig->m_strLastFolderPath))
// 		{
// 			QMessageBox::information(NULL, QObject::tr("提示"), QObject::tr("创建测试模板文件路径失败！"));
// 			return ;
// 		}
// 	}

	CString strFolderPath;
	strFolderPath = _T("");

	if (!pSttDevConfig->m_strLastFolderPath.IsEmpty())
	{
		strFolderPath = GetPathFromFilePathName(pSttDevConfig->m_strLastFolderPath);
	}
	else
	{
		strFolderPath = _P_GetTemplatePath();
	}

	QStringList strFiltPostFixs;
	CString strModelPostfix;
	strModelPostfix.Format(_T("project(*.%s)"), STT_UPDATE_TEST_XML_POSTFIX/*.GetString()*/);

	//2024-4-17 wuxinyi 新需求：另存为时只支持保存tplxml
	// 	strFiltPostFixs << strModelPostfix <<m_strParaFilePostfix;//统一模板文件
	strFiltPostFixs << strModelPostfix;

	fileName = OpenSaveTemplateFileDlg(this,QObject::tr("模板另存为"),strFiltPostFixs,strFolderPath,FALSE);

	//2024-4-22 wuxinyi 硬件支持数字量时另存为可选择iec配置同时保存
	if (!fileName.isEmpty())
	{	
		if(g_oLocalSysPara.m_nSupportDigitalOutput == 1)//不支持数字量
	{
			CString strMsg = _T("是否保存IEC配置？");
			int nRet = QMessageBox::question(this, /*tr("提示")*/g_sLangTxt_Message,strMsg,/*tr("是")*/g_sLangTxt_State_Yes,/*tr("否")*/g_sLangTxt_State_No);
			if(nRet == 0)
			{
				CString strIECFilePath = ChangeFilePostfix(fileName, "ixml");
				g_oSttTestResourceMngr.m_oIecDatasMngr.SaveAsIecCfgFile(strIECFilePath,FALSE);
			}
		}

		CString strFilePath(fileName);
		pSttDevConfig->m_strLastFolderPath = GetPathFromFilePathName(strFilePath);
		CreateAllDirectories(pSttDevConfig->m_strLastFolderPath);
		g_oSttSystemConfig.SaveSystemConfig();
		//		pSttDevConfig->SaveXmlFile(strDefautPath,CSttSystemConfigXmlRWKeys::g_pXmlKeys);

		CString strTmp;
		if (SaveTestMngrFile(fileName))
		{
			strTmp = QString(tr("模板另存为[%1]成功.")).arg(fileName);
		}
		else
		{
			strTmp = QString(tr("模板另存为[%1]失败.")).arg(fileName);
		}

		CLogPrint::LogString(XLOGLEVEL_TRACE,strTmp);
	}

	m_bTmtParaChanged = FALSE;
}

/*
BOOL TestWinBase::OpenTestTestMngrFile(const CString& strParasFile)
{
	CString strFile;

	if (!IsValidTestParasFile(strParasFile))
	{
		strFile = GetDefaultParaFile();
	}
	else
	{
		strFile = strParasFile;
	}

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("功能测试参数文件【%s】不存在"),strFile.GetString());
		return FALSE;
	}


	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase *pRootParas = NULL, *pParas = NULL;
	pRootParas = oSttXmlSerializeTool.CreateXmlSerializeRead(stt_TestMacrosKey(), strFile);

	if (pRootParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析功能测试参数文件【%s】失败"),strFile.GetString());
		return FALSE;
	}

	stt_xml_serialize(&m_oTmtTestMngr, pRootParas);

	long nIndex = 0;
	PTMT_PARAS_HEAD p = NULL;

	char szMacroID[TMT_PARAS_HEAD_MACROID_LEN];  //测试供能ID;

	for (nIndex=0; nIndex<m_oTmtTestMngr.m_nCount; nIndex++)
	{
		pParas = pRootParas->xml_serialize(stt_TestMacroKey(), nIndex, _T(""), _T(""), "macro");//zhouhj 20210712 创建Macro节点的时候,不再传递name和id

		if (pParas == NULL)
		{
			break;
		}

		stt_xml_serialize_ReadMacroID(pParas,szMacroID);
		p = CreateTestParas(szMacroID);
		stt_test_mngr_set_at(&m_oTmtTestMngr, p, nIndex);
		stt_xml_serialize(p, pParas);
		SerializeTestParas(pParas, p,m_pSttTestResource->GetVolRsNum(),m_pSttTestResource->GetVCurRsNum(),
			g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum,g_oSystemParas.m_nHasDigital);
	}

	return TRUE;
}

BOOL TestWinBase::SaveTestMngrFile(const CString& strParasFile)
{
	CString strFile;

	if (!IsValidTestParasFile(strParasFile,FALSE))
	{
		strFile = GetDefaultParaFile();
	}
	else
	{
		strFile = strParasFile;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase *pRootParas = NULL, *pParas = NULL;
	pRootParas = oSttXmlSerializeTool.CreateXmlSerializeRegister(stt_TestMacrosKey());

	if (pRootParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析功能测试参数文件【%s】失败"),strFile.GetString());
		return FALSE;
	}

	stt_xml_serialize(&m_oTmtTestMngr, pRootParas);

	long nIndex = 0;
	PTMT_PARAS_HEAD p = NULL;

	for (nIndex=0; nIndex<m_oTmtTestMngr.m_nCount; nIndex++)
	{
		p = stt_test_mngr_get_at(&m_oTmtTestMngr, nIndex);

		if (p == NULL)
		{
			break;
		}

		pParas = pRootParas->xml_serialize(stt_TestMacroKey(), nIndex, p->m_pszMacroID, p->m_pszMacroID, "macro");

		if (pParas == NULL)
		{
			break;
		}

		stt_xml_serialize(p, pParas);
		SerializeTestParas(pParas, p,m_pSttTestResource->GetVolRsNum(),m_pSttTestResource->GetVCurRsNum(),
			g_oLocalSysPara.m_nCHBinInExNum,g_oLocalSysPara.m_nCHBinOutExNum,g_oSystemParas.m_nHasDigital);
	}

	return oSttXmlSerializeTool.Stt_WriteFile(strFile);
}
*/
void TestWinBase::InitUI_OpenParas()
{
	if(m_TestTable)//2024-01-04 wuxinyi 数字故障回放没有QItemTableBase，打开模板文件调用该函数m_TestTable为空，中断
	{
	m_TestTable->InitData();
	m_TestTable->SetCurrentRow(0);
}
}

void TestWinBase::slot_updateParas()
{
	if (m_bViewTestStarted)
	{
		SendUpdateParameter();
	}
}

void TestWinBase::slot_updateVectorData()
{
	m_vectorWidget->updateDiagram();
}

void TestWinBase::LogString(long nLevel, const CString &strMsg)
{
	if (strMsg.IsEmpty())
	{
		return;
	}

	for ( int i  = 0 ; i  <  8; i++)
	{
		if (strMsg.contains(m_strLogInfo[i]) )
		{
			return;
		}
	}

	if (strMsg.contains(tr("谐波含量超约定值")) || strMsg.contains(tr("输出最大值超设计")) || strMsg.contains(tr("TestParaCheckFail")) || strMsg.contains(tr("超出范围")) )
	{
		m_strListInfo.append(strMsg);
		return;
	}


	//yyj 20210925，结尾加变红标记
	QString strInfo;
	if(nLevel == XLOGLEVEL_EXCEPTION || nLevel == XLOGLEVEL_ERROR)
	{
		strInfo = QString("%1%2").arg(strMsg).arg(LogColor_Red);
	}
	else
	{
		strInfo = QString("%1%2").arg(strMsg).arg(LogColor_Black);
	}

	m_strListInfo.append(strInfo);

	if (m_bIsUsingIecCap)
	{
		emit sig_refreshLog(strMsg);//suyang 20230710 发送信号更新信息栏
	}


	//emit sig_LogString(strMsg);//mym 2021-7-26 zhuxiao ,改在定时器里刷新；
}

void TestWinBase::LogString(long nLevel, const char *strMsg)
{
	LogString(nLevel, CString(strMsg));
}

//2021-7-28 mayangming add
void TestWinBase::UpdateLogString()
{
	int nIndex = 0;
	QString strInfo, strMsg;

	for (nIndex = 0; nIndex < m_strListInfo.size(); nIndex++)
	{
		strInfo = m_strListInfo[nIndex];

		//输出最大值超设计
		if (m_strListInfo[nIndex].contains(tr("谐波含量超约定值")))
		{
			strMsg = m_strListInfo[nIndex] +  tr("，请重新修改谐波含量的值！");
			strInfo = QString("%1%2").arg(strMsg).arg(LogColor_Red);
		}
		else if (m_strListInfo[nIndex].contains(tr("输出最大值超设计")))
		{
			strMsg = m_strListInfo[nIndex] +  tr("，请重新修改谐波含量的值！");
			strInfo = QString("%1%2").arg(strMsg).arg(LogColor_Red);
		}
		else if (m_strListInfo[nIndex].contains(tr("TestParaCheckFail")))
		{
			strMsg = m_strListInfo[nIndex] ;
			strInfo = QString("%1%2").arg(strMsg).arg(LogColor_Red);
		}
		else if (m_strListInfo[nIndex].contains(tr("超出范围")))
		{
			strMsg = m_strListInfo[nIndex] ;
			strInfo = QString("%1%2").arg(strMsg).arg(LogColor_Red);
		}

		//yyj 20210925根据标记显示不同颜色
/*
		//输出最大值超设计
		if (m_strListInfo[nIndex].contains(tr("谐波含量超约定值")))
		{
			AddRecord(QColor("red"), m_strListInfo[nIndex] +  tr("，请重新修改谐波含量的值！"));
		}
		else if (m_strListInfo[nIndex].contains(tr("输出最大值超设计")))
		{
			AddRecord(QColor("red"), m_strListInfo[nIndex] +  tr("，请重新修改输出值！"));
		}
		else if (m_strListInfo[nIndex].contains(tr("TestParaCheckFail")))
		{
			AddRecord(QColor("red"), m_strListInfo[nIndex]);
		}
		else if (m_strListInfo[nIndex].contains(tr("超出范围")))
		{
			AddRecord(QColor("red"), m_strListInfo[nIndex]);
		}
		else 
		{
			AddRecord(QColor("black"), m_strListInfo[nIndex]);
		}
*/

		if (strInfo.right(2)==LogColor_Red)
		{
			strInfo = strInfo.left(strInfo.length()-2);
			AddRecord(QColor("red"), strInfo);
			RaiseStateInfo();
		}
		else if (strInfo.right(2)==LogColor_Black)
		{
			strInfo = strInfo.left(strInfo.length()-2);
			AddRecord(QColor("black"), strInfo);
		}
	}

	m_strListInfo.clear();
}

void TestWinBase::slot_Timer()
{
	UpdateLogString();              //2021-7-28 mayangming add

	//mym 2021-8-21 add 
	if (!m_bInitConneced)
	{
		m_bInitConneced = TRUE;
		OnConnectTestApp(g_oSttTestAppCfg.GetTestAppIP(), g_oSttTestAppCfg.GetTestServerPort());
		setActionEnabled(ACTION_START,true);
	}

	slot_UpdateEventMsg();

	if (m_pXClientEngine != NULL)
	{
		m_pXClientEngine->OnSendHeartbeatTimer_NotCheakAuthority();
		
	}

// 	if (m_bUpdateRtData)
	{
	signalIBreak_UOverLoad_OverHeat();//20240124 suyang 在运行过程中更新电流开路、电压过载、过热指示灯 
	signalBinInToolBtn();
	}


	if(!g_bTestAppConnect)
	{
//		m_oSoeDlg.close();
//		m_oDcSetDlg.close();
		
		signalLink();
#ifdef STT_USE_Resource_Img_
		initToolbutton(m_Run,"Run",QString(":/images/SwichIcon/shutoff.png"));	//显示停运灯
#else
		initToolbutton(m_Run,"Run",QString("./images/SwichIcon/shutoff.png"));	//显示停运灯
#endif
		emit sig_ViewTestLink(g_bTestAppConnect);
	}
}

void TestWinBase::slot_UpdateEventMsg()
{
	CExBaseList oEventInfoList;
	GetEventInfo(oEventInfoList);
	POS pos = oEventInfoList.GetHeadPosition();
	CEventResult *p = NULL;

	while(pos != NULL)
	{
		p = (CEventResult *)oEventInfoList.GetNext(pos);
		UpdateEventMsg(p);
//		m_oEventResultList.AddTail(p);
	}
	oEventInfoList.RemoveAll();
}

void TestWinBase::signalBinInToolBtn()
{
#ifdef STT_USE_Resource_Img_
	char strName[MAX_BINARYIN_COUNT] = "ABCDEFGHIJKLMNOP";		
	for(int i=0; i<m_oBinInToolBtnList.size(); i++)
	{
		if (m_oBinaryConfig.m_binIn[i].nSelect)
		{
			if (m_oCurrEventResult.m_BinIn[i] != 0)
			{
				initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString(":/images/SwitchIcon/switch_close.png"));
			}
			else
			{
				initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString(":/images/SwitchIcon/switch_open.png"));
			}
		}
		else
		{
			initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString(":/images/SwitchIcon/switch_null.png"));
		}	
	}
#else
	char strName[MAX_BINARYIN_COUNT] = "ABCDEFGHIJKLMNOP";		
	for(int i=0; i<m_oBinInToolBtnList.size(); i++)
	{
		if (m_oBinaryConfig.m_binIn[i].nSelect)
		{
			if (m_oCurrEventResult.m_BinIn[i] != 0)
			{
				initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString("./images/SwichIcon/switch_close.png"));
			}
			else
			{
				initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString("./images/SwichIcon/switch_open.png"));
			}
		}
		else
		{
			initToolbutton(m_oBinInToolBtnList.at(i),QString(strName[i]),QString("./images/SwichIcon/switch_null.png"));
		}	
	}
#endif
}

void TestWinBase::signalIBreak_UOverLoad_OverHeat()
{

/*
I 电流开路、电流过载
U 电压短路、电压过载
OH 过热、电压短路
说明书是这么写的
*/

#ifdef STT_USE_Resource_Img_
	//	CSttTestEngineClientData *pClientEngine = g_oSttTestAppConfigTool.m_pClientEngine;

	if (m_pXClientEngine != NULL)
	{
		if (/*(*/m_pXClientEngine->IBreak()/*)|| (m_pXClientEngine->IOverLoad())*/)
		{
			initToolbutton(m_IInfoList.at(0),/*oList.at(i)*/"I",QString(":/images/SwitchIcon/circle_yellow.png"));
		}
		else
		{
			initToolbutton(m_IInfoList.at(0),/*oList.at(i)*/"I",QString(":/images/SwitchIcon/circle_red.png"));
		}

		if ((m_pXClientEngine->UOverLoad())|| (m_pXClientEngine->UShort()))
		{
			initToolbutton(m_V,"U",QString(":/images/SwitchIcon/circle_yellow.png"));
		}
		else
		{
			initToolbutton(m_V,"U",QString(":/images/SwitchIcon/circle_red.png"));
		}

		if ((m_pXClientEngine->OverHeat())||(m_pXClientEngine->UShort()))
		{
			initToolbutton(m_OH,"OH",QString(":/images/SwitchIcon/circle_yellow.png"));
		}
		else
		{
			initToolbutton(m_OH,"OH",QString(":/images/SwitchIcon/circle_red.png"));
		}
	}
	else
	{
		initToolbutton(m_IInfoList.at(0),/*oList.at(i)*/"I",QString(":/images/SwitchIcon/circle_red.png"));
		initToolbutton(m_V,"U",QString(":/images/SwitchIcon/circle_red.png"));
		initToolbutton(m_OH,"OH",QString(":/images/SwitchIcon/circle_red.png"));
	}
#else

	if (m_pXClientEngine != NULL)
	{
		if (/*(*/m_pXClientEngine->IBreak()/*)|| (m_pXClientEngine->IOverLoad())*/)//xueyangfan 20240417 电流开路灯 开路黄色 未开路红色
		{
			initToolbutton(m_IInfoList.at(0),/*oList.at(i)*/"I",QString("./images/SwichIcon/circle_yellow.png"));
		}
		else
		{
			initToolbutton(m_IInfoList.at(0),/*oList.at(i)*/"I",QString("./images/SwichIcon/circle_red.png"));
		}

		if ((m_pXClientEngine->UOverLoad())|| (m_pXClientEngine->UShort()))
		{
			initToolbutton(m_V,"U",QString("./images/SwichIcon/circle_yellow.png"));
		}
		else
		{
			initToolbutton(m_V,"U",QString("./images/SwichIcon/circle_red.png"));
		}

		if ((m_pXClientEngine->OverHeat())||(m_pXClientEngine->UShort()))
		{
			initToolbutton(m_OH,"OH",QString("./images/SwichIcon/circle_yellow.png"));
		}
		else
		{
			initToolbutton(m_OH,"OH",QString("./images/SwichIcon/circle_red.png"));
		}
	}
	else
	{
		initToolbutton(m_IInfoList.at(0),/*oList.at(i)*/"I",QString("./images/SwichIcon/circle_red.png"));
		initToolbutton(m_V,"U",QString("./images/SwichIcon/circle_red.png"));
		initToolbutton(m_OH,"OH",QString("./images/SwichIcon/circle_red.png"));
	}


#endif

}
void TestWinBase::signalLink()
{
#ifdef STT_USE_Resource_Img_
	if(g_bTestAppConnect)
	{
		m_LabLinkIcon->setPixmap(QPixmap(":/images/circle_green.png"));
	}
	else
	{
		m_LabLinkIcon->setPixmap(QPixmap(":/images/circle_black.png"));
	}
#else
	if(g_bTestAppConnect)
	{
		m_LabLinkIcon->setPixmap(QPixmap("./images/circle_green.png"));
	}
	else
	{
		m_LabLinkIcon->setPixmap(QPixmap("./images/circle_black.png"));
	}
#endif
}

void TestWinBase::OnTestStarted(const CString &strMacroID, CDataGroup *pParas)
{
	if(!m_bStarted)
	{
		return;
	}
	CSttPowerTestEngineBase::OnTestStarted(strMacroID,pParas);
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnTestStarted(%s)"),strMacroID.GetString());

	if(pParas)
	{
		if (!m_bViewTestStarted)
		{
			emit sig_ViewTestStart();
		}
	}
}

void TestWinBase::OnTestState(const CString &strMacroID, CDataGroup *pParas)
{
	CSttPowerTestEngineBase::OnTestState(strMacroID,pParas);
//	emit sig_UpdateEventMsg();
}

long TestWinBase::OnDisConnect()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("OnDisConnect"));

	g_bTestAppConnect = FALSE;

	emit sig_ViewTestLink(g_bTestAppConnect);

	return 0;
}

void TestWinBase::OnReport_ReadDevice(const CString &strMacroID, CDataGroup *pParas)
{
/*	CDataGroup *pReadGroup = (CDataGroup*)pParas->FindByID(_T("Device"));
	ASSERT(pReadGroup);
	CSttAdjDevice oReadDevice;
	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	oReadDevice.AttatchAdjRef(pReadGroup);
	oReadDevice.GetAttrs();
	pCurDevice->GetAttrs();

	if ((oReadDevice.m_strModel != pCurDevice->m_strModel)||(oReadDevice.m_strSN != pCurDevice->m_strSN))//如果信号或者装置SN不匹配，则需要重新读取Device信息
	{
		if (pCurDevice->m_pSttAdjRef == NULL)
		{
			pCurDevice->m_pSttAdjRef = new CDataGroup();
			pCurDevice->m_pSttAdjRef->SetParent(pCurDevice);
		}

		pCurDevice->m_pSttAdjRef->DeleteAll();
		pReadGroup->Copy(pCurDevice->m_pSttAdjRef);
		pCurDevice->GetAttrs();
		pCurDevice->SortModules();
		g_oSttTestResourceMngr.SetCurSelDevice(pCurDevice->m_strModel,pCurDevice->m_strSN);
		g_oSttTestResourceMngr.SaveCurDeviceFile();
		g_oSttTestResourceMngr.GetAllModuleTags();
//		emit sig_UpdateTestResource();//发送信号更新软件资源
	}
	else//需要将读取出来的模块的电流档位等信息更新到系统参数中去??????????????????????????????????????????????????????????
	{

	}

	oReadDevice.AttatchAdjRef(NULL);
*/
	CSttXTestMngrBaseApp::OnReport_ReadDevice(strMacroID, pParas);
	emit sig_UpdateTestResource();//发送信号更新软件资源
}

/*
void TestWinBase::initDefaultSoeParaFile()
{
	m_oSoeParas.init();
}
*/

void TestWinBase::InitVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR)
{
	if(m_vectorWidget)
	{
		m_vectorWidget->setPropertyOfParaSet(m_pSttTestResource, STT_COMMON_VECTOR);
		m_vectorWidget->m_TableData->show();

		CSttMacroChannels *pMacroChs = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
		//2023-12-26 zhouyangyong 新增故障通道传参
		m_vectorWidget->setData(pVOL,pCUR,&pMacroChs->m_oVolChListRef, &pMacroChs->m_oCurChListRef, &pMacroChs->m_oUfCh, &pMacroChs->m_oIfCh);
	}
}

//chenling
void TestWinBase::InitPowerDiagramWidget(tmt_channel* pVOL,tmt_channel* pCUR)
{
	if (m_powerdiagramWidget)
	{
		m_powerdiagramWidget->setPropertyOfParaSet(g_oSttTestResourceMngr.m_pTestResouce);
		CSttMacroChannels *pMacroChs = g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels;
		m_powerdiagramWidget->setData(pVOL,pCUR, &pMacroChs->m_oVolChListRef, &pMacroChs->m_oCurChListRef);	
	}
}

void TestWinBase::InitTimeResponseWidget()
{
	if (m_pTimeResponseWidget != NULL)
	{
		m_pTimeResponseWidget->initUI(g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels
			,0,g_oLocalSysPara.m_fAC_VolMax,0,g_oLocalSysPara.m_fAC_CurMax
			,m_oCurrEventResult.m_BinIn,g_nBinCount/*g_oLocalSysPara.m_nCHBinInNum*/,m_oCurrEventResult.m_BinOut,g_nBoutCount/*g_oLocalSysPara.m_nCHBinOutNum*/);
	}
}

long TestWinBase::OnUpdateSyncTime(CDataGroup *pRtSyncTime)
{
	emit sig_OnUpdateGpsTime(pRtSyncTime);
// 	long nSecond = 0,nNSecend = 0,nSyn = 0;
// 	stt_GetDataValueByID(pRtSyncTime, _T("Sync"), nSyn);
// 	stt_GetDataValueByID(pRtSyncTime, _T("Utc_s"), nSecond);
// 	stt_GetDataValueByID(pRtSyncTime, _T("Utc_ns"), nNSecend);
// 	OnUpdateGpsTime(nSyn,nSecond,nNSecend);
	return 0;
}


void TestWinBase::ClearTimeResponseData()
{
	if(m_pTimeResponseWidget)
	{
		if(m_pTimeResponseWidget->m_oChlTimePlotList.size() != 0)
		{
			for(int i=0; i<m_pTimeResponseWidget->m_oChlTimePlotList.size(); i++)
			{
				m_pTimeResponseWidget->m_oChlTimePlotList.at(i)->initCurve();
			}
		}

		if (m_pTimeResponseWidget->m_pBinInTimeResponsePlot != NULL)
		{
			m_pTimeResponseWidget->m_pBinInTimeResponsePlot->initCurve();
		}

		if (m_pTimeResponseWidget->m_pBinOutTimeResponsePlot != NULL)
		{
			m_pTimeResponseWidget->m_pBinOutTimeResponsePlot->initCurve();
		}
	}
}
void TestWinBase::slot_LogString(CString strMsg)
{
	AddRecord(QColor("black"),strMsg);
}

void TestWinBase::slot_initReportView()
{
}

void TestWinBase::UpdateAuxDcEnabled()
{

}

void TestWinBase::updateParas()
{
	slot_updateParas();
}


void TestWinBase::UpdateFreq()
{

}

long TestWinBase::slot_start()
{
	//2022.5.16 caoxc 开始测试时，清除所有的测试标志
	slot_ClearAllResult();

	if (!HasFT3Block_Selected() && (g_oSttSystemConfig.GetDevModel().Find(_T("DRT")) >= 0))
	{
		return 0 ;
	}

	if (m_nCurrTestIndex != -1)//20230615 zhouhj 点击开始测试后,固定从第一个开始测试
	{
		m_nCurrTestIndex = -1;
	}
	//填充报告
	if (m_pSttXTestMngrHtmlRpt)
	{
		//20240514 suyang 增加在开始测试的时候更新报告头 开始时间
		QSttReportViewHtml* pReportView= (QSttReportViewHtml*)m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
		pReportView->UpdateReportHead_StartEndTestTime(TRUE,TRUE);

		m_pSttXTestMngrHtmlRpt->FillReport();
	}

	if (!g_bTestAppConnect)
	{
		CString strIP = g_oSttTestAppCfg.GetTestAppIP();
		long nPort = g_oSttTestAppCfg.GetTestServerPort();

		if (!OnConnectTestApp(strIP,nPort))//如果当前未联机,需要进行联机操作
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("联机失败[%s][%ld]."),strIP.GetString(),nPort);
			SysStateEvent_OnTestStoped();
			return 0;
		}
	}


	if (HasNextNeedTest())//add sf 20210716
	{
		m_nCurrTestIndex = GetNextItemNeedTest();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前已经是最后一个测试下,无法继续测试."));
		return 0;
	}

	if (!m_bViewTestStarted)
	{
		//验证当前测试项参数是否有效,主要用于故障回放模块,在开始测试前切换回放文件,验证回放文件内容是否满足条件
		if (!ValidCurrTestItemParas())
		{
			m_nCurrTestIndex = -1;
			return 0;
		}

		long nRet = STT_CMD_ExecStatus_NULL;

		if (m_bChMapsChanged)
		{
			nRet = SendChMapsConfig();
			if(nRet == STT_CMD_ExecStatus_SUCCESS)
			{
				m_bChMapsChanged = FALSE;
				CLogPrint::LogString(XLOGLEVEL_INFOR,tr("通道映射文件下发完成"));
			}
			else
			{
				CLogPrint::LogString(XLOGLEVEL_ERROR,tr("通道映射文件下发失败"));
				SysStateEvent_OnTestStoped();
				return 0;
			}
		}

		if (m_bSystemParasChanged)
		{
			nRet = SendSystemParaCmd();
			if(nRet == STT_CMD_ExecStatus_SUCCESS)
			{
				CLogPrint::LogString(XLOGLEVEL_INFOR,tr("系统参数设置下发完成"));
				m_bSystemParasChanged = FALSE;
			}
			else
			{
				CLogPrint::LogString(XLOGLEVEL_ERROR,tr("系统参数设置下发失败"));
				SysStateEvent_OnTestStoped();
				return 0;
			}
		}

		if (m_bIECParasChanged && g_oSystemParas.m_nHasDigital)
		{
			nRet = SendIECParaCmd();
			if(nRet == STT_CMD_ExecStatus_SUCCESS || nRet == STT_CMD_ExecStatus_ACK || nRet == STT_CMD_ExecStatus_NULL)
			{
				CLogPrint::LogString(XLOGLEVEL_INFOR,tr("IEC参数设置下发完成"));
				m_bIECParasChanged = FALSE;
			}
			else if(nRet == STT_CMD_ExecStatus_TIMEOUT)
			{
				CLogPrint::LogString(XLOGLEVEL_INFOR,tr("IEC参数设置执行超时"));
			}
			else if(nRet == STT_CMD_ExecStatus_FAILURE)
			{
				CLogPrint::LogString(XLOGLEVEL_ERROR,tr("IEC参数设置执行失败"));
			}
		}

		ClearTestMngr();
		m_bStarted = true;

		nRet = SendStartCmd();
		if(nRet == STT_CMD_ExecStatus_SUCCESS)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,tr("开始测试."));
			RaiseSwitchInfo();
			return 1;
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,tr("开始测试命令下发失败."));
			SysStateEvent_OnTestStoped();
			m_bStarted = false;
			return 0;
		}
	}

	return 0;
}

void TestWinBase::slot_UpdateTestResource()
{
	OnUpdateTestResource(TRUE);
}

void TestWinBase::StartPowerWidget()
{
	if (m_powerdiagramWidget)
	{
		m_powerdiagramWidget->TimerStart();
	}
}

void TestWinBase::StopPowerWidget(bool bUpdate)
{
	if(m_powerdiagramWidget)
	{
		m_powerdiagramWidget->TimerStop(bUpdate);
	}
}

void TestWinBase::OnViewTestStart()
{
//	slot_ClearAllResult();  20220715 zhouhj 已在开始测试槽函数中增加清除结果操作

	if (m_pGooseParaWidget)
	{
		g_theSttXTestMngrBaseApp->m_bGooseFlag = true;
		m_pGooseParaWidget->SetGooseDisabled(true);
	}

	if (m_pFT3Widget)
	{
		g_theSttXTestMngrBaseApp->m_bFt3Flag=true;
		m_pFT3Widget->SetGooseDisabled(true);
	}
}

void TestWinBase::OnViewTestStop()
{
	if (m_pGooseParaWidget)
	{
		g_theSttXTestMngrBaseApp->m_bGooseFlag = false;
		m_pGooseParaWidget->SetGooseDisabled(false);
	}
	
	if (m_pFT3Widget)
	{
		g_theSttXTestMngrBaseApp->m_bFt3Flag=false;
		m_pFT3Widget->SetGooseDisabled(false);
	}
	
	//20240514 suyang 增加在停止测试的时候更新报告头 停止时间
	if (m_pSttXTestMngrHtmlRpt)
	{
		QSttReportViewHtml* pReportView= (QSttReportViewHtml*)m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
		pReportView->UpdateReportHead_StartEndTestTime(FALSE,TRUE);
	}
// 	m_bStarted = false;

	EndBinStateOnStarting();//恢复灯，全部置成关闭状态；
}

void TestWinBase::OnUpdateTestResource(BOOL bCreateChMaps)
{
	if (bCreateChMaps)
	{
		g_oSttTestResourceMngr.CreateChMaps();//打开本地通道映射文件
	}

	initLocalSysPara();
	g_oSttTestResourceMngr.ValidHardRsChMaps();//验证通道映射文件中硬件信息是否在Device中存在，删除不存在的硬件信息，如果不存在，则根据Device信息，创建缺省
	g_oSttTestResourceMngr.CreateSoftRsCh();
	g_oSttTestResourceMngr.CreateRtDataMngr();
	g_oSttTestResourceMngr.SaveSystemParasFile();
	long nMergeCurrCoef = 1;

	if (g_oSttTestResourceMngr.GetAnalogCurrentMergeCoef(nMergeCurrCoef))
	{
		g_oLocalSysPara.m_fAC_CurMax *= nMergeCurrCoef;
		g_oLocalSysPara.m_fAC_CurMin *= nMergeCurrCoef;
		g_oLocalSysPara.m_fDC_CurMax *= nMergeCurrCoef;
		g_oLocalSysPara.m_fDC_CurMin *= nMergeCurrCoef;
	}
}

void TestWinBase::UpdateToolButtons_BinInPart( int nIndexBin)
{
	//开入（最多10个）
	char strName[MAX_BINARYIN_COUNT] = "ABCDEFGHIJKLMNOP";		

	if (nIndexBin==1)
	{
		for(int i  =  0;  i  <  m_oBinInToolBtnList.size()  ;  i++)
		{
			if (i  < 4)
			{
				m_oBinaryConfig.m_binIn[i].nSelect = 0;	
#ifdef STT_USE_Resource_Img_
				initToolbutton(m_oBinInToolBtnList.at(i),  QString(strName[i]),  QString(":/images/SwichIcon/switch_null.png"));
#else
				initToolbutton(m_oBinInToolBtnList.at(i),  QString(strName[i]),  QString("./images/SwichIcon/switch_null.png"));

#endif
			}
			else 
			{	
				m_oBinaryConfig.m_binIn[i].nSelect = 1;
#ifdef STT_USE_Resource_Img_

				initToolbutton(m_oBinInToolBtnList.at(i),  QString(strName[i]),  QString(":/images/SwichIcon/switch_open.png"));
#else
				initToolbutton(m_oBinInToolBtnList.at(i),  QString(strName[i]),  QString("./images/SwichIcon/switch_open.png"));

#endif
			}
		}
	}
	else if (nIndexBin==0)
	{
		for(int i  =  0;  i  <  m_oBinInToolBtnList.size()  ;  i++)
		{
			if (i  >= 4 && i < 8)
			{
				m_oBinaryConfig.m_binIn[i].nSelect = 0; 
#ifdef STT_USE_Resource_Img_
				initToolbutton(m_oBinInToolBtnList.at(i),  QString(strName[i]),  QString(":/images/SwichIcon/switch_null.png"));

#else
				initToolbutton(m_oBinInToolBtnList.at(i),  QString(strName[i]),  QString("./images/SwichIcon/switch_null.png"));
#endif
			}
			else 
			{	
				m_oBinaryConfig.m_binIn[i].nSelect = 1;
#ifdef STT_USE_Resource_Img_
				initToolbutton(m_oBinInToolBtnList.at(i),  QString(strName[i]),  QString(":/images/SwichIcon/switch_open.png"));
#else
				initToolbutton(m_oBinInToolBtnList.at(i),  QString(strName[i]),  QString("./images/SwichIcon/switch_open.png"));

#endif
			}
		}
	}
}

//FT3发布
void TestWinBase::AddFT3Widget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	QTabWidget* pCommonTab = GetCommonTab_UI();

	int nFT3Block = 0;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while(pos)
	{
		CIecCfgDataBase* pIecCfgDataBase = (CIecCfgDataBase *)pIecCfgDatasSMV->GetNext(pos);
		if (pIecCfgDataBase->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA && pIecCfgDataBase->m_nUseFlag)
		{
			nFT3Block ++;
		}
	}

	if (pCommonTab==NULL)
	{
		return;	
	}

	if((m_pFT3Widget == NULL)&&(g_oSystemParas.IsDigitalOutputFT3()) &&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0) && (nFT3Block > 0))
	{
		m_pFT3Widget=new QFT3ParaWidget(pIecCfgDatasSMV);
		CString strTitle=_T("FT3发布");
 		pCommonTab->insertTab(2,m_pFT3Widget,strTitle);	
 			
		connect(m_pFT3Widget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
	else if ((m_pFT3Widget != NULL)&&(!g_oSystemParas.IsDigitalOutputFT3()))
	{
		disconnect(m_pFT3Widget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		pCommonTab->removeTab(pCommonTab->indexOf(m_pFT3Widget));
		delete m_pFT3Widget;
		m_pFT3Widget = NULL;
	}
	else if ((m_pFT3Widget != NULL)&&(g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0))
	{
		if(nFT3Block > 0)
		{
		disconnect(m_pFT3Widget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		m_pFT3Widget->InitFT3Table(pIecCfgDatasSMV);
		connect(m_pFT3Widget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
	}
		else
		{
			disconnect(m_pFT3Widget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
			pCommonTab->removeTab(pCommonTab->indexOf(m_pFT3Widget));
			delete m_pFT3Widget;
			m_pFT3Widget = NULL;
		}
	}
}

void TestWinBase::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
{
	QTabWidget* pCommonTab = GetCommonTab_UI();

	if (pCommonTab == NULL)
	{
		return;
	}

	if ((m_pGooseParaWidget == NULL)&&(g_oSystemParas.m_nHasDigital)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC > 0))//更新前无GOOSE界面,更新后需要GOOSE界面
	{
		m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas);
		pCommonTab->insertTab(1,m_pGooseParaWidget,tr("GOOSE数据发送"));
		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_RepairDataChanged()));
	}
	else if ((m_pGooseParaWidget != NULL)&&(!g_oSystemParas.m_nHasDigital))//更新前有GOOSE界面,更新后不需要
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_RepairDataChanged()));
		pCommonTab->removeTab(pCommonTab->indexOf(m_pGooseParaWidget));
		delete m_pGooseParaWidget;
		m_pGooseParaWidget = NULL;
	}
	else if ((m_pGooseParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC> 0))
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_RepairDataChanged()));
		m_pGooseParaWidget->initGoosePubTable(pCfgGoutDatas);
		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_RepairDataChanged()));
	} 
	else if ((m_pGooseParaWidget != NULL)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC == 0))
	{
		//20240517 suyang 第一次联机光口数量没有更新，上面会新建一个GOOSE，更新光口数量后重新更新的话，GOOSE数据发送Tab已经存在，应删除
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_RepairDataChanged()));
		pCommonTab->removeTab(pCommonTab->indexOf(m_pGooseParaWidget));
		delete m_pGooseParaWidget;
		m_pGooseParaWidget = NULL;
	}
}

void TestWinBase::InitTestTable()
{
	if (m_TestTable == NULL)
	{
		return;
	}

	connect(m_TestTable,SIGNAL(sig_AddItemBF()),this,SLOT(slot_AddItemBF()),Qt::UniqueConnection);
	connect(m_TestTable,SIGNAL(sig_AddItemAF()),this,SLOT(slot_AddItemAF()),Qt::UniqueConnection);
	connect(m_TestTable,SIGNAL(sig_DeleteCurr()),this,SLOT(slot_DeleteCurr()),Qt::UniqueConnection);
	connect(m_TestTable,SIGNAL(sig_Delete_N_1()),this,SLOT(slot_Delete_N_1()),Qt::UniqueConnection);
	connect(m_TestTable,SIGNAL(sig_ClearCurrResult()),this,SLOT(slot_ClearCurrResult()),Qt::UniqueConnection);
	connect(m_TestTable,SIGNAL(sig_ClearAllResult()),this,SLOT(slot_ClearAllResult()),Qt::UniqueConnection);
	connect(m_TestTable,SIGNAL(sig_SelectAll()),this,SLOT(slot_SelectAll()),Qt::UniqueConnection);
	connect(m_TestTable,SIGNAL(sig_UnselectAll()),this,SLOT(slot_UnselectAll()),Qt::UniqueConnection);
	
	m_TestTable->SetData(&m_oTmtTestMngr);//调换了一下顺序,初始化的时候不触发切换行事件,否则表达式为空时会报错
	//需在表达式初始化之后,手动调用m_TestTable->SetCurrentRow(0);    20210817 sf

	connect(m_TestTable,SIGNAL(sig_Table_cellClicked(int)),this,SLOT(slot_Table_CellClicked(int)),Qt::UniqueConnection);
}
/*
int TestWinBase::GetTestItemTableRow(PTMT_PARAS_HEAD pCurr)
{
	for (int i=0;i<m_oTmtTestMngr.m_nCount;i++)
	{
		if(m_oTmtTestMngr.m_pParasBuffer[i] == pCurr)
		{
			return i;
		}
	}

	return -1;
}
*/


CString TestWinBase::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _P_GetMoudleFileName();
	strFile += _T(".");
	//strFile += m_oTmtTestMngr.m_pszParaFilePostfix;
	strFile += STT_UPDATE_TEST_XML_POSTFIX;//2024-05-07 wuxinyi 修改缺省模板文件

	return strFile;
}

void TestWinBase::initTestParas()
{
	if (!OpenTestTestMngrFile(_T("")))
	{
		InitDefaultTestItems();
		InitGoosePubDataGroups();
		InitFT3PubDataGroups();
	}

	//2021-9-12  lijunqing  初始化的时候，还没创建控件，不能显示
	//InitUI_OpenParas();
}
/*
BOOL TestWinBase::IsValidTestParasFile(const CString& strParasFile,BOOL bOpen)
{
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != m_oTmtTestMngr.m_pszParaFilePostfix)
	{
		return FALSE;
	}

	if(bOpen && !IsFileExist(strParasFile))
	{
		return FALSE;
	}

	return TRUE;
}
*/
// 评估 添加测试项的时候; 2021-7-23
//如果是新建测试点，需要根据m_strExprValueID中定义的数据，初始化测试点的各表达式
//pszExprGroupPath="Common",  "Gnd1"
//<group name="通用" id="Common" data-type="" value="">
//例如:<group name="接地距离一段" id="Gnd1" data-type="" value="">
/*
<group name="通用" id="Common" data-type="" value="">
	<group name="跳A" id="TtripA" data-type="" value="">
		<data name="表达式" id="exp1" data-type="" value="TtripA &gt; 0"/>
		<data name="表达式" id="exp1" data-type="" value="TtripA &lt;= 0"/>
		<data name="表达式" id="exp2" data-type="" value="(TtripA &gt; 0) &amp;&amp;  (TtripA &lt; TSet2)"/>
		<data name="表达式" id="exp3" data-type="" value="(TtripA &gt; 0) &amp;&amp; (TtripA &lt; g_TerrAbs)"/>
	</group>
	<group name="跳B" id="TtripB" data-type="" value="">

*/
/*
void TestWinBase::InitTestParaExpr(PTMT_PARAS_HEAD pItemPara, char *pszExprGroupPath, bool bInit )
{
	long nIndex = 0;

	QRsltExprMngr::InitDataGroupByID(pszExprGroupPath);
	//pFind = <group name="通用" id="Common" data-type="" value="">
	CDataGroup *pFind =  NULL;//QRsltExprMngr::GetRsltExprMngr()->FindDataGroupByID(pszExprGroupPath);

	//从第XML文件DataDef中读取评估项的定义,比如有几个跳A,跳B,跳C 和几个结果数据的定义；
	CSttTmtRsltExprDefine*  pSttTmtRsltExprDefine  = g_oSttTmtRsltExprDefineMngr.FindRsltExprDefine(pItemPara->m_pszMacroID);
	
	if (pSttTmtRsltExprDefine->m_pExprDatasDef == NULL&&pSttTmtRsltExprDefine->m_pExprViewDatasDef==NULL)
		return;

	TMT_PARAS_RSLT_EXPR_MNGR *pExprMngr  =  &pItemPara->m_oRsltExprMngr;
	
	if (bInit)//当是TRUE的时候 说明SAVE文件中已经有了表达式的存储；当不相等的时候才往下执行，给结构体中赋初值，保存的时候把结构体保存到XML文件中。
	{
		// 当相等的时候 直接返回，说明SAVE文件中已经有了表达式的存储；当不相等的时候才往下执行，给结构体中赋初值，保存的时候把结构体保存到XML文件中。
		if (pSttTmtRsltExprDefine->m_pExprDatasDef->GetCount() == pExprMngr->m_nCount)
			return;
	}

	pExprMngr->m_nCount  =  pSttTmtRsltExprDefine->m_pExprDatasDef->GetCount(); //获取有几个跳A,跳B,跳C 这样的表达式的数量；
	strcpy(pExprMngr->m_pszExprGroupID, pszExprGroupPath);                                        //从外面传进来的ExprGroup 存入m_pszExprGroupID中；
	
	TMT_PARAS_RSLT_EXPR Expr  ;
	CDataGroup *pDataExprGroup = NULL;
	CDvmData *pData = NULL;

	for (nIndex  =  0; nIndex  <  pExprMngr->m_nCount; nIndex++)
	{
		//<data name="跳A" id="TtripA" data-type="" value=""/>
		pData = (CDvmData*)pSttTmtRsltExprDefine->m_pExprDatasDef->GetAtIndex(nIndex);
		
		//<group name="跳A" id="TtripA" data-type="" value="">
		pDataExprGroup  =  (CDataGroup *)QRsltExprMngr::FindDataGroupByID(pData->m_strID);

		//<data name="表达式" id="exp1" data-type="" value="TtripA &gt; 0"/>
		//初始化为第一个表达式是有问题的，可以初始化为空
		pData = (CDvmData*)pDataExprGroup->GetHead();  
		
		//新建数据表达式，并初始化
		//pExpr = new TMT_PARAS_RSLT_EXPR;

		//初始化为第一个表达式是有问题的，可以初始化为空
		//CString_to_char(pData->m_strValue,  pExpr->m_pRsltExpr);
		//Expr.m_pRsltExpr[0] = pData->m_strValue.GetString();//0;
		CString_to_char(pData->m_strID, Expr.m_pszExprDataID);

		//这里我又改成了初始化为第一个表达式，mym 2021-7-26;
		CString_to_char(pData->m_strValue, Expr.m_pRsltExpr);

		pExprMngr->m_RsltExprs[nIndex] = Expr;
	}

	AdjustTestParaExpr(pItemPara);
}
*/

/*
// 本函数专门用来初始化用的；就是当XML文件中没有表达式的时候
void TestWinBase::InitTestParaExpr_Ex(PTMT_PARAS_HEAD pItemPara, char *pszExprGroupPath)
{
	long nIndex = 0;

	QRsltExprMngr::InitDataGroupByID(pszExprGroupPath);

	//pFind = <group name="通用" id="Common" data-type="" value="">
	CDataGroup *pFind =  NULL;//QRsltExprMngr::GetRsltExprMngr()->FindDataGroupByID(pszExprGroupPath);

	//从第XML文件DataDef中读取评估项的定义,比如有几个跳A,跳B,跳C 和几个结果数据的定义；
	CSttTmtRsltExprDefine*  pSttTmtRsltExprDefine  = g_oSttTmtRsltExprDefineMngr.FindRsltExprDefine(pItemPara->m_pszMacroID);
		
	if (pSttTmtRsltExprDefine->m_pExprDatasDef == NULL&&pSttTmtRsltExprDefine->m_pExprViewDatasDef==NULL)
		return;

	TMT_PARAS_RSLT_EXPR_MNGR *pExprMngr  =  &pItemPara->m_oRsltExprMngr;

	// 当相等的时候 直接返回，说明SAVE文件中已经有了表达式的存储；当不相等的时候才往下执行，给结构体中赋初值，保存的时候把结构体保存到XML文件中。
	if (pSttTmtRsltExprDefine->m_pExprDatasDef->GetCount() == pExprMngr->m_nCount)
		return;

	pExprMngr->m_nCount  =  pSttTmtRsltExprDefine->m_pExprDatasDef->GetCount(); //获取有几个跳A,跳B,跳C 这样的表达式的数量；
	strcpy(pExprMngr->m_pszExprGroupID, pszExprGroupPath);                                        //从外面传进来的ExprGroup 存入m_pszExprGroupID中；

	TMT_PARAS_RSLT_EXPR Expr  ;
	CDataGroup  *  pDataExprGroup = NULL;
	CDvmData  * pData = NULL;

	for (nIndex  =  0; nIndex  <  pExprMngr->m_nCount; nIndex++)
	{
		//<data name="跳A" id="TtripA" data-type="" value=""/>
		pData = (CDvmData*)pSttTmtRsltExprDefine->m_pExprDatasDef->GetAtIndex(nIndex);

		//<group name="跳A" id="TtripA" data-type="" value="">
		pDataExprGroup  =  (CDataGroup *)QRsltExprMngr::FindDataGroupByID(pData->m_strID);

		//<data name="表达式" id="exp1" data-type="" value="TtripA &gt; 0"/>
		//初始化为第一个表达式是有问题的，可以初始化为空
		pData = (CDvmData*)pDataExprGroup->GetHead();  

		//新建数据表达式，并初始化
		//pExpr = new TMT_PARAS_RSLT_EXPR;

		//初始化为第一个表达式是有问题的，可以初始化为空
		//CString_to_char(pData->m_strValue,  pExpr->m_pRsltExpr);
		//Expr.m_pRsltExpr[0] = pData->m_strValue.GetString();//0;
		CString_to_char(pData->m_strID, Expr.m_pszExprDataID);

		//这里我又改成了初始化为第一个表达式，mym 2021-7-26;
		CString_to_char(pData->m_strValue, Expr.m_pRsltExpr);

		pExprMngr->m_RsltExprs[nIndex] = Expr;
	}

	AdjustTestParaExpr(pItemPara);
}
*/

void TestWinBase::CalAxisInstructPoint(float fZK,float fAng)
{
}

void TestWinBase::InitDockSwitch(tmt_BinaryIn *pBinaryIn)
{
	for (int i = 0;i < 20; i++)
	{
		m_oBinaryConfig.m_binIn[i].nSelect = (pBinaryIn + i)->nSelect;
	}
	
	UpdateToolButtons();

}


void TestWinBase::UpdateCurveData()
{
#ifdef _GRADIENT_PLOT_
	if(m_pTimeResponseWidget)
	{
		//此处同步初始化标记 20230605 zhouhj
		m_pTimeResponseWidget->m_pChlTimePlotEx->m_bInited = m_pTimeResponseWidget->isSyncInit();

		m_oGridentTimeResponse_Lock.lockForWrite();
		CSttGlobalRtDataMngr *pRtDataMngr = &g_oSttTestResourceMngr.m_oRtDataMngr;
		CSttMacroChannels *pMacroChs = pRtDataMngr->m_pMacroChannels;
		CSttMacroChannel *pMacroCh = NULL;
		tmt_rtdata_ch* pRtData = NULL;
		tmt_rtdata_ch tmpRtData;
		int nIndex = 0;
		double dLastTime = 0;

		if (!pMacroChs->m_oHisRealTimesBuf.GetLastMemVal(dLastTime))
		{
			m_oGridentTimeResponse_Lock.unlock();
			return;
		}

		if (!m_pTimeResponseWidget->m_pChlTimePlotEx->m_bInited)
		{
			m_oGridentTimeResponse_Lock.unlock();
			return;
		}

		if (m_pTimeResponseWidget->m_pChlTimePlotEx->m_rtDataList.size()==0)
		{
			m_oGridentTimeResponse_Lock.unlock();
			return;
		}

		m_pTimeResponseWidget->m_pChlTimePlotEx->m_dLastTime = dLastTime;
		m_pTimeResponseWidget->m_pBinInTimeResponsePlot->m_dLastTime = dLastTime;
		m_pTimeResponseWidget->m_pBinOutTimeResponsePlot->m_dLastTime = dLastTime;

		CChlTimeSignal* pNewSignal = m_pTimeResponseWidget->m_pChlTimePlotEx->NewSignal();
		POS pos = m_pTimeResponseWidget->m_pChlTimePlotEx->m_oMacroChannels.GetHeadPosition();
		while(pos)
		{
			pMacroCh = (CSttMacroChannel*)m_pTimeResponseWidget->m_pChlTimePlotEx->m_oMacroChannels.GetNext(pos);
			pRtData = m_pTimeResponseWidget->m_pChlTimePlotEx->m_rtDataList.at(nIndex);

			if (pRtData && pMacroCh->m_oHisDataBuf.GetLastMemVal(tmpRtData))
			{
				pRtData->m_fMag = tmpRtData.m_fMag;
				pRtData->m_fAng = tmpRtData.m_fAng;
				pRtData->m_fFreq = tmpRtData.m_fFreq;

				m_pTimeResponseWidget->m_pChlTimePlotEx->AppendSignalData(pNewSignal,dLastTime,&tmpRtData);
			}

			nIndex++;
		}

		m_pTimeResponseWidget->m_pChlTimePlotEx->AppenSignalInfo(pNewSignal);
		m_pTimeResponseWidget->m_pBinInTimeResponsePlot->AppendSignalData(dLastTime);
		m_pTimeResponseWidget->m_pBinOutTimeResponsePlot->AppendSignalData(dLastTime);

		//		emit sig_UpdateCurveData();
		m_oGridentTimeResponse_Lock.unlock();
	}
#endif
}

void TestWinBase::slot_ViewTestStart()
{
	OnViewTestStart();
}

void TestWinBase::slot_ViewTestStop()
{
	OnViewTestStop();
}

void TestWinBase::slot_ViewTestLink(bool b)
{
	if (!b)//zhouhj  在socket中断后，将该值置为false
	{
		m_bViewTestStarted = false;
		m_bChMapsChanged = TRUE;
		m_bSystemParasChanged = TRUE;
		m_bIECParasChanged = TRUE;
		emit sig_OnUpdateGpsTime(0,0,0,_T(""));//断开连接后,将对时状态改为未对时
	}

	OnViewTestLink(b);
}	

void TestWinBase::slot_stop()
{
	long nRet = SendStopCmd();

	if(nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("测试停止"));
		emit sig_ViewTestStop();
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,tr("停止命令下发失败"));
		SysStateEvent_OnTestStoped();
	}

	//20240514 suyang 增加在停止测试的时候更新报告头 停止时间
	if (m_pSttXTestMngrHtmlRpt)
	{
		QSttReportViewHtml* pReportView= (QSttReportViewHtml*)m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
		pReportView->UpdateReportHead_StartEndTestTime(FALSE,TRUE);
	}

	
}

void TestWinBase::SetPlotDigitMaxMinValue()
{
	double dUMin,dUMax,dIMin,dIMax;

	if (!g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
	{
		dUMin = 0;
		dUMax = 130;
		dIMin = 0;
		dIMax = 30;
	}
	else
	{
		dUMin = 0;
		dUMax = g_oLocalSysPara.m_fAC_VolMax;
		dIMin = 0;
		dIMax = g_oLocalSysPara.m_fAC_CurMax;
	}

	if(m_pTimeResponseWidget != NULL)
	{
		m_pTimeResponseWidget->ChangeListType(amplitude_type,dUMin,dUMax,dIMin,dIMax);
	}
}

void TestWinBase::slot_SysParasHasChanged(BOOL bChMapsHasChanged)
{
	if (bChMapsHasChanged)
	{
		OnUpdateTestResource(FALSE);
		SetPlotDigitMaxMinValue();
	}

	m_bChMapsChanged = TRUE;
	m_bSystemParasChanged = TRUE;
	m_bIECParasChanged = TRUE;

	if (OnConnectTestApp())//zhouhj 20210930 如果已经联机成功,则直接下发系统参数命令
	{
		long nRet = SendSystemParaCmd();

		if(nRet == STT_CMD_ExecStatus_SUCCESS)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,tr("系统参数设置下发完成"));
			m_bSystemParasChanged = FALSE;
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,tr("系统参数设置下发失败"));
		}
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,tr("联机失败,无法下发系统参数."));
	}
}

void TestWinBase::slot_OffLineSelChanged()
{
 	m_bSystemParasChanged = TRUE;
 	m_bChMapsChanged = TRUE;
	m_bIECParasChanged = TRUE;
 	OnUpdateTestResource(TRUE);

	if (g_bTestAppConnect)
	{
		FreeXClientEngine();//脱机选择改变后,需要中断与测试仪的连接,如果重新联机,需要重新获取测试仪硬件信息,硬件信息匹配后,才能控制输出
		g_bTestAppConnect = false;
	}
}

void TestWinBase::slot_setSys()
{
	QSysParasSetDialog oSysParas;
	oSysParas.initUI();

	if (oSysParas.exec() == QDialog::Accepted)
	{
		slot_SysParasHasChanged(oSysParas.m_bOutputTypeHasChanged);
		UpdateSettingParas();//柔直模块更新整定值
	}
}

void TestWinBase::slot_OffLineSel()
{
	QOffLineDlg oOffLineDlg;
	oOffLineDlg.initUI();

	connect(&oOffLineDlg, SIGNAL(sig_OffLineSelChanged()), this, SLOT(slot_OffLineSelChanged()));
	oOffLineDlg.exec();
	disconnect(&oOffLineDlg,SIGNAL(sig_OffLineSelChanged()),this,SLOT(slot_OffLineSelChanged()));
}

void TestWinBase::slot_setSetting()
{
#ifndef NOT_USE_SetSetting
	SettingValueDialog dig(this);
	connect(&dig,SIGNAL(sig_ClickOk()),this,SLOT(slot_SettingValueChanged()));
	dig.exec();
	disconnect(&dig,SIGNAL(sig_ClickOk()),this,SLOT(slot_SettingValueChanged()));
#endif
}

void TestWinBase::slot_setCustom()
{
	m_oDcSetDlg.setData(m_bCustomACOutputStarted,m_bAuxDCOutputStarted);
	m_oDcSetDlg.exec();
}

void TestWinBase::slot_connect()
{
	bool bUseScanLan = IsUseScanLan();//单击事件响应用于测试仪脱机window下,此时部分模块暂不响应网卡扫描功能
	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	if (pSttDevConfig->m_nDoubleClickEdit != 0)
	{
		bUseScanLan = 1;
	}

	QScanLanTesterDlg oScanLanDlg(NULL,bUseScanLan);
	oScanLanDlg.initUI();

	if (bUseScanLan)
	{
		oScanLanDlg.slot_ScanClicked();
	}
	connect(&oScanLanDlg, SIGNAL(sig_TesterIP_Changed()), this, SLOT(slot_TesterIP_Changed()));
	oScanLanDlg.exec();
	disconnect(&oScanLanDlg, SIGNAL(sig_TesterIP_Changed()), this, SLOT(slot_TesterIP_Changed()));
// 	m_oCommTestAppCfgDlg.InitParas(g_oSttTestAppCfg.GetTestAppIP(),g_oSttTestAppCfg.GetTestServerPort());
// 	m_oCommTestAppCfgDlg.exec();
}

/*
void TestWinBase::slot_logDebugCfg()
{
	CDebugCfgDlg dlg(this);
	dlg.exec();
}
*/

void TestWinBase::slot_ChRsMaps_Dlg()
{
	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	if (pSttDevConfig->m_nSetPassword)
	{
		QPasswordDlg oPasswordDlg;
		oPasswordDlg.initUI();
		oPasswordDlg.exec();

		if (!oPasswordDlg.m_bIsCorrected)
		{
			return;
		}
	}

	QChMapsDlg oChMapsDlg;
	oChMapsDlg.initUI();
	connect(&oChMapsDlg, SIGNAL(sig_UpdateChRsMaps(BOOL)), this, SLOT(slot_UpdateChRsMaps(BOOL)));
	oChMapsDlg.exec();
	disconnect(&oChMapsDlg, SIGNAL(sig_UpdateChRsMaps(BOOL)), this, SLOT(slot_UpdateChRsMaps(BOOL)));
}

void TestWinBase::slot_AuxDC_Dlg()
{
	QAuxDCOutputDlg oAuxDCOutputDlg;
	oAuxDCOutputDlg.initUI();
	connect(&oAuxDCOutputDlg, SIGNAL(sig_UpdateAuxDCOutput()), this, SLOT(slot_UpdateAuxDCOutput()));
	oAuxDCOutputDlg.exec();
	disconnect(&oAuxDCOutputDlg, SIGNAL(sig_UpdateAuxDCOutput()), this, SLOT(slot_UpdateAuxDCOutput()));
}

void TestWinBase::slot_ModulesGearSwitch_Dlg()
{
	QModuleSetDlg oModuleSetDlg;
	oModuleSetDlg.initUI();
	connect(&oModuleSetDlg, SIGNAL(sig_UpdateModulesGear(bool)), this, SLOT(slot_UpdateModulesGear(bool)));
	oModuleSetDlg.exec();
	disconnect(&oModuleSetDlg, SIGNAL(sig_UpdateModulesGear(bool)), this, SLOT(slot_UpdateModulesGear(bool)));
}

void TestWinBase::slot_LuminousPower_Dlg()
{
	QLuminousPowerDlg oLuminousPowerDlg;
 	CDataGroup *pFiberCopy=(CDataGroup*)(&g_oSttTestResourceMngr.m_oFiberMsgGroup)->Clone();
 	oLuminousPowerDlg.InitData(pFiberCopy);
    oLuminousPowerDlg.exec();
}

void TestWinBase::slot_TesterIP_Changed()
{
	g_oSttTestAppCfg.SttOpen(g_oSttTestAppCfg.GetSttCfgFile());//zhouhj 20211005 修改IP地址后,重新读取IP地址等信息

	if (g_bTestAppConnect)
	{
		FreeXClientEngine();//脱机选择改变后,需要中断与测试仪的连接,如果重新联机,需要重新获取测试仪硬件信息,硬件信息匹配后,才能控制输出
		g_bTestAppConnect = false;
	}

	OnConnectTestApp(g_oSttTestAppCfg.GetTestAppIP(), g_oSttTestAppCfg.GetTestServerPort());
}

void TestWinBase::slot_UpdateModulesGear(bool bMergeCurrHasChanged)
{
	if (bMergeCurrHasChanged)
	{
		m_bChMapsChanged = TRUE;
		OnUpdateTestResource(FALSE);
	}

	if (!OnConnectTestApp())
	{
		return;
	}

	long nRet = SendModulesGearSwitchCmd();

	if(nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("模块档位切换命令下发完成"));
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,tr("模块档位切换命令下发失败"));
	}
}

void TestWinBase::slot_UpdateAuxDCOutput()
{
	UpdateAuxDcEnabled();

	if (!OnConnectTestApp())
	{
		return;
	}

	long nRet = SendAuxDCOutputCmd();

	if(nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("辅助直流输出命令下发完成"));
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,tr("辅助直流输出命令下发失败"));
	}
}

void TestWinBase::slot_UpdateChRsMaps(BOOL bSysParasHasChanged)
{
	m_bChMapsChanged = TRUE;
	OnUpdateTestResource(FALSE);

	if (bSysParasHasChanged)
	{
		m_bSystemParasChanged = TRUE;
		m_bIECParasChanged = TRUE;
	}
}


/*
BOOL TestWinBase::IsTestAppExist(const CString &strIP)
{
	char pszIP[20];
	CString_to_char(strIP,pszIP);
	return xping(pszIP);
}
*/

BOOL TestWinBase::OnConnectTestApp(const CString &strIP, long nPort)
{
	if(!IsTestAppExist(strIP))
	{
		g_bTestAppConnect = false;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("与当前测试仪建立连接失败(%s)."),strIP.GetString());
	}
	else
	{
		g_bTestAppConnect = connectTestApp(strIP,nPort);
	}

	m_bChMapsChanged = TRUE;//每次进行联机操作时固定将该参数置为TRUE,表示下一次开始测试后，需要重新下载通道映射文件，因为Socket中断后，可能已经连接了另外一台测试仪
	m_bSystemParasChanged = TRUE;
	m_bIECParasChanged = TRUE;
	signalLink();
	OnViewTestLink(g_bTestAppConnect);
	return g_bTestAppConnect;
}

BOOL TestWinBase::OnConnectTestApp()
{
	if (g_bTestAppConnect)
	{
		return TRUE;
	}

	CString strIP = g_oSttTestAppCfg.GetTestAppIP();
	long nPort = g_oSttTestAppCfg.GetTestServerPort();

	return OnConnectTestApp(strIP,nPort);
}

void TestWinBase::slot_IEC()
{
#ifdef STT_IEC_PARSE_USE_Iec61850Config
	CString strIXMLFileName = _P_GetConfigPath();
	strIXMLFileName += QString("SttIecConfig.ixml");

	if(!IsFileExist(strIXMLFileName)) 
		return;

	m_oIecConfig.ExitEngine();
	m_oIecConfig.setControl(NULL);

	QString strIEC61850Config("Iec61850Config.TestEngine");
	m_oIecConfig.setControl(strIEC61850Config);
	CDvmDataset oDvmDataset;
	CString strValue,strXmlText;
	strValue.Format("%d",8);//暂时固定8光口
	oDvmDataset.AddNewData("","fiber-num","long",strValue);
	strValue.Format("%d",g_nBinExCount);
	oDvmDataset.AddNewData("","binex-num","long",strValue);
	strValue.Format("%d",g_nBoutExCount);
	oDvmDataset.AddNewData("","boutex-num","long",strValue);
	oDvmDataset.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys,strXmlText);
	m_oIecConfig.CommConfig(strXmlText);

	m_oIecConfig.SetDispMode(_DISP_MODE_PN466);
	m_oIecConfig.SetWndMsg((unsigned int)(HWND)this->winId(), WM_IEC61850CFGFINISHED_MSG);
	showMinimized();
	m_oIecConfig.EditIecfgFile(strIXMLFileName);
	m_bIECParasChanged = TRUE;
#else
	QSttIecConfigDialogWin oIecConfigDlg(&g_oSttTestResourceMngr.m_oIecDatasMngr, this);
	oIecConfigDlg.InitUI();
	oIecConfigDlg.setWindowModality(Qt::WindowModal);
	oIecConfigDlg.m_pSclStation = &m_oSclStation;
	connect(&oIecConfigDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),SLOT(slot_IecCfgDataMngrUpdate()));
	oIecConfigDlg.exec();
	disconnect(&oIecConfigDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),this,SLOT(slot_IecCfgDataMngrUpdate()));
#endif
}

void TestWinBase::slot_IECCap()
{
	disconnect(m_pIECCapBtn, SIGNAL(clicked()), this, SLOT(slot_IECCap()));
	disconnect(m_IECCapAct, SIGNAL(triggered()), this, SLOT(slot_IECCap()));
#ifdef STT_USE_IecCap_

	m_bIsUsingIecCap = TRUE;

	InitKeyDB();
	InitSttIecRecord(&g_oSttTestAppCfg);
	CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();

	if (pXSttCap_61850 == NULL)
	{
		return;
	}

	if ((pXSttCap_61850->m_oCapDeviceAll.GetCount() == 0)&&(g_bSmartCap_RecordNow))//20220610 第一次进入的时,不用开启录波,在进入监视界面时,启动录波
	{
		g_bSmartCap_RecordNow = 0;
	}


	QSttIecCapDialog oSttIecCapDialog(this);
	oSttIecCapDialog.setWindowModality(Qt::NonModal);	//chenling 2024.5.14 改成非模态对话框
	oSttIecCapDialog.InitUI();
	oSttIecCapDialog.show();

	oSttIecCapDialog.StartDetect(true);
	oSttIecCapDialog.exec();
	m_bIsUsingIecCap = FALSE;

#endif
	connect(m_pIECCapBtn, SIGNAL(clicked()), this, SLOT(slot_IECCap()));
	connect(m_IECCapAct, SIGNAL(triggered()), this, SLOT(slot_IECCap()));
}

void TestWinBase::slot_IecCfgDataMngrUpdate()
{
	g_oSttTestResourceMngr.SaveDefaultIec61850Config();//保存xml	
	UpdateIECChannelsData();

	if (m_pGooseParaWidget /*|| m_pFT3Widget*/) //chenling 2024.4.26 修改IEC配置FT3界面不更新
	{
		long nParasSetSel = g_oSttTestResourceMngr.m_oIecDatasMngr.GetParasSetSel();

		UpdateGoutTab(TRUE);//zhouhj 手动模块参数无意义,对于状态序列及多个测试项目的更新全部克隆链表
	//	UpdateFT3Tab(TRUE);

		g_oSttTestResourceMngr.ValidIecParasSetSel();
		long nNewParasSetSel = g_oSttTestResourceMngr.m_oIecDatasMngr.GetParasSetSel();

		if ((nParasSetSel != nNewParasSetSel)&&(nNewParasSetSel))//如果参数设置改变为二次值输出了,需要重新更新界面,设置各通道的电压电流设置最大值
		{
			OnUpdateTestResource(FALSE);
		}
	}
	
	UpdateFT3Tab(TRUE);//20240417 suyang FT3界面不管存在与不存在都更新
	
	m_bIECParasChanged = TRUE;
}

void TestWinBase::slot_soeTest()
{
	m_oSoeDlg.setData(&m_oSoeParas);
	m_oSoeDlg.exec();
}

void TestWinBase::slot_CustomACOutputStart()
{
	long nRet = SendDefaultOutputCmd();

	if(nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("开始稳态量输出"));

		m_bCustomACOutputStarted = true;
		m_setSysAct->setDisabled(true);
		m_pChRsMaps_Action->setDisabled(true);
		m_pAuxDC_Action->setDisabled(true);  //zhouhj 20220217 运行过程中,允许设置输出直流
		m_pModulesGearSwitch_Action->setDisabled(true);

		if (m_pSetSysBtn)
		{
			m_pSetSysBtn->setDisabled(true);
		}

		if (m_pOffLineSelBtn)
		{
			m_pOffLineSelBtn->setDisabled(true);
		}
		
		m_VersionInforAct->setDisabled(true);
		m_updateLocalAct->setDisabled(true);
		m_updateTestAppAct->setDisabled(true);

		m_oDcSetDlg.setAusDCOutputState(m_bCustomACOutputStarted,m_bAuxDCOutputStarted);
	}
}

void TestWinBase::slot_CustomACOutputEnd()
{
	long nRet = SendDefaultOutputCmd();
	if(nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("停止稳态量输出"));

		m_bCustomACOutputStarted = false;
		if((!m_bViewTestStarted) && (!m_bAuxDCOutputStarted))
		{
			m_setSysAct->setDisabled(false);
			m_pChRsMaps_Action->setDisabled(false);
			m_pAuxDC_Action->setDisabled(false);
			m_pModulesGearSwitch_Action->setDisabled(false);

			if (m_pSetSysBtn)
			{
				m_pSetSysBtn->setDisabled(false);
			}

			if(m_pOffLineSelBtn)
				m_pOffLineSelBtn->setDisabled(false);
		}

		m_VersionInforAct->setDisabled(false);
		m_updateLocalAct->setDisabled(false);
		m_updateTestAppAct->setDisabled(false);

		m_oDcSetDlg.setAusDCOutputState(m_bCustomACOutputStarted,m_bAuxDCOutputStarted);
	}
}

void TestWinBase::slot_DASetStart(bool bChanged)
{
	m_bSystemParasChanged = bChanged;

	if(m_bSystemParasChanged)
	{
		long nRet = SendSystemParaCmd();
		if(nRet == STT_CMD_ExecStatus_SUCCESS)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,tr("系统参数设置下发完成"));

			if (m_pSetSysBtn)
			{
				m_pSetSysBtn->setDisabled(true);
			}

			if (m_pOffLineSelBtn)
			{
				m_pOffLineSelBtn->setDisabled(true);
			}

			m_bSystemParasChanged = FALSE;
		}
	}
}

void TestWinBase::slot_SoeStart()
{
	CSttTestCmd oSttCmd;
	GenerateTestCmdFromSoeParas(oSttCmd);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		long nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
		if(nRet == STT_CMD_ExecStatus_SUCCESS)
		{
			m_oSoeDlg.OnViewStartState(true);
			m_soeTestAct->setDisabled(true);

			if (m_pSoeTestBtn)
			{
				m_pSoeTestBtn->setDisabled(true);
			}

			m_VersionInforAct->setDisabled(true);
			m_updateLocalAct->setDisabled(true);
			m_updateTestAppAct->setDisabled(true);
		}
		else
		{
			m_oSoeDlg.OnViewStartState(false);
		}
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}
}

void TestWinBase::slot_SoeStop()
{
	long nRet = SendStopCmd();
	if(nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("停止SOE测试输出"));

		m_oSoeDlg.OnViewStopState(true);
		m_soeTestAct->setDisabled(false);

		if (m_pSoeTestBtn)
		{
			m_pSoeTestBtn->setDisabled(false);
		}

		m_VersionInforAct->setDisabled(false);
		m_updateLocalAct->setDisabled(false);
		m_updateTestAppAct->setDisabled(false);
	}
	else
	{	
		m_oSoeDlg.OnViewStopState(false);
	}
}

void TestWinBase::slot_SoeParasSave()
{
	SaveSoeParasFile();		//直接保存到默认文件
}

void TestWinBase::GetReportHeadFile(CString &strFile)
{
	strFile = stt_ui_GetParasFile("ReportHead_Paras.xml");
}

void TestWinBase::OpenReportHead()
{
	CString strPath;
	GetReportHeadFile(strPath);

	dvm_IncGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	m_oTestReportHead.OpenXmlFile(strPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	dvm_DecGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void TestWinBase::SaveReportHead()
{
	CString strPath;
	GetReportHeadFile(strPath);
	m_oTestReportHead.SaveXmlFile(strPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void TestWinBase::slot_reportSet()
{
	QSttReportHeadSetDlg dlg(&m_oTestReportHead, this);
	dlg.exec();

	if (dlg.m_nOkFlag == 1)
	{
		SaveReportHead();
		
		if (m_pSttXTestMngrHtmlRpt)
		{
			QSttReportViewHtml* pReportView= (QSttReportViewHtml*)m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
			if (pReportView == NULL)
			{
				return;
			}

			if (!dlg.m_bUpataHeadHtml)//只有选中的时候才会插入
			{
				InsertReportHead(&m_oTestReportHead,pReportView);
			}

			pReportView->UpdateReportHead(&m_oTestReportHead);
		}
	}
}

void TestWinBase::InsertReportHead( CDataGroup *pSttReport,QSttReportViewHtml* pReportViewHtml )
{
	if (pSttReport == NULL)
	{
		return;
	}
	CString strFile;
	POS pos = pSttReport->GetHeadPosition();
	CDataGroup *p = NULL;
	CString strItemID;

	// 20240510 suyang 重新勾选后需要将全部删除，再进行填充
	while (pos != NULL)
	{
		p = (CDataGroup*)pSttReport->GetNext(pos);

		strItemID = pSttReport->m_strID + "$" + p->m_strID;
		pReportViewHtml->DeleteRptHtml("", strItemID);
	}
	
	GetReportHeadHtmlFile(strFile);

	pReportViewHtml->InsertRptHtml(pSttReport->m_strID,"","",strFile);


}

CString TestWinBase::GetReportHeadHtmlFile(CString &strFile)
{
	stt_ui_OpenHtmlHeadFile("ReportHead.html",strFile);
	
	return strFile;
}
// 
// void TestWinBase::slot_ReportSetParaOk(reportSetPara &data)
// {
// 	
// }

void TestWinBase::slot_reportOpen()
{
/*
	QProcess *mp_helpProcess = new QProcess(this);
	QString fileName;
	fileName = QFileDialog::getOpenFileName(0, QObject::tr("打开文件"),"",QObject::tr("project(*.pdf)"));
	QStringList argument(fileName);
*/
}

void TestWinBase::slot_reportSave()
{
	if (m_pSttXTestMngrHtmlRpt == NULL)
	{
		return;
	}
/*
	QTextEdit *editor = m_ReportTextEdit;

	QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"),  
		QString(), "*.pdf");  
	if (!fileName.isEmpty()) {  

		// 如果文件后缀为空，则默认使用.pdf  
		if (QFileInfo(fileName).suffix().isEmpty())  
			fileName.append(".pdf");  
		QPrinter printer;  
		// 指定输出格式为pdf  
		printer.setOutputFormat(QPrinter::PdfFormat);  
		printer.setOutputFileName(fileName);  
		editor->print(&printer);  
	}  
*/
	//2022.5.18 caoxc 保存为html文件
// 	QString fileName = QFileDialog::getSaveFileName(this, tr("导出网页文件"),  
// 		QString(), "*.html");  
// 	if (!fileName.isEmpty()) {  
// 		// 如果文件后缀为空，则默认使用.html
// 		if (QFileInfo(fileName).suffix().isEmpty())  
// 			fileName.append(".html");
// 		//保存html
// 		m_pSttXTestMngrHtmlRpt->GenHtml();
// 		m_pSttXTestMngrHtmlRpt->UpdateRptHtml();
// 		m_pSttXTestMngrHtmlRpt->FillReport();
// 		QSttReportViewHtml* pReportView= (QSttReportViewHtml*)m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
// 		pReportView->SaveHtmlReportFile(fileName);
// 	} 

// 	CString fileName = QFileDialog::getSaveFileName(this, tr("导出word文件"),  
// 		QString(),_T("Word97-2003报告(*.doc);;Word报告(*.docx);;HTML报告(*.html);;PDF报告(*.pdf)") /*"报告文件(*.doc *.docx *.html)"*/);  
// 	

	QStringList strReportPostfix ;
	strReportPostfix.clear();
	strReportPostfix << _T("Word97-2003报告(*.doc)")<<_T("Word报告(*.docx))")<<_T("HTML报告(*.html))")<<_T("PDF报告(*.pdf)");
	CString fileName;
	fileName.clear();


	fileName = OpenSaveTemplateFileDlg(this,tr("导出word文件"),strReportPostfix,QString(),FALSE);
	
	if (!fileName.isEmpty()) 
	{  
		// 如果文件后缀为空，则默认使用.html
		if (QFileInfo(fileName).suffix().isEmpty())  
		{
			fileName.append(".doc");
		}
		//保存html
		m_pSttXTestMngrHtmlRpt->GenHtml();
		m_pSttXTestMngrHtmlRpt->UpdateRptHtml();
		m_pSttXTestMngrHtmlRpt->/*FillReport*/FillReportParent();//chenling 20240201 针对状态序列报告填充问题,状态序列重写了FillReport，其他模块调用的基类FillReport
		m_pSttXTestMngrHtmlRpt->UpdateReportState();
		QSttReportViewHtml* pReportView= (QSttReportViewHtml*)m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
		CString strPostfix;
		strPostfix = ParseFilePostfix(fileName);

		if (strPostfix == _T("html"))
		{
			pReportView->SaveHtmlReportFile(fileName);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("网页报告(%s)保存成功."),fileName.GetString());
		} 
		else if (strPostfix == _T("pdf"))
		{
			if (pReportView->SavePdfReportFile(fileName))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("PDF报告文件(%s)保存成功."),fileName.GetString());
			} 
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("PDF报告文件(%s)保存失败."),fileName.GetString());
			}
		} 
		else
		{
			if (pReportView->SaveWordReportFile(fileName))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("WORD报告文件(%s)保存成功."),fileName.GetString());
			} 
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("WORD报告文件(%s)保存失败."),fileName.GetString());
			}
		}
	}  

}

void TestWinBase::slot_viewTest()
{

	int nIndex = m_tabWidget->indexOf(m_testParaView);
	m_tabWidget->setCurrentIndex(nIndex);

	if (nIndex == 0)
	{

		m_pViewTestBtn->setStyleSheet("QToolButton { ""background-color:rgb(240,255,255);" "}");
		m_pViewReportBtn->setStyleSheet("QToolButton { ""background-color:rgb(245,245,245);" "}");
	}


	if (!SeparateShowTestView())
	{
		return;
	}

	MonitorTab* pMonitorTab = m_testParaView->getMonitor();
	QMainPara* pQMainPara = m_testParaView->getMainPara();

	if ((pMonitorTab == NULL)||(pQMainPara == NULL))
	{
		return;
	}

	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	if (pSttDevConfig->m_nDoubleClickEdit == 0)
	{
		if (pMonitorTab->isVisible())
		{
			pMonitorTab->setVisible(false);
			pQMainPara->setVisible(true);
		}
		else
		{
			pMonitorTab->setVisible(true);
			pQMainPara->setVisible(false);
		}
	}
}

void TestWinBase::slot_viewReport()
{
	if (m_pSttXTestMngrHtmlRpt == NULL)
	{
		return;
	}

	// 2022.5.13 caoxc
	if (!m_pSttXTestMngrHtmlRpt->IsHtmlGend())
	{
		m_pSttXTestMngrHtmlRpt->InsertRptHtml();
		//m_pSttXTestMngrHtmlRpt->FillReport();
		m_pSttXTestMngrHtmlRpt->FillReportParent();
		m_pSttXTestMngrHtmlRpt->UpdateReportState();
	}
	else if(!m_bViewTestStarted)
	{
		m_pSttXTestMngrHtmlRpt->UpdateRptHtml();
		//m_pSttXTestMngrHtmlRpt->FillReport();
		m_pSttXTestMngrHtmlRpt->FillReportParent();
		m_pSttXTestMngrHtmlRpt->UpdateReportState();
	}

	CSttHtmlReportVIewInterface* pReportView= m_pSttXTestMngrHtmlRpt->GetHtmlReportView();
	int nIndex = m_tabWidget->indexOf((QSttReportViewHtml*)pReportView);
	m_tabWidget->setCurrentIndex(nIndex);


	if (nIndex == 1)
	{
		m_pViewReportBtn->setStyleSheet("QToolButton { ""background-color:rgb(240,255,255);" "}");
		m_pViewTestBtn->setStyleSheet("QToolButton { ""background-color:rgb(245,245,245);" "}");
	}

}

void TestWinBase::RaiseSwitchInfo()
{
	m_DockSwitch->show();
	m_DockSwitch->raise();

	m_viewDockSwitchAct->setChecked(true);
//	m_pDockSwitchBtn->setChecked(true);

	m_viewDockStaInfoAct->setChecked(false);
//	m_pDockStaInfoBtn->setChecked(false);
}

void TestWinBase::RaiseStateInfo()
{
	m_DockStaInfo->show();
	m_DockStaInfo->raise();

	m_viewDockSwitchAct->setChecked(false);
//	m_pDockSwitchBtn->setChecked(false);

	m_viewDockStaInfoAct->setChecked(true);
//	m_pDockStaInfoBtn->setChecked(true);
}

void TestWinBase::slot_viewDockSwich()
{
	if(!m_viewDockSwitchAct->isChecked())
	{
		RaiseSwitchInfo();
	}
	else
	{
		RaiseStateInfo();
	}
}

void TestWinBase::slot_viewDockSwichEx()
{
	if(m_viewDockSwitchAct->isChecked())
	{
		RaiseSwitchInfo();
	}
	else
	{
		RaiseStateInfo();
	}
}

void TestWinBase::slot_viewDockStaInfo()
{
	if (!m_viewDockStaInfoAct->isChecked())
	{
		RaiseStateInfo();
	}
	else
	{
		RaiseSwitchInfo();
	}
}

void TestWinBase::slot_viewDockStaInfoEx()
{
	if (m_viewDockStaInfoAct->isChecked())
	{
		RaiseStateInfo();
	}
	else
	{
		RaiseSwitchInfo();
	}
}

void TestWinBase::slot_versionInformation()
{
	QDeviceInforDlg oDevInforDlg;
	oDevInforDlg.initUI(FALSE);
	oDevInforDlg.exec();
}

void TestWinBase::slot_localUpdate()
{
	theLiveUpdate.Init();
	theLiveUpdate.LocalUpdate();
}

void TestWinBase::slot_testAppUpdate()
{
	theLiveUpdate.Init();
	theLiveUpdate.TestAppUpdate();
}

bool TestWinBase::winEvent( MSG *message, long *result )
{
	long nValue1 = (long )message->wParam;
	long nValue2 = (long )message->lParam;
	int m_nFunCode = (int)message->lParam;

#ifdef STT_IEC_PARSE_USE_Iec61850Config
	if(message->message == (WM_IEC61850CFGFINISHED_MSG))
	{
		showMaximized();
		m_oIecConfig.ExitEngine();
		m_oIecConfig.setControl(NULL);

		if (m_pGooseParaWidget)
		{
			long nParasSetSel = g_oSttTestResourceMngr.m_oIecDatasMngr.GetParasSetSel();

			if (g_oSttTestResourceMngr.LoadDefaultIec61850Config())
			{
				UpdateGoutTab(TRUE);//zhouhj 手动模块参数无意义,对于状态序列及多个测试项目的更新全部克隆链表
				UpdateFT3Tab(TRUE);

				g_oSttTestResourceMngr.ValidIecParasSetSel();
				long nNewParasSetSel = g_oSttTestResourceMngr.m_oIecDatasMngr.GetParasSetSel();

				if ((nParasSetSel != nNewParasSetSel)&&(nNewParasSetSel))//如果参数设置改变为二次值输出了,需要重新更新界面,设置各通道的电压电流设置最大值
				{
					OnUpdateTestResource(FALSE);
				}
			}

			m_bTmtParaChanged = TRUE;
		}
	}
#endif

	if (message->message == WM_KEYDOWN)
	{
		int adf = 0;

		UINT32  iKey = (UINT32)nValue1;

//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[message->message == WM_KEYDOWN][iKey=%ld]."),iKey);

		switch (iKey)
		{
		case VK_F2:
			{
//				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("TestWinBase::winEvent Key_F2"));
				if (m_startAct->isEnabled())
				{
					slot_start();
				}
			}
			break;			
		case VK_ESCAPE:
			{
				if (m_stopAct->isEnabled())
				{
					slot_stop();
				}
			}
			break;			
		case VK_LEFT:
			{
				if (m_vectorWidget)
				{
					m_vectorWidget->slot_PbnPreClicked();
				}
			}
			break;			
		case VK_RIGHT:
			{
				if (m_vectorWidget)
				{
					m_vectorWidget->slot_PbnNextClicked();
				}
			}
			break;			
		}
	}

	return QWidget::winEvent(message,result);  
}

void TestWinBase::closeEvent(QCloseEvent *e)
{
	int nRet = 0;

	if (m_bViewTestStarted)
	{//如果正在测试，先发送停止测试命令
		nRet = QMessageBox::question(this, tr("提示"),tr("正在运行中,是否停止测试?"),tr("是"),tr("否"));

		if (nRet == 0)
		{
			slot_stop();
		}

		e->ignore();
		return;
	}

	PreCloseMainWidget();

	if (m_bTmtParaChanged)
	{
		QMessageBox::StandardButton defaultBtn = QMessageBox::Yes;
		nRet = QMessageBox::question(this, tr("提示"),tr("测试模板未保存,是否保存?"),tr("是"),tr("否"),tr("取消"));

		if (nRet == 0)//选择"是"返回0   选择"否" 返回1    选择"取消" 返回2
		{
			SaveTestMngrFile(""); //关闭程序时保存参数模板，下次可以打开参数模板
			SaveSoeParasFile();
			e->accept();
			// mym add 2021-7-27
			CLogPrint::CloseLogFile();
		}
		else if (nRet == 1)
		{
			e->accept();
			// mym add 2021-7-27
			CLogPrint::CloseLogFile();
		}
		else
		{
			e->ignore();
		}
	}
}

// void TestWinBase::keyPressEvent( QKeyEvent *event )
// {
// 	if(event->key() == Qt::Key_F2) 
// 	{
// 		if (m_startAct->isEnabled())
// 		{
// 			slot_start();
// 		}
// 	} 
// 	else if(event->key() == Qt::Key_Escape) 
// 	{
// 		if (m_stopAct->isEnabled())
// 		{
// 			slot_stop();
// 		}
// 	}
// 	else if(event->key() == Qt::Key_Left)
// 	{
// 		if (m_vectorWidget)
// 		{
// 			m_vectorWidget->slot_PbnPreClicked();
// 		}
// 	}
// 	else if(event->key() == Qt::Key_Right)
// 	{
// 		if (m_vectorWidget)
// 		{
// 			m_vectorWidget->slot_PbnNextClicked();
// 		}
// 	}
// }

/*
void TestWinBase::InitGoosePubDataGroups()
{
	m_listGoosePub.clear();
	CIecCfgGoutDatas *pSourceGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = NULL;

	for (int i=0;i<m_oTmtTestMngr.m_nCount;i++)
	{
		pIecCfgGoutDatas = (CIecCfgGoutDatas*)pSourceGoutDatas->Clone();
		m_listGoosePub.append(pIecCfgGoutDatas);
	}
}

void TestWinBase::SerializeGoosePubs(CSttXmlSerializeBase *pXmlGoosePubsParent,CIecCfgGoutDatas *pGoutDatas)
{
	if (pXmlGoosePubsParent == NULL)
	{
		return;
	}

	CSttXmlSerializeBase *pXmlGouts = pXmlGoosePubsParent->xml_serialize("GOOSEPubs", "GOOSEPubs", "GOOSEPubs", stt_ParaGroupKey());

	if ((pXmlGouts != NULL)&&g_oSystemParas.m_nHasDigital)
	{
		long nRet = 0;
		CXmlRWElementBase *pElementNode = pXmlGouts->GetElement();
		CDataGroup oGoutGroup;

		if (stt_xml_serialize_is_read(pXmlGouts))
		{
			CXmlRWNodeListBase *pChildNodeList = pElementNode->GetChildNodes();
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlReadChildren(*pChildNodeList, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
			pGoutDatas->ReadGouts_GroupDatas(&oGoutGroup);
		}
		else if (stt_xml_serialize_is_write(pXmlGouts)||stt_xml_serialize_is_register(pXmlGouts))
		{
			CXmlRWDocBase *pRootNode = pXmlGouts->GetRWDoc();
			pGoutDatas->GenerateGouts_GroupDatas(&oGoutGroup);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			oGoutGroup.XmlWriteChildren(*pRootNode,*pElementNode, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
		}			
	}
}
*/
//测试列表公共槽 yyj 20210714
void TestWinBase::slot_AddItemBF()
{
	if (m_TestTable == NULL)
	{
		return;
	}

	int index = m_TestTable->GetCurrentRow();
	if (index<0)
	{
		index = 0;
	}

	PTMT_PARAS_HEAD pCurrItem = m_TestTable->GetCurrentItem();
	PTMT_PARAS_HEAD pNewTest = CreateTestParas(pCurrItem);
	
	Test_InsertAt(pNewTest, index);

	m_TestTable->InitData();
	m_TestTable->SetCurrentRow(index);

	m_bTmtParaChanged = TRUE;
}

void TestWinBase::slot_AddItemAF()
{
	int index = m_TestTable->GetCurrentRow()+1;
	if (index<0)
	{
		index = 0;
	}

	PTMT_PARAS_HEAD pCurrItem = m_TestTable->GetCurrentItem();
	PTMT_PARAS_HEAD pNewTest = CreateTestParas(pCurrItem);
	m_pCurrOpTest = pNewTest;
	pNewTest->m_nTestState = 0;//2023-12-06 suyang 添加时不需要显示结果

	Test_InsertAt(pNewTest, index);

	m_TestTable->InitData();
	m_TestTable->SetCurrentRow(index);

	m_bTmtParaChanged = TRUE;
}

void TestWinBase::slot_DeleteCurr()
{
	if (m_TestTable == NULL)
	{
		return;
	}

	if (m_oTmtTestMngr.m_nCount <= 1)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("至少保留一个测试项！"));
		return;
	}

	int index = m_TestTable->currentRow();
	m_pCurrOpTest = m_TestTable->GetCurrentItem();

	Test_DeleteAt(index);
	m_TestTable->InitData();
	
	index--;
	if (index < 0)
	{
		index = 0;
	}

	m_TestTable->SetCurrentRow(index);

	m_bTmtParaChanged = TRUE;
}

void TestWinBase::slot_Delete_N_1()	//删除N-1
{
	if (m_TestTable == NULL)
	{
		return;
	}

	if (m_oTmtTestMngr.m_nCount <= 1)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("至少保留一个测试项！"));
		return;
	}

	int nCount = m_oTmtTestMngr.m_nCount;
	for (int i=1;i<nCount;i++)
	{
		Test_DeleteAt(1);
	}

	m_TestTable->InitData();
	m_TestTable->SetCurrentRow(0);

	m_pCurrOpTest = m_TestTable->GetCurrentItem();

	m_bTmtParaChanged = TRUE;
}

void TestWinBase::slot_SelectAll()
{
	if (m_TestTable == NULL)
	{
		return;
	}

	for (int i=0;i<m_oTmtTestMngr.m_nCount;i++)
	{
		m_oTmtTestMngr.m_pParasBuffer[i]->m_nSelected = 1;
	}

	m_TestTable->InitData();
	m_TestTable->SetCurrentRow(m_TestTable->currentRow());

	m_bTmtParaChanged = TRUE;
}

void TestWinBase::slot_UnselectAll()
{
	if (m_TestTable == NULL)
	{
		return;
	}

	for (int i=0;i<m_oTmtTestMngr.m_nCount;i++)
	{
		m_oTmtTestMngr.m_pParasBuffer[i]->m_nSelected = 0;
	}

	m_TestTable->InitData();
	m_TestTable->SetCurrentRow(m_TestTable->currentRow());

	m_bTmtParaChanged = TRUE;
}

void TestWinBase::slot_ClearCurrResult()
{
	PTMT_PARAS_HEAD pItemPara = m_TestTable->GetCurrentItem();

	if (pItemPara == NULL)
	{
		return;
	}

	pItemPara->clear_result();

	pItemPara->m_nTestState = 0;

	m_TestTable->ClearCurrItemResult();/*UpdateCurrItemResult();*/ // 20210714 sf  modify
}

void TestWinBase::slot_ClearAllResult()
{
	if(m_TestTable)
	{
		int row = m_TestTable->GetCurrentRow();
		for (int i=0;i<m_oTmtTestMngr.m_nCount;i++)
		{
			if (m_oTmtTestMngr.m_pParasBuffer[i]->m_nSelected != 0)//20210924 为了兼容以前这个标志没有初始化的模板文件而做的改动 sf
			{
				m_oTmtTestMngr.m_pParasBuffer[i]->clear_result();
				m_oTmtTestMngr.m_pParasBuffer[i]->m_nTestState = 0;
			}
		}
		m_TestTable->InitData();
		m_TestTable->SetCurrentRow(row);
	}
}

//2022.5.19 caoxc
void TestWinBase::slot_loadFinished(bool b)
{
	m_bLoadFinished = true;

	if (m_pSttXTestMngrHtmlRpt != NULL)
	{
		m_pSttXTestMngrHtmlRpt->InsertRptHtml();
		m_pSttXTestMngrHtmlRpt->FillReport();
	}
}

//20230628 suyang


void TestWinBase::SendIecDetect(long bEnable)
{
	//需要判断是否联机
	if (!g_bTestAppConnect)
	{
		CString strIP = g_oSttTestAppCfg.GetTestAppIP();
		long nPort = g_oSttTestAppCfg.GetTestServerPort();

		if (!OnConnectTestApp(strIP,nPort))//如果当前未联机,需要进行联机操作
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("联机失败[%s][%ld]."),strIP.GetString(),nPort);
			SysStateEvent_OnTestStoped();
			return;
		}
	}

	CSttPowerTestEngineBase::SendIecDetect(bEnable);
}

void TestWinBase::SendIecRecord(CDataGroup *pIecRecordParas)
{
	if (!g_bTestAppConnect)
	{
		CString strIP = g_oSttTestAppCfg.GetTestAppIP();
		long nPort = g_oSttTestAppCfg.GetTestServerPort();

		if (!OnConnectTestApp(strIP,nPort))//如果当前未联机,需要进行联机操作
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("联机失败[%s][%ld]."),strIP.GetString(),nPort);
			SysStateEvent_OnTestStoped();
			return;
		}
	}

	CSttPowerTestEngineBase::SendIecRecord(pIecRecordParas);
}

void TestWinBase::InitSttIecRecord(CSttTestAppCfg* pSttTestAppCfg)
{
#ifdef STT_USE_IecCap_

	if (g_theSmartCapCtrl != NULL)
	{
		return;
	}

	CXSmartCapMngr::Create();

#ifdef _XSmartCap_use_SttRcdSocket_
	//使用动态分配的内存  2022-6-21  lijunqing
	CSttRcdMemBufferMngr *pSttRcdMemBufferMngr = new CSttRcdMemBufferMngr();
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->CreateSttCap_61850(pSttTestAppCfg, pSttRcdMemBufferMngr);
	pXSttCap_61850->m_bUseSttTestEngineClientData = FALSE;
	g_pSttRcdSndRingBuf = pXSttCap_61850;
#else

	//2022-4-7  lijunqing 创建共性内存Server
	CRingMemBuf *pRingMemBuf = NULL;
#ifdef _PSX_QT_LINUX_
// 	CRingMemBufShm *pRingMemBufShm = new CRingMemBufShm();
// 	pRingMemBufShm->ShmCreateClient();
// 	pRingMemBuf = pRingMemBufShm;
#else
	CRingMemBufShmDebug *pRingMemBufShm = new CRingMemBufShmDebug();
	pRingMemBufShm->ShmCreateServer();
	pRingMemBufShm->ShmCreateClient();
	pRingMemBuf = pRingMemBufShm;
#endif

	CSttLocalRcdMemBufferMngrLinux *pNewRcdMemBufferMngr = new CSttLocalRcdMemBufferMngrLinux();
	pNewRcdMemBufferMngr->SetRingMemBuf(pRingMemBuf);
	pNewRcdMemBufferMngr->ResetBuffer();
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->CreateSttCap_61850(pSttTestAppCfg, pNewRcdMemBufferMngr);
	pXSttCap_61850->m_bUseSttTestEngineClientData = FALSE;
	g_pSttRcdSndRingBuf = pRingMemBuf;

#endif

	//Windows模式下，增加调试功能
#ifndef _PSX_QT_LINUX_

#ifndef _XSmartCap_use_SttRcdSocket_//在socket模式下,暂不启动模拟探测
	g_pRingMemBufShmDebugWidget = new QRingMemBufShmDebugWidget();
	g_pRingMemBufShmDebugWidget->show();
#endif
#endif

	CSmartCapCtrl::Create();
	g_theSmartCapCtrl->m_pXSttCap_61850 = pXSttCap_61850;
	g_theSmartCapCtrl->BeginSmartCapThread();
	pXSttCap_61850->m_pKeyDB = m_pKeyDB;

	//2022-9-25  lijunqing初始化 g_theHtmlRptGenFactory
 	//g_theHtmlRptGenFactory->m_pDvmDevice = pXSttCap_61850->m_pDvmDevice;

#endif

}


void TestWinBase::ExitSttIecRecord()
{
#ifdef STT_USE_IecCap_

	g_pSttRcdSndRingBuf = NULL;
	CXSmartCapMngr::Release();
	CSmartCapCtrl::Release();


	delete g_pRingMemBufShmDebugWidget;
	g_pRingMemBufShmDebugWidget = NULL;

#endif

}


void TestWinBase::InitKeyDB()
{
#ifdef STT_USE_IecCap_

	if (m_pKeyDB != NULL)
	{
		return;
	}

	m_pKeyDB = new CXKeyDB();
	m_pKeyDB->OpenKeyDbFile(_T("RelayTestKeyDb.xml"), TRUE);

#endif

}

void TestWinBase::On_IecDetect(CDataGroup *pIecCb)
{
#ifdef STT_USE_IecCap_

	if(!m_bIsUsingIecCap)
	{
		return;
	}

	CCapDeviceBase *pNew = g_theSmartCapCtrl->m_pXSttCap_61850->m_oCapDeviceAll.AddCapDevice(pIecCb);

	if (g_theCapDeviceMngrMsgRcvWnd != NULL)
	{
		if (pNew != NULL)//返回不为空,则添加成功,则添加控制块  zhouhj20230106 
		{
			g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_ADDCAPDEVICE, (WPARAM)pNew, (LPARAM)pNew);
		} 
		else//返回为空,则更新控制块,防止光口号更新等情况出现
		{
			pNew = g_theSmartCapCtrl->m_pXSttCap_61850->m_oCapDeviceAll.FindCapDevice(pIecCb);

			if (pNew != NULL)
			{
				g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_UPDATECAPDEVICE, (WPARAM)pNew, (LPARAM)pNew);
			}
		}
	}

#endif

}


void TestWinBase::InitIECChannelsData()
{
	m_ListVolChans.RemoveAll();
	m_ListCurChans.RemoveAll();
	m_ACListCurChans.RemoveAll();
	m_ACListVolChans.RemoveAll();
	CIecCfgDatasMngr *pIecCfgDatasMngr = &g_oSttTestResourceMngr.m_oIecDatasMngr;
	CIecCfgDatasSMV *pIecCfgDatasSMV = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfg6044CommonData *pIecCfg6044CommonData = NULL;
	CIecCfg6044CommonCh *pIecCfg6044CommonCh = NULL;
	CExBaseObject *pCurObj = NULL;
	std::set<CString> uniqueAppChIDs;  // 用于存储唯一的 AppChID
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while(pos)
	{
		pCurObj = pIecCfgDatasSMV->GetNext(pos);
		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfg6044CommonData = (CIecCfg6044CommonData *)pCurObj;

			if (pIecCfg6044CommonData->m_nUseFlag == 1)
			{
				POS pos1 = pIecCfg6044CommonData->m_pCfgChs->GetHeadPosition();
				while(pos1)
				{
					pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pIecCfg6044CommonData->m_pCfgChs->GetNext(pos1);

					if (uniqueAppChIDs.find(pIecCfg6044CommonCh->m_strAppChID) != uniqueAppChIDs.end())
					{
						continue;
					}

					if (pIecCfg6044CommonCh->m_strAppChID == _T("zero"))
						{
						continue;
					}

							CString strIndex;
					if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_DCVol) //直流电压
					{
							strIndex = getDCVolIndexByType(pIecCfg6044CommonCh->m_strAppChID);
						m_ListVolChans.AddNewValue(pIecCfg6044CommonCh->m_strAppChID, strIndex);
						}
					else if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_DCCur) //直流电流
					{
						strIndex = getDCCurrIndexByType(pIecCfg6044CommonCh->m_strAppChID);
						m_ListCurChans.AddNewValue(pIecCfg6044CommonCh->m_strAppChID, strIndex);
					}
					else if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Vol) //交流电压
					{
						strIndex = getDCVolIndexByType(pIecCfg6044CommonCh->m_strAppChID);
						m_ACListVolChans.AddNewValue(pIecCfg6044CommonCh->m_strAppChID, strIndex);
					}
					else if ((pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Curr)
						|| 	(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_6CurrProt )
						|| (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)) //交流电流
						{
							strIndex = getDCCurrIndexByType(pIecCfg6044CommonCh->m_strAppChID);
						m_ACListCurChans.AddNewValue(pIecCfg6044CommonCh->m_strAppChID, strIndex);
					}

					uniqueAppChIDs.insert(pIecCfg6044CommonCh->m_strAppChID);
				}
			}
		}
	}
}

BOOL TestWinBase::InitTestMacroSM()
{
	if (!m_oTestMacroSM.attach()) 
	{
		return FALSE;
	}
	//清空共享内存数据
	char *fszTestMacroData = static_cast<char *>(m_oTestMacroSM.data());
	if (fszTestMacroData != NULL)
	{
		qint64 nSharedMemorySize = m_oTestMacroSM.size();
		memset(fszTestMacroData, 0, nSharedMemorySize);

		qDebug() << "成功清空共享内存数据";
		return TRUE;
	} 
	else 
	{
		qDebug() << "清空共享内存失败";
		return FALSE;
	}
	return TRUE;
}

void TestWinBase::UpdateTestModule( const CString& strParasFile,const CString &strTplID )
{
	if (strTplID.IsEmpty() || strParasFile.IsEmpty())
	{
		return;
	}

	if (InitTestMacroSM())
	{
		// 主界面已打开，写入共享内存
		CString strDataToWrite = strTplID + _T(";") + strParasFile;
		const char* fszTestMacroData = strDataToWrite.GetString();
		char* TestMacroSM_addr = static_cast<char*>(m_oTestMacroSM.data());
		if (fszTestMacroData != NULL && m_oTestMacroSM.size() >= strDataToWrite.GetLength())
		{
			m_oTestMacroSM.lock();
			memcpy(TestMacroSM_addr, fszTestMacroData, m_oTestMacroSM.size()/*(strDataToWrite.GetLength() + 1) * sizeof(char)*/);
			m_oTestMacroSM.unlock();
			m_oTestMacroSM.detach();

			QApplication::quit();//退出当前程序
		}
	}
	else
	{
		// 主界面未打开，传参打开主界面
		QProcess MainWinProcess;
		CString strExe = _T("SttWinMain.exe");
		CString strRootPath = _P_GetBinPath() + strExe;

		if (IsFileExist(strRootPath))
		{
			QStringList ListCmd;
			CString strParas;
			QString strQPara = QString("%1=%2;").arg(ARGV_CMD_PARA_ID_TmpPath).arg(strParasFile);//2024-01-03 wuxinyi 解决中文路径乱码问题
// 			strParas.Format(_T("%s=%s;"), ARGV_CMD_PARA_ID_TmpPath, strParasFile.GetString());
			strParas.Format(strQPara);
			strParas.AppendFormat(_T("%s=%s;"), STT_UPDATE_TESTMACRO_TPLID, strTplID.GetString());
			ListCmd << strParas;

			QApplication::quit();//退出当前程序

			MainWinProcess.startDetached(strRootPath, ListCmd);
			MainWinProcess.waitForStarted();
		}
	}
			
}

BOOL TestWinBase::HasFT3Block_Selected()
{
	int nFT3OutBlock = 0 ,nFT3InBlock = 0;
	CIecCfgDatasSMV *pIecCfgDatasSMV = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvMngr();
	POS posIn = pIecCfgDatasSMV->GetHeadPosition();
	while(posIn)
	{
		CIecCfgDataBase* pIecCfgDataBase = (CIecCfgDataBase *)pIecCfgDatasSMV->GetNext(posIn);
		if (pIecCfgDataBase->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA && pIecCfgDataBase->m_nUseFlag)
		{
			nFT3OutBlock ++;
		}
	}

	CIecCfgDatasSmvIn *pIecCfgDatasSMVIn = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvInMngr();
	POS posOut = pIecCfgDatasSMVIn->GetHeadPosition();
	while(posOut)
	{
		CIecCfgDataBase* pIecCfgDataBase = (CIecCfgDataBase *)pIecCfgDatasSMVIn->GetNext(posOut);
		if (pIecCfgDataBase->GetClassID() == CFGCLASSID_CIECCFG6044COMMONINDATA && pIecCfgDataBase->m_nUseFlag)
		{
			nFT3InBlock ++;
		}
	}
	if (g_oSystemParas.m_nHasDigital && !g_oSystemParas.m_nHasAnalog && !g_oSystemParas.m_nHasWeek)
	{
		if (nFT3InBlock == 0 && nFT3OutBlock == 0)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,_T("未勾选要发送的控制块."));
			return FALSE;
		}
	}

	return TRUE;
}

