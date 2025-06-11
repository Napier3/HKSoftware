#pragma once

/*
	功能描述：自动测试的管理基类
	自动测试主程序、单机主程序的应用程序App类都从此类派生
	实现：工作任务的管理、测试管理
*/

#include "../TCtrlCntrConfig.h"
#include "../TCtrlSystemConfig.h"
#include "../GuideBook/GbCommCmdConfig/GbCommCmdConfig.h"

#ifndef _PSX_QT_LINUX_
#include "../../../Module/KeyDb/XKeyDB.h"
#endif

#include "../GuideBook/ReportMap/ReportTemplateConfig/ReportTemplateConfig.h"
#include "../GuideBook/GuideBook.h"

#ifndef _PSX_IDE_QT_
#include "../GuideBook/ReportMap/WordRptFillBase.h"
#endif

#include "../TCtrlCntrWorkSpace.h"
#include "../TCtrlCntrDefine.h"

//TestMacro and Protocol Interface
#include "../Module/SmartTestInterface/MacroTestFactory.h"
#include "../Module/SmartTestInterface/ProtocolEngineFactory.h"

#include "../RecorderInterface.h"
#include "../GuideBook/ReportMap/WordRptFillBase.h"
#include "../Module/SttCmd/SttAtsCmd.h"
#include "../Module/SttAtsSvr/SttSmartTest.h"

class CAutoTestXMLRWKeys;
class CTestControlBase;

//////////////////////////////////////////////////////////////////////////
//CSmartTestBaseApp
class CSmartTestBaseApp
{
public:
	CSmartTestBaseApp();
	virtual ~CSmartTestBaseApp();

	virtual BOOL ats_IsRegisterTrue(BOOL bShowMsg, BOOL bFromTest=FALSE) = 0;

protected:
	DWORD m_dwTestMode;   //测试模式
	CTCtrlCntrConfig* m_pCtrlCntrConfig;
	CTCtrlSystemConfig* m_pSystemConfig;

    //2020-08-27 lijunqing
#ifndef _PSX_QT_LINUX_
    CXKeyDB *m_pKeyDB;
#endif
	CReportTemplateConfig m_oReportTemplateConfig;

protected:
	//初始化方法
	virtual long InitSmartTestBaseApp();
	virtual long ExitSmartTestBaseApp();

public:
	CTCtrlCntrConfig* GetCntrConfig()				{	return m_pCtrlCntrConfig;	}
	CTCtrlSystemConfig* GetSystemConfig()			{	return m_pSystemConfig;		}

	//PpEngine
	CProtocolEngineInterface* GetPpEngine(const CString &strEngineMode, const CString &strProgID);
	BOOL HasPpEngine();
	void ReleasePpEngine(const CString &strProgID);
	void ReleasePpEngine();

	//MacroTest
	CMacroTestInterface* GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps);
	void ReleaseMacroTestEngine();
	virtual void InitMacroTestEngineShowSpyWnd();
	void ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara);

	virtual void CreateMacroTestEngine(const CString &strMacroFile);
    virtual void InitPpEngineShowSpyWnd();
	virtual void StopProtocolParseForReadSoe(BOOL bStop);

#ifndef _PSX_QT_LINUX_
    CXKeyDB* GetXKeyDB()	{	return m_pKeyDB;	}
#endif

	BOOL Is_UsePowerTestTrans();
	long GetSysRptShowMaxCount()	{	return m_pCtrlCntrConfig->GetSysRptShowMaxCount();	}

	CString GetWorkSpacePath();

	CBkmkDataProcessMngr* GetBkmkDataProcessMngr()		{	return m_oReportTemplateConfig.GetBkmkDataProcessMngr();	}

protected:
	CRecorderInterface *m_oRecorder;

public:
	virtual void CreateNewRecorder(){}
	void InitRecorder(CTestControlBase *pTestControl);
	CRecorderInterface* GetRecorder()	{	return m_oRecorder;	}
	BOOL HasRecorder()	{	return m_pCtrlCntrConfig->HasRecorder();	}
	void SetRecorderProgID(const CString &strProgID);
	long GetRecorderDelay()	{	return m_pCtrlCntrConfig->m_nRecordDelay;	}
	long GetAddRecorderReport()	{	return m_pCtrlCntrConfig->m_nAddRecordReport;	}
	BOOL GetAddRecorderReport_Engine()	{	return (m_pCtrlCntrConfig->m_nAddRecordReport == 2);	}
	BOOL GetAddRecorderReport_Recorder()	{	return (m_pCtrlCntrConfig->m_nAddRecordReport == 1);	}
	void ReleaseRecorder();

