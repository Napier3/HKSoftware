#include "StdAfx.h"
#include "PmcYCModelData.h"
#include "YCTamplateXMLKeys.h"


CPmcYCModelData::CPmcYCModelData(void)
{
	m_strUnit = L"";
}

CPmcYCModelData::~CPmcYCModelData(void)
{
}

long CPmcYCModelData::XMLReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(_bstr_t(CYCTamplateXMLKeys::g_pYCTamplateKeys->m_strKeyUnit), oNode, m_strUnit);

	return 0;
}

long CPmcYCModelData::XMLWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement, pXmlRWKeys);

	if (m_strUnit.GetLength() > 0)
	{
		xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strUnit);
	}
	
	return 0;
}



