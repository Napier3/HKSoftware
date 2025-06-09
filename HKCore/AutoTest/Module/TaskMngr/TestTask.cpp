#include "StdAfx.h"
#include "TestTask.h"
#include "TestProject.h"
#include "ReportSNGen.h"
#include "../../../Module/api/GlobalConfigApi.h"
#include "../XLanguageResourceAts.h"

#ifndef _PSX_QT_LINUX_	 //yyj
#include "../GuideBook/ReportMap/WordRptApi.h"
#endif
#include "../../../Protocol/Module/ProcotolProject/PpCfgDevices.h"


#include "../XLanguageResourceAts_AutoTest.h"
#include "../../../Module/DataMngr/DataMngrTrans.h"
#include "TestWzdDefine.h"
#include "TestGlobalDefine.h"
#include "../TCtrlCntrConfig.h"

#ifndef GUIDEBOOK_DEV_MODE
#include "../../../61850/Module/MMS_STACK_CFG/MMS_STACK_CFG.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestTask::CTestTask(void)
{
	m_strTestState = g_strNormal;
	
	::GetLocalTime(&m_tmPlanBegin);
	::GetLocalTime(&m_tmPlanFinish);
	::GetLocalTime(&m_tmTestBegin);
	::GetLocalTime(&m_tmTestFinish);
	m_strLocalID.Format(_T("%04d%02d%02d%02d%02d%02d"), m_tmPlanBegin.wYear
		, m_tmPlanBegin.wMonth, m_tmPlanBegin.wDay, m_tmPlanBegin.wHour, m_tmPlanBegin.wMinute
		, m_tmPlanBegin.wSecond);
	m_strName = g_sLangTxt_TestTask/*"测试任务"*/;
	m_nTestTimeLong = 0;

	m_pCurrTestProject = NULL;
	m_pSysParas = NULL;
	m_bCanTestSysParaEditItem = TRUE;
	m_bDatasetChanged = FALSE;

	m_strTestType = _T("");

#ifndef _not_use_autotest_
	m_pThreadProgressBase = NULL;
	m_pStitchWordReportThread = NULL;
#endif

	m_pCommCmdManyConfig = NULL;   //多测试报告的配置
	m_pDeviceAttr = NULL;   //被测装置的属性

#ifndef GUIDEBOOK_DEV_MODE
	m_pDeviceCmmConfig = NULL;
#endif

	m_nSelect = 1;
}

CTestTask::~CTestTask(void)
{
// 	if (m_pSysParas != NULL)
// 	{
// 		delete m_pSysParas;
// 		m_pSysParas = NULL;
// 	}

// 	if (m_pThreadProgressBase != NULL)
// 	{
// 		delete m_pThreadProgressBase;
// 		m_pThreadProgressBase = NULL;
// 	}
	m_listCmmCfg.RemoveAll();
}

void CTestTask::SetAllSelect(long nSel)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			((CTestProject*)p)->m_nSelect = 1;
		}
	}
}

void CTestTask::Init()
{
}

void CTestTask::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	CString strPath;
	strPath = GetPathFromFilePathName(m_strTaskFile);

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATASET)
		{
			if (p->m_strID == _T("SysPara") || p->m_strName == g_sLangTxt_SystemPara/*_T("系统参数")*/)
			{
				m_pSysParas = (CDvmDataset *)p;
			}
			else if (p->m_strID == DSID_COMMCMDMCONFIG)
			{
				m_pCommCmdManyConfig = (CDvmDataset *)p;
			}
			else if (p->m_strID == DSID_DEVICEATTR)
			{
				m_pDeviceAttr = (CDvmDataset *)p;
			}
		}
		else if (nClassID == CLASSID_TESTPROJECT)
		{
			CTestProject *pTestProject = (CTestProject*)p;
			pTestProject->InitLocation(strPath);
		}
#ifndef GUIDEBOOK_DEV_MODE
		else if (nClassID == DMCLASSID_DEVICECMMCONFIG)
		{
			m_pDeviceCmmConfig = (CDeviceCmmConfig*)p;
		}
#endif

	}
}

long CTestTask::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CTestTask::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strIDKeyEx,oNode,m_strID);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strLocalIDKey,oNode,m_strLocalID);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestTypeKey,oNode,m_strTestType);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strLocationKey,oNode,m_strLocation);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPlanBeginKey,oNode, m_tmPlanBegin);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPlanFinishKey,oNode, m_tmPlanFinish);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestBeginKey,oNode, m_tmTestBegin);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestFinishKey,oNode, m_tmTestFinish);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strNameKeyEx,oNode,m_strName);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestStateKey,oNode,m_strTestState);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestTimeLongKey,oNode,m_nTestTimeLong);

	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpDeviceFileKey,oNode,m_strDeviceFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oNode,m_strPpTemplateFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTemplateFileKey,oNode,m_strTemplateFile);

	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strDvmTestStateKey,oNode,m_strDvmTestState);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strProtocolTestStateKey,oNode,m_strProtocolTestState);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strMaxMgrpIDKey,oNode,m_strMaxMgrpID);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strSelectKey,oNode,m_nSelect);

	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportSNKey,oNode,m_strReportSN);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strEngineModeKey,oNode,m_strEngineMode);  //shaolei 2023-11-3

	return 0;
}

long CTestTask::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strIDKeyEx,oElement,m_strID);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strLocalIDKey,oElement,m_strLocalID);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestTypeKey,oElement,m_strTestType);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strLocationKey,oElement,m_strLocation);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPlanBeginKey,oElement, m_tmPlanBegin);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPlanFinishKey,oElement, m_tmPlanFinish);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestBeginKey,oElement, m_tmTestBegin);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestFinishKey,oElement, m_tmTestFinish);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strNameKeyEx,oElement,m_strName);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestStateKey,oElement,m_strTestState);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestTimeLongKey,oElement,m_nTestTimeLong);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpDeviceFileKey,oElement,m_strDeviceFile);

	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oElement,m_strPpTemplateFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTemplateFileKey,oElement,m_strTemplateFile);

	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strDvmTestStateKey,oElement,m_strDvmTestState);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strProtocolTestStateKey,oElement,m_strProtocolTestState);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strMaxMgrpIDKey,oElement,m_strMaxMgrpID);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strSelectKey,oElement,m_nSelect);

	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportSNKey,oElement,m_strReportSN);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strEngineModeKey,oElement,m_strEngineMode);  //shaolei 2023-11-3

	return 0;
}

BSTR CTestTask::GetXmlElementKey()
{
	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskKey;
}

long CTestTask::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);

	if (m_pSysParas != NULL)
	{
		m_pSysParas->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}


long CTestTask::IsEqual(CExBaseObject* pObj)
{
	CTestTask *pTestTask = (CTestTask*)pObj;
	
	if(pObj == NULL)
		return 0;

	if(pTestTask->m_strID == m_strID && pTestTask->m_strName == m_strName &&pTestTask->m_strLocation == m_strLocation
		&& pTestTask->m_strTestType == m_strTestType && pTestTask->m_strTestState == m_strTestState)
	{
		long nCount1 = pTestTask->GetCount();
		long nCount2 = GetCount();
		if(nCount1 == nCount2)
		{
			for(long i=0;i<nCount1;i++)
			{
				CTestProject* pTestProject1 = (CTestProject*)pTestTask->GetAtIndex(i);
				CTestProject* pTestProject2 = (CTestProject*)GetAtIndex(i);
				if(!pTestProject1->IsEqual(pTestProject2))
					return 0;
			}
			return 1;
		}
	}

	return 0;
}

long CTestTask::Copy(CExBaseObject* pDesObj)
{	
	ASSERT( pDesObj != NULL);

	CTestTask* pTemp = (CTestTask*)pDesObj;
	pTemp->m_strID = m_strID;
	pTemp->m_strName = m_strName;
	pTemp->m_strLocalID = m_strLocalID;
	pTemp->m_tmPlanBegin = m_tmPlanBegin;
	pTemp->m_tmPlanFinish = m_tmPlanFinish;
	pTemp->m_tmTestBegin = m_tmTestBegin;
	pTemp->m_tmTestFinish = m_tmTestFinish;
	pTemp->m_strLocation = m_strLocation;
	pTemp->m_strTestType = m_strTestType;
	pTemp->m_strTestState = m_strTestState;
	pTemp->m_strDeviceFile= m_strDeviceFile;
	pTemp->m_strPpTemplateFile= m_strPpTemplateFile;
	pTemp->m_strPpEngineProgID= m_strPpEngineProgID;
	pTemp->m_strMaxMgrpID= m_strMaxMgrpID;
	pTemp->m_strEngineMode = m_strEngineMode;

	pTemp->m_strDvmTestState= m_strDvmTestState;
	pTemp->m_strProtocolTestState= m_strProtocolTestState;
	pTemp->m_nSelect= m_nSelect;

	pTemp->m_strReportSN = m_strReportSN;

	long nCount = GetCount();
	for(long i=0;i<nCount;i++)
	{
		CTestProject* pProject1 = (CTestProject*)GetAtIndex(i);
		CTestProject* pTestProject = (CTestProject*)pProject1->Clone();
		pTemp->AddTail(pTestProject);
		pTestProject->SetParent(pTemp);
	}

	return 0;
}

CExBaseObject* CTestTask::Clone()
{
	CTestTask *pNew = new CTestTask;
	Copy(pNew);

	return pNew;
}

CExBaseObject* CTestTask::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strProjectKey)
	{
		CTestProject* pTestProject = new CTestProject;
		return pTestProject;
	}

	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->CDvmDatasetKey())
	{
		CDvmDataset* pDvmDataset = new CDvmDataset;
		return pDvmDataset;
	}

	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->CDvmDeviceKey())
	{
		CDvmDevice* pDvmDevice = new CDvmDevice;
		return pDvmDevice;
	}

	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->CPpDeviceRefsKey())
	{
		CPpDeviceRefs* pPpDeviceRefs = new CPpDeviceRefs;
		return pPpDeviceRefs;
	}

	if(strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey)
	{
		CDeviceCmmConfig *pDeviceCmmConfig = new CDeviceCmmConfig();;
		return pDeviceCmmConfig;
	}

	return NULL;
}

CExBaseObject* CTestTask::CreateNewChild(long nClassID)
{
	return NULL;
}


void CTestTask::SetReportSN(const CString &strReportSN)
{
	m_strReportSN = strReportSN;
	//m_strID = strReportSN;
	//m_strName = m_strID;
	m_strLocalID = strReportSN;
	m_strLocation = GetPathFromFilePathName(m_strLocation);
}

BOOL CTestTask::OpenTaskFile()
{
	return OpenTaskFile(m_strLocation);
}

