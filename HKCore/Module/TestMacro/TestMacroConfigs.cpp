//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroConfigs.cpp  CTestMacroConfigs


#include "stdafx.h"
#include "TestMacroConfigs.h"


long CTestMacroConfigs::g_nTestMacroConfigsRef = 0;
CTestMacroConfigs* CTestMacroConfigs::g_pTestMacroConfigs = NULL;

CString CTestMacroConfigs::g_strDefaultMacroTestEngineProgID = _T("PonovoVm.TestEngine");
CString CTestMacroConfigs::g_strDefaultIecConfigFile = _T("ixml");

CTestMacroConfigs* CTestMacroConfigs::Create()
{
	g_nTestMacroConfigsRef++;

	if (g_nTestMacroConfigsRef == 1)
	{
		g_pTestMacroConfigs = new CTestMacroConfigs(); 
	}

	return g_pTestMacroConfigs;
}

void CTestMacroConfigs::Release()
{
	g_nTestMacroConfigsRef--;

	if (g_nTestMacroConfigsRef == 0)
	{
		delete g_pTestMacroConfigs;
		g_pTestMacroConfigs = NULL;
	}
}

CTestMacroConfigs::CTestMacroConfigs()
{
	//初始化属性

	//初始化成员变量

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("MacroTestsConfig.xml");

	OpenXmlFile(strFile, CTestMacroXmlRWKeys::CTestMacroConfigsKey(), CTestMacroXmlRWKeys::g_pXmlKeys);

	m_pActiveMacroTest = (CTestMacroConfig *)FindByID(m_strActiveMacroTest);

	if (m_pActiveMacroTest == NULL)
	{
		m_pActiveMacroTest = (CTestMacroConfig *)GetHead();
	}
}

CTestMacroConfigs::~CTestMacroConfigs()
{
}

long CTestMacroConfigs::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strActiveMacroTestKey, oNode, m_strActiveMacroTest);
	return 0;
}

long CTestMacroConfigs::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strActiveMacroTestKey, oElement, m_strActiveMacroTest);
	return 0;
}

CBaseObject* CTestMacroConfigs::Clone()
{
	CTestMacroConfigs *p = new CTestMacroConfigs();
	Copy(p);
	return p;
}

CExBaseObject* CTestMacroConfigs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTestMacroConfigKey)
	{
		pNew = new CTestMacroConfig();
	}

	return pNew;
}

CExBaseObject* CTestMacroConfigs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TMCLASSID_CTESTMACROCONFIG)
	{
		pNew = new CTestMacroConfig();
	}

	return pNew;
}
BOOL CTestMacroConfigs::CanPaste(UINT nClassID)
{
	if (nClassID == TMCLASSID_CTESTMACROCONFIG)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CTestMacroConfigs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTestMacroConfigs *p = (CTestMacroConfigs*)pObj;

	if(m_strActiveMacroTest != p->m_strActiveMacroTest)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTestMacroConfigs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTestMacroConfigs *p = (CTestMacroConfigs*)pDest;

	p->m_strActiveMacroTest = m_strActiveMacroTest;
	return TRUE;
}

CTestMacroConfig* CTestMacroConfigs::FindByIecFile(const CString &strFile)
{
	POS pos = GetHeadPosition();
	CTestMacroConfig *p = NULL;
	CTestMacroConfig *pFind = NULL;

	while (pos != NULL)
	{
		p = (CTestMacroConfig *)GetNext(pos);

		if (p->m_strIecConfigFile == strFile)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CString CTestMacroConfigs::GetActiveMcroTestEngineProgID()
{
	ASSERT (g_pTestMacroConfigs != NULL);

	if (g_pTestMacroConfigs == NULL)
	{
		return g_strDefaultMacroTestEngineProgID;
	}

	if (g_pTestMacroConfigs->m_pActiveMacroTest == NULL)
	{
		return g_strDefaultMacroTestEngineProgID;
	}

	if (g_pTestMacroConfigs->m_pActiveMacroTest->m_strID.GetLength() <= 3)
	{
		return g_strDefaultMacroTestEngineProgID;
	}

	return g_pTestMacroConfigs->m_pActiveMacroTest->m_strID;
}

CString CTestMacroConfigs::GetAcriveMacroIecFile()
{
	ASSERT (g_pTestMacroConfigs != NULL);

	if (g_pTestMacroConfigs == NULL)
	{
		return g_strDefaultIecConfigFile;
	}

	if (g_pTestMacroConfigs->m_pActiveMacroTest == NULL)
	{
		return g_strDefaultIecConfigFile;
	}

	if (g_pTestMacroConfigs->m_pActiveMacroTest->m_strIecConfigFile.GetLength() <= 1)
	{
		return g_strDefaultIecConfigFile;
	}

	return g_pTestMacroConfigs->m_pActiveMacroTest->m_strIecConfigFile;
}

