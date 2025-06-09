#include "SttTestCntrFrameWin.h"

#ifdef SttXcmdCh_SttClientSocket
#include "SttTestCntrApplication.h"
#endif

#ifdef SttXcmdCh_AxAtsLib
#include "SttTestCntrApplicationAx.h"
typedef CSttTestCntrApplicationAx  CSttTestCntrApplication;
#endif


#include <QTextCodec>
#include <QSharedMemory>
#include <QMessageBox>
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../Module/XLangResource_Win.h"
#include "../../Module/SttTestCtrl/SttTestCtrlCntrWin.h"
#include "../../../Module/API/StringConvertApi.h"
#include "../../Module/SttSystemConfig/SttSystemConfig.h"
#include "../../Module/HtmlReport/IECTest/SttIecTestHtmlRptGenFactory.h"
#include "../../Module/ReplayTest/BigComtradeTransPlay.h"
#include "../../Module/UI/SttTestCntrCmdDefine.h" 
#include "../../Module/SttTestCtrl/SttArgcArgvParser.h"
#include "../../Module/UI/Module/CommonCtrl_QT/QSttProgDlg.h"
#include "../../Module/RecordTest/UI/SttIecRecordDetectWidget.h"
#include "../../Module/RecordTest/UI/SttIecRecordMainWidget.h"
#include "../../../Module/xml/PugiXML/pugixml.hpp"
//#include "../../Module/SttTest/Common/tmt_soe_test.h"

#include "SttMacroParaEditFactoryEng.h"
#include "../../Module/SttSocket/SttXcmdChAtsLib/SttAtsLibClient.h"
#include "../../Module/UI/SttTestCntrThread.h"
#include "sttdebuglogwidget.h"
#ifdef use_sttdebuglogwidget
long g_sttdebuglogwidget = 1;
#else
long g_sttdebuglogwidget = 0;
#endif
//#include "SttTestCntrApplication.h"

QSttProgDlg *g_pSttGlobalProgDlg = NULL;
extern CSttAtsLibClient *g_theSttAtsLibClient;

// extern bool g_bIsOpenMacroFromMain;
//macrotest macro_id=MUTimingAccurTest;macro_file=MuTest;iec=1;meas_svr=0;
//macrotest macro_id=TerminalAutoTest;macro_file=MuTest;iec=0;meas_svr=0;
//macrotest macro_id=ManualTest;macro_file=RelayTest;iec=0;meas_svr=0;
//macrotest macro_id=Gradient;macro_file=RelayTest;iec=0;meas_svr=0;
//macrotest macro_id=IecCapTest;iec=1;meas_svr=0;macro_file=RelayTest;assist=ieccaptest;
//open_dialog dialog_id=IecCapDialog;macro_file=RelayTest;iec=0;meas_svr=0;
//macrotest macro_id=MUAccurAutoTest;macro_file=MuTest;iec=0;meas_svr=1;
//macrotest macro_id=MUAutoTest;macro_file=MuTest;iec=0;meas_svr=1;
//macrotest macro_id=MUAccuracyTest;macro_file=MuTest;iec=0;meas_svr=0;
//macrotest macro_id=MUAccuracyTest;macro_file=MuTest;iec=0;meas_svr=0;
//macrotest macro_id=MUAccuracyTest;sscl_path=D:/11/PONOVO/PONOVO.sscl;iec=0;meas_svr=0;macro_file=MuTest;assist=mutest;
//macrotest macro_id=MUAccurAutoTest;sscl_path=D:/11/PONOVO/PONOVO.sscl;iec=0;meas_svr=1;macro_file=MuTest;assist=mutest;
//macrotest macro_id=ManualTest;sscl_path=D:/11/PONOVO/PONOVO.sscl;iec=0;meas_svr=0;macro_file=RelayTest;assist=RelayTest;
//macrotest macro_id=MUAccurAutoTest;assist=admutest;iec=1;meas_svr=1;macro_file=AdmuTest;
//macrotest macro_id=DistanceTest_I;macro_file=RelayTest;iec=0;meas_svr=0;