BOOL CTestTask::OpenTaskFile(const CString &strTaskFile)
{
	m_strTaskFile = strTaskFile;
	InitTaskType( GetPathFileNameFromFilePathName(strTaskFile) );
	DeleteAll();
	BOOL bRet = OpenXmlFile(m_strTaskFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return bRet;
}

BOOL CTestTask::SaveAs(const CString &strTaskFile)
{
	m_strTaskFile = strTaskFile;
	InitTaskType( GetPathFileNameFromFilePathName(strTaskFile) );
	return Save();
}

BOOL CTestTask::SaveAs2(const CString &strTaskPath)
{
	m_strTaskFile.Format(_T("%s%s.%s"), strTaskPath, m_strLocalID, g_strGuideBookBinaryPostfix_SdvSpoMgrp);
	return Save();
}

void CTestTask::InitTaskType(const CString &strFile)
{
	CString strPostfix;
	ParseFileNameAndPostfix(strFile, m_strTaskType, strPostfix);
}

BOOL CTestTask::Save(BOOL bPostMsg)
{
	try
	{
		BOOL b = SaveXmlFile(m_strTaskFile,CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

		return b;
	}
	catch (...)
	{
		return FALSE;
	}

	m_bDatasetChanged = FALSE;
}

void CTestTask::SetTaskType(const CString &strType)
{
	m_strTaskType = strType;
}

CString CTestTask::GetTaskType()
{
	return m_strTaskType;
}

void CTestTask::AddErrTestItem(CExBaseObject *pItem)
{
	ASSERT (m_pCurrTestProject != NULL);

	if (m_pCurrTestProject == NULL)
	{
		return;
	}

	m_pCurrTestProject->AddErrTestItem(pItem);
}

CTestProject* CTestTask::AddProject(const CString &strFile)
{
	CTestProject *pProject = (CTestProject*)FindByID(strFile);

	if (pProject != NULL)
	{
		return NULL;
	}

	pProject = new CTestProject();
	pProject->m_strName = GetPathFileNameFromFilePathName(strFile);
	pProject->m_strID = strFile;
	pProject->tsk_SetGbxmlFile(strFile);
	pProject->m_strPpDeviceFile   = m_strDeviceFile;
	pProject->tsk_SetPpxmlFile(m_strPpTemplateFile);
	pProject->m_strPpEngineProgID = m_strPpEngineProgID;

	AddNewChild(pProject);

	return pProject;
}

CTestProject* CTestTask::GetNextProject()
{
	POS pos = Find(m_pCurrTestProject);
	
	if (pos == NULL)
	{
		pos = GetHeadPosition();
	}
	else
	{
		if (m_pCurrTestProject->IsTestState_Finish())
		{
			GetNext(pos);
		}
	}

	if (pos == NULL)
	{
		pos = GetHeadPosition();
	}

	CTestProject *pFind = NULL;
	CTestProject *pCurr = NULL;

	while (pos != NULL)
	{
		pCurr = (CTestProject *)GetAt(pos);


		if (pCurr->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		if (!pCurr->IsTestState_Finish())
		{
			pFind = pCurr;
			break;
		}

		GetNext(pos);
	}

	SetCurrProject(pFind);

	return pFind;
}

void CTestTask::SetCurrProject(const CString &strGbFile)
{
	CTestProject *pFind = (CTestProject*)FindByID(strGbFile);

	if (pFind == NULL)
	{
		pFind = FindByGbrptFile(strGbFile);
	}

	SetCurrProject(pFind);
}

long CTestTask::FindProjectIndex(CTestProject *pProject)
{
	long nIndex = -1;
	CTestProject *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CTestProject *)GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		nIndex++;

		if (p == pProject)
		{
			break;
		}
	}

	return nIndex;
}

CTestProject* CTestTask::FindByGbrptFile(const CString &strGbrptFile)
{
	CTestProject *p = NULL;
	CTestProject *pFind = NULL;
	POS pos = GetHeadPosition();
	CString strLocation;

	while (pos != NULL)
	{
		p = (CTestProject *)GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		strLocation = p->tsk_GetLocation();
		strLocation.MakeLower();
		
		if (strLocation == strGbrptFile)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CTestProject* CTestTask::FindByGbrptFileName(const CString &strGbrptFileName)
{
	CTestProject *p = NULL;
	CTestProject *pFind = NULL;
	POS pos = GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		p = (CTestProject *)GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		strTemp = p->tsk_GetLocation(FALSE);//GetPathFileNameFromFilePathName(p->m_strLocation);
		strTemp.MakeLower();

		if (strTemp == strGbrptFileName)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CTestProject* CTestTask::GetTestProjectAtIndex(long nIndex)
{
	CTestProject *p = NULL;
	CTestProject *pFind = NULL;
	POS pos = GetHeadPosition();
	CString strTemp;
	long nTemp = 0;

	while (pos != NULL)
	{
		p = (CTestProject *)GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		if (nTemp == nIndex)
		{
			pFind = p;
			break;
		}

		nTemp++;
	}

	return pFind;
}

CString CTestTask::GetTaskPath()
{
	if (IsFileExist(m_strLocation))
	{
		return GetPathFromFilePathName(m_strLocation);
	}

	CTestTasks *pTestTasks = (CTestTasks*)GetParent();
	CString strFolder;


	if (pTestTasks == NULL)
	{
		m_strLocation = m_strTaskFile;//GetTaskFile();
	}
	else
	{
		CString strTmBegin;
		strTmBegin.Format(_T("%04d%02d%02d%02d%02d%02d"), m_tmPlanBegin.wYear, m_tmPlanBegin.wMonth, m_tmPlanBegin.wDay
			, m_tmPlanBegin.wHour, m_tmPlanBegin.wMinute, m_tmPlanBegin.wSecond);

		strFolder = GetPathFromFilePathName(pTestTasks->m_strTasksFile);
		m_strTaskFile.Format(_T("%s%s\\%s(_%s).%s"), strFolder, m_strLocalID, m_strLocalID, strTmBegin, g_strGuideBookBinaryPostfix_SdvSpoMgrp);
		m_strLocation = m_strTaskFile;
	}

	return GetPathFromFilePathName(m_strLocation);
}

CDvmDataset* CTestTask::GetTaskSysParas(BOOL bCreate)
{
	if (bCreate)
	{
		if (m_pSysParas == NULL)
		{
			m_pSysParas = new CDvmDataset();
		}
	}

	return m_pSysParas;
}

#ifndef GUIDEBOOK_DEV_MODE

CDeviceCmmConfig* CTestTask::GetDeviceCmmConfig()
{
	if (m_pDeviceCmmConfig == NULL)
	{
		m_pDeviceCmmConfig = new CDeviceCmmConfig();
		AddNewChild(m_pDeviceCmmConfig);
	}

	return m_pDeviceCmmConfig;	
}

void CTestTask::InitDeviceCmmConfig(CDeviceCmmConfig *pSrcCmmConfig)
{
	GetDeviceCmmConfig();
	m_pDeviceCmmConfig->InitBy(pSrcCmmConfig);
}

#endif

CDvmDataset* CTestTask::GetDeviceAttr(BOOL bCreate)
{
	if (m_pDeviceAttr == NULL)
	{
		if (bCreate)
		{
			m_pDeviceAttr = new CDvmDataset();
			m_pDeviceAttr->m_strID = DSID_DEVICEATTR;
			m_pDeviceAttr->m_strName = DSID_DEVICEATTR;
			AddNewChild(m_pDeviceAttr);
		}
	}

	return m_pDeviceAttr;
}

void CTestTask::InitDeviceAttr(CDvmDataset *pSrcDeviceAttrsDef)
{
	GetDeviceAttr();

	ASSERT (pSrcDeviceAttrsDef != NULL);
	if (pSrcDeviceAttrsDef != NULL)
	{
		m_pDeviceAttr->AppendCloneEx(*pSrcDeviceAttrsDef);
	}
}

void CTestTask::InitDeviceAttrValue(CDvmDataset *pSrcDeviceAttrsDef)
{
	ASSERT (m_pDeviceAttr != NULL);

	if (m_pDeviceAttr == NULL)
	{
		return;
	}

	m_pDeviceAttr->DeleteAll();

	ASSERT (pSrcDeviceAttrsDef != NULL);
	if (pSrcDeviceAttrsDef != NULL)
	{
		m_pDeviceAttr->AppendCloneEx(*pSrcDeviceAttrsDef);
	}
}

void CTestTask::InitDeviceAttrValueEx(CDvmDataset *pSrcDeviceAttrs)
{
	ASSERT (m_pDeviceAttr != NULL);

	if (m_pDeviceAttr == NULL)
	{
		return;
	}

	POS pos = m_pDeviceAttr->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmData *pDataFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pDeviceAttr->GetNext(pos);
		pDataFind = (CDvmData *)pSrcDeviceAttrs->FindByID(pData->m_strID);

		if (pDataFind != NULL)
		{
			pData->m_strValue = pDataFind->m_strValue;
			continue;
		}

		POS posValue = pData->GetHeadPosition();
		CDvmValue *pVal = NULL;

		while (posValue != NULL)
		{
			pVal = (CDvmValue *)pData->GetNext(posValue);
			pDataFind = (CDvmData *)pSrcDeviceAttrs->FindByID(pVal->m_strID);

			if (pDataFind != NULL)
			{
				pData->m_strValue = pDataFind->m_strValue;
				break;
			}
		}
	}
}

BOOL CTestTask::IsDeviceAttrSame(CDvmDataset *pDeviceAttr)
{
	POS pos = m_pDeviceAttr->GetHeadPosition();
	POS pos2 = pDeviceAttr->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmData *pData2 = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL && pos2 != NULL)
	{
		pData = (CDvmData *)m_pDeviceAttr->GetNext(pos);
		pData2 = (CDvmData *)pDeviceAttr->GetNext(pos2);

		if (pData->m_strID != pData2->m_strID)
		{
			bTrue = FALSE;
			break;
		}

		if (pData->m_strValue != pData2->m_strValue)
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

BOOL CTestTask::IsDeviceAttrEmpty()
{
	POS pos = m_pDeviceAttr->GetHeadPosition();
	CDvmData *pData = NULL;
	BOOL bTrue = FALSE;
	long nEmptyCount = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pDeviceAttr->GetNext(pos);

		if (pData->m_strValue.IsEmpty())
		{
			nEmptyCount++;
		}
	}

	return (nEmptyCount == m_pDeviceAttr->GetCount());
}

void CTestTask::EmptyDeviceAttr()
{
	POS pos = m_pDeviceAttr->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pDeviceAttr->GetNext(pos);
		pData->m_strValue.Empty();
	}
}

CDvmDataset* CTestTask::GetCommCmdManyConfig()
{
	if (m_pCommCmdManyConfig == NULL)
	{
		m_pCommCmdManyConfig = new CDvmDataset();
		m_pCommCmdManyConfig->m_strName = DSID_COMMCMDMCONFIG;
		m_pCommCmdManyConfig->m_strID = DSID_COMMCMDMCONFIG;
		AddNewChild(m_pCommCmdManyConfig);
	}

	return m_pCommCmdManyConfig;
}

void CTestTask::InitCommCmdManyConfig(CDvmDataset *pDsExpand)
{
	GetCommCmdManyConfig();
	m_pCommCmdManyConfig->DeleteAll();

	ASSERT (pDsExpand != NULL);
	if (pDsExpand != NULL)
	{
		m_pCommCmdManyConfig->AppendCloneEx(*pDsExpand);
	}
	else
	{
		//<data name="第一路使能" id="Group1Enable" data-type="BOOL" value="1" unit="" min="" max="" format="REALTIMEDATA" index="0" time="0" change="0" step=""/>
		CDvmData *pData = m_pCommCmdManyConfig->AddNewData(_T("Group1Enable"), _T("Group1Enable"), _T("BOOL"), _T("1"));
		pData->m_strFormat = _T("REALTIMEDATA");

	}

	InitCommCmdManyConfigValue(_T("1"));
}

void  CTestTask::DeleteAllProject()
{
	POS pos = GetHeadPosition();
	POS posPrev = pos;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			DeleteAt(posPrev);
		}
	}
}

void CTestTask::SelectAllTestProject(CExBaseList &listProject, BOOL bMainFirst)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseList listTemp;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			listTemp.AddTail(p);
		}
	}

	if (!bMainFirst)
	{
		p = listTemp.GetHead();

		if (p != NULL)
		{
			listTemp.Remove(p);
			listTemp.AddTail(p);
		}
	}

	listProject.Append(listTemp);
	listTemp.RemoveAll();
}

void CTestTask::InitProjectID()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseList listTemp;
	long nProjectID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			((CTestProject*)p)->m_nProjectID = nProjectID;
			nProjectID++;
		}
	}
}

void CTestTask::InitProjectIndex(long &nPrjIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseList listTemp;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			((CTestProject*)p)->m_nProjectIndex = nPrjIndex;
			nPrjIndex++;
		}
	}
}

CTestProject* CTestTask::FindProjectByPrjIndex(long nPrjIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CTestProject *pFind = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			pFind = (CTestProject*)p;

			if (pFind->m_nProjectIndex == nPrjIndex)
			{
				return pFind;
			}
		}
	}

	return NULL;
}

//此函数为多装置多组调用
void CTestTask::InitProjectByCommCmdManyConfig(const CString &strDestPath)
{
	DeleteAllProject();

	POS pos = m_pCommCmdManyConfig->GetHeadPosition();
	long nCount = m_pCommCmdManyConfig->GetCount();
	CDvmData *pData = NULL;
	CTestProject *pNew = NULL;
	long nIndex = 1;
	CString strPath;
	//单装置、多组的模式
	strPath.Format(_T("%s%s\\"), strDestPath, m_strID);
	CString strTmBegin;
	strTmBegin.Format(_T("%04d%02d%02d%02d%02d%02d"), m_tmPlanBegin.wYear, m_tmPlanBegin.wMonth, m_tmPlanBegin.wDay
		, m_tmPlanBegin.wHour, m_tmPlanBegin.wMinute, m_tmPlanBegin.wSecond);

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pCommCmdManyConfig->GetNext(pos);

		if (pData->m_strValue != _T("1"))
		{
			continue;
		}

		pNew = new CTestProject();
		AddNewChild(pNew);
		pNew->tsk_SetGbxmlFile(m_strTemplateFile);
		pNew->m_strPpDeviceFile = m_strDeviceFile;
		pNew->tsk_SetPpxmlFile(m_strPpTemplateFile);
		pNew->m_strTestType = m_strTestType;
		pNew->m_strPpEngineProgID = m_strPpEngineProgID;

		CString strLocation;
		if (nCount == 1)      //只有一组  ShaoL 2019.04.15
		{
			pNew->m_strName.Format(_T("%s"), m_strID);

			//shaolei  加上时间戳  20220328
			strLocation.Format(_T("%s%s(_%s).%s"), strPath, m_strID, strTmBegin, g_strGuideBookBinaryPostfix);
		}
		else
		{
			pNew->m_strName.Format(g_sLangTxt_SGroupFileName/*_T("%s-组%d")*/
				, m_strID, nIndex);
			
			strLocation.Format(g_sLangTxt_SGroupS/*_T("%s%s-组%d.%s")*/
				, strPath, m_strID, nIndex, g_strGuideBookBinaryPostfix);
		}
//2019-4-23   lijunqing 合并邵雷代码注释，以上部分为邵雷修改	
//		pNew->m_strName.Format(g_sLangTxt_SGroupFileName/*_T("%s-组%d")*/
//			, m_strID, nIndex);
		pNew->m_strID = pNew->m_strName;
		pNew->m_strLocalID = pNew->m_strName;
//		CString strLocation;
//		strLocation.Format(g_sLangTxt_SGroupS/*_T("%s%s-组%d.%s")*/
//			, strPath, m_strID, nIndex, g_strGuideBookBinaryPostfix);
		pNew->tsk_SetLocation(strLocation);

		nIndex++;
	}

	m_strTaskFile.Format(_T("%s\\%s.%s"), strPath, m_strID, g_strGuideBookBinaryPostfix_SdvSpoMgrp);
}

