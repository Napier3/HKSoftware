#include "SttNativeTestMainApp.h"

#include "../../Module/SttSocket/TestServer/VC/SttTestServerSocket.h"
#include "../../Module/Engine/SttNativeTestEngine.h"

//#include "../../Module/SttSocket/SttServerSocketDataBase.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "QNetworkInterface"
#include "../../Module/API/NetworkInterface.h"

#include "QEventLoop"
#include "QTimer"
#include <QDebug>
#include "qtextcodec.h"

#include "../../../AutoTest/Module/GuideBook/Script/GbScriptFunctions.h"
#include "../../../AutoTest/Module/XLanguageResourceAts_AutoTest.h"
#include "../../../Protocol/Module/XLanguageResourcePp_PpEngine.h"
//#include "../../../Module/System/TickCount32.h"

//shaolei   20210528 add
#define TM_TIMER_NATIVE_CONNECT_SERVER_LONG   1500   //Native客户端连接TestServer的定时器
#define TM_TIMER_NATIVE_CONNECT_SERVER_ID   WM_USER + 1112
#define TM_TIMER_NATIVE_AUTO_REGISTER_ID   WM_USER + 1728

//shaolei 20210530  add
#define TM_TIMER_NATIVE_HEARTBEAT_ID   WM_USER + 1618
#define TM_TIMER_NATIVE_HEARTBEAT_LONG   5000
#define TM_TIMER_NATIVE_AUTO_REGISTER_LONG  30000

//QCoreApplication
#ifndef _USE_NO_GUI_
CSttNativeTestMainApp::CSttNativeTestMainApp(int &argc, char **argv):QApplication(argc, argv)
#else
CSttNativeTestMainApp::CSttNativeTestMainApp(int &argc, char **argv):QCoreApplication(argc, argv)
#endif
{
   // g_MainApp = this;
    g_pTheSttTestAppCfg = &m_oSttTestAppCfg;
    CLogPrint::Create(this);

    Gb_InitScrpitEngine();

//    if (argc <= 1)
//    {
//        return;
//    }
}

CSttNativeTestMainApp::~CSttNativeTestMainApp()
{
    CLogPrint::SetLog(NULL);
    CLogPrint::Release();
}

void CSttNativeTestMainApp::LogString(long nLevel, const CString &strMsg)
{
    QTime tm = QTime::currentTime();
    CString str;
    str.Format(("%d:%d:%d.%d:"),
               tm.hour(),tm.minute(), tm.second(),
               tm.msec());

#ifdef DEBUG_MODE
    qDebug()<<str<<strMsg;
#endif

    if (nLevel != XLOGLEVEL_DEBUG && nLevel != XLOGLEVEL_ERROR)
    {
        return;
    }

    CSttNativeTestEngine*pSttNativeTestEngine = CSttNativeTestEngine::GetNativeTestEngine();

    if (pSttNativeTestEngine != NULL)
    {
        pSttNativeTestEngine->LogDebugInfor(strMsg);
    }
}

void CSttNativeTestMainApp::LogString(long nLevel, const char *strMsg)
{
    LogString(nLevel, CString(strMsg));
}

void CSttNativeTestMainApp::InitSttTestServerBaseApp()
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(codec);


    CString strPath = qApp->applicationDirPath();
    long nIndex =  strPath.ReverseFind('/');
    strPath = strPath.left(nIndex);
    _P_SetSystemPath(strPath.GetString());

    //2022-3-25  lijunqing 初始化多语言资源
    CXLanguageXmlRWKeys::Create();
    CXLanguageMngr::Create(new CXLanguageResourceAts_AutoTest, TRUE);
    CXLanguageMngr::xlang_AddXLanguageRerouce(new CXLanguageResourceIecBase, TRUE);

    //g_pTheSttTestAppCfg->Create();
    CSttTestAppGateWayCfg::Create();
    CMacroXmlKeys::Create();
    CGbItemsGenRuleDefMngrXmlRWKeys::Create();
    CSttMacroTestUI_TestMacroUIDB::Create();
    CSttTestApps::Create();
    CSmartTestBaseApp::InitSmartTestBaseApp();

    //2020-12-04   lijunqing
    CString strIP,strMask;

#ifdef _PSX_OS_CENTOS_
    stt_net_get_ip(&strIP);
#else
    stt_net_get_deviceip(strIP, strMask);
#endif

    CSttNativeTestEngine::Create(strIP.GetString(), STT_PORT_NATIVE_SERVER, NULL);

    g_pTheSttTestAppCfg->Open(_T("SttTestAppCfg-remote.xml"));
    if(g_pTheSttTestAppCfg->IsRemote())
    {
        //Native客户端延时连接TestServer，确保TestServer完全启动
        m_oMainWnd.SetTimer(TM_TIMER_NATIVE_CONNECT_SERVER_ID,TM_TIMER_NATIVE_CONNECT_SERVER_LONG, NULL);
    }

    //2020-11-14 lijunqing
    InitTCtrlCntrPath();

    m_oMainWnd.SetTimer(1034, 500, NULL);
}

