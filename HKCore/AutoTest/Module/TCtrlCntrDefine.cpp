#include "StdAfx.h"
#include "TCtrlCntrDefine.h"

#include "XLanguageResourceAts.h"
#include "GuideBook/TestTypeMngr.h"

#ifdef _use_test_task
#include "TCtrlCntrBaseApp.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString g_strTCtrlCntrWorkspacePath			= _T("");
CString g_strTCtrlCntrTemplatePath			=_T("");
CString g_strTCtrlCntrLibraryPath					= _T("");

void InitTCtrlCntrPath(BOOL bUseAts)
{
	CString strPath;

	if(bUseAts)
	{
		strPath = _P_GetInstallPath();
		strPath += _T("e-Report");
		strPath += _P_FOLDER_PATH_SEPARATOR_;
	}
	else
	{
		strPath = _P_GetSystemPath();
	}

	g_strTCtrlCntrWorkspacePath = strPath;
	g_strTCtrlCntrTemplatePath = strPath;
	g_strTCtrlCntrLibraryPath = strPath;

	g_strTCtrlCntrWorkspacePath += _T("Workspace");
	g_strTCtrlCntrWorkspacePath += _P_FOLDER_PATH_SEPARATOR_;

	g_strTCtrlCntrTemplatePath += _T("Template");
	g_strTCtrlCntrTemplatePath += _P_FOLDER_PATH_SEPARATOR_;

	g_strTCtrlCntrLibraryPath += _T("Library") ;
	g_strTCtrlCntrLibraryPath += _P_FOLDER_PATH_SEPARATOR_;
}

#ifdef _use_test_task
CString GetTestTaskPath(CExBaseObject* pObj)
{
	CTestTask *pTestTask = (CTestTask*)pObj;
	ASSERT(pTestTask != NULL);

	CString strPath;
	strPath.Format(_T("%s%s\\"), g_strTCtrlCntrWorkspacePath, pTestTask->m_strLocalID);

	return strPath;
}

inline CString GetTestProjectTempFilePath(CExBaseObject* pObj)
{
	CTestProject *pTestProject = (CTestProject*)pObj;
	ASSERT(pTestProject != NULL);
	ASSERT(pTestProject->m_strLocalID != _T(""));

	CTestTask* pTestTask = (CTestTask*)pTestProject->GetParent();
	ASSERT(pTestTask->m_strLocalID != _T(""));

	CString strTempPath;
	strTempPath.Format(_T("%s%s\\%s\\"), g_strTCtrlCntrWorkspacePath
		, pTestTask->m_strLocalID, pTestProject->m_strLocalID);

	return strTempPath;
}

inline CString GetTestProjectTempFileName(CExBaseObject* pTestProjectObj,CExBaseObject* pItemObj)
{
	CTestProject *pTestProject = (CTestProject*)pTestProjectObj;
	CGbItemBase  *pItem = (CGbItemBase*)pItemObj;
	ASSERT(pItem != NULL);

	CString strTempPath = GetTestProjectTempFilePath(pTestProject);
	CString strTempFileName;
	strTempFileName.Format(_T("%s%d%s"),strTempPath,pItem->m_nIndex,g_strBinaryPostfix);

	return strTempFileName;
}

#endif

void ats_GetMdTestFileFilter(CString &strFilter)
{
    strFilter.Format(g_sLangTxt_MulDeviceRptS/*_T("多装置测试报告文件(*.%s)|*.%s||")*/, g_strGuideBookMdTaskPostfix.GetString(), g_strGuideBookMdTaskPostfix.GetString());
}

void ats_GetSdvMppTestFileFilter(CString &strFilter)
{
    strFilter.Format(g_sLangTxt_SngDeviceRptS/*_T("单装置多规约测试报告文件(*.%s)|*.%s||")*/, g_strGuideBookSdvMppTaskPostfix.GetString(), g_strGuideBookSdvMppTaskPostfix.GetString());
}

void ats_GetMdvMgrpTestFileFilter(CString &strFilter)
{
	strFilter.Format(g_sLangTxt_MdvMgrpFilter/*_T("多装置多组测试报告文件(*.%s)|*.%s||")*/
        , g_strGuideBookMdvMgrpTaskPostfix.GetString(), g_strGuideBookMdvMgrpTaskPostfix.GetString());
}

