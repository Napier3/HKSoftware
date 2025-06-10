#include "stdafx.h"
#include"VmSttMacroTest.h"

#include "../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "MacroTestFactory.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"

#ifdef _USE_SMARTTEST_INTERFACE_STT_

#ifdef _PSX_QT_LINUX_
        #include "SttMacroTestMsgRcvInterface_Linux.h"
#else
        #include "SttMacroTestMsgRcvInterface_Win.h"
#endif
#include "../SttCmd/SttChMaps.h"
#include "../Engine/SttNativeTestEngine.h"

#define ADJUST_MACROID_ADJUSTONE   _T("AdjustOne")
#define ADJUST_MACROID_ADJUSTTHREE   _T("AdjustThree")
#define ADJUST_MACROID_ADJUSTSWITCH   _T("AdjustSwitch")
#define ADJUST_MACROID_ADJUSTONECOPY   _T("AdjustOneCopy")

BOOL g_bIsSendTestCmding = FALSE;

CVmSttMacroTest::CVmSttMacroTest()
{
    //2020-11-6  lijunqing
    m_oReportBuffer.SetBufferLength(256000);
    m_oReportBuffer.AllocBuffer(0);

    //m_pTestMsgRcv = NULL;
	m_oSttTestClient.SetTestEventInterface(this);
	CSttCmdOverTimeTool::AttachCmdOverTimeMsgRcv(this);
	m_bTestStarted = FALSE;
	m_bConnected = FALSE;
	m_bStopFlag = FALSE;

#ifndef _PSX_QT_LINUX_
	m_pVmSttMacroTestSpyDlg = NULL;
#endif

	m_pSttReplayTest = NULL;
	//m_bIsSendTestCmding = FALSE;
	m_oArrSttTestCmd.SetMaxCount(20);
	m_bIsReleaseing = FALSE;
	//m_ppArray = &m_oArrSttTestCmd;
}


CVmSttMacroTest::~CVmSttMacroTest(void)
{
	m_bIsReleaseing = TRUE;

	//析构前，发送完所有需要发送的指令
	SendNextTestCmd();

	//等待最后一条指令处理完毕返回
// 	CTickCount32 oTick;
// 
// 	while (g_bIsSendTestCmding)
// 	{
// 		oTick.DoEvents(10);
// 	}

	if (m_pSttReplayTest != NULL)
	{
		delete m_pSttReplayTest;
		m_pSttReplayTest = NULL;
	}

	RemovePkgDispatchInterface(g_theNativeTestEngine);

#ifndef _PSX_QT_LINUX_
	if (m_pVmSttMacroTestSpyDlg == NULL)
	{
		return;
	}

	m_pVmSttMacroTestSpyDlg->HideSpy();
#endif
}

void CVmSttMacroTest::Release()
{
//     if(m_pTestMsgRcv == NULL)
//         return;

    if(m_oSttTestClient.GetTestEngineClient()!= NULL)
        CSttCmdOverTimeTool::Clear(m_oSttTestClient.GetTestEngineClient()->m_pSttClientSocket);

    CSttCmdOverTimeTool::AttachCmdOverTimeMsgRcv(NULL);
    m_oSttTestClient.AttachSttSocketFileTransferProgress(NULL);
    m_oSttTestClient.SetTestEventInterface(NULL);
    m_oSttTestClient.DisConnect();

// #ifdef _PSX_QT_LINUX_
//     m_pTestMsgRcv->DestroyWindow();
// #endif
// 
//         delete m_pTestMsgRcv;
//         m_pTestMsgRcv = NULL;

    CMacroTestInterface::Release();
}

void CVmSttMacroTest::SetStopFlag(BOOL bStop)
{
	m_bStopFlag = bStop;
}

void CVmSttMacroTest::OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	PostTestWndMsg(MTMSG_CommError, 0);
}

long CVmSttMacroTest::SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID)
{
//     if (m_pTestMsgRcv != NULL)
//     {
//         m_pTestMsgRcv->SetWndMsg(hMainWnd, nMsgID);
//     }

    m_hMsgWnd = hMainWnd;
    m_nMsgID = nMsgID;

	return 0;
}

CString CVmSttMacroTest::GetConfig()
{
	return _T("");
}

long CVmSttMacroTest::SetConfig(CSttTestAppCfg *pSttTestAppCfg)
{
	m_oSttTestClient.SetTestAppConfig(pSttTestAppCfg);

	return 0;
}

long CVmSttMacroTest::SetConfig(const CString & bstrConfig)
{
	m_oSttTestClient.SetTestAppConfig(bstrConfig);

	return 0;
}

BOOL CVmSttMacroTest::IsAdjust(const CString &strMacroID)
{
	//2020-10-24  lijunqing
	//测试功能的类型判断
	if (m_pTestMacro->m_strType.CompareNoCase(_T("adjust")) == 0)
	{
		return TRUE;
	}

	if (strMacroID == ADJUST_MACROID_ADJUSTTHREE || strMacroID == ADJUST_MACROID_ADJUSTONE
	 	|| strMacroID == ADJUST_MACROID_ADJUSTSWITCH || strMacroID == STT_CMD_TYPE_ADJUST_WriteFile
		|| strMacroID == ADJUST_MACROID_ADJUSTONECOPY)
	{
		return TRUE;
	}

	//此命令不会通过TestMacro调用
// 	else if (strMacroID == STT_CMD_TYPE_ADJUST_ReadDeviceParameter)
// 	{
// 		return -1;
// 	}

	return FALSE;
}

extern CString g_strSmartTestRunMode;

