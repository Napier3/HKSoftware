// SclFileFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "SdvSpoMgrpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSclFileFrame

IMPLEMENT_DYNCREATE(CSdvSpoMgrpFrame, CMRptBaseFrame)

CSdvSpoMgrpFrame::CSdvSpoMgrpFrame()
{
	
}

CSdvSpoMgrpFrame::~CSdvSpoMgrpFrame()
{
	
}


BEGIN_MESSAGE_MAP(CSdvSpoMgrpFrame, CMRptBaseFrame)
END_MESSAGE_MAP()


// CSclFileFrame 消息处理程序
CTestControlManyReport* CSdvSpoMgrpFrame::CreateFrame_SdvSpoMgrp(CTestItemViewGrid *pItemGrid, CXFolder *pFolder
											   , const CString &strTemplateFile
											   , const CString &strGuideBookFileType
											   , const CString &strTestProjectName
											   , const CString &strPpEngineProgID
											   , const CString &strPpTemplateFile
											   , const CString &strDeviceFile
											   , const CString &strTestType
											   , CDvmDataset *pExpandDatas
											   , CXFolder **ppNewFolder)
{
	CTestControlManyReport *pTestControlManyReport = new CTestControlManyReport();
	m_pTestControl = pTestControlManyReport;
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);

	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(m_pTestControl);	
	CTestTask *pTestTask = pTestControlManyReport->GetTestTask();
	pTestTask->m_strTestType = strTestType;

	//创建文件夹
	CXFolder *pNewFolder = pFolder->AddFolder(strTestProjectName, TRUE);

	//扩展数据
	CDvmDataset *pDataset = new CDvmDataset();
	pDataset->m_strName = DSID_COMMCMDMCONFIG;
	pDataset->m_strID   = DSID_COMMCMDMCONFIG;
	pDataset->AppendCloneEx(*pExpandDatas);
	pTestTask->AddNewChild(pDataset);

	//创建相应的报告
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;

	CString strReportMapFile,strReportFile;
	DWORD dwTkIDIndex = 0x0FFFFFFF;
	long nIndex = 1;
	CString strTemp, strNewMSWordFileName;

	strReportFile = strTemplateFile;
	strReportFile = ChangeFilePostfix(strReportFile, g_strDocFilePostfix);
	CString strDestPath = pNewFolder->GetFolderPath();
	CGuideBook *pGuideBook = new CGuideBook();
	long nRet = pGuideBook->OpenXMLFile(strTemplateFile);

	pGuideBook->m_strPpTemplateFile = strPpTemplateFile;
	pGuideBook->m_strDeviceModelFile = strDeviceFile;
	pGuideBook->m_strPpEngineProgID = strPpEngineProgID;
	pGuideBook->AdjustByTkIDIndex(pTestTask->m_strTestType, CTCtrlCntrConfig::IsAdjustByTkIDMode_Delete());

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);

		if (pData->m_strValue == _T("1"))
		{
			strNewMSWordFileName.Format(g_sLangTxt_SGroupS/*_T("%s%s-组%d.%s")*/, strDestPath, strTestProjectName, nIndex, g_strDocFilePostfix);

			if( !X_CopyFile(strReportFile,strNewMSWordFileName,FALSE) )
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_FileUnExistS/*L"文件\"%s\"不存在"*/, strReportFile);
			}
			else
			{
				ClearFileReadOnlyAttr(strNewMSWordFileName);
			}

			strNewMSWordFileName = ChangeFilePostfix(strNewMSWordFileName, g_strGuideBookBinaryPostfix);
			pGuideBook->m_strID = pData->m_strFormat;
			Gb_SetGbModifiedFlag(pGuideBook, TRUE);
			pGuideBook->SaveBinaryFile(strNewMSWordFileName, CTCtrlCntrConfig::Get_RWReportFileMode());

			CTestProject *pProject = new CTestProject();
			pProject->m_strName.Format(g_sLangTxt_SGroupFileName/*_T("%s-组%d")*/, strTestProjectName, nIndex);
			pProject->m_strID = pProject->m_strName;
			pProject->m_strLocalID = pProject->m_strID;
			//pProject->m_strLocation = strNewMSWordFileName;
			pProject->tsk_SetLocation(strNewMSWordFileName);
			pProject->m_strPpEngineProgID = strPpEngineProgID;
			pProject->m_strPpDeviceFile = strDeviceFile;
			pProject->tsk_SetGbxmlFile(strTemplateFile);
			pProject->m_strTestType = pTestTask->m_strTestType;
			pTestTask->AddNewChild(pProject);
		}

		nIndex++;
	}

	CString strTaskFile;
	strTaskFile.Format(_T("%s%s.%s"), strDestPath, strTestProjectName, g_strGuideBookBinaryPostfix_SdvSpoMgrp);
	pTestTask->SaveAs(strTaskFile);

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
	CTCtrlCntrWorkSpace::s_SetLastTaskFile(strTaskFile);
	CTCtrlCntrWorkSpace::s_SetLastTestFile(strTaskFile);
	CTCtrlCntrWorkSpace::g_pWorkSpace->Save();

	//发送新建框架线程消息
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	pTestControlManyReport->InitByOwnTask();

	pData = (CDvmData *)pDataset->GetHead();

	if (pData != NULL)
	{
		pTestControlManyReport->EditCommCmdDatasetPath(pData->m_strFormat);
	}
	else
	{
		pTestControlManyReport->EditCommCmdDatasetPath(_T(""));
	}

	delete pGuideBook;
	*ppNewFolder = pNewFolder;

	return pTestControlManyReport;
}

CTestControlManyReport* CSdvSpoMgrpFrame::CreateFrame_SdvSpoMgrp(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath)
{
	CTestControlManyReport *pTestControlManyReport = new CTestControlManyReport();
	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(pTestControlManyReport);

	m_pTestControl = pTestControlManyReport;
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);

	pTestControlManyReport->CreateTest(strGbBinaryFile, bFullPath);

	return pTestControlManyReport;
}

CTestControlManyReport* CSdvSpoMgrpFrame::CreateFrame_SdvSpoMgrp(CTestControlManyReport *pTestControlManyReport, CTestItemViewGrid *pItemGrid)
{
	CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.AddTail(pTestControlManyReport);

	m_pTestControl = pTestControlManyReport;
	m_bTestControlRef = TRUE;
	m_pTestControl->CreateTestControlWnd();
	m_pTestControl->AttachItemViewGrid(pItemGrid, TRUE);
	m_pTestControl->AddTCtrlMsgRcvInterface(this);
	m_pTestControl->SetSafetyParentWnd(this);

	return pTestControlManyReport;
}