BOOL ats_GetMdTestFile(CString &strMdTestFile, CWnd *pParent)
{
	CString strFilter;
	ats_GetMdTestFileFilter(strFilter);

	return PopupOpenFileDialog(pParent, strMdTestFile, strFilter, g_strGuideBookMdTaskPostfix);
}

BOOL ats_GetSdvMppTestFile(CString &strSdvMppTestFile, CWnd *pParent)
{
	CString strFilter;
	ats_GetSdvMppTestFileFilter(strFilter);

	return PopupOpenFileDialog(pParent, strSdvMppTestFile, strFilter, g_strGuideBookSdvMppTaskPostfix);
}

CString _P_GetProjectID()
{
    CTime tm = CTime::GetCurrentTime();
    return tm.Format("_%Y%m%d%H%M%S");
}

#ifndef _PSX_QT_LINUX_

void ats_SetCocumentTitle(const CString &strText, CDocument *pDoc, BOOL bMain, long nDeviceIndex)
{
	CString strTitle = GetPathFileNameFromFilePathName(strText);
	CString strName, strPostfix;
	ParseFileNameAndPostfix(strTitle, strName, strPostfix);

	if (nDeviceIndex >= 0)
	{
		strTitle.Format(_T("%d:"), nDeviceIndex+1);
		strName = strTitle + strName;
	}

	if (bMain)
	{
		strName = _T("主-") + strName;
	}

	pDoc->SetTitle(strName);
}


CString ats_GetCocumentTitle(const CString &strText)
{
	CString strTitle = GetPathFileNameFromFilePathName(strText);
	CString strName, strPostfix;
	ParseFileNameAndPostfix(strTitle, strName, strPostfix);

	return strName;
}