void CTestTask::InitCommCmdManyConfigValue(const CString &strValue)
{
	POS pos = m_pCommCmdManyConfig->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pCommCmdManyConfig->GetNext(pos);
		pData->m_strValue = strValue;
	}
}

void CTestTask::SetCommCmdManyConfigValue(const CString &strMaxID)
{
	POS pos = m_pCommCmdManyConfig->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pCommCmdManyConfig->GetNext(pos);
		pData->m_strValue = _T("1");
		
		if (pData->m_strID == strMaxID)
		{
			break;
		}
	}

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pCommCmdManyConfig->GetNext(pos);
		pData->m_strValue = _T("0");
	}
}

#ifndef _not_use_autotest_
void CTestTask::ExportWordReport(MSWord::_Application &WordApp)
{
	if ( WordApp == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_CreatWordFail/*_T("创建Word失败！导出任务报告失败！")*/);
		return;
	}

	long nRows = GetCount() + 1;
	long nCols = 3;

	MSWord::Documents docs =  WordApp.GetDocuments();
	MSWord::_Document oDoc = NULL;
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);
	COleVariant Password(_T(""));
	COleVariant WritePassword(_T(""));
	CString strRptTmplFile;
	strRptTmplFile = m_strTaskFile;
	strRptTmplFile = ChangeFilePostfix(strRptTmplFile, _T("doc"));
	strRptTmplFile = strRptTmplFile.Left(strRptTmplFile.GetLength() - 4);
	strRptTmplFile += _T("_Summary.doc");

	COleVariant TmplFile(_T(""));
	POS pos = GetHeadPosition();
	long nRow = 0;
	COleVariant vwdWord9TableBehavior((LONG)MSWord::wdWord9TableBehavior);
	COleVariant vwdAutoFitFixed((LONG)MSWord::wdAutoFitFixed);
	COleVariant vwdPreferredWidthPoints((LONG)MSWord::wdPreferredWidthPoints);

	try
	{
		oDoc = docs.Add(&TmplFile,&covFalse,&FileFormat,&covTrue);
		MSWord::Selection oSelection = WordApp.GetSelection();
		oSelection.TypeParagraph();
		oSelection.TypeParagraph();

		MSWord::Tables oTables = oDoc.GetTables();
		MSWord::Range oRange = oSelection.GetRange();
		MSWord::Table  oTable  = oTables.Add(oRange, nRows, nCols, vwdWord9TableBehavior, vwdAutoFitFixed);
		MSWord::Columns oCols = oTable.GetColumns();
		MSWord::Column oCol = oCols.Item(1);
		oCol.SetPreferredWidthType(MSWord::wdPreferredWidthPercent);
		oCol.SetPreferredWidth(0.20);

		oCol = oCols.Item(2);
		oCol.SetPreferredWidthType(MSWord::wdPreferredWidthPoints);
		oCol.SetPreferredWidth(0.50);

		oCol = oCols.Item(3);
		oCol.SetPreferredWidthType(MSWord::wdPreferredWidthPoints);
		oCol.SetPreferredWidth(0.30);

		MSWord::Rows oRows = oTable.GetRows();
		MSWord::Row  oRow;
		MSWord::Cells oCells;
		MSWord::Cell oCell = NULL;
		CString strText;
		nRow = 1;

		oRow = oRows.Item(nRow);
		oCells = oRow.GetCells();
		oCell = oCells.Item(1);
		oCell.Select();
		oSelection.SetText(g_sLangTxt_Index/*_T("编号")*/);
		oCell = oCells.Item(2);
		oCell.Select();
		oSelection.SetText(g_sLangTxt_TestReport/*_T("测试报告")*/);
		oCell = oCells.Item(3);
		oCell.Select();
		oSelection.SetText(g_sLangTxt_Conclusion/*_T("结论")*/);

		nRow = 2;

		while (pos != NULL)
		{
			CTestProject *pProject = (CTestProject*)GetNext(pos);
			oRow = oRows.Item(nRow);
			oCells = oRow.GetCells();
			oCell = oCells.Item(1);
			strText.Format(_T("%d"), nRow);
			oCell.Select();
			oSelection.SetText(strText);

			oCell = oCells.Item(2);
			oCell.Select();
			oSelection.SetText(pProject->m_strName);
			oCell.Select();
			oRange = oSelection.GetRange();

			MSWord::Hyperlinks oHyperlinks = oDoc.GetHyperlinks();
			COleVariant vAddr, vAddrSub, vScreenTip, vTextToDisplay;
			strText = pProject->m_strName;
			strText = ChangeFilePostfix(strText, _T("doc"));
			vAddrSub = _bstr_t(_T(""));
			vAddr = strText;
			vScreenTip = strText;
			vTextToDisplay = strText;
			COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			oHyperlinks.Add(oRange, vAddr, vAddrSub, vScreenTip, vTextToDisplay, vOpt);
			MSWord::_Font oFont;
			oCell = oCells.Item(3);
			oCell.Select();
			oFont = oSelection.GetFont();
			long nColor = oFont.GetColor();

			if (pProject->GetCount() == 0)
			{
				strText = g_sLangTxt_Qualified/*_T("合格")*/;
			}
			else
			{
				strText = g_sLangTxt_UnqualifiedItem/*_T("有不合格项")*/;
				oFont.SetColor(MSWord::wdColorRed);
			}

			oSelection.TypeText(strText);
			oFont.SetColor(nColor);

			nRow++;
		}
	}
	catch (...)
	{
		
	}

	try
	{
		TmplFile = strRptTmplFile;
		oDoc.SaveAs(TmplFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
		oDoc.Close(covFalse,covOptional,covOptional);
	}
	catch (...)
	{
	}

	oDoc = NULL;
	docs = NULL;
}
#endif

void CTestTask::InitAllProject()
{
	POS pos = GetHeadPosition();
	CTestProject *pProject = NULL;

	while (pos != NULL)
	{
		pProject = (CTestProject *)GetNext(pos);

		pProject->m_strPpEngineProgID = m_strPpEngineProgID;
		pProject->tsk_SetPpxmlFile(m_strPpTemplateFile);
		pProject->m_strPpDeviceFile   = m_strDeviceFile;
	}
}

#ifndef _not_use_autotest_
void CTestTask::CreateTask_AllTestType(CGuideBook *pGuideBook, const CString &strRptFile, const CString &strTaskPath)
{
	CTestTypes *pTestTypes = &pGuideBook->m_oTestTypes;
	POS pos = pTestTypes->GetHeadPosition();
	CTestType *pTestType = NULL;

	while (pos != NULL)
	{
		pTestType = (CTestType *)pTestTypes->GetNext(pos);
		CreateProject(pTestType, pGuideBook, strRptFile, strTaskPath);
	}
}

CTestProject* CTestTask::CreateProject(CTestType *pTestType, CGuideBook *pGuideBook, const CString &strRptFile, const CString &strTaskPath)
{
// 	CTestProject *pTestProject = new CTestProject();
// 
// 	//可以根据TestType进行调整
// 	CString strFile;
// 
// 	if (strTaskPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
// 	{
// 		strFile.Format(_T("%s%s.%s"), strTaskPath, pTestType->m_strName, g_strGuideBookBinaryPostfix);
// 	}
// 	else
// 	{
// 		strFile.Format(_T("%s\\%s.%s"), strTaskPath, pTestType->m_strName, g_strGuideBookBinaryPostfix);
// 	}
// 
// 	pGuideBook->SaveBinaryFile(strFile);
// 	pTestProject->m_strLocation       = strFile;
// 
// 	strFile = ChangeFilePostfix(strFile, _T("doc"));
// 	::X_CopyFile(strRptFile, strFile, FALSE);
// 
// 	pTestProject->m_strPpTemplateFile = pGuideBook->m_strPpTemplateFile;  //规约模板文件
// 	pTestProject->m_strPpDeviceFile   = pGuideBook->m_strDeviceModelFile ;    //设备点表文件
// 	pTestProject->m_strTemplateFile   = m_strTemplateFile;    //作业指导书文件
// 	pTestProject->m_strReportMapFile  = ChangeFilePostfix(m_strTemplateFile, _T("doc"));  //报告映射文件
// 	pTestProject->m_strPpEngineProgID = pGuideBook->m_strPpEngineProgID;
// 	pTestProject->m_strName.Format(_T("%s.%s"), pTestType->m_strName, g_strGuideBookBinaryPostfix);
// 	pTestProject->m_strID             = pTestProject->m_strName;
// 	pTestProject->m_strTestType       = pTestType->m_strName;
// 
// 	AddNewChild(pTestProject);

	return CreateProject(pTestType->m_strName, pTestType->m_strName, pGuideBook, strRptFile, strTaskPath);
}


CTestProject* CTestTask::CreateProject(const CString &strTestType, const CString &strProjectName, CGuideBook *pGuideBook, const CString &strRptFile, const CString &strTaskPath)
{
	CTestProject *pTestProject = new CTestProject();

	//可以根据TestType进行调整
	CString strFile;

	if (strTaskPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
	{
		strFile.Format(_T("%s%s.%s"), strTaskPath, strProjectName, g_strGuideBookBinaryPostfix);
	}
	else
	{
		strFile.Format(_T("%s\\%s.%s"), strTaskPath, strProjectName, g_strGuideBookBinaryPostfix);
	}

	Gb_SetGbModifiedFlag(pGuideBook, TRUE);
	pGuideBook->SaveBinaryFile(strFile, CTCtrlCntrConfig::Get_RWReportFileMode());
	//pTestProject->m_strLocation       = strFile;
	pTestProject->tsk_SetLocation(strFile);

	strFile = ChangeFilePostfix(strFile, _T("doc"));
	::X_CopyFile(strRptFile, strFile, FALSE);

	pTestProject->tsk_SetPpxmlFile(pGuideBook->m_strPpTemplateFile);  //规约模板文件
	pTestProject->m_strPpDeviceFile   = pGuideBook->m_strDeviceModelFile ;    //设备点表文件
	pTestProject->tsk_SetGbxmlFile(m_strTemplateFile);    //作业指导书文件
	pTestProject->m_strReportMapFile  = ChangeFilePostfix(m_strTemplateFile, _T("doc"));  //报告映射文件
	pTestProject->m_strPpEngineProgID = pGuideBook->m_strPpEngineProgID;
	pTestProject->m_strName.Format(_T("%s.%s"), strProjectName, g_strGuideBookBinaryPostfix);
	pTestProject->m_strID             = pTestProject->m_strName;
	pTestProject->m_strTestType       = strTestType;

	AddNewChild(pTestProject);

	return pTestProject;
}
#endif

#ifndef _not_use_autotest_
void CTestTask::StitchWordReport(CWnd *pParentWnd, MSWord::_Application &WordApp)
{
	if ( WordApp == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_CreatWordFail/*_T("创建Word失败！导出任务报告失败！")*/);
		return;
	}

	if (CanStitchWordReport())
	{
		StitchWordReportThread(WordApp);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_CreatWordFail/*_T("创建Word失败！导出任务报告失败！")*/);
	}
}

