#include "stdafx.h"
#include"VmXImpBase.h"

#include "../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../../../Module/API/GlobalConfigApi.h"

#include "../../../SttStudio/Module/SmartTestInterface/SttMacroTestMsgRcvInterface_Win.h"
#include "Simpac/SimpacTestAscii2.h"
#include "../../../SttStudio/Module/SttCmd/SttTestCmd.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

CVmXImpBaseMsgWnd::CVmXImpBaseMsgWnd()
{
	m_pVmXImp = NULL;
}

CVmXImpBaseMsgWnd::~CVmXImpBaseMsgWnd()
{
}

void CVmXImpBaseMsgWnd::CreateVmXImpBaseMsgWnd(CVmXImpBase *pInterface)
{
	static int nIndex = 0;
	CString strWndID;
	strWndID.Format(_T("_Vm_Proto_Imp_Wnd_%d"),nIndex++);

	m_pVmXImp = pInterface;

	CreateEx(0, AfxRegisterWndClass(0), strWndID, WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
}

BEGIN_MESSAGE_MAP(CVmXImpBaseMsgWnd, CWnd)
	ON_WM_TIMER()
	//ON_MESSAGE(XCOMM_WND_MSG, &CVmXImpBaseMsgWnd::OnElectricTestMsg)
	ON_MESSAGE(STT_VMSERVER_MSG_RCVCMD, &CVmXImpBaseMsgWnd::OnVmServerCmdRcv)
	ON_MESSAGE(STT_MACROTEST_MSG_CONNECT, &CVmXImpBaseMsgWnd::OnMacroTestMsgConnect)
	ON_MESSAGE(STT_MACROTEST_MSG_BEGIN, &CVmXImpBaseMsgWnd::OnMacroTestMsgBegin)
	ON_MESSAGE(STT_MACROTEST_MSG_FINISH, &CVmXImpBaseMsgWnd::OnMacroTestMsgFinish)
	ON_MESSAGE(STT_MACROTEST_MSG_STOP, &CVmXImpBaseMsgWnd::OnMacroTestMsgStop)
	ON_MESSAGE(STT_MACROTEST_MSG_EXCEPTION, &CVmXImpBaseMsgWnd::OnMacroTestMsgException)
	ON_MESSAGE(STT_MACROTEST_MSG_EVENT, &CVmXImpBaseMsgWnd::OnMacroTestMsgEvent)
	ON_MESSAGE(STT_MACROTEST_MSG_RTDATA, &CVmXImpBaseMsgWnd::OnMacroTestMsgRtData)
	ON_MESSAGE(STT_MACROTEST_MSG_CONFIGDEVICE, &CVmXImpBaseMsgWnd::OnConfigDevice)

END_MESSAGE_MAP()


LRESULT CVmXImpBaseMsgWnd::OnVmServerCmdRcv(WPARAM wParam, LPARAM lParam)
{
	if (m_pVmXImp != NULL)
	{
		m_pVmXImp->OnVmServerCmdRcv(wParam,lParam);
	}

	return 0;
}

LRESULT CVmXImpBaseMsgWnd::OnElectricTestMsg(WPARAM wParam, LPARAM lParam)
{
	if (m_pVmXImp != NULL)
	{
		m_pVmXImp->OnElectricTestMsg(wParam,lParam);
	}

	return 0;
}

void CVmXImpBaseMsgWnd::OnTimer(UINT nIDEvent)
{
	if (m_pVmXImp != NULL)
	{
		m_pVmXImp->OnXTimer(nIDEvent);
	}	
}

LRESULT CVmXImpBaseMsgWnd::OnMacroTestMsgConnect(WPARAM wParam, LPARAM lParam)
{
	m_pVmXImp->OnMacroTestMsgConnect(wParam, lParam);
	return 0;
}

LRESULT CVmXImpBaseMsgWnd::OnMacroTestMsgBegin(WPARAM wParam, LPARAM lParam)
{
	m_pVmXImp->OnMacroTestMsgBegin(wParam, lParam);
	return 0;
}

LRESULT CVmXImpBaseMsgWnd::OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam)
{
	m_pVmXImp->OnMacroTestMsgFinish(wParam, lParam);
	return 0;
}

LRESULT CVmXImpBaseMsgWnd::OnMacroTestMsgStop(WPARAM wParam, LPARAM lParam)
{
	m_pVmXImp->OnMacroTestMsgStop(wParam, lParam);
	return 0;
}