void ShowSttGlobalProgDlg()
{
	CTickCount32 oTickCount;

	if (g_pSttGlobalProgDlg == NULL)
	{
		g_pSttGlobalProgDlg = new QSttProgDlg(NULL);
	}

	CString strTitle = g_sLangTxt_Native_LoadingBar.GetString();
	CString strText = g_sLangTxt_Win_LoadingTestInterface.GetString();
	g_pSttGlobalProgDlg->initUI(strTitle, strText);
	//g_pSttGlobalProgDlg->initUI(_T("功能加载进度条"), _T("正在加载测试功能界面,请稍后..."));
	g_pSttGlobalProgDlg->setModal(false);
	g_pSttGlobalProgDlg->Start(0,30,0);
	long nDelayTimeMs = 2000;//zhouhj  2023.7.27 在普通电脑,延时2s

	if (!g_oSttSystemConfig.IsDoubleClickEdit())
	{
		nDelayTimeMs = g_oSttSystemConfig.m_fOpenDelayTime*1000;//zhouhj  2023.7.20 在工控机内增加延时,保证自动测试能调用成功
	} 

	oTickCount.DoEvents(nDelayTimeMs);
	g_pSttGlobalProgDlg->Stop();
}

void assist_create(QSttTestCntrFrameWin &oSttTestCntrFrameLinux, const CString &strAssistID)
{
	assist_create(strAssistID);

	QSttToolButtonBase *pButton = NULL;
	CSttFrame_Button *pBtnAssist = oSttTestCntrFrameLinux.m_pSttFrameConfig->FindBtnByID(STT_CNTR_CMD_Assist);

	if (pBtnAssist != NULL)
        {
		pButton = (QSttToolButtonBase*)pBtnAssist->m_dwItemData;
    }

	assist_set_entry_wnd(pButton);
}

