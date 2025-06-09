#include "stdafx.h"
#include "AtsNewTestTool.h"
#include "../XLanguageResourceAts_AutoTest.h"
#include "..\..\..\Protocol\Module\ProcotolProject\ClassProcotolProjectGlobal.h"
#include "..\..\..\Module\TestMacro\TestMacrosFileMngr.h"
#include "../TCtrlCntrWorkSpace.h"
#include "..\..\..\Module\Socket\XPing.h"

#include "..\..\..\Module\Encrypt\EncryptTool.h"
#include "..\TCtrlCntrConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void sdvmpp_UpdateProjectName(CTestProject *pTestProject)
{
	CString strName, strPostfix, strFile;
	strFile = GetPathFileNameFromFilePathName(pTestProject->m_strPpDeviceFile);
	ParseFileNameAndPostfix(strFile, strName, strPostfix);

	if (pTestProject->m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		pTestProject->m_strName.Format(_T("%s-%s"), engine_GetEngineEngineText(pTestProject->m_strPpEngineProgID), strName);
	}
	else if (pTestProject->m_strPpEngineProgID == g_strPpEngineProgID)
	{
		pTestProject->m_strName = strName;
		strFile = pTestProject->tsk_GetPpxmlFile(FALSE);
		ParseFileNameAndPostfix(strFile, strName, strPostfix);
		strName.AppendFormat(_T("-%s"), pTestProject->m_strName);
		pTestProject->m_strName = strName;
	}
	else
	{
		pTestProject->m_strName.Format(_T("%s-%s"), engine_GetEngineEngineText(pTestProject->m_strPpEngineProgID), strName);
	}

	pTestProject->m_strID = pTestProject->m_strName;
}


CAtsNewTestTool *g_theAtsNewTestTool;

CAtsNewTestTool* CAtsNewTestTool::g_pAtsNewTestTool = NULL;
long CAtsNewTestTool::g_nAtsNewTestToolRef = 0;


CAtsNewTestTool* CAtsNewTestTool::Create()
{
	g_nAtsNewTestToolRef++;

	if (g_nAtsNewTestToolRef == 1)
	{
		CAutoTestXMLRWKeys::Create();
		g_pAtsNewTestTool = new CAtsNewTestTool();
// 		g_pAtsNewTestTool->m_nNewMode = nNewMode;
// 		g_pAtsNewTestTool->m_pXCurrFolder = pXCurrFolder;
// 		g_pAtsNewTestTool->InitAtsNewTestTool();
	}

	return g_pAtsNewTestTool;
}

void CAtsNewTestTool::Release()
{
	g_nAtsNewTestToolRef--;

	if (g_nAtsNewTestToolRef == 0)
	{
		CAutoTestXMLRWKeys::Release();
		delete g_pAtsNewTestTool;
		g_pAtsNewTestTool = NULL;
	}
}

CAtsNewTestTool::CAtsNewTestTool()
{
	g_theAtsNewTestTool = this;

	m_pTempGuideBook = new CGuideBook();
	m_pTempGuideBook->m_strGuideBookFileType = g_strGbFileFilter;
	m_pTestTask  = NULL;
	m_pTestTasks = NULL;
	m_dwReportType = REPORTFILL_INDEX_NONE;

	m_pExpandDatas = NULL;
	m_pExpandDatasAutoSet = NULL;
	m_pReportSNGen = NULL;
	m_pTaskReportSNGen = NULL;
	m_pDeviceAttrsDefine = NULL;
	m_pTestAppDefine = NULL;
	m_pTestApp = NULL;
	m_dwTkID_Index = 0;
	m_pTestTypes = NULL;
	m_pTestMacrosFile = NULL;
	m_bTestTasksAttach = FALSE;

	m_bHasLink_TestApp = FALSE;
	m_bHasLink_Device = FALSE;
	m_pInspectionBases = NULL;
	m_pTesters = NULL;
	m_pGlobalDatas = NULL;

	//ȫ�ֵ�װ�ö���
	m_pCommConfig = NULL;   
	m_pTestApps = NULL;
}

CAtsNewTestTool::~CAtsNewTestTool()
{
	//����TestDefine�ļ�  //shaolei  20211022
	m_oTestGlobalDefine.SaveTestDefineFile(CGbXMLKeys::g_pGbXMLKeys);

	delete m_pTempGuideBook;
	m_pTempGuideBook = NULL;

	if (m_pTestTask != NULL)
	{
		delete m_pTestTask;
		m_pTestTask = NULL;
	}

	if (m_pTestTasks != NULL)
	{
		if (!m_bTestTasksAttach)
		{
			delete m_pTestTasks;
		}

		m_pTestTasks = NULL;
	}

	if (m_pTestApp != NULL)
	{
		delete m_pTestApp;
		m_pTestApp = NULL;
	}

	if (m_pInspectionBases != NULL)
	{
		delete m_pInspectionBases;
		m_pInspectionBases = NULL;
	}

	if (m_pTesters != NULL)
	{
		delete m_pTesters;
		m_pTesters = NULL;
	}

	if (m_pGlobalDatas != NULL)
	{
		delete m_pGlobalDatas;
		m_pGlobalDatas = NULL;
	}

	if (m_pCommConfig != NULL)
	{
		delete m_pCommConfig;
	}

	if (m_pTestApps != NULL)
	{
		delete m_pTestApps;
	}
}

void CAtsNewTestTool::InitAtsNewTestTool(UINT nNewMode, CXFolder *pXCurrFolder, CTestTasks *pTestTasks)
{
	m_nNewMode = nNewMode;
	m_pXCurrFolder = pXCurrFolder;

	if (m_nNewMode == TESTCONTROLMODE_MDGBRPT)
	{
		m_pTestTask = new CTestTask();
	}
	else if (m_nNewMode == TESTCONTROLMODE_SDVMPP)
	{
		m_pTestTask = new CTestTask();
	}
	else
	{
		
	}

	if (m_nNewMode == TESTCONTROLMODE_MDVMGRP)
	{
		if (pTestTasks == NULL)
		{
			m_pTestTasks = new CTestTasks();
		}
		else
		{
			m_pTestTasks = pTestTasks;
			m_bTestTasksAttach = TRUE;
		}

		m_pTestTasks->m_strTasksParentPath = m_pXCurrFolder->GetFolderPath(TRUE);
	}
	
}


CString CAtsNewTestTool::GetXTestDbGroupPath()
{
	return m_oTasksFromXDb.m_strXTestDbGroupPath;
}

DWORD CAtsNewTestTool::GetReportType()
{
	return m_dwReportType;
}

BOOL CAtsNewTestTool::IsUseQRCode()
{
	if (g_theAtsNewTestTool->m_nNewMode != TESTCONTROLMODE_MDVMGRP)
	{
		return FALSE;
	}

	if (CQRCodeRead::GetQrCodeEnType() == QRCODE_EncodeType_none)
	{
		return FALSE;
	}

	return TRUE;
}

void CAtsNewTestTool::SetTestType(const CString &strTestType)
{
	m_strTestType = strTestType;

	if (m_strTestType.GetLength() == 0)
	{
		if (m_pTestTypes != NULL)
		{
			CTestType *pTestType = (CTestType*)m_pTestTypes->GetHead();

			if (pTestType != NULL)
			{
				m_strTestType = pTestType->m_strName;
			}
		}
	}

	if (m_pTestTasks != NULL)
	{
		m_pTestTasks->SetTestType(m_strTestType);
	}

	m_dwTkID_Index = ATS_GetTkIDIndex(m_strTestType, m_pTestTypes);
}

//2021-7-31  lijunqing
BOOL Encrypt_CanUseGuideBook(CGuideBook *pGuideBook)
{
	if (Encrypt_IsUseRegisterFile())
	{
		return TRUE;
	}

	if (pGuideBook == NULL)
	{
		return TRUE;
	}

	return pGuideBook->IsAuthority();
}

BOOL CAtsNewTestTool::IsAuthority()
{
	return Encrypt_CanUseGuideBook(m_pTempGuideBook);
}

BOOL CAtsNewTestTool::IsOfflineTestMode()
{
	return m_pTempGuideBook->IsOfflineTestMode();
}

void CAtsNewTestTool::InitByGuideBookFile(const CString &strFile)
{
	m_pTempGuideBook->InitGuideBookAttrs();
	m_pTempGuideBook->Open(strFile, TRUE);
	CXFile *pPpFile = NULL;
	m_strGuideBookFile = GetPathFileNameFromFilePathName(strFile);

	SetEngineProgID(m_pTempGuideBook->m_strPpEngineProgID);

	if (m_pTestTasks != NULL)
	{
		///m_pTestTasks->m_strTemplateFile = strFile;
		m_pTestTasks->tsk_SetGbxmlFile(strFile);
	}

	GetGbTestTypes();

	CTestMacrosFileMngr *pTestMacroFileMngr = CTestMacrosFileMngr::g_pTestMacrosFileMngr;;
	m_pTestMacrosFile = pTestMacroFileMngr->FindByFile(m_pTempGuideBook->m_strTestMacroFileID, m_pTempGuideBook->m_strCommCmdConfigFile);

		if (m_pTestMacrosFile != NULL)
		{
			m_strMacroFileID = m_pTestMacrosFile->m_strID;
		}
		else
		{
			m_strMacroFileID.Empty();
		}
// 	if (m_nNewMode == TESTCONTROLMODE_MDVMGRP)
// 	{
// 		if (m_pTestMacrosFile != NULL)
// 		{
// 			m_strMacroFileID = m_pTestMacrosFile->m_strID;
// 		}
// 		else
// 		{
// 			m_strMacroFileID.Empty();
// 		}
// 	}

	InitExpandMode();

	//2021-1-6 ��ȡģ������  lijunqing
	CDevice *pDevice = m_pTempGuideBook->GetDevice();
	m_astrDvmFiles.RemoveAll();

	if (pDevice != NULL)
	{
		ATS_GetSrcDeviceModelFiles(pDevice->m_strSrcDeviceModelFile, m_astrDvmFiles);
	}
}

