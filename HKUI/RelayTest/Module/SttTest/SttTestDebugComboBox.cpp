// BaseListComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SttTestDebugComboBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// CSttTestDebugComboBox
CSttTestDebugComboBox::CSttTestDebugComboBox()
{
	m_pFilterTextMngr = NULL;
}

CSttTestDebugComboBox::~CSttTestDebugComboBox()
{
	if (m_pFilterTextMngr != NULL)
	{
		delete m_pFilterTextMngr;
		m_pFilterTextMngr = NULL;
	}
}


void CSttTestDebugComboBox::InitSttTestDebugComboBox()
{
	if (m_pFilterTextMngr == NULL)
	{
		m_pFilterTextMngr = new CFilterTextMngr();
		CString strFile;
		strFile = _P_GetLibraryPath();
		strFile += _T("SttTestDebugParaFiles.xml");
		m_pFilterTextMngr->OpenXmlFile(strFile);
	}

	ShowBaseList(m_pFilterTextMngr);;
}

void CSttTestDebugComboBox::GetSttTestDebugParaText(CString &strParaText)
{
	CString strTextFile;
	BOOL b = GetCurrSelFilterText(strTextFile);

	if (!b)
	{
		strParaText.Empty();
		return;
	}

	Stt_GetSttTestDebugParaText(strTextFile,strParaText);
}

#include "../SttGlobalDef.h"

void stt_InitSysCmdCmboBox(CComboBox *pComboBox)
{
	//系统命令
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_SetSysConfig);//_T("SetSysConfig")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_GetSysConfig);//_T("GetSysConfig")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_Login);//_T("Login")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_Logout);//_T("Logout")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_Request);//_T("Request")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_GetDirs);//_T("GetDirs")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_DownFile);//_T("DownFile")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_DeleteFile);//_T("DeleteFile")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_DownFolder);//_T("DownFolder")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_DeleteFolder);//_T("DeleteFolder")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_CreateFolder);//_T("CreateFolder")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_LiveUpdate);//_T("LiveUpdate")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_Authority);//_T("Authority")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_NativeAuthority);//_T("NativeAuthority")

	//测试控制命令
	pComboBox->AddString( STT_CMD_TYPE_TEST_SetParameter);//_T("SetParameter")
	pComboBox->AddString( STT_CMD_TYPE_TEST_UpdateParameter);//_T("UpdateParameter")
	pComboBox->AddString( STT_CMD_TYPE_TEST_StartTest);//_T("StartTest")
	pComboBox->AddString( STT_CMD_TYPE_TEST_StopTest);//_T("StopTest")
	pComboBox->AddString( STT_CMD_TYPE_TEST_GetReport);//_T("GetReport")
	pComboBox->AddString( STT_CMD_TYPE_TEST_CloseDevice);//_T("CloseDevice")
	pComboBox->AddString( STT_CMD_TYPE_SYSTEM_GetSystemState);//_T("GetSystemState")

	//内部调试命令
	pComboBox->AddString( STT_CMD_TYPE_DEBUG_GetProcessState);//_T("GetProcessState")
	pComboBox->AddString( STT_CMD_TYPE_DEBUG_GetMemState);//_T("GetMemState")
	pComboBox->AddString( STT_CMD_TYPE_DEBUG_GetTestParas);//_T("GetTestParas")
	pComboBox->AddString( STT_CMD_TYPE_DEBUG_GetBasicTestParas);//_T("GetBasicTestParas")
	pComboBox->AddString( STT_CMD_TYPE_DEBUG_GetFpgaData);//_T("GetFpgaData")
	pComboBox->AddString( STT_CMD_TYPE_DEBUG_GetSocketConnect);//_T("GetSocketConnect")
	pComboBox->AddString( STT_CMD_TYPE_DEBUG_ConfigDebug);//_T("ConfigDebug")

	//远程控制命令
	pComboBox->AddString( STT_CMD_TYPE_REMOTE_Register);//_T("Register")
	pComboBox->AddString( STT_CMD_TYPE_REMOTE_UnRegister);//_T("UnRegister")
	pComboBox->AddString( STT_CMD_TYPE_REMOTE_Query);//_T("Query")
	pComboBox->AddString( STT_CMD_TYPE_REMOTE_Bind);//_T("Bind")

	//自动测试命令
	pComboBox->AddString( STT_CMD_TYPE_ATS_CreateTest);//_T("CreateTest")
	pComboBox->AddString( STT_CMD_TYPE_ATS_StartTest);//_T("StartTest")
	pComboBox->AddString( STT_CMD_TYPE_ATS_StopTest);//_T("StopTest")
	pComboBox->AddString( STT_CMD_TYPE_ATS_TestItem);//_T("TestItem")
	pComboBox->AddString( STT_CMD_TYPE_ATS_TestFrom);//_T("TestFrom")
	pComboBox->AddString( STT_CMD_TYPE_ATS_TestAllFailedItems);//_T("TestAllFailedItems")
	pComboBox->AddString( STT_CMD_TYPE_ATS_GetItemReport);//_T("GetItemReport")
	pComboBox->AddString( STT_CMD_TYPE_ATS_GetReportFile);//_T("GetReportFile")
	pComboBox->AddString( STT_CMD_TYPE_ATS_GetSystemState);//_T("GetSystemState")

	//远程协助命令
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_GetTestParas);//_T("GetTestParas")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_SetTestParas);//_T("SetTestParas")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_StartTest);//_T("StartTest")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_StopTest);//_T("StopTest")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_SelectTestMacro);//_T("SelectTestMacro")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_RunExe);//_T("RunExe")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_ImportDvmFile);//_T("ImportDvmFile")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_ReadDataset);//_T("ReadDataset")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_WriteDataset);//_T("WriteDataset")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_Reset);//_T("Reset")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_ReadSetZone);//_T("ReadSetZone")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_WriteSetZone);//_T("WriteSetZone")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_StartReport);//_T("StartReport")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_StopReport);//_T("StopReport")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_CreateDevcie);//_T("CreateDevcie")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_EnumDevice);//_T("EnumDevice")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_EnumLdevice);//_T("EnumLdevice")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_EnumDataset);//_T("EnumDataset")
	pComboBox->AddString( STT_CMD_TYPE_ASSIST_SelectDvmNode);//_T("SelectDvmNode")
}

void Stt_GetSttTestDebugParaText(const CString &strFileName,CString &strParaText)
{
	CString strTextFile = strFileName;

	if (strFileName.IsEmpty())
	{
		strParaText.Empty();
		return;
	}

	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += strTextFile;
	CFile oFile;

	if (!oFile.Open(strFile, CFile::modeRead))
	{
		strParaText.Empty();
		return;
	}

	long nLen = oFile.GetLength();
	char *pBuffer = new char [nLen + 5];
	oFile.Read(pBuffer, nLen);
	pBuffer[nLen] = 0;
	strParaText = pBuffer;
	delete pBuffer;
	oFile.Close();
}