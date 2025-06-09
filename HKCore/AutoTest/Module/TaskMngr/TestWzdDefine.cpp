#include "StdAfx.h"
#include "TestWzdDefine.h"
#include "..\..\..\System\Module\XAtsSysSvrGlobalDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestWzdDefine::CTestWzdDefine(void)
{
	m_pTestApp = NULL;
}

CTestWzdDefine::~CTestWzdDefine(void)
{

}

void CTestWzdDefine::Init()
{
}

void CTestWzdDefine::InitAfterRead()
{
	CTestMacrosFileMngr *pTestMacrosFileMngr = CTestMacrosFileMngr::g_pTestMacrosFileMngr;
	ASSERT (pTestMacrosFileMngr != NULL);

	m_pTestMacrosFile = (CTestMacrosFile *)pTestMacrosFileMngr->FindByID(m_strMacroFile);
	ASSERT( m_pTestMacrosFile != NULL );

	if (m_pTestMacrosFile == NULL)
	{
		return;
	}

	CString strExpandFile;
	strExpandFile = m_pTestMacrosFile->GetTestMacroCfgFile(m_pTestMacrosFile->ExpandConfigFile(FALSE));
	
	BOOL bRet = m_oTestGlobalDefine.OpenXmlFile(strExpandFile, CGbXMLKeys::TestDefineKey(), CGbXMLKeys::g_pGbXMLKeys);

	m_pTestApp = (CDvmDataset *)FindByID(DSID_TESTAPP);

	GetTestApp();

	CString strTestTypeFile;
	strTestTypeFile = m_pTestMacrosFile->GetTestMacroCfgFile(m_pTestMacrosFile->TestTypeFile(FALSE));
	
	m_oTestTypes.Open(strTestTypeFile);
}

CString CTestWzdDefine::GetTemplateFile()
{
	CString strPath;

	if (m_strTemplateFile.GetLength() > 0)
	{
		strPath = _P_GetTemplatePath();
		strPath = strPath + m_strTemplateFile;
	}

	return strPath;
}

CString CTestWzdDefine::GetDeviceFile()
{
	CString strPath;

	if (m_strDeviceFile.GetLength() > 0)
	{
		strPath = _P_GetLibraryPath();
		strPath = strPath + m_strDeviceFile;
	}

	return strPath;
}

CString CTestWzdDefine::GetPpTemplateFile()
{
	CString strPath;

	if (m_strPpTemplateFile.GetLength() > 0)
	{
		strPath = atssys_GetProtocolTemplatePath();
		strPath = strPath + m_strPpTemplateFile;
	}

	return strPath;
}

CDvmDataset* CTestWzdDefine::GetTestApp()
{
	if (m_pTestApp == NULL)
	{
		m_pTestApp = new CDvmDataset();
		m_pTestApp->m_strID = DSID_TESTAPP;
		m_pTestApp->m_strName = DSID_TESTAPP;
		AddNewChild(m_pTestApp);
	}

	return m_pTestApp;
}

CTestTypes* CTestWzdDefine::GetTestTypes()
{
	return &m_oTestTypes;
}

long CTestWzdDefine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CTestWzdDefine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strMacroFileKey,oNode,m_strMacroFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strDvmFileKey,oNode,m_strDeviceFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oNode,m_strPpTemplateFile);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oNode,m_strPpEngineProgID);
	xml_GetAttibuteValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTemplateFileKey,oNode,m_strTemplateFile);

	return 0;
}

long CTestWzdDefine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strMacroFileKey,oElement,m_strMacroFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strDvmFileKey,oElement,m_strDeviceFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpTemplateFileKey,oElement,m_strPpTemplateFile);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strPpEngineProgIDKey,oElement,m_strPpEngineProgID);
	xml_SetAttributeValue(CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTemplateFileKey,oElement,m_strTemplateFile);

	return 0;
}

long CTestWzdDefine::IsEqual(CExBaseObject* pObj)
{


	return 0;
}

long CTestWzdDefine::CopyOwn(CExBaseObject* pDesObj)
{	
	ASSERT( pDesObj != NULL);
	CExBaseList::CopyOwn(pDesObj);

	CTestWzdDefine* pTemp = (CTestWzdDefine*)pDesObj;

	pTemp->m_strDeviceFile= m_strMacroFile;
	pTemp->m_strDeviceFile= m_strDeviceFile;
	pTemp->m_strPpTemplateFile= m_strPpTemplateFile;
	pTemp->m_strPpEngineProgID= m_strPpEngineProgID;
	pTemp->m_strTemplateFile= m_strTemplateFile;

	return 0;
}

CExBaseObject* CTestWzdDefine::Clone()
{
	CTestWzdDefine *pNew = new CTestWzdDefine;
	Copy(pNew);

	return pNew;
}

CExBaseObject* CTestWzdDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCDvmDatasetKey)
	{
		return new CDvmDataset();
	}

	return NULL;
}

CExBaseObject* CTestWzdDefine::CreateNewChild(long nClassID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//CTestWzdDefines
CTestWzdDefines::CTestWzdDefines()
{
	
}

CTestWzdDefines::~CTestWzdDefines()
{
	
}

void CTestWzdDefines::Init()
{
	
}

void CTestWzdDefines::InitAfterRead()
{

}


long CTestWzdDefines::IsEqual(CExBaseObject* pObj)
{

	return 0;
}

long CTestWzdDefines::Copy(CExBaseObject* pDesObj)
{
	

	return 0;
}

CExBaseObject* CTestWzdDefines::Clone()
{
	CTestWzdDefines* pNew = new CTestWzdDefines;
	Copy(pNew);

	return pNew;
}

CExBaseObject* CTestWzdDefines::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCTestWzdDefineKey)
	{
		CTestWzdDefine* pTestWzdDefine = new CTestWzdDefine;
		return pTestWzdDefine;
	}

	return NULL;
}

CExBaseObject* CTestWzdDefines::CreateNewChild(long nClassID)
{
	return NULL;
}


long CTestWzdDefines::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CTestWzdDefines::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);


	return 0;
}

