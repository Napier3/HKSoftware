#include "SttTestCntrFrameLinux.h"

#ifdef SttXcmdCh_SttClientSocket
#include "SttTestCntrApplication.h"
#endif

#include "../../Module/SttSocket/SttXcmdChAtsLib/SttAtsLibClient.h"
extern CSttAtsLibClient *g_theSttAtsLibClient;
#ifdef SttXcmdCh_AxAtsLib
#include "SttTestCntrApplicationAx.h"
typedef CSttTestCntrApplicationAx  CSttTestCntrApplication;
#endif

#include <QTextCodec>
#include <QSharedMemory>
#include <QMessageBox>
#include<QDebug>
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../Module/XLangResource_Native.h"
#include "../../Module/SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../../Module/API/StringConvertApi.h"
#include "../../Module/ReplayTest/BigComtradeTransPlay.h"
#include "../../Module/UI/SttEventFilter/SttEventFilter.h"
#include "../../Module/SttTest/Common/LineVolt/tmt_linevolt_gradient_test.h"
#include "../../Module/RecordTest/UI/SttIecRecordDetectWidget.h"
#include "../../Module/RecordTest/UI/MUTest/SttMUTestIecCbSelWidget.h"
#include "../../Module/RecordTest/UI/SttIecRecordMainWidget.h"

//  #ifndef _PSX_QT_LINUX_
//  #include "../../../Module/XMinidmp/XMinidmp.h"
//  #endif

//2022-9-23  lijunqing
#include "../../Module/HtmlReport/IECTest/SttIecTestHtmlRptGenFactory.h"
#include "../../Module/SttTestCtrl/SttArgcArgvParser.h"
// extern bool g_bIsOpenMacroFromMain;

//2022-10-8  lijunqing
#include "../../Module/SmartTestInterface/QT/PpSttIotEngineDebugWidget.h"

#include "../../Module/UI/SttTestCntrCmdDefine.h"
#include "../../Module/UI/Module/CommonCtrl_QT/QSttProgDlg.h"
#include "../../../Module/OSInterface/QT/CDateTime_QT.h"
#include"../../../AutoTest/Module/Characteristic/CharInterfaceVariable.h"
#include "SttMacroParaEditFactoryEng.h"

QSttEventFilter *g_pSttEventFilter = NULL;
QSttProgDlg *g_pSttGlobalProgDlg = NULL;


//t2022-12-02  lijunqing
//macrotest macro_id=MUAccuracyTest;assist=admutest;iec=1;meas_svr=0;macro_file=AdmuTest;
//macrotest macro_id=MUAccuracyTest;assist=mutest;iec=1;meas_svr=0;macro_file=MuTest;
//macrotest macro_id=MUAccurAutoTest;assist=mutest;iec=1;meas_svr=1;macro_file=MuTest;
//open_dialog dialog_id=IecCapDialog;assist=relaytest;iec=0;meas_svr=0;
//open_dialog dialog_id=PpIotEngineClient;assist=relaytest;iec=0;meas_svr=0;
//open_dialog dialog_id=CommConfig;assist=relaytest;iec=0;meas_svr=0;
//macrotest macro_id=ManualTest;macro_file=RelayTest;assist=RelayTest;iec=0;meas_svr=0;
//macrotest macro_id=RemoteCtrlTest;macro_file=RemoteCtrlTest;assist=remotectrltest;iec=0;meas_svr=0;
//macrotest macro_id=RemoteMeasTest;macro_file=RelayTest;assist=RelayTest;iec=0;meas_svr=0;
//macrotest macro_id=DistSearchOneTest;macro_file=RelayTest;assist=RelayTest;iec=0;meas_svr=0;
//macrotest macro_id=ManualTest;sscl_path=D:/11/PONOVO/PONOVO.sscl;iec=0;meas_svr=0;macro_file=RelayTest;assist=RelayTest;
//macrotest macro_id=MUTimingAccurTest;assist=mutest;iec=1;meas_svr=0;macro_file=MuTest;
//macrotest macro_id=DistanceTest_I;macro_file=RelayTest;assist=RelayTest;iec=0;meas_svr=0;


#include "../../Module/UI/SttTestCntrThread.h"

void assist_create(QSttTestCntrFrameLinux &oSttTestCntrFrameLinux, const CString &strAssistID)
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

