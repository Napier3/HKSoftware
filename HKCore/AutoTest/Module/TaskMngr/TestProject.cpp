#include "stdafx.h"

#include "TestProject.h"
// #include "../../../Module/Interface/XML2Interface.h"
#include "../../../Module/api/GlobalConfigApi.h"
#include "../AutoTestXMLRWKeys.h"
#include "../XLanguageResourceAts.h"
#include "TestTask.h"

#ifndef _TSK_MNGR_NOT_USE_GUIDEBOOK
#include "..\TestControl/TestControl.h"
#endif

#include "../../../System/Module/XAtsSysSvrGlobalDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CErrTestItemRef::CErrTestItemRef()
{
	
}

CErrTestItemRef::~CErrTestItemRef()
{

}

UINT CErrTestItemRef::GetClassID()	
{		
	return CLASSID_ERRTESTITEMREF;	
}


BSTR CErrTestItemRef::GetXmlElementKey()
{
	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestItemErrRefKey;
}

CExBaseObject* CErrTestItemRef::Clone()
{
	CErrTestItemRef *pNew = new CErrTestItemRef;
	Copy(pNew);

	return pNew;
}

CTestProject::CTestProject()
{
	m_nCurrTestItemIndex = 0;
	m_strTestState = g_strNormal;

	::GetLocalTime(&m_tmPlanBegin);
	::GetLocalTime(&m_tmPlanFinish);
	::GetLocalTime(&m_tmTestBegin);
	::GetLocalTime(&m_tmTestFinish);

	m_bNewProject = FALSE;
	m_pRefFrameWnd = NULL;
	m_nSelect = 1;
	m_nTestParaEditMode = MTTTASK_PROJECT_USETASKSPARA;
	m_nProjectID = 0;
	m_nProjectIndex = -1;
	m_pTestControlRef = NULL;
}

CTestProject::~CTestProject()
{
}


void CTestProject::SetTestState_Stop()		{	SetTestState(g_strTestStop);		}
void CTestProject::SetTestState_Testting()	{	SetTestState(g_strTesting);			}

void CTestProject::SetTestState_Finish()
{
	SetTestState(g_strTestFinished);	
	UpdateTestRsltJdg();
}

void CTestProject::SetTestState_Normal()		{	SetTestState(g_strNormal);	}
void CTestProject::SetTestState_Archiving()		{	SetTestState(g_strTestArchiving);	}

BOOL CTestProject::IsTestState_Normal()		{	return m_strTestState == g_strNormal;		}
BOOL CTestProject::IsTestState_Stop()			{	return m_strTestState == g_strTestStop;		}
BOOL CTestProject::IsTestState_Testting()		{	return m_strTestState == g_strTesting;		}
BOOL CTestProject::IsTestState_Finish()		{	return m_strTestState == g_strTestFinished;	}
BOOL CTestProject::IsTestState_Archiving()		{	return m_strTestState == g_strTestArchiving;	}

CString CTestProject::GetTestStateDesc()
{
	if (m_strTestState == g_strTestArchiving)
	{
		return g_sLangTxt_TaskArchive/*_T("测试完成")*/;
	}

	if (m_strTestState == g_strTestFinished)
	{
		return g_sLangTxt_TestComplete/*_T("测试完成")*/;
	}

	if (m_strTestState == g_strTestStop)
	{
		return g_sLangTxt_TerminationTest/*_T("终止测试")*/;
	}

	if (m_strTestState == g_strTesting)
	{
		return g_sLangTxt_Testing/*_T("测试中")*/;
	}

	if (m_strTestState == g_strNormal)
	{
		return g_sLangTxt_UnTest/*_T("未测试")*/;
	}

	return g_sLangTxt_UnTest/*_T("未测试")*/;
}

void CTestProject::UpdateTestRsltJdg() //2021-1-1  lijunqing
{
	if (m_strTestRsltJdg.GetLength() == 0)
	{
		m_strTestRsltJdg = _T("测试合格");
	}
}

BOOL CTestProject::Init()
{	
	return FALSE;
}

long CTestProject::InitAfterSerialize()
{
	return 0;
}

UINT CTestProject::GetClassID()
{
	return CLASSID_TESTPROJECT;
}