CString CTestTask::GetStitchWordReportFile()
{
	CString strRptTmplFile;
	strRptTmplFile = m_strTaskFile;
	strRptTmplFile = ChangeFilePostfix(strRptTmplFile, _T("doc"));

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CTestProject *pProject = NULL;
	CString strName;
	CString strTaskName;
	strTaskName = m_strName;
	strTaskName.MakeLower();
	BOOL bSame = FALSE;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		strName = ParseFileName(p->m_strName);
		strName.MakeLower();

		if (strName == strTaskName)
		{
			bSame = TRUE;
			break;
		}
	}

	if (bSame)
	{
		strRptTmplFile = strRptTmplFile.Left(strRptTmplFile.GetLength() - 4);
		SYSTEMTIME tm;
		::GetLocalTime(&tm);

#ifdef _UNICODE
		strRptTmplFile.AppendFormat(L"_%04d%02d%02d%02d%02d%02d.doc", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
#else
		strRptTmplFile.AppendFormat("_%04d%02d%02d%02d%02d%02d.doc", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
#endif
	}

	return strRptTmplFile;
}

UINT CTestTask::StitchWordReportThread(MSWord::_Application &WordApp)
{
	MSWord::Documents docs =  WordApp.GetDocuments();
	MSWord::_Document oDoc = NULL;
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);
	COleVariant Password(_T(""));
	COleVariant WritePassword(_T(""));
	CString strRptTmplFile;
	CString strPrjRptFile;

	strRptTmplFile = GetStitchWordReportFile();

	COleVariant strRptFile(_T(""));
	POS pos = GetHeadPosition();
	long nRow = 0;
	COleVariant vwdWord9TableBehavior((LONG)MSWord::wdWord9TableBehavior);
	COleVariant vwdAutoFitFixed((LONG)MSWord::wdAutoFitFixed);
	COleVariant vwdPreferredWidthPoints((LONG)MSWord::wdPreferredWidthPoints);
	CExBaseObject *p = NULL;

	try
	{
		WordApp.SetVisible(TRUE);
		oDoc = docs.Add(&strRptFile,&covFalse,&FileFormat,&covTrue);
		strRptFile = strRptTmplFile;
		oDoc.SaveAs(strRptFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);

		while (pos != NULL)
		{
			p = GetNext(pos);

			if (p->GetClassID() != CLASSID_TESTPROJECT)
			{
				continue;
			}
			
			CTestProject *pProject = (CTestProject*)p;
			strPrjRptFile = pProject->m_strID;
			strPrjRptFile = ChangeFilePostfix(strPrjRptFile, _T("doc"));
			//CGuideBook oGuideBook;
			//oGuideBook.OpenBinaryFile(pProject->m_strID);
			COleVariant vstrPrjRptFile(_T(""));
			vstrPrjRptFile = strPrjRptFile;
			MSWord::_Document oDocSrc = docs.Open(&vstrPrjRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
			wordrpt_InsertWordEdit(WordApp, oDoc, oDocSrc, strRptTmplFile, vstrPrjRptFile, 0);
			oDocSrc.Close(covFalse,covOptional,covOptional);
		}
	}
	catch (...)
	{

	}

	try
	{
		oDoc.SaveAs(strRptFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
		oDoc.Close(covFalse,covOptional,covOptional);
	}
	catch (...)
	{
	}

	oDoc = NULL;
	docs = NULL;

	return 0;
}

BOOL CTestTask::CanStitchWordReport()
{
	CTestProject *pTestProject = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();
	BOOL bCan = TRUE;
	CString strRpt;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pTestProject = (CTestProject *)p;
		
		if (!pTestProject->IsTestState_Finish())
		{
			strRpt = GetPathFileNameFromFilePathName(pTestProject->m_strID);
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_TestPrjNotFinish, strRpt);
			bCan = FALSE;
			break;
		}
	}

	return bCan;
}
#endif

void CTestTask::SelectCmmCfgChannel(CExBaseList &listCmmCfgChannel)
{
#ifndef GUIDEBOOK_DEV_MODE
	if (m_pDeviceCmmConfig == NULL)
	{
		return;
	}

	//更新自身通讯通道
	m_listCmmCfg.RemoveAll();
	m_pDeviceCmmConfig->SelectCmmCfgChannel(m_listCmmCfg);

	//初始化总的通讯通道信息表格
	POS pos = m_listCmmCfg.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)m_listCmmCfg.GetNext(pos);

		if (listCmmCfgChannel.FindByClassID(p->GetClassID()) == NULL)
		{
			listCmmCfgChannel.AddTail(p);
		}
	}
#endif
}

void CTestTask::WritePpMmsEngineConfig()
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestProject *pProject = NULL;
	CMMS_STACK_CFG oMMS_STACK_CFG;
	oMMS_STACK_CFG.Open_MMS_STACK_CFG_Outer();
	CStkCfg_RemoteAddressList *pRemoteAddressList = oMMS_STACK_CFG.GetRemoteAddressList();
	long nIndex = 0;
	pRemoteAddressList->SetCount(GetCount());
	CStkCfg_RemoteAddress *pAddress = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pProject = (CTestProject *)GetNext(pos);
		pAddress = (CStkCfg_RemoteAddress *)pRemoteAddressList->GetAtIndex(nIndex);
		pAddress->SetIP(pProject->m_strLocalID);
		pAddress->m_strModel = pProject->m_strName;
		nIndex++;
	}

	oMMS_STACK_CFG.Save_MMS_STACK_CFG_Outer();
	oMMS_STACK_CFG.WriteIpToVMDFile();
#endif
}

void CTestTask::ValidateSystemPath(const CString &strFrom, const CString &strTo)
{
	_P_ReplaceSystemPath(strFrom, strTo, m_strLocation);
	_P_ReplaceSystemPath(strFrom, strTo, m_strPpTemplateFile);
	_P_ReplaceSystemPath(strFrom, strTo, m_strTemplateFile);
	_P_ReplaceSystemPath(strFrom, strTo, m_strDeviceFile);

	CTestProject *pTestProject = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();
	BOOL bCan = TRUE;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pTestProject = (CTestProject *)p;
		pTestProject->ValidateSystemPath(strFrom, strTo);
	}
}

BOOL CTestTask::HasAllProjectCreated()
{
	CTestProject *pTestProject = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();
	BOOL bTrue = TRUE;
	CString strLocation;
	long nCount = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pTestProject = (CTestProject *)p;
		strLocation = pTestProject->tsk_GetLocation(FALSE);
		
		if (strLocation.GetLength() < 10)
		{
			pTestProject->ValidateLocation();
		}

		strLocation = pTestProject->tsk_GetLocation();
		nCount++;

		if (pTestProject->m_nSelect == 0)
		{
			continue;
		}

		if (! IsFileExist(strLocation))
		{
			bTrue = FALSE;
		}
	}

	if (nCount == 0)
	{
		bTrue = FALSE;
	}

	return bTrue;
}

void CTestTask::SetDeviceFile(const CString &strFile)
{
	m_strDeviceFile = strFile;

	CTestProject *pTestProject = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pTestProject = (CTestProject *)p;
		//pTestProject->m_strPpDeviceFile = strFile;
		pTestProject->SetDeviceFile(strFile);
	}
}

void CTestTask::SetTestType(const CString &strTestTask)
{
	CTestProject *pTestProject = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();
	m_strTestType = strTestTask;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pTestProject = (CTestProject *)p;
		pTestProject->m_strTestType = strTestTask;
	}
}

CString CTestTask::GetPoProjectFile()
{
	CString strFile;
	strFile = m_strTaskFile;
	strFile = ChangeFilePostfix(strFile, g_strPodFilePostfix);

	return strFile;
}

BOOL CTestTask::IsTestEligible()
{
	BOOL bEligible = TRUE;
	CTestProject *pTestProject = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pTestProject = (CTestProject *)p;

		if (pTestProject->GetCount() > 0)
		{
			bEligible = FALSE;
			break;
		}

		if (pTestProject->m_strTestRsltJdg.GetLength() > 0)
		{
			bEligible = FALSE;
			break;
		}
	}

	return bEligible;
}

BOOL CTestTask::IsTestState_Finish()
{
	BOOL bIsTestState_Finish = TRUE;
	CTestProject *pTestProject = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pTestProject = (CTestProject *)p;

		if (!pTestProject->IsTestState_Finish())
		{
			bIsTestState_Finish = FALSE;
			break;
		}
	}

	return bIsTestState_Finish;
}

void CTestTask::SetGlobalDatas_DeviceAttr()
{
	CTestProject *pTestProject = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pTestProject = (CTestProject *)p;
		pTestProject->SetGlobalDatas_DeviceAttr(m_pDeviceAttr);
	}
}

void CTestTask::SavePoProjectFile()
{
	if (m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		SavePoProjectFile_MmsEngine();
	}
	else if (m_strPpEngineProgID == g_strPpEngineProgID)
	{
		SavePoProjectFile_PpEngine();
	}
}

void CTestTask::SavePoProjectFile_MmsEngine()
{
#ifndef GUIDEBOOK_DEV_MODE

	CTestTask *pTask = NULL;
	CMMS_STACK_CFG oMMS_STACK_CFG;
	oMMS_STACK_CFG.Open_MMS_STACK_CFG_Outer();
	CStkCfg_RemoteAddressList *pRemoteAddressList = oMMS_STACK_CFG.GetRemoteAddressList();
	long nIndex = 0;
	pRemoteAddressList->SetCount(GetCount());
	CStkCfg_RemoteAddress *pAddress = NULL;
	CDeviceCmmConfig *pDeviceCmmConfig = NULL;
	CCmmMmsConfig *pMmsConfig = NULL;

		pTask = this;
		pDeviceCmmConfig = pTask->GetDeviceCmmConfig();
		ASSERT (pDeviceCmmConfig != NULL);
		pMmsConfig = pDeviceCmmConfig->GetConfigMms();
		ASSERT (pMmsConfig != NULL);

		pAddress = (CStkCfg_RemoteAddress *)pRemoteAddressList->GetAtIndex(nIndex);
		pAddress->SetIP(pMmsConfig->m_strRemoteIP);
		pAddress->m_strKey = pMmsConfig->m_strKey;
		pAddress->m_strPSW = pMmsConfig->m_strPSW;

		pAddress->m_strModel = pTask->m_strName;
		nIndex++;

	oMMS_STACK_CFG.Save_MMS_STACK_CFG_Outer();
	oMMS_STACK_CFG.WriteIpToVMDFile();

#endif
}

void CTestTask::SavePoProjectFile_PpEngine()
{
#ifndef GUIDEBOOK_DEV_MODE
	CString strFile = GetPoProjectFile();

	CPpCfgDevices oPpCfgDevices;
	CTestTask *pTask = NULL;
	CPpCfgDevice *pDevice = NULL;
	CDeviceCmmConfig *pDeviceCmmConfig = NULL;
	CExBaseObject *p = NULL;

		pTask = (CTestTask *)this;
		pDevice = new CPpCfgDevice();
		pDevice->m_strName = pTask->m_strName;
		pDevice->m_strID = pTask->m_strID;
		oPpCfgDevices.AddNewChild(pDevice);
		pDeviceCmmConfig = pTask->GetDeviceCmmConfig();
		ASSERT (pDeviceCmmConfig != NULL);
		pDevice->m_pDeviceCmmConfig = (CDeviceCmmConfig*)pDeviceCmmConfig->Clone();
		pDevice->AddNewChild(pDevice->m_pDeviceCmmConfig);
		pDevice->m_strTemplateFile = pTask->m_strPpTemplateFile;
		pDevice->m_strDdvmFile = pTask->m_strDeviceFile;

	oPpCfgDevices.SaveCfgDevicesFile(strFile);

#endif
}


CString CTestTask::tsk_GetGbxmlFile(BOOL bFullPath)
{
	return tskapi_GetGbxmlFile(m_strTemplateFile, bFullPath);
}

void CTestTask::tsk_SetGbxmlFile(const CString &strFile)
{
	tskapi_SetGbxmlFile(strFile, m_strTemplateFile);
}

CString CTestTask::tsk_GetPpxmlFile(BOOL bFullPath)
{
	return tskapi_GetPpxmlFile(m_strPpTemplateFile, bFullPath);
}

void CTestTask::tsk_SetPpxmlFile(const CString &strFile, BOOL bUpdateAllProject)
{
	tskapi_SetPpxmlFile(strFile, m_strPpTemplateFile);

	if (!bUpdateAllProject)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CTestProject *pPrj = NULL;
	CDvmValue *pRpt = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pPrj = (CTestProject *)p;
		pPrj->tsk_SetPpxmlFile(m_strPpTemplateFile);
	}
}

