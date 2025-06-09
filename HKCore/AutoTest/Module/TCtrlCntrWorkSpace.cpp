#include "stdafx.h"
#include "TCtrlCntrWorkSpace.h"
#include "TCtrlCntrDefine.h"


#ifndef _PSX_QT_LINUX_
#include "TaskMngr/TestTask.h"
#include "TCtrlCntrDefine.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTCtrlCntrWorkSpace* CTCtrlCntrWorkSpace::g_pWorkSpace = NULL;
long CTCtrlCntrWorkSpace::g_nWorkSpaceRef = 0;

CTCtrlCntrWorkSpace::CTCtrlCntrWorkSpace()
{
	//m_pCurrTask = NULL;
	m_dwTkID_Index = 0xFFFFFFFF;

#ifndef _PSX_QT_LINUX_
	//2023-4-2  lijunqing
	m_pSttCommConfigs = NULL;
	m_pSttCommConfig = NULL;
#endif
}


CTCtrlCntrWorkSpace* CTCtrlCntrWorkSpace::Create()
{
	g_nWorkSpaceRef ++;

	if(g_pWorkSpace == NULL)
	{
		g_pWorkSpace = new CTCtrlCntrWorkSpace();
	}

	return g_pWorkSpace;
}

void CTCtrlCntrWorkSpace::Release()
{
	g_nWorkSpaceRef --;

	if(g_nWorkSpaceRef == 0)
	{
		delete g_pWorkSpace;
		g_pWorkSpace = NULL;
	}
}

CTCtrlCntrWorkSpace::~CTCtrlCntrWorkSpace()
{
}

BOOL CTCtrlCntrWorkSpace::Init()
{
	return Open();
}

long CTCtrlCntrWorkSpace::InitAfterSerialize()
{
	return 0;
}

UINT CTCtrlCntrWorkSpace::GetClassID()
{
#ifndef _PSX_QT_LINUX_
    return CLASSID_WORKSPACE;
#else
    return 0;
#endif
}

long CTCtrlCntrWorkSpace::BinarySerializeOwn(CBinarySerialBuffer& oBinaryBuff)
{
	return 0;
}

long CTCtrlCntrWorkSpace::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAutoTestXMLRWKeys* pKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;

	xml_GetElementText(pKeys->m_strAppExitStateKey,oNode,m_strAppExitState);
	xml_GetElementText(pKeys->m_strCurrTestKey,oNode,m_strLastTestFile);
	xml_GetElementText(pKeys->m_strCurrTaskKey,oNode,m_strLastTaskFile);
	xml_GetElementText(pKeys->m_strTestStateKey,oNode,m_strLastTestState);
	xml_GetElementText(pKeys->m_strCurrTestItemIndex,oNode,m_nCurrTestItemIndex);

	return 0;
}

long CTCtrlCntrWorkSpace::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAutoTestXMLRWKeys* pKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;

	xml_SetElementText(pKeys->m_strAppExitStateKey,oXMLDoc, oElement,m_strAppExitState);
	xml_SetElementText(pKeys->m_strCurrTestKey,oXMLDoc, oElement,m_strLastTestFile);
	xml_SetElementText(pKeys->m_strCurrTaskKey,oXMLDoc, oElement,m_strLastTaskFile);
	xml_SetElementText(pKeys->m_strTestStateKey,oXMLDoc, oElement,m_strLastTestState);
	xml_SetElementText(pKeys->m_strCurrTestItemIndex,oXMLDoc, oElement,m_nCurrTestItemIndex);

	return 0;
}

BSTR CTCtrlCntrWorkSpace::GetXmlElementKey()
{
	ASSERT ( CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);
	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strWorkspaceKeyEx;
}

long CTCtrlCntrWorkSpace::IsEqual(CExBaseObject* pObj)
{
	return 0;
}

long CTCtrlCntrWorkSpace::Copy(CExBaseObject* pDesObj)
{
	return 0;
}