long CVmSttMacroTest::Test(const CString & strMacroID, const CString & strParameter)
{
	CAutoSimpleLock oLock(&m_oTestCriticSection);  //下一个测试前，必须等前一个返回。因为故障参数是成员，每个试验都会DeleteAll

	if (m_bStopFlag)
	{
		//已经接收到停止测试指令
		return -1;
	}

#ifndef _PSX_QT_LINUX_

	if ((g_strSmartTestRunMode == SmartTest_Run_Mode_Local) || g_strSmartTestRunMode.IsEmpty())
	{
		if (m_pVmSttMacroTestSpyDlg == NULL)
		{
			m_pVmSttMacroTestSpyDlg = new CVmSttMacroTestSpyDlg();

#ifdef _PSX_IDE_QT_

#else
			m_pVmSttMacroTestSpyDlg->SetUseModeless();
			m_pVmSttMacroTestSpyDlg->DoModal();
#endif
		}
	}

#endif
    //m_strReport.Empty();
    //2020-11-6  lijunqing
    m_oReportBuffer.SeekToHead();
    m_oReportBuffer.StringEnd();

	if (strMacroID != m_pTestMacro->m_strID)
	{
		return -1;
	}

	//for debug
 	if (!ConnectDevice())
 	{
         CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.. MacroID = %s, strParameter = %s"), strMacroID.GetString(), strParameter.GetString());
 
         return -1;
 	}

	//CDataGroup oDataGroup;
	BOOL bRet_SetParameter = SetParameter(m_pTestMacro, strParameter);
	long nRet = STT_CMD_ExecStatus_NULL;

	//通道映射，需要特殊处理，从固定路径下获取对应的文件，形成参数
	if (m_pTestMacro->m_strID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		if (!SetParameter_ChMapsConfig(m_oFaultParas_Dvm, strParameter))
		{
			return -1;
		}

		//nRet = m_oSttTestClient.Test_SetParameter(strMacroID, &oDataGroup);
		nRet = Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
		return 0;
	}

    //IEC61850配置，特殊处理
    if(m_pTestMacro->m_strID == STT_CMD_TYPE_SYSTEM_IECConfig)
    {
		if(!SetParameter_IECConfig(m_oFaultParas_Dvm, strParameter))
		{
				return -1;
		}

        nRet = Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
        return 0;
    }

	//系统参数配置，特殊处理
	if(m_pTestMacro->m_strID == STT_CMD_TYPE_SYSTEM_SystemConfig)
	{
		if (!bRet_SetParameter)
		{
			if(!SetParameter_SystemConfig(m_oFaultParas_Dvm, strParameter))
			{
				return -1;
			}
		}
		
        nRet = Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
		return 0;
	}

#ifndef _PSX_QT_LINUX_
	//故障回放，特殊处理
	if (m_pTestMacro->m_strID == STT_CMD_ATS_MACRO_ID_ReplayTest)
	{
		nRet = ComtradeReplayTest();

		if (nRet <= 0)
		{
			return -1;
		}

		return 0;
	}
#endif

	//校准命令特殊处理
	if (IsAdjust(strMacroID))
	{
		if (strMacroID == STT_CMD_TYPE_ADJUST_WriteFile)
		{
			nRet = m_oSttTestClient.Adjust_WriteFile(TRUE);
		}
		else
		{
			nRet = m_oSttTestClient.Adjust_Adjust(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
		}
	}
	else if (strMacroID.Find(STT_CMD_TYPE_TEST_SysDefaultOutput) >= 0)
	{
		//系统默认输出命令，特殊处理：当收到Success后，直接发送结束消息
		nRet = Test_StartTest(strMacroID, &m_oFaultParas_Dvm, TRUE, NULL, FALSE);  //同步方式

		if (Stt_Is_ExecStatus_Success(nRet))
		{
            PostTestWndMsg(MTMSG_TestFinished, 0);
		}
	}
	else
	{
		CString strID = strMacroID;
		GenGbItem_MacroID_Revise(strID);
		nRet = Test_StartTest(strID, &m_oFaultParas_Dvm, TRUE, NULL, TRUE);
	}

	return 0;
}

CString CVmSttMacroTest::GetReport()
{
// 	CString strID;
// 	strID = m_pTestMacro->m_strID;

	//此函数，暂时没有添加应答
	//long nRet = m_oClientTestEngine.Test_GetReport(strID);

	//shaolei 2021 07 29
    //所有的结果参数，均已经在m_oResults_Dvm中，此处不用再从TestMacro.xml文件中获取结果了
    //故注释，20220221
    //GetResultFromTestMacro();

    CString strReport;
    m_oReportBuffer.StringEnd();
    strReport = m_oReportBuffer.GetBuffer();
    return strReport;
}

long CVmSttMacroTest::StopTest()
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("CVmSttMacroTest---->StopTest()"));

	if (!m_oSttTestClient.IsConnectSuccess())
	{
		return 0;
	}

	long nRet = m_oSttTestClient.Test_StopTest(_T(""), TRUE, NULL, TRUE);  //shaolei  2024-4-2 改为异步

	if (nRet > 0)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug CVmSttMacroTest::StopTest()  -->m_bTestStarted=false"));
		m_bTestStarted = FALSE;
	}

	return nRet;
}

long CVmSttMacroTest::CloseDevice()
{
	return m_oSttTestClient.Test_CloseDevice();
}

CString CVmSttMacroTest::GetSearchReport()
{
	CValues oValues;
	POS pos = m_oSearchRslts.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)m_oSearchRslts.GetNext(pos);
		oValues.AddValue(pData->m_strID, pData->m_strName, pData->m_strValue);
	}

	return oValues.GetDatasString();
}

long CVmSttMacroTest::FinishTest(long nState)
{
	return 0;
}

long CVmSttMacroTest::ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter)
{
	return 0;
}

unsigned long CVmSttMacroTest::GetExternMsgRcvWnd()
{
	return 0;
}

unsigned long CVmSttMacroTest::GetExternMsgID()
{
	return 0;
}

unsigned long CVmSttMacroTest::StopDevice(void)
{
	return 0;
}

long CVmSttMacroTest::UpdateParameter(const CString &strMacroID, CDataGroup *pParas)
{
    if(pParas == NULL)
    {
        return -1;
    }

    if (!m_oSttTestClient.IsConnectSuccess())
    {
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.."), strMacroID.GetString());
        return -1;
    }

	m_oFaultParas_Dvm.InitDataValues(pParas, TRUE);  //把更新的参数，更新到故障啊参数中
    return m_oSttTestClient.Test_UpdateParameter(strMacroID, pParas);
}