CString CAtsNewTestTool::GetSrcDeviceModelFile()
{
	CString strFile;
	long nCount = m_astrDvmFiles.GetCount();
	long nIndex = 0;
	CString strSysPath;
	strSysPath = _P_GetSystemPath();

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strFile = m_astrDvmFiles.GetAt(nIndex);

		if (ATS_ValidateSystemPath(strFile, strSysPath))
		{
			return strFile;
		}
	}

	strFile.Empty();

	return strFile;
}

CString CAtsNewTestTool::XPing_IP(const CString &strIP_TestApp, const CString &strIP_Device)
{
	m_strMsg_IP_Err.Empty();
	char pszIPAddr[64];

	CString_to_char(strIP_TestApp, pszIPAddr);
	m_bHasLink_TestApp = xping(pszIPAddr);

	CString_to_char(strIP_Device, pszIPAddr);
	m_bHasLink_Device = xping(pszIPAddr);

	if (!m_bHasLink_TestApp)
	{
		m_strMsg_IP_Err.Format(_T("������IP %s ������\r\n"), strIP_TestApp);
	}

	if (!m_bHasLink_Device)
	{
		m_strMsg_IP_Err.AppendFormat(_T("����װ��IP %s ������\r\n"), strIP_Device);
	}

	return m_strMsg_IP_Err;
}

//shaolei 20211022 ���²����ǡ�װ�����Զ����е����ݵ�ֵ���Ա㱣��
void CAtsNewTestTool::UpdateTestDefine(CExBaseList *pList, CDvmDataset *pTestDef)
{
	if (pTestDef == NULL)
	{
		return;
	}

	POS pos = pTestDef->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pTestDef->GetNext(pos);
		CExBaseObject *pObj = pList->FindByID(pData->m_strID);

		if (pObj == NULL)
		{
			continue;
		}

		if (pObj->GetClassID() == DTMCLASSID_CVALUE)
		{
			CValue *pValue = (CValue *)pObj;
			pData->m_strValue = pValue->m_strValue;
		}
		else if (pObj->GetClassID() == DVMCLASSID_CDVMVALUE)
		{
			CDvmValue *pValue = (CDvmValue *)pObj;
			pData->m_strValue = pValue->m_strValue;
		}		
	}
}

void CAtsNewTestTool::SetEngineProgID(const CString &strEngineProgID)
{
	if (m_strPpEngineProgID == strEngineProgID)
	{
		return;
	}

	m_strPpEngineProgID = strEngineProgID;

	if (m_pTestTasks != NULL)
	{
		m_pTestTasks->m_strPpEngineProgID = m_strPpEngineProgID;
	}

	if (m_pTestTask != NULL)
	{
		m_pTestTask->m_strPpEngineProgID = m_strPpEngineProgID;
	}

	InitCommConfigEngineByProgID();
}

void CAtsNewTestTool::SetEngineMode(const CString &strEngineMode)
{
	if (m_strEngineMode == strEngineMode)
	{
		return;
	}

	m_strEngineMode = strEngineMode;

	if (m_pTestTasks != NULL)
	{
		m_pTestTasks->m_strEngineMode = m_strEngineMode;
	}

	if (m_pTestTask != NULL)
	{
		m_pTestTask->m_strEngineMode = m_strEngineMode;
	}
}


void CAtsNewTestTool::InitProjectName(CAtsTestDefineInterface *pAtsTestDefine)
{
	BOOL bHasName = FALSE;

	if (pAtsTestDefine != NULL)
	{
		if (pAtsTestDefine->m_strTaskName.GetLength() > 5)
		{
			m_strTestProjectName = pAtsTestDefine->m_strTaskName;
			bHasName = TRUE;
		}
	}

	if (!bHasName)
	{
		m_strTestProjectName = m_strGuideBookFile;
		long nPos = m_strTestProjectName.ReverseFind('.');

		if (nPos > 0)
		{
			m_strTestProjectName = m_strTestProjectName.Left(nPos);
		}

		m_strTestProjectName.AppendFormat(_T("(%s)"), _P_GetProjectID());
	}

	if (m_nNewMode == TESTCONTROLMODE_MDVMGRP)
	{
		m_pTestTasks->SetTasksNameAndID(m_strTestProjectName, m_strTestProjectName);
	}

	if (m_pTestTasks != NULL)
	{
		m_pTestTasks->m_strTasksPath.Format(_T("%s%s\\"), m_pTestTasks->m_strTasksParentPath, m_strTestProjectName);
	}
}

void CAtsNewTestTool::InitExpandMode()
{
	if (TESTCONTROLMODE_MDGBRPT == m_nNewMode 
		|| m_nNewMode == TESTCONTROLMODE_SDVMPP)
	{
		return;
	}

	if (m_nNewMode == TESTCONTROLMODE_MDVMGRP)
	{
		m_oExpandDatas.DeleteAll();
		m_pTempGuideBook->OpenExpandFile(&m_oExpandDatas);
		MdvMgrpTest_InitExpandMode(m_pTempGuideBook->GetExpandFile());
		TestApp_InitExpandMode(m_pTestAppDefine);

		return;
	}

	if (m_pTempGuideBook == NULL)
	{
		return;
	}

	m_oExpandDatas.DeleteAll();
	m_pTempGuideBook->OpenExpandFile(&m_oExpandDatas);
}


long CAtsNewTestTool::GetExpandDataCount()
{
	POS pos = m_oExpandDatas.GetHeadPosition();
	CDvmData *pData = NULL;
	long nSelCount = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_oExpandDatas.GetNext(pos);

		if (pData->m_strValue == _T("1"))
		{
			nSelCount++;
		}
	}

	return nSelCount;
}

