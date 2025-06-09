#include "stdafx.h"
#include "SttSmartTest.h"
#include "SttNativeTestCtrlCntr.h"
#include "../Engine/SttServerNativeConfig.h"
#include "../Engine/SttNativeTestEngine.h"

#include "../../../AutoTest/Module/SmartTestRpcApi.h"
#include "../../../AutoTest/Module/GuideBook/GuideBookStruDscTool.h"
#include "../SttCmd/GuideBook/SttCmdGuideBookTransTool.h"
#include "../../../AutoTest/Module/SmartTestDefineInterface.h"
#include "../../../AutoTest/Module/TCtrlCntrConfig.h"
#include "../../../AutoTest/Module/AtsMes/AtsMesTestDefine.h"
#ifndef _PSX_IDE_QT_
#include "../../../AutoTest/Module/TestControl/TestControlMdvMgrp.h"
#include "../../../AutoTest/Module/TestMacroRptTemplate/RptTemplate_GenXmlTool.h"
#include "../../../AutoTest/Module/TestMacroRptTemplate/RptTemplate_GenDocTool.h"
#endif
#include "../SttSystemConfig/SttSystemConfigGlobal.h"

#ifdef _PSX_IDE_QT_
#include "SttSmartTestWnd_Linux.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttSmartTest* CSttSmartTest::g_pSttSmartTest = NULL;
long CSttSmartTest::g_nSttSmartTestRef = 0;

//shaolei  2023-2-21对于安全措施、系统参数编辑项目，是否显示测试对话框
CString g_strSmartTestRunMode = SmartTest_Run_Mode_Local;  //0-Local；

//GennrateItems要在上一次模板的基础上生成测试项目，不能用临时变量进行生成，因此定义一个全局对象、
//shaolei 2022-1-12
CSttGuideBookGenServer g_oSttGuideBookGenServer; 

//shaolei 2023-10-08
CSttSmartTest *g_theSttSmartTest = NULL;

extern CDataGroup *g_pGlobalDatas_Gb_CalParaExp;

CSttSmartTest::CSttSmartTest()
{
    m_bIsAtsLib = FALSE;
	m_bPpEngineReleased = FALSE;
    m_bFirstInit = TRUE;
	m_bTestCreated = FALSE;
	m_pTestControl = NULL;
	m_pSttMainFrame = NULL;
	CSttSystemConfigXmlRWKeys::Create();
	g_oSttGuideBookGenServer.InitGbGenSysPath(_T(""));  //2022-3-29  lijunqing SttTestMainCore模式

#ifndef _PSX_IDE_QT_
	CTestMacroRptTemplateXmlRWKeys::Create();
#endif

	m_nStartTestAfterCreate = 0;
}

CSttSmartTest::~CSttSmartTest()
{
#ifndef _PSX_IDE_QT_
	CTestMacroRptTemplateXmlRWKeys::Release();
#endif
    FreeTestControl();
	CSttSystemConfigXmlRWKeys::Release();
}

//CSttSmartTest* CSttSmartTest::Create()
//{
//	g_nSttSmartTestRef++;

//	if (g_nSttSmartTestRef == 1)
//	{
//		g_pSttSmartTest = new CSttSmartTest();
//		g_theSttSmartTest = g_pSttSmartTest;
//        CSttSmartTest *p = g_theSttSmartTest;
//        p = g_theSttSmartTest;
//	}

//	return g_pSttSmartTest;
//}

//void CSttSmartTest::Release()
//{
//	g_nSttSmartTestRef--;

//	if (g_nSttSmartTestRef == 0)
//	{
//		delete g_pSttSmartTest;
//		g_pSttSmartTest = NULL;
//		g_theSttSmartTest = NULL;
//	}
//}

void CSttSmartTest::FreeTestControl(BOOL bResetTestControl)
{
    if(m_bIsAtsLib)
    {
        delete m_pTestControl;
        m_pTestControl = NULL;
        return;
    }

     if (m_pTestControl != NULL)
    {
		if (m_pSttMainFrame != NULL)
		{
			m_pSttMainFrame->SendMessage(WM_STT_FREETESTCONTROL, (WPARAM)this, bResetTestControl);
		}
		else
		{
			delete m_pTestControl;
			m_pTestControl = NULL;
		}
    }
}

void CSttSmartTest::FreeTestControlEx(BOOL bDelete)
{
	if (m_pTestControl != NULL)
	{
		if (bDelete)
		{
			delete m_pTestControl;
		}

		m_pTestControl = NULL;
	}
}

void CSttSmartTest::StartTestAfterCreate()
{
	if (m_nStartTestAfterCreate == 0)
	{
		return;
	}

    if(m_bIsAtsLib)
    {
        m_pTestControl->TestFrom(-1);
        return;
    }

	if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_BEGINETEST, (WPARAM)m_pTestControl, 0);
	}
	else
	{
		// 		m_pTestControl->m_pGuideBook->m_nIndex = 0;
		m_pTestControl->TestFrom(-1);
	}
}

long CSttSmartTest::BeforeCreateTest(const CString &strGbXmlFile, const CString &strTestProjectName)
{
    if (m_pTestControl == NULL)
    {
        return CREATE_TEST_CREATE_NEW;
    }

    CString strGbXmlFile2 = ParseFileName(strGbXmlFile);
    CString strTempPrjName = m_pTestControl->GetGbBinaryFileName();
    CString strTempGbxml = GetPathFileNameFromFilePathName(m_pTestControl->m_pGuideBook->m_strGbXmlFile);

	//2022-6-27  lijunqing 如果当前测试为空，则创建新的测试
	if (strTempPrjName.GetLength() == 0 || strTempGbxml.GetLength() == 0)
	{
		return CREATE_TEST_CREATE_NEW;
	}

    strTempGbxml = ParseFileName(strTempGbxml);
    long nRet1 = strTempPrjName.CompareNoCase(strTestProjectName);
    long nRet2 = strTempGbxml.CompareNoCase(strGbXmlFile2);

    if ((nRet1 == 0) &&  (nRet2  == 0) )
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Test is exist: [%s]  [%s]"), strGbXmlFile.GetString(), strTestProjectName.GetString());
        return CREATE_TEST_CURR_EXIST_SAME;
    }

    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Create Filed, has an other test: [%s]  [%s]"), strGbXmlFile.GetString(), strTestProjectName.GetString());

    return CREATE_TEST_CURR_EXIST_NOT_SAME;
}

BOOL CSttSmartTest::IsNowTesting()
{
    if(m_pTestControl == NULL)
        return FALSE;

    return m_pTestControl->IsNowTesting();
}

long CSttSmartTest::UpdateParameter(CDataGroup *pParas)
{
    if(m_pTestControl == NULL)
        return 1;

   return m_pTestControl->UpdateParameter(pParas);
}

BOOL CSttSmartTest::IsInternational()
{
	return g_oSttGuideBookGenServer.IsInternational();
}

CTestControlBase* CSttSmartTest::GetTestControl()
{
    return m_pTestControl;
}

CGuideBook* CSttSmartTest::GetGuideBook()
{
    if (m_pTestControl == NULL)
    {
        return NULL;
    }

    return m_pTestControl->m_pGuideBook;
}

CDvmDataset* CSttSmartTest::GetGlobalDatas()
{
	return g_oSttGuideBookGenServer.GetGlobalDatas();
}

CExBaseList* CSttSmartTest::GetSysPara()
{
	return g_oSttGuideBookGenServer.GetSysPara();
}

BOOL CSttSmartTest::IsTestCreated()
{
    return m_pTestControl != NULL;
}

CString CSttSmartTest::GetProjectName()
{
    if (m_pTestControl != NULL)
    {
        return m_pTestControl->GetProjectName();
    }
    else
    {
        return _T("");
    }
}

void CSttSmartTest::GetReadDeviceParameter(CSttParas *pParas)
{
// 	CVmSttMacroTest *pInterface = GetMacroTestInterface();
// 
// 	if (pInterface == NULL)
// 	{
// 		return;
// 	}

	pParas->AppendCloneEx2(g_oReadDeviceParameter);
	//pInterface->m_oReadDeviceParameter.RemoveAll();
}

CString CSttSmartTest::ValidFileName(const CString &strPath, const CString &strFileName, const CString &strProfix)
{
	CString strLocalPath;

	if (strPath.Right(1) == _T("/"))
	{
		strLocalPath = strPath + strFileName;
	}
	else if (strPath.Right(1) == _T("\\"))
	{
		strLocalPath = strPath + strFileName;
	}
	else
	{
		strLocalPath = strPath + _T("/") + strFileName;
	}

	strLocalPath = ChangeFilePostfix(strLocalPath, strProfix);
	return strLocalPath;
}

//界面交互
long CSttSmartTest::OnException(long nError,const CString &strError, CExBaseObject *pTestControl)
{
    //atsrpc_OnTestAppEvent  已经发送了事件，此处只显示消息 lijunqing  2020-11-24
    CLogPrint::LogString(XLOGLEVEL_ERROR, strError);

    return 0;
}

long CSttSmartTest::OnConnectSuccess(CExBaseObject *pTestControl)
{
    //2022-2-12  lijunqing  为测试仪通信通道指定报文转发对象，TestEngine为转发接口实现对象
	CTestControlBase *pTestCtrlBase = (CTestControlBase *)pTestControl;

	if (pTestCtrlBase->m_pMacroTestInterface != NULL)
	{
		pTestCtrlBase->m_pMacroTestInterface->AddPkgDispatchInterface(g_theNativeTestEngine);
	}
    
   //Event msg send in atsrpc_OnTestAppEvent

    return 0;
}

long CSttSmartTest::OnConnectFailed(CExBaseObject *pTestControl)
{
   //Event msg send in atsrpc_OnTestAppEvent

    return 0;
}

long CSttSmartTest::OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop)
{
	//如果是测试结束，则发送当前项目的报告；
	//再发送当前项目的项目状态改变
	//发送进度
	if (pItem == NULL)
	{
		return 0;
	}

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();

	long nState = pItem->GetState();

	//如果是测试结束，则发送当前项目的报告；
	if (nState == TEST_STATE_ELIGIBLE || nState == TEST_STATE_INLEGIBLE
		|| nState == TEST_STATE_SKIP || nState == TEST_STATE_ELIGIBLEEX)
	{
		stt_Return_Ats_Event(pTestControl, pItem, TRUE, TRUE);
	}

	//再发送当前项目的项目状态改变
	stt_Return_Ats_Event(pTestControl, pItem, SYS_STATE_EVENT_OnItemStateChanged);

	//发送大项的状态改变
	stt_Return_Ats_ParentItem_StateChanged(pTestControl, pItem);

	//发送进度
	stt_Return_Ats_Event_Process(pTestControl, pItem);

    return 0;
}

/*
<sys-state name="" id="ItemStateChanged" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data id="DeviceSN" data-type="long" value="0" unit=""/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
		<data id="ItemIndex" data-type="long" value="2" unit=""/>
		<data id="ItemPath" data-type="string" value="MacroTest1" unit=""/>
		<data id="State" data-type="string" value="TESTING" unit=""/>
		<group name="" id="SearchLine">
			<data name="" id="x-b" value="" />
			<data name="" id="y-b" value="" />
			<data name="" id="x-e" value="" />
			<data name="" id="y-e" value="" />
			<data name="" id="x-set" value="" />
			<data name="" id="y-set" value="" />
			<data name="" id="x-act" value="" />
			<data name="" id="y-act" value="" />
			<data name="" id="flag-act" value="" />
			<data name="" id="search-x-b" value="" />
			<data name="" id="search-y-b" value="" />
			<data name="" id="search-actb" value="" />
			<data name="" id="search-x-e" value="" />
			<data name="" id="search-y-e" value="" />
			<data name="" id="search-acte" value="" />
			<data name="" id="search-x-c" value="" />
			<data name="" id="search-y-c" value="" />
		</group>
	</paras>
</sys-state>
*/
long CSttSmartTest::OnCurrCharItemStateChanged(CGbItemBase* pItem, CExBaseObject *pObj)
{
	CMacroCharItems *pMacroCharItems = (CMacroCharItems*)(pItem->GetParent());
	CMacroTest *pMacroTest = (CMacroTest *)pItem;
	//在自动测试端，已经做了计算，此处可以直接获取
	CMacroCharItemLineDef *pMacroCharItemLineDef = pMacroCharItems->m_pItemLineDef;
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();

	CSttSysState oSysState;
	CSttParas *pParas = oSysState.GetSttParas();
	oSysState.SetEvent();
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
	oSysState.m_strID = SYS_STATE_EVENT_OnItemStateChanged;

	CDvmDataset oDvmDataset;
	stt_Ats_InitSttStateDatas(&oDvmDataset, pTestControl, pItem);
	pParas->AppendCloneEx(oDvmDataset);
	CDataGroup *pSearchLine = pParas->AddNewGroup(_T(""), STT_CMD_PARA_SEARCH_LINE, _T(""));
	pSearchLine->AddNewData(STT_CMD_PARA_XB, pMacroCharItemLineDef->m_fXb);
	pSearchLine->AddNewData(STT_CMD_PARA_YB, pMacroCharItemLineDef->m_fYb);
	pSearchLine->AddNewData(STT_CMD_PARA_XE, pMacroCharItemLineDef->m_fXe);
	pSearchLine->AddNewData(STT_CMD_PARA_YE, pMacroCharItemLineDef->m_fYe);
	pSearchLine->AddNewData(STT_CMD_PARA_XSET, pMacroCharItemLineDef->m_fXset);
	pSearchLine->AddNewData(STT_CMD_PARA_YSET, pMacroCharItemLineDef->m_fYset);
	pSearchLine->AddNewData(STT_CMD_PARA_XACT, pMacroCharItemLineDef->m_fXact);
	pSearchLine->AddNewData(STT_CMD_PARA_YACT, pMacroCharItemLineDef->m_fYact);

	//以下数据通过SearchPointRepot进行更新过
 	pSearchLine->AddNewData(STT_CMD_PARA_FLAGACT, pMacroCharItemLineDef->m_nFlagAct);
	pSearchLine->AddNewData(STT_CMD_PARA_SEARCH_XB, pMacroCharItemLineDef->m_fSearchXb);
	pSearchLine->AddNewData(STT_CMD_PARA_SEARCH_YB, pMacroCharItemLineDef->m_fSearchYb);
	pSearchLine->AddNewData(STT_CMD_PARA_SEARCH_XE, pMacroCharItemLineDef->m_fSearchXe);
	pSearchLine->AddNewData(STT_CMD_PARA_SEARCH_YE, pMacroCharItemLineDef->m_fSearchYe);
	pSearchLine->AddNewData(STT_CMD_PARA_SEARCH_XC, pMacroCharItemLineDef->m_fSearchXc);
	pSearchLine->AddNewData(STT_CMD_PARA_SEARCH_YC, pMacroCharItemLineDef->m_fSearchYc);
	pSearchLine->AddNewData(STT_CMD_PARA_SEARCH_ACTB, pMacroCharItemLineDef->m_nSearchActb);
	pSearchLine->AddNewData(STT_CMD_PARA_SEARCH_ACTE, pMacroCharItemLineDef->m_nSearchActe);

	if (g_theNativeTestEngine != NULL)
	{
		g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

    return 0;
}

long CSttSmartTest::OnStopTest(long nType, CExBaseObject *pTestControl)
{
	CTestControlBase *pTestCtrlBase = (CTestControlBase *)pTestControl;

    //2020-11-23  lijunqing
    if (nType == 1)
    {
		pTestCtrlBase->m_nCurrTestItemIndex = 0;
		pTestCtrlBase->m_pGuideBook->m_nIndex = 0;
        stt_Return_Ats_Event(pTestCtrlBase, NULL, SYS_STATE_EVENT_OnTestFinished);
    }
    else
    {
        stt_Return_Ats_Event(pTestCtrlBase, NULL, SYS_STATE_EVENT_OnTestStoped);

		if (pTestCtrlBase->m_nTestItemIndexBkForAllInlegible > 0)
		{
			//重测结束
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("+++++++++++重测结束，返回重测结束事件++++++++++++++"));
			stt_Return_Ats_Event(pTestCtrlBase, NULL, SYS_STATE_EVENT_OnReTestFinished);
		}
    }

    return 0;
}