long CVmSttMacroTest::ManualTrigger()
{
	ConnectDevice();

    if (!m_oSttTestClient.IsConnectSuccess())
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.."));
        return -1;
    }

    return m_oSttTestClient.Test_SendTrigger();
}

long CVmSttMacroTest::SendTestCmd(BYTE *pBuf, long nLen)
{
	ConnectDevice();

	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("++++CVmSttMacroTest::SendTestCmd++++"));
	if (!m_oSttTestClient.IsConnectSuccess())
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.."));
		return -1;
	}

	//此处指令是转发
	//pBuf是携带报文头的，应当重新拼报文头
	char* pszXmlBuffer = new char[2 * nLen + 10];
	memset(pszXmlBuffer, 0, 2 * nLen + 10);
	CSttTestCmd oTestCmd;
	oTestCmd.ParsePkgXml(pBuf,nLen, pszXmlBuffer);


	long nRet = m_oSttTestClient.SendTestCmd(&oTestCmd);//SendTestCmd(pBuf, nLen);

	delete pszXmlBuffer;
	return nRet;
}

long CVmSttMacroTest::SendTestCmd(CSttTestCmd *pTestCmd)
{
	if (pTestCmd == NULL)
	{
		return -1;
	}

	g_bIsSendTestCmding = TRUE;
	ConnectDevice();

	if (!m_oSttTestClient.IsConnectSuccess())
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">> Connect Device Failed.."));
		g_bIsSendTestCmding = FALSE;
		return -1;
	}

	//当自动测试作为19815服务时，此处为转发上位机的TestCmd指令。
	//转发的指令中，不存在StartTest指令，因此可以不考虑和其它实验冲突。
	//同步发送，函数返回即为成功、失败或超时
	long nRet = m_oSttTestClient.SendTestCmd(pTestCmd);

	g_bIsSendTestCmding = FALSE;

	return nRet;
}

long CVmSttMacroTest::SendTestCmdEx(CSttTestCmd *pTestCmd)
{
	if (m_bIsReleaseing)
	{
		return STT_CMD_ExecStatus_FAILURE;
	}

	m_oArrSttTestCmd.AddObject((CSttTestCmd *)pTestCmd->CloneEx(TRUE, TRUE));

	if (!g_bIsSendTestCmding)
	{
		return SendNextTestCmd();
	}

	return STT_CMD_ExecStatus_SUCCESS;
}

long CVmSttMacroTest::SendNextTestCmd()
{
	while (m_oArrSttTestCmd.GetCurrReadCount() > 0)
	{
		CSttTestCmd *pNextCmd = m_oArrSttTestCmd.ReadCurr();
		m_oArrSttTestCmd.FreeCurr();
		long nRet = SendTestCmd(pNextCmd);
		delete pNextCmd;
	}

	return STT_CMD_ExecStatus_SUCCESS;
}

void CVmSttMacroTest::AddPkgDispatchInterface(CSttPkgDispatchInterface *p)
{
	m_oSttTestClient.AddPkgDispatchInterface(p);
}

void CVmSttMacroTest::RemovePkgDispatchInterface(CSttPkgDispatchInterface *p)
{
	m_oSttTestClient.RemovePkgDispatchInterface(p);
}

BOOL CVmSttMacroTest::SetParameter(CTestMacro *pTestMacro, const CString & strParameter)
{
    m_oFaultParas_Dvm.DeleteAll();
    m_oResults_Dvm.DeleteAll();
    pTestMacro->GetTestMacroParas_Fault_CloneEx(&m_oFaultParas_Dvm);
    pTestMacro->GetTestMacroParas_Result_CloneEx(&m_oResults_Dvm);

    long nLen = strParameter.GetLength();

    if(nLen > 6)
    {
        CString strLeft = strParameter.Left(6);

        if(strLeft == _T("<group"))
        {
            //如果TestMacroUiParas中有参数，则可以解析成一个CDataGroup
			//并且，该参数有可能只保存了非默认值
            CDataGroup oGroup;
            BSTR bstrText = strParameter.AllocSysString();
            CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
            BOOL bRet = oGroup.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
            CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

        #ifdef _PSX_IDE_QT_
            delete bstrText;
        #else
            SysFreeString(bstrText);
        #endif

            if(bRet)
            {
				/*  //非默认值，则不能直接删除后克隆
                m_oFaultParas_Dvm.DeleteAll();
                m_oFaultParas_Dvm.AppendCloneEx(oGroup, TRUE);
				*/
				m_oFaultParas_Dvm.InitDataValues(&oGroup, TRUE);
                return TRUE;
            }
        }
    }

    CString strLeft = strParameter.Left(1);

    if(strLeft == _T("<"))
    {
        return FALSE;
    }

	CEquationBuffer *pEquation = new CEquationBuffer;
	pEquation->InitBuffer(strParameter);
	//pTestMacro->InitParas_Dvm()
	//pTestMacro->GetTestMacroParas_Fault_CloneEx(&oDataGroup);

	m_oFaultParas_Dvm.Parser(pEquation);
	delete pEquation;
	return TRUE;
}

BOOL CVmSttMacroTest::SetParameter_ChMapsConfig(CDataGroup &oDataGroup, const CString &strParameter)
{
	if (oDataGroup.GetCount() == 0 || strParameter.Left(1) == _T("<"))
	{
		return  SetParameter_ChMapsConfig_UIParas(oDataGroup, strParameter);
	}

	CDvmData *pChMapsConfigFile = (CDvmData *)oDataGroup.FindByID(STT_CMD_PARA_ChMapConfig_File);

	if (pChMapsConfigFile == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">> 通道映射配置，参数中找不到配置文件名..."));
        return  SetParameter_ChMapsConfig_UIParas(oDataGroup, strParameter);
	}

	//固定的路径
	CString strPath = _P_GetLibraryPath();
	strPath += _T("ChMapsConfig\\");

	pChMapsConfigFile->m_strValue.Replace(_T("\""), _T(""));
	CString strFile = strPath + pChMapsConfigFile->m_strValue;

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> 通道映射配置，映射文件【%s】不存在..."), strFile.GetString());
        return  SetParameter_ChMapsConfig_UIParas(oDataGroup, strParameter);
	}

	oDataGroup.DeleteAll();
    CSttChMaps *pMaps = new CSttChMaps;
    BOOL bOpen = pMaps->OpenChMapsFile(strFile);

	if (!bOpen)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T(">> 通道映射配置，映射文件【%s】打开失败..."), strFile.GetString());
		return FALSE;
	}

    //CSttChMaps *pNew = (CSttChMaps *)oMaps.CloneEx(TRUE, TRUE);
    oDataGroup.AddNewChild(pMaps);

	return TRUE;
}