void CSttNativeTestMainApp::ExitSttTestServerBaseApp()
{
    m_oMainWnd.killTimer(1034);
    m_oMainWnd.DestroyWindow();

    //g_pTheSttTestAppCfg->Release();
    CSttTestAppGateWayCfg::Release();
    CMacroXmlKeys::Release();
    CGbItemsGenRuleDefMngrXmlRWKeys::Release();
    CSttMacroTestUI_TestMacroUIDB::Release();
    CSttTestApps::Release();
    CXLanguageMngr::Release();
    CXLanguageXmlRWKeys::Release();
    CSmartTestBaseApp::ExitSmartTestBaseApp();
    CSttNativeTestEngine::Release();
}

void CSttNativeTestMainApp::Register()
{
    CSttNativeTestEngine *pNativeTestEngine = CSttNativeTestEngine::GetNativeTestEngine();

    if(pNativeTestEngine == NULL)
        return;

    pNativeTestEngine->m_oRemoteRegister.SN_TestApp(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strSN);
    pNativeTestEngine->m_oRemoteRegister.Name_Cop(_T("PowerSky"));
    pNativeTestEngine->m_oRemoteRegister.Name_User(_T("SmartTest"));
    pNativeTestEngine->m_oRemoteRegister.Description(_T("SmartTest"));
    pNativeTestEngine->m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_SmartTest, _T("1.0.0.2"));
    pNativeTestEngine->m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_TestServer, _T("1.0.0.3"));

    CSttCmdData oRetData;
    pNativeTestEngine->Register(&oRetData);
}

void CSttNativeTestMainApp::FireTestItemErrorMsg(CGbItemBase *pItem, long nStopByError)
{

}

void CSttNativeTestMainApp::FireTestFinishMessage(BOOL bMttTaskFinish)
{

}