void main_macrotest(CSttTestCntrApplication &oSttTestCntrApplication, CSttArgcArgvParser &oParser)
{
	BOOL bSmartTestRet = oSttTestCntrApplication.StartSmartTest(oParser.m_strMacroID);
	CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID = oParser.m_strMacroFile;
	//2022-9-23  lijunqing
	CSttIecTestHtmlRptGenFactory *pHtmlRptGenFactory = new CSttIecTestHtmlRptGenFactory();

	debug_time_long_log("--------", true);
	CSttTestCtrlCntrWin *pSttTestCtrlCntrWin = new CSttTestCtrlCntrWin();
	debug_time_long_log("new CSttTestCtrlCntrWin", true);
	g_oSttTestAppCfg.Open("TestAppConfigSttAtsWin.xml");
	oSttTestCntrApplication.SetSttTestCtrlCntr(pSttTestCtrlCntrWin);
	debug_time_long_log("SetSttTestCtrlCntr", true);
	pHtmlRptGenFactory->OpenDataTypesByMacroFileID(oParser.m_strMacroFile);
	debug_time_long_log("OpenDataTypesByMacroFileID", true);


	CString strMacroID, strDialogID;
	strMacroID = oParser.m_strMacroID;
	strDialogID = oParser.m_strDialogID;

	oSttTestCntrApplication.SetCurrTestMacroUI(strMacroID);
	oSttTestCntrApplication.m_pTestCtrlCntr->InitDefaultHdRs();
	debug_time_long_log("SetCurrTestMacroUI", true);

	CSttMacroParaEditViewMngr::Create();
	QSttTestCntrFrameWin oSttTestCntrFrameWin;
	debug_time_long_log("QSttTestCntrFrameWin Create", true);

	//2022-10-5  lijunqing macrotest
	CString strFrameConfigPath;
	if (!oParser.m_strMacroFile.IsEmpty())//20221206 zhouhj 增加用于区分测试功能
	{
		strFrameConfigPath.Format(_T("%s/TestCntrlFrameConfigWin.xml"), oParser.m_strMacroFile.GetString());
	}
	else
	{
		strFrameConfigPath = _T("TestCntrlFrameConfigWin.xml");
	}
	if (IsFileExist(oParser.m_strSsclFilePath))
	{
		pSttTestCtrlCntrWin->m_oSclStation.OpenSclStationFile(oParser.m_strSsclFilePath);
	}
		oSttTestCntrFrameWin.SetAutoTest(FALSE);

		oSttTestCntrFrameWin.SetTestCtrlCntrBase(oSttTestCntrApplication.m_pTestCtrlCntr);
		debug_time_long_log("SetTestCtrlCntrBase", true);

		oSttTestCntrFrameWin.InitFrame(strFrameConfigPath);
	debug_time_long_log("InitFrame_End", true);
	if ((oParser.m_strCmdID != ARGV_CMD_ID_OPENDIALOG) &&
		(!oSttTestCntrApplication.IsMuTest(oParser.m_strMacroID))
		&& (!g_oSttSystemConfig.m_nInternationalMode))
	{
		debug_time_long_log("StartIotProtoServer_Begin", true);
		oSttTestCntrApplication.StartIotProtoServer();
		debug_time_long_log("StartIotProtoServer_End", true);
	}
	
		oSttTestCntrFrameWin.show();

// 	if (bSmartTestRet)//单击响应消息,且本次调用了SmartTest,则经过延时处理
// 	{
// 		ShowSttGlobalProgDlg();
// 	}

		if (oParser.m_nUseIec)
		{
		if ((oParser.m_strAssistID == STT_AssistID_MUTEST))
			{
				oSttTestCntrFrameWin.OnCmd_IecCap(STT_IEC_DETECT_TYPE_61850_92);
			}
			else if (oParser.m_strAssistID == STT_AssistID_ADMUTEST)
			{
				oSttTestCntrFrameWin.OnCmd_IecCap(STT_IEC_DETECT_TYPE_60044);
			}
			else
			{
				oSttTestCntrFrameWin.OnCmd_IecCap();
			}

			g_bSmartCap_RecordNow = 0;//进入监视界面时,再开启报文解析功能,
			g_theSttIecRecordMainWidget->StartDetect();
		}

		if (oParser.m_nUseMeasServer)
		{
			pSttTestCtrlCntrWin->InitMeasServer();
		}

		oSttTestCntrFrameWin.m_pSttGbTreeView->setVisible(FALSE);
		oSttTestCntrFrameWin.showMaximized();
	debug_time_long_log("OnMacroTest__Begin", true);
//	oSttTestCntrFrameWin.OnMacroTest(oSttTestCntrApplication.m_pTestMacroUI);
	oSttTestCntrFrameWin.emit_OpenMacroTest(unsigned long(oSttTestCntrApplication.m_pTestMacroUI));
	//2024-10-29 zhouyangyong 连发信号合并单元那边特殊处理会导致登录出问题
//	debug_time_long_log("emit_OpenMacroTest", true);
//	oSttTestCntrFrameWin.emit_SendGenerateTemplate(unsigned long(oSttTestCntrApplication.m_pTestMacroUI));
//	debug_time_long_log("emit_SendGenerateTemplate", true);

		if (strMacroID == STT_ORG_MACRO_ReplayTest && (g_theBigComtradeTransPlay != NULL))
		{
		debug_time_long_log("CreateSttComtradeSocket_Begin", true);
			g_theBigComtradeTransPlay->CreateSttComtradeSocket();
		debug_time_long_log("CreateSttComtradeSocket_End", true);
		}

	if (!g_oSttSystemConfig.IsDoubleClickEdit()) //2023.7.25 zhouhj 在测试仪工控机内运行关闭时,会报Runtime Error 错误,暂时关闭时做延时处理
	{
		Sleep(2000);
		debug_time_long_log("Sleep_End", true);
	}
	debug_time_long_log("OnMacroTest__End", true);
	oSttTestCntrApplication.exec();
	delete pHtmlRptGenFactory;
}