BOOL CVmSttMacroTest::SetParameter_ChMapsConfig_UIParas(CDataGroup &oDataGroup, const CString &strParameter)
{
    BOOL bRet = FALSE;
    oDataGroup.DeleteAll();;

    if(strParameter.IsEmpty())
    {
        return bRet;
    }

    CSttChMaps *pMaps = new CSttChMaps;
    BSTR bstrText = strParameter.AllocSysString();
    bRet = pMaps->SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

#ifdef _PSX_IDE_QT_
    delete bstrText;
#else
    SysFreeString(bstrText);
#endif

    if(!bRet)
    {
        return FALSE;
    }

    //CSttChMaps *pNew = (CSttChMaps *)oMaps.CloneEx(TRUE, TRUE);
    oDataGroup.AddNewChild(pMaps);
    return TRUE;
}

 BOOL CVmSttMacroTest::SetParameter_IECConfig(CDataGroup &oDataGroup, const CString &strParameter)
 {
	 if(strParameter.Left(1) == _T("<"))
	 {
		 return SetParameter_IECConfig_UIParas(oDataGroup, strParameter);
	 }

     BOOL bRet = FALSE;
    CDvmData *pIecCfg_File = (CDvmData *)oDataGroup.FindByID(STT_CMD_PARA_IecCfg_File);

    if (pIecCfg_File == NULL)
    {
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">>测试仪 IECCFG配置功能测试，参数中找不到配置文件名..."));
		return FALSE;
	}

	CString strPath;
// 		strPath = _P_GetLibraryPath();
// 		strPath += _T("IEC61850Config/");

	if (pIecCfg_File->m_strValue.Find(_T(".ixml")) < 0 && pIecCfg_File->m_strValue.Find(_T(".iecfg")) < 0)
	{
		strPath = pIecCfg_File->m_strValue + _T(".ixml");
	}
	else
	{
		strPath = pIecCfg_File->m_strValue;
	}
	
	//strPath += _T(".ixml");
	CIecCfgDatasMngr *pNewCfgDatasMngr = new CIecCfgDatasMngr;
	bRet = pNewCfgDatasMngr->OpenIecCfgFile(strPath);

	if (!bRet)
	{
		return FALSE;
	}

	oDataGroup.DeleteAll();
	oDataGroup.AddNewChild(pNewCfgDatasMngr);
	return TRUE;
 }

BOOL CVmSttMacroTest::SetParameter_IECConfig_UIParas(CDataGroup &oDataGroup, const CString &strParameter)
{
	CIecCfgDatasMngr *pNewCfgDatasMngr = new CIecCfgDatasMngr;
	BSTR bstrText = strParameter.AllocSysString();
	BOOL bRet = pNewCfgDatasMngr->SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);
#endif

	if(!bRet)
	{
		return FALSE;
	}

	oDataGroup.DeleteAll();
	//CIecCfgDatasMngr *pNew = (CIecCfgDatasMngr *)oCfgDatasMngr.CloneEx(TRUE, TRUE);
	oDataGroup.AddNewChild(pNewCfgDatasMngr);

	return TRUE;
}

BOOL CVmSttMacroTest::SetParameter_SystemConfig(CDataGroup &oDataGroup, const CString &strParameter)
{
	BOOL bRet = FALSE;
	CSttMacro oSttMacro;
    oSttMacro.SetCreateMacroChild(TRUE);
	BSTR bstrText = strParameter.AllocSysString();
    bRet = oSttMacro.SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);
#endif

	if(!bRet)
	{
		return FALSE;
	}

	oDataGroup.DeleteAll();
	CSttParas *pParas = oSttMacro.GetParas();
	oDataGroup.AppendCloneEx(*pParas, TRUE);

	return TRUE;
}

BOOL CVmSttMacroTest::ConnectDevice()
{	
	if (m_oSttTestClient.IsConnectSuccess())
	{
		return TRUE;
	}

	BOOL bSucc = m_oSttTestClient.ConnectSttServer(NULL);

	if (bSucc)
	{
		CTickCount32 oTick;
		oTick.DoEvents(50);

		m_oSttTestClient.SetTestEventInterface(this);
		m_oSttTestClient.CreateSttTimer();

		//local模式下，在ConnectSttServer中已经有登陆了
		if (m_oSttTestClient.m_oTestAppCfg.IsRemote())
		{
			long nRet = System_Login();

			if (Stt_Is_ExecStatus_Success(nRet))
			{
				CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Login success"));
			}
			else
			{
				m_oSttTestClient.DisConnect();
				bSucc = FALSE;
				CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Login failed"));
			}
		}
	}

    if (bSucc)
	{
        PostTestWndMsg(MTMSG_ConnectSuccess, 0);
	}
    else
    {
        PostTestWndMsg(MTMSG_ConnectFaild, 0);
     }

    return bSucc;
}

BOOL CVmSttMacroTest::IsConnectSuccess()
{
	return m_oSttTestClient.IsConnectSuccess();
}

long CVmSttMacroTest::System_Login()
{
	return m_oSttTestClient.System_LoginEx();
}

long CVmSttMacroTest::Adjust_ReadDeviceParameter(CStringArray &astrTypes, BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug -->CVmSttMacroTest::Adjust_ReadDeviceParameter-->19814"));
	if (!m_oSttTestClient.IsConnectSuccess())
	{
		return 0;
	}

	return m_oSttTestClient.Adjust_ReadDeviceParameter(astrTypes, bDoEvents, pRetData, bSendCmdAsync);
}

