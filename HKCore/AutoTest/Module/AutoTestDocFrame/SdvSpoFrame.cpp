// SclFileFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "SdvSpoFrame.h"
#include "..\TestControl/AtsNewTestTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSclFileFrame

IMPLEMENT_DYNCREATE(CSdvSpoFrame, CAutoTestBaseFrame)

CSdvSpoFrame::CSdvSpoFrame()
{
	
}

CSdvSpoFrame::~CSdvSpoFrame()
{

}


BEGIN_MESSAGE_MAP(CSdvSpoFrame, CAutoTestBaseFrame)
END_MESSAGE_MAP()


// CSclFileFrame 消息处理程序
CTestControlBase* CSdvSpoFrame::CreateFrame_SdvSpo(CTestControlBase *pTestControl, CTestItemViewGrid *pItemGrid)
{
	m_bTestControlRef = TRUE;
	m_pTestControl =pTestControl;
	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(m_pTestControl);
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);

	return pTestControl;
}

CTestControlBase* CSdvSpoFrame::CreateFrame_SdvSpo(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath)
{
	m_pTestControl = new CTestControl();
	m_pTestControl->CreateTestControlWnd();
	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(m_pTestControl);

	if(m_pTestControl->CreateTest(strGbBinaryFile, bFullPath))
	{
		m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
		
		m_pTestControl->AddTCtrlMsgRcvInterface(this);
		m_pTestControl->SetSafetyParentWnd(this);
	}

	return m_pTestControl;
}

CTestControlBase* CSdvSpoFrame::CreateFrame_SdvSpo(CTestItemViewGrid *pItemGrid, CXFolder *pFolder
									, const CString &strTemplateFile, const CString &strGuideBookFileType
								   , const CString &strTestProjectName, const CString &strPpEngineProgID, const CString &strPpTemplateFile
								   , const CString &strDeviceFile)
{
	ASSERT (pFolder != NULL);

	CString strReportMapFile,strReportFile;
	DWORD dwTkIDIndex = 0x0FFFFFFF;

	CString strSrc = _T(".") + g_strGbFilePostfix;
	CString strDest = _T(".") + g_strDocPostfix;

	strReportFile = strTemplateFile;
	strReportFile = ChangeFilePostfix(strReportFile, g_strDocFilePostfix);

	CString strNewTemplateFileName/*,strNewMapFileName*/,strNewMSWordFileName,strNewBinaryFileName;
	strNewMSWordFileName = pFolder->GetFolderPath();
	strNewMSWordFileName.AppendFormat(_T("%s.%s"), strTestProjectName, g_strDocFilePostfix);

	if( !X_CopyFile(strReportFile,strNewMSWordFileName,FALSE) )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_FileUnExistS/*L"文件\"%s\"不存在"*/, strReportFile);
	}
	else
	{
		ClearFileReadOnlyAttr(strNewMSWordFileName);
	}

	CTCtrlCntrWorkSpace::s_SetPpTemplateFile(strPpTemplateFile);
	CTCtrlCntrWorkSpace::s_SetPpDeviceFile(strDeviceFile);
	CTCtrlCntrWorkSpace::s_SetTemplateFile(strTemplateFile);
	CTCtrlCntrWorkSpace::s_SetReportMapFile(strGuideBookFileType);
	CTCtrlCntrWorkSpace::s_SetTestFolder(pFolder->GetFolderPath());
	CTCtrlCntrWorkSpace::s_SetTestName(strTestProjectName);
	CTCtrlCntrWorkSpace::s_SetTestFolder(pFolder->GetFolderPath());
	CTCtrlCntrWorkSpace::s_SetTestID(strTestProjectName);
	//CTCtrlCntrWorkSpace::s_SetTkIDIndex(dwTkIDIndex);
	CTCtrlCntrWorkSpace::s_SetPpEngineProgID(strPpEngineProgID);
	CTCtrlCntrWorkSpace::SetSttCommConfig(g_theAtsNewTestTool->m_pCommConfig);
	CTCtrlCntrWorkSpace::g_pWorkSpace->Save();

	//////////////////////////////////////////////////////////////////////////
	if (g_theAtsNewTestTool->IsOfflineTestMode())
	{
		m_pTestControl = new CTestControlOffline();
	}
	else
	{
		m_pTestControl = new CTestControl();
	}

	m_pTestControl->CreateTestControlWnd();
	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(m_pTestControl);

	if(m_pTestControl->CreateTest(g_theAtsNewTestTool->m_pTestApps))
	{
		m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);

		m_pTestControl->AddTCtrlMsgRcvInterface(this);
		m_pTestControl->SetSafetyParentWnd(this);

// 		if (pFolder == NULL)
// 		{
// 			CXFileMngr *pXFileMngr = theApp.GetTestFileMngr();
// 			pFolder = pXFileMngr->GetCurrFolder();
// 		}
	}

	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);

	return m_pTestControl;
}