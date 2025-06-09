#include "stdafx.h"
#include "SttPTUServerApp.h"

#ifndef _PSX_IDE_QT_
#include "../../../Module/SttSocket/TestServer/VC/SttTestServerSocket.h"
#else
#include "../../Module/SttSocket/TestServer/QT/SttTestServerSocket.h"
#include "../../Module/SttDevice/PTU/SttDevice.h"
#endif

#include "../../Module/Engine/SttTestServerBase.h"
#include "../../Module/Engine/SttServerTestCtrlCntr.h"

//////////////////////////////////////////////////////////////////////////

#include "../../Module/Engine/QT/SttTestServerEngine.h"
#include "../../Module/SttSocket/SttServerSocketDataBase.h"
#include "../../Module/SttTest/PTU/SttTestFactoryPTU.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include"../../Module/SttTest/PTU/tmt_manu_test.h"
#include "../../Module/SttTest/PTU/tmt_state_test.h"
#include "../../Module/SttTest/PTU/tmt_harm_test.h"
#include "../../Module/SttTest/PTU/tmt_set_parameter.h"
#include "../../Module/SttTest/PTU/tmt_soe_test.h"
#include "../../Module/SttTest/PTU/tmt_pt_test.h"
#include"SttPTUServerApp.h"
#include "QEventLoop"
#include "QTimer"

#ifdef DEBUG_MODE
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#endif

int fd=0,nport=0;
char *pszip;
CSttPTUServerApp::CSttPTUServerApp(int &argc, char **argv):QCoreApplication(argc, argv)
{
    CLogPrint::Create(this);
#ifndef DEBUG_MODE
	fd=QString(argv[1]).toInt();
#else
	fd=open("/dev/regtest",O_RDWR);
#endif
	pszip=argv[2];
	nport=QString(argv[3]).toInt();
}

CSttPTUServerApp::~CSttPTUServerApp()
{
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();
}

void CSttPTUServerApp::LogString(long nLevel, const CString &strMsg)
{
	QTime tm = QTime::currentTime();
	CString str;
	str.Format(("%d:%d:%d.%d:"),
		tm.hour(),tm.minute(), tm.second(),
		tm.msec());
#ifdef DEBUG_MODE
	qDebug()<<str<<strMsg;
#endif
}

void CSttPTUServerApp::LogString(long nLevel, const char *strMsg)
{
	LogString(nLevel, CString(strMsg));
}

void CSttPTUServerApp::InitSttTestServerBaseApp()
{
	CSttTestServerBaseApp::InitSttTestServerBaseApp();
	QEventLoop loop;
	QTimer::singleShot(3000,&loop,SLOT(quit()));
	loop.exec();

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

	CString strPath = qApp->applicationDirPath();
	long nIndex =  strPath.ReverseFind('/');
	strPath = strPath.left(nIndex);
	_P_SetSystemPath(strPath.GetString());

	CSttDriverOper::Create(fd);
	CSttDevice::Create();
	CCfgDataMngrXmlRWKeys::Create();
	//CCfgDataMngrConstGlobal::Create();
	CSttTestFactoryPTU *pSttFactory = CSttTestFactoryPTU::Create();
	CSttTestServerEngine::Create(fd,pszip,nport);

	stt_xml_serialize_write_ManuTest();
	stt_xml_serialize_write_StateTest();
	stt_xml_serialize_write_HarmTest();
	stt_xml_serialize_write_SetParameter();
	stt_xml_serialize_write_SoeTest();
	stt_xml_serialize_write_PtTest();
}

void CSttPTUServerApp::ExitSttTestServerBaseApp()
{	
	CSttDriverOper::Stop();
	CSttTestServerEngine::Release();
	CSttTestFactoryPTU::Release();
	CSttDevice::Release();

	CSttTestServerBaseApp::ExitSttTestServerBaseApp();
}

