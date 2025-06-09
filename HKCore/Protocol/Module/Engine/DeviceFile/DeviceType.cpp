#include "StdAfx.h"
#include "DeviceType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDeviceType::CDeviceType(void)
{
}

CDeviceType::~CDeviceType(void)
{
}

long CDeviceType::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	xml_GetAttibuteValue(((CDeviceTypePathXmlKeys*)pXmlRWKeys)->m_strDeviceModelFile,oNode,m_strDeviceModelFile);
	xml_GetAttibuteValue(((CDeviceTypePathXmlKeys*)pXmlRWKeys)->m_strTemplateFile,oNode,m_strTemplateFile);

	return 0;
}

long CDeviceType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElemen,pXmlRWKeys);

	xml_SetAttributeValue(((CDeviceTypePathXmlKeys*)pXmlRWKeys)->m_strDeviceModelFile,oElemen,m_strDeviceModelFile);
	xml_SetAttributeValue(((CDeviceTypePathXmlKeys*)pXmlRWKeys)->m_strTemplateFile,oElemen,m_strTemplateFile);

	return 0;

}

void CDeviceType::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(m_strName, 1, 1, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}