LRESULT CVmXImpBaseMsgWnd::OnMacroTestMsgException(WPARAM wParam, LPARAM lParam)
{
	m_pVmXImp->OnMacroTestMsgException(wParam, lParam);
	return 0;
}

LRESULT CVmXImpBaseMsgWnd::OnMacroTestMsgEvent(WPARAM wParam, LPARAM lParam)
{
	m_pVmXImp->OnMacroTestMsgEvent(wParam, lParam);
	return 0;
}

LRESULT CVmXImpBaseMsgWnd::OnMacroTestMsgRtData(WPARAM wParam, LPARAM lParam)
{
	m_pVmXImp->OnMacroTestMsgRtData(wParam, lParam);
	return 0;
}

LRESULT CVmXImpBaseMsgWnd::OnConfigDevice(WPARAM wParam, LPARAM lParam)
{
	m_pVmXImp->OnConfigDevice(wParam, lParam);
	return 0;
}
//////////////////////////////////////////////////////////////////////////
CVmXImpBase::CVmXImpBase()
{
    m_oReportBuffer.SetBufferLength(256000);
    m_oReportBuffer.AllocBuffer(0);

	//CSttCmdOverTimeTool::AttachCmdOverTimeMsgRcv(this);

	m_pVmImpMsgWnd = new CVmXImpBaseMsgWnd();
	m_pVmImpMsgWnd->CreateVmXImpBaseMsgWnd(this);
	m_pSttMacroTestEventServerInterface = NULL;
	m_pCmmOptrInterface = NULL;
}


CVmXImpBase::~CVmXImpBase(void)
{
	m_oTestMacroParas.RemoveAll();
	//CSttCmdOverTimeTool::AttachCmdOverTimeMsgRcv(NULL);

	m_pVmImpMsgWnd->DestroyWindow();
	delete m_pVmImpMsgWnd;
}

long CVmXImpBase::TestExec(CDataGroup *pParas)
{
	ASSERT( FALSE );
	return 0;
}

BOOL CVmXImpBase::ConnectDeviceExec()
{
	ASSERT( FALSE );
	return FALSE;
}


BOOL CVmXImpBase::ConnectDevice()
{
	if (IsConnectSuccess())
	{
		return TRUE;
	}

	//在此添加ConnectDevice的代码
	return ConnectDeviceExec();
}

// 
// void CVmXImpBase::Release()
// {
// 
//     CMacroTestInterface::Release();
// }

void CVmXImpBase::OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	PostTestWndMsg(MTMSG_CommError, 0);
}

/**********************
<group>
	<data name="" id="DeviceSN" value="1921681112"/>
	<group name="" id="RTDATA">
		<data name="" id="RealTemp" value="23.15"/>
		<data name="" id="SetTemp" value="22.00"/>
	</group>
</group>
****************************/
void CVmXImpBase::SendRtData()
{

}
// 
// CString CVmXImpBase::GetConfig()
// {
// 	return _T("");
// }
// 
// long CVmXImpBase::SetConfig(CSttTestAppCfg *pSttTestAppCfg)
// {
// 	return 0;
// 	return 0;
// }
// 
// long CVmXImpBase::SetConfig(const CString & bstrConfig)
// {
// 	return 0;
// }
// 
// void CVmXImpBase::SetConfig(CDataGroup *pAppConfig)
// {
// 	ASSERT (FALSE);
// }
/*

long CVmXImpBase::Test(const CString & strMacroID, const CString & strParameter)
{
    //m_strReport.Empty();
    //2020-11-6  lijunqing
    m_oReportBuffer.SeekToHead();
    m_oReportBuffer.StringEnd();

	if (!ConnectDevice())
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.."), strMacroID.GetString(), strParameter.GetString());

        return -1;
	}

	m_oTestMacroParas.DeleteAll();
	SetParameter(m_pTestMacro, m_oTestMacroParas, strParameter);

	long nRet = STT_CMD_ExecStatus_NULL;

//测试执行代码，在具体实现对象中实现
	TestExec(&m_oTestMacroParas);
	

    CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += strMacroID;
	strFile += _T(".xml");
	m_oTestMacroParas.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	return 0;
}
*/

