#pragma once

/*
	功能描述：自动测试的管理基类
	自动测试主程序、单机主程序的应用程序App类都从此类派生
	实现：工作任务的管理、测试管理
*/

#include "TestMsgWnd.h"
#include "..\..\Module\Interface\ProtocolEngineInterface.h"

class CTPpEngineBaseApp : public CWinAppEx
{
public:
	CTPpEngineBaseApp();
	virtual ~CTPpEngineBaseApp();


protected:
	CString m_strPpEngineProgID;
	PpEngine::IPpEnginePtr m_pPpEngine;

protected:
	//初始化方法
	long InitPpEngineBaseApp();
	long ExitTPpEngineBaseApp();

public:
	PpEngine::IPpEnginePtr GetPpEngine(const CString &strProgID);
	void ReleasePpEngine();
	virtual void CreatePpEngine();


};