long  CTestProject::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CTestProject::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAutoTestXMLRWKeys *pXmlKeys = CAutoTestXMLRWKeys::g_pAutoTestRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKeyEx,oNode,m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strLocalIDKey,oNode,m_strLocalID);
	xml_GetAttibuteValue(pXmlKeys->m_strTestTypeKey,oNode,m_strTestType);
	xml_GetAttibuteValue(pXmlKeys->m_strLocationKey,oNode,m_strLocation);
	xml_GetAttibuteValue(pXmlKeys->m_strPlanBeginKey,oNode, m_tmPlanBegin);
	xml_GetAttibuteValue(pXmlKeys->m_strPlanFinishKey,oNode, m_tmPlanFinish);
	xml_GetAttibuteValue(pXmlKeys->m_strTestBeginKey,oNode, m_tmTestBegin);
	xml_GetAttibuteValue(pXmlKeys->m_strTestFinishKey,oNode, m_tmTestFinish);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKeyEx,oNode,m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTestStateKey,oNode,m_strTestState);
	xml_GetAttibuteValue(pXmlKeys->m_strCurrTestItemIndex,oNode,m_nCurrTestItemIndex);

	xml_GetAttibuteValue(pXmlKeys->m_strTemplateFileKey,oNode,m_strTemplateFile);
	xml_GetAttibuteValue(pXmlKeys->m_strReportMapFileKey,oNode,m_strReportMapFile);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocolTemplateKey,oNode,m_strPpTemplateFile);
	xml_GetAttibuteValue(pXmlKeys->m_strPpDeviceFileKey,oNode,m_strPpDeviceFile);
	xml_GetAttibuteValue(pXmlKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);

	xml_GetAttibuteValue(pXmlKeys->m_strReportSNKey,oNode,m_strReportSN);
	xml_GetAttibuteValue(pXmlKeys->m_strSelectKey, oNode, m_nSelect);

	m_strID.Trim();

	xml_GetAttibuteValue(pXmlKeys->m_strTestParaEditModeKey, oNode, m_nTestParaEditMode);
	xml_GetAttibuteValue(pXmlKeys->m_strProjectIDKey, oNode, m_nProjectID);
	xml_GetAttibuteValue(pXmlKeys->m_strEngineModeKey, oNode, m_strEngineMode);  //2023-11-3
	return 0;
}

long CTestProject::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAutoTestXMLRWKeys *pXmlKeys = CAutoTestXMLRWKeys::g_pAutoTestRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKeyEx,oElement,m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strLocalIDKey,oElement,m_strLocalID);
	xml_SetAttributeValue(pXmlKeys->m_strTestTypeKey,oElement,m_strTestType);
	xml_SetAttributeValue(pXmlKeys->m_strLocationKey,oElement,m_strLocation);
	xml_SetAttributeValue(pXmlKeys->m_strPlanBeginKey,oElement, m_tmPlanBegin);
	xml_SetAttributeValue(pXmlKeys->m_strPlanFinishKey,oElement, m_tmPlanFinish);
	xml_SetAttributeValue(pXmlKeys->m_strTestBeginKey,oElement, m_tmTestBegin);
	xml_SetAttributeValue(pXmlKeys->m_strTestFinishKey,oElement, m_tmTestFinish);
	xml_SetAttributeValue(pXmlKeys->m_strNameKeyEx,oElement,m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strTestStateKey,oElement,m_strTestState);
	xml_SetAttributeValue(pXmlKeys->m_strCurrTestItemIndex,oElement,m_nCurrTestItemIndex);

	xml_SetAttributeValue(pXmlKeys->m_strTemplateFileKey,oElement,m_strTemplateFile);
	xml_SetAttributeValue(pXmlKeys->m_strReportMapFileKey,oElement,m_strReportMapFile);
	xml_SetAttributeValue(pXmlKeys->m_strProtocolTemplateKey,oElement,m_strPpTemplateFile);
	xml_SetAttributeValue(pXmlKeys->m_strPpDeviceFileKey,oElement,m_strPpDeviceFile);
	xml_SetAttributeValue(pXmlKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);
	xml_SetAttributeValue(pXmlKeys->m_strReportSNKey,oElement,m_strReportSN);
	xml_SetAttributeValue(pXmlKeys->m_strSelectKey,oElement,m_nSelect);
	xml_SetAttributeValue(pXmlKeys->m_strTestParaEditModeKey,oElement,m_nTestParaEditMode);
	xml_SetAttributeValue(pXmlKeys->m_strProjectIDKey,oElement,m_nProjectID);
	xml_SetAttributeValue(pXmlKeys->m_strEngineModeKey,oElement,m_strEngineMode);  //shaolei 2023-11-3

	return 0;
}

BSTR CTestProject::GetXmlElementKey()
{
	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strProjectKey;
}