void CSttSmartTest::OnTestItemCount(long nCount, CExBaseObject *pTestControl)
{
	CTestControlBase *pTestCtrlBase = (CTestControlBase *)pTestControl;
    stt_Return_Ats_Event_TestItemCount(pTestCtrlBase, nCount);
}

long CSttSmartTest::OnUpdateMeasure(long nData, CExBaseObject *pTestControl)
{
    return 0;
}

BOOL CSttSmartTest::IsRunning(long nType, CExBaseObject *pTestControl)
{
    return FALSE;
}

long CSttSmartTest::HideAllTestItemUI(long nData, CExBaseObject *pTestControl)
{
    return 0;
}

HWND CSttSmartTest::GetFrameHwnd()
{
    return 0;
}


void CSttSmartTest::ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate, BOOL bShow)
{

}

void CSttSmartTest::ShowCharDraw(CExBaseObject *pGbItem, BOOL bShow)
{

}

void CSttSmartTest::LocateItemReport(CExBaseObject *pGbItem)
{

}

void CSttSmartTest::OnExportRptEvent(CExBaseObject *pTestControl, const CString &strEventID)
{
	CTestControlBase *pBase = (CTestControlBase *)pTestControl;
// 	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0, nTotalDevices = 1;
// 	RPC_API_GetTestCtrlAttr(pBase, strTestID, nDeviceIndex, nReportIndex);

	CSttSysState oSysState;
	CSttParas *pParas = oSysState.GetSttParas();
	oSysState.SetEvent();
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
	oSysState.m_strID = SYS_STATE_EVENT_ExportReport;
	//CString strDeviceSN = pBase->m_pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);

	// 	if (pBase->GetParent() != NULL)
	// 	{
	// 		nTotalDevices = pBase->GetCount();
	// 	}

#ifndef _PSX_IDE_QT_
	//计算装置总的数量，总是以主TestControl去计算，故此处通过m_pTestControl而不是形参pTestControl去判断
	if (m_pTestControl->GetTestControlMode() == TESTCONTROLMODE_MDVMGRP)
	{
		CMdvMgrpSpoDeviceMngrTestControl *pMainControl = (CMdvMgrpSpoDeviceMngrTestControl *)m_pTestControl;
		nTotalDevices = pMainControl->m_listMdvMgrpTestControl.GetCount() + 1;
	}
#endif

	pParas->AddNewData(STT_CMD_PARA_EventID, strEventID);
// 	pParas->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);
// 	//pParasReturn->AddNewData(STT_CMD_PARA_ReportIndex, nReportIndex);
// 	pParas->AddNewData(STT_CMD_PARA_BenchSN, m_strBenchSN);
	pParas->AddNewData(STT_CMD_PARA_CurrDevice, nDeviceIndex+1);
	pParas->AddNewData(STT_CMD_PARA_TotalDevices, nTotalDevices);
	stt_Return_Ats_X_AddPatas(pBase, pParas);

	CDataGroup oGrp;
	pBase->GetReportFiles(&oGrp);
	pParas->AppendClone(oGrp);

	if (g_theNativeTestEngine != NULL)
	{
		g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}
}

void CSttSmartTest::EditItemPara(CExBaseObject *pGbItem)
{

}

long CSttSmartTest::OnTestBegin(CExBaseObject *pTestControl)
{
	CTestControlBase *pTestCtrlBase = (CTestControlBase *)pTestControl;
    stt_Return_Ats_Event(pTestCtrlBase, NULL, SYS_STATE_EVENT_OnTestStarted);

    return 0;
}

/*
老版本：
<ats-cmd name="" id="CreateTest" testor="" >
    <paras name="" id="">
        <data id="test-id" value="" /> 【测试标识】
+测试定义：
        <data id="gbxml-file" value="*.ppxml" /> 【规约模板文件】
        <data name="EngineProgID" id="EngineProgID" value=""/>
        <data id="ppxml-file" value="*.ppxml" /> 【规约模板文件】
        <data id="dvm-file" value="*.xml" />  【点表文件】
        <data id="cmm-cfg-file" value="*.xml" />  【通信地址设置文件】
        <group id="omm-config" >  【通信地址设置】
            ...........................
        </group>
或者：
        <data id="TestDefine" value="" ><![CADATA[   创建测试的定义  ]]></data>
    </paras>
</ats -cmd>

新版本：
<ats-cmd name="" id="CreateTest" testor="" >
	<paras name="" id="">
		<data name="测试模板" id="gbxml-file" data-type="" value="ATS_TEST_11_TEMPLATEFILE.gbxml" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<group name="" id="devices" data-type="devices" value="">
			<group name="" id="ATS_TEST_11_TEMPLATEFILE" data-type="device" value="">
				<data name="模型文件" id="dvm-file" data-type="" value="931标准模型文件.xml" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
				<data name="规约引擎" id="EngineProgID" data-type="" value="PpMmsEngine.PoEngine" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
			</group>
		</group>
		<group name="" id="test-apps" data-type="test-apps" value="">
			<group name="" id="test-app" data-type="test-app" value="">
				<data name="" id="SN" data-type="" unit="" value="123456789" format="" remark="" default="" reserved="0" time="0" />
				<data name="" id="EngineProgID" data-type="" unit="" value="PsuVm.TestEngine" format="" remark="" default="" reserved="0" time="0" />
				<data name="" id="dvm-file" data-type="" unit="" value="TestMacro.xml" format="" remark="" default="" reserved="0" time="0" />
				<data name="" id="remote-ip" data-type="" unit="" value="192.168.2.10" format="" remark="" default="" reserved="0" time="0" />
				<data name="" id="remote-port" data-type="" unit="" value="9988" format="" remark="" default="" reserved="0" time="0" />
			</group>
		</group>
		<group name="全局数据" id="GlobalDatas" data-type="" value="">
			<data name="类型检验" id="TestType" data-type="" value="全部检验" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		</group>
	</paras>
</ats -cmd>
 */
//如果没有传递测试模板参数，则表示打开已有测试记录，否则创建新的测试记录
long CSttSmartTest::Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();

	if (m_pSttMainFrame != NULL)
	{
		oAtsCmdDrv.DetachXObject();
		m_pSttMainFrame->PostMessage(WM_STT_CREATETEST_BY_CMD, (WPARAM)this, (LPARAM)pAtsCmd);
		return 1;
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SmartTest Has No MainFrame Thread......"));
	}
	// 	else //2023-8-30  lijunqing 在主窗口（主线程）中创建测试
	// 	{
	// 		return Ats_CreateTest(pAtsCmd, pSttProtocol);
	// 	}

	return 0;
}

//2023-8-31 lijunqing 发送自动测试创建消息给主线程，创建测试
//自动测试主线程调用 On_Ats_CreateTest
long CSttSmartTest::Post_Ats_CreateTest(CSttAtsCmd *pAtsCmd)
{
	pAtsCmd->AddRef();
	m_pSttMainFrame->PostMessage(WM_STT_CREATETEST_BY_CMD, (WPARAM)this, (LPARAM)pAtsCmd);

	return 0;
}

long CSttSmartTest::On_Ats_CreateTest(CSttAtsCmd *pAtsCmd)
{////2023-8-31 lijunqing 执行自动测试创建，被主线程消息函数调用
	m_bTestCreated = FALSE;
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("@@@@@@@@@@@@@@@@@@@@degub---------0000"));
	long nRet = Ats_CreateTest(pAtsCmd, NULL);
	CString strDeviceSN;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

	if (nRet == CREATE_TEST_CREATE_ERROR || nRet == CREATE_TEST_CURR_EXIST_NOT_SAME)
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}
	else if (CREATE_TEST_CREATE_NEW  == nRet || CREATE_TEST_CURR_EXIST_SAME == nRet)
	{
		CDvmDataset oDatas;
		CString strGbrptFile = GetProjectName();
		//注释此处，传递全路径  shaolei 20220707
		//strGbrptFile = GetPathFileNameFromFilePathName(strGbrptFile);
		oDatas.AddNewData(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE, "string", strGbrptFile);
		oDatas.AddNewData(STT_CMD_PARA_DeviceSN, STT_CMD_PARA_DeviceSN, "string", strDeviceSN);
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oDatas, NULL);
	}
	else
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

	pAtsCmd->Release();

	return 0;
}
//2023-8-31 lijunqing 发送自动测试创建消息给主线程，创建测试
//自动测试主线程调用 On_Ats_CreateTest
long CSttSmartTest::Post_Ats_ExportReport(CSttAtsCmd *pAtsCmd)
{
	pAtsCmd->AddRef();
	m_pSttMainFrame->PostMessage(WM_STT_EXPORTREPORT, (WPARAM)this, (LPARAM)pAtsCmd);

	return 0;
}


long CSttSmartTest::Pre_Ats_ExportReport(CSttAtsCmd *pAtsCmd)
{
	g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_ACK, NULL, NULL);

	CString strExportMode;
	if (! pAtsCmd->GetParasDataValueByID(XPARA_ID_Export_Mode, strExportMode))
	{//没有定义导出模式，暂时定义为导出当前TestControl的报告
		//还需要导出当前TestControl的报告，故此处不能发送失败应答。
		//g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -1;
	}

	//以下三种模式：导出失败时，失败应答由各自执行函数回复。导出成功时，成功应答由当前函数返回统一回复
	if (strExportMode == XPARA_Val_Export_Mode_single)
	{//导出单个报告
		return Pre_Ats_ExportReport_single(pAtsCmd);
	}

	if (strExportMode == XPARA_Val_Export_Mode_docs)
	{//合并Word报告
		return Pre_Ats_ExportReport_docs(pAtsCmd);
	}

	if (strExportMode == XPARA_Val_Export_Mode_gbrpts)
	{//合并Word报告
		return Pre_Ats_ExportReport_gbrpts(pAtsCmd);
	}

	//还需要导出当前TestControl的报告，故此处不能发送失败应答。
	//g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
	
	return -1;
}

void CSttSmartTest::SetGbrptFileFullPath(CString &strGbrptFile)
{
	if (strGbrptFile.Find(_T(":")) < 0)
	{
		CString strPath = _P_GetWorkspacePath() ;
		strGbrptFile = strPath + strGbrptFile;
	}
// 	if (strGbrptFile.Find(_T("/")) < 0 || strGbrptFile.Find(_T("\\")) < 0)
// 	{//如果带相对路径，则不能处理正确了
// 		CString strPath = _P_GetWorkspacePath() ;
// 		strGbrptFile = strPath + strGbrptFile;
// 	}
}

/*
<ats-cmd name="" id="ExportReport" testor="ATS">
	<paras name="" id="">
		<data name="" id="ExportMode" data-type="ExportMode" value="single"/>
		<data name="" id="BenchSN" data-type="" value="测试台SN/"/>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="测试模板" id="gbxml-file" value="……………"/> 
		<data name="gbrpt-file" id="gbrpt-file" data-type="" value="1"/>
		<group name="rpt-files" id="rpt-files" data-type="rpt-files" >
			<group name="rpt-file" id="rpt-file" data-type="rpt-file" >
				<data id="ItemPath" data-type="string" value=""/>
				<data id="file" data-type="rpt-file" value="XXXXX.xml"/>
				<data id="mode" data-type="mode" value="items"/>
			</group>
			。。。。。。。。。。。。。。
		</group>
		<group name="globaldatas" id="globaldatas" data-type="rpt-files" >
			<data id="" data-type="string" value=""/>
			。。。。。。。。。。。。。。
		</group>
	</paras>
</ats-cmd>
如果定义了gbrpt-file，则将rpt-files合并到gbrpt-file，并导出
如果没定义gbrpt-file，则打开模板创建gbrpt-file，将rpt-files合并到gbrpt-file，并导出
Globaldatas：全局数据，采用绝对路径的方式，填入到报告对应的标签位置。
*/
long CSttSmartTest::Pre_Ats_ExportReport_single(CSttAtsCmd *pAtsCmd)
{
	CString strGbrptFile, strGbxmlFile, strDeviceSN, strBenchSN;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBRPTFILE, strGbrptFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strGbxmlFile);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, strBenchSN);
	SetGbrptFileFullPath(strGbrptFile);

	if (! m_pTestControl->CreateTest(strGbrptFile, 1))
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -1;
	}

	CDataGroup *pRptFiles = (CDataGroup*)pAtsCmd->FindInParasByID(XPARA_Val_Export_Para_RptFiles);
	Pre_Ats_ExportReport_RptFiles(m_pTestControl, pRptFiles);

	m_pTestControl->m_pGuideBook->GBS_SetGlobal_Str(DATAID_DEVICESN, strDeviceSN);

	return 0;
}

long CSttSmartTest::Pre_Ats_ExportReport_RptFiles(CTestControlBase *pTestControl, CDataGroup *pRptFiles)
{
	if (pRptFiles == NULL)
	{
		return -1;
	}

	if (pRptFiles->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return -1;
	}

	CGuideBook *pGuideBook = pTestControl->m_pGuideBook;
	POS pos = pRptFiles->GetHeadPosition();
	CDataGroup *pRptFile = NULL;

	while (pos != NULL)
	{
		pRptFile = (CDataGroup *)pRptFiles->GetNext(pos);

		if (pRptFile->m_strID == XPARA_Val_Export_Para_RptFile)
		{
			Pre_Ats_ExportReport_RptFile(pGuideBook, pRptFile);
		}
	}

	pTestControl->SaveBinaryFile();

	return 0;
}

