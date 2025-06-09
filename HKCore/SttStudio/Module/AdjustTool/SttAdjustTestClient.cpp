//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjustTestClient.cpp  CSttAdjustTestClient


#include "stdafx.h"
#include "SttAdjustTestClient.h"

#include "..\..\..\Module\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttAdjustTestClient::CSttAdjustTestClient()
{
// 	m_pFaultParas_ModuleOutput = new CDataGroup();
// 	m_pResults_ModuleOutput = new CDataGroup();
// 
// 	m_pFaultParas_Adjust = new CDataGroup();
// 	m_pResults_Adjust = new CDataGroup();

	m_pAdjModuleOutput = new CSttAdjTest_ModuleOutput();
	m_pAdjModuleAdjust = new CSttAdjTest_AdjustOne();
	m_pAdjustSwitch = new CSttAdjTest_AdjustSwitch();
	m_pAdjModuleAdjustThree = new CSttAdjTest_AdjustThree();

	m_pAdjustOne2Points = new CSttAdjTest_AdjustOne2Points();
	m_pAdjustOneAngle = new CSttAdjTest_AdjustOneAngle();
	m_pAdjustOneFreq = new CSttAdjTest_AdjustOneFreq();
	m_pAdjustOneDcZero = new CSttAdjTest_AdjustOneDcZero();

	m_pMeasRcvWnd = NULL;
}

CSttAdjustTestClient::~CSttAdjustTestClient()
{
	delete m_pAdjModuleOutput;
	delete m_pAdjModuleAdjust;
	delete m_pAdjustSwitch;
	delete m_pAdjModuleAdjustThree;


	delete m_pAdjustOne2Points;
	delete m_pAdjustOneAngle;
	delete m_pAdjustOneFreq;
	delete m_pAdjustOneDcZero;
}

void CSttAdjustTestClient::InitTestMacros(CTestMacros*pTestMacros)
{
	m_pAdjustTestMacros = pTestMacros;

    InitModuleOutput(STT_ADJUST_MACRO_ID_ModuleOutput);
	InitAdjustTestItem(STT_ADJUST_MACRO_ID_AdjustOne);
	InitAdjustSwitch(STT_ADJUST_MACRO_ID_AdjustSwitch);
	InitAdjustThree(STT_ADJUST_MACRO_ID_AdjustThree);

	InitTestMacro(STT_ADJUST_MACRO_ID_AdjustOne2Points, m_pAdjustOne2Points);
	InitTestMacro(STT_ADJUST_MACRO_ID_AdjustOneAngle, m_pAdjustOneAngle);
	InitTestMacro(STT_ADJUST_MACRO_ID_AdjustOneFreq, m_pAdjustOneFreq);
	InitTestMacro(STT_ADJUST_MACRO_ID_AdjustOneDcZero, m_pAdjustOneDcZero);
}

void CSttAdjustTestClient::InitModuleOutput(const CString &strAdjMacroID)
{
	CTestMacro *p = (CTestMacro *)m_pAdjustTestMacros->FindByID(strAdjMacroID);
	m_pAdjModuleOutput->SetTestMacro(p);

}

void CSttAdjustTestClient::InitAdjustTestItem(const CString &strAdjMacroID)
{
	CTestMacro *p =  (CTestMacro *)m_pAdjustTestMacros->FindByID(strAdjMacroID);
	m_pAdjModuleAdjust->SetTestMacro(p);
}

void CSttAdjustTestClient::InitAdjustSwitch(const CString &strAdjMacroID)
{
	CTestMacro *p =  (CTestMacro *)m_pAdjustTestMacros->FindByID(strAdjMacroID);
	m_pAdjustSwitch->SetTestMacro(p);
}

void CSttAdjustTestClient::InitAdjustThree(const CString &strAdjMacroID)
{
	CTestMacro *p =  (CTestMacro *)m_pAdjustTestMacros->FindByID(strAdjMacroID);
	m_pAdjModuleAdjustThree->SetTestMacro(p);
}

//2021-9-22  lijunqing
void CSttAdjustTestClient::InitTestMacro(const CString &strAdjMacroID, CSttAdjTest_Base *pAdjTest)
{
	CTestMacro *p =  (CTestMacro *)m_pAdjustTestMacros->FindByID(strAdjMacroID);

	if (p == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("MacroID [%s] is not exist"), strAdjMacroID);
		return;
	}

	pAdjTest->SetTestMacro(p);
}

void CSttAdjustTestClient::TestConfig()
{
	CSttAdjustTestClient::ConfigTest(NULL);
}