//报告处理部分
public:
	CRptFillAppBase* m_pRptFillAppBase;
	void CreateApp(PFUNC_RPTFILLAPP_CREATE pCreateFunc);
    virtual void CreateReportApp() = 0;

public:
    virtual void FireTestItemErrorMsg(CGbItemBase *pItem, long nStopByError) = 0;
    virtual void FireTestFinishMessage(BOOL bMttTaskFinish=FALSE) = 0;

	BOOL IsDebugWithoutReport()	{	return m_pCtrlCntrConfig->m_nDebugWithoutReport;	}
	BOOL IsDebugWithoutGbTree()	{	return m_pCtrlCntrConfig->m_nDebugWithoutGbTree;	}
	BOOL IsInsertDataLinkWhenEligible()	{	return m_pCtrlCntrConfig->m_nInsertDataLinkWhenEligible;	}
	BOOL IsSaveRptToDB()	{	return m_pCtrlCntrConfig->m_nSaveRptToDB;	}
	BOOL IsWriteTestTempFile()	{	return m_pCtrlCntrConfig->m_nWriteTestTempFile;	}
	BOOL IsFillReport()	{	return m_pCtrlCntrConfig->m_nFillReport;	}
	void SetSaveRptToDB(BOOL b)	{	m_pCtrlCntrConfig->m_nSaveRptToDB = b;	}
	long GetReportControl()	{	return m_pCtrlCntrConfig->GetReportControl();	}

	CString GetPpTemplateFilePath();

//2020-12-22  lijunqing   for 简化版本
public:
	void ConfigTestApp(const CString &strProgID, const CString &strIP);
	void ConfigTestDevice(const CString &strProgID, const CString &strDvmFile);
	void ReleaseConfig();

	unsigned long m_hMacroTestLogWnd;
	unsigned long m_hPpEngineLogWnd;

private:
	CString m_strOldProgID_TestEngine;
	CString m_strOldProgID_PpEngine;

//////////////////////////////////////////////////////////////////////////
//自动测试相关的服务  2023-8-15  lijunqing
public:
	void ProcessShellCmd(const CString &strCmdLine, CWnd *pMainWnd);
	void SetMainWnd(CWnd *pWnd);
	BOOL IsSmartTestRpc();

	CString m_strBentchSN;  //测试台SN
	CString m_strDeviceSN;  //被测装置SN

protected:
	CString m_strCmdID;  //命令行参数的CmdID：open_gbrpt	CreateTest ReTest	ExportReport
	CString m_strCmdFile;  //命令对应的参数文件
	long m_nSvr_MQTT;      //是否启动MQTT服务
	long m_nSvr_STT;      //是否启动MQTT服务
	long m_nSmartTestServer;  //自动测试智能服务
	CString m_strAtsServiceSN;   //服务端SN
	long m_nSttCmdFormat;  //命令格式
	long m_nStartTestAfterCreate;  //创建测试后，立即开始自动测试

	CString m_strMacroID; //外部调用时，功能模块ID；

	long ProcessShellCmd_Key(CString &strID, CString &strValue);
	virtual void OnShellCmd(CWnd *pMainWnd);
	virtual void StartSvr_CreateSttSmartTest();
	virtual void StartSvr_SmartTestServer();
	virtual void StartSvr_MQTT();
	virtual void StartSvr_STT();
	virtual void OnShellCmd_open_gbrpt();
	virtual void OnShellCmd_CreateTest();
	virtual void OnShellCmd_ReTest();
	virtual void OnShellCmd_ExportReport();
	virtual void SetXmlRwType(long nType);
	void StopSvr();
	virtual CString GetCmdFilePath(long nMode);
	virtual CSttAtsCmd* OpenCmdFile();
public:
	virtual long GetXmlRwType();
};

BOOL TCC_IsDebugWithoutReport();
COLORREF TCC_GetItemStateColor(CGbItemBase *pItem, BOOL bEnable=TRUE);
extern CSmartTestBaseApp *g_theSmartTestBaseApp;
extern CRptFillAppBase *g_theRptFillApp;

void Init_ShowTestWndTop(BOOL bMinimize);

//2023-8-22 李俊庆  自动测试端，全局唯一的BenchSN
extern CString *g_strSmartTest_BenchSN;
extern CSttSmartTest *g_theSttSmartTest;
extern CString *g_strMacroID;