long CSttSmartTest::Pre_Ats_ExportReport_RptFile(CGuideBook *pGuideBook, CDataGroup *pRptFile)
{
	CString strItemPath, strRptFile;
	pRptFile->GetDataValue(STT_CMD_PARA_ItemPath, strItemPath);
	pRptFile->GetDataValue(XPARA_Val_Export_Para_RptFile, strRptFile);
		
	CGbItemBase *pGbItem = (CGbItemBase*)Gb_GetItem(pGuideBook, strItemPath);

	if (pGbItem == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("item-path [%s] error"), strItemPath.GetString());
		return -1;
	}

	if (pGbItem->GetClassID() != GBCLASSID_ITEMS)
	{
		return -1;
	}

	CItems oItems;
	FILE *pFile = fopen(strRptFile.GetString(), "r");

	if (pFile == NULL)
	{
		return -1;
	}

	char pBuff[4];
	fread(pBuff, 1, 2, pFile);
	fclose(pFile);

	if (pBuff[0] == '<')
	{
		oItems.OpenXmlFile(strRptFile, CGbXMLKeys::g_pGbXMLKeys, _PUGI_XML_TYPE_);
	}
	else
	{
		oItems.OpenXmlFile(strRptFile, CGbXMLKeys::g_pGbXMLKeys, _JSON_TYPE_);
	}
	
	Gb_SetItemsReport((CItems*)pGbItem, &oItems);
	pGbItem->m_nEnable = 1;
	Gb_SetItemsAllItemState(pGbItem, 1);
	Gb_SetGbModifiedFlag(pGbItem, TRUE);

	return 0;
}
/*
<ats-cmd name="" id="ExportReport" testor="ATS">
	<paras name="" id="">
		<data name="" id="ExportMode" data-type="ExportMode" value="docs"/>
		<data name="" id="BenchSN" data-type="" value="测试台SN/"/>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="doc-file" data-type="" value="######.Doc"/>
		<group name="gbrpts" id="gbrpts" data-type="gbrpts" >
			<data id="gbrpt" data-type="gbrpt" value="XXXXX.gbrpt"/>
			。。。。。。。。。。。。。。
			<data id="gbrpt" data-type="gbrpt" value="XXXXX.gbrpt"/>
		</group>
		<group name="docs" id="docs" data-type="docs" >
			<data id="doc" data-type="doc" value="XXXXX.doc"/>
			。。。。。。。。。。。。。。
			<data id="doc" data-type="doc" value="XXXXX.doc"/>
		</group>
	</paras>
</ats-cmd>
doc-file：多个word文档合并的目标文档
Docs：待合并的多个word文档
*/
long CSttSmartTest::Pre_Ats_ExportReport_docs(CSttAtsCmd *pAtsCmd)
{
#ifdef _PSX_IDE_QT_
	return -1;
#else
	CSttParas *pSttParas = pAtsCmd->GetSttParas();
	CDataGroup *pDocs = (CDataGroup*)pSttParas->FindByID(XPARA_Val_Export_Mode_docs);

	if (pDocs == NULL)
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -1;
	}

	if (pDocs->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -2;
	}

	CExBaseList listDocs;
	pDocs->SelectChildrenByClassID(listDocs, DVMCLASSID_CDVMDATA);
	long nDocCount = listDocs.GetCount();

	if (nDocCount <= 1)
	{
		listDocs.RemoveAll();
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -3;
	}

	FreeTestControlEx();

	CTestControlManyReport *pNew = new CTestControlManyReport();
	pNew->SetAutoDeleteChild(TRUE);
	m_pTestControl = pNew;
	CString strGbrptFile, strGbxmlFile, strDeviceSN, strBenchSN;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBRPTFILE, strGbrptFile);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strGbxmlFile);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, strBenchSN);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DOCRPTFILE, pNew->m_strCmbdDocFile);
	SetGbrptFileFullPath(strGbrptFile);
	SetGbrptFileFullPath(pNew->m_strCmbdDocFile);

	pNew->AddTCtrlMsgRcvInterface(this);

	CTestControlManyReportChild *pChild = NULL;
	CDvmData *pDoc = (CDvmData*)listDocs.GetHead();
	strGbrptFile = pDoc->m_strValue;
	strGbrptFile = ChangeFilePostfix(strGbrptFile, XPARA_Val_Export_Para_gbrpt);
	SetGbrptFileFullPath(strGbrptFile);

	if (! m_pTestControl->CTestControlBase::CreateTest(strGbrptFile, 1))
	{
		g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_FAILURE, NULL, NULL);
		return -4;
	}

	for (long k=1; k<nDocCount; k++)
	{
		pDoc = (CDvmData *)listDocs.GetAtIndex(k);
		strGbrptFile = pDoc->m_strValue;
		strGbrptFile = ChangeFilePostfix(strGbrptFile, XPARA_Val_Export_Para_gbrpt);
		pChild = new CTestControlManyReportChild();
		SetGbrptFileFullPath(strGbrptFile);
		pChild->SetBinaryFile(strGbrptFile);
		m_pTestControl->AddNewChild(pChild);
		pChild->AddTCtrlMsgRcvInterface(this);
	}

	listDocs.RemoveAll();
	m_pTestControl->m_pGuideBook->GBS_SetGlobal_Str(DATAID_DEVICESN, strDeviceSN);
	//在外面统一回复成功
	//g_theNativeTestEngine->Return_Ats_Success(pAtsCmd, STT_CMD_ExecStatus_SUCCESS, NULL, NULL);

	return 0;
#endif
}

long CSttSmartTest::Pre_Ats_ExportReport_gbrpts(CSttAtsCmd *pAtsCmd)
{
	return 0;
}

long CSttSmartTest::Ats_CreateTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);

	if (pDevices != NULL)
	{
		long nCount = pDevices->GetCount();

		//应用于线路纵联差动以及比对式自动测试  多装置，一个测试
		if (nCount > 1 && pDevices->m_strValue != XPARA_ID_devices_one_test)
		{
			return Ats_CreateTest_MdvMgrpSpo(pAtsCmd, pSttProtocol);
		}
	}

	return Ats_CreateTest_OneTest(pAtsCmd, pSttProtocol);
}


long CSttSmartTest::Ats_CreateTest_OneTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
	CDataGroup *pCommConfig = (CDataGroup*)pParas->FindByID(STT_CMD_PARA_CommConfig);
	CDataGroup *pTestApps = (CDataGroup*)pParas->FindByID(XPARA_ID_test_apps);
	CDataGroup *pDevice = (CDataGroup *)pDevices->FindByID(XPARA_ID_device);

	if (pDevice == NULL)
	{
		pDevice = (CDataGroup *)pDevices->FindByDataType(XPARA_ID_device);
	}

     CString strGbXmlFile, strGuideBookFileType
             , strTestProjectName, strPpEngineProgID
			 , strPpTemplateFile, strDeviceFile, strDeviceFile2
			 , strTestFolder, strDeviceSN;
    CString strPath;
    BOOL bCreateNew = FALSE;

    pAtsCmd->GetParasDataValueByID(XPARA_ID_Path, strTestFolder);
    bCreateNew = pAtsCmd->GetParasDataValueByID(XPARA_ID_GBXMLFILE, strGbXmlFile);
    pAtsCmd->GetParasDataValueByID(XPARA_ID_GBRPTFILE, strTestProjectName);
	//对于安全措施、系统参数编辑项目，是否显示测试对话框
	pAtsCmd->GetParasDataValueByID(XPARA_ID_SmartTestRunMode, g_strSmartTestRunMode);  

	//2023-8-21  李俊庆 默认从AtsCmd获取参数
	if (! pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_EngineProgID, strPpEngineProgID))
	{
		pDevice->GetDataValue(STT_CMD_PARA_EngineProgID, strPpEngineProgID);
	}

	if (! pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN))
	{
		pDevice->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);
	}

	if (! pAtsCmd->GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpTemplateFile))
	{
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE, strPpTemplateFile);
	}	

    long nRet = BeforeCreateTest(strGbXmlFile, strTestProjectName);

    if (nRet == CREATE_TEST_CURR_EXIST_SAME || nRet == CREATE_TEST_CURR_EXIST_NOT_SAME)
    {
        return nRet;
    }

	//单装置测试：多设备数据模型的设置
	Ats_CreateTest_OneTest_devices(pAtsCmd, pSttProtocol, strDeviceFile2);
	
	if (! pAtsCmd->GetParasDataValueByID(XPARA_ID_DVMFILE, strDeviceFile))
	{
		if (! pDevice->GetDataValue(XPARA_ID_DVMFILE, strDeviceFile))
		{
			strDeviceFile = strDeviceFile2;
		}
	}

	if (strPpEngineProgID.GetLength() == 0)
	{
		strPpEngineProgID = g_strSttEngine_PXI;//_T("PpEngine");
	}
    
    strGuideBookFileType = _T("");
    strPath = _P_GetWorkspacePath();
    strPath += strTestFolder;

    //gbrpt-file  validate
    if (strTestProjectName.GetLength() <= 6)
    {
        strTestProjectName = _P_GetProjectID();
        strTestProjectName += ".gbrpt";
    }

    BOOL bRet = FALSE;

    if (bCreateNew)
    {
        CString strTempFile;
        strTempFile = _P_GetTemplatePath();
        strTempFile += strGbXmlFile;

        CTCtrlCntrWorkSpace::s_SetPpTemplateFile(strPpTemplateFile);
        CTCtrlCntrWorkSpace::s_SetPpDeviceFile(strDeviceFile);
        CTCtrlCntrWorkSpace::s_SetTemplateFile(strTempFile);
        CTCtrlCntrWorkSpace::s_SetReportMapFile(strGuideBookFileType);
        CTCtrlCntrWorkSpace::s_SetTestFolder(strPath);
        CTCtrlCntrWorkSpace::s_SetTestName(strTestProjectName);
        CTCtrlCntrWorkSpace::s_SetTestID(strTestProjectName);
        CTCtrlCntrWorkSpace::s_SetPpEngineProgID(strPpEngineProgID);
        //CTCtrlCntrWorkSpace::g_pWorkSpace->Save();

#ifndef _PSX_IDE_QT_
		//报告模板文件
		CString strRptFile = strTempFile;
		CString strDestRptFile = strPath + strTestProjectName;

		if (strTestProjectName.Find(_T("\\")) > 0 || strTestProjectName.Find(_T("/")) > 0)
		{
			strDestRptFile = strTestProjectName;
		}

		strRptFile = ChangeFilePostfix(strRptFile, g_strDocFilePostfix);
		strDestRptFile = ChangeFilePostfix(strDestRptFile, g_strDocFilePostfix);
		CopyFile(strRptFile, strDestRptFile, FALSE);
#endif

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>  open %s"), strPpTemplateFile.GetString());
		bRet = m_pTestControl->CreateTest(pTestApps);
    }
    else
    {
        strPath += strTestProjectName;
        bRet = m_pTestControl->OpenBinaryFile(strPath, TRUE);
    }

	//项目选择
	CDataGroup *pItemsSel = (CDataGroup*)pParas->FindByID(STT_CMD_PARA_ItemsSel);
	InitGuideBook_ItemsSel(m_pTestControl->m_pGuideBook, pItemsSel);
	InitGuideBook_UpdateSysParas(m_pTestControl->m_pGuideBook, pParas);

	m_bTestCreated = FALSE;

	if (bRet)
	{
		m_pTestControl->CTestControlBase::SetDeviceSN_AfterTestCreated(strDeviceSN);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(">>  retrun SYS_STATE_EVENT_OnTestCreated"));
		stt_Return_Ats_Event_Ex(m_pTestControl, SYS_STATE_EVENT_OnTestCreated, _T(""));
	}

    if(m_bIsAtsLib)
    {
        m_pTestControl->CreateReportFill(g_strReportFillProgID);
        m_pTestControl->CreateTestControlWnd();
        //CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(pTestCtrl);
        m_pTestControl->SetSafetyParentWnd(m_pSttMainFrame);
        m_bTestCreated = TRUE;
    }
    else if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_CREATETEST, (WPARAM)m_pTestControl, (LPARAM)this);
	}

    if (bRet)
    {
        return CREATE_TEST_CREATE_NEW;
    }
    else
    {
        return CREATE_TEST_CREATE_ERROR;
    }
}

void CSttSmartTest::InitGuideBook_ItemsSel(CGuideBook *pGuideBook, CDataGroup *pItemsSel)
{
	if (pGuideBook == NULL || pItemsSel == NULL)
	{
		return;
	}

	POS pos = pItemsSel->GetHeadPosition();
	CDataGroup *p = NULL;

	while (pos != NULL)
	{
		p = (CDataGroup *)pItemsSel->GetNext(pos);
		InitGuideBook_ItemSel(pGuideBook, p);
	}
}

void CSttSmartTest::InitGuideBook_ItemSel(CGuideBook *pGuideBook, CDataGroup *pItemSel)
{
	if (pItemSel->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CString  strItemPath;

	if (!pItemSel->GetDataValue(STT_CMD_PARA_ItemPath, strItemPath))
	{
		return;
	}

	CGbItemBase *pGbItem = (CGbItemBase*)Gb_GetItem(pGuideBook, strItemPath);

	if (pGbItem == NULL)
	{
		return;
	}

	POS pos = pItemSel->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pItemSel->GetNext(pos);

		if (pData->m_strID == STT_CMD_PARA_Enable)
		{
			pGbItem->m_nEnable = CString_To_long(pData->m_strValue);
		}
		else if (pData->m_strID == STT_CMD_PARA_Select)
		{
			Gb_SetTestItemSelectedState(pGbItem, CString_To_long(pData->m_strValue));
		}
	}
}

void CSttSmartTest::InitGuideBook_UpdateSysParas(CGuideBook *pGuideBook, CDataGroup *pSttParas)
{
	CExBaseList listDatas;
	pSttParas->SelectAllDatas(listDatas);
	pGuideBook->UpdateSysPara(&listDatas, TRUE);
	listDatas.RemoveAll();
}

void CSttSmartTest::WaitForTestFinished(const CString &strCmd)
{
#ifdef _PSX_QT_LINUX_
	//若测试前，点击了IEC配置、系统参数配置、硬件通道映射配置，因为是立即生效，需要等待返回
	CVmSttMacroTest* pInterface = (CVmSttMacroTest*)m_pTestControl->m_pMacroTestInterface;

	if (pInterface != NULL)
	{
		CTickCount32 oTick;

		while (pInterface->m_bTestStarted)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("for debug   --->   测试已开始--->CSttSmartTest::WaitForTestFinished()   %s"), strCmd.GetString());
			oTick.DoEvents(50);
		}
	}
#endif 
}

BOOL CSttSmartTest::IsTestStarted()
{
	if (m_pTestControl == NULL)
	{
		return FALSE;
	}

	CVmSttMacroTest* pInterface = (CVmSttMacroTest*)m_pTestControl->m_pMacroTestInterface;

	if (pInterface != NULL)
	{
		return pInterface->m_bTestStarted;
	}

	return FALSE;
}

void CSttSmartTest::SetStopFlag(BOOL bStop)
{
	if (m_pTestControl == NULL)
	{
		return;
	}

	CVmSttMacroTest* pInterface = (CVmSttMacroTest*)m_pTestControl->m_pMacroTestInterface;

	if (pInterface == NULL)
	{
		return;
	}

	pInterface->SetStopFlag(bStop);
}

long CSttSmartTest::Ats_CreateTest_OneTest_devices(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol, CString &strDeviceFile)
{
	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);
	CDataGroup *pCommConfig = (CDataGroup*)pParas->FindByID(STT_CMD_PARA_CommConfig);
	CDataGroup *pTestApps = (CDataGroup*)pParas->FindByID(XPARA_ID_test_apps);

	if (pCommConfig != NULL)
	{
		m_pTestControl->InitCmmConfig(pCommConfig);
#ifndef _PSX_QT_LINUX_
		CTCtrlCntrWorkSpace::SetSttCommConfig((CPpSttCommConfig *)pCommConfig);
#endif
	}

