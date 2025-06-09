#include "QAxSmartTestApp.h"

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

extern CSttTestAppCfg *g_pTheSttTestAppCfg;


CAxSmartTestApp::CAxSmartTestApp()
{
    m_oMainWnd = NULL;
    g_pTheSttTestAppCfg = &m_oSttTestAppCfg;
    g_bLogEngineDebugInfor = TRUE;
    CLogPrint::Create(this);

    Gb_InitScrpitEngine();
}

CAxSmartTestApp::~CAxSmartTestApp()
{
    CLogPrint::SetLog(NULL);
    CLogPrint::Release();
}

void CAxSmartTestApp::LogString(long nLevel, const CString &strMsg)
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

void CAxSmartTestApp::LogString(long nLevel, const char *strMsg)
{
    LogString(nLevel, CString(strMsg));
}

void CAxSmartTestApp::InitSttTestServerBaseApp()
{
//    QEventLoop loop;
//    QTimer::singleShot(3000,&loop,SLOT(quit()));
//    loop.exec();

//    QTextCodec *codec = QTextCodec::codecForName("GBK");
//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);

    //2022-3-25  lijunqing 初始化多语言资源
    CXLanguageXmlRWKeys::Create();
    CXLanguageMngr::Create(new CXLanguageResourceAts_AutoTest, TRUE);
    CXLanguageMngr::xlang_AddXLanguageRerouce(new CXLanguageResourceIecBase, TRUE);
    CXLanguageMngr::xlang_AddXLanguageRerouce(new CXLanguageResourcePp_PpEngine, TRUE);

    CSttTestAppGateWayCfg::Create();
    CMacroXmlKeys::Create();
    CGbItemsGenRuleDefMngrXmlRWKeys::Create();
    CSttMacroTestUI_TestMacroUIDB::Create();
    CSttTestApps::Create();
    CSmartTestBaseApp::InitSmartTestBaseApp();

    //2020-12-04   lijunqing
//    CString strIP,strMask;
//    stt_net_get_deviceip(strIP, strMask);
//    CSttNativeTestEngine::Create(strIP.GetString(), STT_PORT_NATIVE_SERVER, NULL);

    //2020-11-14 lijunqing
    InitTCtrlCntrPath();

    m_oMainWnd = new CAxSmartTestMainWnd();
    m_oMainWnd->SetTimer(1034, 500, NULL);
}

void CAxSmartTestApp::ExitSttTestServerBaseApp()
{
    if (m_oMainWnd != 0)
    {
        m_oMainWnd->killTimer(1034);
        m_oMainWnd->DestroyWindow();
        delete m_oMainWnd;
    }

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

void CAxSmartTestApp::FireTestItemErrorMsg(CGbItemBase *pItem, long nStopByError)
{

}

void CAxSmartTestApp::FireTestFinishMessage(BOOL bMttTaskFinish)
{

}

void CAxSmartTestApp::CreateReportApp()
{

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CAxSmartTestMainWnd::CAxSmartTestMainWnd()
{

}

CAxSmartTestMainWnd::~CAxSmartTestMainWnd()
{

}

void CAxSmartTestMainWnd::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{

}

void CAxSmartTestMainWnd::OnWndTimer(unsigned int nIDEvent)
{
    if (nIDEvent == 1034)
    {
        g_theNativeTestEngine->OnTimer();
    }
}