void CTestTask::GetByDvmObj(CDvmData *pDvmData)
{
	pDvmData->m_strID = m_strLocalID;
	pDvmData->m_strValue = m_strLocation;

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CTestProject *pPrj = NULL;
	CDvmValue *pRpt = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		pPrj = (CTestProject *)p;
		pDvmData->AddValue(pPrj->m_strLocalID, pPrj->GetLocation());
	}
}

//2019-4-28  lijunqing  调试四方多装置、项目组每台装置独立执行
void CTestTask::Debug_AddTaskBinBoutOffset(long nBinffset, long nBoutOffset)
{
	CString strValue;
	CDvmData *pData = NULL;

	//AtsRpcTestDef_bin_offset
	strValue.Format(_T("%d"), nBinffset);
	pData = (CDvmData*)m_pDeviceAttr->FindByID(AtsRpcTestDef_bin_offset);
	
	if (pData == NULL)
	{
		m_pDeviceAttr->AddNewData(AtsRpcTestDef_bin_offset, AtsRpcTestDef_bin_offset, _T("long"), strValue);
	}
	else
	{
		pData->m_strValue = strValue;
	}

	//AtsRpcTestDef_bout_offset
	pData = (CDvmData*)m_pDeviceAttr->FindByID(AtsRpcTestDef_bout_offset);
	strValue.Format(_T("%d"), nBinffset);

	if (pData == NULL)
	{
		m_pDeviceAttr->AddNewData(AtsRpcTestDef_bout_offset, AtsRpcTestDef_bout_offset, _T("long"), strValue);
	}
	else
	{
		pData->m_strValue = strValue;
	}

}

//2020-12-31  lijunqing
void CTestTask::SetTestState(const CString &strState)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		((CTestProject *)p)->SetTestState(strState);
	}
}

BOOL CTestTask::HasTestProjectSelected()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTPROJECT)
		{
			continue;
		}

		if ( ((CTestProject *)p)->m_nSelect != 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}


//2021-10-01  lijunqing
void CTestTask::SetEngineProgID(const CString &strEngineProgID)
{
	m_strPpEngineProgID = strEngineProgID;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			((CTestProject *)p)->m_strPpEngineProgID = strEngineProgID;
		}
	}
}

//shaolei 2023-11-2
void CTestTask::SetEngineMode(const CString &strEngineMode)
{
	m_strEngineMode = strEngineMode;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			((CTestProject *)p)->m_strEngineMode = strEngineMode;
		}
	}
}

void CTestTask::SetDvmFile(const CString &strDvmFile)
{
	m_strDeviceFile = strDvmFile;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			((CTestProject *)p)->m_strPpDeviceFile = strDvmFile;
		}
	}
}

void CTestTask::SetPpTemplateFile(const CString &strPpXmlFile)
{
	m_strPpTemplateFile = strPpXmlFile;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTPROJECT)
		{
			((CTestProject *)p)->SetProtocalTemplate(strPpXmlFile);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CTestTasks
CTestTasks::CTestTasks()
{
	m_pExpandDatas = NULL;
	m_pExpandDatasAutoSet = NULL;
	m_pDeviceAttrsDefine = NULL;
	m_pTestAppDefine = NULL;
	m_pTestGlobalDefine = NULL;

	m_bPingState = FALSE;

	m_strTasksParentPath = _P_GetWorkspacePath();
	m_dwAtsRptType = REPORTFILL_INDEX_NONE;

	Init();
}

CTestTasks::~CTestTasks()
{
	m_listCmmCfgChannel.RemoveAll();
}

void CTestTasks::Init()
{
	m_pTestApp = NULL;
	m_strReportFillClassID = REPORTFILL_PROGID_WORD;
	InitSystemPath();
}

void CTestTasks::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATASET)
		{
			if (p->m_strID == DSID_TESTAPP)
			{
				m_pTestApp = (CDvmDataset *)p;
				break;
			}
		}
	}

	InitAllCmdCfgChannels();
}

long CTestTasks::IsEqual(CExBaseObject* pObj)
{
	CTestTasks *pTestTasks = (CTestTasks*)pObj;

	if(pObj == NULL)
		return 0;

	long nCount1 = pTestTasks->GetCount();
	long nCount2 = GetCount();

	if(nCount1 == nCount2)
	{
		for(long i=0;i<nCount1;i++)
		{
			CTestTask* pTestTask1 = (CTestTask*)pTestTasks->GetAtIndex(i);
			CTestTask* pTestTask2 = (CTestTask*)GetAtIndex(i);
			if(!pTestTask1->IsEqual(pTestTask2))
				return 0;
		}
		return 1;
	}

	return 0;
}

long CTestTasks::Copy(CExBaseObject* pDesObj)
{
	if(pDesObj != NULL)
	{
		CTestTasks* pTemp = (CTestTasks*)pDesObj;

		long nCount = GetCount();
		for(long i=0;i<nCount;i++)
		{
			CTestTask* pTask1 = (CTestTask*)GetAtIndex(i);
			CTestTask* pTask2 = (CTestTask*)pTask1->Clone();
			pTemp->AddTail(pTask2);
		}
	}

	return 0;
}

CExBaseObject* CTestTasks::Clone()
{
	CTestTasks* pNew = new CTestTasks;
	Copy(pNew);

	return pNew;
}

CExBaseObject* CTestTasks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskKey)
	{
		CTestTask* pTestTask = new CTestTask;
		return pTestTask;
	}

	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strProjectKey)
	{
		CTestProject* pTestProject = new CTestProject;
		return pTestProject;
	}

	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->CDvmDatasetKey())
	{
		return new CDvmDataset();
	}

	return NULL;
}

CExBaseObject* CTestTasks::CreateNewChild(long nClassID)
{
	return NULL;
}


long CTestTasks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTemplateFileKey,oNode,m_strTemplateFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportFillClassIDKey,oNode,m_strReportFillClassID);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strSystemPathKey,oNode,m_strSystemPath);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strDeviceModelFileKey,oNode,m_strDeviceFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strMacroFileKey,oNode,m_strMacroFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestTypeKey,oNode,m_strTestType);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oNode,m_strPpTemplateFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strXTestDbGroupPathKey,oNode,m_strXTestDbGroupPath);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strShowWordRptKey,oNode,m_dwAtsRptType);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strEngineModeKey,oNode,m_strEngineMode);  //2023-11-3 shaolei

	return 0;
}

long CTestTasks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTemplateFileKey,oElement,m_strTemplateFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strReportFillClassIDKey,oElement,m_strReportFillClassID);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strSystemPathKey,oElement,m_strSystemPath);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strDeviceModelFileKey,oElement,m_strDeviceFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strMacroFileKey,oElement,m_strMacroFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTestTypeKey,oElement,m_strTestType);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oElement,m_strPpTemplateFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strXTestDbGroupPathKey,oElement,m_strXTestDbGroupPath);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strShowWordRptKey,oElement,m_dwAtsRptType);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strEngineModeKey,oElement,m_strEngineMode);  //shaolei 2023-11-3

	return 0;
}


BOOL CTestTasks::OpenTasksFile(const CString &strFile)
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	BOOL bTrue = FALSE;
	m_strTasksFile = strFile;

	bTrue = OpenXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	ValidateSystemPath();

	InitProjectIndex();

	return bTrue;
}

BOOL CTestTasks::SaveTasksFile(const CString &strFile)
{
	if (strFile.GetLength() > 0)
	{
		m_strTasksFile = strFile;
		return SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
	}
	else
	{
		return SaveXmlFile(m_strTasksFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
	}
}

BOOL CTestTasks::SaveTasksFile()
{
	return SaveTasksFile(m_strTasksFile);
}

BOOL CTestTasks::InitTasksFileByParentPath(BOOL bCreatePath)
{
	m_strTasksPath.Format(_T("%s%s\\"), m_strTasksParentPath, m_strName);

	if (bCreatePath)
	{
		::CreateAllDirectories(m_strTasksPath);
	}

	return TRUE;
}

BOOL CTestTasks::SaveTasksFileByParentPath()
{
	::CreateAllDirectories(m_strTasksPath);
	CString strFile;
	strFile.Format(_T("%s%s.%s"), m_strTasksPath, m_strName, g_strGuideBookMdvMgrpTaskPostfix);
	return SaveTasksFile(strFile);
}

void CTestTasks::SetTasksNameAndID(const CString &strName, const CString &strID)
{
	m_strName = strName;
	m_strID = strID;
}

void CTestTasks::DeleteTestTasks()
{
	m_listCmmCfgChannel.RemoveAll();

	DeleteAll();
	m_pTestApp = NULL;
}

void CTestTasks::DeleteAllTestTask()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			DeleteAt(posPrev);
		}
	}
}


void CTestTasks::SetTestType(const CString &strTestTask)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	m_strTestType = strTestTask;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			((CTestTask*)p)->SetTestType(strTestTask);
		}
	}
}

void CTestTasks::SetAllSelect(long nSel)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			((CTestTask*)p)->m_nSelect = nSel;
		}
	}
}

BOOL CTestTasks::IsTestState_Finish()
{
	BOOL bIsTestState_Finish = TRUE;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			if (! ((CTestTask*)p)->IsTestState_Finish() )
			{
				bIsTestState_Finish = FALSE;
				break;
			}
		}
	}

	return bIsTestState_Finish;
}

void CTestTasks::SetGlobalDatas_DeviceAttr()
{
	BOOL bIsTestState_Finish = TRUE;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			((CTestTask*)p)->SetGlobalDatas_DeviceAttr();
		}
	}
}

void CTestTasks::InitTasksByTestWzdDefine(CTestWzdDefine  *pTestWzdDefine, BOOL bCreateChild)
{
	CTestGlobalDefine *pTestGlobalDef = &pTestWzdDefine->m_oTestGlobalDefine;

	if (bCreateChild)
	{
		CDvmDataset *pTestApp = pTestWzdDefine->GetTestApp();
		m_pTestApp = (CDvmDataset *)pTestApp->Clone();
		AddNewChild(m_pTestApp);
	}

	m_strTemplateFile = pTestWzdDefine->GetTemplateFile();
	m_strPpEngineProgID = pTestWzdDefine->m_strPpEngineProgID;
	m_strDeviceFile = pTestWzdDefine->GetDeviceFile();
	m_strPpTemplateFile = pTestWzdDefine->GetPpTemplateFile();
	m_strMacroFile = pTestWzdDefine->m_strMacroFile;
// 	m_gridTestApp.m_pTestAppDefine = pTestGlobalDef->m_pTestAppDefine;
// 	m_gridTestApp.ShowDatas();

	m_pExpandDatas = pTestGlobalDef->m_pExpandDatas;
	m_pExpandDatasAutoSet = pTestGlobalDef->m_pExpandDatasAutoSet;
	m_pDeviceAttrsDefine = pTestGlobalDef->m_pDeviceAttrsDefine;
	m_pTestAppDefine = pTestGlobalDef->m_pTestAppDefine;
	m_pTestGlobalDefine = pTestGlobalDef;
}

CDvmDataset* CTestTasks::GetTestApp()
{
	if (m_pTestApp == NULL)
	{
		m_pTestApp = new CDvmDataset();
		m_pTestApp->m_strName = DSID_TESTAPP;
		m_pTestApp->m_strID = m_pTestApp->m_strName;
		AddNewChild(m_pTestApp);
	}

	return m_pTestApp;
}

CDvmData* CTestTasks::AddTestApp(CDvmData *pTestApp)
{
	CDvmData *pNew = (CDvmData*)pTestApp->Clone();
	m_pTestApp->AddNewChild(pNew);
	InitTestAppAfterAdd(pNew);

	return pNew;
}

void CTestTasks::InitTestAppAfterAdd(CDvmData *pTestApp)
{
	if (pTestApp == NULL)
	{
		return;
	}

	CDvmValue *pFind = NULL;

	if (pTestApp->m_strName.GetLength() == 0)
	{
		pFind = (CDvmValue *)pTestApp->FindByID(_T("Name"));

		if (pFind != NULL)
		{
			pTestApp->m_strName = pFind->m_strValue;
		}
	}


	if (pTestApp->m_strID.GetLength() == 0)
	{
		pFind = (CDvmValue *)pTestApp->FindByID(_T("SN"));

		if (pFind != NULL)
		{
			pTestApp->m_strID = pFind->m_strValue;
		}
	}
}

CDvmData* CTestTasks::AddTestApp(CValues *pValues, CDvmDataset *pTestAppDef)
{
	if (dvm_FindDataInDataset(pValues, m_pTestApp) != NULL)
	{
		return NULL;
	}

	CDvmData *pNew = dvm_AddValuesToDataset(pValues, pTestAppDef, m_pTestApp);
	InitTestAppAfterAdd(pNew);

	return pNew;
}

void CTestTasks::DeleteTestApp(CDvmData *pTestApp)
{
	m_pTestApp->Delete(pTestApp);
}