BOOL CAtsNewTestTool::IsMgbrptMode()
{
	if (m_pTempGuideBook == NULL)
	{
		return FALSE;
	}

	if (m_pTempGuideBook->m_nTestControlMode == 1)
	{
		if (GetExpandDataCount() > 1)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

CTestTypes* CAtsNewTestTool::GetGbTestTypes()
{
	if (m_pTempGuideBook == NULL)
	{
		m_pTestTypes = Gb_GetTestTypes(NULL);
	}
	else if (m_pTempGuideBook->m_oTestTypes.GetCount() == 0)
	{
		m_pTestTypes = Gb_GetTestTypes(NULL);
	}
	else
	{
		m_pTestTypes = Gb_GetTestTypes(m_pTempGuideBook);
	}

	return m_pTestTypes;
}


BOOL CAtsNewTestTool::CanCreateMdTask(CString &strMsg)
{
	if (m_pTestTask == NULL)
	{
		return FALSE;
	}

	if (m_pTestTask->GetCount() == 0)
	{
		strMsg = g_sLangTxt_NoAddDevTestRep/*_T("û�����װ�ò��Ա���")*/;
		return FALSE;
	}

	if (m_pTestTask->GetCount() == 1)
	{
		strMsg = g_sLangTxt_OlAddOnRep/*_T("ֻ�����һ��װ�ò��Ա���")*/;
		return FALSE;
	}

	POS pos = m_pTestTask->GetHeadPosition();
	POS posCurr = NULL;
	CTestProject *p = NULL, *pCurr = NULL;
	BOOL bCan = TRUE;

	while (pos != NULL)
	{
		p = (CTestProject *)m_pTestTask->GetAt(pos);
		m_pTestTask->GetNext(pos);
		posCurr = pos;

		while (posCurr != NULL)
		{
			pCurr = (CTestProject *)m_pTestTask->GetNext(posCurr);

			if (pCurr->m_strID == p->m_strID)
			{
				strMsg.Format(g_sLangTxt_NameSame/*_T("װ�ñ����б�ڡ�%d����ڡ�%d�����ơ�%s����ͬ")*/
					, m_pTestTask->FindIndex(p), m_pTestTask->FindIndex(pCurr), p->m_strName);
				bCan = FALSE;
				break;
			}

			if (pCurr->m_strLocalID == p->m_strLocalID)
			{
				strMsg.Format(g_sLangTxt_IPSame/*_T("װ�ñ����б�ڡ�%d����ڡ�%d��IP��%s����ͬ")*/
					, m_pTestTask->FindIndex(p), m_pTestTask->FindIndex(pCurr), p->m_strLocalID);
				bCan = FALSE;
				break;
			}
		}

		if (!bCan)
		{
			break;
		}
	}

	return bCan;
}


void CAtsNewTestTool::SetGuideBookFile(const CString &strFile)
{
	m_strGuideBookFile = strFile;
	POS pos = m_pTestTask->GetHeadPosition();
	CTestProject *p = NULL;

	while (pos != NULL)
	{
		p = (CTestProject *)m_pTestTask->GetNext(pos);
		p->tsk_SetGbxmlFile(strFile);
	}
}


CTestProject* CAtsNewTestTool::InsertNewTestProject(CWnd *pWnd)
{
	CString strDeviceFile;

	if (!ats_GetDeviceModeleFiles(strDeviceFile, pWnd))
	{
		return NULL;
	}

	CString strName, strPostfix, strFile;
	strFile = GetPathFileNameFromFilePathName(strDeviceFile);
	ParseFileNameAndPostfix(strFile, strName, strPostfix);

	CTestProject *pNew = new CTestProject();
	strName.Trim();
	pNew->m_strName = strName;
	pNew->m_strID = strName;
	pNew->m_strLocalID = _T("192.168.1.10");
	pNew->m_strPpDeviceFile = strDeviceFile;
	pNew->m_strPpEngineProgID = g_strPpEngineProgIDMms;
	pNew->tsk_SetGbxmlFile(m_strGuideBookFile);
	m_pTestTask->AddNewChild(pNew, TRUE);

	return pNew;
}


BOOL CAtsNewTestTool::OnBnClickedBtnDvmfile(CTestProject *pProject, CWnd *pWnd)
{
	if (pProject == NULL)
	{
		return FALSE;
	}

	CString strDeviceFile;

	if (!ats_GetDeviceModeleFiles(strDeviceFile, pWnd))
	{
		return FALSE;
	}

	CString strName, strPostfix, strFile;
	strFile = GetPathFileNameFromFilePathName(strDeviceFile);
	ParseFileNameAndPostfix(strFile, strName, strPostfix);

	pProject->m_strName = strName;
	pProject->m_strID = strName;
	pProject->m_strPpDeviceFile = strDeviceFile;
	
	return TRUE;
}

BOOL CAtsNewTestTool::OnBnClickedBtnImport(CWnd *pWnd)
{
	CString strTaskFile;

	if (!ats_GetMdTestFile(strTaskFile, pWnd))
	{
		return FALSE;
	}

	m_pTestTask->OpenTaskFile(strTaskFile);
	SetGuideBookFile(m_strGuideBookFile);
	
	return TRUE;
}


void CAtsNewTestTool::OnBnClickedBtnExport(CWnd *pWnd)
{
	CString strFilter;
	ats_GetMdTestFileFilter(strFilter);

	CString strMdTaskFile;
	CString strRoot;
	strRoot = _P_GetSoftRegKey();

	if( !PopupSaveAsFileDialog(pWnd, strMdTaskFile, strRoot, _T("MdTestFilePath"),strFilter, g_strGuideBookMdTaskPostfix) )
	{
		return;
	}

	m_pTestTask->SaveAs(strMdTaskFile);
}

BOOL CAtsNewTestTool::CanCreateSdvMppTask(CString &strMsg)
{
	if (m_pTestTask == NULL)
	{
		return FALSE;
	}

	if (m_pTestTask->GetCount() == 0)
	{
		strMsg = g_sLangTxt_NoAddTestRpt/*_T("û����Ӳ��Ա���")*/;
		return FALSE;
	}

	if (m_pTestTask->GetCount() == 1)
	{
		strMsg = g_sLangTxt_OneTestRpt/*_T("ֻ�����һ�����Ա���")*/;
		return FALSE;
	}

	POS pos = m_pTestTask->GetHeadPosition();
	POS posCurr = NULL;
	CTestProject *p = NULL, *pCurr = NULL;
	BOOL bCan = TRUE;

	while (pos != NULL)
	{
		p = (CTestProject *)m_pTestTask->GetAt(pos);
		m_pTestTask->GetNext(pos);
		posCurr = pos;

		if (p->m_strPpEngineProgID == g_strPpEngineProgID)
		{
			if (p->tsk_GetPpxmlFile().GetLength() == 0)
			{
				strMsg.Format(g_sLangTxt_NoSelPrtcTem/*_T("װ�ñ����б�ڡ�%d��û��ѡ���Լģ��")*/
					, m_pTestTask->FindIndex(p));
				bCan = FALSE;
				break;
			}
		}

		if (p->m_strPpDeviceFile.GetLength() == 0)
		{
			strMsg.Format(g_sLangTxt_NoSelFile/*_T("װ�ñ����б�ڡ�%d��û��ѡ�����ļ�")*/
				, m_pTestTask->FindIndex(p));
			bCan = FALSE;
			break;
		}

		while (posCurr != NULL)
		{
			pCurr = (CTestProject *)m_pTestTask->GetNext(posCurr);

			if (pCurr->m_strID == p->m_strID)
			{
				strMsg.Format(g_sLangTxt_NameSame/*_T("װ�ñ����б�ڡ�%d����ڡ�%d�����ơ�%s����ͬ")*/
					, m_pTestTask->FindIndex(p), m_pTestTask->FindIndex(pCurr), p->m_strName);
				bCan = FALSE;
				break;
			}

			//if (pCurr->m_strPpTemplateFile == p->m_strPpTemplateFile)
			if (pCurr->tsk_GetPpxmlFile() == p->tsk_GetPpxmlFile())
			{
				strMsg.Format(g_sLangTxt_PrtcSame/*_T("װ�ñ����б�ڡ�%d����ڡ�%d����Լģ�塾%s����ͬ")*/
					, m_pTestTask->FindIndex(p), m_pTestTask->FindIndex(pCurr), p->tsk_GetPpxmlFile(FALSE));
				bCan = FALSE;
				break;
			}
		}

		if (!bCan)
		{
			break;
		}
	}

	return bCan;
}


CTestProject* CAtsNewTestTool::SdvMppTest_OnBnClickedBtnInsert(CWnd *pWnd)
{
	CTestProject *pNew = InsertNewTestProject(pWnd);

	if (pNew != NULL)
	{
		sdvmpp_UpdateProjectName(pNew);
	}

	return pNew;
}



BOOL CAtsNewTestTool::SdvMppTest_OnBnClickedBtnImport(CWnd *pWnd)
{
	CString strTaskFile;

	if (!ats_GetSdvMppTestFile(strTaskFile, pWnd))
	{
		return FALSE;
	}
	
	m_pTestTask->OpenTaskFile(strTaskFile);
	SetGuideBookFile(m_strGuideBookFile);

	return TRUE;
}

void CAtsNewTestTool::SdvMppTest_OnBnClickedBtnExport(CWnd *pWnd)
{
	CString strFilter;
	ats_GetSdvMppTestFileFilter(strFilter);

	CString strMdTaskFile;
	CString strRoot;
	strRoot = _P_GetSoftRegKey();

	if( !PopupSaveAsFileDialog(pWnd, strMdTaskFile, strFilter, g_strGuideBookSdvMppTaskPostfix) )
	{
		return;
	}

	m_pTestTask->SaveAs(strMdTaskFile);
}


BOOL CAtsNewTestTool::MdvMgrpTest_InitExpandMode(const CString &strExpandFile)
{
	//BOOL bRet = m_oTestGlobalDefine.OpenXmlFile(strExpandFile, CGbXMLKeys::TestDefineKey(), CGbXMLKeys::g_pGbXMLKeys);
	BOOL bRet = m_oTestGlobalDefine.OpenTestDefineFile(strExpandFile, CGbXMLKeys::TestDefineKey(), CGbXMLKeys::g_pGbXMLKeys);

	m_pExpandDatas = (CDvmDataset*)m_oTestGlobalDefine.FindByID(DSID_COMMCMDMCONFIG);
	m_pExpandDatasAutoSet = (CDvmDataset*)m_oTestGlobalDefine.FindByID(DSID_COMMCMDMCONFIG_AUTOSET);
	m_pReportSNGen = (CDvmDataset*)m_oTestGlobalDefine.FindByID(DSID_REPORT_SN_GEN);
	m_pTaskReportSNGen = (CDvmDataset*)m_oTestGlobalDefine.FindByID(DSID_TASK_REPORT_SN_GEN);
	m_pTestAppDefine = (CDvmDataset*)m_oTestGlobalDefine.FindByID(DSID_TESTAPP_DEF);
	m_pDeviceAttrsDefine = (CDvmDataset*)m_oTestGlobalDefine.FindByID(DSID_DEVICEATTR);
	m_dwReportType = m_oTestGlobalDefine.m_nShowWordRpt;
	bRet = FALSE;

#ifdef _UNICODE
	if (_wcsicmp(m_strPrevExpandFile, strExpandFile) != 0)
#else
	if (stricmp(m_strPrevExpandFile, strExpandFile) != 0)
#endif
	{
		if (!m_bTestTasksAttach)
		{
			m_pTestTasks->DeleteTestTasks();
		}

		bRet = TRUE;
	}

	m_strPrevExpandFile = strExpandFile;

	return bRet;
}



BOOL CAtsNewTestTool::MdvMgrpTest_OnBnClickedBtnImport(CWnd *pWnd)
{
	CString strFilter;
	ats_GetMdvMgrpTestFileFilter(strFilter);

	CString strMdvMgrpTaskFile;

	if( !PopupOpenFileDialog(pWnd, strMdvMgrpTaskFile, strFilter, g_strGuideBookMdvMgrpTaskPostfix) )
	{
		return FALSE;
	}

	m_pTestTasks->DeleteTestTasks();
	m_pTestTasks->Init();
	m_pTestTasks->OpenTasksFile(strMdvMgrpTaskFile);
	m_pTestTasks->InitAllCmdCfgChannels();

	return TRUE;
}

void CAtsNewTestTool::MdvMgrpTest_OnBnClickedBtnExport(CWnd *pWnd)
{
	CString strFilter;
	ats_GetMdvMgrpTestFileFilter(strFilter);

	CString strMdvMgrpTaskFile;

	if( !PopupSaveAsFileDialog(pWnd, strMdvMgrpTaskFile, strFilter, g_strGuideBookMdvMgrpTaskPostfix) )
	{
		return;
	}

	m_pTestTasks->SaveTasksFile(strMdvMgrpTaskFile);
	m_pTestTasks->SavePoProjectFile();
}

void CAtsNewTestTool::MdvMgrpTest_InsertDevices(const CString &strPpTemplateFile, const CString &strDevice, long nDvNum)
{
	if (m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		MdvMgrpTest_InsertMmsDevices(strDevice, nDvNum);
	}
	else if (m_strPpEngineProgID == g_strPpEngineProgID)
	{
		MdvMgrpTest_InsertPpDevices(strPpTemplateFile, strDevice, nDvNum);
	}
	else
	{
		MdvMgrpTest_InsertMmsDevices(strDevice, nDvNum);
	}
}

//shaolei 20210911
void CAtsNewTestTool::MdvMgrpTest_InsertIotDevices(const CString &strTemplate, const CString &strDevice, long nDvNum)
{
	CTestTask *pNew = NULL;

	//������չ���ö���
	CDvmData *pMaxID = NULL;//(CDvmData*)m_pExpandDatas->GetTail();
	//ͨѶ���ã���ȡ������Ϣ���˴��̶�����һ��TcpClient
	CDeviceCmmConfig oDeviceCmmConfig;
	CCmmNetConfig *pNet = new CCmmNetConfig();
	oDeviceCmmConfig.AddNewChild(pNet);
	CCmmTcpClientConfig *pTcpClient = new CCmmTcpClientConfig();
	pNet->AddNewChild(pTcpClient);

	if (m_pExpandDatas != NULL)
	{
		pMaxID = (CDvmData*)m_pExpandDatas->GetTail();
	}

	while (nDvNum > 0)
	{
		pNew = new CTestTask();
		pNew->m_strDeviceFile = strDevice;
		pNew->tsk_SetPpxmlFile(strTemplate);
		pNew->m_strID = Pp_GetPopCfgDeviceName(strTemplate, strDevice, m_pTestTasks, FALSE);
		pNew->m_strName = pNew->m_strID;
		pNew->m_strLocalID = pNew->m_strID;
		pNew->tsk_SetGbxmlFile(m_pTestTasks->tsk_GetGbxmlFile());//m_strTemplateFile;
		//pNew->m_strPpEngineProgID = m_pTestTasks->m_strPpEngineProgID;
		pNew->InitCommCmdManyConfig(m_pExpandDatas);

		if (pMaxID != NULL)
		{
			pNew->m_strMaxMgrpID = pMaxID->m_strID;
		}

		pNew->InitDeviceAttr(m_pDeviceAttrsDefine); //װ������
		pNew->InitDeviceCmmConfig(&oDeviceCmmConfig); //ͨѶ����
		

		m_pTestTasks->AddNewChild(pNew);
		m_pTestTasks->InitProjectByCommCmdManyConfig(pNew);
		nDvNum--;
	}

	InsertPpDevicesCmmConfig(&oDeviceCmmConfig);
	m_pTestTasks->InitAllCmdCfgChannels();
}

void CAtsNewTestTool::MdvMgrpTest_InsertPpDevices(const CString &strTemplate, const CString &strDevice, long nDvNum)
{
	CString strCmmCfgFile;
	CTestTask *pNew = NULL;

	//ͨѶ�����ļ�����ȡ������Ϣ
	CDeviceCmmConfig oDeviceCmmConfig;
	strCmmCfgFile = pp_GetDeviceCmmCfgFile(strDevice);
	oDeviceCmmConfig.OpenXmlFile(strCmmCfgFile, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey, CDeviceModelXmlKeys::g_pXmlRWKeys);

	//������չ���ö���
	CDvmData *pMaxID = NULL;//(CDvmData*)m_pExpandDatas->GetTail();

	if (m_pExpandDatas != NULL)
	{
		pMaxID = (CDvmData*)m_pExpandDatas->GetTail();
	}

	while (nDvNum > 0)
	{
		pNew = new CTestTask();
		pNew->m_strDeviceFile = strDevice;
		pNew->tsk_SetPpxmlFile(strTemplate);
		pNew->m_strID = Pp_GetPopCfgDeviceName(strTemplate, strDevice, m_pTestTasks, FALSE);
		pNew->m_strName = pNew->m_strID;
		pNew->m_strLocalID = pNew->m_strID;
		pNew->tsk_SetGbxmlFile(m_pTestTasks->tsk_GetGbxmlFile());//m_strTemplateFile;
		pNew->m_strPpEngineProgID = m_pTestTasks->m_strPpEngineProgID;
		pNew->InitCommCmdManyConfig(m_pExpandDatas);

		if (pMaxID != NULL)
		{
			pNew->m_strMaxMgrpID = pMaxID->m_strID;
		}

		pNew->InitDeviceAttr(m_pDeviceAttrsDefine); //װ������
		pNew->InitDeviceCmmConfig(&oDeviceCmmConfig); //ͨѶ����

		m_pTestTasks->AddNewChild(pNew);
		m_pTestTasks->InitProjectByCommCmdManyConfig(pNew);
		nDvNum--;
	}

	InsertPpDevicesCmmConfig(&oDeviceCmmConfig);
	m_pTestTasks->InitAllCmdCfgChannels();
}

void CAtsNewTestTool::InsertPpDevicesCmmConfig(CDeviceCmmConfig *pCmmConfig)
{
	CCmmSerialConfig *pCmmSerialConfig = pCmmConfig->GetConfigSerial();

	if (pCmmSerialConfig != NULL)
	{
		InsertPpDevicesCmmConfig_Serial(pCmmSerialConfig);
		return;
	}

	CCmmNetConfig *pCmmNetConfig = pCmmConfig->GetConfigNet();

	if (pCmmNetConfig != NULL)
	{
		InsertPpDevicesCmmConfig_Net(pCmmNetConfig);
		return;
	}

	CCmmMmsConfig *pCmmMmsConfig = pCmmConfig->GetConfigMms();

	if (pCmmMmsConfig != NULL)
	{
		InsertPpDevicesCmmConfig_Mms(pCmmMmsConfig);
		return;
	}
}

void CAtsNewTestTool::InsertPpDevicesCmmConfig_Serial(CCmmSerialConfig *pCmmConfig)
{
	CDeviceCmmConfig *pTestDefine = (CDeviceCmmConfig*)m_oTestGlobalDefine.FindByID(DSID_CommConfig_Serial);

	m_pTestTasks->InsertPpDevicesCmmConfig_Serial(pTestDefine);
}

void CAtsNewTestTool::InsertPpDevicesCmmConfig_Net(CCmmNetConfig *pCmmConfig)
{
	CDeviceCmmConfig *pTestDefine = (CDeviceCmmConfig*)m_oTestGlobalDefine.FindByID(DSID_CommConfig_Net);

	m_pTestTasks->InsertPpDevicesCmmConfig_Net(pTestDefine);
}

void CAtsNewTestTool::InsertPpDevicesCmmConfig_Mms(CCmmMmsConfig *pCmmConfig)
{
	CDeviceCmmConfig *pTestDefine = (CDeviceCmmConfig*)m_oTestGlobalDefine.FindByID(DSID_CommConfig_Mms);

	m_pTestTasks->InsertPpDevicesCmmConfig_Mms(pTestDefine);
}


void CAtsNewTestTool::MdvMgrpTest_InsertPpDevices(CTestTasks *pSrcTestTasks)
{
	CString strTemplate, strDevice, strCmmCfgFile;
	strTemplate = pSrcTestTasks->tsk_GetPpxmlFile();
	strDevice = pSrcTestTasks->m_strDeviceFile;
	long nDvNum = pSrcTestTasks->GetCount();
	CTestTask *pNew = NULL;
	CTestTask *pSrc = NULL;
	long nTaskIndex = 0;
	CDvmDataset *pDeviceAttr = NULL;

	//ͨѶ�����ļ�����ȡ������Ϣ
	CDeviceCmmConfig oDeviceCmmConfig;
	strCmmCfgFile = pp_GetDeviceCmmCfgFile(strDevice);
	oDeviceCmmConfig.OpenXmlFile(strCmmCfgFile, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey, CDeviceModelXmlKeys::g_pXmlRWKeys);

	//������չ���ö���
	CDvmData *pMaxID = NULL;//(CDvmData*)m_pExpandDatas->GetTail();

	if (m_pExpandDatas != NULL)
	{
		pMaxID = (CDvmData*)m_pExpandDatas->GetTail();
	}

	while (nDvNum > 0)
	{
		pSrc = (CTestTask *)pSrcTestTasks->GetAtIndex(nTaskIndex);
		pDeviceAttr = pSrc->GetDeviceAttr(FALSE);
		pNew = new CTestTask();

		pNew->m_strDeviceFile = strDevice;
		pNew->tsk_SetPpxmlFile( strTemplate);
		//pNew->m_strID = Pp_GetPopCfgDeviceName(strTemplate, strDevice, m_pTestTasks, FALSE);
		//pNew->m_strName = pNew->m_strID;
		pNew->m_strName = pSrc->m_strName;
		pNew->m_strID = pSrc->m_strID;
		pNew->tsk_SetGbxmlFile(m_pTestTasks->tsk_GetGbxmlFile(FALSE));//m_strTemplateFile;
		pNew->m_strPpEngineProgID = m_pTestTasks->m_strPpEngineProgID;
		pNew->InitCommCmdManyConfig(m_pExpandDatas);

		if (pMaxID != NULL)
		{
			pNew->m_strMaxMgrpID = pMaxID->m_strID;
		}


		pNew->InitDeviceAttr(m_pDeviceAttrsDefine); //װ������

		if (pDeviceAttr != NULL)
		{
			pNew->InitDeviceAttrValueEx(pDeviceAttr); //װ������
		}

		pNew->InitDeviceCmmConfig(&oDeviceCmmConfig); //ͨѶ����

		m_pTestTasks->AddNewChild(pNew);
		m_pTestTasks->InitProjectByCommCmdManyConfig(pNew);
		nDvNum--;
		nTaskIndex++;
	}

	InsertPpDevicesCmmConfig(&oDeviceCmmConfig);
	m_pTestTasks->InitAllCmdCfgChannels();
}

//2021-3-14  lijunqing  
void MdvMgrpTest_UpdateTasksByDvmFile(CTestTasks *pTestTasks, const CString &strDvmFile)
{
	POS pos = pTestTasks->GetHeadPosition();
	CTestTask *pTask = NULL;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pTestTasks->GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}
		
		pTask  =(CTestTask*)p;
		pTask->m_strDeviceFile = strDvmFile;
		pTask->m_strID = Pp_GetPopCfgDeviceName(_T(""), strDvmFile, pTestTasks, FALSE);
		pTask->m_strLocalID = pTask->m_strID;
		pTask->m_strName = pTask->m_strID;
	}
}

