#pragma once

/*
	功能描述：测试控制对象；管理一个测试的全部过程
*/

#include "..\..\Module\TestMacro\TestMacroInterface.h"
#include "..\..\Module\Interface\ProtocolEngineInterface.h"
#include "GuideBook\GuideBookInterface.h"
#include "GuideBookFileMngr\GuideBookFileMngr.h"
#include "GuideBook\GuideBookDefine.h"

#include "GuideBook\GuideBookInterface.h"
#include "TaskMngr/TestProject.h"
#include "TCtrlMsgRcvInterface.h"

#include "Interface\MacroTestEngine.h"

#include "UITestItem/UISafetyTest.h"
#include "GuideBook/ReportMap/WordReport/WordRptFill.h"
#include "UITestItem/SysParaEditDlg.h"
#include "UITestItem/UICommCmdDlg.h"
#include "UITestItem/UICommCmdViewDlg.h"
#include "UITestItem/TestItemViewGrid.h"

class CRptFillInterface;
class CTestControlCommCmdWnd;


class CTestControlCommCmd : public CBaseList
{
protected:
	//与通讯引擎通讯的接口
	class CPpEngineDevice : public CBaseObject
	{
	public:
		CString m_strDeviceID;
		PpEngine::IDevicePtr m_oPpDevice;
		BOOL m_bPpDeviceConnectSucc;
	};
	
public:
	CTestControlCommCmd();
	virtual ~CTestControlCommCmd();

public:
	PpEngine::IDevicePtr m_oPpDevice;
	PpEngine::IDevicePtr m_oPpDeviceEx;
	BOOL m_bPpDeviceConnectSucc;

	PpEngine::IDevicePtr GetDevicePtr(CCommCmd* pItem);
	PpEngine::IDevicePtr GetDevicePtr();

//////////////////////////////////////////////////////////////////////////
//通讯命令的处理
public:
	void CreatePpEngineDevice();
	BOOL IsAllDeviceCreated();
	
	//通讯命令处理完成
	BOOL IsCommCmdFinished();
	
	//执行项目的测试：通讯命令通讯迁延时
	void ExcuteCommCmd(CCommCmd* pItem);

	LRESULT OnCommCommandMsg(WPARAM wParam, LPARAM lParam);
	LRESULT OnEngineSystemMessage(WPARAM wParam, LPARAM lParam);
			
private:
	//执行过程
	CString m_strProcedureID;
	CString m_strDatasetPath;
	void RunProcedure(const CString &bstrProcedureID, const CString &bstrDatasetPath, WPARAM wParam, LPARAM lParam);
	void UnRegisterProcedureMsg(WPARAM wParam, LPARAM lParam);

};