#ifndef _PSX_QT_LINUX_
	CDataGroup *pDevice = NULL;
	CPpDeviceRefs *pDeviceRefs = CTCtrlCntrWorkSpace::GetPpDeviceRefs();
	CPpDeviceRef *pRef = NULL;

	if (pDevices == NULL)
	{
		return -1;
	}

	POS pos = pDevices->GetHeadPosition();
	pDevice = (CDataGroup *)pDevices->GetHead();
	pDevice->GetDataValue(STT_CMD_PARA_DvmFile, strDeviceFile);

	while (pos != NULL)
	{
		pDevice = (CDataGroup *)pDevices->GetNext(pos);

		if (pDevice->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		if (pDevice->m_strID != XPARA_ID_device)
		{
			if (pDevice->m_strDataType != XPARA_ID_device)
			{
				continue;
			}
		}

		pRef = new CPpDeviceRef();
		pDevice->GetDataValue(STT_CMD_PARA_EngineMode, pRef->m_strEngineMode);
		pDevice->GetDataValue(STT_CMD_PARA_EngineProgID, pRef->m_strPpEngineProgID);
		pDevice->GetDataValue(STT_CMD_PARA_DeviceSN, pRef->m_strID);
		pDevice->GetDataValue(STT_CMD_PARA_DvmFile, pRef->m_strDeviceModelFile);
		pDevice->GetDataValue(XPARA_ID_PPXMLFILE, pRef->m_strPpTemplateFile);

		pDeviceRefs->AddNewChild(pRef);
	}

	pDeviceRefs->InitBy_CreateTest();
#endif

	return 0;
}

//多装置单规约
long CSttSmartTest::Ats_CreateTest_MdvMgrpSpo(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	BOOL bRet = FALSE;
	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);

	CXObjectRefDriver oDriver(CAtsMesTestDefine::New);
	CAtsMesTestDefine *pAtsMesTestDef = (CAtsMesTestDefine*)oDriver.New();
	oDriver.AddRef();
	pAtsMesTestDef->AppendCloneEx2(*pParas, TRUE, TRUE);
	pAtsMesTestDef->InitAfterRead();

	if (m_pSttMainFrame != NULL)
	{
		//在主线程中，创建测试，加载模板：释放是在主线程
		m_bTestCreated = FALSE;
		m_pSttMainFrame->PostMessage(WM_ATS_CREATETEST, (WPARAM)pAtsMesTestDef, (LPARAM)DTMCLASSID_CDATAGROUP);
		bRet = TRUE;
	}

	CTickCount32 oTick;
	while (TRUE)
	{
		if (m_bTestCreated)
		{
			break;
		}

		oTick.DoEvents(100);
	}

	if (bRet)
	{
		FreeTestControl(TRUE);
		InitTestControl(false);
		SetDeviceSN_AfterTestCreated(pDevices);
		m_pTestControl->AddTCtrlMsgRcvInterface(this);  //创建视图时，会覆盖该指针，此处重新绑定
		return CREATE_TEST_CREATE_NEW;
	}
	else
	{
		return CREATE_TEST_CREATE_ERROR;
	}
}

long CSttSmartTest::Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    return Ats_StartTest(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_StartTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    if (m_pTestControl == NULL)
    {
        return 0;
    }

	if (m_pTestControl->GetDeviceRefsCount() == 0)
	{
		CreateDeviceRefs();
	}

	g_pGlobalDatas_Gb_CalParaExp = NULL;  //开始测试后，上一次的界面参数，应该不能再起作用了
	pAtsCmd->GetParasDataValueByID(STT_CMD_PATA_TestMode, g_nSmartTestMode);

	WaitForTestFinished(_T("Ats_StartTest"));

	if (g_nSmartTestMode == TEST_MODE_SINGLETEST)
	{
		//停止测试后，下次开始将从头开始测试   add by  shaolei  20220318
		m_pTestControl->m_nCurrTestItemIndex = 0;
		m_pTestControl->m_pGuideBook->m_nIndex = 0;
	}

	SetStopFlag(FALSE);

    if(m_bIsAtsLib)
    {
        m_pTestControl->TestFrom(-1);
        return 1;
    }

	if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_BEGINETEST, (WPARAM)m_pTestControl, 0);
	}
	else
	{
// 		m_pTestControl->m_pGuideBook->m_nIndex = 0;
		m_pTestControl->TestFrom(-1);
	}

    return 1;
}

long CSttSmartTest::Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    return Ats_StopTest(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_StopTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    if (m_pTestControl == NULL)
    {
        return 0;
    }

	SetStopFlag(TRUE);

    if(m_bIsAtsLib)
    {
        m_pTestControl->StopTestByOptr();

        if (g_nSmartTestMode == TEST_MODE_SINGLETEST)
        {
            //停止测试后，下次开始将从头开始测试   add by  shaolei  20220318
            m_pTestControl->m_nCurrTestItemIndex = 0;
            m_pTestControl->m_pGuideBook->m_nIndex = 0;
        }

        return 1;
    }

	if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_STOPTEST, (WPARAM)m_pTestControl, 0);
		return 1;
	}

    //CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    m_pTestControl->StopTestByOptr();

	
	if (g_nSmartTestMode == TEST_MODE_SINGLETEST)
	{
		//停止测试后，下次开始将从头开始测试   add by  shaolei  20220318
		m_pTestControl->m_nCurrTestItemIndex = 0;
		m_pTestControl->m_pGuideBook->m_nIndex = 0;
	}

    return 1;
}

long CSttSmartTest::Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    return Ats_CloseTest(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_CloseTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    if (m_pTestControl == NULL)
    {
        return 0;
    }

//#ifdef _PSX_QT_LINUX_

	SetStopFlag(TRUE);

	if (IsTestStarted())
	{
		m_pTestControl->StopTestByOptr();
	}
//#endif

    //CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    CString strMsg;
   // m_pTestControl->StopTestExtern(strMsg, TRUE);   //目前，移动端发CloseTest之前，会下发StopTest，故此处注释。shaolei 20201215

    if(m_bIsAtsLib)
    {
        FreeTestControlEx(true);
//        CTickCount32 oTick;
//        oTick.DoEvents(50);//等待tcp线程断链
//        InitTestControl(true);
        return 1;
    }

	if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_CLOSETEST, (WPARAM)m_pTestControl, (LPARAM)this);
		return 1;
	}
	
	//m_pTestControl->ReleaseMacroTestInterface(TRUE);
	FreeTestControl();	
	
	//close pxengine  2020-11-22  lijunqing


    return 1;
}
/*
<ats-cmd name="" id="TestItem" testor="" >
<paras name="" id="">	
<data id="ItemPath" value="" />  【项目的绝对路径】
<data id="ItemIndex" value="" />  【项目的编号】
</paras>
</ats -cmd>
*/
long CSttSmartTest::Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    return Ats_TestItem(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_TestItem(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    if (m_pTestControl == NULL)
    {
        return 0;
    }

   CGbItemBase *pItemFind = GetItemFromAtsCmd(*pAtsCmd);

	if (pItemFind == NULL)
	{
        return 0;
	}

	//shaolei 2023-9-14 此处是保证能够重新查询：重复测试时，需要项目报告备份
	m_pTestControl->m_nCurrTestItemIndex = 0;
	m_pTestControl->m_pGuideBook->m_nIndex = 0;
	g_pGlobalDatas_Gb_CalParaExp = NULL;  //开始测试后，上一次的界面参数，应该不能再起作用了

	WaitForTestFinished(_T("Ats_TestItem"));
	SetStopFlag(FALSE);

    if(m_bIsAtsLib)
    {
        return m_pTestControl->TestSingle(pItemFind);
    }

	if (m_pSttMainFrame != NULL)
	{
		m_pTestControl->InitGuideBook();
		m_pSttMainFrame->PostMessage(WM_STT_TESTPOINT, (WPARAM)m_pTestControl, pItemFind->m_nIndex);
		return 1;
	}
	else
	{
		return m_pTestControl->TestSingle(pItemFind);
	}
}

long CSttSmartTest::Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    return Ats_TestFrom(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_TestFrom(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    if (m_pTestControl == NULL)
    {
        return 0;
    }

    CGbItemBase *pItemFind = GetItemFromAtsCmd(*pAtsCmd);

	//shaolei 2023-9-14 此处是保证能够重新查询：重复测试时，需要项目报告备份
	m_pTestControl->m_nCurrTestItemIndex = 0;
	m_pTestControl->m_pGuideBook->m_nIndex = 0;
	g_pGlobalDatas_Gb_CalParaExp = NULL;  //开始测试后，上一次的界面参数，应该不能再起作用了

	WaitForTestFinished(_T("Ats_TestFrom"));
	SetStopFlag(FALSE);

    if(m_bIsAtsLib)
    {
        if (pItemFind == NULL)
        {
            m_pTestControl->TestFrom(-1);
        }
        else
        {
            m_pTestControl->TestFrom(pItemFind);
        }

        return 1;
    }

	if (m_pSttMainFrame != NULL)
	{			
		m_pTestControl->InitGuideBook();

		if (pItemFind == NULL)
		{
			m_pSttMainFrame->PostMessage(WM_STT_TESTBELOW, (WPARAM)m_pTestControl, -1);
		}
		else
		{
			m_pSttMainFrame->PostMessage(WM_STT_TESTBELOW, (WPARAM)m_pTestControl, pItemFind->m_nIndex);
		}
	}
	else
	{
		if (pItemFind == NULL)
		{
			m_pTestControl->TestFrom(-1);
		}
		else
		{
			m_pTestControl->TestFrom(pItemFind);
		}
	}

    return 1;
}

long CSttSmartTest::Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    return Ats_TestAllFailedItems(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_TestAllFailedItems(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    if (m_pTestControl == NULL)
    {
        return 0;
    }

	//shaolei 2023-9-14 此处是保证能够重新查询：重复测试时，需要项目报告备份
	m_pTestControl->m_nCurrTestItemIndex = 0;
	m_pTestControl->m_pGuideBook->m_nIndex = 0;

    if(m_bIsAtsLib)
    {
        m_pTestControl->OnTestAllInlegibleItems();
        return 0;
    }

	//2022-11-2  lijunqing
	if (m_pSttMainFrame != NULL)
	{//如果第一个不合格测试项目为通信命令项目，则会导致COM接口调用问题：线程外调用COM
		m_pSttMainFrame->PostMessage(WM_STT_TESTALLINLEGIBLEITEMS, (WPARAM)m_pTestControl, 0);
	}
	else
	{
		m_pTestControl->OnTestAllInlegibleItems();
	}

    return 0;
}

long CSttSmartTest::Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{//暂时不实现
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    return Ats_GetItemReport(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_GetItemReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{//暂时不实现
    return 1;
}

long CSttSmartTest::Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    return Ats_GetReportFile(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_GetReportFile(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    if (m_pTestControl == NULL)
    {
        return 0;
    }

    return 1;
}

long CSttSmartTest::Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
    return Ats_GetSystemState(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_GetSystemState(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    return 0;
}
/*
<ats-cmd name="FinishInputData" id="" testor="" >
    <paras name="" id="">
        <data name="温度" id="Temperature" data-type="float" unit="" value="0" ……/>
        <data name="湿度" id="Humidity" data-type="float" unit="" value="0" ……/>
        <data name="气压" id="AirPressure" data-type="float" unit="" value="0" ……/>
    </paras>
</ats -cmd>
 */
 long CSttSmartTest::Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
     CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
     return Ats_FinishInputData(pAtsCmd, pSttProtocol);
 }

 long CSttSmartTest::Ats_FinishInputData(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
     if(m_bIsAtsLib)
     {
         CSttParas *pParas = pAtsCmd->GetSttParas();
         m_pTestControl->FinishCurrTestItem(pParas);
         return 0;
     }

	if (m_pSttMainFrame != NULL)
	{
		pAtsCmd->AddRef();
		m_pSttMainFrame->PostMessage(WM_STT_FINISHINPUTDATA, (WPARAM)m_pTestControl, (LPARAM)pAtsCmd);
	}
	else
	{   
		CSttParas *pParas = pAtsCmd->GetSttParas();
		m_pTestControl->FinishCurrTestItem(pParas);
	}
	return 0;
 }

 /*
 <ats-cmd name="" id="SetItemState" testor="" >
     <paras name="" id="">
         <data id="ItemPath" value="" />  【项目的绝对路径】
         <data id="ItemIndex" value="" />  【项目的编号】
         <data id="Select" value="1" />
         <data id="Enable" value="1" />
         <data id="Show" value="1" />
     </paras>
 </ats -cmd>e
 */
 long CSttSmartTest::Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
     CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
     return Ats_SetItemState(pAtsCmd, pSttProtocol);
 }

 long CSttSmartTest::Ats_SetItemState(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
     if (m_pTestControl == NULL)
     {
         return 0;
     }

	 CDataGroup *pParas = pAtsCmd->GetSttParas();

	 if (m_pTestControl->SetItemState(pParas))
	 {
		 return 1;
	 }

	 return 0;
 }


 //2021-11-30  lijunqing
 long CSttSmartTest::Ats_InputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
     return 0;
 }
 long CSttSmartTest::Ats_InputData(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
     return 0;
 }

 long CSttSmartTest::Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	 return Ats_ExportReport(pAtsCmd, pSttProtocol);
 }

 long CSttSmartTest::Ats_ExportReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
	 if (m_pTestControl == NULL)
	 {
		 return -1;
	 }

	 CGuideBook *pGuideBook = GetGuideBook();

	 if (pGuideBook == NULL)
	 {
		 return -1;
	 }

	 if (m_pSttMainFrame != NULL)
	 {
		pAtsCmd->AddRef();
		m_pSttMainFrame->PostMessage(WM_STT_EXPORTREPORT, (WPARAM)this, (LPARAM)pAtsCmd);
	 }
	 else
	 {
		 //导出报告，只考虑在Windows下，有主界面
		 return -1;
	 }

	 return 1;
 }

 long CSttSmartTest::Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
     return 0;
 }
 long CSttSmartTest::Ats_SetItemsReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
     return 0;
 }

 long CSttSmartTest::Ats_QueryItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
     return 0;
 }
 long CSttSmartTest::Ats_QueryItems(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
     return 0;
 }

 long CSttSmartTest::Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
     return 0;
 }
 long CSttSmartTest::Ats_ConfigTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
     return 0;
 }

 long CSttSmartTest::Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase)
 {
     return 0;
 }

 long CSttSmartTest::Ats_ConfigTest(const CString &strDeviceSN, CExBaseList *pTestApps)
 {
     return 0;
 }

 long CSttSmartTest::Ats_QueryTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
    return 0;
}

 long CSttSmartTest::Ats_QueryTestParas(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    return 0;
}

 long CSttSmartTest::Ats_SetTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_SetTestParas(pAtsCmd, pSttProtocol);
}

/* 2024-2-21
<ats-cmd name="" id="SetTestPara" testor="ATS">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="SN"/>
		<group name="" id="Paras">
			<data name="参数1" id="Para1" value="0.25" />
			<data name="参数2" id="Para2" value="0.25999999" />
			<data name="参数3" id="Para3" value="0.75" />
			……
		</group>
	</paras>
</ats-cmd>
*/
 long CSttSmartTest::Ats_SetTestParas(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook == NULL)
	{
		return -2;
	}

	CDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return -3;
	}

	CSttParas *pSttParas = pAtsCmd->GetSttParas();
	CDataGroup *pParas = (CDataGroup *)pSttParas->FindByID(_T("Paras"));

	if (pParas == NULL)
	{
		return -4;
	}

	pDevice->SetSysParaValue(pParas, TRUE);

    return 0;
}

