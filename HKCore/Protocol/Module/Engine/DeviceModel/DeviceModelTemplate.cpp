#include "stdafx.h"
#include"DeviceModelTemplate.h"
#include "DeviceModelXmlKeys.h"

CDeviceModelTemplate::CDeviceModelTemplate()
{
	m_strRemark=_T("");


	m_strName = "DeviceModelTemplate";
	m_strID = m_strName;

}

CDeviceModelTemplate::~CDeviceModelTemplate()
{

}

void CDeviceModelTemplate::Init()
{

}

void CDeviceModelTemplate::InitAfterRead()
{

}

long CDeviceModelTemplate::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strRemark,oNode,m_strRemark);

	return 0;
}

long CDeviceModelTemplate::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strRemark,oXMLDoc,m_strRemark);

	return 0;

}

BOOL CDeviceModelTemplate::IsEqualOwn(CBaseObject* pObj)
{
	return 0;
}

BOOL CDeviceModelTemplate::CopyOwn(CBaseObject* pDesObj)
{
	if (pDesObj == this)
	{
		return FALSE;
	}

	CExBaseObject::CopyOwn(pDesObj);

	((CDeviceModelTemplate*)pDesObj)->m_strRemark = m_strRemark;

	return TRUE;
}

CExBaseObject* CDeviceModelTemplate::Clone()
{
	CDeviceModelTemplate *pNew = new CDeviceModelTemplate();

	Copy(pNew);

	return pNew;
}

CExBaseObject*  CDeviceModelTemplate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

CExBaseObject*  CDeviceModelTemplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strNodeTypeKey)
	{
		return new CPpDeviceNodeType();
	}

	return NULL;
}

void CDeviceModelTemplate::GetAllNodeTypes(CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DMCLASSID_DEVICENODETYPE)
		{
			oList.AddTail(p);
			((CPpDeviceNodeType*)p)->GetAllNodeTypes(oList);
		}

	}
}

CPpDeviceNodeType* Pp_FindDeviceNodeType(CExBaseList *pList, const CString &strNodeType)
{
	CExBaseObject *pFind = NULL;
	CExBaseObject *p = NULL;
	pFind = pList->FindByID(strNodeType);

	if (pFind != NULL)
	{
		return (CPpDeviceNodeType*)pFind;
	}

	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->GetClassID() == DMCLASSID_DEVICENODETYPE)
		{
			pFind = Pp_FindDeviceNodeType((CExBaseList*)p, strNodeType);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return (CPpDeviceNodeType*)pFind;
}

