#include "StdAfx.h"
#include "PmcYCTemplate.h"
#include "PmcYCModel.h"
#include "YCTamplateXMLKeys.h"

long CPmcYCTemplate::g_nPmcYCTemplateRef = 0;
CPmcYCTemplate* CPmcYCTemplate::g_pPmcYCTemplate = NULL;

CPmcYCTemplate* CPmcYCTemplate::CreatetPmcYCTemplate()
{
	g_nPmcYCTemplateRef++;

	if (g_nPmcYCTemplateRef == 1)
	{
		g_pPmcYCTemplate = new CPmcYCTemplate();
		ASSERT(g_pPmcYCTemplate != NULL);
	}

	return g_pPmcYCTemplate;
}

void CPmcYCTemplate::Release()
{
	g_nPmcYCTemplateRef--;

	if (g_nPmcYCTemplateRef == 0)
	{
		delete g_pPmcYCTemplate;
		g_pPmcYCTemplate = NULL;
	}
}

CPmcYCTemplate::CPmcYCTemplate(void)
{
	CYCTamplateXMLKeys::CreatetYCTamplateXMLkeys();
}

CPmcYCTemplate::~CPmcYCTemplate(void)
{
	CYCTamplateXMLKeys::Release();
}

void CPmcYCTemplate::ReadYCTamplateXml()
{
	CString strPath = (CString)_P_GetConfigPath();
	strPath += L"YCTemplate.xml";
	ReadYCTamplateXml(strPath);
}

void CPmcYCTemplate::ReadYCTamplateXml(const CString &strPath)
{
	OpenXmlFile(strPath, CYCTamplateXMLKeys::g_pYCTamplateKeys);
}

long CPmcYCTemplate::XMLReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}


long CPmcYCTemplate::XMLWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	return 0;
}

CExBaseObject* CPmcYCTemplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;

	if(strClassID == CYCTamplateXMLKeys::g_pYCTamplateKeys->m_strKeyModel)
	{
		pNew =  new CPmcYCModel();
		ASSERT(pNew != NULL);
	}

	return pNew;
}