void CAtsNewTestTool::MdvMgrpTest_InsertMmsDevices(const CString &strDvmFile, long nDvNum)
{
	CTestTask *pNew = NULL;

	//ͨѶ�����ļ�����ȡ������Ϣ
	CDeviceCmmConfig oDeviceCmmConfig;
	oDeviceCmmConfig.AddConfigMms();

	//������չ���ö���
	CDvmData *pMaxID = NULL;//(CDvmData*)m_pExpandDatas->GetTail();

	if (m_pExpandDatas != NULL)
	{
		pMaxID = (CDvmData*)m_pExpandDatas->GetTail();
	}

	while (nDvNum > 0)
	{
		pNew = new CTestTask();
		pNew->m_strDeviceFile = strDvmFile;
		pNew->m_strID = Pp_GetPopCfgDeviceName(_T(""), strDvmFile, m_pTestTasks, FALSE);
		pNew->m_strLocalID = pNew->m_strID;
		pNew->m_strName = pNew->m_strID;
		pNew->tsk_SetGbxmlFile(m_pTestTasks->tsk_GetGbxmlFile(FALSE));
		pNew->m_strPpEngineProgID = m_pTestTasks->m_strPpEngineProgID;
		pNew->InitCommCmdManyConfig(m_pExpandDatas);

		if (pMaxID != NULL)
		{
			pNew->m_strMaxMgrpID = pMaxID->m_strID;
		}

		pNew->InitDeviceAttr(m_pDeviceAttrsDefine); //װ������
		pNew->InitDeviceCmmConfig(&oDeviceCmmConfig); //ͨѶ����

		m_pTestTasks->AddNewChild(pNew);

		//shaolei 2023-11-3  ע�ʹ���
		//������Task������������������������ص�·������ע��
		m_pTestTasks->InitProjectByCommCmdManyConfig(pNew);    
		nDvNum--;
	}

	InsertPpDevicesCmmConfig(&oDeviceCmmConfig);
	m_pTestTasks->InitAllCmdCfgChannels();
}


