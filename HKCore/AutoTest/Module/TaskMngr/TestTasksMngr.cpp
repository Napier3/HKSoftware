#include "StdAfx.h"
#include "TestTasksMngr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CTestTasksMngr
CTestTasksMngr::CTestTasksMngr()
{
	m_bXmlWriteChildren = TRUE;
	m_nVersion = 0;
}

CTestTasksMngr::~CTestTasksMngr()
{
	m_listDeviceAttrs.RemoveAll();
	m_listFinish.RemoveAll();
}

void CTestTasksMngr::Init()
{
	
}

void CTestTasksMngr::InitAfterRead()
{
	m_listDeviceAttrs.RemoveAll();
	m_listFinish.RemoveAll();

	SelectAllDeviceAttrs(m_listFinish, FALSE, TRUE);
	SelectAllDeviceAttrs(m_listDeviceAttrs, TRUE, FALSE);

	if (m_nVersion == 0)
	{
		POS pos = m_listFinish.GetTailPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = m_listFinish.GetPrev(pos);
			
			if (m_listDeviceAttrs.Find(p) == NULL)
			{
				((CDvmDataset*)p)->m_nWriteMode = 2;
				m_listDeviceAttrs.AddHead(p);
			}
		}
	}
}

long CTestTasksMngr::IsEqual(CExBaseObject* pObj)
{

	return 0;
}

long CTestTasksMngr::Copy(CExBaseObject* pDesObj)
{

	return 0;
}

CExBaseObject* CTestTasksMngr::Clone()
{
	CTestTasksMngr* pNew = new CTestTasksMngr;
	Copy(pNew);

	return pNew;
}

CExBaseObject* CTestTasksMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrKey)
	{
		CTestTasks* pTestTasks = new CTestTasks;
		return pTestTasks;
	}

	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCDvmDatasetKey)
	{
		CDvmDataset* pDvmDataset = new CDvmDataset;
		return pDvmDataset;
	}

	return NULL;
}

CExBaseObject* CTestTasksMngr::CreateNewChild(long nClassID)
{
	return NULL;
}


long CTestTasksMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTemplateFileKey,oNode,m_strTestTemplateFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oNode,m_strPpTemplateFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strDeviceModelFileKey,oNode,m_strDeviceFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTasksMngrSrcFileKey,oNode,m_strTasksMngrSrcFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strVersionKey,oNode,m_nVersion);

	return 0;
}

long CTestTasksMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	m_nVersion = 1;

	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTemplateFileKey,oElement,m_strTestTemplateFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oElement,m_strPpTemplateFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strDeviceModelFileKey,oElement,m_strDeviceFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTasksMngrSrcFileKey,oElement,m_strTasksMngrSrcFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strVersionKey,oElement,m_nVersion);

	return 0;
}


long CTestTasksMngr::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (m_bXmlWriteChildren)
	{
		return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}

CString CTestTasksMngr::GetTaskMngrsFile()
{
	CString strPath, strTasksMngrFile;
	CExBaseObject *pParent = (CExBaseObject*)GetParent();

	while (pParent->GetClassID() != CLASSID_TESTTASKMNGRSDB)
	{
		strPath = pParent->m_strID + _T("\\") + strPath;
		pParent = (CExBaseObject *)pParent->GetParent();
	}

	strTasksMngrFile = _P_GetWorkspacePath();
	strTasksMngrFile += strPath;
	strTasksMngrFile.AppendFormat(_T("%s.xml"), m_strID);

	return strTasksMngrFile;
}

BOOL CTestTasksMngr::OpenTaskMngrsFile()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	if (m_strTasksMngrFile.GetLength() > 0)
	{
		return TRUE;
	}

	m_strTasksMngrFile = GetTaskMngrsFile();

	BOOL bTrue = OpenXmlFile(m_strTasksMngrFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrsKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return bTrue;
}

BOOL CTestTasksMngr::OpenTaskMngrsFile(const CString &strFile)
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	BOOL bTrue = FALSE;
	m_strTasksMngrFile = strFile;

	bTrue = OpenXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return bTrue;
}

BOOL CTestTasksMngr::SaveTasksFile()
{
	if (m_strTasksMngrFile.GetLength() <= 5)
	{
		m_strTasksMngrFile = GetTaskMngrsFile();
	}

	return SaveXmlFile(m_strTasksMngrFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
}


BOOL CTestTasksMngr::SaveTasksFile(const CString &strFile)
{
	if (strFile.GetLength() > 0)
	{
		m_strTasksMngrFile = strFile;
		return SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
	}
	else
	{
		return SaveXmlFile(m_strTasksMngrFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
	}
}

long CTestTasksMngr::SelectAllDeviceAttrs(CExBaseList &listDvmAttrs, BOOL bIncludeDataset, BOOL bIncludeTasks)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATASET)
		{
			if (bIncludeDataset)
			{
				listDvmAttrs.AddTail(p);
			}
		}
		else if (nClassID == CLASSID_TESTTASKS)
		{
			if (bIncludeTasks)
			{
				((CTestTasks*)p)->SelectAllDeviceAttrs(listDvmAttrs);
			}
		}
	}

	return listDvmAttrs.GetCount();
}

void CTestTasksMngr::AddToFinish(CDvmDataset *pDeviceAttr)
{
	if (m_listFinish.FindByID(pDeviceAttr->m_strID) == NULL)
	{
		m_listFinish.AddTail(pDeviceAttr);
	}
}

long CTestTasksMngr::GetSelDeviceAttrsCount()
{
	POS pos = m_listDeviceAttrs.GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	long nSelCount = 0;

	while(pos)
	{
		pDataset = (CDvmDataset *)m_listDeviceAttrs.GetNext(pos);

		if (pDataset->m_nIndex == 1)
		{
			nSelCount++;
		}
	}

	return nSelCount;
}