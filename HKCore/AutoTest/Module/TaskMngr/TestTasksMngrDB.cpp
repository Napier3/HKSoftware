#include "StdAfx.h"
#include "TestTasksMngrDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CTestTasksMngrGroup
CTestTasksMngrGroup::CTestTasksMngrGroup()
{

}

CTestTasksMngrGroup::~CTestTasksMngrGroup()
{
	
}

void CTestTasksMngrGroup::Init()
{
	
}

void CTestTasksMngrGroup::InitAfterRead()
{
	
}

long CTestTasksMngrGroup::IsEqual(CExBaseObject* pObj)
{

	return 0;
}

long CTestTasksMngrGroup::Copy(CExBaseObject* pDesObj)
{

	return 0;
}

CExBaseObject* CTestTasksMngrGroup::Clone()
{
	CTestTasksMngrGroup* pNew = new CTestTasksMngrGroup;
	Copy(pNew);

	return pNew;
}

CExBaseObject* CTestTasksMngrGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrsKey)
	{
		CTestTasksMngr* pNew = new CTestTasksMngr;
		return pNew;
	}

	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrsGroupKey)
	{
		CTestTasksMngrGroup* pNew = new CTestTasksMngrGroup;
		return pNew;
	}

	return NULL;
}

CExBaseObject* CTestTasksMngrGroup::CreateNewChild(long nClassID)
{
	return NULL;
}


long CTestTasksMngrGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	//xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);

	return 0;
}

long CTestTasksMngrGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	//xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);

	return 0;
}

long CTestTasksMngrGroup::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (pObj->GetClassID() == CLASSID_TESTTASKMNGRS)
		{
			CTestTasksMngr *pMngr = (CTestTasksMngr*)pObj;
			pMngr->m_bXmlWriteChildren = FALSE;
			pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
			pMngr->m_bXmlWriteChildren = TRUE;
		}
		else
		{
			pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
		}
	}

	return 0;
}

CTestTasksMngr* CTestTasksMngrGroup::AddTaskMngrsFile(const CString &strFile)
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	CString strID = ParseFileName(strFile);
	CString strType = ParseFilePostfix(strFile);
	CString strName = strID;

	strID.MakeLower();
	strType.MakeLower();

	CTestTasksMngr *pTestTasksMngr = (CTestTasksMngr*)FindByID(strID);

	if (pTestTasksMngr != NULL)
	{
		return pTestTasksMngr;
	}

	pTestTasksMngr = new CTestTasksMngr();
	pTestTasksMngr->m_strName = strName;
	pTestTasksMngr->m_strID = strName;
	AddNewChild(pTestTasksMngr);

	if (strType == _T("xls") || strType == _T("xlsx"))
	{
		CTestTasksMngrExcelTool oExcelTool;
		oExcelTool.ImportFromExcel(pTestTasksMngr, strFile);
		pTestTasksMngr->InitAfterRead();
		CString strTasksMngrFile = strFile;
		strTasksMngrFile = ChangeFilePostfix(strTasksMngrFile, _T("xml"));
		pTestTasksMngr->m_strName = ParseFileName(strTasksMngrFile);
		pTestTasksMngr->m_strID = pTestTasksMngr->m_strName;
		pTestTasksMngr->SaveTasksFile();
	}
	else if (strType == _T("xml"))
	{
		pTestTasksMngr->OpenTaskMngrsFile(strFile);
	}

	return pTestTasksMngr;
}
// 
// BOOL CTestTasksMngrDB::In_SaveTasksFile(const CString &strFile)
// {
// 	if (strFile.GetLength() > 0)
// 	{
// 		m_strTasksMngrDBFile = strFile;
// 		return SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
// 	}
// 	else
// 	{
// 		return SaveXmlFile(m_strTasksMngrDBFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
// 	}
// }

//////////////////////////////////////////////////////////////////////////
//CTestTasksMngrDB
CTestTasksMngrDB* CTestTasksMngrDB::g_pTestTasksMngrDB = NULL;
long CTestTasksMngrDB::g_nTestTasksMngrDBRef = 0;


CTestTasksMngrDB::CTestTasksMngrDB()
{
	m_strName = _T("测试任务管理数据库");
	m_strID = _T("TestTasksMngrDB");
	m_pActiveTasksMngr = NULL;
}

CTestTasksMngrDB::~CTestTasksMngrDB()
{

}

CTestTasksMngrDB* CTestTasksMngrDB::Create()
{
	g_nTestTasksMngrDBRef++;

	if (g_nTestTasksMngrDBRef == 1)
	{
		g_pTestTasksMngrDB = new CTestTasksMngrDB();
		g_pTestTasksMngrDB->OpenDBFile();
	}

	return g_pTestTasksMngrDB;
}

