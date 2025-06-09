#include "StdAfx.h"
#include "DeviceTypePath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDeviceTypePath::CDeviceTypePath(void)
{
}

CDeviceTypePath::~CDeviceTypePath(void)
{
}

long CDeviceTypePath::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	xml_GetAttibuteValue(((CDeviceTypePathXmlKeys*)pXmlRWKeys)->m_strPath,oNode,m_strPath);

	return 0;
}

long CDeviceTypePath::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElemen,pXmlRWKeys);

	xml_SetAttributeValue(((CDeviceTypePathXmlKeys*)pXmlRWKeys)->m_strPath,oElemen,m_strPath);

	return 0;

}

CExBaseObject* CDeviceTypePath::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}

CExBaseObject* CDeviceTypePath::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if(strClassID==CDeviceTypePathXmlKeys::g_pXmlRWKeys->m_strPath) 	
	{
		return new CDeviceTypePath();
	}
	else if(strClassID==CDeviceTypePathXmlKeys::g_pXmlRWKeys->m_strDevice)
	{
		return new CDeviceType();
	}

	return NULL;
}
