// SclFileFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "MdvMgrpSpoFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSclFileFrame

IMPLEMENT_DYNCREATE(CMdvMgrpSpoFrame, CMRptBaseFrame)

CMdvMgrpSpoFrame::CMdvMgrpSpoFrame()
{
	
}

CMdvMgrpSpoFrame::~CMdvMgrpSpoFrame()
{
	
}


BEGIN_MESSAGE_MAP(CMdvMgrpSpoFrame, CMRptBaseFrame)
END_MESSAGE_MAP()


// CSclFileFrame 消息处理程序
// CMdvMgrpSpoDeviceTestControl* CreateFrame_MdvMgrpSpo_Task(CTestItemViewGrid *pItemGrid
// 														  , CXFolder *pParentFolder , CGuideBook *pGuideBook
// 														  , CTestTask *pTestTask, CXFolder **ppNewTaskFolder)
// {
// 	CString strFolder = pParentFolder->GetFolderPath(TRUE);
// 	POS pos = pTestTask->GetHeadPosition();
// 	CTestProject *pProject = NULL;
// 
// 	//创建任务文档：当装置、多组
// 	CXFolder *pNewTaskFolder = pParentFolder->AddFolder(pTestTask->m_strName);
// 	*ppNewTaskFolder = pNewTaskFolder;
// 	CString strFile;
// 
// 	while (pos != NULL)
// 	{
// 		pProject = (CTestProject *)pTestTask->GetNext(pos);
// 		pNewTaskFolder->AddFile2(pProject->m_strLocation);
// 		
// 	}
// 
// 	return NULL;
// }
CXFolder* CMdvMgrpSpoFrame::CreateMdvMgrpFolders(CTestTasks *pTestTasks, CXFolder *pFolder)
{
	CXFolder *pMdvMgrpFolder = pFolder->AddFolder(pTestTasks->m_strName, FALSE);
	pMdvMgrpFolder->AddFile2(GetPathFileNameFromFilePathName(pTestTasks->m_strTasksFile));

	CreateMdvMgrpTaskFolders(pTestTasks, pMdvMgrpFolder);

// 	CXFolder *pMgrpFolder = NULL;
// 	POS pos = pTestTasks->GetHeadPosition();
// 	CTestTask *pTestTask = NULL;
// 	POS posProject = NULL;
// 	CTestProject *pProject = NULL;
// 	CExBaseList listProject;
// 
// 	while (pos != NULL)
// 	{
// 		pTestTask = (CTestTask *)pTestTasks->GetNext(pos);
// 		pMgrpFolder = pMdvMgrpFolder->AddFolder(pTestTask->m_strName, FALSE);
// 		pTestTask->SelectAllTestProject(listProject);
// 		posProject = listProject.GetHeadPosition();
// 
// 		while (posProject != NULL)
// 		{
// 			pProject = (CTestProject *)listProject.GetNext(posProject);
// 			pMgrpFolder->AddFile2(pProject->m_strName);
// 		}
// 
// 		listProject.RemoveAll();
// 	}

	return pMdvMgrpFolder;
}

void CMdvMgrpSpoFrame::CreateMdvMgrpTaskFolders(CTestTasks *pTestTasks, CXFolder *pMdvMgrpFolder)
{
	CExBaseList listTask;
	pTestTasks->SelectAllTestTask(listTask);

	POS pos = listTask.GetHeadPosition();
	CTestTask *pTestTask = NULL;
	POS posProject = NULL;
	CTestProject *pProject = NULL;
	CExBaseList listProject;
	CXFolder *pMgrpFolder = NULL;

	while (pos != NULL)
	{
		pTestTask = (CTestTask *)listTask.GetNext(pos);

		if (pTestTask->m_strLocalID.GetLength() > 0)
		{
			pMgrpFolder = pMdvMgrpFolder->AddFolder(pTestTask->m_strLocalID, TRUE);
		}
		else
		{
			pMgrpFolder = pMdvMgrpFolder->AddFolder(pTestTask->m_strName, TRUE);
		}

		pTestTask->SelectAllTestProject(listProject);
		posProject = listProject.GetHeadPosition();

		while (posProject != NULL)
		{
			pProject = (CTestProject *)listProject.GetNext(posProject);
			pMgrpFolder->AddFile2(pProject->m_strName);
		}

		listProject.RemoveAll();
	}

	listTask.RemoveAll();
}