void CVmSttMacroTest::PostTestWndMsg(WPARAM wParam, LPARAM lParam)
{
//     if (m_pTestMsgRcv != NULL)
//     {
//         m_pTestMsgRcv->PostTestWndMsg(wParam, lParam);
//     }

	if (!::IsWindow(((HWND)m_hMsgWnd)))
	{
		return;
	}

	::PostMessage((HWND)m_hMsgWnd, m_nMsgID, wParam, lParam);
}

long CVmSttMacroTest::Test_StartTest(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	if (m_bStopFlag)
	{
		//已经接收到停止测试指令
		return -1;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("CVmSttMacroTest---->Test_StartTest()， %s"), strMacroID.GetString());

	CTickCount32 oTick;

	//shaolei  2023-3-15 注释此处。这样有问题
	//shaolei  2024-1-16 重新开放此处。
	//原因：330机器，进入模块后，点击IEC配置，SetItemPara会立即执行。此时若还没收到TestFinished，立即点开始试验。
	//后续收到TestFinished事件时，TestControl中的当前测试项和与实际结束的项目不一致

#ifdef _PSX_QT_LINUX_    //记不得之前是啥原因注释，暂时只在linux下放开
	while (m_bTestStarted)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("for debug   --->   测试已开始--->CVmSttMacroTest::Test_StartTest   %s"), strMacroID.GetString());
		oTick.DoEvents(50);
	}
#endif

	return m_oSttTestClient.Test_StartTest(strMacroID, pParas, bDoEvents, pRetData, bSendCmdAsync);
}

long CVmSttMacroTest::ComtradeReplayTest()
{
	if (m_pSttReplayTest == NULL)
	{
		m_pSttReplayTest = new CVmSttRelayTest();
	}

	m_pSttReplayTest->SetSttTestEngineClient(m_oSttTestClient.GetTestEngineClient());

	CDvmData *pRecordFileName = (CDvmData *)m_oFaultParas_Dvm.FindByID(STT_CMD_PARA_Record_File_Name);

	if (pRecordFileName == NULL)
	{
		return -1;
	}

	CString strFile;
	strFile = pRecordFileName->m_strValue;
	strFile.Replace(_T("\""), _T(""));

	if (strFile.GetAt(1) != ':')
	{
		CString strPath = _P_GetLibraryPath();
		strPath += _T("ComtradeFile/");
		CreateAllDirectories(strPath);
		strFile = strPath + strFile;
	}

	return m_pSttReplayTest->ComtradeReplayTestStart(strFile, &m_oFaultParas_Dvm);
}

//测试功能事件接口
void CVmSttMacroTest::OnTestStarted(const CString &strMacroID, CDataGroup *pParas)
{
#ifndef _PSX_QT_LINUX_
	//后续添加获取总的测试时长消息
	if (m_pVmSttMacroTestSpyDlg != NULL)
	{
		m_pVmSttMacroTestSpyDlg->ShowSpy(0);
	}
#endif

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("MacroTestEvent-->OnTestStarted   ++  MacroID = %s"), strMacroID.GetString());
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug CVmSttMacroTest::OnTestStarted  -->m_bTestStarted=true"));
	m_bTestStarted = TRUE;

	//对于状态序列功能，进行特殊处理：根据状态数，删除多余的故障和结果参数
	CDvmData *pStateCount = (CDvmData *)m_oFaultParas_Dvm.FindByID(_T("StateCount"));

	if (pStateCount != NULL)
	{
		long nStateCount = CString_To_long(pStateCount->m_strValue);
		ResetParasByStateCount(nStateCount);
		ResetParas_RsltEvalute();
	}

	PostTestWndMsg(MTMSG_TestBegin, 0);
}

void CVmSttMacroTest::OnTestStoped(const CString &strMacroID, CDataGroup *pParas)
{
#ifndef _PSX_QT_LINUX_
	if (m_pVmSttMacroTestSpyDlg != NULL)
	{
		m_pVmSttMacroTestSpyDlg->HideSpy();
	}
#endif

	m_bTestStarted = FALSE;
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug CVmSttMacroTest::OnTestStoped  -->m_bTestStarted=false"));
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("MacroTestEvent-->OnTestStoped   ++  MacroID = %s"), strMacroID.GetString());
}

void CVmSttMacroTest::OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{
#ifndef _PSX_QT_LINUX_
	if (m_pVmSttMacroTestSpyDlg != NULL)
	{
		m_pVmSttMacroTestSpyDlg->HideSpy();
	}
#endif

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("OnTestFinished   ++  MacroID = %s"), strMacroID.GetString());
	//结束的时候发送结果上来
// 	POS pos = pResults->GetHeadPosition();
// 	CDvmData *pData = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pResults->GetNext(pos);
//         //CString strReport;
//         //strReport.Format(_T("%s=%s;"), pData->m_strID.GetString(), pData->m_strValue.GetString());
//         //m_strReport.AppendFormat(strReport);
//         //2020-11-6  lijunqing
//         m_oReportBuffer.AppendEquation(pData->m_strID.GetString(), pData->m_strValue.GetString());
// 	}

	//shaolei  20210729
	//AppendReport_ResultEx(pResults);
    //CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("<<<<<<CVmSttMacroTest::OnTestFinished<<<<<<MacroID = %s"), m_pTestMacro->m_strID.GetString());
	m_oResults_Dvm.InitDataValues(pResults, TRUE);

	//对于状态序列功能，进行特殊处理：根据状态数，删除多余的故障和结果参数
	CDvmData *pStateCount = (CDvmData *)m_oFaultParas_Dvm.FindByID(_T("StateCount"));

	if (pStateCount != NULL)
    {
		long nStateCount = CString_To_long(pStateCount->m_strValue);
		ResetParasByStateCount(nStateCount);
		ResetParas_RsltEvalute();
    }

	AppendReport_ResultEx(&m_oResults_Dvm);

	//shaolei   新平台脱机软件，需要将结果返回给网页显示，将故障参数部分也作为结果传回
#ifndef _PSX_QT_LINUX_
	//LINUX下，状态序列试验，只送结果参数
	if (m_pTestMacro->m_strID != _T("StateTest"))
	{
		AppendReport_ResultEx(&m_oFaultParas_Dvm);
	}