long CSttSmartTest::Process_Cmd_Test(CSttTestCmd *pTestCmd)
{
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("++++CSttSmartTest::Process_Cmd_Test++++"));
	if (m_pTestControl == NULL)
	{
        //IecDetect指令，作为单独模块时，第二次进入会删除TestControl
      InitTestControl(true);
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook->m_strTestMacroFileID.IsEmpty())
	{
		pGuideBook->m_strGuideBookFileType = _T("gbxml");
		pGuideBook->m_strTestMacroFileID = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->m_strMacroID;
		pGuideBook->InitAfterRead();
	}

    if(m_bIsAtsLib)
    {
        CVmSttMacroTest* pInterface = GetMacroTestInterface();

        if (pInterface == NULL)
        {
            CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("TestCmd ERROR --- MacroTestInterface == NULL"));
            return -1;
        }

        long nRet = pInterface->SendTestCmdEx(pTestCmd);
        delete pTestCmd;

        return nRet;
    }

	if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_SENDTESTCMD, (WPARAM)m_pTestControl/*pInterface*/, (LPARAM)pTestCmd);
		return 0;
	}

	CVmSttMacroTest* pInterface = GetMacroTestInterface();

	if (pInterface == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("TestCmd ERROR --- MacroTestInterface == NULL"));
		return -1;
	}

	long nRet = pInterface->SendTestCmdEx(pTestCmd);
	delete pTestCmd;

	return nRet;
}

void CSttSmartTest::InitTestControlMainWnd(CWnd *pWnd)
{
        m_pSttMainFrame = pWnd;
}
 void CSttSmartTest::InitTestControl(bool bCreate)
 {
	 if(m_pTestControl == NULL)
	 {
		 bCreate = true;
		 m_pTestControl = new CSttNativeTestCltlCntr();
		 m_pTestControl->CreateTestControlWnd();
		m_pTestControl->AddTCtrlMsgRcvInterface(this);
	 }

	 CGuideBook *pGuideBook = GetGuideBook();

	 if(pGuideBook  != NULL)
	 {
		 g_oSttGuideBookGenServer.SetGuideBook(pGuideBook);

		 if (bCreate)
		 {
			 pGuideBook->m_strGuideBookFileType = _T("gbxml");
			 pGuideBook->m_strTestMacroFileID = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->m_strMacroID;
			 pGuideBook->InitAfterRead();
		 }
	 }
	 else
	 {
		 //统一在此处新建GuideBook
		 pGuideBook = new CGuideBook();
		 m_pTestControl->m_pGuideBook = pGuideBook;
		 pGuideBook->m_strGuideBookFileType = _T("gbxml");
		 pGuideBook->m_strTestMacroFileID = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->m_strMacroID;
		 pGuideBook->InitAfterRead();
		 g_oSttGuideBookGenServer.SetGuideBook(pGuideBook);
	 }

	 if (bCreate)
		 CreateDeviceRefs();

     //创建后立即创建电气量项目的接口，以便连接底层服务，获取GPS对时时间等信息
#ifdef _PSX_IDE_QT_
     if (bCreate)
	 {
         CreateSmartTestWnd();

        if(m_bIsAtsLib)
        {
            ConnectSttServer_WhenInit();
        }
        else if (m_pSttMainFrame != NULL && m_bFirstInit)
		{
            //只有第一次初始化，才通过发消息，延迟3秒连接19814
            CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug   ->  First Init to connect 19814:emit signal"));
			m_pSttMainFrame->PostMessage(WM_STT_CONNECTSTTSERVER_19814, (WPARAM)m_pTestControl, (LPARAM)this);
		}
		else
		{
			ConnectSttServer_WhenInit();
		}
	 }
#endif
}

void CSttSmartTest::ConnectSttServer_WhenInit()
{
	CVmSttMacroTest* pInterface = (CVmSttMacroTest*)m_pTestControl->CreateMacroTestInterface(_T("Relay"), g_strSttTestClientEngine);

    if (pInterface == 0)
    {
        CLogPrint::LogString(XLOGLEVEL_TRACE, "ConnectSttServer_WhenInit: CreateMacroTestInterface == 0");
        return;
    }

	//已经连接成功，则不在重新连接
	if (pInterface->IsConnectSuccess())
	{
		return;
	}

#ifdef _PSX_QT_LINUX_
    if(m_bFirstInit)
    {
        CTickCount32 oTick;
        oTick.DoEvents(2000);//Linux下，延迟2秒，确保底层服务启动成功
    }
#endif

    m_bFirstInit = FALSE;
	BOOL bRet = pInterface->ConnectDevice();

	if (bRet)
	{
		if (g_oReadDeviceParameter.GetCount() == 0)
		{
			//没有读过装置参数，则下发读取命令
			//OnConnectSuccess();
			CStringArray astrType;
			astrType.Add(STT_CMD_PARA_DeviceAttrs);
			astrType.Add(STT_CMD_PARA_BoutTrunOnValueDef);
			astrType.Add(STT_CMD_PARA_ModuleAttrs);
			astrType.Add(STT_CMD_PARA_HdGears);
			astrType.Add(STT_CMD_PARA_ChMapDef);//zhouhj 20211006 增加用于上送混合插件的通道映射信息
			pInterface->Adjust_ReadDeviceParameter(astrType);
		}
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug -->CSttSmartTest::ConnectSttServer_WhenInit-->connect 19814 failed"));
	}
}

void CSttSmartTest::CreateSmartTestWnd()
{
#ifdef _PSX_IDE_QT_
	if (m_pSttMainFrame != NULL)
	{
		return;
	}

	m_pSttMainFrame = new CSttSmartTestWnd_Linux();
	CSttSmartTestWnd_Linux *pWnd = (CSttSmartTestWnd_Linux *)m_pSttMainFrame;
	pWnd->CreateSttSmartTestWnd();
	pWnd->SetTestControl(m_pTestControl);
#endif
}

CVmSttMacroTest* CSttSmartTest::GetMacroTestInterface(const CString &strType, const CString &strProgID)
{
	if (m_pTestControl == NULL)
	{
		return NULL;
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook->m_strTestMacroFileID.IsEmpty())
	{
		pGuideBook->m_strGuideBookFileType = _T("gbxml");
		pGuideBook->m_strTestMacroFileID = CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->m_strMacroID;
		pGuideBook->InitAfterRead();
	}

	if (m_pTestControl->m_pTCtrlWnd == NULL)
	{
		m_pTestControl->CreateTestControlWnd();
	}

	return (CVmSttMacroTest*)m_pTestControl->CreateMacroTestInterface(strType, strProgID);
}

 long CSttSmartTest::Ats_GenerateTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_GenerateTemplate(pAtsCmd, pSttProtocol);
}

 long CSttSmartTest::Ats_GenerateTemplate(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
     //关闭脱机进程时，会发送CloseTest指令，会释放m_pTestControl，所以此处需要判断
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("+++++++++++++++++  begin  Ats_GenerateTemplate"));
	InitTestControl(false);

#ifdef _PSX_IDE_QT_
	SetStopFlag(TRUE);

	if (IsTestStarted())
	{
		m_pTestControl->StopTestByOptr();
	}
#endif

    m_pTestControl->m_nCurrTestItemIndex = 0;
	CSttParas *pParas = pAtsCmd->GetSttParas();
	CGuideBook *pGuideBook = GetGuideBook();

    pGuideBook->m_strGuideBookFileType = _T("gbxml");
    pGuideBook->InitAfterRead();
    g_oSttGuideBookGenServer.SetGuideBook(pGuideBook);
	g_strSmartTestRunMode = SmartTest_Run_Mode_Server;
    long nRet = g_oSttGuideBookGenServer.Process_Cmd_Ats_GenerateTemplate(pParas);
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("------------------- end  Ats_GenerateTemplate"));
	//for debug begin
//  	CString strPath = _P_GetTemplatePath();
//  	strPath += _T("0x0x01.gbxml");
//  	pGuideBook->SaveXMLFile(strPath);
	//for debug end

    SetStopFlag(FALSE);
    if (nRet != 0)
    {
        return nRet;
    }

    return 0;
}

 long CSttSmartTest::Ats_GenerateItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	 return Ats_GenerateItems(pAtsCmd, pSttProtocol);
 }

 long CSttSmartTest::Ats_GenerateItems(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("+++for debug+++  begin generateitems"));
	InitTestControl(false);

	//只要新增加测试项，都需要从0开始
	m_pTestControl->m_pGuideBook->m_nIndex = 0;
	m_pTestControl->m_nCurrTestItemIndex = 0;

	CSttParas *pParas = pAtsCmd->GetSttParas();
	long nRet = g_oSttGuideBookGenServer.Process_Cmd_Ats_GenerateItems(pParas);

	CDataGroup *p_PARA_generate_items = (CDataGroup*)pParas->FindByID(STT_CMD_PARA_generate_items);

	if (p_PARA_generate_items != NULL)
	{
		if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_create)
		{
			//创建测试，需要重头开始测试
			m_pTestControl->m_nCurrTestItemIndex = 0;
			g_strSmartTestRunMode = SmartTest_Run_Mode_Server;

			/*m_pTestControl->*/ReleasePpEngine();
			CreateDeviceRefs();
		}
		else if (p_PARA_generate_items->m_strValue == STT_CMD_PARA_generate_items_import_dvm_file)
		{
			//导入模型文件（模型替换），需要断开与装置的连接，并重新创建Device
			m_pTestControl->m_nCurrTestItemIndex = 0;
			g_strSmartTestRunMode = SmartTest_Run_Mode_Server;

			/*m_pTestControl->*/ReleasePpEngine();
			CreateDeviceRefs();
		}
	}

	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("+++for debug+++  end generateitems"));

	//for debug begin
// 	CString strPath = _P_GetTemplatePath();
// 	strPath += _T("0x0x01.gbxml");
// 	CGuideBook *pGuideBook = GetGuideBook();
// 	pGuideBook->SaveXMLFile(strPath);
	//for debug end

	return nRet;
 }

 long CSttSmartTest::Ats_GenerateMacroTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	 return Ats_GenerateMacroTest(pAtsCmd, pSttProtocol);
 }

 long CSttSmartTest::Ats_GenerateMacroTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
	CSttParas *pParas = pAtsCmd->GetSttParas();
	long nRet = g_oSttGuideBookGenServer.Process_Cmd_Ats_GenerateMacroTest(pParas);

	return nRet;
 }

 long CSttSmartTest::Ats_SetItemPara(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
 {
	 CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	 return Ats_SetItemPara(pAtsCmd, pSttProtocol);
 }

long CSttSmartTest::Ats_SetItemPara(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
 {
	 CSttParas *pParas = pAtsCmd->GetSttParas();
	 long nRet = g_oSttGuideBookGenServer.Process_Cmd_Ats_SetItemPara(pParas);

	 if (nRet == 0)
	 {
		 AfterSetItemPara(pParas);
	 }

	 return nRet;
 }

long CSttSmartTest::Ats_SetItemPara_SystemConfig(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    CSttParas *pParas = pAtsCmd->GetSttParas();
// 	m_pTestControl->m_pGuideBook->m_nIndex = 0;
// 	m_pTestControl->InitGuideBook();
    long nRet = g_oSttGuideBookGenServer.Process_Cmd_Ats_SetItemPara_SystemConfig(pParas);
	return nRet;
}

long CSttSmartTest::Ats_ManualTrigger(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_ManualTrigger(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_ManualTrigger(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
    if (m_pTestControl == NULL)
    {
        return 0;
    }

    return m_pTestControl->ManualTrigger();
}

long CSttSmartTest::Ats_SaveTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) 
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_SaveTemplate(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_SaveTemplate(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	if (m_pTestControl->m_pGuideBook == NULL)
	{
		return -1;
	}

	CString strFileName, strPath;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_Path, strPath);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_FILE_NAME, strFileName);

	//存gbxml模板文件
	CString strLocalPath = ValidFileName(strPath, strFileName, g_strGbFileFilter);
	CGbXMLKeys::DecXml_SaveItemRpts();  //保存模板时，不保存项目报告
	m_pTestControl->m_pGuideBook->SaveXMLFile(strLocalPath);
	CGbXMLKeys::IncXml_SaveItemRpts();
	
	//存dscxml模板结构描述文件
	strLocalPath = ChangeFilePostfix(strLocalPath, g_strGbStruDscFileFilter);
	CGuideBookStruDscTool oTool;
	oTool.m_bExportMacroUIParas = TRUE;
	oTool.m_bExportRsltExpr = TRUE;
	oTool.m_nExportRpt = EXPROT_RPT_INIT;  //保存模板时，保存初始化报告
	oTool.m_bExportGlobalDatas = TRUE;
	oTool.m_bExportSysParas = TRUE;
	oTool.m_bExportCharacteristic = TRUE;
	oTool.m_bExportCmd = TRUE;
	g_bGbSaveItemState_WhenSavedscxml = FALSE;
	oTool.m_bExportItemsTecs = TRUE;
	oTool.ExportGuideBookStruDsc(m_pTestControl->m_pGuideBook, strLocalPath);
	
	return 1;
}

long CSttSmartTest::Ats_SaveTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) 
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_SaveTest(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_SaveTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	if (m_pTestControl->m_pGuideBook == NULL)
	{
		return -1;
	}

	CString strFileName, strPath;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_Path, strPath);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_FILE_NAME, strFileName);

	//存gbrpt测试记录文件
	CString strLocalPath = ValidFileName(strPath, strFileName, g_strGuideBookBinaryPostfix);
	Gb_SetGbModifiedFlag(m_pTestControl->m_pGuideBook, TRUE);
	m_pTestControl->m_pGuideBook->SaveBinaryFile(strLocalPath/*, CTCtrlCntrConfig::Get_RWReportFileMode()*/);

	//保存dscxml模板结构描述文件
	//保存测试记录时，dscxml中应该保留所有报告信息
	strLocalPath = ChangeFilePostfix(strLocalPath, g_strGbStruDscFileFilter);
	CGuideBookStruDscTool oTool;
	oTool.m_bExportMacroUIParas = TRUE;
	oTool.m_bExportRsltExpr = TRUE;
	oTool.m_nExportRpt = EXPROT_RPT_ALL;  //保存记录，导出所有测试报告
	oTool.m_bExportGlobalDatas = TRUE;
	oTool.m_bExportSysParas = TRUE;
	oTool.m_bExportCharacteristic = TRUE;
	oTool.m_bExportCmd = TRUE;
	g_bGbSaveItemState_WhenSavedscxml = TRUE;
	oTool.m_bExportItemsTecs = TRUE;
	oTool.ExportGuideBookStruDsc(m_pTestControl->m_pGuideBook, strLocalPath);

	return 1;
}

long CSttSmartTest::Ats_ExportWordRpt(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) 
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_ExportWordRpt(pAtsCmd, pSttProtocol);
}

