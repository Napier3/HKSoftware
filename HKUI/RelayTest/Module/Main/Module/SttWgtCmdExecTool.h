#ifndef QSTTWGTCMDEXECTOOL_H
#define QSTTWGTCMDEXECTOOL_H

#include "../../../Module/BaseClass/ExBaseList.h"
#include "SttWgtCmdThread.h"
#include <QMainWindow>
#include "../../../Module/System/TickCount32.h"
#include <QSharedMemory>

//wuxinyi 需要将这个存进与testwinbase的公共模块中
// #define STT_UPDATE_TESTMACRO_SM_SIZE	 1048				//TestMacroSM内存大小
// #define STT_UPDATE_TESTMACRO_SM_ID		_T("TestMacroSM")	//TestMacroSM共享内存ID
// #define STATE_ABNORMAL_TYPE _T("abnormal_type")
// #define SMVABNTEST_TPL_ID	_T("abnormal")

class QSttWgtCmdExecTool
{
public:
	enum
	{
		LINUX,
		WINDOWS
	};

	QSttWgtCmdExecTool();
	virtual ~QSttWgtCmdExecTool();

	//zhouhj 2023.10.18 获取等待延时字符串
	CString GetCmdParasString_WaitingTime();

	QSttWgtCmdThread m_oThread;
	long m_nType;

	//zhouhj 2023.10.18
	//在Linux下记录软件已打开运行的时间,如刚打开,进入测试控制中心,需要等待时间长一些
	CTickCount32 m_oStartTickCount;

public:
	static void ExecCmd(const CString& strType, const CString& strID, const CString& strSrcData, const CString &strArgv);
	static void ExecCmd(const CString& strType, QStringList strings);
	static void UpdateExecCmd( const CString &strTmpFile, const CString &strTplID);//通过共享内存或传入参数，调用新的exe  

private:
	//330
	static void OnOpenFile(const CString& strDataSrc, const CString &strArgv);
	static void OnMacroTest(const CString& strID, const CString &strArgv);
	static void OnOpenDialog(const CString& strID, const CString &strArgv);//zhouhj  在linux程序中弹出对话框
	static void OnCmd(const CString& strID);
	static void OnMacroExe(const CString& strID, const CString &strArgv);

	static void ReadSharedData();//读取共享内存数据

	//windows
//	static void OnMacroTest(const CString& strMacroID);
};

extern QSttWgtCmdExecTool* g_pQSttWgtCmdExecTool;
extern QMainWindow *g_pSttWgtCmdMainWindow;
extern QSharedMemory g_oTestMacroSM;//2023-12-26 wuxinyi 切换测试模块共享内存
extern double g_dStartupDelayTime;//开机后等待自动测试启动需要的延时时间

#endif//!QSTTWGTCMDEXECTOOL_H