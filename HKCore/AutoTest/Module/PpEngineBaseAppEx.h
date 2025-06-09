#pragma once

/*
	功能描述：规约引擎调用管理基础App对象
	自动测试主程序、单机主程序的应用程序App类都从此类派生
*/

#include "PpEngineCreateMngr.h"

//////////////////////////////////////////////////////////////////////////
//CPpEngineBaseAppEx
class CPpEngineBaseAppEx : public CWinAppEx
{
public:
	CPpEngineBaseAppEx();
	virtual ~CPpEngineBaseAppEx();

protected:
	//支持多规约功能，即传统规约和61850MMS规约兼容  2016-8-15
	CPpEngineCreateMngr m_oPpEngineCreateMngr;

	CWnd *m_pXTestMsgWnd;

protected:
	//初始化方法
	long InitTCtrlBaseApp();
	long ExitPpEngineBaseAppEx();

public:
	//PpEngine
	PpEngine::IPpEnginePtr GetPpEngine(const CString &strProgID);
	BOOL HasPpEngine();

	//MacroTest
	virtual void CreatePpEngine();
	virtual void CreateAllEngine();
	virtual void InitPpEngineShowSpyWnd();
	virtual void StopProtocolParseForReadSoe(BOOL bStop);

public:
	virtual void ReleasePpEngine(const CString &strProgID);
	virtual void ReleasePpEngine();
};

extern CPpEngineBaseAppEx *g_thePpEngineApp;
