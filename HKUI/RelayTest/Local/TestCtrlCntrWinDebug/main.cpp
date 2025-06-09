#include "../TestCtrlCntrWin/SttTestCntrFrameWin.h"
#ifdef SttXcmdCh_SttClientSocket
#include "../TestCtrlCntrWin/SttTestCntrApplication.h"
#endif

#ifdef SttXcmdCh_AxAtsLib
#include "../TestCtrlCntrWin/SttTestCntrApplicationAx.h"
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

#ifdef use_CSmartCapCtrl
#include "../../Module/RecordTest/UI/SttIecRecordDetectWidget.h"
#endif

#include "../../../Module/xml/PugiXML/pugixml.hpp"

#include "SttMacroParaEditFactoryDebug.h"
#include "../../Module/SttSocket/SttXcmdChAtsLib/SttAtsLibClient.h"
QSttProgDlg *g_pSttGlobalProgDlg = NULL;
extern CSttAtsLibClient *g_theSttAtsLibClient;

void ShowSttGlobalProgDlg()
{
	CTickCount32 oTickCount;

	if (g_pSttGlobalProgDlg == NULL)
	{
		g_pSttGlobalProgDlg = new QSttProgDlg(NULL);
	}

	g_pSttGlobalProgDlg->initUI(_T("功能加载进度条"),_T("正在加载测试功能界面,请稍后..."));
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

int main(int argc, char *argv[])
{
    CSttMacroParaEditFactoryDebug oFactory;

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

	//2022-10-5  lijunqing
	CSttArgcArgvParser oParser;
	oParser.Parser(argc, argv);
	CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID = oParser.m_strMacroFile;

	//2022-9-23  lijunqing
#ifdef use_CSmartCapCtrl
    CSttIecTestHtmlRptGenFactory *pHtmlRptGenFactory = new CSttIecTestHtmlRptGenFactory();
#endif  //use_CSmartCapCtrl

	CSttTestCntrApplication oSttTestCntrApplication(argc, argv); 
	oSttTestCntrApplication.InitSttTestApp(new CXLangResource_Win());  
//	g_oSttTestResourceMngr.SelectDeviceFromLocalDB();
	CSttTestCtrlCntrWin *pSttTestCtrlCntrWin = new CSttTestCtrlCntrWin();
	pSttTestCtrlCntrWin->SttOpen("TestAppConfigSttAtsWin.xml");
	oSttTestCntrApplication.SetSttTestCtrlCntr(pSttTestCtrlCntrWin);

#ifdef use_CSmartCapCtrl
    pHtmlRptGenFactory->OpenDataTypesByMacroFileID(_T("RelayTest"));
#endif  //use_CSmartCapCtrl

    g_oSttSystemConfig.OpenSystemConfig();

	//2023.6.2 zhouhj
	if ((oParser.m_strCmdID != ARGV_CMD_ID_OPENDIALOG)&&
		(!oSttTestCntrApplication.IsMuTest(oParser.m_strMacroID))
		&&(!g_oSttSystemConfig.m_nInternationalMode))
	{
		oSttTestCntrApplication.StartIotProtoServer();
	}

	BOOL bSmartTestRet = oSttTestCntrApplication.StartSmartTest(oParser.m_strMacroID);

	CString strTestMode, strMacroID;
	strTestMode = argv[1];
	strMacroID = oParser.m_strMacroID;;

	QStringList strings;
	for (int i = 1; i < argc; i++)
	{
		strings << argv[i];
	}
	
	oSttTestCntrApplication.SetCurrTestMacroUI(strMacroID);
	oSttTestCntrApplication.m_pTestCtrlCntr->InitDefaultHdRs();

	//当前测试功能ID
	CSttMacroParaEditViewMngr::Create();
	QSttTestCntrFrameWin oSttTestCntrFrameWin;
	oSttTestCntrFrameWin.SetTestCtrlCntrBase(oSttTestCntrApplication.m_pTestCtrlCntr);

	CString strFrameConfigPath;

	if (!oParser.m_strMacroFile.IsEmpty())//20221206 zhouhj 增加用于区分测试功能
	{
		strFrameConfigPath.Format(_T("%s/TestCntrlFrameConfigWin.xml"),oParser.m_strMacroFile.GetString());
	} 
	else
	{
		strFrameConfigPath = _T("TestCntrlFrameConfigWin.xml");
	}

	if (IsFileExist(oParser.m_strSsclFilePath))
	{
		pSttTestCtrlCntrWin->m_oSclStation.OpenSclStationFile(oParser.m_strSsclFilePath);
	}

	if ((oParser.m_strCmdID == ARGV_CMD_ID_MACROTEST)&&(!strMacroID.IsEmpty()))
	{	//2022-10-5  lijunqing macrotest
		oSttTestCntrFrameWin.SetAutoTest(FALSE);
		oSttTestCntrFrameWin.InitFrame(strFrameConfigPath);
		oSttTestCntrFrameWin.show();
//		oSttTestCntrFrameWin.FFT_CalDebug();

		if (bSmartTestRet)//单击响应消息,且本次调用了SmartTest,则经过延时处理
		{
			ShowSttGlobalProgDlg();
		}

		if (oParser.m_nUseIec)
		{
#ifdef use_CSmartCapCtrl
            if ((oParser.m_strAssistID == STT_AssistID_MUTEST/*_T("mutest")*/))
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
#endif  //use_CSmartCapCtrl
        }

		if (oParser.m_nUseMeasServer)
		{
			pSttTestCtrlCntrWin->InitMeasServer();
		}

		oSttTestCntrFrameWin.m_pSttGbTreeView->setVisible(FALSE);
		oSttTestCntrFrameWin.OnMacroTest(oSttTestCntrApplication.m_pTestMacroUI);
		oSttTestCntrFrameWin.showMaximized();

//		if (strMacroID == STT_ORG_MACRO_ReplayTest)
//		{
//			g_theBigComtradeTransPlay->CreateSttComtradeSocket();
//		}
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s"),argv[2]);

// 		CString strFiber;
// 		strFiber.Format(/*_T("光口%d")*/g_sLangTxt_Gradient_POpticalPort.GetString(),3); //lcq

		oSttTestCntrApplication.exec();

// 		if (oParser.m_nUseMeasServer)
//		{
// 			pSttTestCtrlCntrWin->ExitMeasServer();
//		}

		if (!g_oSttSystemConfig.IsDoubleClickEdit()) //2023.7.25 zhouhj 在测试仪工控机内运行关闭时,会报Runtime Error 错误,暂时关闭时做延时处理
		{
			Sleep(2000);
		}
	}
	else if (oParser.m_strCmdID == ARGV_CMD_ID_OPENFILE)
	{
		oSttTestCntrFrameWin.InitFrame(strFrameConfigPath);
		oSttTestCntrFrameWin.SetAddMacroEnable(false);
	}
	else if (oParser.m_strCmdID == ARGV_CMD_ID_OPENDIALOG)
	{
		if (bSmartTestRet)//单击响应消息,且本次调用了SmartTest,则经过延时处理
		{
			ShowSttGlobalProgDlg();
		}

		oSttTestCntrFrameWin.InitFrame(strFrameConfigPath);
		oSttTestCntrFrameWin.OpenDialog(oParser.m_strDialogID);
	}
	else if (strings.count()>0)
	{
		oSttTestCntrFrameWin.InitFrame(strFrameConfigPath);
		oSttTestCntrFrameWin.show();
		oSttTestCntrFrameWin.SetAutoTest(TRUE);
		oSttTestCntrFrameWin.OnAutoTest(strings);
		oSttTestCntrFrameWin.showMaximized();
		oSttTestCntrApplication.exec();
	}
	else
	{
		oSttTestCntrFrameWin.InitFrame(strFrameConfigPath);
		oSttTestCntrFrameWin.showMaximized();
		oSttTestCntrApplication.exec();
	}

#ifdef SttXcmdCh_AxAtsLib
    AtsLib *pAtsLib = g_theSttAtsLibClient->GetAtsLib();
    pAtsLib->SetLogBase(CLogPrint::GetLog());
#endif

// 	if(strTestMode.GetLength())
// 	{
// 		if(strTestMode == "MacroTest")
// 		{
// 			oSttTestCntrFrameWin.SetAutoTest(FALSE);
// 
// 			
// 			oSttTestCntrFrameWin.OnMacroTest(oSttTestCntrApplication.m_pTestMacroUI);
// 
// 			if (strMacroID == STT_ORG_MACRO_ReplayTest)
// 			{
// 				g_theBigComtradeTransPlay->CreateSttComtradeSocket();
// 			}
// 		}
// 		else
// 		{
// 			oSttTestCntrFrameWin.SetAutoTest(TRUE);
// 			oSttTestCntrFrameWin.OnAutoTest(strings);
// 		}
// 	}

	/*oSttTestCntrFrameWin.OpenMacroTestUI(oSttTestCntrApplication.m_pTestMacroUI);

	if (strMacroID == _T(""))
	{
		oSttTestCntrFrameWin.SetSelectEnable(true);
	}
	else
	{
		oSttTestCntrFrameWin.SetSelectEnable(false);
	}*/

//	stt_xml_serialize_write_SoeTest();

//	oSttTestCntrApplication.exec();

	if (g_pSttGlobalProgDlg != NULL)
	{
		delete g_pSttGlobalProgDlg;
		g_pSttGlobalProgDlg = NULL;
	}

	if(shareMem->isAttached())
		shareMem->detach();
	delete shareMem;

	CSttMacroParaEditViewMngr::Release();

#ifdef use_CSmartCapCtrl
    //2022-9-23  lijunqing
    delete pHtmlRptGenFactory;
#endif  //use_CSmartCapCtrl

    return 0;
}