/*
<ats-cmd name="" id="ExportWordRpt" mid="0" time="2023-10-20 10:30:25" testor="ATS">
	<paras name="" id="">
		<data id="path" data-type="string" value="D:/Program Files/EPOTO/Stt/Workspace/"/>【报告目标路径】
		<data id="file-name" data-type="string" value="rfg.doc"/>【报告文件名】
		<data id="src-path" data-type="string" value="d:/Program Files/EPOTO/Stt/Library/DOC_FILE_TEMPLATE_EMPTY.doc"/>【报告格式模板-空白模板】
		<group id="items-tecs" data-type="items-tecs">【技术要求编辑+数据小数位数配置】
			<group id="item-path" data-type="items-tec">【一个group，代表一个项目的技术要求，id填写为实际项目路径】
				<data id="rpt_tec_data1" value=""/>【技术要求，id用固定前缀：“rpt_tec_”。技术要求可以有多个】
				<data name="动作值小数点位数" data-type="int" id="rpt_precision_data1" value="1" min="0" max="4"/>【报告数据小数位数编辑，id用固定前缀：“rpt_precision_”。小数位数编辑可以有多个】
			</group>
			<group id="item-path" data-type="items-tec">
				<data id="rpt_tec_data1" value=""/>
			</group>
			<group id="item-path" data-type="items-tec">
				<data id="rpt_tec_data1" value=""/>
			</group>
		</group>
	</paras>
</ats-cmd>
*/
long CSttSmartTest::Ats_ExportWordRpt(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
#ifndef _PSX_IDE_QT_
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	if (m_pTestControl->m_pGuideBook == NULL)
	{
		return -1;
	}

	//传递的参数，是word报告文件的路径和文件名
	CString strFileName, strPath, strSrcPath;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_Path, strPath);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_FILE_NAME, strFileName);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_Src_Path, strSrcPath);

	CDataGroup* pItemsTec = (CDataGroup*)pAtsCmd->FindInParasByID(STT_CMD_PARA_items_tecs);

	if (pItemsTec != NULL)
	{
		m_pTestControl->m_pGuideBook->SetItemsTec(pItemsTec);
	}

	CString strXmlFileName;
	strXmlFileName = ChangeFilePostfix(strFileName, XML_FILE_POSTFIX_DATXML);
	strXmlFileName = strPath + strXmlFileName;

	//先在同路径下，生成Xml报告数据文件
	BOOL bRet = TRUE;
	CRptTemplate_GenXmlTool oGenXmlTool;
	bRet = oGenXmlTool.GenRpt_Xml_Dat(strXmlFileName, m_pTestControl->m_pGuideBook);

// 	if (! bRet)
// 	{
// 		return -1;
// 	}

	//再在同路径下，生成XML的word结构文件
	strXmlFileName = ChangeFilePostfix(strXmlFileName, XML_FILE_POSTFIX_DOCXML);
	bRet = oGenXmlTool.GenRpt_Xml_Doc(strXmlFileName, m_pTestControl->m_pGuideBook);

// 	if (! bRet)
// 	{
// 		return -1;
// 	}

	//最后在同路径下，生成doc报告文件
	CRptTemplate_GenDocTool *pGenDocTool = new CRptTemplate_GenDocTool();
	pGenDocTool->SetDestRptFile(strPath + strFileName);
	pGenDocTool->SetSrcRptFile(strSrcPath);
	pGenDocTool->SetXmlFile(strXmlFileName);

    if(m_bIsAtsLib)
    {
#ifndef _PSX_IDE_QT_
        bRet = pGenDocTool->GenRpt_Word();
#endif
        delete pGenDocTool;
        return 1;
    }

	if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_GENWORDRPT_BYTOOL, (WPARAM)this, (LPARAM)pGenDocTool);
		bRet = 1;
	}
	else
	{
		bRet = pGenDocTool->GenRpt_Word();
		delete pGenDocTool;
	}

// 	if (! bRet)
// 	{
// 		return -1;
// 	}

#endif
	return 1;
}

long CSttSmartTest::Ats_OpenTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_OpenTemplate(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_OpenTemplate(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook == NULL)
	{
		return -1;
	}

	CString strPath, strDvmFile;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_Path, strPath);
	strPath = ChangeFilePostfix(strPath, g_strGbFileFilter);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);
	
	pGuideBook->DeleteAll();

	m_pTestControl->m_nCurrTestItemIndex = 0;
	pGuideBook->m_nIndex = 0;
	g_strSmartTestRunMode = SmartTest_Run_Mode_Server;

	long nRet = pGuideBook->OpenXMLFile(strPath);

	if (strDvmFile.IsEmpty())
	{
		strDvmFile = pGuideBook->m_strDeviceModelFile;
	}
	else
	{
		if (IsFileExist(strDvmFile))
		{
			pGuideBook->m_strDeviceModelFile = strDvmFile;
			pGuideBook->SetCommConfig_DvmFile(strDvmFile);
		}
	}
	
	g_oSttGuideBookGenServer.OpenDvmFile_Ex(strDvmFile);

	return nRet;
}

long CSttSmartTest::Ats_OpenGbrptFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_OpenGbrptFile(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_OpenGbrptFile(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook == NULL)
	{
		return -1;
	}

	pGuideBook->FreeGuideBook();
	CString strPath, strDvmFile;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_GBRPTFILE, strPath);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);
	//对于安全措施、系统参数编辑项目，是否显示测试对话框
	pAtsCmd->GetParasDataValueByID(XPARA_ID_SmartTestRunMode, g_strSmartTestRunMode);  
	m_pTestControl->ChangeGbBinaryFileName(strPath);

	m_pTestControl->m_nCurrTestItemIndex = 0;
	pGuideBook->m_nIndex = 0;
	//g_strSmartTestRunMode = SmartTest_Run_Mode_Server;
	m_bTestCreated = FALSE;

    if(m_bIsAtsLib)
    {
        m_bTestCreated = FALSE;
        CString strPath = m_pTestControl->GetProjectName();
        m_pTestControl->OpenBinaryFile(strPath, TRUE);
        m_pTestControl->InitAfterOpenBinaryFile();
        m_bTestCreated = TRUE;
    }
    else if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_OPENGBRPTFILE, (WPARAM)m_pTestControl, (LPARAM)this);
	}
	else
	{
		return m_pTestControl->OpenBinaryFile(strPath, TRUE);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("wait for opening test"));
	CTickCount32 oTick;
	while (TRUE)
	{
		if (m_bTestCreated)
		{
			break;
		}

		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("wait for opening test"));
		oTick.DoEvents(100);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("open test success"));

	if (strDvmFile.IsEmpty())
	{
		strDvmFile = pGuideBook->m_strDeviceModelFile;
	}
	else
	{
		if (IsFileExist(strDvmFile))
		{
			pGuideBook->m_strDeviceModelFile = strDvmFile;
			pGuideBook->SetCommConfig_DvmFile(strDvmFile);
		}
	}

	if (stt_Is_SmartTest_Run_Server())
	{
		g_oSttGuideBookGenServer.OpenDvmFile(strDvmFile);
	}

	return 1;
}

long CSttSmartTest::Ats_AdjustMainWnd(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_AdjustMainWnd(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_UpdateItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_UpdateItem(pAtsCmd, pSttProtocol);
}

CString CSttSmartTest::Ats_QueryItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_QueryItem(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_AdjustReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_AdjustReport(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_ClearReportsRslts(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_ClearReportsRslts(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_ConfigDevice(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	return Ats_ConfigDevice(pAtsCmd, pSttProtocol);
}

long CSttSmartTest::Ats_AdjustMainWnd(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook == NULL)
	{
		return -1;
	}

	LONG nMainWnd = 0;
	LONG nLogWnd = 0;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_MainWnd, nMainWnd);
	pAtsCmd->GetParasDataValueByID(XPARA_ID_LogWnd, nLogWnd);

	if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_ADJUSTMAINWND, (WPARAM)nMainWnd, (LPARAM)nLogWnd);
	}
	else
	{
		return -1;
	}

	return 1;
}

long CSttSmartTest::Ats_UpdateItem(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook == NULL)
	{
		return -1;
	}

	CSttParas *pParas = pAtsCmd->GetSttParas();
	return g_oSttGuideBookGenServer.Process_Cmd_Ats_UpdateItem(pParas);
}

long CSttSmartTest::Ats_AdjustReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook == NULL)
	{
		return -1;
	}

	LONG nShowSypDlg = 0;
	pAtsCmd->GetParasDataValueByID(XPARA_ID_ADJUSTREPORT_ShowWnd, nShowSypDlg);

    if(m_bIsAtsLib)
    {
        m_pTestControl->AdjustReport(NULL);
        return 0;
    }

	if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_ADJUSTREPORT, (WPARAM)m_pTestControl, (LPARAM)nShowSypDlg);
	}
	else
	{
		m_pTestControl->AdjustReport(NULL);
		return 0;
	}

	return 0;
}

long CSttSmartTest::Ats_ClearReportsRslts(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook == NULL)
	{
		return -1;
	}

	LONG nOnlySelect = 0;
	CString strItemsID;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_OnlySelect, nOnlySelect);
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_ItemsID, strItemsID);

	CGbItemBase *pItemBase = (CGbItemBase *)Gb_GetItem(pGuideBook, strItemsID);

	if (pItemBase == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("cannot find item [%s]"), strItemsID.GetString());
		return -1;
	}

    if(m_bIsAtsLib)
    {
        CDevice *pDevice = pGuideBook->GetDevice();

        if (pDevice == pItemBase)
        {
            pGuideBook->CGbItemBase::ClearReport(FALSE);
            pGuideBook->CGbItemBase::SetState(TEST_STATE_NORMAL);
        }

        Gb_EmptyReportDatas(pItemBase, nOnlySelect);
        return 0;
    }

	if (m_pSttMainFrame != NULL)
	{
		pAtsCmd->AddRef();
		m_pSttMainFrame->PostMessage(WM_STT_CLEARREPORTSRSLTS, (WPARAM)m_pTestControl, (LPARAM)pAtsCmd);
	}
	else
	{
		CDevice *pDevice = pGuideBook->GetDevice();

		if (pDevice == pItemBase)
		{
			pGuideBook->CGbItemBase::ClearReport(FALSE);
			pGuideBook->CGbItemBase::SetState(TEST_STATE_NORMAL);
		}
		
		Gb_EmptyReportDatas(pItemBase, nOnlySelect);
		return 0;
	}

	return 0;
}

long CSttSmartTest::Ats_ConfigDevice(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return -1;
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook == NULL)
	{
		return -1;
	}

	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pCommConfig = (CDataGroup*)pParas->FindByID(STT_CMD_PARA_CommConfig);
	pGuideBook->SetCommConfig(pCommConfig);

	/*m_pTestControl->*/ReleasePpEngine();
	CreateDeviceRefs();

	return 0;
}

CString CSttSmartTest::Ats_QueryItem(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol)
{
	if (m_pTestControl == NULL)
	{
		return _T("");
	}

	CGuideBook *pGuideBook = GetGuideBook();

	if (pGuideBook == NULL)
	{
		return _T("");
	}

	CSttParas *pParas = pAtsCmd->GetSttParas();
	return g_oSttGuideBookGenServer.Process_Cmd_Ats_QueryItem(pParas);
}

CGuideBook* CSttSmartTest::GetGuideBook_AtsGen()
{
	if (m_pTestControl == NULL)
	{
		return NULL;
	}

    return m_pTestControl->m_pGuideBook;
}

CItems* CSttSmartTest::GetItems_AtsGen()
{
	return g_oSttGuideBookGenServer.GetItems();
}

CSttItems* CSttSmartTest::GetSttItems_AtsGen()
{
	CItems *pItems = g_oSttGuideBookGenServer.GetItems();

	if (pItems == NULL)
	{
		return NULL;
	}

	CSttItems *pSttItems = new CSttItems();
	CSttCmdGuideBookTransTool oTool;
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("+++for debug+++  begin transitems"));
	oTool.Trans(pItems, pSttItems);
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("+++for debug+++  end transitems"));

	CString strFile;
	strFile = _T("D:\\0\\ITEMS_FORDEBUG");
	strFile += pItems->m_strName;
	strFile += _T(".xml");

	pItems->SaveXmlFile(strFile, CGbXMLKeys::g_pXmlKeys);

	return pSttItems;
}

CItems* CSttSmartTest::GetItems_AtsGen_CmdAddGrp()
{
	return g_oSttGuideBookGenServer.GetItems_CmdAddGrp();
}

CSttItems* CSttSmartTest::GetSttItems_AtsGen_CmdAddGrp()
{
	CItems *pItems = g_oSttGuideBookGenServer.GetItems_CmdAddGrp();

	if (pItems == NULL)
	{
		return NULL;
	}

	CSttItems *pSttItems = new CSttItems();
	CSttCmdGuideBookTransTool oTool;
	oTool.Trans(pItems, pSttItems);

	return pSttItems;
}

CItems* CSttSmartTest::GetItems_AtsGen_ImportDvm()
{
	return g_oSttGuideBookGenServer.GetItems_ImportDvm();
}

CSttItems* CSttSmartTest::GetSttItems_AtsGen_ImportDvm()
{
	CItems *pItems = g_oSttGuideBookGenServer.GetItems_ImportDvm();

	if (pItems == NULL)
	{
		return NULL;
	}

	CSttItems *pSttItems = new CSttItems();
	CSttCmdGuideBookTransTool oTool;
	oTool.Trans(pItems, pSttItems);

	return pSttItems;
}

CItems* CSttSmartTest::GetItems_AtsGen_AinCfg()
{
	return g_oSttGuideBookGenServer.GetItems_AinCfg();
}

CSttItems* CSttSmartTest::GetSttItems_AtsGen_AinCfg()
{
	CItems *pItems = g_oSttGuideBookGenServer.GetItems_AinCfg();

	if (pItems == NULL)
	{
		return NULL;
	}

	CSttItems *pSttItems = new CSttItems();
	CSttCmdGuideBookTransTool oTool;
	oTool.Trans(pItems, pSttItems);

	return pSttItems;
}

void CSttSmartTest::FreeItems_AinCfg()
{
	g_oSttGuideBookGenServer.FreeItems_AinCfg();
}

CMacroTest* CSttSmartTest::GetSttMacroTest_AtsGen()
{
	return g_oSttGuideBookGenServer.GetMacroTest();
}

CSttItems* CSttSmartTest::GetSttItems_AtsGenEx()
{
	CItems *pItems = g_oSttGuideBookGenServer.GetItems_CurSel();  //当前选中的父节点

	if (pItems == NULL)
	{
		return NULL;
	}

	CExBaseList *pList = g_oSttGuideBookGenServer.GetItemsAppend(); //新生成的需要追加的项目，都是当前节点的子对象

	if (pList->GetCount() == 0)
	{
		return NULL;
	}

	CItems *pNewItems = (CItems *)pItems->CloneEx();//仅克隆自身
	pNewItems->Append(*pList);
	g_oSttGuideBookGenServer.ClearItemsAppend();  //清空新生成的追加项目
	CSttItems *pSttItems = new CSttItems();
	CSttCmdGuideBookTransTool oTool;
	oTool.Trans(pNewItems, pSttItems);

	return pSttItems;
}

void CSttSmartTest::SetMacroTestSaveParas(BOOL bSaveParas)
{
	g_oSttGuideBookGenServer.SetMacroTestSaveParas(bSaveParas);
}

void CSttSmartTest::AfterGenGuideBook()
{
    //m_pTestControl->SetGuideBook(m_pGuideBook);
}

void CSttSmartTest::SetTemplateGenMode(UINT nMode)
{
	g_oSttGuideBookGenServer.SetTemplateGenMode(nMode);
}

BOOL CSttSmartTest::Is_GenerateItems_CmdWzd()
{
	return g_oSttGuideBookGenServer.Is_GenerateItems_CmdWzd();
}