CMdvMgrpSpoDeviceMngrTestControl* CMdvMgrpSpoFrame::CreateFrame_MdvMgrpSpo(CTestItemViewGrid *pItemGrid, CXFolder *pFolder
											   , const CString &strTasksFile, CXFolder **ppNewFolder)
{
	CMdvMgrpSpoDeviceMngrTestControl *pTestControlMdvMgrp = new CMdvMgrpSpoDeviceMngrTestControl();

	m_pTestControl = pTestControlMdvMgrp;
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);
	
	pTestControlMdvMgrp->OpenTasksFile(strTasksFile);
	CTestTasks *pTestTasks = pTestControlMdvMgrp->GetTestTasks();
	*ppNewFolder = CreateMdvMgrpFolders(pTestTasks, pFolder);
	pTestControlMdvMgrp->CreateTestControls(TRUE);

	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(m_pTestControl);	
	CTCtrlCntrWorkSpace::s_SetPpTemplateFile(_T(""));
	CTCtrlCntrWorkSpace::s_SetPpDeviceFile(_T(""));
	CTCtrlCntrWorkSpace::s_SetTemplateFile(_T(""));
	CTCtrlCntrWorkSpace::s_SetReportMapFile(_T(""));
	CTCtrlCntrWorkSpace::s_SetTestFolder(pFolder->GetFolderPath());
	CTCtrlCntrWorkSpace::s_SetTestName(_T(""));
	CTCtrlCntrWorkSpace::s_SetTestFolder(pFolder->GetFolderPath());
	CTCtrlCntrWorkSpace::s_SetTestID(_T(""));
	//CTCtrlCntrWorkSpace::s_SetTkIDIndex(0);
	CTCtrlCntrWorkSpace::s_SetPpEngineProgID(_T(""));
	CTCtrlCntrWorkSpace::s_SetLastTaskFile(pTestTasks->m_strTasksFile);
	CTCtrlCntrWorkSpace::s_SetLastTestFile(_T(""));
	CTCtrlCntrWorkSpace::g_pWorkSpace->Save();

	//发送新建框架线程消息
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);

	return pTestControlMdvMgrp;
}

CMdvMgrpSpoDeviceMngrTestControl* CMdvMgrpSpoFrame::CreateFrame_MdvMgrpSpo(CXFileMngr *pXFileMngr, const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath)
{
	CMdvMgrpSpoDeviceMngrTestControl *pTestControlMdvMgrp = new CMdvMgrpSpoDeviceMngrTestControl();
	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(pTestControlMdvMgrp);

	m_pTestControl = pTestControlMdvMgrp;
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);

	pTestControlMdvMgrp->OpenTasksFile(strGbBinaryFile);
	CTestTasks *pTestTasks = pTestControlMdvMgrp->GetTestTasks();

	pTestTasks->SetRptViewByMrpt();

	if (pTestTasks->HasAllProjectCreated())
	{
		pTestControlMdvMgrp->CreateTestControls(FALSE);
	}
	else
	{
		CString strPath;
		strPath = GetPathFromFilePathName(strGbBinaryFile);
		strPath.MakeLower();

		CXFolder *pFolder = pXFileMngr->SelectFolder(strPath, TRUE);
		ASSERT (pFolder != NULL);

		if (pFolder == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("路径[%s]异常！"), strPath);
			return pTestControlMdvMgrp;
		}

		strPath = strPath.Left(strPath.GetLength() - 1);
		strPath = GetPathFromFilePathName(strPath);
		pTestTasks->m_strTasksParentPath = strPath;

		pTestControlMdvMgrp->CreateAllFilesByTasks(pTestTasks);
		pTestTasks->SaveTasksFile(_T(""));
		pTestControlMdvMgrp->CreateTestControls(TRUE);
	}

	pTestControlMdvMgrp->CreateEnginePoProject();
	pTestControlMdvMgrp->AttachTestControlWnd(pTestControlMdvMgrp->m_pTCtrlWnd);

	return pTestControlMdvMgrp;
}

