#include "stdafx.h"
#include"VmTmprtrCtrlApp.h"

#include "../../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../../../../Module/API/GlobalConfigApi.h"

#include "../../../../SttStudio/Module/SmartTestInterface/SttMacroTestMsgRcvInterface_Win.h"


CVmTmprtrCtrlApp::CVmTmprtrCtrlApp()
{

}


CVmTmprtrCtrlApp::~CVmTmprtrCtrlApp(void)
{

}

void CVmTmprtrCtrlApp::Release()
{
   CVmXImpBase::Release();

   //添加释放的代码
}

CString CVmTmprtrCtrlApp::GetConfig()
{
	return _T("");
}

long CVmTmprtrCtrlApp::SetConfig(CSttTestAppCfg *pSttTestAppCfg)
{
	return 0;
}

long CVmTmprtrCtrlApp::SetConfig(const CString & bstrConfig)
{
	return 0;
}

long CVmTmprtrCtrlApp::TestExec()
{
	//在此添加测试仪控制的代码
	return 0;
}

long CVmTmprtrCtrlApp::StopTest()
{
	//在此添加停止测试的代码
	ASSERT (FALSE);
	return 0;
}

long CVmTmprtrCtrlApp::CloseDevice()
{
	//在此添加关闭设备的代码
	ASSERT (FALSE);
	return 0;
}

CString CVmTmprtrCtrlApp::GetSearchReport()
{
	//在此添加代码
	return _T("");
}

long CVmTmprtrCtrlApp::FinishTest(long nState)
{
	//在此添加代码
	return 0;
}

long CVmTmprtrCtrlApp::ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter)
{
	//在此添加代码
	return 0;
}

unsigned long CVmTmprtrCtrlApp::StopDevice(void)
{
	//在此添加代码
	return 0;
}

BOOL CVmTmprtrCtrlApp::IsConnectSuccess()
{
	//在此添加代码
	ASSERT (FALSE);
	return FALSE;
}

BOOL CVmTmprtrCtrlApp::ConnectDeviceExec()
{
BOOL bSucc = FALSE;
	//在此添加ConnectDevice的代码
	ASSERT (FALSE);

    return bSucc;
}

long CVmTmprtrCtrlApp::System_Login()
{
	ASSERT (FALSE);
	return FALSE;
}