void CAtsNewTestTool::MdvMgrpTest_InsertMmsDevices(CTestTasks *pTestTasks)
{
	ASSERT (FALSE);
}

void CAtsNewTestTool::AutoSetExpandDatas(CTestTask *pTestTask)
{
	if (m_pExpandDatasAutoSet == NULL)
	{
		return;
	}

	CDvmData *pAttr = (CDvmData*)m_pExpandDatasAutoSet->FindByID(DSID_DEVICEATTR);

	if (pAttr == NULL)
	{
		return;
	}

	CDvmData *pAttrExpand = (CDvmData*)m_pDeviceAttrsDefine->FindByID(pAttr->m_strValue);

	if (pAttrExpand == NULL)
	{
		return;
	}

	CDvmData *pOptrFunc = (CDvmData*)m_pExpandDatasAutoSet->FindByID(_T("OptrFunc"));

	if (pOptrFunc == NULL)
	{
		return;
	}

	if (pOptrFunc->m_strValue == _T("right"))
	{
		CDvmValue *pValue = (CDvmValue*)pOptrFunc->GetHead();

		if (pValue == NULL)
		{
			return;
		}

		long nLen = CString_To_long(pValue->m_strValue);
		CString strText = pAttrExpand->m_strValue.Right(nLen);
		long nIndex = CString_To_long(strText) - 1;
		CDvmData *pMaxID = (CDvmData*)m_pExpandDatas->GetAtIndex(nIndex);

		if (pMaxID != NULL)
		{
			pTestTask->m_strMaxMgrpID = pMaxID->m_strID;
			pTestTask->SetCommCmdManyConfigValue(pTestTask->m_strMaxMgrpID);
			m_pTestTasks->InitProjectByCommCmdManyConfig(pTestTask);
		}
	}
}

void CAtsNewTestTool::ReportSNGenClear()
{
	m_pTestTasks->ReportSNGenClear();
}

void CAtsNewTestTool::ReportSNGen()
{
	m_pTestTasks->InitProjectID();
	m_pTestTasks->TaskReportSNGen(m_pTaskReportSNGen, m_strMacroFileID);
	m_pTestTasks->ReportSNGen(m_pReportSNGen, m_strMacroFileID);
}

void CAtsNewTestTool::SetShowWordRpt(DWORD dwReportType)
{
	ats_SetReportFillProgID(dwReportType);
	m_dwReportType = dwReportType;

	if (m_dwReportType == m_oTestGlobalDefine.m_nShowWordRpt)
	{
		return;
	}

	m_oTestGlobalDefine.m_nShowWordRpt = m_dwReportType;
	m_oTestGlobalDefine.SaveTestDefineFile(CGbXMLKeys::g_pGbXMLKeys);
}

CTestTask* CAtsNewTestTool::MdvMgrpTest_OnQRCodeInput()
{
	// 	m_edtDeviceAttrBarCode.SetWindowText(m_oXBarcodeStrParser.GetQRCodeData());
	// 	m_oXBarcodeStrParser.GetDatas(m_pDeviceAttrsDefine);
	CQRCodeRead::GetDatas(m_pDeviceAttrsDefine);

	CTestTask *pFind = m_pTestTasks->FindTestTask(m_pDeviceAttrsDefine);

	if (pFind != NULL)
	{
		return NULL;
	}

	pFind = m_pTestTasks->FindTestTaskByEmptyDeviceAttr();

	if (pFind == NULL)
	{
		return pFind;
	}

	pFind->InitDeviceAttrValue(m_pDeviceAttrsDefine);
	AutoSetExpandDatas(pFind);

	//2020-1-3 lijunqing �������
	m_pDeviceAttrsDefine->ResetDvmDataValues();

	return pFind;
}

void CAtsNewTestTool::MdvMgrpTest_OnBnClickedBtnDeleteall()
{
	CExBaseList listTask;
	m_pTestTasks->SelectAllTestTask(listTask);
	POS pos = listTask.GetHeadPosition();
	CTestTask *pTestTask = NULL;
	long nRow = 2;

	while (pos != NULL)
	{
		pTestTask = (CTestTask *)listTask.GetNext(pos);
		m_pTestTasks->Delete(pTestTask);
	}

	listTask.RemoveAll();
	m_pTestTasks->InitAllCmdCfgChannels();
}


void CAtsNewTestTool::TestApp_InitExpandMode(CDvmDataset *pTestAppDefine)
{
	m_pTestAppDefine = pTestAppDefine;
	//m_pTestApp = m_pTestTasks->GetTestApp();

	//shaolei ע�ʹ˴� 20210913
	//NewTestTool�Ĳ�������Ϣ��ֱ�Ӵ�TestTasks����ֵ���ᵼ�´�����ͼ�󣬲�������Ϣ��ɾ��
	//CTestControl��m_oTestTasks������
	if (m_pTestApp == NULL)
	{
		m_pTestTasks->GetTestApp();
		m_pTestApp = new CDvmDataset();
		m_pTestApp->m_strName = DSID_TESTAPP;
		m_pTestApp->m_strID = m_pTestApp->m_strName;
		/*(CDvmDataset *)m_pTestTasks->GetTestApp()->CloneEx(TRUE, TRUE);*/
	}
}

CDvmData*  CAtsNewTestTool::TestApp_AddTestApp(CValues *pValues)
{
	if (m_pTestAppDefine == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("AtsNewTestTool::TestApp_AddTestApp: û�ж�������Ƕ���"));
		return NULL;
	}

	CDvmData *pTestApp = m_pTestTasks->AddTestApp(pValues, m_pTestAppDefine);

	//��¼�����Ƕ��壬�Ա��浽�ļ�
	UpdateTestDefine(pValues, m_pTestAppDefine);

	return pTestApp;
}

CDvmData* CAtsNewTestTool::TestApp_AddTestApp(CDvmDataset *pTestApp)
{
	CValues oValues;
	POS pos = pTestApp->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pTestApp->GetNext(pos);
		oValues.AddNew(pData->m_strID, pData->m_strName, pData->m_strValue);
	}

	return TestApp_AddTestApp(&oValues);
}

CDvmData* CAtsNewTestTool::TestApp_AddTestApp(CDvmData *pTestApp)
{
	return m_pTestTasks->AddTestApp(pTestApp);
}

CDvmData* CAtsNewTestTool::TestApp_AddTestApp(CDataGroup *pTestApp)
{
	CValues oValues;
	POS pos = pTestApp->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pTestApp->GetNext(pos);
		oValues.AddNew(pData->m_strID, pData->m_strName, pData->m_strValue);
	}

	return TestApp_AddTestApp(&oValues);
}

void CAtsNewTestTool::BeforeCreate(const CString &strTestType)
{
	SetTestType(strTestType);
	CTCtrlCntrWorkSpace::s_SetTkIDIndex(m_dwTkID_Index);

	//�������к��Զ�����
	if (m_nNewMode == TESTCONTROLMODE_MDVMGRP)
	{
		ReportSNGen();
	}
}