void main_macrotest(QSttTestCntrFrameLinux &oSttTestCntrFrameLinux
                    , CSttTestCntrApplication &oSttTestCntrApplication, CSttArgcArgvParser &oParser
                    , CSttTestCtrlCntrNative *pSttTestCtrlCntrNative)
{
    CTickCount32 oTickCount;
    CString strMacroID = oParser.m_strMacroID;

    g_nTimeOut_Ats = 8000;//zhouhj 2024.3.21 增加超时时间,防止模板生成超时(合并单元精度测试)
    oSttTestCntrFrameLinux.show();
    oTickCount.DoEvents(50);//zhouhj 2024.3.22 解决打开界面后,只显示进度条,不显示主窗口问题
    oSttTestCntrFrameLinux.OpenMacroTestUI_Test(oSttTestCntrApplication.m_pTestMacroUI, "", "");

    if (oParser.m_nUseIec)
    {
        oSttTestCntrFrameLinux.InitSttIecRecord();
        g_bSmartCap_RecordNow = 0;//
    }

    if (oParser.m_nUseMeasServer)
    {
        pSttTestCtrlCntrNative->InitMeasServer();
    }

    if (strMacroID == STT_ORG_MACRO_ReplayTest)
    {
        g_theBigComtradeTransPlay->CreateSttComtradeSocket();
    }
    else if (strMacroID == STT_ORG_MACRO_IecCapTest)
    {
        if (!g_oSttTestResourceMngr.HasLoadDevice())//
        {
            if (g_oSttTestResourceMngr.SelectDeviceFromLocalDB())
            {
                g_oSttTestResourceMngr.InitLocalSysPara();
            }
        }
    }

    if (g_theSttIecRecordMainWidget != NULL)
    {
        if ((oParser.m_strAssistID == STT_AssistID_MUTEST/*_T("mutest")*/))
        {
            oSttTestCntrFrameLinux.InitSttIecRecord();
            g_bSmartCap_RecordNow = 0;//
            g_theSttIecRecordMainWidget->InitIecRecordCbWidget(strMacroID,STT_IEC_DETECT_TYPE_61850_92);
        }
        else if (oParser.m_strAssistID == STT_AssistID_ADMUTEST)
        {
            oSttTestCntrFrameLinux.InitSttIecRecord();
            g_bSmartCap_RecordNow = 0;//
            g_theSttIecRecordMainWidget->InitIecRecordCbWidget(strMacroID,STT_IEC_DETECT_TYPE_60044);
        }
    }

    //2022-12-01  lijunqing
    assist_create(oSttTestCntrFrameLinux, oParser.m_strAssistID);

#ifdef _PSX_QT_LINUX_
    g_pSttEventFilter = new QSttEventFilter();
    oSttTestCntrApplication.installEventFilter(g_pSttEventFilter);
    //	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,strFrameConfigPath.GetString());
#endif

    if (g_pSttGlobalProgDlg)
    {
        g_pSttGlobalProgDlg->Stop();
    }

    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s(%ld)"),oParser.m_strMacroID.GetString(),
                               oParser.m_nWaitingTime);
    oSttTestCntrApplication.exec();

#ifdef _PSX_QT_LINUX_
    delete g_pSttEventFilter;
#endif
}

void main_openfile(QSttTestCntrFrameLinux &oSttTestCntrFrameLinux
, CSttTestCntrApplication &oSttTestCntrApplication, CSttArgcArgvParser &oParser)
{
    oSttTestCntrFrameLinux.SetAddMacroEnable(false);

    if (g_pSttGlobalProgDlg)
    {
        g_pSttGlobalProgDlg->Stop();
    }
}

void main_open_dialog(QSttTestCntrFrameLinux &oSttTestCntrFrameLinux
                      , CSttTestCntrApplication &oSttTestCntrApplication, CSttArgcArgvParser &oParser)
{
    if (g_pSttGlobalProgDlg)
    {
        g_pSttGlobalProgDlg->Stop();
    }
    oSttTestCntrFrameLinux.OpenDialog(oParser.m_strDialogID);
}

void main_open_none(QSttTestCntrFrameLinux &oSttTestCntrFrameLinux
                    , CSttTestCntrApplication &oSttTestCntrApplication, CSttArgcArgvParser &oParser)
{
    if (g_pSttGlobalProgDlg)
    {
        g_pSttGlobalProgDlg->Stop();
    }
    oSttTestCntrFrameLinux.SetAddMacroEnable(true);
}