/*
CString CVmXImpBase::GetReport()
{
	GetResultFromTestMacro();

    CString strReport;
    m_oReportBuffer.StringEnd();
    strReport = m_oReportBuffer.GetBuffer();

    return strReport;
}


long CVmXImpBase::CloseDevice()
{
	ASSERT (FALSE);
	return 0;
}

CString CVmXImpBase::GetSearchReport()
{
	return _T("");
}

long CVmXImpBase::FinishTest(long nState)
{
	return 0;
}

long CVmXImpBase::ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter)
{
	return 0;
}

unsigned long CVmXImpBase::GetExternMsgRcvWnd()
{
	return 0;
}

unsigned long CVmXImpBase::GetExternMsgID()
{
	return 0;
}

unsigned long CVmXImpBase::StopDevice(void)
{
	return 0;
}

void CVmXImpBase::SetParameter(CTestMacro *pTestMacro, CDataGroup &oDataGroup, const CString & strParameter)
{
	CEquationBuffer *pEquation = new CEquationBuffer;
	pEquation->InitBuffer(strParameter);
	pTestMacro->GetTestMacroParas_Fault_CloneEx(&oDataGroup);

	oDataGroup.Parser(pEquation);
	delete pEquation;
}

long CVmXImpBase::System_Login()
{
	ASSERT (FALSE);
	return FALSE;
}
*/

void CVmXImpBase::PostTestWndMsg(WPARAM wParam, LPARAM lParam)
{
	if (!::IsWindow(((HWND)m_hMsgWnd)))
	{
		return;
	}

	::PostMessage((HWND)m_hMsgWnd, m_nMsgID, wParam, lParam);
}

//测试功能事件接口
/*
void CVmXImpBase::OnTestStarted(const CString &strMacroID, CDataGroup *pParas)
{
	PostTestWndMsg(MTMSG_TestBegin, 0);
}

void CVmXImpBase::OnTestStoped(const CString &strMacroID, CDataGroup *pParas)
{
	
}

void CVmXImpBase::OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{
	AppendReport_ResultEx(pResults);

	PostTestWndMsg(MTMSG_TestFinished, 0);
}

void CVmXImpBase::OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{

}
*/

/*
<sys-state name="" id="" ldName="0" LDdesc="1970-01-01 01:05:58" scl_gcb_confRev="" scl_gcb_APPID="EVENT" scl_gse_APPID="test-cmd">
	<paras name="" id="">
		<data name="ExecStatus" id="ExecStatus" data-type="string" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<group name="Event" id="Event" data-type="Event" value="">
			<data name="绝对时间" id="Time" data-type="time" value="993747952.809979558" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="相对时间" id="RealTime" data-type="double" value="19.809979558" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="Bin001" id="Bin001" data-type="long" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="Event" id="Event" data-type="Event" value="">
			<data name="绝对时间" id="Time" data-type="time" value="993747952.810141921" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="相对时间" id="RealTime" data-type="double" value="19.810141921" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="Bin001" id="Bin001" data-type="long" value="1" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
		<group name="Event" id="Event" data-type="Event" value="">
			<data name="绝对时间" id="Time" data-type="time" value="993747952.810370088" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="相对时间" id="RealTime" data-type="double" value="19.810370088" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			<data name="Bin001" id="Bin001" data-type="long" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</paras>
</sys-state>
*/
//每一个sys-state$paras$group都会调用一次OnTestState
/*
void CVmXImpBase::OnTestState(const CString &strMacroID, CDataGroup *pParas)
{
	//shaolei 20210624 新增存文件功能
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("OnTestState");
	strFile += _T(".xml");

	pParas->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	//shaolei 20210627
	POS pos = pParas->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmData *pTime = (CDvmData *)pParas->FindByID(_T("Time"));
	CDvmData *pRealTime = (CDvmData *)pParas->FindByID(_T("RealTime"));

	while (pos != NULL)
	{
		pData = (CDvmData *)pParas->GetNext(pos);

		if (pData->m_strID == _T("Time") || pData->m_strID == _T("RealTime"))
		{
			continue;
		}

		m_oReportBuffer.AppendEquation(pData->m_strID.GetString(), pData->m_strValue.GetString());

		CString strID;

		if (pTime != NULL)
		{
			strID.Format(_T("%s$%s"), pData->m_strID, pTime->m_strID);
			m_oReportBuffer.AppendEquation(strID.GetString(), pTime->m_strValue.GetString());
		}

		if (pRealTime != NULL)
		{
			strID.Format(_T("%s$%s"), pData->m_strID, pRealTime->m_strID);
			m_oReportBuffer.AppendEquation(strID.GetString(), pRealTime->m_strValue.GetString());
		}
	}
}

void CVmXImpBase::OnReport(CDataGroup *pParas)
{

}

long CVmXImpBase::OnAts_Stop(CDataGroup *pParas)
{
	return 0;
}*/
// 
// void CVmXImpBase::SetConfig_TestApp()
// {
// 	if (m_pSttTestApp == NULL)
// 	{
// 		return;
// 	}
// 
// 	SetConfig(m_pSttTestApp);
// }
/*

void CVmXImpBase::GetParaIDPath(CString &strPath, CDvmData *pData)
{
	strPath.Empty();
	CExBaseObject *pParent = pData;
	CString strTemp;

	while (pParent != NULL)
	{
		if (pParent->m_strID.GetLength() == 0)
		{
			break;
		}

		strTemp.Format(_T("%s$"), pParent->m_strID);
		strPath = strTemp + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent->GetClassID() != STTCMDCLASSID_CSTTRESULTS)
		{
			break;
		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - 1;
		strPath = strPath.Left(nLen);
	}
}

void CVmXImpBase::AppendReport_ResultEx(CDataGroup *pRsltGroup)
{
	CDvmData *pData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	POS pos = pRsltGroup->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pRsltGroup->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pGroup = (CDataGroup *)pObj;
			AppendReport_ResultEx(pGroup);
			continue;
		}

		pData = (CDvmData *)pObj;
		CString strID;
		GetParaIDPath(strID, pData);
		m_oReportBuffer.AppendEquation(strID.GetString(), pData->m_strValue.GetString());
	}
}

void CVmXImpBase::GetResultFromTestMacro()
{
	CTmResultParas *pResults = (CTmResultParas *)m_pTestMacro->GetResults();
	CTmResultParasEx *pResultsEx = m_pTestMacro->GetResultsEx();

	POS pos = pResults->GetHeadPosition();
	while (pos != NULL)
	{
		CShortData *pData = (CShortData*)pResults->GetNext(pos);
		m_oReportBuffer.AppendEquation(pData->m_strID.GetString(), pData->m_strValue.GetString());
	}

	//AppendReport_ResultEx(pResultsEx);
}
*/

