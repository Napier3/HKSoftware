#include "SttTestCntrApplication.h"
#include "..\..\Module\UI\SttTestCntrFrameAPI.h"
#include "../../../61850/Module/61850ClientConfig/61850ClientCfgMngrGlobal.h"

#ifdef SttXcmdCh_SttClientSocket

CGbSmartGenWzd *g_theGbSmartGenWzd;
#ifdef use_CSmartCapCtrl
extern long g_nXSttRcdInitChDvmData_Harm;// = 31;
#endif

CSttTestCntrApplication::CSttTestCntrApplication(int argc, char *argv[])
	: QApplication( argc, argv)
{
	m_pGbSmartGenWzd = NULL;
#ifdef use_CSmartCapCtrl
    g_nXSttRcdInitChDvmData_Harm = 25; //2022-5-8  lijunqing  //20220511 zhouhj 目前只计算到25次谐波,暂时只显示25次
#endif
}

CSttTestCntrApplication::~CSttTestCntrApplication()
{

}


void CSttTestCntrApplication::InitSttTestApp(CXLanguageResourceBase *pLanguage)
{
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	//   QTextCodec::setCodecForLocale(codec);  

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#else
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif

#ifndef _PSX_QT_LINUX_ 
	//2023.03.25 zhouhj 增加用于解决未装Qt环境的电脑乱码问题
	CString strLibraryPath;
	strLibraryPath = _P_GetBinPath();
	strLibraryPath += _T("codecs");
	QCoreApplication::addLibraryPath(strLibraryPath);
#endif

	CSttTestAppBase::InitSttTestApp(pLanguage);

//	C61850ClientCfgMngrXmlRWKeys::Create();

	//2022-09-09  lijunqing
	m_pGbSmartGenWzd = new CGbSmartGenWzd();
	g_theGbSmartGenWzd = m_pGbSmartGenWzd;
	m_pGbSmartGenWzd->InitGbSmartGenWzd();
}

void CSttTestCntrApplication::ExitSttTestApp()
{
	if (stt_Frame_GbTreeCtrl() != NULL)
	{
		disconnect(stt_Frame_GbTreeCtrl(),SIGNAL(itemChanged(QTreeWidgetItem *, int))
			,stt_Frame_GbTreeCtrl(),SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	}

	CSttTestAppBase::ExitSttTestApp();

//	C61850ClientCfgMngrXmlRWKeys::Release();
	delete m_pGbSmartGenWzd;
	m_pGbSmartGenWzd = NULL;
	g_theGbSmartGenWzd = NULL;
	CLogPrint::CloseLogFile();
}

BOOL CSttTestCntrApplication::StartSmartTest(const CString& strMacroID)
{
    if (IsProgramExist(_T("SmartTestCore.exe")))
    {
#ifdef _DEBUG
        return FALSE;
#endif
        ExitSmartTest();
    }

    CString strPath;
    strPath = _P_GetInstallPath();
    strPath += _T("e-Report/Bin/");
    strPath += _T("SmartTestCore.exe");

    //2022-3-27  lijunqing  直接启动，运行于后台
    CString strCmdLine = _T("MacroID:");

    if (SmartTestIsNeedArguments(strMacroID))
    {
        strCmdLine += strMacroID;
        strCmdLine += ";";
        QSttWgtCmdThread::startDetached_exe(strPath, strCmdLine);
    }
    else
    {
        QSttWgtCmdThread::startDetached_exe(strPath, _T(""));
    }

    return TRUE;
}

void CSttTestCntrApplication::ExitSmartTest()
{
    TerminateProgram(_T("SmartTestCore.exe"));
}

void CSttTestCntrApplication::StartIotProtoServer()
{
    if (IsProgramExist(_T("IotProtoServer.exe")))
    {
        ExitIotProtoServer();
    }

    CString strPath;
    strPath = _P_GetInstallPath();
    strPath += _T("IotEngineServer/Bin/");
    strPath += _T("IotProtoServer.exe");

    //直接启动，运行于后台
    QSttWgtCmdThread::startDetached_exe(strPath, _T(""));
}

void CSttTestCntrApplication::ExitIotProtoServer()
{
    TerminateProgram(_T("IotProtoServer.exe"));
}

#endif