void main_openfile(CSttTestCntrApplication &oSttTestCntrApplication, CSttArgcArgvParser &oParser)
{
	CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID = oParser.m_strMacroFile;
	//2022-9-23  lijunqing
	CSttIecTestHtmlRptGenFactory *pHtmlRptGenFactory = new CSttIecTestHtmlRptGenFactory();

	debug_time_long_log("--------", true);
	CSttTestCtrlCntrWin *pSttTestCtrlCntrWin = new CSttTestCtrlCntrWin();
	debug_time_long_log("new CSttTestCtrlCntrWin", true);
	oSttTestCntrApplication.SetSttTestCtrlCntr(pSttTestCtrlCntrWin);
	debug_time_long_log("SetSttTestCtrlCntr", true);
	pHtmlRptGenFactory->OpenDataTypesByMacroFileID(oParser.m_strMacroFile);
	debug_time_long_log("OpenDataTypesByMacroFileID", true);
	oSttTestCntrApplication.m_pTestCtrlCntr->InitDefaultHdRs();

	CString strMacroID, strDialogID;
	//strMacroID = argv[1];
	strMacroID = oParser.m_strMacroID;
	strDialogID = oParser.m_strDialogID;

	oSttTestCntrApplication.SetCurrTestMacroUI(strMacroID);
	debug_time_long_log("SetCurrTestMacroUI", true);

	CSttMacroParaEditViewMngr::Create();
	QSttTestCntrFrameWin oSttTestCntrFrameWin;
	debug_time_long_log("QSttTestCntrFrameWin Create", true);

	CString strFrameConfigPath;

	if (!oParser.m_strMacroFile.IsEmpty())
		{
		strFrameConfigPath.Format(_T("%s/TestCntrlFrameConfigWin.xml"), oParser.m_strMacroFile.GetString());
		}
	else
	{
		strFrameConfigPath = _T("TestCntrlFrameConfigWin.xml");
	}

	if (IsFileExist(oParser.m_strSsclFilePath))
	{
		pSttTestCtrlCntrWin->m_oSclStation.OpenSclStationFile(oParser.m_strSsclFilePath);
		debug_time_long_log("OpenSclStationFile", true);
	}

	oSttTestCntrFrameWin.InitConfig(strFrameConfigPath);
		oSttTestCntrFrameWin.InitFrame(strFrameConfigPath);
	debug_time_long_log("InitFrame", true);
	oSttTestCntrFrameWin.SetTestCtrlCntrBase(oSttTestCntrApplication.m_pTestCtrlCntr);
	debug_time_long_log("SetTestCtrlCntrBase", true);


		oSttTestCntrFrameWin.SetAddMacroEnable(false);


	//2022-9-23  lijunqing
	delete pHtmlRptGenFactory;
}

void main_opendialog(CSttTestCntrApplication &oSttTestCntrApplication, CSttArgcArgvParser &oParser)
{
	BOOL bSmartTestRet = oSttTestCntrApplication.StartSmartTest(oParser.m_strMacroID);
	if (bSmartTestRet)//单击响应消息,且本次调用了SmartTest,则经过延时处理
	{
		ShowSttGlobalProgDlg();
	}
	debug_time_long_log("--------", true);
	CSttTestCtrlCntrWin *pSttTestCtrlCntrWin = new CSttTestCtrlCntrWin();
	debug_time_long_log("new CSttTestCtrlCntrWin", true);
	oSttTestCntrApplication.SetSttTestCtrlCntr(pSttTestCtrlCntrWin);
	debug_time_long_log("SetSttTestCtrlCntr", true);
	oSttTestCntrApplication.m_pTestCtrlCntr->InitDefaultHdRs();

	/*20240924 suyang  在 open_dialog dialog_id=IecCapDialog;assist=relaytest;iec=0;meas_svr=0;调试下会导致崩溃
	*	g_theHtmlRptGenFactory没有初始化
	*/
	CSttIecTestHtmlRptGenFactory *pHtmlRptGenFactory = new CSttIecTestHtmlRptGenFactory();
	pHtmlRptGenFactory->OpenDataTypesByMacroFileID(oParser.m_strMacroFile);

	CString strMacroID, strDialogID;
	//strMacroID = argv[1];
	strMacroID = oParser.m_strMacroID;
	strDialogID = oParser.m_strDialogID;

	oSttTestCntrApplication.SetCurrTestMacroUI(strMacroID);
	debug_time_long_log("SetCurrTestMacroUI", true);

	CSttMacroParaEditViewMngr::Create();
	QSttTestCntrFrameWin oSttTestCntrFrameWin;
	debug_time_long_log("QSttTestCntrFrameWin Create", true);

	CString strFrameConfigPath;

	if (!oParser.m_strMacroFile.IsEmpty())
	{
		strFrameConfigPath.Format(_T("%s/TestCntrlFrameConfigWin.xml"), oParser.m_strMacroFile.GetString());
	}
	else
	{
		strFrameConfigPath = _T("TestCntrlFrameConfigWin.xml");
	}

	if (IsFileExist(oParser.m_strSsclFilePath))
		{
		pSttTestCtrlCntrWin->m_oSclStation.OpenSclStationFile(oParser.m_strSsclFilePath);
		debug_time_long_log("OpenSclStationFile", true);
		}

	oSttTestCntrFrameWin.InitConfig(strFrameConfigPath);
		oSttTestCntrFrameWin.InitFrame(strFrameConfigPath);
	debug_time_long_log("InitFrame", true);
	oSttTestCntrFrameWin.SetTestCtrlCntrBase(oSttTestCntrApplication.m_pTestCtrlCntr);//20240924 suyang 在上面调试条件下崩溃，所以开放
	debug_time_long_log("SetTestCtrlCntrBase", true);


		oSttTestCntrFrameWin.OpenDialog(oParser.m_strDialogID);
	debug_time_long_log("OpenDialog", true);

	//2022-9-23  lijunqing
	delete pHtmlRptGenFactory;
}