BOOL CTestTasks::HasTestTask()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			return TRUE;
		}
	}

	return FALSE;
}

long CTestTasks::SelectAllTestTask(CExBaseList &listTask)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			listTask.AddTail(p);
		}
	}

	return listTask.GetCount();
}

long CTestTasks::SelectAllTestProject(CExBaseList &listProject, BOOL bMainFirst)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			((CTestTask*)p)->SelectAllTestProject(listProject, bMainFirst);
		}
	}

	return listProject.GetCount();
}

void CTestTasks::InitAllCmdCfgChannels()
{
	m_listCmmCfgChannel.RemoveAll();
	POS pos = GetHeadPosition();
	CTestTask *p = NULL;

	while (pos != NULL)
	{
		p = (CTestTask *)GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			p->SelectCmmCfgChannel(m_listCmmCfgChannel);
		}
	}
}

CString CTestTasks::GetPoProjectFile()
{
	CString strFile;
	strFile = m_strTasksFile;
	strFile = ChangeFilePostfix(strFile, g_strPodFilePostfix);

	return strFile;
}

void CTestTasks::SavePoProjectFile()
{
	if (m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		SavePoProjectFile_MmsEngine();
	}
	else if (m_strPpEngineProgID == g_strPpEngineProgID)
	{
		SavePoProjectFile_PpEngine();
	}
}

void CTestTasks::SavePoProjectFile_MmsEngine()
{
#ifndef GUIDEBOOK_DEV_MODE

	CTestTask *pTask = NULL;
	CMMS_STACK_CFG oMMS_STACK_CFG;
	oMMS_STACK_CFG.Open_MMS_STACK_CFG_Outer();
	CStkCfg_RemoteAddressList *pRemoteAddressList = oMMS_STACK_CFG.GetRemoteAddressList();
	long nIndex = 0;
	pRemoteAddressList->SetCount(GetCount());
	CStkCfg_RemoteAddress *pAddress = NULL;
	POS pos = GetHeadPosition();
	CDeviceCmmConfig *pDeviceCmmConfig = NULL;
	CCmmMmsConfig *pMmsConfig = NULL;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		pTask = (CTestTask *)p;
		pDeviceCmmConfig = pTask->GetDeviceCmmConfig();
		ASSERT (pDeviceCmmConfig != NULL);
		pMmsConfig = pDeviceCmmConfig->GetConfigMms();
		ASSERT (pMmsConfig != NULL);

		if (pMmsConfig == NULL)
		{
			continue;
		}

		pAddress = (CStkCfg_RemoteAddress *)pRemoteAddressList->GetAtIndex(nIndex);
		pAddress->SetIP(pMmsConfig->m_strRemoteIP);
		pAddress->m_strKey = pMmsConfig->m_strKey;
		pAddress->m_strPSW = pMmsConfig->m_strPSW;

		pAddress->m_strModel = pTask->m_strName;
		nIndex++;
	}

	oMMS_STACK_CFG.Save_MMS_STACK_CFG_Outer();
	oMMS_STACK_CFG.WriteIpToVMDFile();

#endif
}

void CTestTasks::SavePoProjectFile_PpEngine()
{
#ifndef GUIDEBOOK_DEV_MODE
	CString strFile = GetPoProjectFile();

	CPpCfgDevices oPpCfgDevices;
	POS pos = GetHeadPosition();
	CTestTask *pTask = NULL;
	CPpCfgDevice *pDevice = NULL;
	CDeviceCmmConfig *pDeviceCmmConfig = NULL;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		pTask = (CTestTask *)p;
		pDevice = new CPpCfgDevice();
		pDevice->m_strName = pTask->m_strName;
		pDevice->m_strID = pTask->m_strID;
		oPpCfgDevices.AddNewChild(pDevice);
		pDeviceCmmConfig = pTask->GetDeviceCmmConfig();
		ASSERT (pDeviceCmmConfig != NULL);
		pDevice->m_pDeviceCmmConfig = (CDeviceCmmConfig*)pDeviceCmmConfig->Clone();
		pDevice->AddNewChild(pDevice->m_pDeviceCmmConfig);
		pDevice->m_strTemplateFile = pTask->tsk_GetPpxmlFile(FALSE);
		pDevice->m_strDdvmFile = tskapi_GetDvmFile(pTask->m_strDeviceFile);
	}

	oPpCfgDevices.SaveCfgDevicesFile(strFile);

#endif
}

CTestTask* CTestTasks::FindTestTask(CDvmDataset *pDeviceAttr)
{
	POS pos = GetHeadPosition();
	CTestTask *pTask = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		pTask = (CTestTask *)GetNext(pos);

		if (pTask->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		if (CTCtrlCntrConfig::IsFacBatchTestMode())
		{//工厂批量测试模式下，如果不合格，则不处理
			if (!pTask->IsTestEligible())
			{
				continue;
			}
		}

		if (pTask->IsDeviceAttrSame(pDeviceAttr))
		{
			pFind = pTask;
			break;
		}
	}

	return pFind;
}


CTestTask* CTestTasks::FindTestTaskByEmptyDeviceAttr()
{
	POS pos = GetHeadPosition();
	CTestTask *pTask = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		pTask = (CTestTask *)GetNext(pos);

		if (pTask->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		if (pTask->IsDeviceAttrEmpty())
		{
			pFind = pTask;
			break;
		}
	}

	return pFind;
}

void CTestTasks::EmptyDeviceAttr()
{
	POS pos = GetHeadPosition();
	CTestTask *pTask = NULL;

	while (pos != NULL)
	{
		pTask = (CTestTask *)GetNext(pos);

		if (pTask->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		pTask->EmptyDeviceAttr();
	}
}

CTestTask* CTestTasks::FindTestTask(long nIndex)
{
	CExBaseList listTask;
	CTestTask *pTestTask = NULL;
	SelectAllTestTask(listTask);
	pTestTask = (CTestTask *)listTask.GetAtIndex(nIndex);
	listTask.RemoveAll();

	return pTestTask;
}

void CTestTasks::InitProjectByCommCmdManyConfig()
{
	CString strDestPath = m_strTasksParentPath;
	m_strTasksFile.Format(_T("%s%s\\%s.%s"), strDestPath, m_strID, m_strID, g_strGuideBookMdvMgrpTaskPostfix);

	POS pos = GetHeadPosition();
	CTestTask *pTask = NULL;

	while (pos != NULL)
	{
		pTask = (CTestTask *)GetNext(pos);

		if (pTask->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		pTask->InitProjectByCommCmdManyConfig(strDestPath);
	}
}

void CTestTasks::InitProjectByCommCmdManyConfig(CTestTask *pTestTask)
{
	CString strDestPath = m_strTasksParentPath;
	CString strTasksPath;
	strTasksPath.Format(_T("%s%s\\"), strDestPath, m_strID);
	pTestTask->InitProjectByCommCmdManyConfig(strTasksPath);
}

void CTestTasks::ReportSNGenClear()
{
	CExBaseList listTask;
	CExBaseList listProject;

	SelectAllTestTask(listTask);

	POS pos = listTask.GetHeadPosition();
	CTestTask *pTask = NULL;

	while (pos != NULL)
	{
		pTask = (CTestTask *)listTask.GetNext(pos);

		if (pTask->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		pTask->SelectAllTestProject(listProject);
		//pTask->EmptyDeviceAttr();  //2021-1-4   lijunqing
		pTask->m_strReportSN.Empty();
		pTask->m_strID = pTask->m_strName;
		pTask->m_strTestState.Empty();
	}

	listTask.RemoveAll();

	pos = listProject.GetHeadPosition();
	CTestProject *pProject = NULL;

	while (pos != NULL)
	{
		pProject = (CTestProject *)listProject.GetNext(pos);
		pProject->m_strReportSN.Empty();
		pProject->m_strTestState.Empty();
		pProject->m_strTestRsltJdg.Empty();
		pProject->m_strID = pProject->m_strName;
	}

	listProject.RemoveAll();
}

void CTestTasks::ReportSNGen(CDvmDataset *pReportSNGen, const CString &strMacroFileID)
{
	CExBaseList listTask;
	CExBaseList listProject;

	SelectAllTestTask(listTask);

	POS pos = listTask.GetHeadPosition();
	CTestTask *pTask = NULL;

	while (pos != NULL)
	{
		pTask = (CTestTask *)listTask.GetNext(pos);

		if (pTask->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		pTask->SelectAllTestProject(listProject);
	}

	listTask.RemoveAll();

	CReportSNGen oRptSnGen;
	oRptSnGen.ReportSNGen(listProject, pReportSNGen, strMacroFileID);
	
	listProject.RemoveAll();
}

void CTestTasks::TaskReportSNGen(CDvmDataset *pReportSNGen, const CString &strMacroFileID)
{
	CExBaseList listTask;
	CReportSNGen oRptSnGen;

	SelectAllTestTask(listTask);
	oRptSnGen.ReportSNGen(listTask, pReportSNGen, strMacroFileID);

	listTask.RemoveAll();
}

void CTestTasks::InitProjectID()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			((CTestTask*)p)->InitProjectID();
		}
	}
}

void CTestTasks::InitProjectIndex()
{
	long nPrjIndex = 0;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			((CTestTask*)p)->InitProjectIndex(nPrjIndex);
		}
	}
}

CTestProject* CTestTasks::FindProjectByPrjIndex(long nPrjIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CTestProject *pFind = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			pFind = ((CTestTask*)p)->FindProjectByPrjIndex(nPrjIndex);

			if (pFind != NULL)
			{
				return pFind;
			}
		}
	}

	return NULL;
}

void CTestTasks::InitSystemPath()
{
	if (m_strSystemPath.GetLength() > 0)
	{
		return;
	}

	m_strSystemPath = _P_GetInstallPath();
	m_strSystemPath.MakeLower();
}

void CTestTasks::ValidateSystemPath()
{
	if (m_strSystemPath.GetLength() == 0)
	{
		m_strSystemPath = m_strTemplateFile;
		m_strSystemPath.MakeLower();
		long nPos = m_strTemplateFile.Find(_T("e-report"));

		if (nPos > 0)
		{
			m_strSystemPath = m_strTemplateFile.Left(nPos);
		}
		else
		{
			m_strSystemPath.Empty();
			return;
		}
	}

	CString strPath, strTemp;
	strPath = _P_GetInstallPath();
	strPath.MakeLower();
	strTemp = m_strSystemPath;
	strTemp.MakeLower();

	if (strTemp == strPath)
	{
		return;
	}

	CExBaseList listTask;
	SelectAllTestTask(listTask);
	POS pos = listTask.GetHeadPosition();
	CTestTask *pTask = NULL;

	while (pos != NULL)
	{
		pTask = (CTestTask *)listTask.GetNext(pos);
		pTask->ValidateSystemPath(m_strSystemPath, strPath);
	}

	_P_ReplaceSystemPath(m_strSystemPath, strPath, m_strTemplateFile);
	listTask.RemoveAll();
	m_strSystemPath = strPath;

	SaveTasksFile(_T(""));
}

CTestTask* CTestTasks::AddTestTask(CDvmDataset *pDeviceAttrsDefine)
{
	CTestTask *pFind = FindTestTask(pDeviceAttrsDefine);

	if (pFind != NULL)
	{
		return NULL;
	}

	pFind = FindTestTaskByEmptyDeviceAttr();

	if (pFind != NULL)
	{
		return NULL;
	}

	pFind = NewTestTask(pDeviceAttrsDefine);
	pFind->InitDeviceAttrValue(pDeviceAttrsDefine);
	AutoSetExpandDatas(pFind);

	return pFind;
}

CTestTask* CTestTasks::NewTestTask(CDvmDataset *pDeviceAttrsDefine)
{
	CString strDevice = m_strDeviceFile;

	//通讯配置文件，获取配置信息
	CDeviceCmmConfig oDeviceCmmConfig;
	oDeviceCmmConfig.AddConfigMms();

	//多组扩展配置对象
	CDvmData *pMaxID = NULL;//(CDvmData*)m_pExpandDatas->GetTail();

	if (m_pExpandDatas != NULL)
	{
		pMaxID = (CDvmData*)m_pExpandDatas->GetTail();
	}

	CTestTask *pNew = new CTestTask();
	pNew->m_strDeviceFile = strDevice;
	pNew->m_strID = Pp_GetPopCfgDeviceName(_T(""), strDevice, this, FALSE);
	pNew->m_strName = pNew->m_strID;
	pNew->tsk_SetGbxmlFile(m_strTemplateFile);
	pNew->m_strPpEngineProgID = m_strPpEngineProgID;
	pNew->m_strTestType = m_strTestType;
	pNew->InitCommCmdManyConfig(m_pExpandDatas);

	if (pMaxID != NULL)
	{
		pNew->m_strMaxMgrpID = pMaxID->m_strID;
	}

	pNew->InitDeviceAttr(pDeviceAttrsDefine); //装置属性
	pNew->InitDeviceCmmConfig(&oDeviceCmmConfig); //通讯配置

	AddNewChild(pNew);
	InitProjectByCommCmdManyConfig(pNew);

	InsertPpDevicesCmmConfig(&oDeviceCmmConfig);
	InitAllCmdCfgChannels();
	AutoSetExpandDatas(pNew);

	return pNew;
}