long CTestProject::IsEqual(CExBaseObject* pObj)
{
	CTestProject *pTestProject = (CTestProject*)pObj;
	
	if(pObj == NULL)
		return 0;

	//时间没有作比较
	if(pTestProject->m_strID == m_strID && pTestProject->m_strName == m_strName && pTestProject->m_strLocalID == m_strLocalID
		&&pTestProject->m_strLocation == m_strLocation && pTestProject->m_strTestType == m_strTestType 
		&&pTestProject->m_strPpTemplateFile == m_strPpTemplateFile)
	{
		return 1;
	}

	return 0;
}

long CTestProject::Copy(CExBaseObject* pDesObj)
{
	if(pDesObj != NULL)
	{
		CTestProject* pTemp = (CTestProject*)pDesObj;
		pTemp->m_strID = m_strID;
		pTemp->m_strName = m_strName;
		pTemp->m_strLocalID = m_strLocalID;
		pTemp->m_tmPlanBegin = m_tmPlanBegin;
		pTemp->m_tmPlanFinish = m_tmPlanFinish;
		pTemp->m_tmTestBegin = m_tmTestBegin;
		pTemp->m_tmTestFinish = m_tmTestFinish;
		pTemp->m_strLocation = m_strLocation;
		pTemp->m_strTestType = m_strTestType;
		pTemp->m_strPpTemplateFile = m_strPpTemplateFile;
		pTemp->m_strPpDeviceFile = m_strPpDeviceFile;
		pTemp->m_strTemplateFile = m_strTemplateFile;
		pTemp->m_strReportMapFile = m_strReportMapFile;
		pTemp->m_strPpEngineProgID = m_strPpEngineProgID;
		pTemp->m_strReportSN = m_strReportSN;
		pTemp->m_nSelect = m_nSelect;
		pTemp->m_nTestParaEditMode = m_nTestParaEditMode;
		pTemp->m_nProjectID = m_nProjectID;
		pTemp->m_strEngineMode = m_strEngineMode;

		return 1;
	}

	return 0;
}

CExBaseObject* CTestProject::Clone()
{
	CTestProject *pNew = new CTestProject;
	Copy(pNew);

	return pNew;
}


CExBaseObject* CTestProject::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestItemErrRefKey)
	{
		CErrTestItemRef* p = new CErrTestItemRef;
		return p;
	}

	return NULL;
}

CExBaseObject* CTestProject::AddErrTestItem(CExBaseObject *pItem)
{
	CString strNamePath = pItem->GetNamePathEx(GBCLASSID_DEVICE, TRUE);
	CString strIDPath = pItem->GetIDPathEx(GBCLASSID_DEVICE, TRUE);

	CExBaseObject *pFind = (CExBaseObject *)FindByID(strIDPath);
	CExBaseObject *pNew = NULL;

	if (pFind == NULL)
	{
		pNew = new CErrTestItemRef();
		pNew->m_strName = strNamePath;
		pNew->m_strID = strIDPath;
		AddNewChild(pNew);

		if (m_strTestRsltJdg.GetLength() == 0)
		{
			m_strTestRsltJdg.AppendFormat(_T("[%s]"), strNamePath);
		}
	}

	return pNew;
}


DWORD CTestProject::RemoveErrTestItem(CExBaseObject *pItem)
{
	CString strIDPath = pItem->GetIDPathEx(GBCLASSID_DEVICE, TRUE);

	CExBaseObject *pFind = (CExBaseObject *)FindByID(strIDPath);
	DWORD dwItemData = 0;

	if (pFind != NULL)
	{
		dwItemData = pFind->m_dwItemData;
		Delete(pFind);
	}

	return dwItemData;
}

void CTestProject::InitLocation(const CString &strTaskPath)
{
	if (IsFileExist(m_strLocation))
	{
		return;
	}

	m_strLocation = strTaskPath + GetPathFileNameFromFilePathName(m_strLocation);
}

void CTestProject::InitLocationEx(const CString &strTaskPath)
{
	if (IsFileExist(m_strLocation))
	{
		return;
	}

	//shaolei 20220328  增加时间戳
	CString strTmBegin;
	CTestTask *pTask = (CTestTask *)GetParent();
	strTmBegin.Format(_T("%04d%02d%02d%02d%02d%02d"), pTask->m_tmPlanBegin.wYear, pTask->m_tmPlanBegin.wMonth, pTask->m_tmPlanBegin.wDay
		, pTask->m_tmPlanBegin.wHour, pTask->m_tmPlanBegin.wMinute, pTask->m_tmPlanBegin.wSecond);

	m_strLocation.Format(_T("%s%s(_%s).%s"), strTaskPath, m_strID, strTmBegin, g_strGuideBookBinaryPostfix);
}