void CTestTasksMngrDB::Release()
{
	g_nTestTasksMngrDBRef--;

	if (g_nTestTasksMngrDBRef == 0)
	{
		delete g_pTestTasksMngrDB;
		g_pTestTasksMngrDB = NULL;
	}

}

CTestTasksMngrDB* CTestTasksMngrDB::GetTestTasksMngrDB()
{
	ASSERT (g_pTestTasksMngrDB != NULL);
	return g_pTestTasksMngrDB;
}

CTestTasksMngr* CTestTasksMngrDB::InsertTaskMngrFile(CTestTasksMngrGroup *pGroup, const CString &strFile)
{
	ASSERT (g_pTestTasksMngrDB != NULL);
	CTestTasksMngr *pNew = pGroup->AddTaskMngrsFile(strFile);
	g_pTestTasksMngrDB->SaveDBFile();

	return pNew;
}

CTestTasksMngr* CTestTasksMngrDB::GetActiveTasksMngr()
{
	if (g_pTestTasksMngrDB->m_pActiveTasksMngr != NULL)
	{
		return g_pTestTasksMngrDB->m_pActiveTasksMngr;
	}

	g_pTestTasksMngrDB->InitAfterRead();

	return g_pTestTasksMngrDB->m_pActiveTasksMngr;
}

CString CTestTasksMngrDB::GetActiveTasksMngrID()
{
	return g_pTestTasksMngrDB->m_strActiveTasksMngr;
}

void CTestTasksMngrDB::SetActiveTasksMngr(CTestTasksMngr *pTasksMngr)
{
	g_pTestTasksMngrDB->m_pActiveTasksMngr = pTasksMngr;
	g_pTestTasksMngrDB->m_strActiveTasksMngr = pTasksMngr->GetIDPathEx(CLASSID_TESTTASKMNGRSDB, FALSE, _T("\\"));

	g_pTestTasksMngrDB->SaveDBFile();
}

void CTestTasksMngrDB::DeleteTasksMngr(CTestTasksMngr *pTasksMngr)
{
	CExBaseList *pParent = (CExBaseList *)pTasksMngr->GetParent();
	pParent->Delete(pTasksMngr);
	g_pTestTasksMngrDB->SaveDBFile();
}	

void CTestTasksMngrDB::Save()
{
	ASSERT (g_pTestTasksMngrDB != NULL);
	g_pTestTasksMngrDB->SaveDBFile();
}

void CTestTasksMngrDB::Init()
{

}

long CTestTasksMngrDB::IsEqual(CExBaseObject* pObj)
{

	return 0;
}

long CTestTasksMngrDB::Copy(CExBaseObject* pDesObj)
{

	return 0;
}

CExBaseObject* CTestTasksMngrDB::Clone()
{
	CTestTasksMngrDB* pNew = new CTestTasksMngrDB;
	Copy(pNew);

	return pNew;
}

CExBaseObject* CTestTasksMngrDB::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CTestTasksMngrGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);;
}

CExBaseObject* CTestTasksMngrDB::CreateNewChild(long nClassID)
{
	return CTestTasksMngrGroup::CreateNewChild(nClassID);
}


long CTestTasksMngrDB::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CTestTasksMngrGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCurrTaskKey,oNode,m_strActiveTasksMngr);

	return 0;
}

long CTestTasksMngrDB::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCurrTaskKey,oElement,m_strActiveTasksMngr);

	return 0;
}

void CTestTasksMngrDB::InitAfterRead()
{
	if (m_strActiveTasksMngr.GetLength() == 0)
	{
		return;
	}

	CExBaseList listTasksMngr;
	g_pTestTasksMngrDB->Select(g_pTestTasksMngrDB->m_strActiveTasksMngr, listTasksMngr);

	if (listTasksMngr.GetCount() > 0)
	{
		g_pTestTasksMngrDB->m_pActiveTasksMngr = (CTestTasksMngr*)listTasksMngr.GetHead();
		listTasksMngr.RemoveAll();
	}

}

CString CTestTasksMngrDB::GetDBFile()
{
	CString strPath;
	strPath = _P_GetWorkspacePath();
	strPath += _T("TestTaskMngrDB.xml");

	return strPath;
}

void CTestTasksMngrDB::OpenDBFile()
{
	CString strPath;
	strPath = GetDBFile();
	OpenXmlFile(strPath, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
}

void CTestTasksMngrDB::SaveDBFile()
{
	CString strPath;
	strPath = GetDBFile();
	SaveXmlFile(strPath, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
}