CExBaseObject* CTCtrlCntrWorkSpace::Clone()
{
	return NULL;
}

CExBaseObject* CTCtrlCntrWorkSpace::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	ASSERT ( CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

// 	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskKey)
// 	{
// 		CTestTask* pTask = new CTestTask;
// 		return pTask;
// 	}

	return NULL;
}

CExBaseObject* CTCtrlCntrWorkSpace::CreateNewChild(long nClassID)
{
	return NULL;
}

//根据workspace.xml初始化
long CTCtrlCntrWorkSpace::Open()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);
	CString strFile;
	GetTCtrlCntrWorkspaceCfgFile(strFile);

	return OpenXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
}

//保存workspace修改 xml格式
long CTCtrlCntrWorkSpace::Save()
{
#ifdef _PSX_QT_LINUX_
    return 0;
#endif

	CString strFile;
	GetTCtrlCntrWorkspaceCfgFile(strFile);
	SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return 0;
}
// 
// CTestTask* CTCtrlCntrWorkSpace::FindTaskByLocalID(const CString &strLocalID)
// {	
// 	CTestTask* pTemp = NULL;
// 	CTestTask* pFind = NULL;
// 
// 	POS pos = GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pTemp = (CTestTask*)GetNext(pos);
// 
// 		if (pTemp->m_strLocalID == strLocalID)
// 		{
// 			pFind = pTemp;
// 			break;
// 		}
// 	}
// 
// 	return pFind;
// }

CTCtrlMsgRcvInterface* CTCtrlCntrWorkSpace::FindMsgRcvWndByTestProject(CExBaseObject* pTestProject)
{
#ifndef _PSX_QT_LINUX_
    ASSERT(g_pWorkSpace != NULL);

	CTestControlBase* pFindTestControl = NULL;
	CTestControlBase* pTemp = NULL;
	POS pos = m_oTestControlList.GetHeadPosition();

	while(pos != NULL)
	{
		pTemp = (CTestControlBase*)m_oTestControlList.GetNext(pos);

		//if(pTemp->GetTestProject() == pTestProject)
		{
			pFindTestControl = pTemp;
			break;
		}
	}

	return &pFindTestControl->m_oTCtrlMsgRcv;
#else
    return NULL;
#endif

}

CString CTCtrlCntrWorkSpace::GetLastTestFile()
{
	return m_strLastTestFile;
}

CString CTCtrlCntrWorkSpace::GetLastTaskFile()
{
	return m_strLastTaskFile;
}

CString CTCtrlCntrWorkSpace::GetLastTestState()
{
	return m_strLastTestState;
}

void CTCtrlCntrWorkSpace::SetLastTaskFile(const CString &strTaskFile)
{
	m_strLastTaskFile = strTaskFile;
}

void CTCtrlCntrWorkSpace::SetLastTestFile(const CString &strTestFile)
{
	m_strLastTestFile = strTestFile;
}

void CTCtrlCntrWorkSpace::SetLastTestState(const CString &strTestState)
{
	m_strLastTestState = strTestState;
}

void CTCtrlCntrWorkSpace::SetCurrTestItemIndex(long nCurrTestItemIndex)
{
	m_nCurrTestItemIndex = nCurrTestItemIndex;
}

CString CTCtrlCntrWorkSpace::GetNewGuideBookBinaryFileName()
{
	if (m_strTestID.Find(_T("/")) > 0 || m_strTestID.Find(_T("\\")) > 0)
	{
		return m_strTestID;
	}
	else
	{
	CString strFile;
    strFile.Format(_T("%s%s"), m_strTestFolder.GetString(), m_strTestID.GetString());
    strFile = ChangeFilePostfix(strFile, g_strGuideBookBinaryPostfix);
	return strFile;
	}
}

//////////////////////////////////////////////////////////////////////////

CString CTCtrlCntrWorkSpace::s_GetLastTestFile()
{
	if (g_pWorkSpace == NULL)
	{
		return _T("");
	}

	return g_pWorkSpace->GetLastTestFile();
}

