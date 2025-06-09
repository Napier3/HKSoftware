#include "StdAfx.h"
#include "PmcYCModel.h"
#include "PmcYCModelData.h"
#include "YCTamplateXMLKeys.h"



CPmcYCModel::CPmcYCModel(void)
{
}

CPmcYCModel::~CPmcYCModel(void)
{
}

long CPmcYCModel::XMLReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}

long CPmcYCModel::XMLWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	return 0;
}

CExBaseObject* CPmcYCModel::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;

	if(strClassID == CYCTamplateXMLKeys::g_pYCTamplateKeys->m_strKeyData)
	{
		pNew =  new CPmcYCModelData();
		ASSERT(pNew != NULL);
	}

	return pNew;
}

