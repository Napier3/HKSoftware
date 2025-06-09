// SclFileFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "MdvSpoFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSclFileFrame

IMPLEMENT_DYNCREATE(CMdvSpoFrame, CSdvSpoFrame)

CMdvSpoFrame::CMdvSpoFrame()
{
	
}

CMdvSpoFrame::~CMdvSpoFrame()
{
	
}


BEGIN_MESSAGE_MAP(CMdvSpoFrame, CSdvSpoFrame)
END_MESSAGE_MAP()


// CSclFileFrame 消息处理程序
#if 0
CTestControl* CMdvSpoFrameFrame::OnCreateFrame_MdvSpoFrame(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath)
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

CTestControl* CMdvSpoFrameFrame::OnCreateFrame_MdvSpoFrame(CTestItemViewGrid *pItemGrid, CXFolder *pFolder, const CString &strTemplateFile, const CString &strGuideBookFileType
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
	CTCtrlCntrWorkSpace::g_pWorkSpace->Save();

	//////////////////////////////////////////////////////////////////////////
	m_pTestControl = new CTestControl();
	m_pTestControl->CreateTestControlWnd();
	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(m_pTestControl);

	if(m_pTestControl->CreateTest())
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
#endif

CTestControlManyDevice* CMdvSpoFrame::CreateFrame_MdvSpo(CTestTask *pSrcTestTask
														 , CTestItemViewGrid *pItemGrid, CXFolder *pFolder
														 , const CString &strTemplateFile
														 , const CString &strGuideBookFileType
														 , const CString &strTestProjectName
														 , const CString &strPpEngineProgID
														 , const CString &strPpTemplateFile
														 , const CString &strDeviceFile
														 , CXFolder **ppNewFolder)
{
	CTestControlManyDevice *pTestControlManyDevice = new CTestControlManyDevice();
	CTestTask *pTestTask = pTestControlManyDevice->CloneTask(pSrcTestTask);
	m_pTestControl = pTestControlManyDevice;
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);

	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(m_pTestControl);	

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
		pProject->tsk_SetLocation(strNewMSWordFileName);
	}

	CString strTaskFile;
	strTaskFile.Format(_T("%s%s.%s"), strDestPath, strTestProjectName, g_strGuideBookMdTaskPostfix);
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
	pTestControlManyDevice->InitByOwnTask();

	delete pGuideBook;
	*ppNewFolder = pNewFolder;

	return pTestControlManyDevice;
}

CTestControlManyDevice* CMdvSpoFrame::CreateFrame_MdvSpo(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath)
{
	CTestControlManyDevice *pTestControlManyDevice = new CTestControlManyDevice();
	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(pTestControlManyDevice);

	//g_theTCtrlCntrApp->WritePpMmsEngineConfig();
	pTestControlManyDevice->OpenTaskFile(strGbBinaryFile);

	m_pTestControl = pTestControlManyDevice;
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);

	pTestControlManyDevice->InitByOwnTask();

	return pTestControlManyDevice;
}