void ATS_InitSysReportFileMngr(CXFileMngr *pXFileMngr, const CString &strWorkSpacePath)
{
	pXFileMngr->m_strName = g_sLangTxt_TestLogMngmt/*_T("测试记录文件管理")*/;

	CXFileType *pXFileType = pXFileMngr->AddFileType(g_sLangTxt_TestRptRecodFile/*_T("测试报告记录文件")*/, g_strGuideBookBinaryPostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(g_sLangTxt_TestRptRecodFile/*_T("测试报告记录文件")*/, g_strGuideBookBinaryPostfix);
	pXFileType->AddNewPostfix(g_sLangTxt_TestRptFile/*_T("测试报告文件")*/, g_strDocFilePostfix);

	pXFileType = pXFileMngr->AddFileType(g_sLangTxt_TestTaskFile/*_T("测试任务文件")*/, g_strTestTaskFilePostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(g_sLangTxt_TestTaskFile/*_T("测试任务文件")*/, g_strTestTaskFilePostfix);

	//2015-6-10添加：多测试报告文件
	pXFileType = pXFileMngr->AddFileType(g_sLangTxt_SngDeviceRpt/*_T("单装置多通道测试报告文件")*/, g_strGuideBookBinaryPostfix_SdvSpoMgrp, _T(""), _T(""));
	pXFileType->AddNewPostfix(g_sLangTxt_SngDeviceRpt/*_T("单装置多通道测试报告文件")*/, g_strGuideBookBinaryPostfix_SdvSpoMgrp);

	//2015-6-10添加：多测试报告文件
	pXFileType = pXFileMngr->AddFileType(g_sLangTxt_MulDeviceRpt/*_T("多装置测试报告文件")*/, g_strGuideBookMdTaskPostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(g_sLangTxt_MulDeviceRpt/*_T("多装置测试报告文件")*/, g_strGuideBookMdTaskPostfix);

	pXFileType = pXFileMngr->AddFileType(g_sLangTxt_SngDeviceRpt2/*_T("单装置多规约测试报告文件")*/, g_strGuideBookSdvMppTaskPostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(g_sLangTxt_SngDeviceRpt2/*_T("单装置多规约测试报告文件")*/, g_strGuideBookSdvMppTaskPostfix);

	pXFileType = pXFileMngr->AddFileType(g_sLangTxt_MdvMgrpFile/*_T("单装置多规约测试报告文件")*/, g_strGuideBookMdvMgrpTaskPostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(g_sLangTxt_MdvMgrpFile/*_T("单装置多规约测试报告文件")*/, g_strGuideBookMdvMgrpTaskPostfix);

	pXFileMngr->SetOnllySearchMainTypeFile(TRUE);
	pXFileMngr->InitByXFileTypes();
	pXFileMngr->SetLibraryPath(strWorkSpacePath);

	CString strTemp;
	strTemp.Format(_T(".%s"), g_strTestTaskFilePostfix);
	XFile_BringFileHead(pXFileMngr, strTemp);
}

void ATS_InitSysReportFileMngr(CXFileMngr *pXFileMngr, const CString &strWorkSpacePath, const CString &strPostfix)
{
	pXFileMngr->m_strName = g_sLangTxt_TestLogMngmt/*_T("测试记录文件管理")*/;

	CXFileType *pXFileType = NULL;

	pXFileType = pXFileMngr->AddFileType(strPostfix, strPostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(strPostfix, strPostfix);

	pXFileMngr->SetOnllySearchMainTypeFile(TRUE);
	pXFileMngr->InitByXFileTypes();
	pXFileMngr->SetLibraryPath(strWorkSpacePath);
}


DWORD ATS_GetTkIDIndex(CComboBox *pComboBox)
{
	CString strTestType;

	return ATS_GetTkIDIndex(pComboBox, strTestType);
}

DWORD ATS_GetTkIDIndex(CComboBox *pComboBox, CString &strTestType)
{
	long nSel = pComboBox->GetCurSel();

	if (nSel == CB_ERR)
	{
		strTestType = _T("1");
		return 0xFFFFFFFF;
	}

	CTestType *pTestType = (CTestType*)pComboBox->GetItemDataPtr(nSel);

	if (pTestType == NULL)
	{
		strTestType = _T("1");
		return 0xFFFFFFFF;
	}

	strTestType = pTestType->m_strName;
	DWORD dwTkID_Index = 1;
	long nIndex = CString_To_long(pTestType->m_strID);
	nIndex -= 1;
	dwTkID_Index = dwTkID_Index << nIndex;

	return dwTkID_Index;
}
#endif

DWORD ATS_GetTkIDIndex(const CString &strTestType, CDataTypes *pDataTypes)
{
	if (strTestType.GetLength() == 0 || pDataTypes == NULL)
	{
		return 0xFFFFFFFF;
	}

	CTestType *pTestType = (CTestType*)pDataTypes->FindByName(strTestType);

	if (pTestType == NULL)
	{
		return 0xFFFFFFFF;
	}

	DWORD dwTkID_Index = 1;
	long nIndex = CString_To_long(pTestType->m_strID);
	nIndex -= 1;
	dwTkID_Index = dwTkID_Index << nIndex;

	return dwTkID_Index;
}


//2021-1-6  lijunqing 为简化版本
BOOL ATS_ValidateSystemPath(CString &strFile, const CString &strSysPath, const CString &strSysID)
{
	CString strTemp = strFile;

	strTemp.MakeLower();
	long nPos = strTemp.Find(strSysID);

	if (nPos > 0)
	{
		strFile = strFile.Mid(nPos+1+strSysID.GetLength());
		strFile = strSysPath + strFile;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL ATS_ValidateSystemPath(CString &strFile, const CString &strSysPath)
{
	if (strFile.Find(':') > 0)
	{
		if (ATS_ValidateSystemPath(strFile, strSysPath, _T("e-report")))
		{
			return IsFileExist(strFile);
		}

		if (ATS_ValidateSystemPath(strFile, strSysPath, _T("e-protocol")))
		{
			return IsFileExist(strFile);
		}

		return FALSE;
	}
	else
	{
		strFile = strSysPath + strFile;
		return IsFileExist(strFile);
	}
}

long ATS_GetSrcDeviceModelFiles(const CString &strSrcDeviceModelFile, CStringArray &astrFiles)
{
	astrFiles.RemoveAll();
	CBufferBase oBuffer;
	oBuffer.InitBuffer(strSrcDeviceModelFile);
	oBuffer.FormatBuffer('\r');
	oBuffer.FormatBuffer('\n');
	char *p = oBuffer.GetString();
	CString strFile;

	while (oBuffer.IsPoiterInBuffer())
	{
		p = oBuffer.GetString();
		strFile = p;

		if (strFile.GetLength() > 4)
		{
			astrFiles.Add(strFile);
		}

		p = oBuffer.NextString();
	}

	return astrFiles.GetCount();
}

