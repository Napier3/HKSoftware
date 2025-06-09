#include "stdafx.h"
#include "SttRelayTestServerApp.h"

#ifndef _PSX_IDE_QT_
#include "../../../Module/SttSocket/TestServer/VC/SttTestServerSocket.h"
#else
#include "../../Module/SttSocket/TestServer/QT/SttTestServerSocket.h"
#include "../../Module/SttDevice/SttDeviceBase.h"
#include "../../Module/SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../../Module/SttTest/Common/IEC61850CfgMngr.h"
#endif

#include "../../Module/Engine/SttTestServerBase.h"
#include "../../Module/Engine/SttServerTestCtrlCntr.h"
#include "../../Module/Engine/QT/SttTestServerEngine.h"
#include "../../Module/SttSocket/SttServerSocketDataBase.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include"SttRelayTestServerApp.h"

#ifdef _PSX_QT_LINUX_
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "QEventLoop"
#include "QTimer"
#include "QNetworkInterface"
#endif

#include "../../Module/SttTest/Common/tmt_adjust_test.h"
#include "../../Module/SttTest/Common/tmt_manu_test.h"
#include "../../Module/SttTest/PTU200L/tmt_pt_test.h"
#include "../../Module/SttTest/Common/SttSystemConfig.h"

CSttRelayTestServerApp::CSttRelayTestServerApp(int &argc, char **argv):QCoreApplication(argc, argv)
{
	CLogPrint::Create(this);
}

CSttRelayTestServerApp::~CSttRelayTestServerApp()
{
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();
}

void CSttRelayTestServerApp::LogString(long nLevel, const CString &strMsg)
{
	QTime tm = QTime::currentTime();
	CString str;
	str.Format(("%d:%d:%d.%d:"),
			   tm.hour(),tm.minute(), tm.second(),
			   tm.msec());
#ifdef _PSX_QT_LINUX_
	qDebug()<<str<<strMsg;
#endif

	if (nLevel != XLOGLEVEL_DEBUG)
	{
		return;
	}

	CSttTestServerBase *pSttTestServer = CSttTestServerBase::GetServerEngine();

	if (pSttTestServer != NULL)
	{
		pSttTestServer->LogDebugInfor(strMsg);
	}
}

void CSttRelayTestServerApp::LogString(long nLevel, const char *strMsg)
{
	LogString(nLevel, CString(strMsg));
}

void CSttRelayTestServerApp::InitSttTestServerBaseApp()
{
	CSttTestServerBaseApp::InitSttTestServerBaseApp();
	int fd=0;
	fd=open("/dev/relaytester",O_RDWR);
	QEventLoop loop;
	QTimer::singleShot(2000,&loop,SLOT(quit()));
	loop.exec();

	QTextCodec *codec = QTextCodec::codecForName("gbk");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForTr(codec);

	CString strPath = qApp->applicationDirPath();
	long nIndex =  strPath.ReverseFind('/');
	strPath = strPath.left(nIndex);
	_P_SetSystemPath(strPath.GetString());

	g_strFtpRootFile=_P_GetSystemPath();
	BOOL bRet = stt_open_adjust_file("DeviceSystemParas.xml");
	stt_init_systemconfig(g_theSystemConfig);
//	stt_xml_serialize_write_SystemConfig();
//	stt_xml_serialize_write_adjust();
	CSttCmdOverTimeTool::Create();
	CSttDeviceBase::g_pSttDeviceBase->InitDevice(fd);
	CIEC61850CfgMngr::Create();
	CIEC61850CfgMngr::g_pIEC61850CfgMngr->InitGooseSub();
	CCfgDataMngrXmlRWKeys::Create();
	CCfgDataMngrConstGlobal::Create();


	QString ip;
	foreach(QNetworkInterface interface,QNetworkInterface::allInterfaces())
	{
		QString name=interface.name();
		if(QString::compare(name,"eth0")==0)
		{
			ip=interface.addressEntries().at(0).ip().toString();
			break;
		}
	}

	QByteArray ba = ip.toLatin1();	


	//stt_xml_serialize_write_ModuleOutPut();
	//stt_xml_serialize_write_SysOutput();
	//stt_xml_serialize_write_PtTest();
	//stt_xml_serialize_write_adjust();
	//	stt_xml_serialize_write_Record();
	//	stt_xml_serialize_write_TimeMeasureTest();
	//	stt_xml_serialize_write_HarmTest();
	//	stt_xml_serialize_write_IEDTest();
	//	stt_xml_serialize_write_MUTimeTest();

	CSttTestServerEngine::Create(fd,ba.data(),STT_PORT_TEST_SERVER);
}

void CSttRelayTestServerApp::ExitSttTestServerBaseApp()
{	
	CCfgDataMngrConstGlobal::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CSttTestServerEngine::Release();

	CIEC61850CfgMngr::Release();
	CSttCmdOverTimeTool::Release();
	CSttTestServerBaseApp::ExitSttTestServerBaseApp();
}