#else
	AppendReport_ResultEx(&m_oFaultParas_Dvm);
#endif

	PostTestWndMsg(MTMSG_TestFinished, 0);
	m_bTestStarted = FALSE;
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug CVmSttMacroTest::OnTestFinished  -->m_bTestStarted=false"));
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("MacroTestEvent-->OnTestFinished   ++  MacroID = %s"), strMacroID.GetString());
}

void CVmSttMacroTest::OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{

}

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
void CVmSttMacroTest::OnTestState(const CString &strMacroID, CDataGroup *pParas)
{
	//EVENT事件，例如开入变位等信息，需要记录到报告中
	//shaolei 2020526
// 	POS pos = pParas->GetHeadPosition();
// 	CDvmData *pData = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pParas->GetNext(pos);
// 		m_oReportBuffer.AppendEquation(pData->m_strID.GetString(), pData->m_strValue.GetString());
// 	}

	//shaolei 20210627
	POS pos = pParas->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmData *pTime = (CDvmData *)pParas->FindByID(_T("Time"));
	CDvmData *pRealTime = (CDvmData *)pParas->FindByID(_T("RealTime"));

	//2021-10-13  lijunqing
	/*CTmResultParas *pResults = (CTmResultParas *)m_pTestMacro->GetResults();*/

	while (pos != NULL)
	{
		pData = (CDvmData *)pParas->GetNext(pos);

		if (pData->m_strID == _T("Time") || pData->m_strID == _T("RealTime"))
		{
			continue;
		}

		m_oReportBuffer.AppendEquation(pData->m_strID.GetString(), pData->m_strValue.GetString());
		m_oResults_Dvm.SetDataValue(pData->m_strID, pData->m_strValue, TRUE);//2021-10-13  lijunqing

		CString strID;

		if (pTime != NULL)
		{
            strID.Format(_T("%s$%s"), pData->m_strID.GetString(), pTime->m_strID.GetString());
			m_oReportBuffer.AppendEquation(strID.GetString(), pTime->m_strValue.GetString());
			m_oResults_Dvm.SetDataValue(strID, pTime->m_strValue, TRUE);//2021-10-13  lijunqing
		}

		if (pRealTime != NULL)
		{
            strID.Format(_T("%s$%s"), pData->m_strID.GetString(), pRealTime->m_strID.GetString());
			m_oReportBuffer.AppendEquation(strID.GetString(), pRealTime->m_strValue.GetString());
			m_oResults_Dvm.SetDataValue(strID, pRealTime->m_strValue, TRUE);//2021-10-13  lijunqing
		}
	}
}

/*
<search-results name="" id="">【从CDataGroup派生】
	<data name="搜索起点" id="SearchBegin" value="0.25" />
	<data name="当前值" id="CurrSearchVal" value="0.270000011" />
	<data name="搜索终点" id="SearchEnd" value="0.75" />
	<data name="搜索区间长度" id="SearchArea" value="0.5" />
	<data name="I1(Ie)" id="TripI1Ie" value="0.735000014" />
	<data name="I1A" id="TripI1A" value="0.735000014" />
	<data name="I2(Ie)" id="TripI2Ie" value="0.729984283" />
	<data name="I2A" id="TripI2A" value="0.729984283" />
</search-results>
*/
void CVmSttMacroTest::OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults)
{
	m_oSearchRslts.DeleteAll();
	m_oSearchRslts.AppendCloneEx(*pSearchResults, TRUE);

	//记录搜索结果，发送消息给自动测试。自动测试收到消息后，会来获取结果
	PostTestWndMsg(MTMSG_SearchPointReport, 0);
}

void CVmSttMacroTest::OnReport(CDataGroup *pParas)
{
	//这个函数不会被调用
// 	POS pos = pParas->GetHeadPosition();
// 	CDvmData *pData = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pParas->GetNext(pos);
// 		CString strReport;
// 		strReport.Format(_T("%s=%s;"), pData->m_strID, pData->m_strValue);
// 		m_strReport.AppendFormat(strReport);
// 	}
}

//#include "../../Native/Module/SttNativeTestMainApp.h"
//ret-type="REPORT" id-cmd="test-cmd"
/*
<sys-state name="" id="StartTest" mid="0" time="1970-01-01 00:00:00" mater-host="" ret-type="REPORT" id-cmd="test-cmd">
	<paras name="" id="">
		<data name="ExecStatus" id="ExecStatus" data-type="string" default-value="" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	</paras>
	<macro name="" id="" version="" type="" remark="">
		<results name="" id="">
			<group id="state0" data-type="State">
				<data id="TtripBin1" value="0" />
				<data id="TtripBin2" value="0" />
				……
				<data id="RampStepIndexBin8" value="-1" />
				<group id="ActRcd" data-type="ActRcd" />
			</group>
			<group id="state1" data-type="State">
				<data id="TtripBin1" value="0" />
				<data id="TtripBin2" value="0" />
				……
				<data id="RampStepIndexBin8" value="-1" />
				<group id="ActRcd" data-type="ActRcd" />
			</group>
			<group id="state2" data-type="State">
				<data id="TtripBin1" value="0" />
				<data id="TtripBin2" value="0" />
				……
				<data id="RampStepIndexBin8" value="-1" />
				<group id="ActRcd" data-type="ActRcd" />
			</group>
		</results>
	</macro>
</sys-state>
*/
void CVmSttMacroTest::OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas)
{
	if (pParas->m_strID == STT_CMD_TYPE_ADJUST_ReadDeviceParameter)
	{
		stt_OnReport_ReadDeviceParameter(pParas);
// 		m_oReadDeviceParameter.DeleteAll();
// 		m_oReadDeviceParameter.AppendCloneEx2(*pParas);
		return;
	}

	if (m_pTestMacro == NULL)
	{
		return;
	}

	//状态序列功能，重复测试时，每个REPORT都需要发送ats-cmd的REPORT事件；
	if (m_pTestMacro->m_strID != _T("StateTest"))
	{
		return;
	}

	CDvmData *pRepeatTimes = (CDvmData *)m_oFaultParas_Dvm.FindByID(_T("_RepeatNumbers"));

	if (pRepeatTimes == NULL)
	{
		return;
	}

	long nRepeatTimes = CString_To_long(pRepeatTimes->m_strValue);

	if (nRepeatTimes <= 0)
	{
		return;
	}

	CSttSysState oSysState;
	CSttParas *pRtParas = oSysState.GetSttParas();
	oSysState.SetReporting();
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ATS;
	CSttReports *pSttReports = pRtParas->GetSttReports(TRUE);
	CSttReport *pRpt = new CSttReport;
	pRpt->m_strID = _T("_RepeatTest_Rpt_");
	pSttReports->AddNewChild(pRpt);
	pRpt->InitValues(NULL);
	CDvmValues *pValues = pRpt->m_pValues;
	pRtParas->AddNewData(STT_CMD_PARA_ItemPath, m_strItemPath);;

	CSttSysState *pState = (CSttSysState *)pParas->GetParent();
	CSttMacro *pMacro = pState->GetSttMacro();
	CSttResults *pResults = pMacro->GetResults();
	CExBaseList oList;
	pResults->SelectAllDatas(oList);//这个链表中的参数暂时不带路径信息

	POS pos = oList.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)oList.GetNext(pos);
	 	CDvmValue *pNew = new CDvmValue();
	 	pNew->m_strID = pData->GetIDPathEx(pResults);
		pNew->m_strName = pData->GetNamePathEx(pResults);
	 	pNew->m_strValue = pData->m_strValue;
		pValues->AddNewChild(pNew);
	}

	oList.RemoveAll();