void CTestTasks::DeleteTestTask(CTestTask *pTestTask)
{
	Delete(pTestTask);
}

BOOL CTestTasks::HasAllProjectCreated()
{
	CExBaseList listTask;
	SelectAllTestTask(listTask);
	POS pos = listTask.GetHeadPosition();
	CTestTask *pTask = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pTask = (CTestTask *)listTask.GetNext(pos);
		bTrue = pTask->HasAllProjectCreated();

		if (!bTrue)
		{
			break;
		}
	}

	listTask.RemoveAll();

	return bTrue;
}

void CTestTasks::AutoSetExpandDatas(CTestTask *pTestTask)
{
	ASSERT (m_pExpandDatasAutoSet != NULL);

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
			InitProjectByCommCmdManyConfig(pTestTask);
		}
	}
}

#ifndef GUIDEBOOK_DEV_MODE

void CTestTasks::InsertPpDevicesCmmConfig(CDeviceCmmConfig *pCmmConfig)
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

void CTestTasks::InsertPpDevicesCmmConfig_Serial(CCmmSerialConfig *pCmmConfig)
{
	ASSERT (m_pTestGlobalDefine != NULL);
	CDeviceCmmConfig *pTestDefine = (CDeviceCmmConfig*)m_pTestGlobalDefine->FindByID(DSID_CommConfig_Serial);

	InsertPpDevicesCmmConfig_Serial(pTestDefine);
// 	if (pTestDefine == NULL)
// 	{
// 		return;
// 	}
// 
// 	CTestTask *pTestTask = NULL;
// 	CCmmSerialConfig *pCurrCmmCfg = NULL, *pFind = NULL;
// 	CDeviceCmmConfig *pDeviceCmmConfig = NULL;
// 	long nIndex = 0;
// 	CExBaseList listTask;
// 	SelectAllTestTask(listTask);
// 	POS pos = listTask.GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pTestTask = (CTestTask *)listTask.GetNext(pos);
// 		pDeviceCmmConfig = pTestTask->GetDeviceCmmConfig();
// 		pCurrCmmCfg = pDeviceCmmConfig->GetConfigSerial();
// 
// 		if (pCurrCmmCfg != NULL)
// 		{
// 			pFind = (CCmmSerialConfig *)pTestDefine->GetAtIndex(nIndex);
// 
// 			if (pFind != NULL)
// 			{
// 				pCurrCmmCfg->m_nPortNum = pFind->m_nPortNum;
// 			}
// 		}
// 
// 		nIndex++;
// 	}
// 
// 	listTask.RemoveAll();
}

void CTestTasks::InsertPpDevicesCmmConfig_Net(CCmmNetConfig *pCmmConfig)
{
	ASSERT (m_pTestGlobalDefine != NULL);
	CDeviceCmmConfig *pTestDefine = (CDeviceCmmConfig*)m_pTestGlobalDefine->FindByID(DSID_CommConfig_Net);

	InsertPpDevicesCmmConfig_Net(pTestDefine);
}

void CTestTasks::InsertPpDevicesCmmConfig_Mms(CCmmMmsConfig *pCmmConfig)
{
	ASSERT (m_pTestGlobalDefine != NULL);
	CDeviceCmmConfig *pTestDefine = (CDeviceCmmConfig*)m_pTestGlobalDefine->FindByID(DSID_CommConfig_Mms);

	InsertPpDevicesCmmConfig_Mms(pTestDefine);
// 	if (pTestDefine == NULL)
// 	{
// 		return;
// 	}
// 
// 	CTestTask *pTestTask = NULL;
// 	CCmmMmsConfig *pCurrCmmCfg = NULL, *pFind = NULL;
// 	CDeviceCmmConfig *pDeviceCmmConfig = NULL;
// 	long nIndex = 0;
// 	CExBaseList listTask;
// 	SelectAllTestTask(listTask);
// 	POS pos = listTask.GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pTestTask = (CTestTask *)listTask.GetNext(pos);
// 		pDeviceCmmConfig = pTestTask->GetDeviceCmmConfig();
// 		pCurrCmmCfg = pDeviceCmmConfig->GetConfigMms();
// 
// 		if (pCurrCmmCfg != NULL)
// 		{
// 			pFind = (CCmmMmsConfig *)pTestDefine->GetAtIndex(nIndex);
// 
// 			if (pFind != NULL)
// 			{
// 				pFind->CopyOwn(pCurrCmmCfg);
// 				//pCurrCmmCfg->m_strRemoteIP = pFind->m_strRemoteIP;
// 			}
// 		}
// 
// 		nIndex++;
// 	}
// 
// 	listTask.RemoveAll();
}


void CTestTasks::InsertPpDevicesCmmConfig_Serial(CDeviceCmmConfig *pTestDefine)
{
	if (pTestDefine == NULL)
	{
		return;
	}

	CTestTask *pTestTask = NULL;
	CCmmSerialConfig *pCurrCmmCfg = NULL, *pFind = NULL;
	CDeviceCmmConfig *pDeviceCmmConfig = NULL;
	long nIndex = 0;
	CExBaseList listTask;
	SelectAllTestTask(listTask);
	POS pos = listTask.GetHeadPosition();

	while (pos != NULL)
	{
		pTestTask = (CTestTask *)listTask.GetNext(pos);
		pDeviceCmmConfig = pTestTask->GetDeviceCmmConfig();
		pCurrCmmCfg = pDeviceCmmConfig->GetConfigSerial();

		if (pCurrCmmCfg != NULL)
		{
			pFind = (CCmmSerialConfig *)pTestDefine->GetAtIndex(nIndex);

			if (pFind != NULL)
			{
				pFind->Copy(pCurrCmmCfg);
// 				pCurrCmmCfg->m_nPortNum = pFind->m_nPortNum;
// 				pCurrCmmCfg->m_nPortNum = pFind->m_nPortNum;
// 				pCurrCmmCfg->m_nBaudRate = pFind->m_nBaudRate;
// 				pCurrCmmCfg->m_nDataBit = pFind->m_nDataBit;
// 				pCurrCmmCfg->m_nParity = pFind->m_nParity;
			}
		}

		nIndex++;
	}

	listTask.RemoveAll();
}

void CTestTasks::InsertPpDevicesCmmConfig_Net(CDeviceCmmConfig *pTestDefine)
{
	if (pTestDefine == NULL)
	{
		return;
	}

	CTestTask *pTestTask = NULL;
	CCmmNetConfig *pCurrCmmCfg = NULL, *pFind = NULL;
	CDeviceCmmConfig *pDeviceCmmConfig = NULL;
	long nIndex = 0;
	CExBaseList listTask;
	SelectAllTestTask(listTask);
	POS pos = listTask.GetHeadPosition();

	while (pos != NULL)
	{
		pTestTask = (CTestTask *)listTask.GetNext(pos);
		pDeviceCmmConfig = pTestTask->GetDeviceCmmConfig();
		pCurrCmmCfg = pDeviceCmmConfig->GetConfigNet();

		if (pCurrCmmCfg != NULL)
		{
			pCurrCmmCfg->DeleteAll();
			pFind = (CCmmNetConfig *)pTestDefine->GetAtIndex(nIndex);

			if (pFind != NULL)
			{
				pFind->Copy(pCurrCmmCfg);
			}
		}

		nIndex++;
	}

	listTask.RemoveAll();
}

void CTestTasks::InsertPpDevicesCmmConfig_Mms(CDeviceCmmConfig *pTestDefine)
{
	if (pTestDefine == NULL)
	{
		return;
	}

	CTestTask *pTestTask = NULL;
	CCmmMmsConfig *pCurrCmmCfg = NULL, *pFind = NULL;
	CDeviceCmmConfig *pDeviceCmmConfig = NULL;
	long nIndex = 0;
	CExBaseList listTask;
	SelectAllTestTask(listTask);
	POS pos = listTask.GetHeadPosition();

	while (pos != NULL)
	{
		pTestTask = (CTestTask *)listTask.GetNext(pos);
		pDeviceCmmConfig = pTestTask->GetDeviceCmmConfig();
		pCurrCmmCfg = pDeviceCmmConfig->GetConfigMms();

		if (pCurrCmmCfg != NULL)
		{
			pFind = (CCmmMmsConfig *)pTestDefine->GetAtIndex(nIndex);

			if (pFind != NULL)
			{
				pFind->CopyOwn(pCurrCmmCfg);
				//pCurrCmmCfg->m_strRemoteIP = pFind->m_strRemoteIP;
			}
		}

		nIndex++;
	}

	listTask.RemoveAll();
}

#endif


long CTestTasks::SelectAllDeviceAttrs(CExBaseList &listDvmAttrs)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	CTestTask *pTask = NULL;
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == CLASSID_TESTTASK)
		{
			pTask = (CTestTask *)p;
			pDataset = pTask->GetDeviceAttr(FALSE);

			if (pDataset != NULL)
			{
				if (listDvmAttrs.FindByID(pTask->m_strID) == NULL)
				{
					listDvmAttrs.AddTail(pDataset);
				}
			}
		}
	}

	return listDvmAttrs.GetCount();
}

#ifndef _not_use_autotest_
CString CTestTasks::ExportWordReport_Summary(MSWord::_Application &WordApp)
{
	if ( WordApp == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_CreatWordFail/*_T("创建Word失败！导出任务报告失败！")*/);
		return _T("");
	}

	CExBaseList listTestTasks;
	SelectAllTestTask(listTestTasks);
	long nRows = listTestTasks.GetCount() + 1;
	long nCols = 2 + m_pDeviceAttrsDefine->GetCount();

	MSWord::Documents docs =  WordApp.GetDocuments();
	MSWord::_Document oDoc = NULL;
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);
	COleVariant Password(_T(""));
	COleVariant WritePassword(_T(""));
	CString strRptTmplFile;
	strRptTmplFile = m_strTasksFile;
	strRptTmplFile = ChangeFilePostfix(strRptTmplFile, _T("doc"));
	strRptTmplFile = strRptTmplFile.Left(strRptTmplFile.GetLength() - 4);
	strRptTmplFile += _T("_Summary.doc");

	COleVariant TmplFile(_T(""));
	POS pos = GetHeadPosition();
	long nRow = 0;
	COleVariant vwdWord9TableBehavior((LONG)MSWord::wdWord9TableBehavior);
	COleVariant vwdAutoFitFixed((LONG)MSWord::wdAutoFitFixed);
	COleVariant vwdPreferredWidthPoints((LONG)MSWord::wdPreferredWidthPoints);

	try
	{
		oDoc = docs.Add(&TmplFile,&covFalse,&FileFormat,&covTrue);
		MSWord::Selection oSelection = WordApp.GetSelection();
		oSelection.TypeParagraph();
		oSelection.TypeParagraph();

		MSWord::Tables oTables = oDoc.GetTables();
		MSWord::Range oRange = oSelection.GetRange();
		MSWord::Table  oTable  = oTables.Add(oRange, nRows, nCols, vwdWord9TableBehavior, vwdAutoFitFixed);
		MSWord::Columns oCols = oTable.GetColumns();

		//编号
		MSWord::Column oCol = oCols.Item(1);
		oCol.SetPreferredWidthType(MSWord::wdPreferredWidthPercent);
		oCol.SetPreferredWidth(0.20);

		//装置序列号
		oCol = oCols.Item(2);
		oCol.SetPreferredWidthType(MSWord::wdPreferredWidthPoints);
		oCol.SetPreferredWidth(0.50);

		//二维码
		POS pos = m_pDeviceAttrsDefine->GetHeadPosition();
		CDvmData *pData = NULL;
		long nCol = 3;

		while (pos != NULL)
		{
			pData = (CDvmData *)m_pDeviceAttrsDefine->GetNext(pos);
			oCol = oCols.Item(nCol);
			oCol.SetPreferredWidthType(MSWord::wdPreferredWidthPoints);
			oCol.SetPreferredWidth(0.30);
			nCol++;
		}

		MSWord::Rows oRows = oTable.GetRows();
		MSWord::Row  oRow;
		MSWord::Cells oCells;
		MSWord::Cell oCell = NULL;
		CString strText;
		nRow = 1;

		oRow = oRows.Item(nRow);
		oCells = oRow.GetCells();
		oCell = oCells.Item(1);
		oCell.Select();
		oSelection.SetText(g_sLangTxt_Index/*_T("编号")*/);
		oCell = oCells.Item(2);
		oCell.Select();
		oSelection.SetText(_T("序列号"));
		
		pos = m_pDeviceAttrsDefine->GetHeadPosition();
		nCol = 3;

		while (pos != NULL)
		{
			pData = (CDvmData *)m_pDeviceAttrsDefine->GetNext(pos);
			oCell = oCells.Item(nCol);
			oCell.Select();
			oSelection.SetText(pData->m_strName);
			nCol++;
		}

		nRow = 2;
		pos = listTestTasks.GetHeadPosition();
		long nTaskIndex = 0;

		while (pos != NULL)
		{
			nTaskIndex++;
			CTestTask *pTestTask = (CTestTask*)listTestTasks.GetNext(pos);

			if (!pTestTask->IsTestEligible())
			{
				continue;
			}

			oRow = oRows.Item(nRow);
			oCells = oRow.GetCells();
			oCell = oCells.Item(1);
			strText.Format(_T("%d"), nTaskIndex);
			oCell.Select();
			oSelection.SetText(strText);

			//装置序列号
			oCell = oCells.Item(2);
			oCell.Select();
			oSelection.SetText(pTestTask->m_strID);
			
			//二维码
			nCol = 3;
			CDvmDataset *pDeviceAttr = pTestTask->GetDeviceAttr();
			if (pDeviceAttr == NULL)	continue;

			POS posAttr = pDeviceAttr->GetHeadPosition();

			while (posAttr != NULL)
			{
				pData = (CDvmData*)pDeviceAttr->GetNext(posAttr);
				oCell = oCells.Item(nCol);
				oCell.Select();
				oSelection.SetText(pData->m_strValue);
			}

			nRow++;
		}
	}
	catch (...)
	{
	}

	try
	{
		TmplFile = strRptTmplFile;
		oDoc.SaveAs(TmplFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
		oDoc.Close(covFalse,covOptional,covOptional);
	}
	catch (...)
	{
	}

	oDoc = NULL;
	docs = NULL;

	listTestTasks.RemoveAll();

	return strRptTmplFile;
}