void CTCtrlCntrWorkSpace::s_Save()
{
	if (g_pWorkSpace == NULL)
	{
		return;
	}

	g_pWorkSpace->Save();
}

CString CTCtrlCntrWorkSpace::s_GetLastTaskFile()
{
	if (g_pWorkSpace == NULL)
	{
		return _T("");
	}

	return g_pWorkSpace->GetLastTaskFile();
}

CString CTCtrlCntrWorkSpace::s_GetLastTestState()
{
	if (g_pWorkSpace == NULL)
	{
		return _T("");
	}

	return g_pWorkSpace->GetLastTestState();
}


void CTCtrlCntrWorkSpace::s_SetLastTestFile(const CString &strTestFile)
{
	if (g_pWorkSpace == NULL)
	{
		return;
	}

	g_pWorkSpace->SetLastTestFile(strTestFile);
}

void CTCtrlCntrWorkSpace::s_SetLastTaskFile(const CString &strTaskFile)
{
	if (g_pWorkSpace == NULL)
	{
		return;
	}

	g_pWorkSpace->SetLastTaskFile(strTaskFile);
}

void CTCtrlCntrWorkSpace::s_SetLastTestState(const CString &strTestState)
{
	if (g_pWorkSpace == NULL)
	{
		return ;
	}

	g_pWorkSpace->SetLastTestState(strTestState);
}

CString CTCtrlCntrWorkSpace::s_GetNewGuideBookBinaryFileName()
{
	if (g_pWorkSpace == NULL)
	{
		return _T("");
	}

	return g_pWorkSpace->GetNewGuideBookBinaryFileName();
}

#ifndef _PSX_QT_LINUX_
CPpSttCommConfig* CTCtrlCntrWorkSpace::GetSttCommConfig(BOOL bCreateNew)
{
	return g_pWorkSpace->In_GetSttCommConfig(bCreateNew);
}

CPpSttCommConfigs* CTCtrlCntrWorkSpace::GetSttCommConfigs(BOOL bCreateNew)
{
	return g_pWorkSpace->In_GetSttCommConfigs(bCreateNew);
}

void CTCtrlCntrWorkSpace::SetSttCommConfig(CPpSttCommConfig *p)
{
	return g_pWorkSpace->In_SetSttCommConfig(p);
}

void CTCtrlCntrWorkSpace::SetSttCommConfigs(CPpSttCommConfigs *p)
{
	return g_pWorkSpace->In_SetSttCommConfigs(p);
}

CPpSttCommConfig* CTCtrlCntrWorkSpace::In_GetSttCommConfig(BOOL bCreateNew)
{
	if (m_pSttCommConfig == NULL)
	{
		if (bCreateNew)
		{
			m_pSttCommConfig = new CPpSttCommConfig();
			AddNewChild(m_pSttCommConfig);
		}
	}

	return m_pSttCommConfig;
}

CPpSttCommConfigs* CTCtrlCntrWorkSpace::In_GetSttCommConfigs(BOOL bCreateNew)
{
	if (m_pSttCommConfigs == NULL)
	{
		if (bCreateNew)
		{
			m_pSttCommConfigs = new CPpSttCommConfigs();
			AddNewChild(m_pSttCommConfigs);
		}
	}

	return m_pSttCommConfigs;
}

void CTCtrlCntrWorkSpace::In_SetSttCommConfig(CPpSttCommConfig *p)
{
	CPpSttCommConfig *pCurr = In_GetSttCommConfig(TRUE);

	if (p != NULL)
	{
		pCurr->DeleteAll();
		pCurr->AppendCloneEx(*p);
	}
}

void CTCtrlCntrWorkSpace::In_SetSttCommConfigs(CPpSttCommConfigs *p)
{
	CPpSttCommConfigs *pCurr = In_GetSttCommConfigs(TRUE);

	if (p != NULL)
	{
		pCurr->DeleteAll();
		pCurr->AppendCloneEx(*p);
	}
}
#endif