void CSttNativeTestMainApp::CreateReportApp()
{

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttNativeTestMainWnd::CSttNativeTestMainWnd()
{

}

CSttNativeTestMainWnd::~CSttNativeTestMainWnd()
{

}

void CSttNativeTestMainWnd::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{

}

extern CDataGroup *g_pDeviceAttrs;
void CSttNativeTestMainWnd::OnWndTimer(unsigned int nIDEvent)
{
    if (nIDEvent == 1034)
    {
        g_theNativeTestEngine->OnTimer();
        return;
    }

    //延时1.5s，自动连接TestServer
    if(nIDEvent == TM_TIMER_NATIVE_CONNECT_SERVER_ID )
    {
        CString strIP,strMask;
        stt_net_get_deviceip(strIP, strMask);
        CSttNativeTestEngine *pNativeTestEngine = CSttNativeTestEngine::GetNativeTestEngine();
        BOOL bRet = pNativeTestEngine->m_pNativeClientTestEngine->ConnectServer(strIP, STT_PORT_TEST_SERVER);
        long nRet = 0;

        if(bRet)
        {
            CSttCmdData oRetData;
            nRet = pNativeTestEngine->m_pNativeClientTestEngine->System_Login_Local_Test(TRUE, &oRetData);

            if(Stt_Is_ExecStatus_Success(nRet))
            {
                //登陆成功后，开始心跳
                KillTimer(nIDEvent);
                SetTimer(TM_TIMER_NATIVE_HEARTBEAT_ID, TM_TIMER_NATIVE_HEARTBEAT_LONG, NULL);

                if(!CSttTestAppGateWayCfg::IsAutoRegister())
                {
                    return;
                }

                 //登陆成功后，需要修改测试仪网关，与4G模块的网关一致
                CDataGroup* pGroup = new CDataGroup();
                CDataGroup* pParas = new CDataGroup();
                pParas->AddNewChild(pGroup);
                pGroup->AddNewData(_T(""), _T("IP"), _T(""), CSttTestAppGateWayCfg::GetSubIP());
                pGroup->AddNewData(_T(""), _T("mask"), _T(""), CSttTestAppGateWayCfg::GetMask());
                pGroup->AddNewData(_T(""), _T("GateWay"), _T(""), CSttTestAppGateWayCfg::GetGateWay());
                pGroup->m_strID.Format(_T("SubIP1"));
                pGroup->m_strName.Format(_T("SubIP1"));
                pGroup->m_strDataType.Format(_T("SubIP"));
                nRet = pNativeTestEngine->m_pNativeClientTestEngine->System_SetSysConfig(pParas);
                delete pParas;

                if(Stt_Is_ExecStatus_Success(nRet))
                {
                    //修改辅IP成功后，延时500ms，确保生效
                    CTickCount32 oTick;
                    oTick.DoEvents(500);
                }

                //pNativeTestEngine->AttatchSttTestMsgViewInterface(this);
                // pNativeTestEngine->m_pNativeClientTestEngine->AttatchSttTestMsgViewInterface(this);
                //连接远程服务端
                BOOL bSucc = pNativeTestEngine->ConnectCloudServer(g_pTheSttTestAppCfg->GetCloudIP(), g_pTheSttTestAppCfg->GetCloudServerPort());
                CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("ConnectCloudServer = %d, IP = %s, Port = %d"),
                                           bSucc, g_pTheSttTestAppCfg->GetCloudIP().GetString(), g_pTheSttTestAppCfg->GetCloudServerPort());
                if(bSucc)
                {
                    //向远程服务器注册
                    CSttParas *pParas = oRetData.GetSttParas();
                    CDataGroup *pDeviceAttrs = (CDataGroup*)pParas->FindByID(_T("DeviceAttrs"));
                    CDvmData *pSn = (CDvmData*)pDeviceAttrs->FindByID(_T("SN"));
                    pNativeTestEngine->m_oRemoteRegister.SN_TestApp(pSn->m_strValue);
                    pNativeTestEngine->m_oRemoteRegister.Name_Cop(_T("PowerSky"));
                    pNativeTestEngine->m_oRemoteRegister.Name_User(_T("SmartTest"));
                    pNativeTestEngine->m_oRemoteRegister.Description(_T("SmartTest"));
                    pNativeTestEngine->m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_SmartTest, _T("1.0.0.2"));
                    pNativeTestEngine->m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_TestServer, _T("1.0.0.3"));
                    CSttCmdData oRetData2;
                    long nRegister = pNativeTestEngine->Register(&oRetData2);
                    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Register = %d, SN=%s, IP=%s"),
                                               nRegister, pSn->m_strValue.GetString(), g_pTheSttTestAppCfg->GetCloudIP().GetString());
                }

                SetTimer(TM_TIMER_NATIVE_AUTO_REGISTER_ID, TM_TIMER_NATIVE_AUTO_REGISTER_LONG, NULL);
            }
        }
    }

    if(nIDEvent == TM_TIMER_NATIVE_HEARTBEAT_ID)
    {
        CSttNativeTestEngine *pNativeTestEngine = CSttNativeTestEngine::GetNativeTestEngine();
        if(pNativeTestEngine->m_pNativeClientTestEngine->IsConnectServerSucc())
        {
            pNativeTestEngine->m_pNativeClientTestEngine->Test_SendHeartbeat();
            //pNativeTestEnginet->Test_Send
        }

        if(pNativeTestEngine->IsConnectColudServerSuccess())
        {
            BYTE pSendBuf[STT_PKG_HEAD_LEN];
            long nSendBufLen = 0;

            stt_InitPktBuffer_Head(pSendBuf, STT_CMD_TYPE_HEARTBEAT, 0,
                pNativeTestEngine->m_pSttCloudClientSocket->m_nIDTester, 0, 0);

            pNativeTestEngine->m_pSttCloudClientSocket->SendBuffer(pSendBuf,STT_PKG_HEAD_LEN);
        }
    }

    if(nIDEvent == TM_TIMER_NATIVE_AUTO_REGISTER_ID)
    {
        CSttNativeTestEngine *pNativeTestEngine = CSttNativeTestEngine::GetNativeTestEngine();
        if(!pNativeTestEngine->IsConnectColudServerSuccess())
        {
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Auto Connect to CloudServer per 30s：IP=%s, Port=%d"),
                                       g_pTheSttTestAppCfg->GetCloudIP().GetString(), g_pTheSttTestAppCfg->GetCloudServerPort());
            pNativeTestEngine->ConnectCloudServer(g_pTheSttTestAppCfg->GetCloudIP(), g_pTheSttTestAppCfg->GetCloudServerPort());
            //向远程服务器注册
            CDvmData *pSn = (CDvmData*)g_pDeviceAttrs->FindByID(_T("SN"));
            pNativeTestEngine->m_oRemoteRegister.SN_TestApp(pSn->m_strValue);
            pNativeTestEngine->m_oRemoteRegister.Name_Cop(_T("PowerSky"));
            pNativeTestEngine->m_oRemoteRegister.Name_User(_T("SmartTest"));
            pNativeTestEngine->m_oRemoteRegister.Description(_T("SmartTest"));
            pNativeTestEngine->m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_SmartTest, _T("1.0.0.2"));
            pNativeTestEngine->m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_TestServer, _T("1.0.0.3"));
            CSttCmdData oRetData;
            pNativeTestEngine->Register(&oRetData);
        }
    }
}