CDataGroup* CSttSmartTest::GetGenrateItems_CmdWzd_Reply()
{
	return g_oSttGuideBookGenServer.GetGenrateItems_CmdWzd_Reply();
}

void CSttSmartTest::SetDeviceSN_AfterTestCreated(CDataGroup *pDevices)
{
	if (m_pTestControl == NULL || pDevices == NULL)
	{
		return;
	}

#ifndef _PSX_IDE_QT_
	CMdvMgrpSpoDeviceMngrTestControl *pTestControl = (CMdvMgrpSpoDeviceMngrTestControl *)m_pTestControl;
#else
	CTestControlBase *pTestControl = m_pTestControl;
#endif

	long nIndex = 0;
	CDataGroup *pDevice = (CDataGroup *)pDevices->GetAtIndex(nIndex);

	if (pDevice == NULL)
	{
		return;
	}

	CString strDeviceSN;
	pDevice->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pTestControl->CTestControlBase::SetDeviceSN_AfterTestCreated(strDeviceSN);

#ifndef _PSX_IDE_QT_
	POS pos = pTestControl->m_listMdvMgrpTestControl.GetHeadPosition();

	while (pos != NULL)
	{
		nIndex++;
		pDevice = (CDataGroup *)pDevices->GetAtIndex(nIndex);

		if (pDevice == NULL)
		{
			return;
		}

		pDevice->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);
		CTestControlBase *pChildTestControl = (CTestControlBase *)pTestControl->m_listMdvMgrpTestControl.GetNext(pos);

		pChildTestControl->CTestControlBase::SetDeviceSN_AfterTestCreated(strDeviceSN);
	}
#endif
}

void CSttSmartTest::AfterSetItemPara(CSttParas *pParas)
{
#ifdef _PSX_IDE_QT_
	//Linux下，设置参数立即执行
	CString strItemPath, strMacroID;
	pParas->GetDataValue(STT_CMD_PARA_ItemPath, strItemPath);
	pParas->GetDataValue(STT_CMD_PARA_MacroID, strMacroID);

	//if (strItemPath.IsEmpty())
	{
		//项目路径为空，说明是从主界面进行的设置
		CSttContents *pContents = (CSttContents *)pParas->FindByID(STT_CMD_PARA_ContentsParas);

		if(strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig || strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig || strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
		{
			if (m_pTestControl == NULL)
			{
				//从主界面进入时，可能执行过CloseTest，会导致m_pTestControl为空，此处重新创建
				InitTestControl(TRUE);
			}
		}

		if(strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig)
		{
			AfterSetItemPara_IECConfig(pContents);
			return;
		}
		else if (strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig)
		{
			AfterSetItemPara_SystemConfig(pContents);
			return;
		}
		else if (strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
		{
			AfterSetItemPara_ChMapsConfig(pContents);
			return;
		}
		else
		{
			return;
		}
	}

	//不管项目是否存在，都直接下发指令给19815。此处直接返回
	return;

	CGuideBook *pGuideBook = GetGuideBook();
	CExBaseObject *pObj = Gb_GetItem(pGuideBook, strItemPath);

	if (pObj == NULL)
	{
		return;
	}

	if (pObj->GetClassID() != GBCLASSID_MACROTEST)
	{
		return;
	}

	CMacroTest *pMacroTest = (CMacroTest *)pObj;
	CString strItemMacroID = pMacroTest->GetTestMacroID() ;

	if(strItemMacroID != strMacroID)
	{
		return;
	}

	if(strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig || strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig || strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		m_pTestControl->TestSingle(pMacroTest);
	}

#endif
}

void CSttSmartTest::AfterSetItemPara_IECConfig(CSttContents *pContents)
{
	CVmSttMacroTest* pInterface = (CVmSttMacroTest*)m_pTestControl->m_pMacroTestInterface;

	if (pInterface == NULL)
	{
		pInterface = (CVmSttMacroTest*)m_pTestControl->CreateMacroTestInterface(_T("Relay"), g_strSttTestClientEngine);
	}

	BOOL bRet = pInterface->ConnectDevice();

	if (bRet)
	{
		CIecCfgDatasMngr *pIecCfgDatasMngr = (CIecCfgDatasMngr *)g_oSttGuideBookGenServer.m_oTool.m_pIecDatasMngr->CloneEx(TRUE, TRUE);

		CDataGroup oDataGroup;
		oDataGroup.AddNewChild(pIecCfgDatasMngr);

		pInterface->Test_StartTest(STT_CMD_TYPE_SYSTEM_IECConfig, &oDataGroup, TRUE, NULL, TRUE);
	}
}

void CSttSmartTest::AfterSetItemPara_SystemConfig(CSttContents *pContents)
{
	CVmSttMacroTest* pInterface = (CVmSttMacroTest*)m_pTestControl->m_pMacroTestInterface;

	if (pInterface == NULL)
	{
		pInterface = (CVmSttMacroTest*)m_pTestControl->CreateMacroTestInterface(_T("Relay"), g_strSttTestClientEngine);
	}

	BOOL bRet = pInterface->ConnectDevice();

	if (bRet)
	{
		CSttMacro *pSttMacro = g_oSttGuideBookGenServer.m_oTool.m_pSysParameter;

		CDataGroup oDataGroup;
		CSttParas *pParas = pSttMacro->GetParas();
		oDataGroup.AppendCloneEx(*pParas, TRUE);

		pInterface->Test_StartTest(STT_CMD_TYPE_SYSTEM_SystemConfig, &oDataGroup, TRUE, NULL, TRUE);
	}
}

void CSttSmartTest::AfterSetItemPara_ChMapsConfig(CSttContents *pContents)
{
	CVmSttMacroTest* pInterface = (CVmSttMacroTest*)m_pTestControl->m_pMacroTestInterface;
	if (pInterface == NULL)
	{
		pInterface = (CVmSttMacroTest*)m_pTestControl->CreateMacroTestInterface(_T("Relay"), g_strSttTestClientEngine);
	}

	BOOL bRet = pInterface->ConnectDevice();

	if (bRet)
	{
		CSttChMaps *pMaps = (CSttChMaps *)g_oSttGuideBookGenServer.m_oTool.m_pChMaps->CloneEx(TRUE, TRUE);

		CDataGroup oDataGroup;
		oDataGroup.AddNewChild(pMaps);

		pInterface->Test_StartTest(STT_CMD_TYPE_ADJUST_ChMapsConfig, &oDataGroup, TRUE, NULL, TRUE);
	}
}

void CSttSmartTest::CreateDeviceRefs()
{
	if (m_pTestControl == NULL)
	{
		return;
	}

    if(m_bIsAtsLib)
    {
        m_pTestControl->CreatePpDeviceRefs();
        return;
    }

	if (m_pSttMainFrame != NULL)
	{
		m_pSttMainFrame->PostMessage(WM_STT_CREATEDEVICEREFS, (WPARAM)m_pTestControl, 0);
	}
	else
	{
		m_pTestControl->CreatePpDeviceRefs();
	}
}

void CSttSmartTest::ReleasePpEngine()
{
	if (m_pTestControl == NULL)
	{
		return;
	}

    if(m_bIsAtsLib)
    {
        m_pTestControl->ReleasePpEngine();
        return;
    }

	if (m_pSttMainFrame != NULL)
	{
		m_bPpEngineReleased = FALSE;
		m_pSttMainFrame->PostMessage(WM_STT_RELEASEPPENGINE, (WPARAM)m_pTestControl, (LPARAM)this);

		CTickCount32 oTick;

		while (!m_bPpEngineReleased)
		{
			oTick.DoEvents(100);
		}
	}
	else
	{
		m_pTestControl->ReleasePpEngine();
	}
}

/*
<paras name="" id="">
    <data id="ItemPath" value="" />  【项目的绝对路径】
    <data id="ItemIndex" value="" />  【项目的编号】
</paras>
*/
CGbItemBase* CSttSmartTest::GetItemFromAtsCmd(CSttAtsCmd &oAtsCmd)
{
    CGbItemBase *pItemFind = NULL;
    CString strItemPath, strItemIndex;
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_ItemIndex, strItemIndex);

    CGuideBook *pGuideBook = m_pTestControl->m_pGuideBook;

    if (strItemPath.GetLength() > 0)
    {
        pItemFind = (CGbItemBase*)Gb_GetItem(pGuideBook, strItemPath);

        if (pItemFind == NULL)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, "GetItem([%s] == NULL", strItemPath.GetString());
        }
    }
    else
    {
        long nItemIndex = CString_To_long(strItemIndex);
        pItemFind = Gb_GetItemByIndex(pGuideBook, nItemIndex);

        if (pItemFind == NULL)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, "GetItem([%d] == NULL", nItemIndex);
        }
    }

    return pItemFind;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
<sys-state name="" id="事件ID" mater-host="" id-cmd="ATS-CMD" ret-type="EVENT">
    <paras name="" id="">
        <data id="ItemID" value="" />
        .............................
        <reports>
            ..............................
        </reports>
        <rpt-map-datas>
            <data name="开入B动作描述" id="Bmk17E213E1H654I517J69_99"
                value="57.395" data-type="" format="ActB"/>
        </rpt-map-datas>
    </paras>
<sys-state>
*/
long stt_Return_Ats_Event(CTestControlBase *pTestControl, CGbItemBase* pItem, char *pszEventID)
{
    CSttSysState oSysState;
    CSttParas *pParas = oSysState.GetSttParas();
    oSysState.SetEvent();
    oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
    oSysState.m_strID = pszEventID;

    CDvmDataset oDvmDataset;
    stt_Ats_InitSttStateDatas(&oDvmDataset, pTestControl, pItem);
    pParas->AppendCloneEx(oDvmDataset);

	if (pParas->FindByID(STT_CMD_PARA_DeviceSN) == NULL)
	{
		CString strDeviceSN;
		strDeviceSN = pTestControl->m_pGuideBook->GBS_GetGlobal_Str(STT_CMD_PARA_DeviceSN);
		pParas->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);;
	}

	if (g_theNativeTestEngine != NULL)
	{
		g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

    return 0;
}

long stt_Return_Ats_Event_TestItemCount(CTestControlBase *pTestControl, long nTestItemCount)
{
    CSttSysState oSysState;
    CSttParas *pParas = oSysState.GetSttParas();
    oSysState.SetEvent();
    oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
    oSysState.m_strID = SYS_STATE_EVENT_OnTestItemCount;

    long nDeviceIndex = 0;
    CString strTemp, strID;

    nDeviceIndex = RPC_API_GetTestControlIndex(pTestControl);
    strTemp.Format(_T("%d"), nDeviceIndex);
    strID = STT_CMD_PARA_DeviceIndex;
    pParas->AddNewData(strID, strTemp);

    strTemp.Format(_T("%d"), nTestItemCount);
    strID = STT_CMD_PARA_TestItemCount;
    pParas->AddNewData(strID, strTemp);

	if (g_theNativeTestEngine != NULL)
	{
		return g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

	return 0;
}

long stt_Return_Ats_Event(CTestControlBase *pTestControl, CGbItemBase* pItem, BOOL bReports, BOOL bRptMapDatas)
{
    CSttSysState oSysState;
    CSttParas *pParas = oSysState.GetSttParas();
    oSysState.SetReporting();
    oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;

    if (bReports)
    {
        CSttReports *pSttReports = pParas->GetSttReports(TRUE);
        stt_Ats_InitSttReports(pSttReports, pItem);

		CString strRsltExpr;
		pItem->GetRsltExpr(strRsltExpr);

		if (! strRsltExpr.IsEmpty())
		{
			pParas->AddContents(STT_CMD_PARA_RsltEpxr, strRsltExpr);
		}
    }

    if (bRptMapDatas)
    {
        CSttRptMapDatas *pSttRptMapDatas = pParas->GetSttRptMapDatas(TRUE);
        stt_Ats_InitSttRptMapDatas(pSttRptMapDatas, pItem);
    }

    CDvmDataset oDvmDataset;
    stt_Ats_InitSttStateDatas(&oDvmDataset, pTestControl, pItem);
    pParas->AppendCloneEx(oDvmDataset);

	CString strDeviceSN;
	strDeviceSN = pTestControl->m_pGuideBook->GBS_GetGlobal_Str(STT_CMD_PARA_DeviceSN);
	pParas->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);;

	oSysState.Set_Xml_Pkg_With_Name(TRUE);

	if (g_theNativeTestEngine != NULL)
	{
		g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

	oSysState.Set_Xml_Pkg_With_Name(FALSE);

    return 0;
}

void stt_Ats_InitSttReports(CSttReports *pSttReports, CGbItemBase *pItem)
{
    CReports *pReports = pItem->GetReports();
	CReports *pReportsBack = pItem->GetReportsBack();

	if (pReportsBack != NULL)
	{
		//按照执行测试的顺序，先处理备份的报告
		stt_Ats_InitSttReports_Ex(pSttReports, pReportsBack, pItem);
	}

	stt_Ats_InitSttReports_Ex(pSttReports, pReports, pItem);
}

void stt_Ats_InitSttReports_Ex(CSttReports *pSttReports, CReports *pReports, CGbItemBase *pItem)
{
	POS pos = pReports->GetHeadPosition();
	CReport *pReport = NULL;
	CSttReport *pSttReport = NULL;

	while (pos != NULL)
	{
		pReport = (CReport*)pReports->GetNext(pos);

		if (pReport->m_strID == STT_REPORT_ID_INIT)
		{
			//报告事件中，不上送初始化报告
			//shaolei 2023-7-18 修改为上送初始化报告；
			//这样，在上位机，清除报告后，还能有初始化报告。
			//continue;
		}

		pSttReport = new CSttReport();
		pSttReports->AddNewChild(pSttReport);

		pSttReport->m_strName = pReport->m_strName;
		pSttReport->m_strID = pReport->m_strID;
		pSttReport->m_strBeginTime = pReport->m_strBeginTime;
		pSttReport->m_strEndTime = pReport->m_strEndTime;
		pSttReport->InitValues(pReport->m_pValues);
		stt_AtsInitSttReport_DataType(pSttReport, pItem, FALSE);   //处理电气量项目报告数据的数据类型和名称

		if (pReport->m_pRptDvmDataset != NULL)
		{
			pSttReport->InitRptDvmDataset(pReport->m_pRptDvmDataset);
		}
	}
}

void stt_Ats_InitSttRptMapDatas(CSttRptMapDatas *pSttRptMapDatas, CGbItemBase *pItem)
{
    CExBaseList oListDatas;
    pItem->GetReportDatasByMap(&oListDatas);
     POS pos = oListDatas.GetHeadPosition();
     CValue *pValue = NULL;
     CRptData *pRptData = NULL;
    CRptBkmk *pBkmk = NULL;
    CDvmData *pDvmData = NULL;

    while (pos != NULL)
    {
        pValue = (CValue*)oListDatas.GetNext(pos);
        pRptData = (CRptData*)pValue->m_dwItemData;

        if (pRptData == NULL)
        {
            continue;
        }

        POS posBkmk = pRptData->GetHeadPosition();

        while (posBkmk != NULL)
        {
            pBkmk = (CRptBkmk*)pRptData->GetNext(posBkmk);
            pDvmData = new CDvmData();
            pSttRptMapDatas->AddNewChild(pDvmData);
            pDvmData->m_strName = pRptData->m_strName;
            pDvmData->m_strID = pBkmk->m_strID;
            pDvmData->m_strValue = pValue->m_strValue;
            pDvmData->m_strFormat = pValue->m_strID;
        }
    }
}

void stt_Ats_InitSttStateDatas(CDvmDataset *pDvmDataset, CTestControlBase *pTestControl, CGbItemBase *pItem)
{
    CString strTestID, strItemID, strState, strTemp, strSelect;
    long nDeviceIndex = 0, nReportIndex = 0,  nItemIndex = 0;

//     nDeviceIndex = RPC_API_GetTestControlIndex(pTestControl);
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);
	strTemp.Format(_T("%d"), nDeviceIndex);
	pDvmDataset->AddNewData(STT_CMD_PARA_DeviceIndex, STT_CMD_PARA_DeviceIndex, _T("long"), strTemp);
	pDvmDataset->AddNewData(STT_CMD_PARA_DeviceSN, STT_CMD_PARA_DeviceSN, _T("string"), strTestID);

    if (pItem == NULL)
    {
        return;
    }

    RPC_API_GetItemState(pItem, strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);

    pDvmDataset->AddNewData(STT_CMD_PARA_Test_ID, STT_CMD_PARA_Test_ID, _T("string"), strTestID);

    strTemp.Format(_T("%d"), nReportIndex);
    pDvmDataset->AddNewData(STT_CMD_PARA_ReportIndex, STT_CMD_PARA_ReportIndex, _T("long"), strTemp);

    strTemp.Format(_T("%d"), nItemIndex);
    pDvmDataset->AddNewData(STT_CMD_PARA_ItemIndex, STT_CMD_PARA_ItemIndex, _T("long"), strTemp);

    pDvmDataset->AddNewData(STT_CMD_PARA_ItemID, STT_CMD_PARA_ItemID, _T("string"), strItemID);
    pDvmDataset->AddNewData(STT_CMD_PARA_State, STT_CMD_PARA_State, _T("string"), strState);

	strSelect.Format(_T("%d"), pItem->GetSelect());
	pDvmDataset->AddNewData(STT_CMD_PARA_Select, STT_CMD_PARA_Select, _T("string"), strSelect);
}