void CVmXImpBase::OnXTimer(DWORD dwTimerID)
{
	
}

LRESULT CVmXImpBase::OnVmServerCmdRcv(WPARAM wParam, LPARAM lParam)
{
	CSttCmmOptrInterface *pCmmOptrInterface = (CSttCmmOptrInterface *)wParam;

	//shaolei 2021-9-26 记录pCmmOptrInterface用于发送测试结束事件
	m_pCmmOptrInterface = pCmmOptrInterface;
	CXObjectRefDriver oDriver((CSttTestCmd*)lParam);
	CSttTestCmd *pTestCmd = (CSttTestCmd*)oDriver.GetXObjectRef();
	pTestCmd->SetSttCmmOptrInterface(pCmmOptrInterface);

	if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_ConfigDevice)
	{
		TestCmd_ConfigDevice(pCmmOptrInterface, pTestCmd->GetSttParas());
	}
	else if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_ConnectDevice)
	{
		TestCmd_ConnectDevice(pCmmOptrInterface, pTestCmd->GetSttParas());
	}
	else if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_StartTest)
	{
		TestCmd_StartTest(pCmmOptrInterface, pTestCmd->GetSttMacro());
	}
	else if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_StopTest)
	{
		TestCmd_StopTest(pCmmOptrInterface, pTestCmd->GetSttParas());
	}
	else if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_CloseDevice)
	{
		TestCmd_CloseDevice(pCmmOptrInterface, pTestCmd->GetSttParas());
	}


	return 0;
}

LRESULT CVmXImpBase::OnElectricTestMsg(WPARAM wParam, LPARAM lParam)
{

	return 0;
}

long CVmXImpBase::StopTest()
{
	//在此添加停止测试的代码
	ASSERT (FALSE);
	return 0;
}

//CSttMacroTestServerInterface

void CVmXImpBase::PostVmServerRcvCmd(CSttCmmOptrInterface *pCmmOptrInterface, CSttTestCmd *pTestCmd)
{
	m_pVmImpMsgWnd->PostMessage(STT_VMSERVER_MSG_RCVCMD, (WPARAM)pCmmOptrInterface, (LPARAM)pTestCmd);
}

long CVmXImpBase::SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID)
{
	m_hMsgWnd = hMainWnd;
	m_nMsgID = nMsgID;

	return 0;
}

long CVmXImpBase::TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	return 0;
}

long CVmXImpBase::TestCmd_ConnectDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	TestCmd_ConfigDevice(pSttCmmOptrInterface, pSttParas);

	return 0;
}