CString CTestTasks::ExportWordReport_Summary(WPS::_Application &WPSApp)
{
	if ( WPSApp == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_CreatWordFail/*_T("创建Word失败！导出任务报告失败！")*/);
		return _T("");
	}

	CExBaseList listTestTasks;
	SelectAllTestTask(listTestTasks);
	long nRows = listTestTasks.GetCount() + 1;
	long nCols = 2 + m_pDeviceAttrsDefine->GetCount();

	WPS::Documents docs =  WPSApp.get_Documents();
	WPS::_Document oDoc = NULL;
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);
	COleVariant Password(_T(""));
	COleVariant WritePassword(_T(""));
	CString strRptTmplFile;
	strRptTmplFile = m_strTasksFile;
	strRptTmplFile = ChangeFilePostfix(strRptTmplFile, _T("doc"));
	strRptTmplFile = strRptTmplFile.Left(strRptTmplFile.GetLength() - 4);
	strRptTmplFile += _T("_Summary.doc");

	COleVariant TmplFile(_T(""));
	POS pos = GetHeadPosition();
	long nRow = 0;
	COleVariant vwpsWord9TableBehavior((LONG)WPS::wpsWord9TableBehavior);
	COleVariant vwpsAutoFitFixed((LONG)WPS::wpsAutoFitFixed);
	COleVariant vwpsPreferredWidthPoints((LONG)WPS::wpsPreferredWidthPoints);

	try
	{
		oDoc = docs.Add(&TmplFile,&covFalse,&FileFormat,&covTrue);
		WPS::Selection oSelection = WPSApp.get_Selection();
		oSelection.TypeParagraph();
		oSelection.TypeParagraph();

		WPS::Tables oTables = oDoc.get_Tables();
		WPS::Range oRange = oSelection.get_Range();
		WPS::Table  oTable  = oTables.Add(oRange, nRows, nCols, vwpsWord9TableBehavior, vwpsAutoFitFixed);
		WPS::Columns oCols = oTable.get_Columns();

		//编号
		WPS::Column oCol = oCols.Item(1);
		oCol.put_PreferredWidthType(WPS::wpsPreferredWidthPercent);
		oCol.put_PreferredWidth(0.20);

		//装置序列号
		oCol = oCols.Item(2);
		oCol.put_PreferredWidthType(MSWord::wdPreferredWidthPoints);
		oCol.put_PreferredWidth(0.50);

		//二维码
		POS pos = m_pDeviceAttrsDefine->GetHeadPosition();
		CDvmData *pData = NULL;
		long nCol = 3;

		while (pos != NULL)
		{
			pData = (CDvmData *)m_pDeviceAttrsDefine->GetNext(pos);
			oCol = oCols.Item(nCol);
			oCol.put_PreferredWidthType(WPS::wpsPreferredWidthPoints);
			oCol.put_PreferredWidth(0.30);
			nCol++;
		}

		WPS::Rows oRows = oTable.get_Rows();
		WPS::Row  oRow;
		WPS::Cells oCells;
		WPS::Cell oCell = NULL;
		CString strText;
		nRow = 1;

		oRow = oRows.Item(nRow);
		oCells = oRow.get_Cells();
		oCell = oCells.Item(1);
		oCell.Select();
		oSelection.put_Text(g_sLangTxt_Index/*_T("编号")*/);
		oCell = oCells.Item(2);
		oCell.Select();
		oSelection.put_Text(_T("序列号"));

		pos = m_pDeviceAttrsDefine->GetHeadPosition();
		nCol = 3;

		while (pos != NULL)
		{
			pData = (CDvmData *)m_pDeviceAttrsDefine->GetNext(pos);
			oCell = oCells.Item(nCol);
			oCell.Select();
			oSelection.put_Text(pData->m_strName);
			nCol++;
		}

		nRow = 2;
		pos = listTestTasks.GetHeadPosition();
		long nTaskIndex = 0;

		while (pos != NULL)
		{
			nTaskIndex++;
			CTestTask *pTestTask = (CTestTask*)listTestTasks.GetNext(pos);

			if (!pTestTask->IsTestEligible())
			{
				continue;
			}

			oRow = oRows.Item(nRow);
			oCells = oRow.get_Cells();
			oCell = oCells.Item(1);
			strText.Format(_T("%d"), nTaskIndex);
			oCell.Select();
			oSelection.put_Text(strText);

			//装置序列号
			oCell = oCells.Item(2);
			oCell.Select();
			oSelection.put_Text(pTestTask->m_strID);

			//二维码
			nCol = 3;
			CDvmDataset *pDeviceAttr = pTestTask->GetDeviceAttr();
			if (pDeviceAttr == NULL)	continue;

			POS posAttr = pDeviceAttr->GetHeadPosition();

			while (posAttr != NULL)
			{
				pData = (CDvmData*)pDeviceAttr->GetNext(posAttr);
				oCell = oCells.Item(nCol);
				oCell.Select();
				oSelection.put_Text(pData->m_strValue);
			}

			nRow++;
		}
	}
	catch (...)
	{
	}

	try
	{
		TmplFile = strRptTmplFile;
//		oDoc.SaveAs(TmplFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
		oDoc.SaveAs(TmplFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
		oDoc.Close(covFalse,covOptional,covOptional);
	}
	catch (...)
	{
	}

	oDoc = NULL;
	docs = NULL;

	listTestTasks.RemoveAll();

	return strRptTmplFile;
}
#endif

CString CTestTasks::tsk_GetGbxmlFile(BOOL bFullPath)
{
	return tskapi_GetGbxmlFile(m_strTemplateFile, bFullPath);
}

void CTestTasks::tsk_SetGbxmlFile(const CString &strFile)
{
	tskapi_SetGbxmlFile(strFile, m_strTemplateFile);
}

CString CTestTasks::tsk_GetPpxmlFile(BOOL bFullPath)
{
	return tskapi_GetPpxmlFile(m_strPpTemplateFile, bFullPath);
}

void CTestTasks::tsk_SetPpxmlFile(const CString &strFile, BOOL bUpdateAllTasks)
{
	tskapi_SetPpxmlFile(strFile, m_strPpTemplateFile);

	//2021-3-14  lijunqing
	if (!bUpdateAllTasks)
	{
		return;
	}

	CTestTask *pTestTask = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		pTestTask = (CTestTask *)p;
		pTestTask->tsk_SetPpxmlFile(m_strPpTemplateFile, TRUE);
	}
}

CString CTestTasks::tsk_GetDvmFile()
{
	return m_strDeviceFile;
}

void CTestTasks::tsk_SetDvmFile(const CString &strFile, BOOL bUpdateAllTasks)
{
	m_strDeviceFile = strFile;

	//2021-3-14  lijunqing
	if (!bUpdateAllTasks)
	{
		return;
	}

	CTestTask *pTestTask = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		pTestTask = (CTestTask *)p;
		pTestTask->SetDeviceFile(strFile);
	}
}

CString CTestTasks::tsk_GetLocation()
{
	return _T("");
}

void CTestTasks::GetByDvmObj(CDvmDataset *pDvmDataset)
{
	CDvmData *pData = NULL;
	pDvmDataset->m_strName = m_strTasksFile;
	pDvmDataset->m_strID = m_strTasksFile;
	pDvmDataset->m_strDataType = m_strTasksPath;
	CTestTask *pTestTask = NULL;
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CTestTasks::GetByDvmObj --- %s"), m_strTasksFile);

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		pTestTask = (CTestTask *)p;
		pData = new CDvmData();
		pDvmDataset->AddNewChild(pData);
		pTestTask->GetByDvmObj(pData);
	}
}

//2019-4-28  lijunqing  调试四方多装置、项目组每台装置独立执行
// void CTestTasks::Debug_AddTaskBinBoutOffset(long nBinffset, long nBoutOffset)
// {
// 	CTestTask *pTestTask = NULL;
// 
// 	POS pos = GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	long nBinffsetCurr = 0;
// 	long nBoutOffsetCurr = 0;
// 
// 	while (pos != NULL)
// 	{
// 		p = GetNext(pos);
// 
// 		if (p->GetClassID() != CLASSID_TESTTASK)
// 		{
// 			continue;
// 		}
// 
// 		pTestTask = (CTestTask *)p;
// 		pTestTask->Debug_AddTaskBinBoutOffset(nBinffsetCurr, nBoutOffsetCurr);
// 		nBinffsetCurr += nBinffset;
// 		nBoutOffsetCurr += nBoutOffset;
// 	}
// }

void CTestTasks::SetRptViewByMrpt()
{
	if (m_dwAtsRptType == REPORTFILL_INDEX_WPS
		|| m_dwAtsRptType == REPORTFILL_INDEX_WORD)
	{
		if (CTCtrlCntrConfig::IsEnableViewWordForMrpt())
		{
			CExBaseList listProjects;
			SelectAllTestProject(listProjects);
			CTCtrlCntrConfig::SetRptViewByMrpt(listProjects.GetCount());
			listProjects.RemoveAll();
		
			return;
		}
	}

	ats_SetReportFillProgID(m_dwAtsRptType);
}


void CTestTasks::SetRptViewByMrpt(DWORD dwRptType)
{
	m_dwAtsRptType = dwRptType;

	if (m_dwAtsRptType == REPORTFILL_INDEX_WPS
		|| m_dwAtsRptType == REPORTFILL_INDEX_WORD)
	{
		if (CTCtrlCntrConfig::IsEnableViewWordForMrpt())
		{
			CExBaseList listProjects;
			SelectAllTestProject(listProjects);
			CTCtrlCntrConfig::SetRptViewByMrpt(listProjects.GetCount());
			listProjects.RemoveAll();

			return;
		}
	}

	ats_SetReportFillProgID(m_dwAtsRptType);
}

void CTestTasks::SetTestState(const CString &strState)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		((CTestTask*)p)->SetTestState(strState);
	}
}

//2021-10-01  lijunqing
void CTestTasks::SetEngineProgID(const CString &strEngineProgID)
{
	m_strPpEngineProgID = strEngineProgID;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		((CTestTask*)p)->SetEngineProgID(strEngineProgID);
	}
}

//shaolei 2023-11-2
void CTestTasks::SetEngineMode(const CString &strEngineMode)
{
	m_strEngineMode = strEngineMode;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != CLASSID_TESTTASK)
		{
			continue;
		}

		((CTestTask*)p)->SetEngineMode(strEngineMode);
	}
}