void stt_Return_Ats_X_AddPatas(CTestControlBase *pTestControl, CSttParas *pSttParas, long nMode)
{
	CString strDeviceSN = pTestControl->m_pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);
	pSttParas->AddNewData( STT_CMD_PARA_DeviceSN, strDeviceSN);

	CString strSampleSN, strTaskSN; 
	
	if (pTestControl->m_pGuideBook->GBS_GetGlobal_Str(DATAID_SAMPLESN, strSampleSN))
	{
		pSttParas->AddNewData(XPARA_ID_SampleSN, strSampleSN);
	}	

	if (pTestControl->m_pGuideBook->GBS_GetGlobal_Str(DATAID_TASKSN, strTaskSN))
	{
		pSttParas->AddNewData(XPARA_ID_TaskSN, strTaskSN);
	}

	CString strTestID, strTemp;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);

	strTemp.Format(_T("%d"), nDeviceIndex);
	pSttParas->AddNewData3( STT_CMD_PARA_DeviceIndex, _T("long"), strTemp);
	pSttParas->AddNewData3( STT_CMD_PARA_Test_ID, _T("string"), strTestID);
	strTemp.Format(_T("%d"), nReportIndex);
	pSttParas->AddNewData3(STT_CMD_PARA_ReportIndex, _T("long"), strTemp);
}

long stt_Return_Ats_Event_Ex(CTestControlBase *pTestControl, const CString &strEventType, const CString &strEventID)
{
    CSttSysState oSysState;
    CSttParas *pParas = oSysState.GetSttParas();
    oSysState.SetEvent();
    oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
    oSysState.m_strID = strEventType;

    if (strEventID.GetLength() > 0)
    {
        pParas->AddNewData(SYS_STATE_XEVENT_EVENTID, strEventID);
    }

// 	CString strTestID, strTemp;
// 	long nDeviceIndex = 0, nReportIndex = 0;
// 	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);
// 
// 	strTemp.Format(_T("%d"), nDeviceIndex);
// 	pParas->AddNewData3( STT_CMD_PARA_DeviceIndex, _T("long"), strTemp);
// 	pParas->AddNewData3( STT_CMD_PARA_Test_ID, _T("string"), strTestID);
// 	strTemp.Format(_T("%d"), nReportIndex);
// 	pParas->AddNewData3(STT_CMD_PARA_ReportIndex, _T("long"), strTemp);
	stt_Return_Ats_X_AddPatas(pTestControl, pParas);


#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
    //2020-12-07  lijunqing
    if (strEventType == SYS_STATE_EVENT_OnTestCreated)
    {
        //pParas->AttatchGuideBook((CGuideBook*)pTestControl->m_pGuideBook);
    }
#endif

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
	if (strEventType == SYS_STATE_EVENT_OnTestCreated)
	{
		//Server模式下，才返回GuideBook。2023-11-27
		if (g_strSmartTestRunMode == SmartTest_Run_Mode_Server)
		{
			CGuideBook *pGuideBook = (CGuideBook*)pTestControl->m_pGuideBook;
			CSttCmdGuideBookTransTool oTool;
			CSttGuideBook *pNewSttGuideBook = pParas->NewGuideBook();
			oTool.Trans(pGuideBook, pNewSttGuideBook);
		}
	}
#endif

	if (g_theNativeTestEngine != NULL)
	{
		return g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

	return 0;
}

long stt_Return_Ats_EngineEvent(const CString &strDeviceID, const CString &strEventType, const CString &strEventID, CDvmDataset *pDataset)
{
    CSttSysState oSysState;
    CSttParas *pParas = oSysState.GetSttParas();
    oSysState.SetEvent();
    oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
    oSysState.m_strID = strEventType;

    pParas->AddNewData(SYS_STATE_XEVENT_EVENTID, strEventID);
    pParas->AddNewData3( STT_CMD_PARA_DeviceIndex, _T("string"), strDeviceID);

    if (pDataset != NULL)
    {
        pParas->AddTail(pDataset);
    }

	if (g_theNativeTestEngine != NULL)
	{
		g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

    if (pDataset != NULL)
    {
        pParas->Remove(pDataset);
    }

	return 0;
}

long stt_Return_Ats_ParentItem_StateChanged(CTestControlBase *pTestControl, CGbItemBase *pItem)
{
	long nState = pItem->GetState();

	if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_strItemsCountMode == SMARTTEST_ITEM_COUNT_MODE_ALLITEMS)
	{
		//按小项统计的，不发送大项的状态改变
		return 0;
	}
	else
	{
		//进入到此处的，都是测试小项
		CItems *pParentItems = Gb_GetFirstParentItems(pItem,TRUE);

		if (pParentItems == NULL)
		{
			//直接在CDevice下的测试小项，会返回为空
			return 0;
		}

		if (!pParentItems->IsTypeRootNode())
		{
			return 0;
		}

		if (!Gb_IsItemsTestFinished(pParentItems))
		{
			//若第二遍测试，此处也会判断为测完
			return 0;
		}

		if (pTestControl->m_pItemContainer == NULL)
		{
			return 0;
		}

		//CString strParentItem = Gb_GetItemPath(pParentItems);
		CGbItemBase *pNext = pTestControl->m_pItemContainer->GetNextItem_Ex(); //获取下一个项目

		if (pNext != NULL)
		{
			//CString strNextItem = Gb_GetItemPath(pNext);
			//shaolei 2024-4-18 改为是否为祖先节点判断。项目路径判断有bug

			if (pParentItems->IsAncestorOf(pNext))
			{
				//下一项是当前父项目的子项
				return 0;
			}
		}

		stt_Return_Ats_Event(pTestControl, pParentItems, SYS_STATE_EVENT_OnItemStateChanged);
	}

	return 0;
}

long stt_Return_Ats_Event_Process(CTestControlBase *pTestControl, CGbItemBase *pItem)
{
	long nState = pItem->GetState();
	CGbItemBase *pNext = NULL;
	CString strNextItemName = _T("无项目");

	if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_strItemsCountMode == SMARTTEST_ITEM_COUNT_MODE_ALLITEMS)
	{
		if (pItem->GetClassID() == GBCLASSID_ITEMS)
		{
			return 0;
		}

		//略过子项目：子项目结束时，父项目已经结束，会导致发两次TestProcess
		if (pItem->m_bIsSubItem)
		{
			return 0;
		}

		if (nState == TEST_STATE_ELIGIBLE || nState == TEST_STATE_INLEGIBLE
			|| nState == TEST_STATE_SKIP || nState == TEST_STATE_ELIGIBLEEX)
		{
			//电气量项目需要考虑重复次数，全部测试完成，算测试结束
			if (pItem->GetClassID() == GBCLASSID_MACROTEST)
			{
				CMacroTest *pMacroTest = (CMacroTest *)pItem;

				if (!pTestControl->IsRepeatTimesFinished(pMacroTest))
				{
					return 0;
				}
			}

			pNext = pTestControl->m_pItemContainer->GetNextItem_Ex();
			
			if (pNext != NULL)
			{
				strNextItemName = pNext->m_strName;
			}

			stt_Return_Ats_Event_Process(pTestControl, pItem->m_strName, strNextItemName);
		}
	}
	else
	{
		//进入到此处的，都是测试小项
		CItems *pParentItems = Gb_GetFirstParentItems(pItem,TRUE);

		if (pParentItems == NULL)
		{
			//直接在CDevice下的测试小项，会返回为空
			return 0;
		}

		if (!pParentItems->IsTypeRootNode())
		{
			return 0;
		}

		if (!Gb_IsItemsTestFinished(pParentItems))
		{
			return 0;
		}

		pNext = Gb_GetNextRootTypeItems(pParentItems);

		if (pNext != NULL)
		{
			strNextItemName = pNext->m_strName;
		}

		stt_Return_Ats_Event_Process(pTestControl, pParentItems->m_strName, strNextItemName);
	}
	
	return 0;
}

long stt_Return_Ats_Event_Process(CTestControlBase *pTestControl, const CString &strCurrItemName, const CString &strNextItemName)
{
	if (pTestControl->m_pItemContainer == NULL)
	{
		return 0;
	}

	CString strDeviceID, strTestID, strDeviceState;
	long nTotalItems = 0, nCurrItem = 0, nTotalTime = 0, nRemainTime = 0;
	long nEligibleItems = 0;
	long nInlegibleItems = 0;
	strDeviceID = pTestControl->m_pGuideBook->GBS_GetGlobal_Str(DATAID_DEVICESN);
	strDeviceState = pTestControl->m_pGuideBook->GetSummaryRslt();

	if (pTestControl->GetParent() != NULL)
	{
		//表示是从TestControl对象
		CTestControlBase *pMainTestControl = (CTestControlBase *)pTestControl->GetParent();
		pMainTestControl->m_pItemContainer->GetTestProcess(nTotalItems, nCurrItem, nTotalTime, nRemainTime);
		pMainTestControl->GetItemsCount(nTotalItems, nEligibleItems, nInlegibleItems);

		pMainTestControl->m_pItemContainer->m_nCurrFinishItem--;  //从TestControl对象的进度会累加到主TestControl。故此处还原
		nCurrItem--;
	}
	else
	{
		pTestControl->m_pItemContainer->GetTestProcess(nTotalItems, nCurrItem, nTotalTime, nRemainTime);
		pTestControl->GetItemsCount(nTotalItems, nEligibleItems, nInlegibleItems);
	}

	CSttSysState oSysState;
	CSttParas *pParas = oSysState.GetSttParas();
	oSysState.SetEvent();
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
	oSysState.m_strID = SYS_STATE_EVENT_OnTestProcess;

	long nDeviceIndex = 0;
	CString strTemp, strID;

	nDeviceIndex = RPC_API_GetTestControlIndex(pTestControl);
	strTemp.Format(_T("%d"), nDeviceIndex);
	strID = STT_CMD_PARA_DeviceIndex;
	pParas->AddNewData(strID, strTemp);

	pParas->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceID);
	pParas->AddNewData(STT_CMD_PARA_Test_ID, strTestID);
	pParas->AddNewData(STT_CMD_PARA_DeviceState, strDeviceState);

	strTemp.Format(_T("%d"), nTotalItems);
	strID = STT_CMD_PARA_TotalItems;
	pParas->AddNewData(strID, strTemp);

	strTemp.Format(_T("%d"), nCurrItem);
	strID = STT_CMD_PARA_CurrItem;
	pParas->AddNewData(strID, strTemp);

	strTemp.Format(_T("%d"), nTotalTime);
	strID = STT_CMD_PARA_TotalTime;
	pParas->AddNewData(strID, strTemp);

	strTemp.Format(_T("%d"), nRemainTime);
	strID = STT_CMD_PARA_RemainTime;
	pParas->AddNewData(strID, strTemp);

	strTemp.Format(_T("%d"), nEligibleItems);
	strID = XPARA_ID_ELIGIBLEITEMS;
	pParas->AddNewData(strID, strTemp);

	strTemp.Format(_T("%d"), nInlegibleItems);
	strID = XPARA_ID_INLEGIBLEITEMS;
	pParas->AddNewData(strID, strTemp);
	pParas->AddNewData(STT_CMD_PARA_CurrItemName, strCurrItemName);
	pParas->AddNewData(STT_CMD_PARA_NextItemName, strNextItemName);

	if (g_theNativeTestEngine != NULL)
	{
		return g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

	return 0;
}

//导出报告结束，直接携带报告文件绝对路径
long stt_Return_Ats_Event_ExportFinish(CTestControlBase *pTestControl)
{
	CString strTestID;
	long nDeviceIndex = 0, nReportIndex = 0;
	RPC_API_GetTestCtrlAttr(pTestControl, strTestID, nDeviceIndex, nReportIndex);

	CDataGroup oGrp;
	pTestControl->GetReportFiles(&oGrp);

	CSttSysState oSysState;
	CSttParas *pParas = oSysState.GetSttParas();
	oSysState.SetEvent();
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
	oSysState.m_strID = SYS_STATE_EVENT_ExportReport;

	pParas->AddNewData(STT_CMD_PARA_EventID, SYS_STATE_XEVENT_EVENTID_ExportFinish);
	stt_Return_Ats_X_AddPatas(pTestControl, pParas);

// 	pParas->AddNewData(STT_CMD_PARA_Test_ID, strTestID);
// 	CString strTemp, strID;
// 
// 	strTemp.Format(_T("%d"), nDeviceIndex);
// 	strID = STT_CMD_PARA_DeviceIndex;
// 	pParas->AddNewData(strID, strTemp);
// 
// 	strTemp.Format(_T("%d"), nReportIndex);
// 	strID = STT_CMD_PARA_ReportIndex;
// 	pParas->AddNewData(strID, strTemp);

	pParas->AppendClone(oGrp);

	if (g_theNativeTestEngine != NULL)
	{
		return g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

	return 0;
}

BOOL stt_Is_SmartTest_Run_Local()
{
	return (g_strSmartTestRunMode == SmartTest_Run_Mode_Local) || g_strSmartTestRunMode.IsEmpty();
}

BOOL stt_Is_SmartTest_Run_Server()
{
	return g_strSmartTestRunMode == SmartTest_Run_Mode_Server;
}