void CSttAdjustTestClient::ModuleOutput()
{
	m_pAdjModuleOutput->WriteParasFile();

	Test_StartTest(STT_ADJUST_MACRO_ID_ModuleOutput
		, m_pAdjModuleOutput->m_pFaultParas, TRUE, NULL);//m_pAdjModuleAdjust->m_pResults);
}


BOOL CSttAdjustTestClient::AdjustTest()
{
	m_pAdjModuleAdjust->WriteParasFile();

	long nRet = Adjust_Adjust(STT_ADJUST_MACRO_ID_AdjustOne
		, m_pAdjModuleAdjust->m_pFaultParas, TRUE, NULL);//m_pAdjModuleAdjust->m_pResults);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttAdjustTestClient::AdjustMoudleParasCmdSend(CDataGroup *pMoudleDataGroup, const CString &strMacroID)
{
	long nRet = Adjust_Adjust(strMacroID, pMoudleDataGroup, TRUE, NULL);

	if(Stt_Is_ExecStatus_Success(nRet))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttAdjustTestClient::AdjustFPGAUpdate(CDataGroup *pMoudleDataGroup)
{
	long nRet = Test_StartTest(STT_ADJUST_MACRO_ID_FPGAUPDATE
		, pMoudleDataGroup, TRUE, NULL);
	if(Stt_Is_ExecStatus_Success(nRet))
	{
		return TRUE;
	}
	return FALSE;
}

//BOOL CSttAdjustTestClient::AdjustReadCoefficent(CDataGroup *pMoudleDataGroup)
//{
//	long nRet = Adjust_Adjust(STT_ADJUST_MACRO_ID_ReadMoudleFlash
//		, pMoudleDataGroup, TRUE, NULL);
//	if(Stt_Is_ExecStatus_Success(nRet))
//	{
//		return TRUE;
//	}
//	return FALSE;
//}
//
//BOOL CSttAdjustTestClient::AdjustWriteCoefficent(CDataGroup *pMoudleDataGroup)
//{
//	long nRet = Adjust_Adjust(STT_ADJUST_MACRO_ID_WriteMoudleFlash
//		, pMoudleDataGroup, TRUE, NULL);
//	if(Stt_Is_ExecStatus_Success(nRet))
//	{
//		return TRUE;
//	}
//	return FALSE;
//}
//
//BOOL CSttAdjustTestClient::AdjustSetUTC(CDataGroup *pUTCTime)
//{
//	long nRet = Adjust_Adjust(STT_ADJUST_MACRO_ID_SetUTCTime
//		, pUTCTime, TRUE, NULL);
//	if(Stt_Is_ExecStatus_Success(nRet))
//	{
//		return TRUE;
//	}
//	return FALSE;
//}
//
//BOOL CSttAdjustTestClient::AdjustGetUTC()
//{
//	long nRet = Adjust_Adjust(STT_ADJUST_MACRO_ID_GetUTCTime,NULL,TRUE,NULL);
//	if (Stt_Is_ExecStatus_Success(nRet))
//	{
//		return TRUE;
//	}
//
//	return FALSE;
//}


BOOL CSttAdjustTestClient::AdjustThree()
{
	m_pAdjModuleAdjustThree->WriteParasFile();

	long nRet = Adjust_Adjust(STT_ADJUST_MACRO_ID_AdjustThree
		, m_pAdjModuleAdjustThree->m_pFaultParas, TRUE, NULL);//m_pAdjModuleAdjustThree->m_pResults);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		return TRUE;
	}

	return FALSE;
}


BOOL CSttAdjustTestClient::WriteFile()
{
	long nRet = Adjust_WriteFile();

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttAdjustTestClient::AdjustSwitch()
{
	m_pAdjustSwitch->WriteParasFile();

	long nRet = Adjust_Adjust(STT_ADJUST_MACRO_ID_AdjustSwitch,
		m_pAdjustSwitch->m_pFaultParas, TRUE, NULL);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttAdjustTestClient::SttSystemConfig(CDataGroup *pParas,BOOL bSendCmdAsync, BOOL bDoEvents)
{
	CString strFile;
	strFile = _P_GetBinPath();
	strFile += STT_TEST_MACROID_SttSystemConfig;
	strFile += _T(".xml");
	pParas->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	long nRet = Test_StartTest(STT_TEST_MACROID_SttSystemConfig,
		pParas, bDoEvents, NULL, bSendCmdAsync);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		return TRUE;
	}

	return FALSE;
}

long CSttAdjustTestClient::AdjustWriteFile(const CString &strLocalFile)
{//写配置
	CString strFileName;
	strFileName = STT_ADJ_SYS_FILE_NAME;
	strFileName.MakeLower();
	long nPos = strLocalFile.Find(strFileName);
	CString strDestFile;

	//确保传到机器的文件，其文件名为DeviceSystemParas.xml；
	//shaolei 20210717 
	if (nPos < 0)
	{
		strDestFile = _P_GetConfigPath();
		strDestFile += _T("WriteFile\\");
		CreateAllDirectories(strDestFile);
		strDestFile += STT_ADJ_SYS_FILE_NAME;
		
		X_CopyFile(strLocalFile, strDestFile, FALSE);
	}
	else
	{
		strDestFile = strLocalFile;
	}

	CString strRemoteFile;
	//如果是PC端调试，需用"Config\\%s",如果是测试仪，需要"Config/%s"
	strRemoteFile.Format(_T("Config/%s"),STT_ADJ_SYS_FILE_NAME);
	return Write(strDestFile,strRemoteFile,GetFileTransferProgress());
}
long CSttAdjustTestClient::AdjustSendFile(const CString &strLocalFile,const CString &strRemoteFile)
{
	return Write(strLocalFile,strRemoteFile,GetFileTransferProgress());
}

void CSttAdjustTestClient::StopTest()
{
	Test_StopTest(STT_ADJUST_MACRO_ID_ModuleOutput);
}

void CSttAdjustTestClient::CloseDevice()
{
	Test_CloseDevice();
}

long CSttAdjustTestClient::AdjustReadFile(const CString &strLocalPath)
{//读配置
	CString strLocalFile;
	strLocalFile.Format(_T("%sDeviceSystemParas.xml"),strLocalPath);

	//如果是PC端调试，需用"Config\\%s",如果是测试仪，需要"Config/%s"
	CString strRemoteFile = _T("Config/DeviceSystemParas.xml");
	return ReadFile(strLocalFile,strRemoteFile,GetFileTransferProgress());
}

void CSttAdjustTestClient::ConfigTest(CSttTestAppConfigTool *pTool)
{
	CSttTestClientBase::ConfigTest(pTool);
	//CSttTestEngineClientData *pXClientEngine = GetTestEngineClient();
	//pTool->TestAppConfig(&pXClientEngine, this, AfxGetMainWnd());
}

//2021-9-28  lijunqing
BOOL CSttAdjustTestClient::Adjust(CSttAdjTest_Base *pAdjustTest, const CString &strMacroID)
{
	pAdjustTest->WriteParasFile();

	long nRet = Adjust_Adjust(strMacroID
		, pAdjustTest->m_pFaultParas, TRUE, NULL);

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttAdjustTestClient::AdjustOne2Points()
{
	return Adjust(m_pAdjustOne2Points, STT_ADJUST_MACRO_ID_AdjustOne2Points);
}

BOOL CSttAdjustTestClient::AdjustOneAngle()
{
	return Adjust(m_pAdjustOneAngle, STT_ADJUST_MACRO_ID_AdjustOneAngle);
}

BOOL CSttAdjustTestClient::AdjustOneFreq()
{
	return Adjust(m_pAdjustOneFreq, STT_ADJUST_MACRO_ID_AdjustOneFreq);
}

BOOL CSttAdjustTestClient::AdjustOneDcZero()
{
	return Adjust(m_pAdjustOneDcZero, STT_ADJUST_MACRO_ID_AdjustOneDcZero);
}

BOOL CSttAdjustTestClient::Meas_Read()
{
	long nRet = CSttTestClientBase::Meas_Read();

	if (Stt_Is_ExecStatus_Success(nRet))
	{
		return TRUE;
	}

	return FALSE;
}

//测试功能事件接口
void CSttAdjustTestClient::OnTestStarted(const CString &strMacroID, CDataGroup *pParas)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s  TestStarted"), strMacroID);
}

void CSttAdjustTestClient::OnTestStoped(const CString &strMacroID, CDataGroup *pParas)
{

}

void CSttAdjustTestClient::OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s  TestFinished"), strMacroID);
	POS pos = pResults->GetHeadPosition();
	CDvmData *pData = NULL;
	CString strLog;

	while (pos != NULL)
	{
		pData = (CDvmData *)pResults->GetNext(pos);
		strLog.AppendFormat(_T("%s = %s;\r\n"), pData->m_strID, pData->m_strValue);
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
}

void CSttAdjustTestClient::OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{

}

void CSttAdjustTestClient::OnTestState(const CString &strMacroID, CDataGroup *pParas)
{

}

long CSttAdjustTestClient::OnMeas(CDataGroup *pParas)
{
	if (m_pMeasRcvWnd != NULL)
	{
		m_pMeasRcvWnd->PostMessage(WM_MEAS_DATA, (LPARAM)&m_oMeasData, (LPARAM)&m_oMeasData);
	}

	return 0;
}

