// SclFileFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "SdvMpoFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSclFileFrame

IMPLEMENT_DYNCREATE(CSdvMpoFrame, CSdvSpoFrame)

CSdvMpoFrame::CSdvMpoFrame()
{
	
}

CSdvMpoFrame::~CSdvMpoFrame()
{
	
}


BEGIN_MESSAGE_MAP(CSdvMpoFrame, CSdvSpoFrame)
END_MESSAGE_MAP()


// CSclFileFrame 消息处理程序

CTestControlSdvMpp* CSdvMpoFrame::CreateFrame_SdvMpo(CTestTask *pSrcTestTask
													 , CTestItemViewGrid *pItemGrid, CXFolder *pFolder
													 , const CString &strTemplateFile
													 , const CString &strGuideBookFileType
													 , const CString &strTestProjectName
													 , CXFolder **ppNewFolder)
{
	CTestControlSdvMpp *pTestControl_SdvMpp = new CTestControlSdvMpp();
	CTestTask *pTestTask = pTestControl_SdvMpp->CloneTask(pSrcTestTask);
	m_pTestControl = pTestControl_SdvMpp;
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);

	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(m_pTestControl);	
	CString strPpEngineProgID, strPpTemplateFile, strDeviceFile;

	//创建文件夹
	CXFolder *pNewFolder = pFolder->AddFolder(strTestProjectName, TRUE);

	//创建相应的报告
	POS pos = pTestTask->GetHeadPosition();
	CTestProject *pProject = NULL;

	CString strReportMapFile,strReportFile;
	DWORD dwTkIDIndex = 0x0FFFFFFF;
	long nIndex = 1;
	CString strTemp, strNewMSWordFileName;

	strReportFile = strTemplateFile;
	strReportFile = ChangeFilePostfix(strReportFile, g_strDocFilePostfix);
	CString strDestPath = pNewFolder->GetFolderPath();
	CGuideBook *pGuideBook = new CGuideBook();
	long nRet = pGuideBook->OpenXMLFile(strTemplateFile);


	pGuideBook->m_strPpTemplateFile = strTemplateFile;
	pGuideBook->m_strDeviceModelFile = strDeviceFile;
	pGuideBook->m_strPpEngineProgID = strPpEngineProgID;

	while (pos != NULL)
	{
		pProject = (CTestProject *)pTestTask->GetNext(pos);
		pGuideBook->m_strDeviceModelFile = pProject->m_strPpDeviceFile;
		strNewMSWordFileName.Format(_T("%s%s.%s"), strDestPath, pProject->m_strID, g_strDocFilePostfix);

		if( !X_CopyFile(strReportFile,strNewMSWordFileName,FALSE) )
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_FileUnExistS/*L"文件\"%s\"不存在"*/, strReportFile);
		}
		else
		{
			ClearFileReadOnlyAttr(strNewMSWordFileName);
		}

		strNewMSWordFileName = ChangeFilePostfix(strNewMSWordFileName, g_strGuideBookBinaryPostfix);
		Gb_SetGbModifiedFlag(pGuideBook, TRUE);
		pGuideBook->SaveBinaryFile(strNewMSWordFileName, CTCtrlCntrConfig::Get_RWReportFileMode());
		//pProject->m_strLocation = strNewMSWordFileName;
		pProject->SetLocation(strNewMSWordFileName);
	}

	CString strTaskFile;
	strTaskFile.Format(_T("%s%s.%s"), strDestPath, strTestProjectName, g_strGuideBookSdvMppTaskPostfix);
	pTestTask->m_strName = strTestProjectName;
	pTestTask->SaveAs(strTaskFile);

	CTCtrlCntrWorkSpace::s_SetPpTemplateFile(_T(""));
	CTCtrlCntrWorkSpace::s_SetPpDeviceFile(_T(""));
	CTCtrlCntrWorkSpace::s_SetTemplateFile(strTemplateFile);
	CTCtrlCntrWorkSpace::s_SetReportMapFile(strGuideBookFileType);
	CTCtrlCntrWorkSpace::s_SetTestFolder(pFolder->GetFolderPath());
	CTCtrlCntrWorkSpace::s_SetTestName(strTestProjectName);
	CTCtrlCntrWorkSpace::s_SetTestFolder(pFolder->GetFolderPath());
	CTCtrlCntrWorkSpace::s_SetTestID(strTestProjectName);
	//CTCtrlCntrWorkSpace::s_SetTkIDIndex(dwTkIDIndex);
	CTCtrlCntrWorkSpace::s_SetPpEngineProgID(_T(""));
	CTCtrlCntrWorkSpace::s_SetLastTaskFile(strTaskFile);
	CTCtrlCntrWorkSpace::s_SetLastTestFile(strTaskFile);
	CTCtrlCntrWorkSpace::g_pWorkSpace->Save();

	//发送新建框架线程消息
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	pTestControl_SdvMpp->InitByOwnTask();

	delete pGuideBook;
	*ppNewFolder = pNewFolder;

	return pTestControl_SdvMpp;
}

CTestControlSdvMpp* CSdvMpoFrame::CreateFrame_SdvMpo(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath)
{
	CTestControlSdvMpp *pTestControl_SdvMpp = new CTestControlSdvMpp();
	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(pTestControl_SdvMpp);

	pTestControl_SdvMpp->OpenTaskFile(strGbBinaryFile);
	CTestTask *pTestTask = pTestControl_SdvMpp->GetTestTask();

	ASSERT (g_theTCtrlCntrApp != NULL);
	g_theTCtrlCntrApp->WritePpMmsEngineConfig(pTestTask);

	m_pTestControl = pTestControl_SdvMpp;
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);

	pTestControl_SdvMpp->InitByOwnTask();

	return pTestControl_SdvMpp;
}

