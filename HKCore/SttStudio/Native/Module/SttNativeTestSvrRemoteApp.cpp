#include "SttNativeTestSvrRemoteApp.h"

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

CSttNativeTestSvrRemoteApp::CSttNativeTestSvrRemoteApp(int &argc, char **argv):QCoreApplication(argc, argv)
{
    g_bLogEngineDebugInfor = TRUE;
     CLogPrint::Create(this);

     Gb_InitScrpitEngine();

    if (argc <= 1)
    {
        return;
    }
}

CSttNativeTestSvrRemoteApp::~CSttNativeTestSvrRemoteApp()
{
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();
}

void CSttNativeTestSvrRemoteApp::LogString(long nLevel, const CString &strMsg)
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

void CSttNativeTestSvrRemoteApp::LogString(long nLevel, const char *strMsg)
{
	LogString(nLevel, CString(strMsg));
}

void CSttNativeTestSvrRemoteApp::InitSttTestServerBaseApp()
{
	QEventLoop loop;
	QTimer::singleShot(3000,&loop,SLOT(quit()));
	loop.exec();

    QTextCodec *codec = QTextCodec::codecForName("GBK");//("UTF-8");//
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale()); //设置GBK到本地
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());


	CString strPath = qApp->applicationDirPath();
	long nIndex =  strPath.ReverseFind('/');
	strPath = strPath.left(nIndex);
	_P_SetSystemPath(strPath.GetString());

//2020-12-04   lijunqing
    CString strIP,strMask;
    stt_net_get_deviceip(strIP, strMask);

    CSttNativeTestEngine::Create(strIP.GetString(), STT_PORT_NATIVE_SERVER);

    //2020-11-14 lijunqing
    InitTCtrlCntrPath();
   /*
// 2020-5-31  lijunqing
    //Test open file
    CString strFile, strFile2, strFile3, strFile4;
    strFile = _P_GetLibraryPath();
    strFile += "TTU0.xml";
    strFile2 = _P_GetLibraryPath();
    strFile2 += "TTU2.xml";
    strFile3 = _P_GetLibraryPath();
    strFile3 += "TTU3.xml";
    strFile4 = _P_GetLibraryPath();
    strFile4 += "TTU4.xml";
    CDvmDevice oDevice;
    CDataMngrXmlRWKeys::Create();
    oDevice.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

     oDevice.SaveXmlFile(strFile2, CDataMngrXmlRWKeys::g_pXmlKeys);

     char *pszBuffer = NULL;
     long nLen = oDevice.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, &pszBuffer, 0);
     FILE *pfile = fopen(strFile3.GetString(), "w+b");
     fwrite(pszBuffer, nLen, 1, pfile);
     fclose(pfile);

     CDvmDevice oDevice2;
     oDevice2.SetXml_UTF8(pszBuffer, CDataMngrXmlRWKeys::g_pXmlKeys);
      oDevice2.SaveXmlFile(strFile4, CDataMngrXmlRWKeys::g_pXmlKeys);

     delete pszBuffer;

    CDataMngrXmlRWKeys::Release();
*/

    //2020-11-14 test script load
    /*
    CString strTemplateFile, strDeviceFile, strDeviceID;
    strTemplateFile = _P_GetTemplatePath();
    strTemplateFile += "TcpClient.ppxml";
    strDeviceFile = _P_GetLibraryPath();
    strDeviceFile += "TTU.xml";
    strDeviceID = "TTU";
    CPxiDevice *pXiDevice = g_thePxiEngine->CreateDevice(strTemplateFile, strDeviceFile, strDeviceID);
    pXiDevice->RunProcedure("ReadAin", "");
*/

    m_oMainWnd.SetTimer(1034, 500, NULL);
}

void CSttNativeTestSvrRemoteApp::ExitSttTestServerBaseApp()
{
    m_oMainWnd.killTimer(1034);
   m_oMainWnd.DestroyWindow();

     CSttNativeTestEngine::Release();
 }

void CSttNativeTestSvrRemoteApp::FireTestItemErrorMsg(CGbItemBase *pItem, long nStopByError)
{

}

void CSttNativeTestSvrRemoteApp::FireTestFinishMessage(BOOL bMttTaskFinish)
{

}

void CSttNativeTestSvrRemoteApp::CreateReportApp()
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

void CSttNativeTestMainWnd::OnWndTimer(unsigned int nIDEvent)
{
    if (nIDEvent == 1034)
    {
         g_theNativeTestEngine->OnTimer();
    }
}