void main_none(CSttTestCntrApplication &oSttTestCntrApplication, CSttArgcArgvParser &oParser, QStringList strings)
{
	BOOL bSmartTestRet = oSttTestCntrApplication.StartSmartTest(oParser.m_strMacroID);
	if (bSmartTestRet)//单击响应消息,且本次调用了SmartTest,则经过延时处理
	{
		ShowSttGlobalProgDlg();
	}

	CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID = oParser.m_strMacroFile;
	//2022-9-23  lijunqing
	CSttIecTestHtmlRptGenFactory *pHtmlRptGenFactory = new CSttIecTestHtmlRptGenFactory();

	debug_time_long_log("--------", true);
	CSttTestCtrlCntrWin *pSttTestCtrlCntrWin = new CSttTestCtrlCntrWin();
	debug_time_long_log("new CSttTestCtrlCntrWin", true);
	g_oSttTestAppCfg.Open("TestAppConfigSttAtsWin.xml");
	oSttTestCntrApplication.SetSttTestCtrlCntr(pSttTestCtrlCntrWin);
	debug_time_long_log("SetSttTestCtrlCntr", true);
	pHtmlRptGenFactory->OpenDataTypesByMacroFileID(oParser.m_strMacroFile);
	debug_time_long_log("OpenDataTypesByMacroFileID", true);
	oSttTestCntrApplication.m_pTestCtrlCntr->InitDefaultHdRs();

	CString strMacroID, strDialogID;
	strMacroID = oParser.m_strMacroID;
	strDialogID = oParser.m_strDialogID;

	oSttTestCntrApplication.SetCurrTestMacroUI(strMacroID);
	debug_time_long_log("SetCurrTestMacroUI", true);

	CSttMacroParaEditViewMngr::Create();
	QSttTestCntrFrameWin oSttTestCntrFrameWin;
	debug_time_long_log("QSttTestCntrFrameWin Create", true);

	CString strFrameConfigPath;

	if (!oParser.m_strMacroFile.IsEmpty())
	{
		strFrameConfigPath.Format(_T("%s/TestCntrlFrameConfigWin.xml"), oParser.m_strMacroFile.GetString());
	}
	else
	{
		strFrameConfigPath = _T("TestCntrlFrameConfigWin.xml");
	}

	if (IsFileExist(oParser.m_strSsclFilePath))
	{
		pSttTestCtrlCntrWin->m_oSclStation.OpenSclStationFile(oParser.m_strSsclFilePath);
		debug_time_long_log("OpenSclStationFile", true);
	}

	oSttTestCntrFrameWin.InitConfig(strFrameConfigPath);
		oSttTestCntrFrameWin.InitFrame(strFrameConfigPath);
	debug_time_long_log("InitFrame", true);
	oSttTestCntrFrameWin.SetTestCtrlCntrBase(oSttTestCntrApplication.m_pTestCtrlCntr);
	debug_time_long_log("SetTestCtrlCntrBase", true);
	if (g_pSttGlobalProgDlg)
	{
		g_pSttGlobalProgDlg->Stop();
	}
	if (strings.count() > 0)
	{
		oSttTestCntrFrameWin.SetAddMacroEnable(true);
		oSttTestCntrFrameWin.show();
		oSttTestCntrFrameWin.SetAutoTest(TRUE);
		oSttTestCntrFrameWin.OnAutoTest(strings);
		oSttTestCntrFrameWin.showMaximized();
		oSttTestCntrApplication.exec();
	}
	else
	{
		oSttTestCntrFrameWin.show();
		oSttTestCntrFrameWin.showMaximized();
		oSttTestCntrApplication.exec();
	}
	delete pHtmlRptGenFactory;
}

