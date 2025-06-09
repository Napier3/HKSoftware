#include "StdAfx.h"
#include "PpDataInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpDataInterface::CPpDataInterface(void)
{
}

CPpDataInterface::~CPpDataInterface(void)
{
}

long CPpDataInterface::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_strProcessDataMapVarIDKey, oNode, m_strProcedureDataID);
	xml_GetAttibuteValue(pKeys->m_strProcessDataMapPkgIDKey, oNode, m_strPackageDataID);

	m_strID = m_strPackageDataID;

	return 0;
}

long CPpDataInterface::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	m_strID = m_strPackageDataID;

	xml_SetAttributeValue(pKeys->m_strProcessDataMapVarIDKey, oElement, m_strProcedureDataID);
	xml_SetAttributeValue(pKeys->m_strProcessDataMapPkgIDKey,oElement,m_strPackageDataID);

	return 0;
}

BOOL CPpDataInterface::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpDataInterface*)pDest)->m_strPackageDataID = m_strPackageDataID;
	((CPpDataInterface*)pDest)->m_strProcedureDataID = m_strProcedureDataID;

	return CExBaseObject::CopyOwn(pDest);
}

CBaseObject* CPpDataInterface::Clone()
{
	CPpDataInterface *pNew = new CPpDataInterface();
	Copy(pNew);
	return pNew;
}