#ifndef _PSX_QT_LINUX_
	AppendReport_ResultEx(pValues, &m_oFaultParas_Dvm);
#else
	////装置序列，报告不传故障参数部分，由上位机自行处理
	//AppendReport_ResultEx(pValues, &m_oFaultParas_Dvm);
#endif

	oSysState.Set_Xml_Pkg_With_Name(TRUE);

	if (g_theNativeTestEngine != NULL)
	{
		g_theNativeTestEngine->X_ReturnSysStateToChildren(NULL,  &oSysState);
	}

	oSysState.Set_Xml_Pkg_With_Name(FALSE);
}

long CVmSttMacroTest::OnAts_Stop(CDataGroup *pParas)
{
	//shaolei 20210526  测试仪急停事件
	//暂时先发送通讯错误消息
	char strIP[20] = {0};
	CSttTestEngineClientData* pEngine = m_oSttTestClient.GetTestEngineClient();
	pEngine->m_pSttClientSocket->get_LocalIP(strIP);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("测试仪【%s】急停！自动测试停止测试！"), strIP);
	PostTestWndMsg(MTMSG_CommError, 0);
	m_bTestStarted = FALSE;
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug CVmSttMacroTest::OnAts_Stop  -->m_bTestStarted=false"));
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("MacroTestEvent-->OnAts_Stop"));
	return 0;
}

void CVmSttMacroTest::SetConfig_TestApp()
{
	if (m_pSttTestApp == NULL)
	{
		return;
	}

	SetConfig(m_pSttTestApp);
}

void CVmSttMacroTest::GetParaIDPath(CString &strPath, CDvmData *pData)
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

        strTemp.Format(_T("%s$"), pParent->m_strID.GetString());
		strPath = strTemp + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent == NULL)
		{
			break;
		}

		if (pParent->m_strID.IsEmpty())
		{
			break;
		}

// 		if (pParent->GetClassID() != STTCMDCLASSID_CSTTRESULTS)
// 		{
// 			break;
// 		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - 1;
		strPath = strPath.Left(nLen);
	}
}

void CVmSttMacroTest::GetParaNamePath(CString &strPath, CDvmData *pData)
{
	strPath.Empty();
	CExBaseObject *pParent = pData;
	CString strTemp;

	while (pParent != NULL)
	{
		if (pParent->m_strName.GetLength() == 0)
		{
			break;
		}

		strTemp.Format(_T("%s$"), pParent->m_strName.GetString());
		strPath = strTemp + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent == NULL)
		{
			break;
		}

		if (pParent->m_strName.IsEmpty())
		{
			break;
		}

		// 		if (pParent->GetClassID() != STTCMDCLASSID_CSTTRESULTS)
		// 		{
		// 			break;
		// 		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - 1;
		strPath = strPath.Left(nLen);
	}
}

//形参为测试仪底层返回的结果数据的group
void CVmSttMacroTest::AppendReport_ResultEx(CDataGroup *pRsltGroup)
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

        if(nClassID  != DVMCLASSID_CDVMDATA)
            continue;

		pData = (CDvmData *)pObj;
		CString strID;
		GetParaIDPath(strID, pData);

		m_oReportBuffer.AppendEquation(strID.GetString(), pData->m_strValue.GetString());
	}
}

void CVmSttMacroTest::AppendReport_ResultEx(CDvmValues *pValues, CDataGroup *pRsltGroup)
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
			AppendReport_ResultEx(pValues, pGroup);
			continue;
		}

		if(nClassID  != DVMCLASSID_CDVMDATA)
			continue;

		pData = (CDvmData *)pObj;
		CString strID, strName;
		GetParaIDPath(strID, pData);
		GetParaNamePath(strName, pData);

		CDvmValue *pNew = new CDvmValue();
		pNew->m_strID = strID;
		pNew->m_strName = strName;
		pNew->m_strValue = pData->m_strValue;
		pValues->AddNewChild(pNew);
	}
}

void CVmSttMacroTest::GetResultFromTestMacro()
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

void CVmSttMacroTest::GenGbItem_MacroID_Revise(CString &strMacroID)
{
	if (strMacroID == STT_CMD_ATS_MACRO_ID_GradientTest)
	{
		long nVarType, nVaryMode = 0;
		m_oFaultParas_Dvm.GetDataValue(STT_CMD_PARA_VarType, nVarType);
		m_oFaultParas_Dvm.GetDataValue(STT_CMD_PARA_VaryMode, nVaryMode);

		if (nVarType == 1 && nVaryMode == 2)
		{
			strMacroID = STT_CMD_ATS_MACRO_ID_GradientMaxAngleTest;
		}
	}
}