int main(int argc, char *argv[])
{

#ifdef SttXcmdCh_AxAtsLib
    g_nSttXcmdCh_Type = SttXcmdChType_AxAtsLib;
#else
    g_nSttXcmdCh_Type = SttXcmdChType_SttClientSocket;
#endif

    CSttMacroParaEditFactoryEng oMacroParaEditFactory;

	//唯一对象处理
    QSharedMemory *shareMem = new QSharedMemory(QString("Stt_TestCtrlCntr_Native"));

    volatile short i = 2;
    while (i--)
    {
        if(shareMem->attach(QSharedMemory::ReadOnly))
		{
            shareMem->detach();
        }
		}

    if(! shareMem->create(1))
	{//已经创建，则返回错误
		qDebug() << "Error: Stt_TestCtrlCntr_Native is exist !";
		return 0;
	}
	//yzj2023-4-17设置xml解析时的浮点数float位数
	g_nPugiFloatSize = 3;

	debug_enter_time_long_log();
	CreateSttTestCntrThread();
	//2022-10-5  lijunqing
	CSttArgcArgvParser oParser;
	oParser.Parser(argc, argv);
	CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID = oParser.m_strMacroFile;

	CSttTestCntrApplication oSttTestCntrApplication(argc, argv); 
#ifdef use_sttdebuglogwidget
	sttdebuglogwidget wDebugLog;
	wDebugLog.m_strMacroID = oParser.m_strMacroID;
	wDebugLog.show();
#endif
	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("sttdebuglogwidget"));
	debug_time_long_log("InitSttTestApp_Begin", true);
	oSttTestCntrApplication.InitSttTestApp(new CXLangResource_Win()); 
	debug_time_long_log("InitSttTestApp_End", true);


	QStringList strings;
	for (int i = 1; i < argc; i++)
	{
		strings << argv[i];
	}

	//当前测试功能ID
	if ((oParser.m_strCmdID == ARGV_CMD_ID_MACROTEST) && (!oParser.m_strMacroID.IsEmpty()))
	{
		debug_time_long_log("main_macrotest_Begin", true);
		main_macrotest(oSttTestCntrApplication, oParser);
	}
	else if (oParser.m_strCmdID == ARGV_CMD_ID_OPENFILE)
	{
		main_openfile(oSttTestCntrApplication, oParser);
	}
	else if (oParser.m_strCmdID == ARGV_CMD_ID_OPENDIALOG)
	{
		main_opendialog(oSttTestCntrApplication, oParser);
	}
	else
	{
		main_none(oSttTestCntrApplication, oParser, strings);
	}

#ifdef SttXcmdCh_AxAtsLib

	if (g_theSttAtsLibClient!= NULL)
	{ 
		AtsLib *pAtsLib = g_theSttAtsLibClient->GetAtsLib();
		
		if (pAtsLib)
		{
			pAtsLib->SetLogBase(CLogPrint::GetLog());
		}
	}
   
#endif
	if (g_pSttGlobalProgDlg != NULL)
	{
		delete g_pSttGlobalProgDlg;
		g_pSttGlobalProgDlg = NULL;
	}

	if(shareMem->isAttached())
		shareMem->detach();
	delete shareMem;

	CSttMacroParaEditViewMngr::Release();
	ReleaseSttTestCntrThread();
	debug_time_long_log("ReleaseSttTestCntrThread", true);

    return 0;
}