long CVmXImpBase::TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	return 0;
}

long CVmXImpBase::TestCmd_SetParameter(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro)
{
	return 0;
}

long CVmXImpBase::TestCmd_UpdateParameter(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro)
{
	return 0;
}

long CVmXImpBase::TestCmd_StartTest(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro)
{
	//m_strReport.Empty();
	//2020-11-6  lijunqing

	CSttSysState oSysState;
	m_pSttMacroTestEventServerInterface->OnTestState_Reply(pSttCmmOptrInterface, &oSysState, STT_CMD_ExecStatus_ACK, STT_CMD_TYPE_ATS_StartTest, STT_CMD_SYSSTATE_TEST);
	m_oReportBuffer.SeekToHead();
	m_oReportBuffer.StringEnd();

	if (!ConnectDevice())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.."));
		CSttSysState oSysStateFail;
		m_pSttMacroTestEventServerInterface->OnTestState_Reply(pSttCmmOptrInterface, &oSysStateFail, STT_CMD_ExecStatus_FAILURE, STT_CMD_TYPE_ATS_StartTest, STT_CMD_SYSSTATE_TEST);
		return -1;
	}

	//yzj 2021-9-26 
	//执行完成后已经被delete,此处多次delete,需要做的是清空而非析构
	//m_oTestMacroParas.DeleteAll();
	m_oTestMacroParas.RemoveAll();
	CSttParas *pSttParas = pSttMacro->GetParas();
	m_oTestMacroParas.Append(pSttParas);
	m_strCurrTestMacroID = pSttMacro->m_strID;
	long nRet = STT_CMD_ExecStatus_NULL;

	//测试执行代码，在具体实现对象中实现
	long nRes = TestExec(&m_oTestMacroParas);

	CSttSysState oSysState2;
	m_pSttMacroTestEventServerInterface->OnTestState_Reply(pSttCmmOptrInterface, &oSysState2, STT_CMD_ExecStatus_SUCCESS, STT_CMD_TYPE_ATS_StartTest, STT_CMD_SYSSTATE_TEST);
	m_pSttMacroTestEventServerInterface->OnTestEvent_TestStarted(pSttCmmOptrInterface, NULL);

	return 0;
}

long CVmXImpBase::TestCmd_StopTest(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	CSttSysState oSysState;
	m_pSttMacroTestEventServerInterface->OnTestState_Reply(pSttCmmOptrInterface, &oSysState, STT_CMD_ExecStatus_ACK, STT_CMD_TYPE_ATS_StopTest, STT_CMD_SYSSTATE_TEST);
	StopTest();
	return 0;
}

long CVmXImpBase::TestCmd_GetReport(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro)
{
	return 0;
}

long CVmXImpBase::TestCmd_GetSystemState(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	return 0;
}

long CVmXImpBase::TestCmd_TriggerTest(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	return 0;
}

long CVmXImpBase::TestCmd_FinishInputData(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	return 0;
}

BOOL CVmXImpBase::IsTestFinished(DWORD dwPara)
{
	return 0;
}

BOOL CVmXImpBase::IsConnectSuccess()
{
	ASSERT (FALSE);
	return FALSE;
}

long CVmXImpBase::GetEvents(CDataGroup *pSttParas)
{
	return 0;
}

long CVmXImpBase::GetRtDatas(CDataGroup *pSttParas)
{
	return 0;
}

long CVmXImpBase::GetExceptions(CDataGroup *pSttParas)
{
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//消息事件处理
void CVmXImpBase::OnMacroTestMsgConnect(WPARAM wParam, LPARAM lParam)
{

}

void CVmXImpBase::OnMacroTestMsgBegin(WPARAM wParam, LPARAM lParam)
{

}

void CVmXImpBase::OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam)
{

}

void CVmXImpBase::OnMacroTestMsgStop(WPARAM wParam, LPARAM lParam)
{

}

void CVmXImpBase::OnMacroTestMsgException(WPARAM wParam, LPARAM lParam)
{

}

void CVmXImpBase::OnMacroTestMsgEvent(WPARAM wParam, LPARAM lParam)
{

}

void CVmXImpBase::OnMacroTestMsgRtData(WPARAM wParam, LPARAM lParam)
{
	CDataGroup oParas;
	GetRtDatas(&oParas);
	
	m_pSttMacroTestEventServerInterface->OnTestState_Report(NULL, &oParas);
}

void CVmXImpBase::OnConfigDevice(WPARAM wParam, LPARAM lParam)
{

}