int main(int argc, char *argv[])
{
#ifdef SttXcmdCh_AxAtsLib
    g_nSttXcmdCh_Type = SttXcmdChType_AxAtsLib;
#else
    g_nSttXcmdCh_Type = SttXcmdChType_SttClientSocket;
#endif

	CSttMacroParaEditFactoryEng oMacroParaEditFactory;

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
	{//
		delete shareMem;
		return 0;
	}

#ifdef USE_Custom_CDateTime
	CDateTime::CreateClientDataTime();
#endif
	CreateSttTestCntrThread();

	//2022-10-5  lijunqing
	CSttArgcArgvParser oParser;
	oParser.Parser(argc, argv);

	CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID = oParser.m_strMacroFile;
	//2022-9-23  lijunqing
    CSttIecTestHtmlRptGenFactory *pHtmlRptGenFactory = new CSttIecTestHtmlRptGenFactory();

	CSttTestCntrApplication oSttTestCntrApplication(argc, argv);
	oSttTestCntrApplication.InitSttTestApp(new CXLangResource_Native());
	
	{
        CTickCount32 oTickCount;
        oTickCount.DoEvents(10);
	}

    //2023-3-1  lijunqing
    //QSttStartInfoWidget wndStartInfor;
    //wndStartInfor.show();

	CSttTestCtrlCntrNative *pSttTestCtrlCntrNative = new CSttTestCtrlCntrNative();
	oSttTestCntrApplication.SetSttTestCtrlCntr(pSttTestCtrlCntrNative);
    pHtmlRptGenFactory->OpenDataTypesByMacroFileID(oParser.m_strMacroFile);

	CString strMacroID,strDialogID;
	//strMacroID = argv[1];
	strMacroID = oParser.m_strMacroID;
	strDialogID = oParser.m_strDialogID;

	oSttTestCntrApplication.SetCurrTestMacroUI(strMacroID);

	CSttMacroParaEditViewMngr::Create();
    QSttTestCntrFrameLinux oSttTestCntrFrameLinux;
	CString strFrameConfigPath;
//	oParser.m_strMacroFile = _T("RelayTest");

//	stt_xml_serialize_write_LineVolGradientTest();

	if (!oParser.m_strMacroFile.IsEmpty())
	{
		strFrameConfigPath.Format(_T("%s/TestCntrlFrameConfig.xml"),oParser.m_strMacroFile.GetString());
	}
	else
	{
		strFrameConfigPath = _T("TestCntrlFrameConfig.xml");
	}

	if (IsFileExist(oParser.m_strSsclFilePath))
	{
		pSttTestCtrlCntrNative->m_oSclStation.OpenSclStationFile(oParser.m_strSsclFilePath);
	}

 	oSttTestCntrFrameLinux.InitFrame(strFrameConfigPath);
 	oSttTestCntrFrameLinux.SetTestCtrlCntrBase(oSttTestCntrApplication.m_pTestCtrlCntr);

    oSttTestCntrApplication.StartSmartTest(oParser.m_strMacroID);

	if (oParser.m_strCmdID == ARGV_CMD_ID_MACROTEST)
	{	//2022-10-5  lijunqing macrotest
        main_macrotest(oSttTestCntrFrameLinux, oSttTestCntrApplication, oParser, pSttTestCtrlCntrNative);
	}
	else if (oParser.m_strCmdID == ARGV_CMD_ID_OPENFILE)
	{////2022-10-5  lijunqing open auto test file : gbxml, gbrpt
        main_openfile(oSttTestCntrFrameLinux, oSttTestCntrApplication, oParser);
	}
	else if (oParser.m_strCmdID == ARGV_CMD_ID_OPENDIALOG)
	{
        main_open_dialog(oSttTestCntrFrameLinux, oSttTestCntrApplication, oParser);
	}
	else
	{
        main_open_none(oSttTestCntrFrameLinux, oSttTestCntrApplication, oParser);
	}

//	CXMessageBox::information(NULL,"042","000000" );
	if (g_pSttGlobalProgDlg)
	{
		delete g_pSttGlobalProgDlg;
		g_pSttGlobalProgDlg = NULL;
	}

    if(shareMem->isAttached())
        shareMem->detach();
    delete shareMem;

	CSttMacroParaEditViewMngr::Release();

	//2022-9-23  lijunqing
   delete pHtmlRptGenFactory;

	ReleaseSttTestCntrThread();

#ifdef USE_Custom_CDateTime
	CDateTime::ReleaseClientDataTime();
#endif
    return 0;
}