//////////////////////////////////////////////////////////////////////////
//
void CAtsNewTestTool::InitByAtsRpcTestDefine(CAtsTestDefineInterface *pAtsTestDefine, CXFolder *pFolder)
{
	CString strGbFile, strEngineProgID, strTestType, strEngineMode;
	long nDeviceCount = pAtsTestDefine->m_pDevices->GetCount();

	if (nDeviceCount == 0)
	{
		return;
	}

	if (!pAtsTestDefine->GetGuideBookFile(strGbFile))
	{
		return;
	}

	//����֮ǰ�İ汾��Ĭ��Ϊ��װ�ö���
	BOOL bMdvMode = TRUE;

	if (pAtsTestDefine->m_strTestMode == g_strGuideBookBinaryPostfix)
	{
		bMdvMode = FALSE;
	}

	if (bMdvMode)
	{
		InitAtsNewTestTool(TESTCONTROLMODE_MDVMGRP, pFolder);
	}

	pAtsTestDefine->GetEngineProgID(strEngineProgID);
	pAtsTestDefine->GetEngineMode(strEngineMode);  //shaolei 2023-11-2
	pAtsTestDefine->GetPpxmlFile(m_strPpTemplateFile);  //��װ��ģʽ�£��˴�ֻ�ܻ�ȡ��һ̨��
	pAtsTestDefine->GetDvmFile(m_strDeviceFile);    //��װ��ģʽ�£��˴�ֻ�ܻ�ȡ��һ̨��
	InitByGuideBookFile(strGbFile);
	SetEngineProgID(strEngineProgID);
	SetEngineMode(strEngineMode);  //shaolei 2023-11-2
	InitProjectName(pAtsTestDefine);

	m_strTemplateFile = strGbFile;
	m_strGuideBookFile = strGbFile;

	//shaolei 20210810
	CTCtrlCntrWorkSpace::s_SetPpTemplateFile(m_strPpTemplateFile);
	CTCtrlCntrWorkSpace::s_SetPpDeviceFile(m_strDeviceFile);
	CTCtrlCntrWorkSpace::s_SetPpEngineProgID(strEngineProgID);

	//��Ӳ�����
	InitByAtsRpcTestDef_AddTestApp(pAtsTestDefine);
	m_pTestApp->AppendCloneEx( *(m_pTestTasks->GetTestApp()) );

	if (!bMdvMode)
	{
		return;
	}

	//���װ��
	InitByAtsRpcTestDef_AddDevices(pAtsTestDefine);
	//��Ӽ����׼
	InitByAtsRpcTestDef_AddInspectionBases(pAtsTestDefine);
	//���Ӽ�����Ա
	InitByAtsRpcTestDef_AddTesters(pAtsTestDefine);
	//��������ȫ������
	InitByAtsRpcTestDef_AddGlobalDatas(pAtsTestDefine);

	//shaolei 2023-10-30 ��������
	if (pAtsTestDefine->GetTestType(strTestType))
	{
		m_pTestTasks->SetTestType(strTestType);
	}

	//2021-10-1  lijunqing
	InitTasksPpEngineProgID();

	//shaolei 2023-11-2
	InitTasksEngineMode();

	m_pTestTasks->SaveTasksFileByParentPath();
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddTestApp(CAtsTestDefineInterface *pAtsTestDefine)
{
	POS pos = pAtsTestDefine->m_pTestApps->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pAtsTestDefine->m_pTestApps->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			TestApp_AddTestApp((CDvmData *)p);
		}
		else if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			//�����ݹ����Ĳ����Ƕ��壬ÿһ��������ת��һ��CDvmData����ŵ�m_pTestAppָ��
			//�����ǵĶ���ÿ�����������磺DeviceSN��remote-ip�ȣ���Ϊһ��CDvmValue��š�
			//��ҪExpandData.xml�ж���Ĳ����ǣ���(CDataGroup *)p�ж���Ĳ���һ��
			TestApp_AddTestApp((CDataGroup *)p);
		}
	}
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevices(CAtsTestDefineInterface *pAtsTestDefine)
{
// 	m_strPpEngineProgID = g_strPpEngineProgIDMms;
// 	pAtsTestDefine->GetEngineProgID(m_strPpEngineProgID);

	if (m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		InitByAtsRpcTestDef_AddDevices_MMS(pAtsTestDefine);
	}
	else if (m_strPpEngineProgID == g_strPpEngineProgID)
	{
		InitByAtsRpcTestDef_AddDevices_PP(pAtsTestDefine);
	}
	else if (m_strPpEngineProgID == g_strIotEngineProgID)
	{
		InitByAtsRpcTestDef_AddDevices_Iot(pAtsTestDefine);
	}
	else
	{
		InitByAtsRpcTestDef_AddDevices_MMS(pAtsTestDefine);
	}

	//����װ������
	InitByAtsRpcTestDef_AddDevice_Attrs(pAtsTestDefine);
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevice_Attrs(CAtsTestDefineInterface *pAtsTestDefine)
{
	CTestTask *p = NULL;
	CExBaseList listTask;
	m_pTestTasks->SelectAllTestTask(listTask);
	POS pos = listTask.GetHeadPosition();
	CDvmDataset *pDeviceAttr = NULL;
	CExBaseObject *pAtsRpcDevice = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = (CTestTask *)listTask.GetNext(pos);
		pDeviceAttr = p->GetDeviceAttr(FALSE);

		if (pDeviceAttr == NULL)
		{
			continue;
		}

		pAtsRpcDevice = pAtsTestDefine->m_pDevices->GetAtIndex(nIndex);

		if (pAtsRpcDevice->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			InitByAtsRpcTestDef_AddDevice_Attrs(pDeviceAttr, (CDataGroup*)pAtsRpcDevice);
		}
		else if (pAtsRpcDevice->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			InitByAtsRpcTestDef_AddDevice_Attrs(pDeviceAttr, (CDvmData*)pAtsRpcDevice);
		}

		//���Դ���
// 		CString strPath;
// 		strPath.AppendFormat(_T("D:\\0\\InitByAtsRpcTestDef_AddDevices_Attrs_%d.xml"), nIndex);
// 		pDeviceAttr->SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);

		nIndex++;
	}

	listTask.RemoveAll();
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevice_Attrs(CDvmDataset *pDeviceAttrs, CDataGroup *pAtsDevice)
{
	CDvmData oDataDevice;
	POS pos = pAtsDevice->GetHeadPosition();
	CDvmData *pAttr = NULL;

	while (pos != NULL)
	{
		pAttr = (CDvmData *)pAtsDevice->GetNext(pos);
		oDataDevice.AddValue(pAttr->m_strID, pAttr->m_strValue);
	}

	InitByAtsRpcTestDef_AddDevice_Attrs(pDeviceAttrs, &oDataDevice);

	//��¼װ��������Ϣ���Ա㱣��
	UpdateTestDefine(&oDataDevice, m_pDeviceAttrsDefine);
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevice_Attrs(CDvmDataset *pDeviceAttrs, CDvmData *pAtsRpcDevice)
{
	CDvmValue *pValue = NULL;
	POS pos = pAtsRpcDevice->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pAtsRpcDevice->GetNext(pos);
		InitByAtsRpcTestDef_AddDevice_Attr(pDeviceAttrs, pValue);
	}
// 	CDvmValue *pValue = (CDvmValue*)pAtsRpcDevice->FindByID(AtsRpcTestDef_bin_offset);
// 
// 	if (pValue != NULL)
// 	{
// 		InitByAtsRpcTestDef_AddDevices_Attrs(pDeviceAttrs, pValue);
// 	}
// 
// 	pValue = (CDvmValue*)pAtsRpcDevice->FindByID(AtsRpcTestDef_bout_offset);
// 
// 	if (pValue != NULL)
// 	{
// 		InitByAtsRpcTestDef_AddDevices_Attrs(pDeviceAttrs, pValue);
// 	}
// 
// 	pValue = (CDvmValue*)pAtsRpcDevice->FindByID(_T("udc-power"));
// 
// 	if (pValue != NULL)
// 	{
// 		InitByAtsRpcTestDef_AddDevices_Attrs(pDeviceAttrs, pValue);
// 	}
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevice_Attr(CDvmDataset *pDeviceAttrs, CDvmValue *pAtsRpcAttr)
{
	CDvmData *pAttr = NULL;
	pAttr = new CDvmData();
	pDeviceAttrs->AddNewChild(pAttr);
	pAttr->m_strName = pAtsRpcAttr->m_strName;
	pAttr->m_strID = pAtsRpcAttr->m_strID;
	pAttr->m_strValue = pAtsRpcAttr->m_strValue;
}

void CAtsNewTestTool::InitByAtsRpcTestDef_InitCmmConfig_MMS(CDeviceCmmConfig *pCmmConfig, CDvmData *pData)
{
	CString strIP = pData->GetValueByID(AtsRpcTestDef_ip);
	CCmmMmsConfig *pMmsCfg = NULL;

	if (pCmmConfig == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_MMS::pTask->GetDeviceCmmConfig() == NULL"));
		return;
	}

	pMmsCfg = pCmmConfig->GetConfigMms();

	if (pMmsCfg == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_MMS::pCmmConfig->GetConfigMms() == NULL"));
		return;
	}

	pMmsCfg->m_strRemoteIP = strIP;
}

void CAtsNewTestTool::InitByAtsRpcTestDef_InitCmmConfig_MMS(CDeviceCmmConfig *pCmmConfig, CDataGroup *pDataGroup)
{
	CString strIP;

	if (!pDataGroup->GetDataValue(XPARA_ID_Remote_ip, strIP))
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitCmmConfig_MMS has no data [remote-ip]"));
		return;
	}

	//shaolei 20210810
	CTCtrlCntrConfig::SetIP_Device(strIP);

	CCmmMmsConfig *pMmsCfg = NULL;

	if (pCmmConfig == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_MMS::pTask->GetDeviceCmmConfig() == NULL"));
		return;
	}

	pMmsCfg = pCmmConfig->GetConfigMms();

	if (pMmsCfg == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_MMS::pCmmConfig->GetConfigMms() == NULL"));
		return;
	}

	pMmsCfg->m_strRemoteIP = strIP;
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevices_MMS(CAtsTestDefineInterface *pAtsTestDefine)
{
	CString strDvmFile, strIP;
	CExBaseObject *pData = NULL;
	long nCount = pAtsTestDefine->m_pDevices->GetCount();
	POS pos = pAtsTestDefine->m_pDevices->GetHeadPosition();
	CExBaseList listTask;
	CTestTask *pTask = NULL;
	long nTaskIndex = 0;
	CDeviceCmmConfig *pCmmConfig = NULL;
	CCmmMmsConfig *pMmsCfg = NULL;

	strDvmFile = m_strDeviceFile;//pData->GetValueByID(XPARA_ID_DVMFILE);
	MdvMgrpTest_InsertMmsDevices(strDvmFile, nCount);   //�˺�������װ������������������
	m_pTestTasks->SelectAllTestTask(listTask);
	InitAtsRpcTestTaskName(pAtsTestDefine, listTask);   //ShaoL  2019.04.15

	if (nCount > 1)
	{
		//��װ��ʱ����ͬ��װ�õ�ģ���ļ�����Լģ���ļ����ܲ�һ�����ٸ�����������������
		MdvMgrpTest_InitDvm_Ppxml(pAtsTestDefine);
	}

	//����IP
	while (pos != NULL)
	{
		pData =pAtsTestDefine->m_pDevices->GetNext(pos);
		pTask = (CTestTask *)listTask.GetAtIndex(nTaskIndex);
		pCmmConfig = pTask->GetDeviceCmmConfig();
		ASSERT (pCmmConfig != NULL);

		if (pData->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			InitByAtsRpcTestDef_InitCmmConfig_MMS(pCmmConfig, (CDvmData*)pData);
		}
		else if (pData->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			CDvmDataset *pDeviceAttrs = pTask->GetDeviceAttr();
			pDeviceAttrs->AppendCloneWithoutRepeat( (CDataGroup*)pData);
			InitByAtsRpcTestDef_InitCmmConfig_MMS(pCmmConfig, (CDataGroup*)pData);
		}
		
		nTaskIndex++;
	}

	listTask.RemoveAll();
}

void CAtsNewTestTool::MdvMgrpTest_InitDvm_Ppxml(CAtsTestDefineInterface *pAtsTestDefine)
{
	if (m_pTestTasks == NULL || pAtsTestDefine == NULL)
	{
		return;
	}

	CExBaseList listTask;
	CTestTask *pTask = NULL;
	long nTaskIndex = 0;
	m_pTestTasks->SelectAllTestTask(listTask);
	POS pos = listTask.GetHeadPosition();

	while (pos != NULL)
	{
		CString strDvmFile, strPpXmlFile;
		pAtsTestDefine->GetDvmFile(strDvmFile, nTaskIndex);
		pAtsTestDefine->GetPpxmlFile(strPpXmlFile, nTaskIndex);
		pTask = (CTestTask *)listTask.GetNext(pos);

		if (strDvmFile.GetLength() > 0)
		{
			pTask->SetDvmFile(strDvmFile);
		}
		
		if (strPpXmlFile.GetLength() > 0)
		{
			pTask->SetPpTemplateFile(strPpXmlFile);
		}

		nTaskIndex++;
	}

	listTask.RemoveAll();
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevices_PP(CAtsTestDefineInterface *pAtsTestDefine)
{
	CString strDvmFile, strIP, strPpTemplate;
	CDvmData *pData = NULL;
	POS pos = pAtsTestDefine->m_pDevices->GetHeadPosition();
	CExBaseList listTask;
	long nCount = 0;

	pData = (CDvmData *)pAtsTestDefine->m_pDevices->GetAt(pos);
	nCount = pAtsTestDefine->m_pDevices->GetCount();
	strDvmFile = m_strDeviceFile;//pData->GetValueByID(XPARA_ID_DVMFILE);
	strPpTemplate = pData->GetValueByID(XPARA_ID_PPXMLFILE);
	strIP = pData->GetValueByID(AtsRpcTestDef_ip);

	if (strPpTemplate.GetLength() == 0)
	{
		strPpTemplate = m_strPpTemplateFile;
	}

	if (strDvmFile.GetLength() == 0)
	{
		strDvmFile = m_strDeviceFile;
	}

	MdvMgrpTest_InsertPpDevices(strPpTemplate, strDvmFile, nCount);
	m_pTestTasks->SelectAllTestTask(listTask);

	if (strIP.GetLength() > 0)
	{
		InitByAtsRpcTestDef_AddDevices_PP_Net(pAtsTestDefine, listTask);
	}
	else
	{
		InitByAtsRpcTestDef_AddDevices_PP_Serial(pAtsTestDefine, listTask);
	}

	listTask.RemoveAll();
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevices_PP_Net(CAtsTestDefineInterface *pAtsTestDefine, CExBaseList &listTask)
{
	CString strDvmFile, strIP;
	CDvmData *pData = NULL;
	POS pos = pAtsTestDefine->m_pDevices->GetHeadPosition();
	CTestTask *pTask = NULL;
	long nTaskIndex = 0;
	CDeviceCmmConfig *pCmmConfig = NULL;
	CCmmNetConfig *pNetCfg = NULL;
	long nPort = 0;

	pData = (CDvmData *)pAtsTestDefine->m_pDevices->GetAt(pos);
	strDvmFile = m_strDeviceFile;//pData->GetValueByID(XPARA_ID_DVMFILE);

	while (pos != NULL)
	{
		pData = (CDvmData *)pAtsTestDefine->m_pDevices->GetNext(pos);

		//2021-8-4  lijunqing ����MES��IOTЭ�飬���ݶ���ΪCDataGroup���ȶ��ԣ������޸�
		//ASSERT (pData->GetClassID() == DVMCLASSID_CDVMDATA);

		if (pData->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pDevice = (CDataGroup *)pData;
			pDevice->GetDataValue(XPARA_ID_Remote_ip, strIP);
			pDevice->GetDataValue(XPARA_ID_Remote_port, nPort);
		}
		else
		{
			strIP = pData->GetValueByID(AtsRpcTestDef_ip);
			nPort = CString_To_long( pData->GetValueByID(AtsRpcTestDef_port) );
		}

		pTask = (CTestTask *)listTask.GetAtIndex(nTaskIndex);
		pCmmConfig = pTask->GetDeviceCmmConfig();
		ASSERT (pCmmConfig != NULL);

		if (pCmmConfig == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_PP_Net::pTask->GetDeviceCmmConfig() == NULL"));
			continue;
		}

		pNetCfg = pCmmConfig->GetNetConfig();

		if (pNetCfg == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_PP_Net::pCmmConfig->GetNetConfig() == NULL"));
			continue;
		}

		pNetCfg->SetRemoteIP(strIP, nPort);
		nTaskIndex++;
	}
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevices_PP_Serial(CAtsTestDefineInterface *pAtsTestDefine, CExBaseList &listTask)
{
	CString strDvmFile, strIP;
	CDvmData *pData = NULL;
	POS pos = pAtsTestDefine->m_pDevices->GetHeadPosition();
	CTestTask *pTask = NULL;
	long nTaskIndex = 0;
	CDeviceCmmConfig *pCmmConfig = NULL;
	CCmmSerialConfig *pSerialCfg = NULL;
	long nPort = 0;

	pData = (CDvmData *)pAtsTestDefine->m_pDevices->GetAt(pos);
	strDvmFile = m_strDeviceFile;//pData->GetValueByID(XPARA_ID_DVMFILE);

	while (pos != NULL)
	{
		pData = (CDvmData *)pAtsTestDefine->m_pDevices->GetNext(pos);

		//2021-8-4  lijunqing ����MES��IOTЭ�飬���ݶ���ΪCDataGroup���ȶ��ԣ������޸�
		ASSERT (pData->GetClassID() == DVMCLASSID_CDVMDATA);

		pTask = (CTestTask *)listTask.GetAtIndex(nTaskIndex);
		pCmmConfig = pTask->GetDeviceCmmConfig();
		ASSERT (pCmmConfig != NULL);

		if (pCmmConfig == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_MMS::pTask->GetDeviceCmmConfig() == NULL"));
			continue;
		}

		pSerialCfg = pCmmConfig->GetConfigSerial();

		if (pSerialCfg == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_MMS::pCmmConfig->GetConfigSerial() == NULL"));
			continue;
		}

		pSerialCfg->m_nPortNum = CString_To_long( pData->GetValueByID(AtsRpcTestDef_port) );
		pSerialCfg->m_nDataBit = CString_To_long( pData->GetValueByID(AtsRpcTestDef_byte_size) );
		pSerialCfg->m_fStopBit = CString_To_long( pData->GetValueByID(AtsRpcTestDef_stop_bit) );
		pSerialCfg->m_nParity = CString_To_long( pData->GetValueByID(AtsRpcTestDef_parity) );
		pSerialCfg->m_nBaudRate = CString_To_long( pData->GetValueByID(AtsRpcTestDef_baud_rate) );

		nTaskIndex++;
	}
}

void CAtsNewTestTool::InitAtsRpcTestTaskName(CAtsTestDefineInterface *pAtsTestDefine, CExBaseList &listTask)
{
	CString strDvmFile, strIP;
	CExBaseObject *pData = NULL;
	POS pos = pAtsTestDefine->m_pDevices->GetHeadPosition();
	CTestTask *pTask = NULL;
	long nTaskIndex = 0;

	while (pos != NULL)
	{
		pData = pAtsTestDefine->m_pDevices->GetNext(pos);
		pTask = (CTestTask *)listTask.GetAtIndex(nTaskIndex);
		CString strDeviceSN;
		pAtsTestDefine->GetDeviceSN(strDeviceSN, nTaskIndex);

		//����ʹ��DeviceSN����Task������shaolei 2023-11-3
		if (strDeviceSN.GetLength() > 0)
		{
			pTask->m_strName = strDeviceSN;
			pTask->m_strID = strDeviceSN;
			pTask->m_strLocalID = strDeviceSN;
		}
		else
		{
			if (pData->m_strName.GetLength() > 0)
			{
				pTask->m_strName = pData->m_strName;
			}

			if (pData->m_strID.GetLength() > 0)
			{
				pTask->m_strID = pData->m_strID;
				pTask->m_strLocalID = pData->m_strID;
			}
		}

		m_pTestTasks->InitProjectByCommCmdManyConfig(pTask);    //ShaoL 2019.04.15 ����pTask��name��id���ö�װ�ö���
		nTaskIndex++;
	}
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevices_Iot(CAtsTestDefineInterface *pAtsTestDefine)
{
	CString strDvmFile, strPpTemplate;
	CDvmData *pData = NULL;
	POS pos = pAtsTestDefine->m_pDevices->GetHeadPosition();
	CExBaseList listTask;
	long nCount = 0;

	pData = (CDvmData *)pAtsTestDefine->m_pDevices->GetAt(pos);
	nCount = pAtsTestDefine->m_pDevices->GetCount();
	strDvmFile = m_strDeviceFile;//pData->GetValueByID(XPARA_ID_DVMFILE);
	strPpTemplate = pData->GetValueByID(XPARA_ID_PPXMLFILE);

	if (strPpTemplate.GetLength() == 0)
	{
		strPpTemplate = m_strPpTemplateFile;
	}

	if (strDvmFile.GetLength() == 0)
	{
		strDvmFile = m_strDeviceFile;
	}

	MdvMgrpTest_InsertIotDevices(strPpTemplate, strDvmFile, nCount);
	m_pTestTasks->SelectAllTestTask(listTask);
	InitByAtsRpcTestDef_AddDevices_Iot(pAtsTestDefine, listTask);
	listTask.RemoveAll();
}

/***************************************
<group id="devices">
	<group id="device">
		<data id="DeviceSN" name="" value="A92E082D1F02"/>
		<data id="EngineProgID" name="" value="IotEngine.PoEngine"/>
		<data id="ppxml-file" name="�����ļ�" value="WSD.iotxml"/>
		<data id="ppxml-file_s" name="�����ļ�" value="/profile/upload/2021/07/31/4e42cc98113b4bfa8fe90ec5e13447ec.iotxml"/>
		<data id="dvm-file" name="" value="WSD.xml"/>
		<data id="dvm-file_s" name="" value="/profile/upload/2021/07/31/360770cc768a45fab98c0db2277a2780.xml"/>
		<data id="remote-ip" name="" value=""/>
		<data id="remote-port" name="" value="0"/>
	</group>
</group>
***************************************/
void CAtsNewTestTool::InitByAtsRpcTestDef_AddDevices_Iot(CAtsTestDefineInterface *pAtsTestDefine, CExBaseList &listTask)
{
	CString strDvmFile, strIP;
	CDataGroup *pDevice = NULL;
	POS pos = pAtsTestDefine->m_pDevices->GetHeadPosition();
	CTestTask *pTask = NULL;
	long nTaskIndex = 0;
	CDeviceCmmConfig *pCmmConfig = NULL;
	CCmmNetConfig *pNetCfg = NULL;
	long nPort = 0;

	pDevice = (CDataGroup *)pAtsTestDefine->m_pDevices->GetAt(pos);
	//pDevice->GetDataValue(XPARA_ID_DVMFILE, strDvmFile);
	strDvmFile = m_strDeviceFile;

	while (pos != NULL)
	{
		pDevice = (CDataGroup *)pAtsTestDefine->m_pDevices->GetNext(pos);
		ASSERT (pDevice->GetClassID() == DTMCLASSID_CDATAGROUP);

		pDevice->GetDataValue(XPARA_ID_Remote_ip, strIP);
		pDevice->GetDataValue(XPARA_ID_Remote_port, nPort);
		pTask = (CTestTask *)listTask.GetAtIndex(nTaskIndex);
		pCmmConfig = pTask->GetDeviceCmmConfig();
		ASSERT (pCmmConfig != NULL);

		if (pCmmConfig == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_Iot::pTask->GetDeviceCmmConfig() == NULL"));
			continue;
		}

		pNetCfg = pCmmConfig->GetNetConfig();

		if (pNetCfg == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T(" InitByAtsRpcTestDef_AddDevices_Iot::pCmmConfig->GetNetConfig() == NULL"));
			continue;
		}

		pNetCfg->SetRemoteIP(strIP, nPort);
		nTaskIndex++;
	}
}

/**********************************************
<group id="InspectionBases" name="��������">
	<group id="InspectionBasis">
		<data id="Name" name="��������" value="����1"/>
		<data id="Properties" name="��������" value="����"/>
	</group>
	<group id="InspectionBasis">
		<data id="Name" name="��������" value="����2"/>
		<data id="Properties" name="��������" value="���"/>
	</group>
	<group id="InspectionBasis">
		<data id="Name" name="��������" value="����3"/>
		<data id="Properties" name="����" value="�б�"/>
	</group>
</group>
************************************/
  //��Ӽ����׼����CDataGroupת����CDvmDataset
void CAtsNewTestTool::InitByAtsRpcTestDef_AddInspectionBases(CAtsTestDefineInterface *pAtsTestDefine)
{
	CDataGroup *pInspectionBases = (CDataGroup *)pAtsTestDefine->m_pInspectionBases;
	
	if (m_pInspectionBases == NULL)
	{
		m_pInspectionBases = new CDvmDataset();
	}

	m_pInspectionBases->DeleteAll();

	POS pos = pInspectionBases->GetHeadPosition();

	while ( pos != NULL)
	{
		CDataGroup *pGroup = (CDataGroup *)pInspectionBases->GetNext(pos);
		CDvmData *pNewData = m_pInspectionBases->AddNewData(pGroup->m_strName, pGroup->m_strID, pGroup->m_strDataType, pGroup->m_strValue);

		POS pos2 = pGroup->GetHeadPosition();

		while (pos2 != NULL)
		{
			CDvmData *pData = (CDvmData *)pGroup->GetNext(pos2);
			pNewData->AddValue(pData->m_strName, pData->m_strID, pData->m_strValue);
		}
	}
}

/*********************************************
<group id="Testors" name="����Ա��Ϣ">
	<group id="MainInspection" name="����" type=�����족>
		<data id="Type" name="����" value="����"/>
		<data id="Name" name="����" value="*****"/>
		<data id="Number" name="����" value="*****"/>
	</group>
	<group id="Proofreader" name="У��" type=��У�ԡ�>
		<data id="Type" name="����" value="У��"/>
		<data id="Name" name="����" value="*****"/>
		<data id="Number" name="����" value="*****"/>
	</group>
	<group id="Checker" name="���" type=����ˡ�>
		<data id="Type" name="����" value="���"/>
		<data id="Name" name="����" value="*****"/>
		<data id="Number" name="����" value="*****"/>
	</group>
</group>
****************************************************/
//��Ӽ���Ա
void CAtsNewTestTool::InitByAtsRpcTestDef_AddTesters(CAtsTestDefineInterface *pAtsTestDefine)
{
	CDataGroup *pTesters = (CDataGroup *)pAtsTestDefine->m_pTesters;

	if (m_pTesters == NULL)
	{
		m_pTesters = new CDvmDataset();
	}

	m_pTesters->DeleteAll();

	POS pos = pTesters->GetHeadPosition();

	while ( pos != NULL)
	{
		CDataGroup *pGroup = (CDataGroup *)pTesters->GetNext(pos);
		CDvmData *pNewData = m_pTesters->AddNewData(pGroup->m_strName, pGroup->m_strID, pGroup->m_strDataType, pGroup->m_strValue);

		POS pos2 = pGroup->GetHeadPosition();

		while (pos2 != NULL)
		{
			CDvmData *pData = (CDvmData *)pGroup->GetNext(pos2);
			pNewData->AddValue(pData->m_strName, pData->m_strID, pData->m_strValue);
		}
	}
}

/*********************************************
<group id="GlobalDatas" name="ȫ������" type="">
	<data id="TestType" name="��������" value="��ʽ����"/>
</group>
****************************************************/
//�������ȫ�����ݣ����磺��������
void CAtsNewTestTool::InitByAtsRpcTestDef_AddGlobalDatas(CAtsTestDefineInterface *pAtsTestDefine)
{
	CDataGroup *pGlobalDatas = (CDataGroup *)pAtsTestDefine->m_pGlobalDatas;

	if (m_pGlobalDatas == NULL)
	{
		m_pGlobalDatas = new CDvmDataset();
	}

	m_pGlobalDatas->DeleteAll();

	InitByAtsRpcTestDef_AddGlobalDatas(pGlobalDatas);
}

void CAtsNewTestTool::InitByAtsRpcTestDef_AddGlobalDatas(CDataGroup *pGroupDatas)
{
	POS pos = pGroupDatas->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while ( pos != NULL)
	{
		pObj = pGroupDatas->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;

			if (pData->m_strID == _T("TestType"))
			{
				SetTestType(pData->m_strValue);
			}

			m_pGlobalDatas->AddNewData(pData->m_strName, pData->m_strID, pData->m_strDataType, pData->m_strValue);
		}
		else if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			CDataGroup *pGroup = (CDataGroup *)pObj;
			InitByAtsRpcTestDef_AddGlobalDatas(pGroup);
		}
		//CDvmData *pData = (CDvmData *)pGlobalDatas->GetNext(pos);
		//CDvmData *pNewData = m_pGlobalDatas->AddNewData(pData->m_strName, pData->m_strID, pData->m_strDataType, pData->m_strValue);
	}
}

BOOL CAtsNewTestTool::HasLogic()
{
	CString strVisio = ChangeFilePostfix(m_strTemplateFile, g_strGbVisioFileFilter);

	if (IsFileExist(strVisio))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CAtsNewTestTool::InitGuideBookAttrs(CGuideBook *pGuideBook)
{
	if (g_theAtsNewTestTool == NULL)
	{
		return;
	}

	pGuideBook->m_strPpEngineProgID  = g_theAtsNewTestTool->m_strPpEngineProgID;
	pGuideBook->m_strPpTemplateFile   = g_theAtsNewTestTool->m_strPpTemplateFile;
	pGuideBook->m_strDvmFile            = g_theAtsNewTestTool->m_strDeviceFile;
}

//2021-10-1  lijunqing  �˺����������ø�Task��EngineProgID��������ڴ���Task��Project��ʱ������
void CAtsNewTestTool::InitTasksPpEngineProgID()
{
	if (g_theAtsNewTestTool == NULL)
	{
		return;
	}

	if (g_theAtsNewTestTool->m_pTestTasks == NULL)
	{
		return;
	}

	g_theAtsNewTestTool->m_pTestTasks->SetEngineProgID(g_theAtsNewTestTool->m_strPpEngineProgID);
}

//shaolei 2023-11-2  �˺����������ø�Task��EngineMode��
void CAtsNewTestTool::InitTasksEngineMode()
{
	if (g_theAtsNewTestTool == NULL)
	{
		return;
	}

	if (g_theAtsNewTestTool->m_pTestTasks == NULL)
	{
		return;
	}

	g_theAtsNewTestTool->m_pTestTasks->SetEngineMode(g_theAtsNewTestTool->m_strEngineMode);
}

//2023-3-26  lijunqing ͨ�Ų��֣�ʹ��ͨ�ŷ�����޸�
//ͨ�����ö���ʹ��CPpSttCommConfig����װ��ģʽ�£���Ա����m_oCommConfig
//��װ��ģʽ�£�Tool��ΪCExBaseList���Ӷ���ΪCPpSttCommConfig����
void CAtsNewTestTool::SetCommConfig(CPpSttCommConfig *pCommConfig)
{
	if (m_pCommConfig != NULL)
	{
		m_pCommConfig = new CPpSttCommConfig();
	}

	m_pCommConfig->DeleteAll();
	m_pCommConfig->AppendCloneEx(*pCommConfig);
}

CString File_SmartTestCommConfig_mms();

void CAtsNewTestTool::InitCommConfigEngineByProgID()
{
	if (m_pCommConfig == NULL)
	{
		m_pCommConfig = new CPpSttCommConfig();
	}

	CString strFile;

	if (m_strPpEngineProgID == g_strPpEngineProgID)
	{
		strFile = File_SmartTestCommConfig_pp();
	}
	else if (m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		strFile = File_SmartTestCommConfig_mms();
	}
	else if (m_strPpEngineProgID == g_strPpEngineProgIDDlt)
	{
		strFile = File_SmartTestCommConfig_cms();
	}

	if (strFile.GetLength() > 0)
	{
		m_pCommConfig->DeleteAll();
		m_pCommConfig->OpenCommConfigFile(strFile);
	}
}

//2023-6-17 lijunqing ��ʼ��APP������󣬴������ļ���ȡ
void CAtsNewTestTool::InitTestApps()
{
	if (m_pTestApps == NULL)
	{
		m_pTestApps = new CDataGroup();
	}

	CString strFile = _P_GetConfigPath();
	strFile.AppendFormat(_T("%s/TestAppConfig.xml"), m_strMacroFileID.GetString());
	
	dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	m_pTestApps->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
}

