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

   //����ͷŵĴ���
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
	//�ڴ���Ӳ����ǿ��ƵĴ���
	return 0;
}

long CVmTmprtrCtrlApp::StopTest()
{
	//�ڴ����ֹͣ���ԵĴ���
	ASSERT (FALSE);
	return 0;
}

long CVmTmprtrCtrlApp::CloseDevice()
{
	//�ڴ���ӹر��豸�Ĵ���
	ASSERT (FALSE);
	return 0;
}

CString CVmTmprtrCtrlApp::GetSearchReport()
{
	//�ڴ���Ӵ���
	return _T("");
}

long CVmTmprtrCtrlApp::FinishTest(long nState)
{
	//�ڴ���Ӵ���
	return 0;
}

long CVmTmprtrCtrlApp::ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter)
{
	//�ڴ���Ӵ���
	return 0;
}

unsigned long CVmTmprtrCtrlApp::StopDevice(void)
{
	//�ڴ���Ӵ���
	return 0;
}

BOOL CVmTmprtrCtrlApp::IsConnectSuccess()
{
	//�ڴ���Ӵ���
	ASSERT (FALSE);
	return FALSE;
}

BOOL CVmTmprtrCtrlApp::ConnectDeviceExec()
{
BOOL bSucc = FALSE;
	//�ڴ����ConnectDevice�Ĵ���
	ASSERT (FALSE);

    return bSucc;
}

long CVmTmprtrCtrlApp::System_Login()
{
	ASSERT (FALSE);
	return FALSE;
}