void CTestProject::SetReportSN(const CString &strReportSN)
{
	m_strReportSN = strReportSN;
	m_strID = strReportSN;
	m_strName = strReportSN;
	m_strLocalID = strReportSN;
	m_strLocation = GetPathFromFilePathName(m_strLocation);
	m_strLocation.AppendFormat(_T("%s.%s"), strReportSN, g_strGuideBookBinaryPostfix);
}

CDvmDataset* CTestProject::GetDeviceAttr(BOOL bCreate)
{
	CTestTask *pTestTask = (CTestTask*)GetParent();
	return pTestTask->GetDeviceAttr(bCreate);
}

void CTestProject::ValidateSystemPath(const CString &strFrom, const CString &strTo)
{
	_P_ReplaceSystemPath(strFrom, strTo, m_strLocation);
	_P_ReplaceSystemPath(strFrom, strTo, m_strPpTemplateFile);
	_P_ReplaceSystemPath(strFrom, strTo, m_strPpDeviceFile);
	_P_ReplaceSystemPath(strFrom, strTo, m_strTemplateFile);
	_P_ReplaceSystemPath(strFrom, strTo, m_strReportMapFile);
}

void CTestProject::SetDeviceFile(const CString &strFile)
{
	m_strPpDeviceFile = strFile;
	CString strTitle = ParseFileName(m_strPpDeviceFile);
	long nPos = m_strID.ReverseFind('-');
	m_strID = strTitle + m_strID.Mid(nPos);
	m_strName = m_strID;
	m_strLocalID = m_strID;
	m_strLocation = GetPathFromFilePathName(m_strLocation);
	m_strLocation.AppendFormat(_T("%s.%s"), m_strID, g_strGuideBookBinaryPostfix);
}

void CTestProject::ValidateLocation()
{
	if (m_strLocation.GetLength() >= 10)
	{
		if (IsFileExist2(m_strLocation))
		{
			return;
		}
	}

	CTestTask *pTestTask = (CTestTask*)GetParent();
	CTestTasks *pTestTasks = (CTestTasks*)pTestTask->GetParent();
	CString strFolder;

	if (pTestTasks == NULL)
	{
		strFolder = GetPathFromFilePathName(pTestTask->GetTaskFile());
		m_strLocation.Format(_T("%s%s.%s"), strFolder, m_strID, g_strGuideBookBinaryPostfix);
	}
	else
	{
		strFolder = GetPathFromFilePathName(pTestTasks->m_strTasksFile);
		m_strLocation.Format(_T("%s%s\\%s.%s"), strFolder, pTestTask->m_strLocalID, m_strID, g_strGuideBookBinaryPostfix);
	}

	tsk_SetLocation(m_strLocation);
}

void CTestProject::SetGlobalDatas_DeviceAttr(CDvmDataset *pDeviceAttr)
{
	if (m_pTestControlRef == NULL)
	{
		return;
	}

#ifndef _TSK_MNGR_NOT_USE_GUIDEBOOK
	CTestControl *pTestControl = (CTestControl*)m_pTestControlRef;
	pTestControl->m_pGuideBook->SetGlobalDatas_DeviceAttr(pDeviceAttr);
#endif
}

void CTestProject::ChangeID(const CString &strID, BOOL bUseRptIndex)
{
	m_strID = strID;
	m_strLocalID = strID;
	CString strDestFile, strDocSrcFile;
	CString strFileName;

	if (bUseRptIndex > 0)
	{
		strFileName.Format(_T("%s_%d"), strID, m_nProjectIndex);
	}
	else
	{
		strFileName = strID;
	}

	CString strLocation = tsk_GetLocation(TRUE);
	strDestFile = ChangeFileName(strLocation, strFileName);
	strDocSrcFile = m_strLocation;
	strDocSrcFile = ChangeFilePostfix(strLocation, g_strDocFilePostfix);

	::rename(strLocation, strDestFile);
	m_strLocation = strDestFile;

	strDestFile = ChangeFilePostfix(strDestFile, g_strDocFilePostfix);
	::rename(strDocSrcFile, strDestFile);
}


CString CTestProject::tsk_GetGbxmlFile(BOOL bFullPath)
{
	return tskapi_GetGbxmlFile(m_strTemplateFile, bFullPath);
}

void CTestProject::tsk_SetGbxmlFile(const CString &strFile)
{
	tskapi_SetGbxmlFile(strFile, m_strTemplateFile);
}

CString CTestProject::tsk_GetPpxmlFile(BOOL bFullPath)
{
	return tskapi_GetPpxmlFile(m_strPpTemplateFile, bFullPath);
}

void CTestProject::tsk_SetPpxmlFile(const CString &strFile)
{
	return tskapi_SetPpxmlFile(strFile, m_strPpTemplateFile);
}

