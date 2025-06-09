#include "stdafx.h"
#include "TestTasks.h"
#include "../AutoTestXMLRWKeys.h"

CTestTasks::CTestTasks()
{

}

CTestTasks::~CTestTasks()
{

}

void CTestTasks::Init()
{

}

long CTestTasks::InitAfterSerialize()
{
	return 0;
}

UINT CTestTasks::GetClassID()
{
	return 0;
}

BSTR CTestTasks::GetXmlElementKey()
{
	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrKey;
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

CExBaseObject* CTestTasks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskKey)
	{
		CTestTask* pTestTask = new CTestTask;
		return pTestTask;
	}

	return NULL;
}

CExBaseObject* CTestTasks::CreateNewChild(long nClassID)
{
	return NULL;
}

BOOL CTestTasks::Open()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);
	MSXML2::IXMLDOMDocumentPtr oDoc;

	CString strFile;
	GetTCtrlCntrTaskMngrCfgFile(strFile);
	BOOL bTrue = FALSE;

	if(::xml_OpenFile(oDoc, strFile))
	{
		MSXML2::IXMLDOMNodePtr oDocRoot = oDoc->GetdocumentElement();
		MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode(L"//"+(_bstr_t)CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrKey);
	
		ASSERT(oRoot != NULL);
	
		if(oRoot != NULL)
		{
			XmlRead(oRoot, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);	
			bTrue = TRUE;
		}
	}
	else  
	{
	}

	if (!bTrue)
	{
		Save();
	}

	return bTrue;
}

BOOL CTestTasks::Save()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);
	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	XmlWrite(docPtr,NULL, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	CString strFile;
	GetTCtrlCntrTaskMngrCfgFile(strFile);
	docPtr->save((_bstr_t)strFile);

	return TRUE;
}