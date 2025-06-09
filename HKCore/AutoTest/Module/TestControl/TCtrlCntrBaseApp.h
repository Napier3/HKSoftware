#pragma once

/*
	功能描述：自动测试的管理基类
	自动测试主程序、单机主程序的应用程序App类都从此类派生
	实现：工作任务的管理、测试管理
*/

#include "SmartTestBaseApp.h"

#include "../TaskMngr/TestLibraryTasks.h"

#include "TestControl.h"
#include "TestControlManyReport.h"
#include "TestControlManyDevice.h"
#include "TestControlSdvMpp.h"
#include "TestControlMdvMgrp.h"

#include "..\..\..\Module\TestMacro\TestMacroInterface.h"
#include "..\..\..\Module\TestMacro\TestMacrosFileMngr.h"

#include "../GuideBook/Script/GbScriptFunctions.h"
#include "..\..\..\Module\XfileMngrBase\XFileMngr.h"

#include "../RecorderInterface.h"
#define _use_ppengine_exception  1

#ifdef _use_ppengine_exception
#include "..\..\..\Module\System\SysExeCpuUsage.h"
#endif

#include "../FactoryBatchTestMngr.h"

#include "..\..\..\Module\Office\WPS.h"
#include "..\..\..\Module\Office\KSO.h"
#include "../GuideBook\ReportMap\WordReport\WordRptFill.h"
#include "../GuideBook\ReportMap\WPSReport\WPSRptFill.h"

class CAutoTestXMLRWKeys;

UINT UI_GetGbTreeImageListID();			//获取GuideBookTreeImageList的图标ID，在CPAautoTest.cpp中实现

// #define _use_MACROTEST_MEM_

#ifdef _use_MACROTEST_MEM_
#include "..\..\..\Module\ShareMem\ShareMemServer.h"
#define	MACROTEST_MEMFILENAME	"_macro_test_ctrl.mrsm"
#define	MACROTEST_MAPNAME			"_macro_test_ctrl"
#define	MACROTEST_MAPSIZE			32768 //(64k*8)524288 + 1000
#endif

#define TEST_MODE_REPORT      0
#define TEST_MODE_TASK        1

//////////////////////////////////////////////////////////////////////////
//CTCtrlCntrBaseApp
class CTCtrlCntrBaseApp : public CWinAppEx, public CSmartTestBaseApp
{
public:
	CTCtrlCntrBaseApp();
	virtual ~CTCtrlCntrBaseApp();

	virtual BOOL ats_IsRegisterTrue(BOOL bShowMsg, BOOL bFromTest=FALSE);

protected:
#ifndef GUIDEBOOK_DEV_MODE
	CTestTask* m_pMttTestTask;
	CProtocolDeviceInterface *m_oMttPpDevice; //2019-6-4  测试任务对应的装置对象
#endif

	//CTestMsgWnd *m_pTestMsgWnd;
	CWnd *m_pXTestMsgWnd;
	
	
#ifdef _use_MACROTEST_MEM_
	CShareMemServer *m_pMemServer;
#endif

#ifdef GB_USE_XFILEMNGRBASE
	CXFileMngr *m_pWaveFileMngr;
#else
	CFileMngrBase m_oWaveFileMngr;
#endif

	CXFileMngr *m_pTestFileMngr;

protected:
	//初始化方法
	virtual long InitSmartTestBaseApp();
	virtual long ExitSmartTestBaseApp();
	void InitTaskMngr();
	void SaveTaskMngr();

	CImageList m_GbTreeImageList;
	CFont *m_pFontTestItem;
	void CreateGbTreeImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);

public:
#ifdef _use_ppengine_exception
	CSysExeCpuUsage m_oSysExeCpuUsage;
	long m_nPpMmsEngineCpuCounts;
	BOOL IsPpMmsEngineException();
#endif

#ifndef GUIDEBOOK_DEV_MODE
	CTestTask* GetMttTestTask()						{	return m_pMttTestTask;			}
	CProtocolDeviceInterface* GetMttPpDevice()						{	return m_oMttPpDevice;			}
	void SetMttPpDevice(CProtocolDeviceInterface  *oMttPpDevoce)						{	m_oMttPpDevice = oMttPpDevoce;			}
#endif

	CImageList* GetGbTreeImageList()				{	return &m_GbTreeImageList;	}
	
	//PpEngine

	virtual void CreatePpEngine();
	virtual void CreateAllEngine();

	virtual BOOL IsMacroTCtrlException();
#ifdef GB_USE_XFILEMNGRBASE
	CXFileMngr* GetWaveFileMngr()	{	return m_pWaveFileMngr;		}
#else
	CFileMngrBase* GetWaveFileMngr()	{	return &m_oWaveFileMngr;		}
#endif
	void ExecutePpEngineCmd(CTestControlBase *pTestControl, const CString &strCmdID, const CString &strCmdPara);

		virtual void CreateNewRecorder();

	CXFileMngr* GetTestFileMngr()	{	return m_pTestFileMngr;	}

	//////////////////////////////////////////////////////////////////////////
	//测试任务部分
#ifndef GUIDEBOOK_DEV_MODE
	CTestTask* CreateNewTask(CTestTask *pTestTask);
	void OpenTaskFile(const CString &strTaskFile);
	void SaveTaskFile();
	void CloseTestTask();
	void ReleaseMttDevice();
#endif

	void SetTestMode_Task()		{	m_dwTestMode = TEST_MODE_TASK;				}
	void SetTestMode_Report()	{	m_dwTestMode = TEST_MODE_REPORT;			}
	BOOL IsTestMode_Task()		{	return (m_dwTestMode == TEST_MODE_TASK);	}
	BOOL IsTestMode_Report()	{	return (m_dwTestMode == TEST_MODE_REPORT);	}

	//报告处理部分
public:
	virtual void CreateReportApp();

public:
	virtual void FireTestItemErrorMsg(CGbItemBase *pItem, long nStopByError);
	virtual void FireTestFinishMessage(BOOL bMttTaskFinish=FALSE);

//其他
public:
	UINT m_nDsvImage;

public:
	CString GetPpEngineCmdID()		{	return m_strPpEngineCmdID;		}
	CString GetPpEngineCmdPara()	{	return m_strPpEngineCmdPara;	}
	void ResetPpEngineCmd()			{	m_strPpEngineCmdID.Empty();		}
	void WritePpMmsEngineConfig();
#ifndef GUIDEBOOK_DEV_MODE
	void WritePpMmsEngineConfig(CTestTask *pTestTask);
#endif

protected:
	CString m_strPpEngineCmdID;
	CString m_strPpEngineCmdPara;

	void ExecutePpEngineCmd_NORMAL(CTestControlBase *pTestControl, const CString &strCmdID, const CString &strCmdPara);
	void ExecutePpEngineCmd_MGBRPT(CTestControlBase *pTestControl, const CString &strCmdID, const CString &strCmdPara);
	void ExecutePpEngineCmd_MDGBRPT(CTestControlBase *pTestControl, const CString &strCmdID, const CString &strCmdPara);
};

extern CTCtrlCntrBaseApp *g_theTCtrlCntrApp;
extern CRptFillAppBase *g_theRptFillApp;