CString CTestProject::tsk_GetLocation(BOOL bFullPath)
{
	if (m_strLocation.GetLength() <= 5)
	{
		return m_strLocation;
	}

	if (!bFullPath)
	{
		if (m_strLocation.GetAt(1) == ':')
		{
			return GetPathFileNameFromFilePathName(m_strLocation);
		}
		else
		{
			return m_strLocation;
		}
	}

	if (IsFileExist(m_strLocation))
	{
		return m_strLocation;
	}

	CString strFile;

	if (m_strLocation.GetAt(1) != ':')
	{
		CTestTask *pTestTask = (CTestTask*)GetParent();
		strFile = pTestTask->GetTaskPath();
		strFile += m_strLocation;

		if (IsFileExist(strFile))
		{
			return strFile;
		}
		else
		{
			return strFile;
		}
	}

	return m_strLocation;
}

void CTestProject::tsk_SetLocation(const CString &strLocation)
{
	m_strLocation = strLocation;

	if (m_strLocation.GetAt(1) == ':')
	{
		m_strLocation = GetPathFileNameFromFilePathName(m_strLocation);;
	}
}

CString tskapi_GetGbxmlFile(const CString &strTemplateFile, BOOL bFullPath)
{
	if (!bFullPath)
	{
		if (strTemplateFile.GetAt(1) == ':')
		{
			return GetPathFileNameFromFilePathName(strTemplateFile);
		}
		else
		{
			return strTemplateFile;
		}
	}

	if (IsFileExist(strTemplateFile))
	{
		return strTemplateFile;
	}

	CString strFile;

	if (strTemplateFile.GetAt(1) != ':')
	{
		strFile = _P_GetTemplatePath();
		strFile += strTemplateFile;
	}
	else
	{
		strFile = strTemplateFile;
	}

	return strFile;
}

void tskapi_SetGbxmlFile(const CString &strFile, CString &strTemplateFile)
{
	if (strFile.GetLength() == 0)
	{
		return;
	}

	strTemplateFile = strFile;
	const char *pTemp = _P_GetTemplatePath();

	if (strTemplateFile.GetAt(1) == ':')
	{
		if (IsFileExist(strTemplateFile))
		{
			strTemplateFile = strTemplateFile.Mid(strlen(pTemp));
		}
	}
}

CString tskapi_GetPpxmlFile(const CString &strPpTemplateFile, BOOL bFullPath)
{
	if (strPpTemplateFile.GetLength() == 0)
	{
		return strPpTemplateFile;
	}

	if (!bFullPath)
	{
		if (strPpTemplateFile.GetAt(1) == ':')
		{
			return GetPathFileNameFromFilePathName(strPpTemplateFile);
		}
		else
		{
			return strPpTemplateFile;
		}
	}

	if (IsFileExist(strPpTemplateFile))
	{
		return strPpTemplateFile;
	}

	CString strFile;

	if (strPpTemplateFile.GetAt(1) != ':')
	{
		strFile = atssys_GetProtocolTemplatePath();
		strFile += strPpTemplateFile;
	}
	else
	{
		strFile = strPpTemplateFile;
	}

	return strFile;
}

void tskapi_SetPpxmlFile(const CString &strFile, CString &strPpTemplateFile)
{
	if (strFile.GetLength() == 0)
	{
		strPpTemplateFile.Empty();
		return;
	}

	strPpTemplateFile = strFile;
	CString strPath = atssys_GetProtocolTemplatePath();

	if (strPpTemplateFile.GetAt(1) == ':')
	{
		if (IsFileExist(strPpTemplateFile))
		{
			strPpTemplateFile = strPpTemplateFile.Mid(strPath.GetLength());
		}
	}
}

CString tskapi_GetDvmFile(const CString &strDvmFile, BOOL bFullPath)
{
	if (!bFullPath)
	{
		if (strDvmFile.GetAt(1) == ':')
		{
			return GetPathFileNameFromFilePathName(strDvmFile);
		}
		else
		{
			return strDvmFile;
		}
	}

	if (IsFileExist(strDvmFile))
	{
		return strDvmFile;
	}

	CString strFile;

	if (strDvmFile.GetAt(1) != ':')
	{
		strFile = atssys_GetProtocolDvmPath();
		strFile += strDvmFile;

		if (IsFileExist(strFile))
		{
			return strFile;
		}
		else
		{
			strFile = _P_GetLibraryPath();
			strFile += strDvmFile;
			return strFile;
		}
	}
	else
	{
		strFile = strDvmFile;
	}

	return strFile;
}
