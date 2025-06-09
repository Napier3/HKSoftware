#pragma once

#ifndef _SttLiveUpdateCoreBaseApp_h__
#define _SttLiveUpdateCoreBaseApp_h__

#include "LiveUpdateBaseApp.h"
#ifdef _USE_NO_GUI_
#include <QCoreApplication>
#else
#include <QApplication>
#endif

#include "QNetworkInterface"
#include <QTimer>

#define SPI_FLAG_EREASE_FINISH      0x01
#define SPI_FLAG_IN_WRITING         0x02
#define SPI_FLAG_WRITE_FINISH       0x03
#define SPI_FLAG_EREASE_FAILED      0x1001
#define SPI_FLAG_IN_WRITING_FAILED  0x1002

//测试仪主板信息
typedef struct{
   unsigned int flag;
   unsigned int version[10];
}Drv_BoardVersion;

#ifdef _USE_NO_GUI_
class CSttLiveUpdateCoreBaseApp : public CLiveUpdateBaseApp, public QCoreApplication, public CLogBase
{
#else
class CSttLiveUpdateCoreBaseApp : public QApplication,public CLiveUpdateBaseApp // ,public QObject
{
    Q_OBJECT
#endif

public:
	CSttLiveUpdateCoreBaseApp(int &argc, char **argv);
	virtual ~CSttLiveUpdateCoreBaseApp();

    void StartServerSocket();

public:
	CString GetLocalIP();
	void ExecSttLiveUpdate();
    void ExecSttLiveUpdate_Debug();
	void ExecSttLiveUpdate_OffLine();//dxy 直接传入压缩包路径，不使用Socket通讯
	void ExecSttLiveUpdate_RollBack();
	void ExecSttLiveUpdate_OnLine();
	void ExitSttLiveUpdate();
	void SendExitInfo(const char *pBuf, long nLen);
	void WriteUpdateLog();
	void WriteRollbackLog();
#ifndef _USE_NO_GUI_
	void MessageBoxReboot();
#endif

	//rollback
	bool SelectFiles(const CString& strDir,CStringArray& arrFiles);
	bool RollbackInstall();

	//FPGA
	bool InitDriverOper();
	void ExitDriverOper();
	void GetFPGAPosition(const CString& strModType,CString& strModTypeDes,CByteArray& nPosArray);
	bool WaitForFPGA();
	CString TransVersion(unsigned int nVal);
	virtual bool IsFPGAFile(const CString& strFPGAFile);
	virtual bool IsMntSysFile(const CString& strSysFile);
	virtual bool UpdateFPGAFile(const CString& strFPGAFile);
	virtual bool UpdateMntSysFile(const CString& strSysFile);
	bool UpdateFPGAData(const CString& strFPGAFile);
    CString GetDriverDevPath();
    void KillRunningProgram();
	void KillRunningProgram_OffLine();//离线升级使用

	void StartLiveUpdateByThr();//通过线程方式启动升级程序
	void FreeLiveUpdateExceThread();
	static UINT LiveUpdateExceThread(LPVOID pParam);
	CWinThread *m_pLiveUpdateExceThread;
	BOOL m_nHasExceFinished;//线程是否执行完成

#ifndef _USE_NO_GUI_
	QTimer m_oTimerThreadRun;
public slots:
	void slot_TimerThreadRun();
#endif
};

extern CSttLiveUpdateCoreBaseApp* g_theCoreBaseApp;

#endif // _SttLiveUpdateCoreBaseApp_h__