void CVmSttMacroTest::ResetParasByStateCount(long nStateCount)
{
	ResetParasByStateCount(&m_oFaultParas_Dvm, nStateCount);
	//ResetParasByStateCount(&m_oResults_Dvm, nStateCount);
}

void CVmSttMacroTest::ResetParasByStateCount(CDataGroup *pParas, long nStateCount)
{
	long nStateNum = -1;
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	POS pos = pParas->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pParas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		CDataGroup *pGrp = (CDataGroup *)pObj;
		long nPos = pGrp->m_strID.Find(_T("state"));

		if (nPos != 0)
		{
			continue;
		}

		CString strID = pGrp->m_strID.Mid(nPos + 5);
		//对于6.3的StateTest6U6I功能，状态序列的ID是从1开始：state1、state2...
		//所以此处注释掉“+ 1”。防止删掉最后一个状态的结果数据。
		//这样，对于ID是从0开始的状态序列：state0、state1。会多出一个状态的结果数据。
		nStateNum = CString_To_long(strID)/* + 1*/; 

		if (nStateNum > nStateCount)
		{
			m_oResults_Dvm.DeleteByID(pGrp->m_strID);   //结果参数删除对应的参数
			pParas->Delete(pGrp);
		}
	}
}

void CVmSttMacroTest::ResetParas_RsltEvalute()
{
	CDataGroup *pRlstEvalueGrp = (CDataGroup *)m_oFaultParas_Dvm.FindByID(_T("rslt_evaluation"));
	CDataGroup *pRlstEvalueGrpRslt = (CDataGroup *)m_oResults_Dvm.FindByID(_T("rslt_evaluation"));

	if (pRlstEvalueGrp == NULL)
	{
		return;
	}

	CDataGroup *pRsltEvasluteChild = NULL;
	POS pos = pRlstEvalueGrp->GetHeadPosition();
	CDvmData *pUseError = NULL;

	while (pos != NULL)
	{
		pRsltEvasluteChild = (CDataGroup *)pRlstEvalueGrp->GetNext(pos);
		pUseError = (CDvmData *)pRsltEvasluteChild->FindByID(_T("UseError"));

		if (pUseError == NULL)
		{
			continue;
		}

		if (CString_To_long(pUseError->m_strValue) == 0)
		{
			if (pRlstEvalueGrpRslt != NULL)
			{
				pRlstEvalueGrpRslt->DeleteByID(pRsltEvasluteChild->m_strID);
			}

			pRlstEvalueGrp->Delete(pRsltEvasluteChild);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//
CSttMacroTestCreator::CSttMacroTestCreator()
{

}

CSttMacroTestCreator::~CSttMacroTestCreator()
{

}

CMacroTestEngineInterface* CSttMacroTestCreator::CreateMacroTestEngine(const CString &strMacroFile)
{

	return NULL;
}

CMacroTestEngineInterface* CSttMacroTestCreator::GetMacroTestEngine(const CString &strType, const CString &strProgID, const CString &strMacroFile)
{

	return NULL;
}

CMacroTestInterface* CSttMacroTestCreator::GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps)
{
	CString strActiveMacroTestEngineProgID;
	strActiveMacroTestEngineProgID = CTestMacrosFileMngr::GetActiveMacroTestProgID(strMacroFile, strType);

	CString strID;
	strID = strActiveMacroTestEngineProgID ;//+ strTestAppGroup;
	CVmSttMacroTest *pSttMacroTest = (CVmSttMacroTest*)SttFindByID(strID);

	if (pSttMacroTest == NULL)
	{
		pSttMacroTest = new CVmSttMacroTest();

// #ifdef _PSX_QT_LINUX_
//         pSttMacroTest->m_pTestMsgRcv = new CSttMacroTestMsgRcvInterface_Linux();
// #else
//         pSttMacroTest->m_pTestMsgRcv = new CSttMacroTestMsgRcvInterface_Win();
// #endif

		BOOL bFirstCreate = FALSE;
		AddNewChild(pSttMacroTest);
		pSttMacroTest->m_strID = strID;
	}

	//20210515 shaolei
	CSttTestAppCfg* pApp = CSttTestApps::g_pSttTestApps->FindByType(strType);
	pSttMacroTest->m_pSttTestApp = pApp;
	pSttMacroTest->SetConfig_TestApp();

	return pSttMacroTest;
}

void CSttMacroTestCreator::InitMacroTestEngineShowSpyWnd()
{

}

void CSttMacroTestCreator::ReleaseMacroTestEngine()
{
	POS pos = GetHeadPosition();
	CVmSttMacroTest *pSttMacroTest = NULL;

	while (pos != NULL)
	{
		pSttMacroTest = (CVmSttMacroTest *)GetNext(pos);
		pSttMacroTest->CloseDevice();
        pSttMacroTest->m_oSttTestClient.SetTestEventInterface(NULL);
		pSttMacroTest->m_oSttTestClient.DisConnect();
	}

	DeleteAll();
}

void CSttMacroTestCreator::ReleaseMacroTestEngine(const CString &strProgID)
{
	CVmSttMacroTest *pMacroTest = (CVmSttMacroTest*)SttFindByID(strProgID);

	if (pMacroTest != NULL)
	{
		pMacroTest->CloseDevice();
		pMacroTest->m_oSttTestClient.DisConnect();
		Delete(pMacroTest);
	}
}

void CSttMacroTestCreator::ShowSpyWnd()
{

}

void CSttMacroTestCreator::ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara)
{

}

long CSttMacroTestCreator::ConfigEngine(const CString &strMacroFile, const CString &strIP)
{
	return 0;
}

long CSttMacroTestCreator::AttatchLogWnd(unsigned long hWnd)
{
// 	POS pos = GetHeadPosition();
// 	CSttMacroTest *pSttMacroTest = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pSttMacroTest = (CSttMacroTest *)GetNext(pos);
// 		pSttMacroTest->AttatchLogWnd(hWnd);
// 	}

	m_hLogWnd = hWnd;

	return 0;
}

#endif  //#ifdef _USE_SMARTTEST_INTERFACE_STT_
